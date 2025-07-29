
#define  DL645_FILE_GLOBALS
#include <App.h>
#include "ProDefine.h"

//=========����������,������ȶ�==================

// --------------------------------3P4-----------------------------------
#if(METERTYPE == 0)
// ���ܱ�

#endif
#if(METERTYPE == 1)
//Զ�̷ѿر�
const sDocment_TypeDef DocParaDefault _reserve =
{
    0x00, 15, 0x01, 80, nHarmonic, 60, 300, 0x00, 0x00
};
const sComPara_TypeDef ComParaDefault =
{
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
    2, 2, 6, 6, 6, 0x00
};

const sDispPara_TypeDef DispParaDefault _reserve =
{
    5,      //�ϵ�ȫ����ʾʱ��
    60,     //�������ʱ�� 60
    10,     //��ʾ�鿴�������ʱ��10
    30,     //�޵簴����Ļפ�����ʱ��30
    2,      //��ʾ����С��λ��
    4,      //��ʾ����С��λ��
    0,      //Һ���ڢ���������
    5,      //ѭ������
    23,     //������ʾ����
    5,
    60,
    {
        //�����  OAD              ��OAD-------
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, //������
        0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x00, 0x00, 0x00,
    },
    {
        //�����  OAD             CSD-------
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, //������(���ͻ���źͱ�ŷ�����)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x02, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x03, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x04, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x05, 0x04, 0x00, 0x00, 0x01, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x01, 0x04, 0x00, 0x00, 0x02, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x02, 0x04, 0x00, 0x00, 0x02, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x03, 0x04, 0x00, 0x00, 0x02, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x04, 0x04, 0x00, 0x00, 0x02, 0x02, 0x05, 0x50, 0x01,
        0x00, 0x05, 0x04, 0x00, 0x00, 0x02, 0x02, 0x05, 0x50, 0x01,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x40, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x40, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40, 0x00, //
        0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x01, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0A, 0x20, 0x00,
    },
};

const sOutputPara_TypeDef OutputParaDefault _reserve =
{
    0x00c8, 0x0003,
    0x8000, 0x0004,
    0x0050, 0x0010,
    0x8000, 0x0100,
    0x8000, 0x1000,
    0x8000, 0x2000,
    0x400c, 0x0021, 0x0021, 0x0021, 0x0003,
    0x400c, 0x0021, 0x0021, 0x0021, 0x0003,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

const u8 CipherKeyParaDefault[3] =
{
    0x14, 0x00, 0x00
};
//---------�����ϱ�----------
const sEvtRptPara_TypeDef EvtReportDefault _reserve =
{
    0x01,
    0x00,
    {0x03, 0x04, 0x80, 0x00, 0x00, 0x00, 0x00, },

    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, },

    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, },

    0x01,

    0x00,

    {0x09, 0x00, 0x00 },

    0x00
};
#endif
#if(METERTYPE == 2)
// ���طѿر�

#endif

const sTemperSchoolPara_TypeDef TemperSchoolParaDefault _reserve =
{
    {
        {0, 10000, 0},
        {0, 10000, 0},
        {0, 10000, 0},
        {0, 10000, 0}
    }
};

const sHighParaFile_TypeDef HighParaDefault _reserve =
{
    0x05,
    0x41,
    0x14,

    {MeterConst},  //2000 ���峣��
    {MeterConst},  //2000

    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00},           // ���
    0x01,           // CT
    0x01,           // PT
    0x00,           // 0--��������  1--��������
    0x50,
    1320,

    {0x12, 0x34, 0x56, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    0x00,
    30,
    30,
    30,
    300000,
    1440,
    30,
    {2640, 1540, 2354, 2046, 0},

    0x0000,         /*"u16 RTCDota0; 2�����߳�ʼƵ��ƫ��"*/
    2,      /*"u16 CurveMode; ����ģʽ" dyf ��̼��Ĭ��2�����ߣ�У׼Dota0 */
    0,      /*"u16    DATA0;4�λ���3�����߳�ʼƵ��ƫ��"*/
    0,      /*"u16    XT1;�����¶����߶����¶�"*/
    0,      /*"u16    ALPHA;����һ���¶�ϵ��"*/
    0,      /*"u16    BETA;��������¶�ϵ��"*/
    0,      /*"u16    GAMMA;���������¶�ϵ��"*/
    0,      /*"u16    ZETA;�����Ĵ��¶�ϵ��"*/

    {0x00, 0x00, 0x00, 0x00}, //RTCAdj
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //RTCCalData

    {0x00, 0x00, 0x00, 0x00},
};

