
#include "Dl698_Type.h"

#include "Dl698_Globals.h"
#include "Dl698_UserData.h"
#include "Dl698_Memory.h"
#include "Dl698AL_Conn.h"
#include "Dl698AL_Get.h"
#include "Dl698AL_Set.h"
#include "Dl698AL_Act.h"
#include "Dl698AL_Report.h"
#include "Dl698AL_asn1.h"
#ifdef _WIN32
#else
#include "Dl698_EsamOp.h"
#endif

#ifdef _WIN32
#else
u32 current_cout = 0;
#endif

extern ErrorStatus fnFile_Write(u8 FileId, u32 OffAddr, void *Src, u32 Len);
extern u8 fnGet_ConnSta(void);

s8 fnDl698_Serv_Init(u8 channel_number, sDl698AL_UserCfg_TypeDef *pUsrCfg)
{
    u8 id = 0;
    sCommSize_TypeDef tempSize;

    fnDl698_memset((u8*)&gDl698AL_Server, 0x00, sizeof(sDl698AL_Server_TypeDef));

    gDl698AL_Server.channel_number = channel_number;
    gDl698AL_Server.user_para = pUsrCfg;

    pDl698DL_Channel  = &gDl698AL_Server.pDlChan[0];//

    //进行各channel资源分配
    //  global_buf_temp = global_buf;
    for (id = 0; id < channel_number; id ++)
    {
        DL698AL_CLR_RECV_FLAG(id);
        DL698AL_CLR_SEND_FLAG(id);

        //部分资源初始化
        gDl698AL_Server.pDlChan[id].stAddr.pSA = gDl698AL_Server.user_para[id].pSa;
        gDl698AL_Server.pAlChan[id].nego.apdu_size_rx_nego   = gDl698AL_Server.user_para[id].dl_size_rx;
        gDl698AL_Server.pAlChan[id].nego.apdu_size_tx_nego   = gDl698AL_Server.user_para[id].dl_size_tx;
        gDl698AL_Server.pAlChan[id].nego.apdu_window_size_rx = gDl698AL_Server.user_para[id].apdu_window_size_rx;
        gDl698AL_Server.pAlChan[id].nego.apdu_size_deal = gDl698AL_Server.user_para[id].apdu_size;
        gDl698AL_Server.pAlChan[id].time_info.time_tag.len = 1;

        tempSize.apdu_window_size_rx = gDl698AL_Server.pAlChan[id].nego.apdu_window_size_rx;
        tempSize.apdu_size = gDl698AL_Server.pAlChan[id].nego.apdu_size_deal;
        tempSize.dl_size_rx = gDl698AL_Server.pAlChan[id].nego.apdu_size_rx_nego;
        tempSize.dl_size_tx = gDl698AL_Server.pAlChan[id].nego.apdu_size_tx_nego;
        fnWriteConnSize(&tempSize, id, MASTER);
        fnWriteConnSize(&tempSize, id, TERMINAL);
    }
    fnDl698_Buffer_Init();
    return SUCCESS;
}

//COSEM层初始化，一次初始化指定的一个通道
VOID fnDl698AL_Init(u8 channel_id)
{
    //u8 i;
    if (channel_id < gDl698AL_Server.channel_number)
    {
        fnDl698AL_Brk_Asso(channel_id);
    }
    fnDl698_al_debug("DL698 AL init OK!\n");
}

/*********************************************************************
* @fn      fnDl698AL_BuildActRsp
*
* @brief   异常响应时封装接口
*
* @param   chan 通道编号
*
* @return  无返回值
*/

static u8 fnDl698AL_BuildERRRsp(u8 chan, u8 dar, u8 *Recv_data)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;
    u8 *send_data = NULL;
    u16 maxlen = 0, retlen = 0;

    //1.检查buffer是否存在，若不存在则申请发送buffer资源
    if (buf_send->data == NULL)
    {
        buf_send->data = (u8 *)fnDl698_Buffer_Alloc(DL698AL_APDU_MAXSIZE(chan));
        if (buf_send->data == NULL)
        {
            return ERROR;
        }
        buf_send->size = DL698AL_APDU_MAXSIZE(chan);
        fnDl698_memset(buf_send->data, 0, buf_send->size);
    }
    send_data = &buf_send->data[buf_send->right];

    // 2.根据封装类型进行相应封装流程

    UINT8_TO_STREAM(send_data, DL698AL_APDU_TAG_ERRORRSP);     //封装
    UINT8_TO_STREAM(send_data, *Recv_data);                    //PIID
    UINT8_TO_STREAM(send_data, dar);                           //封装DAR

    buf_send->right += 3;

    maxlen = buf_send->size - buf_send->right - DL698AL_RESV_TIMETAG(chan);
    fnDl698AL_FlwRptPkg(chan, maxlen, send_data, &retlen); //封装FollowReport
    send_data += retlen;
    fnDl698AL_TimeTagPkg(chan, send_data); //封装TimeTag
    buf_send->right += retlen + DL698AL_RESV_TIMETAG(chan);
    // 12.打上发包标志
    pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
    pchan->funcode = DL698AL_FUNCODE_DATAINTER;
    DL698AL_SET_SEND_FLAG(chan);

    return SUCCESS;
}

/*********************************************************************
* @fn      fnDl698AL_BuildActRsp
*
* @brief   安全响应异常时封装接口
*
* @param   chan 通道编号
*
* @return  无返回值
*/
u8 fnDl698AL_BuildRsp(u8 chan, u8 dar)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;
    u8 *send_data = NULL;
    //  u16 maxlen = 0,retlen = 0;

    //fnDl698_al_debug("build Act Response part %d\n",encode_type);

    //1.检查buffer是否存在，若不存在则申请发送buffer资源
    if (buf_send->data == NULL)
    {
        buf_send->data = (u8 *)fnDl698_Buffer_Alloc(DL698AL_APDU_MAXSIZE(chan));
        if (buf_send->data == NULL)
        {
            return ERROR;
        }
        buf_send->size = DL698AL_APDU_MAXSIZE(chan);
        fnDl698_memset(buf_send->data, 0, buf_send->size);
    }
    send_data = &buf_send->data[buf_send->right];

    // 2.根据封装类型进行相应封装流程

    UINT8_TO_STREAM(send_data, DL698AL_APDU_TAG_SECRSP);     //封装actrsp
    UINT8_TO_STREAM(send_data, 2);                    //封装DAR 2=异常错误
    UINT8_TO_STREAM(send_data, dar);                           //封装DAR
    UINT8_TO_STREAM(send_data, 0);                             //封装选择
    buf_send->right += 4;

    // 12.打上发包标志
    pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
    pchan->funcode = DL698AL_FUNCODE_DATAINTER;
    DL698AL_SET_SEND_FLAG(chan);

    return SUCCESS;
}

//函数实现的伪码表示
void fnDl698AL_Process(u8 chan)
{
    u16 error = DATA_ACCESS_RESULT_SUC;

    if (DL698AL_GET_RECV_FLAG(chan) != 0) //COSEM接收标志有效
    {
        error = fnDl698AL_Handle(chan);
        if (error != DATA_ACCESS_RESULT_SUC)
        {
            fnDl698_al_debug("It is erro! erro code is %d.\n", error);
        }
    }
    return ;
}

