/********************************************************************
Filename:       Dl698_AL.c
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"
#include "Dl698_Memory.h"
#include "Dl698_Globals.h"
#include "Dl698AL_def.h"
#include "Dl698AL_Report.h"
#include "Dl698_UserData.h"
#include <Dl698_EsamOp.h>
/*********************************************************************
* MACROS
*/
/** @defgroup DL698_AL_XXX
* @{
*/

/** @} End DL698_AL_XXX */

/*********************************************************************
* CONSTANTS
*/

/*********************************************************************
* TYPEDEFS
*/

/*********************************************************************
* GLOBAL VARIABLES
*/

/*********************************************************************
* EXTERNAL VARIABLES
*/

/*********************************************************************
* EXTERNAL FUNCTIONS
*/

/*********************************************************************
* LOCAL VARIABLES
*/

/*********************************************************************
* LOCAL FUNCTIONS
*/

/*********************************************************************
* PUBLIC FUNCTIONS
*/

/*********************************************************************
* @fn      fnDl698AL_ChkDl_Idle
*
* @brief   检查DL是否处于空闲状态，可以接收、发送帧
*
* @param   chan      通道编号
*
*
* @return  DL的状态，空闲返回0，非空闲返回1...255
*/
u8 fnDl698AL_ChkDl_Idle(u8 chan)
{
    return 0;
}

/*********************************************************************
* @fn      fnDl698AL_ChkAl_Idle
*
* @brief   检查AL是否处于空闲状态，可以接收、发送帧
*
* @param   chan      通道编号
*
*
* @return  AL的状态，空闲返回0，非空闲返回1...255
*/
u8 fnDl698AL_ChkAl_Idle(u8 chan)
{
    return 0;
}

/*********************************************************************
* @fn      fnDl698_RptRspValue
* @brief   将ReportRsp的回复信息发给电表
* @param   chan      通道编号
*
*          pBuffer   待发送信息的buf
*          BufferLen 待发送信息的长度
* @return  无
*/
VOID fnDl698_RptRspValue(u8 chan,  u8* pBuffer, u8* pOADNum)
{
    if (chan != SCOM_PORT_ZBCOM)
    {
        return;
    }

    fnDl698_ReportValue(pBuffer, pOADNum);

    return;
}

/*********************************************************************
* @fn      fnDl698AL_RptNotiToAl
* @brief   表端将要上报的数据传给AL层，此函数为AL层调用表端的函数
* @param   pBuffer  协议栈为此次上报事件分配的BUFFER起始地址
*          BufferLen
*          pBufLen  pBuffer的真实长度
* @return  处理结果，0 表示成功；非零表示失败；如果失败，再次上报则需要重新调用fnDl698AL_RptReqHandle再次分配BUFFER
*/
u8 fnDl698AL_RptNotiToAl(u8 chan, u16 dataLen)
{
    sDl698AL_ChnInfo_TypeDef* pchan = &gDl698AL_Server.pAlChan[chan];
    // sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;

    u8* send_data = &buf_send->data[buf_send->left];
    u16 op_len = 0;        //待上报数据帧总长度
    u8  result = DL698AL_RPTHANDLE_SUCC;       //上报通知处理结果，成功?

    // 4. 表将上报数据已经存入apdu_tx_buf,包括OAD个数、OAD及上传数据
    // 判断
    if (dataLen <= 4)    //至少应该是OAD个数、OAD加1字节数据，一共6字节
    {
        result = DL698AL_RPTHANDLE_LENFAULT;
        return result;
    }

    op_len = 3 + dataLen;   //包头3个字节加上报数据长度
    send_data += op_len;   //找到包尾指针

    // 5. 跟随上报信息
    *send_data++ = 0x00;    //跟随上报信息为空
    // 6. 时间标签
    *send_data++ = 0x00;      //时间标签为空
    op_len += 2;

    if (op_len > 0)
    {
        //buf_send->left = 0;
        buf_send->right = buf_send->left + op_len;
        pchan->funcode = DL698AL_FUNCODE_DATAINTER;
        pchan->dirprm  = DL698AL_DIRPRM_SERVREPORT;
        result = DL698AL_RPTHANDLE_SUCC;
        DL698AL_SET_SEND_FLAG(chan);
    }

    return result;
}

