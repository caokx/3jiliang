
#define  _ENERGY_GLOBALS
#include <App.h>

/*********************************************************************************************************
** Function name:       EnergyOpConst
** Descriptions:        ���ܳ����ļ�����ӵĵ�������洢��ͬһ�ļ���
**                      FileId_CurEgSh,FileId_CurEgBackUp�ļ���ƫ�Ƶ�ַ����һ��
*********************************************************************************************************/
#if(nPhs==ThreePhs)
const sEnergy_Operate_TypeDef EnergyOpConst[] =
{
    {PtPEg, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.PtPEgSh[0], FileItemInfoOffAddr_EgSh_PtPEgSh, FileItemInfoLen_EgSh_PtPEgSh, (u8 *) &Energy.PubData.PtPEgShCrc   },
    {NtPEg, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.NtPEgSh[0], FileItemInfoOffAddr_EgSh_NtPEgSh, FileItemInfoLen_EgSh_NtPEgSh, (u8 *) &Energy.PubData.NtPEgShCrc   },

    {Qd1QEg, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd1QEgSh[0], FileItemInfoOffAddr_EgSh_Qd1QEgSh, FileItemInfoLen_EgSh_Qd1QEgSh, (u8 *) &Energy.PubData.Qd1QEgShCrc  },
    {Qd2QEg, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd2QEgSh[0], FileItemInfoOffAddr_EgSh_Qd2QEgSh, FileItemInfoLen_EgSh_Qd2QEgSh, (u8 *) &Energy.PubData.Qd2QEgShCrc  },
    {Qd3QEg, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd3QEgSh[0], FileItemInfoOffAddr_EgSh_Qd3QEgSh, FileItemInfoLen_EgSh_Qd3QEgSh, (u8 *) &Energy.PubData.Qd3QEgShCrc  },
    {Qd4QEg, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd4QEgSh[0], FileItemInfoOffAddr_EgSh_Qd4QEgSh, FileItemInfoLen_EgSh_Qd4QEgSh, (u8 *) &Energy.PubData.Qd4QEgShCrc  },

    //-------
    {PtPEgA, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.PtPEgSha, FileItemInfoOffAddr_EgSh_PtPEgSha, FileItemInfoLen_EgSh_PtPEgSha, (u8 *) &Energy.PubData.PtPEgShaCrc  },
    {NtPEgA, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.NtPEgSha, FileItemInfoOffAddr_EgSh_NtPEgSha, FileItemInfoLen_EgSh_NtPEgSha, (u8 *) &Energy.PubData.NtPEgShaCrc  },

    {Qd1QEgA, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd1QEgSha, FileItemInfoOffAddr_EgSh_Qd1QEgSha, FileItemInfoLen_EgSh_Qd1QEgSha, (u8 *) &Energy.PubData.Qd1QEgShaCrc },
    {Qd2QEgA, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd2QEgSha, FileItemInfoOffAddr_EgSh_Qd2QEgSha, FileItemInfoLen_EgSh_Qd2QEgSha, (u8 *) &Energy.PubData.Qd2QEgShaCrc },
    {Qd3QEgA, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd3QEgSha, FileItemInfoOffAddr_EgSh_Qd3QEgSha, FileItemInfoLen_EgSh_Qd3QEgSha, (u8 *) &Energy.PubData.Qd3QEgShaCrc },
    {Qd4QEgA, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd4QEgSha, FileItemInfoOffAddr_EgSh_Qd4QEgSha, FileItemInfoLen_EgSh_Qd4QEgSha, (u8 *) &Energy.PubData.Qd4QEgShaCrc },
    //------
    {PtPEgB, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.PtPEgShb, FileItemInfoOffAddr_EgSh_PtPEgShb, FileItemInfoLen_EgSh_PtPEgShb, (u8 *) &Energy.PubData.PtPEgShbCrc  },
    {NtPEgB, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.NtPEgShb, FileItemInfoOffAddr_EgSh_NtPEgShb, FileItemInfoLen_EgSh_NtPEgShb, (u8 *) &Energy.PubData.NtPEgShbCrc  },

    {Qd1QEgB, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd1QEgShb, FileItemInfoOffAddr_EgSh_Qd1QEgShb, FileItemInfoLen_EgSh_Qd1QEgShb, (u8 *) &Energy.PubData.Qd1QEgShbCrc },
    {Qd2QEgB, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd2QEgShb, FileItemInfoOffAddr_EgSh_Qd2QEgShb, FileItemInfoLen_EgSh_Qd2QEgShb, (u8 *) &Energy.PubData.Qd2QEgShbCrc },
    {Qd3QEgB, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd3QEgShb, FileItemInfoOffAddr_EgSh_Qd3QEgShb, FileItemInfoLen_EgSh_Qd3QEgShb, (u8 *) &Energy.PubData.Qd3QEgShbCrc },
    {Qd4QEgB, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd4QEgShb, FileItemInfoOffAddr_EgSh_Qd4QEgShb, FileItemInfoLen_EgSh_Qd4QEgShb, (u8 *) &Energy.PubData.Qd4QEgShbCrc },
    //-------
    {PtPEgC, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.PtPEgShc, FileItemInfoOffAddr_EgSh_PtPEgShc, FileItemInfoLen_EgSh_PtPEgShc, (u8 *) &Energy.PubData.PtPEgShcCrc  },
    {NtPEgC, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.NtPEgShc, FileItemInfoOffAddr_EgSh_NtPEgShc, FileItemInfoLen_EgSh_NtPEgShc, (u8 *) &Energy.PubData.NtPEgShcCrc  },

    {Qd1QEgC, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd1QEgShc, FileItemInfoOffAddr_EgSh_Qd1QEgShc, FileItemInfoLen_EgSh_Qd1QEgShc, (u8 *) &Energy.PubData.Qd1QEgShcCrc },
    {Qd2QEgC, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd2QEgShc, FileItemInfoOffAddr_EgSh_Qd2QEgShc, FileItemInfoLen_EgSh_Qd2QEgShc, (u8 *) &Energy.PubData.Qd2QEgShcCrc },
    {Qd3QEgC, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd3QEgShc, FileItemInfoOffAddr_EgSh_Qd3QEgShc, FileItemInfoLen_EgSh_Qd3QEgShc, (u8 *) &Energy.PubData.Qd3QEgShcCrc },
    {Qd4QEgC, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd4QEgShc, FileItemInfoOffAddr_EgSh_Qd4QEgShc, FileItemInfoLen_EgSh_Qd4QEgShc, (u8 *) &Energy.PubData.Qd4QEgShcCrc },

    {PtFEg, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.PtFEgSh[0], FileItemInfoOffAddr_EgSh_PtFEgSh, FileItemInfoLen_EgSh_PtFEgSh, (u8 *) &Energy.PubData.PtFEgShCrc   },
    {NtFEg, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.NtFEgSh[0], FileItemInfoOffAddr_EgSh_PtFEgSh, FileItemInfoLen_EgSh_NtFEgSh, (u8 *) &Energy.PubData.NtFEgShCrc   },

    {PtHEg, HConst, (u8 *) &Energy.PubPara.HUnit, (u8 *) &Energy.PubData.PtHEgSh[0], FileItemInfoOffAddr_EgSh_PtHEgSh, FileItemInfoLen_EgSh_PtHEgSh, (u8 *) &Energy.PubData.PtHEgShCrc   },
    {NtHEg, HConst, (u8 *) &Energy.PubPara.HUnit, (u8 *) &Energy.PubData.NtHEgSh[0], FileItemInfoOffAddr_EgSh_NtHEgSh, FileItemInfoLen_EgSh_NtHEgSh, (u8 *) &Energy.PubData.NtHEgShCrc   },
};
#else
const sEnergy_Operate_TypeDef EnergyOpConst[] =
{
    {PtPEg, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.PtPEgSh[0], FileItemInfoOffAddr_EgSh_PtPEgSh, FileItemInfoLen_EgSh_PtPEgSh, (u8 *) &Energy.PubData.PtPEgShCrc   },
    {NtPEg, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.NtPEgSh[0], FileItemInfoOffAddr_EgSh_NtPEgSh, FileItemInfoLen_EgSh_NtPEgSh, (u8 *) &Energy.PubData.NtPEgShCrc   },

    {Qd1QEg, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd1QEgSh[0], FileItemInfoOffAddr_EgSh_Qd1QEgSh, FileItemInfoLen_EgSh_Qd1QEgSh, (u8 *) &Energy.PubData.Qd1QEgShCrc   },
    {Qd2QEg, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd2QEgSh[0], FileItemInfoOffAddr_EgSh_Qd2QEgSh, FileItemInfoLen_EgSh_Qd2QEgSh, (u8 *) &Energy.PubData.Qd2QEgShCrc   },
    {Qd3QEg, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd3QEgSh[0], FileItemInfoOffAddr_EgSh_Qd3QEgSh, FileItemInfoLen_EgSh_Qd3QEgSh, (u8 *) &Energy.PubData.Qd3QEgShCrc   },
    {Qd4QEg, QConst, (u8 *) &Energy.PubPara.QUnit, (u8 *) &Energy.PubData.Qd4QEgSh[0], FileItemInfoOffAddr_EgSh_Qd4QEgSh, FileItemInfoLen_EgSh_Qd4QEgSh, (u8 *) &Energy.PubData.Qd4QEgShCrc   },

    {PtFEg, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.PtFEgSh[0], FileItemInfoOffAddr_EgSh_PtFEgSh, FileItemInfoLen_EgSh_PtFEgSh, (u8 *) &Energy.PubData.PtFEgShCrc   },
    {NtFEg, PConst, (u8 *) &Energy.PubPara.PUnit, (u8 *) &Energy.PubData.NtFEgSh[0], FileItemInfoOffAddr_EgSh_PtFEgSh, FileItemInfoLen_EgSh_NtFEgSh, (u8 *) &Energy.PubData.NtFEgShCrc   },

    {PtHEg, HConst, (u8 *) &Energy.PubPara.HUnit, (u8 *) &Energy.PubData.PtHEgSh[0], FileItemInfoOffAddr_EgSh_PtHEgSh, FileItemInfoLen_EgSh_PtHEgSh, (u8 *) &Energy.PubData.PtHEgShCrc   },
    {NtHEg, HConst, (u8 *) &Energy.PubPara.HUnit, (u8 *) &Energy.PubData.NtHEgSh[0], FileItemInfoOffAddr_EgSh_NtHEgSh, FileItemInfoLen_EgSh_NtHEgSh, (u8 *) &Energy.PubData.NtHEgShCrc   },
};
#endif

