
#define  _BKGRD_GLOBALS
#include <Includes.h>

//函数功能：时钟温度电池计算
//入口参数：无
//出口参数：无
void fnBkgrd_ClockBatCalculate(void)
{
    u32 ClockBat;

    #if(nPhs==ThreePhs)
    ClockBat = Rn8xxx_SarADC_Get(AIN0_Channel, PGA_0p5);
    if (ClockBat != 0)  // dyf 增加容错处理，防止读取的时钟电池电压跳变成0
    {
        ClockBat = (ClockBat * 500) / 1024 + 20; // 参考在1.25V，1/2分压//2*((2.2+2.2)/2.2)*1.25*100=829.5=830;20:二极管压降0.2V
        if (ClockBat < 90)
        {
            ClockBat = 0;
        }
        Bkgrd.PubData.ClockBat = (u16)(ClockBat);   //时钟电池电压 U16
    }

    ClockBat = Rn8xxx_SarADC_Get(AIN2_Channel, PGA_0p5);
    if (ClockBat != 0)  // dyf 增加容错处理，防止读取的电压跳变成0
    {
        ClockBat = (ClockBat * 830) / 1024 + 30; //2*((5.1+2.2)/2.2)*1.25*100=829.5=830;30:二极管压降=0.3V
        Bkgrd.PubData.BackupBat = (u16)(ClockBat);
    }
    #else
    ClockBat = Rn8xxx_SarADC_Get(AIN0_Channel, PGA_0p5);
    ClockBat = (ClockBat * 500) / 1024 + 20; // 参考在1.25V，1/2分压//2*((2.2+2.2)/2.2)*1.25*100=829.5=830;20:二极管压降0.2V
    Bkgrd.PubData.ClockBat = (u16)(ClockBat);   //时钟电池电压 U16
    #endif
    #if 0
    // 当前温度值
    ClockBat = RTC->TEMP;
    ClockBat &= 0x3ff;
    if (ClockBat & 0x200)
    {
        ClockBat = 0x3ff - ClockBat;
        Bkgrd.PubData.Temperature = (u16)((ClockBat * 10) / 4) | 0x8000;
    }
    else
    {
        Bkgrd.PubData.Temperature = (u16)((ClockBat * 10) / 4);
    }
    #else
    Bkgrd.PubData.Temperature2 = Rn8xxx_RTC_TempGet();

    Bkgrd.PubData.Temperature = (s16)(Bkgrd.PubData.Temperature2 / 100);

    #endif
}

void fnBkgrd__RTCParaCheck(void)
{
    u8 i;

    for (i = 0; i < 3; i++)
    {
        if (fnCrc_Check(1, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef) - 2, (u8 *)&RTCPara.Crc) == 1)     //-效验错误---
        {
            fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef));
            if (fnCrc_Check(1, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef) - 2, (u8 *)&RTCPara.Crc) == 0)    //--效验正确时退出-------
            {
                break;
            }
        }
        else
        {
            break;/*"正确时直接退出"*/
        }
    }

    if ((i == 3) || ((RTCPara.CurveMode != RTC_CurveMode_2) && (RTCPara.CurveMode != RTC_CurveMode_4)))
    {
        Std_Memset((u8 *)&RTCPara.RTCDota0, 0x00, sizeof(sRTCParaE2_TypeDef));
        RTCPara.CurveMode = RTC_CurveMode_2;  //-----参数恢复默认值----------
    }
}

/*****************************************************************************
** Function name:fnBkgrd_TemperIAGain
**
** Description:对RTC进行高低温补偿
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnBkgrd_TemperIAGain(void)
{
    #if 0
    u16 Temper, TempData;
    s8  RTCAdj[3];
    float ADErr;
    s8  RtcDota0 = 0;

    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCAdj, &RTCAdj[0], 3);
    //以下为RTC 校正温度影响
    Temper = RTC->TEMP;
    if (Temper & 0x200)
    {
        Temper = ((0x3ff - Temper) * 10) / 4;
        RtcDota0 = RTCAdj[1] * 8;

        while (Temper > 270)
        {
            RtcDota0 += RTCAdj[0];
            RtcDota0 += RTCAdj[1];
            Temper = Temper - 20;
        }

        while (Temper > 20)
        {
            RtcDota0 += RTCAdj[1];
            Temper = Temper - 20;
        }
    }
    else
    {
        Temper = (Temper * 10) / 4;
        if (Temper < 150)
        {
            while (Temper < 150)
            {
                RtcDota0 += RTCAdj[1];
                Temper = Temper + 20;
            }
        }
        else if (Temper > 350)
        {
            while (Temper > 350)
            {
                RtcDota0 += RTCAdj[2];
                Temper = Temper - 20;
            }
        }
    }

    if (RtcDota0 != 0)
    {
        fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&Temper, 2);
        if (Temper > 4095)      // 补偿值为负
        {
            ADErr = -(0x1fff - Temper + 1) - (RtcDota0 * 32) / 10 ;
            if (ADErr < 0)
            {
                Temper = (u16)(0x1fff + ADErr);
            }
            else
            {
                Temper = (u16)ADErr;
            }
        }
        else
        {
            ADErr = Temper - (RtcDota0 * 32) / 10 ;
            if (ADErr < 0)
            {
                Temper = (u16)(0x1fff + ADErr);
            }
            else
            {
                Temper = (u16)ADErr;
            }
        }
        TempData = RtcReadDota();
        if (TempData != Temper)
        {
            RtcWriteDota(Temper);
            RTCPara.RTCDota0 = Temper;
        }
    }
    else
    {
        fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&Temper, 2);
        TempData = RtcReadDota();
        if (TempData != Temper)
        {
            RtcWriteDota(Temper);
            RTCPara.RTCDota0 = Temper;
        }
    }
    #else
    /*"每秒进行一次校验和TRIM"*/
    // fnFile_Read(FileId_HighPara,FileItemInfoOffAddr_HighPara_RTCDota0,(u8 *)&RTCPara.RTCDota0,sizeof(sRTCParaE2_TypeDef));/*"tocheck"*/
    fnBkgrd__RTCParaCheck();
    if (RTC_CurveMode_4 == RTCPara.CurveMode)
    {
        RtcWriteDota(RTCPara.DATA0);
    }
    else
    {
        RtcWriteDota(RTCPara.RTCDota0);
    }
    #endif
}

/*****************************************************************************
** Function name:fnBkgrd_Tnal_Tmper
**
** Description:端子测温
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnBkgrd_Tnal_Tmper(void)
{
    fnBsp_CT7538_read_temp(MAX_TERMINAL_TMP_NUM, &Bkgrd.PubData.Tnal_Tmper[0]);
}

/*****************************************************************************
** Function name:   fnBkgrd_Second_Exec
**
** Description:     秒进位处理程序
**
** Parameters:      NONE
**
** Returned value:  NONE
**
******************************************************************************/
void fnBkgrd_Second_Exec(void)
{
    fnBkgrd_TemperIAGain();
    fnBkgrd_ClockBatCalculate();
    #if (HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_JI_LIANG_XIN)
    fnBkgrd_Tnal_Tmper();   //端子温度测量 dyf 电碳表没有端子测温
    #endif

    fnEvent_SumTime();

    //
    if (Bkgrd.PubData.tEmuRstDely)
    {
        Bkgrd.PubData.tEmuRstDely--;
    }

    if (Bkgrd.PubData.tMngPlug)
    {
        Bkgrd.PubData.tMngPlug--;
    }

    if (Bkgrd.PubData.FrzWink_Delay)
    {
        Bkgrd.PubData.FrzWink_Delay--;
        if (Bkgrd.PubData.FrzWink_Delay == 0)
        {
            Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_WINKFRZ;
        }
    }

    fnCHK_LinkDly();
    fnCHK_ESAMDly();

    if (EvtRptData.tReportDely)
    {
        EvtRptData.tReportDely--;
    }

    fnMeasureAverage_PowerCalc();  //计算1分钟平均有功功率

    //EvtRptData.PowerUpTime = 61; //debug

    //fnDemand_PulseCalc();  //debug
}

void fnBkgrd_Minute_Exec(void)
{
    if (Energy.PubPara.fMinute)
    {
        Energy.PubPara.fMinute--;
    }

    //  if(Bkgrd.PubData.ClockBat > 280)
    //      Bkgrd.PubData.tWorkBat++;
    //-------分钟冻结判断-------------
    if (SysDatetimes.second < 3)
    {
        fnJudgeTime_FrzMin();
    }

    if (EvtRptData.PowerUpTime < 0xFF)
    {
        EvtRptData.PowerUpTime++;
    }
}

void fnBkgrd_Hour_Exec(void)
{
    return;
}

void fnBkgrd_Day_Exec(void)
{
    u8  TemHex_Day ;
    //u32 OffAddr;
    //u16   Cycle;
    sBroatStatue_TypeDef  broadsta;

    broadsta.Already = 0;
    broadsta.ClockErr = 0;
    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_BroatStatue, (u8 *)&broadsta, sizeof(sBroatStatue_TypeDef));

    Secret.nMacErr = 0;
    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 10, &Secret.nMacErr, 1);

    //如果处在密码错误封锁期，则解除密码闭锁
    Std_Memset(&Secret.nPswRetry[0], 0x00, 2);
    Std_Memset(&Secret.tPswFailClose[0], 0x00, 4);
    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret, &Secret.nPswRetry[0], 2);
    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 2, &Secret.tPswFailClose[0], 4);

    //----------日冻结--------------------
    if ((SysDatetimes.hour == 0) && (SysDatetimes.minute == 0) && (SysDatetimes.second < 3))
    {
        TemHex_Day = SysDatetimes.day;

        if (TemHex_Day == 1) //每月1日0点，月冻结
        {
            Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_MONTHFRZ;
        }
    }
}

