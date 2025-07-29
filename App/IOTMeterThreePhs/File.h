
#ifndef _FILE_H
#define _FILE_H

#ifdef   _FILE_GLOBALS
#define  FILE_EXT
#else
#define  FILE_EXT  extern
#endif

#pragma pack(1)

// ---当前电能文件
typedef struct
{
    //-------------
    sFsEgSh_HighTypeDef PtPEgSh[1];      //正向有功电能
    u16             PtPEgShCrc;
    sFsEgSh_HighTypeDef NtPEgSh[1];      //反向有功电能
    u16             NtPEgShCrc;

    sFsEgSh_HighTypeDef Qd1QEgSh[1];        //一象限无功电能示值
    u16             Qd1QEgShCrc;
    sFsEgSh_HighTypeDef Qd2QEgSh[1];        //四象限无功电能示值
    u16             Qd2QEgShCrc;
    sFsEgSh_HighTypeDef Qd3QEgSh[1];        //二象限无功电能示值
    u16             Qd3QEgShCrc;
    sFsEgSh_HighTypeDef Qd4QEgSh[1];        //三象限无功电能示值
    u16             Qd4QEgShCrc;

    //-------------
    sFsEgSh_HighTypeDef PtPEgSha;                       //A相正向有功电能示值
    u16             PtPEgShaCrc;
    sFsEgSh_HighTypeDef NtPEgSha;                       //A相反向有功电能示值
    u16             NtPEgShaCrc;

    sFsEgSh_HighTypeDef Qd1QEgSha;                      //A相一象限无功电能示值
    u16             Qd1QEgShaCrc;
    sFsEgSh_HighTypeDef Qd2QEgSha;                      //A相一象限无功电能示值
    u16             Qd2QEgShaCrc;
    sFsEgSh_HighTypeDef Qd3QEgSha;                      //A相一象限无功电能示值
    u16             Qd3QEgShaCrc;
    sFsEgSh_HighTypeDef Qd4QEgSha;                      //A相一象限无功电能示值
    u16             Qd4QEgShaCrc;

    //-------------
    sFsEgSh_HighTypeDef PtPEgShb;                       //B相正向有功电能示值
    u16             PtPEgShbCrc;
    sFsEgSh_HighTypeDef NtPEgShb;                       //B相反向有功电能示值
    u16             NtPEgShbCrc;

    sFsEgSh_HighTypeDef Qd1QEgShb;                      //B相一象限无功电能示值
    u16             Qd1QEgShbCrc;
    sFsEgSh_HighTypeDef Qd2QEgShb;                      //B相一象限无功电能示值
    u16             Qd2QEgShbCrc;
    sFsEgSh_HighTypeDef Qd3QEgShb;                      //B相一象限无功电能示值
    u16             Qd3QEgShbCrc;
    sFsEgSh_HighTypeDef Qd4QEgShb;                      //B相一象限无功电能示值
    u16             Qd4QEgShbCrc;

    //-------------
    sFsEgSh_HighTypeDef PtPEgShc;                       //C相正向有功电能示值
    u16             PtPEgShcCrc;
    sFsEgSh_HighTypeDef NtPEgShc;                       //C相反向有功电能示值
    u16             NtPEgShcCrc;

    sFsEgSh_HighTypeDef Qd1QEgShc;                      //C相一象限无功电能示值
    u16             Qd1QEgShcCrc;
    sFsEgSh_HighTypeDef Qd2QEgShc;                      //C相一象限无功电能示值
    u16             Qd2QEgShcCrc;
    sFsEgSh_HighTypeDef Qd3QEgShc;                      //C相一象限无功电能示值
    u16             Qd3QEgShcCrc;
    sFsEgSh_HighTypeDef Qd4QEgShc;                      //C相一象限无功电能示值
    u16             Qd4QEgShcCrc;

    sFsEgSh_HighTypeDef PtFEgSh[1];         //正向基波波总电能
    u16             PtFEgShCrc;

    sFsEgSh_HighTypeDef NtFEgSh[1];         // 反向基波总电能
    u16             NtFEgShCrc;

    sFsEgSh_HighTypeDef PtHEgSh[1];         //正向谐波总电能
    u16             PtHEgShCrc;

    sFsEgSh_HighTypeDef NtHEgSh[1];         // 反向谐波总电能
    u16             NtHEgShCrc;

    //-------------
} sEgShFile_TypeDef;

// 用电量文件
typedef struct
{
    sFsEgSh_TypeDef CurYearEgSh;                    //当前年结算用电量
    u16             CurYearEgShCrc;
    sFsEgSh_TypeDef CurMonthEgSh;                   //当前月度用电量
    u16             CurMonthEgShCrc;
    sFsEgSh_TypeDef CurDayEgSh;                     //当前结算日用电量
    u16             CurDayEgShCrc;
} sDl645CurApplyEgShFile_TypeDef;

typedef struct
{
    sDF29           RmTime;                         // 上1次年结算日结算时间
    sFsEgSh_TypeDef RmApplyEg;                      // 上1年结算周期组合有功总累计用电量
} sDl645YearApplyEgShFile_TypeDef;

typedef struct
{
    sFsEgSh_TypeDef                 RmMonthEgSh;     // 上1月度有功总累计用电量
    sFsEgSh_TypeDef                 RmDayEgSh;       // 上1结算有功总累计用电量
    sDl645YearApplyEgShFile_TypeDef RmYearEgSh[4];   // 上4次年结算数据
} sDl645RmApplyEgShFile_TypeDef;

//---购电量文件-------
typedef struct
{
    u8  nBuy;
    u32 Remain;
} sDl645MoneyFile_TypeDef;

typedef struct
{
    sFsEgSh_TypeDef PtPEgSh;                        //正向有功电能示值
    sFsEgSh_TypeDef NtPEgSh;                        //反向有功电能示值
    sFsEgSh_TypeDef PtQEgSh;                        //正向无功电能示值
    sFsEgSh_TypeDef NtQEgSh;                        //反向无功电能示值
} sDl645CurvePQEgFile_TypeDef;

typedef struct
{
    sFsEgSh_TypeDef Qd1QEgSh;                       //一象限无功电能示值
    sFsEgSh_TypeDef Qd2QEgSh;                       //四象限无功电能示值
    sFsEgSh_TypeDef Qd3QEgSh;                       //二象限无功电能示值
    sFsEgSh_TypeDef Qd4QEgSh;                       //三象限无功电能示值
} sDl645CurveQdEgFile_TypeDef;

typedef struct
{
    sDF09   PNeed;
    sDF09   QNeed;
} sDl645CurveNeedFile_TypeDef;

//---事件记录-------
typedef struct
{
    u32   OAD;
    u8    len;      //数据存储长度
    u16 OffPos;     //在每条记录中的偏移地址
} sContextList_TypeDef;   //关联对象属性表

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[24];
} sCList24_TypeDef;

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[14];
} sCList14_TypeDef;
typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[13];
} sCList13_TypeDef;

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[12];
} sCList12_TypeDef;

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[11];
} sCList11_TypeDef;   //关联对象属性表
typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[9];
} sCList9_TypeDef;
typedef struct
{
    u8       num;           //关联对象属性表OAD个数
    u16    reclen;      //关联对象属性表对应事件记录存储长度
    sContextList_TypeDef     Clist[8];
} sCList8_TypeDef;   //关联对象属性表

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[7];
} sCList7_TypeDef;

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[6];
} sCList6_TypeDef;   //关联对象属性表

typedef struct
{
    u8       num;           //关联对象属性表OAD个数
    u16    reclen;      //关联对象属性表对应事件记录存储长度
    sContextList_TypeDef     Clist[5];
} sCList5_TypeDef;   //关联对象属性表

typedef struct
{
    u8       num;           //关联对象属性表OAD个数
    u16    reclen;      //关联对象属性表对应事件记录存储长度
    sContextList_TypeDef     Clist[4];
} sCList4_TypeDef;   //关联对象属性表

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[3];
} sCList3_TypeDef;   //关联对象属性表

typedef struct
{
    u8       num;           //关联对象属性表OAD个数
    u16    reclen;      //关联对象属性表对应事件记录存储长度
    sContextList_TypeDef     Clist[2];
} sCList2_TypeDef;   //关联对象属性表

typedef struct
{
    u8       num;           //关联对象属性表OAD个数
    u16    reclen;      //关联对象属性表对应事件记录存储长度
    sContextList_TypeDef     Clist[1];
} sCList1_TypeDef;   //关联对象属性表

typedef struct
{
    u8       num;
    u16    reclen;
} sCListNULL_TypeDef;   //关联对象属性表

typedef struct
{
    u32                 EventSumCnt;   //事件发生次数 累计次数
    sDate_time_s_TypeDef    EventStartTime;   //事件发生时间
    sDate_time_s_TypeDef    EventEndTime;   //时间结束时间
    u16                 EventCnt;   //当前记录数，最大值等于最大记录数
    u32             EventTime;      //时间发生累计时间
    u8      EventRptStatus; //事件上报状态
    //  u8      EventReportMode;    //事件上报模式
    u8      nTarf;              // 费率数---管理模组升级
} sEvtRcdHead_TypeDef;

typedef struct
{
    //---失压判断---//
    u16 LossVolUTouchUp;    //电压触发上限 NNN.N(78%Un)
    u16 LossVolUResumeDn;   //电压恢复下限 NNN.N(85%Un)
    s32 LossVolITouchDn;    //电流触发下限 NN.NNNN(0.5%Ib)
    u8      tLossVol;           //持续时间 s (60S)
} sEvtCfgPara_LossVol_TypeDef;

typedef struct
{
    //---欠压判断---//
    u16 LackVolUTouchUp;    //电压触发上限 NNN.N
    u8      tLackVol;           //持续时间 s (60S)
} sEvtCfgPara_LackVol_TypeDef;

typedef struct
{
    //---过压判断---//
    u16 OverUpVolUTouchDn;  //电压触发下限 NNN.N
    u8      tOverUpVol;         //持续时间 s (60S)
} sEvtCfgPara_OverVol_TypeDef;

typedef struct
{
    //---断相判断---//
    u16     LossPhaUTouchUp;    //电压触发上限 NNN.N
    s32     LossPhaITouchUp;    //电流触发上限 NN.NNNN(启动电流)
    u8      tLossPha;           //持续时间 s (60S)
} sEvtCfgPara_LossPha_TypeDef;

typedef struct
{
    //---失流判断---//
    u16 LossCurUTouchDn;    //电压触发下限 +-NNN.N (60%Un)
    s32 LossCurITouchUp;    //电流触发上限 +-NN.NNNN(0.5%Ib)
    s32 LossCurITouchDn;    //电流触发下限 +-NN.NNNN(5%Ib)
    u8      tLossCur;           //持续时间 s (60S)
} sEvtCfgPara_LossCur_TypeDef;

typedef struct
{
    //---过流判断---//
    s32 OverUpCurITouchUp;  //电流触发 下限 NN.NNNN(%Ib) sDF23修改sDF07
    u8      tOverUpCur;         //持续时间 s (60S)
} sEvtCfgPara_OverCur_TypeDef;

typedef struct
{
    //---断流判断---//
    u16 BreakCurUTouchDn;   //电压触发下限 +-NNN.N(60%Un)
    s32 BreakCurITouchUp;   //电流触发上限 +-NN.NNNN(启动电流)
    u8      tBreakCur;          //持续时间 s (60S)
} sEvtCfgPara_BreakCur_TypeDef;

typedef struct
{
    //---功率反向--//
    s32 InSwimPwTouchDn;    //功率触发下限 NN.NNNN
    u8      tInSwim;            //持续时间 s (60S)
} sEvtCfgPara_InSwimPw_TypeDef;

typedef struct
{
    //---过载判断---//
    s32 OverPwTouchDn;      //功率触发下限 NN.NNNN
    u8      tOverPw;            //持续时间 s (60S)
} sEvtCfgPara_OverPw_TypeDef;

typedef struct
{
    u32 OverNeedTouchDn;    //量触发下限 NN.NNNN
    u8      tOverNeed;          //持续时间 s (60S)
} sEvtCfgPara_OverNeed_TypeDef;

typedef struct
{
    //---零线电流异常---//
    s32 NLineErrCurITouchDn;    //电流触发下限  double-long（单位：A，换算：-4）
    u16 NLineErrTouch;          //零线电流不平衡限值  long- unsigned（单位：%，换算：-2）
    u8      tNLineErr;         //延时判定时间        unsigned（单位：s，换算：0）
} sEvtCfgPara_NLineErr_TypeDef;
/*
typedef struct {
    //---超总功率因数判断---//
    s16 OverPfTouchDn;      //有功需量触发下限 N.NNN
    u8      tOverPf;            //持续时间 s (60S)
} sEvtCfgPara_OverPf_TypeDef;
*/
//----超总功率因数,不平衡事件 配置参数格式一样-----------
typedef struct
{
    s16 INT16Touch;     //触发上限 xx.xx%
    u8  tDly;           //持续时间 s (60S)
} sEvtCfgPara_INT16Touch_TypeDef;

typedef struct
{
    u8      tDly;           //持续延时时间 s (60S)
} sEvtCfgPara_TimeDly_TypeDef;

typedef struct
{
    //-------class24----

    sEvtCfgPara_OverCur_TypeDef VrCur;
    sEvtCfgPara_TimeDly_TypeDef PowDn;

    sEvtCfgPara_TimeDly_TypeDef CkErr;
    sEvtCfgPara_TimeDly_TypeDef MrErr;
    sEvtCfgPara_TimeDly_TypeDef CPLC;
    sEvtCfgPara_NLineErr_TypeDef    NLineErr;  //零线电流异常

    u16 Crc;
} sTrim_TypeDef;

//---电压合格率统计文件-------
typedef struct              //
{
    u32 tInspectU;      //电压监测时间
    u16 EligRateU;      //电压合格率
    u16 OverRateU;      //电压超限率
    u32 tOverUpU;       //电压超上限时间
    u32 tOverDnU;       //电压超下限时间
} sUEligStat_TypeDef;       //MONTHSTAT_TYPE;

typedef struct              //
{
    sDF27   tBatWork;       //电池工作时间
    sDF27   tWork;          //终端工作时间
} sMiscStat_TypeDef;

typedef struct
{
    sUEligStat_TypeDef  UElig_Day[3];  //A、B、C
    sUEligStat_TypeDef  UElig_Month[3];
    sMiscStat_TypeDef       MiscStat;
} sStatFile_TypeDef;

typedef struct
{
    u16 UUp;                    //电压上限
    u16 UDn;                    //电压下限
    u16     UCheckUp;               //电压考核上限 NNN.N
    u16     UCheckDn;               //电压考核下限 NNN.N

    u16     Crc;
} sVolYieldPara_TypeDef;

typedef struct
{
    u16 RTCDota0;       /*"2次曲线初始频率偏差"*/
    u16 CurveMode;
    u16    DATA0;       /*"4次或者3次曲线初始频率偏差"*/
    u16    XT1;     /*"晶振温度曲线顶点温度"*/
    u16    ALPHA;       /*"晶振一次温度系数"*/
    u16    BETA;        /*"晶振二次温度系数"*/
    u16    GAMMA;       /*"晶振三次温度系数"*/
    u16    ZETA;        /*"晶振四次温度系数"*/

    u16     Crc;
} sRTCParaE2_TypeDef;

typedef struct
{
    sDF15           Time;                //购电日期
    sDF08           nALLBuyEg;           //购电后总购电次数
    sFsEgSh_TypeDef BuyEg;               //购电量
    sFsEgSh_TypeDef FrSurplusEg;         //购电前剩余电量
    sFsEgSh_TypeDef AfSurplusEg;         //购电后剩余电量
    sFsEgSh_TypeDef AllBuyEg;            //购电后累计购电量
} sBuyEg_TypeDef;           //购电事件记录（购电量）

typedef struct
{
    sDF15           Time;                   //购电日期
    sDF08           nALLBuyMoney;           //购电后总购电次数
    u32             BuyMoney;               //购电金额
    u32             FrSurplusMoney;         //购电前剩余金额
    u32             AfSurplusMoney;         //购电后剩余金额
    u32             AllBuyMoney;            //购电后累计购金额
} sBuyMoney_TypeDef;        //购电事件记录（购金额）

//-------冻结------------
//-----------------------
typedef struct
{
    u16 Cycle;      //周期
    u32   OAD;
    u32 Depth;      //深度
    u8    len;      //数据存储长度
    u16 OffPos;     //在每条记录中的偏移地址
} sFrzCtxList_TypeDef;   //关联对象属性表

typedef struct
{
    u8  num;            //关联对象属性表OAD个数
    u16   reclen;       //关联对象属性表对应事件记录存储长度
    sFrzCtxList_TypeDef Clist[3];
} sFrzWinkList_TypeDef;   //关联对象属性表

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[15];
} sFrzMinList_TypeDef;   //

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[2];
} sFrzHourList_TypeDef;   //

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[3];
} sFrzDayList_TypeDef;   //关联对象属性表

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[4];
} sFrzRmDayList_TypeDef;   //

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[3];
} sFrzMonthList_TypeDef;   //

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[1];
} sFrzLadderList_TypeDef;   //

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[3];
} sFrzSwList_TypeDef;   //切换冻结

typedef struct
{
    u8  num;            //
    u16   reclen;       //关联对象属性表对应事件记录存储长度
    sFrzCtxList_TypeDef Clist[2];
} sFrzStdList_TypeDef;   //标准记录单元

typedef struct
{
    u32                 FrzAddrEnd;   //冻结的结束地址(1~冻结深度)
    sDate_time_s_TypeDef    FrzTime;   //冻结时间
    u32                 FrzAddrStart;   //冻结的起始地址(0~(冻结深度-1))
} sFrzRcdHead_TypeDef;

typedef struct
{
    u8  OADnum;         //
    u16 RecLen;     //单条事件记录长度
    u32 LineOffAdder;       //曲线事件记录地址
    u32 LineRecLen;         //一条曲线事件记录总长度
    u16 Cycle;      //周期
    u32 Depth;      //深度
} sFrzMinLinePara_TypeDef;

typedef struct
{
    sFrzMinLinePara_TypeDef  LinePara;
    sFrzRcdHead_TypeDef      RecHead;
} sFrzMinHead_TypeDef;

//---中间变量文件-------
typedef struct
{
    struct sCellEg_TypeDef
    {
        u16 PulseE[12]; //{PNeed,QNeed,PsNeed},{PNeeda,QNeeda,PsNeeda},{PNeedb,QNeedb,PsNeedb},{PNeedc,QNeedc,PsNeedc}
    } CellEg[60];
} sNeedInter_TypeDef;

typedef struct
{
    u32 lStatus[2]; //nStatus:   实时状态
    //0:过流
    //1:掉电
    //2:计量芯片异常
    //3:零线电流异常
    u32 Status[2];  //同  lStatus   判断延时时间结束后状态

    u8  tOverCura;
    u8   tPowDn;
    u8  tMeasureErr;
    u8  tNLineErr;
    //---------------------
} sEvStatusInter_TypeDef;   //STATUSINTER_TYPE;

typedef struct
{
    u32 tTotal;          //(hyg) BCD码 电表工作分钟累计
    u32 tVolPass;        //(hyg) BCD码 电压合格分钟累计

    u32 Cos;            //(hyg) BCD码 总功率因数累计
    u32 ACos;           //(hyg) BCD码 A相功率因数累计
    u32 BCos;           //(hyg) BCD码 B相功率因数累计
    u32 CCos;           //(hyg) BCD码 C相功率因数累计
} sStatInter_TypeDef;   //暂时保留

typedef struct
{
    u8      nPswRetry[2];       //密码重试次数
    u16     tPswFailClose[2];   //密码闭锁时间
    u16     tPrgKeyValid;
    u16     tPrgKeyLock;
    u8      nMacErr;        //远程MAC效验失败

    u8      SecretIndex[3]; //最近的密引
    u8      Labour[17];     //实验室模型用数据

    u32     tLinkDly[4];    //应用连接超时剩余时间 单位:秒
} sSecretInter_TypeDef;//SECRETINTER_TYPE;

typedef struct
{
    u8   MeterShellStamp;   //当表壳（上盖）由开转为合时，该变量作为延时累计
    u8   JunctionBoxStamp;  //当接线盒（尾盖）由开转为合时，该变量作为延时累计
    u8   ProgramBoxStamp;   //当编程盒（编程盒盖）由开转为合时，该变量作为延时累计
    u8   Reserval;
} sOpenCoverInter_TypeDef;      //COVEROPENINTER_TYPE;

typedef struct                  //用于电能脉冲尾数
{
    u16 PieceEg[28];
    u16 Crc;
} sEgPiece_TypeDef;             //sEgPiece_TypeDef;

