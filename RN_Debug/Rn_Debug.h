/****************************************************************************
* @file     RN_Debug.h
* @author   zhupeng
* @version  V1.0.0
* @date     2023.03.16
* @brief    锐能微DEBUG模块
******************************************************************************
* @attention
*包括1、RTT
*      2 、断言
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _RN_Debug_H_
#define _RN_Debug_H_

/* Exported define ------------------------------------------------------------*/
/*"锐能微DEBUG模块总开关"*/
#define  USE_RN_Debug

#ifdef USE_RN_Debug
#define  USE_RN_RTT         /*"锐能微RTT模块开关"*/
#define  USE_RN_Assert      /*"锐能微Assert模块开关"*/

#endif

/* Includes ------------------------------------------------------------------*/
#include <SEGGER_RTT.h>
#include <Rn_Assert.h>

//int SEGGER_RTT_printf(unsigned BufferIndex, const char * sFormat, ...);
#ifdef USE_RN_RTT
#define RN_SEGGER_RTT_Init()   SEGGER_RTT_Init();
#define RN_SEGGER_RTT_printf(BufferIndex, sFormat, ...)   SEGGER_RTT_printf( BufferIndex, sFormat)
#else
#define RN_SEGGER_RTT_Init()   ((void)0)
#define RN_SEGGER_RTT_printf(BufferIndex, sFormat, ...)    ((void)0)
#endif

/* Exported enum ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported data  ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

#endif

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
