/****************************************************************************
* @file     Rn8xxx_TC.h
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.05.25
* @brief    TimerÇý¶¯
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TC_H
#define _TC_H

/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/
#define Timer0      0
#define Timer1      1

/* Exported enum ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern  void Rn8xxx_TC_SquareWaveInit(u8 TimerId, uint32_t SquareWaveClock) ;
extern  void Rn8xxx_TC_TimeInit(u8 TimerId, u8 tUnit_ms);
extern  void Rn8xxx_TC_TimeStar(u8 TimerId, FunctionalState IrqFlag);
extern  void Rn8xxx_TC_TimeStop(u8 TimerId);
#endif

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
