
#define  DL645_FILE_GLOBALS
#include <App.h>
#include "ProDefine.h"

//=========保护区数据,不参与比对==================

// --------------------------------3P4-----------------------------------
#if(METERTYPE == 0)
// 智能表

#endif
#if(METERTYPE == 1)
//远程费控表
const sDocment_TypeDef DocParaDefault _reserve =
{
    0x00, 15, 0x01, 80, nHarmonic, 60, 300, 0x00, 0x00
};
const sComPara_TypeDef ComParaDefault =
{
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
    2, 2, 6, 6, 6, 0x00
};

const sDispPara_TypeDef DispParaDefault _reserve =
{
    5,      //上电全屏显示时间
    60,     //背光点亮时间 60
    10,     //显示查看背光点亮时间10
    30,     //无电按键屏幕驻留最大时间30
    2,      //显示电能小数位数
    4,      //显示功率小数位数
    0,      //液晶②①字样意义
    5,      //循显屏数
    23,     //按键显示屏数
    5,
    60,
    {
        //屏序号  OAD              主OAD-------
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, //轮显项
        0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x00, 0x00, 0x00,
    },
    {
        //屏序号  OAD             CSD-------
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, //键显项(，客户编号和表号分两屏)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x02, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x03, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x04, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x05, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x01, 0x04, 0x00, 0x00, 0x02, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x02, 0x04, 0x00, 0x00, 0x02, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x03, 0x04, 0x00, 0x00, 0x02, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x04, 0x04, 0x00, 0x00, 0x02, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x05, 0x04, 0x00, 0x00, 0x02, 0x02, 0x05, 0x50, 0x01,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x40, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x40, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40, 0x00, //
        0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x01, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0A, 0x20, 0x00,
    },
};

const sOutputPara_TypeDef OutputParaDefault _reserve =
{
    0x00c8, 0x0003,
    0x8000, 0x0004,
    0x0050, 0x0010,
    0x8000, 0x0100,
    0x8000, 0x1000,
    0x8000, 0x2000,
    0x400c, 0x0021, 0x0021, 0x0021, 0x0003,
    0x400c, 0x0021, 0x0021, 0x0021, 0x0003,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

const u8 CipherKeyParaDefault[3] =
{
    0x14, 0x00, 0x00
};
//---------主动上报----------
const sEvtRptPara_TypeDef EvtReportDefault _reserve =
{
    0x01,
    0x00,
    {0x03, 0x04, 0x80, 0x00, 0x00, 0x00, 0x00, },

    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, },

    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, },

    0x01,

    0x00,

    {0x09, 0x00, 0x00 },

    0x00
};
#endif
#if(METERTYPE == 2)
// 本地费控表

#endif

const sTemperSchoolPara_TypeDef TemperSchoolParaDefault _reserve =
{
    {
        {0, 10000, 0},
        {0, 10000, 0},
        {0, 10000, 0},
        {0, 10000, 0}
    }
};

const sHighParaFile_TypeDef HighParaDefault _reserve =
{
    0x05,
    0x41,
    0x14,

    {MeterConst},  //2000 脉冲常数
    {MeterConst},  //2000

    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00},           // 表号
    0x01,           // CT
    0x01,           // PT
    0x00,           // 0--三相四线  1--三相三线
    0x50,
    1320,

    {0x12, 0x34, 0x56, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    0x00,
    30,
    30,
    30,
    300000,
    1440,
    30,
    {2640, 1540, 2354, 2046, 0},

    0x0000,         /*"u16 RTCDota0; 2次曲线初始频率偏差"*/
    2,      /*"u16 CurveMode; 曲线模式" dyf 电碳表默认2次曲线，校准Dota0 */
    0,      /*"u16    DATA0;4次或者3次曲线初始频率偏差"*/
    0,      /*"u16    XT1;晶振温度曲线顶点温度"*/
    0,      /*"u16    ALPHA;晶振一次温度系数"*/
    0,      /*"u16    BETA;晶振二次温度系数"*/
    0,      /*"u16    GAMMA;晶振三次温度系数"*/
    0,      /*"u16    ZETA;晶振四次温度系数"*/

    {0x00, 0x00, 0x00, 0x00}, //RTCAdj
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //RTCCalData

    {0x00, 0x00, 0x00, 0x00},
};

