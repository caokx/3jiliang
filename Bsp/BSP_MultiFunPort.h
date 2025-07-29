/****************************************************************************
* @file     BSP_MultiFunPort.c
* @author   Renergy Application Team
* @version  V1.0.1
* @date     2021.10.14
* @brief    板级层多功能端子
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BSP_MULTIFUNPORT_H_
#define _BSP_MULTIFUNPORT_H_

/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/
#define BSP_MultiFunPort_TimeScan()      {if(MultiFunPulseStamp !=0 )\
        {\
            MultiFunPulseStamp--;\
            if(MultiFunPulseStamp ==0 )\
            {GPIO_WRITE_PIN5_6(1);}\
        }\
    }

/* Exported enum ------------------------------------------------------------*/
typedef enum
{
    MF_SecondPulse = 0,   /*"秒脉冲输出"*/
    MF_DemandCycle = 1,   /*"需量周期"*/
    MF_TimeCut = 2,      /*"时段投切"*/
} eMultiFunPort_TypeDef; /*"端子功能"*/

typedef enum
{
    MF_SignalOFF = 0,   /*"多功能端子常态信号"*/
    MF_SignalON = 1,    /*"多功能端子触发信号"*/
} eMultiFunSignal_TypeDef; /*"端子信号"*/
/* Exported types ------------------------------------------------------------*/

/* Exported data  ----------------------------------------------------------*/
extern u16 MultiFunPulseStamp;
/* Exported functions ------------------------------------------------------- */
extern void BSP_MultiFunPort_Init(eMultiFunPort_TypeDef mfport);
extern void BSP_MultiFunPort_Output(u16 u16time);
#endif

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
