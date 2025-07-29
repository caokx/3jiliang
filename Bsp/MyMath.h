
#ifndef  _MYMATH_H
#define  _MYMATH_H

extern  u8  fnHexToBcd_u8(u8 Dat);
extern  u16 fnHexTo2Bcd_u8(u8 Dat);
extern  u16 fnHexToBcd_u16(u16 Dat);
extern  u32 fnHexToBcd_u32(u32 Dat);

extern  u8  fnBcdToHex_u8(u8 Dat);

extern  u16 fnBcdToHex_u16(u16 Dat);
extern  u32 fnBcdToHex_u32(u32 Dat);

extern  u8  fnBcdAdd_u8(u8 Augend, u8 Addend);
extern  u32 fnBcdAdd_u32(u32 Augend, u32 Addend);
extern  u32 fnBcdSub_u32(u32 Reduced, u32 Minuend);

extern  u8  fnSum(u8 *Dat, u16 Len);

extern  u8  fnJudge_Zero(void *Dat, u32 Len);
extern      u8  fnJudge_Value(void *Dat, u8 value, u8 Len);

extern s8       fnDFCmp_absDF09(sDF09 *Dat1, sDF09 *Dat2);

extern s8       fnDFCmp_DF09(sDF09 Dat1, sDF09 Dat2);
extern  s8  fnDFCmp_DF20(sDF20 *Dat1, sDF20 *Dat2);
extern  s8  fnDFCmp_DF15(sDF15 *Dat1, sDF15 *Dat2);
extern s8       fnDFCmp_DF31(sDF31 Dat1, sDF31 Dat2);

extern  sDF10   fnDFInc_DF10(sDF10 Dat);
extern  sDF27   fnDFInc_DF27(sDF27 Dat);

extern  void    fnDFGet_DF34(sDF34 *Dst, sDF01 *Src);
extern  sDF15   fnDFGet_DF15(sDF01 *Time);
extern sDF17    fnDFGet_DF17(sDF01 *Time);

extern  s32     fnTwoDateApart_DayCount(sDF20 *Date1, sDF20 *Date2);
extern  s32     fnTwoDateApart_MinuteCount(sDF15 *Date1, sDF15 *Date2);
extern  u8      fnWeek_Calculate(u16 Year, u8 Month, u8 Day);

extern  u8      fnCrc_Check(u8 byDir, u8 *pStartPos, u16 nCheckLen, u8 *Crc16);
extern  u8 fnBCD_Check(u8 *buf, u8 len);

extern sDF09    fnDFConver_Hex32ToDF09(s32 Dat);
extern sDF31    fnDFConver_Hex32ToDF31(u32 Dat);
extern sDF05    fnDFConver_Bcd16ToDF05(u16 Dat);
extern sDF07    fnDFConver_Bcd16ToDF07(u16 Dat);
extern sDF25    fnDFConver_Bcd32ToDF25(u32 Dat);
extern sDF31    fnDFConver_Bcd32ToDF31(u32 Dat);

extern u16      fnDFConver_Bcd16To16(s16 Dat);
extern u32      fnDFConver_Bcd32To32(s32 Dat);

extern u32      fnDFConver_DF10ToHex32(sDF10 *Dat);

extern sDF11    fnDFAdd_DF11(sDF11 Augend, sDF11 Addend);

extern u32 fn32mul32div(u32 DataA, u32 DataB, u16 DataC, u16 DataD);
extern  sDF09   fnDFConver_Bcd32ToDF09(u32 Dat);
extern  sDF26   fnDFConver_Bcd16ToDF26(u16 Dat);
extern  sDF33   fnDFConver_Bcd16ToDF33(u16 Dat);
extern  sDF18       fnDFGet_DF18(sDF01 *Time);
extern  double ConverDoubleData(double Data, u8 OldDot, u8 NewDot);
extern u8  fnCheckTime_DF15(sDF15 *Dat1);
extern u8  fnCheckTime_DF01(sDF01 *Dat1);
extern  void fnBcdSub_Bytes(u8 *Dst, u8 *Src, u8 Len);
extern  void fnBcdAdd_Bytes(u8 *Dst, u8 *Src, u8 Len);
extern  s8  fnDFCompData(u8 *Dat1, u8 *Dat2, u8 Len);
extern  u8   fnGetDay(u8 SMonth, u8 SYear);
extern  u8  fnGetBlurDay(u8 SMonth);
extern  u16 fnDayCount(sDate_time_s_TypeDef *pDate);
extern  void fnDayDec(sDate_time_s_TypeDef *Date1, u32 DecDay);
extern  void fnMinuteDec(sDate_time_s_TypeDef *Date1, u32 DecMinute);
extern  void fnMinAdd(sDate_time_s_TypeDef *Time, u32 IncMin);

extern u32 fn4BcdToHex_u32(u8 Dat0, u8 Dat1, u8 Dat2, u8 Dat3);
extern s32 fn4BcdToHex_s32(u8 Dat0, u8 Dat1, u8 Dat2, u8 Dat3);
extern u32 fn3BcdToHex_u32(u8 Dat0, u8 Dat1, u8 Dat2);
extern s32 fn3BcdToHex_s32(u8 Dat0, u8 Dat1, u8 Dat2);
extern u16 fn3BcdToHex_u16(u8 Dat0, u8 Dat1, u8 Dat2);
extern s16 fn3BcdToHex_s16(u8 Dat0, u8 Dat1, u8 Dat2, u8 sign);
extern void Std_MemRvsSelf(u8 *srcData, u16 len);

extern u16 Std_Lsb16DataGet(const u8* buf);
extern void Std_Lsb16DataSet(u8* buf, u16 data);
extern u16 Std_Msb16DataGet(const u8* p);
extern void Std_Msb16DataSet(u8* buf, u16 data);
extern u32 Std_Lsb32DataGet(const u8* buf);
extern void Std_Lsb32DataSet(u8* buf, u32 data);
extern u32 Std_Msb32DataGet(const u8* buf);
extern void Std_Msb32DataSet(u8* buf, u32 data);
extern ErrorStatus Std_Memcmp(const void* cmp1, const void* cmp2, u16 len);
extern void Std_Memcpy(void* dest, const void* src, u16 len);
extern void Std_SubMemcpy(UCHAR *dsc, UCHAR *src, UCHAR len);
extern void Std_Memset(void* dest, s8 data, u16 len);
extern void Std_MemRvs(u8 *dest, u8 *src, u16 len);
extern void Std_MemRvsSelf(u8 *srcData, u16 len);
extern void Std_BitRvsSelf(u8 *destData, u8 *srcData);
extern void Std_HexToAscii(char* Ascii, u8 hex);
extern u8 Std_AsciiToHex(u8* hex,  u8* Ascii);
extern u16 Std_HexStrToAsciiStr(char* Ascii, const u8* hex, u32 len);
extern u16 Std_AsciiStrToHexStr(u8* hex,  u8* Ascii, u16 len);

extern u32 fnDateTimeToMin(sDate_time_s_TypeDef *pDateTime);
extern u32 fnDateTimeToSec(sDate_time_s_TypeDef *pDateTime);
extern ErrorStatus fnCheck_Date_time_s(sDate_time_s_TypeDef *Ck);
extern void fnDayAdd(sDate_time_s_TypeDef *Time, u32 IncDay);
extern void fnMinAdd(sDate_time_s_TypeDef *Time, u32 IncMin);
#endif  //_MYMATH_H
