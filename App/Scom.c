
#define  _SCOM_GLOBALS
#include <App.h>

/*********************************************************************
* @fn      fnDl698DL_AddrGet
*
* @brief
*
******************************************************************/
void fnComAddrGet(u8 *pAddr)
{
    if ((fnCrc_Check(1, (u8 *)&CommPara, FileLen_ParaCom - 2, (u8 *)&CommPara.Crc)) ||
        (fnBCD_Check(&CommPara.ComAddr[0], 6) == false))
    {
        fnFile_Read(FileId_ParaCom, FileItemInfoOffAddr_ComPara_ComAddr, &CommPara.ComAddr[0], FileLen_ParaCom);

        if (fnBCD_Check(&CommPara.ComAddr[0], 6) == false)
        {
            Std_Memcpy((u8 *)&CommPara.ComAddr[0], (u8 *)&ComParaDefault, 6);
        }
    }

    Std_Memcpy(pAddr, &CommPara.ComAddr[0], 6);
}

void fnScom_ReadBps(void)
{
    if (fnCrc_Check(1, (u8 *)&CommPara, FileLen_ParaCom - 2, (u8 *)&CommPara.Crc))
    {
        fnFile_Read(FileId_ParaCom, 0, (u8 *)&CommPara, FileLen_ParaCom);
        if (fnCrc_Check(1, (u8 *)&CommPara, FileLen_ParaCom - 2, (u8 *)&CommPara.Crc))
        {
            Std_Memcpy((u8 *)&CommPara, (u8 *)&ComParaDefault, FileLen_ParaCom);
        }
    }
    ComPack[SCOM_PORT_RS485A].NewBps =  CommPara.Com1Style;
    //ComPack[SCOM_PORT_ZBCOM].NewBps = CommPara.Com3Style; // dyf del
    //ComPack[SCOM_PORT_IR].NewBps = CommPara.Ir1Style;     // dyf del
    #if(SCOM_PORT_MAX == 4)
    ComPack[SCOM_PORT_RS485B].NewBps =  CommPara.Com2Style;
    #endif
}

const u8 eUsartBps_Def[11] = {USART_BPS_300, USART_BPS_600, USART_BPS_1200, USART_BPS_2400, USART_BPS_4800,
                              USART_BPS_7200, USART_BPS_9600, USART_BPS_19200, USART_BPS_38400, USART_BPS_57600, USART_BPS_115200
                             };

void fnScomUart_Init(u8 ComPort)
{
    //u8 USART_BPS;
    uUART_DMAPara_TypeDef   uart_dma;

    //if(ComPack[ComPort].NewBps < 11)
    //  USART_BPS=eUsartBps_Def[ComPack[ComPort].NewBps];
    //else
    //  USART_BPS=eUsartBps_Def[10];

    //复位698状态机状态
    pDl698DL_Channel[ComPort].stRxBuf.usIndex = 0;
    pDl698DL_Channel[ComPort].stScom.ucComflag = DL698_SCOMPK_EFLAG_IDLE;

    //初始化Spi外设和Dma
    memset(&uart_dma, 0, sizeof(uUART_DMAPara_TypeDef));
    uart_dma.TBADR = (u16)((u32)(pDl698DL_Channel[ComPort].stTxBuf.pData));
    uart_dma.RBADR = (u16)((u32)(pDl698DL_Channel[ComPort].stRxBuf.pData));
    uart_dma.RLEN = (u16)gDl698AL_Server.pAlChan[ComPort].nego.apdu_size_rx_nego + 50;
    uart_dma.TLEN = (u16)gDl698AL_Server.pAlChan[ComPort].nego.apdu_size_tx_nego;
    uart_dma.CTL.UART_DMACtl_TX_DMA_EN = 0;
    uart_dma.CTL.UART_DMACtl_RX_DMA_EN = 1;
    uart_dma.CTL.UART_DMACtl_TX_CYC_MODE = 0;
    uart_dma.CTL.UART_DMACtl_RX_CYC_MODE = 0;
    //uart_dma.IE = 0x08;//接收全满标志
    uart_dma.IE = UART_DMA_RX_FIE;
    BSP_Uart_DMAInit(ComPort, uart_dma);
    BSP_Uart_Init(ComPort, USART_BPS_115200); //USART_BPS
    //SystemDelayUs(20000);
}

