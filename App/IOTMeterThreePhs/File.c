
#define  _FILE_GLOBALS
#include <App.h>

//文件项信息，排列顺序必须与文件项编号保持一致
const sFileItemInfo_TypeDef FileItemInfo_EgSh[] =
{
    { FileItemInfoOffAddr_EgSh_PtPEgSh, FileItemInfoLen_EgSh_PtPEgSh     },
    { FileItemInfoOffAddr_EgSh_NtPEgSh, FileItemInfoLen_EgSh_NtPEgSh     },

    { FileItemInfoOffAddr_EgSh_Qd1QEgSh, FileItemInfoLen_EgSh_Qd1QEgSh  },
    { FileItemInfoOffAddr_EgSh_Qd2QEgSh, FileItemInfoLen_EgSh_Qd2QEgSh  },
    { FileItemInfoOffAddr_EgSh_Qd3QEgSh, FileItemInfoLen_EgSh_Qd3QEgSh    },
    { FileItemInfoOffAddr_EgSh_Qd4QEgSh, FileItemInfoLen_EgSh_Qd4QEgSh    },

    { FileItemInfoOffAddr_EgSh_PtPEgSha, FileItemInfoLen_EgSh_PtPEgSha  },
    { FileItemInfoOffAddr_EgSh_NtPEgSha, FileItemInfoLen_EgSh_NtPEgSha  },
    { FileItemInfoOffAddr_EgSh_Qd1QEgSha, FileItemInfoLen_EgSh_Qd1QEgSha },
    { FileItemInfoOffAddr_EgSh_Qd2QEgSha, FileItemInfoLen_EgSh_Qd2QEgSha },
    { FileItemInfoOffAddr_EgSh_Qd3QEgSha, FileItemInfoLen_EgSh_Qd3QEgSha },
    { FileItemInfoOffAddr_EgSh_Qd4QEgSha, FileItemInfoLen_EgSh_Qd4QEgSha },

    { FileItemInfoOffAddr_EgSh_PtPEgShb, FileItemInfoLen_EgSh_PtPEgShb  },
    { FileItemInfoOffAddr_EgSh_NtPEgShb, FileItemInfoLen_EgSh_NtPEgShb  },
    { FileItemInfoOffAddr_EgSh_Qd1QEgShb, FileItemInfoLen_EgSh_Qd1QEgShb },
    { FileItemInfoOffAddr_EgSh_Qd2QEgShb, FileItemInfoLen_EgSh_Qd2QEgShb },
    { FileItemInfoOffAddr_EgSh_Qd3QEgShb, FileItemInfoLen_EgSh_Qd3QEgShb },
    { FileItemInfoOffAddr_EgSh_Qd4QEgShb, FileItemInfoLen_EgSh_Qd4QEgShb },

    { FileItemInfoOffAddr_EgSh_PtPEgShc, FileItemInfoLen_EgSh_PtPEgShc  },
    { FileItemInfoOffAddr_EgSh_NtPEgShc, FileItemInfoLen_EgSh_NtPEgShc  },
    { FileItemInfoOffAddr_EgSh_Qd1QEgShc, FileItemInfoLen_EgSh_Qd1QEgShc },
    { FileItemInfoOffAddr_EgSh_Qd2QEgShc, FileItemInfoLen_EgSh_Qd2QEgShc },
    { FileItemInfoOffAddr_EgSh_Qd3QEgShc, FileItemInfoLen_EgSh_Qd3QEgShc },
    { FileItemInfoOffAddr_EgSh_Qd4QEgShc, FileItemInfoLen_EgSh_Qd4QEgShc },

    { FileItemInfoOffAddr_EgSh_PtFEgSh, FileItemInfoLen_EgSh_PtFEgSh     },
    { FileItemInfoOffAddr_EgSh_NtFEgSh, FileItemInfoLen_EgSh_NtFEgSh     },

    { FileItemInfoOffAddr_EgSh_PtHEgSh, FileItemInfoLen_EgSh_PtHEgSh     },
    { FileItemInfoOffAddr_EgSh_NtHEgSh, FileItemInfoLen_EgSh_NtHEgSh     }
};

const sFileItemInfo_TypeDef FileItemInfo_InterTmp[] =
{
    {   FileItemInfoOffAddr_InterTmp_Need,   FileItemInfoLen_InterTmp_Need   },
    {   FileItemInfoOffAddr_InterTmp_EvStatus,   FileItemInfoLen_InterTmp_EvStatus   },
    {   FileItemInfoOffAddr_InterTmp_Stat,   FileItemInfoLen_InterTmp_Stat   },
    {   FileItemInfoOffAddr_InterTmp_Secret,   FileItemInfoLen_InterTmp_Secret     },
    {   FileItemInfoOffAddr_InterTmp_OpenCover,    FileItemInfoLen_InterTmp_OpenCover  },
    {   FileItemInfoOffAddr_InterTmp_Misc,   FileItemInfoLen_InterTmp_Misc   },
    {   FileItemInfoOffAddr_InterTmp_EgMoney,   FileItemInfoLen_InterTmp_EgMoney    },
    {   FileItemInfoOffAddr_InterTmp_MLinkSize,    FileItemInfoLen_InterTmp_MLinkSize  },
    {   FileItemInfoOffAddr_InterTmp_TLinkSize,    FileItemInfoLen_InterTmp_TLinkSize  }
};

const sFileItemInfo_TypeDef FileItemInfo_CurStat[] =
{
    {   FileItemInfoOffAddr_Stat_UaElig_Day, FileItemInfoLen_Stat_UaElig_Day   },
    {   FileItemInfoOffAddr_Stat_UbElig_Day, FileItemInfoLen_Stat_UbElig_Day   },
    {   FileItemInfoOffAddr_Stat_UcElig_Day, FileItemInfoLen_Stat_UcElig_Day   },
    {   FileItemInfoOffAddr_Stat_UaElig_Month, FileItemInfoLen_Stat_UaElig_Month },
    {   FileItemInfoOffAddr_Stat_UbElig_Month, FileItemInfoLen_Stat_UbElig_Month },
    {   FileItemInfoOffAddr_Stat_UcElig_Month, FileItemInfoLen_Stat_UcElig_Month },
    {   FileItemInfoOffAddr_Stat_Misc, FileItemInfoLen_Stat_Misc                 }
};

const sFileItemInfo_TypeDef FileItemInfo_RatePara[] =
{
    {   FileItemInfoOffAddr_RatePara_nTimeZone,   FileItemInfoLen_RatePara_nTimeZone  },
    {   FileItemInfoOffAddr_RatePara_nPOTTable,   FileItemInfoLen_RatePara_nPOTTable  },
    {   FileItemInfoOffAddr_RatePara_nDayPOT,   FileItemInfoLen_RatePara_nDayPOT    },
    {   FileItemInfoOffAddr_RatePara_nFl,   FileItemInfoLen_RatePara_nFl    },
    {   FileItemInfoOffAddr_RatePara_nHoliday,   FileItemInfoLen_RatePara_nHoliday   },
    {   FileItemInfoOffAddr_RatePara_nLadder,   FileItemInfoLen_RatePara_nLadder    },
    {   FileItemInfoOffAddr_RatePara_Weekend,   FileItemInfoLen_RatePara_Weekend    },
    {   FileItemInfoOffAddr_RatePara_WeekendPOT,   FileItemInfoLen_RatePara_WeekendPOT },
    {   FileItemInfoOffAddr_RatePara_RmDate,   FileItemInfoLen_RatePara_RmDate },
    {   FileItemInfoOffAddr_RatePara_HolidayTable,   FileItemInfoLen_RatePara_HolidayTable   },
    {   FileItemInfoOffAddr_RatePara_TimeZonePara,   FileItemInfoLen_RatePara_TimeZonePara   },
    {   FileItemInfoOffAddr_RatePara_POTTablePara,   FileItemInfoLen_RatePara_POTTablePara   },
    {   FileItemInfoOffAddr_RatePara_RatePricePara,   FileItemInfoLen_RatePara_RatePricePara  },
    {   FileItemInfoOffAddr_RatePara_LadderPara,   FileItemInfoLen_RatePara_LadderPara },
    {   FileItemInfoOffAddr_RatePara_ChargMoneyPara,  FileItemInfoLen_RatePara_ChargMoneyPara }
};

