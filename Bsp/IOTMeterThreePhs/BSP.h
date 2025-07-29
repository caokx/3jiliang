/****************************************************************************
* @file     BSP.h
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.08.12
* @brief    板级层头文件
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  _BSP_H
#define  _BSP_H

//-----------科陆特殊要求-------------------
#define     KeLu       FALSE   //  TRUE/  FALSE， 科陆硬件为5V系统，其他为3.3V系统

//------硬件版本-----------------------
#define     RN8613V2_RN8209DV4          1
#define     RN8611_RN8209D                  2

#define  PCB_Version         RN8611_RN7306//RN8611_RN8209D    //硬件PCB版本

//----------------------------------
#define  RN8xxx_V1           0
#define  RN8xxx_V2      1

#define  RN8xxx_Ver   RN8xxx_V2   //MCU芯片版本

#define HarmonicFun_Disable     0   //谐波功能关闭
#define HarmonicFun_Enable     1   //谐波功能开启
#define HarmonicFun_EnORDis         HarmonicFun_Enable

#define HarmonicPulseOut_Auto       0//D2F自动输出
#define HarmonicPulseOut_Interrupt  1//D2F转中断输出

#if(KeLu == TRUE)
#define HarmonicPulseOut_Mode       HarmonicPulseOut_Auto//谐波脉冲输出方式选择
#else
#define HarmonicPulseOut_Mode       HarmonicPulseOut_Interrupt//谐波脉冲输出方式选择
#endif

#define SinglePhs               1
#define ThreePhs                3
#define nPhs                    ThreePhs      //3： 三相表

//------------------------------------------
#define     DL645SOFT_DEBUG     0
#define     HOSC_PLL 0 // 0=PLL 1=HOSC
#define SPI_ESAM            1//
#define     METERTYPE           1       //  本地费控表设置为2，智能电能表设置为0 ，远程设置为1
#define ZBComFlag           0       // 0 无载波通讯模块  1 有载波通讯模块
#define GataFlag            0       // 0 内置继电器  1 外置继电器

#define     KEY_Enable       TRUE   //    FALSE  无按键功能   , TRUE  有按键(包括开盖及磁场检测)
#define LCD_DISP        FALSE   //    FALSE     , TRUE
//-----------------------------------
#define  VOLREP_Enable     0x55
#define  VOLREP_Disable     0x00

#define  VOL_REPAIR         VOLREP_Enable  //电压影响量补偿
#define  MAX_VOLT_STEP      8  //电压影响量补偿点，预留10个点

//--------上下电判断选择-----------------------
#define     CHECKLVD        0  //判断Lvd 标志确定上电或掉电
#define     CHECKCMP1           1  //判断cmp1 标志确定上电或掉电
#define CHECKCMP2           2  //判断cmp2 标志确定上电或掉电
#define CHECKLVD_CMP1       3  //判断LVD&cmp1 标志确定上电或掉电
#define CHECKLVD_CMP2       4  //判断LVD&cmp2 标志确定上电或掉电

#define  POWERCHACK   CHECKLVD_CMP2
/* Includes ------------------------------------------------------------------*/
//#include <CoreSupport.h>

#include <Rn8xxx_Devices.h>

#include <Types.h>

#include <MyMath.h>

#include <xTarget.h>
#include <Key.h>

#include <Drive_Clock.h>
#include <BSP_IIC.h>
#include <BSP_Spi.h>
#include <BSP_Tmp.h>

#include <RN8302.h>
#include <Misc.h>

#include <BSP_Uart.h>
#include <BSP_MultiFunPort.h>
#include <BSP_Relay.h>
#include <BSP_LvdCmpSar.h>
#include <BSP_Scom.h>
#include <Fm24Cxx.h>
#include <AT45DB642D.h>
#include <BSP_Esam.h>
#include <Drive_ALLINT.h>

#include <FIFO.h>
/* Exported define ------------------------------------------------------------*/

/* Exported enum ------------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/
extern u16                  SysStamp;               //在Dl645_Globals.h中定义。

/* Exported functions ------------------------------------------------------- */

//---------------------------------------------------
#endif  //_BSP_H
//---------------------------------------------------

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
