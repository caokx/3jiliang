
#ifndef _ENERGY_H
#define _ENERGY_H

#ifdef   _ENERGY_GLOBALS
#define  ENERGY_EXT
#else
#define  ENERGY_EXT  extern
#endif

#define EGINT64_MYDATA_Len  5

typedef enum
{
    Energy_BCD2FractionE = 0,//
    Energy_BCD4FractionE,//
    Energy_HEX2FractionE,//
    Energy_HEX4FractionE,//
    Energy_HEX6FractionE,//
} eENERGY_DATA_TypeDef;

typedef enum
{
    PConst  = 0x01,         // 有功脉冲数
    QConst  = 0x02,         // 无功脉冲数
    HConst  = 0x03,         // 谐波脉冲数
} eEnergy_EgConst_TypeDef;

typedef struct
{
    u8  EgId;
    u8  Flag;
    u8    *EgUnit;
    u8  *EgRamAd;
    u32 EgRomAd;
    u8  EgLen;
    u8  *EgCrcRamAd;
} sEnergy_Operate_TypeDef;

// 电能顺序，必须与sEgShFile_TypeDef中顺序一致
#if(nPhs==ThreePhs)
typedef enum
{
    PtPEg   = 0x00,
    NtPEg,      //= 0x01    ,
    Qd1QEg,     //= 0x02    ,
    Qd2QEg,     //= 0x03    ,
    Qd3QEg,     //= 0x04    ,
    Qd4QEg,     //= 0x05    ,

    //--------------------
    PtPEgA,     //= 0x06    ,
    NtPEgA,     //= 0x07    ,
    Qd1QEgA,    //= 0x08    ,
    Qd2QEgA,    //= 0x09    ,
    Qd3QEgA,    //= 0x0A    ,
    Qd4QEgA,    //= 0x0B    ,

    //-------------------
    PtPEgB,     //= 0x0C    ,
    NtPEgB,     //= 0x0D    ,
    Qd1QEgB,    //= 0x0E    ,
    Qd2QEgB,    //= 0x0F    ,
    Qd3QEgB,    //= 0x10    ,
    Qd4QEgB,    //= 0x11    ,

    //----------------
    PtPEgC,     //= 0x12    ,
    NtPEgC,     //= 0x13    ,
    Qd1QEgC,    //= 0x14    ,
    Qd2QEgC,    //= 0x15    ,
    Qd3QEgC,    //= 0x16    ,
    Qd4QEgC,    //= 0x17    ,

    PtFEg,      //= 0x18    ,
    NtFEg,      //= 0x19    ,

    PtHEg,      //= 0x1A    ,
    NtHEg,      //= 0x1B    ,

    AllPEg,     //= 0x1C    ,
} eEnergy_EgType_TypeDef;

