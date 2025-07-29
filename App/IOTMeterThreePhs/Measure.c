
#include <Includes.h>
#include "ProDefine.h"

//--------计量参数默认配置---------------------------------
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

    0x393,          //电压系数
    0x00001787,     //电流系数
    0x0223,         //功率系数

    22000,          //RatedU
    19461570,       //RatedUrms
    10000,          //RatedI
    6827797,        //RatedIrms
    {220000, 220000, 220000},   //RealU
    {100000, 100000, 100000, 100000}, //RealI
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //RealAngle
    {0x0000, 0x0000, 0x0000},   //RealPw
    128     //波形输出点数
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

    0x375,          //电压系数
    0x00014E09,     //电流系数 0x00001787
    0x2339,         //功率系数

    22000,          //RatedU
    0x0128F5C2,     //RatedUrms
    1500,           //RatedI
    0x00C3B962,     //RatedIrms
    {220000, 220000, 220000},   //RealU
    {15000, 15000, 15000, 15000}, //RealI
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //RealAngle
    {0x0000, 0x0000, 0x0000},   //RealPw
    128     //波形输出点数
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

    0x385,          //电压系数
    0x00014DC1,     //电流系数
    0x23DC,         //功率系数

    5770,           //RatedU
    0x004F5C28,     //RatedUrms
    1500,           //RatedI
    0x00C38F44,     //RatedIrms
    {57700, 57700, 57700},      //RealU
    {15000, 15000, 15000, 15000}, //RealI
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //RealAngle
    {0x0000, 0x0000, 0x0000},   //RealPw
    128     //波形输出点数
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

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTempBuf[0] = 0xAA;
    EmuCommbuf.ucTempBuf[1] = RN8302_WREN_EN;   // WREN2寄存器使能
    EmuCommbuf.ucTempBuf[2] = 0;
    EmuCommbuf.ucTempBuf[3] = 0;
    fnRN8302_Write(RN8302_WREN2, EmuCommbuf.ucTempBuf, 4);

    fnRN8302_Read(RN8302_SYSCFG, EmuCommbuf.ucTempBuf, 4);
    EmuCommbuf.lTemp32 |= (0xEA000000 | 0x1000);
    fnRN8302_Write(RN8302_SYSCFG, EmuCommbuf.ucTempBuf, 4);

    //复位MMU波形缓存DMA
    EmuCommbuf.ucTempBuf[0] = 0xE1;
    fnRN8302_Write(RN8302_SOFTRST, EmuCommbuf.ucTempBuf, 1);
    //复位HSDC
    EmuCommbuf.ucTempBuf[0] = 0x4C;
    fnRN8302_Write(RN8302_SOFTRST, EmuCommbuf.ucTempBuf, 1);

    //      /*"Step3:配置HSDC的SPI  模式  "*/
    //      EmuCommbuf.lTemp32 = 0x04;
    //      fnRN8302_Write(RN8306_HDSC_CTRL,EmuCommbuf.ucTempBuf,4);

    /*"Step4:配置波形格式和EMMDMA模式  "*/
    /*"UA UB UC IA IB IC  固定256 "*/
    EmuCommbuf.ucTempBuf[0] = 0x80;//0x00;
    fnRN8302_Write(RN8302_WSAVECON, EmuCommbuf.ucTempBuf, 1);
    EmuCommbuf.lTemp32 = 0;//0x13F0;
    EmuCommbuf.ucTempBuf[0] = 0x04;
    fnRN8302_Write(RN8302_DMA_WAVECON, EmuCommbuf.ucTempBuf, 4);
    EmuCommbuf.lTemp32 = 0xC00;     // 交叉缓存
    fnRN8302_Write(RN8306_DMA_WAVECON3, EmuCommbuf.ucTempBuf, 4);

    /*"Step5:开启HSDC的SPI    "*/
    EmuCommbuf.ucTempBuf[0] = 0x0D; // 配置HSDC 带校验  4.096Mhz
    EmuCommbuf.ucTempBuf[1] = 0x04;         // 按字节反序---先发低字节  累加校验和
    EmuCommbuf.ucTempBuf[2] = 0;
    EmuCommbuf.ucTempBuf[3] = 0;
    fnRN8302_Write(RN8306_HDSC_CTRL, EmuCommbuf.ucTempBuf, 4);

    /*"Step6:开启EMMDMA模式    "*/
    EmuCommbuf.lTemp32 = 0xC00 | 0x01; //0x01; // 交叉缓存
    fnRN8302_Write(RN8306_DMA_WAVECON3, EmuCommbuf.ucTempBuf, 4);

    EmuCommbuf.ucTempBuf[0] = 0x00;
    EmuCommbuf.ucTempBuf[1] = 0x07;   //EmuCommbuf.ucTempBuf[1] = 0x05;
    EmuCommbuf.ucTempBuf[2] = 0;
    EmuCommbuf.ucTempBuf[3] = 0;
    fnRN8302_Write(RN8302_DMA_WAVECON2, EmuCommbuf.ucTempBuf, 4);

    // 半波有效值使用开根号之后的
    EmuCommbuf.ucTempBuf[0] = 0x05;     // 全波过零  开根号后值
    EmuCommbuf.ucTempBuf[1] = 0x00;
    EmuCommbuf.ucTempBuf[2] = 0;
    EmuCommbuf.ucTempBuf[3] = 0;
    fnRN8302_Write(RN8302_EMUCFG2, EmuCommbuf.ucTempBuf, 4);

    //      // 使能半波有效值2计算
    //      EmuCommbuf.ucTempBuf[0] = 0x01;
    //      EmuCommbuf.ucTempBuf[1] = 0x00;
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8302_EMUCFG3,EmuCommbuf.ucTempBuf,4);
    //      // 半波有效值2配置
    //      EmuCommbuf.ucTempBuf[0] = 0x7F;
    //      EmuCommbuf.ucTempBuf[1] = 0x00;
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8302_HWCNT,EmuCommbuf.ucTempBuf,4);
    //
    //      // 使能半波有效值2更新---INT1中断
    //      EmuCommbuf.ucTempBuf[0] = 0x00;
    //      EmuCommbuf.ucTempBuf[1] = 0x00;
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0x01;
    //      fnRN8302_Write(RN8302_EMMIE2,EmuCommbuf.ucTempBuf,4);

    // 电压增益初始化x
    /*
    EmuCommbuf.ucTempBuf[0] = 0x00;
    EmuCommbuf.ucTempBuf[1] = 0x00;
    EmuCommbuf.ucTempBuf[2] = 0;
    EmuCommbuf.ucTempBuf[3] = 0;
    fnRN8302_Write(RN8302_GSUA_WAVE, EmuCommbuf.ucTempBuf,2);
    fnRN8302_Write(RN8302_GSUB_WAVE, EmuCommbuf.ucTempBuf,2);
    fnRN8302_Write(RN8302_GSUC_WAVE, EmuCommbuf.ucTempBuf,2);

    // 电流增益初始化
    fnRN8302_Write(RN8302_GSIA_WAVE, EmuCommbuf.ucTempBuf,2);
    fnRN8302_Write(RN8302_GSIB_WAVE, EmuCommbuf.ucTempBuf,2);
    fnRN8302_Write(RN8302_GSIC_WAVE, EmuCommbuf.ucTempBuf,2);
    fnRN8302_Write(RN8302_GSIN_WAVE, EmuCommbuf.ucTempBuf,2);*/

    //      fnRN8302_Write(RN8302_GSUA_WAVE,(u8 *)&MeasureFirmPara.GSU[0],2);
    //      fnRN8302_Write(RN8302_GSUB_WAVE,(u8 *)&MeasureFirmPara.GSU[1],2);
    //      fnRN8302_Write(RN8302_GSUC_WAVE,(u8 *)&MeasureFirmPara.GSU[2],2);
    //
    //      // 电流增益初始化
    //      fnRN8302_Write(RN8302_GSIA_WAVE,(u8 *)&MeasureFirmPara.GSI[0],2);
    //      fnRN8302_Write(RN8302_GSIB_WAVE,(u8 *)&MeasureFirmPara.GSI[1],2);
    //      fnRN8302_Write(RN8302_GSIC_WAVE,(u8 *)&MeasureFirmPara.GSI[2],2);
    //      fnRN8302_Write(RN8302_GSIN_WAVE,(u8 *)&MeasureFirmPara.GSI[3],2);

    //      EmuCommbuf.ucTemp8 = 0x10; // 清空采样数据缓存区
    //      fnRN8302_Write(RN8302_WSAVECON,EmuCommbuf.ucTempBuf,1);
    //
    //      EmuCommbuf.ucTempBuf[0] = 0;
    //      EmuCommbuf.ucTempBuf[1] = 0x9A;   // 打开HSDC
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0xEA;
    //      fnRN8302_Write(RN8302_SYSCFG,EmuCommbuf.ucTempBuf,4);
    //
    //      fnRN8302_Read(RN8302_SYSCFG,EmuCommbuf.ucTempBuf,4);
    //
    //      EmuCommbuf.ucTempBuf[0] = 0;    // 关闭波形缓存
    //      EmuCommbuf.ucTempBuf[1] = 0;
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8306_DMA_WAVECON3,EmuCommbuf.ucTempBuf,4);
    //
    //      //复位MMU波形缓存DMA
    //      EmuCommbuf.ucTempBuf[0] = 0xE1;
    //      fnRN8302_Write(RN8302_SOFTRST,EmuCommbuf.ucTempBuf,1);
    //      //复位HSDC
    //      EmuCommbuf.ucTempBuf[0] = 0x4C;
    //      fnRN8302_Write(RN8302_SOFTRST,EmuCommbuf.ucTempBuf,1);
    //      //写DMA_WAVECON寄存器---128点
    ///*        EmuCommbuf.ucTempBuf[0] = 0x00;
    //      EmuCommbuf.ucTempBuf[1] = 0;
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8302_DMA_WAVECON,EmuCommbuf.ucTempBuf,4);  */

    //      EmuCommbuf.ucTempBuf[0] = 0xF4;
    //      EmuCommbuf.ucTempBuf[1] = 0x09;   //256点同步采样，固定wavecnt
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8302_DMA_WAVECON,EmuCommbuf.ucTempBuf,4);

    ///*
    //      EmuCommbuf.ucTempBuf[0] = 0x90;
    //      EmuCommbuf.ucTempBuf[1] = 0x14;   //128点同步采样，固定cnt
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8302_DMA_WAVECON,EmuCommbuf.ucTempBuf,4);
    //*/

    ///*        EmuCommbuf.ucTempBuf[0] = 0x01; //8K采样
    //      EmuCommbuf.ucTempBuf[1] = 0x00;
    //      EmuCommbuf.ucTempBuf[2] = 0;
    //      EmuCommbuf.ucTempBuf[3] = 0;
    //      fnRN8302_Write(RN8302_DMA_WAVECON,EmuCommbuf.ucTempBuf,4);*/
    //
    //      //写WSAVECON寄存器
    //      EmuCommbuf.ucTemp8 = 0x01;//0xAC;//0xA0;//0xA2; // 0x01
    //      fnRN8302_Write(RN8302_WSAVECON,EmuCommbuf.ucTempBuf,1);
    ////        //写EMMIE2寄存器
    ////        EmuCommbuf.ucTempBuf[0] = 0;    //
    ////        EmuCommbuf.ucTempBuf[1] = 0x0A;
    ////        EmuCommbuf.ucTempBuf[2] = 0x10;
    ////        EmuCommbuf.ucTempBuf[3] = 0;
    ////        fnRN8302_Write(RN8302_EMMIE,EmuCommbuf.ucTempBuf,4);
    ////        //写EMMIF2寄存器
    ////        EmuCommbuf.ucTempBuf[0] = 0;    //
    ////        EmuCommbuf.ucTempBuf[1] = 0x0A;
    ////        EmuCommbuf.ucTempBuf[2] = 0x00;
    ////        EmuCommbuf.ucTempBuf[3] = 0;
    ////        fnRN8302_Write(RN8302_EMMIF,EmuCommbuf.ucTempBuf,4);
    //
    //      EmuCommbuf.ucTempBuf[0] = 0x1D; // 配置HSDC 带校验
    //      #ifdef EnCrc
    //      EmuCommbuf.ucTempBuf[0] = 0x1D; // 配置HSDC
    //      #endif
    //      EmuCommbuf.ucTempBuf[1] = 0x04;         // 按字节反序---先发低字节  累加校验和
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
    //      EmuCommbuf.ucTemp8 = ((EmuCommbuf.ucTemp8 & 0xCF)|0x20); //启动波形缓存
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
** Description:     RN8611对RN8302的PF、QF脉冲脚输入检测、转发，以及谐波电能脉冲输出管脚
**
** Parameters:      NONE
**
** Returned value:  NONE
**
******************************************************************************/
#if (PCB_Version==RN8611_RN7306)
void fnRN8611_EnergyPulseIO_Init(void)
{
    Rn8xxx_GPIO_CfgFun(PinRN8302_PF, _INTRUPT); /*"RN8302有功电能脉冲输入脚"*/
    Rn8xxx_INTC_Init(INTC_ID6, INTC_RisingEdge, INTC_IRQ_ENABLE);
    Rn8xxx_GPIO_CfgFun(PinRN8302_QF, _INTRUPT); /*"RN8302无功电能脉冲输入脚"*/
    Rn8xxx_INTC_Init(INTC_ID7, INTC_RisingEdge, INTC_IRQ_ENABLE);
    Rn8xxx_GPIO_CfgFun(Pin_PF, _SF1); /*"有功电能脉冲输出脚"*/
    Rn8xxx_GPIO_CfgFun(Pin_QF, _SF2); /*"无功电能脉冲输出脚"*/
    Rn8xxx_GPIO_CfgFun(Pin_PtHPF, _CF0); /*"正向谐波电能脉冲输出脚"*/
    Rn8xxx_GPIO_CfgFun(Pin_NtHPF, _CF1); /*"反向谐波电能脉冲输出脚"*/
    GPIO->IOCNT_CTL |= (0x1 << 1) | (0x1 << 2); /*使能P50/P51的IOCNT功能*/
    GPIO->P50_CFG |= 0x80000000;
    GPIO->P51_CFG |= 0x80000000;
}

