
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
// ������:  void ResetClear(u8 CH)
// ���أ�   ��Ƭ��ESAM��RST������1MS
// ������   ��ESAM��Ƭ�����临λ
//*********************************************************************************

void fnResetClear(u8 CH)
{
    /*
     if (CH == CARD)                               // 1--��Ƭ����  0--ESAM����
       ;
       //PinWrite_CardRst(0);
     else PinWrite_EsamRst(0); */
}

//*********************************************************************************
// ������:  void ResetSet(u8 CH)
// ���أ�   ��Ƭ��ESAM��RST�Żָ�
// ������   ��ESAM��Ƭ�����临λ��ָ�
//*********************************************************************************

void fnResetSet(u8 CH)
{
    /*
    if (CH == CARD)                               // 1--��Ƭ����  0--ESAM����
      ;
      //PinWrite_CardRst(1);
    else PinWrite_EsamRst(1);*/
}

//*********************************************************************************
// �������� ErrorStatus fnICEsam_CardTxRxFrame( u8 CH, u8 Lc, u8 Le )
// ���룺   CH ����ESAMѡ�� Lc �������ݳ������ȥ5�ֽ����� Le���ճ���
// ���أ�   SUCCESSΪ��ȷ��ERRORΪ����ȷ
// ������   �����ͼ���������
//*********************************************************************************
ErrorStatus fnICEsam_CardTxRxFrame(u8 CH, u8 Lc, u8 Le)
{
    #if(0)
    u8 k, Temp_Data, Temp_SW1, Temp_SW2, Proc_Byte;
    ErrorStatus result;
    Std_Memset(ICEsamComm.Ic_Comm_RxBuf, 0x00, MAX_ICEsamCom_SIZE);
    for (k = 0; k < 5; k++) //send command header (5bytes)
    {
        result = fnCardSendByte(CH, ICEsamComm.Ic_Comm_TxBuf[k]);       //;ȡ����������
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
                    result = fnCardSendByte(CH, ICEsamComm.Ic_Comm_TxBuf[k++]);    //;ȡ����������
                    if (result == ERROR)
                    {
                        return ERROR;    //send failure.
                    }
                }
            }
            else
            {
                //;�����ֽ���֮ǰ�ѽ��գ�ֻ����2��״̬�ֽڼ��ɡ�
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
// �������� ErrorStatus fnICEsam_CardColdReset(u8 CH)
// ���룺   CH ����ESAMѡ��
// ���أ�   SUCCESSΪ��ȷ��ERRORΪ����ȷ
// ������   //���㼤��&�临λ
//��⵽�������, RST�õ͵�ƽ, VCC�ϵ�, ��ʱһ��ʱ��, IO����Ϊ����̬, CLK���ʱ���ź�(T0ʱ��)
//��T0��40000~45000��CLK��, ��RST��Ϊ�ߵ�ƽ(T1ʱ��), ��T1���400~40000��CLK��, ��λӦ��Ӧ�ÿ�ʼ,
//��IC���ĸ�λӦ��û���ڴ�ʱ����ڿ�ʼ, �ն˽������ͷ�ʱ��.���յ���λӦ��, ��������Э��淶, ����Ҫ�ȸ�λ
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

//��ֹESAM����
void fnICEsam_CloseEsam(void)
{
    fnResetClear(ESAM);
    #if(SPI_ESAM)
    DISABLE_ESAM();
    #else
    CardFoutClose();            //�ر�CLK
    #endif
    EsamPowerOff();
}

//ESAM��λ
ErrorStatus fnICEsam_EsamReset(void)
{
    unsigned char i;

    for (i = 0; i < 3; i++)
    {
        if (fnICEsam_CardColdReset(ESAM) == ERROR)
        {
            fnICEsam_CloseEsam();       //�ͷ�ESAM
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

//�жϿ�Ƭ���ݸ�ʽ���ж�����Ч��ͼ�ͷβ�Ƿ���ȷ
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
        return ERROR;    //֡��ʽ����: 68H/CS/16H
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

//ѡ���ļ�
ErrorStatus fnICEsam_SelectFile(u8 CH, u8 F1, u8 F2)
{
    ErrorStatus err;
    fnICEsam_RxTxCommhead(0, 0xa4, 0, 0, 2);
    ICEsamComm.Ic_Comm_TxBuf[5] = F1;   //DATA0
    ICEsamComm.Ic_Comm_TxBuf[6] = F2;   //DATA1

    err = fnICEsam_CardTxRxFrame(CH, 0x02, 0x00);

    return (err);
}

//���������ļ�
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

//д�������ļ�
ErrorStatus fnICEsam_WriteBinFile(u8 CH, u8 P1, u8 P2, u8 Len)
{
    ErrorStatus err;
    fnICEsam_RxTxCommhead(0, 0xD6, P1, P2, Len);

    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], ICEsamComm.Ic_Comm_RxBuf, Len);

    err = fnICEsam_CardTxRxFrame(CH, Len, 0x00);   //CARD Com

    return (err);
}

//����¼�ļ�
ErrorStatus fnICEsam_ReadRecFile(u8 CH, u8 P1, u8 P2, u8 Len)
{
    ErrorStatus err;

    fnICEsam_RxTxCommhead(0, 0xb2, P1, P2, Len);

    err = fnICEsam_CardTxRxFrame(CH, 0x00, Len);

    return (err);
}

//ȡ��Ӧ����
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

//ȡ�����
ErrorStatus fnICEsam_ReadRandom(u8 CH, u8 Len)
{
    fnICEsam_RxTxCommhead(0, 0x84, 0, 0, Len);
    if (SUCCESS == fnICEsam_CardTxRxFrame(CH, 0x00, Len))
    {
        if (CH == ESAM)
        {
            Std_Memcpy(ICEsamComm.EsamRand, ICEsamComm.Ic_Comm_RxBuf, Len);    //ȡESAM�����
        }
        else
        {
            Std_Memcpy(ICEsamComm.CardRand, ICEsamComm.Ic_Comm_RxBuf, Len);    //ȡ��Ƭ�����
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

//���ܣ��ڲ����ⲿ��֤����
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

//ϵͳ�ڲ���֤
ErrorStatus fnICEsam_Inter_Auth(u8 Psw)
{
    u8 i, K1[8], K2[8];

    fnICEsam_ReadRandom(ESAM, 8);           //��ESAMȡ8�ֽ������

    fnICEsam_Auth_In_Out(0xfa, ESAM, 0x01, ICEsamComm.CardRst8B); //ESAM��ɢ�ڲ���֤��Կ

    fnICEsam_Auth_In_Out(0xfa, ESAM, 0x00, ICEsamComm.EsamRand);  //ESAM���������

    fnICEsam_Read_Kx(ESAM, 0x08);           //ȡESAM���ܽ��K1

    Std_Memcpy(K1, ICEsamComm.Ic_Comm_RxBuf, 8);

    fnICEsam_Auth_In_Out(0x88, CARD, Psw, ICEsamComm.EsamRand); //��Ƭ���������

    fnICEsam_Read_Kx(CARD, 0x08);           //ȡ��Ƭ���ܽ��K2

    Std_Memcpy(K2, ICEsamComm.Ic_Comm_RxBuf, 8);

    for (i = 0; i < 8; i++)
    {
        if (K1[i] != K2[i])
        {
            return ERROR;    //�ڲ���֤ʧ��
        }
    }

    return SUCCESS;
}

//��Ƭ�ⲿ��֤
ErrorStatus fnICEsam_Card_Ext_Auth(u8 P2)
{
    ErrorStatus err;

    fnICEsam_ReadRandom(CARD, 8);           //�ӿ�Ƭȡ8�ֽ������

    fnICEsam_Auth_In_Out(0xfa, ESAM, 0x02, ICEsamComm.CardRst8B);  //ESAM��ɢ�ⲿ��֤��Կ

    err = fnICEsam_Auth_In_Out(0xfa, ESAM, 0x00, ICEsamComm.CardRand); //ESAM���������
    if (err == ERROR)
    {
        return ERROR;
    }

    fnICEsam_Read_Kx(ESAM, 0x08);           //ȡ���ܽ��

    err = fnICEsam_Auth_In_Out(0x82, CARD, P2, ICEsamComm.Ic_Comm_RxBuf); //��Ƭ���ⲿ��֤
    if (err == ERROR)
    {
        return ERROR;
    }

    return SUCCESS;
}

// ������ָ֤��
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

// Զ�������ָ֤��
ErrorStatus fnICEsam_Authorization(u8 *Buf)
{
    u8 i;
    ErrorStatus err;
    //���ܱ��ESAM����������⣺
    //a����Կ��ɢ���80fa000108+8�ֽڷ�ɢ���ӣ�
    //;Esam encryp random data.
    err = fnICEsam_Auth_In_Out(0xfa, ESAM, 0x03, Buf + 16);
    if (!((err == SUCCESS) && (ICEsamComm.Ic_Comm_RxPtr == 0x02) && (ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00)))
    {
        return ERROR;
    }
    //b��������������80fa000008+�������
    err = fnICEsam_Auth_In_Out(0xfa, ESAM, 0x00, Buf + 8);
    if (!((err == SUCCESS) && (ICEsamComm.Ic_Comm_RxPtr == 0x02) && (ICEsamComm.Ic_Comm_RxBuf[0] == 0x61) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x08)))
    {
        return ERROR;
    }
    //c��ȡ�������00c0000008��
    //�Ƚ�����1������2, ���߲�����򱨾�, ���������������
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
    //ȡ�����2��0084000004
    //;Read random in ESAM
    err = fnICEsam_ReadRandom(ESAM, 4);
    if (!((err == SUCCESS) && (ICEsamComm.Ic_Comm_RxPtr == 0x06) && (ICEsamComm.Ic_Comm_RxBuf[4] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[5] == 0x00)))
    {
        return ERROR;
    }
    return  SUCCESS;
}

//��MAC��ȡ�������ļ�,Զ�̷ѿ�ʹ��
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

    err = fnICEsam_Read_Kx(ESAM, Len + 4); //����Ԥ�õ���+MAC
    return (err);
}

//��MAC��ȡ������Ǯ���ļ�,Զ�̷ѿ�ʹ��
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

    err = fnICEsam_Read_Kx(ESAM, Len + 4); //����Ԥ�õ���+MAC
    return (err);
}

//=====��MAC��ȡ�������ļ�
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

        Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[16], ICEsamComm.Ic_Comm_RxBuf, 6);//���
    }
    else if (CH == 0x10)    //ESAM with ID
    {
        Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[14], &ICEsamComm.CardRst8B[0], 8);//�����
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

    err = fnICEsam_Read_Kx(CH, Len);   //����data+MAC

    return (err);
}

