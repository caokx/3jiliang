
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
* @brief   ����Э��һ���Լ�����һ����
*
* @param   buf_recv ָ����������ݵ�ָ��
*          nego     ���Э�����ݵĽṹ��
*
* @return  �޷���ֵ
*/
void fnDl698AL_Decode_Conformance(u8* buf_recv, sDl698AL_Nego_TypeDef * nego)
{
    //    u8 conf1,conf2,conf3;

    //Э��һ���Խ�����ԭʼ����Ϊ�Ӹ��ֽڵ����ֽ�

    STREAM_TO_UINT32(nego->protocol_conformance.protocolconformance_hi8, buf_recv);
    STREAM_TO_UINT32(nego->protocol_conformance.protocolconformance_lo4, buf_recv);

    //Э��һ���Խ�����ԭʼ����Ϊ�Ӹ��ֽڵ����ֽ�

    STREAM_TO_UINT32(nego->function_conformance.functionconformance_hi16, buf_recv);
    STREAM_TO_UINT32(nego->function_conformance.functionconformance_hi12, buf_recv);
    STREAM_TO_UINT32(nego->function_conformance.functionconformance_lo8, buf_recv);
    STREAM_TO_UINT32(nego->function_conformance.functionconformance_lo4, buf_recv);
}

/*********************************************************************
* @fn      fnDl698AL_ConnRes
*
* @brief   ��Ӧ�����ӽ�������Ļظ�
*
* @param   chan     ͨ��
*          nego     ���Э�����ݵĽṹ��
*          buffer   ָ����ظ����ݵ�ָ��
*          result   ���ӽ������
*          timetag_exist  ��ʾ�յ����������Ƿ���ʱ���ǩ����Ϊ1��û��Ϊ0
*
* @return  op_len   �ظ���APDU֡����
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
        buf_send->data = (u8 *)fnDl698_Buffer_Alloc(DL698AL_APDU_MAXSIZE(chan));  //ȷ��buffer����
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

    //���̰汾��Ϣ
    fnGet_ConnServer(buffer);
    buffer += 32;

    op_len += 32;

    //�̶���Ӧ�ò�Э��汾��
    UINT16_TO_STREAM(buffer, DL698AL_PROTOCOL_VERSION);
    op_len += 2;

    /*
    //Э��һ�����빦��һ����
    //Э��һ���ԣ�ԭʼ����Ϊ�Ӹ��ֽڵ����ֽ�
    UINT32_TO_STREAM(buffer, (DL698AL_PROTCFM_HI8B & nego->protocol_conformance.protocolconformance_hi8));
    UINT32_TO_STREAM(buffer, (DL698AL_PROTCFM_LO4B & nego->protocol_conformance.protocolconformance_lo4));
    op_len += 8;

    //����һ���ԣ�ԭʼ����Ϊ�Ӹ��ֽڵ����ֽ�
    UINT32_TO_STREAM(buffer, (DL698AL_FUNCCFM_HI16B & nego->function_conformance.functionconformance_hi16));
    UINT32_TO_STREAM(buffer, (DL698AL_FUNCCFM_HI12B & nego->function_conformance.functionconformance_hi12));
    UINT32_TO_STREAM(buffer, (DL698AL_FUNCCFM_HI8B  & nego->function_conformance.functionconformance_lo8));
    UINT32_TO_STREAM(buffer, (DL698AL_FUNCCFM_LO4B  & nego->function_conformance.functionconformance_lo4));
    op_len += 16;
    */

    //Э��һ�����빦��һ����
    //Э��һ���ԣ�ԭʼ����Ϊ�Ӹ��ֽڵ����ֽ�
    UINT32_TO_STREAM(buffer, DL698AL_PROTCFM_HI8B);
    UINT32_TO_STREAM(buffer, DL698AL_PROTCFM_LO4B);
    op_len += 8;

    //����һ���ԣ�ԭʼ����Ϊ�Ӹ��ֽڵ����ֽ�
    UINT32_TO_STREAM(buffer, DL698AL_FUNCCFM_HI16B);
    UINT32_TO_STREAM(buffer, DL698AL_FUNCCFM_HI12B);
    UINT32_TO_STREAM(buffer, DL698AL_FUNCCFM_HI8B);
    UINT32_TO_STREAM(buffer, DL698AL_FUNCCFM_LO4B);
    op_len += 16;

    //����������֡���ߴ�
    UINT16_TO_STREAM(buffer, gDl698AL_Server.user_para[chan].dl_size_tx);

    //����������֡���ߴ�
    UINT16_TO_STREAM(buffer, gDl698AL_Server.user_para[chan].dl_size_rx);

    //����������֡��󴰿ڳߴ�
    *buffer++ = gDl698AL_Server.user_para[chan].apdu_window_size_rx;

    //���������ɴ���APDU�ߴ�
    UINT16_TO_STREAM(buffer, gDl698AL_Server.user_para[chan].apdu_size);
    op_len += 7;

    //�̶���Ӧ�����ӳ�ʱʱ�䣬bit32
    UINT32_TO_STREAM(buffer, nego->timeout_nego);
    op_len += 4;

    //add by wj, if timetag error,the result is timetag
    if (pchan->time_info.time_tag.check_timetag_result == DL698AL_TIMETAG_ERROR) //��ʱ���ǩ���������ظ���������
    {
        *buffer++ = CONN_OTHERS_FAULT;
        op_len += 1;
    }
    else
    {
        //��֤���
        *buffer++ = result;   //�ӵĴ������ӽ��
        op_len += 1;
    }

    /*
    //û�м���֤������Ϣ
      *buffer++ = 0x00;

    //û�мӸ����ϱ���Ϣ
      *buffer++ = 0x00;
      op_len += 1;
    */
    //�Ȼظ�00����������ESAM�ٻظ�RN��ǩ����Ϣ;
    //nego->auth_object = (eDl698ConnMechInfo_TypeDef)0;

    if (nego->auth_object == 1)   //һ�����룬�����������
    {
        //�����Ƿ���ȷ
        *buffer++ = 0x00;
        op_len += 1;
    }
    else if (nego->auth_object == 2)   //�ԳƼ���
    {
        RN_Len = gConnResRnLen & 0xFF;

        *buffer++ = 0x01;            //��RN����ǰ�и�0x01
        *buffer++ = RN_Len;            //RN����
        Std_Memcpy(buffer, pchan->sec_data.RN,  RN_Len);
        buffer += RN_Len;
        *buffer++ = 0x04;            //ǩ����Ϣ����Ϊ0x4
        Std_Memcpy(buffer, pchan->sec_data.Sign, 4);  //ǩ����Ϣ����Ϊ4bytes
        buffer += 4;
        op_len += RN_Len + 4 + 3;
    }
    else
    {
        *buffer++ = 0x00;
        op_len += 1;
    }

    //���������Ϣ
    flwrpt_maxlen = buf_send->size - op_len - DL698AL_RESV_TIMETAG(chan);
    fnDl698AL_FlwRptPkg(chan, flwrpt_maxlen, buffer, &flwrpt_retlen);

    buffer += flwrpt_retlen;
    op_len += flwrpt_retlen;

    //���ʱ���ǩ
    timetag_retlen = fnDl698AL_TimeTagPkg(chan, buffer);
    buffer += timetag_retlen;
    op_len += timetag_retlen;

    return op_len;
}

