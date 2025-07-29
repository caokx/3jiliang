#define  _Drive_ALLINT

#include <BSP.h>
#include <App.h>

#if (HarmonicPulseOut_Mode==HarmonicPulseOut_Interrupt)
u8 PtHPwPulseCnt = 0, NtHPwPulseCnt = 0;
#endif

//---------------------------------------------------
void TC0_HANDLER(void)    //系统主节拍5ms
{
    extern sWDOG_TypeDef  Wdog;

    TC0->STA = 0x0f;
    SysStamp += 5;      //5MS
    if (Bkgrd.PubData.Active != BKGRD_ACTIVE_POWDN)
    {
        if (Wdog.T_WDOG)
        {
            fnWDT_Restart();
            Wdog.T_WDOG--;
        }

        //      if(fnStamp_Through(Bkgrd.PubData.SecondSysStamp) >= 1000 )
        //      {
        //          Bkgrd.PubData.SecondSysStamp = SysStamp;
        //
        //      }
        //      if(AdcWaveData.SendFlag == CTLSTAR)
        //      {
        //          AdcWaveData.SendFlag = CTLSTOP;
        //          fnMeasure_TxHarmonicPack();
        //      }

        fnWaveHfrmsSmple();

        fnKey_Scan();
    }
}

void TC1_HANDLER(void)
{
    TC1->STA = 0x0f;
    #if (HarmonicPulseOut_Mode==HarmonicPulseOut_Interrupt)

    if (NtHPwPulseCnt)
    {
        NtHPwPulseCnt--;
        if (NtHPwPulseCnt == 0)
        {
            Rn8xxx_GPIO_CfgIOMode(Pin_NtHPF, GPIO_MODE_IN, NORMAL_IN);
            PinWrite_NtHPF(1);
        }
    }
    if (PtHPwPulseCnt)
    {
        PtHPwPulseCnt--;
        if (PtHPwPulseCnt == 0)
        {
            Rn8xxx_GPIO_CfgIOMode(Pin_PtHPF, GPIO_MODE_IN, NORMAL_IN);
            PinWrite_PtHPF(1);
        }
    }
    if ((PtHPwPulseCnt == 0) && (NtHPwPulseCnt == 0))
    {
        Rn8xxx_TC_TimeStop(Timer1);
    }
    #endif
}

void D2F_HANDLER(void)
{
    u32 Irqflg;
    Irqflg = D2F->IF;

    #if (HarmonicPulseOut_Mode==HarmonicPulseOut_Interrupt)

    if (Irqflg & 0x01)
    {
        NtHPwPulseCnt = 80;
        Rn8xxx_GPIO_CfgIOMode(Pin_NtHPF, GPIO_MODE_OUT, N_OPENDRAIN_OUT);
        PinWrite_NtHPF(0);
        if (!(TC1->CTRL & 0x01))
        {
            Rn8xxx_TC_TimeInit(Timer1, 1);
            Rn8xxx_TC_TimeStar(Timer1, ENABLE);
        }
    }
    if (Irqflg & 0x02)
    {
        PtHPwPulseCnt = 80;
        Rn8xxx_GPIO_CfgIOMode(Pin_PtHPF, GPIO_MODE_OUT, N_OPENDRAIN_OUT);
        PinWrite_PtHPF(0);
        if (!(TC1->CTRL & 0x01))
        {
            Rn8xxx_TC_TimeInit(Timer1, 1);
            Rn8xxx_TC_TimeStar(Timer1, ENABLE);
        }
    }

    #endif
    D2F->IF = Irqflg;
}

