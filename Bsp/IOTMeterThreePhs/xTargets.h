#ifndef  _XTARGER_H
#define  _XTARGER_H

#define TIMEOUT_DATA 0x3ff

#ifndef __SocEE_H__
#define __SocEE_H__
//存储器类型定义，页大小设置
#define EEPROM24C04MAXSize      (4*128)  //每1Kbit为128字节
#define EEPROM24C128MAXSize     (128*128)   //每1Kbit为128字节
#define EEPROM24C64MAXSize      (64*128)    //每1Kbit为128字节
#define EEPROM24C256MAXSize     (256*128)   //每1Kbit为128字节
#define EEPROM24C512MAXSIZE     (512*128)
#define EEPROM24C1024MAXSIZE    (1024*128)
#define SocEE_MAXSize   (256*128)
//---------------------
#define EEPROM24C04PageSize     0x07
#define EEPROM24C64PageSize     0x1f
#define EEPROM24C128PageSize    0x3f
#define EEPROM24C256PageSize    0x3f
#define EEPROM24C512PageSize    0x7f
#define EEPROM24C1024PageSize   0xff
#define SocEE_PageSize   0x3f
#define EEPROM_MEMORY_BASE      0x08000000
#define Read_EEPROM              ((u8  *) EEPROM_MEMORY_BASE    )
#endif

#if (PCB_Version==RN8611_RN8209D)
#define _PIN_NULL               0xFF

#define PinSWDCLK               _PIN2_4
#define PinSWDIO                _PIN2_5

#define PinISP                  _PIN3_0         /*"ISP检测"*/
#define PinAD_3V6               _PIN0_0         /*"时钟电池电压检测脚"*/
#define PinAD_6V                _PIN_NULL       /*"抄表电池电压检测脚"*/
#define PinLVD                  _PIN0_3         /*"系统电源检测"*/

#define PinRelayCheck_Ctrl      _PIN_NULL           /*"继电器检测"*/
#define RelayCheck_PowerON()
#define RelayCheck_PowerOFF()

#define PinRelayCheck           _PIN_NULL           /*"继电器检测"*/
#define PinMode_RelayCheck(x)
#define PinRead_RelayGataCheck(x)   1/*"继电器检测P01 "*/

#define PinSCAP_VCTRL           _PIN_NULL
#define SCAP_VCTRL_PowerOn()
#define SCAP_VCTRL_PowerOff()

//P30输出
#define PinWrite_DEBUGOut           {Rn8xxx_GPIO_CfgFun(_PIN3_0,_NORMALIO);Rn8xxx_GPIO_CfgIOMode( _PIN3_0 , GPIO_MODE_OUT , NORMAL_OUT ); }
#define PinWrite_DEBUGOutput(x)     (GPIO_WRITE_PIN3_0(x))

//---按键定义--------------------------------

#define PinKTURA                _PIN_NULL       /*"按键up"*/
#define PinRead_KeyTurnA(x)     1               /*"按键up    p1.0"*/

#define PinKTURB                _PIN_NULL       /*"按键down"*/
#define PinRead_KeyTurnB(x)     1               /*"按键down     p1.1"*/

#define PinKCOVER               _PIN3_1         /*"开上盖检测"*/
#define PinRead_KeyShell(x)     (GPIO_READ_PIN3_1(0))

#define PinKBTMBOX              _PIN_NULL           /*"开端盖检测"*/
#define PinRead_KeyJunBox(x)    1

#define PinMR_Check             _PIN_NULL       /*" 磁检测 "*/
#define PinRead_StrongMan(x)    1

#define PinClkOut               _PIN3_2         /*"秒脉冲输出"*/
#define PinWrite_OpticalOutMulFun(x)   (GPIO_WRITE_PIN3_2(x))

/*"*****************************加密模块相关IO口*********************************************************************"*/

/*"EASM  IO口定义"*/
#define PinEsamClk              _PIN10_5                    /*"Esam时钟脚"*/
#define PinWrite_EsamSCK(x)     (GPIO_WRITE_PIN10_5(x))
#define PinMode_EsamSCK(x)      (GPIO_MODE_PIN10_5(x))

#define PinEASMMISO             _PIN10_6                    //EASM通讯SPI 的MISO脚
#define PinWrite_EsamMISO(x)    (GPIO_WRITE_PIN10_6(x))
#define PinRead_EsamMISO(x)     (GPIO_READ_PIN10_6(x))
#define PinMode_EsamMISO(x)     (GPIO_MODE_PIN10_6(x))

#define PinEASMMOSI             _PIN10_7                    //EASM通讯SPI 的MOSI脚
#define PinWrite_EsamMOSI(x)    (GPIO_WRITE_PIN10_7(x))
#define PinRead_EsamMOSI(x)     (GPIO_READ_PIN10_7(x))
#define PinMode_EsamMOSI(x)     (GPIO_MODE_PIN10_7(x))

#define PinEASMCS               _PIN10_4                    /*"EASM通讯SPI 的CS脚"*/
#define ENABLE_ESAM()   {GPIO_WRITE_PIN10_4(0);GPIO_MODE_PIN10_4(GPIO_MODE_OUT);}
#define DISABLE_ESAM()  {GPIO_WRITE_PIN10_4(1);GPIO_MODE_PIN10_4(GPIO_MODE_OUT);}

#define PinEASMPower            _PIN0_1         /*"EASM电源控制脚"*/
#define EsamPowerOff()          {GPIO_MODE_PIN0_1(GPIO_MODE_OUT);GPIO_WRITE_PIN0_1(1);}
#define EsamPowerOn()           {GPIO_MODE_PIN0_1(GPIO_MODE_OUT);GPIO_WRITE_PIN0_1(0);}

