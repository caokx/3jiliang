#ifndef  _XTARGER_H
#define  _XTARGER_H

#define TIMEOUT_DATA 0x3ff

#ifndef __SocEE_H__
#define __SocEE_H__
//�洢�����Ͷ��壬ҳ��С����
#define EEPROM24C04MAXSize      (4*128)  //ÿ1KbitΪ128�ֽ�
#define EEPROM24C128MAXSize     (128*128)   //ÿ1KbitΪ128�ֽ�
#define EEPROM24C64MAXSize      (64*128)    //ÿ1KbitΪ128�ֽ�
#define EEPROM24C256MAXSize     (256*128)   //ÿ1KbitΪ128�ֽ�
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

#define PinISP                  _PIN3_0         /*"ISP���"*/
#define PinAD_3V6               _PIN0_0         /*"ʱ�ӵ�ص�ѹ����"*/
#define PinAD_6V                _PIN_NULL       /*"�����ص�ѹ����"*/
#define PinLVD                  _PIN0_3         /*"ϵͳ��Դ���"*/

#define PinRelayCheck           _PIN_NULL           /*"�̵������"*/
#define PinRead_RelayGataCheck(x)   1/*"�̵������P01 "*/

#define PinSCAP_VCTRL           _PIN_NULL

//P30���
#define PinWrite_DEBUGOut           {Rn8xxx_GPIO_CfgFun(_PIN3_0,_NORMALIO);Rn8xxx_GPIO_CfgIOMode( _PIN3_0 , GPIO_MODE_OUT , NORMAL_OUT ); }
#define PinWrite_DEBUGOutput(x)     (GPIO_WRITE_PIN3_0(x))

#define PinSCAP_VCTRL           _PIN_NULL
#define SCAP_VCTRL_PowerOn()
#define SCAP_VCTRL_PowerOff()

//---��������--------------------------------

#define PinKTURA                _PIN_NULL       /*"����up"*/
#define PinRead_KeyTurnA(x)     1               /*"����up    p1.0"*/

#define PinKTURB                _PIN_NULL       /*"����down"*/
#define PinRead_KeyTurnB(x)     1               /*"����down     p1.1"*/

#define PinKCOVER               _PIN0_1         /*"���ϸǼ��" dyf ԭ��ͼ�ǶԵģ�PCB���Ĳ��ԣ��ŵ�λ�ò��ԣ�������ť���෴ */
#define PinRead_KeyShell(x)     (GPIO_READ_PIN0_1(0))   /* dyf ͬ������ */

#define PinKBTMBOX              _PIN3_1         /*"���˸Ǽ��" dyf ԭ��ͼ�ǶԵģ�PCB���Ĳ��ԣ��ŵ�λ�ò���*/
#define PinRead_KeyJunBox(x)    (GPIO_READ_PIN3_1(0))   /* dyf ͬ������ */

#define PinMR_Check             _PIN14_2        /*" �ż�� "*/
#define PinRead_StrongMan(x)     (GPIO_READ_PIN14_2(0))

#define PinClkOut               _PIN3_2         /*"���������"*/
#define PinWrite_OpticalOutMulFun(x)   (GPIO_WRITE_PIN3_2(x))

/*"*****************************����ģ�����IO��*********************************************************************"*/

/*"EASM  IO�ڶ���"*/
#define PinEsamClk              _PIN10_5                    /*"Esamʱ�ӽ�"*/
#define PinWrite_EsamSCK(x)     (GPIO_WRITE_PIN10_5(x))
#define PinMode_EsamSCK(x)      (GPIO_MODE_PIN10_5(x))

#define PinEASMMISO             _PIN10_6                    //EASMͨѶSPI ��MISO��
#define PinWrite_EsamMISO(x)    (GPIO_WRITE_PIN10_6(x))
#define PinRead_EsamMISO(x)     (GPIO_READ_PIN10_6(x))
#define PinMode_EsamMISO(x)     (GPIO_MODE_PIN10_6(x))

#define PinEASMMOSI             _PIN10_7                    //EASMͨѶSPI ��MOSI��
#define PinWrite_EsamMOSI(x)    (GPIO_WRITE_PIN10_7(x))
#define PinRead_EsamMOSI(x)     (GPIO_READ_PIN10_7(x))
#define PinMode_EsamMOSI(x)     (GPIO_MODE_PIN10_7(x))

#define PinEASMCS               _PIN10_4                    /*"EASMͨѶSPI ��CS��"*/
#define ENABLE_ESAM()   {GPIO_WRITE_PIN10_4(0);GPIO_MODE_PIN10_4(GPIO_MODE_OUT);}
#define DISABLE_ESAM()  {GPIO_WRITE_PIN10_4(1);GPIO_MODE_PIN10_4(GPIO_MODE_OUT);}

#define PinEASMPower            _PIN5_7         /*"EASM��Դ���ƽ�"*/
#define EsamPowerOff()          {GPIO_MODE_PIN5_7(GPIO_MODE_OUT);GPIO_WRITE_PIN5_7(1);}
#define EsamPowerOn()           {GPIO_MODE_PIN5_7(GPIO_MODE_OUT);GPIO_WRITE_PIN5_7(0);}

#define PinIC_IO                _PIN_NULL       /*"�����ݿ�"*/
#define PinIC_RST               _PIN_NULL       /*"����λ��"*/
#define PinIC_KEY               _PIN_NULL       /*"������"*/

