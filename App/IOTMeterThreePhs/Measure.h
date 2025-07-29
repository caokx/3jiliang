
#ifndef _MEASURE_H
#define _MEASURE_H

#ifdef   _MEASURE_GLOBALS
#define  MEASURE_EXT
#else
#define  MEASURE_EXT  extern
#endif

#define TAI_TI_CE_SHI_EN    0   /* dyf ������̨�����ʹ�ܣ�1:ʹ�ܡ�����о+��װ�巽ʽ���ԣ�̨����Ҫ�л��๦�ܶ��ӣ���Ҫ��ȷ�� */

#define HARDWARE_TYPE_JI_LIANG_XIN          1   /* ��ͨ�������о 220V */
#define HARDWARE_TYPE_DIAN_TAN_BIAO_220_10  2   /* ��̼�� 3*220V 10��100��A */
#define HARDWARE_TYPE_DIAN_TAN_BIAO_220_1_5 3   /* ��̼�� 3*220V 1.5��6��A */
#define HARDWARE_TYPE_DIAN_TAN_BIAO_577     4   /* ��̼�� 3*57.7V 1.5��6��A */

/* Ӳ���������� */
#define HARDWARE_TYPE_CONFIG        HARDWARE_TYPE_JI_LIANG_XIN

#define DefaultHighPulseRate        10

#define RatedCurFlag                2     // �������־ 0��0.3A��  1��1.5A��  2��10A         dyf 2��ʾ10A

#if (HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_577)
/* 3*57.7V 1.5��6��A */
#define RateUnom    57700           // 57.7V , 3λС��
#define RateIb      15000           // 1.5A  ��4λС��
#elif (HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_220_1_5)
/* 3*220V 1.5��6��A */
#define RateUnom    220000          // 220V , 3λС��
#define RateIb      15000           // 1.5A ��4λС��
#else
/* Ĭ��3*220V 10��100��A */
#define RateUnom    220000          // 220V , 3λС��
#define RateIb      100000          // 10A  ��4λС��
#endif

#define ClearIValue             (RateIb * 0.0015)   // 0.15%Ib��������
#define ClearUValue             (RateUnom * 0.01)   // 1%Un��������
#define ClearPwValue            (RateUnom/1000 * RateIb/1000 *0.8)  // Un*Ib*0.001*0.8 ��������

//#define     PwnVoltPer60Un      (RateUnom * 0.6 * 10)   //0.6Un   4λС��
#define     PwnVoltPer60Un      (RateUnom * 0.523 * 10)   //0.523Un   4λС�� dyf �ο���������������0.523Un�Ÿ�����о��������ź�
#define     FLOWV_VOL60Un       (RateUnom * 0.599)  //��2%����
#define     FLOWV_CUR5Ib        (RateIb * 0.0499)   //MeasureRms.PubData.I 4λС��

#define     AngleCalc_Volt      (RateUnom * 0.2)    // 20%Un
#define     AngleCalc_Cur       (RateIb * 0.01)     // 1%Ib

#define IRMS_MIN                (RateIb * 0.002)   // 10mA,ǧ��֮��
#define URMS_MIN                (RateUnom * 0.1)      //10%���µ�ѹȫ����

#define  Un115_Max      (u32)(RateUnom * 1.165)  //256.3V
#define  Un115_Min      (u32)(RateUnom * 1.118)  //245.9V

#define  Un110_Max      (u32)(RateUnom * 1.118)  //245.9V
#define  Un110_Min      (u32)(RateUnom * 1.086)  //238.9V

#define  Un90_Max       (u32)(RateUnom * 0.913)  //200.8V
#define  Un90_Min       (u32)(RateUnom * 0.886) //194.9V

#define  Un80_Max       (u32)(RateUnom * 0.886) //194.9V
#define  Un80_Min       (u32)(RateUnom * 0.786) //172.9V

#define  COS10_Max      1000 //
#define  COS10_Min      900 //

#define  COS05L_Max     600 //
#define  COS05L_Min     400 //

