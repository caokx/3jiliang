#define  _OUTPUT_GLOBALS

#include <App.h>

/*******************
    �ɱ����������ʼ��
********************/
void fnOutput_Init(void)
{
    u8 i;

    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }

    Std_Memset(&Output, 0, sizeof(sOutput_TypeDef));
    for (i = 0; i < OUTPUTPORT_NUM; i++)
    {
        fnFile_Read(FileId_ParaOutput, FileItemInfoOffAddr_OutputPara_Style1 + (i << 2), (u8 *)&Output.Object[i], 4);
    }
    //����������

    fnFile_Read(FileId_ParaOutput, FileItemInfoOffAddr_OutputPara_RelaysOutAlarm, (u8 *)&Output.PriPara.RelaysOutAlarm[0], 10);
    fnFile_Read(FileId_ParaOutput, FileItemInfoOffAddr_OutputPara_LightAlarm, (u8 *)&Output.PriPara.LightAlarm[0], 10);
    fnFile_Read(FileId_ParaOutput, FileItemInfoOffAddr_OutputPara_SoundAlarm, (u8 *)&Output.PriPara.SoundAlarm[0], 10);
    fnFile_Read(FileId_ParaOutput, FileItemInfoOffAddr_OutputPara_SoundAlarm, (u8 *)&Output.PriPara.SoundAlarm[0], 10);
    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_GataSafeCur, (u8 *)&Output.PriPara.GataSafeCur, 4);
    fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_tSafeGata, (u8 *)&Output.PriPara.tSafeGata, 2);
    fnCrc_Check(0, (u8 *)&Output.PriPara, sizeof(Output.PriPara) - 2, (u8 *)&Output.PriPara.Crc);

    #if(GataFlag == 1)
    // ��Ϊ���ü̵�����Ϊ�������巽ʽ��������ʱ������Ϊ400MS
    Output.Object[0].Style = 0x0190;
    #endif

    BSP_RelayInit();

    return;
}

/**********************
         �ɱ���������λ
***********************/

void fnOutput_Reset(u8 Object)
{
    if (Object == OUTPUTPORT_OPTICAL)
    {
        PinWrite_OpticalOutMulFun(1);
    }
    else if (Object == OUTPUTPORT_RELAYLED)
    {
        //if(DispOperParm.Mode!=DISP_FULL_MODE)
        //PinWrite_RelayLed(1);
    }

    Output.Object[Object].Stamp = 0;

    return;
}

