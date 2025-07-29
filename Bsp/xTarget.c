//硬件总初始化文件

#define  _XTARGET_GLOBALS

#include <BSP.h>
#include <Measure.h>

void fnRTCDrive_Delay(void)
{
    u16 i;
    for (i = 400; i > 0; i--)
    {
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }
}

// t*ms
void SystemDelay(u16 t)
{
    u16 i;
    while (t--)
    {
        for (i = 0; i < 1760; i++); // dyf old=1600
    }
}

/*********************************************************************************************************
** Function name:        fnDelayMs for 1100 us when operate on 3.6864MHz and t=1; and 980ms when on 3.6864MHz and t=1000
** Descriptions:        Software Delay
** input parameters:
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void fnDelayMs(u16 t)
{
    u32 i;
    uint32_t cur_freq;

    cur_freq = fnMainClock_Get();
    cur_freq = 2 * cur_freq / 32768; // dyf add
    while (t--)
    {
        for (i = 0; i < cur_freq; i++)    // dyf 改
        {
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
        }
        WDT->EN = 0xbb;
    }
}

void fnKEYINT_Init(void)
{
}

void fnWDT_Restart(void)
{
    WDT->EN = 0xbb;     /* restart watch dog timer */
}

void fnRCC_Configuration(void)
{
    fnMainClock_Init();
}