#include "globals.h"
//返回0表示成功，非零值表示错误
s16 fnDl698AL_Handle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef* pchan = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;
    #ifdef DL698_THENGET_WITH_DELAY
    sDl698TimeInfo_TypeDef* pTime = &gDl698AL_Server.pAlChan[chan].time_info;
    sDl698AL_BlockInfo_TypeDef* pBlock = &gDl698AL_Server.pAlChan[chan].blockInfo;
    #endif
    #ifdef DL698_GETBLOCK
    #ifndef DL698_THENGET_WITH_DELAY
    sDl698AL_BlockInfo_TypeDef* pBlock = &gDl698AL_Server.pAlChan[chan].blockInfo;
    #endif
    #endif
    u8  tag1;
    u8  secreqtag;
    //for sec-req parse
    //u8  tag_cp,tag_mac;
    //    u8* pSecData;
    //
    u8* pdata;
    s16 error = DATA_ACCESS_RESULT_SUC;
    //u16 ret_len;
    //    sDl698DL_FrameInfo_TypeDef *pframInfo = &pDl698DL_Channel[chan].stRxFrameInfo;

    fnDl698_al_debug("fnDl698AL_Handle !\n");

    #ifdef DL698_THENGET_WITH_DELAY
    if (pBlock->block_flag == DL698AL_SETTHENGET_BLOCKING)
    {
        if (DL698AL_BOOL_GETTIMEOUT(pTime->start_stamp, pTime->current_cout, pTime->delay_time) == true)
        {
            fnDl698AL_SetReqHandle(chan);
        }
    }
    else if (pBlock->block_flag == DL698AL_ACTTHENGET_BLOCKING)
    {
        if (DL698AL_BOOL_GETTIMEOUT(pTime->start_stamp, pTime->current_cout, pTime->delay_time) == true)
        {
            fnDl698AL_ActReqHandle(chan);
        }
    }
    else
    #endif
    {
        if (buf_recv->right <= buf_recv->left)
        {
            //指定通道的APDU接收缓存中没有数据
            //报错并返回
            DL698AL_CLR_RECV_FLAG(chan);
            return -DATA_ACCESS_RESULT_OVERFLOAT_ERR;
        }
        else
        {
            #ifdef _WIN32
            #else
            pchan->time_info.lastdata_cout = current_cout;  //最后一次数据交互的时间
            #endif
            pdata = &buf_recv->data[buf_recv->left]; //把pdata指向APDU的首地址
            tag1 = *pdata++;

            fnDl698_al_debug("recv an apud tag %d\n", tag1);

            /*
            if(BSP_EASM_GetPower() == false)  //ESAM电源关闭时需先打开
            {
                fnWDT_Restart();
                fnEsamOp_EsamInit();
            }
            */

            //在这里开始解密
            if ((tag1 == DL698AL_APDU_TAG_SECREQ) || (tag1 == DL698AL_APDU_TAG_SECRSP))
            {
                //SECURITY-Request
                secreqtag = tag1;
                error = fnDl698AL_SecReq_Handle(chan);//解密后会更新left和right
                if (error != DATA_ACCESS_RESULT_SUC)
                {
                    //解密或者MAC校验错误
                    DL698AL_CLR_RECV_FLAG(chan);
                    gDl698AL_Server.pAlChan[chan].sec_data.SecType = 0xFF;
                    *pdata = 0xFF;
                    fnDl698AL_BuildRsp(chan, error);   //解密失败应答退出

                    return error;
                }
                //u8 temp[50] , len;
                //Std_Memset(&temp[0] , 0x00 , 50);
                //if(buf_recv->right > 50)
                //  len = 50;
                //else
                //  len = buf_recv->right;
                //Std_Memcpy(&temp[0] ,&buf_recv->data[buf_recv->left] , len);
                //if((temp[3] !=0x41)&&(temp[4] !=0x03)&&(gDl698AL_Server.pAlChan[chan].sec_data.SecType > 9))
                //  fnFile_Write(13 , 12, &temp[0] , 50);
            }
            else
            {
                gDl698AL_Server.pAlChan[chan].sec_data.SecType = 0x08;    //纯明文
            }
            //-解密完成

            gActSessionDestroyed = 0;
            pdata = &buf_recv->data[buf_recv->left];
            tag1 = *pdata++;

            if (gDl698AL_Server.pAlChan[chan].dirprm == DL698DL_FRAME_TYPE_C2S_RESPONSE)
            {
                if (tag1 != DL698AL_APDU_TAG_RPTRSP)
                {
                    DL698AL_CLR_RECV_FLAG(chan);
                    return DATA_ERRORRSP_NOTSEVR;
                }
            }

            if (fnDl698AL_TimeTag_Handle(chan) == 0xFF) //查找是否有时间标签，并判APDU 合法性
            {
                error = DATA_ERRORRSP_APDUERR;
                pdata++;  //Request [integer]
                fnDl698AL_BuildERRRsp(chan, error, pdata);
            }
            else
            {
                #ifdef DL698_GETBLOCK
                if ((pchan->blockInfo.block_flag == true)
                    && (tag1 != DL698AL_APDU_TAG_GETREQ))
                {
                    //分片过程中来了个其他帧，把分片终止，处理新包优先级最高处理
                    DL698AL_CLR_BLOCKINFO(chan);    //重置分片相关信息
                    DL698AL_CLR_PEND_BUFFER(chan);  //重置挂起包信息
                }
                #endif
                //第一个字节是APDU的tag

                switch (tag1)
                {
                    case (DL698AL_APDU_TAG_CONREQ) :
                    {
                        //连接请求
                        //if(pchan->state == DL698AL_STATE_NO_ASSO)
                        {
                            //if(fnDl698AL_Check_Auth(chan , tag1 , 0)==DATA_ACCESS_RESULT_SUC)
                            error = fnDl698AL_ConnHandle(chan);

                            if (error == 0)
                            {
                                //如果连接可以建立，则修改状态为已连接
                                pchan->state = DL698AL_STATE_IDLE;
                                fnDl698AL_EvtNotify(chan, DL698AL_EVENT_CONNECT);
                            }
                            else //如果连接不可以建立，则维持未连接的状态，状态不变，但是要将协商的内容清除，防止出错
                            {
                                fnDl698_memset((u8*)&pchan->nego, 0, sizeof(pchan->nego));
                                {
                                    //è?1????°??óD?μ￡??òê1ó?ó??§????μ??μ
                                    pchan->nego.apdu_size_deal = gDl698AL_Server.user_para[chan].apdu_size;
                                    pchan->nego.apdu_size_rx_nego = gDl698AL_Server.user_para[chan].dl_size_rx;
                                    pchan->nego.apdu_size_tx_nego = gDl698AL_Server.user_para[chan].dl_size_tx;
                                    pchan->nego.apdu_window_size_rx = gDl698AL_Server.user_para[chan].apdu_window_size_rx;
                                }
                                fnDl698AL_EvtNotify(chan, DL698AL_EVENT_CONNECTFAIL);
                            }
                        }
                        //else
                        //{//已经建立了连接，又重复连接，将重复连接的请求丢弃就可以了！
                        //  error = -DATA_ACCESS_AL_ASSO_ERROR;//COSEM_RE_ASSO_ERROR;
                        //  fnDl698AL_EvtNotify(chan,DL698AL_EVENT_RECONNECT);
                        //}
                        break;
                    }
                    case (DL698AL_APDU_TAG_RLSREQ) :
                    {
                        //断开连接请求
                        //if(state!=DL698AL_STATE_NO_ASSO)
                        {
                            //if(fnDl698AL_Check_Auth(chan , tag1 , 0)==DATA_ACCESS_RESULT_SUC)
                            error = fnDl698AL_RlsHandle(chan);

                            if (error < DATA_ACCESS_RESULT_SUC)
                            {
                                fnDl698_al_debug("RLRQ 断开连接失败！\n");
                            }
                            else
                            {
                                fnDl698_al_debug("RLRQ 断开连接成功！\n");
                            }
                            if (error == DATA_ACCESS_RESULT_SUC)
                            {
                                //只有连接断开成功时，才做相应的清除处理。
                                fnDl698AL_Brk_Asso(chan);
                                fnDl698AL_EvtNotify(chan, DL698AL_EVENT_RELEASE);
                            }
                            else
                            {
                                fnDl698AL_EvtNotify(chan, DL698AL_EVENT_RELEASEFAIL);
                            }
                        }
                        //else
                        //{//当前没有建立连接，那么丢弃RLRQ请求
                        //  error = 0;//COSEM_RE_ASSO_ERROR;
                        //  fnDl698AL_EvtNotify(chan,DL698AL_EVENT_DUMMYDIS);
                        //}
                        break;
                    }
                    case (DL698AL_APDU_TAG_GETREQ) :
                    {
                        fnDl698_al_debug("Get requesting...\n");

                        error = fnDl698AL_GetReqHandle(chan);

                        break;
                    }
                    case (DL698AL_APDU_TAG_SETREQ) :
                    {
                        fnDl698_al_debug("Set requesting...\n");

                        error = fnDl698AL_SetReqHandle(chan);

                        break;
                    }
                    case (DL698AL_APDU_TAG_ACTREQ) :
                    {
                        fnDl698_al_debug("Act requesting...\n");

                        error = fnDl698AL_ActReqHandle(chan);

                        break;
                    }
                    case (DL698AL_APDU_TAG_RPTRSP) :
                    {
                        fnDl698_al_debug("Report Response...\n");
                        //if(state == DL698AL_STATE_NO_ASSO)
                        //{
                        //  error = 0; //没有建立连接，收到set服务请求，则不做响应
                        //}
                        //else if(state == DL698AL_STATE_IDLE)
                        {
                            //pchan->funcode = DL698AL_FUNCODE_DATAINTER;
                            if (buf_recv->right - buf_recv->left < 5)  //即使数据为1个字节,无时间标签，整个帧长度也大于9
                            {
                                error = -DATA_ACCESS_RESULT_DENY;
                            }
                            else
                            {
                                //if(fnDl698AL_Check_Auth(chan , tag1 , 0)==DATA_ACCESS_RESULT_SUC)
                                error = fnDl698AL_RptRspHandle(chan);
                            }
                        }
                        break;
                    }

                    default:
                        error = DATA_ERRORRSP_NOTSEVR;
                        pdata++;  //Request [integer]
                        fnDl698AL_BuildERRRsp(chan, error, pdata);

                        break;
                }
            }
        }
    }

    //连接剩余时间清零
    if (Secret.CA == MASTER)
    {
        if (Secret.Master.tLinkDly[chan] != 0)
        {
            Secret.Master.tLinkDly[chan] = Secret.Master.tLink[chan];
        }
    }
    else
    {
        if (Secret.Terminal.tLinkDly[chan] != 0)
        {
            Secret.Terminal.tLinkDly[chan] = Secret.Terminal.tLink[chan];
        }
    }
    //

    #ifdef DL698_THENGET_WITH_DELAY
    if ((pchan->blockInfo.block_flag != DL698AL_SETTHENGET_BLOCKING)
        && (pchan->blockInfo.block_flag != DL698AL_ACTTHENGET_BLOCKING))
    #endif
    {
        DL698AL_CLR_RECV_FLAG(chan);
        //加密
        if (secreqtag == DL698AL_APDU_TAG_SECREQ)
        {
            if (fnDl698AL_Gen_SecRsp(chan) == 0xFFFF)
            {
                //error
            }
        }
        //
    }
    #ifdef DL698_THENGET_WITH_DELAY
    else
    {
        DL698DL_SET_SCOMFLAG(chan, DL698_SCOMPK_EFLAG_RXTOTX);
    }
    #endif

    if (gActSessionDestroyed)
    {
        fnEsamOp_SessionDestroyed(Secret.CA);
    }

    DL698AL_CLR_RECV_FLAG(chan);

    return error;
}