#if(METERTYPE == 0)
u16 MAXFrmLen[3] = {512, 200, 512};
#else
u16 MAXFrmLen[4] = {512, 200, 255, 512};
#endif
u16 lastRxBufferSize;
void UART0_HANDLER(void)
{
    u32  status, dmastatus;
    FIFOMailBox_CFG_TypeDef fifo_cfg;

    status = UART0->STA;
    dmastatus = UART0->DMA_FLG;
    if (dmastatus & 0x0A)
    {
        if (lastRxBufferSize != gDl698AL_Server.pAlChan[SCOM_PORT_RS485A].nego.apdu_size_rx_nego)
        {
            lastRxBufferSize = gDl698AL_Server.pAlChan[SCOM_PORT_RS485A].nego.apdu_size_rx_nego;
            fifo_cfg.TxBuffer = pDl698DL_Channel[SCOM_PORT_RS485A].stTxBuf.pData;
            fifo_cfg.RxBuffer = pDl698DL_Channel[SCOM_PORT_RS485A].stRxBuf.pData;
            fifo_cfg.RxBufferSize = gDl698AL_Server.pAlChan[SCOM_PORT_RS485A].nego.apdu_size_rx_nego + 50;
            fifo_cfg.TxBufferSize = gDl698AL_Server.pAlChan[SCOM_PORT_RS485A].nego.apdu_size_tx_nego;
            FIFO_Init(SCOM_PORT_RS485A, fifo_cfg);
        }
        pDl698DL_Channel[SCOM_PORT_RS485A].stRxBuf.usIndex = 0;
        pDl698DL_Channel[SCOM_PORT_RS485A].stScom.ucComflag = DL698_SCOMPK_EFLAG_IDLE;
        fnScomUart_Init(SCOM_PORT_RS485A);
    }

    UART0->STA = status;
    UART0->DMA_FLG = dmastatus;

    return;
}

void UART1_HANDLER(void)
{
    u32  status ;

    status = UART1->STA;

    //----------------
    UART1->STA = status;

    return;
}

void UART3_HANDLER(void)  //ZB
{
    u32  status ;

    status = UART3->STA;

    //----------------
    UART3->STA = status;  // clear receive IF

    return;
}

void UART4_HANDLER(void)  //485A
{
    u32  status ;

    status = UART4->STA;

    //----------------
    UART4->STA = status;  // clear receive IF

    return;
}

void UART5_HANDLER(void)   //
{
    //      u8 temp = 0;
    u32  status;

    status = UART5->STA;
    UART5->STA = status;
    return;//
}

void EXT1_HANDLER(void)
{
    u32  status;

    status = INTC->STA;
    INTC->STA = status;         //INTP3 IF clear

    Inactive.InactiveFlag.fChange |= 0x04;

    //  if(PinRead_KeyShell())
    //  {
    //      Key.Release |= 0X0040;          //记录合盖记录用
    //      Key.Press &= 0XFFBF;
    //
    //      Inactive.InactiveFlag.fChange |= 0x04;
    //  }
    //  else
    //  {
    //      Key.Press |= 0X0040;
    //      Key.Release &= 0XFFBF;
    //
    //      Inactive.InactiveFlag.fChange |= 0x04;
    //  }
}

void EXT3_HANDLER(void)
{
    u32  status;

    status = INTC->STA;
    INTC->STA = status;         //INTP3 IF clear
}

void EXT4_HANDLER(void)
{
    u32  status;

    status = INTC->STA;

    fnMeasure_DMAReadWaveData();

    INTC->STA = status;         //INTP4 IF clear
}

void EXT6_HANDLER(void)
{
    u32  status;

    status = INTC->STA;
    INTC->STA = status;         //INTP IF clear

    //  if((MeasureRms.PubData.DirectSta.Direct == QUADRANT_I)||(MeasureRms.PubData.DirectSta.Direct == QUADRANT_IV))
    //      MeasureRegTmp.Pulse_Eg[0]++;  //正向有功
    //  else
    //      MeasureRegTmp.Pulse_Eg[1]++;   //反向有功
}

void EXT7_HANDLER(void)
{
    u32  status;

    status = INTC->STA;
    INTC->STA = status;         //INTP IF clear

    //  if(MeasureRms.PubData.DirectSta.Direct == QUADRANT_I)
    //      MeasureRegTmp.Pulse_Eg[2]++;  //无功脉冲
    //
    //  else if(MeasureRms.PubData.DirectSta.Direct == QUADRANT_II)
    //      MeasureRegTmp.Pulse_Eg[3]++;  //无功脉冲

    //  else if(MeasureRms.PubData.DirectSta.Direct == QUADRANT_III)
    //      MeasureRegTmp.Pulse_Eg[4]++;  //无功脉冲

    //  else if(MeasureRms.PubData.DirectSta.Direct == QUADRANT_IV)
    //      MeasureRegTmp.Pulse_Eg[5]++;  //无功脉冲
}

