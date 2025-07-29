
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
} sDl645BkgrdFlagBit_TypeDef;       //后台状态标志字

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
    CLOCK_STA_OK                    = 0x00,   //00--无时钟故障
    CLOCK_STA_SETOVER               = 0x01,  //01--明文广播校时范围超出最大校时偏差
    CLOCK_STA_ERR                   = 0x10, //10--时钟发生倒退、格式错乱、上电时刻时间小于掉电时间或大于掉电时间1000天
    CLOCK_STA_SETOVER_ERR   = 0x11    //11--明文广播校时范围超出最大校时偏差，且时钟发生倒退、格式错乱、上电时刻时间小于掉电时间或大于掉电时间1000天
} eClock_ERRSTA_TypeDef;

//------------------------------------------------------------
typedef struct
{
    u16 SwCtlMode : 1;      //外置开关控制方式 0电平、1脉冲(贯宣)
    u16 NeedMode : 1;       //需量计算方式 0滑差、1区间
    u16 ClockBat : 1;       //时钟电池 0正常、1欠压
    u16 BackupBat : 1;      //停电抄表电池 0正常、1欠压
    u16 PPwDir : 1;         //有功功率方向 0正向、1反向
    u16 QPwDir : 1;         //无功功率方向 0正向、1反向
    u16 OutMulFun: 2;       //多功能输出00输出秒信号，01输出时段投切信号，10输出需量周期信号
    u16 ControlErr: 1;      //控制回路错误
    u16 EsamErr : 1;        //ESAM错误
    u16 Reserve2 : 2;
    u16 ProgramErr: 1;      //内部程序错误
    u16 MemoryErr: 1;       //存储器故障
    u16 Overdraft: 1;       //透支状态
    u16 ClockErr : 1;       //时钟错误
} sMtSta1Bit_TypeDef;   //电表运行状态字1

typedef struct
{
    u16 PPwaDir : 1;        //A相有功功率方向 0正向、1反向
    u16 PPwbDir : 1;        //B相有功功率方向 0正向、1反向
    u16 PPwcDir : 1;        //C相有功功率方向 0正向、1反向
    u16 Reserve1 : 1;       //
    u16 QPwaDir : 1;        //A相无功功率方向 0正向、1反向
    u16 QPwbDir : 1;        //B相无功功率方向 0正向、1反向
    u16 QPwcDir : 1;        //C相无功功率方向 0正向、1反向
    u16 Reserve2 : 9;
} sMtSta2Bit_TypeDef;   //电表运行状态字2

typedef struct
{
    u16 Reserve1 : 1;           //保留
    u16 PowMode : 2;        //供电方式 00主电源、01辅助电源、10电池供电
    u16 PrgEnable : 1;      //红外编程允许 0禁止、1允许
    u16 GateStatus : 1;     //继电器状态 0通、1断
    u16 Reserve2 : 1;       //保留
    u16 GateCmdStatus : 1;  //继电器命令状态 0通、1断
    u16 PreGateOff : 1;     //预跳闸报警状态 0无、1有

    u16 MtType : 2;         //电表类型 00非预付费表、01电量型预付费表、10电费型预付费表
    u16 TrmRemoteValid : 1; //终端身份认证
    u16 TrmSecValid : 1;        //终端安全认证
    u16 KeepEg : 1;         //保电状态
    u16 RemoteValid : 1;    //身份认证状态
    u16 LocalOpen : 1;      //本地开户
    u16 RemoteOpen : 1;     //远程开户
} sMtSta3Bit_TypeDef;   //电表运行状态字3(操作类)

typedef struct
{
    u16 LossVol : 1;        //失压 0无、1有
    u16 LackVol : 1;        //欠压 0无、1有
    u16 OverVol : 1;        //过压 0无、1有
    u16 LossCur : 1;        //失流 0无、1有
    u16 OverCur : 1;        //过流 0无、1有
    u16 OverPw : 1;         //过载 0无、1有
    u16 InSwim : 1;         //潮流反向 0无、1有
    u16 LossPha : 1;        //断相 0无、1有

    u16 BreakCur : 1;       //断流 0无、1有
    u16 Reserve1 : 5;
    u16 CTShort : 1;        // CT短路
    u16 CTOpen : 1;         // CT开路
} sMtSta4Bit_TypeDef;   //电表运行状态字4(A相故障类)

typedef struct
{
    u16 InPhaVol : 1;       //电压逆相序 0无、1有
    u16 InPhaCur : 1;       //电流逆相序 0无、1有
    u16 UnblVol : 1;        //电压不平衡 0无、1有
    u16 UnblCur : 1;        //电流不平衡 0无、1有
    u16 LossAux : 1;        //辅助电源失电 0无、1有
    u16 PowDn : 1;          //掉电 0无、1有
    u16 OverNeed : 1;       //超需量 0无、1有
    u16 OverPf : 1;         //总功率因数超下限 0无、1有

    u16 OverUnblCur : 1;    //电流严重不平衡 0无、1有
    u16 OpenCover : 1;      // 开表盖
    u16 OpenShell : 1;      // 开端钮
    u16 Reserve1 : 5;
} sMtSta7Bit_TypeDef;   //电表运行状态字7(合相故障类)

