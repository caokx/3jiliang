
#ifndef  _GLOBALS_H
#define  _GLOBALS_H

#ifdef   _GLOBALS
#define  _EXTERN
#else
#define  _EXTERN  extern
#endif
#include <App.h>
#include "ProDefine.h"

#define BUFTEMP_MAXLEN  3072    //
#define BUFTEMP_BLKSIZE 256      //256
#define BUFTEMP_BLKNUM  (BUFTEMP_MAXLEN/BUFTEMP_BLKSIZE)

_EXTERN      u16        SysStamp;    //系统主节拍.1ms
_EXTERN sDF01   SysClock;
_EXTERN sDate_time_s_TypeDef    SysDatetimes;

_EXTERN   sWDOG_TypeDef  Wdog;

_EXTERN sMeasureRegTmp_TypeDef          MeasureRegTmp;

_EXTERN sMeasureRms_TypeDef             MeasureRms;
_EXTERN sSynVarOtherUnitDataTypeDef     SynVarOtherUnitData;

_EXTERN sMeasureRepairPara_TypeDef              MeasureRepairPara;   //计量补偿
_EXTERN   sMeasureFirmPara_TypeDef      MeasureFirmPara;
_EXTERN   sRTCParaE2_TypeDef            RTCPara;
_EXTERN     sBkgrd_TypeDef          Bkgrd;
_EXTERN __no_init    sEnergy_TypeDef                    Energy;
//#if(nPhs==ThreePhs)
//_EXTERN   sDemand_TypeDef                     Demand;
//#endif
_EXTERN     sStat_TypeDef               Stat;
_EXTERN     sSecret_TypeDef         Secret;
_EXTERN     sTrim_TypeDef                   Trim;
_EXTERN   sEvent_TypeDef            Event;
_EXTERN   sEvStatusInter_TypeDef            EvStatusInter;
_EXTERN   sEvtRptData_TypeDef           EvtRptData;
_EXTERN   sEgMoney_TypeDef          EgMoney;
_EXTERN   sCurApplyEgSh_TypeDef         CurApplyEg;
_EXTERN     sComPack_TypeDef                ComPack[SCOM_PORT_MAX];
_EXTERN   sOutput_TypeDef           Output;
//_EXTERN   sDispOperParm_TypeDef       DispOperParm;
_EXTERN   sInactive_TypeDef         Inactive;
_EXTERN sFrzMinCycle_TypeDef            RFrzMinLine;
_EXTERN   sComPara_TypeDef          CommPara;
_EXTERN     sICEsamPack_TypeDef             ICEsamComm;
_EXTERN sICEsamReadBuf_TypeDef          ICEsamReadBuf;
_EXTERN u8  BufTemp[BUFTEMP_MAXLEN];

#if(HarmonicFun_EnORDis == HarmonicFun_Enable)

//  _EXTERN     sEmuAdcReg_Wave_TypeDef EmuAdcRegBuf;
//  //
//  #ifdef USE_IAR
//  _EXTERN sAdcWaveData_TypeDef AdcWaveData @ 0x10003000;          //
//  #else
//  _EXTERN sAdcWaveData_TypeDef AdcWaveData __attribute__( (at(0x10003000)));          //
//  #endif

_EXTERN u32 TestWaveDoTime[25];
#endif

/*********************************************************************
* CONSTANTS
*/

/*********************************************************************
* TYPEDEFS
*/

typedef enum
{
    BUFTEMP_STAT_IDLE = 0,
    BUFTEMP_STAT_IDLE_FIRST,
    BUFTEMP_STAT_BUSY,
    BUFTEMP_STAT_BUSY_FIRST,
} eBufTempStat_Typedef;

typedef struct
{
    u8 size;    //block number
    u8 stat;    //
} sBufTemp_Info_Typedef;

extern void fnBufTemp_Init(void);
extern void *fnBufTemp_Alloc(u16 BufLen);
extern void fnBufTemp_Free(void* pBuf);
//--------------------------------------------
#endif
