/****************************************************************************
* @file     GPIODrive.c
* @author   zhupeng
* @version  V1.0.0
* @date     2022.08.01
* @brief    GPIO驱动
******************************************************************************
* @attention    RA9701A
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _Rn8xxx_GPIO_H_
#define _Rn8xxx_GPIO_H_

#ifndef NULL
#define NULL          0
#endif
/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/
/*"****************************   GPIO定义    ****************************"*/
#define   _PIN0_Group           0x00
#define   _PIN1_Group           0x08
#define   _PIN2_Group           0x10
#define   _PIN3_Group           0x18
#define   _PIN4_Group           0x20
#define   _PIN5_Group           0x28
#define   _PIN6_Group           0x30
#define   _PIN7_Group           0x38
#define   _PIN8_Group           0x40
#define   _PIN9_Group           0x48
#define   _PIN10_Group          0x50
#define   _PIN11_Group          0x58
#define   _PIN12_Group          0x60
#define   _PIN13_Group          0x68
#define   _PIN14_Group          0x70

#define   _PINSegCom_Group      0x78
#define   _PIN_nMAX             _PINSegCom_Group+4
/*------------------------------------------------------------------------------------*/
#define     _PIN0_0 0   /*" _PIN0_Group + 0x00  "*/
#define     _PIN0_1 1   /*" _PIN0_Group + 0x01  "*/
#define     _PIN0_2 2   /*" _PIN0_Group + 0x02  "*/
#define     _PIN0_3 3   /*" _PIN0_Group + 0x03  "*/
#define     _PIN0_4 4   /*" _PIN0_Group + 0x04  "*/
#define     _PIN0_5 5   /*" _PIN0_Group + 0x05  "*/
#define     _PIN0_6 6   /*" _PIN0_Group + 0x06  "*/
#define     _PIN0_7 7   /*" _PIN0_Group + 0x07  "*/
#define     _PIN1_0 8   /*" _PIN1_Group + 0x00  "*/
#define     _PIN1_1 9   /*" _PIN1_Group + 0x01  "*/
#define     _PIN1_2 10  /*" _PIN1_Group + 0x02  "*/
#define     _PIN1_3 11  /*" _PIN1_Group + 0x03  "*/
#define     _PIN1_4 12  /*" _PIN1_Group + 0x04  "*/
#define     _PIN1_5 13  /*" _PIN1_Group + 0x05  "*/
#define     _PIN1_6 14  /*" _PIN1_Group + 0x06  "*/
#define     _PIN1_7 15  /*" _PIN1_Group + 0x07  "*/
#define     _PIN2_0 16  /*" _PIN2_Group + 0x00  "*/
#define     _PIN2_1 17  /*" _PIN2_Group + 0x01  "*/
#define     _PIN2_2 18  /*" _PIN2_Group + 0x02  "*/
#define     _PIN2_3 19  /*" _PIN2_Group + 0x03  "*/
#define     _PIN2_4 20  /*" _PIN2_Group + 0x04  "*/
#define     _PIN2_5 21  /*" _PIN2_Group + 0x05  "*/
#define     _PIN2_6 22  /*" _PIN2_Group + 0x06  "*/
#define     _PIN2_7 23  /*" _PIN2_Group + 0x07  "*/
#define     _PIN3_0 24  /*" _PIN3_Group + 0x00  "*/
#define     _PIN3_1 25  /*" _PIN3_Group + 0x01  "*/
#define     _PIN3_2 26  /*" _PIN3_Group + 0x02  "*/
#define     _PIN3_3 27  /*" _PIN3_Group + 0x03  "*/
#define     _PIN3_4 28  /*" _PIN3_Group + 0x04  "*/
#define     _PIN3_5 29  /*" _PIN3_Group + 0x05  "*/
#define     _PIN3_6 30  /*" _PIN3_Group + 0x06  "*/
#define     _PIN3_7 31  /*" _PIN3_Group + 0x07  "*/
#define     _PIN4_0 32  /*" _PIN4_Group + 0x00  "*/
#define     _PIN4_1 33  /*" _PIN4_Group + 0x01  "*/
#define     _PIN4_2 34  /*" _PIN4_Group + 0x02  "*/
#define     _PIN4_3 35  /*" _PIN4_Group + 0x03  "*/
#define     _PIN4_4 36  /*" _PIN4_Group + 0x04  "*/
#define     _PIN4_5 37  /*" _PIN4_Group + 0x05  "*/
#define     _PIN4_6 38  /*" _PIN4_Group + 0x06  "*/
#define     _PIN4_7 39  /*" _PIN4_Group + 0x07  "*/
#define     _PIN5_0 40  /*" _PIN5_Group + 0x00  "*/
#define     _PIN5_1 41  /*" _PIN5_Group + 0x01  "*/
#define     _PIN5_2 42  /*" _PIN5_Group + 0x02  "*/
#define     _PIN5_3 43  /*" _PIN5_Group + 0x03  "*/
#define     _PIN5_4 44  /*" _PIN5_Group + 0x04  "*/
#define     _PIN5_5 45  /*" _PIN5_Group + 0x05  "*/
#define     _PIN5_6 46  /*" _PIN5_Group + 0x06  当VCC无电，VBAT初次上电时，P56默认输出1HZ。"*/
#define     _PIN5_7 47  /*" _PIN5_Group + 0x07  "*/
#define     _PIN6_0 48  /*" _PIN6_Group + 0x00  "*/
#define     _PIN6_1 49  /*" _PIN6_Group + 0x01  "*/
#define     _PIN6_2 50  /*" _PIN6_Group + 0x02  "*/
#define     _PIN6_3 51  /*" _PIN6_Group + 0x03  "*/
#define     _PIN6_4 52  /*" _PIN6_Group + 0x04  "*/
#define     _PIN6_5 53  /*" _PIN6_Group + 0x05  "*/
#define     _PIN6_6 54  /*" _PIN6_Group + 0x06  "*/
#define     _PIN6_7 55  /*" _PIN6_Group + 0x07  "*/
#define     _PIN7_0 56  /*" _PIN7_Group + 0x00  "*/
#define     _PIN7_1 57  /*" _PIN7_Group + 0x01  "*/
#define     _PIN7_2 58  /*" _PIN7_Group + 0x02  "*/
#define     _PIN7_3 59  /*" _PIN7_Group + 0x03  "*/
#define     _PIN7_4 60  /*" _PIN7_Group + 0x04  "*/
#define     _PIN7_5 61  /*" _PIN7_Group + 0x05  "*/
#define     _PIN7_6 62  /*" _PIN7_Group + 0x06  "*/
#define     _PIN7_7 63  /*" _PIN7_Group + 0x07  "*/
#define     _PIN8_0 64  /*" _PIN8_Group + 0x00  "*/
#define     _PIN8_1 65  /*" _PIN8_Group + 0x01  "*/
#define     _PIN8_2 66  /*" _PIN8_Group + 0x02  "*/
#define     _PIN8_3 67  /*" _PIN8_Group + 0x03  "*/
#define     _PIN8_4 68  /*" _PIN8_Group + 0x04  "*/
#define     _PIN8_5 69  /*" _PIN8_Group + 0x05  "*/
#define     _PIN8_6 70  /*" _PIN8_Group + 0x06  "*/
#define     _PIN8_7 71  /*" _PIN8_Group + 0x07  "*/
#define     _PIN9_0 72  /*" _PIN9_Group + 0x00  "*/
#define     _PIN9_1 73  /*" _PIN9_Group + 0x01  "*/
#define     _PIN9_2 74  /*" _PIN9_Group + 0x02  "*/
#define     _PIN9_3 75  /*" _PIN9_Group + 0x03  "*/
#define     _PIN9_4 76  /*" _PIN9_Group + 0x04  "*/
#define     _PIN9_5 77  /*" _PIN9_Group + 0x05  "*/
#define     _PIN9_6 78  /*" _PIN9_Group + 0x06  "*/
#define     _PIN9_7 79  /*" _PIN9_Group + 0x07  "*/
#define     _PIN10_0    80  /*" _PIN10_Group + 0x00 "*/
#define     _PIN10_1    81  /*" _PIN10_Group + 0x01 "*/
#define     _PIN10_2    82  /*" _PIN10_Group + 0x02 "*/
#define     _PIN10_3    83  /*" _PIN10_Group + 0x03 "*/
#define     _PIN10_4    84  /*" _PIN10_Group + 0x04 "*/
#define     _PIN10_5    85  /*" _PIN10_Group + 0x05 "*/
#define     _PIN10_6    86  /*" _PIN10_Group + 0x06 "*/
#define     _PIN10_7    87  /*" _PIN10_Group + 0x07 "*/
#define     _PIN11_0    88  /*" _PIN11_Group + 0x00 "*/
#define     _PIN11_1    89  /*" _PIN11_Group + 0x01 "*/
#define     _PIN11_2    90  /*" _PIN11_Group + 0x02 "*/
#define     _PIN11_3    91  /*" _PIN11_Group + 0x03 "*/
#define     _PIN11_4    92  /*" _PIN11_Group + 0x04 "*/
#define     _PIN11_5    93  /*" _PIN11_Group + 0x05 "*/
#define     _PIN11_6    94  /*" _PIN11_Group + 0x06 "*/
#define     _PIN11_7    95  /*" _PIN11_Group + 0x07 "*/
#define     _PIN12_0    96  /*" _PIN12_Group + 0x00 "*/
#define     _PIN12_1    97  /*" _PIN12_Group + 0x01 "*/
#define     _PIN12_2    98  /*" _PIN12_Group + 0x02 "*/
#define     _PIN12_3    99  /*" _PIN12_Group + 0x03 "*/
#define     _PIN12_4    100 /*" _PIN12_Group + 0x04 "*/
#define     _PIN12_5    101 /*" _PIN12_Group + 0x05 "*/
#define     _PIN12_6    102 /*" _PIN12_Group + 0x06 "*/
#define     _PIN12_7    103 /*" _PIN12_Group + 0x07 "*/
#define     _PIN13_0    104 /*" _PIN13_Group + 0x00 "*/
#define     _PIN13_1    105 /*" _PIN13_Group + 0x01 "*/
#define     _PIN13_2    106 /*" _PIN13_Group + 0x02 "*/
#define     _PIN13_3    107 /*" _PIN13_Group + 0x03 "*/
#define     _PIN13_4    108 /*" _PIN13_Group + 0x04 "*/
#define     _PIN13_5    109 /*" _PIN13_Group + 0x05 "*/
#define     _PIN13_6    110 /*" _PIN13_Group + 0x06 "*/
#define     _PIN13_7    111 /*" _PIN13_Group + 0x07 "*/
#define     _PIN14_0    112 /*" _PIN14_Group + 0x00 "*/
#define     _PIN14_1    113 /*" _PIN14_Group + 0x01 "*/
#define     _PIN14_2    114 /*" _PIN14_Group + 0x02 "*/
#define     _PIN14_3    115 /*" _PIN14_Group + 0x03 "*/
#define     _PIN14_4    116 /*" _PIN14_Group + 0x04 "*/
#define     _PIN14_5    117 /*" _PIN14_Group + 0x05 "*/
#define     _PIN14_6    118 /*" _PIN14_Group + 0x06 "*/
#define     _PIN14_7    119 /*" _PIN14_Group + 0x07 "*/

