/******************************************************************************
 * @file     sysctrl.c
 * @brief    System control driver source code file for RN821x series SOC
 * @author   Renergy Technology
 * @version  V1.5
 * @date     2018-01-11
 *
 * @note
 * Copyright (C) 2008, Renergy Technology Inc. All rights reserved.
 ******************************************************************************/
#include "rn8xxx_v2_lib.h"
#include "sysctrl_reg.h"
#include "utils.h"

/* IAP command define */
#define IAP_NVRP 0x70U
#define IAP_FW 0x58U
#define IAP_EW 0x59U
#define IAP_NV 0x5aU

#define FLASH_NVM 0x0U
#define EEPROM_NVM 0x1U

/* us unit */
#define PLL_TIMEOUT 3000000U
#define HOSC_TIMEOUT 100000U
#define RCH_TIMEOUT 10000U
#define LOSC_TIMEOUT 3000000U
#define MIP_TIMEOUT 7000U
#define RTC_TIMEOUT 1000U
#define HOSC_CALC_TIMEOUT 10000U
#define LOSC_CALC_TIMEOUT 120U

#define IS_LC_MODE(mode) ((Clock_Losc == (mode)) || (Clock_RCL_32K == (mode)))
#define IS_RC_MODE(mode) ((Clock_RC_1M8 == (mode)) || /*(Clock_RC_3M7 == (mode)) || */(Clock_RC_29M5 == (mode)))
#define IS_PLL_MODE(mode) ((Clock_PLL_7M4 == (mode)) || (Clock_PLL_14M7 == (mode)) || (Clock_PLL_29M5 == (mode)))
#define IS_HOSC_MODE(mode) (Clock_Hosc == (mode))

#define RC_ON  (OSC_CTRL1 &= (~((unsigned int)1U << 1)))
#define RC_OFF (OSC_CTRL1 |= ((unsigned int)1U << 1))
#define PLL_ON (OSC_CTRL1 &= (~((unsigned int)1U << 0)))
#define PLL_OFF (OSC_CTRL1 |= ((unsigned int)1U << 0))
#define HOSC_ON (OSC_CTRL2 &= (~((unsigned int)1U << 3)))
#define HOSC_OFF (OSC_CTRL2 |= ((unsigned int)1U << 3))

typedef enum
{
    LIGHT_MODE = 0,
    HIGH_MODE = 1,
    SAFE_MODE = 2
} ldo_mode_t;

typedef enum
{
    IN_FLASH = 0,
    IN_EEPROM = 1
} spl_type_e;

typedef struct
{
    unsigned int mem_addr;
    unsigned int page_size;
    spl_type_e spl_type;
    unsigned int spl0_offset;
} flash_info_t;

static void setMipTW(unsigned int freq, rn_chipid_t chipid);
static eSysCtrlRet_TypeDef loscCalc(rn_chipid_t chipid);
static eSysCtrlRet_TypeDef loscCheck(rn_chipid_t chipid);
static eSysCtrlRet_TypeDef PllEnable(rn_chipid_t chipid);
static eSysCtrlRet_TypeDef HoscEnable(rn_chipid_t chipid);
static eSysCtrlRet_TypeDef clock_valid_check(eSysCtrlClockMode_TypeDef mode, eSysCtrlClockDiv_TypeDef div, rn_chipid_t chipid);
static unsigned int get_target_freq(eSysCtrlClockMode_TypeDef mode, eSysCtrlClockDiv_TypeDef div);
static void set_ldo_mode(ldo_mode_t ldo_mode, rn_chipid_t chipid);
static eSysCtrlRet_TypeDef sysmodeWrite(eSysCtrlClockMode_TypeDef mode, eSysCtrlClockDiv_TypeDef div, rn_chipid_t chipid, unsigned int cur_freq);
static eSysCtrlRet_TypeDef sysmode_params_check(eSysCtrlClockMode_TypeDef mode, eSysCtrlClockDiv_TypeDef div, rn_chipid_t chipid);
static void mem_cpy(unsigned char dst[], const unsigned char src[], unsigned int len);
static eSysCtrlRet_TypeDef HoscValid(rn_chipid_t chipid);
static void get_flash_info(flash_info_t * fl_info);

static const unsigned int fl_tw_98ns[6];
static const unsigned int fl_tw_198ns[6];
static const unsigned int ee_tw_98ns[6];
static const unsigned int ee_tw_198ns[6];
static const unsigned int fl_tw_v2[6];
static const unsigned int HOSC_CYCLES[4];

