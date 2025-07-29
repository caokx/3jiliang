
#ifndef _FILE_H
#define _FILE_H

#ifdef   _FILE_GLOBALS
#define  FILE_EXT
#else
#define  FILE_EXT  extern
#endif

#pragma pack(1)

// ---��ǰ�����ļ�
typedef struct
{
    //-------------
    sFsEgSh_HighTypeDef PtPEgSh[1];      //�����й�����
    u16             PtPEgShCrc;
    sFsEgSh_HighTypeDef NtPEgSh[1];      //�����й�����
    u16             NtPEgShCrc;

    sFsEgSh_HighTypeDef Qd1QEgSh[1];        //һ�����޹�����ʾֵ
    u16             Qd1QEgShCrc;
    sFsEgSh_HighTypeDef Qd2QEgSh[1];        //�������޹�����ʾֵ
    u16             Qd2QEgShCrc;
    sFsEgSh_HighTypeDef Qd3QEgSh[1];        //�������޹�����ʾֵ
    u16             Qd3QEgShCrc;
    sFsEgSh_HighTypeDef Qd4QEgSh[1];        //�������޹�����ʾֵ
    u16             Qd4QEgShCrc;

    //-------------
    sFsEgSh_HighTypeDef PtPEgSha;                       //A�������й�����ʾֵ
    u16             PtPEgShaCrc;
    sFsEgSh_HighTypeDef NtPEgSha;                       //A�෴���й�����ʾֵ
    u16             NtPEgShaCrc;

    sFsEgSh_HighTypeDef Qd1QEgSha;                      //A��һ�����޹�����ʾֵ
    u16             Qd1QEgShaCrc;
    sFsEgSh_HighTypeDef Qd2QEgSha;                      //A��һ�����޹�����ʾֵ
    u16             Qd2QEgShaCrc;
    sFsEgSh_HighTypeDef Qd3QEgSha;                      //A��һ�����޹�����ʾֵ
    u16             Qd3QEgShaCrc;
    sFsEgSh_HighTypeDef Qd4QEgSha;                      //A��һ�����޹�����ʾֵ
    u16             Qd4QEgShaCrc;

    //-------------
    sFsEgSh_HighTypeDef PtPEgShb;                       //B�������й�����ʾֵ
    u16             PtPEgShbCrc;
    sFsEgSh_HighTypeDef NtPEgShb;                       //B�෴���й�����ʾֵ
    u16             NtPEgShbCrc;

    sFsEgSh_HighTypeDef Qd1QEgShb;                      //B��һ�����޹�����ʾֵ
    u16             Qd1QEgShbCrc;
    sFsEgSh_HighTypeDef Qd2QEgShb;                      //B��һ�����޹�����ʾֵ
    u16             Qd2QEgShbCrc;
    sFsEgSh_HighTypeDef Qd3QEgShb;                      //B��һ�����޹�����ʾֵ
    u16             Qd3QEgShbCrc;
    sFsEgSh_HighTypeDef Qd4QEgShb;                      //B��һ�����޹�����ʾֵ
    u16             Qd4QEgShbCrc;

    //-------------
    sFsEgSh_HighTypeDef PtPEgShc;                       //C�������й�����ʾֵ
    u16             PtPEgShcCrc;
    sFsEgSh_HighTypeDef NtPEgShc;                       //C�෴���й�����ʾֵ
    u16             NtPEgShcCrc;

    sFsEgSh_HighTypeDef Qd1QEgShc;                      //C��һ�����޹�����ʾֵ
    u16             Qd1QEgShcCrc;
    sFsEgSh_HighTypeDef Qd2QEgShc;                      //C��һ�����޹�����ʾֵ
    u16             Qd2QEgShcCrc;
    sFsEgSh_HighTypeDef Qd3QEgShc;                      //C��һ�����޹�����ʾֵ
    u16             Qd3QEgShcCrc;
    sFsEgSh_HighTypeDef Qd4QEgShc;                      //C��һ�����޹�����ʾֵ
    u16             Qd4QEgShcCrc;

    sFsEgSh_HighTypeDef PtFEgSh[1];         //����������ܵ���
    u16             PtFEgShCrc;

    sFsEgSh_HighTypeDef NtFEgSh[1];         // ��������ܵ���
    u16             NtFEgShCrc;

    sFsEgSh_HighTypeDef PtHEgSh[1];         //����г���ܵ���
    u16             PtHEgShCrc;

    sFsEgSh_HighTypeDef NtHEgSh[1];         // ����г���ܵ���
    u16             NtHEgShCrc;

    //-------------
} sEgShFile_TypeDef;

// �õ����ļ�
typedef struct
{
    sFsEgSh_TypeDef CurYearEgSh;                    //��ǰ������õ���
    u16             CurYearEgShCrc;
    sFsEgSh_TypeDef CurMonthEgSh;                   //��ǰ�¶��õ���
    u16             CurMonthEgShCrc;
    sFsEgSh_TypeDef CurDayEgSh;                     //��ǰ�������õ���
    u16             CurDayEgShCrc;
} sDl645CurApplyEgShFile_TypeDef;

typedef struct
{
    sDF29           RmTime;                         // ��1��������ս���ʱ��
    sFsEgSh_TypeDef RmApplyEg;                      // ��1�������������й����ۼ��õ���
} sDl645YearApplyEgShFile_TypeDef;

typedef struct
{
    sFsEgSh_TypeDef                 RmMonthEgSh;     // ��1�¶��й����ۼ��õ���
    sFsEgSh_TypeDef                 RmDayEgSh;       // ��1�����й����ۼ��õ���
    sDl645YearApplyEgShFile_TypeDef RmYearEgSh[4];   // ��4�����������
} sDl645RmApplyEgShFile_TypeDef;

//---�������ļ�-------
typedef struct
{
    u8  nBuy;
    u32 Remain;
} sDl645MoneyFile_TypeDef;

typedef struct
{
    sFsEgSh_TypeDef PtPEgSh;                        //�����й�����ʾֵ
    sFsEgSh_TypeDef NtPEgSh;                        //�����й�����ʾֵ
    sFsEgSh_TypeDef PtQEgSh;                        //�����޹�����ʾֵ
    sFsEgSh_TypeDef NtQEgSh;                        //�����޹�����ʾֵ
} sDl645CurvePQEgFile_TypeDef;

typedef struct
{
    sFsEgSh_TypeDef Qd1QEgSh;                       //һ�����޹�����ʾֵ
    sFsEgSh_TypeDef Qd2QEgSh;                       //�������޹�����ʾֵ
    sFsEgSh_TypeDef Qd3QEgSh;                       //�������޹�����ʾֵ
    sFsEgSh_TypeDef Qd4QEgSh;                       //�������޹�����ʾֵ
} sDl645CurveQdEgFile_TypeDef;

typedef struct
{
    sDF09   PNeed;
    sDF09   QNeed;
} sDl645CurveNeedFile_TypeDef;

//---�¼���¼-------
typedef struct
{
    u32   OAD;
    u8    len;      //���ݴ洢����
    u16 OffPos;     //��ÿ����¼�е�ƫ�Ƶ�ַ
} sContextList_TypeDef;   //�����������Ա�

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[24];
} sCList24_TypeDef;

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[14];
} sCList14_TypeDef;
typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[13];
} sCList13_TypeDef;

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[12];
} sCList12_TypeDef;

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[11];
} sCList11_TypeDef;   //�����������Ա�
typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[9];
} sCList9_TypeDef;
typedef struct
{
    u8       num;           //�����������Ա�OAD����
    u16    reclen;      //�����������Ա��Ӧ�¼���¼�洢����
    sContextList_TypeDef     Clist[8];
} sCList8_TypeDef;   //�����������Ա�

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[7];
} sCList7_TypeDef;

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[6];
} sCList6_TypeDef;   //�����������Ա�

typedef struct
{
    u8       num;           //�����������Ա�OAD����
    u16    reclen;      //�����������Ա��Ӧ�¼���¼�洢����
    sContextList_TypeDef     Clist[5];
} sCList5_TypeDef;   //�����������Ա�

typedef struct
{
    u8       num;           //�����������Ա�OAD����
    u16    reclen;      //�����������Ա��Ӧ�¼���¼�洢����
    sContextList_TypeDef     Clist[4];
} sCList4_TypeDef;   //�����������Ա�

typedef struct
{
    u8       num;
    u16    reclen;
    sContextList_TypeDef     Clist[3];
} sCList3_TypeDef;   //�����������Ա�

typedef struct
{
    u8       num;           //�����������Ա�OAD����
    u16    reclen;      //�����������Ա��Ӧ�¼���¼�洢����
    sContextList_TypeDef     Clist[2];
} sCList2_TypeDef;   //�����������Ա�

typedef struct
{
    u8       num;           //�����������Ա�OAD����
    u16    reclen;      //�����������Ա��Ӧ�¼���¼�洢����
    sContextList_TypeDef     Clist[1];
} sCList1_TypeDef;   //�����������Ա�

typedef struct
{
    u8       num;
    u16    reclen;
} sCListNULL_TypeDef;   //�����������Ա�

typedef struct
{
    u32                 EventSumCnt;   //�¼��������� �ۼƴ���
    sDate_time_s_TypeDef    EventStartTime;   //�¼�����ʱ��
    sDate_time_s_TypeDef    EventEndTime;   //ʱ�����ʱ��
    u16                 EventCnt;   //��ǰ��¼�������ֵ��������¼��
    u32             EventTime;      //ʱ�䷢���ۼ�ʱ��
    u8      EventRptStatus; //�¼��ϱ�״̬
    //  u8      EventReportMode;    //�¼��ϱ�ģʽ
    u8      nTarf;              // ������---����ģ������
} sEvtRcdHead_TypeDef;

typedef struct
{
    //---ʧѹ�ж�---//
    u16 LossVolUTouchUp;    //��ѹ�������� NNN.N(78%Un)
    u16 LossVolUResumeDn;   //��ѹ�ָ����� NNN.N(85%Un)
    s32 LossVolITouchDn;    //������������ NN.NNNN(0.5%Ib)
    u8      tLossVol;           //����ʱ�� s (60S)
} sEvtCfgPara_LossVol_TypeDef;

typedef struct
{
    //---Ƿѹ�ж�---//
    u16 LackVolUTouchUp;    //��ѹ�������� NNN.N
    u8      tLackVol;           //����ʱ�� s (60S)
} sEvtCfgPara_LackVol_TypeDef;

typedef struct
{
    //---��ѹ�ж�---//
    u16 OverUpVolUTouchDn;  //��ѹ�������� NNN.N
    u8      tOverUpVol;         //����ʱ�� s (60S)
} sEvtCfgPara_OverVol_TypeDef;

typedef struct
{
    //---�����ж�---//
    u16     LossPhaUTouchUp;    //��ѹ�������� NNN.N
    s32     LossPhaITouchUp;    //������������ NN.NNNN(��������)
    u8      tLossPha;           //����ʱ�� s (60S)
} sEvtCfgPara_LossPha_TypeDef;

typedef struct
{
    //---ʧ���ж�---//
    u16 LossCurUTouchDn;    //��ѹ�������� +-NNN.N (60%Un)
    s32 LossCurITouchUp;    //������������ +-NN.NNNN(0.5%Ib)
    s32 LossCurITouchDn;    //������������ +-NN.NNNN(5%Ib)
    u8      tLossCur;           //����ʱ�� s (60S)
} sEvtCfgPara_LossCur_TypeDef;

typedef struct
{
    //---�����ж�---//
    s32 OverUpCurITouchUp;  //�������� ���� NN.NNNN(%Ib) sDF23�޸�sDF07
    u8      tOverUpCur;         //����ʱ�� s (60S)
} sEvtCfgPara_OverCur_TypeDef;

typedef struct
{
    //---�����ж�---//
    u16 BreakCurUTouchDn;   //��ѹ�������� +-NNN.N(60%Un)
    s32 BreakCurITouchUp;   //������������ +-NN.NNNN(��������)
    u8      tBreakCur;          //����ʱ�� s (60S)
} sEvtCfgPara_BreakCur_TypeDef;

typedef struct
{
    //---���ʷ���--//
    s32 InSwimPwTouchDn;    //���ʴ������� NN.NNNN
    u8      tInSwim;            //����ʱ�� s (60S)
} sEvtCfgPara_InSwimPw_TypeDef;

typedef struct
{
    //---�����ж�---//
    s32 OverPwTouchDn;      //���ʴ������� NN.NNNN
    u8      tOverPw;            //����ʱ�� s (60S)
} sEvtCfgPara_OverPw_TypeDef;

typedef struct
{
    u32 OverNeedTouchDn;    //���������� NN.NNNN
    u8      tOverNeed;          //����ʱ�� s (60S)
} sEvtCfgPara_OverNeed_TypeDef;

typedef struct
{
    //---���ߵ����쳣---//
    s32 NLineErrCurITouchDn;    //������������  double-long����λ��A�����㣺-4��
    u16 NLineErrTouch;          //���ߵ�����ƽ����ֵ  long- unsigned����λ��%�����㣺-2��
    u8      tNLineErr;         //��ʱ�ж�ʱ��        unsigned����λ��s�����㣺0��
} sEvtCfgPara_NLineErr_TypeDef;
/*
typedef struct {
    //---���ܹ��������ж�---//
    s16 OverPfTouchDn;      //�й������������� N.NNN
    u8      tOverPf;            //����ʱ�� s (60S)
} sEvtCfgPara_OverPf_TypeDef;
*/
//----���ܹ�������,��ƽ���¼� ���ò�����ʽһ��-----------
typedef struct
{
    s16 INT16Touch;     //�������� xx.xx%
    u8  tDly;           //����ʱ�� s (60S)
} sEvtCfgPara_INT16Touch_TypeDef;

typedef struct
{
    u8      tDly;           //������ʱʱ�� s (60S)
} sEvtCfgPara_TimeDly_TypeDef;

typedef struct
{
    //-------class24----

    sEvtCfgPara_OverCur_TypeDef VrCur;
    sEvtCfgPara_TimeDly_TypeDef PowDn;

    sEvtCfgPara_TimeDly_TypeDef CkErr;
    sEvtCfgPara_TimeDly_TypeDef MrErr;
    sEvtCfgPara_TimeDly_TypeDef CPLC;
    sEvtCfgPara_NLineErr_TypeDef    NLineErr;  //���ߵ����쳣

    u16 Crc;
} sTrim_TypeDef;

//---��ѹ�ϸ���ͳ���ļ�-------
typedef struct              //
{
    u32 tInspectU;      //��ѹ���ʱ��
    u16 EligRateU;      //��ѹ�ϸ���
    u16 OverRateU;      //��ѹ������
    u32 tOverUpU;       //��ѹ������ʱ��
    u32 tOverDnU;       //��ѹ������ʱ��
} sUEligStat_TypeDef;       //MONTHSTAT_TYPE;

typedef struct              //
{
    sDF27   tBatWork;       //��ع���ʱ��
    sDF27   tWork;          //�ն˹���ʱ��
} sMiscStat_TypeDef;

typedef struct
{
    sUEligStat_TypeDef  UElig_Day[3];  //A��B��C
    sUEligStat_TypeDef  UElig_Month[3];
    sMiscStat_TypeDef       MiscStat;
} sStatFile_TypeDef;

typedef struct
{
    u16 UUp;                    //��ѹ����
    u16 UDn;                    //��ѹ����
    u16     UCheckUp;               //��ѹ�������� NNN.N
    u16     UCheckDn;               //��ѹ�������� NNN.N

    u16     Crc;
} sVolYieldPara_TypeDef;

typedef struct
{
    u16 RTCDota0;       /*"2�����߳�ʼƵ��ƫ��"*/
    u16 CurveMode;
    u16    DATA0;       /*"4�λ���3�����߳�ʼƵ��ƫ��"*/
    u16    XT1;     /*"�����¶����߶����¶�"*/
    u16    ALPHA;       /*"����һ���¶�ϵ��"*/
    u16    BETA;        /*"��������¶�ϵ��"*/
    u16    GAMMA;       /*"���������¶�ϵ��"*/
    u16    ZETA;        /*"�����Ĵ��¶�ϵ��"*/

    u16     Crc;
} sRTCParaE2_TypeDef;

typedef struct
{
    sDF15           Time;                //��������
    sDF08           nALLBuyEg;           //������ܹ������
    sFsEgSh_TypeDef BuyEg;               //������
    sFsEgSh_TypeDef FrSurplusEg;         //����ǰʣ�����
    sFsEgSh_TypeDef AfSurplusEg;         //�����ʣ�����
    sFsEgSh_TypeDef AllBuyEg;            //������ۼƹ�����
} sBuyEg_TypeDef;           //�����¼���¼����������

typedef struct
{
    sDF15           Time;                   //��������
    sDF08           nALLBuyMoney;           //������ܹ������
    u32             BuyMoney;               //������
    u32             FrSurplusMoney;         //����ǰʣ����
    u32             AfSurplusMoney;         //�����ʣ����
    u32             AllBuyMoney;            //������ۼƹ����
} sBuyMoney_TypeDef;        //�����¼���¼������

//-------����------------
//-----------------------
typedef struct
{
    u16 Cycle;      //����
    u32   OAD;
    u32 Depth;      //���
    u8    len;      //���ݴ洢����
    u16 OffPos;     //��ÿ����¼�е�ƫ�Ƶ�ַ
} sFrzCtxList_TypeDef;   //�����������Ա�

typedef struct
{
    u8  num;            //�����������Ա�OAD����
    u16   reclen;       //�����������Ա��Ӧ�¼���¼�洢����
    sFrzCtxList_TypeDef Clist[3];
} sFrzWinkList_TypeDef;   //�����������Ա�

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[15];
} sFrzMinList_TypeDef;   //

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[2];
} sFrzHourList_TypeDef;   //

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[3];
} sFrzDayList_TypeDef;   //�����������Ա�

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[4];
} sFrzRmDayList_TypeDef;   //

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[3];
} sFrzMonthList_TypeDef;   //

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[1];
} sFrzLadderList_TypeDef;   //

typedef struct
{
    u8  num;
    u16   reclen;
    sFrzCtxList_TypeDef Clist[3];
} sFrzSwList_TypeDef;   //�л�����

typedef struct
{
    u8  num;            //
    u16   reclen;       //�����������Ա��Ӧ�¼���¼�洢����
    sFrzCtxList_TypeDef Clist[2];
} sFrzStdList_TypeDef;   //��׼��¼��Ԫ

typedef struct
{
    u32                 FrzAddrEnd;   //����Ľ�����ַ(1~�������)
    sDate_time_s_TypeDef    FrzTime;   //����ʱ��
    u32                 FrzAddrStart;   //�������ʼ��ַ(0~(�������-1))
} sFrzRcdHead_TypeDef;

typedef struct
{
    u8  OADnum;         //
    u16 RecLen;     //�����¼���¼����
    u32 LineOffAdder;       //�����¼���¼��ַ
    u32 LineRecLen;         //һ�������¼���¼�ܳ���
    u16 Cycle;      //����
    u32 Depth;      //���
} sFrzMinLinePara_TypeDef;

typedef struct
{
    sFrzMinLinePara_TypeDef  LinePara;
    sFrzRcdHead_TypeDef      RecHead;
} sFrzMinHead_TypeDef;

//---�м�����ļ�-------
typedef struct
{
    struct sCellEg_TypeDef
    {
        u16 PulseE[12]; //{PNeed,QNeed,PsNeed},{PNeeda,QNeeda,PsNeeda},{PNeedb,QNeedb,PsNeedb},{PNeedc,QNeedc,PsNeedc}
    } CellEg[60];
} sNeedInter_TypeDef;

typedef struct
{
    u32 lStatus[2]; //nStatus:   ʵʱ״̬
    //0:����
    //1:����
    //2:����оƬ�쳣
    //3:���ߵ����쳣
    u32 Status[2];  //ͬ  lStatus   �ж���ʱʱ�������״̬

    u8  tOverCura;
    u8   tPowDn;
    u8  tMeasureErr;
    u8  tNLineErr;
    //---------------------
} sEvStatusInter_TypeDef;   //STATUSINTER_TYPE;

typedef struct
{
    u32 tTotal;          //(hyg) BCD�� ����������ۼ�
    u32 tVolPass;        //(hyg) BCD�� ��ѹ�ϸ�����ۼ�

    u32 Cos;            //(hyg) BCD�� �ܹ��������ۼ�
    u32 ACos;           //(hyg) BCD�� A�๦�������ۼ�
    u32 BCos;           //(hyg) BCD�� B�๦�������ۼ�
    u32 CCos;           //(hyg) BCD�� C�๦�������ۼ�
} sStatInter_TypeDef;   //��ʱ����

typedef struct
{
    u8      nPswRetry[2];       //�������Դ���
    u16     tPswFailClose[2];   //�������ʱ��
    u16     tPrgKeyValid;
    u16     tPrgKeyLock;
    u8      nMacErr;        //Զ��MACЧ��ʧ��

    u8      SecretIndex[3]; //���������
    u8      Labour[17];     //ʵ����ģ��������

    u32     tLinkDly[4];    //Ӧ�����ӳ�ʱʣ��ʱ�� ��λ:��
} sSecretInter_TypeDef;//SECRETINTER_TYPE;

