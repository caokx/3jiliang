
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
#include "Dl698_UserData.h"
#include "Dl698AL_def.h"
#include "Dl698AL_Conn.h"
#include "Dl698AL_Report.h"
#include <App.h>

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
//extern ErrorStatus Rn8xxx_RTC_Read(u8 *Dst);
#ifdef _WIN32
#else
extern ErrorStatus fnEsamOp_CreatConnect(u8 *SessionData1, u8 *Mac1, u8 *SessionData2, u8 *Mac2, u8 CA);
#endif

#ifdef _WIN32
#else
extern u32 current_cout;
#endif

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
* @fn      fnDl698AL_Decode_conformance
*
* @brief   解析协议一致性及功能一致性
*
* @param   buf_recv 指向待解析数据的指针
*          nego     存放协商内容的结构体
*
* @return  无返回值
*/
void fnDl698AL_Decode_Conformance(u8* buf_recv, sDl698AL_Nego_TypeDef * nego)
{
    //    u8 conf1,conf2,conf3;

    //协议一致性解析，原始数据为从高字节到低字节

    STREAM_TO_UINT32(nego->protocol_conformance.protocolconformance_hi8, buf_recv);
    STREAM_TO_UINT32(nego->protocol_conformance.protocolconformance_lo4, buf_recv);

    //协议一致性解析，原始数据为从高字节到低字节

    STREAM_TO_UINT32(nego->function_conformance.functionconformance_hi16, buf_recv);
    STREAM_TO_UINT32(nego->function_conformance.functionconformance_hi12, buf_recv);
    STREAM_TO_UINT32(nego->function_conformance.functionconformance_lo8, buf_recv);
    STREAM_TO_UINT32(nego->function_conformance.functionconformance_lo4, buf_recv);
}

/*********************************************************************
* @fn      fnDl698AL_ConnRes
*
* @brief   对应用连接建立请求的回复
*
* @param   chan     通道
*          nego     存放协商内容的结构体
*          buffer   指向待回复数据的指针
*          result   连接建立结果
*          timetag_exist  表示收到的请求中是否含有时间标签，有为1，没有为0
*
* @return  op_len   回复的APDU帧长度
*/