const sFileItemInfo_TypeDef FileItemInfo_ParaDoc[] =
{
    {   FileItemInfoOffAddr_DocPara_NeedMode, FileItemInfoLen_DocPara_NeedMode           },
    {   FileItemInfoOffAddr_DocPara_NeedCyc, FileItemInfoLen_DocPara_NeedCyc        },
    {   FileItemInfoOffAddr_DocPara_NeedSlip, FileItemInfoLen_DocPara_NeedSlip       },
    {   FileItemInfoOffAddr_DocPara_PlsWidth, FileItemInfoLen_DocPara_PlsWidth       },
    {   FileItemInfoOffAddr_DocPara_nWave, FileItemInfoLen_DocPara_nWave          },
    {   FileItemInfoOffAddr_DocPara_BroadcastMIN, FileItemInfoLen_DocPara_BroadcastMIN    },
    {   FileItemInfoOffAddr_DocPara_BroadcastMAX, FileItemInfoLen_DocPara_BroadcastMAX    },
    {   FileItemInfoOffAddr_DocPara_WirelessSignal, FileItemInfoLen_DocPara_WirelessSignal },
    {   FileItemInfoOffAddr_DocPara_Crc, FileItemInfoLen_DocPara_Crc }
};

const sFileItemInfo_TypeDef FileItemInfo_ParaCom[] =
{
    {   FileItemInfoOffAddr_ComPara_ComAddr, FileItemInfoLen_ComPara_ComAddr   },
    {   FileItemInfoOffAddr_ComPara_Ir1Style, FileItemInfoLen_ComPara_Ir1Style  },
    {   FileItemInfoOffAddr_ComPara_Ir2Style, FileItemInfoLen_ComPara_Ir2Style  },
    {   FileItemInfoOffAddr_ComPara_Com1Style, FileItemInfoLen_ComPara_Com1Style },
    {   FileItemInfoOffAddr_ComPara_Com2Style, FileItemInfoLen_ComPara_Com2Style },
    {   FileItemInfoOffAddr_ComPara_Com3Style, FileItemInfoLen_ComPara_Com3Style }
};
const sFileItemInfo_TypeDef FileItemInfo_ParaDisp[] =
{
    {   FileItemInfoOffAddr_DispPara_AllonDispTime, FileItemInfoLen_DispPara_AllonDispTime  },
    {   FileItemInfoOffAddr_DispPara_KeyLightTime, FileItemInfoLen_DispPara_KeyLightTime      },
    {   FileItemInfoOffAddr_DispPara_ChkLightTime, FileItemInfoLen_DispPara_ChkLightTime      },
    {   FileItemInfoOffAddr_DispPara_KeyPwrOffTime, FileItemInfoLen_DispPara_KeyPwrOffTime  },
    {   FileItemInfoOffAddr_DispPara_DecimalEg, FileItemInfoLen_DispPara_DecimalEg       },
    { FileItemInfoOffAddr_DispPara_DecimalPw, FileItemInfoLen_DispPara_DecimalPw       },
    { FileItemInfoOffAddr_DispPara_LCDWordMn, FileItemInfoLen_DispPara_LCDWordMn       },
    { FileItemInfoOffAddr_DispPara_nCycDisp, FileItemInfoLen_DispPara_nCycDisp          },
    { FileItemInfoOffAddr_DispPara_nKeyDisp, FileItemInfoLen_DispPara_nKeyDisp          },
    { FileItemInfoOffAddr_DispPara_AutoDispTime, FileItemInfoLen_DispPara_AutoDispTime      },
    { FileItemInfoOffAddr_DispPara_KeyDispTime, FileItemInfoLen_DispPara_KeyDispTime   },
    { FileItemInfoOffAddr_DispPara_CycDispItem, FileItemInfoLen_DispPara_CycDispItem       },
    { FileItemInfoOffAddr_DispPara_KeyDispItem, FileItemInfoLen_DispPara_KeyDispItem       }
};
const sFileItemInfo_TypeDef FileItemInfo_ParaWaste[] =
{
    {   FileItemInfoOffAddr_WastePara_Ga, FileItemInfoLen_WastePara_Ga },
    {   FileItemInfoOffAddr_WastePara_Ba, FileItemInfoLen_WastePara_Ba },
    {   FileItemInfoOffAddr_WastePara_Ra, FileItemInfoLen_WastePara_Ra },
    {   FileItemInfoOffAddr_WastePara_Xa, FileItemInfoLen_WastePara_Xa },
    {   FileItemInfoOffAddr_WastePara_Gb, FileItemInfoLen_WastePara_Gb },
    { FileItemInfoOffAddr_WastePara_Bb, FileItemInfoLen_WastePara_Bb },
    { FileItemInfoOffAddr_WastePara_Rb, FileItemInfoLen_WastePara_Rb },
    { FileItemInfoOffAddr_WastePara_Xb, FileItemInfoLen_WastePara_Xb },
    { FileItemInfoOffAddr_WastePara_Gc, FileItemInfoLen_WastePara_Gc },
    { FileItemInfoOffAddr_WastePara_Bc, FileItemInfoLen_WastePara_Bc },
    { FileItemInfoOffAddr_WastePara_Rc, FileItemInfoLen_WastePara_Rc },
    { FileItemInfoOffAddr_WastePara_Xc, FileItemInfoLen_WastePara_Xc }
};
const sFileItemInfo_TypeDef FileItemInfo_ParaOutput[] =
{
    { FileItemInfoOffAddr_OutputPara_Style1, FileItemInfoLen_OutputPara_Style1                 },
    { FileItemInfoOffAddr_OutputPara_Trigger1, FileItemInfoLen_OutputPara_Trigger1       },
    { FileItemInfoOffAddr_OutputPara_Style2, FileItemInfoLen_OutputPara_Style2         },
    { FileItemInfoOffAddr_OutputPara_Trigger2, FileItemInfoLen_OutputPara_Trigger2       },
    { FileItemInfoOffAddr_OutputPara_Style3, FileItemInfoLen_OutputPara_Style3         },
    { FileItemInfoOffAddr_OutputPara_Trigger3, FileItemInfoLen_OutputPara_Trigger3       },
    { FileItemInfoOffAddr_OutputPara_Style4, FileItemInfoLen_OutputPara_Style4         },
    { FileItemInfoOffAddr_OutputPara_Trigger4, FileItemInfoLen_OutputPara_Trigger4       },
    { FileItemInfoOffAddr_OutputPara_Style5, FileItemInfoLen_OutputPara_Style5         },
    { FileItemInfoOffAddr_OutputPara_Trigger5, FileItemInfoLen_OutputPara_Trigger5       },
    { FileItemInfoOffAddr_OutputPara_Style6, FileItemInfoLen_OutputPara_Style6         },
    { FileItemInfoOffAddr_OutputPara_Trigger6, FileItemInfoLen_OutputPara_Trigger6       },
    { FileItemInfoOffAddr_OutputPara_RelaysOutAlarm, FileItemInfoLen_OutputPara_RelaysOutAlarm },
    { FileItemInfoOffAddr_OutputPara_LightAlarm, FileItemInfoLen_OutputPara_LightAlarm     },
    { FileItemInfoOffAddr_OutputPara_SoundAlarm, FileItemInfoLen_OutputPara_SoundAlarm     }
};
const sFileItemInfo_TypeDef FileItemInfo_ParaCipherKey[] =
{
    {   FileItemInfoOffAddr_CipherKeyPara_nCipherKey, FileItemInfoLen_CipherKeyPara_nCipherKey               },
    {   FileItemInfoOffAddr_CipherKeyPara_WriteStarFlag, FileItemInfoLen_CipherKeyPara_WriteStarFlag      },
    {   FileItemInfoOffAddr_CipherKeyPara_CipherKeyWriteFlag, FileItemInfoLen_CipherKeyPara_CipherKeyWriteFlag },
    {   FileItemInfoOffAddr_CipherKeyPara_CipherKeyFlag, FileItemInfoLen_CipherKeyPara_CipherKeyFlag      },
    {   FileItemInfoOffAddr_CipherKeyPara_CipherKey, FileItemInfoLen_CipherKeyPara_CipherKey          },
    {   FileItemInfoOffAddr_CipherKeyPara_nCipherKeyEE, FileItemInfoLen_CipherKeyPara_nCipherKeyEE       },
    {   FileItemInfoOffAddr_CipherKeyPara_OpCode, FileItemInfoLen_CipherKeyPara_OpCode             }
};

