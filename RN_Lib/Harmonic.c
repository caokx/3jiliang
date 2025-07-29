#define  _Harmonic_GLOBALS

#include <Includes.h>

/*********************************************************************************************************
** Function name:       fnHarmonic_CheckUn
** Descriptions:        判断电压有效值是否有值
** input parameters:    nPhs: 相别，0-2分别代表 A,B,C
** output parameters:   NONE
** Returned value:      0：电压有效值为0  1：电压有效值有值
*********************************************************************************************************/
u8 fnHarmonic_CheckUn(u8 Phs)
{
    #if(nPhs == SinglePhs)
    if (MeasureRms.PubData.U[0] < 125000)
    {
        return 0;    //小于125V
    }
    #else
    if (MeasureRms.PubData.U[Phs] < 12500)
    {
        return 0;
    }
    #endif
    else
    {
        return 1;
    }
}

/*********************************************************************************************************
** Function name:       fnHarmonic_CheckI
** Descriptions:        判断电流有效值是否有值
** input parameters:    nPhs: 相别，0-2分别代表 A,B,C
** output parameters:   NONE
** Returned value:      0：电流有效值为0  1：电流有效值有值
*********************************************************************************************************/
u8 fnHarmonic_CheckI(u8 Phs)
{
    #if(nPhs == SinglePhs)
    if (abs(MeasureRms.PubData.Pw[0]) < 1100)
    {
        return 0;    //小于1% 时不计算
    }
    #else
    if (abs(MeasureRms.PubData.I[Phs]) < 110)
    {
        return 0;    //
    }
    #endif
    else
    {
        return 1;
    }
}

