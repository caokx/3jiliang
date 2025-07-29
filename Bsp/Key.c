#define  _KEY_GLOBALS

#include <BSP.h>
#include <App.h>

//�������ܣ�������ʼ��
//��ڲ�������
//���ڲ�������
void fnKey_Init(void)
{
    Std_Memset(&Key, 0, sizeof(sKey_TypeDef));
    Key.Release |= 0X00A0;
}

//�������ܣ�����ɨ��
//��ڲ�������
//���ڲ�������(�������º��ͷŷֱ����Key.StampPress��Key.StampRelease�����а�����������ӦλΪ1)
void fnKey_Scan(void)
{
    //    Key.KeyTurn_Scan2  =(Key.KeyTurn_Scan2 << 1)+ PinRead_KeyTurnB();
    Key.KeyShell_Scan  = (Key.KeyShell_Scan << 1) + PinRead_KeyShell();

    #if(nPhs==ThreePhs)
    //  Key.KeyTurn_Scan1  =(Key.KeyTurn_Scan1 << 1)+ PinRead_KeyTurnA();
    Key.KeyJUNBOX_Scan = (Key.KeyJUNBOX_Scan << 1) + PinRead_KeyJunBox();

    Key.StrongMan_Scan = (Key.StrongMan_Scan << 1) + PinRead_StrongMan();
    //  Key.RelayGataCheck=(Key.RelayGataCheck << 1)+PinRead_RelayGataCheck();
    #else
    fnOutput_RelayPinCheck();
    Key.RelayGataCheck = (Key.RelayGataCheck << 1) + Output.PubData.CheckGataSta;
    #endif

    Key.CtrlModuPlgChk = (Key.CtrlModuPlgChk << 1) + PinRead_ManageModuleCOMRQIN();

    //  if (Key.KeyProg_Scan ==0x00 )    //��̰�ť����
    //  {
    //          if(Key.Release&KEY_VAL_PRG)
    //      {
    //              Key.Press |= 0X0001;
    //              Key.Release &= 0XFFFE;
    //      }
    //    }
    //  if (Key.KeyProg_Scan ==0xFF )   //��̰�ť��̬�ͷ�̬
    //      {
    //          Key.Release |= 0X0001;
    //      }
    //
    //  if (Key.KeyTurn_Scan1 ==0x00 )    //�Ϸ����԰�ť����
    //      {
    //      Key.KeyTurn_Time1++;
    //      if(Key.Release &KEY_VAL_TURNA)
    //      {
    //          Key.Press |= 0X0002;
    //          Key.Release &= 0XFFFD;
    //      }
    //      }
    //  if (Key.KeyTurn_Scan1 ==0xFF )    //�Ϸ����԰�ť��̬�ͷ�̬
    //      {
    //          Key.KeyTurn_Time1=0;
    //          Key.Release |= 0X0002;
    //      }
    //
    //  if (Key.KeyTurn_Time1>=500 )
    //  {
    //          Key.KeyTurn_Time1=0;      //�й��Ϸ������̼���ϵ��ֶ���������
    //          Key.Press |= 0X0004;
    //          Key.Press |=KEY_Relay_Ctrl;
    ////        Key.Press |=KEY_BJRelay_Ctrl;
    //      }
    //
    //  if (Key.KeyTurn_Scan2 ==0x00 )     //�·����԰�ť����
    //      {
    //      Key.KeyTurn_Time2++;
    //      if(Key.Release &KEY_VAL_TURNB)
    //      {
    //          Key.Press |= 0X0008;
    //          Key.Release &= 0XFFF7;
    //      }
    //      }
    //  if (Key.KeyTurn_Scan2 ==0xFF )    //�·����԰�ť�ͷ�״̬
    //      {
    //          Key.KeyTurn_Time2=0;
    //          Key.Release |= 0X0008;
    //      }

    //  if (Key.KeyTurn_Time2>=500 )
    //  {
    //          Key.KeyTurn_Time2=0;       //�й��Ϸ������̼���ϵ��ֶ���������
    //          Key.Press |= 0X0010;
    //          Key.Press |=KEY_Relay_Ctrl;
    ////        Key.Press |=KEY_BJRelay_Ctrl;
    //      }

    if (Bkgrd.PubData.tMngPlug)
    {
        Key.MngPlgDnTmr = 0;
        Key.MngPlgUpTmr = 0;
    }

    if (Key.CtrlModuPlgChk == 0xFF)//����ģ��γ�
    {
        Key.MngPlgDnTmr = 0;
        Key.MngPlgUpTmr++;
        if (Key.MngPlgUpTmr >= EvtMngPlugPinTmr)
        {
            Key.MngPlgUpTmr = EvtMngPlugPinTmr;
            Key.Press |= KEY_VAL_CTRLMODUPLGCHKVS;
            if (Key.Release & KEY_VAL_CTRLMODUPLGCHKVS)
            {
                Key.Press |= KEY_VAL_CTRLMODUPLGCHK;    //����ģ��γ���־λ����
                Key.Release &= ~KEY_VAL_CTRLMODUPLGCHKVS;
            }
            Bkgrd.PubData.MtSysSta.SysStaBit.BothCoreValid = 0;
        }
    }
    if (Key.CtrlModuPlgChk == 0x00)//����ģ�����
    {
        Key.MngPlgUpTmr = 0;
        Key.MngPlgDnTmr++;
        if (Key.MngPlgDnTmr >= EvtMngPlugPinTmr)
        {
            Key.MngPlgDnTmr = EvtMngPlugPinTmr;
            Key.Release |= KEY_VAL_CTRLMODUPLGCHKVS;           //״̬����
            if (Key.Press & KEY_VAL_CTRLMODUPLGCHKVS)
            {
                Key.Release |= KEY_VAL_CTRLMODUPLGCHK;          //����ģ����ϱ�־λ����
                Key.Press &= ~KEY_VAL_CTRLMODUPLGCHKVS;
            }
        }
    }

    if (Key.KeyShell_Scan == 0x00)    //���ϱ�ǰ�ťɨ��
    {
        Key.Press |= 0X0020;              //״̬����
        if (Key.Release & KEY_VAL_SHELLVS)
        {
            Key.Press |= 0X0040;              //��¼���Ǽ�¼��
            Key.Release &= 0XFFBF;
        }
        Bkgrd.PubData.MtSysSta.SysStaBit.OpenCover = 1;  //����״̬
    }
    if (Key.KeyShell_Scan == 0xFF)     //��ǳ�̬���ϸ�״̬
    {
        Key.Release |= 0X0020;           //״̬����
        if (Key.Press & KEY_VAL_SHELLVS)
        {
            Key.Release |= 0X0040;          //��¼�ϸǼ�¼��
            Key.Press &= 0XFFBF;
        }

        Bkgrd.PubData.MtSysSta.SysStaBit.OpenCover = 0;  //�ϸ�״̬
    }
    if (Key.KeyJUNBOX_Scan == 0x00)    //���ϱ�ǰ�ťɨ��
    {
        Key.Press |= 0X0080;              //״̬����
        if (Key.Release & KEY_VAL_JUNBOXVS)
        {
            Key.Press |= 0X0100;              //��¼���Ǽ�¼��
            Key.Release &= 0XFEFF;
        }

        Bkgrd.PubData.MtSysSta.SysStaBit.OpenShell = 1;  //����״̬
    }
    if (Key.KeyJUNBOX_Scan == 0xFF)     //��ǳ�̬���ϸ�״̬
    {
        Key.Release |= 0X0080;           //״̬����
        if (Key.Press & KEY_VAL_JUNBOXVS)
        {
            Key.Release |= 0X0100;      //��¼�ϸǼ�¼��
            Key.Press &= 0XFEFF;
        }

        Bkgrd.PubData.MtSysSta.SysStaBit.OpenShell = 0;  //�ϸ�״̬
    }
    if (Key.StrongMan_Scan == 0x00)    //ǿ�ų�Ӱ�����
    {
        Key.STROMAN_Time++;
        Key.Press |= 0X0800;
        if ((Key.Release & KEY_VAL_STROMANVS) && (Key.STROMAN_Time > 1000))
        {
            Key.Press |= 0X1000;
            Key.Release &= 0XEFFF;

            Bkgrd.PubData.MtSysSta.SysStaBit.MagnetDisturb = 1;
        }
    }
    if (Key.StrongMan_Scan == 0xFF)
    {
        Key.STROMAN_Time = 0;
        Key.Release |= 0X0800;
        if (Key.Press & KEY_VAL_STROMANVS)
        {
            Key.Release |= 0X1000;
            Key.Press &= 0XEFFF;

            Bkgrd.PubData.MtSysSta.SysStaBit.MagnetDisturb = 0;
        }
    }
    //  if (Key.RelayGataCheck ==0x00 )    //��բ״̬
    //    {
    //          //if(Key.Release&KEY_VAL_RelayGataCheck)
    //      {
    //              Key.Press |= KEY_VAL_RelayGataCheck;
    //              Key.Release &= ~KEY_VAL_RelayGataCheck;
    //      }
    //    }
    //  if (Key.RelayGataCheck ==0xFF )  // ��բ״̬
    //  {
    //      Key.Release |= KEY_VAL_RelayGataCheck;
    //      Key.Press &= ~KEY_VAL_RelayGataCheck;
    //  }
    return;
}