const sFileItemInfo_TypeDef FileItemInfo_EvtReport[] =
{
    {   FileItemInfoOffAddr_EvtReport_AtiveAllow, FileItemInfoLen_EvtReport_AtiveAllow       },
    {   FileItemInfoOffAddr_EvtReport_FollowAllow, FileItemInfoLen_EvtReport_FollowAllow      },
    {   FileItemInfoOffAddr_EvtReport_RptFlagHappen, FileItemInfoLen_EvtReport_RptFlagHappen    },
    {   FileItemInfoOffAddr_EvtReport_RptFlagEnd, FileItemInfoLen_EvtReport_RptFlagEnd         },
    {   FileItemInfoOffAddr_EvtReport_RptMode, FileItemInfoLen_EvtReport_RptMode            },
    { FileItemInfoOffAddr_EvtReport_RptStatusAllow, FileItemInfoLen_EvtReport_RptStatusAllow },
    { FileItemInfoOffAddr_EvtReport_RptStatusMode, FileItemInfoLen_EvtReport_RptStatusMode  },
    { FileItemInfoOffAddr_EvtReport_RptChannel, FileItemInfoLen_EvtReport_RptChannel  },
    { FileItemInfoOffAddr_EvtReport_Crc, FileItemInfoLen_EvtReport_Crc            },

    { FileItemInfoOffAddr_EvtReport_RptStatusZB, FileItemInfoLen_EvtReport_RptStatusZB    },
    { FileItemInfoOffAddr_EvtReport_RptStuZBBack, FileItemInfoLen_EvtReport_RptStuZBBack   },
    { FileItemInfoOffAddr_EvtReport_RptStatus485, FileItemInfoLen_EvtReport_RptStatus485   },
    { FileItemInfoOffAddr_EvtReport_RptStu485Back, FileItemInfoLen_EvtReport_RptStu485Back  },
    { FileItemInfoOffAddr_EvtReport_RptStatus4852, FileItemInfoLen_EvtReport_RptStatus4852  },
    { FileItemInfoOffAddr_EvtReport_RptStu4852Back, FileItemInfoLen_EvtReport_RptStu4852Back },

    { FileItemInfoOffAddr_EvtReport_OADNumZB_A, FileItemInfoLen_EvtReport_OADNumZB_A      },
    { FileItemInfoOffAddr_EvtReport_RptListZB_A, FileItemInfoLen_EvtReport_RptListZB_A     },

    { FileItemInfoOffAddr_EvtReport_OADNumZB_F, FileItemInfoLen_EvtReport_OADNumZB_F      },
    { FileItemInfoOffAddr_EvtReport_RptListZB_F, FileItemInfoLen_EvtReport_RptListZB_F      },

    { FileItemInfoOffAddr_EvtReport_OADNum485_F, FileItemInfoLen_EvtReport_OADNum485_F      },
    { FileItemInfoOffAddr_EvtReport_RptList485_F, FileItemInfoLen_EvtReport_RptList485_F    },

    { FileItemInfoOffAddr_EvtReport_OADNum4852_F, FileItemInfoLen_EvtReport_OADNum4852_F    },
    { FileItemInfoOffAddr_EvtReport_RptList4852_F, FileItemInfoLen_EvtReport_RptList4852_F   },
    { FileItemInfoOffAddr_EvtReport_PowerUpTime, FileItemInfoLen_EvtReport_PowerUpTime     },
    { FileItemInfoOffAddr_EvtReport_PowerDnEvtRcd, FileItemInfoLen_EvtReport_PowerDnEvtRcd   },
    { FileItemInfoOffAddr_EvtReport_First_ClrTime, FileItemInfoLen_EvtReport_First_ClrTime   },
    { FileItemInfoOffAddr_EvtReport_Factory_ClrTime, FileItemInfoLen_EvtReport_Factory_ClrTime },
};

