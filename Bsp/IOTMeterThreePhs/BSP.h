/****************************************************************************
* @file     BSP.h
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.08.12
* @brief    �弶��ͷ�ļ�
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  _BSP_H
#define  _BSP_H

//-----------��½����Ҫ��-------------------
#define     KeLu       FALSE   //  TRUE/  FALSE�� ��½Ӳ��Ϊ5Vϵͳ������Ϊ3.3Vϵͳ

//------Ӳ���汾-----------------------
#define     RN8613V2_RN8209DV4          1
#define     RN8611_RN8209D                  2

#define  PCB_Version         RN8611_RN7306//RN8611_RN8209D    //Ӳ��PCB�汾

//----------------------------------
#define  RN8xxx_V1           0
#define  RN8xxx_V2      1

#define  RN8xxx_Ver   RN8xxx_V2   //MCUоƬ�汾

#define HarmonicFun_Disable     0   //г�����ܹر�
#define HarmonicFun_Enable     1   //г�����ܿ���
#define HarmonicFun_EnORDis         HarmonicFun_Enable

#define HarmonicPulseOut_Auto       0//D2F�Զ����
#define HarmonicPulseOut_Interrupt  1//D2Fת�ж����

#if(KeLu == TRUE)
#define HarmonicPulseOut_Mode       HarmonicPulseOut_Auto//г�����������ʽѡ��
#else
#define HarmonicPulseOut_Mode       HarmonicPulseOut_Interrupt//г�����������ʽѡ��
#endif

#define SinglePhs               1
#define ThreePhs                3
#define nPhs                    ThreePhs      //3�� �����

//------------------------------------------
#define     DL645SOFT_DEBUG     0
#define     HOSC_PLL 0 // 0=PLL 1=HOSC
#define SPI_ESAM            1//
#define     METERTYPE           1       //  ���طѿر�����Ϊ2�����ܵ��ܱ�����Ϊ0 ��Զ������Ϊ1
#define ZBComFlag           0       // 0 ���ز�ͨѶģ��  1 ���ز�ͨѶģ��
#define GataFlag            0       // 0 ���ü̵���  1 ���ü̵���

#define     KEY_Enable       TRUE   //    FALSE  �ް�������   , TRUE  �а���(�������Ǽ��ų����)
#define LCD_DISP        FALSE   //    FALSE     , TRUE
//-----------------------------------
#define  VOLREP_Enable     0x55
#define  VOLREP_Disable     0x00

#define  VOL_REPAIR         VOLREP_Enable  //��ѹӰ��������
#define  MAX_VOLT_STEP      8  //��ѹӰ���������㣬Ԥ��10����

//--------���µ��ж�ѡ��-----------------------
#define     CHECKLVD        0  //�ж�Lvd ��־ȷ���ϵ�����
#define     CHECKCMP1           1  //�ж�cmp1 ��־ȷ���ϵ�����
#define CHECKCMP2           2  //�ж�cmp2 ��־ȷ���ϵ�����
#define CHECKLVD_CMP1       3  //�ж�LVD&cmp1 ��־ȷ���ϵ�����
#define CHECKLVD_CMP2       4  //�ж�LVD&cmp2 ��־ȷ���ϵ�����

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
extern u16                  SysStamp;               //��Dl645_Globals.h�ж��塣

/* Exported functions ------------------------------------------------------- */

//---------------------------------------------------
#endif  //_BSP_H
//---------------------------------------------------

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
