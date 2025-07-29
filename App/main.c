/*
*******************************************************************************
**  Include files
*******************************************************************************
*/

#include <Includes.h>

#define DEBUG_Cyctime_Stat                  0           // ��ѭ�����ʱ��ͳ��ʹ��

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
    __disable_irq(); //���������жϣ�ȷ����ʼ�����̲����жϴ��
    SysConfCheck();
    fnSocRegCheck(true, 0, 0);
    SysConfCheck();
    SEGGER_RTT_Init();
    SEGGER_RTT_printf(0, "MCU Rester:%x\r\n", SYSCTL->SYS_RST);
    SEGGER_RTT_printf(0, "LibVersion is:%x\r\n", GetLibVersion());
    SEGGER_RTT_printf(0, "CodeVersion is:%x\r\n", GetCodeVersion());

    Bkgrd.PubData.Active = BKGRD_ACTIVE_POWDN;         //����
    Inactive.PubData.InactiveStamp = BKGRD_INACTIVE_LOWPOWER;   //����

    fnPowerOn_DrvieInit();
    fnPowerUp_Check();

    if (Inactive.PubData.InactiveStamp  == BKGRD_INACTIVE_POWERONINIT)
    {
        fnPowerUp_AppInit();
        //------�ϵ�ָ����ݺ����ϵ�ģʽ---------------
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

        fnMeasure_Exec();         //-------���������ݺ���----------

        fnBkgrd_Exec();         //-------ʱ��������Ⱥ���-------

        fnHarmonic_Exec();

        fnEnergy_Exec();        //-------�����ۼӺ���-------------

        fnEvent_Exec();         //-------�¼���¼��غ���--------

        fnFreeze();             //------����-------------

        fnScomPk_Exec();        //-------ͨѶ����-------------------

        fnSecret_Exec();

        //fnOutput_Exec();

        fnPowerDown_Inactive();     //������

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
