/********************************************************************
Filename:       Dl698_AL.h
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
#ifndef _DL698_AL_H_
#define _DL698_AL_H_

/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"
#include "Dl698AL_def.h"
#ifdef __cplusplus
extern "C"
{
#endif

//protocolconformance��=bit-string��SIZE��64���� bit offset
typedef enum
{
    DL698AL_CPRO_ASSNEGO                = 0,
    DL698AL_CPRO_GET                    = 1,
    DL698AL_CPRO_GETLIST                = 2,
    DL698AL_CPRO_GETREC                 = 3,
    DL698AL_CPRO_GETPROXY               = 4,
    DL698AL_CPRO_GETPROXYREC            = 5,
    DL698AL_CPRO_GETNEXT                = 6,
    DL698AL_CPRO_SET                    = 7,
    DL698AL_CPRO_SETLIST                = 8,
    DL698AL_CPRO_SETWITHGET             = 9,
    DL698AL_CPRO_SETPROXY               = 10,
    DL698AL_CPRO_SETPROXYWITHGET        = 11,
    DL698AL_CPRO_ACT                    = 12,
    DL698AL_CPRO_ACTLIST                = 13,
    DL698AL_CPRO_ACTWITHGET             = 14,
    DL698AL_CPRO_ACTPROXY               = 15,
    DL698AL_CPRO_ACTPROXYWITHGET        = 16,
    DL698AL_CPRO_RPT                    = 17,
    DL698AL_CPRO_FLLORPT                = 18,
    DL698AL_CPRO_ACDRPT                 = 19,
    DL698AL_CPRO_SLICE                  = 20,
    DL698AL_CPRO_GETREQSLI              = 21,
    DL698AL_CPRO_GETRSPSLI              = 22,
    DL698AL_CPRO_SETREQSLI              = 23,
    DL698AL_CPRO_SETRSPSLI              = 24,
    DL698AL_CPRO_ACTREQSLI              = 25,
    DL698AL_CPRO_ACTRSPSLI              = 26,
    DL698AL_CPRO_PRXREQSLI              = 27,
    DL698AL_CPRO_PRXRSPSLI              = 28,
    DL698AL_CPRO_RPTSLI                 = 29,
    DL698AL_CPRO_DLT645                 = 30,
    DL698AL_CPRO_SEC                    = 31,
    DL698AL_CPRO_GET0                   = 32,
    DL698AL_CPRO_SET0                   = 33,
} eDl698AL_CPro_TypeDef;

//FunctionConformance��=bit-string��SIZE��128����
typedef enum
{
    DL698AL_FPRO_ENERGY = 0,
    DL698AL_FPRO_TACT   = 1,
    DL698AL_FPRO_IENERGY = 2,
} eDl698AL_CFun_TypeDef;

//��ȫģʽ�������붨��
#define DL698AL_SECMASK_PRXACT      0x0001
#define DL698AL_SECMASK_PRXSET      0x0002
#define DL698AL_SECMASK_PRXGET      0x0004
#define DL698AL_SECMASK_RSV         0x0008
#define DL698AL_SECMASK_ACT_CYPMAC  0x0010
#define DL698AL_SECMASK_ACT_CYP     0x0020
#define DL698AL_SECMASK_ACT_PLAMAC  0x0040
#define DL698AL_SECMASK_ACT_PLA     0x0080
#define DL698AL_SECMASK_SET_CYPMAC  0x0100
#define DL698AL_SECMASK_SET_CYP     0x0200
#define DL698AL_SECMASK_SET_PLAMAC  0x0400
#define DL698AL_SECMASK_SET_PLA     0x0800
#define DL698AL_SECMASK_GET_CYPMAC  0x1000
#define DL698AL_SECMASK_GET_CYP     0x2000
#define DL698AL_SECMASK_GET_PLAMAC  0x4000
#define DL698AL_SECMASK_GET_PLA     0x8000

/*LINK-APDU TAG*/
#define DL698AL_APDU_TAG_LNKREQ     0x01  //2
#define DL698AL_APDU_TAG_LNKRSP     0x81  //129
/*Client-APDU TAG*/
#define DL698AL_APDU_TAG_CONREQ     0x02  //2
#define DL698AL_APDU_TAG_RLSREQ     0x03  //3
#define DL698AL_APDU_TAG_GETREQ     0x05  //5
#define DL698AL_APDU_TAG_SETREQ     0x06  //6
#define DL698AL_APDU_TAG_ACTREQ     0x07  //7
#define DL698AL_APDU_TAG_RPTRSP     0x08  //8
#define DL698AL_APDU_TAG_PRXREQ     0x09  //9
/*Server-APDU TAG*/
#define DL698AL_APDU_TAG_CONRSP     0x82  //130
#define DL698AL_APDU_TAG_RLSRSP     0x83  //131
#define DL698AL_APDU_TAG_RLSRPT     0x84  //132
#define DL698AL_APDU_TAG_GETRSP     0x85  //133
#define DL698AL_APDU_TAG_SETRSP     0x86  //134
#define DL698AL_APDU_TAG_ACTRSP     0x87  //135
#define DL698AL_APDU_TAG_RPTNOTI    0x88  //136
#define DL698AL_APDU_TAG_PRXRSP     0x89  //137
#define DL698AL_APDU_TAG_ERRORRSP     0xEE  //238
/*SECURITY-APDU TAG*/
#define DL698AL_APDU_TAG_SECREQ     0x10  //16
#define DL698AL_APDU_TAG_SECRSP     0x90  //144
#define DL698AL_APDU_TAG_SECREQ_PT  0x00
#define DL698AL_APDU_TAG_SECREQ_CT  0x01
#define DL698AL_APDU_TAG_SECREQ_DAR 0x02
#define DL698AL_APDU_TAG_SECRSP_PT  0x00
#define DL698AL_APDU_TAG_SECRSP_CT  0x01
#define DL698AL_APDU_TAG_SECRSP_DAR 0x02
#define DL698AL_APDU_TAG_SECRSP_MAC 0x00

