/****************************************************************************
* @file     Uart.h
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.04.28
* @brief    Uart����
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _Rn8xxx_UART_H
#define _Rn8xxx_UART_H

/* Includes ------------------------------------------------------------------*/
//#include <includes.h>

/* Exported define ------------------------------------------------------------*/

#define UARTCTL_DEFAULT    0x00   //UART_CTL �Ĵ�����λĬ��ֵ

#define UART_DMA_RX_ERR_IE      BIT5    //  �������ݸ����ж�ʹ��
#define UART_DMA_TX_ERR_IE      BIT4    //  �������ݴ����ж�ʹ��
#define UART_DMA_RX_FIE     BIT3    //  DMA����ȫ���ж�ʹ��
#define UART_DMA_RX_HIE     BIT2    //  DMA���հ����ж�ʹ��
#define UART_DMA_TX_FIE     BIT1    //  DMA����ȫ���ж�ʹ��
#define UART_DMA_TX_HIE     BIT0    //  DMA���Ͱ����ж�ʹ��

/* Exported enum ------------------------------------------------------------*/
typedef enum
{
    UART0_ID = 0,
    UART1_ID = 1,
    UART2_ID = 2,
    UART3_ID = 3,
    UART4_ID = 4,
    UART5_ID = 5,
    UARTx_ID = 6,
} eUART_ID_TypeDef;

typedef enum
{
    UART_BPS_300        = 300,  //������
    UART_BPS_600        = 600,
    UART_BPS_1200       = 1200,
    UART_BPS_2400       = 2400,
    UART_BPS_4800       = 4800,
    UART_BPS_7200       = 7200,
    UART_BPS_9600       = 9600,
    UART_BPS_14400      = 14400,
    UART_BPS_19200      = 19200,
    UART_BPS_38400      = 38400,
    UART_BPS_57600      = 56700,
    UART_BPS_115200     = 115200,
} eUART_BPS_TypeDef;

typedef enum
{
    UARTCTL_NEG_H   = 0x00,     /*"Ĭ��������ƽΪ�ߣ�����/���յ����ݼ��Բ���"*/
    UARTCTL_NEG_L   = 0x01,    /*"Ĭ��������ƽΪ�ͣ�����/���յ����ݼ���ȡ��"*/

    UARTCTL_LSB     = 0x00,     /*"LSB�ȴ���"*/
    UARTCTL_MSB     = 0x01,     /*"MSB�ȴ���"*/

    UARTCTL_IRSEL_H     = 0x00,     /*"�����ԣ����͵�ƽ����������ߵ�ƽ��Ĭ��״̬������"*/
    UARTCTL_IRSEL_L     = 0x01,     /*"�����ԣ�������ȡ�����ߵ�ƽ����������͵�ƽ����"*/
    //-IRSEL ֻ���������������Ч��ƽ��ʱ�ĵ�ƽ�ߵͣ���Ӱ����Ч�����ڼ�ĵ�ƽ

    UARTCTL_ILBE_DIS    = 0x00,
    UARTCTL_ILBE_EN     = 0x01,

    UARTCTL_IRE_DIS     = 0x00,     /*"�رպ���������"*/
    UARTCTL_IRE_EN      = 0x01,     /*"�򿪺������������� 38k �ز�����������ݵĵ͵�ƽ"*/

    UARTCTL_NO_PARITY   = 0x00,     /*"��У��"*/
    UARTCTL_ODD_PARITY      = 0x01,     /*"��У��"*/
    UARTCTL_EVEN_PARITY     = 0x02,     /*"żУ��"*/
    UARTCTL_0_PARITY        = 0x03,     /*"�̶�Ϊ��У��"*/
    UARTCTL_1_PARITY        = 0x04,     /*"�̶�Ϊ 1 У��"*/

    UARTCTL_5BIT_DAT    = 0x00, //����λ
    UARTCTL_6BIT_DAT   = 0x01,
    UARTCTL_7BIT_DAT    = 0x02,
    UARTCTL_8BIT_DAT   = 0x03,

    UARTCTL_1STOP_SBIT      = 0x00, //ֹͣλ
    UARTCTL_2STOP_SBIT      = 0x01,

    UARTCTL_ERRIE_DIS   = 0x00,
    UARTCTL_ERRIE_EN    = 0x01,

    UARTCTL_RXIE_DIS    = 0x00,
    UARTCTL_RXIE_EN     = 0x01,

    UARTCTL_TXIE_DIS    = 0x00,
    UARTCTL_TXIE_EN     = 0x01,

    UARTCTL_DIS     = 0x00,
    UARTCTL_EN      = 0x01,
} eUART_CtlPara_TypeDef;

