/****************************************************************************
* @file     SPI.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.04.28
* @brief    SPI?y?бе
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BSP_SPI_H
#define _BSP_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "Bsp_Scom.h"
/* Exported define ------------------------------------------------------------*/

#define  FLASH_SPI_ID       SPI0_ID
#define  FLASH_SPI_SPEED       2000000

#define  SPI_FLASH_HardwareMode    0
#define  SPI_FLASH_FirmwareMode    1
#define  SPI_FLASH_Mode            SPI_FLASH_FirmwareMode//SPI_FLASH_HardwareMode

/* Exported enum ------------------------------------------------------------*/

typedef enum
{
    SPI_DMA_DIS = 0,
    SPI_DMA_EN = 1,
} eSPI_DMAEnOrDis_TypeDef;

/* Exported types ------------------------------------------------------------*/

//========================
//extern void fnSpi1_Init(void);

/* Exported data ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern uint8_t BSP_FlashSpi_ReadByte(void);
extern void BSP_FlashSpi_WriteByte(uint8_t Dat);

extern void BSP_FlashSpi_Init(void);
extern void BSP_FlashSpi_Stop(void);

extern eSPI_ID_TypeDef BSP_SpiId_Get(eScomPort_TypeDef Scom);

extern void BSP_SpiId_DMAEnOrDis_Get(eScomPort_TypeDef Scom, eSPI_ID_TypeDef *SpiId, u8 *DMAEnOrDis);
extern void BSP_ManageModuleSpi_Init(u8 SpiId, u32 BdRate);
extern ErrorStatus BSP_SpiCtrlandDmaRxCheck(eScomPort_TypeDef Scom);

#endif  //_SPI_H
/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
