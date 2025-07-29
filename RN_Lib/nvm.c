/******************************************************************************
 * @file     nvm.c
 * @brief    non-valatile memory driver source code file for RN821x series SOC
 * @author   Renergy Technology
 * @version  V1.1
 * @date     2020-07-13
 * @note
 * Copyright (C) 2008, Renergy Technology Inc. All rights reserved.
 ******************************************************************************/
#include "rn8xxx_v2_lib.h"
#include "utils.h"

/* Register define */

/* IAP command define*/
#define FL_PAGE_ERASE 0x50U
#define FL_SECT_ERASE 0x51U
#define EE_PAGE_ERASE 0x54U
#define EE_SECT_ERASE 0x55U
#define FL_PROG 0x58U
#define EE_PROG 0x59U

#define FL_TYPE 0U
#define EE_TYPE 1U

#define FLASH_PAGE_SIZE  (512U)
/* IAP Call */
typedef void (*IAP_Entry)(unsigned long *cmd, unsigned long *stat);
#define IAP_OFFSET 0x1c01U

eNvmRet_TypeDef __eepromProgram(unsigned int dst_addr, unsigned int src_addr, unsigned int byte_num);
eNvmRet_TypeDef __eepromProgram_9103c(unsigned int dst_addr, unsigned int src_addr, unsigned int byte_num);

eNvmRet_TypeDef flashPageErase(unsigned int pg)
{
    struct sIAP
    {
        unsigned long cmd;
        unsigned long par[4];
        unsigned long stat;
        unsigned long res[2];
    } IAP;
    IAP_Entry iap_addr;
    eNvmRet_TypeDef res;

    iap_addr = (IAP_Entry)(getMipAddr(2U) + IAP_OFFSET);

    IAP.cmd = FL_PAGE_ERASE;
    IAP.par[0] = pg;

    (void)nvmWrEnable(FL_TYPE);
    iap_addr(&IAP.cmd, &IAP.stat);
    res = (eNvmRet_TypeDef)IAP.stat;

    return res;
}

eNvmRet_TypeDef flashSectorErase(unsigned int sec)
{
    struct sIAP
    {
        unsigned long cmd;
        unsigned long par[4];
        unsigned long stat;
        unsigned long res[2];
    } IAP;
    IAP_Entry iap_addr;

    iap_addr = (IAP_Entry)(getMipAddr(2U) + IAP_OFFSET);

    IAP.cmd = FL_SECT_ERASE;
    IAP.par[0] = sec;

    (void)nvmWrEnable(FL_TYPE);
    iap_addr(&IAP.cmd, &IAP.stat);
    return (eNvmRet_TypeDef)IAP.stat;
}

/*
eNvmRet_TypeDef eepromPageErase(unsigned int pg)
{
    struct sIAP
    {
        unsigned long cmd;
        unsigned long par[4];
        unsigned long stat;
        unsigned long res[2];
    } IAP;
    unsigned int iap_addr;
    rn_chipid_t chipid = getChipid();

    if ((chipid == CHIP_RA9103A) || (chipid == CHIP_RA9103D) || (chipid == CHIP_RA9103C) || (chipid == CHIP_RA9103E))
    {
        iap_addr = getMipAddr(2) + IAP_OFFSET;

        IAP.cmd = EE_PAGE_ERASE;
        IAP.par[0] = pg;

        nvmWrEnable(EE_TYPE);
        (*(void (*)())(iap_addr))(&IAP.cmd, &IAP.stat);
        return (eNvmRet_TypeDef)IAP.stat;
    }
    else
    {
        return SRC_ADDR_NOT_MAPPED;
    }
}

eNvmRet_TypeDef eepromSectorErase(unsigned int sec)
{
    struct sIAP
    {
        unsigned long cmd;
        unsigned long par[4];
        unsigned long stat;
        unsigned long res[2];
    } IAP;
    unsigned int iap_addr;
    rn_chipid_t chipid = getChipid();

    if ((chipid == CHIP_RA9103A) || (chipid == CHIP_RA9103D) || (chipid == CHIP_RA9103C) || (chipid == CHIP_RA9103E))
    {
        iap_addr = getMipAddr(2) + IAP_OFFSET;

        IAP.cmd = EE_SECT_ERASE;
        IAP.par[0] = sec;

        nvmWrEnable(EE_TYPE);
        (*(void (*)())(iap_addr))(&IAP.cmd, &IAP.stat);
        return (eNvmRet_TypeDef)IAP.stat;
    }
    else
    {
        return SRC_ADDR_NOT_MAPPED;
    }
}
*/
eNvmRet_TypeDef flashProgram(unsigned int dst_addr, unsigned int src_addr, unsigned int len)
{
    struct sIAP
    {
        unsigned long cmd;
        unsigned long par[4];
        unsigned long stat;
        unsigned long res[2];
    } IAP;
    IAP_Entry iap_addr;
    unsigned int temp;
    unsigned char pg_buf[FLASH_PAGE_SIZE];
    unsigned int i;
    eNvmRet_TypeDef res;

    if (len < FLASH_PAGE_SIZE)
    {
        for (i = 0U; i < len; i++)
        {
            pg_buf[i] = (*(unsigned char *)(src_addr + i));
        }
        for (i = i; i < FLASH_PAGE_SIZE; i++)
        {
            pg_buf[i] = 0xffU;
        }
        src_addr = (unsigned int)pg_buf;
        len = FLASH_PAGE_SIZE;
    }

    temp = getMipAddr(2U) + IAP_OFFSET;
    iap_addr = (IAP_Entry)temp;

    IAP.cmd = FL_PROG;
    IAP.par[0] = dst_addr;
    IAP.par[1] = src_addr;
    IAP.par[2] = len;

    (void)nvmWrEnable(FL_TYPE);
    iap_addr(&IAP.cmd, &IAP.stat);
    res = (eNvmRet_TypeDef)IAP.stat;

    return res;
}

