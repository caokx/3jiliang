
#ifndef _POWER_UP_DOWN_H
#define _POWER_UP_DOWN_H

#ifdef   _POWER_UP_DOWN_GLOBALS
#define  POWER_UP_DOWN_EXT
#else
#define  POWER_UP_DOWN_EXT  extern
#endif

typedef enum
{
    BKGRD_ACTIVE_POWON          = 0x00, //--0=��������
    BKGRD_ACTIVE_POWDN          = 0x01, //--1=����
    BKGRD_ACTIVE_POWUP          = 0x02, //--2=�ϵ�ָ�
} eBkgrd_Flag_TypeDef;

typedef enum
{
    BKGRD_INACTIVE_NOACTION     = 0x00, //�������
    BKGRD_INACTIVE_SAVE         = 0x01, //�����������
    BKGRD_INACTIVE_LOWPOWER     = 0x02, //����
    BKGRD_INACTIVE_POWERONINIT  = 0x03  //�ϵ��ʼ��
} eBkgrd_InActive_TypeDef;

#define End_State           0x0
#define Start_State         0x1
#define Running_State       0x2
#define IRComRun_State      0x03

typedef  struct
{
    struct InactiveData_Type
    {
        u8      ActiveState;    //����ʱϵͳ�Ƿ񱻻��ѱ�־
        u8      ActiveInit;     //����ʱ�Ƿ񱻳�ʼ��
        u16     ActiveStamp;    //���߻���ʱ��
        u8      QLossVolTime;   // ͣ���ȫʧѹ���ʱ��
        u16     InactiveStamp;
        s32     PowerDnTimer;   //ͣ��ʱ�䣬����7���֧�ֺ��Ⳮ������
        u8      IrWakeupFlag;   // ���⻽�ѱ�־
        u32     IrWakeupStamp;  // ���⻽����ʱ
        u8      tCheckIR;       // ���⻽��ʱ�䣬5S����һ��
        u16     CheckIRStamp;   // ������չܻ����ж�
        u8      PowerErrFlag;   // ��Դ�쳣��־
        u16     BackupBat;      // �����ص�ѹ����
        u8      tCheckBat;      // ��ص�ѹ��⣬ÿ5S���1��
        u16     tCheckSysConf;      //ͣ��SysConfCheck ��ÿ30min���1��
    } PubData;
    struct Event_TYPE
    {
        u8  ExeFlag;
        u8  SleepFlag;
        u32 EventFlag;
        u8  OpenFlag;       // ���ǡ���ť�б���
        u8  fChange;        // 01 ��������  02 ���λ  04 ��Ǵ�  08 ��ť�� 10 ���⻽�Ѽ��
    } InactiveFlag;

    struct MngPlug_Type
    {
        u8  OldEsam[8];
        u8  NewEsam[8];
        u16 Sta;
        u32 LstEvtFlag;
        u8  RevEsam;
    } Mng;

    sEvtPwnCoverTailTypedef     EvtPwn;
} sInactive_TypeDef;

//---

extern void fnPowerUp_Check(void);
extern void fnPowerUp_AppInit(void);
extern void fnPowerDown_Check(void);
extern void fnPowerDown_Handle(void);
extern void fnPowerDown_Inactive(void);
extern void fnPowerDown_SetWakeOpIO(void);
extern void fnPowerDown_SleepWakeOpIO(void);
extern void fnPowerUp_RTCParaInit(void) ;

#endif