typedef struct
{
    u8   MeterShellStamp;   //����ǣ��ϸǣ��ɿ�תΪ��ʱ���ñ�����Ϊ��ʱ�ۼ�
    u8   JunctionBoxStamp;  //�����ߺУ�β�ǣ��ɿ�תΪ��ʱ���ñ�����Ϊ��ʱ�ۼ�
    u8   ProgramBoxStamp;   //����̺У���̺иǣ��ɿ�תΪ��ʱ���ñ�����Ϊ��ʱ�ۼ�
    u8   Reserval;
} sOpenCoverInter_TypeDef;      //COVEROPENINTER_TYPE;

typedef struct                  //���ڵ�������β��
{
    u16 PieceEg[28];
    u16 Crc;
} sEgPiece_TypeDef;             //sEgPiece_TypeDef;

typedef struct
{
    sDF01   PowOn;              //����ʱ��
    sDF01   PowDn;              //ͣ��ʱ�䣨ÿ���¼һ���Ա������жϣ�

    u8      fTZoneSw;           //ʱ�����л���־,D7 = 0δ�л� =1���л���D0=0��ǰʹ�õ�һ�ײ��� =1��ǰʹ�õڶ��ײ���
    u8      fPOTSw;             //ʱ�α��л���־,D7 = 0δ�л� =1���л���D0=0��ǰʹ�õ�һ�ײ��� =1��ǰʹ�õڶ��ײ���
    u8      fRatePriceSw;       //���ʵ�۱��л���־,D7 = 0δ�л� =1���л���D0=0��ǰʹ�õ�һ�ײ��� =1��ǰʹ�õڶ��ײ���
    u8      fLadderSw;          //���ݵ�۱��л���־,D7 = 0δ�л� =1���л���D0=0��ǰʹ�õ�һ�ײ��� =1��ǰʹ�õڶ��ײ���

    u8      CurveStarYear;      //�������߿�ʼʱ�䱣����
    u8      flagCurve;          //���߼�¼�ѿ�ʼ��־ 18
    u16     nCurve;             //���ɼ�¼��������
} sMisc_TypeDef;                //

typedef struct                  //
{
    sFsEgSh_TypeDef CurSurplusEg;             //��ǰʣ�����4���ֽ�
    sFsEgSh_TypeDef CurOverdraftEg;           //��ǰ͸֧����4���ֽ�

    sDF12           CurSurplusMoney;          //��ǰʣ����6�ֽڣ�����2���ֽڣ�
    sDF12           CurOverdraftMoney;        //��ǰ͸֧���6�ֽڣ�����2���ֽڣ�

    sFsEgSh_TypeDef CurApplyEg;               //��ǰ������������й����ۼ��õ���
    sFsEgSh_TypeDef Rmday1ApplyEg;            //��һ������������й����ۼ��õ���
    u16             CurSurplusEgCrc;          //��ǰʣ�༰͸֧������CRCЧ��
    u16             CurSurplusMoneyCrc;       //��ǰʣ�༰͸֧����CRCЧ��
    u16             CurApplyEgCrc;            //��ǰ����1��������ۼ��õ�����CRCЧ��
    u32             nAllBuyMoney;             // �ܹ������
    u32             AllBuyMoney;              // �ܹ�����
} sCurEgMoney_TypeDef;                            //���ڷѿأ�������������

typedef struct
{
    sCommSize_TypeDef   Comm[4];  //4��ͨ��:485B,IR , PLC, 485B
} sLinkSize_TypeDef;    //����Ӧ������Э�̳ߴ�

typedef struct
{
    sNeedInter_TypeDef      Need;
    sEvStatusInter_TypeDef  EvStatus;
    sStatInter_TypeDef      Stat;
    sSecretInter_TypeDef    Secret;
    sOpenCoverInter_TypeDef OpenCover;
    sMisc_TypeDef           Misc;
    sCurEgMoney_TypeDef        CurEgMoney;          //�Ʒ����м����
    sLinkSize_TypeDef       MLinkSize;      //��վ
    sLinkSize_TypeDef       TLinkSize;      //�ն�
    u16   Crc;
} sDl645InterTmpFile_TypeDef;

//---���ʲ����ļ�-------
typedef struct
{
    sDate_time_s_TypeDef                    TimeZoneSw;             //����ʱ�����л�ʱ��
    sTimeZoneTable_TypeDef  TimeZoneTable[2][14];   //ʱ����
    u16   Crc;
} sTimeZonePara_TypeDef;

typedef struct
{
    sDate_time_s_TypeDef                    POTTableSw;             //������ʱ�α��л�ʱ��
    sPOTTable_TypeDef       POTTable[2][8][14];     //��ʱ�α�
    u16   Crc;
} sPOTTablePara_TypeDef;

typedef struct
{
    sDate_time_s_TypeDef    EgPriceSw;       //���׷��ʵ���л�ʱ��
    sDF13   RatePrice[2][MAX_FL + 1];//���׷��ʵ�۱�
    u16   Crc;
} sRatePricePara_TypeDef;

typedef struct
{
    sDate_time_s_TypeDef    EgPriceSw;        //���׽��ݵ���л�ʱ��

    sDF13   LadderVal[2][MAX_LADDER];//���׽���ֵ
    sDF13   LadderPrice[2][MAX_LADDER];//���׽��ݵ��ֵ
    sDF28   RmYear[2][4];                     // 2�׽����������
    u16   Crc;
} sLadderPara_TypeDef;

typedef struct
{
    sDF11   WarnMoney1;      //�������1��ֵ
    sDF11   WarnMoney2;      //�������2��ֵ
    sDF11   OverdraftMoney;  //͸֧�����ֵ
    sDF11   RegrateMoney;    //�ڻ������ֵ
    sDF11   GateOnAllowMoney;     //��բ��������ֵ
    u16    Crc;
} sChargMoneyPara_TypeDef;

//---ͨ�ò����ļ�-------
typedef struct
{
    u8      NeedMode;   //����ģʽ
    u8      NeedCyc;    //��������
    u8      NeedSlip;   //��������

    sDF08   PlsWidth;   //У��������
    u8      nWave;      //г����������
    u16     BroadcastTime_ParaMin;
    u16     BroadcastTime_ParaMax;
    u8          WirelessSignal;     //�����ź�ǿ��ָʾ      40
    u16     Crc;
} sDocment_TypeDef;

typedef struct
{
    u8      ComAddr[6];
    u8      Ir1Style;   //�����ͺ���ڲ����������� IR
    u8      Ir2Style;   //�Ӵ��ͺ���ڲ�����������
    u8      Com1Style;  //ͨ�ſ�1������������  4851
    u8      Com2Style;  //ͨ�ſ�2������������  4852
    u8      Com3Style;  //ͨ�ſ�3������������  ZB
    u16     Crc;
} sComPara_TypeDef;

typedef struct
{
    u8      AllOnDispTime;  // �ϵ�ȫ��ʱ��5-30S����Ĭ��5S
    u16     Key_LightTime;  //�������ʱ�� 1
    u16     Chk_LightTime;  //��ʾ�鿴�������ʱ��  3
    u16     Key_PwrOffTime; //�޵簴����Ļפ�����ʱ��   5
    u8      DecimalEg;  //��ʾ����С��λ�� 7
    u8      DecimalPw;  //��ʾ����С��λ�� 8
    u8      LCD_WordMn;  //Һ����������٢� 9
    u8      nCycDisp;   //ѭ������  10
    u8      nKeyDisp;   //��������  11
    u16     AutoDispTime;   //��ʾʱ�� �Զ�ѭ����ʾ    12
    u16     KeyDispTime;    //��ʾʱ�� ������ʾ    13
} sDispPubPara_TypeDef;

typedef struct
{
    sDispPubPara_TypeDef    PubPara;

    sDispItem_TypeDef       CycDispItem[MAX_CYCDISP];
    sDispItem_TypeDef       KeyDispItem[MAX_KEYDISP];
    u16 Crc;
} sDispPara_TypeDef;

typedef struct
{
    u8  nCipherKey;             // ��Կ������
    u8  WriteStarFlag;          // ��Կд������־ÿλ��Ӧ1����Կ��λ��1֤����Կ��д��EEPROM��
    u32 CipherKeyWriteFlag;     // ��Կд��־
    u32 CipherKeyFlag;          // ��Կ״̬��
    u8  CipherKey[MAX_CipherKey][32];   // ��Կ��Ϣ�洢
    u32 nCipherKeyEE;           // EEPROM�д洢����Կ����
    u32 OpCode;                 // ��Կ�����ߴ���
} sCipherKeyPara_TypeDef;

typedef struct
{
    sDF26   Ga;     //A��絼ϵ��
    sDF26   Ba;     //A�����ϵ��
    sDF26   Ra;     //A�����ϵ��
    sDF26   Xa;     //A��翹ϵ��

    sDF26   Gb;     //B��絼ϵ��
    sDF26   Bb;     //B�����ϵ��
    sDF26   Rb;     //B�����ϵ��
    sDF26   Xb;     //B��翹ϵ��

    sDF26   Gc;     //C��絼ϵ��
    sDF26   Bc;     //C�����ϵ��
    sDF26   Rc;     //C�����ϵ��
    sDF26   Xc;     //C��翹ϵ��
} sWastePara_TypeDef;

typedef struct
{
    u16 Style1;
    u16 Trigger1;

    u16 Style2;
    u16 Trigger2;

    u16 Style3;
    u16 Trigger3;

    u16 Style4;
    u16 Trigger4;

    u16 Style5;
    u16 Trigger5;

    u16 Style6;
    u16 Trigger6;

    u16  RelaysOutAlarm[5];
    u16  LightAlarm[5];
    u16  SoundAlarm[5];
} sOutputPara_TypeDef;

typedef enum
{
    //����
    //---class7---
    FileItemInfoNum_Evt_PowDn             = 0,      //����
    FileItemInfoNum_Evt_Clr                   = 1,      //�������
    FileItemInfoNum_Evt_SetClock          = 2,      //Уʱ
    FileItemInfoNum_Evt_OpenCover     = 3,      //�����
    FileItemInfoNum_Evt_OpenTail      = 4,      //���˸�
    FileItemInfoNum_Evt_PrgSetPsw       =   5,    //��Կ����
    FileItemInfoNum_Evt_BroadcastTime   =   6,    //�㲥Уʱ
    FileItemInfoNum_Evt_MngPlug       = 7,      //����ģ����
    FileItemInfoNum_Evt_MngUpdate     = 8,      //����ģ������

    FileItemInfoNum_Evt_Max         =   9,

    //----�����¼���¼��������֧��,Ϊ������ݶ�����---------
    //  FileItemInfoNum_Evt_LossVol         =   ( ITEM_EVT_MAX + 1 ) ,     //ʧѹ
    //  FileItemInfoNum_Evt_LackVol         =   ( ITEM_EVT_MAX + 2 ) ,     //Ƿѹ
    //  FileItemInfoNum_Evt_OverVol         =   ( ITEM_EVT_MAX + 3 ) ,     //��ѹ
    //  FileItemInfoNum_Evt_LossPha         =   ( ITEM_EVT_MAX + 4 ) ,     //����
    //  FileItemInfoNum_Evt_LossCur         =   ( ITEM_EVT_MAX + 5 ) ,     //ʧ��
    //  FileItemInfoNum_Evt_BreakCur        =   ( ITEM_EVT_MAX + 6 ) ,     //����
    //  FileItemInfoNum_Evt_InSwimPw        =   ( ITEM_EVT_MAX + 7 ) ,     //���ʷ���
    //  FileItemInfoNum_Evt_OverPw          =   ( ITEM_EVT_MAX + 8 ) ,      //����
    //  FileItemInfoNum_Evt_QtOverNeed  =   ( ITEM_EVT_MAX + 9 ) ,     //�޹���������
    //  FileItemInfoNum_Evt_OverPf          =   ( ITEM_EVT_MAX + 10 ) ,   //������������
    //  FileItemInfoNum_Evt_PtOverNeed  =   ( ITEM_EVT_MAX + 11 ) ,   //�����й�����
    //  FileItemInfoNum_Evt_NtOverNeed  =   ( ITEM_EVT_MAX + 12 ) ,   //�����й�����
    //  FileItemInfoNum_Evt_QLossVol        =   ( ITEM_EVT_MAX + 13 ) ,   //ȫʧѹ
    //  FileItemInfoNum_Evt_LossAux         =   ( ITEM_EVT_MAX + 14 ) ,   //������Դ
    //  FileItemInfoNum_Evt_InPhaVol        =   ( ITEM_EVT_MAX + 15 ) ,   //��ѹ������
    //  FileItemInfoNum_Evt_InPhaCur        =   ( ITEM_EVT_MAX + 16 ) ,   //����������
    //  FileItemInfoNum_Evt_NeedClr         =   ( ITEM_EVT_MAX + 17 ) ,   //��������
    //  FileItemInfoNum_Evt_OpenTail        =   ( ITEM_EVT_MAX + 18 ) ,   //��β��
    //  FileItemInfoNum_Evt_UnblVol         =   ( ITEM_EVT_MAX + 19 ) ,   //��ѹ��ƽ��
    //  FileItemInfoNum_Evt_UnblCur         =   ( ITEM_EVT_MAX + 20 ) ,   //������ƽ��
    //  FileItemInfoNum_Evt_PrgQ                =   ( ITEM_EVT_MAX + 21 ) ,   //�޹���������ֱ��
    //  FileItemInfoNum_Evt_MagnetDisturb=( ITEM_EVT_MAX + 22 ) , //�ų�����
    //  FileItemInfoNum_Evt_OverUnblCur     =   ( ITEM_EVT_MAX + 23 )   , //�������ز�ƽ��
} eFileItemInfoNum_Evt_TypeDef;   //�¼���¼ö�٣������������Ա����ò������¼���¼����˳����һ��

#define ITEM_EVT_MAX    FileItemInfoNum_Evt_Max

typedef struct
{
    u8  OADNum;  //
    u32 OAD[ITEM_EVT_MAX];      //�����ϱ�OAD
} sReportList_TypeDef;

typedef struct
{
    u8  AtiveAllow; //�����ϱ��ܿ��أ�1=����,0=�ر�
    u8  FollowAllow;        //�����ϱ��ܿ���,1=����,0=�ر�
    u8  RptFlagHappen[7];       //�ϱ���ʶ�����ϱ�,bitʹ��,����˳�����¼���¼eFileItemInfoNum_Evt_TypeDef˳��
    u8  RptFlagEnd[7];      //�ϱ���ʶ�����ϱ�,bitʹ��,����˳�����¼���¼eFileItemInfoNum_Evt_TypeDef˳��
    u8  RptMode[7];         //�ϱ���ʽ0=�����ϱ�;  1=�����ϱ�,bitʹ��

    u8  RptStatusAllow;     //�ϱ�״̬���ϱ���ʽ 0x20150500,0=�����ϱ���1=�����ϱ�
    u32  RptStatusMode;    //�ϱ�״̬��ģʽ��0x20150400
    u8  RptChannel[3];   //9=�ز�,1=485_1 , 2=485_2

    u16 Crc;
} sEvtRptPara_TypeDef;  //�����ϱ�����

typedef struct
{
    u32  RptStuZB;          // �����ϱ�״̬��
    u32  RptStuZBBack;

    u32  RptStu485;         //
    u32  RptStu485Back;

    u32  RptStu4852;            //
    u32  RptStu4852Back;
} sEvtRptStatus_TypeDef;

typedef struct
{
    sEvtRptPara_TypeDef  RptPara;

    sEvtRptStatus_TypeDef  RptStatus; // �����ϱ�״̬��

    sReportList_TypeDef   RptListZB_A;  //�ز������ϱ��б�,��E2
    sReportList_TypeDef   RptListZB_F;  //�ز������ϱ��б���E2

    sReportList_TypeDef   RptList485_F; //485ֻ֧�ָ����ϱ��������ϱ��б���E2
    sReportList_TypeDef   RptList4852_F; //485ֻ֧�ָ����ϱ��������ϱ��б���E2
    u8    RptPowerUpTime;   //�ϵ�ʱ�䣬С��1Сʱ���ϱ�
    u8    RptPowerDnEvtRcd[150];  //�����¼���¼��E2�ռ��С
} sEvtReport_TypeDef;   // �����ϱ�

//---�߼������ļ�-------
typedef struct
{
    u8      PExpression;        //�й���Ϸ�ʽ������
    u8      PtQExpression;      //�޹����1��ʽ������
    u8      NtQExpression;      //�޹����2��ʽ������
    sDF11       PConstE;            //�й�����
    sDF11       QConstE;            //�޹�����

    sDF12       MeterNo;            //���
    sDF13       MCT;            //�������������
    sDF13       MPT;                //��ѹ���������

    u8      WireMode;            //���߷�ʽ 0�������ߡ�1��������
    u32     StartCur;           //��������
    u16     CriticalVol;        //�ٽ��ѹ

    sDF12       UserNo;         //�ͻ����
    u8      CardSerial[8];      // �û������

    u8      MeterRunFlag;       //�������������

    u32     tIRPrg;         // ������֤ʱЧ
    u32     tTerminalPrg;           // �ն������֤ʱЧ
    u8      tEvRstDely;         // �����ϱ�״̬���Զ���λ��ʱʱ��
    u32     GataSafeCur;        // �̵�����բ���Ƶ�������ֵ
    u16     tSafeGata;          // ����բ���Ƶ������ޱ�����ʱʱ��,��λ:��

    u16         GateOffDelayTime;       //��բ��ʱʱ�䣨NNNNΪ��բǰ�澯ʱ�䣩
    sVolYieldPara_TypeDef   Yield;  //��ѹ�ϸ��ʲ���

    u16 RTCDota0;       /*"2�����߳�ʼƵ��ƫ��"*/
    u16 CurveMode;
    u16    DATA0;       /*"4�λ���3�����߳�ʼƵ��ƫ��"*/
    u16    XT1;     /*"�����¶����߶����¶�"*/
    u16    ALPHA;       /*"����һ���¶�ϵ��"*/
    u16    BETA;        /*"��������¶�ϵ��"*/
    u16    GAMMA;       /*"���������¶�ϵ��"*/
    u16    ZETA;        /*"�����Ĵ��¶�ϵ��"*/

    u8  RTCAdj[4];              // RTC�ߵ���ʱ����ֵ
    u8  RTC_CAL_Data[10];   // RTC���β���ֵ

    u8      FristPowOnBak2[4];
    u16     Crc;
} sHighParaFile_TypeDef;        //

//���������Ϣ����
typedef struct
{
    u8 Type[2];         //��������
    u8 FactoryNo[4];    //���Ҵ���
    u8 SoftType[1];     //���򱸰�����
    u8 Date[8];         //��������
    u8 DayNo;           //���ձ������
    u8 No[16];          //������
} sSoftWareInfo_TypeDef;

//---�����Ϣ------
typedef struct
{
    u8  MeterPlace[12];     //���λ����Ϣ
    char    DeviceNo[32];       //�ʲ������
    char    RatingVol[6];       //���ѹ
    char    MimCur[32];         //��С����
    char    TrCur[32];          //ת�۵���
    char    RatingCur[6];           //������
    char    MaxCur[6];          //������
    char    PGrade[4];          //�й����ȵȼ�
    char    QGrade[4];          //�޹����ȵȼ�
    char    MeterModel[32];     //���ͺ�/ �豸������
    sDate_time_s_TypeDef    ProductDate;        //��������
    char    PtVer[20];          //Э��汾��/֧�ֹ�Լ�б�

    char    SoftVer[32];        //��������汾
    char    FirmVer[32];        //����Ӳ���汾
    char    FactoryNo[32];      //���ұ��
    u8      SoftWare[16];           //��������汾��
    sSoftWareInfo_TypeDef       softWareInfo;

    u8      ServerVer[32];          //698���������̰汾��Ϣ:���̴���(4byte)+����汾��(4byte)+
    //����汾����(6byte)+Ӳ���汾��(4byte)+Ӳ���汾����(6byte)+������չ��Ϣ(8)

    char    FactoryMAC[32];  //�����ڲ�MAC��ַ���ڲ����
    u16 Crc;
} sASCIIParaFile_TypeDef;       //

typedef struct
{
    u8  Already;        //�����ѹ㲥Уʱ��־
    u8  ClockErr;       //�㲥Уʱ�������Уʱƫ��ʱ����ʱ�ӹ����¼���¼
} sBroatStatue_TypeDef;

typedef struct
{
    u8  CoverOpen;
    sDate_time_s_TypeDef    CoverOpenTime;
    u8  CoverClose;
    sDate_time_s_TypeDef    CoverCloseTime;

    u8  TailOpen;
    sDate_time_s_TypeDef    TailOpenTime;
    u8  TailClose;
    sDate_time_s_TypeDef    TailCloseTime;

    u8 EvtPwdn;
    sDate_time_s_TypeDef    EvtPwdnTime;

    u8  EvtVoltLoss;
} sEvtPwnCoverTailTypedef;

typedef struct
{
    u16     OI;         //�����ʶ
    u16     Mode;   //��ȫģʽ����
} sSafeModeTable_TypeDef;

typedef struct
{
    u8      OI_Cnt;         //��ʽ��ȫģʽ�� OI����
    sSafeModeTable_TypeDef      SafeModeTable[MAX_SafePara];   //��ȫģʽ�б�
    u16 Crc;
} sSafeModePara_TypeDef;

