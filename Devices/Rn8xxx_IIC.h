/****************************************************************************
* @file     Rn8xxx_IIC.h
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.06.10
* @brief    IICÇý¶¯
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  _Rn8xxx_IIC_H
#define  _Rn8xxx_IIC_H

/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/
#define IIC_TIMEOUT 0xfff

/* Exported enum ------------------------------------------------------------*/

//---------------------------------------------------
//----------------------------
//---------------------------------------------------
typedef enum
{
    F8M_400K = 2,
    F8M_100K = 4,

    F16M_400K = 3,
    F16M_100K = 5,

    F32M_400K = 4,
    F32M_100K = 6,
} eIICCLKDIV_enum;

/* Exported data ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

extern void Rn8xxx_IIC_HardMode_Init(uint8_t clkdiv);
extern ErrorStatus Rn8xxx_IIC_HardMode_Start(uint8_t iic_id);
extern void Rn8xxx_IIC_HardMode_Stop(void);
extern ErrorStatus Rn8xxx_IIC_HardMode_SendByte(uint8_t data);
extern u8 Rn8xxx_IIC_HardMode_ReceiveByte(BOOL ACK);

//---------------------------------------------------
#endif  //_IIC_H
//---------------------------------------------------

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
