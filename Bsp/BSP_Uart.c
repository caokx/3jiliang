/****************************************************************************
* @file     BSP_Uart.c
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
/* Private define ------------------------------------------------------------*/
#include <BSP.h>
#include <Scom.h>
/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
    eScomPort_TypeDef   Scom;
    eUART_ID_TypeDef    UartID;
    u8  DMAEnOrDis;
} sScomPort_UartID_TypeDef;

/* Private data ---------------------------------------------------------*/
//#if(nPhs == ThreePhs)

//  #if(RN8xxx_Ver==RN8xxx_V2)
//  sScomPort_UartID_TypeDef ScomPort_UartID_Table[] =
//  {
//      {SCOM_PORT_RS485A,  UART4_ID , UART_DMA_EN},   //V2�汾оƬ����DMA����
//      {SCOM_PORT_RS485B,      UART4_ID , UART_DMA_EN},
//      {SCOM_PORT_IR,  UART1_ID , UART_DMA_EN},
//      {SCOM_PORT_ZBCOM,   UART3_ID , UART_DMA_EN},
//  };
//  #else
//  sScomPort_UartID_TypeDef ScomPort_UartID_Table[] =
//  {
//      {SCOM_PORT_RS485A,  UART4_ID , UART_DMA_DIS},   //V1�汾оƬ��DMA����
//      {SCOM_PORT_RS485B,      UART4_ID , UART_DMA_DIS},
//      {SCOM_PORT_IR,  UART1_ID , UART_DMA_DIS},
//      {SCOM_PORT_ZBCOM,   UART3_ID , UART_DMA_DIS},
//  };
//  #endif
//#else

//#if(PCB_Version ==  RN8611_RN8209D)
sScomPort_UartID_TypeDef ScomPort_UartID_Table[] =
{
    {SCOM_PORT_RS485A,  UART0_ID, UART_DMA_EN},     //V2�汾оƬ����DMA����
};

//#elif(PCB_Version ==  RN8613V2_RN8209DV4)
//  sScomPort_UartID_TypeDef ScomPort_UartID_Table[] =
//  {
//      {SCOM_PORT_ZBCOM,  UART0_ID , UART_DMA_EN},    //V2�汾оƬ����DMA����
//
//  };

//#else
//  #if(RN8xxx_Ver==RN8xxx_V2)
//  sScomPort_UartID_TypeDef ScomPort_UartID_Table[] =
//  {
//      {SCOM_PORT_RS485A,  UART0_ID , UART_DMA_EN},    //V2�汾оƬ����DMA����
//      {SCOM_PORT_IR,  UART1_ID , UART_DMA_EN},
//      {SCOM_PORT_ZBCOM,   UART3_ID , UART_DMA_EN},
//
//  };
//  #else
//  sScomPort_UartID_TypeDef ScomPort_UartID_Table[] =
//  {
//      {SCOM_PORT_RS485A,  UART0_ID , UART_DMA_DIS},   //V1�汾оƬ��DMA����
//      {SCOM_PORT_IR,  UART1_ID , UART_DMA_DIS},
//      {SCOM_PORT_ZBCOM,   UART3_ID , UART_DMA_DIS},
//
//  };
//  #endif
//
//#endif

//#endif

const eUART_BPS_TypeDef UsartBps_Def[9] =
{
    UART_BPS_300,
    UART_BPS_600,
    UART_BPS_1200,
    UART_BPS_2400,
    UART_BPS_4800,
    UART_BPS_7200,
    UART_BPS_9600,
    UART_BPS_19200,
    UART_BPS_115200
};

const u32 BpsTable[] = {300, 600, 1200, 2400, 4800, 7200, 9600, 19200, 115200};