const sFileItemInfo_TypeDef FileItemInfo_ParaASCII[] =
{
    { FileItemInfoOffAddr_ASCIIPara_MeterPlace, FileItemInfoLen_ASCIIPara_MeterPlace  },
    { FileItemInfoOffAddr_ASCIIPara_DeviceNo, FileItemInfoLen_ASCIIPara_DeviceNo    },
    { FileItemInfoOffAddr_ASCIIPara_RatingVol, FileItemInfoLen_ASCIIPara_RatingVol   },
    { FileItemInfoOffAddr_ASCIIPara_MinCur, FileItemInfoLen_ASCIIPara_MinCur   },
    { FileItemInfoOffAddr_ASCIIPara_TrCur, FileItemInfoLen_ASCIIPara_TrCur   },
    { FileItemInfoOffAddr_ASCIIPara_RatingCur, FileItemInfoLen_ASCIIPara_RatingCur       },
    { FileItemInfoOffAddr_ASCIIPara_MaxCur, FileItemInfoLen_ASCIIPara_MaxCur      },
    { FileItemInfoOffAddr_ASCIIPara_PGrade, FileItemInfoLen_ASCIIPara_PGrade      },
    { FileItemInfoOffAddr_ASCIIPara_QGrade, FileItemInfoLen_ASCIIPara_QGrade      },
    { FileItemInfoOffAddr_ASCIIPara_MeterModel, FileItemInfoLen_ASCIIPara_MeterModel  },
    { FileItemInfoOffAddr_ASCIIPara_ProductDate, FileItemInfoLen_ASCIIPara_ProductDate },
    { FileItemInfoOffAddr_ASCIIPara_PtVer, FileItemInfoLen_ASCIIPara_PtVer       },
    { FileItemInfoOffAddr_ASCIIPara_SoftVer, FileItemInfoLen_ASCIIPara_SoftVer     },
    { FileItemInfoOffAddr_ASCIIPara_FirmVer, FileItemInfoLen_ASCIIPara_FirmVer     },
    { FileItemInfoOffAddr_ASCIIPara_FactoryNo, FileItemInfoLen_ASCIIPara_FactoryNo   },
    { FileItemInfoOffAddr_ASCIIPara_SoftWare, FileItemInfoLen_ASCIIPara_SoftWare    },
    { FileItemInfoOffAddr_ASCIIPara_ServerVer, FileItemInfoLen_ASCIIPara_ServerVer   },
    { FileItemInfoOffAddr_ASCIIPara_FactoryMAC, FileItemInfoLen_ASCIIPara_FactoryMAC   }
};
const sFileItemInfo_TypeDef FileItemInfo_HighState[] =
{
    {   FileItemInfoOffAddr_HighState_tEvRstDec, FileItemInfoLen_HighState_tEvRstDec                   },
    {   FileItemInfoOffAddr_HighState_GataCheckFlag, FileItemInfoLen_HighState_GataCheckFlag     },
    {   FileItemInfoOffAddr_HighState_FactoryFlag, FileItemInfoLen_HighState_FactoryFlag       },
    {   FileItemInfoOffAddr_HighState_GateOffRemainTime, FileItemInfoLen_HighState_GateOffRemainTime },
    {   FileItemInfoOffAddr_HighState_GataOffStat, FileItemInfoLen_HighState_GataOffStat       },
    {   FileItemInfoOffAddr_HighState_PowDnMoneySta, FileItemInfoLen_HighState_PowDnMoneySta     },
    {   FileItemInfoOffAddr_HighState_LocalOpenFlag, FileItemInfoLen_HighState_LocalOpenFlag     },
    {   FileItemInfoOffAddr_HighState_Gata_Do, FileItemInfoLen_HighState_Gata_Do     },
    {   FileItemInfoOffAddr_HighState_Gata_Err, FileItemInfoLen_HighState_Gata_Err     },
    {   FileItemInfoOffAddr_HighState_BroatStatue, FileItemInfoLen_HighState_BroatStatue     },
    {   FileItemInfoOffAddr_HighState_PrgQ1_Cnt, FileItemInfoLen_HighState_PrgQ1_Cnt     },
    {   FileItemInfoOffAddr_HighState_PrgQ2_Cnt, FileItemInfoLen_HighState_PrgQ2_Cnt     },
    {   FileItemInfoOffAddr_HighState_EvtSumTime, FileItemInfoLen_HighState_EvtSumTime     },
    {   FileItemInfoOffAddr_HighState_EvtRcdBfEsam, FileItemInfoLen_HighState_EvtRcdBfEsam     },
    {   FileItemInfoOffAddr_HighState_EvtRcdAfterEsam, FileItemInfoLen_HighState_EvtRcdAftEsam     },
    {   FileItemInfoOffAddr_HighState_MngPlugSta, FileItemInfoLen_HighState_MngPlugSta     },
    {   FileItemInfoOffAddr_HighState_EvtFlag, FileItemInfoLen_HighState_EvtFlag     },
    {   FileItemInfoOffAddr_HighState_EvtPwn, FileItemInfoLen_HighState_EvtPwn      },
};
const sFileItemInfo_TypeDef FileItemInfo_HighPara[] =
{
    {   FileItemInfoOffAddr_HighPara_PExpression,   FileItemInfoLen_HighPara_PExpression    },
    {   FileItemInfoOffAddr_HighPara_PtQExpression,   FileItemInfoLen_HighPara_PtQExpression  },
    {   FileItemInfoOffAddr_HighPara_NtQExpression,   FileItemInfoLen_HighPara_NtQExpression  },
    {   FileItemInfoOffAddr_HighPara_PConstE, FileItemInfoLen_HighPara_PConstE    },
    {   FileItemInfoOffAddr_HighPara_QConstE, FileItemInfoLen_HighPara_QConstE    },
    {   FileItemInfoOffAddr_HighPara_MeterNo,   FileItemInfoLen_HighPara_MeterNo    },
    {   FileItemInfoOffAddr_HighPara_CT,   FileItemInfoLen_HighPara_CT },
    {   FileItemInfoOffAddr_HighPara_PT,   FileItemInfoLen_HighPara_PT },
    {   FileItemInfoOffAddr_HighPara_WireMode,   FileItemInfoLen_HighPara_WireMode   },
    {   FileItemInfoOffAddr_HighPara_StartCur,   FileItemInfoLen_HighPara_StartCur   },
    {   FileItemInfoOffAddr_HighPara_CriticalVol,   FileItemInfoLen_HighPara_CriticalVol    },
    {   FileItemInfoOffAddr_HighPara_UserNo,   FileItemInfoLen_HighPara_UserNo },
    {   FileItemInfoOffAddr_HighPara_CardSerial,   FileItemInfoLen_HighPara_CardSerial },
    {   FileItemInfoOffAddr_HighPara_MeterRunFlag,   FileItemInfoLen_HighPara_MeterRunFlag   },
    {   FileItemInfoOffAddr_HighPara_tIRPrg,   FileItemInfoLen_HighPara_tIRPrg },
    {   FileItemInfoOffAddr_HighPara_tTerminalPrg,   FileItemInfoLen_HighPara_tTerminalPrg   },
    {   FileItemInfoOffAddr_HighPara_tEvRstDely,   FileItemInfoLen_HighPara_tEvRstDely },
    {   FileItemInfoOffAddr_HighPara_GataSafeCur,   FileItemInfoLen_HighPara_GataSafeCur},
    {   FileItemInfoOffAddr_HighPara_tSafeGata,   FileItemInfoLen_HighPara_tSafeGata  },
    {   FileItemInfoOffAddr_HighPara_GateOffDelayTime,   FileItemInfoLen_HighPara_GateOffDelayTime},
    { FileItemInfoOffAddr_HighPara_ParaVolYield, FileItemInfoLen_HighPara_ParaVolYield },
    {   FileItemInfoOffAddr_HighPara_RTCDota0,   FileItemInfoLen_HighPara_RTCDota0   },
    {   FileItemInfoOffAddr_HighPara_RTCAdj,   FileItemInfoLen_HighPara_RTCAdj},
    { FileItemInfoOffAddr_HighPara_RTCCalData, FileItemInfoLen_HighPara_RTCCalData },
    {   FileItemInfoOffAddr_HighPara_FristPowOnBak2, FileItemInfoLen_HighPara_FristPowOnBak2    }
};

