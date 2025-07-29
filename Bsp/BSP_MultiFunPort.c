/****************************************************************************
* @file     BSP_MultiFunPort.c
* @author   Renergy Application Team
* @version  V1.0.1
* @date     2021.10.14
* @brief    板级层多功能端子
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include <BSP.h>
/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/
u16 MultiFunPulseStamp;/*"多功能端子脉冲持续时戳"*/

/* Exported data  ----------------------------------------------------------*/

/* Private functions ------------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/

/*****************************************************************************
** Function name:BSP_MultiFunPort_Init
** Description:　多功能端子输出信号类型选择
** Parameters:
** Returned value:NONE
******************************************************************************/
void BSP_MultiFunPort_Init(eMultiFunPort_TypeDef mfport)
{
    if (mfport == MF_SecondPulse)
    {
        Rn8xxx_GPIO_CfgFun(PinClkOut, _RTC_OUT); /*"秒脉冲输出"*/
    }
    else
    {
        Rn8xxx_GPIO_CfgFun(PinClkOut, _NORMALIO); /*"控制输出"*/
        Rn8xxx_GPIO_CfgIOMode(PinClkOut, GPIO_MODE_OUT, NORMAL_OUT);
        Rn8xxx_GPIO_SetPin(PinClkOut, 1);
    }
    MultiFunPulseStamp = 0 ;
}

/*****************************************************************************
** Function name:BSP_MultiFunPort_Output
** Description:　多功能端子触发脉冲
** Parameters:  u8time  脉冲持续毫秒数
** Returned value:NONE
******************************************************************************/
void BSP_MultiFunPort_Output(u16 u16time)
{
    Rn8xxx_GPIO_CfgIOMode(PinClkOut, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinClkOut, 0);

    MultiFunPulseStamp = u16time / 5;
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
