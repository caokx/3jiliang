/****************************************************************************
* @file     GPIODrive.c
* @author   zhupeng
* @version  V1.1.1
* @date     2022.08.01
* @brief    GPIO����
******************************************************************************
* @attention    RA9701A
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include <Rn8xxx_Gpio.h>
#include <Rn8xxx_GpioRegMap.h>

/* Private define ------------------------------------------------------------*/
#ifndef NULL
#define NULL          0
#endif

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/
const sGPIOFunFile_TypeDef  GpioFunFile[] =
{
    /*"****************************************************Group0*********************************************************************"*/
    {_PIN0_0,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit0,  2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN0_0,   _AIN, (uint32_t *) &GPIO->PCA0,    _bit0,  2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN0_0,   _KEY, (uint32_t *) &GPIO->PCA0,    _bit0,  2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN0_0,   _UART2, (uint32_t *) &GPIO->PCA0,    _bit0,  2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN0_1,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit2,  2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN0_1,   _AIN, (uint32_t *) &GPIO->PCA0,    _bit2,  2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN0_1,   _KEY, (uint32_t *) &GPIO->PCA0,    _bit2,  2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN0_1,   _UART2, (uint32_t *) &GPIO->PCA0,    _bit2,  2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN0_2,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit4,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN0_2,   _AIN, (uint32_t *) &GPIO->PCA0,    _bit4,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN0_3,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit5,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN0_3,   _AIN, (uint32_t *) &GPIO->PCA0,    _bit5,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN0_4,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit6,  1,  0x00, (uint32_t *) &GPIO->PCA0,    _bit8,  1,      0x00},
    {_PIN0_4,   _AIN, (uint32_t *) &GPIO->PCA0,    _bit6,  1,  0x01, (uint32_t *) &GPIO->PCA0,    _bit8,  1,      0x00},
    {_PIN0_4,   _KEY, (uint32_t *) &GPIO->PCA0,    _bit6,  1,  0x00, (uint32_t *) &GPIO->PCA0,    _bit8,  1,      0x01},

    {_PIN0_5,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit7,  1,  0x00,   NULL,                       _bit0,  NULL,   0x00},
    {_PIN0_5,   _AIN, (uint32_t *) &GPIO->PCA0,    _bit7,  1,  0x01,   NULL,                       _bit0,  NULL,   0x00},
    /*"****************************************************Group1*********************************************************************"*/
    {_PIN1_0,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit9,  2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_0,   _KEY, (uint32_t *) &GPIO->PCA0,    _bit9,  2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_0,   _TC_OUT, (uint32_t *) &GPIO->PCA0,    _bit9,  2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_0,   _TC_IN, (uint32_t *) &GPIO->PCA0,    _bit9,  2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN1_1,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit11, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_1,   _KEY, (uint32_t *) &GPIO->PCA0,    _bit11, 2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_1,   _TC_OUT, (uint32_t *) &GPIO->PCA0,    _bit11, 2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_1,   _TC_IN, (uint32_t *) &GPIO->PCA0,    _bit11, 2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN1_2,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit13, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_2,   _KEY, (uint32_t *) &GPIO->PCA0,    _bit13, 2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_2,   _TC_OUT, (uint32_t *) &GPIO->PCA0,    _bit13, 2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_2,   _TC_IN, (uint32_t *) &GPIO->PCA0,    _bit13, 2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN1_3,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit15, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_3,   _KEY, (uint32_t *) &GPIO->PCA0,    _bit15, 2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_3,   _TC_OUT, (uint32_t *) &GPIO->PCA0,    _bit15, 2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_3,   _TC_IN, (uint32_t *) &GPIO->PCA0,    _bit15, 2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN1_4,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit17, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_4,   _KEY, (uint32_t *) &GPIO->PCA0,    _bit17, 2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_4,   _TC_OUT, (uint32_t *) &GPIO->PCA0,    _bit17, 2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_4,   _TC_IN, (uint32_t *) &GPIO->PCA0,    _bit17, 2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN1_5,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit19, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_5,   _KEY, (uint32_t *) &GPIO->PCA0,    _bit19, 2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_5,   _TC_OUT, (uint32_t *) &GPIO->PCA0,    _bit19, 2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_5,   _TC_IN, (uint32_t *) &GPIO->PCA0,    _bit19, 2,  0x03,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_6,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit21, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_6,   _KEY, (uint32_t *) &GPIO->PCA0,    _bit21, 2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_6,   _TC_OUT, (uint32_t *) &GPIO->PCA0,    _bit21, 2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_6,   _TC_IN, (uint32_t *) &GPIO->PCA0,    _bit21, 2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN1_7,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit23, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_7,   _KEY, (uint32_t *) &GPIO->PCA0,    _bit23, 2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_7,   _TC_OUT, (uint32_t *) &GPIO->PCA0,    _bit23, 2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN1_7,   _TC_IN, (uint32_t *) &GPIO->PCA0,    _bit23, 2,  0x03,   NULL,                       _bit0,  NULL,   NULL},
    /*"****************************************************Group2*********************************************************************"*/
    {_PIN2_0,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit25, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN2_0,   _UART0, (uint32_t *) &GPIO->PCA0,    _bit25, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN2_1,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit25, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN2_1,   _UART0, (uint32_t *) &GPIO->PCA0,    _bit25, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN2_2,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit26, 1,  0x00, (uint32_t *) &GPIO->PCA1,    _bit16, 1,      0x00},
    {_PIN2_2,   _UART1, (uint32_t *) &GPIO->PCA0,    _bit26, 1,  0x01, (uint32_t *) &GPIO->PCA1,    _bit16, 1,      0x00},
    {_PIN2_2,   _UART2, (uint32_t *) &GPIO->PCA0,    _bit26, 1,  0x00, (uint32_t *) &GPIO->PCA1,    _bit16, 1,      0x01},

    {_PIN2_3,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit26, 1,  0x00, (uint32_t *) &GPIO->PCA1,    _bit16, 1,      0x00},
    {_PIN2_3,   _UART1, (uint32_t *) &GPIO->PCA0,    _bit26, 1,  0x01, (uint32_t *) &GPIO->PCA1,    _bit16, 1,      0x00},
    {_PIN2_3,   _UART2, (uint32_t *) &GPIO->PCA0,    _bit26, 1,  0x00, (uint32_t *) &GPIO->PCA1,    _bit16, 1,      0x01},

    {_PIN2_4,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit27, 1,  0x00, (uint32_t *) &GPIO->PCA0,    _bit29, 1,      0x00},
    {_PIN2_4,   _UART2, (uint32_t *) &GPIO->PCA0,    _bit27, 1,  0x01, (uint32_t *) &GPIO->PCA0,    _bit29, 2,      0x00},
    {_PIN2_4,   _SWD, (uint32_t *) &GPIO->PCA0,    _bit27, 1,  0x00, (uint32_t *) &GPIO->PCA0,    _bit29, 1,      0x01},

    {_PIN2_5,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit27, 1,  0x00, (uint32_t *) &GPIO->PCA0,    _bit29, 1,      0x00},
    {_PIN2_5,   _UART2, (uint32_t *) &GPIO->PCA0,    _bit27, 1,  0x01, (uint32_t *) &GPIO->PCA0,    _bit29, 2,      0x00},
    {_PIN2_5,   _SWD, (uint32_t *) &GPIO->PCA0,    _bit27, 1,  0x00, (uint32_t *) &GPIO->PCA0,    _bit29, 1,      0x01},

    {_PIN2_6,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit28, 1,  0x00, (uint32_t *) &GPIO->PCA1,    _bit17, 1,      0x00},
    {_PIN2_6,   _UART3, (uint32_t *) &GPIO->PCA0,    _bit28, 1,  0x01, (uint32_t *) &GPIO->PCA1,    _bit17, 1,      0x00},
    {_PIN2_6,   _UART2, (uint32_t *) &GPIO->PCA0,    _bit28, 1,  0x00, (uint32_t *) &GPIO->PCA1,    _bit17, 1,      0x01},

    {_PIN2_7,   _NORMALIO, (uint32_t *) &GPIO->PCA0,    _bit28, 1,  0x00, (uint32_t *) &GPIO->PCA1,    _bit17, 1,      0x00},
    {_PIN2_7,   _UART3, (uint32_t *) &GPIO->PCA0,    _bit28, 1,  0x01, (uint32_t *) &GPIO->PCA1,    _bit17, 1,      0x00},
    {_PIN2_7,   _UART2, (uint32_t *) &GPIO->PCA0,    _bit28, 1,  0x00, (uint32_t *) &GPIO->PCA1,    _bit17, 1,      0x01},
    /*"****************************************************Group3*********************************************************************"*/
    {_PIN3_0,   _NORMALIO, (uint32_t *) &GPIO->PCA1,    _bit0,  2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_0,   _INTRUPT, (uint32_t *) &GPIO->PCA1,    _bit0,  2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_0,   _TC_IN, (uint32_t *) &GPIO->PCA1,    _bit0,  2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_0,   _UART4, (uint32_t *) &GPIO->PCA1,    _bit0,  2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN3_1,   _NORMALIO, (uint32_t *) &GPIO->PCA1,    _bit2,  2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_1,   _INTRUPT, (uint32_t *) &GPIO->PCA1,    _bit2,  2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_1,   _TC_IN, (uint32_t *) &GPIO->PCA1,    _bit2,  2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_1,   _UART4, (uint32_t *) &GPIO->PCA1,    _bit2,  2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN3_2,   _NORMALIO, (uint32_t *) &GPIO->PCA1,    _bit4,  2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_2,   _INTRUPT, (uint32_t *) &GPIO->PCA1,    _bit4,  2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_2,   _RTC_OUT, (uint32_t *) &GPIO->PCA1,    _bit4,  2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_2,   _KEY, (uint32_t *) &GPIO->PCA1,    _bit4,  2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN3_3,   _NORMALIO, (uint32_t *) &GPIO->PCA1,    _bit6,  2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_3,   _INTRUPT, (uint32_t *) &GPIO->PCA1,    _bit6,  2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_3,   _TC_IN, (uint32_t *) &GPIO->PCA1,    _bit6,  2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_3,   _CF0, (uint32_t *) &GPIO->PCA1,    _bit6,  2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN3_4,   _NORMALIO, (uint32_t *) &GPIO->PCA1,    _bit8,  2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_4,   _INTRUPT, (uint32_t *) &GPIO->PCA1,    _bit8,  2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_4,   _SF_OUT, (uint32_t *) &GPIO->PCA1,    _bit8,  2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_4,   _CF1, (uint32_t *) &GPIO->PCA1,    _bit8,  2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN3_5,   _NORMALIO, (uint32_t *) &GPIO->PCA1,    _bit10, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_5,   _INTRUPT, (uint32_t *) &GPIO->PCA1,    _bit10, 2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_5,   _TC_IN, (uint32_t *) &GPIO->PCA1,    _bit10, 2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_5,   _CF2, (uint32_t *) &GPIO->PCA1,    _bit10, 2,  0x03,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN3_6,   _NORMALIO, (uint32_t *) &GPIO->PCA1,    _bit12, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_6,   _INTRUPT, (uint32_t *) &GPIO->PCA1,    _bit12, 2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_6,   _POSC, (uint32_t *) &GPIO->PCA1,    _bit12, 2,  0x02,   NULL,                       _bit0,  NULL,   NULL},

    {_PIN3_7,   _NORMALIO, (uint32_t *) &GPIO->PCA1,    _bit14, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_7,   _INTRUPT, (uint32_t *) &GPIO->PCA1,    _bit14, 2,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN3_7,   _POSC, (uint32_t *) &GPIO->PCA1,    _bit14, 2,  0x02,   NULL,                       _bit0,  NULL,   NULL},
    /*"****************************************************Group4*********************************************************************"*/
    {_PIN4_0,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit0,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit0,  2,      0x00},
    {_PIN4_0,   _ISO7816, (uint32_t *) &GPIO->PCB,     _bit0,  1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit0,  2,      0x00},
    {_PIN4_0,   _INTRUPT, (uint32_t *) &GPIO->PCB,     _bit0,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit0,  2,      0x01},
    {_PIN4_0,   _SPI1, (uint32_t *) &GPIO->PCB,     _bit0,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit0,  2,      0x02},
    {_PIN4_0,   _SPI2, (uint32_t *) &GPIO->PCB,     _bit0,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit0,  2,      0x03},

    {_PIN4_1,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit1,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit2,  2,      0x00},
    {_PIN4_1,   _ISO7816, (uint32_t *) &GPIO->PCB,     _bit1,  1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit2,  2,      0x00},
    {_PIN4_1,   _INTRUPT, (uint32_t *) &GPIO->PCB,     _bit1,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit2,  2,      0x01},
    {_PIN4_1,   _SPI1, (uint32_t *) &GPIO->PCB,     _bit1,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit2,  2,      0x02},
    {_PIN4_1,   _SPI2, (uint32_t *) &GPIO->PCB,     _bit1,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit2,  2,      0x03},

    {_PIN4_2,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit2,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit4,  2,      0x00},
    {_PIN4_2,   _ISO7816, (uint32_t *) &GPIO->PCB,     _bit2,  1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit4,  2,      0x00},
    {_PIN4_2,   _INTRUPT, (uint32_t *) &GPIO->PCB,     _bit2,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit4,  2,      0x01},
    {_PIN4_2,   _SPI1, (uint32_t *) &GPIO->PCB,     _bit2,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit4,  2,      0x02},
    {_PIN4_2,   _SPI2, (uint32_t *) &GPIO->PCB,     _bit2,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit4,  2,      0x03},

    {_PIN4_3,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit3,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit6,  2,      0x00},
    {_PIN4_3,   _ISO7816, (uint32_t *) &GPIO->PCB,     _bit3,  1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit6,  2,      0x00},
    {_PIN4_3,   _INTRUPT, (uint32_t *) &GPIO->PCB,     _bit3,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit6,  2,      0x01},
    {_PIN4_3,   _SPI1, (uint32_t *) &GPIO->PCB,     _bit3,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit6,  2,      0x02},
    {_PIN4_3,   _SPI2, (uint32_t *) &GPIO->PCB,     _bit3,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit6,  2,      0x03},

    {_PIN4_4,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit4,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit8,  2,      0x00},
    /*"�����Դ�����𣬴˸��ò�����ʹ�ã���ѡP51/P50����Ϊ�˹��ܣ�"*/
    {_PIN4_4,   _SPI0, (uint32_t *) &GPIO->PCB,     _bit4,  1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit8,  2,      0x00},
    {_PIN4_4,   _KEY, (uint32_t *) &GPIO->PCB,     _bit4,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit8,  2,      0x01},
    {_PIN4_4,   _AIN, (uint32_t *) &GPIO->PCB,     _bit4,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit8,  2,      0x02},

    {_PIN4_5,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit5,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit10, 2,      0x00},
    /*"�����Դ�����𣬴˸��ò�����ʹ�ã���ѡP51/P50����Ϊ�˹��ܣ�"*/
    {_PIN4_5,   _SPI0, (uint32_t *) &GPIO->PCB,     _bit5,  1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit10, 2,      0x00},
    {_PIN4_5,   _KEY, (uint32_t *) &GPIO->PCB,     _bit5,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit10, 2,      0x01},
    {_PIN4_5,   _AIN, (uint32_t *) &GPIO->PCB,     _bit5,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit10, 2,      0x02},

    {_PIN4_6,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit6,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit12, 2,      0x00},
    {_PIN4_6,   _SPI0, (uint32_t *) &GPIO->PCB,     _bit6,  1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit12, 2,      0x00},
    {_PIN4_6,   _UART4, (uint32_t *) &GPIO->PCB,     _bit6,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit12, 2,      0x01},
    {_PIN4_6,   _CF1, (uint32_t *) &GPIO->PCB,     _bit6,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit12, 2,      0x02},
    {_PIN4_6,   _CF2, (uint32_t *) &GPIO->PCB,     _bit6,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit12, 2,      0x03},

    {_PIN4_7,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit7,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit14, 2,      0x00},
    {_PIN4_7,   _SPI0, (uint32_t *) &GPIO->PCB,     _bit7,  1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit14, 2,      0x00},
    {_PIN4_7,   _UART4, (uint32_t *) &GPIO->PCB,     _bit7,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit14, 2,      0x01},
    {_PIN4_7,   _CF0, (uint32_t *) &GPIO->PCB,     _bit7,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit14, 2,      0x02},
    {_PIN4_7,   _CF1, (uint32_t *) &GPIO->PCB,     _bit7,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit14, 2,      0x03},
    /*"****************************************************Group5*********************************************************************"*/
    {_PIN5_0,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit8,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit16, 2,      0x00},
    {_PIN5_0,   _PF, (uint32_t *) &GPIO->PCB,     _bit8,  1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit16, 2,      0x00},
    {_PIN5_0,   _RTC_OUT, (uint32_t *) &GPIO->PCB,     _bit8,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit16, 2,      0x01},
    {_PIN5_0,   _SPI0, (uint32_t *) &GPIO->PCB,     _bit8,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit16, 2,      0x02},
    {_PIN5_0,   _SF1, (uint32_t *) &GPIO->PCB,     _bit8,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit16, 2,      0x03},

    {_PIN5_1,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit9,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit18, 2,      0x00},
    {_PIN5_1,   _QF, (uint32_t *) &GPIO->PCB,     _bit9,  1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit18, 2,      0x00},
    {_PIN5_1,   _RTC_OUT, (uint32_t *) &GPIO->PCB,     _bit9,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit18, 2,      0x01},
    {_PIN5_1,   _SPI0, (uint32_t *) &GPIO->PCB,     _bit9,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit18, 2,      0x02},
    {_PIN5_1,   _SF2, (uint32_t *) &GPIO->PCB,     _bit9,  1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit18, 2,      0x03},

    {_PIN5_2,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit10, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit20, 2,      0x00},
    {_PIN5_2,   _IIC, (uint32_t *) &GPIO->PCB,     _bit10, 1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit20, 2,      0x00},
    {_PIN5_2,   _TC_IN, (uint32_t *) &GPIO->PCB,     _bit10, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit20, 2,      0x01},
    {_PIN5_2,   _TC0_N_1, (uint32_t *) &GPIO->PCB,     _bit10, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit20, 2,      0x02},
    {_PIN5_2,   _SPI1, (uint32_t *) &GPIO->PCB,     _bit10, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit20, 2,      0x03},

    {_PIN5_3,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit11, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit22, 2,      0x00},
    {_PIN5_3,   _IIC, (uint32_t *) &GPIO->PCB,     _bit11, 1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit22, 2,      0x00},
    {_PIN5_3,   _TC_IN, (uint32_t *) &GPIO->PCB,     _bit11, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit22, 2,      0x01},
    {_PIN5_3,   _TC0_P_1, (uint32_t *) &GPIO->PCB,     _bit11, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit22, 2,      0x02},
    {_PIN5_3,   _SPI1, (uint32_t *) &GPIO->PCB,     _bit11, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit22, 2,      0x03},

    {_PIN5_4,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit12, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit24, 2,      0x00},
    {_PIN5_4,   _UART5, (uint32_t *) &GPIO->PCB,     _bit12, 1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit24, 2,      0x00},
    {_PIN5_4,   _TC_IN, (uint32_t *) &GPIO->PCB,     _bit12, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit24, 2,      0x01},
    {_PIN5_4,   _TC1_N_0, (uint32_t *) &GPIO->PCB,     _bit12, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit24, 2,      0x02},
    {_PIN5_4,   _SPI1, (uint32_t *) &GPIO->PCB,     _bit12, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit24, 2,      0x03},

    {_PIN5_5,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit13, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit26, 2,      0x00},
    {_PIN5_5,   _UART5, (uint32_t *) &GPIO->PCB,     _bit13, 1,  0x01, (uint32_t *) &GPIO->PCB2,    _bit26, 2,      0x00},
    {_PIN5_5,   _TC_IN, (uint32_t *) &GPIO->PCB,     _bit13, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit26, 2,      0x01},
    {_PIN5_5,   _TC1_P_0, (uint32_t *) &GPIO->PCB,     _bit13, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit26, 2,      0x02},
    {_PIN5_5,   _SPI1, (uint32_t *) &GPIO->PCB,     _bit13, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit26, 2,      0x03},

    {_PIN5_6,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit14, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit28, 2,      0x00},
    {_PIN5_6,   _TC_IN, (uint32_t *) &GPIO->PCB,     _bit14, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit28, 2,      0x01},
    {_PIN5_6,   _TC1_N_1, (uint32_t *) &GPIO->PCB,     _bit14, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit28, 2,      0x02},
    /*"_RTC_OUT  P56����Ϊ��ͨIO����RTCģ������"*/
    {_PIN5_6,   _RTC_OUT, (uint32_t *) &GPIO->PCB,     _bit14, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit28, 2,      0x00},

    {_PIN5_7,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit15, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit30, 2,      0x00},
    {_PIN5_7,   _TC_IN, (uint32_t *) &GPIO->PCB,     _bit15, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit30, 2,      0x01},
    {_PIN5_7,   _TC1_N_1, (uint32_t *) &GPIO->PCB,     _bit15, 1,  0x00, (uint32_t *) &GPIO->PCB2,    _bit30, 2,      0x02},
    /*"****************************************************Group6*********************************************************************"*/
    {_PIN6_0,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit16, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_0,   _LCD, (uint32_t *) &GPIO->PCB,     _bit16, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_1,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit17, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_1,   _LCD, (uint32_t *) &GPIO->PCB,     _bit17, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_2,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit18, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_2,   _LCD, (uint32_t *) &GPIO->PCB,     _bit18, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_3,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit19, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_3,   _LCD, (uint32_t *) &GPIO->PCB,     _bit19, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_4,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit20, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_4,   _LCD, (uint32_t *) &GPIO->PCB,     _bit20, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_5,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit21, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_5,   _LCD, (uint32_t *) &GPIO->PCB,     _bit21, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_6,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit22, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_6,   _LCD, (uint32_t *) &GPIO->PCB,     _bit22, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_7,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit23, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN6_7,   _LCD, (uint32_t *) &GPIO->PCB,     _bit23, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    /*"****************************************************Group7*********************************************************************"*/
    {_PIN7_0,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit24, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_0,   _LCD, (uint32_t *) &GPIO->PCB,     _bit24, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_1,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit25, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_1,   _LCD, (uint32_t *) &GPIO->PCB,     _bit25, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_2,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit26, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_2,   _LCD, (uint32_t *) &GPIO->PCB,     _bit26, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_3,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit27, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_3,   _LCD, (uint32_t *) &GPIO->PCB,     _bit27, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_4,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit28, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_4,   _LCD, (uint32_t *) &GPIO->PCB,     _bit28, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_5,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit29, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_5,   _LCD, (uint32_t *) &GPIO->PCB,     _bit29, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_6,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit30, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_6,   _LCD, (uint32_t *) &GPIO->PCB,     _bit30, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_7,   _NORMALIO, (uint32_t *) &GPIO->PCB,     _bit31, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN7_7,   _LCD, (uint32_t *) &GPIO->PCB,     _bit31, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    /*"****************************************************Group8*********************************************************************"*/
    {_PIN8_0,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit0,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_0,   _LCD, (uint32_t *) &GPIO->PCC,     _bit0,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_1,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit1,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_1,   _LCD, (uint32_t *) &GPIO->PCC,     _bit1,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_2,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit2,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_2,   _LCD, (uint32_t *) &GPIO->PCC,     _bit2,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_3,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit3,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_3,   _LCD, (uint32_t *) &GPIO->PCC,     _bit3,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_4,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit4,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_4,   _LCD, (uint32_t *) &GPIO->PCC,     _bit4,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_5,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit5,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_5,   _LCD, (uint32_t *) &GPIO->PCC,     _bit5,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_6,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit6,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_6,   _LCD, (uint32_t *) &GPIO->PCC,     _bit6,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_7,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit7,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN8_7,   _LCD, (uint32_t *) &GPIO->PCC,     _bit7,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    /*"****************************************************Group9*********************************************************************"*/
    {_PIN9_0,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit8,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_0,   _LCD, (uint32_t *) &GPIO->PCC,     _bit8,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_1,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit9,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_1,   _LCD, (uint32_t *) &GPIO->PCC,     _bit9,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_2,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit10, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_2,   _LCD, (uint32_t *) &GPIO->PCC,     _bit10, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_3,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit11, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_3,   _LCD, (uint32_t *) &GPIO->PCC,     _bit11, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_4,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit12, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_4,   _LCD, (uint32_t *) &GPIO->PCC,     _bit12, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_5,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit13, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_5,   _LCD, (uint32_t *) &GPIO->PCC,     _bit13, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_6,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit14, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_6,   _LCD, (uint32_t *) &GPIO->PCC,     _bit14, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_7,   _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit15, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN9_7,   _LCD, (uint32_t *) &GPIO->PCC,     _bit15, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    /*"****************************************************Group10*********************************************************************"*/
    {_PIN10_0,  _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit16, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_0,  _LCD, (uint32_t *) &GPIO->PCC,     _bit16, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_1,  _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit17, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_1,  _LCD, (uint32_t *) &GPIO->PCC,     _bit17, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_2,  _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit18, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_2,  _LCD, (uint32_t *) &GPIO->PCC,     _bit18, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_3,  _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit19, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_3,  _LCD, (uint32_t *) &GPIO->PCC,     _bit19, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_4,  _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit20, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_4,  _SPI3, (uint32_t *) &GPIO->PCC,     _bit20, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_5,  _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit21, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_5,  _SPI3, (uint32_t *) &GPIO->PCC,     _bit21, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_6,  _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit22, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_6,  _SPI3, (uint32_t *) &GPIO->PCC,     _bit22, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_7,  _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit23, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN10_7,  _SPI3, (uint32_t *) &GPIO->PCC,     _bit23, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},

    /*"****************************************************Group11*********************************************************************"*/
    {_PIN11_0,  _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit24, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN11_0,  _SPI0, (uint32_t *) &GPIO->PCC,     _bit24, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN11_1,  _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit25, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN11_1,  _SPI0, (uint32_t *) &GPIO->PCC,     _bit25, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN11_2,  _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit26, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN11_2,  _SPI0, (uint32_t *) &GPIO->PCC,     _bit26, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN11_3,  _NORMALIO, (uint32_t *) &GPIO->PCC,     _bit27, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN11_3,  _SPI0, (uint32_t *) &GPIO->PCC,     _bit27, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},

    /*"****************************************************Group12*********************************************************************"*/
    {_PIN12_0,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit0,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_0,  _LCD, (uint32_t *) &GPIO->PCD,     _bit0,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_1,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit1,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_1,  _LCD, (uint32_t *) &GPIO->PCD,     _bit1,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_2,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit2,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_2,  _LCD, (uint32_t *) &GPIO->PCD,     _bit2,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_3,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit3,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_3,  _LCD, (uint32_t *) &GPIO->PCD,     _bit3,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_4,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit4,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_4,  _LCD, (uint32_t *) &GPIO->PCD,     _bit4,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_5,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit5,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_5,  _LCD, (uint32_t *) &GPIO->PCD,     _bit5,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_6,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit6,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_6,  _LCD, (uint32_t *) &GPIO->PCD,     _bit6,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_7,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit7,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN12_7,  _LCD, (uint32_t *) &GPIO->PCD,     _bit7,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},
    /*"****************************************************Group13*********************************************************************"*/
    {_PIN13_0,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit8,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN13_0,  _LCDV, (uint32_t *) &GPIO->PCD,     _bit8,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},    /*"_LCDVA"*/
    {_PIN13_1,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit9,  1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN13_1,  _LCDV, (uint32_t *) &GPIO->PCD,     _bit9,  1,  0x01,   NULL,                       _bit0,  NULL,   NULL},    /*"_LCDVB"*/
    {_PIN13_2,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit10, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN13_2,  _LCDV, (uint32_t *) &GPIO->PCD,     _bit10, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},    /*"_LCDVC"*/
    {_PIN13_3,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit11, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN13_3,  _LCDV, (uint32_t *) &GPIO->PCD,     _bit11, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},    /*"_LCDVD"*/
    {_PIN13_4,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit12, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN13_4,  _LCDV, (uint32_t *) &GPIO->PCD,     _bit12, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},    /*"_LCDVP1"*/
    {_PIN13_5,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit13, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN13_5,  _LCDV, (uint32_t *) &GPIO->PCD,     _bit13, 1,  0x01,   NULL,                       _bit0,  NULL,   NULL},    /*"_LCDVP2"*/
    {_PIN13_6,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit14, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN13_7,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit15, 1,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    /*"****************************************************Group14*********************************************************************"*/
    {_PIN14_0,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit16, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN14_1,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit18, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN14_2,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit20, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN14_3,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit22, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN14_4,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit24, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN14_5,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit26, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN14_6,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit28, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
    {_PIN14_7,  _NORMALIO, (uint32_t *) &GPIO->PCD,     _bit30, 2,  0x00,   NULL,                       _bit0,  NULL,   NULL},
};

/* Exported data  ----------------------------------------------------------*/

/* Private functions ------------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/

/*****************************************************************************
** Function name:Rn8xxx_GPIO_SetPin
** Description:��GPIO �����ƽ
** Parameters: pin_id:�˿ں�  value:�����ƽ
** Returned value:NONE
******************************************************************************/
void Rn8xxx_GPIO_SetPin(uint8_t pin_id, uint8_t value)
{
    uint32_t pin_addr;
    uint8_t group_no ;

    if (pin_id >= _PIN_nMAX)
    {
        return;
    }

    group_no = (pin_id >> 3); /*"��ȡIO������"*/
    /*"*********************��ѯ��Ӧ�Ĵ�����ַ************************"*/
    if (group_no <= 3) /*" Group0 Group1 Group2 Group3"*/
    {
        pin_addr = (uint32_t)(&GPIO->PA);
    }
    else if (group_no <= 7) /*" Group4 Group5 Group6 Group7"*/
    {
        pin_addr = (uint32_t)(&GPIO->PB);
    }
    else if (group_no <= 11) /*" Group8 Group9 Group10 Group11"*/
    {
        pin_addr = (uint32_t)(&GPIO->PC);
    }
    else if (group_no <= 14) /*" Group12 Group13 Group14 "*/
    {
        pin_addr = (uint32_t)(&GPIO->PD);
    }
    else
    {
        return;
    }

    /*"����IO�����value��ƽ"*/
    //BITBAND_ADDR(pin_addr,(pin_id &0x07)+(group_no%4)*8) = value;
    BITBAND_ADDR(pin_addr, (pin_id & 0x07) + (group_no & 0x03) * 8) = value;
}

/*****************************************************************************
** Function name:   Rn8xxx_GPIO_ReadPin
** Description:����ȡGPIO ��ƽ
** Parameters:  pin_id:�˿ں�
** Returned value: GPIO�����ƽ
******************************************************************************/
uint8_t Rn8xxx_GPIO_ReadPin(uint8_t pin_id)
{
    uint32_t pin_addr;
    uint8_t  group_no, value = 0 ;

    if (pin_id >= _PIN_nMAX)
    {
        return (NULL);
    }

    group_no = (pin_id >> 3); /*"��ȡIO������"*/
    /*"*********************��ѯ��Ӧ�Ĵ�����ַ************************"*/
    if (group_no <= 3) /*" Group0 Group1 Group2 Group3"*/
    {
        pin_addr = (uint32_t)(&GPIO->PA);
    }
    else if (group_no <= 7) /*" Group4 Group5 Group6 Group7"*/
    {
        pin_addr = (uint32_t)(&GPIO->PB);
    }
    else if (group_no <= 11) /*" Group8 Group9 Group10 Group11"*/
    {
        pin_addr = (uint32_t)(&GPIO->PC);
    }
    else if (group_no <= 14) /*" Group12 Group13 Group14 "*/
    {
        pin_addr = (uint32_t)(&GPIO->PD);
    }
    else
    {
        return (NULL);
    }

    /*" ����IO��״̬"*/
    value = BITBAND_ADDR(pin_addr, (pin_id & 0x07) + (group_no % 4) * 8) ;
    return (value);
}

/*****************************************************************************
** Function name:Rn8xxx_GPIO_OverturnPin
** Description:������IO�ڷ�ת
** Parameters: pin_id:�˿ں�
** Returned value: GPIO�����ƽ
******************************************************************************/
void Rn8xxx_GPIO_OverturnPin(uint8_t pin_id)
{
    uint8_t Val_Over;
    Val_Over = Rn8xxx_GPIO_ReadPin(pin_id); /*"�õ���Ӧ���ŵĵ�ƽ"*/
    Val_Over ^= 1;
    Rn8xxx_GPIO_SetPin(pin_id, Val_Over);   // ����෴��ƽ
    return;
}

/*****************************************************************************
** Function name:Rn8xxx_GPIO_CfgPullMode
** Description:������IO�������Ĵ򿪼��ر�
** Parameters: pin_id:�˿ں� mode:Pull_ON ��  Pull_OFF �ر�
** Returned value:NONE
******************************************************************************/
void Rn8xxx_GPIO_CfgPullMode(uint8_t pin_id, eGPIOPull_TypeDef mode)
{
    uint32_t pin_addr;
    uint8_t group_no ;

    if (pin_id >= _PIN_nMAX)
    {
        return;
    }
    group_no = (pin_id >> 3); /*"��ȡIO������"*/
    /*"*********************��ѯ��Ӧ�Ĵ�����ַ************************"*/
    if (group_no <= 3) /*" Group0 Group1 Group2 Group3"*/
    {
        pin_addr = (uint32_t)(&GPIO->PUA);
    }
    else if (group_no <= 7) /*" Group4 Group5 Group6 Group7"*/
    {
        pin_addr = (uint32_t)(&GPIO->PUB);
    }
    else if (group_no <= 11) /*" Group8 Group9 Group10 Group11"*/
    {
        pin_addr = (uint32_t)(&GPIO->PUC);
    }
    else if (group_no <= 14) /*" Group12 Group13 Group14"*/
    {
        pin_addr = (uint32_t)(&GPIO->PUD);
    }
    else
    {
        return;
    }
    /*" ����IO�������Ĵ���"*/
    BITBAND_ADDR(pin_addr, (pin_id & 0x07) + (group_no % 4) * 8) = mode;
}

/*****************************************************************************
** Function name:GPIO_Config_IOMode
** Description:������IO��ģʽ
** Parameters: pin_id:�˿ں�
**   dir:GPIO_MODE_IN ����ģʽ  GPIO_MODE_OUT ���ģʽ GPIO_MODE_NORMAL ��̬ģʽ
**   mode:���������״̬����ѡ��ΪTTL_IN,NORMAL_IN���룬
**        ���������ΪNORMAL_OUT��N_OPENDRAIN_OUT
** Returned value:NONE
******************************************************************************/
void Rn8xxx_GPIO_CfgIOMode(uint8_t pin_id, eGPIODir_TypeDef dir, eGPIOMode_TypeDef mode)
{
    uint32_t pin_addr1, pin_addr2, pin_addr3;
    uint8_t group_no ;
    uint8_t  pil_cnt = 0xff, pid_cnt = 0xff;
    if (pin_id >= _PIN_nMAX)
    {
        return;
    }
    group_no = (pin_id >> 3); /*"��ȡIO������"*/
    /*"*********************��ѯ��Ӧ�Ĵ�����ַ************************"*/
    if (group_no <= 3) /*" Group0 Group1 Group2 Group3"*/
    {
        pin_addr1 = (uint32_t)(&GPIO->PMA);
        pin_addr2 = (uint32_t)(&GPIO->PIEA);
        pin_addr3 = (uint32_t)(&GPIO->PIMA);
        if (group_no == 1)
        {
            pil_cnt = (pin_id & 0x07) +16;
            pid_cnt = (pin_id & 0x07);
        }
        else if (group_no == 2)
        {
            pil_cnt = (pin_id & 0x07) +24;
            pid_cnt = (pin_id & 0x07) +8;
        }
    }
    else if (group_no <= 7) /*" Group4 Group5 Group6 Group7"*/
    {
        pin_addr1 = (uint32_t)(&GPIO->PMB);
        pin_addr2 = (uint32_t)(&GPIO->PIEB);
        pin_addr3 = (uint32_t)(&GPIO->PIMB);
        if (group_no == 4)
        {
            pil_cnt = (pin_id & 0x07) +16;
            pid_cnt = (pin_id & 0x07);
        }
        else if (group_no == 5)
        {
            pil_cnt = (pin_id & 0x07) +24;
            pid_cnt = (pin_id & 0x07) +8;
        }
    }
    else if (group_no <= 11) /*" Group8 Group9 Group10 Group11"*/
    {
        pin_addr1 = (uint32_t)(&GPIO->PMC);
        pin_addr2 = (uint32_t)(&GPIO->PIEC);
        pin_addr3 = (uint32_t)(&GPIO->PIMC);
        if ((pin_id == _PIN11_0) || (pin_id == _PIN11_1) || (pin_id == _PIN11_2) || (pin_id == _PIN11_3))
        {
            pil_cnt = (pin_id & 0x07) +4;
            pid_cnt = (pin_id & 0x07);
        }
        else if ((pin_id == _PIN11_4) || (pin_id == _PIN11_5) || (pin_id == _PIN11_6) || (pin_id == _PIN11_7))
        {
            pil_cnt = (pin_id & 0x07) +8;
            pid_cnt = (pin_id & 0x07) +4;
        }
    }
    else if (group_no <= 14) /*" Group12 Group13 Group14"*/
    {
        pin_addr1 = (uint32_t)(&GPIO->PMD);
        pin_addr2 = (uint32_t)(&GPIO->PIED);
        pin_addr3 = (uint32_t)(&GPIO->PIMD);
        if ((pin_id == _PIN14_0) || (pin_id == _PIN14_1) || (pin_id == _PIN14_2) || (pin_id == _PIN14_3))
        {
            pil_cnt = (pin_id & 0x07) +4;
            pid_cnt = (pin_id & 0x07);
        }
        else if ((pin_id == _PIN14_4) || (pin_id == _PIN14_5) || (pin_id == _PIN14_6) || (pin_id == _PIN14_7))
        {
            pil_cnt = (pin_id & 0x07) +8;
            pid_cnt = (pin_id & 0x07) +4;
        }
    }
    else
    {
        return;
    }
    /*"*********************������Ӧ�Ĵ���************************"*/
    switch (dir)
    {
        case GPIO_MODE_IN:              /*" ����ģʽ"*/
        case GPIO_MODE_NORMAL:          /*" ����ģʽ�����粻�õ�IO������Ϊ��ģʽ"*/
        {
            BITBAND_ADDR(pin_addr1, (pin_id & 0x07) + (group_no % 4) * 8) = 1 ; /*" GPIO->PMģʽ����Ϊ����"*/
            if (dir == GPIO_MODE_IN)
            {
                BITBAND_ADDR(pin_addr2, (pin_id & 0x07) + (group_no % 4) * 8) = 0 ; /*" ������ʹ��"*/
            }
            else
            {
                BITBAND_ADDR(pin_addr2, (pin_id & 0x07) + (group_no % 4) * 8) = 1 ;
            }

            if ((mode == TTL_IN) && (pil_cnt != 0xff))
            {
                BITBAND_ADDR(pin_addr3, pil_cnt) = 1 ;
            }
            else if ((mode == NORMAL_IN) && (pil_cnt != 0xff))
            {
                BITBAND_ADDR(pin_addr3, pil_cnt) = 0 ;
            }
        }
        break;
        case GPIO_MODE_OUT:             /*" ���ģʽ"*/
        {
            BITBAND_ADDR(pin_addr1, (pin_id & 0x07) + (group_no % 4) * 8) = 0 ; /*"GPIO->PMģʽ����Ϊ���"*/

            if ((mode == N_OPENDRAIN_OUT) && (pid_cnt != 0xff))
            {
                BITBAND_ADDR(pin_addr3, pid_cnt) =  1 ;
            }
            else if ((mode == NORMAL_OUT) && (pid_cnt != 0xff))
            {
                BITBAND_ADDR(pin_addr3, pid_cnt) =  0 ;
            }
        }
        break;
        default:
            break;
    }
    return;
}

/*****************************************************************************
** Function name:   Rn8xxx_GPIO_CfgFun
** Description:     ����IO�ڹ��ܣ���˿��޶�Ӧ���ܣ��˳�
**              ע��:�в���IO�й����ԣ����ú��ı�����IO����
** Parameters:  pin_id:�˿ں�
**              Fun:IO�ڶ�Ӧ���ܣ����й���ʹ��eGPIOFunction_TypeDefö��
** Returned value:NONE
******************************************************************************/
ErrorStatus Rn8xxx_GPIO_CfgFun(uint8_t pin_id, eGPIOFunction_TypeDef Fun)
{
    uint16_t i, j;
    ErrorStatus status;

    status = ERROR;
    SysCtl_EnableWrite;
    GPIO_Clk_En;
    if (pin_id < _PINSegCom_Group) /*"��ͨGPIO�ڸ��ù�������"*/
    {
        if (_UART2 == Fun) /*"UART2_SEL��Ҫ��ǰ����"*/
        {
            switch (pin_id)
            {
                case _PIN2_4:/*"P24/P25ѡ��ΪUART2"*/
                case _PIN2_5:
                    BITBAND_ADDR((uint32_t)(&GPIO->PCA0), 30) = 0;  //
                    BITBAND_ADDR((uint32_t)(&GPIO->PCA0), 31) = 0;  //
                    break;
                case _PIN0_0:/*"P00/P01ѡ��ΪUART2"*/
                case _PIN0_1:
                    BITBAND_ADDR((uint32_t)(&GPIO->PCA0), 30) = 1;  //
                    BITBAND_ADDR((uint32_t)(&GPIO->PCA0), 31) = 0;  //
                    break;
                case _PIN2_2:/*"P22/P23ѡ��ΪUART2"*/
                case _PIN2_3:
                    BITBAND_ADDR((uint32_t)(&GPIO->PCA0), 30) = 0;  //
                    BITBAND_ADDR((uint32_t)(&GPIO->PCA0), 31) = 1;  //
                    break;
                case _PIN2_6:/*"P26/P27ѡ��ΪUART2"*/
                case _PIN2_7:
                    BITBAND_ADDR((uint32_t)(&GPIO->PCA0), 30) = 1;  //
                    BITBAND_ADDR((uint32_t)(&GPIO->PCA0), 31) = 1;  //
                    break;
                default:
                    break;
            }
        }
        else if (_SPI0 == Fun)
        {
            switch (pin_id)
            {
                case _PIN5_0:/*"ѡ��P50/P51/P46/P47��ΪSPI0�ӿ�"*/
                case _PIN5_1:
                case _PIN4_6:
                case _PIN4_7:
                    BITBAND_ADDR((uint32_t)(&GPIO->PCC), 28) = 0;  //
                    break;
                case _PIN11_0:/*"ѡ��P110~P113��ΪSPI0�ӿ�"*/
                case _PIN11_1:
                case _PIN11_2:
                case _PIN11_3:
                    BITBAND_ADDR((uint32_t)(&GPIO->PCC), 28) = 1;  //
                    break;
                default:
                    break;
            }
        }
        for (i = 0; i < sizeof(GpioFunFile) / sizeof(GpioFunFile[0]); i++)
        {
            if ((pin_id == GpioFunFile[i].pin_id) && (Fun == GpioFunFile[i].GpioFun))
            {
                if (GpioFunFile[i].RegAd_2 != NULL)
                {
                    for (j = 0; j < GpioFunFile[i].nbit_2; j++)
                    {
                        BITBAND_ADDR((uint32_t)GpioFunFile[i].RegAd_2, (GpioFunFile[i].starNum_2 + j)) = ((GpioFunFile[i].PutData_2 >> j) & 0x01);
                    }
                }
                for (j = 0; j < GpioFunFile[i].nbit; j++)
                {
                    BITBAND_ADDR((uint32_t)GpioFunFile[i].RegAd, (GpioFunFile[i].starNum + j)) = ((GpioFunFile[i].PutData >> j) & 0x01);
                }

                if ((pin_id == _PIN4_4) || (pin_id == _PIN4_5))
                {
                    if (Fun == _AIN)
                    {
                        //BITBAND_ADDR((uint32_t)((uint32_t *)&MADC->ANA_PAD) , (pin_id-_PIN4_4)) = 1;
                        MADC->ANA_PAD |= (0x00000001 << (pin_id - (_PIN4_4)));
                    }
                    else
                    {
                        MADC->ANA_PAD &= (~(0x00000001 << (pin_id - (_PIN4_4))));
                    }
                }

                if ((pin_id == _PIN5_6) || (pin_id == _PIN4_4) || (pin_id == _PIN4_5))
                {
                    RTC->VBAT_IOWEN &= 0xFFFFFF0F;
                    RTC->VBAT_IOWEN |= 0xb0;
                    if (pin_id == _PIN5_6)
                    {
                        /*"P56 �ڵ� RTCOUT ���ù�ϵ�� RTC �½ڼĴ���������                �� GPIO �½ڸ������üĴ����޹ء�
                        �� VCC �޵磬 VBAT �ϵ�ʱ�� P56 Ĭ����� 1Hz��һ�� VCC�ϵ磬 1Hz ����ᱻ�رա���Χ��·�����Ҫע������⡣                "*/
                        if (Fun == _RTC_OUT)
                        {
                            RTC->VBAT_IOMODE |= 0x00a0;
                        }
                        else
                        {
                            RTC->VBAT_IOMODE &= 0xFFFFFF0F;
                        }
                    }
                    else if (pin_id == _PIN4_4)
                    {
                        RTC->VBAT_IOMODE &= 0xFFFFFFF0;
                    }
                    else if (pin_id == _PIN4_5)
                    {
                        RTC->VBAT_IOMODE &= 0xFFFFF0FF;
                    }

                    RTC->VBAT_IOWEN &= 0xFFFFFF0F;
                }

                status = SUCCESS;
                break;
            }
        }
    }
    else if (pin_id < _PIN_nMAX) /*"SEGCOM �ڸ��ù�������"*/
    {
        if (Fun == _SEG)
        {
            BITBAND_ADDR((uint32_t)(&GPIO->PCE), (pin_id & 0x07)) = 0;
            status = SUCCESS;
        }
        else if (Fun == _COM)
        {
            BITBAND_ADDR((uint32_t)(&GPIO->PCE), (pin_id & 0x07)) = 1;
            status = SUCCESS;
        }
        else
        {
            status = ERROR;
        }
    }
    else
    {
        status = ERROR;
    }

    return status;
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
