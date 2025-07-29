/****************************************************************************
* @file     BSP_Tmp.h
* @author   Renergy Application Team
* @version  V1.0.1
* @date     2023.4.23
* @brief    板级层温度传感器
******************************************************************************
* @attention
*
*
****************************************************************************/
#ifndef _BSP_TMP_H
#define _BSP_TMP_H

/*
#if (PCB_Version==RN8611_RN7306)
    #define MAX_TERMINAL_TMP_NUM    8
    extern s16 TerminalTmp[8];
#else
    #define MAX_TERMINAL_TMP_NUM    8
    extern s16 TerminalTmp[4];
#endif
*/

#define MAX_TERMINAL_TMP_NUM    8

typedef union
{
    u8 regByte[2];
    s16 regS16;
} ct7568tempReg_Type;

typedef struct
{
    u8 valid;
    s32 k;
    s32 offs;
} sTemperSchoolParaItem_TypeDef; //???èD￡×?2?êy

typedef struct
{
    sTemperSchoolParaItem_TypeDef chan[MAX_TERMINAL_TMP_NUM];
} sTemperSchoolPara_TypeDef; //???èD￡×?2?êy

extern  sTemperSchoolPara_TypeDef gTemperSchoolParaMem;
extern  sTemperSchoolPara_TypeDef gTemperSchoolParaTemp;
extern s16 gTempData[MAX_TERMINAL_TMP_NUM];

void fnBsp_Tmp_Init(void);
void fnBsp_Tmp_Read(void);
void fnBsp_CT7538_TempRange(void);
extern u8 fnBsp_CT7538_read_temp(u8 chNum, s16 *pTempData);

#endif
