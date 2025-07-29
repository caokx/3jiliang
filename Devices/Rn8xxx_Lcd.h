/****************************************************************************
* @file     Rn8xxx_Lcd.h
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.06.12
* @brief    LcdDrive����
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  _LcdDrive_H
#define  _LcdDrive_H

/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/
#define LCD_TIMEOUT 0x3fff

#define LCDCTL_DEFAULT    0x00   //LCD_CTL �Ĵ�����λĬ��ֵ

/*"****************************   LCD_BUF  COM�ڶ���    ****************************"*/
#define     LCD_BUF_BIT0    0x01
#define     LCD_BUF_BIT1    0x02
#define     LCD_BUF_BIT2    0x04
#define     LCD_BUF_BIT3    0x08
#define     LCD_BUF_BIT4    0x10
#define     LCD_BUF_BIT5    0x20
#define     LCD_BUF_BIT6    0x40
#define     LCD_BUF_BIT7    0x80

/*"****************************   LCD_BUFָ��(SEG��)����    ****************************"*/
#define     LCD_BUF_0   0   /*"ƫ�Ƶ�ַ 0x  20   "*/
#define     LCD_BUF_1   1   /*"ƫ�Ƶ�ַ 0x  21   "*/
#define     LCD_BUF_2   2   /*"ƫ�Ƶ�ַ 0x  22   "*/
#define     LCD_BUF_3   3   /*"ƫ�Ƶ�ַ 0x  23   "*/
#define     LCD_BUF_4   4   /*"ƫ�Ƶ�ַ 0x  24   "*/
#define     LCD_BUF_5   5   /*"ƫ�Ƶ�ַ 0x  25   "*/
#define     LCD_BUF_6   6   /*"ƫ�Ƶ�ַ 0x  26   "*/
#define     LCD_BUF_7   7   /*"ƫ�Ƶ�ַ 0x  27   "*/
#define     LCD_BUF_8   8   /*"ƫ�Ƶ�ַ 0x  28   "*/
#define     LCD_BUF_9   9   /*"ƫ�Ƶ�ַ 0x  29   "*/
#define     LCD_BUF_10  10  /*"ƫ�Ƶ�ַ 0x  2A   "*/
#define     LCD_BUF_11  11  /*"ƫ�Ƶ�ַ 0x  2B   "*/
#define     LCD_BUF_12  12  /*"ƫ�Ƶ�ַ 0x  2C   "*/
#define     LCD_BUF_13  13  /*"ƫ�Ƶ�ַ 0x  2D   "*/
#define     LCD_BUF_14  14  /*"ƫ�Ƶ�ַ 0x  2E   "*/
#define     LCD_BUF_15  15  /*"ƫ�Ƶ�ַ 0x  2F   "*/
#define     LCD_BUF_16  16  /*"ƫ�Ƶ�ַ 0x  30   "*/
#define     LCD_BUF_17  17  /*"ƫ�Ƶ�ַ 0x  31   "*/
#define     LCD_BUF_18  18  /*"ƫ�Ƶ�ַ 0x  32   "*/
#define     LCD_BUF_19  19  /*"ƫ�Ƶ�ַ 0x  33   "*/
#define     LCD_BUF_20  20  /*"ƫ�Ƶ�ַ 0x  34   "*/
#define     LCD_BUF_21  21  /*"ƫ�Ƶ�ַ 0x  35   "*/
#define     LCD_BUF_22  22  /*"ƫ�Ƶ�ַ 0x  36   "*/
#define     LCD_BUF_23  23  /*"ƫ�Ƶ�ַ 0x  37   "*/
#define     LCD_BUF_24  24  /*"ƫ�Ƶ�ַ 0x  38   "*/
#define     LCD_BUF_25  25  /*"ƫ�Ƶ�ַ 0x  39   "*/
#define     LCD_BUF_26  26  /*"ƫ�Ƶ�ַ 0x  3A   "*/
#define     LCD_BUF_27  27  /*"ƫ�Ƶ�ַ 0x  3B   "*/
#define     LCD_BUF_28  28  /*"ƫ�Ƶ�ַ 0x  3C   "*/
#define     LCD_BUF_29  29  /*"ƫ�Ƶ�ַ 0x  3D   "*/
#define     LCD_BUF_30  30  /*"ƫ�Ƶ�ַ 0x  3E   "*/
#define     LCD_BUF_31  31  /*"ƫ�Ƶ�ַ 0x  3F   "*/
#define     LCD_BUF_32  32  /*"ƫ�Ƶ�ַ 0x  40   "*/
#define     LCD_BUF_33  33  /*"ƫ�Ƶ�ַ 0x  41   "*/
#define     LCD_BUF_34  34  /*"ƫ�Ƶ�ַ 0x  42   "*/
#define     LCD_BUF_35  35  /*"ƫ�Ƶ�ַ 0x  43   "*/
#define     LCD_BUF_36  36  /*"ƫ�Ƶ�ַ 0x  44   "*/
#define     LCD_BUF_37  37  /*"ƫ�Ƶ�ַ 0x  45   "*/

