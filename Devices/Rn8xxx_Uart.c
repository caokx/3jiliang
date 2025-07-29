/****************************************************************************
* @file     Uart.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.04.28
* @brief    Uart����
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include "Rn8xxx_Uart.h"

/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*********************************************************************************************************
** Function name:       *Rn8xxx_Uart_GetRegAddr
** Descriptions:        get the UART address
** input parameters:    uart_id:the serial no of uart;
** output parameters:   None
** Returned value:     related UART address
*********************************************************************************************************/
UART_TypeDef *Rn8xxx_Uart_GetRegAddr(eUART_ID_TypeDef uart_id)
{
    if (uart_id == UART0_ID)
    {
        return UART0;
    }
    else if (uart_id == UART1_ID)
    {
        return UART1;
    }
    else if (uart_id == UART2_ID)
    {
        return UART2;
    }
    else if (uart_id == UART3_ID)
    {
        return UART3;
    }
    else if (uart_id == UART4_ID)
    {
        return UART4;
    }
    else
    {
        return UART5;
    }
}

/* Exported functions ----------------------------------------------------------*/
/*********************************************************************************************************
** Function name:     Rn8xxx_Uart_Init
** Descriptions:        init uart configuration including IO and uart parameters(check mode, baudrate, stop bis, data lenth )
** input parameters:
** output parameters: null
** Returned value:      null
*********************************************************************************************************/
void Rn8xxx_Uart_Init(eUART_ID_TypeDef uart_id, eUART_BPS_TypeDef bsp, uUART_CtlPara_TypeDef ctlpara)
{
    u32 ClkDiv = 0;
    float fClkDiv = 0;
    UART_TypeDef *UARTi = NULL;

    /*"��ȡ������UART��ַ"*/
    UARTi = Rn8xxx_Uart_GetRegAddr(uart_id);

    /*"����GPIO��APBʱ��"*/
    SysCtl_EnableWrite;
    /*"������ӦUART��APBʱ��"*/
    switch (uart_id)
    {
        case UART0_ID:
            UART0_Clk_En;
            break;
        case UART1_ID:
            UART1_Clk_En;
            break;
        case UART2_ID:
            UART2_Clk_En;
            break;
        case UART3_ID:
            UART3_Clk_En;
            break;
        case UART4_ID:
            UART4_Clk_En;
            break;
        case UART5_ID:
            UART5_Clk_En;
            break;
        default:
            break;
    }

    /*"����UARTͨѶ������"*/
    ClkDiv = SystemCoreClock;/*"��ȡ��ǰϵͳʱ��    "*/
    fClkDiv = ((float)ClkDiv) / ((float)(bsp * 16));

    ClkDiv = (u32)fClkDiv;
    UARTi->BAUD = ClkDiv - 1;
    UARTi->FDIV = (u32)((fClkDiv - ClkDiv) * 16384 + 0.5);

    /*"����UARTģʽ������"*/
    UARTi->CTRL = ctlpara.gUARTCtl;

    if (ctlpara.UartCtl_IRE == UARTCTL_IRE_EN)
    {
        UART38K_Clk_En;
    }

    return;
}

/*********************************************************************************************************
** Function name:     fnUART_ITConfig
** Descriptions:        modify uart state
** input parameters:  ComPort:   USART_IT: transmition direction as tx or rx;
                                            NewState: enable of disable corresponding transmition
** output parameters: null
** Returned value:      null
*********************************************************************************************************/
void Rn8xxx_Uart_SttConfig(uint8_t uart_id, FunctionalMODE USART_IT, FunctionalState NewState)
{
    uint8_t Compose;
    UART_TypeDef *UARTi = NULL;

    UARTi = Rn8xxx_Uart_GetRegAddr((eUART_ID_TypeDef)uart_id);
    Compose = (USART_IT << 1) | (NewState);
    switch (Compose)
    {
        //-------------------------
        case (USART_IT_RX<<1)|DISABLE:  /*" ����|�ر�"*/
            UARTi->CTRL &= 0xfff3;      /*" ���ν����ж�,���ν��մ����ж�"*/
            UARTi->STA = 0x3d;          /*" ������жϱ�־�����մ����־"*/
            break;
        case (USART_IT_RX<<1)|ENABLE:   /*" ����|��"*/
            UARTi->CTRL |= 0x0c;        /*" ��������ж�,������մ����ж�"*/
            UARTi->STA = 0x3d;          /*" ������жϱ�־�����մ����־        "*/
            break;
        case (USART_IT_TX<<1)|DISABLE:  /*" ����|�ر�"*/
            UARTi->CTRL &= 0xfffd;      /*" ���η����ж�"*/
            UARTi->STA = 0x02;          /*" �巢���жϱ�־"*/
            break;
        case (USART_IT_TX<<1)|ENABLE:   /*" ����|��"*/
            UARTi->CTRL |= 0x02;        /*" �������ж�"*/
            UARTi->STA = 0x02;          /*" �巢���жϱ�־"*/

            break;
        default:
            break;
    }
    return;
}

