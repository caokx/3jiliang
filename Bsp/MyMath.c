/**
  ******************************************************************************
  * @file    MyMath.c
  * @author  Renergy Application Team
  * @version V1.0.0
  * @date    2019.06.10
  * @brief   公用函数
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#define  _MYMATH_GLOBALS

#include <BSP.h>

/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Exported variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/

const u8 TAB_DayOfMonth[] = {0, 31, 29, 31, 30, 31, 30, 31,  31, 30, 31, 30, 31};

/*********************************************************************************************************
** Function name:   计算数据8位累加和
** Descriptions:
** input parameters:  Dat, 数据缓冲, len, 数据长度
** output parameters:
** Returned value:      8累加和值
*********************************************************************************************************/
u8  fnSum(u8 *Dat, u16 Len)
{
    u8  Sum;
    u16 i;

    for (Sum = 0, i = 0 ; i < Len ; i++)
    {
        Sum += Dat[i];
    }
    return (Sum);
}

double ConverDoubleData(double Data, u8 OldDot, u8 NewDot)
{
    u8 i;
    OldDot &= 0x7;
    NewDot &= 0x7;
    if (OldDot >= NewDot)
    {
        i = OldDot - NewDot;
        while (i--)
        {
            Data /= 10;
        }
    }
    else
    {
        i = NewDot - OldDot;
        while (i--)
        {
            Data *= 10;
        }
    }
    return Data;
}

//根据年月日计算星期几
//返回：1星期一、2星期二、3星期三、4星期四、5星期五、6星期六、0星期日
u8 fnWeek_Calculate(u16 Year, u8 Month, u8 Day)
{
    //Year = fnBcdToHex_u8(Year) + 2000;
    //Month = fnBcdToHex_u8(Month);
    //Day = fnBcdToHex_u8(Day);
    u8 Week;

    if (Month <= 2)
    {
        Year -= 1;
        Month += 12;
    }

    //Week = ((Day + 2 * Month + 3 * (Month + 1) / 5 + Year + Year / 4 - Year / 100 + Year / 400 + 1) % 7+1)%7;
    Week = (Day + 2 * Month + 3 * (Month + 1) / 5 + Year + Year / 4 - Year / 100 + Year / 400 + 1) % 7;
    return Week;
}

u8 fnHexToBcd_u8(u8 Dat)
{
    u8 Result = 0;

    Dat = Dat % 100;
    Result += (Dat / 10) * 0x10;
    Dat = Dat % 10;
    Result += Dat;

    return (Result);
}

u16 fnHexToBcd_u16(u16 Dat)
{
    u16 Result = 0;

    Dat = Dat % 10000;
    Result += (Dat / 1000) * 0x1000;
    Dat = Dat % 1000;
    Result += (Dat / 100) * 0x100;
    Dat = Dat % 100;
    Result += (Dat / 10) * 0x10;
    Dat = Dat % 10;
    Result += Dat;

    return (Result);
}

u16 fnHexTo2Bcd_u8(u8 Dat)
{
    u16 Result = 0;
    u8  Dat1 = 0;
    u8  Dat2 = 0;

    Dat1 = Dat / 100;
    Dat2 = ((Dat - Dat1 * 100) / 10) * 0x10;
    Dat2 = Dat2 + (Dat % 10);
    Result = Dat1 * 0x100 + Dat2;

    return (Result);
}

u32 fnHexToBcd_u32(u32 Dat)
{
    u32 result = 0;

    Dat = Dat % 100000000;
    result += (Dat / 10000000) * 0x10000000;
    Dat = Dat % 10000000;
    result += (Dat / 1000000) * 0x1000000;
    Dat = Dat % 1000000;
    result += (Dat / 100000) * 0x100000;
    Dat = Dat % 100000;
    result += (Dat / 10000) * 0x10000;
    Dat = Dat % 10000;
    result += (Dat / 1000) * 0x1000;
    Dat = Dat % 1000;
    result += (Dat / 100) * 0x100;
    Dat = Dat % 100;
    result += (Dat / 10) * 0x10;
    Dat = Dat % 10;
    result += Dat;

    return (result);
}

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

u32 fnBcdToHex_u32(u32 Dat)
{
    u32 Result;
    u32 tmp = 0x0f;
    Result = (Dat & tmp) +
             ((Dat >> 4) & tmp) * 10 +
             ((Dat >> 8) & tmp) * 100 +
             ((Dat >> 12) & tmp) * 1000 +
             ((Dat >> 16) & tmp) * 10000 +
             ((Dat >> 20) & tmp) * 100000 +
             ((Dat >> 24) & tmp) * 1000000 +
             ((Dat >> 28) & tmp) * 10000000;
    return (Result);
}

//=========================================
u8 fnBcdAdd_u8(u8 Augend, u8 Addend)
{
    u8 ResultTmp;
    u8 CBit = 0, i;
    u8 Result = 0;

    for (i = 0 ; i < 8 ; i += 4)
    {
        ResultTmp = ((Augend >> i) & 0x0f) + ((Addend >> i) & 0x0f) + CBit;
        if (ResultTmp > 9)
        {
            ResultTmp += 6;
        }
        CBit = ResultTmp >> 4;
        Result += (ResultTmp & 0x0f) << i;
    }

    return (Result);
}

u32 fnBcdSub_u32(u32 Reduced, u32 Minuend)
{
    u32 Result;

    Minuend = 0x9999999a - Minuend;
    Result = fnBcdAdd_u32(Reduced, Minuend);
    return (Result);
}

u8  fnJudge_Zero(void *Dat, u32 Len)
{
    u32 i;
    for (i = 0 ; i < Len ; i++)
    {
        if (((u8 *)Dat)[i] != 0)
        {
            return (FALSE);
        }
    }
    return (TRUE);
}

/*****************************************************************************
** Function name:fnJudge_Value
**
** Description:一组数据与一个固定的数据比较函数
**
** Parameters:Dat：待比较数组;value:被比较的固定数值
**
** Returned : TRUE=相等;FALSE=不相等
**
******************************************************************************/
u8  fnJudge_Value(void *Dat, u8 value, u8 Len)
{
    u8 i;
    for (i = 0 ; i < Len ; i++)
    {
        if (((u8 *)Dat)[i] != value)
        {
            return (FALSE);
        }
    }
    return (TRUE);
}