void fnScomSpi_Init(u8 ComPort)
{
    u8 SpiId;
    uSPI_DMAPara_TypeDef   spi_DmaPara;

    //复位698状态机状态
    pDl698DL_Channel[ComPort].stRxBuf.usIndex = 0;
    pDl698DL_Channel[ComPort].stScom.ucComflag = DL698_SCOMPK_EFLAG_IDLE;

    //初始化Spi外设和Dma
    SpiId = BSP_SpiId_Get(SCOM_PORT_SPI);
    memset(&spi_DmaPara, 0, sizeof(uSPI_DMAPara_TypeDef));
    spi_DmaPara.TbAdr = (u16)((u32)(pDl698DL_Channel[ComPort].stTxBuf.pData));
    spi_DmaPara.RbAdr = (u16)((u32)(pDl698DL_Channel[ComPort].stRxBuf.pData));
    spi_DmaPara.RLen = (u16)gDl698AL_Server.pAlChan[ComPort].nego.apdu_size_rx_nego;
    spi_DmaPara.TLen = (u16)gDl698AL_Server.pAlChan[ComPort].nego.apdu_size_tx_nego;
    spi_DmaPara.DmaCtl.SPI_DMACtl_TX_DMA_EN = 0;
    spi_DmaPara.DmaCtl.SPI_DMACtl_RX_DMA_EN = 1;
    spi_DmaPara.DmaCtl.SPI_DMACtl_TX_CYC_MODE = 0;
    spi_DmaPara.DmaCtl.SPI_DMACtl_RX_CYC_MODE = 0;
    //spi_DmaPara.DmaIE = SPI_DMA_RX_FIE; //接收全满中断
    Rn8xxx_Spi_DMAInit(SpiId, spi_DmaPara);
}

void fnScomPk_Init(u8 ComPort)  //端口初始化
{
    // u8 USART_BPS;
    FIFOMailBox_CFG_TypeDef fifo_cfg;

    if (ComPort >= SCOM_PORT_MAX)
    {
        return;
    }

    fifo_cfg.TxBuffer = pDl698DL_Channel[ComPort].stTxBuf.pData;
    fifo_cfg.RxBuffer = pDl698DL_Channel[ComPort].stRxBuf.pData;
    fifo_cfg.RxBufferSize = gDl698AL_Server.pAlChan[ComPort].nego.apdu_size_rx_nego + 50;
    fifo_cfg.TxBufferSize = gDl698AL_Server.pAlChan[ComPort].nego.apdu_size_tx_nego;
    FIFO_Init(ComPort, fifo_cfg);

    ComPack[ComPort].EFlag = 0;
    ComPack[ComPort].RxLen = 0;
    ComPack[ComPort].TxLen = 0;
    ComPack[ComPort].TimeOutStamp = 0;

    if (ComPort == SCOM_PORT_RS485A)
    {
        fnScomUart_Init(ComPort);
    }
    else if (ComPort == SCOM_PORT_SPI)
    {
        BSP_ManageModuleSpi_Init(BSP_SpiId_Get(ComPort), 4000000);
        fnScomSpi_Init(ComPort);
    }
}

void fnScomPk_ChangeBps(u8 ComPort)
{
    if (ComPack[ComPort].fBps == 0)
    {
        return;
    }
    fnScomPk_Init(ComPort);
    ComPack[ComPort].NewBpsStamp = 0;
    ComPack[ComPort].fBps = 0;
}

