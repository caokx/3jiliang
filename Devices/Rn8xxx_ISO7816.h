/****************************************************************************
* @file     Uart.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.04.28
* @brief    UartÇý¶¯
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef  _ISO7816_H
#define  _ISO7816_H

/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/

/* Exported enum ------------------------------------------------------------*/
typedef enum
{
    ISO7816_0ID     = 0x00,
    ISO7816_1ID     = 0x01,
} eISO7816_ID_TypeDef;

/* Exported data ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

extern void ISO7816_SquareWave_Init(uint32_t SquareWaveClock);
extern void ISO7816_Init(void);
extern ErrorStatus ISO7816_ReadByte(eISO7816_ID_TypeDef id, u8 *Data);
extern ErrorStatus ISO7816_WriteByte(eISO7816_ID_TypeDef id, u8 Data) ;

#endif

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