u32 fnBcdAdd_u32(u32 Augend, u32 Addend)
{
    u8 ResultTmp;
    u8 CBit = 0, i;
    u32 Result = 0;

    for (i = 0 ; i < 32 ; i += 4)
    {
        ResultTmp = ((Augend >> i) & 0x0f) + ((Addend >> i) & 0x0f) + CBit;
        if (ResultTmp > 9)
        {
            ResultTmp += 6;
        }
        CBit = ResultTmp >> 4;
        Result += ((u32)(ResultTmp & 0x0f) << i);
    }
    return (Result);
}

void fnBcdAdd_Bytes(u8 *Dst, u8 *Src, u8 Len)       // 多字节的BCD加法
{
    u8 ResultTmp, DataTmp;
    u8 CBit = 0, i;
    for (i = 0 ; i < Len ; i ++)
    {
        ResultTmp = (Dst[i] & 0x0f) + (Src[i] & 0x0f) + CBit;
        if (ResultTmp > 9)
        {
            ResultTmp += 6;
        }
        CBit = ResultTmp >> 4;
        DataTmp = ResultTmp & 0x0f;
        ResultTmp = ((Dst[i] >> 4) & 0x0f) + ((Src[i] >> 4) & 0x0f) + CBit;
        if (ResultTmp > 9)
        {
            ResultTmp += 6;
        }
        CBit = ResultTmp >> 4;
        DataTmp += (ResultTmp & 0x0f) << 4;
        Dst[i] = DataTmp;
    }
}

void fnBcdSub_Bytes(u8 *Dst, u8 *Src, u8 Len)       // 多字节的BCD减法
{
    u8 i;
    u8 DataTmp[8];

    for (i = 1 ; i < Len ; i ++)
    {
        DataTmp[i] = 0x99 - Src[i];
    }
    DataTmp[0] = 0x9a - Src[0];
    fnBcdAdd_Bytes(Dst, DataTmp, Len);
}

/*********************************************************************************************************
** Function name:    两数据比较
** Descriptions:
**
** input parameters:
** output parameters:
** Returned value:  1   Dat1 > Dat2
**                 -1   Dat1 < Dat2
**                  0   Dat1 = Dat2
*********************************************************************************************************/
s8  fnDFCompData(u8 *Dat1, u8 *Dat2, u8 Len)
{
    u8 i;
    for (i = Len; i > 0; i--)
    {
        if (Dat1[i - 1] > Dat2[i - 1])
        {
            return (1);
        }
        else if (Dat1[i - 1] < Dat2[i - 1])
        {
            return (-1);
        }
        else ;
    }
    return (0);
}

//==========================================
//数据+1
sDF10 fnDFInc_DF10(sDF10 Dat)
{
    u32 Tmp;

    Tmp = (u32)Dat.Dat0 +
          ((u32)Dat.Dat1 << 8) +
          ((u32)Dat.Dat2 << 16);
    Tmp = fnBcdAdd_u32(Tmp, 1);

    Dat.Dat0 = (u8)Tmp;
    Dat.Dat1 = (u8)(Tmp >> 8);
    Dat.Dat2 = (u8)(Tmp >> 16);
    return (Dat);
}

sDF27 fnDFInc_DF27(sDF27 Dat)
{
    Dat.Dat = fnBcdAdd_u32(Dat.Dat, 1);
    return (Dat);
}

sDF17 fnDFGet_DF17(sDF01 *Time)
{
    sDF17 TimeMark;

    TimeMark.Minute = Time->Minute;
    TimeMark.Hour = Time->Hour;
    TimeMark.Day = Time->Day;
    TimeMark.Month = Time->Month;

    return (TimeMark);
}

void fnDFGet_DF34(sDF34 *Dst, sDF01 *Src)
{
    Dst->Second = Src->Second;
    Dst->Minute = Src->Minute;
    Dst->Hour = Src->Hour;
    Dst->Day = Src->Day;
    Dst->Month = Src->Month;
    Dst->Year = Src->Year;
}

sDF15 fnDFGet_DF15(sDF01 *Time)
{
    sDF15 TimeMark;

    TimeMark.Minute = Time->Minute;
    TimeMark.Hour = Time->Hour;
    TimeMark.Day = Time->Day;
    TimeMark.Month = Time->Month;
    TimeMark.Year = Time->Year;
    return (TimeMark);
}

/*****************************************************************************
** Function name:fnMinAdd
**
** Description:将Time时间累加IncMin的分钟数
**
** Parameters:Time：时间  IncMin：累加分钟数
**
** Returned value:TIME+IncMin的时间
**
******************************************************************************/
void fnMinAdd(sDate_time_s_TypeDef *Time, u32 IncMin)
{
    u8  i;
    u8  SMinute, SHour, SMonth, SDay;
    u16 SYear;

    SMinute = Time->minute;
    SHour = Time->hour;
    SMonth = Time->month;
    SDay = Time->day;
    SYear = Time->year;
    while (IncMin)
    {
        i = (60 - SMinute);
        if (i > IncMin)
        {
            SMinute += IncMin;
            Time->minute = SMinute;
            Time->hour = SHour;
            Time->day = SDay;
            Time->month = SMonth;
            Time->year = SYear;
            IncMin = 0;
        }
        else
        {
            SMinute = 0;
            IncMin -= i;
            if (SHour >= 23)
            {
                SHour = 0;
                i = TAB_DayOfMonth[SMonth];

                if (SDay < i)
                {
                    SDay++;
                }
                else
                {
                    SDay = 1;
                    if (SMonth < 12)
                    {
                        SMonth++;
                    }
                    else
                    {
                        SMonth = 1;
                        SYear++;
                    }
                }
            }
            else
            {
                SHour++;
            }
        }
    }

    Time->minute = SMinute;
    Time->hour = SHour;
    Time->day = SDay;
    Time->month = SMonth;
    Time->year = SYear;
}

