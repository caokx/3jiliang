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
* @brief   表端将要上报的数据传给AL层，此函数为AL层调用表端的函数
* @param   Current_time  获取到的当前时间(年月日时分秒)存于此指针中
*
* @return  获取当前时间(年月日时分秒)处理结果，0 表示成功；非零表示失败(比如获取的时间年、月、日为0等异常情况)；
*          如果失败，则再次获取当前时间，若三次都获取失败则报错
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
    //  u8 cout_fault = 0;       //得到时间错误的错误，最多三次，多余三次则报失败

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
* @brief   解析时间标签，解析时间标签时，若有时间标签，则第一个字节为date_time_s的数据类型0x1C，
*          接着为7字节的year、month、day、hour、minute、second；
*          TI段仍以TI的数据类型0x54开始，接着为3字节的单位和time_interval，总共12个字节。
*
* @param   chan     通道
*          recvdata 待解析的时间标签
*
* @return  timetag_result  是否有时间标签，有为true，没有为false
*/
u8 fnDl698AL_Decode_TimeTag(u8 chan, u8* recvdata)      //解析时间标签
{
    sDl698AL_ChnInfo_TypeDef*  pchan = &gDl698AL_Server.pAlChan[chan];
    u8 timetag_result = DL698AL_TIMETAG_ERROR;
    u8 vert0, vert2;

    /*date_time_s*/
    //date_time_s.year
    vert0 = *recvdata++;

    if (vert0 == 1)    //有时间标签，第一个字节为date_time_s的数据类型DL698AL_DATA_TYPE_DATETIME_S
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

        if (fnDl698AL_TimeTag_Valid(chan) == SUCCESS)          //时间标签有效性判断,有效
        {
            pchan->time_info.time_tag.check_timetag_result = DL698AL_TIMETAG_SUCCESS;
            timetag_result = SUCCESS;
        }
        else           //若时间标签无效，则无需解析，丢弃此帧，丢弃后需释放recv_buf
        {
            pchan->time_info.time_tag.check_timetag_result = DL698AL_TIMETAG_ERROR;
            timetag_result = ERROR;
        }
    }
    else if (vert0 == 0)     //vert0为0，无时间标签
    {
        pchan->time_info.time_tag.len = 1;
        timetag_result = SUCCESS;
        pchan->time_info.time_tag.check_timetag_result = DL698AL_NO_TIMETAG;
    }
    else       //vert0为其他值，则时间标签信息错误
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
* @brief   时间标签有效性判断
*
* @param   chan     通道
*
* @return  timetag_valid  时间标签有效性判断结果，有效返回SUCCESS，无效返回ERROR
*/
u8 fnDl698AL_TimeTag_Valid(u8 chan)
{
    //测试的时候需要注意各个字段是从0开始还是从1开始

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
        //如果超时时间是“日，时，分，秒”，则转换成秒后来比较

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
        //如果超时时间是月或者年，来比较日期
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
* @brief   时间标签组包，第一个字节为date_time_s的数据类型0x1C，
*          接着为7字节的year、month、day、hour、minute、second；
*          TI段仍以TI的数据类型0x54开始，接着为3字节的单位和time_interval，总共12个字节。
*
* @param   chan     通道
*          recvdata 待解析的时间标签
*
* @return  length  时间标签长度，有时间标签时返回12，没有时间标签时返回1
*/

u16 fnDl698AL_TimeTagPkg(u8 chan, u8 *send_buf)
{
    sDl698AL_ChnInfo_TypeDef*  pchan = &gDl698AL_Server.pAlChan[chan];
    u16 length = 0;

    //没有加时间标签
    if (pchan->time_info.time_tag.len == 1)    //没有时间标签，则时间标签长度为1
    {
        *send_buf++ = 0x00;
        length += 1;   //此时加3时没有加认证附加信息，只有连接结果、跟随上报信息及时间标签
    }

    //若加了时间标签则需要在回复时也加上时间标签
    else
    {
        //加上时间标签
        //date_time_s
        UINT8_TO_STREAM(send_buf, 0x01);  //01 代表有时间标签
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
        length += 11;   //时间标签为11个字节,除了数据部分还有两个数据类型
    }
    return length;
}

/**************************************************************************************
* @fn      fnDl698AL_TimeTag_Handle
*
* @brief   时间标签的处理及判断有效性
*
* @param   chan         通道编号
*
* @return  时间标签有效结果，SUCCESS:时间标签有效，可解APDU，ERROR 无时间标签
*                                                              0xFF: 数据长度不正确， APDU 无法解析
*/

u8 fnDl698AL_TimeTag_Handle(u8 chan)
{
    //sDl698AL_ChnInfo_TypeDef*  pchan = gDl698AL_Server.pAlChan + chan;
    u8* pBuf = gDl698AL_Server.pAlChan[chan].apdu_rx_buf.data;

    u16 timetag_offset = 0;   //一帧里时间标签起始地址偏移量
    //u8 timetag = 0;  //时间标签标志位，有时间标签为1，没有时间标签为0
    //  u8 timetag_valid = 0;  //时间标签有效标志位，有效为1,无效为0
    u8 result = ERROR;

    timetag_offset = fnDl698AL_Check_TimeTag(chan);    //找到时间标签起始地址偏移量
    if (timetag_offset != 0xFFFF)     //偏移值有效
    {
        pBuf += timetag_offset;  //指针指向时间标签前一个字节
        //pBuf++;                  //指针指向时间标签的第一个字节
        result = fnDl698AL_Decode_TimeTag(chan, pBuf);    //解析时间标签,有时间标签为true，没有为false
    }
    else    //若时间标签偏移值无效，则无需解析，丢弃此帧，丢弃后需释放recv_buf
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
* @brief   当有上报信息时，表段调用此函数进行异常情况判断并封发送包的前几个字节
*
* @param   chan         通道编号
*          retMaxLen    可上报的最大数据长度
*          pRetBuf      return result buffer
*          retLen       return result buffer length
*
* @return  无返回值
*/

void fnDl698AL_FlwRptPkg(u8 chan, u16 retMaxLen, u8 *pRetBuf, u16 *retLen)
{
    // u8  result = DL698AL_RPTHANDLE_SUCC;       //上报通知处理结果，成功返回0

    if (fnDl698_GetFlwRptFlag(chan) == 0)   //若没有需要上报的信息，则直接退出
    {
        *pRetBuf++ = 0x00;    //跟随上报消息为0x00
        // result = DL698AL_RPTHANDLE_SUCC;
        *retLen = 1;
    }
    else
    {
        //是否需要更改piid
        *pRetBuf++ = 0x01;    //跟随上报消息第一个字节为0x01
        fnDl698_FlwRptValue(retMaxLen, pRetBuf, retLen);
        if (*retLen == 0)    //无跟随上报信息，上报的长度为0
        {
            pRetBuf--;
            *pRetBuf = 0x00;
            *retLen = 1;
        }
        else
        {
            (*retLen)++;              //还需加上跟随上报第一个字节0x01
        }
    }
}

/*********************************************************************
* @fn      fnDl698AL_DelayHandle
*
* @brief   延迟字段处理接口
*
* @param   chan 通道编号
*
* @return  无返回值
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
        pchan->time_info.start_stamp = pchan->time_info.current_cout;//记录当前时戳
    }

    return pchan->time_info.delay_time;
}

/*********************************************************************
* @fn      fnDl698AL_Check_Auth
*
* @brief   身份认证权限判断
*
* @param   chan 通道编号
*
* @return  允许访问：DATA_ACCESS_RESULT_SUC，不允许访问：其它
*/
#include "globals.h"
u8 fnDl698AL_Check_Auth(u8 chan, u8 tag_flag, u32 OAD_OMD)
{
    u8 ret = DATA_ACCESS_RESULT_DENY;
    u16 OI = (u16)(OAD_OMD >> 16);
    u8  tagsec;

    tagsec = gDl698AL_Server.pAlChan[chan].sec_data.SecType;

    //厂内模式，所有请求权限均可通过
    if (fnReadStatus_PrgEnable() == true)
    {
        return DATA_ACCESS_RESULT_SUC;
    }

    //ESAM没焊接或者发生故障，仅允许明文读或者明文+RN读操作
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

    //未进行身份认证前，某些参数可以进行读写
    if (tag_flag == DL698AL_APDU_TAG_GETREQ)
    {
        if (tagsec == 0x08)
        {
            switch (OI) //身份认证未通过前只允许读取如下几个数据
            {
                case 0x0000:  //组合有功
                case 0x0010:  //正向有功
                case 0x0020:  //反向有功
                case 0x0050:  /*"第1象限无功"*/
                case 0x0060:  /*"第2象限无功"*/
                case 0x0070:  /*"第3象限无功"*/
                case 0x0080:  /*"第4象限无功"*/

                case 0x0100:  //基波组合有功
                case 0x0110:  //基波正向有功
                case 0x0120:  //基波反向有功
                case 0x0130:  //基波组合无功1
                case 0x0140:  //基波组合无功2

                case 0x0200:  //谐波组合有功
                case 0x0210:  //谐波正向有功
                case 0x0220:  //谐波反向有功
                case 0x0230:  //谐波组合无功1
                case 0x0240:  //谐波组合无功2

                case 0x4001:  //通讯地址
                case 0x4002:  //表号
                case 0x4111:  //备案号
                case 0x4000:  //日期
                case 0x4003:  //客户编号
                case 0x2031:  //当前月用电量
                case 0x4804:  //周波传送开启
                case 0x40EE:  //管理模组费率电能备份

                case 0xF100:    //Esam
                case 0xF101:    //安全模式参数

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
                case 0x2032:  //当前年用电量
                case 0x202c:  //剩余金额
                case 0x202d:  //透支金额
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
                case 0x80008300:  //明文拉合闸
                case 0xF1000B00:  //红外请求
                case 0xF1000C00:  //红外认证
                case 0x40007F00:   //广播校时
                case 0x30367F00:
                case 0x20147F00:
                case 0xF100FE00:
                case 0x48047F00:
                case 0x48048000:
                case 0x48057F00:    //rongguocan add 不添加会导致物联表无法自动连接蓝牙断路器
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
            if (OI == 0x40EE) //管理模组费率电能备份
            {
                ret = DATA_ACCESS_RESULT_SUC;
            }
            if (OAD_OMD == 0xF1010300) //不能设置安全模式属性3
            {
                return (DATA_ACCESS_RESULT_DENY);
            }
        }
    }
    if (ret == DATA_ACCESS_RESULT_SUC)
    {
        return DATA_ACCESS_RESULT_SUC;
    }

    //读操作判断身份认证
    if (tag_flag == DL698AL_APDU_TAG_GETREQ)
    {
        if (Secret.NeedIdentityAuth == 1)
        {
            if (fnChk_TermBinCoreAuthStatus(chan))  //终端认证或双芯认证通过后可明文读取
            {
                return DATA_ACCESS_RESULT_SUC;
            }
        }
        else
        {
            if (tagsec == 0x08 || tagsec == 0x01)   //明文、明文+RN读操作不用进行身份认证
            {
                return DATA_ACCESS_RESULT_SUC;
            }
        }
    }

    //读写操作判断应用连接
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
    else   //密文必须建立应用连接
        return DATA_ACCESS_RESULT_SECFAIL;
    */
}
