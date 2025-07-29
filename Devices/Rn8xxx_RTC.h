/****************************************************************************
* @file     Rn8xxx_RTC.h
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.07.30
* @brief    RTC����
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
    RTC_CurveMode_2 = 2,    /*"��������"*/
    RTC_CurveMode_4 = 4,    /*"�Ĵ�����"*/
} eRTC_CurveMode;/*"����ģʽ"*/

typedef enum
{
    /*"ע��
      1\DOTA0����Ҫ����
      2\ �Ĵ����߲�����������"*/
    CurveParaDef    = 0,    /*"��оƬSPLĬ��ֵ�ָ����߲���"*/
    CurveParaSet    = 1,    /*"����������������߲���"*/
} eRTC_IsCurveParaDef; /*"����ϵ���Ƿ����Ĭ��ֵ"*/

typedef enum
{
    RTC_IE_EN = 0,   /*"��ֹ���"*/
} eRTC_IE_Typedef; /*"RTCʱ��Դ���Ƶ��"*/

typedef enum
{
    RTC_FOUT_Disable    = 0, /*"��ֹ���"*/
    RTC_FOUT_1HZ        = 1, /*"1Hz ���"*/
    RTC_FOUT_1Div30HZ   = 2, /*"1/30Hz ���"*/
    RTC_FOUT_32768HZ    = 3, /*"32768Hz ���"*/
    RTC_FOUT_16HZ       = 4, /*"16Hz ���"*/
    RTC_FOUT_8HZ        = 5, /*"8Hz ���"*/
    RTC_FOUT_4HZ        = 6, /*"4Hz ���"*/
} eRTC_FOUT_Typedef; /*"RTCʱ��Դ���Ƶ��"*/

typedef enum
{
    RTC_TCP_2Sec    = 0, /*"2S"*/
    RTC_TCP_10Sec   = 1, /*"10S"*/
    RTC_TCP_20Sec   = 2, /*"20S"*/
    RTC_TCP_30Sec   = 3, /*"30S"*/
    RTC_TCP_1Min    = 4, /*"1 ����"*/
    RTC_TCP_2Min    = 5, /*"2 ����"*/
    RTC_TCP_5Min    = 6, /*"5 ����"*/
    RTC_TCP_10Min   = 7, /*"10 ����"*/
} eRTC_TCP_Typedef; /*"�¶Ȳ�������"*/

typedef enum
{
    RTC_TSE_Disable     = 0, /*"��ֹ�Զ��²�"*/
    RTC_TSE_AutoMode    = 1, /*"�����Զ��²������� TCP �����ý����������²�"*/
    RTC_TSE_UserMode0   = 2, /*"�����û��²�ģʽ 0��
                                �¶ȼĴ����ɸ��ģ�
                                ���û������¶�ֵ��
                                �û�ÿдһ���¶ȼĴ�������һ���¶Ȳ�����"*/
    RTC_TSE_UserMode1   = 3, /*"�����û��²�ģʽ 1��
                                �¶ȼĴ������ɸ��ģ�
                                ÿ��д�¶ȼĴ���������һ���¶Ȳ���������
                                �¶ȼĴ�����ֵ��MCU �����õ�"*/
} eRTC_TSE_Typedef; /*"�¶ȴ������²�ģʽ"*/

typedef enum
{
    /*"�������μ�¼ʱ
    û�����ֻ����д��ʱ���Ⱥ�
    Ӧ��������жϡ�"*/
    RTC_KeyFaillingEdge_1   = 0,    /*"��1���½���"*/
    RTC_KeyRisingEdge_1,            /*"��1��������"*/
    RTC_KeyFaillingEdge_2,          /*"��2���½���"*/
    RTC_KeyRisingEdge_2,            /*"��2��������"*/
} eRTCKeyTimeStampEdge_TypeDef;

typedef enum
{
    RTC_KeyTimeEarliest = 0,    /*"��¼IOENʹ�ܺ��������ΰ����¼�"*/
    RTC_KeyTimeLatest   = 1,    /*"��¼IOENʹ�ܺ��������ΰ����¼�"*/
} eRTCKeyTime_TypeDef;

/* Exported types ------------------------------------------------------------*/

typedef struct
{
    uint16_t    DATA0;      /*"��ʼƵ��ƫ��"*/
    uint16_t    XT1;        /*"�����¶����߶����¶�"*/
    uint16_t    ALPHA;      /*"����һ���¶�ϵ��"*/
    uint16_t    BETA;       /*"��������¶�ϵ��"*/
    uint16_t    GAMMA;      /*"���������¶�ϵ��"*/
    uint16_t    ZETA;       /*"�����Ĵ��¶�ϵ��"*/
} sRTCCurve4Para;
typedef struct
{
    uint16_t    DATA0;      /*"��ʼƵ��ƫ��"*/
    uint16_t    XT0;        /*"�����¶����߶����¶�"*/
    uint16_t    ALPHAL;     /*"������¶ζ����¶�ϵ��"*/
    uint16_t    ALPHAH;     /*"������¶ζ����¶�ϵ��"*/
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
