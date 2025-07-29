
#define  _EVENT_GLOBALS
#include <App.h>

//----------����¼���¼��׼�¼���¼��Ԫ������ͨѶ�޸�--------------
const   sCList6_TypeDef EvtPrg_StdRecList =
{
    6, 69,
    0x20220200, 4,    0,
    0x201E0200, 7,    4,
    0x20200200, 7,    11,
    0x20240200, 0,    18,    //�¼�����Դ
    0x33000200, 0,    18,
    0x33020206, 51, 18    //51 = 10 * 5 + 1(1byte��̸���)
};

//----EvtPrg_StdRecList ��Ӧ����������
const   u8  EvtPrgStdRcdList_DataType[] =
{
    DTYPE_UINT32,
    DTYPE_DATETIME_S,
    DTYPE_DATETIME_S,
    NULL,  //�¼�����Դ
    NULL,
    DTYPE_ARRAY, 10, DTYPE_OAD
};
//----ʱ�α�------------
const   sCList7_TypeDef EvtPrgTable_StdRecList =
{
    7, 64,
    0x20220200, 4,    0,
    0x201E0200, 7,    4,
    0x20200200, 7,    11,
    0x20240200, 0,    18,    //�¼�����Դ
    0x33000200, 0,    18,
    0x33140206, 4,    18,
    0x33140207, 42, 22
};
//----EvtPrgTable_StdRecList ��Ӧ����������
const   u8  EvtPrgTableStdRcdList_DataType[] =
{
    DTYPE_UINT32,
    DTYPE_DATETIME_S,
    DTYPE_DATETIME_S,
    NULL,  //�¼�����Դ
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
    0x20240200, 0,    18,    //�¼�����Դ
    0x33000200, 0,    18,
    0x33150206, 4,  18,      //
    0x33150207, 6,  22      //
};

//----EvtHldy_StdRecList ��Ӧ����������
const   u8  EvtHldyStdRcdList_DataType[] =
{
    DTYPE_UINT32,
    DTYPE_DATETIME_S,
    DTYPE_DATETIME_S,
    NULL,  //�¼�����Դ
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
    0x20240200, 0,    18,    //�¼�����Դ
    0x33000200, 0,    18,
    0x330C0206, 4,  18,      //
};

//----EvtHldy_StdRecList ��Ӧ����������
const   u8  EvtClrStdRcdList_DataType[] =
{
    DTYPE_UINT32,
    DTYPE_DATETIME_S,
    DTYPE_DATETIME_S,
    NULL,  //�¼�����Դ
    NULL,
    DTYPE_ARRAY, 1, DTYPE_OMD,
};

//------�޹���Ϸ�ʽ����¼���¼---------------
const   sCList5_TypeDef EvtPrgQ_StdRecList =
{
    5, 19,
    0x20220200, 4,    0,
    0x201E0200, 7,    4,
    0x20200200, 7,    11,
    0x20240200, 1,    18,     //�¼�����Դ
    0x33000200, 0,    19
};

const   u8  EvtPrgQStdRcdList_DataType[] =
{
    DTYPE_UINT32,
    DTYPE_DATETIME_S,
    DTYPE_DATETIME_S,
    DTYPE_ENUM,    //�¼�����Դ
    NULL
};

//------class24��׼�¼���¼��Ԫ---------------
const   sCList4_TypeDef EvtC24_StdRecList =
{
    4, 18,
    0x20220200, 4,    0,
    0x201E0200, 7,    4,
    0x20200200, 7,    11,
    0x33000200, 0,    18
};

//------class7��׼�¼���¼��Ԫ---------------
const   sCList5_TypeDef EvtC7_StdRecList =
{
    5, 18,
    0x20220200, 4,    0,
    0x201E0200, 7,    4,
    0x20200200, 7,    11,
    0x20240200, 0,    18,     //�¼�����Դ
    0x33000200, 0,    18
};

const   u8  EvtStdRcdList_DataType[] =
{
    DTYPE_UINT32,
    DTYPE_DATETIME_S,
    DTYPE_DATETIME_S,
    NULL,      //�¼�����Դ
    NULL
};

//------------��׼�¼���¼��Ԫ--����ͨѶ�޸�--------------
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

//����¼���¼�ļ�����
const u8 MAX_EVRECORD_TABLE[] =
{
    MAX_POWDN_EVRECORD,                //�������¼���¼ 0
    MAX_EVRECORD,                      //����������¼���¼ 1
    MAX_EVRECORD,                  //���Уʱ�¼���¼ 2
    MAX_EVRECORD,                //��󿪸��¼���¼ 3
    MAX_EVRECORD,                //��󿪶˸��¼���¼ 4

    MAX_PrgSetPsw_EVRECORD,                //�����Կ�����¼���¼ 5
    MAX_BrdTime_EVRECORD,       //1 //�㲥Уʱ 6
    MAX_EVRECORD,                //������ģ���θ����¼���¼ 7
    MAX_EVRECORD,                //������ģ�������¼���¼ 8
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

// ͣ���ѹ��������
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

        // ͬ��ϵͳʱ��
        fnSysDateTimes(&SysDatetimes);

        // ͣ��ʱ��
        memcpy(&Volt.PwdnTime.second, &SysDatetimes.second, sizeof(sDate_time_s_TypeDef));

        // ��ѹ����
        Volt.VoltVal[0] = MeasureRms.PubData.U[0] / 100;
        Volt.VoltVal[1] = MeasureRms.PubData.U[1] / 100;
        Volt.VoltVal[2] = MeasureRms.PubData.U[2] / 100;

        // ��������
        Volt.CurVal[0] = MeasureRms.PubData.I[0] / 10;
        Volt.CurVal[1] = MeasureRms.PubData.I[1] / 10;
        Volt.CurVal[2] = MeasureRms.PubData.I[2] / 10;

        // ��������
        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_PwdnVoltLoss, &Volt.PwdnTime.second, FileItemInfoLen_HighState_PwdnVoltLoss);

        Inactive.EvtPwn.EvtVoltLoss = 0x5A;
        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                     &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
    }

    fnPowerDown_SleepWakeOpIO();
    fnSubClock_Init();
}

