
#define  DL645B_COM_GLOBALS
#include <App.h>
u8 Rn_ReadInfo[4];
const u8    RdAddr[] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};

//函数:获取两个日期间的秒数
//参数:Date1、Date2日期(sDF01)
//返回:秒数(Date1 > Date2 返回正、否则返回负)
//#pragma location="BANK2"
s32 fnTwoDateApart_SecondCount(sDF01 *Date1, sDF01 *Date2)
{
    s32 Total;

    Total = fnTwoDateApart_MinuteCount((sDF15 *)&Date1->Minute, (sDF15 *)&Date2->Minute);

    Total = Total * 60 +
            (fnBcdToHex_u8(Date1->Second & 0x7f)) -
            (fnBcdToHex_u8(Date2->Second & 0x7f)) ;
    return (Total);
}

void fnDl645B_Inverse(u8 *Buf, u8 Len)
{
    u8 i, Temp08;

    for (i = 0; i < Len / 2; i++)
    {
        Temp08 = Buf[i];
        Buf[i] = Buf[Len - 1 - i];
        Buf[Len - 1 - i] = Temp08;
    }
}

ErrorStatus fnDl645B_ByteCheckBCD(u8 Value)
{
    if (((Value & 0xF0) <= 0x90) && ((Value & 0x0F) <= 0x09))
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

ErrorStatus fnDl645B_FramCheckBCD(u8 *Buf, u8 Len)
{
    u8 i;

    for (i = 0; i < Len; i++)
    {
        if (fnDl645B_ByteCheckBCD(Buf[i]) != SUCCESS)
        {
            return ERROR;
        }
    }

    return SUCCESS;
}

// 比较设置的切换时间是否合法
ErrorStatus fnDl645B_JudgeClockNoWeek(u8 Start, u8 *Ck, u8 Len)
{
    u8  i;
    u8 Max[] = { 0x59, 0x59, 0x23, 0x31, 0x12, 0x99 }, Min[] = { 0x00, 0x00, 0x00, 0x01, 0x01, 0x00 };

    for (i = 0; i < Len; i++)
    {
        if ((Ck[i] > Max[i + Start]) || (Ck[i] < Min[i + Start]))
        {
            return ERROR;    //合法性检查错误
        }
        if (fnDl645B_ByteCheckBCD(Ck[i]) != SUCCESS)
        {
            return ERROR;    //BCD码检查错误
        }
    }

    return SUCCESS;//正确
}

ErrorStatus fnDl645B_JudgeSwitch(u8 *Buf)
{
    u8 i;
    ErrorStatus err;

    for (i = 0; i < 5; i++)
    {
        if (Buf[i] != 0x00)
        {
            break;
        }
    }

    if (i < 5)
    {
        for (i = 0; i < 5; i++)
        {
            if (Buf[i] != 0x99)
            {
                break;
            }
        }

        if (i < 5)
        {
            err = fnDl645B_JudgeClockNoWeek(1, Buf, 5);
            return (err); //错误
        }
    }
    return SUCCESS;
}

ErrorStatus fnDl645B_AddrCheck(u8 *ComAddr, u8 AFN)
{
    const u8    BcAddr[] = {0x99, 0x99, 0x99, 0x99, 0x99, 0x99};

    s8          i, Flag;

    if ((Std_Memcmp(&ComAddr[0], &BcAddr, 6) == SUCCESS) &&
        ((AFN == 0x08) || (AFN == 0x16) || (AFN == 0x1D)))
    {
        return (SUCCESS);
    }

    if (Std_Memcmp(&ComAddr[0], &RdAddr, 6) == ERROR)
    {
        for (Flag = 0, i = 5 ; i >= 0 ; i--)
        {
            if (ComAddr[i] != CommPara.ComAddr[i])
            {
                if (ComAddr[i] != 0xAA)
                {
                    return (ERROR);
                }
                if (Flag)
                {
                    return (ERROR);
                }
            }
            else
            {
                Flag = 1;
            }
        }
    }
    else
    {
        if ((AFN == 0x14) || (AFN == 0x17) || (AFN == 0x19) || (AFN == 0x1a) || (AFN == 0x1b) || (AFN == 0x1c))
        {
            return (ERROR);
        }
    }
    return (SUCCESS);
}

ErrorStatus fnDl645B_FrameCheck(sFrmDl645B_TypeDef *pCheck, u16 *usDataLen)
{
    const u8    BcAddr[] = {0x99, 0x99, 0x99, 0x99, 0x99, 0x99};
    if (pCheck->Head1 != 0x68)
    {
        return (ERROR);
    }
    if (pCheck->Head2 != 0x68)
    {
        return (ERROR);
    }

    if ((pCheck->AFN == 0x11) && (pCheck->UDat.DI0 == 0x33) && (pCheck->UDat.DI1 == 0x36) && (pCheck->UDat.DI2 == 0x37) && (pCheck->UDat.DI3 == 0x37)) // 液晶查看命令
    {
        if (Std_Memcmp(pCheck->Addr, &BcAddr, 6) == ERROR)
        {
            if (fnDl645B_AddrCheck(pCheck->Addr, pCheck->AFN) != SUCCESS)
            {
                return (ERROR);
            }
        }
    }
    else
    {
        if (fnDl645B_AddrCheck(pCheck->Addr, pCheck->AFN) != SUCCESS)
        {
            return (ERROR);
        }
    }
    if (pCheck->AFN != 0x01 && pCheck->AFN != 0x04 && pCheck->AFN != 0x03 && pCheck->AFN != 0x08 && pCheck->AFN < 0x10)
    {
        return (ERROR);
    }

    if (pCheck->UDat.Dat[pCheck->Len - 4 + 0] != fnSum(&pCheck->Head1, pCheck->Len + 10))
    {
        return (ERROR);
    }
    if (pCheck->UDat.Dat[pCheck->Len - 4 + 1] != 0x16)
    {
        return (ERROR);
    }

    *usDataLen = pCheck->Len + 10 + 2;

    return (SUCCESS);
}

void fnDl645B_Modify(u8 *pModify, u16 Len, u8 OpFlag)
{
    if (OpFlag)
    {
        for (; Len != 0 ; Len--)
        {
            *pModify = *pModify + 0x33;
            pModify++;
        }
    }
    else
    {
        for (; Len != 0 ; Len--)
        {
            *pModify = *pModify - 0x33;
            pModify++;
        }
    }
}

//=================================================================
u16 fnDl645_PackErr(sFrmDl645B_TypeDef *TxFrm, sFrmDl645B_TypeDef *RxFrm, eDL645B_ErrInfo_TypeDef ErrInfo)
{
    BufTemp[100] = RxFrm->AFN;
    TxFrm->Head1 = 0x68;
    fnFile_Read(FileId_ParaCom, FileItemInfoOffAddr_ComPara_ComAddr, &TxFrm->Addr, 6);
    TxFrm->Head2 = 0x68;

    TxFrm->AFN = BufTemp[100];
    TxFrm->Persist = 0;
    TxFrm->Dir = 1;

    if (ErrInfo != DL645B_ERRINFO_OK)
    {
        TxFrm->Ack = 1;
        TxFrm->Len = 1;
        TxFrm->UDat.DI0 = ErrInfo;

        fnDl645B_Modify(&TxFrm->UDat.DI0, TxFrm->Len, 1);
        TxFrm->UDat.DI1 = fnSum(&TxFrm->Head1, TxFrm->Len + 10);
        TxFrm->UDat.DI2 = 0x16;
    }
    else
    {
        TxFrm->Ack = 0;
        TxFrm->Len = 0;

        fnDl645B_Modify(&TxFrm->UDat.DI0, TxFrm->Len, 1);
        TxFrm->UDat.DI0 = fnSum(&TxFrm->Head1, TxFrm->Len + 10);
        TxFrm->UDat.DI1 = 0x16;
    }

    return (TxFrm->Len + 12);
}

u16 fnDl645_SafetyPackErr(sFrmDl645B_TypeDef *TxFrm, sFrmDl645B_TypeDef *RxFrm, eDL645B_SErrInfo_TypeDef ErrInfo)
{
    BufTemp[100] = RxFrm->AFN;
    TxFrm->Head1 = 0x68;
    fnFile_Read(FileId_ParaCom, FileItemInfoOffAddr_ComPara_ComAddr, &TxFrm->Addr, 6);
    TxFrm->Head2 = 0x68;

    TxFrm->AFN = BufTemp[100];
    TxFrm->Persist = 0;
    TxFrm->Dir = 1;
    if (ErrInfo == DL645B_SERRINFO_OK)
    {
        TxFrm->Ack = 0;
        TxFrm->Len = 0;

        fnDl645B_Modify(&TxFrm->UDat.DI0, TxFrm->Len, 1);
        TxFrm->UDat.DI0 = fnSum(&TxFrm->Head1, TxFrm->Len + 10);
        TxFrm->UDat.DI1 = 0x16;
    }
    else
    {
        TxFrm->Ack = 1;
        TxFrm->Len = 2;
        TxFrm->UDat.DI0 = ErrInfo;
        TxFrm->UDat.DI1 = 0x00;

        fnDl645B_Modify(&TxFrm->UDat.DI0, TxFrm->Len, 1);
        TxFrm->UDat.DI2 = fnSum(&TxFrm->Head1, TxFrm->Len + 10);
        TxFrm->UDat.DI3 = 0x16;
    }
    return (TxFrm->Len + 12);
}

u16 fnDl645_ControlPackErr(sFrmDl645B_TypeDef *TxFrm, eDL645B_ContErrInfo_TypeDef ErrInfo, eDL645B_ContExeInfo_TypeDef ExeInfo, u8 Flag)
{
    TxFrm->Head1 = 0x68;
    fnFile_Read(FileId_ParaCom, FileItemInfoOffAddr_ComPara_ComAddr, &TxFrm->Addr, 6);
    TxFrm->Head2 = 0x68;

    TxFrm->AFN = 0x1c;
    TxFrm->Persist = 0;
    TxFrm->Dir = 1;
    if (ErrInfo == DL645B_ContErrInfo_OK)
    {
        if (Flag == 0)
        {
            TxFrm->Ack = 0;
            TxFrm->Len = 0;
            fnDl645B_Modify(&TxFrm->UDat.DI0, TxFrm->Len, 1);
            TxFrm->UDat.DI0 = fnSum(&TxFrm->Head1, TxFrm->Len + 10);
            TxFrm->UDat.DI1 = 0x16;
        }
        else
        {
            TxFrm->Ack = 0;
            TxFrm->Len = 2;
            TxFrm->UDat.DI0 = ExeInfo;
            TxFrm->UDat.DI1 = (ExeInfo >> 8);

            fnDl645B_Modify(&TxFrm->UDat.DI0, TxFrm->Len, 1);
            TxFrm->UDat.DI2 = fnSum(&TxFrm->Head1, TxFrm->Len + 10);
            TxFrm->UDat.DI3 = 0x16;
        }
    }
    else
    {
        TxFrm->Ack = 1;
        TxFrm->Len = 2;
        if (Flag == 0)
        {
            TxFrm->Len = 1;
            TxFrm->UDat.DI0 = 0x04;
            fnDl645B_Modify(&TxFrm->UDat.DI0, TxFrm->Len, 1);
            TxFrm->UDat.DI1 = fnSum(&TxFrm->Head1, TxFrm->Len + 10);
            TxFrm->UDat.DI2 = 0x16;
        }
        else
        {
            TxFrm->Len = 2;
            TxFrm->UDat.DI0 = ErrInfo;
            TxFrm->UDat.DI1 = (ErrInfo >> 8);
            fnDl645B_Modify(&TxFrm->UDat.DI0, TxFrm->Len, 1);
            TxFrm->UDat.DI2 = fnSum(&TxFrm->Head1, TxFrm->Len + 10);
            TxFrm->UDat.DI3 = 0x16;
        }
    }
    return (TxFrm->Len + 12);
}

u16 fnDl645_PackOk(sFrmDl645B_TypeDef *TxFrm, sFrmDl645B_TypeDef *RxFrm, u16 Len)
{
    u8 i;
    //sDF38 EventSt;
    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_MeterRunFlag, &i, 1);
    //fnDl645File_Read(FileId_EvtReport , FileItemInfoOffAddr_EvtReport_EventStatus,  &EventSt , FileItemInfoLen_EvtReport_EventStatus);

    BufTemp[100] = RxFrm->AFN;
    BufTemp[101] = RxFrm->UDat.DI0 ;
    BufTemp[102] = RxFrm->UDat.DI1 ;
    BufTemp[103] = RxFrm->UDat.DI2 ;
    BufTemp[104] = RxFrm->UDat.DI3 ;
    BufTemp[105] = RxFrm->UDat.Dat[0] ;

    TxFrm->Head1 = 0x68;
    fnFile_Read(FileId_ParaCom, FileItemInfoOffAddr_ComPara_ComAddr, &TxFrm->Addr, 6);
    TxFrm->Head2 = 0x68;

    TxFrm->AFN = BufTemp[100];
    TxFrm->Persist = 0;
    TxFrm->Ack = 0;
    TxFrm->Dir = 1;

    TxFrm->Len = Len;

    TxFrm->UDat.DI0 = BufTemp[101];
    TxFrm->UDat.DI1 = BufTemp[102];
    TxFrm->UDat.DI2 = BufTemp[103];
    TxFrm->UDat.DI3 = BufTemp[104];

    if (TxFrm->AFN == 0x12)
    {
        TxFrm->Len += 1;
        TxFrm->UDat.Dat[TxFrm->Len - 4 - 1] = BufTemp[105];
    }

    fnDl645B_Modify(&TxFrm->UDat.DI0, TxFrm->Len, 1);

    TxFrm->UDat.Dat[TxFrm->Len - 4 + 0] = fnSum(&TxFrm->Head1, TxFrm->Len + 10);
    TxFrm->UDat.Dat[TxFrm->Len - 4 + 1] = 0x16;

    return (TxFrm->Len + 12);
}

u16 fnDl645_PackSeq(sFrmDl645B_TypeDef *TxFrm, sFrmDl645B_TypeDef *RxFrm, u16 Len)
{
    BufTemp[100] = RxFrm->AFN;
    BufTemp[101] = RxFrm->UDat.DI0 ;
    BufTemp[102] = RxFrm->UDat.DI1 ;
    BufTemp[103] = RxFrm->UDat.DI2 ;
    BufTemp[104] = RxFrm->UDat.DI3 ;
    BufTemp[105] = RxFrm->UDat.Dat[0] ;
    TxFrm->Head1 = 0x68;
    fnFile_Read(FileId_ParaCom, FileItemInfoOffAddr_ComPara_ComAddr, &TxFrm->Addr, 6);
    TxFrm->Head2 = 0x68;

    TxFrm->AFN = BufTemp[100];
    TxFrm->Persist = 1;
    TxFrm->Ack = 0;
    TxFrm->Dir = 1;

    TxFrm->Len = Len;

    TxFrm->UDat.DI0 = BufTemp[101];
    TxFrm->UDat.DI1 = BufTemp[102];
    TxFrm->UDat.DI2 = BufTemp[103];
    TxFrm->UDat.DI3 = BufTemp[104];

    if (TxFrm->AFN == 0x12)
    {
        TxFrm->Len += 1;
        TxFrm->UDat.Dat[TxFrm->Len - 4 - 1] = BufTemp[105];
    }
    fnDl645B_Modify(&TxFrm->UDat.DI0, TxFrm->Len, 1);

    TxFrm->UDat.Dat[TxFrm->Len - 4 + 0] = fnSum(&TxFrm->Head1, TxFrm->Len + 10);
    TxFrm->UDat.Dat[TxFrm->Len - 4 + 1] = 0x16;

    return (TxFrm->Len + 12);
}

u16 fnDl645_PackNoDI(sFrmDl645B_TypeDef *TxFrm, sFrmDl645B_TypeDef *RxFrm, u16 Len)
{
    BufTemp[100] = RxFrm->AFN;
    TxFrm->Head1 = 0x68;
    fnFile_Read(FileId_ParaCom, FileItemInfoOffAddr_ComPara_ComAddr, &TxFrm->Addr, 6);
    TxFrm->Head2 = 0x68;

    TxFrm->AFN = BufTemp[100];
    TxFrm->Persist = 0;
    TxFrm->Ack = 0;
    TxFrm->Dir = 1;

    TxFrm->Len = Len;

    fnDl645B_Modify(&TxFrm->UDat.DI0, TxFrm->Len, 1);

    TxFrm->UDat.Dat[TxFrm->Len - 4 + 0] = fnSum(&TxFrm->Head1, TxFrm->Len + 10);
    TxFrm->UDat.Dat[TxFrm->Len - 4 + 1] = 0x16;

    return (TxFrm->Len + 12);
}

u16 fnDl645_PackFeatureData(sFrmDl645B_TypeDef *TxFrm, sFrmDl645B_TypeDef *RxFrm, u8 FeatureData)
{
    BufTemp[100] =  RxFrm->AFN;
    TxFrm->Head1 = 0x68;
    fnFile_Read(FileId_ParaCom, FileItemInfoOffAddr_ComPara_ComAddr, &TxFrm->Addr, 6);
    TxFrm->Head2 = 0x68;

    TxFrm->AFN = BufTemp[100];
    TxFrm->Persist = 0;
    TxFrm->Dir = 1;
    TxFrm->Ack = 0;
    TxFrm->Len = 1;
    TxFrm->UDat.DI0 = FeatureData;
    fnDl645B_Modify(&TxFrm->UDat.DI0, TxFrm->Len, 1);
    TxFrm->UDat.DI1 = fnSum(&TxFrm->Head1, TxFrm->Len + 10);
    TxFrm->UDat.DI2 = 0x16;

    return (TxFrm->Len + 12);
}

//=================================================================
#if 0 //(nPhs==ThreePhs)
const sDl645B_RmEgSh_TypeDef Dl645B_RmEgSh[] =
{
    //  {   0   ,   0x00    ,   Dl645FileItemInfoOffAddr_EgSh_RmTime    },
    {   1,   0x00, 0x0000,  FileItemInfoOffAddr_EgSh_PtPEgSh    },         //待完善
    {   1,   0x01, 0x0010,  FileItemInfoOffAddr_EgSh_PtPEgSh    },
    {   1,   0x02, 0x0020,      FileItemInfoOffAddr_EgSh_NtPEgSh    },
    //  {   1   ,   0x00    ,   Dl645FileItemInfoOffAddr_EgSh_AllQEgSh  },
    {   1,   0x03, 0x0030,  FileItemInfoOffAddr_EgSh_Qd1QEgSh   },          //待完善
    {   1,   0x04, 0x0040,  FileItemInfoOffAddr_EgSh_Qd3QEgSh   },          //待完善
    {   1,   0x05, 0x0050,  FileItemInfoOffAddr_EgSh_Qd1QEgSh   },
    {   1,   0x06, 0x0060,  FileItemInfoOffAddr_EgSh_Qd2QEgSh   },
    {   1,   0x07, 0x0070,  FileItemInfoOffAddr_EgSh_Qd3QEgSh   },
    {   1,   0x08, 0x0080,  FileItemInfoOffAddr_EgSh_Qd4QEgSh   },

    {   0,   0x15, 0x0011,  FileItemInfoOffAddr_EgSh_PtPEgSha   },
    {   0,   0x16, 0x0021,  FileItemInfoOffAddr_EgSh_NtPEgSha   },
    {   0,   0x17, 0x0031,  FileItemInfoOffAddr_EgSh_Qd1QEgSha  },         //待完善
    {   0,   0x18, 0x0041,  FileItemInfoOffAddr_EgSh_Qd3QEgSha  },         //待完善
    {   0,   0x19, 0x0051,  FileItemInfoOffAddr_EgSh_Qd1QEgSha  },
    {   0,   0x1a, 0x0061,  FileItemInfoOffAddr_EgSh_Qd2QEgSha  },
    {   0,   0x1b, 0x0071,  FileItemInfoOffAddr_EgSh_Qd3QEgSha  },
    {   0,   0x1c, 0x0081,  FileItemInfoOffAddr_EgSh_Qd4QEgSha  },

    {   0,   0x29, 0x0012,      FileItemInfoOffAddr_EgSh_PtPEgShb   },
    {   0,   0x2a, 0x0022,  FileItemInfoOffAddr_EgSh_NtPEgShb   },
    {   0,   0x2b, 0x0032,  FileItemInfoOffAddr_EgSh_Qd1QEgShb  },         //待完善
    {   0,   0x2c, 0x0042,  FileItemInfoOffAddr_EgSh_Qd3QEgShb  },         //待完善
    {   0,   0x2d, 0x0052,  FileItemInfoOffAddr_EgSh_Qd1QEgShb  },
    {   0,   0x2e, 0x0062,  FileItemInfoOffAddr_EgSh_Qd2QEgShb  },
    {   0,   0x2f, 0x0072,  FileItemInfoOffAddr_EgSh_Qd3QEgShb  },
    {   0,   0x30, 0x0082,  FileItemInfoOffAddr_EgSh_Qd4QEgShb  },

    {   0,   0x3d, 0x0013,  FileItemInfoOffAddr_EgSh_PtPEgShc   },
    {   0,   0x3e, 0x0023,  FileItemInfoOffAddr_EgSh_NtPEgShc   },
    {   0,   0x3f, 0x0033,  FileItemInfoOffAddr_EgSh_Qd1QEgShc  },         //待完善
    {   0,   0x40, 0x0043,  FileItemInfoOffAddr_EgSh_Qd3QEgShc  },         //待完善
    {   0,   0x41, 0x0053,  FileItemInfoOffAddr_EgSh_Qd1QEgShc  },
    {   0,   0x42, 0x0063,  FileItemInfoOffAddr_EgSh_Qd2QEgShc  },
    {   0,   0x43, 0x0073,  FileItemInfoOffAddr_EgSh_Qd3QEgShc  },
    {   0,   0x44, 0x0083,  FileItemInfoOffAddr_EgSh_Qd4QEgShc  },
};
#else
const sDl645B_RmEgSh_TypeDef Dl645B_RmEgSh[] =
{
    {   1,   0x00, 0x0000,  FileItemInfoOffAddr_EgSh_PtPEgSh    },
    {   1,   0x01, 0x0010,  FileItemInfoOffAddr_EgSh_PtPEgSh    },
    {   1,   0x02, 0x0020,      FileItemInfoOffAddr_EgSh_NtPEgSh    },
};
#endif
ErrorStatus fnDl645_FindRmEgSh(u8 DI2, u16 *nItem)
{
    for (*nItem = 0 ; *nItem < (sizeof(Dl645B_RmEgSh) / sizeof(sDl645B_RmEgSh_TypeDef)) ; *nItem += 1)
    {
        if (DI2 == Dl645B_RmEgSh[*nItem].DI2)
        {
            return (SUCCESS);
        }
    }
    return (ERROR);
}

ErrorStatus fnDl645_GetRmEgShItemLen(u16 nItem, u8 DI1, u16 *Len)
{
    if (nItem >= (sizeof(Dl645B_RmEgSh) / sizeof(sDl645B_RmEgSh_TypeDef)))
    {
        return (ERROR);
    }

    *Len = sizeof(sFsEgSh_TypeDef);
    if ((Dl645B_RmEgSh[nItem].Flag & 0x01) &&
        (DI1 == 0xff))
    {
        if (Bkgrd.PubData.nFl > MAX_FL)
        {
            Bkgrd.PubData.nFl = MAX_FL;
        }
        *Len = *Len * (Bkgrd.PubData.nFl + 1);
    }
    return (SUCCESS);
}

extern u8 fnGet_EnergyData(u32  OAD, u8  *uBuf);
ErrorStatus fnDl645_GetRmEgShItem(u16 nItem, u8 DI1, u8 nRecord, u32 OffAddr, u16 Len, u8 *Dst)
{
    u8  i;
    const sDispItem_TypeDef  RmEgShRecTime_Tab = {0x00, 0x00, 0x02, 0x00, 0x00, 0x01, 0x02, 0x05, 0x50, 0x01}; //698 读取
    sDispItem_TypeDef   temp_tab;
    u8 temp[15];
    u16 temp16 = 0;
    u32 OAD, temp32;

    if (nItem >= (sizeof(Dl645B_RmEgSh) / sizeof(sDl645B_RmEgSh_TypeDef)))
    {
        return (ERROR);
    }
    if ((DI1 != 0xff) && (DI1 > MAX_FL))
    {
        return (ERROR);
    }

    OffAddr += Dl645B_RmEgSh[nItem].OffAddr;
    if (nRecord == 0)   //当前电能
    {
        if (DI1 != 0xff)
        {
            OAD = (Dl645B_RmEgSh[nItem].OI_698 << 16) + 0x0200 + (DI1 + 1);
            fnGet_EnergyData(OAD, &temp[0]);
            temp32 = Std_Lsb32DataGet(&temp[0]);
            temp32 = fnHexToBcd_u32(temp32);
            Std_Memcpy(Dst, (u8 *)&temp32, 4);
        }
        else
        {
            for (i = 0; i < (Bkgrd.PubData.nFl + 1); i++)
            {
                OAD = (Dl645B_RmEgSh[nItem].OI_698 << 16) + 0x0200 + (i + 1);
                fnGet_EnergyData(OAD, &temp[0]);
                temp32 = Std_Lsb32DataGet(&temp[0]);
                temp32 = fnHexToBcd_u32(temp32);
                Std_Memcpy(Dst + i * 4, (u8 *)&temp32, 4);
            }
        }
    }
    else
    {
        Std_Memcpy((u8 *)&temp_tab, &RmEgShRecTime_Tab, sizeof(sDispItem_TypeDef));
        temp_tab.M_Element = nRecord; //上几月
        fnGet_DispData(&temp_tab, &temp[0], &temp16);  //temp:数据类型(1byte) +hexData
    }
    return (SUCCESS);
}

//---获取当前、结算电量数据------------------------------------------------
eDL645B_ErrInfo_TypeDef fnDl645_GetRmEgSh(u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    u8 nRecord;
    u16 nItem, ItemLen, OnceLen;
    u32 FindAddr, OffAddr;
    ErrorStatus err;
    u16 temp16 = 0;
    u8 temp[20];
    const sDispItem_TypeDef  RmEgShRecTime_Tab = {0x00, 0x00, 0x02, 0x21, 0x20, 0x01, 0x02, 0x05, 0x50, 0x01}; //698 读取结算日时间 MOAD
    sDF29  tmpClock;
    sDispItem_TypeDef   temp_tab;

    FindAddr = 0 ;
    OffAddr = 0;
    *Len = 0 ;
    OnceLen = 0;

    if ((DI2 == 0x90) || (DI2 == 0x0B) || (DI2 == 0x80) || (DI2 == 0x0c))
    {
        u32 DI;
        DI = (DI2 << 16) + (DI1 << 8) + (DI0);
        switch (DI)
        {
                #if(METERTYPE ==2)
            case 0x00900100:                //剩余电量
                ItemLen = 0x04 ;
                Std_Memcpy(Dst, &EgMoney.PubData.CurSurplusEg, ItemLen);
                *Len = ItemLen;
                break;
            case 0x00900101:                //透支电量
                ItemLen = 0x04 ;
                Std_Memcpy(Dst, &EgMoney.PubData.CurOverdraftEg, ItemLen);
                *Len = ItemLen;
                break;
            case 0x00900200:                //剩余金额
                ItemLen = 0x04 ;
                Std_Memcpy(Dst, &EgMoney.PubData.CurSurplusMoney.Dat2, ItemLen);
                *Len = ItemLen;
                break;
            case 0x00900201:                //透支金额
                ItemLen = 0x04 ;
                Std_Memcpy(Dst, &EgMoney.PubData.CurOverdraftMoney.Dat2, ItemLen);
                *Len = ItemLen;
                break;
            case 0x000c0000:                //当前月度用电量
                ItemLen = 0x04 ;
                Std_Memcpy(Dst, &CurApplyEg.CurMonthEgSh, ItemLen);
                *Len = ItemLen;
                break;
                #endif
            case 0x000b0000:                //当前结算周期组合有功总累计用电量
                ItemLen = 0x04 ;
                Std_Memcpy(Dst, &EgMoney.PubData.CurApplyEg, ItemLen);
                *Len = ItemLen;
                break;
            case 0x000b0001:                //上1结算周期组合有功总累计用电量
                ItemLen = 0x04 ;
                Std_Memcpy(Dst, &EgMoney.PubData.Rmday1ApplyEg, ItemLen);
                *Len = ItemLen;
                //fnDl645File_Read(Dl645FileId_RmApplyEgSh , Dl645FileItemInfoOffAddr_RmApplyEgShFile_RmDayEgSh , Dst , sizeof(sFsEgSh_TypeDef) );
                //*Len = sizeof(sFsEgSh_TypeDef);
                break;
            default:
                return (DL645B_ERRINFO_DATA);
        }
        return (DL645B_ERRINFO_OK);
    }
    #if(METERTYPE ==2)
    if ((DI2 == 0x0d) && (DI1 == 0x00) && (DI0 < 0x05))     // 上4次年结算日数据
    {
        if (DI0 == 0)       // 当前年结算组合有功累计用电量
        {
            Dst[0] = SysClock.Hour;
            Dst[1] = SysClock.Day;
            Dst[2] = SysClock.Month;
            Dst[3] = SysClock.Year;
            Dst += 4;
            if (Bkgrd.PubData.RmYearFlag)
            {
                Std_Memset(Dst, 0x00, 4);
            }
            else
            {
                Std_Memcpy(Dst, (u8 *)&CurApplyEg.CurYearEgSh, 4);
            }
            *Len = sizeof(sDl645YearApplyEgShFile_TypeDef);
        }

        return (DL645B_ERRINFO_OK);
    }
    #endif
    if ((DI2 == 0xfe) && (DI1 == 0x00) && ((DI0 < 0x0d) || (DI0 == 0xff)) && (DI0 != 0)) //上12次月结算日时间
    {
        Std_Memcpy((u8 *)&temp_tab, &RmEgShRecTime_Tab, sizeof(sDispItem_TypeDef));
        if (DI0 == 0xff)
        {
            OnceLen = sizeof(sDF29);
            for (nRecord = 1 ; nRecord <= DL645_MAX_RMDAY ; nRecord++)
            {
                temp_tab.M_Element = nRecord; //上几月
                fnGet_DispData(&temp_tab, &temp[0], &temp16);  //temp:数据类型(1byte) +hexData
                //------格式转换------------------------
                Std_Msb16DataSet(&temp[1], temp16);
                tmpClock.Year = (u8)(temp16 - 2000);
                tmpClock.Year = fnHexToBcd_u8(tmpClock.Year);
                tmpClock.Month = fnHexToBcd_u8(temp[3]);
                tmpClock.Day = fnHexToBcd_u8(temp[4]);
                tmpClock.Hour = fnHexToBcd_u8(temp[5]);
                Std_Memcpy(Dst, (u8 *)&tmpClock, sizeof(sDF29));
                *Len += OnceLen;
                Dst += OnceLen;
            }
        }
        else
        {
            *Len = sizeof(sDF29);
            temp_tab.M_Element = DI0; //上几月
            fnGet_DispData(&temp_tab, &temp[0], &temp16);  //temp:数据类型(1byte) +hexData
            //------格式转换------------------------
            Std_Msb16DataSet(&temp[1], temp16);
            tmpClock.Year = (u8)(temp16 - 2000);
            tmpClock.Year = fnHexToBcd_u8(tmpClock.Year);
            tmpClock.Month = fnHexToBcd_u8(temp[3]);
            tmpClock.Day = fnHexToBcd_u8(temp[4]);
            tmpClock.Hour = fnHexToBcd_u8(temp[5]);
            Std_Memcpy(Dst, (u8 *)&tmpClock, sizeof(sDF29));
        }
        return (DL645B_ERRINFO_OK);
    }
    //  if(((DI2 == 0x60)||(DI2 == 0x61))&&(DI1 == 0x00))       // 2014增补精确电能
    //  {
    //
    //  }
    if ((DI1 != 0xff) && (DI1 > MAX_FL))
    {
        return (DL645B_ERRINFO_FL);
    }
    if (DI0 == 0xff)
    {
        for (nRecord = 0 ; nRecord <= DL645_MAX_RMDAY ; nRecord++)
        {
            if (DI2 == 0xff)
            {
                if (DI1 != 0xff)
                {
                    return (DL645B_ERRINFO_DATA);
                }

                for (nItem = 0 ; nItem < (sizeof(Dl645B_RmEgSh) / sizeof(sDl645B_RmEgSh_TypeDef)) ; nItem++)
                {
                    err = fnDl645_GetRmEgShItemLen(nItem, DI1, &ItemLen);
                    if (err != SUCCESS)
                    {
                        return (DL645B_ERRINFO_DATA);
                    }

                    if ((FindAddr + *Len + ItemLen) > (DL645B_FRAME_MAXLEN * Seq))
                    {
                        if (*Len == 0)
                        {
                            OnceLen = FindAddr + ItemLen - DL645B_FRAME_MAXLEN * Seq;
                            OffAddr = ItemLen - OnceLen;
                        }
                        else
                        {
                            OnceLen = ItemLen;
                            OffAddr = 0;
                        }
                        if ((*Len + OnceLen) > DL645B_FRAME_MAXLEN)
                        {
                            OnceLen = DL645B_FRAME_MAXLEN - *Len;
                        }

                        if (fnDl645_GetRmEgShItem(nItem, DI1, nRecord, OffAddr, OnceLen, Dst) != SUCCESS)
                        {
                            return (DL645B_ERRINFO_FL);
                        }
                        *Len += OnceLen;
                        if (*Len >= DL645B_FRAME_MAXLEN)
                        {
                            if ((OnceLen < ItemLen) ||
                                (nItem < (sizeof(Dl645B_RmEgSh) / sizeof(sDl645B_RmEgSh_TypeDef))) ||
                                (nRecord < DL645_MAX_RMDAY))
                            {
                                return (DL645B_ERRINFO_SEQDATA);
                            }
                            else
                            {
                                return (DL645B_ERRINFO_OK);
                            }
                        }
                        Dst += OnceLen;
                    }
                    else
                    {
                        FindAddr += ItemLen;
                    }
                }
            }
            else
            {
                err = fnDl645_FindRmEgSh(DI2, &nItem);
                if (err != SUCCESS)
                {
                    return (DL645B_ERRINFO_DATA);
                }
                err = fnDl645_GetRmEgShItemLen(nItem, DI1, &ItemLen);
                if (err != SUCCESS)
                {
                    return (DL645B_ERRINFO_DATA);
                }

                if ((FindAddr + *Len + ItemLen) > (DL645B_FRAME_MAXLEN * Seq))
                {
                    if (*Len == 0)
                    {
                        OnceLen = FindAddr + ItemLen - DL645B_FRAME_MAXLEN * Seq;
                        OffAddr = ItemLen - OnceLen;
                    }
                    else
                    {
                        OnceLen = ItemLen;
                        OffAddr = 0;
                    }
                    if ((*Len + OnceLen) > DL645B_FRAME_MAXLEN)
                    {
                        OnceLen = DL645B_FRAME_MAXLEN - *Len;
                    }

                    fnDl645_GetRmEgShItem(nItem, DI1, nRecord, OffAddr, OnceLen, Dst);
                    *Len += OnceLen;
                    if (*Len >= DL645B_FRAME_MAXLEN)
                    {
                        if ((OnceLen < ItemLen) ||
                            (nRecord < DL645_MAX_RMDAY))
                        {
                            return (DL645B_ERRINFO_SEQDATA);
                        }
                        else
                        {
                            return (DL645B_ERRINFO_OK);
                        }
                    }
                    Dst += OnceLen;
                }
                else
                {
                    FindAddr += ItemLen;
                }
            }
        }
    }
    else
    {
        if (DI0 > DL645_MAX_RMDAY)
        {
            return (DL645B_ERRINFO_DATA);
        }

        if (DI2 == 0xff)
        {
            if (DI1 != 0xFF)
            {
                return (DL645B_ERRINFO_DATA);
            }

            for (nItem = 0 ; nItem < (sizeof(Dl645B_RmEgSh) / sizeof(sDl645B_RmEgSh_TypeDef)) ; nItem++)
            {
                err = fnDl645_GetRmEgShItemLen(nItem, DI1, &ItemLen);
                if (err != SUCCESS)
                {
                    return (DL645B_ERRINFO_DATA);
                }

                if ((FindAddr + *Len + ItemLen) > (DL645B_FRAME_MAXLEN * Seq))
                {
                    if (*Len == 0)
                    {
                        OnceLen = FindAddr + ItemLen - DL645B_FRAME_MAXLEN * Seq;
                        OffAddr = ItemLen - OnceLen;
                    }
                    else
                    {
                        OnceLen = ItemLen;
                        OffAddr = 0;
                    }
                    if ((*Len + OnceLen) > DL645B_FRAME_MAXLEN)
                    {
                        OnceLen = DL645B_FRAME_MAXLEN - *Len;
                    }

                    fnDl645_GetRmEgShItem(nItem, DI1, DI0, OffAddr, OnceLen, Dst);
                    *Len += OnceLen;
                    if (*Len >= DL645B_FRAME_MAXLEN)
                    {
                        if ((OnceLen < ItemLen) ||
                            (nItem < (sizeof(Dl645B_RmEgSh) / sizeof(sDl645B_RmEgSh_TypeDef))))
                        {
                            return (DL645B_ERRINFO_SEQDATA);
                        }
                        else
                        {
                            return (DL645B_ERRINFO_OK);
                        }
                    }
                    Dst += OnceLen;
                }
                else
                {
                    FindAddr += ItemLen;
                }
            }
        }
        else
        {
            err = fnDl645_FindRmEgSh(DI2, &nItem);
            if (err != SUCCESS)
            {
                return (DL645B_ERRINFO_DATA);
            }
            err = fnDl645_GetRmEgShItemLen(nItem, DI1, &ItemLen);
            if (err != SUCCESS)
            {
                return (DL645B_ERRINFO_DATA);
            }

            *Len = ItemLen - DL645B_FRAME_MAXLEN * Seq;

            if (*Len > DL645B_FRAME_MAXLEN)
            {
                *Len = DL645B_FRAME_MAXLEN;
                fnDl645_GetRmEgShItem(nItem, DI1, DI0, OffAddr, *Len, Dst);
                return (DL645B_ERRINFO_SEQDATA);
            }
            else
            {
                fnDl645_GetRmEgShItem(nItem, DI1, DI0, OffAddr, *Len, Dst);
                return (DL645B_ERRINFO_OK);
            }
        }
    }
    if (*Len == 0)
    {
        return (DL645B_ERRINFO_DATA);
    }
    else
    {
        return (DL645B_ERRINFO_OK);
    }
}

