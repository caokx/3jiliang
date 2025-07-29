
#define  _SECRET_GLOBALS
#include <App.h>

void fnSecret_Init(void)
{
    u8      i, len, eSamBuf[20];
    sDate_time_s_TypeDef   PowDn_Datetimes ;
    u32 temp1, temp2;
    u16 Esamlen;

    u32 OffAddr;
    sEvtRcdHead_TypeDef  headData;

    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }

    fnFile_Read(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_PowDnTime, &PowDn_Datetimes, sizeof(sDate_time_s_TypeDef));

    temp1 = fnDateTimeToMin(&SysDatetimes);
    temp2 = fnDateTimeToMin(&PowDn_Datetimes);

    if (temp1 > temp2)
    {
        temp1 = temp1 - temp2;
    }
    else
    {
        temp1 = 0;
    }

    if (fnCheck_Date_time_s(&PowDn_Datetimes) == ERROR)
    {
        temp1 = 0;
    }

    if (fnCheck_Date_time_s(&SysDatetimes) == ERROR)
    {
        temp1 = 0;
    }

    //恢复中间变量值（密码重试次数、本次密码封锁倒计时、编程开关作用时间倒计时、编程开关闭锁时间倒计时）
    Std_Memset(&Secret, 0, sizeof(sSecret_TypeDef));
    //fnFile_Read(FileId_InterTmp , FileItemInfoOffAddr_InterTmp_Secret + 31, (u8 *)&Secret.Master.tLinkDly[0] , 16);
    //Secret.Master.tLink[SCOM_PORT_RS485A] = Secret.Master.tLinkDly[SCOM_PORT_RS485A];

    //身份认证是否启用
    fnEsamOp_ReadEsam_Info(8, &eSamBuf[0], &Esamlen);
    Secret.NeedIdentityAuth = eSamBuf[0];

    fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret, &Secret.nPswRetry[0], 2);
    fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 2, &Secret.tPswFailClose[0], 4);
    fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 6, &Secret.tPrgKeyValid, 2);
    fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 8, &Secret.tPrgKeyLock, 2);
    fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 10, &Secret.nMacErr, 1);

    for (i = 0 ; i < 2 ; i++)
    {
        if (Secret.tPswFailClose[i])        //如果处在密码错误封锁期，则作用时间递减
        {
            if (Secret.tPswFailClose[i] <= temp1)
            {
                Secret.tPswFailClose[i] = 0;
                Secret.nPswRetry[i] = 0;
                fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + i, &Secret.nPswRetry[i], 1);
            }
            else
            {
                Secret.tPswFailClose[i] = Secret.tPswFailClose[i] - temp1;
            }
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 2 + i * 2, &Secret.tPswFailClose[i], 2);
        }
    }

    if (Secret.tPrgKeyLock)         //编程开关闭锁时间倒计时
    {
        if (Secret.tPrgKeyLock <= temp1)
        {
            Secret.tPrgKeyLock = 0;
        }
        else
        {
            Secret.tPrgKeyLock = Secret.tPrgKeyLock - temp1;
        }
        fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 8, &Secret.tPrgKeyLock, 2);
    }

    if (Secret.tPrgKeyValid)            //编程开关作用时间倒计时
    {
        if (Secret.tPrgKeyValid <= temp1)   //编程作用时间完毕，置闭锁时间
        {
            Secret.tPrgKeyValid = 0;
            fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_tPrgKeyLock, &Secret.tPrgKeyLock, 2);
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 8, &Secret.tPrgKeyLock, 2);
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 6, &Secret.tPrgKeyValid, 2);
            Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable = 0;
        }
        else
        {
            Secret.tPrgKeyValid = Secret.tPrgKeyValid - temp1;
        }
        fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 6, &Secret.tPrgKeyValid, 2);
    }

    if (Secret.tPrgKeyValid)
    {
        Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable = 1;
    }
    else
    {
        Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable = 0;
    }

    //-------读取编程时间记录头，判断是否有未结束编程事件记录-------------
    len = 2 * sizeof(sDate_time_s_TypeDef);
    OffAddr = 0;//FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_Prg].OffAddr + 4;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, &headData.EventStartTime, len);

    //----事件记录发生时间不为0，结束时间为0-------
    if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        //fnEvent_Operation(FileItemInfoNum_Evt_Prg , EVTEND, NULL );
        Event.PriData.Prg_Step = 1;
    }
}