const sFileItemInfo_TypeDef FileItemInfo_SecretPara[] =
{
    {   FileItemInfoOffAddr_SecretPara_SecretPara,   FileItemInfoLen_SecretPara_SecretPara   },
    {   FileItemInfoOffAddr_SecretPara_nPswRetry,   FileItemInfoLen_SecretPara_nPswRetry        },
    {   FileItemInfoOffAddr_SecretPara_tPswFailClose, FileItemInfoLen_SecretPara_tPswFailClose        },
    {   FileItemInfoOffAddr_SecretPara_tPrgKeyValid,   FileItemInfoLen_SecretPara_tPrgKeyValid },
    {   FileItemInfoOffAddr_SecretPara_tPrgKeyLock,   FileItemInfoLen_SecretPara_tPrgKeyLock  },
    {   FileItemInfoOffAddr_SecretPara_SafeModeFlag,   FileItemInfoLen_SecretPara_SafeModeFlag},
    {   FileItemInfoOffAddr_SecretPara_SafeModePara,   FileItemInfoLen_SecretPara_SafeModePara},
    {   FileItemInfoOffAddr_SecretPara_AuthOn,   FileItemInfoLen_SecretPara_AuthOn   },
    {   FileItemInfoOffAddr_SecretPara_FuncationItem,   FileItemInfoLen_SecretPara_FuncationItem    },
    {   FileItemInfoOffAddr_SecretPara_Labour,   FileItemInfoLen_SecretPara_Labour   },
    {   FileItemInfoOffAddr_SecretPara_FristPowOnBak1, FileItemInfoLen_SecretPara_FristPowOnBak1 }
};
const sFileItemInfo_TypeDef FileItemInfo_FirmPara[] =
{
    { FileItemInfoOffAddr_FirmPara_FractionI, FileItemInfoLen_FirmPara_FractionI         },
    { FileItemInfoOffAddr_FirmPara_FractionU, FileItemInfoLen_FirmPara_FractionU         },
    { FileItemInfoOffAddr_FirmPara_FractionE, FileItemInfoLen_FirmPara_FractionE         },
    { FileItemInfoOffAddr_FirmPara_FractionP, FileItemInfoLen_FirmPara_FractionP         },
    { FileItemInfoOffAddr_FirmPara_Pulse_deltaE, FileItemInfoLen_FirmPara_Pulse_deltaE    },
    { FileItemInfoOffAddr_FirmPara_HighPulseRate, FileItemInfoLen_FirmPara_HighPulseRate   },
    { FileItemInfoOffAddr_FirmPara_HFConst1, FileItemInfoLen_FirmPara_HFConst1          },
    { FileItemInfoOffAddr_FirmPara_Start_Ps, FileItemInfoLen_FirmPara_Start_Ps          },
    { FileItemInfoOffAddr_FirmPara_Start_Q, FileItemInfoLen_FirmPara_Start_Q             },
    { FileItemInfoOffAddr_FirmPara_ELostVoltT, FileItemInfoLen_FirmPara_ELostVoltT    },
    { FileItemInfoOffAddr_FirmPara_Zxot, FileItemInfoLen_FirmPara_Zxot            },
    { FileItemInfoOffAddr_FirmPara_PRth, FileItemInfoLen_FirmPara_PRth                },
    { FileItemInfoOffAddr_FirmPara_PHSU, FileItemInfoLen_FirmPara_PHSU                },
    { FileItemInfoOffAddr_FirmPara_PHSI, FileItemInfoLen_FirmPara_PHSI                },
    { FileItemInfoOffAddr_FirmPara_GSU, FileItemInfoLen_FirmPara_GSU               },
    { FileItemInfoOffAddr_FirmPara_GSI, FileItemInfoLen_FirmPara_GSI               },
    { FileItemInfoOffAddr_FirmPara_U_OS, FileItemInfoLen_FirmPara_U_OS              },
    { FileItemInfoOffAddr_FirmPara_I_OS, FileItemInfoLen_FirmPara_I_OS              },
    { FileItemInfoOffAddr_FirmPara_GP, FileItemInfoLen_FirmPara_GP                  },
    { FileItemInfoOffAddr_FirmPara_GQ, FileItemInfoLen_FirmPara_GQ                  },
    { FileItemInfoOffAddr_FirmPara_GS, FileItemInfoLen_FirmPara_GS                  },
    { FileItemInfoOffAddr_FirmPara_P_PHS, FileItemInfoLen_FirmPara_P_PHS               },
    { FileItemInfoOffAddr_FirmPara_Q_PHS, FileItemInfoLen_FirmPara_Q_PHS               },
    { FileItemInfoOffAddr_FirmPara_P_OS, FileItemInfoLen_FirmPara_P_OS            },
    { FileItemInfoOffAddr_FirmPara_Q_OS, FileItemInfoLen_FirmPara_Q_OS            },
    { FileItemInfoOffAddr_FirmPara_P_PHSMH, FileItemInfoLen_FirmPara_P_PHSMH         },
    { FileItemInfoOffAddr_FirmPara_Q_PHSMH, FileItemInfoLen_FirmPara_Q_PHSMH         },
    { FileItemInfoOffAddr_FirmPara_ChkSum1, FileItemInfoLen_FirmPara_ChkSum1         },
    { FileItemInfoOffAddr_FirmPara_KUrms, FileItemInfoLen_FirmPara_KUrms             },
    { FileItemInfoOffAddr_FirmPara_KIArms, FileItemInfoLen_FirmPara_KIArms            },
    { FileItemInfoOffAddr_FirmPara_KPrms, FileItemInfoLen_FirmPara_KPrms             },
    { FileItemInfoOffAddr_FirmPara_RatedU, FileItemInfoLen_FirmPara_RatedU          },
    { FileItemInfoOffAddr_FirmPara_RatedUrms, FileItemInfoLen_FirmPara_RatedUrms     },
    { FileItemInfoOffAddr_FirmPara_RatedI, FileItemInfoLen_FirmPara_RatedI          },
    { FileItemInfoOffAddr_FirmPara_RatedIrms, FileItemInfoLen_FirmPara_RatedIrms     },
    { FileItemInfoOffAddr_FirmPara_RealU, FileItemInfoLen_FirmPara_RealU             },
    { FileItemInfoOffAddr_FirmPara_RealI, FileItemInfoLen_FirmPara_RealI             },
    { FileItemInfoOffAddr_FirmPara_RealAngle, FileItemInfoLen_FirmPara_RealAngle     },
    { FileItemInfoOffAddr_FirmPara_RealPw, FileItemInfoLen_FirmPara_RealPw          },
    { FileItemInfoOffAddr_VoltRepair_EnOrDis, FileItemInfoLen_VoltRepair_EnOrDis     },
    { FileItemInfoOffAddr_VoltRepair_Rep, FileItemInfoLen_VoltRepair_Rep         },
    { FileItemInfoOffAddr_VoltRepair_Crc, FileItemInfoLen_VoltRepair_Crc         },
    { FileItemInfoOffAddr_VoltRepair_RN8302TIRM, FileItemInfoLen_VoltRepair_RN8302TIRM     },
    { FileItemInfoOffAddr_VoltRepair_RN8207DTIRM, FileItemInfoLen_VoltRepair_RN8207DTIRM    },

    { FileItemInfoOffAddr_Harmonic_FftGP, FileItemInfoLen_Harmonic_FftGP            },
    { FileItemInfoOffAddr_Harmonic_FftCosAngle, FileItemInfoLen_Harmonic_FftCosAngle      },
    { FileItemInfoOffAddr_Harmonic_Crc, FileItemInfoLen_Harmonic_Crc           },

    // dyf 增加南瑞中天特有参数
    { FileItemInfoOffAddr_Xiebo_Flag_EnOrDis, FileItemInfoLen_Xiebo_Flag_EnOrDis},
    { FileItemInfoOffAddr_Xiebo_Err, FileItemInfoLen_Xiebo_Err},
    { FileItemInfoOffAddr_Xiebo_Value, FileItemInfoLen_Xiebo_Value},
    { FileItemInfoOffAddr_Xiebo_Mid_Current, FileItemInfoLen_Xiebo_Mid_Current},
};

const sFileItemInfo_TypeDef FileItemInfo_TemperSchoolPara[] =
{
    { FileItemInfoOffAddr_TemperSchoolPara_chan1, FileItemInfoLen_TemperSchoolPara_chan1         },
    { FileItemInfoOffAddr_TemperSchoolPara_chan2, FileItemInfoLen_TemperSchoolPara_chan2         },
    { FileItemInfoOffAddr_TemperSchoolPara_chan3, FileItemInfoLen_TemperSchoolPara_chan3         },
    { FileItemInfoOffAddr_TemperSchoolPara_chan4, FileItemInfoLen_TemperSchoolPara_chan4        },
};

const sFileItemInfo_TypeDef FileItemInfo_NvRam[] =
{
    {   FileItemInfoOffAddr_NvRam_FristPowOn,   FileItemInfoLen_NvRam_FristPowOn    },
    {   FileItemInfoOffAddr_NvRam_pFile,   FileItemInfoLen_NvRam_pFile     }
};

const sFileItemInfo_TypeDef FileItemInfo_PowDnDataMemory[] =
{
    {   FileItemInfoOffAddr_PowDn_PowDnTime,   FileItemInfoLen_PowDn_PowDnTime     },
    {   FileItemInfoOffAddr_PowDn_EgPiece,   FileItemInfoLen_PowDn_EgPiece   },
    {   FileItemInfoOffAddr_PowDn_CheckMoneyFlag,   FileItemInfoLen_PowDn_CheckMoneyFlag    },
    {   FileItemInfoOffAddr_PowDn_PownDnAllPEgSh,   FileItemInfoLen_PowDn_PownDnAllPEgSh },
    {   FileItemInfoOffAddr_PowDn_PownDnPtPEgSh,   FileItemInfoLen_PowDn_PownDnPtPEgSh     },
    {   FileItemInfoOffAddr_PowDn_PownDnNtPEgSh,   FileItemInfoLen_PowDn_PownDnNtPEgSh },
    {   FileItemInfoOffAddr_PowDn_tWorkBat,   FileItemInfoLen_PowDn_tWorkBat  },
    {   FileItemInfoOffAddr_PowDn_FrzDayTime,   FileItemInfoLen_PowDn_FrzDayTime    },
    {   FileItemInfoOffAddr_PowDn_FrzRmDayTime,   FileItemInfoLen_PowDn_FrzRmDayTime  },
    {   FileItemInfoOffAddr_PowDn_Irms,   FileItemInfoLen_PowDn_Irms  }
};//掉电数据编号（5个掉电脉冲数，小数电量，掉电时间）