u16 fnDl698AL_ConnRes(u8 chan, sDl698AL_Nego_TypeDef* nego, u8 result)
{
    u16 op_len = 0;
    u16 flwrpt_maxlen = 0;
    u16 flwrpt_retlen = 0;
    u16 timetag_retlen = 0;

    //u8* pApduLen;
    sDl698AL_ChnInfo_TypeDef  *pchan = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;
    u8 *buffer = NULL;
    u8  RN_Len;

    if (buf_send->data == NULL)
    {
        buf_send->data = (u8 *)fnDl698_Buffer_Alloc(DL698AL_APDU_MAXSIZE(chan));  //确定buffer长度
        if (buf_send->data == NULL)
        {
            return ERROR;
        }
        buf_send->size = DL698AL_APDU_MAXSIZE(chan);
        fnDl698_memset(buf_send->data, 0, buf_send->size);
    }
    buffer = &buf_send->data[buf_send->right];

    // Set CONNRES tag
    *buffer++ = DL698AL_APDU_TAG_CONRSP;    //connect.response tag
    //PIID-ACD
    *buffer++ = pchan->apdu_rx_buf.obj.piid;
    op_len += 2;

    //厂商版本信息
    fnGet_ConnServer(buffer);
    buffer += 32;

    op_len += 32;

    //商定的应用层协议版本号
    UINT16_TO_STREAM(buffer, DL698AL_PROTOCOL_VERSION);
    op_len += 2;

    /*
    //协议一致性与功能一致性
    //协议一致性，原始数据为从高字节到低字节
    UINT32_TO_STREAM(buffer, (DL698AL_PROTCFM_HI8B & nego->protocol_conformance.protocolconformance_hi8));
    UINT32_TO_STREAM(buffer, (DL698AL_PROTCFM_LO4B & nego->protocol_conformance.protocolconformance_lo4));
    op_len += 8;

    //功能一致性，原始数据为从高字节到低字节
    UINT32_TO_STREAM(buffer, (DL698AL_FUNCCFM_HI16B & nego->function_conformance.functionconformance_hi16));
    UINT32_TO_STREAM(buffer, (DL698AL_FUNCCFM_HI12B & nego->function_conformance.functionconformance_hi12));
    UINT32_TO_STREAM(buffer, (DL698AL_FUNCCFM_HI8B  & nego->function_conformance.functionconformance_lo8));
    UINT32_TO_STREAM(buffer, (DL698AL_FUNCCFM_LO4B  & nego->function_conformance.functionconformance_lo4));
    op_len += 16;
    */

    //协议一致性与功能一致性
    //协议一致性，原始数据为从高字节到低字节
    UINT32_TO_STREAM(buffer, DL698AL_PROTCFM_HI8B);
    UINT32_TO_STREAM(buffer, DL698AL_PROTCFM_LO4B);
    op_len += 8;

    //功能一致性，原始数据为从高字节到低字节
    UINT32_TO_STREAM(buffer, DL698AL_FUNCCFM_HI16B);
    UINT32_TO_STREAM(buffer, DL698AL_FUNCCFM_HI12B);
    UINT32_TO_STREAM(buffer, DL698AL_FUNCCFM_HI8B);
    UINT32_TO_STREAM(buffer, DL698AL_FUNCCFM_LO4B);
    op_len += 16;

    //服务器发送帧最大尺寸
    UINT16_TO_STREAM(buffer, gDl698AL_Server.user_para[chan].dl_size_tx);

    //服务器接收帧最大尺寸
    UINT16_TO_STREAM(buffer, gDl698AL_Server.user_para[chan].dl_size_rx);

    //服务器接收帧最大窗口尺寸
    *buffer++ = gDl698AL_Server.user_para[chan].apdu_window_size_rx;

    //服务器最大可处理APDU尺寸
    UINT16_TO_STREAM(buffer, gDl698AL_Server.user_para[chan].apdu_size);
    op_len += 7;

    //商定的应用连接超时时间，bit32
    UINT32_TO_STREAM(buffer, nego->timeout_nego);
    op_len += 4;

    //add by wj, if timetag error,the result is timetag
    if (pchan->time_info.time_tag.check_timetag_result == DL698AL_TIMETAG_ERROR) //若时间标签出错，则结果回复其他错误
    {
        *buffer++ = CONN_OTHERS_FAULT;
        op_len += 1;
    }
    else
    {
        //认证结果
        *buffer++ = result;   //接的处理连接结果
        op_len += 1;
    }

    /*
    //没有加认证附加消息
      *buffer++ = 0x00;

    //没有加跟随上报消息
      *buffer++ = 0x00;
      op_len += 1;
    */
    //先回复00，后面有了ESAM再回复RN和签名信息;
    //nego->auth_object = (eDl698ConnMechInfo_TypeDef)0;

    if (nego->auth_object == 1)   //一般密码，将密码存下来
    {
        //密码是否正确
        *buffer++ = 0x00;
        op_len += 1;
    }
    else if (nego->auth_object == 2)   //对称加密
    {
        RN_Len = gConnResRnLen & 0xFF;

        *buffer++ = 0x01;            //在RN长度前有个0x01
        *buffer++ = RN_Len;            //RN长度
        Std_Memcpy(buffer, pchan->sec_data.RN,  RN_Len);
        buffer += RN_Len;
        *buffer++ = 0x04;            //签名信息长度为0x4
        Std_Memcpy(buffer, pchan->sec_data.Sign, 4);  //签名信息长度为4bytes
        buffer += 4;
        op_len += RN_Len + 4 + 3;
    }
    else
    {
        *buffer++ = 0x00;
        op_len += 1;
    }

    //处理跟随信息
    flwrpt_maxlen = buf_send->size - op_len - DL698AL_RESV_TIMETAG(chan);
    fnDl698AL_FlwRptPkg(chan, flwrpt_maxlen, buffer, &flwrpt_retlen);

    buffer += flwrpt_retlen;
    op_len += flwrpt_retlen;

    //组包时间标签
    timetag_retlen = fnDl698AL_TimeTagPkg(chan, buffer);
    buffer += timetag_retlen;
    op_len += timetag_retlen;

    return op_len;
}