#define CardFoutOpen()          /*����ESAM��ʱ�����p4[0]*/
#define CardFoutClose()

/*"***************************ͨѶģ�����IO��*********************************************************************"*/

#define Pin485RE                _PIN_NULL       /*"485ͨ���շ����ƽ�"*/
#define PinRXD485               _PIN2_0         /*"485ͨ�����ս�"*/
#define PinTXD485               _PIN2_1         /*"485ͨ�����ͽ�"*/

#define Pin485BRE               _PIN_NULL       /*"485ͨ���շ����ƽ�"*/
#define PinRXD485B              _PIN_NULL       /*"485ͨ�����ս�"*/
#define PinTXD485B              _PIN_NULL       /*"485ͨ�����ͽ�"*/

#define PinCtrlWake             _PIN_NULL       /*"�����Դ����"*/
#define IRPowerPowerOff()
#define IRPowerPowerOn()

#define PinRXD_IR               _PIN_NULL       /*"����ͨ�����ս�"*/
#define PinTXD_IR               _PIN_NULL       /*"����ͨ�����ͽ�"*/
#define PinMode_IRRX(x)
#define PinRead_IRRX(x)         1

#define PinRXD_ZB               _PIN_NULL         /*"�ز�ͨ�����ս�"*/
#define PinTXD_ZB               _PIN_NULL         /*"�ز�ͨ�����ͽ�"*/

//���������
#define PinSPK                  _PIN_NULL       /*"������"*/
#define PinWrite_Beep(x)

#define PinLCDBackLight         _PIN_NULL       /*"Һ������"*/
#define LCDBackLightOff()
#define LCDBackLightON()

/*"****************************����ģ�����IO��*********************************************************************"*/
#define PinMS_RST               _PIN_NULL //_PIN2_0         /*"RN8302��λ�ܽ�"*/

#define PinCLKOUT_2M            _PIN_NULL       /*"RN8207D  CLK   "*/
#define PinCLKOUT_8M            _PIN_NULL       /*"RN8302  CLK    "*/

#define PinRN8302_Power         _PIN8_4
#define RN8302_PowerOff()       {GPIO_MODE_PIN8_4(GPIO_MODE_OUT);GPIO_WRITE_PIN8_4(1);}
#define RN8302_PowerOn()        {GPIO_MODE_PIN8_4(GPIO_MODE_OUT);GPIO_WRITE_PIN8_4(0);}

#define PinRN8207_Power         _PIN_NULL
#define RN8207_PowerOff()
#define RN8207_PowerOn()

//---rn8302-----------
#define PinSCLK                 _PIN11_4            /*"RN8302ͨѶSPI ��CLK��"*/
#define PinWrite_ADSCLK(x)      (GPIO_WRITE_PIN11_4(x))
#define PinMode_ADSCLK(x)       (GPIO_MODE_PIN11_4(x))

#define PinSDO_C                _PIN4_6         /*"RN8302ͨѶSPI ��MISO��"*/
#define PinRead_ADMISO()        (GPIO_READ_PIN4_6(0))
#define PinMode_ADMISO(x)       (GPIO_MODE_PIN4_6(x))

#define PinSDI_C                _PIN14_1            /*"RN8302ͨѶSPI ��MOSI��"*/
#define PinWrite_ADSMOSI(x)     (GPIO_WRITE_PIN14_1(x))
#define PinMode_ADSMOSI(x)      (GPIO_MODE_PIN14_1(x))

#define PinSCS_C                _PIN11_2            /*"RN8302ͨѶSPI ��CS��"*/
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

/*"*****************************�̵���ģ�����IO��*********************************************************************"*/
#define PinJump                 _PIN_NULL       /*��բָʾLED"*/
#define PinWrite_RelayLed(x)

#define PinWarn                 _PIN_NULL       /*"�����̵�������"*/
#define PinLoadRelayON          _PIN_NULL
#define PinLoadRelayOFF         _PIN_NULL

/*"***************************�洢ģ�����IO��*********************************************************************"*/
#define PinFlashCLK             _PIN2_6     /*"�ⲿFlashͨѶSPI ��CLK��"*/
#define PinWrite_MX25LSCK(x)    (GPIO_WRITE_PIN2_6(x))
#define PinMode_MX25LSCK(x)     (GPIO_MODE_PIN2_6(x))

#define PinFlashMISO            _PIN1_2     /*"�ⲿFlashͨѶSPI ��MISO��"*/
#define PinWrite_MX25LMISO(x)   (GPIO_WRITE_PIN1_2(x))
#define PinRead_MX25LMISO(x)        (GPIO_READ_PIN1_2(x))
#define PinMode_MX25LMISO(x)        (GPIO_MODE_PIN1_2(x))

#define PinFlashMOSI            _PIN1_0     /*"�ⲿFlashͨѶSPI ��MOSI��"*/
#define PinWrite_MX25LMOSI(x)   (GPIO_WRITE_PIN1_0(x))
#define PinMode_MX25LMOSI(x)        (GPIO_MODE_PIN1_0(x))

#define PinFlashCS              _PIN1_1     /*"�ⲿFlashͨѶSPI ��CS��"*/
#define ENABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN1_1(0);GPIO_MODE_PIN1_1(GPIO_MODE_OUT);}
#define DISABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN1_1(1);GPIO_MODE_PIN1_1(GPIO_MODE_OUT);}