const sASCIIParaFile_TypeDef ASCIIParaDefault _reserve =
{
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {"00000000000000000000000000000000"},
    #if (HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_577)
    {"57.7V"},
    #else
    {"220.0V"},
    #endif
    #if (RateIb == 15000)
    {"0.015A"},
    {"0.075A"},
    #else
    {"0.400A"},
    {"1.000A"},
    #endif
    #if ((HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_577)||(HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_220_1_5))
    {"1.500A"},
    {"6.000A"},
    #else
    {"10.00A"},
    {"100.0A"},
    #endif
    {'B', 0x00, 0x00, 0x00}, // dyf 有功默认B级
    {'2', '.', '0', 0x00},  // dyf 无功默认2.0级

    {"DTZYXXX-X"},
    {0, 0, 0, 10, 6, 2023},
    {"DL/T698.45-2017-WL20"},

    {"00000000000000000000000000000000"},
    {"00000000000000000000000000000000"},
    {"00000000000000000000000000000000"},
    {"AAAAAAAAAAAAAAAA"},
    {"XX", "0001", 1, "20230620", 1, "0123456789ABCDEF"},
    {"00000000000000000000000000000000"},
    {"00000000000000000000000000000000"},
};
//------------------------------------------------------------------------

const sSecretParaFile_TypeDef SecretParaDefault _reserve =
{
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x78, 0x56, 0x34,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    3,
    1440,
    240,
    0,

    1,
    {
        0x00,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, //显式安全模式字
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
    },

    0x01,  //需要身份认证

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00
};
//------事件记录-----------------
const   sTrim_TypeDef EvtCfgParaDefault _reserve =
{
    //---------配置参数---------------
    {720000, 60 },  //720000
    { 0 },
    { 0 },
    { 60 },
    { 0 },
    { 10000, 5000, 60 }
};

//-------过流-8项默认关联对象属性表--------
const   sCList8_TypeDef EvtCListOverCurDefault _reserve =
{
    8, CLIST_OverCur_RCDLEN,

    0x00102201, 4,    18,
    0x00202201, 4,    22,

    0x20002200, 2,    26,
    0x20012200, 4,      28,
    0x20042200, 8,      32,
    0x200A2200, 4,     40,

    0x00108201, 4,    44,
    0x00208201, 4,    48,
};

const sCList14_TypeDef EvtMngPlugCListDefault _reserve =
{
    14, Evt_MngPlug_RCDLen,
    0xF1002200, 8,    18,               // 原ESAM序列号
    0x00102201, 4,    26,               // 拔掉时刻正向有功总电能
    0x00202201, 4,    30,               // 拔掉时刻反向有功总电能
    0x00502201, 4,    34,               // 拔掉时刻第I象限无功电能
    0x00602201, 4,    38,               // 拔掉时刻第II象限无功电能
    0x00702201, 4,    42,               // 拔掉时刻第III象限无功电能
    0x00802201, 4,    46,               // 拔掉时刻第IV象限无功电能
    0xF1008200, 8,    52,               // 新ESAM序列号     注意更新Event.h中宏定义
    0x00108201, 4,    60,               // 插上时刻正向有功总电能
    0x00208201, 4,    64,               // 插上时刻反向有功总电能
    0x00508201, 4,    68,               // 插上时刻第I象限无功电能
    0x00608201, 4,    72,               // 插上时刻第II象限无功电能
    0x00708201, 4,    76,               // 插上时刻第III象限无功电能
    0x00808201, 4,    80,               // 插上时刻第IV象限无功电能
};

const sCList8_TypeDef EvtMngUpdateCListDefault _reserve =
{
    8, Evt_MngUpdate_RCDLen,
    0x40272300, 1,    18,               // 升级操作类型
    0x00102200, 52,   19,               // 升级前正向有功总电能
    0x00202200, 52,   71,               // 升级前反向有功总电能
    0xF0012500, 32,   123,              // 下载方标识
    0xF4022204, 16,   155,              // 升级前软件版本号
    0xF4028204, 16,   171,              // 升级后软件版本号
    0xF4028202, 32,   187,              // 升级应用名称
    0x40278200, 1,    219,              // 升级结果
};

const sCList12_TypeDef EvtOpenCoverCListDefault _reserve =
{
    12, Evt_OpenCover_RCDLen,
    0x00102201, 4,    18,               // 开盖前正向有功总电能
    0x00202201, 4,    22,               // 开盖前反向有功总电能
    0x00502201, 4,    26,               // 开盖前第I象限无功电能
    0x00602201, 4,    30,               // 开盖前第II象限无功电能
    0x00702201, 4,    34,               // 开盖前第III象限无功电能
    0x00802201, 4,    38,               // 开盖前第IV象限无功电能
    0x00108201, 4,    42,
    0x00208201, 4,    46,
    0x00508201, 4,    50,               // 开盖后第I象限无功电能
    0x00608201, 4,    54,               // 开盖后第II象限无功电能
    0x00708201, 4,    58,               // 开盖后第III象限无功电能
    0x00808201, 4,    62,               // 开盖后第IV象限无功电能
};