static const unsigned int fl_tw_98ns[6] = {FL_TW_32K_98NS, FL_TW_1M_98NS, FL_TW_3M_98NS, FL_TW_7M_98NS, FL_TW_14M_98NS, FL_TW_29M_98NS};
static const unsigned int fl_tw_198ns[6] = {FL_TW_32K_198NS, FL_TW_1M_198NS, FL_TW_3M_198NS, FL_TW_7M_198NS, FL_TW_14M_198NS, FL_TW_29M_198NS};
static const unsigned int ee_tw_98ns[6] = {EE_TW_32K_98NS, EE_TW_1M_98NS, EE_TW_3M_98NS, EE_TW_7M_98NS, EE_TW_14M_98NS, EE_TW_29M_98NS};
static const unsigned int ee_tw_198ns[6] = {EE_TW_32K_198NS, EE_TW_1M_198NS, EE_TW_3M_198NS, EE_TW_7M_198NS, EE_TW_14M_198NS, EE_TW_29M_198NS};
static const unsigned int fl_tw_v2[6] = {FL_TW_32K_V2, FL_TW_1M_V2, FL_TW_3M_V2, FL_TW_7M_V2, FL_TW_14M_V2, FL_TW_29M_V2};
static void setMipTW(unsigned int freq, rn_chipid_t chipid)
{
    volatile unsigned int *fltw_reg_addr;
    volatile unsigned int *eetw_reg_addr = ((void *)0U);
    const unsigned int *eetw_ptemp;
    const unsigned int *fltw_ptemp;
    unsigned int eetw_value;
    unsigned int fltw_value;
    unsigned int spl_valid;
    unsigned int *spl_base;
    unsigned int fl_tw_spl[6];
    unsigned int i;
    unsigned int temp;

    if ((chipid == CHIP_RA9103A) || (chipid == CHIP_RA9103D))
    {
        fltw_reg_addr = (unsigned int *)(getMipAddr(0U) + 0x00800018U);
        eetw_reg_addr = (unsigned int *)(getMipAddr(1U) + 0x00800018U);
        fltw_ptemp = fl_tw_98ns;
        eetw_ptemp = ee_tw_98ns;
    }
    else if ((chipid == CHIP_RA9103E) || (chipid == CHIP_RA9103C))
    {
        fltw_reg_addr = (unsigned int *)(getMipAddr(0U) + 0x00800018U);
        eetw_reg_addr = (unsigned int *)(getMipAddr(1U) + 0x00800018U);
        fltw_ptemp = fl_tw_198ns;
        eetw_ptemp = ee_tw_198ns;
    }
    else if (chipid == CHIP_RA9103F)
    {
        fltw_reg_addr = (unsigned int *)(0x50014040U);
        fltw_ptemp = fl_tw_198ns;
        eetw_ptemp = fl_tw_198ns;
    }
    else if (chipid == CHIP_RA9103G)
    {
        fltw_reg_addr = (unsigned int *)(0x00800040U);
        fltw_ptemp = fl_tw_198ns;
        eetw_ptemp = fl_tw_198ns;
    }
    else/* if ((chipid == CHIP_RA9701A) || (chip_id == CHIP_RA9701A1))*/
    {
        fltw_reg_addr = (unsigned int *)(0x50014014U);
        if (freq == 32768U)
        {
            /* speed up LOSC */
            spl_valid = 0U;
        }
        else
        {
            spl_base = (unsigned int *)(getMipAddr(0U) + 0x00080000U);
            spl_valid = check_spl_valid(spl_base, 512U, 0U);
            if (1U == spl_valid)
            {
                for (i = 0U; i < 6U; i++)
                {
                    temp = (unsigned int)spl_base;
                    temp += (SPL_TW_32K_ADDR + 2U * i);
                    fl_tw_spl[i] = *(volatile unsigned short *)(temp);
                    if (fl_tw_spl[i] > 3U)
                    {
                        spl_valid = 0U;
                        break;
                    }
                }
            }
        }
        fltw_ptemp = (1U == spl_valid) ? fl_tw_spl : fl_tw_v2;
        eetw_ptemp = (1U == spl_valid) ? fl_tw_spl : fl_tw_v2;
    }

    switch (freq)
    {
        case 32768U:
            fltw_value = (*fltw_ptemp) << 16U;
            eetw_value = (*eetw_ptemp) << 16U;
            break;
        case 1843200U:
            fltw_value = (unsigned int)fltw_ptemp;
            fltw_value += 4U;
            fltw_value = *(unsigned int *)(fltw_value) << 16U;
            eetw_value = (unsigned int)eetw_ptemp;
            eetw_value += 4U;
            eetw_value = *(unsigned int *)(eetw_value) << 16U;
            break;
        case 3686400U:
            fltw_value = (unsigned int)fltw_ptemp;
            fltw_value += 8U;
            fltw_value = *(unsigned int *)(fltw_value) << 16U;
            eetw_value = (unsigned int)eetw_ptemp;
            eetw_value += 8U;
            eetw_value = *(unsigned int *)(eetw_value) << 16U;
            break;
        case 7372800U:
            fltw_value = (unsigned int)fltw_ptemp;
            fltw_value += 12U;
            fltw_value = *(unsigned int *)(fltw_value) << 16U;
            eetw_value = (unsigned int)eetw_ptemp;
            eetw_value += 12U;
            eetw_value = *(unsigned int *)(eetw_value) << 16U;
            break;
        case 14745600U:
            fltw_value = (unsigned int)fltw_ptemp;
            fltw_value += 16U;
            fltw_value = *(unsigned int *)(fltw_value) << 16U;
            eetw_value = (unsigned int)eetw_ptemp;
            eetw_value += 16U;
            eetw_value = *(unsigned int *)(eetw_value) << 16U;
            break;
        case 29491200U:
            fltw_value = (unsigned int)fltw_ptemp;
            fltw_value += 20U;
            fltw_value = *(unsigned int *)(fltw_value) << 16U;
            eetw_value = (unsigned int)eetw_ptemp;
            eetw_value += 20U;
            eetw_value = *(unsigned int *)(eetw_value) << 16U;
            break;
        default:
            fltw_value = (unsigned int)fltw_ptemp;
            fltw_value += 4U;
            fltw_value = *(unsigned int *)(fltw_value) << 16U;
            eetw_value = (unsigned int)eetw_ptemp;
            eetw_value += 4U;
            eetw_value = *(unsigned int *)(eetw_value) << 16U;
            break;
    }

    if ((void *)0U != eetw_reg_addr)
    {
        *eetw_reg_addr = eetw_value;
    }

    if ((chipid == CHIP_RA9701A) || (chipid == CHIP_RA9701A1))
    {
        *fltw_reg_addr = (*fltw_reg_addr & (~((unsigned int)0x3U << 2))) | (fltw_value >> 14);
    }
    else
    {
        *fltw_reg_addr = fltw_value;
    }
}

/* use CLK_TRIM to check LOSC */
/* 500ms总时间，每1ms检查losc能否计数超过10个节拍，如是，则认为losc存在，如否，超过500ms总时间后错误返回 */
/* 优化方案：使用LOSC测试RCH
     1ms测试时长，ref_cnt=32，被测时钟RCH离散度按照最低频率计算，即2.5M/25M，再按照10%余量得到calc_cnt=2250/22500
*/
#define  RCH_1MS_CNT    (2250U)
#define  RCH_1MS_CNT_71 (22500U)
/* 超时按照2倍余量 */
#define  RCH_LOSC_CALC_TIMEOUT  (2000U)