s8  fnDl698AL_Wr_RecvData(u8 chan, u16* length, u8* pdata, u8 seg, u8 scramble)
{
    u16 right = 0;
    u16 len = *length;
    u8* src = NULL, *temp = NULL;
    u8 scrambleData = 0;
    u16 allocSize = 0;

    if (len == 0)
    {
        DL698AL_CLR_RECV_FLAG(chan);
        *length = 0;
        return ERROR;
    }

    //apdu RXBUF资源分配
    if (gDl698AL_Server.pAlChan[chan].apdu_rx_buf.data == NULL)
    {
        if (seg == 0)
        {
            //DL接收的是个完整帧时，申请的接收buf为最大协商发送帧大小
            allocSize = DL698DL_RX_INFO_SIZE(chan);
        }
        else
        {
            //DL接收的是个分片帧时，申请的接收buf为最大协商apdu大小
            allocSize = DL698AL_APDU_MAXSIZE(chan);
        }

        temp = (u8 *)fnDl698_Buffer_Alloc(allocSize);
        if (temp == NULL)
        {
            return ERROR;
        }
        fnDl698_memset(temp, 0, allocSize);
        gDl698AL_Server.pAlChan[chan].apdu_rx_buf.data = temp;
    }

    right = gDl698AL_Server.pAlChan[chan].apdu_rx_buf.right;
    src  = &gDl698AL_Server.pAlChan[chan].apdu_rx_buf.data[right];

    if (right + len > gDl698AL_Server.user_para->apdu_size) //长度为0
    {
        //如果出错了，则清除已经接收到的数据
        DL698AL_CLR_RECV_FLAG(chan);
        *length = 0;
        return ERROR;
    }

    gDl698AL_Server.pAlChan[chan].apdu_rx_buf.right += len;

    if (scramble != 0)
    {
        scrambleData = 0x33;
    }

    while (len--)
    {
        *src++ = (*pdata++) - scrambleData;
    }

    return SUCCESS;
}

s8  fnDl698AL_Rd_SendData(u8 chan, u16* length, u8* pdata, u8 scramble)
{
    u16 left = gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left;
    u16 right = gDl698AL_Server.pAlChan[chan].apdu_tx_buf.right;
    u16 len = 0;
    u8* src = &gDl698AL_Server.pAlChan[chan].apdu_tx_buf.data[left];
    u8 scrambleData = 0;

    if (left >= right)
    {
        len = 0;
    }
    else
    {
        len = right - left;
    }

    if (*length == 0)
    {
        *length = len;
        return SUCCESS;
    }
    else
    {
        if (*length < len)
        {
            len = *length;
        }
        else
        {
            *length = len;
        }

        if (scramble != 0)
        {
            scrambleData = 0x33;
        }

        while (len--)
        {
            *pdata++ = (*src++) + scrambleData;
        }
    }
    gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left += *length;
    if (gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left >= gDl698AL_Server.pAlChan[chan].apdu_tx_buf.right)
    {
        DL698AL_CLR_SEND_FLAG(chan);
    }
    return SUCCESS;
}

extern u8 fnConnectDis_SecretClr(void);

s8  fnDl698AL_Brk_Asso(u8 chan)
{
    sCommSize_TypeDef   tempSize;

    if (gDl698AL_Server.pAlChan[chan].state != DL698AL_STATE_NO_ASSO)
    {
        fnDl698AL_EvtNotify(chan, DL698AL_EVENT_BREAK);
    }
    gDl698AL_Server.pAlChan[chan].state = DL698AL_STATE_NO_ASSO;

    fnDl698_memset((u8*)&gDl698AL_Server.pAlChan[chan].nego, 0, sizeof(gDl698AL_Server.pAlChan[chan].nego));
    //if(apdu_size_tx == 0)
    {
        //保证如果还有未发送出去的数据则发送出去，其实只用于AARE和RLRE
        gDl698AL_Server.pAlChan[chan].nego.apdu_size_tx_nego = gDl698AL_Server.user_para[chan].dl_size_tx;
        gDl698AL_Server.pAlChan[chan].nego.apdu_size_rx_nego = gDl698AL_Server.user_para[chan].dl_size_rx;
        gDl698AL_Server.pAlChan[chan].nego.apdu_size_deal = gDl698AL_Server.user_para[chan].apdu_size;
        gDl698AL_Server.pAlChan[chan].nego.apdu_window_size_rx = gDl698AL_Server.user_para[chan].apdu_window_size_rx;

        //建立连接时间清零
        gDl698AL_Server.pAlChan[chan].time_info.conn_time.year = 0;
        gDl698AL_Server.pAlChan[chan].time_info.conn_time.month = 0;
        gDl698AL_Server.pAlChan[chan].time_info.conn_time.day  = 0;
        gDl698AL_Server.pAlChan[chan].time_info.conn_time.hour = 0;
        gDl698AL_Server.pAlChan[chan].time_info.conn_time.minute = 0;
        gDl698AL_Server.pAlChan[chan].time_info.conn_time.second = 0;
        //时间标签长度赋值为1
        gDl698AL_Server.pAlChan[chan].time_info.time_tag.len = 1;

        tempSize.apdu_window_size_rx = gDl698AL_Server.pAlChan[chan].nego.apdu_window_size_rx;
        tempSize.apdu_size = gDl698AL_Server.pAlChan[chan].nego.apdu_size_deal;
        tempSize.dl_size_rx = gDl698AL_Server.pAlChan[chan].nego.apdu_size_rx_nego;
        tempSize.dl_size_tx = gDl698AL_Server.pAlChan[chan].nego.apdu_size_tx_nego;
        fnWriteConnSize(&tempSize, chan, pDl698DL_Channel[chan].stRxFrameInfo.ucCA);
        fnConnectDis_SecretClr();
    }
    return 0;
}

