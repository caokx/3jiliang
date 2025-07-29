
#ifndef _BKGRD_H
#define _BKGRD_H

#ifdef   _BKGRD_GLOBALS
#define  BKGRD_EXT
#else
#define  BKGRD_EXT  extern
#endif

#define     BKGRD_FCHANGE_SECOND        ( (u32)1 << 0)
#define     BKGRD_FCHANGE_MINUTE        ( (u32)1 << 1)
#define     BKGRD_FCHANGE_HOUR          ( (u32)1 << 2)
#define     BKGRD_FCHANGE_DAY           ( (u32)1 << 3)
#define     BKGRD_FCHANGE_MONTH         ( (u32)1 << 4)
#define     BKGRD_FCHANGE_RMDAY1        ( (u32)1 << 5)
#define     BKGRD_FCHANGE_RMDAY2        ( (u32)1 << 6)
#define     BKGRD_FCHANGE_RMDAY3        ( (u32)1 << 7)

#define     BKGRD_FCHANGE_WINKFRZ       ( (u32)1 << 8)
#define     BKGRD_FCHANGE_MINFRZ        ( (u32)1 << 9)
#define     BKGRD_FCHANGE_HOURFRZ       ( (u32)1 << 10)
#define     BKGRD_FCHANGE_DAYFRZ        ( (u32)1 << 11)
#define     BKGRD_FCHANGE_MONTHFRZ      ( (u32)1 << 12)
#define     BKGRD_FCHANGE_TZONEFRZSW    ( (u32)1 << 13)
#define     BKGRD_FCHANGE_POTFRZSW          ( (u32)1 << 14)
#define     BKGRD_FCHANGE_RATEPRICESW   ( (u32)1 << 15)
#define     BKGRD_FCHANGE_LADDERESW     ( (u32)1 << 16)

#define     BKGRD_FCHANGE_FL            ( (u32)1 << 17)
#define     BKGRD_FCHANGE_INIT          ( (u32)1 << 18)
#define     BKGRD_FCHANGE_RMYEAR1  ( (u32)1 << 19)
#define     BKGRD_FCHANGE_RMYEAR2  ( (u32)1 << 20)
#define     BKGRD_FCHANGE_RMYEAR3  ( (u32)1 << 21)
#define     BKGRD_FCHANGE_RMYEAR4  ( (u32)1 << 22)
#define     BKGRD_FCHANGE_CURVE         ( (u32)1 << 23)
#define     BKGRD_FCHANGE_POT       ( (u32)1 << 24)

typedef struct
{
    u8  Second : 1;
    u8  Minute : 1;
    u8 Hour : 1;
    u8 Day : 1;
    u8 Month : 1;
    u8 RmDay1 : 1;
    u8 RmDay2 : 1;
    u8 RmDay3 : 1;
    u8 WinkFrz : 1;
    u8 MinFrz : 1;
    u8 HourFrz : 1;
    u8 DayFrz : 1;
    u8 MonthFrz : 1;
    u8 TZoneFrz : 1;
    u8 POTFrz : 1;
    u8 RatePriceSw : 1;
    u8 LaddereSw : 1;
    u8 FL : 1;
    u8 INIT : 1;
    u8  RmYear1 : 1;
    u8  RmYear2 : 1;
    u8  RmYear3 : 1;
    u8  RmYear4 : 1;
    u8 Curve : 1;
    u8 XiugaiClock: 1;
    u8  t500ms: 1;
    u8  POT : 1;
    u8 DemandCycle : 1;
} sDl645BkgrdFlagBit_TypeDef;       //��̨״̬��־��

typedef union
{
    u32                         Flag;
    sDl645BkgrdFlagBit_TypeDef  FlagBit;
} sBkgrdFlag_TypeDef;

