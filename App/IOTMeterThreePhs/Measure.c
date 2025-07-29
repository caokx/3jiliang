
#include <Includes.h>
#include "ProDefine.h"

//--------��������Ĭ������---------------------------------
// 3*220V 10A
const sMeasureFirmPara_TypeDef FirmParaDefault _reserve =
{
    0x04,    //FractionI
    0x02,    //FractionU
    0x04,    //FractionE
    0x04,    //FractionP
    0x0040,  //Pulse_deltaE
    DefaultHighPulseRate,  //HighPulseRate
    0x0B04,     //HFConst1
    0x0178,     //Start_Ps
    0x01A3,     //Start_Q
    0x0400,     //LostVoltT
    0x0002,     //Zxot
    {0x0000, 0x0000, 0x0000, 0x0000}, //PRth
    {0x80, 0x80, 0x80},             //PHSU
    {0x808080, 0x808080, 0x808080}, //PHSI
    {0x0000, 0x0000, 0x0000},       //GSU
    {0x0000, 0x0000, 0x0000, 0x0000}, //GSI
    {0x0000, 0x0000, 0x0000},       //U_OS
    {0x0000, 0x0000, 0x0000, 0x0000}, //I_OS
    {0x0000, 0x0000, 0x0000},   //GP
    {0x0000, 0x0000, 0x0000},   //GQ
    {0x0000, 0x0000, 0x0000},   //GS
    {0x0000, 0x0000, 0x0000},   //P_PHS
    {0x0000, 0x0000, 0x0000},   //Q_PHS
    {0x0000, 0x0000, 0x0000},   //P_OS
    {0x0000, 0x0000, 0x0000},   //Q_OS
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //P_PHSMH
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //Q_PHSMH
    0x00FF0F49,     //ChkSum1

    0x393,          //��ѹϵ��
    0x00001787,     //����ϵ��
    0x0223,         //����ϵ��

    22000,          //RatedU
    19461570,       //RatedUrms
    10000,          //RatedI
    6827797,        //RatedIrms
    {220000, 220000, 220000},   //RealU
    {100000, 100000, 100000, 100000}, //RealI
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //RealAngle
    {0x0000, 0x0000, 0x0000},   //RealPw
    128     //�����������
};

// 3*220V 1.5A
const sMeasureFirmPara_TypeDef FirmParaDefault220_1_5 _reserve =
{
    0x04,    //FractionI
    0x02,    //FractionU
    0x04,    //FractionE
    0x04,    //FractionP
    0x0040,  //Pulse_deltaE
    DefaultHighPulseRate,  //HighPulseRate
    0x0F1E,     //HFConst1 0x0b04
    0x0096,     //Start_Ps
    0x0096,     //Start_Q
    0x0400,     //LostVoltT
    0x0009,     //Zxot
    {0x0000, 0x0000, 0x0000, 0x0000}, //PRth
    {0x80, 0x80, 0x80},             //PHSU
    {0x808080, 0x808080, 0x808080}, //PHSI
    {0x0000, 0x0000, 0x0000},       //GSU
    {0x0000, 0x0000, 0x0000, 0x0000}, //GSI
    {0x0000, 0x0000, 0x0000},       //U_OS
    {0x0000, 0x0000, 0x0000, 0x0000}, //I_OS
    {0x0000, 0x0000, 0x0000},   //GP
    {0x0000, 0x0000, 0x0000},   //GQ
    {0x0000, 0x0000, 0x0000},   //GS
    {0x0000, 0x0000, 0x0000},   //P_PHS
    {0x0000, 0x0000, 0x0000},   //Q_PHS
    {0x0000, 0x0000, 0x0000},   //P_OS
    {0x0000, 0x0000, 0x0000},   //Q_OS
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //P_PHSMH
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //Q_PHSMH
    0x0040ACC0,     //ChkSum1

    0x375,          //��ѹϵ��
    0x00014E09,     //����ϵ�� 0x00001787
    0x2339,         //����ϵ��

    22000,          //RatedU
    0x0128F5C2,     //RatedUrms
    1500,           //RatedI
    0x00C3B962,     //RatedIrms
    {220000, 220000, 220000},   //RealU
    {15000, 15000, 15000, 15000}, //RealI
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //RealAngle
    {0x0000, 0x0000, 0x0000},   //RealPw
    128     //�����������
};

// dyf 3*57.7V 1.5A
const sMeasureFirmPara_TypeDef FirmParaDefault577_1_5 _reserve =
{
    0x04,    //FractionI
    0x02,    //FractionU
    0x04,    //FractionE
    0x04,    //FractionP
    0x0040,  //Pulse_deltaE
    DefaultHighPulseRate,  //HighPulseRate
    0x07B2,     //HFConst1
    0x0642,     //Start_Ps
    0x0642,     //Start_Q
    0x0400,     //LostVoltT
    0x0009,     //Zxot
    {0x0000, 0x0000, 0x0000, 0x0000}, //PRth
    {0x80, 0x80, 0x80},             //PHSU
    {0x808080, 0x808080, 0x808080}, //PHSI
    {0x0000, 0x0000, 0x0000},       //GSU
    {0x0000, 0x0000, 0x0000, 0x0000}, //GSI
    {0x0000, 0x0000, 0x0000},       //U_OS
    {0x0000, 0x0000, 0x0000, 0x0000}, //I_OS
    {0x0000, 0x0000, 0x0000},   //GP
    {0x0000, 0x0000, 0x0000},   //GQ
    {0x0000, 0x0000, 0x0000},   //GS
    {0x0000, 0x0000, 0x0000},   //P_PHS
    {0x0000, 0x0000, 0x0000},   //Q_PHS
    {0x0000, 0x0000, 0x0000},   //P_OS
    {0x0000, 0x0000, 0x0000},   //Q_OS
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //P_PHSMH
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //Q_PHSMH
    0x0040B4EC,     //ChkSum1

    0x385,          //��ѹϵ��
    0x00014DC1,     //����ϵ��
    0x23DC,         //����ϵ��

    5770,           //RatedU
    0x004F5C28,     //RatedUrms
    1500,           //RatedI
    0x00C38F44,     //RatedIrms
    {57700, 57700, 57700},      //RealU
    {15000, 15000, 15000, 15000}, //RealI
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //RealAngle
    {0x0000, 0x0000, 0x0000},   //RealPw
    128     //�����������
};

/*****************************************************************************
** Function name:   fnRN8302_HSDCMode_Init(void)
**
** Description:
**
** Parameters:      NONE
**
** Returned value:  NONE
**
******************************************************************************/
void fnRN8302_HSDCMode_Init(void)
{
    sDataComm_TypeDef      EmuCommbuf;

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // дʹ��λ
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTempBuf[0] = 0xAA;
    EmuCommbuf.ucTempBuf[1] = RN8302_WREN_EN;   // WREN2�Ĵ���ʹ��
    EmuCommbuf.ucTempBuf[2] = 0;
    EmuCommbuf.ucTempBuf[3] = 0;
    fnRN8302_Write(RN8302_WREN2, EmuCommbuf.ucTempBuf, 4);

    fnRN8302_Read(RN8302_SYSCFG, EmuCommbuf.ucTempBuf, 4);
    EmuCommbuf.lTemp32 |= (0xEA000000 | 0x1000);
    fnRN8302_Write(RN8302_SYSCFG, EmuCommbuf.ucTempBuf, 4);

    //��λMMU���λ���DMA
    EmuCommbuf.ucTempBuf[0] = 0xE1;
    fnRN8302_Write(RN8302_SOFTRST, EmuCommbuf.ucTempBuf, 1);
    //��λHSDC
    EmuCommbuf.ucTempBuf[0] = 0x4C;
    fnRN8302_Write(RN8302_SOFTRST, EmuCommbuf.ucTempBuf, 1);

    //      /*"Step3:����HSDC��SPI  ģʽ  "*/
    //      EmuCommbuf.lTemp32 = 0x04;
    //      fnRN8302_Write(RN8306_HDSC_CTRL,EmuCommbuf.ucTempBuf,4);

    /*"Step4:���ò��θ�ʽ��EMMDMAģʽ  "*/
    /*"UA UB UC IA IB IC  �̶�256 "*/
    EmuCommbuf.ucTempBuf[0] = 0x80;//0x00;
    fnRN8302_Write(RN8302_WSAVECON, EmuCommbuf.ucTempBuf, 1);
    EmuCommbuf.lTemp32 = 0;//0x13F0;
    EmuCommbuf.ucTempBuf[0] = 0x04;
    fnRN8302_Write(RN8302_DMA_WAVECON, EmuCommbuf.ucTempBuf, 4);
    EmuCommbuf.lTemp32 = 0xC00;     // ���滺��
    fnRN8302_Write(RN8306_DMA_WAVECON3, EmuCommbuf.ucTempBuf, 4);

    /*"Step5:����HSDC��SPI    "*/
    EmuCommbuf.ucTempBuf[0] = 0x0D; // ����HSDC ��У��  4.096Mhz
    EmuCommbuf.ucTempBuf[1] = 0x04;         // ���ֽڷ���---�ȷ����ֽ�  �ۼ�У���
    EmuCommbuf.ucTempBuf[2] = 0;
    EmuCommbuf.ucTempBuf[3] = 0;
    fnRN8302_Write(RN8306_HDSC_CTRL, EmuCommbuf.ucTempBuf, 4);

    /*"Step6:����EMMDMAģʽ    "*/
    EmuCommbuf.lTemp32 = 0xC00 | 0x01; //0x01; // ���滺��
    fnRN8302_Write(RN8306_DMA_WAVECON3, EmuCommbuf.ucTempBuf, 4);

    EmuCommbuf.ucTempBuf[0] = 0x00;
    EmuCommbuf.ucTempBuf[1] = 0x07;   //EmuCommbuf.ucTempBuf[1] = 0x05;
    EmuCommbuf.ucTempBuf[2] = 0;
    EmuCommbuf.ucTempBuf[3] = 0;
    fnRN8302_Write(RN8302_DMA_WAVECON2, EmuCommbuf.ucTempBuf, 4);

    // �벨��Чֵʹ�ÿ�����֮���
    EmuCommbuf.ucTempBuf[0] = 0x05;     // ȫ������  �����ź�ֵ
    EmuCommbuf.ucTempBuf[1] = 0x00;
    EmuCommbuf.ucTempBuf[2] = 0;
    EmuCommbuf.ucTempBuf[3] = 0;
    fnRN8302_Write(RN8302_EMUCFG2, EmuCommbuf.ucTempBuf, 4);

    //      // ʹ�ܰ벨��Чֵ2����
    //      EmuCommbuf.ucTempBuf[0] = 0x01;
    //      EmuCommbuf.ucTempBuf[1] = 0x00;
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8302_EMUCFG3,EmuCommbuf.ucTempBuf,4);
    //      // �벨��Чֵ2����
    //      EmuCommbuf.ucTempBuf[0] = 0x7F;
    //      EmuCommbuf.ucTempBuf[1] = 0x00;
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8302_HWCNT,EmuCommbuf.ucTempBuf,4);
    //
    //      // ʹ�ܰ벨��Чֵ2����---INT1�ж�
    //      EmuCommbuf.ucTempBuf[0] = 0x00;
    //      EmuCommbuf.ucTempBuf[1] = 0x00;
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0x01;
    //      fnRN8302_Write(RN8302_EMMIE2,EmuCommbuf.ucTempBuf,4);

    // ��ѹ�����ʼ��x
    /*
    EmuCommbuf.ucTempBuf[0] = 0x00;
    EmuCommbuf.ucTempBuf[1] = 0x00;
    EmuCommbuf.ucTempBuf[2] = 0;
    EmuCommbuf.ucTempBuf[3] = 0;
    fnRN8302_Write(RN8302_GSUA_WAVE, EmuCommbuf.ucTempBuf,2);
    fnRN8302_Write(RN8302_GSUB_WAVE, EmuCommbuf.ucTempBuf,2);
    fnRN8302_Write(RN8302_GSUC_WAVE, EmuCommbuf.ucTempBuf,2);

    // ���������ʼ��
    fnRN8302_Write(RN8302_GSIA_WAVE, EmuCommbuf.ucTempBuf,2);
    fnRN8302_Write(RN8302_GSIB_WAVE, EmuCommbuf.ucTempBuf,2);
    fnRN8302_Write(RN8302_GSIC_WAVE, EmuCommbuf.ucTempBuf,2);
    fnRN8302_Write(RN8302_GSIN_WAVE, EmuCommbuf.ucTempBuf,2);*/

    //      fnRN8302_Write(RN8302_GSUA_WAVE,(u8 *)&MeasureFirmPara.GSU[0],2);
    //      fnRN8302_Write(RN8302_GSUB_WAVE,(u8 *)&MeasureFirmPara.GSU[1],2);
    //      fnRN8302_Write(RN8302_GSUC_WAVE,(u8 *)&MeasureFirmPara.GSU[2],2);
    //
    //      // ���������ʼ��
    //      fnRN8302_Write(RN8302_GSIA_WAVE,(u8 *)&MeasureFirmPara.GSI[0],2);
    //      fnRN8302_Write(RN8302_GSIB_WAVE,(u8 *)&MeasureFirmPara.GSI[1],2);
    //      fnRN8302_Write(RN8302_GSIC_WAVE,(u8 *)&MeasureFirmPara.GSI[2],2);
    //      fnRN8302_Write(RN8302_GSIN_WAVE,(u8 *)&MeasureFirmPara.GSI[3],2);

    //      EmuCommbuf.ucTemp8 = 0x10; // ��ղ������ݻ�����
    //      fnRN8302_Write(RN8302_WSAVECON,EmuCommbuf.ucTempBuf,1);
    //
    //      EmuCommbuf.ucTempBuf[0] = 0;
    //      EmuCommbuf.ucTempBuf[1] = 0x9A;   // ��HSDC
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0xEA;
    //      fnRN8302_Write(RN8302_SYSCFG,EmuCommbuf.ucTempBuf,4);
    //
    //      fnRN8302_Read(RN8302_SYSCFG,EmuCommbuf.ucTempBuf,4);
    //
    //      EmuCommbuf.ucTempBuf[0] = 0;    // �رղ��λ���
    //      EmuCommbuf.ucTempBuf[1] = 0;
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8306_DMA_WAVECON3,EmuCommbuf.ucTempBuf,4);
    //
    //      //��λMMU���λ���DMA
    //      EmuCommbuf.ucTempBuf[0] = 0xE1;
    //      fnRN8302_Write(RN8302_SOFTRST,EmuCommbuf.ucTempBuf,1);
    //      //��λHSDC
    //      EmuCommbuf.ucTempBuf[0] = 0x4C;
    //      fnRN8302_Write(RN8302_SOFTRST,EmuCommbuf.ucTempBuf,1);
    //      //дDMA_WAVECON�Ĵ���---128��
    ///*        EmuCommbuf.ucTempBuf[0] = 0x00;
    //      EmuCommbuf.ucTempBuf[1] = 0;
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8302_DMA_WAVECON,EmuCommbuf.ucTempBuf,4);  */

    //      EmuCommbuf.ucTempBuf[0] = 0xF4;
    //      EmuCommbuf.ucTempBuf[1] = 0x09;   //256��ͬ���������̶�wavecnt
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8302_DMA_WAVECON,EmuCommbuf.ucTempBuf,4);

    ///*
    //      EmuCommbuf.ucTempBuf[0] = 0x90;
    //      EmuCommbuf.ucTempBuf[1] = 0x14;   //128��ͬ���������̶�cnt
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8302_DMA_WAVECON,EmuCommbuf.ucTempBuf,4);
    //*/

    ///*        EmuCommbuf.ucTempBuf[0] = 0x01; //8K����
    //      EmuCommbuf.ucTempBuf[1] = 0x00;
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8302_DMA_WAVECON,EmuCommbuf.ucTempBuf,4);*/
    //
    //      //дWSAVECON�Ĵ���
    //      EmuCommbuf.ucTemp8 = 0x01;//0xAC;//0xA0;//0xA2; // 0x01
    //      fnRN8302_Write(RN8302_WSAVECON,EmuCommbuf.ucTempBuf,1);
    ////        //дEMMIE2�Ĵ���
    ////        EmuCommbuf.ucTempBuf[0] = 0;    //
    ////        EmuCommbuf.ucTempBuf[1] = 0x0A;
    ////        EmuCommbuf.ucTempBuf[2] = 0x10;
    ////        EmuCommbuf.ucTempBuf[3] = 0;
    ////        fnRN8302_Write(RN8302_EMMIE,EmuCommbuf.ucTempBuf,4);
    ////        //дEMMIF2�Ĵ���
    ////        EmuCommbuf.ucTempBuf[0] = 0;    //
    ////        EmuCommbuf.ucTempBuf[1] = 0x0A;
    ////        EmuCommbuf.ucTempBuf[2] = 0x00;
    ////        EmuCommbuf.ucTempBuf[3] = 0;
    ////        fnRN8302_Write(RN8302_EMMIF,EmuCommbuf.ucTempBuf,4);
    //
    //      EmuCommbuf.ucTempBuf[0] = 0x1D; // ����HSDC ��У��
    //      #ifdef EnCrc
    //      EmuCommbuf.ucTempBuf[0] = 0x1D; // ����HSDC
    //      #endif
    //      EmuCommbuf.ucTempBuf[1] = 0x04;         // ���ֽڷ���---�ȷ����ֽ�  �ۼ�У���
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8306_HDSC_CTRL,EmuCommbuf.ucTempBuf,4);
    //
    //      fnRN8302_Read(RN8306_HDSC_CTRL,EmuCommbuf.ucTempBuf,4);
    //
    //      EmuCommbuf.ucTempBuf[0] = 0x00;//0x05;//0x01;//0x03;
    //      EmuCommbuf.ucTempBuf[1] = 0x00;
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8306_DMA_WAVECON3,EmuCommbuf.ucTempBuf,4);
    //
    //      fnRN8302_Read( RN8302_WSAVECON , EmuCommbuf.ucTempBuf , 1 );
    //      EmuCommbuf.ucTemp8 = ((EmuCommbuf.ucTemp8 & 0xCF)|0x20); //�������λ���
    //      fnRN8302_Write(RN8302_WSAVECON,EmuCommbuf.ucTempBuf,1);

    EmuCommbuf.ucTemp8 = RN8302_WREN_DIS; //
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTempBuf[0] = 0xAA;
    EmuCommbuf.ucTempBuf[1] = RN8302_WREN_DIS;   //
    EmuCommbuf.ucTempBuf[2] = 0;
    EmuCommbuf.ucTempBuf[3] = 0;
    fnRN8302_Write(RN8302_WREN2, EmuCommbuf.ucTempBuf, 4);
}

/*****************************************************************************
** Function name:   fnRN8611_EnergyPulseIO_Init(void)
**
** Description:     RN8611��RN8302��PF��QF����������⡢ת�����Լ�г��������������ܽ�
**
** Parameters:      NONE
**
** Returned value:  NONE
**
******************************************************************************/
#if (PCB_Version==RN8611_RN7306)
void fnRN8611_EnergyPulseIO_Init(void)
{
    Rn8xxx_GPIO_CfgFun(PinRN8302_PF, _INTRUPT); /*"RN8302�й��������������"*/
    Rn8xxx_INTC_Init(INTC_ID6, INTC_RisingEdge, INTC_IRQ_ENABLE);
    Rn8xxx_GPIO_CfgFun(PinRN8302_QF, _INTRUPT); /*"RN8302�޹��������������"*/
    Rn8xxx_INTC_Init(INTC_ID7, INTC_RisingEdge, INTC_IRQ_ENABLE);
    Rn8xxx_GPIO_CfgFun(Pin_PF, _SF1); /*"�й��������������"*/
    Rn8xxx_GPIO_CfgFun(Pin_QF, _SF2); /*"�޹��������������"*/
    Rn8xxx_GPIO_CfgFun(Pin_PtHPF, _CF0); /*"����г���������������"*/
    Rn8xxx_GPIO_CfgFun(Pin_NtHPF, _CF1); /*"����г���������������"*/
    GPIO->IOCNT_CTL |= (0x1 << 1) | (0x1 << 2); /*ʹ��P50/P51��IOCNT����*/
    GPIO->P50_CFG |= 0x80000000;
    GPIO->P51_CFG |= 0x80000000;
}

/*****************************************************************************
** Function name:   fnRn8302_HSPI_Init(void)
**
** Description:     Rn8302  ADC���λ���ר��HSDC�ӿ�IO��ʼ��
**
** Parameters:      NONE
**
** Returned value:  NONE
**
******************************************************************************/
#define RXDMA_nPoint 64
#define RXDMA_nChan  6
typedef struct
{
    u8  Data[RXDMA_nPoint][RXDMA_nChan][3];
    u32 CRC;
} EmuAdcRecvBuf_Type;

sWaveSpiOutTypedef      sWaveSpiOut;

