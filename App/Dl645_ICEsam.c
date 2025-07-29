
#define  _DL645_ICEsam_GLOBALS
#include <App.h>

void fnBcdInc(u8 *Dst, u8 Len)
{
    u8 temp1, temp2;
    u8 CBit = 0, i;
    temp1 = (Dst[Len - 1] & 0x0f) + 1;
    if (temp1 > 9)
    {
        temp1 += 6;
    }
    CBit = temp1 >> 4;
    temp2 = ((Dst[Len - 1] >> 4) & 0x0f) + CBit;
    if (temp2 > 9)
    {
        temp2 += 6;
    }
    CBit = temp2 >> 4;
    Dst[Len - 1] = ((temp2 << 4) & 0xf0) + (temp1 & 0x0f);
    for (i = 2 ; i < (Len + 1) ; i++)
    {
        temp1 = (Dst[Len - i] & 0x0f) + CBit;
        if (temp1 > 9)
        {
            temp1 += 6;
        }
        CBit = temp1 >> 4;
        temp2 = ((Dst[Len - i] >> 4) & 0x0f) + CBit;
        if (temp2 > 9)
        {
            temp2 += 6;
        }
        CBit = temp2 >> 4;
        Dst[Len - i] = ((temp2 << 4) & 0xf0) + (temp1 & 0x0f);
    }
}

//*********************************************************************************
// 函数名:  void ResetClear(u8 CH)
// 返回：   卡片或ESAM的RST脚拉低1MS
// 描述：   对ESAM或卡片进行冷复位
//*********************************************************************************

void fnResetClear(u8 CH)
{
    /*
     if (CH == CARD)                               // 1--卡片命令  0--ESAM命令
       ;
       //PinWrite_CardRst(0);
     else PinWrite_EsamRst(0); */
}

//*********************************************************************************
// 函数名:  void ResetSet(u8 CH)
// 返回：   卡片或ESAM的RST脚恢复
// 描述：   对ESAM或卡片进行冷复位后恢复
//*********************************************************************************

void fnResetSet(u8 CH)
{
    /*
    if (CH == CARD)                               // 1--卡片命令  0--ESAM命令
      ;
      //PinWrite_CardRst(1);
    else PinWrite_EsamRst(1);*/
}

//*********************************************************************************
// 函数名： ErrorStatus fnICEsam_CardTxRxFrame( u8 CH, u8 Lc, u8 Le )
// 输入：   CH 卡或ESAM选择 Lc 发送数据长度需减去5字节命令 Le接收长度
// 返回：   SUCCESS为正确，ERROR为不正确
// 描述：   卡发送及接收数据
//*********************************************************************************
ErrorStatus fnICEsam_CardTxRxFrame(u8 CH, u8 Lc, u8 Le)
{
    #if(0)
    u8 k, Temp_Data, Temp_SW1, Temp_SW2, Proc_Byte;
    ErrorStatus result;
    Std_Memset(ICEsamComm.Ic_Comm_RxBuf, 0x00, MAX_ICEsamCom_SIZE);
    for (k = 0; k < 5; k++) //send command header (5bytes)
    {
        result = fnCardSendByte(CH, ICEsamComm.Ic_Comm_TxBuf[k]);       //;取待发送数据
        if (result == ERROR)
        {
            return ERROR;    //send failure.
        }
    }
    for (;;)
    {
        result = fnCardGetByte(CH, &Proc_Byte);   //receive procedure byte.
        if (result != SUCCESS)
        {
            return ERROR;    //receive failure.
        }
        if (Proc_Byte == 0x60)
        {
            //do nothing. continue to receive.
        }
        else if (Proc_Byte == ICEsamComm.Ic_Comm_TxBuf[1])
        {
            if (k < (Lc + 5))   //send remaining data, then wait for procedure byte.
            {
                for (; k < (Lc + 5);)
                {
                    result = fnCardSendByte(CH, ICEsamComm.Ic_Comm_TxBuf[k++]);    //;取待发送数据
                    if (result == ERROR)
                    {
                        return ERROR;    //send failure.
                    }
                }
            }
            else
            {
                //;过程字节在之前已接收，只增加2个状态字节即可。
                for (ICEsamComm.Ic_Comm_RxPtr = 0x00; ICEsamComm.Ic_Comm_RxPtr < (Le + 2); ICEsamComm.Ic_Comm_RxPtr++)
                {
                    result = fnCardGetByte(CH, &Temp_Data);
                    if (result == ERROR)
                    {
                        return ERROR;
                    }   //;Receive fail

                    ICEsamComm.Ic_Comm_RxBuf[ICEsamComm.Ic_Comm_RxPtr] = Temp_Data;
                }
                return SUCCESS;
            }
        }
        else
        {
            Temp_SW1 = (Proc_Byte & 0xF0);
            if ((Temp_SW1 == 0x60) || (Temp_SW1 == 0x90))  //procedure byte = 6X or 9X (ex. 60H)
            {
                result = fnCardGetByte(CH, &Temp_SW2);   //receive sw2.
                if (result == ERROR)
                {
                    return ERROR;    //receive failure.
                }

                // 61H: send get response command, P3<=XX
                // 6CH: send last command again, P3 = XX;
                // other 6X or 9X, this communication is over.

                //'9000' command normally completed
                //'6E00' CLA not supported
                //'6D00' CLA supported, but INS not programmed or invalid
                //'6B00' CLA INS supported, but P1 P2 incorrect
                //'6700' CLA INS P1 P2 supported, but P3 incorrect
                //'6F00' command not supported and no precise diagnosis given

                ICEsamComm.Ic_Comm_RxBuf[0] = Proc_Byte;
                ICEsamComm.Ic_Comm_RxBuf[1] = Temp_SW2;
                ICEsamComm.Ic_Comm_RxPtr = 2;

                if ((Proc_Byte == 0x61) || (Proc_Byte == 0x90))
                {
                    return SUCCESS;
                }

                return ERROR;
            }
            else
            {
                return ERROR;
            }
        }
    }
    #endif
    return ERROR;
}

//*********************************************************************************
// 函数名： ErrorStatus fnICEsam_CardColdReset(u8 CH)
// 输入：   CH 卡或ESAM选择
// 返回：   SUCCESS为正确，ERROR为不正确
// 描述：   //触点激活&冷复位
//检测到卡插入后, RST置低电平, VCC上电, 延时一段时间, IO设置为输入态, CLK输出时钟信号(T0时刻)
//在T0后40000~45000个CLK内, 将RST置为高电平(T1时刻), 在T1后的400~40000个CLK内, 复位应答应该开始,
//若IC卡的复位应答没有在此时间段内开始, 终端将启动释放时序.若收到复位应答, 但不符合协议规范, 则需要热复位
//*********************************************************************************
ErrorStatus fnICEsam_CardColdReset(u8 CH)
{
    u8  i;
    u8  Temp_ATR;   // T0, TD1, TD2;
    ErrorStatus err;
    fnResetClear(CH);
    SystemDelay(1);
    fnResetSet(CH);
    for (i = 0; i < 13; i++)
    {
        err = fnCardGetByte(CH, &Temp_ATR);   //receive TS.
        if (err != SUCCESS)
        {
            return  ERROR;
        }
        ICEsamComm.Ic_Comm_RxBuf[i] = Temp_ATR;
    }
    if ((ICEsamComm.Ic_Comm_RxBuf[0] != 0x3b) || (ICEsamComm.Ic_Comm_RxBuf[1] != 0x69))
    {
        return  ERROR;
    }
    return  SUCCESS;
}

//禁止ESAM工作
void fnICEsam_CloseEsam(void)
{
    fnResetClear(ESAM);
    #if(SPI_ESAM)
    DISABLE_ESAM();
    #else
    CardFoutClose();            //关闭CLK
    #endif
    EsamPowerOff();
}

//ESAM复位
ErrorStatus fnICEsam_EsamReset(void)
{
    unsigned char i;

    for (i = 0; i < 3; i++)
    {
        if (fnICEsam_CardColdReset(ESAM) == ERROR)
        {
            fnICEsam_CloseEsam();       //释放ESAM
            SystemDelay(100);
            EsamPowerOn();
            SystemDelay(50);
            #if(SPI_ESAM)
            ENABLE_ESAM();
            #else
            CardFoutOpen();
            #endif
            SystemDelay(2);
        }
        else
        {
            return SUCCESS;
        }
    }
    return ERROR;
}

//判断卡片数据格式，判断数据效验和及头尾是否正确
ErrorStatus fnICEsam_JudgeFile(u8 Len)
{
    u8 i, Csdata;

    Csdata = 0x00;
    for (i = 1; i < Len + 4; i++)
    {
        Csdata += ICEsamComm.Ic_Comm_RxBuf[i];
    }
    if ((ICEsamComm.Ic_Comm_RxBuf[0] != 0x68) || (ICEsamComm.Ic_Comm_RxBuf[i + 0] != Csdata) || (ICEsamComm.Ic_Comm_RxBuf[i + 1] != 0x16))
    {
        return ERROR;    //帧格式错误: 68H/CS/16H
    }
    return SUCCESS;
}

void fnICEsam_RxTxCommhead(u8 inc, u8 com, u8 P1, u8 P2, u8 len)
{
    ICEsamComm.Ic_Comm_TxBuf[0] = inc;
    ICEsamComm.Ic_Comm_TxBuf[1] = com;
    ICEsamComm.Ic_Comm_TxBuf[2] = P1;
    ICEsamComm.Ic_Comm_TxBuf[3] = P2;
    ICEsamComm.Ic_Comm_TxBuf[4] = len;
}

//选择文件
ErrorStatus fnICEsam_SelectFile(u8 CH, u8 F1, u8 F2)
{
    ErrorStatus err;
    fnICEsam_RxTxCommhead(0, 0xa4, 0, 0, 2);
    ICEsamComm.Ic_Comm_TxBuf[5] = F1;   //DATA0
    ICEsamComm.Ic_Comm_TxBuf[6] = F2;   //DATA1

    err = fnICEsam_CardTxRxFrame(CH, 0x02, 0x00);

    return (err);
}

