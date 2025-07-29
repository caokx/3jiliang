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

#define PinISP                  _PIN3_0         /*"ISP���"*/
#define PinAD_3V6               _PIN0_0         /*"ʱ�ӵ�ص�ѹ����"*/
#define PinAD_6V                _PIN_NULL       /*"�����ص�ѹ����"*/
#define PinLVD                  _PIN0_3         /*"ϵͳ��Դ���"*/

#define PinRelayCheck_Ctrl      _PIN_NULL           /*"�̵������"*/
#define RelayCheck_PowerON()
#define RelayCheck_PowerOFF()

#define PinRelayCheck           _PIN_NULL           /*"�̵������"*/
#define PinMode_RelayCheck(x)
#define PinRead_RelayGataCheck(x)   1/*"�̵������P01 "*/

#define PinSCAP_VCTRL           _PIN_NULL
#define SCAP_VCTRL_PowerOn()
#define SCAP_VCTRL_PowerOff()

//P30���
#define PinWrite_DEBUGOut           {Rn8xxx_GPIO_CfgFun(_PIN3_0,_NORMALIO);Rn8xxx_GPIO_CfgIOMode( _PIN3_0 , GPIO_MODE_OUT , NORMAL_OUT ); }
#define PinWrite_DEBUGOutput(x)     (GPIO_WRITE_PIN3_0(x))

//---��������--------------------------------

#define PinKTURA                _PIN_NULL       /*"����up"*/
#define PinRead_KeyTurnA(x)     1               /*"����up    p1.0"*/

#define PinKTURB                _PIN_NULL       /*"����down"*/
#define PinRead_KeyTurnB(x)     1               /*"����down     p1.1"*/

#define PinKCOVER               _PIN3_1         /*"���ϸǼ��"*/
#define PinRead_KeyShell(x)     (GPIO_READ_PIN3_1(0))

#define PinKBTMBOX              _PIN_NULL           /*"���˸Ǽ��"*/
#define PinRead_KeyJunBox(x)    1

#define PinMR_Check             _PIN_NULL       /*" �ż�� "*/
#define PinRead_StrongMan(x)    1

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

#define PinEASMPower            _PIN0_1         /*"EASM��Դ���ƽ�"*/
#define EsamPowerOff()          {GPIO_MODE_PIN0_1(GPIO_MODE_OUT);GPIO_WRITE_PIN0_1(1);}
#define EsamPowerOn()           {GPIO_MODE_PIN0_1(GPIO_MODE_OUT);GPIO_WRITE_PIN0_1(0);}

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

/*"*****************************�̵���ģ�����IO��*********************************************************************"*/
#define PinJump                 _PIN_NULL       /*��բָʾLED"*/
#define PinWrite_RelayLed(x)

#define PinWarn                 _PIN_NULL       /*"�����̵�������"*/
#define PinLoadRelayON          _PIN_NULL
#define PinLoadRelayOFF         _PIN_NULL

/*"***************************�洢ģ�����IO��*********************************************************************"*/
#define PinFlashCLK             _PIN1_2     /*"�ⲿFlashͨѶSPI ��CLK��"*/
#define PinWrite_MX25LSCK(x)    (GPIO_WRITE_PIN1_2(x))
#define PinMode_MX25LSCK(x)     (GPIO_MODE_PIN1_2(x))

#define PinFlashMISO            _PIN1_0     /*"�ⲿFlashͨѶSPI ��MISO��"*/
#define PinWrite_MX25LMISO(x)   (GPIO_WRITE_PIN1_0(x))
#define PinRead_MX25LMISO(x)        (GPIO_READ_PIN1_0(x))
#define PinMode_MX25LMISO(x)        (GPIO_MODE_PIN1_0(x))

#define PinFlashMOSI            _PIN1_1     /*"�ⲿFlashͨѶSPI ��MOSI��"*/
#define PinWrite_MX25LMOSI(x)   (GPIO_WRITE_PIN1_1(x))
#define PinMode_MX25LMOSI(x)        (GPIO_MODE_PIN1_1(x))

