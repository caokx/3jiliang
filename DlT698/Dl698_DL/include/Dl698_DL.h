/********************************************************************
Filename:       Dl698_DL.h
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:         lin.xiaoman

Description:   data link layer data type definitions
**********************************************************************/
#ifndef _DL698DL_H_
#define _DL698DL_H_

/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"
#include "Dl698_Scom.h"
/*********************************************************************
* TYPEDEFS
*/
typedef enum
{
    DL698DL_SERVER_ADDR_TYPE_UNICAST        = 0,
    DL698DL_SERVER_ADDR_TYPE_WILDCARD       = 1,
    DL698DL_SERVER_ADDR_TYPE_MULTICAST      = 2,
    DL698DL_SERVER_ADDR_TYPE_BROADCAST      = 3
} eDl698DL_ServerAddr_TypeDef;

typedef enum
{
    DL698DL_FRAME_TYPE_C2S_RESPONSE    = 0x00,
    DL698DL_FRAME_TYPE_C2S_REQUEST     = 0x01,
    DL698DL_FRAME_TYPE_S2C_REPORT      = 0x02,
    DL698DL_FRAME_TYPE_S2C_RESPONSE    = 0x03
} eDl698DL_frame_TypeDef;

typedef enum
{
    DL698DL_RX_ERR_INFO_FIELD_SIZE    = -1,  //收到不合法信息域长度
    DL698DL_RX_ERR_RECV_NUM           = -2,  //收到N(R)序号无效
    DL698DL_ERR_SA_ADDR               = -3,  //不合法SA地址
    DL698DL_ERR_CA_ADDR               = -4,  //不合法CA地址
    DL698DL_RX_I_INFO_CHEACK_ERR      = -5,  //apdu 分片帧头校验不合法
    DL698DL_ERR_HCS                   = -6,  //hcs校验出错
    DL698DL_ERR_FCS                   = -7,  //fcs校验出错
    DL698DL_ERR_DIR_PRM               = -8,   //帧发送方向出错
    DL698DL_ERR_AL_MEM_ALLOC          = -9   //上报AL失败，apdu buffer申请失败
} eDL698DL_ErrCode_TypeDef;

typedef enum
{
    DL698DL_SEGMEMT_FRAME_TYPE_START    = 0,
    DL698DL_SEGMEMT_FRAME_TYPE_LAST     = 1,
    DL698DL_SEGMEMT_FRAME_TYPE_ACK      = 2,
    DL698DL_SEGMEMT_FRAME_TYPE_MIDDLE   = 3
} eDl698DL_Segmentframe_TypeDef;

typedef enum
{
    DL698DL_FUNCODE_TYPE_LINKCTRL    = 1,
    DL698DL_FUNCODE_TYPE_DATAEXG     = 3
} eDl698DL_funCode_TypeDef;

typedef struct
{
    u8 ucUartType;  //通讯类型，645或698
    u8 ucUartId;
    //    u8 ucBaudRate;
    u8 ucComflag;
    u8 ucTimeout;
    u8 ucPktType;
    u16 usFramelen;
    u16 ucToStamp;     //帧间超时时间存储
    u16 ucToStamp2;    //帧内超时时间存储
} sDl698DL_ScomCtrl_TypeDef;

typedef struct
{
    u8  ubLen      : 4,
    ubLogic    : 2,
    ubAddrType : 2;
    u8  *pAddr;      //server地址的前面2字节表示逻辑器件地址 dyf 改用法、注释，前面1字节为扩展逻辑地址，接收报文时保存
} sServerAddr_TypeDef;

typedef struct
{
    sServerAddr_TypeDef *pSA;
    u8                  ucCA;   //
} sDl698DL_Address_TypeDef;

typedef struct
{
    u16 ubNumber : 12,
        ubReserve: 2, //
        ubType   : 2;
} sSegmentHdr_TypeDef;

typedef struct
{
    u8  ubCode    : 3,
    ubScramble: 1, //扰码
    ubResever : 1,
    ubSegment : 1,
    ubDirPrm  : 2;
} sDl698DL_CtrlInfo_TypeDef;