//函数：生成电表上报状态字
//参数：
//返回：
void fnBkgrd_GetMtConfirmStatus(void)
{
    u8 i = 0;
    //------------
    if (Bkgrd.PubData.MtSta.MtSta1.StaBit.ClockBat)
    {
        fnUpdate_RptStatus(REPORT_STATUS_CLOCKBAT);
    }
    else
    {
        fnClr_RptStatus(REPORT_STATUS_CLOCKBAT);
    }
    #if(nPhs==ThreePhs)
    //------------
    if (Bkgrd.PubData.MtSta.MtSta1.StaBit.BackupBat)
    {
        fnUpdate_RptStatus(REPORT_STATUS_BACKUPBAT);
    }
    else
    {
        fnClr_RptStatus(REPORT_STATUS_BACKUPBAT);
    }
    #endif
    //------------
    if (Bkgrd.PubData.MtSta.MtSta1.StaBit.EsamErr)
    {
        fnUpdate_RptStatus(REPORT_STATUS_ESAMERR);
    }
    else
    {
        fnClr_RptStatus(REPORT_STATUS_ESAMERR);
    }

    //------------
    if (Bkgrd.PubData.MtSta.MtSta1.StaBit.MemoryErr)
    {
        fnUpdate_RptStatus(REPORT_STATUS_MEMORYERR);
    }
    else
    {
        fnClr_RptStatus(REPORT_STATUS_MEMORYERR);
    }

    //------------
    if (Bkgrd.PubData.MtSta.MtSta1.StaBit.Overdraft)
    {
        fnUpdate_RptStatus(REPORT_STATUS_OVERDRAFT);
    }
    else
    {
        fnClr_RptStatus(REPORT_STATUS_OVERDRAFT);
    }

    if ((EvtRptData.Para.FollowAllow == TRUE) && //跟随上报总开关开启
        (EvtRptData.RecOADZB || ((EvtRptData.Para.RptStatusAllow == 1) && (EvtRptData.Status.RptStuZB)))) //有跟随上报信息
    {
        for (i = 0; i < 3; i++)
        {
            if (EvtRptData.Para.RptChannel[i] == 9) //上报通道有载波上报
            {
                PinWrite_ZBEvenOut(1);
                i = 0xAA;
                break;
            }
        }
    }

    if (i != 0xAA)
    {
        PinWrite_ZBEvenOut(0);
    }
}

#if 0 //(nPhs==ThreePhs)
//函数：生成电表状态字
//参数：Status0、Status1当前状态。
//返回：无
void fnBkgrd_GetMtStatusWd(u32 Status0, u32 Status1)
{
    u16 MtStatus;

    //---状态字1---
    MtStatus = Bkgrd.PubData.MtSta.MtSta1.Sta;
    if (Bkgrd.PubData.ClockBat < 280)
    {
        MtStatus |= (1 << 2);
        Bkgrd.PubData.EventErr[3] = BKGRD_EVENTERR_CLOCKBATLOW;
    }
    else
    {
        MtStatus &= ~(1 << 2);
        Bkgrd.PubData.EventErr[3] = BKGRD_EVENTERR_OK;
    }
    if (Bkgrd.PubData.BackupBat < 500)
    {
        MtStatus |= (1 << 3);
    }
    else
    {
        MtStatus &= ~(1 << 3);
    }
    if (MeasureRms.PubData.PDirect & (1 << 0))
    {
        MtStatus |= (1 << 4);
    }
    else
    {
        MtStatus &= ~(1 << 4);
    }
    if (MeasureRms.PubData.PDirect & (1 << 4))
    {
        MtStatus |= (1 << 5);
    }
    else
    {
        MtStatus &= ~(1 << 5);
    }
    if (Bkgrd.PubData.MoneySta.Overdraft)
    {
        MtStatus |= (1 << 14);
    }
    else
    {
        MtStatus &= ~(1 << 14);
    }
    Bkgrd.PubData.MtSta.MtSta1.Sta = MtStatus;
    //---状态字2---
    MtStatus = Bkgrd.PubData.MtSta.MtSta2.Sta;
    if (MeasureRms.PubData.PDirect & (1 << 1))
    {
        MtStatus |= (1 << 0);
    }
    else
    {
        MtStatus &= ~(1 << 0);
    }
    if (MeasureRms.PubData.PDirect & (1 << 2))
    {
        MtStatus |= (1 << 1);
    }
    else
    {
        MtStatus &= ~(1 << 1);
    }
    if (MeasureRms.PubData.PDirect & (1 << 3))
    {
        MtStatus |= (1 << 2);
    }
    else
    {
        MtStatus &= ~(1 << 2);
    }

    if (MeasureRms.PubData.PDirect & (1 << 5))
    {
        MtStatus |= (1 << 4);
    }
    else
    {
        MtStatus &= ~(1 << 4);
    }
    if (MeasureRms.PubData.PDirect & (1 << 6))
    {
        MtStatus |= (1 << 5);
    }
    else
    {
        MtStatus &= ~(1 << 5);
    }
    if (MeasureRms.PubData.PDirect & (1 << 7))
    {
        MtStatus |= (1 << 6);
    }
    else
    {
        MtStatus &= ~(1 << 6);
    }
    Bkgrd.PubData.MtSta.MtSta2.Sta = MtStatus;

    //---状态字4---
    MtStatus = 0;
    Bkgrd.PubData.EventWake[2] = BKGRD_EVENTERR_OK;
    Bkgrd.PubData.EventWake[0] = BKGRD_EVENTERR_OK;
    if (Status0 & EVGEN_MARK_LOSSVOLA)
    {
        MtStatus |= (1 << 0);
    }
    if (Status0 & EVGEN_MARK_LACKVOLA)
    {
        MtStatus |= (1 << 1);
    }
    if (Status0 & EVGEN_MARK_OVERVOLA)
    {
        MtStatus |= (1 << 2);
        Bkgrd.PubData.EventWake[2] = BKGRD_EVENTERR_OVERVOL;
    }
    if (Status0 & EVGEN_MARK_LOSSCURA)
    {
        MtStatus |= (1 << 3);
    }
    if (Status0 & EVGEN_MARK_OVERCURA)
    {
        MtStatus |= (1 << 4);
    }
    if (Status0 & EVGEN_MARK_OVERPWA)
    {
        MtStatus |= (1 << 5);
        Bkgrd.PubData.EventWake[0] = BKGRD_EVENTERR_OVERPWA;
    }
    if (Status0 & EVGEN_MARK_INSWIMA)
    {
        MtStatus |= (1 << 6);
    }
    if (Status0 & EVGEN_MARK_LOSSPHAA)
    {
        MtStatus |= (1 << 7);
    }
    if (Status0 & EVGEN_MARK_BREAKCURA)
    {
        MtStatus |= (1 << 8);
    }
    Bkgrd.PubData.MtSta.MtSta4.Sta = MtStatus + (Bkgrd.PubData.MtSta.MtSta4.Sta & 0xc000);
    //---状态字5---
    MtStatus = 0;
    if (Status0 & EVGEN_MARK_LOSSVOLB)
    {
        MtStatus |= (1 << 0);
    }
    if (Status0 & EVGEN_MARK_LACKVOLB)
    {
        MtStatus |= (1 << 1);
    }
    if (Status0 & EVGEN_MARK_OVERVOLB)
    {
        MtStatus |= (1 << 2);
        Bkgrd.PubData.EventWake[2] = BKGRD_EVENTERR_OVERVOL;
    }
    if (Status0 & EVGEN_MARK_LOSSCURB)
    {
        MtStatus |= (1 << 3);
    }
    if (Status0 & EVGEN_MARK_OVERCURB)
    {
        MtStatus |= (1 << 4);
    }
    if (Status0 & EVGEN_MARK_OVERPWB)
    {
        MtStatus |= (1 << 5);
        Bkgrd.PubData.EventWake[0] = BKGRD_EVENTERR_OVERPWA;
    }
    if (Status0 & EVGEN_MARK_INSWIMB)
    {
        MtStatus |= (1 << 6);
    }
    if (Status0 & EVGEN_MARK_LOSSPHAB)
    {
        MtStatus |= (1 << 7);
    }
    if (Status0 & EVGEN_MARK_BREAKCURB)
    {
        MtStatus |= (1 << 8);
    }
    Bkgrd.PubData.MtSta.MtSta5.Sta = MtStatus + (Bkgrd.PubData.MtSta.MtSta5.Sta & 0xc000);
    //---状态字6---
    MtStatus = 0;
    if (Status0 & EVGEN_MARK_LOSSVOLC)
    {
        MtStatus |= (1 << 0);
    }
    if (Status0 & EVGEN_MARK_LACKVOLC)
    {
        MtStatus |= (1 << 1);
    }
    if (Status0 & EVGEN_MARK_OVERVOLC)
    {
        MtStatus |= (1 << 2);
        Bkgrd.PubData.EventWake[2] = BKGRD_EVENTERR_OVERVOL;
    }
    if (Status0 & EVGEN_MARK_LOSSCURC)
    {
        MtStatus |= (1 << 3);
    }
    if (Status0 & EVGEN_MARK_OVERCURC)
    {
        MtStatus |= (1 << 4);
    }
    if (Status0 & EVGEN_MARK_OVERPWC)
    {
        MtStatus |= (1 << 5);
        Bkgrd.PubData.EventWake[0] = BKGRD_EVENTERR_OVERPWA;
    }
    if (Status0 & EVGEN_MARK_INSWIMC)
    {
        MtStatus |= (1 << 6);
    }
    if (Status0 & EVGEN_MARK_LOSSPHAC)
    {
        MtStatus |= (1 << 7);
    }
    if (Status0 & EVGEN_MARK_BREAKCURC)
    {
        MtStatus |= (1 << 8);
    }
    Bkgrd.PubData.MtSta.MtSta6.Sta = MtStatus + (Bkgrd.PubData.MtSta.MtSta6.Sta & 0xc000);
    //---状态字7---
    MtStatus = 0;
    if (Status1 & EVGEN_MARK_INPHAVOL)
    {
        MtStatus |= (1 << 0);
    }
    if (Status1 & EVGEN_MARK_INPHACUR)
    {
        MtStatus |= (1 << 1);
    }
    if (Status1 & EVGEN_MARK_UNBLVOL)
    {
        MtStatus |= (1 << 2);
    }
    if (Status1 & EVGEN_MARK_UNBLCUR)
    {
        MtStatus |= (1 << 3);
    }
    if (Status1 & EVGEN_MARK_LOSSAUX)
    {
        MtStatus |= (1 << 4);
    }
    if (Status1 & EVGEN_MARK_POWDN)
    {
        MtStatus |= (1 << 5);
    }
    if ((Status0 & EVGEN_MARK_OVERQNEED) ||
        (Status1 & EVGEN_MARK_OVERPNEED))
    {
        MtStatus |= (1 << 6);
    }
    if (Status0 & EVGEN_MARK_OVERPF)
    {
        MtStatus |= (1 << 7);
        Bkgrd.PubData.EventWake[3] = BKGRD_EVENTERR_OVERPF;
    }
    else
    {
        Bkgrd.PubData.EventWake[3] = BKGRD_EVENTERR_OK;
    }
    if (Status1 & EVGEN_MARK_OVERUNBLCUR)
    {
        MtStatus |= (1 << 8);
        Bkgrd.PubData.EventWake[1] = BKGRD_EVENTERR_OVERUNBLCUR;
    }
    else
    {
        Bkgrd.PubData.EventWake[1] = BKGRD_EVENTERR_OK;
    }

    //双方向表有功反向不报警
    //if((MeasureRms.PubData.PDirect >> 0) & 0x01) Bkgrd.PubData.EventWake[5]=BKGRD_EVENTERR_INSWIM;
    //else Bkgrd.PubData.EventWake[5]=BKGRD_EVENTERR_OK;

    if (Status1 & (EVGEN_MARK_OVERPTPNEED | EVGEN_MARK_OVERNTPNEED))
    {
        Bkgrd.PubData.EventWake[4] = BKGRD_EVENTERR_OVERPNEED;
    }
    else
    {
        Bkgrd.PubData.EventWake[4] = BKGRD_EVENTERR_OK;
    }

    if (Status1 & EVGEN_MARK_QLOSSVOL)
    {
        Bkgrd.PubData.ValCurStatus.FlagBit.QLOSSVOL = 1;
    }

    if (Key.Press & KEY_VAL_SHELL)
    {
        MtStatus |= (1 << 9);
    }
    if (Key.Press & KEY_VAL_JUNBOX)
    {
        MtStatus |= (1 << 10);
    }

    Bkgrd.PubData.MtSta.MtSta7.Sta = MtStatus;
}