//---��������ļ�-------
typedef struct
{
    u8      SecretPara[10][4];          //

    u8      nPswRetry;                  //�������Դ���          //(hyg) BCD��
    u16     tPswFailClose;              //����������ʱ��      //(hyg) BCD��

    u16     tPrgKeyValid;               //��̿�����Чʱ��,��λ�����ӣ���ͬ (hyg) BCD��
    u16     tPrgKeyLock;                //��̿��ر���ʱ�� (���α�̼����µ�ʱ����)

    // ��ȫģʽ����
    u8      SafeModeFlag;
    sSafeModePara_TypeDef   SafeModePara;
    u8      AuthOn;   //�����֤����:0=����/����+RN �������������֤;1=���Ķ�ȡ��Ҫ�����֤
    u8      FuncationItem[32];
    u8      Labour[32];
    u8      FristPowOnBak1[4];
    u16   Crc;
} sSecretParaFile_TypeDef;      //111 Byte

//---�洢�������ļ�-------
typedef struct
{
    u8      FristPowOn[4];

    u8      pRmEgSh;            //0
    u8      pRmNeed;            //1
    u8      pTimeFrz;           //2
    u8      pWinkFrz;           //3
    u8      pDayFrz;            //4
    u8      pTZoneSwFrz;        //5
    u8      pPOTSwFrz;          //6
    u8      pRatePriceSwFrz;    //7
    u8      pLadderSwFrz;       //8
    u8      pHourFrz;           //9
    u8      pStat;              //10
    u16     pSCurve;            //����������ʼָ��11
    u16     pECurve;            //�������߽���ָ��13
    u8      pRmApplyEg;         //15
    u16 Crc;
} sNvRamFile_TypeDef;

//�����ļ���������Ҫ��������ݣ����ļ����������ط��п��ܶ����
typedef struct
{
    sDate_time_s_TypeDef    PowDnTime;                            //����ʱ��
    sEgPiece_TypeDef        EgPiece;
    u8      CheckMoneyFlag;                        //����ʣ��������
    u8      PownDnAllPEgSh[MAX_FL + 1];     //������ϸ�����������
    u8      PownDnPtPEgSh[MAX_FL + 1];      //�������������������
    u8      PownDnNtPEgSh[MAX_FL + 1];      //���練���������������
    u32    tWorkBat;
    sDate_time_s_TypeDef  FrzDayTime;
    sDate_time_s_TypeDef  FrzRmDayTime;
    u8      Irms[12];  //����ȫʧѹʱABC�������
    u16     Crc;
} sPowDnFile_TypeDef;

typedef struct
{
    u8    EnOrDis;     //��ѹӰ������������
    u8    Rep[nPhs][MAX_VOLT_STEP];  //��ѹӰ��������
    u16   Crc;  //
}   sVoltRepairPara_TypeDef;

typedef struct
{
    sVoltRepairPara_TypeDef  Volt; //��ѹӰ��������
    u16 TIRM;
}   sMeasureRepairPara_TypeDef;

typedef struct
{
    u8    BackUp_FL;
    sFsEgSh_HighTypeDef BackUpEnergy[12 + 1];   // Ԥ���ܼ�12���ʿռ�
}   sBackUpEnergy_TypeDef;

typedef struct
{
    sDF12           CurSurplusMoneyBackUp;          //��ǰʣ����6�ֽڣ�����2���ֽڣ�
    sDF12           CurOverdraftMoneyBackUp;        //��ǰ͸֧���6�ֽڣ�����2���ֽڣ�
    sFsEgSh_TypeDef CurApplyEgBackUp;               //��ǰ������������й����ۼ��õ���
    sFsEgSh_TypeDef Rmday1ApplyEgBackUp;            //��һ������������й����ۼ��õ���
    u16             CurSurplusMoneyBackUpCrc;
    u16             CurApplyEgBackUpCrc;
    u8              BackUpOpCode[4];                // ���浱ǰ����բ��ʹ�õĲ����ߴ���

    sDate_time_s_TypeDef   BackUpDatetime;
    sBackUpEnergy_TypeDef BackUpPtPEgSh;      //�����й�����
    sBackUpEnergy_TypeDef BackUpNtPEgSh;      //�����й�����
    sBackUpEnergy_TypeDef BackUpQd1QEgSh;       //һ�����޹�����ʾֵ
    sBackUpEnergy_TypeDef BackUpQd2QEgSh;       //�������޹�����ʾֵ
    sBackUpEnergy_TypeDef BackUpQd3QEgSh;       //�������޹�����ʾֵ
    sBackUpEnergy_TypeDef BackUpQd4QEgSh;       //�������޹�����ʾֵ
    u16 Crc;
} sBackUpCurMoneyFile_TypeDef;

typedef struct
{
    sDate_time_s_TypeDef    Start;                  // ��������ʱ��
    sDate_time_s_TypeDef    End;                    // ��������ʱ��
    u8                      OptType;                // ������������
    u32                     StPosEng;               // ����ǰ�����й��ܵ���
    u32                     StNegEng;               // ����ǰ�����й��ܵ���
    u8                      LoadId[32];             // ���ط���ʶ
    u8                      BfSoftVer[16];          // ����ǰ����汾��
    u8                      AftSoftVer[16];         // ����������汾��
    u8                      AppName[32];            // ����Ӧ������
    u8                      Result;                 // �������
} sEvtMngUpdateTypedef;

typedef struct
{
    u8                      OldEsamSq[8];       // ԭESAM���к�
    u8                      NewEsamSq[8];       // ��ESAM���к�
    sEvtMngUpdateTypedef    EvtMngUpdate;       // ����о������¼����
} sEvtExternRecordTypedef;

typedef struct
{
    sDate_time_s_TypeDef    PwdnTime;           // ͣ�緢��ʱ��
    u16                     VoltVal[3];         // ͣ���ڼ��ѹ���� 0.1V
    u32                     CurVal[3];          // ͣ���ڼ�������� 0.001A
} sPwdnVoltCurTypedef;

#pragma pack()

//=============================================================================
//===�����ļ�����Ϣ========================================
typedef enum
{
    //���                            ���ݳ��� + У��ͳ���(2byte) 8*13+2=106
    FileItemInfoLen_EgSh_PtPEgSh        = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_NtPEgSh        = (sizeof(sFsEgSh_HighTypeDef) + 2),

    FileItemInfoLen_EgSh_Qd1QEgSh       = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd2QEgSh       = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd3QEgSh       = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd4QEgSh       = (sizeof(sFsEgSh_HighTypeDef) + 2),

    FileItemInfoLen_EgSh_PtPEgSha   = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_NtPEgSha   = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd1QEgSha  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd2QEgSha  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd3QEgSha  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd4QEgSha  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_PtPEgShb   = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_NtPEgShb   = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd1QEgShb  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd2QEgShb  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd3QEgShb  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd4QEgShb  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_PtPEgShc   = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_NtPEgShc   = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd1QEgShc  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd2QEgShc  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd3QEgShc  = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_Qd4QEgShc  = (sizeof(sFsEgSh_HighTypeDef) + 2),

    FileItemInfoLen_EgSh_PtFEgSh        = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_NtFEgSh        = (sizeof(sFsEgSh_HighTypeDef) + 2),

    FileItemInfoLen_EgSh_PtHEgSh        = (sizeof(sFsEgSh_HighTypeDef) + 2),
    FileItemInfoLen_EgSh_NtHEgSh        = (sizeof(sFsEgSh_HighTypeDef) + 2),

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_EgSh_PtPEgSh        = (0),
    FileItemInfoOffAddr_EgSh_NtPEgSh        = (FileItemInfoOffAddr_EgSh_PtPEgSh   +   FileItemInfoLen_EgSh_PtPEgSh),

    FileItemInfoOffAddr_EgSh_Qd1QEgSh       = (FileItemInfoOffAddr_EgSh_NtPEgSh   +   FileItemInfoLen_EgSh_NtPEgSh),   //ҳ���룬�������дE2ʱ��ҳ
    FileItemInfoOffAddr_EgSh_Qd2QEgSh       = (FileItemInfoOffAddr_EgSh_Qd1QEgSh  +   FileItemInfoLen_EgSh_Qd1QEgSh),   //ҳ���룬�������дE2ʱ��ҳ
    FileItemInfoOffAddr_EgSh_Qd3QEgSh       = (FileItemInfoOffAddr_EgSh_Qd2QEgSh  +   FileItemInfoLen_EgSh_Qd2QEgSh),   //ҳ���룬�������дE2ʱ��ҳ
    FileItemInfoOffAddr_EgSh_Qd4QEgSh       = (FileItemInfoOffAddr_EgSh_Qd3QEgSh  +   FileItemInfoLen_EgSh_Qd3QEgSh),

    FileItemInfoOffAddr_EgSh_PtPEgSha   = (64),
    FileItemInfoOffAddr_EgSh_NtPEgSha   = (FileItemInfoOffAddr_EgSh_PtPEgSha  +   FileItemInfoLen_EgSh_PtPEgSha),
    FileItemInfoOffAddr_EgSh_Qd1QEgSha  = (FileItemInfoOffAddr_EgSh_NtPEgSha  +   FileItemInfoLen_EgSh_NtPEgSha),
    FileItemInfoOffAddr_EgSh_Qd2QEgSha  = (FileItemInfoOffAddr_EgSh_Qd1QEgSha +   FileItemInfoLen_EgSh_Qd1QEgSha),
    FileItemInfoOffAddr_EgSh_Qd3QEgSha  = (FileItemInfoOffAddr_EgSh_Qd2QEgSha +   FileItemInfoLen_EgSh_Qd2QEgSha),
    FileItemInfoOffAddr_EgSh_Qd4QEgSha  = (FileItemInfoOffAddr_EgSh_Qd3QEgSha +   FileItemInfoLen_EgSh_Qd3QEgSha),

    FileItemInfoOffAddr_EgSh_PtPEgShb   = (128),
    FileItemInfoOffAddr_EgSh_NtPEgShb   = (FileItemInfoOffAddr_EgSh_PtPEgShb  +   FileItemInfoLen_EgSh_PtPEgShb),
    FileItemInfoOffAddr_EgSh_Qd1QEgShb  = (FileItemInfoOffAddr_EgSh_NtPEgShb  +   FileItemInfoLen_EgSh_NtPEgShb),
    FileItemInfoOffAddr_EgSh_Qd2QEgShb  = (FileItemInfoOffAddr_EgSh_Qd1QEgShb +   FileItemInfoLen_EgSh_Qd1QEgShb),
    FileItemInfoOffAddr_EgSh_Qd3QEgShb  = (FileItemInfoOffAddr_EgSh_Qd2QEgShb +   FileItemInfoLen_EgSh_Qd2QEgShb),
    FileItemInfoOffAddr_EgSh_Qd4QEgShb  = (FileItemInfoOffAddr_EgSh_Qd3QEgShb +   FileItemInfoLen_EgSh_Qd3QEgShb),

    FileItemInfoOffAddr_EgSh_PtPEgShc   = (192),
    FileItemInfoOffAddr_EgSh_NtPEgShc   = (FileItemInfoOffAddr_EgSh_PtPEgShc  +   FileItemInfoLen_EgSh_PtPEgShc),
    FileItemInfoOffAddr_EgSh_Qd1QEgShc  = (FileItemInfoOffAddr_EgSh_PtPEgShc  +   FileItemInfoLen_EgSh_NtPEgShc),
    FileItemInfoOffAddr_EgSh_Qd2QEgShc  = (FileItemInfoOffAddr_EgSh_Qd1QEgShc +   FileItemInfoLen_EgSh_Qd1QEgShc),
    FileItemInfoOffAddr_EgSh_Qd3QEgShc  = (FileItemInfoOffAddr_EgSh_Qd2QEgShc +   FileItemInfoLen_EgSh_Qd2QEgShc),
    FileItemInfoOffAddr_EgSh_Qd4QEgShc  = (FileItemInfoOffAddr_EgSh_Qd3QEgShc +   FileItemInfoLen_EgSh_Qd2QEgShc),

    FileItemInfoOffAddr_EgSh_PtFEgSh        = (256),   //ҳ���룬�������дE2ʱ��ҳ
    FileItemInfoOffAddr_EgSh_NtFEgSh        = (FileItemInfoOffAddr_EgSh_PtFEgSh   +   FileItemInfoLen_EgSh_PtFEgSh),   //

    FileItemInfoOffAddr_EgSh_PtHEgSh        = (FileItemInfoOffAddr_EgSh_NtFEgSh   +   FileItemInfoLen_EgSh_NtFEgSh),   //
    FileItemInfoOffAddr_EgSh_NtHEgSh        = (FileItemInfoOffAddr_EgSh_PtHEgSh   +   FileItemInfoLen_EgSh_PtHEgSh),   //

    FileItemInfoOffAddr_EgSh_End            = (FileItemInfoOffAddr_EgSh_NtHEgSh   +   FileItemInfoLen_EgSh_NtHEgSh),

    FileItemInfoLen_EgSh_TotalLen   = FileItemInfoOffAddr_EgSh_End + 128  //Ԥ��128byte �ռ�
} eFileItemInfo_EgSh_TypeDef; //�����ļ�����Ϣ

typedef enum
{
    //���
    FileItemInfoLen_InterTmp_Need   = (sizeof(sNeedInter_TypeDef)),
    FileItemInfoLen_InterTmp_EvStatus   = (sizeof(sEvStatusInter_TypeDef)),
    FileItemInfoLen_InterTmp_Stat   = (sizeof(sStatInter_TypeDef)),
    FileItemInfoLen_InterTmp_Secret     = (sizeof(sSecretInter_TypeDef)),
    FileItemInfoLen_InterTmp_OpenCover  = (sizeof(sOpenCoverInter_TypeDef)),
    FileItemInfoLen_InterTmp_Misc   = (sizeof(sMisc_TypeDef)),
    FileItemInfoLen_InterTmp_EgMoney    = (sizeof(sCurEgMoney_TypeDef)),
    FileItemInfoLen_InterTmp_MLinkSize  = (sizeof(sLinkSize_TypeDef)),
    FileItemInfoLen_InterTmp_TLinkSize  = (sizeof(sLinkSize_TypeDef)),

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_InterTmp_Need   = (0),
    FileItemInfoOffAddr_InterTmp_EvStatus   = (FileItemInfoOffAddr_InterTmp_Need   +   FileItemInfoLen_InterTmp_Need),
    FileItemInfoOffAddr_InterTmp_Stat           = (FileItemInfoOffAddr_InterTmp_EvStatus   +   FileItemInfoLen_InterTmp_EvStatus),
    FileItemInfoOffAddr_InterTmp_Secret         = (FileItemInfoOffAddr_InterTmp_Stat       +   FileItemInfoLen_InterTmp_Stat),
    FileItemInfoOffAddr_InterTmp_OpenCover = (FileItemInfoOffAddr_InterTmp_Secret     +   FileItemInfoLen_InterTmp_Secret),
    FileItemInfoOffAddr_InterTmp_Misc           = (FileItemInfoOffAddr_InterTmp_OpenCover + FileItemInfoLen_InterTmp_OpenCover),
    FileItemInfoOffAddr_InterTmp_EgMoney        = (FileItemInfoOffAddr_InterTmp_Misc   +   FileItemInfoLen_InterTmp_Misc),
    FileItemInfoOffAddr_InterTmp_MLinkSize  = (FileItemInfoOffAddr_InterTmp_EgMoney    +   FileItemInfoLen_InterTmp_EgMoney),
    FileItemInfoOffAddr_InterTmp_TLinkSize  = (FileItemInfoOffAddr_InterTmp_MLinkSize  +   FileItemInfoLen_InterTmp_MLinkSize),

    FileItemInfoOffAddr_InterTmp_End    = (FileItemInfoOffAddr_InterTmp_TLinkSize  +   FileItemInfoLen_InterTmp_TLinkSize)
} eFileItemInfo_InterTmp_TypeDef;//�м�����ļ���Ϣ�ļ�(�����ʱ���������������ʱ�䣬�������������)

typedef enum
{
    //���
    FileItemInfoLen_RatePara_nTimeZone  = (1),
    FileItemInfoLen_RatePara_nPOTTable  = (1),
    FileItemInfoLen_RatePara_nDayPOT    = (1),
    FileItemInfoLen_RatePara_nFl    = (1),
    FileItemInfoLen_RatePara_nHoliday   = (1),
    FileItemInfoLen_RatePara_nLadder    = (1),
    FileItemInfoLen_RatePara_Weekend    = (1),
    FileItemInfoLen_RatePara_WeekendPOT = (1),
    FileItemInfoLen_RatePara_RmDate = (6),
    FileItemInfoLen_RatePara_HolidayTable   = (sizeof(sHolidayTable_TypeDef) * 20),
    FileItemInfoLen_RatePara_TimeZonePara   = (sizeof(sTimeZonePara_TypeDef)),
    FileItemInfoLen_RatePara_POTTablePara   = (sizeof(sPOTTablePara_TypeDef)),
    FileItemInfoLen_RatePara_RatePricePara  = (sizeof(sRatePricePara_TypeDef)),
    FileItemInfoLen_RatePara_LadderPara = (sizeof(sLadderPara_TypeDef)),
    FileItemInfoLen_RatePara_ChargMoneyPara = (sizeof(sChargMoneyPara_TypeDef)),

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_RatePara_nTimeZone  = (0),
    FileItemInfoOffAddr_RatePara_nPOTTable  = (FileItemInfoOffAddr_RatePara_nTimeZone  +   FileItemInfoLen_RatePara_nTimeZone),
    FileItemInfoOffAddr_RatePara_nDayPOT        = (FileItemInfoOffAddr_RatePara_nPOTTable  +   FileItemInfoLen_RatePara_nPOTTable),
    FileItemInfoOffAddr_RatePara_nFl                = (FileItemInfoOffAddr_RatePara_nDayPOT        +   FileItemInfoLen_RatePara_nDayPOT),
    FileItemInfoOffAddr_RatePara_nHoliday   = (FileItemInfoOffAddr_RatePara_nFl                +   FileItemInfoLen_RatePara_nFl),
    FileItemInfoOffAddr_RatePara_nLadder        = (FileItemInfoOffAddr_RatePara_nHoliday       +   FileItemInfoLen_RatePara_nHoliday),
    FileItemInfoOffAddr_RatePara_Weekend        = (FileItemInfoOffAddr_RatePara_nLadder        +   FileItemInfoLen_RatePara_nLadder),
    FileItemInfoOffAddr_RatePara_WeekendPOT = (FileItemInfoOffAddr_RatePara_Weekend        +   FileItemInfoLen_RatePara_Weekend),
    FileItemInfoOffAddr_RatePara_RmDate     = (FileItemInfoOffAddr_RatePara_WeekendPOT +   FileItemInfoLen_RatePara_WeekendPOT),
    FileItemInfoOffAddr_RatePara_HolidayTable   = (FileItemInfoOffAddr_RatePara_RmDate +   FileItemInfoLen_RatePara_RmDate),
    FileItemInfoOffAddr_RatePara_TimeZonePara   = (FileItemInfoOffAddr_RatePara_HolidayTable   +   FileItemInfoLen_RatePara_HolidayTable),
    FileItemInfoOffAddr_RatePara_POTTablePara   = (FileItemInfoOffAddr_RatePara_TimeZonePara   +   FileItemInfoLen_RatePara_TimeZonePara),
    FileItemInfoOffAddr_RatePara_RatePricePara  = (FileItemInfoOffAddr_RatePara_POTTablePara   +   FileItemInfoLen_RatePara_POTTablePara),
    FileItemInfoOffAddr_RatePara_LadderPara     = (FileItemInfoOffAddr_RatePara_RatePricePara + FileItemInfoLen_RatePara_RatePricePara),
    FileItemInfoOffAddr_RatePara_ChargMoneyPara = (FileItemInfoOffAddr_RatePara_LadderPara +   FileItemInfoLen_RatePara_LadderPara),
    FileItemInfoOffAddr_RatePara_End    = (FileItemInfoOffAddr_RatePara_ChargMoneyPara +   FileItemInfoLen_RatePara_ChargMoneyPara)
} eDl645FileItemInfo_RatePara_TypeDef;//���ʲ�����Ϣ�ļ�

typedef enum
{
    //���
    FileItemInfoLen_DocPara_NeedMode                = 1,
    FileItemInfoLen_DocPara_NeedCyc         = 1,
    FileItemInfoLen_DocPara_NeedSlip        = 1,
    FileItemInfoLen_DocPara_PlsWidth        = 2,
    FileItemInfoLen_DocPara_nWave           = 1,
    FileItemInfoLen_DocPara_BroadcastMIN     = 2,
    FileItemInfoLen_DocPara_BroadcastMAX     = 2,
    FileItemInfoLen_DocPara_WirelessSignal  = 1,
    FileItemInfoLen_DocPara_Crc  = 2,

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_DocPara_NeedMode                = (0),
    FileItemInfoOffAddr_DocPara_NeedCyc         = (FileItemInfoOffAddr_DocPara_NeedMode            +    FileItemInfoLen_DocPara_NeedMode),
    FileItemInfoOffAddr_DocPara_NeedSlip        = (FileItemInfoOffAddr_DocPara_NeedCyc      +    FileItemInfoLen_DocPara_NeedCyc),
    FileItemInfoOffAddr_DocPara_PlsWidth        = (FileItemInfoOffAddr_DocPara_NeedSlip     +    FileItemInfoLen_DocPara_NeedSlip),
    FileItemInfoOffAddr_DocPara_nWave           = (FileItemInfoOffAddr_DocPara_PlsWidth     +    FileItemInfoLen_DocPara_PlsWidth),
    FileItemInfoOffAddr_DocPara_BroadcastMIN     = (FileItemInfoOffAddr_DocPara_nWave  +    FileItemInfoLen_DocPara_nWave),
    FileItemInfoOffAddr_DocPara_BroadcastMAX     = (FileItemInfoOffAddr_DocPara_BroadcastMIN        +    FileItemInfoLen_DocPara_BroadcastMIN),
    FileItemInfoOffAddr_DocPara_WirelessSignal  = (FileItemInfoOffAddr_DocPara_BroadcastMAX  +    FileItemInfoLen_DocPara_BroadcastMAX),
    FileItemInfoOffAddr_DocPara_Crc                     = (FileItemInfoOffAddr_DocPara_WirelessSignal  +  FileItemInfoLen_DocPara_WirelessSignal),
    FileItemInfoOffAddr_DocPara_end                     = (FileItemInfoOffAddr_DocPara_Crc  +  FileItemInfoLen_DocPara_Crc)
} eFileItemInfo_DocPara_TypeDef;// ͨ�ò����ļ�

typedef enum
{
    //���
    FileItemInfoLen_ComPara_ComAddr     = (6),
    FileItemInfoLen_ComPara_Ir1Style        = 1,
    FileItemInfoLen_ComPara_Ir2Style         = 1,
    FileItemInfoLen_ComPara_Com1Style        = 1,
    FileItemInfoLen_ComPara_Com2Style        = 1,
    FileItemInfoLen_ComPara_Com3Style        = 1,

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_ComPara_ComAddr     = (0),
    FileItemInfoOffAddr_ComPara_Ir1Style    = (FileItemInfoOffAddr_ComPara_ComAddr + FileItemInfoLen_ComPara_ComAddr),
    FileItemInfoOffAddr_ComPara_Ir2Style    = (FileItemInfoOffAddr_ComPara_Ir1Style    +   FileItemInfoLen_ComPara_Ir1Style),
    FileItemInfoOffAddr_ComPara_Com1Style   = (FileItemInfoOffAddr_ComPara_Ir2Style  +   FileItemInfoLen_ComPara_Ir2Style),
    FileItemInfoOffAddr_ComPara_Com2Style   = (FileItemInfoOffAddr_ComPara_Com1Style +   FileItemInfoLen_ComPara_Com1Style),
    FileItemInfoOffAddr_ComPara_Com3Style   = (FileItemInfoOffAddr_ComPara_Com2Style +   FileItemInfoLen_ComPara_Com2Style),
    FileItemInfoOffAddr_ComPara_end             = (FileItemInfoOffAddr_ComPara_Com3Style +   FileItemInfoLen_ComPara_Com3Style)
} eFileItemInfo_ComPara_TypeDef;// ͨѶ����

typedef enum
{
    //���
    FileItemInfoLen_DispPara_AllonDispTime  =   1,
    FileItemInfoLen_DispPara_KeyLightTime   =   2,
    FileItemInfoLen_DispPara_ChkLightTime   =   2,
    FileItemInfoLen_DispPara_KeyPwrOffTime  =   2,
    FileItemInfoLen_DispPara_DecimalEg  =   1,
    FileItemInfoLen_DispPara_DecimalPw  =   1,
    FileItemInfoLen_DispPara_LCDWordMn  =   1,
    FileItemInfoLen_DispPara_nCycDisp   =   1,
    FileItemInfoLen_DispPara_nKeyDisp   =   1,
    FileItemInfoLen_DispPara_AutoDispTime   =   2,
    FileItemInfoLen_DispPara_KeyDispTime    =   2,
    FileItemInfoLen_DispPara_CycDispItem        = (sizeof(sDispItem_TypeDef) * MAX_CYCDISP),
    FileItemInfoLen_DispPara_KeyDispItem        = (sizeof(sDispItem_TypeDef) * MAX_CYCDISP),

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_DispPara_AllonDispTime = (0),
    FileItemInfoOffAddr_DispPara_KeyLightTime = (FileItemInfoOffAddr_DispPara_AllonDispTime  +   FileItemInfoLen_DispPara_AllonDispTime),
    FileItemInfoOffAddr_DispPara_ChkLightTime = (FileItemInfoOffAddr_DispPara_KeyLightTime   +   FileItemInfoLen_DispPara_KeyLightTime),
    FileItemInfoOffAddr_DispPara_KeyPwrOffTime = (FileItemInfoOffAddr_DispPara_ChkLightTime   +   FileItemInfoLen_DispPara_ChkLightTime),
    FileItemInfoOffAddr_DispPara_DecimalEg    = (FileItemInfoOffAddr_DispPara_KeyPwrOffTime  +   FileItemInfoLen_DispPara_KeyPwrOffTime),
    FileItemInfoOffAddr_DispPara_DecimalPw    = (FileItemInfoOffAddr_DispPara_DecimalEg      +   FileItemInfoLen_DispPara_DecimalEg),
    FileItemInfoOffAddr_DispPara_LCDWordMn    = (FileItemInfoOffAddr_DispPara_DecimalPw      +   FileItemInfoLen_DispPara_DecimalPw),
    FileItemInfoOffAddr_DispPara_nCycDisp     = (FileItemInfoOffAddr_DispPara_LCDWordMn      +   FileItemInfoLen_DispPara_LCDWordMn),
    FileItemInfoOffAddr_DispPara_nKeyDisp     = (FileItemInfoOffAddr_DispPara_nCycDisp       +   FileItemInfoLen_DispPara_nCycDisp),
    FileItemInfoOffAddr_DispPara_AutoDispTime   = (FileItemInfoOffAddr_DispPara_nKeyDisp       +   FileItemInfoLen_DispPara_nKeyDisp),
    FileItemInfoOffAddr_DispPara_KeyDispTime    = (FileItemInfoOffAddr_DispPara_AutoDispTime   +   FileItemInfoLen_DispPara_AutoDispTime),
    FileItemInfoOffAddr_DispPara_CycDispItem    = (FileItemInfoOffAddr_DispPara_KeyDispTime      + FileItemInfoLen_DispPara_KeyDispTime),
    FileItemInfoOffAddr_DispPara_KeyDispItem    = (FileItemInfoOffAddr_DispPara_CycDispItem      + FileItemInfoLen_DispPara_CycDispItem),
    FileItemInfoOffAddr_DispPara_end            = (FileItemInfoOffAddr_DispPara_KeyDispItem      + FileItemInfoLen_DispPara_KeyDispItem)
} eDl645FileItemInfo_DispPara_TypeDef;//��ʾ����
typedef enum
{
    //���
    FileItemInfoLen_WastePara_Ga = sizeof(sDF26),
    FileItemInfoLen_WastePara_Ba = sizeof(sDF26),
    FileItemInfoLen_WastePara_Ra = sizeof(sDF26),
    FileItemInfoLen_WastePara_Xa = sizeof(sDF26),
    FileItemInfoLen_WastePara_Gb = sizeof(sDF26),
    FileItemInfoLen_WastePara_Bb = sizeof(sDF26),
    FileItemInfoLen_WastePara_Rb = sizeof(sDF26),
    FileItemInfoLen_WastePara_Xb = sizeof(sDF26),
    FileItemInfoLen_WastePara_Gc = sizeof(sDF26),
    FileItemInfoLen_WastePara_Bc = sizeof(sDF26),
    FileItemInfoLen_WastePara_Rc = sizeof(sDF26),
    FileItemInfoLen_WastePara_Xc = sizeof(sDF26),
    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_WastePara_Ga = (0),
    FileItemInfoOffAddr_WastePara_Ba = (FileItemInfoOffAddr_WastePara_Ga +  FileItemInfoLen_WastePara_Ga),
    FileItemInfoOffAddr_WastePara_Ra = (FileItemInfoOffAddr_WastePara_Ba +  FileItemInfoLen_WastePara_Ba),
    FileItemInfoOffAddr_WastePara_Xa = (FileItemInfoOffAddr_WastePara_Ra +  FileItemInfoLen_WastePara_Ra),
    FileItemInfoOffAddr_WastePara_Gb = (FileItemInfoOffAddr_WastePara_Xa +  FileItemInfoLen_WastePara_Xa),
    FileItemInfoOffAddr_WastePara_Bb = (FileItemInfoOffAddr_WastePara_Gb +  FileItemInfoLen_WastePara_Gb),
    FileItemInfoOffAddr_WastePara_Rb = (FileItemInfoOffAddr_WastePara_Bb +  FileItemInfoLen_WastePara_Bb),
    FileItemInfoOffAddr_WastePara_Xb = (FileItemInfoOffAddr_WastePara_Rb +  FileItemInfoLen_WastePara_Rb),
    FileItemInfoOffAddr_WastePara_Gc = (FileItemInfoOffAddr_WastePara_Xb +  FileItemInfoLen_WastePara_Xb),
    FileItemInfoOffAddr_WastePara_Bc = (FileItemInfoOffAddr_WastePara_Gc +  FileItemInfoLen_WastePara_Gc),
    FileItemInfoOffAddr_WastePara_Rc = (FileItemInfoOffAddr_WastePara_Bc +  FileItemInfoLen_WastePara_Bc),
    FileItemInfoOffAddr_WastePara_Xc = (FileItemInfoOffAddr_WastePara_Rc +  FileItemInfoLen_WastePara_Rc),
    FileItemInfoOffAddr_WastePara_end = (FileItemInfoOffAddr_WastePara_Xc +  FileItemInfoLen_WastePara_Xc)
} eFileItemInfo_WastePara_TypeDef;// ͨѶ����

typedef enum
{
    //���
    FileItemInfoLen_OutputPara_Style1                   = (2),
    FileItemInfoLen_OutputPara_Trigger1       = (2),
    FileItemInfoLen_OutputPara_Style2         = (2),
    FileItemInfoLen_OutputPara_Trigger2       = (2),
    FileItemInfoLen_OutputPara_Style3         = (2),
    FileItemInfoLen_OutputPara_Trigger3       = (2),
    FileItemInfoLen_OutputPara_Style4         = (2),
    FileItemInfoLen_OutputPara_Trigger4       = (2),
    FileItemInfoLen_OutputPara_Style5         = (2),
    FileItemInfoLen_OutputPara_Trigger5       = (2),
    FileItemInfoLen_OutputPara_Style6         = (2),
    FileItemInfoLen_OutputPara_Trigger6       = (2),
    FileItemInfoLen_OutputPara_RelaysOutAlarm = (10),
    FileItemInfoLen_OutputPara_LightAlarm     = (10),
    FileItemInfoLen_OutputPara_SoundAlarm     = (10),
    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_OutputPara_Style1                   = (0),
    FileItemInfoOffAddr_OutputPara_Trigger1       = (FileItemInfoOffAddr_OutputPara_Style1               +   FileItemInfoLen_OutputPara_Style1),
    FileItemInfoOffAddr_OutputPara_Style2         = (FileItemInfoOffAddr_OutputPara_Trigger1       +   FileItemInfoLen_OutputPara_Trigger1),
    FileItemInfoOffAddr_OutputPara_Trigger2       = (FileItemInfoOffAddr_OutputPara_Style2         +   FileItemInfoLen_OutputPara_Style2),
    FileItemInfoOffAddr_OutputPara_Style3         = (FileItemInfoOffAddr_OutputPara_Trigger2       +   FileItemInfoLen_OutputPara_Trigger2),
    FileItemInfoOffAddr_OutputPara_Trigger3       = (FileItemInfoOffAddr_OutputPara_Style3         +   FileItemInfoLen_OutputPara_Style3),
    FileItemInfoOffAddr_OutputPara_Style4         = (FileItemInfoOffAddr_OutputPara_Trigger3       +   FileItemInfoLen_OutputPara_Trigger3),
    FileItemInfoOffAddr_OutputPara_Trigger4       = (FileItemInfoOffAddr_OutputPara_Style4         +   FileItemInfoLen_OutputPara_Style4),
    FileItemInfoOffAddr_OutputPara_Style5         = (FileItemInfoOffAddr_OutputPara_Trigger4       +   FileItemInfoLen_OutputPara_Trigger4),
    FileItemInfoOffAddr_OutputPara_Trigger5       = (FileItemInfoOffAddr_OutputPara_Style5         +   FileItemInfoLen_OutputPara_Style5),
    FileItemInfoOffAddr_OutputPara_Style6         = (FileItemInfoOffAddr_OutputPara_Trigger5       +   FileItemInfoLen_OutputPara_Trigger5),
    FileItemInfoOffAddr_OutputPara_Trigger6       = (FileItemInfoOffAddr_OutputPara_Style6         +   FileItemInfoLen_OutputPara_Style6),
    FileItemInfoOffAddr_OutputPara_RelaysOutAlarm = (FileItemInfoOffAddr_OutputPara_Trigger6       +   FileItemInfoLen_OutputPara_Trigger6),
    FileItemInfoOffAddr_OutputPara_LightAlarm     = (FileItemInfoOffAddr_OutputPara_RelaysOutAlarm +   FileItemInfoLen_OutputPara_RelaysOutAlarm),
    FileItemInfoOffAddr_OutputPara_SoundAlarm     = (FileItemInfoOffAddr_OutputPara_LightAlarm     +   FileItemInfoLen_OutputPara_LightAlarm),
    FileItemInfoOffAddr_OutputPara_end                  = (FileItemInfoOffAddr_OutputPara_SoundAlarm     +   FileItemInfoLen_OutputPara_SoundAlarm)
} eFileItemInfo_OutputPara_TypeDef;//
typedef enum
{
    //���
    FileItemInfoLen_CipherKeyPara_nCipherKey                 = (1),
    FileItemInfoLen_CipherKeyPara_WriteStarFlag      = (1),
    FileItemInfoLen_CipherKeyPara_CipherKeyWriteFlag = (4),
    FileItemInfoLen_CipherKeyPara_CipherKeyFlag      = (16),
    FileItemInfoLen_CipherKeyPara_CipherKey          = (1024),
    FileItemInfoLen_CipherKeyPara_nCipherKeyEE       = (4),
    FileItemInfoLen_CipherKeyPara_OpCode             = (4),
    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_CipherKeyPara_nCipherKey               = (0),
    FileItemInfoOffAddr_CipherKeyPara_WriteStarFlag      = (FileItemInfoOffAddr_CipherKeyPara_nCipherKey               +  FileItemInfoLen_CipherKeyPara_nCipherKey),
    FileItemInfoOffAddr_CipherKeyPara_CipherKeyWriteFlag = (FileItemInfoOffAddr_CipherKeyPara_WriteStarFlag      +  FileItemInfoLen_CipherKeyPara_WriteStarFlag),
    FileItemInfoOffAddr_CipherKeyPara_CipherKeyFlag      = (FileItemInfoOffAddr_CipherKeyPara_CipherKeyWriteFlag +  FileItemInfoLen_CipherKeyPara_CipherKeyWriteFlag),
    FileItemInfoOffAddr_CipherKeyPara_CipherKey          = (FileItemInfoOffAddr_CipherKeyPara_CipherKeyFlag      +  FileItemInfoLen_CipherKeyPara_CipherKeyFlag),
    FileItemInfoOffAddr_CipherKeyPara_nCipherKeyEE       = (FileItemInfoOffAddr_CipherKeyPara_CipherKey          +  FileItemInfoLen_CipherKeyPara_CipherKey),
    FileItemInfoOffAddr_CipherKeyPara_OpCode             = (FileItemInfoOffAddr_CipherKeyPara_nCipherKeyEE       +  FileItemInfoLen_CipherKeyPara_nCipherKeyEE),
    FileItemInfoOffAddr_CipherKeyPara_end                              = (FileItemInfoOffAddr_CipherKeyPara_OpCode             +  FileItemInfoLen_CipherKeyPara_OpCode)
} eFileItemInfo_CipherKeyPara_TypeDef;//

typedef enum
{
    //���
    FileItemInfoLen_EvtReport_AtiveAllow      = (1),
    FileItemInfoLen_EvtReport_FollowAllow   = (1),
    FileItemInfoLen_EvtReport_RptFlagHappen = (7),     //7*8=56 ����֧��56���¼���¼
    FileItemInfoLen_EvtReport_RptFlagEnd    = (7),
    FileItemInfoLen_EvtReport_RptMode       = (7),
    FileItemInfoLen_EvtReport_RptStatusAllow = (1),
    FileItemInfoLen_EvtReport_RptStatusMode = (4),
    FileItemInfoLen_EvtReport_RptChannel    = (3),
    FileItemInfoLen_EvtReport_Crc               = (2),

    FileItemInfoLen_EvtReport_RptStatusZB    = (4),
    FileItemInfoLen_EvtReport_RptStuZBBack   = (4),
    FileItemInfoLen_EvtReport_RptStatus485   = (4),
    FileItemInfoLen_EvtReport_RptStu485Back  = (4),
    FileItemInfoLen_EvtReport_RptStatus4852  = (4),
    FileItemInfoLen_EvtReport_RptStu4852Back = (4),

    FileItemInfoLen_EvtReport_OADNumZB_A     = (1),
    FileItemInfoLen_EvtReport_RptListZB_A     = (4 * ITEM_EVT_MAX),

    FileItemInfoLen_EvtReport_OADNumZB_F     = (1),
    FileItemInfoLen_EvtReport_RptListZB_F     = (4 * ITEM_EVT_MAX),

    FileItemInfoLen_EvtReport_OADNum485_F    = (1),
    FileItemInfoLen_EvtReport_RptList485_F   = (4 * ITEM_EVT_MAX),

    FileItemInfoLen_EvtReport_OADNum4852_F   = (1),
    FileItemInfoLen_EvtReport_RptList4852_F    = (4 * ITEM_EVT_MAX),
    FileItemInfoLen_EvtReport_PowerUpTime    = (1),
    FileItemInfoLen_EvtReport_PowerDnEvtRcd      = (136),
    FileItemInfoLen_EvtReport_First_ClrTime     = (sizeof(sDate_time_s_TypeDef)),
    FileItemInfoLen_EvtReport_Factory_ClrTime        = (sizeof(sDate_time_s_TypeDef)),

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_EvtReport_AtiveAllow    = (0),
    FileItemInfoOffAddr_EvtReport_FollowAllow   = (FileItemInfoOffAddr_EvtReport_AtiveAllow  + FileItemInfoLen_EvtReport_AtiveAllow),
    FileItemInfoOffAddr_EvtReport_RptFlagHappen = (FileItemInfoOffAddr_EvtReport_FollowAllow + FileItemInfoLen_EvtReport_FollowAllow),
    FileItemInfoOffAddr_EvtReport_RptFlagEnd    = (FileItemInfoOffAddr_EvtReport_RptFlagHappen + FileItemInfoLen_EvtReport_RptFlagHappen),
    FileItemInfoOffAddr_EvtReport_RptMode       = (FileItemInfoOffAddr_EvtReport_RptFlagEnd    + FileItemInfoLen_EvtReport_RptFlagEnd),
    FileItemInfoOffAddr_EvtReport_RptStatusAllow = (FileItemInfoOffAddr_EvtReport_RptMode       + FileItemInfoLen_EvtReport_RptMode),
    FileItemInfoOffAddr_EvtReport_RptStatusMode = (FileItemInfoOffAddr_EvtReport_RptStatusAllow + FileItemInfoLen_EvtReport_RptStatusAllow),
    FileItemInfoOffAddr_EvtReport_RptChannel    = (FileItemInfoOffAddr_EvtReport_RptStatusMode + FileItemInfoLen_EvtReport_RptStatusMode),
    FileItemInfoOffAddr_EvtReport_Crc           = (FileItemInfoOffAddr_EvtReport_RptChannel + FileItemInfoLen_EvtReport_RptChannel),

    FileItemInfoOffAddr_EvtReport_RptStatusZB   = (FileItemInfoOffAddr_EvtReport_Crc         + FileItemInfoLen_EvtReport_Crc),
    FileItemInfoOffAddr_EvtReport_RptStuZBBack  = (FileItemInfoOffAddr_EvtReport_RptStatusZB + FileItemInfoLen_EvtReport_RptStatusZB),
    FileItemInfoOffAddr_EvtReport_RptStatus485  = (FileItemInfoOffAddr_EvtReport_RptStuZBBack  + FileItemInfoLen_EvtReport_RptStuZBBack),
    FileItemInfoOffAddr_EvtReport_RptStu485Back = (FileItemInfoOffAddr_EvtReport_RptStatus485 + FileItemInfoLen_EvtReport_RptStatus485),
    FileItemInfoOffAddr_EvtReport_RptStatus4852 = (FileItemInfoOffAddr_EvtReport_RptStu485Back + FileItemInfoLen_EvtReport_RptStu485Back),
    FileItemInfoOffAddr_EvtReport_RptStu4852Back = (FileItemInfoOffAddr_EvtReport_RptStatus4852 + FileItemInfoLen_EvtReport_RptStatus4852),

    FileItemInfoOffAddr_EvtReport_OADNumZB_A    = (FileItemInfoOffAddr_EvtReport_RptStu4852Back + FileItemInfoLen_EvtReport_RptStu4852Back),
    FileItemInfoOffAddr_EvtReport_RptListZB_A   = (FileItemInfoOffAddr_EvtReport_OADNumZB_A    + FileItemInfoLen_EvtReport_OADNumZB_A),

    FileItemInfoOffAddr_EvtReport_OADNumZB_F    = (FileItemInfoOffAddr_EvtReport_RptListZB_A   + FileItemInfoLen_EvtReport_RptListZB_A),
    FileItemInfoOffAddr_EvtReport_RptListZB_F   = (FileItemInfoOffAddr_EvtReport_OADNumZB_F    + FileItemInfoLen_EvtReport_OADNumZB_F),

    FileItemInfoOffAddr_EvtReport_OADNum485_F   = (FileItemInfoOffAddr_EvtReport_RptListZB_F   + FileItemInfoLen_EvtReport_RptListZB_F),
    FileItemInfoOffAddr_EvtReport_RptList485_F  = (FileItemInfoOffAddr_EvtReport_OADNum485_F   + FileItemInfoLen_EvtReport_OADNum485_F),

    FileItemInfoOffAddr_EvtReport_OADNum4852_F  = (FileItemInfoOffAddr_EvtReport_RptList485_F  + FileItemInfoLen_EvtReport_RptList485_F),
    FileItemInfoOffAddr_EvtReport_RptList4852_F = (FileItemInfoOffAddr_EvtReport_OADNum4852_F  + FileItemInfoLen_EvtReport_OADNum4852_F),

    FileItemInfoOffAddr_EvtReport_PowerUpTime   = (FileItemInfoOffAddr_EvtReport_RptList4852_F + FileItemInfoLen_EvtReport_RptList4852_F),
    FileItemInfoOffAddr_EvtReport_PowerDnEvtRcd = (FileItemInfoOffAddr_EvtReport_PowerUpTime + FileItemInfoLen_EvtReport_PowerUpTime),
    FileItemInfoOffAddr_EvtReport_First_ClrTime         = (FileItemInfoOffAddr_EvtReport_PowerDnEvtRcd + FileItemInfoLen_EvtReport_PowerDnEvtRcd),
    FileItemInfoOffAddr_EvtReport_Factory_ClrTime           = (FileItemInfoOffAddr_EvtReport_First_ClrTime + FileItemInfoLen_EvtReport_First_ClrTime),

    FileItemInfoOffAddr_EvtReport_end           = (FileItemInfoOffAddr_EvtReport_Factory_ClrTime + FileItemInfoLen_EvtReport_Factory_ClrTime)
} eFileItemInfo_EvtReport_TypeDef;//

