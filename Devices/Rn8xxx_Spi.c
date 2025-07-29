/****************************************************************************
* @file     Spi.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.04.30
* @brief    Spi驱动
******************************************************************************
* @attention
*
*
****************************************************************************/
/* Includes ------------------------------------------------------------------*/

#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include <Rn8xxx_Spi.h>
/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/
/*********************************************************************************************************
** Function name:     fnSpi_ReadByte
** Descriptions:     to get data spi received
** input parameters: spi_id no
** output parameters:  null
** Returned value:   spi received data
*********************************************************************************************************/
u8 Rn8xxx_Spi_ReadByte(u8 spi_id)
{
    SPI_TypeDef *SPIi;
    //获取要操作的SPI
    if (spi_id == SPI0_ID)
    {
        SPIi = SPI;
    }
    else if (spi_id == SPI1_ID)
    {
        SPIi = SPI1;
    }
    else if (spi_id == SPI2_ID)
    {
        SPIi = SPI2;
    }
    else if (spi_id == SPI3_ID)
    {
        SPIi = SPI3;
    }
    else
    {
        return 0;
    }
    SPIi->STA = 0Xff;//清状态
    SPIi->TX = 0xff;//往发送寄存器写数据，启动SPI时钟发送
    if (fnRegState_Detect((u32)(&SPIi->STA), 0, 1, SPI_TIMEOUT) == ERROR) //等待SPI传输完成
    {
        ;
    }
    return (SPIi->RX);
}

/*********************************************************************************************************
** Function name:     fnSpi_WriteByte
** Descriptions:    to send data through SPI
** input parameters:  spi_id:  dat: data to be send
** output parameters:  null
** Returned value: null
*********************************************************************************************************/
void Rn8xxx_Spi_WriteByte(u8 spi_id, u8 Dat)
{
    SPI_TypeDef *SPIi;

    if (spi_id == SPI0_ID)
    {
        SPIi = SPI;
    }
    else if (spi_id == SPI1_ID)
    {
        SPIi = SPI1;
    }
    else if (spi_id == SPI2_ID)
    {
        SPIi = SPI2;
    }
    else if (spi_id == SPI3_ID)
    {
        SPIi = SPI3;
    }
    else
    {
        return ;
    }

    SPIi->STA = 0Xff;//清状态
    SPIi->TX = Dat;//写待发送的数据

    if (fnRegState_Detect((u32)(&SPIi->STA), 0, 1, SPI_TIMEOUT) == ERROR) //等待发送完成
    {
        ;
    }
}

