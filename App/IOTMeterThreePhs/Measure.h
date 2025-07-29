
#ifndef _MEASURE_H
#define _MEASURE_H

#ifdef   _MEASURE_GLOBALS
#define  MEASURE_EXT
#else
#define  MEASURE_EXT  extern
#endif

#define TAI_TI_CE_SHI_EN    0   /* dyf 物联表台体测试使能，1:使能。计量芯+工装板方式测试，台体需要切换多功能端子，需要回确认 */

#define HARDWARE_TYPE_JI_LIANG_XIN          1   /* 普通三相计量芯 220V */
#define HARDWARE_TYPE_DIAN_TAN_BIAO_220_10  2   /* 电碳表 3*220V 10（100）A */
#define HARDWARE_TYPE_DIAN_TAN_BIAO_220_1_5 3   /* 电碳表 3*220V 1.5（6）A */
#define HARDWARE_TYPE_DIAN_TAN_BIAO_577     4   /* 电碳表 3*57.7V 1.5（6）A */

/* 硬件类型配置 */
#define HARDWARE_TYPE_CONFIG        HARDWARE_TYPE_JI_LIANG_XIN

#define DefaultHighPulseRate        10

#define RatedCurFlag                2     // 额定电流标志 0：0.3A，  1：1.5A，  2：10A         dyf 2表示10A

#if (HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_577)
/* 3*57.7V 1.5（6）A */
#define RateUnom    57700           // 57.7V , 3位小数
#define RateIb      15000           // 1.5A  ，4位小数
#elif (HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_220_1_5)
/* 3*220V 1.5（6）A */
#define RateUnom    220000          // 220V , 3位小数
#define RateIb      15000           // 1.5A ，4位小数
#else
/* 默认3*220V 10（100）A */
#define RateUnom    220000          // 220V , 3位小数
#define RateIb      100000          // 10A  ，4位小数
#endif

#define ClearIValue             (RateIb * 0.0015)   // 0.15%Ib以下清零
#define ClearUValue             (RateUnom * 0.01)   // 1%Un以下清零
#define ClearPwValue            (RateUnom/1000 * RateIb/1000 *0.8)  // Un*Ib*0.001*0.8 以下清零

//#define     PwnVoltPer60Un      (RateUnom * 0.6 * 10)   //0.6Un   4位小数
#define     PwnVoltPer60Un      (RateUnom * 0.523 * 10)   //0.523Un   4位小数 dyf 参考三星物联表，低于0.523Un才给管理芯输出掉电信号
#define     FLOWV_VOL60Un       (RateUnom * 0.599)  //留2%余量
#define     FLOWV_CUR5Ib        (RateIb * 0.0499)   //MeasureRms.PubData.I 4位小数

#define     AngleCalc_Volt      (RateUnom * 0.2)    // 20%Un
#define     AngleCalc_Cur       (RateIb * 0.01)     // 1%Ib

#define IRMS_MIN                (RateIb * 0.002)   // 10mA,千分之二
#define URMS_MIN                (RateUnom * 0.1)      //10%以下电压全清零

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

#define Itr_Max         (u32)(RateIb * 0.15)   //--15%~2%之间按功率因素补偿    --
//#define Itr_Max           (u32)(RateIb * 1.2)
#define Imin_Min        (u32)(RateIb * 0.02)   //

#if (RateUnom == 57700)
#define     HarmonicConst       400000  //谐波脉冲常数 ，国网参数
#define     MeterConst          20000   //有功脉冲常数 ，国网参数
#else
#if (HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_220_1_5)
#define     HarmonicConst       200000  //谐波脉冲常数 ，国网参数
#define     MeterConst          10000   //有功脉冲常数 ，国网参数
#else
#define     HarmonicConst       10000   //谐波脉冲常数 ，国网参数
#define     MeterConst          500     //有功脉冲常数 ，国网参数
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

#define NUM_FFT                 128             // 瞬时数据点数64/128/256/512
//#pragma pack(1)

typedef   enum
{
    Un115_COS10_Itr,
    Un110_COS10_Itr,
    Un110_COS05L_Itr,
    Un90_COS10_Itr,
    Un90_COS05L_Itr,
    Un80_COS10_Itr
} eVoltRepairStep_TypeDef;  //电压影响量补偿点

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
} eMeasure_Flag_TypeDef;//8302工作异常标志

typedef enum
{
    MeasureModeEMM      = 0x00,
    MeasureModeNVM1     = 0x01,
    MeasureModeNVM2 = 0x11,
    MeasureModeSLM      = 0x10
} eMeasureMode_TypeDef;/*"计量模式"*/