void fnBkgrd_StatusGenerate(void)
{
    u32             nStatus[2];

    u32             tempU32_I[4], temp_VectorI;

    u8              *p, i;
    u32             D;
    u32 tmpPw[3];
    u16 tmpPf[4], temp16;

    if (fnCrc_Check(1, (u8 *)&Bkgrd.PriPara, sizeof(Bkgrd.PriPara) - 2, (u8 *)&Bkgrd.PriPara.Crc))
    {
        fnFile_Read(FileId_HighPara,
                    FileItemInfoOffAddr_HighPara_WireMode,
                    &Bkgrd.PriPara.WireMode, 1);

        fnCrc_Check(0, (u8 *)&Bkgrd.PriPara, sizeof(Bkgrd.PriPara) - 2, (u8 *)&Bkgrd.PriPara.Crc);
    }

    if (fnCrc_Check(1, (u8 *)&Trim, sizeof(sTrim_TypeDef) - 2, (u8 *)&Trim.Crc))
    {
        fnFile_Read(FileId_EvtCfgPara, FileItemInfoOffAddr_EvtCfgPara_LossVol, &Trim, sizeof(sTrim_TypeDef));
        if (fnCrc_Check(1, (u8 *)&Trim, sizeof(sTrim_TypeDef) - 2, (u8 *)&Trim.Crc))    //E2数据错恢复到默认值
        {
            Std_Memcpy((u8 *)&Trim, (u8 *)&EvtCfgParaDefault, FileLen_EvtCfgPara);
        }
    }

    //---状态产生---
    nStatus[0] = 0 ;
    nStatus[1] = 0;

    for (i = 0 ; i < nPhs; i++)
    {
        tempU32_I[i] = abs(MeasureRms.PubData.I[i]);    //A,B,C
        tmpPf[i + 1] =  abs(MeasureRms.PubData.Pf[i + 1]); //A,B,C
    }

    tempU32_I[3] = abs(MeasureRms.PubData.In);  //N
    tmpPf[0] =  abs(MeasureRms.PubData.Pf[0]);  //总

    //有功功率反向判定
    for (i = 0 ; i < nPhs; i++)
    {
        tmpPw[i] =  abs(MeasureRms.PubData.Pw[1 + i]);
    }

    //-----零序电流--------------

    temp_VectorI = abs(MeasureRms.PubData.VectorI[2]);

    //-------判断电压电流实时状态------------------
    for (i = 0 ; i < nPhs; i++)
    {
        if (MeasureRms.PubData.U[i] < FLOWV_VOL60Un)
        {
            Bkgrd.PubData.ValCurStatus.Flag |= (1 << i);
        }
        else
        {
            Bkgrd.PubData.ValCurStatus.Flag &= ~(1 << i);
        }

        if (MeasureRms.PubData.I[i] == 0)
        {
            Bkgrd.PubData.ValCurStatus.Flag |= (1 << (i + 4));
        }
        else
        {
            Bkgrd.PubData.ValCurStatus.Flag &= ~(1 << (i + 4));
        }
    }

    // --------判延时时间------------------
    if (Bkgrd.PriPara.WireMode == 0)
    {
        if ((MeasureRms.PubData.U[0] < FLOWV_VOL60Un) &&
            (MeasureRms.PubData.U[1] < FLOWV_VOL60Un) &&
            (MeasureRms.PubData.U[2] < FLOWV_VOL60Un))
        {
            nStatus[1] |= EVGEN_MARK_POWDN;
        }
    }
    else
    {
        if ((MeasureRms.PubData.U[0] < FLOWV_VOL60Un) &&
            (MeasureRms.PubData.U[2] < FLOWV_VOL60Un))
        {
            nStatus[1] |= EVGEN_MARK_POWDN;
        }
    }

    //断相判定
    if (!(nStatus[1] & EVGEN_MARK_POWDN))
    {
        if (!(nStatus[1] & EVGEN_MARK_POWDN)
            && (MeasureRms.PubData.U[0] < Trim.LpVol.LossPhaUTouchUp)
            && (tempU32_I[0] < Trim.LpVol.LossPhaITouchUp)
            && (Trim.LpVol.LossPhaITouchUp != 0))
        {
            nStatus[0]  |= EVGEN_MARK_LOSSPHAA;
        }

        if (!(nStatus[1] & EVGEN_MARK_POWDN)
            && (Bkgrd.PriPara.WireMode == 0)
            && (MeasureRms.PubData.U[1] < Trim.LpVol.LossPhaUTouchUp)
            && (tempU32_I[1] < Trim.LpVol.LossPhaITouchUp)
            && (Trim.LpVol.LossPhaITouchUp != 0))
        {
            nStatus[0] |= EVGEN_MARK_LOSSPHAB;
        }

        if (!(nStatus[1] & EVGEN_MARK_POWDN)
            && (MeasureRms.PubData.U[2] < Trim.LpVol.LossPhaUTouchUp)
            && (tempU32_I[2] < Trim.LpVol.LossPhaITouchUp)
            && (Trim.LpVol.LossPhaITouchUp != 0))
        {
            nStatus[0] |= EVGEN_MARK_LOSSPHAC;
        }
    }

    //过压判定
    if ((MeasureRms.PubData.U[0] > Trim.VrVol.OverUpVolUTouchDn) && (Trim.VrVol.OverUpVolUTouchDn != 0))
    {
        nStatus[0]  |= EVGEN_MARK_OVERVOLA;
    }

    if ((Bkgrd.PriPara.WireMode == 0) &&
        (MeasureRms.PubData.U[1] > Trim.VrVol.OverUpVolUTouchDn) &&
        (Trim.VrVol.OverUpVolUTouchDn != 0))
    {
        nStatus[0]  |= EVGEN_MARK_OVERVOLB;
    }

    if ((MeasureRms.PubData.U[2] > Trim.VrVol.OverUpVolUTouchDn) && (Trim.VrVol.OverUpVolUTouchDn != 0))
    {
        nStatus[0]  |= EVGEN_MARK_OVERVOLC;
    }

    //欠压判定
    if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
        !(nStatus[0] & EVGEN_MARK_LOSSPHAA) &&
        (MeasureRms.PubData.U[0] < Trim.LkVol.LackVolUTouchUp) &&
        (Trim.LkVol.LackVolUTouchUp != 0))
    {
        nStatus[0] |= EVGEN_MARK_LACKVOLA;
    }

    if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
        (Bkgrd.PriPara.WireMode == 0) &&
        !(nStatus[0] & EVGEN_MARK_LOSSPHAB) &&
        (MeasureRms.PubData.U[1] < Trim.LkVol.LackVolUTouchUp) &&
        (Trim.LkVol.LackVolUTouchUp != 0))
    {
        nStatus[0]   |= EVGEN_MARK_LACKVOLB;
    }

    if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
        !(nStatus[0] & EVGEN_MARK_LOSSPHAC) &&
        (MeasureRms.PubData.U[2] < Trim.LkVol.LackVolUTouchUp) &&
        (Trim.LkVol.LackVolUTouchUp != 0))
    {
        nStatus[0]   |= EVGEN_MARK_LACKVOLC;
    }

    //全失压判定

    if (Bkgrd.PriPara.WireMode == 0)
    {
        if (((MeasureRms.PubData.U[0] < FLOWV_VOL60Un) &&
             (MeasureRms.PubData.U[1] < FLOWV_VOL60Un) &&
             (MeasureRms.PubData.U[2] < FLOWV_VOL60Un)) &&
            ((tempU32_I[0] > FLOWV_CUR5Ib) ||
             (tempU32_I[1] > FLOWV_CUR5Ib) ||
             (tempU32_I[2] > FLOWV_CUR5Ib)))
        {
            nStatus[1] |= EVGEN_MARK_QLOSSVOL;
        }
        else
        {
            Bkgrd.PubData.ValCurStatus.FlagBit.QLOSSVOL = 0;
        }
    }
    else
    {
        if (((MeasureRms.PubData.U[0] < FLOWV_VOL60Un) &&
             (MeasureRms.PubData.U[2] < FLOWV_VOL60Un)) &&
            ((tempU32_I[0] > FLOWV_CUR5Ib) ||
             (tempU32_I[2] > FLOWV_CUR5Ib)))
        {
            nStatus[1] |= EVGEN_MARK_QLOSSVOL;
        }
        else
        {
            Bkgrd.PubData.ValCurStatus.FlagBit.QLOSSVOL = 0;
        }
    }

    if (!(nStatus[1] & EVGEN_MARK_QLOSSVOL))    // 全失压发生时不做失压判断
    {
        //失压判定
        if (EvStatusInter.Status[0] & EVGEN_MARK_LOSSVOLA)
        {
            if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
                !(nStatus[1] & EVGEN_MARK_QLOSSVOL) &&
                (MeasureRms.PubData.U[0] < Trim.LsVol.LossVolUResumeDn) &&
                (tempU32_I[0] > Trim.LsVol.LossVolITouchDn) &&
                (Trim.LsVol.LossVolUTouchUp != 0))
            {
                nStatus[0] |= EVGEN_MARK_LOSSVOLA;    //失压尚未恢复
            }
        }
        else
        {
            if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
                !(nStatus[1] & EVGEN_MARK_QLOSSVOL) &&
                (MeasureRms.PubData.U[0] < Trim.LsVol.LossVolUTouchUp) &&
                (tempU32_I[0] > Trim.LsVol.LossVolITouchDn) &&
                (Trim.LsVol.LossVolUTouchUp != 0))
            {
                nStatus[0] |= EVGEN_MARK_LOSSVOLA;    //失压起始条件满足
            }
        }
        if (Bkgrd.PriPara.WireMode == 0)
        {
            if (EvStatusInter.Status[0] & EVGEN_MARK_LOSSVOLB)
            {
                if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
                    !(nStatus[1] & EVGEN_MARK_QLOSSVOL) &&
                    (MeasureRms.PubData.U[1] < Trim.LsVol.LossVolUResumeDn) &&
                    (tempU32_I[1] > Trim.LsVol.LossVolITouchDn) &&
                    (Trim.LsVol.LossVolUTouchUp != 0))
                {
                    nStatus[0] |= EVGEN_MARK_LOSSVOLB;
                }
            }
            else
            {
                if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
                    !(nStatus[1] & EVGEN_MARK_QLOSSVOL) &&
                    (MeasureRms.PubData.U[1] < Trim.LsVol.LossVolUTouchUp) &&
                    (tempU32_I[1] > Trim.LsVol.LossVolITouchDn) &&
                    (Trim.LsVol.LossVolUTouchUp != 0))
                {
                    nStatus[0] |= EVGEN_MARK_LOSSVOLB;
                }
            }
        }
        if (EvStatusInter.Status[0] & EVGEN_MARK_LOSSVOLC)
        {
            if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
                !(nStatus[1] & EVGEN_MARK_QLOSSVOL) &&
                (MeasureRms.PubData.U[2] <  Trim.LsVol.LossVolUResumeDn) &&
                (tempU32_I[2] > Trim.LsVol.LossVolITouchDn) &&
                (Trim.LsVol.LossVolUTouchUp != 0))
            {
                nStatus[0] |= EVGEN_MARK_LOSSVOLC;
            }
        }
        else
        {
            if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
                !(nStatus[1] & EVGEN_MARK_QLOSSVOL) &&
                (MeasureRms.PubData.U[2] < Trim.LsVol.LossVolUTouchUp) &&
                (tempU32_I[2] > Trim.LsVol.LossVolITouchDn) &&
                (Trim.LsVol.LossVolUTouchUp != 0))
            {
                nStatus[0] |= EVGEN_MARK_LOSSVOLC;
            }
        }
    }

    //断流判定
    if ((MeasureRms.PubData.U[0] > Trim.BkCur.BreakCurUTouchDn) &&
        (tempU32_I[0] < Trim.BkCur.BreakCurITouchUp) &&
        (Trim.BkCur.BreakCurITouchUp != 0))
    {
        nStatus[0]  |= EVGEN_MARK_BREAKCURA;
    }

    if ((Bkgrd.PriPara.WireMode == 0) &&
        (MeasureRms.PubData.U[1] > Trim.BkCur.BreakCurUTouchDn) &&
        (tempU32_I[1] < Trim.BkCur.BreakCurITouchUp) &&
        (Trim.BkCur.BreakCurITouchUp != 0))
    {
        nStatus[0]  |= EVGEN_MARK_BREAKCURB;
    }

    if ((MeasureRms.PubData.U[2] > Trim.BkCur.BreakCurUTouchDn) &&
        (tempU32_I[2] < Trim.BkCur.BreakCurITouchUp) &&
        (Trim.BkCur.BreakCurITouchUp != 0))
    {
        nStatus[0]  |= EVGEN_MARK_BREAKCURC;
    }

    //失流判定
    if (Bkgrd.PriPara.WireMode == 0)
    {
        if (((tempU32_I[0] > Trim.LsCur.LossCurITouchDn) ||
             (tempU32_I[1] > Trim.LsCur.LossCurITouchDn) ||
             (tempU32_I[2] > Trim.LsCur.LossCurITouchDn)) &&
            (Trim.LsCur.LossCurITouchUp != 0))
        {
            if (!(nStatus[1] & EVGEN_MARK_POWDN)
                && (tempU32_I[0] < Trim.LsCur.LossCurITouchUp)
                && (MeasureRms.PubData.U[0] > Trim.LsCur.LossCurUTouchDn))
            {
                nStatus[0] |= EVGEN_MARK_LOSSCURA;
            }

            if (!(nStatus[1] & EVGEN_MARK_POWDN)
                && (tempU32_I[1] < Trim.LsCur.LossCurITouchUp)
                && (MeasureRms.PubData.U[1] > Trim.LsCur.LossCurUTouchDn))
            {
                nStatus[0] |= EVGEN_MARK_LOSSCURB;
            }

            if (!(nStatus[1] & EVGEN_MARK_POWDN)
                && (tempU32_I[2] < Trim.LsCur.LossCurITouchUp)
                && (MeasureRms.PubData.U[2] > Trim.LsCur.LossCurUTouchDn))
            {
                nStatus[0] |= EVGEN_MARK_LOSSCURC;
            }
        }
    }
    else
    {
        if (((tempU32_I[0] > Trim.LsCur.LossCurITouchDn) ||
             (tempU32_I[2] > Trim.LsCur.LossCurITouchDn)) &&
            (Trim.LsCur.LossCurITouchUp != 0))
        {
            if (!(nStatus[1] & EVGEN_MARK_POWDN)
                && (tempU32_I[0] < Trim.LsCur.LossCurITouchUp)
                && (MeasureRms.PubData.U[0] > Trim.LsCur.LossCurUTouchDn))
            {
                nStatus[0] |= EVGEN_MARK_LOSSCURA;
            }

            if (!(nStatus[1] & EVGEN_MARK_POWDN)
                && (tempU32_I[2] < Trim.LsCur.LossCurITouchUp)
                && (MeasureRms.PubData.U[2] > Trim.LsCur.LossCurUTouchDn))
            {
                nStatus[0]    |= EVGEN_MARK_LOSSCURC;
            }
        }
    }

    if ((((MeasureRms.PubData.PDirect >> 1) & 0x11) == QUADRANT_II) ||
        (((MeasureRms.PubData.PDirect >> 1) & 0x11) == QUADRANT_III))
    {
        if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
            (tmpPw[0] > Trim.SwPw.InSwimPwTouchDn) &&
            (Trim.SwPw.InSwimPwTouchDn != 0))
        {
            nStatus[0]  |= EVGEN_MARK_INSWIMA;
        }
    }
    if ((Bkgrd.PriPara.WireMode == 0) &&
        ((((MeasureRms.PubData.PDirect >> 2) & 0x11) == QUADRANT_II) ||
         (((MeasureRms.PubData.PDirect >> 2) & 0x11) == QUADRANT_III)))
    {
        if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
            (tmpPw[1] > Trim.SwPw.InSwimPwTouchDn) &&
            (Trim.SwPw.InSwimPwTouchDn != 0))
        {
            nStatus[0]  |= EVGEN_MARK_INSWIMB;
        }
    }
    if ((((MeasureRms.PubData.PDirect >> 3) & 0x11) == QUADRANT_II) ||
        (((MeasureRms.PubData.PDirect >> 3) & 0x11) == QUADRANT_III))
    {
        if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
            (tmpPw[2] > Trim.SwPw.InSwimPwTouchDn) &&
            (Trim.SwPw.InSwimPwTouchDn != 0))
        {
            nStatus[0]  |= EVGEN_MARK_INSWIMC;
        }
    }

    //过载判定
    if ((tmpPw[0] > Trim.VrPw.OverPwTouchDn) && (Trim.VrPw.OverPwTouchDn != 0))
    {
        nStatus[0] |= EVGEN_MARK_OVERPWA;
    }

    if ((Bkgrd.PriPara.WireMode == 0) &&
        (tmpPw[1] > Trim.VrPw.OverPwTouchDn) &&
        (Trim.VrPw.OverPwTouchDn != 0))
    {
        nStatus[0] |= EVGEN_MARK_OVERPWB;
    }

    if ((tmpPw[2] > Trim.VrPw.OverPwTouchDn) && (Trim.VrPw.OverPwTouchDn != 0))
    {
        nStatus[0] |= EVGEN_MARK_OVERPWC;
    }

    //电压不平衡判定
    if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
        (MeasureRms.PubData.UnblU > Trim.UbVol.INT16Touch) &&
        (Trim.UbVol.INT16Touch != 0))
    {
        nStatus[1]  |= EVGEN_MARK_UNBLVOL;
    }

    //电流不平衡判定
    if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
        (MeasureRms.PubData.UnblI > Trim.UbCur.INT16Touch) &&
        (Trim.UbCur.INT16Touch != 0))
    {
        nStatus[1]  |= EVGEN_MARK_UNBLCUR;
    }

    //电流严重不平衡事件记录
    if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
        (MeasureRms.PubData.UnblI > Trim.VUbCur.INT16Touch) &&
        (Trim.UbCur.INT16Touch != 0))
    {
        nStatus[1]   |= EVGEN_MARK_OVERUNBLCUR;
    }

    //电压逆相序判定
    if (Bkgrd.PriPara.WireMode == 0)
    {
        if ((MeasureRms.PubData.U[0] > FLOWV_VOL60Un) &&
            (MeasureRms.PubData.U[1] > FLOWV_VOL60Un) &&
            (MeasureRms.PubData.U[2] > FLOWV_VOL60Un) &&
            (1000 < MeasureRms.PubData.Angle[2]) &&
            (MeasureRms.PubData.Angle[2] < 1400))
        {
            nStatus[1]  |= EVGEN_MARK_INPHAVOL;
        }
    }
    else
    {
        if ((MeasureRms.PubData.U[0] > FLOWV_VOL60Un) &&
            (MeasureRms.PubData.U[2] > FLOWV_VOL60Un) &&
            (1000 < MeasureRms.PubData.Angle[2]) &&
            (MeasureRms.PubData.Angle[2] < 1400))
        {
            nStatus[1]  |= EVGEN_MARK_INPHAVOL;
        }
    }

    //电流逆相序判定
    if (Bkgrd.PriPara.WireMode == 0)
    {
        i = 0;
        if (MeasureRegTmp.Angle[3] > MeasureRegTmp.Angle[2])
        {
            i++;
        }
        if (MeasureRegTmp.Angle[4] > MeasureRegTmp.Angle[3])
        {
            i++;
        }
        if (MeasureRegTmp.Angle[4] > MeasureRegTmp.Angle[2])
        {
            i++;
        }
        if ((MeasureRms.PubData.U[0] > FLOWV_VOL60Un)
            && (MeasureRms.PubData.U[1] > FLOWV_VOL60Un)
            && (MeasureRms.PubData.U[2] > FLOWV_VOL60Un)
            && (tempU32_I[0] > FLOWV_CUR5Ib)
            && (tempU32_I[1] > FLOWV_CUR5Ib)
            && (tempU32_I[2] > FLOWV_CUR5Ib)
            && ((i == 2) || (i == 0))
           )
        {
            nStatus[1] |= EVGEN_MARK_INPHACUR;
        }
    }
    else
    {
        i = 0;
        if (MeasureRegTmp.Angle[4] > MeasureRegTmp.Angle[2])
        {
            i++;
        }
        if ((MeasureRms.PubData.U[0] > FLOWV_VOL60Un) &&
            (MeasureRms.PubData.U[2] > FLOWV_VOL60Un) &&
            (tempU32_I[0] > FLOWV_CUR5Ib) &&
            (tempU32_I[2] > FLOWV_CUR5Ib) &&
            (i == 0))
        {
            nStatus[1] |= EVGEN_MARK_INPHACUR;
        }
    }

    //超需量事件记录
    if (!(nStatus[1] & EVGEN_MARK_POWDN))
    {
        switch ((MeasureRms.PubData.PDirect >> 0) & 0x11)
        {
            case QUADRANT_I:
            case QUADRANT_IV:   //正向有功需量
                if ((fnDFCompData((u8 *)&Demand.PriData[PtDmndWndw].Need, (u8 *)&Trim.VrPNd.OverNeedTouchDn, 4) > 0) &&
                    (Trim.VrPNd.OverNeedTouchDn != 0))
                {
                    nStatus[1] |= EVGEN_MARK_OVERPTPNEED;
                }

                break;

            case QUADRANT_II:
            case QUADRANT_III:  //反向有功需量

                nStatus[1] |= EVGEN_MARK_PSING;  //有功需量反向

                if ((fnDFCompData((u8 *)&Demand.PriData[NtDmndWndw].Need, (u8 *)&Trim.VrNNd.OverNeedTouchDn, 4) > 0) &&
                    (Trim.VrNNd.OverNeedTouchDn != 0))
                {
                    nStatus[1] |= EVGEN_MARK_OVERNTPNEED;
                }

                break;

            default:
                break;
        }
    }

    if (!(nStatus[1] & EVGEN_MARK_POWDN))
    {
        switch ((MeasureRms.PubData.PDirect >> 0) & 0x11)
        {
            case QUADRANT_I:
                if ((fnDFCompData((u8 *)&Demand.PriData[Qd1DmndWndw].Need, (u8 *)&Trim.VrQNd.OverNeedTouchDn, 4) > 0) &&
                    (Trim.VrQNd.OverNeedTouchDn != 0))
                {
                    nStatus[0] |= EVGEN_MARK_OVERQD1QNEED;
                }

                break;

            case QUADRANT_II:   //
                if ((fnDFCompData((u8 *)&Demand.PriData[Qd2DmndWndw].Need, (u8 *)&Trim.VrQNd.OverNeedTouchDn, 4) > 0) &&
                    (Trim.VrQNd.OverNeedTouchDn != 0))
                {
                    nStatus[0] |= EVGEN_MARK_OVERQD2QNEED;
                }

                break;

            case QUADRANT_III:

                nStatus[1] |= EVGEN_MARK_QSING; //无功需量反向

                if ((fnDFCompData((u8 *)&Demand.PriData[Qd3DmndWndw].Need, (u8 *)&Trim.VrQNd.OverNeedTouchDn, 4) > 0) &&
                    (Trim.VrQNd.OverNeedTouchDn != 0))
                {
                    nStatus[0] |= EVGEN_MARK_OVERQD3QNEED;
                }

                break;

            case QUADRANT_IV:  //反向有功需量

                nStatus[1] |= EVGEN_MARK_QSING;  //无功需量反向

                if ((fnDFCompData((u8 *)&Demand.PriData[Qd4DmndWndw].Need, (u8 *)&Trim.VrQNd.OverNeedTouchDn, 4) > 0) &&
                    (Trim.VrQNd.OverNeedTouchDn != 0))
                {
                    nStatus[0] |= EVGEN_MARK_OVERQD4QNEED;
                }

                break;

            default:
                break;
        }
    }

    if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
        (tmpPf[0] < Trim.VrPf.INT16Touch) &&
        (Trim.VrPf.INT16Touch != 0) &&
        ((tempU32_I[0] > FLOWV_CUR5Ib)
         || (tempU32_I[1] > FLOWV_CUR5Ib)
         || (tempU32_I[2] > FLOWV_CUR5Ib)))
    {
        nStatus[0]  |= EVGEN_MARK_OVERPF;
    }

    //A相功率因数超标
    if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
        (tmpPf[1] < Trim.VrPf.INT16Touch) &&
        (Trim.VrPf.INT16Touch != 0) &&
        (tempU32_I[0] > FLOWV_CUR5Ib))
    {
        nStatus[1]  |= EVGEN_MARK_OVERPFA;
    }

    //B相功率因数超标
    if (Bkgrd.PriPara.WireMode == 0)
    {
        if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
            (tmpPf[2] < Trim.VrPf.INT16Touch) &&
            (Trim.VrPf.INT16Touch != 0) &&
            (tempU32_I[1] > FLOWV_CUR5Ib))
        {
            nStatus[1]  |= EVGEN_MARK_OVERPFB;
        }
    }

    //C相功率因数超标
    if (!(nStatus[1] & EVGEN_MARK_POWDN) &&
        (tmpPf[3] < Trim.VrPf.INT16Touch) &&
        (Trim.VrPf.INT16Touch != 0) &&
        (tempU32_I[2] > FLOWV_CUR5Ib))
    {
        nStatus[1]  |= EVGEN_MARK_OVERPFC;
    }

    //过流判定 过流阀值NNN.N
    if ((tempU32_I[0] > Trim.VrCur.OverUpCurITouchUp) &&
        (Trim.VrCur.OverUpCurITouchUp != 0))
    {
        nStatus[0] |= EVGEN_MARK_OVERCURA;
    }

    if ((Bkgrd.PriPara.WireMode == 0) &&
        (tempU32_I[1] > Trim.VrCur.OverUpCurITouchUp) &&
        (Trim.VrCur.OverUpCurITouchUp != 0))
    {
        nStatus[0] |= EVGEN_MARK_OVERCURB;
    }

    if ((tempU32_I[2] > Trim.VrCur.OverUpCurITouchUp) &&
        (Trim.VrCur.OverUpCurITouchUp != 0))
    {
        nStatus[0] |= EVGEN_MARK_OVERCURC;
    }

    //-------零线电流异常---------------
    if (((temp_VectorI > Trim.NLineErr.NLineErrCurITouchDn) || (tempU32_I[3] > Trim.NLineErr.NLineErrCurITouchDn)) &&
        (Trim.NLineErr.NLineErrCurITouchDn != 0) &&
        (Trim.NLineErr.NLineErrTouch != 0))
    {
        if (temp_VectorI > tempU32_I[3])
        {
            temp16 = (temp_VectorI - tempU32_I[3]) * 10000 / temp_VectorI;
        }
        else
        {
            temp16 = (tempU32_I[3] - temp_VectorI) * 10000 / tempU32_I[3];
        }

        if (temp16 > Trim.NLineErr.NLineErrTouch)
        {
            nStatus[1]  |= EVGEN_MARK_NLineErr;
        }
    }
    //---------计量芯片异常----------------
    if (MeasureRms.PriData.Flag & MEASURE_FLAG_Err)
    {
        nStatus[1]  |= EVGEN_MARK_MeasureErr;
    }

    //---滤波---
    p = (u8 *)&EvStatusInter.tLossVola;
    for (D = 1, i = 0 ; i < 32 ; i++, D <<= 1, p++)
    {
        if (((EvStatusInter.lStatus[0] ^ nStatus[0]) & nStatus[0]) & D)         //事件发生滤波，状态改变,时间定值赋初值
        {
            switch (i)
            {
                case 0: //失压
                case 1:
                case 2:
                    *p = Trim.LsVol.tLossVol ;
                    break;
                case 3: //欠压
                case 4:
                case 5:
                    *p = Trim.LkVol.tLackVol ;
                    break;
                case 6: //过压
                case 7:
                case 8:
                    *p = Trim.VrVol.tOverUpVol ;
                    break;
                case 9: //断相
                case 10:
                case 11:
                    *p = Trim.LpVol.tLossPha ;
                    break;
                case 12:    //失流
                case 13:
                case 14:
                    *p = Trim.LsCur.tLossCur ;
                    break;
                case 15:    //过流
                case 16:
                case 17:
                    *p = Trim.VrCur.tOverUpCur ;
                    break;
                case 18:    //断流
                case 19:
                case 20:
                    *p = Trim.BkCur.tBreakCur ;
                    break;
                case 21:    //分相有功功率反向
                case 22:
                case 23:
                    *p = Trim.SwPw.tInSwim ;
                    break;
                case 24:    //过载
                case 25:
                case 26:
                    *p = Trim.VrPw.tOverPw ;
                    break;
                case 27:    //一象限无功需量超限
                case 28:    //二象限无功需量超限
                case 29:    //三象限无功需量超限
                case 30:    //四象限无功需量超限
                    *p = Trim.VrQNd.tOverNeed;
                    break;

                case 31:    //超功率因数
                    *p = Trim.VrPf.tDly;
                    break;

                default:
                    *p = 10;
                    break;
            }
        }
        if (((EvStatusInter.lStatus[0] ^ nStatus[0]) & EvStatusInter.lStatus[0] & EvStatusInter.Status[0]) & D)     //事件结束滤波
        {
            switch (i)
            {
                case 0: //失压
                case 1:
                case 2:
                    *p = Trim.LsVol.tLossVol ;
                    break;
                case 3: //欠压
                case 4:
                case 5:
                    *p = Trim.LkVol.tLackVol ;
                    break;
                case 6: //过压
                case 7:
                case 8:
                    *p = Trim.VrVol.tOverUpVol ;
                    break;
                case 9: //断相
                case 10:
                case 11:
                    *p = Trim.LpVol.tLossPha ;
                    break;
                case 12:    //失流
                case 13:
                case 14:
                    *p = Trim.LsCur.tLossCur ;
                    break;
                case 15:    //过流
                case 16:
                case 17:
                    *p = Trim.VrCur.tOverUpCur ;
                    break;
                case 18:    //断流
                case 19:
                case 20:
                    *p = Trim.BkCur.tBreakCur ;
                    break;
                case 21:    //分相有功功率反向
                case 22:
                case 23:
                    *p = Trim.SwPw.tInSwim ;
                    break;
                case 24:    //过载
                case 25:
                case 26:
                    *p = Trim.VrPw.tOverPw ;
                    break;
                case 27:    //一象限无功需量超限
                case 28:    //二象限无功需量超限
                case 29:    //三象限无功需量超限
                case 30:    //四象限无功需量超限
                    *p = Trim.VrQNd.tOverNeed;
                    break;

                case 31:    //超功率因数
                    *p = Trim.VrPf.tDly;
                    break;

                default:
                    *p = 10;
                    break;
            }
        }

        if (EvStatusInter.Status[0] & D)
        {
            if (!((EvStatusInter.lStatus[0] | nStatus[0]) & D))     //事件结束
            {
                if (*p == 0)
                {
                    *p = 10;
                }
                if (*p)
                {
                    *p = *p - 1;    //倒计时,每秒钟调用该子程序时减一次
                }
                if (*p == 0)
                {
                    EvStatusInter.Status[0] &= ~D;    //倒计时结束，读入最终的状态，最后是用该StatusInter.Status来判断状态字的
                }
            }
        }
        else
        {
            if (EvStatusInter.lStatus[0] & nStatus[0] & D)      //事件产生
            {
                if (*p == 0)
                {
                    *p = 10;
                }
                if (*p)
                {
                    *p = *p - 1;    //倒计时,每秒钟调用该子程序时减一次
                }
                if (*p == 0)
                {
                    EvStatusInter.Status[0] |= D;    //倒计时结束，读入最终的状态，最后是用该StatusInter.Status来判断状态字的
                }
            }
        }
    }

    p = (u8 *) &EvStatusInter.tOverPfA;
    for (D = 1, i = 0 ; i < 17 ; i++, D <<= 1, p++)
    {
        if (((EvStatusInter.lStatus[1] ^ nStatus[1]) & nStatus[1]) & D)         //事件发生滤波，状态改变,时间定值赋初值
        {
            switch (i)
            {
                case 0:
                case 1:
                case 2:       //A,B,C相超功率因数
                    *p = Trim.VrPf.tDly ;
                    break;
                case 3: //正向有功需量超限
                    *p = Trim.VrPNd.tOverNeed;
                    break;
                case 4: //反向有功需量超限
                    *p = Trim.VrNNd.tOverNeed;
                    break;
                case 5: //全失压
                    *p = 60 ;
                    break;
                case 6: //辅助电源
                    *p = 0 ;
                    break;
                case 7: //电压逆相序
                    *p = Trim.IPVol.tDly ;
                    break;
                case 8: //电流逆相序
                    *p = Trim.IPCur.tDly ;
                    break;
                case 9:
                    //*p = Trim.PowDn.tDly ; break;
                    *p = 2 ;
                    break;  //停电固定2秒判断延时

                case 10:    //电压不平衡
                    *p = Trim.UbVol.tDly ;
                    break;
                case 11:    //电流不平衡
                    *p = Trim.UbCur.tDly ;
                    break;
                case 12:    //电流严重不平衡
                    *p = Trim.VUbCur.tDly ;
                    break;

                case 13:    //零线电流异常
                    *p = Trim.NLineErr.tNLineErr;
                    break;

                case 14:    //计量芯片异常
                    *p = Trim.MrErr.tDly;
                    break;

                case 15:
                case 16:
                    *p = 60; //需量方向改变判断时间固定1min
                    break;
                default:
                    *p = 10;
                    break;
            }
        }
        u32 temp;
        temp = EvStatusInter.lStatus[1] ^ nStatus[1];
        temp &= EvStatusInter.lStatus[1];
        temp &= D;
        if (((EvStatusInter.lStatus[1]^nStatus[1]) & EvStatusInter.lStatus[1]) & D)     //事件结束滤波
        {
            switch (i)
            {
                case 0:
                case 1:
                case 2:       //A,B,C相超功率因数
                    *p = Trim.VrPf.tDly ;
                    break;
                case 3: //正向有功需量超限
                    *p = Trim.VrPNd.tOverNeed;
                    break;
                case 4: //反向有功需量超限
                    *p = Trim.VrNNd.tOverNeed;
                    break;
                case 5: //全失压
                    *p = 60 ;
                    break;
                case 6: //辅助电源
                    *p = 0 ;
                    break;
                case 7: //电压逆相序
                    *p = Trim.IPVol.tDly ;
                    break;
                case 8: //电流逆相序
                    *p = Trim.IPCur.tDly ;
                    break;
                case 9:
                    //*p = Trim.PowDn.tDly ; break;
                    *p = 2 ;
                    break;  //停电固定2秒判断延时

                case 10:    //电压不平衡
                    *p = Trim.UbVol.tDly ;
                    break;
                case 11:    //电流不平衡
                    *p = Trim.UbCur.tDly ;
                    break;
                case 12:    //电流严重不平衡
                    *p = Trim.VUbCur.tDly ;
                    break;

                case 13:    //零线电流异常
                    *p = Trim.NLineErr.tNLineErr;
                    break;

                case 14:    //计量芯片异常
                    *p = Trim.MrErr.tDly;
                    break;

                case 15:
                case 16:
                    *p = 60; //需量方向改变判断时间固定1min
                    break;

                default:
                    *p = 10;
                    break;
            }
        }

        if (EvStatusInter.Status[1] & D)
        {
            if (!((EvStatusInter.lStatus[1] | nStatus[1]) & D))   //事件结束
            {
                if (*p == 0)
                {
                    *p = 10;
                }
                if (*p)
                {
                    *p = *p - 1;    //倒计时,每秒钟调用该子程序时减一次
                }
                if (*p == 0)
                {
                    EvStatusInter.Status[1] &= ~D;    //倒计时结束，读入最终的状态，最后是用该StatusInter.Status来判断状态字的
                }
            }
        }
        else
        {
            if (EvStatusInter.lStatus[1] & nStatus[1] & D)   //事件发生
            {
                if (*p == 0)
                {
                    *p = 10;
                }
                if (*p)
                {
                    *p = *p - 1;    //倒计时,每秒钟调用该子程序时减一次
                }
                if (*p == 0)
                {
                    EvStatusInter.Status[1] |= D;    //倒计时结束，读入最终的状态，最后是用该StatusInter.Status来判断状态字的
                }
            }
        }
    }

    EvStatusInter.lStatus[0] = nStatus[0];
    EvStatusInter.lStatus[1] = nStatus[1];

    //---合成后台电表状态字---
    fnBkgrd_GetMtStatusWd(EvStatusInter.Status[0], EvStatusInter.Status[1]);
    fnEvent_GetStatus(EvStatusInter.Status[0], EvStatusInter.Status[1]);
    return;
}