/*****************************************************************************
** Function name:fnDayAdd
**
** Description:将Time时间累加IncDay 天数
**
** Parameters:Time：时间  IncDay：累加天数
**
** Returned value:TIME+IncDay的时间
**
******************************************************************************/
void fnDayAdd(sDate_time_s_TypeDef *Time, u32 IncDay)
{
    u8  i;
    u8  SMonth, SDay;
    u16 SYear;

    SDay = Time->day;
    SMonth = Time->month;
    SYear = Time->year;

    while (IncDay)
    {
        i = TAB_DayOfMonth[SMonth] - SDay;
        if (i > IncDay)
        {
            SDay += IncDay;
            Time->day = SDay;
            Time->month = SMonth;
            Time->year = SYear;
            IncDay = 0;
        }
        else
        {
            IncDay -= i;
            SDay = 1;
            if (SMonth < 12)
            {
                SMonth++;
            }
            else
            {
                SMonth = 1;
                SYear++;
            }
        }
    }

    Time->day = SDay;
    Time->month = SMonth;
    Time->year = SYear;
}

sDF18 fnDFGet_DF18(sDF01 *Time)
{
    sDF18 TimeMark;

    TimeMark.Minute = Time->Minute;
    TimeMark.Hour = Time->Hour;
    TimeMark.Day = Time->Day;
    return (TimeMark);
}

s8  fnDFCmp_absDF09(sDF09 *Dat1, sDF09 *Dat2)   //绝对值比较
{
    if (Dat1->Dat2 > Dat2->Dat2)
    {
        return (1);
    }
    else if (Dat1->Dat2 < Dat2->Dat2)
    {
        return (-1);
    }
    else
    {
        if (Dat1->Dat1 > Dat2->Dat1)
        {
            return (1);
        }
        else if (Dat1->Dat1 < Dat2->Dat1)
        {
            return (-1);
        }
        else
        {
            if (Dat1->Dat0 > Dat2->Dat0)
            {
                return (1);
            }
            else if (Dat1->Dat0 < Dat2->Dat0)
            {
                return (-1);
            }
            else
            {
                return (0);
            }
        }
    }
}

s8  fnDFCmp_DF09(sDF09 Dat1, sDF09 Dat2)
{
    if (Dat1.Dat2 > Dat2.Dat2)
    {
        return (1);
    }
    else if (Dat1.Dat2 < Dat2.Dat2)
    {
        return (-1);
    }
    else
    {
        if (Dat1.Dat1 > Dat2.Dat1)
        {
            return (1);
        }
        else if (Dat1.Dat1 < Dat2.Dat1)
        {
            return (-1);
        }
        else
        {
            if (Dat1.Dat0 > Dat2.Dat0)
            {
                return (1);
            }
            else if (Dat1.Dat0 < Dat2.Dat0)
            {
                return (-1);
            }
            else
            {
                return (0);
            }
        }
    }
}

s8  fnDFCmp_DF15(sDF15 *Dat1, sDF15 *Dat2)
{
    u32 Tmp1, Tmp2;

    Tmp1 = ((u32)Dat1->Year << 24) +
           (((u32)Dat1->Month & 0x1f) << 19) +
           (((u32)Dat1->Day & 0x3f) << 13) +
           (((u32)Dat1->Hour & 0x3f) << 7) +
           (((u32)Dat1->Minute & 0x7f) << 0) ;

    Tmp2 = ((u32)Dat2->Year << 24) +
           (((u32)Dat2->Month & 0x1f) << 19) +
           (((u32)Dat2->Day & 0x3f) << 13) +
           (((u32)Dat2->Hour & 0x3f) << 7) +
           (((u32)Dat2->Minute & 0x7f) << 0) ;

    if (Tmp1 > Tmp2)
    {
        return (1);
    }
    else if (Tmp1 < Tmp2)
    {
        return (-1);
    }
    else
    {
        return (0);
    }
}

s8  fnDFCmp_DF20(sDF20 *Dat1, sDF20 *Dat2)
{
    u32 Tmp1, Tmp2;

    Tmp1 = ((u32)Dat1->Year << 16) +
           (((u32)Dat1->Month & 0x3f) << 8) +
           ((u32)Dat1->Day & 0x3f) ;
    Tmp2 = ((u32)Dat2->Year << 16) +
           (((u32)Dat2->Month & 0x3f) << 8) +
           ((u32)Dat2->Day & 0x3f) ;
    if (Tmp1 > Tmp2)
    {
        return (1);
    }
    else if (Tmp1 < Tmp2)
    {
        return (-1);
    }
    else
    {
        return (0);
    }
}

s8  fnDFCmp_DF31(sDF31 Dat1, sDF31 Dat2)
{
    u32 Tmp1 = 0, Tmp2 = 0;

    Std_Memcpy(&Tmp1, &Dat1, sizeof(sDF23));
    Std_Memcpy(&Tmp2, &Dat2, sizeof(sDF23));
    if (Tmp1 > Tmp2)
    {
        return (1);
    }
    else if (Tmp1 == Tmp2)
    {
        return (0);
    }
    else
    {
        return (-1);
    }
}

// 得到当前年、月得到当前月的天数
u8   fnGetDay(u8 SMonth, u8 SYear)
{
    u8  SDay = 0;
    SMonth = fnBcdToHex_u8(SMonth);
    SYear = fnBcdToHex_u8(SYear);
    switch (SMonth)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            SDay = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            SDay = 30;
            break;
        case 2:
            if ((SYear % 4) == 0)
            {
                SDay = 29;
            }
            else
            {
                SDay = 28;
            }
            break;
        default:
            break;
    }
    SDay = fnHexToBcd_u8(SDay);
    return (SDay);
}

// 得到当前月得到当前月的模糊天数
u8  fnGetBlurDay(u8 SMonth)
{
    u8  SDay = 0;
    switch (SMonth)
    {
        case 0x01:
        case 0x03:
        case 0x05:
        case 0x07:
        case 0x08:
        case 0x10:
        case 0x12:
            SDay = 0x31;
            break;
        case 0x04:
        case 0x06:
        case 0x09:
        case 0x11:
            SDay = 0x30;
            break;
        case 2:
            SDay = 0x29;
            break;
        default:
            break;
    }
    return (SDay);
}

