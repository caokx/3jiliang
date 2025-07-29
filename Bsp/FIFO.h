/**
  ******************************************************************************
  * @file    FIFO.c
  * @author  Renergy Application Team
  * @version V1.0.0
  * @date    2019.06.10
  * @brief   ����FIFOģ�飬������շ���������ѭ����ȡͨѶ�����ݡ�
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
    uint8_t *RxBuffer;/* ���ջ������� */
    uint8_t *TxBuffer; /*���ͻ������� */
    uint16_t RxBufferSize; /*���ջ�������С�� */
    uint16_t TxBufferSize; /*���ͻ�������С�� */
} FIFOMailBox_CFG_TypeDef;

typedef struct
{
    uint8_t *RxBuffer;/* ���ջ������� */
    uint8_t *TxBuffer; /*���ͻ������� */
    uint16_t RxBufferSize; /*���ջ�������С�� */
    uint16_t TxBufferSize; /*���ͻ�������С�� */
    uint16_t RxCount; /*���ջ������еĽ����ֽ����� */
    uint16_t TxCount;   /*���ͻ������еĴ����ֽ����� */
    uint16_t RxPointer; /*���½��յ��ֽ�ָ��,���ڽ����ж��б��޸ģ���ʼ��Ϊ0�� */
    uint16_t TxPointer; /*���´������ֽ�ָ�룬���ڷ����ж��б��޸ģ���ʼ��Ϊ0�� */
    uint8_t enterflag;/*��ͨ���Ѿ�����FIFO��־;*/
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
