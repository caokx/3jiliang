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
#define SocEE_MAXSize   EEPROM24C256MAXSize
//---------------------
#define EEPROM24C04PageSize     0x07
#define EEPROM24C64PageSize     0x1f
#define EEPROM24C128PageSize    0x3f
#define EEPROM24C256PageSize    0x3f
#define EEPROM24C512PageSize    0x7f
#define EEPROM24C1024PageSize   0xff
#define SocEE_PageSize   EEPROM24C128PageSize
#define EEPROM_MEMORY_BASE      0x08000000
#define Read_EEPROM              ((u8  *) EEPROM_MEMORY_BASE    )
#endif

//#if (PCB_Version==RN8611_RN7306)
#define _PIN_NULL               0xFF

#define PinSWDCLK               _PIN2_4
#define PinSWDIO                _PIN2_5

#define PinISP                  _PIN3_0         /*"ISP检测"*/
#define PinAD_3V6               _PIN0_0         /*"时钟电池电压检测脚"*/
#define PinAD_6V                _PIN_NULL       /*"抄表电池电压检测脚"*/
#define PinLVD                  _PIN0_3         /*"系统电源检测"*/

#define PinRelayCheck           _PIN_NULL           /*"继电器检测"*/
#define PinRead_RelayGataCheck(x)   1/*"继电器检测P01 "*/

#define PinSCAP_VCTRL           _PIN_NULL

//P30输出
#define PinWrite_DEBUGOut           {Rn8xxx_GPIO_CfgFun(_PIN3_0,_NORMALIO);Rn8xxx_GPIO_CfgIOMode( _PIN3_0 , GPIO_MODE_OUT , NORMAL_OUT ); }
#define PinWrite_DEBUGOutput(x)     (GPIO_WRITE_PIN3_0(x))

#define PinSCAP_VCTRL           _PIN_NULL
#define SCAP_VCTRL_PowerOn()
#define SCAP_VCTRL_PowerOff()

//---按键定义--------------------------------

#define PinKTURA                _PIN_NULL       /*"按键up"*/
#define PinRead_KeyTurnA(x)     1               /*"按键up    p1.0"*/

#define PinKTURB                _PIN_NULL       /*"按键down"*/
#define PinRead_KeyTurnB(x)     1               /*"按键down     p1.1"*/

#define PinKCOVER               _PIN0_1         /*"开上盖检测" dyf 原理图是对的，PCB画的不对，放的位置不对，跟开端钮盖相反 */
#define PinRead_KeyShell(x)     (GPIO_READ_PIN0_1(0))   /* dyf 同步调整 */

#define PinKBTMBOX              _PIN3_1         /*"开端盖检测" dyf 原理图是对的，PCB画的不对，放的位置不对*/
#define PinRead_KeyJunBox(x)    (GPIO_READ_PIN3_1(0))   /* dyf 同步调整 */

#define PinMR_Check             _PIN14_2        /*" 磁检测 "*/
#define PinRead_StrongMan(x)     (GPIO_READ_PIN14_2(0))

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

#define PinEASMPower            _PIN5_7         /*"EASM电源控制脚"*/
#define EsamPowerOff()          {GPIO_MODE_PIN5_7(GPIO_MODE_OUT);GPIO_WRITE_PIN5_7(1);}
#define EsamPowerOn()           {GPIO_MODE_PIN5_7(GPIO_MODE_OUT);GPIO_WRITE_PIN5_7(0);}

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
#define PinMS_RST               _PIN_NULL //_PIN2_0         /*"RN8302复位管脚"*/

#define PinCLKOUT_2M            _PIN_NULL       /*"RN8207D  CLK   "*/
#define PinCLKOUT_8M            _PIN_NULL       /*"RN8302  CLK    "*/

#define PinRN8302_Power         _PIN8_4
#define RN8302_PowerOff()       {GPIO_MODE_PIN8_4(GPIO_MODE_OUT);GPIO_WRITE_PIN8_4(1);}
#define RN8302_PowerOn()        {GPIO_MODE_PIN8_4(GPIO_MODE_OUT);GPIO_WRITE_PIN8_4(0);}

#define PinRN8207_Power         _PIN_NULL
#define RN8207_PowerOff()
#define RN8207_PowerOn()

//---rn8302-----------
#define PinSCLK                 _PIN11_4            /*"RN8302通讯SPI 的CLK脚"*/
#define PinWrite_ADSCLK(x)      (GPIO_WRITE_PIN11_4(x))
#define PinMode_ADSCLK(x)       (GPIO_MODE_PIN11_4(x))

