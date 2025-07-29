
#define  _EVENT_GLOBALS
#include <App.h>

//----------编程事件记录标准事件记录单元，不可通讯修改--------------
const   sCList6_TypeDef EvtPrg_StdRecList =
{
    6, 69,
    0x20220200, 4,    0,
    0x201E0200, 7,    4,
    0x20200200, 7,    11,
    0x20240200, 0,    18,    //事件发生源
    0x33000200, 0,    18,
    0x33020206, 51, 18    //51 = 10 * 5 + 1(1byte编程个数)
};

//----EvtPrg_StdRecList 对应的数据类型
const   u8  EvtPrgStdRcdList_DataType[] =
{
    DTYPE_UINT32,
    DTYPE_DATETIME_S,
    DTYPE_DATETIME_S,
    NULL,  //事件发生源
    NULL,
    DTYPE_ARRAY, 10, DTYPE_OAD
};
//----时段表------------
const   sCList7_TypeDef EvtPrgTable_StdRecList =
{
    7, 64,
    0x20220200, 4,    0,
    0x201E0200, 7,    4,
    0x20200200, 7,    11,
    0x20240200, 0,    18,    //事件发生源
    0x33000200, 0,    18,
    0x33140206, 4,    18,
    0x33140207, 42, 22
};
//----EvtPrgTable_StdRecList 对应的数据类型
const   u8  EvtPrgTableStdRcdList_DataType[] =
{
    DTYPE_UINT32,
    DTYPE_DATETIME_S,
    DTYPE_DATETIME_S,
    NULL,  //事件发生源
    NULL,
    DTYPE_OAD,
    DTYPE_ARRAY, 14, DTYPE_STRUCTURE, 3, DTYPE_UINT8, DTYPE_UINT8, DTYPE_UINT8
};

const   sCList7_TypeDef EvtHldy_StdRecList =
{
    7, 28,
    0x20220200, 4,    0,
    0x201E0200, 7,    4,
    0x20200200, 7,    11,
    0x20240200, 0,    18,    //事件发生源
    0x33000200, 0,    18,
    0x33150206, 4,  18,      //
    0x33150207, 6,  22      //
};

//----EvtHldy_StdRecList 对应的数据类型
const   u8  EvtHldyStdRcdList_DataType[] =
{
    DTYPE_UINT32,
    DTYPE_DATETIME_S,
    DTYPE_DATETIME_S,
    NULL,  //事件发生源
    NULL,
    DTYPE_OAD,
    DTYPE_STRUCTURE, 2, DTYPE_DATE, DTYPE_UINT8
};

const   sCList6_TypeDef EvtClr_StdRecList =
{
    6, 22,
    0x20220200, 4,    0,
    0x201E0200, 7,    4,
    0x20200200, 7,    11,
    0x20240200, 0,    18,    //事件发生源
    0x33000200, 0,    18,
    0x330C0206, 4,  18,      //
};

//----EvtHldy_StdRecList 对应的数据类型
const   u8  EvtClrStdRcdList_DataType[] =
{
    DTYPE_UINT32,
    DTYPE_DATETIME_S,
    DTYPE_DATETIME_S,
    NULL,  //事件发生源
    NULL,
    DTYPE_ARRAY, 1, DTYPE_OMD,
};

//------无功组合方式编程事件记录---------------
const   sCList5_TypeDef EvtPrgQ_StdRecList =
{
    5, 19,
    0x20220200, 4,    0,
    0x201E0200, 7,    4,
    0x20200200, 7,    11,
    0x20240200, 1,    18,     //事件发生源
    0x33000200, 0,    19
};

const   u8  EvtPrgQStdRcdList_DataType[] =
{
    DTYPE_UINT32,
    DTYPE_DATETIME_S,
    DTYPE_DATETIME_S,
    DTYPE_ENUM,    //事件发生源
    NULL
};

//------class24标准事件记录单元---------------
const   sCList4_TypeDef EvtC24_StdRecList =
{
    4, 18,
    0x20220200, 4,    0,
    0x201E0200, 7,    4,
    0x20200200, 7,    11,
    0x33000200, 0,    18
};

//------class7标准事件记录单元---------------
const   sCList5_TypeDef EvtC7_StdRecList =
{
    5, 18,
    0x20220200, 4,    0,
    0x201E0200, 7,    4,
    0x20200200, 7,    11,
    0x20240200, 0,    18,     //事件发生源
    0x33000200, 0,    18
};

const   u8  EvtStdRcdList_DataType[] =
{
    DTYPE_UINT32,
    DTYPE_DATETIME_S,
    DTYPE_DATETIME_S,
    NULL,      //事件发生源
    NULL
};

//------------标准事件记录单元--不可通讯修改--------------
const sRecord_ParaDefault_TypeDef EvtStdlist[] =
{
    { FileItemInfoNum_Evt_PowDn, (u8 *) &EvtC7_StdRecList, sizeof(sCList5_TypeDef)   },
    { FileItemInfoNum_Evt_Clr, (u8 *) &EvtC7_StdRecList, sizeof(sCList5_TypeDef)   },
    { FileItemInfoNum_Evt_SetClock, (u8 *) &EvtC7_StdRecList, sizeof(sCList5_TypeDef)   },
    { FileItemInfoNum_Evt_OpenCover, (u8 *) &EvtC7_StdRecList, sizeof(sCList5_TypeDef)     },
    { FileItemInfoNum_Evt_OpenTail, (u8 *) &EvtC7_StdRecList, sizeof(sCList5_TypeDef)     },
    { FileItemInfoNum_Evt_PrgSetPsw, (u8 *) &EvtC7_StdRecList, sizeof(sCList5_TypeDef)     },
    { FileItemInfoNum_Evt_BroadcastTime, (u8 *) &EvtC7_StdRecList, sizeof(sCList5_TypeDef)    },
    { FileItemInfoNum_Evt_MngPlug, (u8 *) &EvtC7_StdRecList, sizeof(sCList5_TypeDef)    },
    { FileItemInfoNum_Evt_MngUpdate, (u8 *) &EvtC7_StdRecList, sizeof(sCList5_TypeDef)    },
};

const sDl645EvConst_TypeDef EvConst[] =
{
    //  {FileItemInfoNum_Evt_OverCur , 0}, //
    {FileItemInfoNum_Evt_MngPlug, 0},   //
    {FileItemInfoNum_Evt_PowDn, 0},   //
    {FileItemInfoNum_Evt_OpenCover, 0},   //
    {FileItemInfoNum_Evt_OpenTail, 0},   //
};

//最大事件记录文件定义
const u8 MAX_EVRECORD_TABLE[] =
{
    MAX_POWDN_EVRECORD,                //最大掉电事件记录 0
    MAX_EVRECORD,                      //最大电表清零事件记录 1
    MAX_EVRECORD,                  //最大校时事件记录 2
    MAX_EVRECORD,                //最大开盖事件记录 3
    MAX_EVRECORD,                //最大开端盖事件记录 4

    MAX_PrgSetPsw_EVRECORD,                //最大密钥更新事件记录 5
    MAX_BrdTime_EVRECORD,       //1 //广播校时 6
    MAX_EVRECORD,                //最大管理模组插拔更新事件记录 7
    MAX_EVRECORD,                //最大管理模组升级事件记录 8
    MAX_EVRECORD,       //1     //9
};

const u16 MAX_EVTFLASHCNT_TABLE[] =
{
    MAX_PowDnEvt_FlashCnt,
    MAX_ClrEvt_FlashCnt,
    MAX_SetClockEvt_FlashCnt,
    MAX_OpenCoverEvt_FlashCnt,
    MAX_OpenTailEvt_FlashCnt,

    MAX_PrgSetPswEvt_FlashCnt,
    MAX_BroadcastTimeEvt_FlashCnt,
    MAX_MngPlugEvt_FlashCnt,
    MAX_MngUpdateEvt_FlashCnt,
    MAX_EVRECORD,
};

// 停电电压电流数据
void fnEvtVoltLoss_PowerDwn(void)
{
    sPwdnVoltCurTypedef Volt;

    fnRCClock_Init();
    fnFm24c256_Init();

    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);

    if (Inactive.EvtPwn.EvtVoltLoss != 0x5A)
    {
        fnMeasure_EvtVoltLoss();

        // 同步系统时钟
        fnSysDateTimes(&SysDatetimes);

        // 停电时间
        memcpy(&Volt.PwdnTime.second, &SysDatetimes.second, sizeof(sDate_time_s_TypeDef));

        // 电压数据
        Volt.VoltVal[0] = MeasureRms.PubData.U[0] / 100;
        Volt.VoltVal[1] = MeasureRms.PubData.U[1] / 100;
        Volt.VoltVal[2] = MeasureRms.PubData.U[2] / 100;

        // 电流数据
        Volt.CurVal[0] = MeasureRms.PubData.I[0] / 10;
        Volt.CurVal[1] = MeasureRms.PubData.I[1] / 10;
        Volt.CurVal[2] = MeasureRms.PubData.I[2] / 10;

        // 保存数据
        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_PwdnVoltLoss, &Volt.PwdnTime.second, FileItemInfoLen_HighState_PwdnVoltLoss);

        Inactive.EvtPwn.EvtVoltLoss = 0x5A;
        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                     &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
    }

    fnPowerDown_SleepWakeOpIO();
    fnSubClock_Init();
}

// 上电补齐开盖事件记录
void fnEvtCoverTail_PowerOn(void)
{
    u32 OffAddr;
    u16 len;
    sEvtRcdHead_TypeDef  headData;

    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);

    len = sizeof(sEvtRcdHead_TypeDef);
    OffAddr = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_OpenCover].OffAddr;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len);

    // 之前为开盖状态
    if ((fnJudge_Zero((u8 *)&headData.EventStartTime, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Zero((u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        // 补合盖记录
        if ((Inactive.EvtPwn.CoverClose == 0x5A)
            && (fnJudge_Zero((u8 *)&Inactive.EvtPwn.CoverCloseTime, sizeof(sDate_time_s_TypeDef)) == FALSE))
        {
            fnEvent_Operation(FileItemInfoNum_Evt_OpenCover, EVTEND, (u8 *)&Inactive.EvtPwn.CoverCloseTime);

            Inactive.EvtPwn.CoverClose = 0;
            memset(&Inactive.EvtPwn.CoverCloseTime, 0, sizeof(sDate_time_s_TypeDef));

            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                         &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
        }
    }
    else
    {
        // 补开盖记录
        if ((Inactive.EvtPwn.CoverOpen == 0x5A)
            && (fnJudge_Zero((u8 *)&Inactive.EvtPwn.CoverOpenTime, sizeof(sDate_time_s_TypeDef)) == FALSE))
        {
            fnEvent_Operation(FileItemInfoNum_Evt_OpenCover, EVTSTART, (u8 *)&Inactive.EvtPwn.CoverOpenTime);

            Inactive.EvtPwn.CoverOpen = 0;
            memset(&Inactive.EvtPwn.CoverOpenTime, 0, sizeof(sDate_time_s_TypeDef));

            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                         &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
        }

        // 补合盖记录
        if ((Inactive.EvtPwn.CoverClose == 0x5A)
            && (fnJudge_Zero((u8 *)&Inactive.EvtPwn.CoverCloseTime, sizeof(sDate_time_s_TypeDef)) == FALSE))
        {
            fnEvent_Operation(FileItemInfoNum_Evt_OpenCover, EVTEND, (u8 *)&Inactive.EvtPwn.CoverCloseTime);

            Inactive.EvtPwn.CoverClose = 0;
            memset(&Inactive.EvtPwn.CoverCloseTime, 0, sizeof(sDate_time_s_TypeDef));

            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                         &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
        }
    }

    // 开端妞盖记录
    OffAddr = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_OpenTail].OffAddr;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len);

    // 之前为开盖状态
    if ((fnJudge_Zero((u8 *)&headData.EventStartTime, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Zero((u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        // 补合盖记录
        if ((Inactive.EvtPwn.TailClose == 0x5A)
            && (fnJudge_Zero((u8 *)&Inactive.EvtPwn.TailCloseTime, sizeof(sDate_time_s_TypeDef)) == FALSE))
        {
            fnEvent_Operation(FileItemInfoNum_Evt_OpenTail, EVTEND, (u8 *)&Inactive.EvtPwn.TailCloseTime);

            Inactive.EvtPwn.TailClose = 0;
            memset(&Inactive.EvtPwn.TailCloseTime, 0, sizeof(sDate_time_s_TypeDef));

            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                         &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
        }
    }
    else
    {
        // 补开盖记录
        if ((Inactive.EvtPwn.TailOpen == 0x5A)
            && (fnJudge_Zero((u8 *)&Inactive.EvtPwn.TailOpenTime, sizeof(sDate_time_s_TypeDef)) == FALSE))
        {
            fnEvent_Operation(FileItemInfoNum_Evt_OpenTail, EVTSTART, (u8 *)&Inactive.EvtPwn.TailOpenTime);

            Inactive.EvtPwn.TailOpen = 0;
            memset(&Inactive.EvtPwn.TailOpenTime, 0, sizeof(sDate_time_s_TypeDef));

            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                         &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
        }

        // 补合盖记录
        if ((Inactive.EvtPwn.TailClose == 0x5A)
            && (fnJudge_Zero((u8 *)&Inactive.EvtPwn.TailCloseTime, sizeof(sDate_time_s_TypeDef)) == FALSE))
        {
            fnEvent_Operation(FileItemInfoNum_Evt_OpenTail, EVTEND, (u8 *)&Inactive.EvtPwn.TailCloseTime);

            Inactive.EvtPwn.TailClose = 0;
            memset(&Inactive.EvtPwn.TailCloseTime, 0, sizeof(sDate_time_s_TypeDef));

            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                         &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
        }
    }

    // 清停电期间电压电流数据保存标志
    Inactive.EvtPwn.EvtVoltLoss = 0;
    Inactive.PubData.QLossVolTime = 0;
    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                 &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
}

// 掉电开盖记录
void fnEvtCoverTail_PwDn(void)
{
    //u32 OffAddr;
    //u16 len;
    //sEvtRcdHead_TypeDef  headData;

    if (0 == (Inactive.InactiveFlag.fChange & 0x0C))
    {
        return;
    }

    fnRCClock_Init();
    //  fnMainClock_Init();
    fnBufTemp_Init();

    SystemDelayUs(10);

    if (Inactive.InactiveFlag.fChange & 0x04)
    {
        Rn8xxx_GPIO_CfgFun(PinKCOVER, _INTRUPT);
        Rn8xxx_GPIO_CfgIOMode(PinKCOVER, GPIO_MODE_IN, NORMAL_IN);

        // 表盖记录
        if (PinRead_KeyShell())
        {
            Key.Release |= 0X0040;          //记录合盖记录用
            Key.Press &= 0XFFBF;
        }
        else
        {
            Key.Press |= 0X0040;
            Key.Release &= 0XFFBF;
        }
    }

    // 同步系统时钟
    fnSysDateTimes(&SysDatetimes);

    //  len = sizeof(sEvtRcdHead_TypeDef);
    //  OffAddr = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_OpenCover].OffAddr;

    //  I2C_Clk_En;
    fnFm24c256_Init();
    //  fnPowerDown_SetWakeOpIO();

    //  fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len );

    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);

    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_MngPlugSta,
                &Inactive.Mng.Sta, FileItemInfoLen_HighState_MngPlugSta + FileItemInfoLen_HighState_EvtFlag);

    if (Inactive.InactiveFlag.fChange & 0x04)
    {
        // 之前为开盖状态
        if (Inactive.Mng.Sta & EvtSta_OpenCover)
        {
            // 合盖
            if (Key.Release & KEY_VAL_SHELL)
            {
                Key.Release &= ~KEY_VAL_SHELL;
                Inactive.EvtPwn.CoverClose = 0x5A;
                Std_Memcpy((u8 *)&Inactive.EvtPwn.CoverCloseTime.second, (u8 *)&SysDatetimes.second, sizeof(sDate_time_s_TypeDef));

                Inactive.Mng.LstEvtFlag &= ~((u32)1 << EVENT_STYLE_SHELL);

                Inactive.Mng.Sta &= ~EvtSta_OpenCover;

                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                             &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);

                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_MngPlugSta,
                             &Inactive.Mng.Sta, FileItemInfoLen_HighState_MngPlugSta + FileItemInfoLen_HighState_EvtFlag);

                // 关闭开盖IO口中断
                Rn8xxx_INTC_Init(INTC_ID1, INTC_DoubleEdge, INTC_IRQ_DISABLE);

                Rn8xxx_GPIO_CfgFun(PinKCOVER, _NORMALIO);

                I2C_Clk_Dis;
            }
        }
        else
        {
            // 开盖
            if (Key.Press & KEY_VAL_SHELL)
            {
                Key.Press &= ~KEY_VAL_SHELL;
                Inactive.EvtPwn.CoverOpen = 0x5A;
                Std_Memcpy((u8 *)&Inactive.EvtPwn.CoverOpenTime.second, (u8 *)&SysDatetimes.second, sizeof(sDate_time_s_TypeDef));

                Inactive.Mng.LstEvtFlag |= ((u32)1 << EVENT_STYLE_SHELL);

                Inactive.Mng.Sta |= EvtSta_OpenCover;

                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                             &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);

                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_MngPlugSta,
                             &Inactive.Mng.Sta, FileItemInfoLen_HighState_MngPlugSta + FileItemInfoLen_HighState_EvtFlag);
            }
        }

        Inactive.InactiveFlag.fChange &= ~0x04;
    }

    if (Inactive.InactiveFlag.fChange & 0x08)
    {
        // 开端钮盖
        // 之前为开盖状态
        if (Inactive.Mng.Sta & EvtSta_OpenTail)
        {
            // 合盖
            if (Key.Release & KEY_VAL_JUNBOX)
            {
                Key.Release &= ~KEY_VAL_JUNBOX;
                Inactive.EvtPwn.TailClose = 0x5A;
                Std_Memcpy((u8 *)&Inactive.EvtPwn.TailCloseTime.second, (u8 *)&SysDatetimes.second, sizeof(sDate_time_s_TypeDef));

                Inactive.Mng.LstEvtFlag &= ~((u32)1 << EVENT_STYLE_JUNBOX);

                Inactive.Mng.Sta &= ~EvtSta_OpenTail;

                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                             &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);

                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_MngPlugSta,
                             &Inactive.Mng.Sta, FileItemInfoLen_HighState_MngPlugSta + FileItemInfoLen_HighState_EvtFlag);

                // 关闭开盖IO口中断
                //              Rn8xxx_INTC_Init(INTC_ID1,INTC_DoubleEdge,INTC_IRQ_DISABLE);
                Rn8xxx_KBI_Init(KBI_ID3, KBI_FallingEdge, KBI_IRQ_DISABLE);

                Rn8xxx_GPIO_CfgFun(PinKBTMBOX, _NORMALIO);

                I2C_Clk_Dis;
            }
        }
        else
        {
            // 开盖
            if (Key.Press & KEY_VAL_JUNBOX)
            {
                Key.Press &= ~KEY_VAL_JUNBOX;
                Inactive.EvtPwn.TailOpen = 0x5A;
                Std_Memcpy((u8 *)&Inactive.EvtPwn.TailOpenTime.second, (u8 *)&SysDatetimes.second, sizeof(sDate_time_s_TypeDef));

                Inactive.Mng.LstEvtFlag |= ((u32)1 << EVENT_STYLE_JUNBOX);

                Inactive.Mng.Sta |= EvtSta_OpenTail;

                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                             &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);

                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_MngPlugSta,
                             &Inactive.Mng.Sta, FileItemInfoLen_HighState_MngPlugSta + FileItemInfoLen_HighState_EvtFlag);

                Rn8xxx_KBI_Init(KBI_ID3, KBI_RisingEdge, KBI_IRQ_ENABLE);
            }
        }

        Inactive.InactiveFlag.fChange &= ~0x08;
    }

    fnPowerDown_SleepWakeOpIO();

    fnSubClock_Init();
}

