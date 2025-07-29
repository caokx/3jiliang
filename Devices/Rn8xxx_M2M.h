/**
  ******************************************************************************
  * @file    Rn8xxx_M2M.h
  * @author  Renergy Application Team
  * @version V1.0.0
  * @date    2023.4.09
  * @brief
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include <Rn8xxx_Common.h>

#ifndef _Rn8xxx_M2M_H
#define _Rn8xxx_M2M_H

#ifdef   _DRIVE_M2M_GLOBALS
#define  Rn8xxx_M2M_EXT
#else
#define  Rn8xxx_M2M_EXT  extern
#endif

//-----------------------------------------
#define M2M_TimeOut 0x3ff

typedef enum
{
    IVLD_1BYTE  = 0x01,   //输入1字节有效
    IVLD_2BYTE  = 0x03,  //输入2字节有效
    IVLD_3BYTE  = 0x07,  //输入3字节有效
    IVLD_4BYTE  = 0x0F,  //输入4字节有效

    OVLD_1BYTE  = 0x01,  //输出1字节有效
    OVLD_2BYTE  = 0x03,  //输出2字节有效
    OVLD_3BYTE  = 0x07,  //输出3字节有效
    OVLD_4BYTE  = 0x0F,  //输出4字节有效

    ORV_EN      = 1,                //反序搬运
    ORV_DIS     = 0,         //正序搬运

    DUMMY_EN        = 1,        //目标地址中无效byte位置，写入dummy值
    DUMMY_DIS       = 0,          //目标地址中无效byte位置，不进行写操作

    ADDR_RV_EN  = 0,       //数据按地址反序排列
    ADDR_RV_DIS     = 1,   //数据按地址正序排列
} eM2M_ModePara_TypeDef;

typedef union
{
    struct
    {
        u32 Mode_IVLD   : 4;
        u32 Mode_OVLD   : 4;
        u32 Mode_ORV    : 1;
        u32 Mode_DUMMY      : 1;
        u32 Mode_ADDR_RV    : 1;
        u32  RESERVEBIT                  : 21;
    };
    u32 gMode;
} uM2M_ModePara_TypeDef;
//-----------------------------------------

extern ErrorStatus Rn8xxx_M2M_Move(uM2M_ModePara_TypeDef M2M_ModePara, u32 SAddr, u32 DAddr, u16 ILen);
#endif
/****************************  (C) COPYRIGHT Renergy  ****************************/
/****************************          END OF FILE          ****************************/