/*********************************************************************
* @fn      fnDl698AL_ConnHandle
*
* @brief   处理接收到的建立应用连接请求，包括解析请求和回复
*
* @param   chan 通道
*
* @return  是否建立连接成功，成功返回0, 失败返回非0
*/
u8 fnDl698AL_ConnHandle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;
    u8* recv_data = &buf_recv->data[buf_recv->left];
    u8 return_result = 0;   //用于此次handle的返回值
    u8 vert0, vert1; //,vert2,vert3;
    //    u16 i = 0;
    u8 result = CONN_SUCCESS;       //用于连接建立的结果
    u8 confirm_error = 0xFF;        //用于ConfirmedServiceError中表示错误原因
    u8* encrytext = NULL;
    u8* signature = NULL;
    //  u8* safety_par = NULL;  //安全参数指针，指向密文1+MAC1+MAC2的首地址
    u32 temp32;
    u8  tempCA, temp[8];
    sCommSize_TypeDef tempSize;
    //u8* ptemp = NULL;
    //u8* Conn_ret = NULL;
    //u16 Conn_retlen = 0;

    // 1. connect tag
    recv_data++;
    buf_recv->left++;
    // 判断tag是否错误，此处不判断也行，前面已经判断过
    // if(byte!=DL698AL_APDU_TAG_CONREQ) //0x02
    // {
    //     return_result = -1;
    //  result = CONN_OTHERS_FAULT;
    // }
    // 2.解析piid
    buf_recv->obj.piid = *recv_data++;
    buf_recv->left++;

    if (buf_recv->left < buf_recv->right) //left>=right则说明数据为空
    {
        // 3.解析期望的应用层版本号
        STREAM_TO_UINT16(pchan->nego.pro_version, recv_data);
        //判断版本号是否合法
        /*
        if( pchan->nego.pro_version > DL698AL_PROTOCOL_VERSION )
        {
           pchan->nego.pro_version = DL698AL_PROTOCOL_VERSION;
           result = CONN_PROTOCOL_UNMATCH;
        }
        else
        {
           result = CONN_SUCCESS;
        }
        */
        // 4.解析协议一致性和功能一致性
        fnDl698AL_Decode_Conformance(recv_data, &pchan->nego);  //协议一致性、功能一致性解析
        recv_data += 24;

        // 5.解析客户机发送帧最大尺寸
        STREAM_TO_UINT16(pchan->nego.apdu_size_tx_nego, recv_data);
        //与服务器协商后的结果存入apdu_size_tx_nego
        if (pchan->nego.apdu_size_tx_nego > gDl698AL_Server.user_para[chan].dl_size_tx)
        {
            pchan->nego.apdu_size_tx_nego = gDl698AL_Server.user_para[chan].dl_size_tx;
        }

        // 6.解析客户机接收帧最大尺寸
        STREAM_TO_UINT16(pchan->nego.apdu_size_rx_nego, recv_data);
        //与服务器协商后的结果存入apdu_size_rx_nego
        if (pchan->nego.apdu_size_rx_nego > gDl698AL_Server.user_para[chan].dl_size_rx)
        {
            pchan->nego.apdu_size_rx_nego = gDl698AL_Server.user_para[chan].dl_size_rx;
        }

        // 7. 解析客户机接收帧最大窗口尺寸
        vert0 = *recv_data++;
        pchan->nego.apdu_window_size_rx = vert0;
        //与服务器协商后的结果存入apdu_window_size_rx
        if (pchan->nego.apdu_window_size_rx > gDl698AL_Server.user_para[chan].apdu_window_size_rx)
        {
            pchan->nego.apdu_window_size_rx = gDl698AL_Server.user_para[chan].apdu_window_size_rx;
        }

        // 8. 解析客户机最大可处理的APDU尺寸
        STREAM_TO_UINT16(pchan->nego.apdu_size_deal, recv_data);
        //与服务器协商后的结果存入apdu_size_deal
        if (pchan->nego.apdu_size_deal > gDl698AL_Server.user_para[chan].apdu_size)
        {
            pchan->nego.apdu_size_deal = gDl698AL_Server.user_para[chan].apdu_size;
        }

        // 9. 解析期望的应用连接超时时间
        STREAM_TO_UINT32(pchan->nego.timeout_nego, recv_data);

        //与服务器协商后的结果存入timeout_nego
        //if( pchan->nego.timeout_nego > DL698AL_CONNECT_TIMEOUT )   //若应用连接超时时间大于7200s，则将7200s作为协商结果
        // {
        //   pchan->nego.timeout_nego = DL698AL_CONNECT_TIMEOUT;
        // }

        if (pDl698DL_Channel[chan].stRxFrameInfo.stSA.ubAddrType != DL698DL_SERVER_ADDR_TYPE_UNICAST)
        {
            result = CONN_OTHERS_FAULT;
        }

        tempCA = pDl698DL_Channel[chan].stRxFrameInfo.ucCA; //
        fnReadDlyTime_Esam(&temp32, tempCA, 1);   //读取会话门限值
        if (pchan->nego.timeout_nego > temp32)
        {
            pchan->nego.timeout_nego = temp32;
        }
        // 10. 解析认证请求对象，共多少个字节
        vert0 = *recv_data++;
        pchan->nego.auth_object = (eDl698ConnMechInfo_TypeDef)vert0;
        if (pchan->nego.auth_object == 1)   //一般密码，将密码存下来
        {
            //若是一般密码，首先应该有个密码长度吧，
            vert0 = *recv_data++;  //若有密码长度，则存于vert0中

            //-----判密码-------------
            Std_AsciiStrToHexStr(&temp[0], recv_data, 8);

            if (fnSecret_Verify(0, 0, &temp[0]) == ERROR)  //698固定用00级密码
            {
                //若密码错误则置
                if (Bkgrd.PubData.MtSysSta.SysStaBit.EsamErr == 1)
                {
                    result = CONN_ESAMEER_FAULT;
                }
                else
                {
                    result = CONN_PASSWORD_FAULT;
                }
            }
        }
        else if (pchan->nego.auth_object == 2)   //对称加密
        {
            vert0 = *recv_data++;    //密文长度
            encrytext =  recv_data;
            //safety_par = encrytext;  //先将安全认证参数指针指向密文1指针首地址
            recv_data += vert0;

            vert1 = *recv_data++;    //签名信息长度
            signature = recv_data;
            recv_data += vert1;

            #ifdef _WIN32
            confirm_error = fnDl698_Chk_Symm(encrytext, signature, pchan->sec_data.RN, pchan->sec_data.Sign);   //对称加密
            #else
            tempCA = pDl698DL_Channel[chan].stRxFrameInfo.ucCA; //
            confirm_error = fnEsamOp_CreatConnect(encrytext, signature, pchan->sec_data.RN, pchan->sec_data.Sign, tempCA);    //对称加密
            #endif
            if (confirm_error == ERROR)  //若结果为ERROR
            {
                //若对称解密错误则置 result = CONN_SYSDECRYP_FAULT;
                if (Bkgrd.PubData.MtSysSta.SysStaBit.EsamErr == 1)
                {
                    result = CONN_ESAMEER_FAULT;
                }
                else
                {
                    result = CONN_SYSDECRYP_FAULT;
                }
            }
        }
        else if (pchan->nego.auth_object == 0)   //公共连接
        {
            //*recv_data++;    //NULL
        }

        //加入认证请求处理

        //时间标签
        fnDl698AL_Decode_TimeTag(chan, recv_data);    //解析时间标签

        //回复给Connect.Response 给client端
        if ((buf_send->right = fnDl698AL_ConnRes(chan, &pchan->nego, result)) > 0)
        {
            fnEvtPrg_End();

            buf_send->left = 0;
            pchan->funcode = DL698AL_FUNCODE_DATAINTER;
            pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
            DL698AL_SET_SEND_FLAG(chan);
            fnDl698AL_GetCurrTime(&pchan->time_info.conn_time);      //更新建立连接时间
            return_result = 0;
            fnConnect_Secret(pchan->nego.timeout_nego, pchan->nego.auth_object);

            tempSize.apdu_window_size_rx = pchan->nego.apdu_window_size_rx;
            tempSize.apdu_size = pchan->nego.apdu_size_deal;
            tempSize.dl_size_rx = pchan->nego.apdu_size_rx_nego;
            tempSize.dl_size_tx = pchan->nego.apdu_size_tx_nego;
            fnWriteConnSize(&tempSize, chan, tempCA);
        }
        else
        {
            //报错
            return_result = CONN_OTHERS_FAULT;
        }
    }
    else
    {
        return_result = CONN_OTHERS_FAULT;
    }

    return return_result;
}