/*"SEGCOM 口ID定义"*/
#define   _PIN_Seg0Com4        _PINSegCom_Group+0x00
#define   _PIN_Seg1Com5        _PINSegCom_Group+0x01
#define   _PIN_Seg2Com6        _PINSegCom_Group+0x02
#define   _PIN_Seg3Com7        _PINSegCom_Group+0x03

/* Exported enum ------------------------------------------------------------*/

/*"GPIO方向选择"*/
typedef enum
{
    GPIO_MODE_OUT   = 0,
    GPIO_MODE_IN    = 1,
    GPIO_MODE_NORMAL = 2, /*"输入不使能;不使用的IO口配置为此模式"*/
} eGPIODir_TypeDef;

/*"GPIO模式选择"*/
typedef enum
{
    NORMAL_IN       = 0x00,      /*"普通模式输入，即CMOS输入缓冲器类型"*/
    TTL_IN          = 0x02,     /*"TTL输入缓冲器类型"*/
    NORMAL_OUT      = 0x03,     /*"普通模式输出"*/
    N_OPENDRAIN_OUT = 0x04     /*"N通道漏极开路模式输出"*/
} eGPIOMode_TypeDef;

/*"GPIO上拉选择"*/
typedef enum
{
    Pull_ON     = 0x01,      /*"选择上拉"*/
    Pull_OFF    = 0x00,      /*"选择上拉"*/
} eGPIOPull_TypeDef;

