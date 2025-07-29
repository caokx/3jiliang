/****************************************************************************
* @file     Uart.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.04.28
* @brief    Uart����
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

//;CPU�����������뼯��
//;======================================================================
#define     UserCard            0x01    //;�û���������

#define     UserCardLen         39  //;�û�������
#define     InitCardType        0x01    //;��ʼ����������
#define     UserCardType        0x02    //;��ͨ�û���������
#define     RecuitCardType      0x03    //;����������

#define     SetPswCard          0x02    //;��Կ�޸Ŀ�������
#define     RestorePswCard      0x03    //;��Կ�ָ���������
#define     PswCardLen          4   //;��Կ������

#define     PutParaVarCard      0x04    //;�����޸Ŀ�������
#define     PutParaVarCardLen   12  //;�����޸Ŀ�����

#define     ReadBackCard        0x05    //;�س���������
#define     ReadBackCardLen     0x00    //;�س�������

#define     PresetCard          0x06    //;Ԥ�ƿ�������
#define     PresetCardLen       26  //;Ԥ�ƿ�����

#define     PutMeterNumCard     0x07    //;��ſ�������
#define     PutMeterNumCardLen  12  //;��ſ�����

#define     IncMoneyCard        0x08    //;���ӵ�����������
#define     IncMoneyCardLen     8   //;���ӵ���������

#define     RelayCard   0x09    //;�̵�����������
#define     RelayCardLen        0   //;�̵���������
/* Exported enum ------------------------------------------------------------*/

typedef enum
{
    ESAM        = 0x00,
    CARD        = 0x01
} eICEsamSelFlag_TypeDef;

typedef struct
{
    u32 FailStamp;          // �͵�ƽ��������
    u16 HighStamp;          // �ߵ�ƽʱ���ʱ
    u8  EFlag;          // �����봦���־���д˱�־ʱ���п�������������ɺ��˳�
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
