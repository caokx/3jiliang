
#ifndef  _APP_H
#define  _APP_H

//------------------------------
#define MAX_FL                    0//12 //��������
#define MAX_FLPrice               0 //�����ʵ����
#define DEFAULT_FL                    1//   Ĭ�Ϸ�����

#define MAX_POTTABLE                  0     //���ʱ�α���

#define MAX_POT                     0    //���ʱ����
#define MAX_TIMEZONE                  0     //���ʱ����
#define MAX_HOLIDAY                 0   //��󹫹�������

#define MAX_CYCDISP                 99    //�����������
#define MAX_KEYDISP                 99    //����������

#define MAX_EVSTAT                15    //����¼�ͳ��
#define MAX_EVRECORD                  10    //����¼���¼

#define MAX_POWDN_EVRECORD          100      //�������¼���¼
#define MAX_PRG_EVRECORD            10      //������¼���¼
#define MAX_CLR_EVRECORD            10      //��������¼���¼
#define MAX_NEEDCLR_EVRECORD          10      //������������¼���¼
#define MAX_EVENTCLR_EVRECORD       10      //����¼������¼���¼
#define MAX_SETCLOK_EVRECORD        10      //���Уʱ�¼���¼
#define MAX_PRGPOTTABLE_EVRECORD    10      //���ʱ�α���¼���¼
#define MAX_PRGTIMEZONE_EVRECORD    10      //���ʱ������¼���¼
#define MAX_PRGWEEKEND_EVRECORD     10      //��������ձ���¼���¼
#define MAX_PRGHOLIDAY_EVRECORD     10       //��󹫹����ձ���¼���¼
#define MAX_PRGP_EVRECORD           10      //����й���������ֱ���¼���¼
#define MAX_QRGP_EVRECORD         10      //����޹����1�����ֱ���¼���¼
#define MAX_PRGRMDAY_EVRECORD       10      //�������ձ���¼���¼
#define MAX_OPENCOVER_EVRECORD      10      //��󿪸��¼���¼
#define MAX_OPENTAIL_EVRECORD       10      //��󿪶�ť���¼���¼
#define MAX_GATEOFF_EVRECORD        10      //�����բ�¼���¼
#define MAX_GATEON_EVRECORD         10      //����բ�¼���¼
#define MAX_BUYEG_EVRECORD          10      //��󹺵����¼���¼
#define MAX_BUYMONEY_EVRECORD       10      //��󹺽���¼���¼
#define MAX_PrgRatePrice_EVRECORD     10      //�����ʱ���¼���¼
#define MAX_PrgLadderPrice_EVRECORD 10    //�����ݵ�۱���¼���¼
#define MAX_PrgSetPsw_EVRECORD    2   //�����Կ�����¼���¼
#define MAX_InsertCardErr_EVRECORD  10    //����쳣�忨�¼���¼
#define MAX_ReturnMoney_EVRECORD    10    //����˷��¼���¼
#define MAX_MagnetDisturb_EVRECORD  10    //�㶨�ų������¼���¼
#define MAX_RelayStatErr_EVRECORD     10      //��󸺺ɿ��������¼���¼
#define MAX_PowerErr_EVRECORD         10      //����Դ�쳣�¼���¼
#define     MAX_BrdTime_EVRECORD    100 //�㲥Уʱ

#define MAX_EVENTTYPE       4   //��������¼�����(ʵʱ�ж�״̬������)

#define MAX_LADDER                6       //��������

#define DL645_MAX_RMDAY                   12    //��������

#define MAX_CipherKey                 32    // �����Կ����
#define MAX_SafePara                  64    // ���ȫģʽ���ò���

//--------����Ҫ��-�洢����--------
#define MAX_FRZWINK_RECORD                3 //���˲ʱ����
#define MAX_FRZMIN_RECORD1                525600    //����1 �洢���
#define MAX_FRZMIN_RECORD2                35040       //����2 �洢���
#define MAX_FRZHOUR_RECORD                254   //������㶳��
#define MAX_FRZDAY_RECORD                 365   //����ն���
#define MAX_FRZRMDAY_RECORD                12   //��������
#define MAX_FRZMONTH_RECORD                24   //�¶���
#define MAX_FRZLADDER_RECORD                   4    //����������
#define MAX_FRZTZONESW_RECORD                  2    //���ʱ�����л�����
#define MAX_FRZPOTSW_RECORD                2    //���ʱ�α��л�����
#define MAX_FRZRATEPRICESW_RECORD            2  //�����ʵ�۱��л�����
#define MAX_FRZLADDERSW_RECORD               2  //�����ݵ�۱��л�����

//--------Ԥ�����洢�ռ����1.3��--------
#define MAX_FRZWINK_STAT                  4 //���˲ʱ����
#define MAX_FRZMIN_STAT                 525600
#define MAX_FRZHOUR_STAT                  330   //������㶳��
#define MAX_FRZDAY_STAT                 475 //����ն���
#define MAX_FRZRMDAY_STAT                  16   //��������
#define MAX_FRZMONTH_STAT                  32   //�¶���
#define MAX_FRZLADDER_STAT                 6    //����������
#define MAX_FRZTZONESW_STAT                3    //���ʱ�����л�����
#define MAX_FRZPOTSW_STAT                  3    //���ʱ�α��л�����
#define MAX_FRZRATEPRICESW_STAT          3  //�����ʵ�۱��л�����
#define MAX_FRZLADDERSW_STAT                 3  //�����ݵ�۱��л�����

#define MAX_FRZMIN_LINE                  8  //�����Ӷ�����������

#define MAX_MACERR                  200  //MAC��֤����������

#define FlashAdMax  0x80000

#define First_DataInit    1
#define Comm_DataInit    1

#include <BSP.h>

#include <Memory.h>
#include <Types.h>
#include <File.h>

#include <Power_Up_Down.h>
#include <Measure.h>
#include <Bkgrd.h>
#include <Energy.h>
#include <Harmonic.h>
#include <Event.h>

#include <Secret.h>
#include <Output.h>
#include <Freeze.h>
#include <Dl645_ICEsam.h>

#include <Scom.h>
#include <Dl645B_Com.h>

#include <Globals.h>

#include "Dl698_Type.h"
#include "Dl698_Scom.h"
#include "Dl698_Globals.h"
#include "Dl698_DL.h"
#include <Dl698_EsamOp.h>
#include "Dl698_Memory.h"
#include "Dl698_UserData_Oad2DI.h"
#include "Dl698_UserData.h"

// dyf ������������ͷ�ļ�
#include "app_rn7306.h"

#include <SysConst.h>

#endif  //_APP_H
