/********************************************************************
Filename:       Dl698AL_Act.c
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
#include "Dl698AL_Act.h"
#include "Dl698_UserData.h"
#include "Dl698_Memory.h"
#include "Dl698AL_Get.h"
#include "Dl698AL_asn1.h"

static u8 fnDl698AL_BuildActRsp(u8 chan, u8 encode_type, u8 act_type, u8 oad_num, u8 dar);
/*********************************************************************
* PUBLIC FUNCTIONS
*/

/*********************************************************************
* @fn      fnDl698_AL_Act_Of_IC
*
* @brief   IC01 电能量接口类 act统一处理接口
*
* @param   chan 通道编号
*
* @return  处理结果，成功返回0
*/
u8 fnDl698_AL_Act_Of_IC(u8 chan)
{
    sDl698AL_ApduRBuf_TypeDef *buf_recv = &gDl698AL_Server.pAlChan[chan].apdu_rx_buf;
    sDl698AL_ApduSBuf_TypeDef *buf_send = &gDl698AL_Server.pAlChan[chan].apdu_tx_buf;
    sDl698AL_ObjInfo_TypeDef *pObj = &buf_recv->obj;
    u8 *pParBuf = &buf_recv->data[buf_recv->left];
    u8 *pRetBuf = &buf_send->data[buf_send->right];
    u16 ret_max_len = buf_send->size - buf_send->right - DL698AL_RESV_TIMETAG(chan) - DL698AL_RESV_REPORT;
    u16 par_len = 0, ret_len = 0;
    u8 ret = DATA_ACCESS_RESULT_SUC;

    #ifdef _WIN32
    ret = fnDl698_ActMethTest(pObj->oad_omd,
                              pObj->class_id,
                              pParBuf,
                              &par_len,
                              ret_max_len,
                              pRetBuf,
                              &ret_len);
    #else
    ret = fnDl698_ActMeth(pObj->oad_omd,
                          pObj->class_id,
                          pParBuf,
                          &par_len,
                          ret_max_len,
                          pRetBuf,
                          &ret_len);
    #endif
    //buf_recv->left += par_len;  //更新已处理了buffer长度
    buf_send->right += ret_len; //更新已填充的发送buffer的长度

    buf_recv->left += par_len;  //更新已处理了buffer长度

    return ret;
}

/*********************************************************************
* @fn      fnDl698AL_BuildActRsp
*
* @brief   Act Response命令封装接口
*
* @param   chan 通道编号
*
* @return  无返回值
*/
static u8 fnDl698AL_BuildActRsp(u8 chan, u8 encode_type, u8 act_type, u8 oad_num, u8 dar)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;
    u8 *send_data = NULL;
    u16 maxlen = 0, retlen = 0;

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
    if (encode_type == DL698_ACTRSP_ENCODE_HDR_PART)
    {
        UINT8_TO_STREAM(send_data, DL698AL_APDU_TAG_ACTRSP);     //封装actrsp
        UINT8_TO_STREAM(send_data, act_type);                    //封装acttype
        UINT8_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.piid); //封装piid
        if (act_type != DL698AL_ACTTYPE_NORMAL)
        {
            UINT8_TO_STREAM(send_data, oad_num);                //封装Sequence of
            buf_send->right++;
        }
        UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.oad_omd);//封装OAD
        buf_send->right += 7;
    }
    else if (encode_type == DL698_ACTRSP_ENCODE_LIST_PART)
    {
        UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.oad_omd);//封装OAD
        buf_send->right += 4;
    }
    else if (encode_type == DL698_ACTRSP_ENCODE_DAR_PART)
    {
        UINT8_TO_STREAM(send_data, dar);                           //封装DAR
        UINT8_TO_STREAM(send_data, 0);                             //封装选择DAR 0
        buf_send->right += 2;
    }
    else
    {
        maxlen = buf_send->size - buf_send->right - DL698AL_RESV_TIMETAG(chan);
        fnDl698AL_FlwRptPkg(chan, maxlen, send_data, &retlen); //封装FollowReport
        send_data += retlen;
        fnDl698AL_TimeTagPkg(chan, send_data); //封装TimeTag
        buf_send->right += retlen + DL698AL_RESV_TIMETAG(chan);
    }

    return SUCCESS;
}