#define PinFlashCS              _PIN5_7     /*"�ⲿFlashͨѶSPI ��CS��"*/
#define ENABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN5_7(0);GPIO_MODE_PIN5_7(GPIO_MODE_OUT);}
#define DISABLE_FLASH_MX25LXX() {GPIO_WRITE_PIN5_7(1);GPIO_MODE_PIN5_7(GPIO_MODE_OUT);}

#define PinFLASHPower           _PIN2_6 //Flash��Դ�����
#define FLASH_PowerOff()    {  GPIO_MODE_PIN2_6(GPIO_MODE_OUT);GPIO_WRITE_PIN2_6(1); }  //flash��8302��Դ����
#define FLASH_PowerOn()    {  GPIO_MODE_PIN2_6(GPIO_MODE_OUT);GPIO_WRITE_PIN2_6(0); }   //flash��8302��Դ����
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

#define PinManageModuleRSTM     _PIN11_5    //����ģ�鸴λ�ܽ�
#define PinWrite_PinManageModuleRSTM(x)     (GPIO_WRITE_PIN11_5(x))
#define PinMode_PinManageModuleRSTM(x)      (GPIO_MODE_PIN11_5(x))

#define PinManageModuleLVDOUT       _PIN2_7 //����״̬����ܽ�
#define PinWrite_ManageModuleLVDOUT(x)      (GPIO_WRITE_PIN2_7(x))
#define PinMode_ManageModuleLVDOUT(x)       (GPIO_MODE_PIN2_7(x))

#define PinManageModuleCOMRQIN  _PIN11_6    // ģ��γ����
#define PinRead_ManageModuleCOMRQIN(x)  (GPIO_READ_PIN11_6(0))

#define PinManageModuleCS       _PIN11_0
#define PinManageModuleCLK      _PIN11_1
#define PinManageModuleMISO     _PIN11_2
#define PinManageModuleMOSI     _PIN11_3

/*"***************************�����оƬͨ�Žӿ�*********************************************************************"*/

#define PinTmpSDA           _PIN14_2    //����оƬIIC-SDA�ܽ�
#define PinTmpSCL           _PIN14_1    //����оƬIIC-SCL�ܽ�

#define PinWrite_TmpSDA(x)          (GPIO_WRITE_PIN14_2(x))
#define PinRead_TmpSDA(x)           (GPIO_READ_PIN14_2(0))
#define PinMode_TmpSDA(x)           (GPIO_MODE_PIN14_2(x))
#define PinWrite_TmpSCL(x)          (GPIO_WRITE_PIN14_1(x))
#define PinMode_TmpSCL(x)           (GPIO_MODE_PIN14_1(x))

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

#else

#if(PCB_Version==RN8613V2_RN8209DV4)

#define PinISP                  _PIN3_0        /*"ISP���"*/
//P30���
#define PinWrite_DEBUGOut           {Rn8xxx_GPIO_CfgFun(_PIN3_0,_NORMALIO);Rn8xxx_GPIO_CfgIOMode( _PIN3_0 , GPIO_MODE_OUT , NORMAL_OUT ); }
#define PinWrite_DEBUGOutput(x)     (GPIO_WRITE_PIN3_0(x))

#define PinAD_3V6               _PIN0_0         /*"ʱ�ӵ�ص�ѹ����"*/
#define PinLVD                  _PIN0_3         /*"ϵͳ��Դ���"*/

//---��������--------------------------------

#define PinKTURB                0xFF        /*"����up"*/
#define PinRead_KeyTurnB(x)     (0) /*"����up    p1.0"*/

#define PinKCOVER               0xFF            /*"���ϸǼ��"*/
#define PinRead_KeyShell(x)     (0) /*"���ϸǼ��p45"*/

#define PinClkOut               _PIN3_2         /*"���������"*/
#define PinWrite_OpticalOutMulFun(x)   (GPIO_WRITE_PIN3_2(x))

/*"*****************************����ģ�����IO��*********************************************************************"*/

/*"EASM  IO�ڶ���"*/
#define PinEsamClk              _PIN10_5//_PIN5_3//_PIN1_3          /*"Esamʱ�ӽ�"*/
#define PinWrite_EsamSCK(x)     (GPIO_WRITE_PIN10_5(x))
#define PinMode_EsamSCK(x)      (GPIO_MODE_PIN10_5(x))

