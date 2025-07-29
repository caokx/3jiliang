
#define  _POWER_UP_DOWN_GLOBALS
#include <Includes.h>

/*********************************************************************************************************
** Function name:       fnPowerDown_Check
** Descriptions:        掉电检测程序
**                  ①仅用于电表当前处于PowerOn/powerSub状态时，检测掉电；
**                  ②检测到LVD阈值低于2.9V时，置低功耗处理标志；
**                  ③LVD阈值正常，Cmp检测到低，不进低功耗，只置PowerUp;
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void fnPowerDown_Check(void)
{
    u8 step1_ch, step2_ch;
    static u8 FUrmLowChkCnt = 0;

    #if(POWERCHACK == CHECKLVD)
    step1_ch = LVD_CH;
    step2_ch = LVD_CH;
    #endif

    #if(POWERCHACK == CHECKCMP1)
    step1_ch = CMP1_CH;
    step2_ch = CMP1_CH;
    #endif

    #if(POWERCHACK == CHECKCMP2)
    step1_ch = CMP2_CH;
    step2_ch = CMP2_CH;
    #endif

    #if(POWERCHACK == CHECKLVD_CMP1)
    step1_ch = LVD_CH;
    step2_ch = CMP1_CH;
    #endif

    #if(POWERCHACK == CHECKLVD_CMP2)
    step1_ch = LVD_CH;
    step2_ch = CMP2_CH;
    #endif

    if ((Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN) || (Rn8xxx_LvdCmp_STAT(step2_ch, 3) == ERROR))
    {
        if ((Rn8xxx_LvdCmp_STAT(step1_ch, 2500) == ERROR) ||
            (Rn8xxx_LvdCmp_STAT(step2_ch, 2500) == ERROR))
        {
            Bkgrd.PubData.Active = BKGRD_ACTIVE_POWDN;
            Inactive.PubData.InactiveStamp = BKGRD_INACTIVE_LOWPOWER;
        }
        else
        {
            Inactive.PubData.InactiveStamp = BKGRD_INACTIVE_NOACTION;
            Bkgrd.PubData.Active = BKGRD_ACTIVE_POWON;
        }
    }

    if (Bkgrd.PubData.FUrmsRdFlg == 0xDA) // dyf 改, (0x5A | 0x80)
    {
        //三相基波电压有效值掉电检测
        if (((MeasureRms.PubData.HUrms[0][0] < PwnVoltPer60Un) && (MeasureRms.PubData.HUrms[1][0] < PwnVoltPer60Un)
             && (MeasureRms.PubData.HUrms[2][0] < PwnVoltPer60Un)) && (FUrmLowChkCnt < 255))
        {
            FUrmLowChkCnt++;
        }
        else
        {
            FUrmLowChkCnt = 0;
        }

        Bkgrd.PubData.FUrmsRdFlg &= 0x7F;   // dyf
    }

    //管理模组掉电信号输出
    if ((FUrmLowChkCnt >= 3) || (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN))
    {
        Rn8xxx_GPIO_CfgFun(PinManageModuleLVDOUT, _NORMALIO);
        Rn8xxx_GPIO_CfgIOMode(PinManageModuleLVDOUT, GPIO_MODE_OUT, NORMAL_OUT);
        Rn8xxx_GPIO_CfgPullMode(PinManageModuleLVDOUT, Pull_OFF);
        PinWrite_ManageModuleLVDOUT(0); // dyf test
    }
    else
    {
        PinWrite_ManageModuleLVDOUT(1);
        Rn8xxx_GPIO_CfgFun(PinManageModuleLVDOUT, _NORMALIO);
        //Rn8xxx_GPIO_CfgIOMode(PinManageModuleLVDOUT, GPIO_MODE_OUT, NORMAL_OUT);  // dyf add
        Rn8xxx_GPIO_CfgIOMode(PinManageModuleLVDOUT, GPIO_MODE_NORMAL, NORMAL_IN); // dyf test del
        Rn8xxx_GPIO_CfgPullMode(PinManageModuleLVDOUT, Pull_OFF);
    }
}

/*********************************************************************************************************
** Function name:
** Descriptions:        lqs:20210323, 上电电源检测程序
**                      1、检测到LVD\CMP都满足时，从函数体中出去。
**                      2、该函数仅用于，第1次上电和低功耗状态下的上电检测
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
#define CHECKUPTIME  150//  100is 200ms//150is 300ms
void fnPowerUp_Check(void)
{
    u8 step1_ch, step2_ch;

    #if(POWERCHACK == CHECKLVD)
    step1_ch = LVD_CH;
    step2_ch = LVD_CH;
    #endif

    #if(POWERCHACK == CHECKCMP1)
    step1_ch = CMP1_CH;
    step2_ch = CMP1_CH;
    #endif

    #if(POWERCHACK == CHECKCMP2)
    step1_ch = CMP2_CH;
    step2_ch = CMP2_CH;
    #endif

    #if(POWERCHACK == CHECKLVD_CMP1)
    step1_ch = LVD_CH;
    step2_ch = CMP1_CH;
    #endif

    #if(POWERCHACK == CHECKLVD_CMP2)
    step1_ch = LVD_CH;
    step2_ch = CMP2_CH;
    #endif
    #if 0
    if (Rn8xxx_LvdCmp_STAT(step2_ch, 3) == SUCCESS)
    {
        SystemDelayUs(1); //等待稳定
        if ((Rn8xxx_LvdCmp_STAT(step1_ch, 2500) == SUCCESS) &&
            (Rn8xxx_LvdCmp_STAT(step2_ch, 2500) == SUCCESS))
        {
            Inactive.PubData.InactiveStamp = BKGRD_INACTIVE_POWERONINIT;

            Bkgrd.PubData.Active = BKGRD_ACTIVE_POWON;
        }
    }
    #else

    if (Rn8xxx_LvdCmp_STATPowerUp(step2_ch, 3) == ERROR)
    {
        fnWDT_Restart();
        SystemDelayUs(1); //等待稳定
        if ((Rn8xxx_LvdCmp_STATPowerUp(step1_ch, 5) == ERROR) &&
            (Rn8xxx_LvdCmp_STATPowerUp(step2_ch, CHECKUPTIME) == ERROR))
        {
            Inactive.PubData.InactiveStamp = BKGRD_INACTIVE_POWERONINIT;

            Bkgrd.PubData.Active = BKGRD_ACTIVE_POWON;
        }
        else
        {
        }
    }
    #endif
}

/*****************************************************************************
** Function name:fnPowerUp_CHKDateTime
**
** Description:上电后检查时间合法性
**
** Parameters:None
**
** Returned value:TURE:时间合法;FALSE:时钟错误
**
******************************************************************************/
UCHAR fnPowerUp_CHKDateTime(void)
{
    sDate_time_s_TypeDef   PowDn_Datetimes;

    u16 temp1, temp2;

    fnFile_Read(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_PowDnTime, (u8 *)&PowDn_Datetimes, sizeof(sDate_time_s_TypeDef));

    if (fnCheck_Date_time_s(&PowDn_Datetimes) == ERROR)
    {
        if (fnCheck_Date_time_s(&SysDatetimes) == ERROR)
        {
            Std_Memset((u8 *)&PowDn_Datetimes, 0x00, sizeof(sDate_time_s_TypeDef));
            PowDn_Datetimes.year = 2022;
            PowDn_Datetimes.month = 1;
            PowDn_Datetimes.day = 1;
        }
        else
        {
            Std_Memcpy((u8 *)&PowDn_Datetimes, (u8 *)&SysDatetimes, sizeof(sDate_time_s_TypeDef));
        }

        fnFile_Write(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_PowDnTime, (u8 *)&PowDn_Datetimes, sizeof(sDate_time_s_TypeDef));
    }

    if ((fnCheck_Date_time_s(&SysDatetimes) == ERROR) ||   //时间格式非法
        (fnDFCompData((u8 *)&PowDn_Datetimes, (u8 *)&SysDatetimes, sizeof(sDate_time_s_TypeDef)) == 1))     //时间倒退
    {
        fnSetCurrTime(&PowDn_Datetimes);
        return FALSE;
    }

    temp1 = fnDayCount(&PowDn_Datetimes);
    temp2 = fnDayCount(&SysDatetimes);

    if (temp2 > (temp1 + 1000)) //上电时刻大于掉电时间1000天
    {
        fnSetCurrTime(&PowDn_Datetimes);
        return FALSE;
    }

    return TRUE;
}

