/*!
    \file    RN8XXX_V2_SYSC.h
    \brief   definitions for the SYSC

    \version 2023,03,07, V1.0.0, firmware for rn8xxx_v2
*/
#ifndef RN8XXX_V2_SYSC_H
#define RN8XXX_V2_SYSC_H

#include "RN8XXX_V2.h"

/* bits definitions */
/* OSC_CTRL1 */
#define OSC_CTRL1_PLL_PD              BIT(0)        /*!< PLL disable bit (=1 disable, =0 enable) */
#define OSC_CTRL1_IRCH_PD             BIT(1)        /*!< internal RCH oscillator disable bit (=1 disable, =0 enable)*/
#define OSC_CTRL1_PLL_HOSC_DIV        BITS(2,3)     /*!< system clock division(applicable for high frequency mode(PLL or HOSC))*/
#define OSC_CTRL1_LOSC_ON             BIT(4)        /*!< system clock flag of losc or RCL */
#define OSC_CTRL1_IRCH_ON             BIT(5)        /*!< system clock flag of internal RC oscillator*/
#define OSC_CTRL1_PLL_HOSC_ON         BIT(6)        /*!< system clock flag of external high-frequence oscillator or internal PLL*/
#define OSC_CTRL1_PLL_LOCK            BIT(7)        /*!< PLL locked status*/
#define OSC_CTRL1_SYSCLK_STAT         BITS(8,10)    /*!< system clock freq status flag */
#define OSC_CTRL1_LOSC_CLOCK_FLAG     BIT(11)       /*!< LOSC ON status flag*/
#define OSC_CTRL1_PLL_CLOCK_FLAG      BIT(12)       /*!< PLL ON status flag */
#define OSC_CTRL1_IRCH_CLOCK_FLAG     BIT(13)       /*!< internal RCH ON status flag*/
#define OSC_CTRL1_IRCL_CLOCK_FLAG     BIT(14)       /*!< internal RCL ON status flag*/
#define OSC_CTRL1_HOSC_CLOCK_FLAG     BIT(15)       /*!< HOSC ON status flag*/

/* SYS_MODE */
#define SYS_MODE_MODE             BITS(0,3)      /*!< system clock configuration bits*/
#define SYS_MODE_FLASH_BUSY       BIT(5)         /*!< FLASH busy status flag (=1 busy, =0 idle)*/

/* SYS_PD */
#define SYS_PD_LVD_PD             BIT(3)         /*!< LVD power down switch (=1 power down, =0 power on)*/
#define SYS_PD_CMP1_PD            BIT(4)         /*!< power down switch of Comparator No.1 (=1 power down, =0 power on) */
#define SYS_PD_CMP2_PD            BIT(5)         /*!< power down switch of Comparator No.2 (=1 power down, =0 power on) */
#define SYS_PD_PWD_CMP1R          BIT(8)         /*!< switch of CMP1 internal simpling resistor(=1 register off, =0 register on)*/
#define SYS_PD_PWD_CMP2R          BIT(9)         /*!< switch of CMP2 internal simpling resistor(=1 register off, =0 register on)*/
#define SYS_PD_hysen_cmp1         BIT(10)        /*!< CMP1 hysteresis switch*/
#define SYS_PD_hysen_cmp2         BIT(11)        /*!< CMP2 hysteresis switch*/
#define SYS_PD_vsel_bor5          BIT(16)        /*!< BOR5 voltage threshold */

/* OSC_CTRL2 */
#define OSC_CTRL2_HOSC_FREQ        BITS(0,2)       /*!< freq of external high-frequence oscillator */
#define OSC_CTRL2_HOSC_PD          BIT(3)          /*!< HOSC disable bit (=1 disable HOSC, =0 enable HOSC) */
#define OSC_CTRL2_PLL_HOSC_SEL     BIT(4)          /*!< system clock selection for full speed mode */
#define OSC_CTRL2_PLL_FREQ         BITS(5,7)       /*!< PLL frenquency selection*/
#define OSC_CTRL2_RCL_STB          BIT(12)         /*!< system clock selection for low frequency mode */
#define OSC_CTRL2_RCL_LCD          BIT(13)         /*!< clock selection (RCL/LOSC) for LCD */
#define OSC_CTRL2_RCL_LOSC_FLT_SEL BIT(15)         /*!< clock selection (RCL/LOSC) for KBI filter */
#define OSC_CTRL2_RCH_FREQ         BIT(16,18)      /*!< RCH frequency selection */
#define OSC_CTRL2_RCL_VBAT_SEL     BIT(19)         /*!< switch on RCL clock for VBAT (=1 switch on, =0 switch off )*/

