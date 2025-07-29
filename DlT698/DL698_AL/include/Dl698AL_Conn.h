/********************************************************************
Filename:       Dl698_AL.h
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
#ifndef Dl698AL_CONN_H_
#define Dl698AL_CONN_H_

/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"
#include "Dl698AL_def.h"

//连接结果
#define      CONN_SUCCESS                  0      //允许连接建立
#define      CONN_PASSWORD_FAULT           1      //密码错误,未授权
#define      CONN_SYSDECRYP_FAULT          2      //对称解密错误
#define      CONN_ASYSDECRYP_FAULT         3      //非对称解密错误
#define      CONN_SIGN_FAULT               4      //签名错误
#define      CONN_PROTOCOL_UNMATCH         5      //协议不匹配
#define      CONN_ESAMEER_FAULT            6      //ESAM通讯故障
#define      CONN_OTHERS_FAULT             255    //其他错误

/*********************************************************************
* MACROS
*/

/*********************************************************************
* CONSTANTS
*/

/*********************************************************************
* TYPEDEFS
*/

/*********************************************************************
* GLOBAL VARIABLES
*/

/*********************************************************************
* EXTERNAL VARIABLES
*/

/*********************************************************************
* EXTERNAL FUNCTIONS
*/
u16 fnDl698AL_ConnRes(u8 chan, sDl698AL_Nego_TypeDef* nego, u8 result);
u8 fnDl698AL_ConnHandle(u8 chan);
s8 fnDl698AL_RlsHandle(u8 chan);
s8 fnDl698AL_NotiRlsConnHandle(u8 chan);

#endif //Dl698AL_CONN_H_
