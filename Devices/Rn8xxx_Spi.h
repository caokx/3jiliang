/****************************************************************************
* @file     SPI.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.04.28
* @brief    SPI驱动
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _Rn8xxx_SPI_H
#define _Rn8xxx_SPI_H

/* Includes ------------------------------------------------------------------*/
/* Exported define ------------------------------------------------------------*/
#define SPI_TIMEOUT 0x3ff

#define  SPI_DMAAdrLen_MASK 0x1ffff
#define  SPIS_MAX_DEPTH 32
#define SPICTL_DEFAULT    0x02   //spi_CTL 寄存器复位默认值
/* Exported enum ------------------------------------------------------------*/
typedef enum
{
    SPI0_ID = 0,
    SPI1_ID = 1,
    SPI2_ID = 2,
    SPI3_ID = 3,
    SPIx_ID = 4,
} eSPI_ID_TypeDef;

typedef enum
{
    SPICTL_WIDTH_8BIT = 0,
    SPICTL_WIDTH_16BIT = 1,
    SPICTL_WIDTH_32BIT = 2,
    SPICTL_WIDTH_RSVBIT = 3,

    SPICTL_SCSN_DIS = 0,
    SPICTL_SCSN_EN = 1,

    SPICTL_CPH = 0,
    SPICTL_CPA = 1,

    SPICTL_CPOL = 0,
    SPICTL_CPOH = 1,

    SPICTL_MSB = 0,            /*"高BIT先传"*/
    SPICTL_LSB = 1,            /*"低BIT先传"*/

    SPICTL_TXCOL_IRQ_DIS = 0,
    SPICTL_TXCOL_IRQ_EN = 1,

    SPICTL_RXCOL_IRQ_DIS = 0,
    SPICTL_RXCOL_IRQ_EN = 1,

    SPICTL_ERR_IRQ_DIS = 0,
    SPICTL_ERR_IRQ_EN = 1,

    SPICTL_TR_IRQ_DIS = 0,
    SPICTL_TR_IRQ_EN = 1,

    SPICTL_SLAV = 0,           /*"从机"*/
    SPICTL_MAST = 1,           /*"主机"*/

    SPICTL_DIS = 0,
    SPICTL_EN = 1,
} eSPICtl_TypeDef;        /*"CPOL时钟极性/CPHA时钟相位选择"*/

typedef enum
{
    /*"BIT7:BIT8"*/
    SPICtl_Mode_00 = 0,            /*" 上升沿，数据采样;下降沿，数据建立"*/
    SPICtl_Mode_01 = 1,            /*" 上升沿，数据建立;下降沿，数据采样  "*/
    SPICtl_Mode_10 = 2,            /*" 下降沿，数据采样;上升沿，数据建立  "*/
    SPICtl_Mode_11 = 3,            /*" 下降沿，数据建立;上升沿，数据采样  "*/
} eSPICtl_Mode_TypeDef;        /*"CPOL时钟极性/CPHA时钟相位选择"*/
#if(0)
typedef enum
{
    SPICtl_TR_IRQ_EN        = 0x00000004,   /*"BIT2 :数据传输中断使能"*/
    SPICtl_ERR_IRQ_EN       = 0x00000008,   /*"BIT3 :SCSN 模式错误中断使能"*/
    SPICtl_RXCOL_IRQ_EN     = 0x00000010,   /*"BIT4 :数据冲突中断使能信号"*/
    SPICtl_TXCOL_IRQ_EN     = 0x00000020,   /*"BIT5 :数据冲突中断使能"*/
    SPICtl_SCSN_EN          = 0x00000200,   /*"BIT9 :SCSN 模式错误检测使能，只适用于主模式"*/
    SPICtl_TX_DFLT_EN       = 0x00400000,   /*"BIT22 :发送 BUF 空时，发送数据内容"*/
    SPICtl_TX_EMPT_IRQ_EN   = 0x00800000,   /*"BIT23:TXEMPT 中断使能"*/
    SPICtl_SCSN_NEG_IRQ_EN  = 0x01000000,   /*"BIT24 :SCSN_NEG 中断使能"*/
    SPICtl_SCSN_POS_IRQ_EN  = 0x02000000,   /*"BIT25 :SCSN_POS 中断使能"*/
} eSPICtl_IE_TypeDef;                       /*"数据中断选择"*/
#endif
typedef enum
{
    SPI_STA_TRIF    = (1u << 0),            // bit0 --数据传输中断
    SPI_STA_ERRIF   = (1u << 1),            // bit1 --SCSN模式冲突中断
    SPI_STA_RXCOLIF = (1u << 2),            // bit2 --接收数据溢出中断
    SPI_STA_TXCOLIF = (1u << 3),            // bit3 --写数据冲突
    SPI_STA_TXBUF_VLD   = (1u << 4),        // bit4 --TXBUF非空
    SPI_STA_TXEMPT  = (1u << 5),            // bit5 --发送数据空冲突
    SPI_STA_SCSN_NEG    = (1u << 6),        // bit6 --作为从机时，CSN拉低事件
    SPI_STA_SCSN_POS    = (1u << 7),        // bit7 --作为从机时，CSN拉高事件
} eSPI_STA_Typedef;

