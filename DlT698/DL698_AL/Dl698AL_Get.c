/********************************************************************
Filename:       Dl698AL_Get.c
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
#include "Dl698_UserData.h"
#include "Dl698_Memory.h"

static u8 fnDl698AL_BuildGetRsp(u8 chan, u8 encode_type, u8 get_type, u8 oad_num, u8 lastblock, u8 dar);
#ifdef DL698_GETBLOCK
static u8 fnDl698AL_GetNextReqHandle(u8 chan, u8 piid, u16 block_num);
#endif
//各IC单位及换算表声明
extern sDl698_UnitScaler_Typedef gDl698_UnitScaList_IC01[];
extern sDl698_UnitScaler_Typedef gDl698_HDRUnitScaList_IC01[];
extern sDl698_UnitScaler_Typedef gDl698_MantissaUnitScaList_IC01[];
extern sDl698_UnitScaler_Typedef gDl698_HDR2UnitScaList_IC01[];
extern sDl698_UnitScaler_Typedef gDl698_UnitScaList_IC02[];
extern sDl698_UnitScaler_Typedef gDl698_UnitScaList_IC03[];
extern sDl698_UnitScaler_Typedef gDl698_HDRUnitScaList_IC03[];
extern sDl698_UnitScaler_Typedef gDl698_UnitScaList_IC04[];
extern sDl698_UnitScaler_Typedef gDl698_HDRUnitScaList_IC04[];
extern sDl698_UnitScaler_Typedef gDl698_UnitScaList_IC05[];
extern sDl698_UnitScaler_Typedef gDl698_UnitScaList_IC06[];

/*********************************************************************
* PUBLIC FUNCTIONS
*/
u8 fnDl698_GetUnitScaler(u16 classId, u16 oi_list_index, u8 att_id, u16 ret_max_len, u8 *pRetBuf, u16 *retLen, u8 *blockRsq)
{
    sDl698_UnitScaler_Typedef* pUnitScaler = NULL;
    u8 res = DATA_ACCESS_RESULT_SUC;
    if (ret_max_len < 6)
    {
        *blockRsq = true;
        *retLen = 0;
    }
    else
    {
        switch (classId)
        {
            case (1):
                //oi_list_index /= 4;   //包含分相
                if (att_id == 3) //属性3
                {
                    pUnitScaler = gDl698_UnitScaList_IC01;
                }
                else if (att_id == 5) //属性5，扩展高精度换算及单位
                {
                    pUnitScaler = gDl698_HDRUnitScaList_IC01;
                }
                else if (att_id == 7) //属性7，尾数换算及单位
                {
                    pUnitScaler = gDl698_MantissaUnitScaList_IC01;
                }
                else if (att_id == 9) //属性9，扩展高精度2换算及单位
                {
                    pUnitScaler = gDl698_HDR2UnitScaList_IC01;
                }
                break;
                #if(nPhs==ThreePhs)
            case (2):
                if (att_id == 3)
                {
                    pUnitScaler = gDl698_UnitScaList_IC02;
                }
                break;
                #endif
            case (3):
                if (att_id == 3)
                {
                    pUnitScaler = gDl698_UnitScaList_IC03;
                }
                else if (((att_id == 4) && (oi_list_index == 0)) || ((att_id == 7) && (oi_list_index == 1))) //属性4，电压高精度；属性7，电流高精度
                {
                    pUnitScaler = gDl698_HDRUnitScaList_IC03;
                }
                break;
            case (4):
                if (att_id == 3)
                {
                    pUnitScaler = gDl698_UnitScaList_IC04;
                }
                else if ((att_id == 5) && (oi_list_index < 3)) //属性5，有功功率扩展精度
                {
                    pUnitScaler = gDl698_HDRUnitScaList_IC04;
                }
                break;
            case (5):
                if (att_id == 6) //仅class5的换算及单位在属性6中，其他class均在属性3中
                {
                    pUnitScaler = gDl698_UnitScaList_IC05;
                }
                break;
            case (6):
                if (att_id == 3)
                {
                    pUnitScaler = gDl698_UnitScaList_IC06;
                }
                break;
            default:
                ;
        }
        if (pUnitScaler == NULL)
        {
            res = DATA_ACCESS_RESULT_UNAVA;
            *pRetBuf++ = 0;//DAR
            *pRetBuf++ = res;//
            *retLen = 2;
        }
        else
        {
            *pRetBuf++ = 1;//data
            *pRetBuf++ = DTYPE_SCAUNIT;     //
            *pRetBuf++ = pUnitScaler[oi_list_index].scala & 0xFF;
            *pRetBuf++ = pUnitScaler[oi_list_index].unit & 0xFF;
            *retLen = 4;
        }
        *blockRsq = false;
    }
    return res;
}

