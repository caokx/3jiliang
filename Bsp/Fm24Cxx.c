/****************************************************************************
* @file
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.04.28
* @brief
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/

#define  _FM24CXX_GLOBALS

#include <BSP.h>

/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/

/*
**-----------------------------------------------------------------------------
**EEPROM存储器操作子程序
**-----------------------------------------------------------------------------
*/

//---------------------------------------------------

// /************************
//  判断I2C器件忙否
// *************************/
// void IsI2CBusy(u8 DeviceNo)
// {
//   u8 B;
//   u16 i;
//
//   for (i=0;i<1000;i++) /*等待器件响应*/
//   {
//     IIC_FirmMode_Start();
//     B=(DeviceNo<<1)+0xa0;
//     B=IIC_FirmMode_SendByte(B);
//     IIC_FirmMode_Stop();
//     if (B==0) break;/*如有响应则退出，否则循环200次*/
//   }
//   return;
// }
//---------------------------------------------------

//---------------------------------------------------
bool fnCheckNVRAM(u8 DeviceNo, u16 Address, u8 *Buff, u16 Length)
{
    u16 i;
    u8 Data;
    BOOL ACK = 1;

    #if(IICFun_Mode == IICFun_FirmwareMode)

    IIC_FirmMode_Start();
    i = (DeviceNo << 1) +0xa0;
    if (IIC_FirmMode_SendByte(i) == false)
    {
        IIC_FirmMode_Stop();    //Error  return false;
        return false;
    }
    if (IIC_FirmMode_SendByte(Address >> 8) == false)
    {
        IIC_FirmMode_Stop();    //Error  return false;
        return false;
    }
    if (IIC_FirmMode_SendByte(Address) == false)
    {
        IIC_FirmMode_Stop();    //Error  return false;
        return false;
    }
    IIC_FirmMode_Start();

    i = (DeviceNo << 1) +0xa1;
    if (IIC_FirmMode_SendByte(i) == false)
    {
        IIC_FirmMode_Stop();    //Error  return false;
        return false;
    }

    for (i = 0; i < Length - 1; i++)
    {
        Data = IIC_FirmMode_ReceiveByte(ACK);
        if (Data != Buff[i])
        {
            IIC_FirmMode_Stop();
            return false;
        }
    }
    Data = IIC_FirmMode_ReceiveByte(!ACK);
    if (Data != Buff[i])
    {
        IIC_FirmMode_Stop();
        return false;
    }
    IIC_FirmMode_Stop();
    return true;

    #else

    i = (DeviceNo << 1) +0xa0;
    if (Rn8xxx_IIC_HardMode_Start(i) == ERROR)
    {
        Rn8xxx_IIC_HardMode_Stop();    //Error  return false;
        return false;
    }
    if (Rn8xxx_IIC_HardMode_SendByte(Address >> 8) == ERROR)
    {
        Rn8xxx_IIC_HardMode_Stop();    //Error  return false;
        return false;
    }
    if (Rn8xxx_IIC_HardMode_SendByte(Address) == ERROR)
    {
        Rn8xxx_IIC_HardMode_Stop();    //Error  return false;
        return false;
    }

    i = (DeviceNo << 1) +0xa1;
    if (Rn8xxx_IIC_HardMode_Start(i) == ERROR)
    {
        Rn8xxx_IIC_HardMode_Stop();    //Error  return false;
        return false;
    }

    for (i = 0; i < Length - 1; i++)
    {
        Data = Rn8xxx_IIC_HardMode_ReceiveByte(ACK);
        if (Data != Buff[i])
        {
            Rn8xxx_IIC_HardMode_Stop();
            return false;
        }
    }
    Data = Rn8xxx_IIC_HardMode_ReceiveByte(!ACK);
    if (Data != Buff[i])
    {
        Rn8xxx_IIC_HardMode_Stop();
        return false;
    }
    Rn8xxx_IIC_HardMode_Stop();
    return true;

    #endif
}

