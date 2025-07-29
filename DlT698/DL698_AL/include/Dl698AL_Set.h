/********************************************************************
Filename:       Dl698AL_SET.h
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
#ifndef _DL698AL_SET_H_
#define _DL698AL_SET_H_

/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"

/*********************************************************************
* MACROS
*/
#define  DL698AL_SETTYPE_NORMAL            1    //SetRequestNormal
#define  DL698AL_SETTYPE_NORMALLIST        2    //SetRequestNormalList
#define  DL698AL_SETTHENGETNORMALLIST      3    //SetThenGetRequestNormalList

//
#define DL698_SETRSP_ENCODE_HDR_PART  0
#define DL698_SETRSP_ENCODE_LIST_PART 1
#define DL698_SETRSP_ENCODE_DATA_PART 2
#define DL698_SETRSP_ENCODE_LAST_PART 3
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
u8 fnDl698AL_SetReqHandle(u8 chan);
#endif //_DL698AL_SET_H_