typedef enum
{
    QUADRANT_I      = 0x00,
    QUADRANT_II     = 0x01,
    QUADRANT_III    = 0x11,
    QUADRANT_IV     = 0x10
} eDl645Front_Quadrant_TypeDef;//一二三四象限

typedef union                                         //公共数据运算区8字节
{
    u8  ucTempBuf[8];
    u32 lTemp32;
    u16 wTemp16;
    u8  ucTemp8;
} sDataComm_TypeDef;

typedef struct
{
    u32 Chksum: 16;         //校验和输出
    u32 ChksumBusy: 1;      //=0，表示校表数据校验和计算已经完成。校验值可用
    u32 REVP : 1;           //反向有功功率指示标识信号，当检测到负有功功率时，该信号为 1
    u32 REVQ: 1;            //反向自定义功率指示标识信号，当检测到负功率时，该信号为 1
    u32 Nopld: 1;           //当有功功率小于起动功率时，NoPld 被置为 1
    u32 ANopld: 1;          // A相有功处于潜动状态 置 1    bit20
    u32 BNopld: 1;          // B相有功处于潜动状态 置 1
    u32 CNopld: 1;          // C相有功处于潜动状态 置 1
    u32 Noqld : 1;          //当自定义功率小于起动功率时，NoPld 被置为 1
    u32 ANoqld: 1;          // A相无功处于潜动状态 置 1    bit24
    u32 BNoqld: 1;          // B相无功处于潜动状态 置 1
    u32 CNoqld: 1;          // C相无功处于潜动状态 置 1
    u32 CHNSEL  : 1;        //=1 表示当前用于计算有功电能的电流通道为通道 B,=0表示A通道，默认0
    u32  VREFLOW: 1;        //=1，表示 REFV 引脚的电压值过低，外部电路有异常

    u32  Reserve1 : 1;
} sEMUStatusBit_TypeDef;    //计量模组系统状态字

typedef union
{
    u32             EMUSta;
    sEMUStatusBit_TypeDef   EMUStaBit;
} sEMUStatus_TypeDef;       //计量状态和效验和寄存器

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
    u8      ChkErrCnt;       //读错误计数1

    s32     Pw[(nPhs + 1) * 3];         //{Pa Pb Pc P Qa Qb Qc Q Sa Sb Sc S}   48

    u32     Urms[nPhs];            // Ua/ub/uc
    u32     Irms[nPhs + 1];         // ia/ib/ic/IN

    s32     VectorU[nPhs];      // 正序、负序、零序电压
    s32     VectorI[nPhs];      // 正序、负序、零序电流
    s32     Pf[nPhs + 1];       //Pf Pfa Pfb Pfc      16
    u32     Frequency;      //电网频率，单位：        4

    u32     FUrms[nPhs];        // 基波电压
    u32     FIrms[nPhs];        // 基波电流
    s32     FPw[nPhs + 1];          // 基波功率

    u32     HfIrms2[nPhs];      // 电流半波有效值2

    u32     Pulse[(nPhs + 1) * 3 + (nPhs + 1) * 2]; //前台高频脉冲48
    //---电能脉冲---
    u16     Pulse_Eg[(nPhs + 1) * 3 + (nPhs + 1) * 2]; //低频脉冲数{P,Q,Ps},{Pa,Qa,Psa},{Pb,Qb,Psb},{Pc,Qc,Psc}{Fp,Fq}{Fpa,Fqa}{Fpb,Fqb}{Fpc,Fqc}
    // Pulse_Eg[20] 失压、失流
    //---需量脉冲---
    //      u16     Pulse_Need[12]; //{PNeed,QNeed,PsNeed},{PNeeda,QNeeda,PsNeeda},{PNeedb,QNeedb,PsNeedb},{PNeedc,QNeedc,PsNeedc}48

    s64     Ppwave[4];      //有功脉冲数 1min,
    s64     Pqwave[4];      //无功脉冲数 1min,
    u8      Pwave_sec;      //平均有功功率(1min)累计秒
    u8      PCalcFlg;       //计算标志

    u32     Angle[3 * nPhs]; /*"UB UC IA IB IC"*/
    u16     PDirect;
    u16     PQNoLoad;           // 功率启动标志
    //4
    u32     ChkSum1;   //4
    u32     ChkSum2;   //4
} sMeasureRegTmp_TypeDef;//8302读出的数据缓冲区