//------------------------------------------------------------
typedef struct
{
    u32 KeySta: 1;  //密钥状态(0公钥，1私钥)
    u32 EsamErr : 1;        //ESAM错误
    u32 Reserve1 : 1;
    u32 ClockBat : 1;       //时钟电池 0正常、1欠压
    u32 ProgramErr: 1;      //内部程序错误
    u32 MemoryErr: 1;       //存储器故障
    u32 ClockErr : 2;       //时钟故障
    u32 MagnetDisturb: 1;    //恒定磁场干扰
    u32 LossAux: 1;     //辅助电源失电 0无、1有
    u32 OpenCover : 1;      // 开表盖
    u32 OpenShell : 1;      // 开端钮
    u32 TrmSecValid : 1;    //终端身份认证
    u32 TrmRemoteValid : 1; //终端安全认证
    u32 BothCoreValid : 1;      //双芯认证状态(0失效，1有效)
    u32 RemoteValid : 1;    //主站安全认证状态(0失效，1有效)

    u32 EvtSetClock: 1; //普通校时
    u32 EvtBroadcastTime: 1; //广播校时
    u32 EvtOpenCover : 1;       // 开表盖
    u32 EvtOpenShell : 1;       // 开端钮
    u32 EvtControlPullOut: 1;       //管理模组插拔
    u32 EvtControlUpgrade : 1;      //管理模组升级
    u32 EvtMeterClear : 1;      //计量模组清零
    u32 Reserve2 : 8;
    u32 EvtMinFreeze : 1;       //分钟冻结
} sMtSysStaBit_TypeDef; //计量模组系统状态字

typedef struct
{
    u32 PPwDir : 1;     //总有功功率方向 0正向、1反向
    u32 PPwaDir : 1;        //A相有功功率方向 0正向、1反向
    u32 PPwbDir : 1;        //B相有功功率方向 0正向、1反向
    u32 PPwcDir : 1;        //C相有功功率方向 0正向、1反向
    u32 QPwDir : 1;     //总无功功率方向 0正向、1反向
    u32 QPwaDir : 1;        //A相无功功率方向 0正向、1反向
    u32 QPwbDir : 1;        //B相无功功率方向 0正向、1反向
    u32 QPwcDir : 1;        //C相无功功率方向 0正向、1反向
    u32 Reserve1 : 1;
    u32 Noplda: 1;          //A相潜动0代表处于起动，1代表处于潜动
    u32 Nopldb: 1;          //B相潜动
    u32 Nopldc: 1;          //C相潜动
    u32 InPhaVol : 1;       //电压逆相序 0无、1有
    u32 InPhaCur : 1;       //电流逆相序 0无、1有
    u32 Reserve2 : 2;
    u32 MeasureType : 2;    //01-单相，02-三相三线，03-三相四线
    u32 MeasureUn : 2;      //00-57.7V，01-100V，02-220V
    u32 Reserve3 : 12;
} sMeasureSysStaBit_TypeDef;

typedef struct
{
    u8  LowAlarm1 : 1;      // 低于报警金额1
    u8  LowAlarm2 : 1;      // 低于报警金额2
    u8  SurplusMoneyZero : 1;   // 剩余电量为0
    u8  Overdraft : 1;      // 高于透支金额
    u8  RemoteAlarm : 1;    // 远程报警状态
    u8  RemoteRelay : 1;    // 远程拉合闸
    u8  RemoteKeepEg : 1;   // 远程保电
    u8  GataOffAlarm : 1;   // 本地费控表拉闸报警
} sMoneyAlarm_TypeDef;

typedef struct
{
    u8  PHAV : 1;   //=1 时电压符号不显示，电压小于0.6Un
    u8  PHBV : 1;
    u8  PHCV : 1;
    u8  QLOSSVOL : 1;   //液晶屏全失压状态显示
    u8  PHAI : 1;  //=1时电流符号不显示，电流值小于5mA
    u8  PHBI : 1;
    u8  PHCI : 1;
    u8   : 1;
} sValCurStatusFlagBit_TypeDef;     //后台状态标志字

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
} sMtSta_TypeDef;       //电表运行状态字1

typedef union
{
    u32             SysSta;
    sMtSysStaBit_TypeDef    SysStaBit;
} sMtSysSta_TypeDef;        //计量模组系统状态字

typedef union
{
    u32             SysSta;
    sMeasureSysStaBit_TypeDef   SysStaBit;
} sMeasureSysSta_TypeDef;       //采样系统状态字