/* Exported enum ------------------------------------------------------------*/
typedef enum
{
    /*"���贮��ѹѡ�������ѹ"*/
    LCD_LDO2_70V    = 0x00,   /*"2.7V"*/
    LCD_LDO2_76V    = 0x01,   /*"2.76V"*/
    LCD_LDO2_82V    = 0x02,   /*"2.82V"*/
    LCD_LDO2_88V    = 0x03,   /*"2.88V"*/
    LCD_LDO2_94V    = 0x04,   /*"2.94V"*/
    LCD_LDO3_00V    = 0x05,   /*"3V"*/
    LCD_LDO3_06V    = 0x06,   /*"3.06V"*/
    LCD_LDO3_12V    = 0x07,   /*"3.12V"*/
    LCD_LDO3_18V    = 0x08,   /*"3.18V"*/
    LCD_LDO3_24V    = 0x09,   /*"3.18V"*/
    LCD_LDO3_30V    = 0x0a,   /*"3.30V"*/
    LCD_LDO3_36V    = 0x0b,   /*"3.36V"*/
    LCD_LDO3_42V    = 0x0c,   /*"3.42V"*/
    LCD_LDO3_48V    = 0x0d,   /*"3.48V"*/
    LCD_LDO3_54V    = 0x0e,   /*"3.54V"*/
    LCD_LDO3_60V    = 0x0f,   /*"3.60V"*/
} eLCD_LDO_V_TypeDef;

typedef enum
{
    LCD_ChargePmup      = 0x00, /*"Charge Pmup ��ʽ�ṩ LCD ƫ�õ�ѹ"*/
    LCD_ResistorDivid   = 0x01, /*"�ڲ����贮��ѹ��ʽ�ṩ LCD ƫ�õ�ѹ "*/

    LCD_Type_A      = 0x00, /*"Type A ����Ϊ�з�ת��ʽ������ 1 �� frame ��ʱ�������һ�����������Ľ���"*/
    LCD_Type_B      = 0x01, /*"Type B ����Ϊ֡��ת��ʽ������Ҫ�� 2 �� frame ��ʱ���ڲ������һ�����������Ľ��� "*/

    LCD_1_3BIAS     = 0x00, /*"1/3bias "*/
    LCD_1_4BIAS     = 0x01, /*"1/4bias "*/

    LCD_Static_DUTY = 0x00,/*"000����̬�����COM0��"*/
    LCD_1_2DUTY      = 0x01,/*"001�� 1/2 ռ�ձȣ�COM0~1��"*/
    LCD_1_3DUTY     = 0x02,/*"010�� 1/3 ռ�ձȣ�COM0~2��"*/
    LCD_1_4DUTY     = 0x03,/*"011�� 1/4 ռ�ձȣ�COM0~3��"*/
    LCD_1_6DUTY     = 0x04,/*"100�� 1/6 ռ�ձȣ�COM0~5��"*/
    LCD_1_8DUTY     = 0x05,/*"101�� 1/8 ռ�ձȣ�COM0~7��"*/

    LCD_CTL_EN      = 0x01,
    LCD_CTL_DIS = 0x00,
} eLCD_Ctl_TypeDef;

typedef union
{
    struct
    {
        uint32_t    LcdCtl_EN: 1;
        uint32_t    LcdCtl_DUTY: 3;
        uint32_t    LcdCtl_BIAS: 1;
        uint32_t    LcdCtl_BIASLVL: 6;
        uint32_t    LcdCtl_TYPE: 1;
        uint32_t    LcdCtl_PWD_PUMP: 1;
    };
    uint32_t gLCDCtl;
} uLCD_CtlPara_TypeDef;

/* Exported types ------------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void Rn8xxx_Lcd_Init(uLCD_CtlPara_TypeDef LCD_CtlPara, u16 LCD_Voltage);
extern void Rn8xxx_Lcd_ScrSet(uint8_t value, uint8_t len);
extern void Rn8xxx_Lcd_ScrCpy(uint8_t *buf, uint8_t len);
extern void Rn8xxx_Lcd_Close(void);

#endif
/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
