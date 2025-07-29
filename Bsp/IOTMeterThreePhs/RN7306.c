/****************************************************************************
* @file     RN7306.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2023.04.18
* @brief    RN7306驱动
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include <stdint.h>
//#include <Dat_Types.h>
//#include <RN7306.h>
#include <BSP.h>
/* Private define ------------------------------------------------------------*/
#define  Rn7306_SPI_ID      SPI0_ID
#define  Rn7306_SPI_SPEED      2000000
#define  SPI_Rn7306_HardwareMode    0
#define  SPI_Rn7306_FirmwareMode    1
#define  SPI_Rn7306_Mode           SPI_Rn7306_FirmwareMode//SPI_Rn7306_HardwareMode
/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/
sRn8302_API_TypeDef     Rn8302_API;/*" Rn7306 SPI函数接口 "*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/

/*********************************************************************************************************
** Function name:         fnRN7306_ApiRegister
** Descriptions:            注册需要用到的SPI驱动函数和延迟函数
** input parameters:     SpiCS CS控制函数SpiRead   SPI读函数   SpiWrite SPI写函数Delay_1us 系统微妙延迟函数
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnRN8302_ApiRegister(Rn8302_SpiCSPtr SpiCS, Rn8302_SpiReadPtr SpiRead, Rn8302_SpiWritePtr SpiWrite, Rn8302_DelayUsPtr Delay_1us)
{
    /*" Rn8302  SPI函数接口初始化 "*/
    Rn8302_API.SpiCS = SpiCS;
    Rn8302_API.SpiRead = SpiRead;
    Rn8302_API.SpiWrite = SpiWrite;
    Rn8302_API.Delay_1us = Delay_1us;
}