typedef struct
{
    struct sMeasureRmsPubData_TypeDef
    {
        u32     U[nPhs];            //---电压---NNN.NNN6    dyf NNN.N => NNN.NNN
        u16     VectorU[nPhs];      // 正序电压   负序电压   零序电压
        s32     I[nPhs];            //---电流NNNN.NNNN(电流值要求3整3小，整定值要求2整4小，最高位表示方向)---16
        s32     In;         //--零线-电流NNNN.NNNN(电流值要求3整3小，整定值要求2整4小，最高位表示方向)---16

        s32     VectorI[nPhs];      // 正序电流   负序电流   零序电流
        s32     Pw[nPhs * 4];       //---瞬时有功/无功/视在功率NN.NNNN---{P Pa Pb Pc Q Qa Qb Qc S Sa Sb Sc}36
        s16     Pf[nPhs + 1];           //---功率因数N.NNN---   最高位表示方向{Pf Pfa Pfb Pfc}  8  sDF05
        u16     Angle[nPhs * 3 + 1];    //---相角NNN.N---       18  /*"UBA UCA IAUA IBUB ICUC"*/
        //PhUa,PhUb,PhUc, 以A相电压为基准，B、C相角度               //(hyg) BCD码
        //PhIa,PhIb,PhIc,A相电流与A相电压间角度、B相电流与B相电压间角度、C相电流与C相电压间角度
        //Angle A,Angle B,Angle C, A相电流与A相电压间角度、B相电流与A相电压间角度、C相电流与A相电压间角度
        //Angle C-Angle A ,C相电流与A相电流间角度
        u32     UnblU;          //电压不平衡度NNNN.NN%4
        u32     UnblI;          //电流不平衡度NNNN.NN%4

        u16     FuzzyU[nPhs];       //---电压波形失真度NN.NN%---    6
        u16     FuzzyI[nPhs];       //---电流波形失真度NN.NN%---    6

        //---其他---
        u16     Frequency;      //NN.NN 2
        s32     PPwave[nPhs + 1];       //NN.NNNN 4 ，1分钟平均有功功率
        s32     Pqwave[nPhs + 1];       //分钟平均无功功率
        s32     Pswave[nPhs + 1];       //分钟平均视在功率

        u8      PDirect;        //原功率方向，用于需量处理(0总/1A/2B/3C , 注意与FrontTmp不同) 1
        u8      OPDirect;       //历史功率方向

        sEMUStatus_TypeDef    EMUStatus;
        sDirectSta_TypeDef        DirectSta;

        u32     HUrms[3][41];       // 基波及谐波电压,V,4位小数
        u32     HIrms[3][41];       // 基波及谐波电流,A,4位小数
        s32     HPrms[3][41];       // 基波及谐波功率,w,4位小数
        u32     HPtw;               // 正向谐波总功率
        u32     HNtw;               // 反向谐波总功率
    } PubData;

    struct sMeasureRmsPriData_TypeDef
    {
        u16     Flag;           //---工作异常标志---1
        u16     MeasureStamp;
    } PriData;

    struct sMeasureRmsPriPara_TypeDef
    {
        u32  PConstE;           //有功常数
        u32  QConstE;           //无功常数(Hex码)4
        u16  Crc;//2
    } PriPara;
} sMeasureRms_TypeDef;  //缓冲区转换后的有效数据
#pragma pack(1)

typedef struct
{
    u16 nPoint: 12;     //采样数据输出点数
    u16 EnOrDis: 4;    //=0 停止采样数据输出; =A 启动采样数据输出
} sSendParaBit_TypeDef; //采样数据输出

typedef union
{
    u16             SendPara;
    sSendParaBit_TypeDef    SendParaBit;
} sSendPara_TypeDef;        //采样数据输出

