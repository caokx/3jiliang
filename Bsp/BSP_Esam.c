/****************************************************************************
* @file     ISO7816.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.05.26
* @brief    ISO7816����
******************************************************************************
* @attention
*
*
****************************************************************************/
/* Includes ------------------------------------------------------------------*/
#define  DRIVE_BSP_ESAM_GLOBALS

#include <BSP.h>

/* Private define ------------------------------------------------------------*/
#define ESAM_SPI_Delay()            {__NOP();__NOP();}

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/

/*********************************************************************************************************
** Function name:       BSP_ISO7816_Init
** Descriptions:        ��ʼ��7816
** input parameters:    None
** output parameters:       None
** Returned value:     None
*********************************************************************************************************/

void BSP_ISO7816_Init(void)
{
    #if(METERTYPE==2)
    ISO7816->CTRL1 = 0x70000201;
    #endif
    ISO7816->CTRL0 = 0x0800ea01;
    //ISO7816->CTRL0 = 0x0000ea01;
    ISO7816->STA0 = 0x3f;                   //clear status
    ISO7816->STA1 = 0x3f;                   //clear status
    //ISO7816->BDDIV0 = 0X216a00;
    ISO7816_Init();
    //PinWrite_EsamRst(1);
    Std_Memset(&I7816ComExt, 0x00, sizeof(sISO7816ComBuf_TypeDef));
}

u8 BSP_EASM_GetPower(void)
{
    if (Rn8xxx_GPIO_ReadPin(PinEASMPower) == 0) //ESAM��Դ��
    {
        return  true;
    }
    else
    {
        return false;    //ESAM��Դ�ر�
    }
}

/*********************************************************************************************************
** Function name:       BSP_Esam_Stop
** Descriptions:        �ر�ESAMģ��
** input parameters:    None
** output parameters:       None
** Returned value:     None
*********************************************************************************************************/

void BSP_Esam_Stop(void)
{
    Rn8xxx_GPIO_CfgFun(PinEASMCS, _NORMALIO); /*"EsamͨѶSPI ��CS��"*/
    Rn8xxx_GPIO_CfgIOMode(PinEASMCS, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinEASMCS, 0);

    Rn8xxx_GPIO_CfgFun(PinEsamClk, _NORMALIO); /*"EsamͨѶSPI ��CLK��"*/
    Rn8xxx_GPIO_CfgIOMode(PinEsamClk, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinEsamClk, 0);

    Rn8xxx_GPIO_CfgFun(PinEASMMOSI, _NORMALIO); /*"EsamͨѶSPI ��MOSI��"*/
    Rn8xxx_GPIO_CfgIOMode(PinEASMMOSI, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinEASMMOSI, 0);

    Rn8xxx_GPIO_CfgFun(PinEASMMISO, _NORMALIO); /*"EsamͨѶSPI ��MISO��"*/
    Rn8xxx_GPIO_CfgIOMode(PinEASMMOSI, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinEASMMOSI, 0);
    Rn8xxx_GPIO_CfgPullMode(PinEASMMISO, Pull_OFF);

    EsamPowerOff();
}

/*********************************************************************************************************
** Function name:         BSP_EsamSpi_Init
** Descriptions:           Esam  spi��ʼ��
** input parameters:
** output parameters:   none
** Returned value:
*********************************************************************************************************/
void BSP_EsamSpi_Init(void)
{
    uSPICtlPara_TypeDef spi_para;

    #if(SPI_Esam_Mode == SPI_Esam_FirmwareMode)
    Rn8xxx_GPIO_CfgFun(PinEASMCS, _NORMALIO); /*"EsamͨѶSPI ��CS��"*/
    Rn8xxx_GPIO_CfgIOMode(PinEASMCS, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinEASMCS, 1);

    Rn8xxx_GPIO_CfgFun(PinEsamClk, _NORMALIO); /*"EsamͨѶSPI ��CLK��"*/
    Rn8xxx_GPIO_CfgIOMode(PinEsamClk, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinEsamClk, 1);

    Rn8xxx_GPIO_CfgFun(PinEASMMOSI, _NORMALIO); /*"EsamͨѶSPI ��MOSI��"*/
    Rn8xxx_GPIO_CfgIOMode(PinEASMMOSI, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinEASMMOSI, 1);

    Rn8xxx_GPIO_CfgFun(PinEASMMISO, _NORMALIO); /*"EsamͨѶSPI ��MISO��"*/
    Rn8xxx_GPIO_CfgIOMode(PinEASMMISO, GPIO_MODE_IN, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinEASMMISO, Pull_ON);

    #else
    Rn8xxx_GPIO_CfgFun(PinEASMCS, _NORMALIO); /*"EsamͨѶSPI ��CS��"*/
    Rn8xxx_GPIO_CfgIOMode(PinEASMCS, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinEASMCS, 1);

    Rn8xxx_GPIO_CfgFun(PinEsamClk, (eGPIOFunction_TypeDef)(_SPI0 + Esam_SPI_ID)); /*"EsamͨѶSPI ��CLK��"*/

    Rn8xxx_GPIO_CfgFun(PinEASMMOSI, (eGPIOFunction_TypeDef)(_SPI0 + Esam_SPI_ID)); /*"EsamͨѶSPI ��MOSI��"*/

    Rn8xxx_GPIO_CfgFun(PinEASMMISO, (eGPIOFunction_TypeDef)(_SPI0 + Esam_SPI_ID)); /*"EsamͨѶSPI ��MISO��"*/
    Rn8xxx_GPIO_CfgPullMode(PinEASMMISO, Pull_ON);

    spi_para.gSPICtl = SPICTL_DEFAULT;
    spi_para.SPICtl_EN = SPICTL_EN;
    spi_para.SPICtl_MAST_SLAV = SPICTL_MAST;
    spi_para.SPICtl_LMSB = SPICTL_MSB;
    spi_para.SPICtl_CPOL = (SPICtl_Mode_11 >> 1);
    spi_para.SPICtl_CPHA = (SPICtl_Mode_11 & 0x01);
    spi_para.SPICtl_WIDTH = SPICTL_WIDTH_8BIT;

    Rn8xxx_Spi_Init(Esam_SPI_ID, spi_para, Esam_SPI_SPEED);

    #endif
}