/*********************************************************************************************************
** Function name:           fnRN7306_Write
** Descriptions:
** input parameters:
** output parameters:       None
** Returned value:
*********************************************************************************************************/
ErrorStatus fnRN8302_Write(uint16_t wReg, uint8_t *pBuf, uint8_t ucLen)
{
    uint8_t i, temp, chksum, Repeat;
    uint8_t buff[4] = {0};  // dyf add
    ErrorStatus err;
    if ((ucLen == 0) || (ucLen > 4))
    {
        return (ERROR);
    }
    for (Repeat = 3; Repeat != 0 ; Repeat--)
    {
        err = SUCCESS;
        Rn8302_API.SpiCS(CSEnable);//PinWrite_ADCS(0);
        temp = (u8)(wReg & 0x00ff);
        chksum = temp;
        Rn8302_API.SpiWrite(temp);  //first write hight Addr
        temp = (((u8)(wReg >> 4)) & 0xf0) + 0x80;
        chksum += temp;
        Rn8302_API.SpiWrite(temp);

        for (i = ucLen; i > 0; i--)
        {
            Rn8302_API.SpiWrite(pBuf[i - 1]); // first write high data
            chksum += pBuf[i - 1];
        }
        chksum = ~chksum;
        Rn8302_API.SpiWrite(chksum);

        if (wReg != RN830x_OTPDBG)     // RN830x_OTPDBG,进入调试模式时不能插入读操作
        {
            Rn8302_API.SpiWrite(0x8D);
            chksum = 0x8D;
            temp = ((u8)(0x018D >> 4) & 0xf0);
            Rn8302_API.SpiWrite(temp);
            chksum += temp;
            for (i = 0; i < 3; i++)     // dyf 先读3字节数据，0x018D可能是3字节或者4字节，写扩位命令后为4字节
            {
                temp = Rn8302_API.SpiRead();
                chksum += temp;
                buff[i] = temp;         // dyf 先缓存3字节上次写的数据
            }
            if (err == SUCCESS)
            {
                temp = Rn8302_API.SpiRead();
                if (temp != ((uint8_t)~chksum) || (ucLen > 3))        // dyf 先检查0x018D是3字节长度的情况
                {
                    chksum += temp;
                    buff[3] = temp;   // 缓存，当作第4字节数据
                    temp = Rn8302_API.SpiRead();
                    if (temp != ((uint8_t)~chksum) || (ucLen > 4))   // dyf 再检查0x018D是4字节长度的情况
                    {
                        err = ERROR;
                    }
                    else
                    {
                        for (i = 0; i < ucLen; i++)     // dyf 检查上次写入的寄存器数据是否一致，0x018D是4字节长度的情况
                        {
                            if (pBuf[i] != buff[3 - i])
                            {
                                err = ERROR;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    for (i = 0; i < ucLen; i++)         // dyf 检查上次写入的寄存器数据是否一致，0x018D是3字节长度的情况
                    {
                        if (pBuf[i] != buff[2 - i])
                        {
                            err = ERROR;
                            break;
                        }
                    }
                }
            }
        }

        Rn8302_API.SpiCS(CSDisable);//PinWrite_ADCS(1);
        if (err == SUCCESS)
        {
            break;
        }
        Rn8302_API.Delay_1us(4);
    }
    return (err);
}

/*********************************************************************************************************
** Function name:           fnRN7306_Read
** Descriptions:
** input parameters:
** output parameters:       None
** Returned value:
*********************************************************************************************************/
ErrorStatus fnRN8302_Read(uint16_t wReg, uint8_t *pBuf, uint8_t ucLen)
{
    uint8_t i, temp, chksum, Repeat;
    ErrorStatus err;
    if (ucLen == 0)
    {
        return (ERROR);
    }
    for (Repeat = 3; Repeat != 0 ; Repeat--)
    {
        err = SUCCESS;
        Rn8302_API.SpiCS(CSEnable);//PinWrite_ADCS(0);
        temp = (u8)(wReg & 0x00ff);
        chksum = temp;
        Rn8302_API.SpiWrite(temp);  //first write hight Addr
        temp = ((u8)(wReg >> 4)) & 0xf0;
        chksum += temp;
        Rn8302_API.SpiWrite(temp);

        for (i = ucLen; i > 0; i--)
        {
            pBuf[i - 1] = Rn8302_API.SpiRead();
            chksum += pBuf[i - 1];
        }
        chksum = ~chksum;
        if (Rn8302_API.SpiRead() != chksum)
        {
            err = ERROR;
        }
        //      //---读RData寄存器检查------------------------------------
        //      if(err != SUCCESS) continue;
        //      Rn8302_API.SpiWrite( 0x8c);
        //      chksum = 0x8c;
        //      temp =  ( (u8)(0x018C >> 4) & 0xf0);
        //      Rn8302_API.SpiWrite( temp );
        //      chksum += temp;
        //      for(i = 4 ; i > 0 ; i--)
        //      {
        //          temp = Rn8302_API.SpiRead();
        //          if(ucLen >= i)
        //          {
        //              if(temp != pBuf[i - 1])
        //              {
        //                  err = ERROR;
        //                  break;
        //              }
        //          }
        //          chksum += temp;
        //      }
        //      if(err == SUCCESS)
        //        {
        //          chksum = ~chksum;
        //          temp = Rn8302_API.SpiRead();
        //          if(temp != chksum)  err = ERROR;
        //          }
        Rn8302_API.SpiCS(CSDisable);  // ronggc
        if (err == SUCCESS)
        {
            break;
        }
        Rn8302_API.Delay_1us(20);  // ronggc 4->20
        for (i = ucLen; i > 0; i--)
        {
            pBuf[i - 1] = 0;
        }
    }
    Rn8302_API.SpiCS(CSDisable);
    return (err);
}

/*********************************************************************************************************
** Function name:           fnRN7306_ReadBuf
** Descriptions:
** input parameters:
** output parameters:       None
** Returned value:
*********************************************************************************************************/
void fnRN8302_ReadBuf(uint16_t wReg, uint8_t *pBuf)
{
    uint8_t i, j, temp, chksum;
    Rn8302_API.SpiCS(CSEnable);//PinWrite_ADCS(0);
    temp = (u8)(wReg & 0x00ff);
    chksum = temp;
    Rn8302_API.SpiWrite(temp);  //first write hight Addr
    temp = ((u8)(wReg >> 4)) & 0xf0;
    temp = temp | 0x0c ;            //BRUST,读取地址为16
    chksum += temp;
    Rn8302_API.SpiWrite(temp);

    for (j = 0; j < 16 ; j++)
    {
        for (i = 3; i > 0; i--)
        {
            pBuf[(i + j * 3 - 1)] = Rn8302_API.SpiRead();
            chksum += pBuf[i - 1];
        }
    }
    if (Rn8302_API.SpiRead() != chksum)
    {
        Rn8302_API.SpiCS(CSDisable);//DISABLE_RN7306();//PinWrite_ADCS(1);
    }
    Rn8302_API.SpiCS(CSDisable);
}

/*********************************************************************************************************
** Function name:           fnRN7306_CheckRegSum
** Descriptions:
** input parameters:
** output parameters:       None
** Returned value:
*********************************************************************************************************/
ErrorStatus fnRN8302_CheckRegSum(uint32_t *RtCheckSum)
{
    uint32_t CheckSum1, CheckSum2;

    CheckSum1 = 0;
    CheckSum2 = 0;

    fnRN8302_Read(RN8302_CheckSum1, (uint8_t *)(&CheckSum1), 4);
    fnRN8302_Read(RN8302_CheckSum2, (uint8_t *)(&CheckSum2), 4);

    *RtCheckSum = CheckSum1 + CheckSum2;
    return SUCCESS;
}

/*********************************************************************************************************
** Function name:         Rn8302_SpiCS
** Descriptions:           Rn8302  spi通讯CS
** input parameters:
** output parameters:   none
** Returned value:
*********************************************************************************************************/
void Rn8302_Spi_Init(void)
{
    #if(SPI_Rn7306_Mode == SPI_Rn7306_FirmwareMode)
    Rn8xxx_GPIO_CfgFun(PinSCS_C, _NORMALIO); /*"RN7306通讯SPI 的CS脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinSCS_C, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinSCS_C, 1);

    Rn8xxx_GPIO_CfgFun(PinSCLK, _NORMALIO); /*"RN7306通讯SPI 的CLK脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinSCLK, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinSCLK, 0);

    Rn8xxx_GPIO_CfgFun(PinSDI_C, _NORMALIO); /*"RN7306通讯SPI 的MOSI脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinSDI_C, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_CfgPullMode(PinSDI_C, Pull_ON); // dyf 需要关闭内部默认的上拉电阻，否则导致掉电后功耗比较高；Pull_ON 对应关闭上拉，与其他引脚设置不同
    Rn8xxx_GPIO_SetPin(PinSDI_C, 1);

    Rn8xxx_GPIO_CfgFun(PinSDO_C, _NORMALIO); /*"RN7306通讯SPI 的MISO脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinSDO_C, GPIO_MODE_IN, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinSDO_C, Pull_ON);

    #else
    Rn8xxx_GPIO_CfgFun(PinSCS_C, _NORMALIO); /*"RN7306通讯SPI 的CS脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinSCS_C, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinSCS_C, 1);

    Rn8xxx_GPIO_CfgFun(PinSCLK, _SPI); /*"RN7306通讯SPI 的CLK脚"*/

    Rn8xxx_GPIO_CfgFun(PinSDI_C, _SPI); /*"RN7306通讯SPI 的MOSI脚"*/

    Rn8xxx_GPIO_CfgFun(PinSDO_C, _SPI); /*"RN7306通讯SPI 的MISO脚"*/
    Rn8xxx_GPIO_CfgPullMode(PinSDO_C, Pull_ON);

    uSPICtlPara_TypeDef spi_para;

    spi_para.gSPICtl = SPICTL_DEFAULT;
    spi_para.SPICtl_EN = SPICTL_EN;
    spi_para.SPICtl_MAST_SLAV = SPICTL_MAST;
    spi_para.SPICtl_LMSB = SPICTL_MSB;
    spi_para.SPICtl_CPOL = (SPICtl_Mode_01 >> 1); //模式0
    spi_para.SPICtl_CPHA = (SPICtl_Mode_01 & 0x01);
    spi_para.SPICtl_WIDTH = SPICTL_WIDTH_8BIT;

    Rn8xxx_Spi_Init(Rn7306_SPI_ID, spi_para, Rn7306_SPI_SPEED);

    #endif
}

/*********************************************************************************************************
** Function name:         Rn7306_SpiCS
** Descriptions:           Rn7306  spi通讯CS
** input parameters:
** output parameters:   none
** Returned value:
*********************************************************************************************************/
void Rn8302_SpiCS(eRn8302_SpiCS_TypeDef CSSwitch)   /*" RN7326E  spi通讯CS原型 "*/
{
    if (CSSwitch == CSEnable)
    {
        PinWrite_ADCS(0);
    }
    else
    {
        PinWrite_ADCS(1);
    }
}

/*********************************************************************************************************
** Function name:   Rn7306Spi_WriteByte
** Descriptions:    RN7306写数据,SPI采用模式1,SCLK高电平时写数据
** input parameters:    spi send data
** output parameters:   null
** Returned value:         null
*********************************************************************************************************/
void Rn8302Spi_WriteByte(uint8_t data)
{
    #if(SPI_Rn7306_Mode == SPI_Rn7306_FirmwareMode)
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        PinWrite_ADSCLK(1);
        PinWrite_ADSCLK(1);
        if (data & 0x80)
        {
            PinWrite_ADSMOSI(1);
            PinWrite_ADSMOSI(1);
        }
        else
        {
            PinWrite_ADSMOSI(0);
            PinWrite_ADSMOSI(0);
        }

        PinWrite_ADSCLK(0);
        PinWrite_ADSCLK(0);

        data <<= 1;
    }
    PinWrite_ADSMOSI(1);
    PinWrite_ADSMOSI(1);

    #else
    Rn8xxx_Spi_WriteByte(Rn7306_SPI_ID, data);
    #endif
}

/*********************************************************************************************************
** Function name:   Rn7306Spi_ReadByte
** Descriptions:    RN7306读数据,SPI采用模式1,SCLK下降沿取数据
** input parameters:    null
** output parameters:   null
** Returned value:      spi received data
*********************************************************************************************************/
uint8_t Rn8302Spi_ReadByte(void)
{
    #if(SPI_Rn7306_Mode == SPI_Rn7306_FirmwareMode)
    uint8_t i, data = 0;
    for (i = 0; i < 8; i++)
    {
        data <<= 1;
        PinWrite_ADSCLK(1);
        PinWrite_ADSCLK(1);

        PinWrite_ADSCLK(0);
        PinWrite_ADSCLK(0);
        if (PinRead_ADMISO())
        {
            data = data + 0x1;
        }
    }
    return  data;
    #else
    return (Rn8xxx_Spi_ReadByte(Rn7306_SPI_ID));
    #endif
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