typedef enum {USART_IT_RX = 0, USART_IT_TX = !USART_IT_RX} FunctionalMODE;

typedef union
{
    struct
    {
        uint32_t    UartCtl_EN: 1;
        uint32_t    UartCtl_TXIE: 1;
        uint32_t    UartCtl_RXIE: 1;
        uint32_t    UartCtl_ERRIE: 1;
        uint32_t    UartCtl_STOPS: 1;
        uint32_t    UartCtl_DATLEN: 2;
        uint32_t    UartCtl_PARS: 3;
        uint32_t    UartCtl_IRE: 1;
        uint32_t    UartCtl_ILBE: 1;
        uint32_t    UartCtl_IRSEL: 1;
        uint32_t    UartCtl_LMSB: 1;
        uint32_t    UartCtl_NEG: 1;
    };
    uint32_t gUARTCtl;
} uUART_CtlPara_TypeDef;

/*UART DMA����*/
typedef enum
{
    UART_DMA_TX_DIS = 0,
    UART_DMA_TX_EN = 1,

    UART_DMA_RX_DIS = 0,
    UART_DMA_RX_EN = 1,

    UART_DMA_TX_CYC_DIS = 0,
    UART_DMA_TX_CYC_EN = 1,

    UART_DMA_RX_CYC_DIS = 0,
    UART_DMA_RX_CYC_EN = 1,
} eUART_DMACtlPara_TypeDef;

typedef union
{
    struct
    {
        u32 UART_DMACtl_TX_DMA_EN: 1; //   ����DMAʹ��
        u32 UART_DMACtl_RX_DMA_EN: 1; //   ����DMAʹ��
        u32 UART_DMACtl_TX_CYC_MODE: 1; //����ѭ��ģʽʹ��
        u32 UART_DMACtl_RX_CYC_MODE: 1; //����ѭ��ģʽʹ��
    };
    u32 gUART_DMACtl;
} uUART_DMACtlPara_TypeDef;

typedef struct
{
    uUART_DMACtlPara_TypeDef CTL;
    u32 TBADR;
    u32 RBADR;
    u32 TLEN;
    u32 RLEN;
    u8  IE;
} uUART_DMAPara_TypeDef;

/* Exported data ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void Rn8xxx_Uart_Init(eUART_ID_TypeDef uart_id, eUART_BPS_TypeDef bsp, uUART_CtlPara_TypeDef ctlpara);
extern void Rn8xxx_Uart_SttConfig(uint8_t uart_id, FunctionalMODE USART_IT, FunctionalState NewState);

extern UART_TypeDef *Rn8xxx_Uart_GetRegAddr(eUART_ID_TypeDef uart_id);
s32 Rn8xxx_Uart_Read(u8 uartid);
void Rn8xxx_Uart_Write(u8 uartid, u8 data);
extern void Rn8xxx_Uart_Clr_STA(u8 uartid, u16 temp);
BOOL Rn8xxx_Uart_IRQCheck(u8 uartid);
extern BOOL Rn8xxx_UartDMA_IRQCheck(u8 uartid);
extern void Rn8xxx_UART_DMAInit(eUART_ID_TypeDef uart_id, uUART_DMAPara_TypeDef UART_DMAPara);
extern u16 Rn8xxx_Uart_DMA_RxInfo(eUART_ID_TypeDef uart_id);
extern u16 Rn8xxx_Uart_DMA_TxInfo(eUART_ID_TypeDef uart_id);
#endif  //_UART_H
/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
