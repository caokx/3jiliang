/******************************************************************************
 * @file     sysupdate.c
 * @brief    system update source code file for RN821x series SOC
 * @author   Renergy Technology
 * @version  V1.4
 * @date     2017-08-23
 *
 * @note
 * Copyright (C) 2008, Renergy Technology Inc. All rights reserved.
 ******************************************************************************/
#include "rn8xxx_v2_lib.h"
#include "sysctrl_reg.h"
#include "utils.h"

typedef enum
{
    REG_ANA_ADC = 0U,
    REG_ANA_CLK1,
    REG_ANA_CLK2,
    REG_ANA_LDO,
    REG_ANA_BGR,
    REG_ANA_PSW,
    REG_ANA_PWR,
    REG_ANA_CLK3,
    REG_ANA_SYS,
    REG_ANA_ULBGR1,
    REG_ANA_ULBGR2,
    REG_ANA_LURLS1,
    /* REG_ANA_LURLS1,*/
    REG_TRNG_CTRL,
    REG_MADC_TPSCTRL,
    REG_MADC_ADTEST,
    REG_LOSC_CFG2,
    REG_MADC_ANABGR,
    REG_MADC_ANALDO,
    REG_MADC_ANARCH,
    REG_MADC_SARCTRL2,
    REG_RTC_MODE,
    REG_RTC_ALPHAL,
    REG_RTC_ALPHAH,
    REG_RTC_XT0,
    REG_RTC_BETA,
    REG_RTC_TADJ,
    REG_RTC_ZT,
    REG_WDT_CTRL,
    REG_WDT_HALT,
    REG_WDT_STBY,
    REG_CONF_MAX
} conf_reg_idx_e;

typedef struct
{
    unsigned int reg_addr;
    unsigned int reg_passwd;
} conf_reg_t;

typedef struct
{
    conf_reg_idx_e  reg_id;
    /* 0 means spl0, 1 means spl1 */
    unsigned char   reg_spl_idx;
    /* offset in spl */
    unsigned char   reg_spl_addr;
    /* read and write data mask */
    unsigned short  reg_mask;
    unsigned short  reg_default;
} conf_info_t;

static eSysCtrlRet_TypeDef ldo_adj_a0(void);
static unsigned int sar_measure(void);
eSysCtrlRet_TypeDef ldo_adj_a1(void);
static eSysCtrlRet_TypeDef ldo_auto_adj(void);

static const conf_reg_t conf_reg[30];
static const conf_info_t spl_ra9103a_conf[17];
static const conf_info_t spl_ra9103d_conf[17];
static const conf_info_t spl_ra9103c_conf[20];
static const conf_info_t spl_ra9103e_conf[23];
static const conf_info_t spl_ra9103f_conf[24];
static const conf_info_t spl_ra9103g_conf[20];
static const conf_info_t spl_ra9701a_conf[17];

