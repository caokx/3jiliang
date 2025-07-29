/********************************************************************
Filename:       Dl698_UserData_Encode645to698.h
Revised:        $Date: 2017-07-03 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
#ifndef _DL698_USERDATA_ENCODE645TO698_H_
#define _DL698_USERDATA_ENCODE645TO698_H_

/*********************************************************************
* INCLUDES
*/
#ifdef _WIN32
#else
#include <App.h>
#endif

/*********************************************************************
* MACROS
*/

/*********************************************************************
* CONSTANTS
*/

/*********************************************************************
* TYPEDEFS
*/
//DL645->DL698返回数据类型转换映射关系枚举
typedef enum
{
    DATA_TYPE_VOID,                                            // 0,
    DATA_TYPE_4BYTE_YMDH_TO_DATATIMES,                         // 1,
    DATA_TYPE_NEED_TO_DOUBLE_LONG_UNSIGNED_STR,                // 2,
    DATA_TYPE_NEED_ARRAY_TO_DOUBLE_LONG_UNSIGNED_STR_ARRAY,    // 3,
    DATA_TYPE_UELIG_TO_UELIG,                                  // 4,
    DATA_TYPE_5BYTE_YMDHM_TO_DATATIMES,                        // 5,
    DATA_TYPE_4BYTE_BCD_TO_LONG64_UNSIGNED,                    // 6,
    DATA_TYPE_4BYTE_BCD_TO_DOUBLE_LONG,                        // 7,
    DATA_TYPE_4BYTE_BCD_TO_DOUBLE_LONG_UNSIGNED,               // 8,
    DATA_TYPE_2BYTE_BCD_TO_DOUBLE_LONG_UNSIGNED,               // 9,
    DATA_TYPE_4BYTE_BCD_ARRAY_TO_DOUBLE_LONG_UNSIGNED_ARRAY,   // 10,
    DATA_TYPE_U64_BCD_PART1_STR_TO_DOUBLE_LONG_ARRAY_4,        // 11,
    DATA_TYPE_U64_BCD_PART2_STR_TO_DOUBLE_LONG_ARRAY_4,        // 12,
    DATA_TYPE_YMDHMS_TO_DATATIMES,                             // 13,
    DATA_TYPE_3BYTE_BCD_TO_LONG_UNSIGNED,                      // 14,
    DATA_TYPE_2BYTE_BCD_TO_LONG_UNSIGNED,                      // 15
    DATA_TYPE_3BYTE_BCD_TO_DOUBLE_LONG,                        // 16,
    DATA_TYPE_2BYTE_BCD_TO_LONG,                               // 17,
    DATA_TYPE_1BYTE_BCD_TO_UNSIGNED,                           // 18,
    DATA_TYPE_2BYTE_BCD_TO_UNSIGNED,                           // 19,
    DATA_TYPE_1BYTE_HEX_TO_UNSIGNED,                           // 20,
    DATA_TYPE_3BYTE_BCD_TO_DOUBLE_LONG_UNSIGNED,               // 21,
    DATA_TYPE_7BYTE_YMDWHMS_TO_DATATIMES,                      // 22,
    DATA_TYPE_10BYTE_ASCII_TO_DATATIMES,                       // 23,
    DATA_TYPE_6BYTE_TO_OCTET_STRING_6,                         // 24,
    DATA_TYPE_2BYTE_BCD_TO_OCTET_STRING_2,                     // 25,
    DATA_TYPE_4BYTE_BCD_TO_OCTET_STRING_4,                     // 26,
    DATA_TYPE_32BYTE_ASCII_TO_VISBLE_STRING_32,                // 27,
    DATA_TYPE_10BYTE_ASCII_TO_VISBLE_STRING_32,                // 28,
    DATA_TYPE_8BYTE_BCD_TO_VISIBLE_STRING,                     // 29,
    DATA_TYPE_1BYTE_BCD_TO_BIT_STRING_8,                       // 30,
    DATA_TYPE_2BYTE_BCD_TO_BIT_STRING_SIZE_16,                 // 31,
    DATA_TYPE_2BYTE_BCD_TO_BIT_STRING_SIZE_1,                  // 32,
    DATA_TYPE_1BYTE_BCD_TO_COMDCB,                             // 33,
    DATA_TYPE_POSITION_TO_STR1,                                // 34,
    DATA_TYPE_TIMEZONE_3BYTE_BCD_TO_STR1,                      // 35
    DATA_TYPE_2BYTE_DH_TO_STR1,                                // 36,
    DATA_TYPE_3BYTE_BCD_HMN_BCD_STR3,                          // 37,
    DATA_TYPE_4BYTE_YMDN_BCD_TO_STR4,                          // 38,
    DATA_TYPE_LOSEVOLTAGE_TO_STR5,                             // 39,
    DATA_TYPE_UNDERVOLTAGE_TO_STR6,                            // 40,
    DATA_TYPE_OVERVOLATE_TO_STR7,                              // 41,
    DATA_TYPE_PHASEFAILTURE_TO_STR8,                           // 42,
    DATA_TYPE_UNBALANCEVOLTAGE_TO_STR9,                        // 43,
    DATA_TYPE_UNBALANCECURRENT_TO_STR10,                       // 44,
    DATA_TYPE_LOSECURRENT_TO_STR11,                            // 45
    DATA_TYPE_OVERCURRENT_TO_STR12,                            // 46,
    DATA_TYPE_CURRENTFAILTURE_TO_STR13,                        // 47,
    DATA_TYPE_POWERREVERSE_TO_STR14,                           // 48,
    DATA_TYPE_OVERLOAD_TO_STR15,                               // 49,
    DATA_TYPE_POWERFACTORULTRALIMIT_TO_STR17,                  // 50,
    DATA_TYPE_UNBALANCESERIOUSCURRENT_TO_STR18,                // 51,
    DATA_TYPE_POWERREVERSELOW_TO_STR19,                        // 52,
    DATA_TYPE_LADDER_TO_STR20,                                 // 53,
    DATA_TYPE_MONEYFRZ_TO_STR21,                               // 54,
    DATA_TYPE_6BYTE_ASCII_TO_VISBLE_STRING_6,                  // 55,
    DATA_TYPE_4BYTE_ASCII_TO_VISBLE_STRING_4,                  // 56,
    DATA_TYPE_2BYTE_BCD_ARRAY_3_TO_LONG_UNSIGNED_ARRAY_3,      // 57
    DATA_TYPE_2BYTE_BCD_ARRAY_3_TO_LONG_ARRAY_3,               // 58
    DATA_TYPE_3BYTE_BCD_ARRAY_3_TO_DOUBLE_LONG_ARRAY_3,        // 59
    DATA_TYPE_3BYTE_BCD_ARRAY_4_TO_DOUBLE_LONG_ARRAY_4,        // 60
    DATA_TYPE_2BYTE_BCD_ARRAY_4_TO_LONG_ARRAY_4,               // 61
    DATA_TYPE_2BYTE_BCD_ARRAY_21_TO_LONG_ARRAY_21,             // 62
    DATA_TYPE_YMDHMS_ARRAY_TO_STANDARD_RECORD_STR,             // 63
    DATA_TYPE_NEEDLIMIT_TO_STANDARD_RECORD_STR,                // 64 //正向有功需量超限记录   反向有功需量超限记录
    DATA_TYPE_PRGCONT_TO_PRG_RECORD_STR,                       // 65 //编程记录内容
    DATA_TYPE_CLRRCDCONT_TO_STANDARD_RECORD_STR,               // 66 //电表清零记录内容
    DATA_TYPE_NEEDRCDCONT_TO_STANDARD_RECORD_STR,              // 67 //需量清零记录内容
    DATA_TYPE_EVTRCDCONT_TO_CLREVENT_RECORD_STR,               // 68 //事件清零记录内容
    DATA_TYPE_CALRCDCONT_TO_STANDARD_RECORD_STR,               // 69 //校时记录内容
    DATA_TYPE_TTBLRCDCONT_TO_STANDARD_RECORD_STR,              // 70 //时段表编程记录内容
    DATA_TYPE_TZTBLRCDCONT_TO_STANDARD_RECORD_STR,             // 71 //时区表编程记录内容
    DATA_TYPE_WKOFFRCDCONT_TO_STANDARD_RECORD_STR,             // 72 //周休日编程记录内容
    DATA_TYPE_HLDAYRCDCONT_TO_STANDARD_RECORD_STR,             // 73 //节假日编程记录内容
    DATA_TYPE_COMPPRGRCD_TO_STANDARD_RECORD_STR,               // 74 //有功组合方式编程记录 无功组合方式编程记录
    DATA_TYPE_ACCDAYRCDCONT_TO_STANDARD_RECORD_STR,            // 75 //结算日编程记录内容
    DATA_TYPE_OPENCOVERRCD_TO_STANDARD_RECORD_STR,             // 76 //开表盖记录  开端钮盒记录
    DATA_TYPE_RATEPARRCD_TO_STANDARD_RECORD_STR,               // 77 //费率参数表编程记录内容
    DATA_TYPE_STEPCHARTRCD_TO_STANDARD_RECORD_STR,             // 78 //阶梯表编程记录内容
    DATA_TYPE_KEYUPDATA_TO_STANDARD_RECORD_STR,                // 79 //秘钥更新记录内容
    DATA_TYPE_ABNORCARDRCD_TO_ABNO_RECORD_STR,                 // 80 //异常插卡记录内容
    DATA_TYPE_RETURNRATERCD_TO_RETURN_RECORD_STR,              // 81 //退费记录内容
    DATA_TYPE_CONTINTERRCD_TO_STANDARD_RECORD_STR,             // 82 //恒定磁场干扰记录
    DATA_TYPE_MISOPLDSWHRCD_TO_STANDARD_RECORD_STR,            // 83 //负荷开关误动作记录内容
    DATA_TYPE_PWREXPTRCD_TO_STANDARD_RECORD_STR,               // 84 //电源异常记录内容
    DATA_TYPE_NEEDLIMIT_TO_STR22,                              // 85
    DATA_TYPE_DISPLAY_OAD_DI_STR,                              // 86
    DATA_TYPE_FL_TO_STR,                                       // 87
    DATA_TYPE_4BYTE_BCD_TO_DOUBLE_LONG_ARRAY,                  // 88,
    DATA_TYPE_4BYTE_BCD_TO_DOUBLE_LONG_UNSIGNED_ARRAY,         // 89,
    DATA_TYPE_1BYTE_BCD_TO_ENUM,                               // 90
    DATA_TYPE_EXCHG_MAX,                                       // 91
} eDl698DL_DataTypeExchg_TypeDef;