s32 Rn8xxx_Uart_Read(u8 uartid)
{
    u8 temp = 0;
    UART_TypeDef *UARTi = NULL;
    UARTi = Rn8xxx_Uart_GetRegAddr((eUART_ID_TypeDef)uartid);

    temp = UARTi->RXD;

    return temp;
}

void Rn8xxx_Uart_Write(u8 uartid, u8 data)
{
    UART_TypeDef *UARTi = NULL;
    UARTi = Rn8xxx_Uart_GetRegAddr((eUART_ID_TypeDef)uartid);

    UARTi->TXD = data;
    return;
}

BOOL Rn8xxx_UartDMA_IRQCheck(u8 uartid)
{
    UART_TypeDef *UARTi = NULL;
    UARTi = Rn8xxx_Uart_GetRegAddr((eUART_ID_TypeDef)uartid);

    if ((UARTi->DMA_CTRL & 0x1) || (UARTi->DMA_CTRL & 0x2))
    {
        return true;
    }
    return false;
}

BOOL Rn8xxx_Uart_IRQCheck(u8 uartid)
{
    UART_TypeDef *UARTi = NULL;
    UARTi = Rn8xxx_Uart_GetRegAddr((eUART_ID_TypeDef)uartid);

    if ((UARTi->CTRL & 0x4) || (UARTi->CTRL & 0x2))
    {
        return true;
    }
    return false;
}

void Rn8xxx_Uart_Clr_STA(u8 uartid, u16 temp)
{
    UART_TypeDef *UARTi = NULL;
    UARTi = Rn8xxx_Uart_GetRegAddr((eUART_ID_TypeDef)uartid);

    UARTi->STA = temp;
}

/*********************************************************************************************************
** Function name:     fnUART_DMAInit
** Descriptions:
** input parameters:
** output parameters: null
** Returned value:      null
*********************************************************************************************************/
void Rn8xxx_UART_DMAInit(eUART_ID_TypeDef uart_id, uUART_DMAPara_TypeDef UART_DMAPara)
{
    UART_TypeDef *UARTi = NULL;

    /*"��ȡ������UART��ַ"*/
    UARTi = Rn8xxx_Uart_GetRegAddr(uart_id);

    /*"����GPIO��APBʱ��"*/
    SysCtl_EnableWrite;
    /*"������ӦUART��APBʱ��"*/
    switch (uart_id)
    {
        case UART0_ID:
            UART0_Clk_En;
            break;
        case UART1_ID:
            UART1_Clk_En;
            break;
        case UART2_ID:
            UART2_Clk_En;
            break;
        case UART3_ID:
            UART3_Clk_En;
            break;
        case UART4_ID:
            UART4_Clk_En;
            break;
        case UART5_ID:
            UART5_Clk_En;
            break;
        default:
            break;
    }

    UARTi->DMA_CTRL = 0;
    UARTi->DMA_TBADR = UART_DMAPara.TBADR;            /*offset = 0x1C*/
    UARTi->DMA_RBADR = UART_DMAPara.RBADR;            /*offset = 0x20*/
    UARTi->DMA_TLEN = UART_DMAPara.TLEN;             /*offset = 0x24*/
    UARTi->DMA_RLEN = UART_DMAPara.RLEN;             /*offset = 0x28*/
    UARTi->DMA_FLG = 0x3f;
    UARTi->DMA_IE = UART_DMAPara.IE;
    UARTi->DMA_CTRL = UART_DMAPara.CTL.gUART_DMACtl;
    return;
}

/*********************************************************************************************************
** Function name:       fnUart_DMA_RxInfo
** Descriptions:
** input parameters:        null
** output parameters:   Uart2 DMA?����?��DD�쨺y?Y3��?��
** Returned value:      null
*********************************************************************************************************/
u16 Rn8xxx_Uart_DMA_RxInfo(eUART_ID_TypeDef uart_id)
{
    u16 rx_count;
    UART_TypeDef *UARTi = NULL;

    /*"��ȡ������UART��ַ"*/
    UARTi = Rn8xxx_Uart_GetRegAddr(uart_id);

    rx_count = UARTi->DMA_RADR;
    rx_count    -= UARTi->DMA_RBADR;
    return rx_count;
}

/*********************************************************************************************************
** Function name:       fnUart_DMA_TxInfo
** Descriptions:
** input parameters:        null
** output parameters:   Uart2 DMA����?����DD�쨺y?Y3��?��
** Returned value:      null
*********************************************************************************************************/
u16 Rn8xxx_Uart_DMA_TxInfo(eUART_ID_TypeDef uart_id)
{
    u16 tx_count;
    UART_TypeDef *UARTi = NULL;

    /*"��ȡ������UART��ַ"*/
    UARTi = Rn8xxx_Uart_GetRegAddr(uart_id);

    tx_count = UARTi->DMA_TADR ;
    tx_count -= UARTi->DMA_TBADR;
    return tx_count;
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
