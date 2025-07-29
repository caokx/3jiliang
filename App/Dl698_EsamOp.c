
#define  _DL698_EsamOp_GLOBALS
#include <App.h>

//******************************************************************************************************
// �������� void fnEsamOp_EsamInit(void)
// ���룺   ESAM��ʼ��
// ���أ�   NONE
// ������   NONE
//******************************************************************************************************
void fnEsamOp_EsamInit(void)
{
    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }
    //fnSPI_Mast_Init(SPI1_ID , 0x03, 2000);//  //2M  SPISpeed
    fnWDT_Restart();
    EsamPowerOn();   //ESAM ��Դ�򿪺���ȴ�50ms������ȥ����ESAM
    BSP_EsamSpi_Init();
    fnDelayMs(40); //��ʱ80ms
}

//******************************************************************************************************
// �������� void fnEsamOp_RxTxCommhead( u8 cal, u8 ins, u8 P1, u8 P2, u8 len1, u8 len2)
// ���룺   SPI ESAM����ͷ����
// ���أ�   NONE
// ������   ESAM����ͷ����
//******************************************************************************************************
void fnEsamOp_RxTxCommhead(u8 cal, u8 ins, u8 P1, u8 P2, u8 len1, u8 len2)
{
    ICEsamComm.Ic_Comm_TxBuf[0] = cal;
    ICEsamComm.Ic_Comm_TxBuf[1] = ins;
    ICEsamComm.Ic_Comm_TxBuf[2] = P1;
    ICEsamComm.Ic_Comm_TxBuf[3] = P2;
    ICEsamComm.Ic_Comm_TxBuf[4] = len1;
    ICEsamComm.Ic_Comm_TxBuf[5] = len2;
}

//******************************************************************************************************
// �������� ErrorStatus fnEsamOp_CardTxRxFrame( u8 CH, u8 Lc, u8 Le , u8 *RxBuf , u8 *TxBuf)
// ���룺   CH ����ESAMѡ�� Lc �������ݳ������ȥ5��6�ֽ�����
//          RxBuf: ��������BUFָ��  TxBuf����������BUFָ��
// ���أ�   SUCCESSΪ��ȷ��ERRORΪ����ȷ
// ������   �����ͼ���������
//******************************************************************************************************
#if 1
u8 esamErrCnt = 0;
ErrorStatus fnEsamOp_CardTxRxFrame(u8 CH, u16 Lc, u8 *RxBuf, u8 *TxBuf)
{
    u8 Temp_Data, Proc_Byte;
    u8 Rept1, Rept2;
    u16 k;
    u8 ErrFlg;

    if (BSP_EASM_GetPower() == false) //ESAM��Դ�ر�ʱ���ȴ�
    {
        fnWDT_Restart();
        fnEsamOp_EsamInit();
    }
    Std_Memset(ICEsamComm.Ic_Comm_RxBuf, 0x00, MAX_ICEsamCom_SIZE);

    // SPI �ӿ�ESAMͨѶ
    ErrFlg = 1;
    for (Rept1 = 0; Rept1 < 3; Rept1++)
    {
        u8 chksum;
        u16 RxLen;

        fnWDT_Restart();

        ENABLE_ESAM();
        SystemDelayUs(60);
        fnCardSendByte(CH, 0x55);   //;ȡ����������
        chksum = 0;
        for (k = 0; k < 6; k++) //send command header (5bytes)
        {
            fnCardSendByte(CH, ICEsamComm.Ic_Comm_TxBuf[k]);
            chksum ^= ICEsamComm.Ic_Comm_TxBuf[k];
        }
        for (; k < (Lc + 6); k++)   //send Data
        {
            fnCardSendByte(CH, TxBuf[k - 6]);
            chksum ^= TxBuf[k - 6];
        }
        chksum = ~chksum;
        fnCardSendByte(CH, chksum);     //;����У�������
        SystemDelayUs(8);
        DISABLE_ESAM();
        SystemDelayUs(100);

        for (Rept2 = 0; Rept2 < 3; Rept2++)
        {
            ENABLE_ESAM();
            SystemDelayUs(60);
            for (k = 0; k < 300; k++)
            {
                fnCardGetByte(CH, &Proc_Byte);   //receive procedure byte.
                if (Proc_Byte == 0x55)
                {
                    break;
                }
                SystemDelayUs(200);
            }
            if (k >= 300)
            {
                DISABLE_ESAM();
                continue;
            }
            // ��������4�ֽ�����
            chksum = 0;
            for (ICEsamComm.Ic_Comm_RxPtr = 0x00; ICEsamComm.Ic_Comm_RxPtr < 4; ICEsamComm.Ic_Comm_RxPtr++)
            {
                fnCardGetByte(CH, &Temp_Data);
                chksum ^= Temp_Data;
                ICEsamComm.Ic_Comm_RxBuf[ICEsamComm.Ic_Comm_RxPtr] = Temp_Data;
            }
            RxLen = ((ICEsamComm.Ic_Comm_RxBuf[2] << 8) + ICEsamComm.Ic_Comm_RxBuf[3]);
            for (; ICEsamComm.Ic_Comm_RxPtr < (RxLen + 4); ICEsamComm.Ic_Comm_RxPtr++)
            {
                fnCardGetByte(CH, &Temp_Data);
                RxBuf[ICEsamComm.Ic_Comm_RxPtr - 4] = Temp_Data;
                chksum ^= Temp_Data;
            }

            fnCardGetByte(CH, &Temp_Data);
            chksum = ~chksum;
            if (chksum != Temp_Data)
            {
                DISABLE_ESAM();
                SystemDelayUs(20);
            }
            else
            {
                ErrFlg = 0;
                esamErrCnt = 0;
                Bkgrd.PubData.MtSysSta.SysStaBit.EsamErr = 0;
                break;
            }
        }

        if (ErrFlg == 0)
        {
            if ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x6a) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x90))
            {
                DISABLE_ESAM();
                SystemDelayUs(20);
            }
            else
            {
                DISABLE_ESAM();
                return SUCCESS;
            }
        }
    }

    if (esamErrCnt < 3)
    {
        BSP_Esam_Stop();
        esamErrCnt++;
    }
    else
    {
        Bkgrd.PubData.MtSysSta.SysStaBit.EsamErr = 1;
    }
    return ERROR;
}
#endif