typedef struct
{
    sDF01   PowOn;              //来电时间
    sDF01   PowDn;              //停电时间（每秒记录一次以便来电判断）

    u8      fTZoneSw;           //时区表切换标志,D7 = 0未切换 =1已切换，D0=0当前使用第一套参数 =1当前使用第二套参数
    u8      fPOTSw;             //时段表切换标志,D7 = 0未切换 =1已切换，D0=0当前使用第一套参数 =1当前使用第二套参数
    u8      fRatePriceSw;       //费率电价表切换标志,D7 = 0未切换 =1已切换，D0=0当前使用第一套参数 =1当前使用第二套参数
    u8      fLadderSw;          //阶梯电价表切换标志,D7 = 0未切换 =1已切换，D0=0当前使用第一套参数 =1当前使用第二套参数

    u8      CurveStarYear;      //负荷曲线开始时间保存年
    u8      flagCurve;          //曲线记录已开始标志 18
    u16     nCurve;             //负荷记录发生次数
} sMisc_TypeDef;                //

typedef struct                  //
{
    sFsEgSh_TypeDef CurSurplusEg;             //当前剩余电量4个字节
    sFsEgSh_TypeDef CurOverdraftEg;           //当前透支电量4个字节

    sDF12           CurSurplusMoney;          //当前剩余金额6字节（扩充2个字节）
    sDF12           CurOverdraftMoney;        //当前透支金额6字节（扩充2个字节）

    sFsEgSh_TypeDef CurApplyEg;               //当前结算周期组合有功总累计用电量
    sFsEgSh_TypeDef Rmday1ApplyEg;            //上一结算周期组合有功总累计用电量
    u16             CurSurplusEgCrc;          //当前剩余及透支电量的CRC效验
    u16             CurSurplusMoneyCrc;       //当前剩余及透支金额的CRC效验
    u16             CurApplyEgCrc;            //当前及上1结算组合累计用电量的CRC效验
    u32             nAllBuyMoney;             // 总购电次数
    u32             AllBuyMoney;              // 总购电金额
} sCurEgMoney_TypeDef;                            //用于费控，电量，金额计算

typedef struct
{
    sCommSize_TypeDef   Comm[4];  //4个通道:485B,IR , PLC, 485B
} sLinkSize_TypeDef;    //建立应用连接协商尺寸

typedef struct
{
    sNeedInter_TypeDef      Need;
    sEvStatusInter_TypeDef  EvStatus;
    sStatInter_TypeDef      Stat;
    sSecretInter_TypeDef    Secret;
    sOpenCoverInter_TypeDef OpenCover;
    sMisc_TypeDef           Misc;
    sCurEgMoney_TypeDef        CurEgMoney;          //计费用中间变量
    sLinkSize_TypeDef       MLinkSize;      //主站
    sLinkSize_TypeDef       TLinkSize;      //终端
    u16   Crc;
} sDl645InterTmpFile_TypeDef;

//---费率参数文件-------
typedef struct
{
    sDate_time_s_TypeDef                    TimeZoneSw;             //两套时区表切换时间
    sTimeZoneTable_TypeDef  TimeZoneTable[2][14];   //时区表
    u16   Crc;
} sTimeZonePara_TypeDef;

typedef struct
{
    sDate_time_s_TypeDef                    POTTableSw;             //两套日时段表切换时间
    sPOTTable_TypeDef       POTTable[2][8][14];     //日时段表
    u16   Crc;
} sPOTTablePara_TypeDef;

typedef struct
{
    sDate_time_s_TypeDef    EgPriceSw;       //两套费率电价切换时间
    sDF13   RatePrice[2][MAX_FL + 1];//两套费率电价表
    u16   Crc;
} sRatePricePara_TypeDef;

typedef struct
{
    sDate_time_s_TypeDef    EgPriceSw;        //两套阶梯电价切换时间

    sDF13   LadderVal[2][MAX_LADDER];//两套阶梯值
    sDF13   LadderPrice[2][MAX_LADDER];//两套阶梯电价值
    sDF28   RmYear[2][4];                     // 2套阶梯年结算日
    u16   Crc;
} sLadderPara_TypeDef;

typedef struct
{
    sDF11   WarnMoney1;      //报警金额1限值
    sDF11   WarnMoney2;      //报警金额2限值
    sDF11   OverdraftMoney;  //透支金额限值
    sDF11   RegrateMoney;    //囤积金额限值
    sDF11   GateOnAllowMoney;     //合闸允许金额限值
    u16    Crc;
} sChargMoneyPara_TypeDef;

//---通用参数文件-------
typedef struct
{
    u8      NeedMode;   //需量模式
    u8      NeedCyc;    //需量周期
    u8      NeedSlip;   //滑差周期

    sDF08   PlsWidth;   //校表脉冲宽度
    u8      nWave;      //谐波分析次数
    u16     BroadcastTime_ParaMin;
    u16     BroadcastTime_ParaMax;
    u8          WirelessSignal;     //无线信号强弱指示      40
    u16     Crc;
} sDocment_TypeDef;

typedef struct
{
    u8      ComAddr[6];
    u8      Ir1Style;   //调制型红外口波特率特征字 IR
    u8      Ir2Style;   //接触型红外口波特率特征字
    u8      Com1Style;  //通信口1波特率特征字  4851
    u8      Com2Style;  //通信口2波特率特征字  4852
    u8      Com3Style;  //通信口3波特率特征字  ZB
    u16     Crc;
} sComPara_TypeDef;

typedef struct
{
    u8      AllOnDispTime;  // 上电全显时间5-30S设置默认5S
    u16     Key_LightTime;  //背光点亮时间 1
    u16     Chk_LightTime;  //显示查看背光点亮时间  3
    u16     Key_PwrOffTime; //无电按键屏幕驻留最大时间   5
    u8      DecimalEg;  //显示电能小数位数 7
    u8      DecimalPw;  //显示功率小数位数 8
    u8      LCD_WordMn;  //液晶字样意义①① 9
    u8      nCycDisp;   //循显屏数  10
    u8      nKeyDisp;   //键显屏数  11
    u16     AutoDispTime;   //显示时间 自动循环显示    12
    u16     KeyDispTime;    //显示时间 按键显示    13
} sDispPubPara_TypeDef;

typedef struct
{
    sDispPubPara_TypeDef    PubPara;

    sDispItem_TypeDef       CycDispItem[MAX_CYCDISP];
    sDispItem_TypeDef       KeyDispItem[MAX_KEYDISP];
    u16 Crc;
} sDispPara_TypeDef;

typedef struct
{
    u8  nCipherKey;             // 密钥总条数
    u8  WriteStarFlag;          // 密钥写启动标志每位对应1条密钥，位置1证明密钥已写入EEPROM中
    u32 CipherKeyWriteFlag;     // 密钥写标志
    u32 CipherKeyFlag;          // 密钥状态字
    u8  CipherKey[MAX_CipherKey][32];   // 密钥信息存储
    u32 nCipherKeyEE;           // EEPROM中存储的密钥条数
    u32 OpCode;                 // 密钥操作者代码
} sCipherKeyPara_TypeDef;

typedef struct
{
    sDF26   Ga;     //A相电导系数
    sDF26   Ba;     //A相电纳系数
    sDF26   Ra;     //A相电阻系数
    sDF26   Xa;     //A相电抗系数

    sDF26   Gb;     //B相电导系数
    sDF26   Bb;     //B相电纳系数
    sDF26   Rb;     //B相电阻系数
    sDF26   Xb;     //B相电抗系数

    sDF26   Gc;     //C相电导系数
    sDF26   Bc;     //C相电纳系数
    sDF26   Rc;     //C相电阻系数
    sDF26   Xc;     //C相电抗系数
} sWastePara_TypeDef;

typedef struct
{
    u16 Style1;
    u16 Trigger1;

    u16 Style2;
    u16 Trigger2;

    u16 Style3;
    u16 Trigger3;

    u16 Style4;
    u16 Trigger4;

    u16 Style5;
    u16 Trigger5;

    u16 Style6;
    u16 Trigger6;

    u16  RelaysOutAlarm[5];
    u16  LightAlarm[5];
    u16  SoundAlarm[5];
} sOutputPara_TypeDef;

typedef enum
{
    //项编号
    //---class7---
    FileItemInfoNum_Evt_PowDn             = 0,      //掉电
    FileItemInfoNum_Evt_Clr                   = 1,      //电表清零
    FileItemInfoNum_Evt_SetClock          = 2,      //校时
    FileItemInfoNum_Evt_OpenCover     = 3,      //开表盖
    FileItemInfoNum_Evt_OpenTail      = 4,      //开端盖
    FileItemInfoNum_Evt_PrgSetPsw       =   5,    //密钥更新
    FileItemInfoNum_Evt_BroadcastTime   =   6,    //广播校时
    FileItemInfoNum_Evt_MngPlug       = 7,      //管理模组插拔
    FileItemInfoNum_Evt_MngUpdate     = 8,      //管理模组升级

    FileItemInfoNum_Evt_Max         =   9,

    //----以下事件记录单相表均不支持,为程序兼容而定义---------
    //  FileItemInfoNum_Evt_LossVol         =   ( ITEM_EVT_MAX + 1 ) ,     //失压
    //  FileItemInfoNum_Evt_LackVol         =   ( ITEM_EVT_MAX + 2 ) ,     //欠压
    //  FileItemInfoNum_Evt_OverVol         =   ( ITEM_EVT_MAX + 3 ) ,     //过压
    //  FileItemInfoNum_Evt_LossPha         =   ( ITEM_EVT_MAX + 4 ) ,     //断相
    //  FileItemInfoNum_Evt_LossCur         =   ( ITEM_EVT_MAX + 5 ) ,     //失流
    //  FileItemInfoNum_Evt_BreakCur        =   ( ITEM_EVT_MAX + 6 ) ,     //断流
    //  FileItemInfoNum_Evt_InSwimPw        =   ( ITEM_EVT_MAX + 7 ) ,     //功率反向
    //  FileItemInfoNum_Evt_OverPw          =   ( ITEM_EVT_MAX + 8 ) ,      //过载
    //  FileItemInfoNum_Evt_QtOverNeed  =   ( ITEM_EVT_MAX + 9 ) ,     //无功需量超限
    //  FileItemInfoNum_Evt_OverPf          =   ( ITEM_EVT_MAX + 10 ) ,   //功率因数超限
    //  FileItemInfoNum_Evt_PtOverNeed  =   ( ITEM_EVT_MAX + 11 ) ,   //正向有功超限
    //  FileItemInfoNum_Evt_NtOverNeed  =   ( ITEM_EVT_MAX + 12 ) ,   //反向有功超限
    //  FileItemInfoNum_Evt_QLossVol        =   ( ITEM_EVT_MAX + 13 ) ,   //全失压
    //  FileItemInfoNum_Evt_LossAux         =   ( ITEM_EVT_MAX + 14 ) ,   //辅助电源
    //  FileItemInfoNum_Evt_InPhaVol        =   ( ITEM_EVT_MAX + 15 ) ,   //电压逆向序
    //  FileItemInfoNum_Evt_InPhaCur        =   ( ITEM_EVT_MAX + 16 ) ,   //电流逆向序
    //  FileItemInfoNum_Evt_NeedClr         =   ( ITEM_EVT_MAX + 17 ) ,   //需量清零
    //  FileItemInfoNum_Evt_OpenTail        =   ( ITEM_EVT_MAX + 18 ) ,   //开尾盖
    //  FileItemInfoNum_Evt_UnblVol         =   ( ITEM_EVT_MAX + 19 ) ,   //电压不平衡
    //  FileItemInfoNum_Evt_UnblCur         =   ( ITEM_EVT_MAX + 20 ) ,   //电流不平衡
    //  FileItemInfoNum_Evt_PrgQ                =   ( ITEM_EVT_MAX + 21 ) ,   //无功组合特征字编程
    //  FileItemInfoNum_Evt_MagnetDisturb=( ITEM_EVT_MAX + 22 ) , //磁场干扰
    //  FileItemInfoNum_Evt_OverUnblCur     =   ( ITEM_EVT_MAX + 23 )   , //电流严重不平衡
} eFileItemInfoNum_Evt_TypeDef;   //事件记录枚举，关联对象属性表，配置参数，事件记录排列顺序需一致

#define ITEM_EVT_MAX    FileItemInfoNum_Evt_Max

typedef struct
{
    u8  OADNum;  //
    u32 OAD[ITEM_EVT_MAX];      //主动上报OAD
} sReportList_TypeDef;

typedef struct
{
    u8  AtiveAllow; //主动上报总开关，1=开启,0=关闭
    u8  FollowAllow;        //跟随上报总开关,1=开启,0=关闭
    u8  RptFlagHappen[7];       //上报标识发生上报,bit使用,排列顺序按照事件记录eFileItemInfoNum_Evt_TypeDef顺序
    u8  RptFlagEnd[7];      //上报标识结束上报,bit使用,排列顺序按照事件记录eFileItemInfoNum_Evt_TypeDef顺序
    u8  RptMode[7];         //上报方式0=主动上报;  1=跟随上报,bit使用

    u8  RptStatusAllow;     //上报状态字上报方式 0x20150500,0=主动上报，1=跟随上报
    u32  RptStatusMode;    //上报状态字模式字0x20150400
    u8  RptChannel[3];   //9=载波,1=485_1 , 2=485_2

    u16 Crc;
} sEvtRptPara_TypeDef;  //主动上报参数

typedef struct
{
    u32  RptStuZB;          // 主动上报状态字
    u32  RptStuZBBack;

    u32  RptStu485;         //
    u32  RptStu485Back;

    u32  RptStu4852;            //
    u32  RptStu4852Back;
} sEvtRptStatus_TypeDef;

typedef struct
{
    sEvtRptPara_TypeDef  RptPara;

    sEvtRptStatus_TypeDef  RptStatus; // 主动上报状态字

    sReportList_TypeDef   RptListZB_A;  //载波主动上报列表,存E2
    sReportList_TypeDef   RptListZB_F;  //载波跟随上报列表，存E2

    sReportList_TypeDef   RptList485_F; //485只支持跟随上报，跟随上报列表，存E2
    sReportList_TypeDef   RptList4852_F; //485只支持跟随上报，跟随上报列表，存E2
    u8    RptPowerUpTime;   //上电时间，小于1小时不上报
    u8    RptPowerDnEvtRcd[150];  //掉电事件记录存E2空间大小
} sEvtReport_TypeDef;   // 主动上报

//---高级参数文件-------
typedef struct
{
    u8      PExpression;        //有功组合方式特征字
    u8      PtQExpression;      //无功组合1方式特征字
    u8      NtQExpression;      //无功组合2方式特征字
    sDF11       PConstE;            //有功常数
    sDF11       QConstE;            //无功常数

    sDF12       MeterNo;            //表号
    sDF13       MCT;            //电流互感器变比
    sDF13       MPT;                //电压互感器变比

    u8      WireMode;            //接线方式 0三相四线、1三相三线
    u32     StartCur;           //启动电流
    u16     CriticalVol;        //临界电压

    sDF12       UserNo;         //客户编号
    u8      CardSerial[8];      // 用户卡序号

    u8      MeterRunFlag;       //电表运行特征字

    u32     tIRPrg;         // 红外认证时效
    u32     tTerminalPrg;           // 终端身份认证时效
    u8      tEvRstDely;         // 主动上报状态字自动复位延时时间
    u32     GataSafeCur;        // 继电器拉闸控制电流门限值
    u16     tSafeGata;          // 超拉闸控制电流门限保护延时时间,单位:分

    u16         GateOffDelayTime;       //跳闸延时时间（NNNN为跳闸前告警时间）
    sVolYieldPara_TypeDef   Yield;  //电压合格率参数

    u16 RTCDota0;       /*"2次曲线初始频率偏差"*/
    u16 CurveMode;
    u16    DATA0;       /*"4次或者3次曲线初始频率偏差"*/
    u16    XT1;     /*"晶振温度曲线顶点温度"*/
    u16    ALPHA;       /*"晶振一次温度系数"*/
    u16    BETA;        /*"晶振二次温度系数"*/
    u16    GAMMA;       /*"晶振三次温度系数"*/
    u16    ZETA;        /*"晶振四次温度系数"*/

    u8  RTCAdj[4];              // RTC高低温时补偿值
    u8  RTC_CAL_Data[10];   // RTC二次补偿值

    u8      FristPowOnBak2[4];
    u16     Crc;
} sHighParaFile_TypeDef;        //

//软件备案信息类型
typedef struct
{
    u8 Type[2];         //备案类型
    u8 FactoryNo[4];    //厂家代码
    u8 SoftType[1];     //程序备案类型
    u8 Date[8];         //备案日期
    u8 DayNo;           //当日备案序号
    u8 No[16];          //备案号
} sSoftWareInfo_TypeDef;

//---电表信息------
typedef struct
{
    u8  MeterPlace[12];     //电表位置信息
    char    DeviceNo[32];       //资产管理号
    char    RatingVol[6];       //额定电压
    char    MimCur[32];         //最小电流
    char    TrCur[32];          //转折电流
    char    RatingCur[6];           //最大电流
    char    MaxCur[6];          //最大电流
    char    PGrade[4];          //有功精度等级
    char    QGrade[4];          //无功精度等级
    char    MeterModel[32];     //表型号/ 设备描述符
    sDate_time_s_TypeDef    ProductDate;        //生产日期
    char    PtVer[20];          //协议版本号/支持规约列表

    char    SoftVer[32];        //厂家软件版本
    char    FirmVer[32];        //厂家硬件版本
    char    FactoryNo[32];      //厂家编号
    u8      SoftWare[16];           //软件备案版本号
    sSoftWareInfo_TypeDef       softWareInfo;

    u8      ServerVer[32];          //698服务器厂商版本信息:厂商代码(4byte)+软件版本号(4byte)+
    //软件版本日期(6byte)+硬件版本号(4byte)+硬件版本日期(6byte)+厂家扩展信息(8)

    char    FactoryMAC[32];  //厂家内部MAC地址，内部表号
    u16 Crc;
} sASCIIParaFile_TypeDef;       //

typedef struct
{
    u8  Already;        //当日已广播校时标志
    u8  ClockErr;       //广播校时超过最大校时偏差时，记时钟故障事件记录
} sBroatStatue_TypeDef;

typedef struct
{
    u8  CoverOpen;
    sDate_time_s_TypeDef    CoverOpenTime;
    u8  CoverClose;
    sDate_time_s_TypeDef    CoverCloseTime;

    u8  TailOpen;
    sDate_time_s_TypeDef    TailOpenTime;
    u8  TailClose;
    sDate_time_s_TypeDef    TailCloseTime;

    u8 EvtPwdn;
    sDate_time_s_TypeDef    EvtPwdnTime;

    u8  EvtVoltLoss;
} sEvtPwnCoverTailTypedef;

typedef struct
{
    u16     OI;         //对象标识
    u16     Mode;   //安全模式参数
} sSafeModeTable_TypeDef;

typedef struct
{
    u8      OI_Cnt;         //显式安全模式字 OI个数
    sSafeModeTable_TypeDef      SafeModeTable[MAX_SafePara];   //安全模式列表
    u16 Crc;
} sSafeModePara_TypeDef;

//---密码参数文件-------
typedef struct
{
    u8      SecretPara[10][4];          //

    u8      nPswRetry;                  //密码重试次数          //(hyg) BCD码
    u16     tPswFailClose;              //密码错误封锁时间      //(hyg) BCD码

    u16     tPrgKeyValid;               //编程开关有效时间,单位：分钟，下同 (hyg) BCD码
    u16     tPrgKeyLock;                //编程开关闭锁时间 (两次编程键按下的时间间隔)

    // 安全模式参数
    u8      SafeModeFlag;
    sSafeModePara_TypeDef   SafeModePara;
    u8      AuthOn;   //身份认证启用:0=明文/明文+RN 抄读无需身份认证;1=明文读取需要身份认证
    u8      FuncationItem[32];
    u8      Labour[32];
    u8      FristPowOnBak1[4];
    u16   Crc;
} sSecretParaFile_TypeDef;      //111 Byte

//---存储器特性文件-------
typedef struct
{
    u8      FristPowOn[4];

    u8      pRmEgSh;            //0
    u8      pRmNeed;            //1
    u8      pTimeFrz;           //2
    u8      pWinkFrz;           //3
    u8      pDayFrz;            //4
    u8      pTZoneSwFrz;        //5
    u8      pPOTSwFrz;          //6
    u8      pRatePriceSwFrz;    //7
    u8      pLadderSwFrz;       //8
    u8      pHourFrz;           //9
    u8      pStat;              //10
    u16     pSCurve;            //负荷曲线起始指针11
    u16     pECurve;            //负荷曲线结束指针13
    u8      pRmApplyEg;         //15
    u16 Crc;
} sNvRamFile_TypeDef;

//掉电文件，掉电需要保存的数据，此文件数据其他地方有可能定义过
typedef struct
{
    sDate_time_s_TypeDef    PowDnTime;                            //掉电时间
    sEgPiece_TypeDef        EgPiece;
    u8      CheckMoneyFlag;                        //掉电剩余脉冲数
    u8      PownDnAllPEgSh[MAX_FL + 1];     //掉电组合各费率脉冲数
    u8      PownDnPtPEgSh[MAX_FL + 1];      //掉电正向各费率脉冲数
    u8      PownDnNtPEgSh[MAX_FL + 1];      //掉电反向向各费率脉冲数
    u32    tWorkBat;
    sDate_time_s_TypeDef  FrzDayTime;
    sDate_time_s_TypeDef  FrzRmDayTime;
    u8      Irms[12];  //掉电全失压时ABC三相电流
    u16     Crc;
} sPowDnFile_TypeDef;