typedef enum
{
    //���
    FileItemInfoLen_ASCIIPara_MeterPlace    = (12),
    FileItemInfoLen_ASCIIPara_DeviceNo    = (32),
    FileItemInfoLen_ASCIIPara_RatingVol   = (6),
    FileItemInfoLen_ASCIIPara_MinCur    = (32),
    FileItemInfoLen_ASCIIPara_TrCur     = (32),
    FileItemInfoLen_ASCIIPara_RatingCur   = (6),
    FileItemInfoLen_ASCIIPara_MaxCur      = (6),
    FileItemInfoLen_ASCIIPara_PGrade      = (4),
    FileItemInfoLen_ASCIIPara_QGrade      = (4),
    FileItemInfoLen_ASCIIPara_MeterModel  = (32),
    FileItemInfoLen_ASCIIPara_ProductDate = (7),
    FileItemInfoLen_ASCIIPara_PtVer       = (20),
    FileItemInfoLen_ASCIIPara_SoftVer     = (32),
    FileItemInfoLen_ASCIIPara_FirmVer     = (32),
    FileItemInfoLen_ASCIIPara_FactoryNo   = (32),
    FileItemInfoLen_ASCIIPara_SoftWare    = (16),
    FileItemInfoLen_ASCIIPara_SoftWareInfo  = (32),
    FileItemInfoLen_ASCIIPara_ServerVer   = (32),
    FileItemInfoLen_ASCIIPara_FactoryMAC   = (32),
    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_ASCIIPara_MeterPlace    = (0),
    FileItemInfoOffAddr_ASCIIPara_DeviceNo    = (FileItemInfoOffAddr_ASCIIPara_MeterPlace  +  FileItemInfoLen_ASCIIPara_MeterPlace),
    FileItemInfoOffAddr_ASCIIPara_RatingVol   = (FileItemInfoOffAddr_ASCIIPara_DeviceNo    +  FileItemInfoLen_ASCIIPara_DeviceNo),
    FileItemInfoOffAddr_ASCIIPara_MinCur   = (FileItemInfoOffAddr_ASCIIPara_RatingVol  +  FileItemInfoLen_ASCIIPara_RatingVol),
    FileItemInfoOffAddr_ASCIIPara_TrCur   = (FileItemInfoOffAddr_ASCIIPara_MinCur   +  FileItemInfoLen_ASCIIPara_MinCur),
    FileItemInfoOffAddr_ASCIIPara_RatingCur   = (FileItemInfoOffAddr_ASCIIPara_TrCur   +  FileItemInfoLen_ASCIIPara_TrCur),
    FileItemInfoOffAddr_ASCIIPara_MaxCur      = (FileItemInfoOffAddr_ASCIIPara_RatingCur   +  FileItemInfoLen_ASCIIPara_RatingCur),
    FileItemInfoOffAddr_ASCIIPara_PGrade      = (FileItemInfoOffAddr_ASCIIPara_MaxCur      +  FileItemInfoLen_ASCIIPara_MaxCur),
    FileItemInfoOffAddr_ASCIIPara_QGrade      = (FileItemInfoOffAddr_ASCIIPara_PGrade      +  FileItemInfoLen_ASCIIPara_PGrade),
    FileItemInfoOffAddr_ASCIIPara_MeterModel  = (FileItemInfoOffAddr_ASCIIPara_QGrade     +  FileItemInfoLen_ASCIIPara_QGrade),
    FileItemInfoOffAddr_ASCIIPara_ProductDate = (FileItemInfoOffAddr_ASCIIPara_MeterModel  +  FileItemInfoLen_ASCIIPara_MeterModel),
    FileItemInfoOffAddr_ASCIIPara_PtVer       = (FileItemInfoOffAddr_ASCIIPara_ProductDate +  FileItemInfoLen_ASCIIPara_ProductDate),
    FileItemInfoOffAddr_ASCIIPara_SoftVer     = (FileItemInfoOffAddr_ASCIIPara_PtVer       +  FileItemInfoLen_ASCIIPara_PtVer),
    FileItemInfoOffAddr_ASCIIPara_FirmVer     = (FileItemInfoOffAddr_ASCIIPara_SoftVer     +  FileItemInfoLen_ASCIIPara_SoftVer),
    FileItemInfoOffAddr_ASCIIPara_FactoryNo   = (FileItemInfoOffAddr_ASCIIPara_FirmVer     +  FileItemInfoLen_ASCIIPara_FirmVer),
    FileItemInfoOffAddr_ASCIIPara_SoftWare    = (FileItemInfoOffAddr_ASCIIPara_FactoryNo   +  FileItemInfoLen_ASCIIPara_FactoryNo),
    FileItemInfoOffAddr_ASCIIPara_SoftWareInfo   = (FileItemInfoOffAddr_ASCIIPara_SoftWare +  FileItemInfoLen_ASCIIPara_SoftWare),
    FileItemInfoOffAddr_ASCIIPara_ServerVer   = (FileItemInfoOffAddr_ASCIIPara_SoftWareInfo    +  FileItemInfoLen_ASCIIPara_SoftWareInfo),
    FileItemInfoOffAddr_ASCIIPara_FactoryMAC = (FileItemInfoOffAddr_ASCIIPara_ServerVer   +  FileItemInfoLen_ASCIIPara_ServerVer),
    FileItemInfoOffAddr_ASCIIPara_end               = (FileItemInfoOffAddr_ASCIIPara_FactoryMAC   +  FileItemInfoLen_ASCIIPara_FactoryMAC)
} eFileItemInfo_ASCIIPara_TypeDef;//
typedef enum
{
    //���
    FileItemInfoLen_HighState_tEvRstDec                 = (1),
    FileItemInfoLen_HighState_GataCheckFlag     = (2),
    FileItemInfoLen_HighState_FactoryFlag       = (1),
    FileItemInfoLen_HighState_GateOffRemainTime = (2),
    FileItemInfoLen_HighState_GataOffStat       = (1),
    FileItemInfoLen_HighState_PowDnMoneySta     = (1),
    FileItemInfoLen_HighState_LocalOpenFlag     = (1),
    FileItemInfoLen_HighState_Gata_Do     = (2),
    FileItemInfoLen_HighState_Gata_Err     = (2),
    FileItemInfoLen_HighState_BroatStatue     = (sizeof(sBroatStatue_TypeDef)),
    FileItemInfoLen_HighState_PrgQ1_Cnt     = 4,    //�޹�1��̴���
    FileItemInfoLen_HighState_PrgQ2_Cnt     = 4,    //�޹�2��̴���
    FileItemInfoLen_HighState_EvtSumTime        = 4 * MAX_EVENTTYPE,
    FileItemInfoLen_HighState_EvtRcdBfEsam      = (8),
    FileItemInfoLen_HighState_EvtRcdAftEsam     = (8),
    FileItemInfoLen_HighState_MngPlugSta        = (2),
    FileItemInfoLen_HighState_EvtFlag       = (4),
    FileItemInfoLen_HighState_EvtMngStr     = (FileItemInfoLen_HighState_EvtRcdBfEsam + FileItemInfoLen_HighState_EvtRcdAftEsam + FileItemInfoLen_HighState_MngPlugSta + FileItemInfoLen_HighState_EvtFlag),
    FileItemInfoLen_HighState_EvtPwn        = (sizeof(sEvtPwnCoverTailTypedef)),
    FileItemInfoLen_HighState_PwdnVoltLoss  = (sizeof(sPwdnVoltCurTypedef)),

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_HighState_tEvRstDec                   = (0),
    FileItemInfoOffAddr_HighState_GataCheckFlag     = (FileItemInfoOffAddr_HighState_tEvRstDec                   + FileItemInfoLen_HighState_tEvRstDec),
    FileItemInfoOffAddr_HighState_FactoryFlag       = (FileItemInfoOffAddr_HighState_GataCheckFlag     + FileItemInfoLen_HighState_GataCheckFlag),
    FileItemInfoOffAddr_HighState_GateOffRemainTime = (FileItemInfoOffAddr_HighState_FactoryFlag       + FileItemInfoLen_HighState_FactoryFlag),
    FileItemInfoOffAddr_HighState_GataOffStat       = (FileItemInfoOffAddr_HighState_GateOffRemainTime + FileItemInfoLen_HighState_GateOffRemainTime),
    FileItemInfoOffAddr_HighState_PowDnMoneySta     = (FileItemInfoOffAddr_HighState_GataOffStat       + FileItemInfoLen_HighState_GataOffStat),
    FileItemInfoOffAddr_HighState_LocalOpenFlag     = (FileItemInfoOffAddr_HighState_PowDnMoneySta     + FileItemInfoLen_HighState_PowDnMoneySta),
    FileItemInfoOffAddr_HighState_Gata_Do   = (FileItemInfoOffAddr_HighState_LocalOpenFlag     + FileItemInfoLen_HighState_LocalOpenFlag),
    FileItemInfoOffAddr_HighState_Gata_Err      = (FileItemInfoOffAddr_HighState_Gata_Do     + FileItemInfoLen_HighState_Gata_Do),
    FileItemInfoOffAddr_HighState_BroatStatue   = (FileItemInfoOffAddr_HighState_Gata_Err     + FileItemInfoLen_HighState_Gata_Err),
    FileItemInfoOffAddr_HighState_PrgQ1_Cnt     = (FileItemInfoOffAddr_HighState_BroatStatue     + FileItemInfoLen_HighState_BroatStatue),
    FileItemInfoOffAddr_HighState_PrgQ2_Cnt     = (FileItemInfoOffAddr_HighState_PrgQ1_Cnt     + FileItemInfoLen_HighState_PrgQ1_Cnt),
    FileItemInfoOffAddr_HighState_EvtSumTime = (FileItemInfoOffAddr_HighState_PrgQ2_Cnt     + FileItemInfoLen_HighState_PrgQ2_Cnt),
    FileItemInfoOffAddr_HighState_EvtRcdBfEsam = (FileItemInfoOffAddr_HighState_EvtSumTime     + FileItemInfoLen_HighState_EvtSumTime),
    FileItemInfoOffAddr_HighState_EvtRcdAfterEsam = (FileItemInfoOffAddr_HighState_EvtRcdBfEsam     + FileItemInfoLen_HighState_EvtRcdBfEsam),
    FileItemInfoOffAddr_HighState_MngPlugSta = (FileItemInfoOffAddr_HighState_EvtRcdAfterEsam     + FileItemInfoLen_HighState_EvtRcdAftEsam),
    FileItemInfoOffAddr_HighState_EvtFlag = (FileItemInfoOffAddr_HighState_MngPlugSta     + FileItemInfoLen_HighState_MngPlugSta),
    FileItemInfoOffAddr_HighState_EvtPwn = (FileItemInfoOffAddr_HighState_EvtFlag     + FileItemInfoLen_HighState_EvtFlag),

    FileItemInfoOffAddr_HighState_PwdnVoltLoss = (FileItemInfoOffAddr_HighState_EvtPwn  + FileItemInfoLen_HighState_EvtPwn),

    FileItemInfoOffAddr_HighState_end           = (FileItemInfoOffAddr_HighState_PwdnVoltLoss  + FileItemInfoLen_HighState_PwdnVoltLoss),

    FileItemInfoLen_HighState_TotalLen        = FileItemInfoOffAddr_HighState_end
} eFileItemInfo_HighState_TypeDef;//

typedef enum
{
    //���
    FileItemInfoLen_HighPara_PExpression    = (1),
    FileItemInfoLen_HighPara_PtQExpression  = (1),
    FileItemInfoLen_HighPara_NtQExpression  = (1),
    FileItemInfoLen_HighPara_PConstE     = (4),
    FileItemInfoLen_HighPara_QConstE     = (4),
    FileItemInfoLen_HighPara_MeterNo                = (sizeof(sDF12)),
    FileItemInfoLen_HighPara_CT                     = (4),
    FileItemInfoLen_HighPara_PT                     = (4),
    FileItemInfoLen_HighPara_WireMode           = (1),
    FileItemInfoLen_HighPara_StartCur           = (4),
    FileItemInfoLen_HighPara_CriticalVol        = (2),
    FileItemInfoLen_HighPara_UserNo             =   6,//(   sizeof( sDF12   )   ),
    FileItemInfoLen_HighPara_CardSerial     = (8),
    FileItemInfoLen_HighPara_MeterRunFlag   = (1),
    FileItemInfoLen_HighPara_tIRPrg                 = (4),
    FileItemInfoLen_HighPara_tTerminalPrg       = (4),
    FileItemInfoLen_HighPara_tEvRstDely     = (1),
    FileItemInfoLen_HighPara_GataSafeCur    = (4),
    FileItemInfoLen_HighPara_tSafeGata      = (2),
    FileItemInfoLen_HighPara_GateOffDelayTime   = (2),
    FileItemInfoLen_HighPara_ParaVolYield   = (sizeof(sVolYieldPara_TypeDef)),
    FileItemInfoLen_HighPara_RTCDota0          = (sizeof(sRTCParaE2_TypeDef)),
    FileItemInfoLen_HighPara_RTCAdj            = 4,
    FileItemInfoLen_HighPara_RTCCalData      = 10,
    FileItemInfoLen_HighPara_FristPowOnBak2     = (4),
    FileItemInfoLen_HighPara_Crc        = (2),
    //��ƫ�Ƶ�ַtTerminalDly
    FileItemInfoOffAddr_HighPara_PExpression         = (0),
    FileItemInfoOffAddr_HighPara_PtQExpression     = (FileItemInfoOffAddr_HighPara_PExpression         + FileItemInfoLen_HighPara_PExpression),
    FileItemInfoOffAddr_HighPara_NtQExpression     = (FileItemInfoOffAddr_HighPara_PtQExpression     + FileItemInfoLen_HighPara_PtQExpression),
    FileItemInfoOffAddr_HighPara_PConstE                   = (FileItemInfoOffAddr_HighPara_NtQExpression     + FileItemInfoLen_HighPara_NtQExpression),
    FileItemInfoOffAddr_HighPara_QConstE                   = (FileItemInfoOffAddr_HighPara_PConstE       +       FileItemInfoLen_HighPara_PConstE),
    FileItemInfoOffAddr_HighPara_MeterNo                   = (FileItemInfoOffAddr_HighPara_QConstE                   + FileItemInfoLen_HighPara_QConstE),
    FileItemInfoOffAddr_HighPara_CT                        = (FileItemInfoOffAddr_HighPara_MeterNo                   + FileItemInfoLen_HighPara_MeterNo),
    FileItemInfoOffAddr_HighPara_PT                        = (FileItemInfoOffAddr_HighPara_CT                        + FileItemInfoLen_HighPara_CT),
    FileItemInfoOffAddr_HighPara_WireMode              = (FileItemInfoOffAddr_HighPara_PT                        + FileItemInfoLen_HighPara_PT),
    FileItemInfoOffAddr_HighPara_StartCur              = (FileItemInfoOffAddr_HighPara_WireMode              + FileItemInfoLen_HighPara_WireMode),
    FileItemInfoOffAddr_HighPara_CriticalVol           = (FileItemInfoOffAddr_HighPara_StartCur              + FileItemInfoLen_HighPara_StartCur),
    FileItemInfoOffAddr_HighPara_UserNo                = (FileItemInfoOffAddr_HighPara_CriticalVol         + FileItemInfoLen_HighPara_CriticalVol),
    FileItemInfoOffAddr_HighPara_CardSerial        = (FileItemInfoOffAddr_HighPara_UserNo                + FileItemInfoLen_HighPara_UserNo),
    FileItemInfoOffAddr_HighPara_MeterRunFlag      = (FileItemInfoOffAddr_HighPara_CardSerial        + FileItemInfoLen_HighPara_CardSerial),
    FileItemInfoOffAddr_HighPara_tIRPrg                = (FileItemInfoOffAddr_HighPara_MeterRunFlag       +  FileItemInfoLen_HighPara_MeterRunFlag),
    FileItemInfoOffAddr_HighPara_tTerminalPrg        = (FileItemInfoOffAddr_HighPara_tIRPrg                  + FileItemInfoLen_HighPara_tIRPrg),
    FileItemInfoOffAddr_HighPara_tEvRstDely        = (FileItemInfoOffAddr_HighPara_tTerminalPrg       +  FileItemInfoLen_HighPara_tTerminalPrg),
    FileItemInfoOffAddr_HighPara_GataSafeCur           = (FileItemInfoOffAddr_HighPara_tEvRstDely        + FileItemInfoLen_HighPara_tEvRstDely),
    FileItemInfoOffAddr_HighPara_tSafeGata             = (FileItemInfoOffAddr_HighPara_GataSafeCur       + FileItemInfoLen_HighPara_GataSafeCur),
    FileItemInfoOffAddr_HighPara_GateOffDelayTime = (FileItemInfoOffAddr_HighPara_tSafeGata          + FileItemInfoLen_HighPara_tSafeGata),
    FileItemInfoOffAddr_HighPara_ParaVolYield      = (FileItemInfoOffAddr_HighPara_GateOffDelayTime + FileItemInfoLen_HighPara_GateOffDelayTime),
    FileItemInfoOffAddr_HighPara_RTCDota0          = (FileItemInfoOffAddr_HighPara_ParaVolYield            + FileItemInfoLen_HighPara_ParaVolYield),
    FileItemInfoOffAddr_HighPara_RTCAdj            = (FileItemInfoOffAddr_HighPara_RTCDota0        + FileItemInfoLen_HighPara_RTCDota0),
    FileItemInfoOffAddr_HighPara_RTCCalData       = (FileItemInfoOffAddr_HighPara_RTCAdj           + FileItemInfoLen_HighPara_RTCAdj),
    FileItemInfoOffAddr_HighPara_FristPowOnBak2  = (FileItemInfoOffAddr_HighPara_RTCCalData + FileItemInfoLen_HighPara_RTCCalData),
    FileItemInfoOffAddr_HighPara_Crc              = (FileItemInfoOffAddr_HighPara_FristPowOnBak2   + FileItemInfoLen_HighPara_FristPowOnBak2),
    FileItemInfoOffAddr_HighPara_end              = (FileItemInfoOffAddr_HighPara_Crc  + FileItemInfoLen_HighPara_Crc)
} eFileItemInfo_HighPara_TypeDef;//�߼������ļ�

typedef enum
{
    //���
    FileItemInfoLen_SecretPara_SecretPara   = (40),
    FileItemInfoLen_SecretPara_nPswRetry        = (1),
    FileItemInfoLen_SecretPara_tPswFailClose        = (2),
    FileItemInfoLen_SecretPara_tPrgKeyValid = (2),
    FileItemInfoLen_SecretPara_tPrgKeyLock  = (2),
    FileItemInfoLen_SecretPara_SafeModeFlag = (1),
    FileItemInfoLen_SecretPara_SafeModePara =   sizeof(sSafeModePara_TypeDef),
    FileItemInfoLen_SecretPara_AuthOn       =   1,
    FileItemInfoLen_SecretPara_FuncationItem    = (32),
    FileItemInfoLen_SecretPara_Labour   = (32),
    FileItemInfoLen_SecretPara_FristPowOnBak1   = (4),

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_SecretPara_SecretPara   = (0),
    FileItemInfoOffAddr_SecretPara_nPswRetry     = (FileItemInfoOffAddr_SecretPara_SecretPara      +    FileItemInfoLen_SecretPara_SecretPara),
    FileItemInfoOffAddr_SecretPara_tPswFailClose = (FileItemInfoOffAddr_SecretPara_nPswRetry     +  FileItemInfoLen_SecretPara_nPswRetry),
    FileItemInfoOffAddr_SecretPara_tPrgKeyValid  = (FileItemInfoOffAddr_SecretPara_tPswFailClose +  FileItemInfoLen_SecretPara_tPswFailClose),
    FileItemInfoOffAddr_SecretPara_tPrgKeyLock   = (FileItemInfoOffAddr_SecretPara_tPrgKeyValid  +  FileItemInfoLen_SecretPara_tPrgKeyValid),
    FileItemInfoOffAddr_SecretPara_SafeModeFlag  = (FileItemInfoOffAddr_SecretPara_tPrgKeyLock       +  FileItemInfoLen_SecretPara_tPrgKeyLock),
    FileItemInfoOffAddr_SecretPara_SafeModePara  = (FileItemInfoOffAddr_SecretPara_SafeModeFlag  +  FileItemInfoLen_SecretPara_SafeModeFlag),
    FileItemInfoOffAddr_SecretPara_AuthOn        = (FileItemInfoOffAddr_SecretPara_SafeModePara  +  FileItemInfoLen_SecretPara_SafeModePara),
    FileItemInfoOffAddr_SecretPara_FuncationItem = (FileItemInfoOffAddr_SecretPara_AuthOn    +  FileItemInfoLen_SecretPara_AuthOn),
    FileItemInfoOffAddr_SecretPara_Labour          = (FileItemInfoOffAddr_SecretPara_FuncationItem +  FileItemInfoLen_SecretPara_FuncationItem),
    FileItemInfoOffAddr_SecretPara_FristPowOnBak1 = (FileItemInfoOffAddr_SecretPara_Labour    +  FileItemInfoLen_SecretPara_Labour),
    FileItemInfoOffAddr_SecretPara_End           = (FileItemInfoOffAddr_SecretPara_FristPowOnBak1   +   FileItemInfoLen_SecretPara_FristPowOnBak1)
} eFileItemInfo_SecretPara_TypeDef;//�������

typedef enum
{
    //���
    FileItemInfoLen_FirmPara_FractionI         = 1,
    FileItemInfoLen_FirmPara_FractionU         = 1,
    FileItemInfoLen_FirmPara_FractionE         = 1,
    FileItemInfoLen_FirmPara_FractionP         = 1,
    FileItemInfoLen_FirmPara_Pulse_deltaE      = 2,
    FileItemInfoLen_FirmPara_HighPulseRate   = 1,
    FileItemInfoLen_FirmPara_HFConst1            = 2,
    FileItemInfoLen_FirmPara_Start_Ps            = 2,
    FileItemInfoLen_FirmPara_Start_Q               = 2,
    FileItemInfoLen_FirmPara_ELostVoltT      = 2,
    FileItemInfoLen_FirmPara_Zxot                = 2,
    FileItemInfoLen_FirmPara_PRth                  = 8,
    FileItemInfoLen_FirmPara_PHSU                  = 3,
    FileItemInfoLen_FirmPara_PHSI                  = 12,
    FileItemInfoLen_FirmPara_GSU                   = 6,
    FileItemInfoLen_FirmPara_GSI                   = 8,
    FileItemInfoLen_FirmPara_U_OS                  = 6,
    FileItemInfoLen_FirmPara_I_OS                  = 8,
    FileItemInfoLen_FirmPara_GP                  = 6,
    FileItemInfoLen_FirmPara_GQ                  = 6,
    FileItemInfoLen_FirmPara_GS                  = 6,
    FileItemInfoLen_FirmPara_P_PHS               = 6,
    FileItemInfoLen_FirmPara_Q_PHS               = 6,
    FileItemInfoLen_FirmPara_P_OS                = 6,
    FileItemInfoLen_FirmPara_Q_OS                = 6,
    FileItemInfoLen_FirmPara_P_PHSMH             = 24,
    FileItemInfoLen_FirmPara_Q_PHSMH             = 24,
    FileItemInfoLen_FirmPara_ChkSum1             = 4,
    FileItemInfoLen_FirmPara_KUrms             = 4,
    FileItemInfoLen_FirmPara_KIArms            = 4,
    FileItemInfoLen_FirmPara_KPrms             = 4,
    FileItemInfoLen_FirmPara_RatedU            = 2,
    FileItemInfoLen_FirmPara_RatedUrms       = 4,
    FileItemInfoLen_FirmPara_RatedI            = 2,
    FileItemInfoLen_FirmPara_RatedIrms       = 4,
    FileItemInfoLen_FirmPara_RealU               = 12,
    FileItemInfoLen_FirmPara_RealI               = 16,
    FileItemInfoLen_FirmPara_RealAngle       = 12,
    FileItemInfoLen_FirmPara_RealPw            = 12,
    FileItemInfoLen_FirmPara_Send_nPoint        = 2,
    FileItemInfoLen_FirmPara_Crc                    = 2,

    FileItemInfoLen_VoltRepair_EnOrDis       =  1,
    FileItemInfoLen_VoltRepair_Rep           =  nPhs * MAX_VOLT_STEP,
    FileItemInfoLen_VoltRepair_Crc           =  2,
    FileItemInfoLen_VoltRepair_RN8302TIRM            =  2,
    FileItemInfoLen_VoltRepair_RN8207DTIRM           =  nPhs * 2,

    FileItemInfoLen_Harmonic_FftGP           =  nPhs * (41 * 2 + 2),  //-��2�ֽ�Ϊ����RAM���� ---
    FileItemInfoLen_Harmonic_FftCosAngle             =  nPhs * 41 * 4,
    FileItemInfoLen_Harmonic_Crc             =  4,

    // dyf ���������������в���
    FileItemInfoLen_Xiebo_Flag_EnOrDis          = 1,
    FileItemInfoLen_Xiebo_Err                   = 8,
    FileItemInfoLen_Xiebo_Value                 = 24,
    FileItemInfoLen_Xiebo_Mid_Current           = 4,

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_FirmPara_FractionI        = (0),
    FileItemInfoOffAddr_FirmPara_FractionU        = (FileItemInfoOffAddr_FirmPara_FractionI         + FileItemInfoLen_FirmPara_FractionI),
    FileItemInfoOffAddr_FirmPara_FractionE        = (FileItemInfoOffAddr_FirmPara_FractionU         + FileItemInfoLen_FirmPara_FractionU),
    FileItemInfoOffAddr_FirmPara_FractionP        = (FileItemInfoOffAddr_FirmPara_FractionE         + FileItemInfoLen_FirmPara_FractionE),
    FileItemInfoOffAddr_FirmPara_Pulse_deltaE     = (FileItemInfoOffAddr_FirmPara_FractionP         + FileItemInfoLen_FirmPara_FractionP),
    FileItemInfoOffAddr_FirmPara_HighPulseRate  = (FileItemInfoOffAddr_FirmPara_Pulse_deltaE    + FileItemInfoLen_FirmPara_Pulse_deltaE),
    FileItemInfoOffAddr_FirmPara_HFConst1         = (FileItemInfoOffAddr_FirmPara_HighPulseRate + FileItemInfoLen_FirmPara_HighPulseRate),
    FileItemInfoOffAddr_FirmPara_Start_Ps         = (FileItemInfoOffAddr_FirmPara_HFConst1      + FileItemInfoLen_FirmPara_HFConst1),
    FileItemInfoOffAddr_FirmPara_Start_Q            = (FileItemInfoOffAddr_FirmPara_Start_Ps        + FileItemInfoLen_FirmPara_Start_Ps),
    FileItemInfoOffAddr_FirmPara_ELostVoltT     = (FileItemInfoOffAddr_FirmPara_Start_Q           + FileItemInfoLen_FirmPara_Start_Q),
    FileItemInfoOffAddr_FirmPara_Zxot               = (FileItemInfoOffAddr_FirmPara_ELostVoltT    + FileItemInfoLen_FirmPara_ELostVoltT),
    FileItemInfoOffAddr_FirmPara_PRth                 = (FileItemInfoOffAddr_FirmPara_Zxot            + FileItemInfoLen_FirmPara_Zxot),
    FileItemInfoOffAddr_FirmPara_PHSU                 = (FileItemInfoOffAddr_FirmPara_PRth              + FileItemInfoLen_FirmPara_PRth),
    FileItemInfoOffAddr_FirmPara_PHSI                 = (FileItemInfoOffAddr_FirmPara_PHSU              + FileItemInfoLen_FirmPara_PHSU),
    FileItemInfoOffAddr_FirmPara_GSU                  = (FileItemInfoOffAddr_FirmPara_PHSI              + FileItemInfoLen_FirmPara_PHSI),
    FileItemInfoOffAddr_FirmPara_GSI                  = (FileItemInfoOffAddr_FirmPara_GSU               + FileItemInfoLen_FirmPara_GSU),
    FileItemInfoOffAddr_FirmPara_U_OS               = (FileItemInfoOffAddr_FirmPara_GSI                 + FileItemInfoLen_FirmPara_GSI),
    FileItemInfoOffAddr_FirmPara_I_OS               = (FileItemInfoOffAddr_FirmPara_U_OS              + FileItemInfoLen_FirmPara_U_OS),
    FileItemInfoOffAddr_FirmPara_GP                 = (FileItemInfoOffAddr_FirmPara_I_OS              + FileItemInfoLen_FirmPara_I_OS),
    FileItemInfoOffAddr_FirmPara_GQ                 = (FileItemInfoOffAddr_FirmPara_GP                + FileItemInfoLen_FirmPara_GP),
    FileItemInfoOffAddr_FirmPara_GS                 = (FileItemInfoOffAddr_FirmPara_GQ                + FileItemInfoLen_FirmPara_GQ),
    FileItemInfoOffAddr_FirmPara_P_PHS            = (FileItemInfoOffAddr_FirmPara_GS                  + FileItemInfoLen_FirmPara_GS),
    FileItemInfoOffAddr_FirmPara_Q_PHS            = (FileItemInfoOffAddr_FirmPara_P_PHS             + FileItemInfoLen_FirmPara_P_PHS),
    FileItemInfoOffAddr_FirmPara_P_OS               = (FileItemInfoOffAddr_FirmPara_Q_PHS           + FileItemInfoLen_FirmPara_Q_PHS),
    FileItemInfoOffAddr_FirmPara_Q_OS               = (FileItemInfoOffAddr_FirmPara_P_OS              + FileItemInfoLen_FirmPara_P_OS),
    FileItemInfoOffAddr_FirmPara_P_PHSMH          = (FileItemInfoOffAddr_FirmPara_Q_OS            + FileItemInfoLen_FirmPara_Q_OS),
    FileItemInfoOffAddr_FirmPara_Q_PHSMH          = (FileItemInfoOffAddr_FirmPara_P_PHSMH       + FileItemInfoLen_FirmPara_P_PHSMH),
    FileItemInfoOffAddr_FirmPara_ChkSum1          = (FileItemInfoOffAddr_FirmPara_Q_PHSMH       + FileItemInfoLen_FirmPara_Q_PHSMH),
    FileItemInfoOffAddr_FirmPara_KUrms            = (FileItemInfoOffAddr_FirmPara_ChkSum1       + FileItemInfoLen_FirmPara_ChkSum1),
    FileItemInfoOffAddr_FirmPara_KIArms         = (FileItemInfoOffAddr_FirmPara_KUrms           + FileItemInfoLen_FirmPara_KUrms),
    FileItemInfoOffAddr_FirmPara_KPrms            = (FileItemInfoOffAddr_FirmPara_KIArms          + FileItemInfoLen_FirmPara_KIArms),
    FileItemInfoOffAddr_FirmPara_RatedU           = (FileItemInfoOffAddr_FirmPara_KPrms             + FileItemInfoLen_FirmPara_KPrms),
    FileItemInfoOffAddr_FirmPara_RatedUrms      = (FileItemInfoOffAddr_FirmPara_RatedU          + FileItemInfoLen_FirmPara_RatedU),
    FileItemInfoOffAddr_FirmPara_RatedI           = (FileItemInfoOffAddr_FirmPara_RatedUrms       + FileItemInfoLen_FirmPara_RatedUrms),
    FileItemInfoOffAddr_FirmPara_RatedIrms      = (FileItemInfoOffAddr_FirmPara_RatedI          + FileItemInfoLen_FirmPara_RatedI),
    FileItemInfoOffAddr_FirmPara_RealU              = (FileItemInfoOffAddr_FirmPara_RatedIrms     + FileItemInfoLen_FirmPara_RatedIrms),
    FileItemInfoOffAddr_FirmPara_RealI              = (FileItemInfoOffAddr_FirmPara_RealU             + FileItemInfoLen_FirmPara_RealU),
    FileItemInfoOffAddr_FirmPara_RealAngle      = (FileItemInfoOffAddr_FirmPara_RealI             + FileItemInfoLen_FirmPara_RealI),
    FileItemInfoOffAddr_FirmPara_RealPw           = (FileItemInfoOffAddr_FirmPara_RealAngle       + FileItemInfoLen_FirmPara_RealAngle),
    FileItemInfoOffAddr_FirmPara_Send_nPoint        = (FileItemInfoOffAddr_FirmPara_RealPw    + FileItemInfoLen_FirmPara_RealPw),
    FileItemInfoOffAddr_FirmPara_Crc        = (FileItemInfoOffAddr_FirmPara_Send_nPoint    + FileItemInfoLen_FirmPara_Send_nPoint),

    FileItemInfoOffAddr_VoltRepair_EnOrDis      = (FileItemInfoOffAddr_FirmPara_Crc    + FileItemInfoLen_FirmPara_Crc),
    FileItemInfoOffAddr_VoltRepair_Rep              = (FileItemInfoOffAddr_VoltRepair_EnOrDis     + FileItemInfoLen_VoltRepair_EnOrDis),
    FileItemInfoOffAddr_VoltRepair_Crc              = (FileItemInfoOffAddr_VoltRepair_Rep             + FileItemInfoLen_VoltRepair_Rep),

    FileItemInfoOffAddr_VoltRepair_RN8302TIRM   = (FileItemInfoOffAddr_VoltRepair_Crc +   FileItemInfoLen_VoltRepair_Crc),
    FileItemInfoOffAddr_VoltRepair_RN8207DTIRM  = (FileItemInfoOffAddr_VoltRepair_RN8302TIRM  +   FileItemInfoLen_VoltRepair_RN8302TIRM),

    FileItemInfoOffAddr_Harmonic_FftGP      = (FileItemInfoOffAddr_VoltRepair_RN8207DTIRM   + FileItemInfoLen_VoltRepair_RN8207DTIRM),
    FileItemInfoOffAddr_Harmonic_FftCosAngle    = (FileItemInfoOffAddr_Harmonic_FftGP   + FileItemInfoLen_Harmonic_FftGP),
    FileItemInfoOffAddr_Harmonic_Crc        = (FileItemInfoOffAddr_Harmonic_FftCosAngle     + FileItemInfoLen_Harmonic_FftCosAngle),

    FileItemInfoOffAddr_FirmPara_Reversd    = (FileItemInfoOffAddr_Harmonic_Crc   +   FileItemInfoLen_Harmonic_Crc),

    // dyf ���������������в���
    FileItemInfoOffAddr_Xiebo_Flag_EnOrDis  = (FileItemInfoOffAddr_FirmPara_Reversd + 200),
    FileItemInfoOffAddr_Xiebo_Err           = (FileItemInfoOffAddr_Xiebo_Flag_EnOrDis + FileItemInfoLen_Xiebo_Flag_EnOrDis),
    FileItemInfoOffAddr_Xiebo_Value         = (FileItemInfoOffAddr_Xiebo_Err + FileItemInfoLen_Xiebo_Err),
    FileItemInfoOffAddr_Xiebo_Mid_Current   = (FileItemInfoOffAddr_Xiebo_Value + FileItemInfoLen_Xiebo_Value),

    FileItemInfoOffAddr_FirmPara_End        = (FileItemInfoOffAddr_Xiebo_Mid_Current + FileItemInfoLen_Xiebo_Mid_Current),

    //------�ܳ���-----------
    FileItemInfoLen__FirmPara_TotalLen      = FileItemInfoOffAddr_FirmPara_End + 128 - 37   // dyfԤ��128-37byte
} eFileItemInfo_FirmPara_TypeDef;//У��������ɸ��ݼ���оƬ����?

typedef enum
{
    FileItemInfoLen_TemperSchoolPara_chan1  =   sizeof(sTemperSchoolParaItem_TypeDef),
    FileItemInfoLen_TemperSchoolPara_chan2  =   sizeof(sTemperSchoolParaItem_TypeDef),
    FileItemInfoLen_TemperSchoolPara_chan3  =   sizeof(sTemperSchoolParaItem_TypeDef),
    FileItemInfoLen_TemperSchoolPara_chan4  =   sizeof(sTemperSchoolParaItem_TypeDef),
    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_TemperSchoolPara_chan1  = (0),
    FileItemInfoOffAddr_TemperSchoolPara_chan2  = (FileItemInfoOffAddr_TemperSchoolPara_chan1  +   FileItemInfoLen_TemperSchoolPara_chan1),
    FileItemInfoOffAddr_TemperSchoolPara_chan3 = (FileItemInfoOffAddr_TemperSchoolPara_chan2 + FileItemInfoLen_TemperSchoolPara_chan2),
    FileItemInfoOffAddr_TemperSchoolPara_chan4 = (FileItemInfoOffAddr_TemperSchoolPara_chan3 + FileItemInfoLen_TemperSchoolPara_chan3),
    FileItemInfoOffAddr_TemperSchoolPara_End    = (FileItemInfoOffAddr_TemperSchoolPara_chan4      +   FileItemInfoLen_TemperSchoolPara_chan4),
} eFileItemInfo_TemperSchoolPara_TypeDef; //�¶�У׼����

typedef enum
{
    //���
    FileItemInfoLen_NvRam_FristPowOn    = (4),
    FileItemInfoLen_NvRam_pFile = (15),
    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_NvRam_FristPowOn    = (0),
    FileItemInfoOffAddr_NvRam_pFile     = (FileItemInfoOffAddr_NvRam_FristPowOn        +   FileItemInfoLen_NvRam_FristPowOn),
    FileItemInfoOffAddr_NvRam_End   = (FileItemInfoOffAddr_NvRam_pFile         +   FileItemInfoLen_NvRam_pFile)
} eFileItemInfo_NvRam_TypeDef;//�洢������������FM��AT��

typedef enum
{
    //���
    FileItemInfoLen_PowDn_PowDnTime     = (sizeof(sDate_time_s_TypeDef)),
    FileItemInfoLen_PowDn_EgPiece                 = (sizeof(sEgPiece_TypeDef)),
    FileItemInfoLen_PowDn_CheckMoneyFlag    = (1),
    FileItemInfoLen_PowDn_PownDnAllPEgSh    = (sizeof(u8) * (MAX_FL + 1)),
    FileItemInfoLen_PowDn_PownDnPtPEgSh = (sizeof(u8) * (MAX_FL + 1)),
    FileItemInfoLen_PowDn_PownDnNtPEgSh = (sizeof(u8) * (MAX_FL + 1)),
    FileItemInfoLen_PowDn_tWorkBat          =   4,
    FileItemInfoLen_PowDn_FrzDayTime        = (sizeof(sDate_time_s_TypeDef)),
    FileItemInfoLen_PowDn_FrzRmDayTime      = (sizeof(sDate_time_s_TypeDef)),
    FileItemInfoLen_PowDn_Irms      =   12,   //����ȫʧѹʱABC�������
    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_PowDn_PowDnTime     = (0),
    FileItemInfoOffAddr_PowDn_EgPiece   = (FileItemInfoOffAddr_PowDn_PowDnTime         +   FileItemInfoLen_PowDn_PowDnTime),
    FileItemInfoOffAddr_PowDn_PownDnAllPEgSh    = (FileItemInfoOffAddr_PowDn_EgPiece       +   FileItemInfoLen_PowDn_EgPiece),
    FileItemInfoOffAddr_PowDn_PownDnPtPEgSh     = (FileItemInfoOffAddr_PowDn_PownDnAllPEgSh        +   FileItemInfoLen_PowDn_PownDnAllPEgSh),
    FileItemInfoOffAddr_PowDn_PownDnNtPEgSh     = (FileItemInfoOffAddr_PowDn_PownDnPtPEgSh         +   FileItemInfoLen_PowDn_PownDnPtPEgSh),
    FileItemInfoOffAddr_PowDn_CheckMoneyFlag    = (FileItemInfoOffAddr_PowDn_PownDnNtPEgSh + FileItemInfoLen_PowDn_PownDnNtPEgSh),
    FileItemInfoOffAddr_PowDn_tWorkBat      = (FileItemInfoOffAddr_PowDn_CheckMoneyFlag        +   FileItemInfoLen_PowDn_CheckMoneyFlag),
    FileItemInfoOffAddr_PowDn_FrzDayTime    = (FileItemInfoOffAddr_PowDn_tWorkBat      +   FileItemInfoLen_PowDn_tWorkBat),
    FileItemInfoOffAddr_PowDn_FrzRmDayTime = (FileItemInfoOffAddr_PowDn_FrzDayTime        +   FileItemInfoLen_PowDn_FrzDayTime),
    FileItemInfoOffAddr_PowDn_Irms  = (FileItemInfoOffAddr_PowDn_FrzRmDayTime      +   FileItemInfoLen_PowDn_FrzRmDayTime),
    FileItemInfoOffAddr_PowDn_End   = (FileItemInfoOffAddr_PowDn_Irms      +   FileItemInfoLen_PowDn_Irms)
} eFileItemInfo_PowDn_TypeDef;//�������ݴ洢����

typedef enum
{
    //���

    FileItemInfoLen_BackUpCurMoney_CurSurplusMoney  = sizeof(sDF12),
    FileItemInfoLen_BackUpCurMoney_CurOverdraftMoney    = sizeof(sDF12),
    FileItemInfoLen_BackUpCurMoney_CurApplyEg           = sizeof(sFsEgSh_TypeDef),
    FileItemInfoLen_BackUpCurMoney_Rmday1ApplyEg        = sizeof(sFsEgSh_TypeDef),
    FileItemInfoLen_BackUpCurMoney_CurSurplusMoneyCrc   = sizeof(u16),
    FileItemInfoLen_BackUpCurMoney_CurApplyEgCrc        = sizeof(u16),
    FileItemInfoLen_BackUpCurMoney_OpCode               = 4,

    FileItemInfoLen_BackUpCurMoney_DateTime                 = (sizeof(sDate_time_s_TypeDef)),     //����ģ����ʵ��ܱ���ʱ��
    FileItemInfoLen_BackUpCurMoney_PtPEgSh              = (sizeof(sBackUpEnergy_TypeDef)),     //����ģ����ʵ�������Ԥ��12�����ʿռ�
    FileItemInfoLen_BackUpCurMoney_NtPEgSh              = (sizeof(sBackUpEnergy_TypeDef)),     //����ģ����ʵ��ܷ���Ԥ��12�����ʿռ�
    FileItemInfoLen_BackUpCurMoney_Qd1QEgSh             = (sizeof(sBackUpEnergy_TypeDef)),     //����ģ����ʵ���Q1��Ԥ��12�����ʿռ�
    FileItemInfoLen_BackUpCurMoney_Qd2QEgSh             = (sizeof(sBackUpEnergy_TypeDef)),     //����ģ����ʵ���Q2��Ԥ��12�����ʿռ�
    FileItemInfoLen_BackUpCurMoney_Qd3QEgSh             = (sizeof(sBackUpEnergy_TypeDef)),     //����ģ����ʵ���Q3��Ԥ��12�����ʿռ�
    FileItemInfoLen_BackUpCurMoney_Qd4QEgSh             = (sizeof(sBackUpEnergy_TypeDef)),     //����ģ����ʵ���Q4��Ԥ��12�����ʿռ�

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_BackUpCurMoney_CurSurplusMoney  =   0,
    FileItemInfoOffAddr_BackUpCurMoney_CurOverdraftMoney = (FileItemInfoOffAddr_BackUpCurMoney_CurSurplusMoney   +   FileItemInfoLen_BackUpCurMoney_CurSurplusMoney),
    FileItemInfoOffAddr_BackUpCurMoney_CurApplyEg           = (FileItemInfoOffAddr_BackUpCurMoney_CurOverdraftMoney   +   FileItemInfoLen_BackUpCurMoney_CurOverdraftMoney),
    FileItemInfoOffAddr_BackUpCurMoney_Rmday1ApplyEg        = (FileItemInfoOffAddr_BackUpCurMoney_CurApplyEg  +   FileItemInfoLen_BackUpCurMoney_CurApplyEg),
    FileItemInfoOffAddr_BackUpCurMoney_CurSurplusMoneyCrc   = (FileItemInfoOffAddr_BackUpCurMoney_Rmday1ApplyEg   +   FileItemInfoLen_BackUpCurMoney_Rmday1ApplyEg),
    FileItemInfoOffAddr_BackUpCurMoney_CurApplyEgCrc        = (FileItemInfoOffAddr_BackUpCurMoney_CurSurplusMoneyCrc  +   FileItemInfoLen_BackUpCurMoney_CurSurplusMoneyCrc),
    FileItemInfoOffAddr_BackUpCurMoney_OpCode               = (FileItemInfoOffAddr_BackUpCurMoney_CurApplyEgCrc       +   FileItemInfoLen_BackUpCurMoney_CurApplyEgCrc),

    FileItemInfoOffAddr_BackUpCurMoney_DateTime                 = (FileItemInfoOffAddr_BackUpCurMoney_OpCode      +   FileItemInfoLen_BackUpCurMoney_OpCode),
    FileItemInfoOffAddr_BackUpCurMoney_PtPEgSh              = (FileItemInfoOffAddr_BackUpCurMoney_DateTime        +   FileItemInfoLen_BackUpCurMoney_DateTime),
    FileItemInfoOffAddr_BackUpCurMoney_NtPEgSh              = (FileItemInfoOffAddr_BackUpCurMoney_PtPEgSh         +   FileItemInfoLen_BackUpCurMoney_PtPEgSh),
    FileItemInfoOffAddr_BackUpCurMoney_Qd1QEgSh                 = (FileItemInfoOffAddr_BackUpCurMoney_NtPEgSh         +   FileItemInfoLen_BackUpCurMoney_NtPEgSh),
    FileItemInfoOffAddr_BackUpCurMoney_Qd2QEgSh                 = (FileItemInfoOffAddr_BackUpCurMoney_Qd1QEgSh        +   FileItemInfoLen_BackUpCurMoney_Qd1QEgSh),
    FileItemInfoOffAddr_BackUpCurMoney_Qd3QEgSh                 = (FileItemInfoOffAddr_BackUpCurMoney_Qd2QEgSh        +   FileItemInfoLen_BackUpCurMoney_Qd2QEgSh),
    FileItemInfoOffAddr_BackUpCurMoney_Qd4QEgSh                 = (FileItemInfoOffAddr_BackUpCurMoney_Qd3QEgSh        +   FileItemInfoLen_BackUpCurMoney_Qd3QEgSh),

    FileItemInfoOffAddr_BackUpCurMoney_End              = (FileItemInfoOffAddr_BackUpCurMoney_Qd4QEgSh        +   FileItemInfoLen_BackUpCurMoney_Qd4QEgSh)
} eFileItemInfo_BackUpCurMoney_TypeDef;//���ܼ�ʣ������ļ�

typedef enum
{
    //���
    FileItemInfoLen_Stat_UaElig_Day     = (sizeof(sUEligStat_TypeDef)),
    FileItemInfoLen_Stat_UbElig_Day     = (sizeof(sUEligStat_TypeDef)),
    FileItemInfoLen_Stat_UcElig_Day     = (sizeof(sUEligStat_TypeDef)),
    FileItemInfoLen_Stat_UaElig_Month   = (sizeof(sUEligStat_TypeDef)),
    FileItemInfoLen_Stat_UbElig_Month   = (sizeof(sUEligStat_TypeDef)),
    FileItemInfoLen_Stat_UcElig_Month   = (sizeof(sUEligStat_TypeDef)),
    FileItemInfoLen_Stat_Misc   = (sizeof(sMiscStat_TypeDef)),

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_Stat_UaElig_Day     = (0),
    FileItemInfoOffAddr_Stat_UbElig_Day     = (FileItemInfoOffAddr_Stat_UaElig_Day     +   FileItemInfoLen_Stat_UaElig_Day),
    FileItemInfoOffAddr_Stat_UcElig_Day     = (FileItemInfoOffAddr_Stat_UbElig_Day     +   FileItemInfoLen_Stat_UbElig_Day),
    FileItemInfoOffAddr_Stat_UaElig_Month   = (FileItemInfoOffAddr_Stat_UcElig_Day     +   FileItemInfoLen_Stat_UcElig_Day),
    FileItemInfoOffAddr_Stat_UbElig_Month   = (FileItemInfoOffAddr_Stat_UaElig_Month   +   FileItemInfoLen_Stat_UaElig_Month),
    FileItemInfoOffAddr_Stat_UcElig_Month   = (FileItemInfoOffAddr_Stat_UbElig_Month   +   FileItemInfoLen_Stat_UbElig_Month),
    FileItemInfoOffAddr_Stat_Misc       = (FileItemInfoOffAddr_Stat_UcElig_Month   +   FileItemInfoLen_Stat_UcElig_Month),

    FileItemInfoOffAddr_Stat_End        = (FileItemInfoOffAddr_Stat_Misc   +   FileItemInfoLen_Stat_Misc)
} eFileItemInfo_Stat_TypeDef; //��ѹ�ϸ���ͳ���¼���Ϣ�ļ�

typedef enum
{
    //���     �����������Ա����(1byte) + һ���¼���¼����(2byte) + N��������������( Ĭ��֧��OAD�ռ� + Ԥ��OAD�ռ�)
    FileItemInfoLen_EvtCtxlist_PowDn              =  sizeof(sCList5_TypeDef)        + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_Clr                =  sizeof(sCList24_TypeDef)     + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_SetClock       =  sizeof(sCList5_TypeDef)        + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_OpenCover        =    sizeof(sCList12_TypeDef)     + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_OpenTail         =    sizeof(sCList12_TypeDef)     + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_PrgSetPsw            =    sizeof(sCList5_TypeDef)    + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_BroadcastTime    =    sizeof(sCList5_TypeDef)    + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_MngPlug      =    sizeof(sCList14_TypeDef)     + 5 * sizeof(sContextList_TypeDef),
    FileItemInfoLen_EvtCtxlist_MngUpdate        =    sizeof(sCList8_TypeDef)      + 5 * sizeof(sContextList_TypeDef),

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_EvtCtxlist_PowDn             = (0),
    FileItemInfoOffAddr_EvtCtxlist_Clr               = (FileItemInfoOffAddr_EvtCtxlist_PowDn                + FileItemInfoLen_EvtCtxlist_PowDn),
    FileItemInfoOffAddr_EvtCtxlist_SetClock      = (FileItemInfoOffAddr_EvtCtxlist_Clr          + FileItemInfoLen_EvtCtxlist_Clr),
    FileItemInfoOffAddr_EvtCtxlist_OpenCover       = (FileItemInfoOffAddr_EvtCtxlist_SetClock       + FileItemInfoLen_EvtCtxlist_SetClock),
    FileItemInfoOffAddr_EvtCtxlist_OpenTail        = (FileItemInfoOffAddr_EvtCtxlist_OpenCover      + FileItemInfoLen_EvtCtxlist_OpenCover),
    FileItemInfoOffAddr_EvtCtxlist_PrgSetPsw         = (FileItemInfoOffAddr_EvtCtxlist_OpenTail + FileItemInfoLen_EvtCtxlist_OpenTail),
    FileItemInfoOffAddr_EvtCtxlist_BroadcastTime = (FileItemInfoOffAddr_EvtCtxlist_PrgSetPsw            + FileItemInfoLen_EvtCtxlist_PrgSetPsw),
    FileItemInfoOffAddr_EvtCtxlist_MngPlug = (FileItemInfoOffAddr_EvtCtxlist_BroadcastTime            + FileItemInfoLen_EvtCtxlist_BroadcastTime),
    FileItemInfoOffAddr_EvtCtxlist_MngUpdate = (FileItemInfoOffAddr_EvtCtxlist_MngPlug              + FileItemInfoLen_EvtCtxlist_MngPlug),
    FileItemInfoOffAddr_EvtCtxlist_end             = (FileItemInfoOffAddr_EvtCtxlist_MngUpdate              + FileItemInfoLen_EvtCtxlist_MngUpdate),
    //------�ܳ���-----------
    FileItemInfoLen_EvtCtxlist_TotalLen            = FileItemInfoOffAddr_EvtCtxlist_end
} eFileItemInfo_EvtCtxlist_TypeDef; //�¼���¼�����������Ա�

typedef enum
{
    FileItemInfoLen_EvtCfgPara_PowDn             =  sizeof(sEvtCfgPara_TimeDly_TypeDef),
    FileItemInfoLen_EvtCfgPara_Clr               =  0,
    FileItemInfoLen_EvtCfgPara_SetClock      =  0,
    FileItemInfoLen_EvtCfgPara_OpenCover       =  0,
    FileItemInfoLen_EvtCfgPara_OpenTail        =  0,
    FileItemInfoLen_EvtCfgPara_PrgSetPsw         =  0,
    FileItemInfoLen_EvtCfgPara_BroadcastTime = 0,
    FileItemInfoLen_EvtCfgPara_MngPlug = 0,
    FileItemInfoLen_EvtCfgPara_MngUpdate = 0,
    FileItemInfoLen_EvtCfgPara_Crc                 = 2,

    //��ƫ�Ƶ�ַ

    FileItemInfoOffAddr_EvtCfgPara_PowDn           = (0),
    FileItemInfoOffAddr_EvtCfgPara_Clr               = (FileItemInfoOffAddr_EvtCfgPara_PowDn                + FileItemInfoLen_EvtCfgPara_PowDn),
    FileItemInfoOffAddr_EvtCfgPara_SetClock      = (FileItemInfoOffAddr_EvtCfgPara_Clr          + FileItemInfoLen_EvtCfgPara_Clr),
    FileItemInfoOffAddr_EvtCfgPara_OpenCover       = (FileItemInfoOffAddr_EvtCfgPara_SetClock       + FileItemInfoLen_EvtCfgPara_SetClock),
    FileItemInfoOffAddr_EvtCfgPara_OpenTail        = (FileItemInfoOffAddr_EvtCfgPara_OpenCover      + FileItemInfoLen_EvtCfgPara_OpenCover),
    FileItemInfoOffAddr_EvtCfgPara_PrgSetPsw         = (FileItemInfoOffAddr_EvtCfgPara_OpenTail + FileItemInfoLen_EvtCfgPara_OpenTail),
    FileItemInfoOffAddr_EvtCfgPara_BroadcastTime = (FileItemInfoOffAddr_EvtCfgPara_PrgSetPsw            + FileItemInfoLen_EvtCfgPara_PrgSetPsw),
    FileItemInfoOffAddr_EvtCfgPara_MngPlug = (FileItemInfoOffAddr_EvtCfgPara_BroadcastTime            + FileItemInfoLen_EvtCfgPara_BroadcastTime),
    FileItemInfoOffAddr_EvtCfgPara_MngUpdate = (FileItemInfoOffAddr_EvtCfgPara_MngPlug              + FileItemInfoLen_EvtCfgPara_MngPlug),
    FileItemInfoOffAddr_EvtCfgPara_Crc             = (FileItemInfoOffAddr_EvtCfgPara_MngUpdate              + FileItemInfoLen_EvtCfgPara_MngUpdate),
    FileItemInfoOffAddr_EvtCfgPara_end             = (FileItemInfoOffAddr_EvtCfgPara_Crc              + FileItemInfoLen_EvtCfgPara_Crc)
} eFileItemInfo_EvtCfgPara_TypeDef; //�¼����ò���

typedef enum
{
    //���

    FileItemInfoLen_EvtRcdHead_PowDn                = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_Clr                  = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_SetClock         = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_OpenCover      = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_OpenTail      = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_PrgSetPsw          = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_BroadcastTime  = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_MngPlug  = sizeof(sEvtRcdHead_TypeDef),
    FileItemInfoLen_EvtRcdHead_MngUpdate  = sizeof(sEvtRcdHead_TypeDef),

    //��ƫ�Ƶ�ַ

    FileItemInfoOffAddr_EvtRcdHead_PowDn           = (0),
    FileItemInfoOffAddr_EvtRcdHead_Clr                 = (FileItemInfoOffAddr_EvtRcdHead_PowDn      + FileItemInfoLen_EvtRcdHead_PowDn),
    FileItemInfoOffAddr_EvtRcdHead_SetClock        = (FileItemInfoOffAddr_EvtRcdHead_Clr        + FileItemInfoLen_EvtRcdHead_Clr),
    FileItemInfoOffAddr_EvtRcdHead_OpenCover       = (FileItemInfoOffAddr_EvtRcdHead_SetClock       + FileItemInfoLen_EvtRcdHead_SetClock),
    FileItemInfoOffAddr_EvtRcdHead_OpenTail       = (FileItemInfoOffAddr_EvtRcdHead_OpenCover       + FileItemInfoLen_EvtRcdHead_OpenCover),
    FileItemInfoOffAddr_EvtRcdHead_PrgSetPsw         = (FileItemInfoOffAddr_EvtRcdHead_OpenTail + FileItemInfoLen_EvtRcdHead_OpenTail),
    FileItemInfoOffAddr_EvtRcdHead_BroadcastTime   = (FileItemInfoOffAddr_EvtRcdHead_PrgSetPsw      + FileItemInfoLen_EvtRcdHead_PrgSetPsw),
    FileItemInfoOffAddr_EvtRcdHead_MngPlug   = (FileItemInfoOffAddr_EvtRcdHead_BroadcastTime        + FileItemInfoLen_EvtRcdHead_BroadcastTime),
    FileItemInfoOffAddr_EvtRcdHead_MngUpdate   = (FileItemInfoOffAddr_EvtRcdHead_MngPlug        + FileItemInfoLen_EvtRcdHead_MngPlug),
    FileItemInfoOffAddr_EvtRcdHead_end             = (FileItemInfoOffAddr_EvtRcdHead_MngUpdate      + FileItemInfoLen_EvtRcdHead_MngUpdate),

    FileItemInfoLen_EvtRcdHead_TotalLen                      = FileItemInfoOffAddr_EvtRcdHead_end
} eFileItemInfo_EvtRcdHead_TypeDef;  //�¼���¼ͷ�ļ�

//----------�¼���¼ �����¼���¼����----------------------
#define  CLIST_OverCur_RCDLEN    52  // =���һ��OADƫ�Ƶ�ַ + OAD���ݳ���
#define  CLIST2_RCDLEN    26
#define  CLISTZone_RCDLEN    64
#define  CLISTWeek_RCDLEN    19
#define  CLISTPrgP_RCDLEN    19
#define  CLISTPrgQ_RCDLEN    21
#define  CLISTDay_RCDLEN    24
#define  CLISTSetPsw_RCDLEN  34
#define  CLIST4_RCDLEN    34
#define  CLIST5_RCDLEN    42
#define  CLISTNERR_RCDLEN    26

#define  CLISTPrg_RCDLEN  74
#define  CLISTPrgTab_RCDLEN  22 + 42
#define  CLISTPrgHldy_RCDLEN  28

#define  CLISTRate_RCDLEN    50
#define  CLISTLad_RCDLEN    138
#define  CLISTCardErr_RCDLEN  34
#define  CLISTBuy_RCDLEN   42
#define  CLISTRtrn_RCDLEN  30
#define  CLISTGateOff_RCDLEN    42

#define  CLIST0_RCDLEN    18 + 8  //Ԥ��2��4byte�����ռ�

#define  MAX_RCDLEN     2*CLISTLad_RCDLEN   //�����¼���¼����󳤶�

#define     Evt_PowDn_RCDLen        26
#define     Evt_Clr_RCDLen          114             // ThreePhase---114   singnlPhase---42
#define     Evt_SetClock_RCDLen     26
#define     Evt_OpenCover_RCDLen    66
#define     Evt_OpenTail_RCDLen     50
#define     Evt_PrgSetPsw_RCDLen    34
#define     Evt_BroadcastTime_RCDLen    26
#define     Evt_MngPlug_RCDLen      84
#define     Evt_MngUpdate_RCDLen    220//124

typedef enum
{
    //���
    FileItemInfoLen_EvtRecord_PowDn             =   4096 * 2,       //Ԥ��2��bank��ȷ������һ��bank������������¼����
    FileItemInfoLen_EvtRecord_Clr             = 4096 * 2,
    FileItemInfoLen_EvtRecord_SetClock        = 4096 * 2,
    FileItemInfoLen_EvtRecord_OpenCover     =   4096 * 2,
    FileItemInfoLen_EvtRecord_OpenTail     =    4096 * 2,
    FileItemInfoLen_EvtRecord_PrgSetPsw       = 4096 * 2,
    FileItemInfoLen_EvtRecord_BroadcastTime =   4096 * 2,
    FileItemInfoLen_EvtRecord_MngPlug     = 4096 * 2,
    FileItemInfoLen_EvtRecord_MngUpdate       = 4096 * 2,

    //��ƫ�Ƶ�ַ

    FileItemInfoOffAddr_EvtRecord_PowDn         = (0),
    FileItemInfoOffAddr_EvtRecord_Clr           = (FileItemInfoOffAddr_EvtRecord_PowDn   + FileItemInfoLen_EvtRecord_PowDn),
    FileItemInfoOffAddr_EvtRecord_SetClock      = (FileItemInfoOffAddr_EvtRecord_Clr      + FileItemInfoLen_EvtRecord_Clr),
    FileItemInfoOffAddr_EvtRecord_OpenCover     = (FileItemInfoOffAddr_EvtRecord_SetClock       + FileItemInfoLen_EvtRecord_SetClock),
    FileItemInfoOffAddr_EvtRecord_OpenTail     = (FileItemInfoOffAddr_EvtRecord_OpenCover       + FileItemInfoLen_EvtRecord_OpenCover),
    FileItemInfoOffAddr_EvtRecord_PrgSetPsw       = (FileItemInfoOffAddr_EvtRecord_OpenTail + FileItemInfoLen_EvtRecord_OpenTail),
    FileItemInfoOffAddr_EvtRecord_BroadcastTime = (FileItemInfoOffAddr_EvtRecord_PrgSetPsw        + FileItemInfoLen_EvtRecord_PrgSetPsw),
    FileItemInfoOffAddr_EvtRecord_MngPlug = (FileItemInfoOffAddr_EvtRecord_BroadcastTime        + FileItemInfoLen_EvtRecord_BroadcastTime),
    FileItemInfoOffAddr_EvtRecord_MngUpdate = (FileItemInfoOffAddr_EvtRecord_MngPlug      + FileItemInfoLen_EvtRecord_MngPlug),
    FileItemInfoOffAddr_EvtRecord_end               = (FileItemInfoOffAddr_EvtRecord_MngUpdate      + FileItemInfoLen_EvtRecord_MngUpdate),

    FileItemInfoLen_EvtRecord_TotalLen  =   FileItemInfoOffAddr_EvtRecord_end
} eFileItemInfo_EvtRecord_TypeDef;  //�¼���¼