static eSysCtrlRet_TypeDef loscCalc(rn_chipid_t chipid)
{
    unsigned int trim_cfg1_bak, trim_start_bak, sys_ps_bak;
    unsigned int temp;
    unsigned int rch_cnt;
    eSysCtrlRet_TypeDef res = SYSCTRL_PASS;

    sys_ps_bak = SYS_PS;
    SYS_PS = 0x82U;
    trim_cfg1_bak = TRIM_CFG1;
    trim_start_bak = TRIM_START;

    /* enable RC to calculate HOSC! */
    if (1U == ((OSC_CTRL1 >> 1) & 1U))
    {
        RC_ON;
    }

    if ((CHIP_RA9701A == chipid) || (CHIP_RA9701A1 == chipid))
    {
        rch_cnt = RCH_1MS_CNT_71;
    }
    else
    {
        rch_cnt = RCH_1MS_CNT;
    }

    TRIM_START = (unsigned int)1U << 27;
    TRIM_CFG1 = ((unsigned int)0U << 26) | ((unsigned int)0U << 24) | ((unsigned int)32U << 0); /* use losc to calc rch */
    TRIM_START = (unsigned int)0x7U << 24;
    usTimeout((unsigned int)(&TRIM_START), ((unsigned int)1U << 24), 0U, RCH_LOSC_CALC_TIMEOUT, chipid);
    temp = TRIM_START & 0xfffffU;
    if ((((TRIM_START >> 24) & 0x1U) == 0x0U) ||
        (temp < rch_cnt))
    {
        res = SYSCTRL_FAIL;
    }
    TRIM_START = (unsigned int)0x1U << 27;
    TRIM_START = (unsigned int)0x3U << 24;

    TRIM_CFG1 = trim_cfg1_bak;
    TRIM_START = trim_start_bak;
    SYS_PS = sys_ps_bak;
    return res;
}

#if 0
/**
 * RA9103:
 * RCH freq=(2.5, 4)Mhz, width=(0.4, 0.25us)
 * 1 losc = (76, 122)*RCH, *2=(38, 183)*RCH
 * 10% losc width=3.05us = 12*RCH(4Mhz)
 *
 * RA9701:
 * ?
 */
#define  LOSC_CNT_MIN  38U
#define  LOSC_CNT_MAX  183U
#define  LOSC_DIFF_MAX 12U
static unsigned int loscCalc_backup(rn_chipid_t chipid)
{
    unsigned int trim_cfg1_bak, trim_start_bak, sys_ps_bak;
    unsigned int temp, losc_avr, losc_max, losc_min, losc_diff;
    unsigned int loops = 0;
    unsigned int res = SYSCTRL_PASS;

    sys_ps_bak = SYS_PS;
    SYS_PS = 0x82U;
    trim_cfg1_bak = TRIM_CFG1;
    trim_start_bak = TRIM_START;

    losc_avr = 0U;
    losc_max = 0U;
    losc_min = 0xffffffU;
    for (loops = 0U; loops < 32U; loops++)
    {
        TRIM_START = 1U << 27;
        TRIM_CFG1 = (0U << 26) | (0U << 24) | (1U << 0); /* use losc(ref) to calc rch(calc) */
        TRIM_START = 0x7U << 24;
        usTimeout((unsigned int)(&TRIM_START), (1U << 24), 0U, LOSC_CALC_TIMEOUT, chipid);
        if (!(TRIM_START & (1U << 24)))
        {
            res = SYSCTRL_FAIL;
            break;
        }
        temp = (TRIM_START & 0xfffffU);
        losc_avr += temp;
        if (losc_max < temp)
        {
            losc_max = temp;
        }
        if (losc_min > temp)
        {
            losc_max = temp;
        }
    }
    if (loops == 32U)
    {
        losc_avr /= 32U;
        losc_diff = losc_max - losc_min;
        if ((losc_avr > LOSC_CNT_MAX) || (losc_avr < LOSC_CNT_MIN) || (losc_diff > LOSC_DIFF_MAX))
        {
            res = SYSCTRL_FAIL;
        }
    }

    TRIM_START = 0x1U << 27;
    TRIM_START = 0x3U << 24;

    TRIM_CFG1 = trim_cfg1_bak;
    TRIM_START = trim_start_bak;
    SYS_PS = sys_ps_bak;
    return res;
}
#endif

static eSysCtrlRet_TypeDef loscCheck(rn_chipid_t chipid)
{
    unsigned int i;
    eSysCtrlRet_TypeDef res = SYSCTRL_FAIL;

    if (chipid != CHIP_RA9103A)
    {
        for (i = 0U; i < 500U; i++)
        {
            if (SYSCTRL_PASS == loscCalc(chipid))
            {
                res = SYSCTRL_PASS;
                break;
            }
            FEED_WDT;
        }
    }
    else
    {
        usTimeout((unsigned int)(&OSC_CTRL1), ((unsigned int)1U << 11), 0U, LOSC_TIMEOUT, chipid); /* wait LOSC flag*/
        if (((OSC_CTRL1 >> 11) & 0x1U) == 0x1U)
        {
            res = SYSCTRL_PASS;
        }
    }
    return res;
}

/* check: PLL lock and LOSC flag(if LOSC pwr-down, check RTC write) */
static eSysCtrlRet_TypeDef PllEnable(rn_chipid_t chipid)
{
    unsigned int flag, osc1_ctrl_bak, osc2_ctrl_bak, sys_ps_bak;
    eSysCtrlRet_TypeDef res = SYSCTRL_PASS;

    sys_ps_bak = SYS_PS;
    SYS_PS = 0x82U;
    osc1_ctrl_bak = OSC_CTRL1;
    osc2_ctrl_bak = OSC_CTRL2;

    /* pll as source */
    OSC_CTRL2 &= (~((unsigned int)1U << 4));
    PLL_ON;
    usTimeout((unsigned int)(&OSC_CTRL1), ((unsigned int)1U << 7), 0U, PLL_TIMEOUT, chipid);
    /* delay 1ms here(total 2ms for PLL stable) */
    usTimeout((unsigned int)(&OSC_CTRL1), ((unsigned int)1U << 7), 1U, 2000U, chipid);

    if (((OSC_CTRL1 >> 7) & 0x1U) == 0x0U)
    {
        res = SYSCTRL_FAIL;
    }
    else
    {
        if (SYSCTRL_FAIL == loscCheck(chipid))
        {
            res = SYSCTRL_FAIL;
        }
        else
        {
            usTimeout((unsigned int)(&OSC_CTRL1), ((unsigned int)1U << 12), 0U, PLL_TIMEOUT, chipid); /* wait PLL flag*/
            flag = OSC_CTRL1;
            if (((flag >> 12) & 0x1U) == 0x0U)
            {
                res = SYSCTRL_FAIL;
            }
        }
    }

    if (SYSCTRL_FAIL == res)
    {
        OSC_CTRL2 = osc2_ctrl_bak;
        OSC_CTRL1 = osc1_ctrl_bak;
    }

    SYS_PS = sys_ps_bak;
    return res;
}