// �ϵ粹�뿪���¼���¼
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

    // ֮ǰΪ����״̬
    if ((fnJudge_Zero((u8 *)&headData.EventStartTime, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Zero((u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        // ���ϸǼ�¼
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
        // �����Ǽ�¼
        if ((Inactive.EvtPwn.CoverOpen == 0x5A)
            && (fnJudge_Zero((u8 *)&Inactive.EvtPwn.CoverOpenTime, sizeof(sDate_time_s_TypeDef)) == FALSE))
        {
            fnEvent_Operation(FileItemInfoNum_Evt_OpenCover, EVTSTART, (u8 *)&Inactive.EvtPwn.CoverOpenTime);

            Inactive.EvtPwn.CoverOpen = 0;
            memset(&Inactive.EvtPwn.CoverOpenTime, 0, sizeof(sDate_time_s_TypeDef));

            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                         &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
        }

        // ���ϸǼ�¼
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

    // ����椸Ǽ�¼
    OffAddr = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_OpenTail].OffAddr;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len);

    // ֮ǰΪ����״̬
    if ((fnJudge_Zero((u8 *)&headData.EventStartTime, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Zero((u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        // ���ϸǼ�¼
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
        // �����Ǽ�¼
        if ((Inactive.EvtPwn.TailOpen == 0x5A)
            && (fnJudge_Zero((u8 *)&Inactive.EvtPwn.TailOpenTime, sizeof(sDate_time_s_TypeDef)) == FALSE))
        {
            fnEvent_Operation(FileItemInfoNum_Evt_OpenTail, EVTSTART, (u8 *)&Inactive.EvtPwn.TailOpenTime);

            Inactive.EvtPwn.TailOpen = 0;
            memset(&Inactive.EvtPwn.TailOpenTime, 0, sizeof(sDate_time_s_TypeDef));

            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                         &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
        }

        // ���ϸǼ�¼
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

    // ��ͣ���ڼ��ѹ�������ݱ����־
    Inactive.EvtPwn.EvtVoltLoss = 0;
    Inactive.PubData.QLossVolTime = 0;
    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtPwn,
                 &Inactive.EvtPwn, FileItemInfoLen_HighState_EvtPwn);
}

// ���翪�Ǽ�¼
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

        // ��Ǽ�¼
        if (PinRead_KeyShell())
        {
            Key.Release |= 0X0040;          //��¼�ϸǼ�¼��
            Key.Press &= 0XFFBF;
        }
        else
        {
            Key.Press |= 0X0040;
            Key.Release &= 0XFFBF;
        }
    }

    // ͬ��ϵͳʱ��
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
        // ֮ǰΪ����״̬
        if (Inactive.Mng.Sta & EvtSta_OpenCover)
        {
            // �ϸ�
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

                // �رտ���IO���ж�
                Rn8xxx_INTC_Init(INTC_ID1, INTC_DoubleEdge, INTC_IRQ_DISABLE);

                Rn8xxx_GPIO_CfgFun(PinKCOVER, _NORMALIO);

                I2C_Clk_Dis;
            }
        }
        else
        {
            // ����
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
        // ����ť��
        // ֮ǰΪ����״̬
        if (Inactive.Mng.Sta & EvtSta_OpenTail)
        {
            // �ϸ�
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

                // �رտ���IO���ж�
                //              Rn8xxx_INTC_Init(INTC_ID1,INTC_DoubleEdge,INTC_IRQ_DISABLE);
                Rn8xxx_KBI_Init(KBI_ID3, KBI_FallingEdge, KBI_IRQ_DISABLE);

                Rn8xxx_GPIO_CfgFun(PinKBTMBOX, _NORMALIO);

                I2C_Clk_Dis;
            }
        }
        else
        {
            // ����
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
        case 0x40272300:        // ������������
            pDst[0] = pSrc[1];
            break;
        case 0x00102200:        // ����ǰ�����й��ܵ���
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
        case 0x00202200:        // ����ǰ�����й��ܵ���
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
        case 0xF0012500:        // ���ط���ʶ
            if (pSrc[4] == 0x06)
            {
                iOffset = pSrc[3] * (4 + 1) * 2;
            }
            iOffset += 6;
            memset(pDst, 0, ilen);
            memcpy(pDst, &pSrc[iOffset + 2], pSrc[iOffset + 1]);
            break;
        case 0xF4022204:        // ����ǰ����汾��
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
        case 0xF4028204:        // ����������汾��
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
        case 0xF4028202:        // ����Ӧ������
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
        case 0x40278200:        // �������
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

    maxcnt_u16 = (u16)MAX_EVRECORD_TABLE[item];    //��ȡ����¼��

    if ((item == FileItemInfoNum_Evt_SetClock) || (item == FileItemInfoNum_Evt_BroadcastTime))
    {
        Std_Memcpy((u8 *)&headData.EventStartTime, Buff, 7);
        fnGetCurrTime(&headData.EventEndTime);
        //-------class7��׼�¼���¼��Ԫ--------------
        Std_Memcpy(EvtData, (u8 *)&headData.EventSumCnt, EvtC7_StdRecList.reclen);   //��Ŵ�0��ʼ

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
            fnGetCurrTime(&headData.EventStartTime);  //�¼���ʼʱ��
            Std_Memset((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef));      //�������ʱ��

            if (Buff != NULL)
            {
                // ����ģ�������¼�
                if (item == FileItemInfoNum_Evt_MngUpdate)
                {
                    Std_MemRvs((u8 *)&headData.EventStartTime, &Buff[3], sizeof(sDate_time_s_TypeDef));
                    Std_MemRvs((u8 *)&headData.EventEndTime, &Buff[11], sizeof(sDate_time_s_TypeDef));
                    headData.nTarf = Buff[21] - 1;
                }
                // �����翪���¼�ʱ��
                else if ((item == FileItemInfoNum_Evt_OpenCover) || (item == FileItemInfoNum_Evt_OpenTail))
                {
                    Std_Memcpy((u8 *)&headData.EventStartTime, Buff, sizeof(sDate_time_s_TypeDef));
                }
                // �������¼���¼ʱ��
                else if (item == FileItemInfoNum_Evt_PowDn)
                {
                    Std_Memcpy((u8 *)&headData.EventStartTime, Buff, sizeof(sDate_time_s_TypeDef));
                }
            }

            Std_Memcpy(EvtData, (u8 *)&headData.EventSumCnt, EvtC7_StdRecList.reclen);      //��Ŵ�0��ʼ
        }
        else
        {
            //--------Ҫ��ȡԭ�¼���¼��ʼʱ����������-------------
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
                    //���¹���о����¼���¼ESAM���к�
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
                // �����翪���¼�ʱ��
                if ((item == FileItemInfoNum_Evt_OpenCover) || (item == FileItemInfoNum_Evt_OpenTail))
                {
                    Std_Memcpy((u8 *)&headData.EventEndTime, Buff, sizeof(sDate_time_s_TypeDef));
                }
            }

            Std_Memcpy(EvtData + 11, (u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef));  //�����¼���¼����ʱ��
        }
    }
    //-------���ݹ����������Ա��ȡ����-----------------
    //-----��ȡ�����������Ա�---------
    len = FileItemInfo_EvtCtxlist[item].Len;
    OffAddr = FileItemInfo_EvtCtxlist[item].OffAddr;
    fnFile_Read(FileId_EvtCtxlist, OffAddr, DataBuf, len);

    listOADSumNum = *DataBuf++;
    Std_Memcpy((u8 *)&recordlen, DataBuf, 2);
    DataBuf += 2;

    //-------�����������Ա�Ϸ����ж�------------------
    if ((recordlen > MAX_RCDLEN) || (listOADSumNum > 100)) //�ݴ���������100��OAD
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
            if ((item == FileItemInfoNum_Evt_PrgSetPsw) && (tmplist.OAD == 0xF1002400)) //��Կ�����¼���¼������ǰ��Կ�汾��
            {
                Std_MemRvs(EvtData + tmplist.OffPos, Buff, tmplist.len);
            }
            // ����о����¼���¼ ESAM���к�
            else if ((item == FileItemInfoNum_Evt_MngPlug) && (tmplist.OAD == 0xF1002200))
            {
                fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_EvtRcdBfEsam, EvtData + tmplist.OffPos, FileItemInfoLen_HighState_EvtRcdBfEsam);
            }
            // ����о�����¼�
            else if (item == FileItemInfoNum_Evt_MngUpdate)
            {
                fnGetEvtMngUpdateRcd(EvtData + tmplist.OffPos, &Buff[18], tmplist.OAD, tmplist.len);
            }
            else
            {
                // ��ʼͬʱ�������¼�
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
** Descriptions:    �¼���¼״̬��������
** input parameters:  item �¼���¼��ţ�=0xFF ȫ�壻
**                            nphase  ����A��=0 ; B��=1; C��=2; ����ȫ��=0xFF
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

    if (item == 0xFF) //ȫ��
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

//--------�����¼�---------------------------
void fnEvent_nphsEvt_Exec(void)
{
    uEventFlag_TypeDef  fEventStart, fEventTerm; //�¼�����/���� /��ֹ��־

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

    //-------class24 ���ݴ�����־������Ӧ�¼���¼---------------------------
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

    //---�¼�����---
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
                    Event.ExecFlag.EvFlag.EvFlagData0 |= D.EvFlag.EvFlagData0;      //����¼�����
                    Event.ExecFlag.EvFlag.EvFlagData1 |= D.EvFlag.EvFlagData1;      //����¼�����
                    continue;
                }
                nphase = EvConst[i].nPha;

                len = sizeof(sEvtRcdHead_TypeDef);
                OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr + (u32)nphase * len;

                fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, len);
                fnWDT_Restart();
                // �Ѿ��������¼�
                if ((fnJudge_Zero((u8 *)&headData.EventStartTime, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
                    (fnJudge_Zero((u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef)) == TRUE))
                {
                    continue;
                }

                fnGetCurrTime(&headData.EventStartTime);  //�¼���ʼʱ��
                Std_Memset((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef));     //����ʱ������

                headData.EventTime = Event.EvtSumTime[i];

                //-------���ݹ����������Ա��ȡ����-----------------
                //-----��ȡ�����������Ա�---------
                len = FileItemInfo_EvtCtxlist[item].Len;
                OffAddr = FileItemInfo_EvtCtxlist[item].OffAddr;
                fnFile_Read(FileId_EvtCtxlist, OffAddr, DataBuf, len);

                listOADSumNum = *DataBuf++;

                Std_Memcpy((u8 *)&recordlen, DataBuf, 2);
                DataBuf += 2;

                //-------�����������Ա�Ϸ����ж�------------------
                if ((recordlen > MAX_RCDLEN) || (listOADSumNum > 100)) //�ݴ���������100��OAD
                {
                    continue;
                }

                Std_Memset(EvtData, 0x00, recordlen);     //���ݻ�����0
                Std_Memcpy(EvtData, (u8 *)&headData.EventSumCnt, 18);   //��Ŵ�0��ʼ

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

                maxcnt_u16 = (u16)MAX_EVRECORD_TABLE[item];    //��ȡ����¼��

                if (headData.EventCnt < maxcnt_u16)
                {
                    headData.EventCnt ++;    //
                }

                headData.EventSumCnt ++;

                //--class24�洢�ռ����: 10��A�� + 10��B�� + 10��C��-----------------
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

                Event.ExecFlag.EvFlag.EvFlagData0 |= D.EvFlag.EvFlagData0;      //����¼�����
                Event.ExecFlag.EvFlag.EvFlagData1 |= D.EvFlag.EvFlagData1;      //����¼�����

                fnEvent_Report(item, nphase, EVTSTART);
            }
        }
    }

    if (fEventStart.EvFlag.EvFlagData0 | fEventStart.EvFlag.EvFlagData1)
    {
        fnBufTemp_Free(DataBuf);
        fnBufTemp_Free(EvtData);
        return; //�¼�δ�����겻�����¼�ִ�С�����������
    }

    //---�¼�����---
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
            fnGetCurrTime(&headData.EventEndTime);  //�¼���ʼʱ��

            headData.EventTime = Event.EvtSumTime[i];

            //-------���ݹ����������Ա��ȡ����-----------------
            //-----��ȡ�����������Ա�-������ABC��--------
            len = FileItemInfo_EvtCtxlist[item].Len;
            OffAddr = FileItemInfo_EvtCtxlist[item].OffAddr;
            fnFile_Read(FileId_EvtCtxlist, OffAddr, DataBuf, len);

            listOADSumNum = *DataBuf++;

            Std_Memcpy((u8 *)&recordlen, DataBuf, 2);
            DataBuf += 2;

            //-------�����������Ա�Ϸ����ж�------------------
            if ((recordlen > MAX_RCDLEN) || (listOADSumNum > 100)) //�ݴ���������100��OAD
            {
                continue;
            }

            //--class24�洢�ռ����: 10��A�� + 10��B�� + 10��C��-----------------
            maxcnt_u16 = (u16)MAX_EVRECORD_TABLE[item];    //��ȡ����¼��
            if (headData.EventSumCnt % maxcnt_u16)
            {
                OffAddr = ((headData.EventSumCnt % maxcnt_u16) - 1) * (u32)recordlen;
            }
            else
            {
                OffAddr = (maxcnt_u16 - 1) * (u32)recordlen;
            }

            OffAddr += FileItemInfo_EvtRecord[item].OffAddr + (u32)(nphase * recordlen * maxcnt_u16);

            //--------��ȡ�¼�����ǰ����------------------------
            fnFile_Read(FileId_EvtRecord, OffAddr, EvtData, recordlen);
            Std_Memcpy(EvtData + 11, (u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef));

            for (j = 0; j < listOADSumNum; j++)
            {
                Std_Memcpy(&tmplist, DataBuf, sizeof(sContextList_TypeDef));
                DataBuf += sizeof(sContextList_TypeDef);

                pOad = (OAD_Analyse_TypeDef *)&tmplist.OAD;
                //---------�����¼�����������------------------------
                if ((pOad->AtrFeature == EVT_END_BEFORE) || (pOad->AtrFeature == EVT_END_AFTER))
                {
                    tmplist.OAD = (tmplist.OAD & 0xFFFF1FFF);
                    tmplist.len = fnGet_OADStoreData(tmplist.OAD, EvtData + tmplist.OffPos);
                }
            }

            //----------д�¼���¼----------------
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
    fnEvent_nphsEvt_Exec();   //�����¼���¼

    //-------����״̬�жϼ��¼���¼-------------------
    fnOpenCoverTailEvent();

    fnEvent_OpExec();
}