#define PinEASMMISO             _PIN10_6//      //EASMͨѶSPI ��MISO��
#define PinWrite_EsamMISO(x)    (GPIO_WRITE_PIN10_6(x))
#define PinRead_EsamMISO(x)     (GPIO_READ_PIN10_6(x))
#define PinMode_EsamMISO(x)     (GPIO_MODE_PIN10_6(x))

#define PinEASMMOSI             _PIN10_7//          //EASMͨѶSPI ��MOSI��
#define PinWrite_EsamMOSI(x)    (GPIO_WRITE_PIN10_7(x))
#define PinRead_EsamMOSI(x)     (GPIO_READ_PIN10_7(x))
#define PinMode_EsamMOSI(x)     (GPIO_MODE_PIN10_7(x))

#define PinEASMCS               _PIN10_4//_PIN5_2//_PIN11_0         /*"EASMͨѶSPI ��CS��"*/
#define ENABLE_ESAM()           {GPIO_WRITE_PIN10_4(0);GPIO_MODE_PIN10_4(GPIO_MODE_OUT);}
#define DISABLE_ESAM()          {GPIO_WRITE_PIN10_4(1);GPIO_MODE_PIN10_4(GPIO_MODE_OUT);}

#define PinEASMPower            _PIN0_1         /*"EASM��Դ���ƽ�"*/
#define EsamPowerOff()          {GPIO_WRITE_PIN0_1(1);GPIO_MODE_PIN0_1(GPIO_MODE_OUT);}//
#define EsamPowerOn()           {GPIO_WRITE_PIN0_1(0);GPIO_MODE_PIN0_1(GPIO_MODE_OUT);}
#define PinIC_IO                (0xFF)//_PIN4_2         /*"�����ݿ�"*/
#define PinIC_RST              (0xFF) //_PIN3_4         /*"����λ��"*/
#define PinIC_KEY               (0xFF)//_PIN3_5         /*"������"*/

#define CardFoutOpen()          (0xFF)//ZHUPDEBUG {ISO7816 ->CLK=0x0A;}             /*����ESAM��ʱ�����p4[0]*/
#define CardFoutClose()         (0xFF)//ZHUPDEBUG {ISO7816 ->CLK=0x02;}

/*"***************************ͨѶģ�����IO��*********************************************************************"*/
#define Pin485RE                0xFF //_PIN1_4         /*"485ͨ���շ����ƽ�"*/
#define PinRXD485               0xFF         /*"485ͨ�����ս�"*/
#define PinTXD485              0xFF         /*"485ͨ�����ͽ�"*/

#define PinRXD_IR               0xFF//_PIN5_4         /*"����ͨ�����ս�"*/
#define PinTXD_IR               0xFF//_PIN5_5         /*"����ͨ�����ͽ�"*/
#define PinMode_IRRX(x)         (0)//
#define PinRead_IRRX(x)         (0)//

#define PinRXD_ZB               _PIN2_0         /*"�ز�ͨ�����ս�"*/
#define PinTXD_ZB               _PIN2_1         /*"�ز�ͨ�����ͽ�"*/

//���������
#define PinSPK                  0xFF            /*"������"*/
#define PinWrite_Beep(x)                (0)//

/*"****************************����ģ�����IO��*********************************************************************"*/

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

#define PinRN8209_PF               _PIN3_6  //����оƬ�����й�����ܽ�
#define PinRN8209_QF               _PIN3_7  //����оƬ�����޹�����ܽ�

#define Pin_PF               _PIN5_1// MCU����й�����
#define Pin_QF               _PIN5_0//MCU����޹�����

#define Pin_PtHPF               _PIN3_4// MCU��������й�г������
#define Pin_NtHPF               _PIN4_7//MCU��������й�г������

#define PinRN8209_IRQ               _PIN4_2 //����оƬ�ж�����

/*"***************************����չģ��ͨ�Žӿڣ������������IO��*********************************************************************"*/
#define PinExModuleClk              _PIN4_1 //�ⲿ��չģ��SPI��CLK��
#define PinWrite_ExModuleSCK(x)     (GPIO_WRITE_PIN4_1(x))
#define PinMode_ExModuleSCK(x)      (GPIO_MODE_PIN4_1(x))