//读二进制文件
ErrorStatus fnICEsam_ReadBinFile(u8 CH, u8 P1, u8 P2, u8 Len)
{
    fnICEsam_RxTxCommhead(0, 0xb0, P1, P2, Len);

    fnICEsam_CardTxRxFrame(CH, 0x00, Len);

    if (ICEsamComm.Ic_Comm_RxPtr == (Len + 2))
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

//写二进制文件
ErrorStatus fnICEsam_WriteBinFile(u8 CH, u8 P1, u8 P2, u8 Len)
{
    ErrorStatus err;
    fnICEsam_RxTxCommhead(0, 0xD6, P1, P2, Len);

    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], ICEsamComm.Ic_Comm_RxBuf, Len);

    err = fnICEsam_CardTxRxFrame(CH, Len, 0x00);   //CARD Com

    return (err);
}

//读记录文件
ErrorStatus fnICEsam_ReadRecFile(u8 CH, u8 P1, u8 P2, u8 Len)
{
    ErrorStatus err;

    fnICEsam_RxTxCommhead(0, 0xb2, P1, P2, Len);

    err = fnICEsam_CardTxRxFrame(CH, 0x00, Len);

    return (err);
}

//取响应数据
ErrorStatus fnICEsam_Read_Kx(u8 CH, u8 Len)
{
    ErrorStatus err;

    fnICEsam_RxTxCommhead(0, 0xC0, 0, 0, Len);

    err = fnICEsam_CardTxRxFrame(CH, 0x00, Len);   //Esam Com

    if (err == SUCCESS)
    {
        if (ICEsamComm.Ic_Comm_RxPtr == Len + 2)
        {
            if ((ICEsamComm.Ic_Comm_RxBuf[ICEsamComm.Ic_Comm_RxPtr - 2] == 0x61)
                || ((ICEsamComm.Ic_Comm_RxBuf[ICEsamComm.Ic_Comm_RxPtr - 2] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[ICEsamComm.Ic_Comm_RxPtr - 1] == 0x00)))
            {
                return SUCCESS;
            }
        }
    }
    return (ERROR);
}

//取随机数
ErrorStatus fnICEsam_ReadRandom(u8 CH, u8 Len)
{
    fnICEsam_RxTxCommhead(0, 0x84, 0, 0, Len);
    if (SUCCESS == fnICEsam_CardTxRxFrame(CH, 0x00, Len))
    {
        if (CH == ESAM)
        {
            Std_Memcpy(ICEsamComm.EsamRand, ICEsamComm.Ic_Comm_RxBuf, Len);    //取ESAM随机数
        }
        else
        {
            Std_Memcpy(ICEsamComm.CardRand, ICEsamComm.Ic_Comm_RxBuf, Len);    //取卡片随机数
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

//加密，内部和外部认证命令
ErrorStatus fnICEsam_Auth_In_Out(u8 INS, u8 CH, u8 P2, u8 *BufA)
{
    ErrorStatus err;
    if (INS == 0xfa)
    {
        fnICEsam_RxTxCommhead(0x80, INS, 0, P2, 0x08);
    }
    else
    {
        fnICEsam_RxTxCommhead(0, INS, 0, P2, 0x08);
    }

    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], BufA, 8);

    err = fnICEsam_CardTxRxFrame(CH, 0x08, 0x00);   //CARD Com

    return (err);
}

//系统内部认证
ErrorStatus fnICEsam_Inter_Auth(u8 Psw)
{
    u8 i, K1[8], K2[8];

    fnICEsam_ReadRandom(ESAM, 8);           //从ESAM取8字节随机数

    fnICEsam_Auth_In_Out(0xfa, ESAM, 0x01, ICEsamComm.CardRst8B); //ESAM分散内部认证密钥

    fnICEsam_Auth_In_Out(0xfa, ESAM, 0x00, ICEsamComm.EsamRand);  //ESAM加密随机数

    fnICEsam_Read_Kx(ESAM, 0x08);           //取ESAM加密结果K1

    Std_Memcpy(K1, ICEsamComm.Ic_Comm_RxBuf, 8);

    fnICEsam_Auth_In_Out(0x88, CARD, Psw, ICEsamComm.EsamRand); //卡片加密随机数

    fnICEsam_Read_Kx(CARD, 0x08);           //取卡片加密结果K2

    Std_Memcpy(K2, ICEsamComm.Ic_Comm_RxBuf, 8);

    for (i = 0; i < 8; i++)
    {
        if (K1[i] != K2[i])
        {
            return ERROR;    //内部认证失败
        }
    }

    return SUCCESS;
}

//卡片外部认证
ErrorStatus fnICEsam_Card_Ext_Auth(u8 P2)
{
    ErrorStatus err;

    fnICEsam_ReadRandom(CARD, 8);           //从卡片取8字节随机数

    fnICEsam_Auth_In_Out(0xfa, ESAM, 0x02, ICEsamComm.CardRst8B);  //ESAM分散外部认证密钥

    err = fnICEsam_Auth_In_Out(0xfa, ESAM, 0x00, ICEsamComm.CardRand); //ESAM加密随机数
    if (err == ERROR)
    {
        return ERROR;
    }

    fnICEsam_Read_Kx(ESAM, 0x08);           //取加密结果

    err = fnICEsam_Auth_In_Out(0x82, CARD, P2, ICEsamComm.Ic_Comm_RxBuf); //卡片做外部认证
    if (err == ERROR)
    {
        return ERROR;
    }

    return SUCCESS;
}

// 红外认证指令
ErrorStatus fnICEsam_HW_RemoteAuth(u8 *Buf)
{
    ErrorStatus err;
    fnICEsam_RxTxCommhead(0x00, 0x82, 0x00, 0x08, 0x08);
    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], Buf, 8);

    err = fnICEsam_CardTxRxFrame(ESAM, 0x08, 0x00);   //CARD Com

    if ((err == SUCCESS) && (ICEsamComm.Ic_Comm_RxPtr == 2) && ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61) || ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))))
    {
        return (SUCCESS);
    }
    else
    {
        return (ERROR);
    }
}

// 远程身份认证指令
ErrorStatus fnICEsam_Authorization(u8 *Buf)
{
    u8 i;
    ErrorStatus err;
    //电能表对ESAM操作命令详解：
    //a）密钥分散命令：80fa000108+8字节分散因子；
    //;Esam encryp random data.
    err = fnICEsam_Auth_In_Out(0xfa, ESAM, 0x03, Buf + 16);
    if (!((err == SUCCESS) && (ICEsamComm.Ic_Comm_RxPtr == 0x02) && (ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00)))
    {
        return ERROR;
    }
    //b）加密随机数命令：80fa000008+随机数；
    err = fnICEsam_Auth_In_Out(0xfa, ESAM, 0x00, Buf + 8);
    if (!((err == SUCCESS) && (ICEsamComm.Ic_Comm_RxPtr == 0x02) && (ICEsamComm.Ic_Comm_RxBuf[0] == 0x61) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x08)))
    {
        return ERROR;
    }
    //c）取密文命令：00c0000008；
    //比较密文1和密文2, 两者不相等则报警, 相等则继续下面操作
    //;Read K2 from Esam
    err = fnICEsam_Read_Kx(ESAM, 0x08);
    if (err != SUCCESS)
    {
        return ERROR;
    }
    for (i = 0; i < 8; i++)
    {
        if (Buf[i] != ICEsamComm.Ic_Comm_RxBuf[i])
        {
            return ERROR;
        }
    }
    //取随机数2：0084000004
    //;Read random in ESAM
    err = fnICEsam_ReadRandom(ESAM, 4);
    if (!((err == SUCCESS) && (ICEsamComm.Ic_Comm_RxPtr == 0x06) && (ICEsamComm.Ic_Comm_RxBuf[4] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[5] == 0x00)))
    {
        return ERROR;
    }
    return  SUCCESS;
}

//带MAC读取二进制文件,远程费控使用
ErrorStatus fnICEsam_ReadBin2BinWithMac(u8 Ins, u8 P1, u8 P2, u8 Len)
{
    u8 i, k, n;
    ErrorStatus err;

    for (n = 0; n < 2; n++)
    {
        k = 0x05;
        fnICEsam_RxTxCommhead(0x04, Ins, P1, P2, 0x11);

        for (i = 0; i < 4; i++)
        {
            ICEsamComm.Ic_Comm_TxBuf[k++] = ICEsamComm.PcRand[i];
        }

        ICEsamComm.Ic_Comm_TxBuf[k++] = 0x04;
        ICEsamComm.Ic_Comm_TxBuf[k++] = 0xD6;
        ICEsamComm.Ic_Comm_TxBuf[k++] = 0x86;

        if (Ins == 0xB2)
        {
            ICEsamComm.Ic_Comm_TxBuf[k++] = 0x00;
        }
        else
        {
            ICEsamComm.Ic_Comm_TxBuf[k++] = P2;
        }

        ICEsamComm.Ic_Comm_TxBuf[k++] = Len + 12;

        Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[k], ICEsamComm.PcRst8B, 8);

        err = fnICEsam_CardTxRxFrame(ESAM, 0x11, 0x00);   //CARD Com

        if ((err == SUCCESS) && (ICEsamComm.Ic_Comm_RxPtr == 2) && ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61) || ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))))
        {
            break;
        }
    }

    if (n >= 2)
    {
        return ERROR;
    }

    err = fnICEsam_Read_Kx(ESAM, Len + 4); //返回预置电量+MAC
    return (err);
}

