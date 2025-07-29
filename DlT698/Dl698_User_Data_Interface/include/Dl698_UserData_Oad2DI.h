/********************************************************************
Filename:       Dl698_UserData_Oad2DI.h
Revised:        $Date: 2017-07-103 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
#ifndef _DL698_USERDATA_OAD2DI_H_
#define _DL698_USERDATA_OAD2DI_H_

/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"
#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
* TYPEDEFS
*/
typedef struct
{
    u8 elementIndex: 8;
    u8 AtrIndex: 5;
    u8 AtrFeature: 3;
    u8 OIB2: 4;
    u8 OIB1: 4;
    u8 OIA2: 4;
    u8 OIA1: 4;
} OAD_Analyse_TypeDef; //OAD解析

typedef struct
{
    u8 ActMeth;  //操作模式
    u8 ActFlag;   //方法标识
    u16 OI;
} OMD_Analyse_TypeDef; //OMD解析

typedef struct
{
    u8 OIB2: 4;
    u8 OIB1: 4;
    u8 OIA2: 4;
    u8 OIA1: 4;
} OI_Analyse_TypeDef; //OI解析

typedef struct
{
    u8 DI0;
    u8 DI1;
    u8 DI2;
    u8 DI3;
} DI_Analyse_TypeDef; //645_DI解析

typedef struct
{
    u8 table;
    u8 srcType;
    u8 dstType;     // 规律18种，DI1的取值
} sDl698_TypeSwitch_TypeDef;

typedef struct
{
    u16 OI;
    u8  Atr_type;  //数据类型
    u8      Flag;       //D7=1可写、D6=1可读、D0 = 1 需效验数据的hex
    u8  FileId;
    u16 Len;
    u32 OffAddr;
} sDl698_PARA_VAR_TypeDef;
typedef struct
{
    u16  OI;
    u8   Item;
    u32  Addr;
} sNEED_TypeDef;

typedef struct
{
    u16  OI;
    u8   Item;
    u8  Atr_type;  //数据类型
    u8   *Addr;
    u8  Len;
} sDl698_VAR_TypeDef;

typedef struct
{
    u16 OI;
    u8  Item;
    u8   *Addr;
} sDl698_ENERGY_TypeDef;

typedef struct
{
    u32 OAD;        //
    u8 EsamP2;      //
} sESAMP2_OAD_TypeDef;

typedef struct
{
    u16     OI;             //事件记录或冻结OI
    u8   Item;      //事件记录/冻结对应的枚举号
} sRecordItem_TypeDef;

typedef struct
{
    u16     OI;             //事件记录OI
    u16   EvtConfigParaOffAddr;  //事件记录配置参数首地址
    u8    ConfigParaLen;            //配置参数长度
} sEventCfgPara_TypeDef;

typedef struct
{
    u16     OI;             //事件记录OI
    u16   EvtRcddOffAddr;  //事件记录配置参数首地址
    u8    RcdLen;           //配置参数长度
} sEvtRcd_TypeDef;

typedef struct
{
    u8   Item;      //冻结对应的枚举号
    u8   Enume;   //单位
} sEnumeRated_TypeDef;

typedef struct
{
    u8  Frz1DateValid;      //上一分钟冻结方案2数据是否有效：0无效1有效
    sDate_time_s_TypeDef    Frz1DateTimes;  //上一分钟冻结方案1日期时间
    sFsEgSh_HighTypeDef     FrzPtPEgSh;     //冻结正向有功电能
    sFsEgSh_HighTypeDef     FrzNtPEgSh;     //冻结反向有功电能
    u16 FrzU[nPhs];     //冻结电压
    s32 FrzI[nPhs];     //冻结电流
    s32 FrzPwavg[nPhs + 1]; //冻结一分钟平均有功功率
    s32 FrzPqavg[nPhs + 1]; //冻结一分钟平均无功功率
    s16 FrzPf[nPhs + 1];    //冻结功率因数

    u8  Frz2DateValid;      //上一分钟冻结方案2数据是否有效：0无效1有效
    sDate_time_s_TypeDef    Frz2DateTimes;  //上一分钟冻结方案2日期时间
    sFsEgSh_HighTypeDef     FrzQd1QEgSh;    //第一象限无功电能
    sFsEgSh_HighTypeDef     FrzQd2QEgSh;    //第二象限无功电能
    sFsEgSh_HighTypeDef     FrzQd3QEgSh;    //第三象限无功电能
    sFsEgSh_HighTypeDef     FrzQd4QEgSh;    //第四象限无功电能
    sFsEgSh_HighTypeDef     FrzPtFEgSh;     //正向（有功）基波总电能
    sFsEgSh_HighTypeDef     FrzNtFEgSh;     //反向（有功）基波总电能
    sFsEgSh_HighTypeDef     FrzPtHEgSh;     //正向（有功）谐波总电能
    sFsEgSh_HighTypeDef     FrzNtHEgSh;     //反向（有功）谐波总电能
} sSynFrzDataBlock_Type;

