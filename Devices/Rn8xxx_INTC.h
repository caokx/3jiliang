/****************************************************************************
* @file     INTC.h
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.05.25
* @brief    �ⲿ�ж�ģ������
******************************************************************************
* @attention
*
*
****************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _Rn8xxx_INTC_H
#define _Rn8xxx_INTC_H

/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/

/* Exported enum ------------------------------------------------------------*/
typedef enum
{
    //INTC num
    INTC_ID0 = 0,
    INTC_ID1 = 1,
    INTC_ID2 = 2,
    INTC_ID3 = 3,
    INTC_ID4 = 4,
    INTC_ID5 = 5,
    INTC_ID6 = 6,
    INTC_ID7 = 7,
    INTC_IDMAX,
} eINTC_ID_TypeDef; /*"INTC       ID��"*/

typedef enum
{
    INTC_RisingEdge = 0,        /*"00��������"*/
    INTC_FallingEdge = 1,       /*"01���½���"*/
    INTC_DoubleEdge = 2,        /*"10��˫����"*/
    INTC_NoEdge = 3,            /*"11������"*/
} eINTC_TriggerEdge_TypeDef; /*"INTC     ��������"*/

typedef enum
{
    INTC_IRQ_ENABLE = 1,    /*"INTC �ж�ʹ��"*/
    INTC_IRQ_DISABLE = 0,   /*"INTC �жϽ�ֹ"*/
} eINTC_IRQ_TypeDef;        /*"INTC �ж�ʹ��ѡ��"*/

/* Exported types ------------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void Rn8xxx_INTC_Init(eINTC_ID_TypeDef INTC_Id, eINTC_TriggerEdge_TypeDef TriggerEdge, eINTC_IRQ_TypeDef IrqFlag) ;
extern void Rn8xxx_INTC_Stop(eINTC_ID_TypeDef INTC_Id) ;
#endif//END _INTC_H

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