//函数：密码校验函数
//参数：PA需要校验的权限、Pn需要校验的密码、LimitPA限制权限(即传入的密码必须满足的权限)
//返回：密码对应的权限，如果密码错误返回0xFF
ErrorStatus fnSecret_Verify(u8 LimitPA, u8 PA, u8 *Pn)
{
    u8  SecretPara[4];
    u8  MaxRetry;
    //最低权限为09，校验的权限必须小于或等于允许的最低权限
    if (PA > 9)
    {
        return (ERROR);
    }
    if (LimitPA > 9)
    {
        return (ERROR);
    }
    if (PA > LimitPA)
    {
        return (ERROR);
    }

    if (PA == 2)
    {
        PA = 0;    //645采用02级权限时
    }
    else if (PA == 4)
    {
        PA = 1;    //645采用04级权限时
    }
    //-----698无安全权限，PA=0---------------

    //校验的权限密码是否处于封锁状态
    if (Secret.tPswFailClose[PA])
    {
        return (ERROR);
    }
    //读出校验的4字节密码
    fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SecretPara + 4 * PA, &SecretPara[0], 4);
    //验证密码
    if (Std_Memcmp(Pn, &SecretPara[0], 4) == SUCCESS)
    {
        //密码正确，重试次数清0，写入E2，并返回成功
        Secret.nPswRetry[PA] = 0;
        fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + PA, &Secret.nPswRetry[PA], 1);
        return (SUCCESS);
    }
    //密码不正确，读出允许密码重试的次数
    fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_nPswRetry, &MaxRetry, 1);
    //当前重试的次数+1后比较允许密码重试次数
    if ((++Secret.nPswRetry[PA]) >= MaxRetry)
    {
        //读出密码闭锁时间，放入RAM，并写入中间变量
        fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_tPswFailClose, &Secret.tPswFailClose[PA], 2);

        fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 2 + 2 * PA, &Secret.tPswFailClose[PA], 2);
    }
    //写密码重试次数到E2
    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + PA, &Secret.nPswRetry[PA], 1);
    return (ERROR);
}

/************************************************************************
                       密码系统处理主循环程序
功能1：如果编程开关按下且编程开关并不处于闭锁状态，提取编程开关作用时间
功能2：密码错误封锁时间倒计时
功能3：密码有效时间倒计时
功能4：编程开关作用时间倒计时
功能5：编程开关闭锁时间倒计时
*************************************************************************/
void fnSecret_Exec(void)
{
    if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON) || (Inactive.PubData.InactiveStamp))
    {
        return;
    }
    //--------------------------
    #if(PRGTime_AutoDec == TRUE)
    if (Bkgrd.PubData.fChange.FlagBit.Minute)
    {
        if (Secret.tPrgKeyValid)            //编程开关作用时间倒计时
        {
            Secret.tPrgKeyValid--;
            if (Secret.tPrgKeyValid == 0) //编程作用时间完毕，置闭锁时间
            {
                fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_tPrgKeyLock, &Secret.tPrgKeyLock, 2);
                fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 8, &Secret.tPrgKeyLock, 2);
            }
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 6, &Secret.tPrgKeyValid, 2);
        }
    }
    #endif

    if (Secret.tPrgKeyValid)
    {
        Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable = 1;
    }
    else
    {
        Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable = 0;
    }

    return;
}

