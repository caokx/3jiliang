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
* @brief   IC01 �������ӿ��� setͳһ����ӿ�
*
* @param   chan ͨ�����
*
* @return  ���������ɹ�����0
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
    buf_recv->left += par_len;  //�����Ѵ�����buffer����

    return ret;
}

/*********************************************************************
* @fn      fnDl698AL_BuildSetRsp
*
* @brief   Set Response�����װ�ӿ�
*
* @param   chan ͨ�����
*
* @return  �޷���ֵ
*/
static u8 fnDl698AL_BuildSetRsp(u8 chan, u8 encode_type, u8 set_type, u8 oad_num, u8 dar)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;
    u8 *send_data = NULL;
    u16 maxlen = 0, retlen = 0;

    //fnDl698_al_debug("build Set Rsp part %d\n",encode_type);

    //1.���buffer�Ƿ���ڣ��������������뷢��buffer��Դ
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

    // 2.���ݷ�װ���ͽ�����Ӧ��װ����
    if (encode_type == DL698_SETRSP_ENCODE_HDR_PART)
    {
        UINT8_TO_STREAM(send_data, DL698AL_APDU_TAG_SETRSP);   //��װsetrsp
        UINT8_TO_STREAM(send_data, set_type);                  //��װsettype
        UINT8_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.piid); //��װpiid
        if (set_type != DL698AL_SETTYPE_NORMAL)
        {
            UINT8_TO_STREAM(send_data, oad_num);               //��װSequence of
            buf_send->right++;
        }
        UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.oad_omd);//��װOAD
        buf_send->right += 7;
    }
    else if (encode_type == DL698_SETRSP_ENCODE_LIST_PART)
    {
        UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.oad_omd);//��װOAD
        buf_send->right += 4;
    }
    else if (encode_type == DL698_SETRSP_ENCODE_DATA_PART)
    {
        UINT8_TO_STREAM(send_data, dar);        //��װDAR
        buf_send->right++;
    }
    else
    {
        maxlen = buf_send->size - buf_send->right - DL698AL_RESV_TIMETAG(chan);
        //��װFollowReport
        fnDl698AL_FlwRptPkg(chan, maxlen, send_data, &retlen);
        send_data += retlen;

        //��װTimeTag
        fnDl698AL_TimeTagPkg(chan, send_data);
        buf_send->right += retlen + DL698AL_RESV_TIMETAG(chan);
    }
    return SUCCESS;
}

/*********************************************************************
* @fn      fnDl698AL_SetReqHandle
*
* @brief   �����ظ�Set Request����
*
* @param   chan ͨ�����
*
* @return  ���������ɹ�����0
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
        //����set����������

        // 1.Ԥ�Ȼ�ȡIOȨ�޺Ϸ��Լ����
        //secCheck = fnDl698AL_Check_ApduSec(chan);

        recv_data = &buf_recv->data[buf_recv->left + 1];
        encode = DL698_SETRSP_ENCODE_HDR_PART;
        buf_recv->left++;
        // 1.��������
        STREAM_TO_UINT8(set_type, recv_data);

        // 2.��������ȡ ppid
        STREAM_TO_UINT8(buf_recv->obj.piid, recv_data);
        buf_recv->left += 2;

        // 3.����list���ͣ����ȡsequence of��Ϣ
        if (set_type != DL698AL_SETTYPE_NORMAL)
        {
            STREAM_TO_UINT8(oad_num, recv_data);
            buf_recv->left++;
        }
    }
    #ifdef DL698_THENGET_WITH_DELAY
    else
    {
        //setthenget block��������
        //1.ִ��get����
        res = fnDl698AL_ThenGetReqHandle(chan);
        buf_recv->left++;//����delay�ֶ�

        //2.��ȡ��һ�δ�����seq��
        oad_num = pchan->blockInfo.temp_seq_num;

        if ((res != DATA_ACCESS_RESULT_SUC) || (oad_num == 1))
        {
            while_break = 1;
            DL698AL_CLR_BLOCKINFO(chan);    //����BLOCK�����Ϣ
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
        // 1.����OAD����ȡOI��Ϣ
        buf_recv->obj.oi = BUILD_U16(recv_data[1], recv_data[0]);//oi
        buf_recv->obj.attevt_id = recv_data[2] & 0x1F;

        STREAM_TO_UINT32(buf_recv->obj.oad_omd, recv_data); //�洢OAD
        buf_recv->left += 4;

        secCheck = fnDl698AL_Check_ApduSec(chan, DL698AL_APDU_TAG_SETREQ, set_type, buf_recv->obj.oad_omd);

        // 2.����set rsp������Ϣ
        if (fnDl698AL_BuildSetRsp(chan, encode, set_type, oad_num, 0) != SUCCESS)
        {
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }

        // 3.���ʱ���ǩ�Ƿ�Ϸ�
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
            // 6.���IOȨ�޺Ϸ���
            buf_recv->obj.oi_list_index = fnDl698AL_Check_OIList(&buf_recv->obj);
            // 7.���ø�class�ӿڽ���set����
            res = fnDl698_AL_Set_Of_IC(chan);
        }

        // 8.��װ���
        fnDl698AL_BuildSetRsp(chan, DL698_SETRSP_ENCODE_DATA_PART, 0, 0, res);

        // 9. set then get��Ҫת��Get����
        if (set_type == DL698AL_SETTHENGETNORMALLIST)
        {
            if (fnDl698AL_DelayHandle(chan, DL698AL_SETTHENGET_BLOCKING, temp_oad_num) == 0)
            {
                //��������ʱ�������ִ��get����
                res = fnDl698AL_ThenGetReqHandle(chan);
            }
            else
            {
                //������ʱ����������������
                return DATA_ACCESS_RESULT_SUC;
            }
        }

        // 10.���ݽ�����ϣ�����set����
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
    // 11.����act rsp������Ϣ
    fnDl698AL_BuildSetRsp(chan, DL698_SETRSP_ENCODE_LAST_PART, 0, 0, 0);

    // 12.���Ϸ�����־
    pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
    pchan->funcode = DL698AL_FUNCODE_DATAINTER;
    DL698AL_SET_SEND_FLAG(chan);

    return res;
}