#define PinIC_IO                _PIN_NULL       /*"卡数据口"*/
#define PinIC_RST               _PIN_NULL       /*"卡复位口"*/
#define PinIC_KEY               _PIN_NULL       /*"卡检测口"*/

#define CardFoutOpen()          /*卡及ESAM的时钟输出p4[0]*/
#define CardFoutClose()

/*"***************************通讯模块相关IO口*********************************************************************"*/

#define Pin485RE                _PIN_NULL       /*"485通道收发控制脚"*/
#define PinRXD485               _PIN2_0         /*"485通道接收脚"*/
#define PinTXD485               _PIN2_1         /*"485通道发送脚"*/

#define Pin485BRE               _PIN_NULL       /*"485通道收发控制脚"*/
#define PinRXD485B              _PIN_NULL       /*"485通道接收脚"*/
#define PinTXD485B              _PIN_NULL       /*"485通道发送脚"*/

#define PinCtrlWake             _PIN_NULL       /*"红外电源控制"*/
#define IRPowerPowerOff()
#define IRPowerPowerOn()

#define PinRXD_IR               _PIN_NULL       /*"红外通道接收脚"*/
#define PinTXD_IR               _PIN_NULL       /*"红外通道发送脚"*/
#define PinMode_IRRX(x)
#define PinRead_IRRX(x)         1

#define PinRXD_ZB               _PIN_NULL         /*"载波通道接收脚"*/
#define PinTXD_ZB               _PIN_NULL         /*"载波通道发送脚"*/

//蜂鸣器输出
#define PinSPK                  _PIN_NULL       /*"蜂鸣器"*/
#define PinWrite_Beep(x)

#define PinLCDBackLight         _PIN_NULL       /*"液晶背光"*/
#define LCDBackLightOff()
#define LCDBackLightON()

/*"****************************计量模块相关IO口*********************************************************************"*/
#define PinRN8209CS             _PIN5_2
#define ENABLE_RN8209CS()       {GPIO_WRITE_PIN5_2(0);GPIO_MODE_PIN5_2(GPIO_MODE_OUT);}
#define DISABLE_RN8209CS()      {GPIO_WRITE_PIN5_2(1);GPIO_MODE_PIN5_2(GPIO_MODE_OUT);}

#define PinRN8209Clk            _PIN5_3
#define PinRN8209MOSI           _PIN5_5
#define PinRN8209MISO           _PIN5_4
#define PinRN8209_PF            _PIN3_6
#define PinRN8209_QF            _PIN3_7
#define PinRN8209_IRQ           _PIN4_2

#define Pin_PF                  _PIN5_0
#define Pin_QF                  _PIN5_1

#define Pin_PtHPF               _PIN4_6
#define Pin_NtHPF               _PIN4_7

#define PinWrite_PtHPF(x)           GPIO_WRITE_PIN4_6(x)
#define PinWrite_NtHPF(x)           GPIO_WRITE_PIN4_7(x)

/*"*****************************继电器模块相关IO口*********************************************************************"*/
#define PinJump                 _PIN_NULL       /*跳闸指示LED"*/
#define PinWrite_RelayLed(x)

#define PinWarn                 _PIN_NULL       /*"报警继电器控制"*/
#define PinLoadRelayON          _PIN_NULL
#define PinLoadRelayOFF         _PIN_NULL

/*"***************************存储模块相关IO口*********************************************************************"*/
#define PinFlashCLK             _PIN1_2     /*"外部Flash通讯SPI 的CLK脚"*/
#define PinWrite_MX25LSCK(x)    (GPIO_WRITE_PIN1_2(x))
#define PinMode_MX25LSCK(x)     (GPIO_MODE_PIN1_2(x))

#define PinFlashMISO            _PIN1_0     /*"外部Flash通讯SPI 的MISO脚"*/
#define PinWrite_MX25LMISO(x)   (GPIO_WRITE_PIN1_0(x))
#define PinRead_MX25LMISO(x)        (GPIO_READ_PIN1_0(x))
#define PinMode_MX25LMISO(x)        (GPIO_MODE_PIN1_0(x))

#define PinFlashMOSI            _PIN1_1     /*"外部Flash通讯SPI 的MOSI脚"*/
#define PinWrite_MX25LMOSI(x)   (GPIO_WRITE_PIN1_1(x))
#define PinMode_MX25LMOSI(x)        (GPIO_MODE_PIN1_1(x))

#define PinFlashCS              _PIN5_7     /*"外部Flash通讯SPI 的CS脚"*/
#define ENABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN5_7(0);GPIO_MODE_PIN5_7(GPIO_MODE_OUT);}
#define DISABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN5_7(1);GPIO_MODE_PIN5_7(GPIO_MODE_OUT);}

#define PinFLASHPower           _PIN2_6 //Flash电源供电脚
#define FLASH_PowerOff()    {  GPIO_MODE_PIN2_6(GPIO_MODE_OUT);GPIO_WRITE_PIN2_6(1); }  //flash与8302电源共用
#define FLASH_PowerOn()    {  GPIO_MODE_PIN2_6(GPIO_MODE_OUT);GPIO_WRITE_PIN2_6(0); }   //flash与8302电源共用
//---I2C0定义-----存储器---------------------------
#define PinEepromSCL            _PIN2_2             /*"E2   IIC通讯SCL脚"*/
#define PinEepromSDA            _PIN2_3             /*"E2   IIC通讯SDA脚"*/
#define PinWrite_SDA0(x)        (GPIO_WRITE_PIN2_3(x))
#define PinRead_SDA0(x)         (GPIO_READ_PIN2_3(0))
#define PinMode_SDA0(x)         (GPIO_MODE_PIN2_3(x))
#define PinWrite_SCL0(x)        (GPIO_WRITE_PIN2_2(x))
#define PinMode_SCL0(x)         (GPIO_MODE_PIN2_2(x))
/*"***************************载波模块相关IO口*********************************************************************"*/
#define PinZB_CTRL              _PIN_NULL       /*"载波电源控制"*/
#define PinSET_ZB               _PIN_NULL       /*" 载波设置脚   "*/
#define PinEVENOUT              _PIN_NULL       /*"事件上报口"*/
#define PinRST_ZB               _PIN_NULL       /*"载波复位脚"*/
#define PinSTA_ZB               _PIN_NULL       /*"载波状态脚"*/
#if(ZBComFlag == 1)
#define PinRead_CheckZBSta(x)   0
#define PinWrite_ZBRst(x)
#define PinWrite_ZBEvenOut(x)
#endif
#define PinWrite_ZBEvenOut(x)

