/**************************************************************************************************
  Filename:       Dl698_DL.c
  Revised:        $Date: 2017-05-17 $
  Revision:       $Revision: V0.1 $
  Author:         lin.xiaoman

  Description:    DLT698 stack data link layer main function file.
**************************************************************************************************/
/*********************************************************************
 * INCLUDES
 */
#include "Dl698_Scom.h"
#include "Dl698_Crc.h"
#include "Dl698_Memory.h"
#include "Dl698_Globals.h"
#include "Dl698AL_Conn.h"
#include "Dl698_UserData.h"
#include <BSP.h>
#include "Dl698AL_Report.h"
#ifdef _WIN32
#else
//#include <Drive_Lib.h>
#include <BSP.h>
#include "Scom.h"
#endif
/*********************************************************************
* GLOBAL VARIABLES
*/
extern sComPack_TypeDef ComPack[SCOM_PORT_MAX];

/*===DL698=====*/
//#define CHANNEL_NUM 1

sServerAddr_TypeDef gSa = {0};
#define SR_ADDR_LEN 0x06
#define SR_ADDR_LOG 0x00
#define SR_ADDR_TYPE DL698DL_SERVER_ADDR_TYPE_UNICAST
u8 SrAddr[6];

/*winsize ,max apdu size, dl_rx_size,dl_tx_size, pSrAddr*/
sDl698AL_UserCfg_TypeDef gUserCfg[] =
{
    {1, DL698AL_APTU_MAXSIZE_485A, DL698AL_DL_SIZE_TX_485A, DL698AL_DL_SIZE_RX_485A, &gSa},  /* channel 0 for 485A */
    {1, DL698AL_APTU_MAXSIZE_SPI,   DL698AL_DL_SIZE_TX_SPI,   DL698AL_DL_SIZE_RX_SPI,   &gSa},  /* channel 1 for IR */
    {1, DL698AL_APTU_MAXSIZE_PLC,  DL698AL_DL_SIZE_TX_PLC,  DL698AL_DL_SIZE_RX_PLC,  &gSa},  /* channel 2 for ZBCOM */
    {1, DL698AL_APTU_MAXSIZE_485B, DL698AL_DL_SIZE_TX_485B, DL698AL_DL_SIZE_RX_485B, &gSa}   /* channel 3 for 485B */
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */
#ifdef DL698_DEBUG
void fnDl698_debug_buf(u8 *buf, u32 len, u8 type)
{
    u32 i = 0;
    if (type == 3)
    {
        fnDl698_debug("0x%02X ", DL698_SCOM_START_FLAG);
    }
    for (i = 0; i < len; i++)
    {
        fnDl698_debug("0x%02X ", buf[i]);
    }
    if (type == 3)
    {
        fnDl698_debug("0x%02X ", DL698_SCOM_END_FLAG);
        len += 2;
    }

    if (type)
    {
        fnDl698_debug("\n============================= length %3d ===============================\n", len);
    }
    return;
}

void fnDl698_debug_rxframe(u8 *pRxbuf, sDl698DL_FrameInfo_TypeDef *pframInfo, u16 hcs, u16 fcs)
{
    u16 seghdr = BUILD_U16(pframInfo->pInfo[0], pframInfo->pInfo[1]);

    fnDl698_debug("============================= Receive a pkt =============================\n");
    fnDl698_debug_buf(pRxbuf, pframInfo->usFrameLen, 3);
    fnDl698_debug("=============== pkt decode start ===================\n");
    fnDl698_debug("frame len : 0x%x\n", pframInfo->usFrameLen);
    fnDl698_debug("Control   : 0x%x\n", pRxbuf[2]);
    fnDl698_debug("    funCode     : 0x%x\n", pframInfo->ubCode);
    fnDl698_debug("    segment flag: 0x%x\n", pframInfo->ubSegment);
    fnDl698_debug("    dir_prm     : 0x%x\n", pframInfo->ubDirPrm);
    fnDl698_debug("Addr Info : ");
    fnDl698_debug_buf(&pRxbuf[3], pframInfo->stSA.ubLen + 2, 0);
    fnDl698_debug("\n");
    fnDl698_debug("    ServerAddr.len  : 0x%x\n", pframInfo->stSA.ubLen);
    fnDl698_debug("    ServerAddr.logic: 0x%x\n", pframInfo->stSA.ubLogic);
    fnDl698_debug("    ServerAddr.type : 0x%x\n", pframInfo->stSA.ubAddrType);
    fnDl698_debug("    ServerAddr: ");
    fnDl698_debug_buf(&pRxbuf[4], pframInfo->stSA.ubLen + 1, 0);
    fnDl698_debug("\n");
    fnDl698_debug("    ClientAddr: 0x%x\n", pframInfo->ucCA);
    fnDl698_debug("HCS : 0x%x\n", hcs);
    fnDl698_debug("Apdu Info :\n");
    if (pframInfo->ubSegment == 1)
    {
        fnDl698_debug("    segment hdr : 0x%x\n", seghdr);
        fnDl698_debug("        segment number : 0x%x\n", seghdr & 0x0FFF);
        fnDl698_debug("        segment type   : 0x%x\n", seghdr >> 14 & 0x0F);
        fnDl698_debug("    Apdu data :\n");
        //fnDl698_debug_buf(&pframInfo->pInfo[3],pframInfo->usInfoLen - 2,1);
    }
    else
    {
        fnDl698_debug("    segment hdr :None \n");
        fnDl698_debug("    Apdu data   :");
        //fnDl698_debug_buf(pframInfo->pInfo,pframInfo->usInfoLen,0);
    }
    fnDl698_debug("\n");
    fnDl698_debug("FCS : 0x%x\n", fcs);
    fnDl698_debug("=============== pkt decode end ===================\n");
    return;
}
#endif

/*********************************************************************
* @fn      fnDl698DL_Init
*
* @brief   ������·����Դ��ʼ��������uart��ʼ��
*
* @param   channId   ͨ����
*          uart_id   ����ͨ����Ӧ�Ĵ��ں�
*          baud_rate ����ͨ����Ӧ�Ĵ��ڲ�����
*
* @return  void �޷���ֵ
*/
void fnDl698DL_Init(u8 channId)
{
    // sDl698DL_ChannelInfo_TypeDef *pChan=&pDl698DL_Channel[channId];
    sDl698DL_ChannelInfo_TypeDef *pChan = (void *)&pDl698DL_Channel[channId];

    u8   baud_rate, uart_dmaEnOrDis;
    eUART_ID_TypeDef uart_id;

    if (ComPack[channId].NewBps < 11)
    {
        baud_rate = eUsartBps_Def[ComPack[channId].NewBps];
    }
    else
    {
        baud_rate = eUsartBps_Def[10];
    }

    BSP_UartId_DMAEnOrDis_Get(channId, &uart_id, &uart_dmaEnOrDis);    //��ȡchannId��Ӧ��UART

    pChan->stScom.ucUartId = uart_id;

    pChan->stScom.ucComflag = DL698_SCOMPK_EFLAG_IDLE;

    pChan->stAddr.ucCA = DL698DL_DEFAULT_CLIENT_ADDR;
    if (baud_rate != 0) // dyf ���ӷ�����ж�����
    {
        pChan->stScom.ucTimeout = ((DL698_SCOM_DELAY_BIT * 1000 + (baud_rate - 1)) / baud_rate); //ms,����֡�����ʱʱ��
    }
    else
    {
        pChan->stScom.ucTimeout = 255; // dyf Ĭ��֡���ʱ��
    }

    ComPack[channId].UartId = uart_id;
    ComPack[channId].RTxBuf = pChan->stRxBuf.pData;
    ComPack[channId].pTx = pChan->stTxBuf.pData;

    #ifdef _WIN32
    uart_open(uart_id, baud_rate);
    #else
    fnScomPk_Init(channId);
    #endif
    fnDl698_dl_debug("DL698 DL init OK!\n");

    return;
}

/*********************************************************************
* @fn      fnDl698DL_AddrCheck
*
* @brief   ����֡��ַ��ĺϷ��Լ��
*
* @param   id   ͨ����
*          pSA  ָ�����֡Server��ַ������
*          CA   ����֡Client��ַ����
*
* @return  ���ؼ����
*/
s8 fnDl698DL_AddrCheck(u8 id, sServerAddr_TypeDef *pSA, u8 CA)
{
    sDl698DL_ChannelInfo_TypeDef *pChan = &pDl698DL_Channel[id];
    sServerAddr_TypeDef *plocalSa       =  pDl698DL_Channel[id].stAddr.pSA;
    s8 res = SUCCESS;

    if (pSA->ubLogic & 0x02)    // dyf ���Ǵ�һ���ֽ���չ�߼���ַ�����
    {
        plocalSa->pAddr[0] = pSA->pAddr[0];
        fnComAddrGet(plocalSa->pAddr + 1); //��ȡͨѶ��ַ
    }
    else
    {
        fnComAddrGet(plocalSa->pAddr);  //��ȡͨѶ��ַ
    }

    if (/*(pSA->ubLogic != plocalSa->ubLogic)
        ||*/((pSA->ubAddrType != DL698DL_SERVER_ADDR_TYPE_BROADCAST) && (((pSA->ubLogic != 0x02) && (pSA->ubLen + 1 != plocalSa->ubLen))
                     || ((pSA->ubLogic == 0x02) && (pSA->ubLen != plocalSa->ubLen))))) //�㲥��ַ����Ҫ�� ��ַ�����ж� dyf ������չ�߼���ַ
    {
        return DL698DL_ERR_SA_ADDR;
    }
    switch (pSA->ubAddrType)
    {
        case DL698DL_SERVER_ADDR_TYPE_UNICAST:
        {
            if (pSA->ubLogic & 0x02)    // dyf ���Ǵ�һ���ֽ���չ�߼���ַ�����
            {
                if (fnDl698_memcmp(plocalSa->pAddr, pSA->pAddr, plocalSa->ubLen + 1) == false)
                {
                    res = DL698DL_ERR_SA_ADDR;
                }
            }
            else
            {
                if (fnDl698_memcmp(plocalSa->pAddr, pSA->pAddr, plocalSa->ubLen) == false)
                {
                    res = DL698DL_ERR_SA_ADDR;
                }
            }
            break;
        }
        case DL698DL_SERVER_ADDR_TYPE_WILDCARD:
        {
            u8 hi = 0, lo = 0;
            s8 i = 0;
            for (i = (plocalSa->ubLen - 1); i >= 0 ; i--)
            {
                hi = HI_U8(pSA->pAddr[i]);
                lo = LO_U8(pSA->pAddr[i]);
                if (((hi != HI_U8(plocalSa->pAddr[i])) && (hi != 0x0A))
                    || ((lo != LO_U8(plocalSa->pAddr[i])) && (lo != 0x0A)))
                {
                    res = DL698DL_ERR_SA_ADDR;
                    break;
                }
            }
            break;
        }
        case DL698DL_SERVER_ADDR_TYPE_MULTICAST:
        {
            res = DL698DL_ERR_SA_ADDR;
            break;
        }
        case DL698DL_SERVER_ADDR_TYPE_BROADCAST:
        {
            //if(fnDl698_memcmp_wildcard(plocalSa->pAddr, pSA->pAddr, (pSA->ubLen+1),0xAA) == false)
            if (pSA->ubLogic & 0x02)    // dyf ���Ǵ�һ���ֽ���չ�߼���ַ�����
            {
                if (pSA->pAddr[1] != 0xAA)
                {
                    res = DL698DL_ERR_SA_ADDR;
                }
            }
            else
            {
                if (pSA->pAddr[0] != 0xAA)
                {
                    res = DL698DL_ERR_SA_ADDR;
                }
            }
            break;
        }
        default:
        {
            res = DL698DL_ERR_SA_ADDR;
            break;
        }
    }
    if (res == SUCCESS)
    {
        //if(DL698DL_TEST_FLAG(id, DL698DL_STATE_MASK_LINKED))
        //{
        //  if(CA != pChan->stAddr.ucCA)
        //  {
        //      res = DL698DL_ERR_CA_ADDR;
        //  }
        //}
        //else
        //{
        pChan->stAddr.ucCA = CA;
        //  DL698DL_SET_FLAG(id, DL698DL_STATE_MASK_LINKED);
        //}
    }
    return res;
}

/*********************************************************************************************************
** Function name:   Dl698_FrameCheck
** Descriptions:        698֡����
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
ErrorStatus Dl698_FrameCheck(u8 ComPort, u8 *Src, u16 len, u16 *usDataLen)
{
    u8 control, addr_type, addr_len, addr_logic, addr_Server[DL698_FRAME_MAX_ADDRLEN]; // dyf ɾ�� addr_logic_flag
    u8 addr_client;
    u16 frame_len, frame_header_crc, frame_end_crc;

    sDl698DL_ChannelInfo_TypeDef *pChan = &pDl698DL_Channel[ComPort];
    sDl698DL_FrameInfo_TypeDef *pframInfo = &pDl698DL_Channel[ComPort].stRxFrameInfo;
    u8 headlen = 0 ;
    s8  res = SUCCESS;
    sCommSize_TypeDef temp;

    if (*Src == DL698_SCOM_START_FLAG) //�ж�֡ͷ
    {
        frame_len = BUILD_U16((*(Src + 1)), (*(Src + 2))) & DL698_FRAME_LEN_MASK;
        if ((frame_len >= DL698_FRAME_LEN_MIN)
            && (*(Src + 1 + frame_len) == DL698_SCOM_END_FLAG) //�ж�֡β
            && (frame_len + 2 <= len)) //���������Ƿ񹻳��ж�
        {
            control = (*(Src + 3));                 //������
            addr_type = *(Src + 4) >> 6 & 0x03;     //��ַ����
            addr_logic = *(Src + 4) >> 4 & 0x03;    //�߼���ַ
            addr_len = ((*(Src + 4)) & 0x0f);       //�������豸��ַ����

            #if 0 /* dyf ����Ҫ���� addr_logic_flag */

            if (addr_logic == 0x02) //����չ�߼���ַ
            {
                addr_logic_flag = 1;
                //addr_logic += *(Src+5);   // dyf ����
            }
            else if (addr_logic == 0x01) //������о�߼���ַ
            {
                addr_logic_flag = 0;
            }
            else
            {
                addr_logic_flag = 0;
            }

            #endif

            fnDl698_memcpy(addr_Server, (Src + 5), (addr_len + 1)); //�������豸��ַ dyf �޸�
            addr_client = (*(Src + 6 + addr_len));    //�ͻ�����ַ dyf ɾ�� addr_logic_flag
            //todo
            frame_header_crc = BUILD_U16((*(Src + 8 + addr_len)), (*(Src + 7 + addr_len))); //֡ͷУ�� dyf ɾaddr_logic_flag
            frame_end_crc = BUILD_U16((*(Src + frame_len)), (*(Src + frame_len - 1)));; //֡βУ�� dyf ɾaddr_logic_flag

            if (frame_header_crc == fcs16((Src + 1), (6 + addr_len))) //֡ͷУ���ж� dyf ɾ�� addr_logic_flag
            {
                if (frame_end_crc == fcs16((Src + 1), (frame_len - 2))) //֡βУ���ж� dyf ɾ�� addr_logic_flag
                {
                    *usDataLen = frame_len + 2;
                    //����״̬
                    pChan->stScom.ucComflag = DL698_SCOMPK_EFLAG_RXEND;
                    pChan->stScom.ucPktType = PTTYEP_DL698;
                    pChan->stRxBuf.usDataLen = *usDataLen;
                    pChan->stRxBuf.usDataLen--;//ȥ��������������

                    fnDl698_memset(pframInfo, 0, sizeof(sDl698DL_FrameInfo_TypeDef));//�����һ֡�洢��Ϣ
                    //��ȡ��������Ϣ
                    pframInfo->usFrameLen = frame_len;
                    //��ȡ��������Ϣ
                    pframInfo->ubCode   = control & 0x07;
                    pframInfo->ubScramble   = control >> 3 & 0x01;//�洢������Ϣ
                    pframInfo->ubSegment    = control >> 5 & 0x01;
                    pframInfo->ubDirPrm = control >> 6 & 0x03;
                    if ((pframInfo->ubDirPrm != DL698DL_FRAME_TYPE_C2S_REQUEST)//���䷽������ǿͻ�����������
                        && (pframInfo->ubDirPrm != DL698DL_FRAME_TYPE_C2S_RESPONSE))
                    {
                        res = ERROR;
                    }
                    //��ȡ��ַ����Ϣ
                    pframInfo->stSA.ubLen      = addr_len;
                    pframInfo->stSA.ubLogic    = addr_logic;
                    pframInfo->stSA.ubAddrType = addr_type;
                    pframInfo->stSA.pAddr = addr_Server;
                    pframInfo->ucCA = addr_client;

                    //������յ����߼���ַ���ͻ�����ַ
                    pChan->stAddr.pSA->ubLogic = addr_logic;
                    pChan->stAddr.ucCA = addr_client;

                    //��ַ�Ϸ��Լ��
                    res = fnDl698DL_AddrCheck(ComPort, &pframInfo->stSA, pframInfo->ucCA);

                    headlen = pframInfo->stSA.ubLen + 6;
                    pframInfo->usInfoLen = pframInfo->usFrameLen - headlen - 4;
                    if (pframInfo->usInfoLen > DL698DL_RX_INFO_SIZE(ComPort)) //�жϳ����Ƿ�Ϸ�
                    {
                        res = ERROR;
                    }

                    if (res != SUCCESS)
                    {
                        //����֡���Ϸ�
                        fnDl698_memset(Src, 0, headlen + 2);//���������Ϣ����ͷ,2�ֽ�Ч���
                        pChan->stScom.ucComflag = DL698_SCOMPK_EFLAG_IDLE;
                        pChan->stScom.ucPktType = PTTYEP_NONE;

                        return res;
                    }

                    //��ȡ�û���������Ϣ
                    pframInfo->pInfo = Src + 1 + (6 + addr_len) +2; //��·��APDU��ʼ��ַ dyf ɾaddr_logic_flag
                    //fnDl698_memcpy(&pChan->stRxBuf.pData[0] , Src , pframInfo->usFrameLen + 2);

                    gDl698AL_Server.pAlChan[ComPort].dirprm = pframInfo->ubDirPrm;

                    fnConnDataInit(ComPort, pframInfo->ucCA);

                    if (fnReadConnSize(&temp, ComPort, pframInfo->ucCA))
                    {
                        gDl698AL_Server.pAlChan[ComPort].nego.apdu_size_deal = temp.apdu_size;
                        gDl698AL_Server.pAlChan[ComPort].nego.apdu_size_rx_nego = temp.dl_size_rx;
                        gDl698AL_Server.pAlChan[ComPort].nego.apdu_size_tx_nego = temp.dl_size_tx;
                        gDl698AL_Server.pAlChan[ComPort].nego.apdu_window_size_rx = temp.apdu_window_size_rx;
                    }

                    fnDl698_memset(Src, 0, headlen + 2);//���������Ϣ����ͷ,2�ֽ�Ч���

                    //pChan->stScom.ucToStamp2 = SysStamp ? SysStamp :(SysStamp - 1);

                    return SUCCESS;
                }
            }
        }
    }
    return ERROR;
}