#define PinExModuleMOSI             _PIN4_3 //�ⲿ��չģ��SPI��MOSI��
#define PinWrite_ExModuleMOSI(x)    (GPIO_WRITE_PIN4_3(x))
#define PinRead_ExModuleMOSI(x)     (GPIO_READ_PIN4_3(x))
#define PinMode_ExModuleMOSI(x)     (GPIO_MODE_PIN4_3(x))

#define PinExModuleCS               _PIN11_5 //�ⲿ��չSPI��CS��
#define ENABLE_ExModule()           {GPIO_WRITE_PIN11_5(0);GPIO_MODE_PIN11_5(GPIO_MODE_OUT);}
#define DISABLE_ExModule()          {GPIO_WRITE_PIN11_5(1);GPIO_MODE_PIN11_5(GPIO_MODE_OUT);}

/*"***************************�洢ģ�����IO��*********************************************************************"*/
/*"flashSPI"*/
#define     PinFLASHPower           _PIN2_6
#define FLASH_PowerOff()    {GPIO_WRITE_PIN2_6(1);GPIO_MODE_PIN2_6(GPIO_MODE_OUT);}//
#define FLASH_PowerOn()    {GPIO_WRITE_PIN2_6(0);GPIO_MODE_PIN2_6(GPIO_MODE_OUT);}

/*"----FLASH   SPI����-----"*/
#define PinFlashCLK         _PIN1_2     /*"�ⲿFlashͨѶSPI ��CLK��"*/
#define PinWrite_MX25LSCK(x)        (GPIO_WRITE_PIN1_2(x))//
#define PinMode_MX25LSCK(x)     (GPIO_MODE_PIN1_2(x))

#define PinFlashMISO            _PIN1_0     /*"�ⲿFlashͨѶSPI ��MISO��"*/
#define PinWrite_MX25LMISO(x)   (GPIO_WRITE_PIN1_0(x))//
#define PinRead_MX25LMISO(x)        (GPIO_READ_PIN1_0(x))

#define PinFlashMOSI            _PIN1_1     /*"�ⲿFlashͨѶSPI ��MOSI��"*/
#define PinMode_MX25LMISO(x)        (GPIO_MODE_PIN1_0(x))
#define PinWrite_MX25LMOSI(x)   (GPIO_WRITE_PIN1_1(x))  //
#define PinMode_MX25LMOSI(x)        (GPIO_MODE_PIN1_1(x))

#define PinFlashCS              _PIN5_7 //  /*"�ⲿFlashͨѶSPI ��CS��"*/
#define ENABLE_FLASH_MX25LXX()    {GPIO_WRITE_PIN5_7(0); GPIO_MODE_PIN5_7(GPIO_MODE_OUT);}
#define DISABLE_FLASH_MX25LXX()  {GPIO_WRITE_PIN5_7(1); GPIO_MODE_PIN5_7(GPIO_MODE_OUT);}

//---I2C0����-----�洢��---------------------------
#define PinEepromSCL            _PIN2_2//       /*"E2   IICͨѶSCL��"*/
#define PinEepromSDA            _PIN2_3//           /*"E2   IICͨѶSDA��"*/
#define PinWrite_SDA0(x)        (GPIO_WRITE_PIN2_3(x))//p5.3
#define PinRead_SDA0(x)     (GPIO_READ_PIN2_3(0))//
#define PinMode_SDA0(x)     (GPIO_MODE_PIN2_3(x))//
#define PinWrite_SCL0(x)        (GPIO_WRITE_PIN2_2(x))//
#define PinMode_SCL0(x)     (GPIO_MODE_PIN2_2(x))//

#define PinEVENOUT              0xFF        /*"�¼��ϱ���"*/
#define PinWrite_ZBEvenOut(x)   (0) //

#define PinSCAP_VCTRL              _PIN11_6   //���������ϱ�������Դ�������
#define SCAP_VCTRL_PowerOff()    {GPIO_WRITE_PIN11_6(1);GPIO_MODE_PIN11_6(GPIO_MODE_OUT);}//
#define SCAP_VCTRL_PowerOn()    {GPIO_WRITE_PIN11_6(0);GPIO_MODE_PIN11_6(GPIO_MODE_OUT);}

