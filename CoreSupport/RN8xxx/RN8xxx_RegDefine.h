/****************************************************************************
* @file     RN8318_RegDefine.h
* @author   Renergy Application Team
* @version  V1.0.0
* @date     2021.04.28
* @brief
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  _RN8xxx_RegDefine_H
#define  _RN8xxx_RegDefine_H

////寄存器地址为addr的第bitnum位的bitband地址获取
#define BITBAND_ADDR(addr,bitnum) *((__IO uint32_t *)((addr&0xFC000000) + 0x02000000 + (bitnum<<2) + (((addr & 0x07FFFFFF)<<5)&0x03FFFFFF)))
/*--------------------------各模块使能打开及关闭操作star-----------------------------------*/
#define     SysCtl_EnableRegister   SYSCTL->SYS_PS
#define     SysCtl_EnableWrite      {SYSCTL->SYS_PS = 0x82;}
#define     SysCtl_DisableWrite     {SYSCTL->SYS_PS = 0x00;}
#define     RtcCtl_EnableWrite      {RTC->CTRL |= 0x00000100;}
#define     RtcCtl_DisableWrite     {RTC->CTRL &= 0xfffffeff;}

/*--------------------------各模块使能打开及关闭操作END------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
    Hosc_Set8192M  = 0x0,
    Hosc_Set1638M  = 0x01,
    Hosc_Set3276M  = 0x02,
} eClockHoscFreq_TypeDef;

#define DriveClock_SetHoscFreq(x)   {SYSCTL->OSC_CTRL2 &= 0xfffffff8 , SYSCTL->OSC_CTRL2 |= x;}

/*--------------------------各寄存器位操作定义star-----------------------------------*/
// 操作模块APB时钟SYSCTL->MOD0_EN
#define Sys_Tc_Clk_En           {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 0) = 1;}
#define Sys_Tc_Clk_Dis          {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 0) = 0;}
#define CPC_Clk_En              {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 3) = 1;}
#define CPC_Clk_Dis             {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 3) = 0;}
#define TC0_Clk_En              {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 4) = 1;}
#define TC0_Clk_Dis             {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 4) = 0;}
#define TC1_Clk_En              {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 5) = 1;}
#define TC1_Clk_Dis             {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 5) = 0;}
#define UART4_Clk_En            {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 6) = 1;}
#define UART4_Clk_Dis           {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 6) = 0;}
#define UART5_Clk_En            {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 7) = 1;}
#define UART5_Clk_Dis           {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 7) = 0;}
#define UART0_Clk_En            {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 8) = 1;}
#define UART0_Clk_Dis           {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 8) = 0;}
#define UART1_Clk_En            {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 9) = 1;}
#define UART1_Clk_Dis           {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 9) = 0;}
#define UART2_Clk_En            {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 10)= 1;}
#define UART2_Clk_Dis           {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 10)= 0;}
#define UART3_Clk_En            {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 11)= 1;}
#define UART3_Clk_Dis           {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 11)= 0;}
#define UART38K_Clk_En          {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 12)= 1;}
#define UART38K_Clk_Dis         {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 12)= 0;}
#define ISO7816_Clk_En          {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 13)= 1;}
#define ISO7816_Clk_Dis         {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 13)= 0;}
#define I2C_Clk_En              {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 14)= 1;}
#define I2C_Clk_Dis             {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , 14)= 0;}
#define SPI_Clk_En(x)           {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , (15+x))= 1;}
#define SPI_Clk_Dis(x)             {BITBAND_ADDR((u32 )(&SYSCTL->MOD0_EN) , (15+x))= 0;}

// 操作模块APB时钟SYSCTL->MOD1_EN
#define GPIO_Clk_En             {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 5) = 1;}
#define GPIO_Clk_Dis            {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 5) = 0;}
#define LCD_Clk_En              {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 6) = 1;}
#define LCD_Clk_Dis             {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 6) = 0;}
#define WDT_Clk_En              {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 9) = 1;}
#define WDT_Clk_Dis             {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 9) = 0;}
#define RTC_SAR_Clk_En          {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 10)= 1;}
#define RTC_SAR_Clk_Dis         {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 10)= 0;}
#define CMPLVD_Clk_En           {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 11)= 1;}
#define CMPLVD_Clk_Dis          {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 11)= 0;}

#define D2F_Clk_En           {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 13)= 1;}
#define D2F_Clk_Dis          {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 13)= 0;}
#define DSP_Clk_En           {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 14)= 1;}
#define DSP_Clk_Dis          {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 14)= 0;}
#define M2M_Clk_En           {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 15)= 1;}
#define M2M_Clk_Dis          {BITBAND_ADDR((u32 )(&SYSCTL->MOD1_EN) , 15)= 0;}

// 操作模块电源SYSCTL->SYS_PD
#define LVD_PD_PowOn            {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 3)  = 0;}
#define LVD_PD_PowDwn           {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 3)  = 1;}
#define CMP1_PD_PowOn           {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 4)  = 0;}
#define CMP1_PD_PowDwn          {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 4)  = 1;}
#define CMP2_PD_PowOn           {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 5)  = 0;}
#define CMP2_PD_PowDwn          {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 5)  = 1;}
#define PWD_CMP1R_En            {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 8)  = 0;}
#define PWD_CMP1R_Dis           {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 8)  = 1;}
#define PWD_CMP2R_En            {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 9)  = 0;}
#define PWD_CMP2R_Dis           {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 9)  = 1;}
#define HYSEN_CMP1_En           {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 10) = 1;}
#define HYSEN_CMP1_Dis          {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 10) = 0;}
#define HYSEN_CMP2_En           {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 11) = 1;}
#define HYSEN_CMP2_Dis          {BITBAND_ADDR((u32 )(&SYSCTL->SYS_PD) , 11) = 0;}

#endif
