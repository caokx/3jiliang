/********************************************************************
Filename:       DL698AL_Act.h
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
#ifndef _DL698AL_ACT_H_
#define _DL698AL_ACT_H_

/*********************************************************************
* INCLUDES
*/

/*********************************************************************
* MACROS
*/
#define  DL698AL_ACTTYPE_NORMAL            1    //ActRequestNormal
#define  DL698AL_ACTTYPE_NORMALLIST        2    //ActRequestNormalList
#define  DL698AL_ACTTHENGETNORMALLIST      3    //ActThenGetRequestNormalList

//
#define DL698_ACTRSP_ENCODE_HDR_PART  0
#define DL698_ACTRSP_ENCODE_LIST_PART 1
#define DL698_ACTRSP_ENCODE_LAST_PART 2
#define DL698_ACTRSP_ENCODE_DAR_PART  3

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
u8 fnDl698AL_ActReqHandle(u8 chan);

#endif //_DL698AL_ACT_H_