const sFileItemInfo_TypeDef FileItemInfo_BackUpCurMoney[] =
{
    {   FileItemInfoOffAddr_BackUpCurMoney_CurSurplusMoney,   FileItemInfoLen_BackUpCurMoney_CurSurplusMoney },
    {   FileItemInfoOffAddr_BackUpCurMoney_CurOverdraftMoney,  FileItemInfoLen_BackUpCurMoney_CurOverdraftMoney    },
    {   FileItemInfoOffAddr_BackUpCurMoney_CurApplyEg,   FileItemInfoLen_BackUpCurMoney_CurApplyEg },
    {   FileItemInfoOffAddr_BackUpCurMoney_Rmday1ApplyEg,   FileItemInfoLen_BackUpCurMoney_Rmday1ApplyEg    },
    {   FileItemInfoOffAddr_BackUpCurMoney_CurSurplusMoneyCrc,   FileItemInfoLen_BackUpCurMoney_CurSurplusMoneyCrc   },
    {   FileItemInfoOffAddr_BackUpCurMoney_CurApplyEgCrc,   FileItemInfoLen_BackUpCurMoney_CurApplyEgCrc },
    {   FileItemInfoOffAddr_BackUpCurMoney_OpCode,   FileItemInfoLen_BackUpCurMoney_OpCode },
    {   FileItemInfoOffAddr_BackUpCurMoney_DateTime,   FileItemInfoLen_BackUpCurMoney_DateTime },
    {   FileItemInfoOffAddr_BackUpCurMoney_PtPEgSh,   FileItemInfoLen_BackUpCurMoney_PtPEgSh },
    {   FileItemInfoOffAddr_BackUpCurMoney_NtPEgSh,   FileItemInfoLen_BackUpCurMoney_NtPEgSh },
    {   FileItemInfoOffAddr_BackUpCurMoney_Qd1QEgSh,   FileItemInfoLen_BackUpCurMoney_Qd1QEgSh },
    {   FileItemInfoOffAddr_BackUpCurMoney_Qd2QEgSh,   FileItemInfoLen_BackUpCurMoney_Qd2QEgSh },
    {   FileItemInfoOffAddr_BackUpCurMoney_Qd3QEgSh,   FileItemInfoLen_BackUpCurMoney_Qd3QEgSh },
    {   FileItemInfoOffAddr_BackUpCurMoney_Qd4QEgSh,   FileItemInfoLen_BackUpCurMoney_Qd4QEgSh },
};//备份数据存储

const sFileItemInfo_TypeDef FileItemInfo_EvtCtxlist[] =
{
    { FileItemInfoOffAddr_EvtCtxlist_PowDn,  FileItemInfoLen_EvtCtxlist_PowDn               },
    { FileItemInfoOffAddr_EvtCtxlist_Clr,  FileItemInfoLen_EvtCtxlist_Clr                 },
    { FileItemInfoOffAddr_EvtCtxlist_SetClock,  FileItemInfoLen_EvtCtxlist_SetClock       },
    { FileItemInfoOffAddr_EvtCtxlist_OpenCover,  FileItemInfoLen_EvtCtxlist_OpenCover         },
    { FileItemInfoOffAddr_EvtCtxlist_OpenTail,  FileItemInfoLen_EvtCtxlist_OpenTail          },
    { FileItemInfoOffAddr_EvtCtxlist_PrgSetPsw,  FileItemInfoLen_EvtCtxlist_PrgSetPsw             },
    { FileItemInfoOffAddr_EvtCtxlist_BroadcastTime,  FileItemInfoLen_EvtCtxlist_BroadcastTime },
    { FileItemInfoOffAddr_EvtCtxlist_MngPlug,  FileItemInfoLen_EvtCtxlist_MngPlug },
    { FileItemInfoOffAddr_EvtCtxlist_MngUpdate,  FileItemInfoLen_EvtCtxlist_MngUpdate },
};//事件记录关联对象属性表

const sFileItemInfo_TypeDef FileItemInfo_EvtCfgPara[] =
{
    { FileItemInfoOffAddr_EvtCfgPara_PowDn,  FileItemInfoLen_EvtCfgPara_PowDn               },
    { FileItemInfoOffAddr_EvtCfgPara_Clr,  FileItemInfoLen_EvtCfgPara_Clr                 },
    { FileItemInfoOffAddr_EvtCfgPara_SetClock,  FileItemInfoLen_EvtCfgPara_SetClock       },
    { FileItemInfoOffAddr_EvtCfgPara_OpenCover,  FileItemInfoLen_EvtCfgPara_OpenCover         },
    { FileItemInfoOffAddr_EvtCfgPara_OpenTail,   FileItemInfoLen_EvtCfgPara_OpenTail      },
    { FileItemInfoOffAddr_EvtCfgPara_PrgSetPsw,  FileItemInfoLen_EvtCfgPara_PrgSetPsw             },
    { FileItemInfoOffAddr_EvtCfgPara_BroadcastTime,  FileItemInfoLen_EvtCfgPara_BroadcastTime },
    { FileItemInfoOffAddr_EvtCfgPara_MngPlug,  FileItemInfoLen_EvtCfgPara_MngPlug },
    { FileItemInfoOffAddr_EvtCfgPara_MngUpdate,  FileItemInfoLen_EvtCfgPara_MngUpdate },
    { FileItemInfoOffAddr_EvtCfgPara_Crc,  FileItemInfoLen_EvtCfgPara_Crc               }
};
//---------事件记录头----------
const sFileItemInfo_TypeDef FileItemInfo_EvtRcdHead[] =
{
    { FileItemInfoOffAddr_EvtRcdHead_PowDn, FileItemInfoLen_EvtRcdHead_PowDn              },
    { FileItemInfoOffAddr_EvtRcdHead_Clr, FileItemInfoLen_EvtRcdHead_Clr                  },
    { FileItemInfoOffAddr_EvtRcdHead_SetClock, FileItemInfoLen_EvtRcdHead_SetClock         },
    { FileItemInfoOffAddr_EvtRcdHead_OpenCover, FileItemInfoLen_EvtRcdHead_OpenCover      },
    { FileItemInfoOffAddr_EvtRcdHead_OpenTail, FileItemInfoLen_EvtRcdHead_OpenTail      },
    { FileItemInfoOffAddr_EvtRcdHead_PrgSetPsw, FileItemInfoLen_EvtRcdHead_PrgSetPsw        },
    { FileItemInfoOffAddr_EvtRcdHead_BroadcastTime, FileItemInfoLen_EvtRcdHead_BroadcastTime  },
    { FileItemInfoOffAddr_EvtRcdHead_MngPlug, FileItemInfoLen_EvtRcdHead_MngPlug  },
    { FileItemInfoOffAddr_EvtRcdHead_MngUpdate, FileItemInfoLen_EvtRcdHead_MngUpdate  },
};
//------事件记录------------
const sFileItemInfo_TypeDef FileItemInfo_EvtRecord[] =
{
    { FileItemInfoOffAddr_EvtRecord_PowDn, FileItemInfoLen_EvtRecord_PowDn             },
    { FileItemInfoOffAddr_EvtRecord_Clr, FileItemInfoLen_EvtRecord_Clr    },
    { FileItemInfoOffAddr_EvtRecord_SetClock, FileItemInfoLen_EvtRecord_SetClock     },
    { FileItemInfoOffAddr_EvtRecord_OpenCover, FileItemInfoLen_EvtRecord_OpenCover    },
    { FileItemInfoOffAddr_EvtRecord_OpenTail, FileItemInfoLen_EvtRecord_OpenTail    },
    { FileItemInfoOffAddr_EvtRecord_PrgSetPsw, FileItemInfoLen_EvtRecord_PrgSetPsw        },
    { FileItemInfoOffAddr_EvtRecord_BroadcastTime, FileItemInfoLen_EvtRecord_BroadcastTime  },
    { FileItemInfoOffAddr_EvtRecord_MngPlug, FileItemInfoLen_EvtRecord_MngPlug  },
    { FileItemInfoOffAddr_EvtRecord_MngUpdate, FileItemInfoLen_EvtRecord_MngUpdate  },
};//事件记录

const sFileItemInfo_TypeDef FileItemInfo_FrzCtxlist[] =
{
    { FileItemInfoOffAddr_FrzCtxlist_Min, FileItemInfoLen_FrzCtxlist_Min       }
}; //冻结

const sFileItemInfo_TypeDef FileItemInfo_FrzRcdHead[] =
{
    { FileItemInfoOffAddr_FrzRcdHead_Min, FileItemInfoLen_FrzRcdHead_Min       }
}; //冻结