/*********************************************************************
* @fn      fnDl698AL_RlsHandle
*
* @brief   处理接收到的断开连接请求，包括解析请求和回复
*
* @param   chan 通道
*
* @return  reason ,正常为0，异常为-1
*/
s8 fnDl698AL_RlsHandle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;

    //u16 recv_left=buf_recv->left;
    //u16 recv_right=buf_recv->right;
    u8* recv_data = &buf_recv->data[buf_recv->left];
    //u8 timetag_flag = 0;
    u8* send_data = NULL;//=& buf_send->data[buf_send->left];
    //  u8 vert0,vert1;
    s16 op_len = 0;
    s8 reason = 1; //not-finished
    u16 flwrpt_maxlen = 0;
    u16 flwrpt_retlen = 0;
    u16 timetag_retlen = 0;
    u8 *safety_par = NULL;
    u8 *Rls_ret = NULL;
    u16 Rls_retlen = 0;

    recv_data++;
    buf_recv->left++;

    buf_recv->obj.piid = *recv_data++;
    //buf_recv->invoke_id= *recv_data++;
    buf_recv->left++;

    if (buf_recv->left <= buf_recv->right)
    {
        //时间标签
        fnDl698AL_Decode_TimeTag(chan, recv_data);    //解析时间标签
        reason = 0; //normal
        //fnDl698AL_Brk_Asso(chan,reason);
        fnDl698_SafetyCertiHandle(DL698AL_APDU_TAG_RLSREQ, 0, safety_par, Rls_ret, &Rls_retlen);
    }
    else
    {
        reason = -1;
        return reason;
    }

    // 1.检查buffer是否存在，若不存在则申请发送buffer资源
    if (buf_send->data == NULL)
    {
        buf_send->data = (u8 *)fnDl698_Buffer_Alloc(DL698AL_APDU_MAXSIZE(chan));
        if (buf_send->data == NULL)
        {
            return -1;
        }
        buf_send->size = DL698AL_APDU_MAXSIZE(chan);   //考虑响应包长度
        fnDl698_memset(buf_send->data, 0, buf_send->size);
    }
    send_data = &buf_send->data[buf_send->right];

    //生成RLRE回应APDU
    buf_send->left = 0;
    send_data = &buf_send->data[buf_send->left];
    *send_data++ = DL698AL_APDU_TAG_RLSRSP;    //RLSRE tag
    *send_data++ = buf_recv->obj.piid;    //piid
    *send_data++ = 0x00;    //value
    op_len = 3;           //RLSRE tag, piid 及 结果

    //处理跟随信息
    flwrpt_maxlen = buf_send->size - op_len - DL698AL_RESV_TIMETAG(chan);
    fnDl698AL_FlwRptPkg(chan, flwrpt_maxlen, send_data, &flwrpt_retlen);
    send_data += flwrpt_retlen;
    op_len += flwrpt_retlen;

    //组包时间标签
    timetag_retlen = fnDl698AL_TimeTagPkg(chan, send_data);
    send_data += timetag_retlen;
    op_len += timetag_retlen;

    buf_send->right = buf_send->left + op_len;
    pchan->funcode = DL698AL_FUNCODE_DATAINTER;
    pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
    DL698AL_SET_SEND_FLAG(chan);

    return ((reason == 0) ? 0 : (-1));
}