/* SYS_RST */
#define SYS_RST_LOCKUP_ENRST      BIT(2)         /*!< selection for the connection of lockup and system reset(=1 lock up cause system reset, =0 lock up can not cause system reset)*/
#define SYS_RST_POWEROK_RST       BIT(5)         /*!< power-on reset flag (=1 reset occured)*/
#define SYS_RST_PIN_RST           BIT(6)         /*!< external pin reset flag (=1 reset occured) */
#define SYS_RST_WDT_RST           BIT(7)         /*!< WDT reset flag (=1 reset occured) */
#define SYS_RST_MCU_RST           BIT(8)         /*!< CPU reset flag(software or LOCKUP) (=1 reset occured) */
#define SYS_RST_boi_vbat_flag     BIT(9)         /*!< vbat power down flag(=1 vbat power down occured) */
#define SYS_RST_boi_vbat_ie       BIT(10)        /*!< vbat area power down interrupt control(=1 enable interupt, =0 disable)*/

/* MAP_CTRL */
#define MAP_CTRL_REMAP            BITS(0,2)      /*!< system remap address configuration*/

/* MOD0_EN */
#define MOD0_EN_EMB_EN            BIT(3)         /*!< EMB enable  */
#define MOD0_EN_TC0_EN            BIT(4)         /*!< TC0 enable */
#define MOD0_EN_TC1_EN            BIT(5)         /*!< TC1 enable */
#define MOD0_EN_UART4_EN          BIT(6)         /*!< uart4 enable */
#define MOD0_EN_UART5_EN          BIT(7)         /*!< uart5 enable */
#define MOD0_EN_UART0_EN          BIT(8)         /*!< uart0 enable */
#define MOD0_EN_UART1_EN          BIT(9)         /*!< uart1 enable */
#define MOD0_EN_UART2_EN          BIT(10)        /*!< uart2 enable */
#define MOD0_EN_UART3_EN          BIT(11)        /*!< uart3 enable */
#define MOD0_EN_UART38K_EN        BIT(12)        /*!< UART 38KHz infra-red moduling clock enable */
#define MOD0_EN_ISO7816_EN        BIT(13)        /*!< ISO7816 enable */
#define MOD0_EN_I2C_EN            BIT(14)        /*!< I2C enable */
#define MOD0_EN_SPI0_EN           BIT(15)        /*!< SPI0 enable */
#define MOD0_EN_SPI1_EN           BIT(16)        /*!< SPI1 enable */
#define MOD0_EN_SPI2_EN           BIT(17)        /*!< SPI2 enable */
#define MOD0_EN_SPI3_EN           BIT(18)        /*!< SPI3 enable */
#define MOD0_EN_SIMP_TC_EN        BIT(20)        /*!< SIMP_TC enable */

/* MOD1_EN */
#define MOD1_EN_GPIO_EN           BIT(5)        /*!< GPIO enable */
#define MOD1_EN_LCD_EN            BIT(6)        /*!< LCD enable */
#define MOD1_EN_WDT_EN            BIT(9)        /*!< WDT enable */
#define MOD1_EN_RTC_SAR_EN        BIT(10)       /*!< RTC/SAR enable */
#define MOD1_EN_CMPLVD_EN         BIT(11)       /*!< CMPLVD enable */
#define MOD1_EN_D2F_EN            BIT(13)       /*!< D2F enable */
#define MOD1_EN_M2M_EN            BIT(15)       /*!< M2M enable */

/* INTC_EN */
#define INTC_EN_INTC0_EN          BIT(0)        /*!< INTC channel 0 enable */
#define INTC_EN_INTC1_EN          BIT(1)        /*!< INTC channel 1 enable*/
#define INTC_EN_INTC2_EN          BIT(2)        /*!< INTC channel 2 enable*/
#define INTC_EN_INTC3_EN          BIT(3)        /*!< INTC channel 3 enable*/
#define INTC_EN_INTC4_EN          BIT(4)        /*!< INTC channel 4 enable*/
#define INTC_EN_INTC5_EN          BIT(5)        /*!< INTC channel 5 enable*/
#define INTC_EN_INTC6_EN          BIT(6)        /*!< INTC channel 6 enable*/
#define INTC_EN_INTC7_EN          BIT(7)        /*!< INTC channel 7 enable*/
#define INTC_EN_INTC_EN           BIT(8)        /*!< INTC enable*/