sFsEgSh_HighTypeDef fnEnergy_GrpAddEg(sFsEgSh_HighTypeDef *Eg, sFsEgSh_HighTypeDef *DeltaEg, u8 DeltaEgSign)
{
    sFsEgSh_HighTypeDef Result;

    s64 s64_data1 = 0, s64_data2 = 0;

    s64_data1 = ((s64)(Eg->Dat0)) + (((s64)(Eg->Dat1)) << 32);
    s64_data2 = ((s64)(DeltaEg->Dat0)) + (((s64)(DeltaEg->Dat1)) << 32);

    if (DeltaEgSign == 0)
    {
        s64_data1 += s64_data2;
    }
    else
    {
        s64_data1 -= s64_data2;
    }

    Result.Dat1 = (u32)(s64_data1 >> 32);
    Result.Dat0 = (u32)s64_data1;

    *Eg = Result;
    return (Result);
}

/*********************************************************************************************************
** Function name:
** Descriptions:
** input parameters:    Eg_InData:����������ݣ�6λС��
**              Datatype:ת���������͸�ʽ
** output parameters:   Eg_OutData:��������ĵ������ݸ�ʽ��4�ֽ�
** Returned value:      None
*********************************************************************************************************/
void fnEnergy_Change(u8 *Eg_InData, u8* Eg_OutData,     u8 FractionE)
{
    s32 data32 = 0;
    s64 data64 = 0;
    sFsEgSh_HighTypeDef *pEg = (sFsEgSh_HighTypeDef *)Eg_InData;

    if (FractionE == Energy_HEX2FractionE) //������ת����4�ֽ�hex��2λС����ʽ
    {
        data64 = ((s64)(pEg->Dat0)) + (((s64)(pEg->Dat1)) << 32);

        data64 /= 10000;

        data32 = (u32)data64;
        Std_Memcpy(Eg_OutData, (u8 *)&data32, 4);
    }
    else if (FractionE == Energy_HEX4FractionE)
    {
        data64 = ((s64)(pEg->Dat0)) + (((s64)(pEg->Dat1)) << 32);

        data64 /= 100;

        Std_Memcpy(Eg_OutData, (u8 *)&data64, 8);
    }
    else                             //8�ֽڣ�4λС��,hex��ʽ
    {
        Std_Memcpy(Eg_OutData, Eg_InData, 8);
    }
}

