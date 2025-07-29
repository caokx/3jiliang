/******************************************************************************
 * @file    eepromProgam.c
 * @brief    eeprom program source code file for RN821x series SOC
 * @author   Renergy Technology
 * @version  V1.1
 * @date     2020-07-13
 *
 * @note
 * Copyright (C) 2017, Renergy Technology Inc. All rights reserved.
 ******************************************************************************/
#include "rn8xxx_v2_lib.h"

/* Register define */
#define OSC_CTRL1  (*(volatile unsigned int *)(0x40034000U))
#define MAP_CTL    (*(volatile unsigned int *)(0x40034018U))
#define MOD0_EN    (*(volatile unsigned int *)(0x4003401cU))
#define MOD1_EN    (*(volatile unsigned int *)(0x40034020U))
#define SYS_PS     (*(volatile unsigned int *)(0x40034030U))
#define DIE_VER    (*(volatile unsigned int *)(0x40034074U))
#define SYSTC_CTRL (*(volatile unsigned int *)(0x50010000U))
#define SYSTC_LOAD (*(volatile unsigned int *)(0x50010004U))
#define SYSTC_VAL  (*(volatile unsigned int *)(0x50010008U))
#define WDT_EN     (*(volatile unsigned int *)(0x40030000U))
#define FEED_WDT   (WDT_EN = 0xbbU)

#define EEPROM_BASE_REMAP0 (0x08000000U) /*!< (EEPROM    ) Base Address */
#define EEPROM_BASE_REMAP1 (0x00000000U) /*!< (EEPROM    ) Base Address */
#define EEPROM_BASE_REMAP2 (0x08000000U) /*!< (EEPROM    ) Base Address */
#define EEPROM_BASE_REMAP3 (0x08000000U) /*!< (EEPROM    ) Base Address */

#define EEPROM_TP (1U)
#define EEPROM_TE (2U)
#define EEPROM_TMS_CHIP (932U)
#define EEPROM_TMS_PAGE (832U)
#define EEPROM_TMS_CHIP_32K (30U)
#define EEPROM_TMS_PAGE_32K (26U)

#define TW_7M (0x2U << 16)
#define TW_3M (0x0U << 16)
#define TW_1M (0x0U << 16)
#define TW_32K (0x0U << 16)
#define TW_14M (0x2U << 16)
#define TW_29M (0x5U << 16)

/* ----2020-07-13 9103C_EEPROMPROGRAM----- */
#define EEPROM_PAGE_SIZE_C0 (128U)
#define EEPROM_SECTOR_NUM_C0 (4U) /* 64 PAGE  (RTL SIZE : 4KB,FPGA SIZE :8KB) */
#define EEPROM_PAGE_NUM_C0 (64U * EEPROM_SECTOR_NUM)
#define EEPROM_SECTOR_SIZE_C0 (EEPROM_PAGE_SIZE * 64U)
#define EEPROM_SIZE_C0 (EEPROM_SECTOR_SIZE * EEPROM_SECTOR_NUM)

#define ECMD_SE_C0 (6U)
#define ECMD_PE_C0 (10U)
#define ECMD_PP_C0 (14U)
/* ----2020-07-13 9103C_EEPROMPROGRAM----- */