/*********************************************************************************************************
** Function name:       fnHarmonic_D2fp_Exec
** Descriptions:        谐波电能处理程序，PtHPw 填入D2FP00,NtHPw填入D2FP01
** input parameters:    PtPw：正向总谐波功率    NtHPw:反相总谐波功率
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void fnHarmonic_D2fp_Exec(s32 *PtHPw, s32 *NtHPw)
{
    u32 TempData;

    // 总谐波脉冲

    TempData = (abs(PtHPw[0]) >> 4) * Harmonic_D2FK;

    D2F->D2FP[1] = TempData;

    TempData = (abs(NtHPw[0]) >> 4) * Harmonic_D2FK;

    D2F->D2FP[0] = TempData;
}

/*********************************************************************************************************
** Function name:       fnHarmonic_FEgSh_D2fp_Exec
** Descriptions:        基波电能处理程序，正向 填入D2FP03 , 反向填入D2FP02
** input parameters:    PtFPw：基波功率
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void fnHarmonic_FEgSh_D2fp_Exec(s32 *FPw)
{
    u32 TempData;

    // 总谐波脉冲

    TempData = (abs(FPw[0]) >> 4);

    if (FPw[0] > 0)
    {
        D2F->D2FP[3] = TempData;
    }
    else
    {
        D2F->D2FP[2] = TempData;
    }
}

/*********************************************************************************************************
** Function name:       fnHarmonic_Init
** Descriptions:        谐波分析数据初始化
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void fnHarmonic_Init(void)
{
    u32  TempData;

    memset(&HarmonicData, 0, sizeof(sHarmonicData_TypeDef));

    fnHarmonic_FirmParaCheck();

    Rn8xxx_DSP_Init();

    SysCtl_EnableWrite;
    M2M_Clk_En;

    Rn8xxx_GPIO_CfgFun(Pin_PtHPF, _CF1);  //正向谐波电能脉冲输出
    Rn8xxx_GPIO_CfgIOMode(Pin_PtHPF, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_CfgFun(Pin_NtHPF, _CF0);  //反向谐波电能脉冲输出
    Rn8xxx_GPIO_CfgIOMode(Pin_NtHPF, GPIO_MODE_OUT, NORMAL_OUT);

    SysCtl_EnableWrite;
    D2F_Clk_En;

    //D2F->CFG = 0x01;   //D2F 累加型
    D2F->CFG = 0x00;   //D2F 读后清零
    //----谐波电能积分，D2F------------

    TempData = MeasureFirmPara.HFConst1;
    D2F->HFconst3 = (u16)((0.9216 / 2.048) * (float)TempData);
    //  D2F->HFconst3 = (u16)((0.9216/3.58)*(float)TempData);   //MCU芯片D2F积分的时钟是3.6864MHz/4=0.9216MHz，
    //HFconst3=(0.9216/计量芯片积分时钟)*HFconst1
    #if (HarmonicPulseOut_Mode==HarmonicPulseOut_Interrupt)
    Rn8xxx_GPIO_CfgFun(Pin_PtHPF, _NORMALIO);  //正向谐波电能脉冲输出
    Rn8xxx_GPIO_CfgIOMode(Pin_PtHPF, GPIO_MODE_IN, NORMAL_IN);
    Rn8xxx_GPIO_CfgFun(Pin_NtHPF, _NORMALIO);  //反向谐波电能脉冲输出
    Rn8xxx_GPIO_CfgIOMode(Pin_NtHPF, GPIO_MODE_IN, NORMAL_IN);
    D2F->IE = 0x03; //CF0,CF1中断
    NVIC_EnableIRQ(D2F_IRQn);
    NVIC_SetPriority(D2F_IRQn, 0);
    NVIC_SetPriority(TC1_IRQn, 0);
    #endif

    //  NVIC_SetPriority(EXT4_IRQn, 1);
    //  NVIC_SetPriority(SPI_IRQn, 0);
    //  NVIC_SetPriority(SPI1_IRQn, 2);
    //  NVIC_SetPriority(TC0_IRQn, 2);
}

sFftMath_Percent_TypeDef Temp_Per;
sFftMath_HPf_Pw_TypeDef Temp_HPf;
u32 TestHarmonicTime[10];
/*********************************************************************************************************
** 各次谐波补偿系数值，针对128点补偿数据
**
*********************************************************************************************************/
const u32 Fftcoefficient_128[21] =
{
    0x3F800000,     // 1.00            //基波
    0x3F800000,     // 1.00         //2
    0x3F804F12,     // 1.002413     //3
    0x3F801E30,     // 1.000921     //4
    0x3F801E30,     // 1.000921     //5
    0x3F801E30,     // 1.000921     //6
    0x3F804F12,     // 1.002413     //7
    0x3F8059EA,     // 1.002744      //8
    0x3F807A3A,     // 1.003730     //9
    0x3F809B06,     // 1.004730     //10
    0x3F811783,     // 1.008530     //11
    0x3F811783,     // 1.008530     //12
    0x3F81178B,     // 1.008531     //13
    0x3F81470F,     // 1.009981     //14
    0x3F818F47,     // 1.012185     //15
    0x3F81B121,     // 1.013218     //16
    0x3F820C8D,     // 1.016008     //17
    0x3F82362A,     // 1.017278     //18
    0x3F827F91,     // 1.019518     //19
    0x3F82BA38,     // 1.021308     //20
    0x3F8302A3,     // 1.023518     //21
};
#if(nPhs == SinglePhs)
//----具体计算参见exel文件:谐波误差打高分补偿值计算公式-------------
const u16 FftGP_Tab[nHarmonic][nPhs] =
{
    0x0000,     // 1 次谐波功率增益
    0xF7A0,     // 2 次谐波功率增益
    0xF830,     // 3
    0xF8C1,     // 4
    0xF953,     // 5
    0xF9E7,     // 6
    0xFA5E,     // 7
    0xFB13,     // 8
    0xFBAB,     // 9
    0xFC45,     // 10
    0xFCE0,     // 11
    0xFE1B,     // 12
    0xFF5C,     // 13
    0x0000,     // 14
    0x14A,      // 15
    0x29C,      // 16
    0x348,      // 17
    0x4A4,      // 18
    0x608,      // 19
    0x6BC,      // 20
    0x773,      // 21
};
//----具体计算参见exel文件:谐波误差打高分补偿值计算公式-------------
const u32 FftCosAngle_Tab[nHarmonic][nPhs] =
{
    0x00000000, // 1 次谐波功率增益
    0x00000000,     // 2 次谐波功率增益
    0x00000000,     // 3
    0x00000000,     // 4
    0x00000000,     // 5
    0x0000,     // 6
    0x0000,     // 7
    0x0000,     // 8
    0x0000,     // 9
    0x0000,     // 10
    0x0000,     // 11
    0x0000,     // 12
    0x0000,     // 13
    0x0000,     // 14
    0x0000,     // 15
    0x0000,     // 16
    0x0000,     // 17
    0x0000,     // 18
    0x0000,     // 19
    0x0000,     // 20
    0x0000,     // 21
};
#else
//----具体计算参见exel文件:谐波误差打高分补偿值计算公式-------------
const u16 FftGP_Tab[nHarmonic][nPhs] =
{
    0x0000,   0x0000,   0x0000,      // 1 次谐波功率增益
    0x00B3,   0x003B, 0x0072,      // 2 次谐波功率增益
    0x0000,   0x0000, 0x0000,      // 3
    0x0000,   0x0000, 0x0000,      // 4
    0x0000,   0x0000, 0x0000,      // 5
    0x0000,   0x0000, 0x0000,      // 6
    0x0000,   0x0000, 0x0000,      // 7
    0x0000,   0x0000, 0x0000,      // 8
    0x0000,   0x0000, 0x0000,      // 9
    0x0000,   0x0000, 0x0000,      // 10
    0x0000,   0x0000, 0x0000,      // 11
    0x0000,   0x0000, 0x0000,      // 12
    0x0000,   0x0000, 0x0000,      // 13
    0x0000,   0x0000, 0x0000,      // 14
    0x0000,   0x0000, 0x0000,      // 15
    0x0000,   0x0000, 0x0000,      // 16
    0x0000,   0x0000, 0x0000,      // 17
    0x0000,   0x0000, 0x0000,      // 18
    0x0000,   0x0000, 0x0000,      // 19
    0x0000,   0x0000, 0x0000,      // 20
    0x0000,   0x0000, 0x0000,      // 21
    0x0000,   0x0000, 0x0000,      // 22
    0x0000,   0x0000, 0x0000,      // 23
    0x0000,   0x0000, 0x0000,      // 24
    0x0000,   0x0000, 0x0000,      // 25
    0x0000,   0x0000, 0x0000,      // 26
    0x0000,   0x0000, 0x0000,      // 27
    0x0000,   0x0000, 0x0000,      // 28
    0x0000,   0x0000, 0x0000,      // 29
    0x0000,   0x0000, 0x0000,      // 30
    0x0000,   0x0000, 0x0000,      // 31
    0x0000,   0x0000, 0x0000,      // 32
    0x0000,   0x0000, 0x0000,      // 33
    0x0000,   0x0000, 0x0000,      // 34
    0x0000,   0x0000, 0x0000,      // 35
    0x0000,   0x0000, 0x0000,      // 36
    0x0000,   0x0000, 0x0000,      // 37
    0x0000,   0x0000, 0x0000,      // 38
    0x0000,   0x0000, 0x0000,      // 39
    0x002A,   0xFF0D, 0xFFD0,      // 40
    0x0071,   0x01BE, 0x0100,      // 41
};
//----具体计算参见exel文件:谐波误差打高分补偿值计算公式-------------
const u32 FftCosAngle_Tab[nHarmonic][nPhs] =
{
    0x00000000,   0x00000000,   0x00000000,      // 1 次谐波
    0xFFB1B612,   0xFFDE8134, 0xFFDAD33D,      // 2 次谐波
    0xFFD5990E,   0xFFD3E962, 0xFF9FB2C4,      // 3
    0xFFB27229,   0xFFC3A3BB, 0xFFD29DEC,      // 4
    0xFFCA1D0E,   0xFFC1CA6E, 0x00000000,      // 5
    0xFFD0C7B5,   0xFFCC249B, 0x00000000,      // 6
    0xFFB3D021,   0x00000000, 0x00000000,      // 7
    0xFFB74CC8,   0x00000000, 0x00000000,      // 8
    0xFFE386F7,   0x00000000, 0x00000000,      // 9
    0xFFA93214,   0x00000000, 0x00000000,      // 10
    0xFFAFF6F9,   0x00000000, 0x00000000,      // 11
    0xFFE53518,   0x00000000, 0x00000000,      // 12
    0xFF9A3DF2,   0x00000000, 0x00000000,      // 13
    0xFFA9BE60,   0x00000000, 0x00000000,      // 14
    0x00000000,   0x00000000, 0x00000000,      // 15
    0x00000000,   0x00000000, 0x00000000,      // 16
    0x00000000,   0x00000000, 0x00000000,      // 17
    0x00000000,   0x00000000, 0x00000000,      // 18
    0x00000000,   0x00000000, 0x00000000,      // 19
    0x00000000,   0x00000000, 0x00000000,      // 20
    0x00000000,   0x00000000, 0x00000000,      // 21
    0x00000000,   0x00000000, 0x00000000,      // 22
    0x00000000,   0x00000000, 0x00000000,      // 23
    0x00000000,   0x00000000, 0x00000000,      // 24
    0x00000000,   0x00000000, 0x00000000,      // 25
    0x00000000,   0x00000000, 0x00000000,      // 26
    0x00000000,   0x00000000, 0x00000000,      // 27
    0x00000000,   0x00000000, 0x00000000,      // 28
    0x00000000,   0x00000000, 0x00000000,      // 29
    0x00000000,   0x00000000, 0x00000000,      // 30
    0x00000000,   0x00000000, 0x00000000,      // 31
    0x00000000,   0x00000000, 0x00000000,      // 32
    0x00000000,   0x00000000, 0x00000000,      // 33
    0x00000000,   0x00000000, 0x00000000,      // 34
    0x00000000,   0x00000000, 0x00000000,      // 35
    0x00000000,   0x00000000, 0x00000000,      // 36
    0x00000000,   0x00000000, 0x00000000,      // 37
    0x00000000,   0x00000000, 0x00000000,      // 38
    0x00000000,   0x00000000, 0x00000000,      // 39
    0xFF7E8B5B,   0xFF45CA7F, 0xFFB343D5,      // 40
    0xFF8AA341,   0xFF4956AF, 0xFFBC44B0,      // 41
};
#endif
//-------测试波形数据，21次谐波，谐波含量10%---------
const u32 test_wave_U[128] =
{
    0xFFFFF692,
    0xFFFFF472,
    0xFFFFF5DB,
    0xFFFFF4DE,
    0xFFFFF312,
    0xFFFFF49A,
    0xFFFFF42B,
    0xFFFFF2EA,
    0xFFFFF45E,
    0xFFFFF478,
    0xFFFFF31C,
    0xFFFFF561,
    0xFFFFF608,
    0xFFFFF4C3,
    0xFFFFF73A,
    0xFFFFF850,
    0xFFFFF740,
    0xFFFFF9DF,
    0xFFFFFB57,
    0xFFFFFA6F,
    0xFFFFFD15,
    0xFFFFFED6,
    0xFFFFFE01,
    0x0000008D,
    0x00000283,
    0x000001A6,
    0x00000401,
    0x00000607,
    0x00000513,
    0x00000722,
    0x00000926,
    0x000007F6,
    0x00000998,
    0x00000B89,
    0x00000A19,
    0x00000B3E,
    0x00000CEA,
    0x00000B55,
    0x00000BED,
    0x00000D14,
    0x00000B8F,
    0x00000B9C,
    0x00000CDF,
    0x00000A85,
    0x00000A06,
    0x00000B37,
    0x000008A9,
    0x000007B8,
    0x000008B9,
    0x00000602,
    0x000004A9,
    0x00000587,
    0x000002CC,
    0x00000123,
    0x000001F8,
    0xFFFFFF54,
    0xFFFFFD78,
    0xFFFFFE57,
    0xFFFFFBDD,
    0xFFFFF9F6,
    0xFFFFFAF0,
    0xFFFFF8BD,
    0xFFFFF6DC,
    0xFFFFF80E,
    0xFFFFF692,
    0xFFFFF472,
    0xFFFFF5DB,
    0xFFFFF4DE,
    0xFFFFF312,
    0xFFFFF49A,
    0xFFFFF42B,
    0xFFFFF2EA,
    0xFFFFF45E,
    0xFFFFF478,
    0xFFFFF31C,
    0xFFFFF561,
    0xFFFFF608,
    0xFFFFF4C3,
    0xFFFFF73A,
    0xFFFFF850,
    0xFFFFF740,
    0xFFFFF9DF,
    0xFFFFFB57,
    0xFFFFFA6F,
    0xFFFFFD15,
    0xFFFFFED6,
    0xFFFFFE01,
    0x0000008D,
    0x00000283,
    0x000001A6,
    0x00000401,
    0x00000607,
    0x00000513,
    0x00000722,
    0x00000926,
    0x000007F6,
    0x00000998,
    0x00000B89,
    0x00000A19,
    0x00000B3E,
    0x00000CEA,
    0x00000B55,
    0x00000BED,
    0x00000D14,
    0x00000B8F,
    0x00000B9C,
    0x00000CDF,
    0x00000A85,
    0x00000A06,
    0x00000B37,
    0x000008A9,
    0x000007B8,
    0x000008B9,
    0x00000602,
    0x000004A9,
    0x00000587,
    0x000002CC,
    0x00000123,
    0x000001F8,
    0xFFFFFF54,
    0xFFFFFD78,
    0xFFFFFE57,
    0xFFFFFBDD,
    0xFFFFF9F6,
    0xFFFFFAF0,
    0xFFFFF8BD,
    0xFFFFF6DC,
    0xFFFFF80E,
};

