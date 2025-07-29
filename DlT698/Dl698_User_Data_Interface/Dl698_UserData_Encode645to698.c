/********************************************************************
Filename:       Dl698_UserData_Encode645to698.c
Revised:        $Date: 2017-07-03 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"
#include "Dl698_UserData_Encode645to698.h"
#include "Dl645B_Com.h"
#include "Dl698_AL.h"
#include "Dl698AL_asn1.h"

/*********************************************************************
* CONSTANTS
*/

//根据exchgType查询返回dl698数据内容长度
//简单说明: 1.index = 0xFF 时，说明该类型通配对应OAD 所有元素。
//          2.index < 0xFF 时，说明该类型对应的returnlen仅匹配对应OAD的对应index元素项
//          3.returnlen = 0时，表明该类型对应的OAD返回的长度不确定，需要以编解码后返回的len为准
const sDl698_len_TypeDef gDl698_DataRetlenMap[] =
{
    /* exchange_type , index, returnlen */
    { DATA_TYPE_4BYTE_YMDH_TO_DATATIMES, 0xFF,  8                               },
    { DATA_TYPE_NEED_TO_DOUBLE_LONG_UNSIGNED_STR, 0xFF,  15                              },
    { DATA_TYPE_NEED_ARRAY_TO_DOUBLE_LONG_UNSIGNED_STR_ARRAY, 0xFF, (15 * (MAX_FL + 1) + 2)      },
    { DATA_TYPE_UELIG_TO_UELIG, 0xFF,  23                              },
    { DATA_TYPE_5BYTE_YMDHM_TO_DATATIMES, 0xFF,  8                               },
    { DATA_TYPE_4BYTE_BCD_TO_LONG64_UNSIGNED, 0xFF,  9                               },
    { DATA_TYPE_4BYTE_BCD_TO_DOUBLE_LONG, 0xFF,  5                               },
    { DATA_TYPE_4BYTE_BCD_TO_DOUBLE_LONG_UNSIGNED, 0xFF,  5                               },
    { DATA_TYPE_2BYTE_BCD_TO_DOUBLE_LONG_UNSIGNED, 0xFF,  5                               },
    { DATA_TYPE_4BYTE_BCD_ARRAY_TO_DOUBLE_LONG_UNSIGNED_ARRAY, 0xFF, (5 * (MAX_FL + 1) +2)         },
    { DATA_TYPE_U64_BCD_PART1_STR_TO_DOUBLE_LONG_ARRAY_4, 0xFF,  22                              },
    { DATA_TYPE_U64_BCD_PART2_STR_TO_DOUBLE_LONG_ARRAY_4, 0xFF,  22                              },
    { DATA_TYPE_YMDHMS_TO_DATATIMES, 0xFF,  8                               },
    { DATA_TYPE_3BYTE_BCD_TO_LONG_UNSIGNED, 0xFF,  3                               },
    { DATA_TYPE_2BYTE_BCD_TO_LONG_UNSIGNED, 0xFF,  3                               },
    { DATA_TYPE_3BYTE_BCD_TO_DOUBLE_LONG, 0xFF,  5                               },
    { DATA_TYPE_2BYTE_BCD_TO_LONG, 0xFF,  3                               },
    { DATA_TYPE_1BYTE_BCD_TO_UNSIGNED, 0xFF,  2                               },
    { DATA_TYPE_2BYTE_BCD_TO_UNSIGNED, 0xFF,  2                               },
    { DATA_TYPE_1BYTE_HEX_TO_UNSIGNED, 0xFF,  2                               },
    { DATA_TYPE_3BYTE_BCD_TO_DOUBLE_LONG_UNSIGNED, 0xFF,  5                               },
    { DATA_TYPE_7BYTE_YMDWHMS_TO_DATATIMES, 0xFF,  8                               },
    { DATA_TYPE_10BYTE_ASCII_TO_DATATIMES, 0xFF,  8                               },
    { DATA_TYPE_6BYTE_TO_OCTET_STRING_6, 0xFF,  8                               },
    { DATA_TYPE_2BYTE_BCD_TO_OCTET_STRING_2, 0xFF,  4                               },
    { DATA_TYPE_4BYTE_BCD_TO_OCTET_STRING_4, 0xFF,  6                               },
    { DATA_TYPE_32BYTE_ASCII_TO_VISBLE_STRING_32, 0xFF,  34                              },
    { DATA_TYPE_10BYTE_ASCII_TO_VISBLE_STRING_32, 0xFF,  34                              },
    { DATA_TYPE_8BYTE_BCD_TO_VISIBLE_STRING, 0xFF,  18                              },
    { DATA_TYPE_1BYTE_BCD_TO_BIT_STRING_8, 0xFF,  3                               },
    { DATA_TYPE_2BYTE_BCD_TO_BIT_STRING_SIZE_16, 0xFF,  4                               },
    { DATA_TYPE_2BYTE_BCD_TO_BIT_STRING_SIZE_1, 0xFF,  0                               },
    { DATA_TYPE_1BYTE_BCD_TO_COMDCB, 0xFF,  6                               },
    { DATA_TYPE_POSITION_TO_STR1, 0xFF, 27                               },
    { DATA_TYPE_POSITION_TO_STR1, 1, 10                               },
    { DATA_TYPE_POSITION_TO_STR1, 2, 10                               },
    { DATA_TYPE_POSITION_TO_STR1, 3,  5                               },
    { DATA_TYPE_TIMEZONE_3BYTE_BCD_TO_STR1, 0, (8 * MAX_TIMEZONE + 2)        },
    { DATA_TYPE_TIMEZONE_3BYTE_BCD_TO_STR1, 0xFE,  8                               },
    { DATA_TYPE_2BYTE_DH_TO_STR1, 0xFF,  6                               },
    { DATA_TYPE_3BYTE_BCD_HMN_BCD_STR3, 0xFF, (8 * MAX_POT + 2)           },
    { DATA_TYPE_4BYTE_YMDN_BCD_TO_STR4, 0xFF, 10                               },
    { DATA_TYPE_LOSEVOLTAGE_TO_STR5, 1, 3                                },
    { DATA_TYPE_LOSEVOLTAGE_TO_STR5, 2, 3                                },
    { DATA_TYPE_LOSEVOLTAGE_TO_STR5, 3, 5                                },
    { DATA_TYPE_LOSEVOLTAGE_TO_STR5, 4, 2                                },
    { DATA_TYPE_UNDERVOLTAGE_TO_STR6, 1, 3                                },
    { DATA_TYPE_UNDERVOLTAGE_TO_STR6, 2, 2                                },
    { DATA_TYPE_OVERVOLATE_TO_STR7, 1, 3                                },
    { DATA_TYPE_OVERVOLATE_TO_STR7, 2, 2                                },
    { DATA_TYPE_PHASEFAILTURE_TO_STR8, 1, 3                                },
    { DATA_TYPE_PHASEFAILTURE_TO_STR8, 2, 5                                },
    { DATA_TYPE_PHASEFAILTURE_TO_STR8, 3, 2                                },
    { DATA_TYPE_UNBALANCEVOLTAGE_TO_STR9, 1, 3                                },
    { DATA_TYPE_UNBALANCEVOLTAGE_TO_STR9, 2, 2                                },
    { DATA_TYPE_UNBALANCECURRENT_TO_STR10, 1, 3                                },
    { DATA_TYPE_UNBALANCECURRENT_TO_STR10, 2, 2                                },
    { DATA_TYPE_LOSECURRENT_TO_STR11, 1, 3                                },
    { DATA_TYPE_LOSECURRENT_TO_STR11, 2, 5                                },
    { DATA_TYPE_LOSECURRENT_TO_STR11, 3, 5                                },
    { DATA_TYPE_LOSECURRENT_TO_STR11, 4, 2                                },
    { DATA_TYPE_OVERCURRENT_TO_STR12, 1, 5                                },
    { DATA_TYPE_OVERCURRENT_TO_STR12, 2, 2                                },
    { DATA_TYPE_CURRENTFAILTURE_TO_STR13, 1, 3                                },
    { DATA_TYPE_CURRENTFAILTURE_TO_STR13, 2, 5                                },
    { DATA_TYPE_CURRENTFAILTURE_TO_STR13, 3, 2                                },
    { DATA_TYPE_POWERREVERSE_TO_STR14, 1, 5                                },
    { DATA_TYPE_POWERREVERSE_TO_STR14, 2, 2                                },
    { DATA_TYPE_OVERLOAD_TO_STR15, 1, 5                                },
    { DATA_TYPE_OVERLOAD_TO_STR15, 2, 2                                },
    { DATA_TYPE_POWERFACTORULTRALIMIT_TO_STR17, 1, 3                                },
    { DATA_TYPE_POWERFACTORULTRALIMIT_TO_STR17, 2, 2                                },
    { DATA_TYPE_UNBALANCESERIOUSCURRENT_TO_STR18, 1, 3                                },
    { DATA_TYPE_UNBALANCESERIOUSCURRENT_TO_STR18, 2, 2                                },
    { DATA_TYPE_POWERREVERSELOW_TO_STR19, 1, 5                                },
    { DATA_TYPE_POWERREVERSELOW_TO_STR19, 2, 2                                },
    { DATA_TYPE_LADDER_TO_STR20, 0, 105                              },
    { DATA_TYPE_LADDER_TO_STR20, 1, (5 * MAX_LADDER + 2)        },
    { DATA_TYPE_LADDER_TO_STR20, 2, (5 * MAX_LADDER + 7)        },
    { DATA_TYPE_LADDER_TO_STR20, 3, 34                               },
    { DATA_TYPE_MONEYFRZ_TO_STR21, 1, 5                                },
    { DATA_TYPE_MONEYFRZ_TO_STR21, 2, 5                                },
    { DATA_TYPE_MONEYFRZ_TO_STR21, 3, 5                                },
    { DATA_TYPE_6BYTE_ASCII_TO_VISBLE_STRING_6, 0xFF, 8                                },
    { DATA_TYPE_4BYTE_ASCII_TO_VISBLE_STRING_4, 0xFF, 6                                },
    { DATA_TYPE_2BYTE_BCD_ARRAY_3_TO_LONG_UNSIGNED_ARRAY_3, 0xFF, 11                               },
    { DATA_TYPE_2BYTE_BCD_ARRAY_3_TO_LONG_ARRAY_3, 0xFF, 11                               },
    { DATA_TYPE_3BYTE_BCD_ARRAY_3_TO_DOUBLE_LONG_ARRAY_3, 0xFF, 17                               },
    { DATA_TYPE_3BYTE_BCD_ARRAY_4_TO_DOUBLE_LONG_ARRAY_4, 0xFF, 22                               },
    { DATA_TYPE_2BYTE_BCD_ARRAY_4_TO_LONG_ARRAY_4, 0xFF, 14                               },
    { DATA_TYPE_2BYTE_BCD_ARRAY_21_TO_LONG_ARRAY_21, 0xFF, 65                               },
    { DATA_TYPE_YMDHMS_ARRAY_TO_STANDARD_RECORD_STR, 0xFF, 26                               },
    { DATA_TYPE_NEEDLIMIT_TO_STANDARD_RECORD_STR, 0xFF, 38                               },
    { DATA_TYPE_PRGCONT_TO_PRG_RECORD_STR, 0xFF, 78                               },
    { DATA_TYPE_CLRRCDCONT_TO_STANDARD_RECORD_STR, 0xFF, 146                              },
    { DATA_TYPE_NEEDRCDCONT_TO_STANDARD_RECORD_STR, 0xFF, 384                              },
    { DATA_TYPE_EVTRCDCONT_TO_CLREVENT_RECORD_STR, 0xFF, 33                               },
    { DATA_TYPE_CALRCDCONT_TO_STANDARD_RECORD_STR, 0xFF, 26                               },
    { DATA_TYPE_TTBLRCDCONT_TO_STANDARD_RECORD_STR, 0xFF, ((8 * MAX_POT + 2) * 16 + 26) },
    { DATA_TYPE_TZTBLRCDCONT_TO_STANDARD_RECORD_STR, 0xFF, ((8 * MAX_TIMEZONE + 2) * 2 + 28)},
    { DATA_TYPE_WKOFFRCDCONT_TO_STANDARD_RECORD_STR, 0xFF, 28                               },
    { DATA_TYPE_HLDAYRCDCONT_TO_STANDARD_RECORD_STR, 0xFF, (5 * MAX_HOLIDAY + 26)      },
    { DATA_TYPE_COMPPRGRCD_TO_STANDARD_RECORD_STR, 0xFF, 28                               },
    { DATA_TYPE_ACCDAYRCDCONT_TO_STANDARD_RECORD_STR, 0xFF, 44                               },
    { DATA_TYPE_OPENCOVERRCD_TO_STANDARD_RECORD_STR, 0xFF, 86                               },
    { DATA_TYPE_RATEPARRCD_TO_STANDARD_RECORD_STR, 0xFF, ((5 * MAX_FL + 2) * 2 + 26)     },
    { DATA_TYPE_STEPCHARTRCD_TO_STANDARD_RECORD_STR, 0xFF, (20 * MAX_LADDER + 116)   },
    { DATA_TYPE_KEYUPDATA_TO_STANDARD_RECORD_STR, 0xFF, 44                               },
    { DATA_TYPE_ABNORCARDRCD_TO_ABNO_RECORD_STR, 0xFF, 58                               },
    { DATA_TYPE_RETURNRATERCD_TO_RETURN_RECORD_STR, 0xFF, 31                               },
    { DATA_TYPE_CONTINTERRCD_TO_STANDARD_RECORD_STR, 0xFF, 46                               },
    { DATA_TYPE_MISOPLDSWHRCD_TO_STANDARD_RECORD_STR, 0xFF, 48                               },
    { DATA_TYPE_PWREXPTRCD_TO_STANDARD_RECORD_STR, 0xFF, 36                               },
    { DATA_TYPE_NEEDLIMIT_TO_STR22, 0, 22                               },
    { DATA_TYPE_NEEDLIMIT_TO_STR22, 1, 5                                },
    { DATA_TYPE_DISPLAY_OAD_DI_STR, 0xFF, 10                               },
    { DATA_TYPE_FL_TO_STR, 0xFF, ((5 * MAX_FL) +2)             },
    { DATA_TYPE_4BYTE_BCD_TO_DOUBLE_LONG_ARRAY, 0xFF, 0                                },
    { DATA_TYPE_4BYTE_BCD_TO_DOUBLE_LONG_UNSIGNED_ARRAY, 0xFF, 0                                },
    { DATA_TYPE_1BYTE_BCD_TO_ENUM, 0xFF,  2                               },
};
const u8 gDl698_DataRetlenMapSize = sizeof(gDl698_DataRetlenMap) / sizeof(gDl698_DataRetlenMap[0]);

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

