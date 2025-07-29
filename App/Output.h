#ifndef _OUTPUT_H
#define _OUTPUT_H

typedef enum
{
    OUTPUTPORT_RELAY            = 0x00,
    OUTPUTPORT_BJRELAY          = 0x01,
    OUTPUTPORT_OPTICAL          = 0x02,
    OUTPUTPORT_ALARMLED         = 0x03,
    OUTPUTPORT_BEEP             = 0x04,
    OUTPUTPORT_RELAYLED         = 0x05,
    OUTPUTPORT_NUM              = 0x06
} eOutput_Style_TypeDef;

typedef struct
{
    u16 nSignal;      //记录当前的信号状态  0001  0002 对应拉合闸 0004 对应报警继电器 0010 对应时段输出  0100 对应报警灯 1000对应声音报警 2000对应继电器灯
    u16 lSignal;      //记录上次的信号状态

    struct sOutputPubData_TypeDef
    {
        u8      RealErrFlag;  // 继电器状态错误，即继电器命令状态和实际状态不符合
        u8      RealErrCount;// 继电器错误操作次数，防止因检测线断一直进行拉合闸
        u8      RealErrTime; // 继电器错误持续时间
        u8      OpGataAllow;    //继电器允许操作临界电压
        u8      SafeCurFlag;    // 电流门限不为零标志
        u32     GateOffRemainTime;          // 跳闸延时时间

        u32     GataOffResumeTime;          // 跳闸自动恢复时间
        u8          nCheckGata;                 // 继电器状态检测记数
        u8      CheckGataSta;               // 继电器状态检测
        u8      CheckGataSysStamp;              // 继电器检测延时
        u8      GataCommandDo;                  // 继电器命令执行标志
    } PubData;

    struct sOutputObject_TypeDef
    {
        u16 Style;    //Bit15：0脉冲输出1保持输出 Bit14~0：脉冲输出宽度，单位ms
        u16 Trigger;  //触发表达式，
        u16 Stamp;    //输出时将时标记录到时戳
    } Object[6];      //0继电器；1光藕；2报警指示灯；3蜂鸣器;

    struct sOutputPriPara_TypeDef
    {
        u16  RelaysOutAlarm[5];
        u16  LightAlarm[5];
        u16  SoundAlarm[5];
        u32 GataSafeCur;     //拉合闸电流控制门限
        u16 tSafeGata;
        u16  Crc;
    } PriPara;
} sOutput_TypeDef;

extern void fnOutput_Init(void);
extern void fnOutput_Exec(void);
extern void fnOutput_Reset(u8 Object);
extern void fnOutput_CheckGataSta(void);
extern void fnOutput_RelayPinCheck(void);
#endif
