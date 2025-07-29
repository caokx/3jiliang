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
//�ϱ�����
#define  DL698AL_RPTNOTI_LIST            1    //ReportNotificationList
#define  DL698AL_RPTNOTI_RECORDLIST      2    //ReportNotificationRecordList

//AL��DL�Ƿ��ڿ���״̬
#define  DL698AL_AL_IDLE                 0    //AL����IDLE״̬
#define  DL698AL_DL_IDLE                 0    //DL����IDLE״̬

//ReportNotification ������
#define  DL698AL_RPTHANDLE_SUCC          0    //AL���Է���ReportNotification
#define  DL698AL_RPTHANDLE_TYPEFAULT     1    //�ϱ����ʹ��󣬵���Բ�ԭ����ٴη����ϱ�
#define  DL698AL_RPTHANDLE_RETRANFAULT   2    //�ش���־���󣬵���Բ�ԭ����ٴη����ϱ�
#define  DL698AL_RPTHANDLE_DLBUSY        3    //DL��busy,���ٴη����ϱ�
#define  DL698AL_RPTHANDLE_ALBUSY        4    //AL��busy,���ٴη����ϱ�
#define  DL698AL_RPTHANDLE_BUFINVALID    5    //��������Ч��buffer,���ٴη����ϱ�

//ReportNotiToAL������
#define  DL698AL_RPTHANDLE_LENFAULT      6    //�ϴ����ȴ���
//û����Ҫ�ϱ�����Ϣ
#define  DL698AL_RPTHANDLE_NORPTINFO     7    //û����Ҫ�ϱ�����Ϣ
#define  DL698AL_RPTHANDLE_OTHFAULT      255  //��������

//��APDU��������ߴ�Ϊ2K
#define  DL698AL_APDU_MAX_SIZE           2048  //���APDU�ߴ�

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
