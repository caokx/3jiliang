#define  _DL645_CURVE_GLOBALS

#include <App.h>

extern u32  fnFind_FrzMinSpecPos(u8 Line, u8 type, sDate_time_s_TypeDef  *TimeDest,  sFrzMinHead_TypeDef  *tempFrzMin);
extern u16  fnFind_FrzSpecPos(u8 Item, u8 type, sDate_time_s_TypeDef  *TimeDest,  sFrzCtxList_TypeDef  *List);

//-----标准记录单元---------------
const   sFrzStdList_TypeDef Frz_StdRecList =
{
    2, 11,
    0, 0x20230200, 0, 4, 0,
    0, 0x20210200, 0, 7, 4,
};

/*****************************************************************************
** Function name:fnWrite_FrzRmDayTime
**
** Description:写当前时间到掉电上电补分钟冻结，分钟冻结写/清零写/校时写/设置日冻结时间写
**                 不直接使用PowDn_Datetimes,避免频繁上下电时误补，漏补
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnWrite_PowDn_FrzDayTime(void)
{
    sDate_time_s_TypeDef tempTime;

    fnFile_Read(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_FrzDayTime, (u8 *)&tempTime, FileItemInfoLen_PowDn_FrzDayTime);

    fnGetCurrTime(&tempTime);
    tempTime.second = 0;
    fnFile_Write(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_FrzDayTime, (u8 *)&tempTime, FileItemInfoLen_PowDn_FrzDayTime);
}

/*****************************************************************************
** Function name:fnWrite_FrzRmDayTime
**
** Description:写当前时间到掉电上电补结算日冻结，结算写/清零写/校时写
**                 不直接使用PowDn_Datetimes,避免频繁上下电时误补，漏补
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnWrite_PowDn_FrzRmDayTime(void)
{
    sDate_time_s_TypeDef tempTime;

    fnFile_Read(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_FrzRmDayTime, (u8 *)&tempTime, FileItemInfoLen_PowDn_FrzRmDayTime);

    if (fnDFCompData((u8 *)&SysDatetimes.hour, (u8 *)&tempTime.hour, 5) != 0)  //小时不改变时不写E2
    {
        fnGetCurrTime(&tempTime);
        tempTime.minute = 0;
        tempTime.second = 0;
        fnFile_Write(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_FrzRmDayTime, (u8 *)&tempTime, FileItemInfoLen_PowDn_FrzRmDayTime);
    }
}

/*********************************************************************************************************
** Function name:       fnJudgeTime_FrzMin
** Descriptions:       分钟冻结查找
** input parameters:
** output parameters:
** Returned value:      TRUE  or FALSE ，TRUE:有分钟冻结产生；FALSE:无分钟冻结产生
*********************************************************************************************************/
u8 fnJudgeTime_FrzMin(void)
{
    u8 i, res = FALSE;
    sFrzMinLinePara_TypeDef tempFrzMin;

    if (fnCrc_Check(1, (u8 *)&RFrzMinLine.Cycle[0], sizeof(sFrzMinCycle_TypeDef) -2, (u8 *)&RFrzMinLine.Crc))
    {
        for (i = 0; i < MAX_FRZMIN_LINE; i++)
        {
            fnFile_Read(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[i].OffAddr, (u8 *)&tempFrzMin, sizeof(sFrzMinLinePara_TypeDef));
            RFrzMinLine.Cycle[i] = tempFrzMin.Cycle;
        }
        fnCrc_Check(0, (u8 *)&RFrzMinLine.Cycle[0], sizeof(sFrzMinCycle_TypeDef) -2, (u8 *)&RFrzMinLine.Crc);
    }

    for (i = 0; i < MAX_FRZMIN_LINE; i++)
    {
        if (((SysDatetimes.minute % RFrzMinLine.Cycle[i]) == 0) && (RFrzMinLine.Cycle[i]))
        {
            Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_MINFRZ;
            Bkgrd.PubData.FrzMin_LineItem |= 1 << i;
            res = TRUE;
        }
    }

    return res;
}