#define PARAM_B_V0P9   409270U    /* (0.39031008 * (1 << 20)) */
#define PARAM_A_V0P9   89492420U  /*(21.3366556 * (1 << 22)) */
#define PARAM_B_V0P8   365376U    /* (0.34844961 * (1 << 20)) */
#define PARAM_A_V0P8   100194166U /* (23.88815061 * (1 << 22)) */
static eSysCtrlRet_TypeDef ldo_adj_a0(void)
{
    unsigned int spl0_base = getMipAddr(0U) + 512U * 1024U;
    unsigned int calc_v0p9, calc_v0p8;
    unsigned int v09_b, v09_a, v08_b, v08_a;
    unsigned int rtcctrl;
    unsigned int temp;
    unsigned char cnt;
    unsigned int i;
    static unsigned int temp_prev = 0x0U;
    eSysCtrlRet_TypeDef res = SYSCTRL_PASS;

    v09_b = ((unsigned int)(*(unsigned short *)(spl0_base + 0x78U)) << 16) | (*(unsigned short *)(spl0_base + 0x76U));
    v09_a = ((unsigned int)(*(unsigned short *)(spl0_base + 0x7cU)) << 16) | (*(unsigned short *)(spl0_base + 0x7aU));
    v08_b = ((unsigned int)(*(unsigned short *)(spl0_base + 0x80U)) << 16) | (*(unsigned short *)(spl0_base + 0x7eU));
    v08_a = ((unsigned int)(*(unsigned short *)(spl0_base + 0x84U)) << 16) | (*(unsigned short *)(spl0_base + 0x82U));

    /* if all parameters are 0/0xffffffff, do nothing */
    if (((0U == v09_b) && (0U == v09_a) && (0U == v08_a) && (0U == v08_b)) ||
        ((0xffffffffU == v09_b) && (v09_b == v09_a) && (v09_b == v08_a) && (v09_b == v08_b)))
    {
        res = SYSCTRL_PASS;
    }
    else
    {
        SYS_PS = 0x82U;
        if (0x0U == ((MOD1_EN >> 10) & 0x1U))
        {
            MOD1_EN = MOD1_EN | ((unsigned int)1U << 10);
        }
        rtcctrl = RTC_CTRL & 0xffU;
        /* check rtc-temp-calc mode */
        if (((rtcctrl >> 6) & 0x3U) == 0x0U)
        {
            /* enable rtc-temp-calc */
            /* start tps firstly */
            RTC_CTRL = 0x1c0U;
            RTC_CTRL = 0x1c0U;
            RTC_TEMP = 0x0U;
            for (i = 0U; i < 1000U; i++)
            {
                if ((RTC_CTRL & 0x200U) == 0x0U)
                {
                    break;
                }
            }
            /* set default rtc-temp-calc */
            RTC_CTRL = 0x148U;
            RTC_CTRL = 0x148U;
        }
        else
        {
            /* read rtc temperature safely */
            temp = RTC_TEMP;
            cnt = 0U;
            for (i = 0U; i < 6U; i++)
            {
                if (temp != RTC_TEMP)
                {
                    temp = RTC_TEMP;
                }
                else
                {
                    cnt++;
                    if (cnt >= 3U)
                    {
                        break;
                    }
                }
            }
            if (cnt < 3U)
            {
                /* temp is not stable, fail! */
                res = SYSCTRL_FAIL;
            }
            else
            {
                if (temp == temp_prev)
                {
                    /* return if temp is same with previous */
                    res = SYSCTRL_PASS;
                }
                else
                {
                    if ((rtcctrl >> 6) == 0x2U)
                    {
                        if (0xEA65U == RTC_MODE1)
                        {
                            /* keep 10bit temp value if rtc-temp-calc mode is user mode0 */
                            temp >>= 6U;
                        }
                    }

                    if (1U == ((temp >> 9) & 0x1U))
                    {
                        /* -55 degree */
                        if (temp < 0x324U)
                        {
                            temp = 0x324U;
                        }
                        calc_v0p9 = PARAM_A_V0P9 - PARAM_B_V0P9 * ((~temp + 1U) & 0x1ffU);
                        calc_v0p8 = PARAM_A_V0P8 - PARAM_B_V0P8 * ((~temp + 1U) & 0x1ffU);
                    }
                    else
                    {
                        /* 125 degree */
                        if (temp > 0x1f4U)
                        {
                            temp = 0x1f4U;
                        }
                        calc_v0p9 = PARAM_B_V0P9 * temp + PARAM_A_V0P9;
                        calc_v0p8 = PARAM_B_V0P8 * temp + PARAM_A_V0P8;
                    }
                    if ((calc_v0p9 >> 31) == 0x1U)
                    {
                        calc_v0p9 = 0U;
                    }
                    /* Q22 */
                    calc_v0p9 >>= 21U;
                    if (1U == (calc_v0p9 & 0x1U))
                    {
                        calc_v0p9++;
                    }
                    calc_v0p9 >>= 1U;
                    if (calc_v0p9 > 0x7fU)
                    {
                        calc_v0p9 = 0x7fU;
                    }

                    if ((calc_v0p8 >> 31) == 0x1U)
                    {
                        calc_v0p8 = 0U;
                    }
                    calc_v0p8 >>= 21U;
                    if (1U == (calc_v0p8 & 0x1U))
                    {
                        calc_v0p8++;
                    }
                    calc_v0p8 >>= 1U;
                    if (calc_v0p8 > 0x7fU)
                    {
                        calc_v0p8 = 0x7fU;
                    }

                    SYS_PS = 0x75U;
                    *(volatile unsigned int *)ANA_ULBGR2 = 0xa5670000U | (calc_v0p8 << 1) | (calc_v0p9 << 8) | (*(volatile unsigned int *)ANA_ULBGR2 & 0x1U);
                    temp_prev = temp;
                }
            }
        }
    }
    return res;
}

#define ERR_RANGE  (8U)
#define TARGET_V  (800U)
/* max measure loop */
#define N  (10U)
/* ulbgr stable time(us unit) when vsel modify=7ms (1300) */
#define ULBGR_STABLE_T  (1300U)
/* SAR measure timeout(us unit) Ttps=11.2ms  --> [3*Ttps] (35000) */
#define SAR_T (35000U)
/* +/-10% 20230613 fix! */
#define V0P8_MIN (720U)
#define V0P8_MAX (880U)

static unsigned int sar_measure(void)
{
    unsigned int i;
    unsigned int vol = 0U;

    for (i = 0U; i < 500U; i++)
    {
        MADC_SAR_STATUS = 1U;
        if ((MADC_SAR_STATUS & 0x1U) == 0x0U)
        {
            break;
        }
    }
    MADC_SAR_START = 1U;
    /* T=360us, timeout=4*T */
    usTimeout((unsigned int)(&MADC_SAR_STATUS), 1U, 0U, SAR_T, CHIP_RA9701A);
    if (0x1U == (MADC_SAR_STATUS & 0x1U))
    {
        vol = (5000U * MADC_SAR_DAT2) / 16384U;
        if ((vol < V0P8_MIN) || (vol > V0P8_MAX))
        {
            vol = 0U;
        }
    }

    return vol;
}

