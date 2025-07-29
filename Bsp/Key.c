#define  _KEY_GLOBALS

#include <BSP.h>
#include <App.h>

//函数功能：按键初始化
//入口参数：无
//出口参数：无
void fnKey_Init(void)
{
    Std_Memset(&Key, 0, sizeof(sKey_TypeDef));
    Key.Release |= 0X00A0;
}

//函数功能：按键扫描
//入口参数：无
//出口参数：无(按键按下和释放分别放于Key.StampPress和Key.StampRelease，如有按键动作，对应位为1)
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

    //  if (Key.KeyProg_Scan ==0x00 )    //编程按钮按下
    //  {
    //          if(Key.Release&KEY_VAL_PRG)
    //      {
    //              Key.Press |= 0X0001;
    //              Key.Release &= 0XFFFE;
    //      }
    //    }
    //  if (Key.KeyProg_Scan ==0xFF )   //编程按钮常态释放态
    //      {
    //          Key.Release |= 0X0001;
    //      }
    //
    //  if (Key.KeyTurn_Scan1 ==0x00 )    //上翻键显按钮按下
    //      {
    //      Key.KeyTurn_Time1++;
    //      if(Key.Release &KEY_VAL_TURNA)
    //      {
    //          Key.Press |= 0X0002;
    //          Key.Release &= 0XFFFD;
    //      }
    //      }
    //  if (Key.KeyTurn_Scan1 ==0xFF )    //上翻键显按钮常态释放态
    //      {
    //          Key.KeyTurn_Time1=0;
    //          Key.Release |= 0X0002;
    //      }
    //
    //  if (Key.KeyTurn_Time1>=500 )
    //  {
    //          Key.KeyTurn_Time1=0;      //有关上翻键与编程键配合的手动需量清零
    //          Key.Press |= 0X0004;
    //          Key.Press |=KEY_Relay_Ctrl;
    ////        Key.Press |=KEY_BJRelay_Ctrl;
    //      }
    //
    //  if (Key.KeyTurn_Scan2 ==0x00 )     //下翻键显按钮按下
    //      {
    //      Key.KeyTurn_Time2++;
    //      if(Key.Release &KEY_VAL_TURNB)
    //      {
    //          Key.Press |= 0X0008;
    //          Key.Release &= 0XFFF7;
    //      }
    //      }
    //  if (Key.KeyTurn_Scan2 ==0xFF )    //下翻键显按钮释放状态
    //      {
    //          Key.KeyTurn_Time2=0;
    //          Key.Release |= 0X0008;
    //      }

    //  if (Key.KeyTurn_Time2>=500 )
    //  {
    //          Key.KeyTurn_Time2=0;       //有关上翻键与编程键配合的手动需量清零
    //          Key.Press |= 0X0010;
    //          Key.Press |=KEY_Relay_Ctrl;
    ////        Key.Press |=KEY_BJRelay_Ctrl;
    //      }

    if (Bkgrd.PubData.tMngPlug)
    {
        Key.MngPlgDnTmr = 0;
        Key.MngPlgUpTmr = 0;
    }

    if (Key.CtrlModuPlgChk == 0xFF)//管理模组拔出
    {
        Key.MngPlgDnTmr = 0;
        Key.MngPlgUpTmr++;
        if (Key.MngPlgUpTmr >= EvtMngPlugPinTmr)
        {
            Key.MngPlgUpTmr = EvtMngPlugPinTmr;
            Key.Press |= KEY_VAL_CTRLMODUPLGCHKVS;
            if (Key.Release & KEY_VAL_CTRLMODUPLGCHKVS)
            {
                Key.Press |= KEY_VAL_CTRLMODUPLGCHK;    //管理模组拔出标志位置起
                Key.Release &= ~KEY_VAL_CTRLMODUPLGCHKVS;
            }
            Bkgrd.PubData.MtSysSta.SysStaBit.BothCoreValid = 0;
        }
    }
    if (Key.CtrlModuPlgChk == 0x00)//管理模组插上
    {
        Key.MngPlgUpTmr = 0;
        Key.MngPlgDnTmr++;
        if (Key.MngPlgDnTmr >= EvtMngPlugPinTmr)
        {
            Key.MngPlgDnTmr = EvtMngPlugPinTmr;
            Key.Release |= KEY_VAL_CTRLMODUPLGCHKVS;           //状态跟随
            if (Key.Press & KEY_VAL_CTRLMODUPLGCHKVS)
            {
                Key.Release |= KEY_VAL_CTRLMODUPLGCHK;          //管理模组插上标志位置起
                Key.Press &= ~KEY_VAL_CTRLMODUPLGCHKVS;
            }
        }
    }

    if (Key.KeyShell_Scan == 0x00)    //开上表盖按钮扫描
    {
        Key.Press |= 0X0020;              //状态跟随
        if (Key.Release & KEY_VAL_SHELLVS)
        {
            Key.Press |= 0X0040;              //记录开盖记录用
            Key.Release &= 0XFFBF;
        }
        Bkgrd.PubData.MtSysSta.SysStaBit.OpenCover = 1;  //开盖状态
    }
    if (Key.KeyShell_Scan == 0xFF)     //表盖常态合上盖状态
    {
        Key.Release |= 0X0020;           //状态跟随
        if (Key.Press & KEY_VAL_SHELLVS)
        {
            Key.Release |= 0X0040;          //记录合盖记录用
            Key.Press &= 0XFFBF;
        }

        Bkgrd.PubData.MtSysSta.SysStaBit.OpenCover = 0;  //合盖状态
    }
    if (Key.KeyJUNBOX_Scan == 0x00)    //开上表盖按钮扫描
    {
        Key.Press |= 0X0080;              //状态跟随
        if (Key.Release & KEY_VAL_JUNBOXVS)
        {
            Key.Press |= 0X0100;              //记录开盖记录用
            Key.Release &= 0XFEFF;
        }

        Bkgrd.PubData.MtSysSta.SysStaBit.OpenShell = 1;  //开盖状态
    }
    if (Key.KeyJUNBOX_Scan == 0xFF)     //表盖常态合上盖状态
    {
        Key.Release |= 0X0080;           //状态跟随
        if (Key.Press & KEY_VAL_JUNBOXVS)
        {
            Key.Release |= 0X0100;      //记录合盖记录用
            Key.Press &= 0XFEFF;
        }

        Bkgrd.PubData.MtSysSta.SysStaBit.OpenShell = 0;  //合盖状态
    }
    if (Key.StrongMan_Scan == 0x00)    //强磁场影响存在
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
    //  if (Key.RelayGataCheck ==0x00 )    //合闸状态
    //    {
    //          //if(Key.Release&KEY_VAL_RelayGataCheck)
    //      {
    //              Key.Press |= KEY_VAL_RelayGataCheck;
    //              Key.Release &= ~KEY_VAL_RelayGataCheck;
    //      }
    //    }
    //  if (Key.RelayGataCheck ==0xFF )  // 拉闸状态
    //  {
    //      Key.Release |= KEY_VAL_RelayGataCheck;
    //      Key.Press &= ~KEY_VAL_RelayGataCheck;
    //  }
    return;
}