typedef enum
{
    PieceEgOffAddr_PtPEg    =   0,
    PieceEgOffAddr_NtPEg    =   1,
    PieceEgOffAddr_Qd1QEg   =   PieceEgOffAddr_NtPEg + 1,
    PieceEgOffAddr_Qd2QEg   =   PieceEgOffAddr_Qd1QEg + 1,
    PieceEgOffAddr_Qd3QEg   =   PieceEgOffAddr_Qd2QEg + 1,
    PieceEgOffAddr_Qd4QEg   =   PieceEgOffAddr_Qd3QEg + 1,

    PieceEgOffAddr_PtPEgA   =   PieceEgOffAddr_Qd4QEg + 1,
    PieceEgOffAddr_NtPEgA   =   PieceEgOffAddr_PtPEgA + 1,
    PieceEgOffAddr_Qd1QEgA  =   PieceEgOffAddr_NtPEgA + 1,
    PieceEgOffAddr_Qd2QEgA  =   PieceEgOffAddr_Qd1QEgA + 1,
    PieceEgOffAddr_Qd3QEgA  =   PieceEgOffAddr_Qd2QEgA + 1,
    PieceEgOffAddr_Qd4QEgA  =   PieceEgOffAddr_Qd3QEgA + 1,

    PieceEgOffAddr_PtPEgB   =   PieceEgOffAddr_Qd4QEgA + 1,

    PieceEgOffAddr_PtPEgC =     PieceEgOffAddr_PtPEgB + 6,

    PieceEgOffAddr_PtFEg    =   PieceEgOffAddr_PtPEgC + 6,

    PieceEgOffAddr_NtFEg    =   PieceEgOffAddr_PtFEg + 1,
    PieceEgOffAddr_PtHEg    =   PieceEgOffAddr_NtFEg + 1,
    PieceEgOffAddr_NtHEg    =   PieceEgOffAddr_PtHEg + 1,

    PieceEgOffAddr_end  =   PieceEgOffAddr_NtHEg + 1
} eEnergy_PieceEgOffAddr_TypeDef;//脉冲尾数偏移地址
#else
typedef enum
{
    PtPEg   = 0x00,
    NtPEg   = 0x01,

    Qd1QEg  = 0x02,
    Qd2QEg  = 0x03,
    Qd3QEg  = 0x04,
    Qd4QEg  = 0x05,

    PtFEg   = 0x06,
    NtFEg   = 0x07,

    PtHEg   = 0x08,
    NtHEg   = 0x09,

    AllPEg = 0x0A,
    MaxItemEg = 0x0A,
} eEnergy_EgType_TypeDef;

typedef enum
{
    PieceEgOffAddr_PtPEg    =   0,
    PieceEgOffAddr_NtPEg    =   PieceEgOffAddr_PtPEg + 1,

    PieceEgOffAddr_Qd1QEg   =   PieceEgOffAddr_NtPEg + 1,
    PieceEgOffAddr_Qd2QEg   =   PieceEgOffAddr_Qd1QEg + 1,
    PieceEgOffAddr_Qd3QEg   =   PieceEgOffAddr_Qd2QEg + 1,
    PieceEgOffAddr_Qd4QEg   =   PieceEgOffAddr_Qd3QEg + 1,

    PieceEgOffAddr_PtFEg    =   PieceEgOffAddr_Qd4QEg + 1,
    PieceEgOffAddr_NtFEg    =   PieceEgOffAddr_PtFEg + 1,

    PieceEgOffAddr_PtHEg    =   PieceEgOffAddr_NtFEg + 1,
    PieceEgOffAddr_NtHEg    =   PieceEgOffAddr_PtHEg + 1,

    PieceEgOffAddr_end  =   PieceEgOffAddr_NtHEg + 1
} eEnergy_PieceEgOffAddr_TypeDef;//脉冲尾数偏移地址
#endif

#pragma pack(1)
typedef struct
{
    sEgShFile_TypeDef   PubData;
    sEgPiece_TypeDef  PriData;   //存放顺序参照 eEnergy_PieceEgOffAddr_TypeDef

    struct sEgPubPara_TypeDef
    {
        u8      PExpression;
        u8      PtQExpression;
        u8      NtQExpression;
        u16     PPlsDeltaE;         //
        u16     QPlsDeltaE;         //
        u16     HPlsDeltaE;         //

        u16     PUnit;          //脉冲个数为1时对应的电能
        u16     QUnit;          //
        u16     HUnit;          //

        u16     Crc;

        u8      fMinute;
        u8      EgUpFlag[PieceEgOffAddr_end];// 电能更新标志                    // 脉冲更新
    } PubPara;
} sEnergy_TypeDef;