/*********************************************************************
* @fn      fnDl698AL_RptNotiHandle
*
* @brief   当有上报信息时，表端调用此函数进行异常情况判断并封发送包的前几个字节
*
* @param   chan         通道编号
*          rpt_type     上报类型，是ReportNotificationList还是ReportNotificationRecordList
*          repeat_flag  是否是重传帧，是为1,不是为0
*          pBufferAddr  协议栈为此次上报事件分配的BUFFER起始地址
*          BufLen       BUFFER最大长度
* @return  处理结果，成功返回0
*/

u8 fnDl698AL_RptNotiHandle(u8 chan, u8 rpt_type, u8 piid)
{
    sDl698AL_ChnInfo_TypeDef* pchan = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;

    u8  al_state = 0xFF;   //al状态，空闲为0
    u8  dl_state = 0xFF;   //dl状态，空闲为0
    //  static u8  rpt_piid = 0;   //存放上次report notification的piid，只初始化一次
    //    u16 op_len = 0;        //待上报数据帧总长度
    u8 result = DL698AL_RPTHANDLE_SUCC;       //上报通知处理结果，成功返回0
    u8 *send_data = NULL, blockRsp;
    u16 maxlen = 0, retlen = 0;

    dl_state = fnDl698AL_ChkDl_Idle(chan);
    al_state = fnDl698AL_ChkAl_Idle(chan);

    // 1. DL层busy，丢弃此上报
    if (dl_state != DL698AL_DL_IDLE)
    {
        result = DL698AL_RPTHANDLE_DLBUSY;
        return result;
    }

    // 2. AL层busy，丢弃此上报
    if (al_state != DL698AL_AL_IDLE)
    {
        result = DL698AL_RPTHANDLE_ALBUSY;
        return result;
    }

    // 3. 检查上报类型，若有误，丢弃此上报
    if ((rpt_type != RPTEVT_POWNDOWN) && (rpt_type != RPTEVT_POWNUP) && (rpt_type != RPTEVT_OTHER))
    {
        result = DL698AL_RPTHANDLE_TYPEFAULT;
        return result;
    }
    /*
    // 4. 若不是重传帧，则用之前的piid加1
    if(retrans_flag == 0)
    {
        rpt_piid = pchan->apdu_rx_buf.obj.piid + 1;//PIID-ACD,上次收到的piid加1，将此piid存下来以免下次需要重传
    }

    // 若是重传帧，则用上次的rpt_piid
    else if(retrans_flag == 1)
    {
    }
    else //重传标志出错
    {
        result = DL698AL_RPTHANDLE_RETRANFAULT;
        return result;
    }
    */

    if ((dl_state == DL698AL_DL_IDLE) && (al_state == DL698AL_AL_IDLE))     //AL和DL都空闲
    {
        // 5. 检查buffer是否存在，若不存在则申请发送buffer资源
        if (buf_send->data == NULL)
        {
            buf_send->data = (u8 *)fnDl698_Buffer_Alloc(DL698AL_APDU_MAXSIZE(chan));
            if (buf_send->data == NULL)
            {
                return DL698AL_RPTHANDLE_BUFINVALID;
            }
            buf_send->size = DL698AL_APDU_MAXSIZE(chan);
            fnDl698_memset(buf_send->data, 0, buf_send->size);
        }

        pDl698DL_Channel[chan].stScom.ucToStamp2 = SysStamp ? SysStamp : (SysStamp - 1);

        send_data = &buf_send->data[buf_send->right];

        *send_data++ = DL698AL_APDU_TAG_RPTNOTI;  //封装getrsp

        //封装gettype
        if ((rpt_type == RPTEVT_POWNDOWN) || (rpt_type == RPTEVT_POWNUP)) //掉电事件记录上报
        {
            *send_data++ = 0x02;
        }
        else   //其他事件记录上报
        {
            *send_data++ = 0x01;
        }

        *send_data++ = piid;  //封装piid

        buf_send->right += 3;

        //send_data = &buf_send->data[buf_send->right];

        fnReport_EvtData(send_data, &retlen, rpt_type, &blockRsp);

        buf_send->right += retlen; //更新已填充的发送buffer的长度
        send_data += retlen;
        retlen = 0;

        maxlen = buf_send->size - buf_send->right - DL698AL_RESV_TIMETAG(chan);

        fnDl698AL_FlwRptPkg(chan, maxlen, send_data, &retlen); //封装FollowReport
        send_data += retlen;
        buf_send->right += retlen;
        retlen = 0;

        retlen = fnDl698AL_TimeTagPkg(chan, send_data); //封装TimeTag
        buf_send->right += retlen;

        // 15.打上发包标志
        pchan->dirprm = DL698AL_DIRPRM_SERVREPORT;
        pchan->funcode = DL698AL_FUNCODE_DATAINTER;
        DL698AL_SET_SEND_FLAG(chan);
    }

    return result;
}