#define    MAX_PowDnEvt_FlashCnt    (FileItemInfoLen_EvtRecord_PowDn/Evt_PowDn_RCDLen)
#define    MAX_ClrEvt_FlashCnt          (FileItemInfoLen_EvtRecord_Clr/Evt_Clr_RCDLen)
#define    MAX_SetClockEvt_FlashCnt (FileItemInfoLen_EvtRecord_SetClock/Evt_SetClock_RCDLen)
#define    MAX_OpenCoverEvt_FlashCnt    (FileItemInfoLen_EvtRecord_OpenCover/Evt_OpenCover_RCDLen)
#define    MAX_OpenTailEvt_FlashCnt (FileItemInfoLen_EvtRecord_OpenTail/Evt_OpenTail_RCDLen)
#define    MAX_PrgSetPswEvt_FlashCnt    (FileItemInfoLen_EvtRecord_PrgSetPsw/Evt_PrgSetPsw_RCDLen)
#define    MAX_BroadcastTimeEvt_FlashCnt    (FileItemInfoLen_EvtRecord_BroadcastTime/Evt_BroadcastTime_RCDLen)
#define    MAX_MngPlugEvt_FlashCnt  (FileItemInfoLen_EvtRecord_MngPlug/Evt_MngPlug_RCDLen)
#define    MAX_MngUpdateEvt_FlashCnt    (FileItemInfoLen_EvtRecord_MngUpdate/Evt_MngUpdate_RCDLen)

//--------����---------------
typedef enum
{
    FileItemInfoNum_Frz_MinFrz            = 0,      //���Ӷ���
    FileItemInfoNum_Frz_MAX =   1,
} eFileItemInfoNum_Frz_TypeDef;   //

typedef enum
{
    //���     �����������Ա����(1byte) + һ���¼���¼����(2byte) + N��������������( Ĭ��֧��OAD�ռ� + Ԥ��OAD�ռ�)
    FileItemInfoLen_FrzCtxlist_Min       =   sizeof(sFrzMinList_TypeDef) + 5 * sizeof(sFrzCtxList_TypeDef),
    //��ƫ�Ƶ�ַ

    FileItemInfoOffAddr_FrzCtxlist_Min       = (0),
    FileItemInfoOffAddr_FrzCtxlist_end       = (FileItemInfoOffAddr_FrzCtxlist_Min       +  FileItemInfoLen_FrzCtxlist_Min),
    //------�ܳ���-----------
    FileItemInfoLen_FrzCtxlist_TotalLen     = FileItemInfoOffAddr_FrzCtxlist_end
} eFileItemInfo_FrzCtxlist_TypeDef;

typedef enum
{
    //���
    FileItemInfoLen_FrzRcdHead_Min       =   sizeof(sFrzRcdHead_TypeDef),
    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_FrzRcdHead_Min       = (0),
    FileItemInfoOffAddr_FrzRcdHead_end       = (FileItemInfoOffAddr_FrzRcdHead_Min       +  FileItemInfoLen_FrzRcdHead_Min),
    //------�ܳ���-----------
    FileItemInfoLen_FrzRcdHead_TotalLen     = FileItemInfoOffAddr_FrzRcdHead_end
} eFileItemInfo_FrzRcdHead_TypeDef;

typedef enum
{
    //���
    FileItemInfoLen_FrzMinLine0Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine1Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine2Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine3Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine4Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine5Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine6Head = sizeof(sFrzMinHead_TypeDef),
    FileItemInfoLen_FrzMinLine7Head = sizeof(sFrzMinHead_TypeDef),

    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_FrzMinLine0Head    = (0),
    FileItemInfoOffAddr_FrzMinLine1Head    = (FileItemInfoOffAddr_FrzMinLine0Head  +  FileItemInfoLen_FrzMinLine0Head),
    FileItemInfoOffAddr_FrzMinLine2Head    = (FileItemInfoOffAddr_FrzMinLine1Head  +  FileItemInfoLen_FrzMinLine1Head),
    FileItemInfoOffAddr_FrzMinLine3Head    = (FileItemInfoOffAddr_FrzMinLine2Head  +  FileItemInfoLen_FrzMinLine2Head),
    FileItemInfoOffAddr_FrzMinLine4Head    = (FileItemInfoOffAddr_FrzMinLine3Head  +  FileItemInfoLen_FrzMinLine3Head),
    FileItemInfoOffAddr_FrzMinLine5Head    = (FileItemInfoOffAddr_FrzMinLine4Head  +  FileItemInfoLen_FrzMinLine4Head),
    FileItemInfoOffAddr_FrzMinLine6Head    = (FileItemInfoOffAddr_FrzMinLine5Head  +  FileItemInfoLen_FrzMinLine5Head),
    FileItemInfoOffAddr_FrzMinLine7Head    = (FileItemInfoOffAddr_FrzMinLine6Head  +  FileItemInfoLen_FrzMinLine6Head),
    FileItemInfoOffAddr_FrzMinLineHead_end = (FileItemInfoOffAddr_FrzMinLine7Head  +  FileItemInfoLen_FrzMinLine7Head),
    //------�ܳ���-----------
    FileItemInfoLen_FrzMinLineHead_TotalLen     = FileItemInfoOffAddr_FrzMinLineHead_end
} eFileItemInfo_FrzMinLineHead_TypeDef;

//---------��������������Ա�-----------------------
#define FRZSTDLISTLEN   11    //----=4+7------
//----------�����¼ Ԥ�������¼���¼��󳤶�----------------------
#define  FRZWINKRCDLEN              (FRZSTDLISTLEN+16*(DEFAULT_FL+1) + 8)  //
#define  FRZMINRCDLEN                   (FRZSTDLISTLEN*2+138)//
#define  FRZHOURRCDLEN                  (FRZSTDLISTLEN+ 16) //
#define  FRZDAYRCDLEN                   (FRZSTDLISTLEN+16*(MAX_FL+1) + 8) //
#define  FRZRMDAYRCDLEN             (FRZSTDLISTLEN+24*(MAX_FL+1) + 4)   //
#define  FRZMONTHRCDLEN             (FRZSTDLISTLEN+24*(MAX_FL+1))   //
#define  FRZLADDERRCDLEN            (FRZSTDLISTLEN + 4)  //15
#define  FRZTZONESWRCDLEN           (FRZSTDLISTLEN+16*(MAX_FL+1) + 8)   //
#define  FRZPOTSWRCDLEN             FRZTZONESWRCDLEN  //�����л�����Ĭ�ϳ��Ⱥ�Ĭ�Ϲ����������Ա���ȫһ��
#define  FRZRATEPRICESWRCDLEN   FRZTZONESWRCDLEN
#define  FRZLADDERSWRCDLEN      FRZTZONESWRCDLEN
#define  Len_FrzRecord_Min1        (((u32)(FRZSTDLISTLEN+ 74) * (u32)MAX_FRZMIN_RECORD1 + 4096 + 4096)&0xFFFFF000)  //ÿ������Ԥ��һ��bank��ȷ������һ��bank��Ӱ������¼����
#define  Len_FrzRecord_Min2        (((u32)(FRZSTDLISTLEN+ 64) * (u32)MAX_FRZMIN_RECORD2 + 4096 + 4096)&0xFFFFF000)

typedef enum
{
    //���     �����������Ա����(1byte) + һ���¼���¼����(2byte) + N��������������( Ĭ��֧��OAD�ռ� + Ԥ��OAD�ռ�)

    FileItemInfoLen_FrzRecord_Min       = (Len_FrzRecord_Min1 + Len_FrzRecord_Min2),
    //��ƫ�Ƶ�ַ
    FileItemInfoOffAddr_FrzRecord_Min       = (0),

    FileItemInfoOffAddr_FrzRecord_end       = (FileItemInfoOffAddr_FrzRecord_Min       +  FileItemInfoLen_FrzRecord_Min),
    //------�ܳ���-----------
    FileItemInfoLen_FrzRecord_TotalLen      = FileItemInfoOffAddr_FrzRecord_end
} eFileItemInfo_FrzRecord_TypeDef;
//===�����ļ���Ϣ==========================================
#define FRAM_SADDR  FM24C_START_ADDR

#define FLASH_SADDR AT45DB_START_ADDR

#define SocEE_SADDR SocEE_START_ADDR

#define AT1024_SADDR AT1024_START_ADDR

typedef enum
{
    //�ļ����
    FileId_NvRam        =   0,
    FileId_FirmPara =   1,
    FileId_TemperSchoolPara =   2,
    FileId_HighPara =   3,
    FileId_SecretPara   =   4,
    FileId_RatePara =   5,

    FileId_ParaDoc  =   6,
    FileId_ParaCom  =   7,
    FileId_ParaDisp =   8,
    FileId_ParaWaste    =   9,
    FileId_ParaOutput   =   10,
    FileId_ParaCipherKey    =   11,
    FileId_EvtReport    =   12,

    FileId_ParaASCII    =   13,
    FileId_HighState    =   14,

    FileId_EgSh     =   15,

    FileId_InterTmp =   16,
    FileId_CurStat  =   17,
    FileId_PowDnDataMemory = 18,
    FileId_BackUpEgSh = 19,
    FileId_BackUpCurMoney = 20,

    FileId_EvtCtxlist = 21,     //�¼���¼�����������Ա�
    FileId_EvtCfgPara = 22, //�¼���¼���ò���
    FileId_EvtRcdHead = 23,     //�¼���¼
    FileId_EvtRecord        =   24,     //�¼���¼

    FileId_FrzCtxlist = 25,     //
    FileId_FrzRcdHead = 26,     //
    FileId_FrzMinLineHead = 27,     //���Ӷ���(���8��)����ͷ��Ϣ
    FileId_FrzRecord        =   28,     //

    FileId_Max          =   29,

    //�ļ�����
    FileLen_NvRam   = (sizeof(sNvRamFile_TypeDef)),
    FileLen_FirmPara    = FileItemInfoLen__FirmPara_TotalLen,
    FileLen_TemperSchoolPara    = sizeof(sTemperSchoolPara_TypeDef),
    FileLen_HighPara    = (sizeof(sHighParaFile_TypeDef)),
    FileLen_SecretPara  = (sizeof(sSecretParaFile_TypeDef)),
    FileLen_RatePara    =   0,

    FileLen_ParaDoc     = (sizeof(sDocment_TypeDef)),
    FileLen_ParaCom     = (sizeof(sComPara_TypeDef)),
    FileLen_ParaDisp        = (sizeof(sDispPara_TypeDef)),
    FileLen_ParaWaste       = (sizeof(sWastePara_TypeDef)),
    FileLen_ParaOutput  = (sizeof(sOutputPara_TypeDef)),
    FileLen_ParaCipherKey   = (sizeof(sCipherKeyPara_TypeDef)),
    FileLen_EvtReport       = (sizeof(sEvtReport_TypeDef)),

    FileLen_ParaASCII       = (sizeof(sASCIIParaFile_TypeDef)),
    FileLen_HighState       =   FileItemInfoLen_HighState_TotalLen,

    FileLen_EgSh    =   FileItemInfoLen_EgSh_TotalLen,   //128*2  ҳ����

    FileLen_InterTmp    = (sizeof(sDl645InterTmpFile_TypeDef)),
    FileLen_CurStat = (sizeof(sStatFile_TypeDef)),
    FileLen_PowDnDataMemory = (sizeof(sPowDnFile_TypeDef)),
    FileLen_BackUpEgSh = FileItemInfoLen_EgSh_TotalLen,
    FileLen_BackUpCurMoney = (sizeof(sBackUpCurMoneyFile_TypeDef)),

    FileLen_EvtCtxlist  =   FileItemInfoLen_EvtCtxlist_TotalLen,
    FileLen_EvtCfgPara  = (sizeof(sTrim_TypeDef)),
    FileLen_EvtRcdHead  =   FileItemInfoLen_EvtRcdHead_TotalLen,
    FileLen_EvtRecord   =   FileItemInfoLen_EvtRecord_TotalLen,

    FileLen_FrzCtxlist  =   FileItemInfoLen_FrzCtxlist_TotalLen,
    FileLen_FrzRcdHead  =   FileItemInfoLen_FrzRcdHead_TotalLen,
    FileLen_FrzMinLineHead  =   FileItemInfoLen_FrzMinLineHead_TotalLen,
    FileLen_FrzRecord   =   FileItemInfoLen_FrzRecord_TotalLen,

    //�ļ���ʼ��ַ
    //����ö������ֵ�����ƣ������ļ���ʼ��ַ��#define����
} eFileInfo_TypeDef;

//----FRAM_ADDR ����----
//���������洢��ַ����
#define FileAddr_FRAM_Start     (   FRAM_SADDR      )

#define FileAddr_FirmPara           (   FileAddr_FRAM_Start )
#define FileAddr_TemperSchoolPara   (   FileAddr_FirmPara           +   FileLen_FirmPara )
#define FileAddr_NvRam              (   FileAddr_TemperSchoolPara           +   FileLen_TemperSchoolPara        )
#define FileAddr_EgSh           (   (FileAddr_NvRam +   FileLen_NvRam + 63)/64*64 )  //ҳ���룬�������дE2ʱ��ҳ

#define FileAddr_InterTmp           (   FileAddr_EgSh           +   FileLen_EgSh    )
#define FileAddr_CurStat                (   FileAddr_InterTmp       +   FileLen_InterTmp    )
#define FileAddr_PowDnDataMemory    (   (FileAddr_CurStat + FileLen_CurStat + 63)/64*64 )
#define FileAddr_BackUpEgSh     (   (FileAddr_PowDnDataMemory +  FileLen_PowDnDataMemory    + 63)/64*64 ) //ҳ����
#define FileAddr_BackUpCurMoney     (   FileAddr_BackUpEgSh         +   FileLen_BackUpEgSh  )

#define FileAddr_HighPara           (   FileAddr_BackUpCurMoney     +   FileLen_BackUpCurMoney  )
#define FileAddr_SecretPara     (   FileAddr_HighPara           +   FileLen_HighPara    )
#define FileAddr_RatePara           (   FileAddr_SecretPara     +   FileLen_SecretPara )

#define FileAddr_ParaDoc        (   FileAddr_RatePara       +   FileLen_RatePara    )
#define FileAddr_ParaCom        (   FileAddr_ParaDoc        +   FileLen_ParaDoc )
#define FileAddr_ParaDisp       (   FileAddr_ParaCom        +   FileLen_ParaCom )
#define FileAddr_ParaWaste      (   FileAddr_ParaDisp       +   FileLen_ParaDisp    )
#define FileAddr_ParaOutput     (   FileAddr_ParaWaste      +   FileLen_ParaWaste   )
#define FileAddr_ParaCipherKey      (   FileAddr_ParaOutput         +   FileLen_ParaOutput  )
#define FileAddr_EvtReport      (   FileAddr_ParaCipherKey      +   FileLen_ParaCipherKey   )

#define FileAddr_ParaASCII      (   FileAddr_EvtReport      +   FileLen_EvtReport   )
#define FileAddr_HighState      (   FileAddr_ParaASCII      +   FileLen_ParaASCII   )

#define FileAddr_ParaEnd            (   FileAddr_HighState+ FileLen_HighState)
#define FileAddr_FRAM_End           (   FileAddr_ParaEnd    )

// SOC�ڲ�EEPROM ����
// #define  FileAddr_SocEE_Start    (   (u32)SocEE_SADDR    )
// #define  FileAddr_FirmPara       (   SocEE_SADDR )

//----------------------
#define FileAddr_EvtCtxlist (   FileAddr_ParaEnd        )
#define FileAddr_EvtCfgPara (   FileAddr_EvtCtxlist +   FileLen_EvtCtxlist  )
#define FileAddr_EvtRcdHead (   FileAddr_EvtCfgPara +   FileLen_EvtCfgPara  )

#define FileAddr_FrzCtxlist (   FileAddr_EvtRcdHead +   FileLen_EvtRcdHead  )
#define FileAddr_FrzRcdHead (   FileAddr_FrzCtxlist +   FileLen_FrzCtxlist  )
#define FileAddr_FrzMinLineHead (   FileAddr_FrzRcdHead +   FileLen_FrzRcdHead  )

#define FileAddr_SADDR_End      (   FileAddr_FrzMinLineHead +   FileLen_FrzMinLineHead  )

//--------------------------
#define FileAddr_FLASH_Start    (   (u32)FLASH_SADDR    )  //������¼���¼��flash

#define FileAddr_EvtRecord      (   FileAddr_FLASH_Start    )
#define FileAddr_FrzRecord      (   FileAddr_EvtRecord  + FileLen_EvtRecord )

#define FileAddr_FLASH_End      (   FileAddr_FrzRecord + FileItemInfoLen_FrzRecord_TotalLen )

typedef enum
{
    File_FirstInit      = 0x00,  //��¼�����,��һ�γ�ʼ��
    File_CommInit       = 0x01   //ͨѶ�����ʼ��������ʼ������������ͨѶ��ַ���ʲ��������
} eFileInitMode_TypeDef; //��ʼ����ʽ

typedef struct
{
    u32 OffAddr;
    u32 Len;
} sFileItemInfo_TypeDef;

typedef struct
{
    u32 StartAddr;
    u32 Len;
    const sFileItemInfo_TypeDef *pItemInfo; //�ļ�����Ϣ
} sFileInfo_TypeDef;

typedef struct
{
    u8  Item;
    u8   *Addr;
    u16 Len;
} sRecord_ParaDefault_TypeDef;
//------------------------
extern ErrorStatus fnFile_Read(u8 FileId, u32 OffAddr, void *Dst, u32 Len);
extern ErrorStatus fnFile_Write(u8 FileId, u32 OffAddr, void *Src, u32 Len);
extern ErrorStatus fnFile_Clr(u8 FileId);
extern ErrorStatus fnFileItem_Read(u8 FileId, u8 nItem, void *Dst);
extern ErrorStatus fnFileItem_Write(u8 FileId, u8 nItem, void *Src);

extern void fnFile_Init(u8 Flag);

extern const sFileInfo_TypeDef FileInfo[];
extern const sFileItemInfo_TypeDef FileItemInfo_EvtCtxlist[];
extern const sFileItemInfo_TypeDef FileItemInfo_EvtCfgPara[];
extern const sFileItemInfo_TypeDef FileItemInfo_EvtRcdHead[];
extern const sFileItemInfo_TypeDef FileItemInfo_EvtRecord[];
//extern const sHighParaFile_TypeDef HighParaDefault;
//extern const sASCIIParaFile_TypeDef ASCIIParaDefault;

extern const sFileItemInfo_TypeDef FileItemInfo_FrzCtxlist[];
extern const sFileItemInfo_TypeDef FileItemInfo_FrzRcdHead[];
extern const sFileItemInfo_TypeDef FileItemInfo_FrzRecord[];
extern const sFileItemInfo_TypeDef FileItemInfo_FrzMinLineHead[];
//extern const sTrim_TypeDef EvtCfgParaDefault;

#define StrMemOffset(StrName , Member) offsetof(StrName , Member)   //ʹ�� offsetof �����ɱ������������
#define StrMemOffset2(StrName1 , Member1 , StrMember1 , Member2)     (StrMemOffset(StrName1 , Member1) + StrMemOffset(StrMember1 , Member2) )
#define StrMemOffset3(StrName1 , Member1 , StrMember1 , Member2 , StrMember2 , Member3)  (StrMemOffset(StrName1 , Member1) + StrMemOffset(StrMember1 , Member2) + StrMemOffset(StrMember2 , Member3) )
#define StrMemOffset4(StrName1 , Member1 , StrMember1 , Member2 , StrMember2 , Member3 , StrMember3 , Member4)   (StrMemOffset(StrName1 , Member1) + StrMemOffset(StrMember1 , Member2) + StrMemOffset(StrMember2 , Member3) + StrMemOffset(StrMember3 , Member4) )
// �ṹ��Ա���ȼ���
#define StrMemSizeOf(StrName , Member) (sizeof( ( (StrName *)0)->Member) )  // ����ṹ���Ա��С
#define StrMemSizeOf2(StrName , Member1 , Member2) (sizeof( ( (StrName *)0)->Member1.Member2) )
#define StrMemSizeOf3(StrName , Member1 , Member2 , Member3) (sizeof( ( (StrName *)0)->Member1.Member2.Member3) )
#define StrMemSizeOf4(StrName , Member1 , Member2 , Member3 , Member4) (sizeof( ( (StrName *)0)->Member1.Member2.Member3.Member4) )

#endif // _DL645_FILE_H