/*********************************************************************************************************
** Function name:       fnFreezePoint_Calc
** Descriptions:        周期冻结指针计算
**
*********************************************************************************************************/
void fnFreezePoint_Calc(sDate_time_s_TypeDef TimeOld, sDate_time_s_TypeDef TimeNew)
{
    u32  tempcount, OffAddr;
    u8 i;
    //u16 record_len;
    //sFrzRcdHead_TypeDef  headData;
    sFrzMinHead_TypeDef tempFrzMin;
    //sFrzCtxList_TypeDef   tmplist;
    u32 readitem;

    //--------------
    if (fnDFCompData((u8 *)&TimeOld.minute, (u8 *)&TimeNew.minute, 6) == 1)
    {
        //-------------分钟冻结-----------------
        for (i = 0; i < MAX_FRZMIN_LINE; i++)
        {
            if (RFrzMinLine.Cycle[i])
            {
                fnFile_Read(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[i].OffAddr, (u8 *)&tempFrzMin, FileItemInfo_FrzMinLineHead[i].Len);
                if (tempFrzMin.RecHead.FrzAddrEnd)
                {
                    readitem = fnFind_FrzMinSpecPos(i, GETPOS_END, &TimeNew, &tempFrzMin);
                    if (readitem != 0xFFFFFFFF)
                    {
                        //---------指定时间的上一条数据-------------------------
                        if (readitem >= 1)
                        {
                            tempcount = tempFrzMin.RecHead.FrzAddrEnd % tempFrzMin.LinePara.Depth;
                            tempcount = (tempFrzMin.LinePara.Depth + tempcount - (readitem + 1)) % tempFrzMin.LinePara.Depth;

                            OffAddr = FileItemInfo_FrzRecord[FileItemInfoNum_Frz_MinFrz].OffAddr;
                            OffAddr += (u32)tempFrzMin.LinePara.LineOffAdder + (u32)tempcount * (u32)tempFrzMin.LinePara.RecLen;

                            fnFile_Read(FileId_FrzRecord,  OffAddr, (u8 *)&tempFrzMin.RecHead, 11);

                            tempFrzMin.RecHead.FrzAddrEnd++;

                            OffAddr = FileItemInfo_FrzMinLineHead[i].OffAddr + sizeof(sFrzMinLinePara_TypeDef);  //偏移事件记录头参数
                            fnFile_Write(FileId_FrzMinLineHead, OffAddr, (u8 *)&tempFrzMin.RecHead, sizeof(sFrzRcdHead_TypeDef));
                        }
                    }
                    else
                    {
                        Std_Memset((u8 *)&tempFrzMin.RecHead, 0x00, sizeof(sFrzRcdHead_TypeDef));
                        OffAddr = FileItemInfo_FrzMinLineHead[i].OffAddr + sizeof(sFrzMinLinePara_TypeDef);  //偏移事件记录头参数
                        fnFile_Write(FileId_FrzMinLineHead, OffAddr, (u8 *)&tempFrzMin.RecHead, sizeof(sFrzRcdHead_TypeDef));
                    }
                }
                fnWDT_Restart();    // dyf add
            }
        }
    }
}

const sFrzBlock_TypeDef FrzBlock1Const[] =
{
    { 0x00100801, (u8 *) &SynFrzDataBlock.FrzPtPEgSh },
    { 0x00200801, (u8 *) &SynFrzDataBlock.FrzNtPEgSh },
    { 0x20000200, (u8 *) &SynFrzDataBlock.FrzU },
    { 0x20010200, (u8 *) &SynFrzDataBlock.FrzI },
    { 0x20070200, (u8 *) &SynFrzDataBlock.FrzPwavg},
    { 0x20080200, (u8 *) &SynFrzDataBlock.FrzPqavg},
    { 0x200A0200, (u8 *) &SynFrzDataBlock.FrzPf},
};
#define  FRZBLOCK1_MAX   (sizeof(FrzBlock1Const) / sizeof(FrzBlock1Const[0]))