/*********************************************************************
* @fn      fnDl698DL_DecodePkt
*
* @brief   ����֡���ֶεĽ������Ϸ��Լ��
*
* @param   id   ͨ����
*
* @return  ����֡�����
*/
/*
s8 fnDl698DL_DecodePkt( u8 id )
{
    sDl698DL_RxBuf_TypeDef *pRxbuf        = &pDl698DL_Channel[id].stRxBuf;
    sDl698DL_FrameInfo_TypeDef *pframInfo = &pDl698DL_Channel[id].stRxFrameInfo;
    u8 res = SUCCESS,headlen = 0,*pData = NULL;
    u16 hcs = 0,fcs = 0,datalen = 0;
    u8 srAddr[16] = {0};
    sCommSize_TypeDef temp;

    fnDl698_memset(pframInfo, 0, sizeof(sDl698DL_FrameInfo_TypeDef));//�����һ֡�洢��Ϣ
    pData = &pRxbuf->pData[1]; //������ʼ��0x68�ļ��
//    datalen = pRxbuf->usDataLen -2;  //��ȥ֡ͷ֡β

    //��ȡ��������Ϣ
        pframInfo->usFrameLen = BUILD_U16(pData[0], pData[1]);
    datalen = pframInfo->usFrameLen;
    //FCSУ��Ϸ��Լ��
    fcs = BUILD_U16(pData[datalen - 1],pData[datalen - 2]); //�������ֽ�FCSУ��
    if(fcs != fcs16(&pRxbuf->pData[1],(datalen - 2)))
    {
#if DL_WITHOUT_CHECK
#else
     //   fnDl698_dl_debug("fcs = 0x%x, fcs16 = 0x%x \n",fcs,fcs16(pRxbuf->pData,(datalen - 2)));
        return DL698DL_ERR_FCS;
#endif
    }
    pData += 2;

    //��ȡ��������Ϣ
    pframInfo->ubCode     = *pData & 0x07;
    pframInfo->ubScramble = *pData >> 3 & 0x01;//�洢������Ϣ
    pframInfo->ubSegment  = *pData >> 5 & 0x01;
    pframInfo->ubDirPrm   = *pData++ >> 6 & 0x03;

    if(( pframInfo->ubDirPrm != DL698DL_FRAME_TYPE_C2S_REQUEST)
        &&( pframInfo->ubDirPrm != DL698DL_FRAME_TYPE_C2S_RESPONSE))
    {
#if DL_WITHOUT_CHECK
#else
        return DL698DL_ERR_DIR_PRM;
#endif
    }

    if( pframInfo->ubCode != DL698DL_FUNCODE_TYPE_DATAEXG )
         return DL698DL_ERR_DIR_PRM;

    //��ȡ��ַ����Ϣ
      pframInfo->stSA.ubLen      = *pData & 0x0F;
    pframInfo->stSA.ubLogic    = *pData >> 4 & 0x03;
    pframInfo->stSA.ubAddrType = *pData++ >> 6 & 0x03;
    pframInfo->stSA.pAddr = srAddr;//fnDl698_mem_alloc(pframInfo->stSA.ubLen +1);
    Std_Memcpy(pframInfo->stSA.pAddr , pData , pframInfo->stSA.ubLen+1);
    pData += (pframInfo->stSA.ubLen+1);
    pframInfo->ucCA= *pData++;

    //��ַ�Ϸ��Լ��
#if DL_WITHOUT_CHECK
#else
    res = fnDl698DL_AddrCheck(id, &pframInfo->stSA, pframInfo->ucCA);
#endif
    //fnDl698_mem_free(pframInfo->stSA.pAddr);
    if(res != SUCCESS)
    {
        return res;
    }
    //HCSУ��Ϸ��Լ��
    headlen = pframInfo->stSA.ubLen + 6;

    hcs = BUILD_U16(pData[1], pData[0]);
    pData += 2;

    if(hcs != fcs16(&pRxbuf->pData[1],headlen))
    {
#if DL_WITHOUT_CHECK
#else
      //  fnDl698_dl_debug("hcs = 0x%x,fcs16 = 0x%x \n",hcs,fcs16(pRxbuf->pData,headlen));
        return DL698DL_ERR_HCS;
#endif
    }

    fnConnDataInit(id , pframInfo->ucCA);

    if(fnReadConnSize(&temp , id , pframInfo->ucCA ))
    {
        gDl698AL_Server.pAlChan[id].nego.apdu_size_deal = temp.apdu_size;
        gDl698AL_Server.pAlChan[id].nego.apdu_size_rx_nego = temp.dl_size_rx;
        gDl698AL_Server.pAlChan[id].nego.apdu_size_tx_nego = temp.dl_size_tx;
        gDl698AL_Server.pAlChan[id].nego.apdu_window_size_rx = temp.apdu_window_size_rx;
    }

    gDl698AL_Server.pAlChan[id].dirprm = pframInfo->ubDirPrm;

    pframInfo->usInfoLen = pframInfo->usFrameLen - headlen - 4;

    fnDl698_memset(pRxbuf, 0, headlen + 2);//���������Ϣ����ͷ,2�ֽ�Ч���

    if(pframInfo->usInfoLen > DL698DL_RX_INFO_SIZE(id))
    {
        return DL698DL_RX_ERR_INFO_FIELD_SIZE;
    }
    //��ȡ�û���������Ϣ
    pframInfo->pInfo = pData;
#ifdef DL698_DEBUG
    fnDl698_debug_rxframe(pRxbuf->pData, pframInfo, hcs, fcs);
#endif
    return SUCCESS;
}
*/
/*********************************************************************
* @fn      fnDl698DL_EncodePkt
*
* @brief   ��·��֡��װ�ӿ�
*
* @param   id        ͨ����
*          control   ��Ҫ��װ�Ŀ���������
*          usInfoLen ��Ҫ��װ���û����������ݳ���
*
* @return  �޷���ֵ
*/
void fnDl698DL_EncodePkt(u8 id, u8 control, u16 usInfoLen)
{
    sDl698DL_TxBuf_TypeDef *pTxbuf      = &pDl698DL_Channel[id].stTxBuf;
    sDl698DL_ChannelInfo_TypeDef *pChan = &pDl698DL_Channel[id];
    sServerAddr_TypeDef *pSa = pChan->stAddr.pSA;
    u16  hcs = 0, fcs = 0, framelen = 0, templen = 0;
    u8 *pBuf = NULL;
    u8 comAddr[8];

    pBuf = pTxbuf->pData;

    Std_Memset(pBuf, DL698_SCOMPK_LEADCODE, DL698_LEADERCODE_LEN);
    pBuf += DL698_LEADERCODE_LEN;
    *pBuf++ = DL698_SCOM_START_FLAG;
    templen = DL698_LEADERCODE_LEN + 1;

    //���㲢��װ������
    framelen = 9 + pSa->ubLen + usInfoLen;

    if (pSa->ubLogic & 0x02)    // dyf ������չ�߼���ַ
    {
        framelen++;
    }

    *pBuf++ = LO_U16(framelen);
    *pBuf++ = HI_U16(framelen);

    //��װ������
    *pBuf++ = control;

    //��װ��ַ��
    if (pSa->ubLogic & 0x02)    // dyf ������չ�߼���ַ
    {
        *pBuf++ = (pSa->ubLen) | pSa->ubLogic << 4 | pSa->ubAddrType << 6;    // dyf �� ubAddrType
        *pBuf++ = pSa->pAddr[0];
    }
    else
    {
        *pBuf++ = (pSa->ubLen - 1) | pSa->ubLogic << 4 | pSa->ubAddrType << 6;  // dyf �� ubAddrType
    }

    fnComAddrGet(&comAddr[0]);  //��ȡͨѶ��ַ
    //Std_Memcpy(pBuf, pSa->pAddr, pSa->ubLen);
    Std_Memcpy(pBuf, &comAddr[0], pSa->ubLen);
    pBuf += pSa->ubLen;
    *pBuf++ = pChan->stAddr.ucCA;
    templen += pSa->ubLen + 5;

    if (pSa->ubLogic & 0x02)    // dyf ������չ�߼���ַ
    {
        templen++;
    }

    //���㲢��װ��װHCS
    hcs = fcs16(&pTxbuf->pData[DL698_LEADERCODE_LEN + 1], templen - (DL698_LEADERCODE_LEN + 1));
    *pBuf++ = HI_U16(hcs);
    *pBuf++ = LO_U16(hcs);
    pBuf += usInfoLen;
    templen += usInfoLen + 2;
    //���㲢��װ��װFCS
    fcs = fcs16(&pTxbuf->pData[DL698_LEADERCODE_LEN + 1], templen - (DL698_LEADERCODE_LEN + 1));
    *pBuf++ = HI_U16(fcs);
    *pBuf++ = LO_U16(fcs);

    //��װ������
    *pBuf++ = DL698_SCOM_END_FLAG;

    pTxbuf->usDataLen = templen + 3;
    pTxbuf->usIndex = pTxbuf->usDataLen;
    return;
}

