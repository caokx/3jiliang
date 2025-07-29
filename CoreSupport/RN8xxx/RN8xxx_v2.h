/**
* @file     RN8XXX_V2.h
* @brief    CMSIS Cortex-M0 Core Peripheral Access Layer Header File
*           for RN8XXX_V2 CM0 Device
* @version  V1.0.0
* @date     2023.2.2
*
* @note
* Copyright (C) REnergy Micro-Electronics Co.,LTD.
******************************************************************************/

#ifndef __RN8XXX_V2_H__
#define __RN8XXX_V2_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup RN8XXX_V2_Definitions
     This file defines all structures and symbols for RN8XXX_V2:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - Peripheral definitions
    @{
*/

/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/
/** @addtogroup RN8XXX_V2_CMSIS Device CMSIS Definitions
     Configuration of the Cortex-M0 Processor and Core Peripherals
    @{
*/

/*
    * ==========================================================================
    * ---------- Interrupt Number Definition -----------------------------------
    * ==========================================================================
    */
typedef enum IRQn
{
    /******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn = -14, /*!<  2 Cortex-M0 Non Maskable Interrupt                  */
    HardFault_IRQn = -13,      /*!<  3 Cortex-M0 Hard Fault Interrupt                    */

    SVCall_IRQn = -5, /*!< 11 Cortex-M0 SV Call Interrupt                       */

    PendSV_IRQn = -2,  /*!< 14 Cortex-M0 Pend SV Interrupt                       */
    SysTick_IRQn = -1, /*!< 15 Cortex-M0 System Tick Interrupt                   */

    /******  RN8XXX_V2 Specific Interrupt Numbers ********************************************************/
    SYSCLKCAL_IRQn = 0, /*!<  16 SYSCLK CALC irq number                          */
    CMP_IRQn = 1,       /*!<  17 Voltage compare Interrupt                       */
    // VCH_IRQn                     = 2,      /*!<  18 Power Switch Interrupt                          */
    RTC_IRQn = 3,            /*!<  19 RTC Interrupt                                   */
    D2F_IRQn = 4,
    MADC_IRQn = 5,           /*!<  21 SAR Interrupt                                   */
    UART0_IRQn = 6,          /*!<  22 UART0 Interrupt                                 */
    UART1_IRQn = 7,          /*!<  23 UART1 Interrupt                                 */
    UART2_IRQn = 8,          /*!<  24 UART2 Interrupt                                 */
    UART3_IRQn = 9,          /*!<  25 UART3 Interrupt                                 */
    SPI_IRQn = 10,           /*!<  26 SPI0 Interrupt                                  */
    I2C_IRQn = 11,           /*!<  27 IIC Interrupt                                   */
    ISO78160_SPI3_IRQn = 12, /*!<  28 ISO7816 0 and SPI3 Interrupt                    */
    ISO78161_SPI2_IRQn = 13, /*!<  29 ISO7816 1 and SPI2 Interrupt                    */
    TC0_IRQn = 14,           /*!<  30 Timer/Counter 0 Interrupt                       */
    TC1_IRQn = 15,           /*!<  31 Timer/Counter 1 Interrupt                       */
    UART4_IRQn = 16,         /*!<  32 UART4 Interrupt                                 */
    UART5_IRQn = 17,         /*!<  33 UART5 Interrupt                                 */
    WDT_IRQn = 18,           /*!<  34 Watch Dog Interrupt                             */
    KBI_IRQn = 19,           /*!<  35 Key Interrupt                                   */
    LCD_DSP_IRQn = 20,       /*!<  36 LCD and DSP Interrupt                           */
    //SEA_IRQn = 21,           /*!<  37 SEA Interrupt                                   */
    SPI1_IRQn = 23, /*!<  39 SPI1 Interrupt                                  */
    EXT0_IRQn = 24, /*!<  40 Extern0 Interrupt(or all extern irq)            */
    EXT1_IRQn = 25, /*!<  41 Extern1 Interrupt(share with simp-tc0)          */
    EXT2_IRQn = 26, /*!<  42 Extern2 Interrupt(share with simp-tc1)          */
    EXT3_IRQn = 27, /*!<  43 Extern3 Interrupt(share with simp-tc2)          */
    EXT4_IRQn = 28, /*!<  44 Extern4 Interrupt(share with simp-tc3)          */
    EXT5_IRQn = 29, /*!<  45 Extern5 Interrupt(share with m2m)               */
    EXT6_IRQn = 30, /*!<  46 Extern6 Interrupt                               */
    EXT7_IRQn = 31, /*!<  47 Extern7 Interrupt                               */
} IRQn_Type;

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */
#define __MPU_PRESENT 0          /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS 2       /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig 0 /*!< Set to 1 if different SysTick Config is used     */

#if 0
#if defined(__CC_ARM)
#if defined(__TARGET_FPU_VFP)
#define __FPU_PRESENT 1 /*!< FPU present or not                               */
#else
#define __FPU_PRESENT 0 /*!< FPU present or not                               */
#endif
#else
#define __FPU_PRESENT 0 /*!< FPU present or not                               */
#endif
#endif
/*@}*/ /* end of group RN8XXX_V2_CMSIS */

#include "core_cm0.h" /* Cortex-M0 processor and core peripherals           */

/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/
/** @addtogroup RN8XXX_V2_Peripherals RN8XXX_V2 Peripherals
     RN8XXX_V2 Device Specific Peripheral registers structures
    @{
*/

#if defined(__CC_ARM)
#pragma anon_unions
#endif

/*--------------------- GPIO --------------------------------------------------*/
typedef struct
{
    __IO uint32_t PMA;          /* offset = 0x0          PortA mode register          */
    __IO uint32_t PA;           /* offset = 0x4          PortA data register          */
    __IO uint32_t PCA0;         /* offset = 0x8          PortA control register0      */
    __IO uint32_t PCA1;         /* offset = 0xc          PortA control register1      */
    __IO uint32_t PUA;          /* offset = 0x10         PortA pull-up register       */
    __IO uint32_t PIMA;         /* offset = 0x14         PortA input mode register    */
    __IO uint32_t PIEA;         /* offset = 0x18         PortA input enable register  */
    __IO uint32_t PMB;          /* offset = 0x1c         PortB mode register          */
    __IO uint32_t PB;           /* offset = 0x20         PortB data register          */
    __IO uint32_t PCB;          /* offset = 0x24         PortB control register       */
    __IO uint32_t PUB;          /* offset = 0x28         PortB pull-up register       */
    __IO uint32_t PIMB;         /* offset = 0x2c         PortB input mode register    */
    __IO uint32_t PIEB;         /* offset = 0x30         PortB input enable register  */
    __IO uint32_t PMC;          /* offset = 0x34         PortC mode register          */
    __IO uint32_t PC;           /* offset = 0x38         PortC data register          */
    __IO uint32_t PCC;          /* offset = 0x3c         PortC control register       */
    __IO uint32_t PUC;          /* offset = 0x40         PortC pull-up register       */
    __IO uint32_t PIEC;         /* offset = 0x44         PortC input enable register  */
    __IO uint32_t PIMC;         /* offset = 0x48         PortC input mode register    */
    __IO uint32_t PCB2;         /* offset = 0x4c         PortB control2 register      */
    __IO uint32_t PMD;          /* offset = 0x50         PortC mode register          */
    __IO uint32_t PD;           /* offset = 0x54         PortC data register          */
    __IO uint32_t PCD;          /* offset = 0x58         PortC control register       */
    __IO uint32_t PUD;          /* offset = 0x5c         PortC pull-up register       */
    __IO uint32_t PCE;          /* offset = 0x60         PortE control register       */
    __IO uint32_t PASET;        /* offset = 0x64         PortA data set register      */
    __IO uint32_t PACLR;        /* offset = 0x68         PortA data clear register    */
    __IO uint32_t PBSET;        /* offset = 0x6c         PortB data set register      */
    __IO uint32_t PBCLR;        /* offset = 0x70         PortB data clear register    */
    __IO uint32_t PCSET;        /* offset = 0x74         PortC data set register      */
    __IO uint32_t PCCLR;        /* offset = 0x78         PortC data clear register    */
    __IO uint32_t PDSET;        /* offset = 0x7c    */
    __IO uint32_t PDCLR;        /* offset = 0x80    */
    __IO uint32_t PIED;         /* offset = 0x84    */
    __IO uint32_t PIMD;         /* offset = 0x88    */
    __IO uint32_t RESERVED[29]; /* offset = 0x8c-fc */
    __IO uint32_t P34_CFG;      /* offset = 0x100   */
    __IO uint32_t P50_CFG;      /* offset = 0x104   */
    __IO uint32_t P51_CFG;      /* offset = 0x108   */
    __IO uint32_t IOCNT_CTL;    /* offset = 0x10c   */
} GPIO_TypeDef;
/*--------------------- UART --------------------------------------------------*/
typedef struct
{
    __IO uint32_t CTRL;      /* offset = 0x00 */
    __IO uint32_t BAUD;      /* offset = 0x04 */
    __IO uint32_t STA;       /* offset = 0x08 */
    __IO uint32_t TXD;       /* offset = 0x0C */
    __IO uint32_t RXD;       /* offset = 0x10 */
    __IO uint32_t FDIV;      /* offset = 0x14 */
    __IO uint32_t DMA_CTRL;  /* offset = 0x18 */
    __IO uint32_t DMA_TBADR; /* offset = 0x1C */
    __IO uint32_t DMA_RBADR; /* offset = 0x20 */
    __IO uint32_t DMA_TLEN;  /* offset = 0x24 */
    __IO uint32_t DMA_RLEN;  /* offset = 0x28 */
    __IO uint32_t DMA_TADR;  /* offset = 0x2C */
    __IO uint32_t DMA_RADR;  /* offset = 0x30 */
    __IO uint32_t DMA_IE;    /* offset = 0x34 */
    __IO uint32_t DMA_FLG;   /* offset = 0x38 */
    __IO uint32_t DMA_TO;    /* 0x3C */
} UART_TypeDef;
/*--------------------- TC --------------------------------------------------*/
typedef struct
{
    __IO uint32_t CNT;       /* offset = 0x00 */
    __IO uint32_t PS;        /* offset = 0x04 */
    __IO uint32_t RESERVED1; /* offset = 0x8  */
    __IO uint32_t DN;        /* offset = 0x0c */
    __IO uint32_t RESERVED2; /* offset = 0x10 */
    __IO uint32_t CCD0;      /* offset = 0x14 */
    __IO uint32_t CCD1;      /* offset = 0x18 */
    __IO uint32_t CCFG;      /* offset = 0x1c */
    __IO uint32_t CTRL;      /* offset = 0x20 */
    __IO uint32_t CM0;       /* offset = 0x24 */
    __IO uint32_t CM1;       /* offset = 0x28 */
    __IO uint32_t IE;        /* offset = 0x2c */
    __IO uint32_t STA;       /* offset = 0x30 */
} TC_TypeDef;
/*--------------------- SPI --------------------------------------------------*/
typedef struct
{
    __IO uint32_t CTRL;      /* offset = 0x00 */
    __IO uint32_t STA;       /* offset = 0x04 */
    __IO uint32_t TX;        /* offset = 0x08 */
    __IO uint32_t RX;        /* offset = 0x0c */
    __IO uint32_t TXDFLT;    /* offset = 0x10 */
    __IO uint32_t DMA_CTRL;   /* offset = 0x14 */
    __IO uint32_t DMA_TBADR; /* offset = 0x18 */
    __IO uint32_t DMA_RBADR; /* offset = 0x1C */
    __IO uint32_t DMA_TLEN;  /* offset = 0x20 */
    __IO uint32_t DMA_RLEN;  /* offset = 0x24 */
    __IO uint32_t DMA_TADR;  /* offset = 0x28 */
    __IO uint32_t DMA_RADR;  /* offset = 0x2C */
    __IO uint32_t DMA_IE;    /* offset = 0x30 */
    __IO uint32_t DMA_FLG;   /* offset = 0x34 */
} SPI_TypeDef;
/*--------------------- I2C --------------------------------------------------*/
typedef struct
{
    __IO uint32_t CTRL; /* offset = 0x0 */
    __IO uint32_t CLK;  /* offset = 0x4 */
    __IO uint32_t STA;  /* offset = 0x8 */
    __IO uint32_t ADDR; /* offset = 0xc */
    __IO uint32_t DATA; /* offset = 0x10 */
} I2C_TypeDef;
/*--------------------- KBI --------------------------------------------------*/
typedef struct
{
    __IO uint32_t CTRL; /* offset = 0x0          KBI control register         */
    __IO uint32_t SEL;  /* offset = 0x4          KBI select register          */
    __IO uint32_t DATA; /* offset = 0x8          KBI data register            */
    __IO uint32_t MASK; /* offset = 0xc          KBI mask register            */
} KBI_TypeDef;
/*--------------------- WDT --------------------------------------------------*/
typedef struct
{
    __IO uint32_t EN; /* offset 0x0 */
} WDT_TypeDef;
/*--------------------- SYSCTL --------------------------------------------------*/
typedef struct
{
    __IO uint32_t OSC_CTRL1;     /* offset = 0x0       */
    __IO uint32_t SYS_MODE;      /* offset = 0x4       */
    __IO uint32_t SYS_PD;        /* offset = 0x8       */
    __IO uint32_t ADC_CTRL;      /* offset = 0xc       */
    __IO uint32_t OSC_CTRL2;     /* offset = 0x10      */
    __IO uint32_t SYS_RST;       /* offset = 0x14      */
    __IO uint32_t MAP_CTRL;      /* offset = 0x18      */
    __IO uint32_t MOD0_EN;       /* offset = 0x1c      */
    __IO uint32_t MOD1_EN;       /* offset = 0x20      */
    __IO uint32_t INTC_EN;       /* offset = 0x24      */
    __IO uint32_t KBI_EN;        /* offset = 0x28      */
    __IO uint32_t CHIP_ID;       /* offset = 0x2c      */
    __IO uint32_t SYS_PS;        /* offset = 0x30      */
    __IO uint32_t IRFR_CTRL;     /* offset = 0x34      */
    __IO uint32_t RESERVED1[15]; /* offset = 0x38-0x70 */
    __IO uint32_t DIE_VER;       /* offset = 0x74      */
    __IO uint32_t TRIM_CFG1;     /* offset = 0x78      */
    __IO uint32_t TRIM_START;    /* offset = 0x7c      */
    __IO uint32_t DMA_PRI;       /* offset = 0x80      */
    __IO uint32_t RESERVED2[27]; /* offset = 0x84-0xec */
    __IO uint32_t FAB_UID0;      /* offset = 0xf0      */
    __IO uint32_t FAB_UID1;      /* offset = 0xf4      */
} SYSCTL_TypeDef;
/*--------------------- 7816 --------------------------------------------------*/
typedef struct
{
    __IO uint32_t CTRL0;  /* offset = 0x0        */
    __IO uint32_t CTRL1;  /* offset = 0x4        */
    __IO uint32_t CLK;    /* offset = 0x8        */
    __IO uint32_t BDDIV0; /* offset = 0xc        */
    __IO uint32_t BDDIV1; /* offset = 0x10       */
    __IO uint32_t STA0;   /* offset = 0x14       */
    __IO uint32_t STA1;   /* offset = 0x18       */
    __IO uint32_t DATA0;  /* offset = 0x1c       */
    __IO uint32_t DATA1;  /* offset = 0x20       */
} ISO7816_TypeDef;
/*-------------------- RTC ---------------------------------------------------*/
typedef struct
{
    __IO uint32_t CTRL;          /* offset = 0x00     */
    __IO uint32_t SC;            /* offset = 0x04     */
    __IO uint32_t MN;            /* offset = 0x08     */
    __IO uint32_t HR;            /* offset = 0x0c     */
    __IO uint32_t DT;            /* offset = 0x10     */
    __IO uint32_t MO;            /* offset = 0x14     */
    __IO uint32_t YR;            /* offset = 0x18     */
    __IO uint32_t DW;            /* offset = 0x1c     */
    __IO uint32_t CNT1;          /* offset = 0x20     */
    __IO uint32_t CNT2;          /* offset = 0x24     */
    __IO uint32_t SCA;           /* offset = 0x28     */
    __IO uint32_t MNA;           /* offset = 0x2c     */
    __IO uint32_t HRA;           /* offset = 0x30     */
    __IO uint32_t IE;            /* offset = 0x34     */
    __IO uint32_t IF;            /* offset = 0x38     */
    __IO uint32_t TEMP;          /* offset = 0x3c     */
    __IO uint32_t RESERVED0[11]; /* offset = 0x40~0x68*/
    __IO uint32_t LOSC_CFG1;     /* offset = 0x6c     */
    __IO uint32_t RESERVED1[6];  /* offset = 0x70~0x84*/
    __IO uint32_t VBAT_IOMODE;   /* offset = 0x88     */
    __IO uint32_t VBAT_IOWEN;    /* offset = 0x8c     */
    __IO uint32_t P44N0_TIME0;   /* offset = 0x90     */
    __IO uint32_t P44N0_TIME1;   /* offset = 0x94     */
    __IO uint32_t P44N0_TIME2;   /* offset = 0x98     */
    __IO uint32_t P44P0_TIME0;   /* offset = 0x9c     */
    __IO uint32_t P44P0_TIME1;   /* offset = 0xa0     */
    __IO uint32_t P44P0_TIME2;   /* offset = 0xa4     */
    __IO uint32_t P44N1_TIME0;   /* offset = 0xa8     */
    __IO uint32_t P44N1_TIME1;   /* offset = 0xac     */
    __IO uint32_t P44N1_TIME2;   /* offset = 0xb0     */
    __IO uint32_t P44P1_TIME0;   /* offset = 0xb4     */
    __IO uint32_t P44P1_TIME1;   /* offset = 0xb8     */
    __IO uint32_t P44P1_TIME2;   /* offset = 0xbc     */
    __IO uint32_t RESERVED2[3];  /* offset = 0xc0     */
    __IO uint32_t CALPS;         /* offset = 0xcc     */
    __IO uint32_t CAL_T[10];     /* offset = 0xd0~0xF4 */
    __IO uint32_t RESERVED3[2];  /* offset = 0xF8~0xFC */
    __IO uint32_t P45N0_TIME0;   /* offset = 0x100     */
    __IO uint32_t P45N0_TIME1;   /* offset = 0x104     */
    __IO uint32_t P45N0_TIME2;   /* offset = 0x108     */
    __IO uint32_t P45P0_TIME0;   /* offset = 0x10c     */
    __IO uint32_t P45P0_TIME1;   /* offset = 0x110     */
    __IO uint32_t P45P0_TIME2;   /* offset = 0x114     */
    __IO uint32_t P45N1_TIME0;   /* offset = 0x118     */
    __IO uint32_t P45N1_TIME1;   /* offset = 0x11c     */
    __IO uint32_t P45N1_TIME2;   /* offset = 0x120     */
    __IO uint32_t P45P1_TIME0;   /* offset = 0x124     */
    __IO uint32_t P45P1_TIME1;   /* offset = 0x128     */
    __IO uint32_t P45P1_TIME2;   /* offset = 0x12c     */
} RTC_TypeDef;
/*-------------------- MADC ---------------------------------------------------*/
typedef struct
{
    __IO uint32_t AD_CTRL;     /* offset = 0x0       */
    __IO uint32_t AD_START;    /* offset = 0x4       */
    __IO uint32_t AD_STAT;     /* offset = 0x8       */
    __IO uint32_t AD_DATA;     /* offset = 0xC       */
    __IO uint32_t LVD_CTRL;    /* offset = 0x10      */
    __IO uint32_t LVD_STAT;    /* offset = 0x14      */
    __IO uint32_t SAR_CTRL1;   /* offset = 0x18      */
    __IO uint32_t SAR_DATA2;   /* offset = 0x1c      */
    __IO uint32_t RESERVED[7]; /* offset = 0x20- 0X38*/
    __IO uint32_t ANA_PAD;     /* offset = 0x3c      */
    __IO uint32_t ANA_RST;     /* offset = 0x40      */
} MADC_TypeDef;
/*--------------------- INTC --------------------------------------------------*/
typedef struct
{
    __IO uint32_t CTRL; /* offset = 0x0         interrupt control register   */
    __IO uint32_t MODE; /* offset = 0x4         interrupt mode register      */
    __IO uint32_t MASK; /* offset = 0x8         interrupt mask register      */
    __IO uint32_t STA;  /* offset = 0xC         interrupt status register    */
} INTC_TypeDef;
/*--------------------- LCD --------------------------------------------------*/
typedef struct
{
    __IO uint32_t CTRL;        /* offset = 0x0       */
    __IO uint32_t STA;         /* offset = 0x4       */
    __IO uint32_t CLKDIV;      /* offset = 0x8       */
    __IO uint32_t BLINK;       /* offset = 0xC       */
    __IO uint32_t PS;          /* offset = 0x10      */
    __IO uint32_t RESCTL;      /* offset = 0x14      */
    __IO uint32_t RESERVED[2]; /* offset = 0x18      */
    __IO uint8_t BUF[38];      /* offset = 0x1c      */
} LCD_TypeDef;

/*--------------------- SIMP_TC --------------------------------------------------*/
typedef struct
{
    __IO uint32_t CTRL1;   /* 0x00 */
    __IO uint32_t LOAD1;   /* 0x04 */
    __IO uint32_t VAL1;    /* 0x08 */
    __IO uint32_t CTRL2;   /* 0x0c */
    __IO uint32_t LOAD2;   /* 0x10 */
    __IO uint32_t VAL2;    /* 0x14 */
    __IO uint32_t CTRL3;   /* 0x18 */
    __IO uint32_t LOAD3;   /* 0x1c */
    __IO uint32_t VAL3;    /* 0x20 */
    __IO uint32_t CTRL4;   /* 0x24 */
    __IO uint32_t LOAD4;   /* 0x28 */
    __IO uint32_t VAL4;    /* 0x2c */
} SIMP_TC_TypeDef;

/*--------------------- D2F --------------------------------------------------*/
typedef struct
{
    __IO uint32_t HFconst3;  /* 0x00 */
    __IO uint32_t IE;        /* 0x04 */
    __IO uint32_t IF;        /* 0x08 */
    __IO uint32_t CFG;       /* 0x0c */
    __IO uint32_t D2FP[12];  /* 0x10-0x3c */
    __IO uint32_t D2FE[12];  /* 0x40-0x6c */
} D2F_TypeDef;

/*--------------------- M2M --------------------------------------------------*/
typedef struct
{
    __IO uint32_t MODE;   /* 0x00 */
    __IO uint32_t CTL;    /* 0x04 */
    __IO uint32_t DUMMY;  /* 0x08 */
    __IO uint32_t SADDR;  /* 0x0c */
    __IO uint32_t DADDR;  /* 0x10 */
    __IO uint32_t ILEN;   /* 0x14 */
    __IO uint32_t IE;     /* 0x18 */
    __IO uint32_t IF;     /* 0x1c */
} M2M_TypeDef;

/*--------------------- DSP --------------------------------------------------*/
typedef struct
{
    __IO uint32_t MAC_CTL0;   /* 0x00 */
    __IO uint32_t MAC_CTL1;   /* 0x04 */
    __IO uint32_t MAC_CTL2;   /* 0x08 */
    __IO uint32_t MAC_IN0;    /* 0x0C */
    __IO uint32_t MAC_IN1;    /* 0x10 */
    __IO uint32_t MAC_IN2;    /* 0x14 */
    __IO uint32_t MAC_IN3;    /* 0x18 */
    __IO uint32_t MAC_IN4;    /* 0x1C */
    __IO uint32_t MAC_IN5;    /* 0x20 */
    __IO uint32_t MAC_OUT0;   /* 0x24 */
    __IO uint32_t MAC_OUT1;   /* 0x28 */
    __IO uint32_t MAC_OUT2;   /* 0x2C */
    __IO uint32_t MAC_OUT3;   /* 0x30 */
    __IO uint32_t DIV_IN0;    /* 0x34 */
    __IO uint32_t DIV_IN1;    /* 0x38 */
    __IO uint32_t DIV_OUT0;   /* 0x3C */
    __IO uint32_t DMA_SRBADR; /* 0x40 */
    __IO uint32_t DMA_SIBADR; /* 0x44 */
    __IO uint32_t DMA_PRBADR; /* 0x48 */
    __IO uint32_t DMA_PIBADR; /* 0x4C */
    __IO uint32_t DMA_TRBADR; /* 0x50 */
    __IO uint32_t DMA_TIBADR; /* 0x54 */
    __IO uint32_t DMA_LEN;    /* 0x58 */
    __IO uint32_t FFT_IE;     /* 0x5C */
    __IO uint32_t FFT_FLG;    /* 0x60 */
    __IO uint32_t ALU_STA0;   /* 0x64 */
    __IO uint32_t ALU_STA1;   /* 0x68 */
    __IO uint32_t CRD_CTL;    /* 0x6C */
    __IO uint32_t CRD_XIN;    /* 0x70 */
    __IO uint32_t CRD_YIN;    /* 0x74 */
    __IO uint32_t CRD_AMP;    /* 0x78 */
    __IO uint32_t CRD_PHASE;  /* 0x7C */
    __IO uint32_t CRD_ANGLE;  /* 0x80 */
    __IO uint32_t CRD_COS;    /* 0x84 */
    __IO uint32_t CRD_SIN;    /* 0x88 */
    __IO uint32_t CRD_IE;     /* 0x8C */
    __IO uint32_t CRD_FLG;    /* 0x90 */
    __IO uint32_t INTP_LEN;   /* 0x94 */
    __IO uint32_t INTP_LOC;   /* 0x98 */
    __IO uint32_t INTP_STEP;  /* 0x9C */
} DSP_TypeDef;

#if defined(__CC_ARM)
#pragma no_anon_unions
#endif

/*@}*/ /* end of group RN8XXX_V2_Peripherals */

/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/** @addtogroup RN8XXX_V2_MemoryMap RN8XXX_V2 Memory Mapping
  @{
*/

/* Peripheral and MEMORY base address */
#define LS_PERIPH_BASE (0x40000000)
#define HS_PERIPH_BASE (0x50000000)
#define HSP_BASE HS_PERIPH_BASE
#define LSP_BASE LS_PERIPH_BASE
#define BB_OFFSET 0x02000000

// AHB base address
#define ROM_TABLE_BASE 0xF000_0000
#define GPIO_BASE (HSP_BASE)
#define HSP_BB_BASE (HSP_BASE + BB_OFFSET)
#define GPIO_BB_BASE (HSP_BB_BASE)

/* Peripheral memory map */
// APB base address
#define UART0_BASE (LSP_BASE)
#define UART1_BASE (LSP_BASE + 0x04000)
#define UART2_BASE (LSP_BASE + 0x08000)
#define UART3_BASE (LSP_BASE + 0x0C000)
#define UART4_BASE (LSP_BASE + 0x18000)
#define UART5_BASE (LSP_BASE + 0x1C000)
#define TC0_BASE (LSP_BASE + 0x10000)
#define TC1_BASE (LSP_BASE + 0x14000)
#define SPI0_BASE (LSP_BASE + 0x20000)
#define SPI1_BASE (LSP_BASE + 0x50000)
#define SPI2_BASE (LSP_BASE + 0x54000)
#define SPI3_BASE (LSP_BASE + 0x58000)
#define I2C_BASE (LSP_BASE + 0x24000)
#define KBI_BASE (LSP_BASE + 0x28000)
#define MADC_BASE (LSP_BASE + 0x2C000)
#define WDT_BASE (LSP_BASE + 0x30000)
#define SYSCTL_BASE (LSP_BASE + 0x34000)
#define ISO7816_BASE (LSP_BASE + 0x38000)
#define RTC_BASE (LSP_BASE + 0x3C000)
#define INTC_BASE (LSP_BASE + 0x44000)
#define LCD_BASE (LSP_BASE + 0x48000)
#define D2F_BASE (LSP_BASE + 0x5c000)
#define SIMP_TC_BASE (LSP_BASE + 0x60000)
#define DSP_BASE (LSP_BASE + 0x64000)
#define M2M_BASE (LSP_BASE + 0x68000)

//#endif
/*@}*/ /* end of group RN8XXX_V2_MemoryMap */

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/

#define GPIO ((GPIO_TypeDef *)GPIO_BASE)
#define GPIO_BB ((GPIO_TypeDef *)GPIO_BB_BASE)

#define UART0 ((UART_TypeDef *)UART0_BASE)
#define UART1 ((UART_TypeDef *)UART1_BASE)
#define UART2 ((UART_TypeDef *)UART2_BASE)
#define UART3 ((UART_TypeDef *)UART3_BASE)
#define UART4 ((UART_TypeDef *)UART4_BASE)
#define UART5 ((UART_TypeDef *)UART5_BASE)
#define TC0 ((TC_TypeDef *)TC0_BASE)
#define TC1 ((TC_TypeDef *)TC1_BASE)
#define SPI ((SPI_TypeDef *)SPI0_BASE)
#define SPI1 ((SPI_TypeDef *)SPI1_BASE)
#define SPI2 ((SPI_TypeDef *)SPI2_BASE)
#define SPI3 ((SPI_TypeDef *)SPI3_BASE)
#define I2C ((I2C_TypeDef *)I2C_BASE)
#define KBI ((KBI_TypeDef *)KBI_BASE)
#define MADC ((MADC_TypeDef *)MADC_BASE)
#define WDT ((WDT_TypeDef *)WDT_BASE)
#define SYSCTL ((SYSCTL_TypeDef *)SYSCTL_BASE)
#define ISO7816 ((ISO7816_TypeDef *)ISO7816_BASE)
#define RTC ((RTC_TypeDef *)RTC_BASE)
#define INTC ((INTC_TypeDef *)INTC_BASE)
#define LCD ((LCD_TypeDef *)LCD_BASE)
#define SIMP_TC ((SIMP_TC_TypeDef *)SIMP_TC_BASE)
#define D2F ((D2F_TypeDef *)D2F_BASE)
#define M2M ((M2M_TypeDef *)M2M_BASE)
#define DSP ((DSP_TypeDef *)DSP_BASE)

/* bit operations */
#define REG32(addr) (*(volatile uint32_t *)(uint32_t)(addr))
#define REG16(addr) (*(volatile uint16_t *)(uint32_t)(addr))
#define REG8(addr) (*(volatile uint8_t *)(uint32_t)(addr))
#define BIT(x) ((uint32_t)((uint32_t)0x01U << (x)))
#define BITS(start, end) ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(end))))
#define GET_BITS(regval, start, end) (((regval)&BITS((start), (end))) >> (start))

/*@}*/ /* end of group RN8XXX_V2_PeripheralDecl */

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

#ifdef __cplusplus
}
#endif

#endif // __RN8XXX_V2_H__

// -*- r32775 -*-
