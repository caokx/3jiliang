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
#include "Dl698_Globals.h"
#include "Dl698_UserData.h"
#include "Dl698AL_Report.h"
//#include <time.h>
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
extern u16 fnDl698AL_Check_TimeTag(u8 chan);

#ifdef _WIN32

#else
extern ErrorStatus Rn8xxx_RTC_Read(u8 *Dst);
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
* @fn      fnDl698AL_GetCurrTime
* @brief   ��˽�Ҫ�ϱ������ݴ���AL�㣬�˺���ΪAL����ñ�˵ĺ���
* @param   Current_time  ��ȡ���ĵ�ǰʱ��(������ʱ����)���ڴ�ָ����
*
* @return  ��ȡ��ǰʱ��(������ʱ����)��������0 ��ʾ�ɹ��������ʾʧ��(�����ȡ��ʱ���ꡢ�¡���Ϊ0���쳣���)��
*          ���ʧ�ܣ����ٴλ�ȡ��ǰʱ�䣬�����ζ���ȡʧ���򱨴�
*/
#define DL698AL_YEAR_BASE_645 2000
#define DL698AL_YEAR_BASE_SYS 1900
void fnDl698AL_GetCurrTime(sDl698date_time_s_TypeDef * ptime)
{
    #ifdef _WIN32

    struct tm* curtime;
    time_t cursec;
    time(&cursec);
    curtime = localtime(&cursec);
    ptime->year    = curtime->tm_year + DL698AL_YEAR_BASE_SYS - DL698AL_YEAR_BASE_645;
    ptime->month   = curtime->tm_mon + 1;
    ptime->day     = curtime->tm_mday;
    ptime->hour    = curtime->tm_hour;
    ptime->minute  = curtime->tm_min;
    ptime->second  = curtime->tm_sec;
    return ;
    #else
    u8 buf[10];
    //  u8 cout_fault = 0;       //�õ�ʱ�����Ĵ���������Σ�����������ʧ��

    Rn8xxx_RTC_Read(buf);
    ptime->second = fnBcdToHex_u8(buf[0]);
    ptime->minute = fnBcdToHex_u8(buf[1]);
    ptime->hour  = fnBcdToHex_u8(buf[2]);
    ptime->day   = fnBcdToHex_u8(buf[4]);
    ptime->month = fnBcdToHex_u8(buf[5]);
    //ptime->year  = BUILD_U16(buf[6], 0x07) - 1;
    ptime->year  = fnBcdToHex_u8(buf[6]);
    ptime->year  = ptime->year + DL698AL_YEAR_BASE_645;

    return ;

    #endif
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/

ErrorStatus fnSetCurrTime(sDate_time_s_TypeDef * ptime)
{
    ErrorStatus Status;
    sDF01   tmpClock;

    Status = ERROR;

    if (fnCheck_Date_time_s(ptime) == SUCCESS)
    {
        tmpClock.Year = (u8)(ptime->year - 2000);
        tmpClock.Year = fnHexToBcd_u8(tmpClock.Year);
        tmpClock.Month = fnHexToBcd_u8(ptime->month);
        tmpClock.Day = fnHexToBcd_u8(ptime->day);
        tmpClock.Hour = fnHexToBcd_u8(ptime->hour);
        tmpClock.Minute = fnHexToBcd_u8(ptime->minute);
        tmpClock.Second = fnHexToBcd_u8(ptime->second);

        tmpClock.Week = fnWeek_Calculate(ptime->year, ptime->month, ptime->day);
        if (fnSysClock_Write(&tmpClock) == SUCCESS)
        {
            //fnEvent_Operation(EVENT_STYLE_SETCLOCK , EVENT_OPERATION_START , (u8 *)&tmpClock,SetSource);

            Status = SUCCESS;
        }
    }

    return Status;
}

/*******************************************************************************
* @fn      fnDl698AL_Decode_TimeTag
*
* @brief   ����ʱ���ǩ������ʱ���ǩʱ������ʱ���ǩ�����һ���ֽ�Ϊdate_time_s����������0x1C��
*          ����Ϊ7�ֽڵ�year��month��day��hour��minute��second��
*          TI������TI����������0x54��ʼ������Ϊ3�ֽڵĵ�λ��time_interval���ܹ�12���ֽڡ�
*
* @param   chan     ͨ��
*          recvdata ��������ʱ���ǩ
*
* @return  timetag_result  �Ƿ���ʱ���ǩ����Ϊtrue��û��Ϊfalse
*/
u8 fnDl698AL_Decode_TimeTag(u8 chan, u8* recvdata)      //����ʱ���ǩ
{
    sDl698AL_ChnInfo_TypeDef*  pchan = &gDl698AL_Server.pAlChan[chan];
    u8 timetag_result = DL698AL_TIMETAG_ERROR;
    u8 vert0, vert2;

    /*date_time_s*/
    //date_time_s.year
    vert0 = *recvdata++;

    if (vert0 == 1)    //��ʱ���ǩ����һ���ֽ�Ϊdate_time_s����������DL698AL_DATA_TYPE_DATETIME_S
    {
        pchan->time_info.time_tag.len = 11;
        //date_time_s.year
        STREAM_TO_UINT16(pchan->time_info.time_tag.date_time_s.year, recvdata);
        //date_time_s.month
        STREAM_TO_UINT8(pchan->time_info.time_tag.date_time_s.month, recvdata);
        //date_time_s.day
        STREAM_TO_UINT8(pchan->time_info.time_tag.date_time_s.day, recvdata);
        //date_time_s.hour
        STREAM_TO_UINT8(pchan->time_info.time_tag.date_time_s.hour, recvdata);
        //date_time_s.minute
        STREAM_TO_UINT8(pchan->time_info.time_tag.date_time_s.minute, recvdata);
        //date_time_s.second
        STREAM_TO_UINT8(pchan->time_info.time_tag.date_time_s.second, recvdata);

        //ti.time_unit
        STREAM_TO_UINT8(vert2, recvdata);
        pchan->time_info.time_tag.ti.time_unit = (eDl698TimeUnit_TypeDef)vert2;
        //ti.time_interval
        STREAM_TO_UINT16(pchan->time_info.time_tag.ti.time_interval, recvdata);

        if (fnDl698AL_TimeTag_Valid(chan) == SUCCESS)          //ʱ���ǩ��Ч���ж�,��Ч
        {
            pchan->time_info.time_tag.check_timetag_result = DL698AL_TIMETAG_SUCCESS;
            timetag_result = SUCCESS;
        }
        else           //��ʱ���ǩ��Ч�������������������֡�����������ͷ�recv_buf
        {
            pchan->time_info.time_tag.check_timetag_result = DL698AL_TIMETAG_ERROR;
            timetag_result = ERROR;
        }
    }
    else if (vert0 == 0)     //vert0Ϊ0����ʱ���ǩ
    {
        pchan->time_info.time_tag.len = 1;
        timetag_result = SUCCESS;
        pchan->time_info.time_tag.check_timetag_result = DL698AL_NO_TIMETAG;
    }
    else       //vert0Ϊ����ֵ����ʱ���ǩ��Ϣ����
    {
        pchan->time_info.time_tag.len = 1;
        timetag_result = ERROR;
        pchan->time_info.time_tag.check_timetag_result = DL698AL_TIMETAG_ERROR;
    }

    return timetag_result;
}

#define DL698AL_TI_SEC 0
#define DL698AL_TI_MIN 1
#define DL698AL_TI_HUR 2
#define DL698AL_TI_DAY 3
#define DL698AL_TI_MON 4
#define DL698AL_TI_YEAR 5
#define DL698AL_TI_SEC_SEC  1
#define DL698AL_TI_SEC_MIN  (60)
#define DL698AL_TI_SEC_HOUR (DL698AL_TI_SEC_MIN*60)
#define DL698AL_TI_SEC_DAY  (DL698AL_TI_SEC_HOUR*24)
/*******************************************************************************
* @fn      fnDl698AL_TimeTag_Valid
*
* @brief   ʱ���ǩ��Ч���ж�
*
* @param   chan     ͨ��
*
* @return  timetag_valid  ʱ���ǩ��Ч���жϽ������Ч����SUCCESS����Ч����ERROR
*/
u8 fnDl698AL_TimeTag_Valid(u8 chan)
{
    //���Ե�ʱ����Ҫע������ֶ��Ǵ�0��ʼ���Ǵ�1��ʼ

    sDl698AL_ChnInfo_TypeDef*  pchan = &gDl698AL_Server.pAlChan[chan];
    sDate_time_s_TypeDef* timetag = &pchan->time_info.time_tag.date_time_s;
    sDate_time_s_TypeDef  CurTime;
    u16 timedur = 0;
    u32 timedursec = 0;
    sDate_time_s_TypeDef  TagTime = *timetag;
    //u8 yearleap;
    u8 secflag;
    u32 CurTimeSec, TagTimeSec;
    //  struct tm CurTimeTm,TagTimeTm;

    fnGetCurrTime(&CurTime);
    //#if 0
    timedur = pchan->time_info.time_tag.ti.time_interval;
    switch (pchan->time_info.time_tag.ti.time_unit)
    {
        case (DL698AL_TI_SEC):
        {
            timedursec = timedur;
            secflag = 1;
            break;
        }
        case (DL698AL_TI_MIN):
        {
            timedursec = timedur * DL698AL_TI_SEC_MIN;
            secflag = 1;
            break;
        }
        case (DL698AL_TI_HUR):
        {
            timedursec = timedur * DL698AL_TI_SEC_HOUR;
            secflag = 1;
            break;
        }
        case (DL698AL_TI_DAY):
        {
            timedursec = timedur * DL698AL_TI_SEC_DAY;
            secflag = 1;
            break;
        }
        case (DL698AL_TI_MON):
        {
            TagTime.month = timetag->month + timedur;
            if (TagTime.month > 12)
            {
                TagTime.year += TagTime.month / 12;
                TagTime.month = TagTime.month % 12;
            }
            secflag = 0;
            break;
        }
        case (DL698AL_TI_YEAR):
        {
            TagTime.year = timetag->year + timedur;
            secflag = 0;
            break;
        }
        default:
        {
            return ERROR;
        }
    }

    if (secflag)
    {
        //�����ʱʱ���ǡ��գ�ʱ���֣��롱����ת����������Ƚ�

        CurTimeSec = fnDateTimeToSec(&CurTime);

        TagTimeSec = fnDateTimeToSec(&TagTime);

        TagTimeSec += timedursec;

        if (TagTimeSec < CurTimeSec)
        {
            return ERROR;
        }
    }
    else
    {
        //CurTime.year = CurTime.year+DL698AL_YEAR_BASE_645-DL698AL_YEAR_BASE_SYS;
        //TagTime.year = TagTime.year-DL698AL_YEAR_BASE_SYS;
        //�����ʱʱ�����»����꣬���Ƚ�����
        if (TagTime.year   < CurTime.year)
        {
            return ERROR;
        }
        if ((TagTime.month  < CurTime.month) && (TagTime.year == CurTime.year))
        {
            return ERROR;
        }
        if ((TagTime.day    < CurTime.day) && (TagTime.month == CurTime.month) && (TagTime.year == CurTime.year))
        {
            return ERROR;
        }
        if ((TagTime.hour   < CurTime.hour) && (TagTime.day == CurTime.day) && (TagTime.month == CurTime.month) && (TagTime.year == CurTime.year))
        {
            return ERROR;
        }
        if ((TagTime.minute < CurTime.minute) && (TagTime.hour == CurTime.hour) && (TagTime.day == CurTime.day) && (TagTime.month == CurTime.month) && (TagTime.year == CurTime.year))
        {
            return ERROR;
        }
        if ((TagTime.second < CurTime.second) && (TagTime.minute < CurTime.minute) && (TagTime.hour == CurTime.hour) && (TagTime.day == CurTime.day) && (TagTime.month == CurTime.month)
            && (TagTime.year == CurTime.year))
        {
            return ERROR;
        }
    }
    //#endif
    return SUCCESS;
}

/*******************************************************************************
* @fn      fnDl698AL_Decode_TimeTag
*
* @brief   ʱ���ǩ�������һ���ֽ�Ϊdate_time_s����������0x1C��
*          ����Ϊ7�ֽڵ�year��month��day��hour��minute��second��
*          TI������TI����������0x54��ʼ������Ϊ3�ֽڵĵ�λ��time_interval���ܹ�12���ֽڡ�
*
* @param   chan     ͨ��
*          recvdata ��������ʱ���ǩ
*
* @return  length  ʱ���ǩ���ȣ���ʱ���ǩʱ����12��û��ʱ���ǩʱ����1
*/

u16 fnDl698AL_TimeTagPkg(u8 chan, u8 *send_buf)
{
    sDl698AL_ChnInfo_TypeDef*  pchan = &gDl698AL_Server.pAlChan[chan];
    u16 length = 0;

    //û�м�ʱ���ǩ
    if (pchan->time_info.time_tag.len == 1)    //û��ʱ���ǩ����ʱ���ǩ����Ϊ1
    {
        *send_buf++ = 0x00;
        length += 1;   //��ʱ��3ʱû�м���֤������Ϣ��ֻ�����ӽ���������ϱ���Ϣ��ʱ���ǩ
    }

    //������ʱ���ǩ����Ҫ�ڻظ�ʱҲ����ʱ���ǩ
    else
    {
        //����ʱ���ǩ
        //date_time_s
        UINT8_TO_STREAM(send_buf, 0x01);  //01 ������ʱ���ǩ
        UINT16_TO_STREAM(send_buf, pchan->time_info.time_tag.date_time_s.year);
        UINT8_TO_STREAM(send_buf, pchan->time_info.time_tag.date_time_s.month);
        UINT8_TO_STREAM(send_buf, pchan->time_info.time_tag.date_time_s.day);
        UINT8_TO_STREAM(send_buf, pchan->time_info.time_tag.date_time_s.hour);
        UINT8_TO_STREAM(send_buf, pchan->time_info.time_tag.date_time_s.minute);
        UINT8_TO_STREAM(send_buf, pchan->time_info.time_tag.date_time_s.second);

        //TI
        //ti.time_unit
        // UINT8_TO_STREAM(send_buf, DTYPE_TI);
        UINT8_TO_STREAM(send_buf, pchan->time_info.time_tag.ti.time_unit);
        //ti.time_interval
        UINT16_TO_STREAM(send_buf, pchan->time_info.time_tag.ti.time_interval);
        length += 11;   //ʱ���ǩΪ11���ֽ�,�������ݲ��ֻ���������������
    }
    return length;
}

/**************************************************************************************
* @fn      fnDl698AL_TimeTag_Handle
*
* @brief   ʱ���ǩ�Ĵ����ж���Ч��
*
* @param   chan         ͨ�����
*
* @return  ʱ���ǩ��Ч�����SUCCESS:ʱ���ǩ��Ч���ɽ�APDU��ERROR ��ʱ���ǩ
*                                                              0xFF: ���ݳ��Ȳ���ȷ�� APDU �޷�����
*/

u8 fnDl698AL_TimeTag_Handle(u8 chan)
{
    //sDl698AL_ChnInfo_TypeDef*  pchan = gDl698AL_Server.pAlChan + chan;
    u8* pBuf = gDl698AL_Server.pAlChan[chan].apdu_rx_buf.data;

    u16 timetag_offset = 0;   //һ֡��ʱ���ǩ��ʼ��ַƫ����
    //u8 timetag = 0;  //ʱ���ǩ��־λ����ʱ���ǩΪ1��û��ʱ���ǩΪ0
    //  u8 timetag_valid = 0;  //ʱ���ǩ��Ч��־λ����ЧΪ1,��ЧΪ0
    u8 result = ERROR;

    timetag_offset = fnDl698AL_Check_TimeTag(chan);    //�ҵ�ʱ���ǩ��ʼ��ַƫ����
    if (timetag_offset != 0xFFFF)     //ƫ��ֵ��Ч
    {
        pBuf += timetag_offset;  //ָ��ָ��ʱ���ǩǰһ���ֽ�
        //pBuf++;                  //ָ��ָ��ʱ���ǩ�ĵ�һ���ֽ�
        result = fnDl698AL_Decode_TimeTag(chan, pBuf);    //����ʱ���ǩ,��ʱ���ǩΪtrue��û��Ϊfalse
    }
    else    //��ʱ���ǩƫ��ֵ��Ч�������������������֡�����������ͷ�recv_buf
    {
        result = 0xFF;
    }

    #if 1
    // result = SUCCESS;
    #endif
    return result;
}

/*********************************************************************
* @fn      fnDl698AL_FlwRptPkg
*
* @brief   �����ϱ���Ϣʱ����ε��ô˺��������쳣����жϲ��ⷢ�Ͱ���ǰ�����ֽ�
*
* @param   chan         ͨ�����
*          retMaxLen    ���ϱ���������ݳ���
*          pRetBuf      return result buffer
*          retLen       return result buffer length
*
* @return  �޷���ֵ
*/

void fnDl698AL_FlwRptPkg(u8 chan, u16 retMaxLen, u8 *pRetBuf, u16 *retLen)
{
    // u8  result = DL698AL_RPTHANDLE_SUCC;       //�ϱ�֪ͨ���������ɹ�����0

    if (fnDl698_GetFlwRptFlag(chan) == 0)   //��û����Ҫ�ϱ�����Ϣ����ֱ���˳�
    {
        *pRetBuf++ = 0x00;    //�����ϱ���ϢΪ0x00
        // result = DL698AL_RPTHANDLE_SUCC;
        *retLen = 1;
    }
    else
    {
        //�Ƿ���Ҫ����piid
        *pRetBuf++ = 0x01;    //�����ϱ���Ϣ��һ���ֽ�Ϊ0x01
        fnDl698_FlwRptValue(retMaxLen, pRetBuf, retLen);
        if (*retLen == 0)    //�޸����ϱ���Ϣ���ϱ��ĳ���Ϊ0
        {
            pRetBuf--;
            *pRetBuf = 0x00;
            *retLen = 1;
        }
        else
        {
            (*retLen)++;              //������ϸ����ϱ���һ���ֽ�0x01
        }
    }
}

/*********************************************************************
* @fn      fnDl698AL_DelayHandle
*
* @brief   �ӳ��ֶδ���ӿ�
*
* @param   chan ͨ�����
*
* @return  �޷���ֵ
*/
u8 fnDl698AL_DelayHandle(u8 chan, u8 block_flag, u8 temp_oad_num)
{
    sDl698AL_ChnInfo_TypeDef*  pchan    = &gDl698AL_Server.pAlChan[chan];
    sDl698AL_ApduRBuf_TypeDef* buf_recv = &pchan->apdu_rx_buf;
    u8 delay_time = buf_recv->data[buf_recv->left + 4];

    if (delay_time == 0)
    {
        pchan->time_info.delay_time = DL698AL_SERVER_DELAY_TIME;
    }
    else
    {
        pchan->time_info.delay_time = delay_time;
    }

    if (pchan->time_info.delay_time != 0)
    {
        pchan->blockInfo.block_flag = block_flag;
        pchan->blockInfo.temp_seq_num = temp_oad_num;
        pchan->time_info.start_stamp = pchan->time_info.current_cout;//��¼��ǰʱ��
    }

    return pchan->time_info.delay_time;
}

/*********************************************************************
* @fn      fnDl698AL_Check_Auth
*
* @brief   �����֤Ȩ���ж�
*
* @param   chan ͨ�����
*
* @return  ������ʣ�DATA_ACCESS_RESULT_SUC����������ʣ�����
*/
#include "globals.h"
u8 fnDl698AL_Check_Auth(u8 chan, u8 tag_flag, u32 OAD_OMD)
{
    u8 ret = DATA_ACCESS_RESULT_DENY;
    u16 OI = (u16)(OAD_OMD >> 16);
    u8  tagsec;

    tagsec = gDl698AL_Server.pAlChan[chan].sec_data.SecType;

    //����ģʽ����������Ȩ�޾���ͨ��
    if (fnReadStatus_PrgEnable() == true)
    {
        return DATA_ACCESS_RESULT_SUC;
    }

    //ESAMû���ӻ��߷������ϣ����������Ķ���������+RN������
    if (Bkgrd.PubData.MtSysSta.SysStaBit.EsamErr == 1)
    {
        if (tag_flag == DL698AL_APDU_TAG_GETREQ && (tagsec == 0x08 || tagsec == 0x01))
        {
            return DATA_ACCESS_RESULT_SUC;
        }
        else
        {
            return DATA_ACCESS_RESULT_DENY;
        }
    }

    //δ���������֤ǰ��ĳЩ�������Խ��ж�д
    if (tag_flag == DL698AL_APDU_TAG_GETREQ)
    {
        if (tagsec == 0x08)
        {
            switch (OI) //�����֤δͨ��ǰֻ�����ȡ���¼�������
            {
                case 0x0000:  //����й�
                case 0x0010:  //�����й�
                case 0x0020:  //�����й�
                case 0x0050:  /*"��1�����޹�"*/
                case 0x0060:  /*"��2�����޹�"*/
                case 0x0070:  /*"��3�����޹�"*/
                case 0x0080:  /*"��4�����޹�"*/

                case 0x0100:  //��������й�
                case 0x0110:  //���������й�
                case 0x0120:  //���������й�
                case 0x0130:  //��������޹�1
                case 0x0140:  //��������޹�2

                case 0x0200:  //г������й�
                case 0x0210:  //г�������й�
                case 0x0220:  //г�������й�
                case 0x0230:  //г������޹�1
                case 0x0240:  //г������޹�2

                case 0x4001:  //ͨѶ��ַ
                case 0x4002:  //���
                case 0x4111:  //������
                case 0x4000:  //����
                case 0x4003:  //�ͻ����
                case 0x2031:  //��ǰ���õ���
                case 0x4804:  //�ܲ����Ϳ���
                case 0x40EE:  //����ģ����ʵ��ܱ���

                case 0xF100:    //Esam
                case 0xF101:    //��ȫģʽ����

                case 0x4104:
                case 0x4105:
                case 0x4106:
                case 0x4107:
                case 0x4108:
                case 0x4109:
                case 0x410A:
                case 0x410B:

                    //----------
                    #if(METERTYPE == 2)
                case 0x2032:  //��ǰ���õ���
                case 0x202c:  //ʣ����
                case 0x202d:  //͸֧���
                    #endif
                    ret = DATA_ACCESS_RESULT_SUC;
                    break;

                default:
                    ret = DATA_ACCESS_RESULT_DENY;
                    break;
            }
        }
    }
    else if (tag_flag == DL698AL_APDU_TAG_ACTREQ)
    {
        if (tagsec == 0x08)
        {
            switch (OAD_OMD)
            {
                case 0x80008300:  //��������բ
                case 0xF1000B00:  //��������
                case 0xF1000C00:  //������֤
                case 0x40007F00:   //�㲥Уʱ
                case 0x30367F00:
                case 0x20147F00:
                case 0xF100FE00:
                case 0x48047F00:
                case 0x48048000:
                case 0x48057F00:    //rongguocan add ����ӻᵼ���������޷��Զ�����������·��
                case 0x48058000:    //dyf add
                    ret = DATA_ACCESS_RESULT_SUC;
                    break;

                default:
                    ret = DATA_ACCESS_RESULT_DENY;
                    break;
            }
        }
    }
    else if (tag_flag == DL698AL_APDU_TAG_SETREQ)
    {
        if (tagsec == 0x08)
        {
            if (OI == 0x40EE) //����ģ����ʵ��ܱ���
            {
                ret = DATA_ACCESS_RESULT_SUC;
            }
            if (OAD_OMD == 0xF1010300) //�������ð�ȫģʽ����3
            {
                return (DATA_ACCESS_RESULT_DENY);
            }
        }
    }
    if (ret == DATA_ACCESS_RESULT_SUC)
    {
        return DATA_ACCESS_RESULT_SUC;
    }

    //�������ж������֤
    if (tag_flag == DL698AL_APDU_TAG_GETREQ)
    {
        if (Secret.NeedIdentityAuth == 1)
        {
            if (fnChk_TermBinCoreAuthStatus(chan))  //�ն���֤��˫о��֤ͨ��������Ķ�ȡ
            {
                return DATA_ACCESS_RESULT_SUC;
            }
        }
        else
        {
            if (tagsec == 0x08 || tagsec == 0x01)   //���ġ�����+RN���������ý��������֤
            {
                return DATA_ACCESS_RESULT_SUC;
            }
        }
    }

    //��д�����ж�Ӧ������
    if (fnChkStatus_tLinkDly() == true)
    {
        return DATA_ACCESS_RESULT_SUC;
    }

    return DATA_ACCESS_RESULT_SECFAIL;

    /*
    if( (tagsec == 0x08) ||(tagsec == 0x01) )
    {
        if(fnChk_AuthOnStatus() == true)
            return DATA_ACCESS_RESULT_SUC;
        else
            return DATA_ACCESS_RESULT_DENY;
    }
    else   //���ı��뽨��Ӧ������
        return DATA_ACCESS_RESULT_SECFAIL;
    */
}