/*********************************************************************************************************
** Function name:   fnDl698_GetLogicalName
** Descriptions:     读取逻辑名
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
u8 fnDl698_GetLogicalName(u16 OI, u16 oi_index, u16 ret_max_len, u8 *pRetBuf, u16 *retLen)
{
    u8 res = DATA_ACCESS_RESULT_SUC;

    if (oi_index == 0xFFFF)
    {
        res = DATA_ACCESS_RESULT_UNAVA;
        *pRetBuf++ = 0;//DAR
        *pRetBuf++ = res;//
        *retLen = 2;
    }
    else
    {
        *pRetBuf++ = 1;//data
        *pRetBuf++ = DTYPE_OCT_STR;     //
        *pRetBuf++ = 0x02;
        *pRetBuf++ = (u8)(OI >> 8);
        *pRetBuf++ = (u8)OI;
        *retLen = 5;
    }
    return res;
}

/*********************************************************************
* @fn      fnDl698_AL_Get_Of_IC
*
* @brief   IC接口类 get统一处理接口
*
* @param   chan 通道编号
*
* @return  处理结果，成功返回0
*/
u8 fnDl698_AL_Get_Of_IC(u8 chan)
{
    sDl698AL_ApduRBuf_TypeDef *buf_recv = &gDl698AL_Server.pAlChan[chan].apdu_rx_buf;
    sDl698AL_ApduSBuf_TypeDef *buf_send = &gDl698AL_Server.pAlChan[chan].apdu_tx_buf;
    sDl698AL_BlockInfo_TypeDef *pBlockInfo = &gDl698AL_Server.pAlChan[chan].blockInfo;
    sDl698AL_ObjInfo_TypeDef *pObj = &buf_recv->obj;
    u8 *pParBuf = NULL, blockReq = false, blockRsq = false;
    u8 *pRetBuf = &buf_send->data[buf_send->right];
    u16 ret_max_len = buf_send->size - buf_send->right - DL698AL_RESV_TIMETAG(chan) - DL698AL_RESV_REPORT;
    u16 par_len = 0, ret_len = 0;
    u8 ret = DATA_ACCESS_RESULT_SUC;

    if ((pObj->tag == DL698AL_GETTYPE_RECORD)
        || (pObj->tag == DL698AL_GETTYPE_RECORDLIST))
    {
        pParBuf = &buf_recv->data[buf_recv->left];
    }
    #ifdef DL698_GETBLOCK
    else if (pObj->tag == DL698AL_GETTYPE_NEXT)
    {
        blockReq = true;
        pObj = &gDl698AL_Server.pAlChan[chan].apdu_rx_buf_pend.obj;
    }
    #endif
    #ifdef _WIN32
    if (((pObj->class_id >= 1 && pObj->class_id <= 4) || (pObj->class_id == 6))
        && ((pObj->attevt_id == 3) || (pObj->attevt_id == 5)))
    {
        //
        ret = fnDl698_GetUnitScaler(pObj->class_id,
                                    pObj->oi_list_index,
                                    pObj->attevt_id,
                                    ret_max_len,
                                    pRetBuf,
                                    &ret_len,
                                    &blockRsq);
    }
    else if ((pObj->class_id == 5) && (pObj->attevt_id == 6))
    {
        //
        ret = fnDl698_GetUnitScaler(pObj->class_id,
                                    pObj->oi_list_index,
                                    pObj->attevt_id,
                                    ret_max_len,
                                    pRetBuf,
                                    &ret_len,
                                    &blockRsq);
    }
    #else
    #ifdef DL698_GST_TEST
    if ((pObj->tag == DL698AL_GETDI_TEST) || (pObj->tag == DL698AL_GETRECORDDI_TEST))
    {
        //OAD->DI TEST
        u32 OAD2 = 0xFFFFFFFF;
        if (pObj->tag == DL698AL_GETRECORDDI_TEST)
        {
            pParBuf = &buf_recv->data[buf_recv->left];
            STREAM_TO_UINT32(OAD2, pParBuf);
        }
        fnDl698_TestGetDI(pObj->oad_omd, OAD2, pRetBuf, &ret_len);
    }
    else if (pObj->tag == DL698AL_GETOAD_TEST)
    {
        //DI->OAD TEST
        fnDl698_TestGetOAD(pObj->oad_omd, pRetBuf, &ret_len);
    }
    else if (((pObj->class_id >= 1 && pObj->class_id <= 4) || (pObj->class_id == 6))
             && ((pObj->attevt_id == 3) || (pObj->attevt_id == 5)))
    {
        //
        ret = fnDl698_GetUnitScaler(pObj->class_id,
                                    pObj->oi_list_index,
                                    pObj->attevt_id,
                                    ret_max_len,
                                    pRetBuf,
                                    &ret_len,
                                    &blockRsq);
    }
    else if ((pObj->class_id == 5) && (pObj->attevt_id == 6))
    {
        //
        ret = fnDl698_GetUnitScaler(pObj->class_id,
                                    pObj->oi_list_index,
                                    pObj->attevt_id,
                                    ret_max_len,
                                    pRetBuf,
                                    &ret_len,
                                    &blockRsq);
    }
    #else
    if (((pObj->class_id == 1) && ((pObj->attevt_id == 3) || (pObj->attevt_id == 5) || (pObj->attevt_id == 7) || (pObj->attevt_id == 9)))
        || (((pObj->class_id > 1 && pObj->class_id <= 4) || (pObj->class_id == 6)) && (pObj->attevt_id == 3))
        || ((pObj->class_id == 4) && (pObj->attevt_id == 5))   //-----20040500 class4 有功功率扩展精度单位及换算-----
        || ((pObj->class_id == 3) && (pObj->attevt_id == 5) && (pObj->oi_list_index == 0)) //-----20000500 class3 电压扩展精度---
        || ((pObj->class_id == 3) && (pObj->attevt_id == 7) && (pObj->oi_list_index == 1))) //------20010700 class3 电流扩展精度---
    {
        //
        ret = fnDl698_GetUnitScaler(pObj->class_id,
                                    pObj->oi_list_index,
                                    pObj->attevt_id,
                                    ret_max_len,
                                    pRetBuf,
                                    &ret_len,
                                    &blockRsq);
    }
    else if ((pObj->class_id == 5) && (pObj->attevt_id == 6))
    {
        //
        ret = fnDl698_GetUnitScaler(pObj->class_id,
                                    pObj->oi_list_index,
                                    pObj->attevt_id,
                                    ret_max_len,
                                    pRetBuf,
                                    &ret_len,
                                    &blockRsq);
    }
    else if (pObj->attevt_id == 1)  //读取逻辑名
    {
        //
        ret = fnDl698_GetLogicalName(pObj->oi,
                                     pObj->oi_list_index,
                                     ret_max_len,
                                     pRetBuf,
                                     &ret_len);
    }
    #endif
    #endif
    else
    {
        #ifdef _WIN32
        ret = fnDl698_GetValueTest(&par_len, pRetBuf, &ret_len, &blockRsq);
        #else
        ret = fnDl698_GetValue(pObj->oad_omd,
                               pObj->class_id,
                               pObj->oi_list_index,
                               pParBuf,
                               &par_len,
                               ret_max_len,
                               pRetBuf,
                               &ret_len,
                               blockReq,
                               &blockRsq);
        #endif
    }

    if ((buf_send->right + ret_len) < gDl698AL_Server.pAlChan[chan].nego.apdu_size_deal)
    {
        buf_send->right += ret_len;    //更新已填充的发送buffer的长度
    }
    else
    {
        if (pObj->tag == DL698AL_GETTYPE_RECORD)            // dyf 读取记录数据如停电事件记录，若数据超最大BUFF，则返回DAR=03拒绝读写错误
        {
            buf_send->data[buf_send->right++] = 0x00;
            buf_send->data[buf_send->right++] = 0x00;
            buf_send->data[buf_send->right++] = 0x03;
        }
        else if (pObj->tag == DL698AL_GETTYPE_RECORDLIST)   // dyf 读Record List到某个记录数据长度超最大BUFF时，该记录返回DAR=03拒绝读写错误
        {
            buf_send->data[buf_send->right++] = 0x00;
            buf_send->data[buf_send->right++] = 0x00;
            buf_send->data[buf_send->right++] = 0x03;
        }
        else if (pObj->tag == DL698AL_GETTYPE_NORMALLIST)   // dyf 读Normal List到某个OAD数据长度超最大BUFF时，该OAD返回DAR=03拒绝读写错误
        {
            buf_send->data[buf_send->right++] = 0x00;
            buf_send->data[buf_send->right++] = 0x03;
        }
    }

    if (blockRsq == true)
    {
        pBlockInfo->get_next_wait = true; //打上等待get_next_wait标记
        pBlockInfo->block_flag = true;    //打上分帧标记
    }
    else
    {
        buf_recv->left += par_len;  //更新已处理了buffer长度
        pBlockInfo->get_next_wait = false;//最后block，清除等待get_next_wait标记
    }
    return ret;
}