/*********************************************************************************************************
** Function name:       *Rn8xxx_Spi_GetRegAddr
** Descriptions:        get the SPI address
** input parameters:    spi_id:the serial no of Spi;
** output parameters:   None
** Returned value:     related SPI address
*********************************************************************************************************/
SPI_TypeDef *Rn8xxx_Spi_GetRegAddr(eSPI_ID_TypeDef spi_id)
{
    if (spi_id == SPI0_ID)
    {
        return SPI;
    }
    else if (spi_id == SPI1_ID)
    {
        return SPI1;
    }
    else if (spi_id == SPI2_ID)
    {
        return SPI2;
    }
    else
    {
        return SPI3;
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_Spi_Init
** Descriptions:        初始化SPI
** input parameters:    spi_id:第几个SPI;
                        MastSlav:主从选择
                        LMSB:传输BIT顺序
                        Mode:CPOL时钟极性/CPHA时钟相位选择
                        Width:数据宽度选择
                        SpiIE:数据中断选择通过  eSPICtl_IE_TypeDef的枚举. 例如(SPICtl_SCSN_NEG_IRQ_EN|SPICtl_SCSN_POS_IRQ_EN)
                        speed:单位HZ     .例如:500000表示500KHZ
** output parameters:   null
** Returned value:      null
*********************************************************************************************************/
void Rn8xxx_Spi_Init(eSPI_ID_TypeDef spi_id, uSPICtlPara_TypeDef spi_para, uint32_t speed)
{
    SPI_TypeDef *SPIi;

    uint32_t ClkDiv;
    uint8_t fClkDiv;

    SysCtl_EnableWrite;

    if (spi_id == SPI0_ID)
    {
        SPIi = SPI;
    }
    else if (spi_id == SPI1_ID)
    {
        SPIi = SPI1;
    }
    else if (spi_id == SPI2_ID)
    {
        SPIi = SPI2;
    }
    else if (spi_id == SPI3_ID)
    {
        SPIi = SPI3;
    }
    else
    {
        return;
    }

    SPI_Clk_En(spi_id);

    ClkDiv = SystemCoreClock;/*"获取当前系统时钟    "*/
    if ((2 * speed) > ClkDiv)
    {
        return;
    }
    fClkDiv = (uint8_t)((ClkDiv) / (2 * (speed)) - 1);
    spi_para.SPICtl_CLKDIV = fClkDiv;

    SPIi->CTRL =  spi_para.gSPICtl;
}

/*********************************************************************************************************
** Function name:     Rn8xxx_Spi_DMAInit
** Descriptions:        普通SPI DMA    支持 SPI0    SPI1
** input parameters:    spi_id:第几个SPI;
                        SpiDmaCtlPara: DMA 控制寄存器.  通过  eSPI_DMACtlPara_TypeDef的枚举
                        TbAdr:发送起始地址
                        RbAdr:接收起始地址
                        TLen:DMA 发送长度
                        RLen:DMA 接收长度
                        SPIDmaIE:DMA中断配置.通过  eSPIDMA_IE_TypeDef的枚举. 例如(SPI_DMA_TX_HIE|SPI_DMA_TX_FIE)

** output parameters: null
** Returned value:      null
*********************************************************************************************************/
void Rn8xxx_Spi_DMAInit(eSPI_ID_TypeDef spi_id, uSPI_DMAPara_TypeDef SpiDmaPara)
{
    SPI_TypeDef *SPIi;
    if (spi_id == SPI0_ID)
    {
        SPIi = SPI;
    }
    else if (spi_id == SPI1_ID)
    {
        SPIi = SPI1;
    }
    else if (spi_id == SPI2_ID)
    {
        SPIi = SPI2;
    }
    else if (spi_id == SPI3_ID)
    {
        SPIi = SPI3;
    }
    else
    {
        return;
    }

    SPIi->DMA_CTRL = 0;
    SPIi->DMA_TBADR = SpiDmaPara.TbAdr;            /*offset = 0x1C*/
    SPIi->DMA_RBADR = SpiDmaPara.RbAdr;            /*offset = 0x20*/
    SPIi->DMA_TLEN = SpiDmaPara.TLen;             /*offset = 0x24*/
    SPIi->DMA_RLEN = SpiDmaPara.RLen;             /*offset = 0x28*/
    SPIi->DMA_CTRL = SpiDmaPara.DmaCtl.gSPI_DMACtl;
    SPIi->DMA_FLG = 0x3f;
    SPIi->DMA_IE = SpiDmaPara.DmaIE;

    return;
}

void Rn8xxx_Spi_DMATxStar(eSPI_ID_TypeDef spi_id, u32 Addr, u32 TxLen, u16 CrcInit)
{
    SPI_TypeDef *SPIi;
    if (spi_id == SPI0_ID)
    {
        SPIi = SPI;
    }
    else if (spi_id == SPI1_ID)
    {
        SPIi = SPI1;
    }
    else if (spi_id == SPI2_ID)
    {
        SPIi = SPI2;
    }
    else if (spi_id == SPI3_ID)
    {
        SPIi = SPI3;
    }
    else
    {
        return;
    }
    SPIi->DMA_TBADR = (Addr & SPI_DMAAdrLen_MASK);
    SPIi->DMA_TLEN = (TxLen & SPI_DMAAdrLen_MASK);
    //SPIi->CRC_INIT =  CrcInit;
    SPIi->DMA_CTRL |=  SPI_DMA_TX_EN;
}

/*********************************************************************************************************
** Function name:       Rn8xxx_Spi_DMA_RxInfo
** Descriptions:
** input parameters:    null
** output parameters:   SPI DMA接收到的数据长度
** Returned value:      null
*********************************************************************************************************/
u32 Rn8xxx_Spi_DMA_RxInfo(eSPI_ID_TypeDef spi_id)
{
    u32 rx_count;
    SPI_TypeDef *SPIi = NULL;

    /*"获取待操作SPI地址"*/
    SPIi = Rn8xxx_Spi_GetRegAddr(spi_id);

    rx_count = SPIi->DMA_RADR;
    rx_count -= SPIi->DMA_RBADR;
    return (rx_count & SPI_DMAAdrLen_MASK);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_Spi_DMA_TxInfo
** Descriptions:
** input parameters:    null
** output parameters:   SPI DMA发送的数据长度
** Returned value:      null
*********************************************************************************************************/
u32 Rn8xxx_Spi_DMA_TxInfo(eSPI_ID_TypeDef spi_id)
{
    u32 tx_count;
    SPI_TypeDef *SPIi = NULL;

    /*"获取待操作SPI地址"*/
    SPIi = Rn8xxx_Spi_GetRegAddr(spi_id);

    tx_count = SPIi->DMA_TADR ;
    tx_count -= SPIi->DMA_TBADR;
    return (tx_count & SPI_DMAAdrLen_MASK);
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