typedef struct
{
    u8    EnOrDis;     //电压影响量补偿开关
    u8    Rep[nPhs][MAX_VOLT_STEP];  //电压影响量补偿
    u16   Crc;  //
}   sVoltRepairPara_TypeDef;

typedef struct
{
    sVoltRepairPara_TypeDef  Volt; //电压影响量补偿
    u16 TIRM;
}   sMeasureRepairPara_TypeDef;

typedef struct
{
    u8    BackUp_FL;
    sFsEgSh_HighTypeDef BackUpEnergy[12 + 1];   // 预留总及12费率空间
}   sBackUpEnergy_TypeDef;

typedef struct
{
    sDF12           CurSurplusMoneyBackUp;          //当前剩余金额6字节（扩充2个字节）
    sDF12           CurOverdraftMoneyBackUp;        //当前透支金额6字节（扩充2个字节）
    sFsEgSh_TypeDef CurApplyEgBackUp;               //当前结算周期组合有功总累计用电量
    sFsEgSh_TypeDef Rmday1ApplyEgBackUp;            //上一结算周期组合有功总累计用电量
    u16             CurSurplusMoneyBackUpCrc;
    u16             CurApplyEgBackUpCrc;
    u8              BackUpOpCode[4];                // 保存当前拉合闸所使用的操作者代码

    sDate_time_s_TypeDef   BackUpDatetime;
    sBackUpEnergy_TypeDef BackUpPtPEgSh;      //正向有功电能
    sBackUpEnergy_TypeDef BackUpNtPEgSh;      //反向有功电能
    sBackUpEnergy_TypeDef BackUpQd1QEgSh;       //一象限无功电能示值
    sBackUpEnergy_TypeDef BackUpQd2QEgSh;       //四象限无功电能示值
    sBackUpEnergy_TypeDef BackUpQd3QEgSh;       //二象限无功电能示值
    sBackUpEnergy_TypeDef BackUpQd4QEgSh;       //三象限无功电能示值
    u16 Crc;
} sBackUpCurMoneyFile_TypeDef;

typedef struct
{
    sDate_time_s_TypeDef    Start;                  // 升级发生时间
    sDate_time_s_TypeDef    End;                    // 升级结束时间
    u8                      OptType;                // 升级操作类型
    u32                     StPosEng;               // 升级前正向有功总电能
    u32                     StNegEng;               // 升级前反向有功总电能
    u8                      LoadId[32];             // 下载方标识
    u8                      BfSoftVer[16];          // 升级前软件版本号
    u8                      AftSoftVer[16];         // 升级后软件版本号
    u8                      AppName[32];            // 升级应用名称
    u8                      Result;                 // 升级结果
} sEvtMngUpdateTypedef;

typedef struct
{
    u8                      OldEsamSq[8];       // 原ESAM序列号
    u8                      NewEsamSq[8];       // 新ESAM序列号
    sEvtMngUpdateTypedef    EvtMngUpdate;       // 管理芯升级记录内容
} sEvtExternRecordTypedef;

typedef struct
{
    sDate_time_s_TypeDef    PwdnTime;           // 停电发生时间
    u16                     VoltVal[3];         // 停电期间电压数据 0.1V
    u32                     CurVal[3];          // 停电期间电流数据 0.001A
} sPwdnVoltCurTypedef;

#pragma pack()

//=============================================================================
//===定义文件项信息========================================
typedef enum
{
    //项长度                            数据长度 + 校验和长度(2byte) 8*13+2=106
    FileItemInfoLen_EgSh_PtPEgSh        = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_NtPEgSh        = (sizeof(sFsEgSh_HighTypeDef) + 2),

    FileItemInfoLen_EgSh_Qd1QEgSh       = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd2QEgSh       = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd3QEgSh       = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd4QEgSh       = (sizeof(sFsEgSh_HighTypeDef) + 2),

    FileItemInfoLen_EgSh_PtPEgSha   = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_NtPEgSha   = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd1QEgSha  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd2QEgSha  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd3QEgSha  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd4QEgSha  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_PtPEgShb   = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_NtPEgShb   = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd1QEgShb  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd2QEgShb  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd3QEgShb  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd4QEgShb  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_PtPEgShc   = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_NtPEgShc   = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd1QEgShc  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd2QEgShc  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd3QEgShc  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd4QEgShc  = (sizeof(sFsEgSh_HighTypeDef) + 2),

    FileItemInfoLen_EgSh_PtFEgSh        = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_NtFEgSh        = (sizeof(sFsEgSh_HighTypeDef) + 2),

    FileItemInfoLen_EgSh_PtHEgSh        = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_NtHEgSh        = (sizeof(sFsEgSh_HighTypeDef) + 2),

    //项偏移地址
    FileItemInfoOffAddr_EgSh_PtPEgSh        = (0),
    FileItemInfoOffAddr_EgSh_NtPEgSh        = (FileItemInfoOffAddr_EgSh_PtPEgSh   +   FileItemInfoLen_EgSh_PtPEgSh),

    FileItemInfoOffAddr_EgSh_Qd1QEgSh       = (FileItemInfoOffAddr_EgSh_NtPEgSh   +   FileItemInfoLen_EgSh_NtPEgSh),   //页对齐，避免掉电写E2时翻页
    FileItemInfoOffAddr_EgSh_Qd2QEgSh       = (FileItemInfoOffAddr_EgSh_Qd1QEgSh  +   FileItemInfoLen_EgSh_Qd1QEgSh),   //页对齐，避免掉电写E2时翻页
    FileItemInfoOffAddr_EgSh_Qd3QEgSh       = (FileItemInfoOffAddr_EgSh_Qd2QEgSh  +   FileItemInfoLen_EgSh_Qd2QEgSh),   //页对齐，避免掉电写E2时翻页
    FileItemInfoOffAddr_EgSh_Qd4QEgSh       = (FileItemInfoOffAddr_EgSh_Qd3QEgSh  +   FileItemInfoLen_EgSh_Qd3QEgSh),

    FileItemInfoOffAddr_EgSh_PtPEgSha   = (64),
    FileItemInfoOffAddr_EgSh_NtPEgSha   = (FileItemInfoOffAddr_EgSh_PtPEgSha  +   FileItemInfoLen_EgSh_PtPEgSha),
    FileItemInfoOffAddr_EgSh_Qd1QEgSha  = (FileItemInfoOffAddr_EgSh_NtPEgSha  +   FileItemInfoLen_EgSh_NtPEgSha),
    FileItemInfoOffAddr_EgSh_Qd2QEgSha  = (FileItemInfoOffAddr_EgSh_Qd1QEgSha +   FileItemInfoLen_EgSh_Qd1QEgSha),
    FileItemInfoOffAddr_EgSh_Qd3QEgSha  = (FileItemInfoOffAddr_EgSh_Qd2QEgSha +   FileItemInfoLen_EgSh_Qd2QEgSha),
    FileItemInfoOffAddr_EgSh_Qd4QEgSha  = (FileItemInfoOffAddr_EgSh_Qd3QEgSha +   FileItemInfoLen_EgSh_Qd3QEgSha),

    FileItemInfoOffAddr_EgSh_PtPEgShb   = (128),
    FileItemInfoOffAddr_EgSh_NtPEgShb   = (FileItemInfoOffAddr_EgSh_PtPEgShb  +   FileItemInfoLen_EgSh_PtPEgShb),
    FileItemInfoOffAddr_EgSh_Qd1QEgShb  = (FileItemInfoOffAddr_EgSh_NtPEgShb  +   FileItemInfoLen_EgSh_NtPEgShb),
    FileItemInfoOffAddr_EgSh_Qd2QEgShb  = (FileItemInfoOffAddr_EgSh_Qd1QEgShb +   FileItemInfoLen_EgSh_Qd1QEgShb),
    FileItemInfoOffAddr_EgSh_Qd3QEgShb  = (FileItemInfoOffAddr_EgSh_Qd2QEgShb +   FileItemInfoLen_EgSh_Qd2QEgShb),
    FileItemInfoOffAddr_EgSh_Qd4QEgShb  = (FileItemInfoOffAddr_EgSh_Qd3QEgShb +   FileItemInfoLen_EgSh_Qd3QEgShb),

    FileItemInfoOffAddr_EgSh_PtPEgShc   = (192),
    FileItemInfoOffAddr_EgSh_NtPEgShc   = (FileItemInfoOffAddr_EgSh_PtPEgShc  +   FileItemInfoLen_EgSh_PtPEgShc),
    FileItemInfoOffAddr_EgSh_Qd1QEgShc  = (FileItemInfoOffAddr_EgSh_PtPEgShc  +   FileItemInfoLen_EgSh_NtPEgShc),
    FileItemInfoOffAddr_EgSh_Qd2QEgShc  = (FileItemInfoOffAddr_EgSh_Qd1QEgShc +   FileItemInfoLen_EgSh_Qd1QEgShc),
    FileItemInfoOffAddr_EgSh_Qd3QEgShc  = (FileItemInfoOffAddr_EgSh_Qd2QEgShc +   FileItemInfoLen_EgSh_Qd2QEgShc),
    FileItemInfoOffAddr_EgSh_Qd4QEgShc  = (FileItemInfoOffAddr_EgSh_Qd3QEgShc +   FileItemInfoLen_EgSh_Qd2QEgShc),

    FileItemInfoOffAddr_EgSh_PtFEgSh        = (256),   //页对齐，避免掉电写E2时翻页
    FileItemInfoOffAddr_EgSh_NtFEgSh        = (FileItemInfoOffAddr_EgSh_PtFEgSh   +   FileItemInfoLen_EgSh_PtFEgSh),   //

    FileItemInfoOffAddr_EgSh_PtHEgSh        = (FileItemInfoOffAddr_EgSh_NtFEgSh   +   FileItemInfoLen_EgSh_NtFEgSh),   //
    FileItemInfoOffAddr_EgSh_NtHEgSh        = (FileItemInfoOffAddr_EgSh_PtHEgSh   +   FileItemInfoLen_EgSh_PtHEgSh),   //

    FileItemInfoOffAddr_EgSh_End            = (FileItemInfoOffAddr_EgSh_NtHEgSh   +   FileItemInfoLen_EgSh_NtHEgSh),

    FileItemInfoLen_EgSh_TotalLen   = FileItemInfoOffAddr_EgSh_End + 128  //预留128byte 空间
} eFileItemInfo_EgSh_TypeDef; //电能文件项信息

typedef enum
{
    //项长度
    FileItemInfoLen_InterTmp_Need   = (sizeof(sNeedInter_TypeDef)),
    FileItemInfoLen_InterTmp_EvStatus   = (sizeof(sEvStatusInter_TypeDef)),
    FileItemInfoLen_InterTmp_Stat   = (sizeof(sStatInter_TypeDef)),
    FileItemInfoLen_InterTmp_Secret     = (sizeof(sSecretInter_TypeDef)),
    FileItemInfoLen_InterTmp_OpenCover  = (sizeof(sOpenCoverInter_TypeDef)),
    FileItemInfoLen_InterTmp_Misc   = (sizeof(sMisc_TypeDef)),
    FileItemInfoLen_InterTmp_EgMoney    = (sizeof(sCurEgMoney_TypeDef)),
    FileItemInfoLen_InterTmp_MLinkSize  = (sizeof(sLinkSize_TypeDef)),
    FileItemInfoLen_InterTmp_TLinkSize  = (sizeof(sLinkSize_TypeDef)),

    //项偏移地址
    FileItemInfoOffAddr_InterTmp_Need   = (0),
    FileItemInfoOffAddr_InterTmp_EvStatus   = (FileItemInfoOffAddr_InterTmp_Need   +   FileItemInfoLen_InterTmp_Need),
    FileItemInfoOffAddr_InterTmp_Stat           = (FileItemInfoOffAddr_InterTmp_EvStatus   +   FileItemInfoLen_InterTmp_EvStatus),
    FileItemInfoOffAddr_InterTmp_Secret         = (FileItemInfoOffAddr_InterTmp_Stat       +   FileItemInfoLen_InterTmp_Stat),
    FileItemInfoOffAddr_InterTmp_OpenCover = (FileItemInfoOffAddr_InterTmp_Secret     +   FileItemInfoLen_InterTmp_Secret),
    FileItemInfoOffAddr_InterTmp_Misc           = (FileItemInfoOffAddr_InterTmp_OpenCover + FileItemInfoLen_InterTmp_OpenCover),
    FileItemInfoOffAddr_InterTmp_EgMoney        = (FileItemInfoOffAddr_InterTmp_Misc   +   FileItemInfoLen_InterTmp_Misc),
    FileItemInfoOffAddr_InterTmp_MLinkSize  = (FileItemInfoOffAddr_InterTmp_EgMoney    +   FileItemInfoLen_InterTmp_EgMoney),
    FileItemInfoOffAddr_InterTmp_TLinkSize  = (FileItemInfoOffAddr_InterTmp_MLinkSize  +   FileItemInfoLen_InterTmp_MLinkSize),

    FileItemInfoOffAddr_InterTmp_End    = (FileItemInfoOffAddr_InterTmp_TLinkSize  +   FileItemInfoLen_InterTmp_TLinkSize)
} eFileItemInfo_InterTmp_TypeDef;//中间变量文件信息文件(电表工作时间计数，密码上锁时间，电能脉冲计数等)

typedef enum
{
    //项长度
    FileItemInfoLen_RatePara_nTimeZone  = (1),
    FileItemInfoLen_RatePara_nPOTTable  = (1),
    FileItemInfoLen_RatePara_nDayPOT    = (1),
    FileItemInfoLen_RatePara_nFl    = (1),
    FileItemInfoLen_RatePara_nHoliday   = (1),
    FileItemInfoLen_RatePara_nLadder    = (1),
    FileItemInfoLen_RatePara_Weekend    = (1),
    FileItemInfoLen_RatePara_WeekendPOT = (1),
    FileItemInfoLen_RatePara_RmDate = (6),
    FileItemInfoLen_RatePara_HolidayTable   = (sizeof(sHolidayTable_TypeDef) * 20),
    FileItemInfoLen_RatePara_TimeZonePara   = (sizeof(sTimeZonePara_TypeDef)),
    FileItemInfoLen_RatePara_POTTablePara   = (sizeof(sPOTTablePara_TypeDef)),
    FileItemInfoLen_RatePara_RatePricePara  = (sizeof(sRatePricePara_TypeDef)),
    FileItemInfoLen_RatePara_LadderPara = (sizeof(sLadderPara_TypeDef)),
    FileItemInfoLen_RatePara_ChargMoneyPara = (sizeof(sChargMoneyPara_TypeDef)),

    //项偏移地址
    FileItemInfoOffAddr_RatePara_nTimeZone  = (0),
    FileItemInfoOffAddr_RatePara_nPOTTable  = (FileItemInfoOffAddr_RatePara_nTimeZone  +   FileItemInfoLen_RatePara_nTimeZone),
    FileItemInfoOffAddr_RatePara_nDayPOT        = (FileItemInfoOffAddr_RatePara_nPOTTable  +   FileItemInfoLen_RatePara_nPOTTable),
    FileItemInfoOffAddr_RatePara_nFl                = (FileItemInfoOffAddr_RatePara_nDayPOT        +   FileItemInfoLen_RatePara_nDayPOT),
    FileItemInfoOffAddr_RatePara_nHoliday   = (FileItemInfoOffAddr_RatePara_nFl                +   FileItemInfoLen_RatePara_nFl),
    FileItemInfoOffAddr_RatePara_nLadder        = (FileItemInfoOffAddr_RatePara_nHoliday       +   FileItemInfoLen_RatePara_nHoliday),
    FileItemInfoOffAddr_RatePara_Weekend        = (FileItemInfoOffAddr_RatePara_nLadder        +   FileItemInfoLen_RatePara_nLadder),
    FileItemInfoOffAddr_RatePara_WeekendPOT = (FileItemInfoOffAddr_RatePara_Weekend        +   FileItemInfoLen_RatePara_Weekend),
    FileItemInfoOffAddr_RatePara_RmDate     = (FileItemInfoOffAddr_RatePara_WeekendPOT +   FileItemInfoLen_RatePara_WeekendPOT),
    FileItemInfoOffAddr_RatePara_HolidayTable   = (FileItemInfoOffAddr_RatePara_RmDate +   FileItemInfoLen_RatePara_RmDate),
    FileItemInfoOffAddr_RatePara_TimeZonePara   = (FileItemInfoOffAddr_RatePara_HolidayTable   +   FileItemInfoLen_RatePara_HolidayTable),
    FileItemInfoOffAddr_RatePara_POTTablePara   = (FileItemInfoOffAddr_RatePara_TimeZonePara   +   FileItemInfoLen_RatePara_TimeZonePara),
    FileItemInfoOffAddr_RatePara_RatePricePara  = (FileItemInfoOffAddr_RatePara_POTTablePara   +   FileItemInfoLen_RatePara_POTTablePara),
    FileItemInfoOffAddr_RatePara_LadderPara     = (FileItemInfoOffAddr_RatePara_RatePricePara + FileItemInfoLen_RatePara_RatePricePara),
    FileItemInfoOffAddr_RatePara_ChargMoneyPara = (FileItemInfoOffAddr_RatePara_LadderPara +   FileItemInfoLen_RatePara_LadderPara),
    FileItemInfoOffAddr_RatePara_End    = (FileItemInfoOffAddr_RatePara_ChargMoneyPara +   FileItemInfoLen_RatePara_ChargMoneyPara)
} eDl645FileItemInfo_RatePara_TypeDef;//费率参数信息文件

typedef enum
{
    //项长度
    FileItemInfoLen_DocPara_NeedMode                = 1,
    FileItemInfoLen_DocPara_NeedCyc         = 1,
    FileItemInfoLen_DocPara_NeedSlip        = 1,
    FileItemInfoLen_DocPara_PlsWidth        = 2,
    FileItemInfoLen_DocPara_nWave           = 1,
    FileItemInfoLen_DocPara_BroadcastMIN     = 2,
    FileItemInfoLen_DocPara_BroadcastMAX     = 2,
    FileItemInfoLen_DocPara_WirelessSignal  = 1,
    FileItemInfoLen_DocPara_Crc  = 2,

    //项偏移地址
    FileItemInfoOffAddr_DocPara_NeedMode                = (0),
    FileItemInfoOffAddr_DocPara_NeedCyc         = (FileItemInfoOffAddr_DocPara_NeedMode            +    FileItemInfoLen_DocPara_NeedMode),
    FileItemInfoOffAddr_DocPara_NeedSlip        = (FileItemInfoOffAddr_DocPara_NeedCyc      +    FileItemInfoLen_DocPara_NeedCyc),
    FileItemInfoOffAddr_DocPara_PlsWidth        = (FileItemInfoOffAddr_DocPara_NeedSlip     +    FileItemInfoLen_DocPara_NeedSlip),
    FileItemInfoOffAddr_DocPara_nWave           = (FileItemInfoOffAddr_DocPara_PlsWidth     +    FileItemInfoLen_DocPara_PlsWidth),
    FileItemInfoOffAddr_DocPara_BroadcastMIN     = (FileItemInfoOffAddr_DocPara_nWave  +    FileItemInfoLen_DocPara_nWave),
    FileItemInfoOffAddr_DocPara_BroadcastMAX     = (FileItemInfoOffAddr_DocPara_BroadcastMIN        +    FileItemInfoLen_DocPara_BroadcastMIN),
    FileItemInfoOffAddr_DocPara_WirelessSignal  = (FileItemInfoOffAddr_DocPara_BroadcastMAX  +    FileItemInfoLen_DocPara_BroadcastMAX),
    FileItemInfoOffAddr_DocPara_Crc                     = (FileItemInfoOffAddr_DocPara_WirelessSignal  +  FileItemInfoLen_DocPara_WirelessSignal),
    FileItemInfoOffAddr_DocPara_end                     = (FileItemInfoOffAddr_DocPara_Crc  +  FileItemInfoLen_DocPara_Crc)
} eFileItemInfo_DocPara_TypeDef;// 通用参数文件