//******************************************************************************************************
// �������� fnEsamOp_ReadEsam_Info
// ���룺   P2: ��ȡESAM��Ϣ,P2Ϊ����� Buf:�������ָ�� Len:�������ݳ���
// ���أ�
// ������   ��ȡSAM��Ϣ
//******************************************************************************************************
ErrorStatus fnEsamOp_ReadEsam_Info(u8 P2, u8 *Buf, u16 *Len)
{
    ErrorStatus err;

    fnEsamOp_RxTxCommhead(0x80, 0x36, 0x00, P2, 0x00, 0x00);
    err = fnEsamOp_CardTxRxFrame(ESAM, 0x00, Buf, 0);
    if (err == SUCCESS)
    {
        *Len = ((ICEsamComm.Ic_Comm_RxBuf[2] << 8) + ICEsamComm.Ic_Comm_RxBuf[3]);
        return (SUCCESS);
    }
    else
    {
        return (ERROR);
    }
}

//******************************************************************************************************
// �������� fnEsamOp_ReadEsam_SafeNameList
// ���룺Buf:�������ָ�� Len:�������ݳ���
// ���أ�
// ������   ��ȡESAM��������Ϣ
//******************************************************************************************************
ErrorStatus fnEsamOp_ReadEsam_SafeNameList(u8 *Buf, u16 *Len)
{
    ErrorStatus err;
    u8 txbuf[5] = {0x00, 0x00, 0x00, 0x00, 0x08};

    fnEsamOp_RxTxCommhead(0x80, 0x2C, 0x00, 0x03, 0x00, 0x05);
    err = fnEsamOp_CardTxRxFrame(ESAM, 5, Buf, txbuf);
    if (err == SUCCESS)
    {
        *Len = ((ICEsamComm.Ic_Comm_RxBuf[2] << 8) + ICEsamComm.Ic_Comm_RxBuf[3]);
        return (SUCCESS);
    }
    else
    {
        return (ERROR);
    }
}