/*****************************************************************************
** Function name:fnPowerUp_Freeze_Event
**
** Description:掉电后根据掉点时间补充停电期间的需量、日冻结、结算日数据
**
** Parameters:None
**
** Returned value:None
**
******************************************************************************/
void fnPowerUp_Freeze_Event(void)
{
    sDate_time_s_TypeDef   PowDn_Datetimes ;

    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }

    fnEnergy_CRCCheck();
    if (fnPowerUp_CHKDateTime() == FALSE)
    {
        //      fnEvent_Operation(FileItemInfoNum_Evt_ClockErr , EVTSTART, NULL);
        Bkgrd.PubData.MtSysSta.SysStaBit.ClockErr = 1;
    }

    fnSysDateTimes(&SysDatetimes);  //读取当前时间

    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_EvtSumTime, (u8 *)&Event.EvtSumTime[0], FileItemInfoLen_HighState_EvtSumTime);

    //-------上电补冻结数据-------------------
    fnFreeze_MakeUp();

    //------失压，失流，断相，电压不平衡/电源异常等未结束事件记录----------------------
    fnSavePowerOnEvtStop();

    //--------补掉电发生事件记录--------------------
    fnFile_Read(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_PowDnTime, (u8 *)&PowDn_Datetimes, sizeof(sDate_time_s_TypeDef));
    if (fnCheck_Date_time_s(&PowDn_Datetimes) == SUCCESS)
    {
        fnFile_Read(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_PowerUpTime, &EvtRptData.PowerUpTime, 1);
        fnWrite_PownDownEvtToFlash();
    }

    fnSysDateTimes(&SysDatetimes);  //时间恢复

    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_EvStatus, (u8 *)&EvStatusInter, sizeof(sEvStatusInter_TypeDef));    //回写状态

    //  // 掉电结束
    //  fnEvent_Operation(FileItemInfoNum_Evt_PowDn , EVTEND, NULL);
}

