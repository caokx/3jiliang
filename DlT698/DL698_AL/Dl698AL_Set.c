/********************************************************************
Filename:       Dl698AL_Set.c
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"
#include "Dl698_Globals.h"
#include "Dl698AL_def.h"
#include "Dl698AL_Get.h"
#include "Dl698AL_Set.h"
#include "Dl698_UserData.h"
#include "Dl698_Memory.h"
#include "Dl698AL_asn1.h"

static u8 fnDl698AL_BuildSetRsp(u8 chan, u8 encode_type, u8 set_type, u8 oad_num, u8 dar);
/*********************************************************************
* PUBLIC FUNCTIONS
*/
/*********************************************************************
* @fn      fnDl698_AL_Set_Of_IC
*
* @brief   IC01 电能量接口类 set统一处理接口
*
* @param   chan 通道编号
*
* @return  处理结果，成功返回0
*/
u8 fnDl698_AL_Set_Of_IC(u8 chan)
{
    sDl698AL_ApduRBuf_TypeDef *buf_recv = &gDl698AL_Server.pAlChan[chan].apdu_rx_buf;
    sDl698AL_ObjInfo_TypeDef *pObj = &buf_recv->obj;
    u8 *pParBuf = &buf_recv->data[buf_recv->left];
    u16 par_len = 0;
    u8 ret = DATA_ACCESS_RESULT_SUC;

    #ifdef _WIN32
    ret = fnDl698_SetValueTest(pObj->oad_omd, pObj->class_id, pParBuf, &par_len);
    #else
    ret = fnDl698_SetValue(pObj->oad_omd, pObj->class_id, pParBuf, &par_len);
    #endif
    buf_recv->left += par_len;  //更新已处理了buffer长度

    return ret;
}

/*********************************************************************
* @fn      fnDl698AL_BuildSetRsp
*
* @brief   Set Response命令封装接口
*
* @param   chan 通道编号
*
* @return  无返回值
*/
static u8 fnDl698AL_BuildSetRsp(u8 chan, u8 encode_type, u8 set_type, u8 oad_num, u8 dar)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;
    u8 *send_data = NULL;
    u16 maxlen = 0, retlen = 0;

    //fnDl698_al_debug("build Set Rsp part %d\n",encode_type);

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
    if (encode_type == DL698_SETRSP_ENCODE_HDR_PART)
    {
        UINT8_TO_STREAM(send_data, DL698AL_APDU_TAG_SETRSP);   //封装setrsp
        UINT8_TO_STREAM(send_data, set_type);                  //封装settype
        UINT8_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.piid); //封装piid
        if (set_type != DL698AL_SETTYPE_NORMAL)
        {
            UINT8_TO_STREAM(send_data, oad_num);               //封装Sequence of
            buf_send->right++;
        }
        UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.oad_omd);//封装OAD
        buf_send->right += 7;
    }
    else if (encode_type == DL698_SETRSP_ENCODE_LIST_PART)
    {
        UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.oad_omd);//封装OAD
        buf_send->right += 4;
    }
    else if (encode_type == DL698_SETRSP_ENCODE_DATA_PART)
    {
        UINT8_TO_STREAM(send_data, dar);        //封装DAR
        buf_send->right++;
    }
    else
    {
        maxlen = buf_send->size - buf_send->right - DL698AL_RESV_TIMETAG(chan);
        //封装FollowReport
        fnDl698AL_FlwRptPkg(chan, maxlen, send_data, &retlen);
        send_data += retlen;

        //封装TimeTag
        fnDl698AL_TimeTagPkg(chan, send_data);
        buf_send->right += retlen + DL698AL_RESV_TIMETAG(chan);
    }
    return SUCCESS;
}