//******************************************************************************************************
// �������� ErrorStatus fnEsamOp_ReadMoneyBag(void)
// ���룺   NONE
// ���أ�   SUCCESS  ERROR
// ������   ��ȡESAMǮ���ļ���Ϣ
//******************************************************************************************************
ErrorStatus fnEsamOp_ReadMoneyBag(void)
{
    fnEsamOp_RxTxCommhead(0x80, 0x48, 0x00, 0x00, 0x00, 0x01);
    ICEsamComm.Ic_Comm_TxBuf[6] = 0x06;
    return (fnEsamOp_CardTxRxFrame(ESAM, 0x00, &ICEsamComm.Ic_Comm_TxBuf[6], &ICEsamComm.Ic_Comm_RxBuf[0]));
}

//******************************************************************************************************
// �������� ErrorStatus fnEsamOp_CreatConnect(u8 *SessionData1 , u8 *Mac1 , u8 *SessionData2 , u8 *Mac2  , u8 CA)
// ���룺   SessionData1������ MAC1:�ͻ���ǩ�� SessionData2:�����������
//          Mac2:������ǩ����Ϣ
//          CA = 0xAZ  ��վ;CA = 0x0Z �ն�;Z��������ֵ
// ���أ�   SUCCESS or ERROR
// ������   ����Ӧ������
//******************************************************************************************************
u16 gConnResRnLen;
ErrorStatus fnEsamOp_CreatConnect(u8 *SessionData1, u8 *Mac1, u8 *SessionData2, u8 *Mac2, u8 CA)
{
    ErrorStatus err;

    if (CA & 0xF0) //��վ
    {
        fnEsamOp_RxTxCommhead(0x81, 0x02, 0x00, 0x00, 0x00, 0x24);
    }
    else   //�ն�
    {
        fnEsamOp_RxTxCommhead(0x82, 0x02, 0x00, 0x00, 0x00, 0x24);
    }

    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[6], SessionData1, 32);
    Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[38], Mac1, 4);
    err = fnEsamOp_CardTxRxFrame(ESAM, 0x24, &ICEsamComm.Ic_Comm_RxBuf[4], &ICEsamComm.Ic_Comm_TxBuf[6]);
    if (err == ERROR)
    {
        return (err);
    }
    if (((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61) || ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))))
    {
        gConnResRnLen = (u16)ICEsamComm.Ic_Comm_RxBuf[2] << 8 | ICEsamComm.Ic_Comm_RxBuf[3] - 4;
        Std_Memcpy(SessionData2, &ICEsamComm.Ic_Comm_RxBuf[4], gConnResRnLen);
        Std_Memcpy(Mac2, &ICEsamComm.Ic_Comm_RxBuf[gConnResRnLen + 4], 4);
        if (CA & 0xF0) //��վ
        {
            fnReadDlyTime_Esam(&Secret.Master.tESAMDly, MASTER, 1);
        }
        else
        {
            fnReadDlyTime_Esam(&Secret.Terminal.tESAMDly, TERMINAL, 1);
        }
        return SUCCESS;
    }
    else
    {
        return (ERROR);
    }
}

//******************************************************************************************************
// �������� ErrorStatus fnEsamOp_SessionDestroyed(u8 CA)
// ���룺  chan��ͨ����;    CA = 0xAZ  ��վ;CA = 0x0Z �ն�;Z��������ֵ
// ���أ�   SUCCESS or ERROR
// ������   �ỰʧЧ
//******************************************************************************************************
u8 gActSessionDestroyed;
ErrorStatus fnEsamOp_SessionDestroyed(u8 CA)
{
    ErrorStatus err;

    if (CA & 0xF0) //��վ
    {
        fnEsamOp_RxTxCommhead(0x80, 0x3A, 0x01, 0x00, 0x00, 0x00);
    }
    else
    {
        fnEsamOp_RxTxCommhead(0x80, 0x3A, 0x02, 0x00, 0x00, 0x00);
    }

    err = fnEsamOp_CardTxRxFrame(ESAM, 0, &ICEsamComm.Ic_Comm_RxBuf[4], &ICEsamComm.Ic_Comm_TxBuf[6]);
    if (err == ERROR)
    {
        return (err);
    }
    if ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))
    {
        return SUCCESS;
    }
    else
    {
        return (ERROR);
    }
}

//******************************************************************************************************
// �������� ErrorStatus fnEsamOp_Get_PlainDataMac(u8 *Buf , u8 *Mac)
// ���룺   Buf����������   Mac:��ȡ����������MAC
// ���أ�   SUCCESS or ERROR
// ������   ������������MAC
//******************************************************************************************************