typedef struct
{
    u8 FractionI;   /*电流小数位数*/
    u8 FractionU;   /*电压小数位数*/
    u8 FractionE;   /*电能小数位数*/
    u8 FractionP;   /*功率需量小数位数*/
    u16 Pulse_deltaE;/*数*/
    u8  HighPulseRate;      // 高频脉冲数放大倍数
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
    u16 U_OS[nPhs];             // 电压电流OFFSET校正 RN8302_UA_OS ~ RN8302_UC_OS
    u16 I_OS[nPhs + 1];         // 电压电流OFFSET校正 RN8302_IA_OS ~ RN8302_IC_OS
    u16 GP[nPhs];               /* 有功增益校正寄存器 RN8302_GPA ~ RN8302_GPC */
    u16 GQ[nPhs];               // RN8302_GQA ~ RN8302_GQC
    u16 GS[nPhs];               // RN8302_GSA ~ RN8302_GSC
    u16 P_PHS[nPhs];            // 有功相位---分段相位 低段 RN8302_PA_PHSL ~ RN8302_PC_PHSL
    u16 Q_PHS[nPhs];            // 无功相位---分段相位 低段 RN8302_QA_PHSL ~ RN8302_QC_PHSL
    u16 P_OS[nPhs];             // 有功功率offset RN8302_PA_OS ~ RN8302_PC_OS
    u16 Q_OS[nPhs];             // 无功功率offset RN8302_QA_OS ~ RN8302_QC_OS
    u32 P_PHSMH[6];             // 有功相位---分段相位 中高段 RN8302_PA_PHSM,RN8302_PA_PHSH~
    u32 Q_PHSMH[6];             // 无功相位---分段相位 中高段 RN8302_QA_PHSM,RN8302_QA_PHSH~
    u32 ChkSum1;                // RN8302_CheckSum1

    u32 KUrms;          //
    u32 KIArms;
    u32 KPrms;

    // no use
    u16 RatedU;                 // 台体校正时额定电压
    u32 RatedUrms;              // 台体校正时额定电压寄存器值
    u16 RatedI;                 // 台体校正时额定电流
    u32 RatedIrms;              // 台体校正时额定电流寄存器值
    u32 RealU[nPhs];            // 台体校正时电压
    u32 RealI[nPhs + 1];        // 台体校正时电流
    u16 RealAngle[6];           // 台体校正时角度
    u32 RealPw[nPhs];           // 台体相位校正时功率值
    // no use end

    sSendPara_TypeDef       Send_nPoint;            // 波形缓存发送数据点数

    u16 Crc;
} sMeasureFirmPara_TypeDef;     //184 Byte

typedef struct
{
    u16  PConstE;               //脉冲常数
    u16  Hfconst;               //
    u32 StandUn[nPhs];      // 校正时台体标准电压
    u32 StandUnreg[nPhs];   // 校正时台体电压寄存器标准值
    u32 StandIb[nPhs + 1];      // 校正时台体标准电流
    u32 StandIbreg[nPhs + 1]; // 校正时台体电流寄存器标准值
    u32 StandPw[nPhs];      // 校正时台体标准功率
    u32 StandPwreg[nPhs];   // 校正时台体功率寄存器标准值
    s32 Err[nPhs];                  //误差
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
    u8      EnWaveSpi;                      // 是否使能波形数据往外发送
    u8      nCnt;
    u16     nTLen;                          // 波形数据总长度

    u8      nErr;
    u8      resd[3];                        // 保留

    u16     nSmplPoint;                     // 波形采样点数
    u8      Head;                           // 帧头---0x68
    u8      Ctrl;                           // 控制码---0x33
    u16     fLen;                           // 帧长度
    u8      fSeq;                           // 帧序号
    u8      fEnd;                           // 结束码---0x16
    u32     nSum;                           // 波形校验和
    u8      WaveSpiOut[4621];               // 按256点最大波形输出配置缓存大小  头3字节+帧头5字节用于字节对齐
} sWaveSpiOutTypedef;

#define     nHmCyc      2

typedef struct
{
    FunctionalControl ReadFlag;         //半波采样启动标志
    u8      MsCnt;
    u8      Rate;                       //采样频率，技术要求10表示10ms采样速度，对应半波有效值
    u16     RDepth;                     //采样深度,技术要求默认480，可配置
    u16     Cnt;                        //当前采样点数
    u16     Irms[3][480];
} sHalfIrms_TypeDef;   //电流半波有效值

typedef union
{
    u32     HmSmplVal[nHmCyc][256][6];
    u32     HmVal[nHmCyc][4][384];
} sHmAdcTypedef;

typedef struct
{
    u16     InPoint;
    u16     OutPoint;
    u16     NotEmpty : 1;   // 非空标志{0=空、1=非空}
    u16     Full : 1;       // 满标志{0=不满、1=满}
    u16     Res : 14;       // 保留
    u16     revsed;
    sHmAdcTypedef       sHm;
    sHalfIrms_TypeDef   HalfIrms;           //半波有效值
} sHmWaveTypedef;

typedef struct
{
    s32 Pw[12];
    s16 Pf[4];
    s32 AvgPw[8];
} sSynVarOtherUnitDataTypeDef;

//extern const  sMeasureFirmPara_TypeDef FirmParaDefault;

extern void fnRN8302_Stop(void);
extern void fnRN8302Mode_Init(eMeasureMode_TypeDef MeasureMode);                //上电初始化校表参数，写入EMU
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