/*********************************************************************
* @fn      fnDl698DL_Generate_Ack_Frame
*
* @brief   ����ACK֡
*
* @param   id  ͨ����
*
* @return  �޷���ֵ
*/
void fnDl698DL_Generate_Ack_Frame(u8 id)
{
    sDl698DL_FrameInfo_TypeDef *rxframeInfo = &pDl698DL_Channel[id].stRxFrameInfo;
    u16 infoIndex = (DL698_LEADERCODE_LEN + 8 + pDl698DL_Channel[id].stAddr.pSA->ubLen);
    u8 *pInfo = &pDl698DL_Channel[id].stTxBuf.pData[infoIndex];
    sDl698DL_CtrlInfo_TypeDef control = {0};
    u16 infoHdr = 0;
    u8 *pTemp = (u8 *)&control;

    if (pDl698DL_Channel[id].stAddr.pSA->ubLogic & 0x02)    // dyf ������չ�߼���ַ
    {
        infoIndex++;
        pInfo = &pDl698DL_Channel[id].stTxBuf.pData[infoIndex];
    }

    control.ubSegment = 1;
    control.ubCode    = DL698DL_FUNCODE_TYPE_DATAEXG;
    //control.ubDirPrm  = DL698DL_FRAME_TYPE_S2C_RESPONSE;
    //control.ubDirPrm = DL698DL_GET_DIRPRM(id);
    control.ubDirPrm = DL698AL_DIRPRM_SERVRSP;
    control.ubResever = 0;

    infoHdr = BUILD_U16(rxframeInfo->pInfo[0], rxframeInfo->pInfo[1]);
    infoHdr = (infoHdr & 0x3FFF | DL698DL_SEGMEMT_FRAME_TYPE_ACK << 14);

    pInfo[0] = LO_U16(infoHdr);
    pInfo[1] = HI_U16(infoHdr);

    fnDl698DL_EncodePkt(id, *pTemp, 2);//��������DL698_ACK֡
    return;
}