void fnDayDec(sDate_time_s_TypeDef *Date1, u32 DecDay)
{
    u8  SDay, SMonth ;
    u16 SYear;

    SDay = Date1->day;

    while (DecDay)
    {
        if (SDay > DecDay)
        {
            SDay -= DecDay;
            Date1->day = SDay;
            DecDay = 0;
        }
        else
        {
            DecDay -= SDay;

            SMonth = Date1->month;
            SYear = Date1->year;
            if (SMonth > 1)
            {
                SMonth--;
            }
            else
            {
                if (SYear > 1)
                {
                    SYear--;
                }
                else
                {
                    SYear = 2001;
                }
                SMonth = 12;
            }

            SDay = TAB_DayOfMonth[SMonth];

            Date1->month = SMonth;
            Date1->year = SYear;
            Date1->day = SDay;
        }
    }
}

void fnMinuteDec(sDate_time_s_TypeDef *Date1, u32 DecMinute)
{
    u32  SMinute, SHour, DecHour, DecDay;

    SMinute = (u32)Date1->minute;
    SHour = (u32)Date1->hour;

    if (SMinute >= DecMinute)
    {
        SMinute -= DecMinute;
        DecMinute = 0;
        Date1->minute = (u8)SMinute;
    }
    else
    {
        if (DecMinute > 60)
        {
            SMinute = 60 - DecMinute % 60;
            DecHour = DecMinute / 60;
        }
        else
        {
            SMinute = 60 - DecMinute;
            DecHour = 1;
        }

        if (SHour >= DecHour)
        {
            SHour -= DecHour;
        }
        else
        {
            SHour = 24 - DecHour % 24;

            DecDay = SHour / 24 + 1;

            fnDayDec(Date1, DecDay);
        }
    }

    Date1->minute = (u8)SMinute;
    Date1->hour = (u8)SHour;
}

sDF09 fnDFConver_Hex32ToDF09(s32 Dat)
{
    sDF09   Result;
    Std_Memset(&Result, 0, sizeof(sDF09));
    if (Dat < 0)
    {
        Result.S = 1;
    }
    else
    {
        Result.S = 0;
    }

    Dat = labs(Dat) % 800000;
    Dat = fnHexToBcd_u32(Dat);

    Result.Dat0 = Dat;
    Result.Dat1 = Dat >> 8;
    Result.Dat2 = Dat >> 16;
    return (Result);
}

sDF31 fnDFConver_Hex32ToDF31(u32 Dat)
{
    sDF31   Result;

    Dat = fnHexToBcd_u32(Dat);

    Result.Dat0 = Dat;
    Result.Dat1 = Dat >> 8;
    Result.Dat2 = Dat >> 16;

    return (Result);
}

sDF05 fnDFConver_Bcd16ToDF05(u16 Dat)
{
    sDF05 Result;
    if (Dat & 0x8000)
    {
        Result.S = 1;
    }
    else
    {
        Result.S = 0;
    }
    Result.Dat = Dat & 0x7fff;
    return (Result);
}

u16 fnDFConver_Bcd16To16(s16 Dat)
{
    u16 Result;
    Result = abs(Dat) % 8000;
    Result = fnHexToBcd_u16(Result);
    if (Dat < 0)
    {
        Result |= 0x8000;
    }
    else
    {
        Result &= 0x7fff;
    }
    return (Result);
}

u32 fnDFConver_Bcd32To32(s32 Dat)
{
    u32 Result;
    Result = labs(Dat) % 80000000;
    Result = fnHexToBcd_u32(Result);
    if (Dat < 0)
    {
        Result |= 0x80000000;
    }
    else
    {
        Result &= 0x7fffffff;
    }
    return (Result);
}

sDF07 fnDFConver_Bcd16ToDF07(u16 Dat)
{
    sDF07 Result;
    Result.Dat = Dat;
    return (Result);
}

sDF25 fnDFConver_Bcd32ToDF25(u32 Dat)
{
    sDF25 Result;

    if (Dat & 0x80000000)
    {
        Result.S = 1;
    }
    else
    {
        Result.S = 0;
    }

    Dat &= 0x7ffffff;

    Result.Dat0 = Dat >> 4;
    Result.Dat1 = Dat >> 12;
    Result.Dat2 = (Dat >> 20) & 0x7f;
    return (Result);
}

sDF26   fnDFConver_Bcd16ToDF26(u16 Dat)
{
    sDF26 Result;
    Result.Dat = Dat;
    return (Result);
}

sDF33   fnDFConver_Bcd16ToDF33(u16 Dat)
{
    sDF33 Result;
    Result.Dat = Dat;
    return (Result);
}

sDF31 fnDFConver_Bcd32ToDF31(u32 Dat)
{
    sDF31 Result;

    Result.Dat0 = Dat;
    Result.Dat1 = Dat >> 8;
    Result.Dat2 = Dat >> 16;

    return (Result);
}

sDF09   fnDFConver_Bcd32ToDF09(u32 Dat)
{
    sDF09 Result;

    if (Dat & 0x80000000)
    {
        Result.S = 1;
    }
    else
    {
        Result.S = 0;
    }

    Dat &= 0x7fffff;

    Result.Dat0 = Dat;
    Result.Dat1 = Dat >> 8;
    Result.Dat2 = Dat >> 16;
    return (Result);
}

u32 fnDFConver_DF10ToHex32(sDF10 *Dat)
{
    u32 Result;

    Result = (u32)Dat->Dat0 +
             ((u32)Dat->Dat1 << 8) +
             ((u32)Dat->Dat2 << 16);
    Result = fnBcdToHex_u32(Result);

    return (Result);
}

sDF11 fnDFAdd_DF11(sDF11 Augend, sDF11 Addend)
{
    sDF11 Result;

    Result.Dat = fnBcdAdd_u32(Augend.Dat, Addend.Dat);

    return (Result);
}

