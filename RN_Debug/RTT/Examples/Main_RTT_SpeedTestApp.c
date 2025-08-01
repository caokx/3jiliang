/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*       (c) 2014 - 2016  SEGGER Microcontroller GmbH & Co. KG        *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER RTT * Real Time Transfer for embedded targets         *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* SEGGER strongly recommends to not make any changes                 *
* to or modify the source code of this software in order to stay     *
* compatible with the RTT protocol and J-Link.                       *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* conditions are met:                                                *
*                                                                    *
* o Redistributions of source code must retain the above copyright   *
*   notice, this list of conditions and the following disclaimer.    *
*                                                                    *
* o Redistributions in binary form must reproduce the above          *
*   copyright notice, this list of conditions and the following      *
*   disclaimer in the documentation and/or other materials provided  *
*   with the distribution.                                           *
*                                                                    *
* o Neither the name of SEGGER Microcontroller GmbH & Co. KG         *
*   nor the names of its contributors may be used to endorse or      *
*   promote products derived from this software without specific     *
*   prior written permission.                                        *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************
*                                                                    *
*       RTT version: 6.12a                                           *
*                                                                    *
**********************************************************************
--------- END-OF-HEADER --------------------------------------------
File    : Main_RTT_SpeedTestApp.c
Purpose : Sample program for measuring RTT performance.
*/

#include "RTOS.h"
#include "BSP.h"

#include "SEGGER_RTT.h"
#include <stdio.h>

OS_STACKPTR int StackHP[128], StackLP[128];          /* Task stacks */
OS_TASK TCBHP, TCBLP;                        /* Task-control-blocks */

static void HPTask(void)
{
    while (1)
    {
        //
        // Measure time needed for RTT output
        // Perform dummy write with 0 characters, so we know the overhead of toggling LEDs and RTT in general
        //
        // Set BP here. Then start sampling on scope
        BSP_ClrLED(0);
        SEGGER_RTT_Write(0, 0, 0);
        BSP_SetLED(0);
        BSP_ClrLED(0);
        SEGGER_RTT_Write(0, "01234567890123456789012345678901234567890123456789012345678901234567890123456789\r\n", 82);
        BSP_SetLED(0);
        // Set BP here. Then stop sampling on scope
        OS_Delay(200);
    }
}

static void LPTask(void)
{
    while (1)
    {
        BSP_ToggleLED(1);
        OS_Delay(500);
    }
}

/*********************************************************************
*
*       main
*
*********************************************************************/

int main(void)
{
    OS_IncDI();                      /* Initially disable interrupts  */
    OS_InitKern();                   /* Initialize OS                 */
    OS_InitHW();                     /* Initialize Hardware for OS    */
    BSP_Init();                      /* Initialize LED ports          */
    BSP_SetLED(0);
    /* You need to create at least one task before calling OS_Start() */
    OS_CREATETASK(&TCBHP, "HP Task", HPTask, 100, StackHP);
    OS_CREATETASK(&TCBLP, "LP Task", LPTask,  50, StackLP);
    OS_Start();                      /* Start multitasking            */
    return 0;
}