#define PinSDO_C                _PIN4_6         /*"RN8302通讯SPI 的MISO脚"*/
#define PinRead_ADMISO()        (GPIO_READ_PIN4_6(0))
#define PinMode_ADMISO(x)       (GPIO_MODE_PIN4_6(x))

#define PinSDI_C                _PIN14_1            /*"RN8302通讯SPI 的MOSI脚"*/
#define PinWrite_ADSMOSI(x)     (GPIO_WRITE_PIN14_1(x))
#define PinMode_ADSMOSI(x)      (GPIO_MODE_PIN14_1(x))

#define PinSCS_C                _PIN11_2            /*"RN8302通讯SPI 的CS脚"*/
#define PinWrite_ADCS(x)        (GPIO_WRITE_PIN11_2(x))
#define PinMode_ADCS(x)         (GPIO_MODE_PIN11_2(x))

#define PinHSCS_C               _PIN11_0
#define PinHSCLK_C              _PIN11_1
#define PinHMOSI_C              _PIN11_3

#define PinINTN1_C              _PIN4_2

#define PinRN8302_PF            _PIN3_6
#define PinRN8302_QF            _PIN3_7

#define Pin_PF                  _PIN5_0
#define Pin_QF                  _PIN5_1

#define Pin_PtHPF               _PIN3_4
#define Pin_NtHPF               _PIN4_7

/*"*****************************继电器模块相关IO口*********************************************************************"*/
#define PinJump                 _PIN_NULL       /*跳闸指示LED"*/
#define PinWrite_RelayLed(x)

#define PinWarn                 _PIN_NULL       /*"报警继电器控制"*/
#define PinLoadRelayON          _PIN_NULL
#define PinLoadRelayOFF         _PIN_NULL

/*"***************************存储模块相关IO口*********************************************************************"*/
#define PinFlashCLK             _PIN2_6     /*"外部Flash通讯SPI 的CLK脚"*/
#define PinWrite_MX25LSCK(x)    (GPIO_WRITE_PIN2_6(x))
#define PinMode_MX25LSCK(x)     (GPIO_MODE_PIN2_6(x))

#define PinFlashMISO            _PIN1_2     /*"外部Flash通讯SPI 的MISO脚"*/
#define PinWrite_MX25LMISO(x)   (GPIO_WRITE_PIN1_2(x))
#define PinRead_MX25LMISO(x)        (GPIO_READ_PIN1_2(x))
#define PinMode_MX25LMISO(x)        (GPIO_MODE_PIN1_2(x))

#define PinFlashMOSI            _PIN1_0     /*"外部Flash通讯SPI 的MOSI脚"*/
#define PinWrite_MX25LMOSI(x)   (GPIO_WRITE_PIN1_0(x))
#define PinMode_MX25LMOSI(x)        (GPIO_MODE_PIN1_0(x))

#define PinFlashCS              _PIN1_1     /*"外部Flash通讯SPI 的CS脚"*/
#define ENABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN1_1(0);GPIO_MODE_PIN1_1(GPIO_MODE_OUT);}
#define DISABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN1_1(1);GPIO_MODE_PIN1_1(GPIO_MODE_OUT);}

#define PinWrite_MX25LSCK_BitBandAddr   0x520000D8
#define PinWrite_MX25LMOSI_BitBandAddr  0x520000A0
#define PinWrite_MX25LMISO_BitBandAddr  0x520000A8
#define PinFLASHPower           _PIN11_5    //Flash电源供电脚
#define FLASH_PowerOff()    {  GPIO_MODE_PIN11_5(GPIO_MODE_OUT);GPIO_WRITE_PIN11_5(1); }    //flash与8302电源共用
#define FLASH_PowerOn()    {  GPIO_MODE_PIN11_5(GPIO_MODE_OUT);GPIO_WRITE_PIN11_5(0); } //flash与8302电源共用
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

#define PinManageModuleRSTM     _PIN3_0 //管理模组复位管脚
#define PinWrite_PinManageModuleRSTM(x)     (GPIO_WRITE_PIN3_0(x))
#define PinMode_PinManageModuleRSTM(x)      (GPIO_MODE_PIN3_0(x))

#define PinManageModuleLVDOUT       _PIN2_7 //掉电状态输出管脚
#define PinWrite_ManageModuleLVDOUT(x)      (GPIO_WRITE_PIN2_7(x))
#define PinMode_ManageModuleLVDOUT(x)       (GPIO_MODE_PIN2_7(x))

#define PinManageModuleCOMRQIN  _PIN11_6    // 模块拔出检测
#define PinRead_ManageModuleCOMRQIN(x)  (GPIO_READ_PIN11_6(0))