//带MAC读取二进制钱包文件,远程费控使用
ErrorStatus fnICEsam_ReadMoneyBagWithMac(u8 Ins, u8 P1, u8 P2, u8 Len)
{
    u8 i, k, n;
    ErrorStatus err;

    for (n = 0; n < 2; n++)
    {
        k = 0x05;
        fnICEsam_RxTxCommhead(0x04, Ins, P1, P2, 0x11);

        for (i = 0; i < 4; i++)
        {
            ICEsamComm.Ic_Comm_TxBuf[k++] = ICEsamComm.PcRand[i];
        }

        ICEsamComm.Ic_Comm_TxBuf[k++] = 0x04;
        ICEsamComm.Ic_Comm_TxBuf[k++] = 0xD6;
        ICEsamComm.Ic_Comm_TxBuf[k++] = 0x86;

        if (Ins == 0xB2)
        {
            ICEsamComm.Ic_Comm_TxBuf[k++] = 0x00;
        }
        else
        {
            ICEsamComm.Ic_Comm_TxBuf[k++] = P2;
        }

        ICEsamComm.Ic_Comm_TxBuf[k++] = 0x10;
        Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[k], ICEsamComm.PcRst8B, 8);

        err = fnICEsam_CardTxRxFrame(ESAM, 0x11, 0x00);   //CARD Com

        if ((err == SUCCESS) && (ICEsamComm.Ic_Comm_RxPtr == 2) && ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61) || ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))))
        {
            break;
        }
    }

    if (n >= 2)
    {
        return ERROR;
    }

    err = fnICEsam_Read_Kx(ESAM, Len + 4); //返回预置电量+MAC
    return (err);
}

//=====带MAC读取二进制文件
ErrorStatus fnICEsam_ReadBinWithMac(u8 CH, u8 P1, u8 P2, u8 M1, u8 M2, u8 Len)
{
    ErrorStatus err;
    if ((CH & 0x40) != 0x40)
    {
        if ((CH & 0x0f) == 0) //CH = ESAM
        {
            err = fnICEsam_ReadRandom(CARD, 4);
        }
        else                //CH = CARD
        {
            err = fnICEsam_ReadRandom(ESAM, 4);
        }

        if (err == ERROR)
        {
            return ERROR;
        }

        Std_Memcpy(ICEsamComm.CardRand, ICEsamComm.Ic_Comm_RxBuf, 4);
    }

    if ((CH == ESAM) || (CH == 0x20)) //ESAM with CardRst
    {
        Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[14], &ICEsamComm.CardRst8B[0], 8);
    }
    else if (CH == 0x11)    //CARD with ID
    {
        err = fnICEsam_ReadBinFile(ESAM, 0x82, 0x1e, 6);
        if (err == ERROR)
        {
            return ERROR;
        }

        ICEsamComm.Ic_Comm_TxBuf[14] = 0;
        ICEsamComm.Ic_Comm_TxBuf[15] = 0;

        Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[16], ICEsamComm.Ic_Comm_RxBuf, 6);//表号
    }
    else if (CH == 0x10)    //ESAM with ID
    {
        Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[14], &ICEsamComm.CardRst8B[0], 8);//卡序号
    }

    fnICEsam_RxTxCommhead(0x04, 0xb0, P1, P2, 0x11);
    if (CH == 0x20)
    {
        ICEsamComm.Ic_Comm_TxBuf[1] = 0xb2;
    }
    if ((CH == CARD) || (CH == 0x21) || (CH == 0x31) || ((CH & 0x40) == 0x40))
    {
        ICEsamComm.Ic_Comm_TxBuf[4] = 0x09;
    }
    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], ICEsamComm.CardRand, 4);

    ICEsamComm.Ic_Comm_TxBuf[9] = 0x04;
    ICEsamComm.Ic_Comm_TxBuf[10] = 0xd6;
    ICEsamComm.Ic_Comm_TxBuf[11] = M1;
    ICEsamComm.Ic_Comm_TxBuf[12] = M2;
    ICEsamComm.Ic_Comm_TxBuf[13] = Len;
    if ((CH & 0xbf) == 0x21)
    {
        ICEsamComm.Ic_Comm_TxBuf[10] = 0xdc;
    }
    else if ((CH & 0xbf) == 0x31)
    {
        ICEsamComm.Ic_Comm_TxBuf[10] = 0x32;
        ICEsamComm.Ic_Comm_TxBuf[9] = 0x84;
    }
    CH &= 0x01;
    fnICEsam_CardTxRxFrame(CH, ICEsamComm.Ic_Comm_TxBuf[4], 0x00);    //CARD Com

    err = fnICEsam_Read_Kx(CH, Len);   //返回data+MAC

    return (err);
}

//======带MAC更新二进制文件
ErrorStatus fnICEsam_WriteBinWithMac(u8 CH, u8 P1, u8 P2, u8 Len)
{
    u8  k;
    ErrorStatus err;
    k = 0x05;
    fnICEsam_RxTxCommhead(0x04, 0xd6, P1, P2, Len);
    if (CH > 1)
    {
        ICEsamComm.Ic_Comm_TxBuf[1] = 0xdc;
    }
    if (Len == 4)
    {
        ICEsamComm.Ic_Comm_TxBuf[0] = 0;    //CLA 不带MAC
    }
    CH &= 0x01;

    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[k], ICEsamComm.Ic_Comm_RxBuf, Len);

    err = fnICEsam_CardTxRxFrame(CH, Len, 0x00);   //CARD Com

    return (err);
}

//======带MAC存款操作
ErrorStatus fnICEsam_IncreseWithMac(u8 CH, u8 P1, u8 P2, u8 Len)
{
    ErrorStatus err;
    fnICEsam_RxTxCommhead(0x84, 0x32, P1, P2, Len);

    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], ICEsamComm.Ic_Comm_RxBuf, Len);

    err = fnICEsam_CardTxRxFrame(CH, Len, 0x00);   //CARD Com

    return (err);
}

//======退费处理
ErrorStatus fnICEsam_ReturnMoney(u8 *Buf)
{
    ErrorStatus err;
    fnICEsam_RxTxCommhead(0x84, 0x30, 0x02, 0x0c, 0x08);

    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], Buf, 0x08);

    err = fnICEsam_CardTxRxFrame(ESAM, 0x08, 0x00);   //CARD Com
    if ((err != SUCCESS) || (ICEsamComm.Ic_Comm_RxBuf[0] != 0x61))
    {
        return (ERROR);
    }
    err = fnICEsam_Read_Kx(ESAM, 0x08);
    return (err);
}

//扣款处理程序
ErrorStatus fnICEsam_Decrease(u8 CH, u8 P1, u8 P2, u8 Money)
{
    ErrorStatus err;
    fnICEsam_RxTxCommhead(0x80, 0x30, P1, P2, 0x04);

    ICEsamComm.Ic_Comm_TxBuf[5] = 0x00;
    ICEsamComm.Ic_Comm_TxBuf[6] = 0x00;
    ICEsamComm.Ic_Comm_TxBuf[7] = 0x00;
    ICEsamComm.Ic_Comm_TxBuf[8] = Money;

    err = fnICEsam_CardTxRxFrame(CH, 0x04, 0x00);   //CARD Com

    return (err);
}

// 99级密码，明文+MAC写ESAM中文件信息
ErrorStatus fnICEsam_Update_ESAM_Bin_Mac(u8 P1, u8 P2, u8 *Buf, u8 Len)
{
    u8 i, k;
    ErrorStatus err;

    k = 0x05;
    fnICEsam_RxTxCommhead(0x04, 0xd6, P1, P2, Len + 4);

    for (i = 0; i < (Len); i++)
    {
        ICEsamComm.Ic_Comm_TxBuf[k++] = Buf[(Len - 1) - i];
    }

    for (i = 0; i < 4; i++)
    {
        ICEsamComm.Ic_Comm_TxBuf[k++] = Buf[(Len + 3) - i];
    }

    err = fnICEsam_CardTxRxFrame(ESAM, Len + 4, 0x00); //CARD Com

    if ((err == SUCCESS) && (ICEsamComm.Ic_Comm_RxPtr == 0x02) && (ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))
    {
        err = SUCCESS;
    }

    fnICEsam_MacErrInc(err);

    return (err);
}

// 99级密码，明文+MAC写ESAM中费率电价文件文件信息
ErrorStatus fnICEsam_Update_BackMoneyFile(u8 P1, u8 P2, u8 *Buf, u8 Len)
{
    ErrorStatus err;

    fnICEsam_RxTxCommhead(0x04, 0xd6, P1, P2, Len);

    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], &Buf[0], Len);

    err = fnICEsam_CardTxRxFrame(ESAM, Len, 0x00);   //CARD Com

    if ((err == SUCCESS) && (ICEsamComm.Ic_Comm_RxPtr == 0x02) && (ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))
    {
        err = SUCCESS;
    }

    fnICEsam_MacErrInc(err);

    return (err);
}

// 98级密码，控制命令处理
ErrorStatus fnICEsam_RemoteControl(u8 *Buf, u8 Len, u8 P2)
{
    u8 i, k;
    ErrorStatus err;

    k = 0x05;
    fnICEsam_RxTxCommhead(0x04, 0xd6, P2, 00, Len);

    for (i = 0; i < (Len); i++)
    {
        ICEsamComm.Ic_Comm_TxBuf[k++] = Buf[(Len - 1) - i];
    }

    err = fnICEsam_CardTxRxFrame(ESAM, Len, 0x00);   //CARD Com

    if ((err == SUCCESS) && (ICEsamComm.Ic_Comm_RxPtr == 0x02) && (ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))
    {
        err = SUCCESS;
    }
    fnICEsam_MacErrInc(err);
    return (err);
}

ErrorStatus fnICEsam_UpdatePSW(u8 P1, u8 P2, u8 *Buf)
{
    u8 i;
    ErrorStatus err;

    fnICEsam_RxTxCommhead(0x84, 0xd4, P1, P2, 0x20);

    for (i = 0x00; i < 0x20; i++)
    {
        ICEsamComm.Ic_Comm_TxBuf[5 + i] = Buf[0x20+7 - i];
    }

    err = fnICEsam_CardTxRxFrame(ESAM, 0x20, 0x00);   //CARD Com

    fnICEsam_MacErrInc(err);

    if (err != SUCCESS)
    {
        return ERROR;
    }

    //发更新密钥信息指令：04D6860008+密钥信息+MAC
    fnICEsam_RxTxCommhead(0x04, 0xd6, 0x86, 0, 0x08);

    for (i = 0; i < 8; i++)
    {
        ICEsamComm.Ic_Comm_TxBuf[5 + i] = Buf[7 - i];
    }

    err = fnICEsam_CardTxRxFrame(ESAM, 8, 0x00);   //CARD Com

    return (err);
}