//-------------------------
//-------------------------
//-------------------------
void fnPowerUp_CheckUpCoverSta(void)
{
    RTC->VBAT_IOWEN = 0xb0;//P44 按键检测模式:记录最早两次开盖
    RTC->VBAT_IOMODE = 0x0e;//清零RTC->P44寄存器组
    fnRTCDrive_Delay();
    RTC->VBAT_IOMODE = 0x0a0;//清零RTC->P44寄存器组
    RTC->VBAT_IOWEN = 0x00;
}

void fnPowerUp_RTCParaInit(void)
{
    uRTCCurvePara RTCCurvePara;
    memset((u8*)&RTCCurvePara, 0x00, sizeof(RTCCurvePara));

    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef)); /*"tocheck" dyf 日计时校准 240926 */
    fnBkgrd__RTCParaCheck();
    Rn8xxx_RTC_CtlInit(RTC_TSE_AutoMode, RTC_TCP_2Sec, RTC_FOUT_1HZ);
    //Rn8xxx_LvdCmpSar_Mode(SAR_HighMode);
    //RTCPara.CurveMode = RTC_CurveMode_2;  //debug
    if (RTC_CurveMode_4 == RTCPara.CurveMode)
    {
        RTCCurvePara.Curve4Para.DATA0 = RTCPara.DATA0;
        RTCCurvePara.Curve4Para.XT1 = RTCPara.XT1;
        RTCCurvePara.Curve4Para.ALPHA = RTCPara.ALPHA;
        RTCCurvePara.Curve4Para.BETA = RTCPara.BETA;
        RTCCurvePara.Curve4Para.GAMMA = RTCPara.GAMMA;
        RTCCurvePara.Curve4Para.ZETA = 0;
        Rn8xxx_RTC_CurveModeInit(RTC_CurveMode_4, RTCCurvePara, CurveParaSet);
    }
    else
    {
        RTCCurvePara.Curve2Para.DATA0 = RTCPara.RTCDota0;
        Rn8xxx_RTC_CurveModeInit(RTC_CurveMode_2, RTCCurvePara, CurveParaDef);
    }
}

void fnPowerUp_Init(void)
{
    sDate_time_s_TypeDef    PowDnTime;
    u32     Temp;

    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }

    Std_Memset(&Bkgrd, 0, sizeof(sBkgrd_TypeDef));
    fnBufTemp_Init();
    SysStamp = 0;

    fnFile_Read(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_PowDnTime, &PowDnTime, sizeof(sDate_time_s_TypeDef));

    Bkgrd.PriData.Second = SysDatetimes.second;
    Bkgrd.PriData.Minute = SysDatetimes.minute;
    Bkgrd.PriData.Hour = SysDatetimes.hour;
    Bkgrd.PriData.Day = SysDatetimes.day;
    Bkgrd.PriData.Month = SysDatetimes.month;

    Bkgrd.PubData.Second = SysDatetimes.second;
    if (fnDFCompData((u8 *)&SysDatetimes.day, (u8 *)&PowDnTime.day, 4)) //天发生变化
    {
        //fnBkgrd_Day_Exec();
        Bkgrd.PubData.UpDateTimeFlag |= BKGRD_FCHANGE_DAY;
    }

    Bkgrd.PriData.Fl = Bkgrd.PubData.Fl;
    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_WireMode, &Bkgrd.PriPara.WireMode, 1);
    fnCrc_Check(0, (u8 *)&Bkgrd.PriPara, sizeof(Bkgrd.PriPara) - 2, (u8 *)&Bkgrd.PriPara.Crc);

    //如果时间非法,则不累计电池工作时间
    if ((fnCheck_Date_time_s(&PowDnTime) == SUCCESS) && (fnCheck_Date_time_s(&SysDatetimes) == SUCCESS))
    {
        //-------读取E2电池累计时间------------------
        fnFile_Read(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_tWorkBat, &Bkgrd.PubData.tWorkBat, 4);

        fnBkgrd_ClockBatCalculate();        // dyf 判断时钟电池电压之前，先读取当前的时钟电池电压
        if (Bkgrd.PubData.ClockBat > 280)   // dyf 增加时钟电池电压检查，防止未插时钟电池时也累计时间
        {
            Temp = fnDateTimeToMin(&SysDatetimes) - fnDateTimeToMin(&PowDnTime);
            Bkgrd.PubData.tWorkBat += Temp;
            fnFile_Write(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_tWorkBat, &Bkgrd.PubData.tWorkBat, 4);
        }
    }

    #if(METERTYPE)
    if (Bkgrd.PubData.MoneySta.RemoteKeepEg)
    {
        Bkgrd.PubData.MtSta.MtSta3.StaBit.KeepEg = 1;
    }
    else
    {
        Bkgrd.PubData.MtSta.MtSta3.StaBit.KeepEg = 0;
    }

    Bkgrd.PubData.ZBRSTFlag = 0x5a;
    Bkgrd.PubData.UpRunFileFlag = 0x5a;  //上电后同步表号等ESAM信息

    #endif
    Bkgrd.PubData.tEmuRstDely = 3;
    Bkgrd.PubData.tMngPlug = EvtMngDelay;

    fnFile_Read(FileId_TemperSchoolPara, 0, (u8 *)&gTemperSchoolParaMem, FileLen_TemperSchoolPara);

    #if (HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_JI_LIANG_XIN)
    fnBsp_Tmp_Init(); // dyf 电碳表没有端子测温
    #endif

    return;
}