//函数功能：IO口初始化
//入口参数：无
//出口参数：无
void fnGPIO_Configuration(void)
{
    //Rn8xxx_GPIO_CfgFun(PinSWDCLK,_SWD);
    //Rn8xxx_GPIO_CfgFun(PinSWDIO,_SWD);
    //Rn8xxx_GPIO_CfgPullMode(PinSWDCLK , Pull_ON);
    //Rn8xxx_GPIO_CfgPullMode(PinSWDIO , Pull_ON);

    Rn8xxx_GPIO_CfgFun(PinSPK, _NORMALIO); /*"蜂鸣器"*/
    Rn8xxx_GPIO_CfgIOMode(PinSPK, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinSPK, 0);

    Rn8xxx_GPIO_CfgFun(PinClkOut, _RTC_OUT); /*"秒脉冲输出"*/

    Rn8xxx_GPIO_CfgFun(PinKCOVER, _NORMALIO); /*"开上盖检测"*/
    Rn8xxx_GPIO_CfgIOMode(PinKCOVER, GPIO_MODE_IN, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinKTURB, _NORMALIO); /*"按键"*/
    Rn8xxx_GPIO_CfgIOMode(PinKTURB, GPIO_MODE_IN, NORMAL_IN);

    #if(nPhs==ThreePhs)
    Rn8xxx_GPIO_CfgFun(PinKBTMBOX, _NORMALIO); /*"开端盖检测"*/
    Rn8xxx_GPIO_CfgIOMode(PinKBTMBOX, GPIO_MODE_IN, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinMR_Check, _NORMALIO); /*" 磁检测 "*/
    Rn8xxx_GPIO_CfgIOMode(PinMR_Check, GPIO_MODE_IN, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinKTURA, _NORMALIO); /*"按键"*/
    Rn8xxx_GPIO_CfgIOMode(PinKTURA, GPIO_MODE_IN, NORMAL_IN);
    #endif

    Rn8xxx_GPIO_CfgFun(PinLCDBackLight, _NORMALIO); /*"液晶背光"*/
    Rn8xxx_GPIO_CfgIOMode(PinLCDBackLight, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinLCDBackLight, 0);

    Rn8xxx_GPIO_CfgFun(PinJump, _NORMALIO); /*继电器报警LED"*/
    Rn8xxx_GPIO_CfgIOMode(PinJump, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinJump, 1);    //0 点亮

    Rn8xxx_GPIO_CfgFun(PinAD_3V6, _AIN); /*"时钟电池电压检测脚"*/

    #if(nPhs==ThreePhs)
    Rn8xxx_GPIO_CfgFun(PinAD_6V, _AIN); /*"抄表电池电压检测脚"*/
    #endif
    Rn8xxx_GPIO_CfgFun(PinLVD, _AIN); /*"系统电源检测"*/
    /*"****************************计量模块相关IO口*********************************************************************"*/
    //      #if(nPhs==ThreePhs)
    //   RN8302_PowerOff();
    //       RN8207_PowerOff();
    //  #endif
    /*"*****************************继电器模块相关IO口*********************************************************************"*/
    #if(nPhs==SinglePhs)
    RelayCheck_PowerON();
    #endif

    Rn8xxx_GPIO_CfgFun(PinRelayCheck, _NORMALIO); /*"继电器测试脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinRelayCheck, GPIO_MODE_IN, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinWarn, _NORMALIO); /*"报警继电器控制"*/
    Rn8xxx_GPIO_CfgIOMode(PinWarn, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinWarn, 0);

    Rn8xxx_GPIO_CfgFun(PinLoadRelayON, _NORMALIO); /*"继电器控制1"*/
    Rn8xxx_GPIO_CfgIOMode(PinLoadRelayON, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinLoadRelayON, 0);

    Rn8xxx_GPIO_CfgFun(PinLoadRelayOFF, _NORMALIO); /*"继电器控制2"*/
    Rn8xxx_GPIO_CfgIOMode(PinLoadRelayOFF, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinLoadRelayOFF, 0);

    /*"***************************通讯模块相关IO口***RX/TX管脚在BSP_UART模块内初始化******************************************************************"*/
    #if(nPhs==ThreePhs)
    Rn8xxx_GPIO_CfgFun(PinCtrlWake, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinCtrlWake, GPIO_MODE_OUT, N_OPENDRAIN_OUT);
    IRPowerPowerOn();       //红外电源打开

    Rn8xxx_GPIO_CfgFun(PinZB_CTRL, _NORMALIO); /*" 载波电源脚   "*/
    Rn8xxx_GPIO_CfgIOMode(PinZB_CTRL, GPIO_MODE_OUT, N_OPENDRAIN_OUT);
    Rn8xxx_GPIO_SetPin(PinZB_CTRL, 0);
    #else
    Rn8xxx_GPIO_CfgFun(PinSCAP_VCTRL, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinSCAP_VCTRL, GPIO_MODE_OUT, NORMAL_OUT);
    SCAP_VCTRL_PowerOff();      //

    #endif

    Rn8xxx_GPIO_CfgFun(PinSET_ZB, _NORMALIO); /*" 载波设置脚   "*/
    Rn8xxx_GPIO_CfgIOMode(PinSET_ZB, GPIO_MODE_OUT, N_OPENDRAIN_OUT);     /*" 开漏输出 "*/
    Rn8xxx_GPIO_SetPin(PinSET_ZB, 1);  /*" 常态高阻 "*/

    Rn8xxx_GPIO_CfgFun(PinRST_ZB, _NORMALIO); /*"载波复位脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinRST_ZB, GPIO_MODE_OUT, N_OPENDRAIN_OUT);     /*" 开漏输出 "*/
    Rn8xxx_GPIO_SetPin(PinRST_ZB, 1);  /*" 常态高阻 "*/

    Rn8xxx_GPIO_CfgFun(PinSTA_ZB, _NORMALIO); /*"载波状态脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinSTA_ZB, GPIO_MODE_IN, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinEVENOUT, _NORMALIO); /*"事件上报口"*/
    Rn8xxx_GPIO_CfgIOMode(PinEVENOUT, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinEVENOUT, 0);

    //管理模组复位信号
    Rn8xxx_GPIO_CfgFun(PinManageModuleRSTM, _NORMALIO); /*"事件上报口"*/
    Rn8xxx_GPIO_CfgIOMode(PinManageModuleRSTM, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinManageModuleRSTM, 1);

    // 管理模组插拔信号
    Rn8xxx_GPIO_CfgFun(PinManageModuleCOMRQIN, _NORMALIO);
    Rn8xxx_GPIO_CfgPullMode(PinManageModuleCOMRQIN, Pull_ON);
    Rn8xxx_GPIO_CfgIOMode(PinManageModuleCOMRQIN, GPIO_MODE_IN, NORMAL_IN);
}