#define PinWrite_MX25LSCK_BitBandAddr   0x520000D8
#define PinWrite_MX25LMOSI_BitBandAddr  0x520000A0
#define PinWrite_MX25LMISO_BitBandAddr  0x520000A8
#define PinFLASHPower           _PIN11_5    //Flash��Դ�����
#define FLASH_PowerOff()    {  GPIO_MODE_PIN11_5(GPIO_MODE_OUT);GPIO_WRITE_PIN11_5(1); }    //flash��8302��Դ����
#define FLASH_PowerOn()    {  GPIO_MODE_PIN11_5(GPIO_MODE_OUT);GPIO_WRITE_PIN11_5(0); } //flash��8302��Դ����
//---I2C0����-----�洢��---------------------------
#define PinEepromSCL            _PIN2_2             /*"E2   IICͨѶSCL��"*/
#define PinEepromSDA            _PIN2_3             /*"E2   IICͨѶSDA��"*/
#define PinWrite_SDA0(x)        (GPIO_WRITE_PIN2_3(x))
#define PinRead_SDA0(x)         (GPIO_READ_PIN2_3(0))
#define PinMode_SDA0(x)         (GPIO_MODE_PIN2_3(x))
#define PinWrite_SCL0(x)        (GPIO_WRITE_PIN2_2(x))
#define PinMode_SCL0(x)         (GPIO_MODE_PIN2_2(x))
/*"***************************�ز�ģ�����IO��*********************************************************************"*/
#define PinZB_CTRL              _PIN_NULL       /*"�ز���Դ����"*/
#define PinSET_ZB               _PIN_NULL       /*" �ز����ý�   "*/
#define PinEVENOUT              _PIN_NULL       /*"�¼��ϱ���"*/
#define PinRST_ZB               _PIN_NULL       /*"�ز���λ��"*/
#define PinSTA_ZB               _PIN_NULL       /*"�ز�״̬��"*/
#if(ZBComFlag == 1)
#define PinRead_CheckZBSta(x)   0
#define PinWrite_ZBRst(x)
#define PinWrite_ZBEvenOut(x)
#endif
#define PinWrite_ZBEvenOut(x)

/*"***************************����չģ��ͨ�Žӿڣ������������IO��*********************************************************************"*/
#define PinExModuleClk              _PIN4_1 //�ⲿ��չģ��SPI��CLK��
#define PinWrite_ExModuleSCK(x)     (GPIO_WRITE_PIN4_1(x))
#define PinMode_ExModuleSCK(x)      (GPIO_MODE_PIN4_1(x))

#define PinExModuleMOSI             _PIN4_3 //�ⲿ��չģ��SPI��MOSI��
#define PinWrite_ExModuleMOSI(x)    (GPIO_WRITE_PIN4_3(x))
#define PinRead_ExModuleMOSI(x)     (GPIO_READ_PIN4_3(x))
#define PinMode_ExModuleMOSI(x)     (GPIO_MODE_PIN4_3(x))

#define PinExModuleCS               _PIN4_0 //�ⲿ��չSPI��CS��
#define ENABLE_ExModule()           {GPIO_WRITE_PIN4_0(0);GPIO_MODE_PIN4_0(GPIO_MODE_OUT);}
#define DISABLE_ExModule()          {GPIO_WRITE_PIN4_0(1);GPIO_MODE_PIN4_0(GPIO_MODE_OUT);}

/*"***************************�����ģ��ͨ�Žӿ�*********************************************************************"*/

#define PinManageModuleRSTM     _PIN3_0 //����ģ�鸴λ�ܽ�
#define PinWrite_PinManageModuleRSTM(x)     (GPIO_WRITE_PIN3_0(x))
#define PinMode_PinManageModuleRSTM(x)      (GPIO_MODE_PIN3_0(x))

#define PinManageModuleLVDOUT       _PIN2_7 //����״̬����ܽ�
#define PinWrite_ManageModuleLVDOUT(x)      (GPIO_WRITE_PIN2_7(x))
#define PinMode_ManageModuleLVDOUT(x)       (GPIO_MODE_PIN2_7(x))

#define PinManageModuleCOMRQIN  _PIN11_6    // ģ��γ����
#define PinRead_ManageModuleCOMRQIN(x)  (GPIO_READ_PIN11_6(0))

#define PinManageModuleCS           _PIN5_2
#define PinManageModuleCLK      _PIN5_3
#define PinManageModuleMISO     _PIN5_4
#define PinManageModuleMOSI     _PIN5_5

/*"***************************�����оƬͨ�Žӿ�*********************************************************************"*/

#define PinTmpSDA           _PIN8_0 //����оƬIIC-SDA�ܽ�
#define PinTmpSCL           _PIN8_1 //����оƬIIC-SCL�ܽ�

#define PinWrite_TmpSDA(x)          (GPIO_WRITE_PIN8_0(x))
#define PinRead_TmpSDA(x)           (GPIO_READ_PIN8_0(0))
#define PinMode_TmpSDA(x)           (GPIO_MODE_PIN8_0(x))
#define PinWrite_TmpSCL(x)          (GPIO_WRITE_PIN8_1(x))
#define PinMode_TmpSCL(x)           (GPIO_MODE_PIN8_1(x))

