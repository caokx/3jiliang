/****************************************************************************
* @file     SPI.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.04.28
* @brief    SPI����
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
#define SPICTL_DEFAULT    0x02   //spi_CTL �Ĵ�����λĬ��ֵ
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

    SPICTL_MSB = 0,            /*"��BIT�ȴ�"*/
    SPICTL_LSB = 1,            /*"��BIT�ȴ�"*/

    SPICTL_TXCOL_IRQ_DIS = 0,
    SPICTL_TXCOL_IRQ_EN = 1,

    SPICTL_RXCOL_IRQ_DIS = 0,
    SPICTL_RXCOL_IRQ_EN = 1,

    SPICTL_ERR_IRQ_DIS = 0,
    SPICTL_ERR_IRQ_EN = 1,

    SPICTL_TR_IRQ_DIS = 0,
    SPICTL_TR_IRQ_EN = 1,

    SPICTL_SLAV = 0,           /*"�ӻ�"*/
    SPICTL_MAST = 1,           /*"����"*/

    SPICTL_DIS = 0,
    SPICTL_EN = 1,
} eSPICtl_TypeDef;        /*"CPOLʱ�Ӽ���/CPHAʱ����λѡ��"*/

typedef enum
{
    /*"BIT7:BIT8"*/
    SPICtl_Mode_00 = 0,            /*" �����أ����ݲ���;�½��أ����ݽ���"*/
    SPICtl_Mode_01 = 1,            /*" �����أ����ݽ���;�½��أ����ݲ���  "*/
    SPICtl_Mode_10 = 2,            /*" �½��أ����ݲ���;�����أ����ݽ���  "*/
    SPICtl_Mode_11 = 3,            /*" �½��أ����ݽ���;�����أ����ݲ���  "*/
} eSPICtl_Mode_TypeDef;        /*"CPOLʱ�Ӽ���/CPHAʱ����λѡ��"*/
#if(0)
typedef enum
{
    SPICtl_TR_IRQ_EN        = 0x00000004,   /*"BIT2 :���ݴ����ж�ʹ��"*/
    SPICtl_ERR_IRQ_EN       = 0x00000008,   /*"BIT3 :SCSN ģʽ�����ж�ʹ��"*/
    SPICtl_RXCOL_IRQ_EN     = 0x00000010,   /*"BIT4 :���ݳ�ͻ�ж�ʹ���ź�"*/
    SPICtl_TXCOL_IRQ_EN     = 0x00000020,   /*"BIT5 :���ݳ�ͻ�ж�ʹ��"*/
    SPICtl_SCSN_EN          = 0x00000200,   /*"BIT9 :SCSN ģʽ������ʹ�ܣ�ֻ��������ģʽ"*/
    SPICtl_TX_DFLT_EN       = 0x00400000,   /*"BIT22 :���� BUF ��ʱ��������������"*/
    SPICtl_TX_EMPT_IRQ_EN   = 0x00800000,   /*"BIT23:TXEMPT �ж�ʹ��"*/
    SPICtl_SCSN_NEG_IRQ_EN  = 0x01000000,   /*"BIT24 :SCSN_NEG �ж�ʹ��"*/
    SPICtl_SCSN_POS_IRQ_EN  = 0x02000000,   /*"BIT25 :SCSN_POS �ж�ʹ��"*/
} eSPICtl_IE_TypeDef;                       /*"�����ж�ѡ��"*/
#endif
typedef enum
{
    SPI_STA_TRIF    = (1u << 0),            // bit0 --���ݴ����ж�
    SPI_STA_ERRIF   = (1u << 1),            // bit1 --SCSNģʽ��ͻ�ж�
    SPI_STA_RXCOLIF = (1u << 2),            // bit2 --������������ж�
    SPI_STA_TXCOLIF = (1u << 3),            // bit3 --д���ݳ�ͻ
    SPI_STA_TXBUF_VLD   = (1u << 4),        // bit4 --TXBUF�ǿ�
    SPI_STA_TXEMPT  = (1u << 5),            // bit5 --�������ݿճ�ͻ
    SPI_STA_SCSN_NEG    = (1u << 6),        // bit6 --��Ϊ�ӻ�ʱ��CSN�����¼�
    SPI_STA_SCSN_POS    = (1u << 7),        // bit7 --��Ϊ�ӻ�ʱ��CSN�����¼�
} eSPI_STA_Typedef;

typedef enum
{
    SPI_DMA_TX_EN           = 0x01, /*"���� DMA ʹ��"*/
    SPI_DMA_RX_EN           = 0x02, /*"���� DMA ʹ��"*/
    SPI_DMA_TX_CYC_MODE     = 0x04, /*"����ѭ��ģʽʹ��"*/
    SPI_DMA_RX_CYC_MODE     = 0x08, /*"����ѭ��ģʽʹ��"*/
} eSPI_DMACtlPara_TypeDef;

typedef enum
{
    SPI_DMA_TX_HIE      = 0x01, /*"BIT0:DMA���Ͱ����ж�ʹ��"*/
    SPI_DMA_TX_FIE      = 0x02, /*"BIT1:DMA����ȫ���ж�ʹ��"*/
    SPI_DMA_RX_HIE      = 0x04, /*"BIT2:DMA���հ����ж�ʹ��"*/
    SPI_DMA_RX_FIE      = 0x08, /*"BIT3:DMA����ȫ���ж�ʹ��"*/
    SPI_DMA_TX_ERR_IE   = 0x10, /*"BIT4:�������ݴ����ж�ʹ��"*/
    SPI_DMA_RX_ERR_IE   = 0x20, /*"BIT5:�������ݸ����ж�ʹ��"*/
} eSPIDMA_IE_TypeDef;

typedef enum
{
    SPI_DMA_FLAG_TX_HDONE       = (1u << 0),        // DMA���Ͱ����ж�
    SPI_DMA_FLAG_TX_FDONE       = (1u << 1),        // DMA����ȫ���ж�
    SPI_DMA_FLAG_RX_HDONE       = (1u << 2),        // DMA���հ����ж�
    SPI_DMA_FLAG_RX_FDONE       = (1u << 3),        // DMA����ȫ���ж�
    SPI_DMA_FLAG_Reverse        = (1u << 4),        // ����
    SPI_DMA_FLAG_RX_ERR         = (1u << 5),        // �������ݸ���
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
        uint32_t    SPICtl_Reverse: 2;  //����λ��Ĭ��Ϊ 0����Ҫд 1
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
        uint32_t    SPI_DMACtl_TX_DMA_EN: 1; //   ����DMAʹ��
        uint32_t    SPI_DMACtl_RX_DMA_EN: 1; //   ����DMAʹ��
        uint32_t    SPI_DMACtl_TX_CYC_MODE: 1; //����ѭ��ģʽʹ��
        uint32_t    SPI_DMACtl_RX_CYC_MODE: 1; //����ѭ��ģʽʹ��
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
