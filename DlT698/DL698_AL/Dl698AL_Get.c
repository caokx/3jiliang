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
//��IC��λ�����������
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
                //oi_list_index /= 4;   //��������
                if (att_id == 3) //����3
                {
                    pUnitScaler = gDl698_UnitScaList_IC01;
                }
                else if (att_id == 5) //����5����չ�߾��Ȼ��㼰��λ
                {
                    pUnitScaler = gDl698_HDRUnitScaList_IC01;
                }
                else if (att_id == 7) //����7��β�����㼰��λ
                {
                    pUnitScaler = gDl698_MantissaUnitScaList_IC01;
                }
                else if (att_id == 9) //����9����չ�߾���2���㼰��λ
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
                else if (((att_id == 4) && (oi_list_index == 0)) || ((att_id == 7) && (oi_list_index == 1))) //����4����ѹ�߾��ȣ�����7�������߾���
                {
                    pUnitScaler = gDl698_HDRUnitScaList_IC03;
                }
                break;
            case (4):
                if (att_id == 3)
                {
                    pUnitScaler = gDl698_UnitScaList_IC04;
                }
                else if ((att_id == 5) && (oi_list_index < 3)) //����5���й�������չ����
                {
                    pUnitScaler = gDl698_HDRUnitScaList_IC04;
                }
                break;
            case (5):
                if (att_id == 6) //��class5�Ļ��㼰��λ������6�У�����class��������3��
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
** Descriptions:     ��ȡ�߼���
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
* @brief   IC�ӿ��� getͳһ����ӿ�
*
* @param   chan ͨ�����
*
* @return  ���������ɹ�����0
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
        || ((pObj->class_id == 4) && (pObj->attevt_id == 5))   //-----20040500 class4 �й�������չ���ȵ�λ������-----
        || ((pObj->class_id == 3) && (pObj->attevt_id == 5) && (pObj->oi_list_index == 0)) //-----20000500 class3 ��ѹ��չ����---
        || ((pObj->class_id == 3) && (pObj->attevt_id == 7) && (pObj->oi_list_index == 1))) //------20010700 class3 ������չ����---
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
    else if (pObj->attevt_id == 1)  //��ȡ�߼���
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
        buf_send->right += ret_len;    //���������ķ���buffer�ĳ���
    }
    else
    {
        if (pObj->tag == DL698AL_GETTYPE_RECORD)            // dyf ��ȡ��¼������ͣ���¼���¼�������ݳ����BUFF���򷵻�DAR=03�ܾ���д����
        {
            buf_send->data[buf_send->right++] = 0x00;
            buf_send->data[buf_send->right++] = 0x00;
            buf_send->data[buf_send->right++] = 0x03;
        }
        else if (pObj->tag == DL698AL_GETTYPE_RECORDLIST)   // dyf ��Record List��ĳ����¼���ݳ��ȳ����BUFFʱ���ü�¼����DAR=03�ܾ���д����
        {
            buf_send->data[buf_send->right++] = 0x00;
            buf_send->data[buf_send->right++] = 0x00;
            buf_send->data[buf_send->right++] = 0x03;
        }
        else if (pObj->tag == DL698AL_GETTYPE_NORMALLIST)   // dyf ��Normal List��ĳ��OAD���ݳ��ȳ����BUFFʱ����OAD����DAR=03�ܾ���д����
        {
            buf_send->data[buf_send->right++] = 0x00;
            buf_send->data[buf_send->right++] = 0x03;
        }
    }

    if (blockRsq == true)
    {
        pBlockInfo->get_next_wait = true; //���ϵȴ�get_next_wait���
        pBlockInfo->block_flag = true;    //���Ϸ�֡���
    }
    else
    {
        buf_recv->left += par_len;  //�����Ѵ�����buffer����
        pBlockInfo->get_next_wait = false;//���block������ȴ�get_next_wait���
    }
    return ret;
}

