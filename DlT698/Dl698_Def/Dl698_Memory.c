/**************************************************************************************************
  Filename:       Dl698_Memory.c
  Revised:        $Date: 2017-05-18 $
  Revision:       $Revision: V0.1 $
  Author:         lin.xiaoman

  Description:    DLT698 Def Memory file.
**************************************************************************************************/
/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"
#include "Dl698_Memory.h"
/*********************************************************************
* PUBLIC FUNCTIONS
*/

/*********************************************************************
 * @fn      fnDl698_memcpy
 *
 * @brief
 *
 *   Generic memory copy.
 *
 *   Note: This function differs from the standard memcpy(), since
 *         it returns the pointer to the next destination uint8. The
 *         standard memcpy() returns the original destination address.
 *
 * @param   dst - destination address
 * @param   src - source address
 * @param   len - number of bytes to copy
 *
 * @return  pointer to end of destination buffer
 */
void fnDl698_memcpy(void *dst, const void  *src, int len)
{
    unsigned char *pDst;
    const unsigned char  *pSrc;

    pSrc = src;
    pDst = dst;

    while (len--)
    {
        *pDst++ = *pSrc++;
    }
}

/*********************************************************************
 * @fn      fnDl698_memcmp
 *
 * @brief
 *
 *   Generic memory compare.
 *
 * @param   src1 - source 1 addrexx
 * @param   src2 - source 2 address
 * @param   len - number of bytes to compare
 *
 * @return  TRUE - same, FALSE - different
 */

u8 fnDl698_memcmp(const void *src1, const void *src2, unsigned int len)
{
    const u8 *pSrc1;
    const u8 *pSrc2;

    pSrc1 = src1;
    pSrc2 = src2;

    while (len--)
    {
        if (*pSrc1++ != *pSrc2++)
        {
            return false;
        }
    }
    return true;
}

/*********************************************************************
 * @fn      fnDl698_memset
 *
 * @brief
 *
 *   Set memory buffer to value.
 *
 * @param   dest - pointer to buffer
 * @param   value - what to set each uint8 of the message
 * @param   size - how big
 *
 * @return  pointer to destination buffer
 */
void fnDl698_memset(void *dest, u8 value, int len)
{
    Std_Memset(dest, value, len);
}

/*********************************************************************
 * @fn      fnDl698_memcmp_wildcard
 *
 * @brief
 *
 *   Generic memory compare.
 *
 * @param   src1 - source 1 addrexx
 * @param   src2 - source 2 address
 * @param   len - number of bytes to compare
 *
 * @return  TRUE - same, FALSE - different
 */

u8 fnDl698_memcmp_wildcard(const void *dst, const void *src, unsigned int len, u8 wildCard)
{
    const u8 *pDst;
    const u8 *pSrc;

    pDst = dst;
    pSrc = src;

    while (len--)
    {
        pDst++;
        pSrc++;
        if ((*pDst++ != *pSrc) && (*pSrc++ != wildCard))
        {
            return false;
        }
    }
    return true;
}

#if DL698_BUFFER_DIAGEN
s32 gDl698_BufferInfo_BusyBlk = 0;
s32 gDl698_BufferInfo_IdleBlk = DL698_BUFFER_BLKNUM;
#endif

sDl698_BufferInfo_Typedef gDl698_Buffer_InfoList[DL698_BUFFER_BLKNUM];// = {0};  //__no_init
u8 gDl698_Buffer[DL698_BUFFER_MAXLEN];  //__no_init
/*********************************************************************
* @fn      fnDl698_Buffer_Init
*
* @brief
*           APDU BUFFER初始化
*
* @param
*
* @return
*/
VOID fnDl698_Buffer_Init(VOID)
{
    fnDl698_memset(gDl698_Buffer_InfoList, 0, sizeof(gDl698_Buffer_InfoList));
    gDl698_Buffer_InfoList[0].size = DL698_BUFFER_BLKNUM;
    gDl698_Buffer_InfoList[0].stat = DL698_BUFFER_STAT_IDLE_FIRST;
    //gpDl698_Buffer_FreeList = &gDl698_Buffer_InfoList[0];
    #if DL698_BUFFER_DIAGEN
    gDl698_BufferInfo_BusyBlk = 0;
    gDl698_BufferInfo_IdleBlk = DL698_BUFFER_BLKNUM;
    #endif
    return ;
}