/*"***************************与扩展模组通信接口，波形推送相关IO口*********************************************************************"*/
#define PinExModuleClk              _PIN4_1 //外部扩展模块SPI的CLK脚
#define PinWrite_ExModuleSCK(x)     (GPIO_WRITE_PIN4_1(x))
#define PinMode_ExModuleSCK(x)      (GPIO_MODE_PIN4_1(x))

#define PinExModuleMOSI             _PIN4_3 //外部扩展模块SPI的MOSI脚
#define PinWrite_ExModuleMOSI(x)    (GPIO_WRITE_PIN4_3(x))
#define PinRead_ExModuleMOSI(x)     (GPIO_READ_PIN4_3(x))
#define PinMode_ExModuleMOSI(x)     (GPIO_MODE_PIN4_3(x))

#define PinExModuleCS               _PIN4_0 //外部扩展SPI的CS脚
#define ENABLE_ExModule()           {GPIO_WRITE_PIN4_0(0);GPIO_MODE_PIN4_0(GPIO_MODE_OUT);}
#define DISABLE_ExModule()          {GPIO_WRITE_PIN4_0(1);GPIO_MODE_PIN4_0(GPIO_MODE_OUT);}

/*"***************************与管理模组通信接口*********************************************************************"*/

#define PinManageModuleRSTM     _PIN11_5    //管理模组复位管脚
#define PinWrite_PinManageModuleRSTM(x)     (GPIO_WRITE_PIN11_5(x))
#define PinMode_PinManageModuleRSTM(x)      (GPIO_MODE_PIN11_5(x))

#define PinManageModuleLVDOUT       _PIN2_7 //掉电状态输出管脚
#define PinWrite_ManageModuleLVDOUT(x)      (GPIO_WRITE_PIN2_7(x))
#define PinMode_ManageModuleLVDOUT(x)       (GPIO_MODE_PIN2_7(x))

#define PinManageModuleCOMRQIN  _PIN11_6    // 模块拔出检测
#define PinRead_ManageModuleCOMRQIN(x)  (GPIO_READ_PIN11_6(0))

#define PinManageModuleCS       _PIN11_0
#define PinManageModuleCLK      _PIN11_1
#define PinManageModuleMISO     _PIN11_2
#define PinManageModuleMOSI     _PIN11_3

/*"***************************与测温芯片通信接口*********************************************************************"*/

#define PinTmpSDA           _PIN14_2    //测温芯片IIC-SDA管脚
#define PinTmpSCL           _PIN14_1    //测温芯片IIC-SCL管脚

#define PinWrite_TmpSDA(x)          (GPIO_WRITE_PIN14_2(x))
#define PinRead_TmpSDA(x)           (GPIO_READ_PIN14_2(0))
#define PinMode_TmpSDA(x)           (GPIO_MODE_PIN14_2(x))
#define PinWrite_TmpSCL(x)          (GPIO_WRITE_PIN14_1(x))
#define PinMode_TmpSCL(x)           (GPIO_MODE_PIN14_1(x))

/*"***************************显示模块相关IO口*********************************************************************"*/
#define PinS1                   _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS2                   _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS3                   _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS4                   _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS5                   _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS6                   _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS7                   _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS8                   _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS9                   _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS10                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS11                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS12                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS13                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS14                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS15                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS16                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS17                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS18                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS19                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS20                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS21                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS22                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS23                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS24                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS25                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS26                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS27                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS28                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS29                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS30                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS31                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS32                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS33                  _PIN_NULL       /*"LCD  SEG脚"*/
#define PinS34                  _PIN_NULL       /*"LCD  SEG脚"*/

#define PinCOM0                 _PIN_NULL       /*"LCD  COM脚"*/
#define PinCOM1                 _PIN_NULL       /*"LCD  COM脚"*/
#define PinCOM2                 _PIN_NULL       /*"LCD  COM脚"*/
#define PinCOM3                 _PIN_NULL       /*"LCD  COM脚"*/

#else

#if(PCB_Version==RN8613V2_RN8209DV4)

#define PinISP                  _PIN3_0        /*"ISP检测"*/
//P30输出
#define PinWrite_DEBUGOut           {Rn8xxx_GPIO_CfgFun(_PIN3_0,_NORMALIO);Rn8xxx_GPIO_CfgIOMode( _PIN3_0 , GPIO_MODE_OUT , NORMAL_OUT ); }
#define PinWrite_DEBUGOutput(x)     (GPIO_WRITE_PIN3_0(x))

#define PinAD_3V6               _PIN0_0         /*"时钟电池电压检测脚"*/
#define PinLVD                  _PIN0_3         /*"系统电源检测"*/

//---按键定义--------------------------------

#define PinKTURB                0xFF        /*"按键up"*/
#define PinRead_KeyTurnB(x)     (0) /*"按键up    p1.0"*/

#define PinKCOVER               0xFF            /*"开上盖检测"*/
#define PinRead_KeyShell(x)     (0) /*"开上盖检测p45"*/