ErrorStatus fnEsamOp_Get_PlainDataMac(u8 chan, u8 *Buf, u16 Len, u8 *Mac)
{
    ErrorStatus err;

    if (chan == SCOM_PORT_SPI)
    {
        fnEsamOp_RxTxCommhead(0x83, 0x0e, 0x48, 0x01, (u8)(Len >> 8), (u8)Len);
    }
    else
    {
        if (Secret.CA & 0xF0)
        {
            fnEsamOp_RxTxCommhead(0x80, 0x0e, 0x40, 0x02, (u8)(Len >> 8), (u8)Len);
        }
        else
        {
            fnEsamOp_RxTxCommhead(0x82, 0x0e, 0x40, 0x02, (u8)(Len >> 8), (u8)Len);
        }
    }
    err = fnEsamOp_CardTxRxFrame(ESAM, Len, &ICEsamComm.Ic_Comm_RxBuf[4], Buf);
    if (err == ERROR)
    {
        return (err);
    }
    if (((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61) || ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))))
    {
        Std_Memcpy(Mac, &ICEsamComm.Ic_Comm_RxBuf[4], 4);
        return SUCCESS;
    }
    else
    {
        return (ERROR);
    }
}

//******************************************************************************************************
// �������� ErrorStatus fnEsamOp_Get_PlainData_RN_Mac(u8 *Buf , u8 *RN_Mac)
// ���룺   Buf����������   Mac:��ȡ����������RN_Mac
// ���أ�   SUCCESS or ERROR
// ������   ������������MAC
//******************************************************************************************************
ErrorStatus fnEsamOp_Get_PlainData_RN_Mac(u8 *Buf, u16 Len, u8 *RN_Mac)
{
    ErrorStatus err;

    fnEsamOp_RxTxCommhead(0x80, 0x14, 0x01, 0x03, (u8)(Len >> 8), (u8)Len);
    err = fnEsamOp_CardTxRxFrame(ESAM, Len, &ICEsamComm.Ic_Comm_RxBuf[4], Buf);
    if (err == ERROR)
    {
        return (err);
    }
    if (((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61) || ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))))
    {
        Std_Memcpy(RN_Mac, &ICEsamComm.Ic_Comm_RxBuf[4], 16);
        return SUCCESS;
    }
    else
    {
        return (ERROR);
    }
}

//******************************************************************************************************
// �������� ErrorStatus fnEsamOp_DataToCipher(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// ���룺   RxBuf:������������   TxBuf:��Ҫ���ܵ���������
//          TxLen:�������ݳ���   RxLen:�����������ݳ���
// ���أ�   SUCCESS or ERROR
// ������   ������������
//******************************************************************************************************
ErrorStatus fnEsamOp_DataToCipher(u8 *RxBuf, u8 *TxBuf, u16 *RxLen, u16 TxLen)
{
    ErrorStatus err;

    fnEsamOp_RxTxCommhead(0x80, 0x0A, 0x40, 0x02, (u8)(TxLen >> 8), (u8)TxLen);
    err = fnEsamOp_CardTxRxFrame(ESAM, TxLen, RxBuf, TxBuf);
    if (err == ERROR)
    {
        return (err);
    }
    if (((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61) || ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))))
    {
        *RxLen = ICEsamComm.Ic_Comm_RxPtr - 4;
        return SUCCESS;
    }
    else
    {
        return (ERROR);
    }
}

