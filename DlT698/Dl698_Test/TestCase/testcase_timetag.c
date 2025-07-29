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
#include <time.h>

#include "CuTest.h"

#include "Dl698_Type.h"
#include "Dl698AL_def.h"

//u8 fnDL698AL_asn1_get_ObjCnt(u16* data_len,u8* buffer)
//u8 fnDL698AL_asn1_set_ObjCnt(u16 data_len,u8* buffer)
void fnDl698_mktime_test1(CuTest* tc)
{
    //
    struct tm curtime;  // tm_wday  and tm_yday are ignored ,and they will be setted
    time_t time1, time2;
    int year = 2001, m = 4, d = 4, hh = 1, mm = 1, ss = 1;
    curtime.tm_year = year - 1900;
    curtime.tm_mon  = m;
    curtime.tm_mday = d;
    curtime.tm_hour = hh;
    curtime.tm_min  = mm;
    curtime.tm_sec  = ss;
    curtime.tm_isdst = -1;
    curtime.tm_wday = 0;
    curtime.tm_yday = 0;

    time1 = mktime(&curtime);
    curtime.tm_sec = 10;
    time2 = mktime(&curtime);
}

CuSuite *TimeTagSuite(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, fnDl698_mktime_test1);

    return suite;
}

//从645拷贝过来的功能函数
u8 fnBcdToHex_u8(u8 Dat)
{
    u8 Result;
    u8 tmp = 0x0f;
    Result = (Dat & tmp) +
             ((Dat >> 4) & tmp) * 10;

    return (Result);
}

u16 fnBcdToHex_u16(u16 Dat)
{
    u16 Result;
    u16 tmp = 0x000f;
    Result = (Dat & tmp) +
             ((Dat >> 4) & tmp) * 10 +
             ((Dat >> 8) & tmp) * 100 +
             ((Dat >> 12) & tmp) * 1000;
    return (Result);
}