/*****************************************************************************
** Function name:SPI_HANDLER
**
** Description:SPI_DMA计量芯片采样数据发送完成中断
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void SPI_HANDLER(void)
{
    u32 status;
    u32 dmastatus;
    //uSPI_DMAPara_TypeDef   spi_DmaPara;

    dmastatus = SPI->DMA_FLG;
    status = SPI->STA;

    // CS拉高
    if (status)
    {
        if (status & 0x80)
        {
            fnRN8302_HSPI_DMAInit();
        }

        SPI->STA = status;
    }

    if (dmastatus)
    {
        if (dmastatus & 0x08)
        {
            fnWaveHsdcSpi_AdcCheck();
            //          fnRN8302_HSPI_DMAInit();
        }

        SPI->DMA_FLG = dmastatus;
    }

    //  SPI->DMA_FLG = dmastatus;
    //  SPI->STA = status;
}

/*****************************************************************************
** Function name:SPI1_HANDLER
**
** Description:SPI_DMA方式接收RN8209全满中断
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void SPI1_HANDLER(void)
{
    u32  dmastatus = 0, status2 = 0;

    status2 = SPI1->STA;
    dmastatus = SPI1->DMA_FLG;

    //  if(dmastatus&0x08)
    //  {
    //      fnMeasure_WaveData();
    //  }

    //  if(status&0x80)//上升沿
    {
        if ((dmastatus & 0x0A) || (SPI1->DMA_CTRL & 0x01)) //DMA已经发送完成或者DMA接收缓冲区满或者正在发送
        {
            pDl698DL_Channel[SCOM_PORT_SPI].stRxBuf.usIndex = 0;
            pDl698DL_Channel[SCOM_PORT_SPI].stScom.ucComflag = DL698_SCOMPK_EFLAG_IDLE;
            fnScomSpi_Init(SCOM_PORT_SPI);
            SPI1->TX = 0x00;
            SPI1->TXDFLT = 0x00;
        }
        else
        {
            SPI1->TX = 0xAA;
            SPI1->TXDFLT = 0xAA;
        }
    }

    SPI1->STA = status2;//清状态

    SPI1->DMA_FLG = dmastatus;          //INTP IF clear
}

void CMP_HANDLER(void)
{
    //本模块不检测上电，只检测掉电
    if (MADC->LVD_STAT & 0x10) //检测到LVD中断
    {
        MADC->LVD_STAT |= 0x10;
        if (!(MADC->LVD_STAT & 0x01))
        {
            Bkgrd.PubData.Active = BKGRD_ACTIVE_POWDN;
        }
    }

    if (MADC->LVD_STAT & 0x40) //检测到CMP中断
    {
        MADC->LVD_STAT |= 0x40;

        if (!(MADC->LVD_STAT & 0x04))
        {
            Bkgrd.PubData.Active = BKGRD_ACTIVE_POWDN;
        }
    }

    MADC->LVD_STAT = 0x01ff;
}

//ISO78161_HANDLER与SPI2共用中断向量
void ISO78161_HANDLER(void)
{
    //#if 0
    if (ISO7816->STA1 & 0x1000)  //接收到OLD信号
    {
        ISO7816->STA1 |= 0x1000;
    }
    else if (ISO7816->STA1 & 0x2000) // 检测到卡拔出
    {
        ISO7816->STA1 |= 0x2000;
    }
    //#endif

    u32 status;
    u32 dmastatus;

    dmastatus = SPI2->DMA_FLG;
    status = SPI2->STA;

    if (dmastatus)
    {
        if (dmastatus & 0x02)
        {
            DISABLE_ExModule();
            //SPI0->DMA_FLAG = 0x01;
            //SPI0->STA = 0x01 ;
        }

        SPI2->DMA_FLG = dmastatus;
    }
    //  SPI2->DMA_FLG = dmastatus;
    SPI2->STA = status;
}

void KBI_HANDLER(void)
{
    u32  kbi_data;

    kbi_data = KBI->DATA;

    Inactive.InactiveFlag.fChange |= 0x08;
    if (kbi_data & 0x08)
    {
        // 下降沿
        if (KBI->SEL & 0x08)
        {
            Key.Press |= 0X0100;              //记录开盖记录用
            Key.Release &= 0XFEFF;
        }
        // 上升沿
        else
        {
            Key.Release |= 0X0100;      //记录合盖记录用
            Key.Press &= 0XFEFF;
        }
    }

    KBI->DATA = kbi_data;
}

void RTC_HANDLER(void)
{
    u32 rtcIf;

    rtcIf = RTC->IF;

    if (Inactive.PubData.ActiveState == Running_State)
    {
        fnSysDateTimes(&SysDatetimes);
    }
    Inactive.InactiveFlag.fChange |= 0x02;

    RTC->IF = rtcIf;
}

void HardFault_Handler(void)
{
    WDT->EN = 0xbc;
}