/*"***************************��ʾģ�����IO��*********************************************************************"*/
#define PinS1                   _PIN_NULL       /*"LCD  SEG��"*/
#define PinS2                   _PIN_NULL       /*"LCD  SEG��"*/
#define PinS3                   _PIN_NULL       /*"LCD  SEG��"*/
#define PinS4                   _PIN_NULL       /*"LCD  SEG��"*/
#define PinS5                   _PIN_NULL       /*"LCD  SEG��"*/
#define PinS6                   _PIN_NULL       /*"LCD  SEG��"*/
#define PinS7                   _PIN_NULL       /*"LCD  SEG��"*/
#define PinS8                   _PIN_NULL       /*"LCD  SEG��"*/
#define PinS9                   _PIN_NULL       /*"LCD  SEG��"*/
#define PinS10                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS11                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS12                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS13                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS14                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS15                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS16                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS17                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS18                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS19                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS20                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS21                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS22                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS23                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS24                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS25                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS26                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS27                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS28                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS29                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS30                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS31                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS32                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS33                  _PIN_NULL       /*"LCD  SEG��"*/
#define PinS34                  _PIN_NULL       /*"LCD  SEG��"*/

#define PinCOM0                 _PIN_NULL       /*"LCD  COM��"*/
#define PinCOM1                 _PIN_NULL       /*"LCD  COM��"*/
#define PinCOM2                 _PIN_NULL       /*"LCD  COM��"*/
#define PinCOM3                 _PIN_NULL       /*"LCD  COM��"*/

//#else

//#define PinSWDCLK                  _PIN2_4
//#define PinSWDIO                  _PIN2_5

//#define PinISP                  _PIN3_0        /*"ISP���"*/
//#define PinAD_3V6             _PIN0_0         /*"ʱ�ӵ�ص�ѹ����"*/
//#define PinAD_6V              _PIN0_2         /*"�����ص�ѹ����"*/
//#define PinLVD                    _PIN0_3         /*"ϵͳ��Դ���"*/

//#define PinRelayCheck         _PIN0_1         /*"�̵������"*/
//#define PinRead_RelayGataCheck(x)   (GPIO_READ_PIN0_1(0)) /*"�̵������P01 "*/

////P30���
//#define   PinWrite_DEBUGOut           {Rn8xxx_GPIO_CfgFun(_PIN3_0,_NORMALIO);Rn8xxx_GPIO_CfgIOMode( _PIN3_0 , GPIO_MODE_OUT , NORMAL_OUT ); }
//#define   PinWrite_DEBUGOutput(x)     (GPIO_WRITE_PIN3_0(x))

////---��������--------------------------------

//#define PinKTURA                _PIN1_0        /*"����up"*/
//#define PinRead_KeyTurnA(x)       (GPIO_READ_PIN1_0(0))   /*"����up    p1.0"*/

//#define PinKTURB                _PIN1_1        /*"����down"*/
//#define PinRead_KeyTurnB(x)       (GPIO_READ_PIN1_1(0))   /*"����down     p1.1"*/

//#define PinKCOVER             _PIN4_5         /*"���ϸǼ��"*/
//#define PinRead_KeyShell(x)       (GPIO_READ_PIN4_5(0))   /*"���ϸǼ��p45"*/

//#define PinKBTMBOX                _PIN4_4         /*"���˸Ǽ��"*/
//#define PinRead_KeyJunBox(x)  (GPIO_READ_PIN4_4(0))       /*"���˸Ǽ��p44"*/

//#define PinMR_Check               _PIN0_4         /*" �ż�� "*/
//#define PinRead_StrongMan(x)   (GPIO_READ_PIN0_4(0))      /*" �ż�� P04  "*/

//#define PinClkOut             _PIN5_6         /*"���������"*/
//#define PinWrite_OpticalOutMulFun(x)   (GPIO_WRITE_PIN5_6(x))

///*"*****************************����ģ�����IO��*********************************************************************"*/

///*"EASM  IO�ڶ���"*/
//#define PinEsamClk                _PIN11_1//_PIN5_3//_PIN1_3          /*"Esamʱ�ӽ�"*/
//#define PinWrite_EsamSCK(x)   (GPIO_WRITE_PIN11_1(x))     /*"P53"*/
//#define PinMode_EsamSCK(x)        (GPIO_MODE_PIN11_1(x))

//#define PinEASMMISO               _PIN11_2//_PIN5_4           //EASMͨѶSPI ��MISO��
//#define PinWrite_EsamMISO(x)      (GPIO_WRITE_PIN11_2(x))     /*"P54"*/
//#define PinRead_EsamMISO(x)     (GPIO_READ_PIN11_2(x))     /*"P54"*/
//#define PinMode_EsamMISO(x)       (GPIO_MODE_PIN11_2(x))

//#define PinEASMMOSI               _PIN11_3//_PIN5_5           //EASMͨѶSPI ��MOSI��
//#define PinWrite_EsamMOSI(x)      (GPIO_WRITE_PIN11_3(x))     /*"P55"*/
//#define PinRead_EsamMOSI(x)       (GPIO_READ_PIN11_3(x))
//#define PinMode_EsamMOSI(x)       (GPIO_MODE_PIN11_3(x))