const sFrzBlock_TypeDef FrzBlock2Const[] =
{
    { 0x00502801, (u8 *) &SynFrzDataBlock.FrzQd1QEgSh },
    { 0x00602801, (u8 *) &SynFrzDataBlock.FrzQd2QEgSh },
    { 0x00702801, (u8 *) &SynFrzDataBlock.FrzQd3QEgSh },
    { 0x00802801, (u8 *) &SynFrzDataBlock.FrzQd4QEgSh},
    { 0x01102801, (u8 *) &SynFrzDataBlock.FrzPtFEgSh},
    { 0x01202801, (u8 *) &SynFrzDataBlock.FrzNtFEgSh},
    { 0x02102801, (u8 *) &SynFrzDataBlock.FrzPtHEgSh},
    { 0x02202801, (u8 *) &SynFrzDataBlock.FrzNtHEgSh},
};
#define  FRZBLOCK2_MAX   (sizeof(FrzBlock2Const) / sizeof(FrzBlock2Const[0]))

/*********************************************************************************************************
** Function name:       fnFreeze_Write
** Descriptions:        写冻结数据函数
**              item : 冻结枚举号
*********************************************************************************************************/
void fnFreezeMin_Write(u8 line_item)
{
    u32     OffAddr = 0;

    u8  *DataBuf, *FrzData;
    sFrzMinHead_TypeDef tempFrzMin;
    sFrzCtxList_TypeDef    tmplist;
    u8 listOADSumNum, i, j;
    u16   len;
    u32  maxcnt_u32;

    if (line_item >= MAX_FRZMIN_LINE)
    {
        return;
    }

    fnWDT_Restart();
    DataBuf = (u8 *)fnBufTemp_Alloc(512);
    if (DataBuf == NULL)
    {
        return ;
    }
    Std_Memset(DataBuf, 0, 512);

    FrzData = (u8 *)fnBufTemp_Alloc(512);
    if (FrzData == NULL)
    {
        return ;
    }
    Std_Memset(FrzData, 0, 512);

    len = (u8)FileItemInfo_FrzMinLineHead[line_item].Len;
    OffAddr = FileItemInfo_FrzMinLineHead[line_item].OffAddr;

    fnFile_Read(FileId_FrzMinLineHead, OffAddr, &tempFrzMin, len);

    fnGetCurrTime(&tempFrzMin.RecHead.FrzTime);
    //-----更新冻结时间及序号----------------
    Std_Memcpy(FrzData, (u8 *)&tempFrzMin.RecHead.FrzAddrEnd, sizeof(sFrzRcdHead_TypeDef));     //序号从0开始

    if (line_item == 0) //冻结方案1，更新上报冻结块
    {
        SynFrzDataBlock.Frz1DateValid = 1;
        Std_Memcpy((u8 *)&SynFrzDataBlock.Frz1DateTimes, (u8 *)&tempFrzMin.RecHead.FrzTime, sizeof(sDate_time_s_TypeDef));
        Std_Memset((u8 *)&SynFrzDataBlock.FrzPtPEgSh, 0x00, 32);    //变量清零，查找到后赋值
    }
    else if (line_item == 1) //冻结方案2，更新上报冻结块
    {
        SynFrzDataBlock.Frz2DateValid = 1;
        Std_Memcpy((u8 *)&SynFrzDataBlock.Frz2DateTimes, (u8 *)&tempFrzMin.RecHead.FrzTime, sizeof(sDate_time_s_TypeDef));
        Std_Memset((u8 *)&SynFrzDataBlock.FrzQd1QEgSh, 0x00, 64);   //变量清零，查找到后赋值
    }

    //-----读取分钟冻结关联对象属性表---------
    len = FileItemInfo_FrzCtxlist[FileItemInfoNum_Frz_MinFrz].Len;
    OffAddr = FileItemInfo_FrzCtxlist[FileItemInfoNum_Frz_MinFrz].OffAddr;
    fnFile_Read(FileId_FrzCtxlist, OffAddr, DataBuf, len);

    listOADSumNum = *DataBuf++;

    DataBuf += 2;
    for (i = 0; i < listOADSumNum; i++)
    {
        Std_Memcpy(&tmplist, DataBuf, sizeof(sFrzCtxList_TypeDef));
        DataBuf += sizeof(sFrzCtxList_TypeDef);

        if (((u8)(tmplist.OAD >> 13) & 0x07) == line_item) //方案号相等
        {
            tmplist.len = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF), FrzData + tmplist.OffPos);
            if (line_item == 0)
            {
                for (j = 0; j < FRZBLOCK1_MAX; j++)
                {
                    if (tmplist.OAD == FrzBlock1Const[j].FrzBlock_OAD)
                    {
                        Std_Memcpy(FrzBlock1Const[j].FrzBlock_pAddr, FrzData + tmplist.OffPos, tmplist.len);
                        break;
                    }
                }
            }
            else
            {
                for (j = 0; j < FRZBLOCK2_MAX; j++)
                {
                    if (tmplist.OAD == FrzBlock2Const[j].FrzBlock_OAD)
                    {
                        Std_Memcpy(FrzBlock2Const[j].FrzBlock_pAddr, FrzData + tmplist.OffPos, tmplist.len);
                        break;
                    }
                }
            }
        }
    }

    maxcnt_u32 = tempFrzMin.LinePara.Depth;  //获取最大记录数
    tempFrzMin.RecHead.FrzAddrEnd++;

    if (tempFrzMin.RecHead.FrzAddrEnd % maxcnt_u32)
    {
        OffAddr = (u32)((tempFrzMin.RecHead.FrzAddrEnd % maxcnt_u32) - 1) * (u32)tempFrzMin.LinePara.RecLen;
    }
    else
    {
        OffAddr = (u32)(maxcnt_u32 - 1) * (u32)tempFrzMin.LinePara.RecLen;
    }

    if ((tempFrzMin.RecHead.FrzAddrEnd - tempFrzMin.RecHead.FrzAddrStart) > maxcnt_u32)
    {
        if (line_item == 0)
        {
            tempFrzMin.RecHead.FrzAddrStart = tempFrzMin.RecHead.FrzAddrEnd - MAX_FRZMIN_RECORD1;
        }
        else if (line_item == 1)
        {
            tempFrzMin.RecHead.FrzAddrStart = tempFrzMin.RecHead.FrzAddrEnd - MAX_FRZMIN_RECORD2;
        }
    }

    OffAddr += FileItemInfo_FrzRecord[FileItemInfoNum_Frz_MinFrz].OffAddr + (u32)tempFrzMin.LinePara.LineOffAdder;

    fnFile_Write(FileId_FrzRecord, OffAddr, FrzData, tempFrzMin.LinePara.RecLen);

    len = sizeof(sFrzRcdHead_TypeDef);
    OffAddr = FileItemInfo_FrzMinLineHead[line_item].OffAddr + sizeof(sFrzMinLinePara_TypeDef);
    fnFile_Write(FileId_FrzMinLineHead, OffAddr, (u8 *)&tempFrzMin.RecHead, len);

    fnWDT_Restart();

    fnBufTemp_Free(DataBuf);
    fnBufTemp_Free(FrzData);
}