#define PinLCDBackLight         0xFF        /*"Һ������"*/
#define LCDBackLightOff()      (0)
#define LCDBackLightON()       (0)

#define PinJump                 0xFF        /*��բָʾLED"*/
#define PinWrite_RelayLed(x)           (0)  //x=0 ����

#define PinRelayCheck_Ctrl      0xFF            /*"    "*/
#define RelayCheck_PowerON()    {;}
#define RelayCheck_PowerOFF()   {;}

#define PinRelayCheck           0xFF            /*"�̵������"*/
#define PinMode_RelayCheck(x)       (0)
#define PinRead_RelayGataCheck()   (0)  /*"�̵������P01 "*/

#define PinWarn                 0xFF            /*"���ü̵���"*/
#define PinLoadRelayON          0xFF        /*"�̵�������1"*/
#define PinLoadRelayOFF         0xFF        /*"�̵�������2"*/

#define PinSET_ZB               (0xFF)//_PIN11_6        /*" �ز����ý�   "*/

#define PinRST_ZB               (0xFF)//_PIN5_7 //_PIN5_1         /*"�ز���λ��"*/
#define PinSTA_ZB               (0xFF)//_PIN5_1         /*"�ز�״̬��"*/

#define PinRead_CheckZBSta(x)   (1) //GPIO_READ_PIN5_1(0)            // p5.1
#define PinWrite_ZBRst(x)           (0) //GPIO_WRITE_PIN5_7(x)

#else

#define PinISP                  _PIN3_0        /*"ISP���"*/
#define PinAD_3V6               _PIN4_5         /*"ʱ�ӵ�ص�ѹ����"*/
#define PinLVD                  _PIN0_3         /*"ϵͳ��Դ���"*/

//P30���
#define PinWrite_DEBUGOut           {Rn8xxx_GPIO_CfgFun(_PIN3_0,_NORMALIO);Rn8xxx_GPIO_CfgIOMode( _PIN3_0 , GPIO_MODE_OUT , NORMAL_OUT ); }
#define PinWrite_DEBUGOutput(x)     (GPIO_WRITE_PIN3_0(x))

//---��������--------------------------------

#define PinKTURB                _PIN3_6        /*"����up"*/
#define PinRead_KeyTurnB(x)     (GPIO_READ_PIN3_6(0))   /*"����up    p1.0"*/

#define PinKCOVER               _PIN4_4         /*"���ϸǼ��"*/
#define PinRead_KeyShell(x)     (GPIO_READ_PIN4_4(0))   /*"���ϸǼ��p45"*/

#define PinClkOut               _PIN5_6         /*"���������"*/
#define PinWrite_OpticalOutMulFun(x)   (GPIO_WRITE_PIN5_6(x))

/*"*****************************����ģ�����IO��*********************************************************************"*/

/*"EASM  IO�ڶ���"*/
#define PinEsamClk              _PIN5_1//_PIN5_3//_PIN1_3           /*"Esamʱ�ӽ�"*/
#define PinWrite_EsamSCK(x)     (GPIO_WRITE_PIN5_1(x))
#define PinMode_EsamSCK(x)      (GPIO_MODE_PIN5_1(x))

#define PinEASMMISO             _PIN4_6//       //EASMͨѶSPI ��MISO��
#define PinWrite_EsamMISO(x)    (GPIO_WRITE_PIN4_6(x))
#define PinRead_EsamMISO(x)     (GPIO_READ_PIN4_6(x))
#define PinMode_EsamMISO(x)     (GPIO_MODE_PIN4_6(x))

#define PinEASMMOSI             _PIN4_7//           //EASMͨѶSPI ��MOSI��
#define PinWrite_EsamMOSI(x)    (GPIO_WRITE_PIN4_7(x))
#define PinRead_EsamMOSI(x)     (GPIO_READ_PIN4_7(x))
#define PinMode_EsamMOSI(x)     (GPIO_MODE_PIN4_7(x))

