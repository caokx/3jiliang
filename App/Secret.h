
#ifndef _SECRET_H
#define _SECRET_H

#ifdef   _SECRET_GLOBALS
#define  SECRET_EXT
#else
#define  SECRET_EXT  extern
#endif

#define PRGTime_AutoDec           TRUE   //  TRUE = 软编程有效时间自动扣减/  FALSE =  软编程有效时间不扣减，清零或手动退出

typedef struct
{
    u32 tLinkDly[4];    //应用连接超时剩余时间 单位:秒
    u32 tESAMDly;       //ESAM会话剩余时间。单位:秒

    u32 tLink[4];       //应用连接协商超时时间单位:秒
    u8  LinkChan;       //建立应用连接通道号
    u8  Auth_object;        //应用连接建立安全认证机制
} sLinkData_TypeDef;

typedef struct
{
    u8  nPswRetry[2];       //重试次数          (hyg) HEX
    u16 tPswFailClose[2];   //本次密码错误封锁倒计时，单位：分钟(hyg) HEX
    u16 tPrgKeyValid;       //编程开关作用时间倒计时，单位：分钟(hyg) HEX
    u16 tPrgKeyLock;        //编程开关闭锁时间倒计时，单位：分钟(hyg) HEX
    u8  RemoteValid;    //身份认证是否有效状态
    u8  nMacErr;         //MAC错次数
    sLinkData_TypeDef  Master;  //主站
    sLinkData_TypeDef  Terminal;  //终端
    u16 tIRRequestDly;  // 红外或模拟终端请求倒计时

    u32 tIRDly;         //红外远程认证失效时间倒计时。单位:秒
    u32 tTerminalDly;      //终端身份认证剩余时间
    u8  Chan;       //通道类型,当前通讯通道号
    u8  CA;
    u8  NeedIdentityAuth;
} sSecret_TypeDef;

extern sSecret_TypeDef          Secret;

//-----------------------------------------------------
extern void fnSecret_Init(void);
extern ErrorStatus fnSecret_Verify(u8 LimitPA, u8 PA, u8 *Pn);
extern void fnSecret_Exec(void);
extern void fnICEsam_MacErrInc(ErrorStatus Err);
extern u8 fnConnect_Secret(u32 timeout_nego, u8 auth_object);
extern void fnConnect_SecretClr(void);
extern u8 fnConnectDis_SecretClr(void);

extern u8 fnGet_ConnSta(void);
extern void fnCHK_LinkDly(void);
extern void fnCHK_ESAMDly(void);
#endif // _DL645_SECRET_H