ErrorStatus fnICEsam_VerifyUpdatePSW(u8 *Buf, u8 Len)
{
    ErrorStatus err;
    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], Buf, Len);
    fnICEsam_RxTxCommhead(0x04, 0xd6, 0x96, 0x00, Len);

    err = fnICEsam_CardTxRxFrame(ESAM, Len, 0x00);
    if ((err == SUCCESS) && (ICEsamComm.Ic_Comm_RxPtr == 2) && ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61) || ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))))
    {
        err = SUCCESS;
    }
    return (err);
}

//更新密钥
ErrorStatus fnICEsam_UpdateKey(u8 P1)
{
    ErrorStatus err;

    fnICEsam_RxTxCommhead(0x84, 0xd4, 1, P1, 0x20);

    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], ICEsamComm.Ic_Comm_RxBuf, 0x20);

    err = fnICEsam_CardTxRxFrame(ESAM, 0x20, 0x00);

    return (err);
}

ErrorStatus fnICEsam_Clear_Rand_Gene(void)
{
    ErrorStatus err;
    Std_Memset(ICEsamComm.PcRand,  0x00, 8);
    Std_Memset(ICEsamComm.PcRst8B, 0x00, 8);

    //  if( progenable == 0 )   //编程使能标志 失效
    //  {
    //      first_prog_flag = 0;//清首次编程标志
    //  }

    err = fnICEsam_EsamReset();

    return (err);
}

// 更新ESAM中运行信息文件中的返写时间
ErrorStatus fnICEsam_UpdateRunFile_Clock(void)
{
    ErrorStatus err;
    u8  ChkSum, i;

    ICEsamComm.Ic_Comm_RxBuf[0] = SysClock.Year;
    ICEsamComm.Ic_Comm_RxBuf[1] = (SysClock.Month & 0x1f);
    ICEsamComm.Ic_Comm_RxBuf[2] = SysClock.Day;
    ICEsamComm.Ic_Comm_RxBuf[3] = SysClock.Hour;
    ICEsamComm.Ic_Comm_RxBuf[4] = SysClock.Minute;

    err = fnICEsam_WriteBinFile(ESAM, 0x87, 42, 5);                 //更新返写时间和非法次数

    fnWDT_Restart();
    ICEsamComm.Ic_Comm_RxBuf[0] = 0x68;
    ICEsamComm.Ic_Comm_RxBuf[1] = 0x11;
    ICEsamComm.Ic_Comm_RxBuf[2] = 0x00;
    ICEsamComm.Ic_Comm_RxBuf[3] = 0x2b;
    fnICEsam_WriteBinFile(ESAM, 0x87, 0, 4);
    fnWDT_Restart();
    //更新CS
    fnICEsam_ReadBinFile(ESAM, 0x87, 1, 46);

    ChkSum = 0;
    for (i = 0; i < 46; i++)
    {
        ChkSum += ICEsamComm.Ic_Comm_RxBuf[i];
    }

    ICEsamComm.Ic_Comm_RxBuf[0] = ChkSum;
    ICEsamComm.Ic_Comm_RxBuf[1] = 0x16;
    fnICEsam_WriteBinFile(ESAM, 0x87, 47, 2);
    fnWDT_Restart();
    return (err);
}

ErrorStatus fnICEsam_ReadUserNoFile(void)
{
    ErrorStatus err;
    err = fnICEsam_ReadBinWithMac(CARD + 0x40, 0x81, 36, 0x82, 36, 7 + 4);
    if (err == ERROR)
    {
        return (err);
    }
    Std_Memcpy(&ICEsamReadBuf.CardUserNo[0], &ICEsamComm.Ic_Comm_RxBuf[0], 11);
    return (SUCCESS);
}

ErrorStatus fnICEsam_ReadParaFile(void)
{
    ErrorStatus err;
    err = fnICEsam_ReadBinWithMac(CARD + 0x40, 0x81, 16, 0x82, 16, 14 + 4);
    if (err == ERROR)
    {
        return (err);
    }
    Std_Memcpy(&ICEsamReadBuf.CardParaBuf[0], &ICEsamComm.Ic_Comm_RxBuf[0], 18);
    return (SUCCESS);
}

ErrorStatus fnICEsam_ReadUpdataFlag(void)
{
    ErrorStatus err;
    err = fnICEsam_ReadBinWithMac(CARD, 0x81, 5, 0x82, 5, 1 + 4);
    if (err == ERROR)
    {
        return (err);
    }
    Std_Memcpy(&ICEsamReadBuf.CardUpdataFlag[0], &ICEsamComm.Ic_Comm_RxBuf[0], 5);
    return (SUCCESS);
}

ErrorStatus fnICEsam_ReadPriceSwitchTime(void)
{
    ErrorStatus err;
    err = fnICEsam_ReadBinWithMac(CARD, 0x81, 10, 0x82, 10, 5 + 4);
    if (err == ERROR)
    {
        return (err);
    }
    Std_Memcpy(&ICEsamReadBuf.CardPriceSwitchTime[0], &ICEsamComm.Ic_Comm_RxBuf[0], 9);
    return (SUCCESS);
}

//读取ESAM费率文件
ErrorStatus fnICEsam_ReadFlLadderFile(u8 Flag)
{
    /*
       ErrorStatus err;
    //  u8 CheckSum;
    //  u16 i;
       //============ 更新费率文件03================
       if((Flag & 0x0f)==0)  return ( SUCCESS );   //不进行费率文件的更新
       fnWDT_Restart();
       if(Flag & 0x05)
       {
           fnWDT_Restart();
           err = fnICEsam_ReadBinWithMac( CARD+0x40, 0x83, 0, 0x83, 0, 132+4 );
           if( err == ERROR ) return ( err );
           Std_Memcpy(&ICEsamReadBuf.CardPricePara1Buf[0] ,&ICEsamComm.Ic_Comm_RxBuf[0] , 136);
           fnWDT_Restart();
           err = fnICEsam_ReadBinWithMac( CARD+0x40, 0x83, 132, 0x83, 132, 126+4 );
           if( err == ERROR ) return ( err );
           Std_Memcpy(&ICEsamReadBuf.CardPricePara1Buf[136] ,&ICEsamComm.Ic_Comm_RxBuf[0] , 130);
    //      CheckSum = 0;
           fnWDT_Restart();
    //      for(i=1;i<260;i++)
    //      {
    //          if(i == 132 ) i +=4;
    //          else CheckSum +=ICEsamReadBuf.CardPricePara1Buf[i];
    //      }
    //      if( (ICEsamReadBuf.CardPricePara1Buf[0] != 0x68) || (ICEsamReadBuf.CardPricePara1Buf[i+0] != CheckSum) || (ICEsamReadBuf.CardPricePara1Buf[i+1] != 0x16) ) return ERROR;
       }

       //============ 更新费率文件04================
       if(Flag & 0x0A)
       {
           fnWDT_Restart();
           err = fnICEsam_ReadBinWithMac( CARD+0x40, 0x84, 0, 0x84, 0, 132+4 );
           if( err == ERROR ) return ( err );
           Std_Memcpy(&ICEsamReadBuf.CardPricePara2Buf[0] ,&ICEsamComm.Ic_Comm_RxBuf[0] , 136);
           fnWDT_Restart();
           err = fnICEsam_ReadBinWithMac( CARD+0x40, 0x84, 132, 0x84, 132, 126+4 );
           if( err == ERROR ) return ( err );
           Std_Memcpy(&ICEsamReadBuf.CardPricePara2Buf[136] ,&ICEsamComm.Ic_Comm_RxBuf[0] , 130);
           fnWDT_Restart();
    //      CheckSum = 0;
           fnWDT_Restart();
    //      for(i=1;i<260;i++)
    //      {
    //          if(i == 132 ) i +=4;
    //          else CheckSum +=ICEsamReadBuf.CardPricePara2Buf[i];
    //      }
    //      if( (ICEsamReadBuf.CardPricePara2Buf[0] != 0x68) || (ICEsamReadBuf.CardPricePara2Buf[i+0] != CheckSum) || (ICEsamReadBuf.CardPricePara2Buf[i+1] != 0x16) ) return ERROR;
           if(Flag & 0x02)
           {
               err = fnICEsam_ReadBinWithMac( CARD +0x40, 0x81, 10, 0x82, 10, 5+4 );
               if( err ==ERROR) return( err);
               Std_Memcpy(&ICEsamReadBuf.CardPriceSwitchTime[0] ,&ICEsamComm.Ic_Comm_RxBuf[0] , 9);
           }
       }*/
    return (SUCCESS);
}

// 钱包初始化处理
ErrorStatus fnICEsam_ReadMoneyBag(void)
{
    /*
       ErrorStatus result = SUCCESS;

       result =fnICEsam_ReadBinWithMac( CARD+0x20+0x40, 0x85, 0, 0x01, 0x0c, 4+4 );
       if( result ==ERROR ) return (result);
       Std_Memcpy(&ICEsamReadBuf.CardMoneyBag[0] ,&ICEsamComm.Ic_Comm_RxBuf[0] , 8);
       result = fnICEsam_ReadBinWithMac( CARD+0x20+0x40, 0x85, 4, 0x03, 0x0c, 4+4 );
       if( result ==ERROR ) return (result);
       Std_Memcpy(&ICEsamReadBuf.CardMoneyBag[8] ,&ICEsamComm.Ic_Comm_RxBuf[0] , 8);*/
    return (SUCCESS);
}

