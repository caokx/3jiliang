
#define  _MISC_GLOBALS

#include <BSP.h>

//函数功能：计算时戳(每个定时器节拍，SysStamp累加一次)
//入口参数：Ago需要比较的节拍
//出口参数：返回SysStamp与Ago间的节拍数
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
