/****************************************************************************
* @file     Rn8xxx_SysTickCortexM0.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.05.25
* @brief    SysTick 驱动
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <Rn8xxx_Common.h>
#include <CoreSupport.h>
//#include <Rn8xxx_Gpio.h>
#include <Rn8xxx_SysTickCortexM0.h>
//#include <Drive_Lib.h>

/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/

/*********************************************************************************************************
** Function name:       fnRn8xxx_TC_TimeInit
** Descriptions:        定时器初始化
** input parameters:    tUnit_ms:定时器单位ms
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void Rn8xxx_SysTick_Init(uint32_t tUnit_ms)
{
    uint32_t ticks;

    ticks = SystemCoreClock * tUnit_ms / 1000;
    SysTick_Config(ticks);
}

/*********************************************************************************************************
** Function name:       fnRn8xxx_TC_TimeStop
** Descriptions:        间隔定时器关闭
** input parameters:    None
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void Rn8xxx_SysTick_Stop(void)
{
    SysTick->CTRL  = 0;
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
