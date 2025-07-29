/******************************************************************************
 * @file     sysctrl_reg.h
 * @brief    System control driver header file for RN821x series SOC
 * @author   Renergy Technology
 * @version  V1.01
 * @date V1.01 2017-06-23 modify address define of SYS_TC_BASE from (0x52000000 + 0x10000  ) to (0x50000000 + 0x10000) to avoid err change of p00 p01
 *          V1.00 2017-05-03 INITIAL
 *
 * @note
 * Copyright (C) 2017, Renergy Technology Inc. All rights reserved.
 *
 *
 ******************************************************************************/
#ifndef SYSCTRL_REG_H
#define SYSCTRL_REG_H

/* Register define */
#define TEST_CTL         (0x40034040U)
#define ANA_ADC          (0x40034048U)
#define ANA_CLK1         (0x4003404cU)
#define ANA_CLK2         (0x40034050U)
#define ANA_LDO          (0x40034054U)
#define ANA_BGR          (0x40034058U)
#define ANA_PSW          (0x4003405cU)
#define ANA_PWR          (0x40034068U)
#define ANA_CLK3         (0x4003406cU)
#define ANA_SYS          (0x40034070U)
#define ANA_ULBGR1       (0x40034098U)
#define ANA_ULBGR2       (0x4003409cU)
#define ANA_LURLS1       (0x400340a0U)

#define TRNG_CTRL        (0x5000c3c0U)

#define MADC_TPSCTRL     (0x4002c018U)
#define MADC_TPSCTRL_V2  (0x4002c050U)
#define MADC_ADTEST      (0x4002c01cU)
#define MADC_ADTEST_V2   (0x4002c04cU)
#define LOSC_CFG2        (0x4003c070U)
#define MADC_ANABGR      (0x4002c020U)
#define MADC_ANALDO      (0x4002c028U)
#define MADC_ANARCH      (0x4002c02cU)
#define MADC_SARCTRL2    (0x4002c030U)
#define MADC_ANABGR_V2   (0x4002c054U)
#define MADC_ANALDO_V2   (0x4002c060U)
#define MADC_ANARCH_V2   (0x4002c064U)
#define MADC_SARCTRL2_V2 (0x4002c048U)

#define RTC_MODE         (0x4003c044U)
#define RTC_ALPHAL       (0x4003c04cU)
#define RTC_ALPHAH       (0x4003c050U)
#define RTC_XT0          (0x4003c054U)
#define RTC_BETA         (0x4003c05cU)
#define RTC_TADJ         (0x4003c058U)
#define RTC_ZT           (0x4003c060U)
#define WDT_EN           (0x40030000U)
#define WDT_CTRL         (0x40030004U)
#define WDT_HALT         (0x40030014U)
#define WDT_STBY         (0x40030018U)

#define OSC_CTRL1        (*(volatile unsigned int *)(0x40034000U))
#define SYS_MODE         (*(volatile unsigned int *)(0x40034004U))
#define OSC_CTRL2        (*(volatile unsigned int *)(0x40034010U))
#define MAP_CTL          (*(volatile unsigned int *)(0x40034018U))
#define MOD0_EN          (*(volatile unsigned int *)(0x4003401cU))
#define MOD1_EN          (*(volatile unsigned int *)(0x40034020U))
#define SYS_PS           (*(volatile unsigned int *)(0x40034030U))
#define DIE_VER          (*(volatile unsigned int *)(0x40034074U))
#define DIE_VER2         (*(volatile unsigned int *)(0x40034090U))
#define TRIM_CFG1        (*(volatile unsigned int *)(0x40034078U))
#define TRIM_START       (*(volatile unsigned int *)(0x4003407cU))
#define LDO_MODE         (*(volatile unsigned int *)(0x40034080U))
#define LDO_MODE_V2      (*(volatile unsigned int *)(0x40034054U))