//定时器初始化 用做5MS中断在1.8432M模式下
void fnINTTC0_RCInit(void)
{
    Rn8xxx_TC_TimeInit(Timer0, 5);
    Rn8xxx_TC_TimeStar(Timer0, ENABLE);
}

/*****************************************************************************
** Function name:fnINTTC1_Init
**
** Description:定时器1初始化
**
** Parameters:
**
** Returned value:
**
******************************************************************************/

void fnLVD_Init(void)
{
    #if( (POWERCHACK == CHECKLVD)||(POWERCHACK == CHECKLVD_CMP1)||(POWERCHACK == CHECKLVD_CMP2))
    Rn8xxx_LVD_Init(LVDS_Vol2p9, LVDCMPSAR_IE_Enable);
    #endif

    #if( (POWERCHACK == CHECKCMP1)||(POWERCHACK == CHECKLVD_CMP1))
    Rn8xxx_GPIO_CfgFun(_PIN0_2, _AIN);// 开启CMP1检测
    Rn8xxx_CMP_Init(CMP1_Channel, CMP_R600K_Disable, CMP_Hysen_Enable, LVDCMPSAR_IE_Enable);
    #endif

    #if( (POWERCHACK == CHECKCMP2)||(POWERCHACK == CHECKLVD_CMP2))
    Rn8xxx_GPIO_CfgFun(_PIN0_3, _AIN);// 开启CMP2检测
    Rn8xxx_CMP_Init(CMP2_Channel, CMP_R600K_Disable, CMP_Hysen_Enable, LVDCMPSAR_IE_Enable);
    #endif
}

void fnINTTCAll_Init(void)
{
    Rn8xxx_TC_TimeInit(Timer0, 5);
    Rn8xxx_TC_TimeStar(Timer0, ENABLE);
}

void fnRTCDrive_Init(void)
{
    // u8    i;

    #if 0
    for (i = 0; i < 20; i++)
    {
        if (SUCCESS == Rn8xxx_RTC_CtlInit(RTC_TSE_AutoMode, RTC_TCP_2Sec, RTC_FOUT_1HZ))
        {
            break;
        }
        else
        {
            SystemDelay(100);
            fnWDT_Restart();
        }
    }
    #endif
}

void fnINTRTC_Sleep(void)
{
    //u8    i;
    #if 0
    for (i = 0; i < 20; i++)
    {
        if (SUCCESS == Rn8xxx_RTC_CtlInit(RTC_TSE_AutoMode, RTC_TCP_30Sec, RTC_FOUT_Disable))
        {
            break;
        }
        else
        {
            SystemDelay(100);
            fnWDT_Restart();
        }
    }
    #endif
    fnWDT_Restart();
    Rn8xxx_RTC_Cnt1Init(1);  //RTC秒中断
}

/*********************************************************************************************************
** Function name:       fnSysClock_Read
** Descriptions:        系统时钟读取
** input parameters:    Clock目标指针
** output parameters:       None
** Returned value:     SUCCESS成功，ERROR失败
*********************************************************************************************************/
ErrorStatus fnSysClock_Read(sDF01 *Clock)
{
    u8 Buffer[7];
    if (!Rn8xxx_RTC_Read(Buffer))
    {
        return (ERROR);
    }
    Clock->Second = (Buffer[0]) & 0x7f;
    Clock->Minute = (Buffer[1]) & 0x7f;
    Clock->Hour = (Buffer[2]) & 0x3f;
    Clock->Day = (Buffer[4]) & 0x3f;
    Clock->Month = (Buffer[5]) & 0x1f;
    Clock->Year = (Buffer[6]);
    Clock->Week = (Buffer[3]) & 0x07;
    return (SUCCESS);
}