/* 20180205 add */
/*
hosc max freq = 1.5*

RCH          HOSC(7.3728M)             HOSC(14.7456M)      HOSC(29.4912M)
avr 3.132    3.132*7373/2000=11.55M    23.09M              46.18M
max 3.292    12.14M                    24.27M              48.54M
min 2.724    10.04M                    20.08M              40.17M

RA9701A, RCH avr=29.4912, scaler=29.4912/3.132=9
*/
#define RCH_MAX (2000U)
#define RCH_MAX_71 (9U*2000U)
static const unsigned int HOSC_CYCLES[4] = {7373U, 14746U, 29491U, 29491U};
static eSysCtrlRet_TypeDef HoscValid(rn_chipid_t chipid)
{
    unsigned int trim_cfg1_bak, trim_start_bak, sys_ps_bak;
    eSysCtrlRet_TypeDef res = SYSCTRL_PASS;
    unsigned int rch_max;
    unsigned int temp;

    if ((CHIP_RA9701A == chipid) || (CHIP_RA9701A1 == chipid))
    {
        rch_max = RCH_MAX_71;
    }
    else
    {
        rch_max = RCH_MAX;
    }

    if (chipid != CHIP_RA9103A)
    {
        sys_ps_bak = SYS_PS;
        SYS_PS = 0x82U;
        trim_cfg1_bak = TRIM_CFG1;
        trim_start_bak = TRIM_START;

        TRIM_CFG1 = ((unsigned int)0U << 26) | ((unsigned int)1U << 24) | ((HOSC_CYCLES[OSC_CTRL2 & 0x3U]) << 0); /* use hosc to calc rch(1ms) */
        TRIM_START = (unsigned int)1U << 27;
        TRIM_START = (unsigned int)0x7U << 24;
        usTimeout((unsigned int)(&TRIM_START), ((unsigned int)1U << 24), 0U, HOSC_CALC_TIMEOUT, chipid); /* 10ms timeout */
        temp = TRIM_START;
        if ((((temp >> 24) & 0x1U) == 0x0U) || ((temp & 0xfffffU) < rch_max))
        {
            res = SYSCTRL_FAIL;
        }
        TRIM_START = (unsigned int)0x1U << 27;
        TRIM_START = (unsigned int)0x3U << 24;

        TRIM_CFG1 = trim_cfg1_bak;
        TRIM_START = trim_start_bak;
        SYS_PS = sys_ps_bak;
    }
    return res;
}

static eSysCtrlRet_TypeDef HoscEnable(rn_chipid_t chipid)
{
    unsigned int flag, mod1_en;
    unsigned int gpio_pca1_bak, osc_ctrl2_bak, sys_ps_bak;
    eSysCtrlRet_TypeDef res = SYSCTRL_PASS;

    sys_ps_bak = SYS_PS;
    SYS_PS = 0x82U;
    /* enable pll for rtc in hosc mode */
    PLL_ON;
    /* enable RC to calculate HOSC! */
    if (1U == ((OSC_CTRL1 >> 1) & 1U))
    {
        RC_ON;
    }

    mod1_en = MOD1_EN;

    MOD1_EN |= ((unsigned int)1U << 5);
    osc_ctrl2_bak = OSC_CTRL2;
    gpio_pca1_bak = GPIO_PCA1;

    GPIO_PCA1 |= ((unsigned int)0xfU << 12);
    HOSC_ON;
    OSC_CTRL2 |= ((unsigned int)1U << 4);          /* hosc as source */
    usTimeout((unsigned int)(&OSC_CTRL1), (unsigned int)1U << 15, 0U, HOSC_TIMEOUT, chipid); /* wait HOSC flag */

    flag = OSC_CTRL1;
    if (((flag >> 15) & 0x1U) == 0x0U)
    {
        /* only check HOSC flag(pll bypass) */
        OSC_CTRL2 = osc_ctrl2_bak;
        GPIO_PCA1 = gpio_pca1_bak;
        res = SYSCTRL_FAIL;
    }

    if (SYSCTRL_PASS == res)
    {
        usTimeout((unsigned int)(&OSC_CTRL1), ((unsigned int)1U << 15), 1U, 10000U, chipid); /* delay 5ms for hosc stable @20180111 */
        res = HoscValid(chipid);                                            /* measure hosc with rch @20180205 */
    }

    MOD1_EN = mod1_en;
    SYS_PS = sys_ps_bak;

    return res;
}

/**
 * @brief check if target clock is valid(stable)
 *  Don't need add clock wait time after called this function
 * @param mode: desired system mode
 * @param chipid: chip index
 * @return unsigned char: 0 = PASS, 1 = FAIL
 */
static eSysCtrlRet_TypeDef clock_valid_check(eSysCtrlClockMode_TypeDef mode, eSysCtrlClockDiv_TypeDef div, rn_chipid_t chipid)
{
    eSysCtrlRet_TypeDef res = SYSCTRL_PASS;
    unsigned int temp;

    if (IS_LC_MODE(mode) /* && (SYSCTRL_FAIL == loscCheck(chipid))*/)
    {
        /* 20180404 skip loscCheck while switching to RCL */
        if (Clock_Losc == mode)
        {
            res = loscCheck(chipid);
            if ((((OSC_CTRL2 >> 12) & 0x1U) == 0U) && (SYSCTRL_FAIL == res))
            {
                res = SYSCTRL_FAIL;
            }
        }
    }
    else if (IS_RC_MODE(mode))
    {
        if (Clock_RC_1M8 == mode)
        {
            temp = 0U;
            /*} else if (Clock_RC_3M7 == mode) {
                temp = 1;*/
        }
        else/* if (Clock_RC_29M5 == mode)*/
        {
            temp = (unsigned int)div;
            temp = 4U - temp;
        }

        OSC_CTRL2 = (OSC_CTRL2 & (~((unsigned int)0x7U << 16))) | (temp << 16);
        RC_ON;
        /* wait RCH flag */
        usTimeout((unsigned int)(&OSC_CTRL1), ((unsigned int)1U << 13), 0U, RCH_TIMEOUT, chipid);
        if (((OSC_CTRL1 >> 13) & 0x1U) == 0x0U)
        {
            res = SYSCTRL_FAIL;
        }
    }
    else if (IS_PLL_MODE(mode))
    {
        if (Clock_PLL_7M4 == mode)
        {
            temp = 0U;
        }
        else if (Clock_PLL_14M7 == mode)
        {
            temp = 1U;
        }
        else/* if (Clock_PLL_29M5 == mode)*/
        {
            temp = 2U;
        }
        OSC_CTRL2 = (OSC_CTRL2 & (~((unsigned int)0x7U << 5))) | (temp << 5);
        res = loscCheck(chipid);
        if (SYSCTRL_PASS == res)
        {
            res = PllEnable(chipid);
        }
    }
    else/* if (IS_HOSC_MODE(mode))*/
    {
        res = HoscEnable(chipid);
    }
    return res;
}

