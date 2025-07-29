/****************************************************************************
* @file     RTCDrive.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2023.06.05
* @brief    RTC����
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include <Rn8xxx_Gpio.h>
#include <Rn8xxx_GpioRegMap.h>
#include <Rn8xxx_RTC.h>

//extern ErrorStatus Std_Memcmp(const void* cmp1, const void* cmp2, u16 len);

/* Private define ------------------------------------------------------------*/
/*"�Ĵ�����ַ"*/
#define RTC_REG_TEMP2           (*(uint32_t *)(0x4003C0F8))/*"BIT0-BIT11"*/
#define RTC_REG_TPS_START       (*(uint32_t *)(0x4003C150))/*"���������Ĵ���"*/
#define RTC_REG_TEMP_CAL        (*(uint32_t *)(0x4003C154))/*"BIT0-BIT11"*/

/*"�������߲����Ĵ�����"*/
#define RTC_REG_PS              (*(uint32_t *)(0x4003C040))
#define RTC_REG_MODE            (*(uint32_t *)(0x4003C044))/*"boot ����"*/
#define RTC_REG_DOTA0           (*(uint32_t *)(0x4003C048))/*"boot ����"*/
#define RTC_REG_ALPHAL          (*(uint32_t *)(0x4003C04C))/*"boot ����"*/
#define RTC_REG_ALPHAH          (*(uint32_t *)(0x4003C050))/*"boot ����"*/
#define RTC_REG_XT0             (*(uint32_t *)(0x4003C054))/*"boot ����"*/
/*"�Ĵ����߲����Ĵ�����"*/
#define RTC_REG_MODE1           (*(uint32_t *)(0x4003C130))
#define RTC_REG_XT1             (*(uint32_t *)(0x4003C134))
#define RTC_REG_ALPHA           (*(uint32_t *)(0x4003C138))
#define RTC_REG_BETA            (*(uint32_t *)(0x4003C13C))
#define RTC_REG_GAMMA           (*(uint32_t *)(0x4003C140))
#define RTC_REG_ZETA            (*(uint32_t *)(0x4003C144))

/*"SPL��ַ"*/
#define RTC_REG_DEFAULT_DOTA0       (*(volatile uint16_t *)(0x00080200 + 2 * 5))
#define RTC_REG_DEFAULT_ALPHAL      (*(volatile uint16_t *)(0x00080200 + 2 * 6))
#define RTC_REG_DEFAULT_ALPHAH      (*(volatile uint16_t *)(0x00080200 + 2 * 7))
#define RTC_REG_DEFAULT_XT0         (*(volatile uint16_t *)(0x00080200 + 2 * 8))

#define RTC_RTCPS_EN             (0x8e)

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void rtc_Delay(void)
{
    uint16_t i;
    for (i = 400; i > 0; i--)
    {
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }
}

/* Exported functions ----------------------------------------------------------*/