//const sCList6_TypeDef EvtMeterClrCListDefault _reserve =
//{
//  6 , Evt_Clr_RCDLen ,
//  0x00102201 , 4 ,    18 ,
//  0x00202201 , 4 ,    22 ,
//  0x00502201 , 4 ,    26 ,            // 清零前第I象限无功电能
//  0x00602201 , 4 ,    30 ,            // 清零前第II象限无功电能
//  0x00702201 , 4 ,    34 ,            // 清零前第III象限无功电能
//  0x00802201 , 4 ,    38 ,            // 清零前第IV象限无功电能
//};

#if(nPhs==ThreePhs)
// ThreePhase
const sCList24_TypeDef EvtMeterClrCListDefault _reserve =
{
    24, Evt_Clr_RCDLen,                 // 114
    0x00102201, 4,    18,
    0x00202201, 4,    22,
    0x00502201, 4,    26,               // 清零前第I象限无功电能
    0x00602201, 4,    30,               // 清零前第II象限无功电能
    0x00702201, 4,    34,               // 清零前第III象限无功电能
    0x00802201, 4,    38,               // 清零前第IV象限无功电能

    0x00112201, 4,    42,               // 清零前A相正向有功电能
    0x00212201, 4,    46,               // 清零前A相反向有功电能
    0x00512201, 4,    50,               // 清零前A相第I象限无功电能
    0x00612201, 4,    54,               // 清零前A相第II象限无功电能
    0x00712201, 4,    58,               // 清零前A相第III象限无功电能
    0x00812201, 4,    62,               // 清零前A相第IV象限无功电能

    0x00122201, 4,    66,               // 清零前B相正向有功电能
    0x00222201, 4,    70,               // 清零前B相反向有功电能
    0x00522201, 4,    74,               // 清零前B相第I象限无功电能
    0x00622201, 4,    78,               // 清零前B相第II象限无功电能
    0x00722201, 4,    82,               // 清零前B相第III象限无功电能
    0x00822201, 4,    86,               // 清零前B相第IV象限无功电能

    0x00132201, 4,    90,               // 清零前C相正向有功电能
    0x00232201, 4,    94,               // 清零前C相反向有功电能
    0x00532201, 4,    98,               // 清零前C相第I象限无功电能
    0x00632201, 4,    102,              // 清零前C相第II象限无功电能
    0x00732201, 4,    106,              // 清零前C相第III象限无功电能
    0x00832201, 4,    110,              // 清零前C相第IV象限无功电能
};
#endif

//------掉电，校时,电源异常，计量芯片故障，广播校时-2项默认关联对象属性表--------
//------电表清零-跳闸--合闸----------
const   sCList2_TypeDef EvtCList2Default _reserve =
{
    2, CLIST2_RCDLEN,
    0x00102201, 4,    18,
    0x00202201, 4,    22
};

//------时区表编程-1项默认关联对象属性表--------
const   sCList1_TypeDef EvtCListZoneDefault _reserve =
{
    1, CLISTZone_RCDLEN,
    0x40152200, 42, 18
};

//------周休日编程-1项默认关联对象属性表--------
const   sCList1_TypeDef EvtCListWeekDefault _reserve =
{
    1, CLISTWeek_RCDLEN,
    0x40132200, 1, 18
};
//------结算日编程-1项默认关联对象属性表--------
const   sCList1_TypeDef EvtCListRmDayDefault _reserve =
{
    1, CLISTDay_RCDLEN,
    0x41162200, 6, 18
};
//------有功组合方式-1项默认关联对象属性表--------
const   sCList1_TypeDef EvtCListPrgPDefault _reserve =
{
    1, CLISTPrgP_RCDLEN,
    0x41122200, 1, 18
};

//------密钥更新-1项默认关联对象属性表--------
const   sCList1_TypeDef EvtCListSetPswDefault _reserve =
{
    1, CLISTSetPsw_RCDLEN,
    0xF1002400, 16, 18
};

//----开盖--时钟故障-4-项默认关联对象属性表--------
const   sCList4_TypeDef EvtCList4Default _reserve =
{
    4, CLIST4_RCDLEN,
    0x00102201, 4,    18,
    0x00202201, 4,    22,
    0x00108201, 4,    26,
    0x00208201, 4,    30
};