/*********************************************************************************************************
** Function name:      fnEnergy_Mantissa
** Descriptions:        �����β��
** input parameters:    Eg_InData:����������ݣ�6λС��
**
** output parameters:   Eg_OutData:��������ĵ������ݸ�ʽ��4�ֽ�
** Returned value:      None
*********************************************************************************************************/
void fnEnergy_Mantissa(u8 *Eg_InData,   u8* Eg_OutData)
{
    s64 data64 = 0;
    s8 data8 = 0;
    sFsEgSh_HighTypeDef *pEg = (sFsEgSh_HighTypeDef *)Eg_InData;

    data64 = ((s64)(pEg->Dat0)) + (((s64)(pEg->Dat1)) << 32);
    data8 = data64 % 100;
    if (data8 < 0)
    {
        data8 = -data8;
    }

    *Eg_OutData = (u8)data8;
}

/*********************************************************************************************************
** Function name:       fnEnergy_PluseParaInit
** Descriptions:        �������峣����ʼ������0.0001��Ϊ��λ
**
**
** input parameters:    NONE
**
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void fnEnergy_PluseParaInit(void)
{
    u32 ConstE, ConstQ;

    MeasureFirmPara.HighPulseRate = DefaultHighPulseRate;

    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_PExpression, &Energy.PubPara.PExpression, 3);
    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_PConstE, (u8 *)&ConstE, 4);

    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_QConstE, (u8 *)&ConstQ, 4);

    //-------�ߴ���---------------------
    //if( (ConstE == 0)||(ConstE == 0xFFFFFFFF)||((ConstE*MeasureFirmPara.HighPulseRate) < 1000) )
    {
        ConstE = MeterConst * MeasureFirmPara.HighPulseRate;
        Energy.PubPara.PExpression = 0x05;
        ConstQ = MeterConst * MeasureFirmPara.HighPulseRate;
    }

    //  Energy.PubPara.PPlsDeltaE = ConstE*MeasureFirmPara.HighPulseRate/1000 ;

    Energy.PubPara.PPlsDeltaE = 1;
    Energy.PubPara.PUnit = 1000000 / ConstE; //���ܰ�6λС���洢

    Energy.PubPara.QPlsDeltaE = 1;
    Energy.PubPara.QUnit = 1000000 / ConstQ; //���ܰ�6λС���洢

    Energy.PubPara.HPlsDeltaE = 1;
    Energy.PubPara.HUnit = 1000000 / HarmonicConst; //���ܰ�6λС���洢

    fnCrc_Check(0, (u8 *)&Energy.PubPara.PExpression, 15, (u8 *)&Energy.PubPara.Crc);
}

/*********************************************************************************************************
** Function name:       fnEnergy_DataInit
** Descriptions:        ����ģ���ʼ��,������㼰��һ���ϵ��ʼ�����е������ݣ�ˢ��E2
** input parameters:    NONE
**
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
void fnEnergy_DataInit(void)
{
    u8 i;

    //---------��������------------
    Std_Memset(&Energy.PubData, 0x00, sizeof(Energy.PubData));

    for (i = 0; i < AllPEg; i++)
    {
        fnCrc_Check(0, EnergyOpConst[i].EgRamAd, EnergyOpConst[i].EgLen - 2, EnergyOpConst[i].EgCrcRamAd);
        fnFile_Write(FileId_EgSh, EnergyOpConst[i].EgRomAd, EnergyOpConst[i].EgRamAd, EnergyOpConst[i].EgLen);
        fnFile_Write(FileId_BackUpEgSh, EnergyOpConst[i].EgRomAd, EnergyOpConst[i].EgRamAd, EnergyOpConst[i].EgLen);
        fnWDT_Restart();
    }

    fnEnergy_PluseParaInit();

    // ����������
    Std_Memset((u8 *)&Energy.PriData.PieceEg[0], 0x00, sizeof(sEgPiece_TypeDef) - 2);
    fnCrc_Check(0, (u8 *)&Energy.PriData.PieceEg[0], sizeof(sEgPiece_TypeDef) - 2, (u8 *)&Energy.PriData.Crc);
    fnFile_Write(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_EgPiece, (u8 *)&Energy.PriData.PieceEg[0], FileItemInfoLen_PowDn_EgPiece);

    Std_Memset((u8 *)&EgMoney.PubData.CurSurplusEg, 0x00, sizeof(EgMoney.PubData)); //����ʣ�����/�������
    //----������������й��ܵ���-------
    fnCrc_Check(0, (u8 *)&EgMoney.PubData.CurApplyEg, 8, (u8 *)&EgMoney.PubDataCrc.CurApplyEg);

    Std_Memset((u8 *)&CurApplyEg, 0x00, sizeof(sCurApplyEgSh_TypeDef));
    fnCrc_Check(0, (u8 *)&CurApplyEg.CurYearEgSh, sizeof(sFsEgSh_HighTypeDef), (u8 *)&CurApplyEg.CurYearEgShCrc);
    fnCrc_Check(0, (u8 *)&CurApplyEg.CurMonthEgSh, sizeof(sFsEgSh_HighTypeDef), (u8 *)&CurApplyEg.CurMonthEgShCrc);
    fnCrc_Check(0, (u8 *)&CurApplyEg.CurDayEgSh, sizeof(sFsEgSh_HighTypeDef), (u8 *)&CurApplyEg.CurDayEgShCrc);

    #if(METERTYPE == 2)
    fnCrc_Check(0, (u8 *)&EgMoney.PubData.CurSurplusMoney, 12, (u8 *)&EgMoney.PubDataCrc.CurSurplusMoney);
    fnCrc_Check(0, (u8 *)&EgMoney.PubData.CurSurplusEg, 8, (u8 *)&EgMoney.PubDataCrc.CurSurplusEg);
    #endif
    fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_EgMoney, (u8 *)&EgMoney.PubData.CurApplyEg, sizeof(EgMoney.PubData));
    //fnFile_Write(FileId_BackUpCurMoney , FileItemInfoLen_BackUpCurMoney_CurSurplusMoney, (u8 *)&EgMoney.PubData.CurApplyEg, sizeof(EgMoney.PubData) );
    fnFile_Clr(FileId_BackUpCurMoney);

    #if(METERTYPE == 2)
    EgMoney.PubPara.tSubEsamMoney = 15;
    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_PT, (u8 *)&EgMoney.PubPara.MeterPT, 3);
    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_CT, (u8 *)&EgMoney.PubPara.MeterCT, 3);
    fnCrc_Check(0, (u8 *)&EgMoney.PubPara.MeterCT, 6, (u8 *)&EgMoney.PubPara.Crc);
    #endif
    fnWDT_Restart();
}

/*****************************************************************************
** Function name:void fnEnergy_CRCCheck(void)
**
** Description:�����ļ�RAM��Ч���ж��Ƿ���ȷ
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/

void fnEnergy_CRCCheck(void)
{
    u8 i ;

    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }

    for (i = 0; i < (sizeof(EnergyOpConst) / sizeof(EnergyOpConst[0])); i++)
    {
        if (fnCrc_Check(1, EnergyOpConst[i].EgRamAd, EnergyOpConst[i].EgLen - 2, EnergyOpConst[i].EgCrcRamAd))
        {
            fnFile_Read(FileId_EgSh, EnergyOpConst[i].EgRomAd, EnergyOpConst[i].EgRamAd, EnergyOpConst[i].EgLen);
            if (fnCrc_Check(1, EnergyOpConst[i].EgRamAd, EnergyOpConst[i].EgLen - 2, EnergyOpConst[i].EgCrcRamAd))      //�������������ݴ��󣬶�����������
            {
                fnFile_Read(FileId_BackUpEgSh, EnergyOpConst[i].EgRomAd, EnergyOpConst[i].EgRamAd, EnergyOpConst[i].EgLen);
            }
        }
    }
    if (fnCrc_Check(1, (u8 *)&Energy.PubPara.PExpression, 15, (u8 *)&Energy.PubPara.Crc))
    {
        fnEnergy_PluseParaInit();
    }

    if (fnCrc_Check(1, (u8 *)&Energy.PriData.PieceEg[0], sizeof(sEgPiece_TypeDef) - 2, (u8 *)&Energy.PriData.Crc))
    {
        fnFile_Read(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_EgPiece, (u8 *)&Energy.PriData.PieceEg[0], FileItemInfoLen_PowDn_EgPiece);
    }
}

//*********************************************************************************
// �������� fnEnergy_PulseCalc
// ���룺   NONE
// ���أ�   NONE
// ������   ����ȡ������β���ۼӵ������ʵ�����
// ע�ͣ�
//*********************************************************************************
void fnEnergy_PulseCalc(void)
{
    u8  Quadrant;
    u8  i;

    Quadrant = (MeasureRms.PubData.PDirect >> 0) & 0x11;

    if (MeasureRegTmp.Pulse_Eg[0])
    {
        // �й�����
        if ((Quadrant == QUADRANT_I) || (Quadrant == QUADRANT_IV))  //һ��������
        {
            Energy.PriData.PieceEg[PieceEgOffAddr_PtPEg] += MeasureRegTmp.Pulse_Eg[0];
        }
        else if ((Quadrant == QUADRANT_II) || (Quadrant == QUADRANT_III))  //����������
        {
            Energy.PriData.PieceEg[PieceEgOffAddr_NtPEg] += MeasureRegTmp.Pulse_Eg[0];
        }
        MeasureRegTmp.Pulse_Eg[0] = 0;
    }
    if (MeasureRegTmp.Pulse_Eg[1])
    {
        // �޹�����
        if (Quadrant == QUADRANT_I) //һ����
        {
            Energy.PriData.PieceEg[PieceEgOffAddr_Qd1QEg] += MeasureRegTmp.Pulse_Eg[1];
        }
        if (Quadrant == QUADRANT_II) //������
        {
            Energy.PriData.PieceEg[PieceEgOffAddr_Qd2QEg] += MeasureRegTmp.Pulse_Eg[1];
        }
        if (Quadrant == QUADRANT_III) //������
        {
            Energy.PriData.PieceEg[PieceEgOffAddr_Qd3QEg] += MeasureRegTmp.Pulse_Eg[1];
        }
        if (Quadrant == QUADRANT_IV) //������
        {
            Energy.PriData.PieceEg[PieceEgOffAddr_Qd4QEg] += MeasureRegTmp.Pulse_Eg[1];
        }
        MeasureRegTmp.Pulse_Eg[1] = 0;
    }

    for (i = 0; i < 3; i++)
    {
        Quadrant = (MeasureRms.PubData.PDirect >> (i + 1)) & 0x11;
        if (MeasureRegTmp.Pulse_Eg[3 + i * 3])      // �����й�
        {
            // �й�����
            if ((Quadrant == QUADRANT_I) || (Quadrant == QUADRANT_IV))  //һ��������
            {
                Energy.PriData.PieceEg[PieceEgOffAddr_PtPEgA + i * 6] += MeasureRegTmp.Pulse_Eg[3 + i * 3];
            }
            else if ((Quadrant == QUADRANT_II) || (Quadrant == QUADRANT_III))  //����������
            {
                Energy.PriData.PieceEg[PieceEgOffAddr_NtPEgA + i * 6] += MeasureRegTmp.Pulse_Eg[3 + i * 3];
            }
            MeasureRegTmp.Pulse_Eg[3 + i * 3] = 0;
        }
        if (MeasureRegTmp.Pulse_Eg[4 + i * 3])  // �����޹�
        {
            // �޹�����
            if (Quadrant == QUADRANT_I) //һ����
            {
                Energy.PriData.PieceEg[PieceEgOffAddr_Qd1QEgA + i * 6] += MeasureRegTmp.Pulse_Eg[4 + i * 3];
            }
            if (Quadrant == QUADRANT_II) //������
            {
                Energy.PriData.PieceEg[PieceEgOffAddr_Qd2QEgA + i * 6] += MeasureRegTmp.Pulse_Eg[4 + i * 3];
            }
            if (Quadrant == QUADRANT_III) //������
            {
                Energy.PriData.PieceEg[PieceEgOffAddr_Qd3QEgA + i * 6] += MeasureRegTmp.Pulse_Eg[4 + i * 3];
            }
            if (Quadrant == QUADRANT_IV) //������
            {
                Energy.PriData.PieceEg[PieceEgOffAddr_Qd4QEgA + i * 6] += MeasureRegTmp.Pulse_Eg[4 + i * 3];
            }
            MeasureRegTmp.Pulse_Eg[4 + i * 3] = 0;
        }
    }

    // ��������
    if (MeasureRegTmp.Pulse_Eg[12])
    {
        Energy.PriData.PieceEg[PieceEgOffAddr_PtFEg] += MeasureRegTmp.Pulse_Eg[12];

        MeasureRegTmp.Pulse_Eg[12] = 0;
    }
    if (MeasureRegTmp.Pulse_Eg[13])
    {
        Energy.PriData.PieceEg[PieceEgOffAddr_NtFEg] += MeasureRegTmp.Pulse_Eg[13];

        MeasureRegTmp.Pulse_Eg[13] = 0;
    }

    // г������
    Energy.PriData.PieceEg[PieceEgOffAddr_PtHEg] = D2F->D2FE[1];
    Energy.PriData.PieceEg[PieceEgOffAddr_NtHEg] = D2F->D2FE[0];

    fnCrc_Check(0, (u8 *)&Energy.PriData.PieceEg[0], sizeof(sEgPiece_TypeDef) - 2, (u8 *)&Energy.PriData.Crc);
}

//*********************************************************************************
// �������� fnEnergy_AllPEgCalc
// Mode:   ����й����ܼ���ģʽ
// Buf :   ��ȡ��������й�����
// ������   ��������й�����
// ע�ͣ�
//*********************************************************************************
void fnEnergy_AllPEgCalc(u8 Mode, u8 *Buf)
{
    u8  i;
    sFsEgSh_HighTypeDef *AllPEgSh;

    AllPEgSh = (sFsEgSh_HighTypeDef *)Buf;

    for (i = 0; i < (Bkgrd.PubData.nFl + 1); i++)
    {
        AllPEgSh->Dat0 = 0;
        AllPEgSh->Dat1 = 0;
        if (Mode & 0x01)
        {
            *AllPEgSh = fnEnergy_GrpAddEg(AllPEgSh, &Energy.PubData.PtPEgSh[i], 0);
        }
        if (Mode & 0x02)
        {
            *AllPEgSh = fnEnergy_GrpAddEg(AllPEgSh, &Energy.PubData.PtPEgSh[i], 1);
        }
        if (Mode & 0x04)
        {
            *AllPEgSh = fnEnergy_GrpAddEg(AllPEgSh, &Energy.PubData.NtPEgSh[i], 0);
        }
        if (Mode & 0x08)
        {
            *AllPEgSh = fnEnergy_GrpAddEg(AllPEgSh, &Energy.PubData.NtPEgSh[i], 1);
        }

        AllPEgSh++;
    }
}

//*********************************************************************************
// �������� fnEnergy_PtQEgCalc
// ���룺   ����޹�1������
// ���أ�   NONE
// ������   ��������޹�1����
// ע�ͣ�
//*********************************************************************************
#if(nPhs==ThreePhs)
void fnEnergy_PtQEgCalc(u8 Mode, u8 *Buf)
{
    u8  i;
    sFsEgSh_HighTypeDef *PtQEgSh;

    PtQEgSh = (sFsEgSh_HighTypeDef *)Buf;

    for (i = 0; i < (Bkgrd.PubData.nFl + 1); i++)
    {
        PtQEgSh->Dat0 = 0;
        PtQEgSh->Dat1 = 0;
        if (Mode & 0x01)
        {
            *PtQEgSh = fnEnergy_GrpAddEg(PtQEgSh, &Energy.PubData.Qd1QEgSh[i], 0);
        }
        if (Mode & 0x02)
        {
            *PtQEgSh = fnEnergy_GrpAddEg(PtQEgSh, &Energy.PubData.Qd1QEgSh[i], 1);
        }
        if (Mode & 0x04)
        {
            *PtQEgSh = fnEnergy_GrpAddEg(PtQEgSh, &Energy.PubData.Qd2QEgSh[i], 0);
        }
        if (Mode & 0x08)
        {
            *PtQEgSh = fnEnergy_GrpAddEg(PtQEgSh, &Energy.PubData.Qd2QEgSh[i], 1);
        }
        if (Mode & 0x10)
        {
            *PtQEgSh = fnEnergy_GrpAddEg(PtQEgSh, &Energy.PubData.Qd3QEgSh[i], 0);
        }
        if (Mode & 0x20)
        {
            *PtQEgSh = fnEnergy_GrpAddEg(PtQEgSh, &Energy.PubData.Qd3QEgSh[i], 1);
        }
        if (Mode & 0x40)
        {
            *PtQEgSh = fnEnergy_GrpAddEg(PtQEgSh, &Energy.PubData.Qd4QEgSh[i], 0);
        }
        if (Mode & 0x80)
        {
            *PtQEgSh = fnEnergy_GrpAddEg(PtQEgSh, &Energy.PubData.Qd4QEgSh[i], 1);
        }

        PtQEgSh++;
    }
}

//*********************************************************************************
// �������� fnEnergy_NtQEgCalc
// ���룺   ����޹�2������
// ���أ�   NONE
// ������   ��������޹�2����
// ע�ͣ�
//*********************************************************************************
void fnEnergy_NtQEgCalc(u8 Mode, u8 *Buf)
{
    u8  i;
    sFsEgSh_HighTypeDef *NtQEgSh;

    NtQEgSh = (sFsEgSh_HighTypeDef *)Buf;

    for (i = 0; i < (Bkgrd.PubData.nFl + 1); i++)
    {
        NtQEgSh->Dat0 = 0;
        NtQEgSh->Dat1 = 0;
        if (Mode & 0x01)
        {
            *NtQEgSh = fnEnergy_GrpAddEg(NtQEgSh, &Energy.PubData.Qd1QEgSh[i], 0);
        }
        if (Mode & 0x02)
        {
            *NtQEgSh = fnEnergy_GrpAddEg(NtQEgSh, &Energy.PubData.Qd1QEgSh[i], 1);
        }
        if (Mode & 0x04)
        {
            *NtQEgSh = fnEnergy_GrpAddEg(NtQEgSh, &Energy.PubData.Qd2QEgSh[i], 0);
        }
        if (Mode & 0x08)
        {
            *NtQEgSh = fnEnergy_GrpAddEg(NtQEgSh, &Energy.PubData.Qd2QEgSh[i], 1);
        }
        if (Mode & 0x10)
        {
            *NtQEgSh = fnEnergy_GrpAddEg(NtQEgSh, &Energy.PubData.Qd3QEgSh[i], 0);
        }
        if (Mode & 0x20)
        {
            *NtQEgSh = fnEnergy_GrpAddEg(NtQEgSh, &Energy.PubData.Qd3QEgSh[i], 1);
        }
        if (Mode & 0x40)
        {
            *NtQEgSh = fnEnergy_GrpAddEg(NtQEgSh, &Energy.PubData.Qd4QEgSh[i], 0);
        }
        if (Mode & 0x80)
        {
            *NtQEgSh = fnEnergy_GrpAddEg(NtQEgSh, &Energy.PubData.Qd4QEgSh[i], 1);
        }

        NtQEgSh++;
    }
}

//*********************************************************************************
// �������� fnEnergy_PtQEgaCalc
// ���룺   A������޹�1������
// ���أ�   NONE
// ������   ����A������޹�1����
// ע�ͣ�
//*********************************************************************************
void fnEnergy_PtQEgaCalc(u8 Mode, u8 *Buf)
{
    sFsEgSh_HighTypeDef *PtQEgSha;

    PtQEgSha = (sFsEgSh_HighTypeDef *)Buf;

    PtQEgSha->Dat0 = 0;
    PtQEgSha->Dat1 = 0;

    if (Mode & 0x01)
    {
        *PtQEgSha = fnEnergy_GrpAddEg(PtQEgSha, &Energy.PubData.Qd1QEgSha, 0);
    }
    if (Mode & 0x02)
    {
        *PtQEgSha = fnEnergy_GrpAddEg(PtQEgSha, &Energy.PubData.Qd1QEgSha, 1);
    }
    if (Mode & 0x04)
    {
        *PtQEgSha = fnEnergy_GrpAddEg(PtQEgSha, &Energy.PubData.Qd2QEgSha, 0);
    }
    if (Mode & 0x08)
    {
        *PtQEgSha = fnEnergy_GrpAddEg(PtQEgSha, &Energy.PubData.Qd2QEgSha, 1);
    }
    if (Mode & 0x10)
    {
        *PtQEgSha = fnEnergy_GrpAddEg(PtQEgSha, &Energy.PubData.Qd3QEgSha, 0);
    }
    if (Mode & 0x20)
    {
        *PtQEgSha = fnEnergy_GrpAddEg(PtQEgSha, &Energy.PubData.Qd3QEgSha, 1);
    }
    if (Mode & 0x40)
    {
        *PtQEgSha = fnEnergy_GrpAddEg(PtQEgSha, &Energy.PubData.Qd4QEgSha, 0);
    }
    if (Mode & 0x80)
    {
        *PtQEgSha = fnEnergy_GrpAddEg(PtQEgSha, &Energy.PubData.Qd4QEgSha, 1);
    }
}

//*********************************************************************************
// �������� fnEnergy_NtQEgaCalc
// ���룺   A������޹�2������
// ���أ�   NONE
// ������   ����A������޹�2����
// ע�ͣ�
//*********************************************************************************
void fnEnergy_NtQEgaCalc(u8 Mode, u8 *Buf)
{
    sFsEgSh_HighTypeDef *NtQEgSha;

    NtQEgSha = (sFsEgSh_HighTypeDef *)Buf;

    NtQEgSha->Dat0 = 0;
    NtQEgSha->Dat1 = 0;
    if (Mode & 0x01)
    {
        *NtQEgSha = fnEnergy_GrpAddEg(NtQEgSha, &Energy.PubData.Qd1QEgSha, 0);
    }
    if (Mode & 0x02)
    {
        *NtQEgSha = fnEnergy_GrpAddEg(NtQEgSha, &Energy.PubData.Qd1QEgSha, 1);
    }
    if (Mode & 0x04)
    {
        *NtQEgSha = fnEnergy_GrpAddEg(NtQEgSha, &Energy.PubData.Qd2QEgSha, 0);
    }
    if (Mode & 0x08)
    {
        *NtQEgSha = fnEnergy_GrpAddEg(NtQEgSha, &Energy.PubData.Qd2QEgSha, 1);
    }
    if (Mode & 0x10)
    {
        *NtQEgSha = fnEnergy_GrpAddEg(NtQEgSha, &Energy.PubData.Qd3QEgSha, 0);
    }
    if (Mode & 0x20)
    {
        *NtQEgSha = fnEnergy_GrpAddEg(NtQEgSha, &Energy.PubData.Qd3QEgSha, 1);
    }
    if (Mode & 0x40)
    {
        *NtQEgSha = fnEnergy_GrpAddEg(NtQEgSha, &Energy.PubData.Qd4QEgSha, 0);
    }
    if (Mode & 0x80)
    {
        *NtQEgSha = fnEnergy_GrpAddEg(NtQEgSha, &Energy.PubData.Qd4QEgSha, 1);
    }
}

//*********************************************************************************
// �������� fnEnergy_PtQEgbCalc
// ���룺   B������޹�1������
// ���أ�   NONE
// ������   ����B������޹�1����
// ע�ͣ�
//*********************************************************************************
void fnEnergy_PtQEgbCalc(u8 Mode, u8 *Buf)
{
    sFsEgSh_HighTypeDef *PtQEgShb;

    PtQEgShb = (sFsEgSh_HighTypeDef *)Buf;

    PtQEgShb->Dat0 = 0;
    PtQEgShb->Dat1 = 0;

    if (Mode & 0x01)
    {
        *PtQEgShb = fnEnergy_GrpAddEg(PtQEgShb, &Energy.PubData.Qd1QEgShb, 0);
    }
    if (Mode & 0x02)
    {
        *PtQEgShb = fnEnergy_GrpAddEg(PtQEgShb, &Energy.PubData.Qd1QEgShb, 1);
    }
    if (Mode & 0x04)
    {
        *PtQEgShb = fnEnergy_GrpAddEg(PtQEgShb, &Energy.PubData.Qd2QEgShb, 0);
    }
    if (Mode & 0x08)
    {
        *PtQEgShb = fnEnergy_GrpAddEg(PtQEgShb, &Energy.PubData.Qd2QEgShb, 1);
    }
    if (Mode & 0x10)
    {
        *PtQEgShb = fnEnergy_GrpAddEg(PtQEgShb, &Energy.PubData.Qd3QEgShb, 0);
    }
    if (Mode & 0x20)
    {
        *PtQEgShb = fnEnergy_GrpAddEg(PtQEgShb, &Energy.PubData.Qd3QEgShb, 1);
    }
    if (Mode & 0x40)
    {
        *PtQEgShb = fnEnergy_GrpAddEg(PtQEgShb, &Energy.PubData.Qd4QEgShb, 0);
    }
    if (Mode & 0x80)
    {
        *PtQEgShb = fnEnergy_GrpAddEg(PtQEgShb, &Energy.PubData.Qd4QEgShb, 1);
    }
}

//*********************************************************************************
// �������� fnEnergy_NtQEgbCalc
// ���룺   B������޹�2������
// ���أ�   NONE
// ������   ����B������޹�2����
// ע�ͣ�
//*********************************************************************************
void fnEnergy_NtQEgbCalc(u8 Mode, u8 *Buf)
{
    sFsEgSh_HighTypeDef *NtQEgShb;

    NtQEgShb = (sFsEgSh_HighTypeDef *)Buf;

    NtQEgShb->Dat0 = 0;
    NtQEgShb->Dat1 = 0;

    if (Mode & 0x01)
    {
        *NtQEgShb = fnEnergy_GrpAddEg(NtQEgShb, &Energy.PubData.Qd1QEgShb, 0);
    }
    if (Mode & 0x02)
    {
        *NtQEgShb = fnEnergy_GrpAddEg(NtQEgShb, &Energy.PubData.Qd1QEgShb, 1);
    }
    if (Mode & 0x04)
    {
        *NtQEgShb = fnEnergy_GrpAddEg(NtQEgShb, &Energy.PubData.Qd2QEgShb, 0);
    }
    if (Mode & 0x08)
    {
        *NtQEgShb = fnEnergy_GrpAddEg(NtQEgShb, &Energy.PubData.Qd2QEgShb, 1);
    }
    if (Mode & 0x10)
    {
        *NtQEgShb = fnEnergy_GrpAddEg(NtQEgShb, &Energy.PubData.Qd3QEgShb, 0);
    }
    if (Mode & 0x20)
    {
        *NtQEgShb = fnEnergy_GrpAddEg(NtQEgShb, &Energy.PubData.Qd3QEgShb, 1);
    }
    if (Mode & 0x40)
    {
        *NtQEgShb = fnEnergy_GrpAddEg(NtQEgShb, &Energy.PubData.Qd4QEgShb, 0);
    }
    if (Mode & 0x80)
    {
        *NtQEgShb = fnEnergy_GrpAddEg(NtQEgShb, &Energy.PubData.Qd4QEgShb, 1);
    }
}

//*********************************************************************************
// �������� fnEnergy_PtQEgcCalc
// ���룺   C������޹�1������
// ���أ�   NONE
// ������   ����C������޹�1����
// ע�ͣ�
//*********************************************************************************
void fnEnergy_PtQEgcCalc(u8 Mode, u8 *Buf)
{
    sFsEgSh_HighTypeDef *PtQEgShc;

    PtQEgShc = (sFsEgSh_HighTypeDef *)Buf;

    PtQEgShc->Dat0 = 0;
    PtQEgShc->Dat1 = 0;

    if (Mode & 0x01)
    {
        *PtQEgShc = fnEnergy_GrpAddEg(PtQEgShc, &Energy.PubData.Qd1QEgShc, 0);
    }
    if (Mode & 0x02)
    {
        *PtQEgShc = fnEnergy_GrpAddEg(PtQEgShc, &Energy.PubData.Qd1QEgShc, 1);
    }
    if (Mode & 0x04)
    {
        *PtQEgShc = fnEnergy_GrpAddEg(PtQEgShc, &Energy.PubData.Qd2QEgShc, 0);
    }
    if (Mode & 0x08)
    {
        *PtQEgShc = fnEnergy_GrpAddEg(PtQEgShc, &Energy.PubData.Qd2QEgShc, 1);
    }
    if (Mode & 0x10)
    {
        *PtQEgShc = fnEnergy_GrpAddEg(PtQEgShc, &Energy.PubData.Qd3QEgShc, 0);
    }
    if (Mode & 0x20)
    {
        *PtQEgShc = fnEnergy_GrpAddEg(PtQEgShc, &Energy.PubData.Qd3QEgShc, 1);
    }
    if (Mode & 0x40)
    {
        *PtQEgShc = fnEnergy_GrpAddEg(PtQEgShc, &Energy.PubData.Qd4QEgShc, 0);
    }
    if (Mode & 0x80)
    {
        *PtQEgShc = fnEnergy_GrpAddEg(PtQEgShc, &Energy.PubData.Qd4QEgShc, 1);
    }
}

//*********************************************************************************
// �������� fnEnergy_NtQEgcCalc
// ���룺   C������޹�2������
// ���أ�   NONE
// ������   ����C������޹�2����
// ע�ͣ�
//*********************************************************************************
void fnEnergy_NtQEgcCalc(u8 Mode, u8 *Buf)
{
    sFsEgSh_HighTypeDef *NtQEgShc;

    NtQEgShc = (sFsEgSh_HighTypeDef *)Buf;

    NtQEgShc->Dat0 = 0;
    NtQEgShc->Dat1 = 0;
    if (Mode & 0x01)
    {
        *NtQEgShc = fnEnergy_GrpAddEg(NtQEgShc, &Energy.PubData.Qd1QEgShc, 0);
    }
    if (Mode & 0x02)
    {
        *NtQEgShc = fnEnergy_GrpAddEg(NtQEgShc, &Energy.PubData.Qd1QEgShc, 1);
    }
    if (Mode & 0x04)
    {
        *NtQEgShc = fnEnergy_GrpAddEg(NtQEgShc, &Energy.PubData.Qd2QEgShc, 0);
    }
    if (Mode & 0x08)
    {
        *NtQEgShc = fnEnergy_GrpAddEg(NtQEgShc, &Energy.PubData.Qd2QEgShc, 1);
    }
    if (Mode & 0x10)
    {
        *NtQEgShc = fnEnergy_GrpAddEg(NtQEgShc, &Energy.PubData.Qd3QEgShc, 0);
    }
    if (Mode & 0x20)
    {
        *NtQEgShc = fnEnergy_GrpAddEg(NtQEgShc, &Energy.PubData.Qd3QEgShc, 1);
    }
    if (Mode & 0x40)
    {
        *NtQEgShc = fnEnergy_GrpAddEg(NtQEgShc, &Energy.PubData.Qd4QEgShc, 0);
    }
    if (Mode & 0x80)
    {
        *NtQEgShc = fnEnergy_GrpAddEg(NtQEgShc, &Energy.PubData.Qd4QEgShc, 1);
    }
}
#endif
void fnEnergy_EgAdd(u8 *Dst, u8 *DeltaEg)
{
    sFsEgSh_HighTypeDef *Eg;
    u16  tempDelta;
    Eg = (sFsEgSh_HighTypeDef *)Dst;
    u64 u64_data1;

    memcpy((u8 *)&tempDelta, DeltaEg, 2);

    u64_data1 = ((u64)(Eg->Dat0)) + (((u64)(Eg->Dat1)) << 32);

    u64_data1 += tempDelta;

    memcpy(Dst, (u8 *)&u64_data1, 8);
}

//*********************************************************************************
// �������� fnEnergy_WriteToE2
// ���룺
// ���أ�
// �������洢������E2
// ע�ͣ�
//*********************************************************************************
void fnEnergy_WriteToE2(void)
{
    u8  line = 0 ;
    //      u8 len = 0;

    for (line = 0 ; line < AllPEg ; line++)
    {
        if (Energy.PubPara.EgUpFlag[line])
        {
            Energy.PubPara.EgUpFlag[line] = 0;
            if (fnFile_Write(FileId_EgSh, EnergyOpConst[line].EgRomAd, EnergyOpConst[line].EgRamAd, EnergyOpConst[line].EgLen) == SUCCESS)
            {
                if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWON) //����ʱ���汸����
                {
                    fnFile_Write(FileId_BackUpEgSh, EnergyOpConst[line].EgRomAd, EnergyOpConst[line].EgRamAd, EnergyOpConst[line].EgLen);
                }
            }
        }
    }
}

//-----------------
void fnEnergy_Exec(void)
{
    u8 i;
    u16 DeltaE;

    //-------------
    if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON) || (Inactive.PubData.InactiveStamp))
    {
        return;
    }
    if (MeasureRms.PriData.Flag & (MEASURE_FLAG_INIT | MEASURE_FLAG_RST))
    {
        return;
    }

    fnWDT_Restart();
    fnEnergy_CRCCheck();
    fnEnergy_PulseCalc();

    for (i = 0 ; i < PieceEgOffAddr_end ; i++)
    {
        {
            if ((EnergyOpConst[i].Flag & 0x03) == QConst)
            {
                DeltaE = Energy.PubPara.QPlsDeltaE;
            }
            else if ((EnergyOpConst[i].Flag & 0x03) == HConst)
            {
                DeltaE = Energy.PubPara.HPlsDeltaE;
            }
            else
            {
                DeltaE = Energy.PubPara.PPlsDeltaE;
            }

            if (Energy.PriData.PieceEg[i] > 20 * DefaultHighPulseRate * DeltaE) //�ݴ�������15������β��ʱ����
            {
                Std_Memset((u8 *)&Energy.PriData, 0x00, sizeof(Energy.PriData) - 2);
                fnCrc_Check(0, (u8 *)&Energy.PriData, sizeof(Energy.PriData) - 2, (u8 *)&Energy.PriData.Crc);
            }

            if ((Energy.PriData.PieceEg[i] >= DeltaE) && (DeltaE))
            {
                while (Energy.PriData.PieceEg[i] >= DeltaE)
                {
                    fnEnergy_EgAdd(EnergyOpConst[i].EgRamAd, EnergyOpConst[i].EgUnit);
                    Energy.PriData.PieceEg[i] -= DeltaE;
                }
                fnCrc_Check(0, EnergyOpConst[i].EgRamAd, EnergyOpConst[i].EgLen - 2, EnergyOpConst[i].EgCrcRamAd);
                fnCrc_Check(0, (u8 *)&Energy.PriData, sizeof(Energy.PriData) - 2, (u8 *)&Energy.PriData.Crc);
                Energy.PubPara.EgUpFlag[i] = 1;
            }
        }
    }

    //-----------
    if (!Energy.PubPara.fMinute)
    {
        Energy.PubPara.fMinute = 15;
        fnEnergy_WriteToE2();
    }

    return;
}

void fnEnergy_PownDownWriteToE2(void)
{
    u8 i, j, allEgItem;
    fnFile_Write(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_EgPiece, (u8 *)&Energy.PriData, FileItemInfoLen_PowDn_EgPiece);

    allEgItem = sizeof(EnergyOpConst) / sizeof(EnergyOpConst[0]);
    for (i = 0 ; i < allEgItem ; i += 6)
    {
        for (j = 0; j < 6; j++)
        {
            if (Energy.PubPara.EgUpFlag[i + j])
            {
                if ((i + 6) < allEgItem)
                {
                    fnFile_Write(FileId_EgSh, EnergyOpConst[i].EgRomAd, EnergyOpConst[i].EgRamAd, FileItemInfoLen_EgSh_PtPEgSh * 6);    //д6��������������1ҳ����
                }
                else
                {
                    fnFile_Write(FileId_EgSh, EnergyOpConst[i].EgRomAd, EnergyOpConst[i].EgRamAd, FileItemInfoLen_EgSh_PtPEgSh * (allEgItem - i));  //д6��������������1ҳ����
                }
                break;
            }
        }
    }
}
