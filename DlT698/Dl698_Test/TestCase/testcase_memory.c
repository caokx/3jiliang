/**************************************************************************************************
  Filename:       testcase_memory.c
  Revised:        $Date: 2017-05-18 $
  Revision:       $Revision: V0.1 $
  Author:         lin.xiaoman

  Description:    DLT698 Def Memory file.
**************************************************************************************************/
/*********************************************************************
* INCLUDES
*/
#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CuTest.h"

#include "Dl698_Type.h"
#include "Dl698_Memory.h"

extern sDl698_BufferInfo_Typedef gDl698_Buffer_InfoList[];
extern u8 gDl698_Buffer[];  //__no_init

/* BUFFER测试函数，测试场景包括：
*1. 全部分配最小BLOCK，分配完成之后多分配几个，然后按顺序释放；
*2. 全部分配最小BLOCK，分配完成之后多分配几个，然后按照0,2,4... 1,3,5..的顺序释放；
*3. 全部分配最大BLOCK，分配完成之后多分配几个，然后按顺序释放；
*4. 全部分配最大BLOCK，分配完成之后多分配几个，然后按照0,2,4... 1,3,5..的顺序释放；
*5. 分配随机大小BLOCK，分配完成之后多分配几个，然后按顺序释放；
*6. 分配随机大小BLOCK，分配完成之后多分配几个，然后按照0,2,4... 1,3,5..的顺序释放；
*/
void fnDl698_Buffer_test1(CuTest* tc)
{
    u8* pBuf = NULL;
    u32 i;
    char message[256];
    fnDl698_Buffer_Init();
    //test 1
    for (i = 0; i < DL698_BUFFER_BLKNUM; i++)
    {
        pBuf = (u8*)fnDl698_Buffer_Alloc(DL698_BUFFER_BLKSIZE);
        /*if(pBuf!=(gDl698_Buffer+i*DL698_BUFFER_BLKSIZE))
        {
            printf("fnDl698_Buffer_test1 phase 1 fail , i=%d\n",i);
        }*/
        sprintf(message, "fnDl698_Buffer_test1 phase 1 fail , i=%d\n", i);
        CuAssert(tc, message, pBuf == (gDl698_Buffer + i * DL698_BUFFER_BLKSIZE));
    }
    for (i = 0; i < 2; i++)
    {
        pBuf = (u8*)fnDl698_Buffer_Alloc(DL698_BUFFER_BLKSIZE);
        /*if(pBuf!=NULL)
            printf("fnDl698_Buffer_test1 phase 2 fail , i=%d\n",i);*/
        sprintf(message, "fnDl698_Buffer_test1 phase 2 fail , i=%d\n", i);
        CuAssert(tc, message, pBuf == NULL);
    }
    pBuf = gDl698_Buffer;
    for (i = 0; i < DL698_BUFFER_BLKNUM; i++)
    {
        fnDl698_Buffer_Free(pBuf);
        pBuf += DL698_BUFFER_BLKSIZE;
    }
    for (i = 0; i < DL698_BUFFER_BLKNUM; i++)
    {
        if (i == 0)
        {
            sprintf(message, "fnDl698_Buffer_test1 phase 3 fail , i=%d\n", i);
            CuAssert(tc, message, (gDl698_Buffer_InfoList[i].stat == DL698_BUFFER_STAT_IDLE_FIRST && gDl698_Buffer_InfoList[i].size == DL698_BUFFER_BLKNUM));
            /*if(gDl698_Buffer_InfoList[i].stat !=DL698_BUFFER_STAT_IDLE_FIRST ||  gDl698_Buffer_InfoList[i].size != DL698_BUFFER_BLKNUM)
            {
                printf("fnDl698_Buffer_test1 phase 3 fail , i=%d\n",i);
            }*/
        }
        else
        {
            sprintf(message, "fnDl698_Buffer_test1 phase 3 fail , i=%d\n", i);
            CuAssert(tc, message, (gDl698_Buffer_InfoList[i].stat == DL698_BUFFER_STAT_IDLE &&  gDl698_Buffer_InfoList[i].size == 0));
            /*if(gDl698_Buffer_InfoList[i].stat !=DL698_BUFFER_STAT_IDLE ||  gDl698_Buffer_InfoList[i].size != 0)
            {
                printf("fnDl698_Buffer_test1 phase 3 fail , i=%d\n",i);
            }*/
        }
    }
}