//-----测试波形数据，21次谐波，谐波含量40%-----------------
const u32 test_wave_I[128] =
{
    0xFFFFFA6B,
    0xFFFFF602,
    0xFFFFFAEF,
    0xFFFFF93C,
    0xFFFFF4F8,
    0xFFFFF9F9,
    0xFFFFF8FE,
    0xFFFFF4A7,
    0xFFFFF9B6,
    0xFFFFF974,
    0xFFFFF509,
    0xFFFFFA16,
    0xFFFFFA98,
    0xFFFFF622,
    0xFFFFFB1E,
    0xFFFFFC4F,
    0xFFFFF7D3,
    0xFFFFFCAC,
    0xFFFFFE7F,
    0xFFFFF9FF,
    0xFFFFFE96,
    0x00000110,
    0xFFFFFC5E,
    0x000000A0,
    0x00000393,
    0xFFFFFEFF,
    0x000002CE,
    0x0000060C,
    0x00000154,
    0x000004AB,
    0x0000083D,
    0x0000035F,
    0x00000620,
    0x000009EC,
    0x000004EE,
    0x00000701,
    0x00000AFA,
    0x000005D6,
    0x0000073D,
    0x00000B52,
    0x00000612,
    0x000006C5,
    0x00000AF1,
    0x000005AE,
    0x0000059F,
    0x000009DC,
    0x0000049F,
    0x000003E2,
    0x0000082D,
    0x00000310,
    0x000001AA,
    0x00000609,
    0x00000122,
    0xFFFFFF11,
    0x000003A6,
    0xFFFFFF1C,
    0xFFFFFC8B,
    0x0000011A,
    0xFFFFFCEE,
    0xFFFFFA0F,
    0xFFFFFEC3,
    0xFFFFFB14,
    0xFFFFF7DB,
    0xFFFFFCBB,
    0xFFFFFA6B,
    0xFFFFF602,
    0xFFFFFAEF,
    0xFFFFF93C,
    0xFFFFF4F8,
    0xFFFFF9F9,
    0xFFFFF8FE,
    0xFFFFF4A7,
    0xFFFFF9B6,
    0xFFFFF974,
    0xFFFFF509,
    0xFFFFFA16,
    0xFFFFFA98,
    0xFFFFF622,
    0xFFFFFB1E,
    0xFFFFFC4F,
    0xFFFFF7D3,
    0xFFFFFCAC,
    0xFFFFFE7F,
    0xFFFFF9FF,
    0xFFFFFE96,
    0x00000110,
    0xFFFFFC5E,
    0x000000A0,
    0x00000393,
    0xFFFFFEFF,
    0x000002CE,
    0x0000060C,
    0x00000154,
    0x000004AB,
    0x0000083D,
    0x0000035F,
    0x00000620,
    0x000009EC,
    0x000004EE,
    0x00000701,
    0x00000AFA,
    0x000005D6,
    0x0000073D,
    0x00000B52,
    0x00000612,
    0x000006C5,
    0x00000AF1,
    0x000005AE,
    0x0000059F,
    0x000009DC,
    0x0000049F,
    0x000003E2,
    0x0000082D,
    0x00000310,
    0x000001AA,
    0x00000609,
    0x00000122,
    0xFFFFFF11,
    0x000003A6,
    0xFFFFFF1C,
    0xFFFFFC8B,
    0x0000011A,
    0xFFFFFCEE,
    0xFFFFFA0F,
    0xFFFFFEC3,
    0xFFFFFB14,
    0xFFFFF7DB,
    0xFFFFFCBB,
};

