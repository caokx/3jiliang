/*
*******************************************************************************
**  Include files
*******************************************************************************
*/

#include <Includes.h>

#define DEBUG_Cyctime_Stat                  0           // 主循环最大时间统计使能

#if DEBUG_Cyctime_Stat == 1
u32 cycle_timer = 0;
u32 cycle_max_timer = 0;
#endif

/*****************************************************************************
** Function name:   int32_t  main( void )
**
** Description:
******************************************************************************/
int32_t  main(void)
{
    __disable_irq(); //禁用所有中断，确保初始化过程不被中断打断
    SysConfCheck();
    fnSocRegCheck(true, 0, 0);
    SysConfCheck();
    SEGGER_RTT_Init();
    SEGGER_RTT_printf(0, "MCU Rester:%x\r\n", SYSCTL->SYS_RST);
    SEGGER_RTT_printf(0, "LibVersion is:%x\r\n", GetLibVersion());
    SEGGER_RTT_printf(0, "CodeVersion is:%x\r\n", GetCodeVersion());

    Bkgrd.PubData.Active = BKGRD_ACTIVE_POWDN;         //休眠
    Inactive.PubData.InactiveStamp = BKGRD_INACTIVE_LOWPOWER;   //掉电

    fnPowerOn_DrvieInit();
    fnPowerUp_Check();

    if (Inactive.PubData.InactiveStamp  == BKGRD_INACTIVE_POWERONINIT)
    {
        fnPowerUp_AppInit();
        //------上电恢复数据后置上电模式---------------
        Inactive.PubData.InactiveStamp = BKGRD_INACTIVE_NOACTION;
    }
    else
    {
        fnFm24c256_Init();
        fnPowerDown_Handle();
        Inactive.PubData.InactiveStamp = BKGRD_INACTIVE_NOACTION;
    }

    fnSocRegCheckAddAll();

    //GPIO->PA |= 0x800000; // P27 LVDOUT
    //GPIO->PA &= ~0x800000; // P27 LVDOUT
    //fnDelay2us();
    #if 0
    fnDelay2us();
    fnDelay2us();
    fnDelay2us();
    fnDelay2us();
    fnDelay2us();
    fnDelay2us();
    fnDelay2us();
    fnDelay2us();
    fnDelay2us();
    #endif
    //GPIO->PA |= 0x800000; // P27 LVDOUT
    //fnDelay2us();

    while (1)
    {
        #if DEBUG_Cyctime_Stat == 1
        cycle_timer = SysStamp;
        #endif

        fnMeasure_Exec();         //-------读计量数据函数----------

        fnBkgrd_Exec();         //-------时间任务调度函数-------

        fnHarmonic_Exec();

        fnEnergy_Exec();        //-------电量累加函数-------------

        fnEvent_Exec();         //-------事件记录相关函数--------

        fnFreeze();             //------冻结-------------

        fnScomPk_Exec();        //-------通讯函数-------------------

        fnSecret_Exec();

        //fnOutput_Exec();

        fnPowerDown_Inactive();     //掉电检测

        fnSocRegCheck(false, 0, 0);

        #if DEBUG_Cyctime_Stat == 1
        cycle_timer = ((u32)SysStamp + 65536 - cycle_timer);
        if (cycle_timer >= 65536)
        {
            cycle_timer -= 65536;
        }
        cycle_max_timer = (cycle_timer > cycle_max_timer) ? cycle_timer : cycle_max_timer;
        #endif
    }
    /* End user code. Do not edit comment generated here */
}