/*********************************************************************
* LOCAL VARIABLES
*/

/*********************************************************************
* LOCAL FUNCTIONS
*/

/*********************************************************************
* PUBLIC FUNCTIONS
*/
/*********************************************************************
* @fn      fnBaudRate_Convert()
*
* @brief   波特率转换函数
*
* @param
*
* @return  返回0：获取数据成功； 非零：获取数据失败
*/
u8 fnBaudRate_Convert(u8 u8Src)
{
    if (u8Src == 0x01)
    {
        return (0x00);
    }
    else if (u8Src == 0x02)
    {
        return (0x01);
    }
    else if (u8Src == 0x04)
    {
        return (0x02);
    }
    else if (u8Src == 0x08)
    {
        return (0x03);
    }
    else if (u8Src == 0x10)
    {
        return (0x04);
    }
    else if (u8Src == 0x20)
    {
        return (0x05);
    }
    else if (u8Src == 0x40)
    {
        return (0x06);
    }
    else if (u8Src == 0x80)
    {
        return (0x07);
    }
    else
    {
        return (0x0);
    }
}

/*********************************************************************
* @fn      fnDl698_Get645Data
*
* @brief   按照645的数据标识获取数据
*
* @param
*
* @return  返回0：获取数据成功； 非零：获取数据失败
*/