#define PinClkOut               _PIN3_2         /*"秒脉冲输出"*/
#define PinWrite_OpticalOutMulFun(x)   (GPIO_WRITE_PIN3_2(x))

/*"*****************************加密模块相关IO口*********************************************************************"*/

/*"EASM  IO口定义"*/
#define PinEsamClk              _PIN10_5//_PIN5_3//_PIN1_3          /*"Esam时钟脚"*/
#define PinWrite_EsamSCK(x)     (GPIO_WRITE_PIN10_5(x))
#define PinMode_EsamSCK(x)      (GPIO_MODE_PIN10_5(x))

#define PinEASMMISO             _PIN10_6//      //EASM通讯SPI 的MISO脚
#define PinWrite_EsamMISO(x)    (GPIO_WRITE_PIN10_6(x))
#define PinRead_EsamMISO(x)     (GPIO_READ_PIN10_6(x))
#define PinMode_EsamMISO(x)     (GPIO_MODE_PIN10_6(x))

#define PinEASMMOSI             _PIN10_7//          //EASM通讯SPI 的MOSI脚
#define PinWrite_EsamMOSI(x)    (GPIO_WRITE_PIN10_7(x))
#define PinRead_EsamMOSI(x)     (GPIO_READ_PIN10_7(x))
#define PinMode_EsamMOSI(x)     (GPIO_MODE_PIN10_7(x))

#define PinEASMCS               _PIN10_4//_PIN5_2//_PIN11_0         /*"EASM通讯SPI 的CS脚"*/
#define ENABLE_ESAM()           {GPIO_WRITE_PIN10_4(0);GPIO_MODE_PIN10_4(GPIO_MODE_OUT);}
#define DISABLE_ESAM()          {GPIO_WRITE_PIN10_4(1);GPIO_MODE_PIN10_4(GPIO_MODE_OUT);}

#define PinEASMPower            _PIN0_1         /*"EASM电源控制脚"*/
#define EsamPowerOff()          {GPIO_WRITE_PIN0_1(1);GPIO_MODE_PIN0_1(GPIO_MODE_OUT);}//
#define EsamPowerOn()           {GPIO_WRITE_PIN0_1(0);GPIO_MODE_PIN0_1(GPIO_MODE_OUT);}
#define PinIC_IO                (0xFF)//_PIN4_2         /*"卡数据口"*/
#define PinIC_RST              (0xFF) //_PIN3_4         /*"卡复位口"*/
#define PinIC_KEY               (0xFF)//_PIN3_5         /*"卡检测口"*/

#define CardFoutOpen()          (0xFF)//ZHUPDEBUG {ISO7816 ->CLK=0x0A;}             /*卡及ESAM的时钟输出p4[0]*/
#define CardFoutClose()         (0xFF)//ZHUPDEBUG {ISO7816 ->CLK=0x02;}

/*"***************************通讯模块相关IO口*********************************************************************"*/
#define Pin485RE                0xFF //_PIN1_4         /*"485通道收发控制脚"*/
#define PinRXD485               0xFF         /*"485通道接收脚"*/
#define PinTXD485              0xFF         /*"485通道发送脚"*/

#define PinRXD_IR               0xFF//_PIN5_4         /*"红外通道接收脚"*/
#define PinTXD_IR               0xFF//_PIN5_5         /*"红外通道发送脚"*/
#define PinMode_IRRX(x)         (0)//
#define PinRead_IRRX(x)         (0)//

#define PinRXD_ZB               _PIN2_0         /*"载波通道接收脚"*/
#define PinTXD_ZB               _PIN2_1         /*"载波通道发送脚"*/

//蜂鸣器输出
#define PinSPK                  0xFF            /*"蜂鸣器"*/
#define PinWrite_Beep(x)                (0)//

/*"****************************计量模块相关IO口*********************************************************************"*/

#define PinRN8209Clk                _PIN11_1//
#define PinWrite_RN8209SCK(x)   (GPIO_WRITE_PIN11_1(x))
#define PinMode_RN8209SCK(x)        (GPIO_MODE_PIN11_1(x))

#define PinRN8209MISO               _PIN11_2//
#define PinWrite_RN8209MISO(x)      (GPIO_WRITE_PIN11_2(x))
#define PinRead_RN8209MISO(x)     (GPIO_READ_PIN11_2(x))
#define PinMode_RN8209MISO(x)       (GPIO_MODE_PIN11_2(x))

#define PinRN8209MOSI               _PIN11_3//
#define PinWrite_RN8209MOSI(x)      (GPIO_WRITE_PIN11_3(x))
#define PinRead_RN8209MOSI(x)       (GPIO_READ_PIN11_3(x))
#define PinMode_RN8209MOSI(x)       (GPIO_MODE_PIN11_3(x))

#define PinRN8209CS               _PIN11_0//
#define ENABLE_RN8209CS()           {GPIO_WRITE_PIN11_0(0);GPIO_MODE_PIN11_0(GPIO_MODE_OUT);}
#define DISABLE_RN8209CS()          {GPIO_WRITE_PIN11_0(1);GPIO_MODE_PIN11_0(GPIO_MODE_OUT);}

#define PinRN8209_PF               _PIN3_6  //计量芯片输入有功脉冲管脚
#define PinRN8209_QF               _PIN3_7  //计量芯片输入无功脉冲管脚

#define Pin_PF               _PIN5_1// MCU输出有功脉冲
#define Pin_QF               _PIN5_0//MCU输出无功脉冲

#define Pin_PtHPF               _PIN3_4// MCU输出正向有功谐波电能
#define Pin_NtHPF               _PIN4_7//MCU输出反向有功谐波电能

#define PinRN8209_IRQ               _PIN4_2 //计量芯片中断输入