/*********************************************************************
* @fn      fnDl698AL_Check_OIList
*
* @brief   在OI LIST中查找指定的OI，OI LIST是按照class_id存储的
*
* @param
*
* @return  class_id对应的OI LIST中的索引号，0xFFFF表示没有找到
*/
u16 fnDl698AL_Check_OIList(sDl698AL_ObjInfo_TypeDef *pObj)
{
    u16 ind = 0xFFFF;
    u16 class_id, i;
    //  u16 *pOIList  = NULL;
    CONST u16* pList   ;

    for (class_id = 0 ; class_id < gDl698_OIList_NUMBER; class_id++)
    {
        pList = gDl698_OIList[class_id];
        for (i = 0; i < gDl698_NumIC[class_id]; i++)
        {
            if (*pList == pObj->oi)
            {
                pObj->class_id = class_id + 1;
                pObj->oi_list_index = i;
                ind = i;
                return ind;
            }
            pList++;
        }
    }

    return ind;
}

/*********************************************************************
* @fn      fnDl698AL_Check_OISec
*
* @brief
*
* @param
*
* @return  返回OI权限匹配结果 ,
                1 通过
                0 失败
*/
/*u8 fnDl698AL_Check_OISec(u8 chan)
{
    return SUCCESS;
}*/

#if DL698_PROCESS_DIAGEN
void fnDl698_ChkOIList_test(void)
{
    u16 ind;
    sDl698AL_ObjInfo_TypeDef pTestObj;
    pTestObj.oi = 0x0040;
    ind = fnDl698AL_Check_OIList(&pTestObj);

    pTestObj.oi = 0x1030;
    ind = fnDl698AL_Check_OIList(&pTestObj);

    pTestObj.oi = 0x2002;
    ind = fnDl698AL_Check_OIList(&pTestObj);

    pTestObj.oi = 0x2028;
    ind = fnDl698AL_Check_OIList(&pTestObj);

    pTestObj.oi = 0x4105;
    ind = fnDl698AL_Check_OIList(&pTestObj);

    pTestObj.oi = 0x0003;
    ind = fnDl698AL_Check_OIList(&pTestObj);
}
#endif

void fnDl698AL_SecParse_Rn(u8** pData, u16 *RnLen) //inline
{
    u8* pBuf = *pData;
    //if(*pBuf++ == DL698AL_DATA_TYPE_OCT_STR)
    {
        pBuf += fnDL698AL_asn1_get_ObjCnt(RnLen, *pData); //data length
        *pData = pBuf;
    }
    //else
    //{
    //    *RnLen = 0;
    //}
}

/*
void fnDl698AL_SecParse_SidMac(u8** pData,u16 *DatLen,u8* pDstData)  //inline
{
    //拷贝SID
    u16 DstLen = DL698AL_SIDCHR_LEN;
    u8 TagLen;
    u8* pSrcData = *pData;
    //if((*pSrcData++ != DTYPE_STRUCTURE) || (*pSrcData++ != 2) )
    //{//error
    //}
    //pSrcData += 2;  //struct 2
    Std_Memcpy(pDstData,pSrcData,DL698AL_SIDCHR_LEN);  //标识 double-long-unsigned
    pSrcData += DL698AL_SIDCHR_LEN;

    TagLen = *pSrcData++;
    if(TagLen != 0)
    {//附加数据 02LLXXXX
        Std_Memcpy(pDstData+DstLen,pSrcData,TagLen);
        DstLen += TagLen;
        pSrcData += TagLen;
    }
    else
    {
        pSrcData += 1;
    }
    TagLen = *pSrcData++;
    if(TagLen != 0)
    {
        Std_Memcpy(pDstData+DstLen,pSrcData,TagLen);
        DstLen += TagLen;
        pSrcData += TagLen;
    }

    *DatLen = DstLen;
    *pData = pSrcData;

    return;
}
*/
/*********************************************************************
* @fn      fnDl698AL_SecReq_Handle
*
* @brief   获取APDU的安全等级，包括两部分，明文/密文+数据验证信息类型
*
* @param
*
* @return   bit[0]表示明文或密文,
                0 明文,
                1 密文;
            bit[2:1]表示MAC类型，
                数据验证码      [0]  SID_MAC，
                随机数          [1]  RN，
                随机数+数据MAC  [2]  RN_MAC，
                安全标识        [3]  SID
*/
//u16 fnDl698AL_SecReq_Handle(u8 chan,u8** pSrcData,u16* apdu_len)
u16 fnDl698AL_SecReq_Handle(u8 chan)
{
    u16 apdu_len = 0xFFFF;
    #ifdef _WIN32
    #else
    u8 tag_cp = 0, tag_mac = 0, tag_sec, res = DATA_ACCESS_RESULT_SUC;
    u16 data_len = 0;//,mac_len = 0;
    u8* pTxTemp;
    u8* pRxTemp;
    u16 TxLen, RxLen;
    u16 TagLen;
    u8* pdata = gDl698AL_Server.pAlChan[chan].apdu_rx_buf.data;
    u8* pOrgdata = pdata;
    sDl698DL_FrameInfo_TypeDef *pframInfo = &pDl698DL_Channel[chan].stRxFrameInfo;
    //    ErrorStatus ret;

    pdata++;
    tag_cp = *pdata++;
    //if(*pdata++ == DL698AL_DATA_TYPE_OCT_STR)
    {
        pdata += fnDL698AL_asn1_get_ObjCnt(&data_len, pdata); //data length
        pOrgdata = pdata;
        pdata += data_len;                               //data
        tag_mac = *pdata++;                              //pdata 现在指向数据验证信息
        if (tag_mac > 3) //MAC类型取值范围0~3
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
    }
    //else
    //    return 0xFFFF;

    tag_sec = ((tag_cp << 4) | tag_mac);
    //
    switch (tag_sec)
    {
        //支持5种明文密文+MAC的组合
        //请求为明文+随机数RN，应答为明文+MAC；
        //请求为密文+SID，应答为密文；
        //请求为密文+SID_MAC，应答为密文+MAC（广播或组地址通信无应答）
        //请求为明文+RN_MAC，应答为明文+MAC；
        //请求为明文+SID_MAC，无应答。
        case (0x01): //明文+随机数RN，应答为明文+MAC
        {
            fnDl698AL_SecParse_Rn(&pdata, &TagLen);
            //pSrcData = pOrgdata;
            apdu_len = data_len;
            gDl698AL_Server.pAlChan[chan].sec_data.pSecTag  = pdata;
            gDl698AL_Server.pAlChan[chan].sec_data.SecTagLen = TagLen;
            Std_Memcpy(gDl698AL_Server.pAlChan[chan].sec_data.RN, pdata, TagLen); //保存随机数
            break;
        }
        case (0x00): //明文+SID_MAC，
        case (0x13): //密文+SID，应答为密文
        case (0x10): //密文+SID_MAC，应答为密文+MAC
        {
            if ((fnGet_ConnSta() == ERROR) && (pframInfo->stSA.ubAddrType != DL698DL_SERVER_ADDR_TYPE_BROADCAST))
            {
                res = DATA_ACCESS_RESULT_SECFAIL;
            }
            else
            {
                //分配与ESAM交互所需要的BUFFER
                pTxTemp = (u8 *)fnDl698_Buffer_Alloc(DL698AL_ESAMBUF_MAXSIZE);
                pRxTemp = (u8 *)fnDl698_Buffer_Alloc(DL698AL_ESAMBUF_MAXSIZE);

                if (pTxTemp != NULL && pRxTemp != NULL)
                {
                    //拷贝SID到ESAM TX BUFFER
                    Std_Memcpy(pTxTemp, pdata, DL698AL_SIDCHR_LEN);
                    TxLen = DL698AL_SIDCHR_LEN;
                    pdata += DL698AL_SIDCHR_LEN;

                    TagLen = *pdata++;
                    if (TagLen != 0)
                    {
                        //附加数据 02LLXXXX
                        Std_Memcpy(pTxTemp + TxLen, pdata, TagLen);
                        TxLen += TagLen;
                        pdata += TagLen;
                    }
                    else
                    {
                        pdata += 1;
                    }

                    //拷贝数据到ESAM TX BUFFER
                    Std_Memcpy(pTxTemp + TxLen, pOrgdata, data_len);
                    TxLen += data_len;

                    TagLen = *pdata++;
                    if (TagLen != 0)
                    {
                        Std_Memcpy(pTxTemp + TxLen, pdata, TagLen);
                        TxLen += TagLen;
                        pdata += TagLen;
                    }
                    else
                    {
                        pdata += 1;
                    }
                    if (fnEsamOp_Tx_Esam(pRxTemp, pTxTemp, &RxLen) != ERROR) //计算密文数据及MAC
                    {
                        Std_Memcpy(pOrgdata, pRxTemp, RxLen);
                        apdu_len = RxLen;
                    }
                    else
                    {
                        res = DATA_ACCESS_RESULT_SYMENC;
                    }
                }
                else
                {
                    res = DATA_ACCESS_RESULT_OTH;
                }

                fnDl698_Buffer_Free(pTxTemp);//
                fnDl698_Buffer_Free(pRxTemp);//
            }
            break;
        }
        /*
          case(0x02):{//明文+RN_MAC，应答为明文+MAC ,用于主动上报，不需要支持
              break;
          }
          */

        default:
            return DATA_ACCESS_RESULT_OTH;  //other are all error
    }

    gDl698AL_Server.pAlChan[chan].sec_data.SecType = tag_sec;  //存储到连接信息里面

    gDl698AL_Server.pAlChan[chan].apdu_rx_buf.left  = 0; //no change
    gDl698AL_Server.pAlChan[chan].apdu_rx_buf.right = apdu_len;
    gDl698AL_Server.pAlChan[chan].apdu_rx_buf.data  = pOrgdata;
    #endif
    return res;

    //安全模式参数的判断放到GET/SET/ACT各自的处理函数内部来做，这里不需要了
    //读取安全模式参数，如果不启用安全模式参数则跳过该步骤以及后面判断安全等级步骤
    //判断安全等级
}

