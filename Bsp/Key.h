
#ifndef  _KEY_H
#define  _KEY_H

#ifdef   _KEY_GLOBALS
#define  KEY_EXT
#else
#define  KEY_EXT  extern
#endif

typedef enum
{
    KEY_VAL_PRG     = (1 << 0), //��̰���
    KEY_VAL_TURNA   = (1 << 1), //���԰�ť�̰�
    KEY_VAL_TURNAC  = (1 << 2), //���԰�������
    KEY_VAL_TURNB   = (1 << 3), //���԰�ť�̰�
    KEY_VAL_TURNBC  = (1 << 4), //���԰�ť����
    KEY_VAL_SHELLVS = (1 << 5), //����ǵ�ƽ״̬׷��
    KEY_VAL_SHELL   = (1 << 6), //����ǰ��������ж�
    KEY_VAL_JUNBOXVS = (1 << 7), //���ӿ��Ǽ�״̬׷��
    KEY_VAL_JUNBOX  = (1 << 8), //���ӿ��Ǽ��ж�
    KEY_VAL_CARD    = (1 << 9), //���طѿر�Ƭ�����ж�
    KEY_Relay_Ctrl  = (1 << 10), //�̵��������բ����
    KEY_VAL_STROMANVS = (1 << 11),         //�ų�Ӱ���¼�״̬׷��
    KEY_VAL_STROMAN = (1 << 12),         //�ų�Ӱ���¼��ж����λ
    KEY_VAL_RelayGataCheck = (1 << 13),  //�̵�������״̬���
    //  KEY_BJRelay_Ctrl= (1<<14),  // �ﵽ�������2�󰴼���բ
    KEY_VAL_CTRLMODUPLGCHKVS    = (1 << 14), //����ģ��β�״̬����
    KEY_VAL_CTRLMODUPLGCHK  = (1 << 15), //����ģ��β�
    KEY_PRESS       = (KEY_VAL_PRG + KEY_VAL_TURNA + KEY_VAL_TURNB + KEY_VAL_SHELL + KEY_VAL_JUNBOX + KEY_VAL_CARD + KEY_Relay_Ctrl + KEY_VAL_CTRLMODUPLGCHK),  //�����ж��Ƿ��м�����
    KEY_RELEASE     = (~KEY_PRESS)      //�����ж��Ƿ��м��ͷ�
} eKeyVal_TypeDef;

typedef struct
{
    u8      KeyProg_Scan;           //��̰�������ɨ����
    u8      KeyTurn_Scan1;          //���԰�������ɨ�����Ϸ���
    u8      KeyTurn_Scan2;          //���԰�������ɨ�����·���
    u8      KeyShell_Scan;          //����ǲ���ɨ������
    u8      KeyJUNBOX_Scan;         //�����Ӹǲ���ɨ����
    u8      KeyCARD_Scan;           //��Ƭ�����ɨ����
    u8      StrongMan_Scan;         //ǿ�ų�����ؼ��
    u16     Press;                  //�������£�ȥ��
    u16     Release;                //�����ͷ�
    u16     KeyTurn_Time1;          //�ֶ�����������ʱ�ж��Ϸ�����ʱ����
    u16     KeyTurn_Time2;          //�ֶ�����������ʱ�ж��·�����ʱ����
    u16     STROMAN_Time;           //ǿ�ż����ʱʱ��
    u8      RelayGataCheck;         //�̵������
    u8      CtrlModuPlgChk;         //����ģ��β�
    u16     MngPlgUpTmr;            //����ģ�����ʱʱ��
    u16     MngPlgDnTmr;            //����ģ�����ʱʱ��
} sKey_TypeDef;                     //KEY_TYPE;

KEY_EXT sKey_TypeDef Key;

//==============================================
extern void fnKey_Init(void);
extern void fnKey_Scan(void);

#endif  //_KEY_H