eSysCtrlRet_TypeDef ldo_adj_a1(void)
{
    unsigned int spl0_base = getMipAddr(0U) + 512U * 1024U;
    unsigned int sysps_bak = SYS_PS;
    unsigned int mod1_bak = MOD1_EN;
    unsigned int sarctl_bak;
    unsigned int vol;
    unsigned int vol_pre;
    unsigned int ulbgr2;
    unsigned int vsel;
    unsigned char sar_restore;
    unsigned char retry;
    unsigned char dir;
    unsigned char sar_matched = 0U;
    eSysCtrlRet_TypeDef res = SYSCTRL_PASS;

    if (0x1324U == *(unsigned short *)(spl0_base + 0x76U))
    {
        res = SYSCTRL_PASS;
    }
    else
    {
        SYS_PS = 0x82U;
        MOD1_EN |= ((unsigned int)1U << 10);

        SYS_PS = 0x75U;
        /* vref_0p8 testen */
        MEM32(TEST_CTL) = 0xa5730000U | ((unsigned int)1U << 6) | ((unsigned int)1U << 2);

        sarctl_bak = MADC_SAR_CTL;
        if (0x1U == MADC_SAR_START)
        {
            sar_restore = 1U;
            usTimeout((unsigned int)(&MADC_SAR_START), 1U, 1U, SAR_T, CHIP_RA9701A);
        }
        else if (0x1U == (MADC_SAR_STATUS & 0x1U))
        {
            sar_restore = 1U;
        }
        else
        {
            sar_restore = 0U;
        }

        /* ch=0xd, pga=1 */
        MADC_SAR_CTL = ((unsigned int)0x5U << 12) | ((unsigned int)0xeU << 7) | ((unsigned int)1U << 6) | ((unsigned int)5U << 0) | ((unsigned int)1U << 3);
        vol = sar_measure();
        if ((vol < (TARGET_V - ERR_RANGE)) || (vol > (TARGET_V + ERR_RANGE)))
        {
            SYS_PS = 0x75U;
            /* open dig5 write-window */
            MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x55U << 0);
            MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x55U << 0) | ((unsigned int)0x23U << 10);

            ulbgr2 = MEM32(ANA_ULBGR2);
            vsel = (ulbgr2 >> 1) & 0x3fU;
            ulbgr2 = ulbgr2 & (~((unsigned int)0x3fU << 1));

            vol_pre = vol;
            /* 1=downward, 0=upward */
            dir = (vol > TARGET_V) ? 1U : 0U;

            for (retry = 0U; retry < N; retry++)
            {
                vol = sar_measure();
                if (vol == TARGET_V)
                {
                    sar_matched = 1U;
                }
                else if (vol == 0U)
                {
                    /* sar measure is invalid, do it again! */
                }
                else
                {
                    if (dir == 1U)
                    {
                        /* downward */
                        if (vol < TARGET_V)
                        {
                            if ((TARGET_V - vol) > (vol_pre - TARGET_V))
                            {
                                vsel++;
                                MEM32(ANA_ULBGR2) = 0xa5670000U | ulbgr2 | (vsel << 1);
                            }
                            sar_matched = 1U;
                        }
                        else
                        {
                            vsel--;
                            if (vsel == 0U)
                            {
                                res = SYSCTRL_FAIL;
                                sar_matched = 1U;
                            }
                        }
                    }
                    else
                    {
                        /* upward */
                        if (vol > TARGET_V)
                        {
                            if ((vol - TARGET_V) > (TARGET_V - vol_pre))
                            {
                                vsel--;
                                MEM32(ANA_ULBGR2) = 0xa5670000U | ulbgr2 | (vsel << 1);
                            }
                            sar_matched = 1U;
                        }
                        else
                        {
                            vsel++;
                            if (vsel >= 0x3fU)
                            {
                                res = SYSCTRL_FAIL;
                                sar_matched = 1U;
                            }
                        }
                    }
                    if (1U != sar_matched)
                    {
                        vol_pre = vol;
                        MEM32(ANA_ULBGR2) = 0xa5670000U | ulbgr2 | (vsel << 1);
                        usTimeout(0U, 0U, 0U, ULBGR_STABLE_T, CHIP_RA9701A);
                    }
                }

                if (1U == sar_matched)
                {
                    break;
                }
            }
            /* close dig5 write-window */
            MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x0U << 0);
            MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x0U << 0) | ((unsigned int)0x23U << 10);
        }
        MEM32(TEST_CTL) = 0xa5730000U;

        MADC_SAR_CTL = sarctl_bak;
        if (1U == sar_restore)
        {
            MADC_SAR_START = 1U;
        }
        SYS_PS = 0x82U;
        MOD1_EN = mod1_bak;
        SYS_PS = sysps_bak;
    }

    return res;
}

static eSysCtrlRet_TypeDef ldo_auto_adj(void)
{
    rn_chipid_t chipid = getChipid();
    eSysCtrlRet_TypeDef res;

    if (CHIP_RA9701A == chipid)
    {
        res = ldo_adj_a0();
    }
    else if (CHIP_RA9701A1 == chipid)
    {
        res = ldo_adj_a1();
    }
    else
    {
        res = SYSCTRL_PASS;
    }

    return res;
}

static const conf_reg_t conf_reg[30] =
{
    {ANA_ADC, 0xa5570000U},
    {ANA_CLK1, 0xa5270000U},
    {ANA_CLK2, 0xa5360000U},
    {ANA_LDO, 0xa5580000U},
    {ANA_BGR, 0xa5280000U},
    {ANA_PSW, 0xa5790000U},
    {ANA_PWR, 0xa5430000U},
    {ANA_CLK3, 0xa5750000U},
    {ANA_SYS, 0xa5370000U},
    {ANA_ULBGR1, 0xa5380000U},
    {ANA_ULBGR2, 0xa5670000U},
    {ANA_LURLS1, 0xa5470000U},
    {TRNG_CTRL, 0x00000000U},
    /* incompatible reg */
    {MADC_TPSCTRL, 0x0000e000U},
    /* incompatible reg */
    {MADC_ADTEST, 0x00010000U},
    {LOSC_CFG2, 0x00010000U},
    /* incompatible reg */
    {MADC_ANABGR, 0x00010000U},
    /* incompatible reg */
    {MADC_ANALDO, 0x00010000U},
    /* incompatible reg */
    {MADC_ANARCH, 0x00010000U},
    /* incompatible reg */
    {MADC_SARCTRL2, 0x00010000U},
    {RTC_MODE, 0x00000000U},
    {RTC_ALPHAL, 0x00000000U},
    {RTC_ALPHAH, 0x00000000U},
    {RTC_XT0, 0x00000000U},
    {RTC_BETA, 0x00000000U},
    {RTC_TADJ, 0x00000000U},
    {RTC_ZT, 0x00000000U},
    {WDT_CTRL, 0x00000000U},
    {WDT_HALT, 0x00000000U},
    {WDT_STBY, 0x00000000U},
};