typedef enum
{
    _NORMALIO   = 1,
    _POSC,           /*"时钟"*/
    _SWD,
    _UART0,
    _UART1,
    _UART2,
    _UART3,
    _UART4,
    _UART5,
    _IIC,
    //_SPI          ,//SPI0,SPI1,SPIS,SPI3,SPI4,
    _SPI0,
    _SPI1,
    _SPI2,
    _SPI3,

    _ISO7816,

    _TC_IN,
    _TC_OUT,
    _TC0_N_1,
    _TC0_P_1,
    _TC1_N_0,
    _TC1_P_0,
    _TC1_N_1,
    _TC1_P_1,

    _RTC_OUT,
    _RTC_1S,

    _KEY,
    _INTRUPT,        //INT0,INT1,INT2,INT3,INT4,INT5,INT6,INT7,

    _SF_OUT,         /*"视在电能脉冲输出"*/
    _PF,             /*"计量芯片脉冲输出口"*/
    _QF,             /*"计量芯片脉冲输出口"*/
    _SF1,            /*"计量芯片脉冲输入口"*/
    _SF2,            /*"计量芯片脉冲输入口"*/
    _CF0,                /*"电能积分模块D2F的输出CF0"*/
    _CF1,                /*"电能积分模块D2F的输出CF1"*/
    _CF2,                /*"电能积分模块D2F的输出CF2"*/

    _ZXOUT,

    _AIN,            //SDAIN,AIN
    _CMP2,
    _CTSWO,
    _CTCMPA,
    _CTCMPB,
    _CTCMPC,

    _LCD,            /*"gpio口配置为SEG口时使用此模式"*/
    _LCDV,           /*"gpio口LCDVA, LCDVB, LCDVC, LCDVD, LCDVP1, LCDVP2"*/
    _SEG,            /*"SEG/COM口配置为SEG口时使用此模式"*/
    _COM,            /*"SEG/COM口配置为COM口时使用此模式"*/
} eGPIOFunction_TypeDef;

