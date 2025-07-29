/****************************************************************************
* @file     Rn8xxx_RTC.h
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.07.30
* @brief    RTC驱动
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  _Rn8xxx_RTC_H
#define  _Rn8xxx_RTC_H

/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/
#define RTC_TIMEOUT 0x3Fff

#define RTC_ALARM_MASK      0x80
#define RTC_ALARM_ENABLE    0x80
#define RTC_ALARM_DISABLE   0x00
/* Exported enum ------------------------------------------------------------*/
typedef enum
{
    RTC_CurveMode_2 = 2,    /*"二次曲线"*/
    RTC_CurveMode_4 = 4,    /*"四次曲线"*/
} eRTC_CurveMode;/*"曲线模式"*/

typedef enum
{
    /*"注意
      1\DOTA0均需要设置
      2\ 四次曲线参数必须设置"*/
    CurveParaDef    = 0,    /*"按芯片SPL默认值恢复曲线参数"*/
    CurveParaSet    = 1,    /*"按传入参数设置曲线参数"*/
} eRTC_IsCurveParaDef; /*"曲线系数是否采用默认值"*/

typedef enum
{
    RTC_IE_EN = 0,   /*"禁止输出"*/
} eRTC_IE_Typedef; /*"RTC时钟源输出频率"*/

typedef enum
{
    RTC_FOUT_Disable    = 0, /*"禁止输出"*/
    RTC_FOUT_1HZ        = 1, /*"1Hz 输出"*/
    RTC_FOUT_1Div30HZ   = 2, /*"1/30Hz 输出"*/
    RTC_FOUT_32768HZ    = 3, /*"32768Hz 输出"*/
    RTC_FOUT_16HZ       = 4, /*"16Hz 输出"*/
    RTC_FOUT_8HZ        = 5, /*"8Hz 输出"*/
    RTC_FOUT_4HZ        = 6, /*"4Hz 输出"*/
} eRTC_FOUT_Typedef; /*"RTC时钟源输出频率"*/

typedef enum
{
    RTC_TCP_2Sec    = 0, /*"2S"*/
    RTC_TCP_10Sec   = 1, /*"10S"*/
    RTC_TCP_20Sec   = 2, /*"20S"*/
    RTC_TCP_30Sec   = 3, /*"30S"*/
    RTC_TCP_1Min    = 4, /*"1 分钟"*/
    RTC_TCP_2Min    = 5, /*"2 分钟"*/
    RTC_TCP_5Min    = 6, /*"5 分钟"*/
    RTC_TCP_10Min   = 7, /*"10 分钟"*/
} eRTC_TCP_Typedef; /*"温度补偿周期"*/

typedef enum
{
    RTC_TSE_Disable     = 0, /*"禁止自动温补"*/
    RTC_TSE_AutoMode    = 1, /*"启动自动温补。按照 TCP 的设置进行周期性温补"*/
    RTC_TSE_UserMode0   = 2, /*"启动用户温补模式 0，
                                温度寄存器可更改，
                                由用户填入温度值，
                                用户每写一次温度寄存器启动一次温度补偿；"*/
    RTC_TSE_UserMode1   = 3, /*"启动用户温补模式 1，
                                温度寄存器不可更改，
                                每次写温度寄存器就启动一次温度补偿操作，
                                温度寄存器的值由MCU 测量得到"*/
} eRTC_TSE_Typedef; /*"温度传感器温补模式"*/

typedef enum
{
    /*"最晚两次记录时
    没有区分缓存中存的时间先后，
    应由软件做判断。"*/
    RTC_KeyFaillingEdge_1   = 0,    /*"第1次下降沿"*/
    RTC_KeyRisingEdge_1,            /*"第1次上升沿"*/
    RTC_KeyFaillingEdge_2,          /*"第2次下降沿"*/
    RTC_KeyRisingEdge_2,            /*"第2次上升沿"*/
} eRTCKeyTimeStampEdge_TypeDef;

typedef enum
{
    RTC_KeyTimeEarliest = 0,    /*"记录IOEN使能后最早两次按键事件"*/
    RTC_KeyTimeLatest   = 1,    /*"记录IOEN使能后最晚两次按键事件"*/
} eRTCKeyTime_TypeDef;

/* Exported types ------------------------------------------------------------*/

typedef struct
{
    uint16_t    DATA0;      /*"初始频率偏差"*/
    uint16_t    XT1;        /*"晶振温度曲线顶点温度"*/
    uint16_t    ALPHA;      /*"晶振一次温度系数"*/
    uint16_t    BETA;       /*"晶振二次温度系数"*/
    uint16_t    GAMMA;      /*"晶振三次温度系数"*/
    uint16_t    ZETA;       /*"晶振四次温度系数"*/
} sRTCCurve4Para;
typedef struct
{
    uint16_t    DATA0;      /*"初始频率偏差"*/
    uint16_t    XT0;        /*"晶振温度曲线顶点温度"*/
    uint16_t    ALPHAL;     /*"晶振低温段二次温度系数"*/
    uint16_t    ALPHAH;     /*"晶振高温段二次温度系数"*/
} sRTCCurve2Para;

typedef union
{
    sRTCCurve2Para Curve2Para;
    sRTCCurve4Para Curve4Para;
} uRTCCurvePara;

/* Exported data ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern ErrorStatus Rn8xxx_RTC_Read(uint8_t *Dst);
extern ErrorStatus Rn8xxx_RTC_Write(uint8_t *Dst, uint8_t Repeat);
extern ErrorStatus Rn8xxx_RTC_CtlCheck(eRTC_TSE_Typedef rtc_tse, eRTC_TCP_Typedef rtc_tcp, eRTC_FOUT_Typedef rtc_fout);
extern ErrorStatus Rn8xxx_RTC_CtlInit(eRTC_TSE_Typedef rtc_tse, eRTC_TCP_Typedef rtc_tcp, eRTC_FOUT_Typedef rtc_fout);
extern ErrorStatus Rn8xxx_RTC_Cnt1Init(uint8_t Unit_S);
extern ErrorStatus Rn8xxx_RTC_Cnt2Init(uint8_t Unit_mS);
extern ErrorStatus Rn8xxx_RTC_CurveModeCheck(eRTC_CurveMode RtcCurveMode, uRTCCurvePara RTCCurvePara, eRTC_IsCurveParaDef IsCurveParaDef);
extern ErrorStatus Rn8xxx_RTC_CurveModeInit(eRTC_CurveMode RtcCurveMode, uRTCCurvePara RTCCurvePara, eRTC_IsCurveParaDef IsCurveParaDef);
extern int32_t Rn8xxx_RTC_TempGet(void);
extern void Rn8xxx_RTC_CurveParaToReg(float RTC_DATA0,
                                      float RTC_XT1,
                                      float RTC_ALPHA,
                                      float RTC_BETA,
                                      float RTC_GAMMA,
                                      float RTC_ZETA,
                                      sRTCCurve4Para *RTCCurve4Para);

#endif  //_Rn8xxx_RTC_H

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
