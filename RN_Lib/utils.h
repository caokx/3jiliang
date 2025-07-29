/**
 * @file utils.h
 * @author Renergy Technology Inc.
 * @brief common functions used by lib code
 * @version 1.0.0
 * @date 2023-02-03
 *
 * @copyright Copyright (C) 2008, Renergy Technology Inc. All rights reserved.
 *
 */
#ifndef UTILS_H
#define UTILS_H

/* DON'T CHANGED existed chipid value for compatibility */
typedef enum
{
    CHIP_RA9103A = 0U,
    CHIP_RA9103D = 1U,
    CHIP_RA9103C = 2U,
    CHIP_RA9103E = 3U,
    CHIP_RA9103F = 4U,
    CHIP_RA9103G = 5U,
    CHIP_RA9701A = 6U,
    CHIP_RA9701A1 = 7U
} rn_chipid_t;

typedef enum
{
    RET_INDEX = 0,
    RET_FREQ = 1
} rn_sys_freq_t;
/**
 * @brief Get the Chipid number
 *
 * @return rn_chipid_t: chipid number
 */
rn_chipid_t getChipid(void);

/**
 * @brief Get the Mip Addr object
 *
 * @param mem_type: 0 = FLASH, 1 = EEPROM, 2 = ROM
 * @return unsigned int: memory base address
 */
unsigned int getMipAddr(unsigned char mem_type);

/**
 * @brief get current run clock
 *
 * @return unsigned int: clock frequency
 */
unsigned int currentClk(void);

/**
 * @brief get current run clock index
 *
 * @return unsigned int: clock index
 */
unsigned int currentClk_idx(void);

/**
 * @brief compare register with val in timeout
 * @param addr register address
 * @param val compared data
 * @param sign compared mode:
 *   sign = 1, exit while val != ([addr] & val)
 *   sign = 0, exit while val == ([addr] & val)
 * @param timeout compared timeout(us unit)
 * @param chipid chip id
 */
void usTimeout(unsigned int addr, unsigned int val, unsigned int sign, unsigned int timeout, rn_chipid_t chipid);

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
unsigned char check_spl_valid(unsigned int *p_addr, unsigned int len, unsigned char flag);

/**
 * @brief Enable IAP NVM operation
 *
 * @param nvm_type: 0 = FLASH, 1 = EEPROM
 * @return unsigned char: ref IAP interface in datasheet
 */
unsigned char nvmWrEnable(unsigned char nvm_type);

/**
 * @brief rtc wrong state check
 *   1. check if some of VBAT power domain registers are unexcepted
 *   2. check if rtc calc busy is always on(if yes, VBAT power domain is in wrong state)
 * @return unsigned char: 0 = OK, 1 = FAIL
 */
unsigned char RtcCalCheck(rn_chipid_t chipid);

/**
 * @brief soft reset vbat power domain
 *
 */
void vbat_reset(void);
#endif

// -*- r33840 -*-
