/********************************************************************
Filename:       Dl698_AL.h
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
#ifndef _DL698AL_GET_H_
#define _DL698AL_GET_H_

/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"

#define  DL698AL_GETTYPE_NORMAL          1    //GetRequestNormal
#define  DL698AL_GETTYPE_NORMALLIST      2    //GetRequestNormalList
#define  DL698AL_GETTYPE_RECORD          3    //GetRequestRecord
#define  DL698AL_GETTYPE_RECORDLIST      4    //GetRequestRecordList
#define  DL698AL_GETTYPE_NEXT            5    //GetRequestNext
#ifdef DL698_GST_TEST
#define  DL698AL_GETDI_TEST              0x0A //GetDI
#define  DL698AL_GETRECORDDI_TEST        0x0B //GetRecordDI
#define  DL698AL_GETOAD_TEST             0x0C //GetOAD
#endif

#define DL698_GETRSP_ENCODE_HDR_PART  0
#define DL698_GETRSP_ENCODE_LIST_PART 1
#define DL698_GETRSP_ENCODE_LAST_PART 2
#define DL698_GETRSP_ENCODE_BLOCK_HDR_PART 3
#define DL698_GETRSP_ENCODE_DAR_PART 4
#define DL698_GETRSP_ENCODE_SECERRDAR_PART 5

#define  DL698AL_GETRSPNEXTTYPE_DAR          0    //DAR
#define  DL698AL_GETRSPNEXTTYPE_NORMAL       1    //SEQUENCE OF A-ResultNormal
#define  DL698AL_GETRSPNEXTTYPE_RECORD       2    //SEQUENCE OF A-ResultRecord

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
u8 fnDl698AL_GetReqHandle(u8 chan);
u8 fnDl698AL_ThenGetReqHandle(u8 chan);

#endif //_DL698_AL_GET_H_