/*********************************************************************
* @fn      fnDl698AL_BuildGetRsp
*
* @brief   Get Response命令封装接口
*
* @param   chan 通道编号
*
* @return  无返回值
*/
static u8 fnDl698AL_BuildGetRsp(u8 chan, u8 encode_type, u8 get_type, u8 oad_num, u8 lastblock, u8 dar)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;
    u8 *send_data = NULL;
    u16 maxlen = 0, retlen = 0;

    fnDl698_al_debug("build Get Rsp part %d\n", encode_type);

    //1.检查buffer是否存在，若不存在则申请发送buffer资源
    if (buf_send->data == NULL)
    {
        buf_send->data = (u8 *)fnDl698_Buffer_Alloc(DL698AL_GET_APDU_MAXSIZE(chan));
        if (buf_send->data == NULL)
        {
            return ERROR;
        }
        buf_send->left  = DL698AL_RESV_BLOCK;
        buf_send->right = DL698AL_RESV_BLOCK;
        buf_send->size  = DL698AL_GET_APDU_MAXSIZE(chan);
        fnDl698_memset(buf_send->data, 0, buf_send->size);
    }
    send_data = &buf_send->data[buf_send->right];

    // 2.根据封装类型进行相应封装流程
    if (encode_type == DL698_GETRSP_ENCODE_HDR_PART)
    {
        UINT8_TO_STREAM(send_data, DL698AL_APDU_TAG_GETRSP);  //封装getrsp
        UINT8_TO_STREAM(send_data, get_type);                 //封装gettype
        UINT8_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.piid); //封装piid
        if ((get_type == DL698AL_GETTYPE_NORMALLIST)
            || (get_type == DL698AL_GETTYPE_RECORDLIST))
        {
            UINT8_TO_STREAM(send_data, oad_num);             //封装Sequence of
            buf_send->right++;
        }
        UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.oad_omd);//封装OAD
        buf_send->right += 7;
    }
    #ifdef DL698_GETBLOCK
    else if (encode_type == DL698_GETRSP_ENCODE_BLOCK_HDR_PART)
    {
        if (get_type == DL698AL_GETRSPNEXTTYPE_DAR)
        {
            buf_send->left  = DL698AL_RESV_BLOCK;
            buf_send->right = DL698AL_RESV_BLOCK;
        }
        else
        {
            if (get_type == DL698AL_GETTYPE_NORMAL)
            {
                get_type = DL698AL_GETRSPNEXTTYPE_NORMAL;
                buf_send->left -= 5;
            }
            else if (get_type == DL698AL_GETTYPE_NORMALLIST)
            {
                get_type = DL698AL_GETRSPNEXTTYPE_NORMAL;
                buf_send->left -= 4;
            }
            else if (get_type == DL698AL_GETTYPE_RECORD)
            {
                get_type = DL698AL_GETRSPNEXTTYPE_RECORD;
                buf_send->left -= 5;
            }
            else
            {
                get_type = DL698AL_GETRSPNEXTTYPE_RECORD;
                buf_send->left -= 4;
            }
        }
        send_data = &buf_send->data[buf_send->left];

        UINT8_TO_STREAM(send_data, DL698AL_APDU_TAG_GETRSP);           //封装getrsp
        UINT8_TO_STREAM(send_data, DL698AL_GETTYPE_NEXT);              //封装getnext response
        UINT8_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.piid);       //封装piid
        UINT8_TO_STREAM(send_data, lastblock);                         //封装末帧标志
        UINT16_TO_STREAM(send_data, pchan->blockInfo.block_num);       //封装分帧序号
        UINT8_TO_STREAM(send_data, get_type);                          //封装getnextrsptype
        if (get_type != DL698AL_GETRSPNEXTTYPE_DAR)
        {
            UINT8_TO_STREAM(send_data, oad_num);                      //封装Sequence of
            UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf_pend.obj.oad_omd);//封装OAD
        }
        else
        {
            UINT8_TO_STREAM(send_data, dar);                           //封装DAR
            buf_send->right += 8;
        }
    }
    #endif
    else if (encode_type == DL698_GETRSP_ENCODE_LIST_PART)
    {
        UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.oad_omd);//封装OAD
        buf_send->right += 4;
    }
    else if (encode_type == DL698_GETRSP_ENCODE_DAR_PART)
    {
        if ((get_type == DL698AL_GETTYPE_RECORD) || (get_type == DL698AL_GETTYPE_RECORDLIST))
        {
            UINT8_TO_STREAM(send_data, 0);  //RCSD,SEQUENCE OF CSD [integer]
            buf_send->right++;
        }
        UINT8_TO_STREAM(send_data, 0);                             //封装选择DAR 0
        UINT8_TO_STREAM(send_data, dar);                           //封装DAR
        buf_send->right += 2;
    }
    else if (encode_type == DL698_GETRSP_ENCODE_SECERRDAR_PART)
    {
        UINT8_TO_STREAM(send_data, DL698AL_APDU_TAG_SECRSP);  //封装getrsp
        UINT8_TO_STREAM(send_data, 2);                             //封装选择DAR 0
        UINT8_TO_STREAM(send_data, dar);                           //封装DAR
        buf_send->right += 3;
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

#ifdef DL698_GETBLOCK
/*********************************************************************
* @fn      fnDl698AL_SendGetNextRsp
*
* @brief   回复Get Next Response命令
*
* @param   chan 通道编号
*
* @return  处理结果，成功返回0
*/
static void fnDl698AL_SendGetNextRsp(u8 chan, u8 temp_oad_num, u8 oad_num, u8 dar)
{
    sDl698AL_ChnInfo_TypeDef *pChan = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_BlockInfo_TypeDef *pBlockInfo = &pChan->blockInfo;
    u8 tag = 0, lastblock = false;

    pBlockInfo->temp_seq_num = temp_oad_num;
    pBlockInfo->block_num++;
    if (pBlockInfo->block_num == 1)
    {
        //若是首分片帧，则将当前活动rxbuf挂起，后重置新的活动rxbuf
        pChan->apdu_rx_buf_pend = pChan->apdu_rx_buf;
        DL698AL_CLR_RECV_FLAG(chan);
        pChan->apdu_rx_buf.obj.piid = pChan->apdu_rx_buf_pend.obj.piid;
    }
    if (pBlockInfo->get_next_wait == false)
    {
        //若是最后分片帧，则设置lastblock标志
        lastblock = true;
    }
    tag =  pChan->apdu_rx_buf_pend.obj.tag;
    oad_num = oad_num - temp_oad_num + 1;
    fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_BLOCK_HDR_PART, tag, oad_num, lastblock, dar); //封装Get分片帧头

    if (pBlockInfo->get_next_wait == false)
    {
        //是最后分片帧
        DL698AL_CLR_BLOCKINFO(chan);    //重置分片相关信息
        DL698AL_CLR_PEND_BUFFER(chan);  //重置挂起包信息
    }
    return;
}
#endif
/*********************************************************************
* @fn      fnDl698AL_GetReqHandle
*
* @brief   处理并回复Get Request命令
*
* @param   chan 通道编号
*
* @return  处理结果，成功返回0
*/
u8 fnDl698AL_GetReqHandle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;//指向当前活动的rxbuf
    u8 *recv_data = &buf_recv->data[buf_recv->left + 1];
    u8  get_type = 0, oad_num = 1, temp_oad_num = 0, encode = DL698_GETRSP_ENCODE_HDR_PART, lastblock = false;
    #ifdef DL698_GETBLOCK
    u16 block_num = 0;
    #endif
    u8 secCheck = SUCCESS, res = DATA_ACCESS_RESULT_SUC;

    fnDl698_al_debug("start to do with Get requget pkt...\n");

    // 1.预先获取IO权限合法性检查结果

    buf_recv->left++;
    // 2.解析类型
    STREAM_TO_UINT8(get_type, recv_data);
    buf_recv->obj.tag = get_type;

    // 3.解析并获取 ppid
    STREAM_TO_UINT8(buf_recv->obj.piid, recv_data);
    buf_recv->left += 2;

    #ifdef DL698_GETBLOCK
    // 4.若接收到GETNEXPKT,则走GETNEXT流程
    if (get_type == DL698AL_GETTYPE_NEXT)
    {
        STREAM_TO_UINT16(block_num, recv_data);
        res = fnDl698AL_GetNextReqHandle(chan, buf_recv->obj.piid, block_num);
        return res;
    }
    else
    {
        //5. 分片过程中来了个其他帧，把分片终止，处理新包优先级最高处理
        if (pchan->blockInfo.block_flag == true)
        {
            DL698AL_CLR_BLOCKINFO(chan);    //重置分片相关信息
            DL698AL_CLR_PEND_BUFFER(chan);  //重置挂起包信息
        }
    }
    #endif

    // 6.若是list类型，则获取sequence of信息
    if ((get_type == DL698AL_GETTYPE_NORMALLIST)
        || (get_type == DL698AL_GETTYPE_RECORDLIST))
    {
        STREAM_TO_UINT8(oad_num, recv_data);
        buf_recv->left++;
    }

    temp_oad_num = oad_num;
    while (temp_oad_num)
    {
        // 7.解析OAD，获取OI信息
        buf_recv->obj.oi = BUILD_U16(recv_data[1], recv_data[0]);//oi
        buf_recv->obj.attevt_id = recv_data[2] & 0x1F;
        STREAM_TO_UINT32(buf_recv->obj.oad_omd, recv_data); //存储OAD
        buf_recv->left += 4;

        secCheck = fnDl698AL_Check_ApduSec(chan, DL698AL_APDU_TAG_GETREQ, get_type, buf_recv->obj.oad_omd);

        // 8.构建get rsp部分信息
        if (fnDl698AL_BuildGetRsp(chan, encode, get_type, oad_num, lastblock, 0) != SUCCESS)
        {
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }

        // 10.检查时间标签是否合法
        if (pchan->time_info.time_tag.check_timetag_result == DL698AL_TIMETAG_ERROR)
        {
            fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_DAR_PART, get_type, 0, 0, DATA_ACCESS_RESULT_TIMLAGERR);
        }
        // 11.----------------
        else if (secCheck != DATA_ACCESS_RESULT_SUC)
        {
            fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_DAR_PART, get_type, 0, 0, secCheck);
        }
        else
        {
            buf_recv->obj.oi_list_index = fnDl698AL_Check_OIList(&buf_recv->obj);

            // 11.调用各class接口进行get操作
            res = fnDl698_AL_Get_Of_IC(chan);
            #ifdef DL698_GETBLOCK
            // 12.若需要分帧，则进入分帧流程
            if (pchan->blockInfo.block_flag == true)
            {
                fnDl698AL_SendGetNextRsp(chan, temp_oad_num, oad_num, 0);
                break;
            }
            #endif
        }
        // 13.数据解析完毕，跳出get操作
        temp_oad_num--;
        if (temp_oad_num != 0)
        {
            encode = DL698_GETRSP_ENCODE_LIST_PART;
            recv_data = &buf_recv->data[buf_recv->left];
        }
    }
    // 14.构建get rsp部分信息
    fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_LAST_PART, 0, 0, 0, 0);

    // 15.打上发包标志
    pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
    pchan->funcode = DL698AL_FUNCODE_DATAINTER;
    DL698AL_SET_SEND_FLAG(chan);

    return res;
}

