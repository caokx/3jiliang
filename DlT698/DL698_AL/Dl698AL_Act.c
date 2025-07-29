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
* @brief   IC01 �������ӿ��� actͳһ����ӿ�
*
* @param   chan ͨ�����
*
* @return  ���������ɹ�����0
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
    //buf_recv->left += par_len;  //�����Ѵ�����buffer����
    buf_send->right += ret_len; //���������ķ���buffer�ĳ���

    buf_recv->left += par_len;  //�����Ѵ�����buffer����

    return ret;
}

/*********************************************************************
* @fn      fnDl698AL_BuildActRsp
*
* @brief   Act Response�����װ�ӿ�
*
* @param   chan ͨ�����
*
* @return  �޷���ֵ
*/
static u8 fnDl698AL_BuildActRsp(u8 chan, u8 encode_type, u8 act_type, u8 oad_num, u8 dar)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;
    u8 *send_data = NULL;
    u16 maxlen = 0, retlen = 0;

    //fnDl698_al_debug("build Act Response part %d\n",encode_type);

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
    if (encode_type == DL698_ACTRSP_ENCODE_HDR_PART)
    {
        UINT8_TO_STREAM(send_data, DL698AL_APDU_TAG_ACTRSP);     //��װactrsp
        UINT8_TO_STREAM(send_data, act_type);                    //��װacttype
        UINT8_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.piid); //��װpiid
        if (act_type != DL698AL_ACTTYPE_NORMAL)
        {
            UINT8_TO_STREAM(send_data, oad_num);                //��װSequence of
            buf_send->right++;
        }
        UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.oad_omd);//��װOAD
        buf_send->right += 7;
    }
    else if (encode_type == DL698_ACTRSP_ENCODE_LIST_PART)
    {
        UINT32_TO_STREAM(send_data, pchan->apdu_rx_buf.obj.oad_omd);//��װOAD
        buf_send->right += 4;
    }
    else if (encode_type == DL698_ACTRSP_ENCODE_DAR_PART)
    {
        UINT8_TO_STREAM(send_data, dar);                           //��װDAR
        UINT8_TO_STREAM(send_data, 0);                             //��װѡ��DAR 0
        buf_send->right += 2;
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

/*********************************************************************
* @fn      fnDl698AL_ActReqHandle
*
* @brief   �����ظ�Act Request����
*
* @param   chan ͨ�����
*
* @return  ���������ɹ�����0
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
        //����act����������

        recv_data = &buf_recv->data[buf_recv->left + 1];
        encode = DL698_ACTRSP_ENCODE_HDR_PART;
        buf_recv->left++;
        // 2.��������
        STREAM_TO_UINT8(act_type, recv_data);

        // 3.��������ȡ ppid
        STREAM_TO_UINT8(buf_recv->obj.piid, recv_data);
        buf_recv->left += 2;

        // 4.����list���ͣ����ȡsequence of��Ϣ
        if (act_type != DL698AL_ACTTYPE_NORMAL)
        {
            STREAM_TO_UINT8(oad_num, recv_data);
            buf_recv->left++;
        }
    }
    else
    {
        //actthenget block��������
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
            encode = DL698_ACTRSP_ENCODE_LIST_PART;
        }
    }
    temp_oad_num = oad_num;
    while (!while_break)
    {
        // 1. ��ȡOI��Ϣ
        buf_recv->obj.oi = BUILD_U16(recv_data[1], recv_data[0]);//oi
        buf_recv->obj.attevt_id = recv_data[2] & 0x1F;
        STREAM_TO_UINT32(buf_recv->obj.oad_omd, recv_data); //�洢OMD
        buf_recv->left += 4;

        // 2.IOȨ�޺Ϸ��Լ����
        secCheck = fnDl698AL_Check_ApduSec(chan, DL698AL_APDU_TAG_ACTREQ, act_type, buf_recv->obj.oad_omd);

        //  3.���� rsp������Ϣ
        if (fnDl698AL_BuildActRsp(chan, encode, act_type, oad_num, 0) != SUCCESS)
        {
            return DATA_ACCESS_AL_MEMALLOC_ERR;
        }

        //-5.ʱ���ǩ��Ч����Ӧ��---------------------
        if ((pchan->time_info.time_tag.check_timetag_result == DL698AL_TIMETAG_ERROR) ||
            (((buf_recv->obj.oi == 0x4300) || (buf_recv->obj.oi == 0x8000) || (buf_recv->obj.oi == 0x8001)) &&
             (pchan->time_info.time_tag.check_timetag_result != DL698AL_TIMETAG_SUCCESS)))  //------4300 ����ָ������ʱ���ǩ---
        {
            pSrcLen = fnDl698AL_GetData_Len(1, 0, &buf_recv->data[buf_recv->left]);
            buf_recv->left += pSrcLen;
            res = DATA_ACCESS_RESULT_TIMLAGERR;
        }
        //-6.IO�Ϸ��Լ���ȫȨ�޺Ϸ��Բ���ȷʱ�����˽��Ӧ��-------------------
        else if ((secCheck != DATA_ACCESS_RESULT_SUC) && (buf_recv->obj.oad_omd != 0xF1000B00) &&
                 (buf_recv->obj.oad_omd != 0xF1000C00))  //������֤���а�ȫȨ��
        {
            pSrcLen = fnDl698AL_GetData_Len(1, 0, &buf_recv->data[buf_recv->left]);
            buf_recv->left += pSrcLen;
            res = secCheck;
        }
        else if (((buf_recv->obj.oi == 0x4300) || (buf_recv->obj.oi == 0x8000) || (buf_recv->obj.oi == 0x8001)) &&
                 (fnCheck_nMacErr() == FALSE))  //-----��MAC��֤��������200��ʱ-Զ�̿��ƣ��������Ӧ�����---
        {
            pSrcLen = fnDl698AL_GetData_Len(1, 0, &buf_recv->data[buf_recv->left]);
            buf_recv->left += pSrcLen;
            res = DATA_ACCESS_RESULT_SUSPD;
        }
        else
        {
            buf_recv->obj.oi_list_index = fnDl698AL_Check_OIList(&buf_recv->obj);
            // 4.���ø�class�ӿڽ���act���� ��������һ��OADƫ�Ƶ�ַ
            res = fnDl698_AL_Act_Of_IC(chan);
        }

        #if (TAI_TI_CE_SHI_EN == 1)
        if (buf_recv->obj.oad_omd == 0xF2077F00)    // dyf test ������̨�����
        {
            res = 0;
        }
        #endif

        //----���ݻس�����ȡ�ļ���Ϣ��������֤��ȷʱ����������--��������ֻ��Ӧ��ִ�н��res-----------------------------
        if ((buf_recv->obj.oad_omd == 0xF1000300) || (buf_recv->obj.oad_omd == 0xF1000500) ||
            (buf_recv->obj.oad_omd == 0xF1000B00) || (buf_recv->obj.oad_omd == 0xF0010A00))   //������֤������ȶ�
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

        // 10. act then get��Ҫת��Get����
        if (act_type == DL698AL_ACTTHENGETNORMALLIST)
        {
            if (fnDl698AL_DelayHandle(chan, DL698AL_ACTTHENGET_BLOCKING, temp_oad_num) == 0)
            {
                //��������ʱ�������ִ��get����
                res = fnDl698AL_ThenGetReqHandle(chan);
            }
            else
            {
                //������ʱ����������������
                return res;
            }
        }

        // 11.���ݽ�����ϣ�����set����
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
    // 12.����act rsp������Ϣ
    fnDl698AL_BuildActRsp(chan, DL698_ACTRSP_ENCODE_LAST_PART, 0, 0, 0);

    // 13.���Ϸ�����־
    pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
    pchan->funcode = DL698AL_FUNCODE_DATAINTER;
    DL698AL_SET_SEND_FLAG(chan);
    return res;
}