typedef enum
{
    BKGRD_EVENTERR_OK               = 0x00,
    BKGRD_EVENTERR_CONTROL          = 0x01,
    BKGRD_EVENTERR_ESAM             = 0x02,
    BKGRD_EVENTERR_INTERCARD        = 0x03,
    BKGRD_EVENTERR_CLOCKBATLOW      = 0x04,
    BKGRD_EVENTERR_INTERPROGRAM     = 0x05,
    BKGRD_EVENTERR_INTERMEMORY      = 0x06,
    BKGRD_EVENTERR_CLOCK            = 0x07,
    BKGRD_EVENTERR_OVERPWA          = 0x51,
    BKGRD_EVENTERR_OVERUNBLCUR      = 0x52,
    BKGRD_EVENTERR_OVERVOL          = 0x53,
    BKGRD_EVENTERR_OVERPF           = 0x54,
    BKGRD_EVENTERR_OVERPNEED        = 0x55,
    BKGRD_EVENTERR_INSWIM           = 0x56
} eBkgrd_ERR_TypeDef;

//----------------------------
typedef enum
{
    CLOCK_STA_OK                    = 0x00,   //00--��ʱ�ӹ���
    CLOCK_STA_SETOVER               = 0x01,  //01--���Ĺ㲥Уʱ��Χ�������Уʱƫ��
    CLOCK_STA_ERR                   = 0x10, //10--ʱ�ӷ������ˡ���ʽ���ҡ��ϵ�ʱ��ʱ��С�ڵ���ʱ�����ڵ���ʱ��1000��
    CLOCK_STA_SETOVER_ERR   = 0x11    //11--���Ĺ㲥Уʱ��Χ�������Уʱƫ���ʱ�ӷ������ˡ���ʽ���ҡ��ϵ�ʱ��ʱ��С�ڵ���ʱ�����ڵ���ʱ��1000��
} eClock_ERRSTA_TypeDef;

//------------------------------------------------------------
typedef struct
{
    u16 SwCtlMode : 1;      //���ÿ��ؿ��Ʒ�ʽ 0��ƽ��1����(����)
    u16 NeedMode : 1;       //�������㷽ʽ 0���1����
    u16 ClockBat : 1;       //ʱ�ӵ�� 0������1Ƿѹ
    u16 BackupBat : 1;      //ͣ�糭���� 0������1Ƿѹ
    u16 PPwDir : 1;         //�й����ʷ��� 0����1����
    u16 QPwDir : 1;         //�޹����ʷ��� 0����1����
    u16 OutMulFun: 2;       //�๦�����00������źţ�01���ʱ��Ͷ���źţ�10������������ź�
    u16 ControlErr: 1;      //���ƻ�·����
    u16 EsamErr : 1;        //ESAM����
    u16 Reserve2 : 2;
    u16 ProgramErr: 1;      //�ڲ��������
    u16 MemoryErr: 1;       //�洢������
    u16 Overdraft: 1;       //͸֧״̬
    u16 ClockErr : 1;       //ʱ�Ӵ���
} sMtSta1Bit_TypeDef;   //�������״̬��1

typedef struct
{
    u16 PPwaDir : 1;        //A���й����ʷ��� 0����1����
    u16 PPwbDir : 1;        //B���й����ʷ��� 0����1����
    u16 PPwcDir : 1;        //C���й����ʷ��� 0����1����
    u16 Reserve1 : 1;       //
    u16 QPwaDir : 1;        //A���޹����ʷ��� 0����1����
    u16 QPwbDir : 1;        //B���޹����ʷ��� 0����1����
    u16 QPwcDir : 1;        //C���޹����ʷ��� 0����1����
    u16 Reserve2 : 9;
} sMtSta2Bit_TypeDef;   //�������״̬��2

