
#ifndef __DL645B_COM_H
#define __DL645B_COM_H

#ifdef   DL645B_COM_GLOBALS
#define  DL645B_EXT
#else
#define  DL645B_EXT  extern
#endif

#define DL645B_FRAME_MAXLEN 170

#define DL645B_LEADERCODE       0xFE    //前导码
#define DL645B_LEADERCODE_LEN   4       //前导码长度
#define F_Comm1Event            1       // 正在通讯标志bit0
#define F_Comm2Event            2       // 正在通讯标志bit1
#define F_Comm3Event            4       // 正在通讯标志 红外bit2
#define F_Comm4Event            8       // 正在通讯标志 载波bit3

typedef enum
{
    DL645B_ERRINFO_MISC      = 0x01,
    DL645B_ERRINFO_DATA      = 0x02,
    DL645B_ERRINFO_PSW       = 0x04,
    DL645B_ERRINFO_BPS       = 0x08,
    DL645B_ERRINFO_TZONE     = 0x10,
    DL645B_ERRINFO_POT       = 0x20,
    DL645B_ERRINFO_FL        = 0x40,

    DL645B_ERRINFO_SEQDATA   = 0x80,

    DL645B_ERRINFO_OK        = 0x00
} eDL645B_ErrInfo_TypeDef;

typedef enum
{
    DL645B_SERRINFO_MISC            = 0x0001,
    DL645B_SERRINFO_RepRecharg      = 0x0002,
    DL645B_SERRINFO_VerifyErr       = 0x0004,
    DL645B_SERRINFO_RadiusErr       = 0x0008,
    DL645B_SERRINFO_UserNoErr       = 0x0010,
    DL645B_SERRINFO_RechargCountErr = 0x0020,
    DL645B_SERRINFO_RegrateErr      = 0x0040,
    DL645B_SERRINFO_FlashAdErr      = 0x0080,
    DL645B_SERRINFO_RemoteClose     = 0x0100,
    DL645B_SERRINFO_SetPwdErr       = 0x8000,

    DL645B_SERRINFO_OK              = 0x0000
} eDL645B_SErrInfo_TypeDef;

typedef enum
{
    DL645B_ContExeInfo_DirectOn     = 0x0001,       // 直接合闸
    DL645B_ContExeInfo_AllowOn      = 0x0002,       // 允许合闸
    DL645B_ContExeInfo_DirectOff    = 0x0004,       // 直接跳闸
    DL645B_ContExeInfo_DelayOff     = 0x0008,       // 延时跳闸（跳闸延时时间）
    DL645B_ContExeInfo_ResumeOff    = 0x0010,       // 跳闸自动恢复
    DL645B_ContExeInfo_ContrOff     = 0x0020,       // 延时跳闸（大电流）
    DL645B_ContExeInfo_KeepEg       = 0x0100,       // 保电
    DL645B_ContExeInfo_KeepEgOff    = 0x0200,       // 保电解除
    DL645B_ContExeInfo_Alarm        = 0x0400,       // 报警
    DL645B_ContExeInfo_AlarmOff     = 0x0800,       // 报警解除

    DL645B_ContExeInfo_NoData       = 0x0000,       // 无信息返回
} eDL645B_ContExeInfo_TypeDef;

typedef enum
{
    DL645B_ContErrInfo_RemoteClose  = 0x0001,       // 电表挂起
    DL645B_ContErrInfo_MacErr       = 0x0002,       // MAC错误
    DL645B_ContErrInfo_PswErr       = 0x0004,       // 密码错误/未授权
    DL645B_ContErrInfo_RemoteFail   = 0x0008,       // 身份认证超时
    DL645B_ContErrInfo_RunTFail     = 0x0010,       // 执行时间无效
    DL645B_ContErrInfo_GataOffErr   = 0x0020,       // 跳闸失败（保电）
    DL645B_ContErrInfo_ResumeOffErr = 0x0040,       // 跳闸自动恢复命令执行失败（保电）
    DL645B_ContErrInfo_ResumeTFail  = 0x0080,       // 跳闸自动恢复时间无效
    DL645B_ContErrInfo_ResumeExeFail = 0x0100,      // 跳闸自动恢复命令执行失败（跳闸）

    DL645B_ContErrInfo_OK = 0x0000,
} eDL645B_ContErrInfo_TypeDef;

//====================
typedef struct
{
    u8  Flag;   //D0=1表示含有多费率
    u8  DI2;
    u16  OI_698;
    u32 OffAddr;
} sDl645B_RmEgSh_TypeDef;   //定义读电能数据的常量结构

typedef struct
{
    u8  Flag;   //D0=1表示含有多费率
    u8  DI2;
    u32 OffAddr;
} sDl645B_RmNeed_TypeDef;   //定义读电能数据的常量结构