#define PinManageModuleCS           _PIN5_2
#define PinManageModuleCLK      _PIN5_3
#define PinManageModuleMISO     _PIN5_4
#define PinManageModuleMOSI     _PIN5_5

/*"***************************与测温芯片通信接口*********************************************************************"*/

#define PinTmpSDA           _PIN8_0 //测温芯片IIC-SDA管脚
#define PinTmpSCL           _PIN8_1 //测温芯片IIC-SCL管脚

#define PinWrite_TmpSDA(x)          (GPIO_WRITE_PIN8_0(x))
#define PinRead_TmpSDA(x)           (GPIO_READ_PIN8_0(0))
#define PinMode_TmpSDA(x)           (GPIO_MODE_PIN8_0(x))
#define PinWrite_TmpSCL(x)          (GPIO_WRITE_PIN8_1(x))
#define PinMode_TmpSCL(x)           (GPIO_MODE_PIN8_1(x))

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

//#else

//#define PinSWDCLK                  _PIN2_4
//#define PinSWDIO                  _PIN2_5

//#define PinISP                  _PIN3_0        /*"ISP检测"*/
//#define PinAD_3V6             _PIN0_0         /*"时钟电池电压检测脚"*/
//#define PinAD_6V              _PIN0_2         /*"抄表电池电压检测脚"*/
//#define PinLVD                    _PIN0_3         /*"系统电源检测"*/

//#define PinRelayCheck         _PIN0_1         /*"继电器检测"*/
//#define PinRead_RelayGataCheck(x)   (GPIO_READ_PIN0_1(0)) /*"继电器检测P01 "*/

////P30输出
//#define   PinWrite_DEBUGOut           {Rn8xxx_GPIO_CfgFun(_PIN3_0,_NORMALIO);Rn8xxx_GPIO_CfgIOMode( _PIN3_0 , GPIO_MODE_OUT , NORMAL_OUT ); }
//#define   PinWrite_DEBUGOutput(x)     (GPIO_WRITE_PIN3_0(x))

////---按键定义--------------------------------

//#define PinKTURA                _PIN1_0        /*"按键up"*/
//#define PinRead_KeyTurnA(x)       (GPIO_READ_PIN1_0(0))   /*"按键up    p1.0"*/

//#define PinKTURB                _PIN1_1        /*"按键down"*/
//#define PinRead_KeyTurnB(x)       (GPIO_READ_PIN1_1(0))   /*"按键down     p1.1"*/

//#define PinKCOVER             _PIN4_5         /*"开上盖检测"*/
//#define PinRead_KeyShell(x)       (GPIO_READ_PIN4_5(0))   /*"开上盖检测p45"*/

//#define PinKBTMBOX                _PIN4_4         /*"开端盖检测"*/
//#define PinRead_KeyJunBox(x)  (GPIO_READ_PIN4_4(0))       /*"开端盖检测p44"*/

//#define PinMR_Check               _PIN0_4         /*" 磁检测 "*/
//#define PinRead_StrongMan(x)   (GPIO_READ_PIN0_4(0))      /*" 磁检测 P04  "*/

//#define PinClkOut             _PIN5_6         /*"秒脉冲输出"*/
//#define PinWrite_OpticalOutMulFun(x)   (GPIO_WRITE_PIN5_6(x))

///*"*****************************加密模块相关IO口*********************************************************************"*/

///*"EASM  IO口定义"*/
//#define PinEsamClk                _PIN11_1//_PIN5_3//_PIN1_3          /*"Esam时钟脚"*/
//#define PinWrite_EsamSCK(x)   (GPIO_WRITE_PIN11_1(x))     /*"P53"*/
//#define PinMode_EsamSCK(x)        (GPIO_MODE_PIN11_1(x))

//#define PinEASMMISO               _PIN11_2//_PIN5_4           //EASM通讯SPI 的MISO脚
//#define PinWrite_EsamMISO(x)      (GPIO_WRITE_PIN11_2(x))     /*"P54"*/
//#define PinRead_EsamMISO(x)     (GPIO_READ_PIN11_2(x))     /*"P54"*/
//#define PinMode_EsamMISO(x)       (GPIO_MODE_PIN11_2(x))

//#define PinEASMMOSI               _PIN11_3//_PIN5_5           //EASM通讯SPI 的MOSI脚
//#define PinWrite_EsamMOSI(x)      (GPIO_WRITE_PIN11_3(x))     /*"P55"*/
//#define PinRead_EsamMOSI(x)       (GPIO_READ_PIN11_3(x))
//#define PinMode_EsamMOSI(x)       (GPIO_MODE_PIN11_3(x))