/*********************************************************************
* @fn      fnDl698DL_Generate_I_Frame
*
* @brief   ����I֡(�û�������Ϣ֡)
*
* @param   id  ͨ����
*
* @return  �޷���ֵ
*/
void fnDl698DL_Generate_I_Frame(u8 id)
{
    sDl698DL_ChannelInfo_TypeDef *pChan     = &pDl698DL_Channel[id];
    u16 infoIndex = (DL698_LEADERCODE_LEN + 8 + pDl698DL_Channel[id].stAddr.pSA->ubLen);
    u8 *pInfo = &pDl698DL_Channel[id].stTxBuf.pData[infoIndex];
    sDl698DL_CtrlInfo_TypeDef control = {0};
    u16 infoHdr = 0;
    u8 *pTemp = (u8 *)&control;
    u16 apdu_data_len = 0, usInfoLen = 0;
    u16 maxTxlen;   // = DL698DL_TX_INFO_SIZE(id);

    if (pDl698DL_Channel[id].stAddr.pSA->ubLogic & 0x02)    // dyf ������չ�߼���ַ
    {
        infoIndex++;
        pInfo = &pDl698DL_Channel[id].stTxBuf.pData[infoIndex];
    }

    if (id == SCOM_PORT_SPI)
    {
        maxTxlen = 2048;
    }
    else
    {
        maxTxlen = DL698DL_TX_INFO_SIZE(id);
    }

    control.ubCode = DL698DL_GET_FUNCODE(id);
    control.ubDirPrm = DL698DL_GET_DIRPRM(id);
    control.ubScramble = pChan->stRxFrameInfo.ubScramble;

    fnDl698AL_Rd_SendData(id, (u16 *)&apdu_data_len, NULL, 0); //��ȡ��Ҫ����apdu�ĳ���
    if (DL698DL_TEST_FLAG(id, DL698DL_STATE_MASK_TX_FRAGMENT) == false)
    {
        //Ŀǰ�����ڷ��ͷ�Ƭ֡����
        if ((apdu_data_len + 19) > maxTxlen)
        {
            //��Ҫ�����Ƭ֡�������̣����Ϸ�Ƭ֡���ͱ�־

            DL698DL_SET_FLAG(id, DL698DL_STATE_MASK_TX_FRAGMENT);

            control.ubSegment = 1;
            infoHdr = (pChan->ucNumSend | DL698DL_SEGMEMT_FRAME_TYPE_START << 14);
            usInfoLen = maxTxlen - 17;//����֡ͷ֡β��֡���ݲ��ܳ���Э�̳���
            *pInfo++ = LO_U16(infoHdr);
            *pInfo++ = HI_U16(infoHdr);
            apdu_data_len = usInfoLen - 2;
            fnDl698_dl_debug("This is I-first-fragment, set tx fragment state!\n");
        }
        else
        {
            //��Ҫ���Ƿ�Ƭ֡��������
            control.ubSegment = 0;
            usInfoLen = apdu_data_len;
            pChan->ucNumSend = 0;
        }
    }
    else
    {
        control.ubSegment = 1;
        control.ubDirPrm = DL698AL_DIRPRM_SERVRSP;
        if ((apdu_data_len + 19) > maxTxlen)
        {
            infoHdr = (pChan->ucNumSend | DL698DL_SEGMEMT_FRAME_TYPE_MIDDLE << 14);
            usInfoLen = maxTxlen - 17;
            apdu_data_len = usInfoLen - 2;
        }
        else
        {
            DL698DL_RESET_FLAG(id, DL698DL_STATE_MASK_TX_FRAGMENT);
            infoHdr = (pChan->ucNumSend | DL698DL_SEGMEMT_FRAME_TYPE_LAST << 14);
            usInfoLen = apdu_data_len + 2;//�ӷ�֡��źͷ�֡���� 2byte ����
            fnDl698_dl_debug("This is I-last-fragment, reset tx fragment state!\n");
        }
        *pInfo++ = LO_U16(infoHdr);
        *pInfo++ = HI_U16(infoHdr);
    }

    fnDl698AL_Rd_SendData(id, &apdu_data_len, pInfo, control.ubScramble); //�����Ҫ�������ݵ�ָ������
    fnDl698DL_EncodePkt(id, *pTemp, usInfoLen);//��������DL698_I֡

    return;
}