#define PinEASMCS               _PIN0_4//_PIN5_2//_PIN11_0      /*"EASMͨѶSPI ��CS��"*/
#define ENABLE_ESAM()           {GPIO_WRITE_PIN0_4(0);GPIO_MODE_PIN0_4(GPIO_MODE_OUT);}
#define DISABLE_ESAM()          {GPIO_WRITE_PIN0_4(1);GPIO_MODE_PIN0_4(GPIO_MODE_OUT);}

#define PinEASMPower            _PIN9_3         /*"EASM��Դ���ƽ�"*/
#define EsamPowerOff()          {GPIO_WRITE_PIN9_3(1);GPIO_MODE_PIN9_3(GPIO_MODE_OUT);}//
#define EsamPowerOn()           {GPIO_WRITE_PIN9_3(0);GPIO_MODE_PIN9_3(GPIO_MODE_OUT);}

#define PinIC_IO                (0xFF)//_PIN4_2         /*"�����ݿ�"*/
#define PinIC_RST              (0xFF) //_PIN3_4         /*"����λ��"*/
#define PinIC_KEY               (0xFF)//_PIN3_5         /*"������"*/

#define CardFoutOpen()          (0xFF)//ZHUPDEBUG {ISO7816 ->CLK=0x0A;}             /*����ESAM��ʱ�����p4[0]*/
#define CardFoutClose()         (0xFF)//ZHUPDEBUG {ISO7816 ->CLK=0x02;}

/*"***************************ͨѶģ�����IO��*********************************************************************"*/

#define Pin485RE                _PIN7_1 //_PIN1_4         /*"485ͨ���շ����ƽ�"*/
#define PinRXD485               _PIN2_0         /*"485ͨ�����ս�"*/
#define PinTXD485              _PIN2_1         /*"485ͨ�����ͽ�"*/

#define PinRXD_IR               _PIN2_2//_PIN5_4         /*"����ͨ�����ս�"*/
#define PinTXD_IR               _PIN2_3//_PIN5_5         /*"����ͨ�����ͽ�"*/
#define PinMode_IRRX(x)         (GPIO_MODE_PIN2_2(x))//
#define PinRead_IRRX(x)         (GPIO_READ_PIN2_2(0))//

#define PinRXD_ZB               _PIN2_6         /*"�ز�ͨ�����ս�"*/
#define PinTXD_ZB               _PIN2_7         /*"�ز�ͨ�����ͽ�"*/

//���������
#define PinSPK                  _PIN7_2         /*"������"*/
#define PinWrite_Beep(x)                (GPIO_WRITE_PIN7_2(x))//

/*"****************************����ģ�����IO��*********************************************************************"*/
#define PinRXD_RN8209C               _PIN0_0
#define PinTXD_RN8209C               _PIN0_1

#define PinRXD_RN8209F               _PIN5_4
#define PinTXD_RN8209F               _PIN5_5

/*"***************************�洢ģ�����IO��*********************************************************************"*/
/*"flashSPI"*/
#define     PinFLASHPower           _PIN9_2
#define FLASH_PowerOff()    {GPIO_WRITE_PIN9_2(1);GPIO_MODE_PIN9_2(GPIO_MODE_OUT);}//
#define FLASH_PowerOn()    {GPIO_WRITE_PIN9_2(0);GPIO_MODE_PIN9_2(GPIO_MODE_OUT);}

/*"----FLASH   SPI����-----"*/
#define PinFlashCLK         _PIN9_4     /*"�ⲿFlashͨѶSPI ��CLK��"*/
#define PinWrite_MX25LSCK(x)        (GPIO_WRITE_PIN9_4(x))//
#define PinMode_MX25LSCK(x)     (GPIO_MODE_PIN9_4(x))

#define PinFlashMISO            _PIN1_0     /*"�ⲿFlashͨѶSPI ��MISO��"*/
#define PinWrite_MX25LMISO(x)   (GPIO_WRITE_PIN1_0(x))//
#define PinRead_MX25LMISO(x)        (GPIO_READ_PIN1_0(x))

#define PinFlashMOSI            _PIN1_1     /*"�ⲿFlashͨѶSPI ��MOSI��"*/
#define PinMode_MX25LMISO(x)        (GPIO_MODE_PIN1_0(x))
#define PinWrite_MX25LMOSI(x)   (GPIO_WRITE_PIN1_1(x))  //
#define PinMode_MX25LMOSI(x)        (GPIO_MODE_PIN1_1(x))

