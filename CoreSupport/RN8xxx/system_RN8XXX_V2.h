/**************************************************************************
 * @file     system_RN8XXX_V2.h
 * @brief    CMSIS Cortex-M0 Device System Header File
 *           for RN8XXX_V2 Device
 * @version  V1.0.0
 * @date     2023.2.2
 *
 * @note
 * Copyright (C) REnergy Micro-Electronics Co.,LTD.
 *
 *
 ******************************************************************************/

#ifndef __SYSTEM_RN8XXX_V2_H
#define __SYSTEM_RN8XXX_V2_H

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit(void);

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_RN8XXX_V2_H */

// -*- r32775 -*-