sHmWaveTypedef      sHmWave;
EmuAdcRecvBuf_Type  sEmuAdcRecvBuf;

void fnWaveSpiOut_SynSmplPoint(void)
{
    sWaveSpiOut.nSmplPoint = MeasureFirmPara.Send_nPoint.SendParaBit.nPoint;
    if (sWaveSpiOut.nSmplPoint > 256)
    {
        sWaveSpiOut.nSmplPoint = 128;
    }

    if (sWaveSpiOut.nSmplPoint && MeasureFirmPara.Send_nPoint.SendParaBit.EnOrDis == 0x0A)
    {
        sWaveSpiOut.EnWaveSpi = 1;
    }
    else
    {
        sWaveSpiOut.EnWaveSpi = 0;
    }

    /*
    sWaveSpiOut.nSmplPoint = MeasureFirmPara.Send_nPoint.SendPara;
    if(sWaveSpiOut.nSmplPoint)
    {
        if(sWaveSpiOut.nSmplPoint > 256)
            sWaveSpiOut.nSmplPoint = 128;
        sWaveSpiOut.EnWaveSpi = 1;
    }
    else
        sWaveSpiOut.EnWaveSpi = 0;
    */
}

void fnWaveSpiOut_Init()
{
    memset(&sWaveSpiOut.nSmplPoint, 0, sizeof(sWaveSpiOutTypedef));

    sWaveSpiOut.Head = 0x68;
    sWaveSpiOut.Ctrl = 0x33;
    sWaveSpiOut.fEnd = 0x16;

    fnWaveSpiOut_SynSmplPoint();

    /*
    memset(&sWaveSpiOut.nSmplPoint, 0, sizeof(sWaveSpiOutTypedef));

    sWaveSpiOut.Head = 0x68;
    sWaveSpiOut.Ctrl = 0x33;
    sWaveSpiOut.fEnd = 0x16;

    sWaveSpiOut.nSmplPoint = MeasureFirmPara.Send_nPoint.SendPara;
    if(sWaveSpiOut.nSmplPoint)
    {
        if(sWaveSpiOut.nSmplPoint > 256)
            sWaveSpiOut.nSmplPoint = 128;
        sWaveSpiOut.EnWaveSpi = 1;
    }
    */
}

u8 tstbuf[16];

void fnWaveSpiOutToExModule(u8 *pSrc, u16 Len)
{
    ENABLE_ExModule();

    //  memset(tstbuf, 0x22, 16);
    //
    //  Rn8xxx_Spi_DMATxStar(SPI2_ID , (u32)&tstbuf[0], 16 , 0x0);

    Rn8xxx_Spi_DMATxStar(SPI2_ID, (u32)&pSrc[0], Len, 0x0);
}

uint32_t fnCalSum(uint8_t *buf, uint16_t len)
{
    uint32_t sum = 0;
    uint16_t i;

    for (i = 0; i < len; i++)
    {
        sum += buf[i];
    }

    return sum;
}

extern u32 TestHarmonicTime[10];

void fnWaveHfrms2Smple(void)
{
    // �ɼ��벨����ֵ��ʼ
    if (sHmWave.HalfIrms.ReadFlag == CTLSTAR)
    {
        u8 i;

        if (sHmWave.HalfIrms.MsCnt != 0)
        {
            sHmWave.HalfIrms.MsCnt--;
        }

        //      if( (sWaveSpiOut.nCnt == 0) || (sWaveSpiOut.nCnt == 2) )
        if (sHmWave.HalfIrms.MsCnt == 0)
        {
            u32 itmp; // dyf del frq = 0

            //frq = (u32)(400000 / MeasureRms.PubData.Frequency + 0.5); // dyf del
            TestHarmonicTime[2] = TC0->CNT;

            for (i = 0; i < 3; i++)
            {
                fnRN8302_Read(RN8302_HfIA2 + i, (u8 *)&MeasureRegTmp.HfIrms2[i], 4);
                //              itmp = MeasureRegTmp.HfIrms2[i] * 256 / (sqrt(frq))/(MeasureFirmPara.KIArms);
                itmp = MeasureRegTmp.HfIrms2[i] * 32 / (sqrt(128)) / (MeasureFirmPara.KIArms);
                sHmWave.HalfIrms.Irms[i][sHmWave.HalfIrms.Cnt] = itmp * 10;
            }

            TestHarmonicTime[3] = TC0->CNT;

            sHmWave.HalfIrms.MsCnt = 2;
            sHmWave.HalfIrms.Cnt++;
            if (sHmWave.HalfIrms.Cnt >= sHmWave.HalfIrms.RDepth)
            {
                sHmWave.HalfIrms.Cnt = 0;
                sHmWave.HalfIrms.ReadFlag = CTLSTOP;
            }
        }
    }
}

void fnWaveHfrmsSmple(void)
{
    // �ɼ��벨����ֵ��ʼ
    if (sHmWave.HalfIrms.ReadFlag == CTLSTAR)
    {
        //u8 i;

        if (sHmWave.HalfIrms.MsCnt != 0)
        {
            sHmWave.HalfIrms.MsCnt--;
        }

        //      if( (sWaveSpiOut.nCnt == 0) || (sWaveSpiOut.nCnt == 2) )
        if (sHmWave.HalfIrms.MsCnt == 0)
        {
            float frq = 0;
            u32 itmp;

            TestHarmonicTime[2] = TC0->CNT;

            frq = 2560 / sqrt((u32)(400000 / MeasureRms.PubData.Frequency + 0.5)) / MeasureFirmPara.KIArms;
            //frq = 1;

            //          for(i=0; i<1; i++)
            //          {
            //              fnRN8302_Read(RN8302_HfIA + i, (u8 *)&MeasureRegTmp.HfIrms2[i], 4);
            //              itmp = MeasureRegTmp.HfIrms2[i] * frq ;
            //
            //              sHmWave.HalfIrms.Irms[i][sHmWave.HalfIrms.Cnt] = itmp;
            ////                itmp /= MeasureFirmPara.KIArms;
            ////                sHmWave.HalfIrms.Irms[i][sHmWave.HalfIrms.Cnt] = itmp * 10;
            //          }

            fnRN8302_Read(RN8302_HfIA, (u8 *)&MeasureRegTmp.HfIrms2[0], 4);
            itmp = MeasureRegTmp.HfIrms2[0] * frq ;
            sHmWave.HalfIrms.Irms[0][sHmWave.HalfIrms.Cnt] = itmp;

            //�����쳣�ڵ�
            if (sHmWave.HalfIrms.Cnt >= 3)
            {
                if ((sHmWave.HalfIrms.Irms[0][sHmWave.HalfIrms.Cnt - 1] > (sHmWave.HalfIrms.Irms[0][sHmWave.HalfIrms.Cnt - 2] + 10))
                    && (sHmWave.HalfIrms.Irms[0][sHmWave.HalfIrms.Cnt - 1] > (sHmWave.HalfIrms.Irms[0][sHmWave.HalfIrms.Cnt] + 10)))
                {
                    sHmWave.HalfIrms.Irms[0][sHmWave.HalfIrms.Cnt - 1] = sHmWave.HalfIrms.Irms[0][sHmWave.HalfIrms.Cnt - 2];
                }

                if (((sHmWave.HalfIrms.Irms[0][sHmWave.HalfIrms.Cnt - 1] + 10) < sHmWave.HalfIrms.Irms[0][sHmWave.HalfIrms.Cnt - 2])
                    && ((sHmWave.HalfIrms.Irms[0][sHmWave.HalfIrms.Cnt - 1] + 10) < sHmWave.HalfIrms.Irms[0][sHmWave.HalfIrms.Cnt]))
                {
                    sHmWave.HalfIrms.Irms[0][sHmWave.HalfIrms.Cnt - 1] = sHmWave.HalfIrms.Irms[0][sHmWave.HalfIrms.Cnt - 2];
                }
            }

            TestHarmonicTime[3] = TC0->CNT;

            sHmWave.HalfIrms.MsCnt = 2;
            sHmWave.HalfIrms.Cnt++;
            if (sHmWave.HalfIrms.Cnt >= sHmWave.HalfIrms.RDepth)
            {
                sHmWave.HalfIrms.Cnt = 0;
                sHmWave.HalfIrms.ReadFlag = CTLSTOP;
            }
        }
    }
}

void fnWaveHsdcSpi_ToHmonic(u8 * buf, u16 len)
{
    //u16 j, k, ioffset = 0, rtn;
    uM2M_ModePara_TypeDef  M2M_ModePara;

    M2M_ModePara.gMode = 0x00;
    M2M_ModePara.Mode_IVLD = IVLD_4BYTE;
    M2M_ModePara.Mode_OVLD = OVLD_3BYTE;
    M2M_ModePara.Mode_ORV = ORV_DIS;
    M2M_ModePara.Mode_DUMMY = DUMMY_EN;

    //  ioffset = sWaveSpiOut.nCnt * 64;

    Rn8xxx_M2M_Move(M2M_ModePara, (u32)((u32 *)&buf[0]), (u32)((u32 *)&sHmWave.sHm.HmVal[sHmWave.InPoint][sWaveSpiOut.nCnt][0]), len);

    //  rtn = Rn8xxx_M2M_Move(M2M_ModePara , (u32)((u32 *)&buf[0]) , (u32)((u32 *)&sHmWave.sHm.HmSmplVal[sHmWave.InPoint][ioffset][0]) , len);
    //
    //  if(rtn == ERROR)
    //  {
    //      rtn = ERROR;
    //  }

    //  Rn8xxx_DSP_Int2Fp((u32)((u32 *)&sHmWave.HmSmplVal[sHmWave.InPoint][ioffset][0]) ,
    //                  (u32)((u32 *)&sHmWave.HmSmplVal[sHmWave.InPoint][ioffset][0]) , 384 , 0 , 1);

    //  fnWaveHfrmsSmple();
}

u32 WaveHmFftBuf[6][128];

void fnWaveHsdcSpi_AdcCheck(void)
{
    u32 iSum = 0;
    u16 i, j, k, iHeadLen, ioffset, nStep, nPoint;
    u16 DltaLen = 0;

    TestHarmonicTime[0] = TC0->CNT;

    iHeadLen = 5;
    DltaLen = 3;
    nPoint = sWaveSpiOut.nSmplPoint / 4;            // 64 * sWaveSpiOut.nPoint / 256
    nStep = 64 / nPoint;

    sWaveSpiOut.fLen = sWaveSpiOut.nSmplPoint * 18;

    iSum = fnCalSum(&sEmuAdcRecvBuf.Data[0][0][0], 1152);

    if (iSum == sEmuAdcRecvBuf.CRC)
    {
        // ��������---г������
        fnWaveHsdcSpi_ToHmonic(&sEmuAdcRecvBuf.Data[0][0][0], 1152);

        if (sWaveSpiOut.EnWaveSpi == 0)
        {
            sWaveSpiOut.nCnt++;

            if (sWaveSpiOut.nCnt == 4)
            {
                sWaveSpiOut.nCnt = 0;
                sHmWave.InPoint++;
                if (sHmWave.InPoint >= nHmCyc)
                {
                    sHmWave.InPoint = 0;
                }

                HarmonicData.PriPara.CtlFlag = Harmonic_Exe_CalcHPw;
            }

            return;
        }

        ioffset = sWaveSpiOut.nCnt * nPoint * 18;

        sWaveSpiOut.nCnt++;

        // ��������WaveSpiOut
        if (sWaveSpiOut.nSmplPoint == 256)
        {
            uM2M_ModePara_TypeDef  M2M_ModePara;

            M2M_ModePara.gMode = 0x00;
            M2M_ModePara.Mode_IVLD = IVLD_4BYTE;
            M2M_ModePara.Mode_OVLD = OVLD_4BYTE;
            M2M_ModePara.Mode_ORV = ORV_DIS;
            M2M_ModePara.Mode_DUMMY = DUMMY_EN;

            Rn8xxx_M2M_Move(M2M_ModePara, (u32)((u32 *)&sEmuAdcRecvBuf.Data[0][0][0]),
                            (u32)((u32 *)&sWaveSpiOut.WaveSpiOut[8 + ioffset]), 1152);

            //          memcpy(&sWaveSpiOut.WaveSpiOut[iHeadLen + ioffset], &sEmuAdcRecvBuf.Data[0][0][0], 1152);

            sWaveSpiOut.nSum += sEmuAdcRecvBuf.CRC;
        }
        else
        {
            //          uM2M_ModePara_TypeDef  M2M_ModePara;
            //
            //          M2M_ModePara.gMode = 0x00;
            //          M2M_ModePara.Mode_IVLD = IVLD_4BYTE;
            //          M2M_ModePara.Mode_OVLD = OVLD_4BYTE;
            //          M2M_ModePara.Mode_ORV = ORV_DIS;
            //          M2M_ModePara.Mode_DUMMY= DUMMY_EN;

            u8 *pDst, *pSrc;

            k = iHeadLen + DltaLen;
            j = 0;
            pDst = &sWaveSpiOut.WaveSpiOut[ioffset + k];
            for (i = 0; i < nPoint; i++)
            {
                pSrc = &sEmuAdcRecvBuf.Data[j][0][0];

                // UA
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                // UB
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                // UC
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                // IA
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                // IB
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                // IC
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;

                j += nStep;
            }

            //          for(i=0,j=0,k=iHeadLen+DltaLen; i<nPoint; i++)
            //          {
            //              memcpy(&sWaveSpiOut.WaveSpiOut[ioffset + k], &sEmuAdcRecvBuf.Data[j][0][0], 18);
            //
            //
            ////                Rn8xxx_M2M_Move(M2M_ModePara , (u32)((u32 *)&sEmuAdcRecvBuf.Data[j][0][0]) ,
            ////                            (u32)((u32 *)&sWaveSpiOut.WaveSpiOut[k + ioffset]) , 18);
            //
            //              j += nStep;
            //              k += 18;
            //          }
        }

        if (sWaveSpiOut.nCnt == 4)
        {
            sHmWave.InPoint++;
            if (sHmWave.InPoint >= nHmCyc)
            {
                sHmWave.InPoint = 0;
            }

            sWaveSpiOut.nCnt = 0;

            if (sWaveSpiOut.nSmplPoint != 256)
            {
                sWaveSpiOut.nSum = fnCalSum(&sWaveSpiOut.WaveSpiOut[5 + DltaLen], sWaveSpiOut.fLen);
            }
            sWaveSpiOut.fLen += 8;
            sWaveSpiOut.nTLen = sWaveSpiOut.fLen + 2;

            // ���֡ͷ ���
            memcpy(&sWaveSpiOut.WaveSpiOut[0 + DltaLen], &sWaveSpiOut.Head, iHeadLen);

            // ������֡У���
            sWaveSpiOut.nSum += sWaveSpiOut.Ctrl;
            sWaveSpiOut.nSum += (sWaveSpiOut.fLen & 0x00FF);
            sWaveSpiOut.nSum += ((sWaveSpiOut.fLen >> 8) & 0x00FF);
            sWaveSpiOut.nSum += sWaveSpiOut.fSeq;
            memcpy(&sWaveSpiOut.WaveSpiOut[sWaveSpiOut.nTLen - 5 + DltaLen], &sWaveSpiOut.nSum, 4);

            sWaveSpiOut.WaveSpiOut[sWaveSpiOut.nTLen - 1 + DltaLen] = sWaveSpiOut.fEnd;

            // ����SPI-DMA����
            fnWaveSpiOutToExModule(&sWaveSpiOut.WaveSpiOut[0 + DltaLen], sWaveSpiOut.nTLen);

            // ֡����ۼ�  ����У���
            sWaveSpiOut.fSeq++;
            sWaveSpiOut.nSum = 0;

            HarmonicData.PriPara.CtlFlag = Harmonic_Exe_CalcHPw;
        }
    }
    else
    {
        sWaveSpiOut.nErr++;
    }

    TestHarmonicTime[1] = TC0->CNT;
}

void fnRN8302_WaveDataToExModule(void)
{
    //  ENABLE_ExModule();
    //  fnSetSpiOutData();
    //  Rn8xxx_Spi_DMATxStar(SPI2_ID , (u32)&SpiOutDataBuf, sizeof(SpiOutDataBuf) , 0x0);
}

void fnRN8302_HSPI_DMAInit(void)
{
    uSPI_DMAPara_TypeDef  spi_DmaPara;

    spi_DmaPara.RbAdr = (u16)(&sEmuAdcRecvBuf.Data[0][0][0]);
    spi_DmaPara.DmaCtl.SPI_DMACtl_TX_DMA_EN = 0;
    spi_DmaPara.DmaCtl.SPI_DMACtl_RX_DMA_EN = 1;
    spi_DmaPara.DmaCtl.SPI_DMACtl_TX_CYC_MODE = 0;
    spi_DmaPara.DmaCtl.SPI_DMACtl_RX_CYC_MODE = 1;
    spi_DmaPara.RLen = RXDMA_nPoint * RXDMA_nChan * 3 + 4; //�ۼӺ�
    //  spi_DmaPara.RLen = RXDMA_nPoint*RXDMA_nChan*3;      //����CRC
    //spi_DmaPara.RLen = RXDMA_nPoint*RXDMA_nChan*3 + 2;//��CRC
    spi_DmaPara.DmaIE = SPI_DMA_RX_FIE; //����ȫ���ж�
    Rn8xxx_Spi_DMAInit(SPI0_ID, spi_DmaPara);
}

void fnRn8302_HSDCSPI_Init(void)
{
    uSPICtlPara_TypeDef spi_para;
    //uSPI_DMAPara_TypeDef  spi_DmaPara;
    //u16 SpiClk;

    Rn8xxx_GPIO_CfgFun(PinHSCS_C, _SPI0);
    Rn8xxx_GPIO_CfgPullMode(PinHSCS_C, Pull_ON);

    Rn8xxx_GPIO_CfgFun(PinHSCLK_C, _SPI0);
    Rn8xxx_GPIO_CfgPullMode(PinHSCLK_C, Pull_ON);

    Rn8xxx_GPIO_CfgFun(PinHMOSI_C, _SPI0);
    Rn8xxx_GPIO_CfgPullMode(PinHMOSI_C, Pull_ON);

    //Rn8xxx_GPIO_CfgFun(PinINTN1_C,_INTRUPT);  //����оƬ�ж�����,ƽʱΪ�ߣ��жϲ���ʱΪ��
    //Rn8xxx_INTC_Init(INTC_ID4,INTC_FallingEdge,INTC_IRQ_ENABLE);

    spi_para.gSPICtl = SPICTL_DEFAULT;
    spi_para.SPICtl_EN = SPICTL_EN;
    spi_para.SPICtl_MAST_SLAV = SPICTL_SLAV;
    spi_para.SPICtl_LMSB = SPICTL_MSB;
    spi_para.SPICtl_CPOL = (SPICtl_Mode_01 >> 1);
    spi_para.SPICtl_CPHA = (SPICtl_Mode_01 & 0x01);
    spi_para.SPICtl_WIDTH = SPICTL_WIDTH_8BIT;
    spi_para.SPICtl_SCSN_POS_IRQ_EN = 1;    //�����ӻ�Ƭѡ�������ж�ʹ��
    spi_para.SPICtl_SCSN_NEG_IRQ_EN = 0;    //�����ӻ�Ƭѡ�½����ж�ʹ��
    spi_para.SPICtl_SLV_TX_ADV = 1;         //0Ϊ����ģʽ��ʱ��������ʿɴ�fcpu/8��1Ϊ����ģʽ���ӻ�������ʿɴ�fcpu/4
    //�������õ����ʻ�Ӱ��ӻ����յ������𣿣�
    Rn8xxx_Spi_Init(SPI0_ID, spi_para, 4000000);  //SpiClk

    //  (u16)(&sEmuAdcRecvBuf.Data[0][0][0]);
    //  spi_DmaPara.DmaCtl.SPI_DMACtl_TX_DMA_EN = 0;
    //  spi_DmaPara.DmaCtl.SPI_DMACtl_RX_DMA_EN = 1;
    //  spi_DmaPara.DmaCtl.SPI_DMACtl_TX_CYC_MODE = 0;
    //  spi_DmaPara.DmaCtl.SPI_DMACtl_RX_CYC_MODE = 1;
    //  spi_DmaPara.RLen = RXDMA_nPoint*RXDMA_nChan*3 + 4;  //�ۼӺ�
    ////    spi_DmaPara.RLen = RXDMA_nPoint*RXDMA_nChan*3;      //����CRC
    //  //spi_DmaPara.RLen = RXDMA_nPoint*RXDMA_nChan*3 + 2;//��CRC
    //  spi_DmaPara.DmaIE = SPI_DMA_RX_HIE|SPI_DMA_RX_FIE;  //����ȫ���ж�
    //  Rn8xxx_Spi_DMAInit(SPI0_ID , spi_DmaPara);
    NVIC_EnableIRQ(SPI_IRQn);
}