//---------�¼�����-------------
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

    fnEvent_Clr_Status(0xFF, 0xFF);   //ȫ��

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

    // �������ģ����״̬��ESAM���к�??
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

    // ���ͣ���ڼ��ѹ��������
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
                //---������ģʽ�������ع���ʱ�䣬���ĵ�����㲻���ع���ʱ��---------
                Bkgrd.PubData.tWorkBat = 0;
                fnFile_Write(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_tWorkBat, &Bkgrd.PubData.tWorkBat, 4);
            }
            Bkgrd.PubData.MtSysSta.SysSta = Bkgrd.PubData.MtSysSta.SysSta & 0x0000F000; //--����ȫ��֤����ı�־λȫ��----

            //          Std_Memset((u8 *)&Secret.nPswRetry[0] , 0 , 10);
            //          fnFile_Write(FileId_InterTmp , FileItemInfoOffAddr_InterTmp_Secret , &Secret.nPswRetry[0] , 2);
            //          fnFile_Write(FileId_InterTmp , FileItemInfoOffAddr_InterTmp_Secret + 2 , &Secret.tPswFailClose[0] , 4);
            //          fnFile_Write(FileId_InterTmp , FileItemInfoOffAddr_InterTmp_Secret + 6 , &Secret.tPrgKeyValid , 2);
            //          fnFile_Write(FileId_InterTmp , FileItemInfoOffAddr_InterTmp_Secret + 8 , &Secret.tPrgKeyLock , 2);
            //          fnFile_Write(FileId_InterTmp , FileItemInfoOffAddr_InterTmp_Secret + 10 , &Secret.nMacErr , 1 );

            fnFile_Clr(FileId_FrzRcdHead) ;

            for (i = 0; i < MAX_FRZMIN_LINE; i++)
            {
                Std_Memset((u8 *)&buf, 0x00, sizeof(sFrzRcdHead_TypeDef));  //��8�����Ӷ�������ͷ sFrzRcdHead_TypeDef
                OffAddr = FileItemInfo_FrzMinLineHead[i].OffAddr + sizeof(sFrzMinLinePara_TypeDef);  //��¼ͷ��������
                fnFile_Write(FileId_FrzMinLineHead, OffAddr, (u8 *)&buf, sizeof(sFrzRcdHead_TypeDef));
            }

            fnWrite_PowDn_FrzRmDayTime();
            fnWrite_PowDn_FrzDayTime();

            //fnEnergy_MoneyInit();
            #if(METERTYPE)
            Bkgrd.PubData.UpRunFileFlag = 0x5a;
            #endif

            fnUpDate_FrzParaOffPos();

            //-----�¼������¼���¼���---------------
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
        fnEvent_EvtClr();   //�¼�����

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

    // ���˸�״̬���û����жϴ�����
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

    // ͨѶ�յ�����ģ��ESAM���к�
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
        if (Key.Release & KEY_VAL_SHELL)                        // �ϸǹر�
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
        if (Key.Press & KEY_VAL_SHELL)                      // �ϸǴ�
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

    // ����״̬�������ж�
    //  if( (Bkgrd.PubData.tMngPlug == 0) && (Bkgrd.PubData.MtSta.MtSta7.StaBit.PowDn == 0) )
    if (Bkgrd.PubData.tMngPlug == 0)
    {
        // ����ģ�����¼�
        if (Inactive.InactiveFlag.EventFlag & ((u32)1 << EVENT_STYLE_MngPlug))
        {
            if (Key.Release & KEY_VAL_CTRLMODUPLGCHK)       // ����
            {
                Key.Release &= ~KEY_VAL_CTRLMODUPLGCHK;
                if (Inactive.Mng.Sta & EvtSta_MngPlug)              // ֮ǰΪ�γ�״̬
                {
                    Inactive.Mng.Sta &= ~EvtSta_MngPlug;

                    // ��ʹ��ȫFF���
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
            if (Key.Press & KEY_VAL_CTRLMODUPLGCHK)         // �γ�
            {
                Key.Press &= ~KEY_VAL_CTRLMODUPLGCHK;
                if (!(Inactive.Mng.Sta & EvtSta_MngPlug))           // �ǰγ�״̬
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

        // ����ģ��ESAM���к��б仯
        if (fnEvtMngPlug_EsamCheck())
        {
            // ֮ǰΪ�γ�״̬
            if (Inactive.Mng.Sta & EvtSta_MngPlug)
            {
                fnEvent_Operation(FileItemInfoNum_Evt_MngPlug, EVTEND, NULL);
                memcpy(&Inactive.Mng.OldEsam[0], &Inactive.Mng.NewEsam[0], 8);

                Inactive.Mng.RevEsam |= Mng_SynEsam;

                Bkgrd.PubData.MtSysSta.SysStaBit.EvtControlPullOut = 1;
                Event.StartFlag.EvFlagBit.MngPlug = 0;
                Inactive.Mng.Sta &= ~EvtSta_MngPlug;
            }
            // ֮ǰΪ����״̬
            else
            {
                // ʹ����ESAM���к��滻
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
            // ʹ�ù���оESAM���к��滻
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
        if (Key.Release & KEY_VAL_JUNBOX)                       // �˸ǹر�
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
        if (Key.Press & KEY_VAL_JUNBOX)                         // �˸Ǵ�
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

    // ͬ�����´洢ee
    if (Inactive.Mng.RevEsam & Mng_SynEsam)
    {
        Inactive.Mng.LstEvtFlag = Inactive.InactiveFlag.EventFlag;

        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtRcdBfEsam,
                     &Inactive.Mng.OldEsam[0], FileItemInfoLen_HighState_EvtMngStr);

        Inactive.Mng.RevEsam &= ~Mng_SynEsam;
    }

    return;
}

//---------Ϊ������������ϱ������1�ε��緢���¼���¼��E2--�������ϱ���־-------
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

    //------�¼���¼ͷ����ʱ�䲻Ϊ0������ʱ��Ϊ0����ʾ�е����¼������¼���¼-------
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

    //      maxcnt_u16 = ( u16 )MAX_EVRECORD_TABLE[FileItemInfoNum_Evt_PowDn];  //��ȡ����¼��
    //
    //      fnGetCurrTime(&headData.EventStartTime);  //�¼���ʼʱ��
    //      Std_Memset( (u8 *)&headData.EventEndTime , 0x00 , sizeof(sDate_time_s_TypeDef) );  //�������ʱ��
    //
    //      Std_Memcpy( EvtData, (u8 *)&headData.EventSumCnt, EvtC7_StdRecList.reclen );    //��Ŵ�0��ʼ
    //
    //      //-------���ݹ����������Ա��ȡ����-----------------
    //      //-----��ȡ�����������Ա�---------
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
** Descriptions:    E2���ݸ��ǵ�Flash
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

    // �������¼
    if (Inactive.EvtPwn.EvtPwdn == 0x5A)
    {
        Inactive.EvtPwn.EvtPwdn = 0;

        fnEvent_Operation(FileItemInfoNum_Evt_PowDn, EVTSTART, (u8 *)&Inactive.EvtPwn.EvtPwdnTime);

        //-----------��������ۼ�ʱ��---------------
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

    //����¼�����
    Event.ExecFlag.EvFlag.EvFlagData0 |= EVGEN_MARK_POWDN;
    //�ϵ���ж���ʱ�¼�Ϊ3��
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

    //  //------�¼���¼ͷ����ʱ�䲻Ϊ0������ʱ��Ϊ0����ʾ�е����¼������¼���¼-------
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
    //      //-----��ȡ�¼���¼����---------------
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
    //      //-----------��������ۼ�ʱ��---------------
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
    //      //Event.ExecFlag.EvFlagBit.PowDn = 1;  //����¼�����
    //      Event.ExecFlag.EvFlag.EvFlagData1 |= EVGEN_MARK_POWDN;
    //       //�ϵ���ж���ʱ�¼�Ϊ3��
    //      EvStatusInter.tPowDn = 3;
    //
    //      EvStatusInter.lStatus[1] |= EVGEN_MARK_POWDN;
    //      EvStatusInter.Status[1] |= EVGEN_MARK_POWDN;
    //  #else
    //       //����¼�����
    //      Event.ExecFlag.EvFlag.EvFlagData0 |= EVGEN_MARK_POWDN;
    //       //�ϵ���ж���ʱ�¼�Ϊ3��
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
** Descriptions:    �¼���¼�ۼ�ʱ��
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnEvent_SumTime(void)
{
    uEventFlag_TypeDef  fEventStart;//�¼�����/���� /��ֹ��־

    u8      i;
    uEventFlag_TypeDef  D;

    if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON) || (Inactive.PubData.InactiveStamp))
    {
        return;
    }

    fEventStart.EvFlag.EvFlagData0 = Event.StartFlag.EvFlag.EvFlagData0;
    fEventStart.EvFlag.EvFlagData1 = Event.StartFlag.EvFlag.EvFlagData1;

    //---�¼�����---
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
** Descriptions:�����¼���¼�ۼ�ʱ�䵽�¼���¼ͷ�ļ�����E2
** input parameters:  item �¼���¼��ţ�=0xFF ȫд��
**                            nphase  ����A��=0 ; B��=1; C��=2; ����ȫд=0xFF
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

//-----�޹�1���޹�2��̴�������--
//-----��ȡ��ǰ��¼���赥��Ӧ���޹�1���޹�2��̴���--------
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
** Descriptions:    ����¼���¼�����ϱ�
** input parameters:  item: �¼���¼���,=0xFFʱ��ʾ�����¼���¼
                               Ch:ͨ���ţ�0xFFʱ��ʾ����ͨ��
** output parameters:   ��
** Returned value:
*********************************************************************************************************/
void fnClr_EvtReportData(u8  item, u8 nphase, u8 Ch)
{
    sReportList_TypeDef tempList;
    u32 clrOAD = 0, addr;
    u8 i, j ;

    fnWDT_Restart();

    if ((item == 0xFF) && (Ch == 0xFF)) //����
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
        //          clrOAD = (nphase + 7)<<8;  //�����¼�,����7,8,9
        //      }
        //       else if(item < FileItemInfoNum_Evt_PtOverNeed)
        //      {
        //          clrOAD = (nphase + 6)<<8;  //�����¼�,����6,7,8,9
        //      }
        //      else
        clrOAD = 0x00000200;   //�Ƿ����¼��̶�����2

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
            for (i = 0; i < EvtRptData.ListZB_A.OADNum; i++) //�����ϱ��б�
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

        //-----�����ϱ��б�---------------
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

        for (i = 0; i < tempList.OADNum; i++) //�ϱ��б�
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
** Descriptions:    �����ϱ�����Ч��
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
** Descriptions:    �����ϱ����������¼�����ʱִ��1��
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
    //      RptOAD = (nphase + 7)<<8;  //�����¼�,����7,8,9
    //  }
    //   else if(item < FileItemInfoNum_Evt_PtOverNeed)
    //  {
    //      RptOAD = (nphase + 6)<<8;  //�����¼�,����6,7,8,9
    //  }
    #else
    //   if(item == FileItemInfoNum_Evt_OverCur)
    //  {
    //      RptOAD = (0 + 7)<<8;  //�����¼�,����7,8,9
    //  }
    #endif
    //  else

    RptOAD = 0x00000200;   //�Ƿ����¼��̶�����2

    for (i = 0; i < FileItemInfoNum_Evt_Max; i++)
    {
        if (Event_Item[i].Item == item)
        {
            RptOAD |= (u32)(Event_Item[i].OI << 16);
            break;
        }
    }

    if (i == FileItemInfoNum_Evt_Max) //�Ҳ����¼���¼OI
    {
        return;
    }

    Offset = item / 8;
    i = item % 8;

    if (((EvtRptData.Para.RptMode[Offset] >> i) & 0x01) == ATIVE_REPORT) //�ϱ���ʽΪ�����ϱ�
    {
        addr = FileItemInfoOffAddr_EvtReport_end;
        if (mode == EVTSTART) //�¼�����
        {
            if (((EvtRptData.Para.RptFlagHappen[Offset] >> i) & 0x01) == 0x01) //�ϱ���ʶΪ�����ϱ�
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
            if (((EvtRptData.Para.RptFlagEnd[Offset] >> i) & 0x01) == 0x01) //�ϱ���ʶΪ�����ϱ�
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
                if (RptOAD == EvtRptData.ListZB_A.OAD[k]) //�б��Ѳ����������ظ���¼
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
                    EvtRptData.ReportCnt = 3; //�����ϱ�3��
                    EvtRptData.tReportDely = 0; //
                    fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_PowerUpTime, &EvtRptData.PowerUpTime, 1);  //PowerUpTime�����㣬�ϵ���ж��Ƿ���Ҫ�ϱ�
                }
                else if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWDN) && (EvtRptData.PowerUpTime > 59))
                {
                    EvtRptData.RptType = RPTEVT_POWNUP;
                    EvtRptData.ReportCnt = 3; //�����ϱ�3��
                    EvtRptData.tReportDely = 0; //
                    EvtRptData.PowerUpTime = 0;
                    fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_PowerUpTime, &EvtRptData.PowerUpTime, 1);
                }
                else
                {
                    EvtRptData.RptType = 0;
                    EvtRptData.ReportCnt = 0; //���ϱ�
                    EvtRptData.tReportDely = 0; //
                    EvtRptData.PowerUpTime = 0;
                    fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_PowerUpTime, &EvtRptData.PowerUpTime, 1);
                }
            }
            else
            {
                EvtRptData.RptType = RPTEVT_OTHER;
                EvtRptData.ReportCnt = 3; //�����ϱ�3��
                EvtRptData.tReportDely = 0; //
            }
        }
    }

    //-------------------------
    if (((EvtRptData.Para.RptMode[Offset] >> i) & 0x01) == FOLLOW_REPORT) //�ϱ���ʽΪ�����ϱ�
    {
        addr = FileItemInfoOffAddr_EvtReport_end;

        if (mode == EVTSTART) //�¼�����
        {
            if (((EvtRptData.Para.RptFlagHappen[Offset] >> i) & 0x01) == 0x01) //�ϱ���ʶΪ�����ϱ�
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
                            if (RptOAD == tempList.OAD[k]) //�б��Ѳ����������ظ���¼
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
                            if (RptOAD == tempList.OAD[k]) //�б��Ѳ����������ظ���¼
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
                            if (RptOAD == tempList.OAD[k]) //�б��Ѳ����������ظ���¼
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
            if (((EvtRptData.Para.RptFlagEnd[Offset] >> i) & 0x01) == 0x01) //�ϱ���ʶΪ�����ϱ�
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
                            if (RptOAD == tempList.OAD[k]) //�б��Ѳ����������ظ���¼
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
                            if (RptOAD == tempList.OAD[k]) //�б��Ѳ����������ظ���¼
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
                            if (RptOAD == tempList.OAD[k]) //�б��Ѳ����������ظ���¼
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
** Descriptions:    �����ϱ�״̬�ָ���
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
                if ((EvtRptData.Status.RptStuZBBack & status) != status) //֮ǰδ�������ϱ�
                {
                    if (EvtRptData.Para.RptStatusAllow == 0) //״̬��Ϊ�����ϱ�
                    {
                        EvtRptData.ReportCnt = 3; //�����ϱ�3��
                        EvtRptData.tReportDely = 0;  //�����ϱ����10��
                    }

                    EvtRptData.Status.RptStuZB |= status;
                    EvtRptData.Status.RptStuZBBack |= status;
                    fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatusZB, (u8 *)&EvtRptData.Status.RptStuZB, 8);
                }
            }
            else if (EvtRptData.Para.RptChannel[i] == 1)
            {
                if ((EvtRptData.Status.RptStu485Back & status) != status) //֮ǰδ�������ϱ�
                {
                    EvtRptData.Status.RptStu485 |= status;
                    EvtRptData.Status.RptStu485Back |= status;
                    fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatus485, (u8 *)&EvtRptData.Status.RptStu485, 8);
                }
            }
            else if (EvtRptData.Para.RptChannel[i] == 2)
            {
                if ((EvtRptData.Status.RptStu4852Back & status) != status) //֮ǰδ�������ϱ�
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
** Descriptions:    �����ϱ�״̬������(�����¼����������¼��ϱ��Ѷ�ȡʱִ������)
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnClr_RptStatus(u32 status)
{
    if ((EvtRptData.Status.RptStuZB & status) != status) //�¼��ϱ��ѱ�����
    {
        EvtRptData.Status.RptStuZB &= ~status;
        EvtRptData.Status.RptStuZBBack &= ~status;
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatusZB, (u8 *)&EvtRptData.Status.RptStuZB, 8);
    }

    if ((EvtRptData.Status.RptStu485 & status) != status) //�¼��ϱ��ѱ�����
    {
        EvtRptData.Status.RptStu485 &= ~status;
        EvtRptData.Status.RptStu485Back &= ~status;
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatus485, (u8 *)&EvtRptData.Status.RptStu485, 8);
    }

    if ((EvtRptData.Status.RptStu4852 & status) != status) //�¼��ϱ��ѱ�����
    {
        EvtRptData.Status.RptStu4852 &= ~status;
        EvtRptData.Status.RptStu4852Back &= ~status;
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatus4852, (u8 *)&EvtRptData.Status.RptStu4852, 8);
    }
}

