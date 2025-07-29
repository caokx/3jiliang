/****************************************************************************
* @file     IIC.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.06.10
* @brief    IIC����
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
    if (((SYSCTL->OSC_CTRL1 >> 8) & 0x3) != 0x3) //��Ƶģʽ
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
    //����I2C��GPIO��APBʱ��
    SysCtl_EnableWrite;//����ϵͳ���ƼĴ���дʹ��
    //GPIO_Clk_En;
    I2C_Clk_En;
    SysCtl_DisableWrite;//�ر�ϵͳ���ƼĴ���дʹ��

    //I2Cʱ������
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
    I2C->STA = 0x3f;//��I2C״̬
    I2C->ADDR = iic_id;//��I2Cģ���ַ
    I2C->CTRL = 0x33;//I2C��ģʽ�£�����I2C STARTʱ�򼰴�I2Cģ���ַ����
    if (fnRegState_Detect((u32)(&I2C->STA), 2, 1, IIC_TIMEOUT) == ERROR) //�ȴ�STARTʱ��I2Cģ���ַ�������
    {
        //��ʱδ���STARTʱ��I2Cģ���ַ���䣬�����־�Ĵ��������ش���״̬
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
        //I2C���ڶ�����״̬�£��������һ�δ�����ɺ󣬲�����STOPʱ��
        if (fnRegState_Detect((u32)(&I2C->STA), 2, 1, IIC_TIMEOUT * 2) == ERROR)//�ȴ������Ƿ����
        {
            //��ʱ����δ��ɣ�����״̬�֣�������֣�������
            I2C->STA = 0x3f;
            I2C->CTRL = 0;
            return ;
        }
    }
    I2C->CTRL = 0x35;//����STOPʱ����

    if (fnRegState_Detect((u32)(&I2C->STA), 0, 1, IIC_TIMEOUT) == ERROR)  //�ȴ�STOPʱ�������
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
    if (fnRegState_Detect((u32)(&I2C->STA), 2, 1, IIC_TIMEOUT) == ERROR)  //�ȴ�I2C���ݷ������
    {
        //��ʱ����δ������ɣ���״̬�������ش���
        I2C->STA = 0x3f;
        return ERROR;
    }
    if (I2C->STA & 0x20)
    {
        //���ͳ�ͻ������״̬�������ش���
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

    if (fnRegState_Detect((u32)(&I2C->STA), 2, 1, IIC_TIMEOUT * 2) == ERROR)//�ȴ����ݽ������
    {
        //��ʱ����δ������ɣ���״̬����������0
        I2C->STA = 0x3f;
        return I2C->DATA;
    }
    if (I2C->STA & 0x20)
    {
        //�������ͳ�ͻ������״̬����������0
        I2C->STA = 0x3f;
        return I2C->DATA;
    }
    if (ACK != 1)
    {
        //��9��CLK��������ACK��Ӧ
        I2C->CTRL &= 0xffffffef;
    }
    I2C->STA = 0x3f;
    data = I2C->DATA;//��ȡ���ռĴ����ڵ�����
    return data;
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
