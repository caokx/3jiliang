
#ifndef _DL645_CURVE_H
#define _DL645_CURVE_H

typedef struct
{
    u16   Cycle[MAX_FRZMIN_LINE];
    u16   Crc;
} sFrzMinCycle_TypeDef;

typedef struct
{
    u32 FrzBlock_OAD;   //
    u8 *FrzBlock_pAddr;     //Êý¾ÝµØÖ·
} sFrzBlock_TypeDef;

extern const    sFrzStdList_TypeDef Frz_StdRecList;

extern void fnWrite_PowDn_FrzDayTime(void);
extern void fnWrite_PowDn_FrzRmDayTime(void);
extern void fnFreeze_MakeUp(void);
extern u8 fnJudgeTime_FrzMin(void);
//--------------------------------------------
extern const    sFrzStdList_TypeDef Frz_StdRecList;

extern void fnFreezePoint_Calc(sDate_time_s_TypeDef TimeOld, sDate_time_s_TypeDef TimeNew);

extern  void fnFreeze(void);
extern  void fnEnergy_MoneyInit(void);

#endif