//#define PinEASMCS               _PIN11_0//_PIN5_2//_PIN11_0       /*"EASMͨѶSPI ��CS��"*/
//#define ENABLE_ESAM()     {GPIO_WRITE_PIN11_0(0);GPIO_MODE_PIN11_0(GPIO_MODE_OUT);}
//#define DISABLE_ESAM()    {GPIO_WRITE_PIN11_0(1);GPIO_MODE_PIN11_0(GPIO_MODE_OUT);}

//#define PinEASMPower          _PIN5_0         /*"EASM��Դ���ƽ�"*/
//#define   EsamPowerOff()          {GPIO_MODE_PIN5_0(GPIO_MODE_OUT);GPIO_WRITE_PIN5_0(1);}//P50
//#define   EsamPowerOn()           {GPIO_MODE_PIN5_0(GPIO_MODE_OUT);GPIO_WRITE_PIN5_0(0);}

//#define PinIC_IO                _PIN4_2           /*"�����ݿ�"*/
//#define PinIC_RST               //_PIN3_4         /*"����λ��"*/
//#define PinIC_KEY               _PIN4_3           /*"������"*/

//#define   CardFoutOpen()          //ZHUPDEBUG {ISO7816 ->CLK=0x0A;}               /*����ESAM��ʱ�����p4[0]*/
//#define   CardFoutClose()         //ZHUPDEBUG {ISO7816 ->CLK=0x02;}

///*"***************************ͨѶģ�����IO��*********************************************************************"*/

//#define Pin485RE                _PIN1_6 //_PIN1_4         /*"485ͨ���շ����ƽ�"*/
//#define PinRXD485               _PIN4_6         /*"485ͨ�����ս�"*/
//#define PinTXD485              _PIN4_7         /*"485ͨ�����ͽ�"*/

//#define Pin485BRE                _PIN1_6 //_PIN1_4         /*"485ͨ���շ����ƽ�"*/
//#define PinRXD485B               //_PIN4_6         /*"485ͨ�����ս�"*/
//#define PinTXD485B              //_PIN4_7         /*"485ͨ�����ͽ�"*/

//#define PinCtrlWake             _PIN1_2        /*"�����Դ����"*/
////#define IRPowerPowerOff()   {GPIO_MODE_PIN1_2(GPIO_MODE_OUT);GPIO_WRITE_PIN1_2(1);}
////#define IRPowerPowerOn()    {GPIO_MODE_PIN1_2(GPIO_MODE_OUT);GPIO_WRITE_PIN1_2(0);}
//#define IRPowerPowerOff()     {GPIO_WRITE_PIN1_2(1);}
//#define IRPowerPowerOn()      {GPIO_WRITE_PIN1_2(0);}

//#define PinRXD_IR               _PIN2_2//_PIN5_4         /*"����ͨ�����ս�"*/
//#define PinTXD_IR               _PIN2_3//_PIN5_5         /*"����ͨ�����ͽ�"*/
//#define PinMode_IRRX(x)       (GPIO_MODE_PIN2_2(x))//
//#define PinRead_IRRX(x)       (GPIO_READ_PIN2_2(0))//

//#define PinRXD_ZB               _PIN2_6         /*"�ز�ͨ�����ս�"*/
//#define PinTXD_ZB               _PIN2_7         /*"�ز�ͨ�����ͽ�"*/

//#if(PCB_Version==RN8318_RN8306)   //�߶˵���������Ӳ��

//#define PinSPK                    _PIN1_3         /*"������"*/
//#define PinWrite_Beep(x)              (GPIO_WRITE_PIN1_3(x))//

//#define PinLCDBackLight         _PIN3_1        /*"Һ������"*/
//#define   LCDBackLightOff()      (GPIO_WRITE_PIN3_1(0))
//#define   LCDBackLightON()       (GPIO_WRITE_PIN3_1(1))

///*"****************************����ģ�����IO��*********************************************************************"*/
//#define PinCLKOUT_2M            //_PIN1_5         /*"RN8207D  CLK   "*/
//#define PinCLKOUT_8M            //_PIN4_0         /*"RN8302  CLK    "*/

// /*"RN8207��Դ����"ֻ��8302Cʱ��Ҫ�������汾����оƬʱ��RN8207*/
//#define    PinRN8302_Power            _PIN11_5
//#define   RN8302_PowerOff()           {GPIO_MODE_PIN11_5(GPIO_MODE_OUT);GPIO_WRITE_PIN11_5(0);} //
//#define   RN8302_PowerOn()            {GPIO_MODE_PIN11_5(GPIO_MODE_OUT);GPIO_WRITE_PIN11_5(1);}

//#define   RN8207_PowerOff()           {} //
//#define   RN8207_PowerOn()            {}
//
////---rn8302-----------
//#define PinSCS_C              _PIN10_4//_PIN11_4      /*"RN8302ͨѶSPI ��CS��"*/
//#define PinWrite_ADCS(x)          (GPIO_WRITE_PIN10_4(x))// p11.4
//#define PinMode_ADCS(x)           (GPIO_MODE_PIN10_4(x))

//#define PinSCLK               _PIN10_5//_PIN11_1      /*"RN8302ͨѶSPI ��CLK��"*/
//#define PinWrite_ADSCLK(x)    (GPIO_WRITE_PIN10_5(x))// p11.1
//#define PinMode_ADSCLK(x)     (GPIO_MODE_PIN10_5(x))