#define PinFlashCS              _PIN9_5 //_PIN1_4           /*"�ⲿFlashͨѶSPI ��CS��"*/
#define ENABLE_FLASH_MX25LXX()    {GPIO_WRITE_PIN9_5(0); GPIO_MODE_PIN9_5(GPIO_MODE_OUT);}
#define DISABLE_FLASH_MX25LXX()  {GPIO_WRITE_PIN9_5(1); GPIO_MODE_PIN9_5(GPIO_MODE_OUT);}

//---I2C0����-----�洢��---------------------------
#define PinEepromSCL            _PIN5_2//_PIN5_2            /*"E2   IICͨѶSCL��"*/
#define PinEepromSDA            _PIN5_3//_PIN5_3            /*"E2   IICͨѶSDA��"*/
#define PinWrite_SDA0(x)        (GPIO_WRITE_PIN5_3(x))//p5.3
#define PinRead_SDA0(x)     (GPIO_READ_PIN5_3(0))//
#define PinMode_SDA0(x)     (GPIO_MODE_PIN5_3(x))//
#define PinWrite_SCL0(x)        (GPIO_WRITE_PIN5_2(x))//
#define PinMode_SCL0(x)     (GPIO_MODE_PIN5_2(x))//

#define PinEVENOUT              _PIN4_1        /*"�¼��ϱ���"*/
#define PinWrite_ZBEvenOut(x)   (GPIO_WRITE_PIN4_1(x)) //

#define PinSCAP_VCTRL              _PIN7_3   //���������ϱ�������Դ�������
#define SCAP_VCTRL_PowerOff()    {GPIO_WRITE_PIN7_3(1);GPIO_MODE_PIN7_3(GPIO_MODE_OUT);}//
#define SCAP_VCTRL_PowerOn()    {GPIO_WRITE_PIN7_3(0);GPIO_MODE_PIN7_3(GPIO_MODE_OUT);}

#if(PCB_Version==RN8613_RN8209C)
/*"*****************************�̵���ģ�����IO��*********************************************************************"*/
#define PinLCDBackLight         _PIN10_7        /*"Һ������"*/
#define LCDBackLightOff()      (GPIO_WRITE_PIN10_7(1))
#define LCDBackLightON()       (GPIO_WRITE_PIN10_7(0))

#define PinJump                 _PIN7_0     /*��բָʾLED"*/
#define PinWrite_RelayLed(x)           (GPIO_WRITE_PIN7_0(x))  //x=0 ����

#define PinRelayCheck_Ctrl      _PIN0_2         /*"    "*/
#define RelayCheck_PowerON()    {GPIO_WRITE_PIN0_2(1);GPIO_MODE_PIN0_2(GPIO_MODE_OUT);}
#define RelayCheck_PowerOFF()   {GPIO_WRITE_PIN0_2(0);GPIO_MODE_PIN0_2(GPIO_MODE_OUT);}

#define PinRelayCheck           _PIN10_6            /*"�̵������"*/
#define PinMode_RelayCheck(x)       (GPIO_MODE_PIN10_6(x))
#define PinRead_RelayGataCheck()   (GPIO_READ_PIN10_6(0))   /*"�̵������P01 "*/

#define PinWarn                 _PIN10_4            /*"���ü̵���"*/
#define PinLoadRelayON          _PIN10_4        /*"�̵�������1"*/
#define PinLoadRelayOFF         _PIN10_5        /*"�̵�������2"*/

#define PinSET_ZB               (0)//_PIN11_6        /*" �ز����ý�   "*/

#define PinRST_ZB               (0)//_PIN5_7 //_PIN5_1         /*"�ز���λ��"*/
#define PinSTA_ZB               (0)//_PIN5_1         /*"�ز�״̬��"*/

#define PinRead_CheckZBSta(x)   (1) //GPIO_READ_PIN5_1(0)            // p5.1
#define PinWrite_ZBRst(x)           (0) //GPIO_WRITE_PIN5_7(x)