/*********************************************************************************************************
** Function name:       fnSysClock_Write
** Descriptions:        系统时钟写入
** input parameters:    Clock源指针
** output parameters:       None
** Returned value:     SUCCESS成功，ERROR失败
*********************************************************************************************************/
ErrorStatus fnSysClock_Write(sDF01 *Clock)
{
    u8 Buffer[7];
    Buffer[0] = (Clock->Second) & 0x7f;
    Buffer[1] = (Clock->Minute) & 0x7f;
    Buffer[2] = (Clock->Hour) & 0x3f;
    Buffer[3] = (Clock->Week) & 0x07;
    Buffer[4] = (Clock->Day) & 0x3f;
    Buffer[5] = (Clock->Month) & 0x1f;
    Buffer[6] = (Clock->Year);
    return (Rn8xxx_RTC_Write(Buffer, 3));
}

void fnSysDateTimes(sDate_time_s_TypeDef * ptime)
{
    u8 buf[10];
    //  u8 cout_fault = 0;       //得到时间错误的错误，最多三次，多余三次则报失败

    Rn8xxx_RTC_Read(buf);
    ptime->second = fnBcdToHex_u8(buf[0]);
    ptime->minute = fnBcdToHex_u8(buf[1]);
    ptime->hour  = fnBcdToHex_u8(buf[2]);
    ptime->day   = fnBcdToHex_u8(buf[4]);
    ptime->month = fnBcdToHex_u8(buf[5]);
    //ptime->year  = BUILD_U16(buf[6], 0x07) - 1;
    ptime->year  = fnBcdToHex_u8(buf[6]);
    ptime->year  = ptime->year + 2000;

    return ;
}

/*****************************************************************************
** Function name:fnINTTC1_Stop
**
** Description:TC1定时器关闭
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
//void fnINTTC1_Stop(void)
//{
//  TC1->CTRL = 0x00;       // star TC0
//    TC1->IE = 0x00;           // IRQ enable
//    NVIC_DisableIRQ(TC1_IRQn);
//}
//---------------------------------------------------------
//函数功能：硬件系统初始化
//入口参数：无
//出口参数：无
void fnTarget_Init(void)
{
    fnRCC_Configuration();
    fnGPIO_Configuration();
    fnINTTCAll_Init();

    #if(KEY_Enable == TRUE)
    Std_Memset(&Key, 0, sizeof(sKey_TypeDef));
    Key.Release |= 0X00A0;
    #endif

    fnFm24c256_Init();

    #if(nPhs==ThreePhs)
    fnRN8302Mode_Init(MeasureModeEMM);
    #endif

    fnMX25LXX_Init();

    NVIC_EnableIRQ(TC0_IRQn);

    NVIC_DisableIRQ(KBI_IRQn);
    NVIC_DisableIRQ(RTC_IRQn);
}

bool fnCheckSocEE(u8 DeviceNo, u16 Address, u8 *Buff, u8 Length)
{
    u8 i;
    u8 Data;

    for (i = 0; i < Length; i++)
    {
        Data = *(Read_EEPROM + Address + i);
        if (Data != Buff[i])
        {
            return false;
        }
    }
    return true;
}

ErrorStatus fnOperateSocEE(BOOL Read_Write, u8 DeviceNo, u16 Address, u8 *Buff, u8 Length, u8 Repeat)
{
    u8 i;
    u8 ReReadTimes;
    if (Length == 0)
    {
        return ERROR;
    }
    eepromWakeup();
    for (ReReadTimes = 0; ReReadTimes <= Repeat; ReReadTimes++)
    {
        if (Read == Read_Write)
        {
            for (i = 0; i < Length; i++)
            {
                *(Buff + i) = *(Read_EEPROM + Address + i);
            }
        }
        else
        {
            i = eepromProgram(EEPROM_MEMORY_BASE + Address, (uint32_t)Buff, Length);
            if (i)
            {
                continue;
            }
        }
        if ((fnCheckSocEE(DeviceNo, Address, Buff, Length) == true) || (ReReadTimes > Repeat))
        {
            break;
        }
    }
    eepromStandby();
    if (ReReadTimes >= Repeat)
    {
        return ERROR;
    }
    return (SUCCESS);
}

//---------------------------------------------------
//函数功能：SOC内部EEPROM读取数据，在此实现跨页操作
//入口参数：Dst取数缓冲区目标指针，Src取数源地址，DatLen要取的数据长度，Repeat失败重复次数
//出口参数：SUCCESS成功，ERROR失败
ErrorStatus fnSocEE_Read(u8 *Dst, u32 Src, u32 DatLen, u8 Repeat)
{
    u16 AddressL, AddressH;
    u8 B;
    u16 AddingTimes = 0;

    if (DatLen == 0)
    {
        return (ERROR);
    }
    if (SocEE_MAXSize <= (Src + DatLen))
    {
        return (ERROR);
    }

    while (DatLen)
    {
        if (++AddingTimes > 600)
        {
            return (ERROR);    //防止死循环
        }
        AddressH = (u16)(Src >> 16);
        AddressL = (u16)Src;
        if ((((~AddressL)&SocEE_PageSize) +1) >= DatLen) /*与运算其实相当于求模运算，该语句保证从NVRAM中每一页的任意点开始*/
        {
            B = DatLen;
        }
        else
        {
            B = ((~AddressL)&SocEE_PageSize) +1;
        }

        if (ERROR == fnOperateSocEE(Read, AddressH, AddressL, Dst, B, Repeat))
        {
            return (ERROR);
        }
        Dst += B;
        Src += B;
        DatLen -= B;
    }
    return (SUCCESS);
}