/* Exported data ----------------------------------------------------------*/
extern sComPack_TypeDef     ComPack[SCOM_PORT_MAX]; //��Dl645_Globals.h�ж��塣

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/*********************************************************************************************************
** Function name:
** Descriptions:
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
eUART_ID_TypeDef BSP_UartId_Get(eScomPort_TypeDef Scom)
{
    uint8_t i;
    for (i = 0; i < sizeof(ScomPort_UartID_Table) / sizeof(ScomPort_UartID_Table[0]); i++)
    {
        if (Scom == ScomPort_UartID_Table[i].Scom)
        {
            return  ScomPort_UartID_Table[i].UartID;
        }
    }

    return  ScomPort_UartID_Table[0].UartID;//todo
}

/*********************************************************************************************************
** Function name:       BSP_Scom_Port_Get
** Descriptions:
** input parameters:    uart_id:the serial no of uart;
** output parameters:
** Returned value:     Scom_Port
*********************************************************************************************************/
eScomPort_TypeDef BSP_Scom_Get(eUART_ID_TypeDef UartId)
{
    uint8_t i;
    for (i = 0; i < sizeof(ScomPort_UartID_Table) / sizeof(ScomPort_UartID_Table[0]); i++)
    {
        if (UartId == ScomPort_UartID_Table[i].UartID)
        {
            return  ScomPort_UartID_Table[i].Scom;
        }
    }

    return  ScomPort_UartID_Table[0].Scom;//
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void BSP_UartId_DMAEnOrDis_Get(eScomPort_TypeDef Scom, eUART_ID_TypeDef *UartId, u8 *DMAEnOrDis)
{
    uint8_t i, res = ERROR;
    for (i = 0; i < sizeof(ScomPort_UartID_Table) / sizeof(ScomPort_UartID_Table[0]); i++)
    {
        if (Scom == ScomPort_UartID_Table[i].Scom)
        {
            *UartId = ScomPort_UartID_Table[i].UartID;
            *DMAEnOrDis = ScomPort_UartID_Table[i].DMAEnOrDis;
            res = SUCCESS;
            break;
        }
    }

    if (res == ERROR)
    {
        *UartId = ScomPort_UartID_Table[0].UartID;
        *DMAEnOrDis = ScomPort_UartID_Table[0].DMAEnOrDis;
    }
}

/*********************************************************************************************************
** Function name:       BSP_Scom_Port_Get
** Descriptions:
** input parameters:    uart_id:the serial no of uart;
** output parameters:
** Returned value:     Scom_Port
*********************************************************************************************************/
void BSP_Scom_DMAEnOrDis_Get(eUART_ID_TypeDef UartId, eScomPort_TypeDef *Scom,  u8 *DMAEnOrDis)
{
    uint8_t i, res = ERROR;
    for (i = 0; i < sizeof(ScomPort_UartID_Table) / sizeof(ScomPort_UartID_Table[0]); i++)
    {
        if (UartId == ScomPort_UartID_Table[i].UartID)
        {
            *Scom = ScomPort_UartID_Table[i].Scom;
            *DMAEnOrDis = ScomPort_UartID_Table[i].DMAEnOrDis;
            res = SUCCESS;
            break;
        }
    }

    if (res == ERROR)
    {
        *Scom = ScomPort_UartID_Table[i].Scom;
        *DMAEnOrDis = ScomPort_UartID_Table[i].DMAEnOrDis;
    }
}

/* Exported functions ----------------------------------------------------------*/
/*********************************************************************************************************
** Function name:     BSP_Uart_Init
** Descriptions:        init uart configuration including IO and uart parameters(check mode, baudrate, stop bis, data lenth )
** input parameters:  ComPort:  Cfg: bit1:0 = lenth; bit3:2 = check mode; bit4: lenth of stop bits; bit7:5 = baudrate
** output parameters: null
** Returned value:      null
*********************************************************************************************************/
void BSP_Uart_Init(eScomPort_TypeDef scom_id, uint8_t bsp)
{
    eUART_ID_TypeDef uart_id;
    eUART_BPS_TypeDef uart_bsp;
    u8 uart_dmaEnOrDis;
    uUART_CtlPara_TypeDef  UartPara;

    BSP_UartId_DMAEnOrDis_Get(scom_id, &uart_id, &uart_dmaEnOrDis);

    switch (bsp)
    {
        case USART_BPS_300:     //300
            uart_bsp = UART_BPS_300;
            break;
        case USART_BPS_600:     //600
            uart_bsp = UART_BPS_600;
            break;
        case USART_BPS_1200:    //1200
            uart_bsp = UART_BPS_1200;
            break;
        case USART_BPS_2400:    //2400
            uart_bsp = UART_BPS_2400;
            break;
        case USART_BPS_4800:    //4800
            uart_bsp = UART_BPS_4800;
            break;
        case USART_BPS_9600:    //9600
            uart_bsp = UART_BPS_9600;
            break;
        case USART_BPS_19200:   //
            uart_bsp = UART_BPS_19200;
            break;
        case USART_BPS_38400:   //
            uart_bsp = UART_BPS_38400;
            break;
        case USART_BPS_57600:   //
            uart_bsp = UART_BPS_57600;
            break;
        case USART_BPS_115200:  //
            uart_bsp = UART_BPS_115200;
            break;
        default:
            uart_bsp = UART_BPS_115200;
            break;
    }

    if (SCOM_PORT_IR == scom_id)
    {
        UartPara.gUARTCtl = UARTCTL_DEFAULT; //��λֵ��Ĭ��ֵ

        UartPara.UartCtl_EN = UARTCTL_EN;
        UartPara.UartCtl_RXIE = UARTCTL_RXIE_EN;
        UartPara.UartCtl_ERRIE = UARTCTL_ERRIE_EN;
        UartPara.UartCtl_STOPS = UARTCTL_1STOP_SBIT;
        UartPara.UartCtl_DATLEN = UARTCTL_8BIT_DAT;
        UartPara.UartCtl_PARS = UARTCTL_EVEN_PARITY;
        UartPara.UartCtl_IRE = UARTCTL_IRE_EN;

        //--������Ƽ���ѡ��,��ͨѶʱΪ�͵�ƽ����Ҫ���ǲ�ͨѶʱ��������--------
        #if(nPhs == ThreePhs)
        UartPara.UartCtl_IRSEL = UARTCTL_IRSEL_L;
        #else
        UartPara.UartCtl_IRSEL = UARTCTL_IRSEL_H;
        #endif

        Rn8xxx_Uart_Init(uart_id, uart_bsp, UartPara);
        Rn8xxx_GPIO_CfgFun(PinRXD_IR, (_UART0 + uart_id)); /*"����ͨ�����ս�"*/
        Rn8xxx_GPIO_CfgFun(PinTXD_IR, (_UART0 + uart_id)); /*"����ͨ�����ͽ�"*/
        Rn8xxx_GPIO_CfgPullMode(PinRXD_IR, Pull_ON);
    }
    else if (SCOM_PORT_ZBCOM == scom_id)
    {
        UartPara.gUARTCtl = UARTCTL_DEFAULT; //��λֵ��Ĭ��ֵ

        UartPara.UartCtl_EN = UARTCTL_EN;
        UartPara.UartCtl_RXIE = UARTCTL_RXIE_EN;
        UartPara.UartCtl_ERRIE = UARTCTL_ERRIE_EN;
        UartPara.UartCtl_STOPS = UARTCTL_1STOP_SBIT;
        UartPara.UartCtl_DATLEN = UARTCTL_8BIT_DAT;
        UartPara.UartCtl_PARS = UARTCTL_EVEN_PARITY;
        UartPara.UartCtl_IRE = UARTCTL_IRE_DIS;
        UartPara.UartCtl_IRSEL = UARTCTL_IRSEL_H;

        Rn8xxx_Uart_Init(uart_id, uart_bsp, UartPara);

        Rn8xxx_GPIO_CfgFun(PinRXD_ZB, (_UART0 + uart_id)); /*"�ز�ͨ�����ս�"*/
        Rn8xxx_GPIO_CfgFun(PinTXD_ZB, (_UART0 + uart_id)); /*"�ز�ͨ�����ͽ�"*/
    }
    else if (SCOM_PORT_RS485A == scom_id)
    {
        UartPara.gUARTCtl = UARTCTL_DEFAULT; //��λֵ��Ĭ��ֵ

        UartPara.UartCtl_EN = UARTCTL_EN;
        //UartPara.UartCtl_RXIE= UARTCTL_RXIE_EN;
        //UartPara.UartCtl_ERRIE= UARTCTL_ERRIE_EN;
        UartPara.UartCtl_STOPS = UARTCTL_1STOP_SBIT;
        UartPara.UartCtl_DATLEN = UARTCTL_8BIT_DAT;
        UartPara.UartCtl_PARS = UARTCTL_EVEN_PARITY;
        UartPara.UartCtl_IRE = UARTCTL_IRE_DIS;
        UartPara.UartCtl_IRSEL = UARTCTL_IRSEL_H;

        Rn8xxx_Uart_Init(uart_id, uart_bsp, UartPara);
        Rn8xxx_GPIO_CfgFun(PinRXD485, (_UART0 + uart_id)); /*"485ͨ�����ս�"*/
        Rn8xxx_GPIO_CfgFun(PinTXD485, (_UART0 + uart_id)); /*"485ͨ�����ͽ�"*/
        #if(KeLu==TRUE)
        Rn8xxx_GPIO_CfgIOMode(PinRXD485, GPIO_MODE_IN, TTL_IN);         //kelu
        #endif
    }

    #if(SCOM_PORT_MAX==4)
    else if (SCOM_PORT_RS485B == scom_id)
    {
        UartPara.gUARTCtl = UARTCTL_DEFAULT; //��λֵ��Ĭ��ֵ

        UartPara.UartCtl_EN = UARTCTL_EN;
        UartPara.UartCtl_RXIE = UARTCTL_RXIE_EN;
        UartPara.UartCtl_ERRIE = UARTCTL_ERRIE_EN;
        UartPara.UartCtl_STOPS = UARTCTL_1STOP_SBIT;
        UartPara.UartCtl_DATLEN = UARTCTL_8BIT_DAT;
        UartPara.UartCtl_PARS = UARTCTL_EVEN_PARITY;
        UartPara.UartCtl_IRE = UARTCTL_IRE_DIS;
        UartPara.UartCtl_IRSEL = UARTCTL_IRSEL_H;

        Rn8xxx_Uart_Init(uart_id, uart_bsp, UartPara);
        Rn8xxx_GPIO_CfgFun(PinRXD485, (_UART0 + uart_id)); /*"485Bͨ�����ս�"*/
        Rn8xxx_GPIO_CfgFun(PinTXD485, (_UART0 + uart_id)); /*"485Bͨ�����ͽ�"*/
    }
    #endif

    Rn8xxx_Uart_SttConfig(uart_id, USART_IT_TX, DISABLE);  //�����жϽ�ֹ
    Rn8xxx_Uart_SttConfig(uart_id, USART_IT_RX, DISABLE); //�����ж�ʹ��

    if (uart_id == UART4_ID)
    {
        NVIC_EnableIRQ(UART4_IRQn);    //485
    }
    else if (uart_id == UART5_ID)
    {
        NVIC_EnableIRQ(UART5_IRQn);
    }
    else
    {
        NVIC_EnableIRQ(UART0_IRQn + uart_id);
    }

    return;
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** input parameters:
** output parameters: null
** Returned value:      null
*********************************************************************************************************/
u8 BSP_UartDMA_IRQCheck(eScomPort_TypeDef ComPort)
{
    eUART_ID_TypeDef uart_id;
    u8 uart_dmaEnOrDis;
    u8 res = true;

    BSP_UartId_DMAEnOrDis_Get(ComPort, &uart_id, &uart_dmaEnOrDis);

    if (uart_dmaEnOrDis == UART_DMA_EN)
    {
        if (Rn8xxx_UartDMA_IRQCheck(uart_id) == false)
        {
            res = false;
        }
    }

    return res;
}

/*********************************************************************************************************
** Function name:     BSP_Uart2_DMAInit
** Descriptions:
** input parameters:
** output parameters: null
** Returned value:      null
*********************************************************************************************************/
void BSP_Uart_DMAInit(eScomPort_TypeDef ComPort, uUART_DMAPara_TypeDef uart_dma_para)
{
    eUART_ID_TypeDef uart_id;
    u8 uart_dmaEnOrDis;

    BSP_UartId_DMAEnOrDis_Get(ComPort, &uart_id, &uart_dmaEnOrDis);

    if (uart_dmaEnOrDis == UART_DMA_EN)   //DMAʹ��
    {
        Rn8xxx_UART_DMAInit(uart_id, uart_dma_para);
    }
}

//---------------------------------------------------
//�����˿ڹ�������ʽ���ơ�
void USART_ITConfig(u8 ComPort, FunctionalMODE USART_IT, FunctionalState NewState)
{
    u8 Compose;
    eUART_ID_TypeDef uart_id;

    uart_id = BSP_UartId_Get(ComPort);

    Rn8xxx_Uart_SttConfig(uart_id, USART_IT, NewState);

    Compose = (USART_IT << 1) | (NewState);

    if (Compose == ((USART_IT_TX << 1) | ENABLE))
    {
        Rn8xxx_Uart_Write(uart_id, *(ComPack[ComPort].pTx++));
        ComPack[ComPort].TxLen--;
    }
    return;
}

void BSP_TxEnDis(u8 ComPort, FunctionalState EnOrDis)   //�շ�����DIR
{
    switch (ComPort)  //
    {
        case SCOM_PORT_RS485A:
            Rn8xxx_GPIO_CfgFun(Pin485RE, _NORMALIO); /*"485ͨ���շ����ƽ�"*/
            Rn8xxx_GPIO_CfgIOMode(Pin485RE, GPIO_MODE_OUT, NORMAL_OUT);
            if (EnOrDis == ENABLE)
            {
                Rn8xxx_GPIO_SetPin(Pin485RE, 0);
            }
            else
            {
                Rn8xxx_GPIO_SetPin(Pin485RE, 1);
            }
            break;
            #if(SCOM_PORT_MAX==4)
        case SCOM_PORT_RS485B:
            Rn8xxx_GPIO_CfgFun(Pin485BRE, _NORMALIO); /*"485ͨ���շ����ƽ�"*/
            Rn8xxx_GPIO_CfgIOMode(Pin485BRE, GPIO_MODE_OUT, NORMAL_OUT);
            if (EnOrDis == ENABLE)
            {
                Rn8xxx_GPIO_SetPin(Pin485BRE, 0);
            }
            else
            {
                Rn8xxx_GPIO_SetPin(Pin485BRE, 1);
            }
            break;
            #endif
        default:
            break;
    }
}

/*********************************************************************************************************
** Function name:       BSP_UartCtrlandDmaRxCheck
** Descriptions:        ���ͨ�Ŷ˿ںŶ�Ӧ��UART��ʹ���Լ�DMA����ʹ���Ƿ��
** input parameters:    Scom��Scom���͵�ͨ�Ŷ˿ں�
** output parameters:   none
** Returned value:      ��������SUCCESS�����󷵻�ERROR
*********************************************************************************************************/
const u32 UartBaseAddr[] = {UART0_BASE, UART1_BASE, UART2_BASE, UART3_BASE, UART4_BASE, UART5_BASE};
ErrorStatus BSP_UartCtrlandDmaRxCheck(eScomPort_TypeDef Scom)
{
    //ErrorStatus ret;
    eUART_ID_TypeDef uartid;
    UART_TypeDef* uartx;

    uartid = BSP_UartId_Get(Scom);
    uartx = (UART_TypeDef*)UartBaseAddr[uartid];
    if ((uartx->CTRL & 0x01) && (uartx->DMA_CTRL & 0x02))
    {
        return (SUCCESS);
    }
    else
    {
        return (ERROR);
    }
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
