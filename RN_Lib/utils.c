/**
 * @file utils.c
 * @author Renergy Technology Inc.
 * @brief common functions used by lib code
 * @version 1.0.0
 * @date 2023-02-03
 *
 * @copyright Copyright (C) 2008, Renergy Technology Inc. All rights reserved.
 *
 */

#include "utils.h"
#include "sysctrl_reg.h"

typedef void (*IAP_Entry)(unsigned long *cmd, unsigned long *stat);
#define IAP_OFFSET 0x1c01U

static const unsigned int us_freq[5];
static const unsigned int us_cycle[5];
static const unsigned int CAL_BUSY_TIMEOUT[6];

static unsigned char TICK_STAT_GET(rn_chipid_t chipid);
static unsigned int sumCheck(const unsigned int p_data[], unsigned int length);

/**
 * @brief Get the Chipid number
 *
 * @return rn_chipid_t: chipid number
 */
rn_chipid_t getChipid(void)
{
    rn_chipid_t chipid;
    unsigned int sys_ps_bak;
    unsigned int mod0_en_bak;

    mod0_en_bak = MOD0_EN;
    sys_ps_bak = SYS_PS;

    SYS_PS = 0x82U;
    /* SYS_TC */
    MOD0_EN |= ((unsigned int)1U << 0);
    SYS_PS = 0x75U;
    /**
     * 9103A/D: no define
     * 9103C/E/F/G/H: only accessable when sys_ps is 0x75
     * 9701A: alwasy accessable
     */
    switch (DIE_VER)
    {
        case 0xc0:
            chipid = CHIP_RA9103C;
            break;
        case 0xe0:
            chipid = CHIP_RA9103E;
            break;
        case 0xf0:
            chipid = CHIP_RA9103F;
            break;
        case 0x10:
            chipid = CHIP_RA9103G;
            break;
        case 0x30:
            if (DIE_VER2 == 0x71a1U)
            {
                chipid = CHIP_RA9701A1;
            }
            else
            {
                chipid = CHIP_RA9701A;
            }
            break;
        default:
            /* RA9103A has no SYS_TC */
            SYSTC_LOAD = 0xffffffffU;
            if (SYSTC_LOAD == 0xffffffffU)
            {
                SYSTC_LOAD = 0x0U;
                if (SYSTC_LOAD == 0x0U)
                {
                    chipid = CHIP_RA9103D;
                }
                else
                {
                    chipid = CHIP_RA9103A;
                }
            }
            else
            {
                chipid = CHIP_RA9103A;
            }
            break;
    }

    SYS_PS = 0x82U;
    MOD0_EN = mod0_en_bak;
    SYS_PS = sys_ps_bak;
    return chipid;
}

/**
 * @brief Get the Mip Addr object
 *
 * @param mem_type: 0 = FLASH, 1 = EEPROM, 2 = ROM
 * @return unsigned int: memory base address
 */
unsigned int getMipAddr(unsigned char mem_type)
{
    unsigned int ee_addr, fl_addr, rom_addr;
    switch (MAP_CTL & 0x7U)
    {
        case 0:
            ee_addr = 0x08000000U;
            fl_addr = 0x0U;
            rom_addr = 0x18000000U;
            break;
        case 1:
            ee_addr = 0x0U;
            fl_addr = 0x08000000U;
            rom_addr = 0x18000000U;
            break;
        case 2:
            ee_addr = 0x08000000U;
            fl_addr = 0x10000000U;
            rom_addr = 0x18000000U;
            break;
        case 3:
            ee_addr = 0x08000000U;
            fl_addr = 0x18000000U;
            rom_addr = 0x0U;
            break;
        default:
            ee_addr = 0x08000000U;
            fl_addr = 0x0U;
            rom_addr = 0x18000000U;
            break;
    }
    return (mem_type == 0U) ? fl_addr : (mem_type == 1U) ? ee_addr
           : rom_addr;
}

/**
 * @brief get current run clock
 *
 * @return unsigned int: clock frequency
 */
unsigned int currentClk(void)
{
    unsigned int freq;
    unsigned int val = (OSC_CTRL1 >> 8U) & 0x7U;

    if (val == 0x3U)
    {
        freq = 32768U;
    }
    else if (val == 0x2U)
    {
        freq = 1843200U;
    }
    else if (val == 0x0U)
    {
        freq = 7372800U;
    }
    else if (val == 0x1U)
    {
        freq = 3686400U;
    }
    else if (val == 0x4U)
    {
        freq = 14745600U;
    }
    else if (val == 0x5U)
    {
        freq = 29491200U;
    }
    else
    {
        freq = 1843200U;
    }

    return freq;
}

