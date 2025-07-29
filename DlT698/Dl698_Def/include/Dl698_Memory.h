/********************************************************************
Filename:       Dl698_Memory.h
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
#ifndef _DL698_MEMORY_H_
#define _DL698_MEMORY_H_

/*********************************************************************
* INCLUDES
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*********************************************************************
* MACROS
*/
#define DL698_BUFFER_DIAGEN  1          //BUFFER统计信息，调试用
#define DL698_BUFFER_MAXLEN  (10*1024)  //10k,支持4通道: 2路485,1路载波，1路红外情况
#define DL698_BUFFER_BLKSIZE 256         //256
#define DL698_BUFFER_BLKNUM  (DL698_BUFFER_MAXLEN/DL698_BUFFER_BLKSIZE)

/*********************************************************************
* CONSTANTS
*/

/*********************************************************************
* TYPEDEFS
*/

typedef enum
{
    DL698_BUFFER_STAT_IDLE = 0,
    DL698_BUFFER_STAT_IDLE_FIRST,
    DL698_BUFFER_STAT_BUSY,
    DL698_BUFFER_STAT_BUSY_FIRST,
} eDl698_BufferStat_Typedef;

typedef struct
{
    u8 size;    //block number
    u8 stat;    //
} sDl698_BufferInfo_Typedef;
/*********************************************************************
* GLOBAL VARIABLES
*/

/*********************************************************************
* EXTERNAL VARIABLES
*/

/*********************************************************************
* EXTERNAL FUNCTIONS
*/
void fnDl698_memcpy(void *dst, const void  *src, int len);
u8 fnDl698_memcmp(const void *src1, const void *src2, unsigned int len);
void fnDl698_memset(void *dest, u8 value, int len);
u8 fnDl698_memcmp_wildcard(const void *dst, const void *src, unsigned int len, u8 wildCard);
void fnDl698_Buffer_Init(void);
extern VOID *fnDl698_Buffer_Alloc(u16 BufLen);
extern VOID fnDl698_Buffer_Free(VOID* pBuf);
#endif //_DL698DEF_MEMORY_H_
