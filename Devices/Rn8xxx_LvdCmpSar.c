/****************************************************************************
* @file     LvdCmpSar.c
* @author   Renergy Application Team
* @version  V1.0.1
* @date     2021.07.30
* @brief    LvdCmpSar����
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include <Rn8xxx_LvdCmpSar.h>
/* Private define ------------------------------------------------------------*/
/*"�Ĵ�����ַ"*/
#define SAR_REG_ANA_PASSWD          (*(uint32_t *)(0x4002C044))/*"ANA_PASSWD "*/
#define SAR_REG_SAR_TEST            (*(uint32_t *)(0x4002C04c))/*"SAR TEST"*/
#define SAR_REG_ANA_CTL             (*(uint32_t *)(0x4002C058))/*"ANA_ CTL"*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/

/*********************************************************************************************************
** Function name:
** Descriptions:         LVDģ���ʼ��
** input parameters:     LvdCtl:lvd���üĴ���
** output parameters:   ��
** Returned value:   ��
*********************************************************************************************************/
void Rn8xxx_LVD_Init(eLVD_LVDS_Typedef lvds, eLVDCMPSAR_IE_TypeDef SwitchIE)
{
    SysCtl_EnableWrite;
    CMPLVD_Clk_En;
    LVD_PD_PowOn;

    MADC->LVD_CTRL &= 0xFFFFFFD0;
    MADC->LVD_CTRL |= ((lvds) | (SwitchIE << 5));  /*" LVD ��ֵ��ѹ����"*/      /*" LVD �ж�ʹ��"*/

    MADC->LVD_STAT = 0x10;
    if (SwitchIE == LVDCMPSAR_IE_Enable)
    {
        NVIC_EnableIRQ(CMP_IRQn);
    }
    else
    {
    }
}

/*********************************************************************************************************
** Function name:        Rn8xxx_LVD_Stop
** Descriptions:         �ر�LVDģ��
** input parameters:     void
** output parameters:   ��
** Returned value:   ��
*********************************************************************************************************/
void Rn8xxx_LVD_Stop(void)
{
    SysCtl_EnableWrite;
    LVD_PD_PowDwn;
    MADC->LVD_CTRL &= 0xFFFFFFD0;
}

/*********************************************************************************************************
** Function name:       Rn8xxx_CMP_Init
** Descriptions:         CMP��ʼ��
** input parameters:     CmpCtl: ʹ������
** output parameters:   ��
** Returned value:   ��
*********************************************************************************************************/
void Rn8xxx_CMP_Init(eCMP_CH_TypeDef ch, eCMP_R600K_TypeDef SwitchR600, eCMP_Hysen_TypeDef SwitchHysen, eLVDCMPSAR_IE_TypeDef SwitchIE)
{
    SysCtl_EnableWrite;
    CMPLVD_Clk_En;
    if (ch == CMP1_Channel)
    {
        CMP1_PD_PowOn;
        if (SwitchR600 == CMP_R600K_Disable)
        {
            PWD_CMP1R_Dis;
        }
        else
        {
            PWD_CMP1R_En;
        }

        BITBAND_ADDR((u32)(&SYSCTL->SYS_PD), 10) = SwitchHysen;

        if (SwitchIE == LVDCMPSAR_IE_Enable)
        {
            MADC->LVD_CTRL |= 0x00000040;/*"BIT6 CMP1IE"*/
        }
        else
        {
            MADC->LVD_CTRL &= (~0x00000040);/*"BIT6 CMP1IE"*/
        }
    }
    else
    {
        CMP2_PD_PowOn;
        if (SwitchR600 == CMP_R600K_Disable)
        {
            PWD_CMP2R_Dis;
        }
        else
        {
            PWD_CMP2R_En;
        }

        BITBAND_ADDR((u32)(&SYSCTL->SYS_PD), 11) = SwitchHysen;

        if (SwitchIE == LVDCMPSAR_IE_Enable)
        {
            MADC->LVD_CTRL |= 0x00000080;/*"BIT7 CMP2IE"*/
        }
        else
        {
            MADC->LVD_CTRL &= (~0x00000080);/*"BIT7 CMP2IE"*/
        }
    }

    if (SwitchIE == LVDCMPSAR_IE_Enable)
    {
        NVIC_EnableIRQ(CMP_IRQn);
    }
    else
    {
        NVIC_DisableIRQ(CMP_IRQn);
    }
}