//*********************************************************************************
// 函数名:  void fnICEsam_MacErrInc( ErrorStatus Err )
// 返回：   无
// 描述：   对ESAM进行数据写入时，判断MAC失败次数
//*********************************************************************************
void fnICEsam_MacErrInc(ErrorStatus Err)
{
    if (Err == ERROR)
    {
        Secret.nMacErr++;
        if (Secret.nMacErr <= MAX_MACERR)
        {
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 10, &Secret.nMacErr, 1);
        }
        else
        {
            Secret.RemoteValid = 0;
        }
    }
}

/*********************************************************************************************************
** Function name:
** Descriptions:    应用连接建立后,变量赋值
** input parameters:   timeout_nego 应用连接协商超时时间
** output parameters:
** Returned value:
*********************************************************************************************************/
u8 fnConnect_Secret(u32 timeout_nego, u8 auth_object)
{
    u8 result = ERROR;

    /*
    //----------获取协商时效门限值---------------
    if(Secret.Chan == SCOM_PORT_IR)
    {
        if(Secret.CA != TERMINAL)  //主站
        {
            Secret.tIRDly = 0;

            fnReadDlyTime_Esam(&Secret.Master.tESAMDly, Secret.CA , 0);
            Bkgrd.PubData.MtSysSta.SysStaBit.RemoteValid = 1;       ///////
            Secret.Master.LinkChan = Secret.Chan;
            Secret.Master.tLinkDly[Secret.Chan] = timeout_nego;
            Secret.Master.tLink[Secret.Chan] = timeout_nego;
            Secret.Master.Auth_object = auth_object;
            result = SUCCESS;
        }
    }
    else if(Secret.Chan < SCOM_PORT_MAX)
    {
        if(Secret.CA == TERMINAL)
        {
            fnReadDlyTime_Esam(&Secret.Terminal.tESAMDly , Secret.CA , 0);
            Secret.tTerminalDly= 0;   //新的终端应用连接命令也可失效原来的终端身份认证命令，不区分物理通道
            Bkgrd.PubData.MtSta.MtSta3.StaBit.TrmRemoteValid = 0;
            Bkgrd.PubData.MtSysSta.SysStaBit.TrmRemoteValid = 0;
            Secret.Terminal.LinkChan = Secret.Chan;
            Secret.Terminal.tLinkDly[Secret.Chan] = timeout_nego;
            Secret.Terminal.tLink[Secret.Chan] = timeout_nego;
            Secret.Terminal.Auth_object = auth_object;
            result = SUCCESS;
        }
        else
        {
            fnReadDlyTime_Esam(&Secret.Master.tESAMDly, Secret.CA , 0);
            Bkgrd.PubData.MtSysSta.SysStaBit.RemoteValid = 1;
            Secret.Master.LinkChan = Secret.Chan;
            Secret.Master.tLinkDly[Secret.Chan] = timeout_nego;
            Secret.Master.tLink[Secret.Chan] = timeout_nego;
            Secret.Master.Auth_object = auth_object;
            result = SUCCESS;
        }
    }
    */

    if (Secret.CA == TERMINAL)
    {
        fnReadDlyTime_Esam(&Secret.Terminal.tESAMDly, Secret.CA, 0);
        Secret.tTerminalDly = 0;  //新的终端应用连接命令也可失效原来的终端身份认证命令，不区分物理通道
        if (Secret.Terminal.tESAMDly)
        {
            Bkgrd.PubData.MtSta.MtSta3.StaBit.TrmRemoteValid = 1;
            Bkgrd.PubData.MtSysSta.SysStaBit.TrmRemoteValid = 1;
        }
        else
        {
            Bkgrd.PubData.MtSta.MtSta3.StaBit.TrmRemoteValid = 0;
            Bkgrd.PubData.MtSysSta.SysStaBit.TrmRemoteValid = 0;
        }
        Secret.Terminal.LinkChan = Secret.Chan;
        Secret.Terminal.tLinkDly[Secret.Chan] = timeout_nego;
        Secret.Terminal.tLink[Secret.Chan] = timeout_nego;
        Secret.Terminal.Auth_object = auth_object;
        result = SUCCESS;
    }
    else
    {
        fnReadDlyTime_Esam(&Secret.Master.tESAMDly, Secret.CA, 0);
        if (Secret.Master.tESAMDly)
        {
            Bkgrd.PubData.MtSysSta.SysStaBit.RemoteValid = 1;
        }
        else
        {
            Bkgrd.PubData.MtSysSta.SysStaBit.RemoteValid = 0;
        }
        Secret.Master.LinkChan = Secret.Chan;
        Secret.Master.tLinkDly[Secret.Chan] = timeout_nego;
        Secret.Master.tLink[Secret.Chan] = timeout_nego;
        Secret.Master.Auth_object = auth_object;
        result = SUCCESS;
    }

    return result;
}