eDL645B_ErrInfo_TypeDef fnDl645_GetRmNeed(u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

//---获取当前变量数据------------------------------------------------
eDL645B_ErrInfo_TypeDef fnDl645_GetVar(u8 DI2, u8 DI1, u8 DI0, u8 *Dst, u16 *Len)
{
    u32 DITemp, temp32;

    u16 ItemLen, i, temp16;
    u8 tempdi[4];
    *Len = 0;

    tempdi[0] = DI0;
    tempdi[1] = DI1;
    tempdi[2] = DI2;
    tempdi[3] = 0;
    Std_Memcpy(&DITemp, &tempdi, 4);

    switch (DITemp)
    {
        case 0x00010100: //电压
        case 0x00010200:
        case 0x00010300:
        case 0x0001FF00:
            if (DI1 == 0xff)
            {
                for (i = 0 ; i < 3 ; i++)
                {
                    temp16 = fnHexToBcd_u16((MeasureRms.PubData.U[i] + 50) / 100);  // dyf 3位小数四舍五入为1位小数
                    ItemLen = 2 ;
                    Std_Memcpy(Dst, &temp16, ItemLen);
                    *Len += ItemLen;
                    Dst += ItemLen;
                }
            }
            else
            {
                temp16 = fnHexToBcd_u16((MeasureRms.PubData.U[DI1 - 1] + 50) / 100); // dyf 3位小数四舍五入为1位小数
                ItemLen = 2 ;
                Std_Memcpy(Dst, &temp16, ItemLen);
                *Len = ItemLen;
            }
            break;
        //-----------
        case 0x00020100:    //电流
        case 0x00020200:
        case 0x00020300:
        case 0x0002FF00:
            if (DI1 == 0xff)
            {
                for (i = 0 ; i < 3 ; i++)
                {
                    temp32 = fnHexToBcd_u32(abs(MeasureRms.PubData.I[i]) / 10);
                    ItemLen = 4 ;
                    Std_Memcpy(Dst, &temp32, ItemLen);
                    *Len += ItemLen;
                    Dst += ItemLen;
                }
            }
            else
            {
                temp32 = fnHexToBcd_u32(abs(MeasureRms.PubData.I[DI1 - 1]) / 10);
                ItemLen = 4 ;
                Std_Memcpy(Dst, &temp32, ItemLen);
                *Len = ItemLen;
            }
            break;
        //-----------
        case 0x00030000:    //瞬时有功、无功、视在功率
        case 0x00030100:
        case 0x00030200:
        case 0x00030300:
        case 0x0003FF00:

        case 0x00040000:
        case 0x00040100:
        case 0x00040200:
        case 0x00040300:
        case 0x0004FF00:

        case 0x00050000:
        case 0x00050100:
        case 0x00050200:
        case 0x00050300:
        case 0x0005FF00:
            if (DI1 == 0xff)
            {
                for (i = 0 ; i < 4 ; i++)
                {
                    ItemLen = 4 ;
                    temp32 = fnHexToBcd_u32(abs(MeasureRms.PubData.Pw[(DI2 - 3) * 4 + i]));
                    Std_Memcpy(Dst, &temp32, ItemLen);
                    *Len += ItemLen;
                    Dst += ItemLen;
                }
            }
            else
            {
                ItemLen = 4 ;
                temp32 = fnHexToBcd_u32(abs(MeasureRms.PubData.Pw[(DI2 - 3) * 4 + DI1]));
                Std_Memcpy(Dst, &temp32, ItemLen);
                *Len += ItemLen;
            }
            break;
        //-----------
        case 0x00060000:    //功率因数
        case 0x00060100:
        case 0x00060200:
        case 0x00060300:
        case 0x0006FF00:
            if (DI1 == 0xff)
            {
                for (i = 0 ; i < 4 ; i++)
                {
                    temp16 = fnHexToBcd_u16(abs(MeasureRms.PubData.Pf[i]));
                    ItemLen = 2 ;
                    Std_Memcpy(Dst, &temp16, ItemLen);
                    *Len += ItemLen;
                    Dst += ItemLen;
                }
            }
            else
            {
                temp16 = fnHexToBcd_u16(abs(MeasureRms.PubData.Pf[DI1]));
                ItemLen = 2 ;
                Std_Memcpy(Dst, &temp16, ItemLen);
                *Len += ItemLen;
            }
            break;
        //-----------
        case 0x00070100:    //相角
        case 0x00070200:
        case 0x00070300:
        case 0x0007FF00:
            if (DI1 == 0xff)
            {
                for (i = 0 ; i < 3 ; i++)
                {
                    temp16 = fnHexToBcd_u16(MeasureRms.PubData.Angle[3 + i]);
                    ItemLen = 2 ;
                    Std_Memcpy(Dst, &temp16, ItemLen);
                    *Len += ItemLen;
                    Dst += ItemLen;
                }
            }
            else
            {
                temp16 = fnHexToBcd_u16(MeasureRms.PubData.Angle[DI1 - 1 + 3]);
                ItemLen = 2 ;
                Std_Memcpy(Dst, &temp16, ItemLen);
                *Len += ItemLen;
            }
            break;
        //-----------
        case 0x00800001:
            temp16 = fnHexToBcd_u16(abs(MeasureRms.PubData.In) / 10);
            ItemLen = 2 ;
            Std_Memcpy(Dst, &temp16, ItemLen);
            *Len = ItemLen;
            break;
        case 0x00800002:
            temp16 = fnHexToBcd_u16(MeasureRms.PubData.Frequency);
            ItemLen = 2 ;
            Std_Memcpy(Dst, &temp16, ItemLen);
            *Len = ItemLen;
            break;
        case 0x00800003:
            temp32 = fnHexToBcd_u32(abs(MeasureRms.PubData.PPwave[0]));
            ItemLen = 4 ;
            Std_Memcpy(Dst, &temp32, ItemLen);
            *Len = ItemLen;
            break;

        case 0x00800007:
            temp16 = fnHexToBcd_u16(Bkgrd.PubData.Temperature);
            ItemLen = 2 ;
            Std_Memcpy(Dst, &temp16, ItemLen);
            *Len = ItemLen;
            break;
        case 0x00800017:
            ItemLen = 4 ;
            Std_Memcpy(Dst, &Bkgrd.PubData.Temperature2, ItemLen);
            *Len = ItemLen;
            break;
        case 0x00800027:
            ItemLen = 4 ;
            Std_Memcpy(Dst, &(*(uint32_t *)(0x4003C0F8)), ItemLen);
            *Len = ItemLen;
            break;
        case 0x00800008:
            temp16 = fnHexToBcd_u16(Bkgrd.PubData.ClockBat);
            ItemLen = 2 ;
            Std_Memcpy(Dst, &temp16, ItemLen);
            *Len = ItemLen;
            break;
        case 0x00800009:
            temp16 = fnHexToBcd_u16(Bkgrd.PubData.BackupBat);
            ItemLen = 2 ;
            Std_Memcpy(Dst, &temp16, ItemLen);
            *Len = ItemLen;
            break;

            #if(METERTYPE)
        case 0x00800022:                            // 身份认证有效时间
            ItemLen = fnHexToBcd_u16(Secret.Master.tESAMDly);
            Std_Memcpy(Dst, (u8 *)&ItemLen, 2);
            *Len = 2;
            break;
        case 0x00800023:                          // 红外认证剩余时间
            Dst[0] = fnHexToBcd_u8(Secret.tIRDly);
            *Len = 1;
            break;
            #endif

        case 0x00810001:    //增补
            Dst[0] = Bkgrd.PubData.Fl;
            Dst[1] = Bkgrd.PubData.nPOT;
            Dst[2] = Bkgrd.PubData.nDayPOT;
            Dst[3] = Bkgrd.PubData.nTZone;
            *Len = 4;
            break;
        default:
            return (DL645B_ERRINFO_DATA);
    }
    return (DL645B_ERRINFO_OK);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetVolEv(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

//---------------------------------------
eDL645B_ErrInfo_TypeDef fnDl645_GetInPhaEv(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetAInSwimEv(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetUnblEv(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

ErrorStatus fnDl645_GetCurEvItem(u8 DI3, u8 DI2, u16 nItem, u8 nRecord, u32 OffAddr, u16 Len, u8 *Dst)
{
    return (SUCCESS);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetCurEv(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetWaveEv(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetOverPfEv(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

//---获取事件记录(以下按DL645-2007)-----------
eDL645B_ErrInfo_TypeDef fnDl645_GetQLossVolEv(u8 DI1, u8 DI0, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetLossAuxEv(u8 DI1, u8 DI0, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

ErrorStatus fnDl645_GetStatItem(u8 DI1, u8 nRecord, u32 OffAddr, u16 Len, u8 *Dst)
{
    //  u8  pRecord;

    return (SUCCESS);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetStat(u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    u8 nRecord;
    u16 ItemLen, OnceLen;
    u32 FindAddr, OffAddr;

    *Len = 0;
    if (DI1 > 0x03)
    {
        return (DL645B_ERRINFO_DATA);
    }
    if ((DI0 != 0xff) && (DI0 > MAX_EVSTAT))
    {
        return (DL645B_ERRINFO_DATA);
    }

    if (DI0 == 0xff)
    {
        FindAddr = 0 ;
        OffAddr = 0;
        *Len = 0 ;
        OnceLen = 0;
        for (nRecord = 0 ; nRecord <= MAX_EVSTAT ; nRecord++)
        {
            ItemLen = sizeof(sUEligStat_TypeDef) - 3;

            if ((FindAddr + *Len + ItemLen) > (DL645B_FRAME_MAXLEN * Seq))
            {
                if (*Len == 0)
                {
                    OnceLen = FindAddr + ItemLen - DL645B_FRAME_MAXLEN * Seq;
                    OffAddr = ItemLen - OnceLen;
                }
                else
                {
                    OnceLen = ItemLen;
                    OffAddr = 0;
                }
                if ((*Len + OnceLen) > DL645B_FRAME_MAXLEN)
                {
                    OnceLen = DL645B_FRAME_MAXLEN - *Len;
                }

                fnDl645_GetStatItem(DI1, nRecord, OffAddr, OnceLen, Dst);
                *Len += OnceLen;
                if (*Len >= DL645B_FRAME_MAXLEN)
                {
                    if ((OnceLen < ItemLen) ||
                        (nRecord < MAX_EVSTAT))
                    {
                        return (DL645B_ERRINFO_SEQDATA);
                    }
                    else
                    {
                        return (DL645B_ERRINFO_OK);
                    }
                }
                Dst += OnceLen;
            }
            else
            {
                FindAddr += ItemLen;
            }
        }
    }
    else
    {
        *Len = sizeof(sUEligStat_TypeDef) - 3;
        fnDl645_GetStatItem(DI1, DI0, 0, *Len, Dst);
    }
    return (DL645B_ERRINFO_OK);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetPowDnEv(u8 DI1, u8 DI0, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetOverNeedEv(u8 DI1, u8 DI0, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

//---获取当前购电金额事件记录数据-----------------------------------------------------
eDL645B_ErrInfo_TypeDef fnDl645_GetBuyMoneyEv(u8 DI1, u8 DI0, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

//---获取当前购电电量事件记录数据-----------------------------------------------------
eDL645B_ErrInfo_TypeDef fnDl645_GetBuyEgEv(u8 DI1, u8 DI0, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

const sDl645B_MisEvRecord_TypeDef MiscEvRecord[] =
{
    0, 0, 0
};

//get esam信息接口
eDL645B_ErrInfo_TypeDef fnDl645_GetEsamInfo(u32 Oad, u8 *Dst, u16 *Len)
{
    return DL645B_ERRINFO_OK;
}

ErrorStatus fnDl645_GetMiscEvItemLen(u8 DI1, u16 *Len)
{
    if ((DI1 > 0x14) || (DI1 == 0x11))
    {
        return (ERROR);
    }
    if (MiscEvRecord[DI1].Len == 0)
    {
        return (ERROR);
    }
    *Len = MiscEvRecord[DI1].Len;
    return (SUCCESS);
}

ErrorStatus fnDl645_GetMiscItem(u8 DI1, u8 nRecord, u32 OffAddr, u16 Len, u8 *Dst)
{
    //  u8  pEv;
    return (SUCCESS);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetMiscEv(u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    u8 nRecord;
    u16 ItemLen, OnceLen;
    u32 FindAddr, OffAddr;
    ErrorStatus err;

    *Len = 0;
    if (DI1 == 0x14)        //非法插卡总次数
    {
        if (DI0 != 0x00)
        {
            return (DL645B_ERRINFO_DATA);
        }
        *Len = sizeof(sDF10);

        return (DL645B_ERRINFO_OK);
    }
    else
    {
        if (DI1 > 0x13)
        {
            return (DL645B_ERRINFO_DATA);
        }
        if (DI1 == 0x11)
        {
            return (DL645B_ERRINFO_DATA);
        }
        if ((DI0 != 0xff) && (DI0 > MiscEvRecord[DI1].MaxEventCount))
        {
            return (DL645B_ERRINFO_DATA);
        }

        if (DI0 == 0x00)
        {
            *Len = sizeof(sDF10);
        }
        else if (DI0 == 0xff)
        {
            FindAddr = 0 ;
            OffAddr = 0;
            *Len = 0 ;
            OnceLen = 0;
            for (nRecord = 1 ; nRecord <= MiscEvRecord[DI1].MaxEventCount ; nRecord++)
            {
                err = fnDl645_GetMiscEvItemLen(DI1, &ItemLen);
                if (err != SUCCESS)
                {
                    return (DL645B_ERRINFO_DATA);
                }

                if ((FindAddr + *Len + ItemLen) > (DL645B_FRAME_MAXLEN * Seq))
                {
                    if (*Len == 0)
                    {
                        OnceLen = FindAddr + ItemLen - DL645B_FRAME_MAXLEN * Seq;
                        OffAddr = ItemLen - OnceLen;
                    }
                    else
                    {
                        OnceLen = ItemLen;
                        OffAddr = 0;
                    }
                    if ((*Len + OnceLen) > DL645B_FRAME_MAXLEN)
                    {
                        OnceLen = DL645B_FRAME_MAXLEN - *Len;
                    }

                    fnDl645_GetMiscItem(DI1, nRecord, OffAddr, OnceLen, Dst);
                    *Len += OnceLen;
                    if (*Len >= DL645B_FRAME_MAXLEN)
                    {
                        if ((OnceLen < ItemLen) ||
                            (nRecord <= 10))
                        {
                            return (DL645B_ERRINFO_SEQDATA);
                        }
                        else
                        {
                            return (DL645B_ERRINFO_OK);
                        }
                    }
                    Dst += OnceLen;
                }
                else
                {
                    FindAddr += ItemLen;
                }
            }
        }
        else
        {
            if (DI0 > MiscEvRecord[DI1].MaxEventCount)
            {
                return (DL645B_ERRINFO_DATA);
            }

            err = fnDl645_GetMiscEvItemLen(DI1, &ItemLen);
            if (err != SUCCESS)
            {
                return (DL645B_ERRINFO_DATA);
            }

            if (ItemLen <= (DL645B_FRAME_MAXLEN * Seq))
            {
                return (DL645B_ERRINFO_DATA);
            }

            *Len = ItemLen - DL645B_FRAME_MAXLEN * Seq;
            OffAddr = DL645B_FRAME_MAXLEN * Seq;

            if (*Len > DL645B_FRAME_MAXLEN)
            {
                *Len = DL645B_FRAME_MAXLEN;
                fnDl645_GetMiscItem(DI1, DI0, OffAddr, *Len, Dst);
                return (DL645B_ERRINFO_SEQDATA);
            }
            else
            {
                fnDl645_GetMiscItem(DI1, DI0, OffAddr, *Len, Dst);
                return (DL645B_ERRINFO_OK);
            }
        }
        return (DL645B_ERRINFO_OK);
    }
}

const sDl645B_MisEvRecord_TypeDef OtherEvRecord[] =
{
    0, 0, 0
};

ErrorStatus fnDl645_GetOtherEvItemLen(u8 DI2, u16 *Len)
{
    if (OtherEvRecord[DI2].Len == 0)
    {
        return (ERROR);
    }
    *Len = OtherEvRecord[DI2].Len;
    return (SUCCESS);
}

ErrorStatus fnDl645_GetOtherEvItem(u8 DI2, u8 nRecord, u32 OffAddr, u16 Len, u8 *Dst)
{
    return (SUCCESS);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetOtherEv(u8 DI2, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetEv(u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    eDL645B_ErrInfo_TypeDef err;

    switch (DI2)
    {
        case 0x05:
            err = fnDl645_GetQLossVolEv(DI1, DI0, Dst, Len);
            break;
        case 0x06:
            err = fnDl645_GetLossAuxEv(DI1, DI0, Dst, Len);
            break;
        case 0x10:
            err = fnDl645_GetStat(DI1, DI0, Seq, Dst, Len);
            break;
        case 0x11:
            err = fnDl645_GetPowDnEv(DI1, DI0, Dst, Len);
            break;
        case 0x12:
            err = fnDl645_GetOverNeedEv(DI1, DI0, Dst, Len);
            break;
        case 0x30:
            err = fnDl645_GetMiscEv(DI1, DI0, Seq, Dst, Len);
            break;
            #if(METERTYPE ==2)
        case 0x32:
            err = fnDl645_GetBuyEgEv(DI1, DI0, Dst, Len);
            break;
        case 0x33:
            err = fnDl645_GetBuyMoneyEv(DI1, DI0, Dst, Len);
            break; // 购电记录
            #endif
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
            if (DI1 == 0)
            {
                err = fnDl645_GetOtherEv(DI2, DI0, Seq, Dst, Len);
            }
            else
            {
                err = DL645B_ERRINFO_DATA;
            }
            break;
        default:
            return (DL645B_ERRINFO_DATA);
    }
    return (err);
}

// 读取跳闸事件记录
eDL645B_ErrInfo_TypeDef fnDl645_GetGateOffEv(u8 DI2, u8 DI1, u8 DI0, u8 *Dst, u16 *Len)
{
    /*
       u8 pEv , nRecord;
       u32 OffAddr , OnceLen;
       u8 pEvTemp;

       *Len = 0;
       if(DI2 != 0x00) return(DL645B_ERRINFO_DATA);
       if((DI0 < 1) && (DI0 > MAX_GATEOFF_EVRECORD))  return(DL645B_ERRINFO_DATA);

       if(DI1 == 0x00)
       {
           *Len = sizeof(sDF10);
       }
       else if(DI0 == 0xff)
       {
           switch(DI1)
           {
               case 0x01:
                   OffAddr = 0;
                   OnceLen = 6;
                   break;
               case 0x02:
                   OffAddr = 6;
                   OnceLen = 4;
                   break;
               case 0x03:
                   OffAddr = 10;
                   OnceLen = 4;
                   break;
               case 0x04:
                   OffAddr = 14;
                   OnceLen = 4;
                   break;
               case 0x05:
                   OffAddr = 18;
                   OnceLen = 4;
                   break;
               case 0x06:
                   OffAddr = 22;
                   OnceLen = 4;
                   break;
               case 0x07:
                   OffAddr = 26;
                   OnceLen = 4;
                   break;
               case 0x08:
                   OffAddr = 30;
                   OnceLen = 4;
                   break;
               default: return(DL645B_ERRINFO_DATA);
           }

           pEv &= 0x7F;
           if(pEv > MAX_GATEOFF_EVRECORD) pEv = 0;

           for(nRecord = 1 ; nRecord <= MAX_GATEOFF_EVRECORD ; nRecord++)
           {
               pEvTemp = (pEv + MAX_GATEOFF_EVRECORD - nRecord) % MAX_GATEOFF_EVRECORD;

               Dst += OnceLen ; *Len += OnceLen;
           }
       }
       else if(DI1 == 0xff)
       {
           pEv &= 0x7F;
           if(pEv > MAX_GATEOFF_EVRECORD) pEv = 0;

           pEv = (pEv + MAX_GATEOFF_EVRECORD - DI0) % MAX_GATEOFF_EVRECORD;

           *Len += OnceLen;
       }
       else
       {
           switch(DI1)
           {
               case 0x01:
                   OffAddr = 0;
                   OnceLen = 6;
                   break;
               case 0x02:
                   OffAddr = 6;
                   OnceLen = 4;
                   break;
               case 0x03:
                   OffAddr = 10;
                   OnceLen = 4;
                   break;
               case 0x04:
                   OffAddr = 14;
                   OnceLen = 4;
                   break;
               case 0x05:
                   OffAddr = 18;
                   OnceLen = 4;
                   break;
               case 0x06:
                   OffAddr = 22;
                   OnceLen = 4;
                   break;
               case 0x07:
                   OffAddr = 26;
                   OnceLen = 4;
                   break;
               case 0x08:
                   OffAddr = 30;
                   OnceLen = 4;
                   break;
               default: return(DL645B_ERRINFO_DATA);
           }

           *Len += OnceLen;
       }*/
    return (DL645B_ERRINFO_OK);
}

// 读取合闸事件记录
eDL645B_ErrInfo_TypeDef fnDl645_GetGateOnEv(u8 DI2, u8 DI1, u8 DI0, u8 *Dst, u16 *Len)
{
    /*
       u8 pEv , nRecord;
       u32 OffAddr , OnceLen;
       u8 pEvTemp;

       *Len = 0;
       if(DI2 != 0x00) return(DL645B_ERRINFO_DATA);
       if((DI0 < 1) && (DI0 > MAX_GATEON_EVRECORD))  return(DL645B_ERRINFO_DATA);

       if(DI1 == 0x00)
       {
           *Len = sizeof(sDF10);
       }
       else if(DI0 == 0xff)
       {
           switch(DI1)
           {
               case 0x01:
                   OffAddr = 0;
                   OnceLen = 6;
                   break;
               case 0x02:
                   OffAddr = 6;
                   OnceLen = 4;
                   break;
               case 0x03:
                   OffAddr = 10;
                   OnceLen = 4;
                   break;
               case 0x04:
                   OffAddr = 14;
                   OnceLen = 4;
                   break;
               case 0x05:
                   OffAddr = 18;
                   OnceLen = 4;
                   break;
               case 0x06:
                   OffAddr = 22;
                   OnceLen = 4;
                   break;
               case 0x07:
                   OffAddr = 26;
                   OnceLen = 4;
                   break;
               case 0x08:
                   OffAddr = 30;
                   OnceLen = 4;
                   break;
               default: return(DL645B_ERRINFO_DATA);
           }
       }
       else if(DI1 == 0xff)
       {
           pEv &= 0x7F;
           if(pEv > MAX_GATEON_EVRECORD) pEv = 0;

           *Len += OnceLen;
       }
       else
       {
           switch(DI1)
           {
               case 0x01:
                   OffAddr = 0;
                   OnceLen = 6;
                   break;
               case 0x02:
                   OffAddr = 6;
                   OnceLen = 4;
                   break;
               case 0x03:
                   OffAddr = 10;
                   OnceLen = 4;
                   break;
               case 0x04:
                   OffAddr = 14;
                   OnceLen = 4;
                   break;
               case 0x05:
                   OffAddr = 18;
                   OnceLen = 4;
                   break;
               case 0x06:
                   OffAddr = 22;
                   OnceLen = 4;
                   break;
               case 0x07:
                   OffAddr = 26;
                   OnceLen = 4;
                   break;
               case 0x08:
                   OffAddr = 30;
                   OnceLen = 4;
                   break;
               default: return(DL645B_ERRINFO_DATA);
           }

           *Len += OnceLen;
       }*/
    return (DL645B_ERRINFO_OK);
}

//---获取冻结数据------------------------------------------------
/*
const sDl645B_Frz_TypeDef FrzItem[]=
{
};

const sDl645B_Frz_TypeDef HourFrzItem[]=
{
};
const sDl645B_FrzFile_TypeDef FrzFile[] =
{
};
*/
ErrorStatus fnDl645_FindFrz(u8 DI2, u8 DI1, u16 *nItem)
{
    /*
        if(DI2 == 0x04)
        {
            if(DI1 >= (sizeof(HourFrzItem) / sizeof(sDl645B_Frz_TypeDef) ) )  return(ERROR);
            *nItem = DI1;
        }
        else
        {
            if(DI1 == 0x10)
            {
                *nItem = 11;
            }
            else if(DI1 < (sizeof(FrzItem) / sizeof(sDl645B_Frz_TypeDef) - 1) )
            {
                *nItem = DI1;
            }
            else
            {
                return(ERROR);
            }
        }
    */
    return (SUCCESS);
}

ErrorStatus fnDl645_GetFrzItemLen(u8 DI2, u16 nItem, u16 *Len)
{
    return (ERROR);
}

/*
ErrorStatus fnDl645_GetFrzItem(u8 DI2 , u16 nItem , u8 nRecord ,u32 OffAddr , u16 Len , u8 *Dst)
{
    return(SUCCESS);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetFrz(u8 DI2 , u8 DI1 , u8 DI0 , u8 Seq , u8 *Dst , u16 *Len)
{
    return(SUCCESS);
}
*/
//---获取参变量------------------------------------------------
const sDl645B_ParaVar_TypeDef ParaVar[] =
{
    {0x000103, 0xC1, FileId_ParaDoc, 1, FileItemInfoOffAddr_DocPara_NeedCyc },
    {0x000104, 0xC1, FileId_ParaDoc, 1, FileItemInfoOffAddr_DocPara_NeedSlip },
    {0x000105, 0x41, FileId_ParaDoc, 2, FileItemInfoOffAddr_DocPara_PlsWidth },
    {0x000106, 0xC1, FileId_RatePara, sizeof(sDF15), FileItemInfoOffAddr_RatePara_TimeZonePara + 0 },
    {0x000107, 0xC1, FileId_RatePara, sizeof(sDF15), FileItemInfoOffAddr_RatePara_POTTablePara + 0 },
    #if(METERTYPE ==2)
    {0x000108, 0x41, FileId_RatePara, sizeof(sDF15), FileItemInfoOffAddr_RatePara_RatePricePara + 0 },
    {0x000109, 0x41, FileId_RatePara, sizeof(sDF15), FileItemInfoOffAddr_RatePara_LadderPara + 0 },
    #endif

    {0x000201, 0xC1, FileId_RatePara, 1, FileItemInfoOffAddr_RatePara_nTimeZone },
    {0x000202, 0xC1, FileId_RatePara, 1, FileItemInfoOffAddr_RatePara_nPOTTable },
    {0x000203, 0xC1, FileId_RatePara, 1, FileItemInfoOffAddr_RatePara_nDayPOT },
    {0x000204, 0xC1, FileId_RatePara, 1, FileItemInfoOffAddr_RatePara_nFl },
    {0x000205, 0xC1, FileId_RatePara, 2, FileItemInfoOffAddr_RatePara_nHoliday },
    {0x000206, 0xC1, FileId_ParaDoc, 1, FileItemInfoOffAddr_DocPara_nWave },
    #if(METERTYPE ==2)
    {0x000207, 0x41, FileId_RatePara, 1, FileItemInfoOffAddr_RatePara_nLadder },
    #endif
    {0x000208, 0x41, FileId_ParaCipherKey, 1, FileItemInfoOffAddr_CipherKeyPara_nCipherKey },
    {0x000301, 0xC1, FileId_ParaDisp, 1, FileItemInfoOffAddr_DispPara_AllonDispTime },
    {0x000302, 0xC1, FileId_ParaDisp, 1, FileItemInfoOffAddr_DispPara_KeyLightTime },
    {0x000303, 0xC1, FileId_ParaDisp, 1, FileItemInfoOffAddr_DispPara_ChkLightTime },
    {0x000304, 0xC1, FileId_ParaDisp, 1, FileItemInfoOffAddr_DispPara_KeyPwrOffTime },
    {0x000305, 0xC1, FileId_ParaDisp, 1, FileItemInfoOffAddr_DispPara_DecimalEg },
    {0x000306, 0x41, FileId_HighPara, 3, FileItemInfoOffAddr_HighPara_CT },
    {0x000307, 0x41, FileId_HighPara, 3, FileItemInfoOffAddr_HighPara_PT },
    {0x000308, 0x41, FileId_ParaDisp, 1, FileItemInfoOffAddr_DispPara_CycDispItem + 10 * MAX_CYCDISP },

    {0x000401, 0xC1, FileId_ParaCom, sizeof(sDF12), FileItemInfoOffAddr_ComPara_ComAddr },
    {0x000402, 0xC1, FileId_HighPara, sizeof(sDF12), FileItemInfoOffAddr_HighPara_MeterNo },
    {0x000403, 0xC0, FileId_ParaASCII, 32, FileItemInfoOffAddr_ASCIIPara_DeviceNo },
    {0x000404, 0x40, FileId_ParaASCII, 6, FileItemInfoOffAddr_ASCIIPara_RatingVol },
    {0x000405, 0x40, FileId_ParaASCII, 6, FileItemInfoOffAddr_ASCIIPara_RatingCur },
    {0x000406, 0x40, FileId_ParaASCII, 6, FileItemInfoOffAddr_ASCIIPara_MaxCur },
    {0x000407, 0x40, FileId_ParaASCII, 4, FileItemInfoOffAddr_ASCIIPara_PGrade },
    {0x000408, 0x40, FileId_ParaASCII, 4, FileItemInfoOffAddr_ASCIIPara_QGrade },
    {0x000409, 0x40, FileId_HighPara, sizeof(sDF10), FileItemInfoOffAddr_HighPara_PConstE },
    {0x00040A, 0x40, FileId_HighPara, sizeof(sDF10), FileItemInfoOffAddr_HighPara_QConstE },
    {0x00040B, 0x40, FileId_ParaASCII, 10, FileItemInfoOffAddr_ASCIIPara_MeterModel },
    {0x00040C, 0x40, FileId_ParaASCII, 10, FileItemInfoOffAddr_ASCIIPara_ProductDate },
    {0x00040D, 0x40, FileId_ParaASCII, 16, FileItemInfoOffAddr_ASCIIPara_PtVer },
    {0x00040E, 0xC1, FileId_HighPara, sizeof(sDF12), FileItemInfoOffAddr_HighPara_UserNo },
    {0x00040F, 0xC0, FileId_ParaASCII, 11, FileItemInfoOffAddr_ASCIIPara_MeterPlace },
    {0x00041F, 0xC0, FileId_ParaASCII, 4, FileItemInfoOffAddr_ASCIIPara_MeterPlace },
    {0x00042F, 0xC0, FileId_ParaASCII, 4, FileItemInfoOffAddr_ASCIIPara_MeterPlace + 4 },
    {0x00043F, 0xC0, FileId_ParaASCII, 3, FileItemInfoOffAddr_ASCIIPara_MeterPlace + 8 },

    {0x000508, 0x40, FileId_ParaCipherKey, 4, FileItemInfoOffAddr_CipherKeyPara_CipherKeyFlag },

    {0x000601, 0xC0, FileId_HighPara, 1, FileItemInfoOffAddr_HighPara_PExpression },
    {0x000602, 0xC0, FileId_HighPara, 1, FileItemInfoOffAddr_HighPara_PtQExpression },
    {0x000603, 0xC0, FileId_HighPara, 1, FileItemInfoOffAddr_HighPara_NtQExpression },

    {0x000701, 0xC0, FileId_ParaCom, 1, FileItemInfoOffAddr_ComPara_Ir1Style },
    {0x000702, 0xC0, FileId_ParaCom, 1, FileItemInfoOffAddr_ComPara_Ir2Style },
    {0x000703, 0xC0, FileId_ParaCom, 1, FileItemInfoOffAddr_ComPara_Com1Style },
    {0x000704, 0xC0, FileId_ParaCom, 1, FileItemInfoOffAddr_ComPara_Com2Style },
    {0x000705, 0xC0, FileId_ParaCom, 1, FileItemInfoOffAddr_ComPara_Com3Style },

    {0x000801, 0xC0, FileId_RatePara, 1, FileItemInfoOffAddr_RatePara_Weekend },
    {0x000802, 0xC0, FileId_RatePara, 1, FileItemInfoOffAddr_RatePara_WeekendPOT },

    {0x001101, 0xC0, FileId_HighPara, 1, FileItemInfoOffAddr_HighPara_MeterRunFlag },

    #if(METERTYPE ==2)
    {0x000F01, 0x41, FileId_RatePara, sizeof(sDF11), FileItemInfoOffAddr_RatePara_ChargMoneyPara },
    {0x000F02, 0x41, FileId_RatePara, sizeof(sDF11), FileItemInfoOffAddr_RatePara_ChargMoneyPara + 4 },
    {0x000F03, 0xC1, FileId_RatePara, sizeof(sDF11), FileItemInfoOffAddr_RatePara_ChargMoneyPara + 8 },
    {0x000F04, 0xC1, FileId_RatePara, sizeof(sDF11), FileItemInfoOffAddr_RatePara_ChargMoneyPara + 12 },

    {0x001001, 0x41, FileId_RatePara, sizeof(sDF11), FileItemInfoOffAddr_RatePara_ChargMoneyPara + 16 },
    {0x001002, 0x41, FileId_RatePara, sizeof(sDF11), FileItemInfoOffAddr_RatePara_ChargMoneyPara + 20 },
    {0x001003, 0xC1, FileId_RatePara, sizeof(sDF11), FileItemInfoOffAddr_RatePara_ChargMoneyPara + 24 },
    {0x001004, 0xC1, FileId_RatePara, sizeof(sDF11), FileItemInfoOffAddr_RatePara_ChargMoneyPara + 28 },
    {0x001005, 0xC1, FileId_RatePara, sizeof(sDF11), FileItemInfoOffAddr_RatePara_ChargMoneyPara + 32 },
    #endif
    // 主动上报

    {0x800001, 0x40, FileId_ParaASCII, 32, FileItemInfoOffAddr_ASCIIPara_SoftVer },
    {0x800002, 0x40, FileId_ParaASCII, 32, FileItemInfoOffAddr_ASCIIPara_FirmVer },
    {0x800003, 0x40, FileId_ParaASCII, 32, FileItemInfoOffAddr_ASCIIPara_FactoryNo },

    // 2014增补
    {0x001402, 0xC1, FileId_HighPara, 3, FileItemInfoOffAddr_HighPara_GataSafeCur },
    {0x001403, 0xC1, FileId_HighPara, 2, FileItemInfoOffAddr_HighPara_tSafeGata },
    {0x001404, 0xC1, FileId_HighPara, 1, FileItemInfoOffAddr_HighPara_tIRPrg },
    {0x001405, 0xC1, FileId_HighPara, 1, FileItemInfoOffAddr_HighPara_tEvRstDely }
};

ErrorStatus fnDl645_FindParaVar(u32 DITemp, u16 *nItem)
{
    u16 i;

    for (i = 0 ; i < (sizeof(ParaVar) / sizeof(sDl645B_ParaVar_TypeDef)) ; i++)
    {
        if (DITemp == ParaVar[i].DI)
        {
            *nItem = i;
            return (SUCCESS);
        }
    }
    return (ERROR);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetSocMemory(sFrmDl645B_TypeDef *RxFrm, u8 *Dst, u16 *Len)
{
    u32 DI;

    *Len = 0;
    DI = 0;
    DI = ((u32)RxFrm->UDat.DI2 << 8) + (RxFrm->UDat.DI1);
    DI = (DI << 8);
    DI = DI + (RxFrm->UDat.DI0);
    DI = DI & 0xffffff00;

    switch (DI)
    {
        case 0x00f91100:
            *Len = 4;
            Std_Memcpy(Dst, (u8 *)&Dl645B_RTCCom->Buf[RxFrm->UDat.DI0], *Len);
            break;
        default:
            return (DL645B_ERRINFO_DATA);
    }
    return (DL645B_ERRINFO_OK);
}

eDL645B_ErrInfo_TypeDef fnDl645_GetParaVar(u8 DI2, u8 DI1, u8 DI0, u8 *Dst, u16 *Len)
{
    u32 DITemp;

    u16 nItem;
    u8  i;
    u8 tempdi[4];
    sDataComm_TypeDef      EmuCommbuf;

    //#if(METERTYPE == 2)
    u32 OffAddr;
    u8  FileId;
    //#endif

    *Len = 0;

    tempdi[0] = DI0;
    tempdi[1] = DI1;
    tempdi[2] = DI2;
    tempdi[3] = 0;
    Std_Memcpy(&DITemp, &tempdi, 4);

    //---------内部扩展命令------------------
    if ((DITemp >= 0x00f20000) && (DITemp < 0x00f40000))
    {
        //------ 0x04f2XXxx~0x04f2XXxx 读寄存器-----
        if (tempdi[2] == 0xf2)
        {
            OffAddr = 0x40000000 + ((u32)(tempdi[1] << 8) + (u32)tempdi[0]) * 4;

            if (OffAddr > 0x40068100)  //--大于96K时------------
            {
                return (DL645B_ERRINFO_MISC);
            }
        }
        else
        {
            OffAddr = 0x50000000 + ((u32)(tempdi[1] << 8) + (u32)tempdi[0]) * 4;

            if (OffAddr > 0x50018100)  //--大于96K时------------
            {
                return (DL645B_ERRINFO_MISC);
            }
        }
        *Len = 128;  //-----按128byte应答-------------

        Std_Memcpy(Dst, (u8 *)OffAddr, *Len);

        return (DL645B_ERRINFO_OK);
    }
    else if ((DITemp >= 0x00f40000) && (DITemp < 0x00f60000))
    {
        //----- 0x04f4Xxxx~0x04f5Xxxx读E2或外部flash-----
        OffAddr = ((u32)(tempdi[1] & 0x0F) << 8) + (u32)tempdi[0]; //--每个FileId最大支持0xFFF+0x80(128)= 4223byte, E2可全覆盖，flash读取受限---------------
        if (tempdi[2] == 0xf4)
        {
            FileId = (tempdi[1] & 0xF0) >> 4;    //----FileId按eFileInfo_TypeDef定义----------
        }
        else
        {
            FileId = ((tempdi[1] & 0xF0) >> 4) + 0x10;
        }

        if (OffAddr > FileInfo[FileId].Len)
        {
            return (DL645B_ERRINFO_MISC);
        }

        *Len = 128;  //-----按128byte应答-------------
        if ((*Len + OffAddr) > FileInfo[FileId].Len)
        {
            *Len = FileInfo[FileId].Len - OffAddr;
        }

        if (fnFile_Read(FileId, OffAddr,  Dst, *Len) == SUCCESS)
        {
            return (DL645B_ERRINFO_OK);
        }
        else
        {
            return (DL645B_ERRINFO_DATA);
        }
    }
    else if ((DITemp >= 0x00f60000) && (DITemp < 0x00f70000))
    {
        //------ 0x04f6XXxx 读内部RAM-----
        OffAddr = 0x10000000 + ((u32)(tempdi[1] << 8) + (u32)tempdi[0]) * 4;

        if (OffAddr > 0x10018000)  //--大于96K时------------
        {
            return (DL645B_ERRINFO_MISC);
        }

        *Len = 128;  //-----按128byte应答-------------

        Std_Memcpy(Dst, (u8 *)OffAddr, *Len);

        return (DL645B_ERRINFO_OK);
    }

    #if(nPhs==SinglePhs)
    if ((DITemp >= 0x00f70000) && (DITemp < 0x00f80000))
    {
        //------读计量芯片寄存器数据-----
        fnMeasure_WaveColse();

        fnMeasure_ReadEMUReg(tempdi[0], tempdi[1], Dst, Len);

        fnMeasure_WaveInit();

        return (DL645B_ERRINFO_OK);
    }
    if (DITemp == 0x00fb0100)
    {
        Std_Memcpy(Dst, (u8 *) & (gTemperSchoolParaMem.chan[tempdi[0]].valid), 1);
        *Len = 1;
        return (DL645B_ERRINFO_OK);
    }

    if ((DITemp >= 0x00fb0101) && (DITemp <= 0x00fb0104))
    {
        //------读端子测温补偿寄存器-----
        //u8 k ;
        Std_Memcpy(Dst, (u8 *) & (gTemperSchoolParaMem.chan[tempdi[0] - 1].k), 4);
        Dst += 4;
        Std_Memcpy(Dst, (u8 *) & (gTemperSchoolParaMem.chan[tempdi[0] - 1].offs), 4);
        *Len = 8;
        return (DL645B_ERRINFO_OK);
    }

    #else

    if ((DITemp >= 0x00fb0101) && (DITemp <= 0x00fb0108))   // dyf 0x00fb0104 => 0x00fb0108
    {
        //------读端子测温补偿寄存器-----
        //u8 k ;
        Std_Memcpy(Dst, (u8 *) & (gTemperSchoolParaMem.chan[tempdi[0] - 1].k), 4);
        Dst += 4;
        Std_Memcpy(Dst, (u8 *) & (gTemperSchoolParaMem.chan[tempdi[0] - 1].offs), 4);
        *Len = 8;
        return (DL645B_ERRINFO_OK);
    }

    #endif

    switch (DITemp)
    {
        case 0x00f91100:        // 设置RTC的DOTA0
            Std_Memcpy(Dst, (u8 *) & (RTCPara.RTCDota0), 2);
            *Len = 2;
            break;
        case 0x00f91f00:        /*"设置RTC的曲线模式"*/
            Std_Memcpy(Dst, (u8 *) & (RTCPara.CurveMode), 2);
            *Len = 2;
            break;

        case 0x00f91f01:        /*""*/
            Std_Memcpy(Dst, (u8 *) & (RTCPara.DATA0), 2);
            *Len = 2;
            break;
        case 0x00f91f02:        /*""*/
            Std_Memcpy(Dst, (u8 *) & (RTCPara.XT1), 2);
            *Len = 2;
            break;
        case 0x00f91f03:        /*""*/
            Std_Memcpy(Dst, (u8 *) & (RTCPara.ALPHA), 2);
            *Len = 2;
            break;
        case 0x00f91f04:        /*""*/
            Std_Memcpy(Dst, (u8 *) & (RTCPara.BETA), 2);
            *Len = 2;
            break;
        case 0x00f91f05:        /*""*/
            Std_Memcpy(Dst, (u8 *) & (RTCPara.GAMMA), 2);
            *Len = 2;
            break;
        case 0x00f91f06:        /*""*/
            Std_Memcpy(Dst, (u8 *) & (RTCPara.ZETA), 2);
            *Len = 2;
            break;

        case 0x00800004:            // 软件备案号
            fnFile_Read(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_SoftWare, Dst, 8);
            *Len = 8;
            break;

            #if(nPhs==ThreePhs)
        case 0x00f81000:                // 读电压电流寄存器值
            for (i = 0; i < 8; i++)
            {
                fnRN8302_Read(0x0007+i, EmuCommbuf.ucTempBuf, 4) ;
                Dst[i * 4] = EmuCommbuf.ucTempBuf[0];
                Dst[i * 4 + 1] = EmuCommbuf.ucTempBuf[1];
                Dst[i * 4 + 2] = EmuCommbuf.ucTempBuf[2];
                Dst[i * 4 + 3] = EmuCommbuf.ucTempBuf[3];
            }
            *Len = 32;
            break;
        case 0x00f81001:                // 读功率寄存器值
            for (i = 0; i < 3; i++)
            {
                fnRN8302_Read(0x0014+i, EmuCommbuf.ucTempBuf, 4) ;
                Dst[i * 4] = EmuCommbuf.ucTempBuf[0];
                Dst[i * 4 + 1] = EmuCommbuf.ucTempBuf[1];
                Dst[i * 4 + 2] = EmuCommbuf.ucTempBuf[2];
                Dst[i * 4 + 3] = EmuCommbuf.ucTempBuf[3];
            }
            *Len = 12;
            break;
        case 0x00f81002:
            fnRN8302_Read(0x000f, EmuCommbuf.ucTempBuf, 4) ;
            Dst[0] = EmuCommbuf.ucTempBuf[0];
            Dst[1] = EmuCommbuf.ucTempBuf[1];
            Dst[2] = EmuCommbuf.ucTempBuf[2];
            Dst[3] = EmuCommbuf.ucTempBuf[3];
            *Len = 4;
            break;
        case 0x00f81003:
            fnRN8302_Read(RN8302_CFCFG, EmuCommbuf.ucTempBuf, 3) ;
            Dst[0] = EmuCommbuf.ucTempBuf[0];
            Dst[1] = EmuCommbuf.ucTempBuf[1];
            Dst[2] = EmuCommbuf.ucTempBuf[2];
            *Len = 3;
            break;
        case 0x00f81100:                // 读相角寄存器
            for (i = 0; i < 5; i++)
            {
                fnRN8302_Read(RN8302_YUB + i, EmuCommbuf.ucTempBuf, 3) ;
                Dst[i * 3] = EmuCommbuf.ucTempBuf[0];
                Dst[i * 3 + 1] = EmuCommbuf.ucTempBuf[1];
                Dst[i * 3 + 2] = EmuCommbuf.ucTempBuf[2];
            }
            *Len = 15;
            break;
        case 0x00f81200:                // 读增益寄存器值
            for (i = 0; i < 6; i++)
            {
                fnRN8302_Read(RN8302_GSUA + i, EmuCommbuf.ucTempBuf, 2) ;
                Dst[i * 2] = EmuCommbuf.ucTempBuf[0];
                Dst[i * 2 + 1] = EmuCommbuf.ucTempBuf[1];
            }
            *Len = 12;
            break;
        case 0x00f81300:                // 读相位寄存器值
            for (i = 0; i < 2; i++)
            {
                fnRN8302_Read(RN8302_PHSUB + i, EmuCommbuf.ucTempBuf, 1);
                Dst[i] = EmuCommbuf.ucTempBuf[0];
            }
            for (i = 0; i < 3; i++)
            {
                fnRN8302_Read(RN8302_PHSIA + i, EmuCommbuf.ucTempBuf, 3);
                Dst[i * 3 + 2] = EmuCommbuf.ucTempBuf[0];
                Dst[i * 3 + 3] = EmuCommbuf.ucTempBuf[1];
                Dst[i * 3 + 4] = EmuCommbuf.ucTempBuf[2];
            }
            *Len = 11;
            break;
        case 0x00f81400:            // 读分段寄存器
            for (i = 0; i < 4; i++)
            {
                fnRN8302_Read(RN8302_PRTH1L + i, EmuCommbuf.ucTempBuf, 2);
                Dst[i * 2] = EmuCommbuf.ucTempBuf[0];
                Dst[i * 2 + 1] = EmuCommbuf.ucTempBuf[1];
            }
            *Len = 8;
            break;
        case 0x00f81401:            // 读电压电流OFFSET值
            for (i = 0; i < 3; i++)
            {
                fnRN8302_Read(0x0137+i, EmuCommbuf.ucTempBuf, 2);
                Dst[i * 2] = EmuCommbuf.ucTempBuf[0];
                Dst[i * 2 + 1] = EmuCommbuf.ucTempBuf[1];
            }
            *Len = 6;
            break;
        case 0x00f81402:
            for (i = 0; i < 6; i++)
            {
                fnRN8302_Read(0x0121+i, EmuCommbuf.ucTempBuf, 2);
                Dst[i * 2] = EmuCommbuf.ucTempBuf[0];
                Dst[i * 2 + 1] = EmuCommbuf.ucTempBuf[1];
            }
            *Len = 12;
            break;
        case 0x00f81500:
            fnRN8302_Read(0x0167, EmuCommbuf.ucTempBuf, 2) ;
            Dst[0] = EmuCommbuf.ucTempBuf[0];
            Dst[1] = EmuCommbuf.ucTempBuf[1];
            *Len = 2;
            break;
            #endif

        case 0x00f81604:
            *Len = 1;
            fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_HighPulseRate, Dst, 1);
            break;

        case 0x00f81606:
            *Len = fnMeasure_VoltRepair_CommRead(Dst);
            break;

        case 0x00f81607:
            *Len = fnMeasure_TIRM_CommRead(Dst);
            //*Len =    2;
            break;
            #if(nPhs==ThreePhs)
        case 0x00f81608:
            *Len = fnMeasure_RN8207DTIRM_CommRead(Dst);
            break;
            #endif

        case 0x00f81609:  //----读取谐波增益补偿--A----
        case 0x00f8160A:  //----读取谐波增益补偿--B----
        case 0x00f8160B:  //----读取谐波增益补偿--C----
            nItem = DITemp - 0x00f81609;
            *Len = 2 * nHarmonic;

            for (i = 0; i < nHarmonic; i++)
            {
                Std_Memcpy(Dst, (u8 *)&HarmonicData.PubPara.FftGP[nItem][i], 2);
                Dst += 2;
            }
            break;

        case 0x00f8160C:  //----读取谐波增益补偿--A----
        case 0x00f8160D:  //----读取谐波增益补偿--B----
        case 0x00f8160E:  //----读取谐波增益补偿--C----
            nItem = DITemp - 0x00f8160C;
            *Len = 4 * nHarmonic;

            for (i = 0; i < nHarmonic; i++)
            {
                Std_Memcpy(Dst, (u8 *)&HarmonicData.PubPara.FftCosAngle[nItem][i], 4);
                Dst += 4;
            }
            break;

        case 0x00f91201:
            *Len = 3;
            fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCAdj, Dst, 3);
            break;
        case 0x00fb1001:        //写RN8302B寄存器 liqiushi add
            *Len = Rn_ReadInfo[2];
            fnRN8302_Read((Rn_ReadInfo[0] << 8) + Rn_ReadInfo[1], (u8 *)Dst, Rn_ReadInfo[2]);
            break;
        case 0x00f91300:                        // 程序版本号
            Dst[4] = 0x14;
            Dst[3] = 0x07;
            Dst[2] = 0x26;
            Dst[1] = 0x23;
            Dst[0] = 0x34;
            *Len = 5;
            break;

        case 0x00fA0101:   //---E2预留32byte,实际只用6byte-----------
            *Len = 6;
            fnFile_Read(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_FactoryMAC, Dst, 6);
            break;

        case 0x00fA0102:   //-----厂家内部软件版本号,只读---------
            *Len = 32;
            Std_Memcpy(Dst, &FactorySoftVer[0], *Len);    //-----ASCII码----------

            break;
        default:
            if ((DI2 == 0x03) &&
                (DI1 == 0x00) &&
                ((DI0 != 0) && (DI0 <= 0xFE)))
            {
                *Len = sizeof(sHolidayTable_TypeDef);
                fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_HolidayTable + sizeof(sHolidayTable_TypeDef) * (DI0 - 1), Dst, *Len);
            }

            break;
    }

    return (DL645B_ERRINFO_OK);
}

ErrorStatus fnDl645_POTTable_Check(sPOTTable_TypeDef *POTTab, u8 nPOTTab)
{
    u8  i;
    u8  Cycle;
    u16 Tmpa, Tmpb, Tmpx;

    fnFile_Read(FileId_ParaDoc, FileItemInfoOffAddr_DocPara_NeedCyc, &Cycle, 1);
    Cycle = fnBcdToHex_u8(Cycle);
    if (Cycle < 15)
    {
        Cycle = 15;
    }

    for (i = 1 ; i <= nPOTTab ; i++)
    {
        Tmpa = fnBcdToHex_u8(POTTab[i - 1].Hour) * 60 + fnBcdToHex_u8(POTTab[i - 1].Minute);
        if (i == nPOTTab)
        {
            Tmpb = fnBcdToHex_u8(POTTab[0].Hour) * 60 + fnBcdToHex_u8(POTTab[0].Minute);
        }
        else
        {
            Tmpb = fnBcdToHex_u8(POTTab[i].Hour) * 60 + fnBcdToHex_u8(POTTab[i].Minute);
        }

        if (Tmpa > Tmpb)
        {
            Tmpx = 24 * 60 + Tmpb - Tmpa;
        }
        else
        {
            Tmpx = Tmpb - Tmpa;
        }

        if ((Tmpx != 0) && (Tmpx < Cycle))
        {
            return (ERROR);
        }
    }
    return (SUCCESS);
}

void fnDl645_CmpFrzTime(void)
{
    /*
       sDF15   TmpClock1;
       sDF15   TmpClock2;
       //fnFile_Read(Dl645FileId_FrzTime , Dl645FileItemInfoOffAddr_FrzTime_DayFrzTime , (u8 *)&TmpClock1 , Dl645FileItemInfoLen_FrzTime_DayFrzTime );
       Std_Memcpy((u8 *)&TmpClock2.Minute , (u8 *)&SysClock.Minute , 5);
       TmpClock1.Month &= 0x1f;
       TmpClock2.Month &= 0x1f;
       //if(fnDFCmp_DF15(&TmpClock2 , &TmpClock1)>0)
       {
           //fnFile_Write(Dl645FileId_FrzTime , Dl645FileItemInfoOffAddr_FrzTime_DayFrzTime , (u8 *)&TmpClock2.Minute , Dl645FileItemInfoLen_FrzTime_DayFrzTime );
       }
       //fnFile_Read(Dl645FileId_FrzTime , Dl645FileItemInfoOffAddr_FrzTime_RmEgTime , (u8 *)&TmpClock1 , Dl645FileItemInfoLen_FrzTime_RmEgTime );
       TmpClock1.Month &= 0x1f;
       if(fnDFCmp_DF15(&TmpClock2 , &TmpClock1)>0)
       {
           //fnFile_Write(Dl645FileId_FrzTime , Dl645FileItemInfoOffAddr_FrzTime_RmEgTime , (u8 *)&TmpClock2.Minute , Dl645FileItemInfoLen_FrzTime_RmEgTime );
       }*/
}

eDL645B_ErrInfo_TypeDef fnDl645_PutParaVar(sFrmDl645B_TypeDef *RxFrm)
{
    u8  i;
    u32 DITemp = 0x0;
    //    u8  UnConst[6],InConst[6],ImaxConst[6];
    u16 tempconst;
    #if(nPhs==ThreePhs)
    u16 tempub, tempib;
    u16 temphfconst;
    #endif
    u32 tempus, tempis;
    //  sDF01 OldClock;
    sDF11   ConstE;
    ErrorStatus err;
    u16 tempuc = 0;
    u32 OffAddr;
    u8  FileId;
    u16 len;
    //  u32 tempid=0;
    float ADErr;
    //  eDL645B_ErrInfo_TypeDef     Result;
    u32 temppw[2];
    sDataComm_TypeDef      EmuCommbuf;

    #if(nPhs==SinglePhs)
    sCorrectTmp_TypeDef   stand;
    #endif

    i = RxFrm->UDat.DI3;
    RxFrm->UDat.DI3 = 0;
    Std_Memcpy(&DITemp, &RxFrm->UDat.DI0, 4);
    RxFrm->UDat.DI3 = i;

    if ((DITemp == 0xFE0001) || (DITemp == 0xFE0002) || (DITemp == 0xFE0003))
    {
        if (RxFrm->Len != (12 + 5 * sizeof(u16)))
        {
            return (DL645B_ERRINFO_DATA);
        }
        fnFile_Write(FileId_ParaOutput, FileItemInfoOffAddr_OutputPara_Style5 + (5 * sizeof(u16)) * (RxFrm->UDat.DI0 - 1), &RxFrm->UDat.Dat[8], 5 * sizeof(u16));
        Std_Memset(&Output.PriPara, 0, sizeof(Output.PriPara) - 2);
        return (DL645B_ERRINFO_OK);
    }
    //---------内部扩展命令------------------
    if ((DITemp >= 0x00f20000) && (DITemp < 0x00f40000))
    {
        //------ 0x04f2XXxx~0x04f2XXxx MCU寄存器-----
        if (RxFrm->UDat.DI2 == 0xf2)
        {
            OffAddr = 0x40000000 + ((u32)(RxFrm->UDat.DI1 << 8) + (u32)RxFrm->UDat.DI0) * 4;

            if (OffAddr > 0x40068100)  //-------------
            {
                return (DL645B_ERRINFO_MISC);
            }
        }
        else
        {
            OffAddr = 0x50000000 + ((u32)(RxFrm->UDat.DI1 << 8) + (u32)RxFrm->UDat.DI0) * 4;

            if (OffAddr > 0x50018100)  //-------------
            {
                return (DL645B_ERRINFO_MISC);
            }
        }
        Std_Memcpy((u8 *)OffAddr, &RxFrm->UDat.Dat[8], (RxFrm->Len - 12));

        return (DL645B_ERRINFO_OK);
    }
    else if ((DITemp >= 0x00f40000) && (DITemp < 0x00f60000))
    {
        //----- 0x04f4Xxxx~0x04f5Xxxx E2或外部flash-----
        OffAddr = ((u32)(RxFrm->UDat.DI1 & 0x0F) << 8) + (u32)RxFrm->UDat.DI0; //--每个FileId最大支持0xFFF+0x80(128)= 4223byte, E2可全覆盖，flash读取受限---------------
        if (RxFrm->UDat.DI2 == 0xf4)
        {
            FileId = (RxFrm->UDat.DI1 & 0xF0) >> 4;    //----FileId按eFileInfo_TypeDef定义----------
        }
        else
        {
            FileId = ((RxFrm->UDat.DI1 & 0xF0) >> 4) + 0x10;
        }

        if (OffAddr > FileInfo[FileId].Len)
        {
            return (DL645B_ERRINFO_MISC);
        }

        len = RxFrm->Len - 12;
        if ((len + OffAddr) > FileInfo[FileId].Len)
        {
            len = FileInfo[FileId].Len - OffAddr;
        }

        if (fnFile_Write(FileId, OffAddr,  &RxFrm->UDat.Dat[8], len) == SUCCESS)
        {
            return (DL645B_ERRINFO_OK);
        }
        else
        {
            return (DL645B_ERRINFO_DATA);
        }
    }
    else if ((DITemp >= 0x00f60000) && (DITemp < 0x00f70000))
    {
        //------ 0x04f6XXxx 读内部RAM-----
        OffAddr = 0x10000000 + ((u32)(RxFrm->UDat.DI1 << 8) + (u32)RxFrm->UDat.DI0) * 4;

        if (OffAddr > 0x10018000)  //--大于96K时------------
        {
            return (DL645B_ERRINFO_MISC);
        }

        Std_Memcpy((u8 *)OffAddr, &RxFrm->UDat.Dat[8], (RxFrm->Len - 12));

        return (DL645B_ERRINFO_OK);
    }

    if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable == 0)
    {
        return DL645B_ERRINFO_PSW;
    }

    if ((DITemp >= 0x00f70000) && (DITemp < 0x00f80000))
    {
        //------写计量芯片寄存器数据-----
        fnMeasure_WaveColse();

        //      fnMeasure_WriteEMUReg(RxFrm->UDat.DI0 , &(RxFrm->UDat.Dat[8]) , (RxFrm->Len-12));

        fnMeasure_WaveInit();

        return (DL645B_ERRINFO_OK);
    }

    if (DITemp == 0x00f91201)
    {
        if ((RxFrm->UDat.Dat[0] == 0x03) && (RxFrm->UDat.Dat[1] == 0x43) && (RxFrm->UDat.Dat[2] == 0x56) && (RxFrm->UDat.Dat[3] == 0x98)) ;
        else
        {
            return (DL645B_ERRINFO_PSW);
        }
    }
    else if (DITemp == 0x001503) ;
    else
    {
        err = SUCCESS;
        if (err != SUCCESS)
        {
            return (DL645B_ERRINFO_PSW);
        }
    }
    switch (DITemp)
    {
        case 0x00000401:
            if (RxFrm->Len != (12 + 6))
            {
                return (DL645B_ERRINFO_DATA);
            }
            if (fnBCD_Check(&RxFrm->UDat.Dat[8], 6) == false)
            {
                return (DL645B_ERRINFO_DATA);
            }
            Std_Memcpy(&CommPara.ComAddr[0], &RxFrm->UDat.Dat[8], 6);
            fnCrc_Check(0, (u8 *)&CommPara, FileLen_ParaCom - 2, (u8 *)&CommPara.Crc);
            fnFile_Write(FileId_ParaCom, FileItemInfoOffAddr_ComPara_ComAddr, (u8 *)&CommPara, FileLen_ParaCom);

            break;

            #if(nPhs==ThreePhs)
        case 0x00f81000:                                        //电流电压功率初校,HFCONST等参数设置
            if (RxFrm->Len != (12 + 48))
            {
                return (DL645B_ERRINFO_DATA);
            }

            Std_Memcpy(&tempconst, &(RxFrm->UDat.Dat[8]), 2);
            Std_Memcpy(&temphfconst, &(RxFrm->UDat.Dat[10]), 2);
            Std_Memcpy(&tempub, &(RxFrm->UDat.Dat[12]), 2);
            Std_Memcpy(&tempus, &(RxFrm->UDat.Dat[14]), 4);
            Std_Memcpy(&tempib, &(RxFrm->UDat.Dat[18]), 2);
            Std_Memcpy(&tempis, &(RxFrm->UDat.Dat[20]), 4);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RatedI, (u8 *)&tempib, 2);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RatedU, (u8 *)&tempub, 2);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RatedIrms, (u8 *)&tempis, 4);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RatedUrms, (u8 *)&tempus, 4);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealU, (u8 *) & (RxFrm->UDat.Dat[32]), 24);

            EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
            fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
            MeasureFirmPara.HFConst1 = temphfconst;

            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_HFConst1, (u8 *)&MeasureFirmPara.HFConst1, 2);

            ConstE.Dat = (u32)tempconst * 10;

            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_PConstE, (u8 *)&ConstE, 4);
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_QConstE, (u8 *)&ConstE, 4);

            Std_Memcpy(&tempub, &(RxFrm->UDat.Dat[24]), 2);
            Std_Memcpy(&tempib, &(RxFrm->UDat.Dat[26]), 2);

            MeasureFirmPara.PRth[0] = tempub;
            MeasureFirmPara.PRth[1] = tempib;
            Std_Memcpy(&tempub, &(RxFrm->UDat.Dat[28]), 2);
            Std_Memcpy(&tempib, &(RxFrm->UDat.Dat[30]), 2);
            MeasureFirmPara.PRth[2] = tempub;
            MeasureFirmPara.PRth[3] = tempib;
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_PRth, (u8 *)&MeasureFirmPara.PRth[0], 8);
            MeasureRms.PriData.Flag |= MEASURE_FLAG_CorrectionUI;
            break;
        case 0x00f81100:            //功率相位校准
            if ((RxFrm->Len != (12 + 18)) && (RxFrm->Len != (12 + 20)) && (RxFrm->Len != (12 + 5)))
            {
                return (DL645B_ERRINFO_DATA);
            }
            EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
            fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
            if (RxFrm->Len == (12 + 5))
            {
                // 使用误差进行精校准
                Std_Memcpy(&tempis, &(RxFrm->UDat.Dat[9]), 4);
                if (tempis > 0x7fffffff)
                {
                    ADErr = -(float)(0xffffffff - tempis) / 100000;
                }
                else
                {
                    ADErr = (float)tempis / 100000;
                }
                ADErr = -ADErr / 1.732;
                if (ADErr >= 0)
                {
                    tempub = ADErr * 32768 + 0.5; //四舍五入
                }
                else
                {
                    tempub = 65536 + ADErr * 32768 + 0.5;
                }
                if (MeasureFirmPara.PRth[0] == 0 && MeasureFirmPara.PRth[1] == 0 && MeasureFirmPara.PRth[2] == 0 && MeasureFirmPara.PRth[3] == 0)
                {
                    Std_Memcpy((u8 *)&MeasureFirmPara.P_PHS[RxFrm->UDat.Dat[8]], &tempub, 0x02);
                    Std_Memcpy((u8 *)&MeasureFirmPara.Q_PHS[RxFrm->UDat.Dat[8]], &tempub, 0x02);
                    fnRN8302_Write(RN8302_PA_PHSL + RxFrm->UDat.Dat[8], (u8 *)&MeasureFirmPara.P_PHS[RxFrm->UDat.Dat[8]], 2);
                    fnRN8302_Write(RN8302_QA_PHSL + RxFrm->UDat.Dat[8], (u8 *)&MeasureFirmPara.Q_PHS[RxFrm->UDat.Dat[8]], 2);
                }
                else
                {
                    MeasureFirmPara.P_PHSMH[RxFrm->UDat.Dat[8] * 2] = 0;
                    MeasureFirmPara.Q_PHSMH[RxFrm->UDat.Dat[8] * 2] = 0;
                    Std_Memcpy((u8 *)&MeasureFirmPara.P_PHSMH[RxFrm->UDat.Dat[8] * 2], &tempub, 0x02);
                    Std_Memcpy((u8 *)&MeasureFirmPara.Q_PHSMH[RxFrm->UDat.Dat[8] * 2], &tempub, 0x02);
                    fnRN8302_Write(RN8302_PA_PHSM + RxFrm->UDat.Dat[8] * 2, (u8 *)&MeasureFirmPara.P_PHSMH[RxFrm->UDat.Dat[8] * 2], 3);
                    fnRN8302_Write(RN8302_QA_PHSM + RxFrm->UDat.Dat[8] * 2, (u8 *)&MeasureFirmPara.Q_PHSMH[RxFrm->UDat.Dat[8] * 2], 3);
                }
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_P_PHSMH, (u8 *)&MeasureFirmPara.P_PHSMH[0], 48);
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_P_PHS, (u8 *)&MeasureFirmPara.P_PHS[0], 6);
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_Q_PHS, (u8 *)&MeasureFirmPara.Q_PHS[0], 6);

                EmuCommbuf.ucTemp8 = 0xDC; // 写保护
                fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
                MeasureFirmPara.ChkSum1 = 0;
                SystemDelay(10);
                MeasureRms.PriData.Flag |= MEASURE_FLAG_CalcCheckSum;
                fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureFirmPara.ChkSum1, 3) ;
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_ChkSum1, (u8 *)&MeasureFirmPara.ChkSum1, FileItemInfoLen_FirmPara_ChkSum1);
            }
            else
            {
                Std_Memcpy(&tempis, &(RxFrm->UDat.Dat[8]), 4);
                Std_Memcpy(&tempus, &(RxFrm->UDat.Dat[12]), 4);
                if ((RxFrm->Len == (12 + 18)))
                {
                    RxFrm->UDat.Dat[14] = 0;
                    RxFrm->UDat.Dat[15] = 0;
                    fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealAngle, &RxFrm->UDat.Dat[14], FileItemInfoLen_FirmPara_RealAngle);
                }
                else
                {
                    for (i = 0; i < 3; i++)
                    {
                        Std_Memcpy(&temppw[1], &(RxFrm->UDat.Dat[16 + 4 * i]), 4);
                        temppw[1] = (u32)(((float)tempus / (float)tempis) * (float)temppw[1]);
                        fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealAngle + 4 * i, (u8 *)&temppw[1], 4);
                    }
                }
                MeasureRms.PriData.Flag |= MEASURE_FLAG_CorrectionPHS;
            }
            break;
        case 0x00f81102:            //功率相位校准分段1
            if ((RxFrm->Len != (12 + 10)) && (RxFrm->Len != (12 + 20)) && (RxFrm->Len != (12 + 5)))
            {
                return (DL645B_ERRINFO_DATA);
            }
            if (MeasureFirmPara.PRth[0] == 0 && MeasureFirmPara.PRth[1] == 0 && MeasureFirmPara.PRth[2] == 0 && MeasureFirmPara.PRth[3] == 0)
            {
                return (DL645B_ERRINFO_DATA);
            }
            EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
            fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
            if (RxFrm->Len == (12 + 10))
            {
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealAngle + 2, &RxFrm->UDat.Dat[8], 10);
                RxFrm->UDat.Dat[12] = 0;
                RxFrm->UDat.Dat[13] = 0;
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealAngle, &RxFrm->UDat.Dat[12], 2);
                MeasureRms.PriData.Flag |= MEASURE_FLAG_CorrectionPHSL;
            }
            else if (RxFrm->Len == (12 + 20))
            {
                Std_Memcpy(&tempis, &(RxFrm->UDat.Dat[8]), 4);
                Std_Memcpy(&tempus, &(RxFrm->UDat.Dat[12]), 4);

                for (i = 0; i < 3; i++)
                {
                    Std_Memcpy(&temppw[1], &(RxFrm->UDat.Dat[16 + 4 * i]), 4);
                    temppw[1] = (u32)(((float)tempus / (float)tempis) * (float)temppw[1]);
                    fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealAngle + 4 * i, (u8 *)&temppw[1], 4);
                }
                MeasureRms.PriData.Flag |= MEASURE_FLAG_CorrectionPHSL;
            }
            else
            {
                Std_Memcpy(&tempis, &(RxFrm->UDat.Dat[9]), 4);
                EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
                fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
                if (tempis > 0x7fffffff)
                {
                    ADErr = -(float)(0xffffffff - tempis) / 100000;
                }
                else
                {
                    ADErr = (float)tempis / 100000;
                }
                ADErr = -ADErr / 1.732;
                if (ADErr >= 0)
                {
                    tempub = ADErr * 32768 + 0.5;
                }
                else
                {
                    tempub = 65536 + ADErr * 32768 + 0.5;
                }
                Std_Memcpy((u8 *)&MeasureFirmPara.P_PHS[RxFrm->UDat.Dat[8]], &tempub, 0x02);
                Std_Memcpy((u8 *)&MeasureFirmPara.Q_PHS[RxFrm->UDat.Dat[8]], &tempub, 0x02);
                fnRN8302_Write(RN8302_PA_PHSL + RxFrm->UDat.Dat[8], (u8 *)&MeasureFirmPara.P_PHS[RxFrm->UDat.Dat[8]], 2);
                fnRN8302_Write(RN8302_QA_PHSL + RxFrm->UDat.Dat[8], (u8 *)&MeasureFirmPara.Q_PHS[RxFrm->UDat.Dat[8]], 2);
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_P_PHS, (u8 *)&MeasureFirmPara.P_PHS[0], 6);
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_Q_PHS, (u8 *)&MeasureFirmPara.Q_PHS[0], 6);

                EmuCommbuf.ucTemp8 = 0xDC; // 写保护
                fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
                MeasureFirmPara.ChkSum1 = 0;
                SystemDelay(10);
                MeasureRms.PriData.Flag |= MEASURE_FLAG_CalcCheckSum;
                fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureFirmPara.ChkSum1, 3) ;
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_ChkSum1, (u8 *)&MeasureFirmPara.ChkSum1, FileItemInfoLen_FirmPara_ChkSum1);
            }
            break;
        case 0x00f81103:
            if ((RxFrm->Len != (12 + 10)) && (RxFrm->Len != (12 + 20)) && (RxFrm->Len != (12 + 5)))
            {
                return (DL645B_ERRINFO_DATA);
            }
            if (MeasureFirmPara.PRth[0] == 0 && MeasureFirmPara.PRth[1] == 0 && MeasureFirmPara.PRth[2] == 0 && MeasureFirmPara.PRth[3] == 0)
            {
                return (DL645B_ERRINFO_DATA);
            }
            EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
            fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
            if (RxFrm->Len == (12 + 10))
            {
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealAngle + 2, &RxFrm->UDat.Dat[8], 10);
                RxFrm->UDat.Dat[12] = 0;
                RxFrm->UDat.Dat[13] = 0;
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealAngle, &RxFrm->UDat.Dat[12], 2);
                MeasureRms.PriData.Flag |= MEASURE_FLAG_CorrectionPHSM;
            }
            else if (RxFrm->Len == (12 + 20))
            {
                Std_Memcpy(&tempis, &(RxFrm->UDat.Dat[8]), 4);
                Std_Memcpy(&tempus, &(RxFrm->UDat.Dat[12]), 4);

                for (i = 0; i < 3; i++)
                {
                    Std_Memcpy(&temppw[1], &(RxFrm->UDat.Dat[16 + 4 * i]), 4);
                    temppw[1] = (u32)(((float)tempus / (float)tempis) * (float)temppw[1]);
                    fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealAngle + 4 * i, (u8 *)&temppw[1], 4);
                }
                MeasureRms.PriData.Flag |= MEASURE_FLAG_CorrectionPHSM;
            }
            else
            {
                Std_Memcpy(&tempis, &(RxFrm->UDat.Dat[9]), 4);
                EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
                fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
                if (tempis > 0x7fffffff)
                {
                    ADErr = -(float)(0xffffffff - tempis) / 100000;
                }
                else
                {
                    ADErr = (float)tempis / 100000;
                }
                ADErr = -ADErr / 1.732;
                if (ADErr >= 0)
                {
                    tempub = ADErr * 32768 + 0.5; //四舍五入
                }
                else
                {
                    tempub = 65536 + ADErr * 32768 + 0.5;
                }
                MeasureFirmPara.P_PHSMH[RxFrm->UDat.Dat[8] * 2 + 1] = 0;
                MeasureFirmPara.Q_PHSMH[RxFrm->UDat.Dat[8] * 2 + 1] = 0;
                Std_Memcpy((u8 *)&MeasureFirmPara.P_PHSMH[RxFrm->UDat.Dat[8] * 2 + 1], &tempub, 0x02);
                Std_Memcpy((u8 *)&MeasureFirmPara.Q_PHSMH[RxFrm->UDat.Dat[8] * 2 + 1], &tempub, 0x02);
                fnRN8302_Write(RN8302_PA_PHSH + RxFrm->UDat.Dat[8] * 2, (u8 *)&MeasureFirmPara.P_PHSMH[RxFrm->UDat.Dat[8] * 2 + 1], 3);
                fnRN8302_Write(RN8302_QA_PHSH + RxFrm->UDat.Dat[8] * 2, (u8 *)&MeasureFirmPara.Q_PHSMH[RxFrm->UDat.Dat[8] * 2 + 1], 3);

                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_P_PHSMH, (u8 *)&MeasureFirmPara.P_PHSMH[0], 48);

                EmuCommbuf.ucTemp8 = 0xDC; // 写保护
                fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
                MeasureFirmPara.ChkSum1 = 0;
                SystemDelay(10);
                MeasureRms.PriData.Flag |= MEASURE_FLAG_CalcCheckSum;
                fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureFirmPara.ChkSum1, 3) ;
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_ChkSum1, (u8 *)&MeasureFirmPara.ChkSum1, FileItemInfoLen_FirmPara_ChkSum1);
            }
            break;
        // 零线电流校准
        case 0x00F81200:
            if (RxFrm->Len != (12 + 4))
            {
                return (DL645B_ERRINFO_DATA);
            }
            Std_MemRvs((u8*)&tempis, &(RxFrm->UDat.Dat[8]), 4);      // dyf 主台下发的电流是大端模式，高字节在前低字节在后Std_Memcpy=>Std_MemRvs
            MeasureFirmPara.RealI[3] = tempis;
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_RealI + 12, (u8 *)&MeasureFirmPara.RealI[3], 4);
            EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
            fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
            MeasureRms.PriData.Flag |= MEASURE_FLAG_CorrectionIn;
            break;
        case 0x00f81400:        // 功率OFFSET校正
            if (RxFrm->Len != (12 + 3))
            {
                return (DL645B_ERRINFO_DATA);
            }
            if (RxFrm->UDat.Dat[8] > 0x39)
            {
                return (DL645B_ERRINFO_DATA);
            }
            if (RxFrm->UDat.Dat[8] < 0x37)
            {
                return (DL645B_ERRINFO_DATA);
            }
            Std_Memcpy(&tempub, &(RxFrm->UDat.Dat[9]), 2);
            MeasureFirmPara.P_OS[RxFrm->UDat.Dat[8] - 0x37] = tempub;
            MeasureFirmPara.Q_OS[RxFrm->UDat.Dat[8] - 0x37] = MeasureFirmPara.P_OS[RxFrm->UDat.Dat[8] - 0x37];
            EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
            fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
            fnRN8302_Write(0x0100+RxFrm->UDat.Dat[8], (u8 *)&MeasureFirmPara.P_OS[RxFrm->UDat.Dat[8] - 0x37], 2);
            fnRN8302_Write(0x0100+RxFrm->UDat.Dat[8] + 3, (u8 *)&MeasureFirmPara.Q_OS[RxFrm->UDat.Dat[8] - 0x37], 2);
            EmuCommbuf.ucTemp8 = 0xDC; // 写保护
            fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_P_OS, (u8 *)&MeasureFirmPara.P_OS[0], FileItemInfoLen_FirmPara_P_OS);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_Q_OS, (u8 *)&MeasureFirmPara.Q_OS[0], FileItemInfoLen_FirmPara_Q_OS);
            MeasureFirmPara.ChkSum1 = 0;
            SystemDelay(10);
            MeasureRms.PriData.Flag |= MEASURE_FLAG_CalcCheckSum;
            fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureFirmPara.ChkSum1, 3) ;
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_ChkSum1, (u8 *)&MeasureFirmPara.ChkSum1, FileItemInfoLen_FirmPara_ChkSum1);
            break;
        case 0x00F81402:      // 电压电流OFFSET校正
            if (RxFrm->Len != (12 + 3))
            {
                return (DL645B_ERRINFO_DATA);
            }
            if (RxFrm->UDat.Dat[8] > 0x06)
            {
                return (DL645B_ERRINFO_DATA);
            }
            Std_Memcpy(&tempub, &(RxFrm->UDat.Dat[9]), 2);
            MeasureFirmPara.U_OS[RxFrm->UDat.Dat[8]] = tempub;
            EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
            fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

            i = RxFrm->UDat.Dat[8];
            if (i < 3) //电压
            {
                fnRN8302_Write(0x0121+ i, (u8 *)&MeasureFirmPara.U_OS[i], 2);
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_U_OS + i * 2, (u8 *)&MeasureFirmPara.U_OS[i], 2);
            }
            else
            {
                i -= 3;
                fnRN8302_Write(0x0124+ i, (u8 *)&MeasureFirmPara.I_OS[i], 2);
                fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_I_OS + i * 2, (u8 *)&MeasureFirmPara.I_OS[i], 2);
            }
            #if(CT_Check == 1)
            Dl645CTCheck.CTCheckStatus = CTCheck_FLAG_IDLE;
            EmuCommbuf.ucTempBuf[0] = 0x10; // 计量控制位 默认值 043210
            EmuCommbuf.ucTempBuf[1] = 0x32;
            EmuCommbuf.ucTempBuf[2] = 0x07;
            fnRN8302_Write(0x0160, EmuCommbuf.ucTempBuf, 3);
            #endif
            EmuCommbuf.ucTemp8 = 0xDC; // 写保护
            fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);

            MeasureFirmPara.ChkSum1 = 0;
            SystemDelay(15);
            MeasureRms.PriData.Flag |= MEASURE_FLAG_CalcCheckSum;
            fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureFirmPara.ChkSum1, 3) ;
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_ChkSum1, (u8 *)&MeasureFirmPara.ChkSum1, FileItemInfoLen_FirmPara_ChkSum1);
            break;
        case 0x00f81501:        // 误差校正功率增益
            if (RxFrm->Len != (12 + 5))
            {
                return (DL645B_ERRINFO_DATA);
            }
            if (RxFrm->UDat.Dat[8] > 0x03)
            {
                return (DL645B_ERRINFO_DATA);
            }
            Std_Memcpy(&tempis, &(RxFrm->UDat.Dat[9]), 4);
            EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
            fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
            if (tempis > 0x7fffffff)
            {
                ADErr = -(float)(0xffffffff - tempis) / 100000;
            }
            else
            {
                ADErr = (float)tempis / 100000;
            }
            ADErr = ((-ADErr) / (1 + ADErr));
            if (ADErr >= 0)
            {
                MeasureFirmPara.GP[RxFrm->UDat.Dat[8]] = (u16)(ADErr * 32768 + 0.5);    //四舍五入
            }
            else
            {
                MeasureFirmPara.GP[RxFrm->UDat.Dat[8]] = (u16)(65536 + ADErr * 32768 + 0.5);
            }

            MeasureFirmPara.GQ[RxFrm->UDat.Dat[8]] = MeasureFirmPara.GP[RxFrm->UDat.Dat[8]];
            MeasureFirmPara.GS[RxFrm->UDat.Dat[8]] = MeasureFirmPara.GP[RxFrm->UDat.Dat[8]];

            fnRN8302_Write(RN8302_GPA + RxFrm->UDat.Dat[8], (u8 *)&MeasureFirmPara.GP[RxFrm->UDat.Dat[8]], 2);
            fnRN8302_Write(RN8302_GQA + RxFrm->UDat.Dat[8], (u8 *)&MeasureFirmPara.GQ[RxFrm->UDat.Dat[8]], 2);
            fnRN8302_Write(RN8302_GSA + RxFrm->UDat.Dat[8], (u8 *)&MeasureFirmPara.GS[RxFrm->UDat.Dat[8]], 2);

            EmuCommbuf.ucTemp8 = 0xDC; // 写保护
            fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
            #if(CT_Check == 1)
            Dl645CTCheck.CTCheckStatus = CTCheck_FLAG_IDLE;
            EmuCommbuf.ucTempBuf[0] = 0x10; // 计量控制位 默认值 043210
            EmuCommbuf.ucTempBuf[1] = 0x32;
            EmuCommbuf.ucTempBuf[2] = 0x07;
            fnRN8302_Write(0x0160, EmuCommbuf.ucTempBuf, 3);
            #endif
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_GP, (u8 *)&MeasureFirmPara.GP[0], FileItemInfoLen_FirmPara_GP);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_GQ, (u8 *)&MeasureFirmPara.GQ[0], FileItemInfoLen_FirmPara_GQ);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_GS, (u8 *)&MeasureFirmPara.GS[0], FileItemInfoLen_FirmPara_GS);
            MeasureFirmPara.ChkSum1 = 0;
            SystemDelay(5);
            MeasureRms.PriData.Flag |= MEASURE_FLAG_CalcCheckSum;
            fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureFirmPara.ChkSum1, 3) ;
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_ChkSum1, (u8 *)&MeasureFirmPara.ChkSum1, FileItemInfoLen_FirmPara_ChkSum1);
            break;
        case 0x00f81600:
            if ((RxFrm->Len != (12 + 1)) && (RxFrm->UDat.Dat[8] != 0x5A))
            {
                return (DL645B_ERRINFO_DATA);
            }
            fnMeasure_FirmParaInit(2);

            break;
        case 0x00f81601:
            if ((RxFrm->Len != (12 + 1)) && (RxFrm->UDat.Dat[8] > 100))
            {
                return (DL645B_ERRINFO_DATA);
            }
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_HighPulseRate, &RxFrm->UDat.Dat[8], 1);
            break;
        case 0x00f81604:        // 设置高频放大倍数
            if ((RxFrm->Len != (12 + 1)) || (RxFrm->UDat.Dat[8] > 100))
            {
                return (DL645B_ERRINFO_DATA);
            }
            if (RxFrm->UDat.Dat[8] == 0)
            {
                return (DL645B_ERRINFO_DATA);
            }
            if ((MeasureFirmPara.HFConst1 / RxFrm->UDat.Dat[8]) == 0)
            {
                return (DL645B_ERRINFO_DATA);
            }
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_HighPulseRate, &RxFrm->UDat.Dat[8], 1);
            break;

            #else   //单相表校表

        case 0x00f81000:        //A 通道增益校正
            if (RxFrm->Len != (12 + 24))
            {
                return (DL645B_ERRINFO_MISC);
            }

            fnMeasure_WaveColse();

            Std_Memset((u8 *)&stand, 0x00, sizeof(sCorrectTmp_TypeDef));

            Std_Memcpy((u8 *)&stand.PConstE, &(RxFrm->UDat.Dat[8]), 2);
            Std_Memcpy((u8 *)&stand.Hfconst, &(RxFrm->UDat.Dat[10]), 2);
            Std_Memcpy((u8 *)&stand.StandUn[0], &(RxFrm->UDat.Dat[12]), 4);
            Std_Memcpy((u8 *)&stand.StandUnreg[0], &(RxFrm->UDat.Dat[16]), 4);
            Std_Memcpy((u8 *)&stand.StandIb[0], &(RxFrm->UDat.Dat[20]), 4);
            Std_Memcpy((u8 *)&stand.StandIbreg[0], &(RxFrm->UDat.Dat[24]), 4);
            Std_Memcpy((u8 *)&stand.Err[0], &(RxFrm->UDat.Dat[28]), 4);

            err = fnMeasure_GPCorrect(&stand);
            stand.Err[0] = 0x00;  //----B通道采样功率法--------
            //---需要通过A、B通道的有功无功计算电流矢量和，B通道也需要校正-----------
            fnMeasure_GPBCorrect(&stand);
            fnMeasure_WaveInit();
            if (err == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
            break;

        case 0x00f81100:        //A 通道相位校正
            if (RxFrm->Len != (12 + 12))
            {
                return (DL645B_ERRINFO_MISC);
            }

            fnMeasure_WaveColse();

            Std_Memset((u8 *)&stand, 0x00, sizeof(sCorrectTmp_TypeDef));

            Std_Memcpy((u8 *)&stand.StandPw[0], &(RxFrm->UDat.Dat[8]), 4);
            Std_Memcpy((u8 *)&stand.StandPwreg[0], &(RxFrm->UDat.Dat[12]), 4);
            Std_Memcpy((u8 *)&stand.Err[0], &(RxFrm->UDat.Dat[16]), 4);

            err = fnMeasure_PhsACorrect(&stand);

            fnMeasure_WaveInit();

            if (err == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }

            break;

        case 0x00f81101:        //A 通道相位校正,无功
            if (RxFrm->Len != (12 + 12))
            {
                return (DL645B_ERRINFO_MISC);
            }

            Std_Memset((u8 *)&stand, 0x00, sizeof(sCorrectTmp_TypeDef));

            Std_Memcpy((u8 *)&stand.StandPw[0], &(RxFrm->UDat.Dat[8]), 4);
            Std_Memcpy((u8 *)&stand.StandPwreg[0], &(RxFrm->UDat.Dat[12]), 4);
            Std_Memcpy((u8 *)&stand.Err[0], &(RxFrm->UDat.Dat[16]), 4);

            fnMeasure_WaveColse();

            err = fnMeasure_QPhsCalCorrect(&stand);

            fnMeasure_WaveInit();

            if (err == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }

            break;

        case 0x00f81201:        //A 通道小电流校正
            if (RxFrm->Len != (12 + 8))
            {
                return (DL645B_ERRINFO_MISC);
            }

            Std_Memset((u8 *)&stand, 0x00, sizeof(sCorrectTmp_TypeDef));

            Std_Memcpy((u8 *)&stand.StandPw[0], &(RxFrm->UDat.Dat[8]), 4);
            Std_Memcpy((u8 *)&stand.Err[0], &(RxFrm->UDat.Dat[12]), 4);

            fnMeasure_WaveColse();

            err = fnMeasure_APOSACorrect(&stand);

            fnMeasure_WaveInit();

            if (err == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
            break;

        case 0x00f81300:        //B 通道电流校正
            if (RxFrm->Len != (12 + 12))
            {
                return (DL645B_ERRINFO_MISC);
            }

            Std_Memset((u8 *)&stand, 0x00, sizeof(sCorrectTmp_TypeDef));

            Std_Memcpy((u8 *)&stand.StandIb[0], &(RxFrm->UDat.Dat[8]), 4);
            Std_Memcpy((u8 *)&stand.StandIbreg[0], &(RxFrm->UDat.Dat[12]), 4);
            Std_Memcpy((u8 *)&stand.Err[0], &(RxFrm->UDat.Dat[16]), 4);

            fnMeasure_WaveColse();

            err = fnMeasure_KIBrmsCorrect(&stand);

            fnMeasure_WaveInit();

            if (err == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }

            break;

        case 0x00f81500:
            if (RxFrm->Len != (12 + 3))
            {
                return (DL645B_ERRINFO_MISC);
            }

            fnMeasure_WaveColse();

            err = fnMeasure_RMSOSCorrect();

            fnMeasure_WaveInit();

            if (err == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }

            break;

        case 0x00f81600:
            if ((RxFrm->Len != (12 + 1)) && (RxFrm->UDat.Dat[8] != 0x5A))
            {
                return (DL645B_ERRINFO_DATA);
            }
            fnMeasure_FirmParaInit(1);

            break;
            #endif

        case 0x00f81605:            // 设置脉冲常数
            if (RxFrm->Len != (12 + 2))
            {
                return (DL645B_ERRINFO_DATA);
            }
            Std_Memcpy(&tempconst, &(RxFrm->UDat.Dat[8]), 2);

            ConstE.Dat = (u32)tempconst * 10;

            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_PConstE, (u8 *)&ConstE, 4);
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_QConstE, (u8 *)&ConstE, 4);
            break;
        case 0x00f81606:  //电压影响量补偿
            if (RxFrm->Len != (12 + 6))
            {
                return (DL645B_ERRINFO_DATA);
            }
            if (RxFrm->UDat.Dat[8] > nPhs)
            {
                return (DL645B_ERRINFO_DATA);
            }
            Std_Memcpy(&tempis, &(RxFrm->UDat.Dat[10]), 4);

            fnMeasure_WaveColse();

            if (fnMeasure_VoltRepairCorrect(RxFrm->UDat.Dat[8], RxFrm->UDat.Dat[9], tempis) == FALSE)
            {
                return (DL645B_ERRINFO_DATA);
            }

            fnMeasure_WaveInit();

            break;

        case 0x00f81607:  //计量芯片 Trim
            if (RxFrm->Len != (12 + 2))
            {
                return (DL645B_ERRINFO_DATA);
            }
            Std_Memcpy(&tempuc, &(RxFrm->UDat.Dat[8]), 2);

            fnMeasure_TIRM_CommWrite(tempuc);

            break;

            #if(nPhs==ThreePhs)
        case 0x00f81608:  //8207D Trim
            if (RxFrm->Len != (12 + 3))
            {
                return (DL645B_ERRINFO_DATA);
            }
            if (RxFrm->UDat.Dat[8] > nPhs)
            {
                return (DL645B_ERRINFO_DATA);
            }
            Std_Memcpy(&tempuc, &(RxFrm->UDat.Dat[9]), 2);

            fnMeasure_RN8207DTIRM_CommWrite(RxFrm->UDat.Dat[8], tempuc);

            break;
            #endif

        case 0x00f81609:        //----设置谐波增益补偿--A----
        case 0x00f8160A:        //----设置谐波增益补偿--B----
        case 0x00f8160B:        //----设置谐波增益补偿--C----
        {
            if (RxFrm->Len != (12 + 5))
            {
                return (DL645B_ERRINFO_DATA);
            }

            sCorrectTmp_TypeDef   stand;
            u8 nphs;

            nphs = (u8)(DITemp - 0x00f81609);

            Std_Memset((u8 *)&stand, 0x00, sizeof(sCorrectTmp_TypeDef));
            Std_Memcpy((u8 *)&stand.Err[0], &(RxFrm->UDat.Dat[9]), 4);

            fnMeasure_WaveColse();
            err = fnHarmonic_GPCorrect(&stand, nphs, RxFrm->UDat.Dat[8]);
            fnMeasure_WaveInit();

            if (err == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
        }
        break;

        case 0x00f8160C:    //----设置谐波 相位补偿--A----
        case 0x00f8160D:    //----设置谐波相位补偿--B----
        case 0x00f8160E:    //----设置谐波相位补偿--C----
        {
            if (RxFrm->Len != (12 + 5))
            {
                return (DL645B_ERRINFO_DATA);
            }

            sCorrectTmp_TypeDef   stand;
            u8 nphs;

            nphs = (u8)(DITemp - 0x00f8160C);

            Std_Memset((u8 *)&stand, 0x00, sizeof(sCorrectTmp_TypeDef));
            Std_Memcpy((u8 *)&stand.Err[0], &(RxFrm->UDat.Dat[9]), 4);

            err = fnHarmonic_PhsCorrect(&stand, nphs, RxFrm->UDat.Dat[8]);

            if (err == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
        }
        break;

        case 0x00f91100:        // 设置RTC的DOTA0
            if (RxFrm->Len != (12 + 2))
            {
                return (DL645B_ERRINFO_MISC);
            }
            Std_Memcpy((u8 *)&RTCPara.RTCDota0, &(RxFrm->UDat.Dat[8]), 2);
            RtcWriteDota(RTCPara.RTCDota0);
            fnCrc_Check(0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef) - 2, (u8 *)&RTCPara.Crc);
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef));

            fnPowerUp_RTCParaInit();
            break;
        case 0x00f91f00:        /*"设置RTC的曲线模式"*/
            if (RxFrm->Len != (12 + 2))
            {
                return (DL645B_ERRINFO_MISC);
            }
            Std_Memcpy((u8 *)&RTCPara.CurveMode, &(RxFrm->UDat.Dat[8]), 2);
            fnCrc_Check(0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef) - 2, (u8 *)&RTCPara.Crc);
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef));
            fnPowerUp_RTCParaInit();
            break;
        case 0x00f91f01:        /*""*/
            if (RxFrm->Len != (12 + 2))
            {
                return (DL645B_ERRINFO_MISC);
            }
            Std_Memcpy((u8 *)&RTCPara.DATA0, &(RxFrm->UDat.Dat[8]), 2);
            fnCrc_Check(0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef) - 2, (u8 *)&RTCPara.Crc);
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef));
            fnPowerUp_RTCParaInit();
            break;
        case 0x00f91f02:        /*""*/
            if (RxFrm->Len != (12 + 2))
            {
                return (DL645B_ERRINFO_MISC);
            }
            Std_Memcpy((u8 *)&RTCPara.XT1, &(RxFrm->UDat.Dat[8]), 2);
            fnCrc_Check(0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef) - 2, (u8 *)&RTCPara.Crc);
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef));
            fnPowerUp_RTCParaInit();
            break;
        case 0x00f91f03:        /*""*/
            if (RxFrm->Len != (12 + 2))
            {
                return (DL645B_ERRINFO_MISC);
            }
            Std_Memcpy((u8 *)&RTCPara.ALPHA, &(RxFrm->UDat.Dat[8]), 2);
            fnCrc_Check(0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef) - 2, (u8 *)&RTCPara.Crc);
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef));
            fnPowerUp_RTCParaInit();
            break;
        case 0x00f91f04:        /*""*/
            if (RxFrm->Len != (12 + 2))
            {
                return (DL645B_ERRINFO_MISC);
            }
            Std_Memcpy((u8 *)&RTCPara.BETA, &(RxFrm->UDat.Dat[8]), 2);
            fnCrc_Check(0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef) - 2, (u8 *)&RTCPara.Crc);
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef));
            fnPowerUp_RTCParaInit();
            break;
        case 0x00f91f05:        /*""*/
            if (RxFrm->Len != (12 + 2))
            {
                return (DL645B_ERRINFO_MISC);
            }
            Std_Memcpy((u8 *)&RTCPara.GAMMA, &(RxFrm->UDat.Dat[8]), 2);
            fnCrc_Check(0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef) - 2, (u8 *)&RTCPara.Crc);
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef));
            fnPowerUp_RTCParaInit();
            break;
        case 0x00f91f06:       /*""*/
            if (RxFrm->Len != (12 + 2))
            {
                return (DL645B_ERRINFO_MISC);
            }
            Std_Memcpy((u8 *)&RTCPara.ZETA, &(RxFrm->UDat.Dat[8]), 2);
            fnCrc_Check(0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef) - 2, (u8 *)&RTCPara.Crc);
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef));
            fnPowerUp_RTCParaInit();
            break;
        //    case 0x00f91101:
        //  case 0x00f91102:
        //  case 0x00f91103:
        //  case 0x00f91104:
        //  case 0x00f91105:
        //  case 0x00f91106:
        //  case 0x00f91107:
        //  case 0x00f91108:
        //  case 0x00f91109:
        //  case 0x00f9110a:
        //      if(RxFrm->Len != (12 + 1)) return(DL645B_ERRINFO_MISC);
        //      Std_Memcpy(&RTCPara.RTC_CAL_Data[RxFrm->UDat.DI0-1] ,&(RxFrm->UDat.Dat[8]) ,1 );
        //      tempis = 0;
        //      tempis |=  RTCPara.RTC_CAL_Data[RxFrm->UDat.DI0-1];
        //      RTC->CALPS = 0xA8;
        //      RTC->CAL_T[RxFrm->UDat.DI0-1] = tempis;
        //      fnFile_Write(FileId_HighPara,FileItemInfoOffAddr_HighPara_RTCCalData + RxFrm->UDat.DI0 - 1,(u8 *)&RTCPara.RTC_CAL_Data[RxFrm->UDat.DI0-1],1);
        //      break;
        //  case 0x00f91200:
        //      if(RxFrm->Len != (12 + 2)) return(DL645B_ERRINFO_MISC);
        //      Std_Memcpy(&MeasureFirmPara.TemperAdj[0] ,&(RxFrm->UDat.Dat[8]) ,2 );
        //      fnFile_Write(FileId_FirmPara,FileItemInfoOffAddr_FirmPara_TemperAdj,&MeasureFirmPara.TemperAdj[0],2);
        //      break;
        //  case 0x00f91201:        // 设置RTC高低温的补偿值
        //      if(RxFrm->Len != (12 + 3)) return(DL645B_ERRINFO_MISC);
        //      Std_Memcpy(&RTCPara.RTCAdj[0] ,&(RxFrm->UDat.Dat[8]) ,3 );
        //      fnFile_Write(FileId_HighPara,FileItemInfoOffAddr_HighPara_RTCAdj,&RTCPara.RTCAdj[0],3);
        //      break;

        case 0x00f91a00:        //清除清零事件数据
            if ((RxFrm->Len != (12 + 1)) && (RxFrm->UDat.Dat[8] != 0x5A))
            {
                return (DL645B_ERRINFO_MISC);
            }
            Event.PriData.OpFlag |= (1 << EVENT_STYLE_CLR);
            Event.PriData.Clr_Word = 0xabcdef5a;
            break;
        case 0x00fb1001:        //写RN8302B寄存器 liqiushi add
            if ((RxFrm->Len != (12 + 3)))
            {
                return (DL645B_ERRINFO_MISC);
            }
            Rn_ReadInfo[0] = RxFrm->UDat.Dat[8];
            Rn_ReadInfo[1] = RxFrm->UDat.Dat[9];
            Rn_ReadInfo[2] = RxFrm->UDat.Dat[10];
            Rn_ReadInfo[3] = 0;
            break;
        case 0x00fb1002:        //写RN8302B寄存器 liqiushi addd
            //if((RxFrm->Len != (12 + 1)) && (RxFrm->UDat.Dat[8] != 0x5A)) return(DL645B_ERRINFO_MISC);
            EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
            fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
            EmuCommbuf.ucTempBuf[0] = 0x00;
            EmuCommbuf.ucTempBuf[1] = 0xe5;
            EmuCommbuf.ucTempBuf[2] = 0x00;
            EmuCommbuf.ucTempBuf[3] = 0x00;
            fnRN8302_Write(RN8302_WREN2, EmuCommbuf.ucTempBuf, 4);
            if (RxFrm->Len == (12 + 2 + 1))
            {
                EmuCommbuf.ucTempBuf[0] = RxFrm->UDat.Dat[10];
                EmuCommbuf.ucTempBuf[1] = 0x00;
                EmuCommbuf.ucTempBuf[2] = 0x00;
                EmuCommbuf.ucTempBuf[3] = 0x00;
                fnRN8302_Write(((RxFrm->UDat.Dat[8] << 8) + RxFrm->UDat.Dat[9]), EmuCommbuf.ucTempBuf, (RxFrm->Len - 14));
            }
            else if (RxFrm->Len == (12 + 2 + 2))
            {
                EmuCommbuf.ucTempBuf[0] = RxFrm->UDat.Dat[11];
                EmuCommbuf.ucTempBuf[1] = RxFrm->UDat.Dat[10];
                EmuCommbuf.ucTempBuf[2] = 0x00;
                EmuCommbuf.ucTempBuf[3] = 0x00;
                fnRN8302_Write(((RxFrm->UDat.Dat[8] << 8) + RxFrm->UDat.Dat[9]), EmuCommbuf.ucTempBuf, (RxFrm->Len - 14));
            }
            else if (RxFrm->Len == (12 + 2 + 3))
            {
                EmuCommbuf.ucTempBuf[0] = RxFrm->UDat.Dat[12];
                EmuCommbuf.ucTempBuf[1] = RxFrm->UDat.Dat[11];
                EmuCommbuf.ucTempBuf[2] = RxFrm->UDat.Dat[10];
                EmuCommbuf.ucTempBuf[3] = 0x00;
                fnRN8302_Write(((RxFrm->UDat.Dat[8] << 8) + RxFrm->UDat.Dat[9]), EmuCommbuf.ucTempBuf, (RxFrm->Len - 14));
            }
            else if (RxFrm->Len == (12 + 2 + 4))
            {
                EmuCommbuf.ucTempBuf[0] = RxFrm->UDat.Dat[13];
                EmuCommbuf.ucTempBuf[1] = RxFrm->UDat.Dat[12];
                EmuCommbuf.ucTempBuf[2] = RxFrm->UDat.Dat[11];
                EmuCommbuf.ucTempBuf[3] = RxFrm->UDat.Dat[10];;
                fnRN8302_Write(((RxFrm->UDat.Dat[8] << 8) + RxFrm->UDat.Dat[9]), EmuCommbuf.ucTempBuf, (RxFrm->Len - 14));
            }
            else
            {
            }
            break;
        case 0x00fa0101:
            if (RxFrm->Len != (12 + 6))
            {
                return (DL645B_ERRINFO_MISC);
            }

            fnFile_Write(FileId_ParaASCII, FileItemInfoOffAddr_ASCIIPara_FactoryMAC, &(RxFrm->UDat.Dat[8]), 6);

            break;

        case 0x00001401:                        // 跳闸延时时间 NNNN
            if (RxFrm->Len != (12 + 2))
            {
                return (DL645B_ERRINFO_MISC);
            }
            if (fnDl645B_FramCheckBCD(&RxFrm->UDat.Dat[8], 2) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }

            if (Output.PubData.GateOffRemainTime) //跳闸延时时间
            {
                Output.PubData.GateOffRemainTime = 0;
                Std_Memcpy(&tempuc, &RxFrm->UDat.Dat[8], 2);
                tempuc = fnBcdToHex_u16(tempuc);
                Output.PubData.GateOffRemainTime = tempuc * 60;
                //Bkgrd.PubData.MtSta.MtSta3.StaBit.PreGateOff = 1;
            }
            break;
        case 0x00FB0101://端子温度校准
        case 0x00FB0102:
        case 0x00FB0103:
        case 0x00FB0104:
        case 0x00FB0105:    // dyf 增加 5~8路的DI
        case 0x00FB0106:
        case 0x00FB0107:
        case 0x00FB0108:
            i = (DITemp & 0x0F) - 1;
            Std_Memcpy((u8 *)&gTemperSchoolParaMem.chan[i].k, &(RxFrm->UDat.Dat[8]), 4);
            Std_Memcpy((u8 *)&gTemperSchoolParaMem.chan[i].offs, &(RxFrm->UDat.Dat[12]), 4);
            if ((gTemperSchoolParaMem.chan[i].k == 10000) && (gTemperSchoolParaMem.chan[i].offs == 0))
            {
                gTemperSchoolParaMem.chan[i].valid = 0;
                gTemperSchoolParaTemp.chan[i].valid = 0;
            }
            else
            {
                gTemperSchoolParaMem.chan[i].valid = 0xA5;
                gTemperSchoolParaTemp.chan[i].valid = 0xA5;
            }
            gTemperSchoolParaTemp.chan[i].k = gTemperSchoolParaMem.chan[i].k * 0.8192;
            gTemperSchoolParaTemp.chan[i].offs = gTemperSchoolParaMem.chan[i].offs * 0.001;

            fnFile_Write(FileId_TemperSchoolPara, i * sizeof(sTemperSchoolParaItem_TypeDef), (u8 *)&gTemperSchoolParaMem.chan[i].valid, sizeof(sTemperSchoolParaItem_TypeDef));
            break;

        default:
            return (DL645B_ERRINFO_MISC);
            break;
    }
    if (DITemp != 0x00001503)
    {
        fnDl645Event_Operation(EVENT_STYLE_PRG, EVENT_OPERATION_RUN, &RxFrm->UDat.Dat[4], &RxFrm->UDat.DI0);
    }

    return (DL645B_ERRINFO_OK);
}