//------负荷开关误动作-5-项默认关联对象属性表--------
const   sCList5_TypeDef EvtCList5Default _reserve =
{
    5, CLIST5_RCDLEN,
    0xF2052201, 8,    18,
    0x00102201, 4,    26,
    0x00202201, 4,    30,
    0x00108201, 4,    34,
    0x00208201, 4,    38
};

//------零线电流异常--------------
const   sCList2_TypeDef EvtCListNErrDefault _reserve =
{
    2, CLISTNERR_RCDLEN,
    0x20012400, 4,    18,
    0x20012600, 4,    22
};

//------费率表-2项默认关联对象属性表--------
const   sCList2_TypeDef EvtCListRateDefault _reserve =
{
    2, CLISTRate_RCDLEN,
    0x40182200, 16, 18,
    0x40192200, 16, 34
};
//------阶梯表-2项默认关联对象属性表--------
const   sCList2_TypeDef EvtCListLadderDefault _reserve =
{
    2, CLISTLad_RCDLEN,
    0x401A2200, 64, 18,
    0x401B2200, 64, 78
};
//------异常插卡-4-项默认关联对象属性表--------
const   sCList4_TypeDef EvtCListCardErrDefault _reserve =
{
    4, CLISTCardErr_RCDLEN,
    0x202C2202, 4,    18,
    0x202C2201, 4,    22,
    0x00102201, 4,    26,
    0x00202201, 4,    30
};
//------购电-6-项默认关联对象属性表--------
const   sCList6_TypeDef EvtCListBuyDefault _reserve =
{
    6, CLISTBuy_RCDLEN,
    0x202C8202, 4,    18,
    0x202C2201, 4,    22,
    0x202D2200, 4,    26,
    0x202E2200, 4,    30,
    0x202C8201, 4,    34,
    0x202E8200, 4,    38
};
//-----退费-3-项默认关联对象属性表--------
const   sCList3_TypeDef EvtCListRtrnDefault _reserve =
{
    3, CLISTRtrn_RCDLEN,
    0x202C2202, 4,    18,
    0x202C2201, 4,    22,
    0x202C8200, 4,    26
};

const  sCListNULL_TypeDef EvtCListNULLDefault _reserve = { 0x00, 18    };
const  sCListNULL_TypeDef EvtPrgListDefault _reserve = { 0x00, CLISTPrg_RCDLEN };
const  sCListNULL_TypeDef EvtPrgPOTListDefault _reserve = { 0x00, CLISTZone_RCDLEN };
const  sCListNULL_TypeDef EvtPrgHldyListDefault _reserve = { 0x00, CLISTPrgHldy_RCDLEN };

#define FRZMINLISTOADNUM    15  //默认分钟冻结关联对象属性表OAD个数

#define FRZMINLISTCYCLE1    1    //默认分钟冻结周期 1min 曲线1
#define FRZMINLISTCYCLE2    15    //默认分钟冻结周期 15min 曲线2

const   sFrzMinList_TypeDef FrzMinListDefault _reserve =
{
    FRZMINLISTOADNUM, FRZMINRCDLEN,
    FRZMINLISTCYCLE1, 0x00100801, MAX_FRZMIN_RECORD1, 8, FRZSTDLISTLEN,
    FRZMINLISTCYCLE1, 0x00200801, MAX_FRZMIN_RECORD1, 8, FRZSTDLISTLEN + 8,
    FRZMINLISTCYCLE1, 0x20000200, MAX_FRZMIN_RECORD1, 6, FRZSTDLISTLEN + 16,
    FRZMINLISTCYCLE1, 0x20010200, MAX_FRZMIN_RECORD1, 12, FRZSTDLISTLEN + 22,
    FRZMINLISTCYCLE1, 0x20070200, MAX_FRZMIN_RECORD1, 16, FRZSTDLISTLEN + 34,
    FRZMINLISTCYCLE1, 0x20080200, MAX_FRZMIN_RECORD1, 16, FRZSTDLISTLEN + 50,
    FRZMINLISTCYCLE1, 0x200A0200, MAX_FRZMIN_RECORD1, 8, FRZSTDLISTLEN + 66,

    FRZMINLISTCYCLE2, 0x00502801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN,
    FRZMINLISTCYCLE2, 0x00602801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 8,
    FRZMINLISTCYCLE2, 0x00702801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 16,
    FRZMINLISTCYCLE2, 0x00802801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 24,
    FRZMINLISTCYCLE2, 0x01102801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 32,
    FRZMINLISTCYCLE2, 0x01202801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 40,
    FRZMINLISTCYCLE2, 0x02102801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 48,
    FRZMINLISTCYCLE2, 0x02202801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 56,
};
//-------分钟冻结曲线0默认头，如增加默认曲线条数，需增加曲线N默认头----
const sFrzMinLinePara_TypeDef FrzMinLineDefault0 _reserve =
{
    7,
    (FRZSTDLISTLEN + 74),
    0x00,  //曲线0地址偏移为0
    (((u32)(FRZSTDLISTLEN + 74) * (u32)MAX_FRZMIN_RECORD1 + 4096 + 4096) & 0xFFFFF000), //--预留1个bank后再bank对齐-----
    FRZMINLISTCYCLE1,
    (((u32)(FRZSTDLISTLEN + 74) * (u32)MAX_FRZMIN_RECORD1 + 4096) / (u32)(FRZSTDLISTLEN + 74))
};