#define Itr_Max         (u32)(RateIb * 0.15)   //--15%~2%֮�䰴�������ز���    --
//#define Itr_Max           (u32)(RateIb * 1.2)
#define Imin_Min        (u32)(RateIb * 0.02)   //

#if (RateUnom == 57700)
#define     HarmonicConst       400000  //г�����峣�� ����������
#define     MeterConst          20000   //�й����峣�� ����������
#else
#if (HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_220_1_5)
#define     HarmonicConst       200000  //г�����峣�� ����������
#define     MeterConst          10000   //�й����峣�� ����������
#else
#define     HarmonicConst       10000   //г�����峣�� ����������
#define     MeterConst          500     //�й����峣�� ����������
#endif
#endif
#define     Harmonic_D2FK       (HarmonicConst/MeterConst)

#define  RN8302C           0
#define  RN8302C_V3     1
#define  RN8302B           2
#define  RN8306             3

#if (PCB_Version==RN8318_RN8306)
#define  RN8302C_Ver   RN8306
#elif (PCB_Version==RN8318_RN8302C_V3)
#define  RN8302C_Ver   RN8302C_V3
#elif (PCB_Version==RN8318_RN8302C)
#define  RN8302C_Ver   RN8302C
#else
#define  RN8302C_Ver   RN8302B
#endif

#define NUM_FFT                 128             // ˲ʱ���ݵ���64/128/256/512
//#pragma pack(1)

typedef   enum
{
    Un115_COS10_Itr,
    Un110_COS10_Itr,
    Un110_COS05L_Itr,
    Un90_COS10_Itr,
    Un90_COS05L_Itr,
    Un80_COS10_Itr
} eVoltRepairStep_TypeDef;  //��ѹӰ����������

typedef enum
{
    MEASURE_FLAG_INIT               = 0x01,
    MEASURE_FLAG_RST        = 0x02,
    MEASURE_FLAG_Err        = 0x04,
    MEASURE_FLAG_CorrectionUI   = 0x08,
    MEASURE_FLAG_CorrectionPHS  = 0x10,
    MEASURE_FLAG_CorrectionPHSL = 0x20,
    MEASURE_FLAG_CorrectionPHSM = 0x40,
    MEASURE_FLAG_CalcCheckSum   = 0x80,
    MEASURE_FLAG_CorrectionIn   = 0x100,
} eMeasure_Flag_TypeDef;//8302�����쳣��־

typedef enum
{
    MeasureModeEMM      = 0x00,
    MeasureModeNVM1     = 0x01,
    MeasureModeNVM2 = 0x11,
    MeasureModeSLM      = 0x10
} eMeasureMode_TypeDef;/*"����ģʽ"*/

typedef enum
{
    QUADRANT_I      = 0x00,
    QUADRANT_II     = 0x01,
    QUADRANT_III    = 0x11,
    QUADRANT_IV     = 0x10
} eDl645Front_Quadrant_TypeDef;//һ����������

typedef union                                         //��������������8�ֽ�
{
    u8  ucTempBuf[8];
    u32 lTemp32;
    u16 wTemp16;
    u8  ucTemp8;
} sDataComm_TypeDef;

typedef struct
{
    u32 Chksum: 16;         //У������
    u32 ChksumBusy: 1;      //=0����ʾУ������У��ͼ����Ѿ���ɡ�У��ֵ����
    u32 REVP : 1;           //�����й�����ָʾ��ʶ�źţ�����⵽���й�����ʱ�����ź�Ϊ 1
    u32 REVQ: 1;            //�����Զ��幦��ָʾ��ʶ�źţ�����⵽������ʱ�����ź�Ϊ 1
    u32 Nopld: 1;           //���й�����С���𶯹���ʱ��NoPld ����Ϊ 1
    u32 ANopld: 1;          // A���й�����Ǳ��״̬ �� 1    bit20
    u32 BNopld: 1;          // B���й�����Ǳ��״̬ �� 1
    u32 CNopld: 1;          // C���й�����Ǳ��״̬ �� 1
    u32 Noqld : 1;          //���Զ��幦��С���𶯹���ʱ��NoPld ����Ϊ 1
    u32 ANoqld: 1;          // A���޹�����Ǳ��״̬ �� 1    bit24
    u32 BNoqld: 1;          // B���޹�����Ǳ��״̬ �� 1
    u32 CNoqld: 1;          // C���޹�����Ǳ��״̬ �� 1
    u32 CHNSEL  : 1;        //=1 ��ʾ��ǰ���ڼ����й����ܵĵ���ͨ��Ϊͨ�� B,=0��ʾAͨ����Ĭ��0
    u32  VREFLOW: 1;        //=1����ʾ REFV ���ŵĵ�ѹֵ���ͣ��ⲿ��·���쳣

    u32  Reserve1 : 1;
} sEMUStatusBit_TypeDef;    //����ģ��ϵͳ״̬��

typedef union
{
    u32             EMUSta;
    sEMUStatusBit_TypeDef   EMUStaBit;
} sEMUStatus_TypeDef;       //����״̬��Ч��ͼĴ���

typedef struct
{
    u8 Pw: 4;   //
    u8 Qw: 4;       //
} sDirectStaBit_TypeDef;    //

typedef union
{
    u8              Direct;
    sDirectStaBit_TypeDef   DirectBit;
} sDirectSta_TypeDef;       //

typedef struct
{
    u8      ChkErrCnt;       //���������1

    s32     Pw[(nPhs + 1) * 3];         //{Pa Pb Pc P Qa Qb Qc Q Sa Sb Sc S}   48

    u32     Urms[nPhs];            // Ua/ub/uc
    u32     Irms[nPhs + 1];         // ia/ib/ic/IN

    s32     VectorU[nPhs];      // ���򡢸��������ѹ
    s32     VectorI[nPhs];      // ���򡢸����������
    s32     Pf[nPhs + 1];       //Pf Pfa Pfb Pfc      16
    u32     Frequency;      //����Ƶ�ʣ���λ��        4

    u32     FUrms[nPhs];        // ������ѹ
    u32     FIrms[nPhs];        // ��������
    s32     FPw[nPhs + 1];          // ��������

    u32     HfIrms2[nPhs];      // �����벨��Чֵ2

    u32     Pulse[(nPhs + 1) * 3 + (nPhs + 1) * 2]; //ǰ̨��Ƶ����48
    //---��������---
    u16     Pulse_Eg[(nPhs + 1) * 3 + (nPhs + 1) * 2]; //��Ƶ������{P,Q,Ps},{Pa,Qa,Psa},{Pb,Qb,Psb},{Pc,Qc,Psc}{Fp,Fq}{Fpa,Fqa}{Fpb,Fqb}{Fpc,Fqc}
    // Pulse_Eg[20] ʧѹ��ʧ��
    //---��������---
    //      u16     Pulse_Need[12]; //{PNeed,QNeed,PsNeed},{PNeeda,QNeeda,PsNeeda},{PNeedb,QNeedb,PsNeedb},{PNeedc,QNeedc,PsNeedc}48

    s64     Ppwave[4];      //�й������� 1min,
    s64     Pqwave[4];      //�޹������� 1min,
    u8      Pwave_sec;      //ƽ���й�����(1min)�ۼ���
    u8      PCalcFlg;       //�����־

    u32     Angle[3 * nPhs]; /*"UB UC IA IB IC"*/
    u16     PDirect;
    u16     PQNoLoad;           // ����������־
    //4
    u32     ChkSum1;   //4
    u32     ChkSum2;   //4
} sMeasureRegTmp_TypeDef;//8302���������ݻ�����

typedef struct
{
    struct sMeasureRmsPubData_TypeDef
    {
        u32     U[nPhs];            //---��ѹ---NNN.NNN6    dyf NNN.N => NNN.NNN
        u16     VectorU[nPhs];      // �����ѹ   �����ѹ   �����ѹ
        s32     I[nPhs];            //---����NNNN.NNNN(����ֵҪ��3��3С������ֵҪ��2��4С�����λ��ʾ����)---16
        s32     In;         //--����-����NNNN.NNNN(����ֵҪ��3��3С������ֵҪ��2��4С�����λ��ʾ����)---16

        s32     VectorI[nPhs];      // �������   �������   �������
        s32     Pw[nPhs * 4];       //---˲ʱ�й�/�޹�/���ڹ���NN.NNNN---{P Pa Pb Pc Q Qa Qb Qc S Sa Sb Sc}36
        s16     Pf[nPhs + 1];           //---��������N.NNN---   ���λ��ʾ����{Pf Pfa Pfb Pfc}  8  sDF05
        u16     Angle[nPhs * 3 + 1];    //---���NNN.N---       18  /*"UBA UCA IAUA IBUB ICUC"*/
        //PhUa,PhUb,PhUc, ��A���ѹΪ��׼��B��C��Ƕ�               //(hyg) BCD��
        //PhIa,PhIb,PhIc,A�������A���ѹ��Ƕȡ�B�������B���ѹ��Ƕȡ�C�������C���ѹ��Ƕ�
        //Angle A,Angle B,Angle C, A�������A���ѹ��Ƕȡ�B�������A���ѹ��Ƕȡ�C�������A���ѹ��Ƕ�
        //Angle C-Angle A ,C�������A�������Ƕ�
        u32     UnblU;          //��ѹ��ƽ���NNNN.NN%4
        u32     UnblI;          //������ƽ���NNNN.NN%4

        u16     FuzzyU[nPhs];       //---��ѹ����ʧ���NN.NN%---    6
        u16     FuzzyI[nPhs];       //---��������ʧ���NN.NN%---    6

        //---����---
        u16     Frequency;      //NN.NN 2
        s32     PPwave[nPhs + 1];       //NN.NNNN 4 ��1����ƽ���й�����
        s32     Pqwave[nPhs + 1];       //����ƽ���޹�����
        s32     Pswave[nPhs + 1];       //����ƽ�����ڹ���

        u8      PDirect;        //ԭ���ʷ���������������(0��/1A/2B/3C , ע����FrontTmp��ͬ) 1
        u8      OPDirect;       //��ʷ���ʷ���

        sEMUStatus_TypeDef    EMUStatus;
        sDirectSta_TypeDef        DirectSta;

        u32     HUrms[3][41];       // ������г����ѹ,V,4λС��
        u32     HIrms[3][41];       // ������г������,A,4λС��
        s32     HPrms[3][41];       // ������г������,w,4λС��
        u32     HPtw;               // ����г���ܹ���
        u32     HNtw;               // ����г���ܹ���
    } PubData;

    struct sMeasureRmsPriData_TypeDef
    {
        u16     Flag;           //---�����쳣��־---1
        u16     MeasureStamp;
    } PriData;

    struct sMeasureRmsPriPara_TypeDef
    {
        u32  PConstE;           //�й�����
        u32  QConstE;           //�޹�����(Hex��)4
        u16  Crc;//2
    } PriPara;
} sMeasureRms_TypeDef;  //������ת�������Ч����
#pragma pack(1)

typedef struct
{
    u16 nPoint: 12;     //���������������
    u16 EnOrDis: 4;    //=0 ֹͣ�����������; =A ���������������
} sSendParaBit_TypeDef; //�����������

typedef union
{
    u16             SendPara;
    sSendParaBit_TypeDef    SendParaBit;
} sSendPara_TypeDef;        //�����������

typedef struct
{
    u8 FractionI;   /*����С��λ��*/
    u8 FractionU;   /*��ѹС��λ��*/
    u8 FractionE;   /*����С��λ��*/
    u8 FractionP;   /*��������С��λ��*/
    u16 Pulse_deltaE;/*��*/
    u8  HighPulseRate;      // ��Ƶ�������Ŵ���
    u16 HFConst1;   // =>HFConst2, HFConst1=HFConst2/HighPulseRate
    u16 Start_Ps;   // IStart_PS
    u16 Start_Q;    // IStart_Q
    u16 ELostVoltT; // LostVoltT
    u16 Zxot;       // RN8302_ZXOT
    u16 PRth[4];                // RN8302_PRTH1L ~ RN8302_PRTH2H
    u8  PHSU[nPhs];             //
    u32 PHSI[nPhs];             // RN8302_PHSIA ~ RN8302_PHSIC
    u16 GSU[nPhs];              // RN8302_GSUA ~ RN8302_GSUC
    u16 GSI[nPhs + 1];          // RN8302_GSIA ~ RN8302_GSIC,RN8302_GSIN
    u16 U_OS[nPhs];             // ��ѹ����OFFSETУ�� RN8302_UA_OS ~ RN8302_UC_OS
    u16 I_OS[nPhs + 1];         // ��ѹ����OFFSETУ�� RN8302_IA_OS ~ RN8302_IC_OS
    u16 GP[nPhs];               /* �й�����У���Ĵ��� RN8302_GPA ~ RN8302_GPC */
    u16 GQ[nPhs];               // RN8302_GQA ~ RN8302_GQC
    u16 GS[nPhs];               // RN8302_GSA ~ RN8302_GSC
    u16 P_PHS[nPhs];            // �й���λ---�ֶ���λ �Ͷ� RN8302_PA_PHSL ~ RN8302_PC_PHSL
    u16 Q_PHS[nPhs];            // �޹���λ---�ֶ���λ �Ͷ� RN8302_QA_PHSL ~ RN8302_QC_PHSL
    u16 P_OS[nPhs];             // �й�����offset RN8302_PA_OS ~ RN8302_PC_OS
    u16 Q_OS[nPhs];             // �޹�����offset RN8302_QA_OS ~ RN8302_QC_OS
    u32 P_PHSMH[6];             // �й���λ---�ֶ���λ �и߶� RN8302_PA_PHSM,RN8302_PA_PHSH~
    u32 Q_PHSMH[6];             // �޹���λ---�ֶ���λ �и߶� RN8302_QA_PHSM,RN8302_QA_PHSH~
    u32 ChkSum1;                // RN8302_CheckSum1

    u32 KUrms;          //
    u32 KIArms;
    u32 KPrms;

    // no use
    u16 RatedU;                 // ̨��У��ʱ���ѹ
    u32 RatedUrms;              // ̨��У��ʱ���ѹ�Ĵ���ֵ
    u16 RatedI;                 // ̨��У��ʱ�����
    u32 RatedIrms;              // ̨��У��ʱ������Ĵ���ֵ
    u32 RealU[nPhs];            // ̨��У��ʱ��ѹ
    u32 RealI[nPhs + 1];        // ̨��У��ʱ����
    u16 RealAngle[6];           // ̨��У��ʱ�Ƕ�
    u32 RealPw[nPhs];           // ̨����λУ��ʱ����ֵ
    // no use end

    sSendPara_TypeDef       Send_nPoint;            // ���λ��淢�����ݵ���

    u16 Crc;
} sMeasureFirmPara_TypeDef;     //184 Byte

typedef struct
{
    u16  PConstE;               //���峣��
    u16  Hfconst;               //
    u32 StandUn[nPhs];      // У��ʱ̨���׼��ѹ
    u32 StandUnreg[nPhs];   // У��ʱ̨���ѹ�Ĵ�����׼ֵ
    u32 StandIb[nPhs + 1];      // У��ʱ̨���׼����
    u32 StandIbreg[nPhs + 1]; // У��ʱ̨������Ĵ�����׼ֵ
    u32 StandPw[nPhs];      // У��ʱ̨���׼����
    u32 StandPwreg[nPhs];   // У��ʱ̨�幦�ʼĴ�����׼ֵ
    s32 Err[nPhs];                  //���
} sCorrectTmp_TypeDef;

#pragma pack()
typedef struct
{
    u32    UMax;
    u32    UMin;
    u32    IMax;
    u32    IMin;
    u16    CosMax;
    u16    CosMin;
    u8      Step;
}   sVolRepairRange_TypeDef;

