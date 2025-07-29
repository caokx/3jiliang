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
} OAD_Analyse_TypeDef; //OAD����

typedef struct
{
    u8 ActMeth;  //����ģʽ
    u8 ActFlag;   //������ʶ
    u16 OI;
} OMD_Analyse_TypeDef; //OMD����

typedef struct
{
    u8 OIB2: 4;
    u8 OIB1: 4;
    u8 OIA2: 4;
    u8 OIA1: 4;
} OI_Analyse_TypeDef; //OI����

typedef struct
{
    u8 DI0;
    u8 DI1;
    u8 DI2;
    u8 DI3;
} DI_Analyse_TypeDef; //645_DI����

typedef struct
{
    u8 table;
    u8 srcType;
    u8 dstType;     // ����18�֣�DI1��ȡֵ
} sDl698_TypeSwitch_TypeDef;

typedef struct
{
    u16 OI;
    u8  Atr_type;  //��������
    u8      Flag;       //D7=1��д��D6=1�ɶ���D0 = 1 ��Ч�����ݵ�hex
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
    u8  Atr_type;  //��������
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
    u16     OI;             //�¼���¼�򶳽�OI
    u8   Item;      //�¼���¼/�����Ӧ��ö�ٺ�
} sRecordItem_TypeDef;

typedef struct
{
    u16     OI;             //�¼���¼OI
    u16   EvtConfigParaOffAddr;  //�¼���¼���ò����׵�ַ
    u8    ConfigParaLen;            //���ò�������
} sEventCfgPara_TypeDef;

typedef struct
{
    u16     OI;             //�¼���¼OI
    u16   EvtRcddOffAddr;  //�¼���¼���ò����׵�ַ
    u8    RcdLen;           //���ò�������
} sEvtRcd_TypeDef;

typedef struct
{
    u8   Item;      //�����Ӧ��ö�ٺ�
    u8   Enume;   //��λ
} sEnumeRated_TypeDef;

typedef struct
{
    u8  Frz1DateValid;      //��һ���Ӷ��᷽��2�����Ƿ���Ч��0��Ч1��Ч
    sDate_time_s_TypeDef    Frz1DateTimes;  //��һ���Ӷ��᷽��1����ʱ��
    sFsEgSh_HighTypeDef     FrzPtPEgSh;     //���������й�����
    sFsEgSh_HighTypeDef     FrzNtPEgSh;     //���ᷴ���й�����
    u16 FrzU[nPhs];     //�����ѹ
    s32 FrzI[nPhs];     //�������
    s32 FrzPwavg[nPhs + 1]; //����һ����ƽ���й�����
    s32 FrzPqavg[nPhs + 1]; //����һ����ƽ���޹�����
    s16 FrzPf[nPhs + 1];    //���Ṧ������

    u8  Frz2DateValid;      //��һ���Ӷ��᷽��2�����Ƿ���Ч��0��Ч1��Ч
    sDate_time_s_TypeDef    Frz2DateTimes;  //��һ���Ӷ��᷽��2����ʱ��
    sFsEgSh_HighTypeDef     FrzQd1QEgSh;    //��һ�����޹�����
    sFsEgSh_HighTypeDef     FrzQd2QEgSh;    //�ڶ������޹�����
    sFsEgSh_HighTypeDef     FrzQd3QEgSh;    //���������޹�����
    sFsEgSh_HighTypeDef     FrzQd4QEgSh;    //���������޹�����
    sFsEgSh_HighTypeDef     FrzPtFEgSh;     //�����й��������ܵ���
    sFsEgSh_HighTypeDef     FrzNtFEgSh;     //�����й��������ܵ���
    sFsEgSh_HighTypeDef     FrzPtHEgSh;     //�����й���г���ܵ���
    sFsEgSh_HighTypeDef     FrzNtHEgSh;     //�����й���г���ܵ���
} sSynFrzDataBlock_Type;

typedef struct
{
    u8 AtrType;     //��������
    u8 AtrTypeLen;  //�������ͳ���
    u8 *pAddr;      //���ݵ�ַ
    u8 DataLen;     //���ݳ���
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
    u32     OAD,            //��ȡ�¼���¼OAD,Ԫ��������ʾ��ȡ�ڼ���
    u8  *pParBuf,       //ͨѶ�·�����Ҫ��ȡ��RCSD��Ϣ
    u8  *uBuf,      //��̬����ͨѶbuf,��fnDl698_GetRecordValueͳһ����,2K
    u8      *pRetBuf,       //��ȡ����Ӧ�����ݣ���698��ʽ��װ��
    u16     *pLen,      //���ݳ���
    u8      *blockRsp,
    u8   CheckSec
);

extern u8 fnGet_FrzMinRecord(
    u32     OAD,            //��ȡ�¼���¼OAD,Ԫ��������ʾ��ȡ�ڼ���
    u8  *pParBuf,       //ͨѶ�·�����Ҫ��ȡ��RCSD��Ϣ
    u8  *uBuf,      //��̬����ͨѶbuf,��fnDl698_GetRecordValueͳһ����,2K
    u8      *pRetBuf,       //��ȡ����Ӧ�����ݣ���698��ʽ��װ��
    u16     *pLen,      //���ݳ���
    u8      *blockRsp
);

#ifdef __cplusplus
}
#endif

#endif