/*********************************************************************
* @fn      fnDl698AL_RptRspHandle
*
* @brief   处理并Report response语句
*
* @param   chan 通道编号
*
* @return  处理结果，成功返回0
*/

s8 fnDl698AL_RptRspHandle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef* pchan = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;

    u8* recv_data = &buf_recv->data[buf_recv->left];
    //  u8* data_confirm;
    //    u8 byte;
    s8 op_len = 0;
    //  u8 result = 0xFF;    //是否上报成功，成功置为0
    //  u16 length = 0;
    u8 oad_number = 0;

    // 1.解析tag
    recv_data++;                //ReportRsponse tag

    // 2.解析上报类型
    //byte = *recv_data++;        //Report type
    recv_data++;        //Report type
    buf_recv->left += 2;

    // 3.解析piid
    buf_recv->obj.piid = *recv_data++;  //piid
    buf_recv->left++;

    // 4.解析上报的回复的oad个数
    oad_number = *recv_data++;   //oad_number
    //buf_recv->left++;

    if ((buf_recv->left < buf_recv->right) && (op_len >= 0)) //left>=right则说明数据为空
    {
        //length = buf_recv->right - buf_recv->left;
        //length = oad_number * 4;
        /*
        if( length >= 4 )      //至少有一个OAD上传成功
        {
            result = 0x00;    //上报成功，result置为0
        }
        */
        //发给电表，recv_data为buf，length+1为长度，1为oad个数，length为oad总长度
        fnDl698_RptRspValue(chan, recv_data, &oad_number);
    }
    else
    {
        op_len = -DATA_ACCESS_RESULT_DENY;
    }

    return op_len;
}

u8 fnReportHandle(u8 chan, u8 rpt_type, u8 retrans_flag)
{
    u8 res;

    fnWDT_Restart();

    if (rpt_type != RPTEVT_POWNDOWN)
    {
        if (BSP_EASM_GetPower() == false) //ESAM电源关闭时需先打开
        {
            fnWDT_Restart();
            fnEsamOp_EsamInit();
        }
    }

    res = fnDl698AL_RptNotiHandle(chan, rpt_type, retrans_flag);

    if (res != DL698AL_RPTHANDLE_SUCC)
    {
        return ERROR;
    }

    DL698AL_CLR_RECV_FLAG(chan);

    if (rpt_type != RPTEVT_POWNDOWN)
    {
        gDl698AL_Server.pAlChan[chan].sec_data.SecType = 0x02;
        //加密
        fnDl698AL_Resport_SecRsp(chan);
    }

    return SUCCESS;
}