//*****************************************************************************************************
// �������� ErrorStatus fnEsamOp_RetDataToCipher(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen , u8 RetType)
// ���룺   RxBuf:�������ļ�MAX����   TxBuf:��Ҫ���ܵ���������
//          TxLen:�������ݳ���   RxLen:�������ļ�MAC���ݳ���
//          RetType:������������ 0:����+MAC   1�� ����  2�� ����+MAC
// ���أ�   SUCCESS or ERROR
// ������   ���ܷ�������
//******************************************************************************************************
ErrorStatus fnEsamOp_RetDataToCipher(u8 *RxBuf, u8 *TxBuf, u16 *RxLen, u16 TxLen, u8 RetType)
{
    ErrorStatus err;
    u8 EsamP2;
    if (RetType == 0)
    {
        EsamP2 = 0x11;
    }
    else if (RetType == 1)
    {
        EsamP2 = 0xa6;
    }
    else if (RetType == 2)
    {
        EsamP2 = 0xa7;
    }
    else
    {
        return (ERROR);
    }
    fnEsamOp_RxTxCommhead(0x81, 0x1C, 0x00, EsamP2, (u8)(TxLen >> 8), (u8)TxLen);
    err = fnEsamOp_CardTxRxFrame(ESAM, TxLen, RxBuf, TxBuf);
    if (err == ERROR)
    {
        return (err);
    }
    if (((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61) || ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))))
    {
        *RxLen = ICEsamComm.Ic_Comm_RxPtr - 4;
        return SUCCESS;
    }
    else
    {
        return (ERROR);
    }
}

//*****************************************************************************************************
// �������� ErrorStatus fnEsamOp_DataToCipherWithMac(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// ���룺   RxBuf:�������ļ�MAX����   TxBuf:��Ҫ���ܵ���������
//          TxLen:�������ݳ���   RxLen:�������ļ�MAC���ݳ���
// ���أ�   SUCCESS or ERROR
// ������  ��վ �����������ݼ�MAC
//******************************************************************************************************
ErrorStatus fnEsamOp_DataToCipherWithMac(u8 *RxBuf, u8 *TxBuf, u16 *RxLen, u16 TxLen, u8 P2)
{
    ErrorStatus err;

    fnEsamOp_RxTxCommhead(0x81, 0x1C, 0x00, P2, (u8)(TxLen >> 8), (u8)TxLen);

    err = fnEsamOp_CardTxRxFrame(ESAM, TxLen, RxBuf, TxBuf);
    if (err == ERROR)
    {
        return (err);
    }
    //if(((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61)||((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))) )
    if ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))
    {
        *RxLen = ICEsamComm.Ic_Comm_RxPtr - 4;
        return SUCCESS;
    }
    else
    {
        return (ERROR);
    }
}

//*****************************************************************************************************
// �������� ErrorStatus fnEsamOp_DataToCipherWithMac(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// ���룺   RxBuf:�������ļ�MAX����   TxBuf:��Ҫ���ܵ���������
//          TxLen:�������ݳ���   RxLen:�������ļ�MAC���ݳ���
//                 ����+MAC  :82240011+Lc+Data3+80241100+LC1
//                              LC1��Data3 ����+4��2 �ֽ�
//                 ����:82240012+Lc+Data3
//
//                ����+MAC:82240013+Lc+Data3+80241300+LC1
//                                     LC1��Data3 ����+3 ���� 16�ֽ�������+4��2 �ֽ�
// ���أ�   SUCCESS or ERROR
// ������ ģ���ն� �����������ݼ�MAC
//******************************************************************************************************
const u8  TrmCipherHead1[4] = {0x80, 0x24, 0x11, 0x00};
const u8  TrmCipherHead2[4] = {0x80, 0x24, 0x13, 0x00};
ErrorStatus fnEsamOp_TrmDataToCipherWithMac(u8 *RxBuf, u8 *TxBuf, u16 *RxLen, u16 TxLen, u8 P2)
{
    ErrorStatus err;
    u16  LC1;

    if (P2 == 0x11)   //����+MAC
    {
        LC1 = TxLen + 4;  //LC1��Data3 ����+4
        Std_Memcpy(TxBuf + TxLen, &TrmCipherHead1[0], 4);
        TxLen += 4;
        Std_Msb16DataSet(TxBuf + TxLen, LC1);
        TxLen += 2;
        fnEsamOp_RxTxCommhead(0x82, 0x24, 0x00, 0x11, (u8)(TxLen >> 8), (u8)TxLen);
    }
    else if (P2 == 0xA6)  //����
    {
        fnEsamOp_RxTxCommhead(0x82, 0x24, 0x00, 0x12, (u8)(TxLen >> 8), (u8)TxLen);
    }
    else if (P2 == 0xA7)  //����+MAC
    {
        //--- LC1��Data3 ����+3 ���� 16�ֽ�������+4------
        LC1 = 16 * ((TxLen + 3 + 15) / 16) +4;
        Std_Memcpy(TxBuf + TxLen, &TrmCipherHead2[0], 4);
        TxLen += 4;
        Std_Msb16DataSet(TxBuf + TxLen, LC1);
        TxLen += 2;
        fnEsamOp_RxTxCommhead(0x82, 0x24, 0x00, 0x13, (u8)(TxLen >> 8), (u8)TxLen);
    }

    err = fnEsamOp_CardTxRxFrame(ESAM, TxLen, RxBuf, TxBuf);
    if (err == ERROR)
    {
        return (err);
    }
    if (((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61) || ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))))
    {
        *RxLen = ICEsamComm.Ic_Comm_RxPtr - 4;
        return SUCCESS;
    }
    else
    {
        return (ERROR);
    }
}

