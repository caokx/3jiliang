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
    IVLD_1BYTE  = 0x01,   //����1�ֽ���Ч
    IVLD_2BYTE  = 0x03,  //����2�ֽ���Ч
    IVLD_3BYTE  = 0x07,  //����3�ֽ���Ч
    IVLD_4BYTE  = 0x0F,  //����4�ֽ���Ч

    OVLD_1BYTE  = 0x01,  //���1�ֽ���Ч
    OVLD_2BYTE  = 0x03,  //���2�ֽ���Ч
    OVLD_3BYTE  = 0x07,  //���3�ֽ���Ч
    OVLD_4BYTE  = 0x0F,  //���4�ֽ���Ч

    ORV_EN      = 1,                //�������
    ORV_DIS     = 0,         //�������

    DUMMY_EN        = 1,        //Ŀ���ַ����Чbyteλ�ã�д��dummyֵ
    DUMMY_DIS       = 0,          //Ŀ���ַ����Чbyteλ�ã�������д����

    ADDR_RV_EN  = 0,       //���ݰ���ַ��������
    ADDR_RV_DIS     = 1,   //���ݰ���ַ��������
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