eNvmRet_TypeDef eepromProgram(unsigned int dst_addr, unsigned int src_addr, unsigned int len)
{
    struct sIAP
    {
        unsigned long cmd;
        unsigned long par[4];
        unsigned long stat;
        unsigned long res[2];
    } IAP;
    IAP_Entry iap_addr;
    unsigned int temp;
    rn_chipid_t chip_id = getChipid();
    eNvmRet_TypeDef res;

    if (chip_id == CHIP_RA9103D)
    {
        (void)nvmWrEnable(EE_TYPE);
        res = __eepromProgram(dst_addr, src_addr, len);
    }
    else if ((chip_id == CHIP_RA9103C) || (chip_id == CHIP_RA9103E))
    {
        (void)nvmWrEnable(EE_TYPE);
        res = __eepromProgram_9103c(dst_addr, src_addr, len);
    }
    else if (chip_id == CHIP_RA9103A)
    {
        temp = getMipAddr(2U) + IAP_OFFSET;
        iap_addr = (IAP_Entry)temp;

        IAP.cmd = EE_PROG;
        IAP.par[0] = dst_addr;
        IAP.par[1] = src_addr;
        IAP.par[2] = len;

        (void)nvmWrEnable(EE_TYPE);
        iap_addr(&IAP.cmd, &IAP.stat);
        res = (eNvmRet_TypeDef)IAP.stat;
    }
    else
    {
        res = SRC_ADDR_NOT_MAPPED;
    }

    return res;
}

void eepromStandby(void)
{
    unsigned int reg = getMipAddr(1U);
    rn_chipid_t chip_id = getChipid();

    if ((chip_id == CHIP_RA9103C) || (chip_id == CHIP_RA9103E))
    {
        *(volatile unsigned int *)(reg + 0x00800000U) = 0xfeed000fU;
    }
    else if ((chip_id == CHIP_RA9103A) || (chip_id == CHIP_RA9103D))
    {
        *(volatile unsigned int *)(reg + 0x00800000U) = 0xfeed0007U;
    }
    else
    {
        /* eeprom is not supported */
    }
}

void eepromWakeup(void)
{
    unsigned int reg;
    rn_chipid_t chip_id = getChipid();

    /* if ((chip_id != CHIP_RA9103F) && (chip_id != CHIP_RA9103G)) */
    if ((chip_id == CHIP_RA9103A) || (chip_id == CHIP_RA9103D) || (chip_id == CHIP_RA9103C) || (chip_id == CHIP_RA9103E))
    {
        reg = getMipAddr(1U);
        *(volatile unsigned int *)(reg + 0x00800000U) = 0xfeed0004U;
    }
}

void cacheOff(void)
{
    unsigned int reg;
    rn_chipid_t chip_id = getChipid();

    if (chip_id == CHIP_RA9103F)
    {
        reg = 0x50014060U;
    }
    else if (chip_id == CHIP_RA9103G)
    {
        reg = 0x00800060U;
    }
    else if ((chip_id == CHIP_RA9701A) || (chip_id == CHIP_RA9701A1))
    {
        /* 9701 has no cache, write useless STA register to keep code compability */
        reg = 0x5001401cU;
    }
    else
    {
        reg = getMipAddr(0U) + 0x0080001cU;
    }

    *(volatile unsigned int *)(reg) = 0xfeed0000U;
}

void cacheOn(void)
{
    unsigned int reg;
    rn_chipid_t chip_id = getChipid();

    if (chip_id == CHIP_RA9103F)
    {
        reg = 0x50014060U;
    }
    else if (chip_id == CHIP_RA9103G)
    {
        reg = 0x00800060U;
    }
    else if ((chip_id == CHIP_RA9701A) || (chip_id == CHIP_RA9701A1))
    {
        /* 9701 has no cache, write useless STA register to keep code compability */
        reg = 0x5001401cU;
    }
    else
    {
        reg = getMipAddr(0U) + 0x0080001cU;
    }

    *(volatile unsigned int *)(reg) = 0xfeed0001U;
}

// -*- r33873 -*-