typedef enum
{
    //项长度
    FileItemInfoLen_ComPara_ComAddr     = (6),
    FileItemInfoLen_ComPara_Ir1Style        = 1,
    FileItemInfoLen_ComPara_Ir2Style         = 1,
    FileItemInfoLen_ComPara_Com1Style        = 1,
    FileItemInfoLen_ComPara_Com2Style        = 1,
    FileItemInfoLen_ComPara_Com3Style        = 1,

    //项偏移地址
    FileItemInfoOffAddr_ComPara_ComAddr     = (0),
    FileItemInfoOffAddr_ComPara_Ir1Style    = (FileItemInfoOffAddr_ComPara_ComAddr + FileItemInfoLen_ComPara_ComAddr),
    FileItemInfoOffAddr_ComPara_Ir2Style    = (FileItemInfoOffAddr_ComPara_Ir1Style    +   FileItemInfoLen_ComPara_Ir1Style),
    FileItemInfoOffAddr_ComPara_Com1Style   = (FileItemInfoOffAddr_ComPara_Ir2Style  +   FileItemInfoLen_ComPara_Ir2Style),
    FileItemInfoOffAddr_ComPara_Com2Style   = (FileItemInfoOffAddr_ComPara_Com1Style +   FileItemInfoLen_ComPara_Com1Style),
    FileItemInfoOffAddr_ComPara_Com3Style   = (FileItemInfoOffAddr_ComPara_Com2Style +   FileItemInfoLen_ComPara_Com2Style),
    FileItemInfoOffAddr_ComPara_end             = (FileItemInfoOffAddr_ComPara_Com3Style +   FileItemInfoLen_ComPara_Com3Style)
} eFileItemInfo_ComPara_TypeDef;// 通讯参数

typedef enum
{
    //项长度
    FileItemInfoLen_DispPara_AllonDispTime  =   1,
    FileItemInfoLen_DispPara_KeyLightTime   =   2,
    FileItemInfoLen_DispPara_ChkLightTime   =   2,
    FileItemInfoLen_DispPara_KeyPwrOffTime  =   2,
    FileItemInfoLen_DispPara_DecimalEg  =   1,
    FileItemInfoLen_DispPara_DecimalPw  =   1,
    FileItemInfoLen_DispPara_LCDWordMn  =   1,
    FileItemInfoLen_DispPara_nCycDisp   =   1,
    FileItemInfoLen_DispPara_nKeyDisp   =   1,
    FileItemInfoLen_DispPara_AutoDispTime   =   2,
    FileItemInfoLen_DispPara_KeyDispTime    =   2,
    FileItemInfoLen_DispPara_CycDispItem        = (sizeof(sDispItem_TypeDef) * MAX_CYCDISP),
    FileItemInfoLen_DispPara_KeyDispItem        = (sizeof(sDispItem_TypeDef) * MAX_CYCDISP),

    //项偏移地址
    FileItemInfoOffAddr_DispPara_AllonDispTime = (0),
    FileItemInfoOffAddr_DispPara_KeyLightTime = (FileItemInfoOffAddr_DispPara_AllonDispTime  +   FileItemInfoLen_DispPara_AllonDispTime),
    FileItemInfoOffAddr_DispPara_ChkLightTime = (FileItemInfoOffAddr_DispPara_KeyLightTime   +   FileItemInfoLen_DispPara_KeyLightTime),
    FileItemInfoOffAddr_DispPara_KeyPwrOffTime = (FileItemInfoOffAddr_DispPara_ChkLightTime   +   FileItemInfoLen_DispPara_ChkLightTime),
    FileItemInfoOffAddr_DispPara_DecimalEg    = (FileItemInfoOffAddr_DispPara_KeyPwrOffTime  +   FileItemInfoLen_DispPara_KeyPwrOffTime),
    FileItemInfoOffAddr_DispPara_DecimalPw    = (FileItemInfoOffAddr_DispPara_DecimalEg      +   FileItemInfoLen_DispPara_DecimalEg),
    FileItemInfoOffAddr_DispPara_LCDWordMn    = (FileItemInfoOffAddr_DispPara_DecimalPw      +   FileItemInfoLen_DispPara_DecimalPw),
    FileItemInfoOffAddr_DispPara_nCycDisp     = (FileItemInfoOffAddr_DispPara_LCDWordMn      +   FileItemInfoLen_DispPara_LCDWordMn),
    FileItemInfoOffAddr_DispPara_nKeyDisp     = (FileItemInfoOffAddr_DispPara_nCycDisp       +   FileItemInfoLen_DispPara_nCycDisp),
    FileItemInfoOffAddr_DispPara_AutoDispTime   = (FileItemInfoOffAddr_DispPara_nKeyDisp       +   FileItemInfoLen_DispPara_nKeyDisp),
    FileItemInfoOffAddr_DispPara_KeyDispTime    = (FileItemInfoOffAddr_DispPara_AutoDispTime   +   FileItemInfoLen_DispPara_AutoDispTime),
    FileItemInfoOffAddr_DispPara_CycDispItem    = (FileItemInfoOffAddr_DispPara_KeyDispTime      + FileItemInfoLen_DispPara_KeyDispTime),
    FileItemInfoOffAddr_DispPara_KeyDispItem    = (FileItemInfoOffAddr_DispPara_CycDispItem      + FileItemInfoLen_DispPara_CycDispItem),
    FileItemInfoOffAddr_DispPara_end            = (FileItemInfoOffAddr_DispPara_KeyDispItem      + FileItemInfoLen_DispPara_KeyDispItem)
} eDl645FileItemInfo_DispPara_TypeDef;//显示参数
typedef enum
{
    //项长度
    FileItemInfoLen_WastePara_Ga = sizeof(sDF26),
    FileItemInfoLen_WastePara_Ba = sizeof(sDF26),
    FileItemInfoLen_WastePara_Ra = sizeof(sDF26),
    FileItemInfoLen_WastePara_Xa = sizeof(sDF26),
    FileItemInfoLen_WastePara_Gb = sizeof(sDF26),
    FileItemInfoLen_WastePara_Bb = sizeof(sDF26),
    FileItemInfoLen_WastePara_Rb = sizeof(sDF26),
    FileItemInfoLen_WastePara_Xb = sizeof(sDF26),
    FileItemInfoLen_WastePara_Gc = sizeof(sDF26),
    FileItemInfoLen_WastePara_Bc = sizeof(sDF26),
    FileItemInfoLen_WastePara_Rc = sizeof(sDF26),
    FileItemInfoLen_WastePara_Xc = sizeof(sDF26),
    //项偏移地址
    FileItemInfoOffAddr_WastePara_Ga = (0),
    FileItemInfoOffAddr_WastePara_Ba = (FileItemInfoOffAddr_WastePara_Ga +  FileItemInfoLen_WastePara_Ga),
    FileItemInfoOffAddr_WastePara_Ra = (FileItemInfoOffAddr_WastePara_Ba +  FileItemInfoLen_WastePara_Ba),
    FileItemInfoOffAddr_WastePara_Xa = (FileItemInfoOffAddr_WastePara_Ra +  FileItemInfoLen_WastePara_Ra),
    FileItemInfoOffAddr_WastePara_Gb = (FileItemInfoOffAddr_WastePara_Xa +  FileItemInfoLen_WastePara_Xa),
    FileItemInfoOffAddr_WastePara_Bb = (FileItemInfoOffAddr_WastePara_Gb +  FileItemInfoLen_WastePara_Gb),
    FileItemInfoOffAddr_WastePara_Rb = (FileItemInfoOffAddr_WastePara_Bb +  FileItemInfoLen_WastePara_Bb),
    FileItemInfoOffAddr_WastePara_Xb = (FileItemInfoOffAddr_WastePara_Rb +  FileItemInfoLen_WastePara_Rb),
    FileItemInfoOffAddr_WastePara_Gc = (FileItemInfoOffAddr_WastePara_Xb +  FileItemInfoLen_WastePara_Xb),
    FileItemInfoOffAddr_WastePara_Bc = (FileItemInfoOffAddr_WastePara_Gc +  FileItemInfoLen_WastePara_Gc),
    FileItemInfoOffAddr_WastePara_Rc = (FileItemInfoOffAddr_WastePara_Bc +  FileItemInfoLen_WastePara_Bc),
    FileItemInfoOffAddr_WastePara_Xc = (FileItemInfoOffAddr_WastePara_Rc +  FileItemInfoLen_WastePara_Rc),
    FileItemInfoOffAddr_WastePara_end = (FileItemInfoOffAddr_WastePara_Xc +  FileItemInfoLen_WastePara_Xc)
} eFileItemInfo_WastePara_TypeDef;// 通讯参数

typedef enum
{
    //项长度
    FileItemInfoLen_OutputPara_Style1                   = (2),
    FileItemInfoLen_OutputPara_Trigger1       = (2),
    FileItemInfoLen_OutputPara_Style2         = (2),
    FileItemInfoLen_OutputPara_Trigger2       = (2),
    FileItemInfoLen_OutputPara_Style3         = (2),
    FileItemInfoLen_OutputPara_Trigger3       = (2),
    FileItemInfoLen_OutputPara_Style4         = (2),
    FileItemInfoLen_OutputPara_Trigger4       = (2),
    FileItemInfoLen_OutputPara_Style5         = (2),
    FileItemInfoLen_OutputPara_Trigger5       = (2),
    FileItemInfoLen_OutputPara_Style6         = (2),
    FileItemInfoLen_OutputPara_Trigger6       = (2),
    FileItemInfoLen_OutputPara_RelaysOutAlarm = (10),
    FileItemInfoLen_OutputPara_LightAlarm     = (10),
    FileItemInfoLen_OutputPara_SoundAlarm     = (10),
    //项偏移地址
    FileItemInfoOffAddr_OutputPara_Style1                   = (0),
    FileItemInfoOffAddr_OutputPara_Trigger1       = (FileItemInfoOffAddr_OutputPara_Style1               +   FileItemInfoLen_OutputPara_Style1),
    FileItemInfoOffAddr_OutputPara_Style2         = (FileItemInfoOffAddr_OutputPara_Trigger1       +   FileItemInfoLen_OutputPara_Trigger1),
    FileItemInfoOffAddr_OutputPara_Trigger2       = (FileItemInfoOffAddr_OutputPara_Style2         +   FileItemInfoLen_OutputPara_Style2),
    FileItemInfoOffAddr_OutputPara_Style3         = (FileItemInfoOffAddr_OutputPara_Trigger2       +   FileItemInfoLen_OutputPara_Trigger2),
    FileItemInfoOffAddr_OutputPara_Trigger3       = (FileItemInfoOffAddr_OutputPara_Style3         +   FileItemInfoLen_OutputPara_Style3),
    FileItemInfoOffAddr_OutputPara_Style4         = (FileItemInfoOffAddr_OutputPara_Trigger3       +   FileItemInfoLen_OutputPara_Trigger3),
    FileItemInfoOffAddr_OutputPara_Trigger4       = (FileItemInfoOffAddr_OutputPara_Style4         +   FileItemInfoLen_OutputPara_Style4),
    FileItemInfoOffAddr_OutputPara_Style5         = (FileItemInfoOffAddr_OutputPara_Trigger4       +   FileItemInfoLen_OutputPara_Trigger4),
    FileItemInfoOffAddr_OutputPara_Trigger5       = (FileItemInfoOffAddr_OutputPara_Style5         +   FileItemInfoLen_OutputPara_Style5),
    FileItemInfoOffAddr_OutputPara_Style6         = (FileItemInfoOffAddr_OutputPara_Trigger5       +   FileItemInfoLen_OutputPara_Trigger5),
    FileItemInfoOffAddr_OutputPara_Trigger6       = (FileItemInfoOffAddr_OutputPara_Style6         +   FileItemInfoLen_OutputPara_Style6),
    FileItemInfoOffAddr_OutputPara_RelaysOutAlarm = (FileItemInfoOffAddr_OutputPara_Trigger6       +   FileItemInfoLen_OutputPara_Trigger6),
    FileItemInfoOffAddr_OutputPara_LightAlarm     = (FileItemInfoOffAddr_OutputPara_RelaysOutAlarm +   FileItemInfoLen_OutputPara_RelaysOutAlarm),
    FileItemInfoOffAddr_OutputPara_SoundAlarm     = (FileItemInfoOffAddr_OutputPara_LightAlarm     +   FileItemInfoLen_OutputPara_LightAlarm),
    FileItemInfoOffAddr_OutputPara_end                  = (FileItemInfoOffAddr_OutputPara_SoundAlarm     +   FileItemInfoLen_OutputPara_SoundAlarm)
} eFileItemInfo_OutputPara_TypeDef;//
typedef enum
{
    //项长度
    FileItemInfoLen_CipherKeyPara_nCipherKey                 = (1),
    FileItemInfoLen_CipherKeyPara_WriteStarFlag      = (1),
    FileItemInfoLen_CipherKeyPara_CipherKeyWriteFlag = (4),
    FileItemInfoLen_CipherKeyPara_CipherKeyFlag      = (16),
    FileItemInfoLen_CipherKeyPara_CipherKey          = (1024),
    FileItemInfoLen_CipherKeyPara_nCipherKeyEE       = (4),
    FileItemInfoLen_CipherKeyPara_OpCode             = (4),
    //项偏移地址
    FileItemInfoOffAddr_CipherKeyPara_nCipherKey               = (0),
    FileItemInfoOffAddr_CipherKeyPara_WriteStarFlag      = (FileItemInfoOffAddr_CipherKeyPara_nCipherKey               +  FileItemInfoLen_CipherKeyPara_nCipherKey),
    FileItemInfoOffAddr_CipherKeyPara_CipherKeyWriteFlag = (FileItemInfoOffAddr_CipherKeyPara_WriteStarFlag      +  FileItemInfoLen_CipherKeyPara_WriteStarFlag),
    FileItemInfoOffAddr_CipherKeyPara_CipherKeyFlag      = (FileItemInfoOffAddr_CipherKeyPara_CipherKeyWriteFlag +  FileItemInfoLen_CipherKeyPara_CipherKeyWriteFlag),
    FileItemInfoOffAddr_CipherKeyPara_CipherKey          = (FileItemInfoOffAddr_CipherKeyPara_CipherKeyFlag      +  FileItemInfoLen_CipherKeyPara_CipherKeyFlag),
    FileItemInfoOffAddr_CipherKeyPara_nCipherKeyEE       = (FileItemInfoOffAddr_CipherKeyPara_CipherKey          +  FileItemInfoLen_CipherKeyPara_CipherKey),
    FileItemInfoOffAddr_CipherKeyPara_OpCode             = (FileItemInfoOffAddr_CipherKeyPara_nCipherKeyEE       +  FileItemInfoLen_CipherKeyPara_nCipherKeyEE),
    FileItemInfoOffAddr_CipherKeyPara_end                              = (FileItemInfoOffAddr_CipherKeyPara_OpCode             +  FileItemInfoLen_CipherKeyPara_OpCode)
} eFileItemInfo_CipherKeyPara_TypeDef;//

typedef enum
{
    //项长度
    FileItemInfoLen_EvtReport_AtiveAllow      = (1),
    FileItemInfoLen_EvtReport_FollowAllow   = (1),
    FileItemInfoLen_EvtReport_RptFlagHappen = (7),     //7*8=56 最大可支持56个事件记录
    FileItemInfoLen_EvtReport_RptFlagEnd    = (7),
    FileItemInfoLen_EvtReport_RptMode       = (7),
    FileItemInfoLen_EvtReport_RptStatusAllow = (1),
    FileItemInfoLen_EvtReport_RptStatusMode = (4),
    FileItemInfoLen_EvtReport_RptChannel    = (3),
    FileItemInfoLen_EvtReport_Crc               = (2),

    FileItemInfoLen_EvtReport_RptStatusZB    = (4),
    FileItemInfoLen_EvtReport_RptStuZBBack   = (4),
    FileItemInfoLen_EvtReport_RptStatus485   = (4),
    FileItemInfoLen_EvtReport_RptStu485Back  = (4),
    FileItemInfoLen_EvtReport_RptStatus4852  = (4),
    FileItemInfoLen_EvtReport_RptStu4852Back = (4),

    FileItemInfoLen_EvtReport_OADNumZB_A     = (1),
    FileItemInfoLen_EvtReport_RptListZB_A     = (4 * ITEM_EVT_MAX),

    FileItemInfoLen_EvtReport_OADNumZB_F     = (1),
    FileItemInfoLen_EvtReport_RptListZB_F     = (4 * ITEM_EVT_MAX),

    FileItemInfoLen_EvtReport_OADNum485_F    = (1),
    FileItemInfoLen_EvtReport_RptList485_F   = (4 * ITEM_EVT_MAX),

    FileItemInfoLen_EvtReport_OADNum4852_F   = (1),
    FileItemInfoLen_EvtReport_RptList4852_F    = (4 * ITEM_EVT_MAX),
    FileItemInfoLen_EvtReport_PowerUpTime    = (1),
    FileItemInfoLen_EvtReport_PowerDnEvtRcd      = (136),
    FileItemInfoLen_EvtReport_First_ClrTime     = (sizeof(sDate_time_s_TypeDef)),
    FileItemInfoLen_EvtReport_Factory_ClrTime        = (sizeof(sDate_time_s_TypeDef)),

    //项偏移地址
    FileItemInfoOffAddr_EvtReport_AtiveAllow    = (0),
    FileItemInfoOffAddr_EvtReport_FollowAllow   = (FileItemInfoOffAddr_EvtReport_AtiveAllow  + FileItemInfoLen_EvtReport_AtiveAllow),
    FileItemInfoOffAddr_EvtReport_RptFlagHappen = (FileItemInfoOffAddr_EvtReport_FollowAllow + FileItemInfoLen_EvtReport_FollowAllow),
    FileItemInfoOffAddr_EvtReport_RptFlagEnd    = (FileItemInfoOffAddr_EvtReport_RptFlagHappen + FileItemInfoLen_EvtReport_RptFlagHappen),
    FileItemInfoOffAddr_EvtReport_RptMode       = (FileItemInfoOffAddr_EvtReport_RptFlagEnd    + FileItemInfoLen_EvtReport_RptFlagEnd),
    FileItemInfoOffAddr_EvtReport_RptStatusAllow = (FileItemInfoOffAddr_EvtReport_RptMode       + FileItemInfoLen_EvtReport_RptMode),
    FileItemInfoOffAddr_EvtReport_RptStatusMode = (FileItemInfoOffAddr_EvtReport_RptStatusAllow + FileItemInfoLen_EvtReport_RptStatusAllow),
    FileItemInfoOffAddr_EvtReport_RptChannel    = (FileItemInfoOffAddr_EvtReport_RptStatusMode + FileItemInfoLen_EvtReport_RptStatusMode),
    FileItemInfoOffAddr_EvtReport_Crc           = (FileItemInfoOffAddr_EvtReport_RptChannel + FileItemInfoLen_EvtReport_RptChannel),

    FileItemInfoOffAddr_EvtReport_RptStatusZB   = (FileItemInfoOffAddr_EvtReport_Crc         + FileItemInfoLen_EvtReport_Crc),
    FileItemInfoOffAddr_EvtReport_RptStuZBBack  = (FileItemInfoOffAddr_EvtReport_RptStatusZB + FileItemInfoLen_EvtReport_RptStatusZB),
    FileItemInfoOffAddr_EvtReport_RptStatus485  = (FileItemInfoOffAddr_EvtReport_RptStuZBBack  + FileItemInfoLen_EvtReport_RptStuZBBack),
    FileItemInfoOffAddr_EvtReport_RptStu485Back = (FileItemInfoOffAddr_EvtReport_RptStatus485 + FileItemInfoLen_EvtReport_RptStatus485),
    FileItemInfoOffAddr_EvtReport_RptStatus4852 = (FileItemInfoOffAddr_EvtReport_RptStu485Back + FileItemInfoLen_EvtReport_RptStu485Back),
    FileItemInfoOffAddr_EvtReport_RptStu4852Back = (FileItemInfoOffAddr_EvtReport_RptStatus4852 + FileItemInfoLen_EvtReport_RptStatus4852),

    FileItemInfoOffAddr_EvtReport_OADNumZB_A    = (FileItemInfoOffAddr_EvtReport_RptStu4852Back + FileItemInfoLen_EvtReport_RptStu4852Back),
    FileItemInfoOffAddr_EvtReport_RptListZB_A   = (FileItemInfoOffAddr_EvtReport_OADNumZB_A    + FileItemInfoLen_EvtReport_OADNumZB_A),

    FileItemInfoOffAddr_EvtReport_OADNumZB_F    = (FileItemInfoOffAddr_EvtReport_RptListZB_A   + FileItemInfoLen_EvtReport_RptListZB_A),
    FileItemInfoOffAddr_EvtReport_RptListZB_F   = (FileItemInfoOffAddr_EvtReport_OADNumZB_F    + FileItemInfoLen_EvtReport_OADNumZB_F),

    FileItemInfoOffAddr_EvtReport_OADNum485_F   = (FileItemInfoOffAddr_EvtReport_RptListZB_F   + FileItemInfoLen_EvtReport_RptListZB_F),
    FileItemInfoOffAddr_EvtReport_RptList485_F  = (FileItemInfoOffAddr_EvtReport_OADNum485_F   + FileItemInfoLen_EvtReport_OADNum485_F),

    FileItemInfoOffAddr_EvtReport_OADNum4852_F  = (FileItemInfoOffAddr_EvtReport_RptList485_F  + FileItemInfoLen_EvtReport_RptList485_F),
    FileItemInfoOffAddr_EvtReport_RptList4852_F = (FileItemInfoOffAddr_EvtReport_OADNum4852_F  + FileItemInfoLen_EvtReport_OADNum4852_F),

    FileItemInfoOffAddr_EvtReport_PowerUpTime   = (FileItemInfoOffAddr_EvtReport_RptList4852_F + FileItemInfoLen_EvtReport_RptList4852_F),
    FileItemInfoOffAddr_EvtReport_PowerDnEvtRcd = (FileItemInfoOffAddr_EvtReport_PowerUpTime + FileItemInfoLen_EvtReport_PowerUpTime),
    FileItemInfoOffAddr_EvtReport_First_ClrTime         = (FileItemInfoOffAddr_EvtReport_PowerDnEvtRcd + FileItemInfoLen_EvtReport_PowerDnEvtRcd),
    FileItemInfoOffAddr_EvtReport_Factory_ClrTime           = (FileItemInfoOffAddr_EvtReport_First_ClrTime + FileItemInfoLen_EvtReport_First_ClrTime),

    FileItemInfoOffAddr_EvtReport_end           = (FileItemInfoOffAddr_EvtReport_Factory_ClrTime + FileItemInfoLen_EvtReport_Factory_ClrTime)
} eFileItemInfo_EvtReport_TypeDef;//