#define EEPROM_PAGE_SIZE (64U)
#define EEPROM_SECTOR_NUM (8U)
#define EEPROM_SECTOR_SIZE (EEPROM_PAGE_SIZE * 64U)
#define EEPROM_SIZE (EEPROM_SECTOR_SIZE * EEPROM_SECTOR_NUM)
#define EEPROM_SP0_BASE (0x08c08000U)
#define EEPROM_SP0_OFFSET (0x00c08000U)
#define EEPROM_CMD_OFFSET (0x00800000U)  /*EEPROM Command Register Offset Address */
#define EEPROM_PGA_OFFSET (0x00800004U)  /*EEPROM Page Address Register Offset Address */
#define EEPROM_STA_OFFSET (0x00800008U)  /*EEPROM Status Register Offset Address */
#define EEPROM_PROT_OFFSET (0x00800014U) /*EEPROM Port Register Offset Address */
#define EEPROM_TW_OFFSET (0x00800018U)   /*EEPROM Wait time Register Offset Address */
#define EEPROM_TUS_OFFSET (0x00800020U)  /*EEPROM us time Register Offset Address */
#define EEPROM_TMS_OFFSET (0x00800024U)  /*EEPROM ms time Register Offset Address */
#define EEPROM_TP_OFFSET (0x00800028U)   /*EEPROM Program time Register Offset Address */
#define EEPROM_TE_OFFSET (0x0080002cU)   /*EEPROM Erase time Register Offset Address */

#define ECMD_IDLE (0U)
#define ECMD_TBC (2U)
#define ECMD_POR (3U)
#define ECMD_HVPL (4U)
#define ECMD_LPS1 (6U)
#define ECMD_LPS2 (7U)
#define ECMD_CE (9U)
#define ECMD_SE (10U)
#define ECMD_PE (11U)
#define ECMD_CP (12U)
#define ECMD_PP (15U)

#define TRIM_PAGE (0x0U)
#define TRIM_ERASE (0x0U)
#define TRIM_PROG (0x100U)
#define EEPROM_BUSY_CYCLE (((unsigned int)20U << 8) | 10U) /* 4.4ms..305us*20 = 6ms.  4.4 ms (64 cycles) The maximum counter for EEPROM is */
#define EEPROM_TBC_CYCLE (((unsigned int)50U << 8) | 0U)   /* 0.4 ms (8us per cycle) */

static unsigned int __updateAddr(void);
static unsigned int __acqCorefre(void);
static void __swDelay(unsigned int time);
static void __trimFill(unsigned int dst_addr, unsigned int mode);
static void __checkFlag(unsigned int reg_addr, unsigned short wait_val, unsigned int loop_time);
eNvmRet_TypeDef __eepromProgram(unsigned int dst_addr, unsigned int src_addr, unsigned int byte_num);
eNvmRet_TypeDef __eepromProgram_9103c(unsigned int dst_addr, unsigned int src_addr, unsigned int byte_num);

static unsigned int __updateAddr(void)
{
    unsigned int addr;
    unsigned int map_ctrl;

    map_ctrl = MAP_CTL & 0x3U;

    switch (map_ctrl)
    {
        case 0x0U:
            addr = EEPROM_BASE_REMAP0;
            break;
        case 0x1U:
            addr = EEPROM_BASE_REMAP1;
            break;
        case 0x2U:
            addr = EEPROM_BASE_REMAP2;
            break;
        case 0x3U:
            addr = EEPROM_BASE_REMAP3;
            break;
        default:
            addr = EEPROM_BASE_REMAP0;
            break;
    }

    return addr;
}

#ifndef USE_BOOTLOADER
static unsigned int __acqCorefre(void)
{
    unsigned int result;
    unsigned char sysclk_state;

    sysclk_state = (unsigned char)((OSC_CTRL1 & 0x700U) >> 8U);

    switch (sysclk_state)
    {
        case 0x0U:
            result = 7372800U;
            break;
        case 0x1U:
            result = 3686400U;
            break;
        case 0x2U:
            result = 1843200U;
            break;
        case 0x3U:
            result = 32768U;
            break;
        case 0x4U:
            result = 14745600U;
            break;
        case 0x5U:
            result = 29491200U;
            break;
        default:
            result = 1843200U;
            break;
    }
    return result;
}