/*********************************************************************************************************
** Function name:   BSP_EsamSpi_WriteByte
** Descriptions:    ESAM ģ��SPIд�ֽ�,SPI����ģʽ3,SCLK�½��أ����ݽ���
** input parameters:   Write byte data
** output parameters:   null
** Returned value:      null
*********************************************************************************************************/
void BSP_EsamSpi_WriteByte(uint8_t data)
{
    #if(SPI_Esam_Mode == SPI_Esam_FirmwareMode)
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)
        {
            PinWrite_EsamMOSI(1);
            PinWrite_EsamMOSI(1);
        }
        else
        {
            PinWrite_EsamMOSI(0);
            PinWrite_EsamMOSI(0);
        }

        PinWrite_EsamSCK(0);
        PinWrite_EsamSCK(0);
        ESAM_SPI_Delay();/*"�ȴ��ӻ�ȡ��"*/

        data <<= 1;
        PinWrite_EsamSCK(1);
        PinWrite_EsamSCK(1);
    }

    #else
    Rn8xxx_Spi_WriteByte(Esam_SPI_ID, data);
    #endif
}

/*********************************************************************************************************
** Function name:   BSP_EsamSpi_ReadByte
** Descriptions:    ESAM ģ��SPI���ֽ�,SPI����ģʽ3,SCLK�����ز�������
** input parameters:    null
** output parameters:   null
** Returned value:    spi received data
*********************************************************************************************************/
uint8_t BSP_EsamSpi_ReadByte(void)
{
    #if(SPI_Esam_Mode == SPI_Esam_FirmwareMode)
    uint8_t i, data = 0;
    for (i = 0; i < 8; i++)
    {
        data <<= 1;
        PinWrite_EsamSCK(0);
        PinWrite_EsamSCK(0);
        ESAM_SPI_Delay();
        PinWrite_EsamSCK(1);
        PinWrite_EsamSCK(1);

        if (PinRead_EsamMISO())
        {
            data = data + 0x1;
        }
    }
    return  data;
    #else
    return (Rn8xxx_Spi_ReadByte(Esam_SPI_ID));
    #endif
}

/*********************************************************************************************************
** Function name:       fnCardGetByte
** Descriptions:        �ӿ���ESAM����һ��8λ�ֽ�
** input parameters:    Data ΪҪ���յ�8λ����  ,CH ͨ��ѡ�� Rpt ���½��մ�?
** output parameters:       None
** Returned value:      ���ճɹ���ȴ�1��ETU���أ��Ӽ�⵽��ʼλ���ɹ�����ʱ������11��ETU
*********************************************************************************************************/

ErrorStatus fnCardGetByte(u8 CH, u8 *Data)
{
    fnWDT_Restart();

    if (CH == ESAM)
    {
        #if(SPI_ESAM)
        *Data = BSP_EsamSpi_ReadByte();
        #else
        ISO7816_ReadByte(ISO7816_0ID, Data);
        #endif
    }
    else
    {
        ISO7816_ReadByte(ISO7816_1ID, Data);
    }
    return  SUCCESS;
}

/*********************************************************************************************************
** Function name:       fnCardSendByte
** Descriptions:           �򿨻�ESAM����һ��8λ�ֽ�
** input parameters:       c ΪҪ���͵�8λ����
** output parameters:       None
** Returned value:         0Ϊ��ȷ��1Ϊ����ȷ
*********************************************************************************************************/

ErrorStatus fnCardSendByte(u8 CH, u8 Data)
{
    fnWDT_Restart();
    if (CH == ESAM)
    {
        #if(SPI_ESAM)
        BSP_EsamSpi_WriteByte(Data);
        #else
        ISO7816_WriteByte(ISO7816_0ID, Data);
        #endif
    }
    else
    {
        ISO7816_WriteByte(ISO7816_1ID, Data);
    }
    return  SUCCESS;
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