typedef enum
{
    //项长度
    FileItemInfoLen_ASCIIPara_MeterPlace    = (12),
    FileItemInfoLen_ASCIIPara_DeviceNo    = (32),
    FileItemInfoLen_ASCIIPara_RatingVol   = (6),
    FileItemInfoLen_ASCIIPara_MinCur    = (32),
    FileItemInfoLen_ASCIIPara_TrCur     = (32),
    FileItemInfoLen_ASCIIPara_RatingCur   = (6),
    FileItemInfoLen_ASCIIPara_MaxCur      = (6),
    FileItemInfoLen_ASCIIPara_PGrade      = (4),
    FileItemInfoLen_ASCIIPara_QGrade      = (4),
    FileItemInfoLen_ASCIIPara_MeterModel  = (32),
    FileItemInfoLen_ASCIIPara_ProductDate = (7),
    FileItemInfoLen_ASCIIPara_PtVer       = (20),
    FileItemInfoLen_ASCIIPara_SoftVer     = (32),
    FileItemInfoLen_ASCIIPara_FirmVer     = (32),
    FileItemInfoLen_ASCIIPara_FactoryNo   = (32),
    FileItemInfoLen_ASCIIPara_SoftWare    = (16),
    FileItemInfoLen_ASCIIPara_SoftWareInfo  = (32),
    FileItemInfoLen_ASCIIPara_ServerVer   = (32),
    FileItemInfoLen_ASCIIPara_FactoryMAC   = (32),
    //项偏移地址
    FileItemInfoOffAddr_ASCIIPara_MeterPlace    = (0),
    FileItemInfoOffAddr_ASCIIPara_DeviceNo    = (FileItemInfoOffAddr_ASCIIPara_MeterPlace  +  FileItemInfoLen_ASCIIPara_MeterPlace),
    FileItemInfoOffAddr_ASCIIPara_RatingVol   = (FileItemInfoOffAddr_ASCIIPara_DeviceNo    +  FileItemInfoLen_ASCIIPara_DeviceNo),
    FileItemInfoOffAddr_ASCIIPara_MinCur   = (FileItemInfoOffAddr_ASCIIPara_RatingVol  +  FileItemInfoLen_ASCIIPara_RatingVol),
    FileItemInfoOffAddr_ASCIIPara_TrCur   = (FileItemInfoOffAddr_ASCIIPara_MinCur   +  FileItemInfoLen_ASCIIPara_MinCur),
    FileItemInfoOffAddr_ASCIIPara_RatingCur   = (FileItemInfoOffAddr_ASCIIPara_TrCur   +  FileItemInfoLen_ASCIIPara_TrCur),
    FileItemInfoOffAddr_ASCIIPara_MaxCur      = (FileItemInfoOffAddr_ASCIIPara_RatingCur   +  FileItemInfoLen_ASCIIPara_RatingCur),
    FileItemInfoOffAddr_ASCIIPara_PGrade      = (FileItemInfoOffAddr_ASCIIPara_MaxCur      +  FileItemInfoLen_ASCIIPara_MaxCur),
    FileItemInfoOffAddr_ASCIIPara_QGrade      = (FileItemInfoOffAddr_ASCIIPara_PGrade      +  FileItemInfoLen_ASCIIPara_PGrade),
    FileItemInfoOffAddr_ASCIIPara_MeterModel  = (FileItemInfoOffAddr_ASCIIPara_QGrade     +  FileItemInfoLen_ASCIIPara_QGrade),
    FileItemInfoOffAddr_ASCIIPara_ProductDate = (FileItemInfoOffAddr_ASCIIPara_MeterModel  +  FileItemInfoLen_ASCIIPara_MeterModel),
    FileItemInfoOffAddr_ASCIIPara_PtVer       = (FileItemInfoOffAddr_ASCIIPara_ProductDate +  FileItemInfoLen_ASCIIPara_ProductDate),
    FileItemInfoOffAddr_ASCIIPara_SoftVer     = (FileItemInfoOffAddr_ASCIIPara_PtVer       +  FileItemInfoLen_ASCIIPara_PtVer),
    FileItemInfoOffAddr_ASCIIPara_FirmVer     = (FileItemInfoOffAddr_ASCIIPara_SoftVer     +  FileItemInfoLen_ASCIIPara_SoftVer),
    FileItemInfoOffAddr_ASCIIPara_FactoryNo   = (FileItemInfoOffAddr_ASCIIPara_FirmVer     +  FileItemInfoLen_ASCIIPara_FirmVer),
    FileItemInfoOffAddr_ASCIIPara_SoftWare    = (FileItemInfoOffAddr_ASCIIPara_FactoryNo   +  FileItemInfoLen_ASCIIPara_FactoryNo),
    FileItemInfoOffAddr_ASCIIPara_SoftWareInfo   = (FileItemInfoOffAddr_ASCIIPara_SoftWare +  FileItemInfoLen_ASCIIPara_SoftWare),
    FileItemInfoOffAddr_ASCIIPara_ServerVer   = (FileItemInfoOffAddr_ASCIIPara_SoftWareInfo    +  FileItemInfoLen_ASCIIPara_SoftWareInfo),
    FileItemInfoOffAddr_ASCIIPara_FactoryMAC = (FileItemInfoOffAddr_ASCIIPara_ServerVer   +  FileItemInfoLen_ASCIIPara_ServerVer),
    FileItemInfoOffAddr_ASCIIPara_end               = (FileItemInfoOffAddr_ASCIIPara_FactoryMAC   +  FileItemInfoLen_ASCIIPara_FactoryMAC)
} eFileItemInfo_ASCIIPara_TypeDef;//
typedef enum
{
    //项长度
    FileItemInfoLen_HighState_tEvRstDec                 = (1),
    FileItemInfoLen_HighState_GataCheckFlag     = (2),
    FileItemInfoLen_HighState_FactoryFlag       = (1),
    FileItemInfoLen_HighState_GateOffRemainTime = (2),
    FileItemInfoLen_HighState_GataOffStat       = (1),
    FileItemInfoLen_HighState_PowDnMoneySta     = (1),
    FileItemInfoLen_HighState_LocalOpenFlag     = (1),
    FileItemInfoLen_HighState_Gata_Do     = (2),
    FileItemInfoLen_HighState_Gata_Err     = (2),
    FileItemInfoLen_HighState_BroatStatue     = (sizeof(sBroatStatue_TypeDef)),
    FileItemInfoLen_HighState_PrgQ1_Cnt     = 4,    //无功1编程次数
    FileItemInfoLen_HighState_PrgQ2_Cnt     = 4,    //无功2编程次数
    FileItemInfoLen_HighState_EvtSumTime        = 4 * MAX_EVENTTYPE,
    FileItemInfoLen_HighState_EvtRcdBfEsam      = (8),
    FileItemInfoLen_HighState_EvtRcdAftEsam     = (8),
    FileItemInfoLen_HighState_MngPlugSta        = (2),
    FileItemInfoLen_HighState_EvtFlag       = (4),
    FileItemInfoLen_HighState_EvtMngStr     = (FileItemInfoLen_HighState_EvtRcdBfEsam + FileItemInfoLen_HighState_EvtRcdAftEsam + FileItemInfoLen_HighState_MngPlugSta + FileItemInfoLen_HighState_EvtFlag),
    FileItemInfoLen_HighState_EvtPwn        = (sizeof(sEvtPwnCoverTailTypedef)),
    FileItemInfoLen_HighState_PwdnVoltLoss  = (sizeof(sPwdnVoltCurTypedef)),

    //项偏移地址
    FileItemInfoOffAddr_HighState_tEvRstDec                   = (0),
    FileItemInfoOffAddr_HighState_GataCheckFlag     = (FileItemInfoOffAddr_HighState_tEvRstDec                   + FileItemInfoLen_HighState_tEvRstDec),
    FileItemInfoOffAddr_HighState_FactoryFlag       = (FileItemInfoOffAddr_HighState_GataCheckFlag     + FileItemInfoLen_HighState_GataCheckFlag),
    FileItemInfoOffAddr_HighState_GateOffRemainTime = (FileItemInfoOffAddr_HighState_FactoryFlag       + FileItemInfoLen_HighState_FactoryFlag),
    FileItemInfoOffAddr_HighState_GataOffStat       = (FileItemInfoOffAddr_HighState_GateOffRemainTime + FileItemInfoLen_HighState_GateOffRemainTime),
    FileItemInfoOffAddr_HighState_PowDnMoneySta     = (FileItemInfoOffAddr_HighState_GataOffStat       + FileItemInfoLen_HighState_GataOffStat),
    FileItemInfoOffAddr_HighState_LocalOpenFlag     = (FileItemInfoOffAddr_HighState_PowDnMoneySta     + FileItemInfoLen_HighState_PowDnMoneySta),
    FileItemInfoOffAddr_HighState_Gata_Do   = (FileItemInfoOffAddr_HighState_LocalOpenFlag     + FileItemInfoLen_HighState_LocalOpenFlag),
    FileItemInfoOffAddr_HighState_Gata_Err      = (FileItemInfoOffAddr_HighState_Gata_Do     + FileItemInfoLen_HighState_Gata_Do),
    FileItemInfoOffAddr_HighState_BroatStatue   = (FileItemInfoOffAddr_HighState_Gata_Err     + FileItemInfoLen_HighState_Gata_Err),
    FileItemInfoOffAddr_HighState_PrgQ1_Cnt     = (FileItemInfoOffAddr_HighState_BroatStatue     + FileItemInfoLen_HighState_BroatStatue),
    FileItemInfoOffAddr_HighState_PrgQ2_Cnt     = (FileItemInfoOffAddr_HighState_PrgQ1_Cnt     + FileItemInfoLen_HighState_PrgQ1_Cnt),
    FileItemInfoOffAddr_HighState_EvtSumTime = (FileItemInfoOffAddr_HighState_PrgQ2_Cnt     + FileItemInfoLen_HighState_PrgQ2_Cnt),
    FileItemInfoOffAddr_HighState_EvtRcdBfEsam = (FileItemInfoOffAddr_HighState_EvtSumTime     + FileItemInfoLen_HighState_EvtSumTime),
    FileItemInfoOffAddr_HighState_EvtRcdAfterEsam = (FileItemInfoOffAddr_HighState_EvtRcdBfEsam     + FileItemInfoLen_HighState_EvtRcdBfEsam),
    FileItemInfoOffAddr_HighState_MngPlugSta = (FileItemInfoOffAddr_HighState_EvtRcdAfterEsam     + FileItemInfoLen_HighState_EvtRcdAftEsam),
    FileItemInfoOffAddr_HighState_EvtFlag = (FileItemInfoOffAddr_HighState_MngPlugSta     + FileItemInfoLen_HighState_MngPlugSta),
    FileItemInfoOffAddr_HighState_EvtPwn = (FileItemInfoOffAddr_HighState_EvtFlag     + FileItemInfoLen_HighState_EvtFlag),

    FileItemInfoOffAddr_HighState_PwdnVoltLoss = (FileItemInfoOffAddr_HighState_EvtPwn  + FileItemInfoLen_HighState_EvtPwn),

    FileItemInfoOffAddr_HighState_end           = (FileItemInfoOffAddr_HighState_PwdnVoltLoss  + FileItemInfoLen_HighState_PwdnVoltLoss),

    FileItemInfoLen_HighState_TotalLen        = FileItemInfoOffAddr_HighState_end
} eFileItemInfo_HighState_TypeDef;//

typedef enum
{
    //项长度
    FileItemInfoLen_HighPara_PExpression    = (1),
    FileItemInfoLen_HighPara_PtQExpression  = (1),
    FileItemInfoLen_HighPara_NtQExpression  = (1),
    FileItemInfoLen_HighPara_PConstE     = (4),
    FileItemInfoLen_HighPara_QConstE     = (4),
    FileItemInfoLen_HighPara_MeterNo                = (sizeof(sDF12)),
    FileItemInfoLen_HighPara_CT                     = (4),
    FileItemInfoLen_HighPara_PT                     = (4),
    FileItemInfoLen_HighPara_WireMode           = (1),
    FileItemInfoLen_HighPara_StartCur           = (4),
    FileItemInfoLen_HighPara_CriticalVol        = (2),
    FileItemInfoLen_HighPara_UserNo             =   6,//(   sizeof( sDF12   )   ),
    FileItemInfoLen_HighPara_CardSerial     = (8),
    FileItemInfoLen_HighPara_MeterRunFlag   = (1),
    FileItemInfoLen_HighPara_tIRPrg                 = (4),
    FileItemInfoLen_HighPara_tTerminalPrg       = (4),
    FileItemInfoLen_HighPara_tEvRstDely     = (1),
    FileItemInfoLen_HighPara_GataSafeCur    = (4),
    FileItemInfoLen_HighPara_tSafeGata      = (2),
    FileItemInfoLen_HighPara_GateOffDelayTime   = (2),
    FileItemInfoLen_HighPara_ParaVolYield   = (sizeof(sVolYieldPara_TypeDef)),
    FileItemInfoLen_HighPara_RTCDota0          = (sizeof(sRTCParaE2_TypeDef)),
    FileItemInfoLen_HighPara_RTCAdj            = 4,
    FileItemInfoLen_HighPara_RTCCalData      = 10,
    FileItemInfoLen_HighPara_FristPowOnBak2     = (4),
    FileItemInfoLen_HighPara_Crc        = (2),
    //项偏移地址tTerminalDly
    FileItemInfoOffAddr_HighPara_PExpression         = (0),
    FileItemInfoOffAddr_HighPara_PtQExpression     = (FileItemInfoOffAddr_HighPara_PExpression         + FileItemInfoLen_HighPara_PExpression),
    FileItemInfoOffAddr_HighPara_NtQExpression     = (FileItemInfoOffAddr_HighPara_PtQExpression     + FileItemInfoLen_HighPara_PtQExpression),
    FileItemInfoOffAddr_HighPara_PConstE                   = (FileItemInfoOffAddr_HighPara_NtQExpression     + FileItemInfoLen_HighPara_NtQExpression),
    FileItemInfoOffAddr_HighPara_QConstE                   = (FileItemInfoOffAddr_HighPara_PConstE       +       FileItemInfoLen_HighPara_PConstE),
    FileItemInfoOffAddr_HighPara_MeterNo                   = (FileItemInfoOffAddr_HighPara_QConstE                   + FileItemInfoLen_HighPara_QConstE),
    FileItemInfoOffAddr_HighPara_CT                        = (FileItemInfoOffAddr_HighPara_MeterNo                   + FileItemInfoLen_HighPara_MeterNo),
    FileItemInfoOffAddr_HighPara_PT                        = (FileItemInfoOffAddr_HighPara_CT                        + FileItemInfoLen_HighPara_CT),
    FileItemInfoOffAddr_HighPara_WireMode              = (FileItemInfoOffAddr_HighPara_PT                        + FileItemInfoLen_HighPara_PT),
    FileItemInfoOffAddr_HighPara_StartCur              = (FileItemInfoOffAddr_HighPara_WireMode              + FileItemInfoLen_HighPara_WireMode),
    FileItemInfoOffAddr_HighPara_CriticalVol           = (FileItemInfoOffAddr_HighPara_StartCur              + FileItemInfoLen_HighPara_StartCur),
    FileItemInfoOffAddr_HighPara_UserNo                = (FileItemInfoOffAddr_HighPara_CriticalVol         + FileItemInfoLen_HighPara_CriticalVol),
    FileItemInfoOffAddr_HighPara_CardSerial        = (FileItemInfoOffAddr_HighPara_UserNo                + FileItemInfoLen_HighPara_UserNo),
    FileItemInfoOffAddr_HighPara_MeterRunFlag      = (FileItemInfoOffAddr_HighPara_CardSerial        + FileItemInfoLen_HighPara_CardSerial),
    FileItemInfoOffAddr_HighPara_tIRPrg                = (FileItemInfoOffAddr_HighPara_MeterRunFlag       +  FileItemInfoLen_HighPara_MeterRunFlag),
    FileItemInfoOffAddr_HighPara_tTerminalPrg        = (FileItemInfoOffAddr_HighPara_tIRPrg                  + FileItemInfoLen_HighPara_tIRPrg),
    FileItemInfoOffAddr_HighPara_tEvRstDely        = (FileItemInfoOffAddr_HighPara_tTerminalPrg       +  FileItemInfoLen_HighPara_tTerminalPrg),
    FileItemInfoOffAddr_HighPara_GataSafeCur           = (FileItemInfoOffAddr_HighPara_tEvRstDely        + FileItemInfoLen_HighPara_tEvRstDely),
    FileItemInfoOffAddr_HighPara_tSafeGata             = (FileItemInfoOffAddr_HighPara_GataSafeCur       + FileItemInfoLen_HighPara_GataSafeCur),
    FileItemInfoOffAddr_HighPara_GateOffDelayTime = (FileItemInfoOffAddr_HighPara_tSafeGata          + FileItemInfoLen_HighPara_tSafeGata),
    FileItemInfoOffAddr_HighPara_ParaVolYield      = (FileItemInfoOffAddr_HighPara_GateOffDelayTime + FileItemInfoLen_HighPara_GateOffDelayTime),
    FileItemInfoOffAddr_HighPara_RTCDota0          = (FileItemInfoOffAddr_HighPara_ParaVolYield            + FileItemInfoLen_HighPara_ParaVolYield),
    FileItemInfoOffAddr_HighPara_RTCAdj            = (FileItemInfoOffAddr_HighPara_RTCDota0        + FileItemInfoLen_HighPara_RTCDota0),
    FileItemInfoOffAddr_HighPara_RTCCalData       = (FileItemInfoOffAddr_HighPara_RTCAdj           + FileItemInfoLen_HighPara_RTCAdj),
    FileItemInfoOffAddr_HighPara_FristPowOnBak2  = (FileItemInfoOffAddr_HighPara_RTCCalData + FileItemInfoLen_HighPara_RTCCalData),
    FileItemInfoOffAddr_HighPara_Crc              = (FileItemInfoOffAddr_HighPara_FristPowOnBak2   + FileItemInfoLen_HighPara_FristPowOnBak2),
    FileItemInfoOffAddr_HighPara_end              = (FileItemInfoOffAddr_HighPara_Crc  + FileItemInfoLen_HighPara_Crc)
} eFileItemInfo_HighPara_TypeDef;//高级参数文件

typedef enum
{
    //项长度
    FileItemInfoLen_SecretPara_SecretPara   = (40),
    FileItemInfoLen_SecretPara_nPswRetry        = (1),
    FileItemInfoLen_SecretPara_tPswFailClose        = (2),
    FileItemInfoLen_SecretPara_tPrgKeyValid = (2),
    FileItemInfoLen_SecretPara_tPrgKeyLock  = (2),
    FileItemInfoLen_SecretPara_SafeModeFlag = (1),
    FileItemInfoLen_SecretPara_SafeModePara =   sizeof(sSafeModePara_TypeDef),
    FileItemInfoLen_SecretPara_AuthOn       =   1,
    FileItemInfoLen_SecretPara_FuncationItem    = (32),
    FileItemInfoLen_SecretPara_Labour   = (32),
    FileItemInfoLen_SecretPara_FristPowOnBak1   = (4),

    //项偏移地址
    FileItemInfoOffAddr_SecretPara_SecretPara   = (0),
    FileItemInfoOffAddr_SecretPara_nPswRetry     = (FileItemInfoOffAddr_SecretPara_SecretPara      +    FileItemInfoLen_SecretPara_SecretPara),
    FileItemInfoOffAddr_SecretPara_tPswFailClose = (FileItemInfoOffAddr_SecretPara_nPswRetry     +  FileItemInfoLen_SecretPara_nPswRetry),
    FileItemInfoOffAddr_SecretPara_tPrgKeyValid  = (FileItemInfoOffAddr_SecretPara_tPswFailClose +  FileItemInfoLen_SecretPara_tPswFailClose),
    FileItemInfoOffAddr_SecretPara_tPrgKeyLock   = (FileItemInfoOffAddr_SecretPara_tPrgKeyValid  +  FileItemInfoLen_SecretPara_tPrgKeyValid),
    FileItemInfoOffAddr_SecretPara_SafeModeFlag  = (FileItemInfoOffAddr_SecretPara_tPrgKeyLock       +  FileItemInfoLen_SecretPara_tPrgKeyLock),
    FileItemInfoOffAddr_SecretPara_SafeModePara  = (FileItemInfoOffAddr_SecretPara_SafeModeFlag  +  FileItemInfoLen_SecretPara_SafeModeFlag),
    FileItemInfoOffAddr_SecretPara_AuthOn        = (FileItemInfoOffAddr_SecretPara_SafeModePara  +  FileItemInfoLen_SecretPara_SafeModePara),
    FileItemInfoOffAddr_SecretPara_FuncationItem = (FileItemInfoOffAddr_SecretPara_AuthOn    +  FileItemInfoLen_SecretPara_AuthOn),
    FileItemInfoOffAddr_SecretPara_Labour          = (FileItemInfoOffAddr_SecretPara_FuncationItem +  FileItemInfoLen_SecretPara_FuncationItem),
    FileItemInfoOffAddr_SecretPara_FristPowOnBak1 = (FileItemInfoOffAddr_SecretPara_Labour    +  FileItemInfoLen_SecretPara_Labour),
    FileItemInfoOffAddr_SecretPara_End           = (FileItemInfoOffAddr_SecretPara_FristPowOnBak1   +   FileItemInfoLen_SecretPara_FristPowOnBak1)
} eFileItemInfo_SecretPara_TypeDef;//密码参数