const sASCIIParaFile_TypeDef ASCIIParaDefault _reserve =
{
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {"00000000000000000000000000000000"},
    #if (HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_577)
    {"57.7V"},
    #else
    {"220.0V"},
    #endif
    #if (RateIb == 15000)
    {"0.015A"},
    {"0.075A"},
    #else
    {"0.400A"},
    {"1.000A"},
    #endif
    #if ((HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_577)||(HARDWARE_TYPE_CONFIG == HARDWARE_TYPE_DIAN_TAN_BIAO_220_1_5))
    {"1.500A"},
    {"6.000A"},
    #else
    {"10.00A"},
    {"100.0A"},
    #endif
    {'B', 0x00, 0x00, 0x00}, // dyf �й�Ĭ��B��
    {'2', '.', '0', 0x00},  // dyf �޹�Ĭ��2.0��

    {"DTZYXXX-X"},
    {0, 0, 0, 10, 6, 2023},
    {"DL/T698.45-2017-WL20"},

    {"00000000000000000000000000000000"},
    {"00000000000000000000000000000000"},
    {"00000000000000000000000000000000"},
    {"AAAAAAAAAAAAAAAA"},
    {"XX", "0001", 1, "20230620", 1, "0123456789ABCDEF"},
    {"00000000000000000000000000000000"},
    {"00000000000000000000000000000000"},
};
//------------------------------------------------------------------------

const sSecretParaFile_TypeDef SecretParaDefault _reserve =
{
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x78, 0x56, 0x34,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    3,
    1440,
    240,
    0,

    1,
    {
        0x00,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, //��ʽ��ȫģʽ��
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
    },

    0x01,  //��Ҫ�����֤

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00
};
//------�¼���¼-----------------
const   sTrim_TypeDef EvtCfgParaDefault _reserve =
{
    //---------���ò���---------------
    {720000, 60 },  //720000
    { 0 },
    { 0 },
    { 60 },
    { 0 },
    { 10000, 5000, 60 }
};

//-------����-8��Ĭ�Ϲ����������Ա�--------
const   sCList8_TypeDef EvtCListOverCurDefault _reserve =
{
    8, CLIST_OverCur_RCDLEN,

    0x00102201, 4,    18,
    0x00202201, 4,    22,

    0x20002200, 2,    26,
    0x20012200, 4,      28,
    0x20042200, 8,      32,
    0x200A2200, 4,     40,

    0x00108201, 4,    44,
    0x00208201, 4,    48,
};

const sCList14_TypeDef EvtMngPlugCListDefault _reserve =
{
    14, Evt_MngPlug_RCDLen,
    0xF1002200, 8,    18,               // ԭESAM���к�
    0x00102201, 4,    26,               // �ε�ʱ�������й��ܵ���
    0x00202201, 4,    30,               // �ε�ʱ�̷����й��ܵ���
    0x00502201, 4,    34,               // �ε�ʱ�̵�I�����޹�����
    0x00602201, 4,    38,               // �ε�ʱ�̵�II�����޹�����
    0x00702201, 4,    42,               // �ε�ʱ�̵�III�����޹�����
    0x00802201, 4,    46,               // �ε�ʱ�̵�IV�����޹�����
    0xF1008200, 8,    52,               // ��ESAM���к�     ע�����Event.h�к궨��
    0x00108201, 4,    60,               // ����ʱ�������й��ܵ���
    0x00208201, 4,    64,               // ����ʱ�̷����й��ܵ���
    0x00508201, 4,    68,               // ����ʱ�̵�I�����޹�����
    0x00608201, 4,    72,               // ����ʱ�̵�II�����޹�����
    0x00708201, 4,    76,               // ����ʱ�̵�III�����޹�����
    0x00808201, 4,    80,               // ����ʱ�̵�IV�����޹�����
};

