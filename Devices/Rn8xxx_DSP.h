/**
  ******************************************************************************
  * @file    Rn8xxx_DSP.h
  * @author  Renergy Application Team
  * @version V1.0.0
  * @date    2019.10.09
  * @brief   FFT模块各数学操作
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include <Rn8xxx_Common.h>

#ifndef _Rn8xxx_DSP_H
#define _Rn8xxx_DSP_H

#ifdef   _DRIVE_DSP_GLOBALS
#define  Rn8xxx_DSP_EXT
#else
#define  Rn8xxx_DSP_EXT  extern
#endif

#define FFT_I2F_TimeOut 0x3ff
#define FFT_BitRev_TimeOut 0x3ff
#define FFT_FFT_TimeOut 0x2fff  //1024点3.84ms

typedef struct
{
    u32 ftemp_Int;      // 当前次谐波幅值
    u32 fBase_Int;      // 基波值
    u32 Hpercent;       // 计算的含量
    u32 HRms;           // 谐波有效值
    u32 nMul;           // 含量放大倍数
    u32 EmuReg_Base;    // 基波寄存器值
} sFftMath_Percent_TypeDef;

typedef struct
{
    u32 ftemp_Int;      // 当前次谐波幅值
    u32 fBase_Int;      // 基波值
    u32 Hpercent;       // 计算的含量
    u32 HRms;           // 谐波有效值
    u32 nMul;           // 含量放大倍数
    u32 EmuReg_Base;    // 基波寄存器值
    u32 tPercent[10];   // 10个间谐波含量中间值，用于计算每次间谐波群数据
} sFftMath_InterPercent_TypeDef;

typedef struct
{
    u32 CosAngleU;
    u32 CosAngleI_Fu;
    u32 SinAngleU_Fi;
    u32 SinAngleI_Gp;
    u32 AngleU;         // 谐波电压角度
    u32 AngleI;         // 谐波电流角度
    u16 AngleH_UI;      // 谐波相角
} sFftMath_HPf_Pw_TypeDef;

typedef struct
{
    s32 x;
    u32 y;
} sLagrangeS_TypeDef;

/*MAC_CTL0 配置*/
typedef enum
{
    NOTDO_MODE      = 0,
    I2F_ONCE_MODE   = 1,
    I2F_DMA_MODE    = 2,
    F2I_ONCE_MODE   = 3,
    F2I_DMA_MODE    = 4,
    FP_MUL_MODE     = 5,
    FP_ADD_MODE     = 6,
    FP_SUB_MODE     = 7,
    FP_MLAD_MODE    = 8,

    BTFY_ONCE_MODE  = 9,
    BTFY_DMA_MODE   = 10,

    FFT_MODE        = 11,

    BIT_RVE_MODE    = 12,
    IIR_ONCE_MODE   = 13,
    IIR_DMA_MODE    = 14,
    FIR_DMA_MODE    = 15,
    LINEAR_MODE     = 16,
    LAGRANGE_MODE   = 17,
    ALL_DIS_MODE    = 18,

    MUL_IN_DFM_Fp       = 0,
    MUL_IN_DFM_Int      = 1,

    MUL_OUT_DFM_Fp      = 0,
    MUL_OUT_DFM_Int     = 1,

    ROUND_MODE_NEAREST  = 0,
    ROUND_MODE_ZERO     = 1,
    ROUND_MODE_PINFINITY = 2,
    ROUND_MODE_NINFINITY = 3,
    ROUND_MODE_UP       = 4,
    ROUND_MODE_AWAY     = 5,

    TB_EN_DIS           = 0,
    TB_EN_EN            = 1,

    I2F_PRE_32BIT       = 0,
    I2F_PRE_24BIT       = 1,
    I2F_PRE_16BIT       = 2,
    I2F_PRE_8BIT        = 3,
} eFFTCtl0Para_TypeDef;

typedef enum
{
    MAC_CTL_DMA_DIS   = (0 << 0),
    MAC_CTL_DMA_EN    = (1 << 0),

    BTFY_ONCE_KICK_DIS = (0 << 1),
    BTFY_ONCE_KICK_EN = (1 << 1),

    DIV_KICK_DIS      = (0 << 2),
    DIV_KICK_EN       = (1 << 2),
} eFFTCtl2Para_TypeDef;

typedef union
{
    struct
    {
        u32 CTL0_MODE_SEL   : 5;
        u32 CTL0_MUL_IN_DFM     : 1;
        u32 CTL0_MUL_OUT_DFM    : 1;
        u32 CTL0_ROUND_MODE     : 3;
        u32 CTL0_I2F_DIV_CFG    : 5;
        u32 CTL0_F2I_MUL_CFG    : 5;
        u32 CTL0_TB_FFT_EN      : 1;
        u32 I2F_PRE_EN          : 2;
        u32  RESERVEBIT                  : 9;
    };
    u32 gMACCTL0;
} uFFT_MACCTL0Para_TypeDef;

