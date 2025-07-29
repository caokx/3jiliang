
#ifndef _EVENT_H
#define _EVENT_H

#ifdef   _EVENT_GLOBALS
#define  EVENT_EXT
#else
#define  EVENT_EXT  extern
#endif

typedef enum
{
    EVENT_STYLE_POWDN       = 0,    //�����¼
    EVENT_STYLE_PRG         = 1,    //��̼�¼
    EVENT_STYLE_CLR         = 2,    //��������¼
    EVENT_STYLE_NEEDCLR     = 3,    //���������¼
    EVENT_STYLE_EVENTCLR    = 4,    //�¼������¼
    EVENT_STYLE_SETCLOCK    = 5,    //Уʱ��¼(�������㲥Уʱ)
    EVENT_STYLE_PRGPOTTABLE = 6,    //ʱ�α��̼�¼
    EVENT_STYLE_PRGTIMEZONE = 7,    //ʱ�����̼�¼
    EVENT_STYLE_PRGWEEKEND  = 8,    //�����ձ�̼�¼
    EVENT_STYLE_PRGHOLIDAY  = 9,    //�ڼ��ձ�̼�¼
    EVENT_STYLE_PRGP        = 10,   //�й���Ϸ�ʽ��̼�¼
    EVENT_STYLE_PRGQ1       = 11,   //�޹���Ϸ�ʽ1��̼�¼
    EVENT_STYLE_PRGQ2       = 12,   //�޹���Ϸ�ʽ2��̼�¼
    EVENT_STYLE_PRGRMDAY    = 13,   //�����ձ�̼�¼
    EVENT_STYLE_SHELL       = 14,   //����Ǽ�¼�ļ�
    EVENT_STYLE_JUNBOX      = 15,   //����ť�м�¼
    EVENT_STYLE_GATEOFF     = 16,   //��բ��¼
    EVENT_STYLE_GATEON      = 17,   //��բ��¼
    EVENT_STYLE_BUYEG       = 18,   //�����ܼ�¼
    EVENT_STYLE_BUYMONEY    = 19,   //������¼
    EVENT_STYLE_PrgRatePrice = 20,  //���ʱ��̼�¼
    EVENT_STYLE_PrgLadderPrice = 21, //���ݱ��̼�¼
    EVENT_STYLE_PrgSetPsw   = 22,   //��Կ���ü�¼
    EVENT_STYLE_InsertCardErr = 23, //����������¼
    EVENT_STYLE_ReturnMoney  = 24,  //�˷Ѽ�¼
    EVENT_STYLE_MagnetDisturb =  25,   //�㶨�ų����ż�¼
    EVENT_STYLE_RelayStatErr = 26,  //���ɿ���������¼
    EVENT_STYLE_PowerErr    = 27,   //��Դ�쳣��¼
    EVENT_STYLE_MngPlug     = 28,   //����ģ���μ�¼
    EVENT_STYLE_MAX         = 29,   //����¼���¼

    EVENT_OPERATION_START   = 0,
    EVENT_OPERATION_RUN     = 1,
    EVENT_OPERATION_END     = 2
} eDl645Event_Operation_TypeDef;

typedef enum
{
    EVTSTART = 1,
    EVTEND   = 2,
    EVTRUN   = 3
} eEvent_Status_TypeDef;

typedef enum
{
    EVT_HAP_BEFORE = 1,
    EVT_HAP_AFTER  = 2,
    EVT_END_BEFORE = 3,
    EVT_END_AFTER  = 4,
} eEvtRcd_Feature_TypeDef;

typedef enum
{
    Mng_IsRcvEsam = (1 << 0),           // �Ƿ����յ�������ģ��ESAM
    Mng_ComRcvEsam = (1 << 1),          // ͨѶ�յ�����ģ��ESAM
    Mng_SynEsam = (1 << 2),             // ͬ������ESAM��״̬
    Mng_ReplaceEsam = (1 << 3),         // ʹ��ȫFF�滻

    EvtSta_MngPlug = (1 << 0),          // ����ģ����״̬
    EvtSta_OpenCover = (1 << 1),        // �����״̬
    EvtSta_OpenTail = (1 << 2),         // ���˸�״̬
} eEvtMngPlugStaTypedef;