//*****************************************************************************************************
// �������� ErrorStatus fnEsamOp_Check_SID(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// ���룺   RxBuf:�������ļ�MAX����   TxBuf:��Ҫ���ܵ���������
//          TxLen:�������ݳ���   RxLen:�������ļ�MAC���ݳ���
// ���أ�   SUCCESS or ERROR
// ������   ��SID��SID_MAC���ݽ���У�飬������DATA2����
//******************************************************************************************************
ErrorStatus fnEsamOp_Check_SID(u8 *RxBuf, u8 *TxBuf, u16 *RxLen, u16 TxLen)
{
    ErrorStatus err;

    fnEsamOp_RxTxCommhead(TxBuf[0], TxBuf[1], TxBuf[2], TxBuf[3], (u8)(TxLen >> 8), (u8)TxLen);
    err = fnEsamOp_CardTxRxFrame(ESAM, TxLen, RxBuf, &TxBuf[4]);
    if (err == ERROR)
    {
        return (err);
    }
    if (((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61) || ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))))
    {
        *RxLen = ICEsamComm.Ic_Comm_RxPtr - 4;
        return SUCCESS;
    }
    else
    {
        return (ERROR);
    }
}

//*****************************************************************************************************
// �������� ErrorStatus fnEsamOp_Tx_Esam(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// ���룺   RxBuf:�������ļ�MAX����   TxBuf:��Ҫ���ܵ���������
//          TxLen:�������ݳ���   RxLen:�������ļ�MAC���ݳ���
// ���أ�   SUCCESS or ERROR
// ������   ��ESAM�������ݽ��н��ܵȲ���
//******************************************************************************************************
ErrorStatus fnEsamOp_Tx_Esam(u8 *RxBuf, u8 *TxBuf, u16 *RxLen)
{
    ErrorStatus err;
    u16 TxLen;

    fnEsamOp_RxTxCommhead(TxBuf[0], TxBuf[1], TxBuf[2], TxBuf[3], TxBuf[4], TxBuf[5]);
    TxLen = TxBuf[4];
    TxLen = (TxLen << 8) + TxBuf[5];
    err = fnEsamOp_CardTxRxFrame(ESAM, TxLen, RxBuf, &TxBuf[6]);

    if (err == SUCCESS)
    {
        //SEGGER_RTT_printf(0,"EsamOp Success\n");
        if ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))
        {
            *RxLen = ICEsamComm.Ic_Comm_RxPtr - 4;
        }
        else
        {
            err = ERROR;
        }
    }

    fnICEsam_MacErrInc(err);

    return (err);
}

//*****************************************************************************************************
// �������� ErrorStatus fnEsamOp_Check_SID(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// ���룺   RxBuf:�������ļ�MAX����   TxBuf:��Ҫ���ܵ���������
//          TxLen:�������ݳ���   RxLen:�������ļ�MAC���ݳ���
// ���أ�   SUCCESS or ERROR
// ������   ��SID��SID_MAC���ݽ���У�飬������DATA2����
//******************************************************************************************************
ErrorStatus fnEsamOp_ReadBinFile(u8 *RxBuf, u8 *TxBuf, u16 *RxLen, u16 TxLen)
{
    return (fnEsamOp_Check_SID(RxBuf, TxBuf, RxLen, TxLen));
}