typedef struct
{
    u32 Phs_A_Angle;
    u32 Phs_B_Angle[3];
    u32 Phs_C_Angle[3];
    u32 Cos_PhsA;
    u32 Sin_PhsA;
    u32 Cos_PhsB;
    u32 Sin_PhsB;
    u32 Cos_PhsC;
    u32 Sin_PhsC;
    u32 temp_a;
    u32 temp_b;
} sVector3P4_TempData_TypeDef;

typedef struct
{
    u32 Phs_C_Angle[3];             // 0 Angle_c  1: Angle_c+120  2: Angle_c+240
    u32 temp_iba;
    u32 temp_ibb;
    u32 Cos_Phs[3];
    u32 Sin_Phs[3];
    u32 temp_a;
    u32 temp_b;
} sVector3P3_ITemp_TypeDef;

typedef struct
{
    u32 S_Min_Temp;
    u32 S_Step_Temp;
    u32 Pst_0_1;
    u32 Pst_0_7;
    u32 Pst_1;
    u32 Pst_1_5;
    u32 Pst_2_2;
    u32 Pst_3;
    u32 Pst_4;
    u32 Pst_6;
    u32 Pst_8;
    u32 Pst_10;
    u32 Pst_13;
    u32 Pst_17;
    u32 Pst_30;
    u32 Pst_50;
    u32 Pst_80;
} sFlick_TempData_TypeDef;

extern ErrorStatus Rn8xxx_DSP_Int2Fp(u32 Dst, u32 Src, u16 Len, u8 Div, u8 DataMode);
extern ErrorStatus Rn8xxx_DSP_BitReverse(u32 Dst, u32 Src, u16 Len);
extern ErrorStatus Rn8xxx_DSP_FFT(u32 SrbAddr, u32 SibAddr, u32 PrbAddr, u32 PibAddr, u16 Len);
extern ErrorStatus Rn8xxx_DSP_FpSqrt(u32 *X_In, u32 *Y_In, u32 *Amp_Out, u32 *Arctan_Out);
extern ErrorStatus Rn8xxx_DSP_Fp2Int(u32 Dst, u32 Src, u8 Mul, u16 Len);
extern ErrorStatus Rn8xxx_DSP_Sin_Cos(u32 In0, u32 *CosOut, u32 *SinOut);
extern ErrorStatus Rn8xxx_DSP_IntDiv(u32 In0, u32 In1, u32 *Out, u16 Mul_N);
extern ErrorStatus Rn8xxx_DSP_HPercent(sFftMath_Percent_TypeDef *HPercent);
extern s16 Rn8xxx_DSP_HPf(sFftMath_HPf_Pw_TypeDef *HPf);
extern s32 Rn8xxx_DSP_Pw(sFftMath_HPf_Pw_TypeDef *HPf);
extern u32 Rn8xxx_DSP_CalcPst(sFlick_TempData_TypeDef *PstTemp);
extern ErrorStatus Rn8xxx_DSP_Init(void);
extern u32 Rn8xxx_DSP_CalcThd(u32 *Dst, u8 Num);
//extern  ErrorStatus Rn8xxx_DSP_Lagrange(u32 *InData , u32 *OutData , u16 InLen , u16 *OutLen, u32 LastData, u16 Frequency, u32 *Lag_t);
extern  ErrorStatus Rn8xxx_DSP_Lagrange(u32 *InData, u32 *OutData, u16 InLen, u16 OutLen, u32 LastData, u16 Frequency);
extern ErrorStatus Rn8xxx_DSP_InterHPercent(sFftMath_InterPercent_TypeDef *HPercent);
extern ErrorStatus Rn8xxx_DSP_Isgrp(sFftMath_InterPercent_TypeDef *HPercent,  u32 *FftCoret, u8 Mode);
extern void Rn8xxx_DSP_VectorCalc3P4(u32 *AngleReg, u32 *RmsReg, u32 *VectorOut);
extern void Rn8xxx_DSP_VectorCalc3P3(u32 *AngleReg, u32 *RmsReg, u32 *VectorOut);
extern void Rn8xxx_DSP_VectorCalc3P3_U(u32 *AngleReg, u32 *RmsReg, u32 *VectorOut);
extern void Rn8xxx_DSP_U16I2Fp(u32 *Dst, u16 *Src, u16 Len);
extern u32 Rn8xxx_DSP_CalcThdRms(u32 Thd, u32 FRMS);
extern ErrorStatus Rn8xxx_DSP_FIR(u32 *InData, u32 *OutData, u32 *ParaDtat, u16 InLen, u8 FirOrder);
extern ErrorStatus Rn8xxx_DSP_HWCalc(u32 *InData, u32 *OutData, u32 *LastHwData);
extern ErrorStatus Rn8xxx_DSP_fBaseCalc(u32 *InData, u32 *OutData_F, u32 KMlu, u8 AveFlag);
extern ErrorStatus Rn8xxx_DSP_HWCalc_2Wave(u32 *InData, u32 *OutData, u32 *LastHwData, u8 PointFlag);

extern ErrorStatus fnFFT_FpSub(u32 In0, u32 In1, u32 *Out);
extern ErrorStatus fnFFT_FpMult(u32 In0, u32 In1, u32 *Out);
#endif
/****************************  (C) COPYRIGHT Renergy  ****************************/
/****************************          END OF FILE          ****************************/