static const conf_info_t spl_ra9103a_conf[17] =
{
    {REG_ANA_ADC, 0U, 0x10U, 0x03ffU, 0x0040U},
    {REG_ANA_CLK1, 0U, 0x12U, 0x7fffU, 0x0420U},
    {REG_ANA_CLK2, 0U, 0x14U, 0x00ffU, 0x0014U},
    {REG_ANA_LDO, 0U, 0x16U, 0x007fU, 0x0058U},
    {REG_ANA_BGR, 0U, 0x18U, 0xffffU, 0x615aU},
    {REG_ANA_PSW, 0U, 0x1aU, 0x007fU, 0x0010U},
    {REG_MADC_TPSCTRL, 0U, 0x20U, 0x1fffU, 0x193bU},
    {REG_MADC_ADTEST, 0U, 0x22U, 0x003fU, 0x0028U},
    {REG_RTC_MODE, 1U, 0x08U, 0x0001U, 0x0001U},
    {REG_RTC_ALPHAL, 1U, 0x0cU, 0x07ffU, 0x03eeU},
    {REG_RTC_ALPHAH, 1U, 0x0eU, 0x07ffU, 0x04cfU},
    {REG_RTC_XT0, 1U, 0x10U, 0x007fU, 0x0064U},
    {REG_RTC_TADJ, 1U, 0x1cU, 0x07ffU, 0x0680U},
    {REG_RTC_ZT, 1U, 0x1eU, 0x7fffU, 0x0116U},
    {REG_WDT_CTRL, 1U, 0x14U, 0x00eeU, 0x0068U},
    {REG_WDT_HALT, 1U, 0x18U, 0xffffU, 0x7e5aU},
    {REG_WDT_STBY, 1U, 0x1aU, 0xffffU, 0xa538U},
};

static const conf_info_t spl_ra9103d_conf[17] =
{
    {REG_ANA_ADC, 0U, 0x10U, 0x03ffU, 0x0040U},
    {REG_ANA_CLK1, 0U, 0x12U, 0x7fffU, 0x0420U},
    {REG_ANA_CLK2, 0U, 0x14U, 0xffffU, 0x4e14U},
    {REG_ANA_LDO, 0U, 0x16U, 0x3ff0U, 0x0850U},
    {REG_ANA_BGR, 0U, 0x18U, 0xffffU, 0x615aU},
    {REG_ANA_PSW, 0U, 0x1aU, 0x01ffU, 0x0010U},
    {REG_MADC_TPSCTRL, 0U, 0x20U, 0x1fffU, 0x193bU},
    {REG_MADC_ADTEST, 0U, 0x22U, 0x003fU, 0x0028U},
    {REG_RTC_MODE, 1U, 0x08U, 0x0001U, 0x0001U},
    {REG_RTC_ALPHAL, 1U, 0x0cU, 0x07ffU, 0x03eeU},
    {REG_RTC_ALPHAH, 1U, 0x0eU, 0x07ffU, 0x04cfU},
    {REG_RTC_XT0, 1U, 0x10U, 0x007fU, 0x0064U},
    {REG_RTC_TADJ, 1U, 0x1cU, 0x07ffU, 0x0680U},
    {REG_RTC_ZT, 1U, 0x1eU, 0x7fffU, 0x0116U},
    {REG_WDT_CTRL, 1U, 0x14U, 0x00eeU, 0x0068U},
    {REG_WDT_HALT, 1U, 0x18U, 0xffffU, 0x7e5aU},
    {REG_WDT_STBY, 1U, 0x1aU, 0xffffU, 0xa538U},
};

static const conf_info_t spl_ra9103c_conf[20] =
{
    {REG_ANA_ADC,      0U, 0x10U, 0x7fffU, 0x3440U},
    {REG_ANA_CLK1,     0U, 0x12U, 0x7fffU, 0x0060U},
    {REG_ANA_CLK2,     0U, 0x14U, 0x1fffU, 0x0914U},
    {REG_ANA_LDO,      0U, 0x16U, 0x3fffU, 0x145fU},
    {REG_ANA_BGR,      0U, 0x18U, 0xffffU, 0x612aU},
    {REG_ANA_PSW,      0U, 0x1aU, 0x0088U, 0x0000U},
    {REG_MADC_TPSCTRL, 0U, 0x20U, 0x1fffU, 0x193bU},
    {REG_MADC_ADTEST,  0U, 0x22U, 0x003fU, 0x0028U},
    {REG_ANA_PWR,      0U, 0x26U, 0x7fffU, 0x7000U},
    {REG_ANA_CLK3,     0U, 0x28U, 0xffffU, 0x3ce4U},
    {REG_ANA_SYS,      0U, 0x2aU, 0x7fffU, 0x6c22U},
    {REG_RTC_MODE,     1U, 0x08U, 0x0001U, 0x0001U},
    {REG_RTC_ALPHAL,   1U, 0x0cU, 0x07ffU, 0x03eeU},
    {REG_RTC_ALPHAH,   1U, 0x0eU, 0x07ffU, 0x04cfU},
    {REG_RTC_XT0,      1U, 0x10U, 0x007fU, 0x0064U},
    {REG_RTC_TADJ,     1U, 0x1cU, 0x07ffU, 0x0680U},
    {REG_RTC_ZT,       1U, 0x1eU, 0x7fffU, 0x0116U},
    {REG_WDT_CTRL,     1U, 0x14U, 0x00eeU, 0x0068U},
    {REG_WDT_HALT,     1U, 0x18U, 0xffffU, 0x7e5aU},
    {REG_WDT_STBY,     1U, 0x1aU, 0xffffU, 0xa538U},
};