#elif (PCB_Version==RN8613_RN8209S)
/*"*****************************�̵���ģ�����IO��*********************************************************************"*/
#define PinLCDBackLight         (0) //_PIN14_0        /*"Һ������"*/
#define LCDBackLightOff()      (0) //(GPIO_WRITE_PIN14_0(1))
#define LCDBackLightON()       (0) //(GPIO_WRITE_PIN14_0(0))

#define PinJump                 _PIN7_0     /*��բָʾLED"*/
#define PinWrite_RelayLed(x)           (GPIO_WRITE_PIN7_0(x))  //x=0 ����

#define PinRelayCheck_Ctrl        (0) //_PIN2_4         /*"    "*/
#define RelayCheck_PowerON()    (0) //{GPIO_WRITE_PIN2_4(1);GPIO_MODE_PIN2_4(GPIO_MODE_OUT);}
#define RelayCheck_PowerOFF()   (0) //{GPIO_WRITE_PIN2_4(0);GPIO_MODE_PIN2_4(GPIO_MODE_OUT);}

#define PinRelayCheck           (0)//_PIN2_5            /*"�̵������"*/
#define PinMode_RelayCheck(x)       (0) //(GPIO_MODE_PIN2_5(x))
#define PinRead_RelayGataCheck()   (0) //(GPIO_READ_PIN2_5(0))  /*"�̵������P01 "*/

#define PinWarn                 _PIN0_2         /*"���ü̵���"*/
#define PinLoadRelayON          _PIN0_2     /*"�̵�������1"*/
#define PinLoadRelayOFF         _PIN10_6        /*"�̵�������2"*/

#define PinSET_ZB               (0)//_PIN11_6        /*" �ز����ý�   "*/

#define PinRST_ZB               (0)//_PIN5_7 //_PIN5_1         /*"�ز���λ��"*/
#define PinSTA_ZB               (0)//_PIN5_1         /*"�ز�״̬��"*/

#define PinRead_CheckZBSta(x)   (1) //GPIO_READ_PIN5_1(0)            // p5.1
#define PinWrite_ZBRst(x)           (0) //GPIO_WRITE_PIN5_7(x)

#endif

/*"***************************��ʾģ�����IO��*********************************************************************"*/
#define PinS1                  _PIN_Seg2Com6         /*"LCD  SEG��"*/
#define PinS2                  _PIN_Seg3Com7         /*"LCD  SEG��"*/
#define PinS3                   _PIN6_0         /*"LCD  SEG��"*/
#define PinS4                   _PIN6_1         /*"LCD  SEG��"*/
#define PinS5                   _PIN6_2         /*"LCD  SEG��"*/
#define PinS6                   _PIN6_3         /*"LCD  SEG��"*/
#define PinS7                   _PIN6_4         /*"LCD  SEG��"*/
#define PinS8                   _PIN6_5         /*"LCD  SEG��"*/
#define PinS9                   _PIN6_6         /*"LCD  SEG��"*/
#define PinS10                  _PIN6_7         /*"LCD  SEG��"*/
#define PinS11                  _PIN7_4         /*"LCD  SEG��"*/
#define PinS12                  _PIN7_5         /*"LCD  SEG��"*/
#define PinS13                  _PIN7_6         /*"LCD  SEG��"*/
#define PinS14                  _PIN7_7         /*"LCD  SEG��"*/
#define PinS15                  _PIN8_0         /*"LCD  SEG��"*/
#define PinS16                  _PIN8_1         /*"LCD  SEG��"*/
#define PinS17                  _PIN8_2         /*"LCD  SEG��"*/
#define PinS18                  _PIN8_3         /*"LCD  SEG��"*/
#define PinS19                  _PIN8_4         /*"LCD  SEG��"*/
#define PinS20                  _PIN8_5         /*"LCD  SEG��"*/
#define PinS21                  _PIN8_6         /*"LCD  SEG��"*/
#define PinS22                  _PIN8_7         /*"LCD  SEG��"*/
#define PinS23                  _PIN9_0         /*"LCD  SEG��"*/
#define PinS24                  _PIN9_1         /*"LCD  SEG��"*/

#define PinCOM4                 _PIN_Seg0Com4   /*"LCD  COM��"*/
#define PinCOM5                 _PIN_Seg1Com5   /*"LCD  COM��"*/

#define ON      1
#define OFF     0
#endif
#endif

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
