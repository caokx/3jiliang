
#define  __BSP_IIC_GLOBALS

#include <BSP.h>
//---------------------------------------------------
//---------------------------------------------------

void IIC_FirmMode_Start(void)
{
    PinMode_SCL0(GPIO_MODE_OUT);
    PinMode_SDA0(GPIO_MODE_OUT);
    PinWrite_SDA0(1);
    PinWrite_SDA0(1);
    fnDelay2us();

    PinWrite_SCL0(1);
    PinWrite_SCL0(1);
    fnDelay2us();

    PinWrite_SDA0(0);
    PinWrite_SDA0(0);
    fnDelay2us();

    PinWrite_SCL0(0);
    PinWrite_SCL0(0);
    fnDelay2us();
    return;
}

//---------------------------------------------------

void IIC_FirmMode_Stop(void)
{
    PinMode_SCL0(GPIO_MODE_OUT);
    PinMode_SDA0(GPIO_MODE_OUT);
    PinWrite_SDA0(0);
    PinWrite_SDA0(0);
    fnDelay2us();

    PinWrite_SCL0(1);
    PinWrite_SCL0(1);
    fnDelay2us();

    PinWrite_SDA0(1);
    PinWrite_SDA0(1);
    fnDelay2us();

    return ;
}

void IIC_FirmMode_Reset(void)
{
    u16 i;
    PinWrite_SDA0(0);
    PinWrite_SDA0(0);
    PinWrite_SCL0(0);
    PinWrite_SCL0(0);
    for (i = 0; i < 200; i++)
    {}
    PinWrite_SDA0(1);
    PinWrite_SDA0(1);
    PinWrite_SCL0(0);
    PinWrite_SCL0(0);
    for (i = 0; i < 200; i++)
    {}
    return;
}

//---------------------------------------------------

void IIC_FirmMode_ACK(void)
{
    PinMode_SCL0(GPIO_MODE_OUT);
    PinMode_SDA0(GPIO_MODE_OUT);
    PinWrite_SDA0(0);
    PinWrite_SDA0(0);
    fnDelay2us();

    PinWrite_SCL0(1);
    PinWrite_SCL0(1);
    fnDelay2us();

    PinWrite_SCL0(0);
    PinWrite_SCL0(0);
    return;
}

//---------------------------------------------------

void IIC_FirmMode_NOACK(void)
{
    PinMode_SCL0(GPIO_MODE_OUT);
    PinMode_SDA0(GPIO_MODE_OUT);
    PinWrite_SDA0(1);
    PinWrite_SDA0(1);
    fnDelay2us();

    PinWrite_SCL0(1);
    PinWrite_SCL0(1);
    fnDelay2us();

    PinWrite_SCL0(0);
    PinWrite_SCL0(0);
    fnDelay2us();
    return;
}

/*********************************
向I2C口发一个字节，发送完后收到应答返回TURE,否则返回false.
**********************************/
u8 IIC_FirmMode_SendByte(u8 B)
{
    u8  i;
    i = 0;

    PinMode_SCL0(GPIO_MODE_OUT);
    PinMode_SDA0(GPIO_MODE_OUT);
    PinWrite_SCL0(0);
    fnDelay2us();

    for (; i < 8; i++)
    {
        if (B & 0x80)
        {
            PinWrite_SDA0(1);
            PinWrite_SDA0(1);
            fnDelay2us();
        }
        else
        {
            PinWrite_SDA0(0);
            PinWrite_SDA0(0);
            fnDelay2us();
        }
        PinWrite_SCL0(0);
        fnDelay2us();

        PinWrite_SCL0(1);
        fnDelay2us();

        PinWrite_SCL0(0);
        fnDelay2us();
        B <<= 1;
    }
    PinMode_SDA0(GPIO_MODE_IN);
    PinWrite_SCL0(0);
    PinWrite_SCL0(0);
    fnDelay2us();

    PinWrite_SCL0(1);
    PinWrite_SCL0(1);
    fnDelay2us();
    B = true;
    if (PinRead_SDA0())
    {
        B = false;
    }
    PinWrite_SCL0(0);
    PinWrite_SCL0(0);
    fnDelay2us();

    return B;
}

//---------------------------------------------------
/*********************************
从I2C口读一个字节，返回读到的字节数据
**********************************/
u8 IIC_FirmMode_ReceiveByte(BOOL ACK)
{
    u8 i, B;

    PinMode_SDA0(GPIO_MODE_IN);
    PinMode_SCL0(GPIO_MODE_OUT);
    PinWrite_SCL0(0);
    PinWrite_SCL0(0);
    fnDelay2us();
    B = 0;
    i = 0;
    for (; i < 8; i++)
    {
        B <<= 1;
        PinWrite_SCL0(1);
        PinWrite_SCL0(1);
        fnDelay2us();
        if (PinRead_SDA0())
        {
            B = B + 0x1;
        }
        PinWrite_SCL0(0);
        PinWrite_SCL0(0);
        fnDelay2us();
    }
    if (ACK)
    {
        IIC_FirmMode_ACK();
    }
    else
    {
        IIC_FirmMode_NOACK();
    }
    return B;
}

//---------------------------------------------------

void fnDelay_10ms(void)
{
    u16 i;
    for (i = 0; i <= 15000; i++)
    {
        __NOP();
        __NOP();
    }   //大约20MS 8M。
    return;
}

void fnDelay2us(void)
{
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    __NOP(); // dyf 2.49M add nop()
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    /*
    __NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();
    */
}

//---------------------------------------------------