void fnICEsam_ReadEpFlData(void)
{
    // 读取EEPROM中第1，2套费率

    //  {
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15), &BufTemp[4], sizeof(sDF13)*MAX_FL);
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15) + (sizeof(sDF13) * MAX_FL), &BufTemp[4 + sizeof(sDF13) * MAX_FL], sizeof(sDF13)*MAX_FL);
    //  }

    Std_Memcpy(&BufTemp[0], &ICEsamComm.CardRst8B[4], 4);
}

void fnICEsam_ReadEpLadderData(void)
{
    // 读取EEPROM中第1，2套阶梯电价
    //  if(Bkgrd.PubData.MtSta.MtSta3.StaBit.CurLadder == 1 )
    //  {
    //      fnFile_Read(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_LadderPara + 5 , &BufTemp[36+68] , 24 );
    //      fnFile_Read(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_LadderPara + 5 + 48, &BufTemp[36+92] , 28 );
    //      fnFile_Read(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_LadderPara + 5 + 104,&BufTemp[36+120] , 12 );
    //
    //      fnFile_Read(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_LadderPara + 5 + 24, &BufTemp[36+4] , 24 );
    //      fnFile_Read(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_LadderPara + 5 + 76, &BufTemp[36+28] , 28 );
    //      fnFile_Read(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_LadderPara + 5 + 116,&BufTemp[36+56] , 12 );
    //  }
    //  else
    //  {
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5, &BufTemp[36 + 4], 24);
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 48, &BufTemp[36 + 28], 28);
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 104, &BufTemp[36 + 56], 12);
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 24, &BufTemp[36 + 68], 24);
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 76, &BufTemp[36 + 92], 28);
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 116, &BufTemp[36 + 120], 12);
    //  }
    Std_Memcpy(&BufTemp[36], &ICEsamComm.CardRst8B[4], 4);
}

//更新ESAM费率文件
ErrorStatus fnICEsam_WriteFlLadderFile(u8 Flag, u8 CardType)
{
    #if(0)
    ErrorStatus err;
    u16 i;
    fnWDT_Restart();
    //============ 更新费率文件03================
    if ((Flag & 0x0f) == 0)
    {
        return (SUCCESS);    //不进行费率文件的更新
    }
    fnWDT_Restart();
    if (Flag & 0x05)
    {
        if (Flag & 0x01)
        {
            if (CardType != PresetCard)
            {
                fnICEsam_ReadEpFlData();
            }
            Std_Memcpy(ICEsamComm.Ic_Comm_RxBuf, &ICEsamReadBuf.CardPricePara1Buf[0],  132 + 4);
            err = fnICEsam_WriteBinWithMac(ESAM, 0x83, 0, 132 + 4);
            if (err == ERROR)
            {
                return (err);
            }
            fnWDT_Restart();
            //更新EE中第1套费率文件
            for (i = 0; i < MAX_FL; i++)
            {
                fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[9 + 4 * i], 4);
            }
            //if(Bkgrd.PubData.MtSta.MtSta3.StaBit.CurRatePrice == 1 )      // 当前运行第二套费率
            //{
            //  fnFile_Write(FileId_RatePara , FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15) + (sizeof(sDF13) * MAX_FL) , &ICEsamComm.Ic_Comm_TxBuf[9] , sizeof(sDF13)*MAX_FL);
            //}
            //else              // 当前运行第一套费率
            //{
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15), &ICEsamComm.Ic_Comm_TxBuf[9], sizeof(sDF13)*MAX_FL);
            //}
            fnWDT_Restart();
            if (CardType != PresetCard)
            {
                fnDl645Event_Operation(EVENT_STYLE_PrgRatePrice, EVENT_OPERATION_START, &BufTemp[0], &BufTemp[4]);    // 写费率表编程事件
            }
        }
        if (Flag & 0x04)
        {
            if (CardType != PresetCard)
            {
                fnICEsam_ReadEpLadderData();
            }
            fnWDT_Restart();
            Std_Memcpy(ICEsamComm.Ic_Comm_RxBuf, &ICEsamReadBuf.CardPricePara1Buf[0],  2);
            err = fnICEsam_WriteBinWithMac(ESAM, 0x83, 132, 130);
            if (err == ERROR)
            {
                return (err);
            }
            fnWDT_Restart();
            //更新EE中第1套阶梯电价文件
            for (i = 0; i < 13 ; i++)
            {
                fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[5 + 4 * i], 4);
            }
            for (i = 0; i < 4; i++)
            {
                fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[57 + 3 * i], 3);
            }
            fnWDT_Restart();
            //if(Bkgrd.PubData.MtSta.MtSta3.StaBit.CurLadder == 1 )
            //{
            //  fnWDT_Restart();
            //  fnFile_Write(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_LadderPara + 5 + sizeof(sFsEgSh_TypeDef) * MAX_LADDER , &ICEsamComm.Ic_Comm_TxBuf[5] , sizeof(sFsEgSh_TypeDef) * MAX_LADDER);
            //  fnFile_Write(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_LadderPara + 5 + 76 , &ICEsamComm.Ic_Comm_TxBuf[5+24] , sizeof(sFsEgSh_TypeDef) * (DL645_MAX_LADDER+1));
            //  fnFile_Write(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_LadderPara + 5 + 116 , &ICEsamComm.Ic_Comm_TxBuf[57] , 12);
            //}
            //else
            //{
            fnWDT_Restart();
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5, &ICEsamComm.Ic_Comm_TxBuf[5], sizeof(sFsEgSh_TypeDef) * MAX_LADDER);
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 48, &ICEsamComm.Ic_Comm_TxBuf[5 + 24], sizeof(sFsEgSh_TypeDef) * (MAX_LADDER + 1));
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 104, &ICEsamComm.Ic_Comm_TxBuf[57], 12);
            //}
            if (CardType != PresetCard)
            {
                for (i = 0; i < 4; i++)
                {
                    if ((ICEsamComm.Ic_Comm_TxBuf[57 + 3 * i] == BufTemp[36 + 56 + 3 * i]) && (ICEsamComm.Ic_Comm_TxBuf[58 + 3 * i] == BufTemp[37 + 56 + 3 * i])
                        && (ICEsamComm.Ic_Comm_TxBuf[59 + 3 * i] == BufTemp[38 + 56 + 3 * i])) ;
                    else
                    {
                        Bkgrd.PubData.SetRmYearFlag |= 0x02;
                    }
                }
                fnDl645Event_Operation(EVENT_STYLE_PrgLadderPrice, EVENT_OPERATION_START, &BufTemp[36], &BufTemp[36 + 4]);   // 写阶梯表编程事件
            }
        }
    }

    //============ 更新费率文件04================
    if (Flag & 0x0A)
    {
        if (Flag & 0x02)
        {
            if (CardType != PresetCard)
            {
                fnICEsam_ReadEpFlData();
            }
            fnWDT_Restart();
            Std_Memcpy(ICEsamComm.Ic_Comm_RxBuf, &ICEsamReadBuf.CardPricePara2Buf[0],  132 + 4);
            err = fnICEsam_WriteBinWithMac(ESAM, 0x84, 0, 132 + 4);
            if (err == ERROR)
            {
                return (err);
            }
            fnWDT_Restart();

            for (i = 0; i < MAX_FL; i++)
            {
                fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[9 + 4 * i], 4);
            }
            //if(Bkgrd.PubData.MtSta.MtSta3.StaBit.CurRatePrice == 1 )      // 当前运行第二套费率
            //{
            //  fnFile_Write(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15) , &ICEsamComm.Ic_Comm_TxBuf[9] , sizeof(sDF13)*MAX_FL );
            //}
            //else              // 当前运行第一套费率
            //{
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15) + (sizeof(sDF13) * MAX_FL), &ICEsamComm.Ic_Comm_TxBuf[9], sizeof(sDF13)*MAX_FL);
            //}
            fnWDT_Restart();
            if (CardType != PresetCard)
            {
                fnDl645Event_Operation(EVENT_STYLE_PrgRatePrice, EVENT_OPERATION_START, &BufTemp[0], &BufTemp[4]);    // 写费率表编程事件
            }
        }
        if (Flag & 0x08)
        {
            if (CardType != PresetCard)
            {
                fnICEsam_ReadEpLadderData();
            }
            fnWDT_Restart();
            Std_Memcpy(ICEsamComm.Ic_Comm_RxBuf, &ICEsamReadBuf.CardPricePara2Buf[0],  2);
            err = fnICEsam_WriteBinWithMac(ESAM, 0x84, 132, 130);
            if (err == ERROR)
            {
                return (err);
            }
            fnWDT_Restart();

            //更新EE中第1套阶梯电价文件
            for (i = 0; i < 13 ; i++)
            {
                fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[5 + 4 * i], 4);
            }
            for (i = 0; i < 4; i++)
            {
                fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[57 + 3 * i], 3);
            }

            //          if(Bkgrd.PubData.MtSta.MtSta3.StaBit.CurLadder == 1 )
            //          {
            //              fnWDT_Restart();
            //              fnFile_Write(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_LadderPara + 5 , &ICEsamComm.Ic_Comm_TxBuf[5] , sizeof(sFsEgSh_TypeDef) * MAX_LADDER);
            //              fnFile_Write(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_LadderPara + 5 + 48, &ICEsamComm.Ic_Comm_TxBuf[5+24] , sizeof(sFsEgSh_TypeDef) * (MAX_LADDER+1));
            //              fnFile_Write(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_LadderPara + 5 + 104 , &ICEsamComm.Ic_Comm_TxBuf[57] , 12);
            //          }
            //          else
            //          {
            fnWDT_Restart();
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + sizeof(sFsEgSh_TypeDef) * MAX_LADDER, &ICEsamComm.Ic_Comm_TxBuf[5], sizeof(sFsEgSh_TypeDef) * MAX_LADDER);
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 76, &ICEsamComm.Ic_Comm_TxBuf[5 + 24], sizeof(sFsEgSh_TypeDef) * (MAX_LADDER + 1));
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 116, &ICEsamComm.Ic_Comm_TxBuf[57], 12);
            //          }
            Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], &ICEsamReadBuf.CardPricePara2Buf[2], 5);
            //更新EE中2套阶梯电价切换时间
            fnWDT_Restart();
            fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[5], 5);
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 0, &ICEsamComm.Ic_Comm_TxBuf[5], 5);
            fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Misc + 15, &i, 1);
            i &= 0x7f;
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Misc + 15, &i, 1);
            fnWDT_Restart();
            if (CardType != PresetCard)
            {
                fnDl645Event_Operation(EVENT_STYLE_PrgLadderPrice, EVENT_OPERATION_START, &BufTemp[36], &BufTemp[36 + 4]);    // 写阶梯表编程事件
            }
            Bkgrd.PubData.UpFlStatusFlag = 0x5a;
        }
        if (Flag & 0x02)
        {
            fnWDT_Restart();
            Std_Memcpy(ICEsamComm.Ic_Comm_RxBuf, &ICEsamReadBuf.CardPriceSwitchTime[0],  9);
            err = fnICEsam_WriteBinWithMac(ESAM, 0x82, 10, 5 + 4);
            if (err == ERROR)
            {
                return (err);
            }
            fnWDT_Restart();
            //更新EE中第2套费率文件
            fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[5], 5);
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara, &ICEsamComm.Ic_Comm_TxBuf[5], 0x05);
            fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Misc + 14, &i, 1);
            i &= 0x7f;
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Misc + 14, &i, 1);
            Bkgrd.PubData.UpFlStatusFlag = 0x5a;
        }
    }
    fnWDT_Restart();
    #endif
    return (SUCCESS);
}

