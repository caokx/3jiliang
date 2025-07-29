
#define  _MISC_GLOBALS

#include <BSP.h>

//�������ܣ�����ʱ��(ÿ����ʱ�����ģ�SysStamp�ۼ�һ��)
//��ڲ�����Ago��Ҫ�ȽϵĽ���
//���ڲ���������SysStamp��Ago��Ľ�����
u16 fnStamp_Through(u16 Ago)
{
    extern u16  SysStamp;
    if (SysStamp >= Ago)
    {
        return (SysStamp - Ago);
    }
    else
    {
        return ((0xffff - Ago) + SysStamp);
    }
}

u8 fnStampThroughSecond(u8 Ago)
{
    extern    sDate_time_s_TypeDef    SysDatetimes;
    u8 Now = SysDatetimes.second;
    if (Now >= Ago)
    {
        return Now - Ago;
    }
    else
    {
        return (60 - Ago) + Now;
    }
}
