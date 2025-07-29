/****************************************************************************
* @file     TC.c
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.05.25
* @brief    Timer驱动
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include <stdint.h>
//#include <Dat_Types.h>
//#include <RN8318_RegDefine.h>
//#include <RN8318.h>
//#include <Rn8xxx_Gpio.h>

#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include <Rn8xxx_TC.h>
//#include <Drive_Lib.h>

/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private data ---------------------------------------------------------*/

/* Exported data ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/

/*********************************************************************************************************
** Function name:       fnRn8xxx_TC_SquareWaveInit
** Descriptions:        方波输出初始化
** input parameters:    SquareWaveClock:方波频率HZ
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void Rn8xxx_TC_SquareWaveInit(u8 TimerId, uint32_t SquareWaveClock)
{
    TC_TypeDef  *Timer;
    SysCtl_EnableWrite;
    if (TimerId == Timer0)
    {
        TC0_Clk_En;             /* "开启TC0 APB时钟"*/
        Timer = (TC_TypeDef *)TC0;
    }
    else
    {
        TC1_Clk_En;             /* "开启TC1 APB时钟"*/
        Timer = (TC_TypeDef *)TC1;
    }
    SysCtl_DisableWrite;

    Timer->CCFG = 0;
    Timer->PS = 0;
    Timer->DN = ((SystemCoreClock / SquareWaveClock / 2) / (Timer->PS + 1)) - 1; //   /* " 根据设置频率设置分频数"*/

    Timer->CM0 = (0 << 29) | (1 << 28) | (3 << 25) | (1 << 1) | (1 << 0);;
    // Timer->CM1 = (0<<29)|(1<<28)| (3<<25)|(1<<1)|(1<<0);;
    //Timer->CCD0 = 0X1;/*"相移"*/
    // Timer->CCD1 = 0X3f;

    Timer->CTRL = (BIT28 | BIT0); /*"调试暂停TC继续"*/
}

/*********************************************************************************************************
** Function name:       fnRn8xxx_TC_TimeInit
** Descriptions:        定时器初始化
** input parameters:    tUnit_ms:定时器单位ms
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void Rn8xxx_TC_TimeInit(u8 TimerId, u8 tUnit_ms)
{
    TC_TypeDef  *Timer;
    uint32_t ticks;
    SysCtl_EnableWrite;
    if (TimerId == Timer0)
    {
        TC0_Clk_En;             // 开启TC0 APB时钟
        Timer = (TC_TypeDef *)TC0;
    }
    else if (TimerId == Timer1)
    {
        TC1_Clk_En;             // 开启TC1 APB时钟
        Timer = (TC_TypeDef *)TC1;
    }
    else
    {
        ticks = SystemCoreClock * tUnit_ms;
        SysTick_Config(ticks);
        return;
    }
    SysCtl_DisableWrite;

    Timer->CCFG = 0;
    Timer->PS = 4;
    Timer->DN = (SystemCoreClock * tUnit_ms) / ((Timer->PS + 1) * 1000) -1; // 根据设置间隔时间设置分频数
    Timer->CTRL = 0x00;
}

/*********************************************************************************************************
** Function name:       fnRn8xxx_TC_TimeStar
** Descriptions:        间隔定时器启动
** input parameters:    IrqFlag: ENABLE 打开中断服务程序  DISABLE 关闭中断服务程序
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void Rn8xxx_TC_TimeStar(u8 TimerId, FunctionalState IrqFlag)
{
    TC_TypeDef  *Timer;
    IRQn_Type IRQn;
    if (TimerId == Timer0)
    {
        Timer = (TC_TypeDef *)TC0;
        IRQn = TC0_IRQn;
    }
    else
    {
        Timer = (TC_TypeDef *)TC1;
        IRQn = TC1_IRQn;
    }

    if (IrqFlag == ENABLE)
    {
        Timer->IE |= 0x01;          // IRQ enable
    }
    else
    {
        Timer->IE &= 0xfffffffe;            // IRQ Disable
    }
    Timer->CTRL |= 0x01;        // star TC0
    NVIC_EnableIRQ(IRQn);
}

/*********************************************************************************************************
** Function name:       Rn8xxx_TC_TimeStop
** Descriptions:        间隔定时器关闭
** input parameters:    None
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void Rn8xxx_TC_TimeStop(u8 TimerId)
{
    TC_TypeDef  *Timer;
    IRQn_Type IRQn;
    if (TimerId == Timer0)
    {
        Timer = (TC_TypeDef *)TC0;
        IRQn = TC0_IRQn;
    }
    else if (TimerId == Timer1)
    {
        Timer = (TC_TypeDef *)TC1;
        IRQn = TC1_IRQn;
    }
    else
    {
    }
    Timer->CTRL &= 0xfffffffe;      // stop TC0
    Timer->IE &= 0xfffffffe;            // IRQ Disable
    NVIC_DisableIRQ(IRQn);
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