//length define for temp buf
#define TEMP_MAXSIZE    2048
#define TEMP_GETREC_MAXSIZE    3072   //��ȡ��¼������ʱ������3k
//length define for SEC
#define DL698AL_ESAMBUF_MAXSIZE 2048
#define DL698AL_SIDCHR_LEN      4
#define DL698AL_MAC_LEN         4
/*��������ʧ��ԭ�򣿣�*/

//-------------�쳣Ӧ���������Ͷ���--------------
#define DATA_ERRORRSP_APDUERR           1   //APDU�޷�����
#define DATA_ERRORRSP_NOTSEVR           2   //����֧��
#define DATA_ERRORRSP_OTH               255 //������

//���ݷ��ʽ��DAR��Data Access Result�� �궨��
#define DATA_ACCESS_RESULT_SUC          0   //�ɹ�
#define DATA_ACCESS_RESULT_HD           1   //Ӳ��ʧЧ
#define DATA_ACCESS_RESULT_TEMP         2   //��ʱʧЧ
#define DATA_ACCESS_RESULT_DENY         3   //�ܾ���д
#define DATA_ACCESS_RESULT_UNDEF        4   //����δ����
#define DATA_ACCESS_RESULT_CLAS         5   //����ӿ��಻����
#define DATA_ACCESS_RESULT_UNAVA        6   //���󲻴���
#define DATA_ACCESS_RESULT_TYPE         7   //���Ͳ�ƥ��
#define DATA_ACCESS_RESULT_ACC          8   //Խ��
#define DATA_ACCESS_RESULT_BLKUNV       9   //���ݿ鲻����
#define DATA_ACCESS_RESULT_LGET         10  //��֡������ȡ��
#define DATA_ACCESS_RESULT_NLGET        11  //�����ڷ�֡����״̬
#define DATA_ACCESS_RESULT_LSET         12  //��дȡ��
#define DATA_ACCESS_RESULT_NLSET        13  //�����ڿ�д״̬
#define DATA_ACCESS_RESULT_BLKNUM       14  //���ݿ������Ч
#define DATA_ACCESS_RESULT_SECERR       15  //�����/δ��Ȩ
#define DATA_ACCESS_RESULT_SPDCONST     16  //ͨ�����ʲ��ܸ���
#define DATA_ACCESS_RESULT_YOVER        17  //��ʱ������
#define DATA_ACCESS_RESULT_DOVER        18  //��ʱ������
#define DATA_ACCESS_RESULT_ROVER        19  //��������
#define DATA_ACCESS_RESULT_SECNMATH     20  //��ȫ��֤��ƥ��
#define DATA_ACCESS_RESULT_DUPCHG       21  //�ظ���ֵ
#define DATA_ACCESS_RESULT_ESAMFAIL     22  //ESAM��֤ʧ��
#define DATA_ACCESS_RESULT_SECFAIL      23  //��ȫ��֤ʧ��
#define DATA_ACCESS_RESULT_CLTNMATH     24  //�ͻ���Ų�ƥ��
#define DATA_ACCESS_RESULT_CHGCNTERR    25  //��ֵ��������
#define DATA_ACCESS_RESULT_PUROVER      26  //���糬�ڻ�
#define DATA_ACCESS_RESULT_ADDERR       27  //��ַ�쳣
#define DATA_ACCESS_RESULT_SYMENC       28  //�Գƽ��ܴ���
#define DATA_ACCESS_RESULT_ASYMENC      29  //�ǶԳƽ��ܴ���
#define DATA_ACCESS_RESULT_MACERR       30  //ǩ������
#define DATA_ACCESS_RESULT_SUSPD        31  //���ܱ����
#define DATA_ACCESS_RESULT_TIMLAGERR    32  //ʱ���ǩ��Ч
#define DATA_ACCESS_RESULT_TIMOUT       33  //����ʱ
#define DATA_ACCESS_RESULT_ESAMP1P2     34  //ESAM��P1P2����ȷ
#define DATA_ACCESS_RESULT_ESAMLC       35  //ESAM��LC����
//-Э���Զ���������� linxm
#define DATA_ACCESS_RESULT_OVERFLOAT_ERR 200 //�������left >right
#define DATA_ACCESS_AL_ASSO_ERROR        201 //�Ѿ����������ӣ����ظ����ӣ����ظ����ӵ��������Ϳ����ˣ�
#define DATA_ACCESS_AL_MEMALLOC_ERR      202
#define DATA_ACCESS_RESULT_LGET_ING      203 //��Ƭ֡��������У����յ��Ƿ�Ƭ֡ʱ�ܾ�
#define DATA_ACCESS_LENTH_ERROR          210//�������������Ͳ�ƥ��
#define DATA_CTL_GATA_ERROR              211//�̵������ƴ���
//-end
#define DATA_ACCESS_RESULT_OTH          255 //����

