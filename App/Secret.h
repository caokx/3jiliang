
#ifndef _SECRET_H
#define _SECRET_H

#ifdef   _SECRET_GLOBALS
#define  SECRET_EXT
#else
#define  SECRET_EXT  extern
#endif

#define PRGTime_AutoDec           TRUE   //  TRUE = ������Чʱ���Զ��ۼ�/  FALSE =  ������Чʱ�䲻�ۼ���������ֶ��˳�

typedef struct
{
    u32 tLinkDly[4];    //Ӧ�����ӳ�ʱʣ��ʱ�� ��λ:��
    u32 tESAMDly;       //ESAM�Ựʣ��ʱ�䡣��λ:��

    u32 tLink[4];       //Ӧ������Э�̳�ʱʱ�䵥λ:��
    u8  LinkChan;       //����Ӧ������ͨ����
    u8  Auth_object;        //Ӧ�����ӽ�����ȫ��֤����
} sLinkData_TypeDef;

typedef struct
{
    u8  nPswRetry[2];       //���Դ���          (hyg) HEX
    u16 tPswFailClose[2];   //������������������ʱ����λ������(hyg) HEX
    u16 tPrgKeyValid;       //��̿�������ʱ�䵹��ʱ����λ������(hyg) HEX
    u16 tPrgKeyLock;        //��̿��ر���ʱ�䵹��ʱ����λ������(hyg) HEX
    u8  RemoteValid;    //�����֤�Ƿ���Ч״̬
    u8  nMacErr;         //MAC�����
    sLinkData_TypeDef  Master;  //��վ
    sLinkData_TypeDef  Terminal;  //�ն�
    u16 tIRRequestDly;  // �����ģ���ն����󵹼�ʱ

    u32 tIRDly;         //����Զ����֤ʧЧʱ�䵹��ʱ����λ:��
    u32 tTerminalDly;      //�ն������֤ʣ��ʱ��
    u8  Chan;       //ͨ������,��ǰͨѶͨ����
    u8  CA;
    u8  NeedIdentityAuth;
} sSecret_TypeDef;

extern sSecret_TypeDef          Secret;

//-----------------------------------------------------
extern void fnSecret_Init(void);
extern ErrorStatus fnSecret_Verify(u8 LimitPA, u8 PA, u8 *Pn);
extern void fnSecret_Exec(void);
extern void fnICEsam_MacErrInc(ErrorStatus Err);
extern u8 fnConnect_Secret(u32 timeout_nego, u8 auth_object);
extern void fnConnect_SecretClr(void);
extern u8 fnConnectDis_SecretClr(void);

extern u8 fnGet_ConnSta(void);
extern void fnCHK_LinkDly(void);
extern void fnCHK_ESAMDly(void);
#endif // _DL645_SECRET_H