/* KBI_EN */
#define KBI_EN_KBI0_EN            BIT(0)        /*!< KBI channel 0 enable */
#define KBI_EN_KBI1_EN            BIT(1)        /*!< KBI channel 1 enable */
#define KBI_EN_KBI2_EN            BIT(2)        /*!< KBI channel 2 enable */
#define KBI_EN_KBI3_EN            BIT(3)        /*!< KBI channel 3 enable */
#define KBI_EN_KBI4_EN            BIT(4)        /*!< KBI channel 4 enable */
#define KBI_EN_KBI5_EN            BIT(5)        /*!< KBI channel 5 enable */
#define KBI_EN_KBI6_EN            BIT(6)        /*!< KBI channel 6 enable */
#define KBI_EN_KBI7_EN            BIT(7)        /*!< KBI channel 7 enable */
#define KBI_EN_KBI_EN             BIT(8)        /*!< KBI enable */

/* SYS_PS */
#define SYS_PS_SYS_PSW            BITS(0,7)       /*!< system control register set access protection*/

/* IRFR_CTL */
#define IRFR_CTL_INFRARED_CYCLE   BITS(0,5)       /*!< infra-red modulation clock division */

/* DIE_VER */
#define DIE_VER_VER               BITS(0,7)       /*!< DIE_VER  chip version and die version*/

/* TRIM_CFG */
#define TRIM_CFG_REF_CNT          BITS(0,19)      /*!< reference clock counter value */
#define TRIM_CFG_REF_SEL          BITS(24,25)     /*!< reference clock selection */
#define TRIM_CFG_CAL_SEL          BIT(26)         /*!< calculated clock selection*/
#define TRIM_CFG_DONE_IE          BIT(27)         /*!< calculation down interrupt enable bit */
#define TRIM_CFG_OV_IE            BIT(28)         /*!< calculation overflow interrupt enable bit */
#define TRIM_CFG_RCH_SEL          BIT(29)         /*!< selection of the calculated RCH clock source */

/* TRIM_START */
#define TRIM_START_CAL_CNT        BITS(0,19)      /*!< counter value of the calculated clock */
#define TRIM_START_CAL_DONE       BIT(24)         /*!< clock trim finish flag */
#define TRIM_START_CAL_OV         BIT(25)         /*!< clock trim counter overflow flag */
#define TRIM_START_START          BIT(26)         /*!< start clock trim */
#define TRIM_START_STOP           BIT(27)         /*!< stop clock trim */

/* constants definitions */
/* system clock divison factor only valid for PLL/HOSC  */
#define PLL_HOSC_DIV(regval) (OSC_CTRL1_PLL_HOSC_DIV & ((uint32_t)(regval) << 2))
#define PLL_HOSC_DIV1         PLL_HOSC_DIV(0)       /*!< when PLL/HOSC selected as system clock not devided  */
#define PLL_HOSC_DIV2         PLL_HOSC_DIV(1)       /*!< when PLL/HOSC selected as system clock devided by 2  */
#define PLL_HOSC_DIV4         PLL_HOSC_DIV(2)       /*!< when PLL/HOSC selected as system clock devided by 4  */
#define PLL_HOSC_DIV8         PLL_HOSC_DIV(3)       /*!< when PLL/HOSC selected as system clock devided by 8  */

/* system clock freq state*/
#define SYSCLK_STAT(regval) (OSC_CTRL1_SYSCLK_STAT & ((uint32_t)(regval) << 8))
#define SYSCLK_STAT_7M4       SYSCLK_STAT(0)        /*!< current system clock freq = 7.3728MHz */
#define SYSCLK_STAT_3M6       SYSCLK_STAT(1)        /*!< current system clock freq = 3.6864MHz */
#define SYSCLK_STAT_1M8       SYSCLK_STAT(2)        /*!< current system clock freq = 1.8432MHz */
#define SYSCLK_STAT_32K       SYSCLK_STAT(3)        /*!< current system clock freq = 32.768KHz */
#define SYSCLK_STAT_14M7      SYSCLK_STAT(4)        /*!< current system clock freq = 14.7456Mhz */
#define SYSCLK_STAT_29M5      SYSCLK_STAT(5)        /*!< current system clock freq = 29.4912Mhz */

/* system mode selection */
#define SYS_MODE_CFG(regval) (SYS_MODE_MODE & ((uint32_t)(regval) << 0))
#define SYS_MODE_HCM          SYS_MODE_CFG(0xD)     /*!< select HCM mode as system mode */
#define SYS_MODE_RCM          SYS_MODE_CFG(0xE)     /*!< select RCM mode as system mode */
#define SYS_MODE_LCM          SYS_MODE_CFG(0xF)     /*!< select LCM mode as system mode */

