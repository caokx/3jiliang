
#ifndef  _KEY_H
#define  _KEY_H

#ifdef   _KEY_GLOBALS
#define  KEY_EXT
#else
#define  KEY_EXT  extern
#endif

typedef enum
{
    KEY_VAL_PRG     = (1 << 0), //编程按键
    KEY_VAL_TURNA   = (1 << 1), //键显按钮短按
    KEY_VAL_TURNAC  = (1 << 2), //轮显按键长按
    KEY_VAL_TURNB   = (1 << 3), //键显按钮短按
    KEY_VAL_TURNBC  = (1 << 4), //键显按钮长按
    KEY_VAL_SHELLVS = (1 << 5), //开表壳电平状态追随
    KEY_VAL_SHELL   = (1 << 6), //开表壳按键操作判定
    KEY_VAL_JUNBOXVS = (1 << 7), //端子开盖键状态追随
    KEY_VAL_JUNBOX  = (1 << 8), //端子开盖键判定
    KEY_VAL_CARD    = (1 << 9), //本地费控表卡片插入判定
    KEY_Relay_Ctrl  = (1 << 10), //继电器保电合闸控制
    KEY_VAL_STROMANVS = (1 << 11),         //磁场影响事件状态追随
    KEY_VAL_STROMAN = (1 << 12),         //磁场影响事件判定结果位
    KEY_VAL_RelayGataCheck = (1 << 13),  //继电器开合状态检测
    //  KEY_BJRelay_Ctrl= (1<<14),  // 达到报警金额2后按键合闸
    KEY_VAL_CTRLMODUPLGCHKVS    = (1 << 14), //管理模组拔插状态跟随
    KEY_VAL_CTRLMODUPLGCHK  = (1 << 15), //管理模组拔插
    KEY_PRESS       = (KEY_VAL_PRG + KEY_VAL_TURNA + KEY_VAL_TURNB + KEY_VAL_SHELL + KEY_VAL_JUNBOX + KEY_VAL_CARD + KEY_Relay_Ctrl + KEY_VAL_CTRLMODUPLGCHK),  //用于判断是否有键按下
    KEY_RELEASE     = (~KEY_PRESS)      //用于判断是否有键释放
} eKeyVal_TypeDef;

typedef struct
{
    u8      KeyProg_Scan;           //编程按键采样扫描结果
    u8      KeyTurn_Scan1;          //键显按键采样扫描结果上翻键
    u8      KeyTurn_Scan2;          //键显按键采样扫描结果下翻键
    u8      KeyShell_Scan;          //开表壳采样扫描结果。
    u8      KeyJUNBOX_Scan;         //开端子盖采样扫描结果
    u8      KeyCARD_Scan;           //卡片插入的扫描检测
    u8      StrongMan_Scan;         //强磁场的相关检测
    u16     Press;                  //按键按下，去抖
    u16     Release;                //按键释放
    u16     KeyTurn_Time1;          //手动清需量操作时判定上翻按键时间用
    u16     KeyTurn_Time2;          //手动清需量操作时判定下翻按键时间用
    u16     STROMAN_Time;           //强磁检测延时时间
    u8      RelayGataCheck;         //继电器检测
    u8      CtrlModuPlgChk;         //管理模组拔插
    u16     MngPlgUpTmr;            //管理模组拔延时时间
    u16     MngPlgDnTmr;            //管理模组插延时时间
} sKey_TypeDef;                     //KEY_TYPE;

KEY_EXT sKey_TypeDef Key;

//==============================================
extern void fnKey_Init(void);
extern void fnKey_Scan(void);

#endif  //_KEY_H