/*********************************************************************************************************
** Function name:
** Descriptions:    协商失效后，变量清零
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
u8 fnConnectDis_SecretClr(void)
{
    u8 result = ERROR;

    if (Secret.CA == MASTER)
    {
        Std_Memset((u8 *)&Secret.Master.tLinkDly[0], 0x00, sizeof(sLinkData_TypeDef));
    }
    else
    {
        Std_Memset((u8 *)&Secret.Terminal.tLinkDly[0], 0x00, sizeof(sLinkData_TypeDef));
    }

    Secret.tIRDly = 0;
    Secret.tIRRequestDly = 0;
    Secret.tTerminalDly = 0;
    //fnEsamOp_SessionDestroyed(Secret.CA);//ESAM会话失效

    //fnEvent_Operation(FileItemInfoNum_Evt_Prg , EVTEND, NULL );
    //Bkgrd.PubData.RestEsamFlag = 0x55;
    return result;
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
u8 fnGet_ConnSta(void)
{
    u8 result = ERROR ;

    if (fnRead_SecurtyStatus() == true)
    {
        return SUCCESS;
    }

    //----------获取协商时效门限值---------------
    /*if(Secret.Chan == SCOM_PORT_IR)
    {
        if(Secret.CA != TERMINAL)  //主站
        {
            if(Secret.tIRDly)
                result = SUCCESS;
        }
    }
    else */
    if (Secret.Chan < SCOM_PORT_MAX)
    {
        if (Secret.CA == TERMINAL) //终端
        {
            if ((Secret.Terminal.tLinkDly[Secret.Chan]) || (Secret.Terminal.tESAMDly) || (Secret.tTerminalDly))
            {
                result = SUCCESS;
            }
        }
        else   //主站
        {
            if ((Secret.Master.tLinkDly[Secret.Chan]) || (Secret.Master.tESAMDly))
            {
                result = SUCCESS;
            }
        }
    }

    return result;
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnCHK_LinkDly(void)
{
    u8 i;

    for (i = 0; i < SCOM_PORT_MAX; i++)
    {
        if (Secret.Master.tLinkDly[i])
        {
            Secret.Master.tLinkDly[i]--;
            if (Secret.Master.tLinkDly[i] == 0)
            {
                if (Secret.Master.Auth_object == 2) //对称加密
                {
                    Secret.Master.tESAMDly = 0x00;
                    Bkgrd.PubData.MtSysSta.SysStaBit.RemoteValid = 0;
                    Secret.Master.Auth_object = 0;
                    //fnEsamOp_SessionDestroyed(MASTER);
                    SEGGER_RTT_printf(0, "ESAMDestroyed MASTER \n");
                }
                Secret.Master.LinkChan = 0x00;
            }
        }
    }

    for (i = 0; i < SCOM_PORT_MAX; i++)
    {
        if (Secret.Terminal.tLinkDly[i])
        {
            Secret.Terminal.tLinkDly[i]--;
            if (Secret.Terminal.tLinkDly[i] == 0)
            {
                if (Secret.Terminal.Auth_object == 2) //对称加密
                {
                    Secret.Terminal.tESAMDly = 0x00;
                    Bkgrd.PubData.MtSysSta.SysStaBit.TrmRemoteValid = 0;
                    Secret.Terminal.Auth_object = 0;
                    SEGGER_RTT_printf(0, "ESAMDestroyed TERMINAL \n");
                    //fnEsamOp_SessionDestroyed(TERMINAL);
                }
                Secret.Terminal.LinkChan = 0x00;
            }
        }
    }
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnCHK_ESAMDly(void)
{
    u8 i;

    if (Secret.Master.tESAMDly)
    {
        Secret.Master.tESAMDly--;
        if (Secret.Master.tESAMDly != 0)
        {
            Secret.RemoteValid = 1;
            Bkgrd.PubData.MtSysSta.SysStaBit.RemoteValid = 1;
        }
        else
        {
            for (i = 0; i < SCOM_PORT_MAX; i++)
            {
                Secret.Master.tLinkDly[i] = 0;
            }
            Bkgrd.PubData.MtSysSta.SysStaBit.RemoteValid = 0;
            Secret.Master.Auth_object = 0;
            //fnEsamOp_SessionDestroyed(MASTER);
            SEGGER_RTT_printf(0, "ESAMDestroyed MASTER \n");
        }
    }

    if (Secret.Terminal.tESAMDly)
    {
        Secret.Terminal.tESAMDly--;
        if (Secret.Terminal.tESAMDly != 0)
        {
            Secret.RemoteValid = 1;
            Bkgrd.PubData.MtSysSta.SysStaBit.TrmRemoteValid = 1;
            Bkgrd.PubData.MtSysSta.SysStaBit.TrmSecValid = 0;
        }
        else
        {
            for (i = 0; i < SCOM_PORT_MAX; i++)
            {
                Secret.Terminal.tLinkDly[i] = 0;
            }
            Bkgrd.PubData.MtSysSta.SysStaBit.TrmRemoteValid = 0;
            Secret.Terminal.Auth_object = 0;
            //fnEsamOp_SessionDestroyed(TERMINAL);
            SEGGER_RTT_printf(0, "ESAMDestroyed TERMINAL \n");
        }
    }

    /*
    if(Secret.tIRDly)
    {
        Secret.tIRDly--;
        Secret.RemoteValid = 1;
        //Bkgrd.PubData.MtSta.MtSta3.StaBit.RemoteValid = 1;
        Bkgrd.PubData.MtSysSta.SysStaBit.RemoteValid = 1;
    }
    */

    if (Secret.tTerminalDly)
    {
        Secret.tTerminalDly--;
        if (Secret.tTerminalDly != 0)
        {
            Secret.RemoteValid = 1;
            Bkgrd.PubData.MtSysSta.SysStaBit.TrmSecValid = 1;
            Bkgrd.PubData.MtSysSta.SysStaBit.TrmRemoteValid = 0;
        }
        else
        {
            Bkgrd.PubData.MtSysSta.SysStaBit.TrmSecValid = 0;
        }
    }

    if (Secret.tIRRequestDly)
    {
        Secret.tIRRequestDly--;
    }

    if ((Secret.Master.tESAMDly == 0) && (Secret.Terminal.tESAMDly == 0) &&
        /*(Secret.tIRDly == 0) &&*/ (Secret.tTerminalDly == 0)  && (Secret.tIRRequestDly == 0))
    {
        Secret.Terminal.Auth_object = 0;
        Secret.Master.Auth_object = 0;
        Secret.RemoteValid = 0;
        Bkgrd.PubData.MtSysSta.SysStaBit.RemoteValid = 0;
        Bkgrd.PubData.MtSysSta.SysStaBit.TrmRemoteValid = 0;
        Bkgrd.PubData.MtSysSta.SysStaBit.TrmSecValid = 0;
        if ((BSP_EASM_GetPower() == true) && (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable == 0))
        {
            BSP_Esam_Stop();
            SEGGER_RTT_printf(0, "ESAM Stop \n");
        }
    }

    if (Secret.tIRRequestDly > 1800) //èY′í′|àí
    {
        Secret.tIRRequestDly = 0;
    }

    if (Secret.tIRRequestDly) //oìía???óμ1??ê±
    {
        Secret.tIRRequestDly--;
    }
}