static void __swDelay(unsigned int time)
{
    unsigned int i;
    unsigned int cur_freq;

    cur_freq = __acqCorefre();

    /*if (time != 0U)*/
    {
        SYS_PS = 0x82U;
        MOD0_EN |= ((unsigned int)1U << 0);
        SYSTC_LOAD = 0xffffffffU;
        SYSTC_CTRL = 1U;

        for (i = 0U; i < (time * (cur_freq / 32768U)); i++)
        {
            if (SYSTC_VAL >= time * (cur_freq / 32768U))
            {
                break;
            }
        }

        SYSTC_CTRL = 0x0U;
    }
    return;
}

#if 0
/*********************************************************************************************************
** Function name:       sumCheck
** Descriptions:        32bit SUM Check. Formula : +
** input parameters:    p_data
**　　　　　　　　　　　length　　　
** output parameters:   sum
** Returned value:      None
*********************************************************************************************************/
static unsigned int __sumCheck(unsigned int *p_data, unsigned int length)
{
    unsigned int sum;
    unsigned int i;

    sum = 0x0;

    for (i = 0; i < length; i++)
    {
        sum = sum + *(p_data + i);
    }

    return sum;
}

/*********************************************************************************************************
** Function name:       spValid
** Descriptions:        EEPROM Special Line Check.
** input parameters:    None
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
static unsigned char __spValid(unsigned int *p_addr, unsigned int flag)
{
    unsigned int checksum;
    unsigned char sp_valid = 0x0;

    checksum = __sumCheck(p_addr, (flag == 0x1) ? ((EEPROM_PAGE_SIZE >> 2) - 1) : (EEPROM_PAGE_SIZE >> 2));
    if ((*(p_addr + ((EEPROM_PAGE_SIZE >> 2) - 3)) == 0xffffffff) && (checksum == 0))
    {
        sp_valid = 0x1;
    }

    return sp_valid;
}
#endif

/*********************************************************************************************************
** Function name:       trimFill
** Descriptions:        Fill trim parameter to FLASH/EEPROM
** input parameters:    None　　
** output parameters:   result
** Returned value:      None
*********************************************************************************************************/
static void __trimFill(unsigned int dst_addr, unsigned int mode)
{
    unsigned int sysclk_state;
    unsigned char TW_TABLE[] = {0x2U, 0x0U, 0x0U, 0x0U, 0x2U, 0x5U}; /* 7.3728, 3.6864, 1.8432, 32.768K, 14.7456M, 29.4912M */
    unsigned char TUS_TABLE[] = {7U, 3U, 1U, 1U, 15U, 31U};

    sysclk_state = ((OSC_CTRL1 & 0x700U) >> 8);
    sysclk_state = (sysclk_state > 0x5U) ? 0x2U : sysclk_state;

    *(volatile unsigned int *)(dst_addr + EEPROM_TW_OFFSET) = (unsigned int)TW_TABLE[sysclk_state] << 16;
    *(volatile unsigned int *)(dst_addr + EEPROM_TUS_OFFSET) = (unsigned int)TUS_TABLE[sysclk_state];

    if (sysclk_state != 0x3U)
    {
        /*if (((mode >> 4) & 0x1U) == 0x1U)
        {
            *(volatile unsigned int *)(dst_addr + EEPROM_TMS_OFFSET) = EEPROM_TMS_CHIP;
        }
        else*/
        {
            *(volatile unsigned int *)(dst_addr + EEPROM_TMS_OFFSET) = EEPROM_TMS_PAGE;
        }
    }
    else
    {
        /*if (((mode >> 4) & 0x1U) == 0x1U)
        {
            *(volatile unsigned int *)(dst_addr + EEPROM_TMS_OFFSET) = EEPROM_TMS_CHIP_32K;
        }
        else*/
        {
            *(volatile unsigned int *)(dst_addr + EEPROM_TMS_OFFSET) = EEPROM_TMS_PAGE_32K;
        }
    }

    *(volatile unsigned int *)(dst_addr + EEPROM_TP_OFFSET) = EEPROM_TP;
    *(volatile unsigned int *)(dst_addr + EEPROM_TE_OFFSET) = EEPROM_TE;
}