/*********************************************************************
* @fn      fnDl698AL_BuildGetRsp
*
* @brief   Get Response�����װ�ӿ�
*
* @param   chan ͨ�����
*
* @return  �޷���ֵ
*/
static u8 fnDl698AL_BuildGetRsp(u8 chan, u8 encode_type, u8 get_type, u8 oad_num, u8 lastblock, u8 dar)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;
    u8 *send_data = NULL;
    u16 maxlen = 0, retlen = 0;

    fnDl698_al_debug("build Get Rsp part %d\n", encode_type);

    //1.���buffer�Ƿ���ڣ��������������뷢��buffer��Դ
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

    // 2.���ݷ�װ���ͽ�����Ӧ��װ����
    if (encode_type == DL698_GETRSP_ENCODE_HDR_PART)
    {
        UINT8_TO_STREAM(send_data, DL698AL_APDU_TAG_GETRSP);  //��װgetrsp
        UINT8_TO_STREAM(send_data, get_type);                 //��װgettype
        UINT8_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.piid); //��װpiid
        if ((get_type == DL698AL_GETTYPE_NORMALLIST)
            || (get_type == DL698AL_GETTYPE_RECORDLIST))
        {
            UINT8_TO_STREAM(send_data, oad_num);             //��װSequence of
            buf_send->right++;
        }
        UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.oad_omd);//��װOAD
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

        UINT8_TO_STREAM(send_data, DL698AL_APDU_TAG_GETRSP);           //��װgetrsp
        UINT8_TO_STREAM(send_data, DL698AL_GETTYPE_NEXT);              //��װgetnext response
        UINT8_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.piid);       //��װpiid
        UINT8_TO_STREAM(send_data, lastblock);                         //��װĩ֡��־
        UINT16_TO_STREAM(send_data, pchan->blockInfo.block_num);       //��װ��֡���
        UINT8_TO_STREAM(send_data, get_type);                          //��װgetnextrsptype
        if (get_type != DL698AL_GETRSPNEXTTYPE_DAR)
        {
            UINT8_TO_STREAM(send_data, oad_num);                      //��װSequence of
            UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf_pend.obj.oad_omd);//��װOAD
        }
        else
        {
            UINT8_TO_STREAM(send_data, dar);                           //��װDAR
            buf_send->right += 8;
        }
    }
    #endif
    else if (encode_type == DL698_GETRSP_ENCODE_LIST_PART)
    {
        UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.oad_omd);//��װOAD
        buf_send->right += 4;
    }
    else if (encode_type == DL698_GETRSP_ENCODE_DAR_PART)
    {
        if ((get_type == DL698AL_GETTYPE_RECORD) || (get_type == DL698AL_GETTYPE_RECORDLIST))
        {
            UINT8_TO_STREAM(send_data, 0);  //RCSD,SEQUENCE OF CSD [integer]
            buf_send->right++;
        }
        UINT8_TO_STREAM(send_data, 0);                             //��װѡ��DAR 0
        UINT8_TO_STREAM(send_data, dar);                           //��װDAR
        buf_send->right += 2;
    }
    else if (encode_type == DL698_GETRSP_ENCODE_SECERRDAR_PART)
    {
        UINT8_TO_STREAM(send_data, DL698AL_APDU_TAG_SECRSP);  //��װgetrsp
        UINT8_TO_STREAM(send_data, 2);                             //��װѡ��DAR 0
        UINT8_TO_STREAM(send_data, dar);                           //��װDAR
        buf_send->right += 3;
    }
    else
    {
        maxlen = buf_send->size - buf_send->right - DL698AL_RESV_TIMETAG(chan);
        fnDl698AL_FlwRptPkg(chan, maxlen, send_data, &retlen); //��װFollowReport
        send_data += retlen;
        fnDl698AL_TimeTagPkg(chan, send_data); //��װTimeTag
        buf_send->right += retlen + DL698AL_RESV_TIMETAG(chan);
    }
    return SUCCESS;
}