/****************************************************************************************
* @fn      fnDl698DL_ApduInfoHandle
*
* @brief   �û���������Ϣ��鼰���������ݲ�ͬ������������Ӧ��־(�ش�����ACK�����ϱ�AL)��
*
* @param   id  ͨ����
*
* @return  �û�����������.
*/
s8 fnDl698DL_ApduInfoHandle(u8 id)
{
    sDl698DL_ChannelInfo_TypeDef *pChan   = &pDl698DL_Channel[id];
    sDl698DL_FrameInfo_TypeDef *pframInfo = &pDl698DL_Channel[id].stRxFrameInfo;
    sSegmentHdr_TypeDef *pSegHdr = NULL;
    u8 res = SUCCESS;
    u16 temp = 0;
    u8 *pInfo = pframInfo->pInfo;
    u16 infolen = pframInfo->usInfoLen;

    if (pframInfo->ubSegment == 0)
    {
        if (DL698DL_TEST_FLAG(id, DL698DL_STATE_MASK_RX_FRAGMENT))
        {
            //��Ƭ�����н��յ�����֡ʱ������֡���ȼ���ߣ����������֡
            DL698DL_RESET_FLAG(id, DL698DL_STATE_MASK_RX_FRAGMENT); //���DL��Ƭ֡����״̬
        }
        if (DL698DL_TEST_FLAG(id, DL698DL_STATE_MASK_TX_FRAGMENT)) //��֡���͹����нӵ���֡
        {
            DL698DL_RESET_FLAG(id, DL698DL_STATE_MASK_TX_FRAGMENT); //�����֡����״̬
            DL698AL_CLR_SEND_FLAG(id);
        }
        fnDl698_dl_debug("recv an I frame, response to al !\n");
        pChan->ucNumRecv = 0;
        pChan->ucNumSend = 0;  //��֡�����������
        pChan->usState = 0;
        DL698AL_CLR_RECV_FLAG(id);//����AL����buf
        DL698AL_SET_RECV_FLAG(id);//��������֡������AL���ձ�־
    }
    else
    {
        temp = BUILD_U16(pframInfo->pInfo[0], pframInfo->pInfo[1]);
        pSegHdr = (sSegmentHdr_TypeDef *)&temp;
        switch (pSegHdr->ubType)
        {
            case DL698DL_SEGMEMT_FRAME_TYPE_START://���մ���������ʼ֡
            {
                if (DL698DL_TEST_FLAG(id, DL698DL_STATE_MASK_RX_FRAGMENT))
                {
                    //��Ƭ�����н��յ�����֡ʱ������֡���ȼ���ߣ����������֡
                    DL698DL_RESET_FLAG(id, DL698DL_STATE_MASK_RX_FRAGMENT); //���DL��Ƭ֡����״̬
                    DL698AL_CLR_RECV_FLAG(id);                            //����AL����buf
                    pChan->ucNumRecv = 0;
                }
                if (pSegHdr->ubNumber == pChan->ucNumRecv)
                {
                    fnDl698_dl_debug("recv an first segment I-frame !\n");

                    DL698DL_SET_NEXT_NUM(pChan->ucNumRecv);
                    DL698DL_SET_FLAG(id, DL698DL_STATE_MASK_RX_FRAGMENT); //���÷�Ƭ������ʹ�ܱ�־
                    DL698DL_SET_FLAG(id, DL698DL_STATE_MASK_RESPOSE_ACK); //��ӦACK֡
                    infolen -= 2;
                    pInfo += 2;
                }
                else
                {
                    return DL698DL_RX_ERR_RECV_NUM;
                }
                break;
            }
            case DL698DL_SEGMEMT_FRAME_TYPE_ACK://���յ�����ȷ��֡
            {
                if (DL698DL_TEST_FLAG(id, DL698DL_STATE_MASK_TX_FRAGMENT))
                {
                    if (pSegHdr->ubNumber != pChan->ucNumSend)
                    {
                        //�յ�ACK���к�������͵İ���Ų�һ��ʱ���ش�
                        fnDl698_dl_debug("need to resend !\n");
                        DL698DL_SET_FLAG(id, DL698DL_STATE_MASK_RESEND);
                        return SUCCESS;
                    }
                    else
                    {
                        DL698DL_SET_NEXT_NUM(pChan->ucNumSend);
                        DL698DL_RESET_FLAG(id, DL698DL_STATE_MASK_ACK_WAITING); //DL698AL_SET_SEND_FLAG(id);
                    }
                }
                else
                {
                    return DL698DL_RX_I_INFO_CHEACK_ERR;
                }
                return SUCCESS;
            }
            case DL698DL_SEGMEMT_FRAME_TYPE_MIDDLE://���յ������м�֡
            {
                if ((DL698DL_TEST_FLAG(id, DL698DL_STATE_MASK_RX_FRAGMENT))
                    && (pSegHdr->ubNumber == pChan->ucNumRecv))
                {
                    fnDl698_dl_debug("recv a middle segment I-frame !\n");

                    DL698DL_SET_NEXT_NUM(pChan->ucNumRecv);
                    DL698DL_SET_FLAG(id, DL698DL_STATE_MASK_RESPOSE_ACK); //��ӦACK֡
                    infolen -= 2;
                    pInfo += 2;
                }
                else
                {
                    return DL698DL_RX_I_INFO_CHEACK_ERR;
                }
                break;
            }
            case DL698DL_SEGMEMT_FRAME_TYPE_LAST://���յ��������֡
            {
                if (DL698DL_TEST_FLAG(id, DL698DL_STATE_MASK_RX_FRAGMENT))
                {
                    if (pSegHdr->ubNumber == pChan->ucNumRecv)
                    {
                        DL698DL_RESET_FLAG(id, DL698DL_STATE_MASK_RX_FRAGMENT);
                        fnDl698_dl_debug("recv a last segment I-frame !\n");
                        pChan->ucNumRecv = 0;
                        infolen -= 2;
                        pInfo += 2;
                        // DL698AL_CLR_RECV_FLAG(id);
                        DL698AL_SET_RECV_FLAG(id);//��������֡������AL���ձ�־
                    }
                }
                else
                {
                    return DL698DL_RX_I_INFO_CHEACK_ERR;
                }
                break;
            }
            default:
            {
                return DL698DL_RX_I_INFO_CHEACK_ERR;
            }
        }
    }
    if (fnDl698AL_Wr_RecvData(id, &infolen, pInfo, pframInfo->ubSegment, pframInfo->ubScramble) != SUCCESS) //֪ͨALȡ����Ч����
    {
        fnDl698_dl_debug("report al error !\n");
        return DL698DL_ERR_AL_MEM_ALLOC;
    }

    //DL698AL_SET_RECV_FLAG(id);//��Ƭ֡�������
    return res;
}

