/******************************************************************************
 * @file     rn8xxx_v2_lib.h
 * @brief    rn8xxx v2 library code
 * @author   Renergy Technology
 * @version  V1.0
 * @date     2023-3-22
 *
 * @note
 * Copyright (C) , Renergy Technology Inc. All rights reserved.
 ******************************************************************************/
#ifndef RN8XXX_V2_LIB_H_
#define RN8XXX_V2_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************
  api return
**********************************************************/
typedef enum
{
    SYSCTRL_PASS = 0,
    SYSCTRL_FAIL = 1
} eSysCtrlRet_TypeDef;

typedef enum
{
    RTC_PASS = 0,
    RTC_FAIL = 1,
} eRtcRet_TypeDef;

typedef enum
{
    NVM_PASS = 0,
    COUNT_ERROR = 6,
    INVALID_PAGE = 8,
    SRC_ADDR_NOT_ALIGN = 10,
    SRC_ADDR_NOT_MAPPED = 11,
    DST_ADDR_NOT_ALIGN = 12,
    DST_ADDR_NOT_MAPPED = 13,
    VOL_INVALID = 20
} eNvmRet_TypeDef;

/**********************************************************
  system control
**********************************************************/
typedef enum
{
    Clock_Losc = 0x00,
    Clock_RC_1M8 = 0x01,
    Clock_PLL_7M4 = 0x02,
    Clock_Hosc = 0x03,
    Clock_PLL_14M7 = 0x05,
    Clock_RC_29M5 = 0x06,
    Clock_PLL_29M5 = 0x07,
    Clock_RCL_32K = 0x08,
    Clock_CHG_MAX = 0x09,
} eSysCtrlClockMode_TypeDef;

typedef enum
{
    Clock_Div_1 = 0x00U,
    Clock_Div_2 = 0x01U,
    Clock_Div_4 = 0x02U,
    Clock_Div_8 = 0x03U,
} eSysCtrlClockDiv_TypeDef;

/**
 * @brief system run mode change
 * @param mode: target system mode value:
 *   0 = LC, 8 = RCL
 *   1 = RC(1.8432M), 6 = RCH(29.4912M)
 *   2 = PLL(7.3728M), 5 = PLL(14.7456M), 7 = PLL(29.4912M)
 *   3 = HOSC(depends on OSC_CTRL2[2:0])
 *
 *   V1-A/B support mode=[0-3]
 *   V1-C/D support mode=[0-5]
 *   V2 supports mode=[0-8]
 * @param div: clock div
 * @return eSysCtrlRet_TypeDef: SYSCTRL_PASS = PASS, SYSCTRL_FAIL = FAIL
 */
eSysCtrlRet_TypeDef SysModeChg(eSysCtrlClockMode_TypeDef mode, eSysCtrlClockDiv_TypeDef div);

/**
 * @brief Remap4Sel
 *
 * @param
 *    in unsigned char sel: select remap4(sel = 0) or remap0(sel = 1)
 * @return eSysCtrlRet_TypeDef: SYSCTRL_PASS = PASS, SYSCTRL_FAIL = FAIL
 *
 */
eSysCtrlRet_TypeDef Remap4Sel(unsigned char sel);

/**
 * @brief system configuration parameters check
 *
 * @return eSysCtrlRet_TypeDef: SYSCTRL_PASS = PASS, SYSCTRL_FAIL = FAIL
 */
eSysCtrlRet_TypeDef SysConfCheck(void);

/**
 * @brief Get the Lib Version object
 *
 * @return unsigned int: lib version 0x00XXYYZZ
 */
unsigned int GetLibVersion(void);

/**
 * @brief Get the Code Version object
 *
 * @return unsigned int: code version
 */
unsigned int GetCodeVersion(void);

/**********************************************************
  rtc
**********************************************************/
/**
 * @brief RtcReadDota
 *
 * @param
 *    none
 * @return
 *    unsigned short dota: dota value of RTC
 *
 */
unsigned short  RtcReadDota(void);

/**
 * @brief RtcWriteDota
 *
 * @param
 *    in unsigned short dota: dota value of RTC
 * @return
 *    NVM_PASS: rtc-dota write pass
 *    NVM_FAIL: rtc-dota write fail
 *
 */
eRtcRet_TypeDef RtcWriteDota(unsigned short dota);

/**********************************************************
  nvm
**********************************************************/
eNvmRet_TypeDef flashPageErase(unsigned int pg);
eNvmRet_TypeDef flashSectorErase(unsigned int sec);

eNvmRet_TypeDef flashProgram(unsigned int dst_addr, unsigned int src_addr, unsigned int len);
eNvmRet_TypeDef eepromProgram(unsigned int dst_addr, unsigned int src_addr, unsigned int len);

void    eepromStandby(void);
void    eepromWakeup(void);

void    cacheOn(void);
void    cacheOff(void);

#ifdef __cplusplusw
}
#endif

#endif

// -*- r33840 -*-