/*********************************************************************************************************
** Function name:        fnCMP_Stop
** Descriptions:         �ر�CMPģ��
** input parameters:     ��
** output parameters:   ��
** Returned value:   ��
*********************************************************************************************************/
void Rn8xxx_CMP_Stop(eCMP_CH_TypeDef ch)
{
    SysCtl_EnableWrite;
    if (ch == CMP1_Channel)
    {
        CMP1_PD_PowDwn;
        PWD_CMP1R_Dis;
        HYSEN_CMP1_Dis;
        MADC->LVD_CTRL &= (~0x00000040);/*"BIT6 CMP1IE"*/
    }
    else
    {
        CMP2_PD_PowDwn;
        PWD_CMP2R_Dis;
        HYSEN_CMP2_Dis;
        MADC->LVD_CTRL &= (~0x00000080);/*"BIT7 CMP2IE"*/
    }
}

/*********************************************************************************************************
** Function name:        fnSarADC_Get
** Descriptions:         sarADC��ȡ����ֵ
** input parameters:     void
** output parameters:   ��
** Returned value:   u32 sar ADC����ֵ
*********************************************************************************************************/
u32 Rn8xxx_SarADC_Get(eSARCTL_CH_TypeDef ch, eSARCTL_PGA_TypeDef pga)
{
    u32  SAR_DAT;
    SysCtl_EnableWrite;
    CMPLVD_Clk_En;

    if (fnRegState_Detect((u32)(&MADC->AD_STAT), 1, 0, LvdCmpSar_TIMEOUT) == ERROR)
    {
        return 0;
    }

    MADC->AD_STAT = 0x01;/*"���ADC ת���������ɱ�־"*/

    if (ch == AIN6_Channel)
    {
        MADC->AD_CTRL = ((0 << 0) |     /*" SAR_CH"*/
                         (pga << 3) | /*" SAR-ADC �������"*/
                         (0l << 5) |  /*" SAR-ADC �жϿ���"*/
                         (11 << 6) |  /*" ѡ�� AIN6"*/
                         (0x0el << 7) | /*" SAR ADC �ڿ����󵽿�ʼ����ת����Ҫ�ȴ���ʱ��ѡ��457.5 ΢��"*/
                         (0x10l << 12)); /*" �ӿ��� REF ������ ADC ��Ҫ�ȴ���ʱ��"*/
    }
    else
    {
        MADC->AD_CTRL = ((ch << 0) |     /*" SAR_CH"*/
                         (pga << 3) | /*" SAR-ADC �������"*/
                         (0l << 5) |  /*" SAR-ADC �жϿ���"*/
                         (0l << 6) |  /*" SAR_CH ����"*/
                         (0x0el << 7) | /*" SAR ADC �ڿ����󵽿�ʼ����ת����Ҫ�ȴ���ʱ��ѡ��457.5 ΢��"*/
                         (0x10l << 12)); /*" �ӿ��� REF ������ ADC ��Ҫ�ȴ���ʱ��"*/
    }
    //----------����IO-----------------
    switch (ch)
    {
        case AIN0_Channel:
            GPIO->PCA0 &=  ~(0x3 << 0);
            GPIO->PCA0 |= BIT0;
            break;
        case AIN1_Channel:
            GPIO->PCA0 &=  ~(0x3 << 2);
            GPIO->PCA0 |= BIT2;
            break;
        case AIN2_Channel:
            GPIO->PCA0 |= BIT4;
            break;
        case AIN3_Channel:
            GPIO->PCA0 |= BIT5;
            break;
        case AIN4_Channel:
            GPIO->PCA0 |= BIT6;
            break;
        case AIN5_Channel:
            MADC->ANA_PAD |= BIT0;
            break;
        case AIN6_Channel:
            MADC->ANA_PAD |= BIT1;
            break;

        default:
            break;
    }

    MADC->AD_START = 0x01;/*"����һ�� SAR-ADC ����"*/

    if (fnRegState_Detect((u32)(&MADC->AD_STAT), 0, 1, LvdCmpSar_TIMEOUT) == SUCCESS)
    {
        MADC->AD_STAT = 0x01;/*"���ADC ת���������ɱ�־"*/
        SAR_DAT = MADC->AD_DATA;
        return (SAR_DAT);
    }
    else
    {
        return (0);
    }
}

