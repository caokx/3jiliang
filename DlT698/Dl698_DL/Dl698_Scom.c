/**************************************************************************************************
  Filename:       Dl698_Scom.c
  Revised:        $Date: 2017-05-23 $
  Revision:       $Revision: V0.1 $
  Author:         lin.xiaoman

  Description:    .
**************************************************************************************************/
/*********************************************************************
 * INCLUDES
 */
#ifdef _WIN32
#include "serial.h"
#else
//#include <Drive_Lib.h>
#include <BSP.h>
#include "Scom.h"
#endif
#include "Dl698_Globals.h"

/*********************************************************************
* GLOBAL VARIABLES
*/
#ifdef _WIN32
u16 SysStamp = 0;
#else
extern sComPack_TypeDef ComPack[SCOM_PORT_MAX];
extern ErrorStatus fnDl645_AddrCheck(u8 *ComAddr);
#endif
/*********************************************************************
 * PUBLIC FUNCTIONS
 */
/*********************************************************************
* @fn      fnDl698Scom_TimeOutCheck
*
* @brief
*
* @param
*
* @return  s8.
*/
void fnDl698Scom_TimeOutCheck(u8 chanId)
{
    sDl698DL_ScomCtrl_TypeDef *pScom = &pDl698DL_Channel[chanId].stScom;
    //uUART_DMAPara_TypeDef  uart_dma;

    if (pScom->ucComflag == DL698_SCOMPK_EFLAG_IDLE)
    {
        //帧间隔超时处理
        if (chanId == SCOM_PORT_RS485A)
        {
            //检测接收使能和DMA是否开启，如果未开启，检测超时，重新初始化
            //if(BSP_UartCtrlandDmaRxCheck(chanId)==ERROR)
            {
                //if(fnStamp_Through(pScom->ucToStamp) > pScom->ucTimeout)
                if (fnStamp_Through(pScom->ucToStamp) > 8000)
                {
                    UART0->CTRL = 0;
                    fnScomPk_Init(chanId);
                    pScom->ucToStamp = SysStamp ? SysStamp : (SysStamp - 1);
                }
            }
        }
        else if (chanId == SCOM_PORT_SPI)
        {
            //检测接收使能和DMA是否开启，如果未开启，检测超时，重新初始化
            if (BSP_SpiCtrlandDmaRxCheck(chanId) == ERROR)
            {
                if (0)//fnStamp_Through(pScom->ucToStamp) > pScom->ucTimeout) // dyf test
                {
                    fnScomPk_Init(chanId);
                    pScom->ucToStamp = SysStamp ? SysStamp : (SysStamp - 1);
                }
            }
        }
    }
    else if (pScom->ucComflag < DL698_SCOMPK_EFLAG_RXEND)
    {
        //帧内超时处理
        if (fnStamp_Through(pScom->ucToStamp2) > 1500) //500ms
        {
            /*
            pScom->ucComflag = DL698_SCOMPK_EFLAG_IDLE;
            pScom->ucToStamp = 0;
            pScom->ucToStamp2 = 0;
            Std_Memset((u8*)&pDl698DL_Channel[chanId].stRxBuf , 0x00,sizeof(sDl698DL_RxBuf_TypeDef)); //接收数据清零
            fifo_ClearBuffer(chanId);
            */

            if (chanId == SCOM_PORT_RS485A)
            {
                //fnScomUart_Init(chanId);
                fnScomPk_Init(chanId);
            }
            else if (chanId == SCOM_PORT_SPI)
            {
                fnScomSpi_Init(chanId);
                BSP_ManageModuleSpi_Init(BSP_SpiId_Get(chanId), 4000000);
            }
        }
    }
    else if (pScom->ucComflag >= DL698_SCOMPK_EFLAG_RXEND)
    {
        //发送超时检测
        if (fnStamp_Through(pScom->ucToStamp2) > 8000) //8s
        {
            pScom->ucComflag = DL698_SCOMPK_EFLAG_IDLE;
            pScom->ucToStamp = 0;
            pScom->ucToStamp2 = 0;
            Std_Memset((u8*)&pDl698DL_Channel[chanId].stRxBuf, 0x00, sizeof(sDl698DL_RxBuf_TypeDef)); //接收数据清零
            fnScomPk_Init(chanId);
            //USART_ITConfig(chanId , USART_IT_RX, ENABLE);
            //USART_ITConfig(chanId , USART_IT_TX, DISABLE);
        }
    }

    return;
}

/*********************************************************************
* @fn      fnDl698Scom_Tx
*
* @brief
*
* @param
*
* @return  s8.
*/
void fnDl698Scom_Tx(u8 chanId)
{
    sDl698DL_ChannelInfo_TypeDef *pChan = &pDl698DL_Channel[chanId];
    eUART_ID_TypeDef uart_id;
    u8 uart_dmaEnOrDis;
    u16 len;

    pChan->stScom.ucPktType = PTTYEP_DL698;
    pChan->stScom.ucComflag = DL698_SCOMPK_EFLAG_TXBUSY;

    BSP_TxEnDis(chanId, ENABLE);

    ComPack[chanId].pTx = pDl698DL_Channel[chanId].stTxBuf.pData;
    ComPack[chanId].TxLen = pDl698DL_Channel[chanId].stTxBuf.usDataLen;

    //-------清除接收信息----------
    fifo_ClearBuffer(chanId);
    if (pDl698DL_Channel[chanId].stRxBuf.usDataLen < 12)
    {
        len = 12;
    }
    else
    {
        len = pDl698DL_Channel[chanId].stRxBuf.usDataLen;
    }
    Std_Memset(&pDl698DL_Channel[chanId].stRxBuf.pData[0], 0x00, len);

    //-------------------------
    BSP_UartId_DMAEnOrDis_Get(chanId, &uart_id, &uart_dmaEnOrDis);

    if (uart_dmaEnOrDis == UART_DMA_EN)   //DMA使能
    {
        fnScomStartSend(chanId, pDl698DL_Channel[chanId].stTxBuf.usDataLen, pDl698DL_Channel[chanId].stTxBuf.pData);
    }
    else
    {
        FIFO_StartSend(chanId, pDl698DL_Channel[chanId].stTxBuf.usDataLen, pDl698DL_Channel[chanId].stTxBuf.pData);
    }
    pChan->stScom.ucToStamp = SysStamp ? SysStamp : (SysStamp - 1);
    pChan->stScom.ucToStamp2 = SysStamp ? SysStamp : (SysStamp - 1);

    return;
}