static unsigned int get_target_freq(eSysCtrlClockMode_TypeDef mode, eSysCtrlClockDiv_TypeDef div)
{
    unsigned int freq;
    if ((Clock_Losc == mode) || (Clock_RCL_32K == mode))
    {
        freq = 32768U;
    }
    else if (Clock_RC_1M8 == mode)
    {
        freq = 1843200U;
    }
    else if (Clock_PLL_7M4 == mode)
    {
        freq = 7372800U >> div;
    }
    else if (Clock_Hosc == mode)
    {
        freq = OSC_CTRL2 & 0x3U;
        freq = (freq == 0U) ? 7372800U : ((freq == 1U) ? 14745600U : 29491200U);
        freq = freq >> div;
        /*} else if (Clock_RC_3M7 == mode) {
            freq = 3686400;*/
    }
    else if (Clock_PLL_14M7 == mode)
    {
        freq = 14745600U >> div;
    }
    else if ((Clock_RC_29M5 == mode) || ((Clock_PLL_29M5 == mode)))
    {
        freq = 29491200U >> div;
    }
    else
    {
        freq = 1843200U;
    }

    return freq;
}

/**
 * @brief Set the ldo mode
 *
 * @param ldo_mode: 0 = light-load, 1 = high-load, 2 = safe-load mode
 * @return unsigned char: 0 = PASS, 1 = FAIL
 */
static void set_ldo_mode(ldo_mode_t ldo_mode, rn_chipid_t chipid)
{
    unsigned int sys_ps_bak = SYS_PS;
    unsigned char ldo_set = (ldo_mode == LIGHT_MODE) ? 0x69U : ((ldo_mode == HIGH_MODE) ? 0x96U : 0x0U);

    SYS_PS = 0x75U;
    if (CHIP_RA9103G == chipid)
    {
        LDO_MODE = (LDO_MODE & (~(unsigned int)0xffU)) | (0xa5580000U | ldo_set);
    }
    else if (CHIP_RA9701A == chipid)
    {
        LDO_MODE_V2 = (LDO_MODE_V2 & (~((unsigned int)0xffU << 0))) | (0xa5580000U | ldo_set);
    }
    else if (CHIP_RA9701A1 == chipid)
    {
        /* open dig5 write-window */
        MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x55U << 0);
        MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x55U << 0) | ((unsigned int)0x23U << 10);

        LDO_MODE_V2 = (LDO_MODE_V2 & (~((unsigned int)0xffU << 0))) | (0xa5580000U | ldo_set);

        /* close dig5 write-window */
        MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x0U << 0);
        MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x0U << 0) | ((unsigned int)0x23U << 10);
    }
    else
    {
        /* only 9103G/9701A support LDO mode */
        ;
    }
    SYS_PS = sys_ps_bak;
}

/**
 * @brief system run mode set
 *
 * @param mode: target system mode value:
 *   0 = LC, 1/4 = RC, 2/5 = PLL, 3 = HOSC
 * @param chipid: chip id index
 * @param cur_freq: target system frequency value
 * @return unsigned char: 0 = PASS, 1 = FAIL
 */
static eSysCtrlRet_TypeDef sysmodeWrite(eSysCtrlClockMode_TypeDef mode, eSysCtrlClockDiv_TypeDef div, rn_chipid_t chipid, unsigned int cur_freq)
{
    unsigned int tar_freq = get_target_freq(mode, div);
    unsigned int temp = (unsigned int)div;
    eSysCtrlRet_TypeDef res = SYSCTRL_PASS;

    if (SYSCTRL_FAIL == clock_valid_check(mode, div, chipid))
    {
        res = SYSCTRL_FAIL;
    }
    else
    {
        /* wait until flash not busy */
        usTimeout((unsigned int)(&SYS_MODE), 0x10U, 1U, MIP_TIMEOUT, chipid);
        usTimeout((unsigned int)(&SYS_MODE), 0x20U, 1U, MIP_TIMEOUT, chipid);

        if (tar_freq > cur_freq)
        {
            setMipTW(tar_freq, chipid);
        }

        if (IS_LC_MODE(mode))
        {
            SYS_MODE = 0xFU;
            /* @20180504 wait clk sync before changing TW */
            usTimeout((unsigned int)(&OSC_CTRL1), ((unsigned int)1U << 4), 0U, LOSC_TIMEOUT, chipid);
        }
        else if (IS_RC_MODE(mode))
        {
            SYS_MODE = 0xEU;
            /* @20180504 wait clk sync before changing TW */
            usTimeout((unsigned int)(&OSC_CTRL1), ((unsigned int)1U << 5), 0U, LOSC_TIMEOUT, chipid);
        }
        else if (IS_PLL_MODE(mode))
        {
            OSC_CTRL1 = (OSC_CTRL1 & (~((unsigned int)0x3U << 2))) | (temp << 2);
            SYS_MODE = 0xDU;
            usTimeout((unsigned int)(&OSC_CTRL1), ((unsigned int)1U << 6), 0U, LOSC_TIMEOUT, chipid);
        }
        else if (IS_HOSC_MODE(mode))
        {
            OSC_CTRL1 = (OSC_CTRL1 & (~((unsigned int)0x3U << 2))) | (temp << 2);
            SYS_MODE = 0xDU;
            usTimeout((unsigned int)(&OSC_CTRL1), ((unsigned int)1U << 6), 0U, LOSC_TIMEOUT, chipid);
        }
        else
        {
            res = SYSCTRL_FAIL;
        }

        if ((SYSCTRL_PASS == res) && (tar_freq < cur_freq))
        {
            setMipTW(tar_freq, chipid);
        }
    }

    return res;
}

/**
 * @brief system run mode parameters check
 * @param mode: target system mode value:
 *   0 = LC, 8 = RCL
 *   1 = RC(1.8432M), 4 = RC(3.6864M), 6 = RC(29.4912M)
 *   2 = PLL(7.3728M), 5 = PLL(14.7456M), 7 = PLL(29.4912M)
 *   3 = HOSC(depends on OSC_CTRL2[2:0])
 *
 *   RA9103A/D support mode=[0-3]
 *   RA9103C/G/E/F support mode=[0-5]
 *   RA9701 supports mode=[0-9]
 * @param div: clock div(only for HOSC/PLL mode)
 * @param chipid: chip index
 * @return unsigned char: 0 = PASS, 1 = FAIL
 */