typedef struct
{
    u8  exchg_type;
    u8  elementIndex;
    u16 retlen;
} sDl698_len_TypeDef;

typedef struct
{
    u32 OAD;
    u32 OAD2;
    u32 DI;
    u8  exchg_type;
    u16 dl645_len;
    u16 dl698_len;
    u8  dar;
} sDl698_test_TypeDef;

/*********************************************************************
* GLOBAL VARIABLES
*/

/*********************************************************************
* EXTERNAL VARIABLES
*/

/*********************************************************************
* EXTERNAL FUNCTIONS
*/
u8 fnDl698_Set645Data(DI_Analyse_TypeDef *pDI, u8  *pParam, u16 len);
u8 fnDl698_GetRetlen(u8 index, u8 exchgType, u16 *plen);
u8 fnDl698_EncodeDIData(u32 OAD, u16 datalen, u8 exchg_type, u8 *p645DataBuf, u8 *p698DataBuf, DI_Analyse_TypeDef *pDI, u16 *pRetLen);
u8 fnDl698_EncodeMuitDIData(u32 OAD, u32 OAD2, u16 datalen, u8 exchg_type, u8 *p645DataBuf, u8 *p698DataBuf, DI_Analyse_TypeDef *pDI, u16 *pRetLen);

#ifdef __cplusplus
}
#endif

#endif //_DL698_USERDATA_ENCODE645TO698_H_