extern sHmWaveTypedef   sHmWave;
extern u32 WaveHmFftBuf[6][128];

/*********************************************************************************************************
** Function name:       fnHarmonic_GPCorrect
** Descriptions:     谐波 A  通道增益
** input parameters:    Stand:标准值
**                               Err:台体误差，3位整数，3位小数，单位 %
**                               n_Har:0xFF 所有谐波点校正值相同,1~21 校正基波或对应谐波点
** output parameters:   None
** Returned value:      SUCCESS  or ERROR
*********************************************************************************************************/
ErrorStatus fnHarmonic_GPCorrect(sCorrectTmp_TypeDef *Stand, u8 nphase, u8  n_Har)
{
    float ADErr;
    //sDataComm_TypeDef      EmuCommbuf;
    u8 i;
    u16 tempGP, len;

    if ((n_Har == 0) || ((n_Har > nHarmonic) && (n_Har != 0xFF)))
    {
        return ERROR;
    }

    if (Stand->Err[0])
    {
        ADErr = (float)Stand->Err[0] / 100000;

        ADErr = ((-ADErr) / (1 + ADErr));

        if (ADErr >= 0)
        {
            tempGP = (u16)(ADErr * 32768);
        }
        else
        {
            tempGP = (u16)(65535 + ADErr * 32768);
        }

        if (n_Har == 0xFF)
        {
            for (i = 0; i < nHarmonic; i++)
            {
                HarmonicData.PubPara.FftGP[nphase][i] += tempGP;
            }
        }
        else
        {
            HarmonicData.PubPara.FftGP[nphase][n_Har - 1] += tempGP;
        }
    }
    else
    {
        if (n_Har == 0xFF)
        {
            for (i = 0; i < nHarmonic; i++)
            {
                HarmonicData.PubPara.FftGP[nphase][i] = 0x00;
            }
        }
        else
        {
            HarmonicData.PubPara.FftGP[nphase][n_Har - 1] = 0x00;
        }
    }

    len = FileItemInfoLen_Harmonic_FftGP + FileItemInfoLen_Harmonic_FftCosAngle;
    HarmonicData.PubPara.Crc = 0x00;
    fnCrc_Check(0, (u8 *)&HarmonicData.PubPara,  len, (u8 *)&HarmonicData.PubPara.Crc);

    fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_Harmonic_FftGP, (u8 *)&HarmonicData.PubPara, len + 4);

    return SUCCESS;
}