static const conf_info_t spl_ra9103e_conf[23] =
{
    {REG_ANA_ADC,       0U, 0x10U, 0x7c00U, 0x3400U},
    {REG_ANA_CLK1,      0U, 0x12U, 0x79ffU, 0x0060U},
    {REG_ANA_CLK2,      0U, 0x14U, 0x1f00U, 0x0900U},
    {REG_ANA_LDO,       0U, 0x16U, 0x1fffU, 0x29ffU},
    {REG_ANA_PSW,       0U, 0x1aU, 0x0088U, 0x0000U},
    {REG_MADC_TPSCTRL,  0U, 0x20U, 0x1fffU, 0x083bU},
    {REG_MADC_ADTEST,   0U, 0x22U, 0x0fffU, 0x03e8U},
    {REG_ANA_SYS,       0U, 0x2aU, 0xffffU, 0x2c22U},
    {REG_LOSC_CFG2,     0U, 0x52U, 0xffffU, 0x6428U},
    {REG_MADC_ANABGR,   0U, 0x54U, 0xfff3U, 0x6150U},
    {REG_MADC_ANALDO,   0U, 0x58U, 0x000fU, 0x0004U},
    {REG_MADC_ANARCH,   0U, 0x5aU, 0x3fffU, 0x0300U},
    {REG_MADC_SARCTRL2, 0U, 0x5cU, 0x001fU, 0x0003U},
    {REG_RTC_MODE,      1U, 0x08U, 0x0001U, 0x0001U},
    {REG_RTC_ALPHAL,    1U, 0x0cU, 0x07ffU, 0x03eeU},
    {REG_RTC_ALPHAH,    1U, 0x0eU, 0x07ffU, 0x04cfU},
    {REG_RTC_XT0,       1U, 0x10U, 0x007fU, 0x0064U},
    {REG_RTC_BETA,      1U, 0x12U, 0x03ffU, 0x00ffU},
    {REG_WDT_CTRL,      1U, 0x14U, 0x00eeU, 0x0068U},
    {REG_WDT_HALT,      1U, 0x18U, 0xffffU, 0x7e5aU},
    {REG_WDT_STBY,      1U, 0x1aU, 0xffffU, 0xa538U},
    {REG_RTC_TADJ,      1U, 0x1cU, 0x07ffU, 0x0680U},
    {REG_RTC_ZT,        1U, 0x1eU, 0x7fffU, 0x0116U},
};

static const conf_info_t spl_ra9103f_conf[24] =
{
    {REG_ANA_ADC,       0U, 0x10U, 0x7c00U, 0x3400U},
    {REG_ANA_CLK1,      0U, 0x12U, 0x79ffU, 0x0060U},
    {REG_ANA_CLK2,      0U, 0x14U, 0x1f00U, 0x0900U},
    {REG_ANA_LDO,       0U, 0x16U, 0x7fffU, 0x29ffU},
    {REG_ANA_PSW,       0U, 0x1aU, 0x0088U, 0x0000U},
    {REG_MADC_TPSCTRL,  0U, 0x20U, 0x1fffU, 0x083bU},
    {REG_MADC_ADTEST,   0U, 0x22U, 0x0fffU, 0x03e8U},
    {REG_ANA_CLK3,      0U, 0x28U, 0x0380U, 0x0080U},
    {REG_ANA_SYS,       0U, 0x2aU, 0xffffU, 0x2c22U},
    {REG_LOSC_CFG2,     0U, 0x52U, 0xffffU, 0x6428U},
    {REG_MADC_ANABGR,   0U, 0x54U, 0xfff3U, 0x6150U},
    {REG_MADC_ANALDO,   0U, 0x58U, 0x000fU, 0x0004U},
    {REG_MADC_ANARCH,   0U, 0x5aU, 0x3fffU, 0x0300U},
    {REG_MADC_SARCTRL2, 0U, 0x5cU, 0x001fU, 0x0003U},
    {REG_RTC_MODE,      1U, 0x08U, 0x0001U, 0x0001U},
    {REG_RTC_ALPHAL,    1U, 0x0cU, 0x07ffU, 0x03eeU},
    {REG_RTC_ALPHAH,    1U, 0x0eU, 0x07ffU, 0x04cfU},
    {REG_RTC_XT0,       1U, 0x10U, 0x007fU, 0x0064U},
    {REG_RTC_BETA,      1U, 0x12U, 0x03ffU, 0x00ffU},
    {REG_WDT_CTRL,      1U, 0x14U, 0x00eeU, 0x0068U},
    {REG_WDT_HALT,      1U, 0x18U, 0xffffU, 0x7e5aU},
    {REG_WDT_STBY,      1U, 0x1aU, 0xffffU, 0xa538U},
    {REG_RTC_TADJ,      1U, 0x1cU, 0x07ffU, 0x0680U},
    {REG_RTC_ZT,        1U, 0x1eU, 0x7fffU, 0x0116U},
};