/*"***************************与扩展模组通信接口，波形推送相关IO口*********************************************************************"*/
#define PinExModuleClk              _PIN4_1 //外部扩展模块SPI的CLK脚
#define PinWrite_ExModuleSCK(x)     (GPIO_WRITE_PIN4_1(x))
#define PinMode_ExModuleSCK(x)      (GPIO_MODE_PIN4_1(x))

#define PinExModuleMOSI             _PIN4_3 //外部扩展模块SPI的MOSI脚
#define PinWrite_ExModuleMOSI(x)    (GPIO_WRITE_PIN4_3(x))
#define PinRead_ExModuleMOSI(x)     (GPIO_READ_PIN4_3(x))
#define PinMode_ExModuleMOSI(x)     (GPIO_MODE_PIN4_3(x))

#define PinExModuleCS               _PIN11_5 //外部扩展SPI的CS脚
#define ENABLE_ExModule()           {GPIO_WRITE_PIN11_5(0);GPIO_MODE_PIN11_5(GPIO_MODE_OUT);}
#define DISABLE_ExModule()          {GPIO_WRITE_PIN11_5(1);GPIO_MODE_PIN11_5(GPIO_MODE_OUT);}

/*"***************************存储模块相关IO口*********************************************************************"*/
/*"flashSPI"*/
#define     PinFLASHPower           _PIN2_6
#define FLASH_PowerOff()    {GPIO_WRITE_PIN2_6(1);GPIO_MODE_PIN2_6(GPIO_MODE_OUT);}//
#define FLASH_PowerOn()    {GPIO_WRITE_PIN2_6(0);GPIO_MODE_PIN2_6(GPIO_MODE_OUT);}

/*"----FLASH   SPI定义-----"*/
#define PinFlashCLK         _PIN1_2     /*"外部Flash通讯SPI 的CLK脚"*/
#define PinWrite_MX25LSCK(x)        (GPIO_WRITE_PIN1_2(x))//
#define PinMode_MX25LSCK(x)     (GPIO_MODE_PIN1_2(x))

#define PinFlashMISO            _PIN1_0     /*"外部Flash通讯SPI 的MISO脚"*/
#define PinWrite_MX25LMISO(x)   (GPIO_WRITE_PIN1_0(x))//
#define PinRead_MX25LMISO(x)        (GPIO_READ_PIN1_0(x))

#define PinFlashMOSI            _PIN1_1     /*"外部Flash通讯SPI 的MOSI脚"*/
#define PinMode_MX25LMISO(x)        (GPIO_MODE_PIN1_0(x))
#define PinWrite_MX25LMOSI(x)   (GPIO_WRITE_PIN1_1(x))  //
#define PinMode_MX25LMOSI(x)        (GPIO_MODE_PIN1_1(x))

#define PinFlashCS              _PIN5_7 //  /*"外部Flash通讯SPI 的CS脚"*/
#define ENABLE_FLASH_MX25LXX()    {GPIO_WRITE_PIN5_7(0); GPIO_MODE_PIN5_7(GPIO_MODE_OUT);}
#define DISABLE_FLASH_MX25LXX()  {GPIO_WRITE_PIN5_7(1); GPIO_MODE_PIN5_7(GPIO_MODE_OUT);}

//---I2C0定义-----存储器---------------------------
#define PinEepromSCL            _PIN2_2//       /*"E2   IIC通讯SCL脚"*/
#define PinEepromSDA            _PIN2_3//           /*"E2   IIC通讯SDA脚"*/
#define PinWrite_SDA0(x)        (GPIO_WRITE_PIN2_3(x))//p5.3
#define PinRead_SDA0(x)     (GPIO_READ_PIN2_3(0))//
#define PinMode_SDA0(x)     (GPIO_MODE_PIN2_3(x))//
#define PinWrite_SCL0(x)        (GPIO_WRITE_PIN2_2(x))//
#define PinMode_SCL0(x)     (GPIO_MODE_PIN2_2(x))//

#define PinEVENOUT              0xFF        /*"事件上报口"*/
#define PinWrite_ZBEvenOut(x)   (0) //

#define PinSCAP_VCTRL              _PIN11_6   //掉电主动上报超级电源供电控制
#define SCAP_VCTRL_PowerOff()    {GPIO_WRITE_PIN11_6(1);GPIO_MODE_PIN11_6(GPIO_MODE_OUT);}//
#define SCAP_VCTRL_PowerOn()    {GPIO_WRITE_PIN11_6(0);GPIO_MODE_PIN11_6(GPIO_MODE_OUT);}

#define PinLCDBackLight         0xFF        /*"液晶背光"*/
#define LCDBackLightOff()      (0)
#define LCDBackLightON()       (0)

#define PinJump                 0xFF        /*跳闸指示LED"*/
#define PinWrite_RelayLed(x)           (0)  //x=0 点亮

#define PinRelayCheck_Ctrl      0xFF            /*"    "*/
#define RelayCheck_PowerON()    {;}
#define RelayCheck_PowerOFF()   {;}

#define PinRelayCheck           0xFF            /*"继电器检测"*/
#define PinMode_RelayCheck(x)       (0)
#define PinRead_RelayGataCheck()   (0)  /*"继电器检测P01 "*/

#define PinWarn                 0xFF            /*"外置继电器"*/
#define PinLoadRelayON          0xFF        /*"继电器控制1"*/
#define PinLoadRelayOFF         0xFF        /*"继电器控制2"*/

#define PinSET_ZB               (0xFF)//_PIN11_6        /*" 载波设置脚   "*/

#define PinRST_ZB               (0xFF)//_PIN5_7 //_PIN5_1         /*"载波复位脚"*/
#define PinSTA_ZB               (0xFF)//_PIN5_1         /*"载波状态脚"*/