/*********************************************************************
* @fn      fnDl698DL_Recv
*
* @brief   ���н���֡�Ĵ���
*
* @param   id   ͨ����
*
* @return  void �޷���ֵ
*/
void fnDl698DL_Recv(u8 id)
{
    s8 res = SUCCESS;
    /*  res = fnDl698DL_DecodePkt(id);
      if(res != SUCCESS)
      {
          fnDl698_dl_debug("recv an erro pkt, errocode is %d!\n",res);
      }
      else*/
    {
        fnCommStatus(id);

        res = fnDl698DL_ApduInfoHandle(id);
        if (res != SUCCESS)
        {
            fnDl698_dl_debug("recv an erro pkt, errocode is %d!\n", res);
        }
    }

    return;
}

/*********************************************************************
* @fn      fnDl698DL_Send
*
* @brief   �������õı�־����֡�Ĺ��������ʹ���ӿ�
*
* @param   id   ͨ����
*
* @return  void �޷���ֵ
*/
void fnDl698DL_Send(u8 id)
{
    u8 txflag = 1;
    sDl698DL_FrameInfo_TypeDef *pframInfo = &pDl698DL_Channel[id].stRxFrameInfo;

    fnWDT_Restart();
    if (DL698DL_TEST_FLAG(id, DL698DL_STATE_MASK_RESEND)) //�ش�
    {
        fnDl698_dl_debug("Now resend Frame.\n");

        DL698DL_RESET_FLAG(id, DL698DL_STATE_MASK_RESEND);
    }
    else if (DL698DL_TEST_FLAG(id, DL698DL_STATE_MASK_RESPOSE_ACK)) //��ӦACK֡
    {
        fnDl698_dl_debug("Now response Ack Frame.\n");

        fnDl698DL_Generate_Ack_Frame(id);//����ack֡
        DL698DL_RESET_FLAG(id, DL698DL_STATE_MASK_RESPOSE_ACK);
    }
    else if (DL698AL_GET_SEND_FLAG(id) != 0) //����I֡
    {
        if (DL698DL_TEST_FLAG(id, DL698DL_STATE_MASK_ACK_WAITING) == 0)
        {
            fnDl698_dl_debug("Now response I Frame.\n");
            fnDl698DL_Generate_I_Frame(id);//����I֡
            if (DL698DL_TEST_FLAG(id, DL698DL_STATE_MASK_TX_FRAGMENT))
            {
                //����ǰ���ڷ�Ƭ֡����״̬��������ACK֡������־
                DL698DL_SET_FLAG(id, DL698DL_STATE_MASK_ACK_WAITING);
            }
        }
    }
    else
    {
        txflag = 0;
    }

    if (txflag)
    {
        if (pframInfo->stSA.ubAddrType == DL698DL_SERVER_ADDR_TYPE_BROADCAST) //�㲥��ַ����ҪӦ��
        {
            DL698DL_SET_SCOMFLAG(id, DL698_SCOMPK_EFLAG_IDLE);
            return;
        }
        fnDl698Scom_Tx(id);
    }
    else if (DL698DL_TEST_SCOMFLAG(id, DL698_SCOMPK_EFLAG_RXTOTX) != true)
    {
        DL698DL_SET_SCOMFLAG(id, DL698_SCOMPK_EFLAG_IDLE);
    }

    return;
}

