/****************************************************************************
* @file     KBI.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.05.29
* @brief    外部中断模块驱动
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

        BITBAND_ADDR((u32)(&KBI->CTRL), KBI_Id) = 1;              /*"外部中断模块使能"*/
        BITBAND_ADDR((u32)(&KBI->SEL), KBI_Id) = TriggerEdge;   /*"上升沿&下降沿选择"*/

        BITBAND_ADDR((u32)(&KBI->DATA), KBI_Id) = 1;               /*"中断事件清零"*/
        BITBAND_ADDR((u32)(&KBI->MASK), KBI_Id) = IrqFlag;        /*"配置中断使能"*/
        SysCtl_DisableWrite;

        NVIC_EnableIRQ(KBI_IRQn);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_KBI_Disable
** Descriptions:        外部中断模块
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
            BITBAND_ADDR((u32)(&SYSCTL->KBI_EN), 8) = 0;/*"当KBI模块均被关闭时，总模块也关闭"*/
        }
        BITBAND_ADDR((u32)(&KBI->CTRL), KBI_Id) = 0;                       /*"KBI模块使能"*/
        BITBAND_ADDR((u32)(&KBI->MASK), KBI_Id) = KBI_IRQ_DISABLE;        /*"配置中断使能"*/
        SysCtl_DisableWrite;
    }
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