//======��MAC���¶������ļ�
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
        ICEsamComm.Ic_Comm_TxBuf[0] = 0;    //CLA ����MAC
    }
    CH &= 0x01;

    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[k], ICEsamComm.Ic_Comm_RxBuf, Len);

    err = fnICEsam_CardTxRxFrame(CH, Len, 0x00);   //CARD Com

    return (err);
}

//======��MAC������
ErrorStatus fnICEsam_IncreseWithMac(u8 CH, u8 P1, u8 P2, u8 Len)
{
    ErrorStatus err;
    fnICEsam_RxTxCommhead(0x84, 0x32, P1, P2, Len);

    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], ICEsamComm.Ic_Comm_RxBuf, Len);

    err = fnICEsam_CardTxRxFrame(CH, Len, 0x00);   //CARD Com

    return (err);
}

//======�˷Ѵ���
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

//�ۿ�����
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

// 99�����룬����+MACдESAM���ļ���Ϣ
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

// 99�����룬����+MACдESAM�з��ʵ���ļ��ļ���Ϣ
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

// 98�����룬���������
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

    //��������Կ��Ϣָ�04D6860008+��Կ��Ϣ+MAC
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

//������Կ
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

    //  if( progenable == 0 )   //���ʹ�ܱ�־ ʧЧ
    //  {
    //      first_prog_flag = 0;//���״α�̱�־
    //  }

    err = fnICEsam_EsamReset();

    return (err);
}