#ifdef DL698_GETBLOCK
/*********************************************************************
* @fn      fnDl698AL_SendGetNextRsp
*
* @brief   �ظ�Get Next Response����
*
* @param   chan ͨ�����
*
* @return  ���������ɹ�����0
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
        //�����׷�Ƭ֡���򽫵�ǰ�rxbuf���𣬺������µĻrxbuf
        pChan->apdu_rx_buf_pend = pChan->apdu_rx_buf;
        DL698AL_CLR_RECV_FLAG(chan);
        pChan->apdu_rx_buf.obj.piid = pChan->apdu_rx_buf_pend.obj.piid;
    }
    if (pBlockInfo->get_next_wait == false)
    {
        //��������Ƭ֡��������lastblock��־
        lastblock = true;
    }
    tag =  pChan->apdu_rx_buf_pend.obj.tag;
    oad_num = oad_num - temp_oad_num + 1;
    fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_BLOCK_HDR_PART, tag, oad_num, lastblock, dar); //��װGet��Ƭ֡ͷ

    if (pBlockInfo->get_next_wait == false)
    {
        //������Ƭ֡
        DL698AL_CLR_BLOCKINFO(chan);    //���÷�Ƭ�����Ϣ
        DL698AL_CLR_PEND_BUFFER(chan);  //���ù������Ϣ
    }
    return;
}
#endif
/*********************************************************************
* @fn      fnDl698AL_GetReqHandle
*
* @brief   �����ظ�Get Request����
*
* @param   chan ͨ�����
*
* @return  ���������ɹ�����0
*/
u8 fnDl698AL_GetReqHandle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;//ָ��ǰ���rxbuf
    u8 *recv_data = &buf_recv->data[buf_recv->left + 1];
    u8  get_type = 0, oad_num = 1, temp_oad_num = 0, encode = DL698_GETRSP_ENCODE_HDR_PART, lastblock = false;
    #ifdef DL698_GETBLOCK
    u16 block_num = 0;
    #endif
    u8 secCheck = SUCCESS, res = DATA_ACCESS_RESULT_SUC;

    fnDl698_al_debug("start to do with Get requget pkt...\n");

    // 1.Ԥ�Ȼ�ȡIOȨ�޺Ϸ��Լ����

    buf_recv->left++;
    // 2.��������
    STREAM_TO_UINT8(get_type, recv_data);
    buf_recv->obj.tag = get_type;

    // 3.��������ȡ ppid
    STREAM_TO_UINT8(buf_recv->obj.piid, recv_data);
    buf_recv->left += 2;

    #ifdef DL698_GETBLOCK
    // 4.�����յ�GETNEXPKT,����GETNEXT����
    if (get_type == DL698AL_GETTYPE_NEXT)
    {
        STREAM_TO_UINT16(block_num, recv_data);
        res = fnDl698AL_GetNextReqHandle(chan, buf_recv->obj.piid, block_num);
        return res;
    }
    else
    {
        //5. ��Ƭ���������˸�����֡���ѷ�Ƭ��ֹ�������°����ȼ���ߴ���
        if (pchan->blockInfo.block_flag == true)
        {
            DL698AL_CLR_BLOCKINFO(chan);    //���÷�Ƭ�����Ϣ
            DL698AL_CLR_PEND_BUFFER(chan);  //���ù������Ϣ
        }
    }
    #endif

    // 6.����list���ͣ����ȡsequence of��Ϣ
    if ((get_type == DL698AL_GETTYPE_NORMALLIST)
        || (get_type == DL698AL_GETTYPE_RECORDLIST))
    {
        STREAM_TO_UINT8(oad_num, recv_data);
        buf_recv->left++;
    }

    temp_oad_num = oad_num;
    while (temp_oad_num)
    {
        // 7.����OAD����ȡOI��Ϣ
        buf_recv->obj.oi = BUILD_U16(recv_data[1], recv_data[0]);//oi
        buf_recv->obj.attevt_id = recv_data[2] & 0x1F;
        STREAM_TO_UINT32(buf_recv->obj.oad_omd, recv_data); //�洢OAD
        buf_recv->left += 4;

        secCheck = fnDl698AL_Check_ApduSec(chan, DL698AL_APDU_TAG_GETREQ, get_type, buf_recv->obj.oad_omd);

        // 8.����get rsp������Ϣ
        if (fnDl698AL_BuildGetRsp(chan, encode, get_type, oad_num, lastblock, 0) != SUCCESS)
        {
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }

        // 10.���ʱ���ǩ�Ƿ�Ϸ�
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

            // 11.���ø�class�ӿڽ���get����
            res = fnDl698_AL_Get_Of_IC(chan);
            #ifdef DL698_GETBLOCK
            // 12.����Ҫ��֡��������֡����
            if (pchan->blockInfo.block_flag == true)
            {
                fnDl698AL_SendGetNextRsp(chan, temp_oad_num, oad_num, 0);
                break;
            }
            #endif
        }
        // 13.���ݽ�����ϣ�����get����
        temp_oad_num--;
        if (temp_oad_num != 0)
        {
            encode = DL698_GETRSP_ENCODE_LIST_PART;
            recv_data = &buf_recv->data[buf_recv->left];
        }
    }
    // 14.����get rsp������Ϣ
    fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_LAST_PART, 0, 0, 0, 0);

    // 15.���Ϸ�����־
    pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
    pchan->funcode = DL698AL_FUNCODE_DATAINTER;
    DL698AL_SET_SEND_FLAG(chan);

    return res;
}