/*********************************************************************************************************
** Function name:        fnPowerUp_AppInit
** Descriptions:         上电处理程序
** input parameters:     无
** output parameters:    无
** Returned value:       无
*********************************************************************************************************/
void fnPowerUp_AppInit(void)
{
    __disable_irq();
    fnTarget_Init();

    fnPowerDown_Check();  //中断未打开前通过查询方式判断是否掉电，避免操作时间过长
    fnSysDateTimes(&SysDatetimes);
    Rn8xxx_Lcd_Close();

    fnWDT_Restart();
    fnMeasure_Init();

    fnWDT_Restart();

    //  fnFile_Init(File_FirstInit); //视情况开放或增加判断条件

    fnEnergy_CRCCheck();
    fnWDT_Restart();

    fnPowerUp_CheckUpCoverSta();

    fnPowerDown_Check();

    fnEsamOp_EsamInit();

    fnDl698_Init();
    fnWDT_Restart();
    fnPowerUp_Init();

    fnPowerDown_Check();
    __enable_irq();   //通讯初始化后打开中断

    fnWDT_Restart();

    fnWDT_Restart();
    fnSecret_Init();
    fnOutput_Init();

    fnWDT_Restart();

    fnPowerUp_RTCParaInit();

    fnKey_Init();
    fnEvent_Init();

    fnEvtCoverTail_PowerOn();
    fnPowerUp_Freeze_Event(); // dyf 测试时可以屏蔽

    fnMeasure_WaveInit();
}