/*********************************************************************************************************
** Function name:       fnHarmonic_PhsCorrect
** Descriptions:     谐波 相位校正
** input parameters:    Stand:标准值
**                               Err:台体误差，3位整数，3位小数，单位 %
**                               n_Har:0xFF 所有谐波点校正值相同,1~21 校正基波或对应谐波点
** output parameters:   None
** Returned value:      SUCCESS  or ERROR
*********************************************************************************************************/
ErrorStatus fnHarmonic_PhsCorrect(sCorrectTmp_TypeDef *Stand, u8 nphase, u8  n_Har)
{
    float ADErr;
    //sDataComm_TypeDef     EmuCommbuf;
    u8 i;
    u32 tempPhs;
    u16 len;

    if ((n_Har == 0) || ((n_Har > nHarmonic) && (n_Har != 0xFF)))
    {
        return ERROR;
    }

    if (Stand->Err[0])
    {
        ADErr = (float)Stand->Err[0] / 100000;

        ADErr = (asin(ADErr / 1.732)) * 57.29578 / 180; //--角度偏差---
        if (ADErr > 0)
        {
            tempPhs = ADErr * 2147483648;    //--------------
        }
        else
        {
            tempPhs = (4294967296 + ADErr * 2147483648);
        }

        if (n_Har == 0xFF)
        {
            for (i = 0; i < nHarmonic; i++)
            {
                HarmonicData.PubPara.FftCosAngle[nphase][i] += tempPhs;
            }
        }
        else
        {
            HarmonicData.PubPara.FftCosAngle[nphase][n_Har - 1] += tempPhs;
        }
    }
    else
    {
        if (n_Har == 0xFF)
        {
            for (i = 0; i < nHarmonic; i++)
            {
                HarmonicData.PubPara.FftCosAngle[nphase][i] = 0x00;
            }
        }
        else
        {
            HarmonicData.PubPara.FftCosAngle[nphase][n_Har - 1] = 0x00;
        }
    }

    len = FileItemInfoLen_Harmonic_FftGP + FileItemInfoLen_Harmonic_FftCosAngle;
    HarmonicData.PubPara.Crc = 0x00;
    fnCrc_Check(0, (u8 *)&HarmonicData.PubPara,  len, (u8 *)&HarmonicData.PubPara.Crc);

    fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_Harmonic_FftGP, (u8 *)&HarmonicData.PubPara, len + 4);

    return SUCCESS;
}

