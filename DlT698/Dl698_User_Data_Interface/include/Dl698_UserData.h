/********************************************************************
Filename:       Dl698_UserData.h
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
#ifndef _DL698_USERDATA_H_
#define _DL698_USERDATA_H_

/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"

#ifdef __cplusplus
extern "C"
{
#endif
/*********************************************************************
* MACROS
*/
//�ӿ���id�궨��
#define CLASSID_ENERGY        1   //�������ӿ���
#define CLASSID_NEED          2   //��������ӿ���
#define CLASSID_SP_VAR        3   //��������ӿ���
#define CLASSID_POWER         4   //���ʽӿ���
#define CLASSID_HM_VAR        5   //г�������ӿ���
#define CLASSID_DATA_VAR      6   //���ݱ����ӿ���
#define CLASSID_EVENT         7   //�¼�����ӿ���
#define CLASSID_PARA_VAR      8   //���������ӿ���
#define CLASSID_FREEZE        9   //�������ݽӿ���
#define CLASSID_COLL_MONIT    10  //�ɼ���ؽӿ���
#define CLASSID_COLLECT       11  //���Ͻӿ���
#define CLASSID_PULSE_MEAS    12  //��������ӿ���
#define CLASSID_LOAD_CTL      13  //���ɿ��ƽӿ���
#define CLASSID_REGIONR       14  //����ͳ�ƽӿ���
#define CLASSID_ADD           15  //�ۼ�ƽ���ӿ���
#define CLASSID_EXTREME       16  //��ֵ���߽ӿ���
#define CLASSID_SHOW          17  //��ʾ�ӿ���
#define CLASSID_FILE_TRANS    18  //�ļ�����ӿ���
#define CLASSID_EQUIP_MNG     19  //�豸����ӿ���
#define CLASSID_APP_CONN      20  //Ӧ�����ӽӿ���
#define CLASSID_ESAM          21  //ESAM�ӿ���
#define CLASSID_INPUT_OUTPUT  22  //��������豸�ӿ���
#define CLASSID_TOTAL_GRP     23  //�ܼ���ӿ���
#define CLASSID_DISCIP_EVT    24  //�����¼�����ӿ���
#define CLASSID_GPRS          25  //���߹���ͨ�Žӿ���
#define CLASSID_ETHERNET      26  //��̫��ͨ�Žӿ���

//OIA2
#define OIA2_ENERGY_ALL 0x0
#define OIA2_ENERGY_FUNDWAVE   0x1
#define OIA2_ENERGY_HARMONICWAVE   0x2
#define OIA2_ENERGY_IRONLOSS 0x3
#define OIA2_ENERGY_COPPERLOSS 0x4
#define OIA2_ENERGY_RELATE 0x5

#define OIA2_NEED_NOW 0x0
#define OIA2_NEED_FRERZE 0x1

#define OIA2_VAR_EMU 0X0    //����
#define OIA2_VAR_STATISTIC 0x01 //ͳ��

#define OIB2_PHASE_ALL  0X0
#define OIB2_PHASE_A    0X1
#define OIB2_PHASE_B    0X2
#define OIB2_PHASE_C    0X3

//OIA1
#define SELECTOR_0 0x0
#define SELECTOR_1 0x1
#define SELECTOR_2 0x2
#define SELECTOR_3 0x3
#define SELECTOR_9 0x9

//�û����ݽӿں���
u8 fnDl698_GetValue(
    u32  OAD,           //OAD
    u16  classId,       //class id
    u16  oiindex,       //oi list index
    u8  *pParBuf,       //paramter buffer ,�Ǽ�¼�͵�pParBufΪNULL����¼�͵�pParBufָ������RCD����Ϣ
    u16 *parLen,        //paramter buffer length ,�Ѵ�������ݳ���
    u16  retMaxLen,     //return result buffer max length�����ص����ݳ��ȱ���<= retMaxLen
    u8  *pRetBuf,       //return result buffer
    u16 *retLen,        //return result buffer length
    u8   blockReq,      //req is get-next��Э��ջ�յ�����GET-NEXT����
    u8  *blockRsp       //rsp is blocking�������ص����ݳ���data length>max lengthʱ����BlockRsp��1��˵�����и���������Ҫ�´ζ�ȡ
);