// 一类参数设置，ESAM中文件的设置，密码级别为99H，明文+MAC进行设置
eDL645B_ErrInfo_TypeDef fnDl645_PutParaVarWithMac(sFrmDl645B_TypeDef *RxFrm)
{
    u8  i;
    u32 DITemp = 0x0;
    #if(METERTYPE == 2)
    u8  nRmYear;
    u8  nLadder;
    #endif
    ErrorStatus err;

    if (!Secret.RemoteValid)
    {
        return (DL645B_ERRINFO_PSW);
    }
    if (Secret.nMacErr >= MAX_MACERR)
    {
        return (DL645B_ERRINFO_PSW);
    }
    i = RxFrm->UDat.DI3;
    RxFrm->UDat.DI3 = 0;
    Std_Memcpy(&DITemp, &RxFrm->UDat.DI0, 4);
    RxFrm->UDat.DI3 = i;
    switch (DITemp)
    {
            #if(METERTYPE ==2)
        case 0x00000108:                // 两套费率电价切换时间
            err = fnDl645B_JudgeSwitch(&RxFrm->UDat.Dat[8]);        // 比较设置参数的合法性
            if (err == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
            err = fnICEsam_Update_ESAM_Bin_Mac(0x82, 10, &RxFrm->UDat.Dat[8], 5);
            if (err == ERROR)
            {
                return (DL645B_ERRINFO_PSW);
            }
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara, &RxFrm->UDat.Dat[8], 0x05);
            fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Misc + 14, &i, 1);
            i &= 0x7f;
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Misc + 14, &i, 1);
            Bkgrd.PubData.UpFlStatusFlag = 0x5a;
            break;
        case 0x00000109:            // 两套梯度切换时间
            err = fnDl645B_JudgeSwitch(&RxFrm->UDat.Dat[8]);
            if (err == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
            err = fnICEsam_Update_ESAM_Bin_Mac(0x84, 196, &RxFrm->UDat.Dat[8], 5);
            if (err == ERROR)
            {
                return (DL645B_ERRINFO_PSW);
            }
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara, &RxFrm->UDat.Dat[8], sizeof(sDF15));
            fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Misc + 15, &i, 1);
            i &= 0x7f;
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Misc + 15, &i, 1);
            Bkgrd.PubData.UpFlStatusFlag = 0x5a;
            break;
            #endif
        case 0x00000306:                // 电流互感器变比
        case 0x00000307:                // 电压互感器变比
            if (fnDl645B_FramCheckBCD(&RxFrm->UDat.Dat[8], 3) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
            if (RxFrm->UDat.DI0 == 0x06)
            {
                err = fnICEsam_Update_ESAM_Bin_Mac(0x82, 24, &RxFrm->UDat.Dat[8], 3);
                if (err != ERROR)
                {
                    fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_CT, &RxFrm->UDat.Dat[8], 0x03);
                    Std_Memcpy((u8 *)&EgMoney.PubPara.MeterCT, &RxFrm->UDat.Dat[8], 3);
                }
            }
            else
            {
                err = fnICEsam_Update_ESAM_Bin_Mac(0x82, 27, &RxFrm->UDat.Dat[8], 3);
                if (err != ERROR)
                {
                    fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_PT, &RxFrm->UDat.Dat[8], 0x03);
                    Std_Memcpy((u8 *)&EgMoney.PubPara.MeterPT, &RxFrm->UDat.Dat[8], 3);
                }
            }
            if (err == ERROR)
            {
                return (DL645B_ERRINFO_PSW);
            }
            fnCrc_Check(0, (u8 *)&EgMoney.PubPara.MeterCT, sizeof(sDF10) * 2, (u8 *)&EgMoney.PubPara.Crc);
            #if(METERTYPE ==2)
            fnDl645Energy_EsamInit();
            #endif
            Bkgrd.PubData.UpRunFileFlag = 0x5a;
            break;
        case 0x00000402:                // 表号
            if (fnDl645B_FramCheckBCD(&RxFrm->UDat.Dat[8], 6) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);    //BCD码判断
            }
            if (Bkgrd.PubData.CipherKeyFlag)
            {
                return (DL645B_ERRINFO_MISC);    //正式密钥不允许修改表号
            }
            err = fnICEsam_Update_ESAM_Bin_Mac(0x82, 30, &RxFrm->UDat.Dat[8], 6);
            if (err != SUCCESS)
            {
                return (DL645B_ERRINFO_PSW);    //当传输的数据MAC 校验错是采用错误信息字ERR 中bit2（密码错/未授权）置位，并按照异常应答帧响应。
            }
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_MeterNo, &RxFrm->UDat.Dat[8], 0x06);
            Bkgrd.PubData.UpRunFileFlag = 0x5a;
            break;
            #if(METERTYPE)
        case 0x0000040e:                // 客户编号
            if (Bkgrd.PubData.CipherKeyFlag)
            {
                return (DL645B_ERRINFO_MISC);
            }
            if (fnDl645B_FramCheckBCD(&RxFrm->UDat.Dat[8], 6) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);    //BCD码判断
            }
            err = fnICEsam_Update_ESAM_Bin_Mac(0x82, 36, &RxFrm->UDat.Dat[8], 6);
            if (err != SUCCESS)
            {
                return (DL645B_ERRINFO_PSW);    //当传输的数据MAC 校验错是采用错误信息字ERR 中bit2（密码错/未授权）置位，并按照异常应答帧响应。
            }
            fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_UserNo, &RxFrm->UDat.Dat[8], 0x06);
            Bkgrd.PubData.UpRunFileFlag = 0x5a;
            break;
            #endif
            #if(METERTYPE ==2)
        case 0x00001001:                // 报警金额1限值
        case 0x00001002:                // 报警金额2限值
            if (fnDl645B_FramCheckBCD(&RxFrm->UDat.Dat[8], 4) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);    //BCD码判断
            }
            err = fnICEsam_Update_ESAM_Bin_Mac(0x82, 16 + (RxFrm->UDat.DI0 - 1) * 4, &RxFrm->UDat.Dat[8], 4);
            if (err != SUCCESS)
            {
                return (DL645B_ERRINFO_PSW);    //当传输的数据MAC 校验错是采用错误信息字ERR 中bit2（密码错/未授权）置位，并按照异常应答帧响应。
            }
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_ChargMoneyPara + 16 + 4 * (RxFrm->UDat.DI0 - 1), &RxFrm->UDat.Dat[8], 0x04);
            break;
        case 0x000502ff:                // 第二套费率值
            if (fnDl645B_FramCheckBCD(&RxFrm->UDat.Dat[8], (RxFrm->Len - 16)) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);    //BCD码判断
            }
            if (((RxFrm->Len - 16) % 4) != 0)
            {
                return (DL645B_ERRINFO_MISC);
            }
            // 读取EEPROM中第1，2套费率

            //          if(Bkgrd.PubData.MtSta.MtSta3.StaBit.CurRatePrice == 1 )
            //          {
            //              fnFile_Read(FileId_RatePara , FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15) , &BufTemp[4 + sizeof(sDF13) * DL645_MAX_FL] , sizeof(sDF13)*DL645_MAX_FL );
            //              fnFile_Read(FileId_RatePara , FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15) + (sizeof(sDF13) * DL645_MAX_FL) , &BufTemp[4] , sizeof(sDF13)*DL645_MAX_FL);
            //          }
            //          else
            //          {
            fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15), &BufTemp[4], sizeof(sDF13)*MAX_FL);
            fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15) + (sizeof(sDF13) * MAX_FL), &BufTemp[4 + sizeof(sDF13) * MAX_FL], sizeof(sDF13)*MAX_FL);
            //          }
            nLadder = (RxFrm->Len - 16) / 4 ;
            for (i = 0; i < nLadder; i++)
            {
                ICEsamComm.Ic_Comm_RxBuf[4 * i] = RxFrm->UDat.Dat[8 + 4 * i + 3];
                ICEsamComm.Ic_Comm_RxBuf[4 * i + 1] = RxFrm->UDat.Dat[8 + 4 * i + 2];
                ICEsamComm.Ic_Comm_RxBuf[4 * i + 2] = RxFrm->UDat.Dat[8 + 4 * i + 1];
                ICEsamComm.Ic_Comm_RxBuf[4 * i + 3] = RxFrm->UDat.Dat[8 + 4 * i];
            }
            Std_Memcpy(&BufTemp[100], &RxFrm->UDat.Dat[8], RxFrm->Len - 16);
            for (i = nLadder; i < 4; i++)
            {
                Std_Memcpy(&BufTemp[100 + 4 * i], &BufTemp[100 + 4 * (nLadder - 1)], 4);
            }
            ICEsamComm.Ic_Comm_RxBuf[RxFrm->Len - 16] = RxFrm->UDat.Dat[RxFrm->Len - 5];
            ICEsamComm.Ic_Comm_RxBuf[RxFrm->Len - 15] = RxFrm->UDat.Dat[RxFrm->Len - 6];
            ICEsamComm.Ic_Comm_RxBuf[RxFrm->Len - 14] = RxFrm->UDat.Dat[RxFrm->Len - 7];
            ICEsamComm.Ic_Comm_RxBuf[RxFrm->Len - 13] = RxFrm->UDat.Dat[RxFrm->Len - 8];

            err = fnICEsam_Update_BackMoneyFile(0x84, 4, &ICEsamComm.Ic_Comm_RxBuf[0], RxFrm->Len - 12);
            if (err != SUCCESS)
            {
                return (DL645B_ERRINFO_PSW);
            }
            //          if(Bkgrd.PubData.MtSta.MtSta3.StaBit.CurRatePrice == 1 )        // 当前运行第二套费率
            //          {
            //              fnFile_Write(FileId_RatePara , FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15) , &BufTemp[100] , 16 );
            //          }
            //          else                // 当前运行第一套费率
            //          {
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_RatePricePara + sizeof(sDF15) + (sizeof(sDF13) * MAX_FL), &BufTemp[100], 16);
            //          }
            fnDl645Event_Operation(EVENT_STYLE_PrgRatePrice, EVENT_OPERATION_START, &RxFrm->UDat.Dat[4], &BufTemp[4]);     // 写费率表编程事件
            Bkgrd.PubData.UpFlStatusFlag = 0x5a;
            break;
        case 0x000605ff:            // 备用套阶梯值，只支持块设
            if (RxFrm->Len < (12 + 8))
            {
                return (DL645B_ERRINFO_MISC);
            }
            if (fnDl645B_FramCheckBCD(&RxFrm->UDat.Dat[8], (RxFrm->Len - 16)) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);    //BCD码判断
            }

            //          {
            fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5, &ICEsamReadBuf.CardPricePara1Buf[36 + 4], 24);
            fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 48, &ICEsamReadBuf.CardPricePara1Buf[36 + 28], 28);
            fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 104, &ICEsamReadBuf.CardPricePara1Buf[36 + 56], 12);
            fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 24, &ICEsamReadBuf.CardPricePara1Buf[36 + 68], 24);
            fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 76, &ICEsamReadBuf.CardPricePara1Buf[36 + 92], 28);
            fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 116, &ICEsamReadBuf.CardPricePara1Buf[36 + 120], 12);
            //          }

            i = (RxFrm->Len - 16) % 4;
            if (i == 0)
            {
                nRmYear = 4;
            }
            else if (i == 3)
            {
                nRmYear = 1;
            }
            else if (i == 2)
            {
                nRmYear = 2;
            }
            else
            {
                nRmYear = 3;
            }
            nLadder = (RxFrm->Len - 16 - nRmYear * 3) / 8;

            for (i = 0; i < nLadder; i++)
            {
                Std_Memcpy(&BufTemp[100 + 4 * i], &RxFrm->UDat.Dat[8 + 4 * i], 4);
            }
            for (i = nLadder; i < 6; i++)
            {
                Std_Memcpy(&BufTemp[100 + 4 * i], &BufTemp[100 + 4 * (nLadder - 1)], 4);
            }

            for (i = 0; i < (nLadder + 1); i++)
            {
                Std_Memcpy(&BufTemp[124 + 4 * i], &RxFrm->UDat.Dat[8 + 4 * nLadder + 4 * i], 4);
            }
            for (i = (nLadder + 1); i < 7; i++)
            {
                Std_Memcpy(&BufTemp[124 + 4 * i], &BufTemp[124 + 4 * nLadder], 4);
            }

            for (i = 0; i < nRmYear; i++)
            {
                Std_Memcpy(&BufTemp[152 + 3 * i], &RxFrm->UDat.Dat[8 + 8 * nLadder + 4 + 3 * i], 3);
            }
            for (i = nRmYear; i < 4; i++)
            {
                Std_Memcpy(&BufTemp[152 + 3 * i], &BufTemp[152 + 3 * (nRmYear - 1)], 3);
            }

            for (i = 0; i < 13; i++)
            {
                ICEsamComm.Ic_Comm_RxBuf[4 * i] = RxFrm->UDat.Dat[8 + 4 * i + 3];
                ICEsamComm.Ic_Comm_RxBuf[4 * i + 1] = RxFrm->UDat.Dat[8 + 4 * i + 2];
                ICEsamComm.Ic_Comm_RxBuf[4 * i + 2] = RxFrm->UDat.Dat[8 + 4 * i + 1];
                ICEsamComm.Ic_Comm_RxBuf[4 * i + 3] = RxFrm->UDat.Dat[8 + 4 * i];
            }
            for (i = 0; i < 4; i++)
            {
                ICEsamComm.Ic_Comm_RxBuf[52 + 3 * i] = RxFrm->UDat.Dat[60 + 3 * i + 2];
                ICEsamComm.Ic_Comm_RxBuf[52 + 3 * i + 1] = RxFrm->UDat.Dat[60 + 3 * i + 1];
                ICEsamComm.Ic_Comm_RxBuf[52 + 3 * i + 2] = RxFrm->UDat.Dat[60 + 3 * i];
            }
            ICEsamComm.Ic_Comm_RxBuf[64] = RxFrm->UDat.Dat[RxFrm->Len - 5];
            ICEsamComm.Ic_Comm_RxBuf[65] = RxFrm->UDat.Dat[RxFrm->Len - 6];
            ICEsamComm.Ic_Comm_RxBuf[66] = RxFrm->UDat.Dat[RxFrm->Len - 7];
            ICEsamComm.Ic_Comm_RxBuf[67] = RxFrm->UDat.Dat[RxFrm->Len - 8];

            err = fnICEsam_Update_BackMoneyFile(0x84, 132, &ICEsamComm.Ic_Comm_RxBuf[0], 68);

            if (err != SUCCESS)
            {
                return (DL645B_ERRINFO_PSW);
            }

            //          {
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + sizeof(sFsEgSh_TypeDef) * MAX_LADDER,  &BufTemp[100], 24);
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 76, &BufTemp[124], 28);
            fnFile_Write(FileId_RatePara, FileItemInfoOffAddr_RatePara_LadderPara + 5 + 116, &BufTemp[152], 12);
            //          }
            fnDl645Event_Operation(EVENT_STYLE_PrgLadderPrice, EVENT_OPERATION_START, &RxFrm->UDat.Dat[4], &ICEsamReadBuf.CardPricePara1Buf[36 + 4]);   // 写阶梯表编程事件
            Bkgrd.PubData.UpFlStatusFlag = 0x5a;
            break;
            #endif
        default:
            return (DL645B_ERRINFO_DATA);
    }
    fnDl645Event_Operation(EVENT_STYLE_PRG, EVENT_OPERATION_RUN, &RxFrm->UDat.Dat[4], &RxFrm->UDat.DI0);
    return (DL645B_ERRINFO_OK);
}

