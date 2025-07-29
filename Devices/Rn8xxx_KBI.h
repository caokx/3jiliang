/****************************************************************************
* @file
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.05.25
* @brief    外部中断模块驱动
******************************************************************************
* @attention
*
*
****************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef Rn8xxx_KBI_H
#define Rn8xxx_KBI_H

/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/

/* Exported enum ------------------------------------------------------------*/
typedef enum
{
    //INTC num
    KBI_ID0 = 0,
    KBI_ID1 = 1,
    KBI_ID2 = 2,
    KBI_ID3 = 3,
    KBI_ID4 = 4,
    KBI_ID5 = 5,
    KBI_ID6 = 6,
    KBI_ID7 = 7,
    KBI_IDMAX,
} eKBI_ID_TypeDef; /*"KBI    ID号"*/

typedef enum
{
    KBI_RisingEdge = 0,        /*"0：上升沿有效"*/
    KBI_FallingEdge = 1,       /*"1：下降沿有效"*/
} eKBI_TriggerEdge_TypeDef; /*"KBI     触发边沿"*/

typedef enum
{
    KBI_IRQ_ENABLE = 1,    /*"KBI 中断使能"*/
    KBI_IRQ_DISABLE = 0,   /*"KBI 中断禁止"*/
} eKBI_IRQ_TypeDef;        /*"KBI 中断使能选择"*/

/* Exported types ------------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void Rn8xxx_KBI_Init(eKBI_ID_TypeDef KBI_Id, eKBI_TriggerEdge_TypeDef TriggerEdge, eKBI_IRQ_TypeDef IrqFlag) ;
extern void KBI_Stop(eKBI_ID_TypeDef KBI_Id) ;
#endif//KBI _INTC_H

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
