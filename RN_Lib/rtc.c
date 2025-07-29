/******************************************************************************
 * @file     rtc.c
 * @brief    RTC driver source code file for RN821x series SOC
 * @author   Renergy Technology
 * @version  V1.00
 * @date     2012-11-28
 *
 * @note
 * Copyright (C) 2008, Renergy Technology Inc. All rights reserved.
 ******************************************************************************/
#include "rn8xxx_v2_lib.h"
#include "utils.h"
#include "sysctrl_reg.h"

static void RtcWait(void);
static void RtcCalWait(void);

static void RtcWait(void)
{
    unsigned int i;
    for (i = 0U; i < 2000U; i++)
    {
        if (((RTC_CTRL >> 9) & 0x1U) == 0x0U)
        {
            break;
        }
    }
}

static void RtcCalWait(void)
{
    unsigned int i;

    for (i = 0U; i < 20000U; i++)
    {
        if (((RTC_CTRL >> 10) & 0x1U) == 0x0U)
        {
            break;
        }
    }
}

/**
 * @brief RtcReadDota
 *
 * @param
 *    none
 * @return
 *    unsigned short dota: dota value of RTC
 *
 */
unsigned short RtcReadDota(void)
{
    unsigned short i;
    unsigned int sys_ps;

    sys_ps = SYS_PS;
    SYS_PS = 0x82U;

    MOD1_EN |= ((unsigned int)1U << 9); /* WDT APB */
    MOD1_EN |= ((unsigned int)1U << 10);

    i = (unsigned short)RTC_DOTA;

    /* FEED_WDT; */

    SYS_PS = sys_ps;

    return i;
}

/* unsigned char SysConfCheck(void); */
/**
 * @brief RtcWriteDota
 *
 * @param
 *    in unsigned short dota: dota value of RTC
 * @return
 *    none
 *
 */
eRtcRet_TypeDef RtcWriteDota(unsigned short dota)
{
    unsigned int sys_ps, rtc_ctrl, rtcps_bak;
    eRtcRet_TypeDef res = RTC_PASS;
    rn_chipid_t chipid = getChipid();

    sys_ps = SYS_PS;
    SYS_PS = 0x82U;

    MOD1_EN |= ((unsigned int)1U << 10);
    MOD1_EN |= ((unsigned int)1U << 9); /* WDT APB */

    rtc_ctrl = RTC_CTRL;

    RtcWait();
    RTC_CTRL |= 0x100U;

    RtcWait();
    rtcps_bak = RTC_PS;
    RTC_PS = 0x8EU;

    /* if ((die_ver != 0xe0) && (die_ver != 0xf0)) */
    if ((chipid == CHIP_RA9103A) ||
        (chipid == CHIP_RA9103D) ||
        (chipid == CHIP_RA9103C) ||
        (chipid == CHIP_RA9103G))
    {
        /* single power domain */
        RtcWait();
        if (0x400U == (RTC_CTRL & 0x400U))
        {
            RtcCalWait();
        }
        RTC_DOTA = dota;
        if (0x400U == (RTC_CTRL & 0x400U))
        {
            RtcCalWait();
            RTC_DOTA = dota;
        }
    }
    else
    {
        /* separate vbat power domain */
        /* if (1 == RtcCalCheck(chipid)) {
             vbat_reset();
           }*/
        res = (eRtcRet_TypeDef)SysConfCheck();

        RtcWait();
        if (0x400U == (RTC_CTRL & 0x400U))
        {
            RtcCalWait();
        }
        RTC_DOTA = dota;
        if (0x400U == (RTC_CTRL & 0x400U))
        {
            RtcCalWait();
            RTC_DOTA = dota;
        }

        if (RTC_DOTA != dota)
            /* if (RtcCalCheck(chipid)) */
        {
            res = RTC_FAIL;
        }
    }

    RtcWait();
    RTC_CTRL = rtc_ctrl;

    RtcWait();
    RTC_PS = rtcps_bak;
    RtcWait();

    /* FEED_WDT; */

    SYS_PS = sys_ps;
    return res;
}

// -*- r33840 -*-
