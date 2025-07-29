/**
  ******************************************************************************
  * @file    FIFO.c
  * @author  Renergy Application Team
  * @version V1.0.0
  * @date    2019.06.10
  * @brief   虚拟FIFO模块，管理接收发送驱动。循环收取通讯口数据。
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef   _FIFO_H
#define  _FIFO_H

/* Includes ------------------------------------------------------------------*/
//#include <stdint.h>

/* Exported define ------------------------------------------------------------*/

/* Exported enum ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint8_t *RxBuffer;/* 接收缓冲区； */
    uint8_t *TxBuffer; /*发送缓冲区； */
    uint16_t RxBufferSize; /*接收缓冲区大小； */
    uint16_t TxBufferSize; /*发送缓冲区大小； */
} FIFOMailBox_CFG_TypeDef;

typedef struct
{
    uint8_t *RxBuffer;/* 接收缓冲区； */
    uint8_t *TxBuffer; /*发送缓冲区； */
    uint16_t RxBufferSize; /*接收缓冲区大小； */
    uint16_t TxBufferSize; /*发送缓冲区大小； */
    uint16_t RxCount; /*接收缓冲区中的接收字节数； */
    uint16_t TxCount;   /*发送缓冲区中的待发字节数； */
    uint16_t RxPointer; /*最新接收的字节指针,其在接收中断中被修改，初始化为0； */
    uint16_t TxPointer; /*最新待发的字节指针，其在发送中断中被修改，初始化为0； */
    uint8_t enterflag;/*本通道已经进入FIFO标志;*/
} FIFOMailBox_TypeDef;

/* Exported variables ----------------------------------------------------------*/
extern FIFOMailBox_TypeDef FIFOMailBox[];

/* Exported functions ------------------------------------------------------- */
extern void fifo_ClearBuffer(uint8_t fifo_Id);
extern void FIFO_Init(uint8_t fifo_Id, FIFOMailBox_CFG_TypeDef fifo_cfg);
extern void FIFO_StartSend(uint8_t fifo_Id, uint16_t fifo_txlen, uint8_t*TxBuffer);
//extern void FIFO_Info(uint8_t fifo_Id,FIFOMailBox_TypeDef *fifoPort);
extern uint16_t FIFO_Info(uint8_t fifo_Id);
extern void FIFO_Re_HANDLER(uint8_t fifo_Id, uint8_t* fifo_Rx, uint8_t fifo_RxCount);
extern uint8_t FIFO_Tx_HANDLER(uint8_t fifo_Id, uint8_t*fifo_Tx, uint8_t fifo_TxCount);
extern u8 FIFO_Spis_Rx(void);

#endif
/****************************  (C) COPYRIGHT Renergy  ****************************/
/****************************          END OF FILE          ****************************/