//二类参数设置，密文+MAC设置存储在EEROM中的参数
eDL645B_ErrInfo_TypeDef fnDl645_PutParaVarWithDecipher(sFrmDl645B_TypeDef *RxFrm)
{
    u8  i, tempLen;
    u32 DITemp = 0x0;
    ErrorStatus err;
    #if(METERTYPE ==2)
    u8  OpCodeTemp[4];
    u32 ReturnMoney;
    u32 nReturnMoney;
    #endif

    //  u8  UnConst[6],InConst[6],ImaxConst[6];
    //  u16 tempuc=0,tempud=0;
    //  u32 tempus=0,tempis=0;
    //  u32 tempic=0,tempid=0;
    //  u16 temp,nItem;
    sDF01 OldClock;
    //  eDL645B_ErrInfo_TypeDef     Result;

    if (!Secret.RemoteValid)
    {
        return (DL645B_ERRINFO_PSW);
    }
    if (Secret.nMacErr >= MAX_MACERR)
    {
        return (DL645B_ERRINFO_PSW);
    }
    i = RxFrm->UDat.DI3;
    RxFrm->UDat.DI3 = 0;
    Std_Memcpy(&DITemp, &RxFrm->UDat.DI0, 4);
    RxFrm->UDat.DI3 = i;
    //通过密文+MAC的方式进行数据传输，不需要进行密码验证，也不需要编程键配合使用。
    //68+表号+68+14+L+DI0-DI3+99(98)000000+操作者代码+参数明文+MAC（带MAC的参数密文）+CS+16
    //带MAC写ESAM:      04D682(83,84)+P2+LC+参数+MAC

    //输入到ESAM的参数更新文件来解密，文件号=DI07.B08[2]%5;
    //将密文写入ESAM:   04D689(90,91,92)+00+14+密文(带MAC)
    if (DITemp == 0x00001006)
    {
        i = 0x8c;
        tempLen = RxFrm->Len - 12 - 4;
        err = fnICEsam_Update_ESAM_Bin_Mac(i, 0x00, &RxFrm->UDat.Dat[8], tempLen);
        if (err != SUCCESS)
        {
            return (DL645B_ERRINFO_PSW);
        }
        err = fnICEsam_ReadBinFile(ESAM, i, 0x00, 8);
        if (err != SUCCESS)
        {
            return (DL645B_ERRINFO_PSW);
        }
    }
    else
    {
        i = fnBcdToHex_u8(0x89) + (RxFrm->UDat.DI2 % 5);
        i = fnHexToBcd_u8(i);
        tempLen = RxFrm->Len - 12 - 4;

        err = fnICEsam_Update_ESAM_Bin_Mac(i, 0x00, &RxFrm->UDat.Dat[8], tempLen);
        if (err != SUCCESS)     //当传输的数据MAC 校验错是采用错误信息字ERR 中bit2（密码错/未授权）置位，并按照异常应答帧响应。
        {
            return (DL645B_ERRINFO_PSW);
        }
        err = fnICEsam_ReadBinFile(ESAM, i, 0x00, 1);
        if (err != SUCCESS)
        {
            return (DL645B_ERRINFO_PSW);
        }
        err = fnICEsam_ReadBinFile(ESAM, i, 0x00, ICEsamComm.Ic_Comm_RxBuf[0] + 1);
        if ((err != SUCCESS) || (ICEsamComm.Ic_Comm_RxBuf[ICEsamComm.Ic_Comm_RxPtr - 2] != 0x90) || (ICEsamComm.Ic_Comm_RxBuf[ICEsamComm.Ic_Comm_RxPtr - 1] != 0x00))
        {
            return (DL645B_ERRINFO_PSW);
        }
        if (ICEsamComm.Ic_Comm_RxBuf[1] != RxFrm->UDat.DI3 || ICEsamComm.Ic_Comm_RxBuf[2] != RxFrm->UDat.DI2 || ICEsamComm.Ic_Comm_RxBuf[3] != RxFrm->UDat.DI1
            || ICEsamComm.Ic_Comm_RxBuf[4] != RxFrm->UDat.DI0)
        {
            return (DL645B_ERRINFO_DATA);
        }
        //将密文转换为明文后添入明文数据长度和DI后填入接受数据缓冲区中.
        RxFrm->Len = 8 + ICEsamComm.Ic_Comm_RxBuf[0]; //

        for (i = 0; i < ICEsamComm.Ic_Comm_RxBuf[0] - 4; i++)
        {
            RxFrm->UDat.Dat[8 + i] = ICEsamComm.Ic_Comm_RxBuf[5 + i];
        }
    }
    //if(fnDl645B_FramCheckBCD(&RxFrm->UDat.Dat[8],(ICEsamComm.Ic_Comm_RxBuf[0]-4))== ERROR) return(DL645B_ERRINFO_MISC);
    switch (DITemp)
    {
        case 0x000101:
            fnDl645B_Inverse(&RxFrm->UDat.Dat[8], 4);
            if (RxFrm->Len != (12 + 4))
            {
                return (DL645B_ERRINFO_MISC);
            }
            if (fnDl645B_JudgeClockNoWeek(3, &RxFrm->UDat.Dat[9], 3) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
            if (RxFrm->UDat.Dat[9] > fnGetDay(RxFrm->UDat.Dat[10], RxFrm->UDat.Dat[11]))
            {
                return (DL645B_ERRINFO_MISC);
            }
            OldClock = SysClock;
            SysClock.Day = RxFrm->UDat.Dat[9];
            SysClock.Month = RxFrm->UDat.Dat[10];
            SysClock.Year = RxFrm->UDat.Dat[11];

            if (fnSysClock_Write(&SysClock) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
            fnDl645Event_Operation(EVENT_STYLE_SETCLOCK, EVENT_OPERATION_START, &RxFrm->UDat.Dat[4], (u8 *)&OldClock);

            Bkgrd.PubData.fChange.FlagBit.XiugaiClock = 1;
            fnDl645_CmpFrzTime();
            if ((OldClock.Year != SysClock.Year) || (OldClock.Month != SysClock.Month) || (OldClock.Day != SysClock.Day))
            {
                fnBkgrd_Day_Exec();
            }
            Bkgrd.PubData.UpFlStatusFlag = 0x5a;
            if (SysClock.Day != Bkgrd.PriData.Day)
            {
                Bkgrd.PubData.UpDateTimeFlag |= BKGRD_FCHANGE_DAY;
            }
            if (SysClock.Month != Bkgrd.PriData.Month)
            {
                Bkgrd.PubData.UpDateTimeFlag |= BKGRD_FCHANGE_MONTH;
            }
            Bkgrd.PriData.Day = SysClock.Day;
            Bkgrd.PriData.Month = SysClock.Month;
            break;
        case 0x000102:
            fnDl645B_Inverse(&RxFrm->UDat.Dat[8], 3);
            if (RxFrm->Len != (12 + 3))
            {
                return (DL645B_ERRINFO_MISC);
            }
            if (fnDl645B_JudgeClockNoWeek(0, &RxFrm->UDat.Dat[8], 3) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
            OldClock = SysClock;
            SysClock.Second = RxFrm->UDat.Dat[8];
            SysClock.Minute = RxFrm->UDat.Dat[9];
            SysClock.Hour = RxFrm->UDat.Dat[10];
            Bkgrd.PubData.Second = SysClock.Second;
            if (fnSysClock_Write(&SysClock) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
            fnDl645Event_Operation(EVENT_STYLE_SETCLOCK, EVENT_OPERATION_START, &RxFrm->UDat.Dat[4], (u8 *)&OldClock);

            Bkgrd.PubData.fChange.FlagBit.XiugaiClock = 1;
            fnDl645_CmpFrzTime();
            Bkgrd.PubData.UpFlStatusFlag = 0x5a;
            Bkgrd.PriData.Second = SysClock.Second;
            Bkgrd.PriData.Minute = SysClock.Minute;
            Bkgrd.PriData.Hour = SysClock.Hour;
            break;
        case 0x00010c:                  // 时间块设置
            fnDl645B_Inverse(&RxFrm->UDat.Dat[8], 7);
            if (RxFrm->Len != (12 + 7))
            {
                return (DL645B_ERRINFO_MISC);
            }
            if (fnDl645B_JudgeClockNoWeek(0, &RxFrm->UDat.Dat[8], 3) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
            if (fnDl645B_JudgeClockNoWeek(3, &RxFrm->UDat.Dat[12], 3) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
            if (RxFrm->UDat.Dat[12] > fnGetDay(RxFrm->UDat.Dat[13], RxFrm->UDat.Dat[14]))
            {
                return (DL645B_ERRINFO_MISC);
            }
            OldClock = SysClock;
            SysClock.Second = RxFrm->UDat.Dat[8];
            SysClock.Minute = RxFrm->UDat.Dat[9];
            SysClock.Hour = RxFrm->UDat.Dat[10];
            SysClock.Day = RxFrm->UDat.Dat[12];
            SysClock.Month = RxFrm->UDat.Dat[13];
            SysClock.Year = RxFrm->UDat.Dat[14];

            Bkgrd.PubData.Second = SysClock.Second;
            if (fnSysClock_Write(&SysClock) == ERROR)
            {
                return (DL645B_ERRINFO_MISC);
            }
            fnDl645Event_Operation(EVENT_STYLE_SETCLOCK, EVENT_OPERATION_START, &RxFrm->UDat.Dat[4], (u8 *)&OldClock);

            Bkgrd.PubData.fChange.FlagBit.XiugaiClock = 1;
            fnDl645_CmpFrzTime();
            if ((OldClock.Year != SysClock.Year) || (OldClock.Month != SysClock.Month) || (OldClock.Day != SysClock.Day))
            {
                fnBkgrd_Day_Exec();
            }
            Bkgrd.PubData.UpFlStatusFlag = 0x5a;
            if (SysClock.Day != Bkgrd.PriData.Day)
            {
                Bkgrd.PubData.UpDateTimeFlag |= BKGRD_FCHANGE_DAY;
            }
            if (SysClock.Month != Bkgrd.PriData.Month)
            {
                Bkgrd.PubData.UpDateTimeFlag |= BKGRD_FCHANGE_MONTH;
            }
            Bkgrd.PriData.Second = SysClock.Second;
            Bkgrd.PriData.Minute = SysClock.Minute;
            Bkgrd.PriData.Hour = SysClock.Hour;
            Bkgrd.PriData.Day = SysClock.Day;
            Bkgrd.PriData.Month = SysClock.Month;
            break;
        default:
            break;
    }
    fnDl645Event_Operation(EVENT_STYLE_PRG, EVENT_OPERATION_RUN, &RxFrm->UDat.Dat[4], &RxFrm->UDat.DI0);
    return (DL645B_ERRINFO_OK);
}

// 安全认证处理
eDL645B_SErrInfo_TypeDef fnDl645_SafetyCertification(sFrmDl645B_TypeDef *RxFrm, u8 Seq, u8 *Dst, u16 *Len)
{
    u8  i, k;
    u16 j;
    ErrorStatus result;
    u32 DITemp = 0x0;
    #if(METERTYPE==2)
    sDF12 UserNOTemp;
    #endif
    u32 RechargCountTemp1, RechargCountTemp2;

    if (RxFrm->UDat.DI0 != 0xff)
    {
        return (DL645B_SERRINFO_MISC);
    }
    if (Std_Memcmp(&RxFrm->Addr[0], &RdAddr, 6) == SUCCESS)     // 只有读才支持AA地址
    {
        if (!(RxFrm->UDat.DI2 & 0x80))
        {
            return (DL645B_SERRINFO_MISC);
        }
    }

    i = RxFrm->UDat.DI3;
    RxFrm->UDat.DI3 = 0;
    Std_Memcpy(&DITemp, &RxFrm->UDat.DI0, 4);
    RxFrm->UDat.DI3 = i;
    if ((!Secret.RemoteValid)  && (DITemp != 0x000000FF) && (DITemp != 0x008003FF) && (DITemp != 0x000003FF))
    {
        return (DL645B_SERRINFO_RadiusErr);
    }
    switch (DITemp)
    {
        case 0x008001FF:                            // 数据回抄
            //返回的数据: 8+Le+4字节, [7:0]数据回抄标识; [7+Le:8]返回的数据; [8+Le+3:8+Le]MAC

            //数据回抄命令：采取文件名的方式：
            //81,读取剩余金额和购电次数：
            //回抄剩余金额：04b2010C11+4 字节随机数+04d681000A+8 字节分散因子；
            //回抄购电次数：04b2030C11+4 字节随机数+04d681040A+8 字节分散因子。
            //82—85，读取相应ESAM 二进制文件数据：
            //04b082（83，84，85）+ p2(偏移地址)＋11+4 字节随机数1+04d683+00+LC+8 字节分散因子。
            //LC 是所要读取的明文数据＋MAC+分散因子的总长度，它是1 字节的十六进制数。

            //发送目录选择到ESAM
            if (((RxFrm->UDat.Dat[11] != 0xDF) || (RxFrm->UDat.Dat[10] != 0x01)))
            {
                if ((RxFrm->UDat.Dat[11] != 0x3f) || (RxFrm->UDat.Dat[10] != 0x00))
                {
                    return (DL645B_SERRINFO_MISC);
                }
            }
            if ((RxFrm->UDat.Dat[8] & 0x3F) != 0x01) //除钱包文件以外的其它文件
            {
                //发送：04b082(83,84,86)+p2+11+S4+04D686+P2+LC+8字节分散因子
                //返回：61 XX
                //发送：00C0000008
                //返回：Data+MAC
                result = fnICEsam_ReadBin2BinWithMac(0xB0, (RxFrm->UDat.Dat[8] | 0x80), RxFrm->UDat.Dat[6], RxFrm->UDat.Dat[4]);
                if (result != SUCCESS)
                {
                    return (DL645B_SERRINFO_MISC);
                }
                k = 0;
                for (i = 0; i < 8; i++)
                {
                    Dst[k++] = RxFrm->UDat.Dat[4 + i];
                }

                for (i = 0; i < RxFrm->UDat.Dat[4]; i++)
                {
                    Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[RxFrm->UDat.Dat[4] - 1 - i];
                }

                for (i = 0; i < 4; i++)
                {
                    Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[RxFrm->UDat.Dat[4] + 3 - i];
                }
                *Len = 12 + RxFrm->UDat.Dat[4];
            }
            else    //读取剩余金额和购电次数
            {
                //              if( R_UpdateMoneytimer == 0x00 )
                //              {
                //                  if( Decimal.Status & B0000_0010 )
                //                  {
                //                      Moneybag_Process(); //更新ESAM钱包
                //                      R_UpdateMoneytimer = 15;    //15分钟内，不再更新Esam钱包
                //                  }
                //              }

                //剩余金额(ESAM 内), 4bytes.
                result = fnICEsam_ReadBin2BinWithMac(0xB2, 0x01, 0x0C, 4);
                if (result != SUCCESS)
                {
                    return (DL645B_SERRINFO_MISC);
                }

                k = 0x00;
                for (i = 0; i < 8; i++)
                {
                    Dst[k++] = RxFrm->UDat.Dat[4 + i];
                }
                for (i = 0; i < 4; i++)
                {
                    Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[3 - i];
                }

                for (i = 0; i < 4; i++)
                {
                    Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[7 - i];
                }

                //购电次数（ESAM 内）, 4bytes.
                result = fnICEsam_ReadBin2BinWithMac(0xB2, 0x03, 0x0C, 4);
                if (result != SUCCESS)
                {
                    return (DL645B_SERRINFO_MISC);
                }

                for (i = 0; i < 4; i++)
                {
                    Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[3 - i];
                }

                for (i = 0; i < 4; i++)
                {
                    Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[7 - i];
                }
                *Len = 24;
            }
            break;
        case 0x008002FF:                            // 软件比对
            if (RxFrm->UDat.Dat[4] != 0)
            {
                return (DL645B_SERRINFO_MISC);
            }
            Std_Memcpy(&RechargCountTemp1, &RxFrm->UDat.Dat[6], 4);         // 比对因子起始地址
            Std_Memcpy(&RechargCountTemp2, &RxFrm->UDat.Dat[10], 4);       // 比对数据起始地址
            if (RechargCountTemp1 >= FlashAdMax)
            {
                return (DL645B_SERRINFO_FlashAdErr);
            }
            if (RechargCountTemp2 >= FlashAdMax)
            {
                return (DL645B_SERRINFO_FlashAdErr);
            }
            for (i = 0; i < 16; i++)
            {
                if ((RechargCountTemp1 + i) == 0x1c || (RechargCountTemp1 + i) == 0x1d || (RechargCountTemp1 + i) == 0x1e || (RechargCountTemp1 + i) == 0x1f)
                {
                    BufTemp[i] = 0;
                }
                else
                {
                    ICEsamComm.Ic_Comm_RxBuf[i] = *(Read_Flash + RechargCountTemp1 + i);
                }
                if ((RechargCountTemp1 + i) == FlashAdMax)
                {
                    ICEsamComm.Ic_Comm_RxBuf[i] = 0x80;
                    Std_Memset(&ICEsamComm.Ic_Comm_RxBuf[i + 1], 0x00, (15 - i));
                    break;
                }
            }

            Std_Memset(&ICEsamComm.Ic_Comm_RxBuf[30], 0x00, 16);
            if (Std_Memcmp(&ICEsamComm.Ic_Comm_RxBuf[0], &ICEsamComm.Ic_Comm_RxBuf[30], 16) == SUCCESS)
            {
                return (DL645B_SERRINFO_FlashAdErr);
            }
            Std_Memset(&ICEsamComm.Ic_Comm_RxBuf[30], 0xff, 16);
            if (Std_Memcmp(&ICEsamComm.Ic_Comm_RxBuf[0], &ICEsamComm.Ic_Comm_RxBuf[30], 16) == SUCCESS)
            {
                return (DL645B_SERRINFO_FlashAdErr);
            }
            for (i = 0; i < 8; i++)
            {
                ICEsamComm.Ic_Comm_RxBuf[i] ^= ICEsamComm.Ic_Comm_RxBuf[8 + i];
            }
            result = fnICEsam_Auth_In_Out(0xfa, ESAM, RxFrm->UDat.Dat[5], &ICEsamComm.Ic_Comm_RxBuf[0]);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            for (j = 0; j < 256; j++)
            {
                if ((RechargCountTemp2 + j) == 0x1c || (RechargCountTemp2 + j) == 0x1d || (RechargCountTemp2 + j) == 0x1e || (RechargCountTemp2 + j) == 0x1f)
                {
                    BufTemp[j] = 0;
                }
                else
                {
                    BufTemp[j] = *(Read_Flash + RechargCountTemp2 + j);
                }
                if ((RechargCountTemp2 + j) >= FlashAdMax)
                {
                    BufTemp[j] = 0x80;
                    Std_Memset(&BufTemp[j + 1], 0x00, (255 - j));
                    break;
                }
            }
            for (i = 0; i < 64; i++)
            {
                BufTemp[i] = BufTemp[i] ^ BufTemp[64 + i] ^ BufTemp[128 + i] ^ BufTemp[192 + i];
            }
            fnICEsam_RxTxCommhead(0x80, 0xfa, 0x01, 0x00, 0x40);
            Std_Memcpy(&ICEsamComm.Ic_Comm_TxBuf[5], &BufTemp[0], 64);
            result = fnICEsam_CardTxRxFrame(ESAM, 0x40, 0x00);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            result = fnICEsam_Read_Kx(ESAM, 64);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            Std_Memcpy(Dst, &ICEsamComm.Ic_Comm_RxBuf[0], 64);
            fnDl645B_Inverse(Dst, 64);
            *Len = 64;
            break;
        case 0x008003ff:                            // 红外认证查询
            if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
            {
                return (DL645B_SERRINFO_MISC);
            }
            #if(SPI_ESAM)
            ENABLE_ESAM();
            #else
            CardFoutOpen();
            #endif
            result = fnICEsam_EsamReset();          //Esam Reset
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            fnDl645B_Inverse(&RxFrm->UDat.Dat[4], 8);
            Std_Memcpy(&BufTemp[0], &RxFrm->UDat.Dat[4], 8);
            Secret.RemoteValid = 0;
            Secret.tIRDly = 0;              // 身份认证失效
            result = fnICEsam_ReadBinFile(ESAM, 0x99, 0x01, 0x08);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            k = 0x06;
            for (i = 0; i < 8; i++)
            {
                Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[7 - i];
            }
            result = fnICEsam_ReadBinFile(ESAM, 0x82, 30, 0x06);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            //          // 测试密钥表号固定为1
            //          if(!Bkgrd.PubData.CipherKeyFlag) ICEsamComm.Ic_Comm_RxBuf[5] = 0x01;
            Std_Memcpy(Dst, &ICEsamComm.Ic_Comm_RxBuf[0], 0x06);
            Std_Memcpy(&ICEsamComm.Ic_Comm_RxBuf[2], Dst, 0x06);
            Std_Memset(&ICEsamComm.Ic_Comm_RxBuf[0], 0x00, 2);
            k = 0x00;
            for (i = 0; i < 6; i++)
            {
                Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[7 - i];
            }

            result = fnICEsam_Auth_In_Out(0xfa, ESAM, 0x03, &ICEsamComm.Ic_Comm_RxBuf[0]);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            result = fnICEsam_Auth_In_Out(0xfa, ESAM, 0x00, &BufTemp[0]);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }

            result = fnICEsam_Read_Kx(ESAM, 0x08);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            k = 14;
            for (i = 0; i < 8; i++)
            {
                Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[7 - i];
            }
            result = fnICEsam_ReadRandom(ESAM, 8);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            for (i = 0; i < 8; i++)
            {
                Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[7 - i];
            }
            *Len = 30;
            break;
        case 0x008102FF:                            // 状态查询
            if (!Bkgrd.PubData.RUpdateMoneyFlag)
            {
                fnICEsam_MoneyProc();   //更新esam钱包
                EgMoney.PubPara.tSubEsamMoney = 15; //15分钟内，不再更新Esam钱包
                Bkgrd.PubData.RUpdateMoneyFlag = 0x5a;
            }
            //剩余金额(ESAM 内), 4bytes.
            result = fnICEsam_ReadMoneyBagWithMac(0xB2, 0x01, 0x0C, 4);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }

            k = 0x00;
            for (i = 0; i < 4; i++)
            {
                Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[3 - i];
            }

            for (i = 0; i < 4; i++)
            {
                Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[7 - i];
            }

            //购电次数（ESAM 内）, 4bytes.
            result = fnICEsam_ReadMoneyBagWithMac(0xB2, 0x03, 0x0C, 4);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }

            for (i = 0; i < 4; i++)
            {
                Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[3 - i];
            }

            for (i = 0; i < 4; i++)
            {
                Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[7 - i];
            }

            //客户编号, 6bytes
            result = fnICEsam_ReadBin2BinWithMac(0xB0, 0x82, 36, 6);    //客户编号
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }

            for (i = 0; i < 6; i++)
            {
                Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[5 - i];
            }

            //密钥信息, 4bytes.
            fnFile_Read(FileId_ParaCipherKey, FileItemInfoOffAddr_CipherKeyPara_CipherKeyFlag, &ICEsamComm.Ic_Comm_RxBuf[0], 4);
            //          result = fnICEsam_ReadBin2BinWithMac( 0xB0, 0x87, 35, 4 );
            //          if( result != SUCCESS ) return(DL645B_SERRINFO_MISC);

            Std_Memcpy(&Dst[k], ICEsamComm.Ic_Comm_RxBuf, 0x04);
            //          for( i=0; i<4; i++ )
            //          {
            //              Dst[ k++ ] = ICEsamComm.Ic_Comm_RxBuf[i];
            //          }
            *Len = 26;
            break;
        case 0x000000FF:                            // 身份认证密文1+随机数1+分散因子
            #if(SPI_ESAM)
            ENABLE_ESAM();
            #else
            CardFoutOpen();
            #endif
            result = fnICEsam_EsamReset();          //Esam Reset
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }

            Std_Memcpy(ICEsamComm.EsamRst8B, &ICEsamComm.Ic_Comm_RxBuf[5], 8);   //ESAM序列号, 8bytes.

            fnDl645B_Inverse(&RxFrm->UDat.Dat[4], 8);   //密文1
            fnDl645B_Inverse(&RxFrm->UDat.Dat[12], 8);      //随机数1
            fnDl645B_Inverse(&RxFrm->UDat.Dat[20], 8);      //分散因子

            //result = fnICEsam_SelectFile( ESAM , 0x3F, 0x00 );
            //if( result != SUCCESS ) return(DL645B_SERRINFO_MISC);

            result = fnICEsam_ReadBinFile(ESAM, 0x82, 30, 0x06);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            if ((RxFrm->UDat.Dat[20] != 0x00) || (RxFrm->UDat.Dat[21] != 0x00))
            {
                return (DL645B_SERRINFO_MISC);
            }
            if (Std_Memcmp(&ICEsamComm.Ic_Comm_RxBuf[0], &RxFrm->UDat.Dat[22], 0x06) == ERROR)
            {
                return (DL645B_SERRINFO_MISC);    //表号不相等
            }

            result = fnICEsam_Authorization(&RxFrm->UDat.Dat[4]);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_RadiusErr);
            }
            Std_Memcpy(ICEsamComm.PcRand,  &RxFrm->UDat.Dat[12], 8);    //随机数, 8bytes
            Std_Memcpy(ICEsamComm.PcRst8B, &RxFrm->UDat.Dat[20], 8);    //分散因子, 8bytes
            Secret.RemoteValid = 1;
            //返回信息: 随机数2+ESAM序列号
            for (i = 0; i < 4; i++)
            {
                Dst[i] = ICEsamComm.Ic_Comm_RxBuf[3 - i];
            }
            result = fnICEsam_ReadBinFile(ESAM, 0x99, 0x01, 8);
            if (result == SUCCESS)
            {
                Std_Memcpy(ICEsamComm.EsamRst8B, &ICEsamComm.Ic_Comm_RxBuf[0], 8);    //ESAM序列号, 8bytes.
            }
            for (i = 0; i < 8; i++)
            {
                Dst[4 + i] = ICEsamComm.EsamRst8B[7 - i];
            }
            result = fnICEsam_ReadBinFile(ESAM, 0x82, 43, 2);
            if (result == ERROR)
            {
                fnICEsam_ReadBinFile(ESAM, 0x82, 43, 2);
            }
            //          Secret.PubData.tRemote = ((u16)ICEsamComm.Ic_Comm_RxBuf[0]<<8) + ICEsamComm.Ic_Comm_RxBuf[1];
            //          Secret.PubData.tRemoteDec = fnBcdToHex_u16(Secret.tRemote);
            *Len = 12;
            //fnFile_Read(Dl645FileId_MiscEv , Dl645FileItemInfoOffAddr_MiscEv_Prg , &i , 1);
            if (i & 0x80)
            {
                fnDl645Event_Operation(EVENT_STYLE_PRG, EVENT_OPERATION_END, 0, 0);
            }
            break;
        case 0x000001FF:                            // 身份认证时效设置
            if (Secret.nMacErr >= MAX_MACERR)
            {
                return (DL645B_SERRINFO_RemoteClose);
            }
            if (fnDl645B_FramCheckBCD(&RxFrm->UDat.Dat[4], 2) == ERROR)
            {
                return (DL645B_SERRINFO_MISC);
            }
            if ((RxFrm->UDat.Dat[4] == 0) && (RxFrm->UDat.Dat[5] == 0))
            {
                return (DL645B_SERRINFO_MISC);
            }
            result = fnICEsam_Update_ESAM_Bin_Mac(0x82, 43, &RxFrm->UDat.Dat[4], 2);
            if (result == ERROR)
            {
                return (DL645B_SERRINFO_VerifyErr);
            }
            result = fnICEsam_ReadBinFile(ESAM, 0x82, 43, 2);
            if (result == ERROR)
            {
                fnICEsam_ReadBinFile(ESAM, 0x82, 43, 2);
            }
            //          Secret.PubData.tRemote = ((u16)ICEsamComm.Ic_Comm_RxBuf[0]<<8) + ICEsamComm.Ic_Comm_RxBuf[1];
            //          Secret.PubData.tRemoteDec = fnBcdToHex_u16(Secret.tRemote);
            fnDl645Event_Operation(EVENT_STYLE_PRG, EVENT_OPERATION_RUN, &RxFrm->UDat.Dat[0], &RxFrm->UDat.DI0);
            *Len = 0;
            break;
        case 0x000002FF:                            // 身份认证失效
            //客户编号, 6bytes
            result = fnICEsam_ReadBin2BinWithMac(0xB0, 0x82, 36, 6);    //客户编号
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            k = 0x00;
            for (i = 0; i < 6; i++)
            {
                Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[5 - i];
            }
            //剩余金额(ESAM 内), 4bytes.
            result = fnICEsam_ReadRecFile(ESAM, 0x01, 0x0C, 4);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }

            for (i = 0; i < 4; i++)
            {
                Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[3 - i];
            }

            //购电次数（ESAM 内）, 4bytes.
            result = fnICEsam_ReadRecFile(ESAM, 0x03, 0x0C, 4);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }

            for (i = 0; i < 4; i++)
            {
                Dst[k++] = ICEsamComm.Ic_Comm_RxBuf[3 - i];
            }

            //密钥信息, 4bytes.

            //密钥信息, 4bytes.
            fnFile_Read(FileId_ParaCipherKey, FileItemInfoOffAddr_CipherKeyPara_CipherKeyFlag, &ICEsamComm.Ic_Comm_RxBuf[0], 4);
            Std_Memcpy(&Dst[k], ICEsamComm.Ic_Comm_RxBuf, 0x04);
            *Len = 18;
            Secret.RemoteValid = 0;
            //          Secret.PubData.tRemoteDec = 0;
            fnICEsam_EsamReset();
            break;
        case 0x000003ff:                    // 红外认证指令
            if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
            {
                return (DL645B_SERRINFO_MISC);
            }
            fnDl645B_Inverse(&RxFrm->UDat.Dat[4], 8);
            result = fnICEsam_HW_RemoteAuth(&RxFrm->UDat.Dat[4]);
            /*
            if( result != SUCCESS )
            {
                Secret.HWPrgFlag =0;        // 红外认证指令出现错误，上次认证无效
                Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable = 0;
                Secret.tHWPrgDec = 0;
                return(DL645B_SERRINFO_MISC);
            }
            Secret.HWPrgFlag = 1;
            fnFile_Read(FileId_HighPara , FileItemInfoOffAddr_HighPara_tIRPrg , &Secret.tHWPrgDec , 1);
            if(!Secret.tHWPrgDec) Secret.tHWPrgDec= 30;
            else Secret.tHWPrgDec = fnBcdToHex_u8(Secret.tHWPrgDec);
            Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable = 1;
            */
            break;
        case 0x000004ff:                    //明文写信息文件
        case 0x000005ff:                    // 密文写信息文件
            if (Secret.nMacErr >= MAX_MACERR)
            {
                return (DL645B_SERRINFO_RemoteClose);
            }
            result = fnICEsam_SelectFile(ESAM, 0x00, RxFrm->UDat.Dat[4]);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            if ((RxFrm->UDat.Dat[4] < 0x01) || (RxFrm->UDat.Dat[4] > 0x20))
            {
                return (DL645B_SERRINFO_MISC);
            }
            fnDl645B_Inverse(&RxFrm->UDat.Dat[7], RxFrm->Len - 15);
            fnDl645B_Inverse(&RxFrm->UDat.Dat[7 + RxFrm->Len - 15], 4);
            Std_Memcpy(ICEsamComm.Ic_Comm_RxBuf, &RxFrm->UDat.Dat[7], RxFrm->Len - 11);
            result = fnICEsam_WriteBinWithMac(ESAM, RxFrm->UDat.Dat[6], RxFrm->UDat.Dat[5], RxFrm->Len - 11);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            fnDl645Event_Operation(EVENT_STYLE_PRG, EVENT_OPERATION_RUN, &RxFrm->UDat.Dat[0], &RxFrm->UDat.DI0);
            break;
            #if(METERTYPE == 2)                             //本地费控表
        case 0x000101FF:                            // 开户
        case 0x000102FF:                            // 充值
            //开户时，不需验证客户编号，将客户编号写到ESAM 中
            //充值时，先比对客户编号是否相同，在写入ESAM中
            if (Secret.nMacErr >= MAX_MACERR)
            {
                return (DL645B_SERRINFO_RemoteClose);
            }
            if (!Bkgrd.PubData.CipherKeyFlag)
            {
                return (DL645B_SERRINFO_MISC);
            }
            //购电次数（ESAM 内）, 4bytes.
            result = fnICEsam_ReadRecFile(ESAM, 0x03, 0x0C, 4);
            if (result != SUCCESS)
            {
                return (DL645B_SERRINFO_MISC);
            }
            fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[0], 4);
            Std_Memcpy(&RechargCountTemp1, &ICEsamComm.Ic_Comm_RxBuf[0], 0x04);
            Std_Memcpy(&RechargCountTemp2, &RxFrm->UDat.Dat[8], 0x04);   // 购电次数
            if (RxFrm->UDat.DI1 == 0x01)        // 开户
            {
                if (fnDl645B_FramCheckBCD(&RxFrm->UDat.Dat[16], 6) == ERROR)
                {
                    return (DL645B_SERRINFO_MISC);
                }
                //开户的充值次数必须为0或1
                if (RechargCountTemp1 > 1)
                {
                    return (DL645B_SERRINFO_RechargCountErr);
                }
                if (RechargCountTemp2 > 1)
                {
                    return (DL645B_SERRINFO_RechargCountErr);
                }
            }
            else
            {
                // 未开户，充值失败
                if ((Bkgrd.PubData.MtSta.MtSta3.Sta & 0xc000) == 0xc000)
                {
                    return (DL645B_SERRINFO_MISC);
                }
            }
            Std_Memcpy(&RechargCountTemp2, &RxFrm->UDat.Dat[8], 0x04);   // 购电次数
            if ((RxFrm->UDat.DI1 == 0x02) || ((Bkgrd.PubData.MtSta.MtSta3.Sta & 0xc000) != 0xc000))                         // 充值
            {
                //客户编号, 6bytes
                fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_UserNo, (u8 *)&UserNOTemp, 6);       //读客户编号
                if (Std_Memcmp((u8 *)&UserNOTemp, &RxFrm->UDat.Dat[16], 0x06) == ERROR)
                {
                    return (DL645B_SERRINFO_UserNoErr);
                }
                //if((RechargCountTemp1 ==0)&&(RxFrm->UDat.DI1 == 0x02)) return(DL645B_SERRINFO_MISC);
                // 客户编号相等，判断客户编号的MAC是否正确
                result = fnICEsam_Update_ESAM_Bin_Mac(0x82, 36, &RxFrm->UDat.Dat[16], 6);
                if (result != SUCCESS)
                {
                    return (DL645B_SERRINFO_MISC);
                }
            }
            if (RxFrm->UDat.DI1 == 0x02)
            {
                if (RechargCountTemp2 == RechargCountTemp1)
                {
                    return (DL645B_SERRINFO_RepRecharg);
                }
                if (((RechargCountTemp2 - RechargCountTemp1) != 1))
                {
                    return (DL645B_SERRINFO_RechargCountErr);
                }
            }
            else
            {
                if (RechargCountTemp2 == RechargCountTemp1) // 置远程开户状态，并返回
                {
                    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_LocalOpenFlag, &i, 1);
                    i |= 0x80;
                    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_LocalOpenFlag, &i, 1);
                    Bkgrd.PubData.MtSta.MtSta3.StaBit.RemoteOpen = 0;

                    result = fnICEsam_Update_ESAM_Bin_Mac(0x82, 36, &RxFrm->UDat.Dat[16], 6);
                    if (result != SUCCESS)
                    {
                        return (DL645B_SERRINFO_VerifyErr);
                    }
                    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[5], 6);
                    fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_UserNo, &ICEsamComm.Ic_Comm_TxBuf[5], 6);       //写客户编号
                    fnICEsam_UpdateRunFile();
                    return (DL645B_SERRINFO_OK);
                }
                else if (((RechargCountTemp2 - RechargCountTemp1) != 1))
                {
                    return (DL645B_SERRINFO_RechargCountErr);
                }
            }
            Std_Memcpy(&RechargCountTemp1, &RxFrm->UDat.Dat[4], 0x04);          // 购电金额
            if (fnICEsam_JugeRegrate(RechargCountTemp1) == ERROR)
            {
                return (DL645B_SERRINFO_RegrateErr);
            }

            if (fnIcEsam_AddMoney(0, &RxFrm->UDat.Dat[4]) == ERROR)
            {
                return (DL645B_SERRINFO_VerifyErr);
            }
            if ((RxFrm->UDat.DI1 == 0x01) && (EgMoney.PubPara.nALLBuyMoney <= 1))       // 开户
            {
                result = fnICEsam_Update_ESAM_Bin_Mac(0x82, 36, &RxFrm->UDat.Dat[16], 6);
                if (result != SUCCESS)
                {
                    return (DL645B_SERRINFO_VerifyErr);
                }
                fnDl645B_Inverse(&ICEsamComm.Ic_Comm_TxBuf[5], 6);
                fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_UserNo, &ICEsamComm.Ic_Comm_TxBuf[5], 6);       //写客户编号
            }
            fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_LocalOpenFlag, &i, 1);
            i |= 0x80;
            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_LocalOpenFlag, &i, 1);
            Bkgrd.PubData.MtSta.MtSta3.StaBit.RemoteOpen = 0;
            fnICEsam_UpdateRunFile();
            fnDl645Event_Operation(EVENT_STYLE_PRG, EVENT_OPERATION_RUN, &RxFrm->UDat.Dat[0], &RxFrm->UDat.DI0);
            break;
        case 0x000103ff:                            // 钱包初始化命令
            //清剩余和透支金额
            if (Secret.nMacErr >= MAX_MACERR)
            {
                return (DL645B_SERRINFO_RemoteClose);
            }
            if (Bkgrd.PubData.CipherKeyFlag)
            {
                return (DL645B_SERRINFO_MISC);    //正式密钥不允许
            }
            if ((RxFrm->UDat.Dat[12] != 0) || (RxFrm->UDat.Dat[13] != 0) || (RxFrm->UDat.Dat[14] != 0) || (RxFrm->UDat.Dat[15] != 0))
            {
                return (DL645B_SERRINFO_MISC);
            }
            fnWDT_Restart();
            fnDl645B_Inverse(&RxFrm->UDat.Dat[4], 4);
            fnDl645B_Inverse(&RxFrm->UDat.Dat[8], 4);
            fnDl645B_Inverse(&RxFrm->UDat.Dat[12], 4);
            fnDl645B_Inverse(&RxFrm->UDat.Dat[16], 4);
            Std_Memcpy(&ICEsamReadBuf.CardMoneyBag[0], &RxFrm->UDat.Dat[4], 16);
            result = fnICEsam_RemoteMoneyBagInit();
            if (result == ERROR)
            {
                return (DL645B_SERRINFO_MISC);
            }
            fnDl645Event_Operation(EVENT_STYLE_CLR, EVENT_OPERATION_START, &RxFrm->UDat.Dat[0], 0);
            Bkgrd.PubData.MoneySta.RemoteAlarm = 0;
            Bkgrd.PubData.MtSta.MtSta3.StaBit.PreGateOff = 0;
            //Bkgrd.PubData.MoneySta.RemoteKeepEg = 0;

            //          Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
            //          ICEsamComm.Ic_Comm_RxBuf[0] |=0x80;
            //          fnFile_Write(Dl645FileId_GeneralPara, Dl645FileItemInfoOffAddr_GeneralPara_Record + 28 , &ICEsamComm.Ic_Comm_RxBuf[0] , 1 );//合闸允许状态保存
            fnDl645B_Inverse(&RxFrm->UDat.Dat[4], 4);
            Std_Memcpy(&RechargCountTemp1, &RxFrm->UDat.Dat[4], 4);
            RechargCountTemp1 = fnHexToBcd_u32(RechargCountTemp1);          // 购电金额
            Std_Memcpy(&RxFrm->UDat.Dat[4], &RechargCountTemp1, 4);
            fnDl645B_Inverse(&RxFrm->UDat.Dat[12], 4);
            Std_Memcpy(&RxFrm->UDat.Dat[8], &RxFrm->UDat.Dat[12], 4);
            Std_Memset(&RxFrm->UDat.Dat[12], 0x00, 4);
            Std_Memcpy(&RxFrm->UDat.Dat[16], &RxFrm->UDat.Dat[4], 4);
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_EgMoney + 38, &RxFrm->UDat.Dat[12], 4);      // 初始金额设置为0
            fnDl645Event_Operation(EVENT_STYLE_BUYMONEY, EVENT_OPERATION_START, 0, &RxFrm->UDat.Dat[4]);
            break;
            #endif
        case 0x000301ff:                            // 密钥更新
            fnFile_Read(FileId_ParaCipherKey, FileItemInfoOffAddr_CipherKeyPara_nCipherKey, &i, 1);
            if ((RxFrm->Len - 12) % 36)
            {
                return (DL645B_SERRINFO_MISC);
            }
            //i = fnBcdToHex_u8(i);
            j = (RxFrm->Len - 12) / 36;
            k = RxFrm->UDat.Dat[4 + 32];
            for (; j > 0; j--)
            {
                fnDl645B_Inverse(&RxFrm->UDat.Dat[4 + 36 * (j - 1)], 36);
                if (i != RxFrm->UDat.Dat[4 + 36 * (j - 1)])
                {
                    return (DL645B_SERRINFO_MISC);    // 判断密钥总条数
                }
                if (k != RxFrm->UDat.Dat[7 + 36 * (j - 1)])
                {
                    return (DL645B_SERRINFO_MISC);    // 判断密钥状态位
                }
            }
            if (fnICEsam_ReadBinFile(ESAM, 0x82, 30, 0x06) == ERROR)
            {
                return (DL645B_SERRINFO_MISC);
            }

            Std_Memcpy(&BufTemp[0], &ICEsamComm.Ic_Comm_RxBuf[0], 6);
            Std_Memcpy(&ICEsamComm.Ic_Comm_RxBuf[2], &BufTemp[0], 6);
            ICEsamComm.Ic_Comm_RxBuf[0] = 0x00;
            ICEsamComm.Ic_Comm_RxBuf[1] = 0x00;
            //          // 测试密钥下表号固定使用01
            //          if(!Bkgrd.PubData.CipherKeyFlag) {Std_Memset(&ICEsamComm.Ic_Comm_RxBuf[2] , 0x00 , 6);ICEsamComm.Ic_Comm_RxBuf[7] = 0x01;}
            j = 40;
            Std_Memcpy(&ICEsamComm.Ic_Comm_RxBuf[8], &RxFrm->UDat.Dat[4], 36);
            while (j < (RxFrm->Len - 8))
            {
                for (i = 0; i < 36; i++)
                {
                    ICEsamComm.Ic_Comm_RxBuf[8 + i] ^= RxFrm->UDat.Dat[j++];
                }
            }
            fnDl645B_Inverse(&RxFrm->UDat.Dat[RxFrm->Len - 8], 4);
            Std_Memcpy(&ICEsamComm.Ic_Comm_RxBuf[44], &RxFrm->UDat.Dat[RxFrm->Len - 8], 4);
            result = fnICEsam_VerifyUpdatePSW(&ICEsamComm.Ic_Comm_RxBuf[0], 0x30);
            if (result == ERROR)
            {
                return (DL645B_SERRINFO_MISC);
            }
            // 保存密钥
            j = 0;
            fnFile_Read(FileId_ParaCipherKey, FileItemInfoOffAddr_CipherKeyPara_nCipherKeyEE, &RechargCountTemp1, 4);
            fnFile_Read(FileId_ParaCipherKey, FileItemInfoOffAddr_CipherKeyPara_CipherKeyWriteFlag, &RechargCountTemp2, 4);
            while (j < (RxFrm->Len - 12))
            {
                fnFile_Write(FileId_ParaCipherKey, FileItemInfoOffAddr_CipherKeyPara_CipherKey + RxFrm->UDat.Dat[6 + j] * 32, &RxFrm->UDat.Dat[j + 4 + 4], 32);
                RechargCountTemp1 |= (1 << (RxFrm->UDat.Dat[6 + j]));
                if (RxFrm->UDat.Dat[j + 4 + 3])
                {
                    RechargCountTemp2 |= (1 << (RxFrm->UDat.Dat[6 + j]));
                }
                else
                {
                    RechargCountTemp2 &= ~(1 << (RxFrm->UDat.Dat[6 + j]));
                };
                j += 36;
            }
            if (RxFrm->UDat.Dat[6] == 0x00)
            {
                fnFile_Write(FileId_ParaCipherKey, FileItemInfoOffAddr_CipherKeyPara_OpCode, &RxFrm->UDat.Dat[0], 4);
            }
            fnFile_Write(FileId_ParaCipherKey, FileItemInfoOffAddr_CipherKeyPara_nCipherKeyEE, &RechargCountTemp1, 4);
            fnFile_Write(FileId_ParaCipherKey, FileItemInfoOffAddr_CipherKeyPara_CipherKeyWriteFlag, &RechargCountTemp2, 4);
            fnFile_Read(FileId_ParaCipherKey, FileItemInfoOffAddr_CipherKeyPara_nCipherKey, &i, 1);

            fnDl645Event_Operation(EVENT_STYLE_PRG, EVENT_OPERATION_RUN, &RxFrm->UDat.Dat[0], &RxFrm->UDat.DI0);
            break;
        default:
            return (DL645B_SERRINFO_MISC);
    }
    return (DL645B_SERRINFO_OK);
}

