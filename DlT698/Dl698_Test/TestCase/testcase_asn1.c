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
#include "Dl698AL_def.h"
#include "Dl698_Memory.h"
#include "Dl698AL_asn1.h"

//u8 fnDL698AL_asn1_get_ObjCnt(u16* data_len,u8* buffer)
//u8 fnDL698AL_asn1_set_ObjCnt(u16 data_len,u8* buffer)
void get_objcnt_1(CuTest* tc)
{
    const u16 realLen = 1;
    u16 length;
    u8  TestData[] = {0x09, 1, 0x0a};
    CuAssertTrue(tc, fnDL698AL_asn1_get_ObjCnt(&length, TestData + 1) == 1);
    CuAssertTrue(tc, length == realLen);
}

void get_objcnt_127(CuTest* tc)
{
    const u16 realLen = 127;
    u16 length;
    u8  TestData[] = {0x09, 127, 0x0a};
    CuAssertTrue(tc, fnDL698AL_asn1_get_ObjCnt(&length, TestData + 1) == 1);
    CuAssertTrue(tc, length == realLen);
}

void get_objcnt_128(CuTest* tc)
{
    const u16 realLen = 128;
    u16 length;
    u8  TestData[] = {0x09, 0x81, 0x80, 0x0a};
    CuAssertTrue(tc, fnDL698AL_asn1_get_ObjCnt(&length, TestData + 1) == 2);
    CuAssertTrue(tc, length == realLen);
}

void get_objcnt_129(CuTest* tc)
{
    const u16 realLen = 129;
    u16 length;
    u8  TestData[] = {0x09, 0x81, 0x81, 0x0a};
    CuAssertTrue(tc, fnDL698AL_asn1_get_ObjCnt(&length, TestData + 1) == 2);
    CuAssertTrue(tc, length == realLen);
}

void get_objcnt_255(CuTest* tc)
{
    const u16 realLen = 255;
    u16 length;
    u8  TestData[] = {0x09, 0x81, 0xFF, 0x0a};
    CuAssertTrue(tc, fnDL698AL_asn1_get_ObjCnt(&length, TestData + 1) == 2);
    CuAssertTrue(tc, length == realLen);
}

void get_objcnt_256(CuTest* tc)
{
    const u16 realLen = 256;
    u16 length;
    u8  TestData[] = {0x09, 0x82, 0x01, 0x00, 0x0a};
    CuAssertTrue(tc, fnDL698AL_asn1_get_ObjCnt(&length, TestData + 1) == 3);
    CuAssertTrue(tc, length == realLen);
}

void get_objcnt_500(CuTest* tc)
{
    const u16 realLen = 500;
    u16 length;
    u8  TestData[] = {0x09, 0x82, 0x01, 0xF4, 0x0a};
    CuAssertTrue(tc, fnDL698AL_asn1_get_ObjCnt(&length, TestData + 1) == 3);
    CuAssertTrue(tc, length == realLen);
}

void fnDl698_asn1_set_ObjCnt_test1(CuTest* tc)
{
    const u16 realLen = 1;
    u16 length;
    //u8  TestData[] = {0x09,1,0x0a};
    u8  TestData[16];
    u8 lenLen;
    int i;
    Std_Memset(TestData, 0, sizeof(TestData));

    for (i = 0; i <= 500; i++)
    {
        lenLen = fnDL698AL_asn1_set_ObjCnt(realLen, TestData);

        CuAssertTrue(tc, fnDL698AL_asn1_get_ObjCnt(&length, TestData) == lenLen);
        CuAssertTrue(tc, length == realLen);
    }
}

//void fnDl698_asn1_check_timetag_test1(CuTest* tc);
//void fnDl698_asn1_getdata_len_test1(CuTest* tc)  //可以跟timetag一起测
void fnDl698_asn1_getdata_type_test1(CuTest* tc);
void fnDl698_asn1_build_unsigned_test1(CuTest* tc)
{
    const u16 realLen = 1;
    u16 length;
    //u8  TestData[] = {0x09,1,0x0a};
    u8  data = 0x01;
    u8  TestData[16];
    u8  ret[] = {DL698AL_DATA_TYPE_UINT8, 0x01};

    u8 lenLen;
    int i;
    Std_Memset(TestData, 0, sizeof(TestData));

    CuAssertTrue(tc, fnDl698_asn1_build_unsigned(TestData, data) == 2);
    CuAssertTrue(tc, !Std_Memcmp(ret, TestData, sizeof(ret)));
}

void fnDl698_asn1_build_long_test1(CuTest* tc)
{
    const u16 realLen = 1;
    u16 length;
    //u8  TestData[] = {0x09,1,0x0a};
    s16 data = -16;
    u8  TestData[16];
    u8  ret[] = {DL698AL_DATA_TYPE_INT16, (data >> 8) & 0xFF, data & 0xFF};

    u8 lenLen;
    int i;
    Std_Memset(TestData, 0, sizeof(TestData));

    CuAssertTrue(tc, fnDl698_asn1_build_unsigned(TestData, data) == 3);
    CuAssertTrue(tc, !Std_Memcmp(ret, TestData, sizeof(ret)));
}

void fnDl698_asn1_build_long_unsigned_test1(CuTest* tc)
{
    const u16 realLen = 1;
    u16 length;
    //u8  TestData[] = {0x09,1,0x0a};
    u16 data = 0x1234;
    u8  TestData[16];
    u8  ret[] = {DL698AL_DATA_TYPE_UINT16, (data >> 8) & 0xFF, data & 0xFF};

    u8 lenLen;
    int i;
    Std_Memset(TestData, 0, sizeof(TestData));

    CuAssertTrue(tc, fnDl698_asn1_build_long_unsigned(TestData, data) == 3);
    CuAssertTrue(tc, !Std_Memcmp(ret, TestData, sizeof(ret)));
}