void fnGetEvtMngUpdateRcd(u8 *pDst, u8 *pSrc, u32 iOAD, u16 ilen)
{
    u16 iOffset = 0;
    u8 ik, nlen;

    switch (iOAD)
    {
        case 0x40272300:        // 升级操作类型
            pDst[0] = pSrc[1];
            break;
        case 0x00102200:        // 升级前正向有功总电能
            //      case 0x00102201:
            if (pSrc[4] == 0x06)
            {
                nlen = 4;
            }
            for (ik = 0; ik < pSrc[3]; ik++)
            {
                Std_MemRvs(pDst + nlen * ik, &pSrc[5 + ik * (nlen + 1)], nlen);
            }
            break;
        case 0x00202200:        // 升级前反向有功总电能
            //      case 0x00202201:
            if (pSrc[4] == 0x06)
            {
                nlen = 4;
                iOffset = pSrc[3] * (4 + 1);
            }
            iOffset += 6;
            for (ik = 0; ik < pSrc[3]; ik++)
            {
                Std_MemRvs(pDst + nlen * ik, &pSrc[iOffset + 1 + ik * (nlen + 1)], nlen);
            }
            //          Std_MemRvs(pDst, &pSrc[iOffset + 1], ilen);
            break;
        case 0xF0012500:        // 下载方标识
            if (pSrc[4] == 0x06)
            {
                iOffset = pSrc[3] * (4 + 1) * 2;
            }
            iOffset += 6;
            memset(pDst, 0, ilen);
            memcpy(pDst, &pSrc[iOffset + 2], pSrc[iOffset + 1]);
            break;
        case 0xF4022204:        // 升级前软件版本号
            if (pSrc[4] == 0x06)
            {
                iOffset = pSrc[3] * (4 + 1) * 2;
            }
            iOffset += 6;
            iOffset += pSrc[iOffset + 1];
            iOffset += 2;

            memset(pDst, 0, ilen);
            memcpy(pDst, &pSrc[iOffset + 2], pSrc[iOffset + 1]);
            break;
        case 0xF4028204:        // 升级后软件版本号
            if (pSrc[4] == 0x06)
            {
                iOffset = pSrc[3] * (4 + 1) * 2;
            }
            iOffset += 6;
            iOffset += pSrc[iOffset + 1];
            iOffset += 2;

            iOffset += pSrc[iOffset + 1];
            iOffset += 2;

            memset(pDst, 0, ilen);
            memcpy(pDst, &pSrc[iOffset + 2], pSrc[iOffset + 1]);
            break;
        case 0xF4028202:        // 升级应用名称
            if (pSrc[4] == 0x06)
            {
                iOffset = pSrc[3] * (4 + 1) * 2;
            }
            iOffset += 6;
            iOffset += pSrc[iOffset + 1];
            iOffset += 2;

            iOffset += pSrc[iOffset + 1];
            iOffset += 2;

            iOffset += pSrc[iOffset + 1];
            iOffset += 2;

            memset(pDst, 0, ilen);
            memcpy(pDst, &pSrc[iOffset + 2], pSrc[iOffset + 1]);
            break;
        case 0x40278200:        // 升级结果
            if (pSrc[4] == 0x06)
            {
                iOffset = pSrc[3] * (4 + 1) * 2;
            }
            iOffset += 6;
            iOffset += pSrc[iOffset + 1];
            iOffset += 2;

            iOffset += pSrc[iOffset + 1];
            iOffset += 2;

            iOffset += pSrc[iOffset + 1];
            iOffset += 2;

            iOffset += pSrc[iOffset + 1];
            iOffset += 2;

            //          memcpy(pDst, &pSrc[iOffset + 1], pSrc[iOffset + 1]);
            pDst[0] = pSrc[iOffset + 1];
            break;
        default :

            break;
    }
}

void fnEvent_Operation(u8 item, u8 mode, u8 *Buff)
{
    u8       j;

    u32     OffAddr = 0;

    u8  *DataBuf, *EvtData;
    sEvtRcdHead_TypeDef  headData;
    sContextList_TypeDef    tmplist;
    u8 listOADSumNum;
    u16 recordlen, maxcnt_u16, len;
    OAD_Analyse_TypeDef *pOad;
    //sHolidayTable_TypeDef  hldy_buf;
    if ((Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN) && (item != FileItemInfoNum_Evt_OpenCover))
    {
        return;
    }

    if (item >= FileItemInfoNum_Evt_Max)
    {
        return;
    }

    DataBuf = (u8 *)fnBufTemp_Alloc(512);
    if (DataBuf == NULL)
    {
        return ;
    }
    Std_Memset(DataBuf, 0, 512);

    EvtData = (u8 *)fnBufTemp_Alloc(512);
    if (EvtData == NULL)
    {
        return ;
    }
    Std_Memset(EvtData, 0, 512);

    len = sizeof(sEvtRcdHead_TypeDef);
    OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len);

    maxcnt_u16 = (u16)MAX_EVRECORD_TABLE[item];    //获取最大记录数

    if ((item == FileItemInfoNum_Evt_SetClock) || (item == FileItemInfoNum_Evt_BroadcastTime))
    {
        Std_Memcpy((u8 *)&headData.EventStartTime, Buff, 7);
        fnGetCurrTime(&headData.EventEndTime);
        //-------class7标准事件记录单元--------------
        Std_Memcpy(EvtData, (u8 *)&headData.EventSumCnt, EvtC7_StdRecList.reclen);   //序号从0开始

        if (item == FileItemInfoNum_Evt_SetClock)
        {
            Bkgrd.PubData.MtSysSta.SysStaBit.EvtSetClock = 1;
        }
        else
        {
            Bkgrd.PubData.MtSysSta.SysStaBit.EvtBroadcastTime = 1;
        }
    }
    else
    {
        if (mode == EVTSTART)
        {
            fnGetCurrTime(&headData.EventStartTime);  //事件起始时间
            Std_Memset((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef));      //清零结束时间

            if (Buff != NULL)
            {
                // 管理模组升级事件
                if (item == FileItemInfoNum_Evt_MngUpdate)
                {
                    Std_MemRvs((u8 *)&headData.EventStartTime, &Buff[3], sizeof(sDate_time_s_TypeDef));
                    Std_MemRvs((u8 *)&headData.EventEndTime, &Buff[11], sizeof(sDate_time_s_TypeDef));
                    headData.nTarf = Buff[21] - 1;
                }
                // 补掉电开盖事件时间
                else if ((item == FileItemInfoNum_Evt_OpenCover) || (item == FileItemInfoNum_Evt_OpenTail))
                {
                    Std_Memcpy((u8 *)&headData.EventStartTime, Buff, sizeof(sDate_time_s_TypeDef));
                }
                // 补掉电事件记录时间
                else if (item == FileItemInfoNum_Evt_PowDn)
                {
                    Std_Memcpy((u8 *)&headData.EventStartTime, Buff, sizeof(sDate_time_s_TypeDef));
                }
            }

            Std_Memcpy(EvtData, (u8 *)&headData.EventSumCnt, EvtC7_StdRecList.reclen);      //序号从0开始
        }
        else
        {
            //--------要读取原事件记录起始时产生的数据-------------
            OffAddr = FileItemInfo_EvtCtxlist[item].OffAddr;
            fnFile_Read(FileId_EvtCtxlist, OffAddr, DataBuf, 3);

            Std_Memcpy((u8 *)&recordlen, DataBuf + 1, 2);

            if (headData.EventSumCnt % maxcnt_u16)
            {
                OffAddr = ((headData.EventSumCnt % maxcnt_u16) - 1) * (u32)recordlen;
            }
            else
            {
                OffAddr = (maxcnt_u16 - 1) * (u32)recordlen;
            }
            //----------------------------------
            OffAddr += FileItemInfo_EvtRecord[item].OffAddr ;
            fnFile_Read(FileId_EvtRecord, OffAddr, EvtData, recordlen);

            if ((item == FileItemInfoNum_Evt_MngPlug) && (Buff != NULL))
            {
                u8 ik;
                for (ik = 0; ik < 8; ik++)
                {
                    if (Buff[ik] != 0xFF)
                    {
                        break;
                    }
                }

                if (ik < 8)
                {
                    //更新管理芯插拔事件记录ESAM序列号
                    Std_Memcpy(EvtData + EvtMngPlugNewEsamOffset, Buff, 8);
                    fnFile_Write(FileId_EvtRecord, OffAddr, EvtData, recordlen);

                    fnBufTemp_Free(DataBuf);
                    fnBufTemp_Free(EvtData);
                    return;
                }
            }

            fnGetCurrTime(&headData.EventEndTime);

            if (Buff != NULL)
            {
                // 补掉电开盖事件时间
                if ((item == FileItemInfoNum_Evt_OpenCover) || (item == FileItemInfoNum_Evt_OpenTail))
                {
                    Std_Memcpy((u8 *)&headData.EventEndTime, Buff, sizeof(sDate_time_s_TypeDef));
                }
            }

            Std_Memcpy(EvtData + 11, (u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef));  //更新事件记录结束时间
        }
    }
    //-------根据关联对象属性表获取数据-----------------
    //-----读取关联对象属性表---------
    len = FileItemInfo_EvtCtxlist[item].Len;
    OffAddr = FileItemInfo_EvtCtxlist[item].OffAddr;
    fnFile_Read(FileId_EvtCtxlist, OffAddr, DataBuf, len);

    listOADSumNum = *DataBuf++;
    Std_Memcpy((u8 *)&recordlen, DataBuf, 2);
    DataBuf += 2;

    //-------关联对象属性表合法性判断------------------
    if ((recordlen > MAX_RCDLEN) || (listOADSumNum > 100)) //容错处理，不超过100个OAD
    {
        fnBufTemp_Free(DataBuf);
        fnBufTemp_Free(EvtData);
        return;
    }

    for (j = 0; j < listOADSumNum; j++)
    {
        Std_Memcpy(&tmplist, DataBuf, sizeof(sContextList_TypeDef));
        DataBuf += sizeof(sContextList_TypeDef);
        pOad  = (OAD_Analyse_TypeDef *)&tmplist.OAD;
        if (mode == EVTSTART)
        {
            if ((item == FileItemInfoNum_Evt_PrgSetPsw) && (tmplist.OAD == 0xF1002400)) //密钥更新事件记录，更新前密钥版本号
            {
                Std_MemRvs(EvtData + tmplist.OffPos, Buff, tmplist.len);
            }
            // 管理芯插拔事件记录 ESAM序列号
            else if ((item == FileItemInfoNum_Evt_MngPlug) && (tmplist.OAD == 0xF1002200))
            {
                fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_EvtRcdBfEsam, EvtData + tmplist.OffPos, FileItemInfoLen_HighState_EvtRcdBfEsam);
            }
            // 管理芯升级事件
            else if (item == FileItemInfoNum_Evt_MngUpdate)
            {
                fnGetEvtMngUpdateRcd(EvtData + tmplist.OffPos, &Buff[18], tmplist.OAD, tmplist.len);
            }
            else
            {
                // 起始同时结束的事件
                if (item == FileItemInfoNum_Evt_SetClock)
                {
                    if ((pOad->AtrFeature == EVT_HAP_BEFORE) || (pOad->AtrFeature == EVT_HAP_AFTER) ||
                        (pOad->AtrFeature == EVT_END_BEFORE) || (pOad->AtrFeature == EVT_END_AFTER))
                    {
                        tmplist.len = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF), EvtData + tmplist.OffPos);
                    }
                }
                else
                {
                    if ((pOad->AtrFeature == EVT_HAP_BEFORE) || (pOad->AtrFeature == EVT_HAP_AFTER))
                    {
                        tmplist.len = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF), EvtData + tmplist.OffPos);
                    }
                }
            }
        }
        else
        {
            if ((item == FileItemInfoNum_Evt_MngPlug) && (tmplist.OAD == 0xF1008200) && (mode == EVTEND))
            {
                if (Buff == NULL)
                {
                    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_EvtRcdAfterEsam, EvtData + tmplist.OffPos, FileItemInfoLen_HighState_EvtRcdAftEsam);
                }
                else
                {
                    memcpy(EvtData + tmplist.OffPos, Buff, FileItemInfoLen_HighState_EvtRcdAftEsam);
                }
            }
            else
            {
                if ((pOad->AtrFeature == EVT_END_BEFORE) || (pOad->AtrFeature == EVT_END_AFTER))
                {
                    tmplist.len = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF), EvtData + tmplist.OffPos);
                }
            }
        }
    }

    if (mode == EVTSTART)
    {
        if (headData.EventCnt < maxcnt_u16)
        {
            headData.EventCnt ++;    //
        }

        headData.EventSumCnt ++;
    }

    if (headData.EventSumCnt % maxcnt_u16)
    {
        OffAddr = ((headData.EventSumCnt % maxcnt_u16) - 1) * (u32)recordlen;
    }
    else
    {
        OffAddr = (maxcnt_u16 - 1) * (u32)recordlen;
    }

    OffAddr += FileItemInfo_EvtRecord[item].OffAddr;

    fnFile_Write(FileId_EvtRecord, OffAddr, EvtData, recordlen);

    len = sizeof(sEvtRcdHead_TypeDef);
    OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr;
    fnFile_Write(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len);

    fnEvent_Report(item, 0, mode);

    fnBufTemp_Free(DataBuf);
    fnBufTemp_Free(EvtData);
}