/*********************************************************************************************************
** Function name:       fnFreeze_Write
** Descriptions:        写冻结数据函数
**              item : 冻结枚举号
*********************************************************************************************************/
#if(0)
void fnFreeze_Write(u8 item)
{
    u32     OffAddr = 0;

    u8  *DataBuf, *FrzData;
    sFrzRcdHead_TypeDef  headData;
    sFrzCtxList_TypeDef    tmplist;
    u8 listOADSumNum, i, temp1;
    u16 recordlen, maxcnt_u16, len;

    if (item >= FileItemInfoNum_Frz_MAX)
    {
        return;
    }

    fnWDT_Restart();
    DataBuf = (u8 *)fnBufTemp_Alloc(512);
    if (DataBuf == NULL)
    {
        return ;
    }
    Std_Memset(DataBuf, 0, 512);

    FrzData = (u8 *)fnBufTemp_Alloc(512);
    if (FrzData == NULL)
    {
        return ;
    }
    Std_Memset(FrzData, 0, 512);

    len = sizeof(sFrzRcdHead_TypeDef);
    OffAddr = FileItemInfo_FrzRcdHead[item].OffAddr;

    fnFile_Read(FileId_FrzRcdHead, OffAddr, &headData, len);

    fnGetCurrTime(&headData.FrzTime);
    //---------------------
    Std_Memcpy(FrzData, (u8 *)&headData, sizeof(sFrzRcdHead_TypeDef));    //序号从0开始

    //-----读取关联对象属性表---------
    len = FileItemInfo_FrzCtxlist[item].Len;
    OffAddr = FileItemInfo_FrzCtxlist[item].OffAddr;
    fnFile_Read(FileId_FrzCtxlist, OffAddr, DataBuf, len);

    listOADSumNum = *DataBuf++;

    Std_Memcpy((u8 *)&recordlen, DataBuf, 2);
    DataBuf += 2;
    for (i = 0; i < listOADSumNum; i++)
    {
        Std_Memcpy(&tmplist, DataBuf, sizeof(sFrzCtxList_TypeDef));
        DataBuf += sizeof(sFrzCtxList_TypeDef);
        tmplist.len = fnGet_OADStoreData((tmplist.OAD & 0xFFFF1FFF), FrzData + tmplist.OffPos);

        //结算日冻结，第2，,3结算日需量填全FF
        temp1 = (u8)(tmplist.OAD >> 24);
        if ((item == FileItemInfoNum_Frz_RmDayFrz) && (temp1 == 0x10))
        {
            if ((Bkgrd.PubData.fChange.Flag & BKGRD_FCHANGE_RMDAY2) ||
                (Bkgrd.PubData.fChange.Flag & BKGRD_FCHANGE_RMDAY3))
            {
                Std_Memset(FrzData + tmplist.OffPos, 0xFF, tmplist.len) ;
            }
        }
    }

    maxcnt_u16 = tmplist.Depth;  //获取最大记录数

    headData.FrzAddrEnd++;

    if (headData.FrzAddrEnd % maxcnt_u16)
    {
        OffAddr = ((headData.FrzAddrEnd % maxcnt_u16) - 1) * (u32)recordlen;
    }
    else
    {
        OffAddr = (maxcnt_u16 - 1) * (u32)recordlen;
    }

    if ((headData.FrzAddrEnd - headData.FrzAddrStart) > maxcnt_u16) //首尾相碰
    {
        headData.FrzAddrStart = headData.FrzAddrEnd - maxcnt_u16;
    }

    OffAddr += FileItemInfo_FrzRecord[item].OffAddr;

    fnFile_Write(FileId_FrzRecord, OffAddr, FrzData, recordlen);

    len = sizeof(sFrzRcdHead_TypeDef);
    OffAddr = FileItemInfo_FrzRcdHead[item].OffAddr;
    fnFile_Write(FileId_FrzRcdHead, OffAddr, &headData, len);

    fnWDT_Restart();

    fnBufTemp_Free(DataBuf);
    fnBufTemp_Free(FrzData);
}
#endif
void fnFreeze(void)
{
    u8  i,  tmp = 1, frzMin_lineItem;

    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }

    fnWDT_Restart();

    if (Bkgrd.PubData.fChange.Flag & BKGRD_FCHANGE_MINFRZ)
    {
        if (Bkgrd.PubData.FrzMin_LineItem)
        {
            for (i = 0 ; i < 8 ; i++)
            {
                if (Bkgrd.PubData.FrzMin_LineItem & tmp)
                {
                    frzMin_lineItem = i;
                    fnFreezeMin_Write(frzMin_lineItem);
                    fnWrite_PowDn_FrzDayTime();
                    Bkgrd.PubData.FrzMin_LineItem  &= (~(1 << frzMin_lineItem));
                    Bkgrd.PubData.MtSysSta.SysStaBit.EvtMinFreeze = 1;
                }

                tmp <<= 1;
            }
        }

        Bkgrd.PubData.fChange.Flag &= (~BKGRD_FCHANGE_MINFRZ);
    }
}