/*********************************************************************************************************
** Function name:         fnBSP_ExModuleSpi_Init
** Descriptions:          �ⲿ��չģ��spiͨѶIO��ʼ��
** input parameters:
** output parameters:   none
** Returned value:
*********************************************************************************************************/
#define ExModuleSpiSpeed    1000000
void fnBSP_ExModuleSpi_Init(void)
{
    uSPICtlPara_TypeDef spi_para;
    uSPI_DMAPara_TypeDef  spi_DmaPara;
    //u16 SpiClk;

    Rn8xxx_GPIO_CfgFun(PinExModuleCS, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinExModuleCS, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinExModuleCS, 1);

    //Rn8xxx_GPIO_SetPin(PinExModuleCS , 0);

    Rn8xxx_GPIO_CfgFun(PinExModuleClk, _SPI2);
    Rn8xxx_GPIO_CfgPullMode(PinExModuleClk, Pull_ON);

    Rn8xxx_GPIO_CfgFun(PinExModuleMOSI, _SPI2);
    Rn8xxx_GPIO_CfgPullMode(PinExModuleMOSI, Pull_ON);

    spi_para.gSPICtl = SPICTL_DEFAULT;
    spi_para.SPICtl_EN = SPICTL_EN;
    spi_para.SPICtl_MAST_SLAV = SPICTL_MAST;
    spi_para.SPICtl_LMSB = SPICTL_MSB;
    /*spi_para.SPICtl_CPOL = (SPICtl_Mode_11>>1);
    spi_para.SPICtl_CPHA = (SPICtl_Mode_11&0x01);
    */
    spi_para.SPICtl_CPOL = (SPICtl_Mode_01 >> 1);
    spi_para.SPICtl_CPHA = (SPICtl_Mode_01 & 0x01);
    spi_para.SPICtl_WIDTH = SPICTL_WIDTH_8BIT;
    //SpiClk = fnMeasure_DMATxSpeed();
    Rn8xxx_Spi_Init(SPI2_ID, spi_para, 3200000);  //SpiClk

    spi_DmaPara.DmaCtl.SPI_DMACtl_TX_DMA_EN = 0;
    spi_DmaPara.DmaCtl.SPI_DMACtl_RX_DMA_EN = 0;
    spi_DmaPara.DmaCtl.SPI_DMACtl_TX_CYC_MODE = 0;
    spi_DmaPara.DmaCtl.SPI_DMACtl_RX_CYC_MODE = 0;
    spi_DmaPara.DmaIE = SPI_DMA_TX_FIE; //����ȫ���ж�
    Rn8xxx_Spi_DMAInit(SPI2_ID, spi_DmaPara);

    NVIC_EnableIRQ(ISO78161_SPI2_IRQn);
}

#endif

//--------��ѹӰ��������Ĭ������-----------------
const sMeasureRepairPara_TypeDef RepairParaDefault _reserve =
{
    {
        VOL_REPAIR,
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //A��1~8������
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //B��1~8������
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },    //C��1~8������
        0x00
    },
    0x1018,     //RN8302_TIRM  V30--0x1830   V32--0x1018
    //  {0x4138 , 0x4138 , 0x4138},  //RN8207D_TIRM
};

//-------��ѹӰ����������--------------------
const sVolRepairRange_TypeDef Tab_VoltRepair[] =
{
    {Un115_Max, Un115_Min, Itr_Max, Imin_Min, COS10_Max, COS10_Min, Un115_COS10_Itr},       //
    {Un110_Max, Un110_Min, Itr_Max, Imin_Min, COS10_Min, COS10_Min, Un110_COS10_Itr},
    {Un110_Max, Un110_Min, Itr_Max, Imin_Min, COS05L_Max, COS05L_Min, Un110_COS05L_Itr},
    {Un90_Max, Un90_Min, Itr_Max, Imin_Min, COS10_Max, COS10_Min, Un90_COS10_Itr},       //
    {Un90_Max, Un90_Min, Itr_Max, Imin_Min, COS05L_Min, COS05L_Min, Un90_COS05L_Itr},
    {Un80_Max, Un80_Min, Itr_Max, Imin_Min, COS10_Max, COS10_Min, Un80_COS10_Itr},
};

/*****************************************************************************
** Function name:void fnMeasure_VoltRepairCorrect(u32 err)
**
** Description:��ѹӰ��������У������
**
** Parameters:
** nphase:  A��=0x00��B��=0x01��C��=0x02
**
** step:     0x55:�Զ����ݵ�ѹ����������������ʶ�𲹳���,����ֵΪ�ֶ�ѡ�񲹳���
**
** DataCommErr:    ͨѶ�·�������������,�Ŵ�100000��,  ��̨����ʾ��� 0.142%,ֵΪ��DataCommErr=142(0x8E).
**
**   ����ֵ:0x5A5A5A5A = ��ѹӰ������ʼ��;0x11223344=�򿪵�ѹӰ��������
**                    0x44332211 = �رյ�ѹӰ��������;0x00000000=����ֵ����
**
** Returned value:FALSE ����ʧ�ܣ�TRUE ���óɹ�
**
******************************************************************************/
u8 fnMeasure_VoltRepairCorrect(u8 nphase, u8 step, u32 DataCommErr)
{
    sDataComm_TypeDef      EmuCommbuf;
    float ADErr;
    u8 j, res = FALSE, temp08;
    u32  temp_I ;
    u16  temp_Pf ;

    if (DataCommErr == 0x5A5A5A5A) //��ѹӰ������ʼ��
    {
        Std_Memset((u8 *)&MeasureRepairPara, 0x00, sizeof(sMeasureRepairPara_TypeDef));

        MeasureRepairPara.Volt.EnOrDis = VOLREP_Enable; //�򿪵�ѹӰ��������

        fnCrc_Check(0, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc);

        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef));

        res = TRUE;
    }
    else if (DataCommErr == 0x11223344)
    {
        MeasureRepairPara.Volt.EnOrDis = VOLREP_Enable; //�򿪵�ѹӰ��������
        fnCrc_Check(0, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc);

        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef));

        res = TRUE;
    }
    else if (DataCommErr == 0x44332211)
    {
        MeasureRepairPara.Volt.EnOrDis = VOLREP_Disable;  //�رյ�ѹӰ��������
        fnCrc_Check(0, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc);

        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef));

        res = TRUE;
    }
    else if (DataCommErr == 0x55667788) //����ֵ����
    {
        Std_Memset((u8 *)&MeasureRepairPara, 0x00, sizeof(sMeasureRepairPara_TypeDef));
        MeasureRepairPara.Volt.EnOrDis = VOLREP_Disable;  //�رյ�ѹӰ��������
        fnCrc_Check(0, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc);
        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef));

        res = TRUE;
    }
    else
    {
        if (MeasureRepairPara.Volt.EnOrDis != VOLREP_Enable)
        {
            return FALSE;
        }

        if (step == 0x55)
        {
            temp_I = abs(MeasureRms.PubData.I[nphase]); //A,B,C,N
            temp_Pf =  abs(MeasureRms.PubData.Pf[nphase]);  //,A,B,C

            for (j = 0; j < RE_ARRAY_LENGTH(Tab_VoltRepair) ; j++)
            {
                if ((MeasureRms.PubData.U[nphase] < Tab_VoltRepair[j].UMax) && (MeasureRms.PubData.U[nphase] >= Tab_VoltRepair[j].UMin) &&
                    (temp_I <= Tab_VoltRepair[j].IMax) && (temp_I >= Tab_VoltRepair[j].IMin) &&
                    (temp_Pf <= Tab_VoltRepair[j].CosMax) && (temp_Pf >= Tab_VoltRepair[j].CosMin))
                {
                    step = Tab_VoltRepair[j].Step;
                    break;
                }
            }
        }

        if (step > MAX_VOLT_STEP)
        {
            return FALSE;
        }

        step -= 1;  //ͨѶ�·�step ��1��ʼ

        if (DataCommErr > 0x7fffffff)
        {
            ADErr = -(float)(0xffffffff - DataCommErr + 1) / 100000;
        }
        else
        {
            ADErr = (float)DataCommErr / 100000;
        }
        ADErr = ((-ADErr) / (1 + ADErr));

        EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // дʹ��λ
        fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

        if (ADErr == 0)
        {
            EmuCommbuf.wTemp16 = 0;
            MeasureRepairPara.Volt.Rep[nphase][step] = 0;
        }
        else if (ADErr > 0)
        {
            EmuCommbuf.wTemp16 = ADErr * 32768 + 0.5;    //��������
        }
        else
        {
            EmuCommbuf.wTemp16 = (u16)(65536 + ADErr * 32768 + 0.5);    //��������
        }

        if (EmuCommbuf.wTemp16 & 0x8000)
        {
            temp08 = (u8)(~EmuCommbuf.wTemp16) + 1;
            MeasureRepairPara.Volt.Rep[nphase][step] -= temp08;
        }
        else
        {
            MeasureRepairPara.Volt.Rep[nphase][step] += (u8)EmuCommbuf.wTemp16;
        }

        if (MeasureRepairPara.Volt.Rep[nphase][step] & 0x80)
        {
            temp08 = (u8)(~MeasureRepairPara.Volt.Rep[nphase][step]) + 1;
            EmuCommbuf.wTemp16 = MeasureFirmPara.GP[nphase] - (u16)temp08;
        }
        else
        {
            EmuCommbuf.wTemp16 = MeasureFirmPara.GP[nphase] + (u16)MeasureRepairPara.Volt.Rep[nphase][step];
        }

        fnRN8302_Write(RN8302_GPA + nphase, EmuCommbuf.ucTempBuf, 2);

        fnRN8302_Write(RN8302_GQA + nphase, EmuCommbuf.ucTempBuf, 2);

        fnRN8302_Write(RN8302_GSA + nphase, EmuCommbuf.ucTempBuf, 2);

        EmuCommbuf.ucTemp8 = RN8302_WREN_DIS; // д����
        fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

        fnCrc_Check(0, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc);

        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef));

        res = TRUE;
    }

    return res;
}

/*****************************************************************************
** Function name:fnMeasure_VoltRepair_CommRead
**
** Description:ͨѶ��ȡ��ѹӰ������������
**
** Parameters:��ȡ����
**
** Returned value:���ݳ���
**
******************************************************************************/
u8 fnMeasure_VoltRepair_CommRead(u8 *data)
{
    u8 len;

    Std_Memcpy(data, (u8 *)&MeasureRepairPara.Volt,  sizeof(sVoltRepairPara_TypeDef));

    len = sizeof(sVoltRepairPara_TypeDef);

    return len;
}