typedef struct
{
    u8      EnWaveSpi;                      // �Ƿ�ʹ�ܲ����������ⷢ��
    u8      nCnt;
    u16     nTLen;                          // ���������ܳ���

    u8      nErr;
    u8      resd[3];                        // ����

    u16     nSmplPoint;                     // ���β�������
    u8      Head;                           // ֡ͷ---0x68
    u8      Ctrl;                           // ������---0x33
    u16     fLen;                           // ֡����
    u8      fSeq;                           // ֡���
    u8      fEnd;                           // ������---0x16
    u32     nSum;                           // ����У���
    u8      WaveSpiOut[4621];               // ��256�������������û����С  ͷ3�ֽ�+֡ͷ5�ֽ������ֽڶ���
} sWaveSpiOutTypedef;

#define     nHmCyc      2

typedef struct
{
    FunctionalControl ReadFlag;         //�벨����������־
    u8      MsCnt;
    u8      Rate;                       //����Ƶ�ʣ�����Ҫ��10��ʾ10ms�����ٶȣ���Ӧ�벨��Чֵ
    u16     RDepth;                     //�������,����Ҫ��Ĭ��480��������
    u16     Cnt;                        //��ǰ��������
    u16     Irms[3][480];
} sHalfIrms_TypeDef;   //�����벨��Чֵ

typedef union
{
    u32     HmSmplVal[nHmCyc][256][6];
    u32     HmVal[nHmCyc][4][384];
} sHmAdcTypedef;

typedef struct
{
    u16     InPoint;
    u16     OutPoint;
    u16     NotEmpty : 1;   // �ǿձ�־{0=�ա�1=�ǿ�}
    u16     Full : 1;       // ����־{0=������1=��}
    u16     Res : 14;       // ����
    u16     revsed;
    sHmAdcTypedef       sHm;
    sHalfIrms_TypeDef   HalfIrms;           //�벨��Чֵ
} sHmWaveTypedef;

typedef struct
{
    s32 Pw[12];
    s16 Pf[4];
    s32 AvgPw[8];
} sSynVarOtherUnitDataTypeDef;

//extern const  sMeasureFirmPara_TypeDef FirmParaDefault;

extern void fnRN8302_Stop(void);
extern void fnRN8302Mode_Init(eMeasureMode_TypeDef MeasureMode);                //�ϵ��ʼ��У�������д��EMU
extern  void fnMeasure_EMUInit(void);
extern u8 fnRN8302_ChkSum(void);

extern u8 fnMeasure_VoltRepairCorrect(u8 nphase, u8 step, u32 DataCommErr);
extern  u8 fnMeasure_VoltRepair_CommRead(u8 *data);
extern  void fnMeasure_TIRM_CommWrite(u16 data);
extern  u8 fnMeasure_TIRM_CommRead(u8 *data);
extern  void fnMeasure_RN8207DTIRM_CommWrite(u8 nphase, u16 data);
extern  u8 fnMeasure_RN8207DTIRM_CommRead(u8 *data);

extern void fnMeasure_FirmParaInit(u8 Flag);
extern   void fnMeasure_Init(void);
extern void fnMeasure_FirmParaCheck(void);
extern u8 fnMeasure_VoltRepair_Exe(void);
extern   void fnMeasure_Exec(void);

extern void fnMeasureWSAVE(void);
extern void Measure_WSAVE_Init(void);

extern void fnBSP_ExModuleSpi_Init(void);
extern void fnRN8302_WaveDataToExModule(void);

extern void fnMeasure_TxHarmonicPack(void);
extern  void fnMeasure_DMAReadWaveData(void);
extern void fnMeasure_WaveData(void);
extern void fnMeasure_WaveInit(void);
extern void fnMeasure_WaveColse(void);
extern void fnMeasureAverage_PowerCalc(void);

extern void fnWaveHSpiCheck(void);
extern void fnRN8302_HSPI_DMAInit(void);
extern void fnWaveHsdcSpi_AdcCheck(void);

extern void fnWaveHfrmsSmple(void);
extern void fnWaveSpiOut_SynSmplPoint(void);

extern void fnMeasure_EvtVoltLoss(void);

extern sHmWaveTypedef       sHmWave;

extern sWaveSpiOutTypedef       sWaveSpiOut;
//---------------------

#endif //