#else
//函数：生成电表状态字
//参数：Status0、Status1当前状态。
//返回：无
void fnBkgrd_GetMtStatusWd(u32 Status0, u32 Status1)
{
    u16 MtStatus;

    //---状态字1---
    MtStatus = Bkgrd.PubData.MtSta.MtSta1.Sta;
    if (Bkgrd.PubData.ClockBat < 280)
    {
        MtStatus |= (1 << 2);
        Bkgrd.PubData.EventErr[3] = BKGRD_EVENTERR_CLOCKBATLOW;
        Bkgrd.PubData.MtSysSta.SysStaBit.ClockBat = 1;
    }
    else
    {
        MtStatus &= ~(1 << 2);
        Bkgrd.PubData.EventErr[3] = BKGRD_EVENTERR_OK;
        Bkgrd.PubData.MtSysSta.SysStaBit.ClockBat = 0;
    }

    if (MeasureRms.PubData.DirectSta.DirectBit.Pw)
    {
        MtStatus |= (1 << 4);
    }
    else
    {
        MtStatus &= ~(1 << 4);
    }
    if (MeasureRms.PubData.DirectSta.DirectBit.Qw)
    {
        MtStatus |= (1 << 5);
    }
    else
    {
        MtStatus &= ~(1 << 5);
    }
    if (Bkgrd.PubData.MoneySta.Overdraft)
    {
        MtStatus |= (1 << 14);
    }
    else
    {
        MtStatus &= ~(1 << 14);
    }
    Bkgrd.PubData.MtSta.MtSta1.Sta = MtStatus;

    //---状态字4---
    MtStatus = 0;
    //  if(Status0 & EVGEN_MARK_OVERCURA)   MtStatus |= (1 << 4);
    Bkgrd.PubData.MtSta.MtSta4.Sta = MtStatus + (Bkgrd.PubData.MtSta.MtSta4.Sta & 0xc000);

    //---状态字7---
    MtStatus = 0;

    if (Status0 & EVGEN_MARK_POWDN)
    {
        MtStatus |= (1 << 5);
    }

    if (Key.Press & KEY_VAL_SHELL)
    {
        MtStatus |= (1 << 9);
    }
    if (Key.Press & KEY_VAL_JUNBOX)
    {
        MtStatus |= (1 << 10);
    }

    Bkgrd.PubData.MtSta.MtSta7.Sta = MtStatus;
}