typedef struct
{
    u16 Reserve1 : 1;           //����
    u16 PowMode : 2;        //���緽ʽ 00����Դ��01������Դ��10��ع���
    u16 PrgEnable : 1;      //���������� 0��ֹ��1����
    u16 GateStatus : 1;     //�̵���״̬ 0ͨ��1��
    u16 Reserve2 : 1;       //����
    u16 GateCmdStatus : 1;  //�̵�������״̬ 0ͨ��1��
    u16 PreGateOff : 1;     //Ԥ��բ����״̬ 0�ޡ�1��

    u16 MtType : 2;         //������� 00��Ԥ���ѱ�01������Ԥ���ѱ�10�����Ԥ���ѱ�
    u16 TrmRemoteValid : 1; //�ն������֤
    u16 TrmSecValid : 1;        //�ն˰�ȫ��֤
    u16 KeepEg : 1;         //����״̬
    u16 RemoteValid : 1;    //�����֤״̬
    u16 LocalOpen : 1;      //���ؿ���
    u16 RemoteOpen : 1;     //Զ�̿���
} sMtSta3Bit_TypeDef;   //�������״̬��3(������)

typedef struct
{
    u16 LossVol : 1;        //ʧѹ 0�ޡ�1��
    u16 LackVol : 1;        //Ƿѹ 0�ޡ�1��
    u16 OverVol : 1;        //��ѹ 0�ޡ�1��
    u16 LossCur : 1;        //ʧ�� 0�ޡ�1��
    u16 OverCur : 1;        //���� 0�ޡ�1��
    u16 OverPw : 1;         //���� 0�ޡ�1��
    u16 InSwim : 1;         //�������� 0�ޡ�1��
    u16 LossPha : 1;        //���� 0�ޡ�1��

    u16 BreakCur : 1;       //���� 0�ޡ�1��
    u16 Reserve1 : 5;
    u16 CTShort : 1;        // CT��·
    u16 CTOpen : 1;         // CT��·
} sMtSta4Bit_TypeDef;   //�������״̬��4(A�������)

typedef struct
{
    u16 InPhaVol : 1;       //��ѹ������ 0�ޡ�1��
    u16 InPhaCur : 1;       //���������� 0�ޡ�1��
    u16 UnblVol : 1;        //��ѹ��ƽ�� 0�ޡ�1��
    u16 UnblCur : 1;        //������ƽ�� 0�ޡ�1��
    u16 LossAux : 1;        //������Դʧ�� 0�ޡ�1��
    u16 PowDn : 1;          //���� 0�ޡ�1��
    u16 OverNeed : 1;       //������ 0�ޡ�1��
    u16 OverPf : 1;         //�ܹ������������� 0�ޡ�1��

    u16 OverUnblCur : 1;    //�������ز�ƽ�� 0�ޡ�1��
    u16 OpenCover : 1;      // �����
    u16 OpenShell : 1;      // ����ť
    u16 Reserve1 : 5;
} sMtSta7Bit_TypeDef;   //�������״̬��7(���������)

//------------------------------------------------------------
typedef struct
{
    u32 KeySta: 1;  //��Կ״̬(0��Կ��1˽Կ)
    u32 EsamErr : 1;        //ESAM����
    u32 Reserve1 : 1;
    u32 ClockBat : 1;       //ʱ�ӵ�� 0������1Ƿѹ
    u32 ProgramErr: 1;      //�ڲ��������
    u32 MemoryErr: 1;       //�洢������
    u32 ClockErr : 2;       //ʱ�ӹ���
    u32 MagnetDisturb: 1;    //�㶨�ų�����
    u32 LossAux: 1;     //������Դʧ�� 0�ޡ�1��
    u32 OpenCover : 1;      // �����
    u32 OpenShell : 1;      // ����ť
    u32 TrmSecValid : 1;    //�ն������֤
    u32 TrmRemoteValid : 1; //�ն˰�ȫ��֤
    u32 BothCoreValid : 1;      //˫о��֤״̬(0ʧЧ��1��Ч)
    u32 RemoteValid : 1;    //��վ��ȫ��֤״̬(0ʧЧ��1��Ч)

    u32 EvtSetClock: 1; //��ͨУʱ
    u32 EvtBroadcastTime: 1; //�㲥Уʱ
    u32 EvtOpenCover : 1;       // �����
    u32 EvtOpenShell : 1;       // ����ť
    u32 EvtControlPullOut: 1;       //����ģ����
    u32 EvtControlUpgrade : 1;      //����ģ������
    u32 EvtMeterClear : 1;      //����ģ������
    u32 Reserve2 : 8;
    u32 EvtMinFreeze : 1;       //���Ӷ���
} sMtSysStaBit_TypeDef; //����ģ��ϵͳ״̬��

typedef struct
{
    u32 PPwDir : 1;     //���й����ʷ��� 0����1����
    u32 PPwaDir : 1;        //A���й����ʷ��� 0����1����
    u32 PPwbDir : 1;        //B���й����ʷ��� 0����1����
    u32 PPwcDir : 1;        //C���й����ʷ��� 0����1����
    u32 QPwDir : 1;     //���޹����ʷ��� 0����1����
    u32 QPwaDir : 1;        //A���޹����ʷ��� 0����1����
    u32 QPwbDir : 1;        //B���޹����ʷ��� 0����1����
    u32 QPwcDir : 1;        //C���޹����ʷ��� 0����1����
    u32 Reserve1 : 1;
    u32 Noplda: 1;          //A��Ǳ��0�������𶯣�1������Ǳ��
    u32 Nopldb: 1;          //B��Ǳ��
    u32 Nopldc: 1;          //C��Ǳ��
    u32 InPhaVol : 1;       //��ѹ������ 0�ޡ�1��
    u32 InPhaCur : 1;       //���������� 0�ޡ�1��
    u32 Reserve2 : 2;
    u32 MeasureType : 2;    //01-���࣬02-�������ߣ�03-��������
    u32 MeasureUn : 2;      //00-57.7V��01-100V��02-220V
    u32 Reserve3 : 12;
} sMeasureSysStaBit_TypeDef;

typedef struct
{
    u8  LowAlarm1 : 1;      // ���ڱ������1
    u8  LowAlarm2 : 1;      // ���ڱ������2
    u8  SurplusMoneyZero : 1;   // ʣ�����Ϊ0
    u8  Overdraft : 1;      // ����͸֧���
    u8  RemoteAlarm : 1;    // Զ�̱���״̬
    u8  RemoteRelay : 1;    // Զ������բ
    u8  RemoteKeepEg : 1;   // Զ�̱���
    u8  GataOffAlarm : 1;   // ���طѿر���բ����
} sMoneyAlarm_TypeDef;

typedef struct
{
    u8  PHAV : 1;   //=1 ʱ��ѹ���Ų���ʾ����ѹС��0.6Un
    u8  PHBV : 1;
    u8  PHCV : 1;
    u8  QLOSSVOL : 1;   //Һ����ȫʧѹ״̬��ʾ
    u8  PHAI : 1;  //=1ʱ�������Ų���ʾ������ֵС��5mA
    u8  PHBI : 1;
    u8  PHCI : 1;
    u8   : 1;
} sValCurStatusFlagBit_TypeDef;     //��̨״̬��־��

typedef union
{
    u8                          Flag;
    sValCurStatusFlagBit_TypeDef    FlagBit;
} sValCurStatusFlag_TypeDef;

typedef struct
{
    union
    {
        u16             Sta;
        sMtSta1Bit_TypeDef  StaBit;
    } MtSta1;
    union
    {
        u16             Sta;
        sMtSta2Bit_TypeDef  StaBit;
    } MtSta2;

    union
    {
        u16             Sta;
        sMtSta3Bit_TypeDef  StaBit;
    } MtSta3;

    union
    {
        u16             Sta;
        sMtSta4Bit_TypeDef  StaBit;
    } MtSta4;

    union
    {
        u16             Sta;
        sMtSta4Bit_TypeDef  StaBit;
    } MtSta5;

    union
    {
        u16             Sta;
        sMtSta4Bit_TypeDef  StaBit;
    } MtSta6;

    union
    {
        u16             Sta;
        sMtSta7Bit_TypeDef  StaBit;
    } MtSta7;
} sMtSta_TypeDef;       //�������״̬��1