//函数:获取两个日期间的天数
//参数:Date1、Date2日期(sDF20)
//返回:天数(Date1 > Date2 返回正、否则返回负)
s32 fnTwoDateApart_DayCount(sDF20 *Date1, sDF20 *Date2)
{
    s32 Total;
    u16 i, SYear, EYear;
    u8 SMonth, EMonth;

    sDF20 *pSDate, *pEDate;

    if (fnDFCmp_DF20((sDF20 *)Date1, (sDF20 *)Date2) > 0)
    {
        pSDate = Date2;
        pEDate = Date1;
    }
    else
    {
        pSDate = Date1;
        pEDate = Date2;
    }

    SYear = 2000 + fnBcdToHex_u8(pSDate->Year);
    EYear = 2000 + fnBcdToHex_u8(pEDate->Year);

    for (Total = 0, i = SYear ; i < EYear ; i++)
    {
        Total += 365;
        if ((i % 4) == 0)
        {
            Total += 1;
        }
    }

    EMonth = fnBcdToHex_u8(pEDate->Month & 0x1f);
    for (i = 1 ; i < EMonth ; i++)
    {
        switch (i)
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                Total += 31;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                Total += 30;
                break;
            case 2:
                if ((EYear % 4) == 0)
                {
                    Total += 29;
                }
                else
                {
                    Total += 28;
                }
                break;
            default:
                break;
        }
    }
    Total += fnBcdToHex_u8(pEDate->Day & 0x3f);

    SMonth = fnBcdToHex_u8(pSDate->Month & 0x1f);
    for (i = 1 ; i < SMonth ; i++)
    {
        switch (i)
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                Total -= 31;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                Total -= 30;
                break;
            case 2:
                if ((SYear % 4) == 0)
                {
                    Total -= 29;
                }
                else
                {
                    Total -= 28;
                }
                break;

            default:
                break;
        }
    }
    Total -= fnBcdToHex_u8(pSDate->Day & 0x3f);

    if (fnDFCmp_DF20((sDF20 *)Date1, (sDF20 *)Date2) < 0)
    {
        Total = -Total;
    }
    return (Total);
}

//函数:获取两个日期间的分钟数
//参数:Date1、Date2日期(sDF15)
//返回:分钟数(Date1 > Date2 返回正、否则返回负)
s32 fnTwoDateApart_MinuteCount(sDF15 *Date1, sDF15 *Date2)
{
    s32 Total;

    Total = fnTwoDateApart_DayCount((sDF20 *)&Date1->Day, (sDF20 *)&Date2->Day);

    Total = Total * 24 * 60 +
            (fnBcdToHex_u8(Date1->Hour & 0x3f) * 60 + fnBcdToHex_u8(Date1->Minute & 0x7f)) -
            (fnBcdToHex_u8(Date2->Hour & 0x3f) * 60 + fnBcdToHex_u8(Date2->Minute & 0x7f));

    return (Total);
}

//--------------------
//函数:获取日期间的天数
//参数:
//返回:
const u16 TAB_MonthBeginDay[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
u16 fnDayCount(sDate_time_s_TypeDef *pDate)
{
    u16 Total ;
    sDate_time_s_TypeDef  Dat;

    Dat = *pDate;

    //----一2000年1月1日为基准---------------
    Dat.year = Dat.year - 2000;
    if ((Dat.year % 4) == 0)
    {
        if (Dat.month >= 2)
        {
            Dat.day++;
        }
    }
    else
    {
        Dat.day++;    //非闰年加上2000年闰月多出来的一天
    }

    Total = Dat.year * 365 + TAB_MonthBeginDay[Dat.month - 1] + (Dat.day - 1) + Dat.year / 4 ; // pDate.year/4 是加上过去的整4年里闰年的一天

    return (Total);
}

u16 fnMinCount(u8 Minute, u8 Hour)
{
    u16 Total;

    Total = Hour * 60 + Minute;

    return (Total);
}

//函数:获取日期的分钟数
//参数:
//返回: 日期的总分钟数(min)
u32 fnDateTimeToMin(sDate_time_s_TypeDef *pDateTime)
{
    u16 TotalA, TotalB;
    u32 Total;

    TotalA = fnDayCount(pDateTime);
    TotalB = fnMinCount(pDateTime->minute, pDateTime->hour);

    Total = TotalA * 24 * 60 + TotalB;

    return (Total);
}

//函数:获取日期的秒数
//参数:
//返回: 日期的总秒数(sec)
u32 fnDateTimeToSec(sDate_time_s_TypeDef *pDateTime)
{
    u32 TotalA, Total;

    TotalA = fnDateTimeToMin(pDateTime);

    Total = TotalA * 60 + pDateTime->second;

    return (Total);
}

//-----------------------------------
//--------------------------------------------------------------------------------
// Table of CRC values for High–order byte
const u8 auchCRCHi[] =
{
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40
} ;
// Table of CRC values for low–order byte
const u8 auchCRCLo[] =
{
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
    0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
    0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
    0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
    0x40
};

u16 fnCRC16(unsigned char * puchMsg, unsigned short  usDataLen)  // The function returns the CRC as a unsigned short type
{
    unsigned char uchCRCHi = 0xFF ; // high byte of CRC initialized
    unsigned char uchCRCLo = 0xFF ; // low byte of CRC initialized
    unsigned uIndex ;               // will index into CRC lookup table
    while (usDataLen--)             // pass through message buffer
    {
        uIndex = uchCRCLo ^ *puchMsg++ ; // calculate the CRC
        uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex] ;
        uchCRCHi = auchCRCLo[uIndex] ;
    }
    return ((u16)uchCRCHi << 8 | uchCRCLo) ;
}

//函数功能：计算或进行CRC-16比较
//入口参数：byDir：校验方向，=0表示计算校验值，=1表示校验检查
//          pStartPos：校验开始位置
//          nCheckLen：需要校验的字节长度
//          Crc16：byDir=0时,作校验值返回;byDir=1时,做要检查的校验值(参数)
//出口参数：若bytDir=0，则返回无效
//          若bytDir=1，则校验正确返回0，否则返回1
u8 fnCrc_Check(u8 byDir, u8 *pStartPos, u16 nCheckLen, u8 *Crc16)
{
    u16 Wcrc_data;

    Wcrc_data = fnCRC16(pStartPos, nCheckLen);
    if (!byDir)
    {
        Crc16[0] = (u8)Wcrc_data;
        Crc16[1] = Wcrc_data >> 8;
        return (0x00);
    }
    if ((((u16)Crc16[1] << 8) + Crc16[0]) != Wcrc_data)
    {
        return (0x01);
    }
    else
    {
        return (0x00);
    }
}

