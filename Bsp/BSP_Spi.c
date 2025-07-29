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
#define  _DRIVE_SPI_GLOBALS

#include <BSP.h>
/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef struct
{
    eScomPort_TypeDef  Scom;
    eSPI_ID_TypeDef    SpiID;
    u8  DMAEnOrDis;
} sScomPort_SpiID_TypeDef;

/* Private data ---------------------------------------------------------*/

sScomPort_SpiID_TypeDef ScomPort_SpiID_Table[] =
{
    {SCOM_PORT_SPI,  SPI1_ID, SPI_DMA_EN},     //V2版本芯片开启DMA功能
};

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/
/*********************************************************************************************************
** Function name:         BSP_FlashSpi_Init
** Descriptions:           flash  spi通讯IO初始化
** input parameters:
** output parameters:   none
** Returned value:
*********************************************************************************************************/
void BSP_FlashSpi_Init(void)
{
    #if(SPI_FLASH_Mode == SPI_FLASH_FirmwareMode)
    Rn8xxx_GPIO_CfgFun(PinFlashCS, _NORMALIO); /*"Flash通讯SPI 的CS脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinFlashCS, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinFlashCS, 1);

    Rn8xxx_GPIO_CfgFun(PinFlashCLK, _NORMALIO); /*"Flash通讯SPI 的CLK脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinFlashCLK, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinFlashCLK, 0);

    Rn8xxx_GPIO_CfgFun(PinFlashMOSI, _NORMALIO); /*"Flash通讯SPI 的MOSI脚"*/
    #if(nPhs==ThreePhs)
    Rn8xxx_GPIO_CfgIOMode(PinFlashMOSI, GPIO_MODE_OUT, NORMAL_OUT);
    #else
    Rn8xxx_GPIO_CfgIOMode(PinFlashMOSI, GPIO_MODE_OUT, N_OPENDRAIN_OUT);       //单相表，由于电平匹配，需开漏输出
    #endif
    Rn8xxx_GPIO_SetPin(PinFlashMOSI, 0);

    Rn8xxx_GPIO_CfgFun(PinFlashMISO, _NORMALIO); /*"Flash通讯SPI 的MISO脚"*/

    #if(nPhs==ThreePhs)
    Rn8xxx_GPIO_CfgIOMode(PinFlashMISO, GPIO_MODE_IN, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinFlashMISO, Pull_ON);
    #else
    Rn8xxx_GPIO_CfgIOMode(PinFlashMISO, GPIO_MODE_IN, TTL_IN);
    #endif

    FLASH_PowerOn();

    #else
    Rn8xxx_GPIO_CfgFun(PinFlashCS, _NORMALIO); /*"Flash通讯SPI 的CS脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinFlashCS, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinFlashCS, 1);

    Rn8xxx_GPIO_CfgFun(PinFlashCLK, _SPI); /*"Flash通讯SPI 的CLK脚"*/

    Rn8xxx_GPIO_CfgFun(PinFlashMOSI, _SPI); /*"Flash通讯SPI 的MOSI脚"*/

    Rn8xxx_GPIO_CfgFun(PinFlashMISO, _SPI); /*"Flash通讯SPI 的MISO脚"*/
    Rn8xxx_GPIO_CfgPullMode(PinFlashMISO, Pull_ON);

    FLASH_PowerOn();

    uSPICtlPara_TypeDef spi_para;

    spi_para.gSPICtl = SPICTL_DEFAULT;
    spi_para.SPICtl_EN = SPICTL_EN;
    spi_para.SPICtl_MAST_SLAV = SPICTL_MAST;
    spi_para.SPICtl_LMSB = SPICTL_MSB;
    spi_para.SPICtl_CPOL = (SPICtl_Mode_00 >> 1); //模式0
    spi_para.SPICtl_CPHA = (SPICtl_Mode_00 & 0x01);
    spi_para.SPICtl_WIDTH = SPICTL_WIDTH_8BIT;

    Rn8xxx_Spi_Init(FLASH_SPI_ID, spi_para, FLASH_SPI_SPEED);

    #endif
}