ErrorStatus fnICEsam_UpdateRunFile_Money(void)
{
    ErrorStatus err;
    sFsEgSh_TypeDef tempData;

    Std_Memcpy((u8 *)&tempData, &EgMoney.PubData.CurSurplusMoney.Dat2, 4);              //剩余金额
    tempData.Dat = fnBcdToHex_u32(tempData.Dat);
    Std_Memcpy((u8 *)&ICEsamComm.Ic_Comm_RxBuf, (u8 *)&tempData, 4);
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[0], 4);

    Std_Memcpy((u8 *)&tempData, (u8 *)&EgMoney.PubPara.nALLBuyMoney, 4);        //购电次数
    tempData.Dat = fnBcdToHex_u32(tempData.Dat);
    Std_Memcpy(&ICEsamComm.Ic_Comm_RxBuf[4], (u8 *)&tempData, 4);
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[4], 4);

    Std_Memcpy((u8 *)&tempData, &EgMoney.PubData.CurOverdraftMoney.Dat2, 4);            //透支金额
    //tempData.Dat = fnBcdToHex_u32(tempData.Dat);
    Std_Memcpy(&ICEsamComm.Ic_Comm_RxBuf[8], (u8 *)&tempData, 4);
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[8], 4);

    Std_Memset(&ICEsamComm.Ic_Comm_RxBuf[12], 0x00, 4);

    // 同步更新EEPROM中非法插卡次数
    //fnFile_Read(Dl645FileId_MiscEv , Dl645FileItemInfoOffAddr_MiscEv_InsertCardIllegal , &ICEsamComm.Ic_Comm_RxBuf[16] , sizeof(sDF10) );
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[16], sizeof(sDF10));
    err = fnICEsam_WriteBinFile(ESAM, 0x87, 23, 19);        //更新ESAM

    fnICEsam_UpdateRunFile_Clock();                 //更新运行文件时间
    return (err);
}

ErrorStatus fnICEsam_UpdateRunFile(void)
{
    ErrorStatus err;
    err = fnICEsam_ReadBinFile(ESAM, 0x82, 24, 18);
    if (err == ERROR)
    {
        return (err);    //读指令文件错误
    }
    err = fnICEsam_WriteBinFile(ESAM, 0x87, 5, 18);         //更新ESAM
    if (err == ERROR)
    {
        return (err);
    }
    err = fnICEsam_UpdateRunFile_Money();                   //更新运行文件时间
    return (err);
}

// 钱包文件处理
ErrorStatus fnICEsam_MoneyProc(void)
{
    u8 i;
    ErrorStatus err;
    sFsEgSh_TypeDef tempCurMoney;
    sFsEgSh_TypeDef tempEsamMoney;
    Std_Memcpy((u8 *)&tempCurMoney, (u8 *)&EgMoney.PubData.CurSurplusMoney.Dat2, 0x04);
    tempCurMoney.Dat = fnBcdToHex_u32(tempCurMoney.Dat);

    err = fnICEsam_ReadRecFile(ESAM, 0x01, 0x0c, 0x04); //读钱包剩余金额
    if (err == ERROR)
    {
        return (ERROR);
    }
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[0], 4);
    Std_Memcpy((u8 *)&tempEsamMoney, (u8 *)&ICEsamComm.Ic_Comm_RxBuf[0], 4); //ESAM钱包余额

    if (tempEsamMoney.Dat > tempCurMoney.Dat)
    {
        tempEsamMoney.Dat -= tempCurMoney.Dat;      //钱包 - 剩余

        Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], (u8 *)&tempEsamMoney, 4);
        fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[5], 4);

        ICEsamComm.Ic_Comm_TxBuf[0] = 0x80;     //CLA
        ICEsamComm.Ic_Comm_TxBuf[1] = 0x30;     //INS
        ICEsamComm.Ic_Comm_TxBuf[2] = 0x01;     //P1
        ICEsamComm.Ic_Comm_TxBuf[3] = 0x0c;     //P2
        ICEsamComm.Ic_Comm_TxBuf[4] = 0x05;     //Lc
        ICEsamComm.Ic_Comm_TxBuf[9] = 0;

        for (i = 0; i < 9; i++)
        {
            ICEsamComm.Ic_Comm_TxBuf[9] += ICEsamComm.Ic_Comm_TxBuf[i];
        }

        err = fnICEsam_CardTxRxFrame(ESAM, 0x05, 0x00);
    }

    fnICEsam_UpdateRunFile_Money(); //更新运行文件金额

    return (err);
}

// 判断购电金额是否超过囤积金额
ErrorStatus fnICEsam_JugeRegrate(u32 BuyMoney)
{
    u32  RegrateMoney;
    BuyMoney = fnHexToBcd_u32(BuyMoney);
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_ChargMoneyPara + sizeof(sDF11) * 7, &RegrateMoney, sizeof(sDF11));
    if (fnCrc_Check(1, (u8 *)&EgMoney.PubData.CurSurplusMoney, 12, (u8 *)&EgMoney.PubDataCrc.CurSurplusMoney))
    {
        fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_EgMoney + 8, (u8 *)&EgMoney.PubData.CurSurplusMoney, sizeof(sDF12));
        fnCrc_Check(0, (u8 *)&EgMoney.PubData.CurSurplusMoney, 12, (u8 *)&EgMoney.PubDataCrc.CurSurplusMoney);
    }
    if (fnDFCompData((u8 *)&BuyMoney, (u8 *)&EgMoney.PubData.CurOverdraftMoney.Dat2, 4) < 0)
    {
        return (SUCCESS);    // 购电金额小于透支金额
    }

    fnBcdSub_Bytes((u8 *)&BuyMoney, (u8 *)&EgMoney.PubData.CurOverdraftMoney.Dat2, 4);      //购电金额 - 透支金额
    fnBcdAdd_Bytes((u8 *)&BuyMoney, (u8 *)&EgMoney.PubData.CurSurplusMoney.Dat2, 4);      //购电金额 + 剩余金额
    if (fnDFCompData((u8 *)&BuyMoney, (u8 *)&EgMoney.PubData.CurSurplusMoney.Dat2, 4) < 0)
    {
        return (ERROR);    // 购电金额溢出
    }
    if (RegrateMoney == 0)
    {
        return (SUCCESS);
    }
    if (fnDFCompData((u8 *)&BuyMoney, (u8 *)&RegrateMoney, 4) <= 0)
    {
        return (SUCCESS);
    }
    else
    {
        return (ERROR);
    }
}