void fnDl698_asn1_build_double_long_unsigned_test1(CuTest* tc)
{
    const u16 realLen = 1;
    u16 length;
    //u8  TestData[] = {0x09,1,0x0a};
    u32 data = 0x12345678;
    u8  TestData[16];
    u8  ret[] = {DL698AL_DATA_TYPE_UINT32, (data >> 24) & 0xFF, (data >> 16) & 0xFF, (data >> 8) & 0xFF, data & 0xFF};

    u8 lenLen;
    int i;
    Std_Memset(TestData, 0, sizeof(TestData));

    CuAssertTrue(tc, fnDl698_asn1_build_double_long_unsigned(TestData, data) == 5);
    CuAssertTrue(tc, !Std_Memcmp(ret, TestData, sizeof(ret)));
}

void fnDl698_asn1_build_datatime_s_test1(CuTest* tc)
{
    u8  TestData[16];
    u8 year = 16;
    u8 month = 1;
    u8 day = 20;
    u8 hour = 0;
    u8 minute = 0;
    u8 sec = 0;
    u8  ret[] = {0x1C, 0x07, 0xE0, 0x01, 0x14, 0x00, 0x00, 0x00 }; //2016-01-20 00：00：00

    Std_Memset(TestData, 0, sizeof(TestData));

    CuAssertTrue(tc, fnDl698_asn1_build_datatime_s(TestData, year, month, day, hour, minute, sec) == 8);
    CuAssertTrue(tc, !Std_Memcmp(ret, TestData, sizeof(ret)));
}

void fnDl698_asn1_build_data_test1(CuTest* tc)
{
    u8  TestData[16];
    u8 year = 16;
    u8 month = 1;
    u8 day = 20;
    u8 week = 0;
    u8  ret[] = {0x1A, 0x07, 0xE0, 0x01, 0x14, 0x00, 0x00, 0x00 }; //2016-01-20

    Std_Memset(TestData, 0, sizeof(TestData));

    CuAssertTrue(tc, fnDl698_asn1_build_date(TestData, year, month, day, week) == 6);
    CuAssertTrue(tc, !Std_Memcmp(ret, TestData, sizeof(ret)));
}

void fnDl698_asn1_build_octstring_test1(CuTest* tc)
{
    u8  TestData[16];
    u8  TestDataSrc[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    u8  ret[] = {0x09, 0x05, 0x01, 0x02, 0x03, 0x04, 0x05};

    Std_Memset(TestData, 0, sizeof(TestData));

    CuAssertTrue(tc, fnDl698_asn1_build_octstring(TestData, TestDataSrc, sizeof(TestDataSrc)) == sizeof(TestDataSrc) +2);
    CuAssertTrue(tc, !Std_Memcmp(ret, TestData, sizeof(ret)));
}

void fnDl698_asn1_build_visiblestring_test1(CuTest* tc)
{
    u8  TestData[16];
    u8  TestDataSrc[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    u8  ret[] = {0x0A, 0x05, 0x01, 0x02, 0x03, 0x04, 0x05};

    Std_Memset(TestData, 0, sizeof(TestData));

    CuAssertTrue(tc, fnDl698_asn1_build_visiblestring(TestData, TestDataSrc, sizeof(TestDataSrc)) == sizeof(TestDataSrc) +2);
    CuAssertTrue(tc, !Std_Memcmp(ret, TestData, sizeof(ret)));
}

void fnDl698_asn1_build_bitstring_test1(CuTest* tc)
{
    //BIT STRING 的BER编码规则是 ： T L V ,L表示V的字节数，在V里面的最前面要插入一个octet来表示最后一个字节填充的bit数，即没有用的bit数，
    //          //而填充0还是1由用户决定。
    u8  TestData[16];
    u8  TestDataSrc[] = {0x2D, 0xEB};   //10110111101011
    u8  TestDataLen = 13;
    u8  ret[] = {DL698AL_DATA_TYPE_BITSTRING, 0x03, 0x03, 0x2D, 0xEB};

    Std_Memset(TestData, 0, sizeof(TestData));

    CuAssertTrue(tc, fnDl698_asn1_build_bitstring(TestData, TestDataSrc, 13) == 5);
    CuAssertTrue(tc, !Std_Memcmp(ret, TestData, sizeof(ret)));
}

CuSuite *ASN1GetSuite(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, get_objcnt_1);
    SUITE_ADD_TEST(suite, get_objcnt_127);
    SUITE_ADD_TEST(suite, get_objcnt_128);
    SUITE_ADD_TEST(suite, get_objcnt_129);
    SUITE_ADD_TEST(suite, get_objcnt_255);
    SUITE_ADD_TEST(suite, get_objcnt_256);
    SUITE_ADD_TEST(suite, get_objcnt_500);

    SUITE_ADD_TEST(suite, fnDl698_asn1_set_ObjCnt_test1);

    SUITE_ADD_TEST(suite, fnDl698_asn1_build_unsigned_test1);
    SUITE_ADD_TEST(suite, fnDl698_asn1_build_long_unsigned_test1);
    SUITE_ADD_TEST(suite, fnDl698_asn1_build_double_long_unsigned_test1);
    SUITE_ADD_TEST(suite, fnDl698_asn1_build_datatime_s_test1);
    SUITE_ADD_TEST(suite, fnDl698_asn1_build_data_test1);
    SUITE_ADD_TEST(suite, fnDl698_asn1_build_octstring_test1);
    SUITE_ADD_TEST(suite, fnDl698_asn1_build_visiblestring_test1);

    SUITE_ADD_TEST(suite, fnDl698_asn1_build_bitstring_test1);

    return suite;
}