typedef union
{
    u32             SysSta;
    sMtSysStaBit_TypeDef    SysStaBit;
} sMtSysSta_TypeDef;        //����ģ��ϵͳ״̬��

typedef union
{
    u32             SysSta;
    sMeasureSysStaBit_TypeDef   SysStaBit;
} sMeasureSysSta_TypeDef;       //����ϵͳ״̬��

//=============================================
typedef struct
{
    struct sPubData_TypeDef
    {
        u8      Active;         //0=��������  1=����  2=�ϵ�ָ�����
        u8      PownUpingDelay; //ϵͳ�ϵ���Ҫ��ʱ����֤ǰ����ȷ�����U��I��P��Pf

        sBkgrdFlag_TypeDef  fChange;    //��̨״̬��־��

        sMtSta_TypeDef  MtSta;  //���״̬��
        sMtSysSta_TypeDef  MtSysSta;   //����ģ��ϵͳ״̬��
        sMeasureSysSta_TypeDef  MeasureSysSta;   //����ϵͳ״̬��

        u8      Fl;             //��ǰ����
        u8      nPOT;           //��ǰʱ�κ�
        u8      nDayPOT;        //��ǰʹ�õ���ʱ�α��
        u8      nTZone;         //��ǰʹ�õ���ʱ����
        u8      nFl;            //��ǰ������
        u8      Second;

        u8      CommStatus;
        u8      EventErr[7];    // dyf EventErr[6] �����ⲿFlash�Ķ�д״̬������/�쳣��EventErr[5]�̳�ԭ���ܣ�Ϊ�ڲ��洢��EE�Ķ�д״̬
        u8      EventWake[6];
        sMoneyAlarm_TypeDef MoneySta;   // ʣ����״̬

        u16         SecondSysStamp;
        u8      RmYearFlag;                 // ������־ 0 �����  1 �¶Ƚ���
        u8      SetRmYearFlag;              // ����½������ñ�־ bit0 �����˵�1������ bit1 ���׽����л�������������ڷ����仯

        u8      CipherKeyFlag;              // ��Կ״̬

        u16     OutStamp;                   // ��ʱ��Ͷ���ź�ʱ��10MS��ʱ
        u16     InsertCardFlag;             // �忨״̬��
        u8      BeepFlag;                   // ������������־ 0a ��������  0b �����쳣
        u16     BeepTime;                   // ���������ʱ��
        u8      UpRunFileFlag;              // ����������Ϣ�ļ�
        u8      UpFlStatusFlag;             // ���·����л��������л��Ȳ���
        u8      CorrectionTime;             // У����Чʱ��
        u8      CorrectionFlag;             // У��������Ч��־
        u8      CheckMoneyFlag;             // �Ƿ����к�բ������
        u8      FactoryFlag;                // ��״̬ 55�����ڣ���AA�����⣩
        u16     CheckZBStamp;               // ����ز�ͨѶ��״̬
        u8      CheckZBFlag;                // ��⵽�ز����е͵�ƽ����Ϊ���ز�ģ����� 0 �� 1 ��
        u8      RUpdateMoneyFlag;           // ״̬��ѯ��־����Ϊ0ʱ�����ѽ���״̬��ѯ
        u8      UpDateTimeFlag;             //ʱ��ı��־λ
        u8      ZBRSTFlag;                  // �ز�ģ�鸴λ�ź�
        sValCurStatusFlag_TypeDef ValCurStatus; //��ѹ����ʵʱ״̬��־

        u8      tEmuRstDely;                // ������λ��ʱʱ��,3S��Ž��е����ж�
        u8      Broatcase_SfType;               //�㲥Уʱ���䰲ȫģʽ

        u8      tMngPlug;                   // ����ģ������ʱʱ��
        u8      FUrmsRdFlg;                 // ������ѹ��ȡ��־

        u16     FrzWink_Delay;              //˲ʱ������ʱִ��ʱ�� ��λ:��
        u8      FrzMin_LineItem;            //���Ӷ����������

        s16     Temperature;    //NNN.N 2
        s32     Temperature2;   //NNN.NNN 3
        u16     ClockBat;       //NN.NN 2
        u16     BackupBat;      //NN.NN 2
        u32     tWorkBat;           //---NNNN  ʱ�ӹ���ʱ�䣨���ӣ�

        s16     Tnal_Tmper[MAX_TERMINAL_TMP_NUM];   //�����¶ȣ��з�������0.1��
        //s16   TnTmper_Wave[2][MAX_TERMINAL_TMP_NUM]; // 2���Ӷ���ƽ���¶�ֵ [0][4]:��1���Ӷ���ƽ���¶�  [1][4] ��ǰ1���Ӷ����¶�
        //s16   TnTmper_Chang[MAX_TERMINAL_TMP_NUM];    // �����¶ȸı���
    } PubData;

    struct sPriData_TypeDef
    {
        u8      Second;
        u8      Minute;
        u8      Hour;
        u8      Day;
        u8      Month;
        u8      Fl;
        u8      nPOT;
    } PriData;

    struct sPriPara_TypeDef
    {
        u8      WireMode;   //=0 ��������; =1 ��������
        u8      InvalidByte1;     //Ϊ�˶�����ӵ���Ч�ֽ�
        u16     Crc;
    } PriPara;
} sBkgrd_TypeDef;