typedef enum
{
    //项长度
    FileItemInfoLen_FirmPara_FractionI         = 1,
    FileItemInfoLen_FirmPara_FractionU         = 1,
    FileItemInfoLen_FirmPara_FractionE         = 1,
    FileItemInfoLen_FirmPara_FractionP         = 1,
    FileItemInfoLen_FirmPara_Pulse_deltaE      = 2,
    FileItemInfoLen_FirmPara_HighPulseRate   = 1,
    FileItemInfoLen_FirmPara_HFConst1            = 2,
    FileItemInfoLen_FirmPara_Start_Ps            = 2,
    FileItemInfoLen_FirmPara_Start_Q               = 2,
    FileItemInfoLen_FirmPara_ELostVoltT      = 2,
    FileItemInfoLen_FirmPara_Zxot                = 2,
    FileItemInfoLen_FirmPara_PRth                  = 8,
    FileItemInfoLen_FirmPara_PHSU                  = 3,
    FileItemInfoLen_FirmPara_PHSI                  = 12,
    FileItemInfoLen_FirmPara_GSU                   = 6,
    FileItemInfoLen_FirmPara_GSI                   = 8,
    FileItemInfoLen_FirmPara_U_OS                  = 6,
    FileItemInfoLen_FirmPara_I_OS                  = 8,
    FileItemInfoLen_FirmPara_GP                  = 6,
    FileItemInfoLen_FirmPara_GQ                  = 6,
    FileItemInfoLen_FirmPara_GS                  = 6,
    FileItemInfoLen_FirmPara_P_PHS               = 6,
    FileItemInfoLen_FirmPara_Q_PHS               = 6,
    FileItemInfoLen_FirmPara_P_OS                = 6,
    FileItemInfoLen_FirmPara_Q_OS                = 6,
    FileItemInfoLen_FirmPara_P_PHSMH             = 24,
    FileItemInfoLen_FirmPara_Q_PHSMH             = 24,
    FileItemInfoLen_FirmPara_ChkSum1             = 4,
    FileItemInfoLen_FirmPara_KUrms             = 4,
    FileItemInfoLen_FirmPara_KIArms            = 4,
    FileItemInfoLen_FirmPara_KPrms             = 4,
    FileItemInfoLen_FirmPara_RatedU            = 2,
    FileItemInfoLen_FirmPara_RatedUrms       = 4,
    FileItemInfoLen_FirmPara_RatedI            = 2,
    FileItemInfoLen_FirmPara_RatedIrms       = 4,
    FileItemInfoLen_FirmPara_RealU               = 12,
    FileItemInfoLen_FirmPara_RealI               = 16,
    FileItemInfoLen_FirmPara_RealAngle       = 12,
    FileItemInfoLen_FirmPara_RealPw            = 12,
    FileItemInfoLen_FirmPara_Send_nPoint        = 2,
    FileItemInfoLen_FirmPara_Crc                    = 2,

    FileItemInfoLen_VoltRepair_EnOrDis       =  1,
    FileItemInfoLen_VoltRepair_Rep           =  nPhs * MAX_VOLT_STEP,
    FileItemInfoLen_VoltRepair_Crc           =  2,
    FileItemInfoLen_VoltRepair_RN8302TIRM            =  2,
    FileItemInfoLen_VoltRepair_RN8207DTIRM           =  nPhs * 2,

    FileItemInfoLen_Harmonic_FftGP           =  nPhs * (41 * 2 + 2),  //-多2字节为了与RAM对齐 ---
    FileItemInfoLen_Harmonic_FftCosAngle             =  nPhs * 41 * 4,
    FileItemInfoLen_Harmonic_Crc             =  4,

    // dyf 增加南瑞中天特有参数
    FileItemInfoLen_Xiebo_Flag_EnOrDis          = 1,
    FileItemInfoLen_Xiebo_Err                   = 8,
    FileItemInfoLen_Xiebo_Value                 = 24,
    FileItemInfoLen_Xiebo_Mid_Current           = 4,

    //项偏移地址
    FileItemInfoOffAddr_FirmPara_FractionI        = (0),
    FileItemInfoOffAddr_FirmPara_FractionU        = (FileItemInfoOffAddr_FirmPara_FractionI         + FileItemInfoLen_FirmPara_FractionI),
    FileItemInfoOffAddr_FirmPara_FractionE        = (FileItemInfoOffAddr_FirmPara_FractionU         + FileItemInfoLen_FirmPara_FractionU),
    FileItemInfoOffAddr_FirmPara_FractionP        = (FileItemInfoOffAddr_FirmPara_FractionE         + FileItemInfoLen_FirmPara_FractionE),
    FileItemInfoOffAddr_FirmPara_Pulse_deltaE     = (FileItemInfoOffAddr_FirmPara_FractionP         + FileItemInfoLen_FirmPara_FractionP),
    FileItemInfoOffAddr_FirmPara_HighPulseRate  = (FileItemInfoOffAddr_FirmPara_Pulse_deltaE    + FileItemInfoLen_FirmPara_Pulse_deltaE),
    FileItemInfoOffAddr_FirmPara_HFConst1         = (FileItemInfoOffAddr_FirmPara_HighPulseRate + FileItemInfoLen_FirmPara_HighPulseRate),
    FileItemInfoOffAddr_FirmPara_Start_Ps         = (FileItemInfoOffAddr_FirmPara_HFConst1      + FileItemInfoLen_FirmPara_HFConst1),
    FileItemInfoOffAddr_FirmPara_Start_Q            = (FileItemInfoOffAddr_FirmPara_Start_Ps        + FileItemInfoLen_FirmPara_Start_Ps),
    FileItemInfoOffAddr_FirmPara_ELostVoltT     = (FileItemInfoOffAddr_FirmPara_Start_Q           + FileItemInfoLen_FirmPara_Start_Q),
    FileItemInfoOffAddr_FirmPara_Zxot               = (FileItemInfoOffAddr_FirmPara_ELostVoltT    + FileItemInfoLen_FirmPara_ELostVoltT),
    FileItemInfoOffAddr_FirmPara_PRth                 = (FileItemInfoOffAddr_FirmPara_Zxot            + FileItemInfoLen_FirmPara_Zxot),
    FileItemInfoOffAddr_FirmPara_PHSU                 = (FileItemInfoOffAddr_FirmPara_PRth              + FileItemInfoLen_FirmPara_PRth),
    FileItemInfoOffAddr_FirmPara_PHSI                 = (FileItemInfoOffAddr_FirmPara_PHSU              + FileItemInfoLen_FirmPara_PHSU),
    FileItemInfoOffAddr_FirmPara_GSU                  = (FileItemInfoOffAddr_FirmPara_PHSI              + FileItemInfoLen_FirmPara_PHSI),
    FileItemInfoOffAddr_FirmPara_GSI                  = (FileItemInfoOffAddr_FirmPara_GSU               + FileItemInfoLen_FirmPara_GSU),
    FileItemInfoOffAddr_FirmPara_U_OS               = (FileItemInfoOffAddr_FirmPara_GSI                 + FileItemInfoLen_FirmPara_GSI),
    FileItemInfoOffAddr_FirmPara_I_OS               = (FileItemInfoOffAddr_FirmPara_U_OS              + FileItemInfoLen_FirmPara_U_OS),
    FileItemInfoOffAddr_FirmPara_GP                 = (FileItemInfoOffAddr_FirmPara_I_OS              + FileItemInfoLen_FirmPara_I_OS),
    FileItemInfoOffAddr_FirmPara_GQ                 = (FileItemInfoOffAddr_FirmPara_GP                + FileItemInfoLen_FirmPara_GP),
    FileItemInfoOffAddr_FirmPara_GS                 = (FileItemInfoOffAddr_FirmPara_GQ                + FileItemInfoLen_FirmPara_GQ),
    FileItemInfoOffAddr_FirmPara_P_PHS            = (FileItemInfoOffAddr_FirmPara_GS                  + FileItemInfoLen_FirmPara_GS),
    FileItemInfoOffAddr_FirmPara_Q_PHS            = (FileItemInfoOffAddr_FirmPara_P_PHS             + FileItemInfoLen_FirmPara_P_PHS),
    FileItemInfoOffAddr_FirmPara_P_OS               = (FileItemInfoOffAddr_FirmPara_Q_PHS           + FileItemInfoLen_FirmPara_Q_PHS),
    FileItemInfoOffAddr_FirmPara_Q_OS               = (FileItemInfoOffAddr_FirmPara_P_OS              + FileItemInfoLen_FirmPara_P_OS),
    FileItemInfoOffAddr_FirmPara_P_PHSMH          = (FileItemInfoOffAddr_FirmPara_Q_OS            + FileItemInfoLen_FirmPara_Q_OS),
    FileItemInfoOffAddr_FirmPara_Q_PHSMH          = (FileItemInfoOffAddr_FirmPara_P_PHSMH       + FileItemInfoLen_FirmPara_P_PHSMH),
    FileItemInfoOffAddr_FirmPara_ChkSum1          = (FileItemInfoOffAddr_FirmPara_Q_PHSMH       + FileItemInfoLen_FirmPara_Q_PHSMH),
    FileItemInfoOffAddr_FirmPara_KUrms            = (FileItemInfoOffAddr_FirmPara_ChkSum1       + FileItemInfoLen_FirmPara_ChkSum1),
    FileItemInfoOffAddr_FirmPara_KIArms         = (FileItemInfoOffAddr_FirmPara_KUrms           + FileItemInfoLen_FirmPara_KUrms),
    FileItemInfoOffAddr_FirmPara_KPrms            = (FileItemInfoOffAddr_FirmPara_KIArms          + FileItemInfoLen_FirmPara_KIArms),
    FileItemInfoOffAddr_FirmPara_RatedU           = (FileItemInfoOffAddr_FirmPara_KPrms             + FileItemInfoLen_FirmPara_KPrms),
    FileItemInfoOffAddr_FirmPara_RatedUrms      = (FileItemInfoOffAddr_FirmPara_RatedU          + FileItemInfoLen_FirmPara_RatedU),
    FileItemInfoOffAddr_FirmPara_RatedI           = (FileItemInfoOffAddr_FirmPara_RatedUrms       + FileItemInfoLen_FirmPara_RatedUrms),
    FileItemInfoOffAddr_FirmPara_RatedIrms      = (FileItemInfoOffAddr_FirmPara_RatedI          + FileItemInfoLen_FirmPara_RatedI),
    FileItemInfoOffAddr_FirmPara_RealU              = (FileItemInfoOffAddr_FirmPara_RatedIrms     + FileItemInfoLen_FirmPara_RatedIrms),
    FileItemInfoOffAddr_FirmPara_RealI              = (FileItemInfoOffAddr_FirmPara_RealU             + FileItemInfoLen_FirmPara_RealU),
    FileItemInfoOffAddr_FirmPara_RealAngle      = (FileItemInfoOffAddr_FirmPara_RealI             + FileItemInfoLen_FirmPara_RealI),
    FileItemInfoOffAddr_FirmPara_RealPw           = (FileItemInfoOffAddr_FirmPara_RealAngle       + FileItemInfoLen_FirmPara_RealAngle),
    FileItemInfoOffAddr_FirmPara_Send_nPoint        = (FileItemInfoOffAddr_FirmPara_RealPw    + FileItemInfoLen_FirmPara_RealPw),
    FileItemInfoOffAddr_FirmPara_Crc        = (FileItemInfoOffAddr_FirmPara_Send_nPoint    + FileItemInfoLen_FirmPara_Send_nPoint),

    FileItemInfoOffAddr_VoltRepair_EnOrDis      = (FileItemInfoOffAddr_FirmPara_Crc    + FileItemInfoLen_FirmPara_Crc),
    FileItemInfoOffAddr_VoltRepair_Rep              = (FileItemInfoOffAddr_VoltRepair_EnOrDis     + FileItemInfoLen_VoltRepair_EnOrDis),
    FileItemInfoOffAddr_VoltRepair_Crc              = (FileItemInfoOffAddr_VoltRepair_Rep             + FileItemInfoLen_VoltRepair_Rep),

    FileItemInfoOffAddr_VoltRepair_RN8302TIRM   = (FileItemInfoOffAddr_VoltRepair_Crc +   FileItemInfoLen_VoltRepair_Crc),
    FileItemInfoOffAddr_VoltRepair_RN8207DTIRM  = (FileItemInfoOffAddr_VoltRepair_RN8302TIRM  +   FileItemInfoLen_VoltRepair_RN8302TIRM),

    FileItemInfoOffAddr_Harmonic_FftGP      = (FileItemInfoOffAddr_VoltRepair_RN8207DTIRM   + FileItemInfoLen_VoltRepair_RN8207DTIRM),
    FileItemInfoOffAddr_Harmonic_FftCosAngle    = (FileItemInfoOffAddr_Harmonic_FftGP   + FileItemInfoLen_Harmonic_FftGP),
    FileItemInfoOffAddr_Harmonic_Crc        = (FileItemInfoOffAddr_Harmonic_FftCosAngle     + FileItemInfoLen_Harmonic_FftCosAngle),

    FileItemInfoOffAddr_FirmPara_Reversd    = (FileItemInfoOffAddr_Harmonic_Crc   +   FileItemInfoLen_Harmonic_Crc),

    // dyf 增加南瑞中天特有参数
    FileItemInfoOffAddr_Xiebo_Flag_EnOrDis  = (FileItemInfoOffAddr_FirmPara_Reversd + 200),
    FileItemInfoOffAddr_Xiebo_Err           = (FileItemInfoOffAddr_Xiebo_Flag_EnOrDis + FileItemInfoLen_Xiebo_Flag_EnOrDis),
    FileItemInfoOffAddr_Xiebo_Value         = (FileItemInfoOffAddr_Xiebo_Err + FileItemInfoLen_Xiebo_Err),
    FileItemInfoOffAddr_Xiebo_Mid_Current   = (FileItemInfoOffAddr_Xiebo_Value + FileItemInfoLen_Xiebo_Value),

    FileItemInfoOffAddr_FirmPara_End        = (FileItemInfoOffAddr_Xiebo_Mid_Current + FileItemInfoLen_Xiebo_Mid_Current),

    //------总长度-----------
    FileItemInfoLen__FirmPara_TotalLen      = FileItemInfoOffAddr_FirmPara_End + 128 - 37   // dyf预留128-37byte
} eFileItemInfo_FirmPara_TypeDef;//校表参数（可根据计量芯片更改?

typedef enum
{
    FileItemInfoLen_TemperSchoolPara_chan1  =   sizeof(sTemperSchoolParaItem_TypeDef),
    FileItemInfoLen_TemperSchoolPara_chan2  =   sizeof(sTemperSchoolParaItem_TypeDef),
    FileItemInfoLen_TemperSchoolPara_chan3  =   sizeof(sTemperSchoolParaItem_TypeDef),
    FileItemInfoLen_TemperSchoolPara_chan4  =   sizeof(sTemperSchoolParaItem_TypeDef),
    //项偏移地址
    FileItemInfoOffAddr_TemperSchoolPara_chan1  = (0),
    FileItemInfoOffAddr_TemperSchoolPara_chan2  = (FileItemInfoOffAddr_TemperSchoolPara_chan1  +   FileItemInfoLen_TemperSchoolPara_chan1),
    FileItemInfoOffAddr_TemperSchoolPara_chan3 = (FileItemInfoOffAddr_TemperSchoolPara_chan2 + FileItemInfoLen_TemperSchoolPara_chan2),
    FileItemInfoOffAddr_TemperSchoolPara_chan4 = (FileItemInfoOffAddr_TemperSchoolPara_chan3 + FileItemInfoLen_TemperSchoolPara_chan3),
    FileItemInfoOffAddr_TemperSchoolPara_End    = (FileItemInfoOffAddr_TemperSchoolPara_chan4      +   FileItemInfoLen_TemperSchoolPara_chan4),
} eFileItemInfo_TemperSchoolPara_TypeDef; //温度校准参数

typedef enum
{
    //项长度
    FileItemInfoLen_NvRam_FristPowOn    = (4),
    FileItemInfoLen_NvRam_pFile = (15),
    //项偏移地址
    FileItemInfoOffAddr_NvRam_FristPowOn    = (0),
    FileItemInfoOffAddr_NvRam_pFile     = (FileItemInfoOffAddr_NvRam_FristPowOn        +   FileItemInfoLen_NvRam_FristPowOn),
    FileItemInfoOffAddr_NvRam_End   = (FileItemInfoOffAddr_NvRam_pFile         +   FileItemInfoLen_NvRam_pFile)
} eFileItemInfo_NvRam_TypeDef;//存储器参数（铁电FM或AT）

typedef enum
{
    //项长度
    FileItemInfoLen_PowDn_PowDnTime     = (sizeof(sDate_time_s_TypeDef)),
    FileItemInfoLen_PowDn_EgPiece                 = (sizeof(sEgPiece_TypeDef)),
    FileItemInfoLen_PowDn_CheckMoneyFlag    = (1),
    FileItemInfoLen_PowDn_PownDnAllPEgSh    = (sizeof(u8) * (MAX_FL + 1)),
    FileItemInfoLen_PowDn_PownDnPtPEgSh = (sizeof(u8) * (MAX_FL + 1)),
    FileItemInfoLen_PowDn_PownDnNtPEgSh = (sizeof(u8) * (MAX_FL + 1)),
    FileItemInfoLen_PowDn_tWorkBat          =   4,
    FileItemInfoLen_PowDn_FrzDayTime        = (sizeof(sDate_time_s_TypeDef)),
    FileItemInfoLen_PowDn_FrzRmDayTime      = (sizeof(sDate_time_s_TypeDef)),
    FileItemInfoLen_PowDn_Irms      =   12,   //掉电全失压时ABC三相电流
    //项偏移地址
    FileItemInfoOffAddr_PowDn_PowDnTime     = (0),
    FileItemInfoOffAddr_PowDn_EgPiece   = (FileItemInfoOffAddr_PowDn_PowDnTime         +   FileItemInfoLen_PowDn_PowDnTime),
    FileItemInfoOffAddr_PowDn_PownDnAllPEgSh    = (FileItemInfoOffAddr_PowDn_EgPiece       +   FileItemInfoLen_PowDn_EgPiece),
    FileItemInfoOffAddr_PowDn_PownDnPtPEgSh     = (FileItemInfoOffAddr_PowDn_PownDnAllPEgSh        +   FileItemInfoLen_PowDn_PownDnAllPEgSh),
    FileItemInfoOffAddr_PowDn_PownDnNtPEgSh     = (FileItemInfoOffAddr_PowDn_PownDnPtPEgSh         +   FileItemInfoLen_PowDn_PownDnPtPEgSh),
    FileItemInfoOffAddr_PowDn_CheckMoneyFlag    = (FileItemInfoOffAddr_PowDn_PownDnNtPEgSh + FileItemInfoLen_PowDn_PownDnNtPEgSh),
    FileItemInfoOffAddr_PowDn_tWorkBat      = (FileItemInfoOffAddr_PowDn_CheckMoneyFlag        +   FileItemInfoLen_PowDn_CheckMoneyFlag),
    FileItemInfoOffAddr_PowDn_FrzDayTime    = (FileItemInfoOffAddr_PowDn_tWorkBat      +   FileItemInfoLen_PowDn_tWorkBat),
    FileItemInfoOffAddr_PowDn_FrzRmDayTime = (FileItemInfoOffAddr_PowDn_FrzDayTime        +   FileItemInfoLen_PowDn_FrzDayTime),
    FileItemInfoOffAddr_PowDn_Irms  = (FileItemInfoOffAddr_PowDn_FrzRmDayTime      +   FileItemInfoLen_PowDn_FrzRmDayTime),
    FileItemInfoOffAddr_PowDn_End   = (FileItemInfoOffAddr_PowDn_Irms      +   FileItemInfoLen_PowDn_Irms)
} eFileItemInfo_PowDn_TypeDef;//掉电数据存储定义