#define PinRead_CheckZBSta(x)   (1) //GPIO_READ_PIN5_1(0)            // p5.1
#define PinWrite_ZBRst(x)           (0) //GPIO_WRITE_PIN5_7(x)

#else

#define PinISP                  _PIN3_0        /*"ISP检测"*/
#define PinAD_3V6               _PIN4_5         /*"时钟电池电压检测脚"*/
#define PinLVD                  _PIN0_3         /*"系统电源检测"*/

//P30输出
#define PinWrite_DEBUGOut           {Rn8xxx_GPIO_CfgFun(_PIN3_0,_NORMALIO);Rn8xxx_GPIO_CfgIOMode( _PIN3_0 , GPIO_MODE_OUT , NORMAL_OUT ); }
#define PinWrite_DEBUGOutput(x)     (GPIO_WRITE_PIN3_0(x))

//---按键定义--------------------------------

#define PinKTURB                _PIN3_6        /*"按键up"*/
#define PinRead_KeyTurnB(x)     (GPIO_READ_PIN3_6(0))   /*"按键up    p1.0"*/

#define PinKCOVER               _PIN4_4         /*"开上盖检测"*/
#define PinRead_KeyShell(x)     (GPIO_READ_PIN4_4(0))   /*"开上盖检测p45"*/

#define PinClkOut               _PIN5_6         /*"秒脉冲输出"*/
#define PinWrite_OpticalOutMulFun(x)   (GPIO_WRITE_PIN5_6(x))

/*"*****************************加密模块相关IO口*********************************************************************"*/

/*"EASM  IO口定义"*/
#define PinEsamClk              _PIN5_1//_PIN5_3//_PIN1_3           /*"Esam时钟脚"*/
#define PinWrite_EsamSCK(x)     (GPIO_WRITE_PIN5_1(x))
#define PinMode_EsamSCK(x)      (GPIO_MODE_PIN5_1(x))

#define PinEASMMISO             _PIN4_6//       //EASM通讯SPI 的MISO脚
#define PinWrite_EsamMISO(x)    (GPIO_WRITE_PIN4_6(x))
#define PinRead_EsamMISO(x)     (GPIO_READ_PIN4_6(x))
#define PinMode_EsamMISO(x)     (GPIO_MODE_PIN4_6(x))

#define PinEASMMOSI             _PIN4_7//           //EASM通讯SPI 的MOSI脚
#define PinWrite_EsamMOSI(x)    (GPIO_WRITE_PIN4_7(x))
#define PinRead_EsamMOSI(x)     (GPIO_READ_PIN4_7(x))
#define PinMode_EsamMOSI(x)     (GPIO_MODE_PIN4_7(x))

#define PinEASMCS               _PIN0_4//_PIN5_2//_PIN11_0      /*"EASM通讯SPI 的CS脚"*/
#define ENABLE_ESAM()           {GPIO_WRITE_PIN0_4(0);GPIO_MODE_PIN0_4(GPIO_MODE_OUT);}
#define DISABLE_ESAM()          {GPIO_WRITE_PIN0_4(1);GPIO_MODE_PIN0_4(GPIO_MODE_OUT);}

#define PinEASMPower            _PIN9_3         /*"EASM电源控制脚"*/
#define EsamPowerOff()          {GPIO_WRITE_PIN9_3(1);GPIO_MODE_PIN9_3(GPIO_MODE_OUT);}//
#define EsamPowerOn()           {GPIO_WRITE_PIN9_3(0);GPIO_MODE_PIN9_3(GPIO_MODE_OUT);}

#define PinIC_IO                (0xFF)//_PIN4_2         /*"卡数据口"*/
#define PinIC_RST              (0xFF) //_PIN3_4         /*"卡复位口"*/
#define PinIC_KEY               (0xFF)//_PIN3_5         /*"卡检测口"*/

#define CardFoutOpen()          (0xFF)//ZHUPDEBUG {ISO7816 ->CLK=0x0A;}             /*卡及ESAM的时钟输出p4[0]*/
#define CardFoutClose()         (0xFF)//ZHUPDEBUG {ISO7816 ->CLK=0x02;}

/*"***************************通讯模块相关IO口*********************************************************************"*/

#define Pin485RE                _PIN7_1 //_PIN1_4         /*"485通道收发控制脚"*/
#define PinRXD485               _PIN2_0         /*"485通道接收脚"*/
#define PinTXD485              _PIN2_1         /*"485通道发送脚"*/

#define PinRXD_IR               _PIN2_2//_PIN5_4         /*"红外通道接收脚"*/
#define PinTXD_IR               _PIN2_3//_PIN5_5         /*"红外通道发送脚"*/
#define PinMode_IRRX(x)         (GPIO_MODE_PIN2_2(x))//
#define PinRead_IRRX(x)         (GPIO_READ_PIN2_2(0))//

#define PinRXD_ZB               _PIN2_6         /*"载波通道接收脚"*/
#define PinTXD_ZB               _PIN2_7         /*"载波通道发送脚"*/

//蜂鸣器输出
#define PinSPK                  _PIN7_2         /*"蜂鸣器"*/
#define PinWrite_Beep(x)                (GPIO_WRITE_PIN7_2(x))//

/*"****************************计量模块相关IO口*********************************************************************"*/
#define PinRXD_RN8209C               _PIN0_0
#define PinTXD_RN8209C               _PIN0_1

#define PinRXD_RN8209F               _PIN5_4
#define PinTXD_RN8209F               _PIN5_5

/*"***************************存储模块相关IO口*********************************************************************"*/
/*"flashSPI"*/
#define     PinFLASHPower           _PIN9_2
#define FLASH_PowerOff()    {GPIO_WRITE_PIN9_2(1);GPIO_MODE_PIN9_2(GPIO_MODE_OUT);}//
#define FLASH_PowerOn()    {GPIO_WRITE_PIN9_2(0);GPIO_MODE_PIN9_2(GPIO_MODE_OUT);}