const sCList8_TypeDef EvtMngUpdateCListDefault _reserve =
{
    8, Evt_MngUpdate_RCDLen,
    0x40272300, 1,    18,               // ������������
    0x00102200, 52,   19,               // ����ǰ�����й��ܵ���
    0x00202200, 52,   71,               // ����ǰ�����й��ܵ���
    0xF0012500, 32,   123,              // ���ط���ʶ
    0xF4022204, 16,   155,              // ����ǰ����汾��
    0xF4028204, 16,   171,              // ����������汾��
    0xF4028202, 32,   187,              // ����Ӧ������
    0x40278200, 1,    219,              // �������
};

const sCList12_TypeDef EvtOpenCoverCListDefault _reserve =
{
    12, Evt_OpenCover_RCDLen,
    0x00102201, 4,    18,               // ����ǰ�����й��ܵ���
    0x00202201, 4,    22,               // ����ǰ�����й��ܵ���
    0x00502201, 4,    26,               // ����ǰ��I�����޹�����
    0x00602201, 4,    30,               // ����ǰ��II�����޹�����
    0x00702201, 4,    34,               // ����ǰ��III�����޹�����
    0x00802201, 4,    38,               // ����ǰ��IV�����޹�����
    0x00108201, 4,    42,
    0x00208201, 4,    46,
    0x00508201, 4,    50,               // ���Ǻ��I�����޹�����
    0x00608201, 4,    54,               // ���Ǻ��II�����޹�����
    0x00708201, 4,    58,               // ���Ǻ��III�����޹�����
    0x00808201, 4,    62,               // ���Ǻ��IV�����޹�����
};

//const sCList6_TypeDef EvtMeterClrCListDefault _reserve =
//{
//  6 , Evt_Clr_RCDLen ,
//  0x00102201 , 4 ,    18 ,
//  0x00202201 , 4 ,    22 ,
//  0x00502201 , 4 ,    26 ,            // ����ǰ��I�����޹�����
//  0x00602201 , 4 ,    30 ,            // ����ǰ��II�����޹�����
//  0x00702201 , 4 ,    34 ,            // ����ǰ��III�����޹�����
//  0x00802201 , 4 ,    38 ,            // ����ǰ��IV�����޹�����
//};

#if(nPhs==ThreePhs)
// ThreePhase
const sCList24_TypeDef EvtMeterClrCListDefault _reserve =
{
    24, Evt_Clr_RCDLen,                 // 114
    0x00102201, 4,    18,
    0x00202201, 4,    22,
    0x00502201, 4,    26,               // ����ǰ��I�����޹�����
    0x00602201, 4,    30,               // ����ǰ��II�����޹�����
    0x00702201, 4,    34,               // ����ǰ��III�����޹�����
    0x00802201, 4,    38,               // ����ǰ��IV�����޹�����

    0x00112201, 4,    42,               // ����ǰA�������й�����
    0x00212201, 4,    46,               // ����ǰA�෴���й�����
    0x00512201, 4,    50,               // ����ǰA���I�����޹�����
    0x00612201, 4,    54,               // ����ǰA���II�����޹�����
    0x00712201, 4,    58,               // ����ǰA���III�����޹�����
    0x00812201, 4,    62,               // ����ǰA���IV�����޹�����

    0x00122201, 4,    66,               // ����ǰB�������й�����
    0x00222201, 4,    70,               // ����ǰB�෴���й�����
    0x00522201, 4,    74,               // ����ǰB���I�����޹�����
    0x00622201, 4,    78,               // ����ǰB���II�����޹�����
    0x00722201, 4,    82,               // ����ǰB���III�����޹�����
    0x00822201, 4,    86,               // ����ǰB���IV�����޹�����

    0x00132201, 4,    90,               // ����ǰC�������й�����
    0x00232201, 4,    94,               // ����ǰC�෴���й�����
    0x00532201, 4,    98,               // ����ǰC���I�����޹�����
    0x00632201, 4,    102,              // ����ǰC���II�����޹�����
    0x00732201, 4,    106,              // ����ǰC���III�����޹�����
    0x00832201, 4,    110,              // ����ǰC���IV�����޹�����
};
#endif