/* SYS_PD_PWD_CMP1R switch of CMP1 resistor */
#define SYS_PD_PWD_CMP1R_ON     ((uint32_t)0x00000000U)     /*!< CMP1 internal simpling resistor on */
#define SYS_PD_PWD_CMP1R_OFF    SYS_PD_PWD_CMP1R            /*!< CMP1 internal simpling resistor off */

/* SYS_PD_PWD_CMP2R switch of CMP2 resistor */
#define SYS_PD_PWD_CMP2R_ON     ((uint32_t)0x00000000U)     /*!< CMP2 internal simpling resistor on */
#define SYS_PD_PWD_CMP2R_OFF    SYS_PD_PWD_CMP2R            /*!< CMP2 internal simpling resistor off */

/* SYS_PD_hysen_cmp1 CMP1 switch of hysteresis */
#define SYS_PD_hysen_cmp1_ON    SYS_PD_hysen_cmp1           /*!< CMP1 hysteresis on */
#define SYS_PD_hysen_cmp1_OFF   ((uint32_t)0x00000000U)     /*!< CMP1 hysteresis off */

/* SYS_PD_hysen_cmp2 CMP2 switch of hysteresis */
#define SYS_PD_hysen_cmp2_ON    SYS_PD_hysen_cmp2           /*!< CMP2 hysteresis on */
#define SYS_PD_hysen_cmp2_OFF   ((uint32_t)0x00000000U)     /*!< CMP2 hysteresis off */

/* SYS_PD_vsel_bor5 switch of BOR5 level */
#define SYS_PD_vsel_bor5_LOW    SYS_PD_vsel_bor5            /*!< BOR5 low level(2.1/1.8V) */
#define SYS_PD_vsel_bor5_HIGH   ((uint32_t)0x00000000U)     /*!< BOR5 high level(2.5/2.2V) */

/* external high-frequence oscillator freq selection */
#define HOSC_FREQ_CFG(regval) (OSC_CTRL2_HOSC_FREQ & ((uint32_t)(regval) << 0))
#define HOSC_FREQ_7M4         HOSC_FREQ_CFG(0)       /*!< external high-frequence oscillator freq = 7.3728MHz */
#define HOSC_FREQ_14M7        HOSC_FREQ_CFG(1)       /*!< external high-frequence oscillator freq = 14.7456Mhz  */
#define HOSC_FREQ_29M5        HOSC_FREQ_CFG(2)       /*!< external high-frequence oscillator freq = 29.4912Mhz  */
#define HOSC_FREQ_29M5_PLUS   HOSC_FREQ_CFG(3)       /*!< external high-frequence oscillator freq = 29.4912Mhz (driver enhanced)*/

/* OSC_CTRL2_PLL_HOSC_SEL system clock selection for full speed mode*/
#define OSC_CTRL2_PLL_HOSC_SEL_PLL     ((uint32_t)0x00000000U)     /*!< select PLL  as system clock for full speed mode  */
#define OSC_CTRL2_PLL_HOSC_SEL_HOSC    OSC_CTRL2_PLL_HOSC_SEL      /*!< select HOSC as system clock for full speed mode  */

/*OSC_CTRL2_RCL_STB system clock selection for low frequency mode*/
#define OSC_CTRL2_RCL_STB_RCL    OSC_CTRL2_RCL_STB          /*!< select RCL  as system clock for low frequency mode */
#define OSC_CTRL2_RCL_STB_LOSC   ((uint32_t)0x00000000U)    /*!< select LOSC as system clock for low frequency mode */

/* OSC_CTRL2_RCL_LCD  LCD clock selection */
#define OSC_CTRL2_RCL_LCD_RCL    OSC_CTRL2_RCL_LCD          /*!< select RCL  as LCD clock */
#define OSC_CTRL2_RCL_LCD_LOSC   ((uint32_t)0x00000000U)    /*!< select LOSC as LCD clock */

/* OSC_CTRL2_RCL_LOSC_FLT_SEL  KBI filter clock selection */
#define OSC_CTRL2_KBI_FLT_SEL_RCL     OSC_CTRL2_RCL_LOSC_FLT_SEL    /*!< select RCL  as KBI filter clock */
#define OSC_CTRL2_KBI_FLT_SEL_LOSC    ((uint32_t)0x00000000U)       /*!< select LOSC as KBI filter clock */

