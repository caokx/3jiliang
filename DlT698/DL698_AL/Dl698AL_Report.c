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
* @brief   ���DL�Ƿ��ڿ���״̬�����Խ��ա�����֡
*
* @param   chan      ͨ�����
*
*
* @return  DL��״̬�����з���0���ǿ��з���1...255
*/
u8 fnDl698AL_ChkDl_Idle(u8 chan)
{
    return 0;
}

/*********************************************************************
* @fn      fnDl698AL_ChkAl_Idle
*
* @brief   ���AL�Ƿ��ڿ���״̬�����Խ��ա�����֡
*
* @param   chan      ͨ�����
*
*
* @return  AL��״̬�����з���0���ǿ��з���1...255
*/
u8 fnDl698AL_ChkAl_Idle(u8 chan)
{
    return 0;
}

/*********************************************************************
* @fn      fnDl698_RptRspValue
* @brief   ��ReportRsp�Ļظ���Ϣ�������
* @param   chan      ͨ�����
*
*          pBuffer   ��������Ϣ��buf
*          BufferLen ��������Ϣ�ĳ���
* @return  ��
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
* @brief   ��˽�Ҫ�ϱ������ݴ���AL�㣬�˺���ΪAL����ñ�˵ĺ���
* @param   pBuffer  Э��ջΪ�˴��ϱ��¼������BUFFER��ʼ��ַ
*          BufferLen
*          pBufLen  pBuffer����ʵ����
* @return  ��������0 ��ʾ�ɹ��������ʾʧ�ܣ����ʧ�ܣ��ٴ��ϱ�����Ҫ���µ���fnDl698AL_RptReqHandle�ٴη���BUFFER
*/
u8 fnDl698AL_RptNotiToAl(u8 chan, u16 dataLen)
{
    sDl698AL_ChnInfo_TypeDef* pchan = &gDl698AL_Server.pAlChan[chan];
    // sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;

    u8* send_data = &buf_send->data[buf_send->left];
    u16 op_len = 0;        //���ϱ�����֡�ܳ���
    u8  result = DL698AL_RPTHANDLE_SUCC;       //�ϱ�֪ͨ���������ɹ�?

    // 4. ���ϱ������Ѿ�����apdu_tx_buf,����OAD������OAD���ϴ�����
    // �ж�
    if (dataLen <= 4)    //����Ӧ����OAD������OAD��1�ֽ����ݣ�һ��6�ֽ�
    {
        result = DL698AL_RPTHANDLE_LENFAULT;
        return result;
    }

    op_len = 3 + dataLen;   //��ͷ3���ֽڼ��ϱ����ݳ���
    send_data += op_len;   //�ҵ���βָ��

    // 5. �����ϱ���Ϣ
    *send_data++ = 0x00;    //�����ϱ���ϢΪ��
    // 6. ʱ���ǩ
    *send_data++ = 0x00;      //ʱ���ǩΪ��
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
* @brief   �����ϱ���Ϣʱ����˵��ô˺��������쳣����жϲ��ⷢ�Ͱ���ǰ�����ֽ�
*
* @param   chan         ͨ�����
*          rpt_type     �ϱ����ͣ���ReportNotificationList����ReportNotificationRecordList
*          repeat_flag  �Ƿ����ش�֡����Ϊ1,����Ϊ0
*          pBufferAddr  Э��ջΪ�˴��ϱ��¼������BUFFER��ʼ��ַ
*          BufLen       BUFFER��󳤶�
* @return  ���������ɹ�����0
*/

u8 fnDl698AL_RptNotiHandle(u8 chan, u8 rpt_type, u8 piid)
{
    sDl698AL_ChnInfo_TypeDef* pchan = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;

    u8  al_state = 0xFF;   //al״̬������Ϊ0
    u8  dl_state = 0xFF;   //dl״̬������Ϊ0
    //  static u8  rpt_piid = 0;   //����ϴ�report notification��piid��ֻ��ʼ��һ��
    //    u16 op_len = 0;        //���ϱ�����֡�ܳ���
    u8 result = DL698AL_RPTHANDLE_SUCC;       //�ϱ�֪ͨ���������ɹ�����0
    u8 *send_data = NULL, blockRsp;
    u16 maxlen = 0, retlen = 0;

    dl_state = fnDl698AL_ChkDl_Idle(chan);
    al_state = fnDl698AL_ChkAl_Idle(chan);

    // 1. DL��busy���������ϱ�
    if (dl_state != DL698AL_DL_IDLE)
    {
        result = DL698AL_RPTHANDLE_DLBUSY;
        return result;
    }

    // 2. AL��busy���������ϱ�
    if (al_state != DL698AL_AL_IDLE)
    {
        result = DL698AL_RPTHANDLE_ALBUSY;
        return result;
    }

    // 3. ����ϱ����ͣ������󣬶������ϱ�
    if ((rpt_type != RPTEVT_POWNDOWN) && (rpt_type != RPTEVT_POWNUP) && (rpt_type != RPTEVT_OTHER))
    {
        result = DL698AL_RPTHANDLE_TYPEFAULT;
        return result;
    }
    /*
    // 4. �������ش�֡������֮ǰ��piid��1
    if(retrans_flag == 0)
    {
        rpt_piid = pchan->apdu_rx_buf.obj.piid + 1;//PIID-ACD,�ϴ��յ���piid��1������piid�����������´���Ҫ�ش�
    }

    // �����ش�֡�������ϴε�rpt_piid
    else if(retrans_flag == 1)
    {
    }
    else //�ش���־����
    {
        result = DL698AL_RPTHANDLE_RETRANFAULT;
        return result;
    }
    */

    if ((dl_state == DL698AL_DL_IDLE) && (al_state == DL698AL_AL_IDLE))     //AL��DL������
    {
        // 5. ���buffer�Ƿ���ڣ��������������뷢��buffer��Դ
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

        *send_data++ = DL698AL_APDU_TAG_RPTNOTI;  //��װgetrsp

        //��װgettype
        if ((rpt_type == RPTEVT_POWNDOWN) || (rpt_type == RPTEVT_POWNUP)) //�����¼���¼�ϱ�
        {
            *send_data++ = 0x02;
        }
        else   //�����¼���¼�ϱ�
        {
            *send_data++ = 0x01;
        }

        *send_data++ = piid;  //��װpiid

        buf_send->right += 3;

        //send_data = &buf_send->data[buf_send->right];

        fnReport_EvtData(send_data, &retlen, rpt_type, &blockRsp);

        buf_send->right += retlen; //���������ķ���buffer�ĳ���
        send_data += retlen;
        retlen = 0;

        maxlen = buf_send->size - buf_send->right - DL698AL_RESV_TIMETAG(chan);

        fnDl698AL_FlwRptPkg(chan, maxlen, send_data, &retlen); //��װFollowReport
        send_data += retlen;
        buf_send->right += retlen;
        retlen = 0;

        retlen = fnDl698AL_TimeTagPkg(chan, send_data); //��װTimeTag
        buf_send->right += retlen;

        // 15.���Ϸ�����־
        pchan->dirprm = DL698AL_DIRPRM_SERVREPORT;
        pchan->funcode = DL698AL_FUNCODE_DATAINTER;
        DL698AL_SET_SEND_FLAG(chan);
    }

    return result;
}

/*********************************************************************
* @fn      fnDl698AL_RptRspHandle
*
* @brief   ����Report response���
*
* @param   chan ͨ�����
*
* @return  ���������ɹ�����0
*/

s8 fnDl698AL_RptRspHandle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef* pchan = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;

    u8* recv_data = &buf_recv->data[buf_recv->left];
    //  u8* data_confirm;
    //    u8 byte;
    s8 op_len = 0;
    //  u8 result = 0xFF;    //�Ƿ��ϱ��ɹ����ɹ���Ϊ0
    //  u16 length = 0;
    u8 oad_number = 0;

    // 1.����tag
    recv_data++;                //ReportRsponse tag

    // 2.�����ϱ�����
    //byte = *recv_data++;        //Report type
    recv_data++;        //Report type
    buf_recv->left += 2;

    // 3.����piid
    buf_recv->obj.piid = *recv_data++;  //piid
    buf_recv->left++;

    // 4.�����ϱ��Ļظ���oad����
    oad_number = *recv_data++;   //oad_number
    //buf_recv->left++;

    if ((buf_recv->left < buf_recv->right) && (op_len >= 0)) //left>=right��˵������Ϊ��
    {
        //length = buf_recv->right - buf_recv->left;
        //length = oad_number * 4;
        /*
        if( length >= 4 )      //������һ��OAD�ϴ��ɹ�
        {
            result = 0x00;    //�ϱ��ɹ���result��Ϊ0
        }
        */
        //�������recv_dataΪbuf��length+1Ϊ���ȣ�1Ϊoad������lengthΪoad�ܳ���
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
        if (BSP_EASM_GetPower() == false) //ESAM��Դ�ر�ʱ���ȴ�
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
        //����
        fnDl698AL_Resport_SecRsp(chan);
    }

    return SUCCESS;
}