// 远程充值处理,buf[0]-buf[3] 购电金额,buf[4]-buf[7] 购电次数,buf[8]-buf[11] 购电次数
// CH ==0 远程充值  CH == 1 增加电费卡充值   CH == 2 用户卡充值
ErrorStatus fnIcEsam_AddMoney(u8 CH, u8 *Buf)
{
    u32 TempData;
    u8  i;
    u32 nBuyMoney;
    ErrorStatus err;
    sDF12 MoneyTemp;
    u8  OpCodeTemp[4];
    Std_Memcpy(&TempData, Buf, 4);
    TempData = fnHexToBcd_u32(TempData);
    Std_Memset((u8 *)&MoneyTemp, 0x00, 6);
    Std_Memcpy((u8 *)&MoneyTemp.Dat2, &TempData, 0x04);
    Std_Memset(OpCodeTemp, 0xff, 4);
    if (fnCrc_Check(1, (u8 *)&EgMoney.PubData.CurSurplusMoney, 12, (u8 *)&EgMoney.PubDataCrc.CurSurplusMoney))
    {
        fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_EgMoney + 14, (u8 *)&EgMoney.PubData.CurSurplusMoney, 12);
        fnCrc_Check(0, (u8 *)&EgMoney.PubData.CurSurplusMoney, 12, (u8 *)&EgMoney.PubDataCrc.CurSurplusMoney);
    }
    if (CH == 0)
    {
        fnDl645B_Inverse(&Buf[0], 4);
        fnDl645B_Inverse(&Buf[4], 4);
        fnDl645B_Inverse(&Buf[8], 4);
        Std_Memcpy(ICEsamComm.Ic_Comm_RxBuf, Buf, 12);
    }
    else
    {
        Std_Memcpy(ICEsamComm.Ic_Comm_RxBuf, &ICEsamReadBuf.CardMoneyBag[0], 12);
    }
    err = fnICEsam_IncreseWithMac(ESAM, 0x01, 0x0c, 8 + 4);     // 充值
    if (err == ERROR)
    {
        return (err);
    }

    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[9], 4);
    Std_Memcpy(&nBuyMoney, &ICEsamComm.Ic_Comm_TxBuf[9], 4);
    EgMoney.PubPara.nALLBuyMoney = fnHexToBcd_u32(nBuyMoney);

    Std_Memcpy(&Buf[8], (u8 *)&EgMoney.PubData.CurSurplusMoney.Dat2, 0x04);

    if (fnDFCompData((u8 *)&MoneyTemp, (u8 *)&EgMoney.PubData.CurOverdraftMoney, 0x06) < 0)    // 充值金额小于透支金额
    {
        fnBcdSub_Bytes((u8 *)&EgMoney.PubData.CurOverdraftMoney, (u8 *)&MoneyTemp, 0x06);
        Std_Memset((u8 *)&EgMoney.PubData.CurSurplusMoney, 0x00, 0x06);
        Std_Memcpy(&TempData, Buf, 4);                      // 扣减掉透支金额
        Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], &TempData, 4);

        ICEsamComm.Ic_Comm_TxBuf[0] = 0x80;     //CLA
        ICEsamComm.Ic_Comm_TxBuf[1] = 0x30;     //INS
        ICEsamComm.Ic_Comm_TxBuf[2] = 0x01;     //P1
        ICEsamComm.Ic_Comm_TxBuf[3] = 0x0c;     //P2
        ICEsamComm.Ic_Comm_TxBuf[4] = 0x05;     //Lc
        ICEsamComm.Ic_Comm_TxBuf[9] = 0;

        for (i = 0; i < 9; i++)
        {
            ICEsamComm.Ic_Comm_TxBuf[9] += ICEsamComm.Ic_Comm_TxBuf[i];
        }

        err = fnICEsam_CardTxRxFrame(ESAM, 0x05, 0x00);
    }
    else
    {
        fnBcdSub_Bytes((u8 *)&MoneyTemp, (u8 *)&EgMoney.PubData.CurOverdraftMoney, 0x06);
        fnBcdAdd_Bytes((u8 *)&EgMoney.PubData.CurSurplusMoney, (u8 *)&MoneyTemp, 0x06);
        Std_Memset((u8 *)&EgMoney.PubData.CurOverdraftMoney, 0x00, 0x06);
        fnICEsam_MoneyProc();    // 剩余电量处理
    }

    // 更新RAM及EEPROM
    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_EgMoney + 8, (u8 *)&EgMoney.PubData.CurSurplusMoney, 12);
    fnCrc_Check(0, (u8 *)&EgMoney.PubData.CurSurplusMoney, 12, (u8 *)&EgMoney.PubDataCrc.CurSurplusMoney);
    if (CH == 0)
    {
        fnDl645B_Inverse(&Buf[4], 4);
    }
    Std_Memcpy(&TempData, &Buf[4], 4);
    TempData = fnHexToBcd_u32(TempData);            // 购电次数
    Std_Memcpy(&Buf[4], &TempData, 4);
    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_EgMoney + 34, (u8 *)&TempData, 0x04);
    if (CH == 0)
    {
        fnDl645B_Inverse(&Buf[0], 4);
    }
    Std_Memcpy(&TempData, &Buf[0], 4);
    TempData = fnHexToBcd_u32(TempData);            // 购电金额
    Std_Memcpy(&Buf[0], &TempData, 4);
    fnDl645Event_Operation(EVENT_STYLE_BUYMONEY, EVENT_OPERATION_START, 0, &Buf[0]);      // 写购电记录
    // 合闸允许金额判断
    if (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus && (Bkgrd.PubData.CheckMoneyFlag == 0x5a))
    {
        fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_ChargMoneyPara + sizeof(sDF11) * 8, &TempData, 4);
        if (fnDFCompData((u8 *)&EgMoney.PubData.CurSurplusMoney.Dat2, (u8 *)&TempData, 0x04) >= 0)
        {
            fnFile_Write(FileId_BackUpCurMoney, FileItemInfoLen_BackUpCurMoney_CurSurplusMoney, &OpCodeTemp[0], 4);
            Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
            Bkgrd.PubData.MoneySta.Overdraft = 0;
            OpCodeTemp[0] = 0x9b;
            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &OpCodeTemp[0], 1);   //状态保存
            Bkgrd.PubData.CheckMoneyFlag = 0;
            fnFile_Write(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_CheckMoneyFlag, &Bkgrd.PubData.CheckMoneyFlag, 1);
        }
    }
    return SUCCESS;
}

//将ESAM中的参数更新到EEPROM中
ErrorStatus fnICEsam_EsamParaVarToEE(void)
{
    ErrorStatus Result;
    Result = fnICEsam_ReadBinFile(ESAM, 0x82, 10, 32);
    if (Result == ERROR)
    {
        return (ERROR);    //读指令文件错误
    }

    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[6], 4);
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[10], 4);
    fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_ChargMoneyPara + 16, &ICEsamComm.Ic_Comm_RxBuf[6], 0x08);
    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], &ICEsamComm.Ic_Comm_RxBuf[14], 18);
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[14], 3);
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[17], 3);
    Std_Memcpy((u8 *)&EgMoney.PubPara.MeterCT, &ICEsamComm.Ic_Comm_RxBuf[14], 6);

    fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_CT, &ICEsamComm.Ic_Comm_RxBuf[14], 0x03);
    fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_PT, &ICEsamComm.Ic_Comm_RxBuf[17], 0x03);
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[20], 6);
    fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_MeterNo, &ICEsamComm.Ic_Comm_RxBuf[20], 0x06);
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[26], 6);
    fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_UserNo, &ICEsamComm.Ic_Comm_RxBuf[26], 0x06);
    fnCrc_Check(0, (u8 *)&EgMoney.PubPara.MeterCT, sizeof(sDF10) * 2, (u8 *)&EgMoney.PubPara.Crc);
    Std_Memcpy(&ICEsamComm.Ic_Comm_RxBuf[0], &ICEsamComm.Ic_Comm_TxBuf[5], 18);
    fnICEsam_WriteBinFile(ESAM, 0x87, 5, 18);       //更新ESAM
    return (SUCCESS);
}

// 钱包初始化处理
ErrorStatus fnICEsam_MoneyBagInit(void)
{
    ErrorStatus result = SUCCESS;
    u32 ExeCount, BuyMoney;
    Std_Memset((u8 *)&EgMoney.PubData.CurSurplusEg, 0x00, 28);
    Std_Memset((u8 *)&EgMoney.PubPara.nALLBuyMoney, 0x00, 4);

    Std_Memcpy(ICEsamComm.Ic_Comm_RxBuf, &ICEsamReadBuf.CardMoneyBag[0],  8);
    result = fnICEsam_WriteBinWithMac(ESAM + 0x10, 0x01, 0x0c, 4 + 4); //更新钱包金额
    if (result == ERROR)
    {
        return (result);
    }
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[5], 4);
    Std_Memcpy(&BuyMoney, &ICEsamComm.Ic_Comm_TxBuf[5], 4);
    BuyMoney = fnHexToBcd_u32(BuyMoney);
    Std_Memcpy((u8 *)&EgMoney.PubData.CurSurplusEg, &BuyMoney, 4);
    Std_Memcpy((u8 *)&EgMoney.PubData.CurSurplusMoney.Dat2, (u8 *)&EgMoney.PubData.CurSurplusEg, 0x04);
    fnCrc_Check(0, (u8 *)&EgMoney.PubData.CurSurplusEg, 8, (u8 *)&EgMoney.PubDataCrc.CurSurplusEg);
    fnCrc_Check(0, (u8 *)&EgMoney.PubData.CurSurplusMoney, 12, (u8 *)&EgMoney.PubDataCrc.CurSurplusMoney);
    fnCrc_Check(0, (u8 *)&EgMoney.PubData.CurApplyEg, 8, (u8 *)&EgMoney.PubDataCrc.CurApplyEg);
    fnWDT_Restart();
    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_EgMoney, (u8 *)&EgMoney.PubData, sizeof(EgMoney.PubData));

    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_EgMoney + 38, (u8 *)&EgMoney.PubData.CurSurplusMoney.Dat2, 4);

    Std_Memcpy(ICEsamComm.Ic_Comm_RxBuf, &ICEsamReadBuf.CardMoneyBag[0],  1);
    if (result == ERROR)
    {
        return (result);
    }
    result = fnICEsam_WriteBinWithMac(ESAM + 0x10, 0x03, 0x0c, 4 + 4); //更新钱包购电次数
    if (result == ERROR)
    {
        return (result);
    }
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[5], 4);
    Std_Memcpy(&ExeCount, &ICEsamComm.Ic_Comm_TxBuf[5], 4);
    ExeCount = fnHexToBcd_u32(ExeCount);
    Std_Memcpy((u8 *)&EgMoney.PubPara.nALLBuyMoney, &ExeCount, 4);

    return (SUCCESS);
}

