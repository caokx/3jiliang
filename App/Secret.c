
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

    //�ָ��м����ֵ���������Դ��������������������ʱ����̿�������ʱ�䵹��ʱ����̿��ر���ʱ�䵹��ʱ��
    Std_Memset(&Secret, 0, sizeof(sSecret_TypeDef));
    //fnFile_Read(FileId_InterTmp , FileItemInfoOffAddr_InterTmp_Secret + 31, (u8 *)&Secret.Master.tLinkDly[0] , 16);
    //Secret.Master.tLink[SCOM_PORT_RS485A] = Secret.Master.tLinkDly[SCOM_PORT_RS485A];

    //�����֤�Ƿ�����
    fnEsamOp_ReadEsam_Info(8, &eSamBuf[0], &Esamlen);
    Secret.NeedIdentityAuth = eSamBuf[0];

    fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret, &Secret.nPswRetry[0], 2);
    fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 2, &Secret.tPswFailClose[0], 4);
    fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 6, &Secret.tPrgKeyValid, 2);
    fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 8, &Secret.tPrgKeyLock, 2);
    fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 10, &Secret.nMacErr, 1);

    for (i = 0 ; i < 2 ; i++)
    {
        if (Secret.tPswFailClose[i])        //������������������ڣ�������ʱ��ݼ�
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

    if (Secret.tPrgKeyLock)         //��̿��ر���ʱ�䵹��ʱ
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

    if (Secret.tPrgKeyValid)            //��̿�������ʱ�䵹��ʱ
    {
        if (Secret.tPrgKeyValid <= temp1)   //�������ʱ����ϣ��ñ���ʱ��
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

    //-------��ȡ���ʱ���¼ͷ���ж��Ƿ���δ��������¼���¼-------------
    len = 2 * sizeof(sDate_time_s_TypeDef);
    OffAddr = 0;//FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_Prg].OffAddr + 4;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, &headData.EventStartTime, len);

    //----�¼���¼����ʱ�䲻Ϊ0������ʱ��Ϊ0-------
    if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        //fnEvent_Operation(FileItemInfoNum_Evt_Prg , EVTEND, NULL );
        Event.PriData.Prg_Step = 1;
    }
}

//����������У�麯��
//������PA��ҪУ���Ȩ�ޡ�Pn��ҪУ������롢LimitPA����Ȩ��(�������������������Ȩ��)
//���أ������Ӧ��Ȩ�ޣ����������󷵻�0xFF
ErrorStatus fnSecret_Verify(u8 LimitPA, u8 PA, u8 *Pn)
{
    u8  SecretPara[4];
    u8  MaxRetry;
    //���Ȩ��Ϊ09��У���Ȩ�ޱ���С�ڻ������������Ȩ��
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
        PA = 0;    //645����02��Ȩ��ʱ
    }
    else if (PA == 4)
    {
        PA = 1;    //645����04��Ȩ��ʱ
    }
    //-----698�ް�ȫȨ�ޣ�PA=0---------------

    //У���Ȩ�������Ƿ��ڷ���״̬
    if (Secret.tPswFailClose[PA])
    {
        return (ERROR);
    }
    //����У���4�ֽ�����
    fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SecretPara + 4 * PA, &SecretPara[0], 4);
    //��֤����
    if (Std_Memcmp(Pn, &SecretPara[0], 4) == SUCCESS)
    {
        //������ȷ�����Դ�����0��д��E2�������سɹ�
        Secret.nPswRetry[PA] = 0;
        fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + PA, &Secret.nPswRetry[PA], 1);
        return (SUCCESS);
    }
    //���벻��ȷ�����������������ԵĴ���
    fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_nPswRetry, &MaxRetry, 1);
    //��ǰ���ԵĴ���+1��Ƚ������������Դ���
    if ((++Secret.nPswRetry[PA]) >= MaxRetry)
    {
        //�����������ʱ�䣬����RAM����д���м����
        fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_tPswFailClose, &Secret.tPswFailClose[PA], 2);

        fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 2 + 2 * PA, &Secret.tPswFailClose[PA], 2);
    }
    //д�������Դ�����E2
    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + PA, &Secret.nPswRetry[PA], 1);
    return (ERROR);
}

/************************************************************************
                       ����ϵͳ������ѭ������
����1�������̿��ذ����ұ�̿��ز������ڱ���״̬����ȡ��̿�������ʱ��
����2������������ʱ�䵹��ʱ
����3��������Чʱ�䵹��ʱ
����4����̿�������ʱ�䵹��ʱ
����5����̿��ر���ʱ�䵹��ʱ
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
        if (Secret.tPrgKeyValid)            //��̿�������ʱ�䵹��ʱ
        {
            Secret.tPrgKeyValid--;
            if (Secret.tPrgKeyValid == 0) //�������ʱ����ϣ��ñ���ʱ��
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
// ������:  void fnICEsam_MacErrInc( ErrorStatus Err )
// ���أ�   ��
// ������   ��ESAM��������д��ʱ���ж�MACʧ�ܴ���
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
** Descriptions:    Ӧ�����ӽ�����,������ֵ
** input parameters:   timeout_nego Ӧ������Э�̳�ʱʱ��
** output parameters:
** Returned value:
*********************************************************************************************************/
u8 fnConnect_Secret(u32 timeout_nego, u8 auth_object)
{
    u8 result = ERROR;

    /*
    //----------��ȡЭ��ʱЧ����ֵ---------------
    if(Secret.Chan == SCOM_PORT_IR)
    {
        if(Secret.CA != TERMINAL)  //��վ
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
            Secret.tTerminalDly= 0;   //�µ��ն�Ӧ����������Ҳ��ʧЧԭ�����ն������֤�������������ͨ��
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
        Secret.tTerminalDly = 0;  //�µ��ն�Ӧ����������Ҳ��ʧЧԭ�����ն������֤�������������ͨ��
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
** Descriptions:    Э��ʧЧ�󣬱�������
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
    //fnEsamOp_SessionDestroyed(Secret.CA);//ESAM�ỰʧЧ

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

    //----------��ȡЭ��ʱЧ����ֵ---------------
    /*if(Secret.Chan == SCOM_PORT_IR)
    {
        if(Secret.CA != TERMINAL)  //��վ
        {
            if(Secret.tIRDly)
                result = SUCCESS;
        }
    }
    else */
    if (Secret.Chan < SCOM_PORT_MAX)
    {
        if (Secret.CA == TERMINAL) //�ն�
        {
            if ((Secret.Terminal.tLinkDly[Secret.Chan]) || (Secret.Terminal.tESAMDly) || (Secret.tTerminalDly))
            {
                result = SUCCESS;
            }
        }
        else   //��վ
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
                if (Secret.Master.Auth_object == 2) //�ԳƼ���
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
                if (Secret.Terminal.Auth_object == 2) //�ԳƼ���
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

    if (Secret.tIRRequestDly > 1800) //��Y�䨪��|����
    {
        Secret.tIRRequestDly = 0;
    }

    if (Secret.tIRRequestDly) //o����a???����1??����
    {
        Secret.tIRRequestDly--;
    }
}
