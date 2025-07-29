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
    DL698DL_RX_ERR_INFO_FIELD_SIZE    = -1,  //�յ����Ϸ���Ϣ�򳤶�
    DL698DL_RX_ERR_RECV_NUM           = -2,  //�յ�N(R)�����Ч
    DL698DL_ERR_SA_ADDR               = -3,  //���Ϸ�SA��ַ
    DL698DL_ERR_CA_ADDR               = -4,  //���Ϸ�CA��ַ
    DL698DL_RX_I_INFO_CHEACK_ERR      = -5,  //apdu ��Ƭ֡ͷУ�鲻�Ϸ�
    DL698DL_ERR_HCS                   = -6,  //hcsУ�����
    DL698DL_ERR_FCS                   = -7,  //fcsУ�����
    DL698DL_ERR_DIR_PRM               = -8,   //֡���ͷ������
    DL698DL_ERR_AL_MEM_ALLOC          = -9   //�ϱ�ALʧ�ܣ�apdu buffer����ʧ��
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
    u8 ucUartType;  //ͨѶ���ͣ�645��698
    u8 ucUartId;
    //    u8 ucBaudRate;
    u8 ucComflag;
    u8 ucTimeout;
    u8 ucPktType;
    u16 usFramelen;
    u16 ucToStamp;     //֡�䳬ʱʱ��洢
    u16 ucToStamp2;    //֡�ڳ�ʱʱ��洢
} sDl698DL_ScomCtrl_TypeDef;

typedef struct
{
    u8  ubLen      : 4,
    ubLogic    : 2,
    ubAddrType : 2;
    u8  *pAddr;      //server��ַ��ǰ��2�ֽڱ�ʾ�߼�������ַ dyf ���÷���ע�ͣ�ǰ��1�ֽ�Ϊ��չ�߼���ַ�����ձ���ʱ����
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
    ubScramble: 1, //����
    ubResever : 1,
    ubSegment : 1,
    ubDirPrm  : 2;
} sDl698DL_CtrlInfo_TypeDef;

//������֡����Ҫ�洢����
typedef struct
{
    //������
    u16 usFrameLen;

    //������
    u8  ubCode    : 3,
    ubScramble: 1, //����
    ubResever : 1,
    ubSegment : 1,
    ubDirPrm  : 2;

    //Address��
    sServerAddr_TypeDef stSA;      //server��ַ��ǰ��2�ֽڱ�ʾ�߼�������ַ
    u8  ucCA;       //client��ַ,1�ֽ�

    //�û�������
    u16 usInfoLen;
    u8  *pInfo;
} sDl698DL_FrameInfo_TypeDef;

//���ջ���
typedef struct
{
    u16 usIndex;
    u16 usDataLen;    //��Ч�����ݳ��ȣ�������Ϊ0ʱ��ʾû����Ч����
    u8  pData[2048 + 21];//512+21
} sDl698DL_RxBuf_TypeDef;

//���ͻ���
typedef struct
{
    u16 usIndex;
    u16 usDataLen;//��Ч�����ݳ��ȣ�������Ϊ0ʱ��ʾû����Ч����
    u8  pData[2048 + 21];//512+21
} sDl698DL_TxBuf_TypeDef;

//����һ��data_linkͨ��
typedef struct
{
    //u8                 ucChannId;
    u16                 ucNumRecv;     //N(R)
    u16                 ucNumSend;     //N(S)
    u16                usState;
    sDl698DL_ScomCtrl_TypeDef    stScom;
    sDl698DL_Address_TypeDef     stAddr;
    sDl698DL_RxBuf_TypeDef       stRxBuf;       //�������ݻ���������
    sDl698DL_TxBuf_TypeDef       stTxBuf;       //�������ݻ���������
    sDl698DL_FrameInfo_TypeDef   stRxFrameInfo; //����������յ���֡����Ϣ
} sDl698DL_ChannelInfo_TypeDef;
/*********************************************************************
* MACROS
*/
#define DL698DL_DEFAULT_CLIENT_ADDR  0x00

/** @defgroup DL698DL_STATE_MASK
* @{
*/
#define DL698DL_STATE_MASK_LINKED             0x0001  //!< ��ʾͨ����������״̬
#define DL698DL_STATE_MASK_RESPOSE_ACK        0x0002  //!< ��ʾ��Ҫ��ӦACK֡
#define DL698DL_STATE_MASK_ACK_WAITING        0x0004  //!< ��ʾ����ACK֡������
#define DL698DL_STATE_MASK_RX_FRAGMENT        0x0008  //!< ��ʾͨ�������ڽ��շ�Ƭ֡״̬
#define DL698DL_STATE_MASK_TX_FRAGMENT        0x0010  //!< ��ʾͨ�������ڷ��ͷ�Ƭ֡״̬
#define DL698DL_STATE_MASK_RESEND             0x0020  //!< ��ʾ��Ҫִ���ش�

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