typedef enum
{
    _bit0           = 0x00,
    _bit1           = 0x01,
    _bit2           = 0x02,
    _bit3           = 0x03,
    _bit4           = 0x04,
    _bit5           = 0x05,
    _bit6           = 0x06,
    _bit7           = 0x07,

    _bit8           = 0x08,
    _bit9           = 0x09,
    _bit10          = 0x0a,
    _bit11          = 0x0b,
    _bit12          = 0x0c,
    _bit13          = 0x0d,
    _bit14          = 0x0e,
    _bit15          = 0x0f,

    _bit16          = 0x10,
    _bit17          = 0x11,
    _bit18          = 0x12,
    _bit19          = 0x13,
    _bit20          = 0x14,
    _bit21          = 0x15,
    _bit22          = 0x16,
    _bit23          = 0x17,

    _bit24          = 0x18,
    _bit25          = 0x19,
    _bit26          = 0x1a,
    _bit27          = 0x1b,
    _bit28          = 0x1c,
    _bit29          = 0x1d,
    _bit30          = 0x1e,
    _bit31          = 0x1f
} eGPIOBitNumber_TypeDef;

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint8_t                 pin_id;
    eGPIOFunction_TypeDef   GpioFun;
    uint32_t                *RegAd;
    eGPIOBitNumber_TypeDef  starNum;
    uint8_t                 nbit;
    uint8_t                 PutData;

    uint32_t                *RegAd_2;
    eGPIOBitNumber_TypeDef  starNum_2;
    uint8_t                 nbit_2;
    uint8_t                 PutData_2;
} sGPIOFunFile_TypeDef;

/* Exported data  ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void Rn8xxx_GPIO_SetPin(uint8_t pin_id, uint8_t value);
extern uint8_t Rn8xxx_GPIO_ReadPin(uint8_t pin_id);
extern void Rn8xxx_GPIO_OverturnPin(uint8_t pin_id);
extern void Rn8xxx_GPIO_CfgPullMode(uint8_t pin_id, eGPIOPull_TypeDef mode);
extern void Rn8xxx_GPIO_CfgIOMode(uint8_t pin_id, eGPIODir_TypeDef dir, eGPIOMode_TypeDef mode);
extern ErrorStatus Rn8xxx_GPIO_CfgFun(uint8_t pin_id, eGPIOFunction_TypeDef Fun);

#endif

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