/*********************************************************************
* @fn      fnDl698AL_RlsConnPkg
*
* @brief   组主动断开应用连接通知包
*
* @param   chan           通道编号
*          buffer         发送包指针
*          Current_time   Current_time当前实时时间
*
* @return  返回包长度
*/

u16 fnDl698AL_RlsConnPkg(u8 chan, u8* buffer, sDl698date_time_s_TypeDef Current_time)
{
    sDl698AL_ChnInfo_TypeDef* pchan = &gDl698AL_Server.pAlChan[chan];
    //sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;
    u16 op_len = 0;
    u16 flwrpt_maxlen = 0;
    u16 flwrpt_retlen = 0;

    // RlsNoti tag
    *buffer++ = DL698AL_APDU_TAG_RLSRPT;    //connect.response tag
    //PIID-ACD
    *buffer++ = pchan->apdu_rx_buf.obj.piid + 1;
    op_len += 2;

    //应用连接建立时间date_time_s
    UINT8_TO_STREAM(buffer, DTYPE_DATETIME_S);   //add by wj
    UINT16_TO_STREAM(buffer, pchan->time_info.conn_time.year);
    UINT8_TO_STREAM(buffer, pchan->time_info.conn_time.month);
    UINT8_TO_STREAM(buffer, pchan->time_info.conn_time.day);
    UINT8_TO_STREAM(buffer, pchan->time_info.conn_time.hour);
    UINT8_TO_STREAM(buffer, pchan->time_info.conn_time.minute);
    UINT8_TO_STREAM(buffer, pchan->time_info.conn_time.second);
    op_len += 8;

    //服务器当前时间date_time_s
    UINT8_TO_STREAM(buffer, DTYPE_DATETIME_S);  //add by wj
    UINT16_TO_STREAM(buffer, Current_time.year);
    UINT8_TO_STREAM(buffer, Current_time.month);
    UINT8_TO_STREAM(buffer, Current_time.day);
    UINT8_TO_STREAM(buffer, Current_time.hour);
    UINT8_TO_STREAM(buffer, Current_time.minute);
    UINT8_TO_STREAM(buffer, Current_time.second);
    op_len += 8;

    //处理跟随信息
    flwrpt_maxlen = DL698AL_APDU_MAX_SIZE - op_len - DL698AL_RESV_TIMETAG(chan);
    fnDl698AL_FlwRptPkg(chan, flwrpt_maxlen, buffer, &flwrpt_retlen);
    buffer += flwrpt_retlen;
    op_len += flwrpt_retlen;

    //没有加时间标签
    *buffer++ = 0x00;
    op_len += 1;

    return op_len;
}