u8  fnCheckTime_DF15(sDF15 *Dat1)
{
    if ((Dat1->Year >= 0xa0) || ((Dat1->Year & 0x0f) >= 0x0a))
    {
        return (1);
    }
    if ((Dat1->Month >= 0x13) || (Dat1->Month == 0x00) || ((Dat1->Month & 0x0f) >= 0x0a))
    {
        return (1);
    }
    if ((Dat1->Day >= 0x32) || (Dat1->Day == 0x00) || ((Dat1->Day & 0x0f) >= 0x0a))
    {
        return (1);
    }
    if ((Dat1->Hour >= 0x24) || ((Dat1->Hour & 0x0f) >= 0x0a))
    {
        return (1);
    }
    if ((Dat1->Minute >= 0x5a) || ((Dat1->Minute & 0x0f) >= 0x0a))
    {
        return (1);
    }
    return (0);
}

u8  fnCheckTime_DF01(sDF01 *Dat1)
{
    if ((Dat1->Year >= 0xa0) || ((Dat1->Year & 0x0f) >= 0x0a))
    {
        return (1);
    }
    if ((Dat1->Month >= 0x13) || (Dat1->Month == 0x00) || ((Dat1->Month & 0x0f) >= 0x0a))
    {
        return (1);
    }
    if (Dat1->Day >= 0x32 || (Dat1->Day == 0x00) || ((Dat1->Day & 0x0f) >= 0x0a))
    {
        return (1);
    }
    if (Dat1->Week >= 0x07)
    {
        return (1);
    }
    if (Dat1->Hour >= 0x24 || ((Dat1->Hour & 0x0f) >= 0x0a))
    {
        return (1);
    }
    if (Dat1->Minute >= 0x5a || ((Dat1->Minute & 0x0f) >= 0x0a))
    {
        return (1);
    }
    if (Dat1->Second >= 0x5a || ((Dat1->Second & 0x0f) >= 0x0a))
    {
        return (1);
    }
    return (0);
}

/*********************************************************************************************************
** Function name:
** Descriptions:

** input parameters:
** output parameters:
** Returned value: true=BCD,    false = no BCD
*********************************************************************************************************/
u8 fnBCD_Check(u8 *buf, u8 len)
{
    u8 i;
    for (i = 0; i < len; i++)
    {
        if (((buf[i] & 0xF0) > 0x90) || ((buf[i] & 0x0F) > 0x09))
        {
            return false;
        }
    }
    return true;
}

u32 fn32mul32div(u32 DataA, u32 DataB, u16 DataC, u16 DataD)
{
    sDF64 Temp ;
    sDF64 Temp1;
    Std_Memset(&Temp, 0, sizeof(u64));
    Temp.DF01.Dat0 = Temp.DF01.Dat0 + (((u32)(u16)DataA) * (u16)DataB) ;

    Temp.DF02.Dat1 = Temp.DF02.Dat1 + (((u32)(DataA >> 16)) * (u16)DataB) ;

    Temp.DF02.Dat1 = Temp.DF02.Dat1 + (((u32)(DataB >> 16)) * (u16)DataA) ;

    Temp.DF01.Dat1 = Temp.DF01.Dat1 + ((u32)DataA >> 16) * (DataB >> 16) ;

    Std_Memset(&Temp1, 0, sizeof(sDF64));
    if (!(DataC && DataD))
    {
        return 0x0000;
    }

    Temp1.DF01.Dat1 = Temp.DF01.Dat1 / DataC;

    Temp1.DF03.Dat1 = ((((u32)(Temp.DF01.Dat1 % DataC)) << 16) + (Temp.DF03.Dat1)) / DataC;

    Temp1.DF03.Dat0 = (((u32)((((u32)(Temp.DF01.Dat1 % DataC)) << 16) + (Temp.DF03.Dat1)) % DataC << 16) + (Temp.DF03.Dat0)) / DataC;

    Std_Memset(&Temp, 0, sizeof(sDF64));

    Temp.DF01.Dat1 = Temp1.DF01.Dat1 / DataD;

    Temp.DF03.Dat1 = ((((u32)(Temp1.DF01.Dat1 % DataD)) << 16) + (Temp1.DF03.Dat1)) / DataD;

    Temp.DF03.Dat0 = (((u32)((((u32)(Temp1.DF01.Dat1 % DataD)) << 16) + (Temp1.DF03.Dat1)) % DataD << 16) + (Temp1.DF03.Dat0)) / DataD;

    return Temp.DF01.Dat0;
}

u32 fn4BcdToHex_u32(u8 Dat0, u8 Dat1, u8 Dat2, u8 Dat3)
{
    u32 Result = 0;
    u8 tmp = 0x0f;
    Result = (Dat0 & tmp) +
             ((Dat0 >> 4) & tmp) * 10 +
             ((Dat1) & tmp) * 100 +
             ((Dat1 >> 4) & tmp) * 1000 +
             ((Dat2) & tmp) * 10000 +
             ((Dat2 >> 4) & tmp) * 100000 +
             ((Dat3) & tmp) * 1000000 +
             ((Dat3 >> 4) & tmp) * 10000000;
    return (Result);
}

s32 fn4BcdToHex_s32(u8 Dat0, u8 Dat1, u8 Dat2, u8 Dat3)
{
    s32 Result;
    u8 tmp = 0x0f;
    u8 sign = Dat3 >> 7 & 0x01;
    Dat3 = Dat3 & 0x7F;
    Result = (Dat0 & tmp) +
             ((Dat0 >> 4) & tmp) * 10 +
             ((Dat1) & tmp) * 100 +
             ((Dat1 >> 4) & tmp) * 1000 +
             ((Dat2) & tmp) * 10000 +
             ((Dat2 >> 4) & tmp) * 100000 +
             ((Dat3) & tmp) * 1000000 +
             ((Dat3 >> 4) & tmp) * 10000000;
    Result = ((Result & 0x7FFFFFFF) | (sign << 31)); //增加符合位
    return (Result);
}

s32 fn3BcdToHex_s32(u8 Dat0, u8 Dat1, u8 Dat2)
{
    s32 Result = 0;
    u8 tmp = 0x0f;
    u8 sign = Dat2 >> 7 & 0x01;
    Dat2 = Dat2 & 0x7F;
    Result = (Dat0 & tmp) +
             ((Dat0 >> 4) & tmp) * 10 +
             ((Dat1) & tmp) * 100 +
             ((Dat1 >> 4) & tmp) * 1000 +
             ((Dat2) & tmp) * 10000 +
             ((Dat2 >> 4) & tmp) * 100000;
    Result = ((Result & 0x7FFFFFFF) | (sign << 31)); //增加符合位
    return (Result);
}