/*"----FLASH   SPI定义-----"*/
#define PinFlashCLK         _PIN9_4     /*"外部Flash通讯SPI 的CLK脚"*/
#define PinWrite_MX25LSCK(x)        (GPIO_WRITE_PIN9_4(x))//
#define PinMode_MX25LSCK(x)     (GPIO_MODE_PIN9_4(x))

#define PinFlashMISO            _PIN1_0     /*"外部Flash通讯SPI 的MISO脚"*/
#define PinWrite_MX25LMISO(x)   (GPIO_WRITE_PIN1_0(x))//
#define PinRead_MX25LMISO(x)        (GPIO_READ_PIN1_0(x))

#define PinFlashMOSI            _PIN1_1     /*"外部Flash通讯SPI 的MOSI脚"*/
#define PinMode_MX25LMISO(x)        (GPIO_MODE_PIN1_0(x))
#define PinWrite_MX25LMOSI(x)   (GPIO_WRITE_PIN1_1(x))  //
#define PinMode_MX25LMOSI(x)        (GPIO_MODE_PIN1_1(x))

#define PinFlashCS              _PIN9_5 //_PIN1_4           /*"外部Flash通讯SPI 的CS脚"*/
#define ENABLE_FLASH_MX25LXX()    {GPIO_WRITE_PIN9_5(0); GPIO_MODE_PIN9_5(GPIO_MODE_OUT);}
#define DISABLE_FLASH_MX25LXX()  {GPIO_WRITE_PIN9_5(1); GPIO_MODE_PIN9_5(GPIO_MODE_OUT);}

//---I2C0定义-----存储器---------------------------
#define PinEepromSCL            _PIN5_2//_PIN5_2            /*"E2   IIC通讯SCL脚"*/
#define PinEepromSDA            _PIN5_3//_PIN5_3            /*"E2   IIC通讯SDA脚"*/
#define PinWrite_SDA0(x)        (GPIO_WRITE_PIN5_3(x))//p5.3
#define PinRead_SDA0(x)     (GPIO_READ_PIN5_3(0))//
#define PinMode_SDA0(x)     (GPIO_MODE_PIN5_3(x))//
#define PinWrite_SCL0(x)        (GPIO_WRITE_PIN5_2(x))//
#define PinMode_SCL0(x)     (GPIO_MODE_PIN5_2(x))//

#define PinEVENOUT              _PIN4_1        /*"事件上报口"*/
#define PinWrite_ZBEvenOut(x)   (GPIO_WRITE_PIN4_1(x)) //

#define PinSCAP_VCTRL              _PIN7_3   //掉电主动上报超级电源供电控制
#define SCAP_VCTRL_PowerOff()    {GPIO_WRITE_PIN7_3(1);GPIO_MODE_PIN7_3(GPIO_MODE_OUT);}//
#define SCAP_VCTRL_PowerOn()    {GPIO_WRITE_PIN7_3(0);GPIO_MODE_PIN7_3(GPIO_MODE_OUT);}

#if(PCB_Version==RN8613_RN8209C)
/*"*****************************继电器模块相关IO口*********************************************************************"*/
#define PinLCDBackLight         _PIN10_7        /*"液晶背光"*/
#define LCDBackLightOff()      (GPIO_WRITE_PIN10_7(1))
#define LCDBackLightON()       (GPIO_WRITE_PIN10_7(0))

#define PinJump                 _PIN7_0     /*跳闸指示LED"*/
#define PinWrite_RelayLed(x)           (GPIO_WRITE_PIN7_0(x))  //x=0 点亮

#define PinRelayCheck_Ctrl      _PIN0_2         /*"    "*/
#define RelayCheck_PowerON()    {GPIO_WRITE_PIN0_2(1);GPIO_MODE_PIN0_2(GPIO_MODE_OUT);}
#define RelayCheck_PowerOFF()   {GPIO_WRITE_PIN0_2(0);GPIO_MODE_PIN0_2(GPIO_MODE_OUT);}

#define PinRelayCheck           _PIN10_6            /*"继电器检测"*/
#define PinMode_RelayCheck(x)       (GPIO_MODE_PIN10_6(x))
#define PinRead_RelayGataCheck()   (GPIO_READ_PIN10_6(0))   /*"继电器检测P01 "*/

#define PinWarn                 _PIN10_4            /*"外置继电器"*/
#define PinLoadRelayON          _PIN10_4        /*"继电器控制1"*/
#define PinLoadRelayOFF         _PIN10_5        /*"继电器控制2"*/

#define PinSET_ZB               (0)//_PIN11_6        /*" 载波设置脚   "*/

#define PinRST_ZB               (0)//_PIN5_7 //_PIN5_1         /*"载波复位脚"*/
#define PinSTA_ZB               (0)//_PIN5_1         /*"载波状态脚"*/

#define PinRead_CheckZBSta(x)   (1) //GPIO_READ_PIN5_1(0)            // p5.1
#define PinWrite_ZBRst(x)           (0) //GPIO_WRITE_PIN5_7(x)

#elif (PCB_Version==RN8613_RN8209S)
/*"*****************************继电器模块相关IO口*********************************************************************"*/
#define PinLCDBackLight         (0) //_PIN14_0        /*"液晶背光"*/
#define LCDBackLightOff()      (0) //(GPIO_WRITE_PIN14_0(1))
#define LCDBackLightON()       (0) //(GPIO_WRITE_PIN14_0(0))

#define PinJump                 _PIN7_0     /*跳闸指示LED"*/
#define PinWrite_RelayLed(x)           (GPIO_WRITE_PIN7_0(x))  //x=0 点亮

