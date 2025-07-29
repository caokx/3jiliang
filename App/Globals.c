
#define  _GLOBALS
//#include <includes.h>
#include <App.h>
#include "ProDefine.h"
//============================
//
//============================
u8 BufTemp[BUFTEMP_MAXLEN];
sBufTemp_Info_Typedef gBufferTemp_InfoList[BUFTEMP_BLKNUM];

/*********************************************************************
* @fn
*
* @brief
*            BUFFER��ʼ��
*
* @param
*
* @return
*/
void fnBufTemp_Init(void)
{
    Std_Memset(gBufferTemp_InfoList, 0, sizeof(sBufTemp_Info_Typedef));
    gBufferTemp_InfoList[0].size = BUFTEMP_BLKNUM;
    gBufferTemp_InfoList[0].stat = BUFTEMP_STAT_IDLE_FIRST;

    return ;
}

/*********************************************************************
* @fn      fnBufTemp_Alloc
*
* @brief
*           BufTemp ��Դ����
*
* @param
*
* @return
*/
void *fnBufTemp_Alloc(u16 BufLen)
{
    u8 blknum = (BufLen + BUFTEMP_BLKSIZE - 1) / BUFTEMP_BLKSIZE;
    u8 blknumfree = 0;
    u32 i, j;
    VOID* pBufferAlloc = NULL;
    sBufTemp_Info_Typedef* pBufferInfo = &gBufferTemp_InfoList[0];

    for (i = 0 ; i < BUFTEMP_BLKNUM ; i++)
    {
        if ((pBufferInfo->stat == BUFTEMP_STAT_IDLE_FIRST) &&
            (pBufferInfo->size >= blknum))
        {
            //�ҵ����Է���Ŀռ�
            pBufferAlloc = (VOID*)(BufTemp + i * BUFTEMP_BLKSIZE);
            blknumfree = pBufferInfo->size - blknum;
            pBufferInfo->stat = BUFTEMP_STAT_BUSY_FIRST;
            pBufferInfo->size = blknum;
            pBufferInfo++;
            for (j = 1; j < blknum; j++)
            {
                pBufferInfo->stat = BUFTEMP_STAT_BUSY;
                pBufferInfo->size = 0;
                pBufferInfo++;
            }
            if (blknumfree != 0)
            {
                pBufferInfo->stat = BUFTEMP_STAT_IDLE_FIRST;
                pBufferInfo->size = blknumfree;
            }

            break;
        }
        pBufferInfo++;
    }
    if (i == BUFTEMP_BLKNUM) //����ʧ��
    {
        return NULL;
    }

    return pBufferAlloc;
}

/*********************************************************************
* @fn      fnBuffer_Free
*
* @brief
*            BUFFER ��Դ�ͷ�
*
* @param
*
* @return
*/
//ָ�����ָ�����BUFFER���׵�ַ��������ͬһ��BLOCK�ĵ�ַ��Χ��
void fnBufTemp_Free(void* pBuf)
{
    u32 BufAddr = (u32)pBuf;

    u8  blknumfree = 0;
    u32 offset = 0;
    u16 afterblk = 0;

    s32 i;

    if (pBuf == NULL)
    {
        return;
    }

    offset = (BufAddr - (u32)BufTemp) / BUFTEMP_BLKSIZE;

    blknumfree = gBufferTemp_InfoList[offset].size;

    //���ÿ�BUFFER����BLOCK��size��stat��Ӧ����
    for (i = 1; i < blknumfree; i++)
    {
        gBufferTemp_InfoList[offset + i].size = 0;
        gBufferTemp_InfoList[offset + i].stat = BUFTEMP_STAT_IDLE;
    }
    //�ж��ͷ�BLOCK�ĺ�����û����Ҫ��������
    afterblk = offset + blknumfree;
    if (afterblk < BUFTEMP_BLKNUM)
    {
        if (gBufferTemp_InfoList[afterblk].stat == BUFTEMP_STAT_IDLE_FIRST)
        {
            blknumfree += gBufferTemp_InfoList[afterblk].size;
            gBufferTemp_InfoList[afterblk].size = 0;
            gBufferTemp_InfoList[afterblk].stat = BUFTEMP_STAT_IDLE;
        }
    }

    //�ж��ͷ�BLOCK��ǰ����û����Ҫ��������
    //if(offset > 0)
    {
        for (i = offset - 1; i >= 0; i--)
        {
            if (gBufferTemp_InfoList[i].stat != BUFTEMP_STAT_IDLE)
            {
                break;
            }
        }
    }
    if ((i < 0) || (gBufferTemp_InfoList[i].stat != BUFTEMP_STAT_IDLE_FIRST))
    {
        gBufferTemp_InfoList[offset].size = blknumfree;
        gBufferTemp_InfoList[offset].stat = BUFTEMP_STAT_IDLE_FIRST;
    }
    else
    {
        gBufferTemp_InfoList[offset].size = 0;
        gBufferTemp_InfoList[offset].stat = BUFTEMP_STAT_IDLE;
        gBufferTemp_InfoList[i].size += blknumfree;
    }

    return;
}