/*********************************************************************
* @fn      fnDl698AL_ConnHandle
*
* @brief   ������յ��Ľ���Ӧ���������󣬰�����������ͻظ�
*
* @param   chan ͨ��
*
* @return  �Ƿ������ӳɹ����ɹ�����0, ʧ�ܷ��ط�0
*/
u8 fnDl698AL_ConnHandle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;
    u8* recv_data = &buf_recv->data[buf_recv->left];
    u8 return_result = 0;   //���ڴ˴�handle�ķ���ֵ
    u8 vert0, vert1; //,vert2,vert3;
    //    u16 i = 0;
    u8 result = CONN_SUCCESS;       //�������ӽ����Ľ��
    u8 confirm_error = 0xFF;        //����ConfirmedServiceError�б�ʾ����ԭ��
    u8* encrytext = NULL;
    u8* signature = NULL;
    //  u8* safety_par = NULL;  //��ȫ����ָ�룬ָ������1+MAC1+MAC2���׵�ַ
    u32 temp32;
    u8  tempCA, temp[8];
    sCommSize_TypeDef tempSize;
    //u8* ptemp = NULL;
    //u8* Conn_ret = NULL;
    //u16 Conn_retlen = 0;

    // 1. connect tag
    recv_data++;
    buf_recv->left++;
    // �ж�tag�Ƿ���󣬴˴����ж�Ҳ�У�ǰ���Ѿ��жϹ�
    // if(byte!=DL698AL_APDU_TAG_CONREQ) //0x02
    // {
    //     return_result = -1;
    //  result = CONN_OTHERS_FAULT;
    // }
    // 2.����piid
    buf_recv->obj.piid = *recv_data++;
    buf_recv->left++;

    if (buf_recv->left < buf_recv->right) //left>=right��˵������Ϊ��
    {
        // 3.����������Ӧ�ò�汾��
        STREAM_TO_UINT16(pchan->nego.pro_version, recv_data);
        //�жϰ汾���Ƿ�Ϸ�
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
        // 4.����Э��һ���Ժ͹���һ����
        fnDl698AL_Decode_Conformance(recv_data, &pchan->nego);  //Э��һ���ԡ�����һ���Խ���
        recv_data += 24;

        // 5.�����ͻ�������֡���ߴ�
        STREAM_TO_UINT16(pchan->nego.apdu_size_tx_nego, recv_data);
        //�������Э�̺�Ľ������apdu_size_tx_nego
        if (pchan->nego.apdu_size_tx_nego > gDl698AL_Server.user_para[chan].dl_size_tx)
        {
            pchan->nego.apdu_size_tx_nego = gDl698AL_Server.user_para[chan].dl_size_tx;
        }

        // 6.�����ͻ�������֡���ߴ�
        STREAM_TO_UINT16(pchan->nego.apdu_size_rx_nego, recv_data);
        //�������Э�̺�Ľ������apdu_size_rx_nego
        if (pchan->nego.apdu_size_rx_nego > gDl698AL_Server.user_para[chan].dl_size_rx)
        {
            pchan->nego.apdu_size_rx_nego = gDl698AL_Server.user_para[chan].dl_size_rx;
        }

        // 7. �����ͻ�������֡��󴰿ڳߴ�
        vert0 = *recv_data++;
        pchan->nego.apdu_window_size_rx = vert0;
        //�������Э�̺�Ľ������apdu_window_size_rx
        if (pchan->nego.apdu_window_size_rx > gDl698AL_Server.user_para[chan].apdu_window_size_rx)
        {
            pchan->nego.apdu_window_size_rx = gDl698AL_Server.user_para[chan].apdu_window_size_rx;
        }

        // 8. �����ͻ������ɴ����APDU�ߴ�
        STREAM_TO_UINT16(pchan->nego.apdu_size_deal, recv_data);
        //�������Э�̺�Ľ������apdu_size_deal
        if (pchan->nego.apdu_size_deal > gDl698AL_Server.user_para[chan].apdu_size)
        {
            pchan->nego.apdu_size_deal = gDl698AL_Server.user_para[chan].apdu_size;
        }

        // 9. ����������Ӧ�����ӳ�ʱʱ��
        STREAM_TO_UINT32(pchan->nego.timeout_nego, recv_data);

        //�������Э�̺�Ľ������timeout_nego
        //if( pchan->nego.timeout_nego > DL698AL_CONNECT_TIMEOUT )   //��Ӧ�����ӳ�ʱʱ�����7200s����7200s��ΪЭ�̽��
        // {
        //   pchan->nego.timeout_nego = DL698AL_CONNECT_TIMEOUT;
        // }

        if (pDl698DL_Channel[chan].stRxFrameInfo.stSA.ubAddrType != DL698DL_SERVER_ADDR_TYPE_UNICAST)
        {
            result = CONN_OTHERS_FAULT;
        }

        tempCA = pDl698DL_Channel[chan].stRxFrameInfo.ucCA; //
        fnReadDlyTime_Esam(&temp32, tempCA, 1);   //��ȡ�Ự����ֵ
        if (pchan->nego.timeout_nego > temp32)
        {
            pchan->nego.timeout_nego = temp32;
        }
        // 10. ������֤������󣬹����ٸ��ֽ�
        vert0 = *recv_data++;
        pchan->nego.auth_object = (eDl698ConnMechInfo_TypeDef)vert0;
        if (pchan->nego.auth_object == 1)   //һ�����룬�����������
        {
            //����һ�����룬����Ӧ���и����볤�Ȱɣ�
            vert0 = *recv_data++;  //�������볤�ȣ������vert0��

            //-----������-------------
            Std_AsciiStrToHexStr(&temp[0], recv_data, 8);

            if (fnSecret_Verify(0, 0, &temp[0]) == ERROR)  //698�̶���00������
            {
                //�������������
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
        else if (pchan->nego.auth_object == 2)   //�ԳƼ���
        {
            vert0 = *recv_data++;    //���ĳ���
            encrytext =  recv_data;
            //safety_par = encrytext;  //�Ƚ���ȫ��֤����ָ��ָ������1ָ���׵�ַ
            recv_data += vert0;

            vert1 = *recv_data++;    //ǩ����Ϣ����
            signature = recv_data;
            recv_data += vert1;

            #ifdef _WIN32
            confirm_error = fnDl698_Chk_Symm(encrytext, signature, pchan->sec_data.RN, pchan->sec_data.Sign);   //�ԳƼ���
            #else
            tempCA = pDl698DL_Channel[chan].stRxFrameInfo.ucCA; //
            confirm_error = fnEsamOp_CreatConnect(encrytext, signature, pchan->sec_data.RN, pchan->sec_data.Sign, tempCA);    //�ԳƼ���
            #endif
            if (confirm_error == ERROR)  //�����ΪERROR
            {
                //���Գƽ��ܴ������� result = CONN_SYSDECRYP_FAULT;
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
        else if (pchan->nego.auth_object == 0)   //��������
        {
            //*recv_data++;    //NULL
        }

        //������֤������

        //ʱ���ǩ
        fnDl698AL_Decode_TimeTag(chan, recv_data);    //����ʱ���ǩ

        //�ظ���Connect.Response ��client��
        if ((buf_send->right = fnDl698AL_ConnRes(chan, &pchan->nego, result)) > 0)
        {
            fnEvtPrg_End();

            buf_send->left = 0;
            pchan->funcode = DL698AL_FUNCODE_DATAINTER;
            pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
            DL698AL_SET_SEND_FLAG(chan);
            fnDl698AL_GetCurrTime(&pchan->time_info.conn_time);      //���½�������ʱ��
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
            //����
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
* @brief   ������յ��ĶϿ��������󣬰�����������ͻظ�
*
* @param   chan ͨ��
*
* @return  reason ,����Ϊ0���쳣Ϊ-1
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
        //ʱ���ǩ
        fnDl698AL_Decode_TimeTag(chan, recv_data);    //����ʱ���ǩ
        reason = 0; //normal
        //fnDl698AL_Brk_Asso(chan,reason);
        fnDl698_SafetyCertiHandle(DL698AL_APDU_TAG_RLSREQ, 0, safety_par, Rls_ret, &Rls_retlen);
    }
    else
    {
        reason = -1;
        return reason;
    }

    // 1.���buffer�Ƿ���ڣ��������������뷢��buffer��Դ
    if (buf_send->data == NULL)
    {
        buf_send->data = (u8 *)fnDl698_Buffer_Alloc(DL698AL_APDU_MAXSIZE(chan));
        if (buf_send->data == NULL)
        {
            return -1;
        }
        buf_send->size = DL698AL_APDU_MAXSIZE(chan);   //������Ӧ������
        fnDl698_memset(buf_send->data, 0, buf_send->size);
    }
    send_data = &buf_send->data[buf_send->right];

    //����RLRE��ӦAPDU
    buf_send->left = 0;
    send_data = &buf_send->data[buf_send->left];
    *send_data++ = DL698AL_APDU_TAG_RLSRSP;    //RLSRE tag
    *send_data++ = buf_recv->obj.piid;    //piid
    *send_data++ = 0x00;    //value
    op_len = 3;           //RLSRE tag, piid �� ���

    //���������Ϣ
    flwrpt_maxlen = buf_send->size - op_len - DL698AL_RESV_TIMETAG(chan);
    fnDl698AL_FlwRptPkg(chan, flwrpt_maxlen, send_data, &flwrpt_retlen);
    send_data += flwrpt_retlen;
    op_len += flwrpt_retlen;

    //���ʱ���ǩ
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
* @brief   �������Ͽ�Ӧ������֪ͨ��
*
* @param   chan           ͨ�����
*          buffer         ���Ͱ�ָ��
*          Current_time   Current_time��ǰʵʱʱ��
*
* @return  ���ذ�����
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

    //Ӧ�����ӽ���ʱ��date_time_s
    UINT8_TO_STREAM(buffer, DTYPE_DATETIME_S);   //add by wj
    UINT16_TO_STREAM(buffer, pchan->time_info.conn_time.year);
    UINT8_TO_STREAM(buffer, pchan->time_info.conn_time.month);
    UINT8_TO_STREAM(buffer, pchan->time_info.conn_time.day);
    UINT8_TO_STREAM(buffer, pchan->time_info.conn_time.hour);
    UINT8_TO_STREAM(buffer, pchan->time_info.conn_time.minute);
    UINT8_TO_STREAM(buffer, pchan->time_info.conn_time.second);
    op_len += 8;

    //��������ǰʱ��date_time_s
    UINT8_TO_STREAM(buffer, DTYPE_DATETIME_S);  //add by wj
    UINT16_TO_STREAM(buffer, Current_time.year);
    UINT8_TO_STREAM(buffer, Current_time.month);
    UINT8_TO_STREAM(buffer, Current_time.day);
    UINT8_TO_STREAM(buffer, Current_time.hour);
    UINT8_TO_STREAM(buffer, Current_time.minute);
    UINT8_TO_STREAM(buffer, Current_time.second);
    op_len += 8;

    //���������Ϣ
    flwrpt_maxlen = DL698AL_APDU_MAX_SIZE - op_len - DL698AL_RESV_TIMETAG(chan);
    fnDl698AL_FlwRptPkg(chan, flwrpt_maxlen, buffer, &flwrpt_retlen);
    buffer += flwrpt_retlen;
    op_len += flwrpt_retlen;

    //û�м�ʱ���ǩ
    *buffer++ = 0x00;
    op_len += 1;

    return op_len;
}

/*********************************************************************
* @fn      fnDl698AL_NotiRlsConnHandle
*
* @brief   �����ϱ��Ͽ�����������ͻ������ͻ�������ظ���Ҳ���þܾ�
*
* @param   chan ͨ��
*
* @return  ���������Ͽ����Ӱ��ɹ�����0�����򷵻ط�0
*         (��δ����Ӧ�����ӡ�δ��ʱ���������-1, δ�ɹ���ȡʵʱʱ�䷵��1)
*/
s8 fnDl698AL_NotiRlsConnHandle(u8 chan)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    //sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;
    sDl698AL_ApduSBuf_TypeDef* buf_send = &pchan->apdu_tx_buf;

    //����date_time_s������ʱ�������ڵ�ǰʱ��
    sDl698date_time_s_TypeDef  Current_time;
    s8  result = -1;            //�����Ͽ����ӵĴ�������Ϊ0��ʾ���ͶϿ����ӳɹ���Ϊ-1���ʾδ���ͶϿ�����
    //��Ϊû�н������ӻ��޷���ȡ��ǰʱ���ԭ��

    if (pchan->time_info.conn_time.year != 0)      //û�н������ӣ��������ж��Ƕ���Ҫ�����Ͽ�Ӧ������
    {
        return result;
    }
    #ifdef _WIN32
    #else
    pchan->time_info.current_cout = current_cout;  //��ǰʱ��
    #endif

    //��RTC��ǰ����ֵ��ȥ���һ�����ݽ�����ʱ����ڳ�ʱʱ�����������Ͽ����Ӱ�
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

            //��ȡ��ǰʱ��
            fnDl698AL_GetCurrTime(&Current_time);
            //������ذ���
            if ((buf_send->right = fnDl698AL_RlsConnPkg(chan, buf_send->data, Current_time)) > 0)
            {
                buf_send->left = 0;
                pchan->funcode = DL698AL_FUNCODE_DATAINTER;
                pchan->dirprm = DL698AL_DIRPRM_SERVRSP;
                DL698AL_SET_SEND_FLAG(chan);
                result = 0;
            }
        }
        else    //��δ��ʱ����1
        {
            result = 1;
        }
    }

    if (result == 0)     //�Ͽ��������ݰ��Ѿ�׼������
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
* @param   chan ͨ��
*
* @return  �Ƿ������ӳɹ����ɹ�����0, ʧ�ܷ��ط�0
*/
u8 fnDl698AL_ConnSuccess(u8 chan)
{
    return SUCCESS;
}