//#define PinEASMCS               _PIN11_0//_PIN5_2//_PIN11_0       /*"EASM通讯SPI 的CS脚"*/
//#define ENABLE_ESAM()     {GPIO_WRITE_PIN11_0(0);GPIO_MODE_PIN11_0(GPIO_MODE_OUT);}
//#define DISABLE_ESAM()    {GPIO_WRITE_PIN11_0(1);GPIO_MODE_PIN11_0(GPIO_MODE_OUT);}

//#define PinEASMPower          _PIN5_0         /*"EASM电源控制脚"*/
//#define   EsamPowerOff()          {GPIO_MODE_PIN5_0(GPIO_MODE_OUT);GPIO_WRITE_PIN5_0(1);}//P50
//#define   EsamPowerOn()           {GPIO_MODE_PIN5_0(GPIO_MODE_OUT);GPIO_WRITE_PIN5_0(0);}

//#define PinIC_IO                _PIN4_2           /*"卡数据口"*/
//#define PinIC_RST               //_PIN3_4         /*"卡复位口"*/
//#define PinIC_KEY               _PIN4_3           /*"卡检测口"*/

//#define   CardFoutOpen()          //ZHUPDEBUG {ISO7816 ->CLK=0x0A;}               /*卡及ESAM的时钟输出p4[0]*/
//#define   CardFoutClose()         //ZHUPDEBUG {ISO7816 ->CLK=0x02;}

///*"***************************通讯模块相关IO口*********************************************************************"*/

//#define Pin485RE                _PIN1_6 //_PIN1_4         /*"485通道收发控制脚"*/
//#define PinRXD485               _PIN4_6         /*"485通道接收脚"*/
//#define PinTXD485              _PIN4_7         /*"485通道发送脚"*/

//#define Pin485BRE                _PIN1_6 //_PIN1_4         /*"485通道收发控制脚"*/
//#define PinRXD485B               //_PIN4_6         /*"485通道接收脚"*/
//#define PinTXD485B              //_PIN4_7         /*"485通道发送脚"*/

//#define PinCtrlWake             _PIN1_2        /*"红外电源控制"*/
////#define IRPowerPowerOff()   {GPIO_MODE_PIN1_2(GPIO_MODE_OUT);GPIO_WRITE_PIN1_2(1);}
////#define IRPowerPowerOn()    {GPIO_MODE_PIN1_2(GPIO_MODE_OUT);GPIO_WRITE_PIN1_2(0);}
//#define IRPowerPowerOff()     {GPIO_WRITE_PIN1_2(1);}
//#define IRPowerPowerOn()      {GPIO_WRITE_PIN1_2(0);}

//#define PinRXD_IR               _PIN2_2//_PIN5_4         /*"红外通道接收脚"*/
//#define PinTXD_IR               _PIN2_3//_PIN5_5         /*"红外通道发送脚"*/
//#define PinMode_IRRX(x)       (GPIO_MODE_PIN2_2(x))//
//#define PinRead_IRRX(x)       (GPIO_READ_PIN2_2(0))//

//#define PinRXD_ZB               _PIN2_6         /*"载波通道接收脚"*/
//#define PinTXD_ZB               _PIN2_7         /*"载波通道发送脚"*/

//#if(PCB_Version==RN8318_RN8306)   //高端电能质量表硬件

//#define PinSPK                    _PIN1_3         /*"蜂鸣器"*/
//#define PinWrite_Beep(x)              (GPIO_WRITE_PIN1_3(x))//

//#define PinLCDBackLight         _PIN3_1        /*"液晶背光"*/
//#define   LCDBackLightOff()      (GPIO_WRITE_PIN3_1(0))
//#define   LCDBackLightON()       (GPIO_WRITE_PIN3_1(1))

///*"****************************计量模块相关IO口*********************************************************************"*/
//#define PinCLKOUT_2M            //_PIN1_5         /*"RN8207D  CLK   "*/
//#define PinCLKOUT_8M            //_PIN4_0         /*"RN8302  CLK    "*/

// /*"RN8207电源控制"只有8302C时需要，其他版本计量芯片时无RN8207*/
//#define    PinRN8302_Power            _PIN11_5
//#define   RN8302_PowerOff()           {GPIO_MODE_PIN11_5(GPIO_MODE_OUT);GPIO_WRITE_PIN11_5(0);} //
//#define   RN8302_PowerOn()            {GPIO_MODE_PIN11_5(GPIO_MODE_OUT);GPIO_WRITE_PIN11_5(1);}