/*****************************************************************************
** Function name:fnDl645_ReadCurve
**
** Description:负荷曲线增补协议，读取连续曲线数据
**
** Parameters:
**
** Returned value:
**
******************************************************************************/
eDL645B_ErrInfo_TypeDef fnDl645_ReadCurve(sFrmDl645B_TypeDef *RxFrm, u8 Seq, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

// 读取负荷曲线
eDL645B_ErrInfo_TypeDef fnDl645_ReadProfile(sFrmDl645B_TypeDef *RxFrm, u8 Seq, u8 *Dst, u16 *Len)
{
    return (DL645B_ERRINFO_OK);
}

#if(nPhs==ThreePhs)
const u8    FirmDataLen[] =
{
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    3,
    3,
    3,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    4,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    3,
    3,
    3,
};

const sFirmPara_TypeDef FirmPara[] =
{
    {   0x0100,   0x02,   FileItemInfoOffAddr_FirmPara_HFConst1   },
    {   0x0102,   0x02,   FileItemInfoOffAddr_FirmPara_Start_Ps   },
    {   0x0103,   0x02,   FileItemInfoOffAddr_FirmPara_Start_Q    },
    {   0x0104,   0x02,   FileItemInfoOffAddr_FirmPara_ELostVoltT     },
    {   0x0105,   0x02,   FileItemInfoOffAddr_FirmPara_Zxot   },
    {   0x0106,   0x02,   FileItemInfoOffAddr_FirmPara_PRth   },
    {   0x0107,   0x02,   FileItemInfoOffAddr_FirmPara_PRth + 2 },
    {   0x0108,   0x02,   FileItemInfoOffAddr_FirmPara_PRth + 4 },
    {   0x0109,   0x02,   FileItemInfoOffAddr_FirmPara_PRth + 6 },
    {   0x010f,   0x03,   FileItemInfoOffAddr_FirmPara_PHSI },
    {   0x0110,   0x03,   FileItemInfoOffAddr_FirmPara_PHSI + 4 },
    {   0x0111,   0x03,   FileItemInfoOffAddr_FirmPara_PHSI + 8 },
    {   0x0113,   0x02,   FileItemInfoOffAddr_FirmPara_GSU    },
    {   0x0114,   0x02,   FileItemInfoOffAddr_FirmPara_GSU + 2  },
    {   0x0115,   0x02,   FileItemInfoOffAddr_FirmPara_GSU + 4  },
    {   0x0116,   0x02,   FileItemInfoOffAddr_FirmPara_GSI    },
    {   0x0117,   0x02,   FileItemInfoOffAddr_FirmPara_GSI + 2  },
    {   0x0118,   0x02,   FileItemInfoOffAddr_FirmPara_GSI + 4  },
    {   0x0119,   0x02,   FileItemInfoOffAddr_FirmPara_GSI + 6 },
    {   0x0121,   0x02,   FileItemInfoOffAddr_FirmPara_U_OS   },
    {   0x0122,   0x02,   FileItemInfoOffAddr_FirmPara_U_OS + 2     },
    {   0x0123,   0x02,   FileItemInfoOffAddr_FirmPara_U_OS + 4     },
    {   0x0124,   0x02,   FileItemInfoOffAddr_FirmPara_I_OS   },
    {   0x0125,   0x02,   FileItemInfoOffAddr_FirmPara_I_OS + 2     },
    {   0x0126,   0x02,   FileItemInfoOffAddr_FirmPara_I_OS + 4     },
    {   0x0128,   0x02,   FileItemInfoOffAddr_FirmPara_GP     },
    {   0x0129,   0x02,   FileItemInfoOffAddr_FirmPara_GP + 2   },
    {   0x012a,   0x02,   FileItemInfoOffAddr_FirmPara_GP + 4   },
    {   0x012b,   0x02,   FileItemInfoOffAddr_FirmPara_GQ     },
    {   0x012c,   0x02,   FileItemInfoOffAddr_FirmPara_GQ + 2   },
    {   0x012d,   0x02,   FileItemInfoOffAddr_FirmPara_GQ + 4 },
    {   0x012e,   0x02,   FileItemInfoOffAddr_FirmPara_GS     },
    {   0x012f,   0x02,   FileItemInfoOffAddr_FirmPara_GS + 2   },
    {   0x0130,   0x02,   FileItemInfoOffAddr_FirmPara_GS + 4 },
    {   0x0131,   0x02,   FileItemInfoOffAddr_FirmPara_P_PHS  },
    {   0x0132,   0x02,   FileItemInfoOffAddr_FirmPara_P_PHS + 2    },
    {   0x0133,   0x02,   FileItemInfoOffAddr_FirmPara_P_PHS + 4 },
    {   0x0134,   0x02,   FileItemInfoOffAddr_FirmPara_Q_PHS  },
    {   0x0135,   0x02,   FileItemInfoOffAddr_FirmPara_Q_PHS + 2    },
    {   0x0136,   0x02,   FileItemInfoOffAddr_FirmPara_Q_PHS + 4 },
    {   0x0137,   0x02,   FileItemInfoOffAddr_FirmPara_P_OS   },
    {   0x0138,   0x02,   FileItemInfoOffAddr_FirmPara_P_OS + 2     },
    {   0x0139,   0x02,   FileItemInfoOffAddr_FirmPara_P_OS + 4 },
    {   0x013a,   0x02,   FileItemInfoOffAddr_FirmPara_Q_OS   },
    {   0x013b,   0x02,   FileItemInfoOffAddr_FirmPara_Q_OS + 2     },
    {   0x013c,   0x02,   FileItemInfoOffAddr_FirmPara_Q_OS + 4 },
    {   0x01b0,   0x03,   FileItemInfoOffAddr_FirmPara_P_PHSMH },
    {   0x01b1,   0x03,   FileItemInfoOffAddr_FirmPara_P_PHSMH + 4  },
    {   0x01b2,   0x03,   FileItemInfoOffAddr_FirmPara_P_PHSMH + 8  },
    {   0x01b3,   0x03,   FileItemInfoOffAddr_FirmPara_P_PHSMH + 12 },
    {   0x01b4,   0x03,   FileItemInfoOffAddr_FirmPara_P_PHSMH + 16     },
    {   0x01b5,   0x03,   FileItemInfoOffAddr_FirmPara_P_PHSMH + 20     },
    {   0x01b6,   0x03,   FileItemInfoOffAddr_FirmPara_Q_PHSMH        },
    {   0x01b7,   0x03,   FileItemInfoOffAddr_FirmPara_Q_PHSMH + 4  },
    {   0x01b8,   0x03,   FileItemInfoOffAddr_FirmPara_Q_PHSMH + 8  },
    {   0x01b9,   0x03,   FileItemInfoOffAddr_FirmPara_Q_PHSMH + 12     },
    {   0x01ba,   0x03,   FileItemInfoOffAddr_FirmPara_Q_PHSMH + 16     },
    {   0x01bb,   0x03,   FileItemInfoOffAddr_FirmPara_Q_PHSMH + 20     },
};
#endif

// dyf 新增设置南瑞中天参数
eDL645B_ErrInfo_TypeDef fnDl645_SetNRZTPara(sFrmDl645B_TypeDef *RxFrm)
{
    u32 DI = ((u32)RxFrm->UDat.DI3 << 24) + ((u32)RxFrm->UDat.DI2 << 16) + ((u32)RxFrm->UDat.DI1 << 8) + (u32)RxFrm->UDat.DI0;
    extern void rn7306_cail_fine_phs_error_xiebo(UINT8 * buf, UINT8 interval);

    switch (DI)
    {
        case 0xE0020000:
        {
            if (RxFrm->UDat.Dat[8] == 0xAA)     // dyf 开锁默认255min
            {
                Secret.tPrgKeyValid = 0x00FF;
                fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 6, &Secret.tPrgKeyValid, 2);
                Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable = 1;
            }
            else
            {
                Secret.tPrgKeyValid = 0;
                fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 6, &Secret.tPrgKeyValid, 2);
                Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable = 0;
            }
            break;
        }

        case 0xE00C0B00:    // 直流偶次谐波补偿开关
        {
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Flag_EnOrDis, &RxFrm->UDat.Dat[8], 1);
            parameter.xiebo_flag = RxFrm->UDat.Dat[8];  // 更新变量
            break;
        }

        case 0xE00C0B01:    //直流偶次谐波误差补偿值 - 小于谐波补偿中心点电流时
        {
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Err, &RxFrm->UDat.Dat[8], 3);
            //0.5L下校正直流偶次谐波误差 - 低段
            rn7306_cail_fine_phs_error_xiebo(&RxFrm->UDat.Dat[8], 0);
            break;
        }

        case 0xE00C0B03:    //直流偶次谐波误差补偿值 - 大于等于谐波补偿中心点电流时
        {
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Err + 4, &RxFrm->UDat.Dat[8], 3);
            //0.5L下校正直流偶次谐波误差- 高段
            rn7306_cail_fine_phs_error_xiebo(&RxFrm->UDat.Dat[8], 1);
            break;
        }

        case 0xE00C0B05:    // 直流偶次谐波补偿中心点电流值
        {
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Mid_Current, &RxFrm->UDat.Dat[8], 4);
            break;
        }

        case 0xE00C0B06:    // 一键读写直流偶次谐波补偿值
        {
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Mid_Current, &RxFrm->UDat.Dat[8], 4);
            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Value, &RxFrm->UDat.Dat[12], 24);
            break;
        }

        default:
            break;
    }

    return DL645B_ERRINFO_OK;
}

