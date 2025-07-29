#ifndef _OUTPUT_H
#define _OUTPUT_H

typedef enum
{
    OUTPUTPORT_RELAY            = 0x00,
    OUTPUTPORT_BJRELAY          = 0x01,
    OUTPUTPORT_OPTICAL          = 0x02,
    OUTPUTPORT_ALARMLED         = 0x03,
    OUTPUTPORT_BEEP             = 0x04,
    OUTPUTPORT_RELAYLED         = 0x05,
    OUTPUTPORT_NUM              = 0x06
} eOutput_Style_TypeDef;

typedef struct
{
    u16 nSignal;      //��¼��ǰ���ź�״̬  0001  0002 ��Ӧ����բ 0004 ��Ӧ�����̵��� 0010 ��Ӧʱ�����  0100 ��Ӧ������ 1000��Ӧ�������� 2000��Ӧ�̵�����
    u16 lSignal;      //��¼�ϴε��ź�״̬

    struct sOutputPubData_TypeDef
    {
        u8      RealErrFlag;  // �̵���״̬���󣬼��̵�������״̬��ʵ��״̬������
        u8      RealErrCount;// �̵������������������ֹ�����߶�һֱ��������բ
        u8      RealErrTime; // �̵����������ʱ��
        u8      OpGataAllow;    //�̵�����������ٽ��ѹ
        u8      SafeCurFlag;    // �������޲�Ϊ���־
        u32     GateOffRemainTime;          // ��բ��ʱʱ��

        u32     GataOffResumeTime;          // ��բ�Զ��ָ�ʱ��
        u8          nCheckGata;                 // �̵���״̬������
        u8      CheckGataSta;               // �̵���״̬���
        u8      CheckGataSysStamp;              // �̵��������ʱ
        u8      GataCommandDo;                  // �̵�������ִ�б�־
    } PubData;

    struct sOutputObject_TypeDef
    {
        u16 Style;    //Bit15��0�������1������� Bit14~0�����������ȣ���λms
        u16 Trigger;  //�������ʽ��
        u16 Stamp;    //���ʱ��ʱ���¼��ʱ��
    } Object[6];      //0�̵�����1��ź��2����ָʾ�ƣ�3������;

    struct sOutputPriPara_TypeDef
    {
        u16  RelaysOutAlarm[5];
        u16  LightAlarm[5];
        u16  SoundAlarm[5];
        u32 GataSafeCur;     //����բ������������
        u16 tSafeGata;
        u16  Crc;
    } PriPara;
} sOutput_TypeDef;

extern void fnOutput_Init(void);
extern void fnOutput_Exec(void);
extern void fnOutput_Reset(u8 Object);
extern void fnOutput_CheckGataSta(void);
extern void fnOutput_RelayPinCheck(void);
#endif