/*****************************************************************************
** Function name:   fnRn8302_HSPI_Init(void)
**
** Description:     Rn8302  ADC波形缓存专用HSDC接口IO初始化
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
    // 采集半波电流值开始
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
    // 采集半波电流值开始
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

            //修正异常节点
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
        // 搬运数据---谐波处理
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

        // 搬运数据WaveSpiOut
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

            // 添加帧头 序号
            memcpy(&sWaveSpiOut.WaveSpiOut[0 + DltaLen], &sWaveSpiOut.Head, iHeadLen);

            // 计算整帧校验和
            sWaveSpiOut.nSum += sWaveSpiOut.Ctrl;
            sWaveSpiOut.nSum += (sWaveSpiOut.fLen & 0x00FF);
            sWaveSpiOut.nSum += ((sWaveSpiOut.fLen >> 8) & 0x00FF);
            sWaveSpiOut.nSum += sWaveSpiOut.fSeq;
            memcpy(&sWaveSpiOut.WaveSpiOut[sWaveSpiOut.nTLen - 5 + DltaLen], &sWaveSpiOut.nSum, 4);

            sWaveSpiOut.WaveSpiOut[sWaveSpiOut.nTLen - 1 + DltaLen] = sWaveSpiOut.fEnd;

            // 启动SPI-DMA发送
            fnWaveSpiOutToExModule(&sWaveSpiOut.WaveSpiOut[0 + DltaLen], sWaveSpiOut.nTLen);

            // 帧序号累加  清零校验和
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
    spi_DmaPara.RLen = RXDMA_nPoint * RXDMA_nChan * 3 + 4; //累加和
    //  spi_DmaPara.RLen = RXDMA_nPoint*RXDMA_nChan*3;      //不带CRC
    //spi_DmaPara.RLen = RXDMA_nPoint*RXDMA_nChan*3 + 2;//带CRC
    spi_DmaPara.DmaIE = SPI_DMA_RX_FIE; //接收全满中断
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

    //Rn8xxx_GPIO_CfgFun(PinINTN1_C,_INTRUPT);  //计量芯片中断输入,平时为高，中断产生时为低
    //Rn8xxx_INTC_Init(INTC_ID4,INTC_FallingEdge,INTC_IRQ_ENABLE);

    spi_para.gSPICtl = SPICTL_DEFAULT;
    spi_para.SPICtl_EN = SPICTL_EN;
    spi_para.SPICtl_MAST_SLAV = SPICTL_SLAV;
    spi_para.SPICtl_LMSB = SPICTL_MSB;
    spi_para.SPICtl_CPOL = (SPICtl_Mode_01 >> 1);
    spi_para.SPICtl_CPHA = (SPICtl_Mode_01 & 0x01);
    spi_para.SPICtl_WIDTH = SPICTL_WIDTH_8BIT;
    spi_para.SPICtl_SCSN_POS_IRQ_EN = 1;    //开启从机片选上升沿中断使能
    spi_para.SPICtl_SCSN_NEG_IRQ_EN = 0;    //开启从机片选下降沿中断使能
    spi_para.SPICtl_SLV_TX_ADV = 1;         //0为低速模式，时钟最高速率可达fcpu/8；1为高速模式，从机最高速率可达fcpu/4
    //这里设置的速率会影响从机接收的速率吗？？
    Rn8xxx_Spi_Init(SPI0_ID, spi_para, 4000000);  //SpiClk

    //  (u16)(&sEmuAdcRecvBuf.Data[0][0][0]);
    //  spi_DmaPara.DmaCtl.SPI_DMACtl_TX_DMA_EN = 0;
    //  spi_DmaPara.DmaCtl.SPI_DMACtl_RX_DMA_EN = 1;
    //  spi_DmaPara.DmaCtl.SPI_DMACtl_TX_CYC_MODE = 0;
    //  spi_DmaPara.DmaCtl.SPI_DMACtl_RX_CYC_MODE = 1;
    //  spi_DmaPara.RLen = RXDMA_nPoint*RXDMA_nChan*3 + 4;  //累加和
    ////    spi_DmaPara.RLen = RXDMA_nPoint*RXDMA_nChan*3;      //不带CRC
    //  //spi_DmaPara.RLen = RXDMA_nPoint*RXDMA_nChan*3 + 2;//带CRC
    //  spi_DmaPara.DmaIE = SPI_DMA_RX_HIE|SPI_DMA_RX_FIE;  //发送全满中断
    //  Rn8xxx_Spi_DMAInit(SPI0_ID , spi_DmaPara);
    NVIC_EnableIRQ(SPI_IRQn);
}

/*********************************************************************************************************
** Function name:         fnBSP_ExModuleSpi_Init
** Descriptions:          外部扩展模组spi通讯IO初始化
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
    spi_DmaPara.DmaIE = SPI_DMA_TX_FIE; //发送全满中断
    Rn8xxx_Spi_DMAInit(SPI2_ID, spi_DmaPara);

    NVIC_EnableIRQ(ISO78161_SPI2_IRQn);
}

#endif

//--------电压影响量补偿默认配置-----------------
const sMeasureRepairPara_TypeDef RepairParaDefault _reserve =
{
    {
        VOL_REPAIR,
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //A相1~8补偿点
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //B相1~8补偿点
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },    //C相1~8补偿点
        0x00
    },
    0x1018,     //RN8302_TIRM  V30--0x1830   V32--0x1018
    //  {0x4138 , 0x4138 , 0x4138},  //RN8207D_TIRM
};

//-------电压影响量补偿点--------------------
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
** Description:电压影响量补偿校正程序
**
** Parameters:
** nphase:  A相=0x00；B相=0x01；C相=0x02
**
** step:     0x55:自动根据电压、电流、功率因数识别补偿点,其他值为手动选择补偿点
**
** DataCommErr:    通讯下发补偿点计量误差,放大100000倍,  如台体显示误差 0.142%,值为：DataCommErr=142(0x8E).
**
**   特殊值:0x5A5A5A5A = 电压影响量初始化;0x11223344=打开电压影响量补偿
**                    0x44332211 = 关闭电压影响量补偿;0x00000000=补偿值清零
**
** Returned value:FALSE 设置失败；TRUE 设置成功
**
******************************************************************************/
u8 fnMeasure_VoltRepairCorrect(u8 nphase, u8 step, u32 DataCommErr)
{
    sDataComm_TypeDef      EmuCommbuf;
    float ADErr;
    u8 j, res = FALSE, temp08;
    u32  temp_I ;
    u16  temp_Pf ;

    if (DataCommErr == 0x5A5A5A5A) //电压影响量初始化
    {
        Std_Memset((u8 *)&MeasureRepairPara, 0x00, sizeof(sMeasureRepairPara_TypeDef));

        MeasureRepairPara.Volt.EnOrDis = VOLREP_Enable; //打开电压影响量补偿

        fnCrc_Check(0, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc);

        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef));

        res = TRUE;
    }
    else if (DataCommErr == 0x11223344)
    {
        MeasureRepairPara.Volt.EnOrDis = VOLREP_Enable; //打开电压影响量补偿
        fnCrc_Check(0, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc);

        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef));

        res = TRUE;
    }
    else if (DataCommErr == 0x44332211)
    {
        MeasureRepairPara.Volt.EnOrDis = VOLREP_Disable;  //关闭电压影响量补偿
        fnCrc_Check(0, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc);

        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef));

        res = TRUE;
    }
    else if (DataCommErr == 0x55667788) //补偿值清零
    {
        Std_Memset((u8 *)&MeasureRepairPara, 0x00, sizeof(sMeasureRepairPara_TypeDef));
        MeasureRepairPara.Volt.EnOrDis = VOLREP_Disable;  //关闭电压影响量补偿
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

        step -= 1;  //通讯下发step 从1开始

        if (DataCommErr > 0x7fffffff)
        {
            ADErr = -(float)(0xffffffff - DataCommErr + 1) / 100000;
        }
        else
        {
            ADErr = (float)DataCommErr / 100000;
        }
        ADErr = ((-ADErr) / (1 + ADErr));

        EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
        fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

        if (ADErr == 0)
        {
            EmuCommbuf.wTemp16 = 0;
            MeasureRepairPara.Volt.Rep[nphase][step] = 0;
        }
        else if (ADErr > 0)
        {
            EmuCommbuf.wTemp16 = ADErr * 32768 + 0.5;    //四舍五入
        }
        else
        {
            EmuCommbuf.wTemp16 = (u16)(65536 + ADErr * 32768 + 0.5);    //四舍五入
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

        EmuCommbuf.ucTemp8 = RN8302_WREN_DIS; // 写保护
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
** Description:通讯读取电压影响量补偿参数
**
** Parameters:获取数据
**
** Returned value:数据长度
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
** Descriptions:       电压影响量补偿,国网打高分用
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
                EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
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

                res = TRUE;  //处于电压影响量补偿状态，此时不判校验和

                break;
            }

            if (j == RE_ARRAY_LENGTH(Tab_VoltRepair)) //不在电压补偿点，立即恢复
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
** Description:     RN8302C或RN8306 RSIOM寄存器设置,通过RSIOM方式修改RN8207D寄存器
**
** Parameters: DevNo:从机设备号(0~3),0代表广播地址;
**           Reg    :从机寄存器地址(0~2)  00:BGR_TRIM; 01:CFG_PWD; 02:DLL_MUX
**           Data: 发送至从机的配置数据
** Returned value:  ERROR:操作失败；SUCCESS:操作成功
**
******************************************************************************/
u8 fnRN830x_RSIOM(u8 DevNo, u8 Reg, u32 Data)
{
    sDataComm_TypeDef      EmuCommbuf;
    RSIOM_MODE_TypeDef    rsiom_mode;
    RSIOM_CMD_TypeDef   rsiom_cmd;
    u32 status ;
    u8 i, result = SUCCESS;

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    fnRN8302_Read(RN8302_WREN2, &EmuCommbuf.ucTempBuf[0], 4); //先读取扩位命令是否有效
    if (EmuCommbuf.ucTempBuf[0]) //写入0xAA时表示扩位有效，读出为0x01
    {
        EmuCommbuf.ucTempBuf[0] = 0xAA;
    }
    else
    {
        EmuCommbuf.ucTempBuf[0] = 0x55;    //写入0x55时表示扩位无效，读出为0x00
    }

    EmuCommbuf.ucTempBuf[1] = RN8302_WREN_EN; // 写使能位2
    EmuCommbuf.ucTempBuf[2] = 0x00;
    EmuCommbuf.ucTempBuf[3] = 0x00;
    fnRN8302_Write(RN8302_WREN2, EmuCommbuf.ucTempBuf, 4); //RN8302_WREN2:bit0~bit7表示扩位命令;   bit8~bit15表示写使能;bit16~bit31 保留

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
        rsiom_cmd.DATA = 0x5ea3; //01寄存器写入0x5E3A,BGR_TRIM写使能
        Std_Memcpy((u8 *)&EmuCommbuf.ucTempBuf[0], (u8 *)&rsiom_cmd, 4);
        fnRN8302_Write(RN830x_RSIOM_CMD, EmuCommbuf.ucTempBuf, 4);

        SystemDelay(1);
        fnRN8302_Read(RN830x_RSIOM_STATUS, (u8 *)&status, 4) ;

        for (i = 0; i < 50; i++)
        {
            SystemDelay(1);
            fnRN8302_Read(RN830x_RSIOM_STATUS, (u8 *)&status, 4) ;
            if (status & (1 << 8)) //bit8 是否为1，响应判断
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
        else   //广播模式
        {
            if ((!(status & (1 << 1))) || (!(status & (1 << 2))) || (!(status & (1 << 3)))) //bit1~bit3 有一个响应错误，则退出
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
        if (Reg == 0) //TRIM寄存器需特殊处理
        {
            rsiom_cmd.DATA = Data & 0x7F; //取低7bit
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
            if (status & (1 << 8)) //bit8 是否为1，响应判断
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
        else   //广播模式
        {
            if ((!(status & (1 << 1))) || (!(status & (1 << 2))) || (!(status & (1 << 3)))) //bit1~bit3 有一个响应错误，则退出
            {
                result = ERROR;
            }
        }
    }
    SystemDelay(8); //必须等待电平时间8ms后才能发送退出rsiom命令，否则有可能无法退出rsiom模式

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
        if (status & (1 << 8)) //bit8 是否为1，响应判断
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
    else   //广播模式
    {
        if ((!(status & (1 << 1))) || (!(status & (1 << 2))) || (!(status & (1 << 3)))) //bit1~bit3 有一个响应错误，则退出
        {
            result = ERROR;
        }
    }

    EmuCommbuf.ucTemp8 = RN8302_WREN_DIS; //
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    fnRN8302_Read(RN8302_WREN2, &EmuCommbuf.ucTempBuf[0], 4); //先读取扩位命令是否有效
    if (EmuCommbuf.ucTempBuf[0]) //扩位命令有效
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
** Description: 修改8302 TIRM值
**
** Parameters:  tirm    :待设置的tirm值
**
** Returned value:  SUCCESS:设置成功; ERROR:设置失败
**
******************************************************************************/
u8 fnRN8302_TIRM(u32  tirm)
{
    sDataComm_TypeDef      EmuCommbuf;
    u32 status;
    u8  result;

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTemp8 = 0xE5; //
    fnRN8302_Write(RN830x_ADCIN_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTemp8 = 0x5A; //
    fnRN8302_Write(RN830x_BGR_HT, EmuCommbuf.ucTempBuf, 1);

    fnRN8302_Read(RN830x_OTPTRIM_STA, (u8 *)&status, 4);

    if (status & 0x01) //OTPTRIM_STA.otptrim_in使能时，RN830x_OTPDBG寄存器可配置
    {
        fnRN8302_Read(RN830x_OTPTRIM, EmuCommbuf.ucTempBuf, 3);

        //-进入调试模式：0x02 0xBA 0x7F 0x5C
        //-必须顺序且连续写这4个BYTE数据，并且中间不能插入任何其他读写动作，这样才可以进入调试模式。
        //-在调试模式下，才可以对OTP进行读写操作
        //--fnRN8302_Write-写RN830x_OTPDBG寄存器时，不能通过读0x018D寄存器进行效验，否则会导致无法进入调试模式-

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
** Description:通讯设置8302 tirm值
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
** Description:通讯读取8302 tirm值
**
** Parameters:获取数据
**
** Returned value:数据长度
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
** Description:通讯设置8207D tirm值
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
    //  result = fnRN830x_RSIOM( nphase , 0x00 , MeasureRepairPara.RN8207D_TIRM[nphase]);   //Vref=1.243V,data数值定义与SPI通讯时一致

    //  if(result == ERROR)
    //  {
    //      SystemDelay(10);  //出错后延时10ms后再操作一遍
    //      result = fnRN830x_RSIOM( nphase , 0x00 , MeasureRepairPara.RN8207D_TIRM[nphase]);
    //  }
}

/*****************************************************************************
** Function name:fnMeasure_RN8207DTIRM_ComRead
**
** Description:通讯读取8207D tirm值
**
** Parameters:获取数据
**
** Returned value:数据长度
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
** Description: RN8302C复位清零，RN8207电源关闭，
**                   避免上电1bit流不稳定错出脉冲
** Parameters:      NONE
**
** Returned value:  NONE
**
******************************************************************************/
#if( (RN8302C_Ver == RN8302C)||(RN8302C_Ver == RN8302C_V3) )
void fnRN8302C_Rest(void)
{
    Rn8xxx_GPIO_CfgFun(PinMS_RST, _NORMALIO); /*"RN8302复位控制"*/
    Rn8xxx_GPIO_CfgIOMode(PinMS_RST, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinMS_RST, 0);

    RN8207_PowerOff();

    RN8302_PowerOff();

    SystemDelay(10);

    RN8207_PowerOn();
    RN8302_PowerOn();

    SystemDelay(20);

    Rn8xxx_GPIO_CfgFun(PinMS_RST, _NORMALIO); //"硬件复位"//
    Rn8xxx_GPIO_CfgIOMode(PinMS_RST, GPIO_MODE_OUT, NORMAL_OUT);
    Rn8xxx_GPIO_SetPin(PinMS_RST, 1);

    SystemDelay(10);
}
#endif

/*****************************************************************************
** Function name:   fnRN8302_Stop(void)
**
** Description:     关闭计量
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
    //    Rn8xxx_GPIO_CfgFun(PinMS_RST,_NORMALIO);/*"RN8302复位控制"*/
    //  Rn8xxx_GPIO_CfgIOMode( PinMS_RST , GPIO_MODE_OUT , NORMAL_OUT ); /*""*/
    //    Rn8xxx_GPIO_SetPin( PinMS_RST , 0);//zhupdebug
    Rn8xxx_GPIO_CfgFun(PinMS_RST, _NORMALIO);
    Rn8xxx_GPIO_CfgIOMode(PinMS_RST, GPIO_MODE_NORMAL, NORMAL_IN);

    #endif

    /*"停止计量先将通讯IO口配置为输入不使能防止漏电"*/
    Rn8xxx_GPIO_CfgFun(PinSCS_C, _NORMALIO); /*"RN8302通讯SPI 的CS脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinSCS_C, GPIO_MODE_NORMAL, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinSCLK, _NORMALIO); /*"RN8302通讯SPI 的CLK脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinSCLK, GPIO_MODE_NORMAL, NORMAL_IN);

    Rn8xxx_GPIO_CfgFun(PinSDI_C, _NORMALIO); /*"RN8302通讯SPI 的MOSI脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinSDI_C, GPIO_MODE_NORMAL, NORMAL_IN);
    Rn8xxx_GPIO_CfgPullMode(PinSDI_C, Pull_ON); // dyf 需要关闭内部默认的上拉电阻，否则导致掉电后功耗比较高；Pull_ON 对应关闭上拉，与其他引脚设置不同

    Rn8xxx_GPIO_CfgPullMode(PinSDO_C, Pull_OFF);
    Rn8xxx_GPIO_CfgFun(PinSDO_C, _NORMALIO); /*"RN8302通讯SPI 的MISO脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinSDO_C, GPIO_MODE_NORMAL, NORMAL_IN);

    // RN8207_PowerOff();
    // RN8302_PowerOff();

    Rn8xxx_GPIO_CfgFun(PinRN8302_Power, _NORMALIO); /*"RN8302通讯SPI 的MISO脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinRN8302_Power, GPIO_MODE_NORMAL, NORMAL_IN);

    #if( (RN8302C_Ver == RN8302C)||(RN8302C_Ver == RN8302C_V3) )
    Rn8xxx_GPIO_CfgFun(PinRN8207_Power, _NORMALIO); /*"RN8302通讯SPI 的MISO脚"*/
    Rn8xxx_GPIO_CfgIOMode(PinRN8207_Power, GPIO_MODE_NORMAL, NORMAL_IN);
    #endif
}

/*****************************************************************************
** Function name:   fnRN8302Mode_Init(eMeasureMode_TypeDef MeasureMode)
**
** Description: RN8302模式初始化:计量模式，全失压模式选择
**
** Parameters:      NONE
**
** Returned value:  NONE
**
******************************************************************************/
void fnRN8302Mode_Init(eMeasureMode_TypeDef MeasureMode)
{
    sDataComm_TypeDef      EmuCommbuf;

    //-------函数注册-----------
    fnRN8302_ApiRegister(Rn8302_SpiCS, Rn8302Spi_ReadByte, Rn8302Spi_WriteByte, (void (*)(uint32_t))SystemDelayUs);

    Std_Memset(&MeasureRegTmp, 0, sizeof(sMeasureRegTmp_TypeDef));
    Std_Memset(&MeasureRms, 0, sizeof(sMeasureRms_TypeDef));

    #if( (RN8302C_Ver == RN8302C)||(RN8302C_Ver == RN8302C_V3) )
    fnRN8302C_Rest();
    #else
    RN8302_PowerOn();
    #endif

    Rn8302_Spi_Init();   //SPI初始化

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    //----RN8302C需配置使用内部或外部ADC----------------------
    #if(RN8302C_Ver == RN8302C_V3)
    //"配置电压计量，电流1bit流模式"//
    EmuCommbuf.ucTemp8 = 0XEA; //
    fnRN8302_Write(0x01A1, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.wTemp16 = 0; //
    fnRN8302_Read(0x01A0, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.wTemp16 |= BIT7; // In选择ADC内置,零线不用8207D
    EmuCommbuf.wTemp16 |= BIT12; //U通道1bit来源内置ADC
    EmuCommbuf.wTemp16 |= BIT13; // ADIN_CKO引脚输出2.048MHz时钟

    fnRN8302_Write(0x01A0, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.lTemp32 = 0; //
    fnRN8302_Read(0x01A0, EmuCommbuf.ucTempBuf, 2);

    #elif (RN8302C_Ver == RN8302C)
    //"配置电压计量，电流1bit流模式"//
    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTemp8 = 0XEA; //
    fnRN8302_Write(0x01A1, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.wTemp16 = 0; //
    fnRN8302_Read(0x01A0, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.wTemp16 |= BIT12; //U通道1bit来源内置ADC
    fnRN8302_Write(0x01A0, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.lTemp32 = 0; //
    fnRN8302_Read(0x01A0, EmuCommbuf.ucTempBuf, 2);
    #endif

    if (MeasureModeEMM == MeasureMode)
    {
        EmuCommbuf.ucTemp8 = 0xA2; // 切换到EMM模式
        fnRN8302_Write(RN8302_WMSW, EmuCommbuf.ucTempBuf, 1);
    }
    else if (MeasureModeNVM1 == MeasureMode)
    {
        EmuCommbuf.ucTemp8 = 0xE1; // 切换到NVM1模式
        fnRN8302_Write(RN8302_WMSW, EmuCommbuf.ucTempBuf, 1);
    }

    EmuCommbuf.ucTemp8 = 0xDC; // 写保护
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
}

/*****************************************************************************
** Function name:   fnMeasure_EMUInit(eMeasureMode_TypeDef MeasureMode)
**
** Description: 计量寄存器初始化
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

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    if (Bkgrd.PubData.Active != BKGRD_ACTIVE_POWDN)
    {
        EmuCommbuf.ucTemp8 = 0xA2; // 切换到EMM模式
        fnRN8302_Write(RN8302_WMSW, EmuCommbuf.ucTempBuf, 1);
    }
    else
    {
        EmuCommbuf.ucTemp8 = 0x5C; // 切换到NVM2模式
        fnRN8302_Write(RN8302_WMSW, EmuCommbuf.ucTempBuf, 1);
    }
    SystemDelay(1);
    EmuCommbuf.ucTemp8 = 0xfa; // 软复位
    fnRN8302_Write(RN8302_SOFTRST, EmuCommbuf.ucTempBuf, 1);
    SystemDelay(150);

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTempBuf[0] = 0x77; // 计量控制位
    EmuCommbuf.ucTempBuf[1] = 0x77;
    EmuCommbuf.ucTempBuf[2] = 0x77;
    fnRN8302_Write(RN8302_EMUCON, EmuCommbuf.ucTempBuf, 3);

    fnRN8302_Read(RN8302_HFConst2, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.wTemp16 = MeasureFirmPara.HFConst1;
    fnRN8302_Write(RN8302_HFConst2, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.wTemp16 = MeasureFirmPara.HFConst1 / MeasureFirmPara.HighPulseRate;
    fnRN8302_Write(RN8302_HFConst1, EmuCommbuf.ucTempBuf, 2);

    // 电压增益初始化
    fnRN8302_Write(RN8302_GSUA, (u8 *)&MeasureFirmPara.GSU[0], 2);
    fnRN8302_Write(RN8302_GSUB, (u8 *)&MeasureFirmPara.GSU[1], 2);
    fnRN8302_Write(RN8302_GSUC, (u8 *)&MeasureFirmPara.GSU[2], 2);

    // 电流增益初始化
    fnRN8302_Write(RN8302_GSIA, (u8 *)&MeasureFirmPara.GSI[0], 2);
    fnRN8302_Write(RN8302_GSIB, (u8 *)&MeasureFirmPara.GSI[1], 2);
    fnRN8302_Write(RN8302_GSIC, (u8 *)&MeasureFirmPara.GSI[2], 2);
    fnRN8302_Write(RN8302_GSIN, (u8 *)&MeasureFirmPara.GSI[3], 2);

    // 通道相位校正
    fnRN8302_Write(RN8302_PRTH1L, (u8 *)&MeasureFirmPara.PRth[0], 2);
    fnRN8302_Write(RN8302_PRTH1H, (u8 *)&MeasureFirmPara.PRth[1], 2);
    fnRN8302_Write(RN8302_PRTH2L, (u8 *)&MeasureFirmPara.PRth[2], 2);
    fnRN8302_Write(RN8302_PRTH2H, (u8 *)&MeasureFirmPara.PRth[3], 2); // 通道相位分段参数

    // 通道相位校正
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

    // 电压、电流有效值OFFSET校正
    fnRN8302_Write(RN8302_UA_OS, (u8 *)&MeasureFirmPara.U_OS[0], 2);
    fnRN8302_Write(RN8302_UB_OS, (u8 *)&MeasureFirmPara.U_OS[1], 2);
    fnRN8302_Write(RN8302_UC_OS, (u8 *)&MeasureFirmPara.U_OS[2], 2);

    fnRN8302_Write(RN8302_IA_OS, (u8 *)&MeasureFirmPara.I_OS[0], 2);
    fnRN8302_Write(RN8302_IB_OS, (u8 *)&MeasureFirmPara.I_OS[1], 2);
    fnRN8302_Write(RN8302_IC_OS, (u8 *)&MeasureFirmPara.I_OS[2], 2);
    // 通道功率OFFSET校正
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
    EmuCommbuf.ucTemp8 = 0x19;   // 阻抗检测使能 默认值 00
    fnRN8302_Write(0x015f, EmuCommbuf.ucTempBuf, 1);
    EmuCommbuf.ucTempBuf[0] = 0x00; // ADC配置寄存器 默认值 0000
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
    fnRN8302_Write(RN8302_CFCFG, EmuCommbuf.ucTempBuf, 3);  // 以HFCONST2为高频脉冲常数输出脉冲

    EmuCommbuf.ucTempBuf[0] = 0x00; // 计量控制位 默认值 400000
    EmuCommbuf.ucTempBuf[1] = 0x00;
    EmuCommbuf.ucTempBuf[2] = 0x40; //      // 带零线电流计算矢量和 0x44    不带零线电流计算矢量和 0x40
    fnRN8302_Write(RN8302_EMUCFG, EmuCommbuf.ucTempBuf, 3);

    if (Bkgrd.PriPara.WireMode == 0x01)
    {
        EmuCommbuf.wTemp16 = 0x33;
        fnRN8302_Write(RN8302_MODSEL, EmuCommbuf.ucTempBuf, 1); // 切换到3P3模式
    }

    #if((RN8302C_Ver == RN8306)||(PCB_Version==RN8611_RN7306))
    fnRN8302_HSDCMode_Init();
    #endif

    #if( (RN8302C_Ver == RN8302C_V3)||(RN8302C_Ver == RN8306))
    // fnRN830x_RSIOM(0x00 , 0x00 , 0x3C);  //Vtrim为min,Vref=1.403V ,data数值定义与SPI通讯时一致
    // fnRN830x_RSIOM(0x00 , 0x00 , 0x3F3c);  //Vtrim为max,Vref=1.265V, data数值定义与SPI通讯时一致
    // fnRN830x_RSIOM(0x00 , 0x00 , 0x463C);   //Vref=1.248V 默认值data数值定义与SPI通讯时一致
    //  for(i = 0 ; i < 3 ; i++)
    //  {
    //      fnRN830x_RSIOM( i , 0x00 , MeasureRepairPara.RN8207D_TIRM[i]);   //Vref=1.243V,data数值定义与SPI通讯时一致
    //      if(result == ERROR)
    //      {
    //          SystemDelay(10);  //出错后延时10ms后再操作一遍
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

    // dyf 送检需要支持自热补偿功能，提高精度，为了拿更高分数
    result = fnRN8302_TIRM(MeasureRepairPara.TIRM);
    if (result == ERROR)
    {
        SystemDelay(10);
        result = fnRN8302_TIRM(MeasureRepairPara.TIRM);
    }

    EmuCommbuf.ucTemp8 = 0xDC; // 写保护
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
    MeasureFirmPara.FractionP = 0x04;
    MeasureFirmPara.FractionI = 0x04;
    MeasureFirmPara.FractionU = 0x02;
}

void fnMeasure_EvtVoltLossEMUInit(void)
{
    u8  i, result;
    sDataComm_TypeDef      EmuCommbuf;

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTemp8 = 0xA2; // 切换到EMM模式
    fnRN8302_Write(RN8302_WMSW, EmuCommbuf.ucTempBuf, 1);

    SystemDelay(1);
    EmuCommbuf.ucTemp8 = 0xfa; // 软复位
    fnRN8302_Write(RN8302_SOFTRST, EmuCommbuf.ucTempBuf, 1);
    SystemDelay(150);

    EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

    EmuCommbuf.ucTempBuf[0] = 0x77; // 计量控制位
    EmuCommbuf.ucTempBuf[1] = 0x77;
    EmuCommbuf.ucTempBuf[2] = 0x77;
    fnRN8302_Write(RN8302_EMUCON, EmuCommbuf.ucTempBuf, 3);

    fnRN8302_Read(RN8302_HFConst2, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.wTemp16 = MeasureFirmPara.HFConst1;
    fnRN8302_Write(RN8302_HFConst2, EmuCommbuf.ucTempBuf, 2);

    EmuCommbuf.wTemp16 = MeasureFirmPara.HFConst1 / MeasureFirmPara.HighPulseRate;
    fnRN8302_Write(RN8302_HFConst1, EmuCommbuf.ucTempBuf, 2);

    // 电压增益初始化
    fnRN8302_Write(RN8302_GSUA, (u8 *)&MeasureFirmPara.GSU[0], 2);
    fnRN8302_Write(RN8302_GSUB, (u8 *)&MeasureFirmPara.GSU[1], 2);
    fnRN8302_Write(RN8302_GSUC, (u8 *)&MeasureFirmPara.GSU[2], 2);

    // 电流增益初始化
    fnRN8302_Write(RN8302_GSIA, (u8 *)&MeasureFirmPara.GSI[0], 2);
    fnRN8302_Write(RN8302_GSIB, (u8 *)&MeasureFirmPara.GSI[1], 2);
    fnRN8302_Write(RN8302_GSIC, (u8 *)&MeasureFirmPara.GSI[2], 2);
    fnRN8302_Write(RN8302_GSIN, (u8 *)&MeasureFirmPara.GSI[3], 2);

    // 通道相位校正
    fnRN8302_Write(RN8302_PRTH1L, (u8 *)&MeasureFirmPara.PRth[0], 2);
    fnRN8302_Write(RN8302_PRTH1H, (u8 *)&MeasureFirmPara.PRth[1], 2);
    fnRN8302_Write(RN8302_PRTH2L, (u8 *)&MeasureFirmPara.PRth[2], 2);
    fnRN8302_Write(RN8302_PRTH2H, (u8 *)&MeasureFirmPara.PRth[3], 2); // 通道相位分段参数

    // 通道相位校正
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

    // 电压、电流有效值OFFSET校正
    fnRN8302_Write(RN8302_UA_OS, (u8 *)&MeasureFirmPara.U_OS[0], 2);
    fnRN8302_Write(RN8302_UB_OS, (u8 *)&MeasureFirmPara.U_OS[1], 2);
    fnRN8302_Write(RN8302_UC_OS, (u8 *)&MeasureFirmPara.U_OS[2], 2);

    fnRN8302_Write(RN8302_IA_OS, (u8 *)&MeasureFirmPara.I_OS[0], 2);
    fnRN8302_Write(RN8302_IB_OS, (u8 *)&MeasureFirmPara.I_OS[1], 2);
    fnRN8302_Write(RN8302_IC_OS, (u8 *)&MeasureFirmPara.I_OS[2], 2);
    // 通道功率OFFSET校正
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
    fnRN8302_Write(RN8302_CFCFG, EmuCommbuf.ucTempBuf, 3);  // 以HFCONST2为高频脉冲常数输出脉冲
    EmuCommbuf.ucTempBuf[0] = 0x00; // 计量控制位 默认值 400000
    EmuCommbuf.ucTempBuf[1] = 0x00;
    EmuCommbuf.ucTempBuf[2] = 0x40; //      // 带零线电流计算矢量和 0x44    不带零线电流计算矢量和 0x40
    fnRN8302_Write(RN8302_EMUCFG, EmuCommbuf.ucTempBuf, 3);

    if (Bkgrd.PriPara.WireMode == 0x01)
    {
        EmuCommbuf.wTemp16 = 0x33;
        fnRN8302_Write(RN8302_MODSEL, EmuCommbuf.ucTempBuf, 1); // 切换到3P3模式
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

    EmuCommbuf.ucTemp8 = 0xDC; // 写保护
    fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
    MeasureFirmPara.FractionP = 0x04;
    MeasureFirmPara.FractionI = 0x04;
    MeasureFirmPara.FractionU = 0x02;
}

/*****************************************************************************
** Function name:u8 fnRN8302_ChkSum(void)
**
** Description:RN8302 效验和判断
**
** Parameters:NONE
**
** Returned value:TRUE=效验和正确;  FALSE=效验错误
**
******************************************************************************/
u8 fnRN8302_ChkSum(void)
{
    //---------校验和判断------------------------
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
** Description:通讯对计量RN8302各寄存器进行初始化
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

    if (Flag == 1)  //初始化计量参数，恢复到默认值
    {
        Std_Memset(&MeasureFirmPara, 0, sizeof(sMeasureFirmPara_TypeDef));

        Std_Memcpy((u8 *)&MeasureFirmPara, (u8 *)pMeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));

        fnCrc_Check(0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef) - 2, (u8 *)&MeasureFirmPara.Crc);

        fnFile_Write(FileId_FirmPara, 0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));
        //----------影响量补偿--------------
        Std_Memset((u8 *)&MeasureRepairPara, 0x00, sizeof(sMeasureRepairPara_TypeDef));

        Std_Memcpy((u8 *)&MeasureRepairPara, (u8 *)&RepairParaDefault, sizeof(sMeasureRepairPara_TypeDef));

        fnCrc_Check(0, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc);

        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sMeasureRepairPara_TypeDef));

        fnHarmonic_FirmParaInit();
    }
    // 初始化计量参数默认值,其他补偿值不清
    else if (Flag == 2)
    {
        Std_Memset(&MeasureFirmPara, 0, sizeof(sMeasureFirmPara_TypeDef));

        Std_Memcpy((u8 *)&MeasureFirmPara, (u8 *)pMeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));

        fnCrc_Check(0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef) - 2, (u8 *)&MeasureFirmPara.Crc);

        fnFile_Write(FileId_FirmPara, 0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));
    }
    else   //原计量参数合法则保留原校表参数，程序升级时使用
    {
        Std_Memset(&MeasureFirmPara, 0, sizeof(sMeasureFirmPara_TypeDef));
        fnFile_Read(FileId_FirmPara, 0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));
        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sMeasureRepairPara_TypeDef));

        if ((MeasureFirmPara.FractionI != pMeasureFirmPara->FractionI) || (MeasureFirmPara.HighPulseRate != pMeasureFirmPara->HighPulseRate))
        {
            Std_Memcpy((u8 *)&MeasureFirmPara, (u8 *)pMeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));

            fnCrc_Check(0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef) - 2, (u8 *)&MeasureFirmPara.Crc);

            fnFile_Write(FileId_FirmPara, 0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef));

            //----------影响量补偿--------------
            Std_Memset((u8 *)&MeasureRepairPara, 0x00, sizeof(sMeasureRepairPara_TypeDef));

            Std_Memcpy((u8 *)&MeasureRepairPara, (u8 *)&RepairParaDefault, sizeof(sMeasureRepairPara_TypeDef));

            fnCrc_Check(0, (u8 *)&MeasureRepairPara.Volt, sizeof(sVoltRepairPara_TypeDef) - 2, (u8 *)&MeasureRepairPara.Volt.Crc);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_VoltRepair_EnOrDis, (u8 *)&MeasureRepairPara.Volt, sizeof(sMeasureRepairPara_TypeDef));

            fnHarmonic_FirmParaInit();
        }
    }

    fnMeasure_EMUInit();

    SystemDelay(100);   // dyf 读CheckSum容易出错，10 => 100
    MeasureFirmPara.ChkSum1 = 0;
    fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureFirmPara.ChkSum1, 3) ;
    fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_ChkSum1, (u8 *)&MeasureFirmPara.ChkSum1, FileItemInfoLen_FirmPara_ChkSum1);
}