typedef struct
{
    u8 AtrType;     //数据类型
    u8 AtrTypeLen;  //数据类型长度
    u8 *pAddr;      //数据地址
    u8 DataLen;     //数据长度
} sTagLen_Type;

/*********************************************************************
* MACROS
*/
//OIA1
#define OIA1_ENERGY 0x0
#define OIA1_NEED   0x1
#define OIA1_VAR   0x2
#define OIA1_EVENT 0x3
#define OIA1_PARA 0x4
#define OIA1_FREEZE 0x5
#define OIA1_CURVE 0x6
#define OIA1_CONTROL 0x8
#define OIA1_INTERFACE 0xF  //

#define OIA2_SAFE_MODE 0x1
#define OIA2_INOUT_DEVICE 0x2
#define OIA2_DISP 0x3  //

#define GETPOS_START 0x1
#define GETPOS_END     0x2

typedef enum
{
    Var_V                      =  0,
    Var_I,
    Var_Angle,
    Var_Angle2,
    Var_Pw,
    Var_Pq,
    Var_Ps,
    Var_Pf,
    Var_AveragePw,
    Var_AveragePq,
    Var_AveragePs,
    Var_WaveUnblU,
    Var_WaveUnblI,
    Var_HpercentU,
    Var_HpercentI,
    Var_HUrms,
    Var_HIrms,
    Var_HPrms,

    Var_PowerOFFData,

    Var_Freq,
    Var_TEMP,
    Var_TnT_Chang,

    Var_ClockBat,
    Var_BackupBat,
    Var_BatTime,
    Var_Mstate,
    Var_ReportState,
    Var_PwNeed,
    Var_PqNeed,
    Var_PsNeed,
    Var_Price,
    Var_FLPrice,
    Var_LdPrice,
    Var_SMoney,
    Var_OMoney,
    Var_UnblU,
    Var_UnblI,
    Var_Ahs,
    Var_MonthEg,
    Var_YearEg,
    Var_Gata_Do,
    Var_Gata_Err,
    Var_EligRateUA,
    Var_EligRateUB,
    Var_EligRateUC
} eVar_TypeDef;
/*********************************************************************
* EXTERNAL VARIABLES
*/
extern  sSynFrzDataBlock_Type   SynFrzDataBlock;
/*********************************************************************
* EXTERNAL FUNCTIONS
*/
extern  const sRecordItem_TypeDef Event_Item[];

extern void fnUpDate_EvtParaOffPos(void);
extern void fnUpDate_FrzParaOffPos(void);

u8 fnGet_Para(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen,  u8  *blockRsp);

extern u8 fnGet_VarData(u32  OAD, u8  *uBuf);
extern u8 fnGet_Normal(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen,  u8  *blockRsp);
extern u8 fnSet_Normal(u32  OAD, u8  *pSrc, u8  *pParBuf, u16 *parLen);
extern u8 fnAct_Normal(u32  OMD, u8  *pSrc, u16 *parLen, u8 *pRetBuf, u16 *retLen, u8 *pBuf);
extern u8 fnGet_EvtRecord(u32 OAD, u8 *pParBuf, u8 *uBuf, u8  *pRetBuf, u16 *pLen, u8  *blockRsp, u8 CheckSec);
extern u16 fnGet_OADStoreData(u32  OAD,  u8  *pBuf);

extern u8 fnGet_CsdNum(u32 OAD, u8 *pParaBuf, u8 *uBuf);
extern u8 fnGet_EvtItem(u16 OIA_B, u8 *cid);
extern u8 fnGet_FrzItem(u16 OIA_B);
extern u16 fnGet_OADDataType(u32  OAD,  u8  *pDatatype);
extern u8 fnFill_OADData(u32  OAD,  u8  *pDstBuf, u8  *pSrcBuf, u8 len);
extern void fnGet_DispData(sDispItem_TypeDef  *DispItem, u8 *pBuf, u16 *Len);

extern u8 fnGet_FrzRecord(
    u32     OAD,            //读取事件记录OAD,元素索引表示读取第几次
    u8  *pParBuf,       //通讯下发的需要读取的RCSD信息
    u8  *uBuf,      //动态缓存通讯buf,在fnDl698_GetRecordValue统一申请,2K
    u8      *pRetBuf,       //获取到需应答数据，按698格式封装好
    u16     *pLen,      //数据长度
    u8      *blockRsp,
    u8   CheckSec
);

extern u8 fnGet_FrzMinRecord(
    u32     OAD,            //读取事件记录OAD,元素索引表示读取第几次
    u8  *pParBuf,       //通讯下发的需要读取的RCSD信息
    u8  *uBuf,      //动态缓存通讯buf,在fnDl698_GetRecordValue统一申请,2K
    u8      *pRetBuf,       //获取到需应答数据，按698格式封装好
    u16     *pLen,      //数据长度
    u8      *blockRsp
);

#ifdef __cplusplus
}
#endif

#endif