typedef struct
{
    struct sEgMoneyPubData_TypeDef
    {
        sFsEgSh_TypeDef CurSurplusEg;             //当前剩余电量4个字节
        sFsEgSh_TypeDef CurOverdraftEg;           //当前透支电量4个字节

        sDF12           CurSurplusMoney;          //当前剩余金额6字节（扩充2个字节）
        sDF12           CurOverdraftMoney;        //当前透支金额6字节（扩充2个字节）

        sFsEgSh_TypeDef CurApplyEg;               //当前结算周期组合有功总累计用电量
        sFsEgSh_TypeDef Rmday1ApplyEg;            //上一结算周期组合有功总累计用电量
    } PubData;

    struct sEgMoneyPubDataCrc_TypeDef
    {
        u16     CurSurplusEg;
        u16     CurSurplusMoney;
        u16     CurApplyEg;
    } PubDataCrc;

    struct sEgMoneyLadderPara_TypeDef
    {
        u32             CurLadderPrice;             //当前阶梯电价值XXXX.XXXX 元/kWh
        sFsEgSh_TypeDef CurLadderVal;               //当前所处阶梯电量
        u8              CurLadder;                  //当前所处阶梯
        u16             Crc;
    } LadderPara;

    struct sEgMoneyRataPara_TypeDef
    {
        u32             CurRatePrice;               //当前费率电价值XXXX.XXXX 元/kWh当有阶梯电价时将阶梯电价进行累加
        u16             Crc;
    } RatePara;

    struct sEgMoneyPubPara_TypeDef
    {
        sDF10           MeterCT;                    //电流互感器变比
        sDF10           MeterPT;                    //电压互感器变比
        u16             Crc;
        u32             nALLBuyMoney;               // 总购电次数
        u8              tSubEsamMoney;              // ESAM进行扣减倒计时
    } PubPara;
} sEgMoney_TypeDef;

typedef struct
{
    sFsEgSh_HighTypeDef CurYearEgSh;                    //当前年结算用电量
    u16             CurYearEgShCrc;
    sFsEgSh_HighTypeDef CurMonthEgSh;                   //当前月度用电量
    u16             CurMonthEgShCrc;
    sFsEgSh_HighTypeDef CurDayEgSh;                     //当前结算日用电量
    u16             CurDayEgShCrc;
} sCurApplyEgSh_TypeDef;

#pragma pack()

extern  void fnEnergy_Init(void);
extern  void fnEnergy_Exec(void);
extern  void fnEnergy_DataInit(void);
extern  void fnEnergy_PluseParaInit(void);

extern  void fnEnergy_EsamInit(void);
extern  void fnEnergy_AllPEgCalc(u8 Mode, u8 *Buf);
extern  void fnEnergy_PtQEgCalc(u8 Mode, u8 *Buf);
extern  void fnEnergy_NtQEgCalc(u8 Mode, u8 *Buf);
extern  void fnEnergy_PulseCalc(void);
extern  void fnEnergy_DecMoney(u32 DecMoney, u8 Type);
extern  void fnEnergy_NtQEgcCalc(u8 Mode, u8 *Buf);
extern  void fnEnergy_PtQEgcCalc(u8 Mode, u8 *Buf);
extern  void fnEnergy_NtQEgbCalc(u8 Mode, u8 *Buf);
extern  void fnEnergy_PtQEgbCalc(u8 Mode, u8 *Buf);
extern  void fnEnergy_NtQEgaCalc(u8 Mode, u8 *Buf);
extern  void fnEnergy_PtQEgaCalc(u8 Mode, u8 *Buf);
extern  void fnEnergy_WriteRmMonth(void);
extern  void fnEnergy_CRCCheck(void);
extern  void fnEnergy_Change(u8 *Eg_InData, u8* Eg_OutData,     u8 FractionE);
extern  void fnEnergy_Mantissa(u8 *Eg_InData,   u8* Eg_OutData);
extern  u8 fnEnergy_Get(u16 OIA_B, u8 Feature, u8 FractionE, u8 *Buf);
extern void fnEnergy_WriteToE2(void);
extern void fnEnergy_PownDownWriteToE2(void);
extern void fnMoney_JudgeAlarm(void);
#endif // __DL645_ENERGY_H