/*********************************************************************
* @fn      fnDl698AL_ThenGetReqHandle
*
* @brief   处理并回复XX then Get Request命令
*
* @param   chan 通道编号
*
* @return  处理结果，成功返回0
*/
u8 fnDl698AL_ThenGetReqHandle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;
    u8 *recv_data = &buf_recv->data[buf_recv->left];
    u8 res = DATA_ACCESS_RESULT_SUC;
    u8 secCheck = SUCCESS ;

    // 1.解析OAD，获取OI信息
    buf_recv->obj.oi = BUILD_U16(recv_data[1], recv_data[0]);//oi
    buf_recv->obj.attevt_id = recv_data[2] & 0x1F;
    STREAM_TO_UINT32(buf_recv->obj.oad_omd, recv_data); //存储OAD
    buf_recv->left += 4;   //OAD
    buf_recv->left += 1;  //延时时间
    // 2.IO权限合法性检查结果
    secCheck = fnDl698AL_Check_ApduSec(chan, DL698AL_APDU_TAG_GETREQ, DL698AL_GETTYPE_NORMAL, buf_recv->obj.oad_omd);

    // 8.检查时间标签是否合法
    if (pchan->time_info.time_tag.check_timetag_result == DL698AL_TIMETAG_ERROR)
    {
        if (fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_LIST_PART, 0, 0, 0, 0) != SUCCESS)
        {
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }
        fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_DAR_PART, 0, 0, 0, DATA_ACCESS_RESULT_TIMLAGERR);
    }
    // 9.检查IO权限合法性
    else if (secCheck != DATA_ACCESS_RESULT_SUC)
    {
        if (fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_LIST_PART, 0, 0, 0, 0) != SUCCESS)
        {
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }
        fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_DAR_PART, 0, 0, 0, secCheck);
    }
    else
    {
        // 2.构建get rsp部分信息,填充OAD
        fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_LIST_PART, 0, 0, 0, 0);

        buf_recv->obj.oi_list_index = fnDl698AL_Check_OIList(&buf_recv->obj);
        // 5.调用各class接口进行get操作
        res = fnDl698_AL_Get_Of_IC(chan);
    }
    return res;
}