/*********************************************************************************************************
** Function name:
** Descriptions:        启动发送
** input parameters:    fifo_Id :  板基层通讯对象;
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void fnScomStartSend(u8 fifo_Id, u16 txlen, u8*TxBuffer)
{
    u8 UartId, SpiId;
    FIFOMailBox_TypeDef *fifoPort = &FIFOMailBox[fifo_Id];
    uUART_DMAPara_TypeDef uartdmaPara;
    uSPI_DMAPara_TypeDef spidmapara;

    if (fifo_Id >= SCOM_PORT_MAX)
    {
        return;
    }

    if (txlen > 0)
    {
        if (fifo_Id == SCOM_PORT_RS485A)
        {
            UartId = BSP_UartId_Get(fifo_Id);
            fifoPort->TxBuffer = TxBuffer;
            Rn8xxx_Uart_SttConfig(UartId, USART_IT_RX, ENABLE); //禁止接收
            Rn8xxx_Uart_SttConfig(UartId, USART_IT_TX, ENABLE); //发送使能
            //uart_write(UartId, fifoPort->TxBuffer[0]);//调用串口驱动，启动发送
            memset(&uartdmaPara, 0, sizeof(uartdmaPara));
            uartdmaPara.TBADR = ((u32)TxBuffer) & 0x0001FFFF;
            uartdmaPara.TLEN = (u32)txlen;
            uartdmaPara.IE = UART_DMA_TX_FIE;
            uartdmaPara.CTL.UART_DMACtl_TX_DMA_EN = 1;
            Rn8xxx_UART_DMAInit(UartId, uartdmaPara);
        }
        else if (fifo_Id == SCOM_PORT_SPI)
        {
            SpiId = BSP_SpiId_Get(fifo_Id);
            memset(&spidmapara, 0, sizeof(spidmapara));
            pDl698DL_Channel[fifo_Id].stTxBuf.pData[0] = 0x5A;
            pDl698DL_Channel[fifo_Id].stTxBuf.pData[1] = ((txlen - 3) >> 8) & 0xFF;
            pDl698DL_Channel[fifo_Id].stTxBuf.pData[2] = (txlen - 3) & 0xFF;
            spidmapara.TbAdr = ((u32)TxBuffer) & 0x0001FFFF;
            spidmapara.TLen = (u32)txlen;
            //spidmapara.DmaIE = SPI_DMA_TX_FIE;
            spidmapara.DmaCtl.SPI_DMACtl_TX_DMA_EN = 1;
            Rn8xxx_Spi_DMAInit(SpiId, spidmapara);
        }
    }
}

/*********************************************************************************************************
** Function name:
** Descriptions:        更新FIFO接收状态到SCOM
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
ErrorStatus scom_update_info(u8 ComPort)
{
    u16 Rxlen = 0; /*接收缓冲区中的接收字节数； */
    eUART_ID_TypeDef uart_id;
    eSPI_ID_TypeDef spi_id;
    u8 dmaEnOrDis;

    if (ComPort == SCOM_PORT_RS485A)
    {
        BSP_UartId_DMAEnOrDis_Get(ComPort, &uart_id, &dmaEnOrDis);
        if (dmaEnOrDis == UART_DMA_EN) //DMA使能
        {
            Rxlen = Rn8xxx_Uart_DMA_RxInfo(uart_id);
        }
        else
        {
            Rxlen = FIFO_Info(ComPort);
        }
    }
    else if (ComPort == SCOM_PORT_SPI)
    {
        BSP_SpiId_DMAEnOrDis_Get(ComPort, &spi_id, &dmaEnOrDis);
        if (dmaEnOrDis == SPI_DMA_EN) //DMA使能
        {
            Rxlen = (u16)Rn8xxx_Spi_DMA_RxInfo(spi_id);
        }
        else
        {
            Rxlen = FIFO_Info(ComPort);
        }
    }

    if ((pDl698DL_Channel[ComPort].stRxBuf.usIndex != Rxlen) && (Rxlen))
    {
        pDl698DL_Channel[ComPort].stRxBuf.usIndex = Rxlen;
        pDl698DL_Channel[ComPort].stScom.ucToStamp2 = SysStamp ? SysStamp : (SysStamp - 1);
        return SUCCESS;
    }

    return ERROR;
}