u8 fnDl698_Get645Data(DI_Analyse_TypeDef *pDI, u8  *pRetBuf, u16 *pRetLen)
{
    u8 Result = 0;
    switch (pDI->DI3)
    {
        case 0x00:
            Result = fnDl645_GetRmEgSh(pDI->DI2, pDI->DI1, pDI->DI0, 0, pRetBuf, pRetLen);
            break;
        case 0x01:
            Result = fnDl645_GetRmNeed(pDI->DI2, pDI->DI1, pDI->DI0, 0, pRetBuf, pRetLen);
            break;
        case 0x02:
            Result = fnDl645_GetVar(pDI->DI2, pDI->DI1, pDI->DI0, pRetBuf, pRetLen);
            break;
        case 0x03:
            Result = fnDl645_GetEv(pDI->DI2, pDI->DI1, pDI->DI0, 0, pRetBuf, pRetLen);
            break;
        case 0x04:
            Result = fnDl645_GetParaVar(pDI->DI2, pDI->DI1, pDI->DI0, pRetBuf, pRetLen);
            break;
        //case 0x05: Result = fnDl645_GetFrz(pDI->DI2 , pDI->DI1,pDI->DI0,0 , pRetBuf , pRetLen); break;
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            Result = fnDl645_GetVolEv(pDI->DI3, pDI->DI2, pDI->DI1, pDI->DI0, 0, pRetBuf, pRetLen);
            break;
        case 0x14:
        case 0x15:
            Result = fnDl645_GetInPhaEv(pDI->DI3, pDI->DI2, pDI->DI1, pDI->DI0, 0, pRetBuf, pRetLen);
            break;
        case 0x16:
        case 0x17:
            Result = fnDl645_GetUnblEv(pDI->DI3, pDI->DI2, pDI->DI1, pDI->DI0, 0, pRetBuf, pRetLen);
            break;
        case 0x18:
        case 0x19:
        case 0x1A:
            Result = fnDl645_GetCurEv(pDI->DI3, pDI->DI2, pDI->DI1, pDI->DI0, 0, pRetBuf, pRetLen);
            break;
        case 0x1B:
        case 0x1C:
            Result = fnDl645_GetWaveEv(pDI->DI3, pDI->DI2, pDI->DI1, pDI->DI0, 0, pRetBuf, pRetLen);
            break;
        case 0x1d:
            Result = fnDl645_GetGateOffEv(pDI->DI2, pDI->DI1, pDI->DI0, pRetBuf, pRetLen);
            break;
        case 0x1e:
            Result = fnDl645_GetGateOnEv(pDI->DI2, pDI->DI1, pDI->DI0, pRetBuf, pRetLen);
            break;
        case 0x1F:
            Result = fnDl645_GetOverPfEv(pDI->DI3, pDI->DI2, pDI->DI1, pDI->DI0, 0, pRetBuf, pRetLen);
            break;
        default:
            Result = DATA_ACCESS_RESULT_UNAVA;
            *pRetLen = 0;
            break;
    }
    return Result;
}

