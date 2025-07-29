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

//���ӽ��
#define      CONN_SUCCESS                  0      //�������ӽ���
#define      CONN_PASSWORD_FAULT           1      //�������,δ��Ȩ
#define      CONN_SYSDECRYP_FAULT          2      //�Գƽ��ܴ���
#define      CONN_ASYSDECRYP_FAULT         3      //�ǶԳƽ��ܴ���
#define      CONN_SIGN_FAULT               4      //ǩ������
#define      CONN_PROTOCOL_UNMATCH         5      //Э�鲻ƥ��
#define      CONN_ESAMEER_FAULT            6      //ESAMͨѶ����
#define      CONN_OTHERS_FAULT             255    //��������

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