void fnDl645Event_Operation(u8 Style, u8 Way, u8 *OpCode, u8 *Buff)
{
}

/*********************************************************************************************************
** Function name:   fnEvent_Clr_Status
** Descriptions:    事件记录状态变量清零
** input parameters:  item 事件记录序号，=0xFF 全清；
**                            nphase  分项A相=0 ; B相=1; C相=2; 分相全清=0xFF
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnEvent_Clr_Status(u8 item, u8  nphase)
{
    u8 i, j, nphase_max;

    uEventFlag_TypeDef  falg;

    if ((item > FileItemInfoNum_Evt_Max) && (item != 0xFF))
    {
        return;
    }

    if ((nphase > 2) && (nphase != 0xFF))
    {
        return;
    }

    if (item == 0xFF) //全清
    {
        Std_Memset((u8 *)&EvStatusInter, 0, sizeof(sEvStatusInter_TypeDef));

        for (i = 0; i < MAX_EVENTTYPE; i++)
        {
            Event.EvtSumTime[i] = 0;
        }

        Std_Memset((u8 *)&Event, 0, sizeof(sEvent_TypeDef));

        fnEvent_Clr_BroadstaSta();
        fnEvent_Clr_PrgQSta();
        fnEvent_Clr_PowDnDatetimes();
        fnClr_EvtReportData(0xFF, 0, 0xFF);
    }
    else
    {
        if (item == FileItemInfoNum_Evt_BroadcastTime)
        {
            fnEvent_Clr_BroadstaSta();
        }

        //      else if(item == FileItemInfoNum_Evt_PrgQ)
        //          fnEvent_Clr_PrgQSta();
        else if (item == FileItemInfoNum_Evt_PowDn)
        {
            fnEvent_Clr_PowDnDatetimes();
        }

        for (i = 0; i < MAX_EVENTTYPE; i++)
        {
            if (nphase == 0xFF)
            {
                if (item == EvConst[i].FileId)
                {
                    //???
                    //                  if( item < FileItemInfoNum_Evt_QtOverNeed )
                    //                      nphase_max = 3;
                    //                  else if( item < FileItemInfoNum_Evt_PtOverNeed )
                    //                      nphase_max = 4;
                    //                  else
                    nphase_max = 1;

                    for (j = 0; j < nphase_max ; j++)
                    {
                        Event.EvtSumTime[i + j] = 0;

                        if ((i + j) < 32)
                        {
                            falg.EvFlag.EvFlagData0 = ((u32)1 << (i + j));
                            falg.EvFlag.EvFlagData1 = 0;
                        }
                        else
                        {
                            falg.EvFlag.EvFlagData0 = 0;
                            falg.EvFlag.EvFlagData1 = ((u32)1 << ((i + j) - 32));
                        }

                        EvStatusInter.Status[0] &= ~falg.EvFlag.EvFlagData0;
                        EvStatusInter.lStatus[0] &= ~falg.EvFlag.EvFlagData0;

                        EvStatusInter.Status[1] &= ~falg.EvFlag.EvFlagData1;
                        EvStatusInter.lStatus[1] &= ~falg.EvFlag.EvFlagData1;

                        fnClr_EvtReportData(item, j, SCOM_PORT_ZBCOM);
                        fnClr_EvtReportData(item, j, SCOM_PORT_RS485A);
                        fnClr_EvtReportData(item, j, SCOM_PORT_RS485B);
                    }

                    break;
                }
            }
            if ((item == EvConst[i].FileId) && (nphase == EvConst[i].nPha))
            {
                Event.EvtSumTime[i] = 0;

                if (i < 32)
                {
                    falg.EvFlag.EvFlagData0 = ((u32)1 << i);
                    falg.EvFlag.EvFlagData1 = 0;
                }
                else
                {
                    falg.EvFlag.EvFlagData0 = 0;
                    falg.EvFlag.EvFlagData1 = ((u32)1 << (i - 32));
                }

                EvStatusInter.Status[0] &= ~falg.EvFlag.EvFlagData0;
                EvStatusInter.lStatus[0] &= ~falg.EvFlag.EvFlagData0;

                EvStatusInter.Status[1] &= ~falg.EvFlag.EvFlagData1;
                EvStatusInter.lStatus[1] &= ~falg.EvFlag.EvFlagData1;

                fnClr_EvtReportData(item, nphase, SCOM_PORT_ZBCOM);
                fnClr_EvtReportData(item, nphase, SCOM_PORT_RS485A);
                fnClr_EvtReportData(item, nphase, SCOM_PORT_RS485B);

                break;
            }
        }

        if (i == MAX_EVENTTYPE)
        {
            return;
        }
    }

    fnBkgrd_GetMtStatusWd(EvStatusInter.Status[0], EvStatusInter.Status[1]);
    fnEvent_GetStatus(EvStatusInter.Status[0], EvStatusInter.Status[1]);

    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_EvStatus, &EvStatusInter, sizeof(sEvStatusInter_TypeDef));
    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtSumTime, (u8 *)&Event.EvtSumTime[0], FileItemInfoLen_HighState_EvtSumTime);
}

//============================================

void fnEvent_GetStatus(u32 Status0, u32 Status1)
{
    if (Status0 & EVGEN_MARK_POWDN)
    {
        Event.StartFlag.EvFlagBit.PowDn = 1;
    }
    else
    {
        Event.StartFlag.EvFlagBit.PowDn = 0;
    }
}

void fnEvent_Init(void)
{
    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }

    Std_Memset((u8 *)&Event.StartFlag, 0, sizeof(uEventFlag_TypeDef));
    Std_Memset((u8 *)&Event.ExecFlag, 0, sizeof(uEventFlag_TypeDef));
    Std_Memset((u8 *)&Event.PriData.Step, 0, 20);

    EvStatusInter.lStatus[0] = 0 ;
    EvStatusInter.lStatus[1] = 0 ;
    EvStatusInter.Status[0] = 0 ;
    EvStatusInter.Status[1] = 0 ;

    Std_Memset((u8 *)&EvStatusInter, 0x00, MAX_EVENTTYPE);

    fnEvtMngPlug_Init();

    fnCheck_ReportPara();
}

//--------分项事件---------------------------
void fnEvent_nphsEvt_Exec(void)
{
    uEventFlag_TypeDef  fEventStart, fEventTerm; //事件启动/进行 /终止标志

    u8      i, j, item, nphase;
    uEventFlag_TypeDef  D;
    u32     OffAddr = 0;

    u8  *DataBuf, *EvtData;
    sEvtRcdHead_TypeDef  headData;
    sContextList_TypeDef    tmplist;
    u8 listOADSumNum ;
    u16 recordlen, maxcnt_u16, len;
    OAD_Analyse_TypeDef *pOad;

    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }

    //-------class24 根据触发标志产生对应事件记录---------------------------
    fnWDT_Restart();

    fEventStart.EvFlag.EvFlagData0 = Event.StartFlag.EvFlag.EvFlagData0 & (~Event.ExecFlag.EvFlag.EvFlagData0);
    fEventStart.EvFlag.EvFlagData1 = Event.StartFlag.EvFlag.EvFlagData1 & (~Event.ExecFlag.EvFlag.EvFlagData1);

    fEventTerm.EvFlag.EvFlagData0 = (~Event.StartFlag.EvFlag.EvFlagData0) & Event.ExecFlag.EvFlag.EvFlagData0;
    fEventTerm.EvFlag.EvFlagData1 = (~Event.StartFlag.EvFlag.EvFlagData1) & Event.ExecFlag.EvFlag.EvFlagData1;

    DataBuf = (u8 *)fnBufTemp_Alloc(512);
    if (DataBuf == NULL)
    {
        return ;
    }
    Std_Memset(DataBuf, 0, 512);

    EvtData = (u8 *)fnBufTemp_Alloc(512);
    if (EvtData == NULL)
    {
        return ;
    }
    Std_Memset(EvtData, 0, 512);

    //---事件启动---
    if (fEventStart.EvFlag.EvFlagData0 | fEventStart.EvFlag.EvFlagData1)
    {
        for (D.EvFlag.EvFlagData0 = 1, D.EvFlag.EvFlagData1 = 0, i = 0 ; i < MAX_EVENTTYPE ; i++, D.EvFlag.EvFlagData0 = D.EvFlag.EvFlagData0 << 1, D.EvFlag.EvFlagData1 = D.EvFlag.EvFlagData1 << 1)
        {
            if (D.EvFlag.EvFlagData0 == 0 && D.EvFlag.EvFlagData1 == 0)
            {
                D.EvFlag.EvFlagData1 = 1 ;
            }

            if ((fEventStart.EvFlag.EvFlagData0 & D.EvFlag.EvFlagData0) | (fEventStart.EvFlag.EvFlagData1 & D.EvFlag.EvFlagData1))
            {
                item = EvConst[i].FileId;
                if (item != FileItemInfoNum_Evt_PowDn)
                {
                    Event.ExecFlag.EvFlag.EvFlagData0 |= D.EvFlag.EvFlagData0;      //完成事件启动
                    Event.ExecFlag.EvFlag.EvFlagData1 |= D.EvFlag.EvFlagData1;      //完成事件启动
                    continue;
                }
                nphase = EvConst[i].nPha;

                len = sizeof(sEvtRcdHead_TypeDef);
                OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr + (u32)nphase * len;

                fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len);
                fnWDT_Restart();
                // 已经发生过事件
                if ((fnJudge_Zero((u8 *)&headData.EventStartTime, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
                    (fnJudge_Zero((u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef)) == TRUE))
                {
                    continue;
                }

                fnGetCurrTime(&headData.EventStartTime);  //事件起始时间
                Std_Memset((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef));     //结束时间清零

                headData.EventTime = Event.EvtSumTime[i];

                //-------根据关联对象属性表获取数据-----------------
                //-----读取关联对象属性表---------
                len = FileItemInfo_EvtCtxlist[item].Len;
                OffAddr = FileItemInfo_EvtCtxlist[item].OffAddr;
                fnFile_Read(FileId_EvtCtxlist, OffAddr, DataBuf, len);

                listOADSumNum = *DataBuf++;

                Std_Memcpy((u8 *)&recordlen, DataBuf, 2);
                DataBuf += 2;

                //-------关联对象属性表合法性判断------------------
                if ((recordlen > MAX_RCDLEN) || (listOADSumNum > 100)) //容错处理，不超过100个OAD
                {
                    continue;
                }

                Std_Memset(EvtData, 0x00, recordlen);     //数据缓存清0
                Std_Memcpy(EvtData, (u8 *)&headData.EventSumCnt, 18);   //序号从0开始

                for (j = 0; j < listOADSumNum; j++)
                {
                    Std_Memcpy(&tmplist, DataBuf, sizeof(sContextList_TypeDef));
                    DataBuf += sizeof(sContextList_TypeDef);

                    pOad = (OAD_Analyse_TypeDef *)&tmplist.OAD;

                    if ((pOad->AtrFeature == EVT_HAP_BEFORE) || (pOad->AtrFeature == EVT_HAP_AFTER))
                    {
                        tmplist.len = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF), EvtData + tmplist.OffPos);
                    }
                }

                maxcnt_u16 = (u16)MAX_EVRECORD_TABLE[item];    //获取最大记录数

                if (headData.EventCnt < maxcnt_u16)
                {
                    headData.EventCnt ++;    //
                }

                headData.EventSumCnt ++;

                //--class24存储空间分配: 10条A相 + 10条B相 + 10条C相-----------------
                if (headData.EventSumCnt % maxcnt_u16)
                {
                    OffAddr = ((headData.EventSumCnt % maxcnt_u16) - 1) * (u32)recordlen;
                }
                else
                {
                    OffAddr = (maxcnt_u16 - 1) * (u32)recordlen;
                }

                OffAddr += FileItemInfo_EvtRecord[item].OffAddr + (u32)(nphase * recordlen * maxcnt_u16);

                fnFile_Write(FileId_EvtRecord, OffAddr, EvtData, recordlen);

                len = sizeof(sEvtRcdHead_TypeDef);
                OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr + (u32)(nphase * len);
                fnFile_Write(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len);

                Event.ExecFlag.EvFlag.EvFlagData0 |= D.EvFlag.EvFlagData0;      //完成事件启动
                Event.ExecFlag.EvFlag.EvFlagData1 |= D.EvFlag.EvFlagData1;      //完成事件启动

                fnEvent_Report(item, nphase, EVTSTART);
            }
        }
    }

    if (fEventStart.EvFlag.EvFlagData0 | fEventStart.EvFlag.EvFlagData1)
    {
        fnBufTemp_Free(DataBuf);
        fnBufTemp_Free(EvtData);
        return; //事件未启动完不进行事件执行、结束操作。
    }

    //---事件结束---
    if (fEventTerm.EvFlag.EvFlagData0 | fEventTerm.EvFlag.EvFlagData1)
    {
        for (D.EvFlag.EvFlagData0 = 1, D.EvFlag.EvFlagData1 = 0, i = 0 ; i < MAX_EVENTTYPE ; i++, D.EvFlag.EvFlagData0 = D.EvFlag.EvFlagData0 << 1, D.EvFlag.EvFlagData1 = D.EvFlag.EvFlagData1 << 1)
        {
            if (D.EvFlag.EvFlagData0 == 0 && D.EvFlag.EvFlagData1 == 0)
            {
                D.EvFlag.EvFlagData1 = 1 ;
            }

            if (((fEventTerm.EvFlag.EvFlagData0 & D.EvFlag.EvFlagData0) == 0) &&
                ((fEventTerm.EvFlag.EvFlagData1 & D.EvFlag.EvFlagData1) == 0))
            {
                continue;
            }

            item = EvConst[i].FileId;
            if (item != FileItemInfoNum_Evt_PowDn)
            {
                Event.ExecFlag.EvFlag.EvFlagData0 &= ~D.EvFlag.EvFlagData0;
                Event.ExecFlag.EvFlag.EvFlagData1 &= ~D.EvFlag.EvFlagData1;
                continue;
            }
            nphase = EvConst[i].nPha;

            len = sizeof(sEvtRcdHead_TypeDef);
            OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr + (u32)nphase * len;

            fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len);
            fnWDT_Restart();
            fnGetCurrTime(&headData.EventEndTime);  //事件起始时间

            headData.EventTime = Event.EvtSumTime[i];

            //-------根据关联对象属性表获取数据-----------------
            //-----读取关联对象属性表-不区分ABC相--------
            len = FileItemInfo_EvtCtxlist[item].Len;
            OffAddr = FileItemInfo_EvtCtxlist[item].OffAddr;
            fnFile_Read(FileId_EvtCtxlist, OffAddr, DataBuf, len);

            listOADSumNum = *DataBuf++;

            Std_Memcpy((u8 *)&recordlen, DataBuf, 2);
            DataBuf += 2;

            //-------关联对象属性表合法性判断------------------
            if ((recordlen > MAX_RCDLEN) || (listOADSumNum > 100)) //容错处理，不超过100个OAD
            {
                continue;
            }

            //--class24存储空间分配: 10条A相 + 10条B相 + 10条C相-----------------
            maxcnt_u16 = (u16)MAX_EVRECORD_TABLE[item];    //获取最大记录数
            if (headData.EventSumCnt % maxcnt_u16)
            {
                OffAddr = ((headData.EventSumCnt % maxcnt_u16) - 1) * (u32)recordlen;
            }
            else
            {
                OffAddr = (maxcnt_u16 - 1) * (u32)recordlen;
            }

            OffAddr += FileItemInfo_EvtRecord[item].OffAddr + (u32)(nphase * recordlen * maxcnt_u16);

            //--------读取事件发生前数据------------------------
            fnFile_Read(FileId_EvtRecord, OffAddr, EvtData, recordlen);
            Std_Memcpy(EvtData + 11, (u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef));

            for (j = 0; j < listOADSumNum; j++)
            {
                Std_Memcpy(&tmplist, DataBuf, sizeof(sContextList_TypeDef));
                DataBuf += sizeof(sContextList_TypeDef);

                pOad = (OAD_Analyse_TypeDef *)&tmplist.OAD;
                //---------更新事件发生后数据------------------------
                if ((pOad->AtrFeature == EVT_END_BEFORE) || (pOad->AtrFeature == EVT_END_AFTER))
                {
                    tmplist.OAD = (tmplist.OAD & 0xFFFF1FFF);
                    tmplist.len = fnGet_OADStoreData(tmplist.OAD, EvtData + tmplist.OffPos);
                }
            }

            //----------写事件记录----------------
            fnFile_Write(FileId_EvtRecord, OffAddr, EvtData, recordlen);

            len = sizeof(sEvtRcdHead_TypeDef);
            OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr + (u32)(nphase * len);
            fnFile_Write(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len);

            Event.ExecFlag.EvFlag.EvFlagData0 &= ~D.EvFlag.EvFlagData0;
            Event.ExecFlag.EvFlag.EvFlagData1 &= ~D.EvFlag.EvFlagData1;

            fnEvent_Report(item, nphase, EVTEND);
        }
    }

    fnBufTemp_Free(DataBuf);
    fnBufTemp_Free(EvtData);
}

void fnEvent_Exec(void)
{
    fnEvent_nphsEvt_Exec();   //分相事件记录

    //-------开盖状态判断及事件记录-------------------
    fnOpenCoverTailEvent();

    fnEvent_OpExec();
}

//---------事件清零-------------
void fnEvent_EvtClr(void)
{
    u8 i ;
    u8  *DataBuf;
    //  u32 OffAddr;

    fnWDT_Restart();

    DataBuf = (u8 *)fnBufTemp_Alloc(512);
    if (DataBuf != NULL)
    {
        for (i = 0; i < FileItemInfoNum_Evt_Max; i++)
        {
            if ((i == FileItemInfoNum_Evt_Clr) && (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable != 1))
            {
                fnWDT_Restart();
                continue;
            }
            //          if( (i != FileItemInfoNum_Evt_Clr)&&(i != FileItemInfoNum_Evt_EventClr) )
            {
                Std_Memset(DataBuf, 0x00, FileItemInfo_EvtRcdHead[i].Len);
                fnFile_Write(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[i].OffAddr, DataBuf, FileItemInfo_EvtRcdHead[i].Len);
            }
        }
    }
    fnBufTemp_Free(DataBuf);

    fnFile_Clr(FileId_CurStat);
    Std_Memset((u8 *)&Stat.PubData, 0x00, sizeof(sStatFile_TypeDef));

    fnEvent_Clr_Status(0xFF, 0xFF);   //全清

    Key.Release |= KEY_VAL_SHELLVS;
    Key.Release |= KEY_VAL_JUNBOXVS;
    Key.Release |= KEY_VAL_STROMANVS;
    Key.Release |= KEY_VAL_CTRLMODUPLGCHKVS;
    Inactive.InactiveFlag.EventFlag &= ~((u32)1 << EVENT_STYLE_SHELL);
    Inactive.InactiveFlag.EventFlag &= ~((u32)1 << EVENT_STYLE_JUNBOX);
    Inactive.InactiveFlag.EventFlag &= ~((u32)1 << EVENT_STYLE_MagnetDisturb);
    Inactive.InactiveFlag.EventFlag &= ~((u32)1 << EVENT_STYLE_MngPlug);
    Event.PriData.OpFlag &= ~(1 << EVENT_STYLE_CLR);

    Event.StartFlag.EvFlagBit.MngPlug = 0;
    Event.StartFlag.EvFlagBit.OpenCover = 0;
    Event.StartFlag.EvFlagBit.OpenTail = 0;

    // 清除管理模组插拔状态与ESAM序列号??
    //  memset(&Inactive.Mng.OldEsam[0], 0, FileItemInfoLen_HighState_EvtMngStr + 1);

    memcpy(&Inactive.Mng.OldEsam[0], &Inactive.Mng.NewEsam[0], FileItemInfoLen_HighState_EvtRcdBfEsam);
    Inactive.Mng.LstEvtFlag = 0;
    Inactive.Mng.RevEsam = 0;
    Inactive.Mng.Sta = 0;

    Inactive.Mng.LstEvtFlag = Inactive.InactiveFlag.EventFlag;

    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtRcdBfEsam,
                 &Inactive.Mng.OldEsam[0], FileItemInfoLen_HighState_EvtMngStr);

    memset(&Inactive.EvtPwn.CoverOpen, 0, FileItemInfoLen_HighState_EvtPwn);
    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                 &Inactive.EvtPwn.CoverOpen, FileItemInfoLen_HighState_EvtPwn);

    i = 0 ;
    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_LocalOpenFlag, &i, 1);
    Bkgrd.PubData.MtSta.MtSta3.StaBit.RemoteOpen = 1;
    Bkgrd.PubData.MtSta.MtSta3.StaBit.LocalOpen = 1;

    Bkgrd.PubData.tMngPlug = EvtMngDelay;

    // 清除停电期间电压电流数据
    sPwdnVoltCurTypedef Volt;
    memset(&Volt.PwdnTime.second, 0, FileItemInfoLen_HighState_PwdnVoltLoss);
    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_PwdnVoltLoss, &Volt.PwdnTime.second,
                 FileItemInfoLen_HighState_PwdnVoltLoss);

    //  fnUpDate_EvtParaOffPos();
}

void fnEvent_OpExec(void)
{
    u8 i, temp[4];
    u32 OffAddr ;
    sFrzRcdHead_TypeDef  buf;
    u8 *DataBuf;
    sDate_time_s_TypeDef  timebuf;

    if ((Event.PriData.OpFlag & (1 << EVENT_STYLE_CLR)) && (Event.PriData.Clr_Word == METER_CLR_WORD))
    {
        if (Event.PriData.Clr_Step == 0)
        {
            Wdog.T_WDOG = 1000;
            fnBufTemp_Init();
            fnEnergy_DataInit();
            fnWDT_Restart();

            if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable == 1)
            {
                //---仅厂内模式可以清电池工作时间，密文电表清零不清电池工作时间---------
                Bkgrd.PubData.tWorkBat = 0;
                fnFile_Write(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_tWorkBat, &Bkgrd.PubData.tWorkBat, 4);
            }
            Bkgrd.PubData.MtSysSta.SysSta = Bkgrd.PubData.MtSysSta.SysSta & 0x0000F000; //--除安全认证以外的标志位全清----

            //          Std_Memset((u8 *)&Secret.nPswRetry[0] , 0 , 10);
            //          fnFile_Write(FileId_InterTmp , FileItemInfoOffAddr_InterTmp_Secret , &Secret.nPswRetry[0] , 2);
            //          fnFile_Write(FileId_InterTmp , FileItemInfoOffAddr_InterTmp_Secret + 2 , &Secret.tPswFailClose[0] , 4);
            //          fnFile_Write(FileId_InterTmp , FileItemInfoOffAddr_InterTmp_Secret + 6 , &Secret.tPrgKeyValid , 2);
            //          fnFile_Write(FileId_InterTmp , FileItemInfoOffAddr_InterTmp_Secret + 8 , &Secret.tPrgKeyLock , 2);
            //          fnFile_Write(FileId_InterTmp , FileItemInfoOffAddr_InterTmp_Secret + 10 , &Secret.nMacErr , 1 );

            fnFile_Clr(FileId_FrzRcdHead) ;

            for (i = 0; i < MAX_FRZMIN_LINE; i++)
            {
                Std_Memset((u8 *)&buf, 0x00, sizeof(sFrzRcdHead_TypeDef));  //清8条分钟冻结曲线头 sFrzRcdHead_TypeDef
                OffAddr = FileItemInfo_FrzMinLineHead[i].OffAddr + sizeof(sFrzMinLinePara_TypeDef);  //记录头参数不清
                fnFile_Write(FileId_FrzMinLineHead, OffAddr, (u8 *)&buf, sizeof(sFrzRcdHead_TypeDef));
            }

            fnWrite_PowDn_FrzRmDayTime();
            fnWrite_PowDn_FrzDayTime();

            //fnEnergy_MoneyInit();
            #if(METERTYPE)
            Bkgrd.PubData.UpRunFileFlag = 0x5a;
            #endif

            fnUpDate_FrzParaOffPos();

            //-----事件清零事件记录清除---------------
            DataBuf = (u8 *)fnBufTemp_Alloc(128);
            if (DataBuf != NULL)
            {
                //              len = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_EventClr].Len;
                //              Std_Memset(DataBuf, 0x00 , len );
                //              fnFile_Write(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_EventClr].OffAddr, DataBuf, len);
            }
            fnBufTemp_Free(DataBuf);

            Event.PriData.Clr_Step = 1;
        }
        else if (Event.PriData.Clr_Step == 1)
        {
            fnEvent_EvtClr();   //

            Std_Memset((u8 *)&Secret.nPswRetry[0], 0, 10);
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret, &Secret.nPswRetry[0], 2);
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 2, &Secret.tPswFailClose[0], 4);
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 6, &Secret.tPrgKeyValid, 2);
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 8, &Secret.tPrgKeyLock, 2);
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 10, &Secret.nMacErr, 1);

            Event.PriData.OpFlag &= ~(1 << EVENT_STYLE_CLR);
            Event.PriData.Clr_Word = 0;
            Event.PriData.Clr_Step = 0;

            Bkgrd.PubData.MtSysSta.SysStaBit.EvtMeterClear = 1;
        }
    }
    else if ((Event.PriData.OpFlag & (1 << EVENT_STYLE_EVENTCLR)) && (Event.PriData.Clr_Word == EVENT_CLR_WORD))
    {
        fnEvent_EvtClr();   //事件清零

        Event.PriData.OpFlag &= ~(1 << EVENT_STYLE_EVENTCLR);
        Event.PriData.Clr_Word = 0;
        Event.PriData.Clr_Step = 0;
    }
    else if ((Event.PriData.OpFlag & (1 << EVENT_STYLE_CLR)) && ((Event.PriData.Clr_Word == FACTORY_CLR_WORD) || (Event.PriData.Clr_Word == FIRST_CLR_WORD)))
    {
        if (Event.PriData.Clr_Step == 0x5A) //---------
        {
            Std_Memset(&temp[0], 0x00, 4);
            fnFile_Write(FileId_NvRam, 0, (u8 *)&temp[0], 4);
            fnFile_Write(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_FristPowOnBak1, (u8 *)&temp[0], 4);
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_FristPowOnBak2, (u8 *)&temp[0], 4);
            fnWDT_Restart();

            fnSysDateTimes(&timebuf);

            if ((Event.PriData.Clr_Word == FIRST_CLR_WORD))
            {
                fnFile_Init(File_FirstInit);

                fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_First_ClrTime, (u8 *)&timebuf, sizeof(sDate_time_s_TypeDef));
            }
            else
            {
                fnFile_Init(File_CommInit);

                fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_Factory_ClrTime, (u8 *)&timebuf, sizeof(sDate_time_s_TypeDef));
            }
            fnDl698_Init();
            Bkgrd.PubData.MtSysSta.SysSta = 0;
            Bkgrd.PubData.tWorkBat = 0;
            Event.PriData.OpFlag &= ~(1 << EVENT_STYLE_NEEDCLR);
            Event.PriData.Clr_Word = 0;
            Event.PriData.Clr_Step = 0;
        }
    }
}

void fnEvtMngPlug_Init(void)
{
    memset(&Inactive.Mng.OldEsam[0], 0, FileItemInfoLen_HighState_EvtMngStr + 1);

    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_EvtRcdBfEsam,
                &Inactive.Mng.OldEsam[0], FileItemInfoLen_HighState_EvtMngStr);

    Inactive.InactiveFlag.EventFlag = Inactive.Mng.LstEvtFlag;

    if (Inactive.InactiveFlag.EventFlag & ((u32)1 << EVENT_STYLE_MngPlug))
    {
        Key.Press |= KEY_VAL_CTRLMODUPLGCHKVS;
    }

    if (Inactive.Mng.Sta & EvtSta_MngPlug)
    {
        Event.StartFlag.EvFlagBit.MngPlug = 1;
    }
    if (Inactive.Mng.Sta & EvtSta_OpenCover)
    {
        Event.StartFlag.EvFlagBit.OpenCover = 1;
    }
    if (Inactive.Mng.Sta & EvtSta_OpenTail)
    {
        Event.StartFlag.EvFlagBit.OpenTail = 1;
    }
}

void fnEvtMngPlug_PwdnSave(void)
{
    //  fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtRcdBfEsam ,
    //                  &Inactive.Mng.OldEsam[0], 2 + FileItemInfoLen_HighState_EvtRcdBfEsam + FileItemInfoLen_HighState_EvtRcdAftEsam );
    //
    //  fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtFlag ,
    //                  &Inactive.InactiveFlag.EventFlag, FileItemInfoLen_HighState_EvtFlag );

    // 开端盖状态设置唤醒中断触发沿
    if (Inactive.Mng.Sta & EvtSta_OpenTail)
    {
        Rn8xxx_KBI_Init(KBI_ID3, KBI_RisingEdge, KBI_IRQ_ENABLE);
    }
    else
    {
        Rn8xxx_KBI_Init(KBI_ID3, KBI_FallingEdge, KBI_IRQ_ENABLE);
    }

    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtRcdBfEsam,
                 &Inactive.Mng.OldEsam[0], FileItemInfoLen_HighState_EvtMngStr);
}

u8 fnEvtMngPlug_EsamCheck(void)
{
    u8 i;

    // 通讯收到管理模组ESAM序列号
    if (Inactive.Mng.RevEsam & Mng_ComRcvEsam)
    {
        fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_EvtRcdBfEsam,
                    &Inactive.Mng.OldEsam[0], FileItemInfoLen_HighState_EvtRcdBfEsam + FileItemInfoLen_HighState_EvtRcdAftEsam);

        Inactive.Mng.RevEsam |= Mng_IsRcvEsam;
        Inactive.Mng.RevEsam &= ~Mng_ComRcvEsam;
    }

    for (i = 0; i < 8; i++)
    {
        if (Inactive.Mng.NewEsam[i] != Inactive.Mng.OldEsam[i])
        {
            break;
        }
    }

    if (i != 8)
    {
        return 1;
    }

    return 0;
}

void fnOpenCoverTailEvent(void)
{
    u8 uflg = 0;

    if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON) || (Inactive.PubData.InactiveStamp))
    {
        return;
    }

    if (Inactive.InactiveFlag.EventFlag & ((u32)1 << EVENT_STYLE_SHELL))
    {
        if (Key.Release & KEY_VAL_SHELL)                        // 上盖关闭
        {
            Key.Release &= ~KEY_VAL_SHELL;
            fnEvent_Operation(FileItemInfoNum_Evt_OpenCover, EVTEND, NULL);
            Inactive.InactiveFlag.EventFlag &= ~((u32)1 << EVENT_STYLE_SHELL);

            Bkgrd.PubData.MtSysSta.SysStaBit.EvtOpenCover = 1;
            Bkgrd.PubData.MtSysSta.SysStaBit.OpenCover = 0;
            Event.StartFlag.EvFlagBit.OpenCover = 0;
            Inactive.Mng.Sta &= ~EvtSta_OpenCover;
            uflg = 1;
        }
    }
    else
    {
        if (Key.Press & KEY_VAL_SHELL)                      // 上盖打开
        {
            Key.Press &= ~KEY_VAL_SHELL;
            fnEvent_Operation(FileItemInfoNum_Evt_OpenCover, EVTSTART, NULL);
            Inactive.InactiveFlag.EventFlag |= ((u32)1 << EVENT_STYLE_SHELL);

            Bkgrd.PubData.MtSysSta.SysStaBit.EvtOpenCover = 1;
            Bkgrd.PubData.MtSysSta.SysStaBit.OpenCover = 1;
            Event.StartFlag.EvFlagBit.OpenCover = 1;
            Inactive.Mng.Sta |= EvtSta_OpenCover;
            uflg = 1;
        }
    }

    // 掉电状态不进行判断
    //  if( (Bkgrd.PubData.tMngPlug == 0) && (Bkgrd.PubData.MtSta.MtSta7.StaBit.PowDn == 0) )
    if (Bkgrd.PubData.tMngPlug == 0)
    {
        // 管理模组插拔事件
        if (Inactive.InactiveFlag.EventFlag & ((u32)1 << EVENT_STYLE_MngPlug))
        {
            if (Key.Release & KEY_VAL_CTRLMODUPLGCHK)       // 插上
            {
                Key.Release &= ~KEY_VAL_CTRLMODUPLGCHK;
                if (Inactive.Mng.Sta & EvtSta_MngPlug)              // 之前为拔出状态
                {
                    Inactive.Mng.Sta &= ~EvtSta_MngPlug;

                    // 暂使用全FF替代
                    //                  if(!(Inactive.Mng.RevEsam & Mng_IsRcvEsam))
                    {
                        u8 tmp[8];
                        memset(&tmp[0], 0xFF, 8);
                        fnEvent_Operation(FileItemInfoNum_Evt_MngPlug, EVTEND, &tmp[0]);
                        Inactive.Mng.RevEsam |= Mng_ReplaceEsam;
                    }

                    Inactive.Mng.RevEsam |= Mng_SynEsam;

                    Bkgrd.PubData.MtSysSta.SysStaBit.EvtControlPullOut = 1;
                }

                //              Inactive.Mng.RevEsam |= Mng_SynEsam;
                Inactive.InactiveFlag.EventFlag &= ~((u32)1 << EVENT_STYLE_MngPlug);
                Event.StartFlag.EvFlagBit.MngPlug = 0;
                uflg = 1;

                Bkgrd.PubData.tMngPlug = EvtMngDelay;
            }
        }
        else
        {
            if (Key.Press & KEY_VAL_CTRLMODUPLGCHK)         // 拔出
            {
                Key.Press &= ~KEY_VAL_CTRLMODUPLGCHK;
                if (!(Inactive.Mng.Sta & EvtSta_MngPlug))           // 非拔出状态
                {
                    Inactive.Mng.Sta |= EvtSta_MngPlug;
                    fnEvent_Operation(FileItemInfoNum_Evt_MngPlug, EVTSTART, NULL);

                    Inactive.Mng.RevEsam |= Mng_SynEsam;
                }
                Inactive.InactiveFlag.EventFlag |= ((u32)1 << EVENT_STYLE_MngPlug);

                Bkgrd.PubData.MtSysSta.SysStaBit.EvtControlPullOut = 1;
                Event.StartFlag.EvFlagBit.MngPlug = 1;
                uflg = 1;

                Bkgrd.PubData.tMngPlug = EvtMngDelay / 2;
                Inactive.Mng.RevEsam &= ~Mng_IsRcvEsam;
            }
        }

        // 管理模组ESAM序列号有变化
        if (fnEvtMngPlug_EsamCheck())
        {
            // 之前为拔出状态
            if (Inactive.Mng.Sta & EvtSta_MngPlug)
            {
                fnEvent_Operation(FileItemInfoNum_Evt_MngPlug, EVTEND, NULL);
                memcpy(&Inactive.Mng.OldEsam[0], &Inactive.Mng.NewEsam[0], 8);

                Inactive.Mng.RevEsam |= Mng_SynEsam;

                Bkgrd.PubData.MtSysSta.SysStaBit.EvtControlPullOut = 1;
                Event.StartFlag.EvFlagBit.MngPlug = 0;
                Inactive.Mng.Sta &= ~EvtSta_MngPlug;
            }
            // 之前为插上状态
            else
            {
                // 使用新ESAM序列号替换
                if (Inactive.Mng.RevEsam & Mng_ReplaceEsam)
                {
                    Inactive.Mng.RevEsam &= ~Mng_ReplaceEsam;
                    fnEvent_Operation(FileItemInfoNum_Evt_MngPlug, EVTEND, &Inactive.Mng.NewEsam[0]);
                }
                else
                {
                    fnEvent_Operation(FileItemInfoNum_Evt_MngPlug, EVTSTART, NULL);

                    fnEvent_Operation(FileItemInfoNum_Evt_MngPlug, EVTEND, NULL);
                }
                memcpy(&Inactive.Mng.OldEsam[0], &Inactive.Mng.NewEsam[0], 8);

                Inactive.Mng.RevEsam |= Mng_SynEsam;

                Bkgrd.PubData.MtSysSta.SysStaBit.EvtControlPullOut = 1;
                Event.StartFlag.EvFlagBit.MngPlug = 0;
                Inactive.Mng.Sta &= ~EvtSta_MngPlug;
            }

            Bkgrd.PubData.tMngPlug = EvtMngDelay;
        }
        else
        {
            // 使用管理芯ESAM序列号替换
            if ((Inactive.Mng.RevEsam & Mng_ReplaceEsam) && (Inactive.Mng.RevEsam & Mng_IsRcvEsam))
            {
                Inactive.Mng.RevEsam &= ~Mng_ReplaceEsam;
                fnEvent_Operation(FileItemInfoNum_Evt_MngPlug, EVTEND, &Inactive.Mng.NewEsam[0]);
            }
        }
    }

    #if(nPhs==ThreePhs)
    if (Inactive.InactiveFlag.EventFlag & ((u32)1 << EVENT_STYLE_JUNBOX))
    {
        if (Key.Release & KEY_VAL_JUNBOX)                       // 端盖关闭
        {
            Key.Release &= ~KEY_VAL_JUNBOX;
            fnEvent_Operation(FileItemInfoNum_Evt_OpenTail, EVTEND, NULL);
            Inactive.InactiveFlag.EventFlag &= ~((u32)1 << EVENT_STYLE_JUNBOX);

            Bkgrd.PubData.MtSysSta.SysStaBit.EvtOpenShell = 1;
            Bkgrd.PubData.MtSysSta.SysStaBit.OpenShell = 0;
            Event.StartFlag.EvFlagBit.OpenTail = 0;
            Inactive.Mng.Sta &= ~EvtSta_OpenTail;
            uflg = 1;
        }
    }
    else
    {
        if (Key.Press & KEY_VAL_JUNBOX)                         // 端盖打开
        {
            Key.Press &= ~KEY_VAL_JUNBOX;
            fnEvent_Operation(FileItemInfoNum_Evt_OpenTail, EVTSTART, NULL);
            Inactive.InactiveFlag.EventFlag |= ((u32)1 << EVENT_STYLE_JUNBOX);

            Bkgrd.PubData.MtSysSta.SysStaBit.EvtOpenShell = 1;
            Bkgrd.PubData.MtSysSta.SysStaBit.OpenShell = 1;
            Event.StartFlag.EvFlagBit.OpenTail = 1;
            Inactive.Mng.Sta |= EvtSta_OpenTail;
            uflg = 1;
        }
    }
    //    if(Inactive.InactiveFlag.EventFlag & ((u32)1 << EVENT_STYLE_MagnetDisturb))
    //    {
    //      if(Key.Release&KEY_VAL_STROMAN)                         //
    //      {
    //          Key.Release &= ~KEY_VAL_STROMAN;
    //      //  fnEvent_Operation(FileItemInfoNum_Evt_MagnetDisturb , EVTEND, NULL); //debug
    //          Inactive.InactiveFlag.EventFlag &= ~((u32)1 << EVENT_STYLE_MagnetDisturb);
    //      }
    //    }
    //    else
    //    {
    //      if(Key.Press&KEY_VAL_STROMAN)                           //
    //      {
    //          Key.Press &= ~KEY_VAL_STROMAN;
    //      //  fnEvent_Operation(FileItemInfoNum_Evt_MagnetDisturb , EVTSTART, NULL);  //debug
    //          Inactive.InactiveFlag.EventFlag |= ((u32)1 << EVENT_STYLE_MagnetDisturb);
    //      }
    //    }
    #endif

    if (uflg == 1)
    {
        Inactive.Mng.LstEvtFlag = Inactive.InactiveFlag.EventFlag;

        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_MngPlugSta,
                     &Inactive.Mng.Sta, FileItemInfoLen_HighState_MngPlugSta + FileItemInfoLen_HighState_EvtFlag);

        uflg = 0;
    }

    // 同步更新存储ee
    if (Inactive.Mng.RevEsam & Mng_SynEsam)
    {
        Inactive.Mng.LstEvtFlag = Inactive.InactiveFlag.EventFlag;

        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtRcdBfEsam,
                     &Inactive.Mng.OldEsam[0], FileItemInfoLen_HighState_EvtMngStr);

        Inactive.Mng.RevEsam &= ~Mng_SynEsam;
    }

    return;
}

//---------为方便快速主动上报，最近1次掉电发生事件记录存E2--置主动上报标志-------
void fnWrite_PownDownEvtToE2(void)
{
    //u8        j;

    u32     OffAddr = 0;

    //u8    *DataBuf,*EvtData;
    sEvtRcdHead_TypeDef  headData;
    //sContextList_TypeDef  tmplist;
    //u8 listOADSumNum;
    //u16 recordlen , maxcnt_u16, len;
    u16  len;
    //OAD_Analyse_TypeDef *pOad;

    fnWDT_Restart();

    len = sizeof(sEvtRcdHead_TypeDef);
    OffAddr = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_PowDn].OffAddr;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len);

    //------事件记录头发生时间不为0，结束时间为0，表示有掉电事件发生事件记录-------
    if ((fnJudge_Zero((u8 *)&headData.EventStartTime, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Zero((u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        return;    //--------------------
    }
    {
        fnSysDateTimes(&SysDatetimes);

        fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                    &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);

        Inactive.EvtPwn.EvtPwdn = 0x5A;
        Std_Memcpy((u8 *)&Inactive.EvtPwn.EvtPwdnTime.second, (u8 *)&SysDatetimes.second, sizeof(sDate_time_s_TypeDef));

        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                     &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
    }

    //      DataBuf = (u8 *)fnBufTemp_Alloc(512);
    //      if(DataBuf == NULL)
    //      {
    //          return ;
    //      }
    //      Std_Memset(DataBuf,0, 512);
    //
    //      EvtData = (u8 *)fnBufTemp_Alloc(512);
    //      if(EvtData == NULL)
    //      {
    //          return ;
    //      }
    //      Std_Memset(EvtData,0, 512);

    //      maxcnt_u16 = ( u16 )MAX_EVRECORD_TABLE[FileItemInfoNum_Evt_PowDn];  //获取最大记录数
    //
    //      fnGetCurrTime(&headData.EventStartTime);  //事件起始时间
    //      Std_Memset( (u8 *)&headData.EventEndTime , 0x00 , sizeof(sDate_time_s_TypeDef) );  //清零结束时间
    //
    //      Std_Memcpy( EvtData, (u8 *)&headData.EventSumCnt, EvtC7_StdRecList.reclen );    //序号从0开始
    //
    //      //-------根据关联对象属性表获取数据-----------------
    //      //-----读取关联对象属性表---------
    //      len = FileItemInfo_EvtCtxlist[FileItemInfoNum_Evt_PowDn].Len;
    //      OffAddr = FileItemInfo_EvtCtxlist[FileItemInfoNum_Evt_PowDn].OffAddr;
    //      fnFile_Read(FileId_EvtCtxlist, OffAddr, DataBuf, len );
    //
    //      listOADSumNum = *DataBuf++;
    //      Std_Memcpy((u8 *)&recordlen, DataBuf, 2);
    //      DataBuf += 2;
    //
    //      for(j = 0; j < listOADSumNum; j++)
    //      {
    //          Std_Memcpy(&tmplist,DataBuf,sizeof(sContextList_TypeDef));
    //          DataBuf +=sizeof(sContextList_TypeDef);
    //          pOad  = (OAD_Analyse_TypeDef *)&tmplist.OAD;
    //
    //          if( ( pOad->AtrFeature == EVT_HAP_BEFORE )||( pOad->AtrFeature == EVT_HAP_AFTER ) )
    //              tmplist.len = fnGet_OADStoreData( (tmplist.OAD&0xFFFF1FFF), EvtData + tmplist.OffPos );
    //
    //      }
    //
    //      if( headData.EventCnt < maxcnt_u16)
    //              headData.EventCnt ++;  //
    //
    //          headData.EventSumCnt ++;
    //
    //      OffAddr = FileItemInfoOffAddr_EvtReport_PowerDnEvtRcd;
    //
    //      fnFile_Write(FileId_EvtReport, OffAddr , EvtData, recordlen );
    //
    //      len = sizeof(sEvtRcdHead_TypeDef);
    //      OffAddr = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_PowDn].OffAddr;
    //      fnFile_Write(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len );

    //      if(EvtRptData.PowerUpTime > 59)
    //          fnEvent_Report(FileItemInfoNum_Evt_PowDn ,  0 , EVTSTART);

    //      fnBufTemp_Free(DataBuf);
    //      fnBufTemp_Free(EvtData);
}

/*********************************************************************************************************
** Function name:   fnWrite_PownDownEvtToFlash
** Descriptions:    E2数据覆盖到Flash
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnWrite_PownDownEvtToFlash(void)
{
    u32     temp1, temp2;
    u8      i;

    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);

    // 补掉电记录
    if (Inactive.EvtPwn.EvtPwdn == 0x5A)
    {
        Inactive.EvtPwn.EvtPwdn = 0;

        fnEvent_Operation(FileItemInfoNum_Evt_PowDn, EVTSTART, (u8 *)&Inactive.EvtPwn.EvtPwdnTime);

        //-----------计算掉电累计时间---------------
        fnSysDateTimes(&SysDatetimes);
        temp1 = fnDateTimeToSec(&SysDatetimes);
        temp2 = fnDateTimeToSec(&Inactive.EvtPwn.EvtPwdnTime);
        if (temp1 > temp2)
        {
            for (i = 0; i < MAX_EVENTTYPE; i++)
            {
                if (FileItemInfoNum_Evt_PowDn == EvConst[i].FileId)
                {
                    Event.EvtSumTime[i] += (temp1 - temp2);

                    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtSumTime + 4 * i, (u8 *)&Event.EvtSumTime[i], 4);

                    break;
                }
            }
        }

        memset(&Inactive.EvtPwn.EvtPwdnTime, 0, sizeof(sDate_time_s_TypeDef));

        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                     &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
    }

    //完成事件启动
    Event.ExecFlag.EvFlag.EvFlagData0 |= EVGEN_MARK_POWDN;
    //上电后判断延时事件为3秒
    EvStatusInter.tPowDn = 3;

    EvStatusInter.lStatus[0] |= EVGEN_MARK_POWDN;
    EvStatusInter.Status[0] |= EVGEN_MARK_POWDN;

    //  u32     OffAddr=0 , temp1 , temp2;
    //
    //  u8  *DataBuf,*EvtData , i;
    //  sEvtRcdHead_TypeDef  headData;
    //  u16 recordlen , maxcnt_u16;
    //
    //  OffAddr = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_PowDn].OffAddr;
    //  fnWDT_Restart();
    //  fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, sizeof(sEvtRcdHead_TypeDef) );

    //  //------事件记录头发生时间不为0，结束时间为0，表示有掉电事件发生事件记录-------
    //  if( ( fnJudge_Zero((u8 *)&headData.EventStartTime , sizeof(sDate_time_s_TypeDef)) == ERN_FALSE)&&
    //      ( fnJudge_Zero((u8 *)&headData.EventEndTime , sizeof(sDate_time_s_TypeDef)) == ERN_TRUE))
    //  {
    //      DataBuf = (u8 *)fnBufTemp_Alloc(512);
    //      if(DataBuf == NULL)
    //      {
    //          return ;
    //      }
    //      Std_Memset(DataBuf,0, 512);
    //
    //      EvtData = (u8 *)fnBufTemp_Alloc(512);
    //      if(EvtData == NULL)
    //      {
    //          return ;
    //      }
    //      Std_Memset(EvtData,0, 512);
    //
    //      //-----获取事件记录长度---------------
    //      OffAddr = FileItemInfo_EvtCtxlist[FileItemInfoNum_Evt_PowDn].OffAddr;
    //      fnFile_Read(FileId_EvtCtxlist, OffAddr + 1, DataBuf, 2 );
    //
    //      Std_Memcpy((u8 *)&recordlen, DataBuf, 2);

    //      OffAddr = FileItemInfoOffAddr_EvtReport_PowerDnEvtRcd;
    //
    //      fnFile_Read(FileId_EvtReport, OffAddr , EvtData, recordlen );

    //      maxcnt_u16 = ( u16 )MAX_EVRECORD_TABLE[FileItemInfoNum_Evt_PowDn];
    //
    //      if( headData.EventSumCnt%maxcnt_u16 )
    //      {
    //          OffAddr = ((headData.EventSumCnt%maxcnt_u16) - 1) * (u32)recordlen;
    //      }
    //      else
    //      {
    //          OffAddr = (maxcnt_u16 - 1) * (u32)recordlen;
    //      }

    //      OffAddr += FileItemInfo_EvtRecord[FileItemInfoNum_Evt_PowDn].OffAddr;

    //      fnFile_Write(FileId_EvtRecord, OffAddr , EvtData, recordlen );
    //
    //      //-----------计算掉电累计时间---------------
    //      fnSysDateTimes(&SysDatetimes);
    //      temp1 = fnDateTimeToSec(&SysDatetimes);
    //      temp2 = fnDateTimeToSec(&headData.EventStartTime);
    //      if(temp1 > temp2)
    //      {
    //          for(i = 0; i < MAX_EVENTTYPE; i++)
    //          {
    //              if(FileItemInfoNum_Evt_PowDn == EvConst[i].FileId)
    //              {
    //                  Event.EvtSumTime[i] += (temp1 - temp2);

    //                  fnFile_Write(FileId_HighState , FileItemInfoOffAddr_HighState_EvtSumTime + 4*i , (u8 *)&Event.EvtSumTime[i] , 4);
    //
    //                  break;
    //              }
    //          }
    //
    //      }

    //  #if(nPhs==ThreePhs)
    //      //Event.ExecFlag.EvFlagBit.PowDn = 1;  //完成事件启动
    //      Event.ExecFlag.EvFlag.EvFlagData1 |= EVGEN_MARK_POWDN;
    //       //上电后判断延时事件为3秒
    //      EvStatusInter.tPowDn = 3;
    //
    //      EvStatusInter.lStatus[1] |= EVGEN_MARK_POWDN;
    //      EvStatusInter.Status[1] |= EVGEN_MARK_POWDN;
    //  #else
    //       //完成事件启动
    //      Event.ExecFlag.EvFlag.EvFlagData0 |= EVGEN_MARK_POWDN;
    //       //上电后判断延时事件为3秒
    //      EvStatusInter.tPowDn = 3;
    //
    //      EvStatusInter.lStatus[0] |= EVGEN_MARK_POWDN;
    //      EvStatusInter.Status[0] |= EVGEN_MARK_POWDN;

    //  #endif

    //      fnBufTemp_Free(DataBuf);
    //      fnBufTemp_Free(EvtData);
    //
    //  }
}

/*********************************************************************************************************
** Function name:   fnEvent_SumTime
** Descriptions:    事件记录累计时间
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnEvent_SumTime(void)
{
    uEventFlag_TypeDef  fEventStart;//事件启动/进行 /终止标志

    u8      i;
    uEventFlag_TypeDef  D;

    if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON) || (Inactive.PubData.InactiveStamp))
    {
        return;
    }

    fEventStart.EvFlag.EvFlagData0 = Event.StartFlag.EvFlag.EvFlagData0;
    fEventStart.EvFlag.EvFlagData1 = Event.StartFlag.EvFlag.EvFlagData1;

    //---事件启动---
    if (fEventStart.EvFlag.EvFlagData0 | fEventStart.EvFlag.EvFlagData1)
    {
        for (D.EvFlag.EvFlagData0 = 1, D.EvFlag.EvFlagData1 = 0, i = 0 ; i < MAX_EVENTTYPE ; i++, D.EvFlag.EvFlagData0 = D.EvFlag.EvFlagData0 << 1, D.EvFlag.EvFlagData1 = D.EvFlag.EvFlagData1 << 1)
        {
            if (D.EvFlag.EvFlagData0 == 0 && D.EvFlag.EvFlagData1 == 0)
            {
                D.EvFlag.EvFlagData1 = 1 ;
            }

            if ((fEventStart.EvFlag.EvFlagData0 & D.EvFlag.EvFlagData0) | (fEventStart.EvFlag.EvFlagData1 & D.EvFlag.EvFlagData1))
            {
                Event.EvtSumTime[i]++;
            }
        }
    }
}

/*********************************************************************************************************
** Function name:   fnEvent_WriteSumTime
** Descriptions:更新事件记录累计时间到事件记录头文件并存E2
** input parameters:  item 事件记录序号，=0xFF 全写；
**                            nphase  分项A相=0 ; B相=1; C相=2; 分相全写=0xFF
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnEvent_WriteSumTime(u8 item, u8  nphase)
{
    u8  i;
    u16  len;
    u32     OffAddr = 0;
    sEvtRcdHead_TypeDef  headData;

    len = sizeof(sEvtRcdHead_TypeDef);

    if ((item == 0xFF) && (nphase == 0xFF))
    {
        for (i = 0; i < MAX_EVENTTYPE; i++)
        {
            item = EvConst[i].FileId;
            nphase = EvConst[i].nPha;
            OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr + (u32)nphase * len + 20;   //20=4+7+7+2

            headData.EventTime = Event.EvtSumTime[i];

            fnFile_Write(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventTime, 4);

            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtSumTime, (u8 *)&Event.EvtSumTime[0], FileItemInfoLen_HighState_EvtSumTime);
        }
    }
    else
    {
        for (i = 0; i < MAX_EVENTTYPE; i++)
        {
            if ((item == EvConst[i].FileId) && (nphase == EvConst[i].nPha))
            {
                OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr + (u32)nphase * len + 20;   //

                headData.EventTime = Event.EvtSumTime[i];

                fnFile_Write(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventTime, 4);

                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtSumTime, (u8 *)&Event.EvtSumTime[0], FileItemInfoLen_HighState_EvtSumTime);

                break;
            }
        }
    }
}

void fnEvent_Clr_BroadstaSta(void)
{
    sBroatStatue_TypeDef  broadsta;

    Std_Memset((u8 *)&broadsta, 0x00, sizeof(sBroatStatue_TypeDef));
    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_BroatStatue, (u8 *)&broadsta, sizeof(sBroatStatue_TypeDef));
}

//-----无功1，无功2编程次数清零--
//-----读取当前记录表需单独应答无功1，无功2编程次数--------
void fnEvent_Clr_PrgQSta(void)
{
    u32 temp;

    Std_Memset((u8 *)&temp, 0x00, 4);
    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_PrgQ1_Cnt, (u8 *)&temp, 4);
    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_PrgQ2_Cnt, (u8 *)&temp, 4);
}

void fnEvent_Clr_PowDnDatetimes(void)
{
    sDate_time_s_TypeDef      PowDn_Datetimes;

    Std_Memcpy((u8 *)&PowDn_Datetimes, (u8 *)&SysDatetimes, sizeof(sDate_time_s_TypeDef));

    fnFile_Write(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_PowDnTime, &PowDn_Datetimes, sizeof(sDate_time_s_TypeDef));
}

/*********************************************************************************************************
** Function name:   fnClr_EvtReportData
** Descriptions:    清除事件记录主动上报
** input parameters:  item: 事件记录编号,=0xFF时表示所有事件记录
                               Ch:通道号，0xFF时表示所有通道
** output parameters:   无
** Returned value:
*********************************************************************************************************/
void fnClr_EvtReportData(u8  item, u8 nphase, u8 Ch)
{
    sReportList_TypeDef tempList;
    u32 clrOAD = 0, addr;
    u8 i, j ;

    fnWDT_Restart();

    if ((item == 0xFF) && (Ch == 0xFF)) //总清
    {
        Std_Memset((u8 *)&EvtRptData.ListZB_A, 0, sizeof(sReportList_TypeDef));
        EvtRptData.RecOADZB   = 0;
        EvtRptData.RecOAD485  = 0;
        EvtRptData.RecOAD4852 = 0;

        Std_Memset((u8 *)&tempList, 0, sizeof(sReportList_TypeDef));

        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNumZB_A, &EvtRptData.ListZB_A, sizeof(sReportList_TypeDef));
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNumZB_F, (u8 *)&tempList, sizeof(sReportList_TypeDef));
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNum485_F, (u8 *)&tempList, sizeof(sReportList_TypeDef));
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNum4852_F, (u8 *)&tempList, sizeof(sReportList_TypeDef));
    }
    else
    {
        //       if(item < FileItemInfoNum_Evt_QtOverNeed)
        //      {
        //          clrOAD = (nphase + 7)<<8;  //分相事件,属性7,8,9
        //      }
        //       else if(item < FileItemInfoNum_Evt_PtOverNeed)
        //      {
        //          clrOAD = (nphase + 6)<<8;  //分相事件,属性6,7,8,9
        //      }
        //      else
        clrOAD = 0x00000200;   //非分相事件固定属性2

        for (i = 0; i < FileItemInfoNum_Evt_Max; i++)
        {
            if (Event_Item[i].Item == item)
            {
                clrOAD |= (u32)(Event_Item[i].OI << 16);
                break;
            }
        }

        if (Ch == SCOM_PORT_ZBCOM)
        {
            for (i = 0; i < EvtRptData.ListZB_A.OADNum; i++) //主动上报列表
            {
                if (EvtRptData.ListZB_A.OAD[i] == clrOAD)
                {
                    j = EvtRptData.ListZB_A.OADNum - i;

                    if (j > 1)
                    {
                        Std_Memcpy((u8 *)&EvtRptData.ListZB_A.OAD[i], (u8 *)&EvtRptData.ListZB_A.OAD[i + 1], 4 * (j - 1));
                        EvtRptData.ListZB_A.OAD[i + j - 1] = 0;  //
                    }
                    else
                    {
                        EvtRptData.ListZB_A.OAD[i] = 0;
                    }

                    EvtRptData.ListZB_A.OADNum--;

                    fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNumZB_A, &EvtRptData.ListZB_A, sizeof(sReportList_TypeDef));

                    break;
                }
            }
        }

        //-----跟随上报列表---------------
        if (Ch == SCOM_PORT_ZBCOM)
        {
            addr = FileItemInfoOffAddr_EvtReport_OADNumZB_F;
        }
        else if (Ch == SCOM_PORT_RS485A)
        {
            addr = FileItemInfoOffAddr_EvtReport_OADNum485_F;
        }
        else if (Ch == SCOM_PORT_RS485B)
        {
            addr = FileItemInfoOffAddr_EvtReport_OADNum4852_F;
        }
        else
        {
            return;
        }

        fnFile_Read(FileId_EvtReport, addr, (u8 *)&tempList, sizeof(sReportList_TypeDef));

        for (i = 0; i < tempList.OADNum; i++) //上报列表
        {
            if (tempList.OAD[i] == clrOAD)
            {
                j = tempList.OADNum - i;

                if (j > 1)
                {
                    Std_Memcpy((u8 *)&tempList.OAD[i], (u8 *)&tempList.OAD[i + 1], 4 * (j - 1));
                    EvtRptData.ListZB_A.OAD[i + j - 1] = 0;  //
                }
                else
                {
                    tempList.OAD[i] = 0;
                }

                tempList.OADNum--;

                fnFile_Write(FileId_EvtReport, addr, (u8 *)&tempList, sizeof(sReportList_TypeDef));

                break;
            }
        }

        if (Ch == SCOM_PORT_ZBCOM)
        {
            if (tempList.OADNum)
            {
                EvtRptData.RecOADZB = tempList.OAD[tempList.OADNum - 1];
            }
            else
            {
                EvtRptData.RecOADZB = 0;
            }
        }
        else if (Ch == SCOM_PORT_RS485A)
        {
            if (tempList.OADNum)
            {
                EvtRptData.RecOAD485 = tempList.OAD[tempList.OADNum - 1];
            }
            else
            {
                EvtRptData.RecOAD485 = 0;
            }
        }
        else if (Ch == SCOM_PORT_RS485B)
        {
            if (tempList.OADNum)
            {
                EvtRptData.RecOAD4852 = tempList.OAD[tempList.OADNum - 1];
            }
            else
            {
                EvtRptData.RecOAD4852 = 0;
            }
        }
    }
}

