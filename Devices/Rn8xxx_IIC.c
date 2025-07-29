/****************************************************************************
* @file     IIC.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.06.10
* @brief    IIC驱动
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include <Rn8xxx_IIC.h>

/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/

void Rn8xxx_IICDelayUs(u32 i)
{
    if (((SYSCTL->OSC_CTRL1 >> 8) & 0x3) != 0x3) //高频模式
    {
        for (; i > 0; i--)
        {
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
        }
    }
    else
    {
        for (; i > 0; i--)
        {
            __NOP();
            __NOP();
        }
    }
}

/*********************************************************************************************************
** Function name:     Rn8xxx_IIC_HardMode_Init
** Descriptions:  IIC initial
** input parameters: clkdiv:division for IIC apb clock
** output parameters:   null
** Returned value:   null
*********************************************************************************************************/
void Rn8xxx_IIC_HardMode_Init(uint8_t clkdiv)
{
    //开启I2C、GPIO的APB时钟
    SysCtl_EnableWrite;//开启系统控制寄存器写使能
    //GPIO_Clk_En;
    I2C_Clk_En;
    SysCtl_DisableWrite;//关闭系统控制寄存器写使能

    //I2C时钟配置
    I2C->CLK = clkdiv;
}

/*********************************************************************************************************
** Function name:     Rn8xxx_IIC_HardMode_Start
** Descriptions:  to triggle start signal matching IIC  standard
** input parameters: iic_id: communication id of slave iic
** output parameters:   null
** Returned value:  SUCCESS:  ;  ERROR:  ;
*********************************************************************************************************/
ErrorStatus Rn8xxx_IIC_HardMode_Start(uint8_t iic_id)
{
    I2C->STA = 0x3f;//清I2C状态
    I2C->ADDR = iic_id;//从I2C模块地址
    I2C->CTRL = 0x33;//I2C主模式下，启动I2C START时序及从I2C模块地址发送
    if (fnRegState_Detect((u32)(&I2C->STA), 2, 1, IIC_TIMEOUT) == ERROR) //等待START时序及I2C模块地址传输完成
    {
        //超时未完成START时序及I2C模块地址传输，则清标志寄存器并返回错误状态
        I2C->STA = 0x3f;//
        return ERROR;
    }
    if (I2C->STA & 0x02)
    {
        I2C->STA = 0x3f;
        return ERROR;
    }
    I2C->STA = 0x3f;
    return SUCCESS;
}

/*********************************************************************************************************
** Function name:     Rn8xxx_IIC_HardMode_Stop
** Descriptions:  to send stop signal matching IIC  standard
** input parameters: null
** output parameters:   null
** Returned value:   null
*********************************************************************************************************/
void Rn8xxx_IIC_HardMode_Stop(void)
{
    if (I2C->STA & 0x100)
    {
        //I2C处于读操作状态下，则需待上一次传输完成后，才启动STOP时序
        if (fnRegState_Detect((u32)(&I2C->STA), 2, 1, IIC_TIMEOUT * 2) == ERROR)//等待传输是否完成
        {
            //超时传输未完成，则清状态字，清控制字，并返回
            I2C->STA = 0x3f;
            I2C->CTRL = 0;
            return ;
        }
    }
    I2C->CTRL = 0x35;//启动STOP时序发送

    if (fnRegState_Detect((u32)(&I2C->STA), 0, 1, IIC_TIMEOUT) == ERROR)  //等待STOP时序发送完成
    {
    }

    I2C->STA = 0x3f;
    I2C->CTRL = 0;
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void IIC_HardMode_Reset(void)
{
    Rn8xxx_IICDelayUs(1);
    Rn8xxx_IIC_HardMode_Stop();
    Rn8xxx_IICDelayUs(2);
    Rn8xxx_IIC_HardMode_Stop();
}

/*********************************************************************************************************
** Function name:     Rn8xxx_IIC_HardMode_SendByte
** Descriptions:  to send data through IIC
** input parameters:  data: data to be sent
** output parameters:   null
** Returned value:   SUCCESS:  ;   ERROR:  ;
*********************************************************************************************************/
ErrorStatus Rn8xxx_IIC_HardMode_SendByte(uint8_t data)
{
    I2C->STA = 0x3f;
    I2C->DATA = data;
    if (fnRegState_Detect((u32)(&I2C->STA), 2, 1, IIC_TIMEOUT) == ERROR)  //等待I2C数据发送完成
    {
        //超时数据未发送完成，清状态，并返回错误
        I2C->STA = 0x3f;
        return ERROR;
    }
    if (I2C->STA & 0x20)
    {
        //发送冲突，则清状态，并返回错误
        I2C->STA = 0x3f;
        return ERROR;
    }
    I2C->STA = 0x3f;
    return SUCCESS;
}

/*********************************************************************************************************
** Function name:
** Descriptions:        IIC initial
** input parameters:  ACK: 1=don't change IIC->CTRL to keep the need for ack  as the last time;
                                                     0= change IIC->CTRL to don't triggle ack on the 9th clk
** output parameters:   null
** Returned value:      null
*********************************************************************************************************/
u8  Rn8xxx_IIC_HardMode_ReceiveByte(BOOL ACK)
{
    u8 data = 0;

    if (fnRegState_Detect((u32)(&I2C->STA), 2, 1, IIC_TIMEOUT * 2) == ERROR)//等待数据接收完成
    {
        //超时数据未接收完成，清状态，返回数据0
        I2C->STA = 0x3f;
        return I2C->DATA;
    }
    if (I2C->STA & 0x20)
    {
        //发生发送冲突，则清状态，返回数据0
        I2C->STA = 0x3f;
        return I2C->DATA;
    }
    if (ACK != 1)
    {
        //第9个CLK，不产生ACK响应
        I2C->CTRL &= 0xffffffef;
    }
    I2C->STA = 0x3f;
    data = I2C->DATA;//获取接收寄存器内的数据
    return data;
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