static eSysCtrlRet_TypeDef sysmode_params_check(eSysCtrlClockMode_TypeDef mode, eSysCtrlClockDiv_TypeDef div, rn_chipid_t chipid)
{
    eSysCtrlRet_TypeDef res;
    unsigned int temp = OSC_CTRL2 & 0x7U;
    /* speed up losc */
    if (((Clock_Losc == mode) || (Clock_RCL_32K == mode)) && (Clock_Div_1 == div))
    {
        res = SYSCTRL_PASS;
    }
    else if ((((Clock_Losc == mode) || (Clock_RC_1M8 == mode)) && (div > Clock_Div_1)) ||
             ((Clock_PLL_7M4 == mode) && (div > Clock_Div_4)) ||
             ((Clock_Hosc == mode) && (div > Clock_Div_8)) ||
             ((Clock_Hosc == mode) && (Clock_Div_8 == div) && (temp == 0x0U)) ||
             (4U == (unsigned int)mode))
    {
        res = SYSCTRL_FAIL;
    }
    else if ((CHIP_RA9103A == chipid) || (CHIP_RA9103D == chipid))
    {
        if (mode > Clock_Hosc)
        {
            res = SYSCTRL_FAIL;
        }
        else
        {
            res = SYSCTRL_PASS;
        }
    }
    else if ((CHIP_RA9103C == chipid) ||
             (CHIP_RA9103E == chipid) ||
             (CHIP_RA9103F == chipid) ||
             (CHIP_RA9103G == chipid))
    {
        if (((Clock_PLL_14M7 == mode) && (div > Clock_Div_8)) || (mode > Clock_PLL_14M7))
        {
            res = SYSCTRL_FAIL;
        }
        else
        {
            res = SYSCTRL_PASS;
        }
    }
    else/* if ((CHIP_RA9701A == chipid) || (CHIP_RA9701A1 == chipid))*/
    {
        if ((((Clock_RCL_32K == mode)) && (div > Clock_Div_1)) ||
            (((Clock_PLL_14M7 == mode) || (Clock_RC_29M5 == mode) || (Clock_PLL_29M5 == mode)) && (div > Clock_Div_8)) ||
            (mode >= Clock_CHG_MAX))
        {
            res = SYSCTRL_FAIL;
        }
        else
        {
            res = SYSCTRL_PASS;
        }
    }
    return res;
}

/**
 * @brief system run mode change
 * @param mode: target system mode value:
 *   0 = LC, 8 = RCL
 *   1 = RC(1.8432M), 4 = RC(3.6864M), 6 = RCH(29.4912M)
 *   2 = PLL(7.3728M), 5 = PLL(14.7456M), 7 = PLL(29.4912M)
 *   3 = HOSC(depends on OSC_CTRL2[2:0])
 *
 *   RA9103A/D support mode=[0-3]
 *   RA9103C/G/E/F support mode=[0-5]
 *   RA9701 supports mode=[0-8]
 * @param div: clock div(only for HOSC/PLL/RCH mode)
 * @return unsigned char: 0 = PASS, 1 = FAIL
 */
eSysCtrlRet_TypeDef SysModeChg(eSysCtrlClockMode_TypeDef mode, eSysCtrlClockDiv_TypeDef div)
{
    unsigned int cur_freq;
    unsigned int sys_ps;
    eSysCtrlRet_TypeDef res = SYSCTRL_PASS;
    rn_chipid_t chipid;
    unsigned int temp;

    chipid = getChipid();

    if (SYSCTRL_FAIL == sysmode_params_check(mode, div, chipid))
    {
        res = SYSCTRL_FAIL;
    }
    else
    {
        sys_ps = SYS_PS;
        if (((OSC_CTRL1 >> 4) & 0x1U) == 0x1U)
        {
            /* exit light-mode of ldo(enter safe-mode) if current mode is LC! */
            set_ldo_mode(SAFE_MODE, chipid);
        }
        SYS_PS = 0x82U;

        cur_freq = currentClk_idx();
        cur_freq = (cur_freq == 0U) ? 32768U : ((unsigned int)1843200U << (cur_freq - 1U));
        /* always enable SYS_TC/RTC/WDT apb clock */
        MOD1_EN |= (((unsigned int)1U << 10) | ((unsigned int)1U << 9));
        if (CHIP_RA9103A != chipid)
        {
            MOD0_EN |= ((unsigned int)1U << 0);
        }
        /* FEED_WDT; */

        if (IS_LC_MODE(mode))
        {
            if (1U == ((OSC_CTRL1 >> 4) & 0x1U))
            {
                temp = (OSC_CTRL2 >> 12) & 0x1U;
                if (((mode == Clock_RCL_32K) && (0U == temp))
                    || ((mode == Clock_Losc) && (1U == temp)))
                {
                    /* switch to RC firstly if current mode and target mode are diffrent LC mode */
                    res = sysmodeWrite(Clock_RC_1M8, Clock_Div_1, chipid, cur_freq);
                }
            }

            if (SYSCTRL_PASS == res)
            {
                if (Clock_RCL_32K == mode)
                {
                    OSC_CTRL2 |= ((unsigned int)1U << 12);
                }
                else
                {
                    OSC_CTRL2 &= (~((unsigned int)1U << 12));
                }
                cur_freq = currentClk();
                res = sysmodeWrite(mode, div, chipid, cur_freq);
            }
            if (SYSCTRL_FAIL == res)
            {
                res = SYSCTRL_FAIL;
            }
            else
            {
                /* close RC&PLL&HOSC */
                RC_OFF;
                PLL_OFF;
                HOSC_OFF;
                set_ldo_mode(LIGHT_MODE, chipid);
            }
        }
        else if (IS_RC_MODE(mode))
        {
            if (SYSCTRL_FAIL == sysmodeWrite(mode, div, chipid, cur_freq))
            {
                res = SYSCTRL_FAIL;
            }
            else
            {
                /* close PLL&HOSC */
                PLL_OFF;
                HOSC_OFF;
            }
        }
        else
        {
            /* HOSC */
            if (1U == ((OSC_CTRL1 >> 6) & 1U))
            {
                /* switch to RC firstly if current mode and target mode are HC mode */
                res = sysmodeWrite(Clock_RC_1M8, Clock_Div_1, chipid, cur_freq);
            }

            if (SYSCTRL_PASS == res)
            {
                cur_freq = currentClk();
                res = sysmodeWrite(mode, div, chipid, cur_freq);
            }

            if (SYSCTRL_PASS == res)
            {
                RC_OFF;
                if (Clock_Hosc != mode)
                {
                    HOSC_OFF;
                }
            }
        }

        /* FEED_WDT; */
        SYS_PS = sys_ps;
    }
    return res;
}