static const conf_info_t spl_ra9103g_conf[20] =
{
    {REG_ANA_ADC,       0U, 0x10U, 0x7fffU, 0x3400U},
    {REG_ANA_CLK1,      0U, 0x12U, 0x79ffU, 0x0060U},
    {REG_ANA_CLK2,      0U, 0x14U, 0x1fffU, 0x0914U},
    {REG_ANA_LDO,       0U, 0x16U, 0x3fffU, 0x145fU},
    {REG_ANA_BGR,       0U, 0x18U, 0xffffU, 0x612aU},
    {REG_ANA_PSW,       0U, 0x1aU, 0x0088U, 0x0000U},
    {REG_MADC_TPSCTRL,  0U, 0x20U, 0x1fffU, 0x193bU},
    {REG_MADC_ADTEST,   0U, 0x22U, 0x003fU, 0x0028U},
    {REG_ANA_PWR,       0U, 0x26U, 0x7fffU, 0x7000U},
    {REG_ANA_CLK3,      0U, 0x28U, 0xc3ffU, 0x3ce4U},
    {REG_ANA_SYS,       0U, 0x2aU, 0x0007U, 0x0007U},
    {REG_RTC_MODE,      1U, 0x08U, 0x0001U, 0x0001U},
    {REG_RTC_ALPHAL,    1U, 0x0cU, 0x07ffU, 0x03eeU},
    {REG_RTC_ALPHAH,    1U, 0x0eU, 0x07ffU, 0x04cfU},
    {REG_RTC_XT0,       1U, 0x10U, 0x007fU, 0x0064U},
    {REG_WDT_CTRL,      1U, 0x14U, 0x00eeU, 0x0068U},
    {REG_WDT_HALT,      1U, 0x18U, 0xffffU, 0x7e5aU},
    {REG_WDT_STBY,      1U, 0x1aU, 0xffffU, 0xa538U},
    {REG_RTC_TADJ,      1U, 0x1cU, 0x07ffU, 0x0680U},
    {REG_RTC_ZT,        1U, 0x1eU, 0x7fffU, 0x0116U},
};

static const conf_info_t spl_ra9701a_conf[17] =
{
    {REG_ANA_CLK1,      0U, 0x12U, 0x07ffU, 0x0009U},
    {REG_ANA_CLK2,      0U, 0x14U, 0x3fffU, 0x0680U},
    /* {REG_ANA_LDO,       0U, 0x16U, 0xff00U, 0x8803U},*/
    {REG_MADC_TPSCTRL,  0U, 0x44U, 0x1fffU, 0x083bU},
    {REG_MADC_ADTEST,   0U, 0x42U, 0x7ffcU, 0x5b58U},
    {REG_ANA_CLK3,      0U, 0x1eU, 0x03ffU, 0x0216U},
    {REG_ANA_SYS,       0U, 0x20U, 0x07ffU, 0x041cU},
    {REG_LOSC_CFG2,     0U, 0x4cU, 0xffffU, 0x6428U},
    {REG_MADC_ANABGR,   0U, 0x46U, 0xfff1U, 0x8200U},
    {REG_MADC_ANALDO,   0U, 0x48U, 0x000fU, 0x0004U},
    {REG_MADC_ANARCH,   0U, 0x4aU, 0x3fffU, 0x0180U},
    {REG_MADC_SARCTRL2, 0U, 0x40U, 0x7fffU, 0x2904U},
    /* {REG_ANA_ULBGR1,    0U, 0x22U, 0x7fffU, 0x4088U},*/
    /* {REG_ANA_ULBGR2,    0U, 0x24U, 0x7fffU, 0x2041U},*/
    /* {REG_ANA_LURLS1,    0U, 0x26U, 0xffffU, 0x0000U},*/
    /* {REG_ANA_LURLS1,    0U, 0x28U, 0xffffU, 0x01c5U},*/
    {REG_TRNG_CTRL,     0U, 0x54U, 0xffffU, 0x00e4U},
    {REG_RTC_MODE,      0U, 0x50U, 0x0001U, 0x0001U},
    {REG_RTC_TADJ,      0U, 0x4eU, 0x07ffU, 0x0670U},
    {REG_RTC_ZT,        0U, 0x52U, 0x7fffU, 0x0d11U},
    /* {REG_RTC_ALPHAL,    1U 0x0cU, 0x07ffU, 0x03eeU},*/
    /* {REG_RTC_ALPHAH,    1U 0x0eU, 0x07ffU, 0x04cfU},*/
    /* {REG_RTC_XT0,       1U 0x10U, 0x007fU, 0x0064U},*/
    /* {REG_WDT_CTRL,      1U 0x14U, 0x00eeU, 0x0068U},*/
    {REG_WDT_HALT,      1U, 0x18U, 0xffffU, 0x7e5aU},
    {REG_WDT_STBY,      1U, 0x1aU, 0xffffU, 0xa538U},
};

