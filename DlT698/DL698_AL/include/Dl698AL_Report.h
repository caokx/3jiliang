/********************************************************************
Filename:       Dl698_AL.h
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
#ifndef _DL698AL_REPORT_H_
#define _DL698AL_REPORT_H_

/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"

/*********************************************************************
* MACROS
*/
/** @defgroup DL698_AL_XXX
* @{
*/

/** @} End DL698_AL_XXX */
//#define DL698AL_GET_SEND_FLAG(id)
//上报类型
#define  DL698AL_RPTNOTI_LIST            1    //ReportNotificationList
#define  DL698AL_RPTNOTI_RECORDLIST      2    //ReportNotificationRecordList

//AL及DL是否处于空闲状态
#define  DL698AL_AL_IDLE                 0    //AL处于IDLE状态
#define  DL698AL_DL_IDLE                 0    //DL处于IDLE状态

//ReportNotification 处理结果
#define  DL698AL_RPTHANDLE_SUCC          0    //AL可以发送ReportNotification
#define  DL698AL_RPTHANDLE_TYPEFAULT     1    //上报类型错误，电表自查原因后，再次发起上报
#define  DL698AL_RPTHANDLE_RETRANFAULT   2    //重传标志错误，电表自查原因后，再次发起上报
#define  DL698AL_RPTHANDLE_DLBUSY        3    //DL层busy,表再次发起上报
#define  DL698AL_RPTHANDLE_ALBUSY        4    //AL层busy,表再次发起上报
#define  DL698AL_RPTHANDLE_BUFINVALID    5    //分配了无效的buffer,表再次发起上报

//ReportNotiToAL处理结果
#define  DL698AL_RPTHANDLE_LENFAULT      6    //上传长度错误
//没有需要上报的信息
#define  DL698AL_RPTHANDLE_NORPTINFO     7    //没有需要上报的信息
#define  DL698AL_RPTHANDLE_OTHFAULT      255  //其他错误

//给APDU分配的最大尺寸为2K
#define  DL698AL_APDU_MAX_SIZE           2048  //最大APDU尺寸

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
//void fnDl698AL_RptNotiHandle(u8 chan, u8* buffer, u16 length);
extern u8 fnDl698AL_RptNotiHandle(u8 chan, u8 rpt_type, u8 piid) ;
extern u8 fnReportHandle(u8 chan, u8 rpt_type, u8 retrans_flag);
extern s8 fnDl698AL_RptRspHandle(u8 chan);
#endif //_DL698_AL_H_