//#define PinSDO_C              _PIN10_6//_PIN11_2        /*"RN8302ͨѶSPI ��MISO��"*/
//#define PinRead_ADMISO()        (GPIO_READ_PIN10_6(0))// p11.2
//#define PinMode_ADMISO(x)     (GPIO_MODE_PIN10_6(x))

//#define PinSDI_C              _PIN10_7//_PIN11_3        /*"RN8302ͨѶSPI ��MOSI��"*/
//#define PinWrite_ADSMOSI(x)     (GPIO_WRITE_PIN10_7(x))// p11.3
//#define PinMode_ADSMOSI(x)        (GPIO_MODE_PIN10_7(x))

//#define PinHSCS_C             _PIN5_2
//#define PinHSCLK_C                _PIN5_3
//#define PinHMOSI_C                _PIN5_5

//#define PinRx_JL              _PIN2_0
//#define PinTx_JL              _PIN2_1

//#define PinINTN1_C                _PIN3_2
///*"*****************************�̵���ģ�����IO��*********************************************************************"*/
//#define PinJump                   _PIN1_7     /*"����ָʾ"*/
//#define PinWrite_RelayLed(x)             (GPIO_WRITE_PIN1_7(x))   //x=0 ����

//#define PinWarn                   _PIN4_1         /*"���ñ����̵�������"*/
//#define PinLoadRelayON          _PIN3_4       /*"�̵�������1"*/
//#define PinLoadRelayOFF         _PIN3_5       /*"�̵�������2"*/

///*"***************************�洢ģ�����IO��*********************************************************************"*/
///*"flash��RN8302����SPI"*/

///*"----FLASH   SPI����-----"*/
//#define PinFlashCLK               _PIN10_5        /*"�ⲿFlashͨѶSPI ��CLK��"*/
//#define PinWrite_MX25LSCK(x)      (GPIO_WRITE_PIN10_5(x))// p11.1
//#define   PinMode_MX25LSCK(x)     (GPIO_MODE_PIN10_5(x))

//#define PinFlashMISO          _PIN10_6        /*"�ⲿFlashͨѶSPI ��MISO��"*/
//#define PinWrite_MX25LMISO(x)     (GPIO_WRITE_PIN10_6(x))// p11.2
//#define PinRead_MX25LMISO(x)      (GPIO_READ_PIN10_6(x))
//#define   PinMode_MX25LMISO(x)        (GPIO_MODE_PIN10_6(x))

//#define PinFlashMOSI          _PIN10_7        /*"�ⲿFlashͨѶSPI ��MOSI��"*/
//#define PinWrite_MX25LMOSI(x)     (GPIO_WRITE_PIN10_7(x)) // p11.3
//#define   PinMode_MX25LMOSI(x)        (GPIO_MODE_PIN10_7(x))

//#define PinFlashCS                _PIN11_4 //_PIN1_4          /*"�ⲿFlashͨѶSPI ��CS��"*/
//#define ENABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN11_4(0);GPIO_MODE_PIN11_4(GPIO_MODE_OUT);}
//#define DISABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN11_4(1);GPIO_MODE_PIN11_4(GPIO_MODE_OUT);}

//#define   PinFLASHPower   PinRN8302_Power
//#define   FLASH_PowerOff()    {  RN8302_PowerOff(); } //flash��8302��Դ����
//#define   FLASH_PowerOn()    {  RN8302_PowerOn(); }   //flash��8302��Դ����

////---I2C0����-----�洢��---------------------------
//#define PinEepromSCL          _PIN1_4//_PIN5_2            /*"E2   IICͨѶSCL��"*/
//#define PinEepromSDA          _PIN1_5//_PIN5_3            /*"E2   IICͨѶSDA��"*/
//#define PinWrite_SDA0(x)          (GPIO_WRITE_PIN1_5(x))//( (x) ? (GPIO->PBSET = 0x00000800) : (GPIO->PBCLR = 0x00000800) )   //p5.3
//#define PinRead_SDA0(x)       (GPIO_READ_PIN1_5(0))//((GPIO->PB&0x00000800) ? (0x01) : (0x00))
//#define PinMode_SDA0(x)       (GPIO_MODE_PIN1_5(x))//( (x == GPIO_MODE_OUT) ? (GPIO->PMB &= 0xfffff7ff) : (GPIO->PMB |= 0x00000800,GPIO->PIEB &= 0xfffff7ff) )                    //��Ӧ SDA0_IN
//#define PinWrite_SCL0(x)          (GPIO_WRITE_PIN1_4(x))//( (x) ? (GPIO->PBSET = 0x00000400) : (GPIO->PBCLR = 0x00000400) )   //��Ӧ P5.2
//#define PinMode_SCL0(x)       (GPIO_MODE_PIN1_4(x))//((x == GPIO_MODE_OUT) ? (GPIO->PMB &= 0xfffffbff) : (GPIO->PMB |= 0x00000400) )//��Ӧ P5.2

//#define PinZB_CTRL              _PIN11_7      /*"�ز���Դ����"*/
//#define PinSET_ZB               _PIN11_6        /*" �ز����ý�   "*/
//#define PinEVENOUT              _PIN4_0        /*"�¼��ϱ���"*/
//#define PinRST_ZB               _PIN5_7 //_PIN5_1         /*"�ز���λ��"*/
//#define PinSTA_ZB               _PIN5_1         /*"�ز�״̬��"*/
//#if(ZBComFlag == 1)
//#define   PinRead_CheckZBSta(x)   GPIO_READ_PIN5_1(0)          // p5.1
//#define   PinWrite_ZBRst(x)           GPIO_WRITE_PIN5_7(x)
//#define   PinWrite_ZBEvenOut(x)   GPIO_WRITE_PIN4_0(x)    // P115
//#endif