/**
 * @brief get current run clock index
 *
 * @return unsigned int: clock index
 */
unsigned int currentClk_idx(void)
{
    unsigned int freq;
    unsigned int val = (OSC_CTRL1 >> 8U) & 0x7U;

    if (val == 0x3U)
    {
        freq = 0U;
    }
    else if (val == 0x2U)
    {
        freq = 1U;
    }
    else if (val == 0x0U)
    {
        freq = 3U;
    }
    else if (val == 0x1U)
    {
        freq = 2U;
    }
    else if (val == 0x4U)
    {
        freq = 4U;
    }
    else if (val == 0x5U)
    {
        freq = 5U;
    }
    else
    {
        freq = 1U;
    }

    return freq;
}

#define TICK_START(chipid)          \
    {                               \
        if ((chipid) == CHIP_RA9103A) \
        {                           \
            SYSTICK_CTRL = 0x5U;    \
        }                           \
        else                        \
        {                           \
            SYSTC_CTRL = 3U;       \
        }                           \
    }
#define TICK_STOP(chipid)             \
    {                                 \
        if ((chipid) == CHIP_RA9103A)   \
        {                             \
            SYSTICK_LOAD = 0xffffffU; \
            SYSTICK_CTRL = 0x4U;      \
            SYSTICK_VAL = 0x0U;       \
        }                             \
        else                          \
        {                             \
            SYSTC_CTRL = 2U;         \
        }                             \
    }
#define TICK_TIME_SET(chipid, ticks) \
    {                                \
        if ((chipid) == CHIP_RA9103A)  \
        {                            \
            SYSTICK_LOAD = (ticks);   \
        }                            \
        else                         \
        {                            \
            SYSTC_LOAD = (ticks);    \
        }                            \
    }

static unsigned char TICK_STAT_GET(rn_chipid_t chipid)
{
    unsigned char res;
    if (chipid == CHIP_RA9103A)
    {
        res = (unsigned char)((SYSTICK_CTRL >> 16U) & 0x1U);
    }
    else
    {
        res = (unsigned char)((SYSTC_CTRL >> 1U) & 0x1U);
    }

    return res;
}

static const unsigned int us_freq[5] = {23U, 22U, 21U, 20U, 19U};
static const unsigned int us_cycle[5] = {2U, 4U, 8U, 15U, 30U};                           /* 1us = us_cycle[x] cycles */
/**
 * timeout unit: us
 * sign = 1, exit while val != ([addr] & val)
 * sign = 0, exit while val == ([addr] & val)
 */
void usTimeout(unsigned int addr, unsigned int val, unsigned int sign, unsigned int timeout, rn_chipid_t chipid)
{
    /* const unsigned int us_freq[] = {9100000, 4550000, 2274000, 1137000, 568000}; 0xffffff = us_freq[x] us */
    /* use shift instead of divide */
    unsigned int i, loops;
    unsigned int freq;
    unsigned int ticks;

    if (timeout != 0U)
    {
        /* SysTick range: 29M: 568ms; 14M:1.137s; 7M:2.274s; 3M:4.55s; 1M:9.1s; 32K: 511.7s */
        freq = currentClk_idx();

        if (freq == 0U)
        {
            loops = 1U;
        }
        else
        {
            /* loops = 1 + timeout / us_freq[freq - 1]; */
            loops = 1U + (timeout >> us_freq[freq - 1U]);
        }

        for (i = 0U; i < loops; i++)
        {
            TICK_STOP(chipid)
            if (i != (loops - 1U))
            {
                ticks = 0xffffffU;
            }
            else
            {
                if (freq == 0U)
                {
                    ticks = timeout / 32U;
                }
                else
                {
                    /* ticks = (timeout - (loops - 1) * us_freq[freq - 1]) * us_cycle[freq - 1]; */
                    ticks = (timeout - ((loops - 1U) << us_freq[freq - 1U])) * us_cycle[freq - 1U];
                    if (ticks == 0U)
                    {
                        break;
                    }
                }
            }
            TICK_TIME_SET(chipid, ticks)
            TICK_START(chipid)
            for (; ;)
            {
                if ((1U == TICK_STAT_GET(chipid)) ||
                    ((sign == 1U) && (((*(unsigned int *)addr) & val) != val)) ||
                    ((sign == 0U) && (((*(unsigned int *)addr) & val) == val)))
                {
                    break;
                }
                FEED_WDT;
            }
        }

        TICK_STOP(chipid)
    }
    return;
}