/*********************************************************************************************************
** Function name:     fnPt_Check
** Descriptions:       接收帧协议判断
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
ePtType_TypeDef Scom_ProtocolCheck(u8 ComPort, u8 *Src, u16 Len, u16* Pointer, u16 *usDataLen)
{
    u16 i;
    ErrorStatus tmpbool;
    ePtType_TypeDef PtType;

    PtType = PTTYEP_NONE;

    for (i = 0 ; i < Len ; i++)
    {
        // DL645-07规约判断
        tmpbool = fnDl645B_FrameCheck((sFrmDl645B_TypeDef *) Src, usDataLen);
        if (tmpbool == SUCCESS)
        {
            if (Len < ((*(sFrmDl645B_TypeDef *)Src).Len + 12))
            {
                PtType = PTTYEP_NONE;
            }
            else
            {
                PtType = PTTYEP_DL645;
                ComPack[ComPort].RTxBuf = Src;
                ComPack[ComPort].RxLen  = *usDataLen;
                ComPack[ComPort].EFlag = SCOMPK_EFLAG_RXFINISH;
            }
            break;
        }

        // DL698-45规约判断
        tmpbool = Dl698_FrameCheck(ComPort, Src, Len - i, usDataLen);
        if (tmpbool == SUCCESS)
        {
            PtType = PTTYEP_DL698;
            break;
        }

        Src++;
    }

    *Pointer = i;
    return (PtType);
}

/*********************************************************************************************************
** Function name:   fnDl645_Process
** Descriptions:       645通讯主函数
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void fnDl645_Process(u8 ComPort)
{
    u16         Len = 0;

    if (ComPack[ComPort].EFlag == SCOMPK_EFLAG_RXFINISH) //包接收完，规约处理，是否需要发送
    {
        if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
        {
            fnPowerDown_SetWakeOpIO();
        }
        Len = fnPt_Exec(ComPort);
        if (Len)
        {
            ComPack[ComPort].TxLen = Len;

            Std_Memset(ComPack[ComPort].pTx, DL645B_LEADERCODE, DL645B_LEADERCODE_LEN);

            ComPack[ComPort].TxLen += DL645B_LEADERCODE_LEN;
            BSP_TxEnDis(ComPort, ENABLE);

            Std_Memset(ComPack[ComPort].RTxBuf, 0x00, ComPack[ComPort].RxLen);   //清除上一帧接收信息

            ComPack[ComPort].EFlag = SCOMPK_EFLAG_TXBUSY;
            ComPack[ComPort].TimeOutStamp = SysStamp ? SysStamp : (SysStamp - 1);

            eUART_ID_TypeDef uart_id;
            u8 uart_dmaEnOrDis;

            BSP_UartId_DMAEnOrDis_Get(ComPort, &uart_id, &uart_dmaEnOrDis);

            if (uart_dmaEnOrDis == UART_DMA_EN)   //DMA使能
            {
                fnScomStartSend(ComPort, ComPack[ComPort].TxLen, ComPack[ComPort].pTx);
            }
            else
            {
                FIFO_StartSend(ComPort, ComPack[ComPort].TxLen, ComPack[ComPort].pTx);
            }
        }
        else
        {
            ComPack[ComPort].EFlag = SCOMPK_EFLAG_INIT;
        }
        if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
        {
            fnPowerDown_SleepWakeOpIO();
        }
    }

    if (ComPack[ComPort].EFlag == SCOMPK_EFLAG_TXBUSY) //发送超时处理
    {
        if (fnStamp_Through(ComPack[ComPort].TimeOutStamp) > (OS_TICKS_PER_SEC * 3))
        {
            ComPack[ComPort].EFlag = SCOMPK_EFLAG_TXFINISH;
        }
    }
}

/*********************************************************************************************************
** Function name:     fnScomPk_Exec
** Descriptions:        通讯模块执行主函数
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/

void fnScomPk_Exec(void)  //通讯包执行--
{
    u8   ComPort;
    u16 Pointer;
    ErrorStatus tmpbool; //0-error,1-success

    sDl698DL_ChannelInfo_TypeDef *pChan = NULL;

    for (ComPort = 0; ComPort < CHANNEL_NUM; ComPort++)
    {
        fnDl698Scom_TimeOutCheck(ComPort);

        pChan = &pDl698DL_Channel[ComPort];

        Pointer = 0;
        tmpbool = scom_update_info(ComPort);

        if (pChan->stScom.ucComflag == DL698_SCOMPK_EFLAG_IDLE)
        {
            if (tmpbool == SUCCESS) //接收到新的字节,DMA
            {
                pChan->stScom.ucComflag = DL698_SCOMPK_EFLAG_RXBUSY;
                ComPack[ComPort].EFlag = SCOMPK_EFLAG_RXBUSY;
            }
        }

        if ((pChan->stScom.ucComflag == DL698_SCOMPK_EFLAG_RXBUSY) && (ComPack[ComPort].EFlag == SCOMPK_EFLAG_RXBUSY))
        {
            if (tmpbool == SUCCESS) //接收到新的字节
            {
                pChan->stScom.ucPktType = Scom_ProtocolCheck(ComPort, pChan->stRxBuf.pData, pChan->stRxBuf.usIndex, &Pointer, &pChan->stRxBuf.usDataLen);
            }
            //else
            //{
            //  pChan->stScom.ucPktType= Scom_ProtocolCheck(ComPort , pChan->stRxBuf.pData , gDl698AL_Server.pAlChan[ComPort].nego.apdu_size_rx_nego , &Pointer , &pChan->stRxBuf.usDataLen );

            //}
        }

        if ((pChan->stScom.ucPktType == PTTYEP_DL698)
            && (pChan->stScom.ucComflag == DL698_SCOMPK_EFLAG_RXEND))
        {
            if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
            {
                fnPowerDown_SetWakeOpIO();
                USART_ITConfig(ComPort, USART_IT_RX, DISABLE);
            }

            fnWDT_Restart();

            fnDl698_Process(ComPort);

            fnWDT_Restart();

            if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
            {
                fnPowerDown_SleepWakeOpIO();
            }
        }
        else if (pChan->stScom.ucPktType == PTTYEP_DL645)
        {
            fnWDT_Restart();
            fnDl645_Process(ComPort);

            if (ComPack[ComPort].EFlag == SCOMPK_EFLAG_TXBUSY)
            {
                pChan->stScom.ucToStamp2 = ComPack[ComPort].TimeOutStamp;
            }
        }
        else
        {
            if ((pChan->stScom.ucComflag == DL698_SCOMPK_EFLAG_IDLE) && (ComPack[ComPort].EFlag == SCOMPK_EFLAG_IDLE))
            {
                fnWDT_Restart();
                fnReport_Process(ComPort); //主动上报
            }
        }

        if ((ComPack[ComPort].EFlag == SCOMPK_EFLAG_TXFINISH) ||
            (pChan->stScom.ucComflag == DL698_SCOMPK_EFLAG_TXFINISH))      //发送完成
        {
            ComPack[ComPort].EFlag = SCOMPK_EFLAG_INIT;
            pChan->stScom.ucComflag = DL698_SCOMPK_EFLAG_INIT;

            BSP_TxEnDis(ComPort, DISABLE);
            USART_ITConfig(ComPort, USART_IT_TX, DISABLE);          //禁止发送
        }

        if ((ComPack[ComPort].EFlag == SCOMPK_EFLAG_INIT) ||
            (pChan->stScom.ucComflag == DL698_SCOMPK_EFLAG_INIT))     //端口恢复
        {
            fnDl698_memset((u8*)&pDl698DL_Channel[ComPort].stRxBuf, 0x00, sizeof(sDl698DL_RxBuf_TypeDef)); //接收数据清零

            fnScomPk_ChangeBps(ComPort);
            fnScomPk_Init(ComPort);

            ComPack[ComPort].EFlag = SCOMPK_EFLAG_IDLE;

            pChan->stScom.ucComflag = DL698_SCOMPK_EFLAG_IDLE;
        }
    }
}

u16 fnPt_Exec(u8 ComPort)  //协议执行
{
    //u8                temp1,temp0;

    u16             Len;

    if (ComPort == SCOM_PORT_RS485A)
    {
        Bkgrd.PubData.CommStatus |= F_Comm1Event;
    }

    if (ComPort == SCOM_PORT_RS485B)
    {
        Bkgrd.PubData.CommStatus |= F_Comm2Event;
    }
    if (ComPort == SCOM_PORT_ZBCOM)
    {
        Bkgrd.PubData.CommStatus |= F_Comm4Event;
    }

    Len = fnDl645B_Exec(ComPort, (sFrmDl645B_TypeDef *)ComPack[ComPort].RTxBuf);    //07规约处理

    return (Len);
}