//#define   RN8207_PowerOff()           {} //
//#define   RN8207_PowerOn()            {}
//
////---rn8302-----------
//#define PinSCS_C              _PIN10_4//_PIN11_4      /*"RN8302通讯SPI 的CS脚"*/
//#define PinWrite_ADCS(x)          (GPIO_WRITE_PIN10_4(x))// p11.4
//#define PinMode_ADCS(x)           (GPIO_MODE_PIN10_4(x))

//#define PinSCLK               _PIN10_5//_PIN11_1      /*"RN8302通讯SPI 的CLK脚"*/
//#define PinWrite_ADSCLK(x)    (GPIO_WRITE_PIN10_5(x))// p11.1
//#define PinMode_ADSCLK(x)     (GPIO_MODE_PIN10_5(x))

//#define PinSDO_C              _PIN10_6//_PIN11_2        /*"RN8302通讯SPI 的MISO脚"*/
//#define PinRead_ADMISO()        (GPIO_READ_PIN10_6(0))// p11.2
//#define PinMode_ADMISO(x)     (GPIO_MODE_PIN10_6(x))

//#define PinSDI_C              _PIN10_7//_PIN11_3        /*"RN8302通讯SPI 的MOSI脚"*/
//#define PinWrite_ADSMOSI(x)     (GPIO_WRITE_PIN10_7(x))// p11.3
//#define PinMode_ADSMOSI(x)        (GPIO_MODE_PIN10_7(x))

//#define PinHSCS_C             _PIN5_2
//#define PinHSCLK_C                _PIN5_3
//#define PinHMOSI_C                _PIN5_5

//#define PinRx_JL              _PIN2_0
//#define PinTx_JL              _PIN2_1

//#define PinINTN1_C                _PIN3_2
///*"*****************************继电器模块相关IO口*********************************************************************"*/
//#define PinJump                   _PIN1_7     /*"报警指示"*/
//#define PinWrite_RelayLed(x)             (GPIO_WRITE_PIN1_7(x))   //x=0 点亮

//#define PinWarn                   _PIN4_1         /*"外置报警继电器控制"*/
//#define PinLoadRelayON          _PIN3_4       /*"继电器控制1"*/
//#define PinLoadRelayOFF         _PIN3_5       /*"继电器控制2"*/

///*"***************************存储模块相关IO口*********************************************************************"*/
///*"flash与RN8302共用SPI"*/

///*"----FLASH   SPI定义-----"*/
//#define PinFlashCLK               _PIN10_5        /*"外部Flash通讯SPI 的CLK脚"*/
//#define PinWrite_MX25LSCK(x)      (GPIO_WRITE_PIN10_5(x))// p11.1
//#define   PinMode_MX25LSCK(x)     (GPIO_MODE_PIN10_5(x))

//#define PinFlashMISO          _PIN10_6        /*"外部Flash通讯SPI 的MISO脚"*/
//#define PinWrite_MX25LMISO(x)     (GPIO_WRITE_PIN10_6(x))// p11.2
//#define PinRead_MX25LMISO(x)      (GPIO_READ_PIN10_6(x))
//#define   PinMode_MX25LMISO(x)        (GPIO_MODE_PIN10_6(x))

//#define PinFlashMOSI          _PIN10_7        /*"外部Flash通讯SPI 的MOSI脚"*/
//#define PinWrite_MX25LMOSI(x)     (GPIO_WRITE_PIN10_7(x)) // p11.3
//#define   PinMode_MX25LMOSI(x)        (GPIO_MODE_PIN10_7(x))

//#define PinFlashCS                _PIN11_4 //_PIN1_4          /*"外部Flash通讯SPI 的CS脚"*/
//#define ENABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN11_4(0);GPIO_MODE_PIN11_4(GPIO_MODE_OUT);}
//#define DISABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN11_4(1);GPIO_MODE_PIN11_4(GPIO_MODE_OUT);}

//#define   PinFLASHPower   PinRN8302_Power
//#define   FLASH_PowerOff()    {  RN8302_PowerOff(); } //flash与8302电源共用
//#define   FLASH_PowerOn()    {  RN8302_PowerOn(); }   //flash与8302电源共用