eSysCtrlRet_TypeDef SysConfCheck(void)
{
    rn_chipid_t chipid = getChipid();
    unsigned int *spl_base;
    unsigned int spl_len;
    unsigned char spl_valid[2];
    const conf_info_t *spl_conf_p;
    const conf_info_t *spl_conf;
    unsigned int spl_conf_len;
    unsigned int i, p;
    eSysCtrlRet_TypeDef res = SYSCTRL_PASS;
    unsigned int sysps_bak = SYS_PS;
    unsigned int mod0_bak = MOD0_EN;
    unsigned int mod1_bak = MOD1_EN;
    unsigned int rtcps_bak;
    unsigned int anaps_bak = 0x0U;
    unsigned short temp;
    unsigned short cnt;
    unsigned char vbat_flag = 0U;
    volatile unsigned int tie_addr = 0x0U;
    unsigned int tt;
    unsigned int reg_addr;

    if (((OSC_CTRL1 >> 4) & 0x1U) == 0x0U)
    {
        switch (chipid)
        {
            case CHIP_RA9103A:
                spl_base = (unsigned int *)(getMipAddr(1U) + 0x00c08000U);
                spl_len = 64U;
                spl_conf_p = spl_ra9103a_conf;
                spl_conf_len = sizeof(spl_ra9103a_conf) / sizeof(conf_info_t);
                break;
            case CHIP_RA9103D:
                spl_base = (unsigned int *)(getMipAddr(1U) + 0x00c08000U);
                spl_len = 64U;
                spl_conf_p = spl_ra9103d_conf;
                spl_conf_len = sizeof(spl_ra9103d_conf) / sizeof(conf_info_t);
                break;
            case CHIP_RA9103C:
                spl_base = (unsigned int *)(getMipAddr(1U) + 0x00c08000U);
                spl_len = 128U;
                spl_conf_p = spl_ra9103c_conf;
                spl_conf_len = sizeof(spl_ra9103c_conf) / sizeof(conf_info_t);
                break;
            case CHIP_RA9103E:
                spl_base = (unsigned int *)(getMipAddr(1U) + 0x00c08000U);
                spl_len = 128U;
                spl_conf_p = spl_ra9103e_conf;
                spl_conf_len = sizeof(spl_ra9103e_conf) / sizeof(conf_info_t);
                vbat_flag = 1U;
                tie_addr = 0x4002C038U;
                break;
            case CHIP_RA9103F:
                spl_base = (unsigned int *)(getMipAddr(0U) + 0x00080000U);
                spl_len = 256U;
                spl_conf_p = spl_ra9103f_conf;
                spl_conf_len = sizeof(spl_ra9103f_conf) / sizeof(conf_info_t);
                vbat_flag = 1U;
                tie_addr = 0x4002C038U;
                break;
            case CHIP_RA9103G:
                spl_base = (unsigned int *)(getMipAddr(0U) + 0x00080000U);
                spl_len = 256U;
                spl_conf_p = spl_ra9103g_conf;
                spl_conf_len = sizeof(spl_ra9103g_conf) / sizeof(conf_info_t);
                break;
            case CHIP_RA9701A:
            case CHIP_RA9701A1:
                spl_base = (unsigned int *)(getMipAddr(0U) + 0x00080000U);
                spl_len = 512U;
                spl_conf_p = spl_ra9701a_conf;
                spl_conf_len = sizeof(spl_ra9701a_conf) / sizeof(conf_info_t);
                vbat_flag = 1U;
                tie_addr = 0x4002C074U;
                break;
            default:
                spl_base = (unsigned int *)(getMipAddr(1U) + 0x00c08000U);
                spl_len = 64U;
                spl_conf_p = spl_ra9103a_conf;
                spl_conf_len = sizeof(spl_ra9103a_conf) / sizeof(conf_info_t);
                break;
        }

        SYS_PS = 0x82U;
        /* EMB */
        MOD0_EN |= ((unsigned int)1U << 3);
        /* RTC */
        MOD1_EN |= (((unsigned int)1U << 11) | ((unsigned int)1U << 10) | ((unsigned int)1U << 9));
        rtcps_bak = RTC_PS;
        SYS_PS = 0x75U;
        RTC_PS = 0x8eU;

        /* vbat power domain check */
        if (1U == vbat_flag)
        {
            anaps_bak = ANA_PS;
            ANA_PS = 0x8eU;
            if (1U == RtcCalCheck(chipid))
            {
                vbat_reset();
            }
            RTC_PS = 0x8eU;
            MEM32(tie_addr) = (unsigned int)0xaU << 12;
            MEM32(tie_addr) = 0U;
        }
        WDT_PS = 0x70U;
        WDT_PS = 0x7eU;
        spl_valid[0U] = check_spl_valid(spl_base, spl_len, 0U);
        tt = (unsigned int)spl_base;
        tt += spl_len;
        spl_valid[1U] = check_spl_valid((unsigned int *)tt, spl_len, 1U);

        /* configuration info registers check */
        for (i = 0U; i < spl_conf_len; i++)
        {
            p = (unsigned int)(spl_conf_p);
            p += i * (unsigned int)(sizeof(conf_info_t));
            spl_conf = (const conf_info_t *)(p);
            reg_addr = conf_reg[spl_conf->reg_id].reg_addr;
            if ((reg_addr == MADC_TPSCTRL) && ((chipid == CHIP_RA9701A) || (CHIP_RA9701A1 == chipid)))
            {
                reg_addr = MADC_TPSCTRL_V2;
            }
            if ((reg_addr == MADC_ADTEST) && ((chipid == CHIP_RA9701A) || (CHIP_RA9701A1 == chipid)))
            {
                reg_addr = MADC_ADTEST_V2;
            }
            if ((reg_addr == MADC_ANABGR) && ((chipid == CHIP_RA9701A) || (CHIP_RA9701A1 == chipid)))
            {
                reg_addr = MADC_ANABGR_V2;
            }
            if ((reg_addr == MADC_ANALDO) && ((chipid == CHIP_RA9701A) || (CHIP_RA9701A1 == chipid)))
            {
                reg_addr = MADC_ANALDO_V2;
            }
            if ((reg_addr == MADC_ANARCH) && ((chipid == CHIP_RA9701A) || (CHIP_RA9701A1 == chipid)))
            {
                reg_addr = MADC_ANARCH_V2;
            }
            if ((reg_addr == MADC_SARCTRL2) && ((chipid == CHIP_RA9701A) || (CHIP_RA9701A1 == chipid)))
            {
                reg_addr = MADC_SARCTRL2_V2;
            }
            if (0U == spl_valid[spl_conf->reg_spl_idx])
            {
                /* check conf. reg with default value if spl invalid */
                if (((unsigned short)MEM32(reg_addr) & spl_conf->reg_mask) != (spl_conf->reg_default & spl_conf->reg_mask))
                {
                    temp = ((unsigned short)MEM32(reg_addr) & (unsigned short)(~spl_conf->reg_mask)) & spl_conf->reg_mask;
                    /* spc1: need to modify ldo_ldo according to sysmode */
                    if ((reg_addr) == (conf_reg[REG_ANA_LDO].reg_addr))
                    {
                        if ((CHIP_RA9701A == chipid) || (CHIP_RA9701A1 == chipid))
                        {
                            if (CHIP_RA9701A1 == chipid)
                            {
                                /* open dig5 write-window */
                                MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x55U << 0);
                                MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x55U << 0) | ((unsigned int)0x23U << 10);
                            }
                            if (0U == ((OSC_CTRL1 >> 4) & 0x1U))
                            {
                                /* light-load */
                                temp = (temp & 0xff00U) | 0x0069U;
                            }
                            else
                            {
                                /* safe-load */
                                temp = temp & (unsigned short)(~(unsigned short)0xffU);
                            }
                            if (CHIP_RA9701A1 == chipid)
                            {
                                /* close dig5 write-window */
                                MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x0U << 0);
                                MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x0U << 0) | ((unsigned int)0x23U << 10);
                            }
                        }
                    }

                    if (0U != conf_reg[spl_conf->reg_id].reg_passwd)
                    {
                        MEM32(reg_addr) = (spl_conf->reg_default & (unsigned int)spl_conf->reg_mask) | conf_reg[spl_conf->reg_id].reg_passwd | (unsigned int)temp;
                    }
                    MEM32(reg_addr) = (spl_conf->reg_default & (unsigned int)spl_conf->reg_mask) | (unsigned int)temp;

                    /* spc2: need to wait sync when access wdt */
                    if ((reg_addr & 0xffffff00U) == (conf_reg[REG_WDT_CTRL].reg_addr & 0xffffff00U))
                    {
                        /* 10Khz, 5 ticks= 500us; 14700 sysclk@29Mhz, loops=14700/28(1 loop)=525 */
                        for (cnt = 0U; cnt < 1000U; cnt++)
                        {
                            if (0U == (MEM32(WDT_EN) & ((unsigned int)1U << 8)))
                            {
                                break;
                            }
                        }
                    }

                    if ((MEM32(reg_addr) & (unsigned int)spl_conf->reg_mask) != (spl_conf->reg_default & (unsigned int)spl_conf->reg_mask))
                    {
                        res = SYSCTRL_FAIL;
                    }
                }
            }
            else
            {
                /* check conf. reg with spl */
                tt = (unsigned int)spl_base;
                temp = MEM16(tt + spl_conf->reg_spl_idx * spl_len + spl_conf->reg_spl_addr) & spl_conf->reg_mask;
                if ((unsigned short)(MEM32(reg_addr) & spl_conf->reg_mask) != temp)
                {
                    temp = ((unsigned short)MEM32(reg_addr) & (unsigned short)(~spl_conf->reg_mask)) & spl_conf->reg_mask;
                    if ((reg_addr) == (conf_reg[REG_ANA_LDO].reg_addr))
                    {
                        if ((CHIP_RA9701A == chipid) || (CHIP_RA9701A1 == chipid))
                        {
                            if (CHIP_RA9701A1 == chipid)
                            {
                                /* open dig5 write-window */
                                MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x55U << 0);
                                MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x55U << 0) | ((unsigned int)0x23U << 10);
                            }
                            if (0U == ((OSC_CTRL1 >> 4) & 0x1U))
                            {
                                temp = (temp & 0xff00U) | 0x0069U;
                            }
                            else
                            {
                                temp = temp & (unsigned short)(~(unsigned short)0xffU);
                            }
                            if (CHIP_RA9701A1 == chipid)
                            {
                                /* close dig5 write-window */
                                MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x0U << 0);
                                MEM32(ANA_LURLS1) = 0xa5470000U | ((unsigned int)2U << 8) | ((unsigned int)0x0U << 0) | ((unsigned int)0x23U << 10);
                            }
                        }
                    }

                    if (0U != conf_reg[spl_conf->reg_id].reg_passwd)
                    {
                        temp = (MEM16(tt + spl_conf->reg_spl_idx * spl_len + spl_conf->reg_spl_addr) & spl_conf->reg_mask) | temp;
                        MEM32(reg_addr) = conf_reg[spl_conf->reg_id].reg_passwd | temp;
                    }
                    temp = (MEM16(tt + spl_conf->reg_spl_idx * spl_len + spl_conf->reg_spl_addr) & spl_conf->reg_mask) | temp;
                    MEM32(reg_addr) = temp;

                    if ((reg_addr & 0xffffff00U) == (conf_reg[REG_WDT_CTRL].reg_addr & 0xffffff00U))
                    {
                        for (cnt = 0U; cnt < 1000U; cnt++)
                        {
                            if (0U == (MEM32(WDT_EN) & ((unsigned int)1U << 8)))
                            {
                                break;
                            }
                        }
                    }

                    temp = MEM16(tt + spl_conf->reg_spl_idx * spl_len + spl_conf->reg_spl_addr) & spl_conf->reg_mask;
                    if (((unsigned short)MEM32(reg_addr) & spl_conf->reg_mask) != temp)
                    {
                        res = SYSCTRL_FAIL;
                    }
                }
            }
        }
    }

    if (SYSCTRL_FAIL == res)
    {
        (void)ldo_auto_adj();
    }
    else
    {
        res = ldo_auto_adj();
    }

    WDT_PS = 0x0U;
    if (1U == vbat_flag)
    {
        ANA_PS = anaps_bak;
    }
    RTC_PS = rtcps_bak;
    SYS_PS = 0x82U;
    MOD0_EN = mod0_bak;
    MOD1_EN = mod1_bak;
    SYS_PS = sysps_bak;

    return res;
}

// -*- r33873 -*-