/*****************************************************************************
** Function name:fnPowerDown_SetWakeOpIO
**
** Description:对上电唤醒后需操作的IO进行设置，如SPI，I2C
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnPowerDown_SetWakeOpIO(void)
{
    BSP_FlashSpi_Init();
    fnFm24c256_Init();
}

/*****************************************************************************
** Function name:fnPowerDown_SleepWakeOpIO
**
** Description:关闭上电唤醒后设置的IO ， 如SPI I2C等
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnPowerDown_SleepWakeOpIO(void)
{
    EEprom_Stop();
    BSP_FlashSpi_Stop();
}

/*****************************************************************************
** Function name:   fnPowerDown_IOSetSleep
**
** Description:     CPU进入休眠前对IO口进行配置，达到最低功耗
**
** Parameters:      None
**
** Returned value:  None
**
******************************************************************************/
void fnPowerDown_IOSetSleep(void)
{
    if (Bkgrd.PubData.Active != BKGRD_ACTIVE_POWDN)
    {
        return;
    }

    Inactive.PubData.IrWakeupFlag = 0;

    fnWDT_Restart();

    //////////////////关闭中断使能/////////////////////
    NVIC_DisableIRQ(SYSCLKCAL_IRQn);
    NVIC_DisableIRQ(CMP_IRQn);
    NVIC_DisableIRQ(RTC_IRQn);
    NVIC_DisableIRQ(D2F_IRQn);
    NVIC_DisableIRQ(MADC_IRQn);
    NVIC_DisableIRQ(UART0_IRQn);
    NVIC_DisableIRQ(UART1_IRQn);
    NVIC_DisableIRQ(UART2_IRQn);
    NVIC_DisableIRQ(UART3_IRQn);
    NVIC_DisableIRQ(SPI_IRQn);
    NVIC_DisableIRQ(I2C_IRQn);
    NVIC_DisableIRQ(ISO78160_SPI3_IRQn);
    NVIC_DisableIRQ(ISO78161_SPI2_IRQn);
    NVIC_DisableIRQ(TC0_IRQn);
    NVIC_DisableIRQ(TC1_IRQn);
    NVIC_DisableIRQ(UART4_IRQn);
    NVIC_DisableIRQ(UART5_IRQn);
    NVIC_DisableIRQ(WDT_IRQn);
    NVIC_DisableIRQ(KBI_IRQn);
    NVIC_DisableIRQ(LCD_DSP_IRQn);
    NVIC_DisableIRQ(SPI1_IRQn);
    NVIC_DisableIRQ(EXT0_IRQn);
    NVIC_DisableIRQ(EXT1_IRQn);
    NVIC_DisableIRQ(EXT2_IRQn);
    NVIC_DisableIRQ(EXT3_IRQn);
    NVIC_DisableIRQ(EXT4_IRQn);
    NVIC_DisableIRQ(EXT5_IRQn);
    NVIC_DisableIRQ(EXT6_IRQn);
    NVIC_DisableIRQ(EXT7_IRQn);

    //////////////////关闭外围电源供电/////////////////////
    EsamPowerOff();
    FLASH_PowerOff();
    RN8302_PowerOff();

    Rn8xxx_GPIO_CfgFun(PinKBTMBOX, _KEY);
    Rn8xxx_GPIO_CfgIOMode(PinKBTMBOX, GPIO_MODE_IN, NORMAL_IN);

    //////////////////配置GPIO功能///////////////////////
    Rn8xxx_GPIO_CfgPullMode(PinISP, Pull_OFF);

    Rn8xxx_GPIO_CfgFun(PinAD_3V6, _NORMALIO);   //时钟电池电压
    Rn8xxx_GPIO_CfgIOMode(PinAD_3V6, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinAD_3V6, Pull_OFF);

    Rn8xxx_GPIO_CfgFun(PinLVD, _AIN);   //系统电源检测
    //Rn8xxx_GPIO_CfgFun(PinKCOVER,_KEY);   //开上盖检测
    Rn8xxx_GPIO_CfgFun(PinKCOVER, _INTRUPT); //开上盖检测
    Rn8xxx_GPIO_CfgIOMode(PinKCOVER, GPIO_MODE_IN, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinClkOut, _NORMALIO);   //RTC时钟脉冲输出管脚
    Rn8xxx_GPIO_CfgIOMode(PinClkOut, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinClkOut, Pull_OFF);

    ////ESAM
    Rn8xxx_GPIO_CfgFun(PinEsamClk, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinEsamClk, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinEsamClk, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinEASMMISO, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinEASMMISO, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinEASMMISO, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinEASMMOSI, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinEASMMOSI, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinEASMMOSI, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinEASMCS, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinEASMCS, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinEASMCS, Pull_OFF);

    ////UART
    Rn8xxx_GPIO_CfgFun(PinRXD485, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinRXD485, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinRXD485, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinTXD485, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinTXD485, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinTXD485, Pull_OFF);

    ////计量模块相关
    Rn8xxx_GPIO_CfgFun(PinSCS_C, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinSCS_C, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinSCS_C, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinSCLK, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinSCLK, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinSCLK, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinSDO_C, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinSDO_C, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinSDO_C, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinSDI_C, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinSDI_C, GPIO_MODE_NORMAL, NORMAL_IN);
    //Rn8xxx_GPIO_CfgPullMode(PinSDI_C , Pull_OFF);
    Rn8xxx_GPIO_CfgPullMode(PinSDI_C, Pull_ON); // dyf 需要关闭内部默认的上拉电阻，否则导致掉电后功耗比较高；Pull_ON 对应关闭上拉，与其他引脚设置不同
    Rn8xxx_GPIO_CfgFun(PinRN8302_PF, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinRN8302_PF, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinRN8302_PF, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinRN8302_QF, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinRN8302_QF, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinRN8302_QF, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinINTN1_C, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinINTN1_C, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinINTN1_C, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(Pin_PF, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(Pin_PF, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(Pin_PF, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(Pin_QF, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(Pin_QF, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(Pin_QF, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(Pin_PtHPF, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(Pin_PtHPF, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(Pin_PtHPF, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(Pin_NtHPF, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(Pin_NtHPF, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(Pin_NtHPF, Pull_OFF);

    // HSDC-SPI
    Rn8xxx_GPIO_CfgFun(PinHSCS_C, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinHSCS_C, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinHSCS_C, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinHSCLK_C, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinHSCLK_C, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinHSCLK_C, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinHMOSI_C, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinHMOSI_C, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinHMOSI_C, Pull_OFF);

    ////存储相关
    Rn8xxx_GPIO_CfgFun(PinFlashCLK, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinFlashCLK, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinFlashCLK, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinFlashMISO, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinFlashMISO, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinFlashMISO, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinFlashMOSI, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinFlashMOSI, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinFlashMOSI, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinFlashCS, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinFlashCS, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinFlashCS, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinEepromSCL, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinEepromSCL, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinEepromSCL, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinEepromSDA, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinEepromSDA, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinEepromSDA, Pull_OFF);

    ////扩展模组相关
    Rn8xxx_GPIO_CfgFun(PinExModuleClk, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinExModuleClk, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinExModuleClk, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinExModuleMOSI, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinExModuleMOSI, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinExModuleMOSI, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinExModuleCS, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinExModuleCS, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinExModuleCS, Pull_OFF);

    ////管理模组相关
    Rn8xxx_GPIO_CfgFun(PinManageModuleRSTM, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinManageModuleRSTM, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinManageModuleRSTM, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinManageModuleLVDOUT, _NORMALIO);
    //Rn8xxx_GPIO_CfgIOMode(PinManageModuleLVDOUT, GPIO_MODE_OUT, NORMAL_OUT);    // dyf add
    Rn8xxx_GPIO_CfgIOMode(PinManageModuleLVDOUT, GPIO_MODE_NORMAL, NORMAL_IN); // dyf test del
    Rn8xxx_GPIO_CfgPullMode(PinManageModuleLVDOUT, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinManageModuleCOMRQIN, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinManageModuleCOMRQIN, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinManageModuleCOMRQIN, Pull_OFF);

    Rn8xxx_GPIO_CfgFun(PinManageModuleCS, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinManageModuleCS, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinManageModuleCS, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinManageModuleCLK, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinManageModuleCLK, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinManageModuleCLK, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinManageModuleMISO, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinManageModuleMISO, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinManageModuleMISO, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinManageModuleMOSI, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinManageModuleMOSI, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinManageModuleMOSI, Pull_OFF);

    ////测温芯片相关
    Rn8xxx_GPIO_CfgFun(PinTmpSDA, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinTmpSDA, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinTmpSDA, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinTmpSCL, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinTmpSCL, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinTmpSCL, Pull_OFF);

    //////////////////配置掉电检测功能处理///////////////////////
    #if( (POWERCHACK == CHECKLVD)||(POWERCHACK == CHECKCMP1)||(POWERCHACK == CHECKLVD_CMP1))
    Rn8xxx_CMP_Stop(CMP2_Channel);
    #endif

    #if( (POWERCHACK == CHECKLVD)||(POWERCHACK == CHECKCMP2)||(POWERCHACK == CHECKLVD_CMP2))
    Rn8xxx_CMP_Stop(CMP1_Channel);
    #endif

    #if( (POWERCHACK == CHECKCMP1)||(POWERCHACK == CHECKCMP2) )
    Rn8xxx_LVD_Stop();  //LVD停电开启时功耗增加约4uA
    #endif

    //////////////////关闭外设时钟///////////////////////
    SysCtl_EnableWrite;

    ////SYS_MOD0_EN
    Sys_Tc_Clk_Dis;
    CPC_Clk_Dis;
    TC0_Clk_Dis;
    TC1_Clk_Dis;
    UART4_Clk_Dis;
    UART5_Clk_Dis;
    UART0_Clk_Dis;
    UART1_Clk_Dis;
    UART2_Clk_Dis;
    UART3_Clk_Dis;
    UART38K_Clk_Dis;
    ISO7816_Clk_Dis;
    I2C_Clk_Dis;
    SPI_Clk_Dis(SPI0_ID);
    SPI_Clk_Dis(SPI1_ID);
    SPI_Clk_Dis(SPI2_ID);
    SPI_Clk_Dis(SPI3_ID);

    ////SYS_MOD1_EN
    GPIO_Clk_Dis;
    LCD_Clk_Dis;
    WDT_Clk_En;
    RTC_SAR_Clk_En;
    CMPLVD_Clk_En;
    D2F_Clk_Dis;
    DSP_Clk_Dis;
    M2M_Clk_Dis;

    ////SYS_PD
    LVD_PD_PowDwn;
    CMP1_PD_PowDwn;
    PWD_CMP1R_Dis;
    HYSEN_CMP1_Dis;
    //CMP2_PD_PowDwn;
    //PWD_CMP2R_Dis;
    //HYSEN_CMP2_Dis;

    ////INTC_EN
    Rn8xxx_INTC_Stop(INTC_ID0);
    Rn8xxx_INTC_Stop(INTC_ID1);
    Rn8xxx_INTC_Stop(INTC_ID2);
    Rn8xxx_INTC_Stop(INTC_ID3);
    Rn8xxx_INTC_Stop(INTC_ID4);
    Rn8xxx_INTC_Stop(INTC_ID5);
    Rn8xxx_INTC_Stop(INTC_ID6);
    Rn8xxx_INTC_Stop(INTC_ID7);
    //SYSCTL->INTC_EN = 0x00;
    Rn8xxx_INTC_Init(INTC_ID1, INTC_DoubleEdge, INTC_IRQ_ENABLE);

    ////KBI_EN
    //Rn8xxx_KBI_Init(KBI_ID0,KBI_RisingEdge,KBI_IRQ_ENABLE);

    SysCtl_DisableWrite;

    //使能RTC中断
    RTC->CNT1 = 1;
    RTC->IE = 0x302;
    RTC->IF = 0xff;
    NVIC_EnableIRQ(RTC_IRQn);
    NVIC_EnableIRQ(CMP_IRQn);
    NVIC_EnableIRQ(EXT1_IRQn);
    NVIC_EnableIRQ(KBI_IRQn);
}

void fnPowerDown_SleepSet(void)
{
    fnINTRTC_Sleep();
    fnPowerDown_IOSetSleep();
    SYSCTL->SYS_PS = 0x82;

    RTC->VBAT_IOWEN = 0xb0;//P44 按键检测模式:记录最早两次开盖
    RTC->VBAT_IOMODE = 0x0e;//清零RTC->P44寄存器组
    fnRTCDrive_Delay();
    RTC->VBAT_IOMODE = 0x05;//
}

/*****************************************************************************
** Function name:fnPowerDown_OpenTx_ZB
**
** Description:开启载波通道发送
**
** Parameters:
**
** Returned value:
**
******************************************************************************/
void fnPowerDown_OpenTx_ZB(void)
{
    fnScomPk_Init(SCOM_PORT_ZBCOM);

    SCAP_VCTRL_PowerOn();
}

/*****************************************************************************
** Function name:fnPowerDown_CloseTx_ZB
**
** Description:
**
** Parameters:
**
** Returned value:
**
******************************************************************************/
void fnPowerDown_CloseTx_ZB(void)
{
    NVIC_DisableIRQ(UART3_IRQn);

    Rn8xxx_GPIO_CfgFun(PinSCAP_VCTRL, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinSCAP_VCTRL, GPIO_MODE_NORMAL, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinTXD_ZB, _NORMALIO); /*"载波通道发送脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinTXD_ZB, GPIO_MODE_NORMAL, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinRXD_ZB, _NORMALIO); /*"载波通道接收脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinRXD_ZB, GPIO_MODE_NORMAL, NORMAL_IN);
}

/*****************************************************************************
** Function name:   fnPowerDown_Sleep
**
** Description:     CPU进入休眠
**
** Parameters:      None
**
** Returned value:  None
**
******************************************************************************/
void fnPowerDown_Sleep(void)
{
    //   if(Inactive.PubData.ActiveState==End_State)
    {
        //      Inactive.PubData.InactiveStamp= 0;
        __WFI();
    }
}

/*****************************************************************************
** Function name:   fnPowerDown_BeforeSleep
**
** Description:     休眠前处理程序，检测全失压是否发生
**
** Parameters:      None
**
** Returned value:  None
**
******************************************************************************/
void fnPowerDown_BeforeSleep(void)
{
    if (Bkgrd.PubData.Active != BKGRD_ACTIVE_POWDN)
    {
        return;
    }

    fnWDT_Restart();

    MeasureRegTmp.PCalcFlg = 0;

    EvtRptData.ReportCnt = 0x00;  //上电状态下未发送完的上报，掉电清零
    EvtRptData.tReportDely = 0x00;

    fnFile_Write(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_PowDnTime, (u8 *)&SysDatetimes, sizeof(sDate_time_s_TypeDef));
    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 31, (u8 *)&Secret.Master.tLinkDly[0], 16);

    // 保存管理模组插拔状态
    fnEvtMngPlug_PwdnSave();

    Std_Memset(&Inactive, 0, sizeof(sInactive_TypeDef));

    Inactive.PubData.BackupBat = Bkgrd.PubData.BackupBat;

    fnEnergy_PownDownWriteToE2();

    fnWDT_Restart();
    fnWrite_PownDownEvtToE2();

    //进入休眠后，重新刷新状态字
    Bkgrd.PubData.MtSta.MtSta1.Sta = 0;
    Bkgrd.PubData.MtSta.MtSta2.Sta = 0;
    Bkgrd.PubData.MtSta.MtSta3.Sta = 0;
    Bkgrd.PubData.MtSta.MtSta4.Sta = 0;
    Bkgrd.PubData.MtSta.MtSta5.Sta = 0;
    Bkgrd.PubData.MtSta.MtSta6.Sta = 0;
    Bkgrd.PubData.MtSta.MtSta7.Sta = 0;

    //Std_Memset(&Demand.PubData , 0 , sizeof(Demand.PubData) );
    Inactive.PubData.PowerErrFlag = 0x5a;

    fnSysDateTimes(&SysDatetimes);
}

/*****************************************************************************
** Function name:fnPowerDown_CalcSleepTime
**
** Description:计算停电分钟数,将值存在Dl645Inactive.PubData.PowerDnTimer中
**             用于判断是否进行红外抄表
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnPowerDown_CalcSleepTime(void)
{
    sDate_time_s_TypeDef    PowDnTime;
    // 计算停电时间，决定是否打开红外通讯
    fnFile_Read(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_PowDnTime, &PowDnTime, sizeof(sDate_time_s_TypeDef));

    Inactive.PubData.PowerDnTimer = fnDateTimeToMin(&SysDatetimes) - fnDateTimeToMin(&PowDnTime);
}

/*****************************************************************************
** Function name:   fnPowerDown_Main
**
** Description:     低电压检测主程序，对主电进行监测
**
** Parameters:      None
**
** Returned value:  None
**
******************************************************************************/
// void fnPowerDown_Main(void)
//     __attribute__ ((section (".ARM.__at_0x60000")));  //384KB
void fnPowerDown_Main(void)
{
    __enable_irq();
    fnWDT_Restart();

    while (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        fnWDT_Restart();

        fnPowerDown_Sleep();
        fnWDT_Restart();

        if (Inactive.InactiveFlag.fChange & 0x02) // 秒进位
        {
            Inactive.InactiveFlag.fChange &= 0xfd;

            if (Inactive.PubData.tCheckSysConf < 1800)
            {
                Inactive.PubData.tCheckSysConf++;
            }
            else
            {
                Inactive.PubData.tCheckSysConf = 0;
                SysConfCheck();
            }

            // 停电5s记录电压电流数据
            Inactive.PubData.QLossVolTime++;
            if (Inactive.PubData.QLossVolTime >= 3)
            {
                if (Inactive.PubData.QLossVolTime == 3)
                {
                    fnEvtVoltLoss_PowerDwn();
                }

                Inactive.PubData.QLossVolTime = 4;
            }
        }

        // 掉电开盖记录
        fnEvtCoverTail_PwDn();

        fnPowerUp_Check();
        //------或直接复位MCU-------------
        if (Inactive.PubData.InactiveStamp == BKGRD_INACTIVE_POWERONINIT)
        {
            //---上电初始化-----------
            fnWDT_Restart();

            //------上电恢复数据后置上电模式---------------
            Bkgrd.PubData.Active = BKGRD_ACTIVE_POWON;

            fnPowerOn_DrvieInit();
            fnPowerUp_AppInit();

            Inactive.PubData.InactiveStamp = BKGRD_INACTIVE_NOACTION;   //上下电事件处理
            return;
        }
    }
    return;
}

/*********************************************************************************************************
** Function name:        fnPowerDown_Handle
** Descriptions:         掉电前处理程序
** input parameters:     无
** output parameters:    无
** Returned value:       无
*********************************************************************************************************/
void fnPowerDown_Handle(void)
{
    uRTCCurvePara RTCCurvePara;
    memset((u8*)&RTCCurvePara, 0x00, sizeof(RTCCurvePara));
    __disable_irq();
    fnWDT_Restart();

    fnBkgrd__RTCParaCheck();
    //fnFile_Read(FileId_HighPara,FileItemInfoOffAddr_HighPara_RTCDota0,(u8 *)&RTCPara.RTCDota0,sizeof(sRTCParaE2_TypeDef));/*"tocheck"*/
    Rn8xxx_RTC_CtlInit(RTC_TSE_AutoMode, RTC_TCP_1Min, RTC_FOUT_Disable);
    //Rn8xxx_LvdCmpSar_Mode(SAR_NormalMode);
    if (RTC_CurveMode_4 == RTCPara.CurveMode)
    {
        RTCCurvePara.Curve4Para.DATA0 = RTCPara.DATA0;
        RTCCurvePara.Curve4Para.XT1 = RTCPara.XT1;
        RTCCurvePara.Curve4Para.ALPHA = RTCPara.ALPHA;
        RTCCurvePara.Curve4Para.BETA = RTCPara.BETA;
        RTCCurvePara.Curve4Para.GAMMA = RTCPara.GAMMA;
        RTCCurvePara.Curve4Para.ZETA = 0;
        Rn8xxx_RTC_CurveModeInit(RTC_CurveMode_4, RTCCurvePara, CurveParaSet);
    }
    else
    {
        RTCCurvePara.Curve2Para.DATA0 = RTCPara.RTCDota0;
        Rn8xxx_RTC_CurveModeInit(RTC_CurveMode_2, RTCCurvePara, CurveParaDef);
    }

    fnPowerDown_SleepSet();

    Inactive.PubData.ActiveState = End_State;
    Inactive.PubData.ActiveInit = 0;
    Inactive.InactiveFlag.fChange = 0x00;
    Inactive.PubData.tCheckSysConf = 0x00;
    Inactive.PubData.PowerDnTimer = 0;

    fnSubClock_Init();

    __enable_irq();

    fnPowerDown_Main();
}

/*********************************************************************************************************
** Function name:       fnPowerDown_Inactive
** Descriptions:
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void fnPowerDown_Inactive(void)
{
    fnWDT_Restart();
    fnPowerDown_Check();  //掉电检测

    if (Inactive.PubData.InactiveStamp  == BKGRD_INACTIVE_LOWPOWER)
    {
        __disable_irq();
        fnPowerDown_BeforeSleep();
        __enable_irq();
        fnPowerDown_Handle();
        Inactive.PubData.InactiveStamp = BKGRD_INACTIVE_NOACTION;
    }
}
