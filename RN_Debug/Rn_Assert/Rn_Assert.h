/****************************************************************************
* @file     Rn_Assert.h
* @author   zhupeng
* @version  V1.0.0
* @date     2023.03.16
* @brief    锐能微断言模块
******************************************************************************
* @attention
*
*
****************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef _Rn_Assert_H_
#define _Rn_Assert_H_

/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/
/*"锐能微Assert模块开关"*/

#ifdef  USE_RN_Assert
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports
  *         the name of the source file and the source line number of the call
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
#define Rn_AssertParam(expr) ((expr) ? (void)0 : Rn_AssertFailed((uint8_t *)__FILE__, __LINE__))
void Rn_AssertFailed(uint8_t* file, uint32_t line);
#else
#define Rn_AssertParam(expr)    ((void)0)
#endif

/* Exported enum ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported data  ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

#endif

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