/* PLL freq selection */
#define PLL_FREQ_CFG(regval) (OSC_CTRL2_PLL_FREQ & ((uint32_t)(regval) << 5))
#define PLL_FREQ_7M4          PLL_FREQ_CFG(0)        /*!< PLL freq select 7.3728MHz  */
#define PLL_FREQ_14M7         PLL_FREQ_CFG(1)        /*!< PLL freq select 14.7456Mhz */
#define PLL_FREQ_29M5         PLL_FREQ_CFG(2)        /*!< PLL freq select 29.4912Mhz */

/* RCH frequency selection */
#define RCH_FREQ_CFG(regval) (OSC_CTRL2_RCH_FREQ & ((uint32_t)(regval) << 16))
#define RCH_FREQ_1M8          RCH_FREQ_CFG(0)       /*!< internal RCH freq select 1.8432MHz */
#define RCH_FREQ_3M6          RCH_FREQ_CFG(1)       /*!< internal RCH freq select 3.6864MHz */
#define RCH_FREQ_7M4          RCH_FREQ_CFG(2)       /*!< internal RCH freq select 7.3728MHz */
#define RCH_FREQ_14M7         RCH_FREQ_CFG(3)       /*!< internal RCH freq select 14.7456Mhz */
#define RCH_FREQ_29M5         RCH_FREQ_CFG(4)       /*!< internal RCH freq select 29.4912Mhz */

/* switch of RCL to VBAT */
#define RCL_VBAT_SEL_ON    OSC_CTRL2_RCL_VBAT_SEL      /*!< open rcl to vbat channel */
#define RCL_VBAT_SEL_OFF   ((uint32_t)0x00000000U)     /*!< close rcl to vbat channel */

/* REMAP mode defination */
#define REMAP(regval) (MAP_CTRL_REMAP & ((uint32_t)(regval) << 0))
#define MAP_CTRL_REMAP0       REMAP(0)        /*!< FLASH mapped at address 0 */
#define MAP_CTRL_REMAP1       REMAP(1)        /*!< FLASH mapped at address 1/2 (2nd FLASH at 0x0, 1st FLASH at 0x4000 and bootload at 0 */
#define MAP_CTRL_REMAP2       REMAP(2)        /*!< FLASH switch mapping address with SRAM(FLASH at 0x10000000 and SRAM at 0) */
#define MAP_CTRL_REMAP4       REMAP(4)        /*!< FLASH mapped at address 1/2 total memory capacity(only support less than 512KB */

/* SYS_PS SYSCTRL registers write control defination */
#define SYS_PSW(regval) (SYS_PS_SYS_PSW & ((uint32_t)(regval) << 0))
#define SYS_PS_WRITEACCESS_ENABLE       SYS_PSW(0x82)      /*!< SYSCTRL registers offset adderess at 0x00-0x28 and 0x78-0x80 write access enable */
#define SYS_PS_WRITEACCESS_DISABLE      SYS_PSW(0x55)      /*!< SYSCTRL registers offset adderess at 0x00-0x28 and 0x78-0x80 write access disable */

/* TRIM reference clock selection */
#define TRIM_REF_SEL(regval) (TRIM_CFG_REF_SEL & ((uint32_t)(regval) << 24))
#define TRIM_REF_SEL_LOSC        TRIM_REF_SEL(0)     /*!< select LOSC as reference  clock */
#define TRIM_REF_SEL_HOSC        TRIM_REF_SEL(1)     /*!< select HOSC as reference  clock */
#define TRIM_REF_SEL_RCH         TRIM_REF_SEL(2)     /*!< select RCH  as reference  clock */
#define TRIM_REF_SEL_RCL         TRIM_REF_SEL(3)     /*!< select RCL  as reference  clock */

/* calculated clock selection CAL_CLK_SEL */
#define TRIM_CAL_SEL_RCL        TRIM_CFG_CAL_SEL            /*!< select RCL as calculated  clock */
#define TRIM_CAL_SEL_RCH        ((uint32_t)0x00000000U)     /*!< select RCH as calculated  clock */

/* TRIM_CFG_RCH_SEL RCH source selection */
#define TRIM_CFG_RCH_SEL_VCC    ((uint32_t)0x00000000U)    /*!< select RCH_VCC_CLK as calculated RCH clock source*/
#define TRIM_CFG_RCH_SEL_VBAT   TRIM_CFG_RCH_SEL           /*!< select RCH_VBAT_CLK as calculated RCH clock source*/

#endif /* RN8XXX_V2_SYSC_H */

// -*- r32775 -*-