/**
 * @brief sumCheck
 *   校验和计算，按照32位宽计算
 * @param p_data 源数据起始地址
 * @param length 数据长度（word单位）
 * @return unsigned int 返回校验和值
 */
static unsigned int sumCheck(const unsigned int p_data[], unsigned int length)
{
    unsigned int i;
    unsigned int sum = 0U;
    for (i = 0U; i < length; i++)
    {
        sum = sum + p_data[i];
    }

    return sum;
}

/**
 * @brief check_spl_valid
 *   检查NVR数据合法性（32位累加和）
 * @param p_addr NVR的起始地址
 * @param len NVR的长度
 * @param flag 校验和位置标记(0：最后一个word存放校验和，1：最后第二个word存放校验和(最后一个word不参与计算))
 * @return unsigned char 返回结果
 *   1：正确
 *   0：错误
 */
unsigned char check_spl_valid(unsigned int *p_addr, unsigned int len, unsigned char flag)
{
    unsigned int checksum;
    unsigned char sp_valid = 0x0U;
    unsigned int temp;

    checksum = sumCheck(p_addr, (flag == 0x1U) ? ((len >> 2) - 1U) : (len >> 2));
    temp = (unsigned int)(p_addr);
    temp += (len - 3U * 4U);
    if ((*(unsigned int *)(temp) == 0xffffffffU) && (checksum == 0U))
    {
        sp_valid = 0x1U;
    }

    return sp_valid;
}

/**
 * @brief Enable IAP NVM operation
 *
 * @param nvm_type: 0 = FLASH, 1 = EEPROM
 * @return unsigned char: ref IAP interface in datasheet
 */
unsigned char nvmWrEnable(unsigned char nvm_type)
{
    struct sIAP
    {
        unsigned long cmd;
        unsigned long par[4];
        unsigned long stat;
        unsigned long res[2];
    } IAP;
    unsigned int iap_addr;

    iap_addr = getMipAddr(2U) + IAP_OFFSET;

    IAP.cmd = 0x5aU;
    IAP.par[0] = nvm_type;
    (*(void (*)(unsigned long *cmd, unsigned long *stat))(iap_addr))(&IAP.cmd, &IAP.stat);
    return (unsigned char)IAP.stat;
}

/* max 30ms. */
static const unsigned int CAL_BUSY_TIMEOUT[6] = {40, 56 * 40, 2 * 56 * 40, 2 * 2 * 56 * 40, 2 * 2 * 2 * 56 * 40, 2 * 2 * 2 * 2 * 56 * 40};
/**
 * @brief rtc wrong state check
 *   1. check if some of VBAT power domain registers are unexcepted
 *   2. check if rtc calc busy is always on(if yes, VBAT power domain is in wrong state)
 * @return unsigned char: 0 = OK, 1 = FAIL
 */