////---I2C0定义-----存储器---------------------------
//#define PinEepromSCL          _PIN1_4//_PIN5_2            /*"E2   IIC通讯SCL脚"*/
//#define PinEepromSDA          _PIN1_5//_PIN5_3            /*"E2   IIC通讯SDA脚"*/
//#define PinWrite_SDA0(x)          (GPIO_WRITE_PIN1_5(x))//( (x) ? (GPIO->PBSET = 0x00000800) : (GPIO->PBCLR = 0x00000800) )   //p5.3
//#define PinRead_SDA0(x)       (GPIO_READ_PIN1_5(0))//((GPIO->PB&0x00000800) ? (0x01) : (0x00))
//#define PinMode_SDA0(x)       (GPIO_MODE_PIN1_5(x))//( (x == GPIO_MODE_OUT) ? (GPIO->PMB &= 0xfffff7ff) : (GPIO->PMB |= 0x00000800,GPIO->PIEB &= 0xfffff7ff) )                    //对应 SDA0_IN
//#define PinWrite_SCL0(x)          (GPIO_WRITE_PIN1_4(x))//( (x) ? (GPIO->PBSET = 0x00000400) : (GPIO->PBCLR = 0x00000400) )   //对应 P5.2
//#define PinMode_SCL0(x)       (GPIO_MODE_PIN1_4(x))//((x == GPIO_MODE_OUT) ? (GPIO->PMB &= 0xfffffbff) : (GPIO->PMB |= 0x00000400) )//对应 P5.2

//#define PinZB_CTRL              _PIN11_7      /*"载波电源控制"*/
//#define PinSET_ZB               _PIN11_6        /*" 载波设置脚   "*/
//#define PinEVENOUT              _PIN4_0        /*"事件上报口"*/
//#define PinRST_ZB               _PIN5_7 //_PIN5_1         /*"载波复位脚"*/
//#define PinSTA_ZB               _PIN5_1         /*"载波状态脚"*/
//#if(ZBComFlag == 1)
//#define   PinRead_CheckZBSta(x)   GPIO_READ_PIN5_1(0)          // p5.1
//#define   PinWrite_ZBRst(x)           GPIO_WRITE_PIN5_7(x)
//#define   PinWrite_ZBEvenOut(x)   GPIO_WRITE_PIN4_0(x)    // P115
//#endif

//#else

////蜂鸣器输出
//#define PinSPK                    _PIN3_3         /*"蜂鸣器"*/
//#define PinWrite_Beep(x)              (GPIO_WRITE_PIN3_3(x))//
//
//#define PinLCDBackLight         _PIN3_2        /*"液晶背光"*/
//#define   LCDBackLightOff()      (GPIO_WRITE_PIN3_2(0))
//#define   LCDBackLightON()       (GPIO_WRITE_PIN3_2(1))

///*"****************************计量模块相关IO口*********************************************************************"*/
//#define PinMS_RST             _PIN2_0        /*"RN8302复位管脚"*/

//#define PinCLKOUT_2M            //_PIN1_5         /*"RN8207D  CLK   "*/
//#define PinCLKOUT_8M            //_PIN4_0         /*"RN8302  CLK    "*/

//#define    PinRN8302_Power            _PIN1_4
//#define   RN8302_PowerOff()           {GPIO_MODE_PIN1_4(GPIO_MODE_OUT);GPIO_WRITE_PIN1_4(0);} //
//#define   RN8302_PowerOn()            {GPIO_MODE_PIN1_4(GPIO_MODE_OUT);GPIO_WRITE_PIN1_4(1);}

//#define    PinRN8207_Power            _PIN1_5
//#define   RN8207_PowerOff()           {GPIO_MODE_PIN1_5(GPIO_MODE_OUT);GPIO_WRITE_PIN1_5(0);} //
//#define   RN8207_PowerOn()            {GPIO_MODE_PIN1_5(GPIO_MODE_OUT);GPIO_WRITE_PIN1_5(1);}

////---rn8302-----------

//#define PinSCLK                   _PIN5_3//_PIN11_1       /*"RN8302通讯SPI 的CLK脚"*/
//#define PinWrite_ADSCLK(x)    (GPIO_WRITE_PIN5_3(x))// p11.1
//#define PinMode_ADSCLK(x)     (GPIO_MODE_PIN5_3(x))

//#define PinSDO_C              _PIN5_4//_PIN11_2        /*"RN8302通讯SPI 的MISO脚"*/
//#define PinRead_ADMISO()        (GPIO_READ_PIN5_4(0))// p11.2
//#define PinMode_ADMISO(x)     (GPIO_MODE_PIN5_4(x))

//#define PinSDI_C              _PIN5_5//_PIN11_3        /*"RN8302通讯SPI 的MOSI脚"*/
//#define PinWrite_ADSMOSI(x)     (GPIO_WRITE_PIN5_5(x))// p11.3
//#define PinMode_ADSMOSI(x)        (GPIO_MODE_PIN5_5(x))