const sFileItemInfo_TypeDef FileItemInfo_FrzMinLineHead[] =
{
    { FileItemInfoOffAddr_FrzMinLine0Head, FileItemInfoLen_FrzMinLine0Head },
    { FileItemInfoOffAddr_FrzMinLine1Head, FileItemInfoLen_FrzMinLine1Head },
    { FileItemInfoOffAddr_FrzMinLine2Head, FileItemInfoLen_FrzMinLine2Head },
    { FileItemInfoOffAddr_FrzMinLine3Head, FileItemInfoLen_FrzMinLine3Head },
    { FileItemInfoOffAddr_FrzMinLine4Head, FileItemInfoLen_FrzMinLine4Head },
    { FileItemInfoOffAddr_FrzMinLine5Head, FileItemInfoLen_FrzMinLine5Head },
    { FileItemInfoOffAddr_FrzMinLine6Head, FileItemInfoLen_FrzMinLine6Head },
    { FileItemInfoOffAddr_FrzMinLine7Head, FileItemInfoLen_FrzMinLine7Head }
}; //分钟冻结曲线头

const sFileItemInfo_TypeDef FileItemInfo_FrzRecord[] =
{
    { FileItemInfoOffAddr_FrzRecord_Min, FileItemInfoLen_FrzRecord_Min       },
}; //冻结

//文件信息，排列顺序必须与文件编号保持一致
const sFileInfo_TypeDef FileInfo[] =
{
    {   FileAddr_NvRam,   FileLen_NvRam,   FileItemInfo_NvRam  },
    {   FileAddr_FirmPara,   FileLen_FirmPara,   FileItemInfo_FirmPara   },
    {   FileAddr_TemperSchoolPara,   FileLen_TemperSchoolPara,   FileItemInfo_TemperSchoolPara   },
    {   FileAddr_HighPara,   FileLen_HighPara,   FileItemInfo_HighPara   },
    {   FileAddr_SecretPara,    FileLen_SecretPara,   FileItemInfo_SecretPara },
    {   FileAddr_RatePara,   FileLen_RatePara,   FileItemInfo_RatePara   },

    {   FileAddr_ParaDoc,   FileLen_ParaDoc,   FileItemInfo_ParaDoc    },
    {   FileAddr_ParaCom,   FileLen_ParaCom,   FileItemInfo_ParaCom    },
    {   FileAddr_ParaDisp,   FileLen_ParaDisp,   FileItemInfo_ParaDisp   },
    {   FileAddr_ParaWaste,   FileLen_ParaWaste,   FileItemInfo_ParaWaste  },
    {   FileAddr_ParaOutput,   FileLen_ParaOutput,   FileItemInfo_ParaOutput },
    {   FileAddr_ParaCipherKey,   FileLen_ParaCipherKey,   FileItemInfo_ParaCipherKey  },
    {   FileAddr_EvtReport,   FileLen_EvtReport,   FileItemInfo_EvtReport  },
    {   FileAddr_ParaASCII,   FileLen_ParaASCII,   FileItemInfo_ParaASCII  },
    {   FileAddr_HighState,   FileLen_HighState,   FileItemInfo_HighState  },

    {   FileAddr_EgSh,   FileLen_EgSh,   FileItemInfo_EgSh   },
    {   FileAddr_InterTmp,   FileLen_InterTmp,   FileItemInfo_InterTmp   },
    {   FileAddr_CurStat,   FileLen_CurStat,   FileItemInfo_CurStat    },
    {   FileAddr_PowDnDataMemory,   FileLen_PowDnDataMemory,   FileItemInfo_PowDnDataMemory    },
    {   FileAddr_BackUpEgSh,   FileLen_BackUpEgSh,   FileItemInfo_EgSh   },
    {   FileAddr_BackUpCurMoney,   FileLen_BackUpCurMoney,   FileItemInfo_BackUpCurMoney },
    {   FileAddr_EvtCtxlist,   FileLen_EvtCtxlist,   FileItemInfo_EvtCtxlist },
    {   FileAddr_EvtCfgPara,   FileLen_EvtCfgPara,   FileItemInfo_EvtCfgPara },
    {   FileAddr_EvtRcdHead,   FileLen_EvtRcdHead,   FileItemInfo_EvtRcdHead },
    {   FileAddr_EvtRecord,   FileLen_EvtRecord,   FileItemInfo_EvtRecord  },

    {   FileAddr_FrzCtxlist,   FileLen_FrzCtxlist,   FileItemInfo_FrzCtxlist },
    {   FileAddr_FrzRcdHead,   FileLen_FrzRcdHead,   FileItemInfo_FrzRcdHead },
    {   FileAddr_FrzMinLineHead,   FileLen_FrzMinLineHead,   FileItemInfo_FrzMinLineHead },
    {   FileAddr_FrzRecord,   FileLen_FrzRecord,   FileItemInfo_FrzRecord  }
};

//=================================

ErrorStatus fnFile_Read(u8 FileId, u32 OffAddr, void *Dst, u32 Len)
{
    if (FileId >= FileId_Max)
    {
        return (ERROR);
    }
    if ((OffAddr + Len) > FileInfo[FileId].Len)
    {
        return (ERROR);
    }
    return (fnMemory_Read(Dst, FileInfo[FileId].StartAddr + OffAddr, Len));
}

ErrorStatus fnFile_Write(u8 FileId, u32 OffAddr, void *Src, u32 Len)
{
    if (FileId >= FileId_Max)
    {
        return (ERROR);
    }
    if ((OffAddr + Len) > FileInfo[FileId].Len)
    {
        return (ERROR);
    }
    return (fnMemory_Write(FileInfo[FileId].StartAddr + OffAddr, Src, Len));
}

ErrorStatus fnFileItem_Read(u8 FileId, u8 nItem, void *Dst)
{
    if (FileId >= FileId_Max)
    {
        return (ERROR);
    }

    return (fnMemory_Read(Dst, FileInfo[FileId].StartAddr + FileInfo[FileId].pItemInfo[nItem].OffAddr, FileInfo[FileId].pItemInfo[nItem].Len));
}

ErrorStatus fnFileItem_Write(u8 FileId, u8 nItem, void *Src)
{
    if (FileId >= FileId_Max)
    {
        return (ERROR);
    }

    return (fnMemory_Write(FileInfo[FileId].StartAddr + FileInfo[FileId].pItemInfo[nItem].OffAddr, Src, FileInfo[FileId].pItemInfo[nItem].Len));
}

ErrorStatus fnFile_Clr(u8 FileId)
{
    u32 OffAddr, OnceLen;
    u8  Buf[256];

    if (FileId >= FileId_Max)
    {
        return (ERROR);
    }

    Std_Memset(Buf, 0, sizeof(Buf));

    OffAddr = 0;
    while (OffAddr < FileInfo[FileId].Len)
    {
        fnWDT_Restart();
        if ((OffAddr + sizeof(Buf)) > FileInfo[FileId].Len)
        {
            OnceLen = FileInfo[FileId].Len - OffAddr;
        }
        else
        {
            OnceLen = sizeof(Buf);
        }
        fnFile_Write(FileId, OffAddr, Buf, OnceLen);
        OffAddr += OnceLen;
        fnWDT_Restart();
    }

    return (SUCCESS);
}

void fnEvtClistDefault_Write(void)
{
    u8 i;

    for (i = 0; i < FileItemInfoNum_Evt_Max; i++)
    {
        fnFile_Write(FileId_EvtCtxlist, FileItemInfo_EvtCtxlist[i].OffAddr, EvtDefaultlist[i].Addr, EvtDefaultlist[i].Len);

        //设置关联对象属性表对应事件记录需清零，清事件记录头
        fnWDT_Restart();
    }
    fnFile_Clr(FileId_EvtRcdHead) ;
    Bkgrd.PubData.tWorkBat = 0;
}

