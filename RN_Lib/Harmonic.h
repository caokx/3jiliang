#ifndef _Harmonic_H
#define _Harmonic_H

#ifdef   _Harmonic_GLOBALS
#define  Harmonic_EXT
#else
#define  Harmonic_EXT  extern
#endif

#define FFT_DMA_Mode            1               // 0: FFTʹ��������㣬1��FFTʹ��Ӳ�����٣�

#if(nPhs == SinglePhs)
#define nHarmonic               21              // ����г������,0Ϊ����
#else
#define nHarmonic               41
#endif
#define Harmonic_StarPercent    30              /*"г��Ǳ����ֵ��Ϊ0.3%;����������͵�0.5%"*/
#define  Harmonic_Modify_Disable    0
#define  Harmonic_Modify_Enable     1

#define  Harmonic_Modify_EnORDis         Harmonic_Modify_Enable    //г����������

#define FFT_TO_URMS_Ku   0x3D000000 //(4/NUM_FFT) = 0.03125,  0x3D000000 Ϊ0.03125 ���������޸�NUM_FFTʱ��ֵ�����¼���
#define FFT_TO_IRMS_Ki   0x3D000000 //0x3D000000 Ϊ0.03125 ���������޸�NUM_FFTʱ��ֵ�����¼���

#define  HRMS_AVERAGE_MUN  9     //----40*(HRMS_AVERAGE_MUN + 1)����ˢ��-------

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

        u32 UIArcTan[nPhs][nHarmonic + 1];      // �����ѹͨ������Ƕ�ֵ��COS SIN

        u32 FUrms[nPhs];                        // ��ȡ��ѹ����ֵ
        u32 FIrms[nPhs];
        u32 FWaveUrms[nPhs][5];                 // ����ȫ����Чֵ,��ǰ4���㣬�뵱ǰ�㣬��5������ƽ��
        u32 FWaveIrms[nPhs][5];
        u8  FWaveCnt;                           // ��������ƽ��ֵ����
        u8  FWaveFlag;                          // ��������5������־
    } PriData;

    struct HarmonicPriPara
    {
        u8  Channel;                            // ��ǰ����ͨ��
        eHarmonicExeFlag_TypeDef  CtlFlag;      // ��ʼ����г�����ݷ���
    } PriPara;

    struct HarmonicPubPara
    {
        u16 FftGP[nPhs][nHarmonic + 1];         // ����У��������Ĭ�ϲ�-0.6%����ͨѶ����,��һ������Ϊ�ֽڶ�����
        u32 FftCosAngle[nPhs][nHarmonic];       // ͨ����λУ��������Ĭ�ϲ�-0.6%����ͨѶ����
        u32 Crc;
    } PubPara;

    struct HarmonicPubData
    {
        u16 HarmonicpercentU[nPhs][nHarmonic];
        u16 HarmonicpercentI[nPhs][nHarmonic];  //---г��������--XX.XX%
        u32 HarmonicUrms[nPhs][nHarmonic + 1];      //40msˢ�£����� ����г����Чֵ�������٣������оƬ�Ĵ���ͬ��������Ҫת���õ���Ҫ���
        u32 HarmonicIrms[nPhs][nHarmonic + 1];      //40msˢ�£���������г����Чֵ��������
        s32 HarmonicPw[nPhs][nHarmonic + 1];        //40msˢ�£� ��������г�����ʣ���У������г��ʱ������ֵ�����оƬrms ���
        u16 HarmonicPf[nPhs][nHarmonic + 1];        // г����������A,B,C
        u16 HarmonicAngle[nPhs][nHarmonic + 1];     //---г����� XXX.X
        s32 PtHarmonicPw[nPhs + 1];                 // ������г������ + A/B/C����
        s32 NtHarmonicPw[nPhs + 1];                 // �ܷ���г������ + A/B/C����
        u16 HarmonicThdU[nPhs];                     //---��ѹ��г��������--XX.XX%
        u16 HarmonicThdI[nPhs];//---������г��������--XX.XX%
        u32 HarmonicThdUrms[nPhs];//---��ѹ��г����Чֵ
        u32 HarmonicThdIrms[nPhs];//---��ѹ��г����Чֵ

        u32 HarmonicUrmsSUM[nPhs][nHarmonic + 1];   //���� ����г��1����Чֵ�ۼӺͣ������٣������оƬ�Ĵ���ͬ��������Ҫת���õ���Ҫ���
        u32 HarmonicIrmsSUM[nPhs][nHarmonic + 1];   //��������г��1����Чֵ�ۼӺͣ�������
        s32 HarmonicPwSUM[nPhs][nHarmonic + 1];         // ��������г��1����Чֵ�ۼӺͣ���У������г��ʱ������ֵ�����оƬrms ���
        u8  HarmonicRMSCNT;

        u32 Harmonic_SUrms[nPhs][nHarmonic + 1];    //����,Ĭ��1sˢ�£����� ����г����Чֵ�������٣������оƬ�Ĵ���ͬ��������Ҫת���õ���Ҫ���
        u32 Harmonic_SIrms[nPhs][nHarmonic + 1];    //����,Ĭ��1sˢ�£���������г����Чֵ��������
        s32 Harmonic_SPw[nPhs][nHarmonic + 1];          //1sˢ�£� ��������г�����ʣ���У������г��ʱ������ֵ�����оƬrms ���
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