/*********************************************************************************************************
** Function name:   fnMeasure_VoltRepair_Exe
** Descriptions:       ��ѹӰ��������,������߷���
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
u8 fnMeasure_VoltRepair_Exe(void)
{
    u8 i, j, step, res = FALSE;
    u32  temp_I  ;
    u16 temp16, temp_Pf;
    sDataComm_TypeDef      EmuCommbuf;

    if (MeasureRepairPara.Volt.EnOrDis != VOLREP_Enable)
    {
        return FALSE;
    }

    for (i = 0 ; i < nPhs; i++)
    {
        temp_I = abs(MeasureRms.PubData.I[i]);  //A,B,C,N
        temp_Pf =  abs(MeasureRms.PubData.Pf[i]);  //,A,B,C

        for (j = 0; j < RE_ARRAY_LENGTH(Tab_VoltRepair) ; j++)
        {
            if ((MeasureRms.PubData.U[i] < Tab_VoltRepair[j].UMax) && (MeasureRms.PubData.U[i] >= Tab_VoltRepair[j].UMin) &&
                (temp_I <= Tab_VoltRepair[j].IMax) && (temp_I >= Tab_VoltRepair[j].IMin) &&
                (temp_Pf <= Tab_VoltRepair[j].CosMax) && (temp_Pf >= Tab_VoltRepair[j].CosMin))
            {
                EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // дʹ��λ
                fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

                step = Tab_VoltRepair[j].Step;

                if (MeasureRepairPara.Volt.Rep[i][step] & 0x80)
                {
                    temp16 = (u8)(~MeasureRepairPara.Volt.Rep[i][step]) + 1;
                    EmuCommbuf.wTemp16 = MeasureFirmPara.GP[i] - temp16;
                    //                  EmuCommbuf.wTemp16 = MeasureFirmPara.GP[i] + (u16)(MeasureRepairPara.Volt.Rep[i][step]&0x7f);
                }
                else
                {
                    //                  EmuCommbuf.wTemp16 = MeasureFirmPara.GP[i] - (u16)MeasureRepairPara.Volt.Rep[i][step];
                    EmuCommbuf.wTemp16 = MeasureFirmPara.GP[i] + (u16)MeasureRepairPara.Volt.Rep[i][step];
                }

                temp16 = 0;

                fnRN8302_Read(RN8302_GPA + i, (u8 *)&temp16, 2);
                if (EmuCommbuf.wTemp16 != temp16)
                {
                    fnRN8302_Write(RN8302_GPA + i, EmuCommbuf.ucTempBuf, 2);

                    fnRN8302_Write(RN8302_GQA + i, EmuCommbuf.ucTempBuf, 2);

                    fnRN8302_Write(RN8302_GSA + i, EmuCommbuf.ucTempBuf, 2);
                }

                res = TRUE;  //���ڵ�ѹӰ��������״̬����ʱ����У���

                break;
            }

            if (j == RE_ARRAY_LENGTH(Tab_VoltRepair)) //���ڵ�ѹ�����㣬�����ָ�
            {
                fnRN8302_Read(RN8302_GPA + i, (u8 *)&temp16, 2);
                if (MeasureFirmPara.GP[i] != temp16)
                {
                    fnRN8302_Write(RN8302_GPA + i, (u8 *)&MeasureFirmPara.GP[i], 2);
                }

                fnRN8302_Read(RN8302_GQA + i, (u8 *)&temp16, 2);
                if (MeasureFirmPara.GP[i] != temp16)
                {
                    fnRN8302_Write(RN8302_GQA + i, (u8 *)&MeasureFirmPara.GP[i], 2);
                }

                fnRN8302_Read(RN8302_GSA + i, (u8 *)&temp16, 2);
                if (MeasureFirmPara.GP[i] != temp16)
                {
                    fnRN8302_Write(RN8302_GSA + i, (u8 *)&MeasureFirmPara.GP[i], 2);
                }
            }
        }
    }

    return res;
}

/*****************************************************************************
** Function name:   fnRN830x_RSIOM(void)
**
** Description:     RN8302C��RN8306 RSIOM�Ĵ�������,ͨ��RSIOM��ʽ�޸�RN8207D�Ĵ���
**
** Parameters: DevNo:�ӻ��豸��(0~3),0����㲥��ַ;
**           Reg    :�ӻ��Ĵ�����ַ(0~2)  00:BGR_TRIM; 01:CFG_PWD; 02:DLL_MUX
**           Data: �������ӻ�����������
** Returned value:  ERROR:����ʧ�ܣ�SUCCESS:�����ɹ�
**
******************************************************************************/
u8 fnRN830x_RSIOM(u8 DevNo, u8 Reg, u32 Data)
{
    sDataComm_TypeDef      EmuCommbuf;
    RSIOM_MODE_TypeDef    rsiom_mode;
    RSIOM_CMD_TypeDef   rsiom_cmd;
    u32 status ;
    u8 i, result = SUCCESS;

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // дʹ��λ
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    fnRN8302_Read(RN8302_WREN2, &EmuCommbuf.ucTempBuf[0], 4); //�ȶ�ȡ��λ�����Ƿ���Ч
    if (EmuCommbuf.ucTempBuf[0]) //д��0xAAʱ��ʾ��λ��Ч������Ϊ0x01
    {
        EmuCommbuf.ucTempBuf[0] = 0xAA;
    }
    else
    {
        EmuCommbuf.ucTempBuf[0] = 0x55;    //д��0x55ʱ��ʾ��λ��Ч������Ϊ0x00
    }

    EmuCommbuf.ucTempBuf[1] = RN8302_WREN_EN; // дʹ��λ2
    EmuCommbuf.ucTempBuf[2] = 0x00;
    EmuCommbuf.ucTempBuf[3] = 0x00;
    fnRN8302_Write(RN8302_WREN2, EmuCommbuf.ucTempBuf, 4); //RN8302_WREN2:bit0~bit7��ʾ��λ����;   bit8~bit15��ʾдʹ��;bit16~bit31 ����

    rsiom_mode.RESERVED = 0x00;
    rsiom_mode.CHKSUM_EN = 0x00;
    rsiom_mode.SPEED = 0x00;  //10K Hz
    rsiom_mode.HOLD_Time = 0x00;
    Std_Memcpy((u8 *)&EmuCommbuf.ucTempBuf[0], (u8 *)&rsiom_mode, 1);
    fnRN8302_Write(RN830x_RSIOM_MODE, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTemp8 = RSIOM_EN_STEP1;  //0xA8
    fnRN8302_Write(RN830x_RSIOM_CTL, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTemp8 = RSIOM_EN_STEP2; //0x5E
    fnRN8302_Write(RN830x_RSIOM_CTL, EmuCommbuf.ucTempBuf, 1);

    for (i = 0; i < 50; i++)
    {
        SystemDelay(1);
        fnRN8302_Read(RN830x_RSIOM_STATUS, (u8 *)&status, 4) ;
        if (status & (1 << 10))
        {
            break;
        }
    }
    if (i == 50)
    {
        result = ERROR;
    }

    if (result == SUCCESS)
    {
        rsiom_cmd.WR_Status = 0x01;
        rsiom_cmd.DevNo = DevNo;
        rsiom_cmd.RegAddr = 0x01;
        rsiom_cmd.DATA = 0x5ea3; //01�Ĵ���д��0x5E3A,BGR_TRIMдʹ��
        Std_Memcpy((u8 *)&EmuCommbuf.ucTempBuf[0], (u8 *)&rsiom_cmd, 4);
        fnRN8302_Write(RN830x_RSIOM_CMD, EmuCommbuf.ucTempBuf, 4);

        SystemDelay(1);
        fnRN8302_Read(RN830x_RSIOM_STATUS, (u8 *)&status, 4) ;

        for (i = 0; i < 50; i++)
        {
            SystemDelay(1);
            fnRN8302_Read(RN830x_RSIOM_STATUS, (u8 *)&status, 4) ;
            if (status & (1 << 8)) //bit8 �Ƿ�Ϊ1����Ӧ�ж�
            {
                break;
            }
        }
        if (i == 50)
        {
            result = ERROR;
        }

        if (rsiom_cmd.DevNo)
        {
            if (!(status & (1 << rsiom_cmd.DevNo)))
            {
                result = ERROR;
            }
        }
        else   //�㲥ģʽ
        {
            if ((!(status & (1 << 1))) || (!(status & (1 << 2))) || (!(status & (1 << 3)))) //bit1~bit3 ��һ����Ӧ�������˳�
            {
                result = ERROR;
            }
        }
    }

    if (result == SUCCESS)
    {
        rsiom_cmd.WR_Status = 0x01;
        rsiom_cmd.DevNo = DevNo;
        rsiom_cmd.RegAddr = Reg;
        if (Reg == 0) //TRIM�Ĵ��������⴦��
        {
            rsiom_cmd.DATA = Data & 0x7F; //ȡ��7bit
            rsiom_cmd.DATA |= (Data >> 1) & 0xFF80;
        }
        else
        {
            rsiom_cmd.DATA = Data;
        }

        Std_Memcpy((u8 *)&EmuCommbuf.ucTempBuf[0], (u8 *)&rsiom_cmd, 4);
        fnRN8302_Write(RN830x_RSIOM_CMD, EmuCommbuf.ucTempBuf, 4);

        SystemDelay(1);
        fnRN8302_Read(RN830x_RSIOM_STATUS, (u8 *)&status, 4) ;
        for (i = 0; i < 50; i++)
        {
            SystemDelay(1);
            fnRN8302_Read(RN830x_RSIOM_STATUS, (u8 *)&status, 4) ;
            if (status & (1 << 8)) //bit8 �Ƿ�Ϊ1����Ӧ�ж�
            {
                break;
            }
        }
        if (i == 50)
        {
            result = ERROR;
        }

        if (rsiom_cmd.DevNo)
        {
            if (!(status & (1 << rsiom_cmd.DevNo)))
            {
                result = ERROR;
            }
        }
        else   //�㲥ģʽ
        {
            if ((!(status & (1 << 1))) || (!(status & (1 << 2))) || (!(status & (1 << 3)))) //bit1~bit3 ��һ����Ӧ�������˳�
            {
                result = ERROR;
            }
        }
    }
    SystemDelay(8); //����ȴ���ƽʱ��8ms����ܷ����˳�rsiom��������п����޷��˳�rsiomģʽ

    EmuCommbuf.ucTemp8 = RSIOM_DIS_STEP1;
    fnRN8302_Write(RN830x_RSIOM_CTL, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTemp8 = RSIOM_DIS_STEP2;
    fnRN8302_Write(RN830x_RSIOM_CTL, EmuCommbuf.ucTempBuf, 1);

    //-------------------------
    SystemDelay(1);
    fnRN8302_Read(RN830x_RSIOM_STATUS, (u8 *)&status, 4) ;
    for (i = 0; i < 50; i++)
    {
        SystemDelay(1);
        fnRN8302_Read(RN830x_RSIOM_STATUS, (u8 *)&status, 4) ;
        if (status & (1 << 8)) //bit8 �Ƿ�Ϊ1����Ӧ�ж�
        {
            break;
        }
    }
    if (i == 50)
    {
        result = ERROR;
    }

    if (rsiom_cmd.DevNo)
    {
        if (!(status & (1 << rsiom_cmd.DevNo)))
        {
            result = ERROR;
        }
    }
    else   //�㲥ģʽ
    {
        if ((!(status & (1 << 1))) || (!(status & (1 << 2))) || (!(status & (1 << 3)))) //bit1~bit3 ��һ����Ӧ�������˳�
        {
            result = ERROR;
        }
    }

    EmuCommbuf.ucTemp8 = RN8302_WREN_DIS; //
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    fnRN8302_Read(RN8302_WREN2, &EmuCommbuf.ucTempBuf[0], 4); //�ȶ�ȡ��λ�����Ƿ���Ч
    if (EmuCommbuf.ucTempBuf[0]) //��λ������Ч
    {
        EmuCommbuf.ucTempBuf[0] = 0xAA;
    }
    else
    {
        EmuCommbuf.ucTempBuf[0] = 0x55;
    }
    EmuCommbuf.ucTempBuf[1] = RN8302_WREN_DIS;   //
    EmuCommbuf.ucTempBuf[2] = 0;
    EmuCommbuf.ucTempBuf[3] = 0;
    fnRN8302_Write(RN8302_WREN2, EmuCommbuf.ucTempBuf, 4);

    return result;
}

/*****************************************************************************
** Function name:   fnRN8302_TIRM(u32  tirm)
**
** Description: �޸�8302 TIRMֵ
**
** Parameters:  tirm    :�����õ�tirmֵ
**
** Returned value:  SUCCESS:���óɹ�; ERROR:����ʧ��
**
******************************************************************************/
u8 fnRN8302_TIRM(u32  tirm)
{
    sDataComm_TypeDef      EmuCommbuf;
    u32 status;
    u8  result;

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // дʹ��λ
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTemp8 = 0xE5; //
    fnRN8302_Write(RN830x_ADCIN_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTemp8 = 0x5A; //
    fnRN8302_Write(RN830x_BGR_HT, EmuCommbuf.ucTempBuf, 1);

    fnRN8302_Read(RN830x_OTPTRIM_STA, (u8 *)&status, 4);

    if (status & 0x01) //OTPTRIM_STA.otptrim_inʹ��ʱ��RN830x_OTPDBG�Ĵ���������
    {
        fnRN8302_Read(RN830x_OTPTRIM, EmuCommbuf.ucTempBuf, 3);

        //-�������ģʽ��0x02 0xBA 0x7F 0x5C
        //-����˳��������д��4��BYTE���ݣ������м䲻�ܲ����κ�������д�����������ſ��Խ������ģʽ��
        //-�ڵ���ģʽ�£��ſ��Զ�OTP���ж�д����
        //--fnRN8302_Write-дRN830x_OTPDBG�Ĵ���ʱ������ͨ����0x018D�Ĵ�������Ч�飬����ᵼ���޷��������ģʽ-

        EmuCommbuf.ucTemp8 = 0x02;
        fnRN8302_Write(RN830x_OTPDBG, EmuCommbuf.ucTempBuf, 1);
        EmuCommbuf.ucTemp8 = 0xBA;
        fnRN8302_Write(RN830x_OTPDBG, EmuCommbuf.ucTempBuf, 1);
        EmuCommbuf.ucTemp8 = 0x7F;
        fnRN8302_Write(RN830x_OTPDBG, EmuCommbuf.ucTempBuf, 1);
        EmuCommbuf.ucTemp8 = 0x5C;
        fnRN8302_Write(RN830x_OTPDBG, EmuCommbuf.ucTempBuf, 1);

        EmuCommbuf.lTemp32 = 0;
        fnRN8302_Read(RN830x_OTPTRIM, EmuCommbuf.ucTempBuf, 3);

        EmuCommbuf.lTemp32 = tirm;
        fnRN8302_Write(RN830x_OTPTRIM, EmuCommbuf.ucTempBuf, 3);

        EmuCommbuf.lTemp32 = 0;
        fnRN8302_Read(RN830x_OTPTRIM, EmuCommbuf.ucTempBuf, 3);
        if (EmuCommbuf.lTemp32 != tirm)
        {
            result = ERROR;
        }
        else
        {
            result = SUCCESS;
        }
    }
    else
    {
        result = ERROR;
    }

    EmuCommbuf.ucTemp8 = RN8302_WREN_DIS; //
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    return result;
}

/*****************************************************************************
** Function name:fnMeasure_RN8302TIRM_CommWrite
**
** Description:ͨѶ����8302 tirmֵ
**
** Parameters:
**
** Returned value:
**
******************************************************************************/
void fnMeasure_TIRM_CommWrite(u16 data)
{
    MeasureRepairPara.TIRM = data;

    fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_RN8302TIRM, (u8 *)&MeasureRepairPara.TIRM, FileItemInfoLen_VoltRepair_RN8302TIRM);

    fnRN8302_TIRM(MeasureRepairPara.TIRM);
}

/*****************************************************************************
** Function name:fnMeasure_RN8302TIRM_CommRead
**
** Description:ͨѶ��ȡ8302 tirmֵ
**
** Parameters:��ȡ����
**
** Returned value:���ݳ���
**
******************************************************************************/
u8 fnMeasure_TIRM_CommRead(u8 *data)
{
    u8 len;

    Std_Memcpy(data, (u8 *)&MeasureRepairPara.TIRM,  FileItemInfoLen_VoltRepair_RN8302TIRM);

    len = FileItemInfoLen_VoltRepair_RN8302TIRM;

    return len;
}

/*****************************************************************************
** Function name:fnMeasure_RN8207DTIRM_CommWrite
**
** Description:ͨѶ����8207D tirmֵ
**
** Parameters:
**
** Returned value:
**
******************************************************************************/
void fnMeasure_RN8207DTIRM_CommWrite(u8 nphase, u16 data)
{
    //u8  result;

    //  MeasureRepairPara.RN8207D_TIRM[nphase] = data;
    //
    //  fnFile_Write(FileId_FirmPara , FileItemInfoOffAddr_VoltRepair_RN8207DTIRM + nphase * 2, (u8 *)&MeasureRepairPara.RN8207D_TIRM[nphase] , 2);
    //
    //  result = fnRN830x_RSIOM( nphase , 0x00 , MeasureRepairPara.RN8207D_TIRM[nphase]);   //Vref=1.243V,data��ֵ������SPIͨѶʱһ��

    //  if(result == ERROR)
    //  {
    //      SystemDelay(10);  //�������ʱ10ms���ٲ���һ��
    //      result = fnRN830x_RSIOM( nphase , 0x00 , MeasureRepairPara.RN8207D_TIRM[nphase]);
    //  }
}

/*****************************************************************************
** Function name:fnMeasure_RN8207DTIRM_ComRead
**
** Description:ͨѶ��ȡ8207D tirmֵ
**
** Parameters:��ȡ����
**
** Returned value:���ݳ���
**
******************************************************************************/
u8 fnMeasure_RN8207DTIRM_CommRead(u8 *data)
{
    u8 len = 0;

    //  Std_Memcpy(data , (u8 *)&MeasureRepairPara.RN8207D_TIRM[0],  FileItemInfoLen_VoltRepair_RN8207DTIRM);
    //
    //  len = FileItemInfoLen_VoltRepair_RN8207DTIRM;

    return len;
}

/*****************************************************************************
** Function name:   fnRN8302C_Rest(void)
**
** Description: RN8302C��λ���㣬RN8207��Դ�رգ�
**                   �����ϵ�1bit�����ȶ��������
** Parameters:      NONE
**
** Returned value:  NONE
**
******************************************************************************/
#if( (RN8302C_Ver == RN8302C)||(RN8302C_Ver == RN8302C_V3) )
void fnRN8302C_Rest(void)
{
    Rn8xxx_GPIO_CfgFun(PinMS_RST, _NORMALIO); /*"RN8302��λ����"*/
    Rn8xxx_GPIO_CfgIOMode(PinMS_RST, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinMS_RST, 0);

    RN8207_PowerOff();

    RN8302_PowerOff();

    SystemDelay(10);

    RN8207_PowerOn();
    RN8302_PowerOn();

    SystemDelay(20);

    Rn8xxx_GPIO_CfgFun(PinMS_RST, _NORMALIO); //"Ӳ����λ"//
    Rn8xxx_GPIO_CfgIOMode(PinMS_RST, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinMS_RST, 1);

    SystemDelay(10);
}
#endif

/*****************************************************************************
** Function name:   fnRN8302_Stop(void)
**
** Description:     �رռ���
**
** Parameters:      NONE
**
** Returned value:  NONE
**
******************************************************************************/
void fnRN8302_Stop(void)
{
    Std_Memset(&MeasureRegTmp, 0, sizeof(sMeasureRegTmp_TypeDef));
    Std_Memset(&MeasureRms, 0, sizeof(sMeasureRms_TypeDef));

    #if( (RN8302C_Ver == RN8302C)||(RN8302C_Ver == RN8302C_V3) )
    //    Rn8xxx_GPIO_CfgFun(PinMS_RST,_NORMALIO);/*"RN8302��λ����"*/
    //  Rn8xxx_GPIO_CfgIOMode( PinMS_RST , GPIO_MODE_OUT , NORMAL_OUT ); /*""*/
    //    Rn8xxx_GPIO_SetPin( PinMS_RST , 0);//zhupdebug
    Rn8xxx_GPIO_CfgFun(PinMS_RST, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinMS_RST, GPIO_MODE_NORMAL, NORMAL_IN);

    #endif

    /*"ֹͣ�����Ƚ�ͨѶIO������Ϊ���벻ʹ�ܷ�ֹ©��"*/
    Rn8xxx_GPIO_CfgFun(PinSCS_C, _NORMALIO); /*"RN8302ͨѶSPI ��CS��"*/
    Rn8xxx_GPIO_CfgIOMode(PinSCS_C, GPIO_MODE_NORMAL, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinSCLK, _NORMALIO); /*"RN8302ͨѶSPI ��CLK��"*/
    Rn8xxx_GPIO_CfgIOMode(PinSCLK, GPIO_MODE_NORMAL, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinSDI_C, _NORMALIO); /*"RN8302ͨѶSPI ��MOSI��"*/
    Rn8xxx_GPIO_CfgIOMode(PinSDI_C, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinSDI_C, Pull_ON); // dyf ��Ҫ�ر��ڲ�Ĭ�ϵ��������裬�����µ���󹦺ıȽϸߣ�Pull_ON ��Ӧ�ر��������������������ò�ͬ

    Rn8xxx_GPIO_CfgPullMode(PinSDO_C, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinSDO_C, _NORMALIO); /*"RN8302ͨѶSPI ��MISO��"*/
    Rn8xxx_GPIO_CfgIOMode(PinSDO_C, GPIO_MODE_NORMAL, NORMAL_IN);

    // RN8207_PowerOff();
    // RN8302_PowerOff();

    Rn8xxx_GPIO_CfgFun(PinRN8302_Power, _NORMALIO); /*"RN8302ͨѶSPI ��MISO��"*/
    Rn8xxx_GPIO_CfgIOMode(PinRN8302_Power, GPIO_MODE_NORMAL, NORMAL_IN);

    #if( (RN8302C_Ver == RN8302C)||(RN8302C_Ver == RN8302C_V3) )
    Rn8xxx_GPIO_CfgFun(PinRN8207_Power, _NORMALIO); /*"RN8302ͨѶSPI ��MISO��"*/
    Rn8xxx_GPIO_CfgIOMode(PinRN8207_Power, GPIO_MODE_NORMAL, NORMAL_IN);
    #endif
}

/*****************************************************************************
** Function name:   fnRN8302Mode_Init(eMeasureMode_TypeDef MeasureMode)
**
** Description: RN8302ģʽ��ʼ��:����ģʽ��ȫʧѹģʽѡ��
**
** Parameters:      NONE
**
** Returned value:  NONE
**
******************************************************************************/
void fnRN8302Mode_Init(eMeasureMode_TypeDef MeasureMode)
{
    sDataComm_TypeDef      EmuCommbuf;

    //-------����ע��-----------
    fnRN8302_ApiRegister(Rn8302_SpiCS, Rn8302Spi_ReadByte, Rn8302Spi_WriteByte, (void (*)(uint32_t))SystemDelayUs);

    Std_Memset(&MeasureRegTmp, 0, sizeof(sMeasureRegTmp_TypeDef));
    Std_Memset(&MeasureRms, 0, sizeof(sMeasureRms_TypeDef));

    #if( (RN8302C_Ver == RN8302C)||(RN8302C_Ver == RN8302C_V3) )
    fnRN8302C_Rest();
    #else
    RN8302_PowerOn();
    #endif

    Rn8302_Spi_Init();   //SPI��ʼ��

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // дʹ��λ
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    //----RN8302C������ʹ���ڲ����ⲿADC----------------------
    #if(RN8302C_Ver == RN8302C_V3)
    //"���õ�ѹ����������1bit��ģʽ"//
    EmuCommbuf.ucTemp8 = 0XEA; //
    fnRN8302_Write(0x01A1, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.wTemp16 = 0; //
    fnRN8302_Read(0x01A0, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.wTemp16 |= BIT7; // Inѡ��ADC����,���߲���8207D
    EmuCommbuf.wTemp16 |= BIT12; //Uͨ��1bit��Դ����ADC
    EmuCommbuf.wTemp16 |= BIT13; // ADIN_CKO�������2.048MHzʱ��

    fnRN8302_Write(0x01A0, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.lTemp32 = 0; //
    fnRN8302_Read(0x01A0, EmuCommbuf.ucTempBuf, 2);

    #elif (RN8302C_Ver == RN8302C)
    //"���õ�ѹ����������1bit��ģʽ"//
    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // дʹ��λ
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTemp8 = 0XEA; //
    fnRN8302_Write(0x01A1, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.wTemp16 = 0; //
    fnRN8302_Read(0x01A0, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.wTemp16 |= BIT12; //Uͨ��1bit��Դ����ADC
    fnRN8302_Write(0x01A0, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.lTemp32 = 0; //
    fnRN8302_Read(0x01A0, EmuCommbuf.ucTempBuf, 2);
    #endif

    if (MeasureModeEMM == MeasureMode)
    {
        EmuCommbuf.ucTemp8 = 0xA2; // �л���EMMģʽ
        fnRN8302_Write(RN8302_WMSW, EmuCommbuf.ucTempBuf, 1);
    }
    else if (MeasureModeNVM1 == MeasureMode)
    {
        EmuCommbuf.ucTemp8 = 0xE1; // �л���NVM1ģʽ
        fnRN8302_Write(RN8302_WMSW, EmuCommbuf.ucTempBuf, 1);
    }

    EmuCommbuf.ucTemp8 = 0xDC; // д����
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
}

/*****************************************************************************
** Function name:   fnMeasure_EMUInit(eMeasureMode_TypeDef MeasureMode)
**
** Description: �����Ĵ�����ʼ��
**
** Parameters:      NONE
**
** Returned value:  NONE
**
******************************************************************************/
void fnMeasure_EMUInit(void)
{
    u8  i, result;
    sDataComm_TypeDef      EmuCommbuf;

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // дʹ��λ
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    if (Bkgrd.PubData.Active != BKGRD_ACTIVE_POWDN)
    {
        EmuCommbuf.ucTemp8 = 0xA2; // �л���EMMģʽ
        fnRN8302_Write(RN8302_WMSW, EmuCommbuf.ucTempBuf, 1);
    }
    else
    {
        EmuCommbuf.ucTemp8 = 0x5C; // �л���NVM2ģʽ
        fnRN8302_Write(RN8302_WMSW, EmuCommbuf.ucTempBuf, 1);
    }
    SystemDelay(1);
    EmuCommbuf.ucTemp8 = 0xfa; // ��λ
    fnRN8302_Write(RN8302_SOFTRST, EmuCommbuf.ucTempBuf, 1);
    SystemDelay(150);

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // дʹ��λ
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTempBuf[0] = 0x77; // ��������λ
    EmuCommbuf.ucTempBuf[1] = 0x77;
    EmuCommbuf.ucTempBuf[2] = 0x77;
    fnRN8302_Write(RN8302_EMUCON, EmuCommbuf.ucTempBuf, 3);

    fnRN8302_Read(RN8302_HFConst2, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.wTemp16 = MeasureFirmPara.HFConst1;
    fnRN8302_Write(RN8302_HFConst2, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.wTemp16 = MeasureFirmPara.HFConst1 / MeasureFirmPara.HighPulseRate;
    fnRN8302_Write(RN8302_HFConst1, EmuCommbuf.ucTempBuf, 2);

    // ��ѹ�����ʼ��
    fnRN8302_Write(RN8302_GSUA, (u8 *)&MeasureFirmPara.GSU[0], 2);
    fnRN8302_Write(RN8302_GSUB, (u8 *)&MeasureFirmPara.GSU[1], 2);
    fnRN8302_Write(RN8302_GSUC, (u8 *)&MeasureFirmPara.GSU[2], 2);

    // ���������ʼ��
    fnRN8302_Write(RN8302_GSIA, (u8 *)&MeasureFirmPara.GSI[0], 2);
    fnRN8302_Write(RN8302_GSIB, (u8 *)&MeasureFirmPara.GSI[1], 2);
    fnRN8302_Write(RN8302_GSIC, (u8 *)&MeasureFirmPara.GSI[2], 2);
    fnRN8302_Write(RN8302_GSIN, (u8 *)&MeasureFirmPara.GSI[3], 2);

    // ͨ����λУ��
    fnRN8302_Write(RN8302_PRTH1L, (u8 *)&MeasureFirmPara.PRth[0], 2);
    fnRN8302_Write(RN8302_PRTH1H, (u8 *)&MeasureFirmPara.PRth[1], 2);
    fnRN8302_Write(RN8302_PRTH2L, (u8 *)&MeasureFirmPara.PRth[2], 2);
    fnRN8302_Write(RN8302_PRTH2H, (u8 *)&MeasureFirmPara.PRth[3], 2); // ͨ����λ�ֶβ���

    // ͨ����λУ��
    fnRN8302_Write(RN8302_PHSIA, (u8 *)&MeasureFirmPara.PHSI[0], 3);
    fnRN8302_Write(RN8302_PHSIB, (u8 *)&MeasureFirmPara.PHSI[1], 3);
    fnRN8302_Write(RN8302_PHSIC, (u8 *)&MeasureFirmPara.PHSI[2], 3);

    fnRN8302_Write(RN8302_PA_PHSL, (u8 *)&MeasureFirmPara.P_PHS[0], 2);
    fnRN8302_Write(RN8302_PB_PHSL, (u8 *)&MeasureFirmPara.P_PHS[1], 2);
    fnRN8302_Write(RN8302_PC_PHSL, (u8 *)&MeasureFirmPara.P_PHS[2], 2);

    fnRN8302_Write(RN8302_QA_PHSL, (u8 *)&MeasureFirmPara.Q_PHS[0], 2);
    fnRN8302_Write(RN8302_QB_PHSL, (u8 *)&MeasureFirmPara.Q_PHS[1], 2);
    fnRN8302_Write(RN8302_QC_PHSL, (u8 *)&MeasureFirmPara.Q_PHS[2], 2);

    fnRN8302_Write(RN8302_GPA, (u8 *)&MeasureFirmPara.GP[0], 2);
    fnRN8302_Write(RN8302_GPB, (u8 *)&MeasureFirmPara.GP[1], 2);
    fnRN8302_Write(RN8302_GPC, (u8 *)&MeasureFirmPara.GP[2], 2);

    fnRN8302_Write(RN8302_GQA, (u8 *)&MeasureFirmPara.GQ[0], 2);
    fnRN8302_Write(RN8302_GQB, (u8 *)&MeasureFirmPara.GQ[1], 2);
    fnRN8302_Write(RN8302_GQC, (u8 *)&MeasureFirmPara.GQ[2], 2);

    fnRN8302_Write(RN8302_GSA, (u8 *)&MeasureFirmPara.GS[0], 2);
    fnRN8302_Write(RN8302_GSB, (u8 *)&MeasureFirmPara.GS[1], 2);
    fnRN8302_Write(RN8302_GSC, (u8 *)&MeasureFirmPara.GS[2], 2);

    // ��ѹ��������ЧֵOFFSETУ��
    fnRN8302_Write(RN8302_UA_OS, (u8 *)&MeasureFirmPara.U_OS[0], 2);
    fnRN8302_Write(RN8302_UB_OS, (u8 *)&MeasureFirmPara.U_OS[1], 2);
    fnRN8302_Write(RN8302_UC_OS, (u8 *)&MeasureFirmPara.U_OS[2], 2);

    fnRN8302_Write(RN8302_IA_OS, (u8 *)&MeasureFirmPara.I_OS[0], 2);
    fnRN8302_Write(RN8302_IB_OS, (u8 *)&MeasureFirmPara.I_OS[1], 2);
    fnRN8302_Write(RN8302_IC_OS, (u8 *)&MeasureFirmPara.I_OS[2], 2);
    // ͨ������OFFSETУ��
    fnRN8302_Write(RN8302_PA_OS, (u8 *)&MeasureFirmPara.P_OS[0], 2);
    fnRN8302_Write(RN8302_PB_OS, (u8 *)&MeasureFirmPara.P_OS[1], 2);
    fnRN8302_Write(RN8302_PC_OS, (u8 *)&MeasureFirmPara.P_OS[2], 2);

    fnRN8302_Write(RN8302_QA_OS, (u8 *)&MeasureFirmPara.Q_OS[0], 2);
    fnRN8302_Write(RN8302_QB_OS, (u8 *)&MeasureFirmPara.Q_OS[1], 2);
    fnRN8302_Write(RN8302_QC_OS, (u8 *)&MeasureFirmPara.Q_OS[2], 2);

    fnRN8302_Write(RN8302_IStart_PS, (u8 *)&MeasureFirmPara.Start_Ps, 2);
    fnRN8302_Write(RN8302_IStart_Q, (u8 *)&MeasureFirmPara.Start_Q, 2);
    fnRN8302_Write(RN8302_LostVoltT, (u8 *)&MeasureFirmPara.ELostVoltT, 2);
    fnRN8302_Write(RN8302_ZXOT, (u8 *)&MeasureFirmPara.Zxot, 2);

    for (i = 0; i < 6; i++)
    {
        fnRN8302_Write(RN8302_PA_PHSM + i, (u8 *)&MeasureFirmPara.P_PHSMH[i], 3);
        fnRN8302_Write(RN8302_QA_PHSM + i, (u8 *)&MeasureFirmPara.Q_PHSMH[i], 3);
    }

    #if(CT_Check == 1)
    EmuCommbuf.ucTemp8 = 0x19;   // �迹���ʹ�� Ĭ��ֵ 00
    fnRN8302_Write(0x015f, EmuCommbuf.ucTempBuf, 1);
    EmuCommbuf.ucTempBuf[0] = 0x00; // ADC���üĴ��� Ĭ��ֵ 0000
    EmuCommbuf.ucTempBuf[1] = 0x30;
    fnRN8302_Write(RN8302_ADCCFG, EmuCommbuf.ucTempBuf, 2);
    //MeasureRegTmp.ChkSum1 = ((MeasureRegTmp.ChkSum1 - 0x00010000)&0x00ffffff);
    //MeasureRegTmp.ChkSum1 = ((MeasureRegTmp.ChkSum1 + 0x003dffbf)&0x00ffffff);
    #endif

    //  #if(RN8302C_Ver == RN8302C_V3)
    EmuCommbuf.wTemp16 = 0; //
    fnRN8302_Read(RN8302_ADCCFG, EmuCommbuf.ucTempBuf, 2);
    EmuCommbuf.wTemp16 |= BIT15; //
    fnRN8302_Write(RN8302_ADCCFG, EmuCommbuf.ucTempBuf, 2);
    //  #endif

    EmuCommbuf.ucTempBuf[0] = 0x98;
    EmuCommbuf.ucTempBuf[1] = 0xba;
    EmuCommbuf.ucTempBuf[2] = 0x07;
    fnRN8302_Write(RN8302_CFCFG, EmuCommbuf.ucTempBuf, 3);  // ��HFCONST2Ϊ��Ƶ���峣���������

    EmuCommbuf.ucTempBuf[0] = 0x00; // ��������λ Ĭ��ֵ 400000
    EmuCommbuf.ucTempBuf[1] = 0x00;
    EmuCommbuf.ucTempBuf[2] = 0x40; //      // �����ߵ�������ʸ���� 0x44    �������ߵ�������ʸ���� 0x40
    fnRN8302_Write(RN8302_EMUCFG, EmuCommbuf.ucTempBuf, 3);

    if (Bkgrd.PriPara.WireMode == 0x01)
    {
        EmuCommbuf.wTemp16 = 0x33;
        fnRN8302_Write(RN8302_MODSEL, EmuCommbuf.ucTempBuf, 1); // �л���3P3ģʽ
    }

    #if((RN8302C_Ver == RN8306)||(PCB_Version==RN8611_RN7306))
    fnRN8302_HSDCMode_Init();
    #endif

    #if( (RN8302C_Ver == RN8302C_V3)||(RN8302C_Ver == RN8306))
    // fnRN830x_RSIOM(0x00 , 0x00 , 0x3C);  //VtrimΪmin,Vref=1.403V ,data��ֵ������SPIͨѶʱһ��
    // fnRN830x_RSIOM(0x00 , 0x00 , 0x3F3c);  //VtrimΪmax,Vref=1.265V, data��ֵ������SPIͨѶʱһ��
    // fnRN830x_RSIOM(0x00 , 0x00 , 0x463C);   //Vref=1.248V Ĭ��ֵdata��ֵ������SPIͨѶʱһ��
    //  for(i = 0 ; i < 3 ; i++)
    //  {
    //      fnRN830x_RSIOM( i , 0x00 , MeasureRepairPara.RN8207D_TIRM[i]);   //Vref=1.243V,data��ֵ������SPIͨѶʱһ��
    //      if(result == ERROR)
    //      {
    //          SystemDelay(10);  //�������ʱ10ms���ٲ���һ��
    //          result = fnRN830x_RSIOM( i , 0x00 , MeasureRepairPara.RN8207D_TIRM[i]);
    //      }
    //  }

    result = fnRN8302_TIRM(MeasureRepairPara.TIRM);
    if (result == ERROR)
    {
        SystemDelay(10);
        result = fnRN8302_TIRM(MeasureRepairPara.TIRM);
    }

    #endif

    // dyf �ͼ���Ҫ֧�����Ȳ������ܣ���߾��ȣ�Ϊ���ø��߷���
    result = fnRN8302_TIRM(MeasureRepairPara.TIRM);
    if (result == ERROR)
    {
        SystemDelay(10);
        result = fnRN8302_TIRM(MeasureRepairPara.TIRM);
    }

    EmuCommbuf.ucTemp8 = 0xDC; // д����
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
    MeasureFirmPara.FractionP = 0x04;
    MeasureFirmPara.FractionI = 0x04;
    MeasureFirmPara.FractionU = 0x02;
}

void fnMeasure_EvtVoltLossEMUInit(void)
{
    u8  i, result;
    sDataComm_TypeDef      EmuCommbuf;

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // дʹ��λ
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTemp8 = 0xA2; // �л���EMMģʽ
    fnRN8302_Write(RN8302_WMSW, EmuCommbuf.ucTempBuf, 1);

    SystemDelay(1);
    EmuCommbuf.ucTemp8 = 0xfa; // ��λ
    fnRN8302_Write(RN8302_SOFTRST, EmuCommbuf.ucTempBuf, 1);
    SystemDelay(150);

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // дʹ��λ
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTempBuf[0] = 0x77; // ��������λ
    EmuCommbuf.ucTempBuf[1] = 0x77;
    EmuCommbuf.ucTempBuf[2] = 0x77;
    fnRN8302_Write(RN8302_EMUCON, EmuCommbuf.ucTempBuf, 3);

    fnRN8302_Read(RN8302_HFConst2, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.wTemp16 = MeasureFirmPara.HFConst1;
    fnRN8302_Write(RN8302_HFConst2, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.wTemp16 = MeasureFirmPara.HFConst1 / MeasureFirmPara.HighPulseRate;
    fnRN8302_Write(RN8302_HFConst1, EmuCommbuf.ucTempBuf, 2);

    // ��ѹ�����ʼ��
    fnRN8302_Write(RN8302_GSUA, (u8 *)&MeasureFirmPara.GSU[0], 2);
    fnRN8302_Write(RN8302_GSUB, (u8 *)&MeasureFirmPara.GSU[1], 2);
    fnRN8302_Write(RN8302_GSUC, (u8 *)&MeasureFirmPara.GSU[2], 2);

    // ���������ʼ��
    fnRN8302_Write(RN8302_GSIA, (u8 *)&MeasureFirmPara.GSI[0], 2);
    fnRN8302_Write(RN8302_GSIB, (u8 *)&MeasureFirmPara.GSI[1], 2);
    fnRN8302_Write(RN8302_GSIC, (u8 *)&MeasureFirmPara.GSI[2], 2);
    fnRN8302_Write(RN8302_GSIN, (u8 *)&MeasureFirmPara.GSI[3], 2);

    // ͨ����λУ��
    fnRN8302_Write(RN8302_PRTH1L, (u8 *)&MeasureFirmPara.PRth[0], 2);
    fnRN8302_Write(RN8302_PRTH1H, (u8 *)&MeasureFirmPara.PRth[1], 2);
    fnRN8302_Write(RN8302_PRTH2L, (u8 *)&MeasureFirmPara.PRth[2], 2);
    fnRN8302_Write(RN8302_PRTH2H, (u8 *)&MeasureFirmPara.PRth[3], 2); // ͨ����λ�ֶβ���

    // ͨ����λУ��
    fnRN8302_Write(RN8302_PHSIA, (u8 *)&MeasureFirmPara.PHSI[0], 3);
    fnRN8302_Write(RN8302_PHSIB, (u8 *)&MeasureFirmPara.PHSI[1], 3);
    fnRN8302_Write(RN8302_PHSIC, (u8 *)&MeasureFirmPara.PHSI[2], 3);

    fnRN8302_Write(RN8302_PA_PHSL, (u8 *)&MeasureFirmPara.P_PHS[0], 2);
    fnRN8302_Write(RN8302_PB_PHSL, (u8 *)&MeasureFirmPara.P_PHS[1], 2);
    fnRN8302_Write(RN8302_PC_PHSL, (u8 *)&MeasureFirmPara.P_PHS[2], 2);

    fnRN8302_Write(RN8302_QA_PHSL, (u8 *)&MeasureFirmPara.Q_PHS[0], 2);
    fnRN8302_Write(RN8302_QB_PHSL, (u8 *)&MeasureFirmPara.Q_PHS[1], 2);
    fnRN8302_Write(RN8302_QC_PHSL, (u8 *)&MeasureFirmPara.Q_PHS[2], 2);

    fnRN8302_Write(RN8302_GPA, (u8 *)&MeasureFirmPara.GP[0], 2);
    fnRN8302_Write(RN8302_GPB, (u8 *)&MeasureFirmPara.GP[1], 2);
    fnRN8302_Write(RN8302_GPC, (u8 *)&MeasureFirmPara.GP[2], 2);

    fnRN8302_Write(RN8302_GQA, (u8 *)&MeasureFirmPara.GQ[0], 2);
    fnRN8302_Write(RN8302_GQB, (u8 *)&MeasureFirmPara.GQ[1], 2);
    fnRN8302_Write(RN8302_GQC, (u8 *)&MeasureFirmPara.GQ[2], 2);

    fnRN8302_Write(RN8302_GSA, (u8 *)&MeasureFirmPara.GS[0], 2);
    fnRN8302_Write(RN8302_GSB, (u8 *)&MeasureFirmPara.GS[1], 2);
    fnRN8302_Write(RN8302_GSC, (u8 *)&MeasureFirmPara.GS[2], 2);

    // ��ѹ��������ЧֵOFFSETУ��
    fnRN8302_Write(RN8302_UA_OS, (u8 *)&MeasureFirmPara.U_OS[0], 2);
    fnRN8302_Write(RN8302_UB_OS, (u8 *)&MeasureFirmPara.U_OS[1], 2);
    fnRN8302_Write(RN8302_UC_OS, (u8 *)&MeasureFirmPara.U_OS[2], 2);

    fnRN8302_Write(RN8302_IA_OS, (u8 *)&MeasureFirmPara.I_OS[0], 2);
    fnRN8302_Write(RN8302_IB_OS, (u8 *)&MeasureFirmPara.I_OS[1], 2);
    fnRN8302_Write(RN8302_IC_OS, (u8 *)&MeasureFirmPara.I_OS[2], 2);
    // ͨ������OFFSETУ��
    fnRN8302_Write(RN8302_PA_OS, (u8 *)&MeasureFirmPara.P_OS[0], 2);
    fnRN8302_Write(RN8302_PB_OS, (u8 *)&MeasureFirmPara.P_OS[1], 2);
    fnRN8302_Write(RN8302_PC_OS, (u8 *)&MeasureFirmPara.P_OS[2], 2);

    fnRN8302_Write(RN8302_QA_OS, (u8 *)&MeasureFirmPara.Q_OS[0], 2);
    fnRN8302_Write(RN8302_QB_OS, (u8 *)&MeasureFirmPara.Q_OS[1], 2);
    fnRN8302_Write(RN8302_QC_OS, (u8 *)&MeasureFirmPara.Q_OS[2], 2);

    fnRN8302_Write(RN8302_IStart_PS, (u8 *)&MeasureFirmPara.Start_Ps, 2);
    fnRN8302_Write(RN8302_IStart_Q, (u8 *)&MeasureFirmPara.Start_Q, 2);
    fnRN8302_Write(RN8302_LostVoltT, (u8 *)&MeasureFirmPara.ELostVoltT, 2);
    fnRN8302_Write(RN8302_ZXOT, (u8 *)&MeasureFirmPara.Zxot, 2);

    for (i = 0; i < 6; i++)
    {
        fnRN8302_Write(RN8302_PA_PHSM + i, (u8 *)&MeasureFirmPara.P_PHSMH[i], 3);
        fnRN8302_Write(RN8302_QA_PHSM + i, (u8 *)&MeasureFirmPara.Q_PHSMH[i], 3);
    }

    EmuCommbuf.ucTempBuf[0] = 0x98;
    EmuCommbuf.ucTempBuf[1] = 0xba;
    EmuCommbuf.ucTempBuf[2] = 0x07;
    fnRN8302_Write(RN8302_CFCFG, EmuCommbuf.ucTempBuf, 3);  // ��HFCONST2Ϊ��Ƶ���峣���������
    EmuCommbuf.ucTempBuf[0] = 0x00; // ��������λ Ĭ��ֵ 400000
    EmuCommbuf.ucTempBuf[1] = 0x00;
    EmuCommbuf.ucTempBuf[2] = 0x40; //      // �����ߵ�������ʸ���� 0x44    �������ߵ�������ʸ���� 0x40
    fnRN8302_Write(RN8302_EMUCFG, EmuCommbuf.ucTempBuf, 3);

    if (Bkgrd.PriPara.WireMode == 0x01)
    {
        EmuCommbuf.wTemp16 = 0x33;
        fnRN8302_Write(RN8302_MODSEL, EmuCommbuf.ucTempBuf, 1); // �л���3P3ģʽ
    }

    #if((RN8302C_Ver == RN8306)||(PCB_Version==RN8611_RN7306))
    fnRN8302_HSDCMode_Init();
    #endif

    #if( (RN8302C_Ver == RN8302C_V3)||(RN8302C_Ver == RN8306))

    result = fnRN8302_TIRM(MeasureRepairPara.TIRM);
    if (result == ERROR)
    {
        SystemDelay(10);
        result = fnRN8302_TIRM(MeasureRepairPara.TIRM);
    }

    #endif

    EmuCommbuf.ucTemp8 = 0xDC; // д����
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
    MeasureFirmPara.FractionP = 0x04;
    MeasureFirmPara.FractionI = 0x04;
    MeasureFirmPara.FractionU = 0x02;
}

/*****************************************************************************
** Function name:u8 fnRN8302_ChkSum(void)
**
** Description:RN8302 Ч����ж�
**
** Parameters:NONE
**
** Returned value:TRUE=Ч�����ȷ;  FALSE=Ч�����
**
******************************************************************************/
u8 fnRN8302_ChkSum(void)
{
    //---------У����ж�------------------------
    MeasureRegTmp.ChkSum1 = 0;
    fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureRegTmp.ChkSum1, 3) ;

    if (MeasureRegTmp.ChkSum1 == MeasureFirmPara.ChkSum1)
    {
        MeasureRegTmp.ChkErrCnt = 0;
        MeasureRms.PriData.Flag &= ~MEASURE_FLAG_RST;
        return TRUE;
    }
    else
    {
        MeasureRegTmp.ChkSum1 = 0;
        fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureRegTmp.ChkSum1, 3) ;
        if (MeasureRegTmp.ChkSum1 != MeasureFirmPara.ChkSum1)
        {
            MeasureRegTmp.ChkErrCnt++;
            if (MeasureRegTmp.ChkErrCnt >= 5)
            {
                MeasureRms.PriData.Flag |= MEASURE_FLAG_RST;
                MeasureRegTmp.ChkErrCnt = 0;
            }
        }
        return FALSE;
    }
}

/*****************************************************************************
** Function name:fnMeasure_FirmParaInit
**
** Description:ͨѶ�Լ���RN8302���Ĵ������г�ʼ��
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnMeasure_FirmParaInit(u8 Flag)
{
    const sMeasureFirmPara_TypeDef  *pMeasureFirmPara = &FirmParaDefault;

    #if (HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_220_1_5)
    pMeasureFirmPara = &FirmParaDefault220_1_5;
    #elif (HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_577)
    pMeasureFirmPara = &FirmParaDefault577_1_5;
    #endif

    if (Flag == 1)  //��ʼ�������������ָ���Ĭ��ֵ
    {
        Std_Memset(&MeasureFirmPara, 0, sizeof(sMeasureFirmPara_TypeDef));

        Std_Memcpy((u8 *)&MeasureFirmPara, (u8 *)pMeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));

        fnCrc_Check(0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef) - 2, (u8 *)&MeasureFirmPara.Crc);

        fnFile_Write(FileId_FirmPara, 0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));
        //----------Ӱ��������--------------
        Std_Memset((u8 *)&MeasureRepairPara, 0x00, sizeof(sMeasureRepairPara_TypeDef));

        Std_Memcpy((u8 *)&MeasureRepairPara, (u8 *)&RepairParaDefault, sizeof(sMeasureRepairPara_TypeDef));

        fnCrc_Check(0, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc);

        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sMeasureRepairPara_TypeDef));

        fnHarmonic_FirmParaInit();
    }
    // ��ʼ����������Ĭ��ֵ,��������ֵ����
    else if (Flag == 2)
    {
        Std_Memset(&MeasureFirmPara, 0, sizeof(sMeasureFirmPara_TypeDef));

        Std_Memcpy((u8 *)&MeasureFirmPara, (u8 *)pMeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));

        fnCrc_Check(0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef) - 2, (u8 *)&MeasureFirmPara.Crc);

        fnFile_Write(FileId_FirmPara, 0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));
    }
    else   //ԭ���������Ϸ�����ԭУ���������������ʱʹ��
    {
        Std_Memset(&MeasureFirmPara, 0, sizeof(sMeasureFirmPara_TypeDef));
        fnFile_Read(FileId_FirmPara, 0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));
        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sMeasureRepairPara_TypeDef));

        if ((MeasureFirmPara.FractionI != pMeasureFirmPara->FractionI) || (MeasureFirmPara.HighPulseRate != pMeasureFirmPara->HighPulseRate))
        {
            Std_Memcpy((u8 *)&MeasureFirmPara, (u8 *)pMeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));

            fnCrc_Check(0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef) - 2, (u8 *)&MeasureFirmPara.Crc);

            fnFile_Write(FileId_FirmPara, 0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));

            //----------Ӱ��������--------------
            Std_Memset((u8 *)&MeasureRepairPara, 0x00, sizeof(sMeasureRepairPara_TypeDef));

            Std_Memcpy((u8 *)&MeasureRepairPara, (u8 *)&RepairParaDefault, sizeof(sMeasureRepairPara_TypeDef));

            fnCrc_Check(0, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sMeasureRepairPara_TypeDef));

            fnHarmonic_FirmParaInit();
        }
    }

    fnMeasure_EMUInit();

    SystemDelay(100);   // dyf ��CheckSum���׳���10 => 100
    MeasureFirmPara.ChkSum1 = 0;
    fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureFirmPara.ChkSum1, 3) ;
    fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_ChkSum1, (u8 *)&MeasureFirmPara.ChkSum1, FileItemInfoLen_FirmPara_ChkSum1);
}

/*****************************************************************************
** Function name:void fnRN8302_CorrectionMeter(void)
**
** Description:����RN8302����У������
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnRN8302_CorrectionMeter(void)
{
    u16 tempub, tempib;
    u32 tempus, tempis;
    float ADErr;
    u8 i, j;
    u32 temppw[2];
    u16 B;
    u16 tempangle[6];
    u8  TempBuf[12];
    u32 tempUI[6];
    sDataComm_TypeDef      EmuCommbuf;

    if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable != 1)
    {
        return;
    }

    Std_Memset((u8 *)&tempUI[0], 0x00, 24);
    MeasureFirmPara.HighPulseRate = DefaultHighPulseRate;
    if (MeasureRms.PriData.Flag & MEASURE_FLAG_CorrectionUI)
    {
        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_HFConst1, (u8 *)&MeasureFirmPara.HFConst1, 2);
        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RatedI, (u8 *)&tempib, 2);
        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RatedU, (u8 *)&tempub, 2);
        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RatedIrms, (u8 *)&tempis, 4);
        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RatedUrms, (u8 *)&tempus, 4);

        EmuCommbuf.wTemp16 = MeasureFirmPara.HFConst1;
        fnRN8302_Write(RN8302_HFConst2, EmuCommbuf.ucTempBuf, 2);
        EmuCommbuf.wTemp16 = MeasureFirmPara.HFConst1 / MeasureFirmPara.HighPulseRate;
        fnRN8302_Write(RN8302_HFConst1, EmuCommbuf.ucTempBuf, 2);
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                fnRN8302_Read(RN8302_UA + j, (u8 *)&temppw[0], 4);
                fnRN8302_Read(RN8302_IA + j, (u8 *)&temppw[1], 4);
                tempUI[j] += temppw[0];
                tempUI[j + 3] += temppw[1];
            }
            SystemDelay(250);
            fnWDT_Restart();
        }
        for (i = 0; i < 6; i++)
        {
            tempUI[i] = tempUI[i] / 3;
        }
        for (i = 0; i < 3; i++) //
        {
            fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealU + i * 4, (u8 *)&temppw[0], 4);
            temppw[1] = (((float)tempus / tempub) * ((float)temppw[0]) / 10);

            ADErr = ((float)tempUI[i] - temppw[1]) / temppw[1];
            ADErr = (-ADErr / (1 + ADErr));
            if (ADErr > 0)
            {
                MeasureFirmPara.GSU[i] = (u16)(ADErr * 32768 + 0.5);    //��������
            }
            else
            {
                MeasureFirmPara.GSU[i] = (u16)(65536 + ADErr * 32768 + 0.5);
            }
            fnRN8302_Write(RN8302_GSUA + i, (u8 *)&MeasureFirmPara.GSU[i], 2);
        }
        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_GSU, (u8 *)&MeasureFirmPara.GSU[0], 6);

        for (i = 0; i < 3; i++) //��������У��
        {
            fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealI + i * 4, (u8 *)&temppw[0], 4);
            temppw[1] = ((float)tempis / (float)tempib * (float)temppw[0]) / 10;

            ADErr = ((float)tempUI[i + 3] - (float)temppw[1]) / (float)temppw[1];
            ADErr = ((-ADErr) / (1 + ADErr));
            if (ADErr > 0)
            {
                MeasureFirmPara.GSI[i] = (u16)(ADErr * 32768 + 0.5);
            }
            else
            {
                MeasureFirmPara.GSI[i] = (u16)(65536 + ADErr * 32768 + 0.5);
            }
            fnRN8302_Write(RN8302_GSIA + i, (u8 *)&MeasureFirmPara.GSI[i], 2);
        }
        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_GSI, (u8 *)&MeasureFirmPara.GSI[0], 8);

        i = MeasureFirmPara.FractionI;
        B = 1;
        while (i--)
        {
            B *= 10;
        }
        B = B / 1000;
        MeasureFirmPara.KIArms = (u32)(100 * (float)tempis / ((float)tempib * B) + 0.5);
        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_KIArms, (u8 *)&MeasureFirmPara.KIArms, 4);

        i = MeasureFirmPara.FractionU;
        B = 1;
        while (i--)
        {
            B *= 10;
        }
        B = B / 100;
        MeasureFirmPara.KUrms = (u32)((float)tempus / (tempub * B) + 0.5);
        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_KUrms, (u8 *)&MeasureFirmPara.KUrms, 4);

        #if((RatedCurFlag == 0)||(RatedCurFlag == 1))
        MeasureFirmPara.Start_Ps = (u16)((tempis * 0.0007) / 16);
        MeasureFirmPara.Zxot = (u16)((tempis * 0.001) / 4096);
        #else
        MeasureFirmPara.Start_Ps = (u16)((tempis * 0.002) / 16);
        MeasureFirmPara.Zxot = (u16)((tempis * 0.003) / 4096);
        #endif
        MeasureFirmPara.Start_Q = MeasureFirmPara.Start_Ps;
        fnRN8302_Write(RN8302_IStart_PS, (u8 *)&MeasureFirmPara.Start_Ps, 2);
        fnRN8302_Write(RN8302_IStart_Q, (u8 *)&MeasureFirmPara.Start_Q, 2);
        fnRN8302_Write(RN8302_ZXOT, (u8 *)&MeasureFirmPara.Zxot, 2);
        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_Start_Ps, (u8 *)&MeasureFirmPara.Start_Ps, 2);
        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_Start_Q, (u8 *)&MeasureFirmPara.Start_Q, 2);

        // ����ϵ������
        MeasureFirmPara.KPrms = (u32)((float)tempus * (float)tempis / ((float)tempub * (float)tempib * 838.8608));
        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_KPrms, (u8 *)&MeasureFirmPara.KPrms, 4);

        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_PRth, (u8 *)&MeasureFirmPara.PRth[0], 8);
        fnRN8302_Write(RN8302_PRTH1L, (u8 *)&MeasureFirmPara.PRth[0], 2);
        fnRN8302_Write(RN8302_PRTH1H, (u8 *)&MeasureFirmPara.PRth[1], 2);
        fnRN8302_Write(RN8302_PRTH2L, (u8 *)&MeasureFirmPara.PRth[2], 2);
        fnRN8302_Write(RN8302_PRTH2H, (u8 *)&MeasureFirmPara.PRth[3], 2);
        MeasureRms.PriData.Flag &= ~MEASURE_FLAG_CorrectionUI;
    }
    else if (MeasureRms.PriData.Flag & MEASURE_FLAG_CorrectionPHS)
    {
        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealAngle, &TempBuf[0], 12);
        if ((TempBuf[0] == 0) && (TempBuf[1] == 0))     // �ԽǶȽ���У��
        {
            tempangle[0] = 0;

            for (i = 0; i < 2; i++)
            {
                fnRN8302_Read(RN8302_YUB + i, EmuCommbuf.ucTempBuf, 3) ;
                temppw[0] = EmuCommbuf.lTemp32 & 0x00ffffff;
                tempangle[i + 1] = (u16)(((float)temppw[0] / 16777216) * 36000);
            }
            for (i = 0; i < 3; i++)
            {
                Std_Memcpy(&tempangle[i + 3], &(TempBuf[6 + 2 * i]), 2);
                fnRN8302_Read(RN8302_YIA + i, EmuCommbuf.ucTempBuf, 3) ;
                temppw[0] = EmuCommbuf.lTemp32 & 0x00ffffff;
                ADErr = ((((float)temppw[0] / 16777216) * 36000 - (float)(tempangle[i + 3] + tempangle[i])) / 1.7578);
                if (MeasureFirmPara.PRth[0] == 0 && MeasureFirmPara.PRth[1] == 0 && MeasureFirmPara.PRth[2] == 0 && MeasureFirmPara.PRth[3] == 0)
                {
                    if (ADErr > 0)
                    {
                        tempis = 0x00808080 - (u8)ADErr;
                        Std_Memcpy((u8 *)&MeasureFirmPara.PHSI[i], &tempis, 0x03);
                    }
                    else
                    {
                        ADErr = -ADErr;
                        tempis = 0x00808080 + (u8)ADErr;
                        Std_Memcpy((u8 *)&MeasureFirmPara.PHSI[i], &tempis, 0x03);
                    }
                }
                else
                {
                    if (ADErr > 0)
                    {
                        tempis = 0;
                        Std_Memcpy(&tempis, (u8 *)&MeasureFirmPara.PHSI[i], 0x03);
                        tempis -= (((u32)((u8)ADErr) << 8) & 0x0000ff00);
                        Std_Memcpy((u8 *)&MeasureFirmPara.PHSI[i], &tempis, 0x03);
                    }
                    else
                    {
                        ADErr = -ADErr;
                        tempis = 0;
                        Std_Memcpy(&tempis, (u8 *)&MeasureFirmPara.PHSI[i], 0x03);
                        tempis += (((u32)((u8)ADErr) << 8) & 0x0000ff00);
                        Std_Memcpy((u8 *)&MeasureFirmPara.PHSI[i], &tempis, 0x03);
                    }
                }
                fnRN8302_Write(RN8302_PHSIA + i, (u8 *)&MeasureFirmPara.PHSI[i], 3);
            }
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_PHSI, (u8 *)&MeasureFirmPara.PHSI[0], 12);
        }
        else
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    fnRN8302_Read(RN8302_PA + j, (u8 *)&temppw[0], 4);
                    if (temppw[0] & 0x80000000)
                    {
                        temppw[0] = ~temppw[0] + 1;
                    }
                    tempUI[j] += temppw[0];
                }
                SystemDelay(250);

                fnWDT_Restart();
            }
            for (i = 0; i < 3; i++)
            {
                tempUI[i] = tempUI[i] / 3;
            }
            for (i = 0; i < 3; i++)
            {
                Std_Memcpy(&tempis, &(TempBuf[4 * i]), 4);
                ADErr = ((float)tempUI[i] - (float)tempis) / (float)tempis;
                ADErr = -ADErr / 1.732;
                if (ADErr > 0)
                {
                    tempub = ADErr * 32768 + 0.5;
                }
                else
                {
                    tempub = 65536 + ADErr * 32768 + 0.5;
                }
                if (MeasureFirmPara.PRth[0] == 0 && MeasureFirmPara.PRth[1] == 0 && MeasureFirmPara.PRth[2] == 0 && MeasureFirmPara.PRth[3] == 0)
                {
                    Std_Memcpy((u8 *)&MeasureFirmPara.P_PHS[i], &tempub, 0x02);
                    Std_Memcpy((u8 *)&MeasureFirmPara.Q_PHS[i], &tempub, 0x02);
                    fnRN8302_Write(RN8302_PA_PHSL + i, (u8 *)&MeasureFirmPara.P_PHS[i], 2);
                    fnRN8302_Write(RN8302_QA_PHSL + i, (u8 *)&MeasureFirmPara.Q_PHS[i], 2);
                }
                else
                {
                    MeasureFirmPara.P_PHSMH[i * 2] = 0;
                    MeasureFirmPara.Q_PHSMH[i * 2] = 0;
                    Std_Memcpy((u8 *)&MeasureFirmPara.P_PHSMH[i * 2], &tempub, 0x02);
                    Std_Memcpy((u8 *)&MeasureFirmPara.Q_PHSMH[i * 2], &tempub, 0x02);
                    fnRN8302_Write(RN8302_PA_PHSM + i * 2, (u8 *)&MeasureFirmPara.P_PHSMH[i * 2], 3);
                    fnRN8302_Write(RN8302_QA_PHSM + i * 2, (u8 *)&MeasureFirmPara.Q_PHSMH[i * 2], 3);
                }
            }
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_P_PHSMH, (u8 *)&MeasureFirmPara.P_PHSMH[0], 48);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_P_PHS, (u8 *)&MeasureFirmPara.P_PHS[0], 6);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_Q_PHS, (u8 *)&MeasureFirmPara.Q_PHS[0], 6);
        }
        MeasureRms.PriData.Flag &= ~MEASURE_FLAG_CorrectionPHS;
    }
    else if (MeasureRms.PriData.Flag & MEASURE_FLAG_CorrectionPHSL)
    {
        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealAngle, &TempBuf[0], 12);
        if ((TempBuf[0] == 0) && (TempBuf[1] == 0))     // �ԽǶȽ���У��
        {
            tempangle[0] = 0;
            for (i = 0; i < 2; i++)
            {
                fnRN8302_Read(RN8302_YUB + i, EmuCommbuf.ucTempBuf, 3) ;
                temppw[0] = EmuCommbuf.lTemp32 & 0x00ffffff;
                tempangle[i + 1] = (u16)(((float)temppw[0] / 16777216) * 36000);
            }
            for (i = 0; i < 3; i++)
            {
                Std_Memcpy(&tempangle[i + 3], &(TempBuf[6 + 2 * i]), 2);
                fnRN8302_Read(RN8302_YIA + i, EmuCommbuf.ucTempBuf, 3) ;
                temppw[0] = EmuCommbuf.lTemp32 & 0x00ffffff;
                ADErr = ((((float)temppw[0] / 16777216) * 36000 - (tempangle[i + 3] + tempangle[i])) / 1.7578);
                if (ADErr > 0)
                {
                    tempis = 0;
                    Std_Memcpy(&tempis, (u8 *)&MeasureFirmPara.PHSI[i], 0x03);
                    tempis = ((tempis & 0x00ffff00) | 0x000080) - (u8)ADErr;
                    Std_Memcpy((u8 *)&MeasureFirmPara.PHSI[i], &tempis, 0x03);
                    //Dl645FirmPara.PHSI[i] = ((Dl645FirmPara.PHSI[i]&0xffff00)|0x000080) - (u8)ADErr;
                }
                else
                {
                    ADErr = -ADErr;
                    tempis = 0;
                    Std_Memcpy(&tempis, (u8 *)&MeasureFirmPara.PHSI[i], 0x03);
                    tempis = ((tempis & 0x00ffff00) | 0x000080) + (u8)ADErr;
                    Std_Memcpy((u8 *)&MeasureFirmPara.PHSI[i], &tempis, 0x03);
                    //Dl645FirmPara.PHSI[i] = ((Dl645FirmPara.PHSI[i]&0xffff00)|0x000080) + (u8)ADErr;
                }
                fnRN8302_Write(RN8302_PHSIA + i, (u8 *)&MeasureFirmPara.PHSI[i], 3);
            }
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_PHSI, (u8 *)&MeasureFirmPara.PHSI[0], 12);
        }
        else
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    fnRN8302_Read(RN8302_PA + j, (u8 *)&temppw[0], 4);
                    if (temppw[0] & 0x80000000)
                    {
                        temppw[0] = ~temppw[0] + 1;
                    }
                    tempUI[j] += temppw[0];
                }
                SystemDelay(250);
                fnWDT_Restart();
            }
            for (i = 0; i < 3; i++)
            {
                tempUI[i] = tempUI[i] / 3;
            }
            for (i = 0; i < 3; i++)
            {
                Std_Memcpy(&tempis, &(TempBuf[4 * i]), 4);
                ADErr = ((float)tempUI[i] - (float)tempis) / (float)tempis;
                ADErr = -ADErr / 1.732;
                if (ADErr > 0)
                {
                    tempub = ADErr * 32768 + 0.5;
                }
                else
                {
                    tempub = 65536 + ADErr * 32768 + 0.5;
                }
                Std_Memcpy((u8 *)&MeasureFirmPara.P_PHS[i], &tempub, 0x02);
                Std_Memcpy((u8 *)&MeasureFirmPara.Q_PHS[i], &tempub, 0x02);
                fnRN8302_Write(RN8302_PA_PHSL + i, (u8 *)&MeasureFirmPara.P_PHS[i], 2);
                fnRN8302_Write(RN8302_QA_PHSL + i, (u8 *)&MeasureFirmPara.Q_PHS[i], 2);
            }
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_P_PHS, (u8 *)&MeasureFirmPara.P_PHS[0], 6);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_Q_PHS, (u8 *)&MeasureFirmPara.Q_PHS[0], 6);
        }
        MeasureRms.PriData.Flag &= ~MEASURE_FLAG_CorrectionPHSL;
    }
    else if (MeasureRms.PriData.Flag & MEASURE_FLAG_CorrectionPHSM)
    {
        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealAngle, &TempBuf[0], 12);
        if ((TempBuf[0] == 0) && (TempBuf[1] == 0))     // �ԽǶȽ���У��
        {
            tempangle[0] = 0;
            for (i = 0; i < 2; i++)
            {
                fnRN8302_Read(RN8302_YUB + i, EmuCommbuf.ucTempBuf, 3) ;
                temppw[0] = EmuCommbuf.lTemp32 & 0x00ffffff;
                tempangle[i + 1] = (u16)(((float)temppw[0] / 16777216) * 36000);
            }
            for (i = 0; i < 3; i++)
            {
                Std_Memcpy(&tempangle[i + 3], &(TempBuf[6 + 2 * i]), 2);
                fnRN8302_Read(RN8302_YIA + i, EmuCommbuf.ucTempBuf, 3) ;
                temppw[0] = EmuCommbuf.lTemp32 & 0x00ffffff;
                ADErr = ((((float)temppw[0] / 16777216) * 36000 - (tempangle[i + 3] + tempangle[i])) / 1.7578);
                if (ADErr > 0)
                {
                    tempis = 0;
                    Std_Memcpy(&tempis, (u8 *)&MeasureFirmPara.PHSI[i], 0x03);
                    tempis = ((tempis & 0x00ffff) | 0x800000) - (((u32)((u8)ADErr) * 65536) & 0x00ff0000);
                    Std_Memcpy((u8 *)&MeasureFirmPara.PHSI[i], &tempis, 0x03);
                }
                else
                {
                    ADErr = -ADErr;
                    tempis = 0;
                    Std_Memcpy(&tempis, (u8 *)&MeasureFirmPara.PHSI[i], 0x03);
                    tempis = ((tempis & 0x00ffff) | 0x800000) + (((u32)((u8)ADErr) * 65536) & 0x00ff0000);
                    Std_Memcpy((u8 *)&MeasureFirmPara.PHSI[i], &tempis, 0x03);
                }
                fnRN8302_Write(RN8302_PHSIA + i, (u8 *)&MeasureFirmPara.PHSI[i], 3);
            }
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_PHSI, (u8 *)&MeasureFirmPara.PHSI[0], 12);
        }
        else
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    fnRN8302_Read(RN8302_PA + j, (u8 *)&temppw[0], 4);
                    if (temppw[0] & 0x80000000)
                    {
                        temppw[0] = ~temppw[0] + 1;
                    }
                    tempUI[j] += temppw[0];
                }
                SystemDelay(250);
                fnWDT_Restart();
                SystemDelay(150);
            }
            for (i = 0; i < 3; i++)
            {
                tempUI[i] = tempUI[i] / 3;
            }
            for (i = 0; i < 3; i++)
            {
                Std_Memcpy(&tempis, &(TempBuf[4 * i]), 4);
                ADErr = ((float)tempUI[i] - (float)tempis) / (float)tempis;
                ADErr = -ADErr / 1.732;
                if (ADErr > 0)
                {
                    tempub = ADErr * 32768 + 0.5; //��������
                }
                else
                {
                    tempub = 65536 + ADErr * 32768 + 0.5;
                }
                MeasureFirmPara.P_PHSMH[i * 2 + 1] = 0;
                MeasureFirmPara.Q_PHSMH[i * 2 + 1] = 0;
                Std_Memcpy((u8 *)&MeasureFirmPara.P_PHSMH[i * 2 + 1], &tempub, 0x02);
                Std_Memcpy((u8 *)&MeasureFirmPara.Q_PHSMH[i * 2 + 1], &tempub, 0x02);
                fnRN8302_Write(RN8302_PA_PHSH + i * 2, (u8 *)&MeasureFirmPara.P_PHSMH[i * 2 + 1], 3);
                fnRN8302_Write(RN8302_QA_PHSH + i * 2, (u8 *)&MeasureFirmPara.Q_PHSMH[i * 2 + 1], 3);
            }
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_P_PHSMH, (u8 *)&MeasureFirmPara.P_PHSMH[0], 48);
        }
        MeasureRms.PriData.Flag &= ~MEASURE_FLAG_CorrectionPHSM;
    }
    // ���ߵ���У׼
    else if (MeasureRms.PriData.Flag & MEASURE_FLAG_CorrectionIn)
    {
        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RatedI, (u8 *)&tempib, 2);
        //      fnFile_Read(FileId_FirmPara,FileItemInfoOffAddr_FirmPara_RatedIrms, (u8 *)&tempis, 4);

        EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // дʹ��λ
        fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

        fnWDT_Restart();

        if (MeasureFirmPara.RealI[3] == 0)
        {
            MeasureFirmPara.GSI[3] = 0;
            fnRN8302_Write(RN8302_GSIN, (u8 *)&MeasureFirmPara.GSI[3], 2);
            fnDelayMs(250);
            fnWDT_Restart();
        }
        else
        {
            for (i = 0; i < 3; i++)
            {
                fnRN8302_Read(RN8302_IN, (u8 *)&temppw[1], 4);
                tempUI[0] += temppw[1];
                fnDelayMs(250);
                fnWDT_Restart();
            }
            tempUI[0] = tempUI[0] / 3;
            temppw[1] = (u32)((float)tempib * (float)MeasureFirmPara.KIArms / 10);

            ADErr = ((float)tempUI[0] - (float)temppw[1]) / (float)temppw[1];
            ADErr = ((-ADErr) / (1 + ADErr));
            if (ADErr > 0)
            {
                MeasureFirmPara.GSI[3] = (u16)(ADErr * 32768 + 0.5);
            }
            else
            {
                MeasureFirmPara.GSI[3] = (u16)(65536 + ADErr * 32768 + 0.5);
            }
            fnRN8302_Write(RN8302_GSIN, (u8 *)&MeasureFirmPara.GSI[3], 2);
        }

        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_GSI, (u8 *)&MeasureFirmPara.GSI[0], 8);

        MeasureRms.PriData.Flag &= ~MEASURE_FLAG_CorrectionIn;
    }
    // ����У���
    else if (MeasureRms.PriData.Flag & MEASURE_FLAG_CalcCheckSum)
    {
        SystemDelay(10);
        MeasureRms.PriData.Flag &= ~MEASURE_FLAG_CalcCheckSum;
    }
    else
    {
        return;
    }

    EmuCommbuf.ucTemp8 = 0xDC; // д����
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
    MeasureFirmPara.ChkSum1 = 0;
    fnWDT_Restart();
    fnDelayMs(300);
    fnWDT_Restart();
    fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureFirmPara.ChkSum1, 3) ;
    fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_ChkSum1, (u8 *)&MeasureFirmPara.ChkSum1, 3);

    fnCrc_Check(0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef) - 2, (u8 *)&MeasureFirmPara.Crc);
    fnFile_Write(FileId_FirmPara, 0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));
}

void fnMeasure_FirmParaCheck(void)
{
    Std_Memset(&MeasureFirmPara, 0, sizeof(sMeasureFirmPara_TypeDef));
    fnFile_Read(FileId_FirmPara, 0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));
    fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sMeasureRepairPara_TypeDef));

    if (fnCrc_Check(1, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef) - 2, (u8 *)&MeasureFirmPara.Crc))
    {
        //-----������ٶ�1��-------------
        fnFile_Read(FileId_FirmPara, 0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));
    }

    if (fnCrc_Check(1, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc))
    {
        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef));
        if (fnCrc_Check(1, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc))
        {
            Std_Memset((u8 *)&MeasureRepairPara, 0x00, sizeof(sMeasureRepairPara_TypeDef));

            Std_Memcpy((u8 *)&MeasureRepairPara, (u8 *)&RepairParaDefault, sizeof(sMeasureRepairPara_TypeDef));

            fnCrc_Check(0, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc);

            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sMeasureRepairPara_TypeDef));
        }
    }

    if ((MeasureRepairPara.Volt.EnOrDis != VOLREP_Enable) && (MeasureRepairPara.Volt.EnOrDis != VOLREP_Disable))
    {
        MeasureRepairPara.Volt.EnOrDis = VOLREP_Disable;
    }
}

void fnMeasure_Init(void)
{
    u8 i;
    u32 DeviceID = 0;
    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }

    fnRN8302Mode_Init(MeasureModeEMM);  //����IO������ģʽ
    #if (PCB_Version==RN8611_RN7306)
    fnRN8611_EnergyPulseIO_Init();
    fnRn8302_HSDCSPI_Init();
    fnBSP_ExModuleSpi_Init();
    #endif

    Std_Memset(&MeasureRegTmp, 0, sizeof(sMeasureRegTmp_TypeDef));      //��ʼ��RAM
    Std_Memset(&MeasureRms, 0, sizeof(sMeasureRms_TypeDef));        //��ʼ��RAM
    fnMeasure_FirmParaCheck();

    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_PConstE, &MeasureRms.PriPara.PConstE, 4);
    MeasureRms.PriPara.QConstE = MeasureRms.PriPara.PConstE;
    fnCrc_Check(0, (u8 *)&MeasureRms.PriPara, sizeof(MeasureRms.PriPara) - 2, (u8 *)&MeasureRms.PriPara.Crc);

    for (i = 0; i < 5; i++)
    {
        fnWDT_Restart();
        fnMeasure_EMUInit();

        fnHarmonic_Init();

        SystemDelay(10);
        MeasureRegTmp.ChkSum1 = 0;
        fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureRegTmp.ChkSum1, 3) ;
        if (MeasureRegTmp.ChkSum1 == MeasureFirmPara.ChkSum1)
        {
            break;
        }
    }

    fnWaveSpiOut_Init();

    DeviceID = 0;
    fnRN8302_Read(RN8302_DeviceID, (u8 *)&DeviceID, 3) ;

    // dyf ���Ӷ�ֱ��ż��г������ʹ�ܿ���
    fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Flag_EnOrDis, &parameter.xiebo_flag, 1);
    if ((parameter.xiebo_flag == 0x00) || (parameter.xiebo_flag == 0xFF))
    {
        parameter.xiebo_flag = 0x5A;    // ������ز�����Ч����Ĭ��Ϊ�ر�0x5A
    }
}

// ͣ��͹��Ķ�ȡ��ѹ��������
void fnMeasure_EvtVoltLoss(void)
{
    u8 i;

    fnRN8302Mode_Init(MeasureModeEMM);  //����IO������ģʽ

    Std_Memset(&MeasureRegTmp, 0, sizeof(sMeasureRegTmp_TypeDef));      //��ʼ��RAM
    Std_Memset(&MeasureRms, 0, sizeof(sMeasureRms_TypeDef));            //��ʼ��RAM
    fnMeasure_FirmParaCheck();

    for (i = 0; i < 5; i++)
    {
        fnWDT_Restart();
        fnMeasure_EvtVoltLossEMUInit();

        SystemDelay(10);
        MeasureRegTmp.ChkSum1 = 0;
        fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureRegTmp.ChkSum1, 3) ;
        if (MeasureRegTmp.ChkSum1 == MeasureFirmPara.ChkSum1)
        {
            break;
        }
    }

    SystemDelay(10);

    //����ѹ����
    for (i = 0; i < 3; i++)
    {
        MeasureRegTmp.Irms[i] = 0 ;
        fnRN8302_Read(RN8302_IA + i, (u8 *)&MeasureRegTmp.Irms[i], 4) ;
    }

    for (i = 0; i < 3; i++)
    {
        MeasureRegTmp.Urms[i] = 0 ;
        fnRN8302_Read(RN8302_UA + i, (u8 *)&MeasureRegTmp.Urms[i], 4) ;
    }

    //��ѹ��������
    for (i = 0; i < 3; i++)
    {
        MeasureRms.PubData.U[i] = (s32)(100 * (float)MeasureRegTmp.Urms[i] / (10 * (MeasureFirmPara.KUrms)) + 0.5); //��ѹ hex
    }

    for (i = 0; i < 3; i++)
    {
        MeasureRms.PubData.I[i] = (s32)(100 * (float)MeasureRegTmp.Irms[i] / (MeasureFirmPara.KIArms) + 0.5);
    }

    RN8302_PowerOff();

    ////����ģ�����
    Rn8xxx_GPIO_CfgFun(PinSCS_C, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinSCS_C, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinSCS_C, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinSCLK, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinSCLK, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinSCLK, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinSDO_C, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinSDO_C, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinSDO_C, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinSDI_C, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinSDI_C, GPIO_MODE_NORMAL, NORMAL_IN);
    //Rn8xxx_GPIO_CfgPullMode(PinSDI_C , Pull_OFF);
    Rn8xxx_GPIO_CfgPullMode(PinSDI_C, Pull_ON); // dyf ��Ҫ�ر��ڲ�Ĭ�ϵ��������裬�����µ���󹦺ıȽϸߣ�Pull_ON ��Ӧ�ر��������������������ò�ͬ
}

u32 fnMeasure_UnblCalculate(u8 WireMode, u32 UIa, u32 UIb, u32 UIc)
{
    u32 Max, Min;

    if (WireMode == 0)  //��������
    {
        if (UIa > UIb)
        {
            Max = UIa;
            Min = UIb;
        }
        else
        {
            Max = UIb;
            Min = UIa;
        }
        if (Max < UIc)
        {
            Max = UIc;
        }
        if (Min > UIc)
        {
            Min = UIc;
        }
    }
    else                //��������
    {
        if (UIa > UIc)
        {
            Max = UIa;
            Min = UIc;
        }
        else
        {
            Max = UIc;
            Min = UIa;
        }
    }
    return ((Max - Min) * 10000 / Max);
}

//-----г����ѹ��Чֵ����----------
void fnMeasureHURMS_Get(void)
{
    u8 i;

    for (i = 0; i < 3; i++)
    {
        MeasureRms.PubData.HUrms[i][0] = (s32)(1000 * (float)MeasureRegTmp.FUrms[i] / (10 * (MeasureFirmPara.KUrms)) + 0.5);
        if (MeasureRms.PubData.HUrms[i][0] < ClearUValue)
        {
            MeasureRms.PubData.HUrms[i][0] = 0;
        }
    }

    for (i = 1; i < 41; i++)
    {
        MeasureRms.PubData.HUrms[0][i] = (s32)(1000 * (float)HarmonicData.PubData.HarmonicUrms[0][i] / (10 * (MeasureFirmPara.KUrms)) + 0.5);
        MeasureRms.PubData.HUrms[1][i] = (s32)(1000 * (float)HarmonicData.PubData.HarmonicUrms[1][i] / (10 * (MeasureFirmPara.KUrms)) + 0.5);
        MeasureRms.PubData.HUrms[2][i] = (s32)(1000 * (float)HarmonicData.PubData.HarmonicUrms[2][i] / (10 * (MeasureFirmPara.KUrms)) + 0.5);
    }

    Bkgrd.PubData.FUrmsRdFlg |= 0x80;   // dyf add ������ȡ���������
}

//-----г��������Чֵ����----------
void fnMeasureHIARMS_Get(void)
{
    u8 i;

    for (i = 0; i < 3; i++)
    {
        MeasureRms.PubData.HIrms[i][0] = (s32)(100 * (float)MeasureRegTmp.FIrms[i] / (MeasureFirmPara.KIArms) + 0.5);
        if (MeasureRms.PubData.HIrms[i][0] < ClearIValue)
        {
            MeasureRms.PubData.HIrms[i][0] = 0;
        }
    }

    for (i = 1; i < 41; i++)
    {
        MeasureRms.PubData.HIrms[0][i] = (s32)(100 * (float)HarmonicData.PubData.HarmonicIrms[0][i] / (MeasureFirmPara.KIArms) + 0.5);
        MeasureRms.PubData.HIrms[1][i] = (s32)(100 * (float)HarmonicData.PubData.HarmonicIrms[1][i] / (MeasureFirmPara.KIArms) + 0.5);
        MeasureRms.PubData.HIrms[2][i] = (s32)(100 * (float)HarmonicData.PubData.HarmonicIrms[2][i] / (MeasureFirmPara.KIArms) + 0.5);
    }
}

//-----г��������Чֵ����----------
void fnMeasureHPRMS_Get(void)
{
    u8 i;

    // г���ܹ���
    MeasureRms.PubData.HPtw = (float)HarmonicData.PubData.PtHarmonicPw[0] / (MeasureFirmPara.KPrms) * 1000;
    MeasureRms.PubData.HNtw = (float)(abs(HarmonicData.PubData.NtHarmonicPw[0])) / (MeasureFirmPara.KPrms) * 1000;

    // ��������
    for (i = 0; i < 3; i++)
    {
        MeasureRegTmp.FPw[i] = 0 ;
        fnRN8302_Read(RN8302_FPA + i, (u8 *)&MeasureRegTmp.FPw[i], 4);

        MeasureRms.PubData.HPrms[i][0] = (float)MeasureRegTmp.FPw[i] / (MeasureFirmPara.KPrms) * 1000;
        if (abs(MeasureRms.PubData.HPrms[i][0]) < ClearPwValue)
        {
            MeasureRms.PubData.HPrms[i][0] = 0;
        }
        if (MeasureRms.PubData.HPrms[i][0] < 0)
        {
            MeasureRms.PubData.HIrms[i][0] = -MeasureRms.PubData.HIrms[i][0];
        }
    }

    for (i = 1; i < 41; i++)
    {
        MeasureRms.PubData.HPrms[0][i] = (float)HarmonicData.PubData.HarmonicPw[0][i] / (MeasureFirmPara.KPrms) * 1000;
        if (abs(MeasureRms.PubData.HPrms[0][i]) < ClearPwValue)
        {
            MeasureRms.PubData.HPrms[0][i] = 0;
        }
        if (MeasureRms.PubData.HPrms[0][i] < 0)
        {
            MeasureRms.PubData.HIrms[0][i] = -MeasureRms.PubData.HIrms[0][i];
        }

        MeasureRms.PubData.HPrms[1][i] = (float)HarmonicData.PubData.HarmonicPw[1][i] / (MeasureFirmPara.KPrms) * 1000;
        if (abs(MeasureRms.PubData.HPrms[1][i]) < ClearPwValue)
        {
            MeasureRms.PubData.HPrms[1][i] = 0;
        }
        if (MeasureRms.PubData.HPrms[1][i] < 0)
        {
            MeasureRms.PubData.HIrms[1][i] = -MeasureRms.PubData.HIrms[1][i];
        }

        MeasureRms.PubData.HPrms[2][i] = (float)HarmonicData.PubData.HarmonicPw[2][i] / (MeasureFirmPara.KPrms) * 1000;
        if (abs(MeasureRms.PubData.HPrms[2][i]) < ClearPwValue)
        {
            MeasureRms.PubData.HPrms[2][i] = 0;
        }
        if (MeasureRms.PubData.HPrms[2][i] < 0)
        {
            MeasureRms.PubData.HIrms[2][i] = -MeasureRms.PubData.HIrms[2][i];
        }
    }
}

/*********************************************************************************************************
** Function name:   fnMeasure_Exec
** Descriptions:      ����������
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnMeasure_Exec(void)
{
    u8  i, j;
    u16 TempAngle1, TempAngle2;
    s32 Tempw, Tempq, Tempws;
    u32 DeviceID = 0;
    //float ftmp = 0;

    if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON) || (Inactive.PubData.InactiveStamp))
    {
        return;
    }

    if (fnStamp_Through(MeasureRms.PriData.MeasureStamp) < 1000)
    {
        return;
    }

    fnWDT_Restart();
    MeasureRms.PriData.MeasureStamp = SysStamp;

    fnRN8302_CorrectionMeter();

    check_rn7306_reg();     // dyf �ж�ֱ��ż��г���������غͲ������·�����

    if (MeasureRms.PriData.Flag & MEASURE_FLAG_RST)
    {
        fnWDT_Restart();
        fnMeasure_EMUInit();
        MeasureRms.PriData.Flag &= ~MEASURE_FLAG_RST;

        //      fnWaveSpiOutToExModule(NULL, 0);
    }

    if (fnMeasure_VoltRepair_Exe() == FALSE)  // ��ѹӰ����״̬�ж�
    {
        //---------У����ж�------------------------
        MeasureRegTmp.ChkSum1 = 0;
        fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureRegTmp.ChkSum1, 3) ;

        // dyf �����ж�ֱ��ż��г��������������µ�У����Ƿ�һ��
        if ((MeasureRegTmp.ChkSum1 == MeasureFirmPara.ChkSum1) || ((parameter.xiebo_flag != 0x5A) && (check_rn7306_checksum(MeasureRegTmp.ChkSum1))))
        {
            MeasureRegTmp.ChkErrCnt = 0;
            MeasureRms.PriData.Flag &= ~MEASURE_FLAG_RST;
        }
        else
        {
            MeasureRegTmp.ChkSum1 = 0;
            fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureRegTmp.ChkSum1, 3) ;
            // ����ֱ��ż��г�����������
            if (((parameter.xiebo_flag == 0x5A) && (MeasureRegTmp.ChkSum1 != MeasureFirmPara.ChkSum1))
                || ((parameter.xiebo_flag != 0x5A) && (!check_rn7306_checksum(MeasureRegTmp.ChkSum1))))
            {
                MeasureRegTmp.ChkErrCnt++;
                if (MeasureRegTmp.ChkErrCnt >= 5)
                {
                    MeasureRms.PriData.Flag |= MEASURE_FLAG_RST;  // dyf �������κ����
                    MeasureRegTmp.ChkErrCnt = 0;
                }
            }
        }
    }

    fnWDT_Restart();

    fnRN8302_Read(RN8302_DeviceID, (u8 *)&DeviceID, 3) ;
    if (DeviceID != 0x830200)
    {
        MeasureRms.PriData.Flag |= MEASURE_FLAG_Err;
    }
    else
    {
        MeasureRms.PriData.Flag &= ~MEASURE_FLAG_Err;
    }

    //����ѹ����
    for (i = 0; i < 4; i++)
    {
        MeasureRegTmp.Irms[i] = 0 ;
        fnRN8302_Read(RN8302_IA + i, (u8 *)&MeasureRegTmp.Irms[i], 4) ;
    }

    fnRN8302_Read(RN8302_ISUM, (u8 *)&MeasureRegTmp.VectorI[2], 4) ;

    for (i = 0; i < 3; i++)
    {
        MeasureRegTmp.Urms[i] = 0 ;
        fnRN8302_Read(RN8302_UA + i, (u8 *)&MeasureRegTmp.Urms[i], 4) ;
    }

    //fnMeasureWSAVE();

    //������
    for (i = 0; i < 12; i++)
    {
        MeasureRegTmp.Pw[i] = 0 ;
        fnRN8302_Read(RN8302_PA + i, (u8 *)&MeasureRegTmp.Pw[i], 4);
    }

    //��Ƶ��
    fnRN8302_Read(RN8302_UFreq, (u8 *)&MeasureRegTmp.Frequency, 3);

    //��Ǳ��������־λ
    fnRN8302_Read(RN8302_Noload, (u8 *)&MeasureRegTmp.PQNoLoad, 2);

    //�����ʷ���
    fnRN8302_Read(RN8302_PQSign, (u8 *)&MeasureRegTmp.PDirect, 2);

    //����ѹ�����Ƕ�ֵ
    for (i = 0; i < 5; i++)
    {
        MeasureRegTmp.Angle[i] = 0 ;
        fnRN8302_Read(RN8302_YUB + i, (u8 *)&MeasureRegTmp.Angle[i], 3);
    }
    if (Bkgrd.PriPara.WireMode == 0x01)
    {
        MeasureRegTmp.Angle[0] = 0;
        MeasureRegTmp.Angle[3] = 0;
    }

    // ����������
    for (i = 0; i < 3; i++)
    {
        MeasureRegTmp.Pf[i + 1] = 0 ;
        fnRN8302_Read(RN8302_PfA + i, (u8 *)&MeasureRegTmp.Pf[i + 1], 3);
    }
    MeasureRegTmp.Pf[0] = 0 ;
    fnRN8302_Read(RN8302_PfTV, (u8 *)&MeasureRegTmp.Pf[0], 3);

    //���ʼ���
    for (j = 0; j < 3; j++)
    {
        for (i = 0; i < 3; i++)
        {
            MeasureRms.PubData.Pw[j * 4 + i + 1] = (s32)(1000 * (float)(MeasureRegTmp.Pw[j * 4 + i]) / (((s32)MeasureFirmPara.KPrms))); //�����Pa Pb Pc������Qa Qb Qc������Sa Sb Sc��
        }
    }
    for (i = 0; i < 3; i++)
    {
        MeasureRms.PubData.Pw[i * 4] = (s32)(1000 * (float)(MeasureRegTmp.Pw[i * 4 + 3]) / (((s32)MeasureFirmPara.KPrms))); //����P��Q��S
    }

    for (i = 0; i < 3; i++)
    {
        //S^2 =P^2+Q^2
        MeasureRms.PubData.Pw[9 + i] = sqrt((s64)(MeasureRms.PubData.Pw[1 + i]) * (MeasureRms.PubData.Pw[1 + i]) + (s64)(MeasureRms.PubData.Pw[5 + i]) *
                                            (MeasureRms.PubData.Pw[5 + i])); //�����Pa Pb Pc������Qa Qb Qc������Sa Sb Sc��
    }

    //��ѹ��������
    for (i = 0; i < 3; i++)
    {
        MeasureRms.PubData.U[i] = (s32)(100 * (float)MeasureRegTmp.Urms[i] / (10 * (MeasureFirmPara.KUrms)) + 0.5); //��ѹ hex
    }

    for (i = 0; i < 3; i++)
    {
        MeasureRms.PubData.I[i] = (s32)(100 * (float)MeasureRegTmp.Irms[i] / (MeasureFirmPara.KIArms) + 0.5);
    }

    MeasureRms.PubData.In = (s32)(100 * (float)MeasureRegTmp.Irms[3] / (MeasureFirmPara.KIArms) + 0.5);

    MeasureRms.PubData.VectorI[2] = (s32)(100 * (float)(MeasureRegTmp.VectorI[2] / (MeasureFirmPara.KIArms))) * 4;

    //Ƶ�ʼ���
    if ((MeasureRegTmp.Frequency > 1638400) || (MeasureRegTmp.Frequency < 1092266)) //when 50HZ is 5120 ;+- 20% frequence is 6144 and 4096
    {
        MeasureRegTmp.Frequency = 1310720;
    }
    MeasureRms.PubData.Frequency = (u16)(65536000 / (MeasureRegTmp.Frequency / 100));

    //������������
    //�ܹ�������
    //MeasureRms.PubData.Pf[0]=fnDFConver_Bcd16To16((s16)((1000*(double)(Dl645FrontTmp.Pw[0]/((MeasureFirmPara.PRmsConst))+Dl645FrontTmp.Pw[1]/((MeasureFirmPara.PRmsConst))+Dl645FrontTmp.Pw[2]/((MeasureFirmPara.PRmsConst))))/(Dl645FrontTmp.Pw[6]/((MeasureFirmPara.PRmsConst))+Dl645FrontTmp.Pw[7]/((MeasureFirmPara.PRmsConst))+Dl645FrontTmp.Pw[8]/((MeasureFirmPara.PRmsConst)))));
    if (Bkgrd.PriPara.WireMode == 0x01)
    {
        Tempw = (s32)((MeasureRegTmp.Pw[3]) / ((MeasureFirmPara.KPrms))) ;
        Tempq = (s32)((MeasureRegTmp.Pw[7]) / ((MeasureFirmPara.KPrms))) ;
        // ���������ڹ���
        Tempws = (s32)sqrt((float)Tempw * (float)Tempw + (float)Tempq * (float)Tempq);
        MeasureRms.PubData.Pw[8] = Tempws / 100;

        //������������
        //�ܹ�������
        MeasureRms.PubData.Pf[0] = (s16)((1000 * (double)(Tempw)) / (Tempws));
        if (abs(MeasureRms.PubData.Pf[0]) > 1000)
        {
            MeasureRms.PubData.Pf[0] = 1000;
        }
    }
    else
    {
        if (MeasureRegTmp.Pf[0] & 0x00800000)
        {
            MeasureRegTmp.Pf[0] = 0xffffff - MeasureRegTmp.Pf[0] + 1  ;
            MeasureRms.PubData.Pf[0] = (s16)((float)MeasureRegTmp.Pf[0] / 8388.608 + 0.5); //��������
            MeasureRms.PubData.Pf[0] = 0xffff - MeasureRms.PubData.Pf[0] + 1;
        }
        else
        {
            MeasureRms.PubData.Pf[0] = (s16)((float)MeasureRegTmp.Pf[0] / 8388.608 + 0.5);
        }

        if (abs(MeasureRms.PubData.Pf[0]) > 1000)
        {
            MeasureRms.PubData.Pf[0] = 1000;
        }
    }
    //ABC���๦������
    for (i = 0; i < 3; i++)
    {
        if ((i == 1) && (Bkgrd.PriPara.WireMode))
        {
            MeasureRms.PubData.Pf[2] = 0;
        }
        else
        {
            if (MeasureRegTmp.Pf[i + 1] & 0x00800000)
            {
                MeasureRegTmp.Pf[i + 1] = 0xffffff - MeasureRegTmp.Pf[i + 1] + 1  ;
                MeasureRms.PubData.Pf[i + 1] = (s16)((float)MeasureRegTmp.Pf[i + 1] / 8388.608 + 0.5); //��������
                MeasureRms.PubData.Pf[i + 1] = 0xffff - MeasureRms.PubData.Pf[i + 1] + 1;
            }
            else
            {
                MeasureRms.PubData.Pf[i + 1] = (s16)((float)MeasureRegTmp.Pf[i + 1] / 8388.608 + 0.5);    //��������
            }

            if (abs(MeasureRms.PubData.Pf[i + 1]) > 1000)
            {
                MeasureRms.PubData.Pf[i + 1] = 1000;
            }
        }
    }

    // ��Ǽ���
    for (i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            MeasureRms.PubData.Angle[i] = 0;  //A
        }
        else
        {
            if (MeasureRms.PubData.U[i] > AngleCalc_Volt)
            {
                MeasureRms.PubData.Angle[i] = (u16)(((float)MeasureRegTmp.Angle[i - 1] / 16777216) * 3600);
            }
            else
            {
                MeasureRms.PubData.Angle[i] = 0;
            }
        }
        TempAngle2 = (u16)(((float)MeasureRegTmp.Angle[i + 2] / 16777216) * 3600);
        if (TempAngle2 < MeasureRms.PubData.Angle[i])
        {
            TempAngle2 = TempAngle2 + 3600;
        }

        if (MeasureRms.PubData.I[i] > AngleCalc_Cur)
        {
            MeasureRms.PubData.Angle[i + 3] = TempAngle2 - MeasureRms.PubData.Angle[i]; //��ѹ��������
            MeasureRms.PubData.Angle[i + 6] = TempAngle2; //ABC�������A���ѹ�Ƕ�
        }
        else
        {
            MeasureRms.PubData.Angle[i + 3] = 0; //��ѹ��������
            MeasureRms.PubData.Angle[i + 6] = 0; //ABC�������A���ѹ�Ƕ�
        }
    }
    TempAngle2 = (u16)(((float)MeasureRegTmp.Angle[4] / 16777216) * 3600);
    TempAngle1 = (u16)(((float)MeasureRegTmp.Angle[2] / 16777216) * 3600) ;
    if (TempAngle1 > TempAngle2)
    {
        MeasureRms.PubData.Angle[9] = 3600 - (TempAngle1 - TempAngle2);
    }
    else
    {
        MeasureRms.PubData.Angle[9] = TempAngle2 - TempAngle1;
    }
    //--------�Ϸ����ж�--------------
    //--------ABC----------
    for (i = 0; i < 3; i++)
    {
        if (MeasureRms.PubData.Pw[i + 1] < 0)
        {
            MeasureRms.PubData.I[i] = -MeasureRms.PubData.I[i];
        }
        //--------�����ж�----------------
        if (abs(MeasureRms.PubData.I[i]) < ClearIValue)
        {
            MeasureRms.PubData.I[i] = 0x00;
        }

        //--------��ѹ�ж�-----------------
        if (MeasureRms.PubData.U[i] < ClearUValue)
        {
            MeasureRms.PubData.U[i] = 0x00;
        }

        //----------�����ж�--------------------
        if ((abs(MeasureRms.PubData.I[i]) < ClearIValue) || (MeasureRms.PubData.U[i] < ClearUValue)
            || (abs(MeasureRms.PubData.Pw[i + 9]) < ClearPwValue)) //����
        {
            Std_Memset((u8 *)&MeasureRms.PubData.Pw[i + 1], 0x00, 4);
            Std_Memset((u8 *)&MeasureRms.PubData.Pw[i + 5], 0x00, 4);
            Std_Memset((u8 *)&MeasureRms.PubData.Pw[i + 9], 0x00, 4);
            MeasureRms.PubData.Pf[i + 1] = 1000;
            MeasureRegTmp.PDirect &= ~(0x01 << i);
            MeasureRegTmp.PDirect &= ~(0x01 << (i + 4));
        }
        else
        {
            //------�й��ж�---------------------
            if (MeasureRegTmp.PQNoLoad & (1 << i)) //�й������ڴ���Ǳ��״̬
            {
                MeasureRms.PubData.Pw[i + 1] = 0x00;
                MeasureRms.PubData.Pw[i + 9] = 0x00;
                MeasureRms.PubData.Pf[i + 1] = 1000;
                MeasureRegTmp.PDirect &= ~(0x01 << i);
            }
            else if (abs(MeasureRms.PubData.Pw[i + 1]) < ClearPwValue) //�й�
            {
                MeasureRms.PubData.Pw[i + 1] = 0x00;
                MeasureRms.PubData.Pf[i + 1] = 0;
                MeasureRegTmp.PDirect &= ~(0x01 << i);
            }
            //-------�޹��ж�-----------------------------
            if (MeasureRegTmp.PQNoLoad & (1 << (i + 4))) //�޹�����Ǳ��״̬
            {
                MeasureRms.PubData.Pw[i + 5] = 0x00;
                MeasureRms.PubData.Pf[i + 1] = 1000;
                MeasureRegTmp.PDirect &= ~(0x01 << (i + 4));
            }
            else if (abs(MeasureRms.PubData.Pw[i + 5]) < ClearPwValue) //�޹�
            {
                MeasureRms.PubData.Pw[i + 5] = 0x00;
                MeasureRms.PubData.Pf[i + 1] = 1000;
                MeasureRegTmp.PDirect &= ~(0x01 << (i + 4));
            }
        }
    }
    //------���ߵ����ж�-------------
    if (abs(MeasureRms.PubData.In) < ClearIValue)
    {
        MeasureRms.PubData.In = 0x00;
    }

    //---------��--------------
    if (((abs(MeasureRms.PubData.I[0]) < ClearIValue) && (abs(MeasureRms.PubData.I[1]) < ClearIValue) && (abs(MeasureRms.PubData.I[2]) < ClearIValue)) ||
        ((MeasureRms.PubData.U[0] == 0) && (MeasureRms.PubData.U[1] == 0) && (MeasureRms.PubData.U[2] == 0)) ||
        (abs(MeasureRms.PubData.Pw[8]) < ClearPwValue))   //������
    {
        Std_Memset((u8 *)&MeasureRms.PubData.Pw[0], 0x00, 4);
        Std_Memset((u8 *)&MeasureRms.PubData.Pw[4], 0x00, 4);
        Std_Memset((u8 *)&MeasureRms.PubData.Pw[8], 0x00, 4);
        MeasureRms.PubData.Pf[0] = 1000;
        MeasureRegTmp.PDirect &= ~(0x01 << 3);
        MeasureRegTmp.PDirect &= ~(0x01 << 7);
    }
    else
    {
        if ((MeasureRegTmp.PQNoLoad & 0x07) == 0x07) //�����й������ڶ�����Ǳ��״̬
        {
            MeasureRms.PubData.Pw[0] = 0x00;
            MeasureRms.PubData.Pw[8] = 0x00;
            MeasureRms.PubData.Pf[0] = 1000;
            MeasureRegTmp.PDirect &= ~(0x01 << 3);
        }
        else if (abs(MeasureRms.PubData.Pw[0]) < nPhs * ClearPwValue)   //�й���
        {
            MeasureRms.PubData.Pw[0] = 0x00;
            MeasureRms.PubData.Pf[0] = 0;
            MeasureRegTmp.PDirect &= ~(0x01 << 3);
        }

        //-------�޹��ж�-----------------------------
        if ((MeasureRegTmp.PQNoLoad & 0x70) == 0x70) //�޹�����Ǳ��״̬
        {
            MeasureRms.PubData.Pw[4] = 0x00;
            MeasureRms.PubData.Pf[0] = 1000;
            MeasureRegTmp.PDirect &= ~(0x01 << 7);
        }
        else if (abs(MeasureRms.PubData.Pw[4]) < ClearPwValue)  //�޹���
        {
            MeasureRms.PubData.Pw[4] = 0x00;
            MeasureRms.PubData.Pf[0] = 1000;
            MeasureRegTmp.PDirect &= ~(0x01 << 7);
        }
    }

    // dyf add ���ڹ��ʷ��ŵ����й����ʷ���
    for (i = 0; i < 4; i++)
    {
        if (MeasureRms.PubData.Pw[i] < 0)
        {
            MeasureRms.PubData.Pw[8 + i] = 0 - MeasureRms.PubData.Pw[8 + i];
        }
    }

    // dyf add �������ط��ŵ����й����ʷ���
    for (i = 0; i < 4; i++)
    {
        if (MeasureRms.PubData.Pw[i] < 0)
        {
            MeasureRms.PubData.Pf[i] = 0 - abs(MeasureRms.PubData.Pf[i]);
        }
    }

    //ͬ�����ݿ鹦�ʼ��� dyf ���Ƶ���
    for (i = 0; i < 12; i++)
    {
        SynVarOtherUnitData.Pw[i] = MeasureRms.PubData.Pw[i] / 10;
    }

    //ͬ�����ݿ鹦�����ؼ��� dyf ���Ƶ��ˣ��ڹ��������쳣����Ĭ�ϴ�������ṩ��˫оSPIͬ������ֹֻ�ӵ�ѹ�����ӵ���ʱ������������
    for (i = 0; i < 4; i++)
    {
        SynVarOtherUnitData.Pf[i] = MeasureRms.PubData.Pf[i] * 10;
    }

    //ת�����ʷ���
    MeasureRms.PubData.PDirect = ((MeasureRegTmp.PDirect << 1) & 0xee) | ((MeasureRegTmp.PDirect >> 3) & 0x11);

    //    //��ѹ������ƽ���ʼ���
    //    //-------------��1������ٽ��ѹʱ���㲻ƽ����----------------
    //      if( (MeasureRms.PubData.U[0] > FLOWV_VOL60Un)
    //      ||(MeasureRms.PubData.U[1] > FLOWV_VOL60Un)
    //      || (MeasureRms.PubData.U[2] > FLOWV_VOL60Un))
    //      {
    //      MeasureRms.PubData.UnblU = fnMeasure_UnblCalculate(Bkgrd.PriPara.WireMode ,
    //                                                 (MeasureRms.PubData.U[0]) ,
    //                                                 (MeasureRms.PubData.U[1]) ,
    //                                                 (MeasureRms.PubData.U[2]) );
    //      }
    //  else
    //      MeasureRms.PubData.UnblU = 0x0000;
    //
    //  //------��1���������5%Ibʱ���������ƽ����---------------------------
    //  if((abs(MeasureRms.PubData.I[0] ) > FLOWV_CUR5Ib)
    //      ||(abs(MeasureRms.PubData.I[1] ) > FLOWV_CUR5Ib)
    //      || (abs(MeasureRms.PubData.I[2] ) > FLOWV_CUR5Ib))
    //  {
    //          MeasureRms.PubData.UnblI = fnMeasure_UnblCalculate(Bkgrd.PriPara.WireMode ,
    //                                                 abs(MeasureRms.PubData.I[0]) ,
    //                                                 abs(MeasureRms.PubData.I[1]) ,
    //                                                 abs(MeasureRms.PubData.I[2]) );
    //
    //  }
    //  else
    //  {
    //      MeasureRms.PubData.UnblI = 0x0000;
    //  }

    //��RN8302�����ļ�Ϊ������//{P,Q,Ps},{Pa,Qa,Psa},{Pb,Qb,Psb},{Pc,Qc,Psc}{Fp,Fq}{Fpa,Fqa}{Fpb,Fqb}{Fpc,Fqc}
    /*�����ܼĴ���*/
    for (i = 0; i < 3; i++)
    {
        MeasureRegTmp.Pulse[(i + 1) * 3] = 0;
        fnRN8302_Read(RN8302_EPA + i, (u8 *)&MeasureRegTmp.Pulse[(i + 1) * 3], 3); //�й�
        MeasureRegTmp.Pulse[(i + 1) * 3 + 1] = 0;
        fnRN8302_Read(RN8302_EQA + i, (u8 *)&MeasureRegTmp.Pulse[(i + 1) * 3 + 1], 3); //�޹�
        MeasureRegTmp.Pulse[(i + 1) * 3 + 2] = 0;
        fnRN8302_Read(RN8302_ESA + i, (u8 *)&MeasureRegTmp.Pulse[(i + 1) * 3 + 2], 3); //�����й�
        MeasureRegTmp.Pulse[14 + i * 2] = 0;
        fnRN8302_Read(RN8302_FEPA + i, (u8 *)&MeasureRegTmp.Pulse[14 + i * 2], 3); //�����й�
        MeasureRegTmp.Pulse[15 + i * 2] = 0;
        fnRN8302_Read(RN8302_FEQA + i, (u8 *)&MeasureRegTmp.Pulse[15 + i * 2], 3); //�����й�
    }
    MeasureRegTmp.Pulse[0] = 0;
    fnRN8302_Read(RN8302_EPT, (u8 *)&MeasureRegTmp.Pulse[0], 3);        //���й�
    MeasureRegTmp.Pulse[1] = 0;
    fnRN8302_Read(RN8302_EQT, (u8 *)&MeasureRegTmp.Pulse[1], 3);        //���޹�
    MeasureRegTmp.Pulse[2] = 0;
    fnRN8302_Read(RN8302_ESTA, (u8 *)&MeasureRegTmp.Pulse[2], 3);       //������
    MeasureRegTmp.Pulse[12] = 0;
    fnRN8302_Read(RN8302_PosFEPT, (u8 *)&MeasureRegTmp.Pulse[12], 3);    //���������й�
    MeasureRegTmp.Pulse[13] = 0;
    fnRN8302_Read(RN8302_NegFEPT, (u8 *)&MeasureRegTmp.Pulse[13], 3);    //���������й�

    for (i = 0; i < 20; i++) //���ܸ�Ƶ����ת���ɵ�Ƶ����
    {
        MeasureRegTmp.Pulse_Eg[i] += MeasureRegTmp.Pulse[i];
    }
    //    for(i=0;i<12;i++)//��Ƶ����ת���ɵ�Ƶ����
    //  {
    //      MeasureRegTmp.Pulse_Need[i]+=MeasureRegTmp.Pulse[i];
    //    }

    fnMeasureHURMS_Get();
    fnMeasureHIARMS_Get();
    fnMeasureHPRMS_Get();
}

#if(HarmonicFun_EnORDis == HarmonicFun_Enable)
void fnMeasure_WaveInit(void)
{
}

//--------------�رղ��λ��湦��----------------
void fnMeasure_WaveColse(void)
{
}

/*********************************************************************************************************
** Function name:       fnMeasure_TxHarmonicPack
** Descriptions:        �������ݷ��ͣ�г�����ݴ�����256���г�ȡ64����г������
** input parameters:    NONE
** output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void fnMeasure_TxHarmonicPack(void)
{
}

/*****************************************************************************
** Function name:fnHarmonic_WaveData
**
** Description:RN8209�����жϣ������ȡ���λ����ȡ,DMA��ʽ
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnMeasure_DMAReadWaveData(void)
{
}

/*****************************************************************************
** Function name:fnMeasure_WaveData
**
** Description: 1������RN8209���λ��棬ȫ���жϣ��Խ������ݽ��кϷ����жϣ���װ����ѹ��������
**              2����һ�ܲ����ݺ�����������ղ�ֵ
**              3������ֵ���������������һ��SPI��������ģ����е�����������
**              4������ʣ��Ĳ��ε��������Ⲩ�β�����
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnMeasure_WaveData(void)
{
}

#endif

//*********************************************************************************
// �������� fnMeasureAverage_PowerCalc
// ���룺
// ���أ�   NONE
// ������   �����й����޹���1����ƽ������
// ע�ͣ�
//*********************************************************************************
void fnMeasureAverage_PowerCalc(void)
{
    u8 i;

    for (i = 0; i < 4; i++)
    {
        MeasureRegTmp.Ppwave[i] += MeasureRms.PubData.Pw[i];
        MeasureRegTmp.Pqwave[i] += MeasureRms.PubData.Pw[4 + i];
    }
    MeasureRegTmp.Pwave_sec++;

    //if(MeasureRegTmp.Pwave_sec > 59)
    if (SysDatetimes.second == 0)
    {
        if (MeasureRegTmp.PCalcFlg != 0x5A)
        {
            for (i = 0; i < 4; i++)
            {
                MeasureRegTmp.Ppwave[i] = 0;
                MeasureRegTmp.Pqwave[i] = 0;
            }
            MeasureRegTmp.PCalcFlg = 0x5A;
            MeasureRegTmp.Pwave_sec = 0;
            return;
        }
        for (i = 0; i < 4; i++)
        {
            MeasureRms.PubData.PPwave[i] = MeasureRegTmp.Ppwave[i] / MeasureRegTmp.Pwave_sec;
            MeasureRms.PubData.Pqwave[i] = MeasureRegTmp.Pqwave[i] / MeasureRegTmp.Pwave_sec;
            MeasureRegTmp.Ppwave[i] = 0;
            MeasureRegTmp.Pqwave[i] = 0;
        }
        MeasureRegTmp.Pwave_sec = 0;
        for (i = 0; i < 4; i++)
        {
            SynVarOtherUnitData.AvgPw[i] = MeasureRms.PubData.PPwave[i] / 10;
            SynVarOtherUnitData.AvgPw[i + 4] = MeasureRms.PubData.Pqwave[i] / 10;
        }
    }
}
