#ifndef  _DL698_ICEsam_H
#define  _DL698_ICEsam_H
//Esam Action
#define ESAM_RESET               0x01
#define ESAM_OPTION              0x02
#define ESAM_DATA_READ           0x03
#define ESAM_DATA_UPDATE         0x04
#define ESAM_NEGO_FAILE          0x05
#define ESAM_PURSE_OPTION        0x06
#define ESAM_KEY_UPDATE          0x07
#define ESAM_CERTIFICATE_UPDATE  0x08
#define ESAM_DATA_SET            0x09
#define ESAM_PURSE_INIT          0x0A
#define ESAM_IR_ASK              0x0B
#define ESAM_IR_ORDER            0x0C
#define ESAM_MNG_SET             0xFE

typedef struct
{
    u16   datalen;
    u8  *pData;
    u32  flag;
} sDl698_SID_TypeDef;

typedef struct
{
    u8 Dl698EsamId[8];          // ESAM序列号
    u8 Dl698EsamVer[5];         // ESAM版本号
    u8 CipherVer[16];           // 密钥版本
    u32 RemoteTime;             // 会话时限门限
    u32 tDecRTime;              // 会话时限剩余时间
} sDl698Esam_TypeDef;

typedef struct
{
    u32 money;
    u32 times;
    u8  *pUserNum;
    u16  pUserNumlen;
    u8  *pMeterNum;
    u16  pMeterNumlen;
} sDl698_MoneyPurse_TypeDef;

typedef struct
{
    s8  op;
    u8 *pOctString;
    u16 len;
    u8 *pMac;
    u8  maclen;
    sDl698_SID_TypeDef SID;
    sDl698_MoneyPurse_TypeDef moneryPurse;
} sDl698_EsamParam_TypeDef;

extern u8 gActSessionDestroyed;
extern u16 gConnResRnLen;

extern ErrorStatus fnEsamOp_ReadEsam_Info(u8 P2, u8 *Buf, u16 *Len);
extern ErrorStatus fnEsamOp_ReadEsam_SafeNameList(u8 *Buf, u16 *Len);
extern void fnEsamOp_EsamInit(void);
extern void fnEsamOp_RxTxCommhead(u8 cal, u8 ins, u8 P1, u8 P2, u8 len1, u8 len2);
extern ErrorStatus fnEsamOp_CardTxRxFrame(u8 CH, u16 Lc, u8 *RxBuf, u8 *TxBuf);
extern ErrorStatus fnEsamOp_GetSendToEsamFrame(u8 actflag, u8* pBuf, u16 *pLen, sDl698_EsamParam_TypeDef *pParam);
ErrorStatus fnEsamOp_DataToCipher(u8 *RxBuf, u8 *TxBuf, u16 *RxLen, u16 TxLen);
ErrorStatus fnEsamOp_DataToCipherWithMac(u8 *RxBuf, u8 *TxBuf, u16 *RxLen, u16 TxLen, u8 P2);
ErrorStatus fnEsamOp_TrmDataToCipherWithMac(u8 *RxBuf, u8 *TxBuf, u16 *RxLen, u16 TxLen, u8 P2);

ErrorStatus fnEsamOp_Get_PlainDataMac(u8 chan, u8 *Buf, u16 Len, u8 *Mac);

ErrorStatus fnEsamOp_Get_PlainData_RN_Mac(u8 *Buf, u16 Len, u8 *RN_Mac);
extern ErrorStatus fnEsamOp_Tx_Esam(u8 *RxBuf, u8 *TxBuf, u16 *RxLen);
extern ErrorStatus fnEsamOp_RetDataToCipher(u8 *RxBuf, u8 *TxBuf, u16 *RxLen, u16 TxLen, u8 RetType);
extern ErrorStatus fnEsamOp_Reset(u8 *RxBuf);
extern ErrorStatus fnEsam_In_Auth(u8 type, u8 *RxBuf, u8 *TxBuf);
extern ErrorStatus fnEsam_Random(u8 type, u8 *RxBuf);
extern ErrorStatus fnEsam_Out_Auth(u8 type, u8 *RxBuf, u8 *TxBuf);

extern ErrorStatus fnEsamOp_SessionDestroyed(u8 CA);

#endif  //_ESAM_H