u32 fn3BcdToHex_u32(u8 Dat0, u8 Dat1, u8 Dat2)
{
    u32 Result = 0;
    u32 tmp = 0x0f;
    Result = (Dat0 & tmp) +
             ((Dat0 >> 4) & tmp) * 10 +
             ((Dat1) & tmp) * 100 +
             ((Dat1 >> 4) & tmp) * 1000 +
             ((Dat2) & tmp) * 10000 +
             ((Dat2 >> 4) & tmp) * 100000;
    return (Result);
}

u16 fn3BcdToHex_u16(u8 Dat0, u8 Dat1, u8 Dat2)
{
    u16 Result = 0;
    u8 tmp = 0x0f;
    Result = (Dat0 & tmp) +
             ((Dat0 >> 4) & tmp) * 10 +
             ((Dat1) & tmp) * 100 +
             ((Dat1 >> 4) & tmp) * 1000 +
             ((Dat2) & tmp) * 10000;
    return (Result);
}

s16 fn3BcdToHex_s16(u8 Dat0, u8 Dat1, u8 Dat2, u8 sign)
{
    s16 Result = 0;
    u8 tmp = 0x0f;
    Result = (Dat0 & tmp) +
             ((Dat0 >> 4) & tmp) * 10 +
             ((Dat1) & tmp) * 100 +
             ((Dat1 >> 4) & tmp) * 1000 +
             ((Dat2) & tmp) * 10000;
    Result = ((Result & 0x7FFF) | (sign << 15)); //增加符合位
    return (Result);
}

/*********************************************************************************************************
** Function name:
** Descriptions:        按小端格式获取16为数据
** input parameters:  buf, 数据缓冲
** output parameters:
** Returned value:       16位整形数据
*********************************************************************************************************/
u16 Std_Lsb16DataGet(const u8* buf)
{
    return ((u16)buf[1] << 8) + (u16)buf[0];
}

/*********************************************************************************************************
** Function name:
** Descriptions:    按小端格式设置16位数据缓冲
** input parameters:  data, 16位数据
** output parameters:   buf, 数据缓冲,
** Returned value:
*********************************************************************************************************/
void Std_Lsb16DataSet(u8* buf, u16 data)
{
    buf[1] = (u8)(data >> 8);
    buf[0] = (u8)data;
}

/*********************************************************************************************************
** Function name:
** Descriptions:    按大端格式获取16为数据
** input parameters:   buf, 数据缓冲
** output parameters:
** Returned value:    16位整形数据
*********************************************************************************************************/
u16 Std_Msb16DataGet(const u8* p)
{
    return ((u16)p[0] << 8) + (u16)p[1];
}

/*********************************************************************************************************
** Function name:
** Descriptions:    按大端格式设置16位数据缓冲
** input parameters:   data, 16位数据
** output parameters:   buf, 数据缓冲,
** Returned value:
*********************************************************************************************************/
void Std_Msb16DataSet(u8* buf, u16 data)
{
    buf[0] = (u8)(data >> 8);
    buf[1] = (u8)data;
}

/*********************************************************************************************************
** Function name:
** Descriptions:     按小端格式获取32位数据
** input parameters:   buf, 数据缓冲
** output parameters:
** Returned value:      32位整形数据
*********************************************************************************************************/
u32 Std_Lsb32DataGet(const u8* buf)
{
    u8 i;
    u32 data;
    for (i = 4; i > 0; i--)
    {
        data <<= 8;
        data += buf[i - 1];
    }
    return data;
}

/*********************************************************************************************************
** Function name:
** Descriptions:        按小端格式设置32位数据缓冲
** input parameters:  data, 32位数据
** output parameters:   buf, 数据缓冲,
** Returned value:
*********************************************************************************************************/
void Std_Lsb32DataSet(u8* buf, u32 data)
{
    u8 i;
    for (i = 0; i < 4; i++)
    {
        buf[i] = (u8)data;
        data >>= 8;
    }
}

/*********************************************************************************************************
** Function name:
** Descriptions:     按大端格式获取32位数据
** input parameters:  buf, 数据缓冲
** output parameters:
** Returned value:      32位整形数据
*********************************************************************************************************/
u32 Std_Msb32DataGet(const u8* buf)
{
    u8 i;
    u32 data;
    for (i = 0; i < 4; i++)
    {
        data <<= 8;
        data += buf[i];
    }
    return data;
}

/*********************************************************************************************************
** Function name:
** Descriptions:     按大端格式设置32位数据缓冲
** input parameters:  data, 32位数据
** output parameters:   buf, 数据缓冲,
** Returned value:
*********************************************************************************************************/
void Std_Msb32DataSet(u8* buf, u32 data)
{
    u8 i;
    for (i = 4; i > 0; i--)
    {
        buf[i - 1] = (u8)data;
        data >>= 8;
    }
}

/*********************************************************************************************************
** Function name:
** Descriptions:      多个字节数据比较函数
** input parameters: cmp1, 比较数据1; cmp2,比较数据2, len, 比较的数据长度
** output parameters:
** Returned value:      结果
*********************************************************************************************************/
ErrorStatus Std_Memcmp(const void* cmp1, const void* cmp2, u16 len)
{
    const u8* pcmp1 = cmp1;
    const u8* pcmp2 = cmp2;

    if (cmp1 == cmp2)
    {
        return SUCCESS;
    }
    if (cmp1 == NULL || cmp2 == NULL)
    {
        return ERROR;
    }
    while (len != 0)
    {
        if (*pcmp1 != *pcmp2)
        {
            return ERROR;
        }
        pcmp1++;
        pcmp2++;
        len--;
    }
    return SUCCESS;
}

/*********************************************************************************************************
** Function name:
** Descriptions:    数据块拷贝函数
** input parameters: src,源数据块, len, 拷贝的长度
** output parameters:   dest, 目标数据块;
** Returned value:
*********************************************************************************************************/
void Std_Memcpy(void* dest, const void* src, u16 len)
{
    u8* pdest = (u8*)dest;
    const u8* psrc = (u8*)src;
    if (dest == src)
    {
        return;
    }
    if (dest == NULL || src == NULL)
    {
        return;
    }
    while (len != 0)
    {
        *pdest = *psrc;
        pdest++;
        psrc++;
        len--;
    }
}

