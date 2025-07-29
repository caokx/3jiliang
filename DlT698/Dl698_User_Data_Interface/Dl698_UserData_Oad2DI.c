/**************************************************************************************************
  Filename:       Dl698_UserData_Oad2DI.c
  Revised:        $Date: 2017-07-03 $
  Revision:       $Revision: V0.1 $
  Author:

  Description:
**************************************************************************************************/
/*********************************************************************
 * INCLUDES
 */
#include "Dl698_Type.h"
#include "Dl698_UserData_Oad2DI.h"
#include "Dl698_UserData_Encode645to698.h"
#include "Dl698AL_asn1.h"
#include "Dl698_UserData.h"
#include <Secret.h>

extern u32  fnFind_FrzMinSpecPos(u8 Line, u8 type, sDate_time_s_TypeDef  *TimeDest,  sFrzMinHead_TypeDef  *tempFrzMin);
extern u16  fnFind_FrzSpecPos(u8 Item, u8 type, sDate_time_s_TypeDef  *TimeDest,  sFrzCtxList_TypeDef  *List);
//-----------电能 class1------------------------------
const sDl698_ENERGY_TypeDef ENERGY_Item[] =
{
    { 0x0010, PtPEg, (u8 *) &Energy.PubData.PtPEgSh[0]  },
    { 0x0020, NtPEg, (u8 *) &Energy.PubData.NtPEgSh[0]  },

    { 0x0050, Qd1QEg, (u8 *) &Energy.PubData.Qd1QEgSh[0] },    //第一象限无功
    { 0x0060, Qd2QEg, (u8 *) &Energy.PubData.Qd2QEgSh[0] },
    { 0x0070, Qd3QEg, (u8 *) &Energy.PubData.Qd3QEgSh[0] },
    { 0x0080, Qd4QEg, (u8 *) &Energy.PubData.Qd4QEgSh[0] },

    #if(nPhs==ThreePhs)
    { 0x0011, PtPEgA, (u8 *) &Energy.PubData.PtPEgSha    },
    { 0x0021, NtPEgA, (u8 *) &Energy.PubData.NtPEgSha    },
    { 0x0051, Qd1QEgA, (u8 *) &Energy.PubData.Qd1QEgSha   },
    { 0x0061, Qd2QEgA, (u8 *) &Energy.PubData.Qd2QEgSha   },
    { 0x0071, Qd3QEgA, (u8 *) &Energy.PubData.Qd3QEgSha   },
    { 0x0081, Qd4QEgA, (u8 *) &Energy.PubData.Qd4QEgSha   },

    { 0x0012, PtPEgB, (u8 *) &Energy.PubData.PtPEgShb    },
    { 0x0022, NtPEgB, (u8 *) &Energy.PubData.NtPEgShb    },
    { 0x0052, Qd1QEgB, (u8 *) &Energy.PubData.Qd1QEgShb   },
    { 0x0062, Qd2QEgB, (u8 *) &Energy.PubData.Qd2QEgShb   },
    { 0x0072, Qd3QEgB, (u8 *) &Energy.PubData.Qd3QEgShb   },
    { 0x0082, Qd4QEgB, (u8 *) &Energy.PubData.Qd4QEgShb   },

    { 0x0013, PtPEgC, (u8 *) &Energy.PubData.PtPEgShc    },
    { 0x0023, NtPEgC, (u8 *) &Energy.PubData.NtPEgShc    },
    { 0x0053, Qd1QEgC, (u8 *) &Energy.PubData.Qd1QEgShc   },
    { 0x0063, Qd2QEgC, (u8 *) &Energy.PubData.Qd2QEgShc   },
    { 0x0073, Qd3QEgC, (u8 *) &Energy.PubData.Qd3QEgShc   },
    { 0x0083, Qd4QEgC, (u8 *) &Energy.PubData.Qd4QEgShc   },
    #endif

    { 0x0110, PtFEg, (u8 *) &Energy.PubData.PtFEgSh[0]  },
    { 0x0120, NtFEg, (u8 *) &Energy.PubData.NtFEgSh[0]  },

    { 0x0210, PtHEg, (u8 *) &Energy.PubData.PtHEgSh[0]  },
    { 0x0220, NtHEg, (u8 *) &Energy.PubData.NtHEgSh[0]  },
};

//-----------变量，class3,class4------------------------------
const sDl698_VAR_TypeDef VAR_Item[] =
{
    {0x2000, Var_V, DTYPE_UINT16, (u8 *) &MeasureRms.PubData.U[0], DTYPE_UINT16_Len },         //电压
    {0x2001, Var_I, DTYPE_INT32, (u8 *) &MeasureRms.PubData.I[0],  DTYPE_INT32_Len },         //电流
    {0x2002, Var_Angle, DTYPE_UINT16, (u8 *) &MeasureRms.PubData.Angle[0], DTYPE_UINT16_Len },     //电压相角
    {0x2003, Var_Angle2, DTYPE_UINT16, (u8 *) &MeasureRms.PubData.Angle[3], DTYPE_UINT16_Len },    //电压电流相角
    {0x2004, Var_Pw, DTYPE_INT32, (u8 *) &MeasureRms.PubData.Pw[0],   DTYPE_INT32_Len },          //功率
    {0x2005, Var_Pq, DTYPE_INT32, (u8 *) &MeasureRms.PubData.Pw[4],   DTYPE_INT32_Len },          //功率  无功
    {0x2006, Var_Ps, DTYPE_INT32, (u8 *) &MeasureRms.PubData.Pw[8],   DTYPE_INT32_Len },          //功率  视在
    {0x200A, Var_Pf, DTYPE_INT16, (u8 *) &MeasureRms.PubData.Pf[0],   DTYPE_INT16_Len },          //功率因数
    {0x2007, Var_AveragePw, DTYPE_INT32, (u8 *) &MeasureRms.PubData.PPwave[0],   DTYPE_INT32_Len },   //一分钟平均有功功率
    {0x2008, Var_AveragePq, DTYPE_INT32, (u8 *) &MeasureRms.PubData.Pqwave[0],   DTYPE_INT32_Len },   //一分钟平均无功功率
    {0x2009, Var_AveragePs, DTYPE_INT32, (u8 *) &MeasureRms.PubData.Pswave[0],   DTYPE_INT32_Len },   //一分钟平均视在功率

    {0x200B, Var_WaveUnblU, DTYPE_INT16, (u8 *) &HarmonicData.PubData.HarmonicThdU[0],   DTYPE_INT16_Len },   //电压波形失真度
    {0x200C, Var_WaveUnblI, DTYPE_INT16, (u8 *) &HarmonicData.PubData.HarmonicThdI[0],   DTYPE_INT16_Len },   //电流波形失真度
    {0x200D, Var_HpercentU, DTYPE_INT16, (u8 *) &HarmonicData.PubData.HarmonicpercentU[0][0],    DTYPE_INT16_Len },   //电压谐波含有量（总及 2~n 次）
    {0x200E, Var_HpercentI, DTYPE_INT16, (u8 *) &HarmonicData.PubData.HarmonicpercentI[0][0],    DTYPE_INT16_Len },   //电流谐波含有量（总及 2~n 次）
    {0x2046, Var_HUrms, DTYPE_UINT32, (u8 *) &MeasureRms.PubData.HUrms[0][0],    DTYPE_UINT32_Len },   //谐波电压（1…n次）
    {0x2047, Var_HIrms, DTYPE_INT32, (u8 *) &MeasureRms.PubData.HIrms[0][0], DTYPE_INT32_Len },   //谐波电流（1…n次）
    {0x2048, Var_HPrms, DTYPE_INT32, (u8 *) &MeasureRms.PubData.HPrms[0][0], DTYPE_INT32_Len },   //谐波有功功率（1…n次）

    {0x205E, Var_PowerOFFData, DTYPE_DATETIME_S, NULL,  DTYPE_DATETIME_S },    //停电期间数据

    {0x200F, Var_Freq, DTYPE_UINT16, (u8 *) &MeasureRms.PubData.Frequency,  DTYPE_UINT16_Len },         //电网频率
    {0x2010, Var_TEMP, DTYPE_INT16, (u8 *) &Bkgrd.PubData.Temperature,  DTYPE_INT16_Len },         //表内温度

    //{0x2043 , Var_TnT_Chang        , DTYPE_INT16, (u8 *)&Bkgrd.PubData.TnTmper_Chang[0],  DTYPE_INT16_Len }, //端子座温度分钟变化量

    {0x2011, Var_ClockBat, DTYPE_UINT16, (u8 *) &Bkgrd.PubData.ClockBat,    DTYPE_UINT16_Len },     //时钟电池电压

    {0x2013, Var_BatTime, DTYPE_UINT32, (u8 *) &Bkgrd.PubData.tWorkBat,   DTYPE_UINT32_Len },       //时钟电池工作时间
    {0x2014, Var_Mstate, DTYPE_BITSTRING, (u8 *) &Bkgrd.PubData.MtSta,    DTYPE_UINT16_Len },       //电表运行状态字

    #if(nPhs==ThreePhs)

    {0x2012, Var_BackupBat, DTYPE_UINT16, (u8 *) &Bkgrd.PubData.BackupBat, DTYPE_UINT16_Len },   //停电抄表电池电压

    {0x2026, Var_UnblU, DTYPE_UINT16, (u8 *) &MeasureRms.PubData.UnblU,  DTYPE_UINT16_Len },        //电压不平衡率
    {0x2027, Var_UnblI, DTYPE_UINT16, (u8 *) &MeasureRms.PubData.UnblI,  DTYPE_UINT16_Len },        //电流不平衡率
    {0x2029, Var_Ahs, DTYPE_UINT32, NULL,    DTYPE_UINT32_Len },           //安时值，读取时计算

    {0x2131, Var_EligRateUA, DTYPE_STRUCTURE, (u8 *) &Stat.PubData.UElig_Day[0], sizeof(sUEligStat_TypeDef) },      //A相电压合格率,
    {0x2132, Var_EligRateUB, DTYPE_STRUCTURE, (u8 *) &Stat.PubData.UElig_Day[1], sizeof(sUEligStat_TypeDef) },   //B相电压合格率
    {0x2133, Var_EligRateUC, DTYPE_STRUCTURE, (u8 *) &Stat.PubData.UElig_Day[2], sizeof(sUEligStat_TypeDef) },   //C相电压合格率
    #endif
};

//----------参量，class8-----------------------------
const sDl698_PARA_VAR_TypeDef PARA_VAR_Item[] =
{
    {0x4000, DTYPE_DATETIME_S, 0xC1, 0x00, 0x00, 0x00}, //8 日期时间
    {0x4001, DTYPE_OCT_STR, 0xC1, FileId_ParaCom, sizeof(sDF12), FileItemInfoOffAddr_ComPara_ComAddr},    //通讯地址
    {0x4002, DTYPE_OCT_STR, 0xC1, FileId_HighPara, sizeof(sDF12), FileItemInfoOffAddr_HighPara_MeterNo},    //表号
    {0x4003, DTYPE_OCT_STR, 0xC1, FileId_HighPara, sizeof(sDF12), FileItemInfoOffAddr_HighPara_UserNo },    //客户编号
    {0x4004, DTYPE_STRUCTURE, 0xC0, FileId_ParaASCII, FileItemInfoLen_ASCIIPara_MeterPlace, FileItemInfoOffAddr_ASCIIPara_MeterPlace },    //设备地理位置

    {0x400E, DTYPE_UINT8,  0x41, FileId_ParaDoc, 1, FileItemInfoOffAddr_DocPara_nWave },    //谐波分析次数

    {0x400F, DTYPE_UINT8,  0x41, FileId_ParaCipherKey, 1, FileItemInfoOffAddr_CipherKeyPara_nCipherKey },    //
    {0x4010, DTYPE_UINT8, 0x41, FileId_HighPara, 1, FileItemInfoOffAddr_HighPara_WireMode },    //计量元件数单相表为 1，三相三线表为 2，三相四线表为 3
    {0x4011, DTYPE_STRUCTURE, 0xC0, FileId_RatePara, FileItemInfoLen_RatePara_HolidayTable, FileItemInfoOffAddr_RatePara_HolidayTable },     //公共节假日数

    {0x401C, DTYPE_UINT32, 0x41, FileId_HighPara, 3, FileItemInfoOffAddr_HighPara_CT },     //电流互感器变比
    {0x401D, DTYPE_UINT32, 0x41, FileId_HighPara, 3, FileItemInfoOffAddr_HighPara_PT },     //互感器变比

    {0x4027, DTYPE_ENUM,   0x40,  0, 1, 0},                            // 升级操作类型、结果

    {0x40EE, DTYPE_DATETIME_S, 0x41, FileId_BackUpCurMoney, 7, FileItemInfoOffAddr_BackUpCurMoney_DateTime },     //管理模组费率电能备份

    {0x4102, DTYPE_UINT8, 0x41, FileId_ParaDoc, 2, FileItemInfoOffAddr_DocPara_PlsWidth },
    {0x4103, DTYPE_STRING, 0xC0, FileId_ParaASCII, 32, FileItemInfoOffAddr_ASCIIPara_DeviceNo },     //资产管理编码
    {0x4104, DTYPE_STRING, 0x40, FileId_ParaASCII, 6, FileItemInfoOffAddr_ASCIIPara_RatingVol },
    {0x4105, DTYPE_STRING, 0x40, FileId_ParaASCII, 6, FileItemInfoOffAddr_ASCIIPara_RatingCur },
    {0x4106, DTYPE_STRING, 0x40, FileId_ParaASCII, 6, FileItemInfoOffAddr_ASCIIPara_MaxCur },
    {0x4107, DTYPE_STRING, 0x40, FileId_ParaASCII, 4, FileItemInfoOffAddr_ASCIIPara_PGrade },
    {0x4108, DTYPE_STRING, 0x40, FileId_ParaASCII, 4, FileItemInfoOffAddr_ASCIIPara_QGrade },
    {0x4109, DTYPE_UINT32, 0x40, FileId_HighPara, sizeof(sDF11), FileItemInfoOffAddr_HighPara_PConstE },
    {0x410A, DTYPE_UINT32, 0x40, FileId_HighPara, sizeof(sDF11), FileItemInfoOffAddr_HighPara_QConstE },
    {0x410B, DTYPE_STRING, 0x40, FileId_ParaASCII, 10, FileItemInfoOffAddr_ASCIIPara_MeterModel },
    {0x4111, DTYPE_STRING, 0x40, FileId_ParaASCII, 16, FileItemInfoOffAddr_ASCIIPara_SoftWare },
    {0x4112, DTYPE_BITSTRING, 0xC0, FileId_HighPara, 1, FileItemInfoOffAddr_HighPara_PExpression },
    {0x4113, DTYPE_BITSTRING, 0xC0, FileId_HighPara, 1, FileItemInfoOffAddr_HighPara_PtQExpression },
    {0x4114, DTYPE_BITSTRING, 0xC0, FileId_HighPara, 1, FileItemInfoOffAddr_HighPara_NtQExpression },
    {0x4116, DTYPE_STRUCTURE, 0xC0, FileId_RatePara, 6, FileItemInfoOffAddr_RatePara_RmDate },

    {0x4804, DTYPE_STRUCTURE, 0xC0, FileId_FirmPara, 12, FileItemInfoOffAddr_FirmPara_KUrms },
};

//--------------事件记录-----------------------------
const sRecordItem_TypeDef Event_Item[] =
{
    {0x3050, FileItemInfoNum_Evt_PowDn                 },
    {0x3013, FileItemInfoNum_Evt_Clr                   },
    {0x3016, FileItemInfoNum_Evt_SetClock            },
    {0x301B, FileItemInfoNum_Evt_OpenCover         },
    {0x301C, FileItemInfoNum_Evt_OpenTail          },

    {0x3026, FileItemInfoNum_Evt_PrgSetPsw           },

    {0x303C, FileItemInfoNum_Evt_BroadcastTime     },
    {0x3031, FileItemInfoNum_Evt_MngPlug   },
    {0x3036, FileItemInfoNum_Evt_MngUpdate     },
};

#define ITEMCLASS7  0x7
#define ITEMCLASS24 0x24

//-----------冻结------------------
const sRecordItem_TypeDef Frz_Item[] =
{
    {0x5002, FileItemInfoNum_Frz_MinFrz       },
};

/*********************************************************************************************************
** Function name:    fnGet_EnergyData
** Descriptions:     根据

** input parameters:
** output parameters:
** Returned value:
*********************************************************************************************************/
u8 fnGet_EnergyData(u32  OAD, u8  *uBuf)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    u8  i, datalen = 0, item;
    u16 OIA_B = (OAD >> 16 & 0xFFFF);
    u8  EgBuf[(MAX_FL + 1) * 8];

    for (i = 0 ; i < RE_ARRAY_LENGTH(ENERGY_Item); i++)
    {
        if (ENERGY_Item[i].OI == OIA_B)
        {
            item = ENERGY_Item[i].Item;
            break;
        }
    }

    if (i == RE_ARRAY_LENGTH(ENERGY_Item))
    {
        return datalen;
    }

    Std_Memcpy(EgBuf, ENERGY_Item[item].Addr, sizeof(sFsEgSh_HighTypeDef));

    //----------根据属性把数据封装成标准长度----------------------------
    {
        if (pOadAys->AtrIndex == 0x02)
        {
            if ((pOadAys->elementIndex == 0) || (pOadAys->elementIndex == 1))    //读取总及各费率电能
            {
                fnEnergy_Change(&EgBuf[0], uBuf, Energy_HEX2FractionE);
                datalen += DTYPE_INT32_Len;
            }
        }
        else if (pOadAys->AtrIndex == 0x04)
        {
            if ((pOadAys->elementIndex == 0) || (pOadAys->elementIndex == 1))
            {
                fnEnergy_Change(&EgBuf[0], uBuf, Energy_HEX4FractionE);
                datalen += DTYPE_INT64_Len;
            }
        }
        else if (pOadAys->AtrIndex == 0x06)
        {
            if ((pOadAys->elementIndex == 0) || (pOadAys->elementIndex == 1))
            {
                fnEnergy_Mantissa(&EgBuf[0], uBuf);
                datalen += DTYPE_UINT8_Len;
            }
        }
        else if (pOadAys->AtrIndex == 0x08) //属性8扩展精度2,6位小数电能
        {
            if ((pOadAys->elementIndex == 0) || (pOadAys->elementIndex == 1))
            {
                fnEnergy_Change(&EgBuf[0], uBuf, Energy_HEX6FractionE);
                datalen += DTYPE_INT64_Len;
            }
        }
    }

    return datalen;
}

/*********************************************************************************************************
** Function name:    fnGet_Energy
** Descriptions:     读取电量并按要求组帧

** input parameters:  OAD: 输入电量OAD; oiindex: OAD序号，用于查找数据类型;Data_type:读取数据类型
** output parameters:   pRetBuf: 输出数据地址指针;pRetLen:输出数据长度指针
** Returned value:  ERROR:读取失败;SUCCESS  :读取成功
*********************************************************************************************************/
u8 fnGet_Energy(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen,  u8  *blockRsp)
{
    u8  type[20], datalen;
    u16  len16;

    //------获取电量数据-----------
    datalen = fnGet_EnergyData(OAD, uBuf);

    if (datalen == 0)
    {
        return ERROR;
    }

    //-------获取电量数据类型-----------------
    fnGet_OADDataType(OAD, &type[0]);

    //-------根据数据类型封装成应答的698格式----------------
    len16 = (u16)datalen;
    pRetBuf += fnForm_build_Type(pRetBuf, pRetLen, uBuf, &len16, &type[0]);

    return SUCCESS;
}

/*********************************************************************
* @fn      fnGet_NeedData
*
* @brief
*
* @param
*
* @return
*/

/*********************************************************************
* @fn      fnGet_VarData
*
* @brief
*
* @param
*
* @return
*********************************************************************/
u8 fnGet_VarData(u32  OAD, u8  *uBuf)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    u8  i, datalen = 0, item, offset, line;
    u16 OIA_B = (OAD >> 16 & 0xFFFF);
    s32  temp_s32;
    u32 temp_u32 ;

    for (i = 0 ; i < RE_ARRAY_LENGTH(VAR_Item); i++)
    {
        if (VAR_Item[i].OI == OIA_B)
        {
            item = VAR_Item[i].Item;
            line = i;
            break;
        }
    }

    if (i == RE_ARRAY_LENGTH(VAR_Item))
    {
        return datalen;
    }

    switch (item)
    {
        case Var_V:
            if ((pOadAys->AtrIndex == 2) || (pOadAys->AtrIndex == 4))
            {
                if (pOadAys->elementIndex == 0)
                {
                    for (i = 0; i < nPhs; i++)
                    {
                        datalen = VAR_Item[line].Len ;
                        if (pOadAys->AtrIndex == 2)
                        {
                            temp_u32 = MeasureRms.PubData.U[i] / 100;    //应答按1位小数
                        }
                        else
                        {
                            temp_u32 = MeasureRms.PubData.U[i] / 10;    //应答按2位小数,高精度电压
                        }

                        Std_Memcpy(uBuf + i * datalen, (u8 *)&temp_u32, datalen);
                    }

                    datalen = VAR_Item[line].Len * nPhs ;
                }
                else if (pOadAys->elementIndex < (nPhs + 1))
                {
                    datalen = VAR_Item[line].Len ;

                    if (pOadAys->AtrIndex == 2)
                    {
                        temp_u32 = MeasureRms.PubData.U[pOadAys->elementIndex - 1] / 100;    //应答按1位小数
                    }
                    else
                    {
                        temp_u32 = MeasureRms.PubData.U[pOadAys->elementIndex - 1] / 10;    //应答按2位小数,高精度电压
                    }

                    Std_Memcpy(uBuf, (u8 *)&temp_u32, datalen);
                }
                else
                {
                    datalen = 0;
                }
            }
            else
            {
                datalen = 0;
            }

            break;

        case Var_Angle:
        case Var_Angle2:
            if (pOadAys->AtrIndex != 2)
            {
                datalen = 0;
                break;
            }
            #if(nPhs==ThreePhs)
            if (pOadAys->elementIndex == 0)
            {
                datalen = VAR_Item[line].Len * 3;
                Std_Memcpy(uBuf, VAR_Item[line].Addr, datalen);
            }
            else if (pOadAys->elementIndex < 4)
            {
                datalen = VAR_Item[line].Len ;
                offset = (pOadAys->elementIndex - 1) * VAR_Item[line].Len;
                Std_Memcpy(uBuf, VAR_Item[line].Addr + offset, datalen);
            }
            #else
            if ((pOadAys->elementIndex == 0) || (pOadAys->elementIndex == 1))
            {
                datalen = VAR_Item[line].Len ;
                Std_Memcpy(uBuf, VAR_Item[line].Addr, datalen);
            }
            #endif
            else
            {
                datalen = 0;
            }

            break;

        case Var_I:  //MeasureRms.PubData.I 4位小数存储,698属性2按3位小数应答，属性5按4位小数应答
            if ((pOadAys->AtrIndex == 2) || (pOadAys->AtrIndex == 5))
            {
                if (pOadAys->elementIndex == 0)
                {
                    datalen = DTYPE_INT32_Len * nPhs;
                    for (i = 0; i < nPhs; i++)
                    {
                        if (pOadAys->AtrIndex == 2)
                        {
                            temp_s32 = MeasureRms.PubData.I[i] / 10;
                        }
                        else
                        {
                            temp_s32 = MeasureRms.PubData.I[i];
                        }
                        Std_Memcpy(uBuf + i * DTYPE_INT32_Len, (u8 *)&temp_s32, DTYPE_INT32_Len);
                    }
                }
                else if (pOadAys->elementIndex < (nPhs + 1))
                {
                    datalen = DTYPE_INT32_Len ;
                    offset = (pOadAys->elementIndex - 1);

                    if (pOadAys->AtrIndex == 2)
                    {
                        temp_s32 = MeasureRms.PubData.I[offset] / 10;
                    }
                    else
                    {
                        temp_s32 = MeasureRms.PubData.I[offset];
                    }

                    Std_Memcpy(uBuf, (u8 *)&temp_s32, datalen);
                }
                else
                {
                    datalen = 0;
                }
            }
            else if ((pOadAys->AtrIndex == 4) && (pOadAys->elementIndex == 0)) //零线电流
            {
                datalen = DTYPE_INT32_Len;
                temp_s32 = MeasureRms.PubData.In / 10;
                Std_Memcpy(uBuf, (u8 *)&temp_s32, datalen);
            }

            #if(nPhs==ThreePhs)
            else if ((pOadAys->AtrIndex == 6) && (pOadAys->elementIndex == 0)) //零序电流
            {
                datalen = DTYPE_INT32_Len;
                temp_s32 = MeasureRms.PubData.VectorI[2] / 10;
                Std_Memcpy(uBuf, (u8 *)&temp_s32, datalen);
            }
            #else
            else if ((pOadAys->AtrIndex == 8) && (pOadAys->elementIndex == 0)) //不平衡电流
            {
                datalen = DTYPE_INT32_Len;
                temp_s32 = MeasureRms.PubData.UnblCur / 10;
                Std_Memcpy(uBuf, (u8 *)&temp_s32, datalen);
            }
            #endif
            else
            {
                datalen = 0;
            }

            break;

        case Var_Pw:
        case Var_Pq:
        case Var_Ps:
        case Var_AveragePw:
        case Var_AveragePq:
        case Var_AveragePs:
            if ((pOadAys->AtrIndex == 2) || (pOadAys->AtrIndex == 4))
            {
                if (pOadAys->elementIndex == 0)
                {
                    datalen = VAR_Item[line].Len * (nPhs + 1);
                    for (i = 0; i < (nPhs + 1); i++)
                    {
                        temp_s32 = 0;
                        Std_Memcpy((u8 *)&temp_s32, VAR_Item[line].Addr + i * 4, VAR_Item[line].Len);
                        //                  temp_s32 = (s32)temp_s32/100;   //3位小数存储，应答按1位小数
                        if (pOadAys->AtrIndex == 2)
                        {
                            temp_s32 /= 1000;
                        }
                        Std_Memcpy(uBuf +  VAR_Item[line].Len * i, (u8 *)&temp_s32, VAR_Item[line].Len);
                    }
                }
                else if (pOadAys->elementIndex <= (nPhs + 1))   // dyf 修改，Pc,Qc,Sc elementIndex=4
                {
                    datalen = VAR_Item[line].Len ;
                    offset = (pOadAys->elementIndex - 1) * VAR_Item[line].Len;
                    Std_Memcpy((u8 *)&temp_s32, VAR_Item[line].Addr + offset, datalen);
                    //              temp_s32 = (s32)temp_s32/100;   //3位小数存储，应答按1位小数
                    if (pOadAys->AtrIndex == 2)
                    {
                        temp_s32 /= 1000;
                    }
                    Std_Memcpy(uBuf, (u8 *)&temp_s32, datalen);
                }
                else
                {
                    datalen = 0;
                }
            }
            else
            {
                datalen = 0;
            }
            break;

        case Var_Pf:
            if (pOadAys->AtrIndex != 2)
            {
                datalen = 0;
                break;
            }

            if (pOadAys->elementIndex == 0)
            {
                for (i = 0; i < (nPhs + 1); i++)
                {
                    datalen = VAR_Item[line].Len;
                    temp_s32 = (s32)MeasureRms.PubData.Pf[i];   //应答按3位小数
                    Std_Memcpy(uBuf + i * datalen, (u8 *)&temp_s32, datalen);
                }

                datalen = VAR_Item[line].Len * (nPhs + 1);
            }
            else if (pOadAys->elementIndex <= (nPhs + 1))
            {
                datalen = VAR_Item[line].Len;

                #if(nPhs==ThreePhs)
                temp_s32 = (s32)MeasureRms.PubData.Pf[pOadAys->elementIndex - 1];   //应答按3位小数
                #else
                temp_s32 = (s32)MeasureRms.PubData.Pf[0] / 10; //应答按3位小数
                #endif
                Std_Memcpy(uBuf, (u8 *)&temp_s32, datalen);
            }
            else
            {
                datalen = 0;
            }

            break;

        case     Var_HpercentU:
        case     Var_HpercentI:
        case Var_HUrms:
        case Var_HIrms:
        case Var_HPrms:

            // A、B、C相谐波含有率、含量
            if ((pOadAys->AtrIndex == 2) || (pOadAys->AtrIndex == 3) || (pOadAys->AtrIndex == 4))
            {
                if (pOadAys->elementIndex == 0)
                {
                    datalen = VAR_Item[line].Len * nHarmonic;
                    temp_u32 = (pOadAys->AtrIndex - 2) * datalen;

                    for (i = 0; i < nHarmonic; i++)
                    {
                        offset = i  * VAR_Item[line].Len;

                        Std_Memcpy(uBuf + offset, VAR_Item[line].Addr + offset + temp_u32, VAR_Item[line].Len);
                    }
                }
                else if (pOadAys->elementIndex < (nHarmonic + 1))
                {
                    datalen = VAR_Item[line].Len ;
                    temp_u32 = (pOadAys->AtrIndex - 2) * datalen * nHarmonic;
                    offset = (pOadAys->elementIndex - 1) * VAR_Item[line].Len;

                    Std_Memcpy(uBuf, VAR_Item[line].Addr + offset + temp_u32, datalen);
                }
            }
            else if (pOadAys->AtrIndex == 5) //属性5,谐波含量次数
            {
                *uBuf = nHarmonic;
                datalen = 1;
            }
            else if (pOadAys->AtrIndex == 7) //属性7,谐波总有功功率
            {
                if (pOadAys->elementIndex == 0)
                {
                    datalen = 8;

                    temp_u32 = MeasureRms.PubData.HPtw;
                    Std_Memcpy(uBuf, (u8 *)&temp_u32, 4);

                    temp_u32 = MeasureRms.PubData.HNtw;
                    Std_Memcpy(uBuf + 4, (u8 *)&temp_u32, 4);
                }
                else if (pOadAys->elementIndex == 1)
                {
                    datalen = 4;

                    temp_u32 = MeasureRms.PubData.HPtw;
                    Std_Memcpy(uBuf, (u8 *)&temp_u32, 4);
                }
                else if (pOadAys->elementIndex == 2)
                {
                    datalen = 4;

                    temp_u32 = MeasureRms.PubData.HNtw;
                    Std_Memcpy(uBuf, (u8 *)&temp_u32, 4);
                }
            }

            break;

        case Var_WaveUnblU:
        case Var_WaveUnblI:
            if (pOadAys->AtrIndex == 2)
            {
                if (pOadAys->elementIndex == 0)
                {
                    datalen = VAR_Item[line].Len * 3 ;
                    for (i = 0; i < 3; i++)
                    {
                        offset = i  * VAR_Item[line].Len;
                        Std_Memcpy(uBuf + offset, VAR_Item[line].Addr + offset, datalen);
                    }
                }
                else if (pOadAys->elementIndex < 4)
                {
                    datalen = VAR_Item[line].Len ;
                    offset = (pOadAys->elementIndex - 1)  * VAR_Item[line].Len;
                    Std_Memcpy(uBuf + offset, VAR_Item[line].Addr + offset, datalen);
                }
                else
                {
                    datalen = 0;
                }
            }
            break;

        case Var_PowerOFFData:
            if (pOadAys->AtrIndex == 2)
            {
                if (pOadAys->elementIndex == 0)
                {
                    datalen = FileItemInfoLen_HighState_PwdnVoltLoss;

                    Std_Memset(uBuf, 0x00, datalen);    //停电期间电压电流数据为0

                    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_PwdnVoltLoss, uBuf, FileItemInfoLen_HighState_PwdnVoltLoss);
                }
                else if (pOadAys->elementIndex == 1)
                {
                    datalen = sizeof(sDate_time_s_TypeDef) ;

                    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_PwdnVoltLoss, uBuf, sizeof(sDate_time_s_TypeDef));
                }
                else if (pOadAys->elementIndex == 2)
                {
                    datalen = DTYPE_INT16 * 3;

                    sPwdnVoltCurTypedef Volt;
                    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_PwdnVoltLoss, &Volt.PwdnTime.second, FileItemInfoLen_HighState_PwdnVoltLoss);

                    memcpy(uBuf, &Volt.VoltVal[0], datalen);    //停电期间电压数据
                }
                else if (pOadAys->elementIndex == 3)
                {
                    datalen = DTYPE_INT32 * 3;

                    sPwdnVoltCurTypedef Volt;
                    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_PwdnVoltLoss, &Volt.PwdnTime.second, FileItemInfoLen_HighState_PwdnVoltLoss);

                    memcpy(uBuf, &Volt.CurVal[0], datalen);    //停电期间电流数据
                }
            }
            break;

        case Var_TEMP:
            if (pOadAys->AtrIndex == 2)   //表内温度
            {
                Std_Memcpy(uBuf, VAR_Item[line].Addr, VAR_Item[line].Len);
                datalen = VAR_Item[line].Len;
            }
            else if (pOadAys->AtrIndex == 4)  //端子温度
            {
                if (pOadAys->elementIndex == 0)
                {
                    datalen = DTYPE_INT16_Len * 8;
                    Std_Memcpy(uBuf, (u8 *)&Bkgrd.PubData.Tnal_Tmper[0], datalen);
                }
                else if (pOadAys->elementIndex < 9)
                {
                    datalen = DTYPE_INT16_Len;
                    Std_Memcpy(uBuf, (u8 *)&Bkgrd.PubData.Tnal_Tmper[pOadAys->elementIndex - 1], datalen);
                }
                else
                {
                    datalen = 0;
                }
            }
            break;

        case Var_ClockBat:
            if (pOadAys->elementIndex == 0)
            {
                datalen = DTYPE_UINT16_Len;
                Std_Memcpy(uBuf, (u8 *)&Bkgrd.PubData.ClockBat, datalen);
            }
            else
            {
                datalen = 0;
            }
            break;

        case Var_BatTime:
            if (pOadAys->elementIndex == 0)
            {
                datalen = DTYPE_UINT32_Len;
                Std_Memcpy(uBuf, (u8 *)&Bkgrd.PubData.tWorkBat, datalen);
            }
            else
            {
                datalen = 0;
            }
            break;

        case Var_TnT_Chang:
            if (pOadAys->AtrIndex == 2)
            {
                if (pOadAys->elementIndex == 0)
                {
                    datalen = VAR_Item[line].Len * 4 ;
                    Std_Memcpy(uBuf, VAR_Item[line].Addr, VAR_Item[line].Len);
                }
                else if (pOadAys->elementIndex < 5)
                {
                    datalen = VAR_Item[i].Len ;
                    offset = (pOadAys->elementIndex - 1) * VAR_Item[line].Len;
                    Std_Memcpy(uBuf, VAR_Item[line].Addr + offset, datalen);
                }
            }

            break;

        case Var_Mstate:
            #if 0   /* dyf 计量模组不用支持电能表运行状态字 1～7 0x20140201~20140207*/
            if (pOadAys->AtrIndex == 2)  //属性2，电表运行状态字
            {
                if (pOadAys->elementIndex == 0)
                {
                    datalen = VAR_Item[line].Len ;
                    Std_Memcpy(uBuf, (u8 *)&Bkgrd.PubData.MtSta, datalen * 7);
                }
                else if (pOadAys->elementIndex < 8)
                {
                    datalen = VAR_Item[line].Len;
                    offset = (pOadAys->elementIndex - 1) * datalen;
                    Std_Memcpy(uBuf, (u8 *)&Bkgrd.PubData.MtSta + offset, datalen);
                }
                else
                {
                    datalen = 0;
                }
            }
            //else
            #endif
            if (pOadAys->AtrIndex == 4)  //属性4，计量模组系统状态字
            {
                datalen = DTYPE_UINT32_Len;
                Std_Memcpy(uBuf, (u8 *)&Bkgrd.PubData.MtSysSta.SysSta, datalen);
            }
            else if (pOadAys->AtrIndex == 5)  //属性5，采样系统状态字
            {
                datalen = DTYPE_UINT32_Len;
                Std_Memcpy(uBuf, (u8 *)&Bkgrd.PubData.MeasureSysSta.SysSta, datalen);
            }

            break;

            #if(nPhs==ThreePhs)
        case Var_EligRateUA:
        case Var_EligRateUB:
        case Var_EligRateUC:

            offset = 0;
            if (pOadAys->elementIndex == 0)
            {
                for (i = 0; i < 3; i++)
                {
                    Std_Memcpy(uBuf + offset, (u8 *)&Stat.PubData.UElig_Day[i], sizeof(sUEligStat_TypeDef));
                    offset += sizeof(sUEligStat_TypeDef);
                    Std_Memcpy(uBuf + offset, (u8 *)&Stat.PubData.UElig_Month[i], sizeof(sUEligStat_TypeDef));
                    offset += sizeof(sUEligStat_TypeDef);
                }

                datalen = 6 * sizeof(sUEligStat_TypeDef);
            }
            else if (pOadAys->elementIndex == 1)
            {
                Std_Memcpy(uBuf, (u8 *)&Stat.PubData.UElig_Day[item - Var_EligRateUA], sizeof(sUEligStat_TypeDef));
                datalen = sizeof(sUEligStat_TypeDef);
            }
            else if (pOadAys->elementIndex == 2)
            {
                Std_Memcpy(uBuf, (u8 *)&Stat.PubData.UElig_Month[item - Var_EligRateUA], sizeof(sUEligStat_TypeDef));
                datalen = sizeof(sUEligStat_TypeDef);
            }
            else
            {
                datalen = 0;
            }

            break;
            #endif

        default:
            Std_Memcpy(uBuf, VAR_Item[line].Addr, VAR_Item[line].Len);
            datalen = VAR_Item[line].Len;
            break;
    }

    return datalen;
}

/*********************************************************************
* @fn      fnGet_Var
*
* @brief
*
* @param
*
* @return
*********************************************************************/
u8 fnGet_Var(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen,  u8  *blockRsp)
{
    u8 type[50], datalen;
    u16 len16;

    datalen = fnGet_VarData(OAD, uBuf);

    if (datalen == 0)
    {
        return ERROR;
    }

    // 停电期间电压电流数据
    if (OAD == 0x205E0200)
    {
        sPwdnVoltCurTypedef pwdnVolt;
        fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_PwdnVoltLoss, &pwdnVolt.PwdnTime.second, FileItemInfoLen_HighState_PwdnVoltLoss);
        u8 num;

        num = 3;
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &pwdnVolt.PwdnTime.second, NULL, DTYPE_DATETIME_S);
        // 电压数据
        num = 3;
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
        for (num = 0; num < 3; num++)
        {
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&pwdnVolt.VoltVal[num], NULL, DTYPE_UINT16);
        }
        // 电流数据
        num = 3;
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
        for (num = 0; num < 3; num++)
        {
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&pwdnVolt.CurVal[num], NULL, DTYPE_INT32);
        }
    }
    else
    {
        //-------获取变量数据类型-----------------
        fnGet_OADDataType(OAD, &type[0]);

        //-------根据数据类型封装成应答的698格式----------------
        len16 = (u16)datalen;
        pRetBuf += fnForm_build_Type(pRetBuf, pRetLen, uBuf, &len16, &type[0]);
    }

    return SUCCESS;
}

/*********************************************************************
* @fn      fnGet_Para  读取参数
*
* @brief
*
* @param
*
* @return
**********************************************************************/
u8 fnGet_Para(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen,  u8  *blockRsp)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    sHolidayTable_TypeDef  databuf;
    sTimeZoneTable_TypeDef  ZoneTab;
    sPOTTable_TypeDef       POTTab;
    u16 OffAddr;

    u16 OIA_B = (OAD >> 16 & 0xFFFF), len;
    u8 i, j, line, numHoliday, numZone, numPOTTab, numDayPOT, num  ;
    u8 res = SUCCESS, temp[4];
    u32  temp32;

    for (i = 0 ; i < RE_ARRAY_LENGTH(PARA_VAR_Item); i++)
    {
        if (PARA_VAR_Item[i].OI == OIA_B)
        {
            fnFile_Read(PARA_VAR_Item[i].FileId, PARA_VAR_Item[i].OffAddr, uBuf, PARA_VAR_Item[i].Len);
            line = i ;
            break;
        }
    }

    if ((OIA_B != 0x4000) && (OIA_B != 0x4400) && (OIA_B != 0x4106) && (OIA_B != 0x40EE) && (OIA_B != 0x4111))
    {
        if (pOadAys->AtrIndex != 2)
        {
            return ERROR;
        }
    }

    if (i != RE_ARRAY_LENGTH(PARA_VAR_Item))
    {
        switch (OIA_B) //有多个元素索引参数
        {
            case 0x4000:  //日期时间

                if (pOadAys->AtrIndex == 5)  //属性5，返回最小及最大校时偏差参数
                {
                    fnFile_Read(FileId_ParaDoc, FileItemInfoOffAddr_DocPara_BroadcastMIN, uBuf, 4);
                    if (pOadAys->elementIndex == 0)   //读取全部元素
                    {
                        num = 2;  //2/个结构体
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[0], NULL, DTYPE_UINT16);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[2], NULL, DTYPE_UINT16);
                    }
                    else if (pOadAys->elementIndex == 1)
                    {
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[0], NULL, DTYPE_UINT16);
                    }
                    else if (pOadAys->elementIndex == 2)
                    {
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[2], NULL, DTYPE_UINT16);
                    }
                }
                else if (pOadAys->AtrIndex == 2)
                {
                    fnSysDateTimes(&SysDatetimes);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&SysDatetimes, NULL, DTYPE_DATETIME_S);
                }
                else
                {
                    res = ERROR;
                }
                break;

            case 0x4001:   //通讯地址
                if ((pOadAys->AtrIndex == 2) && (pOadAys->elementIndex == 0))
                {
                    len = 6;
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &CommPara.ComAddr[0],  &len, DTYPE_OCT_STR);
                }
                else
                {
                    res = ERROR;
                }

                break;

            case 0x4002:
                if ((pOadAys->AtrIndex == 2) && (pOadAys->elementIndex == 0))
                {
                    fnUpdateMeterNo();
                    len = 6;
                    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_MeterNo, uBuf, len);

                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_OCT_STR);
                }
                else
                {
                    res = ERROR;
                }

                break;

            case 0x4003://客户编号
                if ((pOadAys->AtrIndex == 2) && (pOadAys->elementIndex == 0))
                {
                    len = FileItemInfoLen_HighPara_UserNo;
                    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_UserNo, uBuf, len);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_OCT_STR);
                }
                else
                {
                    res = ERROR;
                }
                break;

            case 0x4004:   //设备地理位置
                if (pOadAys->elementIndex == 0) //读取全部元素
                {
                    num = 3;  //3/个结构体
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                    for (i = 0; i < 2; i++) //经度、纬度
                    {
                        num = 4; //4/个结构体
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[4 * i + 0], NULL, DTYPE_ENUM);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[4 * i + 1], NULL, DTYPE_UINT8);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[4 * i + 2], NULL, DTYPE_UINT8);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[4 * i + 3], NULL, DTYPE_UINT8);
                    }
                    //高度
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[8], NULL, DTYPE_UINT32);
                }
                else if ((pOadAys->elementIndex == 1) || (pOadAys->elementIndex == 2)) //经度
                {
                    i = pOadAys->elementIndex - 1;
                    num = 4; //4/个结构体
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[4 * i + 0], NULL, DTYPE_ENUM);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[4 * i + 1], NULL, DTYPE_UINT8);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[4 * i + 2], NULL, DTYPE_UINT8);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[4 * i + 3], NULL, DTYPE_UINT8);
                }
                else if (pOadAys->elementIndex == 3)
                {
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[8], NULL, DTYPE_UINT32);
                }
                else
                {
                    res = ERROR;
                }

                break;
            case 0x4007:   //LCD参数

                if (pOadAys->elementIndex == 0) //读取全部元素
                {
                    num = 7;  //7/个结构体
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[0], NULL, DTYPE_UINT8);

                    for (i = 0; i < 3; i++) //long unsigned 背光点亮时间等三个参数
                    {
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[1 + 2 * i], NULL, DTYPE_UINT16);
                    }
                    for (i = 0; i < 3; i++) // unsigned 显示电能小数位数等三个参数
                    {
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[7 + i], NULL, DTYPE_UINT8);
                    }
                }
                else if (pOadAys->elementIndex == 1) //上电全显时间
                {
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[0], NULL, DTYPE_UINT8);
                }
                else if ((pOadAys->elementIndex == 2) || (pOadAys->elementIndex == 3) || (pOadAys->elementIndex == 4)) //
                {
                    i = pOadAys->elementIndex - 2;
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[1 + 2 * i], NULL, DTYPE_UINT16);
                }
                else if ((pOadAys->elementIndex == 5) || (pOadAys->elementIndex == 6) || (pOadAys->elementIndex == 7)) //
                {
                    i = pOadAys->elementIndex - 5;
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[7 + i], NULL, DTYPE_UINT8);
                }
                else
                {
                    res = ERROR;
                }

                break;

            case 0x4008:
            case 0x4009:
                #if(METERTYPE==2)
            case 0x400A:
            case 0x400B:  //切换时间
                #endif
                if (pOadAys->elementIndex == 0)
                {
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[0], NULL, DTYPE_DATETIME_S);
                }
                else
                {
                    res = ERROR;
                }
                break;

            case 0x400C:   //时区时段表参数
                if (pOadAys->elementIndex == 0) //读取全部元素
                {
                    num = 5;  //5个结构体
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                    for (i = 0; i < 5; i++) // unsigned
                    {
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[i], NULL, DTYPE_UINT8);
                    }
                }
                else if (pOadAys->elementIndex < 6) //读取单个元素
                {
                    i = pOadAys->elementIndex - 1;
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[i], NULL, DTYPE_UINT8);
                }
                else
                {
                    res = ERROR;
                }

                break;
            case 0x4010:   //
                if (pOadAys->elementIndex == 0)
                {
                    uBuf[0] = 3;  //三相三线=2    三相四线=3
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT8);
                }
                else
                {
                    res = ERROR;
                }

                break;

            case 0x4030:   //电压合格率参数
                if (pOadAys->elementIndex == 0)
                {
                    num = 4;  //4/个结构体
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                    for (i = 0; i < 4; i++)
                    {
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 2 * i, NULL, DTYPE_UINT16);
                    }
                }
                else if (pOadAys->elementIndex < 5)
                {
                    i = pOadAys->elementIndex - 1;
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 2 * i, NULL, DTYPE_UINT16);
                }
                else
                {
                    res = ERROR;
                }

                break;

            case 0x40EE:   //管理模组费率电能备份
                if (pOadAys->AtrIndex == 2)   //属性2
                {
                    if (pOadAys->elementIndex == 0)
                    {
                        num = 7;  //7/个结构体
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);

                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_DATETIME_S);

                        len = sizeof(sBackUpEnergy_TypeDef);

                        for (i = 0; i < 6 ; i++) //正向、反向、无功Q1、无功Q2、无功Q3、无功Q4
                        {
                            OffAddr = len * i;
                            fnFile_Read(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_PtPEgSh + OffAddr, uBuf, len);

                            num = *uBuf++;  //费率个数
                            if ((num == 0) || (num > 13)) //--初始化或清零后按总+12费率返回----
                            {
                                num = 13;
                            }
                            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
                            for (j = 0; j < num; j++)
                            {
                                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT64_Len * j, NULL, DTYPE_UINT64);
                            }
                        }
                    }
                    else if (pOadAys->elementIndex == 1)
                    {
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_DATETIME_S);
                    }
                    else if (pOadAys->elementIndex < 8)
                    {
                        len = sizeof(sBackUpEnergy_TypeDef);

                        OffAddr = len * (pOadAys->elementIndex - 2);
                        fnFile_Read(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_PtPEgSh + OffAddr, uBuf, len);

                        num = *uBuf++;  //费率个数
                        if ((num == 0) || (num > 13)) //--初始化或清零后按总+12费率返回----
                        {
                            num = 13;
                        }

                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
                        for (j = 0; j < num; j++)
                        {
                            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT64_Len * j, NULL, DTYPE_UINT64);
                        }
                    }
                    else
                    {
                        res = ERROR;
                    }
                }
                else    // dyf add 其他属性不支持召测
                {
                    res = ERROR;
                }

                break;

            case 0x4804:   //计量配置参数
                if (pOadAys->AtrIndex == 2)   //属性2 ,只读
                {
                    if (pOadAys->elementIndex == 0)
                    {
                        num = 5;  //5/个结构体
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                        num = 1;  //1/个
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
                        num = 4;  //4/个结构体
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                        num = 0;  //前闭后开
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_REGION);
                        Std_Memset((u8 *)&temp[0], 0x00, 4);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT32);    //电流区间
                        Std_Memset((u8 *)&temp[0], 0xff, 4);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT32);
                        num = 3;  //3/个
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY); //电压系数 3个，换算单位-3
                        temp32 = (u32)((float)100000000 / MeasureFirmPara.KUrms * 32 * (1.0 + (float)MeasureFirmPara.GSU[0] / 32768));
                        //Std_Memcpy((u8 *)&temp[0] , (u8 *)&temp32 , 4);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);    //电压系数
                        temp32 = (u32)((float)100000000 / MeasureFirmPara.KUrms * 32 * (1.0 + (float)MeasureFirmPara.GSU[1] / 32768));
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);    //电压系数
                        temp32 = (u32)((float)100000000 / MeasureFirmPara.KUrms * 32 * (1.0 + (float)MeasureFirmPara.GSU[2] / 32768));
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);    //电压系数

                        num = 3;  //3/个
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY); //电流系数 3个,换算单位-3

                        temp32 = (u32)((float)100000000 / MeasureFirmPara.KIArms * 32 * (1.0 + (float)MeasureFirmPara.GSI[0] / 32768));
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);    //暂时采用计量芯片转换系数，后续需乘对应关系
                        temp32 = (u32)((float)100000000 / MeasureFirmPara.KIArms * 32 * (1.0 + (float)MeasureFirmPara.GSI[1] / 32768));
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);
                        temp32 = (u32)((float)100000000 / MeasureFirmPara.KIArms * 32 * (1.0 + (float)MeasureFirmPara.GSI[2] / 32768));
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);

                        num = 3;  //3/个
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY); //相位系数 3个,换算单位-3
                        temp32 = 1000000;
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);    //
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);    //
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);    //

                        num = 1;  //1/个
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY); //零线电流系数 1个,换算单位-3
                        num = 2;  //2/个结构体
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                        num = 0;  //前闭后开
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_REGION);
                        Std_Memset((u8 *)&temp[0], 0x00, 4);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT32);    //电流区间
                        Std_Memset((u8 *)&temp[0], 0xff, 4);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT32);
                        temp32 = (u32)((float)100000000 / MeasureFirmPara.KIArms * 32 * (1.0 + (float)MeasureFirmPara.GSI[3] / 32768));
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);    //暂时采用计量芯片转换系数，后续需乘对应关系

                        temp[0] = 10;
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT8);   //偏移小数位数
                        temp[0] = (u8)MeasureFirmPara.Send_nPoint.SendParaBit.nPoint;  //点数128点
                        temp[1] = (u8)(MeasureFirmPara.Send_nPoint.SendParaBit.nPoint >> 8);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT16);   //采样周波点数

                        temp[0] = 3;
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT8);   //采样数据长度
                    }
                    else if (pOadAys->elementIndex == 1)
                    {
                        num = 1;  //1/个
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
                        num = 4;  //4/个结构体
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                        num = 0;  //前闭后开
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_REGION);
                        Std_Memset((u8 *)&temp[0], 0x00, 4);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT32);    //电流区间
                        Std_Memset((u8 *)&temp[0], 0xff, 4);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT32);
                        num = 1;  //1/个
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY); //电压系数 1个，换算单位-3
                        temp32 = (u32)(1000000 / MeasureFirmPara.KUrms);
                        //Std_Memcpy((u8 *)&temp[0] , (u8 *)&temp32 , 4);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);    //电压系数

                        num = 1;  //1/个
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY); //电流系数 1个,换算单位-3

                        temp32 = (u32)(1000000 / MeasureFirmPara.KIArms);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);    //暂时采用计量芯片转换系数，后续需乘对应关系

                        num = 1;  //1/个
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY); //相位系数 1个,换算单位-3
                        temp32 = 1000000;
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);    //
                    }
                    else if (pOadAys->elementIndex == 2)
                    {
                        num = 1;  //1/个
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY); //零线电流系数 1个,换算单位-3
                        num = 2;  //2/个结构体
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                        num = 0;  //前闭后开
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_REGION);
                        Std_Memset((u8 *)&temp[0], 0x00, 4);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT32);    //电流区间
                        Std_Memset((u8 *)&temp[0], 0xff, 4);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT32);
                        temp32 = (u32)(1000000 / MeasureFirmPara.KIArms);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);    //计量芯片转换系数
                    }
                    else if (pOadAys->elementIndex == 3)
                    {
                        temp[0] = 8;
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT8);   //偏移小数位数
                    }
                    else if (pOadAys->elementIndex == 4)
                    {
                        temp[0] = (u8)MeasureFirmPara.Send_nPoint.SendParaBit.nPoint;  //点数128点
                        temp[1] = (u8)(MeasureFirmPara.Send_nPoint.SendParaBit.nPoint >> 8);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT16);   //采样周波点数
                    }
                    else if (pOadAys->elementIndex == 5)
                    {
                        temp[0] = 3;
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp[0], NULL, DTYPE_UINT8);   //采样数据长度
                    }
                }

                break;

            case 0x4106:
                if (pOadAys->AtrIndex == 2)
                {
                    len = 6;
                    fnFile_Read(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_MaxCur, uBuf, len);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
                }
                else if (pOadAys->AtrIndex == 3)
                {
                    len = 32;
                    fnFile_Read(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_MinCur, uBuf, len);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
                }
                else if (pOadAys->AtrIndex == 4)
                {
                    len = 32;
                    fnFile_Read(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_TrCur, uBuf, len);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
                }
                else
                {
                    res = ERROR;
                }

                break;

            case 0x4109:
            case 0x410A:  //有功无功脉冲常数
                if (pOadAys->elementIndex == 0)
                {
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[0], NULL, DTYPE_UINT32);
                }
                else
                {
                    res = ERROR;
                }
                break;

            case 0x410B:    //电能表型号
                len = FileItemInfoLen_ASCIIPara_MeterModel;
                fnFile_Read(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_MeterModel, uBuf, len);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
                break;

            case 0x4111:    //软件备案号
                if (pOadAys->AtrIndex == 2)
                {
                    len = FileItemInfoLen_ASCIIPara_SoftWare;
                    fnFile_Read(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_SoftWare, uBuf, len);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
                }
                else if (pOadAys->AtrIndex == 3)
                {
                    len = FileItemInfoLen_ASCIIPara_SoftWareInfo;
                    fnFile_Read(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_SoftWareInfo, uBuf, len);
                    if (pOadAys->elementIndex == 0)
                    {
                        num = 1;
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
                    }
                    num = 6;
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                    len = 2;
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
                    uBuf += len;
                    len = 4;
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
                    uBuf += len;
                    len = 1;
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT8);
                    uBuf += len;
                    len = 8;
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
                    uBuf += len;
                    len = 1;
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT8);
                    uBuf += len;
                    len = 16;
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
                }
                break;

            case 0x4116:   //结算日
                if (pOadAys->elementIndex == 0) //读取全部元素
                {
                    num = 3;  //3个array
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
                    for (i = 0; i < 3; i++) // unsigned
                    {
                        num = 2;  //2个结构体
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[2 * i + 1], NULL, DTYPE_UINT8);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[2 * i], NULL, DTYPE_UINT8);
                    }
                }
                else if (pOadAys->elementIndex < 4) //读取单个元素
                {
                    i = pOadAys->elementIndex - 1;

                    num = 2;  //2个结构体
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[2 * i + 1], NULL, DTYPE_UINT8);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &uBuf[2 * i], NULL, DTYPE_UINT8);
                }
                else
                {
                    res = ERROR;
                }

                break;
            case 0x4011:   //公共假日表
                fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_nHoliday, &numHoliday, 1);
                if (numHoliday > MAX_HOLIDAY)
                {
                    numHoliday = MAX_HOLIDAY;
                }

                if (pOadAys->elementIndex == 0) //读取全部元素
                {
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &numHoliday, NULL, DTYPE_ARRAY);

                    for (i = 0; i < numHoliday; i++)
                    {
                        num = 2;  //2个结构体
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);

                        Std_Memcpy(&databuf, &uBuf[sizeof(sHolidayTable_TypeDef)*i], sizeof(sHolidayTable_TypeDef));

                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &databuf.Week, NULL, DTYPE_DATE);

                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &databuf.nPOTTable, NULL, DTYPE_UINT8);
                    }
                }
                else if (pOadAys->elementIndex <= numHoliday)
                {
                    i = pOadAys->elementIndex - 1;

                    num = 2;  //2个结构体
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);

                    Std_Memcpy(&databuf, &uBuf[sizeof(sHolidayTable_TypeDef)*i], sizeof(sHolidayTable_TypeDef));

                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &databuf.Week, NULL, DTYPE_DATE);

                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &databuf.nPOTTable, NULL, DTYPE_UINT8);
                }
                else
                {
                    res = ERROR;
                }

                break;

            case 0x4014:
            case 0x4015:   //当前套、备用套时区表
                fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_nTimeZone, &numZone, 1);
                if (numZone > MAX_TIMEZONE)
                {
                    numZone = MAX_TIMEZONE;
                }

                if (pOadAys->elementIndex == 0) //读取全部元素
                {
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &numZone, NULL, DTYPE_ARRAY);

                    for (i = 0; i < numZone; i++)
                    {
                        num = 3;  //3个结构体
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);

                        Std_Memcpy(&ZoneTab,
                                   &uBuf[sizeof(sTimeZoneTable_TypeDef)*i],
                                   sizeof(sTimeZoneTable_TypeDef));

                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &ZoneTab.Month, NULL, DTYPE_UINT8);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &ZoneTab.Day, NULL, DTYPE_UINT8);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &ZoneTab.nPOTTable, NULL, DTYPE_UINT8);
                    }
                }
                else if (pOadAys->elementIndex <= MAX_TIMEZONE)  //
                {
                    i = pOadAys->elementIndex - 1;

                    num = 3;  //3个结构体
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);

                    Std_Memcpy(&ZoneTab,
                               &uBuf[sizeof(sTimeZoneTable_TypeDef)*i],
                               sizeof(sTimeZoneTable_TypeDef));

                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &ZoneTab.Month, NULL, DTYPE_UINT8);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &ZoneTab.Day, NULL, DTYPE_UINT8);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &ZoneTab.nPOTTable, NULL, DTYPE_UINT8);
                }
                else
                {
                    res = ERROR;
                }

                break;
            case 0x4016:
            case 0x4017:   //当前套、备用套时段表
                fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_nPOTTable, &numPOTTab, 1);
                if (numPOTTab > MAX_POTTABLE)
                {
                    numPOTTab = MAX_POTTABLE;
                }

                fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_nDayPOT, &numDayPOT, 1);
                if (numDayPOT > MAX_POT)
                {
                    numDayPOT = MAX_POT;
                }

                if (pOadAys->elementIndex == 0) //读取全部元素
                {
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &numPOTTab, NULL, DTYPE_ARRAY);

                    for (j = 0; j < numPOTTab; j++)
                    {
                        OffAddr = (u16)(j + (pOadAys->OIB2 - 6) * 8) * 14 * sizeof(sPOTTable_TypeDef) + sizeof(sDate_time_s_TypeDef); //计算读取时段表偏移地址

                        fnFile_Read(FileId_RatePara,
                                    FileItemInfoOffAddr_RatePara_POTTablePara + OffAddr,
                                    uBuf,
                                    14 * sizeof(sPOTTable_TypeDef));

                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &numDayPOT, NULL, DTYPE_ARRAY);

                        for (i = 0; i < numDayPOT; i++)
                        {
                            num = 3;  //3个结构体
                            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);

                            Std_Memcpy(&POTTab, &uBuf[sizeof(sPOTTable_TypeDef)*i], sizeof(sPOTTable_TypeDef));

                            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &POTTab.Hour, NULL, DTYPE_UINT8);
                            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &POTTab.Minute, NULL, DTYPE_UINT8);
                            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &POTTab.Fl, NULL, DTYPE_UINT8);
                        }
                    }
                }
                else if (pOadAys->elementIndex <= MAX_POTTABLE)
                {
                    j = pOadAys->elementIndex - 1;
                    OffAddr = (u16)(j + (pOadAys->OIB2 - 6) * 8) * 14 * sizeof(sPOTTable_TypeDef) + sizeof(sDate_time_s_TypeDef); //计算读取时段表偏移地址
                    fnFile_Read(FileId_RatePara,
                                FileItemInfoOffAddr_RatePara_POTTablePara + OffAddr,
                                uBuf,
                                14 * sizeof(sPOTTable_TypeDef));

                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &numDayPOT, NULL, DTYPE_ARRAY);

                    for (i = 0; i < numDayPOT; i++)
                    {
                        num = 3;  //3个结构体
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);

                        Std_Memcpy(&POTTab, &uBuf[sizeof(sPOTTable_TypeDef)*i], sizeof(sPOTTable_TypeDef));

                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &POTTab.Hour, NULL, DTYPE_UINT8);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &POTTab.Minute, NULL, DTYPE_UINT8);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &POTTab.Fl, NULL, DTYPE_UINT8);
                    }
                }
                else
                {
                    res = ERROR;
                }
                break;
                #if(METERTYPE==2)
            case 0x4018:
            case 0x4019:   //费率电价

                if (pOadAys->elementIndex == 0) //读取全部元素
                {
                }
                else if (pOadAys->elementIndex <= Bkgrd.PubData.nFl)  //
                {
                }
                else
                {
                    res = ERROR;
                }
                break;

            case 0x4018:
            case 0x4019:   //阶梯电价 待完善

                break;
                #endif
            default:
                if ((pOadAys->AtrIndex == 2) && (pOadAys->elementIndex == 0))
                {
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf,
                                                       pRetLen,
                                                       uBuf,
                                                       (u16 *)&PARA_VAR_Item[line].Len,
                                                       PARA_VAR_Item[line].Atr_type);
                }
                else
                {
                    res = ERROR;
                }
                break;
        }
    }
    else
    {
        res = ERROR;
    }

    return  res ;
}

/*********************************************************************************************************
** Function name:   fnGet_EvtPara
** Descriptions:    读取class=7,事件记录除属性2以外的数据
** input parameters:  OAD:OAD读取此OAD对应的内容
** output parameters:   pRetBuf:读取到的数据.   pRetLen:读取数据内容应答长度
** Returned value:读取成功或失败结果
*********************************************************************************************************/
u8 fnGet_EvtPara(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen, u8  *blockRsp)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    sEvtRcdHead_TypeDef  headData;
    sContextList_TypeDef    tmplist;

    u16 OIA_B = (OAD >> 16 & 0xFFFF), num_u16;
    u8 i, num, item = FileItemInfoNum_Evt_Max, class_id = 0;
    //u8 temp1,  Offset;

    item = fnGet_EvtItem(OIA_B, &class_id);
    if ((item >= FileItemInfoNum_Evt_Max) || (class_id != ITEMCLASS7))
    {
        return ERROR;
    }

    if (pOadAys->AtrIndex == 3)   //读取关联对象属性表
    {
        fnFile_Read(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[item].OffAddr, uBuf, FileItemInfo_EvtCtxlist[item].Len);

        num = *uBuf ++; //关联对象属性表OAD个数
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&num, NULL, DTYPE_ARRAY);
        uBuf += 2;  //2//recordlen
        for (i = 0; i < num; i++)
        {
            Std_Memcpy(&tmplist, uBuf, sizeof(sContextList_TypeDef));
            uBuf += sizeof(sContextList_TypeDef);

            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tmplist.OAD, NULL, DTYPE_OAD);
        }
    }
    else if (pOadAys->AtrIndex == 4) //当前记录数
    {
        fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, &headData, FileItemInfo_EvtRcdHead[item].Len);

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventCnt, NULL, DTYPE_UINT16);
    }
    else if (pOadAys->AtrIndex == 5) //最大记录数
    {
        num_u16 = (u16)MAX_EVRECORD_TABLE[item];
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&num_u16, NULL, DTYPE_UINT16);
    }
    else if (pOadAys->AtrIndex == 6) //配置参数
    {
        //      if( FileItemInfo_EvtCfgPara[item].Len == 0 )
        //          return ERROR;
        //
        //      fnFile_Read(FileId_EvtCfgPara, FileItemInfo_EvtCfgPara[item].OffAddr, uBuf ,FileItemInfo_EvtCfgPara[item].Len );
        //  #if(nPhs==ThreePhs)
        //      //----正向，反向，无功需量超限格式一样----
        //      if( (item == FileItemInfoNum_Evt_PtOverNeed)
        //          ||(item == FileItemInfoNum_Evt_NtOverNeed)  )
        //      {
        //          if( pOadAys->elementIndex == 0)
        //          {
        //              num = 2; //2个结构体
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT32);
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT32_Len, NULL, DTYPE_UINT8);
        //          }
        //          else if( pOadAys->elementIndex == 1)
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT32);
        //          else if( pOadAys->elementIndex == 2)
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT32_Len, NULL, DTYPE_UINT8);
        //          else
        //              return ERROR;
        //      }
        //      //----不平衡事件格式一样---
        //      else if(    (item == FileItemInfoNum_Evt_UnblVol)
        //              ||(item == FileItemInfoNum_Evt_UnblCur)
        //              ||(item == FileItemInfoNum_Evt_OverUnblCur) )
        //      {
        //          if( pOadAys->elementIndex == 0)
        //          {
        //              num = 2; //2个结构体
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_INT16);
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_INT16_Len, NULL, DTYPE_UINT8);
        //          }
        //          else if( pOadAys->elementIndex == 1)
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_INT16);
        //          else if( pOadAys->elementIndex == 2)
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_INT16_Len, NULL, DTYPE_UINT8);
        //          else
        //              return ERROR;
        //      }
        //
        //      //----零线电流异常----
        //      else if(item == FileItemInfoNum_Evt_NLineErr)
        //  #else
        ////        if(item == FileItemInfoNum_Evt_NLineErr)
        //  #endif
        //      {
        //          if( pOadAys->elementIndex == 0)
        //          {
        //              num = 3; //2个结构体
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_INT32);
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_INT32_Len, NULL, DTYPE_UINT16);
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_INT32_Len+DTYPE_UINT16_Len, NULL, DTYPE_UINT8);
        //
        //          }
        //          else if( pOadAys->elementIndex == 1)
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_INT32);
        //          else if( pOadAys->elementIndex == 2)
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_INT32_Len, NULL, DTYPE_UINT16);
        //          else if( pOadAys->elementIndex == 3)
        //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_INT32_Len+DTYPE_UINT16_Len, NULL, DTYPE_UINT8);
        //          else
        //              return ERROR;
        //      }
        //      else  //----只有延时事件一个参数-----
        {
            //          if( (pOadAys->elementIndex == 0)||(pOadAys->elementIndex == 1) )
            {
                num = 1; //--1个结构体
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                //              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT8);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);
            }
            //          else
            //              return ERROR;
        }
    }
    else if (pOadAys->AtrIndex == 7) //当前记录表
    {
        if ((item == FileItemInfoNum_Evt_PowDn) || (item == FileItemInfoNum_Evt_OpenCover)
            || (item == FileItemInfoNum_Evt_OpenTail) || (item == FileItemInfoNum_Evt_MngPlug))
        {
            if ((pOadAys->elementIndex == 0) || (pOadAys->elementIndex == 1))
            {
                fnEvent_WriteSumTime(item, 0);

                fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, &headData, sizeof(sEvtRcdHead_TypeDef));

                num = 1; //1个
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
                num = 2; //2个结构体
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);
                num = 2; //2个结构体
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventTime, NULL, DTYPE_UINT32);
            }
            else
            {
                return ERROR;
            }
        }
        //      #if(nPhs==ThreePhs)
        //      else if(item == FileItemInfoNum_Evt_PrgQ)
        //      {
        //          if( pOadAys->elementIndex == 0)
        //          {
        //                  num = 2; //1个
        //                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
        //
        //                  num = 2; //2个结构体
        //                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);

        //                  num = 0;  //无功1发生源固定为0
        //                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ENUM);
        //                  num = 2; //2个结构体
        //                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
        //                  fnFile_Read(FileId_HighState , FileItemInfoOffAddr_HighState_PrgQ1_Cnt , (u8 *)&headData.EventSumCnt , 4);
        //                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
        //                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);

        //                  num = 2; //2个结构体
        //                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);

        //                  num = 1;  //无功2发生源固定为1
        //                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ENUM);
        //                  num = 2; //2个结构体
        //                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
        //                  fnFile_Read(FileId_HighState , FileItemInfoOffAddr_HighState_PrgQ2_Cnt , (u8 *)&headData.EventSumCnt , 4);
        //                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
        //                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);
        //
        //          }
        //          else
        //              return ERROR;
        //      }
        //      #endif
        else
        {
            if ((pOadAys->elementIndex == 0) || (pOadAys->elementIndex == 1))
            {
                fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, &headData, sizeof(sEvtRcdHead_TypeDef));

                num = 1; //1个
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
                num = 2; //2个结构体
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);
                num = 2; //2个结构体
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);  //class7除掉电事件记录外，无事件累计时间
            }
            else
            {
                return ERROR;
            }
        }
    }
    //  else if( pOadAys->AtrIndex == 8) //上报标识
    //  {
    //      Offset = item/8;
    //      i = item%8;
    //      //-----------------------
    //      if(((EvtRptData.Para.RptFlagHappen[Offset]>>i)&0x01)==0x01)  //发生上报
    //          temp1 = 0x01;
    //      else
    //          temp1 = 0x00;
    //
    //      if(((EvtRptData.Para.RptFlagEnd[Offset]>>i)&0x01)==0x01)  //结束上报
    //          temp1 |= 0x02;
    //      else
    //          temp1 &= 0x01;
    //
    //      pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1 , NULL , DTYPE_ENUM);

    //  }
    //  else if( pOadAys->AtrIndex == 9) //有效标识
    //  {
    //      temp1 = 0x01;
    //
    //      pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1 , NULL , DTYPE_BOOLEAN);

    //  }
    else if (pOadAys->AtrIndex == 10) //时间状态记录表
    {
        fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, &headData, FileItemInfo_EvtRcdHead[item].Len);

        //      if( (item == FileItemInfoNum_Evt_OpenCover) || (item == FileItemInfoNum_Evt_OpenTail) )
        {
            if (fnJudge_Zero((u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef)))
            {
                if (headData.EventSumCnt > 1)
                {
                    u16 recordlen, maxcnt_u16;;
                    u32 EvtCnt, OffAddr;
                    u8  *DataBuf, *EvtData;

                    DataBuf = (u8 *)fnBufTemp_Alloc(512);

                    EvtData = (u8 *)fnBufTemp_Alloc(512);

                    if ((EvtData != NULL) && (DataBuf != NULL))
                    {
                        Std_Memset(DataBuf, 0, 512);
                        Std_Memset(EvtData, 0, 512);

                        //-----获取事件记录长度---------------

                        OffAddr = FileItemInfo_EvtCtxlist[item].OffAddr;
                        fnFile_Read(FileId_EvtCtxlist, OffAddr + 1, DataBuf, 2);
                        Std_Memcpy((u8 *)&recordlen, DataBuf, 2);

                        maxcnt_u16 = MAX_EVRECORD_TABLE[item];
                        EvtCnt = headData.EventSumCnt - 1;

                        if (EvtCnt % maxcnt_u16)
                        {
                            OffAddr = ((EvtCnt % maxcnt_u16) - 1) * (u32)recordlen;
                        }
                        else
                        {
                            OffAddr = (maxcnt_u16 - 1) * (u32)recordlen;
                        }

                        OffAddr += FileItemInfo_EvtRecord[item].OffAddr;

                        fnFile_Read(FileId_EvtRecord, OffAddr, EvtData, recordlen);

                        // 使用上2次记录的结束时间
                        memcpy(&headData.EventEndTime.second, EvtData + 11, 7);

                        fnBufTemp_Free(DataBuf);
                        fnBufTemp_Free(EvtData);
                    }
                }
            }
        }

        if ((pOadAys->elementIndex == 0) || (pOadAys->elementIndex == 1))
        {
            num = 1; //1个
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
            num = 2; //2个结构体
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);
            num = 2; //2个结构体
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
            if (fnJudge_Zero((u8 *)&headData.EventStartTime, sizeof(sDate_time_s_TypeDef)))     //时间为全0时应答null
            {
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);
            }
            else
            {
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventStartTime, NULL, DTYPE_DATETIME_S);
            }

            if (fnJudge_Zero((u8 *)&headData.EventEndTime, sizeof(sDate_time_s_TypeDef)))     //时间为全0时应答null
            {
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);
            }
            else
            {
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventEndTime, NULL, DTYPE_DATETIME_S);
            }
        }
        else
        {
            return ERROR;
        }
    }
    //  else if( pOadAys->AtrIndex == 11) //上报方式
    //  {
    //      Offset = item/8;
    //      i = item%8;
    //      if(((EvtRptData.Para.RptMode[Offset]>>i)&0x01)==0x01)  //发生上报
    //          temp1 = 0x01;
    //      else
    //          temp1 = 0x00;
    //
    //      pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1 , NULL , DTYPE_ENUM);

    //  }
    else
    {
        return ERROR;
    }

    return  SUCCESS ;
}

/*********************************************************************************************************
** Function name:   fnGet_PhsEvtPara
** Descriptions:    读取class=24,事件记录除属性6~9以外的数据，分项事件
** input parameters:  OAD:OAD读取此OAD对应的内容
** output parameters:   pRetBuf:读取到的数据.   pRetLen:读取数据内容应答长度
** Returned value:读取成功或失败结果
*********************************************************************************************************/
//#if(nPhs==ThreePhs)
//u8 fnGet_PhsEvtPara(u32  OAD, u8  *uBuf, u8 *pRetBuf,u16 *pRetLen, u8  *blockRsp)
//{
//  OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
//  sEvtRcdHead_TypeDef  headData , headData2 , headData3;
//  sContextList_TypeDef    tmplist;
//
//  u16 OIA_B = (OAD >> 16 & 0xFFFF), num_u16;
//  u8 i,num, num2, item = FileItemInfoNum_Evt_Max, class_id = 0;
//  u32  offset = 0;
//  u8 temp1 ;

//  item = fnGet_EvtItem( OIA_B, &class_id );
//  if( (item >= FileItemInfoNum_Evt_Max)||(class_id != ITEMCLASS24) )
//      return ERROR;

//  if( pOadAys->AtrIndex == 2 )  //读取关联对象属性表
//  {
//      fnFile_Read(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[item].OffAddr, uBuf, FileItemInfo_EvtCtxlist[item].Len  );

//      num = *uBuf ++; //关联对象属性表OAD个数
//      pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num,NULL,DTYPE_ARRAY);
//      uBuf += 2;  //2//recordlen
//      for(i = 0; i < num; i++)
//      {
//          Std_Memcpy(&tmplist,uBuf,sizeof(sContextList_TypeDef));
//          uBuf +=sizeof(sContextList_TypeDef);
//
//          pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tmplist.OAD,NULL,DTYPE_OAD);
//
//      }

//  }
//  else if( pOadAys->AtrIndex == 3) //当前记录数
//  {
//      num = 4; //4个结构体
//      pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
//
//      if( (item == FileItemInfoNum_Evt_QtOverNeed)
//        ||(item == FileItemInfoNum_Evt_OverPf) )  //记录表1
//       {
//          fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr + offset, (u8 *)&headData , sizeof(sEvtRcdHead_TypeDef) );

//          pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventCnt, NULL, DTYPE_UINT16);

//          offset += sizeof(sEvtRcdHead_TypeDef);
//       }
//
//       else
//       {    //-----无总事件记录，记录表1 一直为0-------------
//          headData.EventCnt = 0;
//          pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventCnt, NULL, DTYPE_UINT16);
//       }
//       //-------记录表2,3,4----------------
//
//      for(i = 1; i < num; i++)
//      {
//          fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr + offset, (u8 *)&headData , sizeof(sEvtRcdHead_TypeDef) );

//          pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventCnt, NULL, DTYPE_UINT16);

//          offset += sizeof(sEvtRcdHead_TypeDef);
//      }
//
//
//  }
//
//  else if( pOadAys->AtrIndex == 4) //最大记录数
//  {
//      num_u16 = ( u16 )MAX_EVRECORD_TABLE[item];
//      pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&num_u16,NULL,DTYPE_UINT16);

//  }
//  else if( pOadAys->AtrIndex == 5) //配置参数
//  {
//      if( FileItemInfo_EvtCfgPara[item].Len == 0 )
//          return ERROR;
//
//      fnFile_Read(FileId_EvtCfgPara, FileItemInfo_EvtCfgPara[item].OffAddr, uBuf , FileItemInfo_EvtCfgPara[item].Len );
//
//      if(item == FileItemInfoNum_Evt_LossVol) //失压
//      {
//          if( pOadAys->elementIndex == 0)
//          {
//              num = 4; //4个结构体
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
//
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT16);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT16_Len, NULL, DTYPE_UINT16);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 2*DTYPE_UINT16_Len, NULL, DTYPE_INT32);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 2*DTYPE_UINT16_Len + DTYPE_INT32_Len, NULL, DTYPE_UINT8);
//          }
//          else if( pOadAys->elementIndex == 1)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT16);
//          else if( pOadAys->elementIndex == 2)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT16_Len, NULL, DTYPE_UINT16);
//          else if( pOadAys->elementIndex == 3)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 2*DTYPE_UINT16_Len, NULL, DTYPE_INT32);
//          else if( pOadAys->elementIndex == 4)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 2*DTYPE_UINT16_Len + DTYPE_INT32_Len, NULL, DTYPE_UINT8);
//          else
//              return ERROR;
//      }
//
//      else if(    (item == FileItemInfoNum_Evt_LackVol)
//              ||(item == FileItemInfoNum_Evt_OverVol) )
//      {
//          if( pOadAys->elementIndex == 0)
//          {
//              num = 2; //2个结构体
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT16);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT16_Len, NULL, DTYPE_UINT8);
//          }
//          else if( pOadAys->elementIndex == 1)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_INT16);
//          else if( pOadAys->elementIndex == 2)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_INT16_Len, NULL, DTYPE_UINT8);
//          else
//              return ERROR;
//      }
//      else if(    (item == FileItemInfoNum_Evt_LossPha)
//              ||(item == FileItemInfoNum_Evt_BreakCur)    )
//      {
//          if( pOadAys->elementIndex == 0)
//          {
//              num = 3; //3个结构体
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT16);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT16_Len, NULL, DTYPE_INT32);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT16_Len + DTYPE_INT32_Len , NULL, DTYPE_UINT8);
//          }
//          else if( pOadAys->elementIndex == 1 )
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_INT16);
//          else if( pOadAys->elementIndex == 2 )
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT16_Len, NULL, DTYPE_INT32);
//          else if( pOadAys->elementIndex == 3 )
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT16_Len + DTYPE_INT32_Len , NULL, DTYPE_UINT8);
//          else
//              return ERROR;
//      }
//      else if( item == FileItemInfoNum_Evt_LossCur )  //
//      {
//          if( pOadAys->elementIndex == 0)
//          {
//              num = 4; //4个结构体
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
//
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT16);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT16_Len, NULL, DTYPE_INT32);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT16_Len + DTYPE_INT32_Len, NULL, DTYPE_INT32);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT16_Len + 2*DTYPE_INT32_Len, NULL, DTYPE_UINT8);
//          }
//          else if( pOadAys->elementIndex == 1)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT16);
//          else if( pOadAys->elementIndex == 2)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT16_Len, NULL, DTYPE_INT32);
//          else if( pOadAys->elementIndex == 3)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT16_Len + DTYPE_INT32_Len, NULL, DTYPE_INT32);
//          else if( pOadAys->elementIndex == 4)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT16_Len + 2*DTYPE_INT32_Len, NULL, DTYPE_UINT8);
//          else
//              return ERROR;
//      }
//      else if(    (item == FileItemInfoNum_Evt_OverCur)
//              ||(item == FileItemInfoNum_Evt_InSwimPw)
//              ||(item == FileItemInfoNum_Evt_OverPw)  )
//      {
//          if( pOadAys->elementIndex == 0)
//          {
//              num = 2; //2个结构体
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_INT32);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_INT32_Len, NULL, DTYPE_UINT8);
//          }
//          else if( pOadAys->elementIndex == 1)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_INT32);
//          else if( pOadAys->elementIndex == 2)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_INT32_Len, NULL, DTYPE_UINT8);
//          else
//              return ERROR;
//      }
//      else if( item == FileItemInfoNum_Evt_QtOverNeed )
//      {
//          if( pOadAys->elementIndex == 0)
//          {
//              num = 2; //2个结构体
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT32);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT32_Len, NULL, DTYPE_UINT8);
//          }
//          else if( pOadAys->elementIndex == 1)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT32);
//          else if( pOadAys->elementIndex == 2)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_UINT32_Len, NULL, DTYPE_UINT8);
//          else
//              return ERROR;
//      }
//      else if( item == FileItemInfoNum_Evt_OverPf )
//      {
//          if( pOadAys->elementIndex == 0)
//          {
//              num = 2; //2个结构体
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_INT16);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_INT16_Len, NULL, DTYPE_UINT8);
//          }
//          else if( pOadAys->elementIndex == 1)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_INT16);
//          else if( pOadAys->elementIndex == 2)
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_INT16_Len, NULL, DTYPE_UINT8);
//          else
//              return ERROR;
//      }

//  }
//  else if( pOadAys->AtrIndex == 10) //当前记录表
//  {
//      if(pOadAys->elementIndex == 0)
//      {
//          fnEvent_WriteSumTime(item , 0);
//          fnEvent_WriteSumTime(item , 1);
//          fnEvent_WriteSumTime(item , 2);

//          if(item == FileItemInfoNum_Evt_OverPf)
//              fnEvent_WriteSumTime(item , 3);
//
//          fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, uBuf ,FileItemInfo_EvtRcdHead[item].Len );

//          num = 4; //4个
//          pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
//
//          if(item == FileItemInfoNum_Evt_QtOverNeed)
//           {
//              for(i = 0; i < num; i++)
//              {
//                  Std_Memcpy(&headData,uBuf,sizeof(sEvtRcdHead_TypeDef));
//                  uBuf +=sizeof(sEvtRcdHead_TypeDef);
//
//                  num2 = 2;
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num2, NULL, DTYPE_STRUCTURE);
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);
//              }
//           }
//           else
//           {
//
//              for(i = 0; i < num; i++)
//              {
//                  if( (item < FileItemInfoNum_Evt_QtOverNeed)&&(i == 0) )  //-----无总事件记录，记录表1 一直为0----
//                      Std_Memset((u8 *)&headData,0x00,sizeof(sEvtRcdHead_TypeDef));
//                  else
//                  {
//                      Std_Memcpy(&headData,uBuf,sizeof(sEvtRcdHead_TypeDef));
//                      uBuf +=sizeof(sEvtRcdHead_TypeDef);
//                  }
//
//                  num2 = 2;
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num2,NULL, DTYPE_STRUCTURE);
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventTime, NULL, DTYPE_UINT32);
//              }
//           }
//
//
//      }
//      else if(pOadAys->elementIndex == 1)
//      {
//          if(item == FileItemInfoNum_Evt_QtOverNeed) //Q1
//          {
//              fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, (u8 *)&headData , sizeof(sEvtRcdHead_TypeDef) );
//              num2 = 2;
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num2, NULL, DTYPE_STRUCTURE);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);  //事件记录累计时间为NULL

//          }
//          else if(item == FileItemInfoNum_Evt_OverPf)  //总
//          {
//              fnEvent_WriteSumTime(item , pOadAys->elementIndex - 1);
//              fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, (u8 *)&headData , sizeof(sEvtRcdHead_TypeDef) );
//              num2 = 2;
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num2, NULL, DTYPE_STRUCTURE);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventTime, NULL, DTYPE_UINT32);
//          }
//          else
//          {
//              //-----无总事件记录，记录表1 -------------
//              Std_Memset((u8 *)&headData,0x00,sizeof(sEvtRcdHead_TypeDef));
//              num2 = 2;
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num2, NULL, DTYPE_STRUCTURE);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventTime, NULL, DTYPE_UINT32);
//          }
//
//      }
//      else
//      {
//          if(item == FileItemInfoNum_Evt_QtOverNeed) //Q2~Q4
//          {
//              offset = (pOadAys->elementIndex - 1) * sizeof(sEvtRcdHead_TypeDef);
//              fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr + offset, (u8 *)&headData , sizeof(sEvtRcdHead_TypeDef) );
//              num2 = 2;
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num2, NULL, DTYPE_STRUCTURE);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);  //事件记录累计时间为NULL

//          }
//          else if(item == FileItemInfoNum_Evt_OverPf) //A/b/c
//          {
//              offset = (pOadAys->elementIndex - 1) * sizeof(sEvtRcdHead_TypeDef);
//              fnEvent_WriteSumTime(item , pOadAys->elementIndex - 1);
//              fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr + offset, (u8 *)&headData , sizeof(sEvtRcdHead_TypeDef) );
//              num2 = 2;
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num2, NULL, DTYPE_STRUCTURE);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventTime, NULL, DTYPE_UINT32);
//          }
//          else
//          {
//              offset = (pOadAys->elementIndex - 2) * sizeof(sEvtRcdHead_TypeDef);
//              fnEvent_WriteSumTime(item , pOadAys->elementIndex - 2);
//              fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr + offset, (u8 *)&headData , sizeof(sEvtRcdHead_TypeDef) );
//              num2 = 2;
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num2, NULL, DTYPE_STRUCTURE);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventTime, NULL, DTYPE_UINT32);
//          }
//
//      }
//
//  }
//  else if( pOadAys->AtrIndex == 11) //上报标识
//  {
//      offset = item/8;
//      i = item%8;
//      //-----------------------

//      if(((EvtRptData.Para.RptFlagHappen[offset]>>i)&0x01)==0x01)  //发生上报
//          temp1 = 0x01;
//      else
//          temp1 = 0x00;
//
//      if(((EvtRptData.Para.RptFlagEnd[offset]>>i)&0x01)==0x01)  //结束上报
//          temp1 |= 0x02;
//      else
//          temp1 &= 0x01;
//
//      pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1 , NULL , DTYPE_ENUM);

//  }
//  else if( pOadAys->AtrIndex == 12) //有效标识
//  {
//      temp1 = 0x01;
//
//      pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1 , NULL , DTYPE_BOOLEAN);

//  }
//  else if( pOadAys->AtrIndex == 13)
//  {
//      if(item == FileItemInfoNum_Evt_LossVol)   //失压统计
//      {
//          if( (pOadAys->elementIndex == 0)||(pOadAys->elementIndex == 2) )
//          {
//              fnEvent_WriteSumTime(item , 0);
//              fnEvent_WriteSumTime(item , 1);
//              fnEvent_WriteSumTime(item , 2);
//          }
//
//          fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, uBuf ,FileItemInfo_EvtRcdHead[item].Len );
//          Std_Memcpy(&headData,uBuf,sizeof(sEvtRcdHead_TypeDef));
//          uBuf +=sizeof(sEvtRcdHead_TypeDef);
//          Std_Memcpy(&headData2,uBuf , sizeof(sEvtRcdHead_TypeDef));
//          uBuf +=sizeof(sEvtRcdHead_TypeDef);
//          Std_Memcpy(&headData3,uBuf , sizeof(sEvtRcdHead_TypeDef));
//          //找出最近时间
//          if(fnDFCompData((u8 *)&headData.EventStartTime, (u8 *)&headData2.EventStartTime, sizeof(sDate_time_s_TypeDef))== 1)
//          {
//              if(fnDFCompData((u8 *)&headData.EventStartTime, (u8 *)&headData3.EventStartTime, sizeof(sDate_time_s_TypeDef))!= 1)
//                  Std_Memcpy((u8 *)&headData.EventStartTime,(u8 *)&headData3.EventStartTime , 2*sizeof(sDate_time_s_TypeDef));
//          }
//          else
//          {
//              if(fnDFCompData((u8 *)&headData2.EventStartTime, (u8 *)&headData3.EventStartTime, sizeof(sDate_time_s_TypeDef))== 1)
//                  Std_Memcpy((u8 *)&headData.EventStartTime,(u8 *)&headData2.EventStartTime , 2*sizeof(sDate_time_s_TypeDef));
//              else
//                  Std_Memcpy((u8 *)&headData.EventStartTime,(u8 *)&headData3.EventStartTime , 2*sizeof(sDate_time_s_TypeDef));

//          }
//          headData.EventSumCnt += (headData2.EventSumCnt + headData3.EventSumCnt);
//          headData.EventTime += (headData2.EventTime + headData3.EventTime);

//          if(pOadAys->elementIndex == 0)
//          {
//              num2 = 4;
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num2, NULL, DTYPE_STRUCTURE);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventTime, NULL, DTYPE_UINT32);
//
//              if(fnJudge_Zero( (u8 *)&headData.EventStartTime , sizeof(sDate_time_s_TypeDef) ) )  //时间为全0时应答null
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL , NULL , DTYPE_NONE);
//              else
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventStartTime, NULL, DTYPE_DATETIME_S);
//
//              if(fnJudge_Zero( (u8 *)&headData.EventEndTime , sizeof(sDate_time_s_TypeDef) ) )  //时间为全0时应答null
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL , NULL , DTYPE_NONE);
//              else
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventEndTime, NULL, DTYPE_DATETIME_S);
//          }
//          else if(pOadAys->elementIndex == 1)
//          {
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
//          }
//          else if(pOadAys->elementIndex == 2)
//          {
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventTime, NULL, DTYPE_UINT32);
//          }
//          else if(pOadAys->elementIndex == 3)
//          {
//              if(fnJudge_Zero( (u8 *)&headData.EventStartTime , sizeof(sDate_time_s_TypeDef) ) )  //时间为全0时应答null
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL , NULL , DTYPE_NONE);
//              else
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventStartTime, NULL, DTYPE_DATETIME_S);
//          }
//          else if(pOadAys->elementIndex == 4)
//          {
//              if(fnJudge_Zero( (u8 *)&headData.EventEndTime , sizeof(sDate_time_s_TypeDef) ) )  //时间为全0时应答null
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL , NULL , DTYPE_NONE);
//              else
//                  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventEndTime, NULL, DTYPE_DATETIME_S);

//          }
//          else
//              return ERROR;
//
//      }
//      else
//          return ERROR;

//  }
//
//  else if( pOadAys->AtrIndex == 14) //时间状态记录表
//  {
//      fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, uBuf, FileItemInfo_EvtRcdHead[item].Len );
//
//      if( (item == FileItemInfoNum_Evt_QtOverNeed)
//        ||(item == FileItemInfoNum_Evt_OverPf) )
//      {
//          num = 4; //
//      }
//      else
//      {
//          num = 3; //
//      }
//      pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
//
//      for(i = 0; i < num; i++)
//      {
//          Std_Memcpy(&headData,uBuf,sizeof(sEvtRcdHead_TypeDef));
//          uBuf +=sizeof(sEvtRcdHead_TypeDef);
//
//          num2 = 2;
//          pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num2, NULL, DTYPE_STRUCTURE);
//          if(fnJudge_Value((u8 *)&headData.EventStartTime, 0x00,7))
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);
//          else
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventStartTime, NULL, DTYPE_DATETIME_S);

//          if(fnJudge_Value((u8 *)&headData.EventEndTime, 0x00,7))
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);
//          else
//              pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventEndTime, NULL, DTYPE_DATETIME_S);
//      }
//

//  }
//  else if( pOadAys->AtrIndex == 15) //上报模式
//  {
//      offset = item/8;
//      i = item%8;
//
//      if(((EvtRptData.Para.RptMode[offset]>>i)&0x01)==0x01)  //发生上报
//          temp1 = 0x01;
//      else
//          temp1 = 0x00;
//
//      pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1 , NULL , DTYPE_ENUM);

//  }
//  else
//      return ERROR;
//
//  return  SUCCESS ;
//}
//#else
//--------分相事件-单相表只需支持过流事件记录------------------------------
u8 fnGet_PhsEvtPara(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen, u8  *blockRsp)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    sEvtRcdHead_TypeDef  headData ;
    sContextList_TypeDef    tmplist;

    u16 OIA_B = (OAD >> 16 & 0xFFFF), num_u16;
    u8 i, num, num2, item = FileItemInfoNum_Evt_Max;
    u32  offset = 0;
    u8 temp1 ;

    if (OIA_B != 0x3005)  //只支持过流事件
    {
        return ERROR;
    }

    //  item = FileItemInfoNum_Evt_OverCur;
    if (pOadAys->AtrIndex == 2)   //读取关联对象属性表
    {
        fnFile_Read(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[item].OffAddr, uBuf, FileItemInfo_EvtCtxlist[item].Len);

        num = *uBuf ++; //关联对象属性表OAD个数
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
        uBuf += 2;  //2//recordlen
        for (i = 0; i < num; i++)
        {
            Std_Memcpy(&tmplist, uBuf, sizeof(sContextList_TypeDef));
            uBuf += sizeof(sContextList_TypeDef);

            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tmplist.OAD, NULL, DTYPE_OAD);
        }
    }
    else if (pOadAys->AtrIndex == 3) //当前记录数
    {
        num = 4; //4个结构体
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);

        //-----无总事件记录，记录表1 一直为0-------------
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventCnt, NULL, DTYPE_NONE);

        //-------记录表----------------
        fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, (u8 *)&headData, sizeof(sEvtRcdHead_TypeDef));

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventCnt, NULL, DTYPE_UINT16);

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventCnt, NULL, DTYPE_NONE);

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventCnt, NULL, DTYPE_NONE);
    }
    else if (pOadAys->AtrIndex == 4) //最大记录数
    {
        num_u16 = (u16)MAX_EVRECORD_TABLE[item];
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&num_u16, NULL, DTYPE_UINT16);
    }
    else if (pOadAys->AtrIndex == 5) //配置参数
    {
        fnFile_Read(FileId_EvtCfgPara, FileItemInfo_EvtCfgPara[item].OffAddr, uBuf, FileItemInfo_EvtCfgPara[item].Len);

        if (pOadAys->elementIndex == 0)
        {
            num = 2; //2个结构体
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_INT32);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_INT32_Len, NULL, DTYPE_UINT8);
        }
        else if (pOadAys->elementIndex == 1)
        {
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_INT32);
        }
        else if (pOadAys->elementIndex == 2)
        {
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + DTYPE_INT32_Len, NULL, DTYPE_UINT8);
        }
        else
        {
            return ERROR;
        }
    }
    else if (pOadAys->AtrIndex == 10) //当前记录表
    {
        if (pOadAys->elementIndex == 0)
        {
            fnEvent_WriteSumTime(item, 0);

            fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, uBuf, FileItemInfo_EvtRcdHead[item].Len);

            num = 4; //4个
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);

            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventCnt, NULL, DTYPE_NONE);

            Std_Memcpy(&headData, uBuf, sizeof(sEvtRcdHead_TypeDef));

            num2 = 2;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num2, NULL, DTYPE_STRUCTURE);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventSumCnt, NULL, DTYPE_UINT32);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventTime, NULL, DTYPE_UINT32);

            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventCnt, NULL, DTYPE_NONE);

            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventCnt, NULL, DTYPE_NONE);
        }
    }
    else if (pOadAys->AtrIndex == 11) //上报标识
    {
        offset = item / 8;
        i = item % 8;
        //-----------------------

        if (((EvtRptData.Para.RptFlagHappen[offset] >> i) & 0x01) == 0x01) //发生上报
        {
            temp1 = 0x01;
        }
        else
        {
            temp1 = 0x00;
        }

        if (((EvtRptData.Para.RptFlagEnd[offset] >> i) & 0x01) == 0x01) //结束上报
        {
            temp1 |= 0x02;
        }
        else
        {
            temp1 &= 0x01;
        }

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1, NULL, DTYPE_ENUM);
    }
    else if (pOadAys->AtrIndex == 12) //有效标识
    {
        temp1 = 0x01;

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1, NULL, DTYPE_BOOLEAN);
    }
    else if (pOadAys->AtrIndex == 14) //时间状态记录表
    {
        fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, uBuf, FileItemInfo_EvtRcdHead[item].Len);

        num = 4; //
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);

        Std_Memcpy(&headData, uBuf, sizeof(sEvtRcdHead_TypeDef));

        num2 = 2;
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num2, NULL, DTYPE_STRUCTURE);
        if (fnJudge_Value((u8 *)&headData.EventStartTime, 0x00, 7))
        {
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);
        }
        else
        {
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventStartTime, NULL, DTYPE_DATETIME_S);
        }

        if (fnJudge_Value((u8 *)&headData.EventEndTime, 0x00, 7))
        {
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);
        }
        else
        {
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&headData.EventEndTime, NULL, DTYPE_DATETIME_S);
        }

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL, NULL, DTYPE_NONE);
    }
    else if (pOadAys->AtrIndex == 15) //上报模式
    {
        offset = item / 8;
        i = item % 8;

        if (((EvtRptData.Para.RptMode[offset] >> i) & 0x01) == 0x01) //发生上报
        {
            temp1 = 0x01;
        }
        else
        {
            temp1 = 0x00;
        }

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1, NULL, DTYPE_ENUM);
    }
    else
    {
        return ERROR;
    }

    return  SUCCESS ;
}

//#endif
/*********************************************************************************************************
** Function name:   fnGet_FrzPara
** Descriptions:
** input parameters:  OAD:OAD读取此OAD对应的内容
** output parameters:   pRetBuf:读取到的数据.   pRetLen:读取数据内容应答长度
** Returned value:读取成功或失败结果
*********************************************************************************************************/
u8 fnGet_FrzPara(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen, u8  *blockRsp)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    sFrzCtxList_TypeDef  tmplist;

    u16 OIA_B = (OAD >> 16 & 0xFFFF);
    u8 i, oadnum, num, item = FileItemInfoNum_Frz_MAX;

    item = fnGet_FrzItem(OIA_B);
    if (item >= FileItemInfoNum_Frz_MAX)
    {
        return ERROR;
    }

    if ((pOadAys->AtrIndex == 3) && (pOadAys->AtrFeature == 0)) //读取关联对象属性表 dyf 加判属性特征AtrFeature
    {
        fnFile_Read(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[item].OffAddr, uBuf, FileItemInfo_FrzCtxlist[item].Len);

        if (pOadAys->elementIndex == 0)
        {
            oadnum = *uBuf ++; //关联对象属性表OAD个数
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&oadnum, NULL, DTYPE_ARRAY);
            uBuf += 2;  //2//recordlen

            for (i = 0; i < oadnum; i++)
            {
                Std_Memcpy(&tmplist, uBuf, sizeof(sFrzCtxList_TypeDef));
                uBuf += sizeof(sFrzCtxList_TypeDef);

                num = 3; //3//
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&num, NULL, DTYPE_STRUCTURE);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tmplist.Cycle, NULL, DTYPE_UINT16);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tmplist.OAD, NULL, DTYPE_OAD);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tmplist.Depth, NULL, DTYPE_UINT32);
            }
        }
        else    // dyf 增加对单个关联属性的处理
        {
            if (pOadAys->elementIndex <= *uBuf)
            {
                uBuf += 3;  // 关联对象属性表OAD个数1B, recordlen 2B
                uBuf += (pOadAys->elementIndex - 1) * sizeof(sFrzCtxList_TypeDef);

                Std_Memcpy(&tmplist, uBuf, sizeof(sFrzCtxList_TypeDef));

                num = 3; //3//
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&num, NULL, DTYPE_STRUCTURE);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tmplist.Cycle, NULL, DTYPE_UINT16);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tmplist.OAD, NULL, DTYPE_OAD);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tmplist.Depth, NULL, DTYPE_UINT32);
            }
            else
            {
                return ERROR;
            }
        }
    }
    else
    {
        return ERROR;
    }

    return  SUCCESS ;
}

/*********************************************************************************************************
** Function name:   fnGet_LCDPara
** Descriptions:    读取class=17,OI=0xF300 自动轮显,OI=0xF301   按键轮显参数
** input parameters:  OAD:OAD读取此OAD对应的内容
** output parameters:   pRetBuf:读取到的数据.   pRetLen:读取数据内容应答长度
** Returned value:读取成功或失败结果
*********************************************************************************************************/
u8 fnGet_LCDPara(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    u16 OIA_B = (OAD >> 16 & 0xFFFF), len_u16;
    u8 temp1, num, i;
    sDispItem_TypeDef Disptemp;
    u8  tempbuf[10];

    if (pOadAys->AtrIndex > 4)  //不允许属性大于4读取
    {
        return ERROR;
    }

    if ((OIA_B != 0xF300) && (OIA_B != 0xF301))
    {
        return ERROR;
    }

    if (pOadAys->AtrIndex == 2)  //显示对象列表
    {
        if (pOadAys->elementIndex == 0) //读取全部元素
        {
            if (OIA_B == 0xF300)
            {
                fnFile_Read(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_nCycDisp, (u8 *)&temp1, 1);
                len_u16 = (u16)temp1 * sizeof(sDispItem_TypeDef);
                fnFile_Read(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_CycDispItem, uBuf, len_u16);
            }
            else
            {
                fnFile_Read(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_nKeyDisp, (u8 *)&temp1, 1);
                len_u16 = (u16)temp1 * sizeof(sDispItem_TypeDef);
                fnFile_Read(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_KeyDispItem, uBuf, len_u16);
            }
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1, NULL, DTYPE_ARRAY);

            for (i = 0; i < temp1; i++)
            {
                Std_Memcpy(&Disptemp, uBuf, sizeof(sDispItem_TypeDef));
                uBuf += sizeof(sDispItem_TypeDef);

                num = 2;  //2/个结构体
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);

                if (Disptemp.CSD)
                {
                    tempbuf[0] = 0x01; //ROAD
                    Std_Memcpy(&tempbuf[1], &Disptemp.M_Element, 4);
                    tempbuf[5] = 0x01; //
                    Std_Memcpy(&tempbuf[6], &Disptemp.Element, 4);
                }
                else
                {
                    tempbuf[0] = 0x00; //ROAD
                    Std_Memcpy(&tempbuf[1], &Disptemp.M_Element, 4);
                }

                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &tempbuf[0], NULL, DTYPE_CSD);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &Disptemp.nDispIndex, NULL, DTYPE_UINT8);
            }
        }
        else if (pOadAys->elementIndex <= 99)
        {
            i = pOadAys->elementIndex - 1;
            len_u16 = (u16)i * sizeof(sDispItem_TypeDef);

            if (OIA_B == 0xF300)
            {
                fnFile_Read(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_CycDispItem + len_u16, &Disptemp, sizeof(sDispItem_TypeDef));
            }
            else
            {
                fnFile_Read(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_KeyDispItem + len_u16, &Disptemp, sizeof(sDispItem_TypeDef));
            }

            num = 2;  //2/个结构体
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);

            if (Disptemp.CSD)
            {
                tempbuf[0] = 0x01; //ROAD
                Std_Memcpy(&tempbuf[1], &Disptemp.M_Element, 4);
                tempbuf[5] = 0x01; //
                Std_Memcpy(&tempbuf[6], &Disptemp.Element, 4);
            }
            else
            {
                tempbuf[0] = 0x00; //ROAD
                Std_Memcpy(&tempbuf[1], &Disptemp.M_Element, 4);
            }

            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &tempbuf[0], NULL, DTYPE_CSD);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &Disptemp.nDispIndex, NULL, DTYPE_UINT8);
        }
        else
        {
            return ERROR;
        }
    }
    else if (pOadAys->AtrIndex == 3)  //显示时间
    {
        if (pOadAys->elementIndex != 0)
        {
            return ERROR;
        }

        if (OIA_B == 0xF300)
        {
            fnFile_Read(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_AutoDispTime, uBuf, 2);
        }
        else
        {
            fnFile_Read(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_KeyDispTime, uBuf, 2);
        }
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT16);
    }
    else   //显示参数
    {
        if (OIA_B == 0xF300)
        {
            fnFile_Read(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_nCycDisp, (u8 *)&temp1, 1);
        }
        else
        {
            fnFile_Read(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_nKeyDisp, (u8 *)&temp1, 1);
        }
        if (pOadAys->elementIndex == 0) //读取全部元素
        {
            num = 2;  //2/个结构体
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1, NULL, DTYPE_UINT8);  //显示参数值

            temp1 = MAX_CYCDISP;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1, NULL, DTYPE_UINT8);
        }
        else if (pOadAys->elementIndex == 1)
        {
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1, NULL, DTYPE_UINT8);
        }
        else if (pOadAys->elementIndex == 2)
        {
            temp1 = MAX_CYCDISP;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp1, NULL, DTYPE_UINT8);
        }
        else
        {
            return ERROR;
        }
    }
    return SUCCESS;
}

/*********************************************************************
* @fn      fnGet_Para  class19   0x4300 设备管理接口
*
* @brief
*
* @param
*
* @return
**********************************************************************/
u8 fnGet_DevicePara(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen,  u8  *blockRsp)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    u16 OIA_B = (OAD >> 16 & 0xFFFF), len;
    u8 num; // dyf del i
    //u8 ch[3];

    if (OIA_B != 0x4300)
    {
        return ERROR;
    }

    if (pOadAys->AtrIndex == 2)  //设备描述符
    {
        if (pOadAys->elementIndex != 0)
        {
            return ERROR;
        }
        len = 32;
        fnFile_Read(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_MeterModel, uBuf, len);
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
    }
    else if (pOadAys->AtrIndex == 3)  //版本信息
    {
        fnFile_Read(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_ServerVer, uBuf, 32);
        switch (pOadAys->elementIndex)
        {
            case 0:
                num = 6;  //6/个结构体
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                len = 4;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 4, &len, DTYPE_STRING);
                len = 6;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 8, &len, DTYPE_STRING);
                len = 4;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 14, &len, DTYPE_STRING);
                len = 6;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 18, &len, DTYPE_STRING);
                len = 8;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 24, &len, DTYPE_STRING);

                break;
            case 1:
                len = 4;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
                break;

            case 2:
                len = 4;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 4, &len, DTYPE_STRING);
                break;

            case 3:
                len = 6;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 8, &len, DTYPE_STRING);
                break;

            case 4:
                len = 4;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 14, &len, DTYPE_STRING);
                break;

            case 5:
                len = 6;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 18, &len, DTYPE_STRING);
                break;

            case 6:
                len = 8;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 24, &len, DTYPE_STRING);
                break;

            default:

                break;
        }
    }
    else if (pOadAys->AtrIndex == 4)  //生产日期
    {
        if (pOadAys->elementIndex != 0)
        {
            return ERROR;
        }

        fnFile_Read(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_ProductDate, uBuf, sizeof(sDate_time_s_TypeDef));
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_DATETIME_S);
    }
    else if (pOadAys->AtrIndex == 5)  //子设备列表
    {
        if (pOadAys->elementIndex != 0)
        {
            return ERROR;
        }

        num = 1;  //1/个结构体
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
        *uBuf = 0x00;
        *(uBuf + 1) = 0x43;
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_OI);
    }
    else if (pOadAys->AtrIndex == 6)  //支持规约列表
    {
        if (pOadAys->elementIndex != 0)
        {
            return ERROR;
        }

        fnFile_Read(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_PtVer, uBuf, FileItemInfoLen_ASCIIPara_PtVer);
        num = 1;  //1/个结构体
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);
        len = FileItemInfoLen_ASCIIPara_PtVer;
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
    }
    else if (pOadAys->AtrIndex == 7)  //允许跟随上报
    {
        return ERROR;   // dyf 规范要求计量芯返回异常应答，如“对象未定义”
        //if (pOadAys->elementIndex != 0)
        //{
        //    return ERROR;
        //}

        //pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &EvtRptData.Para.FollowAllow, NULL, DTYPE_BOOLEAN);
    }
    else if (pOadAys->AtrIndex == 8)  //允许主动上报
    {
        return ERROR;   // dyf 规范要求计量芯返回异常应答，如“对象未定义”
        //if (pOadAys->elementIndex != 0)
        //{
        //    return ERROR;
        //}

        //pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &EvtRptData.Para.AtiveAllow, NULL, DTYPE_BOOLEAN);
    }
    else if (pOadAys->AtrIndex == 9)  //允许与主站通话
    {
        return ERROR;   // dyf 规范要求计量芯返回异常应答，如“对象未定义”
    }
    else if (pOadAys->AtrIndex == 10)  //上报通道
    {
        return ERROR;   // dyf 规范要求计量芯返回异常应答，如“对象未定义”
        #if 0

        if (pOadAys->elementIndex != 0)
        {
            return ERROR;
        }

        fnFile_Read(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptChannel, &ch[0], 3);
        num = 0;

        for (i = 0; i < 3; i++)
        {
            if ((ch[i] == 9) || (ch[i] == 1) || (ch[i] == 2))
            {
                num++;
            }
        }

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_ARRAY);

        for (i = 0; i < num; i++)
        {
            if (ch[i] == 9)
            {
                OAD = 0xF2090201;
            }
            else if (ch[i] == 1)
            {
                OAD = 0xF2010201;
            }
            else if (ch[i] == 2)
            {
                OAD = 0xF2010202;
            }

            Std_Lsb32DataSet(uBuf, OAD);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_OAD);
        }

        #endif
    }
    else if (pOadAys->AtrIndex == 0x15)  //允许主动上报
    {
        if (pOadAys->elementIndex != 0)
        {
            return ERROR;
        }

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &EvtRptData.Para.AtiveAllow, NULL, DTYPE_BOOLEAN);
    }
    else if (pOadAys->AtrIndex == 30)  //厂家内部软件版本号(0x43001E00)
    {
        len = 32;

        Std_Memcpy(uBuf, &FactorySoftVer[0], len);

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len, DTYPE_STRING);
    }
    else
    {
        return ERROR;
    }

    return  SUCCESS;
}

/*********************************************************************
* @fn      fnGet_LinkPara  class20   0x4400 应用连接接口
*
* @brief
*
* @param
*
* @return
**********************************************************************/
u8 fnGet_LinkPara(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen,  u8  *blockRsp)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    u16 OIA_B = (OAD >> 16 & 0xFFFF), temp16;
    u8 i, num, temp[16];
    //  u8 res = SUCCESS ;
    sCommSize_TypeDef tempsize;

    if (OIA_B != 0x4400)
    {
        return ERROR;
    }

    if (pOadAys->AtrIndex == 3)  //应用语境信息
    {
        if (pOadAys->elementIndex == 0)
        {
            num = 7;  //7个结构体
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
            temp16 = DL698AL_PROTOCOL_VERSION;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp16, NULL, DTYPE_UINT16);

            fnReadConnSize(&tempsize, Secret.Chan, Secret.CA);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tempsize.dl_size_rx, NULL, DTYPE_UINT16);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tempsize.dl_size_tx, NULL, DTYPE_UINT16);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tempsize.apdu_size, NULL, DTYPE_UINT16);

            Std_Msb32DataSet(&temp[0], DL698AL_PROTCFM_HI8B);
            Std_Msb32DataSet(&temp[4], DL698AL_PROTCFM_LO4B);
            for (i = 0; i < 8; i++)
            {
                Std_BitRvsSelf(&temp[i], &temp[i]);
            }
            temp16 = 8;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp[0], &temp16, DTYPE_BITSTRING);

            Std_Msb32DataSet(&temp[0], DL698AL_FUNCCFM_HI16B);
            Std_Msb32DataSet(&temp[4], DL698AL_FUNCCFM_HI12B);
            Std_Msb32DataSet(&temp[8], DL698AL_FUNCCFM_HI8B);
            Std_Msb32DataSet(&temp[12], DL698AL_FUNCCFM_LO4B);
            for (i = 0; i < 16; i++)
            {
                Std_BitRvsSelf(&temp[i], &temp[i]);
            }
            temp16 = 16;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp[0], &temp16, DTYPE_BITSTRING);
            if (Secret.CA == TERMINAL)
            {
                Std_Lsb32DataSet(&temp[0], Secret.Terminal.tLink[Secret.Chan]);
            }
            else
            {
                Std_Lsb32DataSet(&temp[0], Secret.Master.tLink[Secret.Chan]);
            }

            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp[0], NULL, DTYPE_UINT32);
        }
        else if (pOadAys->elementIndex == 1)
        {
            temp16 = DL698AL_PROTOCOL_VERSION;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp16, NULL, DTYPE_UINT16);
        }
        else if (pOadAys->elementIndex == 2)
        {
            fnReadConnSize(&tempsize, Secret.Chan, Secret.CA);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tempsize.dl_size_rx, NULL, DTYPE_UINT16);
        }
        else if (pOadAys->elementIndex == 3)
        {
            fnReadConnSize(&tempsize, Secret.Chan, Secret.CA);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tempsize.dl_size_tx, NULL, DTYPE_UINT16);
        }
        else if (pOadAys->elementIndex == 4)
        {
            fnReadConnSize(&tempsize, Secret.Chan, Secret.CA);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tempsize.dl_size_rx, NULL, DTYPE_UINT16);
        }
        else if (pOadAys->elementIndex == 5)
        {
            Std_Msb32DataSet(&temp[0], DL698AL_PROTCFM_HI8B);
            Std_Msb32DataSet(&temp[4], DL698AL_PROTCFM_LO4B);
            for (i = 0; i < 8; i++)
            {
                Std_BitRvsSelf(&temp[i], &temp[i]);
            }
            temp16 = 8;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp[0], &temp16, DTYPE_BITSTRING);
        }
        else if (pOadAys->elementIndex == 6)
        {
            Std_Msb32DataSet(&temp[0], DL698AL_FUNCCFM_HI16B);
            Std_Msb32DataSet(&temp[4], DL698AL_FUNCCFM_HI12B);
            Std_Msb32DataSet(&temp[8], DL698AL_FUNCCFM_HI8B);
            Std_Msb32DataSet(&temp[12], DL698AL_FUNCCFM_LO4B);
            for (i = 0; i < 16; i++)
            {
                Std_BitRvsSelf(&temp[i], &temp[i]);
            }
            temp16 = 16;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp[0], &temp16, DTYPE_BITSTRING);
        }
        else if (pOadAys->elementIndex == 7)
        {
            if (Secret.CA == TERMINAL)
            {
                Std_Lsb32DataSet(&temp[0], Secret.Terminal.tLink[Secret.Chan]);
            }
            else
            {
                Std_Lsb32DataSet(&temp[0], Secret.Master.tLink[Secret.Chan]);
            }

            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp[0], NULL, DTYPE_UINT32);
        }
    }
    else if (pOadAys->AtrIndex == 4)  //当前连接的客户机地址
    {
        if (pOadAys->elementIndex != 0)
        {
            return ERROR;
        }

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &Secret.CA, NULL, DTYPE_UINT8);
    }
    else if (pOadAys->AtrIndex == 5)  //连接认证机制
    {
        if (pOadAys->elementIndex != 0)
        {
            return ERROR;
        }

        if (Secret.CA == TERMINAL)
        {
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &Secret.Terminal.Auth_object, NULL, DTYPE_ENUM);
        }
        else
        {
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &Secret.Master.Auth_object, NULL, DTYPE_ENUM);
        }
    }
    else
    {
        return ERROR;
    }

    return  SUCCESS;
}

/*********************************************************************
* @fn      fnGet_Control  class8   OI = 0x8000/0x8001 继电器相关信息
*
* @brief
*
* @param
*
* @return
**********************************************************************/
u8 fnGet_Control(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen,  u8  *blockRsp)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    u16 OIA_B = (OAD >> 16 & 0xFFFF), len16;
    u8  num;
    //  u8 res = SUCCESS ;

    if (OIA_B == 0x8000) //远程控制
    {
        if (pOadAys->AtrIndex == 2)  //配置参数
        {
            fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_GataSafeCur, uBuf, 6);

            if (pOadAys->elementIndex == 0)
            {
                num = 2;  //2/个结构体
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &num, NULL, DTYPE_STRUCTURE);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT32);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 4, NULL, DTYPE_UINT16);
            }
            else if (pOadAys->elementIndex == 1)
            {
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT32);
            }
            else if (pOadAys->elementIndex == 2)
            {
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 4, NULL, DTYPE_UINT16);
            }
        }
        else if (pOadAys->AtrIndex == 4)  //告警状态，只读
        {
            if (pOadAys->elementIndex != 0)
            {
                return ERROR;
            }

            *uBuf = Bkgrd.PubData.MoneySta.RemoteAlarm;
            len16 = 1;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len16, DTYPE_BITSTRING);
        }
        else if (pOadAys->AtrIndex == 5)  //命令状态，只读
        {
            if (pOadAys->elementIndex != 0)
            {
                return ERROR;
            }

            fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, uBuf, 1);    //待完善
            len16 = 1;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &len16, DTYPE_BITSTRING);
        }
        else
        {
            return ERROR;
        }
    }
    else  if (OIA_B == 0x8001) //保电
    {
        if (pOadAys->AtrIndex == 2)  //保电状态，只读
        {
            if (pOadAys->elementIndex != 0)
            {
                return ERROR;
            }

            *uBuf = Bkgrd.PubData.MoneySta.RemoteKeepEg;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_ENUM);
        }
        else
        {
            return ERROR;
        }
    }
    else
    {
        return ERROR;
    }

    return  SUCCESS;
}

const sESAMP2_OAD_TypeDef ESAMP2Const[] =
{
    {0xF1000200, 0x02},   //
    {0xF1000300, 0x01},
    {0xF1000400, 0x04},
    {0xF1000500, 0x05},
    {0xF1000600, 0x05},
    {0xF1000700, 0x06},
    {0xF1001000, 0x00},
    {0xF1001100, 0x08},
    {0xF1001200, 0x11},
    {0xF1001300, 0x12},
    {0xF1001400, 0x13},
    {0xF1001500, 0x14},
};
/*********************************************************************
* @fn       fnGet_ESAMPara
*
*       OI = 0xF100
*
* @param
*
* @return
**********************************************************************/
u8 fnGet_ESAMPara(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen,  u8  *blockRsp)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    u8 res = SUCCESS ;

    u8 i;
    u8 EsamP2, temp8;

    u16 temp = 0, esamDatalen = 0;
    //  u16 temp_old = 0;
    u32 temp32;

    for (i = 0 ; i < RE_ARRAY_LENGTH(ESAMP2Const); i++)
    {
        if (ESAMP2Const[i].OAD == (OAD & 0xFFFFFF00))
        {
            EsamP2 = ESAMP2Const[i].EsamP2;
            break;
        }
    }

    if (i < RE_ARRAY_LENGTH(ESAMP2Const)) //获取ESAM数据
    {
        if (0xF1001000 == (OAD & 0xFFFFFF00)) //读取白名单
        {
            if (fnEsamOp_ReadEsam_SafeNameList((u8 *)&ICEsamComm.Ic_Comm_RxBuf[4], &esamDatalen) == ERROR)
            {
                return ERROR;
            }
        }
        else if (fnEsamOp_ReadEsam_Info(EsamP2, (u8 *)&ICEsamComm.Ic_Comm_RxBuf[4], &esamDatalen) == ERROR)
        {
            return ERROR;
        }
    }

    Std_Memcpy(uBuf, (u8 *)&ICEsamComm.Ic_Comm_RxBuf[4], esamDatalen);

    switch (pOadAys->AtrIndex)
    {
        case 0x02:              //ESAM序列号
        case 0x03:              //ESAM版本号
        case 0x04:              //对称密钥版本
        case 0x09:              //终端证书序列号
        case 0x0A:              //终端证书
        case 0x0B:              //主站证书序列号
        case 0x0C:              //主站证书
            Std_MemRvsSelf(uBuf, esamDatalen);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &esamDatalen, DTYPE_OCT_STR);

            if (pOadAys->AtrIndex == 2) //更新密钥信息
            {
                fnUpdatePswSta();
            }
            break;

        case 0x05:              //会话时效门限
            esamDatalen = 4;
            Std_MemRvsSelf(uBuf, esamDatalen);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT32);
            break;

        case 0x06:              //会话时效剩余时间
            esamDatalen = 4;
            if (((Secret.CA == MASTER) && (Secret.Master.tESAMDly == 0)) ||
                ((Secret.CA == TERMINAL) && (Secret.Terminal.tESAMDly == 0)))
            {
                Std_Memset(uBuf + 4, 0x00,  esamDatalen);
            }
            else
            {
                Std_MemRvsSelf(uBuf + 4, esamDatalen);
            }
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 4, NULL, DTYPE_UINT32);
            break;

        case 0x07:              //当前计数器
            temp8 = 3;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp8, NULL, DTYPE_STRUCTURE);

            for (i = 0; i < 3; i++)
            {
                Std_MemRvsSelf(uBuf + 4 * i, 4);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 4 * i,  NULL, DTYPE_UINT32);
            }
            break;

        case 0x08:              //证书版本
            if (pOadAys->elementIndex == 0)
            {
                temp8 = 2;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp8, NULL, DTYPE_STRUCTURE);

                temp = 20;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &temp, DTYPE_OCT_STR);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 5, &temp, DTYPE_OCT_STR);
            }
            else if (pOadAys->elementIndex == 1)
            {
                temp = 20;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &temp, DTYPE_OCT_STR);
            }
            else if (pOadAys->elementIndex == 2)
            {
                temp = 20;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 5, &temp, DTYPE_OCT_STR);
            }
            else
            {
                break;
            }

        case 0x0D:              //ESAM安全存储对象列表
            temp8 = uBuf[0];
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp8, NULL, DTYPE_ARRAY);
            *pRetBuf++ = 1;//Data
            *pRetBuf++ = DTYPE_ARRAY;  //struct类型
            for (i = 0; i < temp8; i++)
            {
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + i * 4 + 1, NULL, DTYPE_OAD);
            }

            break;

        case 0x0E:  //红外时效门限

            if (Secret.CA == TERMINAL) //终端
            {
                fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_tTerminalPrg, uBuf, FileItemInfoLen_HighPara_tTerminalPrg);
            }
            else
            {
                fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_tIRPrg, uBuf, FileItemInfoLen_HighPara_tIRPrg);
            }
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT32);
            break;

        case 0x0F:

            if ((Secret.CA & 0xF0) == TERMINAL) //客户机地址为终端时，抄读红外认证剩余时间为当前终端维持的身份认证剩余时间T2
            {
                temp32 = Secret.tTerminalDly / 60;
            }
            else
            {
                temp32 = Secret.tIRDly / 60;    //客户机地址为主站时，抄读红外认证剩余时间为原红外认证剩余时间T1
            }

            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&temp32, NULL, DTYPE_UINT32);
            break;

        case 0x10:  //白名单1
            i = esamDatalen / 8;
            *pRetBuf++ = DTYPE_ARRAY;
            *pRetBuf++ = i;
            *pRetLen += 2;
            for (; i > 0; i--)
            {
                *pRetBuf++ = DTYPE_OCT_STR;
                *pRetBuf++ = 8;
                Std_Memcpy(pRetBuf, uBuf, 8);
                pRetBuf += 8;
                uBuf += 8;
                *pRetLen += 10;
            }
            break;

        case 0x11:      //身份认证标志
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT8);
            break;

        case 0x12:      //终端地址
            Std_MemRvsSelf(uBuf, esamDatalen);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, &esamDatalen, DTYPE_OCT_STR);

            break;

        case 0x13:      //终端广播计数器
            Std_MemRvsSelf(uBuf, 4);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT32);
            break;

        case 0x14:      //终端与电表会话计数器
            Std_MemRvsSelf(uBuf, 4);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT32);
            break;

        case 0x15:      //终端会话门限
            if (pOadAys->elementIndex == 0)
            {
                temp8 = 2;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp8, NULL, DTYPE_STRUCTURE);

                Std_MemRvsSelf(uBuf, 4);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT32);

                Std_MemRvsSelf(uBuf + 4, 4);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 4, NULL, DTYPE_UINT32);
            }
            else if (pOadAys->elementIndex == 1) //门限
            {
                Std_MemRvsSelf(uBuf, 4);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_UINT32);
            }
            else if (pOadAys->elementIndex == 2) //剩余时间
            {
                Std_MemRvsSelf(uBuf + 4, 4);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf + 4, NULL, DTYPE_UINT32);
            }
            else
            {
                res = ERROR;
            }
            break;

        default:
            res = ERROR;
            break;
    }

    return  res;
}

/*********************************************************************
* @fn       fnGet_SafeModePara  安全模式参数
*
*       OI = 0xF101
*
* @param
*
* @return
**********************************************************************/
u8 fnGet_SafeModePara(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen,  u8  *blockRsp)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    u8 i, safemode_flag, temp;
    //  u8 res = SUCCESS ;
    sSafeModePara_TypeDef   safe_mode;

    if (pOadAys->AtrIndex == 2) //安全模式字选择
    {
        fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SafeModeFlag, (u8 *)&safemode_flag, 1);
        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &safemode_flag, NULL, DTYPE_ENUM);
    }
    else if (pOadAys->AtrIndex == 3) //显式安全模式参数
    {
        fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SafeModePara, (u8 *)&safe_mode, FileItemInfoLen_SecretPara_SafeModePara);

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &safe_mode.OI_Cnt, NULL, DTYPE_ARRAY);
        temp = 2;
        for (i = 0; i < safe_mode.OI_Cnt; i++)
        {
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_STRUCTURE);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&safe_mode.SafeModeTable[i].OI, NULL, DTYPE_OI);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&safe_mode.SafeModeTable[i].Mode, NULL, DTYPE_UINT16);
        }
    }

    return  SUCCESS;
}

/*********************************************************************
* @fn       fnGet_InOut_DevicePara  class22  输入输出设备对象
*
*       OI = 0xF201/0xF202/0xF205/0xF207/0xF209/0xF213
*
* @param
*
* @return
**********************************************************************/
const u8 TAB_RS485[] = {"RS485"};
const u8 TAB_RS4851[] = {"RS4851"};
const u8 TAB_RS4852[] = {"RS4852"};
const u8 TAB_IR[] = {"INFRA"};
const u8 TAB_COM[] = {2, 8, 1, 0};     //校验位:偶校验; 数据位:8 ;停止位:1 流控:无
const u8 TAB_PortFunction[] = { 0 };
const u8 TAB_Relay[] = {"RELAY"};

sSynFrzDataBlock_Type   SynFrzDataBlock;
const sTagLen_Type SynVarDataBlockTagLen[] =
{
    {DTYPE_DATETIME_S,  0, (u8*) &SysDatetimes, 7}, //时间日期
    {DTYPE_BITSTRING,   32, (u8*) &Bkgrd.PubData.MtSysSta.SysSta,    4}, //系统状态字
    {DTYPE_BITSTRING,   32, (u8*) &Bkgrd.PubData.MeasureSysSta.SysSta,   4}, //采样状态字
    {DTYPE_ARRAY,   8,  NULL,   0}, //端子温度
    {DTYPE_INT16,   0, (u8 *) &Bkgrd.PubData.Tnal_Tmper[0], 2},
    {DTYPE_INT16,   0, (u8 *) &Bkgrd.PubData.Tnal_Tmper[1], 2},
    {DTYPE_INT16,   0, (u8 *) &Bkgrd.PubData.Tnal_Tmper[2], 2},
    {DTYPE_INT16,   0, (u8 *) &Bkgrd.PubData.Tnal_Tmper[3], 2},
    {DTYPE_INT16,   0, (u8 *) &Bkgrd.PubData.Tnal_Tmper[4], 2},
    {DTYPE_INT16,   0, (u8 *) &Bkgrd.PubData.Tnal_Tmper[5], 2},
    {DTYPE_INT16,   0, (u8 *) &Bkgrd.PubData.Tnal_Tmper[6], 2},
    {DTYPE_INT16,   0, (u8 *) &Bkgrd.PubData.Tnal_Tmper[7], 2},
    {DTYPE_UINT32,  0, (u8 *) &MeasureRms.PubData.U[0], 4}, //A相电压
    {DTYPE_UINT32,  0, (u8 *) &MeasureRms.PubData.U[1], 4}, //B相电压
    {DTYPE_UINT32,  0, (u8 *) &MeasureRms.PubData.U[2], 4}, //B相电压
    {DTYPE_INT32,   0, (u8 *) &MeasureRms.PubData.I[0], 4}, //A相电流
    {DTYPE_INT32,   0, (u8 *) &MeasureRms.PubData.I[1], 4}, //B相电流
    {DTYPE_INT32,   0, (u8 *) &MeasureRms.PubData.I[2], 4}, //C相电流
    {DTYPE_INT32,   0, (u8 *) &MeasureRms.PubData.In,   4}, //零线电流
    {DTYPE_INT32,   0, (u8 *) &MeasureRms.PubData.VectorI[2],   4}, //三相电流矢量和
    {DTYPE_UINT16,  0, (u8 *) &MeasureRms.PubData.Angle[3], 2}, //A相电压电流相角
    {DTYPE_UINT16,  0, (u8 *) &MeasureRms.PubData.Angle[4], 2}, //B相电压电流相角
    {DTYPE_UINT16,  0, (u8 *) &MeasureRms.PubData.Angle[5], 2}, //C相电压电流相角
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.Pw[0],   4}, //总有功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.Pw[1],   4}, //A相有功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.Pw[2],   4}, //B相有功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.Pw[3],   4}, //C相有功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.Pw[4],   4}, //总无功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.Pw[5],   4}, //A相无功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.Pw[6],   4}, //B相无功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.Pw[7],   4}, //C相无功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.Pw[8],   4}, //总视在功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.Pw[9],   4}, //A相视在功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.Pw[10],  4}, //B相视在功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.Pw[11],  4}, //C相视在功率
    {DTYPE_INT16,   0, (u8 *) &SynVarOtherUnitData.Pf[0],   2}, //总功率因数
    {DTYPE_INT16,   0, (u8 *) &SynVarOtherUnitData.Pf[1],   2}, //A相功率因数
    {DTYPE_INT16,   0, (u8 *) &SynVarOtherUnitData.Pf[2],   2}, //B相功率因数
    {DTYPE_INT16,   0, (u8 *) &SynVarOtherUnitData.Pf[3],   2}, //C相功率因数
    {DTYPE_UINT16,  0, (u8 *) &MeasureRms.PubData.Frequency,    2}, //电网频率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.AvgPw[0],    4}, //一分钟总平均有功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.AvgPw[1],    4}, //一分钟A相平均有功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.AvgPw[2],    4}, //一分钟B相平均有功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.AvgPw[3],    4}, //一分钟C相平均有功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.AvgPw[4],    4}, //一分钟总平均无功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.AvgPw[5],    4}, //一分钟A相平均无功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.AvgPw[6],    4}, //一分钟B相平均无功功率
    {DTYPE_INT32,   0, (u8 *) &SynVarOtherUnitData.AvgPw[7],    4}, //一分钟C相平均无功功率
    {DTYPE_INT16,   0, (u8 *) &HarmonicData.PubData.HarmonicThdU[0],    2}, //A相电压波形失真度
    {DTYPE_INT16,   0, (u8 *) &HarmonicData.PubData.HarmonicThdU[1],    2}, //B相电压波形失真度
    {DTYPE_INT16,   0, (u8 *) &HarmonicData.PubData.HarmonicThdU[2],    2}, //C相电压波形失真度
    {DTYPE_INT16,   0, (u8 *) &HarmonicData.PubData.HarmonicThdI[0],    2}, //A相电流波形失真度
    {DTYPE_INT16,   0, (u8 *) &HarmonicData.PubData.HarmonicThdI[1],    2}, //B相电流波形失真度
    {DTYPE_INT16,   0, (u8 *) &HarmonicData.PubData.HarmonicThdI[2],    2}, //C相电流波形失真度
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.PtPEgSh[0],   8}, //正向有功总电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.PtPEgSha, 8}, //正向有功A相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.PtPEgShb, 8}, //正向有功B相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.PtPEgShc, 8}, //正向有功C相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.NtPEgSh[0],   8}, //反向有功总电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.NtPEgSha, 8}, //反向有功A相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.NtPEgShb, 8}, //反向有功B相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.NtPEgShc, 8}, //反向有功C相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd1QEgSh[0],  8}, //第一象限无功总电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd1QEgSha, 8}, //第一象限无功A相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd1QEgShb, 8}, //第一象限无功B相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd1QEgShc, 8}, //第一象限无功C相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd2QEgSh[0], 8},  //第二象限无功总电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd2QEgSha, 8}, //第二象限无功A相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd2QEgShb, 8}, //第二象限无功B相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd2QEgShc, 8}, //第二象限无功C相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd3QEgSh[0], 8},  //第三象限无功总电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd3QEgSha, 8}, //第三象限无功A相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd3QEgShb, 8}, //第三象限无功B相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd3QEgShc, 8}, //第三象限无功C相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd4QEgSh[0],  8}, //第四象限无功总电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd4QEgSha, 8}, //第四象限无功A相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd4QEgShb, 8}, //第四象限无功B相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.Qd4QEgShc, 8}, //第四象限无功C相电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.PtFEgSh[0],   8}, //正向（有功）基波总电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.NtFEgSh[0],   8}, //反向（有功）基波总电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.PtHEgSh[0],   8}, //正向（有功）谐波总电能
    {DTYPE_UINT64,  0, (u8 *) &Energy.PubData.NtHEgSh[0],   8}  //反向（有功）谐波总电能
};
const sTagLen_Type SynFrz1DataBlockTagLen[] =
{
    {DTYPE_DATETIME_S,  0, (u8*) &SynFrzDataBlock.Frz1DateTimes,    7}, //上一次分钟冻结方案1时间日期
    {DTYPE_UINT64,  0, (u8 *) &SynFrzDataBlock.FrzPtPEgSh,  8}, //冻结正向有功电能
    {DTYPE_UINT64,  0, (u8 *) &SynFrzDataBlock.FrzNtPEgSh,  8}, //冻结反向有功电能
    {DTYPE_ARRAY,   3,  NULL,   0}, //冻结电压
    {DTYPE_UINT16,  0, (u8 *) &SynFrzDataBlock.FrzU[0], 2}, //冻结A相电压
    {DTYPE_UINT16,  0, (u8 *) &SynFrzDataBlock.FrzU[1], 2}, //冻结B相电压
    {DTYPE_UINT16,  0, (u8 *) &SynFrzDataBlock.FrzU[2], 2}, //冻结C相电压
    {DTYPE_ARRAY,   3,  NULL,   0}, //冻结电流
    {DTYPE_INT32,   0, (u8 *) &SynFrzDataBlock.FrzI[0], 4}, //冻结A相电流
    {DTYPE_INT32,   0, (u8 *) &SynFrzDataBlock.FrzI[1], 4}, //冻结B相电流
    {DTYPE_INT32,   0, (u8 *) &SynFrzDataBlock.FrzI[2], 4}, //冻结C相电流
    {DTYPE_ARRAY,   4,  NULL,   0}, //冻结一分钟平均有功功率
    {DTYPE_INT32,   0, (u8 *) &SynFrzDataBlock.FrzPwavg[0], 4}, //冻结一分钟平均总有功功率
    {DTYPE_INT32,   0, (u8 *) &SynFrzDataBlock.FrzPwavg[1], 4}, //冻结一分钟平均A相有功功率
    {DTYPE_INT32,   0, (u8 *) &SynFrzDataBlock.FrzPwavg[2], 4}, //冻结一分钟平均B相有功功率
    {DTYPE_INT32,   0, (u8 *) &SynFrzDataBlock.FrzPwavg[3], 4}, //冻结一分钟平均C相有功功率
    {DTYPE_ARRAY,   4,  NULL,   0}, //冻结一分钟平均无功功率
    {DTYPE_INT32,   0, (u8 *) &SynFrzDataBlock.FrzPqavg[0], 4}, //冻结一分钟平均总无功功率
    {DTYPE_INT32,   0, (u8 *) &SynFrzDataBlock.FrzPqavg[1], 4}, //冻结一分钟平均A相无功功率
    {DTYPE_INT32,   0, (u8 *) &SynFrzDataBlock.FrzPqavg[2], 4}, //冻结一分钟平均B相无功功率
    {DTYPE_INT32,   0, (u8 *) &SynFrzDataBlock.FrzPqavg[3], 4}, //冻结一分钟平均C相无功功率
    {DTYPE_ARRAY,   4,  NULL,   0}, //冻结功率因数
    {DTYPE_INT16,   0, (u8 *) &SynFrzDataBlock.FrzPf[0], 2}, //冻结总功率因数
    {DTYPE_INT16,   0, (u8 *) &SynFrzDataBlock.FrzPf[1], 2}, //冻结A相功率因数
    {DTYPE_INT16,   0, (u8 *) &SynFrzDataBlock.FrzPf[2], 2}, //冻结B相功率因数
    {DTYPE_INT16,   0, (u8 *) &SynFrzDataBlock.FrzPf[3], 2} //冻结C相功率因数
};
const sTagLen_Type SynFrz2DataBlockTagLen[] =
{
    {DTYPE_DATETIME_S,  0, (u8*) &SynFrzDataBlock.Frz2DateTimes,    7}, //上一次分钟冻结方案2时间日期
    {DTYPE_UINT64,  0, (u8 *) &SynFrzDataBlock.FrzQd1QEgSh, 8}, //冻结第一象限无功电能
    {DTYPE_UINT64,  0, (u8 *) &SynFrzDataBlock.FrzQd2QEgSh, 8}, //冻结第二象限无功电能
    {DTYPE_UINT64,  0, (u8 *) &SynFrzDataBlock.FrzQd3QEgSh, 8}, //冻结第三象限无功电能
    {DTYPE_UINT64,  0, (u8 *) &SynFrzDataBlock.FrzQd4QEgSh, 8}, //冻结第四象限无功电能
    {DTYPE_UINT64,  0, (u8 *) &SynFrzDataBlock.FrzPtFEgSh,  8}, //冻结正向（有功）基波总电能
    {DTYPE_UINT64,  0, (u8 *) &SynFrzDataBlock.FrzNtFEgSh,  8}, //冻结反向（有功）基波总电能
    {DTYPE_UINT64,  0, (u8 *) &SynFrzDataBlock.FrzPtHEgSh,  8}, //冻结正向（有功）谐波总电能
    {DTYPE_UINT64,  0, (u8 *) &SynFrzDataBlock.FrzNtHEgSh,  8}  //冻结反向（有功）谐波总电能
};

u8 fnGet_InOut_DevicePara(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen,  u8  *blockRsp)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    u16  len = 0;
    u8  temp, OIB;
    u8 res = SUCCESS ;
    u8 i, *pDst, *pSrc, *pItemNum, SynItemNum;
    u16 j;

    OIB = (OAD >> 16) & 0xFF;

    //if(( pOadAys->OIB2 !=0x13 )&&(pOadAys->AtrIndex != 2) ) //只支持属性2读取
    if ((OIB != 0x13) && (pOadAys->AtrIndex != 2)) //只支持属性2读取
    {
        return ERROR;
    }

    //switch( pOadAys->OIB2 )
    switch (OIB)
    {
        case 1:   //485接口
            #if(METERTYPE == 0)
            // 智能表  两路485
            if (pOadAys->elementIndex == 0)
            {
                temp = 2;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_ARRAY);

                temp = 3;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_STRUCTURE);
                len = 5;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_RS4851, &len, DTYPE_STRING);
                //fnFile_Read(FileId_ParaCom , FileItemInfoOffAddr_ComPara_Com1Style , uBuf , 1 );  //波特率
                *uBuf = ComPack[SCOM_PORT_RS485A].NewBps;
                Std_Memcpy(uBuf + 1, (u8 *)&TAB_COM, 4);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_COMDCB);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_PortFunction, NULL, DTYPE_ENUM);

                temp = 3;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_STRUCTURE);
                len = 5;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_RS4852, &len, DTYPE_STRING);
                //fnFile_Read(FileId_ParaCom , FileItemInfoOffAddr_ComPara_Com1Style , uBuf , 1 );  //波特率
                *uBuf = ComPack[SCOM_PORT_RS485B].NewBps;
                Std_Memcpy(uBuf + 1, (u8 *)TAB_COM, 4);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_COMDCB);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_PortFunction, NULL, DTYPE_ENUM);
            }
            else if (pOadAys->elementIndex == 1)
            {
                temp = 3;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_STRUCTURE);
                len = 5;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_RS4851, &len, DTYPE_STRING);
                //fnFile_Read(FileId_ParaCom , FileItemInfoOffAddr_ComPara_Com1Style , uBuf , 1 );  //波特率
                *uBuf = ComPack[SCOM_PORT_RS485A].NewBps;
                Std_Memcpy(uBuf + 1, (u8 *)&TAB_COM, 4);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_COMDCB);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_PortFunction, NULL, DTYPE_ENUM);
            }
            else if (pOadAys->elementIndex == 2)
            {
                temp = 3;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_STRUCTURE);
                len = 5;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_RS4852, &len, DTYPE_STRING);
                //fnFile_Read(FileId_ParaCom , FileItemInfoOffAddr_ComPara_Com2Style , uBuf , 1 );  //波特率
                *uBuf = ComPack[SCOM_PORT_RS485B].NewBps;
                Std_Memcpy(uBuf + 1, (u8 *)&TAB_COM, 4);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_COMDCB);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_PortFunction, NULL, DTYPE_ENUM);
            }
            else
            {
                res =  ERROR;
            }
            #else
            if (pOadAys->elementIndex == 0)
            {
                temp = 1;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_ARRAY);
                temp = 3;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_STRUCTURE);
                len = 5;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_RS4851, &len, DTYPE_STRING);
                //fnFile_Read(FileId_ParaCom , FileItemInfoOffAddr_ComPara_Com1Style , uBuf , 1 );  //波特率
                *uBuf = ComPack[SCOM_PORT_RS485A].NewBps;
                Std_Memcpy(uBuf + 1, (u8 *)&TAB_COM, 4);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_COMDCB);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_PortFunction, NULL, DTYPE_ENUM);
            }
            else if (pOadAys->elementIndex == 1)
            {
                temp = 3;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_STRUCTURE);
                len = 5;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_RS4851, &len, DTYPE_STRING);
                //fnFile_Read(FileId_ParaCom , FileItemInfoOffAddr_ComPara_Com1Style , uBuf , 1 );  //波特率
                *uBuf = ComPack[SCOM_PORT_RS485A].NewBps;
                Std_Memcpy(uBuf + 1, (u8 *)&TAB_COM, 4);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_COMDCB);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_PortFunction, NULL, DTYPE_ENUM);
            }
            else
            {
                res =  ERROR;
            }
            #endif

            break;

        /*
        case 2:  //红外接口

            if(pOadAys->elementIndex == 0)
            {
                temp = 1;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_ARRAY);
                temp = 3;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_STRUCTURE);
                len = 5;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_IR , &len , DTYPE_STRING);
                *uBuf = ComPack[SCOM_PORT_IR].NewBps;
                Std_Memcpy(uBuf + 1 , (u8 *)&TAB_COM , 4 );
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf , NULL , DTYPE_COMDCB);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_PortFunction , NULL , DTYPE_ENUM);
            }
            else if(pOadAys->elementIndex == 1)
            {
                temp = 3;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_STRUCTURE);
                len = 5;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_IR , &len , DTYPE_STRING);
                *uBuf = ComPack[SCOM_PORT_IR].NewBps;
                Std_Memcpy(uBuf + 1 , (u8 *)&TAB_COM , 4 );
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf , NULL , DTYPE_COMDCB);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_PortFunction , NULL , DTYPE_ENUM);
            }
            else
                res =  ERROR;

            break;
            */

        case 5:  //继电器输出
            if (pOadAys->elementIndex == 0)
            {
                temp = 1;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_ARRAY);
                temp = 4;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_STRUCTURE);
                len = 5;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_Relay, &len, DTYPE_STRING);
                *uBuf = Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_ENUM);
                *uBuf = 0x01; //继电器开关属性  保持式
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_ENUM);
                *uBuf = 0x00; //继电器接线状态 接入
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_ENUM);
            }
            else if (pOadAys->elementIndex == 1)
            {
                temp = 4;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_STRUCTURE);
                len = 5;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&TAB_Relay, &len, DTYPE_STRING);
                *uBuf = Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_ENUM);
                *uBuf = 0x01; //继电器开关属性  保持式
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_ENUM);
                *uBuf = 0x00; //继电器接线状态 接入
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_ENUM);
            }
            else
            {
                res =  ERROR;
            }

            break;

        case 7: //多功能端子输出
            if (pOadAys->elementIndex == 0)
            {
                temp = 1;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_ARRAY);
                *uBuf = Bkgrd.PubData.MtSta.MtSta1.StaBit.OutMulFun;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_ENUM);
            }
            else if (pOadAys->elementIndex == 1)
            {
                *uBuf = Bkgrd.PubData.MtSta.MtSta1.StaBit.OutMulFun;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf, NULL, DTYPE_ENUM);
            }
            else
            {
                res =  ERROR;
            }

            break;

        /*
        case 9:
            if(pOadAys->elementIndex == 0)
            {
                temp = 1;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_ARRAY);
                temp = 3;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_STRUCTURE);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL , NULL , DTYPE_NONE);
                //fnFile_Read(FileId_ParaCom , FileItemInfoOffAddr_ComPara_Ir1Style , uBuf , 1 );  //波特率
                *uBuf = ComPack[SCOM_PORT_ZBCOM].NewBps;
                temp = ComPack[SCOM_PORT_ZBCOM].NewBps;
                Std_Memcpy(uBuf + 1 , (u8 *)&TAB_COM , 4 );
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf , NULL , DTYPE_COMDCB);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL , NULL , DTYPE_NONE);
            }
            else if(pOadAys->elementIndex == 1)
            {
                temp = 3;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_STRUCTURE);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL , NULL , DTYPE_NONE);
                //fnFile_Read(FileId_ParaCom , FileItemInfoOffAddr_ComPara_Ir1Style , uBuf , 1 );  //波特率
                *uBuf = ComPack[SCOM_PORT_ZBCOM].NewBps;
                temp = ComPack[SCOM_PORT_ZBCOM].NewBps;
                Std_Memcpy(uBuf + 1 , (u8 *)&TAB_COM , 4 );
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, uBuf , NULL , DTYPE_COMDCB);
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, NULL , NULL , DTYPE_NONE);
            }
            else
                res =  ERROR;

            break;
            */

        case 0x13:
            if (pOadAys->AtrIndex == 5)
            {
                pDst = pRetBuf;
                *pDst++ = DTYPE_STRUCTURE;//结构体
                pItemNum = pDst++;
                *pItemNum = 0;

                //打包变量数据
                SynItemNum = 0;
                for (i = 0; i < (sizeof(SynVarDataBlockTagLen) / sizeof(sTagLen_Type)); i++)
                {
                    *pDst++ = SynVarDataBlockTagLen[i].AtrType;
                    if (SynVarDataBlockTagLen[i].AtrTypeLen != 0)
                    {
                        *pDst++ = SynVarDataBlockTagLen[i].AtrTypeLen;
                    }
                    if (SynVarDataBlockTagLen[i].DataLen != 0)
                    {
                        if (SynVarDataBlockTagLen[i].AtrType != DTYPE_BITSTRING)
                        {
                            Std_MemRvs(pDst, SynVarDataBlockTagLen[i].pAddr, SynVarDataBlockTagLen[i].DataLen);
                            pDst += SynVarDataBlockTagLen[i].DataLen;
                        }
                        else
                        {
                            pSrc = SynVarDataBlockTagLen[i].pAddr;
                            for (j = 0; j < SynVarDataBlockTagLen[i].DataLen; j++)
                            {
                                Std_BitRvsSelf(pDst++, pSrc++);
                            }
                        }
                    }
                    //减去数组中的元素长度
                    if (SynVarDataBlockTagLen[i].AtrType == DTYPE_ARRAY)
                    {
                        SynItemNum += SynVarDataBlockTagLen[i].AtrTypeLen;
                    }
                }
                *pItemNum = sizeof(SynVarDataBlockTagLen) / sizeof(sTagLen_Type) - SynItemNum;

                if (SynFrzDataBlock.Frz1DateValid == 1)
                {
                    //打包冻结方案1冻结数据
                    SynItemNum = 0;
                    for (i = 0; i < (sizeof(SynFrz1DataBlockTagLen) / sizeof(sTagLen_Type)); i++)
                    {
                        *pDst++ = SynFrz1DataBlockTagLen[i].AtrType;
                        if (SynFrz1DataBlockTagLen[i].AtrTypeLen != 0)
                        {
                            *pDst++ = SynFrz1DataBlockTagLen[i].AtrTypeLen;
                        }
                        if (SynFrz1DataBlockTagLen[i].DataLen != 0)
                        {
                            Std_MemRvs(pDst, SynFrz1DataBlockTagLen[i].pAddr, SynFrz1DataBlockTagLen[i].DataLen);
                            pDst += SynFrz1DataBlockTagLen[i].DataLen;
                        }
                        if (SynFrz1DataBlockTagLen[i].AtrType == DTYPE_ARRAY)
                        {
                            SynItemNum += SynFrz1DataBlockTagLen[i].AtrTypeLen;
                        }
                    }
                    *pItemNum += sizeof(SynFrz1DataBlockTagLen) / sizeof(sTagLen_Type) - SynItemNum;
                }

                if (SynFrzDataBlock.Frz2DateValid == 1)
                {
                    //打包冻结方案2冻结数据
                    SynItemNum = 0;
                    for (i = 0; i < (sizeof(SynFrz2DataBlockTagLen) / sizeof(sTagLen_Type)); i++)
                    {
                        *pDst++ = SynFrz2DataBlockTagLen[i].AtrType;
                        if (SynFrz2DataBlockTagLen[i].AtrTypeLen != 0)
                        {
                            *pDst++ = SynFrz2DataBlockTagLen[i].AtrTypeLen;
                        }
                        if (SynFrz2DataBlockTagLen[i].DataLen != 0)
                        {
                            Std_MemRvs(pDst, SynFrz2DataBlockTagLen[i].pAddr, SynFrz2DataBlockTagLen[i].DataLen);
                            pDst += SynFrz2DataBlockTagLen[i].DataLen;
                        }
                        if (SynFrz2DataBlockTagLen[i].AtrType == DTYPE_ARRAY)
                        {
                            SynItemNum += SynFrz2DataBlockTagLen[i].AtrTypeLen;
                        }
                    }
                    *pItemNum += sizeof(SynFrz2DataBlockTagLen) / sizeof(sTagLen_Type) - SynItemNum;
                }

                *pRetLen = pDst - pRetBuf;
                pRetBuf = pDst;
                *blockRsp = 0;
                res =  SUCCESS;
            }
            else if (pOadAys->AtrIndex == 6) //--电流半波有效值容器-----
            {
                if (sHmWave.HalfIrms.ReadFlag == CTLSTAR) //--半波有效值未结束-
                {
                    len = 0;
                }
                else
                {
                    if (sHmWave.HalfIrms.RDepth > 480)
                    {
                        sHmWave.HalfIrms.RDepth = 480;
                    }

                    len = 2  * sHmWave.HalfIrms.RDepth;
                }

                UINT8_TO_STREAM(pRetBuf, DTYPE_OCT_STR);
                *pRetLen = 1;
                if (len < 128)
                {
                    UINT8_TO_STREAM(pRetBuf, len);
                    *pRetLen += 1;
                }
                else if (len < 256)
                {
                    UINT8_TO_STREAM(pRetBuf, 0x81);
                    UINT8_TO_STREAM(pRetBuf, len & 0xFF);
                    *pRetLen += 2;
                }
                else
                {
                    UINT8_TO_STREAM(pRetBuf, 0x82);
                    UINT8_TO_STREAM(pRetBuf, len >> 8);
                    UINT8_TO_STREAM(pRetBuf, len & 0xFF);
                    *pRetLen += 3;
                }
                if (len != 0)
                {
                    //SEGGER_RTT_printf(0,"HalfIrms: \n");
                    for (j = 0; j < sHmWave.HalfIrms.RDepth; j++)
                    {
                        //----转为小端格式应答------------------
                        //Std_MemRvsSelf((u8 *)&AdcWaveData.HalfIrms.Irms[j] , 2);
                        //pDtest = pRetBuf;

                        //                      for(i=0; i<1; i++)
                        //                      {
                        //                          *pRetBuf++ = sHmWave.HalfIrms.Irms[i][j]&0xFF;
                        //                          *pRetBuf++ = sHmWave.HalfIrms.Irms[i][j]>>8;
                        //                      }

                        *pRetBuf++ = sHmWave.HalfIrms.Irms[0][j] & 0xFF;
                        *pRetBuf++ = sHmWave.HalfIrms.Irms[0][j] >> 8;

                        //if(*pDtest<0x10)SEGGER_RTT_printf(0,"0");
                        //SEGGER_RTT_printf(0,"%X",*pDtest++);
                        //if(*pDtest<0x10)SEGGER_RTT_printf(0,"0");
                        //SEGGER_RTT_printf(0,"%X",*pDtest++);
                        //SEGGER_RTT_printf(0,"\n");
                    }
                    *pRetLen += len;
                    //SEGGER_RTT_printf(0,"\n");
                }
                //  pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&AdcWaveData.HalfIrms.Irms[0] , &len , DTYPE_OCT_STR);

                res =  SUCCESS;
            }
            else
            {
                res =  ERROR;
            }

            break;

        default:
            res =  ERROR;
            break;
    }

    return  res;
}

/*********************************************************************************************************
** Function name:   fnGet_EvtReport
** Descriptions:    读取0x33200200 新增主动上报列表,0x33200300 需上报对象列表
** input parameters:  OAD:OAD读取此OAD对应的内容
** output parameters:   pRetBuf:读取到的数据.   pRetLen:读取数据内容应答长度
** Returned value:读取成功或失败结果
*********************************************************************************************************/
u8 fnGet_EvtReport(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *pRetLen,  u8  *blockRsp)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    u16 OIA_B = (OAD >> 16 & 0xFFFF), OI_rpt;
    u8 i, j, temp = 0, Offset, item = 0;
    sReportList_TypeDef tempList;

    if (OIA_B != 0x3320)
    {
        return ERROR;
    }

    if (pOadAys->AtrIndex == 2) //新增主动上报列表
    {
        if (Secret.Chan == SCOM_PORT_ZBCOM)
        {
            fnFile_Read(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNumZB_F, (u8 *)&tempList, sizeof(sReportList_TypeDef));
            temp = EvtRptData.ListZB_A.OADNum + tempList.OADNum;

            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_ARRAY);

            for (i = EvtRptData.ListZB_A.OADNum; i > 0 ; i--) //主动上报列表
            {
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&EvtRptData.ListZB_A.OAD[i - 1], NULL, DTYPE_OAD);
            }
        }
        else if (Secret.Chan == SCOM_PORT_RS485A)
        {
            fnFile_Read(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNum485_F, (u8 *)&tempList, sizeof(sReportList_TypeDef));
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &tempList.OADNum, NULL, DTYPE_ARRAY);
        }
        else if (Secret.Chan == SCOM_PORT_RS485B)
        {
            fnFile_Read(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_OADNum4852_F, (u8 *)&tempList, sizeof(sReportList_TypeDef));
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &tempList.OADNum, NULL, DTYPE_ARRAY);
        }
        else
        {
            return ERROR;
        }

        for (i = tempList.OADNum; i > 0 ; i--) //跟随上报列表
        {
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&tempList.OAD[i - 1], NULL, DTYPE_OAD);
        }
    }
    else if (pOadAys->AtrIndex == 3) //需上报对象列表
    {
        for (j = 0; j < ITEM_EVT_MAX; j++)
        {
            Offset = j / 8;
            i = j % 8;

            if ((((EvtRptData.Para.RptFlagHappen[Offset] >> i) & 0x01) == 0x01) ||
                (((EvtRptData.Para.RptFlagEnd[Offset] >> i) & 0x01) == 0x01))
            {
                temp++;
            }
        }

        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, &temp, NULL, DTYPE_ARRAY);

        for (j = 0; j < ITEM_EVT_MAX; j++)
        {
            Offset = j / 8;
            i = j % 8;

            if ((((EvtRptData.Para.RptFlagHappen[Offset] >> i) & 0x01) == 0x01) ||
                (((EvtRptData.Para.RptFlagEnd[Offset] >> i) & 0x01) == 0x01))
            {
                item = j;
                for (i = 0; i < FileItemInfoNum_Evt_Max; i++)
                {
                    if (Event_Item[i].Item == item)
                    {
                        OI_rpt = Event_Item[i].OI;
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, pRetLen, (u8 *)&OI_rpt, NULL, DTYPE_OI);
                        break;
                    }
                }
            }
        }
    }
    else
    {
        return ERROR;
    }

    return SUCCESS;
}

/*********************************************************************************************************
** Function name:   fnGetOAD_MemoryLen
** Descriptions:
** input parameters:  OAD:OAD
** output parameters:   OAD 对应的存储数据内容及长度，pBuf获取到的数据内容
** Returned value:  OAD长度
*********************************************************************************************************/
u16 fnGet_OADStoreData(u32  OAD,  u8  *pBuf)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    u8   i, j;
    u16  Len = 0;
    sHolidayTable_TypeDef hldy_buf;
    u16 OIA_B = (OAD >> 16 & 0xFFFF), offset;

    switch (pOadAys->OIA1)
    {
        case OIA1_ENERGY:

            Len = (u16)fnGet_EnergyData(OAD, pBuf);
            if (Len == 0)
            {
                return ERROR;
            }

            break;
        //      #if(nPhs==ThreePhs)
        //      case OIA1_NEED:
        //
        //          Len = (u16)fnGet_NeedData(OAD , pBuf );
        //          if( Len== 0)
        //              return ERROR;
        //
        //          break;
        //      #endif

        case OIA1_VAR:
            Len = (u16)fnGet_VarData(OAD, pBuf);
            if (Len == 0)
            {
                return ERROR;
            }

            break;

        case OIA1_PARA:

            for (i = 0 ; i < RE_ARRAY_LENGTH(PARA_VAR_Item); i++)
            {
                if (PARA_VAR_Item[i].OI == OIA_B)
                {
                    fnFile_Read(PARA_VAR_Item[i].FileId, PARA_VAR_Item[i].OffAddr, pBuf, PARA_VAR_Item[i].Len);
                    Len = PARA_VAR_Item[i].Len ;
                    break;
                }
            }

            if (i == RE_ARRAY_LENGTH(PARA_VAR_Item))
            {
                return ERROR;
            }

            //--------需要特殊处理的参数-----------------
            if (OIA_B == 0x4011)  //公共节假日
            {
                if (pOadAys->elementIndex != 0)
                {
                    offset = (pOadAys->elementIndex - 1) * sizeof(sHolidayTable_TypeDef);
                    Std_Memcpy((u8 *)&hldy_buf, pBuf + offset, sizeof(sHolidayTable_TypeDef));

                    Std_Memcpy(pBuf, &hldy_buf.Week, sizeof(sHolidayTable_TypeDef) - 1);
                    Std_Memcpy(pBuf + sizeof(sHolidayTable_TypeDef) - 1, &hldy_buf.nPOTTable, 1);

                    Len = sizeof(sHolidayTable_TypeDef) ;
                }
            }
            else if ((OIA_B == 0x4014) || (OIA_B == 0x4015)) //时区表
            {
                if (pOadAys->elementIndex != 0)
                {
                    Len = sizeof(sTimeZoneTable_TypeDef) ;
                    offset = sizeof(sDate_time_s_TypeDef);
                    offset += Len * (pOadAys->elementIndex - 1) + (pOadAys->OIB2 - 4) * 42;

                    fnFile_Read(FileId_RatePara,
                                FileItemInfoOffAddr_RatePara_TimeZonePara + offset,
                                pBuf,
                                sizeof(sTimeZoneTable_TypeDef));

                    Std_MemRvsSelf(pBuf, Len);
                }
                else
                {
                    Len = MAX_TIMEZONE * sizeof(sTimeZoneTable_TypeDef);

                    offset = sizeof(sDate_time_s_TypeDef) + (pOadAys->OIB2 - 4) * 42;

                    fnFile_Read(FileId_RatePara,
                                FileItemInfoOffAddr_RatePara_TimeZonePara + offset,
                                pBuf,
                                Len);

                    for (j = 0; j < 14; j++)
                    {
                        Std_MemRvsSelf(pBuf + j * sizeof(sTimeZoneTable_TypeDef), sizeof(sTimeZoneTable_TypeDef));
                    }
                }
            }
            else if ((OIA_B == 0x4016) || (OIA_B == 0x4017)) //时段表
            {
                if (pOadAys->elementIndex != 0)
                {
                    offset = 42 * (pOadAys->elementIndex - 1) + (pOadAys->OIB2 - 6) * 42 * 8;
                    fnFile_Read(FileId_RatePara,
                                FileItemInfoOffAddr_RatePara_POTTablePara + offset,
                                pBuf,
                                42);

                    for (i = 0; i < 14; i++)
                    {
                        Std_MemRvsSelf(pBuf + i * sizeof(sPOTTable_TypeDef), sizeof(sPOTTable_TypeDef));
                    }

                    Len = 42 ;
                }
                else
                {
                    Len = 0 ;
                    for (i = 0 ; i < 8; i++)
                    {
                        offset = 42 * i + (pOadAys->OIB2 - 6) * 42 * 8;
                        fnFile_Read(FileId_RatePara,
                                    FileItemInfoOffAddr_RatePara_POTTablePara + offset,
                                    pBuf + i * 42,
                                    42);

                        for (j = 0; j < 14; j++)
                        {
                            Std_MemRvsSelf(pBuf + i * 42 + j * sizeof(sPOTTable_TypeDef), sizeof(sPOTTable_TypeDef));
                        }

                        Len += 42 ;
                    }
                }
            }
            else if (OIA_B == 0x4116)
            {
                if (pOadAys->elementIndex == 0)
                {
                    for (i = 0; i < 3; i++)
                    {
                        Std_MemRvsSelf(pBuf + i * sizeof(sDF24), sizeof(sDF24));
                    }
                    Len = 6;
                }
                else
                {
                    Std_MemRvsSelf(pBuf + (pOadAys->elementIndex - 1) * sizeof(sDF24), sizeof(sDF24));
                    Len = 2;
                }
            }
            break;

        case OIA1_INTERFACE:
        {
            if (OAD == 0xF2050201)
            {
                Std_Memcpy(pBuf, (u8 *)&TAB_Relay, 5);
                *(pBuf + 5) = Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus;
                *(pBuf + 6) = 0x01; //继电器开关属性  保持式
                *(pBuf + 7) = 0x00; //继电器接线状态 接入

                Len = 8;
            }
        }
        break;

        default:
            Len = ERROR;
            break;
    }
    return Len;
}

/*********************************************************************************************************
** Function name:   fnFill_OADData
** Descriptions:
** input parameters:  OAD:OAD
** output parameters:   OAD 根据读取到的邋OAD数据补充为标准格式(主要为存储的5字节高精度电能转为标准的8字节格式)
** Returned value:  转换后的数据长度
*********************************************************************************************************/
u8 fnFill_OADData(u32  OAD,  u8  *pDstBuf, u8  *pSrcBuf, u8 len)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    u8 i, temp[EGINT64_MYDATA_Len] ; // dyf del item
    u16  OIA_B = (OAD >> 16 & 0xFFFF);

    switch (pOadAys->OIA1)
    {
        case OIA1_ENERGY:

            for (i = 0 ; i < RE_ARRAY_LENGTH(ENERGY_Item); i++)
            {
                if (ENERGY_Item[i].OI == OIA_B)
                {
                    //item = i; // dyf del
                    break;
                }
            }

            if (i == RE_ARRAY_LENGTH(ENERGY_Item))
            {
                return ERROR;
            }

            if (pOadAys->AtrIndex == 0x04)  //高精度电能，属性4
            {
                len = 0;
                if (pOadAys->elementIndex == 0x00) //所有元素
                {
                    //根据费率数应答总电能
                    Std_Memset(pDstBuf, 0x00, (Bkgrd.PubData.nFl + 1) * DTYPE_INT64_Len);

                    for (i = 0; i < (Bkgrd.PubData.nFl + 1); i++)
                    {
                        Std_Memcpy(&temp[0], pSrcBuf + i * EGINT64_MYDATA_Len, EGINT64_MYDATA_Len);
                        Std_Memcpy(pDstBuf + i * DTYPE_INT64_Len, &temp[0], EGINT64_MYDATA_Len);
                        len += DTYPE_INT64_Len;
                    }
                }
                else
                {
                    len = DTYPE_INT64_Len;
                    Std_Memset(pDstBuf, 0x00, DTYPE_INT64_Len);
                    Std_Memcpy(pDstBuf, pSrcBuf, EGINT64_MYDATA_Len);
                }
            }
            else if (pOadAys->AtrIndex == 0x02)
            {
                Std_Memcpy(pDstBuf, pSrcBuf, len);
            }
            break;

        default:
            Std_Memcpy(pDstBuf, pSrcBuf, len);
            break;
    }

    return len;
}

/*********************************************************************************************************
** Function name:   fnGet_EvtRecordUnit_DataType
** Descriptions:
** input parameters:  OAD:OAD
** output parameters:   OAD 对应的数据类型,当为DTYPE_ARRAY等复杂类型时，后面存放数组数量，子项数据类型
** Returned value:
*********************************************************************************************************/
u8 fnGet_EvtRecordUnit_DataType(u32  OAD,  u8  *pDatatype, u8 Item, u8 *pBuf)
{
    u8   i, res = ERROR;

    OAD = OAD & 0xFFFF0FFF;

    if (Item < FileItemInfoNum_Evt_Max)
    {
        //       if(Item == FileItemInfoNum_Evt_Prg)
        //      {
        //          for(i = 0 ;i < 6;i++)
        //          {
        //              if(EvtPrg_StdRecList.Clist[i].OAD == OAD)
        //              {
        //                  if(EvtPrgStdRcdList_DataType[i] == DTYPE_ARRAY)
        //                  {
        //                      Std_Memcpy(pDatatype , &EvtPrgStdRcdList_DataType[i] , 3);
        //                      *(pDatatype + 1) = *pBuf;  //更新编程OAD个数
        //                      for(i = 0; i < *pBuf; i++)
        //                      {
        //                          *(pDatatype + 1 + 1 + i) = DTYPE_OAD;
        //                      }
        //
        //                  }
        //                  else
        //                      *pDatatype = EvtPrgStdRcdList_DataType[i];

        //                  res = SUCCESS;
        //                  break;
        //              }
        //          }

        //      }
        //      else if(Item == FileItemInfoNum_Evt_EventClr)
        //      {
        //          for(i = 0 ;i < 6;i++)
        //          {
        //              if(EvtClr_StdRecList.Clist[i].OAD == OAD)
        //              {
        //                  if(EvtClrStdRcdList_DataType[i] == DTYPE_ARRAY)
        //                  {
        //                      Std_Memcpy(pDatatype , &EvtClrStdRcdList_DataType[i] , 3);
        //                      *(pDatatype + 1) = *pBuf;  //更新编程OAD个数
        //
        //                  }
        //                  else
        //                      *pDatatype = EvtClrStdRcdList_DataType[i];

        //                  res = SUCCESS;
        //                  break;
        //              }
        //          }

        //      }
        //        else if(Item == FileItemInfoNum_Evt_PrgPOTTable)
        //      {
        //          for(i = 0 ;i < 7;i++)
        //          {
        //              if(EvtPrgTable_StdRecList.Clist[i].OAD == OAD)
        //              {
        //                  if(EvtPrgTableStdRcdList_DataType[i] == DTYPE_ARRAY)
        //                  {
        //                      Std_Memcpy(pDatatype , &EvtPrgTableStdRcdList_DataType[i] , 7);
        //
        //                  }
        //                  else
        //                      *pDatatype = EvtPrgTableStdRcdList_DataType[i];

        //                  res = SUCCESS;
        //                  break;
        //              }
        //          }

        //      }
        //       else if(Item == FileItemInfoNum_Evt_PrgHoliday)
        //      {
        //          for(i = 0 ;i < 7;i++)
        //          {
        //              if(EvtHldy_StdRecList.Clist[i].OAD == OAD)
        //              {
        //                  if(EvtHldyStdRcdList_DataType[i] == DTYPE_STRUCTURE)
        //                  {
        //                      Std_Memcpy(pDatatype , &EvtHldyStdRcdList_DataType[i] , 4);
        //
        //                  }
        //                  else
        //                      *pDatatype = EvtHldyStdRcdList_DataType[i];

        //                  res = SUCCESS;
        //                  break;
        //              }
        //          }

        //      }
        //      else if(Item == FileItemInfoNum_Evt_PrgQ)
        //      {
        //          for(i = 0 ;i < 5;i++)
        //          {
        //              if(EvtPrgQ_StdRecList.Clist[i].OAD == OAD)
        //              {
        //                  *pDatatype = EvtPrgQStdRcdList_DataType[i];
        //                  res = SUCCESS;
        //                  break;
        //              }
        //          }

        //      }
        //      else
        {
            for (i = 0 ; i < 5; i++)
            {
                if (EvtC7_StdRecList.Clist[i].OAD == OAD)
                {
                    *pDatatype = EvtStdRcdList_DataType[i];
                    res = SUCCESS;
                    break;
                }
            }
        }
    }

    if (res == SUCCESS)
    {
        if (*pDatatype == DTYPE_DATETIME_S)
        {
            u8 temp[20];
            Std_Memcpy(temp, pBuf, 7);
            if (fnJudge_Zero(pBuf, sizeof(sDate_time_s_TypeDef)))    //时间为全0时应答null
            {
                *pDatatype = DTYPE_NONE;
            }
        }
    }

    return res;
}

/*********************************************************************************************************
** Function name:   fnGet_FrzRecordUnit_DataType
** Descriptions:
** input parameters:  OAD:OAD
** output parameters:   OAD 对应的数据类型,当为DTYPE_ARRAY等复杂类型时，后面存放数组数量，子项数据类型
** Returned value:
*********************************************************************************************************/
u8 fnGet_FrzRecordUnit_DataType(u32  OAD,  u8  *pDatatype)
{
    OAD = OAD & 0xFFFF0FFF;

    if (Frz_StdRecList.Clist[0].OAD == OAD) //冻结序号
    {
        *pDatatype++ = DTYPE_UINT32;
        return SUCCESS;
    }
    if (Frz_StdRecList.Clist[1].OAD == OAD) //冻结时间
    {
        *pDatatype++ = DTYPE_DATETIME_S;
        return SUCCESS;
    }

    return ERROR;
}

/*********************************************************************
* @fn      fnUpDate_EvtParaOffPos
*
* @brief   更新 由于费率数变更后引起的事件记录关联对象属性表
*
*             电量的偏移地址
*
* @return
*/

void fnUpDate_EvtParaOffPos(void)
{
    u8 i, oadnum, item = FileItemInfoNum_Evt_Max, Newlen, Flag;
    sContextList_TypeDef  tmplist;

    u16 OffAddr, recordlen, tmp_OffPos;
    u8  *BufList, *pRecordBuf;

    BufList = (u8 *)fnDl698_Buffer_Alloc(512);
    if (BufList == NULL)
    {
        return ;
    }

    pRecordBuf = (u8 *)fnDl698_Buffer_Alloc(1024);
    if (pRecordBuf == NULL)
    {
        fnDl698_Buffer_Free(BufList);
        return ;
    }

    for (item = 0; item < FileItemInfoNum_Evt_Max; item++)
    {
        Std_Memset(BufList, 0, 512);
        Std_Memset(pRecordBuf, 0, 1024);

        Flag = 0x00;
        fnFile_Read(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[item].OffAddr, BufList, FileItemInfo_EvtCtxlist[item].Len);
        oadnum = *BufList;

        for (i = 0; i < oadnum; i++)
        {
            tmp_OffPos = tmplist.OffPos + tmplist.len;  //OAD偏移= 上一个OAD偏移 + 上一个OAD长度

            OffAddr = 3 + i * sizeof(sContextList_TypeDef);
            Std_Memcpy((u8 *)&tmplist, BufList + OffAddr, sizeof(sContextList_TypeDef));

            Newlen = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF), pRecordBuf);

            if (Newlen == 0)
            {
                if ((tmplist.OAD == 0xF1002200) || (tmplist.OAD == 0xF1008200))
                {
                    Newlen = 8;
                }
                else if ((tmplist.OAD == 0x40272300) || (tmplist.OAD == 0x40278200))
                {
                    Newlen = 1;
                }
                else if ((tmplist.OAD == 0xF0012500) || (tmplist.OAD == 0xF4028202))
                {
                    Newlen = 32;
                }
                else if ((tmplist.OAD == 0xF4022204) || (tmplist.OAD == 0xF4028204))
                {
                    Newlen = 16;
                }
            }

            if (tmplist.len != Newlen)
            {
                Flag = 0xAA;
                tmplist.len = Newlen;
            }

            if (Flag == 0xAA)   //长度有变更后偏移地址均需更新
            {
                if (i > 0)  //第一个OAD偏移固定，从第二个OAD开始计算
                {
                    tmplist.OffPos = tmp_OffPos;
                }
                Std_Memcpy(BufList + OffAddr, (u8 *)&tmplist, sizeof(sContextList_TypeDef));
            }
        }

        if (Flag == 0xAA)
        {
            recordlen = tmplist.OffPos + tmplist.len;  //更新总长度
            Std_Memcpy(BufList + 1, (u8 *)&recordlen, 2);
            //--------更新关联对象属性表-------------
            fnFile_Write(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[item].OffAddr, BufList, FileItemInfo_EvtCtxlist[item].Len);
        }
    }

    fnDl698_Buffer_Free(BufList);
    fnDl698_Buffer_Free(pRecordBuf);
}

/*********************************************************************
* @fn      fnUpDate_FrzMinParaOffPos   分钟冻结(8条曲线)
*
* @brief   更新 由于费率数变更后引起的冻结关联对象属性表
*
*             电量的偏移地址
*
* @return
*/
void fnUpDate_FrzMinParaOffPos(void)
{
    u8 i, j, oadnum,  Newlen, Flag = 0x00, line_item = 0xFF, Frzmin_lineFlag = 0xFF;
    sFrzCtxList_TypeDef  tmplist;

    u16 OffAddr, recordlen, tmp_OffPos;
    sFrzMinLinePara_TypeDef tempFrzMinLine[MAX_FRZMIN_LINE];
    OAD_Analyse_TypeDef  *tempOadAys;

    u8  *BufList, *pRecordBuf;

    BufList = (u8 *)fnDl698_Buffer_Alloc(512);
    if (BufList == NULL)
    {
        return ;
    }

    pRecordBuf = (u8 *)fnDl698_Buffer_Alloc(1024);
    if (pRecordBuf == NULL)
    {
        fnDl698_Buffer_Free(BufList);
        return ;
    }

    fnFile_Read(FileId_FrzCtxlist, FileItemInfoOffAddr_FrzCtxlist_Min, BufList, FileItemInfoLen_FrzCtxlist_Min);

    oadnum = *BufList;

    for (i = 0; i < MAX_FRZMIN_LINE; i++)
    {
        fnFile_Read(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[i].OffAddr, (u8 *)&tempFrzMinLine[i], sizeof(sFrzMinLinePara_TypeDef));
    }

    for (i = 0; i < oadnum; i++)
    {
        OffAddr = 3 + i * sizeof(sFrzCtxList_TypeDef);
        Std_Memcpy((u8 *)&tmplist, BufList + OffAddr, sizeof(sFrzCtxList_TypeDef));
        tempOadAys = (OAD_Analyse_TypeDef *)&tmplist.OAD;

        if (line_item != tempOadAys->AtrFeature)
        {
            line_item = tempOadAys->AtrFeature;
            tmp_OffPos = tmplist.OffPos;
        }
        else
        {
            line_item = tempOadAys->AtrFeature;
            tmp_OffPos = tempFrzMinLine[line_item].RecLen ;
        }

        Newlen = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF), pRecordBuf);

        if (tmplist.len != Newlen)
        {
            Flag = 0xAA;
            tmplist.len = Newlen;
        }
        //--------判每条事件记录长度---------------
        tmplist.OffPos = tmp_OffPos;

        recordlen = tmplist.len + tmplist.OffPos;

        tempFrzMinLine[line_item].RecLen = recordlen;
        tempFrzMinLine[line_item].LineRecLen = (u32)(tempFrzMinLine[line_item].RecLen * tempFrzMinLine[line_item].Depth);
        for (j = line_item; j < MAX_FRZMIN_LINE; j++)
        {
            if (j == 0)
            {
                tempFrzMinLine[j].LineOffAdder = 0;
            }
            else
            {
                tempFrzMinLine[j].LineOffAdder = (u32)(tempFrzMinLine[j - 1].LineRecLen + tempFrzMinLine[j - 1].LineOffAdder);
            }
        }

        if (Flag == 0xAA)   //长度有变更后偏移地址均需更新
        {
            if (line_item == Frzmin_lineFlag)    //长度发生变化的分钟冻结曲线数据更新
            {
                Std_Memcpy(BufList + OffAddr, (u8 *)&tmplist, sizeof(sFrzCtxList_TypeDef));
            }
        }
    }

    if (Flag == 0xAA)
    {
        recordlen = tmplist.OffPos + tmplist.len;  //更新总长度
        Std_Memcpy(BufList + 1, (u8 *)&recordlen, 2);
        //--------更新关联对象属性表-------------
        fnFile_Write(FileId_FrzCtxlist, FileItemInfoOffAddr_FrzCtxlist_Min, BufList, FileItemInfoLen_FrzCtxlist_Min);

        for (j = 0; j < MAX_FRZMIN_LINE; j++)
        {
            Std_Memcpy(BufList, (u8 *)&tempFrzMinLine[j], sizeof(sFrzMinLinePara_TypeDef));
            fnFile_Write(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[j].OffAddr, BufList, sizeof(sFrzMinLinePara_TypeDef));
        }
    }

    fnDl698_Buffer_Free(BufList);
    fnDl698_Buffer_Free(pRecordBuf);
}

/*********************************************************************
* @fn      fnUpDate_EvtParaOffPos
*
* @brief   更新 由于费率数变更后引起的冻结关联对象属性表
*
*             电量的偏移地址
*
* @return
*/
void fnUpDate_FrzParaOffPos(void)
{
    u8 i, oadnum, item, Newlen, Flag;
    sFrzCtxList_TypeDef  tmplist;

    u16 OffAddr, recordlen, tmp_OffPos;
    u8  *BufList, *pRecordBuf;

    for (item = 0; item < FileItemInfoNum_Frz_MAX; item++)
    {
        if (item == FileItemInfoNum_Frz_MinFrz)  //分钟冻结读取8条曲线头
        {
            fnUpDate_FrzMinParaOffPos();    //分钟冻结
        }
        else
        {
            BufList = (u8 *)fnDl698_Buffer_Alloc(512);
            if (BufList == NULL)
            {
                break;
            }

            pRecordBuf = (u8 *)fnDl698_Buffer_Alloc(1024);
            if (pRecordBuf == NULL)
            {
                fnDl698_Buffer_Free(BufList);
                break;
            }
            Std_Memset(BufList, 0, 512);
            Std_Memset(pRecordBuf, 0, 1024);

            Flag = 0x00;
            fnFile_Read(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[item].OffAddr, BufList, FileItemInfo_FrzCtxlist[item].Len);
            oadnum = *BufList;

            for (i = 0; i < oadnum; i++)
            {
                if (i == 0)
                {
                    tmp_OffPos =  Frz_StdRecList.reclen;
                }
                else
                {
                    tmp_OffPos = tmplist.OffPos + tmplist.len;    //OAD偏移= 上一个OAD偏移 + 上一个OAD长度
                }

                OffAddr = 3 + i * sizeof(sFrzCtxList_TypeDef);
                Std_Memcpy((u8 *)&tmplist, BufList + OffAddr, sizeof(sFrzCtxList_TypeDef));

                Newlen = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF), pRecordBuf);

                if (tmplist.len != Newlen)
                {
                    Flag = 0xAA;
                    tmplist.len = Newlen;
                }

                if (Flag == 0xAA)   //长度有变更后偏移地址均需更新
                {
                    tmplist.OffPos = tmp_OffPos;

                    Std_Memcpy(BufList + OffAddr, (u8 *)&tmplist, sizeof(sFrzCtxList_TypeDef));
                }
            }

            if (Flag == 0xAA)
            {
                recordlen = tmplist.OffPos + tmplist.len;  //更新总长度
                Std_Memcpy(BufList + 1, (u8 *)&recordlen, 2);
                //--------更新关联对象属性表-------------
                fnFile_Write(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[item].OffAddr, BufList, FileItemInfo_FrzCtxlist[item].Len);
            }

            fnDl698_Buffer_Free(BufList);
            fnDl698_Buffer_Free(pRecordBuf);
        }
    }
}

/*********************************************************************************************************
** Function name:   fnGetOAD_MemoryLen
** Descriptions:
** input parameters:  OAD:OAD
** output parameters:   OAD 对应的数据类型,当为DTYPE_ARRAY等复杂类型时，后面存放数组数量，子项数据类型
** Returned value:
*********************************************************************************************************/
u16 fnGet_OADDataType(u32  OAD,  u8  *pDatatype)
{
    OAD_Analyse_TypeDef *pOadAys;

    u8  num, i, item, line;

    u16 OIA_B = (OAD >> 16 & 0xFFFF);

    OAD = OAD & 0xFFFF0FFF;
    pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    switch (pOadAys->OIA1)
    {
        case OIA1_ENERGY:

            for (i = 0 ; i < RE_ARRAY_LENGTH(ENERGY_Item); i++)
            {
                if (ENERGY_Item[i].OI == OIA_B)
                {
                    item = ENERGY_Item[i].Item;
                    break;
                }
            }

            if (i == RE_ARRAY_LENGTH(ENERGY_Item))
            {
                return ERROR;
            }

            if (pOadAys->elementIndex == 0)
            {
                *pDatatype++ = DTYPE_ARRAY;

                //根据费率数应答总电能

                *pDatatype++ =  1;
            }

            if ((pOadAys->AtrIndex == 4) || (pOadAys->AtrIndex == 8))
            {
                *pDatatype++ = DTYPE_UINT64;
            }
            else if (pOadAys->AtrIndex == 6)
            {
                *pDatatype++ = DTYPE_UINT8;
            }
            else
            {
                *pDatatype++ = DTYPE_UINT32;
            }

            break;

        //       #if(nPhs==ThreePhs)
        //      case OIA1_NEED:
        //
        //          for(i = 0 ;i < RE_ARRAY_LENGTH(NEED_Item);i++)
        //          {
        //              if(NEED_Item[i].OI == OIA_B)
        //              {
        //                  item = NEED_Item[i].Item;
        //                  break;
        //              }
        //          }
        //
        //          if(i == RE_ARRAY_LENGTH(NEED_Item))
        //              return ERROR;

        //          if(pOadAys->elementIndex == 0)
        //          {
        //              *pDatatype++ = DTYPE_ARRAY;

        //              //根据费率数应答总电能
        //              *pDatatype++ = Bkgrd.PubData.nFl + 1;
        //          }
        //
        //          *pDatatype++ = DTYPE_STRUCTURE;
        //          *pDatatype++ = 2;
        //          if( (item == PtQDmnd)||(item == NtQDmnd) )
        //              *pDatatype++ = DTYPE_INT32;
        //          else
        //              *pDatatype++ = DTYPE_UINT32;
        //
        //          *pDatatype++ = DTYPE_DATETIME_S;
        //
        //          break;
        //      #endif

        case OIA1_VAR:

            for (i = 0 ; i < RE_ARRAY_LENGTH(VAR_Item); i++)
            {
                if (VAR_Item[i].OI == OIA_B)
                {
                    item = VAR_Item[i].Item;
                    line = i;
                    break;
                }
            }
            if (i == RE_ARRAY_LENGTH(VAR_Item))
            {
                return ERROR;
            }

            num = 0;
            if ((item == Var_V) || (item == Var_Angle) || (item == Var_Angle2))
            {
                if (pOadAys->elementIndex == 0)
                {
                    *pDatatype++ = DTYPE_ARRAY;
                    num = 3;
                    *pDatatype++ = num;
                }
            }
            else if ((item == Var_I) || (item == Var_WaveUnblU) || (item == Var_WaveUnblI))
            {
                if ((pOadAys->elementIndex == 0) && ((pOadAys->AtrIndex == 2) || (pOadAys->AtrIndex == 5)))
                {
                    *pDatatype++ = DTYPE_ARRAY;
                    num = 3;
                    *pDatatype++ = num;
                }
            }
            else if ((item == Var_Pw) || (item == Var_Pq) || (item == Var_Ps) || (item == Var_Pf) ||
                     (item == Var_AveragePw) || (item == Var_AveragePq) || (item == Var_AveragePs))
            {
                if (pOadAys->elementIndex == 0)
                {
                    *pDatatype++ = DTYPE_ARRAY;
                    num = 4;
                    *pDatatype++ = num;
                }
            }
            else if ((item == Var_HpercentU) || (item == Var_HpercentI) ||
                     (item == Var_HUrms) || (item == Var_HIrms) || (item == Var_HPrms))
            {
                if ((pOadAys->AtrIndex == 2) || (pOadAys->AtrIndex == 3) || (pOadAys->AtrIndex == 4))
                {
                    if (pOadAys->elementIndex == 0)
                    {
                        *pDatatype++ = DTYPE_ARRAY;
                        num = nHarmonic;
                        *pDatatype++ = num;
                    }
                }
                else if (pOadAys->AtrIndex == 5)
                {
                    *pDatatype++ = DTYPE_UINT8;
                }
                else if (pOadAys->AtrIndex == 7)
                {
                    if (pOadAys->elementIndex == 0)
                    {
                        *pDatatype++ = DTYPE_STRUCTURE;
                        *pDatatype++ = 2;
                        *pDatatype++ = DTYPE_UINT32;
                        *pDatatype++ = DTYPE_UINT32;
                    }
                    else
                    {
                        *pDatatype++ = DTYPE_UINT32;
                    }
                }
            }
            else if (item == Var_PowerOFFData)
            {
                if (pOadAys->elementIndex == 0)
                {
                    *pDatatype++ = DTYPE_STRUCTURE;
                    num = 3;
                    *pDatatype++ = num;

                    *pDatatype++ = DTYPE_DATETIME_S;

                    *pDatatype++ = DTYPE_ARRAY;
                    num = 3;
                    *pDatatype++ = num;
                    *pDatatype++ = DTYPE_UINT16;
                    *pDatatype++ = DTYPE_UINT16;
                    *pDatatype++ = DTYPE_UINT16;

                    *pDatatype++ = DTYPE_ARRAY;
                    num = 3;
                    *pDatatype++ = num;
                    *pDatatype++ = DTYPE_INT32;
                    *pDatatype++ = DTYPE_INT32;
                    *pDatatype++ = DTYPE_INT32;
                }
                else if (pOadAys->elementIndex == 1)
                {
                    *pDatatype++ = DTYPE_DATETIME_S;
                }
                else if (pOadAys->elementIndex == 2)
                {
                    *pDatatype++ = DTYPE_ARRAY;
                    num = 3;
                    *pDatatype++ = num;
                    *pDatatype++ = DTYPE_UINT16;
                    *pDatatype++ = DTYPE_UINT16;
                    *pDatatype++ = DTYPE_UINT16;
                }
                else if (pOadAys->elementIndex == 3)
                {
                    *pDatatype++ = DTYPE_ARRAY;
                    num = 3;
                    *pDatatype++ = num;
                    *pDatatype++ = DTYPE_INT32;
                    *pDatatype++ = DTYPE_INT32;
                    *pDatatype++ = DTYPE_INT32;
                }

                break;
            }
            else if (item == Var_TEMP)
            {
                if ((pOadAys->elementIndex == 0) && (pOadAys->AtrIndex == 4)) //端子温度
                {
                    *pDatatype++ = DTYPE_ARRAY;
                    num = 8;
                    *pDatatype++ = num;
                }
            }
            else if (item == Var_TnT_Chang)
            {
                if (pOadAys->elementIndex == 0)
                {
                    *pDatatype++ = DTYPE_ARRAY;
                    num = 4;
                    *pDatatype++ = num;
                }
            }
            else if (item == Var_Mstate)
            {
                if ((pOadAys->AtrIndex == 2) && (pOadAys->elementIndex == 0))
                {
                    *pDatatype++ = DTYPE_ARRAY;
                    num = 7;
                    *pDatatype++ = num;
                }
            }
            else if (item == Var_ReportState)
            {
                if ((pOadAys->AtrIndex == 2) || (pOadAys->AtrIndex == 4))
                {
                    *pDatatype++ = DTYPE_BITSTRING;
                }
                else if (pOadAys->AtrIndex == 5)
                {
                    *pDatatype++ = DTYPE_ENUM;
                }
            }
            else if ((item == Var_EligRateUA) || (item == Var_EligRateUB) || (item == Var_EligRateUC))
            {
                if (pOadAys->elementIndex == 0)
                {
                    *pDatatype++ = DTYPE_STRUCTURE;
                    num = 2;
                    *pDatatype++ = num;
                }
                for (i = 0; i < (num + 1); i++)
                {
                    *pDatatype++ = DTYPE_STRUCTURE;
                    *pDatatype++ = 5;
                    *pDatatype++ = DTYPE_UINT32;
                    *pDatatype++ = DTYPE_UINT16;
                    *pDatatype++ = DTYPE_UINT16;
                    *pDatatype++ = DTYPE_UINT32;
                    *pDatatype++ = DTYPE_UINT32;
                }
                break;
            }
            //--------------------------------------
            for (i = 0; i < (num + 1); i++)
            {
                *pDatatype++ = VAR_Item[line].Atr_type;
            }

            break;

        case OIA1_PARA:

            for (i = 0 ; i < RE_ARRAY_LENGTH(PARA_VAR_Item); i++)
            {
                if (PARA_VAR_Item[i].OI == OIA_B)
                {
                    break;
                }
            }
            if (i == RE_ARRAY_LENGTH(PARA_VAR_Item))
            {
                return ERROR;
            }

            if ((OIA_B == 0x4014) || (OIA_B == 0x4015)) //时区表
            {
                if (pOadAys->elementIndex == 0)
                {
                    *pDatatype++ = DTYPE_ARRAY;
                    *pDatatype++ = 14;
                }

                *pDatatype++ = DTYPE_STRUCTURE;
                *pDatatype++ = 3;
                *pDatatype++ = DTYPE_UINT8;
                *pDatatype++ = DTYPE_UINT8;
                *pDatatype++ = DTYPE_UINT8;
            }
            else if ((OIA_B == 0x4016) || (OIA_B == 0x4017)) //时段表
            {
                if (pOadAys->elementIndex == 0)
                {
                    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_nPOTTable, &num, 1);
                    *pDatatype++ = DTYPE_ARRAY;
                    *pDatatype++ = num;
                }

                fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_nDayPOT, &num, 1);

                *pDatatype++ = DTYPE_ARRAY;
                *pDatatype++ = num;

                *pDatatype++ = DTYPE_STRUCTURE;
                *pDatatype++ = 3;
                *pDatatype++ = DTYPE_UINT8;
                *pDatatype++ = DTYPE_UINT8;
                *pDatatype++ = DTYPE_UINT8;
            }
            else if (OIA_B == 0x4116)
            {
                if (pOadAys->elementIndex == 0)
                {
                    *pDatatype++ = DTYPE_ARRAY;
                    *pDatatype++ = 3;
                }
                *pDatatype++ = DTYPE_STRUCTURE;
                *pDatatype++ = 2;
                *pDatatype++ = DTYPE_UINT8;
                *pDatatype++ = DTYPE_UINT8;
            }
            else if (OAD == 0x40270300)
            {
                *pDatatype++ = DTYPE_UINT8;
                *pDatatype++ = 1;
            }
            else if (OAD == 0x40270200)
            {
                *pDatatype++ = DTYPE_ENUM;
                *pDatatype++ = 1;
            }
            else
            {
                *pDatatype++ = PARA_VAR_Item[i].Atr_type;
            }

            break;

        case OIA1_INTERFACE:
            if (OAD == 0xF1000400) //密钥版本号
            {
                *pDatatype++ = DTYPE_OCT_STR;
                *pDatatype++ = 16;
            }
            else if (OAD == 0xF2050201)
            {
                *pDatatype++ = DTYPE_STRUCTURE;
                *pDatatype++ = 4;
                *pDatatype++ = DTYPE_STRING;
                *pDatatype++ = DTYPE_ENUM;
                *pDatatype++ = DTYPE_ENUM;
                *pDatatype++ = DTYPE_ENUM;
            }
            // 管理模组ESAM序列号
            //              else if( (OAD == 0xF1000200) || (OAD == 0xF1008200) )
            else if (OAD == 0xF1000200)
            {
                *pDatatype++ = DTYPE_OCT_STR;
                *pDatatype++ = 8;
            }
            // 下载方标识
            else if (OAD == 0xF0010500)
            {
                *pDatatype++ = DTYPE_STRING;
                *pDatatype++ = 32;
            }
            // 升级前软件版本号
            else if (OAD == 0xF4020204)
            {
                *pDatatype++ = DTYPE_STRING;
                *pDatatype++ = 16;
            }
            //              // 升级后软件版本号
            //              else if(OAD == 0xF4028204)
            //              {
            //                  *pDatatype++ = DTYPE_STRING;
            //                  *pDatatype++ = 16;
            //              }
            // 升级应用名称
            else if (OAD == 0xF4020202)
            {
                *pDatatype++ = DTYPE_STRING;
                *pDatatype++ = 32;
            }

            break;

        default:

            break;
    }
    return SUCCESS;
}

u16 fnGet_MngOADDataType(u32  OAD,  u8  *pDatatype, u8 nTarf)
{
    OAD_Analyse_TypeDef *pOadAys;

    u8   i, item ;

    u16 OIA_B = (OAD >> 16 & 0xFFFF);

    OAD = OAD & 0xFFFF0FFF;
    pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    switch (pOadAys->OIA1)
    {
        case OIA1_ENERGY:

            for (i = 0 ; i < RE_ARRAY_LENGTH(ENERGY_Item); i++)
            {
                if (ENERGY_Item[i].OI == OIA_B)
                {
                    item = ENERGY_Item[i].Item;
                    break;
                }
            }

            if (i == RE_ARRAY_LENGTH(ENERGY_Item))
            {
                return ERROR;
            }

            if (pOadAys->elementIndex == 0)
            {
                *pDatatype++ = DTYPE_ARRAY;

                //根据费率数应答总电能

                *pDatatype++ = nTarf + 1;
            }

            //          if( (pOadAys->AtrIndex == 4)||(pOadAys->AtrIndex == 8) )
            //              *pDatatype++ = DTYPE_UINT64;
            //
            //          else if(pOadAys->AtrIndex == 6)
            //              *pDatatype++ = DTYPE_UINT8;
            //          else
            //              *pDatatype++ = DTYPE_UINT32;

            for (i = 0; i < (nTarf + 1); i++)
            {
                if (item >= AllPEg) //组合电能，无符号
                {
                    if (pOadAys->AtrIndex == 4)
                    {
                        *pDatatype++ = DTYPE_INT64;
                    }
                    else
                    {
                        *pDatatype++ = DTYPE_INT32;
                    }
                }
                else            //累计电能，有符号
                {
                    if (pOadAys->AtrIndex == 4)
                    {
                        *pDatatype++ = DTYPE_UINT64;
                    }
                    else
                    {
                        *pDatatype++ = DTYPE_UINT32;
                    }
                }
            }

            break;

        default:

            break;
    }
    return SUCCESS;
}

/*********************************************************************************************************
** Function name:       fnGet_CsdNum
** Descriptions:        读取OAD对应的默认所有列(标准事件记录单元 + 设置的关联对象属性表)
** input parameters:    OAD ;     uBuf: 临时缓存
** output parameters:   pParaBuf 所有列内容
** Returned value:      csdNum
*********************************************************************************************************/
u8 fnGet_CsdNum(u32 OAD, u8 *pParaBuf, u8 *uBuf)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    u16 OIA_B = (OAD >> 16 & 0xFFFF);
    u8 i, item = FileItemInfoNum_Evt_Max, csdNum = 0, class_id;
    u8 stdnum, offset;
    sContextList_TypeDef    tmplist1;
    sFrzCtxList_TypeDef tmplist2;
    u8  *BufList;

    BufList = uBuf + 512;

    if (pOadAys->OIA1 == OIA1_EVENT)
    {
        item = fnGet_EvtItem(OIA_B, &class_id);
        if (item >= FileItemInfoNum_Evt_Max)
        {
            return csdNum;
        }

        //-------读取关联对象属性表-----------
        fnFile_Read(FileId_EvtCtxlist,
                    FileItemInfo_EvtCtxlist[item].OffAddr,
                    BufList,
                    FileItemInfo_EvtCtxlist[item].Len);

        Std_Memcpy((u8 *)&stdnum, EvtStdlist[item].Addr, 1);    //标准事件记录单元OAD个数

        Std_Memset(uBuf, 0x00, 5 * stdnum);
        for (i = 0; i < stdnum; i++) //--5列标准事件单元----
        {
            offset = 3 + sizeof(sContextList_TypeDef) * i;
            Std_MemRvs(uBuf + i * 5 + 1, EvtStdlist[item].Addr + offset, 4);
        }

        csdNum = *BufList + stdnum; //加上标准事件记录单元 5列
        BufList += 3;  //偏移1byte OADNum + 2byte recordLen

        for (i = stdnum; i < csdNum; i++)
        {
            Std_Memcpy((u8 *)&tmplist1, BufList, sizeof(sContextList_TypeDef));
            Std_MemRvs(uBuf + i * 5 + 1, (u8 *)&tmplist1.OAD, 4);
            BufList += sizeof(sContextList_TypeDef);
        }
    }
    else if (pOadAys->OIA1 == OIA1_FREEZE)
    {
        //冻结
        item = fnGet_FrzItem(OIA_B);
        if (item >= FileItemInfoNum_Frz_MAX)
        {
            return csdNum;
        }

        //-------读取关联对象属性表-----------
        fnFile_Read(FileId_FrzCtxlist,
                    FileItemInfo_FrzCtxlist[item].OffAddr,
                    BufList,
                    FileItemInfo_FrzCtxlist[item].Len);

        stdnum = Frz_StdRecList.num;    //标准事件记录单元OAD个数

        csdNum = *BufList + stdnum; //加上标准记录单元 2列
        BufList += 3;  //偏移1byte OADNum + 2byte recordLen

        Std_Memset(uBuf, 0x00, 5 * csdNum);
        for (i = 0; i < stdnum; i++) //--2列标准事件单元----
        {
            Std_MemRvs(uBuf + i * 5 + 1, (u8 *)&Frz_StdRecList.Clist[i].OAD, 4);
        }

        for (i = stdnum; i < csdNum; i++)
        {
            Std_Memcpy((u8 *)&tmplist2, BufList, sizeof(sFrzCtxList_TypeDef));
            Std_MemRvs(uBuf + i * 5 + 1, (u8 *)&tmplist2.OAD, 4);
            BufList += sizeof(sFrzCtxList_TypeDef);
        }
    }

    if (csdNum > 150)   //合法性判断，不允许超过150个OAD
    {
        csdNum = 5;
    }

    return csdNum;
}

/*********************************************************************************************************
** Function name:       fnGet_EvtItem
** Descriptions:        根据OI读取事件记录序号
** input parameters:    OIA_B ;     uBuf: 临时缓存
** output parameters:   cid 对应的class
** Returned value:      事件记录序号
*********************************************************************************************************/
u8 fnGet_EvtItem(u16 OIA_B, u8 *cid)
{
    u8 i, item = FileItemInfoNum_Evt_Max;

    for (i = 0 ; i < RE_ARRAY_LENGTH(Event_Item); i++)
    {
        if (Event_Item[i].OI == OIA_B)
        {
            item = Event_Item[i].Item ;
            break;
        }
    }
    //   #if(nPhs==ThreePhs)
    //  if(item < FileItemInfoNum_Evt_PtOverNeed)
    //      *cid = ITEMCLASS24;
    //  #else
    ////    if(item == FileItemInfoNum_Evt_OverCur)
    ////        *cid = ITEMCLASS24;
    //  #endif
    ////    else
    *cid = ITEMCLASS7;

    return item;
}

/*********************************************************************************************************
** Function name:       fnGet_FrzItem
** Descriptions:        根据OI读取冻结序号
** input parameters:    OI
** output parameters:
** Returned value:      冻结序号
*********************************************************************************************************/
u8 fnGet_FrzItem(u16 OIA_B)
{
    u8 i, item = FileItemInfoNum_Frz_MAX;

    for (i = 0 ; i < RE_ARRAY_LENGTH(Frz_Item); i++)
    {
        if (Frz_Item[i].OI == OIA_B)
        {
            item = Frz_Item[i].Item ;
            break;
        }
    }

    return item;
}

/*********************************************************************
* @fn      fnGet_EvtRecord
*
* @brief
*
* @param
*
* @return
*/
u8 fnGet_EvtRecord(
    u32     OAD,            //读取事件记录OAD,元素索引表示读取第几次
    u8  *pParBuf,       //通讯下发的需要读取的RCSD信息
    u8  *uBuf,      //动态缓存通讯buf,在fnDl698_GetRecordValue统一申请,2K
    u8      *pRetBuf,       //获取到需应答数据，按698格式封装好
    u16     *pLen,      //数据长度
    u8      *blockRsp,
    u8      CheckSec
)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    sContextList_TypeDef    tmplist;
    u8 *pRecordBuf, *pCtxlistBuf, *pDataBuf,  *pSelectlistBuf;

    u16 OIA_B = (OAD >> 16 & 0xFFFF), len, stdoffpos = 0, temp16;
    u16 startlen,  maxlen, recordlen;
    u8 res = DATA_ACCESS_RESULT_SUC;

    u32 temp_oad, OffAddr, evtsumcnt, maxcnt;

    //  u8  pParlen;
    u8  type[20], item = 0, class_id, selector ;
    u8  oadnum, rcsd_num, csd_num, chk_num, record_num = 0, stdnum;
    u8  tempu8, startitem, enditem ; // dyf del tempcount
    u8  i, j, k;

    sDate_time_s_TypeDef time1, time2, timesrc;
    sCommSize_TypeDef  tempsize;

    //uBuf申请了2K空间:
    //1、uBuf[0]~uBuf[511]  数据交换临时缓存
    //2、uBuf[512]~uBuf[911]   从E2获取到的关联对象属性表

    //4、uBuf[1024]~uBuf[2048] 从E2获取到的单条事件记录缓存
    pCtxlistBuf =  uBuf + 512;
    pSelectlistBuf = uBuf + 1024;
    pRecordBuf = uBuf + 1536;

    selector = *pParBuf++;

    if (selector == 1) //方法1
    {
        Std_MemRvs((u8 *)&temp_oad, pParBuf, 4);
        tempu8 = 4;
        tempu8 += fnDl698AL_GetData_Len(1, 0, pParBuf + 4);
        Std_Memcpy(uBuf, pParBuf + 4, tempu8 - 4);  //除去OAD
        pParBuf += tempu8;

        for (i = 1 ; i < 3; i++) //只支持按照事件发生/结束事件索引
        {
            if (EvtC7_StdRecList.Clist[i].OAD == temp_oad)
            {
                stdoffpos = EvtC7_StdRecList.Clist[i].OffPos;
                if (*uBuf++ != DTYPE_DATETIME_S)
                {
                    selector = 0xFF;
                }
                else
                {
                    Std_MemRvs((u8 *)&time1, uBuf, 7);
                }
                break;
            }
        }

        if (i == 3)
        {
            selector = 0xFF;
        }
    }
    else if (selector == 2) //方法2
    {
        Std_MemRvs((u8 *)&temp_oad, pParBuf, 4);
        tempu8 = 4;
        tempu8 += fnDl698AL_GetData_Len(1, 0, pParBuf + tempu8);    //起始时间

        tempu8 += fnDl698AL_GetData_Len(1, 0, pParBuf + tempu8);    //结束时间

        tempu8 += fnDl698AL_GetData_Len(1, 0, pParBuf + tempu8);    //间隔

        Std_Memcpy(uBuf, pParBuf + 4, tempu8 - 4);  //除去OAD

        pParBuf += tempu8;

        for (i = 1 ; i < 3; i++)
        {
            if (EvtC7_StdRecList.Clist[i].OAD == temp_oad)
            {
                stdoffpos = EvtC7_StdRecList.Clist[i].OffPos;
                if (*uBuf++ != DTYPE_DATETIME_S)
                {
                    selector = 0xFF;
                }
                else
                {
                    Std_MemRvs((u8 *)&time1, uBuf, 7);
                    uBuf += 7;
                    if (*uBuf++ != DTYPE_DATETIME_S)
                    {
                        selector = 0xFF;
                    }
                    else
                    {
                        Std_MemRvs((u8 *)&time2, uBuf, 7);
                        //uBuf += 7;
                        //uBuf += 4;  //TI
                    }
                }
                break;
            }
        }

        if (i == 3)
        {
            selector = 0xFF;
        }
    }
    else if (selector == 9) //方法9
    {
        rcsd_num = *pParBuf++;

        if (rcsd_num == 0)
        {
            selector = 0xFF;
        }
    }
    else
    {
        selector = 0xFF;
    }

    //--------------------------------------------
    csd_num = *pParBuf++;
    if (csd_num > 150)  //合法性判断，不允许超过150个OAD
    {
        csd_num = 5;
    }

    item = fnGet_EvtItem(OIA_B, &class_id);

    if (csd_num == 0)
    {
        //若列号为0时，获取总列数
        csd_num = fnGet_CsdNum(OAD, pParBuf, uBuf);
    }
    else
    {
        Std_Memcpy(uBuf, pParBuf, csd_num * 5);
    }

    if (*blockRsp == false) //封装关联对象属性表
    {
        *pRetBuf++ = csd_num;
        *pLen += 1;

        len = csd_num * 5;
        Std_Memcpy(pRetBuf, uBuf, len);
        Std_Memcpy(pSelectlistBuf, uBuf, len);
        pRetBuf += len;
        *pLen += len;
    }

    if (class_id == ITEMCLASS7)
    {
        if (pOadAys->AtrIndex != 2)
        {
            res = DATA_ACCESS_RESULT_DENY;
        }
    }
    else
    {
        //      if( (item == FileItemInfoNum_Evt_QtOverNeed)||
        //          (item == FileItemInfoNum_Evt_OverPf) )
        //      {
        //          if( (pOadAys->AtrIndex <6) || (pOadAys->AtrIndex > 9) )  //4
        //              res =  DATA_ACCESS_RESULT_DENY;
        //      }
        //      else
        {
            if ((pOadAys->AtrIndex < 7) || (pOadAys->AtrIndex > 9))
            {
                res = DATA_ACCESS_RESULT_DENY;
            }
        }
    }

    if (selector == 0xFF)
    {
        res = DATA_ACCESS_RESULT_DENY;
    }
    else if (item >= FileItemInfoNum_Evt_Max)
    {
        res = DATA_ACCESS_RESULT_UNDEF;
    }

    if (CheckSec == TRUE) //液晶显示读取，主动上报读掉电事件记录时不判安全权限
    {
        if (fnDl698AL_Get_OIOpSec(OIA_B, DL698AL_APDU_TAG_GETREQ, gDl698AL_Server.pAlChan[Secret.Chan].sec_data.SecType) == false)
        {
            res = DATA_ACCESS_RESULT_SECNMATH;
        }
    }
    //---------异常应答---------------
    if (res != DATA_ACCESS_RESULT_SUC)
    {
        *pRetBuf++ = 0x00;
        *pRetBuf++ = res;
        *pLen += 2;

        return DATA_ACCESS_RESULT_SUC;  //需应答关联对象属性表
    }

    //------正常应答--应答0~n条记录--------------
    pDataBuf = pRetBuf + 2; //预留两字节封装CHIOCE部分

    //---------标准事件记录单元OAD个数------------------
    Std_Memcpy((u8 *)&oadnum, EvtStdlist[item].Addr, 1);
    //------读取关联对象属性表--------
    fnFile_Read(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[item].OffAddr, pCtxlistBuf, FileItemInfo_EvtCtxlist[item].Len);

    oadnum += *pCtxlistBuf;

    Std_Memcpy((u8 *)&recordlen, pCtxlistBuf + 1, 2);

    //---------读取当前记录次数---------------
    OffAddr = 0;
    if (class_id == ITEMCLASS7)
    {
        fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, &evtsumcnt, 4);
    }
    else
    {
        //      if( (item == FileItemInfoNum_Evt_QtOverNeed)||
        //          (item == FileItemInfoNum_Evt_OverPf) )
        //      {
        //          OffAddr = (pOadAys->AtrIndex - 6) * sizeof( sEvtRcdHead_TypeDef ) ;
        //          fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr + OffAddr, &evtsumcnt ,4 );
        //      }
        //      else
        {
            OffAddr = (pOadAys->AtrIndex - 7) * sizeof(sEvtRcdHead_TypeDef) ;
            fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr + OffAddr, &evtsumcnt, 4);
        }
    }

    maxcnt = (u8)MAX_EVRECORD_TABLE[item];    //获取最大记录数

    if (evtsumcnt != 0)
    {
        if ((selector == 1) || (selector == 2)) //搜索全部
        {
            if (evtsumcnt > maxcnt)
            {
                startitem = maxcnt;
            }
            else
            {
                startitem = evtsumcnt;
            }

            enditem = 0;
        }
        else        //方法9搜索1条
        {
            if ((rcsd_num > evtsumcnt) || (rcsd_num > maxcnt))
            {
                startitem = 0 ;
                enditem = 0 ;
            }
            else
            {
                startitem = rcsd_num ;
                enditem = startitem - 1;
            }
        }

        fnReadConnSize(&tempsize, Secret.Chan, Secret.CA);
        //------------------------------------------
        for (i = startitem; i > enditem; i--)
        {
            //---------读取一条事件记录，再根据读取列筛选内容---------------------
            if (class_id == ITEMCLASS7)
            {
                OffAddr = FileItemInfo_EvtRecord[item].OffAddr;
            }
            else
            {
                //              if( (item == FileItemInfoNum_Evt_QtOverNeed)||
                //                  (item == FileItemInfoNum_Evt_OverPf) )
                //              {
                //                  OffAddr = FileItemInfo_EvtRecord[item].OffAddr + (u32)((pOadAys->AtrIndex - 6) * recordlen * maxcnt);
                //              }
                //              else
                {
                    //--class24存储空间分配: 10条A相 + 10条B相 + 10条C相-----------------
                    OffAddr = FileItemInfo_EvtRecord[item].OffAddr + (u32)((pOadAys->AtrIndex - 7) * recordlen * maxcnt) ;
                }
            }

            temp16 = (u16)(evtsumcnt % maxcnt);
            temp16 = (temp16 + i * (maxcnt - 1)) % maxcnt;

            OffAddr += (u32)temp16 * (u32)recordlen;

            fnFile_Read(FileId_EvtRecord,  OffAddr, pRecordBuf, recordlen);

            Std_Memcpy((u8 *)&timesrc, pRecordBuf + stdoffpos, 7);

            u8 temp1, temp2;

            if (selector == 1)
            {
                temp1 = fnDFCompData((u8 *)&timesrc, (u8 *)&time1, 7);

                if (temp1 == 0) //相等
                {
                    chk_num = csd_num;
                    record_num = 1;
                }
                else
                {
                    chk_num = 0;
                }
            }
            else if (selector == 2)
            {
                temp1 = fnDFCompData((u8 *)&timesrc, (u8 *)&time1, 7);
                temp2 = fnDFCompData((u8 *)&timesrc, (u8 *)&time2, 7);

                if ((temp1 == 0xFF) || (temp2 != 0xFF))
                {
                    chk_num = 0;
                }
                else
                {
                    chk_num = csd_num;
                    record_num ++;
                }
            }
            else  //方法9
            {
                chk_num = csd_num ;

                record_num = 1;
            }

            while (chk_num--)
            {
                startlen = *pLen;
                tempu8 = (csd_num - chk_num - 1) * 5;
                if (*(pSelectlistBuf + tempu8) == 0) //OAD
                {
                    Std_MemRvs((u8 *)&temp_oad, pSelectlistBuf + tempu8 + 1, 4);
                }
                Std_Memcpy((u8 *)&stdnum, EvtStdlist[item].Addr, 1);   //标准事件记录单元OAD个数
                for (j = 0; j < oadnum; j++)
                {
                    if (j < stdnum) //--标准事件单元----
                    {
                        OffAddr = 3 + j * sizeof(sContextList_TypeDef);
                        Std_Memcpy((u8 *)&tmplist, EvtStdlist[item].Addr + OffAddr, sizeof(sContextList_TypeDef));
                    }
                    else
                    {
                        OffAddr = 3 + (j - stdnum) * sizeof(sContextList_TypeDef);
                        Std_Memcpy((u8 *)&tmplist, pCtxlistBuf + OffAddr, sizeof(sContextList_TypeDef));
                    }

                    if (tmplist.OAD == temp_oad)  //找到对应列
                    {
                        OIA_B = (tmplist.OAD >> 16 & 0xFFFF);

                        Std_Memcpy(uBuf, pRecordBuf + tmplist.OffPos, tmplist.len);

                        // 管理模组升级事件
                        if ((item == FileItemInfoNum_Evt_MngUpdate)
                            && ((tmplist.OAD == 0x00102200) || (tmplist.OAD == 0x00202200)))
                        {
                            sEvtRcdHead_TypeDef EvtHeadTmp;
                            fnFile_Read(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, &EvtHeadTmp, sizeof(sEvtRcdHead_TypeDef));

                            if (fnGet_EvtRecordUnit_DataType(tmplist.OAD, &type[0], item, uBuf) == ERROR)
                            {
                                fnGet_MngOADDataType(tmplist.OAD, &type[0], EvtHeadTmp.nTarf);
                            }
                        }
                        else
                        {
                            if (fnGet_EvtRecordUnit_DataType(tmplist.OAD, &type[0], item, uBuf) == ERROR)
                            {
                                fnGet_OADDataType(tmplist.OAD, &type[0]);
                            }
                        }

                        if (tmplist.OAD == 0x33020206) //编程事件记录
                        {
                            temp16 = (u16)(5 * type[1]); //长度

                            Std_Memcpy(uBuf, pRecordBuf + tmplist.OffPos + 1, temp16);

                            pDataBuf += fnDl698_asn1_build_Type(pDataBuf, pLen, &type[1], NULL, DTYPE_ARRAY);

                            for (k = 0; k < type[1]; k++)
                            {
                                pDataBuf += fnDl698_asn1_build_Type(pDataBuf, pLen, uBuf + 5 * k + 1, NULL, *(uBuf + 5 * k));
                            }

                            //pDataBuf += fnForm_build_Type(pDataBuf, pLen, uBuf, &temp16, &type[0]);
                        }
                        else if ((tmplist.OAD & 0xFFFF0FFF) == 0xF2050201)
                        {
                            temp16 = 5;  //VisibleString  len = 5

                            pDataBuf += fnForm_build_Type(pDataBuf, pLen, uBuf, &temp16, &type[0]);
                        }
                        else
                        {
                            temp16 = (u16)tmplist.len;
                            pDataBuf += fnForm_build_Type(pDataBuf, pLen, uBuf, &temp16, &type[0]);
                        }

                        break;
                    }
                }
                //找不到对应列内容应答NULL
                if (j == oadnum)
                {
                    pDataBuf += fnDl698_asn1_build_Type(pDataBuf, pLen, NULL, NULL, DTYPE_NONE);
                }

                maxlen = (*pLen - startlen) * (record_num + 1);  //提前累计多一条事件记录长度，大于2000，跳出
                if (maxlen > tempsize.apdu_size)
                {
                    break;
                }
            }
        }
    }

    *pRetBuf++ = 0x01;
    *pRetBuf++ = record_num; //n条事件记录
    *pLen += 2;

    //???
    //  if(item < FileItemInfoNum_Evt_QtOverNeed)
    //      tempu8 = pOadAys->AtrIndex - 7;  //分相事件
    //
    //  else if(item < FileItemInfoNum_Evt_PtOverNeed)
    //      tempu8 = pOadAys->AtrIndex - 6;
    //  else
    tempu8 = 0;

    fnClr_EvtReportData(item, tempu8, Secret.Chan);

    return res;
}

//--------TI--单位-----------------
const sEnumeRated_TypeDef ENUMERATED[] =
{
    { FileItemInfoNum_Frz_MinFrz, 1 },
};
/*********************************************************************
* @fn      fnGet_FrzRecord
*
* @brief
*
* @param
*
* @return
*/
#if(0)
u8 fnGet_FrzRecord(
    u32     OAD,            //读取事件记录OAD,元素索引表示读取第几次
    u8  *pParBuf,       //通讯下发的需要读取的RCSD信息
    u8  *uBuf,      //动态缓存通讯buf,在fnDl698_GetRecordValue统一申请,2K
    u8      *pRetBuf,       //获取到需应答数据，按698格式封装好
    u16     *pLen,      //数据长度
    u8      *blockRsp,
    u8   CheckSec
)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    sFrzCtxList_TypeDef tmplist;
    u8 *pRecordBuf, *pCtxlistBuf, *pDataBuf,  *pSelectlistBuf;

    u16 OIA_B = (OAD >> 16 & 0xFFFF), len,  intervals = 0, temp16;
    u16 startlen,  maxlen, readitem, startitem, enditem;
    u8 res = DATA_ACCESS_RESULT_SUC;

    u32 temp_oad, OffAddr,  maxcnt, tempcount;

    u8  type[20], item = 0,  selector ;
    u8  oadnum, rcsd_num, csd_num, chk_num, record_num = 0, stdnum;
    u8  tempu8, temp1, temp2;
    u8  j ;
    sFrzRcdHead_TypeDef  headData;

    sDate_time_s_TypeDef time1, time2;
    sCommSize_TypeDef  tempsize;

    //uBuf申请了3K空间:
    //1、uBuf[0]~uBuf[511]  数据交换临时缓存
    //2、uBuf[512]~uBuf[1023]   从E2获取到的关联对象属性表
    //3、uBuf[1024]~uBuf[1535]  标准事件记录单元缓存
    //4、uBuf[1036]~uBuf[3072] 从E2获取到的单条事件记录缓存
    pCtxlistBuf =  uBuf + 512;
    pSelectlistBuf = uBuf + 1024;
    pRecordBuf = uBuf + 1536;

    item = fnGet_FrzItem(OIA_B);

    selector = *pParBuf++;

    if (selector == 1) //方法1
    {
        Std_MemRvs((u8 *)&temp_oad, pParBuf, 4);
        tempu8 = 4;
        tempu8 += fnDl698AL_GetData_Len(1, 0, pParBuf + 4);
        Std_Memcpy(uBuf, pParBuf + 4, tempu8 - 4);  //除去OAD
        pParBuf += tempu8;

        if (Frz_StdRecList.Clist[1].OAD == temp_oad) //只支持按照冻结时间选择
        {
            if (*uBuf++ != DTYPE_DATETIME_S)
            {
                selector = 0xFF;
            }
            else
            {
                Std_MemRvs((u8 *)&time1, uBuf, 7);
            }
        }
        else
        {
            selector = 0xFF;
        }
    }
    else if (selector == 2) //方法2
    {
        Std_MemRvs((u8 *)&temp_oad, pParBuf, 4);
        tempu8 = 4;
        tempu8 += fnDl698AL_GetData_Len(1, 0, pParBuf + tempu8);    //起始时间

        tempu8 += fnDl698AL_GetData_Len(1, 0, pParBuf + tempu8);    //结束时间

        tempu8 += fnDl698AL_GetData_Len(1, 0, pParBuf + tempu8);    //间隔

        Std_Memcpy(uBuf, pParBuf + 4, tempu8 - 4);   //除去OAD

        pParBuf += tempu8;

        if (Frz_StdRecList.Clist[1].OAD == temp_oad) //只支持按照冻结时间选择
        {
            if (*uBuf++ != DTYPE_DATETIME_S)
            {
                selector = 0xFF;
            }
            else
            {
                Std_MemRvs((u8 *)&time1, uBuf, 7);
                uBuf += 7;

                if (*uBuf++ != DTYPE_DATETIME_S)
                {
                    selector = 0xFF;
                }
                else
                {
                    Std_MemRvs((u8 *)&time2, uBuf, 7);
                    uBuf += 7;
                    if (*uBuf++ == DTYPE_TI)
                    {
                        if ((*uBuf++ != ENUMERATED[item].Enume) && (ENUMERATED[item] .Enume != 0xFF))
                        {
                            selector = 0xFF;
                        }
                        else
                        {
                            intervals = Std_Msb16DataGet(uBuf);
                            uBuf += 2;
                        }
                    }
                    else if (*uBuf++ == DTYPE_NONE)
                    {
                        intervals = 0;
                    }
                    else
                    {
                        selector = 0xFF;
                    }
                }
            }
        }
        else
        {
            selector = 0xFF;
        }
    }
    else if (selector == 9) //方法9
    {
        rcsd_num = *pParBuf++;

        if (rcsd_num == 0)
        {
            selector = 0xFF;
        }
    }
    else
    {
        selector = 0xFF;
    }

    //--------------------------------------------
    csd_num = *pParBuf++;

    if (csd_num == 0)
    {
        //若列号为0时，获取总列数
        csd_num = fnGet_CsdNum(OAD, pParBuf, uBuf);
    }
    else
    {
        Std_Memcpy(uBuf, pParBuf, csd_num * 5);
    }

    if (*blockRsp == false) //封装关联对象属性表
    {
        *pRetBuf++ = csd_num;
        *pLen += 1;

        len = csd_num * 5;
        Std_Memcpy(pRetBuf, uBuf, len);
        Std_Memcpy(pSelectlistBuf, uBuf, len);
        pRetBuf += len;
        *pLen += len;
    }

    if (pOadAys->AtrIndex != 2)
    {
        res = DATA_ACCESS_RESULT_DENY;    //
    }

    if (selector == 0xFF)
    {
        res = DATA_ACCESS_RESULT_DENY;
    }
    else if (item >= FileItemInfoNum_Frz_MAX)
    {
        res = DATA_ACCESS_RESULT_UNDEF;
    }
    else  if (selector == 2) //方法2
    {
        if (fnDFCompData((u8 *)&time2, (u8 *)&time1, sizeof(sDate_time_s_TypeDef)) != 1) //结束时间小于等于起始时间时，返回越界
        {
            res = DATA_ACCESS_RESULT_ACC;
        }
    }

    if (fnDl698AL_Get_OIOpSec(OIA_B, DL698AL_APDU_TAG_GETREQ, gDl698AL_Server.pAlChan[Secret.Chan].sec_data.SecType) == false)
    {
        res = DATA_ACCESS_RESULT_SECNMATH;
    }
    //---------异常应答---------------
    if (res != DATA_ACCESS_RESULT_SUC)
    {
        *pRetBuf++ = 0x00;
        *pRetBuf++ = res;
        *pLen += 2;

        return DATA_ACCESS_RESULT_SUC;  //需应答关联对象属性表,按成功应答打包数据
    }

    //------正常应答--应答0~n条记录--------------

    pDataBuf = pRetBuf + 2; //预留两字节封装CHIOCE部分

    //---------标准事件记录单元OAD个数------------------
    oadnum = Frz_StdRecList.num;    //标准事件记录单元OAD个数
    //------读取关联对象属性表--------
    fnFile_Read(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[item].OffAddr, pCtxlistBuf, FileItemInfo_FrzCtxlist[item].Len);

    oadnum += *pCtxlistBuf;
    Std_Memcpy((u8 *)&len, pCtxlistBuf + 1, 2);

    //---------读取当前记录次数---------------
    fnFile_Read(FileId_FrzRcdHead, FileItemInfo_FrzRcdHead[item].OffAddr, (u8 *)&headData, sizeof(sFrzRcdHead_TypeDef));

    Std_Memcpy((u8 *)&tmplist, pCtxlistBuf + 3, sizeof(sFrzCtxList_TypeDef));
    maxcnt = tmplist.Depth;  //获取最大记录数

    if (headData.FrzAddrEnd != 0)
    {
        if (selector == 1)
        {
            startitem = fnFind_FrzSpecPos(item, GETPOS_START, &time1, &tmplist);
            if ((startitem == 0) || (startitem == 0xFFFF))
            {
                startitem = 0;
                enditem = 0;
            }
            else
            {
                enditem = startitem - 1;
            }
        }
        else if (selector == 2)   //
        {
            if (((item == FileItemInfoNum_Frz_HourFrz) && (time1.second  != 0x00) && (time1.minute != 0x00)) ||
                ((item == FileItemInfoNum_Frz_HourFrz) && (time1.second  != 0x00) && (time1.minute != 0x00) && (time1.hour != 0x00)))
            {
                startitem = 0;
                enditem = 0;
            }
            else
            {
                //--------查找指定的起始时间对应的冻结偏移指针(第几次)----------------
                startitem = fnFind_FrzSpecPos(item, GETPOS_START, &time1, &tmplist);
                if ((startitem == 0) || (startitem == 0xFFFF))
                {
                    startitem = 0;
                    enditem = 0;
                }
                else
                {
                    enditem = fnFind_FrzSpecPos(item, GETPOS_END, &time2, &tmplist);
                    if (enditem == 0xFFFF)
                    {
                        startitem = 0;
                        enditem = 0;
                    }
                }
            }
        }
        else        //方法9搜索1条
        {
            tempcount = headData.FrzAddrEnd - headData.FrzAddrStart;

            if ((rcsd_num > tempcount) || (rcsd_num > maxcnt))
            {
                startitem = 0 ;
                enditem = 0 ;
            }
            else
            {
                startitem = rcsd_num;
                enditem = startitem - 1;
            }
        }

        fnReadConnSize(&tempsize, Secret.Chan, Secret.CA);    //读取APDU长度
        //------------------------------------------
        for (readitem = startitem; readitem > enditem; readitem--)
        {
            chk_num = csd_num ;
            //---------读取一条事件记录，再根据读取列筛选内容---------------------
            tempcount = headData.FrzAddrEnd % maxcnt;
            tempcount = (maxcnt + tempcount - readitem) % maxcnt;

            OffAddr = FileItemInfo_FrzRecord[item].OffAddr + (u32)tempcount * (u32)len;

            fnFile_Read(FileId_FrzRecord,  OffAddr, pRecordBuf, len);

            if ((selector == 2) && (intervals))      //判断间隔时间
            {
                Std_Memcpy((u8 *)&time1, pRecordBuf + Frz_StdRecList.Clist[1].OffPos, sizeof(sDate_time_s_TypeDef));

                if (time1.minute == 0)
                {
                    time1.minute = 60;
                }

                if (time1.minute % intervals) //该记录点不在查找间隔范围内
                {
                    chk_num = 0;
                }
            }

            startlen = *pLen;

            if (chk_num)
            {
                while (chk_num--)
                {
                    tempu8 = (csd_num - chk_num - 1) * 5;
                    if (*(pSelectlistBuf + tempu8) == 0) //OAD
                    {
                        Std_MemRvs((u8 *)&temp_oad, pSelectlistBuf + tempu8 + 1, 4);
                    }

                    stdnum = Frz_StdRecList.num; //标准事件记录单元OAD个数

                    for (j = 0; j < oadnum; j++)
                    {
                        if (j < stdnum) //--标准事件单元----
                        {
                            Std_Memcpy((u8 *)&tmplist, (u8 *)&Frz_StdRecList.Clist[j], sizeof(sFrzCtxList_TypeDef));
                        }
                        else
                        {
                            OffAddr = 3 + (j - stdnum) * sizeof(sFrzCtxList_TypeDef);
                            Std_Memcpy((u8 *)&tmplist, pCtxlistBuf + OffAddr, sizeof(sFrzCtxList_TypeDef));
                        }

                        if (tmplist.OAD == temp_oad)    //找到对应列
                        {
                            if (fnGet_FrzRecordUnit_DataType(tmplist.OAD, &type[0]) == ERROR)
                            {
                                fnGet_OADDataType(tmplist.OAD, &type[0]);
                            }

                            Std_Memcpy(uBuf, pRecordBuf + tmplist.OffPos, tmplist.len);

                            if (item == FileItemInfoNum_Frz_RmDayFrz)
                            {
                                //---抄读结算冻结，读取的需量数据为全FF时，应答为NULL------
                                //---第2, 3结算日时存储需量数据为全FF，应答时为NULL-----
                                temp1 = (u8)(temp_oad >> 24);
                                if (temp1 == 0x10) //需量
                                {
                                    if (fnJudge_Value(pRecordBuf + tmplist.OffPos, 0xFF, tmplist.len) == true)
                                    {
                                        type[0] = DTYPE_NONE;
                                        tmplist.len = 0;
                                    }
                                }
                            }
                            temp16 = (u16)tmplist.len;
                            pDataBuf += fnForm_build_Type(pDataBuf, pLen, uBuf, &temp16, &type[0]);

                            break;
                        }
                        else if (tmplist.OAD == (temp_oad & 0xFFFFFF00))  //关联对象属性表元素为00，允许单独读取某一个元素
                        {
                            fnGet_OADDataType(tmplist.OAD, &type[0]);

                            temp1 = (u8)temp_oad;
                            temp2 = 0;
                            if (temp1)   //关联对象属性表元素为0，读取列元素不为0时，需正常应答
                            {
                                if ((type[0] == DTYPE_ARRAY) || (type[0] == DTYPE_STRUCTURE))
                                {
                                    tmplist.len = tmplist.len / type[1];
                                    temp2 = (temp1 - 1) * tmplist.len;
                                    fnGet_OADDataType(temp_oad, &type[0]);
                                }
                            }

                            Std_Memcpy(uBuf, pRecordBuf + tmplist.OffPos + temp2, tmplist.len);

                            if (item == FileItemInfoNum_Frz_RmDayFrz)
                            {
                                //---抄读结算冻结，读取的需量数据为全FF时，应答为NULL------
                                //---第2, 3结算日时存储需量数据为全FF，应答时为NULL-----
                                temp1 = (u8)(temp_oad >> 24);
                                if (temp1 == 0x10) //需量
                                {
                                    if (fnJudge_Value(pRecordBuf + tmplist.OffPos, 0xFF, tmplist.len) == true)
                                    {
                                        type[0] = DTYPE_NONE;
                                        tmplist.len = 0;
                                    }
                                }
                            }
                            temp16 = (u16)tmplist.len;
                            pDataBuf += fnForm_build_Type(pDataBuf, pLen, uBuf, &temp16, &type[0]);

                            break;
                        }
                    }

                    //找不到对应列内容应答NULL
                    if (j == oadnum)
                    {
                        pDataBuf += fnDl698_asn1_build_Type(pDataBuf, pLen, NULL, NULL, DTYPE_NONE);
                    }
                }

                record_num++;

                maxlen = (*pLen - startlen) * (record_num + 1);  //提前累计多一条事件记录长度，大于2000，跳出
                if (maxlen > tempsize.apdu_size)
                {
                    break;
                }
            }
        }
    }

    *pRetBuf++ = 0x01;
    *pRetBuf++ = record_num; //n条事件记录
    *pLen += 2;

    return res;
}
#endif
/*********************************************************************
* @fn      fnGet_FrzMinRecord
*
* @brief
*
* @param
*
* @return
*/
u8 fnGet_FrzMinRecord(
    u32     OAD,            //读取事件记录OAD,元素索引表示读取第几次
    u8  *pParBuf,       //通讯下发的需要读取的RCSD信息
    u8  *uBuf,      //动态缓存通讯buf,在fnDl698_GetRecordValue统一申请,2K
    u8      *pRetBuf,       //获取到需应答数据，按698格式封装好
    u16     *pLen,      //数据长度
    u8      *blockRsp
)
{
    //      OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    sFrzCtxList_TypeDef tmplist;
    u8 *pRecordBuf, *pCtxlistBuf, *pDataBuf, *pSelectlistBuf;

    u16  len, intervals, temp16;
    u16 startlen,  maxlen;
    u8 res = DATA_ACCESS_RESULT_SUC;

    u32 temp_oad, OffAddr, maxcnt, tempcount, startitem, enditem, readitem ;

    u8  type[20],  selector ;
    u8  oadnum, rcsd_num, csd_num, chk_num, record_num = 0, stdnum;
    u8  tempu8, temp1, temp2;
    u8  i, j,   line ;
    sDate_time_s_TypeDef time1, time2;
    sFrzMinHead_TypeDef  tempFrzMin;
    sCommSize_TypeDef  tempsize;
    s8 temps8;
    u32 tempu32_1 = 0, tempu32_2 = 0; // dyf add

    //uBuf申请了2K空间:
    //1、uBuf[0]~uBuf[511]  数据交换临时缓存
    //2、uBuf[512]~uBuf[911]   从E2获取到的关联对象属性表
    //3、uBuf[912]~uBuf[1023]  标准事件记录单元缓存
    //4、uBuf[1024]~uBuf[2048] 从E2获取到的单条事件记录缓存
    pCtxlistBuf =  uBuf + 512;

    pSelectlistBuf = uBuf + 1024;
    pRecordBuf = uBuf + 1536;

    selector = *pParBuf++;

    if (selector == 1) //方法1
    {
        Std_MemRvs((u8 *)&temp_oad, pParBuf, 4);
        tempu8 = 4;
        tempu8 += fnDl698AL_GetData_Len(1, 0, pParBuf + 4);
        Std_Memcpy(uBuf, pParBuf + 4, tempu8 - 4);  //除去OAD
        pParBuf += tempu8;

        if (Frz_StdRecList.Clist[1].OAD == temp_oad) //只支持按照冻结时间选择
        {
            if (*uBuf++ != DTYPE_DATETIME_S)
            {
                selector = 0xFF;
            }
            else
            {
                Std_MemRvs((u8 *)&time1, uBuf, 7);
                if (fnCheck_Date_time_s(&time1) == ERROR)
                {
                    selector = 0xFF;
                }
            }
        }
        else
        {
            selector = 0xFF;
        }
    }
    else if (selector == 2) //方法2
    {
        Std_MemRvs((u8 *)&temp_oad, pParBuf, 4);
        tempu8 = 4;
        tempu8 += fnDl698AL_GetData_Len(1, 0, pParBuf + tempu8);    //起始时间

        tempu8 += fnDl698AL_GetData_Len(1, 0, pParBuf + tempu8);    //结束时间

        tempu8 += fnDl698AL_GetData_Len(1, 0, pParBuf + tempu8);    //间隔

        Std_Memcpy(uBuf, pParBuf + 4, tempu8 - 4);  //除去OAD

        pParBuf += tempu8;

        if (Frz_StdRecList.Clist[1].OAD == temp_oad) //只支持按照冻结时间选择
        {
            if (*uBuf++ != DTYPE_DATETIME_S)
            {
                selector = 0xFF;
            }
            else
            {
                Std_MemRvs((u8 *)&time1, uBuf, 7);
                uBuf += 7;
                if (*uBuf++ != DTYPE_DATETIME_S)
                {
                    selector = 0xFF;
                }
                else
                {
                    Std_MemRvs((u8 *)&time2, uBuf, 7);
                    uBuf += 7;

                    if (*uBuf == DTYPE_TI)
                    {
                        uBuf++;

                        if (*uBuf++ != ENUMERATED[FileItemInfoNum_Frz_MinFrz].Enume)
                        {
                            selector = 0xFF;
                        }
                        else
                        {
                            intervals = Std_Msb16DataGet(uBuf);
                        }
                    }
                    else if (*uBuf == DTYPE_NONE)
                    {
                        uBuf ++;
                        intervals = 0;
                    }
                    else
                    {
                        selector = 0xFF;
                    }
                }

                if (fnCheck_Date_time_s(&time1) == ERROR)
                {
                    selector = 0xFF;
                }

                if (fnCheck_Date_time_s(&time2) == ERROR)
                {
                    selector = 0xFF;
                }
            }
        }
        else
        {
            selector = 0xFF;
        }
    }
    else if (selector == 9) //方法9
    {
        rcsd_num = *pParBuf++;

        if (rcsd_num == 0)
        {
            selector = 0xFF;
        }
    }
    else
    {
        selector = 0xFF;
    }

    if (OAD != 0x50020200)
    {
        selector = 0xFF;
    }

    //--------------------------------------------
    csd_num = *pParBuf++;

    if (csd_num == 0)  //分钟冻结必须指定列
    {
        //若列号为0时，获取总列数
        selector = 0xFF;
        csd_num = fnGet_CsdNum(OAD, pParBuf, uBuf);
    }
    else
    {
        Std_Memcpy(uBuf, pParBuf, csd_num * 5);
    }

    if (*blockRsp == false) //封装关联对象属性表
    {
        *pRetBuf++ = csd_num;
        *pLen += 1;

        len = csd_num * 5;
        Std_Memcpy(pRetBuf, uBuf, len);
        Std_Memcpy(pSelectlistBuf, uBuf, len);
        pRetBuf += len;
        *pLen += len;
    }

    line =  0xFF;
    //-------判断读取列的属性特征(冻结方案)是否一致------------
    for (i = 0; i < csd_num; i++)
    {
        temp_oad = Std_Msb32DataGet(pSelectlistBuf + 5 * i + 1);
        //非冻结时间及冻结序号时判断方案号是否一致
        if ((temp_oad != Frz_StdRecList.Clist[0].OAD) && (temp_oad != Frz_StdRecList.Clist[1].OAD))
        {
            tempu8 = (u8)(temp_oad >> 13) & 0x07;

            if (line == 0xFF) //
            {
                line = tempu8;
            }

            if (line != tempu8)
            {
                res = DATA_ACCESS_RESULT_DENY;
            }
        }
    }
    if (line == 0xFF)  //找不到索引列
    {
        selector = 0xFF;
    }

    if (selector == 0xFF)
    {
        res = DATA_ACCESS_RESULT_DENY;
    }
    else  if (selector == 2) //方法2
    {
        if (fnDFCompData((u8 *)&time2, (u8 *)&time1, sizeof(sDate_time_s_TypeDef)) != 1) //结束时间小于等于起始时间时，返回越界
        {
            res = DATA_ACCESS_RESULT_ACC;
        }
    }

    if (fnDl698AL_Get_OIOpSec(0x5002, DL698AL_APDU_TAG_GETREQ, gDl698AL_Server.pAlChan[Secret.Chan].sec_data.SecType) == false)
    {
        res = DATA_ACCESS_RESULT_SECNMATH;
    }

    //---------异常应答---------------
    if (res != DATA_ACCESS_RESULT_SUC)
    {
        *pRetBuf++ = 0x00;
        *pRetBuf++ = res;
        *pLen += 2;

        return DATA_ACCESS_RESULT_SUC;  //需应答关联对象属性表,按成功应答打包数据
    }

    //------正常应答--应答0~n条记录--------------
    pDataBuf = pRetBuf + 2; //预留两字节封装CHIOCE部分

    //---------标准事件记录单元OAD个数------------------
    oadnum = Frz_StdRecList.num;    //标准事件记录单元OAD个数
    //------读取关联对象属性表--------
    OffAddr = FileItemInfo_FrzCtxlist[FileItemInfoNum_Frz_MinFrz].OffAddr;
    fnFile_Read(FileId_FrzCtxlist, OffAddr, pCtxlistBuf, FileItemInfo_FrzCtxlist[FileItemInfoNum_Frz_MinFrz].Len);

    oadnum += *pCtxlistBuf;
    //Std_Memcpy((u8 *)&len, pCtxlistBuf + 1, 2);

    //---------读取当前记录次数---------------
    OffAddr = FileItemInfo_FrzMinLineHead[line].OffAddr;
    fnFile_Read(FileId_FrzMinLineHead, OffAddr, (u8 *)&tempFrzMin, FileItemInfo_FrzMinLineHead[line].Len);

    maxcnt = tempFrzMin.LinePara.Depth;  //获取最大记录数

    if (tempFrzMin.RecHead.FrzAddrEnd != 0)
    {
        if (selector == 1)
        {
            startitem = fnFind_FrzMinSpecPos(line, GETPOS_START, &time1, &tempFrzMin);
            if ((startitem == 0) || (startitem == 0xFFFFFFFF))
            {
                startitem = 0;
                enditem = 0;
            }
            else
            {
                enditem = startitem - 1;
            }
        }
        else if (selector == 2)   //
        {
            /*
            if(time1.second  != 0x00)
            {
              startitem = 0;
              enditem = 0;
            }
            else*/
            {
                startitem = fnFind_FrzMinSpecPos(line, GETPOS_START, &time1, &tempFrzMin);
                if ((startitem == 0) || (startitem == 0xFFFFFFFF))
                {
                    startitem = 0;
                    enditem = 0;
                }
                else
                {
                    enditem = fnFind_FrzMinSpecPos(line, GETPOS_END, &time2, &tempFrzMin);
                    if (enditem == 0xFFFFFFFF)
                    {
                        startitem = 0;
                        enditem = 0;
                    }
                }
            }
        }
        else        //方法9搜索1条
        {
            tempcount = tempFrzMin.RecHead.FrzAddrEnd - tempFrzMin.RecHead.FrzAddrStart;

            if ((rcsd_num > tempcount) || (rcsd_num > maxcnt))
            {
                startitem = 0 ;
                enditem = 0 ;
            }
            else
            {
                startitem = rcsd_num ;
                enditem = startitem - 1;
            }
        }

        fnReadConnSize(&tempsize, Secret.Chan, Secret.CA);    //读取APDU长度

        if (selector == 2)  // dyf add 将起始时间2000年开始的分钟数
        {
            tempu32_1 = fnDateTimeToMin(&time1);
        }

        //------------------------------------------
        for (readitem = startitem; readitem > enditem; readitem--)
        {
            chk_num = csd_num ;
            //---------读取一条事件记录，再根据读取列筛选内容---------------------

            tempcount = tempFrzMin.RecHead.FrzAddrEnd % maxcnt;
            tempcount = (maxcnt + tempcount - readitem) % maxcnt;

            OffAddr = FileItemInfo_FrzRecord[FileItemInfoNum_Frz_MinFrz].OffAddr ;
            OffAddr += (u32)tempFrzMin.LinePara.LineOffAdder + (u32)tempcount * (u32)tempFrzMin.LinePara.RecLen;

            fnFile_Read(FileId_FrzRecord,  OffAddr, pRecordBuf, tempFrzMin.LinePara.RecLen);

            if ((selector == 2) && (intervals))      //判断间隔时间
            {
                Std_Memcpy((u8 *)&time2, pRecordBuf + Frz_StdRecList.Clist[1].OffPos, sizeof(sDate_time_s_TypeDef));

                temps8 = fnDFCompData((u8 *)&time2.minute, (u8 *)&time1.minute, 5);

                if (temps8 >= 0)
                {
                    /* dyf 计算当前冻结时间与起始提取冻结的分钟时间差，判断是否是间隔时间的整数倍 */
                    tempu32_2 = fnDateTimeToMin(&time2);
                    tempu32_2 -= tempu32_1;

                    if (tempu32_2 % intervals)  //该记录点不在查找间隔范围内 dyf 能被整除则提取该条记录数据
                    {
                        chk_num = 0;
                    }

                    #if 0   /* dyf 旧代码，只判断分钟的时间差 */

                    if ((temps8 == 1) && (time2.minute == 0))
                    {
                        time2.minute = 60;
                    }

                    if (time2.minute >= time1.minute)
                    {
                        tempu8 = time2.minute - time1.minute;
                    }
                    else
                    {
                        tempu8 = time2.minute + 60 - time1.minute;
                    }

                    if (tempu8 % intervals) //该记录点不在查找间隔范围内
                    {
                        chk_num = 0;
                    }

                    #endif
                }
                else
                {
                    chk_num = 0;
                }
            }

            startlen = *pLen;

            if (chk_num)
            {
                while (chk_num--)
                {
                    tempu8 = (csd_num - chk_num - 1) * 5;
                    if (*(pSelectlistBuf + tempu8) == 0) //OAD
                    {
                        Std_MemRvs((u8 *)&temp_oad, pSelectlistBuf + tempu8 + 1, 4);
                    }

                    stdnum = Frz_StdRecList.num; //标准事件记录单元OAD个数
                    for (j = 0; j < oadnum; j++)
                    {
                        if (j < stdnum) //--标准事件单元----
                        {
                            Std_Memcpy((u8 *)&tmplist, (u8 *)&Frz_StdRecList.Clist[j], sizeof(sFrzCtxList_TypeDef));
                        }
                        else
                        {
                            OffAddr = 3 + (j - stdnum) * sizeof(sFrzCtxList_TypeDef);
                            Std_Memcpy((u8 *)&tmplist, pCtxlistBuf + OffAddr, sizeof(sFrzCtxList_TypeDef));
                        }

                        if (tmplist.OAD == temp_oad)    //找到对应列
                        {
                            if (fnGet_FrzRecordUnit_DataType(tmplist.OAD, &type[0]) == ERROR)
                            {
                                fnGet_OADDataType(tmplist.OAD, &type[0]);
                            }

                            temp16 = (u16)tmplist.len;
                            Std_Memcpy(uBuf, pRecordBuf + tmplist.OffPos, temp16);
                            pDataBuf += fnForm_build_Type(pDataBuf, pLen, uBuf, &temp16, &type[0]);

                            break;
                        }
                        else if (tmplist.OAD == (temp_oad & 0xFFFFFF00))  //关联对象属性表元素为00，允许单独读取某一个元素
                        {
                            fnGet_OADDataType(tmplist.OAD, &type[0]);

                            temp1 = (u8)temp_oad;
                            temp2 = 0;
                            if (temp1)   //关联对象属性表元素为0，读取列元素不为0时，需正常应答
                            {
                                if ((type[0] == DTYPE_ARRAY) || (type[0] == DTYPE_STRUCTURE))
                                {
                                    tmplist.len = tmplist.len / type[1];
                                    temp2 = (temp1 - 1) * tmplist.len;
                                    fnGet_OADDataType(temp_oad, &type[0]);
                                }
                            }
                            //datalen = fnFill_OADData(temp_oad, uBuf, pRecordBuf + tmplist.OffPos + temp2, tmplist.len);
                            temp16 = (u16)tmplist.len;
                            Std_Memcpy(uBuf, pRecordBuf + tmplist.OffPos + temp2, temp16);
                            pDataBuf += fnForm_build_Type(pDataBuf, pLen, uBuf, &temp16, &type[0]);

                            break;
                        }
                        else if ((tmplist.OAD < 0x10000000) && ((tmplist.OAD & 0xFFFFF0FF) == (temp_oad & 0xFFFFF0FF))) //------电能OAD---------
                        {
                            tempu8 = (u8)(temp_oad >> 8) & 0x0F;
                            if ((tempu8 == 2) || (tempu8 == 4)) //---属性2、属性4----
                            {
                                temp16 = (u16)tmplist.len;
                                Std_Memcpy(uBuf + 16, pRecordBuf + tmplist.OffPos, temp16);

                                if (tempu8 == 2)
                                {
                                    fnEnergy_Change(uBuf + 16, uBuf, Energy_HEX2FractionE);
                                    temp16 = DTYPE_UINT32_Len;
                                    type[0] = DTYPE_UINT32;
                                }
                                else
                                {
                                    fnEnergy_Change(uBuf + 16, uBuf, Energy_HEX4FractionE);
                                    temp16 = DTYPE_UINT64_Len;
                                    type[0] = DTYPE_UINT64;
                                }

                                pDataBuf += fnForm_build_Type(pDataBuf, pLen, uBuf, &temp16, &type[0]);
                            }

                            break;
                        }
                    }

                    //找不到对应列内容应答NULL
                    if (j == oadnum)
                    {
                        pDataBuf += fnDl698_asn1_build_Type(pDataBuf, pLen, NULL, NULL, DTYPE_NONE);
                    }
                }

                record_num++;  //获取记录条数加1

                maxlen = (*pLen - startlen) * (record_num + 1) + 60;  //提前累计多一条事件记录长度，大于2000，跳出
                if (maxlen > tempsize.apdu_size)
                {
                    readitem = enditem;  //
                    break;
                }
            }
        }
    }

    *pRetBuf++ = 0x01;
    *pRetBuf++ = record_num; //n条事件记录
    *pLen += 2;

    return res;
}

/*********************************************************************************************************
** Function name:   fnSet_4000
** Descriptions:    设置OI=0x4000 时间日期
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_DateTime(u8 elementIndex, u8 AtrIndex, u8  *pSrc,  u8  *pParBuf)
{
    sDate_time_s_TypeDef timebuf;
    sDate_time_s_TypeDef timeold;
    ErrorStatus tmpStatus = SUCCESS;
    u8 offset;
    u16 temp;
    sBroatStatue_TypeDef  broadsta;
    s8 res;
    u32 temp1, temp2, FreezeMinAdd = 0, i;

    if (AtrIndex == 5)  //属性5，返回最小及最大校时偏差参数
    {
        if (elementIndex == 0)
        {
            if ((*pSrc++) != DTYPE_STRUCTURE)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if ((*pSrc++) != 2)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if ((*pSrc++) != DTYPE_UINT16)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            fnFile_Read(FileId_ParaDoc, FileItemInfoOffAddr_DocPara_NeedMode, pParBuf, FileLen_ParaDoc);
            Std_MemRvs(pParBuf + FileItemInfoOffAddr_DocPara_BroadcastMIN, pSrc, 2);
            pSrc += 2;

            if ((*pSrc++) != DTYPE_UINT16)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_MemRvs(pParBuf + FileItemInfoOffAddr_DocPara_BroadcastMAX, pSrc, 2);
            pSrc += 2;
        }
        else if (elementIndex < 3)
        {
            if ((*pSrc++) != DTYPE_UINT16)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            offset = (elementIndex - 1) * 2;
            fnFile_Read(FileId_ParaDoc, FileItemInfoOffAddr_DocPara_NeedMode, pParBuf, FileLen_ParaDoc);
            Std_MemRvs(pParBuf + FileItemInfoOffAddr_DocPara_BroadcastMIN + offset, pSrc, 2);
            pSrc += 2;
        }
        else
        {
            return DATA_ACCESS_RESULT_UNAVA;
        }

        fnCrc_Check(0, pParBuf, FileLen_ParaDoc - 2, (u8 *)&temp);
        Std_Memcpy(pParBuf + FileItemInfoOffAddr_DocPara_Crc, (u8 *)&temp, 2);
        fnFile_Write(FileId_ParaDoc, FileItemInfoOffAddr_DocPara_NeedMode, pParBuf, FileLen_ParaDoc);
    }
    else if (AtrIndex == 2)  //时间日期
    {
        if ((*pSrc++) != DTYPE_DATETIME_S)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        fnGetCurrTime(&timeold);
        fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_BroatStatue, (u8 *)&broadsta, sizeof(sBroatStatue_TypeDef));

        timebuf.year = Std_Msb16DataGet(pSrc);
        pSrc += 2;
        timebuf.month = (*pSrc++);
        timebuf.day = (*pSrc++);
        timebuf.hour = (*pSrc++);
        timebuf.minute = (*pSrc++);
        timebuf.second = (*pSrc++);

        tmpStatus = fnSetCurrTime(&timebuf);
        if (tmpStatus == ERROR)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        res = fnDFCompData((u8 *)&timeold.minute, (u8 *)&timebuf.minute, sizeof(sDate_time_s_TypeDef) -1);
        if (res == 1) //时间往回改重新计算周期冻结指针
        {
            fnFreezePoint_Calc(timeold, timebuf);
        }
        else if (res == -1) //-----时间往前改补下一分钟冻结----------
        {
            //-----补1min冻结------------
            fnMinAdd(&SysDatetimes, 1);
            SysDatetimes.second = 0x00;
            Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_MINFRZ;
            Bkgrd.PubData.FrzMin_LineItem |= 1 << 0;
            fnFreeze();

            //-----------
            temp1 = fnDateTimeToMin(&timebuf);
            temp2 = fnDateTimeToMin(&timeold);
            if (temp1 > temp2)
            {
                FreezeMinAdd = temp1 - temp2;

                fnWDT_Restart();
                SysDatetimes.second = 0x00;

                for (i = 0; i < FreezeMinAdd ; i++)
                {
                    if (((SysDatetimes.minute % RFrzMinLine.Cycle[1]) == 0) && (RFrzMinLine.Cycle[1]))
                    {
                        Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_MINFRZ;
                        Bkgrd.PubData.FrzMin_LineItem |= 1 << 1;

                        fnFreeze();
                        break;
                    }
                    else
                    {
                        fnWDT_Restart();
                        fnMinAdd(&SysDatetimes, 1);
                    }
                }
            }
        }

        fnSysDateTimes(&SysDatetimes);  //产生事件记录前需刷新时间

        //if( (broadsta.ClockErr)||(Bkgrd.PubData.MtSta.MtSta1.StaBit.ClockErr) ) //当前有错误事件产生时，产生结束事件
        //fnEvent_Operation(FileItemInfoNum_Evt_ClockErr , EVTEND , NULL);

        fnEvent_Operation(FileItemInfoNum_Evt_SetClock, EVTSTART, (u8 *)&timeold);

        //broadsta.ClockErr = 0;

        //fnFile_Write(FileId_HighState , FileItemInfoOffAddr_HighState_BroatStatue + 1 , (u8 *)&broadsta.ClockErr , 1);

        Bkgrd.PubData.UpFlStatusFlag = 0x5a;

        if (fnDFCompData((u8 *)&SysDatetimes.hour, (u8 *)&timeold.hour, 5))
        {
            Bkgrd.PubData.UpDateTimeFlag |= BKGRD_FCHANGE_HOUR;
        }

        if (fnDFCompData((u8 *)&SysDatetimes.day, (u8 *)&timeold.day, 4)) //天发生变化
        {
            Bkgrd.PubData.UpDateTimeFlag |= BKGRD_FCHANGE_DAY;
        }

        Bkgrd.PriData.Second = SysDatetimes.second;
        Bkgrd.PriData.Minute = SysDatetimes.minute;
        Bkgrd.PriData.Hour = SysDatetimes.hour;
        Bkgrd.PriData.Day = SysDatetimes.day;
        Bkgrd.PriData.Month = SysDatetimes.month;

        fnFile_Write(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_PowDnTime, &SysDatetimes, sizeof(sDate_time_s_TypeDef));

        fnWrite_PowDn_FrzRmDayTime();
        fnWrite_PowDn_FrzDayTime();

        Bkgrd.PubData.MtSysSta.SysStaBit.ClockErr = CLOCK_STA_OK;
    }
    else
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnSet_ComAddr_UserNo
** Descriptions:    设置OI=0x4001/ 0x4002  通讯地址，客户编号
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_ComAddr_UserNo(u8 elementIndex, u8 AtrIndex, u8 OIB2, u8  *pSrc, u8  *pParBuf)
{
    if ((AtrIndex != 2) || (elementIndex != 0))
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if ((*pSrc++) != DTYPE_OCT_STR)
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    if (*pSrc++ != 6)   //长度
    {
        return DATA_ACCESS_RESULT_DENY;
    }
    if (fnJudge_Value(pSrc, 0x99, 6)) //不可设置为全99
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    //----判断是否为BCD-----
    if (fnBCD_Check(pSrc, 6) == false)
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    pParBuf = pSrc;
    Std_MemRvsSelf(pParBuf, 6);
    pSrc += 6;

    if (OIB2 == 1)
    {
        Std_Memcpy(&CommPara.ComAddr[0], pParBuf, 6);
        fnCrc_Check(0, (u8 *)&CommPara, FileLen_ParaCom - 2, (u8 *)&CommPara.Crc);
        fnFile_Write(FileId_ParaCom, FileItemInfoOffAddr_ComPara_ComAddr, (u8 *)&CommPara, FileLen_ParaCom);
    }
    else
    {
        fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_UserNo, pParBuf, sizeof(sDF12));
    }
    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnSet_UserNo
** Descriptions:    设置OI=0x400  3通讯地址，客户编号
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_UserNo(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    u8 len;
    u8 buf[6];

    if ((AtrIndex != 2) || (elementIndex != 0))
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if ((*pSrc++) != DTYPE_OCT_STR)
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    len = *pSrc++;

    if (len == 0 || len > 6)  //长度
    {
        return DATA_ACCESS_RESULT_DENY;
    }
    if (fnJudge_Value(pSrc, 0x99, len)) //不可设置为全99
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    //----判断是否为BCD-----
    if (fnBCD_Check(pSrc, len) == false)
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    //----前面字节补零-----
    fnDl698_memset(buf, 0, FileItemInfoLen_HighPara_UserNo - len);
    //----复制待写入的编号-----
    fnDl698_memcpy(buf + FileItemInfoLen_HighPara_UserNo - len, pSrc, len);

    pParBuf = buf;
    Std_MemRvsSelf(pParBuf, FileItemInfoLen_HighPara_UserNo);

    fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_UserNo, pParBuf, FileItemInfoLen_HighPara_UserNo);

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnDl698_Set4004
** Descriptions:    设置OI=0x4004 设备位置信息
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_MeterPlace(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    u16 len = 0, SetOffAddr = 0 ;
    u8 i, j;
    u8 *Databuf;

    Databuf = pParBuf;

    if (AtrIndex != 2)
    {
        return DATA_ACCESS_RESULT_UNAVA;
    }

    if (elementIndex == 0)
    {
        if (((*pSrc++) != DTYPE_STRUCTURE) || ((*pSrc++) != 3))
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        for (j = 0; j < 2; j ++)
        {
            if (((*pSrc++) != DTYPE_STRUCTURE) || ((*pSrc++) != 4))
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if ((*pSrc++) != DTYPE_ENUM)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if (*pSrc > 1)
            {
                return DATA_ACCESS_RESULT_DENY;
            }

            Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);  //方位
            len += DTYPE_UINT8_Len;   //设置内容长度

            for (i = 0; i < 3; i ++)
            {
                if ((*pSrc++) != DTYPE_UINT8)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
                len += DTYPE_UINT8_Len;   //设置内容长度
            }
        }
        //---------高度-----
        if ((*pSrc++) != DTYPE_UINT32)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        Std_MemRvs(pParBuf, pSrc, DTYPE_UINT32_Len);

        len += DTYPE_UINT32_Len;
        SetOffAddr = 0;
    }
    else if ((elementIndex == 1) || (elementIndex == 2))   //经度
    {
        if (((*pSrc++) != DTYPE_STRUCTURE) || ((*pSrc++) != 4))
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_ENUM)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if (*pSrc > 1)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        Copy_TO_STREAM(pParBuf, pSrc, DTYPE_ENUM_Len);       //方位
        len += DTYPE_ENUM_Len;
        for (i = 0; i < 3; i ++)
        {
            if ((*pSrc++) != DTYPE_UINT8)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
            len += DTYPE_UINT8_Len;   //设置内容长度
        }
        i = elementIndex - 1;
        SetOffAddr = i * (DTYPE_ENUM_Len + DTYPE_UINT8_Len * 3);
    }
    else if (elementIndex == 3) //高度
    {
        if ((*pSrc++) != DTYPE_UINT32)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        Std_MemRvs(pParBuf, pSrc, DTYPE_UINT32_Len);
        len += DTYPE_UINT32_Len;

        SetOffAddr = 2 * (DTYPE_ENUM_Len + DTYPE_UINT8_Len * 3);
    }
    else
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_MeterPlace + SetOffAddr, Databuf, len);

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnSet_LCDPara
** Descriptions:    设置class=8,OI=0x4007 LCD显示参数
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_LCDPara(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    return 1;
}

/*********************************************************************************************************
** Function name:   fnDl698_Set4008_4009_400A_400B
** Descriptions:    设置OI=0x4008 时区表切换时间；OI=0x4009 时段表切换时间；
**              OI=0x400A 费率表切换时间；OI=0x400B 阶梯表切换时间；
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_SwitchTime(u8 elementIndex, u8 AtrIndex, u8 OIB2, u8  *pSrc, u8  *pParBuf)
{
    sDate_time_s_TypeDef    tmpClock;
    u8 len;

    if ((AtrIndex != 2) || (elementIndex != 0))
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if ((*pSrc++) != DTYPE_DATETIME_S)
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    len = sizeof(sDate_time_s_TypeDef);
    Std_MemRvs((u8 *)&tmpClock, pSrc, len);
    pSrc += len;

    if (tmpClock.second == 0xFF) //避免合法性判断不合格
    {
        tmpClock.second = 0;
    }

    //----之前设置全0或者00 00 00 00 00 00 FF------------------------
    if ((fnCheck_Date_time_s(&tmpClock) == SUCCESS) ||
        ((fnJudge_Value((u8 *)&tmpClock.minute, 0x00, 6) == TRUE) && ((tmpClock.second == 0x00) || (tmpClock.second == 0xFF))))
    {
        tmpClock.second = 0xFF; //切换时间秒无效，固定为FF
        if (OIB2 == 0x08)
        {
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_TimeZonePara, &tmpClock, len);
        }
        else if (OIB2 == 0x09)
        {
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_POTTablePara, &tmpClock, len);
        }
        else if (OIB2 == 0x0A)
        {
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara, &tmpClock, len);
        }
        else if (OIB2 == 0x0B)
        {
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara, &tmpClock, len);
        }
        else
        {
            return DATA_ACCESS_RESULT_UNDEF;
        }
    }
    else
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    Bkgrd.PubData.UpFlStatusFlag = 0x5a;
    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnDl698_Set400C
** Descriptions:    设置OI=0x4007 时区时段数
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_RatePara(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    u16 len = 0, SetOffAddr = 0;

    u8 *Databuf;

    Databuf = pParBuf;

    if (AtrIndex != 2)
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if (elementIndex == 0)
    {
        if (((*pSrc++) != DTYPE_STRUCTURE) || ((*pSrc++) != 5))
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        SetOffAddr = 0;

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        if (((*pSrc) == 0) || ((*pSrc) > MAX_TIMEZONE)) //年时区数
        {
            return DATA_ACCESS_RESULT_YOVER;
        }
        Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
        len += DTYPE_UINT8_Len;

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        if (((*pSrc) == 0) || ((*pSrc) > MAX_POTTABLE)) //日时段表数
        {
            return DATA_ACCESS_RESULT_OTH;
        }
        Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
        len += DTYPE_UINT8_Len;

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        if (((*pSrc) == 0) || ((*pSrc) > MAX_POT)) //日时段数
        {
            return DATA_ACCESS_RESULT_DOVER;
        }
        Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
        len += DTYPE_UINT8_Len;

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        if (((*pSrc) == 0) || ((*pSrc) > MAX_FL)) //费率数
        {
            return DATA_ACCESS_RESULT_ROVER;
        }
        Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
        len += DTYPE_UINT8_Len;

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        // if((*pSrc) > MAX_HOLIDAY)  //公共节假日数
        //  return DATA_ACCESS_RESULT_OTH;
        Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
        len += DTYPE_UINT8_Len;
    }
    else if (elementIndex == 1)
    {
        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        if (((*pSrc) == 0) || ((*pSrc) > MAX_TIMEZONE)) //年时区数
        {
            return DATA_ACCESS_RESULT_YOVER;
        }
        Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
        len += DTYPE_UINT8_Len;
        SetOffAddr = (elementIndex - 1) * DTYPE_UINT8_Len;
    }
    else if (elementIndex == 2)
    {
        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        if (((*pSrc) == 0) || ((*pSrc) > MAX_POTTABLE)) //日时段表数
        {
            return DATA_ACCESS_RESULT_DOVER;
        }
        Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
        len += DTYPE_UINT8_Len;
        SetOffAddr = (elementIndex - 1) * DTYPE_UINT8_Len;
    }
    else if (elementIndex == 3)
    {
        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        if (((*pSrc) == 0) || ((*pSrc) > MAX_POT)) //日时段数
        {
            return DATA_ACCESS_RESULT_DOVER;
        }
        Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
        len += DTYPE_UINT8_Len;
        SetOffAddr = (elementIndex - 1) * DTYPE_UINT8_Len;
    }
    else if (elementIndex == 4)
    {
        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        if (((*pSrc) == 0) || ((*pSrc) > MAX_FL)) //费率数
        {
            return DATA_ACCESS_RESULT_ROVER;
        }
        Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
        len += DTYPE_UINT8_Len;
        SetOffAddr = (elementIndex - 1) * DTYPE_UINT8_Len;
    }
    else if (elementIndex == 5)
    {
        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        //if( ((*pSrc) == 0)||((*pSrc) > MAX_HOLIDAY) )  //公共节假日数
        //  return DATA_ACCESS_RESULT_OTH;
        Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
        len += DTYPE_UINT8_Len;
        SetOffAddr = (elementIndex - 1) * DTYPE_UINT8_Len;
    }
    else
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_nTimeZone + SetOffAddr, Databuf, len);
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_nFl, &Bkgrd.PubData.nFl, 1);

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnDl698_Set400D
** Descriptions:    设置OI=0x400D 阶梯数
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_Ladder(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    if ((AtrIndex != 2) || (elementIndex != 0))
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if ((*pSrc++) != DTYPE_UINT8)
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    pParBuf = pSrc;
    if (*pSrc++ > 7)  //阶梯不允许超过7个
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_nLadder, pParBuf, 1);

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnDl698_Set4011
** Descriptions:    设置OI=0x4011 公共节假日表
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_HolidayPara(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    u16  SetOffAddr = 0, Data16 = 0 ;

    u8 *Databuf ;
    sDate_time_s_TypeDef    tmpClock;
    sHolidayTable_TypeDef tmpHoliday;

    Databuf = pParBuf;

    if (AtrIndex != 2)
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    //不支持元素索引为0时设置
    if ((elementIndex == 0) || (elementIndex > MAX_HOLIDAY))
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    if (((*pSrc++) != DTYPE_STRUCTURE) || ((*pSrc++) != 2))
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    if ((*pSrc++) != DTYPE_DATE)
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    STREAM_TO_UINT16(Data16, pSrc);

    tmpHoliday.Year = Data16;
    tmpHoliday.Month = *pSrc++;
    tmpHoliday.Day = *pSrc++;
    tmpHoliday.Week = *pSrc++;

    if ((*pSrc++) != DTYPE_UINT8)
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    tmpHoliday.nPOTTable = *pSrc++ ;

    //---------不全为00或者FF时判断时间合法性-----------
    //---------公共节假日表支持设置为全0或全FF---------
    if ((fnJudge_Value((u8 *)&tmpHoliday, 0x00, 6) == FALSE) &&
        (fnJudge_Value((u8 *)&tmpHoliday, 0xFF, 6) == FALSE))
    {
        Std_Memset((u8 *)&tmpClock, 0x00, sizeof(sDate_time_s_TypeDef));
        tmpClock.year = tmpHoliday.Year;
        tmpClock.month = tmpHoliday.Month;
        tmpClock.day = tmpHoliday.Day;
        if (fnCheck_Date_time_s(&tmpClock) == ERROR)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        if (tmpHoliday.Week != fnWeek_Calculate(tmpClock.year, tmpClock.month, tmpClock.day))
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        if (tmpHoliday.nPOTTable > MAX_POTTABLE)
        {
            return DATA_ACCESS_RESULT_DENY;
        }
    }

    SetOffAddr = (elementIndex - 1) * sizeof(sHolidayTable_TypeDef);

    //-----读取编程前内容-------------------
    //-----编程OAD-----------------
    *(Databuf + 0) = 0x40;
    *(Databuf + 1) = 0x11;
    *(Databuf + 2) = AtrIndex;
    *(Databuf + 3) = elementIndex;
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_HolidayTable + SetOffAddr, Databuf + 4, sizeof(sHolidayTable_TypeDef));
    //-----节假日编程事件记录---------------
    //  fnEvent_Operation(FileItemInfoNum_Evt_PrgHoliday , EVTSTART, Databuf );

    //-----------更新节假日---------------------
    Std_Memcpy(Databuf, (u8 *)&tmpHoliday, sizeof(sHolidayTable_TypeDef));
    fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_HolidayTable + SetOffAddr, Databuf, sizeof(sHolidayTable_TypeDef));

    Bkgrd.PubData.UpFlStatusFlag = 0x5a;
    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnDl698_Set4012
** Descriptions:    设置OI=0x4012 周休日特征字
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_WeekendWord(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    if ((AtrIndex != 2) || (elementIndex != 0))
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if ((*pSrc++) != DTYPE_BITSTRING)
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    if (*pSrc++ != 0x08)
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    Std_BitRvsSelf(pParBuf, pSrc++);

    fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_Weekend, pParBuf, 1);

    Bkgrd.PubData.UpFlStatusFlag = 0x5a;
    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnDl698_Set4013
** Descriptions:    设置OI=0x4013 周休日采用日时段表号
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_WeekendPOT(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    if ((AtrIndex != 2) || (elementIndex != 0))
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if ((*pSrc++) != DTYPE_UINT8)
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    pParBuf = pSrc;
    if (*pSrc++ > 0x08)     //时段表号不允许大于8
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    //  fnEvent_Operation(FileItemInfoNum_Evt_PrgWeekend , EVTSTART, NULL );

    fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_WeekendPOT, pParBuf, 1);

    Bkgrd.PubData.UpFlStatusFlag = 0x5a;
    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnDl698_Set4015
** Descriptions:    设置OI=0x4015 备用套时区表
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
const u8 TABDayOfMonth[] = {0, 31, 29, 31, 30, 31, 30, 31,  31, 30, 31, 30, 31};

u8 fnSet_ZoneTable(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    u16  SetOffAddr = 0;

    u8 num, i;

    sTimeZoneTable_TypeDef tmpZone;

    if (AtrIndex != 2)
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if (elementIndex > MAX_TIMEZONE)
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    if (elementIndex == 0)
    {
        if ((*pSrc++) != DTYPE_ARRAY)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        num = *pSrc++;
        if (num > MAX_TIMEZONE)
        {
            return DATA_ACCESS_RESULT_ACC;
        }
        for (i = 0; i < num; i++)
        {
            if (((*pSrc++) != DTYPE_STRUCTURE) || ((*pSrc++) != 3))
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if ((*pSrc++) != DTYPE_UINT8)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }
            tmpZone.Month = *pSrc++;
            if ((tmpZone.Month > 12) || (tmpZone.Month == 0))
            {
                return DATA_ACCESS_RESULT_ACC;
            }

            if ((*pSrc++) != DTYPE_UINT8)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }
            tmpZone.Day = *pSrc++;
            if ((tmpZone.Day > TABDayOfMonth[tmpZone.Month]) || (tmpZone.Day == 0))
            {
                return DATA_ACCESS_RESULT_ACC;
            }

            if ((*pSrc++) != DTYPE_UINT8)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }
            tmpZone.nPOTTable = *pSrc++;
            if ((tmpZone.nPOTTable > MAX_POTTABLE) || (tmpZone.nPOTTable == 0))
            {
                return DATA_ACCESS_RESULT_ACC;
            }

            Std_Memcpy(pParBuf + i * sizeof(sTimeZoneTable_TypeDef), (u8 *)&tmpZone, sizeof(sTimeZoneTable_TypeDef));
        }
        //---------不满14时区补最后一个--------------
        for (i = 0; i < (MAX_TIMEZONE - num); i++)
        {
            Std_Memcpy(pParBuf + (i + num)*sizeof(sTimeZoneTable_TypeDef), (u8 *)&tmpZone, sizeof(sTimeZoneTable_TypeDef));
        }

        //      fnEvent_Operation(FileItemInfoNum_Evt_PrgTimeZone , EVTSTART, NULL );

        SetOffAddr = (u16)sizeof(sDate_time_s_TypeDef) + (u16)(MAX_TIMEZONE * sizeof(sTimeZoneTable_TypeDef)); //切换时间及当前套时区长度
        fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_TimeZonePara + SetOffAddr, pParBuf, MAX_TIMEZONE * sizeof(sTimeZoneTable_TypeDef));
    }
    else
    {
        if (((*pSrc++) != DTYPE_STRUCTURE) || ((*pSrc++) != 3))
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        tmpZone.Month = *pSrc++;
        if ((tmpZone.Month > 12) || (tmpZone.Month == 0))
        {
            return DATA_ACCESS_RESULT_ACC;
        }

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        tmpZone.Day = *pSrc++;
        if ((tmpZone.Day > 31) || (tmpZone.Day == 0))
        {
            return DATA_ACCESS_RESULT_ACC;
        }

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        tmpZone.nPOTTable = *pSrc++;
        if ((tmpZone.nPOTTable > MAX_POTTABLE) || (tmpZone.nPOTTable == 0))
        {
            return DATA_ACCESS_RESULT_ACC;
        }

        //      fnEvent_Operation(FileItemInfoNum_Evt_PrgTimeZone , EVTSTART, NULL );

        SetOffAddr = (u16)sizeof(sDate_time_s_TypeDef) + (u16)((MAX_TIMEZONE + elementIndex - 1) * sizeof(sTimeZoneTable_TypeDef));

        fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_TimeZonePara + SetOffAddr, &tmpZone, sizeof(sTimeZoneTable_TypeDef));
    }

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnDl698_Set4017
** Descriptions:    设置OI=0x4017 备用套时段表
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_POTTable(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    u16  SetOffAddr = 0;

    u8 num, i;

    sPOTTable_TypeDef tmpPOTTable;
    u8 *Databuf ;

    if (AtrIndex != 2)
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if ((elementIndex > MAX_POTTABLE) || (elementIndex == 0))
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    if ((*pSrc++) != DTYPE_ARRAY)
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    num = *pSrc++;
    if (num > MAX_POT)
    {
        return DATA_ACCESS_RESULT_ACC;
    }
    //----------技术要求只支持单个时段表设置----------------
    for (i = 0; i < num; i++)
    {
        if (((*pSrc++) != DTYPE_STRUCTURE) || ((*pSrc++) != 3))
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        tmpPOTTable.Hour = *pSrc++;

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        tmpPOTTable.Minute = *pSrc++;

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        tmpPOTTable.Fl = *pSrc++;
        if ((tmpPOTTable.Fl > MAX_FL) || (tmpPOTTable.Fl == 0))
        {
            return DATA_ACCESS_RESULT_ROVER;
        }

        Std_Memcpy(pParBuf + i * sizeof(sPOTTable_TypeDef), (u8 *)&tmpPOTTable, sizeof(sPOTTable_TypeDef));
    }

    //-----------判断时段表合法性--相邻两个时段间隔需大于15min------------------
    if (CheckTPeriodValid(pParBuf,  num) == FALSE)
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    //---------不满补最后一个--------------
    for (i = 0; i < (MAX_POT - num); i++)
    {
        Std_Memcpy(pParBuf + (i + num)*sizeof(sPOTTable_TypeDef), (u8 *)&tmpPOTTable, sizeof(sPOTTable_TypeDef));
    }

    SetOffAddr = (u16)sizeof(sDate_time_s_TypeDef) + (u16)((MAX_POTTABLE + elementIndex - 1) * MAX_POT * sizeof(sTimeZoneTable_TypeDef)); //切换时间及当前套时段表长度

    Databuf = pParBuf + MAX_POT * sizeof(sPOTTable_TypeDef) + 10;
    //-----读取编程前内容-------------------
    //-----编程OAD-----------------
    *(Databuf + 0) = 0x40;
    *(Databuf + 1) = 0x17;
    *(Databuf + 2) = AtrIndex;
    *(Databuf + 3) = elementIndex;
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_POTTablePara + SetOffAddr, Databuf + 4, MAX_POT * sizeof(sPOTTable_TypeDef));
    //-----编程事件记录---------------
    //  fnEvent_Operation(FileItemInfoNum_Evt_PrgPOTTable , EVTSTART, Databuf );

    fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_POTTablePara + SetOffAddr, pParBuf, MAX_POT * sizeof(sPOTTable_TypeDef));

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnSet_MBackUpEnergy
** Descriptions:    设置OI=0x40EE 管理模组费率电能备份
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_MBackUpEnergy(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    u8 nFl_temp, i, j, res = DATA_ACCESS_RESULT_SUC;
    u16  len, OffAddr;

    if (AtrIndex != 2)
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if (elementIndex > 7)
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    if (elementIndex == 0)
    {
        if ((*pSrc++) != DTYPE_STRUCTURE)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != 7)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_DATETIME_S)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_MemRvs(pParBuf, pSrc, sizeof(sDate_time_s_TypeDef)); //电能备份时时间
        pSrc += sizeof(sDate_time_s_TypeDef);

        fnFile_Write(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_DateTime, pParBuf, sizeof(sDate_time_s_TypeDef));

        for (i = 0; i < 6; i++)
        {
            if ((*pSrc++) != DTYPE_ARRAY)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            nFl_temp = *pSrc++;  //费率数

            if (nFl_temp > 13)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            len = sizeof(sBackUpEnergy_TypeDef);
            Std_Memset(pParBuf, 0x00, len);

            *pParBuf = nFl_temp;
            for (j = 0; j < nFl_temp; j++)
            {
                if ((*pSrc++) != DTYPE_UINT64)
                {
                    res = DATA_ACCESS_RESULT_TYPE;
                    break;
                }

                Std_MemRvs(pParBuf + 1 + j * DTYPE_UINT64_Len, pSrc, DTYPE_UINT64_Len);
                pSrc += DTYPE_UINT64_Len;
            }

            if (res == DATA_ACCESS_RESULT_SUC)
            {
                OffAddr = len * i;
                fnFile_Write(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_PtPEgSh + OffAddr, pParBuf, len);
            }
        }
    }
    else if (elementIndex == 1)
    {
        if ((*pSrc++) != DTYPE_DATETIME_S)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_MemRvs(pParBuf, pSrc, sizeof(sDate_time_s_TypeDef)); //电能备份时时间

        fnFile_Write(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_DateTime, pParBuf, sizeof(sDate_time_s_TypeDef));
    }
    else if (elementIndex < 8)
    {
        if ((*pSrc++) != DTYPE_ARRAY)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        nFl_temp = *pSrc++;  //费率数

        if (nFl_temp > 13)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        len = sizeof(sBackUpEnergy_TypeDef);
        Std_Memset(pParBuf, 0x00, len);

        *pParBuf = nFl_temp;
        for (j = 0; j < nFl_temp; j++)
        {
            if ((*pSrc++) != DTYPE_UINT64)
            {
                res = DATA_ACCESS_RESULT_TYPE;
                break;
            }

            Std_MemRvs(pParBuf + 1 + j * DTYPE_UINT64_Len, pSrc, DTYPE_UINT64_Len);
            pSrc += DTYPE_UINT64_Len;
        }

        if (res == DATA_ACCESS_RESULT_SUC)
        {
            OffAddr = len * (elementIndex - 2);
            fnFile_Write(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_PtPEgSh + OffAddr, pParBuf, len);
        }
    }
    else
    {
        res = DATA_ACCESS_RESULT_DENY;
    }

    return res;
}

/*********************************************************************************************************
** Function name:
** Descriptions:    设置OI=0x4030
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_ParaVolYield(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    u8 i, offset, len;
    if (AtrIndex != 2)
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if (elementIndex == 0)
    {
        if ((*pSrc++) != DTYPE_STRUCTURE)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != 4) //
        {
            return DATA_ACCESS_RESULT_OTH;
        }

        offset = 0;
        len = sizeof(sVolYieldPara_TypeDef);
        for (i = 0; i < 4; i++)
        {
            if ((*pSrc++) != DTYPE_UINT16)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_MemRvs(pParBuf + i * 2, pSrc, 2);
            pSrc += 2;
        }
    }
    else if (elementIndex < 5)
    {
        if ((*pSrc++) != DTYPE_UINT16)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        i = elementIndex - 1;
        offset = 2 * i;
        Std_MemRvs(pParBuf, pSrc, 2);
        len = DTYPE_UINT16_Len;
        pSrc += 2;
    }
    else
    {
        return DATA_ACCESS_RESULT_ACC;
    }

    fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_ParaVolYield + offset, pParBuf, len);

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnDl698_Set4100_4101
** Descriptions:    设置OI=0x4100 需量周期；OI=0x4101 滑差时间
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
// #if(nPhs==ThreePhs)
//u8 fnSet_NeedPara(u8 elementIndex,u8 AtrIndex, u8 OIB2,u8  *pSrc, u8  *pParBuf)
//{
//  if( (AtrIndex != 2)||(elementIndex !=0 ) )
//      return DATA_ACCESS_RESULT_UNDEF;

//  if((*pSrc++)!=DTYPE_UINT8)
//      return DATA_ACCESS_RESULT_TYPE;

//  pParBuf = pSrc++;
//  if(OIB2 == 00) //需量周期
//  {
//     //需量周期只能在5min,10min,15min,30min,60min中选择
//      if( (*pParBuf ==5)||(*pParBuf ==10)||(*pParBuf ==15)
//        ||(*pParBuf ==30)||(*pParBuf ==60) )
//      {
//          fnFile_Write(FileId_ParaDoc, FileItemInfoOffAddr_DocPara_NeedCyc, pParBuf, 1);

//          fnDemand_Init();

//      }
//      else
//          return DATA_ACCESS_RESULT_ACC;
//  }
//  else  //滑差时间
//  {
//      //滑差时间只能在1min,2min,3min,5min中选择
//      if( (*pParBuf ==1)||(*pParBuf ==2)||(*pParBuf ==3)||(*pParBuf ==5) )
//      {
//          fnFile_Write(FileId_ParaDoc, FileItemInfoOffAddr_DocPara_NeedSlip, pParBuf, 1);
//          fnFile_Read(FileId_ParaDoc , FileItemInfoOffAddr_DocPara_NeedMode , &Demand.PriPara.Mode , 3 );
//          Demand.PriPara.Window = Demand.PriPara.Window/Demand.PriPara.Cell;  //累计窗口等于滑差时间除以需量周期
//          fnCrc_Check(0 , (u8 *)&Demand.PriPara , sizeof(Demand.PriPara) - 2 , (u8 *)&Demand.PriPara.Crc);
//      }
//      else
//          return DATA_ACCESS_RESULT_ACC;
//  }
//
//
//  return DATA_ACCESS_RESULT_SUC;
//}
// #endif
/*********************************************************************************************************
** Function name:   fnDl698_Set4103
** Descriptions:    设置OI=0x4103 资产管理编码
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_DeviceNo(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    if ((AtrIndex != 2) || (elementIndex != 0))
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if ((*pSrc++) != DTYPE_STRING)
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    if (*pSrc++ != 32)     //长度
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_DeviceNo, pSrc, 32);
    pSrc += 32;

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnDl698_Set4112_4113_4114
** Descriptions:    设置OI=0x4112 有功组合特征字；OI=0x4113 无功1组合特征字；OI=0x4114 无功2组合特征字；
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_Expression(u8 elementIndex, u8 AtrIndex, u8 OIB2, u8  *pSrc, u8  *pParBuf)
{
    u32 temp_Cnt = 0;

    if ((AtrIndex != 2) || (elementIndex != 0))
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if ((*pSrc++) != DTYPE_BITSTRING)
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    if ((*pSrc++) != 8) //size(8)
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    if (OIB2 == 2) //有功
        ;//fnEvent_Operation(FileItemInfoNum_Evt_PrgP , EVTSTART, NULL );
    else
    {
        pParBuf[0] = (OIB2 - 0x03);
        //      fnEvent_Operation(FileItemInfoNum_Evt_PrgQ , EVTSTART, pParBuf );
        if (OIB2 == 3) //无功1
        {
            fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_PrgQ1_Cnt, (u8 *)&temp_Cnt, 4);
            temp_Cnt ++;
            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_PrgQ1_Cnt, (u8 *)&temp_Cnt, 4);
        }
        else
        {
            fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_PrgQ2_Cnt, (u8 *)&temp_Cnt, 4);
            temp_Cnt ++;
            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_PrgQ2_Cnt, (u8 *)&temp_Cnt, 4);
        }
    }

    Std_BitRvsSelf(pParBuf, pSrc++);
    fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_PExpression + (OIB2 - 0x02), pParBuf, 1);
    fnEnergy_PluseParaInit();
    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnDl698_Set4116
** Descriptions:    设置OI=0x4016 结算日
** input parameters:  elementIndex 元素索引；AtrIndex:属性；pSrc :通讯下发数据buf
** output parameters:
** Returned value:设置成功或失败结果
*********************************************************************************************************/
u8 fnSet_RmDate(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    u16  SetOffAddr = 0;
    u8 i, num;
    sDF24 temRecord;

    if ((AtrIndex != 2) || (elementIndex > 3))
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if (elementIndex == 0)
    {
        if ((*pSrc++) != DTYPE_ARRAY)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        num = *pSrc++;
        if ((num == 0) || (num > 3))
        {
            return DATA_ACCESS_RESULT_ACC;
        }
        for (i = 0; i < num; i++)
        {
            if (((*pSrc++) != DTYPE_STRUCTURE) || ((*pSrc++) != 2))
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if ((*pSrc++) != DTYPE_UINT8)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }
            temRecord.Day = *pSrc++;

            if ((*pSrc++) != DTYPE_UINT8)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }
            temRecord.Hour = *pSrc++;

            if ((temRecord.Day != 99) || (temRecord.Hour != 99))
            {
                if ((temRecord.Day > 28) || (temRecord.Hour > 23))
                {
                    return DATA_ACCESS_RESULT_OTH;
                }
            }

            Std_Memcpy(pParBuf + i * sizeof(sDF24), (u8 *)&temRecord, sizeof(sDF24));
        }

        //      fnEvent_Operation(FileItemInfoNum_Evt_PrgRmDay , EVTSTART, NULL );

        fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_RmDate, pParBuf, num * sizeof(sDF24));
    }
    else
    {
        if (((*pSrc++) != DTYPE_STRUCTURE) || ((*pSrc++) != 2))
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        temRecord.Day = *pSrc++;

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        temRecord.Hour = *pSrc++;

        if ((temRecord.Day != 99) || (temRecord.Hour != 99))
        {
            if ((temRecord.Day > 28) || (temRecord.Hour > 23))
            {
                return DATA_ACCESS_RESULT_OTH;
            }
        }

        Std_Memcpy(pParBuf, (u8 *)&temRecord, sizeof(sDF24));

        //          fnEvent_Operation(FileItemInfoNum_Evt_PrgRmDay , EVTSTART, NULL );

        SetOffAddr = (elementIndex - 1) * sizeof(sDF24);
        fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_RmDate + SetOffAddr, pParBuf, sizeof(sDF24));
    }

    return DATA_ACCESS_RESULT_SUC;
}

const u8  ServerVer_Offset[] = {0, 4, 8, 14, 18, 24};
/*********************************************************************************************************
** Function name:   fnSet_DevicePara
** Descriptions:
** input parameters:  OAD:OAD
** output parameters:
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnSet_DevicePara(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    u8  len, i, temp_offset, ch[3];
    u32 OAD;

    //厂内模式下允许设置
    if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable == 1)
    {
        if (AtrIndex == 2) //设备描述符
        {
            if ((*pSrc++) != DTYPE_STRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }
            len = *pSrc++;
            if (len > 32)     //长度
            {
                return DATA_ACCESS_RESULT_OTH;
            }

            fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_MeterModel, pSrc, len);
            pSrc += 32;
        }
        else if (AtrIndex == 3) //版本信息
        {
            if (elementIndex == 0)
            {
                if ((*pSrc++) != DTYPE_STRUCTURE)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                if (*pSrc++ != 6)     //
                {
                    return DATA_ACCESS_RESULT_OTH;
                }
                temp_offset = 0;
                for (i = 0; i < 6; i++)
                {
                    if ((*pSrc++) != DTYPE_STRING)
                    {
                        return DATA_ACCESS_RESULT_TYPE;
                    }

                    len = *pSrc++;
                    Std_Memcpy(pParBuf + temp_offset, pSrc, len);
                    pSrc += len;
                    temp_offset += len;
                }

                fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_ServerVer, pParBuf, FileItemInfoLen_ASCIIPara_ServerVer);
            }
            else if (elementIndex < 7)
            {
                if ((*pSrc++) != DTYPE_STRING)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                len = *pSrc++;
                Std_Memcpy(pParBuf, pSrc, len);
                temp_offset = ServerVer_Offset[elementIndex - 1];

                fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_ServerVer + temp_offset, pParBuf, len);
                pSrc += len;
            }
            else
            {
                return DATA_ACCESS_RESULT_OTH;
            }
        }
        else if (AtrIndex == 4) //生产日期
        {
            if ((*pSrc++) != DTYPE_DATETIME_S)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }
            Std_MemRvs(pParBuf, pSrc, 7);
            fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_ProductDate, pParBuf, 7);
            pSrc += 7;
        }

        return DATA_ACCESS_RESULT_SUC;
    }

    if (AtrIndex == 7)
    {
        if ((*pSrc++) != DTYPE_BOOLEAN)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        EvtRptData.Para.FollowAllow = *pSrc++;

        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_FollowAllow, &EvtRptData.Para.FollowAllow, 1);

        fnCrc_Check(0, &EvtRptData.Para.AtiveAllow, sizeof(sEvtRptPara_TypeDef) - 2, (u8 *)&EvtRptData.Para.Crc);
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_Crc, (u8 *)&EvtRptData.Para.Crc, FileItemInfoLen_EvtReport_Crc);
    }
    else if (AtrIndex == 8)
    {
        if ((*pSrc++) != DTYPE_BOOLEAN)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        EvtRptData.Para.AtiveAllow = *pSrc++;

        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_AtiveAllow, &EvtRptData.Para.AtiveAllow, 1);

        fnCrc_Check(0, &EvtRptData.Para.AtiveAllow, sizeof(sEvtRptPara_TypeDef) - 2, (u8 *)&EvtRptData.Para.Crc);
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_Crc, (u8 *)&EvtRptData.Para.Crc, FileItemInfoLen_EvtReport_Crc);
    }
    else if (AtrIndex == 10)
    {
        if (elementIndex != 0) //不允许单个设置
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_ARRAY)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        len = *pSrc++;
        if (len > 3)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_Memset(&ch[0], 0x00, 3);

        for (i = 0; i < len; i++)
        {
            if ((*pSrc++) != DTYPE_OAD)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            OAD = Std_Msb32DataGet(pSrc);
            pSrc += 4;

            if (OAD == 0xF2090201)
            {
                ch[i] = 0x09;
            }
            else if (OAD == 0xF2010201)
            {
                ch[i] = 0x01;
            }
            else if (OAD == 0xF2010202)
            {
                ch[i] = 0x02;
            }
            else
            {
                return DATA_ACCESS_RESULT_TYPE;
            }
        }

        Std_Memcpy(&EvtRptData.Para.RptChannel[0], &ch[0], 3);

        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptChannel, &EvtRptData.Para.RptChannel[0], 3);

        fnCrc_Check(0, &EvtRptData.Para.AtiveAllow, sizeof(sEvtRptPara_TypeDef) - 2, (u8 *)&EvtRptData.Para.Crc);
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_Crc, (u8 *)&EvtRptData.Para.Crc, FileItemInfoLen_EvtReport_Crc);
    }
    else
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnSet_DevicePara
** Descriptions:
** input parameters:  OAD:OAD
** output parameters:
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnSet_LinkPara(u8 elementIndex, u8 AtrIndex, u8  *pSrc, u8  *pParBuf)
{
    //  u8  len , i , temp_offset;

    if (AtrIndex == 2)
    {
        if (elementIndex != 0)
        {
            return DATA_ACCESS_RESULT_OTH;
        }

        if ((*pSrc++) != DTYPE_STRING)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != 8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        //-----判密码-------------
        Std_AsciiStrToHexStr(pParBuf, pSrc, 8);
        pSrc += 8;
        //698固定用00级密码
        fnFile_Write(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SecretPara, pParBuf, 4);
    }
    else
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************
* @fn      fnSet_FactoryPara  设置厂内参数
*
* @brief
*
* @param
*
* @return
**********************************************************************/
u8 fnSet_FactoryPara(u32  OAD, u8  *pSrc, u8  *pParBuf)
{
    u8 res = DATA_ACCESS_RESULT_SUC ;
    u8 len;

    if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable == 0)  //----仅允许厂内编程-------
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    switch (OAD) //有多个元素索引参数
    {
        case 0x41040200:  //额定电压
            if ((*pSrc++) != DTYPE_STRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            len = *pSrc++;
            if (len > 6)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_RatingVol, pSrc, len);
            pSrc += len;

            break;

        case 0x41050200:  //额定电流
            if ((*pSrc++) != DTYPE_STRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            len = *pSrc++;
            if (len > 6)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_RatingCur, pSrc, len);
            pSrc += len;

            break;

        case 0x41060200:  //最大电流
            if ((*pSrc++) != DTYPE_STRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }
            len = *pSrc++;
            if (len > 6)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }
            fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_MaxCur, pSrc, len);
            pSrc += len;

            break;

        case 0x41060300:  //最小电流
            if ((*pSrc++) != DTYPE_STRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            len = *pSrc++;
            if ((len < 2) || (len > 32))
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_MinCur, pSrc, len);
            pSrc += len;

            break;

        case 0x41060400:  //转折电流
            if ((*pSrc++) != DTYPE_STRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            len = *pSrc++;
            if ((len < 2) || (len > 32))
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_TrCur, pSrc, len);
            pSrc += len;

            break;

        case 0x41070200:  //---有功准确度等级-----
            if ((*pSrc++) != DTYPE_STRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            len = *pSrc++;
            if (len > 4)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_PGrade, pSrc, len);
            pSrc += len;

            break;

        case 0x41080200:  //---无功准确度等级-----
            if ((*pSrc++) != DTYPE_STRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            len = *pSrc++;
            if (len > 4)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_QGrade, pSrc, len);
            pSrc += len;

            break;
        case 0x410B0200:  //---电表型号-----
            if ((*pSrc++) != DTYPE_STRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            len = *pSrc++;
            if (len > 32)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_MeterModel, pSrc, len);
            pSrc += len;

            break;

        case 0x41110300:  //---软件备案号-----
            if ((*pSrc++) != DTYPE_ARRAY)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if ((*pSrc++) != 1)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

        case 0x41110301:  //---软件备案号-----
            Std_Memset(pParBuf, 0x00, 32);

            if ((*pSrc++) != DTYPE_STRUCTURE)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if ((*pSrc++) != 6)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if ((*pSrc++) != DTYPE_STRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            len = *pSrc++;
            if (len > 2)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_Memcpy(pParBuf, pSrc, len);
            pSrc += len;

            if ((*pSrc++) != DTYPE_STRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            len = *pSrc++;
            if (len > 4)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_Memcpy(pParBuf + 2, pSrc, len);
            pSrc += len;

            if ((*pSrc++) != DTYPE_UINT8)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_Memcpy(pParBuf + 6, pSrc, 1);
            pSrc += 1;

            if ((*pSrc++) != DTYPE_STRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            len = *pSrc++;
            if (len > 8)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_Memcpy(pParBuf + 7, pSrc, len);
            pSrc += len;

            if ((*pSrc++) != DTYPE_UINT8)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_Memcpy(pParBuf + 15, pSrc, 1);
            pSrc += 1;

            if ((*pSrc++) != DTYPE_STRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            len = *pSrc++;
            if (len > 16)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_Memcpy(pParBuf + 16, pSrc, len);
            pSrc += len;

            fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_SoftWareInfo, pParBuf, 32);
            pSrc += len;

            break;

        default:
            res = DATA_ACCESS_RESULT_DENY;
            break;
    }

    return res;
}

/*********************************************************************
* @fn      fnSet_Para  设置参数 class8
*
* @brief
*
* @param
*
* @return
**********************************************************************/
u8 fnSet_Para(u32  OAD, u8  *pSrc, u8  *pParBuf)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    u16 OIA_B = (OAD >> 16 & 0xFFFF);

    u8 res = DATA_ACCESS_RESULT_SUC ;

    switch (OIA_B) //有多个元素索引参数
    {
        case 0x4000:  //日期时间
            res = fnSet_DateTime(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x4001:  //通讯地址

            res = fnSet_ComAddr_UserNo(pOadAys->elementIndex, pOadAys->AtrIndex, pOadAys->OIB2, pSrc, pParBuf);
            break;

        case 0x4003:  //客户编号
            res = fnSet_UserNo(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x4004:   //设备地理位置
            res = fnSet_MeterPlace(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x4007:   //LCD参数
            res = fnSet_LCDPara(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;
        case 0x4008:
        case 0x4009:
            #if(METERTYPE==2)
        case 0x400A:
        case 0x400B:  //切换时间
            #endif
            res = fnSet_SwitchTime(pOadAys->elementIndex, pOadAys->AtrIndex, pOadAys->OIB2, pSrc, pParBuf);
            break;

        case 0x400C:   //时区时段表参数
            res = fnSet_RatePara(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x4011:   //公共假日表
            res = fnSet_HolidayPara(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x4012:   //   周休日特征字
            res = fnSet_WeekendWord(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x4013:   //周休日表号
            res = fnSet_WeekendPOT(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x4015:   //备用套时区表
            res = fnSet_ZoneTable(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x4017:   //备用套时段表
            res = fnSet_POTTable(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x40EE:   //管理模组费率电能备份
            res = fnSet_MBackUpEnergy(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x4103:   //资产管理编码
            res = fnSet_DeviceNo(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x4112:  //有功组合特征字
            #if(nPhs==ThreePhs)
        case 0x4113:  //无功1组合特征字
        case 0x4114:  //无功2组合特征字
            #endif
            res = fnSet_Expression(pOadAys->elementIndex, pOadAys->AtrIndex, pOadAys->OIB2, pSrc, pParBuf);
            break;
        case 0x4116:   //结算日
            res = fnSet_RmDate(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x4300:   //电气设备
            res = fnSet_DevicePara(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x4401:   //应用连接接口
            res = fnSet_LinkPara(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;
            #if(METERTYPE==2)
        case 0x400D:   //阶梯数
            res = fnSet_Ladder(pOadAys->elementIndex, pOadAys->AtrIndex, pSrc, pParBuf);
            break;

        case 0x4019:   //费率电价

            break;

        case 0x401B:   //阶梯电价 待完善

            break;
            #endif

        case 0x4104:
        case 0x4105:
        case 0x4106:
        case 0x4107:
        case 0x4108:
        case 0x410B:
        case 0x4111:
            //-----仅允许厂内设置参数----------------
            res = fnSet_FactoryPara(OAD, pSrc, pParBuf);
            break;

        default:
            res = DATA_ACCESS_RESULT_UNDEF;
            break;
    }

    return  res;
}

/*********************************************************************
* @fn      fnSet_VarPara  设置参数 2015 主动上报状态字
*
* @brief
*
* @param
*
* @return
**********************************************************************/
u8 fnSet_VarPara(u32  OAD, u8  *pSrc, u8  *pParBuf)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    u16 OIA_B = (OAD >> 16 & 0xFFFF);
    u8 i, temp[4];

    if (OIA_B == 0x2015)
    {
        if (pOadAys->elementIndex != 0)
        {
            return DATA_ACCESS_RESULT_UNDEF;
        }

        if (pOadAys->AtrIndex == 4)
        {
            if ((*pSrc++) != DTYPE_BITSTRING)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if ((*pSrc++) != 0x20) //长度
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            for (i = 0; i < 4; i++)
            {
                Std_BitRvsSelf(&temp[i], pSrc++);
            }

            if ((temp[0] & 0xD5) || (temp[1] & 0x3C) || (temp[2] & 0xFF) || (temp[3] & 0xFF)) //保留位不允许设置
            {
                return DATA_ACCESS_RESULT_OTH;
            }

            Std_Memcpy((u8 *)&EvtRptData.Para.RptStatusMode, &temp[0], 4);
            fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatusMode, &temp[0], 4);

            fnCrc_Check(0, &EvtRptData.Para.AtiveAllow, sizeof(sEvtRptPara_TypeDef) - 2, (u8 *)&EvtRptData.Para.Crc);
            fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_Crc, (u8 *)&EvtRptData.Para.Crc, FileItemInfoLen_EvtReport_Crc);
        }
        else if (pOadAys->AtrIndex == 5)
        {
            if ((*pSrc++) != DTYPE_ENUM)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            EvtRptData.Para.RptStatusAllow = *pSrc++;
            fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatusAllow, &EvtRptData.Para.RptStatusAllow, 1);

            fnCrc_Check(0, &EvtRptData.Para.AtiveAllow, sizeof(sEvtRptPara_TypeDef) - 2, (u8 *)&EvtRptData.Para.Crc);
            fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_Crc, (u8 *)&EvtRptData.Para.Crc, FileItemInfoLen_EvtReport_Crc);
        }
    }
    else
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnSet_DispPara
** Descriptions:    class=17,OI=0xF300 自动轮显,OI=0xF301   按键轮显参数
** input parameters:  OAD:OAD
** output parameters: pSrc 通讯下发数据
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnSet_DispPara(u32  OAD, u8  *pSrc, u8  *pParBuf)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    u8 num, i;
    sDispItem_TypeDef Disptemp;

    u16 OIA_B = (OAD >> 16 & 0xFFFF), SetOffAddr = 0;
    sDl698AL_ObjInfo_TypeDef  pObj;

    if ((OIA_B != 0xF300) && (OIA_B != 0xF301))
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    if (pOadAys->AtrIndex > 4)  //不允许属性大于4
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }
    if (pOadAys->AtrIndex == 2)  //显示对象列表
    {
        if (pOadAys->elementIndex == 0)
        {
            if ((*pSrc++) != DTYPE_ARRAY)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            num = *pSrc++;
            if (num > MAX_CYCDISP)
            {
                return DATA_ACCESS_RESULT_ACC;
            }

            for (i = 0; i < num; i++)
            {
                if (((*pSrc++) != DTYPE_STRUCTURE) || ((*pSrc++) != 2))
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                if ((*pSrc++) != DTYPE_CSD)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                Std_Memset((u8 *)&Disptemp, 0x00, sizeof(sDispItem_TypeDef));
                Disptemp.CSD = *pSrc++ ;

                if (Disptemp.CSD == 1) //ROAD
                {
                    Std_MemRvs(&Disptemp.M_Element, pSrc, 4);
                    pObj.oi = Std_Msb16DataGet(pSrc);
                    if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
                    {
                        return DATA_ACCESS_RESULT_DENY;
                    }
                    pSrc += (4 + 1);

                    Std_MemRvs(&Disptemp.Element, pSrc, 4);
                    pObj.oi = Std_Msb16DataGet(pSrc);
                    if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
                    {
                        return DATA_ACCESS_RESULT_DENY;
                    }

                    pSrc += 4;
                }
                else
                {
                    Std_MemRvs(&Disptemp.M_Element, pSrc, 4);
                    pObj.oi = Std_Msb16DataGet(pSrc);
                    if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
                    {
                        return DATA_ACCESS_RESULT_DENY;
                    }

                    pSrc += 4;
                }

                if ((*pSrc++) != DTYPE_UINT8)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                Disptemp.nDispIndex = *pSrc++;

                Std_Memcpy(pParBuf + (u16)i * sizeof(sDispItem_TypeDef), (u8 *)&Disptemp, sizeof(sDispItem_TypeDef));
            }

            if (OIA_B == 0xF300)
            {
                fnFile_Write(FileId_ParaDisp,
                             FileItemInfoOffAddr_DispPara_CycDispItem,
                             pParBuf,
                             (u32)num * sizeof(sDispItem_TypeDef));
            }
            else
            {
                fnFile_Write(FileId_ParaDisp,
                             FileItemInfoOffAddr_DispPara_KeyDispItem,
                             pParBuf,
                             (u32)num * sizeof(sDispItem_TypeDef));
            }
        }
        else if (pOadAys->elementIndex <= MAX_CYCDISP)
        {
            if (((*pSrc++) != DTYPE_STRUCTURE) || ((*pSrc++) != 2))
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if ((*pSrc++) != DTYPE_CSD)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_Memset((u8 *)&Disptemp, 0x00, sizeof(sDispItem_TypeDef));
            Disptemp.CSD = *pSrc++ ;

            if (Disptemp.CSD == 1) //ROAD
            {
                Std_MemRvs(&Disptemp.M_Element, pSrc, 4);
                pObj.oi = Std_Msb16DataGet(pSrc);
                if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
                {
                    return DATA_ACCESS_RESULT_DENY;
                }
                pSrc += (4 + 1);

                Std_MemRvs(&Disptemp.Element, pSrc, 4);
                pObj.oi = Std_Msb16DataGet(pSrc);
                if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
                {
                    return DATA_ACCESS_RESULT_DENY;
                }
                pSrc += 4;
            }
            else
            {
                Std_MemRvs(&Disptemp.M_Element, pSrc, 4);
                pObj.oi = Std_Msb16DataGet(pSrc);
                if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
                {
                    return DATA_ACCESS_RESULT_DENY;
                }
                pSrc += 4;
            }

            if ((*pSrc++) != DTYPE_UINT8)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Disptemp.nDispIndex = *pSrc++;

            SetOffAddr = (u16)(pOadAys->elementIndex - 1) * sizeof(sDispItem_TypeDef);
            if (OIA_B == 0xF300)
            {
                fnFile_Write(FileId_ParaDisp,
                             FileItemInfoOffAddr_DispPara_CycDispItem + SetOffAddr,
                             &Disptemp,
                             sizeof(sDispItem_TypeDef));
            }
            else
            {
                fnFile_Write(FileId_ParaDisp,
                             FileItemInfoOffAddr_DispPara_KeyDispItem + SetOffAddr,
                             &Disptemp,
                             sizeof(sDispItem_TypeDef));
            }
        }
        else
        {
            return DATA_ACCESS_RESULT_UNDEF;
        }
    }
    else if (pOadAys->AtrIndex == 3)  //显示时间
    {
        if (pOadAys->elementIndex != 0)
        {
            return DATA_ACCESS_RESULT_UNDEF;
        }

        if ((*pSrc++) != DTYPE_UINT16)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_MemRvs(pParBuf, pSrc, 2);
        pSrc += 2;
        if (OIA_B == 0xF300)
        {
            fnFile_Write(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_AutoDispTime, pParBuf, 2);
        }
        else
        {
            fnFile_Write(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_KeyDispTime, pParBuf, 2);
        }
    }
    else   //显示参数
    {
        if (pOadAys->elementIndex != 1) //只允许设置当前总对象数(按键或循显屏数)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        num = *pSrc++;
        if (num > MAX_CYCDISP)
        {
            return DATA_ACCESS_RESULT_ACC;
        }

        if (OIA_B == 0xF300)
        {
            fnFile_Write(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_nCycDisp, &num, 1);
        }
        else
        {
            fnFile_Write(FileId_ParaDisp, FileItemInfoOffAddr_DispPara_nKeyDisp, &num, 1);
        }
    }
    //------刷新RAM数据------------------------

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnSet_SafeModePara
** Descriptions:    OI=0xF100
** input parameters:  OAD:OAD
** output parameters: pSrc 通讯下发数据
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnSet_SafeModePara(u32  OAD, u8  *pSrc, u8  *pParBuf)
{
    ///////////////
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    u16 SecrettPrgKeyValid;

    u16 OIA_B = (OAD >> 16 & 0xFFFF);

    if (OIA_B == 0xF101)
    {
        if (pOadAys->AtrIndex == 2)   //安全模式参数
        {
            if (pOadAys->elementIndex != 0)  //
            {
                return DATA_ACCESS_RESULT_DENY;
            }

            fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 6, &SecrettPrgKeyValid, 2);
            if (SecrettPrgKeyValid == 0x00)
            {
                return DATA_ACCESS_RESULT_DENY;
            }

            if ((*pSrc++) != DTYPE_ENUM)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            fnFile_Write(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SafeModeFlag, pSrc++, 1);
        }
        else
        {
            return DATA_ACCESS_RESULT_UNDEF;
        }
    }
    else if ((OAD == 0xF1000E00) && (Secret.CA == MASTER))  //红外门限时效设置
    {
        if ((*pSrc++) != DTYPE_UINT32)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_MemRvs(pParBuf, pSrc, 4);

        fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_tIRPrg, pParBuf, FileItemInfoLen_HighPara_tIRPrg);
        pSrc += 4;
    }
    else if ((OAD == 0xF1000E00) && (Secret.CA == TERMINAL)) //终端身份认证有效时长
    {
        if ((*pSrc++) != DTYPE_UINT32)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_MemRvs(pParBuf, pSrc, 4);

        fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_tTerminalPrg, pParBuf, FileItemInfoLen_HighPara_tTerminalPrg);
        pSrc += 4;
    }
    else
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnSet_EvtPara
** Descriptions:
** input parameters:  OAD:OAD
** output parameters:
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnSet_EvtPara(u32  OAD, u8  *pSrc, u8  *pParBuf)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    sContextList_TypeDef  tmplist;
    sDl698AL_ObjInfo_TypeDef  pObj;

    u16 OIA_B = (OAD >> 16 & 0xFFFF), recordlen;
    u8  Offset = 0, len = 0 ;

    u8 i, num, item = FileItemInfoNum_Evt_Max, class_id ;

    item = fnGet_EvtItem(OIA_B, &class_id);
    if ((item >= FileItemInfoNum_Evt_Max) || (class_id != ITEMCLASS7))
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    if (pOadAys->AtrIndex == 3)  //关联对象属性表
    {
        //--------仅支持厂内模式下修改------------
        if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable != 1)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        if (pOadAys->elementIndex != 0)
        {
            return DATA_ACCESS_RESULT_OTH;
        }

        if ((*pSrc++) != DTYPE_ARRAY)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        num = *pSrc++;

        Std_Memset(pParBuf, 0x00, FileItemInfo_EvtCtxlist[item].Len);

        *pParBuf = num;  //关联对象属性表个数
        tmplist.len = 0;
        Std_Memcpy((u8 *)&tmplist.OffPos, EvtStdlist[item].Addr + 1, 2);
        for (i = 0; i < num; i++)
        {
            if ((*pSrc++) != DTYPE_OAD)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_MemRvs((u8 *)&tmplist.OAD, pSrc, 4);

            pObj.oad_omd = tmplist.OAD;
            pObj.oi = (u16)(pObj.oad_omd >> 16);
            if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
            {
                return DATA_ACCESS_RESULT_DENY;
            }

            pSrc += 4;

            u8 *PMyData;
            PMyData = pParBuf + 512;
            tmplist.OffPos += tmplist.len;

            tmplist.len = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF), PMyData);

            //--------判每条事件记录长度----------------
            recordlen = tmplist.len + tmplist.OffPos;
            if (recordlen > FileItemInfo_EvtRecord[item].Len / MAX_EVRECORD_TABLE[item])
            {
                return DATA_ACCESS_RESULT_HD;
            }

            Std_Memcpy(pParBuf + i * sizeof(sContextList_TypeDef) + 3, (u8 *)&tmplist, sizeof(sContextList_TypeDef));
        }
        Std_Memcpy(pParBuf + 1, (u8 *)&recordlen, 2);
        //-------关联对象属性表总个数(1byte)+根据关联对象属性表计算每条事件记录长度(2byte)+关联对象属性表-----------------------
        fnFile_Write(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[item].OffAddr, pParBuf, FileItemInfo_EvtCtxlist[item].Len);

        //设置关联对象属性表对应事件记录需清零，清事件记录头
        Std_Memset(pParBuf, 0x00, FileItemInfo_EvtRcdHead[item].Len);
        fnFile_Write(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, pParBuf, FileItemInfo_EvtRcdHead[item].Len);

        fnEvent_Clr_Status(item, 0xFF);
    }
    else if (pOadAys->AtrIndex == 6)  //配置参数
    {
        //--------仅支持厂内模式下修改------------
        if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable != 1)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        u8 *Databuf;

        if (FileItemInfo_EvtCfgPara[item].Len == 0)
        {
            return DATA_ACCESS_RESULT_OTH;
        }

        Databuf = pParBuf;
        Offset = 0;
        len = FileItemInfo_EvtCfgPara[item].Len;

        //----正向，反向，量超限格式一样----
        //      if( (item == FileItemInfoNum_Evt_PtOverNeed)
        //          ||(item == FileItemInfoNum_Evt_NtOverNeed)  )
        //      {
        //          if( pOadAys->elementIndex == 0)
        //          {
        //              if((*pSrc++)!=DTYPE_STRUCTURE)
        //                  return DATA_ACCESS_RESULT_TYPE;
        //
        //               if((*pSrc++)!=2)//2个结构体
        //                  return DATA_ACCESS_RESULT_OTH;
        //
        //              if((*pSrc++)!=DTYPE_UINT32)
        //                  return DATA_ACCESS_RESULT_TYPE;
        //
        //              Std_MemRvsSelf(pSrc, DTYPE_UINT32_Len);  //大小端转换
        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT32_Len);
        //              if((*pSrc++)!=DTYPE_UINT8)
        //                  return DATA_ACCESS_RESULT_TYPE;

        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
        //          }
        //          else if( pOadAys->elementIndex == 1)
        //          {
        //              if((*pSrc++)!=DTYPE_UINT32)
        //                  return DATA_ACCESS_RESULT_TYPE;
        //
        //              Std_MemRvsSelf(pSrc, DTYPE_UINT32_Len);  //大小端转换
        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT32_Len);
        //              Offset = 0;
        //              len = DTYPE_UINT32_Len;
        //          }
        //          else if( pOadAys->elementIndex == 2)
        //          {
        //              if((*pSrc++)!=DTYPE_UINT8)
        //                  return DATA_ACCESS_RESULT_TYPE;

        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
        //
        //              Offset = DTYPE_UINT32_Len;
        //              len = DTYPE_UINT8_Len;
        //          }
        //          else
        //              return DATA_ACCESS_RESULT_OTH;
        //      }
        //----不平衡事件格式一样---
        //      else if(    (item == FileItemInfoNum_Evt_UnblVol)
        //              ||(item == FileItemInfoNum_Evt_UnblCur)
        //              ||(item == FileItemInfoNum_Evt_OverUnblCur) )
        //      {
        //          if( pOadAys->elementIndex == 0)
        //          {
        //              if((*pSrc++)!=DTYPE_STRUCTURE)
        //                  return DATA_ACCESS_RESULT_TYPE;
        //
        //               if((*pSrc++)!=2)//2个结构体
        //                  return DATA_ACCESS_RESULT_OTH;
        //
        //              if((*pSrc++)!=DTYPE_INT16)
        //                  return DATA_ACCESS_RESULT_TYPE;
        //
        //              Std_MemRvsSelf(pSrc, DTYPE_INT16_Len);  //大小端转换
        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_INT16_Len);
        //              if((*pSrc++)!=DTYPE_UINT8)
        //                  return DATA_ACCESS_RESULT_TYPE;

        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
        //
        //          }
        //          else if( pOadAys->elementIndex == 1)
        //          {
        //              if((*pSrc++)!=DTYPE_INT16)
        //                  return DATA_ACCESS_RESULT_TYPE;
        //
        //              Std_MemRvsSelf(pSrc, DTYPE_INT16_Len);  //大小端转换
        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_INT16_Len);
        //              Offset = 0;
        //              len = DTYPE_INT16_Len;
        //          }
        //          else if( pOadAys->elementIndex == 2)
        //          {
        //              if((*pSrc++)!=DTYPE_UINT8)
        //                  return DATA_ACCESS_RESULT_TYPE;

        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
        //              Offset = DTYPE_INT16_Len;
        //              len = DTYPE_UINT8_Len;
        //          }
        //          else
        //              return DATA_ACCESS_RESULT_OTH;
        //      }
        //      else if(item == FileItemInfoNum_Evt_NLineErr)
        //      {
        //          if( pOadAys->elementIndex == 0)
        //          {
        //              if((*pSrc++)!=DTYPE_STRUCTURE)
        //                  return DATA_ACCESS_RESULT_TYPE;
        //
        //               if((*pSrc++)!=3)//2个结构体
        //                  return DATA_ACCESS_RESULT_OTH;
        //
        //              if((*pSrc++)!=DTYPE_INT32)
        //                  return DATA_ACCESS_RESULT_TYPE;
        //
        //              Std_MemRvsSelf(pSrc, DTYPE_UINT32_Len);  //大小端转换
        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT32_Len);

        //              if((*pSrc++)!=DTYPE_UINT16)
        //                  return DATA_ACCESS_RESULT_TYPE;

        //              Std_MemRvsSelf(pSrc, DTYPE_UINT16_Len);  //大小端转换
        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT16_Len);
        //
        //              if((*pSrc++)!=DTYPE_UINT8)
        //                  return DATA_ACCESS_RESULT_TYPE;

        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
        //          }
        //          else if( pOadAys->elementIndex == 1)
        //          {
        //              if((*pSrc++)!=DTYPE_INT32)
        //                  return DATA_ACCESS_RESULT_TYPE;
        //
        //              Std_MemRvsSelf(pSrc, DTYPE_INT32_Len);  //大小端转换
        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_INT32_Len);
        //              Offset = 0;
        //              len = DTYPE_UINT32_Len;
        //          }
        //          else if( pOadAys->elementIndex == 2)
        //          {
        //              if((*pSrc++)!=DTYPE_UINT16)
        //                  return DATA_ACCESS_RESULT_TYPE;
        //
        //              Std_MemRvsSelf(pSrc, DTYPE_UINT16_Len);  //大小端转换
        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT16_Len);
        //              Offset = DTYPE_UINT32_Len;
        //              len = DTYPE_UINT16_Len;
        //          }
        //          else if( pOadAys->elementIndex == 3)
        //          {
        //              if((*pSrc++)!=DTYPE_UINT8)
        //                  return DATA_ACCESS_RESULT_TYPE;

        //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
        //
        //              Offset = DTYPE_UINT32_Len + DTYPE_UINT16_Len;
        //              len = DTYPE_UINT8_Len;
        //          }
        //          else
        //              return DATA_ACCESS_RESULT_OTH;
        //      }
        //      else  //----只有延时事件一个参数-----
        {
            if (pOadAys->elementIndex == 0)
            {
                if ((*pSrc++) != DTYPE_STRUCTURE)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                if ((*pSrc++) != 1) //1个结构体
                {
                    return DATA_ACCESS_RESULT_OTH;
                }

                if ((*pSrc++) != DTYPE_UINT8)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
            }
            else if (pOadAys->elementIndex == 1)
            {
                if ((*pSrc++) != DTYPE_UINT8)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
                Offset = 0;
                len = FileItemInfo_EvtCfgPara[item].Len;
            }
            else
            {
                return DATA_ACCESS_RESULT_OTH;
            }
        }

        fnFile_Write(FileId_EvtCfgPara, FileItemInfo_EvtCfgPara[item].OffAddr + Offset, Databuf, len);

        fnFile_Read(FileId_EvtCfgPara, FileItemInfo_EvtCfgPara[0].OffAddr, &Trim, FileLen_EvtCfgPara);

        //------------先回读E2数据更新RAM后计算效验和--------------------------
        fnCrc_Check(0, (u8 *)&Trim, FileLen_EvtCfgPara - 2, (u8 *)&Trim.Crc);
        fnFile_Write(FileId_EvtCfgPara, FileItemInfoOffAddr_EvtCfgPara_Crc, (u8 *)&Trim.Crc, 2);
    }
    else if (pOadAys->AtrIndex == 8)  //上报标识
    {
        if (pOadAys->elementIndex != 0)
        {
            return DATA_ACCESS_RESULT_OTH;
        }

        if ((*pSrc++) != DTYPE_ENUM)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if (*pSrc & 0xFC) //只允许设置bit0,bit1  发生及结束上报有效
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        Offset = item / 8;
        i = item % 8;
        //-----------------------

        if ((*pSrc & 0x01) == 0x01) //发生上报
        {
            EvtRptData.Para.RptFlagHappen[Offset] |= 1 << i;
        }
        else
        {
            EvtRptData.Para.RptFlagHappen[Offset] &= ~(1 << i);
        }

        if ((*pSrc & 0x02) == 0x02) //结束上报
        {
            EvtRptData.Para.RptFlagEnd[Offset] |= 1 << i;
        }
        else
        {
            EvtRptData.Para.RptFlagEnd[Offset] &= ~(1 << i);
        }

        len = FileItemInfoLen_EvtReport_RptFlagHappen + FileItemInfoLen_EvtReport_RptFlagEnd;
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptFlagHappen, &EvtRptData.Para.RptFlagHappen[0], len);

        fnCrc_Check(0, &EvtRptData.Para.AtiveAllow, sizeof(sEvtRptPara_TypeDef) - 2, (u8 *)&EvtRptData.Para.Crc);
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_Crc, (u8 *)&EvtRptData.Para.Crc, FileItemInfoLen_EvtReport_Crc);

        pSrc++;
    }
    else if (pOadAys->AtrIndex == 0x0B)  //上报方式
    {
        if (pOadAys->elementIndex != 0)
        {
            return DATA_ACCESS_RESULT_OTH;
        }

        if ((*pSrc++) != DTYPE_ENUM)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Offset = item / 8;
        i = item % 8;
        //-----------------------
        if (*pSrc == 0x00)
        {
            EvtRptData.Para.RptMode[Offset] &= ~(1 << i);
        }
        else if (*pSrc == 0x01)
        {
            EvtRptData.Para.RptMode[Offset] |= 1 << i;
        }
        else
        {
            return DATA_ACCESS_RESULT_OTH;
        }

        len = FileItemInfoLen_EvtReport_RptMode;
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptMode, &EvtRptData.Para.RptMode[0], len);

        fnCrc_Check(0, &EvtRptData.Para.AtiveAllow, sizeof(sEvtRptPara_TypeDef) - 2, (u8 *)&EvtRptData.Para.Crc);
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_Crc, (u8 *)&EvtRptData.Para.Crc, FileItemInfoLen_EvtReport_Crc);

        pSrc++;
    }
    else
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnDl698_SetPhsEventPara
** Descriptions:    class24
** input parameters:  OAD:OAD
** output parameters:
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnSet_PhsEventPara(u32  OAD, u8  *pSrc, u8  *pParBuf)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    sContextList_TypeDef  tmplist;
    sDl698AL_ObjInfo_TypeDef  pObj;

    u16 OIA_B = (OAD >> 16 & 0xFFFF), recordlen;
    u8 Offset, len ;
    u8 i, num, item = FileItemInfoNum_Evt_Max, class_id ;

    item = fnGet_EvtItem(OIA_B, &class_id);
    if ((item >= FileItemInfoNum_Evt_Max) || (class_id != ITEMCLASS24))
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    if (pOadAys->AtrIndex == 2)  //关联对象属性表
    {
        //--------仅支持厂内模式下修改------------
        if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable != 1)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        if (pOadAys->elementIndex != 0)
        {
            return DATA_ACCESS_RESULT_OTH;
        }

        if ((*pSrc++) != DTYPE_ARRAY)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        num = *pSrc++;

        Std_Memset(pParBuf, 0x00, FileItemInfo_EvtCtxlist[item].Len);

        *pParBuf  = num;  //关联对象属性表个数

        tmplist.len = 0;
        Std_Memcpy((u8 *)&tmplist.OffPos, EvtStdlist[item].Addr + 1, 2);     //标准事件记录单元长度
        for (i = 0; i < num; i++)
        {
            if ((*pSrc++) != DTYPE_OAD)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_MemRvs((u8 *)&tmplist.OAD, pSrc, 4);
            pObj.oad_omd = tmplist.OAD;
            pObj.oi = (u16)(pObj.oad_omd >> 16);
            if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
            {
                return DATA_ACCESS_RESULT_DENY;
            }

            pSrc += 4;

            u8 *PMyData;
            PMyData = pParBuf + 512;
            tmplist.OffPos += tmplist.len;
            tmplist.len = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF), PMyData);
            //--------判每条事件记录长度----------------
            recordlen = tmplist.len + tmplist.OffPos;
            if (recordlen > FileItemInfo_EvtRecord[item].Len / MAX_EVRECORD_TABLE[item])
            {
                return DATA_ACCESS_RESULT_ACC;
            }

            Std_Memcpy(pParBuf + i * sizeof(sContextList_TypeDef) + 3, (u8 *)&tmplist, sizeof(sContextList_TypeDef));
        }

        Std_Memcpy(pParBuf + 1, (u8 *)&recordlen, 2);
        fnFile_Write(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[item].OffAddr, pParBuf, FileItemInfo_EvtCtxlist[item].Len);
        //设置关联对象属性表对应事件记录需清零，清事件记录头
        Std_Memset(pParBuf, 0x00, FileItemInfo_EvtRcdHead[item].Len);
        fnFile_Write(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, pParBuf, FileItemInfo_EvtRcdHead[item].Len);

        fnEvent_Clr_Status(item, 0xFF);
    }
    else if (pOadAys->AtrIndex == 5)  //配置参数
    {
        //  u8 *Databuf;

        if (FileItemInfo_EvtCfgPara[item].Len == 0)
        {
            return DATA_ACCESS_RESULT_OTH;
        }

        //  Databuf=pParBuf;
        Offset = 0;
        len = FileItemInfo_EvtCfgPara[item].Len;

        //      switch( item )
        {
            //          case FileItemInfoNum_Evt_LossVol:   //失压
            //              if( pOadAys->elementIndex == 0)
            //              {
            //                  if((*pSrc++)!=DTYPE_STRUCTURE)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                   if((*pSrc++)!=4)//4个结构体
            //                      return DATA_ACCESS_RESULT_OTH;
            //
            //                  if((*pSrc++)!=DTYPE_UINT16)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Std_MemRvsSelf(pSrc, DTYPE_UINT16_Len);  //大小端转换
            //                  Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT16_Len);
            //
            //                  if((*pSrc++)!=DTYPE_UINT16)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Std_MemRvsSelf(pSrc, DTYPE_UINT16_Len);  //大小端转换
            //                  Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT16_Len);

            //                  if((*pSrc++)!=DTYPE_INT32)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Std_MemRvsSelf(pSrc, DTYPE_INT32_Len);  //大小端转换
            //                  Copy_TO_STREAM(pParBuf, pSrc,DTYPE_INT32_Len);
            //
            //                  if((*pSrc++)!=DTYPE_UINT8)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
            //
            //
            //              }
            //              else if( ( pOadAys->elementIndex == 1)||( pOadAys->elementIndex == 2) )
            //              {
            //                  if((*pSrc++)!=DTYPE_UINT16)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Std_MemRvsSelf(pSrc, DTYPE_UINT16_Len);  //大小端转换
            //                  Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT16_Len);
            //                  Offset = (pOadAys->elementIndex - 1)*DTYPE_UINT16_Len;
            //                  len = DTYPE_UINT16_Len;
            //              }
            //              else if( pOadAys->elementIndex == 3)
            //              {
            //                  if((*pSrc++)!=DTYPE_INT32)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Std_MemRvsSelf(pSrc, DTYPE_INT32_Len);  //大小端转换
            //                  Copy_TO_STREAM(pParBuf, pSrc,DTYPE_INT32_Len);
            //                  Offset = 2*DTYPE_UINT16_Len;
            //                  len = DTYPE_INT32_Len;
            //              }
            //              else if( pOadAys->elementIndex == 4)
            //              {
            //                  if((*pSrc++)!=DTYPE_UINT8)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
            //                  Offset = 2*DTYPE_UINT16_Len + DTYPE_INT32_Len;
            //                  len = DTYPE_UINT8_Len;
            //              }
            //              else
            //                  return DATA_ACCESS_RESULT_OTH;
            //              break;

            //      case FileItemInfoNum_Evt_LackVol:
            //      case FileItemInfoNum_Evt_OverVol:
            //          if( pOadAys->elementIndex == 0)
            //          {
            //              if((*pSrc++)!=DTYPE_STRUCTURE)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //
            //               if((*pSrc++)!=2)//2个结构体
            //                  return DATA_ACCESS_RESULT_OTH;
            //
            //              if((*pSrc++)!=DTYPE_UINT16)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Std_MemRvsSelf(pSrc, DTYPE_UINT16_Len);  //大小端转换
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT16_Len);
            //
            //              if((*pSrc++)!=DTYPE_UINT8)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
            //
            //          }
            //          else if( pOadAys->elementIndex == 1)
            //          {
            //              if((*pSrc++)!=DTYPE_UINT16)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Std_MemRvsSelf(pSrc, DTYPE_UINT16_Len);  //大小端转换
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT16_Len);
            //              Offset = 0;
            //              len = DTYPE_UINT16_Len;
            //          }
            //          else if( pOadAys->elementIndex == 2)
            //          {
            //              if((*pSrc++)!=DTYPE_UINT8)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
            //              Offset = DTYPE_UINT16_Len;
            //              len = DTYPE_UINT8_Len;
            //          }
            //          else
            //              return DATA_ACCESS_RESULT_OTH;
            //          break;

            //      case FileItemInfoNum_Evt_LossPha:
            //      case FileItemInfoNum_Evt_BreakCur:
            //          if( pOadAys->elementIndex == 0)
            //          {
            //              if((*pSrc++)!=DTYPE_STRUCTURE)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //
            //               if((*pSrc++)!=3)//3个结构体
            //                  return DATA_ACCESS_RESULT_OTH;
            //
            //              if((*pSrc++)!=DTYPE_UINT16)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Std_MemRvsSelf(pSrc, DTYPE_UINT16_Len);  //大小端转换
            //              Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT16_Len);

            //              if((*pSrc++)!=DTYPE_INT32)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Std_MemRvsSelf(pSrc, DTYPE_INT32_Len);  //大小端转换
            //              Copy_TO_STREAM(pParBuf, pSrc, DTYPE_INT32_Len);
            //
            //              if((*pSrc++)!=DTYPE_UINT8)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
            //
            //          }
            //          else if( pOadAys->elementIndex == 1)
            //          {
            //              if((*pSrc++)!=DTYPE_UINT16)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Std_MemRvsSelf(pSrc, DTYPE_UINT16_Len);  //大小端转换
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT16_Len);
            //              Offset = 0;
            //              len = DTYPE_UINT16_Len;
            //          }
            //          else if( pOadAys->elementIndex == 2)
            //          {
            //              if((*pSrc++)!=DTYPE_INT32)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Std_MemRvsSelf(pSrc, DTYPE_INT32_Len);  //大小端转换
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_INT32_Len);
            //              Offset = DTYPE_UINT16_Len;
            //              len = DTYPE_INT32_Len;
            //          }
            //          else if( pOadAys->elementIndex == 3)
            //          {
            //              if((*pSrc++)!=DTYPE_UINT8)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
            //              Offset = DTYPE_UINT16_Len + DTYPE_INT32_Len;
            //              len = DTYPE_UINT8_Len;
            //          }
            //          else
            //              return DATA_ACCESS_RESULT_OTH;
            //          break;

            //      case FileItemInfoNum_Evt_LossCur:   //
            //              if( pOadAys->elementIndex == 0)
            //              {
            //                  if((*pSrc++)!=DTYPE_STRUCTURE)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                   if((*pSrc++)!=4)//4个结构体
            //                      return DATA_ACCESS_RESULT_OTH;
            //
            //                  if((*pSrc++)!=DTYPE_UINT16)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Std_MemRvsSelf(pSrc, DTYPE_UINT16_Len);  //大小端转换
            //                  Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT16_Len);
            //
            //                  if((*pSrc++)!=DTYPE_INT32)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Std_MemRvsSelf(pSrc, DTYPE_INT32_Len);  //大小端转换
            //                  Copy_TO_STREAM(pParBuf, pSrc,DTYPE_INT32_Len);

            //                  if((*pSrc++)!=DTYPE_INT32)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Std_MemRvsSelf(pSrc, DTYPE_INT32_Len);  //大小端转换
            //                  Copy_TO_STREAM(pParBuf, pSrc,DTYPE_INT32_Len);
            //
            //                  if((*pSrc++)!=DTYPE_UINT8)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
            //
            //              }
            //              else if( pOadAys->elementIndex == 1)
            //              {
            //                  if((*pSrc++)!=DTYPE_UINT16)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Std_MemRvsSelf(pSrc, DTYPE_UINT16_Len);  //大小端转换
            //                  Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT16_Len);
            //                  Offset = 0;
            //                  len = DTYPE_UINT16_Len;
            //              }
            //              else if( (pOadAys->elementIndex == 2)||(pOadAys->elementIndex == 3) )
            //              {
            //                  if((*pSrc++)!=DTYPE_INT32)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Std_MemRvsSelf(pSrc, DTYPE_INT32_Len);  //大小端转换
            //                  Copy_TO_STREAM(pParBuf, pSrc,DTYPE_INT32_Len);
            //                  Offset = DTYPE_UINT16_Len + (pOadAys->elementIndex - 2)*DTYPE_INT32_Len;
            //                  len = DTYPE_INT32_Len;
            //              }
            //              else if( pOadAys->elementIndex == 4)
            //              {
            //                  if((*pSrc++)!=DTYPE_UINT8)
            //                      return DATA_ACCESS_RESULT_TYPE;
            //                  Copy_TO_STREAM(pParBuf, pSrc, DTYPE_UINT8_Len);
            //                  Offset = DTYPE_UINT16_Len + 2*DTYPE_INT32_Len;
            //
            //                  len = DTYPE_UINT8_Len;
            //              }
            //              else
            //                  return DATA_ACCESS_RESULT_OTH;
            //              break;

            //      case FileItemInfoNum_Evt_OverCur:
            //      case FileItemInfoNum_Evt_InSwimPw:
            //      case FileItemInfoNum_Evt_OverPw:
            //          if( pOadAys->elementIndex == 0)
            //          {
            //              if((*pSrc++)!=DTYPE_STRUCTURE)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //
            //               if((*pSrc++)!=2)//2个结构体
            //                  return DATA_ACCESS_RESULT_OTH;
            //
            //              if((*pSrc++)!=DTYPE_INT32)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Std_MemRvsSelf(pSrc, DTYPE_INT32_Len);  //大小端转换
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_INT32_Len);
            //
            //              if((*pSrc++)!=DTYPE_UINT8)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
            //
            //          }
            //          else if( pOadAys->elementIndex == 1)
            //          {
            //              if((*pSrc++)!=DTYPE_INT32)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Std_MemRvsSelf(pSrc, DTYPE_INT32_Len);  //大小端转换
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_INT32_Len);
            //              Offset = 0;
            //              len = DTYPE_INT32_Len;
            //          }
            //          else if( pOadAys->elementIndex == 2)
            //          {
            //              if((*pSrc++)!=DTYPE_UINT8)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
            //              Offset = DTYPE_INT32_Len;
            //              len = DTYPE_UINT8_Len;
            //          }
            //          else
            //              return DATA_ACCESS_RESULT_OTH;
            //          break;

            //      case FileItemInfoNum_Evt_QtOverNeed: //无功需量超限
            //          if( pOadAys->elementIndex == 0)
            //          {
            //              if((*pSrc++)!=DTYPE_STRUCTURE)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //
            //               if((*pSrc++)!=2)//2个结构体
            //                  return DATA_ACCESS_RESULT_OTH;
            //
            //              if((*pSrc++)!=DTYPE_UINT32)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Std_MemRvsSelf(pSrc, DTYPE_UINT32_Len);  //大小端转换
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT32_Len);
            //
            //              if((*pSrc++)!=DTYPE_UINT8)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
            //
            //          }
            //          else if( pOadAys->elementIndex == 1)
            //          {
            //              if((*pSrc++)!=DTYPE_UINT32)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Std_MemRvsSelf(pSrc, DTYPE_UINT32_Len);  //大小端转换
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT32_Len);
            //              Offset = 0;
            //              len = DTYPE_UINT32_Len;
            //          }
            //          else if( pOadAys->elementIndex == 2)
            //          {
            //              if((*pSrc++)!=DTYPE_UINT8)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
            //              Offset = DTYPE_UINT32_Len;
            //              len = DTYPE_UINT8_Len;
            //          }
            //          else
            //              return DATA_ACCESS_RESULT_OTH;
            //          break;

            //      case FileItemInfoNum_Evt_OverPf: //功率因数超下限
            //          if( pOadAys->elementIndex == 0)
            //          {
            //              if((*pSrc++)!=DTYPE_STRUCTURE)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //
            //               if((*pSrc++)!=2)//2个结构体
            //                  return DATA_ACCESS_RESULT_OTH;
            //
            //              if((*pSrc++)!=DTYPE_INT16)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Std_MemRvsSelf(pSrc, DTYPE_INT16_Len);  //大小端转换
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_INT16_Len);
            //
            //              if((*pSrc++)!=DTYPE_UINT8)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
            //
            //          }
            //          else if( pOadAys->elementIndex == 1)
            //          {
            //              if((*pSrc++)!=DTYPE_INT16)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Std_MemRvsSelf(pSrc, DTYPE_INT16_Len);  //大小端转换
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_INT16_Len);
            //              Offset = 0;
            //              len = DTYPE_INT16_Len;
            //          }
            //          else if( pOadAys->elementIndex == 2)
            //          {
            //              if((*pSrc++)!=DTYPE_UINT8)
            //                  return DATA_ACCESS_RESULT_TYPE;
            //              Copy_TO_STREAM(pParBuf, pSrc,DTYPE_UINT8_Len);
            //              Offset = DTYPE_INT32_Len;
            //              len = DTYPE_UINT8_Len;
            //          }
            //          else
            //              return DATA_ACCESS_RESULT_OTH;
            //          break;

            //          default:
            return DATA_ACCESS_RESULT_OTH;
        }

        //      fnFile_Write(FileId_EvtCfgPara, FileItemInfo_EvtCfgPara[item].OffAddr+Offset, Databuf , len );
        //      fnFile_Read( FileId_EvtCfgPara ,FileItemInfo_EvtCfgPara[0].OffAddr , &Trim, FileLen_EvtCfgPara );
        //
        //      fnCrc_Check(0 , (u8 *)&Trim , FileLen_EvtCfgPara - 2 , (u8 *)&Trim.Crc);

        //      fnFile_Write(FileId_EvtCfgPara ,FileItemInfoOffAddr_EvtCfgPara_Crc , (u8 *)&Trim.Crc, 2);
    }
    else if (pOadAys->AtrIndex == 0x0B)   //上报标识
    {
        if (pOadAys->elementIndex != 0)
        {
            return DATA_ACCESS_RESULT_OTH;
        }

        if ((*pSrc++) != DTYPE_ENUM)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if (*pSrc & 0xFC) //只允许设置bit0,bit1  发生及结束上报有效
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        Offset = item / 8;
        i = item % 8;
        //-----------------------
        if ((*pSrc & 0x01) == 0x01) //发生上报
        {
            EvtRptData.Para.RptFlagHappen[Offset] |= 1 << i;
        }
        else
        {
            EvtRptData.Para.RptFlagHappen[Offset] &= ~(1 << i);
        }

        if ((*pSrc & 0x02) == 0x02) //结束上报
        {
            EvtRptData.Para.RptFlagEnd[Offset] |= 1 << i;
        }
        else
        {
            EvtRptData.Para.RptFlagEnd[Offset] &= ~(1 << i);
        }

        len = FileItemInfoLen_EvtReport_RptFlagHappen + FileItemInfoLen_EvtReport_RptFlagEnd;
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptFlagHappen, &EvtRptData.Para.RptFlagHappen[0], len);

        fnCrc_Check(0, &EvtRptData.Para.AtiveAllow, sizeof(sEvtRptPara_TypeDef) - 2, (u8 *)&EvtRptData.Para.Crc);
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_Crc, (u8 *)&EvtRptData.Para.Crc, FileItemInfoLen_EvtReport_Crc);

        pSrc++;
    }
    else if (pOadAys->AtrIndex == 0x0F)   //上报方式，跟随上报，主动上报
    {
        if (pOadAys->elementIndex != 0)
        {
            return DATA_ACCESS_RESULT_OTH;
        }

        if ((*pSrc++) != DTYPE_ENUM)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Offset = item / 8;
        i = item % 8;
        //-----------------------

        if (*pSrc == 0x00)
        {
            EvtRptData.Para.RptMode[Offset] &= ~(1 << i);
        }
        else if (*pSrc == 0x01)
        {
            EvtRptData.Para.RptMode[Offset] |= 1 << i;
        }
        else
        {
            return DATA_ACCESS_RESULT_OTH;
        }

        len = FileItemInfoLen_EvtReport_RptMode;
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptMode, &EvtRptData.Para.RptMode[0], len);

        fnCrc_Check(0, &EvtRptData.Para.AtiveAllow, sizeof(sEvtRptPara_TypeDef) - 2, (u8 *)&EvtRptData.Para.Crc);
        fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_Crc, (u8 *)&EvtRptData.Para.Crc, FileItemInfoLen_EvtReport_Crc);

        pSrc++;
    }
    else
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnSet_FrzPara
** Descriptions:
** input parameters:  OAD:OAD
** output parameters:
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnSet_FrzPara(u32  OAD, u8  *pSrc, u8  *pParBuf)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    sFrzCtxList_TypeDef  tmplist, tmplist_old;
    OAD_Analyse_TypeDef  *tempOadAys;
    u16 OIA_B = (OAD >> 16 & 0xFFFF), recordlen ;
    //  u8  Offset=0, len=0;
    u32 totallen ;
    u8 i, num, item = FileItemInfoNum_Frz_MAX, line_item, j;
    sFrzMinLinePara_TypeDef tempFrzMinLine[MAX_FRZMIN_LINE];

    sDl698AL_ObjInfo_TypeDef  pObj;

    //--------仅支持厂内模式下修改------------
    if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable != 1)
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    item = fnGet_FrzItem(OIA_B);
    if (item >= FileItemInfoNum_Frz_MAX)
    {
        return DATA_ACCESS_RESULT_OTH;
    }

    if ((pOadAys->AtrIndex != 3) || (pOadAys->elementIndex != 0))
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    //设置关联对象属性表

    if ((*pSrc++) != DTYPE_ARRAY)
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    num = *pSrc++;

    Std_Memset(pParBuf, 0x00, FileItemInfo_FrzCtxlist[item].Len);

    *pParBuf = num;  //关联对象属性表个数
    tmplist_old.len = 0;
    Std_Memcpy((u8 *)&recordlen, (u8 *)&Frz_StdRecList.reclen, 2);    //标准事件记录单元空间长度

    if (item == FileItemInfoNum_Frz_MinFrz)
    {
        for (j = 0; j < MAX_FRZMIN_LINE; j++)
        {
            Std_Memset((u8 *)&tempFrzMinLine[j], 0x00, sizeof(sFrzMinLinePara_TypeDef));
        }
    }

    for (i = 0; i < num; i++)
    {
        if ((*pSrc++) != DTYPE_STRUCTURE)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        if ((*pSrc++) != 3) //3//个结构体
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_UINT16)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_MemRvs((u8 *)&tmplist.Cycle, pSrc, 2);  //周期
        pSrc += 2;

        if ((*pSrc++) != DTYPE_OAD)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_MemRvs((u8 *)&tmplist.OAD, pSrc, 4);        //OAD
        pObj.oad_omd = tmplist.OAD;
        pObj.oi = (u16)(pObj.oad_omd >> 16);
        if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        pSrc += 4;

        if ((*pSrc++) != DTYPE_UINT32)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_MemRvs((u8 *)&tmplist.Depth, pSrc, 4);  //深度
        pSrc += 4;

        if (i)   //第二个OAD开始比较存储周期及深度
        {
            if (item != FileItemInfoNum_Frz_MinFrz) //除分钟冻结外，只支持一条曲线，存储周期和深度必须一致
            {
                if ((tmplist.Cycle != tmplist_old.Cycle) || (tmplist.Depth != tmplist_old.Depth))
                {
                    return DATA_ACCESS_RESULT_DENY;
                }
            }
            else
            {
                tempOadAys = (OAD_Analyse_TypeDef *)&tmplist.OAD;
                line_item = tempOadAys->AtrFeature;
                if (tempFrzMinLine[line_item].OADnum)
                {
                    if ((tmplist.Cycle != tempFrzMinLine[line_item].Cycle) || (tmplist.Depth != tempFrzMinLine[line_item].Depth))
                    {
                        return DATA_ACCESS_RESULT_DENY;
                    }
                }
                else
                {
                    tempFrzMinLine[line_item].Cycle = tmplist.Cycle;
                    tempFrzMinLine[line_item].Depth = tmplist.Depth;
                }
            }
        }
        else  //第1个OAD
        {
            if (item != FileItemInfoNum_Frz_MinFrz)
            {
                tmplist_old.Cycle = tmplist.Cycle ;
                tmplist_old.Depth = tmplist.Depth;
            }
            else
            {
                tempOadAys = (OAD_Analyse_TypeDef *)&tmplist.OAD;
                line_item = tempOadAys->AtrFeature;
                tempFrzMinLine[line_item].Cycle = tmplist.Cycle;
                tempFrzMinLine[line_item].Depth = tmplist.Depth;
            }
        }

        tmplist.OffPos = recordlen;  //本字节的偏移 = 未累计前事件记录长度

        tmplist.len = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF), pParBuf + 1024);

        //--------判每条事件记录长度----------------
        recordlen = tmplist.len + tmplist.OffPos;
        if (item == FileItemInfoNum_Frz_MinFrz) //分钟冻结特殊处理，分钟冻结需要支持多条曲线
        {
            totallen = 0;
            tempFrzMinLine[line_item].RecLen = recordlen;
            tempFrzMinLine[line_item].LineRecLen = (u32)(tempFrzMinLine[line_item].RecLen * tempFrzMinLine[line_item].Depth);
            for (j = 0; j < MAX_FRZMIN_LINE; j++)
            {
                totallen += tempFrzMinLine[j].LineRecLen;

                if (j == 0)
                {
                    tempFrzMinLine[j].LineOffAdder = 0;
                }
                else
                {
                    tempFrzMinLine[j].LineOffAdder = (u32)(tempFrzMinLine[j - 1].LineRecLen + tempFrzMinLine[j - 1].LineOffAdder);
                }
            }

            if (totallen > FileItemInfo_FrzRecord[item].Len)
            {
                return DATA_ACCESS_RESULT_ACC;
            }

            tempFrzMinLine[line_item].OADnum ++;
        }
        else
        {
            totallen = (u32)(recordlen * tmplist.Depth);

            if (totallen > FileItemInfo_FrzRecord[item].Len)
            {
                return DATA_ACCESS_RESULT_ACC;
            }
        }
        Std_Memcpy((u8 *)&tmplist_old, (u8 *)&tmplist, sizeof(sFrzCtxList_TypeDef));

        Std_Memcpy(pParBuf + i * sizeof(sFrzCtxList_TypeDef) + 3, (u8 *)&tmplist, sizeof(sFrzCtxList_TypeDef));
    }
    Std_Memcpy(pParBuf + 1, (u8 *)&recordlen, 2);

    //-------关联对象属性表总个数(1byte)+根据关联对象属性表计算每条事件记录长度(2byte)+关联对象属性表-----------------------
    fnFile_Write(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[item].OffAddr, pParBuf, FileItemInfo_FrzCtxlist[item].Len);

    //设置关联对象属性表对应事件记录需清零，清事件记录头
    Std_Memset(pParBuf, 0x00, FileItemInfo_FrzRcdHead[item].Len);
    fnFile_Write(FileId_FrzRcdHead, FileItemInfo_FrzRcdHead[item].OffAddr, pParBuf, FileItemInfo_FrzRcdHead[item].Len);

    if (item == FileItemInfoNum_Frz_MinFrz) //分钟冻结特殊处理，分钟冻结需要支持多条曲线
    {
        for (j = 0; j < MAX_FRZMIN_LINE; j++)
        {
            Std_Memset(pParBuf, 0x00, FileItemInfo_FrzMinLineHead[j].Len);     //清命令头 sFrzRcdHead_TypeDef
            Std_Memcpy(pParBuf, (u8 *)&tempFrzMinLine[j], sizeof(sFrzMinLinePara_TypeDef));
            fnFile_Write(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[j].OffAddr, pParBuf, FileItemInfo_FrzMinLineHead[j].Len);
            RFrzMinLine.Cycle[j] = tempFrzMinLine[j].Cycle;
        }
        fnCrc_Check(0, (u8 *)&RFrzMinLine.Cycle[0], sizeof(sFrzMinCycle_TypeDef) -2, (u8 *)&RFrzMinLine.Crc);
    }

    //if(item == FileItemInfoNum_Frz_DayFrz)
    //  fnWrite_PowDn_FrzDayTime();

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnSet_Control
** Descriptions:
** input parameters:  OAD:OAD
** output parameters:
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnSet_Control(u32  OAD, u8  *pSrc, u8  *pParBuf)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;

    u16 OIA_B = (OAD >> 16 & 0xFFFF);

    if (OIA_B == 0x8000) //远程控制
    {
        if (pOadAys->AtrIndex == 2)
        {
            if (pOadAys->elementIndex == 0)
            {
                if ((*pSrc++) != DTYPE_STRUCTURE)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }
                if ((*pSrc++) != 2) //2//个结构体
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                if ((*pSrc++) != DTYPE_UINT32)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                Std_MemRvs(pParBuf, pSrc, 4);   //
                pSrc += 4;

                if ((*pSrc++) != DTYPE_UINT16)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                Std_MemRvs(pParBuf + 4, pSrc, 2);   //
                pSrc += 2;

                fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_GataSafeCur, pParBuf, 6);
                fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_GataSafeCur, (u8 *)&Output.PriPara.GataSafeCur, 4);
                fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_tSafeGata, (u8 *)&Output.PriPara.tSafeGata, 2);
                fnCrc_Check(0, (u8 *)&Output.PriPara, sizeof(Output.PriPara) - 2, (u8 *)&Output.PriPara.Crc);
            }
            else if (pOadAys->elementIndex == 1)
            {
                if ((*pSrc++) != DTYPE_UINT32)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                Std_MemRvs(pParBuf, pSrc, 4);   //
                pSrc += 4;
                fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_GataSafeCur, pParBuf, 4);
                fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_GataSafeCur, (u8 *)&Output.PriPara.GataSafeCur, 4);
                fnCrc_Check(0, (u8 *)&Output.PriPara, sizeof(Output.PriPara) - 2, (u8 *)&Output.PriPara.Crc);
            }
            else if (pOadAys->elementIndex == 2)
            {
                if ((*pSrc++) != DTYPE_UINT16)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                Std_MemRvs(pParBuf, pSrc, 2);   //
                pSrc += 2;
                fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_tSafeGata, pParBuf, 2);
                fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_tSafeGata, (u8 *)&Output.PriPara.tSafeGata, 2);
                fnCrc_Check(0, (u8 *)&Output.PriPara, sizeof(Output.PriPara) - 2, (u8 *)&Output.PriPara.Crc);
            }
            else
            {
                return DATA_ACCESS_RESULT_UNAVA;
            }
        }
        else
        {
            return DATA_ACCESS_RESULT_UNAVA;
        }
    }
    else
    {
        return DATA_ACCESS_RESULT_UNAVA;
    }

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:       fnGet_DispData
** Descriptions:        根据OAD1，OAD2 获取数据内容(主要用于显示)
** input parameters:    OAD1只能是ROAD，OAD1=0时表示OAD1无效，OAD2可以任何合法数据
** output parameters:   pBuf 返回数据内容 type + data(hex)
** Returned value:
*********************************************************************************************************/
void fnGet_DispData(sDispItem_TypeDef  *DispItem, u8 *pBuf, u16 *Len)
{
    u8 temp[10];
    u8 res = DATA_ACCESS_RESULT_OTH ;
    u32 OAD1;
    u8  blockRsp = false;
    //OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD1;
    *Len = 0;
    u8  *pRecordBuf;

    if (DispItem->CSD)
    {
        //---------把OAD1,OAD2封装成使用方法9读取上几次记录---------------
        pRecordBuf = (u8 *)fnBufTemp_Alloc(BUFTEMP_MAXLEN);
        if (pRecordBuf == NULL)
        {
            return ;
        }
        Std_Memset(pRecordBuf, 0, BUFTEMP_MAXLEN);

        temp[0] = 9;  //方法9
        temp[1] = DispItem->M_Element;  //第几次

        temp[2] = 1;  //列
        temp[3] = 0x00;  //OAD
        Std_MemRvs(&temp[4], &DispItem->Element, 4);

        OAD1 = Std_Lsb32DataGet(&DispItem->M_Element);
        OAD1 &= 0xFFFFFF00;

        if ((DispItem->M_OIA >> 4) == OIA1_EVENT)
        {
            res = fnGet_EvtRecord(OAD1, temp, pRecordBuf, pBuf, Len, &blockRsp, FALSE);
        }

        //else if((DispItem->M_OIA>>4) == OIA1_FREEZE)
        //  res = fnGet_FrzRecord(OAD1, temp, pRecordBuf, pBuf, Len, &blockRsp , FALSE);

        fnBufTemp_Free(pRecordBuf);  //释放

        if (*Len < 9) // 无有效数据,无事件记录产生时
        {
            *pBuf = DTYPE_NONE;
            Std_Memset(pBuf + 1, 0x00, 8);
        }
        else
        {
            Std_Memcpy(pBuf, pBuf + 8, *Len);    //前移8byte,消除记录型数据通讯应答格式影响
        }
    }
    else
    {
        pRecordBuf = (u8 *)fnBufTemp_Alloc(1024);
        if (pRecordBuf == NULL)
        {
            return ;
        }

        Std_Memset(pRecordBuf, 0, 1024);

        OAD1 = Std_Lsb32DataGet(&DispItem->M_Element);
        res = fnGet_Normal(OAD1, pRecordBuf, pBuf, Len, &blockRsp);

        fnBufTemp_Free(pRecordBuf);  //释放

        if (res != DATA_ACCESS_RESULT_SUC) //应答数据类型为NONE
        {
            *pBuf = DTYPE_NONE;
            Std_Memset(pBuf + 1, 0x00, 8);
        }
    }
}

/*********************************************************************
* @fn      fnDl698Act_GataOp
*
* @brief   继电器操作
*
* @param
*
* @return  操作结果
*/
u8 fnAct_GataOp(
    u32  OMD,        //OMD
    u8  *pSrc,    //parameter buffer
    u16 *pSrcLen,     //parameter length ，已处理的参数数据长度
    u8  *pRetBuf,    //return result buffer
    u16 *retLen,     //return result buffer length
    u16 *RtExeFlag   // return Gata Flag
)
{
    OMD_Analyse_TypeDef *pOmdAys = (OMD_Analyse_TypeDef*)&OMD;
    u32 ActOAD;
    //  u8  i;
    eDL645B_ContErrInfo_TypeDef err = DL645B_ContErrInfo_OK;
    eDL645B_ContExeInfo_TypeDef ExeFlag = DL645B_ContExeInfo_NoData;
    u8  tDelay, GataOffStat, GataCmd_temp;
    u16 tGataOff;
    u8 temp[4];
    //  u8 ret = DATA_ACCESS_RESULT_UNDEF;

    *pSrcLen = fnDl698AL_GetData_Len(1, 0, pSrc);
    //-----------------------
    if (pOmdAys->OI == 0x8000) // 遥控
    {
        if (pOmdAys->ActFlag == 127)
        {
            //告警
            if (pOmdAys->ActMeth == 0)
            {
                if (*pSrc++ != DTYPE_NONE)
                {
                    err = DL645B_ContErrInfo_PswErr;
                }
                if (err == DL645B_ContErrInfo_OK)
                {
                    Bkgrd.PubData.MoneySta.RemoteAlarm = 1;
                    Bkgrd.PubData.MtSta.MtSta3.StaBit.PreGateOff = 1;

                    ExeFlag = DL645B_ContExeInfo_Alarm;
                }
            }
            else
            {
                err = DL645B_ContErrInfo_PswErr;
            }
        }
        else if (pOmdAys->ActFlag == 128)
        {
            //解除告警
            if (pOmdAys->ActMeth == 0)
            {
                if (*pSrc++ != DTYPE_NONE)
                {
                    err = DL645B_ContErrInfo_PswErr;
                }

                if (err == DL645B_ContErrInfo_OK)
                {
                    Bkgrd.PubData.MoneySta.RemoteAlarm = 0;
                    #if(METERTYPE == 2)
                    if (!Bkgrd.PubData.MoneySta.LowAlarm1)
                    {
                        Bkgrd.PubData.MtSta.MtSta3.StaBit.PreGateOff = 0;
                    }
                    #else
                    Bkgrd.PubData.MtSta.MtSta3.StaBit.PreGateOff = 0;
                    #endif

                    ExeFlag = DL645B_ContExeInfo_AlarmOff;
                }
            }
            else
            {
                err = DL645B_ContErrInfo_PswErr;
            }
        }
        else if (pOmdAys->ActFlag == 129)
        {
            //拉闸
            if (pOmdAys->ActMeth == 0)
            {
                if (*pSrc++ != DTYPE_ARRAY)
                {
                    err = DL645B_ContErrInfo_PswErr;
                }

                if (*pSrc++ != 1)
                {
                    err = DL645B_ContErrInfo_PswErr;
                }

                if (*pSrc++ != DTYPE_STRUCTURE)
                {
                    err = DL645B_ContErrInfo_PswErr;
                }

                if (*pSrc++ != 4)
                {
                    err = DL645B_ContErrInfo_PswErr;
                }

                if (*pSrc++ != DTYPE_OAD)
                {
                    err = DL645B_ContErrInfo_PswErr;
                }

                ActOAD = Std_Msb32DataGet(pSrc);
                pSrc += 4;
                if ((ActOAD & 0xFFFFFF00) != 0xf2050200)
                {
                    err = DL645B_ContErrInfo_PswErr;
                }

                if (*pSrc++ != DTYPE_UINT8)
                {
                    err = DL645B_ContErrInfo_PswErr;
                }
                else
                {
                    tDelay = *pSrc++;    //拉闸延时时间
                }

                if (*pSrc++ != DTYPE_UINT16)
                {
                    err = DL645B_ContErrInfo_PswErr;
                }
                else
                {
                    tGataOff = Std_Msb16DataGet(pSrc);  //限电时间，跳闸自动恢复时有效
                    pSrc += 2;
                }

                if ((Bkgrd.PubData.MoneySta.RemoteKeepEg) && (err == DL645B_ContErrInfo_OK))  //保电
                {
                    err = DL645B_ContErrInfo_GataOffErr;
                }

                if (err == DL645B_ContErrInfo_OK)
                {
                    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &GataOffStat, 1);   //原始状态

                    if (tGataOff == 0)   //限电时间为0，跳闸
                    {
                        //if(Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus == 0)  //继电器命令状态是通
                        {
                            if ((GataOffStat == 0x1d) || (GataOffStat == 0x1e))
                            {
                                // 跳闸恢复命令已跳闸
                                Output.PubData.GataOffResumeTime = 0;
                                ExeFlag = DL645B_ContExeInfo_DirectOff;
                            }
                            else
                            {
                                Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 1;

                                if (tDelay)
                                {
                                    Output.PubData.GateOffRemainTime = tDelay * 60;
                                    ExeFlag = DL645B_ContExeInfo_DelayOff;
                                }
                                else
                                {
                                    if (Output.PubData.SafeCurFlag)
                                    {
                                        ExeFlag = DL645B_ContExeInfo_ContrOff;
                                    }
                                    else
                                    {
                                        ExeFlag = DL645B_ContExeInfo_DirectOff;
                                    }
                                }
                                if (Output.PubData.SafeCurFlag)
                                {
                                    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_tSafeGata, &temp[0], 2);
                                    Output.PubData.GateOffRemainTime = (u32)Std_Lsb16DataGet(&temp[0]) * 60;
                                }
                            }

                            GataOffStat = 0x9a;  //跳闸
                            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &GataOffStat, 1);   //跳闸状态保存
                        }
                        /*
                        else
                        {
                            if((i==0x1d) || (i == 0x1e))
                              {
                                // 跳闸恢复命令已跳闸
                                   Output.PubData.GataOffResumeTime = 0;
                                    ExeFlag = DL645B_ContExeInfo_DirectOff;
                               }
                               else
                                ExeFlag = DL645B_ContExeInfo_DirectOff;

                            ICEsamComm.Ic_Comm_RxBuf[0] |=0x80;
                            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat , &ICEsamComm.Ic_Comm_RxBuf[0] , 1 );//跳闸状态保存
                        }
                        */
                    }
                    else
                    {
                        //跳闸后自恢复
                        if (*pSrc++ != DTYPE_BOOLEAN)
                        {
                            err = DL645B_ContErrInfo_PswErr;
                        }

                        GataCmd_temp = *pSrc++;

                        if (GataCmd_temp == 0)
                        {
                            GataOffStat = 0x9e;
                        }
                        else if (GataCmd_temp == 1)
                        {
                            GataOffStat = 0x9d;
                        }
                        else
                        {
                            err = DL645B_ContErrInfo_PswErr;
                        }

                        if (GataOffStat == 0x9a)
                        {
                            if (Output.PubData.GateOffRemainTime) //拉闸延时过程中不执行跳闸自恢复功能
                            {
                                err = DL645B_ContErrInfo_PswErr;
                            }
                        }

                        if (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus == 1) //继电器拉闸情况下，不执行自恢复命令
                        {
                            err = DL645B_ContErrInfo_ResumeExeFail;
                        }

                        if (err == DL645B_ContErrInfo_OK)
                        {
                            Output.PubData.GataOffResumeTime = tGataOff * 60;
                            if (Output.PubData.SafeCurFlag)
                            {
                                fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_tSafeGata, &temp[0], 2);
                                Output.PubData.GateOffRemainTime = (u32)Std_Lsb16DataGet(&temp[0]) * 60;
                                ExeFlag = DL645B_ContExeInfo_ContrOff;
                            }
                            else
                            {
                                ExeFlag = DL645B_ContExeInfo_ResumeOff;
                            }

                            Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 1;
                            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &GataOffStat, 1); //跳闸状态保存
                        }
                    }
                }
            }
        }
        else if ((pOmdAys->ActFlag == 130) || (pOmdAys->ActFlag == 131)) //合闸及明文合闸
        {
            // 合闸
            if (pOmdAys->ActMeth == 0)
            {
                if (*pSrc++ != DTYPE_ARRAY)
                {
                    err = DL645B_ContErrInfo_PswErr;
                }

                if (*pSrc++ != 1)
                {
                    err = DL645B_ContErrInfo_PswErr;
                }

                if (pOmdAys->ActFlag == 130)
                {
                    if (*pSrc++ != DTYPE_STRUCTURE)
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }

                    if (*pSrc++ != 2)
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }

                    if (*pSrc++ != DTYPE_OAD)
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }

                    ActOAD = Std_Msb32DataGet(pSrc);
                    pSrc += 4;
                    if ((ActOAD & 0xFFFFFF00) != 0xf2050200)
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }

                    if (*pSrc++ != DTYPE_ENUM)
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }

                    GataCmd_temp = *pSrc++;
                }
                else   //明文合闸，需判密码
                {
                    if (*pSrc++ != DTYPE_STRUCTURE)
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }

                    if (*pSrc++ != 3)
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }

                    if (*pSrc++ != DTYPE_OAD)
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }

                    ActOAD = Std_Msb32DataGet(pSrc);
                    pSrc += 4;
                    if ((ActOAD & 0xFFFFFF00) != 0xf2050200)
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }

                    if (*pSrc++ != DTYPE_ENUM)
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }

                    GataCmd_temp = *pSrc++;

                    if (*pSrc++ != DTYPE_STRING)
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }

                    if (*pSrc++ != 8) //密码 visible-string 长度
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }
                    //-----判密码-------------
                    Std_AsciiStrToHexStr(&temp[0], pSrc, 8);

                    if (fnSecret_Verify(0, 0, &temp[0]) == ERROR)  //698固定用00级密码
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }
                }

                if (err == DL645B_ContErrInfo_OK)
                {
                    if (GataCmd_temp)
                    {
                        // 直接合闸
                        //if(Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus)
                        {
                            if ((GataOffStat == 0x9a) && (Output.PubData.GateOffRemainTime))    //在拉闸允许状态
                            {
                                Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
                                GataOffStat = 0x1C;
                                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &GataOffStat, 1);  //合闸允许状态保存
                            }
                            else
                            {
                                Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
                                //Bkgrd.PubData.MtSta.MtSta3.StaBit.PreGateOff = 0;
                                GataOffStat = 0x9c;
                                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &GataOffStat, 1);   //合闸允许状态保存
                                Key.Press |= KEY_Relay_Ctrl;
                            }
                            ExeFlag = DL645B_ContExeInfo_DirectOn;
                        }
                        /*
                         else
                         {
                            if(GataOffStat == 0x9b) Key.Press |= KEY_Relay_Ctrl;
                            ExeFlag = DL645B_ContExeInfo_DirectOn;
                         }
                         */
                    }
                    else
                    {
                        // 允许合闸
                        if ((GataOffStat != 0x9b) && (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus))
                        {
                            if ((Output.PubData.GateOffRemainTime) && (GataOffStat == 0x9a))
                            {
                                Output.PubData.GateOffRemainTime = 0;
                                Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
                                GataOffStat = 0x1b;
                                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &GataOffStat, 1);   //状态保存
                            }
                            else
                            {
                                Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
                                GataOffStat = 0x9b;
                                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &GataOffStat, 1);   //合闸允许状态保存
                            }
                        }
                        ExeFlag = DL645B_ContExeInfo_AllowOn;
                    }
                }
            }
            else
            {
                err = DL645B_ContErrInfo_PswErr;
            }
        }
        else
        {
            err = DL645B_ContErrInfo_PswErr;
        }
    }
    else if (pOmdAys->OI == 0x8001) // 保电
    {
        if (pOmdAys->ActFlag == 127)
        {
            // 保电
            //ret = DATA_ACCESS_RESULT_SUC;
            fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &GataOffStat, 1);   //原始状态
            Bkgrd.PubData.MoneySta.RemoteKeepEg = 1;
            Bkgrd.PubData.MtSta.MtSta3.StaBit.KeepEg = 1;
            Output.PubData.GataOffResumeTime = 0;
            ExeFlag = DL645B_ContExeInfo_KeepEg;
            if ((Output.PubData.GateOffRemainTime) && (GataOffStat == 0x9a))
            {
                Output.PubData.GateOffRemainTime = 0;
                Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
                GataOffStat = 0x1b;
                fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &GataOffStat, 1);   //状态保存
            }
        }
        else if (pOmdAys->ActFlag == 128)
        {
            // 保电解除
            //ret = DATA_ACCESS_RESULT_SUC;
            Bkgrd.PubData.MoneySta.RemoteKeepEg = 0;
            Bkgrd.PubData.MtSta.MtSta3.StaBit.KeepEg = 0;
            if (Bkgrd.PubData.MoneySta.Overdraft)
            {
                Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 1;
            }
            ExeFlag = DL645B_ContExeInfo_KeepEgOff;
        }
        else
        {
            err = DL645B_ContErrInfo_PswErr;
        }
    }

    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_Gata_Do, &ExeFlag, FileItemInfoLen_HighState_Gata_Do);
    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_Gata_Err, &err, FileItemInfoLen_HighState_Gata_Err);

    if (err == DL645B_ContErrInfo_OK)
    {
        return DATA_ACCESS_RESULT_SUC;
    }
    else if (err == DL645B_ContErrInfo_RemoteClose)
    {
        return DATA_ACCESS_RESULT_SUSPD;
    }
    else if (err == DL645B_ContErrInfo_RemoteFail)
    {
        return DATA_ACCESS_RESULT_SECFAIL;
    }
    else
    {
        return DATA_ACCESS_RESULT_OTH;
    }
}

/*********************************************************************
* @fn      fnDl698Act_EsamOp
*
* @brief
*
* @param
*
* @return
*/
u8 IrAutState = 0;;

u8 fnAct_EsamOp(
    u32  OMD,        //OMD
    u8  *pParBuf,    //parameter buffer
    u16 *parLen,     //parameter length ，已处理的参数数据长度
    u8  *pRetBuf,    //return result buffer
    u16 *retLen,      //return result buffer length
    u8  *pEsamBuf
)
{
    OMD_Analyse_TypeDef *pOmdAys = (OMD_Analyse_TypeDef*)&OMD;

    sDl698_EsamParam_TypeDef EsamParam = {0};
    u16 esamDatalen = 0;
    u16 enc_size = 0, enc_size2 = 0;
    u8 ret = DATA_ACCESS_RESULT_ESAMFAIL;
    u32 temp32;
    u16 TxLen = 0;
    u16 TagLen;
    u16 data_len;
    u8  *pSrcBuf;

    u8  eSamBuf[20];
    u16 Esamlen;

    *parLen = fnDl698AL_GetData_Len(1, 0, pParBuf);
    switch (pOmdAys->ActFlag)
    {
        case ESAM_RESET://复位
        {
            if (*pParBuf++ == DTYPE_INT8)
            {
                EsamParam.op = *pParBuf++;
                *parLen = 2;
                if (fnEsamOp_GetSendToEsamFrame(pOmdAys->ActFlag, (u8 *)pEsamBuf, &esamDatalen, &EsamParam) == SUCCESS)
                {
                    //调用对应的ESAM接口
                    if (fnEsamOp_Reset(pEsamBuf) == SUCCESS)
                    {
                        ret = DATA_ACCESS_RESULT_SUC;
                    }
                }
            }
            break;
        }
        //case ESAM_OPTION://执行
        //{
        //  break;
        //}
        case ESAM_DATA_READ://ESAM数据回抄
        {
            ret = DATA_ACCESS_RESULT_DENY;
            if (*pParBuf++ == DTYPE_SID)
            {
                STREAM_TO_UINT32(EsamParam.SID.flag, pParBuf);

                enc_size = fnDL698AL_asn1_get_ObjCnt(&EsamParam.SID.datalen, pParBuf);
                pParBuf += enc_size;
                EsamParam.SID.pData = pParBuf;
                pParBuf += EsamParam.SID.datalen;

                *parLen = 5 + EsamParam.SID.datalen + enc_size;
                if (fnEsamOp_GetSendToEsamFrame(pOmdAys->ActFlag, (u8 *)pEsamBuf, &esamDatalen, &EsamParam) == SUCCESS)
                {
                    if (fnReadMeter_Esam(&ICEsamComm.Ic_Comm_RxBuf[4]) == SUCCESS)
                    {
                        fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[4], 6);
                        fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_MeterNo, &ICEsamComm.Ic_Comm_RxBuf[10], 0x06);
                        if (fnDFCompData(&ICEsamComm.Ic_Comm_RxBuf[4], &ICEsamComm.Ic_Comm_RxBuf[10], 6) != 0)
                        {
                            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_MeterNo, &ICEsamComm.Ic_Comm_RxBuf[4], 0x06);
                        }
                    }
                    //调用对应的ESAM接口
                    if (fnEsamOp_Tx_Esam(pParBuf, pEsamBuf, &esamDatalen) == SUCCESS)
                    {
                        *pRetBuf++ = 0;
                        *pRetBuf++ = 1;
                        *retLen  += 2;
                        Std_MemRvsSelf(pParBuf, esamDatalen);
                        pRetBuf += fnDl698_asn1_build_Type(pRetBuf, retLen, pParBuf, &esamDatalen, DTYPE_OCT_STR);
                        ret = DATA_ACCESS_RESULT_SUC;
                    }
                }
            }
            break;
        }
        case ESAM_DATA_UPDATE://数据更新
        {
            if ((*pParBuf++ == DTYPE_STRUCTURE) && (*pParBuf++ == 2)
                && (*pParBuf++ == DTYPE_OCT_STR))
            {
                if (*pParBuf & 0x80)
                {
                    if (((*pParBuf) & 0x7f) > 0x02)
                    {
                        return DATA_ACCESS_RESULT_ESAMLC;
                    }
                    *pParBuf++;
                    TxLen = *pParBuf << 8 ;
                    *pParBuf++;
                    TxLen += (*pParBuf++);
                }
                else
                {
                    TxLen = *pParBuf++;
                }
                pSrcBuf = pParBuf;
                pParBuf += TxLen;
                data_len = TxLen;

                if (*pParBuf++ == DTYPE_SID_MAC)
                {
                    Std_Memcpy(pEsamBuf, pParBuf, DL698AL_SIDCHR_LEN);
                    TxLen = DL698AL_SIDCHR_LEN;
                    pParBuf += DL698AL_SIDCHR_LEN;

                    TagLen = *pParBuf++;
                    if (TagLen != 0)
                    {
                        //附加数据 02LLXXXX
                        Std_Memcpy(pEsamBuf + TxLen, pParBuf, TagLen);
                        TxLen += TagLen;
                        pParBuf += TagLen;
                    }
                    else
                    {
                        pParBuf += 1;
                    }

                    temp32 = Std_Msb32DataGet(pSrcBuf);  //更新OAD
                    if (temp32 == 0x40020200) //更新表号
                    {
                        //拷贝数据到ESAM TX BUFFER
                        Std_Memcpy(pEsamBuf + TxLen, pSrcBuf, data_len);
                        TxLen += data_len;
                    }
                    else     //更新除表号以外的参数需删除OAD+len  5个字节后再组帧发给芯片
                    {
                        data_len -= 5;
                        Std_Memcpy(pEsamBuf + TxLen, pSrcBuf + 5, data_len);
                        TxLen += data_len;
                    }
                    TagLen = *pParBuf++;
                    if (TagLen != 0)
                    {
                        Std_Memcpy(pEsamBuf + TxLen, pParBuf, TagLen);
                        TxLen += TagLen;
                        pParBuf += TagLen;
                    }
                    else
                    {
                        pParBuf += 1;
                    }
                    if (fnEsamOp_Tx_Esam(&ICEsamComm.Ic_Comm_RxBuf[6], pEsamBuf, &data_len) != ERROR) //计算密文数据及MAC
                    {
                        ret = DATA_ACCESS_RESULT_SUC;
                        //--------更新数据----------------
                        if (temp32 == 0x40020200) //表号
                        {
                            fnUpdateMeterNo();
                        }

                        *pEsamBuf = DTYPE_OAD;
                        Std_Lsb32DataSet(pEsamBuf + 1, temp32);
                        //                          fnEvent_Operation(FileItemInfoNum_Evt_Prg , EVTSTART, pEsamBuf ); //编程事件记录存数据类型(1byte)+标识(4byte)
                    }
                    else
                    {
                        ret = DATA_ACCESS_RESULT_ESAMFAIL;
                    }
                }
            }
            break;
        }
        case ESAM_KEY_UPDATE://密钥更新
        {
            if ((*pParBuf++ == DTYPE_STRUCTURE) && (*pParBuf++ == 2)
                && (*pParBuf++ == DTYPE_OCT_STR))
            {
                if (*pParBuf & 0x80)
                {
                    if (((*pParBuf) & 0x7f) > 0x02)
                    {
                        return DATA_ACCESS_RESULT_ESAMLC;
                    }
                    *pParBuf++;
                    TxLen = *pParBuf << 8 ;
                    *pParBuf++;
                    TxLen += (*pParBuf++);
                }
                else
                {
                    TxLen = *pParBuf++;
                }
                pSrcBuf = pParBuf;
                pParBuf += TxLen;
                data_len = TxLen;

                if (*pParBuf++ == DTYPE_SID_MAC)
                {
                    Std_Memcpy(pEsamBuf, pParBuf, DL698AL_SIDCHR_LEN);
                    TxLen = DL698AL_SIDCHR_LEN;
                    pParBuf += DL698AL_SIDCHR_LEN;

                    TagLen = *pParBuf++;
                    if (TagLen != 0)
                    {
                        //附加数据 02LLXXXX
                        Std_Memcpy(pEsamBuf + TxLen, pParBuf, TagLen);
                        TxLen += TagLen;
                        pParBuf += TagLen;
                    }
                    else
                    {
                        pParBuf += 1;
                    }

                    temp32 = Std_Msb32DataGet(pEsamBuf);  //SID
                    if (temp32 != 0x812E0000) //判断标识,密钥更新标识必须为812E0000
                    {
                        ret = DATA_ACCESS_RESULT_ESAMP1P2;
                    }
                    else
                    {
                        //拷贝数据到ESAM TX BUFFER
                        Std_Memcpy(pEsamBuf + TxLen, pSrcBuf, data_len);
                        TxLen += data_len;

                        TagLen = *pParBuf++;
                        if (TagLen != 0)
                        {
                            Std_Memcpy(pEsamBuf + TxLen, pParBuf, TagLen);
                            TxLen += TagLen;
                            pParBuf += TagLen;
                        }
                        else
                        {
                            pParBuf += 1;
                        }

                        if (fnEsamOp_Tx_Esam(&ICEsamComm.Ic_Comm_RxBuf[6], pEsamBuf, &data_len) != ERROR) //计算密文数据及MAC
                        {
                            ret = DATA_ACCESS_RESULT_SUC;

                            fnFile_Read(FileId_ParaCipherKey, FileItemInfoOffAddr_CipherKeyPara_CipherKeyFlag, pEsamBuf, FileItemInfoLen_CipherKeyPara_CipherKeyFlag);

                            //----------更新密钥状态--------------------
                            if (fnUpdatePswSta() == TRUE)
                            {
                                //---------密钥更新事件记录---------------
                                fnEvent_Operation(FileItemInfoNum_Evt_PrgSetPsw, EVTSTART, pEsamBuf);
                            }
                        }
                        else
                        {
                            ret = DATA_ACCESS_RESULT_ESAMFAIL;
                        }
                    }
                }
            }
            break;
        }
        case ESAM_NEGO_FAILE://协商失效
        {
            if (*pParBuf == DTYPE_NONE)
            {
                ret = DATA_ACCESS_RESULT_SUC;
                *retLen = 2;
                *pRetBuf++ = ret; //封装DAR
                *pRetBuf++ = 1;
                pRetBuf += fnDl698_asn1_build_Type(pRetBuf, retLen, &SysDatetimes.second, NULL, DTYPE_DATETIME_S);

                fnConnSizeDefault(Secret.Chan, Secret.CA);
                fnConnectDis_SecretClr();
                gActSessionDestroyed = 1;
            }
            /*
            else
            {
                ret = DATA_ACCESS_RESULT_TYPE;
                *retLen = 2;
                *pRetBuf++ = ret; //封装DAR
                *pRetBuf++ = 0;
            }
            */
            break;
        }
        #if(METERTYPE==2)
        case ESAM_PURSE_OPTION://钱包操作
        {
            if ((*pParBuf++ == DTYPE_STRUCTURE) && (*pParBuf++ == 6)
                && (*pParBuf++ == DTYPE_INT8))
            {
                EsamParam.op = *pParBuf++;
                if (*pParBuf++ == DTYPE_UINT32)
                {
                    STREAM_TO_UINT32(EsamParam.moneryPurse.money, pParBuf);
                    if (*pParBuf++ == DTYPE_UINT32)
                    {
                        STREAM_TO_UINT32(EsamParam.moneryPurse.times, pParBuf);
                        if (*pParBuf++ == DTYPE_OCT_STR)
                        {
                            enc_size = fnDL698AL_asn1_get_ObjCnt(&EsamParam.moneryPurse.pUserNumlen, pParBuf);
                            pParBuf += enc_size;
                            EsamParam.moneryPurse.pUserNum = pParBuf;
                            pParBuf += EsamParam.moneryPurse.pUserNumlen;
                            if (*pParBuf++ == DTYPE_SID)
                            {
                                STREAM_TO_UINT32(EsamParam.SID.flag, pParBuf);

                                enc_size2 = fnDL698AL_asn1_get_ObjCnt(&EsamParam.SID.datalen, pParBuf);
                                pParBuf += enc_size2;
                                EsamParam.SID.pData = pParBuf;
                                pParBuf += EsamParam.SID.datalen;

                                EsamParam.maclen = *pParBuf++;
                                EsamParam.pMac = pParBuf;
                                pParBuf += EsamParam.maclen;

                                enc_size3 = fnDL698AL_asn1_get_ObjCnt(&EsamParam.moneryPurse.pMeterNumlen, pParBuf);
                                pParBuf += enc_size3;
                                EsamParam.moneryPurse.pMeterNum = pParBuf;
                                pParBuf += EsamParam.moneryPurse.pMeterNumlen;

                                *parLen = EsamParam.moneryPurse.pUserNumlen + EsamParam.SID.datalen + EsamParam.maclen + EsamParam.moneryPurse.pMeterNumlen  + 21 + enc_size + enc_size2 + enc_size3;
                                if (fnEsamOp_GetSendToEsamFrame(pOmdAys->ActFlag, (u8 *)pEsamBuf, &esamDatalen, &EsamParam) == SUCCESS)
                                {
                                    //调用对应的ESAM接口
                                    ret = DATA_ACCESS_RESULT_SUC;
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
        #endif
        //case ESAM_CERTIFICATE_UPDATE://证书更新
        case ESAM_DATA_SET://设置参数:会话时效门限,终端地址,终端广播计数器,通过SID区别参数
        {
            if ((*pParBuf++ == DTYPE_STRUCTURE) && (*pParBuf++ == 2)
                && (*pParBuf++ == DTYPE_OCT_STR))
            {
                enc_size = fnDL698AL_asn1_get_ObjCnt(&EsamParam.len, pParBuf);
                pParBuf += enc_size;
                EsamParam.pOctString = pParBuf;
                pParBuf += EsamParam.len;
                if (*pParBuf++ == DTYPE_SID)
                {
                    STREAM_TO_UINT32(EsamParam.SID.flag, pParBuf);
                    {
                        enc_size2 = fnDL698AL_asn1_get_ObjCnt(&EsamParam.SID.datalen, pParBuf);
                        pParBuf += enc_size2;
                        EsamParam.SID.pData = pParBuf;
                        pParBuf += EsamParam.SID.datalen;
                        *parLen = EsamParam.len + EsamParam.SID.datalen + 8 + enc_size + enc_size2;
                        if (fnEsamOp_GetSendToEsamFrame(pOmdAys->ActFlag, (u8 *)pEsamBuf, &esamDatalen, &EsamParam) == SUCCESS)
                        {
                            //调用对应的ESAM接口
                            if (fnEsamOp_Tx_Esam(pParBuf, pEsamBuf, &esamDatalen) == SUCCESS)
                            {
                                if (pEsamBuf[2] == 7)
                                {
                                    fnUpdateAuthOn();
                                }
                                else if (pEsamBuf[2] == 1)
                                {
                                    fnReadDlyTime_Esam(&Secret.Master.tESAMDly, MASTER, 0);
                                }
                                else if (pEsamBuf[2] == 4)
                                {
                                    fnReadDlyTime_Esam(&Secret.Terminal.tESAMDly, TERMINAL, 0);
                                }

                                ret = DATA_ACCESS_RESULT_SUC;
                                *pEsamBuf = DTYPE_OMD;
                                Std_Lsb32DataSet(pEsamBuf + 1, OMD);
                                //                                  fnEvent_Operation(FileItemInfoNum_Evt_Prg , EVTSTART, pEsamBuf );

                                fnEsamOp_ReadEsam_Info(8, &eSamBuf[0], &Esamlen);
                                Secret.NeedIdentityAuth = eSamBuf[0];
                            }
                        }
                    }
                }
            }
            break;
        }
        #if(METERTYPE==2)
        case ESAM_PURSE_INIT://钱包初始化
        {
            if ((*pParBuf++ == DTYPE_STRUCTURE) && (*pParBuf++ == 2)
                && (*pParBuf++ == DTYPE_UINT32))
            {
                STREAM_TO_UINT32(EsamParam.moneryPurse.money, pParBuf);
                if (*pParBuf++ == DTYPE_SID_MAC)
                {
                    STREAM_TO_UINT32(EsamParam.SID.flag, pParBuf);
                    enc_size = fnDL698AL_asn1_get_ObjCnt(&EsamParam.SID.datalen, pParBuf);
                    pParBuf += enc_size;
                    EsamParam.SID.pData = pParBuf;
                    pParBuf += EsamParam.SID.datalen;

                    EsamParam.maclen = *pParBuf++;
                    EsamParam.pMac = pParBuf;
                    pParBuf += EsamParam.maclen;

                    *parLen = EsamParam.maclen + EsamParam.SID.datalen + 13 + enc_size;
                    if (fnEsamOp_GetSendToEsamFrame(pOmdAys->ActFlag, (u8 *)pEsamBuf, &esamDatalen, &EsamParam) == SUCCESS)
                    {
                        //调用对应的ESAM接口
                        if (fnEsamOp_Tx_Esam(pParBuf, pEsamBuf, &esamDatalen) == SUCCESS)
                        {
                            *pRetBuf++ = 0;
                            *pRetBuf++ = 1;
                            *retLen  += 2;
                            Std_MemRvsSelf(pParBuf, esamDatalen);
                            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, retLen, pParBuf, &esamDatalen, DTYPE_OCT_STR);
                            ret = DATA_ACCESS_RESULT_SUC;
                        }
                    }
                }
            }
            break;
        }
        #endif
        case ESAM_IR_ASK:   //红外请求

            ret = DATA_ACCESS_RESULT_DENY;

            if ((Secret.CA == MASTER) && (Secret.Chan == SCOM_PORT_SPI)) //管理模组与计量模组双芯认证
                //else if(Secret.CA == MASTER)  //debug
            {
                if ((*pParBuf++ == DTYPE_RN) && (*pParBuf++ == 16))
                {
                    //Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[18] , pParBuf , 16);  //通讯下发随机数RN1
                    //pParBuf += 8;
                    /*
                    if(fnEsamOp_ReadEsam_Info(0x02,pEsamBuf,&data_len)== SUCCESS)  //获取ESAM序列号
                    {
                        //ICEsamComm.Ic_Comm_TxBuf[10] = 0x00;
                        //ICEsamComm.Ic_Comm_TxBuf[11] = 0x00;
                        //fnFile_Read(FileId_HighPara , FileItemInfoOffAddr_HighPara_MeterNo , &ICEsamComm.Ic_Comm_TxBuf[12], 0x06 );
                        //Std_MemRvsSelf(&ICEsamComm.Ic_Comm_TxBuf[12] , 6);
                        if(fnEsamOp_ReadEsam_SafeNameList(pEsamBuf+8,&data_len)==SUCCESS)//读取白名单，获取白名单中管理芯表号
                        {
                            Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[18] , pParBuf , 16);  //通讯下发数据加上16字节随机数RN1
                            //pParBuf += 8;
                            if(fnEsam_In_Auth(MASTER , (u8 *)pEsamBuf + 16 , &ICEsamComm.Ic_Comm_TxBuf[10] )== SUCCESS) //RN1 密文
                            {
                                ret = DATA_ACCESS_RESULT_SUC;
                            }
                        }
                    }
                    */
                    if (fnEsamOp_ReadEsam_SafeNameList(pEsamBuf, &data_len) == SUCCESS) //读取白名单，获取白名单中管理芯表号
                    {
                        SystemDelayUs(60);
                        if (fnEsamOp_ReadEsam_Info(0x02, pEsamBuf + 8, &data_len) == SUCCESS) //获取ESAM序列号
                        {
                            SystemDelayUs(60);
                            Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[10], pEsamBuf, 8);    //通讯下发数据表号
                            Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[18], pParBuf, 16);    //通讯下发数据加上16字节随机数RN1
                            if (fnEsam_In_Auth(MASTER, (u8 *)pEsamBuf + 16, &ICEsamComm.Ic_Comm_TxBuf[10]) == SUCCESS)  //RN1 密文
                            {
                                ret = DATA_ACCESS_RESULT_SUC;
                            }
                        }
                    }
                }
            }
            else if ((Secret.CA == TERMINAL) && (Secret.Chan == SCOM_PORT_RS485A))  //终端
                //else if(Secret.CA == TERMINAL)  //debug
            {
                if ((*pParBuf++ == DTYPE_RN) && (*pParBuf++ == 8))
                {
                    if (fnEsamOp_ReadEsam_SafeNameList(pEsamBuf, &data_len) == SUCCESS) //读取白名单，获取白名单中管理芯表号
                    {
                        Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[10], pParBuf, 8);    //通讯下发随机数RN1
                        pParBuf += 8;
                        SystemDelayUs(60);
                        if (fnEsamOp_ReadEsam_Info(0x02, pEsamBuf + 8, &data_len) == SUCCESS) //获取ESAM序列号
                        {
                            SystemDelayUs(60);
                            if (fnEsam_In_Auth(TERMINAL, (u8 *)pEsamBuf + 16, &ICEsamComm.Ic_Comm_TxBuf[10]) == SUCCESS)  //RN1 密文
                            {
                                SystemDelayUs(60);
                                ret = DATA_ACCESS_RESULT_SUC;
                            }
                        }
                    }
                }
            }

            if (ret == DATA_ACCESS_RESULT_SUC)
            {
                if (fnEsam_Random(Secret.CA, pEsamBuf + 24) == SUCCESS) //获取RN2
                {
                    //-----根据要求应答序列号，表号，RN2等-------------
                    *pRetBuf++ = 0;
                    *pRetBuf++ = 1;
                    *retLen  += 2;
                    temp32 = 4;
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, retLen, (u8 *)&temp32, NULL, DTYPE_STRUCTURE);
                    //fnFile_Read(FileId_HighPara , FileItemInfoOffAddr_HighPara_MeterNo , &ICEsamComm.Ic_Comm_TxBuf[10], 0x06 );
                    //ICEsamComm.Ic_Comm_TxBuf[16] = 0;
                    //ICEsamComm.Ic_Comm_TxBuf[17] = 0;
                    data_len = 8;
                    Std_MemRvsSelf(pEsamBuf, data_len);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, retLen, pEsamBuf, &data_len, DTYPE_OCT_STR);   //表号
                    Std_MemRvsSelf(pEsamBuf + 8, data_len);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, retLen, pEsamBuf + 8, &data_len, DTYPE_OCT_STR);    //ESAM序列号
                    Std_MemRvsSelf(pEsamBuf + 16, data_len);
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, retLen, pEsamBuf + 16, &data_len, DTYPE_OCT_STR);    //RN1 密文
                    if (Secret.CA == MASTER)
                    {
                        data_len = 16;
                    }
                    else if (Secret.CA == TERMINAL)
                    {
                        data_len = 8;
                    }
                    else
                    {
                        data_len = 8;
                    }
                    pRetBuf += fnDl698_asn1_build_Type(pRetBuf, retLen, pEsamBuf + 24, &data_len, DTYPE_RN);   //RN2
                    ret = DATA_ACCESS_RESULT_SUC;

                    Secret.RemoteValid = 0;

                    if (Secret.CA == TERMINAL)
                    {
                        Secret.tTerminalDly = 0;
                        //Bkgrd.PubData.MtSta.MtSta3.StaBit.TrmRemoteValid = 0;
                        Bkgrd.PubData.MtSysSta.SysStaBit.TrmSecValid = 0;
                    }
                    /*
                    else
                    {
                        Secret.tIRDly = 0;      // 身份认证失效
                        Bkgrd.PubData.MtSysSta.SysStaBit.RemoteValid = 0;
                    }
                    */

                    Secret.tIRRequestDly = 1800;  //模拟终端或红外请求30分钟内要进行红外认证，否则请求失效
                }
            }

            break;

        case ESAM_IR_ORDER:    //红外认证
            ret = DATA_ACCESS_RESULT_DENY;

            if (Secret.tIRRequestDly)
            {
                //客户机地址为主站时，红外认证只能通过红外通道打开
                if ((Secret.CA == MASTER) && (Secret.Chan == SCOM_PORT_SPI))
                    //if(Secret.CA == MASTER)    //debug
                {
                    if ((*pParBuf++ == DTYPE_OCT_STR) && (*pParBuf++ == 8))
                    {
                        fnEsamOp_ReadEsam_SafeNameList(&ICEsamComm.Ic_Comm_TxBuf[10], &data_len); //读取白名单，获取白名单中管理芯表号
                        Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[18], pParBuf, 8);      //发送RN1
                        //pParBuf += 8;
                        if (fnEsam_Out_Auth(MASTER, pEsamBuf, &ICEsamComm.Ic_Comm_TxBuf[10]) == SUCCESS)
                        {
                            fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_tIRPrg, (u8 *)&temp32, FileItemInfoLen_HighPara_tIRPrg);
                            Secret.tIRDly = temp32 * 60;
                            ret = DATA_ACCESS_RESULT_SUC;
                            Bkgrd.PubData.MtSysSta.SysStaBit.BothCoreValid = 1;
                        }
                    }
                }
                //客户机地址为终端时，终端身份认证只能通过载波、RS485通道打开
                else if ((Secret.CA == TERMINAL) && (Secret.Chan == SCOM_PORT_RS485A))
                    //else if(Secret.CA == TERMINAL)   //debug
                {
                    if ((*pParBuf++ == DTYPE_OCT_STR) && (*pParBuf++ == 8))
                    {
                        Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[10], pParBuf, 8);
                        //pParBuf += 8;
                        if (fnEsam_Out_Auth(TERMINAL, pEsamBuf, &ICEsamComm.Ic_Comm_TxBuf[10]) == SUCCESS)
                        {
                            fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_tTerminalPrg, (u8 *)&temp32, FileItemInfoLen_HighPara_tTerminalPrg);
                            Secret.tTerminalDly = temp32 * 60;
                            Bkgrd.PubData.MtSysSta.SysStaBit.TrmSecValid = 1;
                            Secret.Terminal.tESAMDly = 1;   //下一循环让终端连接失效
                            ret = DATA_ACCESS_RESULT_SUC;
                        }
                    }
                }
            }
            break;

        case ESAM_MNG_SET:
        {
            u8 tEsam[8] = {0};

            Std_MemRvs(&tEsam[0], &pParBuf[2], 8);
            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_EvtRcdAfterEsam,
                         &tEsam[0], FileItemInfoLen_HighState_EvtRcdAftEsam);

            Inactive.Mng.RevEsam |= Mng_ComRcvEsam;
            ret = DATA_ACCESS_RESULT_SUC;
        }

        break;

        default:
            break;
    }

    return ret;
}

/*********************************************************************************************************
** Function name:   fnAct_SafeModePara
** Descriptions:    OI=0xF101 安全模式参数
** input parameters:  ActMeth:操作模式       ActFlag: 方法标识
** output parameters: pSrc 通讯下发数据
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnAct_SafeModePara(u8  ActMeth, u8 ActFlag, u16 *parLen, u8  *pSrc)
{
    sSafeModePara_TypeDef safepara;
    sSafeModeTable_TypeDef safetemp;
    u8 i, j, add ;
    u16 SecrettPrgKeyValid;
    //  u8 temp[5];
    sDl698AL_ObjInfo_TypeDef  pObj;

    *parLen = fnDl698AL_GetData_Len(1, 0, pSrc);

    if (ActFlag == 1)   //方法1 复位
    {
        fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 6, &SecrettPrgKeyValid, 2);
        if (SecrettPrgKeyValid == 0x00)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        if ((*pSrc++) != DTYPE_INT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != 0)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        Std_Memset((u8 *)&safepara, 0x00, sizeof(sSafeModePara_TypeDef));
        fnCrc_Check(0, (u8 *)&safepara, FileItemInfoLen_SecretPara_SafeModePara - 2, (u8 *)&safepara.Crc);
        fnFile_Write(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SafeModePara, (u8 *)&safepara, FileItemInfoLen_SecretPara_SafeModePara);
    }
    else if (ActFlag == 127)   //增加
    {
        if ((*pSrc++) != DTYPE_STRUCTURE)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != 2)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_OI)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        safetemp.OI = Std_Msb16DataGet(pSrc);

        pObj.oi = safetemp.OI;
        if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        pSrc += 2;

        if ((*pSrc++) != DTYPE_UINT16)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        safetemp.Mode = Std_Msb16DataGet(pSrc);
        pSrc += 2;
        fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SafeModePara, (u8 *)&safepara, sizeof(sSafeModePara_TypeDef));

        if (safepara.OI_Cnt >= MAX_SafePara)
        {
            return DATA_ACCESS_RESULT_ACC;
        }

        for (i = 0; i < safepara.OI_Cnt; i++)
        {
            if (safetemp.OI == safepara.SafeModeTable[i].OI)
            {
                return DATA_ACCESS_RESULT_OTH;
            }
        }

        safepara.SafeModeTable[safepara.OI_Cnt].OI = safetemp.OI;
        safepara.SafeModeTable[safepara.OI_Cnt].Mode = safetemp.Mode;
        safepara.OI_Cnt++;

        fnCrc_Check(0, (u8 *)&safepara, FileItemInfoLen_SecretPara_SafeModePara - 2, (u8 *)&safepara.Crc);
        fnFile_Write(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SafeModePara, (u8 *)&safepara, sizeof(sSafeModePara_TypeDef));
    }
    else if (ActFlag == 128)   //删除
    {
        if ((*pSrc++) != DTYPE_OI)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        safetemp.OI = Std_Msb16DataGet(pSrc);
        pSrc += 2;

        fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SafeModePara, (u8 *)&safepara, sizeof(sSafeModePara_TypeDef));
        for (i = 0; i < safepara.OI_Cnt; i++)
        {
            if (safetemp.OI == safepara.SafeModeTable[i].OI)
            {
                safepara.OI_Cnt--;
                if (safepara.OI_Cnt)
                {
                    for (j = i; j < safepara.OI_Cnt; j++)
                    {
                        safepara.SafeModeTable[j].OI = safepara.SafeModeTable[j + 1].OI;
                        safepara.SafeModeTable[j].Mode = safepara.SafeModeTable[j + 1].Mode;
                    }
                }
                else
                {
                    safepara.SafeModeTable[0].OI = 0;
                    safepara.SafeModeTable[0].Mode = 0;
                }

                fnCrc_Check(0, (u8 *)&safepara, FileItemInfoLen_SecretPara_SafeModePara - 2, (u8 *)&safepara.Crc);
                fnFile_Write(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SafeModePara, (u8 *)&safepara, sizeof(sSafeModePara_TypeDef));
            }
        }

        return DATA_ACCESS_RESULT_UNAVA;
    }
    else if (ActFlag == 129)   //批量增加
    {
        if ((*pSrc++) != DTYPE_ARRAY)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SafeModePara, (u8 *)&safepara, sizeof(sSafeModePara_TypeDef));

        add = *pSrc++;

        if ((safepara.OI_Cnt + j) >= MAX_SafePara)
        {
            return DATA_ACCESS_RESULT_ACC;
        }

        for (i = 0; i < add ; i++)
        {
            if ((*pSrc++) != DTYPE_STRUCTURE)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if ((*pSrc++) != 2)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if ((*pSrc++) != DTYPE_OI)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            safetemp.OI = Std_Msb16DataGet(pSrc);

            pObj.oi = safetemp.OI;
            if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
            {
                return DATA_ACCESS_RESULT_DENY;
            }

            pSrc += 2;

            if ((*pSrc++) != DTYPE_UINT16)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            safetemp.Mode = Std_Msb16DataGet(pSrc);
            pSrc += 2;

            for (j = 0; j < safepara.OI_Cnt; j++)
            {
                if (safetemp.OI == safepara.SafeModeTable[j].OI)
                {
                    return DATA_ACCESS_RESULT_OTH;
                }
            }

            safepara.SafeModeTable[safepara.OI_Cnt].OI = safetemp.OI;
            safepara.SafeModeTable[safepara.OI_Cnt].Mode = safetemp.Mode;
            safepara.OI_Cnt++;
        }

        fnCrc_Check(0, (u8 *)&safepara, FileItemInfoLen_SecretPara_SafeModePara - 2, (u8 *)&safepara.Crc);
        fnFile_Write(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_SafeModePara, (u8 *)&safepara, sizeof(sSafeModePara_TypeDef));
    }
    else
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    //temp[0] = DTYPE_OMD;
    //temp[1] = ActMeth;
    //temp[2] = ActFlag;
    //temp[3] = 0x01;
    //temp[4] = 0xF1;

    //  fnEvent_Operation(FileItemInfoNum_Evt_Prg , EVTSTART, &temp[0] );

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnAct_BroatcastTime
** Descriptions:    广播校时
** input parameters:  ActMeth:操作模式       ActFlag: 方法标识
** output parameters: pSrc 通讯下发数据
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 enClockErr = 0;
u8 fnAct_BroatcastTime(u8  ActMeth, u8 ActFlag, u16 *parLen, u8  *pSrc)
{
    u16 broadcast_min, broadcast_max;
    sDate_time_s_TypeDef timeold, timebuf, rmdaybuf;
    ErrorStatus tmpStatus = SUCCESS;
    u8 sftype, i;
    u32 Temp32A, Temp32B, Temp32C;
    sDF24 temRecord[3];
    sBroatStatue_TypeDef  broadsta;
    s8 res;
    u32 temp1, temp2, FreezeMinAdd = 0, j;

    *parLen = fnDl698AL_GetData_Len(1, 0, pSrc);

    if (ActFlag == 127)   //广播校时
    {
        fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_BroatStatue, (u8 *)&broadsta, sizeof(sBroatStatue_TypeDef));

        if ((*pSrc++) != DTYPE_DATETIME_S)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        timebuf.year = Std_Msb16DataGet(pSrc);
        pSrc += 2;
        timebuf.month = (*pSrc++);
        timebuf.day = (*pSrc++);
        timebuf.hour = (*pSrc++);
        timebuf.minute = (*pSrc++);
        timebuf.second = (*pSrc++);

        fnGetCurrTime(&timeold);

        Temp32A = fnDateTimeToSec(&timeold);
        Temp32B = fnDateTimeToSec(&timebuf);

        if (Temp32A > Temp32B)
        {
            Temp32C = Temp32A - Temp32B;
        }
        else
        {
            Temp32C = Temp32B - Temp32A;
        }

        fnFile_Read(FileId_ParaDoc, FileItemInfoOffAddr_DocPara_BroadcastMIN, (u8 *)&broadcast_min, 2);
        fnFile_Read(FileId_ParaDoc, FileItemInfoOffAddr_DocPara_BroadcastMAX, (u8 *)&broadcast_max, 2);

        sftype = fnRead_Broatcast_SafetyType();

        if (sftype == 0x08) //明文
        {
            if (broadsta.Already)
            {
                return DATA_ACCESS_RESULT_OTH;
            }

            if (fnDFCompData((u8 *)&timeold.day, (u8 *)&timebuf.day, 4))    //日期发生改变，明文广播校时不允许跨天
            {
                return DATA_ACCESS_RESULT_DENY;
            }

            if (Temp32C < broadcast_min) //小于最小校时偏差
            {
                return DATA_ACCESS_RESULT_DENY;
            }

            if (Temp32C > broadcast_max)
            {
                if (broadsta.ClockErr == 0)
                {
                    broadsta.ClockErr = 1;
                    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_BroatStatue, (u8 *)&broadsta, sizeof(sBroatStatue_TypeDef));

                    //-----记时钟故障事件记录----------
                    //                  fnEvent_Operation(FileItemInfoNum_Evt_ClockErr , EVTSTART , NULL);
                }

                Bkgrd.PubData.MtSysSta.SysStaBit.ClockErr |= CLOCK_STA_SETOVER;

                return DATA_ACCESS_RESULT_DENY;
            }

            fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_RmDate, &temRecord[0].Hour, 6);

            for (i = 0; i < 3; i++)  //结算日
            {
                //------年，月用当前系统时间-------------
                rmdaybuf.year = timeold.year;
                rmdaybuf.month = timeold.month;
                rmdaybuf.day = temRecord[i].Day;
                rmdaybuf.hour = temRecord[i].Hour;
                rmdaybuf.minute = 0;
                rmdaybuf.second = 0;
                Temp32C = fnDateTimeToSec(&rmdaybuf); //计算结算日秒数

                if (((Temp32A >= Temp32C) && (Temp32C >= Temp32B)) || ((Temp32A <= Temp32C) && (Temp32C <= Temp32B))) //跨结算日
                {
                    i = 0x55;
                    break;
                }
            }

            if (i == 0x55)
            {
                return DATA_ACCESS_RESULT_DENY;
            }
        }
        else if (sftype == 0x01) //密文+SID_MAC
        {
            if (Temp32C < broadcast_min) //小于最小校时偏差
            {
                return DATA_ACCESS_RESULT_DENY;
            }
        }
        else
        {
            return DATA_ACCESS_RESULT_DENY;
        }
    }
    else
    {
        return DATA_ACCESS_RESULT_UNDEF;
    }

    tmpStatus = fnSetCurrTime(&timebuf);

    if (tmpStatus == SUCCESS)
    {
        if (sftype == 0x08) //明文
        {
            broadsta.Already = 1;
        }
        else
        {
            if (fnDFCompData((u8 *)&timeold.day, (u8 *)&timebuf.day, 4))    //日期发生改变
            {
                broadsta.Already = 0;
            }
        }

        broadsta.ClockErr = 0;
        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_BroatStatue, (u8 *)&broadsta, sizeof(sBroatStatue_TypeDef));

        res = fnDFCompData((u8 *)&timeold.minute, (u8 *)&timebuf.minute, sizeof(sDate_time_s_TypeDef) -1);
        if (res == 1) //时间往回改重新计算周期冻结指针
        {
            fnFreezePoint_Calc(timeold, timebuf);
        }
        else if (res == -1) //-----时间往前改补下一分钟冻结----------
        {
            //-----补1min冻结------------
            Std_Memcpy((u8 *)&SysDatetimes, (u8 *)&timeold, sizeof(sDate_time_s_TypeDef));
            fnMinAdd(&SysDatetimes, 1);
            SysDatetimes.second = 0x00;
            Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_MINFRZ;
            Bkgrd.PubData.FrzMin_LineItem |= 1 << 0;
            fnFreeze();

            //-----------
            temp1 = fnDateTimeToMin(&timebuf);
            temp2 = fnDateTimeToMin(&timeold);
            if (temp1 > temp2)
            {
                FreezeMinAdd = temp1 - temp2;

                fnWDT_Restart();
                SysDatetimes.second = 0x00;

                for (j = 0; j < FreezeMinAdd ; j++)
                {
                    if (((SysDatetimes.minute % RFrzMinLine.Cycle[1]) == 0) && (RFrzMinLine.Cycle[1]))
                    {
                        Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_MINFRZ;
                        Bkgrd.PubData.FrzMin_LineItem |= 1 << 1;

                        fnFreeze();
                        break;
                    }
                    else
                    {
                        fnWDT_Restart();
                        fnMinAdd(&SysDatetimes, 1);
                    }
                }
            }
        }

        fnSysDateTimes(&SysDatetimes);

        //      fnEvent_Operation(FileItemInfoNum_Evt_ClockErr , EVTEND , NULL);
        fnEvent_Operation(FileItemInfoNum_Evt_BroadcastTime, EVTSTART, (u8 *)&timeold);

        Bkgrd.PubData.UpFlStatusFlag = 0x5a;

        if (fnDFCompData((u8 *)&SysDatetimes.hour, (u8 *)&timeold.hour, 5))
        {
            Bkgrd.PubData.UpDateTimeFlag |= BKGRD_FCHANGE_HOUR;
        }

        if (fnDFCompData((u8 *)&SysDatetimes.day, (u8 *)&timeold.day, 4)) //天发生变化
        {
            Bkgrd.PubData.UpDateTimeFlag |= BKGRD_FCHANGE_DAY;
        }

        Bkgrd.PriData.Second = SysDatetimes.second;
        Bkgrd.PriData.Minute = SysDatetimes.minute;
        Bkgrd.PriData.Hour = SysDatetimes.hour;
        Bkgrd.PriData.Day = SysDatetimes.day;
        Bkgrd.PriData.Month = SysDatetimes.month;

        fnWrite_PowDn_FrzRmDayTime();
        fnWrite_PowDn_FrzDayTime();

        return DATA_ACCESS_RESULT_SUC;
    }
    else
    {
        return DATA_ACCESS_RESULT_HD;
    }
}

/*********************************************************************************************************
** Function name:   fnAct_InOut_DevicePara
** Descriptions:    输入输出接口类
** input parameters:  ActMeth:操作模式       ActFlag: 方法标识
** output parameters: pSrc 通讯下发数据
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnAct_InOut_DevicePara(u8  OIB2, u8  ActMeth, u8 ActFlag, u16 *parLen, u8  *pSrc)
{
    u8 temp_bps ;
    u32 temp_OAD;

    *parLen = fnDl698AL_GetData_Len(1, 0, pSrc);

    if (OIB2 == 1)   //485
    {
        #if(METERTYPE == 0)
        // 智能表  两路485
        if (ActFlag == 127)
        {
        }
        #else
        if (ActFlag == 127)
        {
            if (ActMeth == 0)
            {
                if ((*pSrc++) != DTYPE_STRUCTURE)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                if ((*pSrc++) != 3)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                if ((*pSrc++) != DTYPE_OAD)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                temp_OAD = Std_Msb32DataGet(pSrc);

                pSrc += 4;

                if ((temp_OAD != 0xF2010201) && (temp_OAD != 0xF2010200))
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                if ((*pSrc++) != DTYPE_COMDCB)
                {
                    return DATA_ACCESS_RESULT_TYPE;
                }

                temp_bps = *pSrc++;

                if ((temp_bps < 2) || (temp_bps > 10))  //波特率只允许协商1200~115200
                {
                    return DATA_ACCESS_RESULT_SPDCONST;
                }

                if (fnDFCompData(pSrc, (u8 *)&TAB_COM, 4) != 0)
                {
                    return DATA_ACCESS_RESULT_DENY;
                }

                pSrc += 4;

                if ((*pSrc++) != DTYPE_ENUM)
                {
                    return DATA_ACCESS_RESULT_DENY;
                }

                if (fnDFCompData(pSrc, (u8 *)&TAB_PortFunction, 1) != 0)
                {
                    return DATA_ACCESS_RESULT_DENY;
                }

                pSrc += 1;
                ComPack[SCOM_PORT_RS485A].NewBps = temp_bps;
                ComPack[SCOM_PORT_RS485A].fBps = 1;
                fnFile_Write(FileId_ParaCom, FileItemInfoOffAddr_ComPara_Com1Style, &temp_bps, 1);      //波特率
            }
            else
            {
                return DATA_ACCESS_RESULT_DENY;
            }
        }
        else
        {
            return DATA_ACCESS_RESULT_DENY;
        }
        #endif
    }
    /*
    else if( OIB2 == 2 )    //红外
    {
        if(ActFlag == 127)
        {
            if(ActMeth == 0)
            {
                if((*pSrc++)!=DTYPE_STRUCTURE)
                    return DATA_ACCESS_RESULT_TYPE;

                if((*pSrc++)!=2)
                    return DATA_ACCESS_RESULT_TYPE;

                if((*pSrc++)!=DTYPE_OAD)
                    return DATA_ACCESS_RESULT_TYPE;

                temp_OAD = Std_Msb32DataGet(pSrc);

                if( (temp_OAD != 0xF2020201)&&(temp_OAD != 0xF2020200) )
                    return DATA_ACCESS_RESULT_DENY;

                pSrc += 4;

                if((*pSrc++)!=DTYPE_COMDCB)
                    return DATA_ACCESS_RESULT_TYPE;

                temp_bps = *pSrc++;

                if(temp_bps != 2)   //波特率只允许协商1200
                    return DATA_ACCESS_RESULT_SPDCONST;

                if(fnDFCompData(pSrc , (u8 *)&TAB_COM , 4) != 0)
                    return DATA_ACCESS_RESULT_DENY;
                pSrc += 4;

                ComPack[SCOM_PORT_IR].NewBps = temp_bps;
                ComPack[SCOM_PORT_IR].fBps = 1;
                fnFile_Write(FileId_ParaCom , FileItemInfoOffAddr_ComPara_Ir1Style , &temp_bps , 1 );
            }
            else
                return DATA_ACCESS_RESULT_DENY;
        }
        else
            return DATA_ACCESS_RESULT_DENY;
    }
    */
    /*
    else if( OIB2 == 9 )    //载波
    {
        if(ActFlag == 128)
        {
            if(ActMeth == 0)
            {
                if((*pSrc++)!=DTYPE_STRUCTURE)
                    return DATA_ACCESS_RESULT_TYPE;

                if((*pSrc++)!=2)
                    return DATA_ACCESS_RESULT_TYPE;

                if((*pSrc++)!=DTYPE_OAD)
                    return DATA_ACCESS_RESULT_TYPE;

                temp_OAD = Std_Msb32DataGet(pSrc);
                pSrc += 4;

                if(temp_OAD == 0xF20902FD)
                {
                    if(Secret.Chan != SCOM_PORT_ZBCOM)
                        return DATA_ACCESS_RESULT_DENY;
                }
                else if(temp_OAD != 0xF2090201)
                    return DATA_ACCESS_RESULT_TYPE;

                if((*pSrc++)!=DTYPE_COMDCB)
                    return DATA_ACCESS_RESULT_TYPE;

                temp_bps = *pSrc++;

                if( (temp_bps < 2)||(temp_bps > 10) )   //波特率只允许协商1200~115200
                    return DATA_ACCESS_RESULT_SPDCONST;

                if(fnDFCompData(pSrc , (u8 *)&TAB_COM , 4) != 0)
                    return DATA_ACCESS_RESULT_DENY;

                pSrc += 4;

                ComPack[SCOM_PORT_ZBCOM].NewBps = temp_bps;
                ComPack[SCOM_PORT_ZBCOM].fBps = 1;
                fnFile_Write(FileId_ParaCom , FileItemInfoOffAddr_ComPara_Com3Style , &temp_bps , 1 );  //波特率
            }
            else
                return DATA_ACCESS_RESULT_DENY;
        }
        else
            return DATA_ACCESS_RESULT_DENY;

    }*/
    else if (OIB2 == 5)  //继电器输出
    {
        if ((*pSrc++) != DTYPE_STRUCTURE)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != 2)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_OAD)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        temp_OAD = Std_Msb32DataGet(pSrc);
        pSrc += 4;

        if ((temp_OAD != 0xF2050201) && (temp_OAD != 0xF2050200))
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_ENUM)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc != 0) && (*pSrc != 1))
        {
            return DATA_ACCESS_RESULT_ACC;
        }

        pSrc += 1;
        //fnFile_Write( ,  , pSrc , 1 );   //写继电器开关属性(脉冲或保持式)
    }
    #if (TAI_TI_CE_SHI_EN == 1) /* dyf 不应支持 */
    else if (OIB2 == 7)  //多功能端子输出
    {
        if ((*pSrc++) != DTYPE_STRUCTURE)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != 2)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_OAD)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        temp_OAD = Std_Msb32DataGet(pSrc);
        pSrc += 4;

        if ((temp_OAD != 0xF2070201) && (temp_OAD != 0xF2070200))
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_ENUM)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc != 0) && (*pSrc != 1) && (*pSrc != 2))
        {
            return DATA_ACCESS_RESULT_ACC;
        }

        Bkgrd.PubData.MtSta.MtSta1.StaBit.OutMulFun = *pSrc++;

        BSP_MultiFunPort_Init(Bkgrd.PubData.MtSta.MtSta1.StaBit.OutMulFun);
    }
    #endif
    else
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnAct_Clear
** Descriptions:    清零
** input parameters:  ActMeth:操作模式       ActFlag: 方法标识，=3 电表清零; =5 事件总清零  =6 需量清零
** output parameters: pSrc 通讯下发数据
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnAct_Clear(u8  ActMeth, u8 ActFlag, u16 *parLen, u8  *pSrc)
{
    //u8 temp_OMD[4];

    *parLen = fnDl698AL_GetData_Len(1, 0, pSrc);

    if ((*pSrc++) != DTYPE_NONE)
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    if (ActFlag == 3) //电表清零
    {
        if (Bkgrd.PubData.CipherKeyFlag == 1)  //私钥状态下不允许清零
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        Event.PriData.OpFlag |= (1 << EVENT_STYLE_CLR);
        Event.PriData.Clr_Word = METER_CLR_WORD;
        Event.PriData.Clr_Step = 0;  //电表清零
        //Bkgrd.PubData.tWorkBat = 0; //时钟电池工作时间清零 dyf 电能表清零操作清零除电能表清零事件、时钟电池工作时间之外的所有记录数据
        Bkgrd.PubData.MtSysSta.SysStaBit.ClockErr = 0;

        if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable != 1)
        {
            fnEvent_Operation(FileItemInfoNum_Evt_Clr, EVTSTART, NULL);
        }
    }
    //  else if(ActFlag == 5)  //事件总清零
    //  {
    //      Event.PriData.OpFlag |= (1 << EVENT_STYLE_EVENTCLR);
    //      Event.PriData.Clr_Word = EVENT_CLR_WORD;
    //      Event.PriData.Clr_Step = 0;  //事件记录清零
    //
    //
    //      //temp_OMD[0] = 0x43;
    //      //temp_OMD[1] = 0x00;
    //      //temp_OMD[2] = ActFlag;
    //      //temp_OMD[3] = ActMeth;
    ////        fnEvent_Operation(FileItemInfoNum_Evt_EventClr , EVTSTART, &temp_OMD[0] );

    //  }
    //  else if(ActFlag == 6)   //需量清零
    //  {
    //      //-------先记录清零前需量数据，后需量清零------------
    ////        fnEvent_Operation(FileItemInfoNum_Evt_NeedClr , EVTSTART, NULL );

    //      Event.PriData.OpFlag |= (1 << EVENT_STYLE_NEEDCLR);
    //      Event.PriData.Clr_Word = DEMAND_CLR_WORD;
    //      Event.PriData.Clr_Step = 0;
    //
    //  }
    else
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnAct_WavePara
** Descriptions:    采用数据配置参数
** input parameters:  ActMeth:操作模式       ActFlag: 方法标识，=127 启动采样数据输出; =128 停止采样数据输出
** output parameters: pSrc 通讯下发数据
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnAct_WavePara(u8  ActMeth, u8 ActFlag, u16 *parLen, u8  *pSrc)
{
    u16 temp16;
    *parLen = fnDl698AL_GetData_Len(1, 0, pSrc);

    if (ActFlag == 127)
    {
        if ((*pSrc) == DTYPE_NONE) //NULL表示采用原来周波采样点数
        {
            MeasureFirmPara.Send_nPoint.SendParaBit.EnOrDis = 0x0A;
            fnWaveSpiOut_SynSmplPoint();
        }
        else if ((*pSrc++) == DTYPE_UINT16)
        {
            temp16 = Std_Msb16DataGet(pSrc);
            // if(temp16 == 0)
            {
                //  if(MeasureFirmPara.Send_nPoint == 0) temp16 = 128;
                //  else temp16 = MeasureFirmPara.Send_nPoint;
            }

            if ((temp16 != 64) && (temp16 != 128) && (temp16 != 256))
            {
                temp16 = 128;
            }
            //return DATA_ACCESS_RESULT_DENY;

            //----采样点数赋值---------------
            //MeasureFirmPara.Send_nPoint.SendPara = temp16;
            MeasureFirmPara.Send_nPoint.SendParaBit.nPoint = temp16;
            MeasureFirmPara.Send_nPoint.SendParaBit.EnOrDis = 0x0A;
            fnWaveSpiOut_SynSmplPoint();
            fnCrc_Check(0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef) - 2, (u8 *)&MeasureFirmPara.Crc);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_Send_nPoint, (u8 *)&MeasureFirmPara.Send_nPoint,  4);
            //           fnFile_Write(FileId_FirmPara , FileItemInfoOffAddr_FirmPara_Crc , (u8 *)&MeasureFirmPara.Crc ,  2);
        }
        else
        {
            return DATA_ACCESS_RESULT_DENY;
        }
    }
    else if (ActFlag == 128)  //=128 停止采样数据输出
    {
        if ((*pSrc++) != DTYPE_NONE)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        //MeasureFirmPara.Send_nPoint.SendPara = 0;
        MeasureFirmPara.Send_nPoint.SendParaBit.EnOrDis = 0x00;
        fnWaveSpiOut_SynSmplPoint();
        fnCrc_Check(0, (u8 *)&MeasureFirmPara, sizeof(sMeasureFirmPara_TypeDef) - 2, (u8 *)&MeasureFirmPara.Crc);
        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_Send_nPoint, (u8 *)&MeasureFirmPara.Send_nPoint,  4);
        //      fnFile_Write(FileId_FirmPara , FileItemInfoOffAddr_FirmPara_Crc , (u8 *)&MeasureFirmPara.Crc ,  2);
    }
    else
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    return  DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnAct_HalfIrmsPara
** Descriptions:    半波有效值参数配置
** input parameters:  ActMeth:操作模式       ActFlag: 方法标识，=127 启动采样数据输出; =128 停止采样数据输出
** output parameters: pSrc 通讯下发数据
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnAct_HalfIrmsPara(u8  ActMeth, u8 ActFlag, u16 *parLen, u8  *pSrc)
{
    u16 temp16;
    *parLen = fnDl698AL_GetData_Len(1, 0, pSrc);

    if (ActFlag == 127)
    {
        if ((*pSrc++) != DTYPE_STRUCTURE)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        if ((*pSrc++) != 2) //对象2个
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        if ((*pSrc++) != DTYPE_UINT16)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        temp16 = Std_Msb16DataGet(pSrc);    //采样频率
        pSrc     += 2;

        if (temp16 != 10) //如不是10，那么取默认值10，指示采用10ms的采样
        {
            temp16 = 10;
        }

        sHmWave.HalfIrms.Rate = temp16;
        if ((*pSrc++) != DTYPE_UINT16)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        //-----采样深度------------
        temp16 = Std_Msb16DataGet(pSrc);
        pSrc     += 2;

        if (temp16 > 480) //如不是10，那么取默认值10，指示采用10ms的采样
        {
            temp16 = 480;
        }

        sHmWave.HalfIrms.RDepth = temp16;

        sHmWave.HalfIrms.Cnt = 0;
        Std_Memset((u8 *)&sHmWave.HalfIrms.Irms[0], 0x00, 480 * 2);
        sHmWave.HalfIrms.ReadFlag = CTLSTAR;
    }
    else if (ActFlag == 128)  //=128 停止采样数据输出
    {
        if ((*pSrc++) != DTYPE_NONE)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        sHmWave.HalfIrms.ReadFlag = CTLSTOP;
    }
    else
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    return  DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnAct_EvtPara
** Descriptions:    操作事件记录类对象
** input parameters:  pOmdAys->ActMeth = 1 复位(单项事件记录清零)
                pOmdAys->ActMeth = 4 添加一个关联对象属性表
                pOmdAys->ActMeth = 5 删除一个关联对象属性表
** output parameters: pSrc 通讯下发数据
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnAct_EvtPara(u32  OMD, u8  *pSrc, u16 *parLen, u8 *pBuf)
{
    OMD_Analyse_TypeDef *pOmdAys = (OMD_Analyse_TypeDef*)&OMD;
    u8 i, oadnum, item = FileItemInfoNum_Evt_Max, class_id = 0, temp_delete; // dyf del temp_OMD[4]
    sContextList_TypeDef  tmplist;
    u16 OffAddr, recordlen;
    sDl698AL_ObjInfo_TypeDef  pObj;

    *parLen = fnDl698AL_GetData_Len(1, 0, pSrc);

    item = fnGet_EvtItem(pOmdAys->OI, &class_id);
    if ((item >= FileItemInfoNum_Evt_Max))
    {
        return DATA_ACCESS_RESULT_UNAVA;
    }

    if (pOmdAys->ActMeth != 0x00)
    {
        return DATA_ACCESS_RESULT_UNAVA;
    }

    if (pOmdAys->ActFlag == 1) //复位
    {
        return DATA_ACCESS_RESULT_DENY;

        //      if((*pSrc++)!=DTYPE_INT8)
        //          return DATA_ACCESS_RESULT_TYPE;

        //      if((*pSrc++)!=0)
        //          return DATA_ACCESS_RESULT_TYPE;
        //
        //      if (item == FileItemInfoNum_Evt_Clr)
        ////        if( (item == FileItemInfoNum_Evt_Clr)||(item == FileItemInfoNum_Evt_EventClr) ) //电表清零，事件清零不允许复位
        //          return DATA_ACCESS_RESULT_DENY;
        //
        //      Std_Memset(pBuf, 0x00, FileItemInfo_EvtRcdHead[item].Len);
        //      fnFile_Write(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, pBuf, FileItemInfo_EvtRcdHead[item].Len);

        //      fnEvent_Clr_Status(item , 0xFF);
        //          Std_MemRvs(&temp_OMD[0] , (u8 *)&pOmdAys , 4);
        //
        ////        fnEvent_Operation(FileItemInfoNum_Evt_EventClr , EVTSTART, &temp_OMD[0] );  //事件清零事件记录
    }
    else if (pOmdAys->ActFlag == 4) //添加一个关联对象属性表
    {
        if ((*pSrc++) != DTYPE_OAD)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        pObj.oad_omd = Std_Msb32DataGet(pSrc);

        pObj.oi = (u16)(pObj.oad_omd >> 16);
        if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        pSrc += 4;
        fnFile_Read(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[item].OffAddr, pBuf, FileItemInfo_EvtCtxlist[item].Len);

        oadnum = *pBuf;

        if (oadnum == 0)
        {
            Std_Memcpy((u8 *)&tmplist.OffPos, EvtStdlist[item].Addr + 1, 2);
            tmplist.len = 0;
        }
        else
        {
            for (i = 0; i < oadnum; i++)
            {
                OffAddr = 3 + i * sizeof(sContextList_TypeDef);
                Std_Memcpy((u8 *)&tmplist, pBuf + OffAddr, sizeof(sContextList_TypeDef));

                if (tmplist.OAD == pObj.oad_omd)
                {
                    i = 0xFF;
                    break;
                }
            }

            if (i == 0xFF)
            {
                return DATA_ACCESS_RESULT_OTH;
            }
        }

        oadnum ++;
        tmplist.OffPos += tmplist.len;  //添加OAD偏移= 上一个OAD偏移 + 上一个OAD长度

        tmplist.len = fnGet_OADStoreData((pObj.oad_omd & 0xFFFF1FFF),  pBuf + 1024);

        tmplist.OAD = pObj.oad_omd;

        //--------判每条事件记录长度----------------
        recordlen = tmplist.len + tmplist.OffPos;
        if (recordlen > FileItemInfo_EvtRecord[item].Len / MAX_EVRECORD_TABLE[item])
        {
            return DATA_ACCESS_RESULT_HD;
        }

        *pBuf = oadnum;
        Std_Memcpy(pBuf + 1, (u8 *)&recordlen, 2);
        //-------关联对象属性表总个数(1byte)+根据关联对象属性表计算每条事件记录长度(2byte)+关联对象属性表-----------------------
        fnFile_Write(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[item].OffAddr, pBuf, 3);  //写OAD个数，及事件记录长度

        OffAddr = 3 + (oadnum - 1) * sizeof(sContextList_TypeDef);
        Std_Memcpy(pBuf, (u8 *)&tmplist, sizeof(sContextList_TypeDef));
        fnFile_Write(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[item].OffAddr + OffAddr, pBuf, sizeof(sContextList_TypeDef));

        //设置关联对象属性表对应事件记录需清零，清事件记录头
        Std_Memset(pBuf, 0x00, FileItemInfo_EvtRcdHead[item].Len);
        fnFile_Write(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, pBuf, FileItemInfo_EvtRcdHead[item].Len);

        fnEvent_Clr_Status(item, 0xFF);
    }
    else if (pOmdAys->ActFlag == 5) //删除一个关联对象属性表
    {
        if ((*pSrc++) != DTYPE_OAD)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        pObj.oad_omd = Std_Msb32DataGet(pSrc);

        fnFile_Read(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[item].OffAddr, pBuf, FileItemInfo_EvtCtxlist[item].Len);

        oadnum = *pBuf;
        Std_Memcpy((u8 *)&recordlen, pBuf + 1, 2);

        if (oadnum == 0)
        {
            return DATA_ACCESS_RESULT_OTH;
        }
        else
        {
            for (i = 0; i < oadnum; i++)
            {
                OffAddr = 3 + i * sizeof(sContextList_TypeDef);
                Std_Memcpy((u8 *)&tmplist, pBuf + OffAddr, sizeof(sContextList_TypeDef));

                if (tmplist.OAD == pObj.oad_omd)
                {
                    temp_delete = i;

                    if (recordlen < tmplist.len)
                    {
                        i = oadnum;
                    }
                    else
                    {
                        recordlen -= tmplist.len;    //减去删除OAD长度
                    }

                    break;
                }
            }

            if (i == oadnum)
            {
                return DATA_ACCESS_RESULT_OTH;
            }

            OffAddr = 3 + (i - 1) * sizeof(sContextList_TypeDef); //取删除前上一个OAD数据
            Std_Memcpy((u8 *)&tmplist, pBuf + OffAddr, sizeof(sContextList_TypeDef));
        }
        for (i = temp_delete; i < oadnum; i++)
        {
            OffAddr =  3 + (i + 1) * sizeof(sContextList_TypeDef);
            tmplist.OffPos += tmplist.len;  //OAD偏移= 上一个OAD偏移 + 上一个OAD长度

            Std_Memcpy((u8 *)&tmplist, pBuf + OffAddr, 5);    //OAD + len

            OffAddr =  3 + i * sizeof(sContextList_TypeDef);
            Std_Memcpy(pBuf + OffAddr, (u8 *)&tmplist, sizeof(sContextList_TypeDef));
        }

        oadnum --;
        *pBuf = oadnum;
        Std_Memcpy(pBuf + 1, (u8 *)&recordlen, 2);
        //-------关联对象属性表总个数(1byte)+根据关联对象属性表计算每条事件记录长度(2byte)+关联对象属性表-----------------------
        fnFile_Write(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[item].OffAddr, pBuf, FileItemInfo_EvtCtxlist[item].Len);

        //设置关联对象属性表对应事件记录需清零，清事件记录头
        Std_Memset(pBuf, 0x00, FileItemInfo_EvtRcdHead[item].Len);
        fnFile_Write(FileId_EvtRcdHead, FileItemInfo_EvtRcdHead[item].OffAddr, pBuf, FileItemInfo_EvtRcdHead[item].Len);

        fnEvent_Clr_Status(item, 0xFF);
    }
    else if (pOmdAys->ActFlag == 127)
    {
        // 管理模组升级事件
        if (pOmdAys->OI == 0x3036)
        {
            fnEvent_Operation(FileItemInfoNum_Evt_MngUpdate, EVTSTART, pSrc);

            Bkgrd.PubData.MtSysSta.SysStaBit.EvtControlUpgrade = 1;
        }
        else
        {
            return DATA_ACCESS_RESULT_DENY;
        }
    }
    else
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    *pBuf = DTYPE_OMD;
    Std_Lsb32DataSet(pBuf + 1, OMD);
    //  fnEvent_Operation(FileItemInfoNum_Evt_Prg , EVTSTART, pBuf );

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnAct_FrzPara
** Descriptions:    操作冻结类对象
** input parameters:  pOmdAys->ActMeth = 3 触发一次冻结
                pOmdAys->ActMeth = 4 添加一个关联对象属性表
                pOmdAys->ActMeth = 5 删除一个关联对象属性表
                pOmdAys->ActMeth = 7 批量添加关联对象属性表
                pOmdAys->ActMeth = 8 清除关联对象属性表
** output parameters: pSrc 通讯下发数据
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnAct_FrzPara(u32  OMD, u8  *pSrc,  u16 *parLen, u8 *pBuf)
{
    OMD_Analyse_TypeDef *pOmdAys = (OMD_Analyse_TypeDef*)&OMD;
    u8 i, j, oadnum, temp_delete, temp_add;
    u8 item = FileItemInfoNum_Frz_MAX, line_item ;
    sFrzCtxList_TypeDef  tmplist_old, tmplist;
    u16 OffAddr, recordlen;
    u32 totallen;
    sFrzMinLinePara_TypeDef tempFrzMinLine[MAX_FRZMIN_LINE];
    OAD_Analyse_TypeDef  *tempOadAys;
    sDl698AL_ObjInfo_TypeDef  pObj;

    *parLen = fnDl698AL_GetData_Len(1, 0, pSrc);

    //--------仅支持厂内模式下修改------------
    if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable != 1)
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    item = fnGet_FrzItem(pOmdAys->OI);
    if ((item >= FileItemInfoNum_Frz_MAX))
    {
        return DATA_ACCESS_RESULT_UNAVA;
    }

    if (pOmdAys->ActMeth != 0x00)
    {
        return DATA_ACCESS_RESULT_UNAVA;
    }

    if (pOmdAys->ActFlag == 3) //触发一次冻结(瞬时冻结)
    {
        if ((*pSrc++) != DTYPE_UINT16)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        //if(item != FileItemInfoNum_Frz_WinkFrz)
        //  return DATA_ACCESS_RESULT_UNAVA;

        //-----延时时间处理-------
        Bkgrd.PubData.FrzWink_Delay = Std_Msb16DataGet(pSrc);

        if (Bkgrd.PubData.FrzWink_Delay == 0)
        {
            Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_WINKFRZ;
        }
    }
    else if (pOmdAys->ActFlag == 4) //添加一个关联对象属性表
    {
        if ((*pSrc++) != DTYPE_STRUCTURE)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        if ((*pSrc++) != 3) //3//个结构体
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_UINT16)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_MemRvs((u8 *)&tmplist.Cycle, pSrc, 2);  //周期
        pSrc += 2;

        if ((*pSrc++) != DTYPE_OAD)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_MemRvs((u8 *)&tmplist.OAD, pSrc, 4);        //OAD

        pObj.oad_omd = tmplist.OAD;

        pObj.oi = (u16)(pObj.oad_omd >> 16);
        if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        pSrc += 4;

        if ((*pSrc++) != DTYPE_UINT32)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_MemRvs((u8 *)&tmplist.Depth, pSrc, 4);  //深度
        pSrc += 4;

        fnFile_Read(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[item].OffAddr, pBuf, FileItemInfo_FrzCtxlist[item].Len);

        oadnum = *pBuf;

        if (item == FileItemInfoNum_Frz_MinFrz)  //分钟冻结读取8条曲线头
        {
            for (j = 0; j < MAX_FRZMIN_LINE; j++)
            {
                fnFile_Read(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[j].OffAddr, (u8 *)&tempFrzMinLine[j], sizeof(sFrzMinLinePara_TypeDef));
            }

            tempOadAys = (OAD_Analyse_TypeDef *)&tmplist.OAD;
            line_item = tempOadAys->AtrFeature;

            if (tempFrzMinLine[line_item].OADnum == 0)
            {
                tmplist_old.len = 0;
                Std_Memcpy((u8 *)&recordlen, (u8 *)&Frz_StdRecList.reclen, 2);    //标准事件记录单元空间长度

                tempFrzMinLine[line_item].Cycle = tmplist.Cycle;
                tempFrzMinLine[line_item].Depth = tmplist.Depth;
            }
            else
            {
                recordlen = tempFrzMinLine[line_item].RecLen;
                for (i = 0; i < tempFrzMinLine[line_item].OADnum; i++)
                {
                    OffAddr = 3 + i * sizeof(sFrzCtxList_TypeDef);
                    Std_Memcpy((u8 *)&tmplist_old, pBuf + OffAddr, sizeof(sFrzCtxList_TypeDef));

                    if (tmplist_old.OAD == tmplist.OAD)
                    {
                        i = 0xFF;
                        break;
                    }

                    if ((tmplist.Cycle != tempFrzMinLine[line_item].Cycle) || (tmplist.Depth != tempFrzMinLine[line_item].Depth))
                    {
                        return DATA_ACCESS_RESULT_DENY;
                    }
                }

                if (i == 0xFF)
                {
                    return DATA_ACCESS_RESULT_OTH;
                }
            }

            oadnum ++;
            tmplist.OffPos = recordlen;  //本字节的偏移 = 未累计前事件记录长度

            tmplist.len = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF), pBuf + 1024);

            totallen = 0;
            tempFrzMinLine[line_item].RecLen = tmplist.len + tmplist.OffPos;
            tempFrzMinLine[line_item].LineRecLen = (u32)(tempFrzMinLine[line_item].RecLen * tempFrzMinLine[line_item].Depth);
            for (j = 0; j < MAX_FRZMIN_LINE; j++)
            {
                totallen += tempFrzMinLine[j].LineRecLen;

                if (j == 0)
                {
                    tempFrzMinLine[j].LineOffAdder = 0;
                }
                else
                {
                    tempFrzMinLine[j].LineOffAdder = (u32)(tempFrzMinLine[j - 1].LineRecLen +  tempFrzMinLine[j - 1].LineOffAdder);
                }
            }

            if (totallen > FileItemInfo_FrzRecord[item].Len)
            {
                return DATA_ACCESS_RESULT_ACC;
            }

            tempFrzMinLine[line_item].OADnum ++;
        }
        else   //除分钟冻结以外的冻结
        {
            Std_Memcpy((u8 *)&recordlen,  pBuf  + 1,  2);

            if (oadnum == 0)
            {
                tmplist_old.len = 0;
                Std_Memcpy((u8 *)&recordlen, (u8 *)&Frz_StdRecList.reclen, 2);    //标准事件记录单元空间长度
            }
            else
            {
                for (i = 0; i < oadnum; i++)
                {
                    OffAddr = 3 + i * sizeof(sFrzCtxList_TypeDef);
                    Std_Memcpy((u8 *)&tmplist_old, pBuf + OffAddr, sizeof(sFrzCtxList_TypeDef));

                    if (tmplist_old.OAD == tmplist.OAD)
                    {
                        i = 0xFF;
                        break;
                    }

                    if ((tmplist.Cycle != tmplist_old.Cycle) || (tmplist.Depth != tmplist_old.Depth))
                    {
                        return DATA_ACCESS_RESULT_DENY;
                    }
                }

                if (i == 0xFF)
                {
                    return DATA_ACCESS_RESULT_OTH;
                }
            }

            oadnum ++;
            tmplist.OffPos = recordlen;  //本字节的偏移 = 未累计前事件记录长度

            tmplist.len = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF),  pBuf + 1024);

            //--------判每条事件记录长度----------------
            recordlen = tmplist.len + tmplist.OffPos;
            totallen = (u32)(recordlen * tmplist.Depth);

            if (totallen > FileItemInfo_FrzRecord[item].Len)
            {
                return DATA_ACCESS_RESULT_ACC;
            }
        }

        *pBuf = oadnum;
        Std_Memcpy(pBuf + 1, (u8 *)&recordlen, 2);
        //-------关联对象属性表总个数(1byte)+根据关联对象属性表计算每条事件记录长度(2byte)+关联对象属性表-----------------------
        fnFile_Write(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[item].OffAddr, pBuf, 3);  //写OAD个数，及事件记录长度

        OffAddr = 3 + (oadnum - 1) * sizeof(sFrzCtxList_TypeDef);
        Std_Memcpy(pBuf, (u8 *)&tmplist, sizeof(sFrzCtxList_TypeDef));
        fnFile_Write(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[item].OffAddr + OffAddr, pBuf, sizeof(sFrzCtxList_TypeDef));

        //设置关联对象属性表对应事件记录需清零，清事件记录头
        Std_Memset(pBuf, 0x00, FileItemInfo_FrzRcdHead[item].Len);
        fnFile_Write(FileId_FrzRcdHead, FileItemInfo_FrzRcdHead[item].OffAddr, pBuf, FileItemInfo_FrzRcdHead[item].Len);

        if (item == FileItemInfoNum_Frz_MinFrz)
        {
            for (j = 0; j < MAX_FRZMIN_LINE; j++)
            {
                Std_Memset(pBuf, 0x00, FileItemInfo_FrzMinLineHead[j].Len);     //清8条分钟冻结曲线头 sFrzRcdHead_TypeDef
                Std_Memcpy(pBuf, (u8 *)&tempFrzMinLine[j], sizeof(sFrzMinLinePara_TypeDef));
                fnFile_Write(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[j].OffAddr, pBuf, FileItemInfo_FrzMinLineHead[j].Len);
                RFrzMinLine.Cycle[j] = tempFrzMinLine[j].Cycle;
            }
            fnCrc_Check(0, (u8 *)&RFrzMinLine.Cycle[0], sizeof(sFrzMinCycle_TypeDef) -2, (u8 *)&RFrzMinLine.Crc);
        }
    }
    else if (pOmdAys->ActFlag == 5) //删除一个关联对象属性表
    {
        if ((*pSrc++) != DTYPE_OAD)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_MemRvs((u8 *)&tmplist.OAD, pSrc, 4);        //OAD
        pSrc += 4;

        fnFile_Read(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[item].OffAddr, pBuf, FileItemInfo_FrzCtxlist[item].Len);

        oadnum = *pBuf;

        if (item == FileItemInfoNum_Frz_MinFrz)  //分钟冻结读取8条曲线头
        {
            for (j = 0; j < MAX_FRZMIN_LINE; j++)
            {
                fnFile_Read(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[j].OffAddr, (u8 *)&tempFrzMinLine[j], sizeof(sFrzMinLinePara_TypeDef));
            }

            tempOadAys = (OAD_Analyse_TypeDef *)&tmplist.OAD;
            line_item = tempOadAys->AtrFeature;

            if (tempFrzMinLine[line_item].OADnum == 0)
            {
                return DATA_ACCESS_RESULT_OTH;
            }
            else
            {
                for (i = 0; i < oadnum; i++)
                {
                    OffAddr = 3 + i * sizeof(sFrzCtxList_TypeDef);
                    Std_Memcpy((u8 *)&tmplist_old, pBuf + OffAddr, sizeof(sFrzCtxList_TypeDef));

                    if (tmplist.OAD == tmplist_old.OAD)
                    {
                        temp_delete = i;

                        tempFrzMinLine[line_item].RecLen = tmplist_old.OffPos;
                        recordlen = tempFrzMinLine[line_item].RecLen;
                        tempFrzMinLine[line_item].OADnum--;
                        tempFrzMinLine[line_item].LineRecLen = tempFrzMinLine[line_item].RecLen * tempFrzMinLine[line_item].Depth;

                        break;
                    }
                }

                if (i == oadnum)
                {
                    return DATA_ACCESS_RESULT_OTH;
                }

                for (i = temp_delete; i < oadnum; i++)
                {
                    OffAddr =  3 + (i + 1) * sizeof(sFrzCtxList_TypeDef);

                    Std_Memcpy((u8 *)&tmplist, pBuf + OffAddr, sizeof(sFrzCtxList_TypeDef));    //OAD + len

                    if (tempFrzMinLine[line_item].Cycle == tmplist.Cycle)  //相同曲线是重新计算
                    {
                        tmplist.OffPos = tempFrzMinLine[line_item].RecLen;
                        tempFrzMinLine[line_item].RecLen = tmplist.OffPos + tmplist.len;
                        tempFrzMinLine[line_item].LineRecLen = tempFrzMinLine[line_item].RecLen * tempFrzMinLine[line_item].Depth;
                    }

                    OffAddr =  3 + i * sizeof(sFrzCtxList_TypeDef);
                    Std_Memcpy(pBuf + OffAddr, (u8 *)&tmplist, sizeof(sFrzCtxList_TypeDef));
                }
            }
        }
        else
        {
            Std_Memcpy((u8 *)&recordlen, pBuf + 1, 2);

            if (oadnum == 0)
            {
                return DATA_ACCESS_RESULT_OTH;
            }
            else
            {
                for (i = 0; i < oadnum; i++)
                {
                    OffAddr = 3 + i * sizeof(sFrzCtxList_TypeDef);
                    Std_Memcpy((u8 *)&tmplist_old, pBuf + OffAddr, sizeof(sFrzCtxList_TypeDef));

                    if (tmplist.OAD == tmplist_old.OAD)
                    {
                        temp_delete = i;

                        recordlen -= tmplist_old.len;  //减去删除OAD长度

                        break;
                    }
                }

                if (i == oadnum)
                {
                    return DATA_ACCESS_RESULT_OTH;
                }

                OffAddr = 3 + (i - 1) * sizeof(sFrzCtxList_TypeDef); //取删除前上一个OAD数据
                Std_Memcpy((u8 *)&tmplist_old, pBuf + OffAddr, sizeof(sFrzCtxList_TypeDef));
            }

            for (i = temp_delete; i < oadnum; i++)
            {
                OffAddr =  3 + (i + 1) * sizeof(sFrzCtxList_TypeDef);

                Std_Memcpy((u8 *)&tmplist, pBuf + OffAddr, sizeof(sFrzCtxList_TypeDef));    //OAD + len
                tmplist.OffPos = tmplist_old.OffPos + tmplist_old.len;  //OAD偏移= 上一个OAD偏移 + 上一个OAD长度

                OffAddr =  3 + i * sizeof(sFrzCtxList_TypeDef);
                Std_Memcpy(pBuf + OffAddr, (u8 *)&tmplist, sizeof(sFrzCtxList_TypeDef));

                Std_Memcpy((u8 *)&tmplist_old, (u8 *)&tmplist, sizeof(sFrzCtxList_TypeDef));
            }
        }
        oadnum --;
        *pBuf = oadnum;
        Std_Memcpy(pBuf + 1, (u8 *)&recordlen, 2);
        //-------关联对象属性表总个数(1byte)+根据关联对象属性表计算每条事件记录长度(2byte)+关联对象属性表-----------------------
        fnFile_Write(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[item].OffAddr, pBuf, FileItemInfo_FrzCtxlist[item].Len);

        //设置关联对象属性表对应事件记录需清零，清事件记录头
        Std_Memset(pBuf, 0x00, FileItemInfo_FrzRcdHead[item].Len);
        fnFile_Write(FileId_FrzRcdHead, FileItemInfo_FrzRcdHead[item].OffAddr, pBuf, FileItemInfo_FrzRcdHead[item].Len);

        if (item == FileItemInfoNum_Frz_MinFrz)
        {
            for (j = 0; j < MAX_FRZMIN_LINE; j++)
            {
                Std_Memset(pBuf, 0x00, FileItemInfo_FrzMinLineHead[j].Len);     //清命令头 sFrzRcdHead_TypeDef

                if (j == 0)
                {
                    tempFrzMinLine[j].LineOffAdder = 0;
                }
                else
                {
                    tempFrzMinLine[j].LineOffAdder = (u32)(tempFrzMinLine[j - 1].LineRecLen + tempFrzMinLine[j - 1].LineOffAdder);
                }

                Std_Memcpy(pBuf, (u8 *)&tempFrzMinLine[j], sizeof(sFrzMinLinePara_TypeDef));
                fnFile_Write(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[j].OffAddr, pBuf, FileItemInfo_FrzMinLineHead[j].Len);
                RFrzMinLine.Cycle[j] = tempFrzMinLine[j].Cycle;
            }

            fnCrc_Check(0, (u8 *)&RFrzMinLine.Cycle[0], sizeof(sFrzMinCycle_TypeDef) -2, (u8 *)&RFrzMinLine.Crc);
        }
    }
    else if (pOmdAys->ActFlag == 7) //批量添加关联对象属性表
    {
        if ((*pSrc++) != DTYPE_ARRAY)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        temp_add = *pSrc++;
        if ((temp_add == 0) || (temp_add > 30)) //最多允许添加30个OAD
        {
            return DATA_ACCESS_RESULT_ACC;
        }

        fnFile_Read(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[item].OffAddr, pBuf, FileItemInfo_FrzCtxlist[item].Len);

        oadnum = *pBuf;
        Std_Memcpy((u8 *)&recordlen,  pBuf  + 1,  2);

        if (item == FileItemInfoNum_Frz_MinFrz)  //分钟冻结读取8条曲线头
        {
            for (j = 0; j < MAX_FRZMIN_LINE; j++)
            {
                fnFile_Read(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[j].OffAddr, (u8 *)&tempFrzMinLine[j], sizeof(sFrzMinLinePara_TypeDef));
            }
        }

        for (j = 0; j < temp_add; j++)
        {
            if ((*pSrc++) != DTYPE_STRUCTURE)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }
            if ((*pSrc++) != 3) //3//个结构体
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            if ((*pSrc++) != DTYPE_UINT16)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_MemRvs((u8 *)&tmplist.Cycle, pSrc, 2);  //周期
            pSrc += 2;

            if ((*pSrc++) != DTYPE_OAD)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_MemRvs((u8 *)&tmplist.OAD, pSrc, 4);        //OAD
            pSrc += 4;

            pObj.oad_omd = tmplist.OAD;

            pObj.oi = (u16)(pObj.oad_omd >> 16);
            if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
            {
                return DATA_ACCESS_RESULT_DENY;
            }

            if ((*pSrc++) != DTYPE_UINT32)
            {
                return DATA_ACCESS_RESULT_TYPE;
            }

            Std_MemRvs((u8 *)&tmplist.Depth, pSrc, 4);  //深度
            pSrc += 4;

            if (item == FileItemInfoNum_Frz_MinFrz)  //分钟冻结读取8条曲线头
            {
                tempOadAys = (OAD_Analyse_TypeDef *)&tmplist.OAD;
                line_item = tempOadAys->AtrFeature;

                if (tempFrzMinLine[line_item].OADnum == 0)
                {
                    tmplist_old.len = 0;
                    Std_Memcpy((u8 *)&recordlen, (u8 *)&Frz_StdRecList.reclen, 2);    //标准事件记录单元空间长度

                    tempFrzMinLine[line_item].Cycle = tmplist.Cycle;
                    tempFrzMinLine[line_item].Depth = tmplist.Depth;
                }
                else
                {
                    recordlen = tempFrzMinLine[line_item].RecLen;
                    for (i = 0; i < tempFrzMinLine[line_item].OADnum; i++)
                    {
                        OffAddr = 3 + i * sizeof(sFrzCtxList_TypeDef);
                        Std_Memcpy((u8 *)&tmplist_old, pBuf + OffAddr, sizeof(sFrzCtxList_TypeDef));

                        if (tmplist_old.OAD == tmplist.OAD)
                        {
                            i = 0xFF;
                            break;
                        }

                        if ((tmplist.Cycle != tempFrzMinLine[line_item].Cycle) || (tmplist.Depth != tempFrzMinLine[line_item].Depth))
                        {
                            return DATA_ACCESS_RESULT_DENY;
                        }
                    }

                    if (i == 0xFF)
                    {
                        return DATA_ACCESS_RESULT_OTH;
                    }
                }

                tmplist.OffPos = recordlen;  //本字节的偏移 = 未累计前事件记录长度

                tmplist.len = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF),  pBuf + 1024);

                totallen = 0;
                tempFrzMinLine[line_item].RecLen = tmplist.len + tmplist.OffPos;
                tempFrzMinLine[line_item].LineRecLen = (u32)(tempFrzMinLine[line_item].RecLen * tempFrzMinLine[line_item].Depth);
                for (i = 0; i < MAX_FRZMIN_LINE; i++)
                {
                    totallen += tempFrzMinLine[i].LineRecLen;

                    if (i == 0)
                    {
                        tempFrzMinLine[i].LineOffAdder = 0;
                    }
                    else
                    {
                        tempFrzMinLine[i].LineOffAdder = (u32)(tempFrzMinLine[i - 1].LineRecLen + tempFrzMinLine[i - 1].LineOffAdder);
                    }
                }

                if (totallen > FileItemInfo_FrzRecord[item].Len)
                {
                    return DATA_ACCESS_RESULT_ACC;
                }

                tempFrzMinLine[line_item].OADnum ++;
            }
            else
            {
                if (oadnum == 0)
                {
                    tmplist_old.len = 0;
                    Std_Memcpy((u8 *)&recordlen, (u8 *)&Frz_StdRecList.reclen, 2);    //标准事件记录单元空间长度
                }
                else
                {
                    for (i = 0; i < oadnum; i++)
                    {
                        OffAddr = 3 + i * sizeof(sFrzCtxList_TypeDef);
                        Std_Memcpy((u8 *)&tmplist_old, pBuf + OffAddr, sizeof(sFrzCtxList_TypeDef));

                        if (tmplist_old.OAD == tmplist.OAD)
                        {
                            i = 0xFF;
                            break;
                        }

                        if ((tmplist.Cycle != tmplist_old.Cycle) || (tmplist.Depth != tmplist_old.Depth))
                        {
                            return DATA_ACCESS_RESULT_DENY;
                        }
                    }

                    if (i == 0xFF)
                    {
                        return DATA_ACCESS_RESULT_OTH;
                    }
                }

                tmplist.OffPos = recordlen;  //本字节的偏移 = 未累计前事件记录长度

                tmplist.len = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF),  pBuf + 1024);

                //--------判每条事件记录长度----------------
                recordlen = tmplist.len + tmplist.OffPos;
                totallen = (u32)(recordlen * tmplist.Depth);

                if (totallen > FileItemInfo_FrzRecord[item].Len)
                {
                    return DATA_ACCESS_RESULT_ACC;
                }
            }

            OffAddr = 3 + oadnum * sizeof(sFrzCtxList_TypeDef);
            Std_Memcpy(pBuf + OffAddr, (u8 *)&tmplist, sizeof(sFrzCtxList_TypeDef));

            oadnum ++;
        }

        *pBuf = oadnum;
        Std_Memcpy(pBuf + 1, (u8 *)&recordlen, 2);
        fnFile_Write(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[item].OffAddr, pBuf, FileItemInfo_FrzCtxlist[item].Len);

        //设置关联对象属性表对应事件记录需清零，清事件记录头
        Std_Memset(pBuf, 0x00, FileItemInfo_FrzRcdHead[item].Len);
        fnFile_Write(FileId_FrzRcdHead, FileItemInfo_FrzRcdHead[item].OffAddr, pBuf, FileItemInfo_FrzRcdHead[item].Len);

        if (item == FileItemInfoNum_Frz_MinFrz)
        {
            for (j = 0; j < MAX_FRZMIN_LINE; j++)
            {
                Std_Memset(pBuf, 0x00, FileItemInfo_FrzMinLineHead[j].Len);     //清8条分钟冻结曲线头 sFrzRcdHead_TypeDef
                Std_Memcpy(pBuf, (u8 *)&tempFrzMinLine[j], sizeof(sFrzMinLinePara_TypeDef));
                fnFile_Write(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[j].OffAddr, pBuf, FileItemInfo_FrzMinLineHead[j].Len);
                RFrzMinLine.Cycle[j] = tempFrzMinLine[j].Cycle;
            }
            fnCrc_Check(0, (u8 *)&RFrzMinLine.Cycle[0], sizeof(sFrzMinCycle_TypeDef) -2, (u8 *)&RFrzMinLine.Crc);
        }
    }
    else if (pOmdAys->ActFlag == 8) //清除关联对象属性表
    {
        if ((*pSrc++) != DTYPE_NONE)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_Memset(pBuf, 0x00, FileItemInfo_FrzCtxlist[item].Len);
        fnFile_Write(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[item].OffAddr, pBuf, FileItemInfo_FrzCtxlist[item].Len);

        //设置关联对象属性表对应事件记录需清零，清事件记录头
        Std_Memset(pBuf, 0x00, FileItemInfo_FrzRcdHead[item].Len);
        fnFile_Write(FileId_FrzRcdHead, FileItemInfo_FrzRcdHead[item].OffAddr, pBuf, FileItemInfo_FrzRcdHead[item].Len);

        if (item == FileItemInfoNum_Frz_MinFrz) //分钟冻结特殊处理，分钟冻结需要支持多条曲线
        {
            for (j = 0; j < MAX_FRZMIN_LINE; j++)
            {
                Std_Memset(pBuf, 0x00, FileItemInfo_FrzMinLineHead[j].Len);     //清命令头 sFrzRcdHead_TypeDef
                fnFile_Write(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[j].OffAddr, pBuf, FileItemInfo_FrzMinLineHead[j].Len);
                RFrzMinLine.Cycle[j] = 0x00;
            }
            fnCrc_Check(0, (u8 *)&RFrzMinLine.Cycle[0], sizeof(sFrzMinCycle_TypeDef) -2, (u8 *)&RFrzMinLine.Crc);
        }
    }
    else
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    if (pOmdAys->ActFlag != 3) //除触发一次冻结(瞬时冻结)以外事件记编程事件记录
    {
        *pBuf = DTYPE_OMD;
        Std_Lsb32DataSet(pBuf + 1, OMD);
        //      fnEvent_Operation(FileItemInfoNum_Evt_Prg , EVTSTART , pBuf );
    }
    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnAct_DispPara
** Descriptions:    OI=0xF300 0xF301 显示接口类
** input parameters:  ActMeth:操作模式       ActFlag: 方法标识
** output parameters: pSrc 通讯下发数据
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnAct_DispPara(u32  OMD, u16 *parLen, u8  *pSrc)
{
    #if(LCD_DISP == TRUE)
    OMD_Analyse_TypeDef *pOmdAys = (OMD_Analyse_TypeDef*)&OMD;
    sDispItem_TypeDef Disptemp;
    sDl698AL_ObjInfo_TypeDef  pObj;

    *parLen = fnDl698AL_GetData_Len(1, 0, pSrc);

    if (pOmdAys->ActMeth)
    {
        return DATA_ACCESS_RESULT_TYPE;
    }

    if (pOmdAys->ActFlag == 1)   //方法1 复位
    {
        if ((*pSrc++) != DTYPE_INT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != 0)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if (pOmdAys->OI == 0xF300) //回到自动轮显第一屏
        {
            Disp_EnterMode(DISP_AUTO_MODE, 0);
        }
        else if (pOmdAys->OI == 0xF301) //回到按键显示第一屏
        {
            Disp_EnterMode(DISP_MANUAL_MODE, 0);
        }
        else
        {
            return DATA_ACCESS_RESULT_DENY;
        }
    }
    else if (pOmdAys->ActFlag == 3)   //下翻
    {
        if (pOmdAys->OI != 0xF301) //只有按键显示支持上翻，下翻
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        if ((*pSrc++) != DTYPE_NONE)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        Disp_ManualAction(DISP_UP_MANUAL);
    }
    else if (pOmdAys->ActFlag == 4)   //上翻
    {
        if (pOmdAys->OI != 0xF301) //只有按键显示支持上翻，下翻
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        if ((*pSrc++) != DTYPE_NONE)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
        Disp_ManualAction(DISP_DOWN_MANUAL);
    }
    else if (pOmdAys->ActFlag == 5)   //显示查看
    {
        if (((*pSrc++) != DTYPE_STRUCTURE) || ((*pSrc++) != 3))
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != DTYPE_CSD)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Std_Memset((u8 *)&Disptemp, 0x00, sizeof(sDispItem_TypeDef));
        Disptemp.CSD = *pSrc++ ;

        if (Disptemp.CSD == 1) //ROAD
        {
            pObj.oad_omd = Std_Msb32DataGet(pSrc);
            pObj.oi = (u16)(pObj.oad_omd >> 16);
            if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
            {
                return DATA_ACCESS_RESULT_DENY;
            }
            Std_MemRvs(&Disptemp.M_Element, pSrc, 4);
            pSrc += (4 + 1);

            pObj.oad_omd = Std_Msb32DataGet(pSrc);
            pObj.oi = (u16)(pObj.oad_omd >> 16);
            if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
            {
                return DATA_ACCESS_RESULT_DENY;
            }
            Std_MemRvs(&Disptemp.Element, pSrc, 4);
            pSrc += 4;
        }
        else
        {
            pObj.oad_omd = Std_Msb32DataGet(pSrc);
            pObj.oi = (u16)(pObj.oad_omd >> 16);
            if (fnDl698AL_Check_OIList(&pObj) == 0xFFFF)
            {
                return DATA_ACCESS_RESULT_DENY;
            }
            Std_MemRvs(&Disptemp.M_Element, pSrc, 4);
            pSrc += 4;
        }

        if ((*pSrc++) != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Disptemp.nDispIndex = *pSrc++;

        if ((*pSrc++) != DTYPE_UINT16)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        //--------显示持续时间-----------------
        u16 temp; //显示持续时间临时缓存
        temp = Std_Msb16DataGet(pSrc);
        Disp_ViewAction(Disptemp, temp);

        pSrc += 2;
    }
    else if (pOmdAys->ActFlag == 6)  //全显
    {
        if ((*pSrc++) != DTYPE_UINT16)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        u16 disp_all_temp; //全屏显示时间临时缓存
        disp_all_temp = Std_Msb16DataGet(pSrc);
        Disp_EnterMode(DISP_FULL_MODE, disp_all_temp);
        pSrc += 2;
    }
    else
    {
        return DATA_ACCESS_RESULT_DENY;
    }
    #endif
    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************************************************
** Function name:   fnAct_VarPara
** Descriptions:    OI=0x2015 跟随上报状态确认
** input parameters:  ActMeth:操作模式       ActFlag: 方法标识
** output parameters: pSrc 通讯下发数据
** Returned value:成功或失败结果
*********************************************************************************************************/
u8 fnAct_VarPara(u32  OMD, u16 *parLen, u8  *pSrc)
{
    u8 temp[4], i;
    u32 temp32;

    *parLen = fnDl698AL_GetData_Len(1, 0, pSrc);
    if (OMD == 0x20157F00)
    {
        if ((*pSrc++) != DTYPE_BITSTRING)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != 0x20) //长度
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        for (i = 0; i < 4; i++)
        {
            Std_BitRvsSelf(&temp[i], pSrc++);
        }

        temp32 = Std_Lsb32DataGet(&temp[0]);

        if (Secret.Chan == SCOM_PORT_ZBCOM)
        {
            EvtRptData.Status.RptStuZB &= ~temp32;
            fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatusZB, (u8 *)&EvtRptData.Status.RptStuZB, 4);
        }
        else if (Secret.Chan == SCOM_PORT_RS485A)
        {
            EvtRptData.Status.RptStu485 &= ~temp32;
            fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatus485, (u8 *)&EvtRptData.Status.RptStu485, 4);
        }
        else if (Secret.Chan == SCOM_PORT_RS485B)
        {
            EvtRptData.Status.RptStuZB &= ~temp32;
            fnFile_Write(FileId_EvtReport, FileItemInfoOffAddr_EvtReport_RptStatus4852, (u8 *)&EvtRptData.Status.RptStu4852, 4);
        }

        fnClr_RptStatus(REPORT_STATUS_GATAOFF);

        fnClr_RptStatus(REPORT_STATUS_GATAON);
    }
    else if (OMD == 0x20147F00)  //确认计量模组系统状态字
    {
        if ((*pSrc++) != DTYPE_BITSTRING)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++) != 0x20) //长度
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        for (i = 0; i < 4; i++)
        {
            Std_BitRvsSelf(&temp[i], pSrc++);
        }

        temp[0] = 0x00;
        temp[1] = 0x00;  //bit0~bit15 不清

        temp32 = Std_Lsb32DataGet(&temp[0]);

        if (temp[3] & 0x80) //分钟冻结确认，清分钟冻结上报
        {
            SynFrzDataBlock.Frz1DateValid = 0;
            SynFrzDataBlock.Frz2DateValid = 0;
            Std_Memset((u8 *)&SynFrzDataBlock.Frz1DateTimes, 0x00, 100);    //变量清零
        }

        Bkgrd.PubData.MtSysSta.SysSta &= ~temp32;
    }
    else if (OMD == 0x20EB0300)  //厂家扩展透传（参数）
    {
        //20EB0300用于厂家内部生产使用，数据安全性由厂家自己负责。仅限于公钥下使用。
        if ((*pSrc++) != DTYPE_STRING)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }
    }
    else
    {
        return DATA_ACCESS_RESULT_DENY;
    }

    return DATA_ACCESS_RESULT_SUC;
}

/*********************************************************************
* @fn      fnGet_Normal
*
* @brief   软件比对
*
* @param
*
* @return
*/
u8 fnAct_File(
    u32  OMD,        //OMD
    u8  *pSrc,    //parameter buffer
    u16 *parLen,     //parameter length ，已处理的参数数据长度
    u8  *pRetBuf,    //return result buffer
    u16 *retLen,      //return result buffer length
    u8  *pBuf
)
{
    OMD_Analyse_TypeDef *pOmdAys = (OMD_Analyse_TypeDef*)&OMD;
    u32 RechargCountTemp1, RechargCountTemp2;
    u8 keyNo, temp;
    u16  Len, i, len2;
    u8 *KeyBuf, *RnBuf, *DataBuf, *buf;

    if (pOmdAys->ActFlag == 10) //方法10 ，软件比对
    {
        if ((*pSrc++ != DTYPE_STRUCTURE) || (*pSrc++ != 5))
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if ((*pSrc++ != DTYPE_UINT8) || (*pSrc++ > 8)) //支持CPU个数少于等于8个
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        if (*pSrc++ != DTYPE_UINT8)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        keyNo = *pSrc++;  //密钥索引

        if (*pSrc++ != DTYPE_UINT32)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        RechargCountTemp1 = Std_Msb32DataGet(pSrc);   // 比对因子起始地址
        pSrc += 4;

        if (*pSrc++ != DTYPE_UINT32)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        RechargCountTemp2 = Std_Msb32DataGet(pSrc);        // 比对数据起始地址
        pSrc += 4;

        if (*pSrc++ != DTYPE_UINT16)
        {
            return DATA_ACCESS_RESULT_TYPE;
        }

        Len = Std_Msb16DataGet(pSrc);        // 待加密数据长度
        pSrc += 2;

        if (Len > 2000) //最大处理长度2000
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        if ((RechargCountTemp1 >= FlashAdMax) ||
            (RechargCountTemp2 >= FlashAdMax))
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        if (Len % 64) //待加密数据长度必须为 64 整数倍，否则电表返回异常应答“拒绝读写”
        {
            return DATA_ACCESS_RESULT_DENY;
        }

        KeyBuf = pBuf + 6;  //预留6字节放ESAM命令头
        RnBuf = pBuf + 6 + 8;
        DataBuf = pBuf + 6 + 8 + 16;

        buf = (u8 *)fnBufTemp_Alloc(2048);
        if (buf == NULL)
        {
            return DATA_ACCESS_RESULT_OTH;
        }
        Std_Memset(buf, 0, 2048);

        for (i = 0; i < 16; i++)
        {
            //-----地址1C~1F程序校验和,固定返回0----------------
            if ((RechargCountTemp1 + i) == 0x1c || (RechargCountTemp1 + i) == 0x1d || (RechargCountTemp1 + i) == 0x1e || (RechargCountTemp1 + i) == 0x1f)
            {
                *(buf + i) = 0;
            }
            else
            {
                *(buf + i) = *(Read_Flash + RechargCountTemp1 + i);
            }

            if ((RechargCountTemp1 + i) == FlashAdMax)
            {
                *(buf + i) = 0x80;
                Std_Memset(buf + i, 0x00, (15 - i));
                break;
            }
        }

        //----如果获取的比对因子中连续16字节为相同数据（例全00或全FF）时，
        //----电能表应返回安全认证异常应答“地址异常”----------
        /*
        if( (fnJudge_Value(buf , 0x00 , 16) == ERN_TRUE)||
            (fnJudge_Value(buf , 0xFF , 16) == ERN_TRUE) )
        {
            fnBufTemp_Free(buf);
            return DATA_ACCESS_RESULT_ADDERR;
        }*/

        //----提取比对因子-------------
        for (i = 0; i < 8; i++)
        {
            *(KeyBuf + i) = *(buf + i) ^ *(buf + i + 8);
        }

        //-----提取随机数------------
        for (i = 0; i < 64; i++)
        {
            if ((RechargCountTemp2 + i) == 0x1c || (RechargCountTemp2 + i) == 0x1d || (RechargCountTemp2 + i) == 0x1e || (RechargCountTemp2 + i) == 0x1f)
            {
                *(buf + i) = 0;
            }
            else
            {
                *(buf + i) = *(Read_Flash + RechargCountTemp2 + i);
            }
            if ((RechargCountTemp2 + i) >= FlashAdMax)
            {
                *(buf + i) = 0x80;
                Std_Memset(buf + i + 1, 0x00, (63 - i));
                break;
            }
        }
        for (i = 0; i < 16; i++)
        {
            *(RnBuf + i) = *(buf + i) ^ *(buf + i + 16) ^ *(buf + i + 32) ^ *(buf + i + 48); //Data5
        }

        //-----提取待加密数据------------
        for (i = 0; i < Len; i++)
        {
            if ((RechargCountTemp2 + i) == 0x1c || (RechargCountTemp2 + i) == 0x1d || (RechargCountTemp2 + i) == 0x1e || (RechargCountTemp2 + i) == 0x1f)
            {
                *(buf + i) = 0;
            }
            else
            {
                *(buf + i) = *(Read_Flash + RechargCountTemp2 + i);
            }
            if ((RechargCountTemp2 + i) >= FlashAdMax)
            {
                *(buf + i) = 0x80;
                Std_Memset(buf + i + 1, 0x00, (Len - 1 - i));
                break;
            }
        }

        len2 = Len / 4;
        for (i = 0; i < len2; i++)
        {
            *(DataBuf + i) = *(buf + i) ^ *(buf + i + len2) ^ *(buf + i + 2 * len2) ^  *(buf + i + 3 * len2) ; //Data10
        }

        //----800A48P2+Lc+分散因子+随机数+Data1------------------
        len2 += 24;
        *pBuf = 0x80;
        *(pBuf + 1) = 0x0A;
        *(pBuf + 2) = 0x48;
        *(pBuf + 3) = keyNo;
        *(pBuf + 4) = len2 / 256;
        *(pBuf + 5) = (u8)len2;
        if (fnEsamOp_Tx_Esam(buf, pBuf, &Len) == SUCCESS)
        {
            *pRetBuf++ = 0;
            *pRetBuf++ = 1;
            *retLen  += 2;
            temp = 1;
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, retLen, &temp, NULL, DTYPE_STRUCTURE);

            Std_MemRvsSelf(buf, Len);
            pRetBuf += fnDl698_asn1_build_Type(pRetBuf, retLen, buf, &Len, DTYPE_OCT_STR);

            fnBufTemp_Free(buf);
        }
        else
        {
            fnBufTemp_Free(buf);
            return DATA_ACCESS_RESULT_ESAMFAIL;
        }

        return DATA_ACCESS_RESULT_SUC;
    }
    else
    {
        return DATA_ACCESS_RESULT_DENY;
    }
}

/*********************************************************************
* @fn      fnGet_Normal
*
* @brief
*
* @param
*
* @return
*/

u8 fnGet_Normal(u32  OAD, u8  *uBuf, u8 *pRetBuf, u16 *Len,  u8  *blockRsp)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    u8 res = ERROR ;

    switch (pOadAys->OIA1)
    {
        case OIA1_ENERGY:    //电量类，class1
            res =  fnGet_Energy(OAD, uBuf, pRetBuf, Len, blockRsp);
            break;

        case OIA1_VAR:
            res = fnGet_Var(OAD, uBuf, pRetBuf, Len, blockRsp);
            break;

        case OIA1_EVENT:
            res = fnGet_EvtReport(OAD, uBuf, pRetBuf, Len, blockRsp);

            if (res == ERROR)
            {
                res = fnGet_EvtPara(OAD, uBuf, pRetBuf, Len, blockRsp);    //class7
            }

            if (res == ERROR)
            {
                res = fnGet_PhsEvtPara(OAD, uBuf, pRetBuf, Len, blockRsp);    //class24
            }

            break;

        case OIA1_PARA:
            res = fnGet_Para(OAD, uBuf, pRetBuf, Len, blockRsp);

            if (res == ERROR)
            {
                res = fnGet_DevicePara(OAD, uBuf, pRetBuf, Len, blockRsp);
            }

            if (res == ERROR)
            {
                res = fnGet_LinkPara(OAD, uBuf, pRetBuf, Len, blockRsp);
            }

            break;

        case OIA1_FREEZE:
            res = fnGet_FrzPara(OAD, uBuf, pRetBuf, Len, blockRsp);

            break;

        case OIA1_CONTROL:
            res = fnGet_Control(OAD, uBuf, pRetBuf, Len, blockRsp);

            break;

        case OIA1_INTERFACE:
            if ((pOadAys->OIA2 == OIA2_SAFE_MODE) && (pOadAys->OIB1 == 0) && (pOadAys->OIB2 == 0)) //OI = 0xF100
            {
                res =  fnGet_ESAMPara(OAD, uBuf, pRetBuf, Len, blockRsp);
            }
            else if ((pOadAys->OIA2 == OIA2_SAFE_MODE) && (pOadAys->OIB1 == 0) && (pOadAys->OIB2 == 1)) //OI = 0xF101
            {
                res =  fnGet_SafeModePara(OAD, uBuf, pRetBuf, Len, blockRsp);
            }
            else if (pOadAys->OIA2 == OIA2_INOUT_DEVICE)
            {
                res = fnGet_InOut_DevicePara(OAD, uBuf, pRetBuf, Len, blockRsp);
            }
            else if (pOadAys->OIA2 == OIA2_DISP)
            {
                res =  fnGet_LCDPara(OAD, uBuf, pRetBuf, Len);
            }

            break;

        default:
            return DATA_ACCESS_RESULT_UNAVA;
    }

    if (res == SUCCESS)
    {
        return DATA_ACCESS_RESULT_SUC;
    }
    else
    {
        return DATA_ACCESS_RESULT_UNAVA;
    }
}

/*********************************************************************
* @fn      fnSet_Normal
*
* @brief
*
* @param
*
* @return
**********************************************************************/
u8 fnSet_Normal(u32  OAD, u8  *pSrc, u8  *pParBuf, u16 *parLen)
{
    OAD_Analyse_TypeDef *pOadAys = (OAD_Analyse_TypeDef*)&OAD;
    u8 res = DATA_ACCESS_RESULT_UNAVA, temp[5] ;

    *parLen = fnDl698AL_GetData_Len(1, 0, pSrc);

    switch (pOadAys->OIA1)
    {
        case OIA1_VAR:
            res = fnSet_VarPara(OAD, pSrc, pParBuf);
            break;

        case OIA1_PARA:
            res = fnSet_Para(OAD, pSrc, pParBuf);
            break;

        case OIA1_EVENT:
            res = fnSet_EvtPara(OAD, pSrc, pParBuf);

            if (res != DATA_ACCESS_RESULT_SUC)
            {
                res = fnSet_PhsEventPara(OAD, pSrc, pParBuf);
            }

            break;

        case OIA1_FREEZE:

            res = fnSet_FrzPara(OAD, pSrc, pParBuf);

            break;

        case OIA1_CONTROL:
            res = fnSet_Control(OAD, pSrc, pParBuf);
            break;

        case OIA1_INTERFACE:
            if (pOadAys->OIA2 == OIA2_DISP)
            {
                res = fnSet_DispPara(OAD, pSrc, pParBuf);
            }
            else if (pOadAys->OIA2 == OIA2_SAFE_MODE)
            {
                res = fnSet_SafeModePara(OAD, pSrc, pParBuf);
            }

            break;

        default:
            break;
    }
    //---------------
    if (res == DATA_ACCESS_RESULT_SUC)
    {
        temp[0] = DTYPE_OAD;
        Std_Lsb32DataSet(&temp[1], OAD);
        //      fnEvent_Operation(FileItemInfoNum_Evt_Prg , EVTSTART, (u8 *)&temp[0] );
    }

    return res;
}

/*********************************************************************
* @fn      fnAct_Normal
*
* @brief   操作
*
* @param
*
* @return
**********************************************************************/
u8 fnAct_Normal(u32  OMD, u8  *pSrc, u16 *parLen, u8 *pRetBuf, u16 *retLen, u8 *pBuf)
{
    OMD_Analyse_TypeDef *pOmdAys = (OMD_Analyse_TypeDef*)&OMD;
    OI_Analyse_TypeDef *pOIAys = (OI_Analyse_TypeDef*)&pOmdAys->OI;

    u8 res = DATA_ACCESS_RESULT_UNAVA ;
    u16 RtExeFlag;

    switch (pOIAys->OIA1)
    {
        case OIA1_VAR:
            res = fnAct_VarPara(OMD, parLen, pSrc);
            break;

        case OIA1_EVENT:
            res = fnAct_EvtPara(OMD, pSrc, parLen, pBuf);
            break;

        case OIA1_PARA:
            if (pOmdAys->OI == 0x4000)
            {
                res = fnAct_BroatcastTime(pOmdAys->ActMeth, pOmdAys->ActFlag,  parLen, pSrc);
            }
            else if (pOmdAys->OI == 0x4300)
            {
                res = fnAct_Clear(pOmdAys->ActMeth, pOmdAys->ActFlag,  parLen, pSrc);
            }
            else if (pOmdAys->OI == 0x4804)
            {
                res = fnAct_WavePara(pOmdAys->ActMeth, pOmdAys->ActFlag,  parLen, pSrc);
            }
            else if (pOmdAys->OI == 0x4805)
            {
                res = fnAct_HalfIrmsPara(pOmdAys->ActMeth, pOmdAys->ActFlag,  parLen, pSrc);
            }

            break;

        case OIA1_FREEZE:
            res = fnAct_FrzPara(OMD, pSrc, parLen, pBuf);
            break;

        case OIA1_CONTROL:
            if ((pOmdAys->OI == 0x8000) || (pOmdAys->OI == 0x8001))
            {
                res = fnAct_GataOp(OMD, pSrc, parLen, pRetBuf, retLen, &RtExeFlag);
            }
            break;

        case OIA1_INTERFACE:
            if (pOmdAys->OI == 0xF100)
            {
                res = fnAct_EsamOp(OMD, pSrc, parLen, pRetBuf, retLen, pBuf);
            }
            else if (pOmdAys->OI == 0xF101)
            {
                res = fnAct_SafeModePara(pOmdAys->ActMeth, pOmdAys->ActFlag,  parLen, pSrc);
            }
            else if ((pOmdAys->OI & 0xFFF0) == 0xF200)
            {
                res = fnAct_InOut_DevicePara(pOIAys->OIB2, pOmdAys->ActMeth, pOmdAys->ActFlag, parLen, pSrc);
            }
            else if ((pOmdAys->OI == 0xF300) || (pOmdAys->OI == 0xF301))
            {
                res = fnAct_DispPara(OMD, parLen, pSrc);
            }
            else if (pOmdAys->OI == 0xF001)
            {
                res = fnAct_File(OMD, pSrc, parLen, pRetBuf, retLen, pBuf);
            }
            else
            {
                *parLen = fnDl698AL_GetData_Len(1, 0, pSrc);
            }

            break;

        default:
            *parLen = fnDl698AL_GetData_Len(1, 0, pSrc);
            break;
    }
    //---------------

    return res;
}