//=============================================
#if 0 //(nPhs==ThreePhs)
#define EVGEN_MARK_LOSSVOLA     ( (u32)1 << 0)
#define EVGEN_MARK_LOSSVOLB     ( (u32)1 << 1)
#define EVGEN_MARK_LOSSVOLC     ( (u32)1 << 2)

#define EVGEN_MARK_LACKVOLA     ( (u32)1 << 3)
#define EVGEN_MARK_LACKVOLB     ( (u32)1 << 4)
#define EVGEN_MARK_LACKVOLC     ( (u32)1 << 5)

#define EVGEN_MARK_OVERVOLA     ( (u32)1 << 6)
#define EVGEN_MARK_OVERVOLB     ( (u32)1 << 7)
#define EVGEN_MARK_OVERVOLC     ( (u32)1 << 8)

#define EVGEN_MARK_LOSSPHAA     ( (u32)1 << 9)
#define EVGEN_MARK_LOSSPHAB     ( (u32)1 << 10)
#define EVGEN_MARK_LOSSPHAC     ( (u32)1 << 11)

#define EVGEN_MARK_LOSSCURA     ( (u32)1 << 12)
#define EVGEN_MARK_LOSSCURB     ( (u32)1 << 13)
#define EVGEN_MARK_LOSSCURC     ( (u32)1 << 14)

#define EVGEN_MARK_OVERCURA     ( (u32)1 << 15)
#define EVGEN_MARK_OVERCURB     ( (u32)1 << 16)
#define EVGEN_MARK_OVERCURC     ( (u32)1 << 17)

#define EVGEN_MARK_BREAKCURA        ( (u32)1 << 18)
#define EVGEN_MARK_BREAKCURB        ( (u32)1 << 19)
#define EVGEN_MARK_BREAKCURC        ( (u32)1 << 20)

#define EVGEN_MARK_INSWIMA      ( (u32)1 << 21)
#define EVGEN_MARK_INSWIMB      ( (u32)1 << 22)
#define EVGEN_MARK_INSWIMC      ( (u32)1 << 23)

#define EVGEN_MARK_OVERPWA      ( (u32)1 << 24)
#define EVGEN_MARK_OVERPWB      ( (u32)1 << 25)
#define EVGEN_MARK_OVERPWC      ( (u32)1 << 26)

