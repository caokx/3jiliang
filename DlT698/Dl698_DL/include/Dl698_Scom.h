/********************************************************************
Filename:       Dl698_Scom.h
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:         lin.xiaoman

Description:   data link layer data type definitions
**********************************************************************/
#ifndef _DL698_SCOM_H_
#define _DL698_SCOM_H_

/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"
/*********************************************************************
* TYPEDEFS
*/
typedef enum
{
    DL698_SCOMPK_EFLAG_IDLE          = 0,
    DL698_SCOMPK_EFLAG_698_LEN1      = 1,
    DL698_SCOMPK_EFLAG_698_LEN2      = 2,
    DL698_SCOMPK_EFLAG_645_ADDR      = 3,
    DL698_SCOMPK_EFLAG_645_CHK_START = 4,
    DL698_SCOMPK_EFLAG_645_CONTROL   = 5,
    DL698_SCOMPK_EFLAG_645_LEN       = 6,
    DL698_SCOMPK_EFLAG_RXBUSY        = 7,
    DL698_SCOMPK_EFLAG_RXFINISH      = 8,
    DL698_SCOMPK_EFLAG_RXEND         = 9,
    DL698_SCOMPK_EFLAG_RXTOTX        = 10,
    DL698_SCOMPK_EFLAG_TXBUSY        = 11,
    DL698_SCOMPK_EFLAG_TXFINISH      = 12,
    DL698_SCOMPK_EFLAG_INIT      = 13,
} eDl698DL_ScomFlag_TypeDef;

/*********************************************************************
* MACROS
*/
#define DL698_SCOMPK_DL645_ADDR_LEN         6
#define DL698_SCOMPK_LEADCODE        0xFE  //!< 前导码个数,实际发送个数DL698_SCOMPK_LEADCODE+1,其中1个在触发发送时已发送
#define DL698_LEADERCODE_LEN           3    //
#define DL698_SCOM_START_FLAG        0x68  //!< 起始标志符
#define DL698_SCOM_END_FLAG          0x16  //!< 结束标志符
#define DL698_SCOM_DELAY_BIT         33

#define DL698_FRAME_LEN_MASK                0x3FFF      //698帧长掩码
#define DL698_FRAME_LEN_MIN                 6           //698帧长最小长度2+1+1+2
#define DL698_FRAME_MAX_ADDRLEN             26          //698服务器地址最大长度

//baud rate macro defines
#define BAUD_RATE_300     0x01
#define BAUD_RATE_600     0x02
#define BAUD_RATE_1200    0x03
#define BAUD_RATE_2400    0x04
#define BAUD_RATE_4800    0x05
#define BAUD_RATE_9600    0x06
#define BAUD_RATE_19200   0x07
#define BAUD_RATE_38400   0x08
#define BAUD_RATE_57600   0x09
#define BAUD_RATE_115200  0x0A
/*********************************************************************
* EXTERNAL VARIABLES
*/

/*********************************************************************
* EXTERNAL FUNCTIONS
*/
void fnDl698Scom_Tx(u8 id);
void fnDl698Scom_Rx(u8 id, u8 data);
void fnDl698Scom_TimeOutCheck(u8 chanId);
void uart_data_recv(u8 chanId, u8 Comport, u8 uartid);
void uart_data_send(u8 chanId, u8 uartid);

#endif //_DL698_SCOM_H_