//------���磬Уʱ,��Դ�쳣������оƬ���ϣ��㲥Уʱ-2��Ĭ�Ϲ����������Ա�--------
//------�������-��բ--��բ----------
const   sCList2_TypeDef EvtCList2Default _reserve =
{
    2, CLIST2_RCDLEN,
    0x00102201, 4,    18,
    0x00202201, 4,    22
};

//------ʱ������-1��Ĭ�Ϲ����������Ա�--------
const   sCList1_TypeDef EvtCListZoneDefault _reserve =
{
    1, CLISTZone_RCDLEN,
    0x40152200, 42, 18
};

//------�����ձ��-1��Ĭ�Ϲ����������Ա�--------
const   sCList1_TypeDef EvtCListWeekDefault _reserve =
{
    1, CLISTWeek_RCDLEN,
    0x40132200, 1, 18
};
//------�����ձ��-1��Ĭ�Ϲ����������Ա�--------
const   sCList1_TypeDef EvtCListRmDayDefault _reserve =
{
    1, CLISTDay_RCDLEN,
    0x41162200, 6, 18
};
//------�й���Ϸ�ʽ-1��Ĭ�Ϲ����������Ա�--------
const   sCList1_TypeDef EvtCListPrgPDefault _reserve =
{
    1, CLISTPrgP_RCDLEN,
    0x41122200, 1, 18
};

//------��Կ����-1��Ĭ�Ϲ����������Ա�--------
const   sCList1_TypeDef EvtCListSetPswDefault _reserve =
{
    1, CLISTSetPsw_RCDLEN,
    0xF1002400, 16, 18
};

//----����--ʱ�ӹ���-4-��Ĭ�Ϲ����������Ա�--------
const   sCList4_TypeDef EvtCList4Default _reserve =
{
    4, CLIST4_RCDLEN,
    0x00102201, 4,    18,
    0x00202201, 4,    22,
    0x00108201, 4,    26,
    0x00208201, 4,    30
};

//------���ɿ�������-5-��Ĭ�Ϲ����������Ա�--------
const   sCList5_TypeDef EvtCList5Default _reserve =
{
    5, CLIST5_RCDLEN,
    0xF2052201, 8,    18,
    0x00102201, 4,    26,
    0x00202201, 4,    30,
    0x00108201, 4,    34,
    0x00208201, 4,    38
};

//------���ߵ����쳣--------------
const   sCList2_TypeDef EvtCListNErrDefault _reserve =
{
    2, CLISTNERR_RCDLEN,
    0x20012400, 4,    18,
    0x20012600, 4,    22
};

//------���ʱ�-2��Ĭ�Ϲ����������Ա�--------
const   sCList2_TypeDef EvtCListRateDefault _reserve =
{
    2, CLISTRate_RCDLEN,
    0x40182200, 16, 18,
    0x40192200, 16, 34
};
//------���ݱ�-2��Ĭ�Ϲ����������Ա�--------
const   sCList2_TypeDef EvtCListLadderDefault _reserve =
{
    2, CLISTLad_RCDLEN,
    0x401A2200, 64, 18,
    0x401B2200, 64, 78
};
//------�쳣�忨-4-��Ĭ�Ϲ����������Ա�--------
const   sCList4_TypeDef EvtCListCardErrDefault _reserve =
{
    4, CLISTCardErr_RCDLEN,
    0x202C2202, 4,    18,
    0x202C2201, 4,    22,
    0x00102201, 4,    26,
    0x00202201, 4,    30
};
//------����-6-��Ĭ�Ϲ����������Ա�--------
const   sCList6_TypeDef EvtCListBuyDefault _reserve =
{
    6, CLISTBuy_RCDLEN,
    0x202C8202, 4,    18,
    0x202C2201, 4,    22,
    0x202D2200, 4,    26,
    0x202E2200, 4,    30,
    0x202C8201, 4,    34,
    0x202E8200, 4,    38
};
//-----�˷�-3-��Ĭ�Ϲ����������Ա�--------
const   sCList3_TypeDef EvtCListRtrnDefault _reserve =
{
    3, CLISTRtrn_RCDLEN,
    0x202C2202, 4,    18,
    0x202C2201, 4,    22,
    0x202C8200, 4,    26
};

