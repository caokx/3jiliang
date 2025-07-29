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

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <Includes.h>

/* Private define ------------------------------------------------------------*/
#define fifo_eleof(x)    (sizeof(x) / sizeof((x)[0]))
#define SPIS_ENTER_FLAG 0x55

/* Private enum -------------------------------------------------------------*/

/* Exported variables ----------------------------------------------------------*/
FIFOMailBox_TypeDef FIFOMailBox[SCOM_PORT_MAX];

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*********************************************************************************************************
** Function name:
** Descriptions:       ͨѶ�ڻ������
** input parameters:    fifo_Id :  �����ͨѶ����;
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void fifo_ClearBuffer(uint8_t fifo_Id)
{
    FIFOMailBox_TypeDef *fifoPort = &FIFOMailBox[fifo_Id];
    fifoPort->RxPointer = 0;
    fifoPort->RxCount = 0;
    fifoPort->TxPointer = 0;
    fifoPort->TxCount = 0;
    fifoPort->enterflag = 0;
}

/* Exported functions ----------------------------------------------------------*/
/*********************************************************************************************************
** Function name:
** Descriptions:        ͨѶ�ڳ�ʼ��
** input parameters:    fifo_Id :  �����ͨѶ����;
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void FIFO_Init(uint8_t fifo_Id, FIFOMailBox_CFG_TypeDef fifo_cfg)
{
    FIFOMailBox_TypeDef *fifoPort = &FIFOMailBox[fifo_Id];

    if (fifo_Id >= SCOM_PORT_MAX)
    {
        return;
    }

    fifoPort->RxBuffer = fifo_cfg.RxBuffer;
    fifoPort->TxBuffer = fifo_cfg.TxBuffer;
    fifoPort->RxBufferSize = fifo_cfg.RxBufferSize;
    fifoPort->TxBufferSize = fifo_cfg.TxBufferSize;
    fifo_ClearBuffer(fifo_Id);
}

/*********************************************************************************************************
** Function name:
** Descriptions:      ��������
** input parameters:    fifo_Id :  �����ͨѶ����;
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void FIFO_StartSend(uint8_t fifo_Id, uint16_t fifo_txlen, uint8_t*TxBuffer)
{
    uint8_t UartId;
    //    uint16_t sendlen;
    FIFOMailBox_TypeDef *fifoPort = &FIFOMailBox[fifo_Id];

    if (fifo_Id >= SCOM_PORT_MAX)
    {
        return;
    }

    if (fifo_txlen > 0)
    {
        fifoPort->TxCount = fifo_txlen;
        UartId = (uint8_t)BSP_UartId_Get((eScomPort_TypeDef)fifo_Id);
        fifoPort->TxBuffer = TxBuffer;
        if (UartId < UARTx_ID) //����ͨѶ
        {
            Rn8xxx_Uart_SttConfig(UartId, USART_IT_RX, DISABLE);  //�����жϽ�ֹ
            Rn8xxx_Uart_SttConfig(UartId, USART_IT_TX, ENABLE); //�����ж�ʹ��
            Rn8xxx_Uart_Write(UartId, fifoPort->TxBuffer[0]);//���ô�����������������
            fifoPort->TxPointer++;
            fifoPort->TxCount --;
        }
        /*
        else//SPISͨѶ
        {
        if(fifoPort->TxCount <= SPIS_MAX_DEPTH)
        {
        sendlen = fifoPort->TxCount;
        fifoPort->TxPointer = fifoPort->TxCount;
        fifoPort->TxCount = 0;
        }
        else
        {
        sendlen = SPIS_MAX_DEPTH;
        fifoPort->TxPointer += SPIS_MAX_DEPTH;
        fifoPort->TxCount -= SPIS_MAX_DEPTH;
        }

        fnSpis_FlTXFIFO(sendlen, fifoPort->TxBuffer);
        }
        */
    }
}

/*********************************************************************************************************
** Function name:       FIFO_Info
** Descriptions:
** input parameters:   fifo_Id :  �����ͨѶ����;
**
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
uint16_t FIFO_Info(uint8_t fifo_Id)
{
    FIFOMailBox_TypeDef *fifoPort = &FIFOMailBox[fifo_Id];

    if (fifo_Id >= SCOM_PORT_MAX)
    {
        return 0;
    }
    return  fifoPort->RxCount;
}

/*********************************************************************************************************
** Function name:
** Descriptions:      ͨѶ�����жϷ������
** input parameters:    fifo_Id :  �����ͨѶ����;
**                  fifo_Rx:    ѹ�������;
**                  fifo_RxCount:ѹ�����ݸ���;
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void FIFO_Re_HANDLER(uint8_t fifo_Id, uint8_t* fifo_Rx, uint8_t fifo_RxCount)
{
    FIFOMailBox_TypeDef *fifoPort = &FIFOMailBox[fifo_Id];
    //uint8_t i;
    uint16_t Count = 0;

    if (fifoPort->enterflag == SPIS_ENTER_FLAG)
    {
        return;
    }
    else
    {
        fifoPort->enterflag = SPIS_ENTER_FLAG;
    }
    if (fifo_RxCount <= (fifoPort->RxBufferSize - fifoPort->RxCount))
    {
        Count = fifo_RxCount;
    }
    else
    {
        Count = (fifoPort->RxBufferSize - fifoPort->RxCount);
    }

    Std_Memcpy((fifoPort->RxBuffer + fifoPort->RxPointer), &(fifo_Rx[0]), Count);

    fifoPort->RxPointer += Count;
    fifoPort->RxCount += Count;

    fifoPort->enterflag = 0;
}

/*********************************************************************************************************
** Function name:       ͨѶ�����жϷ������
** Descriptions:
** input parameters:    fifo_Id :  �����ͨѶ����;
**                  fifo_Tx:  ����������;
**                  fifo_TxCount:�ڴ����͵�����
** output parameters:   None
** Returned value:     :ErrorStatus ��0 �ɴ��������ݳ��ȣ�0���ͻ����
*********************************************************************************************************/
uint8_t FIFO_Tx_HANDLER(uint8_t fifo_Id, uint8_t*fifo_Tx, uint8_t fifo_TxCount)
{
    FIFOMailBox_TypeDef *fifoPort = &FIFOMailBox[fifo_Id];
    uint8_t Count = 0;
    if (fifoPort->TxCount > 0)
    {
        if (fifoPort->TxCount >= fifo_TxCount)
        {
            Count = fifo_TxCount;
        }
        else
        {
            Count = fifoPort->TxCount;
        }
        Std_Memcpy(fifo_Tx, (fifoPort->TxBuffer + fifoPort->TxPointer), Count);
        fifoPort->TxPointer += Count;
        fifoPort->TxCount -= Count;
    }
    else
    {
        Count = 0;
    }
    return Count;
}

/****************************  (C) COPYRIGHT Renergy  ****************************/
/****************************          END OF FILE          ****************************/