//event_type:   0x0101 ��·�㽨������
//              0x0102 ��·��Ͽ�����
//              0x0103 ��·������ʧ��
//              0x0104 ��·���ظ�����
//              0x0105 ��·������ʧ��
//              0x0106 inter-octet timeout
//              0x0107 inactive timeout

//              0x0201 Ӧ�ò㽨������
//              0x0202 Ӧ�ò�Ͽ����ӣ�ͨ���Ͽ�HDLC���������Ͽ�Ӧ�ò�����
//              0x0203 Ӧ�ò�����ʧ��
//              0x0204 Ӧ�ò�Ͽ�����ʧ��
//              0x0205 Ӧ�ò������Ѿ����ڵ����ӣ�Ӧ�ò㲻��������������
//              0x0206 Ӧ�ò�Ͽ����ӣ�ͨ��RLRQ�Ͽ�Ӧ�ò�����
//              0x0207 Ӧ�ò�Ͽ������ڵ�����

#define DL698DL_EVENT_CONNECT      0x0101
#define DL698DL_EVENT_BREAK        0x0102
#define DL698DL_EVENT_FAIL         0x0103
#define DL698DL_EVENT_RECONNECT    0x0104
#define DL698DL_EVENT_DUMMYBREAK   0x0105
#define DL698DL_EVENT_OCTTIMEOUT   0x0106
#define DL698DL_EVENT_INACTTIMEOUT 0x0107

#define DL698AL_EVENT_CONNECT             0x0201
#define DL698AL_EVENT_BREAK             0x0202
#define DL698AL_EVENT_CONNECTFAIL       0x0203
#define DL698AL_EVENT_RELEASEFAIL       0x0204
#define DL698AL_EVENT_RECONNECT       0x0205
#define DL698AL_EVENT_RELEASE             0x0206
#define DL698AL_EVENT_DUMMYDIS            0x0207

//������
#define DL698AL_FUNCODE_LINKMANAG     1    //��·���ӹ���
#define DL698AL_FUNCODE_DATAINTER     3    //���ݽ���

//��ǰ֡����
#define DL698AL_DIRPRM_SERVREPORT     2    //������������ϱ�
#define DL698AL_DIRPRM_SERVRSP        3    //�������Կͻ����������Ӧ

//ʱ���ǩ
#define DL698AL_TIMETAG_SUCCESS       1    //ʱ���ǩ��ʽ����������ȷ
#define DL698AL_TIMETAG_ERROR         2    //ʱ���ǩ��������
#define DL698AL_NO_TIMETAG            3    //��ʱ���ǩ

#define  RPTEVT_POWNDOWN   1  //�����ϱ���������,�ϱ�3011�����¼���¼����
#define  RPTEVT_POWNUP     2  //�����ϱ�������+MAC,�ϱ�3011�����¼���¼����
#define  RPTEVT_OTHER      3  //�����¼���¼�ϱ�������+MAC���ϱ�3320��2015����

void fnDl698AL_GetCurrTime(sDl698date_time_s_TypeDef * ptime); //ͨ��RTC��ȡ��ǰʱ��
u8 fnDl698AL_Decode_TimeTag(u8 chan, u8* recvdata);      //����ʱ���ǩ
u16 fnDl698AL_TimeTagPkg(u8 chan, u8 *send_buf);
u8 fnDl698AL_TimeTag_Handle(u8 chan);
void fnDl698AL_FlwRptPkg(u8 chan, u16 retMaxLen, u8 *pRetBuf, u16 *retLen);
u8 fnDl698AL_DelayHandle(u8 chan, u8 block_flag, u8 temp_oad_num);

u16 fnDl698AL_Gen_SecRsp(u8 chan);
u16 fnDl698AL_SecReq_Handle(u8 chan);
u8 fnDl698AL_TimeTag_Valid(u8 chan);
u16 fnDl698AL_Resport_SecRsp(u8 chan);

extern  ErrorStatus fnSetCurrTime(sDate_time_s_TypeDef * ptime);
extern u8 fnDl698AL_Check_Auth(u8 chan, u8 tag_flag, u32 OAD_OMD);

#ifdef __cplusplus
}
#endif

#endif