/*********************************************************************
* @fn      fnDl698_Buffer_Alloc
*
* @brief
*           BUFFER 资源申请
*
* @param
*
* @return
*/
VOID *fnDl698_Buffer_Alloc(u16 BufLen)
{
    u8 blknum = (BufLen + DL698_BUFFER_BLKSIZE - 1) / DL698_BUFFER_BLKSIZE;
    u8 blknumfree = 0;
    u32 i, j;
    VOID* pBufferAlloc = NULL;
    sDl698_BufferInfo_Typedef* pBufferInfo = &gDl698_Buffer_InfoList[0];
    for (i = 0; i < DL698_BUFFER_BLKNUM; i++)
    {
        if ((pBufferInfo->stat == DL698_BUFFER_STAT_IDLE_FIRST) &&
            (pBufferInfo->size >= blknum))
        {
            //找到可以分配的空间
            pBufferAlloc = (VOID*)(gDl698_Buffer + i * DL698_BUFFER_BLKSIZE);
            blknumfree = pBufferInfo->size - blknum;
            pBufferInfo->stat = DL698_BUFFER_STAT_BUSY_FIRST;
            pBufferInfo->size = blknum;
            pBufferInfo++;
            for (j = 1; j < blknum; j++)
            {
                pBufferInfo->stat = DL698_BUFFER_STAT_BUSY;
                pBufferInfo->size = 0;
                pBufferInfo++;
            }
            if (blknumfree != 0)
            {
                pBufferInfo->stat = DL698_BUFFER_STAT_IDLE_FIRST;
                pBufferInfo->size = blknumfree;
            }
            #if DL698_BUFFER_DIAGEN
            gDl698_BufferInfo_BusyBlk += blknum;
            gDl698_BufferInfo_IdleBlk -= blknum;
            #endif
            break;
        }
        pBufferInfo++;
    }
    if (i == DL698_BUFFER_BLKNUM) //分配失败
    {
        return NULL;
    }
    //fnDl698_al_debug("fnDl698 buffer alloc point 0x%x,size %d\n",pBufferAlloc,BufLen);

    return pBufferAlloc;
}

/*********************************************************************
* @fn      fnDl698_Buffer_Free
*
* @brief
*           APDU BUFFER 资源释放
*
* @param
*
* @return
*/
//指针必须指向分配BUFFER的首地址，或者在同一个BLOCK的地址范围内
VOID fnDl698_Buffer_Free(VOID* pBuf)
{
    u32 BufAddr = (u32)pBuf;
    //    u32 mask = DL698_BUFFER_BLKSIZE - 1;
    u8  blknumfree = 0;
    u32 offset = 0;
    u16 afterblk = 0;
    //    u32 base = 0;
    //    sDl698_BufferInfo_Typedef* pBufferInfo = NULL;
    s32 i;

    if (pBuf == NULL)
    {
        return;
    }
    //BufAddr &= ~mask;
    //--地址不是BLOCK的起始地址，则不做操作，直接返回  //地址向下取整，即指针指向同一个BLOCK之内都可以
    //if((BufAddr - (u32)gDl698_Buffer) % DL698_BUFFER_BLKSIZE != 0)
    //  return;
    offset = (BufAddr - (u32)gDl698_Buffer) / DL698_BUFFER_BLKSIZE;
    //pBufferInfo = &gDl698_Buffer_InfoList[offset];
    /*for(i=offset;i>=0;i--)
    {
        if(gDl698_Buffer_InfoList[i].stat == DL698_BUFFER_STAT_BUSY_FIRST)
        {
            break;
        }
    }
    if(i<0)
    {//BUFFER状态出错
    #if DL698_BUFFER_DIAGEN
        //printf
        base = 0;
    #endif
    }
    else
        base = i;*/
    blknumfree = gDl698_Buffer_InfoList[offset].size;
    #if DL698_BUFFER_DIAGEN
    gDl698_BufferInfo_BusyBlk -= blknumfree;
    gDl698_BufferInfo_IdleBlk += blknumfree;
    #endif
    //将该块BUFFER所有BLOCK的size和stat相应设置
    for (i = 1; i < blknumfree; i++)
    {
        gDl698_Buffer_InfoList[offset + i].size = 0;
        gDl698_Buffer_InfoList[offset + i].stat = DL698_BUFFER_STAT_IDLE;
    }
    //判断释放BLOCK的后面有没有需要接起来的
    afterblk = offset + blknumfree;
    if (afterblk < DL698_BUFFER_BLKNUM)
    {
        if (gDl698_Buffer_InfoList[afterblk].stat == DL698_BUFFER_STAT_IDLE_FIRST)
        {
            blknumfree += gDl698_Buffer_InfoList[afterblk].size;
            gDl698_Buffer_InfoList[afterblk].size = 0;
            gDl698_Buffer_InfoList[afterblk].stat = DL698_BUFFER_STAT_IDLE;
        }
    }

    //判断释放BLOCK的前面有没有需要接起来的
    //if(offset > 0)
    {
        for (i = offset - 1; i >= 0; i--)
        {
            if (gDl698_Buffer_InfoList[i].stat != DL698_BUFFER_STAT_IDLE)
            {
                break;
            }
        }
    }
    if ((i < 0) || (gDl698_Buffer_InfoList[i].stat != DL698_BUFFER_STAT_IDLE_FIRST))
    {
        gDl698_Buffer_InfoList[offset].size = blknumfree;
        gDl698_Buffer_InfoList[offset].stat = DL698_BUFFER_STAT_IDLE_FIRST;
    }
    else
    {
        gDl698_Buffer_InfoList[offset].size = 0;
        gDl698_Buffer_InfoList[offset].stat = DL698_BUFFER_STAT_IDLE;
        gDl698_Buffer_InfoList[i].size += blknumfree;
    }
    //fnDl698_al_debug("fnDl698 buffer free point 0x%x!\n",pBuf);

    return;
}
