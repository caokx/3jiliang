/****************************************************************************
* @file     KBI.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.05.29
* @brief    �ⲿ�ж�ģ������
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include <stdint.h>
//#include <Dat_Types.h>
//#include <RN8318_RegDefine.h>
//#include <RA9701A0.h>
//#include <Rn8xxx_Gpio.h>

#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include <Rn8xxx_KBI.h>

/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/

/*********************************************************************************************************
** Function name:
** Descriptions:
** input parameters:    INTC_Id   TriggerEdge   IrqFlag
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void Rn8xxx_KBI_Init(eKBI_ID_TypeDef KBI_Id, eKBI_TriggerEdge_TypeDef TriggerEdge, eKBI_IRQ_TypeDef IrqFlag)
{
    if (KBI_Id < KBI_IDMAX)
    {
        SysCtl_EnableWrite;
        BITBAND_ADDR((u32)(&SYSCTL->KBI_EN), 8) = 1;
        BITBAND_ADDR((u32)(&SYSCTL->KBI_EN), KBI_Id) = 1;

        BITBAND_ADDR((u32)(&KBI->CTRL), KBI_Id) = 1;              /*"�ⲿ�ж�ģ��ʹ��"*/
        BITBAND_ADDR((u32)(&KBI->SEL), KBI_Id) = TriggerEdge;   /*"������&�½���ѡ��"*/

        BITBAND_ADDR((u32)(&KBI->DATA), KBI_Id) = 1;               /*"�ж��¼�����"*/
        BITBAND_ADDR((u32)(&KBI->MASK), KBI_Id) = IrqFlag;        /*"�����ж�ʹ��"*/
        SysCtl_DisableWrite;

        NVIC_EnableIRQ(KBI_IRQn);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_KBI_Disable
** Descriptions:        �ⲿ�ж�ģ��
** input parameters:    INTC_Id   TriggerEdge   IrqFlag
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void Rn8xxx_KBI_Disable(eKBI_ID_TypeDef KBI_Id)
{
    if (KBI_Id < KBI_IDMAX)
    {
        SysCtl_EnableWrite;
        BITBAND_ADDR((u32)(&SYSCTL->KBI_EN), KBI_Id) = 0;
        if (((SYSCTL->KBI_EN) & 0xff) == 0)
        {
            BITBAND_ADDR((u32)(&SYSCTL->KBI_EN), 8) = 0;/*"��KBIģ������ر�ʱ����ģ��Ҳ�ر�"*/
        }
        BITBAND_ADDR((u32)(&KBI->CTRL), KBI_Id) = 0;                       /*"KBIģ��ʹ��"*/
        BITBAND_ADDR((u32)(&KBI->MASK), KBI_Id) = KBI_IRQ_DISABLE;        /*"�����ж�ʹ��"*/
        SysCtl_DisableWrite;
    }
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
