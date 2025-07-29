/****************************************************************************
* @file
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
} eKBI_ID_TypeDef; /*"KBI    ID��"*/

typedef enum
{
    KBI_RisingEdge = 0,        /*"0����������Ч"*/
    KBI_FallingEdge = 1,       /*"1���½�����Ч"*/
} eKBI_TriggerEdge_TypeDef; /*"KBI     ��������"*/

typedef enum
{
    KBI_IRQ_ENABLE = 1,    /*"KBI �ж�ʹ��"*/
    KBI_IRQ_DISABLE = 0,   /*"KBI �жϽ�ֹ"*/
} eKBI_IRQ_TypeDef;        /*"KBI �ж�ʹ��ѡ��"*/

/* Exported types ------------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void Rn8xxx_KBI_Init(eKBI_ID_TypeDef KBI_Id, eKBI_TriggerEdge_TypeDef TriggerEdge, eKBI_IRQ_TypeDef IrqFlag) ;
extern void KBI_Stop(eKBI_ID_TypeDef KBI_Id) ;
#endif//KBI _INTC_H

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