#define RTC_CTRL         (*(volatile unsigned int *)(0x4003c000U))
#define RTC_TEMP         (*(volatile unsigned int *)(0x4003c03cU))
#define RTC_PS           (*(volatile unsigned int *)(0x4003c040U))
#define RTC_DOTA         (*(volatile unsigned int *)(0x4003c048U))
#define RTC_LOSC_CFG1    (*(volatile unsigned int *)(0x4003c06cU))
#define RTC_IOEN         (*(volatile unsigned int *)(0x4003c088U))
#define RTC_IOMODE       (*(volatile unsigned int *)(0x4003c08cU))
#define RTC_CALPS        (*(volatile unsigned int *)(0x4003c0ccU))
#define RTC_MODE1        (*(volatile unsigned int *)(0x4003c130U))
/*#define RTC_DOTATBL(i)   (*(volatile unsigned int *)(0x4003c0d0U + 4U * (i)))*/
typedef struct
{
    volatile unsigned int dota[10];
} dota_table_t;
#define RTC_DOTATBL      ((dota_table_t *)0x4003c0d0U)
#define RTC_DOTATBL0     (*(volatile unsigned int *)(0x4003c0d0U))
#define RTC_DOTATBL1     (*(volatile unsigned int *)(0x4003c0d4U))
#define RTC_DOTATBL2     (*(volatile unsigned int *)(0x4003c0d8U))
#define RTC_DOTATBL3     (*(volatile unsigned int *)(0x4003c0dcU))
#define RTC_DOTATBL4     (*(volatile unsigned int *)(0x4003c0e0U))
#define RTC_DOTATBL5     (*(volatile unsigned int *)(0x4003c0e4U))
#define RTC_DOTATBL6     (*(volatile unsigned int *)(0x4003c0e8U))
#define RTC_DOTATBL7     (*(volatile unsigned int *)(0x4003c0ecU))
#define RTC_DOTATBL8     (*(volatile unsigned int *)(0x4003c0f0U))
#define RTC_DOTATBL9     (*(volatile unsigned int *)(0x4003c0f4U))
#define MADC_SAR_CTL     (*(volatile unsigned int *)(0x4002c000U))
#define MADC_SAR_START   (*(volatile unsigned int *)(0x4002c004U))
#define MADC_SAR_STATUS  (*(volatile unsigned int *)(0x4002c008U))
#define MADC_SAR_DAT     (*(volatile unsigned int *)(0x4002c00cU))
#define MADC_SAR_DAT2    (*(volatile unsigned int *)(0x4002c01cU))
#define MADC_ANA_CTL     (*(volatile unsigned int *)(0x4002c024U))
#define MADC_ANA_TEST    (*(volatile unsigned int *)(0x4002c034U))
#define MADC_ANA_PAD     (*(volatile unsigned int *)(0x4002c03cU))
#define MADC_ANA_RST     (*(volatile unsigned int *)(0x4002c040U))
#define ANA_PS           (*(volatile unsigned int *)(0x4002c044U))
#define MADC_ANA_CTL_V2  (*(volatile unsigned int *)(0x4002c058U))
#define MADC_ANA_CTL2_V2 (*(volatile unsigned int *)(0x4002c05cU))
#define MADC_ANA_TEST_V2 (*(volatile unsigned int *)(0x4002c068U))

#define SYSTICK_CTRL     (*(volatile unsigned int *)(0xe000e010U))
#define SYSTICK_LOAD     (*(volatile unsigned int *)(0xe000e014U))
#define SYSTICK_VAL      (*(volatile unsigned int *)(0xe000e018U))

#define SYSTC_CTRL       (*(volatile unsigned int *)(0x50010000U))
#define SYSTC_LOAD       (*(volatile unsigned int *)(0x50010004U))
#define SYSTC_VAL        (*(volatile unsigned int *)(0x50010008U))

#define GPIO_PCA1        (*(volatile unsigned int *)(0x5000000cU))

#define WDT_PS           (*(volatile unsigned int *)(0x40030008U))

#define MEM32(addr)      (*(volatile unsigned int *)(addr))
#define MEM16(addr)      (*(volatile unsigned short *)(addr))

/* Register define */
#define FEED_WDT (MEM32(WDT_EN) = 0xbbU)

/* for RA9103A/D */
#define FL_TW_32K_98NS  (0U)
#define FL_TW_1M_98NS   (0U)
#define FL_TW_3M_98NS   (0U)
#define FL_TW_7M_98NS   (2U)
#define FL_TW_14M_98NS  (2U)
#define FL_TW_29M_98NS  (5U)

/* for RA9103C/E/F */
#define FL_TW_32K_198NS  (0U)
#define FL_TW_1M_198NS   (0U)
#define FL_TW_3M_198NS   (1U)
#define FL_TW_7M_198NS   (2U)
#define FL_TW_14M_198NS  (4U)
#define FL_TW_29M_198NS  (8U)

#define EE_TW_32K_98NS   (0U)
#define EE_TW_1M_98NS    (0U)
#define EE_TW_3M_98NS    (0U)
#define EE_TW_7M_98NS    (1U)
#define EE_TW_14M_98NS   (2U)
#define EE_TW_29M_98NS   (5U)

#define EE_TW_32K_198NS  (0U)
#define EE_TW_1M_198NS   (0U)
#define EE_TW_3M_198NS   (1U)
#define EE_TW_7M_198NS   (2U)
#define EE_TW_14M_198NS  (5U)
#define EE_TW_29M_198NS  (10U)

/* for RA9701A */
#define FL_TW_32K_V2  (0U)
#define FL_TW_1M_V2   (0U)
#define FL_TW_3M_V2   (0U)
#define FL_TW_7M_V2   (0U)
#define FL_TW_14M_V2  (0U)
#define FL_TW_29M_V2  (1U)

#define SPL_TW_32K_ADDR (0x88U)
#define SPL_TW_1M_ADDR  (0x8aU)
#define SPL_TW_3M_ADDR  (0x8cU)
#define SPL_TW_7M_ADDR  (0x8eU)
#define SPL_TW_14M_ADDR (0x90U)
#define SPL_TW_29M_ADDR (0x92U)

#endif

// -*- r33840 -*-