// dyf 新增读南瑞中天数据、参数
eDL645B_ErrInfo_TypeDef fnDl645_NRZTGetData(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len)
{
    u32 DI = ((u32)DI3 << 24) + ((u32)DI2 << 16) + ((u32)DI1 << 8) + (u32)DI0;

    *Len = 0;
    switch (DI)
    {
        case 0xE0020000:
        {
            if (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable == 1)
            {
                Dst[0] = 0xAA;
            }
            else
            {
                Dst[0] = 0x00;
            }
            Dst[1] = 0x00;  // 累加和返回全00
            Dst[2] = 0x00;
            Dst[3] = 0x00;
            *Len = 4;
            break;
        }

        case 0xE00C0B00:    // 直流偶次谐波补偿开关
        {
            fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Flag_EnOrDis, Dst, 1);
            *Len = 1;
            break;
        }

        case 0xE00C0B01:    //直流偶次谐波误差补偿值 - 小于谐波补偿中心点电流时
        {
            fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Err, Dst, 3);
            *Len = 3;
            break;
        }

        case 0xE00C0B02:    //直流偶次谐波补偿后寄存器值 分别为A\B\C相补偿值 - 小于谐波补偿中心点电流时
        {
            fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Value, Dst, 12);
            *Len = 12;
            break;
        }

        case 0xE00C0B03:    //直流偶次谐波误差补偿值 - 大于等于谐波补偿中心点电流时
        {
            fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Err + 4, Dst, 3);
            *Len = 3;
            break;
        }

        case 0xE00C0B04:    // 直流偶次谐波补偿后寄存器值 分别为A\B\C相补偿值 - 大于等于谐波补偿中心点电流时
        {
            fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Value + 12, Dst, 12);
            *Len = 12;
            break;
        }

        case 0xE00C0B05:    // 直流偶次谐波补偿中心点电流值
        {
            fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Mid_Current, Dst, 4);
            *Len = 4;
            break;
        }

        case 0xE00C0B06:    // 一键读写直流偶次谐波补偿值
        {
            fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Mid_Current, Dst, 4);
            fnFile_Read(FileId_FirmPara, FileItemInfoOffAddr_Xiebo_Value, Dst + 4, 24);
            *Len = 28;
            break;
        }

        default:
            break;
    }

    return (DL645B_ERRINFO_OK);
}

