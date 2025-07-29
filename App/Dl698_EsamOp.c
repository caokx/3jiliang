
#define  _DL698_EsamOp_GLOBALS
#include <App.h>

//******************************************************************************************************
// 函数名： void fnEsamOp_EsamInit(void)
// 输入：   ESAM初始化
// 返回：   NONE
// 描述：   NONE
//******************************************************************************************************
void fnEsamOp_EsamInit(void)
{
    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }
    //fnSPI_Mast_Init(SPI1_ID , 0x03, 2000);//  //2M  SPISpeed
    fnWDT_Restart();
    EsamPowerOn();   //ESAM 电源打开后，需等待50ms以上再去操作ESAM
    BSP_EsamSpi_Init();
    fnDelayMs(40); //延时80ms
}

//******************************************************************************************************
// 函数名： void fnEsamOp_RxTxCommhead( u8 cal, u8 ins, u8 P1, u8 P2, u8 len1, u8 len2)
// 输入：   SPI ESAM发送头数据
// 返回：   NONE
// 描述：   ESAM发送头数据
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
// 函数名： ErrorStatus fnEsamOp_CardTxRxFrame( u8 CH, u8 Lc, u8 Le , u8 *RxBuf , u8 *TxBuf)
// 输入：   CH 卡或ESAM选择 Lc 发送数据长度需减去5或6字节命令
//          RxBuf: 接收数据BUF指针  TxBuf：发送数据BUF指针
// 返回：   SUCCESS为正确，ERROR为不正确
// 描述：   卡发送及接收数据
//******************************************************************************************************
#if 1
u8 esamErrCnt = 0;
ErrorStatus fnEsamOp_CardTxRxFrame(u8 CH, u16 Lc, u8 *RxBuf, u8 *TxBuf)
{
    u8 Temp_Data, Proc_Byte;
    u8 Rept1, Rept2;
    u16 k;
    u8 ErrFlg;

    if (BSP_EASM_GetPower() == false) //ESAM电源关闭时需先打开
    {
        fnWDT_Restart();
        fnEsamOp_EsamInit();
    }
    Std_Memset(ICEsamComm.Ic_Comm_RxBuf, 0x00, MAX_ICEsamCom_SIZE);

    // SPI 接口ESAM通讯
    ErrFlg = 1;
    for (Rept1 = 0; Rept1 < 3; Rept1++)
    {
        u8 chksum;
        u16 RxLen;

        fnWDT_Restart();

        ENABLE_ESAM();
        SystemDelayUs(60);
        fnCardSendByte(CH, 0x55);   //;取待发送数据
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
        fnCardSendByte(CH, chksum);     //;发送校验和数据
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
            // 连续接收4字节数据
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
// 函数名： fnEsamOp_ReadEsam_Info
// 输入：   P2: 获取ESAM信息,P2为类序号 Buf:存放数据指针 Len:返回数据长度
// 返回：
// 描述：   获取SAM信息
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
// 函数名： fnEsamOp_ReadEsam_SafeNameList
// 输入：Buf:存放数据指针 Len:返回数据长度
// 返回：
// 描述：   获取ESAM白名单信息
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
// 函数名： ErrorStatus fnEsamOp_ReadMoneyBag(void)
// 输入：   NONE
// 返回：   SUCCESS  ERROR
// 描述：   获取ESAM钱包文件信息
//******************************************************************************************************
ErrorStatus fnEsamOp_ReadMoneyBag(void)
{
    fnEsamOp_RxTxCommhead(0x80, 0x48, 0x00, 0x00, 0x00, 0x01);
    ICEsamComm.Ic_Comm_TxBuf[6] = 0x06;
    return (fnEsamOp_CardTxRxFrame(ESAM, 0x00, &ICEsamComm.Ic_Comm_TxBuf[6], &ICEsamComm.Ic_Comm_RxBuf[0]));
}

//******************************************************************************************************
// 函数名： ErrorStatus fnEsamOp_CreatConnect(u8 *SessionData1 , u8 *Mac1 , u8 *SessionData2 , u8 *Mac2  , u8 CA)
// 输入：   SessionData1：密文 MAC1:客户机签名 SessionData2:服务器随机数
//          Mac2:服务器签名信息
//          CA = 0xAZ  主站;CA = 0x0Z 终端;Z代表任意值
// 返回：   SUCCESS or ERROR
// 描述：   建立应用连接
//******************************************************************************************************
u16 gConnResRnLen;
ErrorStatus fnEsamOp_CreatConnect(u8 *SessionData1, u8 *Mac1, u8 *SessionData2, u8 *Mac2, u8 CA)
{
    ErrorStatus err;

    if (CA & 0xF0) //主站
    {
        fnEsamOp_RxTxCommhead(0x81, 0x02, 0x00, 0x00, 0x00, 0x24);
    }
    else   //终端
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
        if (CA & 0xF0) //主站
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
// 函数名： ErrorStatus fnEsamOp_SessionDestroyed(u8 CA)
// 输入：  chan：通道号;    CA = 0xAZ  主站;CA = 0x0Z 终端;Z代表任意值
// 返回：   SUCCESS or ERROR
// 描述：   会话失效
//******************************************************************************************************
u8 gActSessionDestroyed;
ErrorStatus fnEsamOp_SessionDestroyed(u8 CA)
{
    ErrorStatus err;

    if (CA & 0xF0) //主站
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
// 函数名： ErrorStatus fnEsamOp_Get_PlainDataMac(u8 *Buf , u8 *Mac)
// 输入：   Buf：明文数据   Mac:获取的明文数据MAC
// 返回：   SUCCESS or ERROR
// 描述：   计算明文数据MAC
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
// 函数名： ErrorStatus fnEsamOp_Get_PlainData_RN_Mac(u8 *Buf , u8 *RN_Mac)
// 输入：   Buf：明文数据   Mac:获取的明文数据RN_Mac
// 返回：   SUCCESS or ERROR
// 描述：   计算明文数据MAC
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
// 函数名： ErrorStatus fnEsamOp_DataToCipher(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// 输入：   RxBuf:接收密文数据   TxBuf:需要加密的明文数据
//          TxLen:明文数据长度   RxLen:接收密文数据长度
// 返回：   SUCCESS or ERROR
// 描述：   计算密文数据
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
// 函数名： ErrorStatus fnEsamOp_RetDataToCipher(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen , u8 RetType)
// 输入：   RxBuf:接收密文及MAX数据   TxBuf:需要加密的明文数据
//          TxLen:明文数据长度   RxLen:接收密文及MAC数据长度
//          RetType:返回数据类型 0:明文+MAC   1： 密文  2： 密文+MAC
// 返回：   SUCCESS or ERROR
// 描述：   加密返回数据
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
// 函数名： ErrorStatus fnEsamOp_DataToCipherWithMac(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// 输入：   RxBuf:接收密文及MAX数据   TxBuf:需要加密的明文数据
//          TxLen:明文数据长度   RxLen:接收密文及MAC数据长度
// 返回：   SUCCESS or ERROR
// 描述：  主站 计算密文数据及MAC
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
// 函数名： ErrorStatus fnEsamOp_DataToCipherWithMac(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// 输入：   RxBuf:接收密文及MAX数据   TxBuf:需要加密的明文数据
//          TxLen:明文数据长度   RxLen:接收密文及MAC数据长度
//                 明文+MAC  :82240011+Lc+Data3+80241100+LC1
//                              LC1：Data3 长度+4，2 字节
//                 密文:82240012+Lc+Data3
//
//                密文+MAC:82240013+Lc+Data3+80241300+LC1
//                                     LC1：Data3 长度+3 后补齐 16字节整数倍+4，2 字节
// 返回：   SUCCESS or ERROR
// 描述： 模拟终端 计算密文数据及MAC
//******************************************************************************************************
const u8  TrmCipherHead1[4] = {0x80, 0x24, 0x11, 0x00};
const u8  TrmCipherHead2[4] = {0x80, 0x24, 0x13, 0x00};
ErrorStatus fnEsamOp_TrmDataToCipherWithMac(u8 *RxBuf, u8 *TxBuf, u16 *RxLen, u16 TxLen, u8 P2)
{
    ErrorStatus err;
    u16  LC1;

    if (P2 == 0x11)   //明文+MAC
    {
        LC1 = TxLen + 4;  //LC1：Data3 长度+4
        Std_Memcpy(TxBuf + TxLen, &TrmCipherHead1[0], 4);
        TxLen += 4;
        Std_Msb16DataSet(TxBuf + TxLen, LC1);
        TxLen += 2;
        fnEsamOp_RxTxCommhead(0x82, 0x24, 0x00, 0x11, (u8)(TxLen >> 8), (u8)TxLen);
    }
    else if (P2 == 0xA6)  //密文
    {
        fnEsamOp_RxTxCommhead(0x82, 0x24, 0x00, 0x12, (u8)(TxLen >> 8), (u8)TxLen);
    }
    else if (P2 == 0xA7)  //密文+MAC
    {
        //--- LC1：Data3 长度+3 后补齐 16字节整数倍+4------
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
// 函数名： ErrorStatus fnEsamOp_Check_SID(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// 输入：   RxBuf:接收密文及MAX数据   TxBuf:需要加密的明文数据
//          TxLen:明文数据长度   RxLen:接收密文及MAC数据长度
// 返回：   SUCCESS or ERROR
// 描述：   对SID及SID_MAC数据进行校验，并返回DATA2数据
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
// 函数名： ErrorStatus fnEsamOp_Tx_Esam(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// 输入：   RxBuf:接收密文及MAX数据   TxBuf:需要加密的明文数据
//          TxLen:明文数据长度   RxLen:接收密文及MAC数据长度
// 返回：   SUCCESS or ERROR
// 描述：   对ESAM发送数据进行解密等操作
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
// 函数名： ErrorStatus fnEsamOp_Check_SID(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// 输入：   RxBuf:接收密文及MAX数据   TxBuf:需要加密的明文数据
//          TxLen:明文数据长度   RxLen:接收密文及MAC数据长度
// 返回：   SUCCESS or ERROR
// 描述：   对SID及SID_MAC数据进行校验，并返回DATA2数据
//******************************************************************************************************
ErrorStatus fnEsamOp_ReadBinFile(u8 *RxBuf, u8 *TxBuf, u16 *RxLen, u16 TxLen)
{
    return (fnEsamOp_Check_SID(RxBuf, TxBuf, RxLen, TxLen));
}

//*****************************************************************************************************
// 函数名： ErrorStatus fnEsamOp_GetEsamBuf(u8 actflag,u8* pBuf,u8 *pLen,sDl698_EsamParam_TypeDef *pParam)
// 输入：   actflag:方法标识
//          pBuf:封装后目的buf
//          pLen: 指向填充封装后目的buf长度内容指针
//          pParam: 封装buf需要用到的入参
// 返回：   SUCCESS or ERROR
// 描述：   获取根据不同方法标识，封装发送给Esam的帧内容
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
            //发送: 标识 + 附加数据AttachData
            UINT32_TO_STREAM(pBuf, pParam->SID.flag);
            Std_Memcpy(pBuf, pParam->SID.pData, pParam->SID.datalen);
            pBuf += pParam->SID.datalen;
            *pLen = 4 + pParam->SID.datalen;
            break;
        }
        case ESAM_PURSE_OPTION:
        {
            //发送: 标识 + 附加数据AttachData + 购电金额 +购电次数 +客户编号 +数据Mac
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
            //发送: 标识 + 附加数据AttachData + Endata1 +数据Mac
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
            //发送: 标识 + 附加数据AttachData + D1 +数据Mac
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
            //发送: 标识 + 附加数据AttachData +Data1
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
// 函数名： ErrorStatus fnEsamOp_Reset(u8 *RxBuf , u8 *TxBuf , u16 *RxLen , u16 TxLen)
// 输入：
//
// 返回：   SUCCESS or ERROR
// 描述：
//******************************************************************************************************
ErrorStatus fnEsamOp_Reset(u8 *RxBuf)
{
    u8 i, err;

    for (i = 0; i < 3; i++)
    {
        EsamPowerOff();
        fnDelayMs(100); //延时100ms
        EsamPowerOn();
        fnDelayMs(100); //延时100ms
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

//-------外部认证-----------
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