/*********************************************************************
* @fn      fnDl698_Set645Data
*
* @brief   按照645的数据标识获取数据
*
* @param
*
* @return  返回0：获取数据成功； 非零：获取数据失败
*/
u8 fnDl698_Set645Data(DI_Analyse_TypeDef *pDI, u8  *pParam, u16 len)
{
    u8 Result = SUCCESS;

    return Result;
}

/*********************************************************************
* @fn      fnDl698_GetRetlen
*
* @brief
*
* @param
*
* @return
*/

u8 fnDl698_GetRetlen(u8 index, u8 exchgType, u16 *plen)
{
    u8 i = 0;
    for (i = 0; i < gDl698_DataRetlenMapSize; i++)
    {
        if (exchgType == gDl698_DataRetlenMap[i].exchg_type)
        {
            if (gDl698_DataRetlenMap[i].elementIndex == 0xFF)
            {
                *plen = gDl698_DataRetlenMap[i].retlen;
                return SUCCESS;
            }
            else if ((gDl698_DataRetlenMap[i].elementIndex == 0xFE) && (index != 0))
            {
                *plen = gDl698_DataRetlenMap[i].retlen;
                return SUCCESS;
            }
            else
            {
                if (gDl698_DataRetlenMap[i].elementIndex == index)
                {
                    *plen = gDl698_DataRetlenMap[i].retlen;
                    return SUCCESS;
                }
            }
        }
    }
    return ERROR;
}