// ����ESAM��������Ϣ�ļ��еķ�дʱ��
ErrorStatus fnICEsam_UpdateRunFile_Clock(void)
{
    ErrorStatus err;
    u8  ChkSum, i;

    ICEsamComm.Ic_Comm_RxBuf[0] = SysClock.Year;
    ICEsamComm.Ic_Comm_RxBuf[1] = (SysClock.Month & 0x1f);
    ICEsamComm.Ic_Comm_RxBuf[2] = SysClock.Day;
    ICEsamComm.Ic_Comm_RxBuf[3] = SysClock.Hour;
    ICEsamComm.Ic_Comm_RxBuf[4] = SysClock.Minute;

    err = fnICEsam_WriteBinFile(ESAM, 0x87, 42, 5);                 //���·�дʱ��ͷǷ�����

    fnWDT_Restart();
    ICEsamComm.Ic_Comm_RxBuf[0] = 0x68;
    ICEsamComm.Ic_Comm_RxBuf[1] = 0x11;
    ICEsamComm.Ic_Comm_RxBuf[2] = 0x00;
    ICEsamComm.Ic_Comm_RxBuf[3] = 0x2b;
    fnICEsam_WriteBinFile(ESAM, 0x87, 0, 4);
    fnWDT_Restart();
    //����CS
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

//��ȡESAM�����ļ�
ErrorStatus fnICEsam_ReadFlLadderFile(u8 Flag)
{
    /*
       ErrorStatus err;
    //  u8 CheckSum;
    //  u16 i;
       //============ ���·����ļ�03================
       if((Flag & 0x0f)==0)  return ( SUCCESS );   //�����з����ļ��ĸ���
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

       //============ ���·����ļ�04================
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

// Ǯ����ʼ������
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
    // ��ȡEEPROM�е�1��2�׷���

    //  {
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15), &BufTemp[4], sizeof(sDF13)*MAX_FL);
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15) + (sizeof(sDF13) * MAX_FL), &BufTemp[4 + sizeof(sDF13) * MAX_FL], sizeof(sDF13)*MAX_FL);
    //  }

    Std_Memcpy(&BufTemp[0], &ICEsamComm.CardRst8B[4], 4);
}

void fnICEsam_ReadEpLadderData(void)
{
    // ��ȡEEPROM�е�1��2�׽��ݵ��
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

//����ESAM�����ļ�
ErrorStatus fnICEsam_WriteFlLadderFile(u8 Flag, u8 CardType)
{
    #if(0)
    ErrorStatus err;
    u16 i;
    fnWDT_Restart();
    //============ ���·����ļ�03================
    if ((Flag & 0x0f) == 0)
    {
        return (SUCCESS);    //�����з����ļ��ĸ���
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
            //����EE�е�1�׷����ļ�
            for (i = 0; i < MAX_FL; i++)
            {
                fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[9 + 4 * i], 4);
            }
            //if(Bkgrd.PubData.MtSta.MtSta3.StaBit.CurRatePrice == 1 )      // ��ǰ���еڶ��׷���
            //{
            //  fnFile_Write(FileId_RatePara , FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15) + (sizeof(sDF13) * MAX_FL) , &ICEsamComm.Ic_Comm_TxBuf[9] , sizeof(sDF13)*MAX_FL);
            //}
            //else              // ��ǰ���е�һ�׷���
            //{
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15), &ICEsamComm.Ic_Comm_TxBuf[9], sizeof(sDF13)*MAX_FL);
            //}
            fnWDT_Restart();
            if (CardType != PresetCard)
            {
                fnDl645Event_Operation(EVENT_STYLE_PrgRatePrice, EVENT_OPERATION_START, &BufTemp[0], &BufTemp[4]);    // д���ʱ����¼�
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
            //����EE�е�1�׽��ݵ���ļ�
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
                fnDl645Event_Operation(EVENT_STYLE_PrgLadderPrice, EVENT_OPERATION_START, &BufTemp[36], &BufTemp[36 + 4]);   // д���ݱ����¼�
            }
        }
    }

    //============ ���·����ļ�04================
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
            //if(Bkgrd.PubData.MtSta.MtSta3.StaBit.CurRatePrice == 1 )      // ��ǰ���еڶ��׷���
            //{
            //  fnFile_Write(Dl645FileId_RatePara , Dl645FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15) , &ICEsamComm.Ic_Comm_TxBuf[9] , sizeof(sDF13)*MAX_FL );
            //}
            //else              // ��ǰ���е�һ�׷���
            //{
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15) + (sizeof(sDF13) * MAX_FL), &ICEsamComm.Ic_Comm_TxBuf[9], sizeof(sDF13)*MAX_FL);
            //}
            fnWDT_Restart();
            if (CardType != PresetCard)
            {
                fnDl645Event_Operation(EVENT_STYLE_PrgRatePrice, EVENT_OPERATION_START, &BufTemp[0], &BufTemp[4]);    // д���ʱ����¼�
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

            //����EE�е�1�׽��ݵ���ļ�
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
            //����EE��2�׽��ݵ���л�ʱ��
            fnWDT_Restart();
            fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[5], 5);
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 0, &ICEsamComm.Ic_Comm_TxBuf[5], 5);
            fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Misc + 15, &i, 1);
            i &= 0x7f;
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Misc + 15, &i, 1);
            fnWDT_Restart();
            if (CardType != PresetCard)
            {
                fnDl645Event_Operation(EVENT_STYLE_PrgLadderPrice, EVENT_OPERATION_START, &BufTemp[36], &BufTemp[36 + 4]);    // д���ݱ����¼�
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
            //����EE�е�2�׷����ļ�
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

    Std_Memcpy((u8 *)&tempData, &EgMoney.PubData.CurSurplusMoney.Dat2, 4);              //ʣ����
    tempData.Dat = fnBcdToHex_u32(tempData.Dat);
    Std_Memcpy((u8 *)&ICEsamComm.Ic_Comm_RxBuf, (u8 *)&tempData, 4);
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[0], 4);

    Std_Memcpy((u8 *)&tempData, (u8 *)&EgMoney.PubPara.nALLBuyMoney, 4);        //�������
    tempData.Dat = fnBcdToHex_u32(tempData.Dat);
    Std_Memcpy(&ICEsamComm.Ic_Comm_RxBuf[4], (u8 *)&tempData, 4);
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[4], 4);

    Std_Memcpy((u8 *)&tempData, &EgMoney.PubData.CurOverdraftMoney.Dat2, 4);            //͸֧���
    //tempData.Dat = fnBcdToHex_u32(tempData.Dat);
    Std_Memcpy(&ICEsamComm.Ic_Comm_RxBuf[8], (u8 *)&tempData, 4);
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[8], 4);

    Std_Memset(&ICEsamComm.Ic_Comm_RxBuf[12], 0x00, 4);

    // ͬ������EEPROM�зǷ��忨����
    //fnFile_Read(Dl645FileId_MiscEv , Dl645FileItemInfoOffAddr_MiscEv_InsertCardIllegal , &ICEsamComm.Ic_Comm_RxBuf[16] , sizeof(sDF10) );
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[16], sizeof(sDF10));
    err = fnICEsam_WriteBinFile(ESAM, 0x87, 23, 19);        //����ESAM

    fnICEsam_UpdateRunFile_Clock();                 //���������ļ�ʱ��
    return (err);
}

ErrorStatus fnICEsam_UpdateRunFile(void)
{
    ErrorStatus err;
    err = fnICEsam_ReadBinFile(ESAM, 0x82, 24, 18);
    if (err == ERROR)
    {
        return (err);    //��ָ���ļ�����
    }
    err = fnICEsam_WriteBinFile(ESAM, 0x87, 5, 18);         //����ESAM
    if (err == ERROR)
    {
        return (err);
    }
    err = fnICEsam_UpdateRunFile_Money();                   //���������ļ�ʱ��
    return (err);
}

// Ǯ���ļ�����
ErrorStatus fnICEsam_MoneyProc(void)
{
    u8 i;
    ErrorStatus err;
    sFsEgSh_TypeDef tempCurMoney;
    sFsEgSh_TypeDef tempEsamMoney;
    Std_Memcpy((u8 *)&tempCurMoney, (u8 *)&EgMoney.PubData.CurSurplusMoney.Dat2, 0x04);
    tempCurMoney.Dat = fnBcdToHex_u32(tempCurMoney.Dat);

    err = fnICEsam_ReadRecFile(ESAM, 0x01, 0x0c, 0x04); //��Ǯ��ʣ����
    if (err == ERROR)
    {
        return (ERROR);
    }
    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[0], 4);
    Std_Memcpy((u8 *)&tempEsamMoney, (u8 *)&ICEsamComm.Ic_Comm_RxBuf[0], 4); //ESAMǮ�����

    if (tempEsamMoney.Dat > tempCurMoney.Dat)
    {
        tempEsamMoney.Dat -= tempCurMoney.Dat;      //Ǯ�� - ʣ��

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

    fnICEsam_UpdateRunFile_Money(); //���������ļ����

    return (err);
}

// �жϹ������Ƿ񳬹��ڻ����
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
        return (SUCCESS);    // ������С��͸֧���
    }

    fnBcdSub_Bytes((u8 *)&BuyMoney, (u8 *)&EgMoney.PubData.CurOverdraftMoney.Dat2, 4);      //������ - ͸֧���
    fnBcdAdd_Bytes((u8 *)&BuyMoney, (u8 *)&EgMoney.PubData.CurSurplusMoney.Dat2, 4);      //������ + ʣ����
    if (fnDFCompData((u8 *)&BuyMoney, (u8 *)&EgMoney.PubData.CurSurplusMoney.Dat2, 4) < 0)
    {
        return (ERROR);    // ���������
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

// Զ�̳�ֵ����,buf[0]-buf[3] ������,buf[4]-buf[7] �������,buf[8]-buf[11] �������
// CH ==0 Զ�̳�ֵ  CH == 1 ���ӵ�ѿ���ֵ   CH == 2 �û�����ֵ
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
    err = fnICEsam_IncreseWithMac(ESAM, 0x01, 0x0c, 8 + 4);     // ��ֵ
    if (err == ERROR)
    {
        return (err);
    }

    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[9], 4);
    Std_Memcpy(&nBuyMoney, &ICEsamComm.Ic_Comm_TxBuf[9], 4);
    EgMoney.PubPara.nALLBuyMoney = fnHexToBcd_u32(nBuyMoney);

    Std_Memcpy(&Buf[8], (u8 *)&EgMoney.PubData.CurSurplusMoney.Dat2, 0x04);

    if (fnDFCompData((u8 *)&MoneyTemp, (u8 *)&EgMoney.PubData.CurOverdraftMoney, 0x06) < 0)    // ��ֵ���С��͸֧���
    {
        fnBcdSub_Bytes((u8 *)&EgMoney.PubData.CurOverdraftMoney, (u8 *)&MoneyTemp, 0x06);
        Std_Memset((u8 *)&EgMoney.PubData.CurSurplusMoney, 0x00, 0x06);
        Std_Memcpy(&TempData, Buf, 4);                      // �ۼ���͸֧���
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
        fnICEsam_MoneyProc();    // ʣ���������
    }

    // ����RAM��EEPROM
    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_EgMoney + 8, (u8 *)&EgMoney.PubData.CurSurplusMoney, 12);
    fnCrc_Check(0, (u8 *)&EgMoney.PubData.CurSurplusMoney, 12, (u8 *)&EgMoney.PubDataCrc.CurSurplusMoney);
    if (CH == 0)
    {
        fnDl645B_Inverse(&Buf[4], 4);
    }
    Std_Memcpy(&TempData, &Buf[4], 4);
    TempData = fnHexToBcd_u32(TempData);            // �������
    Std_Memcpy(&Buf[4], &TempData, 4);
    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_EgMoney + 34, (u8 *)&TempData, 0x04);
    if (CH == 0)
    {
        fnDl645B_Inverse(&Buf[0], 4);
    }
    Std_Memcpy(&TempData, &Buf[0], 4);
    TempData = fnHexToBcd_u32(TempData);            // ������
    Std_Memcpy(&Buf[0], &TempData, 4);
    fnDl645Event_Operation(EVENT_STYLE_BUYMONEY, EVENT_OPERATION_START, 0, &Buf[0]);      // д�����¼
    // ��բ�������ж�
    if (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus && (Bkgrd.PubData.CheckMoneyFlag == 0x5a))
    {
        fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_ChargMoneyPara + sizeof(sDF11) * 8, &TempData, 4);
        if (fnDFCompData((u8 *)&EgMoney.PubData.CurSurplusMoney.Dat2, (u8 *)&TempData, 0x04) >= 0)
        {
            fnFile_Write(FileId_BackUpCurMoney, FileItemInfoLen_BackUpCurMoney_CurSurplusMoney, &OpCodeTemp[0], 4);
            Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
            Bkgrd.PubData.MoneySta.Overdraft = 0;
            OpCodeTemp[0] = 0x9b;
            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &OpCodeTemp[0], 1);   //״̬����
            Bkgrd.PubData.CheckMoneyFlag = 0;
            fnFile_Write(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_CheckMoneyFlag, &Bkgrd.PubData.CheckMoneyFlag, 1);
        }
    }
    return SUCCESS;
}

//��ESAM�еĲ������µ�EEPROM��
ErrorStatus fnICEsam_EsamParaVarToEE(void)
{
    ErrorStatus Result;
    Result = fnICEsam_ReadBinFile(ESAM, 0x82, 10, 32);
    if (Result == ERROR)
    {
        return (ERROR);    //��ָ���ļ�����
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
    fnICEsam_WriteBinFile(ESAM, 0x87, 5, 18);       //����ESAM
    return (SUCCESS);
}

// Ǯ����ʼ������
ErrorStatus fnICEsam_MoneyBagInit(void)
{
    ErrorStatus result = SUCCESS;
    u32 ExeCount, BuyMoney;
    Std_Memset((u8 *)&EgMoney.PubData.CurSurplusEg, 0x00, 28);
    Std_Memset((u8 *)&EgMoney.PubPara.nALLBuyMoney, 0x00, 4);

    Std_Memcpy(ICEsamComm.Ic_Comm_RxBuf, &ICEsamReadBuf.CardMoneyBag[0],  8);
    result = fnICEsam_WriteBinWithMac(ESAM + 0x10, 0x01, 0x0c, 4 + 4); //����Ǯ�����
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
    result = fnICEsam_WriteBinWithMac(ESAM + 0x10, 0x03, 0x0c, 4 + 4); //����Ǯ���������
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

//SOC�뿨����ר��оƬ����ͬ�������п���λ��Ϣ�Ļ�ȡ
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

// �Ƿ��忨��¼����һ��
void fnICEsam_AddInsertCardIllegal(void)
{
    /*
       sDF10   nEv;
       //����+1
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
        DispOperParm.BkLightStamp = 194;                //�������������ʱ
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

        Ic_Err_Flag = fnICEsam_Card_Esam_Proc();        //��Ƭ����
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
        //�쳣�忨��¼
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
        //BSP_Lcd_SetSegment(SEG_DuKa,1);           //��ʾ�������С�
        BSP_Lcd_SetSegment(SEG_Success, 1);
        DispOperParm.Stamp = 3;
        DispOperParm.CardDispStamp = 3;
        Bkgrd.PubData.InsertCardFlag = 0x01;
        Bkgrd.PubData.BeepFlag = 0x0a;
        //fnINTTC1_Star();
        Rn8xxx_TC_TimeStar(Timer1, ENABLE);
    }
    BSP_Lcd_Refresh();
    //��������ɣ��ر�CLK���жϿ��Ƿ�γ�
    ISO7816->BDDIV1 = 0x260000;             // F/D =768 2400
    fnCardSendByte(CARD, 0x00);             // close clk
    I7816ComExt.EFlag = 0;
    ISO7816->CTRL1 |= 0x80000000;
    if (!Secret.RemoteValid)
    #if(SPI_ESAM)
        DISABLE_ESAM();
    CardFoutClose();
    #else
        CardFoutClose();            //�ر�CLK
    #endif
    #endif
}