const  sCListNULL_TypeDef EvtCListNULLDefault _reserve = { 0x00, 18    };
const  sCListNULL_TypeDef EvtPrgListDefault _reserve = { 0x00, CLISTPrg_RCDLEN };
const  sCListNULL_TypeDef EvtPrgPOTListDefault _reserve = { 0x00, CLISTZone_RCDLEN };
const  sCListNULL_TypeDef EvtPrgHldyListDefault _reserve = { 0x00, CLISTPrgHldy_RCDLEN };

#define FRZMINLISTOADNUM    15  //Ĭ�Ϸ��Ӷ�������������Ա�OAD����

#define FRZMINLISTCYCLE1    1    //Ĭ�Ϸ��Ӷ������� 1min ����1
#define FRZMINLISTCYCLE2    15    //Ĭ�Ϸ��Ӷ������� 15min ����2

const   sFrzMinList_TypeDef FrzMinListDefault _reserve =
{
    FRZMINLISTOADNUM, FRZMINRCDLEN,
    FRZMINLISTCYCLE1, 0x00100801, MAX_FRZMIN_RECORD1, 8, FRZSTDLISTLEN,
    FRZMINLISTCYCLE1, 0x00200801, MAX_FRZMIN_RECORD1, 8, FRZSTDLISTLEN + 8,
    FRZMINLISTCYCLE1, 0x20000200, MAX_FRZMIN_RECORD1, 6, FRZSTDLISTLEN + 16,
    FRZMINLISTCYCLE1, 0x20010200, MAX_FRZMIN_RECORD1, 12, FRZSTDLISTLEN + 22,
    FRZMINLISTCYCLE1, 0x20070200, MAX_FRZMIN_RECORD1, 16, FRZSTDLISTLEN + 34,
    FRZMINLISTCYCLE1, 0x20080200, MAX_FRZMIN_RECORD1, 16, FRZSTDLISTLEN + 50,
    FRZMINLISTCYCLE1, 0x200A0200, MAX_FRZMIN_RECORD1, 8, FRZSTDLISTLEN + 66,

    FRZMINLISTCYCLE2, 0x00502801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN,
    FRZMINLISTCYCLE2, 0x00602801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 8,
    FRZMINLISTCYCLE2, 0x00702801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 16,
    FRZMINLISTCYCLE2, 0x00802801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 24,
    FRZMINLISTCYCLE2, 0x01102801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 32,
    FRZMINLISTCYCLE2, 0x01202801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 40,
    FRZMINLISTCYCLE2, 0x02102801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 48,
    FRZMINLISTCYCLE2, 0x02202801, MAX_FRZMIN_RECORD2, 8, FRZSTDLISTLEN + 56,
};
//-------���Ӷ�������0Ĭ��ͷ��������Ĭ����������������������NĬ��ͷ----
const sFrzMinLinePara_TypeDef FrzMinLineDefault0 _reserve =
{
    7,
    (FRZSTDLISTLEN + 74),
    0x00,  //����0��ַƫ��Ϊ0
    (((u32)(FRZSTDLISTLEN + 74) * (u32)MAX_FRZMIN_RECORD1 + 4096 + 4096) & 0xFFFFF000), //--Ԥ��1��bank����bank����-----
    FRZMINLISTCYCLE1,
    (((u32)(FRZSTDLISTLEN + 74) * (u32)MAX_FRZMIN_RECORD1 + 4096) / (u32)(FRZSTDLISTLEN + 74))
};

