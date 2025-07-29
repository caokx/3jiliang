
#define  _DL645CLOCK_GLOBALS

#include <BSP.h>

//*********��ʱ���л����ⲿ���پ���ģʽ***********
void fnMainClock_Init(void)
{
    SysCtl_EnableWrite;
    #if(HOSC_PLL)
    //HOSC=14.7456
    SYSCTL->OSC_CTRL2 = 0x31;
    SysModeChg(3, 0);
    #else
    //PLL=14.7456 dyf 5��Ϊ7 29.49M
    SysModeChg(7, 0);
    #endif
    SYSCTL->OSC_CTRL1 &= 0xfffffffe;

    SysCtl_DisableWrite;
    SystemCoreClockUpdate();

    return;
}

//*******��ʱ���л���32768HZ�͹���ģʽ********
void fnSubClock_Init(void)
{
    SysModeChg(0, 0);
}

/*****************************************************************************
** Function name:fnRCClock_Init
**
** Description:����ģʽ��ʱ������Ƶ�� 1.8432M
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnRCClock_Init(void)
{
    //SysModeChg(1,0);
    SysModeChg(2, 2);
}

//*******��ȡ��ǰϵͳʱ��Ƶ��********
u32 fnMainClock_Get(void)
{
    u32  freq;
    switch ((SYSCTL->OSC_CTRL1 >> 8) & 0x7)
    {
        case 0:
            freq = 7372800;
            break;
        case 1:
            freq = 3686400;
            break;
        case 2:
            freq = 1843200;
            break;
        case 3:
            freq = 32768;
            break;
        case 4:
            //freq = 14745600;
            freq = 16384000;
            break;
        case 5:
            freq = 29491200;
            break;
        default:
            freq = 1843200;
            break;
    }
    if (SYSCTL->OSC_CTRL1 & 0x00000020)
    {
        freq = 1843200 - 224704;
    }
    return freq;
}