//---------------------------------------------------
//函数功能：SOC内部存储器写入数据
//入口参数：Dst写入数据的目标地址，Src写数缓冲区源指针，DatLen要写的数据长度，Repeat失败重复次数
//出口参数：SUCCESS成功，ERROR失败
ErrorStatus fnSocEE_Write(u32 Dst, u8 *Src, u32 DatLen, u8 Repeat)
{
    u16 AddressL, AddressH;
    u8 B;
    u16 AddingTimes = 0;

    if (DatLen == 0)
    {
        return (ERROR);
    }
    if (SocEE_MAXSize <= (Dst + DatLen))
    {
        return (ERROR);
    }

    while (DatLen)
    {
        if (++AddingTimes > 600)
        {
            return (ERROR);    //防止死循环
        }

        AddressH = (u16)(Dst >> 16);
        AddressL = (u16)Dst;
        if ((((~AddressL)&SocEE_PageSize) +1) >= DatLen) /*与运算其实相当于求模运算，该语句保证从NVRAM中每一页的任意点开始*/
        {
            B = DatLen;
        }
        else
        {
            B = ((~AddressL)&SocEE_PageSize) +1;
        }

        if (ERROR == fnOperateSocEE(Write, AddressH, AddressL, Src, B, Repeat))
        {
            return (ERROR);
        }
        Dst += B;
        Src += B;
        DatLen -= B;
    }
    return (SUCCESS);
}

#define REGCHKADDLIST_NUM   sizeof(RegCheckMsgList)/sizeof(RegCheckItemMsg_Type)

typedef struct
{
    u32 regAddr;    //寄存器地址
    u32 bitMask;    //位掩码
} RegCheckItemMsg_Type;

typedef struct
{
    u8  wrSta;      //是否已经被正常写入,0--未写入,1--已写入
    u32 regData;    //寄存器值
} RegCheckItemSta_Type;

