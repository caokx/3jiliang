
#ifndef _POWER_UP_DOWN_H
#define _POWER_UP_DOWN_H

#ifdef   _POWER_UP_DOWN_GLOBALS
#define  POWER_UP_DOWN_EXT
#else
#define  POWER_UP_DOWN_EXT  extern
#endif

typedef enum
{
    BKGRD_ACTIVE_POWON          = 0x00, //--0=正常工作
    BKGRD_ACTIVE_POWDN          = 0x01, //--1=修眠
    BKGRD_ACTIVE_POWUP          = 0x02, //--2=上电恢复
} eBkgrd_Flag_TypeDef;

typedef enum
{
    BKGRD_INACTIVE_NOACTION     = 0x00, //无需操作
    BKGRD_INACTIVE_SAVE         = 0x01, //保存电能数据
    BKGRD_INACTIVE_LOWPOWER     = 0x02, //掉电
    BKGRD_INACTIVE_POWERONINIT  = 0x03  //上电初始化
} eBkgrd_InActive_TypeDef;

#define End_State           0x0
#define Start_State         0x1
#define Running_State       0x2
#define IRComRun_State      0x03

typedef  struct
{
    struct InactiveData_Type
    {
        u8      ActiveState;    //休眠时系统是否被唤醒标志
        u8      ActiveInit;     //唤醒时是否被初始化
        u16     ActiveStamp;    //休眠唤醒时戳
        u8      QLossVolTime;   // 停电后全失压检测时间
        u16     InactiveStamp;
        s32     PowerDnTimer;   //停电时间，超过7天后不支持红外抄表及唤醒
        u8      IrWakeupFlag;   // 红外唤醒标志
        u32     IrWakeupStamp;  // 红外唤醒延时
        u8      tCheckIR;       // 红外唤醒时间，5S唤醒一次
        u16     CheckIRStamp;   // 红外接收管唤醒判断
        u8      PowerErrFlag;   // 电源异常标志
        u16     BackupBat;      // 保存电池电压备份
        u8      tCheckBat;      // 电池电压检测，每5S检测1次
        u16     tCheckSysConf;      //停电SysConfCheck ，每30min检测1次
    } PubData;
    struct Event_TYPE
    {
        u8  ExeFlag;
        u8  SleepFlag;
        u32 EventFlag;
        u8  OpenFlag;       // 开盖、端钮有被打开
        u8  fChange;        // 01 按键按下  02 秒进位  04 表盖打开  08 端钮打开 10 红外唤醒检测
    } InactiveFlag;

    struct MngPlug_Type
    {
        u8  OldEsam[8];
        u8  NewEsam[8];
        u16 Sta;
        u32 LstEvtFlag;
        u8  RevEsam;
    } Mng;

    sEvtPwnCoverTailTypedef     EvtPwn;
} sInactive_TypeDef;

//---

extern void fnPowerUp_Check(void);
extern void fnPowerUp_AppInit(void);
extern void fnPowerDown_Check(void);
extern void fnPowerDown_Handle(void);
extern void fnPowerDown_Inactive(void);
extern void fnPowerDown_SetWakeOpIO(void);
extern void fnPowerDown_SleepWakeOpIO(void);
extern void fnPowerUp_RTCParaInit(void) ;

#endif