/*********************************************************************
* @fn      fnDl698_Data645to698
*
* @brief
*
* @param
*
* @return
*/
u8 fnDl698_Data645to698(u8 index, u8 exchgType, u8 *pSrc, u16 srclen, u8 *pRetBuf, u16 *pRetlen)
{
    return 1;
}

/*********************************************************************
* @fn      fnDl698_EncodeDIData
*
* @brief
*
* @param
*
* @return
*/
u8 fnDl698_EncodeDIData(u32 OAD, u16 datalen, u8 exchg_type, u8 *p645DataBuf, u8 *p698DataBuf, DI_Analyse_TypeDef *pDI, u16 *pRetLen)
{
    u8 res = DATA_ACCESS_RESULT_SUC;
    u16 srclen = 0, temp698datalen = 0;
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    //获取645数据
    if (fnDl698_Get645Data(pDI, p645DataBuf, (u16 *)&srclen) == 0x0)
    {
        //645数据 ->698数据映射
        if (fnDl698_Data645to698(pOadAys->elementIndex, exchg_type, p645DataBuf, srclen, p698DataBuf, &temp698datalen) == SUCCESS)
        {
            if (temp698datalen != 0xFFFF)
            {
                datalen = temp698datalen;
            }
            p698DataBuf += datalen;
            *pRetLen += datalen;
            return DATA_ACCESS_RESULT_SUC;
        }
        else
        {
            res = DATA_ACCESS_RESULT_BLKUNV;
        }
    }
    else
    {
        res = DATA_ACCESS_RESULT_DENY;
    }

    return res;
}