#ifdef DL698_GETBLOCK
/*********************************************************************
* @fn      fnDl698AL_GetNextReqHandle
*
* @brief   处理并回复Get Next Request命令
*
* @param   chan 通道编号
*
* @return  处理结果，成功返回0
*/
static u8 fnDl698AL_GetNextReqHandle(u8 chan, u8 piid, u16 block_num)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf_pend; //指向上次未处理完的Rxbuf
    u8 *recv_data = &buf_recv->data[buf_recv->left];
    u8  get_type = buf_recv->obj.tag, while_break = 0, oad_num = 1, temp_oad_num = 0, encode = DL698_GETRSP_ENCODE_HDR_PART;
    u8 res = DATA_ACCESS_RESULT_SUC;

    // 1.判断当前不处于分帧状态，或不处于等待GETNEXTREQ状态，或分帧序号与预期一致时拒绝该帧
    if ((pchan->blockInfo.block_flag == false)
        || (pchan->blockInfo.get_next_wait == false))
    {
        res = DATA_ACCESS_RESULT_NLGET;
    }
    else if (pchan->blockInfo.block_num != block_num)
    {
        res = DATA_ACCESS_RESULT_LGET;
    }

    if (res != DATA_ACCESS_RESULT_SUC)
    {
        encode = DL698_GETRSP_ENCODE_BLOCK_HDR_PART;
        get_type = DL698AL_GETRSPNEXTTYPE_DAR;
        if (fnDl698AL_BuildGetRsp(chan, encode, get_type, 0, true, (u8)res) != SUCCESS)
        {
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }
    }
    else
    {
        // 2.清除等待GETNEXTREQ状态标志
        pchan->blockInfo.get_next_wait = false;

        // 3.获取上一次处理到的seq数
        temp_oad_num = pchan->blockInfo.temp_seq_num;
        oad_num = temp_oad_num;
        while (!while_break)
        {
            // 4.解析OAD，获取OI信息
            buf_recv->obj.oi = BUILD_U16(recv_data[1], recv_data[0]);//oi
            buf_recv->obj.attevt_id = recv_data[2] & 0x1F;
            STREAM_TO_UINT32(buf_recv->obj.oad_omd, recv_data); //存储OAD
            buf_recv->left += 4;

            // 5.构建get rsp部分信息
            if (fnDl698AL_BuildGetRsp(chan, encode, get_type, oad_num, false, 0) != SUCCESS)
            {
                return DATA_ACCESS_AL_MEMALLOC_ERR;
            }
            else
            {
                // 11.调用各class接口进行get操作
                res = fnDl698_AL_Get_Of_IC(chan);

                // 12.若需要分帧，则进入分帧流程
                if (pchan->blockInfo.block_flag == true)
                {
                    fnDl698AL_SendGetNextRsp(chan, temp_oad_num, oad_num, 0);
                    break;
                }
                if (res != DATA_ACCESS_RESULT_SUC)
                {
                    //若是list性获取数据出错时仅回复到当前OAD，剩余OAD直接PASS
                    break;
                }
            }
            // 9.数据解析完毕，跳出get操作
            temp_oad_num--;
            if (temp_oad_num == 0)
            {
                while_break = 1;
            }
            else
            {
                encode = DL698_GETRSP_ENCODE_LIST_PART;
                recv_data = &buf_recv->data[buf_recv->left];
            }
        }
    }
    // 10.构建get rsp部分信息，封装上报信息及时间标签
    fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_LAST_PART, 0, 0, false, 0);

    // 11.打上发包标志
    pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
    pchan->funcode = DL698AL_FUNCODE_DATAINTER;
    DL698AL_SET_SEND_FLAG(chan);

    return res;
}
#endif