#define PinRelayCheck_Ctrl        (0) //_PIN2_4         /*"    "*/
#define RelayCheck_PowerON()    (0) //{GPIO_WRITE_PIN2_4(1);GPIO_MODE_PIN2_4(GPIO_MODE_OUT);}
#define RelayCheck_PowerOFF()   (0) //{GPIO_WRITE_PIN2_4(0);GPIO_MODE_PIN2_4(GPIO_MODE_OUT);}

#define PinRelayCheck           (0)//_PIN2_5            /*"继电器检测"*/
#define PinMode_RelayCheck(x)       (0) //(GPIO_MODE_PIN2_5(x))
#define PinRead_RelayGataCheck()   (0) //(GPIO_READ_PIN2_5(0))  /*"继电器检测P01 "*/

#define PinWarn                 _PIN0_2         /*"外置继电器"*/
#define PinLoadRelayON          _PIN0_2     /*"继电器控制1"*/
#define PinLoadRelayOFF         _PIN10_6        /*"继电器控制2"*/

#define PinSET_ZB               (0)//_PIN11_6        /*" 载波设置脚   "*/

#define PinRST_ZB               (0)//_PIN5_7 //_PIN5_1         /*"载波复位脚"*/
#define PinSTA_ZB               (0)//_PIN5_1         /*"载波状态脚"*/

#define PinRead_CheckZBSta(x)   (1) //GPIO_READ_PIN5_1(0)            // p5.1
#define PinWrite_ZBRst(x)           (0) //GPIO_WRITE_PIN5_7(x)

#endif

/*"***************************显示模块相关IO口*********************************************************************"*/
#define PinS1                  _PIN_Seg2Com6         /*"LCD  SEG脚"*/
#define PinS2                  _PIN_Seg3Com7         /*"LCD  SEG脚"*/
#define PinS3                   _PIN6_0         /*"LCD  SEG脚"*/
#define PinS4                   _PIN6_1         /*"LCD  SEG脚"*/
#define PinS5                   _PIN6_2         /*"LCD  SEG脚"*/
#define PinS6                   _PIN6_3         /*"LCD  SEG脚"*/
#define PinS7                   _PIN6_4         /*"LCD  SEG脚"*/
#define PinS8                   _PIN6_5         /*"LCD  SEG脚"*/
#define PinS9                   _PIN6_6         /*"LCD  SEG脚"*/
#define PinS10                  _PIN6_7         /*"LCD  SEG脚"*/
#define PinS11                  _PIN7_4         /*"LCD  SEG脚"*/
#define PinS12                  _PIN7_5         /*"LCD  SEG脚"*/
#define PinS13                  _PIN7_6         /*"LCD  SEG脚"*/
#define PinS14                  _PIN7_7         /*"LCD  SEG脚"*/
#define PinS15                  _PIN8_0         /*"LCD  SEG脚"*/
#define PinS16                  _PIN8_1         /*"LCD  SEG脚"*/
#define PinS17                  _PIN8_2         /*"LCD  SEG脚"*/
#define PinS18                  _PIN8_3         /*"LCD  SEG脚"*/
#define PinS19                  _PIN8_4         /*"LCD  SEG脚"*/
#define PinS20                  _PIN8_5         /*"LCD  SEG脚"*/
#define PinS21                  _PIN8_6         /*"LCD  SEG脚"*/
#define PinS22                  _PIN8_7         /*"LCD  SEG脚"*/
#define PinS23                  _PIN9_0         /*"LCD  SEG脚"*/
#define PinS24                  _PIN9_1         /*"LCD  SEG脚"*/

#define PinCOM4                 _PIN_Seg0Com4   /*"LCD  COM脚"*/
#define PinCOM5                 _PIN_Seg1Com5   /*"LCD  COM脚"*/

#define ON      1
#define OFF     0
#endif
#endif

//读写定义
#define Read    0
#define Write   1

#define TRUE    1
#define FALSE   0

#define IDLE    0           /* idle status */
#define READ    1           /* read mode */
#define WRITE   2           /* write mode */

#define SET     1
#define CLEAR   0

#define OS_TICKS_PER_SEC         1000    // Set the number of ticks in one second

typedef enum
{
    GPIO_EnableInput    = 0,
    GPIO_DisableInput   = 1
} eGPIOInputMode_TypeDef;

typedef struct
{
    u32    T_WDOG;
} sWDOG_TypeDef;

extern void fnWDT_Restart(void);
extern void fnRTC_Init(void);
extern void fnKEYINT_Init(void);
extern void fnTarget_Init(void);
extern void fnIntp_init(void);
extern void fnRTCDrive_Delay(void);
extern void fnINTTC0_RCInit(void);
extern void fnGPIO_Configuration(void);
extern void fnINTTC2_Star(void);
extern void fnINTTC2_Stop(void);
extern void SystemDelay(u16 t);
extern void fnDelayMs(u16 t);
extern void fnLVD_Init(void);
extern void fnINTRTC_Sleep(void);
extern void fnINTRTC_Init(void);
extern ErrorStatus fnSysClock_Read(sDF01 *Clock);
extern ErrorStatus fnSysClock_Write(sDF01 *Clock);

extern void fnSysDateTimes(sDate_time_s_TypeDef * ptime);

extern ErrorStatus fnSocEE_Write(u32 Dst, u8 *Src, u32 DatLen, u8 Repeat);
extern ErrorStatus fnSocEE_Read(u8 *Dst, u32 Src, u32 DatLen, u8 Repeat);

extern ErrorStatus fnSocRegCheck(bool InitAll, u8 AdOrRmItem, u32 regAddr);
extern ErrorStatus fnSocRegCheckAddAll(void);

extern void fnPowerOn_DrvieInit(void);
#endif  //
