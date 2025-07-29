/****************************************************************************
* @file     BSP_MultiFunPort.c
* @author   Renergy Application Team
* @version  V1.0.1
* @date     2021.10.14
* @brief    �弶��๦�ܶ���
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
u16 MultiFunPulseStamp;/*"�๦�ܶ����������ʱ��"*/

/* Exported data  ----------------------------------------------------------*/

/* Private functions ------------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/

/*****************************************************************************
** Function name:BSP_MultiFunPort_Init
** Description:���๦�ܶ�������ź�����ѡ��
** Parameters:
** Returned value:NONE
******************************************************************************/
void BSP_MultiFunPort_Init(eMultiFunPort_TypeDef mfport)
{
    if (mfport == MF_SecondPulse)
    {
        Rn8xxx_GPIO_CfgFun(PinClkOut, _RTC_OUT); /*"���������"*/
    }
    else
    {
        Rn8xxx_GPIO_CfgFun(PinClkOut, _NORMALIO); /*"�������"*/
        Rn8xxx_GPIO_CfgIOMode(PinClkOut, GPIO_MODE_OUT, NORMAL_OUT);
        Rn8xxx_GPIO_SetPin(PinClkOut, 1);
    }
    MultiFunPulseStamp = 0 ;
}

/*****************************************************************************
** Function name:BSP_MultiFunPort_Output
** Description:���๦�ܶ��Ӵ�������
** Parameters:  u8time  �������������
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