/*=====================================================================================

 Remap4Sel() lib

=====================================================================================*/
#define SPL0_OFFSET 0x00c08000U
#define PAGE_SIZE_512 512U
#define PAGE_SIZE_256 256U
#define PAGE_SIZE_128 128U
#define PAGE_SIZE_64 64U
static struct sIAP
{
    unsigned long cmd;
    unsigned long par[4];
    unsigned long stat;
    unsigned long res[2];
} IAP;

/* IAP Call */
typedef void (*IAP_Entry)(unsigned long *cmd, unsigned long *stat);
#define IAP_ADDR  (0x18001c01U)

static void mem_cpy(unsigned char dst[], const unsigned char src[], unsigned int len)
{
    unsigned int i;
    for (i = 0U; i < len; i++)
    {
        dst[i] = src[i];
    }
}

static void get_flash_info(flash_info_t * fl_info)
{
    rn_chipid_t chipid;

    chipid = getChipid();
    if ((chipid == CHIP_RA9103F) || (chipid == CHIP_RA9103G))
    {
        fl_info->mem_addr = getMipAddr(0U);
        fl_info->page_size = PAGE_SIZE_256;
        fl_info->spl_type = IN_FLASH;
        /* flash2 spl0_offset = 0x80000U + 0x40000U */
        fl_info->spl0_offset = 0x80000U;
    }
    else if ((chipid == CHIP_RA9103A) || (chipid == CHIP_RA9103D))
    {
        fl_info->mem_addr = getMipAddr(1U);
        fl_info->page_size = PAGE_SIZE_64;
        fl_info->spl_type = IN_EEPROM;
        fl_info->spl0_offset = 0x00c08000U;
    }
    else if ((chipid == CHIP_RA9103C) || (chipid == CHIP_RA9103E))
    {
        fl_info->mem_addr = getMipAddr(1U);
        fl_info->page_size = PAGE_SIZE_128;
        fl_info->spl_type = IN_EEPROM;
        fl_info->spl0_offset = 0x00c08000U;
    }
    else/* if ((CHIP_RA9701A == chipid) || (CHIP_RA9701A1 == chipid))*/
    {
        fl_info->mem_addr = getMipAddr(0U);
        fl_info->page_size = PAGE_SIZE_512;
        fl_info->spl_type = IN_FLASH;
        fl_info->spl0_offset = 512U * 1024U;
    }
}

/**
 * @brief Remap4Sel
 *
 * @param
 *    in unsigned char sel: select remap4(sel = 0) or remap0(sel = 1)
 * @return
 *    0: set remap pass
 *    1: set remap fail
 *
 */