//*****************************************************************************************************
// �������� ErrorStatus fnEsamOp_GetEsamBuf(u8 actflag,u8* pBuf,u8 *pLen,sDl698_EsamParam_TypeDef *pParam)
// ���룺   actflag:������ʶ
//          pBuf:��װ��Ŀ��buf
//          pLen: ָ������װ��Ŀ��buf��������ָ��
//          pParam: ��װbuf��Ҫ�õ������
// ���أ�   SUCCESS or ERROR
// ������   ��ȡ���ݲ�ͬ������ʶ����װ���͸�Esam��֡����
//******************************************************************************************************
ErrorStatus fnEsamOp_GetSendToEsamFrame(u8 actflag, u8* pBuf, u16 *pLen, sDl698_EsamParam_TypeDef *pParam)
{
    if (pBuf == NULL)
    {
        return ERROR;
    }
    switch (actflag)
    {
        case ESAM_DATA_READ:
        {
            //����: ��ʶ + ��������AttachData
            UINT32_TO_STREAM(pBuf, pParam->SID.flag);
            Std_Memcpy(pBuf, pParam->SID.pData, pParam->SID.datalen);
            pBuf += pParam->SID.datalen;
            *pLen = 4 + pParam->SID.datalen;
            break;
        }
        case ESAM_PURSE_OPTION:
        {
            //����: ��ʶ + ��������AttachData + ������ +������� +�ͻ���� +����Mac
            UINT32_TO_STREAM(pBuf, pParam->SID.flag);
            Std_Memcpy(pBuf, pParam->SID.pData, pParam->SID.datalen);
            pBuf += pParam->SID.datalen;
            UINT32_TO_STREAM(pBuf, pParam->moneryPurse.money);
            UINT32_TO_STREAM(pBuf, pParam->moneryPurse.times);
            Std_Memcpy(pBuf, pParam->moneryPurse.pUserNum, pParam->moneryPurse.pUserNumlen);
            pBuf += pParam->moneryPurse.pUserNumlen;
            Std_Memcpy(pBuf, pParam->pMac, pParam->maclen);
            pBuf += pParam->maclen;
            *pLen = 8 + pParam->SID.datalen + pParam->maclen + pParam->moneryPurse.pUserNumlen;
            break;
        }
        case ESAM_DATA_UPDATE:
        case ESAM_KEY_UPDATE:
        {
            //����: ��ʶ + ��������AttachData + Endata1 +����Mac
            UINT32_TO_STREAM(pBuf, pParam->SID.flag);
            Std_Memcpy(pBuf, pParam->SID.pData, pParam->SID.datalen);
            pBuf += pParam->SID.datalen;
            Std_Memcpy(pBuf, pParam->pOctString, pParam->len);
            pBuf += pParam->len;
            Std_Memcpy(pBuf, pParam->pMac, pParam->maclen);
            pBuf += pParam->maclen;
            *pLen = 4 + pParam->SID.datalen + pParam->maclen + pParam->len;
            break;
        }
        case ESAM_PURSE_INIT:
        {
            //����: ��ʶ + ��������AttachData + D1 +����Mac
            UINT32_TO_STREAM(pBuf, pParam->SID.flag);
            Std_Memcpy(pBuf, pParam->SID.pData, pParam->SID.datalen);
            pBuf += pParam->SID.datalen;
            UINT32_TO_STREAM(pBuf, pParam->moneryPurse.money);
            Std_Memcpy(pBuf, pParam->pMac, pParam->maclen);
            pBuf += pParam->maclen;
            *pLen = 8 + pParam->SID.datalen + pParam->maclen;
            break;
        }
        case ESAM_RESET:
        case ESAM_OPTION:
        case ESAM_NEGO_FAILE:
        case ESAM_CERTIFICATE_UPDATE:
        case ESAM_DATA_SET:
        {
            //����: ��ʶ + ��������AttachData +Data1
            UINT32_TO_STREAM(pBuf, pParam->SID.flag);
            Std_Memcpy(pBuf, pParam->SID.pData, pParam->SID.datalen);
            pBuf += pParam->SID.datalen;
            Std_Memcpy(pBuf, pParam->pOctString, pParam->len);
            pBuf += pParam->len;
            *pLen = 4 + pParam->SID.datalen + pParam->len;
            break;
        }

        default:
        {
            return ERROR;
        }
    }
    return SUCCESS;
}