/*********************************************************************
* @fn      fnDl698DL_Process
*
* @brief   ������·��(DL)֡�߼����������
*
* @param   id   ͨ����
*
* @return  void �޷���ֵ
*/
/*
void fnDl698DL_Process(u8 id)
{
    sDl698DL_ChannelInfo_TypeDef *pChan = NULL;

    if(id >= DL698DL_MAX_CHANNEL_NUM)
    {
        return;
    }

    pChan = &pDl698DL_Channel[id];
    if(pChan != NULL)
    {
        fnDl698Scom_TimeOutCheck(id);
        if(pChan->stScom.ucComflag == DL698_SCOMPK_EFLAG_RXTOTX)
        {
            fnDl698DL_Send(id);
            pChan->stScom.ucComflag = DL698_SCOMPK_EFLAG_IDLE;
        }

        if((pChan->stScom.ucComflag == DL698_SCOMPK_EFLAG_RXEND)
            &&(pChan->stScom.ucPktType == PTTYEP_DL698))
        {
            fnDl698DL_Recv(id);
            pChan->stScom.ucComflag = DL698_SCOMPK_EFLAG_RXTOTX;
        }
    }

    return;
}
*/
/*********************************************************************
* @fn      fnDl698_Process
*
* @brief   ������·��(DL)֡�߼����������
*
* @param   id   ͨ����
*
* @return  void �޷���ֵ
*/
void fnDl698_Process(u8 id)
{
    //fnDl698AL_NotiRlsConnHandle(id);//������ӳ�ʱ

    fnDl698DL_Recv(id);
    fnDl698AL_Process(id);
    fnDl698DL_Send(id);
}