//#else

////���������
//#define PinSPK                    _PIN3_3         /*"������"*/
//#define PinWrite_Beep(x)              (GPIO_WRITE_PIN3_3(x))//
//
//#define PinLCDBackLight         _PIN3_2        /*"Һ������"*/
//#define   LCDBackLightOff()      (GPIO_WRITE_PIN3_2(0))
//#define   LCDBackLightON()       (GPIO_WRITE_PIN3_2(1))

///*"****************************����ģ�����IO��*********************************************************************"*/
//#define PinMS_RST             _PIN2_0        /*"RN8302��λ�ܽ�"*/

//#define PinCLKOUT_2M            //_PIN1_5         /*"RN8207D  CLK   "*/
//#define PinCLKOUT_8M            //_PIN4_0         /*"RN8302  CLK    "*/

//#define    PinRN8302_Power            _PIN1_4
//#define   RN8302_PowerOff()           {GPIO_MODE_PIN1_4(GPIO_MODE_OUT);GPIO_WRITE_PIN1_4(0);} //
//#define   RN8302_PowerOn()            {GPIO_MODE_PIN1_4(GPIO_MODE_OUT);GPIO_WRITE_PIN1_4(1);}

//#define    PinRN8207_Power            _PIN1_5
//#define   RN8207_PowerOff()           {GPIO_MODE_PIN1_5(GPIO_MODE_OUT);GPIO_WRITE_PIN1_5(0);} //
//#define   RN8207_PowerOn()            {GPIO_MODE_PIN1_5(GPIO_MODE_OUT);GPIO_WRITE_PIN1_5(1);}

////---rn8302-----------

//#define PinSCLK                   _PIN5_3//_PIN11_1       /*"RN8302ͨѶSPI ��CLK��"*/
//#define PinWrite_ADSCLK(x)    (GPIO_WRITE_PIN5_3(x))// p11.1
//#define PinMode_ADSCLK(x)     (GPIO_MODE_PIN5_3(x))

//#define PinSDO_C              _PIN5_4//_PIN11_2        /*"RN8302ͨѶSPI ��MISO��"*/
//#define PinRead_ADMISO()        (GPIO_READ_PIN5_4(0))// p11.2
//#define PinMode_ADMISO(x)     (GPIO_MODE_PIN5_4(x))

//#define PinSDI_C              _PIN5_5//_PIN11_3        /*"RN8302ͨѶSPI ��MOSI��"*/
//#define PinWrite_ADSMOSI(x)     (GPIO_WRITE_PIN5_5(x))// p11.3
//#define PinMode_ADSMOSI(x)        (GPIO_MODE_PIN5_5(x))

//#define PinSCS_C              _PIN5_2//_PIN11_4       /*"RN8302ͨѶSPI ��CS��"*/
//#define PinWrite_ADCS(x)          (GPIO_WRITE_PIN5_2(x))// p11.4
//#define PinMode_ADCS(x)           (GPIO_MODE_PIN5_2(x))

///*"*****************************�̵���ģ�����IO��*********************************************************************"*/
//#define PinJump                   _PIN10_4        /*��բָʾLED"*/
//#define PinWrite_RelayLed(x)             (GPIO_WRITE_PIN10_4(x))  //x=0 ����

//#define PinWarn                   _PIN1_7         /*"�����̵�������"*/
//#define PinLoadRelayON          _PIN10_6      /*"�̵�������1"*/
//#define PinLoadRelayOFF         _PIN10_5      /*"�̵�������2"*/

///*"***************************�洢ģ�����IO��*********************************************************************"*/
///*"flash��RN8302����SPI"*/

///*"----FLASH   SPI����-----"*/
//#define PinFlashCLK               _PIN5_3     /*"�ⲿFlashͨѶSPI ��CLK��"*/
//#define PinWrite_MX25LSCK(x)      (GPIO_WRITE_PIN5_3(x))// p11.1
//#define   PinMode_MX25LSCK(x)     (GPIO_MODE_PIN5_3(x))

//#define PinFlashMISO          _PIN5_4     /*"�ⲿFlashͨѶSPI ��MISO��"*/
//#define PinWrite_MX25LMISO(x)     (GPIO_WRITE_PIN5_4(x))// p11.2
//#define PinRead_MX25LMISO(x)      (GPIO_READ_PIN5_4(x))

//#define PinFlashMOSI          _PIN5_5     /*"�ⲿFlashͨѶSPI ��MOSI��"*/
//#define   PinMode_MX25LMISO(x)        (GPIO_MODE_PIN5_4(x))
//#define PinWrite_MX25LMOSI(x)     (GPIO_WRITE_PIN5_5(x))  // p11.3
//#define   PinMode_MX25LMOSI(x)        (GPIO_MODE_PIN5_5(x))

//#define PinFlashCS                _PIN11_4 //_PIN1_4          /*"�ⲿFlashͨѶSPI ��CS��"*/
//#define ENABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN11_4(0);GPIO_MODE_PIN11_4(GPIO_MODE_OUT);}
//#define DISABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN11_4(1);GPIO_MODE_PIN11_4(GPIO_MODE_OUT);}