void fnBkgrd_StatusGenerate(void)
{
    u32         nStatus[2];

    //  u32             temp_IL ,temp_IN;
    //  u16              temp16;
    u8              *p, i;
    u32             D;

    if (fnCrc_Check(1, (u8 *)&Trim, sizeof(sTrim_TypeDef) - 2, (u8 *)&Trim.Crc))
    {
        fnFile_Read(FileId_EvtCfgPara, FileItemInfo_EvtCfgPara[0].OffAddr, &Trim, FileLen_EvtCfgPara);
        if (fnCrc_Check(1, (u8 *)&Trim, sizeof(sTrim_TypeDef) - 2, (u8 *)&Trim.Crc))    //E2数据错恢复到默认值
        {
            Std_Memcpy((u8 *)&Trim, (u8 *)&EvtCfgParaDefault, FileLen_EvtCfgPara);
        }
    }

    //---状态产生---
    nStatus[0] = 0 ;
    nStatus[1] = 0;

    if ((MeasureRms.PubData.U[0] < FLOWV_VOL60Un) && (MeasureRms.PubData.U[1] < FLOWV_VOL60Un)
        && (MeasureRms.PubData.U[2] < FLOWV_VOL60Un))
    {
        nStatus[0] |= EVGEN_MARK_POWDN;
    }

    p = (u8 *)&EvStatusInter.tOverCura;
    for (D = 1, i = 0 ; i < 4 ; i++, D <<= 1, p++)
    {
        if (((EvStatusInter.lStatus[0] ^ nStatus[0]) & nStatus[0]) & D)         //事件发生滤波，状态改变,时间定值赋初值
        {
            switch (i)
            {
                //              case 0: //过流
                //                  *p = Trim.VrCur.tOverUpCur ; break;

                case 1:
                    *p = 2;
                    break; //掉电判断时间固定2秒

                //              case 2: //计量芯片异常
                //                  *p = Trim.MrErr.tDly; break;
                //
                //              case 3: //零线电流异常
                //                  *p = Trim.NLineErr.tNLineErr; break;

                default:
                    *p = 1;
                    break;
            }
        }
        if (((EvStatusInter.lStatus[0] ^ nStatus[0]) & EvStatusInter.lStatus[0] & EvStatusInter.Status[0]) & D)     //事件结束滤波
        {
            switch (i)
            {
                //              case 0: //过流
                //                  *p = Trim.VrCur.tOverUpCur ; break;

                case 1:  //掉电判断时间固定2秒
                    *p = 2;
                    break;

                //              case 2: //计量芯片异常
                //                  *p = Trim.MrErr.tDly; break;
                //
                //              case 3: //零线电流异常
                //                  *p = Trim.NLineErr.tNLineErr; break;

                default:
                    *p = 1;
                    break;
            }
        }

        if (EvStatusInter.Status[0] & D)
        {
            if (!((EvStatusInter.lStatus[0] | nStatus[0]) & D))     //事件结束
            {
                if (*p == 0)
                {
                    *p = 10;
                }
                if (*p)
                {
                    *p = *p - 1;    //倒计时,每秒钟调用该子程序时减一次
                }
                if (*p == 0)
                {
                    EvStatusInter.Status[0] &= ~D;    //倒计时结束，读入最终的状态，最后是用该StatusInter.Status来判断状态字的
                }
            }
        }
        else
        {
            if (EvStatusInter.lStatus[0] & nStatus[0] & D)      //事件产生
            {
                if (*p == 0)
                {
                    *p = 10;
                }
                if (*p)
                {
                    *p = *p - 1;    //倒计时,每秒钟调用该子程序时减一次
                }
                if (*p == 0)
                {
                    EvStatusInter.Status[0] |= D;    //倒计时结束，读入最终的状态，最后是用该StatusInter.Status来判断状态字的
                }
            }
        }
    }

    EvStatusInter.lStatus[0] = nStatus[0];
    EvStatusInter.lStatus[1] = nStatus[1];

    //---合成后台电表状态字---
    fnBkgrd_GetMtStatusWd(EvStatusInter.Status[0], EvStatusInter.Status[1]);
    fnEvent_GetStatus(EvStatusInter.Status[0], EvStatusInter.Status[1]);
    return;
}
#endif
/*****************************************************************************
** Function name:fnBkgrd_GetMeasureStatusWd
**
** Description:生成采样状态字
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnBkgrd_GetMeasureStatusWd(void)
{
    u8 i;

    //----有功--------------
    if ((MeasureRms.PubData.DirectSta.Direct == QUADRANT_I) || (MeasureRms.PubData.DirectSta.Direct == QUADRANT_IV))
    {
        Bkgrd.PubData.MeasureSysSta.SysStaBit.PPwDir = 0;  //正向
        Bkgrd.PubData.MeasureSysSta.SysStaBit.PPwaDir = 0;  //正向
    }
    else
    {
        Bkgrd.PubData.MeasureSysSta.SysStaBit.PPwDir = 1;
        Bkgrd.PubData.MeasureSysSta.SysStaBit.PPwaDir = 1;
    }

    //----无功--------------
    if ((MeasureRms.PubData.DirectSta.Direct == QUADRANT_I) || (MeasureRms.PubData.DirectSta.Direct == QUADRANT_II))
    {
        Bkgrd.PubData.MeasureSysSta.SysStaBit.QPwDir = 0;  //正向
        Bkgrd.PubData.MeasureSysSta.SysStaBit.QPwaDir = 0;
    }
    else
    {
        Bkgrd.PubData.MeasureSysSta.SysStaBit.QPwDir = 1;
        Bkgrd.PubData.MeasureSysSta.SysStaBit.QPwaDir = 1;
    }

    for (i = 0; i < 3; i++)
    {
        // 有功潜动
        if (MeasureRegTmp.PQNoLoad & (1 << i))
        {
            MeasureRms.PubData.EMUStatus.EMUSta |= (BIT20 << i);
        }
        else
        {
            MeasureRms.PubData.EMUStatus.EMUSta &= ~(BIT20 << i);
        }
        // 无功潜动
        if (MeasureRegTmp.PQNoLoad & (1 << (i + 4)))
        {
            MeasureRms.PubData.EMUStatus.EMUSta |= (BIT24 << i);
        }
        else
        {
            MeasureRms.PubData.EMUStatus.EMUSta &= ~(BIT24 << i);
        }

        // 有功功率方向
        if (MeasureRegTmp.PDirect & (1 << i))
        {
            Bkgrd.PubData.MeasureSysSta.SysSta |= (BIT1 << i);
        }
        else
        {
            Bkgrd.PubData.MeasureSysSta.SysSta &= ~(BIT1 << i);
        }

        // 无功功率方向
        if (MeasureRegTmp.PDirect & (1 << (i + 4)))
        {
            Bkgrd.PubData.MeasureSysSta.SysSta |= (BIT5 << i);
        }
        else
        {
            Bkgrd.PubData.MeasureSysSta.SysSta &= ~(BIT5 << i);
        }
    }

    // 总有功功率方向
    if (MeasureRegTmp.PDirect & (1 << 3))
    {
        Bkgrd.PubData.MeasureSysSta.SysSta |= (BIT0);
    }
    else
    {
        Bkgrd.PubData.MeasureSysSta.SysSta &= ~(BIT0);
    }
    // 总无功功率方向
    if (MeasureRegTmp.PDirect & (1 << 7))
    {
        Bkgrd.PubData.MeasureSysSta.SysSta |= (BIT4);
    }
    else
    {
        Bkgrd.PubData.MeasureSysSta.SysSta &= ~(BIT4);
    }

    // A相有功与无功都处于潜动---潜动
    if ((MeasureRms.PubData.EMUStatus.EMUStaBit.ANopld == 1)
        && (MeasureRms.PubData.EMUStatus.EMUStaBit.ANoqld == 1))
    {
        Bkgrd.PubData.MeasureSysSta.SysStaBit.Noplda = 1;    //潜动
    }
    else
    {
        Bkgrd.PubData.MeasureSysSta.SysStaBit.Noplda = 0;    //启动
    }
    // B相有功与无功都处于潜动---潜动
    if ((MeasureRms.PubData.EMUStatus.EMUStaBit.BNopld == 1)
        && (MeasureRms.PubData.EMUStatus.EMUStaBit.BNoqld == 1))
    {
        Bkgrd.PubData.MeasureSysSta.SysStaBit.Nopldb = 1;    //潜动
    }
    else
    {
        Bkgrd.PubData.MeasureSysSta.SysStaBit.Nopldb = 0;    //启动
    }
    // C相有功与无功都处于潜动---潜动
    if ((MeasureRms.PubData.EMUStatus.EMUStaBit.CNopld == 1)
        && (MeasureRms.PubData.EMUStatus.EMUStaBit.CNoqld == 1))
    {
        Bkgrd.PubData.MeasureSysSta.SysStaBit.Nopldc = 1;    //潜动
    }
    else
    {
        Bkgrd.PubData.MeasureSysSta.SysStaBit.Nopldc = 0;    //启动
    }

    //电压逆相序判定
    if (Bkgrd.PriPara.WireMode == 0)
    {
        if ((MeasureRms.PubData.U[0] > ClearUValue) &&
            (MeasureRms.PubData.U[1] > ClearUValue) &&
            (MeasureRms.PubData.U[2] > ClearUValue) &&
            (1000 < MeasureRms.PubData.Angle[2]) &&
            (MeasureRms.PubData.Angle[2] < 1400))
        {
            Bkgrd.PubData.MeasureSysSta.SysStaBit.InPhaVol = 1;
        }
        else
        {
            Bkgrd.PubData.MeasureSysSta.SysStaBit.InPhaVol = 0;
        }
    }
    else
    {
        if ((MeasureRms.PubData.U[0] > ClearUValue) &&
            (MeasureRms.PubData.U[2] > ClearUValue) &&
            (1000 < MeasureRms.PubData.Angle[2]) &&
            (MeasureRms.PubData.Angle[2] < 1400))
        {
            Bkgrd.PubData.MeasureSysSta.SysStaBit.InPhaVol = 1;
        }
        else
        {
            Bkgrd.PubData.MeasureSysSta.SysStaBit.InPhaVol = 0;
        }
    }

    //电流逆相序判定
    if (Bkgrd.PriPara.WireMode == 0)
    {
        i = 0;
        if (MeasureRegTmp.Angle[3] > MeasureRegTmp.Angle[2])
        {
            i++;
        }
        if (MeasureRegTmp.Angle[4] > MeasureRegTmp.Angle[3])
        {
            i++;
        }
        if (MeasureRegTmp.Angle[4] > MeasureRegTmp.Angle[2])
        {
            i++;
        }
        if ((MeasureRms.PubData.U[0] > ClearUValue)
            && (MeasureRms.PubData.U[1] > ClearUValue)
            && (MeasureRms.PubData.U[2] > ClearUValue)
            && (abs(MeasureRms.PubData.I[0]) > ClearIValue) /* dyf 电流可能是负值，需要取绝对值，abs() */
            && (abs(MeasureRms.PubData.I[1]) > ClearIValue)
            && (abs(MeasureRms.PubData.I[2]) > ClearIValue)
            && ((i == 2) || (i == 0)))
        {
            Bkgrd.PubData.MeasureSysSta.SysStaBit.InPhaCur = 1;
        }
        else
        {
            Bkgrd.PubData.MeasureSysSta.SysStaBit.InPhaCur = 0;
        }
    }
    else
    {
        i = 0;
        if (MeasureRegTmp.Angle[4] > MeasureRegTmp.Angle[2])
        {
            i++;
        }
        if ((MeasureRms.PubData.U[0] > ClearUValue) &&
            (MeasureRms.PubData.U[2] > ClearUValue) &&
            (MeasureRms.PubData.I[0] > ClearIValue) &&
            (MeasureRms.PubData.I[2] > ClearIValue) &&
            (i == 0))
        {
            Bkgrd.PubData.MeasureSysSta.SysStaBit.InPhaCur = 1;
        }
        else
        {
            Bkgrd.PubData.MeasureSysSta.SysStaBit.InPhaCur = 0;
        }
    }

    Bkgrd.PubData.MeasureSysSta.SysStaBit.MeasureType = 0x03;  //单相
    Bkgrd.PubData.MeasureSysSta.SysStaBit.MeasureUn = 0x02;   //220V
}