//=============================================
typedef struct
{
    struct sPubData_TypeDef
    {
        u8      Active;         //0=正常工作  1=修眠  2=上电恢复过程
        u8      PownUpingDelay; //系统上电需要延时，保证前端正确计算出U、I、P、Pf

        sBkgrdFlag_TypeDef  fChange;    //后台状态标志字

        sMtSta_TypeDef  MtSta;  //电表状态字
        sMtSysSta_TypeDef  MtSysSta;   //计量模组系统状态字
        sMeasureSysSta_TypeDef  MeasureSysSta;   //采样系统状态字

        u8      Fl;             //当前费率
        u8      nPOT;           //当前时段号
        u8      nDayPOT;        //当前使用的日时段表号
        u8      nTZone;         //当前使用的年时区号
        u8      nFl;            //当前费率数
        u8      Second;

        u8      CommStatus;
        u8      EventErr[7];    // dyf EventErr[6] 用作外部Flash的读写状态，正常/异常；EventErr[5]继承原功能，为内部存储和EE的读写状态
        u8      EventWake[6];
        sMoneyAlarm_TypeDef MoneySta;   // 剩余金额状态

        u16         SecondSysStamp;
        u8      RmYearFlag;                 // 年结算标志 0 年结算  1 月度结算
        u8      SetRmYearFlag;              // 年或月结算设置标志 bit0 设置了第1结算日 bit1 两套阶梯切换，且年节算日期发生变化

        u8      CipherKeyFlag;              // 密钥状态

        u16     OutStamp;                   // 有时段投切信号时做10MS延时
        u16     InsertCardFlag;             // 插卡状态字
        u8      BeepFlag;                   // 蜂鸣器启动标志 0a 读卡正常  0b 读卡异常
        u16     BeepTime;                   // 蜂鸣器响的时间
        u8      UpRunFileFlag;              // 更新运行信息文件
        u8      UpFlStatusFlag;             // 更新费率切换、阶梯切换等参数
        u8      CorrectionTime;             // 校表有效时间
        u8      CorrectionFlag;             // 校表命令有效标志
        u8      CheckMoneyFlag;             // 是否需判合闸允许金额
        u8      FactoryFlag;                // 表状态 55（厂内）或AA（厂外）
        u16     CheckZBStamp;               // 检测载波通讯口状态
        u8      CheckZBFlag;                // 检测到载波口有低电平，认为有载波模块插入 0 有 1 无
        u8      RUpdateMoneyFlag;           // 状态查询标志，不为0时代表已进行状态查询
        u8      UpDateTimeFlag;             //时间改变标志位
        u8      ZBRSTFlag;                  // 载波模块复位信号
        sValCurStatusFlag_TypeDef ValCurStatus; //电压电流实时状态标志

        u8      tEmuRstDely;                // 计量复位延时时间,3S后才进行电流判断
        u8      Broatcase_SfType;               //广播校时传输安全模式

        u8      tMngPlug;                   // 管理模组插拔延时时间
        u8      FUrmsRdFlg;                 // 基波电压读取标志

        u16     FrzWink_Delay;              //瞬时冻结延时执行时间 单位:秒
        u8      FrzMin_LineItem;            //分钟冻结曲线序号

        s16     Temperature;    //NNN.N 2
        s32     Temperature2;   //NNN.NNN 3
        u16     ClockBat;       //NN.NN 2
        u16     BackupBat;      //NN.NN 2
        u32     tWorkBat;           //---NNNN  时钟工作时间（分钟）

        s16     Tnal_Tmper[MAX_TERMINAL_TMP_NUM];   //端子温度，有符号数，0.1℃
        //s16   TnTmper_Wave[2][MAX_TERMINAL_TMP_NUM]; // 2分钟端子平均温度值 [0][4]:上1分钟端子平均温度  [1][4] 当前1分钟端子温度
        //s16   TnTmper_Chang[MAX_TERMINAL_TMP_NUM];    // 端子温度改变量
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
        u8      WireMode;   //=0 三相四线; =1 三相三线
        u8      InvalidByte1;     //为了对齐添加的无效字节
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
#define EVGEN_MARK_OVERPFA      ( (u32)1 << 0)    //A相功率因数超标
#define EVGEN_MARK_OVERPFB      ( (u32)1 << 1)    //B相功率因数超标
#define EVGEN_MARK_OVERPFC      ( (u32)1 << 2)    //C相功率因数超标

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
#define EVGEN_MARK_PSING            ( (u32)1 << 15) //有功功率方向为负，只判断状态，无事件记录
#define EVGEN_MARK_QSING            ( (u32)1 << 16) //无功功率方向为负，只判断状态，无事件记录
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

//------主动上报状态字 0x2015-------------------
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