typedef struct
{
    u16 Len;
    u32 OffAddr;
} sDl645B_EvRecord_TypeDef;

typedef struct
{
    u16 Len;
    u32 OffAddr;
    u8  MaxEventCount;      // 最大事件记录次数
} sDl645B_MisEvRecord_TypeDef;

typedef struct
{
    u8  Flag;
    u16 Len;
    u32 OffAddr;
} sDl645B_Frz_TypeDef;

typedef struct
{
    u8  FileId;
    u8  pFileOffAddr;
    u8  MaxFrz;
} sDl645B_FrzFile_TypeDef;

typedef struct
{
    u32 DI;
    u8  Flag;       //D8=1可写、D7=1可读、D0 = 1 需效验数据的BCD码
    u8  FileId;
    u16 Len;
    u32 OffAddr;
} sDl645B_ParaVar_TypeDef;

typedef struct
{
    u16 DeviceAd;
    u8  Len;
    u32 OffAddr;
} sFirmPara_TypeDef;   //

typedef struct
{
    u32 DI;
} sDl645B_HWAllowData_TypeDef;

typedef struct
{
    u8  Remain;
    u32 ReadAddress;
} sDl645B_Profile_SubSeq;

typedef struct
{
    u8  Remain;
    u16 tInterVal;
    u32 ReadAddress;
    sDF15 TimeClock;
    u8  Buf[16];
} sDl645B_Curve_strSeq;

typedef struct
{
    sDF15                   ReadEndClock;
    sDl645B_Curve_strSeq    CurveAddress[2];
} sDl645B_Curve_SubSeq;

typedef struct
{
    __IO uint32_t Buf[32];
} sDl645B_RTC_TypeDef;

#define Dl645B_RTCCom             ((sDl645B_RTC_TypeDef     *) RTC_BASE )

extern ErrorStatus  fnDl645B_FrameCheck(sFrmDl645B_TypeDef *pCheck, u16 *usDataLen);
extern u16 fnDl645B_Exec(u8 ComPort, sFrmDl645B_TypeDef *RxFrm);

extern eDL645B_ErrInfo_TypeDef fnDl645_GetRmEgSh(u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len);
extern eDL645B_ErrInfo_TypeDef fnDl645_GetVar(u8 DI2, u8 DI1, u8 DI0, u8 *Dst, u16 *Len);
extern eDL645B_ErrInfo_TypeDef fnDl645_GetMiscEv(u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len);
extern eDL645B_ErrInfo_TypeDef fnDl645_GetParaVar(u8 DI2, u8 DI1, u8 DI0, u8 *Dst, u16 *Len);
extern eDL645B_ErrInfo_TypeDef fnDl645_GetFrz(u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len);
extern eDL645B_ErrInfo_TypeDef fnDl645_GetRmNeed(u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len);
extern void fnDl645B_Modify(u8 *pModify, u16 Len, u8 OpFlag);
extern ErrorStatus  fnDl645_POTTable_Check(sPOTTable_TypeDef *POTTab, u8 nPOTTab);
extern  eDL645B_ErrInfo_TypeDef fnDl645_GetVolEv(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len);
extern  eDL645B_ErrInfo_TypeDef fnDl645_GetInPhaEv(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len);
extern  eDL645B_ErrInfo_TypeDef fnDl645_GetUnblEv(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len);
extern  eDL645B_ErrInfo_TypeDef fnDl645_GetCurEv(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len);
extern  eDL645B_ErrInfo_TypeDef fnDl645_GetWaveEv(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len);
extern  eDL645B_ErrInfo_TypeDef fnDl645_GetOverPfEv(u8 DI3, u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len);
extern  eDL645B_ErrInfo_TypeDef fnDl645_GetEv(u8 DI2, u8 DI1, u8 DI0, u8 Seq, u8 *Dst, u16 *Len);
extern  void fnDl645B_Inverse(u8 *Buf, u8 Len);
extern  eDL645B_ErrInfo_TypeDef fnDl645_GetGateOffEv(u8 DI2, u8 DI1, u8 DI0, u8 *Dst, u16 *Len);
extern  eDL645B_ErrInfo_TypeDef fnDl645_GetGateOnEv(u8 DI2, u8 DI1, u8 DI0, u8 *Dst, u16 *Len);
extern  eDL645B_ErrInfo_TypeDef fnDl645_GetEsamInfo(u32 Oad, u8 *Dst, u16 *Len);
extern  ErrorStatus fnDl645B_JudgeClockNoWeek(u8 Start, u8 *Ck, u8 Len);
extern eDL645B_ErrInfo_TypeDef fnDl645_PutParaVar(sFrmDl645B_TypeDef *RxFrm);
extern ErrorStatus fnDl645B_AddrCheck(u8 *ComAddr, u8 AFN);

#endif // __DL645B_COM_H