#define EVGEN_MARK_OVERQD1QNEED ( (u32)1 << 27)
#define EVGEN_MARK_OVERQD2QNEED ( (u32)1 << 28)
#define EVGEN_MARK_OVERQD3QNEED ( (u32)1 << 29)
#define EVGEN_MARK_OVERQD4QNEED ( (u32)1 << 30)
#define EVGEN_MARK_OVERQNEED        ( (u32)0x3C << 1)

#define EVGEN_MARK_OVERPF           ( (u32)1 << 31)
#define EVGEN_MARK_OVERPFA      ( (u32)1 << 0)    //A�๦����������
#define EVGEN_MARK_OVERPFB      ( (u32)1 << 1)    //B�๦����������
#define EVGEN_MARK_OVERPFC      ( (u32)1 << 2)    //C�๦����������

#define EVGEN_MARK_OVERPTPNEED  ( (u32)1 << 3)
#define EVGEN_MARK_OVERNTPNEED  ( (u32)1 << 4)
#define EVGEN_MARK_OVERPNEED        ( (u32)0x0C << 1)

#define EVGEN_MARK_QLOSSVOL     ( (u32)1 << 5)
#define EVGEN_MARK_LOSSAUX      ( (u32)1 << 6)
#define EVGEN_MARK_INPHAVOL     ( (u32)1 << 7)
#define EVGEN_MARK_INPHACUR     ( (u32)1 << 8)
#define EVGEN_MARK_POWDN            ( (u32)1 << 9)

#define EVGEN_MARK_UNBLVOL      ( (u32)1 << 10)
#define EVGEN_MARK_UNBLCUR      ( (u32)1 << 11)
#define EVGEN_MARK_OVERUNBLCUR  ( (u32)1 << 12)

#define EVGEN_MARK_NLineErr            ( (u32)1 << 13)
#define EVGEN_MARK_MeasureErr       ( (u32)1 << 14)
#define EVGEN_MARK_PSING            ( (u32)1 << 15) //�й����ʷ���Ϊ����ֻ�ж�״̬�����¼���¼
#define EVGEN_MARK_QSING            ( (u32)1 << 16) //�޹����ʷ���Ϊ����ֻ�ж�״̬�����¼���¼
#else
//#define   EVGEN_MARK_OVERCURA     ( (u32)1 << 0)
//#define   EVGEN_MARK_POWDN            ( (u32)1 << 1)
//#define   EVGEN_MARK_MeasureErr       ( (u32)1 << 2)
//#define   EVGEN_MARK_NLineErr            ( (u32)1 << 3)
#define EVGEN_MARK_MngPlug          ( (u32)1 << 0)
#define EVGEN_MARK_POWDN            ( (u32)1 << 1)
#define EVGEN_MARK_OpenCover        ( (u32)1 << 2)
#define EVGEN_MARK_OpenTail         ( (u32)1 << 3)
#endif

//------�����ϱ�״̬�� 0x2015-------------------
#define REPORT_STATUS_ESAMERR       ( (u32)1 << 1)
#define REPORT_STATUS_CLOCKBAT      ( (u32)1 << 3)
#define REPORT_STATUS_MEMORYERR     ( (u32)1 << 5)
#define REPORT_STATUS_BACKUPBAT     ( (u32)1 << 8)
#define REPORT_STATUS_OVERDRAFT     ( (u32)1 << 9)
#define REPORT_STATUS_GATAOFF       ( (u32)1 << 14)
#define REPORT_STATUS_GATAON        ( (u32)1 << 15)

//---

extern void fnBkgrd_Exec(void);
extern  void fnBkgrd_Day_Exec(void);
extern void fnBkgrd_Hour_Exec(void);
extern void fnBkgrd_GetMtStatusWd(u32 Status0, u32 Status1);

extern  void fnBkgrd_TemperIAGain(void);
extern  void fnBkgrd_ClockBatCalculate(void);
extern void fnBkgrd_GetMeasureStatusWd(void);
extern void fnBkgrd__RTCParaCheck(void);

#endif // __DL645_BKGRD_H
