
#define  _DRIVE_DSP_GLOBALS
#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include <Rn8xxx_DSP.h>

u32 FftMathLibBuf[20];                      // 80�ֽ���ʱ��������fft����ʱ�м��������С��ʱ����ʹ��
/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_Init
** Descriptions:        FFTģ���ʼ��
** input parameters:    ���豸ģ��ʱ��
**
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_Init(void)
{
    SysCtl_EnableWrite;
    DSP_Clk_En;
    SysCtl_DisableWrite;
    return SUCCESS;
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_Int2Fp
** Descriptions:       ADC��������ת���ɵ����ȸ�������ʽ
** input parameters:    Dst:ת�������ݴ洢Ŀ���ַ
**                      Src:ת������Դ��ַ
**                      Len: ���ݳ��ȣ�Ϊ4��������
**                      Div: ����ת������ʱ����2^Div
**                           0: 32bit data   1: 24bit data 2: 16bit data 3: 8bit data
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_Int2Fp(u32 Dst, u32 Src, u16 Len, u8 Div, u8 DataMode)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_DMA_MODE;
    MacCtl0Para.CTL0_I2F_DIV_CFG = Div;

    switch (DataMode)
    {
        case  0:
            MacCtl0Para.I2F_PRE_EN = I2F_PRE_32BIT;
            break;

        case  1:
            MacCtl0Para.I2F_PRE_EN = I2F_PRE_24BIT;
            break;
        case  2:
            MacCtl0Para.I2F_PRE_EN = I2F_PRE_16BIT;
            break;

        case  3:
            MacCtl0Para.I2F_PRE_EN = I2F_PRE_8BIT;
            break;

        default:
            break;
    }

    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->FFT_FLG = 0x02;
    DSP->DMA_SRBADR = ((u32)Src & 0x1ffff) / 4;
    DSP->DMA_TRBADR = ((u32)Dst & 0x1ffff) / 4;
    DSP->DMA_LEN = Len - 1;

    DSP->MAC_CTL2 = MAC_CTL_DMA_EN;
    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 1, 1, FFT_I2F_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }
    else
    {
        DSP->FFT_FLG = 0x02;
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_U16I2Fp
** Descriptions:        16λ��������ת���ɵ����ȸ�������ʽ
** input parameters:    Dst:ת�������ݴ洢Ŀ���ַ
**                      Src:ת������Դ��ַ
**                      Len: ���ݳ��ȣ�Ϊ4��������
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
void Rn8xxx_DSP_U16I2Fp(u32 *Dst, u16 *Src, u16 Len)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u16 i;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    for (i = 0; i < Len; i++)
    {
        DSP->MAC_IN0 = Src[i];
        Dst[i] = DSP->MAC_OUT0;
    }
    return;
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_Fp2Int
** Descriptions:        �����ȸ�������ʽת��������
** input parameters:    Dst:ת�������ݴ洢Ŀ���ַ
**                      Src:ת������Դ��ַ
**                      Len: ���ݳ��ȣ�Ϊ4��������
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_Fp2Int(u32 Dst, u32 Src, u8 Mul, u16 Len)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = F2I_DMA_MODE;
    MacCtl0Para.CTL0_F2I_MUL_CFG = Mul;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    DSP->FFT_FLG = 0x10;
    DSP->DMA_SRBADR = ((u32)Src & 0x1ffff) / 4;
    DSP->DMA_TRBADR = ((u32)Dst & 0x1ffff) / 4;
    DSP->DMA_LEN = Len - 1;

    DSP->MAC_CTL2 = MAC_CTL_DMA_EN;
    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 4, 1, FFT_I2F_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }
    else
    {
        DSP->FFT_FLG = 0x10;
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_BitReverse
** Descriptions:        ����bit Reverse
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_BitReverse(u32 Dst, u32 Src, u16 Len)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = BIT_RVE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->DMA_SRBADR = (Src & 0x1ffff) / 4;
    DSP->DMA_TRBADR = (Dst & 0x1ffff) / 4;
    DSP->DMA_LEN = Len - 1;
    DSP->FFT_FLG = 0x100;
    DSP->MAC_CTL2 = MAC_CTL_DMA_EN;
    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 8, 1, FFT_BitRev_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }
    else
    {
        DSP->FFT_FLG = 0x100;
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_FFT
** Descriptions:        ����FFTת�������е�������
** input parameters:    SrbAddr:����ʵ����ַ
**                      SibAddr�������鲿��ַ
**                      PrbAddr�����cosֵ��ַ
**                      PibAddr�����sinֵ��ַ
**                      Len�����ݳ���
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_FFT(u32 SrbAddr, u32 SibAddr, u32 PrbAddr, u32 PibAddr, u16 Len)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = FFT_MODE;
    if (PrbAddr == 0)
    {
        MacCtl0Para.CTL0_TB_FFT_EN = TB_EN_EN;
    }
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->DMA_SRBADR = (SrbAddr & 0x1ffff) / 4;
    DSP->DMA_SIBADR = (SibAddr & 0x1ffff) / 4;

    DSP->DMA_TRBADR = DSP->DMA_SRBADR;      // Ŀ���ַ��Դ��ַʹ��ͬһ��ַ����ʡRAM�ռ�
    DSP->DMA_TIBADR = DSP->DMA_SIBADR;
    DSP->DMA_PRBADR = (PrbAddr & 0x1ffff) / 4;
    DSP->DMA_PIBADR = (PibAddr & 0x1ffff) / 4;

    DSP->DMA_LEN = Len - 1;
    DSP->FFT_FLG = 0x80;
    DSP->MAC_CTL2 = MAC_CTL_DMA_EN;
    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 7, 1, FFT_FFT_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }
    else
    {
        DSP->FFT_FLG = 0x80;
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_FpSqrt
** Descriptions:        �������������������м���
** input parameters:    X_In:��������ʵ��
**                      Y_In�����������鲿
**                      Amp_Out�����sqrtֵ
**                      Arctan_Out��Y/X������ֵ
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_FpSqrt(u32 *X_In, u32 *Y_In, u32 *Amp_Out, u32 *Arctan_Out)
{
    DSP->CRD_XIN = *X_In;
    DSP->CRD_YIN = *Y_In;
    DSP->CRD_ANGLE = 0;
    DSP->CRD_FLG = 0x01;
    DSP->CRD_CTL = 0x1;
    if (fnRegState_Detect((u32)(&DSP->CRD_FLG), 0, 1, FFT_FFT_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }
    else
    {
        DSP->CRD_FLG = 0x01;
        *Amp_Out = DSP->CRD_AMP;
        if (*X_In & 0x80000000)
        {
            *Arctan_Out = (DSP->CRD_PHASE +  0x80000000);
        }
        else
        {
            *Arctan_Out = DSP->CRD_PHASE;
        }
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       fnFFT_FpMult
** Descriptions:        �������˷�
** input parameters:    In0:��������0
**                      In1:��������1
**                      Out:����������
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus fnFFT_FpMult(u32 In0, u32 In1, u32 *Out)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;        // ����Ϊ����ģʽ
    MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;      // ���Ϊ����ģʽ
    MacCtl0Para.I2F_PRE_EN = I2F_PRE_24BIT;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->FFT_FLG = 0x01;
    DSP->MAC_IN0 = In0;
    DSP->MAC_IN1 = In1;
    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 0, 1, FFT_FFT_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }
    else
    {
        DSP->FFT_FLG = 0x01;
        *Out = DSP->MAC_OUT0;
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       fnFFT_FpAdd
** Descriptions:        �������ӷ�
** input parameters:    In0:��������0
**                      In1:��������1
**                      Out:����������
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus fnFFT_FpAdd(u32 In0, u32 In1, u32 *Out)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_ADD_MODE;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->FFT_FLG = 0x01;
    DSP->MAC_IN0 = In0;
    DSP->MAC_IN1 = In1;
    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 0, 1, FFT_FFT_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }
    else
    {
        DSP->FFT_FLG = 0x01;
        *Out = DSP->MAC_OUT0;
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       fnFFT_FpSub
** Descriptions:        ����������
** input parameters:    In0:��������0
**                      In1:��������1
**                      Out:����������
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus fnFFT_FpSub(u32 In0, u32 In1, u32 *Out)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_SUB_MODE;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->FFT_FLG = 0x01;
    DSP->MAC_IN0 = In0;
    DSP->MAC_IN1 = In1;
    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 0, 1, FFT_FFT_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }
    else
    {
        DSP->FFT_FLG = 0x01;
        *Out = DSP->MAC_OUT0;
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_Sin_Cos
** Descriptions:        ��תģʽ:Arctan(y/x) *2^31/pi
** input parameters:    In0:��������, ����Ĵ��������壺(Angle/180)*2^31   AngleΪ�Ƕ�ֵ��λ����
**                      CosOut  �������Ϊ cos(Angle)*2^29/(2*PI)
**                      SinOut  �������Ϊ sin(Angle)*2^29/(2*PI)
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_Sin_Cos(u32 In0, u32 *CosOut, u32 *SinOut)
{
    DSP->CRD_ANGLE = In0;
    DSP->CRD_CTL = 0x02;     // ʹ����תģʽ
    if (fnRegState_Detect((u32)(&DSP->CRD_FLG), 1, 1, FFT_FFT_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }
    else
    {
        DSP->CRD_FLG = 0x02;
        *CosOut = DSP->CRD_COS;
        *SinOut = DSP->CRD_SIN;
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_IntDiv
** Descriptions:        ����������
** input parameters:    In0:������
**                      In1:����
**                      Out:����������
**                      Mul_N:�Ŵ���
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_IntDiv(u32 In0, u32 In1, u32 *Out, u16 Mul_N)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u8 i;

    DSP->MAC_CTL0 = 0;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = In1;
    DSP->DIV_IN1 = DSP->MAC_OUT0;
    DSP->MAC_IN0 = In0;
    DSP->DIV_IN0 = DSP->MAC_OUT0;
    DSP->FFT_FLG = 0x04;
    // ��������
    DSP->MAC_CTL2 = DIV_KICK_EN;

    for (i = 0; i < 200; i++)
    {
        if (DSP->FFT_FLG & 0x04)
        {
            DSP->FFT_FLG = 0x04;
            *Out = DSP->DIV_OUT0;
            break;
        }
    }
    if (i >= 200)
    {
        return (ERROR);
    }

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = *Out;

    *Out = DSP->MAC_OUT0;
    return (SUCCESS);
}

/*********************************************************************************************************
** Function name:       fnFFT_FlDiv
** Descriptions:        ����������
** input parameters:    In0:������
**                      In1:����
**                      Out:����������
**                      Mul_N:�Ŵ���
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
#ifdef USE_IAR
#pragma inline
ErrorStatus fnFFT_FlDiv(u32 In0, u32 In1, u32 *Out)
#else
__inline ErrorStatus fnFFT_FlDiv(u32 In0, u32 In1, u32 *Out)
#endif
{
    u16 i;
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->DIV_IN1 = In1;
    DSP->DIV_IN0 = In0;
    DSP->FFT_FLG = 0x04;
    // ��������
    DSP->MAC_CTL2 = DIV_KICK_EN;

    for (i = 0; i < 300; i++)
    {
        if (DSP->FFT_FLG & 0x04)
        {
            DSP->FFT_FLG = 0x04;
            *Out = DSP->DIV_OUT0;
            return (SUCCESS);
        }
    }
    return (ERROR);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_FIR
** Descriptions:        FIR����
** input parameters:    InData:��������ָ��,����ǰ10��������
**                      OutData:��ֵ������ָ��
**                      InLen:�������ݳ���
**                      OutLen:������ݳ���
**                                InData  ��OutData����ʹ��ͬһ����ַ,��������ת���������
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_FIR(u32 *InData, u32 *OutData, u32 *ParaDtat, u16 InLen, u8 FirOrder)
{
    DSP->FFT_FLG = DSP->FFT_FLG;
    DSP->MAC_CTL2 = 0;
    DSP->MAC_CTL0 = 15;
    DSP->MAC_CTL1 = (FirOrder << 4);        // ����FIR����������
    DSP->DMA_SRBADR = (uint32_t)((uint32_t*)InData) >> 2;
    DSP->DMA_TRBADR = (uint32_t)((uint32_t*)OutData) >> 2;
    DSP->DMA_PRBADR = (uint32_t)((uint32_t*)ParaDtat) >> 2;
    DSP->DMA_LEN = InLen - 1;

    DSP->MAC_CTL2 = (1 << 0);

    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 12, 1, FFT_FFT_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }

    DSP->FFT_FLG = DSP->FFT_FLG;

    return (SUCCESS);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_HWCalc_4Wave
** Descriptions:        �벨��Чֵ����
** input parameters:    InData:����2�ܲ�128������
**                      OutData:�벨��Чֵ��ƽ����ֵ������õ���ʵ�벨���迪����
**
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_HWCalc(u32 *InData, u32 *OutData, u32 *LastHwData)
{
    u8 i;
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u32 HwDatatemp;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MLAD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    DSP->MAC_OUT0 = 0;
    for (i = 0; i < 32; i++)
    {
        DSP->MAC_IN0 = InData[i];
        DSP->MAC_IN1 = InData[i];
        DSP->MAC_IN2 = DSP->MAC_OUT0;
    }
    HwDatatemp = DSP->MAC_OUT0;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = 0x3F800000;              // *1+lasthwdata
    DSP->MAC_IN2 = *LastHwData;

    DSP->MAC_IN0 = DSP->MAC_OUT0;          // *1/64
    DSP->MAC_IN1 = 0x3c800000;
    DSP->MAC_IN2 = 0;
    OutData[0] = DSP->MAC_OUT0;
    *LastHwData = HwDatatemp;

    DSP->MAC_OUT0 = 0;
    for (; i < 64; i++)
    {
        DSP->MAC_IN0 = InData[i];
        DSP->MAC_IN1 = InData[i];
        DSP->MAC_IN2 = DSP->MAC_OUT0;
    }
    HwDatatemp = DSP->MAC_OUT0;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = 0x3F800000;              // *1+lasthwdata
    DSP->MAC_IN2 = *LastHwData;

    DSP->MAC_IN0 = DSP->MAC_OUT0;          // *1/64
    DSP->MAC_IN1 = 0x3c800000;
    DSP->MAC_IN2 = 0;
    OutData[1] = DSP->MAC_OUT0;
    *LastHwData = HwDatatemp;

    DSP->MAC_OUT0 = 0;
    for (; i < 96; i++)
    {
        DSP->MAC_IN0 = InData[i];
        DSP->MAC_IN1 = InData[i];
        DSP->MAC_IN2 = DSP->MAC_OUT0;
    }
    HwDatatemp = DSP->MAC_OUT0;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = 0x3F800000;              // *1+lasthwdata
    DSP->MAC_IN2 = *LastHwData;

    DSP->MAC_IN0 = DSP->MAC_OUT0;          // *1/64
    DSP->MAC_IN1 = 0x3c800000;
    DSP->MAC_IN2 = 0;
    OutData[2] = DSP->MAC_OUT0;
    *LastHwData = HwDatatemp;

    DSP->MAC_OUT0 = 0;
    for (; i < 128; i++)
    {
        DSP->MAC_IN0 = InData[i];
        DSP->MAC_IN1 = InData[i];
        DSP->MAC_IN2 = DSP->MAC_OUT0;
    }
    HwDatatemp = DSP->MAC_OUT0;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = 0x3F800000;              // *1+lasthwdata
    DSP->MAC_IN2 = *LastHwData;

    DSP->MAC_IN0 = DSP->MAC_OUT0;          // *1/64
    DSP->MAC_IN1 = 0x3c800000;
    DSP->MAC_IN2 = 0;
    OutData[3] = DSP->MAC_OUT0;
    *LastHwData = HwDatatemp;
    // ����ת����
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = OutData[0];
    OutData[0] = DSP->MAC_OUT0;
    DSP->MAC_IN0 = OutData[1];
    OutData[1] = DSP->MAC_OUT0;
    DSP->MAC_IN0 = OutData[2];
    OutData[2] = DSP->MAC_OUT0;
    DSP->MAC_IN0 = OutData[3];
    OutData[3] = DSP->MAC_OUT0;
    return (SUCCESS);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_HWCalc_2Wave
** Descriptions:        �벨��Чֵ����
** input parameters:    InData:����1�ܲ�64���128������
**                      OutData:�벨��Чֵ��ƽ����ֵ������õ���ʵ�벨���迪����
**                      Flag: 0: 1�ܲ�64������   1:1�ܲ�128������
**
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_HWCalc_2Wave(u32 *InData, u32 *OutData, u32 *LastHwData, u8 PointFlag)
{
    u8 i, j, k;
    u8 tstep;
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u32 HwDatatemp;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MLAD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    if (PointFlag)
    {
        // 128��1�ܲ�
        j = 64;
        k = 128;
        tstep = 2;
    }
    else
    {
        // 64��1�ܲ�
        j = 32;
        k = 64;
        tstep = 1;
    }
    DSP->MAC_OUT0 = 0;
    for (i = 0; i < j; i += tstep)
    {
        DSP->MAC_IN0 = InData[i];
        DSP->MAC_IN1 = InData[i];
        DSP->MAC_IN2 = DSP->MAC_OUT0;
    }
    HwDatatemp = DSP->MAC_OUT0;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = 0x3F800000;              // *1+lasthwdata
    DSP->MAC_IN2 = *LastHwData;

    DSP->MAC_IN0 = DSP->MAC_OUT0;          // *1/64/128/128
    DSP->MAC_IN1 = 0x35800000;
    DSP->MAC_IN2 = 0;
    OutData[0] = DSP->MAC_OUT0;
    *LastHwData = HwDatatemp;

    DSP->MAC_OUT0 = 0;
    for (; i < k; i += tstep)
    {
        DSP->MAC_IN0 = InData[i];
        DSP->MAC_IN1 = InData[i];
        DSP->MAC_IN2 = DSP->MAC_OUT0;
    }
    HwDatatemp = DSP->MAC_OUT0;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = 0x3F800000;              // *1+lasthwdata
    DSP->MAC_IN2 = *LastHwData;

    DSP->MAC_IN0 = DSP->MAC_OUT0;          // *1/64/128/128
    DSP->MAC_IN1 = 0x35800000;
    DSP->MAC_IN2 = 0;
    OutData[1] = DSP->MAC_OUT0;
    *LastHwData = HwDatatemp;

    // ����ת����
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = OutData[0];
    OutData[0] = DSP->MAC_OUT0;
    DSP->MAC_IN0 = OutData[1];
    OutData[1] = DSP->MAC_OUT0;
    return (SUCCESS);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_fBaseCalc
** Descriptions:        ����ֵ����
** input parameters:    InData: �������ֵ��Ϊ���������ڿ����ź����
**                      OutData_F:����ֵ��������
**                      OutData_Int:����ֵ��������
**                      FWaveData:ǰ4�λ���ֵ�ͣ��뵱ǰֵ�ۼӺ���ƽ��ֵ
**
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_fBaseCalc(u32 *InData, u32 *OutData_F, u32 KMlu, u8 AveFlag)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u32 fBaseTemp;
    // ת�ɸ��㵥Ԫ
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    MacCtl0Para.CTL0_I2F_DIV_CFG = 0;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = *InData;
    fBaseTemp = DSP->MAC_OUT0;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;
    MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    DSP->MAC_IN0 = fBaseTemp;
    DSP->MAC_IN1 = 0x3F5BD95D;              // ��ֵ����4*P=4*0.607253 Ϊ����г����Чֵ���2*sqrt(2),��ֵΪ 4*P/(2*sqrt(2)) = 2*0.607253/1.414
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = KMlu;

    if (AveFlag)
    {
        // ��5��ƽ���������ݳ�0.2
        DSP->MAC_IN0 = DSP->MAC_OUT0;
        DSP->MAC_IN1 = 0x3E4CCCCD;      // 0.2
    }
    fBaseTemp = DSP->MAC_OUT0;
    DSP->FFT_FLG = 0x200;

    *OutData_F = fBaseTemp;
    return (SUCCESS);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_Lagrange
** Descriptions:        �������ղ�ֵ
** input parameters:    InData:��������ָ��
**                      OutData:��ֵ������ָ��
**                      InLen:�������ݳ���
**                      OutLen:������ݳ���
**                            ��ֵǰInData�Ͳ�ֵ��OutData����ʹ��ͬһ����ַ,��������ת���������
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_Lagrange(u32 *InData, u32 *OutData, u16 InLen, u16 OutLen, u32 LastData, u16 Frequency)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u8 i;
    u32 f_step ;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    DSP->MAC_IN0 = Frequency;  //f,Ƶ�ʣ�2λС��
    f_step = DSP->MAC_OUT0;

    DSP->MAC_IN0 = OutLen;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;
    MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->FFT_FLG = 0x200;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = f_step;

    // ���� Step = 3579545/2/128/(Frequency*OutLen)
    DSP->MAC_CTL0 = 0;
    DSP->DIV_IN0 = 0x49AAAF9E;     //0x49AAAF9EΪ100*3579545/2/128������,Frequency�Ŵ�100
    DSP->DIV_IN1 = DSP->MAC_OUT0;
    DSP->FFT_FLG = 0x04;
    // ��������
    DSP->MAC_CTL2 = DIV_KICK_EN;

    for (i = 0; i < 200; i++)
    {
        if (DSP->FFT_FLG & 0x04)
        {
            DSP->FFT_FLG = 0x04;
            f_step = DSP->DIV_OUT0;
            break;
        }
    }
    if (i >= 200)
    {
        return (ERROR);
    }

    // �����ӷ� INTP_LOC = f_step + 1
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = FP_ADD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    DSP->MAC_IN0 = f_step;
    DSP->MAC_IN1 = 0x3F800000;      // +1
    DSP->INTP_LOC = DSP->MAC_OUT0;

    DSP->FFT_FLG = DSP->FFT_FLG;
    DSP->MAC_CTL2 = 0;
    DSP->MAC_CTL0 = 17;
    DSP->MAC_CTL1 = 0x01;     //��ֵģʽʹ�������ڵ����һ�����ݣ�ʹ���ź�
    DSP->INTP_LEN = InLen;
    DSP->DMA_LEN = OutLen - 1;

    DSP->INTP_STEP = f_step;
    DSP->MAC_IN5 = LastData;  //��һ��ֵ

    DSP->DMA_SRBADR = (uint32_t)((uint32_t*)InData) >> 2;
    DSP->DMA_TRBADR = (uint32_t)((uint32_t*)OutData) >> 2;

    DSP->MAC_CTL2 = (1 << 0); //����

    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 14, 1, FFT_FFT_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }

    DSP->FFT_FLG = DSP->FFT_FLG;

    LastData = *(OutData + OutLen - 1); //������һ��ֵ

    return (SUCCESS);
}

/*
 ErrorStatus Rn8xxx_DSP_Lagrange(u32 *InData , u32 *OutData , u16 InLen , u16 *OutLen , u32 LastData, u16 Frequency , u32 *Lag_t)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u8 i;
    u32 f_step ,InLen_F , datatemp;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    DSP->MAC_IN0 = Frequency;  //f,Ƶ�ʣ�2λС��
    f_step = DSP->MAC_OUT0;

    DSP->MAC_IN0 = InLen ;  //
    InLen_F = DSP->MAC_OUT0;

    // ���� Step = 3579545/2/128/(Frequency*256) = 54.61952209/Frequency
    DSP->MAC_CTL0 = 0;
    DSP->DIV_IN0 = 0x45AAAF9E;     //0x45AAAF9EΪ54.61952209*100������,Frequency�Ŵ�100
    DSP->DIV_IN1 = f_step;
    DSP->FFT_FLG = 0x04;
    // ��������
    DSP->MAC_CTL2 = DIV_KICK_EN;

    for(i=0;i<200;i++)
    {
        if(DSP->FFT_FLG&0x04)
        {
            DSP->FFT_FLG = 0x04;
            f_step = DSP->DIV_OUT0;
            break;
        }
    }
    if(i >= 200) return(ERROR);

    if(*Lag_t == 0)
    {
        //------*Lag_t=0x438D0BD3----
        //------��ʼt=InLen_F + 1+f_step-------------------
        MacCtl0Para.gMACCTL0 = 0;
        MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
        MacCtl0Para.CTL0_MODE_SEL = FP_ADD_MODE;
        DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

        DSP->MAC_IN0 = f_step;
        DSP->MAC_IN1 = 0x3F800000;
        DSP->INTP_LOC = DSP->MAC_OUT0;   //INTP_LOC = f_step + 1

        DSP->MAC_IN0 = DSP->MAC_OUT0;
        DSP->MAC_IN1 = InLen_F;    //+InLen_F
        *Lag_t = DSP->MAC_OUT0;   //t = f_step + 1 + Inlen
    }
    else
    {
        MacCtl0Para.gMACCTL0 = 0;
        MacCtl0Para.CTL0_MODE_SEL = FP_SUB_MODE;
        MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
        DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
        DSP->FFT_FLG = 0x01;
        DSP->MAC_IN0 = *Lag_t;
        DSP->MAC_IN1 = InLen_F;
        DSP->INTP_LOC = DSP->MAC_OUT0;
    }

    //------OutLen=(2*InLen+1+step-t)/step---------------
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MLAD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    DSP->MAC_OUT0 = 0;
    DSP->MAC_IN0 = InLen_F;
    DSP->MAC_IN1 = 0x40000000;  //---0x40000000Ϊ2�ĸ�����
    DSP->MAC_IN2 = 0x3F800000;   //----+1---
    datatemp = DSP->MAC_OUT0;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = FP_ADD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = datatemp;
    DSP->MAC_IN1 = f_step;    //+step
    datatemp = DSP->MAC_OUT0;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_SUB_MODE;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->FFT_FLG = 0x01;
    DSP->MAC_IN0 = datatemp;
    DSP->MAC_IN1 = *Lag_t;    //----   -t  ----
    datatemp = DSP->MAC_OUT0;

    DSP->MAC_CTL0 = 0;
    DSP->DIV_IN0 = datatemp;
    DSP->DIV_IN1 = f_step;
    DSP->FFT_FLG = 0x04;
    // ��������
    DSP->MAC_CTL2 = DIV_KICK_EN;

    for(i=0;i<200;i++)
    {
        if(DSP->FFT_FLG&0x04)
        {
            DSP->FFT_FLG = 0x04;
            //-------*OutLen = DSP->DIV_OUT0;  -----
            datatemp = DSP->DIV_OUT0;
            break;
        }
    }
    if(i >= 200) return(ERROR);

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_ZERO;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    DSP->MAC_IN0 = datatemp;  //
    *OutLen = DSP->MAC_OUT0;

    DSP->FFT_FLG=DSP->FFT_FLG;
    DSP->MAC_CTL2 = 0;
    DSP->MAC_CTL0=17;
    DSP->MAC_CTL1=0x01;       //��ֵģʽʹ�������ڵ����һ�����ݣ�ʹ���ź�
    DSP->INTP_LEN=InLen;
    DSP->DMA_LEN=*OutLen-1;

    DSP->INTP_STEP= f_step;
    DSP->MAC_IN5 = LastData;  //��һ��ֵ

    DSP->DMA_SRBADR=(uint32_t)((uint32_t*)InData)>>2;
    DSP->DMA_TRBADR=(uint32_t)((uint32_t*)OutData)>>2;

    DSP->MAC_CTL2=(1<<0);   //����

    if(fnRegState_Detect((u32)(&DSP->FFT_FLG) , 14 , 1 ,FFT_FFT_TimeOut) == ERROR) return(ERROR);//�ȴ�ת�����

    DSP->FFT_FLG=DSP->FFT_FLG;

    //LastData = *(OutData + *OutLen-1);  //������һ��ֵ

    *Lag_t = DSP->INTP_LOC;

    return(SUCCESS);
}
*/
/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_HPercent
** Descriptions:        ����������,���ڼ������г������Чֵ������
** input parameters:    HPercent:�ṹ�����ݣ������г����������Чֵ���
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
/*ErrorStatus Rn8xxx_DSP_HPercent(sFftMath_Percent_TypeDef *HPercent)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    FFT->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    FFT->MAC_IN0 = HPercent->fBase_Int;
    FFT->DIV_IN1 = FFT->MAC_OUT0;
    FFT->MAC_IN0 = HPercent->ftemp_Int;
    FFT->DIV_IN0 = FFT->MAC_OUT0;
    HPercent->HRms = FFT->MAC_OUT0;
    FFT->FFT_FLG = 0x04;
    // ��������
    FFT->MAC_CTL1 = DIV_KICK_EN;
    if(fnRegState_Detect((u32)(&FFT->FFT_FLG) , 2 , 1 ,FFT_I2F_TimeOut) == ERROR) return(ERROR);//�ȴ�ת�����
    else
    {
        FFT->FFT_FLG = 0x04;
        HPercent->Hpercent = FFT->DIV_OUT0;
        // �����˷���������ĺ�������10000�ķŴ���
        FFT->MAC_IN0 = HPercent->nMul;
        MacCtl0Para.gMACCTL0 = 0;
        MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;
        MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;
        MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
        FFT->MAC_CTL0 = MacCtl0Para.gMACCTL0;
        FFT->FFT_FLG = 0x200;
        FFT->MAC_IN0 = FFT->MAC_OUT0;
        FFT->MAC_IN1 = HPercent->Hpercent;
        {
            FFT->FFT_FLG = 0x200;
            HPercent->Hpercent = FFT->MAC_OUT0;
            //�����˷�������г��������ֵ
            FFT->FFT_FLG = 0x200;
            FFT->MAC_IN0 = HPercent->HRms;
            FFT->MAC_IN1 = 0x3F5BD95D;              // ��ֵ����4*P=4*0.607253 Ϊ����г����Чֵ���2*sqrt(2),��ֵΪ 4*P/(2*sqrt(2)) = 2*0.607253/1.414
            {
                FFT->FFT_FLG = 0x200;
                HPercent->HRms = FFT->MAC_OUT0;
                MacCtl0Para.gMACCTL0 = 0;
                MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
                MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
                FFT->MAC_CTL0 = MacCtl0Para.gMACCTL0;
                FFT->MAC_IN0 = HPercent->Hpercent;
                HPercent->Hpercent = FFT->MAC_OUT0;

                FFT->MAC_IN0 = HPercent->HRms;
                HPercent->HRms = FFT->MAC_OUT0;
                return(SUCCESS);
            }
        }
    }
}*/
// ʹ��EMU������Чֵ����г����Чֵ
ErrorStatus Rn8xxx_DSP_HPercent(sFftMath_Percent_TypeDef *HPercent)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u32 PercentTemp;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    DSP->MAC_IN0 = HPercent->fBase_Int;
    DSP->DIV_IN1 = DSP->MAC_OUT0;
    DSP->MAC_IN0 = HPercent->ftemp_Int;
    DSP->DIV_IN0 = DSP->MAC_OUT0;

    DSP->FFT_FLG = 0x04;
    // ��������
    DSP->MAC_CTL2 = DIV_KICK_EN;
    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 2, 1, FFT_I2F_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }
    else
    {
        DSP->FFT_FLG = 0x04;
        HPercent->Hpercent = DSP->DIV_OUT0;
        // �����˷�
        //FFT->MAC_IN0 = HPercent->nMul;
        MacCtl0Para.gMACCTL0 = 0;
        MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;
        MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;
        MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
        DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
        DSP->FFT_FLG = 0x200;
        DSP->MAC_IN0 = HPercent->nMul;
        DSP->MAC_IN1 = HPercent->Hpercent;
        {
            DSP->FFT_FLG = 0x200;
            PercentTemp = DSP->MAC_OUT0;
            // ������ĺ�������10000�ķŴ���
            DSP->MAC_IN0 = DSP->MAC_OUT0;
            DSP->MAC_IN1 = 0x461C4000;                      // 10000�ĸ�������ʾ
            HPercent->Hpercent = DSP->MAC_OUT0;
            DSP->FFT_FLG = 0x200;
            //�����˷�������г��������ֵ
            DSP->MAC_IN0 = HPercent->EmuReg_Base;               // ��EMU������Чֵת�ɸ�����
            DSP->MAC_IN1 = PercentTemp;
            {
                DSP->FFT_FLG = 0x200;
                HPercent->HRms = DSP->MAC_OUT0;

                MacCtl0Para.gMACCTL0 = 0;
                MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;           // ����ת������
                MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
                DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
                DSP->MAC_IN0 = HPercent->Hpercent;
                HPercent->Hpercent = DSP->MAC_OUT0;

                DSP->MAC_IN0 = HPercent->HRms;
                HPercent->HRms = DSP->MAC_OUT0;
                return (SUCCESS);
            }
        }
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_InterHPercent
** Descriptions:        ����������,���ڼ����г������
** input parameters:    HPercent:�ṹ�����ݣ�����ļ�г������
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
//#ifdef USE_IAR
//#pragma inline
ErrorStatus Rn8xxx_DSP_InterHPercent(sFftMath_InterPercent_TypeDef *HPercent)
//#else
//__inline ErrorStatus Rn8xxx_DSP_InterHPercent(sFftMath_InterPercent_TypeDef *HPercent)
//#endif
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    DSP->MAC_IN0 = HPercent->fBase_Int;
    DSP->DIV_IN1 = DSP->MAC_OUT0;
    DSP->MAC_IN0 = HPercent->ftemp_Int;
    DSP->DIV_IN0 = DSP->MAC_OUT0;

    DSP->FFT_FLG = 0x04;
    // ��������
    DSP->MAC_CTL1 = DIV_KICK_EN;
    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 2, 1, FFT_I2F_TimeOut) == ERROR)
    {
        return (ERROR);    //�ȴ�ת�����
    }
    else
    {
        DSP->FFT_FLG = 0x04;
        HPercent->Hpercent = DSP->DIV_OUT0;
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_Isgrp
** Descriptions:        ���ڼ��                     1�����ã��˲���ϵ��������ϵ���Ŵ�10000��
** output parameters:   NONE
** Returned value:      SUCCES��г�����麬��
** input parameters:    HPercent:�ṹ�����ݣ������г����Ⱥ����
**                      ��5hzΪ��λ��10�κ��������ܵļ�г��Ⱥ����
**                      FftCoret: ��г������ϵ����ϵ��*10000���Դ˴ﵽ������ĺ���Ϊxx.xx%
**                      Mode: ����ģʽ�Ƿ����ã�0�������ã�ֱ�ӳ�10000�̶�ֵ
**                                              1�����ã��˲���ϵ��������ϵ���Ŵ�10000��
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
//#ifdef USE_IAR
//#pragma inline
ErrorStatus Rn8xxx_DSP_Isgrp(sFftMath_InterPercent_TypeDef *HPercent,  u32 *FftCoret, u8 Mode)
//#else
//__inline ErrorStatus Rn8xxx_DSP_Isgrp(sFftMath_InterPercent_TypeDef *HPercent , u32 *FftCoret , u8 Mode)
//#endif
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u32 Isgrp;
    u8 i;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;
    MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->FFT_FLG = 0x200;
    for (i = 1; i < 10; i++)
    {
        DSP->MAC_IN0 = HPercent->tPercent[i];
        if (Mode)
        {
            DSP->MAC_IN1 = FftCoret[i];
        }
        else
        {
            DSP->MAC_IN1 = 0x461C4000;    // 0x461C4000Ϊ10000�ĸ�������ʾ
        }
        HPercent->tPercent[i] = DSP->MAC_OUT0;
        DSP->MAC_IN0 = HPercent->tPercent[i];
        DSP->MAC_IN1 = HPercent->tPercent[i];
        HPercent->tPercent[i] = DSP->MAC_OUT0;
    }
    // �����ӷ�
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = FP_ADD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    Isgrp = HPercent->tPercent[1];
    for (i = 2; i < 10; i++)
    {
        DSP->MAC_IN0 = HPercent->tPercent[i];
        DSP->MAC_IN1 = Isgrp;
        Isgrp = DSP->MAC_OUT0;
    }
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = Isgrp;
    Isgrp = DSP->MAC_OUT0;
    Isgrp = (u32)sqrt(Isgrp);
    HPercent->Hpercent = Isgrp;
    return SUCCESS;
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_CalcThd
** Descriptions:        ����г���ܺ�����
** input parameters:    Src:����г��������  Num:����г���ܴ���
**                      Dst:��ʱ�������洢������ת���㼰�Գ˺��ֵ
** output parameters:   NONE
** Returned value:      THD
*********************************************************************************************************/
u32 Rn8xxx_DSP_CalcThd(u32 *Dst, u8 Num)
{
    u8 i;
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u32 TempThd = 0;
    // �����˷�
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;
    MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->FFT_FLG = 0x200;
    for (i = 0; i < Num; i++)
    {
        DSP->MAC_IN0 = Dst[i];
        DSP->MAC_IN1 = Dst[i];
        Dst[i] = DSP->MAC_OUT0;
        DSP->FFT_FLG = 0x200;
    }
    // �����ӷ�
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = FP_ADD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    for (i = 0; i < Num; i++)
    {
        DSP->MAC_IN0 = Dst[i];
        DSP->MAC_IN1 = TempThd;
        TempThd = DSP->MAC_OUT0;
    }
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = TempThd;
    TempThd = DSP->MAC_OUT0;
    TempThd = (u32)sqrt(TempThd);
    return ((u16)TempThd);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_CalcThdRms
** Descriptions:        ����г���ܺ���
** input parameters:    Thd:��г�������ʣ�����������λXX.XX%
**                      FRMS:������Чֵ��������
** output parameters:   NONE
** Returned value:      ��г��������
*********************************************************************************************************/
u32 Rn8xxx_DSP_CalcThdRms(u32 Thd, u32 FRMS)
{
    u32 temp_thd;
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    DSP->MAC_IN0 = Thd;
    temp_thd = DSP->MAC_OUT0;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;
    MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = FRMS;
    DSP->MAC_IN1 = 0x38d1b717;                  // 0.0001
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = temp_thd;
    temp_thd = DSP->MAC_OUT0;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = temp_thd;
    temp_thd = DSP->MAC_OUT0;
    return (temp_thd);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_HPf
** Descriptions:        г�������������㣬���ظ���г���Ĺ�������
** input parameters:    HPf:�ṹ�����ݣ������cos  sinֵ���
** output parameters:   NONE
** Returned value:      ��ǰ��������ֵ*10000,Ϊ����ֵ�����㹦����������CosAngleU������
*********************************************************************************************************/
s16 Rn8xxx_DSP_HPf(sFftMath_HPf_Pw_TypeDef *HPf)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    s16 AngleU, AngleI;
    // ����ת������������2^29
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    MacCtl0Para.CTL0_I2F_DIV_CFG = 29;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = HPf->CosAngleU;
    HPf->CosAngleU = DSP->MAC_OUT0;
    DSP->MAC_IN0 = HPf->CosAngleI_Fu;
    HPf->CosAngleI_Fu = DSP->MAC_OUT0;
    DSP->MAC_IN0 = HPf->SinAngleU_Fi;
    HPf->SinAngleU_Fi = DSP->MAC_OUT0;
    DSP->MAC_IN0 = HPf->SinAngleI_Gp;
    HPf->SinAngleI_Gp = DSP->MAC_OUT0;
    // ���ֵת��
    DSP->MAC_IN0 = HPf->AngleU;
    HPf->AngleU = DSP->MAC_OUT0;
    DSP->MAC_IN0 = HPf->AngleI;
    HPf->AngleI = DSP->MAC_OUT0;
    // �˷�CosAngleU*CosAngleI
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MLAD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = HPf->CosAngleU;
    DSP->MAC_IN1 = HPf->CosAngleI_Fu;
    DSP->MAC_IN2 = 0x0;
    HPf->CosAngleU = DSP->MAC_OUT0;
    // SinAngleU*SinAngleI + CosAngleU*CosAngleI
    DSP->MAC_IN0 = HPf->SinAngleU_Fi;
    DSP->MAC_IN1 = HPf->SinAngleI_Gp;
    DSP->MAC_IN2 = HPf->CosAngleU;
    // (SinAngleU*SinAngleI + CosAngleU*CosAngleI)*2PI*2PI  SinAngleU=SinAngleU/2PI
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = 0x421DE9E6;      // ��ֵ����2*PI*2*PI=39.47842
    DSP->MAC_IN2 = 0x0;
    HPf->CosAngleU = DSP->MAC_OUT0;
    // ����������*100����ת������
    DSP->MAC_IN0 = DSP->MAC_OUT0;;
    DSP->MAC_IN1 = 0x42C80000;      // ��ֵ����100
    DSP->MAC_IN2 = 0x0;
    HPf->SinAngleU_Fi = DSP->MAC_OUT0;
    // ������ǣ�CRD_PHASE*pi/2^31*180/pi = CRD_PHASE*45/2^29
    DSP->MAC_IN0 = HPf->AngleU;//����HPf->AngleUΪCRD_PHASE
    DSP->MAC_IN1 = 0x43E10000;      // ��ֵ����450
    DSP->MAC_IN2 = 0x0;
    HPf->AngleU = DSP->MAC_OUT0;
    DSP->MAC_IN0 = HPf->AngleI;
    DSP->MAC_IN1 = 0x43E10000;      // ��ֵ����450
    DSP->MAC_IN2 = 0x0;
    HPf->AngleI = DSP->MAC_OUT0;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    // �������
    DSP->MAC_IN0 = HPf->AngleU;
    AngleU = (s16)DSP->MAC_OUT0;
    if (AngleU < 0)
    {
        AngleU = 3600 + AngleU;
    }
    DSP->MAC_IN0 = HPf->AngleI;
    AngleI = (s16)DSP->MAC_OUT0;
    if (AngleI < 0)
    {
        AngleI = 3600 + AngleI;
    }
    if (AngleI > AngleU)
    {
        HPf->AngleH_UI = AngleI - AngleU;
    }
    else
    {
        HPf->AngleH_UI = AngleI + 3600 - AngleU;
    }
    // ���㹦������
    DSP->MAC_IN0 = HPf->SinAngleU_Fi;
    return ((s16)DSP->MAC_OUT0);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_Pw
** Descriptions:        г�����ʼ��㣬���ظ���г���Ĺ���
** input parameters:    HPf:�ṹ�����ݣ������FU,FI,cos���;
** output parameters:   NONE
** Returned value:      ��ǰ����ֵΪ����ֵ
*********************************************************************************************************/
s32 Rn8xxx_DSP_Pw(sFftMath_HPf_Pw_TypeDef *HPf)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;

    // ����ת������
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    MacCtl0Para.I2F_PRE_EN = I2F_PRE_32BIT;
    MacCtl0Para.CTL0_I2F_DIV_CFG = 23;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = HPf->CosAngleI_Fu;
    HPf->CosAngleI_Fu = DSP->MAC_OUT0;

    MacCtl0Para.CTL0_I2F_DIV_CFG = 23;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = HPf->SinAngleU_Fi;
    HPf->SinAngleU_Fi = DSP->MAC_OUT0;

    //  MacCtl0Para.CTL0_I2F_DIV_CFG = 31;
    //  DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    //  DSP->MAC_IN0 = HPf->Prms_K;
    //  temp_k = DSP->MAC_OUT0;

    //  MacCtl0Para.gMACCTL0 = 0;
    //  MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    //  MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    //  MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;        // ����Ϊ����ģʽ
    //  MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;      // ���Ϊ����ģʽ
    //  DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    //
    //  DSP->MAC_IN0 = HPf->CosAngleI_Fu;
    //  DSP->MAC_IN1 = temp_k;
    //  HPf->CosAngleI_Fu = DSP->MAC_OUT0;
    //
    //  DSP->MAC_IN0 = HPf->SinAngleU_Fi;
    //  DSP->MAC_IN1 = temp_k;
    //  HPf->SinAngleU_Fi = DSP->MAC_OUT0;

    if (HPf->SinAngleI_Gp)
    {
        MacCtl0Para.gMACCTL0 = 0;
        MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
        MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
        MacCtl0Para.I2F_PRE_EN = I2F_PRE_32BIT;

        if (HPf->SinAngleI_Gp > 0x7fff)
        {
            HPf->SinAngleI_Gp = (HPf->SinAngleI_Gp & 0xffff) | 0xffff0000;
        }
        MacCtl0Para.CTL0_I2F_DIV_CFG = 15;
        DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
        DSP->MAC_IN0 = HPf->SinAngleI_Gp;
        HPf->SinAngleI_Gp = DSP->MAC_OUT0;
        // (1 +��GP)
        MacCtl0Para.gMACCTL0 = 0;
        MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
        MacCtl0Para.CTL0_MODE_SEL = FP_ADD_MODE;
        DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
        DSP->MAC_IN0 = HPf->SinAngleI_Gp;
        DSP->MAC_IN1 = 0x3F800000;
        HPf->SinAngleI_Gp = DSP->MAC_OUT0;
    }
    else
    {
        HPf->SinAngleI_Gp = 0x3F800000;         // GPΪ0ʱ��ֵ�ø�����1
    }
    // �˷�FU*FI*COS��*(1+GP)
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;        // ����Ϊ����ģʽ
    MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;      // ���Ϊ����ģʽ
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    DSP->MAC_IN0 = HPf->CosAngleI_Fu;
    DSP->MAC_IN1 = HPf->SinAngleU_Fi;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = HPf->CosAngleU;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = HPf->SinAngleI_Gp;
    HPf->SinAngleU_Fi = DSP->MAC_OUT0;
    // ������*2^31��ת������
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    MacCtl0Para.CTL0_F2I_MUL_CFG = 31;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = HPf->SinAngleU_Fi;
    return (DSP->MAC_OUT0);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_VectorCalc3P4
** Descriptions:        �������ߵ�ѹ���������򡢸���������������
**                      Angle Ϊ�Ĵ���ֵ��ת���Ƕȹ�ʽΪ Angle/2^24*360������cos,sin����ֵӦΪ �Ƕ�ֵ/180*2^31
**                      ���߽�ϣ�����Ĵ���ֵΪ Angle*2^8
**                      cos,sinֵ�� *2PI/2^29,Ϊ���ټ���������Чֵ��ת����ʱ���2^29/2
**                      RmsReg:0-3�ֱ��ӦA,B,C���ѹ������Ĵ���ֵ
**                      VectorOut��0-3�ֱ��Ӧ���򡢸��������ѹ������Ĵ���ֵ
** input parameters:
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void Rn8xxx_DSP_VectorCalc3P4(u32 *AngleReg, u32 *RmsReg, u32 *VectorOut)
{
    u8 i;
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    sVector3P4_TempData_TypeDef *pTemp;
    pTemp = (sVector3P4_TempData_TypeDef *)&FftMathLibBuf;

    Rn8xxx_DSP_Int2Fp((u32)&RmsReg[0], (u32)&RmsReg[0], 3, 0, 0);

    pTemp->Phs_A_Angle = ((16777216 - AngleReg[0]) << 8);
    pTemp->Phs_B_Angle[2] = ((16777216 - AngleReg[1]) << 8);
    pTemp->Phs_C_Angle[2] = ((16777216 - AngleReg[2]) << 8);
    AngleReg[0] = pTemp->Phs_A_Angle;
    AngleReg[1] = pTemp->Phs_B_Angle[2];
    AngleReg[2] = pTemp->Phs_C_Angle[2];

    if (AngleReg[1] > 2863311530)           // 2863311530 = 2^32-1-1431655765   B��н�+120
    {
        pTemp->Phs_B_Angle[0] = AngleReg[1] - 2863311531;
    }
    else
    {
        pTemp->Phs_B_Angle[0] = AngleReg[1] + 1431655765;
    }
    if (AngleReg[2] > 2863311530)           // 2863311530 = 2^32-1-1431655765   B��н�+120
    {
        pTemp->Phs_C_Angle[1] = AngleReg[2] - 2863311531;
    }
    else
    {
        pTemp->Phs_C_Angle[1] = AngleReg[2] + 1431655765;
    }
    // B,C��н�+240
    if (AngleReg[1] > 1431655764)           // 1431655764 = 2^32-1-2863311531   B��н�+240
    {
        pTemp->Phs_B_Angle[1] = AngleReg[1] - 1431655765;
    }
    else
    {
        pTemp->Phs_B_Angle[1] = AngleReg[1] + 2863311531;
    }
    if (AngleReg[2] > 1431655764)           //C��н�+240
    {
        pTemp->Phs_C_Angle[0] = AngleReg[2] - 1431655765;
    }
    else
    {
        pTemp->Phs_C_Angle[0] = AngleReg[2] + 2863311531;
    }
    Rn8xxx_DSP_Sin_Cos(pTemp->Phs_A_Angle, &pTemp->Cos_PhsA,  &pTemp->Sin_PhsA);
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    MacCtl0Para.CTL0_I2F_DIV_CFG = 28;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = pTemp->Cos_PhsA;
    pTemp->Cos_PhsA = DSP->MAC_OUT0;
    DSP->MAC_IN0 = pTemp->Sin_PhsA;
    pTemp->Sin_PhsA = DSP->MAC_OUT0;

    for (i = 0; i < 3; i++)
    {
        Rn8xxx_DSP_Sin_Cos(pTemp->Phs_B_Angle[i], &pTemp->Cos_PhsB,  &pTemp->Sin_PhsB);
        Rn8xxx_DSP_Sin_Cos(pTemp->Phs_C_Angle[i], &pTemp->Cos_PhsC,  &pTemp->Sin_PhsC);
        // ��cos,sin������ת������
        MacCtl0Para.gMACCTL0 = 0;
        MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
        MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
        MacCtl0Para.CTL0_I2F_DIV_CFG = 28;
        DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
        DSP->MAC_IN0 = pTemp->Cos_PhsB;
        pTemp->Cos_PhsB = DSP->MAC_OUT0;
        DSP->MAC_IN0 = pTemp->Sin_PhsB;
        pTemp->Sin_PhsB = DSP->MAC_OUT0;

        DSP->MAC_IN0 = pTemp->Cos_PhsC;
        pTemp->Cos_PhsC = DSP->MAC_OUT0;
        DSP->MAC_IN0 = pTemp->Sin_PhsC;
        pTemp->Sin_PhsC = DSP->MAC_OUT0;
        // ���� UaCos(Angle0)+Ubcos(Angle1) + UcCos(Angle2)
        MacCtl0Para.gMACCTL0 = 0;
        MacCtl0Para.CTL0_MODE_SEL = FP_MLAD_MODE;
        DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
        DSP->MAC_IN0 = pTemp->Cos_PhsA;
        DSP->MAC_IN1 = RmsReg[0];
        DSP->MAC_IN2 = 0x0;

        DSP->MAC_IN0 = pTemp->Cos_PhsB;
        DSP->MAC_IN1 = RmsReg[1];
        DSP->MAC_IN2 = DSP->MAC_OUT0;

        DSP->MAC_IN0 = pTemp->Cos_PhsC;
        DSP->MAC_IN1 = RmsReg[2];
        DSP->MAC_IN2 = DSP->MAC_OUT0;
        pTemp->temp_a = DSP->MAC_OUT0;

        DSP->MAC_IN0 = pTemp->Sin_PhsA;
        DSP->MAC_IN1 = RmsReg[0];
        DSP->MAC_IN2 = 0x0;

        DSP->MAC_IN0 = pTemp->Sin_PhsB;
        DSP->MAC_IN1 = RmsReg[1];
        DSP->MAC_IN2 = DSP->MAC_OUT0;

        DSP->MAC_IN0 = pTemp->Sin_PhsC;
        DSP->MAC_IN1 = RmsReg[2];
        DSP->MAC_IN2 = DSP->MAC_OUT0;
        pTemp->temp_b = DSP->MAC_OUT0;
        // ���迪��������ת����������
        MacCtl0Para.gMACCTL0 = 0;
        MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
        MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
        DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
        DSP->MAC_IN0 = pTemp->temp_a;
        pTemp->temp_a = DSP->MAC_OUT0;
        DSP->MAC_IN0 = pTemp->temp_b;
        pTemp->temp_b = DSP->MAC_OUT0;
        Rn8xxx_DSP_FpSqrt((u32 *)&pTemp->temp_a, (u32 *)&pTemp->temp_b, &pTemp->Cos_PhsC, &pTemp->Sin_PhsC);
        VectorOut[i] = pTemp->Cos_PhsC;
        // ������ת�ɸ�����
        MacCtl0Para.gMACCTL0 = 0;
        MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
        MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
        DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
        DSP->MAC_IN0 = VectorOut[i];
        VectorOut[i] = DSP->MAC_OUT0;

        MacCtl0Para.gMACCTL0 = 0;
        MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;
        MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Int;
        MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
        DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
        DSP->MAC_IN0 = VectorOut[i];
        DSP->MAC_IN1 = 0x4022CB40;                      // PI*4*P/3 = 4*0.607253/3*pi = 2.543655418
        DSP->FFT_FLG = 0x200;
        VectorOut[i] = DSP->MAC_OUT0;
    }
    return;
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_VectorCalc3P3_U
** Descriptions:        �������ߵ�ѹ���򡢸���������������
**                      Angle Ϊ�Ĵ���ֵ��ת���Ƕȹ�ʽΪ Angle/2^24*360 0-3�ֱ���� A,B,C�ĽǶ�ֵ
**                      cos,sinֵ�� *2PI/2^29,Ϊ���ټ���������Чֵ��ת����ʱ���2^29/2
**                      RmsReg:0-3�ֱ��ӦA,B,C���ѹ�Ĵ���ֵ
**                      VectorOut��0-3�ֱ��Ӧ���򡢸��������ѹ�Ĵ���ֵ����������������
** input parameters:
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void Rn8xxx_DSP_VectorCalc3P3_U(u32 *AngleReg, u32 *RmsReg, u32 *VectorOut)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u32 Temp_a, Temp_b, Temp_U[3];
    float ftemp_a, ftemp_b;

    Rn8xxx_DSP_Int2Fp((u32)&RmsReg[0], (u32)&RmsReg[0], 3, 0, 0);
    // ����Uac
    AngleReg[2] = ((16777216 - AngleReg[2]) << 8);
    Rn8xxx_DSP_Sin_Cos(AngleReg[2], &Temp_a,  &Temp_b);
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    MacCtl0Para.CTL0_I2F_DIV_CFG = 28;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = Temp_a;
    Temp_a = DSP->MAC_OUT0;
    DSP->MAC_IN0 = Temp_b;
    Temp_b = DSP->MAC_OUT0;

    // ���� Uac��ѹ = sqrt((Uab-Ucb*cos(Angle2))^2 + (-Ucb*sin(Angle2))^2)
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = Temp_a;
    DSP->MAC_IN1 = RmsReg[2];
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = 0x40490FDB;              // *PI
    Temp_a = DSP->MAC_OUT0;
    DSP->MAC_IN0 = Temp_b;
    DSP->MAC_IN1 = RmsReg[2];
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = 0x40490FDB;              // *PI
    Temp_b = DSP->MAC_OUT0;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_SUB_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = RmsReg[0];
    DSP->MAC_IN1 = Temp_a;
    Temp_a = DSP->MAC_OUT0;

    // ���迪��������ת����������
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = Temp_a;
    Temp_a = DSP->MAC_OUT0;
    DSP->MAC_IN0 = Temp_b;
    Temp_b = DSP->MAC_OUT0;
    Rn8xxx_DSP_FpSqrt((u32 *)&Temp_a, (u32 *)&Temp_b, &RmsReg[1], &Temp_U[0]);
    // ������ת�ɸ�����
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = RmsReg[1];
    RmsReg[1] = DSP->MAC_OUT0;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;
    MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = RmsReg[1];
    DSP->MAC_IN1 = 0x401B74EF;                      // 4*P = 4*0.607253 = 2.429012
    DSP->FFT_FLG = 0x200;
    RmsReg[1] = DSP->MAC_OUT0;

    // �������򣬸����ѹ
    // Temp_b = Uab+Ucb+Uac
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = FP_ADD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = RmsReg[0];
    DSP->MAC_IN1 = RmsReg[1];
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = RmsReg[2];
    Temp_b = DSP->MAC_OUT0;
    // Temp_b = Temp_b/2
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = Temp_b;
    DSP->MAC_IN1 = 0x3F000000;                  // 0.5 = 0x3f000000
    Temp_b = DSP->MAC_OUT0;
    // Temp_U[0] = Temp_b-Uab ; Temp_U[1] = Temp_b-Ucb ; Temp_U[2] = Temp_b-Uac
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_SUB_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = Temp_b;
    DSP->MAC_IN1 = RmsReg[0];
    Temp_U[0] = DSP->MAC_OUT0;
    DSP->MAC_IN0 = Temp_b;
    DSP->MAC_IN1 = RmsReg[1];
    Temp_U[1] = DSP->MAC_OUT0;
    DSP->MAC_IN0 = Temp_b;
    DSP->MAC_IN1 = RmsReg[2];
    Temp_U[2] = DSP->MAC_OUT0;
    // Temp_b = Temp_b*Temp_U[0]*Temp_U[1]*Temp_U[2]
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = Temp_b;
    DSP->MAC_IN1 = Temp_U[0];
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = Temp_U[1];
    Temp_b = DSP->MAC_OUT0;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = Temp_b;
    DSP->MAC_IN1 = Temp_U[2];
    ftemp_a = sqrt(*(float *)&DSP->MAC_OUT0);

    // ���� Uab^2+Ucb^2+Uac^2
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MLAD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = RmsReg[0];
    DSP->MAC_IN1 = RmsReg[0];
    DSP->MAC_IN2 = 0x0;

    DSP->MAC_IN0 = RmsReg[1];
    DSP->MAC_IN1 = RmsReg[1];
    DSP->MAC_IN2 = DSP->MAC_OUT0;
    DSP->MAC_IN0 = RmsReg[2];
    DSP->MAC_IN1 = RmsReg[2];
    DSP->MAC_IN2 = DSP->MAC_OUT0;
    ftemp_b = *(float *)&DSP->MAC_OUT0;
    ftemp_a = ftemp_a * 1.1547;
    ftemp_b = ftemp_b / 6;
    VectorOut[0] = (u32)sqrt(ftemp_b + ftemp_a);
    VectorOut[1] = (u32)sqrt(ftemp_b - ftemp_a);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_VectorCalc3P3_U
** Descriptions:        �������ߵ������򡢸���������������
**                      Angle Ϊ�Ĵ���ֵ��ת���Ƕȹ�ʽΪ Angle/2^24*360 0-3�ֱ���� A,B,C�ĽǶ�ֵ
**                      cos,sinֵ�� *2PI/2^29,Ϊ���ټ���������Чֵ��ת����ʱ���2^29/2
**                      RmsReg:0-3�ֱ��ӦA,B,C������Ĵ���ֵ
**                      VectorOut��0-3�ֱ��Ӧ���򡢸�����������Ĵ���ֵ����������������
** input parameters:
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void Rn8xxx_DSP_VectorCalc3P3_I(u32 *AngleReg, u32 *RmsReg, u32 *VectorOut)
{
    u8 i;
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    sVector3P3_ITemp_TypeDef *pTemp;
    pTemp = (sVector3P3_ITemp_TypeDef *)&FftMathLibBuf;

    Rn8xxx_DSP_Int2Fp((u32)&RmsReg[0], (u32)&RmsReg[0], 3, 0, 0);

    pTemp->Phs_C_Angle[0] = ((16777216 - AngleReg[2]) << 8);
    AngleReg[2] = pTemp->Phs_C_Angle[0];

    if (AngleReg[2] > 2863311530)           // 2863311530 = 2^32-1-1431655765   B��н�+120
    {
        pTemp->Phs_C_Angle[1] = AngleReg[2] - 2863311531;
    }
    else
    {
        pTemp->Phs_C_Angle[1] = AngleReg[2] + 1431655765;
    }
    // C��н�+240
    if (AngleReg[2] > 1431655764)           //C��н�+240
    {
        pTemp->Phs_C_Angle[2] = AngleReg[2] - 1431655765;
    }
    else
    {
        pTemp->Phs_C_Angle[2] = AngleReg[2] + 2863311531;
    }
    Rn8xxx_DSP_Sin_Cos(pTemp->Phs_C_Angle[0], &pTemp->Cos_Phs[0],  &pTemp->Sin_Phs[0]);
    Rn8xxx_DSP_Sin_Cos(pTemp->Phs_C_Angle[1], &pTemp->Cos_Phs[1],  &pTemp->Sin_Phs[1]);
    Rn8xxx_DSP_Sin_Cos(pTemp->Phs_C_Angle[2], &pTemp->Cos_Phs[2],  &pTemp->Sin_Phs[2]);
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    MacCtl0Para.CTL0_I2F_DIV_CFG = 28;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = pTemp->Cos_Phs[0];
    pTemp->Cos_Phs[0] = DSP->MAC_OUT0;
    DSP->MAC_IN0 = pTemp->Sin_Phs[0];
    pTemp->Sin_Phs[0] = DSP->MAC_OUT0;

    DSP->MAC_IN0 = pTemp->Cos_Phs[1];
    pTemp->Cos_Phs[1] = DSP->MAC_OUT0;
    DSP->MAC_IN0 = pTemp->Sin_Phs[1];
    pTemp->Sin_Phs[1] = DSP->MAC_OUT0;

    DSP->MAC_IN0 = pTemp->Cos_Phs[2];
    pTemp->Cos_Phs[2] = DSP->MAC_OUT0;
    DSP->MAC_IN0 = pTemp->Sin_Phs[2];
    pTemp->Sin_Phs[2] = DSP->MAC_OUT0;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    for (i = 0; i < 3; i++)
    {
        DSP->MAC_IN0 = pTemp->Cos_Phs[i];
        DSP->MAC_IN1 = 0x40490FDB;                      // *pi = 3.141593
        DSP->FFT_FLG = 0x200;
        pTemp->Cos_Phs[i] = DSP->MAC_OUT0;

        DSP->MAC_IN0 = pTemp->Sin_Phs[i];
        DSP->MAC_IN1 = 0x40490FDB;                      // *pi = 3.141593
        DSP->FFT_FLG = 0x200;
        pTemp->Sin_Phs[i] = DSP->MAC_OUT0;
    }
    // ����Iba = -Ia-Ic*cos(Angle)   ; Ibb = -Ic*sin(Angle)
    // ���� = sqrt(a^2+b^2)/3
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MLAD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = pTemp->Cos_Phs[0];
    DSP->MAC_IN1 = (RmsReg[2] | 0x80000000);            // *-Ic
    DSP->MAC_IN2 = (RmsReg[0] | 0x80000000);            // �� -Ia
    pTemp->temp_iba = DSP->MAC_OUT0;
    DSP->MAC_IN0 = pTemp->Sin_Phs[0];
    DSP->MAC_IN1 = (RmsReg[2] | 0x80000000);
    DSP->MAC_IN2 = 0x0;
    pTemp->temp_ibb = DSP->MAC_OUT0;
    // a = (-0.866*Ibb-0.5*Iba) + Ia + Ic*Cos(Angle+240)
    DSP->MAC_IN0 = pTemp->temp_ibb;
    DSP->MAC_IN1 = 0xBF5DB22D;                          // -0.866
    DSP->MAC_IN2 = 0x0;
    DSP->MAC_IN0 = pTemp->temp_iba;
    DSP->MAC_IN1 = 0xBF000000;                          // -0.5
    DSP->MAC_IN2 = DSP->MAC_OUT0;
    DSP->MAC_IN0 = RmsReg[2];
    DSP->MAC_IN1 = pTemp->Cos_Phs[2];
    DSP->MAC_IN2 = DSP->MAC_OUT0;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = 0x3F800000;                        // *1
    DSP->MAC_IN2 = RmsReg[0];
    pTemp->temp_a = DSP->MAC_OUT0;
    // b = (0.866*Iba-0.5*Ibb) + Ic*sin(Angle+240)
    DSP->MAC_IN0 = pTemp->temp_iba;
    DSP->MAC_IN1 = 0x3F5DB22D;                          // -0.866
    DSP->MAC_IN2 = 0x0;
    DSP->MAC_IN0 = pTemp->temp_ibb;
    DSP->MAC_IN1 = 0xBF000000;                          // -0.5
    DSP->MAC_IN2 = DSP->MAC_OUT0;
    DSP->MAC_IN0 = RmsReg[2];
    DSP->MAC_IN1 = pTemp->Sin_Phs[2];
    DSP->MAC_IN2 = DSP->MAC_OUT0;
    pTemp->temp_b = DSP->MAC_OUT0;

    // ���迪��������ת����������
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = pTemp->temp_a;
    pTemp->temp_a = DSP->MAC_OUT0;
    DSP->MAC_IN0 = pTemp->temp_b;
    pTemp->temp_b = DSP->MAC_OUT0;
    Rn8xxx_DSP_FpSqrt((u32 *)&pTemp->temp_a, (u32 *)&pTemp->temp_b, &VectorOut[0], &VectorOut[2]);

    // �������
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MLAD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    // a = (0.866*Ibb-0.5*Iba) + Ia + Ic*Cos(Angle+120)
    DSP->MAC_IN0 = pTemp->temp_ibb;
    DSP->MAC_IN1 = 0x3F5DB22D;                          // -0.866
    DSP->MAC_IN2 = 0x0;
    DSP->MAC_IN0 = pTemp->temp_iba;
    DSP->MAC_IN1 = 0xBF000000;                          // -0.5
    DSP->MAC_IN2 = DSP->MAC_OUT0;
    DSP->MAC_IN0 = RmsReg[2];
    DSP->MAC_IN1 = pTemp->Cos_Phs[1];
    DSP->MAC_IN2 = DSP->MAC_OUT0;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = 0x3F800000;                        // *1
    DSP->MAC_IN2 = RmsReg[0];
    pTemp->temp_a = DSP->MAC_OUT0;
    // b = (-0.866*Iba-0.5*Ibb) + Ic*sin(Angle+120)
    DSP->MAC_IN0 = pTemp->temp_iba;
    DSP->MAC_IN1 = 0xBF5DB22D;                          // -0.866
    DSP->MAC_IN2 = 0x0;
    DSP->MAC_IN0 = pTemp->temp_ibb;
    DSP->MAC_IN1 = 0xBF000000;                          // -0.5
    DSP->MAC_IN2 = DSP->MAC_OUT0;
    DSP->MAC_IN0 = RmsReg[2];
    DSP->MAC_IN1 = pTemp->Sin_Phs[1];
    DSP->MAC_IN2 = DSP->MAC_OUT0;
    pTemp->temp_b = DSP->MAC_OUT0;
    // ���迪��������ת����������
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = pTemp->temp_a;
    pTemp->temp_a = DSP->MAC_OUT0;
    DSP->MAC_IN0 = pTemp->temp_b;
    pTemp->temp_b = DSP->MAC_OUT0;
    Rn8xxx_DSP_FpSqrt((u32 *)&pTemp->temp_a, (u32 *)&pTemp->temp_b, &VectorOut[1], &VectorOut[2]);
    VectorOut[2] = 0;

    // ������ת�ɸ�����
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = I2F_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = VectorOut[0];
    VectorOut[0] = DSP->MAC_OUT0;
    DSP->MAC_IN0 = VectorOut[1];
    VectorOut[1] = DSP->MAC_OUT0;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;
    MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Int;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = VectorOut[0];
    DSP->MAC_IN1 = 0x3F4F4694;                      // 4*P/3 = 4*0.607253/3 = 0.809670667
    VectorOut[0] = DSP->MAC_OUT0;
    DSP->MAC_IN0 = VectorOut[1];
    DSP->MAC_IN1 = 0x3F4F4694;
    VectorOut[1] = DSP->MAC_OUT0;
    DSP->FFT_FLG = 0x200;
    return;
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_CalcPst
** Descriptions:        �����ʱ�������
** input parameters:    PstTemp:�ṹ�����ݣ�����ĸ���ʱ�����
** output parameters:   NONE
** Returned value:      ��ǰ��ʱ����ֵ
*********************************************************************************************************/
/*
    p_0_1    = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 1 * S_DEPTH)  ));
    p_0_7    = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 7 * S_DEPTH)  ));
    p_1      = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 10 * S_DEPTH) ));
    p_1_5    = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 15 * S_DEPTH) ));
    p_2_2    = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 22 * S_DEPTH) ));
    p_3      = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 30 * S_DEPTH) ));
    p_4      = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 40 * S_DEPTH) ));
    p_6      = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 60 * S_DEPTH) ));
    p_8      = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 80 * S_DEPTH) ));
    p_10     = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 100 * S_DEPTH)));
    p_13     = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 130 * S_DEPTH)));
    p_17     = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 170 * S_DEPTH)));
    p_30     = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 300 * S_DEPTH)));
    p_50     = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 500 * S_DEPTH)));
    p_80     = s_min + adc_flicker[UA].s_step * ((float)(get_same_int(cpf[UA], S_CLASS, 800 * S_DEPTH)));
    p_50s_fx = (p_30 + p_50 + p_80) / 3.0;
    p_10s_fx = (p_6 + p_8 + p_10 + p_13 + p_17) / 5.0;
    p_3s_fx  = (p_2_2 + p_3 + p_4) / 3.0;
    p_1s_fx  = (p_0_7 + p_1 + p_1_5) / 3.0;
    p_0_1_fx = p_0_1;
    adc_flicker[UA].pst = (sqrt(0.0314 * p_0_1_fx + 0.0525 * p_1s_fx + 0.0657 * p_3s_fx + 0.28 * p_10s_fx + 0.08 * p_50s_fx) / 512.0) / 2.0;

*/
u32 Rn8xxx_DSP_CalcPst(sFlick_TempData_TypeDef *PstTemp)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u32 *pDat;
    u32 p_1s_fx, p_3s_fx, p_10s_fx, p_50s_fx;
    u8 i;
    float PstErr;
    pDat = &PstTemp->Pst_0_1;
    // �Ƚ�����ת��Ϊ������
    Rn8xxx_DSP_Int2Fp((u32)PstTemp, (u32)PstTemp, 17, 0, 0);
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = FP_MLAD_MODE;
    // ���� P_0_1....P_80
    for (i = 0; i < 15; i++)
    {
        DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
        DSP->MAC_IN0 = *pDat;
        DSP->MAC_IN1 = PstTemp->S_Step_Temp;
        DSP->MAC_IN2 = PstTemp->S_Min_Temp;
        *pDat = DSP->MAC_OUT0;
        *pDat++;
    }
    // �������ӷ�
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = FP_ADD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = PstTemp->Pst_0_7;
    DSP->MAC_IN1 = PstTemp->Pst_1;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = PstTemp->Pst_1_5;
    p_1s_fx = DSP->MAC_OUT0;        // p_1s_fx = Pst_0_7 + Pst_1 + Pst_1_5

    DSP->MAC_IN0 = PstTemp->Pst_2_2;
    DSP->MAC_IN1 = PstTemp->Pst_3;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = PstTemp->Pst_4;
    p_3s_fx = DSP->MAC_OUT0;        // p_3s_fx = Pst_2_2 + Pst_3 + Pst_4

    DSP->MAC_IN0 = PstTemp->Pst_6;
    DSP->MAC_IN1 = PstTemp->Pst_8;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = PstTemp->Pst_10;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = PstTemp->Pst_13;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = PstTemp->Pst_17;
    p_10s_fx = DSP->MAC_OUT0;       // p_10s_fx = Pst_8 + Pst_8 + Pst_10 + Pst_13 + Pst_17

    DSP->MAC_IN0 = PstTemp->Pst_30;
    DSP->MAC_IN1 = PstTemp->Pst_50;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = PstTemp->Pst_80;
    p_50s_fx = DSP->MAC_OUT0;       // p_50s_fx = Pst_30 + Pst_50 + Pst_80

    // �������˼�
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = FP_MLAD_MODE;
    // ����0.0314 * p_0_1_fx + 0.0525 * p_1s_fx + 0.0657 * p_3s_fx + 0.28 * p_10s_fx + 0.08 * p_50s_fx
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = PstTemp->Pst_0_1;
    DSP->MAC_IN1 = 0x3D009D49;  // 0.0314
    DSP->MAC_IN2 = 0x0;

    DSP->MAC_IN0 = p_1s_fx;
    DSP->MAC_IN1 = 0x3C8F5C29;  // 0.0525/3 = 0.0175
    DSP->MAC_IN2 = DSP->MAC_OUT0;

    DSP->MAC_IN0 = p_3s_fx;
    DSP->MAC_IN1 = 0x3CB367A1;  // 0.0657/3 = 0.0219
    DSP->MAC_IN2 = DSP->MAC_OUT0;

    DSP->MAC_IN0 = p_10s_fx;
    DSP->MAC_IN1 = 0x3D656042;  // 0.28/5 = 0.056
    DSP->MAC_IN2 = DSP->MAC_OUT0;

    DSP->MAC_IN0 = p_50s_fx;
    DSP->MAC_IN1 = 0x3CDA740E;  // 0.08/3 = 0.026666667
    DSP->MAC_IN2 = DSP->MAC_OUT0;

    PstErr = *(float *)&DSP->MAC_OUT0;
    PstErr = sqrt(PstErr) / 10.24;
    return ((u32)PstErr);
}

//===================================================
