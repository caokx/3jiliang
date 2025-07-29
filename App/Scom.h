
#ifndef _SCOM_H
#define _SCOM_H

#ifdef   _SCOM_GLOBALS
#define  SCOM_EXT
#else
#define  SCOM_EXT  extern
#endif

#define CHANNEL_NUM SCOM_PORT_MAX

#define MAX_COMPACK_SIZE    256

typedef enum
{
    SCOMPK_EFLAG_IDLE = 0,
    SCOMPK_EFLAG_RXBUSY,
    SCOMPK_EFLAG_RXFINISH,
    SCOMPK_EFLAG_TXBUSY,
    SCOMPK_EFLAG_TXFINISH,
    SCOMPK_EFLAG_INIT
} eScomFlag_TypeDef;

typedef enum
{
    PTTYEP_DL645    = 1,
    PTTYEP_DL698    = 2,
    PTTYEP_NONE = 0xFF
} ePtType_TypeDef;

#pragma pack(1)
typedef struct
{
    u8  Head1;
    u8  Addr[6];
    u8  Head2;

    //  u8 Ctl;
    u8  AFN : 5;
    u8  Persist : 1;
    u8  Ack : 1;
    u8  Dir : 1;

    u8 Len;

    struct
    {
        u8  DI0;
        u8  DI1;
        u8  DI2;
        u8  DI3;
        u8  Dat[MAX_COMPACK_SIZE - 16];
    } UDat;

    u8  Cs;
    u8  Tail;
} sFrmDl645B_TypeDef;   //DL645-2007协议帧结构

typedef struct
{
    u16     EFlag;          //通讯状态

    u16     RxLen;
    u16     TxLen;
    u32     TimeOutStamp;
    u8      *pTx;

    u8      fBps;               //波特率变更标志
    u8      NewBps;             //新波特率
    u32     NewBpsStamp;        //新速率时标

    u8      UartId;             //保存对应的uartid号
    u8      *RTxBuf;
} sComPack_TypeDef;

#pragma pack()

//SCOM_EXT sComPack_TypeDef ComPack[SCOM_PORT_MAX];

typedef enum
{
    USART_EVEN_PARITY   = 0x08, //校验位
    USART_ODD_PARITY    = 0x0C,
    USART_NO_PARITY     = 0x00,

    USART_1STOP_SBIT    = 0x00, //停止位
    USART_2STOP_SBIT    = 0x10,

    USART_5BIT_DAT      = 0x00, //数据位
    USART_6BIT_DAT      = 0x01,
    USART_7BIT_DAT      = 0x02,
    USART_8BIT_DAT      = 0x03,

    USART_BPS_300       = 0x00, //波特率
    USART_BPS_600       = 0x20,
    USART_BPS_1200      = 0x30,
    USART_BPS_2400      = 0x40,
    USART_BPS_4800      = 0x50,
    USART_BPS_7200      = 0x60,
    USART_BPS_9600      = 0x70,
    USART_BPS_19200     = 0x80,
    USART_BPS_38400     = 0x90,
    USART_BPS_57600     = 0xA0,
    USART_BPS_115200    = 0xB0
} eUsartPara_TypeDef;

extern const u8 eUsartBps_Def[11];
extern void fnScomUart_Init(u8 ComPort);
extern void fnScomSpi_Init(u8 ComPort);
extern void fnScomPk_Init(u8 ComPort);  //通讯包初始化
extern void fnScomPk_ChangeBps(u8 ComPort);   //修改波特率
extern void fnScomPk_Exec(void);  //通讯包执行--
extern u8 *fnPt_Check(u8 *Src, u16 Len, ePtType_TypeDef *PtType);    //帧格式检测
extern u16 fnPt_Exec(u8 ComPort);  //协议执行
extern void fnScom_ReadBps(void);
extern void fnComAddrGet(u8 *pAddr);
extern void fnScomStartSend(u8 fifo_Id, u16 txlen, u8*TxBuffer);
//-------------------------------
#endif // _SCOM_H

//-------------------------------