/*********************************************************************************************************
** Function name:       Rn8xxx_RTC_CtlCheck
** Descriptions:        RTC���ƼĴ���У��
** input parameters:    None
** output parameters:   None
** Returned value:     SUCCESS�ɹ���ERRORʧ��
*********************************************************************************************************/
ErrorStatus Rn8xxx_RTC_CtlCheck(eRTC_TSE_Typedef rtc_tse, eRTC_TCP_Typedef rtc_tcp, eRTC_FOUT_Typedef rtc_fout)
{
    uint32_t CheckCtrl;

    CheckCtrl = ((rtc_fout << 0) |      /*"RTCʱ��Դ���Ƶ��"*/
                 (rtc_tcp << 3) |    /*"�¶Ȳ�������"*/
                 (rtc_tse << 6));     /*"�¶ȴ������²�ģʽ"*/

    if (((RTC->CTRL) & 0xff) == CheckCtrl)
    {
        return (SUCCESS);
    }
    else
    {
        return (ERROR);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_RTC_CtlInit
** Descriptions:        RTC���ƼĴ������ú���
** input parameters:    rtc_tse:�¶ȴ������²�ģʽ
**                      rtc_tcp:�¶Ȳ�������
**                      rtc_fout:RTCʱ��Դ���Ƶ��
** output parameters:   None
** Returned value:     SUCCESS�ɹ���ERRORʧ��
*********************************************************************************************************/
ErrorStatus Rn8xxx_RTC_CtlInit(eRTC_TSE_Typedef rtc_tse,
                               eRTC_TCP_Typedef rtc_tcp,
                               eRTC_FOUT_Typedef rtc_fout)
{
    SysCtl_EnableWrite;
    RTC_SAR_Clk_En;             /*" ��RTC/SARʱ�ӣ������ʱ��һֱ��"*/

    if (rtc_fout != RTC_FOUT_Disable)
    {
        GPIO_Clk_En;            /*" ��GPIO APBʱ�ӣ������ʱ��һֱ��"*/
    }
    RtcCtl_EnableWrite;

    if (fnRegState_Detect((u32)(&RTC->CTRL), 9, 0, RTC_TIMEOUT) == ERROR) /*"Wr_busy�ȴ�"*/
    {
        return (ERROR);
    }

    RTC->CTRL = ((rtc_fout << 0) |      /*"RTCʱ��Դ���Ƶ��"*/
                 (rtc_tcp << 3) |    /*"�¶Ȳ�������"*/
                 (rtc_tse << 6) |   /*"�¶ȴ������²�ģʽ"*/
                 (1 << 8));     /*"��ֹ RTC �Ĵ���д���� "*/

    rtc_Delay();

    return (Rn8xxx_RTC_CtlCheck(rtc_tse, rtc_tcp, rtc_fout));
}

/*********************************************************************************************************
** Function name:       fnRTCDrive_Init
** Descriptions:        RTC��ʼ������
** input parameters:    None
** output parameters:   None
** Returned value:     SUCCESS�ɹ���ERRORʧ��
*********************************************************************************************************/
ErrorStatus Rn8xxx_RTC_AlarmInit(uint8_t SCA, uint8_t MNA, uint8_t HRA)
{
    SysCtl_EnableWrite;

    RTC_SAR_Clk_En;             /*" ��RTC/SARʱ�ӣ������ʱ��һֱ��"*/

    RtcCtl_EnableWrite;
    RTC->SCA = SCA;
    RTC->MNA = MNA;
    RTC->HRA = HRA;

    RTC->IF = (0x08);
    RTC->IE |= (0x08 | 0x200);

    rtc_Delay();
    return (SUCCESS);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_RTC_Cnt1Init
** Descriptions:        RTC��ʱ��1��ʼ��
** input parameters:    Unit_S:��ʱ��ʱ�䣬��λS
** output parameters:   None
** Returned value:      SUCCESS �ɹ�  ERROR ���ݴ���ʧ��
*********************************************************************************************************/
ErrorStatus Rn8xxx_RTC_Cnt1Init(uint8_t Unit_S)
{
    if (Unit_S == 0)
    {
        return ERROR;
    }
    RtcCtl_EnableWrite;     //RTC Write enable
    RTC->CNT1 = Unit_S - 1;
    RTC->IF = (0x02);
    RTC->IE |= (0x02);
    RtcCtl_DisableWrite;
    return SUCCESS;
}

/*********************************************************************************************************
** Function name:       Rn8xxx_RTC_Cnt2Init
** Descriptions:        RTC��ʱ��1��ʼ��
** input parameters:    Unit_mS:��ʱ��ʱ�䣬��λms,�̶�3.9ms
** output parameters:   None
** Returned value:      SUCCESS �ɹ�  ERROR ���ݴ���ʧ��
*********************************************************************************************************/
ErrorStatus Rn8xxx_RTC_Cnt2Init(uint8_t Unit_mS)
{
    if (Unit_mS == 0)
    {
        return ERROR;
    }
    RtcCtl_EnableWrite;     //RTC Write enable
    RTC->CNT2 = Unit_mS - 1;
    RTC->IF = 0x04;
    RTC->IE |= 0x04;
    RtcCtl_DisableWrite;
    return SUCCESS;
}

/*********************************************************************************************************
** Function name:       Rn8xxx_RTC_CurveModeCheck
** Descriptions:        ���߲���У��
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
ErrorStatus Rn8xxx_RTC_CurveModeCheck(eRTC_CurveMode RtcCurveMode,
                                      uRTCCurvePara RTCCurvePara,
                                      eRTC_IsCurveParaDef IsCurveParaDef)
{
    if (RTC_CurveMode_4 == RtcCurveMode) /*"�Ĵ�����"*/
    {
        if ((0xea65 != RTC_REG_MODE1) ||
            (RTCCurvePara.Curve4Para.DATA0 != RTC_REG_DOTA0) ||
            (RTCCurvePara.Curve4Para.XT1 != RTC_REG_XT1) ||
            (RTCCurvePara.Curve4Para.ALPHA != RTC_REG_ALPHA) ||
            (RTCCurvePara.Curve4Para.BETA != RTC_REG_BETA) ||
            (RTCCurvePara.Curve4Para.GAMMA != RTC_REG_GAMMA) ||
            (RTCCurvePara.Curve4Para.ZETA != RTC_REG_ZETA))
        {
            return ERROR;
        }
    }
    else                                     /*"��������"*/
    {
        if (CurveParaDef == IsCurveParaDef)
        {
            if ((0x00 != RTC_REG_MODE1) ||
                (RTC_REG_DEFAULT_DOTA0 != RTC_REG_DOTA0) ||
                (RTC_REG_DEFAULT_XT0 != RTC_REG_XT0) ||
                (RTC_REG_DEFAULT_ALPHAL != RTC_REG_ALPHAL) ||
                (RTC_REG_DEFAULT_ALPHAH != RTC_REG_ALPHAH))
            {
                return ERROR;
            }
        }
        else
        {
            if ((0x00 != RTC_REG_MODE1) ||
                (RTCCurvePara.Curve2Para.DATA0 != RTC_REG_DOTA0) ||
                (RTCCurvePara.Curve2Para.XT0 != RTC_REG_XT0) ||
                (RTCCurvePara.Curve2Para.ALPHAL != RTC_REG_ALPHAL) ||
                (RTCCurvePara.Curve2Para.ALPHAH != RTC_REG_ALPHAH))
            {
                return ERROR;
            }
        }
    }
    return SUCCESS;
}

/*********************************************************************************************************
** Function name:       Rn8xxx_RTC_CurveModeInit
** Descriptions:        RTC�¶Ȳ������߳�ʼ������
** input parameters:    RtcCurveMode:����ģʽ
**                      RTCCurvePara:����ϵ��
**                      IsCurveParaDef:����ϵ���Ƿ����Ĭ��ֵ
** output parameters:   None
** Returned value:      SUCCESS �ɹ�  ERROR ���ݴ���ʧ��
*********************************************************************************************************/
ErrorStatus Rn8xxx_RTC_CurveModeInit(eRTC_CurveMode RtcCurveMode,
                                     uRTCCurvePara RTCCurvePara,
                                     eRTC_IsCurveParaDef IsCurveParaDef)
{
    SysCtl_EnableWrite;
    RTC_SAR_Clk_En;         /*" ��RTC/SAR/GPIO APBʱ�ӣ������ʱ��һֱ��"*/
    RtcCtl_EnableWrite;     /*" RTC Write enable"*/

    RTC_REG_PS = RTC_RTCPS_EN;          /*"RTC_PS  ��8'h8Eʱ�������Ĵ���44H~60H�ſ�д"*/

    if (RTC_CurveMode_4 == RtcCurveMode) /*"�Ĵ�����"*/
    {
        RTC_REG_MODE1 = 0xea65; /*"RTC_MODE1 ��16'hEA65�������Ĵ����߲���"*/                //
        RTC_REG_DOTA0 = RTCCurvePara.Curve4Para.DATA0;          /*"�����¶����߶����¶�"*/
        RTC_REG_XT1 = RTCCurvePara.Curve4Para.XT1;          /*"�����¶����߶����¶�"*/
        RTC_REG_ALPHA = RTCCurvePara.Curve4Para.ALPHA;      /*"����һ���¶�ϵ��"*/
        RTC_REG_BETA = RTCCurvePara.Curve4Para.BETA;            /*"��������¶�ϵ��"*/
        RTC_REG_GAMMA = RTCCurvePara.Curve4Para.GAMMA;      /*"���������¶�ϵ��"*/
        RTC_REG_ZETA = RTCCurvePara.Curve4Para.ZETA;            /*"�����Ĵ��¶�ϵ��"*/
    }
    else                                     /*"��������"*/
    {
        RTC_REG_MODE1 = 0;     /*"RTC_MODE1 ��0�����ö������߲���"*/
        //RTC_REG_DOTA0 = RTCCurvePara.Curve2Para.DATA0;
        if (CurveParaDef == IsCurveParaDef)
        {
            /*"��SPL�лָ�,RA9701A"*/
            //RTC_REG_DOTA0 = (uint32_t)RTC_REG_DEFAULT_DOTA0;       /*"RTC_DOTA0"*/
            RTC_REG_ALPHAL = (uint32_t)RTC_REG_DEFAULT_ALPHAL;     /*"RTC_ALPHAL"*/
            RTC_REG_ALPHAH = (uint32_t)RTC_REG_DEFAULT_ALPHAH;     /*"RTC_ALPHAH"*/
            RTC_REG_XT0 = (uint32_t)RTC_REG_DEFAULT_XT0;     /*"RTC_XT0"*/
        }
        else
        {
            /*"���ö������߲���"*/
            RTC_REG_ALPHAL = RTCCurvePara.Curve2Para.ALPHAL;     /*"RTC_ALPHAL"*/
            RTC_REG_ALPHAH = RTCCurvePara.Curve2Para.ALPHAH;     /*"RTC_ALPHAH"*/
            RTC_REG_XT0 = RTCCurvePara.Curve2Para.XT0;     /*"RTC_XT0"*/
        }
        RtcWriteDota(RTCCurvePara.Curve2Para.DATA0);
    }
    RtcCtl_DisableWrite;
    SysCtl_DisableWrite;
    return (Rn8xxx_RTC_CurveModeCheck(RtcCurveMode, RTCCurvePara, IsCurveParaDef));
}

/*********************************************************************************************************
** Function name:        fnRTCDrive_TempGet
** Descriptions:        ��ȡMCU�ڲ��¶�
** input parameters:     void
** output parameters:
** Returned value:   Temperature_value  �¶�ֵ��λ  ������-3
*********************************************************************************************************/
int32_t Rn8xxx_RTC_TempGet(void)
{
    int32_t Temperature_value;
    if (RTC_REG_TEMP2 & BIT11)
    {
        Temperature_value = (int32_t)(RTC_REG_TEMP2 & 0xFFF) -0x1000;
    }
    else
    {
        Temperature_value = (int32_t)(RTC_REG_TEMP2 & 0xFFF);
    }
    Temperature_value = (int32_t)((float)(Temperature_value) * 62.5); /*"250=1000/4"*/

    return (Temperature_value);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_RTC_Read
** Descriptions:        RTC��ȡ����
** input parameters:    Dst��ȡ���ݻ�����Ŀ��ָ��
** output parameters:   None
** Returned value:     SUCCESS�ɹ���ERRORʧ��
*********************************************************************************************************/
ErrorStatus Rn8xxx_RTC_Read(uint8_t *Dst)
{
    u8 Buffer[7], i;
    for (i = 0; i < 3; i++)
    {
        // ��ȡRTC������ʱ��
        // �����ζ�ȡ��ͬʱ����Ϊ��ȡ�ɹ�����ֹ��Sʱʱ�����
        Dst[0] = RTC->SC;
        Dst[1] = RTC->MN;
        Dst[2] = RTC->HR;
        Dst[4] = RTC->DT;
        Dst[5] = RTC->MO;
        Dst[6] = RTC->YR;
        Dst[3] = RTC->DW;

        Buffer[0] = RTC->SC;
        Buffer[1] = RTC->MN;
        Buffer[2] = RTC->HR;
        Buffer[4] = RTC->DT;
        Buffer[5] = RTC->MO;
        Buffer[6] = RTC->YR;
        Buffer[3] = RTC->DW;
        if (memcmp(&Buffer[0], &Dst[0], 6) != 0)
        {
            continue;
        }
        else
        {
            return (SUCCESS);
        }
    }
    return (ERROR);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_RTC_Write
** Descriptions:        RTCд������
** input parameters:    Dstд��������Դָ�룬Repeatʧ���ظ�����
** output parameters:   None
** Returned value:     SUCCESS�ɹ���ERRORʧ��
*********************************************************************************************************/
ErrorStatus Rn8xxx_RTC_Write(uint8_t *Dst, uint8_t Repeat)
{
    uint8_t Buffer[7], i;
    RtcCtl_EnableWrite;     //RTC Write enable

    for (; Repeat > 0; Repeat--)
    {
        for (i = 0; i < 3; i++)
        {
            if (!(RTC->CTRL & 0x200))
            {
                break;    // �ж�RTC�Ƿ���æ��־
            }
            rtc_Delay();
        }
        if (RTC->CTRL & 0x200)
        {
            continue;
        }
        // ����RTC������ʱ��
        // �����ζ�ȡ��ͬʱ����Ϊ��ȡ�ɹ�����ֹ��Sʱʱ�����
        RTC->SC = Dst[0];
        RTC->MN = Dst[1];
        RTC->HR = Dst[2];
        RTC->YR = Dst[6];
        RTC->MO = Dst[5];
        RTC->DT = Dst[4];
        RTC->DW = Dst[3];
        rtc_Delay();        // д�������ʱ350us���ڶ�ȡ�Ĵ�������ȷ���Ƿ�д��ɹ�
        if (Rn8xxx_RTC_Read(Buffer) == ERROR)
        {
            continue;
        }
        if (memcmp(&Buffer[0], &Dst[0], 6) != 0)
        {
            continue;
        }
        else
        {
            RtcCtl_DisableWrite;
            return (SUCCESS);
        }
    }
    RtcCtl_DisableWrite;      // RTC Write Disable
    return (ERROR);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_RTC_CurveParaToReg
** Descriptions:
** input parameters:    None
** output parameters:   None
** Returned value:     None
*********************************************************************************************************/
void Rn8xxx_RTC_CurveParaToReg(float RTC_DATA0,
                               float RTC_XT1,
                               float RTC_ALPHA,
                               float RTC_BETA,
                               float RTC_GAMMA,
                               float RTC_ZETA,
                               sRTCCurve4Para *RTCCurve4Para)
{
    //int16_t i16_temp;
    RTCCurve4Para->DATA0 = (uint16_t)((int16_t)(RTC_DATA0 * 32)) & 0x1FFF;
    RTCCurve4Para->XT1 = (uint16_t)((int16_t)(RTC_XT1 * 256)) & 0x1FFF;
    RTCCurve4Para->ALPHA = (uint16_t)((int16_t)(RTC_ALPHA * 262144)) & 0xFFFF; /*""*/
    RTCCurve4Para->BETA = (uint16_t)((int16_t)(RTC_BETA * 524288)) & 0x7FFF; /*""*/
    RTCCurve4Para->GAMMA = (uint16_t)((int16_t)(65536 + RTC_GAMMA * 268435456)) & 0xFFFF; /*""*/
    if (RTC_ZETA >= 0)
    {
        RTCCurve4Para->ZETA = (uint16_t)(RTC_ZETA * 17179869184) & 0xFFFF; /*""*/
    }
    else
    {
        RTCCurve4Para->ZETA = (uint16_t)(65536 + RTC_ZETA * 17179869184) & 0xFFFF; /*""*/
    }
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