/*****************************************************************************
** Function name:fnFreeze_MakeUp
**
** Description: 掉电上电补分钟冻结数据
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void fnFreeze_MakeUp(void)
{
    sDate_time_s_TypeDef    FrzTime, FrzHeadTime;
    u32 temp1, temp2, PownDnAdd = 0, i;
    //u32 OffAddr;
    //u16   Cycle ;
    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }
    fnWDT_Restart();
    fnFile_Read(FileId_PowDnDataMemory, FileItemInfoOffAddr_PowDn_FrzDayTime, (u8 *)&FrzTime, sizeof(sDate_time_s_TypeDef));

    if (fnCheck_Date_time_s(&FrzTime) == ERROR)
    {
        return;
    }
    if (fnDFCompData((u8 *)&SysDatetimes.minute, (u8 *)&FrzTime.minute, 6) == 0)   //min未发生变化
    {
        return;
    }

    fnFile_Read(FileId_FrzRcdHead, FileItemInfoOffAddr_FrzRcdHead_Min + 4, (u8 *)&FrzHeadTime, sizeof(sDate_time_s_TypeDef));
    if ((fnJudge_Value((u8 *)&FrzHeadTime, 0x00, sizeof(sDate_time_s_TypeDef)) == FALSE) &&
        (fnJudge_Value((u8 *)&FrzHeadTime, 0xFF, sizeof(sDate_time_s_TypeDef)) == FALSE))
    {
        if (fnDFCompData((u8 *)&FrzTime.minute, (u8 *)&FrzHeadTime.minute, 6) != 1) //时间必须大于上1次冻结时间
        {
            return;
        }

        if (fnDFCompData((u8 *)&SysDatetimes.minute, (u8 *)&FrzTime.minute, 6) != 1) //当前时间必须大于补偿冻结起始时间
        {
            return;
        }
    }

    temp1 = fnDateTimeToMin(&SysDatetimes);
    temp2 = fnDateTimeToMin(&FrzTime);
    if (temp1 > temp2)
    {
        //------刷新时间为上1冻结时间，方便冻结时取时间变量--------------
        Std_Memcpy((u8 *)&SysDatetimes, (u8 *)&FrzTime, sizeof(sDate_time_s_TypeDef));
        //-----补1min冻结------------
        fnMinAdd(&SysDatetimes, 1);
        SysDatetimes.second = 0x00;
        Bkgrd.PubData.fChange.Flag |= BKGRD_FCHANGE_MINFRZ;
        Bkgrd.PubData.FrzMin_LineItem |= 1 << 0;
        fnFreeze();

        //-----补15min冻结------
        PownDnAdd = temp1 - temp2;

        fnWDT_Restart();
        SysDatetimes.second = 0x00;

        for (i = 0; i < PownDnAdd ; i++)
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
        //-----时间恢复---------------
        fnSysDateTimes(&SysDatetimes);
    }
}
