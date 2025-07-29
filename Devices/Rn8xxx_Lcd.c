/****************************************************************************
* @file     Rn8xxx_Lcd.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.06.12
* @brief    Lcd����
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include <stdint.h>
//#include <Dat_Types.h>
//#include <RN8318_RegDefine.h>
//#include <RN8318.h>
//#include <system_RN8318.h>

#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include <Rn8xxx_Lcd.h>

/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/*********************************************************************************************************
** Function name:       lcd_BIASLVL_Get
** Descriptions:        Charge Pmup ��ʽ�ṩ LCD ƫ�õ�ѹ
** input parameters:    LCD_Voltage  Һ������ѹ�ȼ�N.NNV(��λV ,����-2)
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
u8 lcd_BIASLVL_Get(u16 Vref, u8 bisa, u16 LCD_Voltage)
{
    u8 BIASLVL;
    float  VaVoltage;
    if (bisa == LCD_1_3BIAS)
    {
        VaVoltage = (float)LCD_Voltage / 3;
        VaVoltage = VaVoltage / ((float)Vref);
    }
    else
    {
        VaVoltage = (float)LCD_Voltage / 4;
        VaVoltage = VaVoltage / ((float)Vref);
    }

    if (VaVoltage >= 1)
    {
        BIASLVL = 0x20 + (u8)((VaVoltage - 1) * 63);
    }
    else
    {
        BIASLVL = (u8)((VaVoltage) * 63) -32;
    }
    BIASLVL = (BIASLVL & 0x3F);
    return BIASLVL;
}

/*********************************************************************************************************
** Function name:       lcd_LDO_V_Get
** Descriptions:        ���贮��ѹ��ʽ
** input parameters:    LCD_Voltage  Һ������ѹ�ȼ�N.NNV(��λV ,����-2)
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
eLCD_LDO_V_TypeDef lcd_LDO_V_Get(u16 LCD_Voltage)
{
    eLCD_LDO_V_TypeDef lcd_ldo_V;
    if (LCD_Voltage <= 270)
    {
        lcd_ldo_V = LCD_LDO2_70V;
    }
    else if (LCD_Voltage >= 360)
    {
        lcd_ldo_V = LCD_LDO3_60V;
    }
    else
    {
        lcd_ldo_V = (eLCD_LDO_V_TypeDef)((LCD_Voltage - 270) / 6);
    }
    return lcd_ldo_V;
}

/* Exported functions ----------------------------------------------------------*/

/*********************************************************************************************************
** Function name:       Rn8xxx_Lcd_Init
** Descriptions:        Һ��������ʼ��
** input parameters:    mode  ����ģʽ
**                      type
**                      bisa  ��Һ��bisa��������
**                      duty  ��Һ��COM�ھ���
**                      LCD_Voltage  Һ������ѹ�ȼ�N.NNV(��λV ,����-2)
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void Rn8xxx_Lcd_Init(uLCD_CtlPara_TypeDef LCD_CtlPara, u16 LCD_Voltage)
{
    eLCD_LDO_V_TypeDef lcd_ldo_V;
    u8 BIASLVL;
    /*"����LCD��APBʱ��"*/
    SysCtl_EnableWrite;
    LCD_Clk_En;
    SysCtl_DisableWrite;

    LCD->CTRL = 0x0;

    /*"�ȴ� LCD_STATUS ״̬�Ĵ����� 6 λ�Ƿ�Ϊ 0������״̬��"*/
    /*"������������һ��������ȴ���"*/
    /*"�ȴ�ʱ   ����Ϊ 16MS ���ҡ�"*/
    if (fnRegState_Detect((u32)(&LCD->STA), 6, 0, LCD_TIMEOUT) == ERROR)
    {
        return;
    }

    if (LCD_ChargePmup == LCD_CtlPara.LcdCtl_PWD_PUMP)
    {
        LCD_CtlPara.LcdCtl_EN = LCD_CTL_DIS;

        BIASLVL = lcd_BIASLVL_Get(125, LCD_CtlPara.LcdCtl_BIAS, LCD_Voltage);
        LCD_CtlPara.LcdCtl_BIASLVL = BIASLVL;

        LCD->CTRL = LCD_CtlPara.gLCDCtl;
        LCD->RESCTL = 0xB81;         /*"Ĭ��ֵ"*/
    }
    else
    {
        LCD_CtlPara.LcdCtl_EN = LCD_CTL_DIS;

        LCD->CTRL = LCD_CtlPara.gLCDCtl;

        lcd_ldo_V = lcd_LDO_V_Get(LCD_Voltage);
        LCD->RESCTL = ((1 << 2) |           /*" RES_FT���� 2 ��"*/
                       (1 << 4) |              /*"RES_DT"*/
                       (1 << 8) |              /*"�򿪿��ٳ�繦�� "*/
                       (lcd_ldo_V << 9));   /*"LDO �����ƽѡ���ź� "*/
    }

    switch (LCD_CtlPara.LcdCtl_DUTY)
    {
        //-------------------------
        case LCD_Static_DUTY:
            LCD->CLKDIV = 0xff;
            break;
        case LCD_1_2DUTY:
            LCD->CLKDIV = 0x7f;
            break;
        case LCD_1_3DUTY:
            LCD->CLKDIV = 0x54;
            break;
        case LCD_1_4DUTY:
            LCD->CLKDIV = 0x3f;
            break;
        case LCD_1_6DUTY:
            LCD->CLKDIV = 0x2a;
            break;
        case LCD_1_8DUTY:
            LCD->CLKDIV = 0x1f;
            break;
        default:
            break;
    }

    LCD->BLINK = 0x000001;/*"�ر���˸����"*/

    LCD->CTRL |= LCD_CTL_EN ;
}

/*********************************************************************************************************
** Function name:       Lcd_SetAllScr
** Descriptions:        Һ����������
** input parameters:    value
** output parameters:       None
** Returned value:      None
*********************************************************************************************************/
void Rn8xxx_Lcd_ScrSet(uint8_t value, uint8_t len)
{
    u8 i;
    if (len > 37)
    {
        return;
    }
    for (i = 0; i < len; i++)
    {
        LCD->BUF[i] = value;
    }
    return;
}

/*********************************************************************************************************
** Function name:       Lcd_SetAllScr
** Descriptions:        Һ����������
** input parameters:    value
** output parameters:       None
** Returned value:      None
*********************************************************************************************************/
void Rn8xxx_Lcd_ScrCpy(uint8_t *buf, uint8_t len)
{
    u8 i;
    if (len > 37)
    {
        return;
    }
    for (i = 0; i < len; i++)
    {
        LCD->BUF[i] = buf[i];
    }
    return;
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void Rn8xxx_Lcd_Close(void)
{
    LCD->CTRL &= (~BIT0);

    #if 0
    /*"�ȴ� LCD_STATUS ״̬�Ĵ����� 6 λ�Ƿ�Ϊ 0������״̬��"*/
    /*"������������һ��������ȴ���"*/
    /*"�ȴ�ʱ   ����Ϊ 16MS ���ҡ�"*/
    if (fnRegState_Detect((u32)(&LCD->STA), 6, 0, LCD_TIMEOUT) == ERROR)
    {
        return ;
    }
    #endif
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