//#define PinSCS_C              _PIN5_2//_PIN11_4       /*"RN8302通讯SPI 的CS脚"*/
//#define PinWrite_ADCS(x)          (GPIO_WRITE_PIN5_2(x))// p11.4
//#define PinMode_ADCS(x)           (GPIO_MODE_PIN5_2(x))

///*"*****************************继电器模块相关IO口*********************************************************************"*/
//#define PinJump                   _PIN10_4        /*跳闸指示LED"*/
//#define PinWrite_RelayLed(x)             (GPIO_WRITE_PIN10_4(x))  //x=0 点亮

//#define PinWarn                   _PIN1_7         /*"报警继电器控制"*/
//#define PinLoadRelayON          _PIN10_6      /*"继电器控制1"*/
//#define PinLoadRelayOFF         _PIN10_5      /*"继电器控制2"*/

///*"***************************存储模块相关IO口*********************************************************************"*/
///*"flash与RN8302共用SPI"*/

///*"----FLASH   SPI定义-----"*/
//#define PinFlashCLK               _PIN5_3     /*"外部Flash通讯SPI 的CLK脚"*/
//#define PinWrite_MX25LSCK(x)      (GPIO_WRITE_PIN5_3(x))// p11.1
//#define   PinMode_MX25LSCK(x)     (GPIO_MODE_PIN5_3(x))

//#define PinFlashMISO          _PIN5_4     /*"外部Flash通讯SPI 的MISO脚"*/
//#define PinWrite_MX25LMISO(x)     (GPIO_WRITE_PIN5_4(x))// p11.2
//#define PinRead_MX25LMISO(x)      (GPIO_READ_PIN5_4(x))

//#define PinFlashMOSI          _PIN5_5     /*"外部Flash通讯SPI 的MOSI脚"*/
//#define   PinMode_MX25LMISO(x)        (GPIO_MODE_PIN5_4(x))
//#define PinWrite_MX25LMOSI(x)     (GPIO_WRITE_PIN5_5(x))  // p11.3
//#define   PinMode_MX25LMOSI(x)        (GPIO_MODE_PIN5_5(x))

//#define PinFlashCS                _PIN11_4 //_PIN1_4          /*"外部Flash通讯SPI 的CS脚"*/
//#define ENABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN11_4(0);GPIO_MODE_PIN11_4(GPIO_MODE_OUT);}
//#define DISABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN11_4(1);GPIO_MODE_PIN11_4(GPIO_MODE_OUT);}

//#define PinFLASHPower  PinRN8302_Power
//#define   FLASH_PowerOff()    { RN8207_PowerOff(); RN8302_PowerOff(); }   //flash与8302电源共用，避免8302闪脉冲，8207电源同开关
//#define   FLASH_PowerOn()    { RN8207_PowerOn(); RN8302_PowerOn(); }  //flash与8302电源共用，避免8302闪脉冲，8207电源同开关

////---I2C0定义-----存储器---------------------------
//#define PinEepromSCL          _PIN4_0//_PIN5_2            /*"E2   IIC通讯SCL脚"*/
//#define PinEepromSDA          _PIN4_1//_PIN5_3            /*"E2   IIC通讯SDA脚"*/
//#define PinWrite_SDA0(x)          (GPIO_WRITE_PIN4_1(x))//p5.3
//#define PinRead_SDA0(x)       (GPIO_READ_PIN4_1(0))//
//#define PinMode_SDA0(x)       (GPIO_MODE_PIN4_1(x))//
//#define PinWrite_SCL0(x)          (GPIO_WRITE_PIN4_0(x))//
//#define PinMode_SCL0(x)       (GPIO_MODE_PIN4_0(x))//

//#define PinZB_CTRL              _PIN10_7      /*"载波电源控制"*/
//#define PinSET_ZB               _PIN11_6        /*" 载波设置脚   "*/
//#define PinEVENOUT              _PIN11_5        /*"事件上报口"*/
//#define PinRST_ZB               _PIN5_7 //_PIN5_1         /*"载波复位脚"*/
//#define PinSTA_ZB               _PIN5_1         /*"载波状态脚"*/
//#if(ZBComFlag == 1)
//#define   PinRead_CheckZBSta(x)   GPIO_READ_PIN5_1(0)          // p5.1
//#define   PinWrite_ZBRst(x)           GPIO_WRITE_PIN5_7(x)
//#define   PinWrite_ZBEvenOut(x)   GPIO_WRITE_PIN11_5(x)   // P115
//#endif

//#endif