/*********************************************************************
* @fn      fnDl698AL_ActReqHandle
*
* @brief   处理并回复Act Request命令
*
* @param   chan 通道编号
*
* @return  处理结果，成功返回0
*/
u8 fnDl698AL_ActReqHandle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;
    u8  *recv_data = NULL, act_type = 0, while_break = 0, oad_num = 1, temp_oad_num = 0, encode = 0;
    u8 res = DATA_ACCESS_RESULT_SUC;
    u8 secCheck = SUCCESS ;
    u16  pSrcLen = 0;
    fnDl698_al_debug("start to do with Act requact pkt...\n");

    if (pchan->blockInfo.block_flag != DL698AL_ACTTHENGET_BLOCKING)
    {
        //正常act包处理流程

        recv_data = &buf_recv->data[buf_recv->left + 1];
        encode = DL698_ACTRSP_ENCODE_HDR_PART;
        buf_recv->left++;
        // 2.解析类型
        STREAM_TO_UINT8(act_type, recv_data);

        // 3.解析并获取 ppid
        STREAM_TO_UINT8(buf_recv->obj.piid, recv_data);
        buf_recv->left += 2;

        // 4.若是list类型，则获取sequence of信息
        if (act_type != DL698AL_ACTTYPE_NORMAL)
        {
            STREAM_TO_UINT8(oad_num, recv_data);
            buf_recv->left++;
        }
    }
    else
    {
        //actthenget block处理流程
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
            encode = DL698_ACTRSP_ENCODE_LIST_PART;
        }
    }
    temp_oad_num = oad_num;
    while (!while_break)
    {
        // 1. 获取OI信息
        buf_recv->obj.oi = BUILD_U16(recv_data[1], recv_data[0]);//oi
        buf_recv->obj.attevt_id = recv_data[2] & 0x1F;
        STREAM_TO_UINT32(buf_recv->obj.oad_omd, recv_data); //存储OMD
        buf_recv->left += 4;

        // 2.IO权限合法性检查结果
        secCheck = fnDl698AL_Check_ApduSec(chan, DL698AL_APDU_TAG_ACTREQ, act_type, buf_recv->obj.oad_omd);

        //  3.构建 rsp部分信息
        if (fnDl698AL_BuildActRsp(chan, encode, act_type, oad_num, 0) != SUCCESS)
        {
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }

        //-5.时间标签无效优先应答---------------------
        if ((pchan->time_info.time_tag.check_timetag_result == DL698AL_TIMETAG_ERROR) ||
            (((buf_recv->obj.oi == 0x4300) || (buf_recv->obj.oi == 0x8000) || (buf_recv->obj.oi == 0x8001)) &&
             (pchan->time_info.time_tag.check_timetag_result != DL698AL_TIMETAG_SUCCESS)))  //------4300 操作指令必须带时间标签---
        {
            pSrcLen = fnDl698AL_GetData_Len(1, 0, &buf_recv->data[buf_recv->left]);
            buf_recv->left += pSrcLen;
            res = DATA_ACCESS_RESULT_TIMLAGERR;
        }
        //-6.IO合法性及安全权限合法性不正确时，按此结果应答-------------------
        else if ((secCheck != DATA_ACCESS_RESULT_SUC) && (buf_recv->obj.oad_omd != 0xF1000B00) &&
                 (buf_recv->obj.oad_omd != 0xF1000C00))  //红外认证不判安全权限
        {
            pSrcLen = fnDl698AL_GetData_Len(1, 0, &buf_recv->data[buf_recv->left]);
            buf_recv->left += pSrcLen;
            res = secCheck;
        }
        else if (((buf_recv->obj.oi == 0x4300) || (buf_recv->obj.oi == 0x8000) || (buf_recv->obj.oi == 0x8001)) &&
                 (fnCheck_nMacErr() == FALSE))  //-----当MAC验证次数大于200次时-远程控制，电表清零应答挂起---
        {
            pSrcLen = fnDl698AL_GetData_Len(1, 0, &buf_recv->data[buf_recv->left]);
            buf_recv->left += pSrcLen;
            res = DATA_ACCESS_RESULT_SUSPD;
        }
        else
        {
            buf_recv->obj.oi_list_index = fnDl698AL_Check_OIList(&buf_recv->obj);
            // 4.调用各class接口进行act操作 ，计算下一个OAD偏移地址
            res = fnDl698_AL_Act_Of_IC(chan);
        }

        #if (TAI_TI_CE_SHI_EN == 1)
        if (buf_recv->obj.oad_omd == 0xF2077F00)    // dyf test 物联表台体测试
        {
            res = 0;
        }
        #endif

        //----数据回抄，读取文件信息，红外认证正确时带数据内容--其他操作只需应答执行结果res-----------------------------
        if ((buf_recv->obj.oad_omd == 0xF1000300) || (buf_recv->obj.oad_omd == 0xF1000500) ||
            (buf_recv->obj.oad_omd == 0xF1000B00) || (buf_recv->obj.oad_omd == 0xF0010A00))   //红外认证，软件比对
        {
            if (res != DATA_ACCESS_RESULT_SUC)
            {
                fnDl698AL_BuildActRsp(chan, DL698_ACTRSP_ENCODE_DAR_PART, 0, 0, res);
            }
        }
        else
        {
            fnDl698AL_BuildActRsp(chan, DL698_ACTRSP_ENCODE_DAR_PART, 0, 0, res);
        }

        // 10. act then get需要转换Get操作
        if (act_type == DL698AL_ACTTHENGETNORMALLIST)
        {
            if (fnDl698AL_DelayHandle(chan, DL698AL_ACTTHENGET_BLOCKING, temp_oad_num) == 0)
            {
                //若不需延时，则继续执行get操作
                res = fnDl698AL_ThenGetReqHandle(chan);
            }
            else
            {
                //若需延时，则跳出后续操作
                return res;
            }
        }

        // 11.数据解析完毕，跳出set操作
        temp_oad_num--;
        if (temp_oad_num == 0)
        {
            while_break = 1;
        }
        else
        {
            encode = DL698_ACTRSP_ENCODE_LIST_PART;
            recv_data = &buf_recv->data[buf_recv->left];
        }
    }
    // 12.构建act rsp部分信息
    fnDl698AL_BuildActRsp(chan, DL698_ACTRSP_ENCODE_LAST_PART, 0, 0, 0);

    // 13.打上发包标志
    pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
    pchan->funcode = DL698AL_FUNCODE_DATAINTER;
    DL698AL_SET_SEND_FLAG(chan);
    return res;
}