static void __checkFlag(unsigned int reg_addr, unsigned short wait_val, unsigned int loop_time)
{
    unsigned short i;
    unsigned short temp;

    for (i = 0U; i < ((loop_time & 0xffff00U) >> 8); i++)
    {
        temp = (unsigned short)(*(volatile unsigned int *)(reg_addr)) & wait_val;
        if ((/*((loop_time & 0x80000000U) != 0x80000000U) && */(temp != wait_val))/* ||
            (((loop_time & 0x80000000U) == 0x80000000U) && (temp == wait_val))*/)
        {
            break;
        }

        __swDelay(loop_time & 0xffU);
    }

    return;
}
#endif

eNvmRet_TypeDef __eepromProgram(unsigned int dst_addr, unsigned int src_addr, unsigned int byte_num)
{
    eNvmRet_TypeDef result;
    unsigned char write_size;
    unsigned char page_res;
    unsigned int temp;
    unsigned int start_addr;
    unsigned int page_num;
    unsigned int page_start;
    unsigned int i;
    unsigned int j;
    unsigned int eeprom_base_addr;

    eeprom_base_addr = __updateAddr();

    if ((byte_num == 0U) || (byte_num > EEPROM_SIZE))
    {
        result = COUNT_ERROR;
    }
    else if ((dst_addr < eeprom_base_addr) ||
             ((dst_addr >= (eeprom_base_addr + EEPROM_SIZE)) && (dst_addr < (eeprom_base_addr + EEPROM_SP0_OFFSET))) ||
             ((dst_addr + byte_num > (eeprom_base_addr + EEPROM_SIZE)) && (dst_addr + byte_num < (eeprom_base_addr + EEPROM_SP0_OFFSET))) ||
             (dst_addr >= (eeprom_base_addr + EEPROM_SP0_BASE - EEPROM_BASE_REMAP3 + 2U * EEPROM_PAGE_SIZE)) ||
             (dst_addr + byte_num > (eeprom_base_addr + EEPROM_SP0_BASE - EEPROM_BASE_REMAP3 + 2U * EEPROM_PAGE_SIZE)))
    {
        result = DST_ADDR_NOT_MAPPED;
    }
    else
    {
        __trimFill(eeprom_base_addr, 0U);

        /* Progam EEPROOM */
        start_addr = dst_addr & (EEPROM_PAGE_SIZE - 1U);
        temp = (byte_num < (EEPROM_PAGE_SIZE - start_addr)) ? 0U : (byte_num - (EEPROM_PAGE_SIZE - start_addr));
        temp = (start_addr != 0x0U) ? temp : byte_num;
        page_num = temp / EEPROM_PAGE_SIZE;
        page_num = (start_addr != 0x0U) ? (page_num + 1U) : page_num;
        page_res = (unsigned char)(temp % EEPROM_PAGE_SIZE);
        page_num = (page_res != 0x0U) ? (page_num + 1U) : page_num;
        page_start = (dst_addr & 0xffffU) / EEPROM_PAGE_SIZE;

        /* Open Protect Bit */
        *(unsigned int *)(eeprom_base_addr + EEPROM_PROT_OFFSET) = 0xfeed0000U;

        temp = 0U;

        for (i = 0U; i < page_num; i++)
        {
            SYS_PS = 0x82U;
            MOD1_EN |= ((unsigned int)1U << 9);
            FEED_WDT;

            *(volatile unsigned int *)(eeprom_base_addr + EEPROM_CMD_OFFSET) = 0xfeed0000U + ((unsigned int)ECMD_HVPL << 0);

            if ((page_res != 0x0U) && (i == (page_num - 0x1U)))
            {
                write_size = page_res;
            }
            else
            {
                if ((start_addr != 0U) && (i == 0U))
                {
                    write_size = (page_num == 1U) ? (unsigned char)byte_num : (unsigned char)(EEPROM_PAGE_SIZE - start_addr);
                }
                else
                {
                    write_size = EEPROM_PAGE_SIZE;
                }
            }

            for (j = 0U; j < write_size; j++)
            {
                if (i == 0U)
                {
                    *(volatile unsigned char *)(eeprom_base_addr + start_addr + j) = *(unsigned char *)(src_addr + temp);
                }
                else
                {
                    *(volatile unsigned char *)(eeprom_base_addr + j) = *(unsigned char *)(src_addr + temp);
                }
                temp = temp + 1U;
            }

            *(volatile unsigned int *)(eeprom_base_addr + EEPROM_PGA_OFFSET) = page_start + i;
            __trimFill(eeprom_base_addr, 0U);

            *(volatile unsigned int *)(eeprom_base_addr + EEPROM_CMD_OFFSET) = 0xfeed0000U + ((unsigned int)ECMD_PE << 0);
            __checkFlag(eeprom_base_addr + EEPROM_STA_OFFSET, 0x1U, EEPROM_BUSY_CYCLE);
            __trimFill(eeprom_base_addr, 0U);

            *(volatile unsigned int *)(eeprom_base_addr + EEPROM_CMD_OFFSET) = 0xfeed0000U + ((unsigned int)ECMD_PP << 0);

            __checkFlag(eeprom_base_addr + EEPROM_STA_OFFSET, 0x1U, EEPROM_BUSY_CYCLE);
        }

        *(volatile unsigned int *)(eeprom_base_addr + EEPROM_PROT_OFFSET) = 0xfeedffffU;

        result = NVM_PASS;
    }

    return result;
}