typedef enum
{
    //项长度

    FileItemInfoLen_BackUpCurMoney_CurSurplusMoney  = sizeof(sDF12),
    FileItemInfoLen_BackUpCurMoney_CurOverdraftMoney    = sizeof(sDF12),
    FileItemInfoLen_BackUpCurMoney_CurApplyEg           = sizeof(sFsEgSh_TypeDef),
    FileItemInfoLen_BackUpCurMoney_Rmday1ApplyEg        = sizeof(sFsEgSh_TypeDef),
    FileItemInfoLen_BackUpCurMoney_CurSurplusMoneyCrc   = sizeof(u16),
    FileItemInfoLen_BackUpCurMoney_CurApplyEgCrc        = sizeof(u16),
    FileItemInfoLen_BackUpCurMoney_OpCode               = 4,

    FileItemInfoLen_BackUpCurMoney_DateTime                 = (sizeof(sDate_time_s_TypeDef)),     //管理模组费率电能备份时间
    FileItemInfoLen_BackUpCurMoney_PtPEgSh              = (sizeof(sBackUpEnergy_TypeDef)),     //管理模组费率电能正向，预留12个费率空间
    FileItemInfoLen_BackUpCurMoney_NtPEgSh              = (sizeof(sBackUpEnergy_TypeDef)),     //管理模组费率电能反向，预留12个费率空间
    FileItemInfoLen_BackUpCurMoney_Qd1QEgSh             = (sizeof(sBackUpEnergy_TypeDef)),     //管理模组费率电能Q1，预留12个费率空间
    FileItemInfoLen_BackUpCurMoney_Qd2QEgSh             = (sizeof(sBackUpEnergy_TypeDef)),     //管理模组费率电能Q2，预留12个费率空间
    FileItemInfoLen_BackUpCurMoney_Qd3QEgSh             = (sizeof(sBackUpEnergy_TypeDef)),     //管理模组费率电能Q3，预留12个费率空间
    FileItemInfoLen_BackUpCurMoney_Qd4QEgSh             = (sizeof(sBackUpEnergy_TypeDef)),     //管理模组费率电能Q4，预留12个费率空间

    //项偏移地址
    FileItemInfoOffAddr_BackUpCurMoney_CurSurplusMoney  =   0,
    FileItemInfoOffAddr_BackUpCurMoney_CurOverdraftMoney = (FileItemInfoOffAddr_BackUpCurMoney_CurSurplusMoney   +   FileItemInfoLen_BackUpCurMoney_CurSurplusMoney),
    FileItemInfoOffAddr_BackUpCurMoney_CurApplyEg           = (FileItemInfoOffAddr_BackUpCurMoney_CurOverdraftMoney   +   FileItemInfoLen_BackUpCurMoney_CurOverdraftMoney),
    FileItemInfoOffAddr_BackUpCurMoney_Rmday1ApplyEg        = (FileItemInfoOffAddr_BackUpCurMoney_CurApplyEg  +   FileItemInfoLen_BackUpCurMoney_CurApplyEg),
    FileItemInfoOffAddr_BackUpCurMoney_CurSurplusMoneyCrc   = (FileItemInfoOffAddr_BackUpCurMoney_Rmday1ApplyEg   +   FileItemInfoLen_BackUpCurMoney_Rmday1ApplyEg),
    FileItemInfoOffAddr_BackUpCurMoney_CurApplyEgCrc        = (FileItemInfoOffAddr_BackUpCurMoney_CurSurplusMoneyCrc  +   FileItemInfoLen_BackUpCurMoney_CurSurplusMoneyCrc),
    FileItemInfoOffAddr_BackUpCurMoney_OpCode               = (FileItemInfoOffAddr_BackUpCurMoney_CurApplyEgCrc       +   FileItemInfoLen_BackUpCurMoney_CurApplyEgCrc),

    FileItemInfoOffAddr_BackUpCurMoney_DateTime                 = (FileItemInfoOffAddr_BackUpCurMoney_OpCode      +   FileItemInfoLen_BackUpCurMoney_OpCode),
    FileItemInfoOffAddr_BackUpCurMoney_PtPEgSh              = (FileItemInfoOffAddr_BackUpCurMoney_DateTime        +   FileItemInfoLen_BackUpCurMoney_DateTime),
    FileItemInfoOffAddr_BackUpCurMoney_NtPEgSh              = (FileItemInfoOffAddr_BackUpCurMoney_PtPEgSh         +   FileItemInfoLen_BackUpCurMoney_PtPEgSh),
    FileItemInfoOffAddr_BackUpCurMoney_Qd1QEgSh                 = (FileItemInfoOffAddr_BackUpCurMoney_NtPEgSh         +   FileItemInfoLen_BackUpCurMoney_NtPEgSh),
    FileItemInfoOffAddr_BackUpCurMoney_Qd2QEgSh                 = (FileItemInfoOffAddr_BackUpCurMoney_Qd1QEgSh        +   FileItemInfoLen_BackUpCurMoney_Qd1QEgSh),
    FileItemInfoOffAddr_BackUpCurMoney_Qd3QEgSh                 = (FileItemInfoOffAddr_BackUpCurMoney_Qd2QEgSh        +   FileItemInfoLen_BackUpCurMoney_Qd2QEgSh),
    FileItemInfoOffAddr_BackUpCurMoney_Qd4QEgSh                 = (FileItemInfoOffAddr_BackUpCurMoney_Qd3QEgSh        +   FileItemInfoLen_BackUpCurMoney_Qd3QEgSh),

    FileItemInfoOffAddr_BackUpCurMoney_End              = (FileItemInfoOffAddr_BackUpCurMoney_Qd4QEgSh        +   FileItemInfoLen_BackUpCurMoney_Qd4QEgSh)
} eFileItemInfo_BackUpCurMoney_TypeDef;//电能及剩余金额备份文件

typedef enum
{
    //项长度
    FileItemInfoLen_Stat_UaElig_Day     = (sizeof(sUEligStat_TypeDef)),
    FileItemInfoLen_Stat_UbElig_Day     = (sizeof(sUEligStat_TypeDef)),
    FileItemInfoLen_Stat_UcElig_Day     = (sizeof(sUEligStat_TypeDef)),
    FileItemInfoLen_Stat_UaElig_Month   = (sizeof(sUEligStat_TypeDef)),
    FileItemInfoLen_Stat_UbElig_Month   = (sizeof(sUEligStat_TypeDef)),
    FileItemInfoLen_Stat_UcElig_Month   = (sizeof(sUEligStat_TypeDef)),
    FileItemInfoLen_Stat_Misc   = (sizeof(sMiscStat_TypeDef)),

    //项偏移地址
    FileItemInfoOffAddr_Stat_UaElig_Day     = (0),
    FileItemInfoOffAddr_Stat_UbElig_Day     = (FileItemInfoOffAddr_Stat_UaElig_Day     +   FileItemInfoLen_Stat_UaElig_Day),
    FileItemInfoOffAddr_Stat_UcElig_Day     = (FileItemInfoOffAddr_Stat_UbElig_Day     +   FileItemInfoLen_Stat_UbElig_Day),
    FileItemInfoOffAddr_Stat_UaElig_Month   = (FileItemInfoOffAddr_Stat_UcElig_Day     +   FileItemInfoLen_Stat_UcElig_Day),
    FileItemInfoOffAddr_Stat_UbElig_Month   = (FileItemInfoOffAddr_Stat_UaElig_Month   +   FileItemInfoLen_Stat_UaElig_Month),
    FileItemInfoOffAddr_Stat_UcElig_Month   = (FileItemInfoOffAddr_Stat_UbElig_Month   +   FileItemInfoLen_Stat_UbElig_Month),
    FileItemInfoOffAddr_Stat_Misc       = (FileItemInfoOffAddr_Stat_UcElig_Month   +   FileItemInfoLen_Stat_UcElig_Month),

    FileItemInfoOffAddr_Stat_End        = (FileItemInfoOffAddr_Stat_Misc   +   FileItemInfoLen_Stat_Misc)
} eFileItemInfo_Stat_TypeDef; //电压合格率统计事件信息文件

typedef enum
{
    //项长度     关联对象属性表个数(1byte) + 一条事件记录长度(2byte) + N个关联对象属性( 默认支持OAD空间 + 预留OAD空间)
    FileItemInfoLen_EvtCtxlist_PowDn              =  sizeof(sCList5_TypeDef)        + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_Clr                =  sizeof(sCList24_TypeDef)     + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_SetClock       =  sizeof(sCList5_TypeDef)        + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_OpenCover        =    sizeof(sCList12_TypeDef)     + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_OpenTail         =    sizeof(sCList12_TypeDef)     + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_PrgSetPsw            =    sizeof(sCList5_TypeDef)    + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_BroadcastTime    =    sizeof(sCList5_TypeDef)    + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_MngPlug      =    sizeof(sCList14_TypeDef)     + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_MngUpdate        =    sizeof(sCList8_TypeDef)      + 5 * sizeof(sContextList_TypeDef),

    //项偏移地址
    FileItemInfoOffAddr_EvtCtxlist_PowDn             = (0),
    FileItemInfoOffAddr_EvtCtxlist_Clr               = (FileItemInfoOffAddr_EvtCtxlist_PowDn                + FileItemInfoLen_EvtCtxlist_PowDn),
    FileItemInfoOffAddr_EvtCtxlist_SetClock      = (FileItemInfoOffAddr_EvtCtxlist_Clr          + FileItemInfoLen_EvtCtxlist_Clr),
    FileItemInfoOffAddr_EvtCtxlist_OpenCover       = (FileItemInfoOffAddr_EvtCtxlist_SetClock       + FileItemInfoLen_EvtCtxlist_SetClock),
    FileItemInfoOffAddr_EvtCtxlist_OpenTail        = (FileItemInfoOffAddr_EvtCtxlist_OpenCover      + FileItemInfoLen_EvtCtxlist_OpenCover),
    FileItemInfoOffAddr_EvtCtxlist_PrgSetPsw         = (FileItemInfoOffAddr_EvtCtxlist_OpenTail + FileItemInfoLen_EvtCtxlist_OpenTail),
    FileItemInfoOffAddr_EvtCtxlist_BroadcastTime = (FileItemInfoOffAddr_EvtCtxlist_PrgSetPsw            + FileItemInfoLen_EvtCtxlist_PrgSetPsw),
    FileItemInfoOffAddr_EvtCtxlist_MngPlug = (FileItemInfoOffAddr_EvtCtxlist_BroadcastTime            + FileItemInfoLen_EvtCtxlist_BroadcastTime),
    FileItemInfoOffAddr_EvtCtxlist_MngUpdate = (FileItemInfoOffAddr_EvtCtxlist_MngPlug              + FileItemInfoLen_EvtCtxlist_MngPlug),
    FileItemInfoOffAddr_EvtCtxlist_end             = (FileItemInfoOffAddr_EvtCtxlist_MngUpdate              + FileItemInfoLen_EvtCtxlist_MngUpdate),
    //------总长度-----------
    FileItemInfoLen_EvtCtxlist_TotalLen            = FileItemInfoOffAddr_EvtCtxlist_end
} eFileItemInfo_EvtCtxlist_TypeDef; //事件记录关联对象属性表

typedef enum
{
    FileItemInfoLen_EvtCfgPara_PowDn             =  sizeof(sEvtCfgPara_TimeDly_TypeDef),
    FileItemInfoLen_EvtCfgPara_Clr               =  0,
    FileItemInfoLen_EvtCfgPara_SetClock      =  0,
    FileItemInfoLen_EvtCfgPara_OpenCover       =  0,
    FileItemInfoLen_EvtCfgPara_OpenTail        =  0,
    FileItemInfoLen_EvtCfgPara_PrgSetPsw         =  0,
    FileItemInfoLen_EvtCfgPara_BroadcastTime = 0,
    FileItemInfoLen_EvtCfgPara_MngPlug = 0,
    FileItemInfoLen_EvtCfgPara_MngUpdate = 0,
    FileItemInfoLen_EvtCfgPara_Crc                 = 2,

    //项偏移地址

    FileItemInfoOffAddr_EvtCfgPara_PowDn           = (0),
    FileItemInfoOffAddr_EvtCfgPara_Clr               = (FileItemInfoOffAddr_EvtCfgPara_PowDn                + FileItemInfoLen_EvtCfgPara_PowDn),
    FileItemInfoOffAddr_EvtCfgPara_SetClock      = (FileItemInfoOffAddr_EvtCfgPara_Clr          + FileItemInfoLen_EvtCfgPara_Clr),
    FileItemInfoOffAddr_EvtCfgPara_OpenCover       = (FileItemInfoOffAddr_EvtCfgPara_SetClock       + FileItemInfoLen_EvtCfgPara_SetClock),
    FileItemInfoOffAddr_EvtCfgPara_OpenTail        = (FileItemInfoOffAddr_EvtCfgPara_OpenCover      + FileItemInfoLen_EvtCfgPara_OpenCover),
    FileItemInfoOffAddr_EvtCfgPara_PrgSetPsw         = (FileItemInfoOffAddr_EvtCfgPara_OpenTail + FileItemInfoLen_EvtCfgPara_OpenTail),
    FileItemInfoOffAddr_EvtCfgPara_BroadcastTime = (FileItemInfoOffAddr_EvtCfgPara_PrgSetPsw            + FileItemInfoLen_EvtCfgPara_PrgSetPsw),
    FileItemInfoOffAddr_EvtCfgPara_MngPlug = (FileItemInfoOffAddr_EvtCfgPara_BroadcastTime            + FileItemInfoLen_EvtCfgPara_BroadcastTime),
    FileItemInfoOffAddr_EvtCfgPara_MngUpdate = (FileItemInfoOffAddr_EvtCfgPara_MngPlug              + FileItemInfoLen_EvtCfgPara_MngPlug),
    FileItemInfoOffAddr_EvtCfgPara_Crc             = (FileItemInfoOffAddr_EvtCfgPara_MngUpdate              + FileItemInfoLen_EvtCfgPara_MngUpdate),
    FileItemInfoOffAddr_EvtCfgPara_end             = (FileItemInfoOffAddr_EvtCfgPara_Crc              + FileItemInfoLen_EvtCfgPara_Crc)
} eFileItemInfo_EvtCfgPara_TypeDef; //事件配置参数

typedef enum
{
    //项长度

    FileItemInfoLen_EvtRcdHead_PowDn                = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_Clr                  = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_SetClock         = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_OpenCover      = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_OpenTail      = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_PrgSetPsw          = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_BroadcastTime  = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_MngPlug  = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_MngUpdate  = sizeof(sEvtRcdHead_TypeDef),

    //项偏移地址

    FileItemInfoOffAddr_EvtRcdHead_PowDn           = (0),
    FileItemInfoOffAddr_EvtRcdHead_Clr                 = (FileItemInfoOffAddr_EvtRcdHead_PowDn      + FileItemInfoLen_EvtRcdHead_PowDn),
    FileItemInfoOffAddr_EvtRcdHead_SetClock        = (FileItemInfoOffAddr_EvtRcdHead_Clr        + FileItemInfoLen_EvtRcdHead_Clr),
    FileItemInfoOffAddr_EvtRcdHead_OpenCover       = (FileItemInfoOffAddr_EvtRcdHead_SetClock       + FileItemInfoLen_EvtRcdHead_SetClock),
    FileItemInfoOffAddr_EvtRcdHead_OpenTail       = (FileItemInfoOffAddr_EvtRcdHead_OpenCover       + FileItemInfoLen_EvtRcdHead_OpenCover),
    FileItemInfoOffAddr_EvtRcdHead_PrgSetPsw         = (FileItemInfoOffAddr_EvtRcdHead_OpenTail + FileItemInfoLen_EvtRcdHead_OpenTail),
    FileItemInfoOffAddr_EvtRcdHead_BroadcastTime   = (FileItemInfoOffAddr_EvtRcdHead_PrgSetPsw      + FileItemInfoLen_EvtRcdHead_PrgSetPsw),
    FileItemInfoOffAddr_EvtRcdHead_MngPlug   = (FileItemInfoOffAddr_EvtRcdHead_BroadcastTime        + FileItemInfoLen_EvtRcdHead_BroadcastTime),
    FileItemInfoOffAddr_EvtRcdHead_MngUpdate   = (FileItemInfoOffAddr_EvtRcdHead_MngPlug        + FileItemInfoLen_EvtRcdHead_MngPlug),
    FileItemInfoOffAddr_EvtRcdHead_end             = (FileItemInfoOffAddr_EvtRcdHead_MngUpdate      + FileItemInfoLen_EvtRcdHead_MngUpdate),

    FileItemInfoLen_EvtRcdHead_TotalLen                      = FileItemInfoOffAddr_EvtRcdHead_end
} eFileItemInfo_EvtRcdHead_TypeDef;  //事件记录头文件

//----------事件记录 单条事件记录长度----------------------
#define  CLIST_OverCur_RCDLEN    52  // =最后一个OAD偏移地址 + OAD数据长度
#define  CLIST2_RCDLEN    26
#define  CLISTZone_RCDLEN    64
#define  CLISTWeek_RCDLEN    19
#define  CLISTPrgP_RCDLEN    19
#define  CLISTPrgQ_RCDLEN    21
#define  CLISTDay_RCDLEN    24
#define  CLISTSetPsw_RCDLEN  34
#define  CLIST4_RCDLEN    34
#define  CLIST5_RCDLEN    42
#define  CLISTNERR_RCDLEN    26

#define  CLISTPrg_RCDLEN  74
#define  CLISTPrgTab_RCDLEN  22 + 42
#define  CLISTPrgHldy_RCDLEN  28

#define  CLISTRate_RCDLEN    50
#define  CLISTLad_RCDLEN    138
#define  CLISTCardErr_RCDLEN  34
#define  CLISTBuy_RCDLEN   42
#define  CLISTRtrn_RCDLEN  30
#define  CLISTGateOff_RCDLEN    42

#define  CLIST0_RCDLEN    18 + 8  //预留2个4byte电量空间

#define  MAX_RCDLEN     2*CLISTLad_RCDLEN   //单条事件记录的最大长度

#define     Evt_PowDn_RCDLen        26
#define     Evt_Clr_RCDLen          114             // ThreePhase---114   singnlPhase---42
#define     Evt_SetClock_RCDLen     26
#define     Evt_OpenCover_RCDLen    66
#define     Evt_OpenTail_RCDLen     50
#define     Evt_PrgSetPsw_RCDLen    34
#define     Evt_BroadcastTime_RCDLen    26
#define     Evt_MngPlug_RCDLen      84
#define     Evt_MngUpdate_RCDLen    220//124

typedef enum
{
    //项长度
    FileItemInfoLen_EvtRecord_PowDn             =   4096 * 2,       //预留2个bank，确保擦除一个bank后仍满足最大记录条数
    FileItemInfoLen_EvtRecord_Clr             = 4096 * 2,
    FileItemInfoLen_EvtRecord_SetClock        = 4096 * 2,
    FileItemInfoLen_EvtRecord_OpenCover     =   4096 * 2,
    FileItemInfoLen_EvtRecord_OpenTail     =    4096 * 2,
    FileItemInfoLen_EvtRecord_PrgSetPsw       = 4096 * 2,
    FileItemInfoLen_EvtRecord_BroadcastTime =   4096 * 2,
    FileItemInfoLen_EvtRecord_MngPlug     = 4096 * 2,
    FileItemInfoLen_EvtRecord_MngUpdate       = 4096 * 2,

    //项偏移地址

    FileItemInfoOffAddr_EvtRecord_PowDn         = (0),
    FileItemInfoOffAddr_EvtRecord_Clr           = (FileItemInfoOffAddr_EvtRecord_PowDn   + FileItemInfoLen_EvtRecord_PowDn),
    FileItemInfoOffAddr_EvtRecord_SetClock      = (FileItemInfoOffAddr_EvtRecord_Clr      + FileItemInfoLen_EvtRecord_Clr),
    FileItemInfoOffAddr_EvtRecord_OpenCover     = (FileItemInfoOffAddr_EvtRecord_SetClock       + FileItemInfoLen_EvtRecord_SetClock),
    FileItemInfoOffAddr_EvtRecord_OpenTail     = (FileItemInfoOffAddr_EvtRecord_OpenCover       + FileItemInfoLen_EvtRecord_OpenCover),
    FileItemInfoOffAddr_EvtRecord_PrgSetPsw       = (FileItemInfoOffAddr_EvtRecord_OpenTail + FileItemInfoLen_EvtRecord_OpenTail),
    FileItemInfoOffAddr_EvtRecord_BroadcastTime = (FileItemInfoOffAddr_EvtRecord_PrgSetPsw        + FileItemInfoLen_EvtRecord_PrgSetPsw),
    FileItemInfoOffAddr_EvtRecord_MngPlug = (FileItemInfoOffAddr_EvtRecord_BroadcastTime        + FileItemInfoLen_EvtRecord_BroadcastTime),
    FileItemInfoOffAddr_EvtRecord_MngUpdate = (FileItemInfoOffAddr_EvtRecord_MngPlug      + FileItemInfoLen_EvtRecord_MngPlug),
    FileItemInfoOffAddr_EvtRecord_end               = (FileItemInfoOffAddr_EvtRecord_MngUpdate      + FileItemInfoLen_EvtRecord_MngUpdate),

    FileItemInfoLen_EvtRecord_TotalLen  =   FileItemInfoOffAddr_EvtRecord_end
} eFileItemInfo_EvtRecord_TypeDef;  //事件记录