/*********************************************************************
* @fn      fnDl698AL_Gen_SecRsp
*
* @brief   将待发送的APDU进行加密和添加校验
*
* @param
*
* @return
*/
u16 fnDl698AL_Gen_SecRsp(u8 chan)
{
    #ifdef _WIN32
    return 0xFFFF;
    #else
    //回应有以下三种：(主站)，模拟终端指令流不一样，需注意
    //请求为明文+随机数RN，应答为明文+MAC；
    //发送：800E4002+LC+Data1 返回：9000+0004+MAC
    //电表计算明文+MAC
    //LC:Data1 长度，2 字节
    //Data1：包含RN+抄读数据
    //PlainData
    //明文数据单元
    //明文应用数据单元：
    //PlainData

    //请求为密文+SID，应答为密文；
    //发送：800A4002+LC+Data1 返回：9000+Len+Data2
    //电表计算密文
    //LC:Data1 长度，2 字节
    //Data1：包含RN+抄读数据
    //PlainData
    //密文应用数据单元：Data2

    //请求为密文+SID_MAC，应答为密文+MAC（广播或组地址通信无应答）
    //发送：80104002+LC+Data1 返回：9000+Len+Data2+MAC
    //电表计算密文+MAC
    //LC:Data1 长度，2 字节
    //Data1：包含RN+抄读数据
    //PlainData
    //Len：Data2 和MAC 长度
    //密文应用数据单元：Data2
    //数据验证信息：MAC
    u8 tag_sec = gDl698AL_Server.pAlChan[chan].sec_data.SecType;  //应该存储在连接的结构体里面
    u8 tempCA = pDl698DL_Channel[chan].stRxFrameInfo.ucCA;
    ErrorStatus ret;
    u8 macVal[DL698AL_MAC_LEN];
    u8 rn_max[16];
    u16 apduLen;
    u8* pTxTemp;
    u8* pRxTemp;
    u8  objLen, P2;
    u16 dataLen = gDl698AL_Server.pAlChan[chan].apdu_tx_buf.right - gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left;
    u8* pData = &gDl698AL_Server.pAlChan[chan].apdu_tx_buf.data[gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left];
    u8* pApdu = gDl698AL_Server.pAlChan[chan].apdu_tx_buf.data;
    u16 RxLen;
    u16 rnlen;
    u16 whithNameLen;

    if (gDl698AL_Server.pAlChan[chan].apdu_tx_buf.data[gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left] == 0x90 &&
        gDl698AL_Server.pAlChan[chan].apdu_tx_buf.data[gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left + 1] == 0x02 &&
        gDl698AL_Server.pAlChan[chan].apdu_tx_buf.data[gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left + 2] == 0x03
       )
    {
        return 3;
    }

    // pTemp = (u8 *)fnDl698_Buffer_Alloc(DL698AL_APDU_MAXSIZE(chan));
    pTxTemp = (u8 *)fnDl698_Buffer_Alloc(DL698AL_ESAMBUF_MAXSIZE);
    if (pTxTemp == NULL)
    {
        return ERROR ;
    }
    pRxTemp = (u8 *)fnDl698_Buffer_Alloc(DL698AL_ESAMBUF_MAXSIZE);
    if (pRxTemp == NULL)
    {
        fnDl698_Buffer_Free(pTxTemp);
        return ERROR ;
    }

    Std_Memcpy(pTxTemp, pData, dataLen);

    *pApdu++ = DL698AL_APDU_TAG_SECRSP;
    switch (tag_sec)
    {
        case (0x01): //明文+随机数RN，应答为明文+MAC ,主站模拟终端指令流一样
        {
            rnlen = gDl698AL_Server.pAlChan[chan].sec_data.SecTagLen;
            *pApdu++ = DL698AL_APDU_TAG_SECRSP_PT;
            objLen = fnDL698AL_asn1_set_ObjCnt(dataLen, pApdu);
            pApdu += objLen;
            Std_Memcpy(pApdu, pTxTemp, dataLen);
            if (chan == SCOM_PORT_SPI)
            {
                fnEsamOp_ReadEsam_SafeNameList(pTxTemp, &whithNameLen); //读取白名单表号
                SystemDelayUs(60);
            }
            else
            {
                whithNameLen = 0;
            }
            Std_Memcpy(pTxTemp + whithNameLen, gDl698AL_Server.pAlChan[chan].sec_data.RN, rnlen); //拷贝随机数
            Std_Memcpy(pTxTemp + whithNameLen + rnlen, pApdu, dataLen);
            ret = fnEsamOp_Get_PlainDataMac(chan, pTxTemp, whithNameLen + dataLen + rnlen, macVal); //计算明文数据MAC
            if (ret == ERROR)
            {
                if (Bkgrd.PubData.MtSysSta.SysStaBit.EsamErr == 0) //不是ESAM通信故障（加解密失败）
                {
                    break;
                }
                else
                {
                    Std_Memset(macVal, 0xFF, DL698AL_MAC_LEN);  //ESAM通信故障，MAC为4字节FF
                    ret = SUCCESS;
                }
            }
            pApdu += dataLen;
            *pApdu++ = 0x01;     //has mac
            *pApdu++ = DL698AL_APDU_TAG_SECRSP_MAC;
            *pApdu++ = DL698AL_MAC_LEN;
            Std_Memcpy(pApdu, macVal, DL698AL_MAC_LEN);
            apduLen = objLen + dataLen + DL698AL_MAC_LEN + 5; //or 3?
            break;
        }
        case (0x13): //密文+SID，应答为密文
        {
            *pApdu++ = DL698AL_APDU_TAG_SECRSP_CT;
            P2 = 0xA6;
            if ((tempCA & 0xF0) == TERMINAL)
            {
                ret = fnEsamOp_TrmDataToCipherWithMac(pRxTemp, pTxTemp, &RxLen, dataLen, P2);    //模拟终端
            }
            else        //主站
            {
                ret = fnEsamOp_DataToCipherWithMac(pRxTemp, pTxTemp, &RxLen, dataLen, P2);    //计算密文数据
            }

            if (ret == ERROR)
            {
                //error
                break;
            }
            objLen = fnDL698AL_asn1_set_ObjCnt(RxLen, pApdu);
            pApdu += objLen;
            Std_Memcpy(pApdu, pRxTemp, RxLen);
            pApdu += RxLen;
            *pApdu++ = 0x00; //no mac
            apduLen = objLen + RxLen + 3;
            break;
        }
        case (0x00):  //明文+SIDMAC,应答为明文+MAC
        case (0x10): //密文+SID_MAC，应答为密文+MAC
        {
            if (tag_sec == 0x10)
            {
                *pApdu++ = DL698AL_APDU_TAG_SECRSP_CT;
                P2 = 0xA7;
            }
            else
            {
                *pApdu++ = DL698AL_APDU_TAG_SECRSP_PT;
                P2 = 0x11;
            }

            if ((tempCA & 0xF0) == TERMINAL)
            {
                ret = fnEsamOp_TrmDataToCipherWithMac(pRxTemp, pTxTemp, &RxLen, dataLen, P2);    //模拟终端
            }
            else //主站
            {
                ret = fnEsamOp_DataToCipherWithMac(pRxTemp, pTxTemp, &RxLen, dataLen, P2);    //计算密文数据及MAC
            }

            if (ret == ERROR)
            {
                //error
                break;
            }
            RxLen -= DL698AL_MAC_LEN;
            objLen = fnDL698AL_asn1_set_ObjCnt(RxLen, pApdu);
            pApdu += objLen;
            Std_Memcpy(pApdu, pRxTemp, RxLen);
            pApdu += RxLen;

            *pApdu++ = 0x01;     //has mac
            *pApdu++ = DL698AL_APDU_TAG_SECRSP_MAC;
            *pApdu++ = DL698AL_MAC_LEN;
            Std_Memcpy(pApdu, pRxTemp + RxLen, DL698AL_MAC_LEN);
            apduLen = objLen + RxLen + DL698AL_MAC_LEN + 5; //or 3?
            break;
        }
        case (0x02): //明文+RN_MAC,用于主动上报
        {
            *pApdu++ = DL698AL_APDU_TAG_SECRSP_PT;
            objLen = fnDL698AL_asn1_set_ObjCnt(dataLen, pApdu);
            pApdu += objLen;
            Std_Memcpy(pApdu, pTxTemp, dataLen);

            ret = fnEsamOp_Get_PlainData_RN_Mac(pTxTemp, dataLen, &rn_max[0]);  //计算明文数据MAC
            if (ret == ERROR)
            {
                //error
                Std_Memset(&rn_max[0], 0x00, 12);
                rn_max[0] = 0x12;
                rn_max[1] = 0x34;
                rn_max[12] = 0xA0;
                rn_max[13] = 0xB0;
                ret = SUCCESS;
            }
            pApdu += dataLen;
            *pApdu++ = 2;    //rn+ mac
            *pApdu++ = 12;   //RN长度
            Std_Memcpy(pApdu, &rn_max[0], 12);
            pApdu += 12;
            *pApdu++ = DL698AL_MAC_LEN;
            Std_Memcpy(pApdu, &rn_max[12], DL698AL_MAC_LEN);
            apduLen = objLen + dataLen + 16 + 5; //or 3?

            break;
        }
        default:
            ret = ERROR;  //other are all error
            break;
    }

    fnDl698_Buffer_Free(pTxTemp);//
    fnDl698_Buffer_Free(pRxTemp);//

    if (ret == SUCCESS)
    {
        gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left  = 0;
        gDl698AL_Server.pAlChan[chan].apdu_tx_buf.right =  apduLen;
        //gDl698AL_Server.pAlChan[chan].apdu_tx_buf.data  =  ;  //no change
    }
    else
    {
        //apduLen = 0;  //不返回数据

        /////////////APDU组帧返回ESAM验证出错
        pApdu = gDl698AL_Server.pAlChan[chan].apdu_tx_buf.data;
        *pApdu++ = 0x90;
        *pApdu++ = 0x02;
        *pApdu++ = 0x16;
        *pApdu = 0x00;
        apduLen = 4;
        gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left  = 0;
        gDl698AL_Server.pAlChan[chan].apdu_tx_buf.right =  apduLen;
        /////////////APDU组帧返回ESAM验证出错
    }

    return apduLen;
    #endif
}