#define   EVENT_CLR_WORD   0x11223344     //�¼�����
#define   DEMAND_CLR_WORD  0x55667788   //��������
#define   METER_CLR_WORD  0xAABBCCDD      //�������
#define   FACTORY_CLR_WORD   0x5A5B5C5D  //ͨѶ��ʼ��,������ʼ��,������RTC�����Ӳ��¡�ͨѶ��ַ��ASCII �벻��ʼ������������ָ�Ĭ��ֵ
#define   FIRST_CLR_WORD   0xA3A5B7B9    //ͨѶ��ʼ��,�״γ�ʼ��,���в������ָ�Ĭ��ֵ,����������
//======================================
#define   ATIVE_REPORT    0
#define   FOLLOW_REPORT   1

#define   EvtMngDelay           6
#define   EvtMngPlugPinTmr      100 // 100 * 5ms = 0.5s
#define   EvtMngPlugNewEsamOffset       52          // ����ģ�����¼���ESAM���к�ƫ�Ƶ�ַ

#if 0 //(nPhs==ThreePhs)
typedef struct
{
    u32 EvFlagData0;
    u32 EvFlagData1;
} sEvFlag_TypeDef ;

typedef union
{
    sEvFlag_TypeDef EvFlag ;

    struct sEvFlagBit_TypeDef
    {
        u32 LossVola : 1;       //0
        u32 LossVolb : 1;       //1
        u32 LossVolc : 1;           //2
        //2
        u32 LackVola : 1;       //3
        u32 LackVolb : 1;       //4
        u32 LackVolc : 1;           //5

        u32 OverVola : 1;       //6
        u32 OverVolb : 1;       //7
        u32 OverVolc : 1;       //8

        u32 LossPhaa : 1;       //9
        u32 LossPhab : 1;       //10
        u32 LossPhac : 1;       //11

        u32 LossCura : 1;       //12
        u32 LossCurb : 1;       //13
        u32 LossCurc : 1;       //14

        u32 OverCura : 1;       //15
        u32 OverCurb : 1;       //16
        u32 OverCurc : 1;       //17

        u32 BreakCura : 1;      //18
        u32 BreakCurb : 1;      //19
        u32 BreakCurc : 1;      //20

        u32 InSwima : 1;        //21
        u32 InSwimb : 1;        //22
        u32 InSwimc : 1;        //23

        u32 OverPwa : 1;        //24
        u32 OverPwb : 1;    //25
        u32 OverPwc : 1;        //26

        u32 OverQd1QNeed : 1;   //27
        u32 OverQd2QNeed : 1;   //28
        u32 OverQd3QNeed : 1;   //29
        u32 OverQd4QNeed : 1;   //30

        u32 OverPf :   1;               //31
        u32 OverPfA : 1;                //0
        u32 OverPfB : 1;                //1
        u32 OverPfC : 1;                //2

        u32 OverPtPNeed : 1;        //3
        u32 OverNtPNeed : 1;    //4
        u32 QLossVol : 1;           //5
        u32 LossAux : 1;                //6
        u32 InPhaVol : 1;               //7
        u32 InPhaCur : 1;           //8

        u32 PowDn   : 1;                //9

        u32 UnblVol : 1;                //10
        u32 UnblCur : 1;                //11
        u32 OverUnblCur : 1;        //12
        u32 NLineErr : 1;       //13

        u32 MeasureErr   : 1;  //14
        //  u32 PowerErr     :1;   //15
        u32 Reserve1 : 17;            //
    } EvFlagBit;
} uEventFlag_TypeDef;
#else
typedef struct
{
    u32 EvFlagData0;
    u32 EvFlagData1;
} sEvFlag_TypeDef ;

typedef union
{
    sEvFlag_TypeDef EvFlag ;

    struct sEvFlagBit_TypeDef
    {
        u32 MngPlug : 1;        //0
        u32 PowDn   : 1;        //--1--
        u32 OpenCover    : 1;  //--2---
        u32 OpenTail : 1;       //-3--
        u32 Reserve1 : 28;            //
    } EvFlagBit;
} uEventFlag_TypeDef;

#endif

typedef struct
{
    uEventFlag_TypeDef  StartFlag;
    uEventFlag_TypeDef  ExecFlag;

    struct sEventPrivateData_TypeDef
    {
        u8 Step;
        u8 ExecStep;    //�¼�ִ�в��裬ÿ��ִ��һ���¼�
        u32 OpFlag;     //�¼�������־
        u32 Clr_Word;   // ��������־��
        u32 EvClr_Word; // �¼������־��
        u8  Clr_Step;   // �������ֲ�ִ��,��ֹ����ʱͨѶ���쳣
        u8  EvClr_Step; // �¼�������ֲ�ִ��,��ֹ����ʱͨѶ���쳣
        u8  Prg_Step;  //����¼���¼����0x00=��̽���,0x01=��̿�ʼ
        u8  OpDI[4];    //�����¼�����
    } PriData;
    u32    EvtSumTime[MAX_EVENTTYPE];    //�¼���¼�ۼ�ʱ�䣬����˳���uEventFlag_TypeDef����һ��
} sEvent_TypeDef;