typedef enum
{
    SPI_DMA_TX_EN           = 0x01, /*"发送 DMA 使能"*/
    SPI_DMA_RX_EN           = 0x02, /*"接收 DMA 使能"*/
    SPI_DMA_TX_CYC_MODE     = 0x04, /*"发送循环模式使能"*/
    SPI_DMA_RX_CYC_MODE     = 0x08, /*"接收循环模式使能"*/
} eSPI_DMACtlPara_TypeDef;

typedef enum
{
    SPI_DMA_TX_HIE      = 0x01, /*"BIT0:DMA发送半满中断使能"*/
    SPI_DMA_TX_FIE      = 0x02, /*"BIT1:DMA发送全满中断使能"*/
    SPI_DMA_RX_HIE      = 0x04, /*"BIT2:DMA接收半满中断使能"*/
    SPI_DMA_RX_FIE      = 0x08, /*"BIT3:DMA接收全满中断使能"*/
    SPI_DMA_TX_ERR_IE   = 0x10, /*"BIT4:发送数据错误中断使能"*/
    SPI_DMA_RX_ERR_IE   = 0x20, /*"BIT5:接收数据覆盖中断使能"*/
} eSPIDMA_IE_TypeDef;

typedef enum
{
    SPI_DMA_FLAG_TX_HDONE       = (1u << 0),        // DMA发送半满中断
    SPI_DMA_FLAG_TX_FDONE       = (1u << 1),        // DMA发送全满中断
    SPI_DMA_FLAG_RX_HDONE       = (1u << 2),        // DMA接收半满中断
    SPI_DMA_FLAG_RX_FDONE       = (1u << 3),        // DMA接收全满中断
    SPI_DMA_FLAG_Reverse        = (1u << 4),        // 保留
    SPI_DMA_FLAG_RX_ERR         = (1u << 5),        // 接收数据覆盖
} eSPIDMA_FLAG_Typedef;

/* Exported types ------------------------------------------------------------*/
typedef union
{
    struct
    {
        uint32_t    SPICtl_EN: 1;
        uint32_t    SPICtl_MAST_SLAV: 1;
        uint32_t    SPICtl_TR_IRQ_EN: 1;
        uint32_t    SPICtl_ERR_IRQ_EN: 1;
        uint32_t    SPICtl_RXCOL_IRQ_EN: 1;
        uint32_t    SPICtl_TXCOL_IRQ_EN: 1;
        uint32_t    SPICtl_LMSB: 1;
        uint32_t    SPICtl_CPOL: 1;
        uint32_t    SPICtl_CPHA: 1;
        uint32_t    SPICtl_SCSN_EN: 1;
        uint32_t    SPICtl_WIDTH: 2;
        uint32_t    SPICtl_CLKDIV: 8;
        uint32_t    SPICtl_Reverse: 2;  //保留位，默认为 0，不要写 1
        uint32_t    SPICtl_TX_DFLT_EN: 1;
        uint32_t    SPICtl_TX_EMPT_IRQ_EN: 1;
        uint32_t    SPICtl_SCSN_NEG_IRQ_EN: 1;
        uint32_t    SPICtl_SCSN_POS_IRQ_EN: 1;
        uint32_t    SPICtl_SLV_TX_ADV: 1;
    };
    uint32_t gSPICtl;
} uSPICtlPara_TypeDef;

typedef union
{
    struct
    {
        uint32_t    SPI_DMACtl_TX_DMA_EN: 1; //   发送DMA使能
        uint32_t    SPI_DMACtl_RX_DMA_EN: 1; //   接收DMA使能
        uint32_t    SPI_DMACtl_TX_CYC_MODE: 1; //发送循环模式使能
        uint32_t    SPI_DMACtl_RX_CYC_MODE: 1; //接收循环模式使能
    };
    uint32_t gSPI_DMACtl;
} uSPI_DMACtlPara_TypeDef;

typedef struct
{
    uSPI_DMACtlPara_TypeDef     DmaCtl;
    uint32_t        TbAdr;
    uint32_t        RbAdr;
    uint32_t        TLen;
    uint32_t        RLen;
    uint32_t        DmaIE;
} uSPI_DMAPara_TypeDef;

/* Exported data ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern u8 Rn8xxx_Spi_ReadByte(u8 spi_id);
extern void Rn8xxx_Spi_WriteByte(u8 spi_id, u8 Dat);
extern void Rn8xxx_Spi_Init(eSPI_ID_TypeDef spi_id, uSPICtlPara_TypeDef spi_para, uint32_t speed);
extern void Rn8xxx_Spi_DMAInit(eSPI_ID_TypeDef spi_id, uSPI_DMAPara_TypeDef SpiDmaPa);
extern void Rn8xxx_Spi_DMATxStar(eSPI_ID_TypeDef spi_id, u32 Addr, u32 TxLen, u16 CrcInit);
extern u32 Rn8xxx_Spi_DMA_RxInfo(eSPI_ID_TypeDef spi_id);
extern u32 Rn8xxx_Spi_DMA_TxInfo(eSPI_ID_TypeDef spi_id);

#endif  //_SPI_H
/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