const sFrzMinLinePara_TypeDef FrzMinLineDefault1 _reserve =
{
    8,
    FRZSTDLISTLEN + 64,
    (((u32)(FRZSTDLISTLEN + 74) * (u32)MAX_FRZMIN_RECORD1 + 4096 + 4096) & 0xFFFFF000), //����1��ַƫ�ƣ�//--Ԥ��1��bank����bank����-----
    (((u32)(FRZSTDLISTLEN + 64) * (u32)MAX_FRZMIN_RECORD2 + 4096 + 4096) & 0xFFFFF000),
    FRZMINLISTCYCLE2,
    (((u32)(FRZSTDLISTLEN + 64) * (u32)MAX_FRZMIN_RECORD2 + 4096) / (u32)(FRZSTDLISTLEN + 64))
};

//------------�¼���¼�����������Ա��ʼ��-----------------
const sRecord_ParaDefault_TypeDef EvtDefaultlist[] _reserve =
{
    { FileItemInfoNum_Evt_PowDn, (u8 *) &EvtCList2Default, sizeof(sCList2_TypeDef)      },
    //  { FileItemInfoNum_Evt_Clr                  , (u8 *)&EvtMeterClrCListDefault    , sizeof(sCList6_TypeDef)     } ,
    { FileItemInfoNum_Evt_Clr, (u8 *) &EvtMeterClrCListDefault, sizeof(sCList24_TypeDef)     },
    { FileItemInfoNum_Evt_SetClock, (u8 *) &EvtCList2Default, sizeof(sCList2_TypeDef)      },
    { FileItemInfoNum_Evt_OpenCover, (u8 *) &EvtOpenCoverCListDefault, sizeof(sCList12_TypeDef)     },
    { FileItemInfoNum_Evt_OpenTail, (u8 *) &EvtOpenCoverCListDefault, sizeof(sCList12_TypeDef)     },
    { FileItemInfoNum_Evt_PrgSetPsw, (u8 *) &EvtCListSetPswDefault, sizeof(sCList1_TypeDef)    },
    { FileItemInfoNum_Evt_BroadcastTime, (u8 *) &EvtCList2Default, sizeof(sCList2_TypeDef)    },
    { FileItemInfoNum_Evt_MngPlug, (u8 *) &EvtMngPlugCListDefault, sizeof(sCList14_TypeDef)    },
    { FileItemInfoNum_Evt_MngUpdate, (u8 *) &EvtMngUpdateCListDefault, sizeof(sCList8_TypeDef)    },
};
//------------�¼���¼�����������Ա��ʼ��-----------------
const sRecord_ParaDefault_TypeDef FrzDefaultlist[] _reserve =
{
    { FileItemInfoNum_Frz_MinFrz, (u8 *) &FrzMinListDefault, sizeof(sFrzMinList_TypeDef) },
};

#if (HarmonicPulseOut_Mode==HarmonicPulseOut_Interrupt)
//---�����ڲ�����汾����Ӳ���汾+�����������+Ӳ�����ͺ����------
const u8 FactorySoftVer[32] _reserve = {"RN8611_RN7306_24101101.0002"};  //--г���������ΪV1.0Ӳ���汾---------
#else

#if(KeLu==TRUE)
const u8 FactorySoftVer[32] _reserve = {"RN8611_RN7306_231129V1.0001"}; //---г���������ΪV2.0Ӳ���汾---------
#else
#if (HARDWARE_TYPE_CONFIG  == HARDWARE_TYPE_DIAN_TAN_BIAO_577)
const u8 FactorySoftVer[32] _reserve = {"RN8611_RN7306_25010901.0002"}; //------------dyf 57.7/100V��̼��汾��Ϣ
#else
const u8 FactorySoftVer[32] _reserve = {"RN8611_RN7306_25070801.0001"}; //------------dyf ����о �� 220��̼��汾��Ϣ
#endif
#endif

#endif

const u8 FristPowOn[4] _reserve = {'9', '7', '0', '1'};