//---------------------------------------------------
/************************
Address~AAddress+Length-1不可跨节，每节64Bytes
*************************/
ErrorStatus fnOperateNVRAM(BOOL Read_Write, u8 DeviceNo, u16 Address, u8 *Buff, u16 Length, u8 Repeat)
{
    u16 i;
    u8 ReReadTimes;
    BOOL ACK = 1;

    if (Length == 0)
    {
        return ERROR;
    }

    for (ReReadTimes = 0; ReReadTimes <= Repeat; ReReadTimes++)
    {
        #if(IICFun_Mode == IICFun_FirmwareMode)
        IIC_FirmMode_Stop();
        fnDelay2us();
        IIC_FirmMode_Start();
        i = (DeviceNo << 1) +0xa0;
        if (IIC_FirmMode_SendByte(i) == false)
        {
            IIC_FirmMode_Stop();    //Error  return false;
            continue;
        }
        if (IIC_FirmMode_SendByte(Address >> 8) == false)
        {
            IIC_FirmMode_Stop();    //Error  return false;
            continue;
        }
        if (IIC_FirmMode_SendByte(Address) == false)
        {
            IIC_FirmMode_Stop();    //Error  return false;
            continue;
        }

        if (Read == Read_Write)
        {
            IIC_FirmMode_Start();
            i = (DeviceNo << 1) +0xa1;
            if (IIC_FirmMode_SendByte(i) == false)
            {
                IIC_FirmMode_Stop();    //Error  return false;
                continue;
            }

            for (i = 0; i < Length - 1; i++)
            {
                *(Buff + i) = IIC_FirmMode_ReceiveByte(ACK);
            }
            *(Buff + i) = IIC_FirmMode_ReceiveByte(!ACK);
            IIC_FirmMode_Stop();
        }
        else
        {
            ACK = 1;
            for (i = 0; i < Length; i++)
            {
                if (IIC_FirmMode_SendByte(*(Buff + i)) == false)
                {
                    IIC_FirmMode_Stop();
                    ACK = 0;
                    break;
                }   //Error  return false;
            }
            if (!ACK)
            {
                continue;
            }
            IIC_FirmMode_Stop();
            //zhupdebug if(DeviceNo >= 0x02)
            {
                SystemDelayUs(5300);//5000 dyf 合入宋工的新修改，适应ST的EE，升频29M 20000->5300
            }
        }
        #else

        i = (DeviceNo << 1) +0xa0;
        if (Rn8xxx_IIC_HardMode_Start(i) == false)
        {
            Rn8xxx_IIC_HardMode_Stop();    //Error  return false;
            continue;
        }
        if (Rn8xxx_IIC_HardMode_SendByte(Address >> 8) == false)
        {
            Rn8xxx_IIC_HardMode_Stop();    //Error  return false;
            continue;
        }
        if (Rn8xxx_IIC_HardMode_SendByte(Address) == false)
        {
            Rn8xxx_IIC_HardMode_Stop();    //Error  return false;
            continue;
        }

        if (Read == Read_Write)
        {
            i = (DeviceNo << 1) +0xa1;
            if (Rn8xxx_IIC_HardMode_Start(i) == false)
            {
                Rn8xxx_IIC_HardMode_Stop();    //Error  return false;
                continue;
            }

            for (i = 0; i < Length - 1; i++)
            {
                *(Buff + i) = Rn8xxx_IIC_HardMode_ReceiveByte(ACK);
            }
            *(Buff + i) = Rn8xxx_IIC_HardMode_ReceiveByte(!ACK);
            Rn8xxx_IIC_HardMode_Stop();
        }
        else
        {
            ACK = 1;
            for (i = 0; i < Length; i++)
            {
                if (Rn8xxx_IIC_HardMode_SendByte(*(Buff + i)) == false)
                {
                    Rn8xxx_IIC_HardMode_Stop();    //Error  return false;
                    ACK = 0;
                    break;
                }
            }
            if (!ACK)
            {
                continue;
            }
            Rn8xxx_IIC_HardMode_Stop();
            //if(DeviceNo >= 0x02)
            SystemDelayUs(5000);
        }
        #endif

        if ((fnCheckNVRAM(DeviceNo, Address, Buff, Length) == true))
        {
            return (SUCCESS);
        }
    }
    return (ERROR);
}

//---------------------------------------------------
//函数功能：I2C存储器读取数据，在此实现跨页操作
//入口参数：Dst取数缓冲区目标指针，Src取数源地址，DatLen要取的数据长度，Repeat失败重复次数
//出口参数：SUCCESS成功，ERROR失败
ErrorStatus fnFM24CXX_Read(u8 *Dst, u32 Src, u32 DatLen, u8 Repeat)
{
    u16 AddressL, AddressH;
    u16 B;
    u16 AddingTimes = 0;

    if (DatLen == 0)
    {
        return (ERROR);
    }
    if (Src >= EEPROM2_DeviceNo)
    {
        if (EEPROM2_MAXSIZE <= ((Src - EEPROM2_DeviceNo) + DatLen))
        {
            return (ERROR);
        }
    }
    else
    {
        if (EEPROM_MAXSize <= (Src + DatLen))
        {
            return (ERROR);
        }
    }
    //  if(Src >= 0x30000)  {if ( EEPROM_MAXSize <= (Src-0x30000+DatLen))  return(ERROR);}
    //  else {if ( EEPROM2_MAXSIZE <= (Src+DatLen))  return(ERROR);}

    while (DatLen)
    {
        if (++AddingTimes > 600)
        {
            return (ERROR);    //防止死循环
        }
        AddressH = (u16)(Src >> 16);
        AddressL = (u16)Src;
        if ((((~AddressL)&EEPROM_PageSize) +1) >= DatLen) /*与运算其实相当于求模运算，该语句保证从NVRAM中每一页的任意点开始*/
        {
            B = DatLen;
        }
        else
        {
            B = ((~AddressL)&EEPROM_PageSize) +1;
        }

        if (ERROR == fnOperateNVRAM(Read, AddressH, AddressL, Dst, B, Repeat))
        {
            #if(IICFun_Mode == IICFun_FirmwareMode)
            IIC_FirmMode_Reset();
            #else
            IIC_HardMode_Reset();
            #endif

            return (ERROR);
        }
        Dst += B;
        Src += B;
        DatLen -= B;
    }
    return (SUCCESS);
}