void fnFrzClistDefault_Write(void)
{
    u8 i ;

    //关联对象属性表对应冻结记录头清零
    fnFile_Clr(FileId_FrzRcdHead) ;
    fnEvent_Clr_Status(0xFF, 0xFF);

    for (i = 0; i < FileItemInfoNum_Frz_MAX; i++)
    {
        fnFile_Write(FileId_FrzCtxlist, FileItemInfo_FrzCtxlist[i].OffAddr, FrzDefaultlist[i].Addr, FrzDefaultlist[i].Len);

        if (i == FileItemInfoNum_Frz_MinFrz) // 分钟冻结曲线头清零
        {
            Std_Memset((u8 *)&RFrzMinLine.Cycle[0], 0x00, MAX_FRZMIN_LINE);
            fnFile_Clr(FileId_FrzMinLineHead) ;
            //--------默认曲线0数据------------
            fnFile_Write(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[0].OffAddr, (u8 *)&FrzMinLineDefault0, sizeof(sFrzMinLinePara_TypeDef));
            RFrzMinLine.Cycle[0] = FrzMinLineDefault0.Cycle;

            //--------默认曲线1数据------------
            fnFile_Write(FileId_FrzMinLineHead, FileItemInfo_FrzMinLineHead[1].OffAddr, (u8 *)&FrzMinLineDefault1, sizeof(sFrzMinLinePara_TypeDef));
            RFrzMinLine.Cycle[1] = FrzMinLineDefault1.Cycle;

            fnCrc_Check(0, (u8 *)&RFrzMinLine.Cycle[0], sizeof(sFrzMinCycle_TypeDef) -2, (u8 *)&RFrzMinLine.Crc);
        }
        fnWDT_Restart();
    }
}

void fnFile_Init(u8 Flag)
{
    u8 Tmp[4];
    u8 i, len;

    if (Bkgrd.PubData.Active == BKGRD_ACTIVE_POWDN)
    {
        return;
    }

    for (i = 0; i < 3; i++)
    {
        fnFile_Read(FileId_NvRam, 0, &Tmp[0], 4);
        if (Std_Memcmp(&FristPowOn[0], &Tmp[0], 4) == SUCCESS)
        {
            return;
        }
        fnFile_Read(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_FristPowOnBak1, &Tmp[0], 4);
        if (Std_Memcmp(&FristPowOn[0], &Tmp[0], 4) == SUCCESS)
        {
            return;
        }
        fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_FristPowOnBak2, &Tmp[0], 4);
        if (Std_Memcmp(&FristPowOn[0], &Tmp[0], 4) == SUCCESS)
        {
            return;
        }
        fnWDT_Restart();
    }
    Wdog.T_WDOG = 60000;

    for (i = 0 ; i < FileId_Max ; i++)
    {
        fnWDT_Restart();
        if ((i == FileId_FirmPara) && (Flag == File_FirstInit))
        {
            fnMeasure_FirmParaInit(0);
        }
        else if ((i == FileId_TemperSchoolPara) && (Flag == File_FirstInit))
        {
            fnFile_Write(FileId_TemperSchoolPara, 0, (u8 *)&TemperSchoolParaDefault, FileLen_TemperSchoolPara);
        }
        else if (i == FileId_HighPara)
        {
            if (Flag == File_FirstInit)
            {
                fnFile_Write(FileId_HighPara, 0, (u8 *)&HighParaDefault, FileLen_HighPara);

                fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef));
                fnCrc_Check(0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef) - 2, (u8 *)&RTCPara.Crc);
                fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef));
            }
            else
            {
                fnFile_Write(FileId_HighPara, 0, (u8 *)&HighParaDefault, FileLen_HighPara - 50);

                fnFile_Read(FileId_HighPara, FileItemInfoOffAddr_HighPara_RTCDota0, (u8 *)&RTCPara.RTCDota0, sizeof(sRTCParaE2_TypeDef));
            }
        }
        else if (i == FileId_SecretPara)
        {
            fnFile_Write(FileId_SecretPara, 0, (u8 *)&SecretParaDefault, FileLen_SecretPara);
            Std_Memset((u8 *)&Secret, 0x00, sizeof(sSecret_TypeDef));
        }

        //-------------------
        else if (i == FileId_ParaDoc)
        {
            fnFile_Write(FileId_ParaDoc, 0, (u8 *)&DocParaDefault, FileLen_ParaDoc);
        }
        else if (i == FileId_ParaCom)
        {
            if (Flag == File_FirstInit)
            {
                Std_Memcpy((u8 *)&CommPara, (u8 *)&ComParaDefault, FileLen_ParaCom);
                fnCrc_Check(0, (u8 *)&CommPara, FileLen_ParaCom - 2, (u8 *)&CommPara.Crc);
                fnFile_Write(FileId_ParaCom, 0, (u8 *)&CommPara, FileLen_ParaCom);
            }
            else
            {
                //----------通讯初始化时不初始化通讯地址-------------------
                len = FileLen_ParaCom - FileItemInfoLen_ComPara_ComAddr;
                Std_Memcpy((u8 *)&CommPara.Ir1Style, (u8 *)&ComParaDefault + FileItemInfoLen_ComPara_ComAddr, len);
                fnCrc_Check(0, (u8 *)&CommPara, FileLen_ParaCom - 2, (u8 *)&CommPara.Crc);
                fnFile_Write(FileId_ParaCom, FileItemInfoOffAddr_ComPara_Ir1Style, (u8 *)&CommPara.Ir1Style, len);
            }
        }
        else if (i == FileId_ParaDisp)
        {
            fnFile_Write(FileId_ParaDisp, 0, (u8 *)&DispParaDefault, FileLen_ParaDisp);
        }
        else if (i == FileId_CurStat)
        {
            fnFile_Clr(i) ;
            Std_Memset((u8 *)&Stat, 0x00, sizeof(sStat_TypeDef));
        }
        else if ((i == FileId_ParaWaste) || (i == FileId_HighState))
        {
            fnFile_Clr(i) ;
        }
        else if (i == FileId_ParaOutput)
        {
            fnFile_Write(FileId_ParaOutput, 0, (u8 *)&OutputParaDefault, FileLen_ParaOutput);
        }
        else if (i == FileId_ParaCipherKey)
        {
            fnFile_Write(FileId_ParaCipherKey, 0, (u8 *)&CipherKeyParaDefault[0], 3);
        }
        else if (i == FileId_EvtReport)
        {
            fnFile_Clr(FileId_EvtReport);
            Std_Memcpy((u8 *)&EvtRptData, (u8 *)&EvtReportDefault, sizeof(sEvtRptPara_TypeDef));
            fnCrc_Check(0, (u8 *)&EvtRptData.Para.AtiveAllow, sizeof(sEvtRptPara_TypeDef) - 2, (u8 *)&EvtRptData.Para.Crc);
            fnFile_Write(FileId_EvtReport, 0, (u8 *)&EvtRptData.Para.AtiveAllow, sizeof(sEvtRptPara_TypeDef));
        }
        else if ((i == FileId_ParaASCII) && (Flag == File_FirstInit)) //通讯初始化时不初始化ASCII码相关参数
        {
            fnFile_Write(FileId_ParaASCII, 0, (u8 *)&ASCIIParaDefault, FileLen_ParaASCII);
        }
        else if (i == FileId_EvtCfgPara)
        {
            Std_Memcpy((u8 *)&Trim, (u8 *)&EvtCfgParaDefault, FileLen_EvtCfgPara);
            fnCrc_Check(0, (u8 *)&Trim, FileLen_EvtCfgPara - 2, (u8 *)&Trim.Crc);

            fnFile_Write(FileId_EvtCfgPara, 0, (u8 *)&Trim, FileLen_EvtCfgPara);
        }
        else if (i == FileId_EvtCtxlist)
        {
            fnEvtClistDefault_Write();
        }
        else if (i == FileId_FrzCtxlist)
        {
            fnFrzClistDefault_Write();
        }
        else if ((i == FileId_InterTmp) || (i == FileId_PowDnDataMemory))
        {
            fnFile_Clr(i);
        }

        //else fnFile_Clr(i);
        fnWDT_Restart();
    }

    fnWDT_Restart();
    fnEnergy_DataInit();
    fnWrite_PowDn_FrzRmDayTime();
    fnWrite_PowDn_FrzDayTime();

    fnWDT_Restart();
    fnFile_Clr(FileId_NvRam);
    fnFile_Write(FileId_NvRam, 0, (u8 *)&FristPowOn[0], 4);
    fnFile_Write(FileId_SecretPara, FileItemInfoOffAddr_SecretPara_FristPowOnBak1, (u8 *)&FristPowOn[0], 4);
    fnFile_Write(FileId_HighPara, FileItemInfoOffAddr_HighPara_FristPowOnBak2, (u8 *)&FristPowOn[0], 4);
}