const sFrzMinLinePara_TypeDef FrzMinLineDefault1 _reserve =
{
    8,
    FRZSTDLISTLEN + 64,
    (((u32)(FRZSTDLISTLEN + 74) * (u32)MAX_FRZMIN_RECORD1 + 4096 + 4096) & 0xFFFFF000), //曲线1地址偏移，//--预留1个bank后再bank对齐-----
    (((u32)(FRZSTDLISTLEN + 64) * (u32)MAX_FRZMIN_RECORD2 + 4096 + 4096) & 0xFFFFF000),
    FRZMINLISTCYCLE2,
    (((u32)(FRZSTDLISTLEN + 64) * (u32)MAX_FRZMIN_RECORD2 + 4096) / (u32)(FRZSTDLISTLEN + 64))
};

//------------事件记录关联对象属性表初始化-----------------
const sRecord_ParaDefault_TypeDef EvtDefaultlist[] _reserve =
{
    { FileItemInfoNum_Evt_PowDn, (u8 *) &EvtCList2Default, sizeof(sCList2_TypeDef)      },
    //  { FileItemInfoNum_Evt_Clr                  , (u8 *)&EvtMeterClrCListDefault    , sizeof(sCList6_TypeDef)     } ,
    { FileItemInfoNum_Evt_Clr, (u8 *) &EvtMeterClrCListDefault, sizeof(sCList24_TypeDef)     },
    { FileItemInfoNum_Evt_SetClock, (u8 *) &EvtCList2Default, sizeof(sCList2_TypeDef)      },
    { FileItemInfoNum_Evt_OpenCover, (u8 *) &EvtOpenCoverCListDefault, sizeof(sCList12_TypeDef)     },
    { FileItemInfoNum_Evt_OpenTail, (u8 *) &EvtOpenCoverCListDefault, sizeof(sCList12_TypeDef)     },
    { FileItemInfoNum_Evt_PrgSetPsw, (u8 *) &EvtCListSetPswDefault, sizeof(sCList1_TypeDef)    },
    { FileItemInfoNum_Evt_BroadcastTime, (u8 *) &EvtCList2Default, sizeof(sCList2_TypeDef)    },
    { FileItemInfoNum_Evt_MngPlug, (u8 *) &EvtMngPlugCListDefault, sizeof(sCList14_TypeDef)    },
    { FileItemInfoNum_Evt_MngUpdate, (u8 *) &EvtMngUpdateCListDefault, sizeof(sCList8_TypeDef)    },
};
//------------事件记录关联对象属性表初始化-----------------
const sRecord_ParaDefault_TypeDef FrzDefaultlist[] _reserve =
{
    { FileItemInfoNum_Frz_MinFrz, (u8 *) &FrzMinListDefault, sizeof(sFrzMinList_TypeDef) },
};

#if (HarmonicPulseOut_Mode==HarmonicPulseOut_Interrupt)
//---厂家内部软件版本号由硬件版本+程序输出日期+硬件类型号组成------
const u8 FactorySoftVer[32] _reserve = {"RN8611_RN7306_24101101.0002"};  //--谐波脉冲输出为V1.0硬件版本---------
#else

#if(KeLu==TRUE)
const u8 FactorySoftVer[32] _reserve = {"RN8611_RN7306_231129V1.0001"}; //---谐波脉冲输出为V2.0硬件版本---------
#else
#if (HARDWARE_TYPE_CONFIG  == HARDWARE_TYPE_DIAN_TAN_BIAO_577)
const u8 FactorySoftVer[32] _reserve = {"RN8611_RN7306_25010901.0002"}; //------------dyf 57.7/100V电碳表版本信息
#else
const u8 FactorySoftVer[32] _reserve = {"RN8611_RN7306_25070801.0001"}; //------------dyf 计量芯 或 220电碳表版本信息
#endif
#endif

#endif

const u8 FristPowOn[4] _reserve = {'9', '7', '0', '1'};