void fnDl698_Buffer_test2(CuTest* tc)
{
    u8* pBuf = NULL;
    u32 i;
    char message[256];

    fnDl698_Buffer_Init();
    //test 1
    for (i = 0; i < DL698_BUFFER_BLKNUM / 4; i++)
    {
        pBuf = (u8*)fnDl698_Buffer_Alloc(DL698_BUFFER_BLKSIZE * 4);
        sprintf(message, "fnDl698_Buffer_test2 phase 1 fail , i=%d\n", i);
        CuAssert(tc, message, (pBuf == (gDl698_Buffer + i * DL698_BUFFER_BLKSIZE * 4)));
        /*if(pBuf!=(gDl698_Buffer+i*DL698_BUFFER_BLKSIZE*4))
        {
            printf("fnDl698_Buffer_test2 phase 1 fail , i=%d\n",i);
        }*/
    }
    for (i = 0; i < 2; i++)
    {
        pBuf = (u8*)fnDl698_Buffer_Alloc(DL698_BUFFER_BLKSIZE * 4);
        sprintf(message, "fnDl698_Buffer_test2 phase 2 fail , i=%d\n", i);
        CuAssert(tc, message, (pBuf == NULL));
        /*if(pBuf!=NULL)
            printf("fnDl698_Buffer_test2 phase 2 fail , i=%d\n",i);*/
    }
    pBuf = gDl698_Buffer;
    for (i = 0; i < DL698_BUFFER_BLKNUM / 4; i++)
    {
        fnDl698_Buffer_Free(pBuf);
        pBuf += DL698_BUFFER_BLKSIZE * 4;
    }
    for (i = 0; i < DL698_BUFFER_BLKNUM; i++)
    {
        if (i == 0)
        {
            sprintf(message, "fnDl698_Buffer_test2 phase 3 fail , i=%d\n", i);
            CuAssert(tc, message, (gDl698_Buffer_InfoList[i].stat == DL698_BUFFER_STAT_IDLE_FIRST &&  gDl698_Buffer_InfoList[i].size == DL698_BUFFER_BLKNUM));
            /*if(gDl698_Buffer_InfoList[i].stat !=DL698_BUFFER_STAT_IDLE_FIRST ||  gDl698_Buffer_InfoList[i].size != DL698_BUFFER_BLKNUM)
            {
                printf("fnDl698_Buffer_test2 phase 3 fail , i=%d\n",i);
            }*/
        }
        else
        {
            sprintf(message, "fnDl698_Buffer_test2 phase 3 fail , i=%d\n", i);
            CuAssert(tc, message, (gDl698_Buffer_InfoList[i].stat == DL698_BUFFER_STAT_IDLE &&  gDl698_Buffer_InfoList[i].size == 0));
            /*if(gDl698_Buffer_InfoList[i].stat !=DL698_BUFFER_STAT_IDLE ||  gDl698_Buffer_InfoList[i].size != 0)
            {
                printf("fnDl698_Buffer_test2 phase 3 fail , i=%d\n",i);
            }*/
        }
    }

    //test 2
}

void fnDl698_Buffer_test3(CuTest* tc)
{
    u8* pBuf = NULL;
    u32 i;
    char message[256];
    fnDl698_Buffer_Init();
    //test 1
    for (i = 0; i < DL698_BUFFER_BLKNUM; i++)
    {
        pBuf = (u8*)fnDl698_Buffer_Alloc(DL698_BUFFER_BLKSIZE - i - 1);
        /*if(pBuf!=(gDl698_Buffer+i*DL698_BUFFER_BLKSIZE))
        {
            printf("fnDl698_Buffer_test1 phase 1 fail , i=%d\n",i);
        }*/
        sprintf(message, "fnDl698_Buffer_test3 phase 1 fail , i=%d\n", i);
        CuAssert(tc, message, pBuf == (gDl698_Buffer + i * DL698_BUFFER_BLKSIZE));
    }
    for (i = 0; i < 2; i++)
    {
        pBuf = (u8*)fnDl698_Buffer_Alloc(DL698_BUFFER_BLKSIZE - i - 1);
        /*if(pBuf!=NULL)
            printf("fnDl698_Buffer_test1 phase 2 fail , i=%d\n",i);*/
        sprintf(message, "fnDl698_Buffer_test3 phase 2 fail , i=%d\n", i);
        CuAssert(tc, message, pBuf == NULL);
    }
    pBuf = gDl698_Buffer;
    for (i = 0; i < DL698_BUFFER_BLKNUM; i++)
    {
        fnDl698_Buffer_Free(pBuf);
        pBuf += DL698_BUFFER_BLKSIZE;
    }
    for (i = 0; i < DL698_BUFFER_BLKNUM; i++)
    {
        if (i == 0)
        {
            sprintf(message, "fnDl698_Buffer_test3 phase 3 fail , i=%d\n", i);
            CuAssert(tc, message, (gDl698_Buffer_InfoList[i].stat == DL698_BUFFER_STAT_IDLE_FIRST && gDl698_Buffer_InfoList[i].size == DL698_BUFFER_BLKNUM));
            /*if(gDl698_Buffer_InfoList[i].stat !=DL698_BUFFER_STAT_IDLE_FIRST ||  gDl698_Buffer_InfoList[i].size != DL698_BUFFER_BLKNUM)
            {
                printf("fnDl698_Buffer_test1 phase 3 fail , i=%d\n",i);
            }*/
        }
        else
        {
            sprintf(message, "fnDl698_Buffer_test3 phase 3 fail , i=%d\n", i);
            CuAssert(tc, message, (gDl698_Buffer_InfoList[i].stat == DL698_BUFFER_STAT_IDLE &&  gDl698_Buffer_InfoList[i].size == 0));
            /*if(gDl698_Buffer_InfoList[i].stat !=DL698_BUFFER_STAT_IDLE ||  gDl698_Buffer_InfoList[i].size != 0)
            {
                printf("fnDl698_Buffer_test1 phase 3 fail , i=%d\n",i);
            }*/
        }
    }
}

CuSuite *MemoryGetSuite(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, fnDl698_Buffer_test1);
    SUITE_ADD_TEST(suite, fnDl698_Buffer_test2);
    SUITE_ADD_TEST(suite, fnDl698_Buffer_test3);

    return suite;
}