/*********************************************************************************************************
** Function name:   fnCheck_ReportPara
** Descriptions:    主动上报参数效验
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnCheck_ReportPara(void)
{
    sReportList_TypeDef tempList;

    if (fnCrc_Check(1, (u8 *)&EvtRptData.Para.AtiveAllow, sizeof(sEvtRptPara_TypeDef) - 2, (u8 *)&EvtRptData.Para.Crc))
    {
        fnFile_Read(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_AtiveAllow, &EvtRptData.Para.AtiveAllow, sizeof(sEvtRptPara_TypeDef));

        fnFile_Read(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNumZB_A, &EvtRptData.ListZB_A, sizeof(sReportList_TypeDef));

        fnFile_Read(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNumZB_F, &tempList, sizeof(sReportList_TypeDef));
        if ((tempList.OADNum != 0) && (tempList.OADNum <= ITEM_EVT_MAX))
        {
            EvtRptData.RecOADZB = tempList.OAD[tempList.OADNum - 1];
        }
        else
        {
            EvtRptData.RecOADZB = 0;
        }

        fnFile_Read(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNum485_F, &tempList, sizeof(sReportList_TypeDef));
        if ((tempList.OADNum != 0) && (tempList.OADNum <= ITEM_EVT_MAX))
        {
            EvtRptData.RecOAD485 = tempList.OAD[tempList.OADNum - 1];
        }
        else
        {
            EvtRptData.RecOAD485 = 0;
        }

        fnFile_Read(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNum485_F, &tempList, sizeof(sReportList_TypeDef));
        if ((tempList.OADNum != 0) && (tempList.OADNum <= ITEM_EVT_MAX))
        {
            EvtRptData.RecOAD4852 = tempList.OAD[tempList.OADNum - 1];
        }
        else
        {
            EvtRptData.RecOAD4852 = 0;
        }

        fnFile_Read(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatusZB, (u8 *)&EvtRptData.Status, sizeof(sEvtRptStatus_TypeDef));
    }
}

/*********************************************************************************************************
** Function name:   fnEvent_Report
** Descriptions:    主动上报产生，有事件新增时执行1次
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnEvent_Report(u8 item, u8 nphase, u8 mode)
{
    u8 i, Offset, j, k;
    u32 RptOAD, addr;
    sReportList_TypeDef tempList;

    fnCheck_ReportPara();

    #if(nPhs==ThreePhs)
    //   if(item < FileItemInfoNum_Evt_QtOverNeed)
    //  {
    //      RptOAD = (nphase + 7)<<8;  //分相事件,属性7,8,9
    //  }
    //   else if(item < FileItemInfoNum_Evt_PtOverNeed)
    //  {
    //      RptOAD = (nphase + 6)<<8;  //分相事件,属性6,7,8,9
    //  }
    #else
    //   if(item == FileItemInfoNum_Evt_OverCur)
    //  {
    //      RptOAD = (0 + 7)<<8;  //分相事件,属性7,8,9
    //  }
    #endif
    //  else

    RptOAD = 0x00000200;   //非分相事件固定属性2

    for (i = 0; i < FileItemInfoNum_Evt_Max; i++)
    {
        if (Event_Item[i].Item == item)
        {
            RptOAD |= (u32)(Event_Item[i].OI << 16);
            break;
        }
    }

    if (i == FileItemInfoNum_Evt_Max) //找不到事件记录OI
    {
        return;
    }

    Offset = item / 8;
    i = item % 8;

    if (((EvtRptData.Para.RptMode[Offset] >> i) & 0x01) == ATIVE_REPORT) //上报方式为主动上报
    {
        addr = FileItemInfoOffAddr_EvtReport_end;
        if (mode == EVTSTART) //事件发生
        {
            if (((EvtRptData.Para.RptFlagHappen[Offset] >> i) & 0x01) == 0x01) //上报标识为发生上报
            {
                for (j = 0; j < 3; j++)
                {
                    if (EvtRptData.Para.RptChannel[j] == 9)
                    {
                        addr = FileItemInfoOffAddr_EvtReport_OADNumZB_A;
                        break;
                    }
                }
            }
        }
        else if (mode == EVTEND)
        {
            if (((EvtRptData.Para.RptFlagEnd[Offset] >> i) & 0x01) == 0x01) //上报标识为结束上报
            {
                for (j = 0; j < 3; j++)
                {
                    if (EvtRptData.Para.RptChannel[j] == 9)
                    {
                        addr = FileItemInfoOffAddr_EvtReport_OADNumZB_A;
                        break;
                    }
                }
            }
        }

        if (addr != FileItemInfoOffAddr_EvtReport_end) //
        {
            for (k = 0; k < EvtRptData.ListZB_A.OADNum; k++)
            {
                if (RptOAD == EvtRptData.ListZB_A.OAD[k]) //列表已产生，不再重复记录
                {
                    break;
                }
            }

            if (k == EvtRptData.ListZB_A.OADNum)
            {
                EvtRptData.ListZB_A.OAD[EvtRptData.ListZB_A.OADNum] = RptOAD;
                EvtRptData.ListZB_A.OADNum++;

                fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNumZB_A, &EvtRptData.ListZB_A, sizeof(sReportList_TypeDef));
            }

            if (item == FileItemInfoNum_Evt_PowDn)
            {
                if ((Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN) && (EvtRptData.PowerUpTime > 59))
                {
                    EvtRptData.RptType = RPTEVT_POWNDOWN;
                    EvtRptData.ReportCnt = 3; //主动上报3次
                    EvtRptData.tReportDely = 0; //
                    fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_PowerUpTime, &EvtRptData.PowerUpTime, 1);  //PowerUpTime不清零，上电后判断是否需要上报
                }
                else if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWDN) && (EvtRptData.PowerUpTime > 59))
                {
                    EvtRptData.RptType = RPTEVT_POWNUP;
                    EvtRptData.ReportCnt = 3; //主动上报3次
                    EvtRptData.tReportDely = 0; //
                    EvtRptData.PowerUpTime = 0;
                    fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_PowerUpTime, &EvtRptData.PowerUpTime, 1);
                }
                else
                {
                    EvtRptData.RptType = 0;
                    EvtRptData.ReportCnt = 0; //不上报
                    EvtRptData.tReportDely = 0; //
                    EvtRptData.PowerUpTime = 0;
                    fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_PowerUpTime, &EvtRptData.PowerUpTime, 1);
                }
            }
            else
            {
                EvtRptData.RptType = RPTEVT_OTHER;
                EvtRptData.ReportCnt = 3; //主动上报3次
                EvtRptData.tReportDely = 0; //
            }
        }
    }

    //-------------------------
    if (((EvtRptData.Para.RptMode[Offset] >> i) & 0x01) == FOLLOW_REPORT) //上报方式为跟随上报
    {
        addr = FileItemInfoOffAddr_EvtReport_end;

        if (mode == EVTSTART) //事件发生
        {
            if (((EvtRptData.Para.RptFlagHappen[Offset] >> i) & 0x01) == 0x01) //上报标识为发生上报
            {
                for (j = 0; j < 3; j++)
                {
                    if (EvtRptData.Para.RptChannel[j] == 9)
                    {
                        addr = FileItemInfoOffAddr_EvtReport_OADNumZB_F;
                        EvtRptData.RecOADZB = RptOAD;

                        fnFile_Read(FileId_EvtReport, addr, &tempList, sizeof(sReportList_TypeDef));
                        for (k = 0; k < tempList.OADNum; k++)
                        {
                            if (RptOAD == tempList.OAD[k]) //列表已产生，不再重复记录
                            {
                                break;
                            }
                        }

                        if (k == tempList.OADNum)
                        {
                            tempList.OAD[tempList.OADNum] = RptOAD;
                            tempList.OADNum++;

                            fnFile_Write(FileId_EvtReport, addr, &tempList, sizeof(sReportList_TypeDef));
                        }
                    }
                    else if (EvtRptData.Para.RptChannel[j] == 1)
                    {
                        addr = FileItemInfoOffAddr_EvtReport_OADNum485_F;
                        EvtRptData.RecOAD485 = RptOAD;

                        fnFile_Read(FileId_EvtReport, addr, &tempList, sizeof(sReportList_TypeDef));
                        for (k = 0; k < tempList.OADNum; k++)
                        {
                            if (RptOAD == tempList.OAD[k]) //列表已产生，不再重复记录
                            {
                                break;
                            }
                        }

                        if (k == tempList.OADNum)
                        {
                            tempList.OAD[tempList.OADNum] = RptOAD;
                            tempList.OADNum++;

                            fnFile_Write(FileId_EvtReport, addr, &tempList, sizeof(sReportList_TypeDef));
                        }
                    }
                    else if (EvtRptData.Para.RptChannel[j] == 2)
                    {
                        addr = FileItemInfoOffAddr_EvtReport_OADNum4852_F;
                        EvtRptData.RecOAD4852 = RptOAD;

                        fnFile_Read(FileId_EvtReport, addr, &tempList, sizeof(sReportList_TypeDef));
                        for (k = 0; k < tempList.OADNum; k++)
                        {
                            if (RptOAD == tempList.OAD[k]) //列表已产生，不再重复记录
                            {
                                break;
                            }
                        }

                        if (k == tempList.OADNum)
                        {
                            tempList.OAD[tempList.OADNum] = RptOAD;
                            tempList.OADNum++;

                            fnFile_Write(FileId_EvtReport, addr, &tempList, sizeof(sReportList_TypeDef));
                        }
                    }
                }
            }
        }
        else if (mode == EVTEND)
        {
            if (((EvtRptData.Para.RptFlagEnd[Offset] >> i) & 0x01) == 0x01) //上报标识为结束上报
            {
                for (j = 0; j < 3; j++)
                {
                    if (EvtRptData.Para.RptChannel[j] == 9)
                    {
                        addr = FileItemInfoOffAddr_EvtReport_OADNumZB_F;
                        EvtRptData.RecOADZB = RptOAD;

                        fnFile_Read(FileId_EvtReport, addr, &tempList, sizeof(sReportList_TypeDef));
                        for (k = 0; k < tempList.OADNum; k++)
                        {
                            if (RptOAD == tempList.OAD[k]) //列表已产生，不再重复记录
                            {
                                break;
                            }
                        }

                        if (k == tempList.OADNum)
                        {
                            tempList.OAD[tempList.OADNum] = RptOAD;
                            tempList.OADNum++;

                            fnFile_Write(FileId_EvtReport, addr, &tempList, sizeof(sReportList_TypeDef));
                        }
                    }
                    else if (EvtRptData.Para.RptChannel[j] == 1)
                    {
                        addr = FileItemInfoOffAddr_EvtReport_OADNum485_F;
                        EvtRptData.RecOAD485 = RptOAD;

                        fnFile_Read(FileId_EvtReport, addr, &tempList, sizeof(sReportList_TypeDef));
                        for (k = 0; k < tempList.OADNum; k++)
                        {
                            if (RptOAD == tempList.OAD[k]) //列表已产生，不再重复记录
                            {
                                break;
                            }
                        }

                        if (k == tempList.OADNum)
                        {
                            tempList.OAD[tempList.OADNum] = RptOAD;
                            tempList.OADNum++;

                            fnFile_Write(FileId_EvtReport, addr, &tempList, sizeof(sReportList_TypeDef));
                        }
                    }
                    else if (EvtRptData.Para.RptChannel[j] == 2)
                    {
                        addr = FileItemInfoOffAddr_EvtReport_OADNum4852_F;
                        EvtRptData.RecOAD4852 = RptOAD;

                        fnFile_Read(FileId_EvtReport, addr, &tempList, sizeof(sReportList_TypeDef));
                        for (k = 0; k < tempList.OADNum; k++)
                        {
                            if (RptOAD == tempList.OAD[k]) //列表已产生，不再重复记录
                            {
                                break;
                            }
                        }

                        if (k == tempList.OADNum)
                        {
                            tempList.OAD[tempList.OADNum] = RptOAD;
                            tempList.OADNum++;

                            fnFile_Write(FileId_EvtReport, addr, &tempList, sizeof(sReportList_TypeDef));
                        }
                    }
                }
            }
        }
    }
}

/*********************************************************************************************************
** Function name:   fnRptStatus_Update
** Descriptions:    主动上报状态字更新
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnUpdate_RptStatus(u32 status)
{
    u8 i;

    if ((EvtRptData.Para.RptStatusMode & status) == status)
    {
        for (i = 0; i < 3; i++)
        {
            if (EvtRptData.Para.RptChannel[i] == 9)
            {
                if ((EvtRptData.Status.RptStuZBBack & status) != status) //之前未产生过上报
                {
                    if (EvtRptData.Para.RptStatusAllow == 0) //状态字为主动上报
                    {
                        EvtRptData.ReportCnt = 3; //主动上报3次
                        EvtRptData.tReportDely = 0;  //主动上报间隔10秒
                    }

                    EvtRptData.Status.RptStuZB |= status;
                    EvtRptData.Status.RptStuZBBack |= status;
                    fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatusZB, (u8 *)&EvtRptData.Status.RptStuZB, 8);
                }
            }
            else if (EvtRptData.Para.RptChannel[i] == 1)
            {
                if ((EvtRptData.Status.RptStu485Back & status) != status) //之前未产生过上报
                {
                    EvtRptData.Status.RptStu485 |= status;
                    EvtRptData.Status.RptStu485Back |= status;
                    fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatus485, (u8 *)&EvtRptData.Status.RptStu485, 8);
                }
            }
            else if (EvtRptData.Para.RptChannel[i] == 2)
            {
                if ((EvtRptData.Status.RptStu4852Back & status) != status) //之前未产生过上报
                {
                    EvtRptData.Status.RptStu4852 |= status;
                    EvtRptData.Status.RptStu4852Back |= status;
                    fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatus4852, (u8 *)&EvtRptData.Status.RptStu4852, 8);
                }
            }
        }
    }
}

/*********************************************************************************************************
** Function name:   fnClr_RptStatus
** Descriptions:    主动上报状态字清零(故障事件结束，且事件上报已读取时执行清零)
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnClr_RptStatus(u32 status)
{
    if ((EvtRptData.Status.RptStuZB & status) != status) //事件上报已被读走
    {
        EvtRptData.Status.RptStuZB &= ~status;
        EvtRptData.Status.RptStuZBBack &= ~status;
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatusZB, (u8 *)&EvtRptData.Status.RptStuZB, 8);
    }

    if ((EvtRptData.Status.RptStu485 & status) != status) //事件上报已被读走
    {
        EvtRptData.Status.RptStu485 &= ~status;
        EvtRptData.Status.RptStu485Back &= ~status;
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatus485, (u8 *)&EvtRptData.Status.RptStu485, 8);
    }

    if ((EvtRptData.Status.RptStu4852 & status) != status) //事件上报已被读走
    {
        EvtRptData.Status.RptStu4852 &= ~status;
        EvtRptData.Status.RptStu4852Back &= ~status;
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatus4852, (u8 *)&EvtRptData.Status.RptStu4852, 8);
    }
}

/*********************************************************************************************************
** Function name:   fnSavePowerOnEvtStop
** Descriptions:    上电情况下存在失压，失流，断相，电压不平衡等未结束时间时，
**                       掉电后结束
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnWrite_EvtStopRecord(u8 item, u8 nphase)
{
    u32 OffAddr;
    sDate_time_s_TypeDef PowDn_Datetimes;
    sEvtRcdHead_TypeDef  headData;
    u8  *DataBuf, *EvtData;
    sContextList_TypeDef    tmplist;
    u8 listOADSumNum, j;
    u16 recordlen, maxcnt_u16, len;
    OAD_Analyse_TypeDef *pOad;

    DataBuf = (u8 *)fnBufTemp_Alloc(512);
    if (DataBuf == NULL)
    {
        return ;
    }
    Std_Memset(DataBuf, 0, 512);

    EvtData = (u8 *)fnBufTemp_Alloc(512);
    if (EvtData == NULL)
    {
        return ;
    }
    Std_Memset(EvtData, 0, 512);

    fnWDT_Restart();

    fnFile_Read(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_PowDnTime, &PowDn_Datetimes, sizeof(sDate_time_s_TypeDef));

    len = sizeof(sEvtRcdHead_TypeDef);
    OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr + (u32)nphase * len;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len);

    Std_Memcpy((u8 *)&headData.EventEndTime, (u8 *)&PowDn_Datetimes, sizeof(sDate_time_s_TypeDef));     //刷新系统时间RAM
    headData.EventTime = Event.EvtSumTime[3 * item + nphase];

    //-------根据关联对象属性表获取数据-----------------
    //-----读取关联对象属性表-不区分ABC相--------
    len = FileItemInfo_EvtCtxlist[item].Len;
    OffAddr = FileItemInfo_EvtCtxlist[item].OffAddr;
    fnFile_Read(FileId_EvtCtxlist, OffAddr, DataBuf, len);

    listOADSumNum = *DataBuf++;

    Std_Memcpy((u8 *)&recordlen, DataBuf, 2);
    DataBuf += 2;

    //-------关联对象属性表合法性判断------------------
    if ((recordlen > MAX_RCDLEN) || (listOADSumNum > 100)) //容错处理，不超过100个OAD
    {
        fnBufTemp_Free(DataBuf);
        fnBufTemp_Free(EvtData);
        return;
    }

    //--class24存储空间分配: 10条A相 + 10条B相 + 10条C相-----------------
    maxcnt_u16 = (u16)MAX_EVRECORD_TABLE[item];    //获取最大记录数
    if (headData.EventSumCnt % maxcnt_u16)
    {
        OffAddr = ((headData.EventSumCnt % maxcnt_u16) - 1) * (u32)recordlen;
    }
    else
    {
        OffAddr = (maxcnt_u16 - 1) * (u32)recordlen;
    }

    OffAddr += FileItemInfo_EvtRecord[item].OffAddr + (u32)(nphase * recordlen * maxcnt_u16);

    //--------读取事件发生前数据------------------------
    fnFile_Read(FileId_EvtRecord, OffAddr, EvtData, recordlen);
    Std_Memcpy(EvtData + 11, (u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef));

    for (j = 0; j < listOADSumNum; j++)
    {
        Std_Memcpy(&tmplist, DataBuf, sizeof(sContextList_TypeDef));
        DataBuf += sizeof(sContextList_TypeDef);

        pOad = (OAD_Analyse_TypeDef *)&tmplist.OAD;
        //---------更新事件发生后数据------------------------
        if ((pOad->AtrFeature == EVT_END_BEFORE) || (pOad->AtrFeature == EVT_END_AFTER))
        {
            tmplist.OAD = (tmplist.OAD & 0xFFFF1FFF);
            tmplist.len = fnGet_OADStoreData(tmplist.OAD, EvtData + tmplist.OffPos);
        }
    }

    //----------写事件记录----------------
    fnFile_Write(FileId_EvtRecord, OffAddr, EvtData, recordlen);

    len = sizeof(sEvtRcdHead_TypeDef);
    OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr + (u32)(nphase * len);
    fnFile_Write(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len);

    fnEvent_Report(item, nphase, EVTEND);

    fnBufTemp_Free(DataBuf);
    fnBufTemp_Free(EvtData);
}

/*********************************************************************************************************
** Function name:   fnSavePowerOnEvtStop
** Descriptions:    上电情况下存在失压，失流，断相，电压不平衡等未结束时间时，
**                       掉电后结束
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnSavePowerOnEvtStop(void)
{
    #if(0)
    //  sDate_time_s_TypeDef   PowDn_Datetimes;
    //  u8      i, j ;
    u8      len, item;
    u32 OffAddr;

    sEvtRcdHead_TypeDef  headData;

    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }
    fnWDT_Restart();

    #if(nPhs==ThreePhs)
    for (i = 0; i < FileItemInfoNum_Evt_QtOverNeed; i++) //
    {
        for (j = 0; j < nPhs; j++) //A/B/C三相
        {
            len = 2 * sizeof(sDate_time_s_TypeDef);
            OffAddr = FileItemInfo_EvtRcdHead[i].OffAddr + j * sizeof(sEvtRcdHead_TypeDef) + 4;

            fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventStartTime, (u32)len);  //读取事件记录头的开始时间、结束时间

            //----事件记录发生时间不为0，结束时间为0-------
            if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
                (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
            {
                fnWrite_EvtStopRecord(i, j);
            }
        }
    }

    for (i = FileItemInfoNum_Evt_QtOverNeed; i < FileItemInfoNum_Evt_PtOverNeed; i++) //
    {
        for (j = 0; j < 4; j++) //
        {
            len = 2 * sizeof(sDate_time_s_TypeDef);
            OffAddr = FileItemInfo_EvtRcdHead[i].OffAddr + j * sizeof(sEvtRcdHead_TypeDef) + 4;

            fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventStartTime, (u32)len);  //读取事件记录头的开始时间、结束时间

            //----事件记录发生时间不为0，结束时间为0-------
            if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
                (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
            {
                fnWrite_EvtStopRecord(i, j);
            }
        }
    }
    fnWDT_Restart();
    for (i = 0; i < 7; i++) //
    {
        switch (i)
        {
            case 0:
                item = FileItemInfoNum_Evt_PtOverNeed;
                break;

            case 1:
                item = FileItemInfoNum_Evt_NtOverNeed;
                break;

            case 2:
                item = FileItemInfoNum_Evt_InPhaVol;
                break;

            case 3:
                item = FileItemInfoNum_Evt_InPhaCur;
                break;

            case 4:
                item = FileItemInfoNum_Evt_UnblVol;
                break;

            case 5:
                item = FileItemInfoNum_Evt_UnblCur;
                break;

            case 6:
                item = FileItemInfoNum_Evt_OverUnblCur;
                break;
        }

        len = 2 * sizeof(sDate_time_s_TypeDef);
        OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr + 4;

        fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventStartTime, (u32)len);  //读取事件记录头的开始时间、结束时间

        //----事件记录发生时间不为0，结束时间为0-------
        if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
            (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
        {
            fnWrite_EvtStopRecord(item, 0);
        }
    }
    fnWDT_Restart();

    //--------补磁场干扰事件记录---------------------
    len = 2 * sizeof(sDate_time_s_TypeDef);
    OffAddr = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_MagnetDisturb].OffAddr + 4;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventStartTime, len);

    //----事件记录发生时间不为0，结束时间为0-------
    if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        fnSysDateTimes(&SysDatetimes);  //时间恢复
        Key.Release &= ~KEY_VAL_STROMAN;
        fnEvent_Operation(FileItemInfoNum_Evt_MagnetDisturb, EVTEND, NULL);
        Inactive.InactiveFlag.EventFlag &= ~((u32)1 << EVENT_STYLE_MagnetDisturb);
    }
    #else
    len = 2 * sizeof(sDate_time_s_TypeDef);
    //  item = FileItemInfoNum_Evt_OverCur;
    OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr + 4;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventStartTime, (u32)len);  //读取事件记录头的开始时间、结束时间

    //----事件记录发生时间不为0，结束时间为0-------
    if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        fnWrite_EvtStopRecord(item, 0);
    }

    #endif
    //--------补电源异常事件记录---------------------
    len = 2 * sizeof(sDate_time_s_TypeDef);
    //  OffAddr = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_PowerErr].OffAddr + 4;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventStartTime, len);

    //----事件记录发生时间不为0，结束时间为0-停电有电源异常事件记录------
    if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        Std_Memcpy((u8 *)&SysDatetimes, (u8 *)&headData.EventStartTime, sizeof(sDate_time_s_TypeDef));      //刷新系统时间RAM
        //      fnEvent_Operation(FileItemInfoNum_Evt_PowerErr ,EVTSTART , NULL);
        fnWDT_Restart();
        fnSysDateTimes(&SysDatetimes);  //时间恢复
        //      fnEvent_Operation(FileItemInfoNum_Evt_PowerErr ,EVTEND, NULL);
    }
    fnWDT_Restart();

    fnSysDateTimes(&SysDatetimes);  //时间恢复
    #endif
}

/*********************************************************************************************************
** Function name:   fnSaveQLossVolEvt
** Descriptions:    上电保存全失压事件记录
**
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
#if 0 //(nPhs==ThreePhs)
void fnSaveQLossVolEvt(void)
{
    u32 OffAddr, temp1, temp2;
    u16 recordlen, maxcnt_u16;
    u8 i;
    sEvtRcdHead_TypeDef  headData, headData_Record;

    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }
    fnWDT_Restart();

    //-------读取上1次全失压事件记录头--------------
    OffAddr = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_QLossVol].OffAddr;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, sizeof(sEvtRcdHead_TypeDef));

    //-----获取事件记录长度---------------
    OffAddr = FileItemInfo_EvtCtxlist[FileItemInfoNum_Evt_QLossVol].OffAddr;
    fnFile_Read(FileId_EvtCtxlist, OffAddr + 1, (u8 *)&recordlen, 2);

    maxcnt_u16 = (u16)MAX_EVRECORD_TABLE[FileItemInfoNum_Evt_QLossVol];

    if (headData.EventSumCnt % maxcnt_u16)
    {
        OffAddr = ((headData.EventSumCnt % maxcnt_u16) - 1) * (u32)recordlen;
    }
    else
    {
        OffAddr = (maxcnt_u16 - 1) * (u32)recordlen;
    }

    OffAddr += FileItemInfo_EvtRecord[FileItemInfoNum_Evt_QLossVol].OffAddr;
    //读取flash的最近一次事件发生次数(4byte)，发生时间(7byte),结束时间(7byte)
    fnFile_Read(FileId_EvtRecord, OffAddr, (u8 *)&headData_Record, 18);

    if ((headData.EventSumCnt > headData_Record.EventSumCnt) &&
        (fnDFCompData((u8 *)&headData.EventStartTime, (u8 *)&headData_Record.EventStartTime, sizeof(sDate_time_s_TypeDef)) != 0))
    {
        //-------补全失压发生事件记录-----------
        Event.StartFlag.EvFlag.EvFlagData0 = 0;
        Event.StartFlag.EvFlag.EvFlagData1 = 0;

        Event.StartFlag.EvFlagBit.QLossVol = 1;
        Std_Memcpy((u8 *)&SysDatetimes, (u8 *)&headData.EventStartTime, sizeof(sDate_time_s_TypeDef));
        fnFile_Read(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_Irms, &MeasureRms.PubData.I[0], FileItemInfoLen_PowDn_Irms);
        fnEvent_Exec();
        Std_Memset((u8 *)&MeasureRms.PubData.I[0], 0x00, FileItemInfoLen_PowDn_Irms);

        //-----------计算全失压累计时间---------------
        fnSysDateTimes(&SysDatetimes);
        temp1 = fnDateTimeToSec(&SysDatetimes);
        temp2 = fnDateTimeToSec(&headData.EventStartTime);
        if (temp1 > temp2)
        {
            for (i = 0; i < MAX_EVENTTYPE; i++)
            {
                if (FileItemInfoNum_Evt_QLossVol == EvConst[i].FileId)
                {
                    Event.EvtSumTime[i] += (temp1 - temp2);

                    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtSumTime + 4 * i, (u8 *)&Event.EvtSumTime[i], 4);

                    break;
                }
            }
        }
    }

    //------发生时间为0，结束时间不为0，则当前处于全失压状态---------------
    if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        // 将状态变为0
        EvStatusInter.lStatus[1] |= EVGEN_MARK_QLOSSVOL;
        EvStatusInter.Status[1] |= EVGEN_MARK_QLOSSVOL;

        Event.ExecFlag.EvFlag.EvFlagData1 |= EVGEN_MARK_QLOSSVOL;
        EvStatusInter.tQLossVol = 5;  //上电后全失压判断延时事件为3秒
    }
}

//-----------------电压合格率------------------------

void fnStat_Init(void)
{
    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }

    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_ParaVolYield, (u8 *)&Stat.PriPara.UUp, sizeof(sVolYieldPara_TypeDef));
    fnCrc_Check(0, (u8 *)&Stat.PriPara, sizeof(Stat.PriPara) - 2, (u8 *)&Stat.PriPara.Crc);

    fnFile_Read(FileId_CurStat, FileItemInfoOffAddr_Stat_UaElig_Day, (u8 *)&Stat.PubData, sizeof(sStatFile_TypeDef));
}

//--------UElig电压合格率判断函数-----------------------
void fnUEligStat_Exec(void)
{
    u32 Tmp1, Tmp2, Tmp3;
    u8 i ;

    if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON) || (Inactive.PubData.InactiveStamp))
    {
        return;
    }

    if ((Bkgrd.PubData.fChange.Flag & BKGRD_FCHANGE_MINUTE) == 0)
    {
        return;
    }

    if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON) || (Inactive.PubData.InactiveStamp))
    {
        return;
    }

    if (fnCrc_Check(1, (u8 *)&Stat.PriPara, sizeof(Stat.PriPara) - 2, (u8 *)&Stat.PriPara.Crc))
    {
        fnStat_Init();
    }

    for (i = 0 ; i < 3 ; i++)
    {
        if ((MeasureRms.PubData.U[i] > Stat.PriPara.UCheckDn) && (MeasureRms.PubData.U[i] < Stat.PriPara.UCheckUp))
        {
            //A相电压监测时间
            Stat.PubData.UElig_Day[i].tInspectU++;
            Stat.PubData.UElig_Month[i].tInspectU++;
        }
        //---分相电压超上限时间---
        if ((MeasureRms.PubData.U[i] > Stat.PriPara.UUp) && (MeasureRms.PubData.U[i] < Stat.PriPara.UCheckUp))
        {
            //A相
            Stat.PubData.UElig_Day[i].tOverUpU++;
            Stat.PubData.UElig_Month[i].tOverUpU++;
        }
        //---分相电压超下限时间
        if ((MeasureRms.PubData.U[i] < Stat.PriPara.UDn) && (MeasureRms.PubData.U[i] > Stat.PriPara.UCheckUp))
        {
            //A相
            Stat.PubData.UElig_Day[i].tOverUpU++;
            Stat.PubData.UElig_Month[i].tOverUpU++;
        }

        if (Stat.PubData.UElig_Day[i].tInspectU)
        {
            Tmp1 = Stat.PubData.UElig_Day[i].tInspectU;         //分相电压监测时间
            Tmp2 = Stat.PubData.UElig_Day[i].tOverUpU;          //分相超上限时间
            Tmp3 = Stat.PubData.UElig_Day[i].tOverDnU;      //分相超下限时间
            Stat.PubData.UElig_Day[i].OverRateU = (Tmp2 + Tmp3) * 10000 / Tmp1;           //分相电压超限率
            Stat.PubData.UElig_Day[i].EligRateU = (Tmp1 - Tmp2 - Tmp3) * 10000 / Tmp1; //分相电压合格率
        }

        if (Stat.PubData.UElig_Month[i].tInspectU)
        {
            Tmp1 = Stat.PubData.UElig_Month[i].tInspectU;       //分相电压监测时间
            Tmp2 = Stat.PubData.UElig_Month[i].tOverUpU;            //分相超上限时间
            Tmp3 = Stat.PubData.UElig_Month[i].tOverDnU;        //分相超下限时间
            Stat.PubData.UElig_Month[i].OverRateU = (Tmp2 + Tmp3) * 10000 / Tmp1;           //分相电压超限率
            Stat.PubData.UElig_Month[i].EligRateU = (Tmp1 - Tmp2 - Tmp3) * 10000 / Tmp1;   //分相电压合格率
        }
    }
    //--------每小时存一次E2---------
    if (Bkgrd.PubData.fChange.Flag & BKGRD_FCHANGE_HOUR)
    {
        fnFile_Write(FileId_CurStat, FileItemInfoOffAddr_Stat_UaElig_Day, (u8 *)&Stat.PubData, sizeof(sStatFile_TypeDef));
    }
}
#endif
/*********************************************************************************************************
** Function name:   fnEvtPrg_End
** Descriptions:
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnEvtPrg_End(void)
{
    if (Event.PriData.Prg_Step)  //有编程事件产生时，编程结束事件
    {
        //          fnEvent_Operation(FileItemInfoNum_Evt_Prg , EVTEND, NULL );
    }
}
