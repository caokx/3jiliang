/****************************************************************************
* @file     Uart.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.04.28
* @brief    Uart驱动
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef  _BSP_ESAM_H
#define  _BSP_ESAM_H

#ifdef   DRIVE_BSP_ESAM_GLOBALS
#define  BSP_ESAM_EXT
#else
#define  BSP_ESAM_EXT   extern
#endif
/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/

#define  Esam_SPI_ID        SPI3_ID//
#define  Esam_SPI_SPEED        2330000

#define  SPI_Esam_HardwareMode    0
#define  SPI_Esam_FirmwareMode    1
#define  SPI_Esam_Mode            SPI_Esam_HardwareMode//SPI_Esam_HardwareMode//SPI_Esam_FirmwareMode

//;CPU卡类型命令码集合
//;======================================================================
#define     UserCard            0x01    //;用户卡命令码

#define     UserCardLen         39  //;用户卡长度
#define     InitCardType        0x01    //;初始化卡类型码
#define     UserCardType        0x02    //;普通用户卡类型码
#define     RecuitCardType      0x03    //;补卡类型码

#define     SetPswCard          0x02    //;密钥修改卡命令码
#define     RestorePswCard      0x03    //;密钥恢复卡命令码
#define     PswCardLen          4   //;密钥卡长度

#define     PutParaVarCard      0x04    //;参数修改卡命令码
#define     PutParaVarCardLen   12  //;参数修改卡长度

#define     ReadBackCard        0x05    //;回抄卡命令码
#define     ReadBackCardLen     0x00    //;回抄卡长度

#define     PresetCard          0x06    //;预制卡命令码
#define     PresetCardLen       26  //;预制卡长度

#define     PutMeterNumCard     0x07    //;表号卡命令码
#define     PutMeterNumCardLen  12  //;表号卡长度

#define     IncMoneyCard        0x08    //;增加电量卡命令码
#define     IncMoneyCardLen     8   //;增加电量卡长度

#define     RelayCard   0x09    //;继电器卡命令码
#define     RelayCardLen        0   //;继电器卡长度
/* Exported enum ------------------------------------------------------------*/

typedef enum
{
    ESAM        = 0x00,
    CARD        = 0x01
} eICEsamSelFlag_TypeDef;

typedef struct
{
    u32 FailStamp;          // 低电平计算脉宽
    u16 HighStamp;          // 高电平时间计时
    u8  EFlag;          // 卡插入处理标志，有此标志时进行卡处理，卡操作完成后退出
} sISO7816ComBuf_TypeDef;

/* Exported data ----------------------------------------------------------*/

BSP_ESAM_EXT    sISO7816ComBuf_TypeDef I7816ComExt;

/* Exported functions ------------------------------------------------------- */

extern void BSP_ISO7816_Init(void);
extern void BSP_Esam_Stop(void);
extern u8 BSP_EASM_GetPower(void);
extern void BSP_EsamSpi_Init(void);
extern void BSP_EsamSpi_WriteByte(uint8_t data);
extern uint8_t BSP_EsamSpi_ReadByte(void);
extern ErrorStatus fnCardSendByte(u8 CH, u8 Data);
extern ErrorStatus fnCardGetByte(u8 CH,  u8 *Data);

#endif

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
