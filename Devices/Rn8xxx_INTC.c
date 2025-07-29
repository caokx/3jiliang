/****************************************************************************
* @file     INTC.c
* @author   Renergy Application Team
* @version  V1.0.1
* @date     2021.06.28
* @brief    外部中断模块驱动
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <Rn8xxx_Common.h>
#include <CoreSupport.h>
#include <Rn8xxx_Gpio.h>
#include <Rn8xxx_INTC.h>

/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*********************************************************************************************************
** Function name:       Rn8xxx_Intc_IRQ
** Descriptions:        外部中断模块
** input parameters:    INTC_Id      IrqFlag
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
static void Rn8xxx_Intc_IRQ(eINTC_ID_TypeDef INTC_Id, eINTC_IRQ_TypeDef IrqFlag)
{
    IRQn_Type IRQn;
    switch (INTC_Id)
    {
        case INTC_ID0:
            IRQn = EXT0_IRQn;
            break;
        case INTC_ID1:
            IRQn = EXT1_IRQn;
            break;
        case INTC_ID2:
            IRQn = EXT2_IRQn;
            break;
        case INTC_ID3:
            IRQn = EXT3_IRQn;
            break;
        case INTC_ID4:
            IRQn = EXT4_IRQn;
            break;
        case INTC_ID5:
            IRQn = EXT5_IRQn;
            break;
        case INTC_ID6:
            IRQn = EXT6_IRQn;
            break;
        case INTC_ID7:
            IRQn = EXT7_IRQn;
            break;
        default:
            return;
    }

    if (INTC_IRQ_ENABLE == IrqFlag)
    {
        NVIC_EnableIRQ(IRQn);
    }
    else
    {
        NVIC_DisableIRQ(IRQn);
    }
}

/* Exported functions ----------------------------------------------------------*/

/*********************************************************************************************************
** Function name:       Rn8xxx_INTC_Init
** Descriptions:        外部中断模块
** input parameters:    INTC_Id   TriggerEdge   IrqFlag
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void Rn8xxx_INTC_Init(eINTC_ID_TypeDef INTC_Id, eINTC_TriggerEdge_TypeDef TriggerEdge, eINTC_IRQ_TypeDef IrqFlag)
{
    if (INTC_Id < INTC_IDMAX)
    {
        SysCtl_EnableWrite;
        BITBAND_ADDR((u32)(&SYSCTL->INTC_EN), 8) = 1;
        BITBAND_ADDR((u32)(&SYSCTL->INTC_EN), INTC_Id) = 1;

        BITBAND_ADDR((u32)(&INTC->CTRL), INTC_Id) = 1;              /*"外部中断模块使能"*/
        BITBAND_ADDR((u32)(&INTC->MODE), (INTC_Id * 2)) = (TriggerEdge & 0x01); /*"上升沿&下降沿选择"*/
        BITBAND_ADDR((u32)(&INTC->MODE), (INTC_Id * 2 + 1)) = ((TriggerEdge >> 1) & 0x01);

        BITBAND_ADDR((u32)(&INTC->STA), INTC_Id) = 1;               /*"中断事件清零"*/
        BITBAND_ADDR((u32)(&INTC->MASK), INTC_Id) = IrqFlag;        /*"配置中断使能"*/
        SysCtl_DisableWrite;

        Rn8xxx_Intc_IRQ(INTC_Id, IrqFlag);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_INTC_Stop
** Descriptions:        外部中断模块
** input parameters:
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void Rn8xxx_INTC_Stop(eINTC_ID_TypeDef INTC_Id)
{
    if (INTC_Id < INTC_IDMAX)
    {
        SysCtl_EnableWrite;
        BITBAND_ADDR((u32)(&SYSCTL->INTC_EN), INTC_Id) = 0;
        BITBAND_ADDR((u32)(&INTC->CTRL), INTC_Id) = 0;              /*"外部中断模块使能"*/
        BITBAND_ADDR((u32)(&INTC->MASK), INTC_Id) = INTC_IRQ_DISABLE;        /*"配置中断使能"*/
        SysCtl_DisableWrite;
        Rn8xxx_Intc_IRQ(INTC_Id, INTC_IRQ_DISABLE);
    }
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