/*********************************************************************************************************
** Function name:       fnHarmonic_FirmParaCheck
** Descriptions:        谐波增益和相位补偿参数效验
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void fnHarmonic_FirmParaCheck(void)
{
    u8 i;
    u16  len;

    len = FileItemInfoLen_Harmonic_FftGP + FileItemInfoLen_Harmonic_FftCosAngle;
    for (i = 0; i < 3; i++)
    {
        if (fnCrc_Check(1, (u8 *)&HarmonicData.PubPara,  len, (u8 *)&HarmonicData.PubPara.Crc))       //-效验错误---
        {
            fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Harmonic_FftGP, (u8 *)&HarmonicData.PubPara, len + 4);
        }
        else  //--效验正确时退出-------
        {
            break;
        }
    }

    if (i == 3)
    {
        //-----参数恢复默认值----------
        Std_Memcpy((u8 *)&HarmonicData.PubPara.FftGP[0][0], (u8 *)&FftGP_Tab, FileItemInfoLen_Harmonic_FftGP);
        Std_Memcpy((u8 *)&HarmonicData.PubPara.FftCosAngle[0][0], (u8 *)&FftCosAngle_Tab, FileItemInfoLen_Harmonic_FftCosAngle);
    }
}

/*********************************************************************************************************
** Function name:       fnHarmonic_FirmParaInit
** Descriptions:        谐波增益和相位补偿参数初始化
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void fnHarmonic_FirmParaInit(void)
{
    u16  len;

    len = FileItemInfoLen_Harmonic_FftGP + FileItemInfoLen_Harmonic_FftCosAngle;

    Std_Memcpy((u8 *)&HarmonicData.PubPara.FftGP[0][0], (u8 *)&FftGP_Tab, FileItemInfoLen_Harmonic_FftGP);
    Std_Memcpy((u8 *)&HarmonicData.PubPara.FftCosAngle[0][0], (u8 *)&FftCosAngle_Tab, FileItemInfoLen_Harmonic_FftCosAngle);
    HarmonicData.PubPara.Crc = 0x00;
    fnCrc_Check(0, (u8 *)&HarmonicData.PubPara,  len, (u8 *)&HarmonicData.PubPara.Crc);

    fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_Harmonic_FftGP, (u8 *)&HarmonicData.PubPara, len + 4);
}

/*********************************************************************************************************
** Function name:       fnHarmonic_Exec
** Descriptions:        谐波计算总控程序,使用硬件加速进行FFT，只有B版本芯片支持
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void fnHarmonic_Exec(void)
{
    u16 i, j, iChPhs = 0;
    u32 IntCosAngle;
    //u32 FWaveTemp;
    s16 Temp_Pf;

    if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON) || (Inactive.PubData.InactiveStamp))
    {
        return;
    }

    for (iChPhs = 0; iChPhs < 3; iChPhs++)
    {
        // 读取基波电压寄存器
        MeasureRegTmp.FUrms[iChPhs] = 0;
        fnRN8302_Read(RN8302_FUA + iChPhs, (u8 *)&MeasureRegTmp.FUrms[iChPhs], 4);

        Bkgrd.PubData.FUrmsRdFlg = 0x5A;

        // 读取基波电流寄存器
        MeasureRegTmp.FIrms[iChPhs] = 0;
        fnRN8302_Read(RN8302_FIA + iChPhs, (u8 *)&MeasureRegTmp.FIrms[iChPhs], 4);
    }

    if (HarmonicData.PriPara.CtlFlag != Harmonic_Exe_CalcHPw)
    {
        return;
    }

    fnHarmonic_FirmParaCheck();

    //  // test
    //  fnHarmonic_D2fp_Exec(&MeasureRegTmp.Pw[3] , &MeasureRegTmp.Pw[7]); //谐波电能

    TestHarmonicTime[8] = TC0->CNT;

    HarmonicData.PriPara.CtlFlag = Harmonic_Exe_Idle;

    if (sHmWave.InPoint == 1)
    {
        sHmWave.OutPoint = 0;
    }
    else
    {
        sHmWave.OutPoint = 1;
    }

    memset(&WaveHmFftBuf[0][0], 0, 3072);

    //  for(i=0; i<128; i++)
    //  {
    //      WaveHmFftBuf[0][i] = sHmWave.sHm.HmSmplVal[sHmWave.OutPoint][k][0];
    //      WaveHmFftBuf[1][i] = sHmWave.sHm.HmSmplVal[sHmWave.OutPoint][k][1];
    //      WaveHmFftBuf[2][i] = sHmWave.sHm.HmSmplVal[sHmWave.OutPoint][k][2];
    //      WaveHmFftBuf[3][i] = sHmWave.sHm.HmSmplVal[sHmWave.OutPoint][k][3];
    //      WaveHmFftBuf[4][i] = sHmWave.sHm.HmSmplVal[sHmWave.OutPoint][k][4];
    //      WaveHmFftBuf[5][i] = sHmWave.sHm.HmSmplVal[sHmWave.OutPoint][k][5];
    //
    //      k += 2;
    //  }
    //
    //  for(i=0; i<6; i++)
    //  {
    //      Rn8xxx_DSP_Int2Fp((u32)((u32 *)&WaveHmFftBuf[i][0]) , (u32)((u32 *)&WaveHmFftBuf[i][0]) , 128 , 0 , 1);
    //  }

    // 整型转浮点数  整序输出 UA UB UC IA IB IC
    for (i = 0; i < 6; i++)
    {
        for (j = 0, iChPhs = 0; j < 128; j++)
        {
            WaveHmFftBuf[i][j] = sHmWave.sHm.HmSmplVal[sHmWave.OutPoint][iChPhs][i];

            iChPhs += 2;
        }

        Rn8xxx_DSP_Int2Fp((u32)((u32 *)&WaveHmFftBuf[i][0]), (u32)((u32 *)&WaveHmFftBuf[i][0]), 128, 0, 1);
    }

    //  memcpy(&WaveHmFftBuf[0][0], &test_wave_U[0], 128*4);
    //  Rn8xxx_DSP_Int2Fp((u32)((u32 *)&WaveHmFftBuf[0][0]) , (u32)((u32 *)&WaveHmFftBuf[0][0]) , 128 , 0 , 2);

    // 顺序为 UA UB UC IA IB IC
    for (i = 0; i < 6; i++)
    {
        Rn8xxx_DSP_BitReverse((u32)&HarmonicData.PriData.iRealArray[0], (u32)((u32 *)&WaveHmFftBuf[i][0]), 128);

        memset(&HarmonicData.PriData.iMageArray[0], 0x00, 512);

        Rn8xxx_DSP_FFT((u32)&HarmonicData.PriData.iRealArray[0], (u32)&HarmonicData.PriData.iMageArray[0], 0, 0, 128);
        // 实部、虚部 浮点数转整型
        Rn8xxx_DSP_Fp2Int((u32)&HarmonicData.PriData.iRealArray[0], (u32)&HarmonicData.PriData.iRealArray[0], 0, 128);
        Rn8xxx_DSP_Fp2Int((u32)&HarmonicData.PriData.iMageArray[0], (u32)&HarmonicData.PriData.iMageArray[0], 0, 128);

        // 基波
        Rn8xxx_DSP_FpSqrt((u32 *)&HarmonicData.PriData.iRealArray[1], (u32 *)&HarmonicData.PriData.iMageArray[1],
                          &Temp_Per.ftemp_Int, &IntCosAngle);

        Temp_Per.fBase_Int = Temp_Per.ftemp_Int;

        iChPhs = i % 3;

        // 电压 UA UB UC
        if (i < 3)
        {
            // 电压有效值低于阈值不处理谐波分析
            if (fnHarmonic_CheckUn(iChPhs) == 0)
            {
                memset((u8 *)&HarmonicData.PubData.HarmonicpercentU[iChPhs][0], 0x00, 2 * (nHarmonic + 1));
                memset((u8 *)&HarmonicData.PubData.HarmonicUrms[iChPhs][0], 0x00, 4 * (nHarmonic + 1));
                memset((u8 *)&HarmonicData.PubData.HarmonicPw[iChPhs][0], 0x00, 4 * (nHarmonic + 1));
                memset((u8 *)&HarmonicData.PubData.HarmonicPf[iChPhs][0], 0x00, 2 * (nHarmonic + 1));
                memset((u8 *)&HarmonicData.PubData.PtHarmonicPw[0], 0x00, 4);
                memset((u8 *)&HarmonicData.PubData.NtHarmonicPw[0], 0x00, 4);
                HarmonicData.PriData.FUrms[iChPhs] = 0;
                HarmonicData.PriData.FWaveUrms[iChPhs][HarmonicData.PriData.FWaveCnt] = 0;
                continue;
            }

            HarmonicData.PubData.HarmonicpercentU[iChPhs][0] = 10000;

            //          // 读取基波电压寄存器
            //          MeasureRegTmp.FUrms[iChPhs] = 0;
            //          fnRN8302_Read(RN8302_FUA + iChPhs, (u8 *)&MeasureRegTmp.FUrms[iChPhs], 4);

            // n次谐波
            for (j = 1; j < nHarmonic; j++)
            {
                Temp_Per.nMul = 0x3F800000;   // 补偿系数1

                Rn8xxx_DSP_FpSqrt((u32 *)&HarmonicData.PriData.iRealArray[j + 1], (u32 *)&HarmonicData.PriData.iMageArray[j + 1],
                                  &Temp_Per.ftemp_Int, &IntCosAngle);

                // 计算谐波含有率
                Rn8xxx_DSP_HPercent(&Temp_Per);

                HarmonicData.PubData.HarmonicpercentU[iChPhs][j] = (u16)Temp_Per.Hpercent;
                HarmonicData.PubData.HarmonicUrms[iChPhs][j] = (u32)((u64)MeasureRegTmp.FUrms[iChPhs] * Temp_Per.Hpercent / 10000);
                //              HarmonicData.PubData.HarmonicUrms[iChPhs][j] = (u32)((float)MeasureRegTmp.FUrms[iChPhs] / 10000 * Temp_Per.Hpercent);
                //              HarmonicData.PubData.HarmonicUrms[iChPhs][j] = (u32)((float)MeasureRegTmp.FUrms[iChPhs] * 0.1);

                HarmonicData.PriData.UIArcTan[iChPhs][j] = IntCosAngle;
                //              memcpy(&HarmonicData.PriData.UIArcTan[j], &IntCosAngle, 4);
                //              if(HarmonicData.PubData.HarmonicpercentU[iChPhs][j] < Harmonic_StarPercent)
                //              {
                //                  HarmonicData.PubData.HarmonicpercentU[iChPhs][j] = 0;
                //                  HarmonicData.PubData.HarmonicUrms[iChPhs][j] = 0;
                //
                //                  HarmonicData.PriData.UIArcTan[iChPhs][j] = 0;
                //              }

                HarmonicData.PubData.HarmonicUrmsSUM[iChPhs][j] += HarmonicData.PubData.HarmonicUrms[iChPhs][j];
            }
        }
        // 电流 IA IB IC
        else
        {
            // 电流有效值低于阈值不处理谐波分析
            if (fnHarmonic_CheckI(iChPhs) == 0)
            {
                memset((u8 *)&HarmonicData.PubData.HarmonicpercentI[iChPhs][0], 0x00, 2 * (nHarmonic + 1));
                memset((u8 *)&HarmonicData.PubData.HarmonicIrms[iChPhs][0], 0x00, 4 * (nHarmonic + 1));
                memset((u8 *)&HarmonicData.PubData.HarmonicPw[iChPhs][0], 0x00, 4 * (nHarmonic + 1));
                memset((u8 *)&HarmonicData.PubData.HarmonicPf[iChPhs][0], 0x00, 2 * (nHarmonic + 1));
                memset((u8 *)&HarmonicData.PubData.PtHarmonicPw[0], 0x00, 4 * (nPhs + 1));
                memset((u8 *)&HarmonicData.PubData.NtHarmonicPw[0], 0x00, 4 * (nPhs + 1));
                HarmonicData.PriData.FIrms[iChPhs] = 0;
                HarmonicData.PriData.FWaveIrms[iChPhs][HarmonicData.PriData.FWaveCnt] = 0;

                continue;
            }

            HarmonicData.PubData.HarmonicpercentI[iChPhs][0] = 10000;

            //          // 读取基波电流寄存器
            //          MeasureRegTmp.FIrms[iChPhs] = 0;
            //          fnRN8302_Read(RN8302_FIA + iChPhs, (u8 *)&MeasureRegTmp.FIrms[iChPhs], 4);

            // n次谐波
            for (j = 1; j < nHarmonic; j++)
            {
                Temp_Per.nMul = 0x3F800000;   // 补偿系数1

                Rn8xxx_DSP_FpSqrt((u32 *)&HarmonicData.PriData.iRealArray[j + 1], (u32 *)&HarmonicData.PriData.iMageArray[j + 1],
                                  &Temp_Per.ftemp_Int, &IntCosAngle);

                // 计算谐波含有率
                Rn8xxx_DSP_HPercent(&Temp_Per);

                HarmonicData.PubData.HarmonicpercentI[iChPhs][j] = (u16)Temp_Per.Hpercent;
                HarmonicData.PubData.HarmonicIrms[iChPhs][j] = (u32)((u64)MeasureRegTmp.FIrms[iChPhs] * Temp_Per.Hpercent / 10000) ;
                //              HarmonicData.PubData.HarmonicIrms[iChPhs][j] = (u32)((float)MeasureRegTmp.FIrms[iChPhs] / 10000 * Temp_Per.Hpercent) ;
                //              HarmonicData.PubData.HarmonicIrms[iChPhs][j] = (u32)((float)MeasureRegTmp.FIrms[iChPhs] * 0.4) ;

                //              if( (HarmonicData.PubData.HarmonicpercentU[iChPhs][j] > Harmonic_StarPercent)
                //                  && (HarmonicData.PubData.HarmonicpercentI[iChPhs][j] > Harmonic_StarPercent) )
                if ((HarmonicData.PubData.HarmonicIrms[iChPhs][j]) && (HarmonicData.PubData.HarmonicUrms[iChPhs][j]))
                {
                    Temp_HPf.AngleU = HarmonicData.PriData.UIArcTan[iChPhs][j];

                    #if(Harmonic_Modify_EnORDis == Harmonic_Modify_Enable)
                    IntCosAngle += HarmonicData.PubPara.FftCosAngle[iChPhs][j];  //FftCosAngle_Tab=(Angle/180)*2^31   Angle为角度值单位：度,Angle=(ASIN(-Err/1.732)*180/3.1415926)
                    #endif

                    Temp_HPf.AngleI = IntCosAngle;
                    //                  memcpy(&Temp_HPf.AngleI, &IntCosAngle, 4);
                    Rn8xxx_DSP_Sin_Cos(HarmonicData.PriData.UIArcTan[iChPhs][j], &Temp_HPf.CosAngleU, &Temp_HPf.SinAngleU_Fi);  //COS( AngleU)  SIN ( AngleU)
                    Rn8xxx_DSP_Sin_Cos(IntCosAngle, &Temp_HPf.CosAngleI_Fu,  &Temp_HPf.SinAngleI_Gp);  //COS( AngleI)  SIN ( AngleI)
                    Temp_Pf = Rn8xxx_DSP_HPf(&Temp_HPf);                // 计算功率因数及谐波相角

                    if (Temp_Pf < 0)
                    {
                        HarmonicData.PubData.HarmonicPf[iChPhs][j] = (-Temp_Pf + 1) | 0x8000;
                    }
                    else
                    {
                        HarmonicData.PubData.HarmonicPf[iChPhs][j] = (u16)Temp_Pf;
                    }

                    HarmonicData.PubData.HarmonicAngle[iChPhs][j] = Temp_HPf.AngleH_UI;
                    Temp_HPf.CosAngleI_Fu = (HarmonicData.PubData.HarmonicUrms[iChPhs][j] >> 4) + 1;
                    Temp_HPf.SinAngleU_Fi = (HarmonicData.PubData.HarmonicIrms[iChPhs][j] >> 4) + 1;
                    Temp_HPf.SinAngleI_Gp = 0;

                    #if(Harmonic_Modify_EnORDis == Harmonic_Modify_Enable)
                    Temp_HPf.SinAngleI_Gp += (u32)HarmonicData.PubPara.FftGP[iChPhs][j]; //FftGP_Tab:Gain=-Err/(1+Err),若Gain>=0,GPA=INT[Gain*215];若Gain<0,GPA=INT[216+Gain*215]
                    #endif

                    HarmonicData.PubData.HarmonicPw[iChPhs][j] = Rn8xxx_DSP_Pw(&Temp_HPf);
                }
                //              else
                //              {
                //                  if((HarmonicData.PubData.HarmonicpercentI[iChPhs][j] < Harmonic_StarPercent))
                //                  {
                //                      HarmonicData.PubData.HarmonicpercentI[iChPhs][j] = 0;
                //                      HarmonicData.PubData.HarmonicIrms[iChPhs][j] = 0;
                //                      HarmonicData.PubData.HarmonicPw[iChPhs][j] = 0;
                //                      HarmonicData.PubData.HarmonicPf[iChPhs][j] = 100;
                //                      HarmonicData.PubData.HarmonicAngle[iChPhs][j] =0;
                //                  }
                //              }

                HarmonicData.PubData.HarmonicIrmsSUM[iChPhs][j] += HarmonicData.PubData.HarmonicIrms[iChPhs][j];
                HarmonicData.PubData.HarmonicPwSUM[iChPhs][j] += HarmonicData.PubData.HarmonicPw[iChPhs][j];
            }
        }
    }

    HarmonicData.PubData.HarmonicRMSCNT++;

    if (HarmonicData.PubData.HarmonicRMSCNT > HRMS_AVERAGE_MUN)
    {
        for (j = 0; j < nPhs; j++)
        {
            for (i = 0; i < nHarmonic; i++)
            {
                if (HarmonicData.PubData.HarmonicUrmsSUM[j][i])
                {
                    HarmonicData.PubData.Harmonic_SUrms[j][i] = HarmonicData.PubData.HarmonicUrmsSUM[j][i] / HarmonicData.PubData.HarmonicRMSCNT;
                }
                else
                {
                    HarmonicData.PubData.Harmonic_SUrms[j][i] = 0x00;
                }

                if (HarmonicData.PubData.HarmonicIrmsSUM[j][i])
                {
                    HarmonicData.PubData.Harmonic_SIrms[j][i] = HarmonicData.PubData.HarmonicIrmsSUM[j][i] / HarmonicData.PubData.HarmonicRMSCNT;
                }
                else
                {
                    HarmonicData.PubData.Harmonic_SIrms[j][i] = 0x00;
                }

                if (HarmonicData.PubData.HarmonicPwSUM[j][i])
                {
                    HarmonicData.PubData.Harmonic_SPw[j][i] = HarmonicData.PubData.HarmonicPwSUM[j][i] / HarmonicData.PubData.HarmonicRMSCNT;
                }
                else
                {
                    HarmonicData.PubData.Harmonic_SPw[j][i] = 0x00;
                }
            }
        }

        HarmonicData.PubData.HarmonicRMSCNT = 0;

        memset((u8 *)&HarmonicData.PubData.HarmonicUrmsSUM[0][0], 0x00, (nHarmonic + 1) * 12 + 4);
    }

    HarmonicData.PriData.FWaveCnt++;
    if (HarmonicData.PriData.FWaveCnt > 4)
    {
        HarmonicData.PriData.FWaveCnt = 0;
        HarmonicData.PriData.FWaveFlag = 0x5a;
    }
    for (i = 0; i < (nPhs + 1); i++)
    {
        HarmonicData.PubData.PtHarmonicPw[i] = 0;
        HarmonicData.PubData.NtHarmonicPw[i] = 0;
    }

    for (j = 0; j < nPhs; j++)
    {
        // 计算分相谐波电能
        for (i = 1; i < nHarmonic; i++)
        {
            if (HarmonicData.PubData.HarmonicPw[j][i] < 0)
            {
                HarmonicData.PubData.NtHarmonicPw[j + 1] += HarmonicData.PubData.HarmonicPw[j][i];
            }
            else
            {
                HarmonicData.PubData.PtHarmonicPw[j + 1] += HarmonicData.PubData.HarmonicPw[j][i];
            }
        }
    }

    // 计算总谐波电能
    for (j = 0; j < nPhs; j++)
    {
        HarmonicData.PubData.PtHarmonicPw[0] += HarmonicData.PubData.PtHarmonicPw[j + 1];
        HarmonicData.PubData.NtHarmonicPw[0] += HarmonicData.PubData.NtHarmonicPw[j + 1];
    }

    fnHarmonic_D2fp_Exec(&HarmonicData.PubData.PtHarmonicPw[0], &HarmonicData.PubData.NtHarmonicPw[0]);  //谐波电能

    //  fnHarmonic_FEgSh_D2fp_Exec(&HarmonicData.PubData.HarmonicPw[0][0]);   //基波电能

    //SEGGER_RTT_printf(0, "HarmonicPw = %d\r\n" , HarmonicData.PubData.HarmonicPw[0][0]);
    //SEGGER_RTT_printf(0, "MeasureRPw = %d\r\n" , MeasureRegTmp.Pw[0]);

    //SEGGER_RTT_printf(0, "PtHarmonicPw[0] = %d\r\n" , HarmonicData.PubData.PtHarmonicPw[0]);
    //SEGGER_RTT_printf(0, "HarmonicpercentU[0][2] = %d\r\n" , HarmonicData.PubData.HarmonicpercentU[0][2]);
    //SEGGER_RTT_printf(0, "HarmonicpercentI[0][2] = %d\r\n" , HarmonicData.PubData.HarmonicpercentI[0][2]);

    for (j = 0; j < nPhs; j++)
    {
        //------U-------
        Rn8xxx_DSP_U16I2Fp((u32 *)&HarmonicData.PriData.iMageArray[0], (u16 *)&HarmonicData.PubData.HarmonicpercentU[j][1], nHarmonic - 1);
        HarmonicData.PubData.HarmonicThdU[j] = Rn8xxx_DSP_CalcThd((u32 *)&HarmonicData.PriData.iMageArray[0], nHarmonic - 1);

        //      HarmonicData.PubData.HarmonicThdUrms[j] = Rn8xxx_DSP_CalcThdRms(HarmonicData.PubData.HarmonicThdU[j] ,HarmonicData.PriData.FUrms[j]);

        //------I---------
        Rn8xxx_DSP_U16I2Fp((u32 *)&HarmonicData.PriData.iMageArray[0], (u16 *)&HarmonicData.PubData.HarmonicpercentI[j][1], nHarmonic - 1);
        HarmonicData.PubData.HarmonicThdI[j] = Rn8xxx_DSP_CalcThd((u32 *)&HarmonicData.PriData.iMageArray[0], nHarmonic - 1);
        //      HarmonicData.PubData.HarmonicThdIrms[j] = Rn8xxx_DSP_CalcThdRms(HarmonicData.PubData.HarmonicThdI[j] ,HarmonicData.PriData.FIrms[j]);
    }

    TestHarmonicTime[9] = TC0->CNT;
}