unsigned char RtcCalCheck(rn_chipid_t chipid)
{
    unsigned int i;
    unsigned int t = CAL_BUSY_TIMEOUT[currentClk_idx()];
    unsigned int passwd_bak;
    unsigned char res = 0U;
    unsigned int calc_ps = RTC_CALPS;
    unsigned int ana_test;
    unsigned int ana_ctl;
    unsigned int ana_ctl2;
    unsigned int losc_cfg2;

    if (!((chipid == CHIP_RA9103A) ||
          (chipid == CHIP_RA9103C) ||
          (chipid == CHIP_RA9103D) ||
          (chipid == CHIP_RA9103G)))
    {
        if ((chipid == CHIP_RA9701A) || (chipid == CHIP_RA9701A1))
        {
            /* registers are re-designed */
            ana_test = MADC_ANA_TEST_V2;
            ana_ctl = MADC_ANA_CTL_V2;
            ana_ctl2 = MADC_ANA_CTL2_V2;
            /* RA9701 calc_ps only has por reset */
            if (/*((calc_ps != 0x0U) && (calc_ps != 0xa8U)) ||*/
                (0U != ana_test) ||
                (0U != ana_ctl) ||
                (0U != ana_ctl2))
            {
                passwd_bak = ANA_PS;
                ANA_PS = 0x8eU;
                MADC_ANA_CTL2_V2 = 0x1b5a5U;
                MADC_ANA_CTL2_V2 = 0x1b5a5U;
                ana_ctl2 = MADC_ANA_CTL2_V2;
                if ((ANA_PS != 0x8eU) ||
                    (ana_ctl2 != 0x1b5a5U))
                {
                    res = 1U;
                }
                MADC_ANA_CTL2_V2 = 0x0U;
                ANA_PS = passwd_bak;
            }
        }
        else
        {
            /**
             * those registers should keep unchanged, otherwise means vbat power domain in wrong state
             * CALPS defines second-temp-calc password
             * LOSC_CFG1 defines losc_pd password
             * ANA_CTL defines RCH/BGR test switch password
             * ANA_TEST defines other test switch
            */
            ana_test = MADC_ANA_TEST;
            ana_ctl = MADC_ANA_CTL;
            losc_cfg2 = RTC_LOSC_CFG1;
            if (((calc_ps != 0x0U) && (calc_ps != 0xa8U)) ||
                (((losc_cfg2 & 0xffU) != 0x0U) && ((losc_cfg2 & 0xffU) != 0xa8U)) ||
                (ana_test != 0x1U) ||
                (ana_ctl != 0x0U))
            {
                res = 1U;
            }
        }

        if (0U == res)
        {
            if (((RTC_CTRL >> 10) & 0x1U) == 0x1U)
            {
                for (i = 0U; i < t; i++)
                {
                    if (((RTC_CTRL >> 10) & 0x1U) == 0x0U)
                    {
                        break;
                    }
                }

                if (i == t)
                {
                    res = 1U;
                }
            }
        }
    }
    return res;
}

static const unsigned int POR_TIME[] = {2, 56 * 2, 2 * 56 * 2, 2 * 2 * 56 * 2, 2 * 2 * 2 * 56 * 2, 2 * 2 * 2 * 2 * 56 * 2};
/**
 * @brief soft reset vbat power domain
 *
 */
void vbat_reset(void)
{
    unsigned int rtc_ioen_bak, rtc_iomode_bak;
    unsigned int ana_pad_bak;
    unsigned int dota_table_bak[10];
    unsigned int dota_ps_bak;
    unsigned int losc_cfg1_bak;
    unsigned int i, t;
    /* rn_chipid_t chipid = getChipid(); */

    /**
     * reset vbat domain if rtc-state-check is wrong
     * before reset, we should backup those registers:
     *   RTC_IOEN/IOMODE/CALPS/CAL_T0~9/LOSCCFG1
     */
    rtc_ioen_bak = RTC_IOEN;
    rtc_iomode_bak = RTC_IOMODE;
    dota_ps_bak = RTC_CALPS;
    for (i = 0U; i < 10U; i++)
    {
        dota_table_bak[i] = RTC_DOTATBL->dota[i];
    }
    ana_pad_bak = MADC_ANA_PAD;
    losc_cfg1_bak = RTC_LOSC_CFG1 & 0x1ffU;

    t = POR_TIME[currentClk_idx()];
    MADC_ANA_RST = ((unsigned int)0xa5U << 8) | ((unsigned int)0xa8U << 0); /* reset RTC */
    MADC_ANA_RST = ((unsigned int)0xa5U << 8) | ((unsigned int)0xa8U << 0);
    for (i = 0U; i < t; i++)
    {
        ;
    }
    MADC_ANA_RST = ((unsigned int)0xa5U << 8);
    MADC_ANA_RST = ((unsigned int)0xa5U << 8);
    MADC_ANA_RST = 0U;

    RTC_PS = 0x8eU;
    RTC_IOMODE = rtc_iomode_bak | ((unsigned int)0xbU << 4);
    RTC_IOEN = rtc_ioen_bak;
    RTC_IOMODE = rtc_iomode_bak;
    for (i = 0U; i < 10U; i++)
    {
        RTC_DOTATBL->dota[i] = dota_table_bak[i];
    }
    if (dota_ps_bak == 0xa8U)
    {
        RTC_CALPS = 0xa8U;
    }
    MADC_ANA_PAD = ana_pad_bak;
    if ((losc_cfg1_bak & 0xffU) == 0xa8U)
    {
        RTC_LOSC_CFG1 = 0x100U;
        RTC_LOSC_CFG1 = losc_cfg1_bak;
    }
}

// -*- r33873 -*-