/*********************************************************************
* @fn      fnDl698AL_ThenGetReqHandle
*
* @brief   �����ظ�XX then Get Request����
*
* @param   chan ͨ�����
*
* @return  ���������ɹ�����0
*/
u8 fnDl698AL_ThenGetReqHandle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;
    u8 *recv_data = &buf_recv->data[buf_recv->left];
    u8 res = DATA_ACCESS_RESULT_SUC;
    u8 secCheck = SUCCESS ;

    // 1.����OAD����ȡOI��Ϣ
    buf_recv->obj.oi = BUILD_U16(recv_data[1], recv_data[0]);//oi
    buf_recv->obj.attevt_id = recv_data[2] & 0x1F;
    STREAM_TO_UINT32(buf_recv->obj.oad_omd, recv_data); //�洢OAD
    buf_recv->left += 4;   //OAD
    buf_recv->left += 1;  //��ʱʱ��
    // 2.IOȨ�޺Ϸ��Լ����
    secCheck = fnDl698AL_Check_ApduSec(chan, DL698AL_APDU_TAG_GETREQ, DL698AL_GETTYPE_NORMAL, buf_recv->obj.oad_omd);

    // 8.���ʱ���ǩ�Ƿ�Ϸ�
    if (pchan->time_info.time_tag.check_timetag_result == DL698AL_TIMETAG_ERROR)
    {
        if (fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_LIST_PART, 0, 0, 0, 0) != SUCCESS)
        {
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }
        fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_DAR_PART, 0, 0, 0, DATA_ACCESS_RESULT_TIMLAGERR);
    }
    // 9.���IOȨ�޺Ϸ���
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
        // 2.����get rsp������Ϣ,���OAD
        fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_LIST_PART, 0, 0, 0, 0);

        buf_recv->obj.oi_list_index = fnDl698AL_Check_OIList(&buf_recv->obj);
        // 5.���ø�class�ӿڽ���get����
        res = fnDl698_AL_Get_Of_IC(chan);
    }
    return res;
}

#ifdef DL698_GETBLOCK
/*********************************************************************
* @fn      fnDl698AL_GetNextReqHandle
*
* @brief   �����ظ�Get Next Request����
*
* @param   chan ͨ�����
*
* @return  ���������ɹ�����0
*/
static u8 fnDl698AL_GetNextReqHandle(u8 chan, u8 piid, u16 block_num)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf_pend; //ָ���ϴ�δ�������Rxbuf
    u8 *recv_data = &buf_recv->data[buf_recv->left];
    u8  get_type = buf_recv->obj.tag, while_break = 0, oad_num = 1, temp_oad_num = 0, encode = DL698_GETRSP_ENCODE_HDR_PART;
    u8 res = DATA_ACCESS_RESULT_SUC;

    // 1.�жϵ�ǰ�����ڷ�֡״̬���򲻴��ڵȴ�GETNEXTREQ״̬�����֡�����Ԥ��һ��ʱ�ܾ���֡
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
        // 2.����ȴ�GETNEXTREQ״̬��־
        pchan->blockInfo.get_next_wait = false;

        // 3.��ȡ��һ�δ�����seq��
        temp_oad_num = pchan->blockInfo.temp_seq_num;
        oad_num = temp_oad_num;
        while (!while_break)
        {
            // 4.����OAD����ȡOI��Ϣ
            buf_recv->obj.oi = BUILD_U16(recv_data[1], recv_data[0]);//oi
            buf_recv->obj.attevt_id = recv_data[2] & 0x1F;
            STREAM_TO_UINT32(buf_recv->obj.oad_omd, recv_data); //�洢OAD
            buf_recv->left += 4;

            // 5.����get rsp������Ϣ
            if (fnDl698AL_BuildGetRsp(chan, encode, get_type, oad_num, false, 0) != SUCCESS)
            {
                return DATA_ACCESS_AL_MEMALLOC_ERR;
            }
            else
            {
                // 11.���ø�class�ӿڽ���get����
                res = fnDl698_AL_Get_Of_IC(chan);

                // 12.����Ҫ��֡��������֡����
                if (pchan->blockInfo.block_flag == true)
                {
                    fnDl698AL_SendGetNextRsp(chan, temp_oad_num, oad_num, 0);
                    break;
                }
                if (res != DATA_ACCESS_RESULT_SUC)
                {
                    //����list�Ի�ȡ���ݳ���ʱ���ظ�����ǰOAD��ʣ��OADֱ��PASS
                    break;
                }
            }
            // 9.���ݽ�����ϣ�����get����
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
    // 10.����get rsp������Ϣ����װ�ϱ���Ϣ��ʱ���ǩ
    fnDl698AL_BuildGetRsp(chan, DL698_GETRSP_ENCODE_LAST_PART, 0, 0, false, 0);

    // 11.���Ϸ�����־
    pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
    pchan->funcode = DL698AL_FUNCODE_DATAINTER;
    DL698AL_SET_SEND_FLAG(chan);

    return res;
}
#endif
