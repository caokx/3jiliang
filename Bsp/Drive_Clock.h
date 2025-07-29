
#ifndef _DL645CLOCK_H
#define _DL645CLOCK_H

//
//*******************************************************************************
//**  Function define
//*******************************************************************************
//
extern void fnMainClock_Init(void);
extern void fnSubClock_Init(void);
extern u32 fnMainClock_Get(void);
extern void fnRCClock_Init(void);
#endif