#ifdef _WIN32
/*********************************************************************
* @fn      fnDl698_GetValueTest
*
* @brief
*
* @param
*
* @return
*/
u8 fnDl698_GetValueTest(u16 *parLen, u8  *pRetBuf, u16 *retLen, u8 *blockRsp)
{
    u16 datalen = 4, i = 0;
    *parLen = 0;
    //*retLen = 1 + datalen;
    *retLen = 2 + datalen;
    *pRetBuf++ = 1;//data
    *pRetBuf++ = 0x06;//start
    for (i = 1; i <= datalen; i++)
    {
        *pRetBuf++ = (u8)i;
    }
    //*pRetBuf = 0xAA;//end
    *blockRsp = false;
    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************
* @fn      fnDl698_SetValueTest
*
* @brief
*
* @param
*
* @return
*/

u8 fnDl698_SetValueTest(
    u32  OAD,          //oad
    u16  classId,      //class id
    u8  *pParBuf,      //parameter buffer
    u16 *parLen        //parameter length ，已处理的参数数据长度
)
{
    *parLen = 3;
    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************
* @fn      fnDl698_ActMethTest
*
* @brief
*
* @param
*
* @return
*/
u8 fnDl698_ActMethTest(
    u32  OMD,        //OMD
    u16  classId,    //class id
    u8  *pParBuf,    //parameter buffer
    u16 *parLen,     //parameter length ，已处理的参数数据长度
    u16  retMaxLen,  //return result buffer max length
    u8  *pRetBuf,    //return result buffer
    u16 *retLen      //return result buffer length
)
{
    u8 datalen = 10, i = 0;
    *parLen = 2;
    for (i = 0; i < datalen; i++)
    {
        *pRetBuf++ = i;
    }
    *retLen = (u16)datalen;
    return DATA_ACCESS_RESULT_SUC;
}

u8 fnDl698_Chk_Symm(u8 *SeqEncry, u8 *SeqSign, u8 *ResRn, u8 *ResSign)
{
    return SUCCESS;
}

u8 fnDl698_Chk_passwd(u8 Chan, u8* pPwd, u8 PwdLen)
{
    return SUCCESS;
}

u8 fnDl698_SafetyCertiHandle(
    u8   req_type,   //请求类型
    u32  OMD,        //OMD
    u8  *pParBuf,    //parameter buffer
    u8  *pRetBuf,    //return result buffer
    u16 *retLen      //return result buffer length
)
{
    return 0;
}

u8 fnDl698_GetFlwRptFlag(u8 chan)
{
    return 1;
}

//跟随上报信息格式为OAD+01(数据)+类型(如06)+数据
void fnDl698_FlwRptValue(
    u16  retMaxLen,     //return result buffer max length，表返回的数据长度必须<= retMaxLen
    u8  *pRetBuf,       //return result buffer
    u16 *retLen         //return result buffer length
)
{
    u8  i = 0;
    u16 datalen = 10;
    for (i = 0; i < datalen; i++)
        if (i == 4)     //OAD后面应该是DAR(0)或数据(1)
        {
            *pRetBuf++ = 1;
        }
        else
        {
            *pRetBuf++ = i;
        }
    *retLen = (u16)datalen;
    return;
}

VOID fnDl698AL_EvtNotify(u8 chan, u16 event_value)
{
    return;
}
#endif

/*********************************************************************
* @fn      fnDl698AL_Get_OISec
*
* @brief   获取指定OI的安全模式参数
*
* @param   oi 对象标识
*
* @return  16bit安全模式参数，格式见附录F；OI不支持则返回0xFFFF
*/
u16 fnDl698AL_Get_OISec(u16 oi)
{
    #ifdef _WIN32
    return 0;
    #else
    u16 res;
    res = fnRead_FormulationSecPar(oi);
    if (res == 0xFFFF)
    {
        res = fnRaed_DefaultSecPar(oi);
    }
    return res;
    #endif
}

/*********************************************************************
* @fn      fnDl698AL_Get_OIOpSec
*
* @brief   获取指定操作下OI的安全模式参数
*
* @param    oi 对象标识
            op 操作类型:
                DL698AL_APDU_TAG_GETREQ
                DL698AL_APDU_TAG_SETREQ
                DL698AL_APDU_TAG_ACTREQ
              transfer_sec=8  明文； transfer_sec=1  明文+RN； transfer_sec=0  明文+SID MAC
*         transfer_sec=0x13  密文+SID； transfer_sec=0x10 密文+SID MAC
* @return  true: transfer_sec <= 显式或默认安全模式权限,通讯传输权限合法，允许读取
*          false: transfer_sec > 显式或默认安全模式权限,通讯传输权限非法，不允许读取
*/
u8 fnDl698AL_Get_OIOpSec(u16 oi, u8 op, u8 transfer_sec)
{
    u16 secTemp;
    u8 offset, sectype;
    u8 OpSec ;

    if (fnRead_SecurtyStatus() == true)
    {
        return true;
    }

    //----0x08=明文 -------
    //----0x04=明文+数据验证码--------
    //----0x02=密文  -------
    //---- 0x01=密文+数据验证码-------
    secTemp = fnDl698AL_Get_OISec(oi);

    switch (op)
    {
        case (DL698AL_APDU_TAG_GETREQ):
            offset = 12;
            if (secTemp == 0xFFFF) //模式字中未有明确要求的按明文+MAC读取
            {
                secTemp = 0x4000;
            }
            break;

        case (DL698AL_APDU_TAG_SETREQ):
            offset =  8;
            if (secTemp == 0xFFFF) //模式字中未有明确要求的按密文+MAC设置
            {
                secTemp = 0x0100;
            }
            break;

        case (DL698AL_APDU_TAG_ACTREQ):
            offset =  4;
            if (secTemp == 0xFFFF) //模式字中未有明确要求的按密文+MAC设置
            {
                secTemp = 0x0010;
            }
            break;
        default :
            return false;
    }
    OpSec = (secTemp >> offset) & 0x0F;

    //----------通讯下方安全认证方式转换与默认定义格式一致------------------
    if ((transfer_sec == 0x01) || (transfer_sec == 0x00)) //明文+RN   明文+SIDMAC
    {
        sectype = 0x04;
    }
    else if (transfer_sec == 0x13)
    {
        sectype = 0x02;
    }
    else if (transfer_sec == 0x10)
    {
        sectype = 0x01;    //存储到连接信息里面
    }
    else
    {
        sectype = 0x08;    //纯明文
    }

    if (sectype > OpSec)
    {
        return false;
    }

    return true;
}

/*********************************************************************
* @fn      fnDl698AL_Cmp_OISec
*
* @brief   比较两个安全模式参数，
*
* @param   sec1 安全模式参数1， sec2 安全模式参数2 ，都是低4bit有效
*
* @return  如果sec1要求的安全等级高于sec2，则返回1；如果sec1=sec2，则返回0；否则返回-1
*/
#define DL698AL_SECMASK_PT    3
#define DL698AL_SECMASK_PTMAC 2
#define DL698AL_SECMASK_CT    1
#define DL698AL_SECMASK_CTMAC 0
//#define fnDl698AL_Cmp_OISec(sec1,sec2) ((sec1)>(sec2) ? 1 : (sec1)==(sec2) ? 0 : (-1))
/*s8 fnDl698AL_Cmp_OISec(u8 sec1,u8 sec2)
{
}*/

/*********************************************************************************************************
** Function name:    fnDl698AL_Check_AddrType
** Descriptions:     判断通讯地址类型合法性
**
**
**
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
u8 fnDl698AL_Check_AddrType(u16 OI,  u8  Aptu_Tag, u8 AddrType)
{
    if (Aptu_Tag == DL698AL_APDU_TAG_GETREQ)
    {
        return  true;
    }
    else if ((Aptu_Tag == DL698AL_APDU_TAG_SETREQ) || (Aptu_Tag == DL698AL_APDU_TAG_CONREQ))
    {
        if (AddrType == DL698DL_SERVER_ADDR_TYPE_UNICAST) //设置参数只能用单地址
        {
            return  true;
        }
        else
        {
            return  false;
        }
    }
    else if (Aptu_Tag == DL698AL_APDU_TAG_ACTREQ)
    {
        if ((OI == 0x4000) || ((OI & 0xFFF0) == 0xF200) || ((OI & 0xFFF0) == 0xF300) || ((OI & 0xFFF0) == 0xF301))
        {
            return  true;
        }
        else
        {
            if (AddrType == DL698DL_SERVER_ADDR_TYPE_UNICAST) //只支持单地址操作
            {
                return  true;
            }
            else
            {
                return  false;
            }
        }
    }
    else
    {
        return  true;
    }
}

/*********************************************************************************************************
** Function name:    fnDl698AL_Check_OMDSec
** Descriptions:
**
**
**
** input parameters:
** output parameters:
** Returned value:      true = 支持明文操作，无需再判安全模式字；false=需判安全模式字
*********************************************************************************************************/
u8 fnDl698AL_Check_OMDSec(u32 OMD, u8 SecType, u8 tag_flag)
{
    u8 broat_type = 0, ret = false;
    u16 OI = (OMD >> 16 & 0xFFFF);

    if (tag_flag == DL698AL_APDU_TAG_GETREQ)
    {
        if (SecType == 0x08)
        {
            switch (OI) //红外未认证前只允许读取如下几个数据
            {
                case 0x0000:  //组合有功
                case 0x0010:  //正向有功
                case 0x0020:  //反向有功
                case 0x0050:  /*"第1象限无功"*/
                case 0x0060:  /*"第2象限无功"*/
                case 0x0070:  /*"第3象限无功"*/
                case 0x0080:  /*"第4象限无功"*/

                case 0x0100:  //基波组合有功
                case 0x0110:  //基波正向有功
                case 0x0120:  //基波反向有功
                case 0x0130:  //基波组合无功1
                case 0x0140:  //基波组合无功2

                case 0x0200:  //谐波组合有功
                case 0x0210:  //谐波正向有功
                case 0x0220:  //谐波反向有功
                case 0x0230:  //谐波组合无功1
                case 0x0240:  //谐波组合无功2

                case 0x4001:  //通讯地址
                case 0x4002:  //表号
                case 0x4111:  //备案号
                case 0x4000:  //日期
                case 0x4003:  //客户编号
                case 0x2031:  //当前月用电量
                case 0x4804:  //周波传送开启
                case 0x40EE:  //管理模组费率电能备份

                case 0x4104:
                case 0x4105:
                case 0x4106:
                case 0x4107:
                case 0x4108:
                case 0x4109:
                case 0x410A:
                case 0x410B:

                    //----------
                    #if(METERTYPE == 2)
                case 0x2032:  //当前年用电量
                case 0x202c:  //剩余金额
                case 0x202d:  //透支金额
                    #endif
                case 0xF100:    //Esam
                case 0xF101:    //安全模式参数
                case 0xF213:
                    ret = true;
                    break;

                default:
                    ret = false;
                    break;
            }
        }
        else
        {
            ret = false;
        }
    }
    else if (tag_flag == DL698AL_APDU_TAG_SETREQ)
    {
        if (OI == 0x40EE) //管理模组费率电能备份
        {
            ret =  true;
        }
    }
    else if (tag_flag == DL698AL_APDU_TAG_ACTREQ)
    {
        switch (OMD)
        {
            case 0x80008300:
            case 0xF1000B00:
            case 0xF1000C00:
            case 0x20147F00: //计量状态字
            case 0x48047F00:
            case 0x48048000:
            case 0x30367F00://--升级事件的方法127----------
            case 0xF100FE00://-用于物联表管理模组把ESAM序列号发给计量模组，为物联表内部使用命令-----
            case 0x48057F00:
            case 0x48058000:// dyf add
                ret = true;
                break;
            case 0x40007F00://广播校时
            {
                if (SecType == 0x10)
                {
                    broat_type = 0x01;
                }
                else if (SecType == 0x08)
                {
                    broat_type = 0x08;
                }

                if (broat_type)
                {
                    fnWrite_Broatcast_SafetyType(broat_type);
                    ret = true;
                }
                break;
            }
            default:
                ret = false;
                break;
        }
    }
    return ret;
}

/*********************************************************************
* @fn      fnDl698AL_Check_ApduSec
*
* @brief   获取并返回APDU的安全模式参数，如果是LIST请求，则返回安全等级最高的
*
* @param   chan 通道编号
*
* @return  DATA_ACCESS_RESULT_SUC        权限检查通过
           DATA_ACCESS_RESULT_UNAVA      OI在OILIST中没有找到
           DATA_ACCESS_RESULT_SECNMATH   权限检查不通过
*/

#include "globals.h"

u8 fnDl698AL_Check_ApduSec(u8 chan, u8 tag, u8 tag2, u32 OMD)
{
    //  u8* pBuf = gDl698AL_Server.pAlChan[chan].apdu_rx_buf.data;
    u16 OI = (u16)(OMD >> 16);
    //   u16 offset = 0xFFFF;
    //   u16 ret = 0xFFFF;
    //   u8  seqnum = 0;
    //   u8 i;

    //   u8 secInfo = 0 ;
    //   u8 secInfoTemp = 0;
    sDl698AL_ObjInfo_TypeDef* pObj = &gDl698AL_Server.pAlChan[chan].apdu_rx_buf.obj;
    //    u32 OMD;
    sServerAddr_TypeDef *pframInfoAddr   =  &pDl698DL_Channel[chan].stRxFrameInfo.stSA;

    if (gDl698AL_Server.pAlChan[chan].sec_data.SecType == 0xFF) //MAC验证失败
    {
        return DATA_ACCESS_RESULT_ESAMFAIL;
    }

    if (fnDl698AL_Check_Auth(chan, tag, OMD) != DATA_ACCESS_RESULT_SUC) //身份认证权限失败
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    switch (tag)
    {
        case (DL698AL_APDU_TAG_GETREQ):
        {
            switch (tag2)
            {
                case (DL698AL_GETTYPE_NORMAL):
                case (DL698AL_GETTYPE_NORMALLIST):
                {
                    pObj->oi = OI;
                    if (fnDl698AL_Check_OIList(pObj) == 0xFFFF)
                    {
                        return DATA_ACCESS_RESULT_UNAVA;
                    }

                    if (fnDl698AL_Check_OMDSec(OMD, gDl698AL_Server.pAlChan[chan].sec_data.SecType, DL698AL_APDU_TAG_GETREQ) == false)
                    {
                        if (fnDl698AL_Get_OIOpSec(OI, DL698AL_APDU_TAG_GETREQ, gDl698AL_Server.pAlChan[chan].sec_data.SecType) == false)
                        {
                            return DATA_ACCESS_RESULT_SECNMATH;
                        }
                    }
                    break;
                }
                case (DL698AL_GETTYPE_RECORD):
                case (DL698AL_GETTYPE_RECORDLIST):  //记录型异常应答需RCSD信息，放到后面判断
                {
                    /*
                      pObj->oi = OI;
                      if(fnDl698AL_Check_OIList(pObj) == 0xFFFF)
                          return DATA_ACCESS_RESULT_UNAVA;

                      if(fnDl698AL_Get_OIOpSec(OI,DL698AL_APDU_TAG_GETREQ,gDl698AL_Server.pAlChan[chan].sec_data.SecType) == false)
                          return DATA_ACCESS_RESULT_SECNMATH;
                          */
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case (DL698AL_APDU_TAG_SETREQ):
        {
            switch (tag2)
            {
                case (DL698AL_SETTYPE_NORMAL):
                case (DL698AL_SETTYPE_NORMALLIST):
                case (DL698AL_SETTHENGETNORMALLIST):
                {
                    pObj->oi = OI;
                    if (fnDl698AL_Check_OIList(pObj) == 0xFFFF)
                    {
                        return DATA_ACCESS_RESULT_UNAVA;
                    }

                    if (fnDl698AL_Check_AddrType(OI, DL698AL_APDU_TAG_SETREQ, pframInfoAddr->ubAddrType) == false)
                    {
                        return DATA_ACCESS_RESULT_DENY;
                    }

                    if (fnDl698AL_Get_OIOpSec(OI, DL698AL_APDU_TAG_SETREQ, gDl698AL_Server.pAlChan[chan].sec_data.SecType) == false)
                    {
                        return DATA_ACCESS_RESULT_SECNMATH;
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case (DL698AL_APDU_TAG_ACTREQ): //三种ACT与SET对应操作封装长度一样
        {
            switch (tag2)
            {
                case (DL698AL_ACTTYPE_NORMAL):
                case (DL698AL_ACTTYPE_NORMALLIST):
                case (DL698AL_ACTTHENGETNORMALLIST):
                {
                    pObj->oi = OI;
                    if (fnDl698AL_Check_OIList(pObj) == 0xFFFF)
                    {
                        return DATA_ACCESS_RESULT_UNAVA;
                    }

                    if (fnDl698AL_Check_AddrType(OI, DL698AL_APDU_TAG_ACTREQ, pframInfoAddr->ubAddrType) == false)
                    {
                        return DATA_ACCESS_RESULT_DENY;
                    }

                    if (fnDl698AL_Check_OMDSec(OMD, gDl698AL_Server.pAlChan[chan].sec_data.SecType, DL698AL_APDU_TAG_ACTREQ) == false)
                    {
                        if (fnDl698AL_Get_OIOpSec(OI, DL698AL_APDU_TAG_ACTREQ, gDl698AL_Server.pAlChan[chan].sec_data.SecType) == false)
                        {
                            return DATA_ACCESS_RESULT_SECNMATH;
                        }
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;  //do nothing
    }

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************
* @fn      fnDl698AL_Resport_SecRsp
*
* @brief   将待发送的主动上报APDU进行加密和添加校验
*
* @param
*
* @return
*/
u16 fnDl698AL_Resport_SecRsp(u8 chan)
{
    u8 tag_sec = gDl698AL_Server.pAlChan[chan].sec_data.SecType;

    ErrorStatus ret;

    u8 rn_max[16];
    u16 apduLen = 0;
    u8* pTxTemp;

    u8  objLen;
    u16 dataLen = gDl698AL_Server.pAlChan[chan].apdu_tx_buf.right - gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left;
    u8* pData = &gDl698AL_Server.pAlChan[chan].apdu_tx_buf.data[gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left];
    u8* pApdu = gDl698AL_Server.pAlChan[chan].apdu_tx_buf.data;

    pTxTemp = (u8 *)fnDl698_Buffer_Alloc(DL698AL_ESAMBUF_MAXSIZE);

    Std_Memcpy(pTxTemp, pData, dataLen);
    *pApdu++ = DL698AL_APDU_TAG_SECREQ;
    switch (tag_sec)
    {
        case (0x02): //明文+RN_MAC,用于主动上报
        {
            *pApdu++ = DL698AL_APDU_TAG_SECRSP_PT;
            objLen = fnDL698AL_asn1_set_ObjCnt(dataLen, pApdu);
            pApdu += objLen;
            Std_Memcpy(pApdu, pTxTemp, dataLen);

            ret = fnEsamOp_Get_PlainData_RN_Mac(pTxTemp, dataLen, &rn_max[0]);  //计算明文数据MAC
            if (ret == ERROR)
            {
                //error
                Std_Memset(&rn_max[0], 0x00, 12);
                ret = SUCCESS;
            }
            pApdu += dataLen;
            *pApdu++ = 2;    //rn+ mac
            *pApdu++ = 12;   //RN长度
            Std_Memcpy(pApdu, &rn_max[0], 12);
            pApdu += 12;
            *pApdu++ = DL698AL_MAC_LEN;
            Std_Memcpy(pApdu, &rn_max[12], DL698AL_MAC_LEN);
            apduLen = objLen + dataLen + 16 + 5; //or 3?

            break;
        }
        default:
            ret = ERROR;  //other are all error
            break;
    }

    fnDl698_Buffer_Free(pTxTemp);//

    gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left  = 0;
    gDl698AL_Server.pAlChan[chan].apdu_tx_buf.right =  apduLen;

    return apduLen;
}