//---------------------------------------------------
//函数功能：I2C存储器写入数据，在此实现跨页操作
//入口参数：Dst写入数据的目标地址，Src写数缓冲区源指针，DatLen要写的数据长度，Repeat失败重复次数
//出口参数：SUCCESS成功，ERROR失败
ErrorStatus fnFM24CXX_Write(u32 Dst, u8 *Src, u32 DatLen, u8 Repeat)
{
    u16 AddressL, AddressH;
    u16 B;
    u16 AddingTimes = 0;

    if (DatLen == 0)
    {
        return (ERROR);
    }
    if (Dst >= EEPROM2_DeviceNo)
    {
        if (EEPROM2_MAXSIZE <= ((Dst - EEPROM2_DeviceNo) + DatLen))
        {
            return (ERROR);
        }
    }
    else
    {
        if (EEPROM_MAXSize <= (Dst + DatLen))
        {
            return (ERROR);
        }
    }

    while (DatLen)
    {
        if (++AddingTimes > 600)
        {
            return (ERROR); //防止死循环
        }

        AddressH = (u16)(Dst >> 16);
        AddressL = (u16)Dst;
        if ((((~AddressL)&EEPROM_PageSize) +1) >= DatLen) /*与运算其实相当于求模运算，该语句保证从NVRAM中每一页的任意点开始*/
        {
            B = DatLen;
        }
        else
        {
            B = ((~AddressL)&EEPROM_PageSize) +1;
        }

        if (ERROR == fnOperateNVRAM(Write, AddressH, AddressL, Src, B, Repeat))
        {
            #if(IICFun_Mode == IICFun_FirmwareMode)
            IIC_FirmMode_Reset();/*PinWrite_EEPow(0)*/;
            #else
            IIC_HardMode_Reset();
            #endif

            return (ERROR);
        }
        Dst += B;
        Src += B;
        DatLen -= B;
        fnWDT_Restart();
    }
    return (SUCCESS);
}

/*********************************************************************************************************
** Function name:       fnFm24c256_Init
** Descriptions:
** input parameters:    null
** output parameters: null
** Returned value:      null
*********************************************************************************************************/

void fnFm24c256_Init(void)
{
    #if(IICFun_Mode == IICFun_FirmwareMode)
    Rn8xxx_GPIO_CfgFun(PinEepromSCL, _NORMALIO); /*"E2    IIC通讯SCL脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinEepromSCL, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinEepromSCL, 1);
    Rn8xxx_GPIO_CfgFun(PinEepromSDA, _NORMALIO); /*"E2    IIC通讯SDA脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinEepromSDA, GPIO_MODE_OUT, GPIO_MODE_OUT);
    Rn8xxx_GPIO_SetPin(PinEepromSDA, 1);

    #else
    Rn8xxx_GPIO_CfgFun(PinEepromSCL, _IIC); /*"E2 IIC通讯SCL脚"*/
    Rn8xxx_GPIO_CfgFun(PinEepromSDA, _IIC); /*"E2 IIC通讯SDA脚"*/
    Rn8xxx_GPIO_CfgPullMode(PinEepromSDA, Pull_ON);

    Rn8xxx_IIC_HardMode_Init(EEPROM_CLK);
    #endif
}

void EEprom_Stop(void)
{
    Rn8xxx_GPIO_CfgFun(PinEepromSCL, _NORMALIO); /*"E2    IIC通讯SCL脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinEepromSCL, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgFun(PinEepromSDA, _NORMALIO); /*"E2    IIC通讯SDA脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinEepromSDA, GPIO_MODE_NORMAL, NORMAL_IN);

    #if(IICFun_Mode == IICFun_FirmwareMode)

    #else
    Rn8xxx_IIC_HardMode_Stop();
    #endif
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