/*********************************************************************
* @fn      fnDl698AL_SetReqHandle
*
* @brief   处理并回复Set Request命令
*
* @param   chan 通道编号
*
* @return  处理结果，成功返回0
*/
u8 fnDl698AL_SetReqHandle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;
    u8  *recv_data = NULL, set_type = 0, while_break = 0, oad_num = 1, temp_oad_num = 0, encode = 0;
    u8 res = DATA_ACCESS_RESULT_SUC;
    u8 secCheck = SUCCESS;
    u16 pSrcLen;

    fnDl698_al_debug("start to do with Set requset pkt...\n");

    #ifdef DL698_THENGET_WITH_DELAY
    if (pchan->blockInfo.block_flag != DL698AL_SETTHENGET_BLOCKING)
    #endif
    {
        //正常set包处理流程

        // 1.预先获取IO权限合法性检查结果
        //secCheck = fnDl698AL_Check_ApduSec(chan);

        recv_data = &buf_recv->data[buf_recv->left + 1];
        encode = DL698_SETRSP_ENCODE_HDR_PART;
        buf_recv->left++;
        // 1.解析类型
        STREAM_TO_UINT8(set_type, recv_data);

        // 2.解析并获取 ppid
        STREAM_TO_UINT8(buf_recv->obj.piid, recv_data);
        buf_recv->left += 2;

        // 3.若是list类型，则获取sequence of信息
        if (set_type != DL698AL_SETTYPE_NORMAL)
        {
            STREAM_TO_UINT8(oad_num, recv_data);
            buf_recv->left++;
        }
    }
    #ifdef DL698_THENGET_WITH_DELAY
    else
    {
        //setthenget block处理流程
        //1.执行get操作
        res = fnDl698AL_ThenGetReqHandle(chan);
        buf_recv->left++;//跳过delay字段

        //2.获取上一次处理到的seq数
        oad_num = pchan->blockInfo.temp_seq_num;

        if ((res != DATA_ACCESS_RESULT_SUC) || (oad_num == 1))
        {
            while_break = 1;
            DL698AL_CLR_BLOCKINFO(chan);    //重置BLOCK相关信息
        }
        else
        {
            recv_data = &buf_recv->data[buf_recv->left];
            encode = DL698_SETRSP_ENCODE_LIST_PART;
        }
    }
    #endif
    temp_oad_num = oad_num;
    while (!while_break)
    {
        // 1.解析OAD，获取OI信息
        buf_recv->obj.oi = BUILD_U16(recv_data[1], recv_data[0]);//oi
        buf_recv->obj.attevt_id = recv_data[2] & 0x1F;

        STREAM_TO_UINT32(buf_recv->obj.oad_omd, recv_data); //存储OAD
        buf_recv->left += 4;

        secCheck = fnDl698AL_Check_ApduSec(chan, DL698AL_APDU_TAG_SETREQ, set_type, buf_recv->obj.oad_omd);

        // 2.构建set rsp部分信息
        if (fnDl698AL_BuildSetRsp(chan, encode, set_type, oad_num, 0) != SUCCESS)
        {
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }

        // 3.检查时间标签是否合法
        if (pchan->time_info.time_tag.check_timetag_result == DL698AL_TIMETAG_ERROR)
        {
            pSrcLen = fnDl698AL_GetData_Len(1, 0, &buf_recv->data[buf_recv->left]);
            buf_recv->left += pSrcLen;
            res = DATA_ACCESS_RESULT_TIMLAGERR;
        }
        // 4.
        else if (secCheck != DATA_ACCESS_RESULT_SUC)
        {
            pSrcLen = fnDl698AL_GetData_Len(1, 0, &buf_recv->data[buf_recv->left]);
            buf_recv->left += pSrcLen;
            res = secCheck;
        }
        // 5.
        else if (fnCheck_nMacErr() == FALSE)
        {
            pSrcLen = fnDl698AL_GetData_Len(1, 0, &buf_recv->data[buf_recv->left]);
            buf_recv->left += pSrcLen;
            res = DATA_ACCESS_RESULT_SUSPD;
        }
        else
        {
            // 6.检查IO权限合法性
            buf_recv->obj.oi_list_index = fnDl698AL_Check_OIList(&buf_recv->obj);
            // 7.调用各class接口进行set操作
            res = fnDl698_AL_Set_Of_IC(chan);
        }

        // 8.封装结果
        fnDl698AL_BuildSetRsp(chan, DL698_SETRSP_ENCODE_DATA_PART, 0, 0, res);

        // 9. set then get需要转换Get操作
        if (set_type == DL698AL_SETTHENGETNORMALLIST)
        {
            if (fnDl698AL_DelayHandle(chan, DL698AL_SETTHENGET_BLOCKING, temp_oad_num) == 0)
            {
                //若不需延时，则继续执行get操作
                res = fnDl698AL_ThenGetReqHandle(chan);
            }
            else
            {
                //若需延时，则跳出后续操作
                return DATA_ACCESS_RESULT_SUC;
            }
        }

        // 10.数据解析完毕，跳出set操作
        temp_oad_num--;
        if (temp_oad_num == 0)
        {
            while_break = 1;
        }
        else
        {
            encode = DL698_SETRSP_ENCODE_LIST_PART;
            recv_data = &buf_recv->data[buf_recv->left];
        }
    }
    // 11.构建act rsp部分信息
    fnDl698AL_BuildSetRsp(chan, DL698_SETRSP_ENCODE_LAST_PART, 0, 0, 0);

    // 12.打上发包标志
    pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
    pchan->funcode = DL698AL_FUNCODE_DATAINTER;
    DL698AL_SET_SEND_FLAG(chan);

    return res;
}