u8 fnDl698_SetValue(
    u32  OAD,          //oad
    u16  classId,      //class id
    u8  *pParBuf,      //parameter buffer
    u16 *parLen        //parameter length �Ѵ�������ݳ���
);

u8 fnDl698_ActMeth(
    u32  OMD,        //OMD
    u16  classId,    //class id
    u8  *pParBuf,    //parameter buffer
    u16 *parLen,     //parameter length ���Ѵ���Ĳ������ݳ���
    u16  retMaxLen,  //return result buffer max length
    u8  *pRetBuf,    //return result buffer
    u16 *retLen      //return result buffer length
);

u8 fnDl698_SafetyCertiHandle(
    u8   req_type,   //��������
    u32  OMD,        //OMD
    u8  *pParBuf,    //parameter buffer
    u8  *pRetBuf,    //return result buffer
    u16 *retLen      //return result buffer length
);

//��ȡβ���ϱ���Ϣ��־������β���ϱ���Ϣ�򷵻�1�����򷵻�0
u8 fnDl698_GetFlwRptFlag(u8 chan);       //channel number

//�ɹ�����0,ʧ�ܷ��ط�0
void fnDl698_FlwRptValue(
    u16  retMaxLen,     //return result buffer max length�����ص����ݳ��ȱ���<= retMaxLen
    u8  *pRetBuf,       //return result buffer
    u16 *retLen         //return follow info length
);

//-�û����ݽӿ�

/*********************************************************************
* @fn      fnDl698_RptRspValue
* @brief   ��ReportRsp�Ļظ���Ϣ�������,������buffer�󣬵���698�Ŀռ��ͷź����ͷŵ�buffer
* @param   chan      ͨ�����
*          Result    �ϱ��¼���������0�ϱ��ɹ��������ϱ�ʧ�ܣ�ʧ��ԭ��˵����XXX���ϱ��ɹ�ʱpBuffer�ſ��ã�ʧ��ʱpBufferΪNULL
*          pBuffer   ��������Ϣ��buf
*          BufferLen ��������Ϣ�ĳ���
* @return  ��
*/
VOID fnDl698_RptRspValue(
    u8  chan,         //channel number
    u8* pBuffer,     //��������Ϣ��buf
    u8  *pOADNum);   //��������Ϣ�ĳ���

extern void fnDl698_ReportValue(
    u8  *pParBuf,      //parameter buffer
    u8  *pOADNum        //
);

//IC��������
//gDl698_OIList_ICXX �� gDl698_SecList_ICXX��һһ��Ӧ��
extern CONST u16 *gDl698_OIList[];
extern CONST u8 gDl698_OIList_NUMBER;
//extern u16 gDl698_SecList_IC01[];//Ĭ��ֵΪĬ�ϰ�ȫģʽ�������û������޸ģ��޸ĺ�Ϊ��ʾ��ȫģʽ����

extern CONST u16 gDl698_NumIC[];

//-IC��������

//Report.c��������ӿڵļ�������
//����ϱ��Ĵ���˳��
//1. fnDl698AL_RptNotiHandle ��˵��ã���ȡ��ǰ�Ƿ������ϱ���BUFFERָ�����󳤶�
//2. fnDl698AL_RptNotiToAl   ��˵��ã����ϱ����ݷŵ�BUFFER�У�����֪��Ч���ݳ��ȣ�
//3. fnDl698_RptRspValue Э��ջ���ã���֪����ϱ������Ƿ�ɹ�
//
/*********************************************************************
* @fn      fnDl698AL_RptReqHandle
* @brief   �����ϱ���Ϣʱ����˵��ô˺�������ReportNotification����������AL���
* @param   chan         ͨ�����
*          rpt_type     �ϱ����ͣ���ReportNotificationList����ReportNotificationRecordList
*          repeat_flag  �Ƿ����ش�֡����Ϊ1,����Ϊ0
*          pBufferAddr  Э��ջΪ�˴��ϱ��¼������BUFFER��ʼ��ַ
*          BufLen       BUFFER��󳤶ȣ�����˼�⵽��Ҫ�ϱ������ݴ���BufLen, ���ϱ���
*                       �����Ҫ��֮ǰ�����txbuf�ͷŵ�
* @return  ����������ReportNotificaionHandle���û���⣬�򷵻�0�����򷵻ش���
*/
//s8 fnDl698AL_RptNotiHandle(u8 chan, u8 rpt_type, u8 retrans_flag, u8** pBufferAddr, u16 *BufLen);
//u8 fnDl698AL_RptNotiHandle(u8 chan, u8 rpt_type, u8 retrans_flag);

/*********************************************************************
* @fn      fnDl698AL_RptNotiToAl
* @brief   ��˽�Ҫ�ϱ������ݴ���AL�㣬�˺���ΪAL����ñ�˵ĺ���
* @param   chan     ͨ�����
*          DataLen  �����ϱ������ݳ���
*
* @return  ��������0 ��ʾ�ɹ��������ʾʧ�ܣ����ʧ�ܣ��ٴ��ϱ�����Ҫ���µ���fnDl698AL_RptReqHandle�ٴη���BUFFER
*/
u8 fnDl698AL_RptNotiToAl(u8 chan, u16 DataLen);

/*********************************************************************
* @fn      fnRaed_DefaultSecPar
*
* @brief   ��ȡOI��Ĭ�ϰ�ȫģʽ����
*
* @param   oi
*
* @return  ����OI��Ĭ�ϰ�ȫģʽ������ʧ�ܷ���0xFFFF��ԭ��ΪĬ�ϰ�ȫģʽ�����б���δ�ҵ���oi
*/
extern u16 fnRaed_DefaultSecPar(u16 oi);
extern u16 fnRead_FormulationSecPar(u16 oi);
extern u8 fnReadMeter_Esam(u8*  uBuf) ;
extern u8 fnUpdateMeterNo(void);
extern u8 fnReadAuthOn_Esam(u8*  uBuf);
extern u8 fnUpdateAuthOn(void);
extern u8 fnRead_SecMode(void);
extern u8 fnReadPswVer_Esam(u8*  uBuf);
extern u8 fnUpdatePswSta(void);
extern void fnWrite_Broatcast_SafetyType(u8  Type);
extern u8 fnRead_Broatcast_SafetyType(void);
extern void fnGetCurrTime(sDate_time_s_TypeDef * ptime);
extern u8 fnReadDlyTime_Esam(u32*  DlyTime, u8 CA, u8 Type);
extern u8 fnConnDataDefault(u8 chan, u8 CA);
extern u8 fnConnSizeDefault(u8 chan, u8 CA);
extern void fnConnDataInit(u8 Chan, u8 CA);
extern u8 fnReadConnSize(sCommSize_TypeDef *Size, u8 chan, u8 CA);
extern u8 fnWriteConnSize(sCommSize_TypeDef *LinkSize, u8 chan, u8 CA);
extern void  fnCommStatus(u8 id);
extern u8 CheckTPeriodValid(u8 *Buf, u8 tpnum);
extern u8 fnReport_EvtData(u8 *pRetBuf, u16 *pRetLen, u8 item,  u8  *blockRsp);
extern u8 fnCheck_ReportCnt(void);
extern u8 fnCheck_RptType(void);
extern u8 fnCheck_nMacErr(void);

extern u8 fnRead_SecurtyStatus(void);
extern u8 fnRead_tIRDly(void);
extern u8 fnChk_TermBinCoreAuthStatus(u8 chan);
extern u8 fnChk_AuthOnStatus(void);
extern u8 fnReadStatus_PrgEnable(void);
extern u8 fnChkStatus_tLinkDly(void);
extern void  fnGet_ConnServer(u8 *Data);

#endif
