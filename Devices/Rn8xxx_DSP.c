
#define  _DRIVE_DSP_GLOBALS
#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include <Rn8xxx_DSP.h>

u32 FftMathLibBuf[20];                      // 80字节临时变量用于fft计算时中间变量，减小临时变量使用
/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_Init
** Descriptions:        FFT模块初始化
** input parameters:    打开设备模块时钟
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
** Descriptions:       ADC采样数据转换成单精度浮点数格式
** input parameters:    Dst:转换后数据存储目标地址
**                      Src:转换数据源地址
**                      Len: 数据长度，为4的整数倍
**                      Div: 整数转浮点数时除以2^Div
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
        return (ERROR);    //等待转换完成
    }
    else
    {
        DSP->FFT_FLG = 0x02;
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_U16I2Fp
** Descriptions:        16位整型数据转换成单精度浮点数格式
** input parameters:    Dst:转换后数据存储目标地址
**                      Src:转换数据源地址
**                      Len: 数据长度，为4的整数倍
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
** Descriptions:        单精度浮点数格式转换成整数
** input parameters:    Dst:转换后数据存储目标地址
**                      Src:转换数据源地址
**                      Len: 数据长度，为4的整数倍
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
        return (ERROR);    //等待转换完成
    }
    else
    {
        DSP->FFT_FLG = 0x10;
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_BitReverse
** Descriptions:        数据bit Reverse
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
        return (ERROR);    //等待转换完成
    }
    else
    {
        DSP->FFT_FLG = 0x100;
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_FFT
** Descriptions:        数据FFT转换，进行叠形运算
** input parameters:    SrbAddr:数据实部地址
**                      SibAddr：数据虚部地址
**                      PrbAddr：表格cos值地址
**                      PibAddr：表格sin值地址
**                      Len：数据长度
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

    DSP->DMA_TRBADR = DSP->DMA_SRBADR;      // 目标地址与源地址使用同一地址，节省RAM空间
    DSP->DMA_TIBADR = DSP->DMA_SIBADR;
    DSP->DMA_PRBADR = (PrbAddr & 0x1ffff) / 4;
    DSP->DMA_PIBADR = (PibAddr & 0x1ffff) / 4;

    DSP->DMA_LEN = Len - 1;
    DSP->FFT_FLG = 0x80;
    DSP->MAC_CTL2 = MAC_CTL_DMA_EN;
    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 7, 1, FFT_FFT_TimeOut) == ERROR)
    {
        return (ERROR);    //等待转换完成
    }
    else
    {
        DSP->FFT_FLG = 0x80;
        return (SUCCESS);
    }
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_FpSqrt
** Descriptions:        浮点数均方根及反正切计算
** input parameters:    X_In:输入数据实部
**                      Y_In：输入数据虚部
**                      Amp_Out：输出sqrt值
**                      Arctan_Out：Y/X反正切值
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
        return (ERROR);    //等待转换完成
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
** Descriptions:        浮点数乘法
** input parameters:    In0:输入数据0
**                      In1:输入数据1
**                      Out:结果输出数据
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus fnFFT_FpMult(u32 In0, u32 In1, u32 *Out)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;        // 输入为浮点模式
    MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;      // 输出为浮点模式
    MacCtl0Para.I2F_PRE_EN = I2F_PRE_24BIT;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->FFT_FLG = 0x01;
    DSP->MAC_IN0 = In0;
    DSP->MAC_IN1 = In1;
    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 0, 1, FFT_FFT_TimeOut) == ERROR)
    {
        return (ERROR);    //等待转换完成
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
** Descriptions:        浮点数加法
** input parameters:    In0:输入数据0
**                      In1:输入数据1
**                      Out:结果输出数据
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
        return (ERROR);    //等待转换完成
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
** Descriptions:        浮点数减法
** input parameters:    In0:输入数据0
**                      In1:输入数据1
**                      Out:结果输出数据
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
        return (ERROR);    //等待转换完成
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
** Descriptions:        旋转模式:Arctan(y/x) *2^31/pi
** input parameters:    In0:输入数据, 输入寄存器代表含义：(Angle/180)*2^31   Angle为角度值单位：度
**                      CosOut  输出数据为 cos(Angle)*2^29/(2*PI)
**                      SinOut  输出数据为 sin(Angle)*2^29/(2*PI)
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_Sin_Cos(u32 In0, u32 *CosOut, u32 *SinOut)
{
    DSP->CRD_ANGLE = In0;
    DSP->CRD_CTL = 0x02;     // 使用旋转模式
    if (fnRegState_Detect((u32)(&DSP->CRD_FLG), 1, 1, FFT_FFT_TimeOut) == ERROR)
    {
        return (ERROR);    //等待转换完成
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
** Descriptions:        整形数除法
** input parameters:    In0:被除数
**                      In1:除数
**                      Out:结果输出数据
**                      Mul_N:放大倍数
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
    // 启动除法
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
** Descriptions:        浮点数除法
** input parameters:    In0:被除数
**                      In1:除数
**                      Out:结果输出数据
**                      Mul_N:放大倍数
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
    // 启动除法
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
** Descriptions:        FIR运算
** input parameters:    InData:输入数据指针,包含前10个点数据
**                      OutData:插值后数据指针
**                      InLen:输入数据长度
**                      OutLen:输出数据长度
**                                InData  和OutData不能使用同一个地址,否则会造成转换结果错误
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_FIR(u32 *InData, u32 *OutData, u32 *ParaDtat, u16 InLen, u8 FirOrder)
{
    DSP->FFT_FLG = DSP->FFT_FLG;
    DSP->MAC_CTL2 = 0;
    DSP->MAC_CTL0 = 15;
    DSP->MAC_CTL1 = (FirOrder << 4);        // 配置FIR阶数及步进
    DSP->DMA_SRBADR = (uint32_t)((uint32_t*)InData) >> 2;
    DSP->DMA_TRBADR = (uint32_t)((uint32_t*)OutData) >> 2;
    DSP->DMA_PRBADR = (uint32_t)((uint32_t*)ParaDtat) >> 2;
    DSP->DMA_LEN = InLen - 1;

    DSP->MAC_CTL2 = (1 << 0);

    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 12, 1, FFT_FFT_TimeOut) == ERROR)
    {
        return (ERROR);    //等待转换完成
    }

    DSP->FFT_FLG = DSP->FFT_FLG;

    return (SUCCESS);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_HWCalc_4Wave
** Descriptions:        半波有效值运算
** input parameters:    InData:输入2周波128点数据
**                      OutData:半波有效值，平方和值，如需得到真实半波，需开根号
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
    // 浮点转整型
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
** Descriptions:        半波有效值运算
** input parameters:    InData:输入1周波64点或128点数据
**                      OutData:半波有效值，平方和值，如需得到真实半波，需开根号
**                      Flag: 0: 1周波64点数据   1:1周波128点数据
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
        // 128点1周波
        j = 64;
        k = 128;
        tstep = 2;
    }
    else
    {
        // 64点1周波
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

    // 浮点转整型
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
** Descriptions:        基波值运算
** input parameters:    InData: 输入基波值，为整形数，在开根号后输出
**                      OutData_F:基波值，浮点数
**                      OutData_Int:基波值，整型数
**                      FWaveData:前4次基波值和，与当前值累加后求平均值
**
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_DSP_fBaseCalc(u32 *InData, u32 *OutData_F, u32 KMlu, u8 AveFlag)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u32 fBaseTemp;
    // 转成浮点单元
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
    DSP->MAC_IN1 = 0x3F5BD95D;              // 此值代表4*P=4*0.607253 为计算谐波有效值需除2*sqrt(2),此值为 4*P/(2*sqrt(2)) = 2*0.607253/1.414
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = KMlu;

    if (AveFlag)
    {
        // 求5点平均，将数据乘0.2
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
** Descriptions:        拉格朗日插值
** input parameters:    InData:输入数据指针
**                      OutData:插值后数据指针
**                      InLen:输入数据长度
**                      OutLen:输出数据长度
**                            插值前InData和插值后OutData不能使用同一个地址,否则会造成转换结果错误
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

    DSP->MAC_IN0 = Frequency;  //f,频率，2位小数
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

    // 除法 Step = 3579545/2/128/(Frequency*OutLen)
    DSP->MAC_CTL0 = 0;
    DSP->DIV_IN0 = 0x49AAAF9E;     //0x49AAAF9E为100*3579545/2/128浮点数,Frequency放大100
    DSP->DIV_IN1 = DSP->MAC_OUT0;
    DSP->FFT_FLG = 0x04;
    // 启动除法
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

    // 启动加法 INTP_LOC = f_step + 1
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
    DSP->MAC_CTL1 = 0x01;     //插值模式使用上周期的最后一个数据，使能信号
    DSP->INTP_LEN = InLen;
    DSP->DMA_LEN = OutLen - 1;

    DSP->INTP_STEP = f_step;
    DSP->MAC_IN5 = LastData;  //上一次值

    DSP->DMA_SRBADR = (uint32_t)((uint32_t*)InData) >> 2;
    DSP->DMA_TRBADR = (uint32_t)((uint32_t*)OutData) >> 2;

    DSP->MAC_CTL2 = (1 << 0); //启动

    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 14, 1, FFT_FFT_TimeOut) == ERROR)
    {
        return (ERROR);    //等待转换完成
    }

    DSP->FFT_FLG = DSP->FFT_FLG;

    LastData = *(OutData + OutLen - 1); //保持上一个值

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

    DSP->MAC_IN0 = Frequency;  //f,频率，2位小数
    f_step = DSP->MAC_OUT0;

    DSP->MAC_IN0 = InLen ;  //
    InLen_F = DSP->MAC_OUT0;

    // 除法 Step = 3579545/2/128/(Frequency*256) = 54.61952209/Frequency
    DSP->MAC_CTL0 = 0;
    DSP->DIV_IN0 = 0x45AAAF9E;     //0x45AAAF9E为54.61952209*100浮点数,Frequency放大100
    DSP->DIV_IN1 = f_step;
    DSP->FFT_FLG = 0x04;
    // 启动除法
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
        //------初始t=InLen_F + 1+f_step-------------------
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
    DSP->MAC_IN1 = 0x40000000;  //---0x40000000为2的浮点数
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
    // 启动除法
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
    DSP->MAC_CTL1=0x01;       //插值模式使用上周期的最后一个数据，使能信号
    DSP->INTP_LEN=InLen;
    DSP->DMA_LEN=*OutLen-1;

    DSP->INTP_STEP= f_step;
    DSP->MAC_IN5 = LastData;  //上一次值

    DSP->DMA_SRBADR=(uint32_t)((uint32_t*)InData)>>2;
    DSP->DMA_TRBADR=(uint32_t)((uint32_t*)OutData)>>2;

    DSP->MAC_CTL2=(1<<0);   //启动

    if(fnRegState_Detect((u32)(&DSP->FFT_FLG) , 14 , 1 ,FFT_FFT_TimeOut) == ERROR) return(ERROR);//等待转换完成

    DSP->FFT_FLG=DSP->FFT_FLG;

    //LastData = *(OutData + *OutLen-1);  //保持上一个值

    *Lag_t = DSP->INTP_LOC;

    return(SUCCESS);
}
*/
/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_HPercent
** Descriptions:        整形数除法,用于计算各次谐波的有效值及含量
** input parameters:    HPercent:结构体数据，计算的谐波含量及有效值存放
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
    // 启动除法
    FFT->MAC_CTL1 = DIV_KICK_EN;
    if(fnRegState_Detect((u32)(&FFT->FFT_FLG) , 2 , 1 ,FFT_I2F_TimeOut) == ERROR) return(ERROR);//等待转换完成
    else
    {
        FFT->FFT_FLG = 0x04;
        HPercent->Hpercent = FFT->DIV_OUT0;
        // 启动乘法，将计算的含量乘以10000的放大倍数
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
            //启动乘法，计算谐波含量幅值
            FFT->FFT_FLG = 0x200;
            FFT->MAC_IN0 = HPercent->HRms;
            FFT->MAC_IN1 = 0x3F5BD95D;              // 此值代表4*P=4*0.607253 为计算谐波有效值需除2*sqrt(2),此值为 4*P/(2*sqrt(2)) = 2*0.607253/1.414
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
// 使用EMU基波有效值计算谐波有效值
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
    // 启动除法
    DSP->MAC_CTL2 = DIV_KICK_EN;
    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 2, 1, FFT_I2F_TimeOut) == ERROR)
    {
        return (ERROR);    //等待转换完成
    }
    else
    {
        DSP->FFT_FLG = 0x04;
        HPercent->Hpercent = DSP->DIV_OUT0;
        // 启动乘法
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
            // 将计算的含量乘以10000的放大倍数
            DSP->MAC_IN0 = DSP->MAC_OUT0;
            DSP->MAC_IN1 = 0x461C4000;                      // 10000的浮点数表示
            HPercent->Hpercent = DSP->MAC_OUT0;
            DSP->FFT_FLG = 0x200;
            //启动乘法，计算谐波含量幅值
            DSP->MAC_IN0 = HPercent->EmuReg_Base;               // 将EMU基波有效值转成浮点数
            DSP->MAC_IN1 = PercentTemp;
            {
                DSP->FFT_FLG = 0x200;
                HPercent->HRms = DSP->MAC_OUT0;

                MacCtl0Para.gMACCTL0 = 0;
                MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;           // 浮点转整型数
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
** Descriptions:        整形数除法,用于计算间谐波含量
** input parameters:    HPercent:结构体数据，计算的间谐波含量
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
    // 启动除法
    DSP->MAC_CTL1 = DIV_KICK_EN;
    if (fnRegState_Detect((u32)(&DSP->FFT_FLG), 2, 1, FFT_I2F_TimeOut) == ERROR)
    {
        return (ERROR);    //等待转换完成
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
** Descriptions:        用于计�                     1：启用，乘补偿系数，补偿系数放大10000倍
** output parameters:   NONE
** Returned value:      SUCCES慵湫巢ㄗ幼楹�
** input parameters:    HPercent:结构体数据，计算间谐波子群含量
**                      将5hz为单位的10次含量计算总的间谐波群含量
**                      FftCoret: 间谐波补偿系数，系数*10000，以此达到计算出的含量为xx.xx%
**                      Mode: 补偿模式是否启用，0：不启用，直接乘10000固定值
**                                              1：启用，乘补偿系数，补偿系数放大10000倍
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
            DSP->MAC_IN1 = 0x461C4000;    // 0x461C4000为10000的浮点数表示
        }
        HPercent->tPercent[i] = DSP->MAC_OUT0;
        DSP->MAC_IN0 = HPercent->tPercent[i];
        DSP->MAC_IN1 = HPercent->tPercent[i];
        HPercent->tPercent[i] = DSP->MAC_OUT0;
    }
    // 启动加法
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
** Descriptions:        计算谐波总含有率
** input parameters:    Src:各次谐波含有率  Num:计算谐波总次数
**                      Dst:临时变量，存储含有率转浮点及自乘后的值
** output parameters:   NONE
** Returned value:      THD
*********************************************************************************************************/
u32 Rn8xxx_DSP_CalcThd(u32 *Dst, u8 Num)
{
    u8 i;
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    u32 TempThd = 0;
    // 启动乘法
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
    // 启动加法
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
** Descriptions:        计算谐波总含量
** input parameters:    Thd:总谐波含有率，整型数，单位XX.XX%
**                      FRMS:基波有效值，浮点数
** output parameters:   NONE
** Returned value:      总谐波含有量
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
** Descriptions:        谐波功率因数计算，返回各次谐波的功率因数
** input parameters:    HPf:结构体数据，计算的cos  sin值存放
** output parameters:   NONE
** Returned value:      当前功率因数值*10000,为整数值，浮点功率因数存在CosAngleU变量中
*********************************************************************************************************/
s16 Rn8xxx_DSP_HPf(sFftMath_HPf_Pw_TypeDef *HPf)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;
    s16 AngleU, AngleI;
    // 整形转浮点数，并除2^29
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
    // 相角值转换
    DSP->MAC_IN0 = HPf->AngleU;
    HPf->AngleU = DSP->MAC_OUT0;
    DSP->MAC_IN0 = HPf->AngleI;
    HPf->AngleI = DSP->MAC_OUT0;
    // 乘法CosAngleU*CosAngleI
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
    DSP->MAC_IN1 = 0x421DE9E6;      // 此值代表2*PI*2*PI=39.47842
    DSP->MAC_IN2 = 0x0;
    HPf->CosAngleU = DSP->MAC_OUT0;
    // 将功率因数*100，并转成整数
    DSP->MAC_IN0 = DSP->MAC_OUT0;;
    DSP->MAC_IN1 = 0x42C80000;      // 此值代表100
    DSP->MAC_IN2 = 0x0;
    HPf->SinAngleU_Fi = DSP->MAC_OUT0;
    // 计算相角，CRD_PHASE*pi/2^31*180/pi = CRD_PHASE*45/2^29
    DSP->MAC_IN0 = HPf->AngleU;//参数HPf->AngleU为CRD_PHASE
    DSP->MAC_IN1 = 0x43E10000;      // 此值代表450
    DSP->MAC_IN2 = 0x0;
    HPf->AngleU = DSP->MAC_OUT0;
    DSP->MAC_IN0 = HPf->AngleI;
    DSP->MAC_IN1 = 0x43E10000;      // 此值代表450
    DSP->MAC_IN2 = 0x0;
    HPf->AngleI = DSP->MAC_OUT0;

    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    // 计算相角
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
    // 计算功率因数
    DSP->MAC_IN0 = HPf->SinAngleU_Fi;
    return ((s16)DSP->MAC_OUT0);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_DSP_Pw
** Descriptions:        谐波功率计算，返回各次谐波的功率
** input parameters:    HPf:结构体数据，计算的FU,FI,cos存放;
** output parameters:   NONE
** Returned value:      当前功率值为整数值
*********************************************************************************************************/
s32 Rn8xxx_DSP_Pw(sFftMath_HPf_Pw_TypeDef *HPf)
{
    uFFT_MACCTL0Para_TypeDef MacCtl0Para;

    // 整形转浮点数
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
    //  MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;        // 输入为浮点模式
    //  MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;      // 输出为浮点模式
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
        // (1 +　GP)
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
        HPf->SinAngleI_Gp = 0x3F800000;         // GP为0时，值置浮点数1
    }
    // 乘法FU*FI*COSΦ*(1+GP)
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MUL_MODE;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MUL_IN_DFM = MUL_IN_DFM_Fp;        // 输入为浮点模式
    MacCtl0Para.CTL0_MUL_OUT_DFM = MUL_OUT_DFM_Fp;      // 输出为浮点模式
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;

    DSP->MAC_IN0 = HPf->CosAngleI_Fu;
    DSP->MAC_IN1 = HPf->SinAngleU_Fi;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = HPf->CosAngleU;
    DSP->MAC_IN0 = DSP->MAC_OUT0;
    DSP->MAC_IN1 = HPf->SinAngleI_Gp;
    HPf->SinAngleU_Fi = DSP->MAC_OUT0;
    // 将功率*2^31，转成整数
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
** Descriptions:        三相四线电压、电流正序、负序、零序向量计算
**                      Angle 为寄存器值，转换角度公式为 Angle/2^24*360，计算cos,sin填入值应为 角度值/180*2^31
**                      两者结合，填入寄存器值为 Angle*2^8
**                      cos,sin值需 *2PI/2^29,为减少计算量，有效值在转浮点时需除2^29/2
**                      RmsReg:0-3分别对应A,B,C相电压或电流寄存器值
**                      VectorOut：0-3分别对应正序、负序、零序电压或电流寄存器值
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

    if (AngleReg[1] > 2863311530)           // 2863311530 = 2^32-1-1431655765   B相夹角+120
    {
        pTemp->Phs_B_Angle[0] = AngleReg[1] - 2863311531;
    }
    else
    {
        pTemp->Phs_B_Angle[0] = AngleReg[1] + 1431655765;
    }
    if (AngleReg[2] > 2863311530)           // 2863311530 = 2^32-1-1431655765   B相夹角+120
    {
        pTemp->Phs_C_Angle[1] = AngleReg[2] - 2863311531;
    }
    else
    {
        pTemp->Phs_C_Angle[1] = AngleReg[2] + 1431655765;
    }
    // B,C相夹角+240
    if (AngleReg[1] > 1431655764)           // 1431655764 = 2^32-1-2863311531   B相夹角+240
    {
        pTemp->Phs_B_Angle[1] = AngleReg[1] - 1431655765;
    }
    else
    {
        pTemp->Phs_B_Angle[1] = AngleReg[1] + 2863311531;
    }
    if (AngleReg[2] > 1431655764)           //C相夹角+240
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
        // 将cos,sin的整数转浮点数
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
        // 计算 UaCos(Angle0)+Ubcos(Angle1) + UcCos(Angle2)
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
        // 将需开根号数据转成整型数据
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
        // 将数据转成浮点数
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
** Descriptions:        三相三线电压正序、负序、零序向量计算
**                      Angle 为寄存器值，转换角度公式为 Angle/2^24*360 0-3分别代表 A,B,C的角度值
**                      cos,sin值需 *2PI/2^29,为减少计算量，有效值在转浮点时需除2^29/2
**                      RmsReg:0-3分别对应A,B,C相电压寄存器值
**                      VectorOut：0-3分别对应正序、负序、零序电压寄存器值，三相三线无零序
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
    // 计算Uac
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

    // 计算 Uac电压 = sqrt((Uab-Ucb*cos(Angle2))^2 + (-Ucb*sin(Angle2))^2)
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

    // 将需开根号数据转成整型数据
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = Temp_a;
    Temp_a = DSP->MAC_OUT0;
    DSP->MAC_IN0 = Temp_b;
    Temp_b = DSP->MAC_OUT0;
    Rn8xxx_DSP_FpSqrt((u32 *)&Temp_a, (u32 *)&Temp_b, &RmsReg[1], &Temp_U[0]);
    // 将数据转成浮点数
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

    // 计算正序，负序电压
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

    // 计算 Uab^2+Ucb^2+Uac^2
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
** Descriptions:        三相三线电流正序、负序、零序向量计算
**                      Angle 为寄存器值，转换角度公式为 Angle/2^24*360 0-3分别代表 A,B,C的角度值
**                      cos,sin值需 *2PI/2^29,为减少计算量，有效值在转浮点时需除2^29/2
**                      RmsReg:0-3分别对应A,B,C相电流寄存器值
**                      VectorOut：0-3分别对应正序、负序、零序电流寄存器值，三相三线无零序
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

    if (AngleReg[2] > 2863311530)           // 2863311530 = 2^32-1-1431655765   B相夹角+120
    {
        pTemp->Phs_C_Angle[1] = AngleReg[2] - 2863311531;
    }
    else
    {
        pTemp->Phs_C_Angle[1] = AngleReg[2] + 1431655765;
    }
    // C相夹角+240
    if (AngleReg[2] > 1431655764)           //C相夹角+240
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
    // 计算Iba = -Ia-Ic*cos(Angle)   ; Ibb = -Ic*sin(Angle)
    // 负序 = sqrt(a^2+b^2)/3
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_MODE_SEL = FP_MLAD_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = pTemp->Cos_Phs[0];
    DSP->MAC_IN1 = (RmsReg[2] | 0x80000000);            // *-Ic
    DSP->MAC_IN2 = (RmsReg[0] | 0x80000000);            // 加 -Ia
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

    // 将需开根号数据转成整型数据
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = F2I_ONCE_MODE;
    DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
    DSP->MAC_IN0 = pTemp->temp_a;
    pTemp->temp_a = DSP->MAC_OUT0;
    DSP->MAC_IN0 = pTemp->temp_b;
    pTemp->temp_b = DSP->MAC_OUT0;
    Rn8xxx_DSP_FpSqrt((u32 *)&pTemp->temp_a, (u32 *)&pTemp->temp_b, &VectorOut[0], &VectorOut[2]);

    // 正序计算
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
    // 将需开根号数据转成整型数据
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

    // 将数据转成浮点数
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
** Descriptions:        闪变短时闪变计算
** input parameters:    PstTemp:结构体数据，计算的各临时量存放
** output parameters:   NONE
** Returned value:      当前短时闪变值
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
    // 先将数据转换为浮点数
    Rn8xxx_DSP_Int2Fp((u32)PstTemp, (u32)PstTemp, 17, 0, 0);
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = FP_MLAD_MODE;
    // 计算 P_0_1....P_80
    for (i = 0; i < 15; i++)
    {
        DSP->MAC_CTL0 = MacCtl0Para.gMACCTL0;
        DSP->MAC_IN0 = *pDat;
        DSP->MAC_IN1 = PstTemp->S_Step_Temp;
        DSP->MAC_IN2 = PstTemp->S_Min_Temp;
        *pDat = DSP->MAC_OUT0;
        *pDat++;
    }
    // 浮点数加法
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

    // 浮点数乘加
    MacCtl0Para.gMACCTL0 = 0;
    MacCtl0Para.CTL0_ROUND_MODE = ROUND_MODE_NEAREST;
    MacCtl0Para.CTL0_MODE_SEL = FP_MLAD_MODE;
    // 计算0.0314 * p_0_1_fx + 0.0525 * p_1s_fx + 0.0657 * p_3s_fx + 0.28 * p_10s_fx + 0.08 * p_50s_fx
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