#define FL_ERASE_PAGE (0xfeed0000U | 0xbU)
eSysCtrlRet_TypeDef Remap4Sel(unsigned char sel)
{
    flash_info_t fl_info;
    unsigned int remap_value;
    rn_chipid_t chipid;
    unsigned int sp1[128];
    unsigned int retry;
    unsigned int temp;
    IAP_Entry iap_func = (IAP_Entry)(IAP_ADDR);
    eSysCtrlRet_TypeDef res;

    remap_value = (sel == 0U) ? ((((~(unsigned int)0x7e5au) & 0xffffU) << 16) | (unsigned int)0x7e5aU) : 0xffffffffU;
    chipid = getChipid();
    get_flash_info(&fl_info);
    if (IN_FLASH == fl_info.spl_type)
    {
        temp = nvmWrEnable(FLASH_NVM);
        IAP.cmd = IAP_FW;
    }
    else
    {
        temp = nvmWrEnable(EEPROM_NVM);
        IAP.cmd = IAP_EW;
    }

    if (0U != temp)
    {
        res = SYSCTRL_FAIL;
    }
    else
    {
        res = SYSCTRL_PASS;
    }

    if (SYSCTRL_PASS == res)
    {
        if ((chipid == CHIP_RA9103F) || (chipid == CHIP_RA9103G))
        {
            unsigned char i;
            unsigned int n;
            /*unsigned char *p_dat;*/
            unsigned int FlashCfgAdr;
            if (chipid == CHIP_RA9103F)
            {
                FlashCfgAdr = 0x50014000U;
            }
            else
            {
                FlashCfgAdr = 0x00800000U;
            }

            for (i = 0U; i < 2U; i++)
            {
                for (retry = 0U; retry < 3U; retry++)
                {
                    /* read sp1 */
                    fl_info.spl0_offset += i * (0x40000U);
                    IAP.par[0] = fl_info.mem_addr + fl_info.spl0_offset + 1U * fl_info.page_size;
                    mem_cpy((unsigned char *)&sp1[0], (unsigned char *)IAP.par[0], fl_info.page_size);
                    if (0U == check_spl_valid(sp1, fl_info.page_size, 1U))
                    {
                        res = SYSCTRL_FAIL;
                    }
                    else
                    {
                        res = SYSCTRL_PASS;

                        /* modify sp1's last 2bytes */
                        /*sp1[fl_info.page_size / 2U - 2U] = (remap_value)&0xffffU;*/
                        /*sp1[fl_info.page_size / 2U - 1U] = (remap_value >> 16) & 0xffffU;*/
                        sp1[fl_info.page_size / 4U - 1U] = remap_value;

                        /* remp0 ,write 1st FlashSPL; remap4 ,write 2nd FlashSPL */
                        temp = MAP_CTL & 0x7U;
                        if (((i == 0U) && (0x4U != temp)) || ((i == 1U) && (0x4U == temp)))
                        {
                            *(unsigned int *)(FlashCfgAdr + 0x14U) = 0xfeed0000U;
                            *(unsigned int *)(FlashCfgAdr + 0x04U) = 0x401U;
                            *(unsigned int *)(FlashCfgAdr + 0x00U) = FL_ERASE_PAGE;

                            usTimeout((FlashCfgAdr + 0x08U), ((unsigned int)1U << 1), 1U, 3000U, chipid);
                        }
                        else
                        {
                            *(unsigned int *)(FlashCfgAdr + 0x34U) = 0xfeed0000U;
                            *(unsigned int *)(FlashCfgAdr + 0x24U) = 0xc01U;
                            *(unsigned int *)(FlashCfgAdr + 0x20U) = FL_ERASE_PAGE;

                            usTimeout((FlashCfgAdr + 0x28U), ((unsigned int)1U << 1), 1U, 3000U, chipid);
                        }
                        if (0x4U == temp)
                        {
                            if (i == 0U)
                            {
                                *(unsigned int *)(FlashCfgAdr + 0x24U) = 0xc01U;
                                *(unsigned int *)(FlashCfgAdr + 0x20U) = 0xfeed0004U;

                                /*p_dat = (unsigned char *)&sp1[0];*/
                                for (n = 0U; n < fl_info.page_size / 4U; n++)
                                {
                                    *((unsigned int *)(0x80100U + 4U * n)) = sp1[n];
                                    /*p_dat++;*/
                                }
                                *(unsigned int *)(FlashCfgAdr + 0x20U) = 0xfeed000fU;
                                usTimeout((FlashCfgAdr + 0x28U), ((unsigned int)1U << 1), 1U, 3000U, chipid);
                            }
                            else
                            {
                                *(unsigned int *)(FlashCfgAdr + 0x04U) = 0x401U;
                                *(unsigned int *)(FlashCfgAdr + 0x00U) = 0xfeed0004U;

                                /*p_dat = (unsigned char *)&sp1[0];*/
                                for (n = 0U; n < fl_info.page_size / 4U; n++)
                                {
                                    *((unsigned int *)(0xc0100U + 4U * n)) = sp1[n];
                                    /*p_dat++;*/
                                }
                                *(unsigned int *)(FlashCfgAdr + 0x00U) = 0xfeed000fU;
                                usTimeout((FlashCfgAdr + 0x08U), ((unsigned int)1U << 1), 1U, 3000U, chipid);
                            }
                        }
                        else
                        {
                            IAP.par[1] = (unsigned int)&sp1[0];
                            IAP.par[2] = fl_info.page_size;
                            iap_func(&IAP.cmd, &IAP.stat);
                            /* function return check in below data compare
                            if (1U == IAP.stat)
                            {
                                res = SYSCTRL_FAIL;
                                continue;
                            } else {
                                res = SYSCTRL_PASS;
                            }
                            */
                        }

                        for (n = 0U; n < (fl_info.page_size / 4U); n++)
                        {
                            temp = 0x80100U + 4U * n + i * (0x40000U);
                            temp = *(unsigned int *)(temp);
                            if (temp != sp1[n])
                            {
                                res = SYSCTRL_FAIL;
                                break;
                            }
                        }
                        if (SYSCTRL_PASS == res)
                        {
                            break;
                        }
                    }
                }
            }
        }
        else if ((CHIP_RA9103A == chipid) ||
                 (CHIP_RA9103D == chipid) ||
                 (CHIP_RA9103C == chipid) ||
                 (CHIP_RA9103E == chipid))
        {
            for (retry = 0U; retry < 3U; retry++)
            {
                IAP.par[0] = fl_info.mem_addr + fl_info.spl0_offset + 2U * fl_info.page_size - 4U;
                IAP.par[1] = (unsigned int)(&remap_value);
                IAP.par[2] = 4U;

                iap_func(&IAP.cmd, &IAP.stat);
                /* function return check in below data compare
                if (1U == IAP.stat)
                {
                    continue;
                }
                */
                remap_value = *(unsigned int *)(fl_info.mem_addr + fl_info.spl0_offset + 2U * fl_info.page_size - 4U);
                if (((sel == 1U) && (remap_value == 0xffffffffU)) ||
                    ((sel == 0U) && (remap_value == ((((~(unsigned int)0x7e5au) & 0xffffU) << 16) | (unsigned int)0x7e5aU))))
                {
                    res = SYSCTRL_PASS;
                    break;
                }
                else
                {
                    res = SYSCTRL_FAIL;
                }
            }
        }
        else if ((CHIP_RA9701A == chipid) || (CHIP_RA9701A1 == chipid))
        {
            unsigned int i;

            for (retry = 0U; retry < 3U; retry++)
            {
                /* read-back sp1 and change remap4 flag */
                IAP.par[0] = fl_info.mem_addr + fl_info.spl0_offset + 1U * fl_info.page_size;
                mem_cpy((unsigned char *)&sp1[0], (unsigned char *)IAP.par[0], fl_info.page_size);
                sp1[fl_info.page_size / 4U - 1U] = remap_value;
                /* check memory checksum */
                if (0U == check_spl_valid(sp1, fl_info.page_size, 1U))
                {
                    res =  SYSCTRL_FAIL;
                }
                else
                {
                    (void)nvmWrEnable(FLASH_NVM);
                    /* erase sp1 */
                    IAP.cmd = IAP_NVRP;
                    IAP.par[0] = 1U;
                    iap_func(&IAP.cmd, &IAP.stat);
                    /* function return check in below data compare
                    if (1U == IAP.stat)
                    {
                        res =  SYSCTRL_FAIL;
                        continue;
                    }
                    */

                    (void)nvmWrEnable(FLASH_NVM);
                    /* program sp1 */
                    IAP.cmd = IAP_FW;
                    IAP.par[0] = fl_info.mem_addr + fl_info.spl0_offset + 1U * fl_info.page_size;
                    IAP.par[1] = (unsigned int)(&sp1);
                    IAP.par[2] = fl_info.page_size;
                    iap_func(&IAP.cmd, &IAP.stat);
                    /* function return check in below data compare
                    if (1U == IAP.stat)
                    {
                        res =  SYSCTRL_FAIL;
                        continue;
                    } else {
                        res = SYSCTRL_PASS;
                    }
                    */

                    /* check */
                    for (i = 0U; i < (fl_info.page_size / 4U); i++)
                    {
                        temp = fl_info.mem_addr + fl_info.spl0_offset + 1U * fl_info.page_size + 4U * i;
                        temp = *(unsigned int *)temp;
                        if (temp != sp1[i])
                        {
                            res = SYSCTRL_FAIL;
                            break;
                        }
                    }
                }
            }
        }
    }
    else
    {
        /* flash unlock fail! */
    }

    return res;
}

#ifndef  SOFT_VER
#define  SOFT_VER 0x00010000U
#endif
unsigned int GetLibVersion(void)
{
    return SOFT_VER;
}

#ifndef  CODE_VER
#define  CODE_VER 0x123U
#endif
unsigned int GetCodeVersion(void)
{
    return CODE_VER;
}

// -*- r33840 -*-