/*********************************************************************
* @fn      fnDl698_EncodeMuitDIData
*
* @brief
*
* @param
*
* @return
*/
u8 fnDl698_EncodeMuitDIData(u32 OAD, u32 OAD2, u16 datalen, u8 exchg_type, u8 *p645DataBuf, u8 *p698DataBuf, DI_Analyse_TypeDef *pDI, u16 *pRetLen)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    u8 i = 0;
    u8 res = DATA_ACCESS_RESULT_SUC;
    if (OAD == 0x20140200)
    {
        UINT8_TO_STREAM(p698DataBuf, DTYPE_ARRAY);
        UINT8_TO_STREAM(p698DataBuf, 8);
        for (pDI->DI0 = 1; pDI->DI0 <= 8; pDI->DI0++)
        {
            res = fnDl698_EncodeDIData(OAD, datalen, exchg_type, p645DataBuf, p698DataBuf, pDI, pRetLen);
            if (res == DATA_ACCESS_RESULT_SUC)
            {
                if (pDI->DI0 == 8)
                {
                    return DATA_ACCESS_RESULT_SUC;
                }
            }
            else
            {
                return res;
            }
        }
    }
    else if ((pOadAys->OIA1 == OIA1_EVENT) && (pDI->DI0 == 0xFF))
    {
        UINT8_TO_STREAM(p698DataBuf, DTYPE_ARRAY);
        UINT8_TO_STREAM(p698DataBuf, 2);
        for (pDI->DI0 = 1; pDI->DI0 <= 2; pDI->DI0++)
        {
            res = fnDl698_EncodeDIData(OAD, datalen, exchg_type, p645DataBuf, p698DataBuf, pDI, pRetLen);
            if (res == DATA_ACCESS_RESULT_SUC)
            {
                if (pDI->DI0 == 2)
                {
                    return DATA_ACCESS_RESULT_SUC;
                }
            }
            else
            {
                return res;
            }
        }
    }
    else if ((pOadAys->OIA1 == OIA1_EVENT) && (pDI->DI1 == 0xFF))
    {
        UINT8_TO_STREAM(p698DataBuf, DTYPE_ARRAY);
        UINT8_TO_STREAM(p698DataBuf, 20);
        for (pDI->DI1 = 1; pDI->DI1 <= 2; pDI->DI1++)
        {
            res = fnDl698_EncodeDIData(OAD, datalen, exchg_type, p645DataBuf, p698DataBuf, pDI, pRetLen);
            if (res == DATA_ACCESS_RESULT_SUC)
            {
                if (pDI->DI1 == 2)
                {
                    return DATA_ACCESS_RESULT_SUC;
                }
            }
            else
            {
                return res;
            }
        }
    }
    else if ((OAD & 0xFFF0F000 == 0x30000000) && (OAD2 != 0xFFFFFFFF))
    {
        if ((OAD2 == 0x20002201) || (OAD2 == 0x20012201) || (OAD2 == 0x20042201) || (OAD2 == 0x20052201) || (OAD2 == 0x200A2201))
        {
            //同一组OAD1对应三组OAD2，每组OAD2仅DI1不同，差9
            UINT8_TO_STREAM(p698DataBuf, DTYPE_ARRAY);
            UINT8_TO_STREAM(p698DataBuf, 8);

            for (i = 0; i < 3; i++)
            {
                res = fnDl698_EncodeDIData(OAD, datalen, exchg_type, p645DataBuf, p698DataBuf, pDI, pRetLen);
                if (res == DATA_ACCESS_RESULT_SUC)
                {
                    if (i == 2)
                    {
                        return DATA_ACCESS_RESULT_SUC;
                    }
                    pDI->DI0 += 9;
                }
                else
                {
                    return res;
                }
            }
        }
    }
    return DATA_ACCESS_RESULT_UNAVA;
}
