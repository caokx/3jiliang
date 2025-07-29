/****************************************************************************
* @file     ISO7816.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.05.26
* @brief    ISO7816����
******************************************************************************
* @attention
*
*
****************************************************************************/
/* Includes ------------------------------------------------------------------*/

#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include <Rn8xxx_ISO7816.h>

/* Private define ------------------------------------------------------------*/
#define     ISO7816_Delay()         {__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}
#define     ISO7816_TIMEOUT 0xfff
/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/

/*********************************************************************************************************
** Function name:       ISO7816_SquareWave_Init
** Descriptions:        ��ʼ��7816ʱ�ӽ���������ź�
** input parameters:    SquareWaveClock ����Ƶ��(HZ)
** output parameters:       None
** Returned value:     None
*********************************************************************************************************/
void ISO7816_SquareWave_Init(uint32_t SquareWaveClock)
{
    SysCtl_EnableWrite;
    ISO7816_Clk_En;
    ISO7816->CTRL1 |= 1;
    ISO7816->CLK = ((1 << 3) | (SystemCoreClock / SquareWaveClock - 1));
}

/*********************************************************************************************************
** Function name:       fnISO7816_Init
** Descriptions:        ��ʼ��7816
** input parameters:    None
** output parameters:       None
** Returned value:     None
*********************************************************************************************************/

void ISO7816_Init(void)
{
    ISO7816->CTRL1 = 0x70000201;
    ISO7816->CTRL0 = 0x0800ea01;
    //ISO7816->CTRL0 = 0x0000ea01;
    ISO7816->STA0 = 0x3f;                   //clear status
    ISO7816->STA1 = 0x3f;                   //clear status
}

/*********************************************************************************************************
** Function name:       fnCardGetByte
** Descriptions:        �ӿ���ESAM����һ��8λ�ֽ�
** input parameters:    Data ΪҪ���յ�8λ����  ,CH ͨ��ѡ�� Rpt ���½��մ�?
** output parameters:       None
** Returned value:      ���ճɹ���ȴ�1��ETU���أ��Ӽ�⵽��ʼλ���ɹ�����ʱ������11��ETU
*********************************************************************************************************/
ErrorStatus ISO7816_ReadByte(eISO7816_ID_TypeDef id, u8 *Data)
{
    //  u16 Stamptemp;

    if (id == ISO7816_0ID)
    {
        ISO7816->CTRL0 &= 0xfffffffb;
        ISO7816->CTRL0 |= 0x08;
        ISO7816->STA0 = 0x3f;

        if (fnRegState_Detect((u32)(&ISO7816->STA0), 8, 1, ISO7816_TIMEOUT * 2) == ERROR)
        {
            ISO7816->STA0 = 0x3f;
            return ERROR;
        }

        if (ISO7816->STA0 & 0x10)
        {
            ISO7816->STA0 = 0x3f;           // clear err flag
            return ERROR;
        }
        *Data = ISO7816->DATA0;
        ISO7816->STA0 = 0x3f;
    }
    else
    {
        ISO7816->CTRL1 &= 0xfffffffb;
        ISO7816->CTRL1 |= 0x08;
        ISO7816->STA1 = 0x3f;

        if (fnRegState_Detect((u32)(&ISO7816->STA1), 8, 1, ISO7816_TIMEOUT * 2) == ERROR)
        {
            ISO7816->STA1 = 0x3f;
            return ERROR;
        }

        if (ISO7816->STA1 & 0x10)
        {
            ISO7816->STA1 = 0x3f;           // clear err flag
            return ERROR;
        }
        *Data = ISO7816->DATA1;
        ISO7816->STA1 = 0x3f;
    }
    return  SUCCESS;
}

/*********************************************************************************************************
** Function name:       fnCardSendByte
** Descriptions:           �򿨻�ESAM����һ��8λ�ֽ�
** input parameters:       c ΪҪ���͵�8λ����
** output parameters:       None
** Returned value:         0Ϊ��ȷ��1Ϊ����ȷ
*********************************************************************************************************/
ErrorStatus ISO7816_WriteByte(eISO7816_ID_TypeDef id, u8 Data)
{
    if (id == ISO7816_0ID)
    {
        ISO7816->CTRL0 &= 0xfffffff7;
        ISO7816->CTRL0 |= 0x04;
        ISO7816->STA0 = 0x3f;
        ISO7816->DATA0 = Data;
        if (fnRegState_Detect((u32)(&ISO7816->STA0), 6, 1, ISO7816_TIMEOUT * 2) == ERROR)
        {
            ISO7816->STA0 = 0x3f;
            return ERROR;
        }

        if ((ISO7816->STA0 & 0x20) || (ISO7816->STA0 & 0x08))       // �жϷ��ʹ����־
        {
            ISO7816->STA0 = 0x3f;           // clear err flag
            return ERROR;
        }
        ISO7816->STA0 = 0x3f;
    }
    else
    {
        ISO7816->CTRL1 &= 0xfffffff7;
        ISO7816->CTRL1 |= 0x04;
        ISO7816->STA1 = 0x3f;
        ISO7816->DATA1 = Data;

        if (fnRegState_Detect((u32)(&ISO7816->STA1), 6, 1, ISO7816_TIMEOUT * 2) == ERROR)
        {
            ISO7816->STA1 = 0x3f;
            return ERROR;
        }

        if ((ISO7816->STA1 & 0x20) || (ISO7816->STA1 & 0x08))       // �жϷ��ʹ����־
        {
            ISO7816->STA1 = 0x3f;           // clear err flag
            return ERROR;
        }
        ISO7816->STA1 = 0x3f;
    }
    return  SUCCESS;
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
