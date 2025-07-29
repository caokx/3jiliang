#ifndef _APP_RN7306_H
#define _APP_RN7306_H

//����
typedef struct _PARAMETER_STRUCT
{
    UINT8   xiebo_flag;                                 // ֱ��ż��г���������� 0x5A-�رգ�����-��
    UINT32  xiebo_err[2];                               // �貹�����ֵ,0-��ǰ����С��г���������ĵ����ʱ���ֵ������-�ڵ�ǰ�������ڵ���г���������ĵ����ʱ���ֵ
    UINT32  xiebo_value[2][3];                          // ֱ��ż��г��������Ĵ���ֵ,0-�����ڵ�ǰ����С��г���������ĵ����ʱ����������-�����ڵ�ǰ�������ڵ���г���������ĵ����ʱ����
    UINT32  xiebo_mid_current;                          // г���������ĵ���� xxx.xxx
    UINT32  xiebo_new_regsum;                           // �����������ۼӺ�
    //UINT8                                       halfimax_phs_flag;                           // 1/2 Imax�ǲ������ 0x5A-�򿪣�����-�ر�
    //UINT8                                       start_power_flag;                            // ������������ 0x5A-�򿪣�����-�ر�
} PARAMETER_STRUCT;

//���Ͻṹ����
typedef union _long_union
{
    UINT8                                       char_type[4];
    UINT32                                      long_type;
} long_union;

extern PARAMETER_STRUCT parameter; // ����

s8 check_rn7306_checksum(u32 ic_checksum);
extern INT8 check_rn7306_reg(void);

#endif // end _APP_RN7306_H
