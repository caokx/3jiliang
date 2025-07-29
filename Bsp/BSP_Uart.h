/****************************************************************************
* @file     BSP_Uart.h
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.04.28
* @brief    Uart驱动
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BSP_UART_H
#define _BSP_UART_H

/* Includes ------------------------------------------------------------------*/
#include <BSP_Scom.h>

/* Exported define ------------------------------------------------------------*/

/* Exported enum ------------------------------------------------------------*/

/*UART DMA使能*/
typedef enum
{
    UART_DMA_DIS = 0,
    UART_DMA_EN = 1,
} eUART_DMAEnOrDis_TypeDef;

/* Exported data ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

extern void USART_ITConfig(u8 ComPort, FunctionalMODE USART_IT, FunctionalState NewState);
extern void BSP_Uart_Init(eScomPort_TypeDef scom_id, uint8_t bsp);
extern void BSP_Uart_DMAInit(eScomPort_TypeDef ComPort, uUART_DMAPara_TypeDef uart_dma_para);
extern void BSP_TxEnDis(u8 ComPort, FunctionalState EnOrDis);   //收发控制DIR
extern eUART_ID_TypeDef BSP_UartId_Get(eScomPort_TypeDef Scom);
extern eScomPort_TypeDef BSP_Scom_Get(eUART_ID_TypeDef UartId);
extern void BSP_UartId_DMAEnOrDis_Get(eScomPort_TypeDef Scom, eUART_ID_TypeDef *UartId, u8 *DMAEnOrDis);
extern void BSP_Scom_DMAEnOrDis_Get(eUART_ID_TypeDef UartId, eScomPort_TypeDef *Scom,  u8 *DMAEnOrDis);
extern u8 BSP_UartDMA_IRQCheck(eScomPort_TypeDef ComPort);
extern ErrorStatus BSP_UartCtrlandDmaRxCheck(eScomPort_TypeDef Scom);

#endif  //BSP__UART_H
/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