const RegCheckItemMsg_Type RegCheckMsgList[] =
{
    {(u32) &SYSCTL->OSC_CTRL1,   0xFFFFFFFF},
    {(u32) &SYSCTL->OSC_CTRL2,   0xFFFFFFFF},
    {(u32) &SYSCTL->SYS_MODE,    0xFFFFFFFF},
    {(u32) &SYSCTL->SYS_PD,  0xFFFFFFFF},
    {(u32) &MADC->LVD_CTRL,  0xFFFFFFFF},
    {(u32) &TC0->CTRL,   0xFFFFFFFF},
    {(u32) &TC0->PS, 0xFFFFFFFF},
    {(u32) &TC0->DN, 0xFFFFFFFF},
    {(u32) &GPIO->PCA0,  0xFFFFFFFF},
    {(u32) &GPIO->PCA1,  0xFFFFFFFF},
    {(u32) &GPIO->PCB,   0xFFFFFFFF},
    {(u32) &GPIO->PCD,   0xFFFFFFFF},
};

RegCheckItemSta_Type RegCheckStaList[REGCHKADDLIST_NUM];
u16 CheckRegStamp;
//---------------------------------------------------
//函数功能：检测SOC内部指定寄存器是否被异常改写
//入口参数：InitAll--全部检测状态初始化
//        AdOrRmItem--0，对所有寄存器状态进行检测；1，插入一个待检测的寄存器；2，删除一个不需要检测的寄存器
//        regAddr--寄存器地址
//出口参数：SUCCESS成功，ERROR失败
ErrorStatus fnSocRegCheck(bool InitAll, u8 AdOrRmItem, u32 regAddr)
{
    u16 i;
    ErrorStatus ret;

    if (fnStamp_Through(CheckRegStamp) < 5000)
    {
        return (SUCCESS);
    }
    CheckRegStamp = SysStamp ? SysStamp : (SysStamp - 1);

    ret = ERROR;

    if (false == InitAll)
    {
        switch (AdOrRmItem)
        {
            case 0:
                ret = SUCCESS;
                for (i = 0; i < REGCHKADDLIST_NUM; i++)
                {
                    if (1 == RegCheckStaList[i].wrSta)
                    {
                        if ((RegCheckStaList[i].regData & RegCheckMsgList[i].bitMask) == (*(u32*)RegCheckMsgList[i].regAddr & RegCheckMsgList[i].bitMask))
                        {
                            ret = SUCCESS;
                        }
                        else
                        {
                            ret = ERROR;
                            break;
                        }
                    }
                }
                break;

            case 1:
                for (i = 0; i < REGCHKADDLIST_NUM; i++)
                {
                    if (RegCheckMsgList[i].regAddr == regAddr)
                    {
                        RegCheckStaList[i].regData = *(u32*)RegCheckMsgList[i].regAddr;
                        RegCheckStaList[i].wrSta = 1;
                        ret = SUCCESS;
                        break;
                    }
                }
                break;

            case 2:
                for (i = 0; i < REGCHKADDLIST_NUM; i++)
                {
                    if (RegCheckMsgList[i].regAddr == regAddr)
                    {
                        RegCheckStaList[i].regData = 0;
                        RegCheckStaList[i].wrSta = 0;
                        ret = SUCCESS;
                        break;
                    }
                }
                break;

            default:
                break;
        }
    }
    else
    {
        Std_Memset(&RegCheckStaList[0], 0x00, sizeof(RegCheckStaList));
        ret = SUCCESS;
    }

    return (ret);
}

//---------------------------------------------------
//函数功能：检测SOC内部指定寄存器是否被异常改写
//入口参数：
//出口参数：SUCCESS成功，ERROR失败
ErrorStatus fnSocRegCheckAddAll(void)
{
    u16 i;
    for (i = 0; i < REGCHKADDLIST_NUM; i++)
    {
        RegCheckStaList[i].regData = *(u32*)RegCheckMsgList[i].regAddr;
        RegCheckStaList[i].wrSta = 1;
    }

    return (SUCCESS);
}

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */

/*********************************************************************************************************
** Function name:        fnPowerOn_DrvieInit
** Descriptions:         切换到高频模式前，上电初始化
** input parameters:     无
** output parameters:   无
** Returned value:   无
*********************************************************************************************************/
void fnPowerOn_DrvieInit(void)
{
    fnLVD_Init();
    fnWDT_Restart();
    fnRTCDrive_Init();
}