/*********************************************************************************************************
** Function name:        Rn8xxx_LvdCmp_STAT
** Descriptions:         LvdCmp ״̬��־λ�ж�
** input parameters:      ch:ͨ��LVD/CMP1/CMP2 ;
**                  checkTime :���ʱ�䣬��λus
** output parameters:
** Returned value:   ״̬��־λ������ֵ�������ֵ:
**                           SUCCESS:������ֵ
**                           ERROR:������ֵ
*********************************************************************************************************/
u8 Rn8xxx_LvdCmp_STAT(eLVDCMP_CH_TypeDef ch, u32 checkTime)
{
    if (fnRegState_Detect((u32)(&MADC->LVD_STAT), ch, 1, checkTime) == SUCCESS)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/*********************************************************************************************************
** Function name:        Rn8xxx_LvdCmp_STAT
** Descriptions:         LvdCmp ״̬��־λ�ж�  ,
**               ֻҪ��һ�ε�����ֵ���ж�Ϊ���磬��ֹ�ϵ綶��
** input parameters:      ch:ͨ��LVD/CMP1/CMP2 ;
**                  checkTime :���ʱ�䣬��λus
** output parameters:
** Returned value:   ״̬��־λ������ֵ�������ֵ:
**                           SUCCESS:������ֵ
**                           ERROR:������ֵ
*********************************************************************************************************/
u8 Rn8xxx_LvdCmp_STATPowerUp(eLVDCMP_CH_TypeDef ch, u32 checkTime)
{
    if (fnRegState_Detect((u32)(&MADC->LVD_STAT), ch, 0, checkTime) == SUCCESS)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/*********************************************************************************************************
** Function name:        Rn8xxx_LvdCmpSar_Mode
** Descriptions:         SAR����ģʽ����
** input parameters:
**
** output parameters:
** Returned value:
*********************************************************************************************************/
void Rn8xxx_LvdCmpSar_Mode(eSAR_PerfMODE PerfMODE)
{
    if (SAR_HighMode == PerfMODE)
    {
        SAR_REG_ANA_PASSWD = 0x8E;
        SAR_REG_SAR_TEST = (0x00000002 << 15); /*"SARPS"*/
        SAR_REG_SAR_TEST = ((0x00000002 << 15) | /*"SARPS"*/
                            (0x00000002 << 13) | /*"F_SAR"*/
                            (0x00000001 << 12) | /*"SAR_MODE"*/
                            (0x00000001 << 10) | /*"dem_mode"*/
                            (0x0000000F << 6) | /*"ibsel_sar"*/
                            (0x00000001 << 11) | /*"IBIAS_MODE_H"*/
                            (0x00000003 << 4) | /*"IBIAS_MODE"*/
                            (0x00000001 << 3)); /*"DEM_EN"*/
        SAR_REG_ANA_CTL = 0x10000;/*"����дʹ��"*/
        SAR_REG_ANA_CTL = 0x1a8a8;
    }
    else
    {
        SAR_REG_ANA_PASSWD = 0x8E;
        SAR_REG_SAR_TEST = (0x00000002 << 15); /*"SARPS"*/
        SAR_REG_SAR_TEST = ((0x00000002 << 15) | /*"SARPS"*/
                            (0x00000002 << 13) | /*"F_SAR"*/
                            (0x00000001 << 12) | /*"SAR_MODE"*/
                            (0x00000000 << 10) | /*"dem_mode"*/
                            (0x0000000F << 6) | /*"ibsel_sar"*/
                            (0x00000001 << 11) | /*"IBIAS_MODE_H"*/
                            (0x00000001 << 4) | /*"IBIAS_MODE"*/
                            (0x00000001 << 3)); /*"DEM_EN"*/
        SAR_REG_ANA_CTL = 0x10000;/*"����дʹ��"*/
        SAR_REG_ANA_CTL = 0x10000;
    }
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