/*********************************************************************************************************
** Function name:         BSP_FlashSpi_Stop
** Descriptions:           flash  spi通讯IO关闭
** input parameters:
** output parameters:   none
** Returned value:
*********************************************************************************************************/
void BSP_FlashSpi_Stop(void)
{
    #if(SPI_FLASH_Mode == SPI_FLASH_FirmwareMode)
    Rn8xxx_GPIO_CfgFun(PinFlashCS, _NORMALIO); /*"Flash通讯SPI 的CS脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinFlashCS, GPIO_MODE_NORMAL, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinFlashCLK, _NORMALIO); /*"Flash通讯SPI 的CLK脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinFlashCLK, GPIO_MODE_NORMAL, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinFlashMOSI, _NORMALIO); /*"Flash通讯SPI 的MOSI脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinFlashMOSI, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinFlashMISO, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinFlashMISO, _NORMALIO); /*"Flash通讯SPI 的MISO脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinFlashMISO, GPIO_MODE_NORMAL, NORMAL_IN);

    //FLASH_PowerOff();
    Rn8xxx_GPIO_CfgFun(PinFLASHPower, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinFLASHPower, GPIO_MODE_NORMAL, NORMAL_IN);

    #else
    Rn8xxx_GPIO_CfgFun(PinFlashCS, _NORMALIO); /*"Flash通讯SPI 的CS脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinFlashCS, GPIO_MODE_NORMAL, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinFlashCLK, _NORMALIO); /*"Flash通讯SPI 的CLK脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinFlashCLK, GPIO_MODE_NORMAL, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinFlashMOSI, _NORMALIO); /*"Flash通讯SPI 的MOSI脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinFlashMOSI, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinFlashMISO, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinFlashMISO, _NORMALIO); /*"Flash通讯SPI 的MISO脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinFlashMISO, GPIO_MODE_NORMAL, NORMAL_IN);

    //FLASH_PowerOff();
    Rn8xxx_GPIO_CfgFun(PinFLASHPower, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinFLASHPower, GPIO_MODE_NORMAL, NORMAL_IN);

    #endif
}

/*********************************************************************************************************
** Function name:         BSP_FlashSpi_WriteByte
** Descriptions:           Flash  写单个字节,SPI采用模式0,SCLK下降沿数据建立
** input parameters:     Write data
** output parameters:   none
** Returned value:     none
*********************************************************************************************************/
void BSP_FlashSpi_WriteByte(uint8_t Dat)
{
    #if(SPI_FLASH_Mode == SPI_FLASH_FirmwareMode)
    /*
    uint8_t i;
    for(i=0;i<8;i++)
    {
        PinWrite_MX25LSCK(0);
        PinWrite_MX25LSCK(0);

        if(Dat & 0x80)
        {
            PinWrite_MX25LMOSI(1);
            PinWrite_MX25LMOSI(1);
        }
        else
        {
            PinWrite_MX25LMOSI(0);
            PinWrite_MX25LMOSI(0);
        }
        PinWrite_MX25LSCK(1);
        PinWrite_MX25LSCK(1);

        Dat <<= 1;
    }
    */

    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    REG32(PinWrite_MX25LMOSI_BitBandAddr) = (Dat >> 7) & 0x01;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    REG32(PinWrite_MX25LMOSI_BitBandAddr) = (Dat >> 6) & 0x01;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    REG32(PinWrite_MX25LMOSI_BitBandAddr) = (Dat >> 5) & 0x01;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    REG32(PinWrite_MX25LMOSI_BitBandAddr) = (Dat >> 4) & 0x01;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    REG32(PinWrite_MX25LMOSI_BitBandAddr) = (Dat >> 3) & 0x01;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    REG32(PinWrite_MX25LMOSI_BitBandAddr) = (Dat >> 2) & 0x01;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    REG32(PinWrite_MX25LMOSI_BitBandAddr) = (Dat >> 1) & 0x01;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    REG32(PinWrite_MX25LMOSI_BitBandAddr) = (Dat >> 0) & 0x01;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;
    #else
    Rn8xxx_Spi_WriteByte(FLASH_SPI_ID, Dat) ;
    #endif
}

/*********************************************************************************************************
** Function name:         BSP_FlashSpi_ReadByte
** Descriptions:           Flash  读单个字节,SPI采用模式0,SCLK上升沿数据采样
** input parameters:     none
** output parameters:   none
** Returned value:        read data
*********************************************************************************************************/
uint8_t BSP_FlashSpi_ReadByte(void)
{
    #if(SPI_FLASH_Mode == SPI_FLASH_FirmwareMode)
    /*
    uint8_t i,data=0;
    for(i=0;i<8;i++)
    {
            data<<=1;
        PinWrite_MX25LSCK(0);
        PinWrite_MX25LSCK(0);

        if (PinRead_MX25LMISO())
            {
                data=data+0x1;
            }
        PinWrite_MX25LSCK(1);
        PinWrite_MX25LSCK(1);
    }
    */

    uint8_t data = 0;

    data <<= 1;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    __NOP();    // dyf add
    __NOP();    // dyf add
    data |= REG32(PinWrite_MX25LMISO_BitBandAddr);
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    data <<= 1;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    __NOP();    // dyf add
    __NOP();    // dyf add
    data |= REG32(PinWrite_MX25LMISO_BitBandAddr);
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    data <<= 1;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    __NOP();    // dyf add
    __NOP();    // dyf add
    data |= REG32(PinWrite_MX25LMISO_BitBandAddr);
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    data <<= 1;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    __NOP();    // dyf add
    __NOP();    // dyf add
    data |= REG32(PinWrite_MX25LMISO_BitBandAddr);
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    data <<= 1;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    __NOP();    // dyf add
    __NOP();    // dyf add
    data |= REG32(PinWrite_MX25LMISO_BitBandAddr);
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    data <<= 1;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    __NOP();    // dyf add
    __NOP();    // dyf add
    data |= REG32(PinWrite_MX25LMISO_BitBandAddr);
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    data <<= 1;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    __NOP();    // dyf add
    __NOP();    // dyf add
    data |= REG32(PinWrite_MX25LMISO_BitBandAddr);
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;

    data <<= 1;
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 0;
    __NOP();    // dyf add
    __NOP();    // dyf add
    data |= REG32(PinWrite_MX25LMISO_BitBandAddr);
    REG32(PinWrite_MX25LSCK_BitBandAddr) = 1;
    return  data;
    #else
    return (Rn8xxx_Spi_ReadByte(FLASH_SPI_ID)) ;
    #endif
}

/*********************************************************************************************************
** Function name:       BSP_SpiId_Get
** Descriptions:        根据Scom类型的通信端口查询对应的SPI类型通信端口
** input parameters:    Scom类型通信端口
** output parameters:   none
** Returned value:      SPI类型通信端口
*********************************************************************************************************/
eSPI_ID_TypeDef BSP_SpiId_Get(eScomPort_TypeDef Scom)
{
    uint8_t i;
    for (i = 0; i < sizeof(ScomPort_SpiID_Table) / sizeof(ScomPort_SpiID_Table[0]); i++)
    {
        if (Scom == ScomPort_SpiID_Table[i].Scom)
        {
            return  ScomPort_SpiID_Table[i].SpiID;
        }
    }

    return  ScomPort_SpiID_Table[0].SpiID;//todo
}

/*********************************************************************************************************
** Function name:       BSP_SpiId_DMAEnOrDis_Get
** Descriptions:        查询Scom类型的通信端口是否开启了DMA
** input parameters:    Scom：Scom类型的通信端口号；DMAEnOrDis：SPI_DMA_EN表示开启了DMA，SPI_DMA_DIS表示未开启DMA
** output parameters:   none
** Returned value:      none
*********************************************************************************************************/
void BSP_SpiId_DMAEnOrDis_Get(eScomPort_TypeDef Scom, eSPI_ID_TypeDef *SpiId, u8 *DMAEnOrDis)
{
    uint8_t i, res = ERROR;
    for (i = 0; i < sizeof(ScomPort_SpiID_Table) / sizeof(ScomPort_SpiID_Table[0]); i++)
    {
        if (Scom == ScomPort_SpiID_Table[i].Scom)
        {
            *SpiId = ScomPort_SpiID_Table[i].SpiID;
            *DMAEnOrDis = ScomPort_SpiID_Table[i].DMAEnOrDis;
            res = SUCCESS;
            break;
        }
    }

    if (res == ERROR)
    {
        *SpiId = ScomPort_SpiID_Table[0].SpiID;
        *DMAEnOrDis = ScomPort_SpiID_Table[0].DMAEnOrDis;
    }
}

/*********************************************************************************************************
** Function name:       BSP_ManageModuleSpi_Init
** Descriptions:        管理模组的SPI接口初始化
** input parameters:    SpiId：SPI端口号，BdRate：SPI通信速率单位Hz
** output parameters:   none
** Returned value:      none
*********************************************************************************************************/
const u8 GpioCfgSpiId[] = {_SPI0, _SPI1, _SPI2, _SPI3};
const u32 SpiBaseAddr[] = {SPI0_BASE, SPI1_BASE, SPI2_BASE, SPI3_BASE};
const IRQn_Type SpiIrqn[] = {SPI_IRQn, SPI1_IRQn, ISO78161_SPI2_IRQn, ISO78160_SPI3_IRQn};
void BSP_ManageModuleSpi_Init(u8 SpiId, u32 BdRate)
{
    uSPICtlPara_TypeDef spi_para;
    u8 GpioCfgSpiIdx;
    SPI_TypeDef* Spix;
    IRQn_Type SpiIrqnx;

    GpioCfgSpiIdx = GpioCfgSpiId[SpiId];
    Rn8xxx_GPIO_CfgFun(PinManageModuleCS, GpioCfgSpiIdx);
    Rn8xxx_GPIO_CfgIOMode(PinManageModuleCS, GPIO_MODE_OUT, N_OPENDRAIN_OUT);        //---开漏输出-------
    Rn8xxx_GPIO_SetPin(PinManageModuleCS, 1);

    //Rn8xxx_GPIO_CfgPullMode(PinManageModuleCS,Pull_ON);

    Rn8xxx_GPIO_CfgFun(PinManageModuleCLK, GpioCfgSpiIdx);
    Rn8xxx_GPIO_CfgPullMode(PinManageModuleCLK, Pull_ON);
    #if(KeLu==TRUE)
    Rn8xxx_GPIO_CfgIOMode(PinManageModuleCLK, GPIO_MODE_IN, TTL_IN);        //Ke Lu
    #endif

    Rn8xxx_GPIO_CfgFun(PinManageModuleMISO, GpioCfgSpiIdx);
    Rn8xxx_GPIO_CfgPullMode(PinManageModuleMISO, Pull_ON);
    #if(KeLu==TRUE)
    Rn8xxx_GPIO_CfgIOMode(PinManageModuleMISO, GPIO_MODE_IN, TTL_IN);       //Ke Lu
    #endif

    Rn8xxx_GPIO_CfgFun(PinManageModuleMOSI, GpioCfgSpiIdx);
    Rn8xxx_GPIO_CfgPullMode(PinManageModuleMOSI, Pull_ON);

    spi_para.gSPICtl = SPICTL_DEFAULT;
    spi_para.SPICtl_EN = SPICTL_EN;
    spi_para.SPICtl_MAST_SLAV = SPICTL_SLAV;
    spi_para.SPICtl_LMSB = SPICTL_MSB;
    spi_para.SPICtl_CPOL = (SPICtl_Mode_10 & 0x01);
    spi_para.SPICtl_CPHA = (SPICtl_Mode_10 >> 1);
    spi_para.SPICtl_WIDTH = SPICTL_WIDTH_8BIT;
    //spi_para.gSPICtl |= 0x01000000;   //下降沿中断
    spi_para.gSPICtl |= 0x02000000; //上升沿中断
    spi_para.gSPICtl |= 0x00400000; //发送buf空时，发送默认字节数据
    spi_para.gSPICtl |= 0x04000000; //从机高速模式
    Rn8xxx_Spi_Init(SpiId, spi_para, BdRate);  //SpiClk

    Spix = (SPI_TypeDef*)SpiBaseAddr[SpiId];
    SpiIrqnx = SpiIrqn[SpiId];
    Spix->TX = 0x00;
    Spix->TXDFLT = 0x00;
    NVIC_EnableIRQ(SpiIrqnx);
}

/*********************************************************************************************************
** Function name:       BSP_SpiCtrlandDmaRxCheck
** Descriptions:        检测通信端口号对应的SPI口使能以及DMA接收使能是否打开
** input parameters:    Scom：Scom类型的通信端口号
** output parameters:   none
** Returned value:      正常返回SUCCESS，错误返回ERROR
*********************************************************************************************************/
ErrorStatus BSP_SpiCtrlandDmaRxCheck(eScomPort_TypeDef Scom)
{
    //ErrorStatus ret;
    eSPI_ID_TypeDef spid;
    SPI_TypeDef* Spix;

    spid = BSP_SpiId_Get(Scom);
    Spix = (SPI_TypeDef*)SpiBaseAddr[spid];
    if ((Spix->CTRL & 0x01) && (Spix->DMA_CTRL & 0x02))
    {
        return (SUCCESS);
    }
    else
    {
        return (ERROR);
    }
}

//===================================================

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