/*****************************************************************************
** Function name:fnRelay_PinCheck
** Description:���̵������,��ʱ��TC0  5ms���һ��
** Parameters:
** Returned value:1:��բ��0:��բ
******************************************************************************/
#if(nPhs==SinglePhs)
void fnOutput_RelayPinCheck(void)
{
    // ���ü̵���
    if (Output.PubData.CheckGataSysStamp < 105)
    {
        Output.PubData.CheckGataSysStamp++;
    }

    if (Output.PubData.CheckGataSysStamp > 100)
    {
        //if((Output.PubData.CheckGataSta&0x7f) <3)
        {
            RelayCheck_PowerON();
            if (PinRead_RelayGataCheck())
            {
                //��բ
                if ((Output.PubData.nCheckGata & 0x80) == 0)
                {
                    Output.PubData.nCheckGata = 0x80;
                }

                if (Output.PubData.nCheckGata < 0xA8)
                {
                    Output.PubData.nCheckGata++;
                }
            }
            else
            {
                //��բ
                if (Output.PubData.nCheckGata & 0x80)
                {
                    Output.PubData.nCheckGata &= 0x7F;
                }

                if (Output.PubData.nCheckGata > 0)
                {
                    Output.PubData.nCheckGata--;
                }
            }

            if (Output.PubData.nCheckGata >= 0xA8)  // ��ߵ�ƽ����200MS������Ϊ��բ
            {
                //��բ

                Output.PubData.CheckGataSta = 0x01;
                //Output.PubData.CheckGataSysStamp = 0;
            }
            else
            {
                //��բ

                Output.PubData.CheckGataSta = 0x00;
                //Output.PubData.CheckGataSysStamp = 0;
            }
        }
    }
}
#endif
/*****************************************************************************
** Function name:fnOutput_CheckGataSta
**
** Description:���̵���״̬
**
** Parameters:
**
** Returned value:
**
******************************************************************************/
#if(METERTYPE)
void fnOutput_CheckGataSta(void)
{
    u8 i, j;
    u8 RelayFlag;

    if (Bkgrd.PubData.tEmuRstDely)
    {
        return;
    }

    if ((Output.PubData.RealErrTime) && (Output.PubData.RealErrTime < 10))
    {
        Output.PubData.RealErrTime++;
    }

    // ����ѹ������Ƿ��ܽ�������բ
    j = 0;
    for (i = 0; i < 3; i++)
    {
        if (MeasureRms.PubData.U[i] > 1530)
        {
            j++;
        }
    }
    if (j > 1)
    {
        Output.PubData.OpGataAllow = 1;
    }
    else if (j == 1)
    {
        for (i = 0; i < 3; i++)
        {
            if (MeasureRms.PubData.U[i] >= 1760)
            {
                Output.PubData.OpGataAllow = 1;
                break;
            }
        }
    }
    else
    {
        Output.PubData.OpGataAllow = 0;
    }
    // �����բ������������
    #if(GataFlag == 0)

    if (Output.PriPara.GataSafeCur)
    {
        if ((abs(MeasureRms.PubData.I[0]) >= Output.PriPara.GataSafeCur) ||
            (abs(MeasureRms.PubData.I[1]) >= Output.PriPara.GataSafeCur) ||
            (abs(MeasureRms.PubData.I[2]) >= Output.PriPara.GataSafeCur))
        {
            if (Output.PubData.SafeCurFlag < 5)
            {
                Output.PubData.SafeCurFlag ++;
            }
        }// ������Ϊ0��24Сʱ��������բ
        else
        {
            if (Output.PubData.SafeCurFlag)
            {
                Output.PubData.SafeCurFlag--;
            }
        }
    }
    else
    {
        Output.PubData.SafeCurFlag = 0;
    }

    #else
    // ���ü̵������жϵ�������
    Output.PubData.SafeCurFlag = 0;

    #endif

    //---��բ��ʱʱ���ж�----
    if ((Output.PubData.GateOffRemainTime != 0) && (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus == 1))
    {
        Output.PubData.GateOffRemainTime--;
    }
    //---��բ�Զ��ָ�ʱ���ж�---
    if ((Output.PubData.GataOffResumeTime != 0) && (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus == 1))
    {
        Output.PubData.GataOffResumeTime--;
        if (!Output.PubData.GataOffResumeTime)
        {
            fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &RelayFlag, 1);   //��բ״̬

            if ((RelayFlag == 0x1d) || (RelayFlag == 0x1e))
            {
                #if(METERTYPE ==2)
                if (Bkgrd.PubData.MoneySta.Overdraft) ;
                else
                #endif
                {
                    Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
                    if (RelayFlag == 0x1d)
                    {
                        RelayFlag = 0x9c;
                        Key.Press |= KEY_Relay_Ctrl;
                    }
                    else
                    {
                        RelayFlag = 0x9b;
                    }
                    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &RelayFlag, 1);   //��բ����״̬����
                }
            }
        }
    }

    if (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus == 0)
    {
        Output.PubData.GateOffRemainTime = 0;
    }

    #if(GataFlag == 1)
    {
        //�����źż̵��������ж�
        if (MeasureRms.PubData.Pw[0])       // ������Ϊ0
        {
            fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &RelayFlag, 1);   //״̬����
            if (!(RelayFlag & 0x80))    // �̵�������δ����ʱ,���жϷǷ�״̬
            {
                Output.PubData.CheckGataSta = 0;
                if (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus)
                {
                    if (Output.PubData.RealErrFlag < 3)
                    {
                        Output.PubData.RealErrFlag++;
                    }
                    if (Output.PubData.RealErrFlag >= 3)
                    {
                        if (!Output.PubData.RealErrTime)
                        {
                            Output.PubData.RealErrTime = 1;
                        }
                        if (Output.PubData.RealErrTime > 4)
                        {
                            if (Bkgrd.PubData.EventErr[0] != BKGRD_EVENTERR_CONTROL)
                            {
                                fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataCheckFlag, &i, 1);     //��բ״̬����
                                Bkgrd.PubData.MtSta.MtSta1.Sta |= (1 << 8);
                                Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus = 0;
                                if (i == 0x5a)
                                {
                                    Bkgrd.PubData.EventErr[0] = BKGRD_EVENTERR_CONTROL;
                                    fnEvent_Operation(FileItemInfoNum_Evt_RelayStatErr, EVTSTART, NULL);
                                    i = 0x00;
                                    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataCheckFlag, &i, 1);
                                }
                            }
                        }
                    }
                }
                else
                {
                    Output.PubData.RealErrTime = 0;
                    Output.PubData.RealErrFlag = 0;
                    Bkgrd.PubData.MtSta.MtSta1.Sta &= ~(1 << 8);
                    Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus = 0;

                    if (Bkgrd.PubData.EventErr[0] != BKGRD_EVENTERR_OK)
                    {
                        Bkgrd.PubData.EventErr[0] = BKGRD_EVENTERR_OK;
                        fnEvent_Operation(FileItemInfoNum_Evt_RelayStatErr, EVTEND, NULL);
                    }

                    // �жϼ̵�����բ�¼��Ƿ��¼
                    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataCheckFlag + 1, &i, 1);
                    if (i == 0x5a)
                    {
                        fnFile_Read(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_OpCode, &temp[0], 4);
                        if (Bkgrd.PubData.EventErr[0] == BKGRD_EVENTERR_OK)
                        {
                            fnEvent_Operation(FileItemInfoNum_Evt_GateOn, EVTSTART, NULL);
                        }
                        temp[0] = 0x00;
                        temp[1] = 0x00;
                        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataCheckFlag, &temp[0], 2);
                    }
                }
            }
        }
        else            // ����Ϊ0������ж�
        {
            fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &RelayFlag, 1);   //״̬����
            if (!(RelayFlag & 0x80))    // �̵�������δ����ʱ,���жϷǷ�״̬
            {
                if (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus) // ��բ���
                {
                    Output.PubData.RealErrTime = 0;
                    if (Bkgrd.PubData.EventErr[0] != BKGRD_EVENTERR_OK)
                    {
                        Bkgrd.PubData.EventErr[0] = BKGRD_EVENTERR_OK;
                        fnEvent_Operation(FileItemInfoNum_Evt_RelayStatErr, EVTEND, NULL);
                    }

                    Output.PubData.RealErrFlag = 0;
                    Bkgrd.PubData.MtSta.MtSta1.Sta &= ~(1 << 8);
                    Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus = Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus;

                    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat + 1, &i, 1);
                    if (i == 0x5a)
                    {
                        fnFile_Read(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_OpCode, &temp[0], 4);
                        fnEvent_Operation(FileItemInfoNum_Evt_GateOff, EVTSTART, NULL);
                        i = 0x00;
                        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat + 1, &i, 1);
                    }
                }
                else                            // ��բ���
                {
                    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &i, 1);
                    if (i == 0x5a)
                    {
                        Bkgrd.PubData.MtSta.MtSta1.Sta |= (1 << 8);
                        Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus = 1;
                    }
                    else
                    {
                        Bkgrd.PubData.MtSta.MtSta1.Sta &= ~(1 << 8);
                        Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus = 0;
                    }
                }
            }
        }
    }

    #else
    {
        if (Key.Press & KEY_VAL_RelayGataCheck) //�̵���ʵ�ʴ��ں�բ״̬
        {
            fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &RelayFlag, 1);   //״̬����
            if (!(RelayFlag & 0x80))    // �̵�������δ����ʱ,���жϷǷ�״̬
            {
                // ����״̬Ϊ��բ��������Ϊ0ʱ��¼����
                // ����״̬Ϊ��բ����������Ϊ0ʱ��¼����
                if (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus)
                {
                    if (Output.PubData.RealErrFlag < 3)
                    {
                        Output.PubData.RealErrFlag++;
                    }
                    if (Output.PubData.RealErrFlag >= 3)
                    {
                        if (!Output.PubData.RealErrTime)
                        {
                            Output.PubData.RealErrTime = 1;
                        }
                        if (Output.PubData.RealErrTime > 4)
                        {
                            if (Bkgrd.PubData.EventErr[0] != BKGRD_EVENTERR_CONTROL)
                            {
                                Bkgrd.PubData.MtSta.MtSta1.Sta |= (1 << 8);
                                Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus = 0;
                                Bkgrd.PubData.EventErr[0] = BKGRD_EVENTERR_CONTROL;

                                //                              fnEvent_Operation(FileItemInfoNum_Evt_RelayStatErr , EVTSTART , NULL);
                            }
                        }
                    }
                }
                else
                {
                    if (Output.PubData.GataCommandDo == 0x55)
                    {
                        Output.PubData.GataCommandDo = 0x00;
                        fnUpdate_RptStatus(REPORT_STATUS_GATAON); //��բ�ɹ���ˢ���ϱ�״̬
                    }
                    Output.PubData.RealErrTime = 0;
                    if (Bkgrd.PubData.EventErr[0] != BKGRD_EVENTERR_OK)
                    {
                        Bkgrd.PubData.EventErr[0] = BKGRD_EVENTERR_OK;
                        Bkgrd.PubData.MtSta.MtSta1.Sta &= ~(1 << 8);
                        Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus = Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus;

                        //                      fnEvent_Operation(FileItemInfoNum_Evt_RelayStatErr , EVTEND, NULL);
                    }
                    Output.PubData.RealErrFlag = 0;
                }
            }
        }
        else        //�̵���ʵ�ʴ�����բ״̬
        {
            fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &RelayFlag, 1);   //״̬����
            if (!(RelayFlag & 0x80))    // �̵�������δ����ʱ,���жϷǷ�״̬
            {
                // ����Ϊ��բ���ҵ���Ϊ0��ʱ���¼������������Ϊ0ʱ����¼
                // ����Ϊ��բ���ҵ�����Ϊ0��ʱ���¼����
                if (((!Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus) && (!MeasureRms.PubData.Pw[0])) ||
                    ((Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus) && (MeasureRms.PubData.Pw[0])))
                {
                    if (Output.PubData.RealErrFlag < 3)
                    {
                        Output.PubData.RealErrFlag++;
                    }
                    if (Output.PubData.RealErrFlag >= 3)
                    {
                        if (!Output.PubData.RealErrTime)
                        {
                            Output.PubData.RealErrTime = 1;
                        }
                        if (Output.PubData.RealErrTime > 4)
                        {
                            if (Bkgrd.PubData.EventErr[0] != BKGRD_EVENTERR_CONTROL)
                            {
                                Bkgrd.PubData.EventErr[0] = BKGRD_EVENTERR_CONTROL;
                                Bkgrd.PubData.MtSta.MtSta1.Sta |= (1 << 8);
                                if (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus)
                                {
                                    Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus = 0;
                                }
                                else
                                {
                                    Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus = 1;
                                }

                                //                              fnEvent_Operation(FileItemInfoNum_Evt_RelayStatErr , EVTSTART , NULL);
                            }
                        }
                    }
                }
                else
                {
                    if (Output.PubData.GataCommandDo == 0x5A)
                    {
                        Output.PubData.GataCommandDo = 0x00;
                        fnUpdate_RptStatus(REPORT_STATUS_GATAOFF);  //��բ�ɹ���ˢ���ϱ�״̬
                    }
                    Output.PubData.RealErrTime = 0;
                    if (Bkgrd.PubData.EventErr[0] != BKGRD_EVENTERR_OK)
                    {
                        Bkgrd.PubData.EventErr[0] = BKGRD_EVENTERR_OK;
                        Bkgrd.PubData.MtSta.MtSta1.Sta &= ~(1 << 8);
                        Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus = Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus;

                        //                      fnEvent_Operation(FileItemInfoNum_Evt_RelayStatErr , EVTEND, NULL);
                    }
                    Output.PubData.RealErrFlag = 0;
                }
            }
        }
    }
    #endif
}
#endif
/**********************
    �ɱ�����������ѭ������?
***********************/
void fnOutput_Exec(void)
{
    u16 Signal;
    u8 i;
    u8  OpCodeTemp[4];
    u8  RelayFlag;

    if ((Bkgrd.PubData.Active != BKGRD_ACTIVE_POWON) || (Inactive.PubData.InactiveStamp))
    {
        return;
    }

    Output.nSignal = 0;
    // RelayFlag Ϊ9Aʱ ��բ  9B  9C ʱ ��բ
    fnFile_Read(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &RelayFlag, 1);   //״̬����

    if (fnCrc_Check(1, (u8 *)&Output.PriPara, sizeof(Output.PriPara) - 2, (u8 *)&Output.PriPara.Crc))
    {
        //����������
        fnFile_Read(FileId_ParaOutput, FileItemInfoOffAddr_OutputPara_RelaysOutAlarm, (u8 *)&Output.PriPara.RelaysOutAlarm[0], 10);
        fnFile_Read(FileId_ParaOutput, FileItemInfoOffAddr_OutputPara_LightAlarm, (u8 *)&Output.PriPara.LightAlarm[0], 10);
        fnFile_Read(FileId_ParaOutput, FileItemInfoOffAddr_OutputPara_SoundAlarm, (u8 *)&Output.PriPara.SoundAlarm[0], 10);
        fnCrc_Check(0, (u8 *)&Output.PriPara, sizeof(Output.PriPara) - 2, (u8 *)&Output.PriPara.Crc);
    }

    if (Bkgrd.PubData.MtSta.MtSta1.Sta & Output.PriPara.RelaysOutAlarm[0])
    {
        Output.nSignal |= 0x0004;    //�ڲ����ⲿ���Ƿѹ ,�й�����̵����������
    }
    if (Bkgrd.PubData.MtSta.MtSta4.Sta & Output.PriPara.RelaysOutAlarm[1])
    {
        Output.nSignal |= 0x0004;    //Aʧѹʧ������
    }
    if (Bkgrd.PubData.MtSta.MtSta5.Sta & Output.PriPara.RelaysOutAlarm[2])
    {
        Output.nSignal |= 0x0004;    //Bʧѹʧ������
    }
    if (Bkgrd.PubData.MtSta.MtSta6.Sta & Output.PriPara.RelaysOutAlarm[3])
    {
        Output.nSignal |= 0x0004;    //Cʧѹʧ������
    }
    if (Bkgrd.PubData.MtSta.MtSta7.Sta & Output.PriPara.RelaysOutAlarm[4])
    {
        Output.nSignal |= 0x0004;    //��ѹ����������
    }
    #if(METERTYPE)
    if (Bkgrd.PubData.MoneySta.RemoteAlarm)
    {
        Output.nSignal |= 0x0004;
    }
    #endif
    //    if (Bkgrd.PubData.MtSta.MtSta1.Sta & Dl645Output.PriPara.LightAlarm[0])  Dl645Output.nSignal |=0x0100;   //�ⱨ��
    //    if (Bkgrd.PubData.MtSta.MtSta4.Sta & Dl645Output.PriPara.LightAlarm[1])  Dl645Output.nSignal |=0x0100;   //
    //    if (Bkgrd.PubData.MtSta.MtSta5.Sta & Dl645Output.PriPara.LightAlarm[2])  Dl645Output.nSignal |=0x0100;   //
    //    if (Bkgrd.PubData.MtSta.MtSta6.Sta & Dl645Output.PriPara.LightAlarm[3])  Dl645Output.nSignal |=0x0100;   //
    //    if (Bkgrd.PubData.MtSta.MtSta7.Sta & Dl645Output.PriPara.LightAlarm[4])  Dl645Output.nSignal |=0x0100;

    #if(METERTYPE)
    if (Bkgrd.PubData.MoneySta.RemoteAlarm == 1)
    {
        Output.nSignal |= 0x0100;
    }
    #if(METERTYPE == 2)
    if (Bkgrd.PubData.MoneySta.LowAlarm1 || Bkgrd.PubData.MoneySta.LowAlarm2 || Bkgrd.PubData.MoneySta.SurplusMoneyZero)
    {
        Output.nSignal |= 0x0100;
    }
    if (Bkgrd.PubData.MoneySta.LowAlarm2 || Bkgrd.PubData.MoneySta.SurplusMoneyZero || Bkgrd.PubData.MoneySta.Overdraft)
    {
        Output.nSignal |= 0x1000;
    }
    #endif
    #endif

    if (Bkgrd.PubData.MtSta.MtSta1.Sta & Output.PriPara.SoundAlarm[0])
    {
        Output.nSignal |= 0x1000;    //������
    }
    if (Bkgrd.PubData.MtSta.MtSta4.Sta & Output.PriPara.SoundAlarm[1])
    {
        Output.nSignal |= 0x1000;    //
    }
    if (Bkgrd.PubData.MtSta.MtSta5.Sta & Output.PriPara.SoundAlarm[2])
    {
        Output.nSignal |= 0x1000;    //
    }
    if (Bkgrd.PubData.MtSta.MtSta6.Sta & Output.PriPara.SoundAlarm[3])
    {
        Output.nSignal |= 0x1000;    //
    }
    if (Bkgrd.PubData.MtSta.MtSta7.Sta & Output.PriPara.SoundAlarm[4])
    {
        Output.nSignal |= 0x1000;
    }

    if (Bkgrd.PubData.fChange.FlagBit.POT && (Bkgrd.PubData.MtSta.MtSta1.StaBit.OutMulFun == 0x02))
    {
        Output.nSignal |= 0x0010;    //ʱ���л�
    }
    if (Bkgrd.PubData.fChange.FlagBit.DemandCycle && (Bkgrd.PubData.MtSta.MtSta1.StaBit.OutMulFun == 0x01))
    {
        Output.nSignal |= 0x0010;    //�������ڽ���
    }
    #if(GataFlag == 0)
    if (!Bkgrd.PubData.MoneySta.RemoteKeepEg)
    {
        if ((Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus) && (!(RelayFlag & 0x80)))
        {
            Output.nSignal |= 0x2000;
        }
    }
    #else
    if ((Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus) && (!(RelayFlag & 0x80)))
    {
        Output.nSignal |= 0x2000;
    }
    #endif

    for (i = 0; i < 7; i++)
    {
        if (Bkgrd.PubData.EventErr[i])
        {
            Output.nSignal |= 0x0100;
        }
    }

    if (Bkgrd.PubData.MoneySta.RemoteKeepEg)
    {
        if ((Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus) || (RelayFlag == 0x9b) || (RelayFlag == 0x9c))
        {
            #if(GataFlag == 0)
            if ((Key.Press & KEY_Relay_Ctrl) || (Key.Press & KEY_VAL_CARD) || (i == 0x9c))
            #endif
            {
                #if(ZBComFlag)
                if ((Output.PubData.OpGataAllow) && ((!PinRead_CheckZBSta()) || (!Bkgrd.PubData.CheckZBFlag)))
                #else
                if (Output.PubData.OpGataAllow)
                #endif
                {
                    Output.nSignal |= 0x0002;
                    fnFile_Read(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_OpCode, &OpCodeTemp[0], 4);
                    #if(GataFlag == 0)
                    //                  if(Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus==1) //�̵���״̬Ϊ��ʱ��¼��բ�¼���¼
                    //                      fnEvent_Operation(FileItemInfoNum_Evt_GateOn , EVTSTART , NULL);
                    #else
                    // ���ü̵����¼���״̬�жϱ�־
                    OpCodeTemp[0] = 0x5a;
                    OpCodeTemp[1] = 0x5a;
                    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataCheckFlag, &OpCodeTemp[0], 2);   //��բ״̬����
                    #endif
                    OpCodeTemp[0] = 0x1b;
                    fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &OpCodeTemp[0], 1);   //״̬����
                    Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus = 0;
                    //Key.Press &= ~KEY_Relay_Ctrl;
                }
            }
            #if(GataFlag == 0)
            else
            {
                if (SysDatetimes.second & 1)
                {
                    Output.nSignal |= 0x2000;
                }
            }
            #endif
        }
        else if (Output.PubData.RealErrFlag)
        {
            #if(ZBComFlag)
            if ((Output.PubData.OpGataAllow) && ((!PinRead_CheckZBSta()) || (!Bkgrd.PubData.CheckZBFlag)))
            #else
            if (Output.PubData.OpGataAllow)
            #endif
                Output.nSignal |= 0x0002;
        }
    }
    else if (RelayFlag & 0x80)
    {
        if ((RelayFlag == 0x9a) || (RelayFlag == 0x9d) || (RelayFlag == 0x9e))
        {
            if (!Output.PubData.GateOffRemainTime)
            {
                #if(ZBComFlag)
                if ((Output.PubData.OpGataAllow) && ((!PinRead_CheckZBSta()) || (!Bkgrd.PubData.CheckZBFlag)))
                #else
                if (Output.PubData.OpGataAllow)
                #endif
                {
                    #if(GataFlag == 0)
                    //if(!Output.PubData.SafeCurFlag)
                    #endif
                    {
                        fnFile_Read(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_OpCode, &OpCodeTemp[0], 4);
                        #if(GataFlag == 0)
                        //                      if(Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus==0) //�̵���״̬Ϊͨʱ��¼��բ�¼���¼
                        //                          fnEvent_Operation(FileItemInfoNum_Evt_GateOff, EVTSTART , NULL);
                        #else
                        // ���ü̵����¼���״̬�жϱ�־
                        OpCodeTemp[0] = 0x5a;
                        OpCodeTemp[1] = 0x5a;
                        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataCheckFlag, &OpCodeTemp[0], 2);   //��բ״̬����
                        #endif
                        Output.nSignal |= 0x0001;
                        Output.nSignal |= 0x2000;
                        //Dl645Bkgrd.PubData.MtSta.MtSta3.StaBit.PreGateOff = 0;
                        OpCodeTemp[0] = RelayFlag & 0x7f;
                        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &OpCodeTemp[0], 1);   //״̬����
                    }
                }
            }
        }
        else if ((RelayFlag == 0x9b) || (RelayFlag == 0x9c))
        {
            #if(GataFlag == 0)
            if ((Key.Press & KEY_Relay_Ctrl) || (Key.Press & KEY_VAL_CARD) || (RelayFlag == 0x9c))
            #endif
            {
                #if(ZBComFlag)
                if ((Output.PubData.OpGataAllow) && ((!PinRead_CheckZBSta()) || (!Bkgrd.PubData.CheckZBFlag)))
                #else
                if (Output.PubData.OpGataAllow)
                #endif
                {
                    //if((!Output.PubData.SafeCurFlag)||(!Output.PubData.GateOffRemainTime))
                    {
                        fnFile_Read(FileId_BackUpCurMoney, FileItemInfoOffAddr_BackUpCurMoney_OpCode, &OpCodeTemp[0], 4);
                        #if(GataFlag == 0)
                        //                      if(Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus==1) //�̵���״̬Ϊ��ʱ��¼��բ�¼���¼
                        //                          fnEvent_Operation(FileItemInfoNum_Evt_GateOn , EVTSTART , NULL);
                        #else
                        // ���ü̵����¼���״̬�жϱ�־
                        OpCodeTemp[0] = 0x5a;
                        OpCodeTemp[1] = 0x5a;
                        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataCheckFlag, &OpCodeTemp[0], 2);   //��բ״̬����
                        #endif
                        OpCodeTemp[0] = 0x1b;
                        fnFile_Write(FileId_HighState, FileItemInfoOffAddr_HighState_GataOffStat, &OpCodeTemp[0], 1);   //״̬����
                        Output.nSignal |= 0x0002;
                        //Key.Press &= ~KEY_Relay_Ctrl;
                    }
                }
            }
            #if(GataFlag == 0)
            else
            {
                if (SysDatetimes.second & 1)
                {
                    Output.nSignal |= 0x2000;
                }
            }
            #endif
        }
    }
    else if ((Output.PubData.RealErrFlag) && (Output.PubData.RealErrFlag < 4) && (Output.PubData.RealErrCount != Output.PubData.RealErrFlag))       // ��̵���״̬�����ظ��Լ̵�������
    {
        Output.PubData.RealErrCount = Output.PubData.RealErrFlag;
        #if(ZBComFlag)
        if ((Output.PubData.OpGataAllow) && ((!PinRead_CheckZBSta()) || (!Bkgrd.PubData.CheckZBFlag)))
        #else
        if (Output.PubData.OpGataAllow)
        #endif
        {
            #if(GataFlag == 0)
            if (Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus)
            {
                Output.nSignal |= 0x0001;
            }
            else
            {
                Output.nSignal |= 0x0002;
            }
            #endif
        }
    }

    if ((!(RelayFlag & 0x80)) && (!Bkgrd.PubData.MoneySta.RemoteKeepEg))
    {
        Key.Press &= ~KEY_Relay_Ctrl;
    }
    Signal = (Output.nSignal ^ Output.lSignal);
    Signal = (Output.nSignal ^ Output.lSignal) & Output.nSignal;
    Output.lSignal = Output.nSignal;
    Key.Press &= ~KEY_Relay_Ctrl;
    for (i = 0; i < OUTPUTPORT_NUM; i++)
    {
        if (Signal & Output.Object[i].Trigger)
        {
            if (i == OUTPUTPORT_RELAY)
            {
                if (Bkgrd.PubData.MoneySta.RemoteKeepEg && Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus)
                {
                    //--------��բ------------
                    #if(GataFlag == 0)
                    BSP_RelayCtrl(Relay_Load_ID, RelayCmdClose);
                    #else
                    BSP_RelayCtrl(Relay_Warn_ID, RelayCmdClose);
                    #endif
                    Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus = 0;
                }
                else if ((Bkgrd.PubData.MtSta.MtSta3.StaBit.GateCmdStatus == 1) && (Output.PubData.GateOffRemainTime == 0))
                {
                    #if(GataFlag == 0)
                    BSP_RelayCtrl(Relay_Load_ID, RelayCmdOpen);
                    #else
                    BSP_RelayCtrl(Relay_Warn_ID, RelayCmdOpen);
                    #endif
                    Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus = 1;
                }
                else
                {
                    #if(GataFlag == 0)
                    BSP_RelayCtrl(Relay_Load_ID, RelayCmdClose);
                    #else
                    BSP_RelayCtrl(Relay_Warn_ID, RelayCmdClose);
                    #endif
                    Bkgrd.PubData.MtSta.MtSta3.StaBit.GateStatus = 0;
                }
            }
            else if (i == OUTPUTPORT_BJRELAY)
            {
                if (Output.PubData.OpGataAllow)
                {
                    BSP_RelayCtrl(Relay_Warn_ID, RelayCmdClose);
                }
            }
            else if (i == OUTPUTPORT_OPTICAL)
            {
                BSP_MultiFunPort_Output(80);
            }
            else if (i == OUTPUTPORT_BEEP)
            {
                PinWrite_Beep(1);
            }
            else if (i == OUTPUTPORT_RELAYLED)
            {
                PinWrite_RelayLed(0);
            }

            Output.Object[i].Stamp = SysStamp ? SysStamp : (SysStamp - 1);
        }
        else
        {
            if ((Output.Object[i].Style & 0x8000) == 0) //���巽ʽ
            {
                if (fnStamp_Through(Output.Object[i].Stamp) > (Output.Object[i].Style & 0x7fff))
                {
                    fnOutput_Reset(i);
                }//ʱ�䵽
            }
            else
            {
                if ((Output.nSignal & Output.Object[i].Trigger) == 0x0)
                {
                    fnOutput_Reset(i);
                }
            }
        }
    }
    return;
}