/*****************************************************************************
** Function name:void fnRN8302_CorrectionMeter(void)
**
** Description:三相RN8302计量校正程序
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
                MeasureFirmPara.GSU[i] = (u16)(ADErr * 32768 + 0.5);    //四舍五入
            }
            else
            {
                MeasureFirmPara.GSU[i] = (u16)(65536 + ADErr * 32768 + 0.5);
            }
            fnRN8302_Write(RN8302_GSUA + i, (u8 *)&MeasureFirmPara.GSU[i], 2);
        }
        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_GSU, (u8 *)&MeasureFirmPara.GSU[0], 6);

        for (i = 0; i < 3; i++) //电流增益校正
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

        // 功率系数计算
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
        if ((TempBuf[0] == 0) && (TempBuf[1] == 0))     // 以角度进行校正
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
        if ((TempBuf[0] == 0) && (TempBuf[1] == 0))     // 以角度进行校正
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
        if ((TempBuf[0] == 0) && (TempBuf[1] == 0))     // 以角度进行校正
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
                    tempub = ADErr * 32768 + 0.5; //四舍五入
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
    // 零线电流校准
    else if (MeasureRms.PriData.Flag & MEASURE_FLAG_CorrectionIn)
    {
        fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RatedI, (u8 *)&tempib, 2);
        //      fnFile_Read(FileId_FirmPara,FileItemInfoOffAddr_FirmPara_RatedIrms, (u8 *)&tempis, 4);

        EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
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
    // 计算校验和
    else if (MeasureRms.PriData.Flag & MEASURE_FLAG_CalcCheckSum)
    {
        SystemDelay(10);
        MeasureRms.PriData.Flag &= ~MEASURE_FLAG_CalcCheckSum;
    }
    else
    {
        return;
    }

    EmuCommbuf.ucTemp8 = 0xDC; // 写保护
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
        //-----出错后再读1次-------------
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

    fnRN8302Mode_Init(MeasureModeEMM);  //配置IO，配置模式
    #if (PCB_Version==RN8611_RN7306)
    fnRN8611_EnergyPulseIO_Init();
    fnRn8302_HSDCSPI_Init();
    fnBSP_ExModuleSpi_Init();
    #endif

    Std_Memset(&MeasureRegTmp, 0, sizeof(sMeasureRegTmp_TypeDef));      //初始化RAM
    Std_Memset(&MeasureRms, 0, sizeof(sMeasureRms_TypeDef));        //初始化RAM
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

    // dyf 增加读直流偶次谐波补偿使能开关
    fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Flag_EnOrDis, &parameter.xiebo_flag, 1);
    if ((parameter.xiebo_flag == 0x00) || (parameter.xiebo_flag == 0xFF))
    {
        parameter.xiebo_flag = 0x5A;    // 如果开关参数无效，则默认为关闭0x5A
    }
}

// 停电低功耗读取电压电流数据
void fnMeasure_EvtVoltLoss(void)
{
    u8 i;

    fnRN8302Mode_Init(MeasureModeEMM);  //配置IO，配置模式

    Std_Memset(&MeasureRegTmp, 0, sizeof(sMeasureRegTmp_TypeDef));      //初始化RAM
    Std_Memset(&MeasureRms, 0, sizeof(sMeasureRms_TypeDef));            //初始化RAM
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

    //读电压电流
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

    //电压电流计算
    for (i = 0; i < 3; i++)
    {
        MeasureRms.PubData.U[i] = (s32)(100 * (float)MeasureRegTmp.Urms[i] / (10 * (MeasureFirmPara.KUrms)) + 0.5); //电压 hex
    }

    for (i = 0; i < 3; i++)
    {
        MeasureRms.PubData.I[i] = (s32)(100 * (float)MeasureRegTmp.Irms[i] / (MeasureFirmPara.KIArms) + 0.5);
    }

    RN8302_PowerOff();

    ////计量模块相关
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
    Rn8xxx_GPIO_CfgPullMode(PinSDI_C, Pull_ON); // dyf 需要关闭内部默认的上拉电阻，否则导致掉电后功耗比较高；Pull_ON 对应关闭上拉，与其他引脚设置不同
}

u32 fnMeasure_UnblCalculate(u8 WireMode, u32 UIa, u32 UIb, u32 UIc)
{
    u32 Max, Min;

    if (WireMode == 0)  //三相四线
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
    else                //三相三线
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

//-----谐波电压有效值计算----------
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

    Bkgrd.PubData.FUrmsRdFlg |= 0x80;   // dyf add 基波读取并计算完成
}

//-----谐波电流有效值计算----------
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

//-----谐波功率有效值计算----------
void fnMeasureHPRMS_Get(void)
{
    u8 i;

    // 谐波总功率
    MeasureRms.PubData.HPtw = (float)HarmonicData.PubData.PtHarmonicPw[0] / (MeasureFirmPara.KPrms) * 1000;
    MeasureRms.PubData.HNtw = (float)(abs(HarmonicData.PubData.NtHarmonicPw[0])) / (MeasureFirmPara.KPrms) * 1000;

    // 基波功率
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
** Descriptions:      计量主函数
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

    check_rn7306_reg();     // dyf 判断直流偶次谐波补偿开关和参数，下发补偿

    if (MeasureRms.PriData.Flag & MEASURE_FLAG_RST)
    {
        fnWDT_Restart();
        fnMeasure_EMUInit();
        MeasureRms.PriData.Flag &= ~MEASURE_FLAG_RST;

        //      fnWaveSpiOutToExModule(NULL, 0);
    }

    if (fnMeasure_VoltRepair_Exe() == FALSE)  // 电压影响量状态判断
    {
        //---------校验和判断------------------------
        MeasureRegTmp.ChkSum1 = 0;
        fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureRegTmp.ChkSum1, 3) ;

        // dyf 增加判断直流偶次谐波补偿开启情况下的校验和是否一致
        if ((MeasureRegTmp.ChkSum1 == MeasureFirmPara.ChkSum1) || ((parameter.xiebo_flag != 0x5A) && (check_rn7306_checksum(MeasureRegTmp.ChkSum1))))
        {
            MeasureRegTmp.ChkErrCnt = 0;
            MeasureRms.PriData.Flag &= ~MEASURE_FLAG_RST;
        }
        else
        {
            MeasureRegTmp.ChkSum1 = 0;
            fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureRegTmp.ChkSum1, 3) ;
            // 考虑直流偶次谐波补偿的情况
            if (((parameter.xiebo_flag == 0x5A) && (MeasureRegTmp.ChkSum1 != MeasureFirmPara.ChkSum1))
                || ((parameter.xiebo_flag != 0x5A) && (!check_rn7306_checksum(MeasureRegTmp.ChkSum1))))
            {
                MeasureRegTmp.ChkErrCnt++;
                if (MeasureRegTmp.ChkErrCnt >= 5)
                {
                    MeasureRms.PriData.Flag |= MEASURE_FLAG_RST;  // dyf 可以屏蔽后测试
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

    //读电压电流
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

    //读功率
    for (i = 0; i < 12; i++)
    {
        MeasureRegTmp.Pw[i] = 0 ;
        fnRN8302_Read(RN8302_PA + i, (u8 *)&MeasureRegTmp.Pw[i], 4);
    }

    //读频率
    fnRN8302_Read(RN8302_UFreq, (u8 *)&MeasureRegTmp.Frequency, 3);

    //读潜动启动标志位
    fnRN8302_Read(RN8302_Noload, (u8 *)&MeasureRegTmp.PQNoLoad, 2);

    //读功率方向
    fnRN8302_Read(RN8302_PQSign, (u8 *)&MeasureRegTmp.PDirect, 2);

    //读电压电流角度值
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

    // 读功率因数
    for (i = 0; i < 3; i++)
    {
        MeasureRegTmp.Pf[i + 1] = 0 ;
        fnRN8302_Read(RN8302_PfA + i, (u8 *)&MeasureRegTmp.Pf[i + 1], 3);
    }
    MeasureRegTmp.Pf[0] = 0 ;
    fnRN8302_Read(RN8302_PfTV, (u8 *)&MeasureRegTmp.Pf[0], 3);

    //功率计算
    for (j = 0; j < 3; j++)
    {
        for (i = 0; i < 3; i++)
        {
            MeasureRms.PubData.Pw[j * 4 + i + 1] = (s32)(1000 * (float)(MeasureRegTmp.Pw[j * 4 + i]) / (((s32)MeasureFirmPara.KPrms))); //计算｛Pa Pb Pc｝、｛Qa Qb Qc｝、｛Sa Sb Sc｝
        }
    }
    for (i = 0; i < 3; i++)
    {
        MeasureRms.PubData.Pw[i * 4] = (s32)(1000 * (float)(MeasureRegTmp.Pw[i * 4 + 3]) / (((s32)MeasureFirmPara.KPrms))); //计算P、Q、S
    }

    for (i = 0; i < 3; i++)
    {
        //S^2 =P^2+Q^2
        MeasureRms.PubData.Pw[9 + i] = sqrt((s64)(MeasureRms.PubData.Pw[1 + i]) * (MeasureRms.PubData.Pw[1 + i]) + (s64)(MeasureRms.PubData.Pw[5 + i]) *
                                            (MeasureRms.PubData.Pw[5 + i])); //计算｛Pa Pb Pc｝、｛Qa Qb Qc｝、｛Sa Sb Sc｝
    }

    //电压电流计算
    for (i = 0; i < 3; i++)
    {
        MeasureRms.PubData.U[i] = (s32)(100 * (float)MeasureRegTmp.Urms[i] / (10 * (MeasureFirmPara.KUrms)) + 0.5); //电压 hex
    }

    for (i = 0; i < 3; i++)
    {
        MeasureRms.PubData.I[i] = (s32)(100 * (float)MeasureRegTmp.Irms[i] / (MeasureFirmPara.KIArms) + 0.5);
    }

    MeasureRms.PubData.In = (s32)(100 * (float)MeasureRegTmp.Irms[3] / (MeasureFirmPara.KIArms) + 0.5);

    MeasureRms.PubData.VectorI[2] = (s32)(100 * (float)(MeasureRegTmp.VectorI[2] / (MeasureFirmPara.KIArms))) * 4;

    //频率计算
    if ((MeasureRegTmp.Frequency > 1638400) || (MeasureRegTmp.Frequency < 1092266)) //when 50HZ is 5120 ;+- 20% frequence is 6144 and 4096
    {
        MeasureRegTmp.Frequency = 1310720;
    }
    MeasureRms.PubData.Frequency = (u16)(65536000 / (MeasureRegTmp.Frequency / 100));

    //功率因数计算
    //总功率因数
    //MeasureRms.PubData.Pf[0]=fnDFConver_Bcd16To16((s16)((1000*(double)(Dl645FrontTmp.Pw[0]/((MeasureFirmPara.PRmsConst))+Dl645FrontTmp.Pw[1]/((MeasureFirmPara.PRmsConst))+Dl645FrontTmp.Pw[2]/((MeasureFirmPara.PRmsConst))))/(Dl645FrontTmp.Pw[6]/((MeasureFirmPara.PRmsConst))+Dl645FrontTmp.Pw[7]/((MeasureFirmPara.PRmsConst))+Dl645FrontTmp.Pw[8]/((MeasureFirmPara.PRmsConst)))));
    if (Bkgrd.PriPara.WireMode == 0x01)
    {
        Tempw = (s32)((MeasureRegTmp.Pw[3]) / ((MeasureFirmPara.KPrms))) ;
        Tempq = (s32)((MeasureRegTmp.Pw[7]) / ((MeasureFirmPara.KPrms))) ;
        // 计算总视在功率
        Tempws = (s32)sqrt((float)Tempw * (float)Tempw + (float)Tempq * (float)Tempq);
        MeasureRms.PubData.Pw[8] = Tempws / 100;

        //功率因数计算
        //总功率因数
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
            MeasureRms.PubData.Pf[0] = (s16)((float)MeasureRegTmp.Pf[0] / 8388.608 + 0.5); //四舍五入
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
    //ABC三相功率因数
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
                MeasureRms.PubData.Pf[i + 1] = (s16)((float)MeasureRegTmp.Pf[i + 1] / 8388.608 + 0.5); //四舍五入
                MeasureRms.PubData.Pf[i + 1] = 0xffff - MeasureRms.PubData.Pf[i + 1] + 1;
            }
            else
            {
                MeasureRms.PubData.Pf[i + 1] = (s16)((float)MeasureRegTmp.Pf[i + 1] / 8388.608 + 0.5);    //四舍五入
            }

            if (abs(MeasureRms.PubData.Pf[i + 1]) > 1000)
            {
                MeasureRms.PubData.Pf[i + 1] = 1000;
            }
        }
    }

    // 相角计算
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
            MeasureRms.PubData.Angle[i + 3] = TempAngle2 - MeasureRms.PubData.Angle[i]; //电压与电流相角
            MeasureRms.PubData.Angle[i + 6] = TempAngle2; //ABC相电流与A相电压角度
        }
        else
        {
            MeasureRms.PubData.Angle[i + 3] = 0; //电压与电流相角
            MeasureRms.PubData.Angle[i + 6] = 0; //ABC相电流与A相电压角度
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
    //--------合法性判断--------------
    //--------ABC----------
    for (i = 0; i < 3; i++)
    {
        if (MeasureRms.PubData.Pw[i + 1] < 0)
        {
            MeasureRms.PubData.I[i] = -MeasureRms.PubData.I[i];
        }
        //--------电流判断----------------
        if (abs(MeasureRms.PubData.I[i]) < ClearIValue)
        {
            MeasureRms.PubData.I[i] = 0x00;
        }

        //--------电压判断-----------------
        if (MeasureRms.PubData.U[i] < ClearUValue)
        {
            MeasureRms.PubData.U[i] = 0x00;
        }

        //----------功率判断--------------------
        if ((abs(MeasureRms.PubData.I[i]) < ClearIValue) || (MeasureRms.PubData.U[i] < ClearUValue)
            || (abs(MeasureRms.PubData.Pw[i + 9]) < ClearPwValue)) //视在
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
            //------有功判断---------------------
            if (MeasureRegTmp.PQNoLoad & (1 << i)) //有功和视在处于潜动状态
            {
                MeasureRms.PubData.Pw[i + 1] = 0x00;
                MeasureRms.PubData.Pw[i + 9] = 0x00;
                MeasureRms.PubData.Pf[i + 1] = 1000;
                MeasureRegTmp.PDirect &= ~(0x01 << i);
            }
            else if (abs(MeasureRms.PubData.Pw[i + 1]) < ClearPwValue) //有功
            {
                MeasureRms.PubData.Pw[i + 1] = 0x00;
                MeasureRms.PubData.Pf[i + 1] = 0;
                MeasureRegTmp.PDirect &= ~(0x01 << i);
            }
            //-------无功判断-----------------------------
            if (MeasureRegTmp.PQNoLoad & (1 << (i + 4))) //无功处于潜动状态
            {
                MeasureRms.PubData.Pw[i + 5] = 0x00;
                MeasureRms.PubData.Pf[i + 1] = 1000;
                MeasureRegTmp.PDirect &= ~(0x01 << (i + 4));
            }
            else if (abs(MeasureRms.PubData.Pw[i + 5]) < ClearPwValue) //无功
            {
                MeasureRms.PubData.Pw[i + 5] = 0x00;
                MeasureRms.PubData.Pf[i + 1] = 1000;
                MeasureRegTmp.PDirect &= ~(0x01 << (i + 4));
            }
        }
    }
    //------零线电流判断-------------
    if (abs(MeasureRms.PubData.In) < ClearIValue)
    {
        MeasureRms.PubData.In = 0x00;
    }

    //---------总--------------
    if (((abs(MeasureRms.PubData.I[0]) < ClearIValue) && (abs(MeasureRms.PubData.I[1]) < ClearIValue) && (abs(MeasureRms.PubData.I[2]) < ClearIValue)) ||
        ((MeasureRms.PubData.U[0] == 0) && (MeasureRms.PubData.U[1] == 0) && (MeasureRms.PubData.U[2] == 0)) ||
        (abs(MeasureRms.PubData.Pw[8]) < ClearPwValue))   //视在总
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
        if ((MeasureRegTmp.PQNoLoad & 0x07) == 0x07) //三相有功和视在都处于潜动状态
        {
            MeasureRms.PubData.Pw[0] = 0x00;
            MeasureRms.PubData.Pw[8] = 0x00;
            MeasureRms.PubData.Pf[0] = 1000;
            MeasureRegTmp.PDirect &= ~(0x01 << 3);
        }
        else if (abs(MeasureRms.PubData.Pw[0]) < nPhs * ClearPwValue)   //有功总
        {
            MeasureRms.PubData.Pw[0] = 0x00;
            MeasureRms.PubData.Pf[0] = 0;
            MeasureRegTmp.PDirect &= ~(0x01 << 3);
        }

        //-------无功判断-----------------------------
        if ((MeasureRegTmp.PQNoLoad & 0x70) == 0x70) //无功处于潜动状态
        {
            MeasureRms.PubData.Pw[4] = 0x00;
            MeasureRms.PubData.Pf[0] = 1000;
            MeasureRegTmp.PDirect &= ~(0x01 << 7);
        }
        else if (abs(MeasureRms.PubData.Pw[4]) < ClearPwValue)  //无功总
        {
            MeasureRms.PubData.Pw[4] = 0x00;
            MeasureRms.PubData.Pf[0] = 1000;
            MeasureRegTmp.PDirect &= ~(0x01 << 7);
        }
    }

    // dyf add 视在功率符号等于有功功率符号
    for (i = 0; i < 4; i++)
    {
        if (MeasureRms.PubData.Pw[i] < 0)
        {
            MeasureRms.PubData.Pw[8 + i] = 0 - MeasureRms.PubData.Pw[8 + i];
        }
    }

    // dyf add 功率因素符号等于有功功率符号
    for (i = 0; i < 4; i++)
    {
        if (MeasureRms.PubData.Pw[i] < 0)
        {
            MeasureRms.PubData.Pf[i] = 0 - abs(MeasureRms.PubData.Pf[i]);
        }
    }

    //同步数据块功率计算 dyf 搬移到此
    for (i = 0; i < 12; i++)
    {
        SynVarOtherUnitData.Pw[i] = MeasureRms.PubData.Pw[i] / 10;
    }

    //同步数据块功率因素计算 dyf 搬移到此，在功率因素异常处理、默认处理后再提供给双芯SPI同步，防止只加电压、不加电流时功率因素跳变
    for (i = 0; i < 4; i++)
    {
        SynVarOtherUnitData.Pf[i] = MeasureRms.PubData.Pf[i] * 10;
    }

    //转换功率方向
    MeasureRms.PubData.PDirect = ((MeasureRegTmp.PDirect << 1) & 0xee) | ((MeasureRegTmp.PDirect >> 3) & 0x11);

    //    //电压电流不平衡率计算
    //    //-------------有1相大于临界电压时计算不平衡率----------------
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
    //  //------有1相电流大于5%Ib时计算电流不平衡率---------------------------
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

    //从RN8302读出的即为脉冲数//{P,Q,Ps},{Pa,Qa,Psa},{Pb,Qb,Psb},{Pc,Qc,Psc}{Fp,Fq}{Fpa,Fqa}{Fpb,Fqb}{Fpc,Fqc}
    /*读电能寄存器*/
    for (i = 0; i < 3; i++)
    {
        MeasureRegTmp.Pulse[(i + 1) * 3] = 0;
        fnRN8302_Read(RN8302_EPA + i, (u8 *)&MeasureRegTmp.Pulse[(i + 1) * 3], 3); //有功
        MeasureRegTmp.Pulse[(i + 1) * 3 + 1] = 0;
        fnRN8302_Read(RN8302_EQA + i, (u8 *)&MeasureRegTmp.Pulse[(i + 1) * 3 + 1], 3); //无功
        MeasureRegTmp.Pulse[(i + 1) * 3 + 2] = 0;
        fnRN8302_Read(RN8302_ESA + i, (u8 *)&MeasureRegTmp.Pulse[(i + 1) * 3 + 2], 3); //视在有功
        MeasureRegTmp.Pulse[14 + i * 2] = 0;
        fnRN8302_Read(RN8302_FEPA + i, (u8 *)&MeasureRegTmp.Pulse[14 + i * 2], 3); //基波有功
        MeasureRegTmp.Pulse[15 + i * 2] = 0;
        fnRN8302_Read(RN8302_FEQA + i, (u8 *)&MeasureRegTmp.Pulse[15 + i * 2], 3); //基波有功
    }
    MeasureRegTmp.Pulse[0] = 0;
    fnRN8302_Read(RN8302_EPT, (u8 *)&MeasureRegTmp.Pulse[0], 3);        //总有功
    MeasureRegTmp.Pulse[1] = 0;
    fnRN8302_Read(RN8302_EQT, (u8 *)&MeasureRegTmp.Pulse[1], 3);        //总无功
    MeasureRegTmp.Pulse[2] = 0;
    fnRN8302_Read(RN8302_ESTA, (u8 *)&MeasureRegTmp.Pulse[2], 3);       //总视在
    MeasureRegTmp.Pulse[12] = 0;
    fnRN8302_Read(RN8302_PosFEPT, (u8 *)&MeasureRegTmp.Pulse[12], 3);    //基波正向有功
    MeasureRegTmp.Pulse[13] = 0;
    fnRN8302_Read(RN8302_NegFEPT, (u8 *)&MeasureRegTmp.Pulse[13], 3);    //基本反向有功

    for (i = 0; i < 20; i++) //电能高频脉冲转换成低频脉冲
    {
        MeasureRegTmp.Pulse_Eg[i] += MeasureRegTmp.Pulse[i];
    }
    //    for(i=0;i<12;i++)//高频脉冲转换成低频脉冲
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

//--------------关闭波形缓存功能----------------
void fnMeasure_WaveColse(void)
{
}

/*********************************************************************************************************
** Function name:       fnMeasure_TxHarmonicPack
** Descriptions:        波形数据发送，谐波数据处理，从256点中抽取64点做谐波处理
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
** Description:RN8209半满中断，发起读取波形缓存读取,DMA方式
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
** Description: 1、接收RN8209波形缓存，全满中断，对接收数据进行合法性判断，封装到电压电流缓存
**              2、满一周波数据后进行拉格朗日插值
**              3、将插值后波形数据输出到另一组SPI，供其他模块进行电能质量分析
**              4、保存剩余的波形点数，避免波形不连续
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
// 函数名： fnMeasureAverage_PowerCalc
// 输入：
// 返回：   NONE
// 描述：   计算有功，无功，1分钟平均功率
// 注释：
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