/*****************************************************************************
** Function name:fnBkgrd_Exec
**
** Description:根据时间查找任务函数
**                   秒查找，分钟查找，小时查找
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/

void fnBkgrd_Exec(void)
{
    if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON) || (Inactive.PubData.InactiveStamp))
    {
        return;
    }
    fnWDT_Restart();
    Bkgrd.PubData.fChange.Flag = 0 ;
    fnSysDateTimes(&SysDatetimes);
    // 检测载波模块状态，如一直为高电平2S，认为无载波模块
    #if(ZBComFlag)
    if (PinRead_CheckZBSta())
    {
        if (Bkgrd.PubData.CheckZBStamp)
        {
            if (fnStamp_Through(Bkgrd.PubData.OutStamp) > 2000)
            {
                Bkgrd.PubData.CheckZBFlag = 0;
            }
        }
        else
        {
            Bkgrd.PubData.CheckZBStamp = SysStamp ? SysStamp : (SysStamp - 1);
        }
    }
    else
    {
        Bkgrd.PubData.CheckZBStamp = 0;
        Bkgrd.PubData.CheckZBFlag = 1;
    }
    #endif

    fnBsp_CT7538_TempRange();

    if (SysDatetimes.second != Bkgrd.PriData.Second)
    {
        fnBkgrd_Second_Exec();
        //RtcWriteDota中已经调用 SysConfCheck();

        Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_SECOND;
        Bkgrd.PriData.Second = SysDatetimes.second;
    }

    if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON) || (Inactive.PubData.InactiveStamp))
    {
        return;
    }

    if (SysDatetimes.minute != Bkgrd.PriData.Minute)
    {
        fnBkgrd_Minute_Exec();
        Bkgrd.PriData.Minute = SysDatetimes.minute;
        Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_MINUTE;
    }

    if (SysDatetimes.hour != Bkgrd.PriData.Hour)
    {
        fnBkgrd_Hour_Exec();
        Bkgrd.PriData.Hour = SysDatetimes.hour;
        Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_HOUR;
    }
    else if (Bkgrd.PubData.UpDateTimeFlag & BKGRD_FCHANGE_HOUR)
    {
        fnBkgrd_Hour_Exec();
        Bkgrd.PubData.UpDateTimeFlag &= (~BKGRD_FCHANGE_HOUR);
    }

    if (SysDatetimes.day != Bkgrd.PriData.Day)
    {
        fnBkgrd_Day_Exec();
        Bkgrd.PriData.Day = SysDatetimes.day;
        Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_DAY;
    }
    else if (Bkgrd.PubData.UpDateTimeFlag & BKGRD_FCHANGE_DAY)
    {
        fnBkgrd_Day_Exec();
        Bkgrd.PubData.UpDateTimeFlag &= (~BKGRD_FCHANGE_DAY);
    }

    if (SysDatetimes.month != Bkgrd.PriData.Month)
    {
        Bkgrd.PriData.Month = SysDatetimes.month;
        Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_MONTH;
    }

    if (Bkgrd.PubData.Fl != Bkgrd.PriData.Fl)
    {
        //       #if(nPhs==ThreePhs)
        //      Demand.PubData.Fl =     Bkgrd.PubData.Fl;
        //       #endif
        Bkgrd.PriData.Fl = Bkgrd.PubData.Fl;
        Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_FL;
    }
    if (Bkgrd.PubData.nPOT != Bkgrd.PriData.nPOT)
    {
        if (!Bkgrd.PubData.OutStamp)
        {
            Bkgrd.PubData.OutStamp = SysStamp ? SysStamp : (SysStamp - 1);
        }
        if (fnStamp_Through(Bkgrd.PubData.OutStamp) > 20)
        {
            Bkgrd.PriData.nPOT = Bkgrd.PubData.nPOT;
            Bkgrd.PubData.fChange.FlagBit.POT = 1;
            Bkgrd.PubData.OutStamp = 0;
        }
    }

    if (Bkgrd.PubData.UpRunFileFlag == 0x5a)
    {
        Bkgrd.PubData.UpRunFileFlag = 0x00;

        if (BSP_EASM_GetPower() == false) //ESAM电源关闭
        {
            fnWDT_Restart();
            fnEsamOp_EsamInit();   //初始化ESAM IO及SPI配置
        }
        fnUpdateMeterNo();
        fnWDT_Restart();

        fnUpdatePswSta();

        fnUpdateAuthOn();
        fnWDT_Restart();
    }

    if (Bkgrd.PubData.UpFlStatusFlag == 0x5a)
    {
        Bkgrd.PubData.UpFlStatusFlag = 0;
    }

    #if(METERTYPE == 2)
    fnDl645Bkgrd_JudgeAlarm();
    #endif
    if (Bkgrd.PubData.fChange.Flag & BKGRD_FCHANGE_SECOND)
    {
        fnBkgrd_StatusGenerate();
        fnBkgrd_GetMtConfirmStatus();
        #if(METERTYPE)
        fnOutput_CheckGataSta();
        #endif

        fnBkgrd_GetMeasureStatusWd();

        Bkgrd.PubData.fChange.Flag &= ~BKGRD_FCHANGE_SECOND;
    }

    if (Bkgrd.PubData.ZBRSTFlag == 0x5a)
    {
        #if(ZBComFlag)
        PinWrite_ZBRst(0);
        SystemDelay(380);
        PinWrite_ZBRst(1);
        #endif
        Bkgrd.PubData.ZBRSTFlag = 0;
    }
}
