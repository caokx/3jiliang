/****************************************************************************
* @file     LvdCmpSar.h
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.06.29
* @brief    LvdCmpSar驱动
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _Rn8xxx_LvdCmpSar_H
#define _Rn8xxx_LvdCmpSar_H

/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/

#define LvdCmpSar_TIMEOUT 0x3fff

/* Exported enum ------------------------------------------------------------*/

//lvd vol 配置
typedef enum
{
    LVDS_Vol2p3 = 0, /*"2.7V"*/
    LVDS_Vol2p7 = 2,
    LVDS_Vol2p9 = 3,
    LVDS_Vol3p1 = 4,
    LVDS_Vol3p3 = 5,
    LVDS_Vol3p5 = 6,
    LVDS_Vol3p7 = 7,
    LVDS_Vol3p9 = 8,
    LVDS_Vol4p1 = 9,
    LVDS_Vol4p3 = 10,
    LVDS_Vol4p5 = 11,
    LVDS_Vol4p7 = 12,
    LVDS_Vol4p9 = 13,
    //外部管脚输入
    LVDS_Vol1p25 = 14,
} eLVD_LVDS_Typedef; /*"电源电压输入"*/

typedef enum
{
    LVDCMPSAR_IE_Disable = 0,
    LVDCMPSAR_IE_Enable = 1,
} eLVDCMPSAR_IE_TypeDef;

typedef enum
{
    CMP1_Channel = 0,
    CMP2_Channel = 1,
} eCMP_CH_TypeDef; /*"CMP 通道选择"*/

typedef enum
{
    CMP_R600K_Disable = 0,
    CMP_R600K_Enable = 1,
} eCMP_R600K_TypeDef; /*"CMP2 内部 600K 电阻采样开关"*/

typedef enum
{
    CMP_Hysen_Disable = 0,
    CMP_Hysen_Enable = 1,
} eCMP_Hysen_TypeDef; /*"内部迟滞比较器迟滞开关"*/

//sarctl 寄存器
typedef union
{
    struct
    {
        u32 Channel: 4; //ch3-ch
        u32 PGA: 2;
        u32 IE: 1;
        u32 Reserved: 25;
    };
    u32 SAR_CTL;
} uSarCtlPara_TypeDef;

typedef enum
{
    TempSensor_Channel = 0,
    VBAT_Channel = 1,
    AIN0_Channel = 2,
    AIN1_Channel = 3,
    AIN2_Channel = 4,
    AIN3_Channel = 5,
    AIN4_Channel = 6,
    AIN5_Channel = 7,
    AIN6_Channel = 8,
} eSARCTL_CH_TypeDef; /*"SAR ADC 通道选择"*/

typedef enum
{
    PGA_0p5 = 0,
    PGA_1p0 = 1,
    PGA_1p5 = 2,
    PGA_2p0 = 3,
} eSARCTL_PGA_TypeDef; /*" PGA选择"*/

typedef enum
{
    LVD_CH = 0,
    CMP1_CH = 1,
    CMP2_CH = 2,
} eLVDCMP_CH_TypeDef; /*"获取状态 通道选择"*/

typedef enum
{
    SAR_NormalMode = 0,
    SAR_HighMode = 1,
} eSAR_PerfMODE; /*"SAR性能模式"*/

/* Exported types ------------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void Rn8xxx_LVD_Init(eLVD_LVDS_Typedef lvds, eLVDCMPSAR_IE_TypeDef SwitchIE);
extern void Rn8xxx_LVD_Stop(void);
extern void Rn8xxx_CMP_Init(eCMP_CH_TypeDef ch, eCMP_R600K_TypeDef SwitchR600, eCMP_Hysen_TypeDef SwitchHysen, eLVDCMPSAR_IE_TypeDef SwitchIE);
extern void Rn8xxx_CMP_Stop(eCMP_CH_TypeDef ch);
extern u32 Rn8xxx_SarADC_Get(eSARCTL_CH_TypeDef ch, eSARCTL_PGA_TypeDef pga);
extern u8 Rn8xxx_LvdCmp_STAT(eLVDCMP_CH_TypeDef ch, u32 checkTime);
extern u8 Rn8xxx_LvdCmp_STATPowerUp(eLVDCMP_CH_TypeDef ch, u32 checkTime);
extern void Rn8xxx_LvdCmpSar_Mode(eSAR_PerfMODE PerfMODE);
#endif

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