/*********************************************************************************************************
** Function name:    Std_SubMemcpy
** Descriptions:    数据块拷贝函数(地址递减)
** input parameters: src,源数据块, len, 拷贝的长度
** output parameters:   dest, 目标数据块;
** Returned value:
*********************************************************************************************************/
void Std_SubMemcpy(UCHAR *dest, UCHAR *src, UCHAR len)
{
    while (len != 0)
    {
        len--;
        dest[len] = src[len];
    }
}

/*********************************************************************************************************
** Function name:
** Descriptions:     数据块设置值
** input parameters: val,数值, len, 拷贝的长度
** output parameters:   dest, 目标数据块;
** Returned value:
*********************************************************************************************************/
void Std_Memset(void* dest, s8 data, u16 len)
{
    u8* pdest = (u8*)dest;
    if (dest == NULL)
    {
        return;
    }
    while (len != 0)
    {
        *pdest = data;
        pdest++, len--;
    }
}

/*********************************************************************************************************
** Function name:
** Descriptions:      数据高低字节掉头，
**                  最高位与最低位互换，
**                  次高位与次低位互换，
**                  依次类推
** input parameters:  src: 输入数据地址指针, len, 拷贝的长度
** output parameters:   dest: 输出数据地址指针
** Returned value:
*********************************************************************************************************/
void Std_MemRvs(u8 *dest, u8 *src, u16 len)
{
    u16 i;

    if ((NULL == src) || (NULL == dest))
    {
        return;
    }

    dest += len - 1;
    for (i = 0; i < len; i++)
    {
        *dest = *src;
        dest--;
        src++;
    }
}

/*********************************************************************************************************
** Function name:
** Descriptions:      数组高低字节自翻转
**                  最高位与最低位互换，
**                  次高位与次低位互换，
**                  依次类推
** input parameters:  srcData: 输入数据地址指针, len, 拷贝的长度
** output parameters:   srcData: 输出数据地址指针
** Returned value:
*********************************************************************************************************/
void Std_MemRvsSelf(u8 *srcData, u16 len)
{
    u8 *begin, *end;
    u16 tmp;

    for (begin = srcData, end = srcData + len - 1; begin < end; begin++, end--)
    {
        tmp = *end;
        *end = *begin;
        *begin = tmp;
    }
}

/*********************************************************************************************************
** Function name:
** Descriptions:     字节bit高低字节自翻转
**                  最高位与最低位互换，
**                  次高位与次低位互换，
**                  依次类推
** input parameters:  srcData: 输入数据地址指针
** output parameters:
** Returned value:
*********************************************************************************************************/
void Std_BitRvsSelf(u8 *destData, u8 *srcData)
{
    u8 i, tmp = 1, result = 0;

    for (i = 0 ; i < 8 ; i++)
    {
        result <<= 1;
        if (*srcData & tmp)
        {
            result |= 1;
        }

        tmp <<= 1;
    }

    *destData = result;
}

static const char AsciiUpperNumberTable[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',};

/*********************************************************************************************************
** Function name:
** Descriptions:      十六进制字节转换成两个可视字符
**
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
void Std_HexToAscii(char* Ascii, u8 hex)
{
    Ascii[0] = AsciiUpperNumberTable[hex >> 4];
    Ascii[1] = AsciiUpperNumberTable[hex & 0xf];
}

/*********************************************************************************************************
** Function name:
** Descriptions:      两个可视字符转换成十六进制字节
**
** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
u8 Std_AsciiToHex(u8* hex,  u8* Ascii)
{
    u8 i, result, tmp;
    for (i = 0, result = 2; i < 2; i++)
    {
        u8 ch = Ascii[i];
        tmp <<= 4;
        if (ch >= '0' && ch <= '9')
        {
            tmp += (ch - '0');
        }
        else if (ch >= 'A' && ch <= 'F')
        {
            tmp += (ch - 'A' + 10);
        }
        else if (ch >= 'a' && ch <= 'f')
        {
            tmp += (ch - 'a' + 10);
        }
        else
        {
            return result;
        }
        result--;
    }
    *hex = tmp;
    return 0;
}

/*********************************************************************************************************
** Function name:
** Descriptions:    hex数据串转换为字符串
**
** input parameters:
** output parameters:
** Returned value:      有效返回转换后的数据串长度
*********************************************************************************************************/
u16 Std_HexStrToAsciiStr(char* Ascii, const u8* hex, u32 len)
{
    u32 i = 0;
    while (len != 0)
    {
        Std_HexToAscii(Ascii, hex[i++]);
        Ascii += 2, len--;
    }
    return i * 2;
}

/*********************************************************************************************************
** Function name:
** Descriptions:    字符串转换为hex数据串
**
** input parameters:
** output parameters:
** Returned value:      有效返回转换后的数据串长度
*********************************************************************************************************/
u16 Std_AsciiStrToHexStr(u8* hex,  u8* Ascii, u16 len)
{
    u16 i = 0;
    while (len > 1)
    {
        Std_AsciiToHex(&hex[i++], Ascii);
        Ascii += 2, len -= 2;
    }
    return i;
}

// 比较设置的切换时间是否合法sDate_time_s_TypeDef
/*********************************************************************************************************
** Function name:    fnCheck_Date_time_s
** Descriptions:    检查时间日期合法性
**
** input parameters:  HEX , Date_time_s 类型
** output parameters:
** Returned value:
*********************************************************************************************************/
ErrorStatus fnCheck_Date_time_s(sDate_time_s_TypeDef *Ck)
{
    if (Ck->year > 2099)
    {
        return ERROR;
    }
    if ((Ck->month > 12) || (Ck->month == 0))
    {
        return ERROR;
    }

    if (Ck->month == 2)
    {
        if (Ck->year  % 4)
        {
            if (Ck->day > 28)
            {
                return ERROR;
            }
        }
        else
        {
            if (Ck->day > 29)
            {
                return ERROR;
            }
        }
    }
    else
    {
        if ((Ck->day > TAB_DayOfMonth[Ck->month]) || (Ck->day == 0))
        {
            return ERROR;
        }
    }
    if (Ck->hour > 23)
    {
        return ERROR;
    }
    if (Ck->minute > 59)
    {
        return ERROR;
    }
    if (Ck->second > 59)
    {
        return ERROR;
    }

    return SUCCESS;//正确
}