//解析后帧的主要存储内容
typedef struct
{
    //长度域
    u16 usFrameLen;

    //控制域
    u8  ubCode    : 3,
    ubScramble: 1, //扰码
    ubResever : 1,
    ubSegment : 1,
    ubDirPrm  : 2;

    //Address域
    sServerAddr_TypeDef stSA;      //server地址的前面2字节表示逻辑器件地址
    u8  ucCA;       //client地址,1字节

    //用户数据域
    u16 usInfoLen;
    u8  *pInfo;
} sDl698DL_FrameInfo_TypeDef;

//接收缓存
typedef struct
{
    u16 usIndex;
    u16 usDataLen;    //有效的数据长度，当长度为0时表示没有有效数据
    u8  pData[2048 + 21];//512+21
} sDl698DL_RxBuf_TypeDef;

//发送缓存
typedef struct
{
    u16 usIndex;
    u16 usDataLen;//有效的数据长度，当长度为0时表示没有有效数据
    u8  pData[2048 + 21];//512+21
} sDl698DL_TxBuf_TypeDef;

//管理一个data_link通道
typedef struct
{
    //u8                 ucChannId;
    u16                 ucNumRecv;     //N(R)
    u16                 ucNumSend;     //N(S)
    u16                usState;
    sDl698DL_ScomCtrl_TypeDef    stScom;
    sDl698DL_Address_TypeDef     stAddr;
    sDl698DL_RxBuf_TypeDef       stRxBuf;       //接收数据缓冲区管理
    sDl698DL_TxBuf_TypeDef       stTxBuf;       //发送数据缓冲区管理
    sDl698DL_FrameInfo_TypeDef   stRxFrameInfo; //下面包含接收到的帧的信息
} sDl698DL_ChannelInfo_TypeDef;
/*********************************************************************
* MACROS
*/
#define DL698DL_DEFAULT_CLIENT_ADDR  0x00

/** @defgroup DL698DL_STATE_MASK
* @{
*/
#define DL698DL_STATE_MASK_LINKED             0x0001  //!< 表示通道处于连接状态
#define DL698DL_STATE_MASK_RESPOSE_ACK        0x0002  //!< 表示需要响应ACK帧
#define DL698DL_STATE_MASK_ACK_WAITING        0x0004  //!< 表示处于ACK帧侦听中
#define DL698DL_STATE_MASK_RX_FRAGMENT        0x0008  //!< 表示通道正处于接收分片帧状态
#define DL698DL_STATE_MASK_TX_FRAGMENT        0x0010  //!< 表示通道正处于发送分片帧状态
#define DL698DL_STATE_MASK_RESEND             0x0020  //!< 表示需要执行重传

/** @} End DL698DL_STATE_MASK */
#define DL698DL_MAX_CHANNEL_NUM        gDl698AL_Server.channel_number
#define DL698DL_RX_INFO_SIZE(id)       gDl698AL_Server.pAlChan[id].nego.apdu_size_rx_nego
#define DL698DL_TX_INFO_SIZE(id)       gDl698AL_Server.pAlChan[id].nego.apdu_size_tx_nego
#define DL698DL_GET_FUNCODE(id)        gDl698AL_Server.pAlChan[id].funcode
#define DL698DL_GET_DIRPRM(id)         gDl698AL_Server.pAlChan[id].dirprm

#define DL698DL_SET_FLAG(id,flag)      (pDl698DL_Channel[id].usState |= flag)
#define DL698DL_RESET_FLAG(id,flag)    (pDl698DL_Channel[id].usState &= ~flag)
#define DL698DL_TEST_FLAG(id,flag)     (pDl698DL_Channel[id].usState & flag)

#define DL698DL_SET_NEXT_NUM(num)    ((num) > (4095) ? (num = 0) : (num++))
#define DL698DL_SET_SCOMFLAG(id,flag)  ( pDl698DL_Channel[id].stScom.ucComflag = flag )
#define DL698DL_TEST_SCOMFLAG(id,flag) ((pDl698DL_Channel[id].stScom.ucComflag == flag) ? true: false)

/*********************************************************************
* EXTERNAL VARIABLES
*/

/*********************************************************************
* EXTERNAL FUNCTIONS
*/

void fnDl698DL_Init(u8 channId);
void fnDl698DL_Process(u8 id);

void fnDl698_Process(u8 id);
void fnReport_Process(u8 id);
extern void fnDl698_Init(void);
extern ErrorStatus Dl698_FrameCheck(u8 ComPort, u8 *Src, u16 len, u16 *usDataLen);

#endif //_DL698DL_H_