//#define PinFLASHPower  PinRN8302_Power
//#define   FLASH_PowerOff()    { RN8207_PowerOff(); RN8302_PowerOff(); }   //flash��8302��Դ���ã�����8302�����壬8207��Դͬ����
//#define   FLASH_PowerOn()    { RN8207_PowerOn(); RN8302_PowerOn(); }  //flash��8302��Դ���ã�����8302�����壬8207��Դͬ����

////---I2C0����-----�洢��---------------------------
//#define PinEepromSCL          _PIN4_0//_PIN5_2            /*"E2   IICͨѶSCL��"*/
//#define PinEepromSDA          _PIN4_1//_PIN5_3            /*"E2   IICͨѶSDA��"*/
//#define PinWrite_SDA0(x)          (GPIO_WRITE_PIN4_1(x))//p5.3
//#define PinRead_SDA0(x)       (GPIO_READ_PIN4_1(0))//
//#define PinMode_SDA0(x)       (GPIO_MODE_PIN4_1(x))//
//#define PinWrite_SCL0(x)          (GPIO_WRITE_PIN4_0(x))//
//#define PinMode_SCL0(x)       (GPIO_MODE_PIN4_0(x))//

//#define PinZB_CTRL              _PIN10_7      /*"�ز���Դ����"*/
//#define PinSET_ZB               _PIN11_6        /*" �ز����ý�   "*/
//#define PinEVENOUT              _PIN11_5        /*"�¼��ϱ���"*/
//#define PinRST_ZB               _PIN5_7 //_PIN5_1         /*"�ز���λ��"*/
//#define PinSTA_ZB               _PIN5_1         /*"�ز�״̬��"*/
//#if(ZBComFlag == 1)
//#define   PinRead_CheckZBSta(x)   GPIO_READ_PIN5_1(0)          // p5.1
//#define   PinWrite_ZBRst(x)           GPIO_WRITE_PIN5_7(x)
//#define   PinWrite_ZBEvenOut(x)   GPIO_WRITE_PIN11_5(x)   // P115
//#endif

//#endif

///*"***************************��ʾģ�����IO��*********************************************************************"*/
//#define PinS1                 _PIN7_3         /*"LCD  SEG��"*/
//#define PinS2                 _PIN7_2         /*"LCD  SEG��"*/
//#define PinS3                 _PIN7_1         /*"LCD  SEG��"*/
//#define PinS4                 _PIN7_0         /*"LCD  SEG��"*/
//#define PinS5                 _PIN6_7         /*"LCD  SEG��"*/
//#define PinS6                 _PIN6_6         /*"LCD  SEG��"*/
//#define PinS7                 _PIN6_5         /*"LCD  SEG��"*/
//#define PinS8                 _PIN6_4         /*"LCD  SEG��"*/
//#define PinS9                 _PIN6_3         /*"LCD  SEG��"*/
//#define PinS10                    _PIN6_2         /*"LCD  SEG��"*/
//#define PinS11                    _PIN6_1         /*"LCD  SEG��"*/
//#define PinS12                    _PIN6_0         /*"LCD  SEG��"*/
//#define PinS13                    _PIN9_7         /*"LCD  SEG��"*/
//#define PinS14                    _PIN9_6         /*"LCD  SEG��"*/
//#define PinS15                    _PIN9_5         /*"LCD  SEG��"*/
//#define PinS16                    _PIN9_4         /*"LCD  SEG��"*/
//#define PinS17                    _PIN9_3         /*"LCD  SEG��"*/
//#define PinS18                    _PIN9_2         /*"LCD  SEG��"*/
//#define PinS19                    _PIN9_1         /*"LCD  SEG��"*/
//#define PinS20                    _PIN9_0         /*"LCD  SEG��"*/
//#define PinS21                    _PIN8_7         /*"LCD  SEG��"*/
//#define PinS22                    _PIN8_6         /*"LCD  SEG��"*/
//#define PinS23                    _PIN8_5         /*"LCD  SEG��"*/
//#define PinS24                    _PIN8_4         /*"LCD  SEG��"*/
//#define PinS25                    _PIN8_3         /*"LCD  SEG��"*/
//#define PinS26                    _PIN8_2         /*"LCD  SEG��"*/
//#define PinS27                    _PIN8_1         /*"LCD  SEG��"*/
//#define PinS28                    _PIN8_0         /*"LCD  SEG��"*/
//#define PinS29                    _PIN7_7         /*"LCD  SEG��"*/
//#define PinS30                    _PIN7_6         /*"LCD  SEG��"*/
//#define PinS31                    _PIN7_5         /*"LCD  SEG��"*/
//#define PinS32                    _PIN7_4         /*"LCD  SEG��"*/
//#define PinS33                    _PIN10_3         /*"LCD  SEG��"*/
//#define PinS34                    _PIN10_1         /*"LCD  SEG��"*/

//#define PinCOM0                 _PIN_Seg3Com7   /*"LCD  COM��"*/
//#define PinCOM1                 _PIN_Seg2Com6   /*"LCD  COM��"*/
//#define PinCOM2                 _PIN_Seg1Com5   /*"LCD  COM��"*/
//#define PinCOM3                 _PIN_Seg0Com4   /*"LCD  COM��"*/

//#endif

#define ON      1
#define OFF     0

//��д����
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

//===GPIO����================================
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