//=============================

typedef struct
{
    u32 FileId;     //�ļ���
    u32 nPha;       //��λ 0�ܡ�1A�ࡢ2B�ࡢ3C��
} sDl645EvConst_TypeDef;

typedef struct
{
    sEvtRptPara_TypeDef  Para;

    sEvtRptStatus_TypeDef  Status; // �����ϱ�״̬��

    sReportList_TypeDef  ListZB_A;  //�����ϱ��б�

    u32  RecOADZB;   //��������ϱ�OAD
    u32  RecOAD485;  //��������ϱ�OAD
    u32  RecOAD4852; //��������ϱ�OAD

    u8  ReportCnt;  //�����ϱ�����
    u8  tReportDely;  //�����ϱ�������ʱ(��)
    u8  RptType;  //�����ϱ�����:�ϵ������¼���¼�ϱ�(3320),��������ϱ���3011��RN_MAC;�����ϱ�3011,������
    u8  PowerUpTime;
} sEvtRptData_TypeDef;

typedef struct
{
    sVolYieldPara_TypeDef   PriPara;
    sStatFile_TypeDef       PubData;
} sStat_TypeDef;

extern const u8 MAX_EVRECORD_TABLE[];
extern const u16 MAX_EVTFLASHCNT_TABLE[];
//=============================
extern void fnEvent_Init(void);
extern void fnEvent_Clr_Status(u8 item, u8  nphase);
extern void fnEvent_GetStatus(u32 Status0, u32 Status1);
extern void fnEvent_nphsEvt_Exec(void);
extern void fnEvent_Exec(void);
extern void fnDl645Event_Operation(u8 Style, u8 Way, u8 *OpCode, u8 *Buff);
extern void fnEvent_OpExec(void);
extern void fnOpenCoverTailEvent(void);
extern void fnEvent_Operation(u8 item, u8 mode, u8 *Buff);

extern void fnEvent_EvtClr(void);

extern const    sCList6_TypeDef EvtPrg_StdRecList;
extern const    u8  EvtPrgStdRcdList_DataType[];

extern const    sCList7_TypeDef EvtPrgTable_StdRecList;
extern const    u8  EvtPrgTableStdRcdList_DataType[];

extern const    sCList7_TypeDef EvtHldy_StdRecList;
extern const u8 EvtHldyStdRcdList_DataType[];

extern const    sCList6_TypeDef EvtClr_StdRecList;
extern const    u8  EvtClrStdRcdList_DataType[];

extern const    sCList4_TypeDef EvtC24_StdRecList;
extern const    sCList5_TypeDef EvtC7_StdRecList;
extern const sRecord_ParaDefault_TypeDef EvtStdlist[];
extern const u8 EvtStdRcdList_DataType[];

extern const    sCList5_TypeDef EvtPrgQ_StdRecList;
extern const    u8  EvtPrgQStdRcdList_DataType[];

extern void fnEvent_SumTime(void);
extern void fnEvent_WriteSumTime(u8 item, u8  nphase);
extern void fnEvent_Clr_BroadstaSta(void);
extern void fnEvent_Clr_PrgQSta(void);
extern void fnEvent_Clr_PowDnDatetimes(void);

extern void fnEvent_Report(u8 item, u8 nphase, u8 mode);
extern void fnCheck_ReportPara(void);
extern void fnClr_EvtReportData(u8  item, u8 nphase, u8 Ch);
extern void fnClr_RptStatus(u32 status);
extern void fnUpdate_RptStatus(u32 status);

extern void fnWrite_PownDownEvtToE2(void);
extern void fnWrite_PownDownEvtToFlash(void);
extern void fnSavePowerOnEvtStop(void);
extern void fnSaveQLossVolEvt(void);
extern void fnGetCurrTime(sDate_time_s_TypeDef * ptime);

extern void fnStat_Init(void);
extern void fnUEligStat_Exec(void);
extern void fnEvtPrg_End(void);

extern void fnEvtMngPlug_Init(void);
extern void fnEvtMngPlug_PwdnSave(void);
extern void fnEvtCoverTail_PwDn(void);
extern void fnEvtCoverTail_PowerOn(void);
extern void fnEvtVoltLoss_PowerDwn(void);

#endif // _EVENT_H