eNvmRet_TypeDef __eepromProgram_9103c(unsigned int dst_addr, unsigned int src_addr, unsigned int byte_num)
{
    eNvmRet_TypeDef result;
    unsigned int write_size, write_word_size;
    unsigned int page_num;
    unsigned int i;
    unsigned int page;
    unsigned int eeprom_base_addr;
    unsigned int buf[EEPROM_PAGE_SIZE_C0 / 4U];
    unsigned int head_addr, tail_addr;
    unsigned int head_bytes;
    unsigned int src_cnt = 0U;
    unsigned char *pb;

    eeprom_base_addr = __updateAddr();

    if ((byte_num == 0U) || (byte_num > EEPROM_SIZE_C0))
    {
        result = COUNT_ERROR;
    }
    else if ((dst_addr < eeprom_base_addr) ||
             ((dst_addr >= (eeprom_base_addr + EEPROM_SIZE_C0)) && (dst_addr < (eeprom_base_addr + EEPROM_SP0_OFFSET))) ||
             ((dst_addr + byte_num > (eeprom_base_addr + EEPROM_SIZE_C0)) && (dst_addr + byte_num < (eeprom_base_addr + EEPROM_SP0_OFFSET))) ||
             (dst_addr >= (eeprom_base_addr + EEPROM_SP0_BASE - EEPROM_BASE_REMAP3 + 2U * EEPROM_PAGE_SIZE_C0)) ||
             (dst_addr + byte_num > (eeprom_base_addr + EEPROM_SP0_BASE - EEPROM_BASE_REMAP3 + 2U * EEPROM_PAGE_SIZE_C0)))
    {
        result = DST_ADDR_NOT_MAPPED;
    }
    else
    {
        __trimFill(eeprom_base_addr, 0U);

        head_addr = dst_addr & (EEPROM_PAGE_SIZE_C0 - 1U);
        tail_addr = (dst_addr + byte_num - 1U) & (EEPROM_PAGE_SIZE_C0 - 1U);
        page_num = (((dst_addr + byte_num - 1U) & (~((unsigned int)EEPROM_PAGE_SIZE_C0 - 1U))) - (dst_addr & (~((unsigned int)EEPROM_PAGE_SIZE_C0 - 1U)))) / EEPROM_PAGE_SIZE_C0 + 1U;
        if (page_num == 1U)
        {
            head_bytes = byte_num;
        }
        else
        {
            head_bytes = EEPROM_PAGE_SIZE_C0 - head_addr;
        }
        for (page = 0U; page < page_num; page++)
        {
            FEED_WDT;

            *(volatile unsigned int *)(eeprom_base_addr + EEPROM_CMD_OFFSET) = 0xfeed0000U + ((unsigned int)ECMD_HVPL << 0);

            if (page == 0U)
            {
                write_size = head_bytes;
                /* read back by word */
                buf[head_addr / 4U] = *(unsigned int *)(dst_addr & 0xfffffffcU);
                if (page_num == 1U)
                {
                    buf[tail_addr / 4U] = *(unsigned int *)((dst_addr + byte_num - 1U) & 0xfffffffcU);
                    write_word_size = ((tail_addr & (~(unsigned int)0x3U)) - (head_addr & (~(unsigned int)0x3U))) / 4U + 1U;
                }
                else
                {
                    write_word_size = (((EEPROM_PAGE_SIZE_C0 - 1U) & (~(unsigned int)0x3U)) - (head_addr & (~(unsigned int)0x3U))) / 4U + 1U;
                }
            }
            else if (page == (page_num - 1U))
            {
                buf[tail_addr / 4U] = *(unsigned int *)((dst_addr + byte_num - 1U) & 0xfffffffcU);
                write_size = tail_addr + 1U;
                write_word_size = ((tail_addr & (~(unsigned int)0x3U))) / 4U + 1U;
            }
            else
            {
                write_size = EEPROM_PAGE_SIZE_C0;
                write_word_size = write_size / 4U;
            }

            for (i = 0U; i < write_size; i++)
            {
                if (page == 0U)
                {
                    pb = (unsigned char *)((unsigned int)(buf) + head_addr + i);
                }
                else
                {
                    pb = (unsigned char *)((unsigned int)(buf) + i);
                }
                *pb = (*(unsigned char *)(src_addr + src_cnt + i));
            }
            src_cnt += write_size;
            for (i = 0U; i < (write_word_size); i++)
            {
                if (page == 0U)
                {
                    *(volatile unsigned int *)(eeprom_base_addr + (head_addr & (~(unsigned int)3U)) + 4U * i) = *(unsigned int *)((unsigned int)buf + (head_addr & (~(unsigned int)3U)) + 4U * i);
                }
                else
                {
                    *(volatile unsigned int *)(eeprom_base_addr + 4U * i) = buf[i & (EEPROM_PAGE_SIZE_C0 / 4U - 1U)];
                }
            }

            *(volatile unsigned int *)(eeprom_base_addr + EEPROM_PGA_OFFSET) = (dst_addr / EEPROM_PAGE_SIZE_C0) + page;
            __trimFill(eeprom_base_addr, 0x0U);

            *(volatile unsigned int *)(eeprom_base_addr + EEPROM_CMD_OFFSET) = 0xfeed0000U + ((unsigned int)ECMD_PE_C0 << 0U);
            __checkFlag(eeprom_base_addr + EEPROM_STA_OFFSET, 0x1U, EEPROM_BUSY_CYCLE);

            __trimFill(eeprom_base_addr, 0x0U);

            *(volatile unsigned int *)(eeprom_base_addr + EEPROM_CMD_OFFSET) = 0xfeed0000U + ((unsigned int)ECMD_PP_C0 << 0U);
            __checkFlag(eeprom_base_addr + EEPROM_STA_OFFSET, 0x1U, EEPROM_BUSY_CYCLE);
        }

        *(volatile unsigned int *)(eeprom_base_addr + EEPROM_PROT_OFFSET) = 0xfeedffffU;

        result = NVM_PASS;
    }

    return result;
}

// -*- r33840 -*-