/*****************************************************************************
** Function name:fnDl645B_Unpack01
**
** Description:扩展协议读特殊数据
**
** Parameters:ComPort 通讯端口 RxFrm 接收数据
**
** Returned value:返回数据长度
**
******************************************************************************/
u16 fnDl645B_Unpack01(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)
{
    eDL645B_ErrInfo_TypeDef     err;
    u16 Len;
    u32 DataAd;
    u8  i;
    u16 BufAd;

    sFrmDl645B_TypeDef *TxFrm;
    TxFrm = (sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN];
    Len = 0;
    err = DL645B_ERRINFO_OK;
    i = 0;
    if ((RxFrm->UDat.DI0 == 0xa5) &&
        (RxFrm->UDat.DI1 == 0x55) &&
        (RxFrm->UDat.DI2 == 0xaa) &&
        (RxFrm->UDat.DI3 == 0x5a))
    {
        switch (RxFrm->UDat.Dat[0])
        {
            case 0x01:
                if (RxFrm->UDat.Dat[1] == 128) ;
                break;
            case 0x08:
                TxFrm->UDat.Dat[5] = Bkgrd.PubData.FactoryFlag;
                Len = 1;
                break;

                #if(nPhs==ThreePhs)
            case 0x0a:
                if (RxFrm->UDat.Dat[2] == 0)
                {
                    i = FirmDataLen[RxFrm->UDat.Dat[1]];
                }
                else if (RxFrm->UDat.Dat[2] == 1)
                {
                    BufAd = (RxFrm->UDat.Dat[2] << 8) + RxFrm->UDat.Dat[1];
                    for (i = 0 ; i < (sizeof(FirmPara) / sizeof(sFirmPara_TypeDef)) ; i++)
                    {
                        if (BufAd == FirmPara[i].DeviceAd)
                        {
                            break;
                        }
                    }
                    if ((i < (sizeof(FirmPara) / sizeof(sFirmPara_TypeDef))))
                    {
                        i = FirmPara[i].Len;
                    }
                    else
                    {
                        i = 0;
                    }
                }
                if (i)
                {
                    TxFrm->UDat.Dat[5] = 0;
                    TxFrm->UDat.Dat[6] = 0;
                    TxFrm->UDat.Dat[7] = 0;
                    TxFrm->UDat.Dat[8] = 0;

                    if (fnRN8302_Read((RxFrm->UDat.Dat[2] << 8) + RxFrm->UDat.Dat[1], &TxFrm->UDat.Dat[5],  i) == ERROR)
                    {
                        err = DL645B_ERRINFO_DATA ;
                    }
                    else
                    {
                        Len = 4;
                    }
                }
                else
                {
                    err = DL645B_ERRINFO_DATA;
                }
                break;
                #endif

            case 0x0b:
                DataAd = (RxFrm->UDat.Dat[1] << 24) + (RxFrm->UDat.Dat[2] << 16) + (RxFrm->UDat.Dat[3] << 8) + (RxFrm->UDat.Dat[4]);
                Len = RxFrm->UDat.Dat[6] + 2;
                if (RxFrm->UDat.Dat[5] == 0x01)     // 外部EEPROM
                {
                    if (fnFM24CXX_Read(&TxFrm->UDat.Dat[7], DataAd, RxFrm->UDat.Dat[6], 3) == ERROR)
                    {
                        err = DL645B_ERRINFO_DATA;
                    }
                }
                else if (RxFrm->UDat.Dat[5] == 0x02) // 内部EEPROM
                {
                    if (fnSocEE_Read(&TxFrm->UDat.Dat[7], DataAd, RxFrm->UDat.Dat[6], 3) == ERROR)
                    {
                        err = DL645B_ERRINFO_DATA;
                    }
                }
                else if (RxFrm->UDat.Dat[5] == 0x03) // 外部FLASH
                {
                    if (fnMX25LXX_Read(&TxFrm->UDat.Dat[7], DataAd, RxFrm->UDat.Dat[6], 3) == ERROR)
                    {
                        err = DL645B_ERRINFO_DATA;
                    }
                }
                else if (RxFrm->UDat.Dat[5] == 0x04) // 内部FLASH
                {
                    if ((DataAd + RxFrm->UDat.Dat[6]) > FlashAdMax)
                    {
                        err = DL645B_ERRINFO_DATA;
                    }
                    for (i = RxFrm->UDat.Dat[6]; i > 0; i--)
                    {
                        TxFrm->UDat.Dat[7 + i] = *(Read_Flash + DataAd + i);
                    }
                }
                else if (RxFrm->UDat.Dat[5] == 0x05) // 内部SRAM
                {
                    if ((DataAd + RxFrm->UDat.Dat[6]) > 0x3800)
                    {
                        err = DL645B_ERRINFO_DATA;
                    }
                    Std_Memcpy(&TxFrm->UDat.Dat[7], (u8 *)DataAd, RxFrm->UDat.Dat[6]);
                }
                else if (RxFrm->UDat.Dat[5] == 0x06) // 外部SRAM，既MB85RC64
                {
                    if (fnFM24CXX_Read(&TxFrm->UDat.Dat[7], DataAd, RxFrm->UDat.Dat[6], 3) == ERROR)
                    {
                        err = DL645B_ERRINFO_DATA;
                    }
                }
                else
                {
                    err = DL645B_ERRINFO_DATA;
                }
                Std_Memcpy(&BufTemp[50], &RxFrm->UDat.Dat[5], 2);
                Std_Memcpy(&TxFrm->UDat.Dat[5], &BufTemp[50], 2);
                break;
            default:
                err = DL645B_ERRINFO_DATA;
                break;
        }
    }
    else
    {
        err = DL645B_ERRINFO_DATA;
    }

    Std_Memcpy(&BufTemp[50], &RxFrm->UDat.Dat[0], 5);
    Std_Memcpy(&TxFrm->UDat.Dat[0], &BufTemp[50], 5);
    if (err == DL645B_ERRINFO_OK)
    {
        Len = fnDl645_PackOk(TxFrm, RxFrm, Len + 9);
    }
    else
    {
        Len = fnDl645_PackErr(TxFrm, RxFrm, err);
    }
    return (Len);
}

//=================================================================
u16 fnDl645B_Unpack03(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)    //安全认证
{
    eDL645B_SErrInfo_TypeDef    err;
    u16 Len;

    sFrmDl645B_TypeDef *TxFrm;
    TxFrm = (sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN];
    Len = 0;
    switch (RxFrm->UDat.DI3)
    {
        case 0x07 :
            err = fnDl645_SafetyCertification(RxFrm, 0, &TxFrm->UDat.Dat[0], &Len);
            break;
        default:
            err = DL645B_SERRINFO_MISC;
            break;
    }
    if (err == DL645B_SERRINFO_OK)
    {
        Len = fnDl645_PackOk(TxFrm, RxFrm, Len + 4);
    }
    else
    {
        Len = fnDl645_SafetyPackErr(TxFrm, RxFrm, err);
    }
    return (Len);
}

/*****************************************************************************
** Function name:fnDl645B_Unpack04
**
** Description:扩展协议写特殊数据
**
** Parameters:ComPort 通讯端口 RxFrm 接收数据
**
** Returned value:返回数据长度
**
******************************************************************************/
u16 fnDl645B_Unpack04(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)
{
    eDL645B_ErrInfo_TypeDef     err;
    u16 Len;
    u16 BufAd;
    u8  i;
    sDataComm_TypeDef      EmuCommbuf;

    sFrmDl645B_TypeDef *TxFrm;
    TxFrm = (sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN];
    Len = 0;
    err = DL645B_ERRINFO_OK;

    if ((RxFrm->UDat.Dat[0] == 0x88) && (RxFrm->UDat.Dat[1] == 0x07) && (RxFrm->UDat.Dat[2] == 0x16) && (RxFrm->UDat.Dat[3] == 0x00)) ;
    else
    {
        return (fnDl645_PackErr(TxFrm, RxFrm, DL645B_ERRINFO_PSW));
    }

    if ((RxFrm->UDat.DI0 == 0xa5) &&
        (RxFrm->UDat.DI1 == 0x55) &&
        (RxFrm->UDat.DI2 == 0xaa) &&
        (RxFrm->UDat.DI3 == 0x5a))
    {
        switch (RxFrm->UDat.Dat[8])
        {
            case 0x01:
                if (RxFrm->UDat.Dat[1] == 128) ;
                break;
            case 0x07:
                if (RxFrm->UDat.Dat[9] == 0)
                {
                    err = DL645B_ERRINFO_DATA;
                }
                else
                {
                }
                break;
            case 0x08:      // 设置出厂状态
                if ((RxFrm->UDat.Dat[10] == 0x55) || (RxFrm->UDat.Dat[10] == 0xaa))
                {
                    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_FactoryFlag, &RxFrm->UDat.Dat[10], 1);
                    Bkgrd.PubData.FactoryFlag = RxFrm->UDat.Dat[10];
                }
                else
                {
                    err = DL645B_ERRINFO_DATA;
                }
                break;

                #if(nPhs==ThreePhs)
            case 0x0a:      // RN8302寄存器写
                EmuCommbuf.ucTemp8 = RN8302_WREN_EN; // 写使能位
                fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
                if (RxFrm->UDat.Dat[9] == 00)       //寄存器写入
                {
                    //BufAd = (RxFrm->UDat.Dat[11]<<8) + RxFrm->UDat.Dat[10];
                    BufAd = 0x0100 + RxFrm->UDat.Dat[10];
                    fnDl645B_Inverse(&RxFrm->UDat.Dat[14], 4);
                    for (i = 0 ; i < (sizeof(FirmPara) / sizeof(sFirmPara_TypeDef)) ; i++)
                    {
                        if (BufAd == FirmPara[i].DeviceAd)
                        {
                            break;
                        }
                    }
                    if ((i < (sizeof(FirmPara) / sizeof(sFirmPara_TypeDef))) && (RxFrm->UDat.Dat[13] < 5))
                    {
                        if (RxFrm->UDat.Dat[10] == 0x00)
                        {
                            BufAd = 0x0101;
                        }
                        fnDl645B_Inverse(&RxFrm->UDat.Dat[14], 4);
                        if (fnRN8302_Write(BufAd, &RxFrm->UDat.Dat[14], FirmPara[i].Len) == ERROR)
                        {
                            err = DL645B_ERRINFO_DATA;
                        }
                        else
                        {
                            if (RxFrm->UDat.Dat[10] == 0x00)
                            {
                                Std_Memcpy((u8 *)&MeasureFirmPara.HFConst1, &RxFrm->UDat.Dat[14 + (4 - FirmPara[i].Len)], 2);
                                EmuCommbuf.wTemp16 = MeasureFirmPara.HFConst1 / MeasureFirmPara.HighPulseRate;
                                fnRN8302_Write(RN8302_HFConst1, EmuCommbuf.ucTempBuf, 2);
                            }
                            fnFile_Write(FileId_FirmPara, FirmPara[i].OffAddr, &RxFrm->UDat.Dat[14], FirmPara[i].Len);
                            MeasureFirmPara.ChkSum1 = 0;
                            SystemDelay(10);
                            MeasureRms.PriData.Flag |= MEASURE_FLAG_CalcCheckSum;
                            fnRN8302_Read(RN8302_CheckSum1, (u8 *)&MeasureFirmPara.ChkSum1, 3) ;
                            fnFile_Write(FileId_FirmPara, FileItemInfoOffAddr_FirmPara_ChkSum1, (u8 *)&MeasureFirmPara.ChkSum1, FileItemInfoLen_FirmPara_ChkSum1);
                        }
                    }
                    else
                    {
                        err = DL645B_ERRINFO_DATA;
                    }
                }
                else if (RxFrm->UDat.Dat[9] == 0xff) //计量初始化
                {
                    fnMeasure_FirmParaInit(1);
                }
                else
                {
                    err = DL645B_ERRINFO_DATA ;
                }
                Len = RxFrm->UDat.Dat[3];
                EmuCommbuf.ucTemp8 = 0xDC; // 写保护
                fnRN8302_Write(RN8302_WREN, EmuCommbuf.ucTempBuf, 1);
                break;
                #endif

            default:
                err = DL645B_ERRINFO_DATA;
                break;
        }
    }
    else
    {
        err = DL645B_ERRINFO_DATA;
    }
    Len = fnDl645_PackErr(TxFrm, RxFrm, err);
    return (Len);
}

u16 fnDl645B_Unpack08(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)    //广播校时
{
    u8  i;
    u8  temp0, temp1, temp2;     //结算日的时转化
    u8  tempc;                             //时间转化
    sDF24   RmDate[3];
    for (i = 0 ; i < 6 ; i++)
    {
        if (RxFrm->Addr[i] != 0x99)
        {
            return (0);
        }
    }
    if (RxFrm->Len != 6)
    {
        return (0);
    }
    if (fnDl645B_JudgeClockNoWeek(0, &RxFrm->UDat.DI0, 6) == ERROR)
    {
        return (0);
    }
    if ((SysClock.Hour == 0x23) && (SysClock.Minute >= 0x55))
    {
        return (0);
    }
    if ((SysClock.Hour == 0x00) && (SysClock.Minute < 0x05))
    {
        return (0);
    }
    // 结算转存数据前不允许广播校时
    fnFile_Read(FileId_RatePara, FileItemInfoOffAddr_RatePara_RmDate, &RmDate, sizeof(sDF24) * 3);
    temp0 = fnBcdToHex_u8(RmDate[0].Hour);
    temp1 = fnBcdToHex_u8(RmDate[1].Hour);
    temp2 = fnBcdToHex_u8(RmDate[2].Hour);
    tempc = fnBcdToHex_u8(SysClock.Hour);
    if (RmDate[0].Hour != 0)
    {
        if ((SysClock.Day == RmDate[0].Day) && (tempc ==  temp0) && (SysClock.Minute < 0x05))
        {
            return (0);
        }
        if ((SysClock.Day == RmDate[0].Day) && (tempc == (temp0 - 1)) && (SysClock.Minute >= 0x55))
        {
            return (0);
        }
    }

    if ((RmDate[1].Hour != 0) && (RmDate[1].Hour != 0x99) && (RmDate[1].Day != 0x99))
    {
        if ((SysClock.Day == RmDate[1].Day) && (tempc ==  temp1) && (SysClock.Minute < 0x05))
        {
            return (0);
        }
        if ((SysClock.Day == RmDate[1].Day) && (tempc == (temp1 - 1)) && (SysClock.Minute >= 0x55))
        {
            return (0);
        }
    }

    if ((RmDate[2].Hour != 0) && (RmDate[2].Hour != 0x99) && (RmDate[2].Day != 0x99))
    {
        if ((SysClock.Day == RmDate[2].Day) && (tempc ==  temp2) && (SysClock.Minute < 0x05))
        {
            return (0);
        }
        if ((SysClock.Day == RmDate[2].Day) && (tempc == (temp2 - 1)) && (SysClock.Minute >= 0x55))
        {
            return (0);
        }
    }
    if (abs(fnTwoDateApart_SecondCount((sDF01 *)&RxFrm->UDat.DI0, &SysClock)) > (5 * 60))
    {
        return (0);
    }

    fnFile_Read(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Misc + 16, &i, 1);
    if (i == 0)
    {
        return (0);
    }
    else
    {
        i -= 1;
        fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Misc + 16, &i, 1);
    }

    SysClock = *(sDF01 *)&RxFrm->UDat.DI0;

    Bkgrd.PubData.Second = SysClock.Second;

    fnSysClock_Write(&SysClock);

    Bkgrd.PubData.fChange.FlagBit.XiugaiClock = 1;

    Bkgrd.PriData.Second = SysClock.Second;
    Bkgrd.PriData.Minute = SysClock.Minute;
    Bkgrd.PriData.Hour = SysClock.Hour;
    Bkgrd.PriData.Day = SysClock.Day;
    Bkgrd.PriData.Month = SysClock.Month;
    return (0);
}