//SOC与卡隔离专用芯片进行同步，进行卡复位信息的获取
ErrorStatus fnICEsam_CheckCard(void)
{
    ErrorStatus result;
    u8 tempData, i;
    u32 temp0;
    ISO7816->CTRL1 = 0x7000ea01;
    ISO7816->STA1 = 0x3f;                   //clear status
    ISO7816->BDDIV1 = 0X260000;             // F/D =768 2400
    if (fnCardSendByte(CARD, 0x00) == ERROR)
    {
        return (ERROR);
    }
    ISO7816->BDDIV1 = 0X226600;             // F/D =307 6000
    for (i = 0; i < 20; i++)
    {
        SystemDelayUs(1);
    }
    if (fnCardSendByte(CARD, 0x16) == ERROR)
    {
        return (ERROR);
    }
    tempData = ISO7816->DATA1;
    ISO7816->CTRL1 = 0x7000ea01;
    ISO7816->STA0 = 0x3f;                   //clear status
    result = fnCardGetByte(CARD, &tempData);   //receive procedure byte.
    if ((result != SUCCESS) || (tempData != 0x16))
    {
        return (ERROR);
    }
    if (fnCardGetByte(CARD, &tempData) == ERROR)
    {
        return (ERROR);    //receive procedure byte.
    }
    temp0 = (u32)(614 * 372) / (u32)(tempData << 1);
    temp0 = (temp0 << 8) & 0x002fff00;
    ISO7816->BDDIV1 = (temp0 | 0x00200000);
    for (i = 0; i < 200; i++)
    {
        SystemDelayUs(1);
        SystemDelayUs(1);
    }

    if (fnCardSendByte(CARD, 0x16) == ERROR)
    {
        return (ERROR);
    }
    result = fnCardGetByte(CARD, &tempData);   //receive procedure byte.
    if ((result != SUCCESS) || (tempData != 0x16))
    {
        return (ERROR);
    }
    //  ISO7816->BDDIV1 = ISO7816->BDDIV1 - (5<<8);
    for (i = 0; i < 13; i++)
    {
        result = fnCardGetByte(CARD, &tempData);   //receive TS.
        if (result != SUCCESS)
        {
            return (ERROR);
        }
        ICEsamComm.Ic_Comm_RxBuf[i] = tempData;
    }
    return (SUCCESS);
}

// 非法插卡记录增加一次
void fnICEsam_AddInsertCardIllegal(void)
{
    /*
       sDF10   nEv;
       //次数+1
       //fnFile_Read(Dl645FileId_MiscEv , Dl645FileItemInfoOffAddr_MiscEv_InsertCardIllegal , &nEv , sizeof(sDF10) );
       nEv = fnDFInc_DF10(nEv);
       //fnFile_Write(Dl645FileId_MiscEv , Dl645FileItemInfoOffAddr_MiscEv_InsertCardIllegal , &nEv , sizeof(sDF10) );
       fnDl645B_Inverse( (u8 *)&nEv, 3 );
       Std_Memcpy(&ICEsamComm.Ic_Comm_RxBuf[0] , (u8 *)&nEv , 3);
       fnWDT_Restart();
       fnICEsam_WriteBinFile( ESAM, 0x87, 39, 3 );
       fnWDT_Restart();
       fnICEsam_UpdateRunFile_Clock();
       fnWDT_Restart();*/
}

void fnICEsam_Card_Proc(void)
{
    #if(METERTYPE ==2)
    eICEsam_ErrInfo_TypeDef Ic_Err_Flag;
    u8  DispErrFlag;
    u8  i, j;
    if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON) || (Inactive.PubData.InactiveStamp))
    {
        return;
    }
    if (!I7816ComExt.EFlag)
    {
        return;
    }
    if (Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON)
    {
        return;
    }
    if ((MeasureRms.PubData.U[0] < 0x1750) && (MeasureRms.PubData.U[1] < 0x1750) && (MeasureRms.PubData.U[2] < 0x1750))
    {
        Ic_Err_Flag = IC_PowerDn_ERR;
    }
    else
    {
        LCDBackLightON();
        DispOperParm.BkLightFlag = 0x5a;
        DispOperParm.BkLightStamp = 194;                //启动背光点亮计时
        if (!Secret.RemoteValid)
        #if(SPI_ESAM)
            ENABLE_ESAM();
        CardFoutOpen();
        #else
            CardFoutOpen();
        #endif
        if (fnICEsam_CheckCard() == ERROR)
        {
            for (i = 0; i < 3; i++)
            {
                SystemDelay(10);
                ISO7816->BDDIV1 = 0X260000;             // F/D =768 2400
                fnCardSendByte(CARD, 0x00);             // close clk
                GPIO->PCB &= 0xfffffff7;
                GPIO->PIEB &= 0xfffffff7;
                SystemDelay(8);
                for (j = 0; j < 20; j++)
                {
                    if (GPIO->PB & 0x08)
                    {
                        break;
                    }
                    SystemDelay(1);
                }
                GPIO->PCB |= 0x00000008;
                GPIO->PIEB |= 0x00000008;
                SystemDelay(50);
                fnWDT_Restart();
                if (fnICEsam_CheckCard() == SUCCESS)
                {
                    break;
                }
            }

            if (i >= 3)
            {
                ISO7816->BDDIV1 = 0X260000;             // F/D =768 2400
                fnCardSendByte(CARD, 0x00);             // close clk
                I7816ComExt.EFlag = 0;
                DispOperParm.Stamp = 5;
                DispOperParm.CardDispStamp = 3;
                BSP_Lcd_ClrScr();
                Ic_Err_Flag = IC_IC_RST_ERR;

                DispApi_CardInfo(DispApi_CardReadErr, 0x32);

                BSP_Lcd_Refresh();
                ISO7816->CTRL1 |= 0x80000000;
                Std_Memset(&ICEsamComm.Ic_Comm_RxBuf[9], 0x00, 7);
                ICEsamComm.Ic_Comm_RxBuf[8] = Ic_Err_Flag;
                Std_Memset(&ICEsamComm.Ic_Comm_RxBuf[0], 0xFF, 8);
                fnDl645Event_Operation(EVENT_STYLE_InsertCardErr, EVENT_OPERATION_START, 0, &ICEsamComm.Ic_Comm_RxBuf[0]);
                fnICEsam_AddInsertCardIllegal();
                Bkgrd.PubData.InsertCardFlag = 0x02;
                Bkgrd.PubData.BeepFlag = 0x0b;
                //fnINTTC1_Star();
                Rn8xxx_TC_TimeStar(Timer1, ENABLE);
                return;
            }
        }
        Std_Memcpy(&ICEsamComm.CardRst8B[0], &ICEsamComm.Ic_Comm_RxBuf[5], 8);

        Ic_Err_Flag = fnICEsam_Card_Esam_Proc();        //卡片处理
    }
    ISO7816->BDDIV1 = 0X260000;             // F/D =768 2400
    if (Ic_Err_Flag != CARD_PROC_OK)
    {
        Bkgrd.PubData.InsertCardFlag = 0x02;
        if (Ic_Err_Flag == IC_Auth_Err || Ic_Err_Flag == IC_IC_RST_ERR || Ic_Err_Flag == IC_MeterNo_Err)
        {
            fnICEsam_AddInsertCardIllegal();
        }
        DispOperParm.Stamp = 5;
        DispOperParm.CardDispStamp = 3;
        BSP_Lcd_ClrScr();
        if (Ic_Err_Flag <= IC_ESAM_RST_ERR)
        {
            DispErrFlag = 0x31;
        }
        else if (Ic_Err_Flag <= IC_MAC_Err)
        {
            DispErrFlag = 0x32;
        }
        else if (Ic_Err_Flag <= IC_CardNo_Err)
        {
            DispErrFlag = 0x33;
        }
        else if (Ic_Err_Flag <= IC_ReturnFile_Err)
        {
            DispErrFlag = 0x34;
        }
        else if (Ic_Err_Flag <= IC_Pull_Err)
        {
            DispErrFlag = 0x35;
        }
        else
        {
            DispErrFlag = 0x36;
        }
        DispApi_CardInfo(DispApi_CardReadErr, DispErrFlag);

        //if(Ic_Err_Flag == IC_Regrate_Err)  BSP_Lcd_SetSegment(SEG_TunJi,1);
        BSP_Lcd_Refresh();
        //异常插卡记录
        if (((ICEsamComm.Ic_Comm_RxBuf[0] & 0xf0) == 0x60) || ((ICEsamComm.Ic_Comm_RxBuf[0] & 0xf0) == 0x90))
        {
            ICEsamComm.Ic_Comm_RxBuf[15] = ICEsamComm.Ic_Comm_RxBuf[0];
            ICEsamComm.Ic_Comm_RxBuf[14] = ICEsamComm.Ic_Comm_RxBuf[1];
        }
        else
        {
            Std_Memset(&ICEsamComm.Ic_Comm_RxBuf[14], 0x00, 2);
        }
        Std_Memcpy(&ICEsamComm.Ic_Comm_RxBuf[9], &ICEsamComm.Ic_Comm_TxBuf[0], 5);
        fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[9], 5);
        Std_Memcpy(&ICEsamComm.Ic_Comm_RxBuf[0], &ICEsamComm.CardRst8B[0], 8);
        fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[0], 8);
        ICEsamComm.Ic_Comm_RxBuf[8] = Ic_Err_Flag;
        fnDl645Event_Operation(EVENT_STYLE_InsertCardErr, EVENT_OPERATION_START, 0, &ICEsamComm.Ic_Comm_RxBuf[0]);
        Bkgrd.PubData.BeepFlag = 0x0b;
        //fnINTTC1_Star();
        Rn8xxx_TC_TimeStar(Timer1, ENABLE);
    }
    else
    {
        //BSP_Lcd_SetSegment(SEG_Zhong,0);
        //BSP_Lcd_SetSegment(SEG_DuKa,1);           //显示“读卡中”
        BSP_Lcd_SetSegment(SEG_Success, 1);
        DispOperParm.Stamp = 3;
        DispOperParm.CardDispStamp = 3;
        Bkgrd.PubData.InsertCardFlag = 0x01;
        Bkgrd.PubData.BeepFlag = 0x0a;
        //fnINTTC1_Star();
        Rn8xxx_TC_TimeStar(Timer1, ENABLE);
    }
    BSP_Lcd_Refresh();
    //卡操作完成，关闭CLK，判断卡是否拔出
    ISO7816->BDDIV1 = 0x260000;             // F/D =768 2400
    fnCardSendByte(CARD, 0x00);             // close clk
    I7816ComExt.EFlag = 0;
    ISO7816->CTRL1 |= 0x80000000;
    if (!Secret.RemoteValid)
    #if(SPI_ESAM)
        DISABLE_ESAM();
    CardFoutClose();
    #else
        CardFoutClose();            //关闭CLK
    #endif
    #endif
}