/*********************************************************************
* @fn      fnDl698AL_NotiRlsConnHandle
*
* @brief   主动上报断开连接请求给客户机，客户机不需回复，也不得拒绝
*
* @param   chan 通道
*
* @return  发送主动断开连接包成功返回0，否则返回非0
*         (如未建立应用连接、未超时等情况返回-1, 未成功获取实时时间返回1)
*/
s8 fnDl698AL_NotiRlsConnHandle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    //sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;

    //定义date_time_s类型临时变量用于当前时间
    sDl698date_time_s_TypeDef  Current_time;
    s8  result = -1;            //主动断开连接的处理结果，为0表示发送断开连接成功，为-1则表示未发送断开连接
    //因为没有建立连接或无法获取当前时间等原因

    if (pchan->time_info.conn_time.year != 0)      //没有建立连接，则无需判断是都需要主动断开应用连接
    {
        return result;
    }
    #ifdef _WIN32
    #else
    pchan->time_info.current_cout = current_cout;  //当前时间
    #endif

    //若RTC当前计数值减去最后一次数据交互的时间大于超时时间则发送主动断开连接包
    //if((pchan->time_info.current_cout - pchan->time_info.lastdata_cout) > (pchan->nego.timeout_nego))
    if (pchan->time_info.current_cout > 0)
    {
        if (DL698AL_BOOL_GETTIMEOUT(pchan->time_info.lastdata_cout, pchan->time_info.current_cout, pchan->nego.timeout_nego) == true)
        {
            if (buf_send->data == NULL)
            {
                buf_send->data = (u8 *)fnDl698_Buffer_Alloc(DL698AL_APDU_MAXSIZE(chan));
                if (buf_send->data == NULL)
                {
                    return -1;
                }
                buf_send->size = DL698AL_APDU_MAXSIZE(chan);
                fnDl698_memset(buf_send->data, 0, buf_send->size);
            }

            //获取当前时间
            fnDl698AL_GetCurrTime(&Current_time);
            //组包返回包长
            if ((buf_send->right = fnDl698AL_RlsConnPkg(chan, buf_send->data, Current_time)) > 0)
            {
                buf_send->left = 0;
                pchan->funcode = DL698AL_FUNCODE_DATAINTER;
                pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
                DL698AL_SET_SEND_FLAG(chan);
                result = 0;
            }
        }
        else    //若未超时返回1
        {
            result = 1;
        }
    }

    if (result == 0)     //断开连接数据包已经准备好了
    {
        fnDl698AL_Brk_Asso(chan);
    }

    return result;
}

/*********************************************************************
* @fn      fnDl698AL_ConnSuccess
*
* @brief
*
* @param   chan 通道
*
* @return  是否建立连接成功，成功返回0, 失败返回非0
*/
u8 fnDl698AL_ConnSuccess(u8 chan)
{
    return SUCCESS;
}
