#ifndef _Harmonic_H
#define _Harmonic_H

#ifdef   _Harmonic_GLOBALS
#define  Harmonic_EXT
#else
#define  Harmonic_EXT  extern
#endif

#define FFT_DMA_Mode            1               // 0: FFT使用软件计算，1：FFT使用硬件加速，

#if(nPhs == SinglePhs)
#define nHarmonic               21              // 计算谐波次数,0为基波
#else
#define nHarmonic               41
#endif
#define Harmonic_StarPercent    30              /*"谐波潜动阀值，为0.3%;国网测试最低到0.5%"*/
#define  Harmonic_Modify_Disable    0
#define  Harmonic_Modify_Enable     1

#define  Harmonic_Modify_EnORDis         Harmonic_Modify_Enable    //谐波补偿开关

#define FFT_TO_URMS_Ku   0x3D000000 //(4/NUM_FFT) = 0.03125,  0x3D000000 为0.03125 浮点数，修改NUM_FFT时此值需重新计算
#define FFT_TO_IRMS_Ki   0x3D000000 //0x3D000000 为0.03125 浮点数，修改NUM_FFT时此值需重新计算

#define  HRMS_AVERAGE_MUN  9     //----40*(HRMS_AVERAGE_MUN + 1)毫秒刷新-------

typedef enum
{
    Harmonic_Exe_Idle,
    Harmonic_Exe_ReadData,
    Harmonic_Exe_CalcHPw,
} eHarmonicExeFlag_TypeDef;

typedef struct
{
    struct HarmonicPriData
    {
        float iRealArray[NUM_FFT];
        float iMageArray[NUM_FFT];

        u32 UIArcTan[nPhs][nHarmonic + 1];      // 保存电压通道计算角度值的COS SIN

        u32 FUrms[nPhs];                        // 读取电压基波值
        u32 FIrms[nPhs];
        u32 FWaveUrms[nPhs][5];                 // 基波全波有效值,存前4个点，与当前点，总5个点求平均
        u32 FWaveIrms[nPhs][5];
        u8  FWaveCnt;                           // 基波计算平均值计数
        u8  FWaveFlag;                          // 基波计算5点满标志
    } PriData;

    struct HarmonicPriPara
    {
        u8  Channel;                            // 当前采样通道
        eHarmonicExeFlag_TypeDef  CtlFlag;      // 开始进行谐波数据分析
    } PriPara;

    struct HarmonicPubPara
    {
        u16 FftGP[nPhs][nHarmonic + 1];         // 增益校正补偿，默认补-0.6%，可通讯设置,多一个变量为字节对齐用
        u32 FftCosAngle[nPhs][nHarmonic];       // 通道相位校正补偿，默认补-0.6%，可通讯设置
        u32 Crc;
    } PubPara;

    struct HarmonicPubData
    {
        u16 HarmonicpercentU[nPhs][nHarmonic];
        u16 HarmonicpercentI[nPhs][nHarmonic];  //---谐波含有率--XX.XX%
        u32 HarmonicUrms[nPhs][nHarmonic + 1];      //40ms刷新，基波 各次谐波有效值，无量纲，与计量芯片寄存器同理，根据需要转换得到想要结果
        u32 HarmonicIrms[nPhs][nHarmonic + 1];      //40ms刷新，基波各次谐波有效值，无量纲
        s32 HarmonicPw[nPhs][nHarmonic + 1];        //40ms刷新， 基波各次谐波功率，已校正，无谐波时，基波值与计量芯片rms 相等
        u16 HarmonicPf[nPhs][nHarmonic + 1];        // 谐波功率因数A,B,C
        u16 HarmonicAngle[nPhs][nHarmonic + 1];     //---谐波相角 XXX.X
        s32 PtHarmonicPw[nPhs + 1];                 // 总正向谐波电能 + A/B/C分向
        s32 NtHarmonicPw[nPhs + 1];                 // 总反向谐波电能 + A/B/C分向
        u16 HarmonicThdU[nPhs];                     //---电压总谐波含有率--XX.XX%
        u16 HarmonicThdI[nPhs];//---电流总谐波含有率--XX.XX%
        u32 HarmonicThdUrms[nPhs];//---电压总谐波有效值
        u32 HarmonicThdIrms[nPhs];//---电压总谐波有效值

        u32 HarmonicUrmsSUM[nPhs][nHarmonic + 1];   //基波 各次谐波1秒有效值累加和，无量纲，与计量芯片寄存器同理，根据需要转换得到想要结果
        u32 HarmonicIrmsSUM[nPhs][nHarmonic + 1];   //基波各次谐波1秒有效值累加和，无量纲
        s32 HarmonicPwSUM[nPhs][nHarmonic + 1];         // 基波各次谐波1秒有效值累加和，已校正，无谐波时，基波值与计量芯片rms 相等
        u8  HarmonicRMSCNT;

        u32 Harmonic_SUrms[nPhs][nHarmonic + 1];    //慢速,默认1s刷新，基波 各次谐波有效值，无量纲，与计量芯片寄存器同理，根据需要转换得到想要结果
        u32 Harmonic_SIrms[nPhs][nHarmonic + 1];    //慢速,默认1s刷新，基波各次谐波有效值，无量纲
        s32 Harmonic_SPw[nPhs][nHarmonic + 1];          //1s刷新， 基波各次谐波功率，已校正，无谐波时，基波值与计量芯片rms 相等
    } PubData;
} sHarmonicData_TypeDef;

Harmonic_EXT sHarmonicData_TypeDef HarmonicData;

extern  void fnHarmonic_FFT(float *dataR, float *dataI);
extern  void SampleDataModifyF(float *piRetValue, u8 *Dst);
extern  void fnHarmonic_Exec(void);
extern  void fnHarmonic_Init(void);
extern  void fnHarmonic_D2fp_Exec(s32 *PtHPw, s32 *NtHPw);

extern void fnHarmonic_FirmParaCheck(void);
extern void fnHarmonic_FirmParaInit(void);
extern ErrorStatus fnHarmonic_GPCorrect(sCorrectTmp_TypeDef *Stand, u8 nphase, u8  n_Har);
extern ErrorStatus fnHarmonic_PhsCorrect(sCorrectTmp_TypeDef *Stand, u8 nphase, u8  n_Har);

#endif