u16 fnDl645B_Unpack11(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)    //读数据
{
    eDL645B_ErrInfo_TypeDef     err = DL645B_ERRINFO_DATA;
    u16 Len = 0;
    //  sDispItem_TypeDef dispitem;

    //  const u8    BcAddr[6] = {0x99,0x99,0x99,0x99,0x99,0x99};

    sFrmDl645B_TypeDef *TxFrm;
    TxFrm = (sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN];
    if (RxFrm->Len == 4)
    {
        switch (RxFrm->UDat.DI3)
        {
            case 0x00:
                err = fnDl645_GetRmEgSh(RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, 0, &TxFrm->UDat.Dat[0], &Len);
                break;
            //case 0x01: err = fnDl645_GetRmNeed(RxFrm->UDat.DI2 , RxFrm->UDat.DI1 , RxFrm->UDat.DI0 , 0 , &TxFrm->UDat.Dat[0] , &Len); break;
            case 0x02:
                err = fnDl645_GetVar(RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, &TxFrm->UDat.Dat[0], &Len);
                break;
            //case 0x03: err = fnDl645_GetEv(RxFrm->UDat.DI2 , RxFrm->UDat.DI1 , RxFrm->UDat.DI0 , 0 , &TxFrm->UDat.Dat[0] , &Len); break;
            case 0x04:
                err = fnDl645_GetParaVar(RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, &TxFrm->UDat.Dat[0], &Len);
                break;
            //case 0x05: err = fnDl645_GetFrz(RxFrm->UDat.DI2 , RxFrm->UDat.DI1 , RxFrm->UDat.DI0 , 0 , &TxFrm->UDat.Dat[0] , &Len); break;
            case 0x06:
                err = fnDl645_GetSocMemory(RxFrm, &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x08:
                err = DL645B_ERRINFO_DATA;
                Len = 0;
                break;
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
                err = fnDl645_GetVolEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, 0, &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x14:
            case 0x15:
                err = fnDl645_GetInPhaEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, 0, &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x16:
            case 0x17:
                err = fnDl645_GetUnblEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, 0, &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x18:
            case 0x19:
            case 0x1A:
                err = fnDl645_GetCurEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, 0, &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x1B:
            case 0x1C:
                err = fnDl645_GetWaveEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, 0, &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x1d:
                err = fnDl645_GetGateOffEv(RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x1e:
                err = fnDl645_GetGateOnEv(RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x1F:
                err = fnDl645_GetOverPfEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, 0, &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x20:
                //增加有关电流严重不平衡相关事件记录
                err = fnDl645_GetUnblEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, 0, &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x21:
                //增加有关潮流反向的相关事件记录
                err = fnDl645_GetAInSwimEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, 0, &TxFrm->UDat.Dat[0], &Len);
                break;

            case 0xE0:  // dyf 南瑞中天新增
                err = fnDl645_NRZTGetData(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, 0, &TxFrm->UDat.Dat[0], &Len);
                break;

            default:
                err = DL645B_ERRINFO_DATA;
                Len = 0;
                break;
        }
    }
    else if (RxFrm->Len == 5)
    {
        err = fnDl645_ReadProfile(RxFrm, 0, &TxFrm->UDat.Dat[0], &Len);
    }
    else if (RxFrm->Len == 9)
    {
        if (RxFrm->UDat.DI2 == 0x4 && RxFrm->UDat.DI1 == 0x03 && RxFrm->UDat.DI0 == 0x00)
        {
            Len = 0;
            #if(LCD_DISP == TRUE)
            if ((RxFrm->UDat.Dat[4] == 0xff) && (RxFrm->UDat.Dat[3] == 0xff) && (RxFrm->UDat.Dat[2] == 0xff) && (RxFrm->UDat.Dat[1] == 0xff) && (RxFrm->UDat.Dat[0] == 0xff))
            {
                Disp_EnterMode(DISP_FULL_MODE, 0);

                err = DL645B_ERRINFO_OK;
                if (Std_Memcmp(RxFrm->Addr, BcAddr, 6) == SUCCESS)
                {
                    return (0);
                }
            }
            else
            {
                if ((RxFrm->UDat.Dat[2] == 0xff) || (RxFrm->UDat.Dat[1] == 0xff) || RxFrm->UDat.Dat[0] == 0xff)
                {
                    err = DL645B_ERRINFO_MISC;
                }
                else
                {
                    {
                        Std_Memcpy(&dispitem, &RxFrm->UDat.Dat[0], 5);
                        Disp_ViewAction(dispitem, 0);
                        err = DL645B_ERRINFO_OK;
                    }
                    //else err = DL645B_ERRINFO_MISC;
                    if (Std_Memcmp(RxFrm->Addr, BcAddr, 6) == SUCCESS)
                    {
                        return (0);
                    }
                }
            }
            if (err == DL645B_ERRINFO_OK)
            {
                Len = 5;
                Std_Memcpy(&TxFrm->UDat.Dat[0], &RxFrm->UDat.Dat[0], 5);
            }
            #endif
        }
    }
    else if (RxFrm->Len == 10)
    {
        if (RxFrm->UDat.DI3 == 0x6 && RxFrm->UDat.DI2 == 0x010)
        {
            err = fnDl645_ReadCurve(RxFrm, 0, &TxFrm->UDat.Dat[0], &Len);
        }
        else
        {
            err = fnDl645_ReadProfile(RxFrm, 0, &TxFrm->UDat.Dat[0], &Len);
        }
    }
    else
    {
        err = DL645B_ERRINFO_DATA;
        Len = 0;
    }

    if (err == DL645B_ERRINFO_OK)
    {
        Len = fnDl645_PackOk(TxFrm, RxFrm, Len + 4);
    }
    else if (err == DL645B_ERRINFO_SEQDATA)
    {
        Len = fnDl645_PackSeq(TxFrm, RxFrm, Len + 4);
    }
    else
    {
        Len = fnDl645_PackErr(TxFrm, RxFrm, err);
    }
    return (Len);
}

u16 fnDl645B_Unpack12(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)
{
    eDL645B_ErrInfo_TypeDef     err;
    u16 Len = 0;
    //  u8  i,j,k;

    sFrmDl645B_TypeDef *TxFrm;
    TxFrm = (sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN];

    if (RxFrm->Len == 5)
    {
        switch (RxFrm->UDat.DI3)
        {
            case 0x00:
                err = fnDl645_GetRmEgSh(RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, RxFrm->UDat.Dat[0], &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x01:
                err = fnDl645_GetRmNeed(RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, RxFrm->UDat.Dat[0], &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x02:
                err = fnDl645_GetVar(RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x03:
                err = fnDl645_GetEv(RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, RxFrm->UDat.Dat[0], &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x04:
                err = fnDl645_GetParaVar(RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, &TxFrm->UDat.Dat[0], &Len);
                break;
            //case 0x05: err = fnDl645_GetFrz(RxFrm->UDat.DI2 , RxFrm->UDat.DI1 , RxFrm->UDat.DI0 , RxFrm->UDat.Dat[0] , &TxFrm->UDat.Dat[0] , &Len); break;
            case 0x06:
                if (RxFrm->UDat.DI3 == 0x6 && RxFrm->UDat.DI2 == 0x010)
                {
                    err = fnDl645_ReadCurve(RxFrm, RxFrm->UDat.Dat[0], &TxFrm->UDat.Dat[0], &Len);
                }
                else
                {
                    err = fnDl645_ReadProfile(RxFrm, RxFrm->UDat.Dat[0], &TxFrm->UDat.Dat[0], &Len);
                }
                break;
            case 0x08:
                err = DL645B_ERRINFO_DATA;
                Len = 0;
                break;
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
                err = fnDl645_GetVolEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, RxFrm->UDat.Dat[0], &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x14:
            case 0x15:
                err = fnDl645_GetInPhaEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, RxFrm->UDat.Dat[0], &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x16:
            case 0x17:
                err = fnDl645_GetUnblEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, RxFrm->UDat.Dat[0], &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x18:
            case 0x19:
            case 0x1A:
                err = fnDl645_GetCurEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, RxFrm->UDat.Dat[0], &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x1B:
            case 0x1C:
                err = fnDl645_GetWaveEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, RxFrm->UDat.Dat[0], &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x1F:
                err = fnDl645_GetOverPfEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, RxFrm->UDat.Dat[0], &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x20:
                //有关电流严重不平衡相关事件记录
                err = fnDl645_GetUnblEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0, RxFrm->UDat.Dat[0], &TxFrm->UDat.Dat[0], &Len);
                break;
            case 0x21:
                //增加有关潮流反向的相关事件记录
                err = fnDl645_GetAInSwimEv(RxFrm->UDat.DI3, RxFrm->UDat.DI2, RxFrm->UDat.DI1, RxFrm->UDat.DI0,  RxFrm->UDat.Dat[0], &TxFrm->UDat.Dat[0], &Len);
                break;
            default:
                err = DL645B_ERRINFO_DATA;
                Len = 0;
                break;
        }
    }
    else if (RxFrm->Len == 6)
    {
        err = fnDl645_ReadProfile(RxFrm, RxFrm->UDat.Dat[1], &TxFrm->UDat.Dat[0], &Len);
    }
    else if (RxFrm->Len == 11)
    {
        err = fnDl645_ReadProfile(RxFrm, RxFrm->UDat.Dat[6], &TxFrm->UDat.Dat[0], &Len);
    }
    else
    {
        err = DL645B_ERRINFO_DATA;
        Len = 0;
    }

    if (err == DL645B_ERRINFO_OK)
    {
        Len = fnDl645_PackOk(TxFrm, RxFrm, Len + 4);
    }
    else if (err == DL645B_ERRINFO_SEQDATA)
    {
        Len = fnDl645_PackSeq(TxFrm, RxFrm, Len + 4);
    }
    else
    {
        Len = fnDl645_PackErr(TxFrm, RxFrm, err);
    }
    return (Len);
}

u16 fnDl645B_Unpack13(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)    //读通信地址
{
    u8 i;
    u16 Len;
    sFrmDl645B_TypeDef *TxFrm;
    TxFrm = (sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN];

    for (i = 0 ; i < 6 ; i++)
    {
        if (RxFrm->Addr[i] != 0xAA)
        {
            return (0);
        }
    }
    if (RxFrm->Len != 0)
    {
        return (0);
    }

    fnFile_Read(FileId_ParaCom, FileItemInfoOffAddr_ComPara_ComAddr, &TxFrm->UDat.DI0, 6);
    Len = fnDl645_PackNoDI(TxFrm, RxFrm, 6);
    return (Len);
}

u16 fnDl645B_Unpack14(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)    //写参数
{
    eDL645B_ErrInfo_TypeDef     err;
    u16 Len = 0;
    sFrmDl645B_TypeDef *TxFrm;

    TxFrm = (sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN];

    switch (RxFrm->UDat.DI3)
    {
        case 0x04 :
            if (RxFrm->UDat.Dat[0] == 0x99)
            {
                #if(METERTYPE)
                err = fnDl645_PutParaVarWithMac(RxFrm);
                #else
                err = DL645B_ERRINFO_PSW;
                #endif
            }
            else if (RxFrm->UDat.Dat[0] == 0x98)
            {
                #if(METERTYPE)
                err = fnDl645_PutParaVarWithDecipher(RxFrm);
                #else
                err = DL645B_ERRINFO_PSW;
                #endif
            }
            else
            {
                err = fnDl645_PutParaVar(RxFrm);
            }
            break;

        case 0xE0:  // dyf 增加南瑞中天参数设置
            err = fnDl645_SetNRZTPara(RxFrm);
            break;
        default:
            err = DL645B_ERRINFO_DATA;
            break;
    }
    Len = fnDl645_PackErr(TxFrm, RxFrm, err);
    return (Len);
}

u16 fnDl645B_Unpack16(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)    //冻结命令
{
    const u8    BcAddr[] = {0x99, 0x99, 0x99, 0x99, 0x99, 0x99};
    u16 Len = 0;
    sFrmDl645B_TypeDef *TxFrm;
    ErrorStatus err;

    TxFrm = (sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN];
    if (RxFrm->Len != 4)
    {
        if (Std_Memcmp(RxFrm->Addr, BcAddr, 6) == SUCCESS)
        {
            return (0);
        }
        else
        {
            return (fnDl645_PackErr(TxFrm, RxFrm, DL645B_ERRINFO_MISC));
        }
    }

    if (fnDl645B_FramCheckBCD(&RxFrm->UDat.DI0, 4) == ERROR)
    {
        if (Std_Memcmp(RxFrm->Addr, BcAddr, 6) == SUCCESS)
        {
            Len = 0;
        }
        else
        {
            Len = fnDl645_PackErr(TxFrm, RxFrm, DL645B_ERRINFO_MISC);
        }
        return (Len);
    }

    if ((RxFrm->UDat.DI0 == 0x99) &&
        (RxFrm->UDat.DI1 == 0x99) &&
        (RxFrm->UDat.DI2 == 0x99) &&
        (RxFrm->UDat.DI3 == 0x99))
    {
        fnFreeze();   //瞬时冻结
    }
    else
    {
        if (RxFrm->UDat.DI3 != 0x99)
        {
            err = ERROR;
        }
        else
        {
            if (RxFrm->UDat.DI2 != 0x99)
            {
                err = fnDl645B_JudgeClockNoWeek(1, &RxFrm->UDat.DI0, 3);
            }
            else
            {
                if (RxFrm->UDat.DI1 != 0x99)
                {
                    err = fnDl645B_JudgeClockNoWeek(1, &RxFrm->UDat.DI0, 2);
                }
                else
                {
                    err = fnDl645B_JudgeClockNoWeek(1, &RxFrm->UDat.DI0, 1);
                }
            }
        }
        if (err == ERROR)
        {
            if (Std_Memcmp(RxFrm->Addr, BcAddr, 6) == SUCCESS)
            {
                Len = 0;
            }
            else
            {
                Len = fnDl645_PackErr(TxFrm, RxFrm, DL645B_ERRINFO_MISC);
            }
            return (Len);
        }
        //else fnFile_Write(Dl645FileId_GeneralPara , Dl645FileItemInfoOffAddr_GeneralPara_Record + 19 , &RxFrm->UDat.DI0 , sizeof(sDF17) );
    }

    if (Std_Memcmp(RxFrm->Addr, BcAddr, 6) == SUCCESS)
    {
        Len = 0;
    }
    else
    {
        Len = fnDl645_PackNoDI(TxFrm, RxFrm, 0);
    }

    return (Len);
}

u16 fnDl645B_Unpack17(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)    //更改波特率
{
    u16 Len;
    u8  i, j;
    u32 OffAddr = 0;

    if (RxFrm->Len != 1)
    {
        return (fnDl645_PackErr((sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN], RxFrm, DL645B_ERRINFO_MISC));
    }
    for (j = 0, i = 0 ; i < 8 ; i++)
    {
        if ((RxFrm->UDat.DI0 & 0x7E) & (1 << i))
        {
            j++;
        }
    }

    if (j > 1)
    {
        Len = fnDl645_PackErr((sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN], RxFrm, DL645B_ERRINFO_BPS);
    }
    else
    {
        //      #if(METERTYPE == 0)
        if (ComPort == SCOM_PORT_RS485A)
        {
            OffAddr = FileItemInfoOffAddr_ComPara_Com2Style;
        }
        else if (ComPort == SCOM_PORT_RS485B)
        {
            OffAddr = FileItemInfoOffAddr_ComPara_Com1Style;
        }
        //      #else
        if (ComPort == SCOM_PORT_RS485B)
        {
            OffAddr = FileItemInfoOffAddr_ComPara_Com1Style;
        }
        else  if (ComPort == SCOM_PORT_ZBCOM)
        {
            OffAddr = FileItemInfoOffAddr_ComPara_Com3Style;
        }
        //      #endif

        fnFile_Write(FileId_ParaCom, OffAddr, &RxFrm->UDat.DI0, 1);
        ComPack[ComPort].fBps = 1;
        ComPack[ComPort].NewBps = RxFrm->UDat.DI0;
        ComPack[ComPort].NewBpsStamp = 0;
        Len = fnDl645_PackFeatureData((sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN], RxFrm, RxFrm->UDat.DI0);
    }
    return (Len);
}

u16 fnDl645B_Unpack19(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)    //最大需量清零
{
    return 0xFFFF;
}

u16 fnDl645B_Unpack1A(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)    //电表清零
{
    return 0xFFFF;
}

u16 fnDl645B_Unpack1B(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)    //事件清零
{
    return 0xFFFF;
}

u16 fnDl645B_Unpack1C(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)     // 远程拉合闸控制
{
    eDL645B_ContErrInfo_TypeDef     err = DL645B_ContErrInfo_OK;
    eDL645B_ContExeInfo_TypeDef     ExeFlag = DL645B_ContExeInfo_NoData;
    u32 Temp1, Temp2;
    ErrorStatus Readerr;
    u8 i;
    u16 Len = 0;
    u16 GateTime;

    sFrmDl645B_TypeDef *TxFrm;
    TxFrm = (sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN];

    if (RxFrm->UDat.DI0 == 0x03)
    {
        if (Bkgrd.PubData.CipherKeyFlag)
        {
            err = DL645B_ContErrInfo_PswErr;
        }
        else
        {
            if ((RxFrm->UDat.DI0 == 0x03) && (RxFrm->UDat.DI1 == 0x43) && (RxFrm->UDat.DI2 == 0x56) && (RxFrm->UDat.DI3 == 0x98))
            {
                for (i = 0; i < 8; i++)
                {
                    ICEsamComm.Ic_Comm_RxBuf[i] = RxFrm->UDat.Dat[11 - i];
                }
            }
            else
            {
                err = DL645B_ContErrInfo_PswErr;
            }
        }
    }
    else if (RxFrm->UDat.DI0 == 0x98)
    {
        if (!Secret.RemoteValid)
        {
            err = DL645B_ContErrInfo_RemoteFail;
        }
        else
        {
            if (Secret.nMacErr >= MAX_MACERR)
            {
                err = DL645B_ContErrInfo_RemoteClose;
            }
            else
            {
                Readerr = fnICEsam_RemoteControl(&RxFrm->UDat.Dat[4], RxFrm->Len - 8, 0x88);
                if (Readerr != SUCCESS)     //当传输的数据MAC 校验错是采用错误信息字ERR 中bit2（密码错/未授权）置位，并按照异常应答帧响应。
                {
                    err = DL645B_ContErrInfo_MacErr;
                }
                else
                {
                    Readerr = fnICEsam_ReadBinFile(ESAM, 0x88, 0x00, 0x08);
                    if (Readerr != SUCCESS)     //当传输的数据MAC 校验错是采用错误信息字ERR 中bit2（密码错/未授权）置位，并按照异常应答帧响应。
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }
                    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[2], 6);
                    if (fnDl645B_JudgeClockNoWeek(0, &ICEsamComm.Ic_Comm_RxBuf[2], 6) == ERROR)
                    {
                        err = DL645B_ContErrInfo_PswErr;
                    }
                    fnDl645B_Inverse(&ICEsamComm.Ic_Comm_RxBuf[2], 6);
                }
            }
        }
    }
    else
    {
        if (fnSecret_Verify(0x04, RxFrm->UDat.DI0, &RxFrm->UDat.DI1) == SUCCESS)
        {
            ICEsamComm.Ic_Comm_RxBuf[0] = RxFrm->UDat.Dat[4];
            ICEsamComm.Ic_Comm_RxBuf[1] = RxFrm->UDat.Dat[5];
            for (i = 0; i < 6; i++)
            {
                ICEsamComm.Ic_Comm_RxBuf[i + 2] = RxFrm->UDat.Dat[11 - i];
            }
            if ((ICEsamComm.Ic_Comm_RxBuf[0] != 0x1c) && (ICEsamComm.Ic_Comm_RxBuf[0] != 0x1b))
            {
                err = DL645B_ContErrInfo_PswErr;
            }
        }
        else
        {
            err = DL645B_ContErrInfo_PswErr;
        }
    }

    if (err == DL645B_ContErrInfo_OK)
    {
        Temp1 = ((u32)(SysClock.Year) << 16) + ((u32)(SysClock.Month) << 8) + (SysClock.Day);
        Temp2 = ((u32)(ICEsamComm.Ic_Comm_RxBuf[2]) << 16) + ((u32)(ICEsamComm.Ic_Comm_RxBuf[3]) << 8) + (ICEsamComm.Ic_Comm_RxBuf[4]);
        if (Temp1 == Temp2)
        {
            Temp1 = ((u32)(SysClock.Hour) << 16) + ((u32)(SysClock.Minute) << 8) + (SysClock.Second);
            Temp2 = ((u32)(ICEsamComm.Ic_Comm_RxBuf[5]) << 16) + ((u32)(ICEsamComm.Ic_Comm_RxBuf[6]) << 8) + (ICEsamComm.Ic_Comm_RxBuf[7]);
            if (Temp1 > Temp2)
            {
                err = DL645B_ContErrInfo_RunTFail;
            }
        }
        else if (Temp1 > Temp2)
        {
            err = DL645B_ContErrInfo_RunTFail;
        }
    }
    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &i, 1);   //原始状态
    if (err == DL645B_ContErrInfo_OK)
    {
        switch (ICEsamComm.Ic_Comm_RxBuf[0])
        {
            case 0x1a:      // 拉闸
            {
                if (Bkgrd.PubData.MoneySta.RemoteKeepEg)
                {
                    err = DL645B_ContErrInfo_GataOffErr;
                }
                else
                {
                    if (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus == 0)
                    {
                        if ((i == 0x1d) || (i == 0x1e))
                        {
                            // 跳闸恢复命令已跳闸
                            ICEsamComm.Ic_Comm_RxBuf[0] |= 0x80;
                            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &ICEsamComm.Ic_Comm_RxBuf[0], 1);   //跳闸状态保存
                            Output.PubData.GataOffResumeTime = 0;
                            ExeFlag = DL645B_ContExeInfo_DirectOff;
                        }
                        else
                        {
                            fnFile_Write(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_OpCode, &RxFrm->UDat.Dat[0], 4);      //保存操作者代码
                            Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 1;
                            fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GateOffRemainTime, &GateTime, 2);   //跳闸延时时间
                            if (GateTime)
                            {
                                //Bkgrd.PubData.MtSta.MtSta3.StaBit.PreGateOff = 1;
                                GateTime = fnBcdToHex_u16(GateTime);
                                Output.PubData.GateOffRemainTime = GateTime * 60;
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
                                fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_tSafeGata, &GateTime, 2);
                                Output.PubData.GateOffRemainTime = GateTime * 60;
                            }
                            //else Bkgrd.PubData.MtSta.MtSta3.StaBit.PreGateOff = 0;
                            ICEsamComm.Ic_Comm_RxBuf[0] |= 0x80;
                            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &ICEsamComm.Ic_Comm_RxBuf[0], 1);   //跳闸状态保存
                        }
                    }
                    else
                    {
                        if ((i == 0x1d) || (i == 0x1e))
                        {
                            // 跳闸恢复命令已跳闸
                            ICEsamComm.Ic_Comm_RxBuf[0] |= 0x80;
                            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &ICEsamComm.Ic_Comm_RxBuf[0], 1);   //跳闸状态保存
                            Output.PubData.GataOffResumeTime = 0;
                            ExeFlag = DL645B_ContExeInfo_DirectOff;
                        }
                        else
                        {
                            ExeFlag = DL645B_ContExeInfo_DirectOff;
                        }
                    }
                }
            }
            break;
            case 0x1b:      // 合闸允许
            {
                #if(METERTYPE ==2)
                if (Bkgrd.PubData.MoneySta.Overdraft) ;
                else
                #endif
                {
                    if ((i != 0x9b) && (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus))
                    {
                        if ((Output.PubData.GateOffRemainTime) && (i == 0x9a))
                        {
                            Output.PubData.GateOffRemainTime = 0;
                            Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
                            i = 0x1b;
                            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &i, 1);   //状态保存
                        }
                        else
                        {
                            fnFile_Write(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_OpCode, &RxFrm->UDat.Dat[0], 4);      //保存操作者代码
                            Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
                            //Bkgrd.PubData.MtSta.MtSta3.StaBit.PreGateOff = 0;
                            ICEsamComm.Ic_Comm_RxBuf[0] |= 0x80;
                            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &ICEsamComm.Ic_Comm_RxBuf[0], 1);   //合闸允许状态保存
                        }
                    }
                    ExeFlag = DL645B_ContExeInfo_AllowOn;
                }
            }
            break;
            case 0x1c:      // 直接合闸
            {
                #if(METERTYPE ==2)
                if (Bkgrd.PubData.MoneySta.Overdraft) ;
                else
                #endif
                {
                    if (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus)
                    {
                        if ((i == 0x9a) && (Output.PubData.GateOffRemainTime))  //在拉闸允许状态
                        {
                            Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
                            ICEsamComm.Ic_Comm_RxBuf[0] = 0x1C;
                            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &ICEsamComm.Ic_Comm_RxBuf[0], 1);   //合闸允许状态保存
                        }
                        else
                        {
                            fnFile_Write(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_OpCode, &RxFrm->UDat.Dat[0], 4);      //保存操作者代码
                            Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
                            //Dl645Bkgrd.PubData.MtSta.MtSta3.StaBit.PreGateOff = 0;
                            ICEsamComm.Ic_Comm_RxBuf[0] |= 0x80;
                            fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &ICEsamComm.Ic_Comm_RxBuf[0], 1);   //合闸允许状态保存
                            Key.Press |= KEY_Relay_Ctrl;
                        }
                        ExeFlag = DL645B_ContExeInfo_DirectOn;
                    }
                    else
                    {
                        if (i == 0x9b)
                        {
                            Key.Press |= KEY_Relay_Ctrl;
                        }
                        ExeFlag = DL645B_ContExeInfo_DirectOn;
                    }
                }
            }
            break;
            case 0x1d:      // 跳闸自动恢复
            case 0x1e:
            {
                if (Bkgrd.PubData.MoneySta.RemoteKeepEg)
                {
                    err = DL645B_ContErrInfo_ResumeOffErr;
                }
                if ((i & 0x7f) == 0x1a)
                {
                    err = DL645B_ContErrInfo_ResumeExeFail;
                }
                if (i == 0x9b)
                {
                    err = DL645B_ContErrInfo_ResumeExeFail;
                }
                if (err == DL645B_ContErrInfo_OK)
                {
                    if (ICEsamComm.Ic_Comm_RxBuf[1])
                    {
                        fnFile_Write(FileId_BackUpCurMoney, FileItemInfoLen_BackUpCurMoney_CurSurplusMoney, &RxFrm->UDat.Dat[0], 4);         //保存操作者代码
                        Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 1;
                        ICEsamComm.Ic_Comm_RxBuf[0] |= 0x80;
                        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &ICEsamComm.Ic_Comm_RxBuf[0], 1);   //跳闸状态保存
                        Output.PubData.GataOffResumeTime = ICEsamComm.Ic_Comm_RxBuf[1] * 300;
                        if (Output.PubData.SafeCurFlag)
                        {
                            fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_tSafeGata, &Output.PubData.GateOffRemainTime, 2);
                            Output.PubData.GateOffRemainTime = fnBcdToHex_u16(Output.PubData.GateOffRemainTime);
                            ExeFlag = DL645B_ContExeInfo_ContrOff;
                        }
                        else
                        {
                            ExeFlag = DL645B_ContExeInfo_ResumeOff;
                        }
                    }
                    else
                    {
                        err = DL645B_ContErrInfo_ResumeTFail;
                    }
                }
            }
            break;
            case 0x2a:      // 报警
                Bkgrd.PubData.MoneySta.RemoteAlarm = 1;
                Bkgrd.PubData.MtSta.MtSta3.StaBit.PreGateOff = 1;
                ExeFlag = DL645B_ContExeInfo_Alarm;
                break;
            case 0x2b:      // 报警解除
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
                break;
            case 0x3a:
                Bkgrd.PubData.MoneySta.RemoteKeepEg = 1;
                Bkgrd.PubData.MtSta.MtSta3.StaBit.KeepEg = 1;
                Output.PubData.GataOffResumeTime = 0;
                ExeFlag = DL645B_ContExeInfo_KeepEg;
                if ((Output.PubData.GateOffRemainTime) && (i == 0x9a))
                {
                    Output.PubData.GateOffRemainTime = 0;
                    Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
                    i = 0x1b;
                    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &i, 1);   //状态保存
                }
                break;
            case 0x3b:
                Bkgrd.PubData.MoneySta.RemoteKeepEg = 0;
                Bkgrd.PubData.MtSta.MtSta3.StaBit.KeepEg = 0;
                if (Bkgrd.PubData.MoneySta.Overdraft)
                {
                    Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 1;
                }
                ExeFlag = DL645B_ContExeInfo_KeepEgOff;
                break;
            default:
                err = DL645B_ContErrInfo_PswErr;
                break;
        }
    }
    if ((RxFrm->UDat.DI0 == 0x98) && (RxFrm->UDat.DI3 == 0x01))
    {
        Len = fnDl645_ControlPackErr(TxFrm, err, ExeFlag, 0x01);
    }
    else
    {
        Len = fnDl645_ControlPackErr(TxFrm, err, ExeFlag, 0x00);
    }
    return (Len);
}

u16 fnDl645B_Unpack1D(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)    //多功能端子输出控制命令
{
    const u8    BcAddr[] = {0x99, 0x99, 0x99, 0x99, 0x99, 0x99};
    u16 Len;

    if (RxFrm->Len != 1)
    {
        return (fnDl645_PackErr((sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN], RxFrm, DL645B_ERRINFO_DATA));
    }

    if (RxFrm->UDat.DI0 == 0) //输出时钟脉冲
    {
        Bkgrd.PubData.MtSta.MtSta1.StaBit.OutMulFun = 0;

        RTC->VBAT_IOMODE = (0xa << 4); //P56 :RTC_OUT

        RTC->CTRL |= 0x00000100;
        fnRTCDrive_Delay();
        RTC->CTRL |= 0x00000001;
        fnRTCDrive_Delay();
    }
    else if ((RxFrm->UDat.DI0 == 1) || (RxFrm->UDat.DI0 == 2))
    {
        RTC->CTRL |= 0x00000100;
        fnRTCDrive_Delay();
        RTC->CTRL &= 0xfffffff8;
        fnRTCDrive_Delay();

        RTC->VBAT_IOMODE &= ~(0xf << 4); //P56 :RTC_OUT

        PinWrite_OpticalOutMulFun(1);
        if (RxFrm->UDat.DI0 == 1) //输出需量周期结束脉冲
        {
            Bkgrd.PubData.MtSta.MtSta1.StaBit.OutMulFun = 1;
        }
        else if (RxFrm->UDat.DI0 == 2) //输出时段切换结束脉冲
        {
            Bkgrd.PubData.MtSta.MtSta1.StaBit.OutMulFun = 2;
        }
    }
    else
    {
        return (0);
    }
    if (Std_Memcmp(RxFrm->Addr, BcAddr, 6) == SUCCESS)
    {
        Len = 0;
    }
    else
    {
        Len = fnDl645_PackFeatureData((sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN], RxFrm, RxFrm->UDat.DI0);
    }

    return (Len);
}

const u8 byFdwRetBuf[68] =
{
    0x05, 0xEE, 0xEE, 0x3E, 0x59, 0x43,
    0x4E, 0x5A, 0x55, 0x41, 0x52, 0x54, 0x47, 0x57,
    0x36, 0x39, 0x38, 0x56, 0x30, 0x39, 0x2D, 0x31,
    0x36, 0x31, 0x32, 0x31, 0x36, 0x2D, 0x30, 0x30,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0x02,
    0x20, 0x00, 0x00, 0xAA, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

u16 fnDl645B_Unpack1E(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)    //复旦软件扩展命令
{
    //  const u8    BcAddr[] = {0x99,0x99,0x99,0x99,0x99,0x99};
    //  u16 Len;

    sFrmDl645B_TypeDef *TxFrm;
    TxFrm = (sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN];

    Std_Memcpy(&TxFrm->UDat.DI0, &byFdwRetBuf[0], 68);

    TxFrm->Head1 = 0x68;
    Std_Memset(&TxFrm->Addr, 0xaa, 6);
    TxFrm->Head2 = 0x68;

    TxFrm->AFN = 0x1e;
    TxFrm->Persist = 0;
    TxFrm->Ack = 0;
    TxFrm->Dir = 0;

    TxFrm->Len = 0x44;

    //fnDl645B_Modify(&TxFrm->UDat.DI0 , TxFrm->Len , 1);

    TxFrm->UDat.Dat[TxFrm->Len - 4 + 0] = 0x07;
    TxFrm->UDat.Dat[TxFrm->Len - 4 + 1] = 0x16;

    return (TxFrm->Len + 12);
}

u16 fnDl645B_Unpack1F(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)    //打开及关闭编程按键
{
    u8  res = DL645B_ERRINFO_OK;

    if (((RxFrm->Len == 0x03) || ((RxFrm->Len == 0x04) && (RxFrm->UDat.DI0 == 0x0F)))
        && (Bkgrd.PubData.CipherKeyFlag == 0))   // 打开软编程 dyf 增加支持长度4B，支持两字节长度的厂内模式允许时间
    {
        if ((RxFrm->UDat.DI0 == 0x0f) && (RxFrm->UDat.DI1 == 0x55))
        {
            // 打开编程 dyf
            //编程作用时间启动
            if (RxFrm->Len == 0x04)
            {
                Secret.tPrgKeyValid = (u16)RxFrm->UDat.DI2 + ((u16)RxFrm->UDat.DI3 << 8);
            }
            else
            {
                Secret.tPrgKeyValid = (u16)RxFrm->UDat.DI2 & 0x00FF;
            }

            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 6, &Secret.tPrgKeyValid, 2);
            Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable = 1;
        }
        else if ((RxFrm->UDat.DI0 == 0x0f) && (RxFrm->UDat.DI1 == 0xaa))
        {
            // 结束编程
            //编程作用时间清0，写入中间变量E2
            fnEvtPrg_End();
            Secret.tPrgKeyValid = 0;
            fnFile_Write(FileId_InterTmp, FileItemInfoOffAddr_InterTmp_Secret + 6, &Secret.tPrgKeyValid, 2);
            Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable = 0;
        }
        else
        {
            res = DL645B_ERRINFO_DATA;
        }
    }
    else if ((RxFrm->Len == 0x04) && (Bkgrd.PubData.CipherKeyFlag == 0) && (Bkgrd.PubData.MtSta.MtSta3.StaBit.PrgEnable == 1)) //电表初始化
    {
        if ((RxFrm->UDat.DI0 == 0x13) && (RxFrm->UDat.DI1 == 0x14) && (RxFrm->UDat.DI2 == 0x54) && (RxFrm->UDat.DI3 == 0x80)) //出厂初始化，不初始化RTC/计量校表、端子测温、ASCII码参数
        {
            Event.PriData.OpFlag |= (1 << EVENT_STYLE_CLR);
            Event.PriData.Clr_Word = FACTORY_CLR_WORD;
            Event.PriData.Clr_Step = 0x5A;
        }
        else if ((RxFrm->UDat.DI0 == 0xB9) && (RxFrm->UDat.DI1 == 0xB7) && (RxFrm->UDat.DI2 == 0xA5) && (RxFrm->UDat.DI3 == 0x80)) //首次初始化，初始化所有参数，包括RTC/计量校表、端子测温、ASCII码参数
        {
            Event.PriData.OpFlag |= (1 << EVENT_STYLE_CLR);
            Event.PriData.Clr_Word = FIRST_CLR_WORD;
            Event.PriData.Clr_Step = 0x5A;
        }
        else
        {
            res = DL645B_ERRINFO_DATA;
        }
    }
    else
    {
        res = DL645B_ERRINFO_DATA;
    }

    return (fnDl645_PackErr((sFrmDl645B_TypeDef *)&ComPack[ComPort].pTx[DL645B_LEADERCODE_LEN], RxFrm, res));
}

u16 fnDl645B_RxAnalyse(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)
{
    u16 Len;

    if (RxFrm->Dir)
    {
        return (0);
    }

    switch (RxFrm->AFN)
    {
        case 0x01:
            Len = fnDl645B_Unpack01(ComPort, RxFrm);
            break;
            #if(METERTYPE)
        case 0x03:
            Len = fnDl645B_Unpack03(ComPort, RxFrm);
            break;
            #endif
        case 0x04:
            Len = fnDl645B_Unpack04(ComPort, RxFrm);
            break;
        case 0x08:
            Len = fnDl645B_Unpack08(ComPort, RxFrm);
            break;
        case 0x11:
            Len = fnDl645B_Unpack11(ComPort, RxFrm);
            break;
        case 0x12:
            Len = fnDl645B_Unpack12(ComPort, RxFrm);
            break;
        case 0x13:
            Len = fnDl645B_Unpack13(ComPort, RxFrm);
            break;
        case 0x14:
            Len = fnDl645B_Unpack14(ComPort, RxFrm);
            break;
        //case 0x15:    Len = fnDl645B_Unpack15(ComPort , RxFrm); break;
        case 0x16:
            Len = fnDl645B_Unpack16(ComPort, RxFrm);
            break;
        case 0x17:
            Len = fnDl645B_Unpack17(ComPort, RxFrm);
            break;
        case 0x19:
            Len = fnDl645B_Unpack19(ComPort, RxFrm);
            break;
        case 0x1a:
            Len = fnDl645B_Unpack1A(ComPort, RxFrm);
            break;
        case 0x1b:
            Len = fnDl645B_Unpack1B(ComPort, RxFrm);
            break;
            #if(METERTYPE)
        case 0x1c:
            Len = fnDl645B_Unpack1C(ComPort, RxFrm);
            break;
            #endif
        case 0x1d:
            Len = fnDl645B_Unpack1D(ComPort, RxFrm);
            break;
        case 0x1E:
            Len = fnDl645B_Unpack1E(ComPort, RxFrm);
            break;
        case 0x1f:
            Len = fnDl645B_Unpack1F(ComPort, RxFrm);
            break;
        default:
            Len = 0 ;
            break;
    }
    return (Len);
}

const sDl645B_HWAllowData_TypeDef HWAllowData[] =
{
    0x04000401,
    0x04000402,
    0x04800004,
    0x04000101,
    0x04000102,
    0x0400010c,
    0x00000000,
    0x00000100,
    0x00000200,
    0x00000300,
    0x00000400,
    0x0000ff00,
    0x00010000,
    0x00010100,
    0x00010200,
    0x00010300,
    0x00010400,
    0x0001ff00,
    0x00020000,
    0x00020100,
    0x00020200,
    0x00020300,
    0x00020400,
    0x0002ff00,
    0x00900100,
    0x00900101,
    0x00900200,
    0x00900201,
    0x078003ff,
    0x070003ff
};

u16 fnDl645B_Exec(u8 ComPort, sFrmDl645B_TypeDef *RxFrm)
{
    u16 Len;
    u32 DITemp;
    u8  nItem;
    //u8    temp0,temp1;
    fnDl645B_Modify((u8 *)&RxFrm->UDat, RxFrm->Len, 0);
    DITemp = (RxFrm->UDat.DI3 << 24) + (RxFrm->UDat.DI2 << 16) + (RxFrm->UDat.DI1 << 8) + (RxFrm->UDat.DI0);
    if (ComPort == SCOM_PORT_IR)
    {
        if (!Secret.tIRRequestDly)
        {
            if ((RxFrm->AFN != 0x13) && (RxFrm->AFN != 0x1F))
            {
                for (nItem = 0 ; nItem < (sizeof(HWAllowData) / sizeof(sDl645B_HWAllowData_TypeDef)) ; nItem++)
                {
                    if (DITemp == HWAllowData[nItem].DI)
                    {
                        break;
                    }
                }
                if (nItem >= (sizeof(HWAllowData) / sizeof(sDl645B_HWAllowData_TypeDef)))
                {
                    if ((RxFrm->AFN == 0x1c) && ((RxFrm->UDat.DI0 == 0x02) || (RxFrm->UDat.DI0 == 0x04))) ;
                    else
                    {
                        return (0);
                    }
                }
            }
        }
    }
    if ((DITemp == 0x078003ff) || (DITemp == 0x070003ff))
    {
        if (ComPort != SCOM_PORT_IR)
        {
            return (0);
        }
    }
    Len = fnDl645B_RxAnalyse(ComPort, RxFrm);
    return (Len);
}