//*****************************************************************************************************
// �������� ErrorStatus fnEsamOp_Reset(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// ���룺
//
// ���أ�   SUCCESS or ERROR
// ������
//******************************************************************************************************
ErrorStatus fnEsamOp_Reset(u8 *RxBuf)
{
    u8 i, err;

    for (i = 0; i < 3; i++)
    {
        EsamPowerOff();
        fnDelayMs(100); //��ʱ100ms
        EsamPowerOn();
        fnDelayMs(100); //��ʱ100ms
        DISABLE_ESAM();

        fnEsamOp_RxTxCommhead(0x80, 0x36, 0x00, 0x02, 0x00, 0x00);
        err = fnEsamOp_CardTxRxFrame(ESAM, 0x00, RxBuf, 0);
        if (err == SUCCESS)
        {
            Bkgrd.PubData.MtSta.MtSta1.StaBit.EsamErr = 0;
            Bkgrd.PubData.MtSysSta.SysStaBit.EsamErr = 0;
            return SUCCESS;
        }
    }

    Bkgrd.PubData.MtSta.MtSta1.StaBit.EsamErr = 1;
    Bkgrd.PubData.MtSysSta.SysStaBit.EsamErr = 1;
    return ERROR;
}

ErrorStatus fnEsam_In_Auth(u8 type, u8 *RxBuf, u8 *TxBuf)
{
    ErrorStatus err;

    if (type == MASTER)
    {
        fnEsamOp_RxTxCommhead(0x80, 0x08, 0x08, 0x01, 0x00, 0x18);
        err = fnEsamOp_CardTxRxFrame(ESAM, 0x18, RxBuf, TxBuf);
    }
    else if (type == TERMINAL)
    {
        fnEsamOp_RxTxCommhead(0x80, 0x08, 0x00, 0x02, 0x00, 0x08);
        err = fnEsamOp_CardTxRxFrame(ESAM, 0x08, RxBuf, TxBuf);
    }
    else
    {
        return (ERROR);
    }

    if (err == ERROR)
    {
        return (err);
    }

    //if(((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61)||((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))) )
    if ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))
    {
        return SUCCESS;
    }
    else
    {
        return (ERROR);
    }
}

ErrorStatus fnEsam_Random(u8 type, u8 *RxBuf)
{
    ErrorStatus err;

    if (type == MASTER)
    {
        fnEsamOp_RxTxCommhead(0x83, 0x04, 0x00, 0x10, 0x00, 0x00);
        err = fnEsamOp_CardTxRxFrame(ESAM, 0x00, RxBuf, &ICEsamComm.Ic_Comm_TxBuf[10]);
    }
    else if (type == TERMINAL)
    {
        fnEsamOp_RxTxCommhead(0x82, 0x04, 0x00, 0x08, 0x00, 0x00);
        err = fnEsamOp_CardTxRxFrame(ESAM, 0x00, RxBuf, &ICEsamComm.Ic_Comm_TxBuf[10]);
    }
    else
    {
        return (ERROR);
    }

    if (err == SUCCESS)
    {
        return (SUCCESS);
    }
    else
    {
        fnICEsam_MacErrInc(err);
        return (ERROR);
    }
}

//-------�ⲿ��֤-----------
ErrorStatus fnEsam_Out_Auth(u8 type, u8 *RxBuf, u8 *TxBuf)
{
    ErrorStatus err;

    if (type == MASTER)
    {
        fnEsamOp_RxTxCommhead(0x83, 0x06, 0x08, 0x01, 0x00, 0x10);
        err = fnEsamOp_CardTxRxFrame(ESAM, 0x10, RxBuf, TxBuf);
    }
    else if (type == TERMINAL)
    {
        fnEsamOp_RxTxCommhead(0x82, 0x06, 0x00, 0x02, 0x00, 0x08);
        err = fnEsamOp_CardTxRxFrame(ESAM, 0x08, RxBuf, TxBuf);
    }
    else
    {
        return (ERROR);
    }

    if (err == ERROR)
    {
        return (ERROR);
    }

    //if(((ICEsamComm.Ic_Comm_RxBuf[0] == 0x61)||((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))) )
    if ((ICEsamComm.Ic_Comm_RxBuf[0] == 0x90) && (ICEsamComm.Ic_Comm_RxBuf[1] == 0x00))
    {
        return SUCCESS;
    }
    else
    {
        fnICEsam_MacErrInc(err);
        return (ERROR);
    }
}