#define    MAX_PowDnEvt_FlashCnt    (FileItemInfoLen_EvtRecord_PowDn/Evt_PowDn_RCDLen)
#define    MAX_ClrEvt_FlashCnt          (FileItemInfoLen_EvtRecord_Clr/Evt_Clr_RCDLen)
#define    MAX_SetClockEvt_FlashCnt (FileItemInfoLen_EvtRecord_SetClock/Evt_SetClock_RCDLen)
#define    MAX_OpenCoverEvt_FlashCnt    (FileItemInfoLen_EvtRecord_OpenCover/Evt_OpenCover_RCDLen)
#define    MAX_OpenTailEvt_FlashCnt (FileItemInfoLen_EvtRecord_OpenTail/Evt_OpenTail_RCDLen)
#define    MAX_PrgSetPswEvt_FlashCnt    (FileItemInfoLen_EvtRecord_PrgSetPsw/Evt_PrgSetPsw_RCDLen)
#define    MAX_BroadcastTimeEvt_FlashCnt    (FileItemInfoLen_EvtRecord_BroadcastTime/Evt_BroadcastTime_RCDLen)
#define    MAX_MngPlugEvt_FlashCnt  (FileItemInfoLen_EvtRecord_MngPlug/Evt_MngPlug_RCDLen)
#define    MAX_MngUpdateEvt_FlashCnt    (FileItemInfoLen_EvtRecord_MngUpdate/Evt_MngUpdate_RCDLen)

//--------冻结---------------
typedef enum
{
    FileItemInfoNum_Frz_MinFrz            = 0,      //分钟冻结
    FileItemInfoNum_Frz_MAX =   1,
} eFileItemInfoNum_Frz_TypeDef;   //

typedef enum
{
    //项长度     关联对象属性表个数(1byte) + 一条事件记录长度(2byte) + N个关联对象属性( 默认支持OAD空间 + 预留OAD空间)
    FileItemInfoLen_FrzCtxlist_Min       =   sizeof(sFrzMinList_TypeDef) + 5 * sizeof(sFrzCtxList_TypeDef),
    //项偏移地址

    FileItemInfoOffAddr_FrzCtxlist_Min       = (0),
    FileItemInfoOffAddr_FrzCtxlist_end       = (FileItemInfoOffAddr_FrzCtxlist_Min       +  FileItemInfoLen_FrzCtxlist_Min),
    //------总长度-----------
    FileItemInfoLen_FrzCtxlist_TotalLen     = FileItemInfoOffAddr_FrzCtxlist_end
} eFileItemInfo_FrzCtxlist_TypeDef;

typedef enum
{
    //项长度
    FileItemInfoLen_FrzRcdHead_Min       =   sizeof(sFrzRcdHead_TypeDef),
    //项偏移地址
    FileItemInfoOffAddr_FrzRcdHead_Min       = (0),
    FileItemInfoOffAddr_FrzRcdHead_end       = (FileItemInfoOffAddr_FrzRcdHead_Min       +  FileItemInfoLen_FrzRcdHead_Min),
    //------总长度-----------
    FileItemInfoLen_FrzRcdHead_TotalLen     = FileItemInfoOffAddr_FrzRcdHead_end
} eFileItemInfo_FrzRcdHead_TypeDef;

typedef enum
{
    //项长度
    FileItemInfoLen_FrzMinLine0Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine1Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine2Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine3Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine4Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine5Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine6Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine7Head = sizeof(sFrzMinHead_TypeDef),

    //项偏移地址
    FileItemInfoOffAddr_FrzMinLine0Head    = (0),
    FileItemInfoOffAddr_FrzMinLine1Head    = (FileItemInfoOffAddr_FrzMinLine0Head  +  FileItemInfoLen_FrzMinLine0Head),
    FileItemInfoOffAddr_FrzMinLine2Head    = (FileItemInfoOffAddr_FrzMinLine1Head  +  FileItemInfoLen_FrzMinLine1Head),
    FileItemInfoOffAddr_FrzMinLine3Head    = (FileItemInfoOffAddr_FrzMinLine2Head  +  FileItemInfoLen_FrzMinLine2Head),
    FileItemInfoOffAddr_FrzMinLine4Head    = (FileItemInfoOffAddr_FrzMinLine3Head  +  FileItemInfoLen_FrzMinLine3Head),
    FileItemInfoOffAddr_FrzMinLine5Head    = (FileItemInfoOffAddr_FrzMinLine4Head  +  FileItemInfoLen_FrzMinLine4Head),
    FileItemInfoOffAddr_FrzMinLine6Head    = (FileItemInfoOffAddr_FrzMinLine5Head  +  FileItemInfoLen_FrzMinLine5Head),
    FileItemInfoOffAddr_FrzMinLine7Head    = (FileItemInfoOffAddr_FrzMinLine6Head  +  FileItemInfoLen_FrzMinLine6Head),
    FileItemInfoOffAddr_FrzMinLineHead_end = (FileItemInfoOffAddr_FrzMinLine7Head  +  FileItemInfoLen_FrzMinLine7Head),
    //------总长度-----------
    FileItemInfoLen_FrzMinLineHead_TotalLen     = FileItemInfoOffAddr_FrzMinLineHead_end
} eFileItemInfo_FrzMinLineHead_TypeDef;

//---------冻结关联对象属性表-----------------------
#define FRZSTDLISTLEN   11    //----=4+7------
//----------冻结记录 预留单条事件记录最大长度----------------------
#define  FRZWINKRCDLEN              (FRZSTDLISTLEN+16*(DEFAULT_FL+1) + 8)  //
#define  FRZMINRCDLEN                   (FRZSTDLISTLEN*2+138)//
#define  FRZHOURRCDLEN                  (FRZSTDLISTLEN+ 16) //
#define  FRZDAYRCDLEN                   (FRZSTDLISTLEN+16*(MAX_FL+1) + 8) //
#define  FRZRMDAYRCDLEN             (FRZSTDLISTLEN+24*(MAX_FL+1) + 4)   //
#define  FRZMONTHRCDLEN             (FRZSTDLISTLEN+24*(MAX_FL+1))   //
#define  FRZLADDERRCDLEN            (FRZSTDLISTLEN + 4)  //15
#define  FRZTZONESWRCDLEN           (FRZSTDLISTLEN+16*(MAX_FL+1) + 8)   //
#define  FRZPOTSWRCDLEN             FRZTZONESWRCDLEN  //所有切换冻结默认长度和默认关联对象属性表完全一致
#define  FRZRATEPRICESWRCDLEN   FRZTZONESWRCDLEN
#define  FRZLADDERSWRCDLEN      FRZTZONESWRCDLEN
#define  Len_FrzRecord_Min1        (((u32)(FRZSTDLISTLEN+ 74) * (u32)MAX_FRZMIN_RECORD1 + 4096 + 4096)&0xFFFFF000)  //每条曲线预留一个bank，确保擦除一个bank不影响最大记录条数
#define  Len_FrzRecord_Min2        (((u32)(FRZSTDLISTLEN+ 64) * (u32)MAX_FRZMIN_RECORD2 + 4096 + 4096)&0xFFFFF000)

typedef enum
{
    //项长度     关联对象属性表个数(1byte) + 一条事件记录长度(2byte) + N个关联对象属性( 默认支持OAD空间 + 预留OAD空间)

    FileItemInfoLen_FrzRecord_Min       = (Len_FrzRecord_Min1 + Len_FrzRecord_Min2),
    //项偏移地址
    FileItemInfoOffAddr_FrzRecord_Min       = (0),

    FileItemInfoOffAddr_FrzRecord_end       = (FileItemInfoOffAddr_FrzRecord_Min       +  FileItemInfoLen_FrzRecord_Min),
    //------总长度-----------
    FileItemInfoLen_FrzRecord_TotalLen      = FileItemInfoOffAddr_FrzRecord_end
} eFileItemInfo_FrzRecord_TypeDef;
//===定义文件信息==========================================
#define FRAM_SADDR  FM24C_START_ADDR

#define FLASH_SADDR AT45DB_START_ADDR

#define SocEE_SADDR SocEE_START_ADDR

#define AT1024_SADDR AT1024_START_ADDR

typedef enum
{
    //文件编号
    FileId_NvRam        =   0,
    FileId_FirmPara =   1,
    FileId_TemperSchoolPara =   2,
    FileId_HighPara =   3,
    FileId_SecretPara   =   4,
    FileId_RatePara =   5,

    FileId_ParaDoc  =   6,
    FileId_ParaCom  =   7,
    FileId_ParaDisp =   8,
    FileId_ParaWaste    =   9,
    FileId_ParaOutput   =   10,
    FileId_ParaCipherKey    =   11,
    FileId_EvtReport    =   12,

    FileId_ParaASCII    =   13,
    FileId_HighState    =   14,

    FileId_EgSh     =   15,

    FileId_InterTmp =   16,
    FileId_CurStat  =   17,
    FileId_PowDnDataMemory = 18,
    FileId_BackUpEgSh = 19,
    FileId_BackUpCurMoney = 20,

    FileId_EvtCtxlist = 21,     //事件记录关联对象属性表
    FileId_EvtCfgPara = 22, //事件记录配置参数
    FileId_EvtRcdHead = 23,     //事件记录
    FileId_EvtRecord        =   24,     //事件记录

    FileId_FrzCtxlist = 25,     //
    FileId_FrzRcdHead = 26,     //
    FileId_FrzMinLineHead = 27,     //分钟冻结(最大8条)曲线头信息
    FileId_FrzRecord        =   28,     //

    FileId_Max          =   29,

    //文件长度
    FileLen_NvRam   = (sizeof(sNvRamFile_TypeDef)),
    FileLen_FirmPara    = FileItemInfoLen__FirmPara_TotalLen,
    FileLen_TemperSchoolPara    = sizeof(sTemperSchoolPara_TypeDef),
    FileLen_HighPara    = (sizeof(sHighParaFile_TypeDef)),
    FileLen_SecretPara  = (sizeof(sSecretParaFile_TypeDef)),
    FileLen_RatePara    =   0,

    FileLen_ParaDoc     = (sizeof(sDocment_TypeDef)),
    FileLen_ParaCom     = (sizeof(sComPara_TypeDef)),
    FileLen_ParaDisp        = (sizeof(sDispPara_TypeDef)),
    FileLen_ParaWaste       = (sizeof(sWastePara_TypeDef)),
    FileLen_ParaOutput  = (sizeof(sOutputPara_TypeDef)),
    FileLen_ParaCipherKey   = (sizeof(sCipherKeyPara_TypeDef)),
    FileLen_EvtReport       = (sizeof(sEvtReport_TypeDef)),

    FileLen_ParaASCII       = (sizeof(sASCIIParaFile_TypeDef)),
    FileLen_HighState       =   FileItemInfoLen_HighState_TotalLen,

    FileLen_EgSh    =   FileItemInfoLen_EgSh_TotalLen,   //128*2  页对齐

    FileLen_InterTmp    = (sizeof(sDl645InterTmpFile_TypeDef)),
    FileLen_CurStat = (sizeof(sStatFile_TypeDef)),
    FileLen_PowDnDataMemory = (sizeof(sPowDnFile_TypeDef)),
    FileLen_BackUpEgSh = FileItemInfoLen_EgSh_TotalLen,
    FileLen_BackUpCurMoney = (sizeof(sBackUpCurMoneyFile_TypeDef)),

    FileLen_EvtCtxlist  =   FileItemInfoLen_EvtCtxlist_TotalLen,
    FileLen_EvtCfgPara  = (sizeof(sTrim_TypeDef)),
    FileLen_EvtRcdHead  =   FileItemInfoLen_EvtRcdHead_TotalLen,
    FileLen_EvtRecord   =   FileItemInfoLen_EvtRecord_TotalLen,

    FileLen_FrzCtxlist  =   FileItemInfoLen_FrzCtxlist_TotalLen,
    FileLen_FrzRcdHead  =   FileItemInfoLen_FrzRcdHead_TotalLen,
    FileLen_FrzMinLineHead  =   FileItemInfoLen_FrzMinLineHead_TotalLen,
    FileLen_FrzRecord   =   FileItemInfoLen_FrzRecord_TotalLen,

    //文件起始地址
    //由于枚举数据值有限制，所以文件起始地址用#define定义
} eFileInfo_TypeDef;

//----FRAM_ADDR 定义----
//参数变量存储地址定义
#define FileAddr_FRAM_Start     (   FRAM_SADDR      )

#define FileAddr_FirmPara           (   FileAddr_FRAM_Start )
#define FileAddr_TemperSchoolPara   (   FileAddr_FirmPara           +   FileLen_FirmPara )
#define FileAddr_NvRam              (   FileAddr_TemperSchoolPara           +   FileLen_TemperSchoolPara        )
#define FileAddr_EgSh           (   (FileAddr_NvRam +   FileLen_NvRam + 63)/64*64 )  //页对齐，避免掉电写E2时翻页

#define FileAddr_InterTmp           (   FileAddr_EgSh           +   FileLen_EgSh    )
#define FileAddr_CurStat                (   FileAddr_InterTmp       +   FileLen_InterTmp    )
#define FileAddr_PowDnDataMemory    (   (FileAddr_CurStat + FileLen_CurStat + 63)/64*64 )
#define FileAddr_BackUpEgSh     (   (FileAddr_PowDnDataMemory +  FileLen_PowDnDataMemory    + 63)/64*64 ) //页对齐
#define FileAddr_BackUpCurMoney     (   FileAddr_BackUpEgSh         +   FileLen_BackUpEgSh  )

#define FileAddr_HighPara           (   FileAddr_BackUpCurMoney     +   FileLen_BackUpCurMoney  )
#define FileAddr_SecretPara     (   FileAddr_HighPara           +   FileLen_HighPara    )
#define FileAddr_RatePara           (   FileAddr_SecretPara     +   FileLen_SecretPara )

#define FileAddr_ParaDoc        (   FileAddr_RatePara       +   FileLen_RatePara    )
#define FileAddr_ParaCom        (   FileAddr_ParaDoc        +   FileLen_ParaDoc )
#define FileAddr_ParaDisp       (   FileAddr_ParaCom        +   FileLen_ParaCom )
#define FileAddr_ParaWaste      (   FileAddr_ParaDisp       +   FileLen_ParaDisp    )
#define FileAddr_ParaOutput     (   FileAddr_ParaWaste      +   FileLen_ParaWaste   )
#define FileAddr_ParaCipherKey      (   FileAddr_ParaOutput         +   FileLen_ParaOutput  )
#define FileAddr_EvtReport      (   FileAddr_ParaCipherKey      +   FileLen_ParaCipherKey   )

#define FileAddr_ParaASCII      (   FileAddr_EvtReport      +   FileLen_EvtReport   )
#define FileAddr_HighState      (   FileAddr_ParaASCII      +   FileLen_ParaASCII   )

#define FileAddr_ParaEnd            (   FileAddr_HighState+ FileLen_HighState)
#define FileAddr_FRAM_End           (   FileAddr_ParaEnd    )

// SOC内部EEPROM 定义
// #define  FileAddr_SocEE_Start    (   (u32)SocEE_SADDR    )
// #define  FileAddr_FirmPara       (   SocEE_SADDR )

//----------------------
#define FileAddr_EvtCtxlist (   FileAddr_ParaEnd        )
#define FileAddr_EvtCfgPara (   FileAddr_EvtCtxlist +   FileLen_EvtCtxlist  )
#define FileAddr_EvtRcdHead (   FileAddr_EvtCfgPara +   FileLen_EvtCfgPara  )

#define FileAddr_FrzCtxlist (   FileAddr_EvtRcdHead +   FileLen_EvtRcdHead  )
#define FileAddr_FrzRcdHead (   FileAddr_FrzCtxlist +   FileLen_FrzCtxlist  )
#define FileAddr_FrzMinLineHead (   FileAddr_FrzRcdHead +   FileLen_FrzRcdHead  )

#define FileAddr_SADDR_End      (   FileAddr_FrzMinLineHead +   FileLen_FrzMinLineHead  )

//--------------------------
#define FileAddr_FLASH_Start    (   (u32)FLASH_SADDR    )  //冻结和事件记录存flash

#define FileAddr_EvtRecord      (   FileAddr_FLASH_Start    )
#define FileAddr_FrzRecord      (   FileAddr_EvtRecord  + FileLen_EvtRecord )

#define FileAddr_FLASH_End      (   FileAddr_FrzRecord + FileItemInfoLen_FrzRecord_TotalLen )

typedef enum
{
    File_FirstInit      = 0x00,  //烧录程序后,第一次初始化
    File_CommInit       = 0x01   //通讯命令初始化，不初始化计量参数，通讯地址，资产管理编码
} eFileInitMode_TypeDef; //初始化方式

typedef struct
{
    u32 OffAddr;
    u32 Len;
} sFileItemInfo_TypeDef;

typedef struct
{
    u32 StartAddr;
    u32 Len;
    const sFileItemInfo_TypeDef *pItemInfo; //文件项信息
} sFileInfo_TypeDef;

typedef struct
{
    u8  Item;
    u8   *Addr;
    u16 Len;
} sRecord_ParaDefault_TypeDef;
//------------------------
extern ErrorStatus fnFile_Read(u8 FileId, u32 OffAddr, void *Dst, u32 Len);
extern ErrorStatus fnFile_Write(u8 FileId, u32 OffAddr, void *Src, u32 Len);
extern ErrorStatus fnFile_Clr(u8 FileId);
extern ErrorStatus fnFileItem_Read(u8 FileId, u8 nItem, void *Dst);
extern ErrorStatus fnFileItem_Write(u8 FileId, u8 nItem, void *Src);

extern void fnFile_Init(u8 Flag);

extern const sFileInfo_TypeDef FileInfo[];
extern const sFileItemInfo_TypeDef FileItemInfo_EvtCtxlist[];
extern const sFileItemInfo_TypeDef FileItemInfo_EvtCfgPara[];
extern const sFileItemInfo_TypeDef FileItemInfo_EvtRcdHead[];
extern const sFileItemInfo_TypeDef FileItemInfo_EvtRecord[];
//extern const sHighParaFile_TypeDef HighParaDefault;
//extern const sASCIIParaFile_TypeDef ASCIIParaDefault;

extern const sFileItemInfo_TypeDef FileItemInfo_FrzCtxlist[];
extern const sFileItemInfo_TypeDef FileItemInfo_FrzRcdHead[];
extern const sFileItemInfo_TypeDef FileItemInfo_FrzRecord[];
extern const sFileItemInfo_TypeDef FileItemInfo_FrzMinLineHead[];
//extern const sTrim_TypeDef EvtCfgParaDefault;

#define StrMemOffset(StrName , Member) offsetof(StrName , Member)   //使用 offsetof 函数可避免编译器报警
#define StrMemOffset2(StrName1 , Member1 , StrMember1 , Member2)     (StrMemOffset(StrName1 , Member1) + StrMemOffset(StrMember1 , Member2) )
#define StrMemOffset3(StrName1 , Member1 , StrMember1 , Member2 , StrMember2 , Member3)  (StrMemOffset(StrName1 , Member1) + StrMemOffset(StrMember1 , Member2) + StrMemOffset(StrMember2 , Member3) )
#define StrMemOffset4(StrName1 , Member1 , StrMember1 , Member2 , StrMember2 , Member3 , StrMember3 , Member4)   (StrMemOffset(StrName1 , Member1) + StrMemOffset(StrMember1 , Member2) + StrMemOffset(StrMember2 , Member3) + StrMemOffset(StrMember3 , Member4) )
// 结构成员长度计算
#define StrMemSizeOf(StrName , Member) (sizeof( ( (StrName *)0)->Member) )  // 计算结构体成员大小
#define StrMemSizeOf2(StrName , Member1 , Member2) (sizeof( ( (StrName *)0)->Member1.Member2) )
#define StrMemSizeOf3(StrName , Member1 , Member2 , Member3) (sizeof( ( (StrName *)0)->Member1.Member2.Member3) )
#define StrMemSizeOf4(StrName , Member1 , Member2 , Member3 , Member4) (sizeof( ( (StrName *)0)->Member1.Member2.Member3.Member4) )

#endif // _DL645_FILE_H