/*********************************************************************
* @fn      fnDl698_Init
*
* @brief
*
* @param   id   ͨ����
*
* @return  void �޷���ֵ
*/
void fnDl698_Init(void)
{
    u8 i = 0;

    gSa.ubLen = SR_ADDR_LEN;
    gSa.ubLogic = SR_ADDR_LOG;
    gSa.ubAddrType = SR_ADDR_TYPE;

    fnScom_ReadBps();

    fnComAddrGet(SrAddr);
    gSa.pAddr = SrAddr;

    for (i = 0; i < 3; i++)
    {
        if (fnDl698_Serv_Init(CHANNEL_NUM, gUserCfg) == SUCCESS)
        {
            break;
        }
    }

    for (i = 0 ; i < SCOM_PORT_MAX ; i++)
    {
        fnDl698DL_Init(i);
        fnDl698AL_Init(i);
    }

    return;
}

/*********************************************************************
* @fn      fnReport_Process
*
* @brief
*
* @param   id   ͨ����
*
* @return  void �޷���ֵ
*/
void fnReport_Process(u8 id)
{
    u8 retrans_flag, cnt, rpt_type;

    if (id != SCOM_PORT_ZBCOM)
    {
        return;
    }

    cnt = fnCheck_ReportCnt();
    rpt_type = fnCheck_RptType();

    if ((cnt == 0) || (cnt > 3)) //���ϱ��¼�
    {
        return;
    }

    retrans_flag = 4 - cnt;  //piid

    if (fnReportHandle(id, rpt_type, retrans_flag) == SUCCESS)
    {
        fnWDT_Restart();
        fnDl698DL_Send(id);
    }
}