/*********************************************************************************************************
** Function name:   fnSavePowerOnEvtStop
** Descriptions:    �ϵ�����´���ʧѹ��ʧ�������࣬��ѹ��ƽ���δ����ʱ��ʱ��
**                       ��������
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

    Std_Memcpy((u8 *)&headData.EventEndTime, (u8 *)&PowDn_Datetimes, sizeof(sDate_time_s_TypeDef));     //ˢ��ϵͳʱ��RAM
    headData.EventTime = Event.EvtSumTime[3 * item + nphase];

    //-------���ݹ����������Ա��ȡ����-----------------
    //-----��ȡ�����������Ա�-������ABC��--------
    len = FileItemInfo_EvtCtxlist[item].Len;
    OffAddr = FileItemInfo_EvtCtxlist[item].OffAddr;
    fnFile_Read(FileId_EvtCtxlist, OffAddr, DataBuf, len);

    listOADSumNum = *DataBuf++;

    Std_Memcpy((u8 *)&recordlen, DataBuf, 2);
    DataBuf += 2;

    //-------�����������Ա�Ϸ����ж�------------------
    if ((recordlen > MAX_RCDLEN) || (listOADSumNum > 100)) //�ݴ���������100��OAD
    {
        fnBufTemp_Free(DataBuf);
        fnBufTemp_Free(EvtData);
        return;
    }

    //--class24�洢�ռ����: 10��A�� + 10��B�� + 10��C��-----------------
    maxcnt_u16 = (u16)MAX_EVRECORD_TABLE[item];    //��ȡ����¼��
    if (headData.EventSumCnt % maxcnt_u16)
    {
        OffAddr = ((headData.EventSumCnt % maxcnt_u16) - 1) * (u32)recordlen;
    }
    else
    {
        OffAddr = (maxcnt_u16 - 1) * (u32)recordlen;
    }

    OffAddr += FileItemInfo_EvtRecord[item].OffAddr + (u32)(nphase * recordlen * maxcnt_u16);

    //--------��ȡ�¼�����ǰ����------------------------
    fnFile_Read(FileId_EvtRecord, OffAddr, EvtData, recordlen);
    Std_Memcpy(EvtData + 11, (u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef));

    for (j = 0; j < listOADSumNum; j++)
    {
        Std_Memcpy(&tmplist, DataBuf, sizeof(sContextList_TypeDef));
        DataBuf += sizeof(sContextList_TypeDef);

        pOad = (OAD_Analyse_TypeDef *)&tmplist.OAD;
        //---------�����¼�����������------------------------
        if ((pOad->AtrFeature == EVT_END_BEFORE) || (pOad->AtrFeature == EVT_END_AFTER))
        {
            tmplist.OAD = (tmplist.OAD & 0xFFFF1FFF);
            tmplist.len = fnGet_OADStoreData(tmplist.OAD, EvtData + tmplist.OffPos);
        }
    }

    //----------д�¼���¼----------------
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
** Descriptions:    �ϵ�����´���ʧѹ��ʧ�������࣬��ѹ��ƽ���δ����ʱ��ʱ��
**                       ��������
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
        for (j = 0; j < nPhs; j++) //A/B/C����
        {
            len = 2 * sizeof(sDate_time_s_TypeDef);
            OffAddr = FileItemInfo_EvtRcdHead[i].OffAddr + j * sizeof(sEvtRcdHead_TypeDef) + 4;

            fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventStartTime, (u32)len);  //��ȡ�¼���¼ͷ�Ŀ�ʼʱ�䡢����ʱ��

            //----�¼���¼����ʱ�䲻Ϊ0������ʱ��Ϊ0-------
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

            fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventStartTime, (u32)len);  //��ȡ�¼���¼ͷ�Ŀ�ʼʱ�䡢����ʱ��

            //----�¼���¼����ʱ�䲻Ϊ0������ʱ��Ϊ0-------
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

        fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventStartTime, (u32)len);  //��ȡ�¼���¼ͷ�Ŀ�ʼʱ�䡢����ʱ��

        //----�¼���¼����ʱ�䲻Ϊ0������ʱ��Ϊ0-------
        if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
            (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
        {
            fnWrite_EvtStopRecord(item, 0);
        }
    }
    fnWDT_Restart();

    //--------���ų������¼���¼---------------------
    len = 2 * sizeof(sDate_time_s_TypeDef);
    OffAddr = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_MagnetDisturb].OffAddr + 4;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventStartTime, len);

    //----�¼���¼����ʱ�䲻Ϊ0������ʱ��Ϊ0-------
    if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        fnSysDateTimes(&SysDatetimes);  //ʱ��ָ�
        Key.Release &= ~KEY_VAL_STROMAN;
        fnEvent_Operation(FileItemInfoNum_Evt_MagnetDisturb, EVTEND, NULL);
        Inactive.InactiveFlag.EventFlag &= ~((u32)1 << EVENT_STYLE_MagnetDisturb);
    }
    #else
    len = 2 * sizeof(sDate_time_s_TypeDef);
    //  item = FileItemInfoNum_Evt_OverCur;
    OffAddr = FileItemInfo_EvtRcdHead[item].OffAddr + 4;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventStartTime, (u32)len);  //��ȡ�¼���¼ͷ�Ŀ�ʼʱ�䡢����ʱ��

    //----�¼���¼����ʱ�䲻Ϊ0������ʱ��Ϊ0-------
    if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        fnWrite_EvtStopRecord(item, 0);
    }

    #endif
    //--------����Դ�쳣�¼���¼---------------------
    len = 2 * sizeof(sDate_time_s_TypeDef);
    //  OffAddr = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_PowerErr].OffAddr + 4;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData.EventStartTime, len);

    //----�¼���¼����ʱ�䲻Ϊ0������ʱ��Ϊ0-ͣ���е�Դ�쳣�¼���¼------
    if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        Std_Memcpy((u8 *)&SysDatetimes, (u8 *)&headData.EventStartTime, sizeof(sDate_time_s_TypeDef));      //ˢ��ϵͳʱ��RAM
        //      fnEvent_Operation(FileItemInfoNum_Evt_PowerErr ,EVTSTART , NULL);
        fnWDT_Restart();
        fnSysDateTimes(&SysDatetimes);  //ʱ��ָ�
        //      fnEvent_Operation(FileItemInfoNum_Evt_PowerErr ,EVTEND, NULL);
    }
    fnWDT_Restart();

    fnSysDateTimes(&SysDatetimes);  //ʱ��ָ�
    #endif
}

/*********************************************************************************************************
** Function name:   fnSaveQLossVolEvt
** Descriptions:    �ϵ籣��ȫʧѹ�¼���¼
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

    //-------��ȡ��1��ȫʧѹ�¼���¼ͷ--------------
    OffAddr = FileItemInfo_EvtRcdHead[FileItemInfoNum_Evt_QLossVol].OffAddr;

    fnFile_Read(FileId_EvtRcdHead, OffAddr, (u8 *)&headData, sizeof(sEvtRcdHead_TypeDef));

    //-----��ȡ�¼���¼����---------------
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
    //��ȡflash�����һ���¼���������(4byte)������ʱ��(7byte),����ʱ��(7byte)
    fnFile_Read(FileId_EvtRecord, OffAddr, (u8 *)&headData_Record, 18);

    if ((headData.EventSumCnt > headData_Record.EventSumCnt) &&
        (fnDFCompData((u8 *)&headData.EventStartTime, (u8 *)&headData_Record.EventStartTime, sizeof(sDate_time_s_TypeDef)) != 0))
    {
        //-------��ȫʧѹ�����¼���¼-----------
        Event.StartFlag.EvFlag.EvFlagData0 = 0;
        Event.StartFlag.EvFlag.EvFlagData1 = 0;

        Event.StartFlag.EvFlagBit.QLossVol = 1;
        Std_Memcpy((u8 *)&SysDatetimes, (u8 *)&headData.EventStartTime, sizeof(sDate_time_s_TypeDef));
        fnFile_Read(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_Irms, &MeasureRms.PubData.I[0], FileItemInfoLen_PowDn_Irms);
        fnEvent_Exec();
        Std_Memset((u8 *)&MeasureRms.PubData.I[0], 0x00, FileItemInfoLen_PowDn_Irms);

        //-----------����ȫʧѹ�ۼ�ʱ��---------------
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

    //------����ʱ��Ϊ0������ʱ�䲻Ϊ0����ǰ����ȫʧѹ״̬---------------
    if ((fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, sizeof(sDate_time_s_TypeDef)) == TRUE))
    {
        // ��״̬��Ϊ0
        EvStatusInter.lStatus[1] |= EVGEN_MARK_QLOSSVOL;
        EvStatusInter.Status[1] |= EVGEN_MARK_QLOSSVOL;

        Event.ExecFlag.EvFlag.EvFlagData1 |= EVGEN_MARK_QLOSSVOL;
        EvStatusInter.tQLossVol = 5;  //�ϵ��ȫʧѹ�ж���ʱ�¼�Ϊ3��
    }
}

//-----------------��ѹ�ϸ���------------------------

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

//--------UElig��ѹ�ϸ����жϺ���-----------------------
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
            //A���ѹ���ʱ��
            Stat.PubData.UElig_Day[i].tInspectU++;
            Stat.PubData.UElig_Month[i].tInspectU++;
        }
        //---�����ѹ������ʱ��---
        if ((MeasureRms.PubData.U[i] > Stat.PriPara.UUp) && (MeasureRms.PubData.U[i] < Stat.PriPara.UCheckUp))
        {
            //A��
            Stat.PubData.UElig_Day[i].tOverUpU++;
            Stat.PubData.UElig_Month[i].tOverUpU++;
        }
        //---�����ѹ������ʱ��
        if ((MeasureRms.PubData.U[i] < Stat.PriPara.UDn) && (MeasureRms.PubData.U[i] > Stat.PriPara.UCheckUp))
        {
            //A��
            Stat.PubData.UElig_Day[i].tOverUpU++;
            Stat.PubData.UElig_Month[i].tOverUpU++;
        }

        if (Stat.PubData.UElig_Day[i].tInspectU)
        {
            Tmp1 = Stat.PubData.UElig_Day[i].tInspectU;         //�����ѹ���ʱ��
            Tmp2 = Stat.PubData.UElig_Day[i].tOverUpU;          //���೬����ʱ��
            Tmp3 = Stat.PubData.UElig_Day[i].tOverDnU;      //���೬����ʱ��
            Stat.PubData.UElig_Day[i].OverRateU = (Tmp2 + Tmp3) * 10000 / Tmp1;           //�����ѹ������
            Stat.PubData.UElig_Day[i].EligRateU = (Tmp1 - Tmp2 - Tmp3) * 10000 / Tmp1; //�����ѹ�ϸ���
        }

        if (Stat.PubData.UElig_Month[i].tInspectU)
        {
            Tmp1 = Stat.PubData.UElig_Month[i].tInspectU;       //�����ѹ���ʱ��
            Tmp2 = Stat.PubData.UElig_Month[i].tOverUpU;            //���೬����ʱ��
            Tmp3 = Stat.PubData.UElig_Month[i].tOverDnU;        //���೬����ʱ��
            Stat.PubData.UElig_Month[i].OverRateU = (Tmp2 + Tmp3) * 10000 / Tmp1;           //�����ѹ������
            Stat.PubData.UElig_Month[i].EligRateU = (Tmp1 - Tmp2 - Tmp3) * 10000 / Tmp1;   //�����ѹ�ϸ���
        }
    }
    //--------ÿСʱ��һ��E2---------
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
    if (Event.PriData.Prg_Step)  //�б���¼�����ʱ����̽����¼�
    {
        //          fnEvent_Operation(FileItemInfoNum_Evt_Prg , EVTEND, NULL );
    }
}