///*"***************************显示模块相关IO口*********************************************************************"*/
//#define PinS1                 _PIN7_3         /*"LCD  SEG脚"*/
//#define PinS2                 _PIN7_2         /*"LCD  SEG脚"*/
//#define PinS3                 _PIN7_1         /*"LCD  SEG脚"*/
//#define PinS4                 _PIN7_0         /*"LCD  SEG脚"*/
//#define PinS5                 _PIN6_7         /*"LCD  SEG脚"*/
//#define PinS6                 _PIN6_6         /*"LCD  SEG脚"*/
//#define PinS7                 _PIN6_5         /*"LCD  SEG脚"*/
//#define PinS8                 _PIN6_4         /*"LCD  SEG脚"*/
//#define PinS9                 _PIN6_3         /*"LCD  SEG脚"*/
//#define PinS10                    _PIN6_2         /*"LCD  SEG脚"*/
//#define PinS11                    _PIN6_1         /*"LCD  SEG脚"*/
//#define PinS12                    _PIN6_0         /*"LCD  SEG脚"*/
//#define PinS13                    _PIN9_7         /*"LCD  SEG脚"*/
//#define PinS14                    _PIN9_6         /*"LCD  SEG脚"*/
//#define PinS15                    _PIN9_5         /*"LCD  SEG脚"*/
//#define PinS16                    _PIN9_4         /*"LCD  SEG脚"*/
//#define PinS17                    _PIN9_3         /*"LCD  SEG脚"*/
//#define PinS18                    _PIN9_2         /*"LCD  SEG脚"*/
//#define PinS19                    _PIN9_1         /*"LCD  SEG脚"*/
//#define PinS20                    _PIN9_0         /*"LCD  SEG脚"*/
//#define PinS21                    _PIN8_7         /*"LCD  SEG脚"*/
//#define PinS22                    _PIN8_6         /*"LCD  SEG脚"*/
//#define PinS23                    _PIN8_5         /*"LCD  SEG脚"*/
//#define PinS24                    _PIN8_4         /*"LCD  SEG脚"*/
//#define PinS25                    _PIN8_3         /*"LCD  SEG脚"*/
//#define PinS26                    _PIN8_2         /*"LCD  SEG脚"*/
//#define PinS27                    _PIN8_1         /*"LCD  SEG脚"*/
//#define PinS28                    _PIN8_0         /*"LCD  SEG脚"*/
//#define PinS29                    _PIN7_7         /*"LCD  SEG脚"*/
//#define PinS30                    _PIN7_6         /*"LCD  SEG脚"*/
//#define PinS31                    _PIN7_5         /*"LCD  SEG脚"*/
//#define PinS32                    _PIN7_4         /*"LCD  SEG脚"*/
//#define PinS33                    _PIN10_3         /*"LCD  SEG脚"*/
//#define PinS34                    _PIN10_1         /*"LCD  SEG脚"*/

//#define PinCOM0                 _PIN_Seg3Com7   /*"LCD  COM脚"*/
//#define PinCOM1                 _PIN_Seg2Com6   /*"LCD  COM脚"*/
//#define PinCOM2                 _PIN_Seg1Com5   /*"LCD  COM脚"*/
//#define PinCOM3                 _PIN_Seg0Com4   /*"LCD  COM脚"*/

//#endif

#define ON      1
#define OFF     0

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

//===GPIO定义================================
//typedef enum
//{
//  GPIO_MODE_OUT   = 0,
//  GPIO_MODE_IN    = 1
//} eGPIOMode_TypeDef;

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
extern void fnRTCDrive_Delay(void);
extern void fnINTTC0_RCInit(void);
extern void fnGPIO_Configuration(void);
extern void fnINTTC2_Star(void);
extern void fnINTTC2_Stop(void);
extern void SystemDelay(u16 t);
extern void fnDelayMs(u16 t);
extern void fnLVD_Init(void);
extern void fnINTRTC_Sleep(void);
extern void fnRTCDrive_Init(void);
extern ErrorStatus fnSysClock_Read(sDF01 *Clock);
extern ErrorStatus fnSysClock_Write(sDF01 *Clock);

extern void fnSysDateTimes(sDate_time_s_TypeDef * ptime);
//extern void fnINTTC1_Star(void);
//extern void fnINTTC1_Stop(void);
extern ErrorStatus fnSocEE_Write(u32 Dst, u8 *Src, u32 DatLen, u8 Repeat);
extern ErrorStatus fnSocEE_Read(u8 *Dst, u32 Src, u32 DatLen, u8 Repeat);

extern ErrorStatus fnSocRegCheck(bool InitAll, u8 AdOrRmItem, u32 regAddr);
extern ErrorStatus fnSocRegCheckAddAll(void);

extern void fnPowerOn_DrvieInit(void);
#endif  //_XTARGER_H
