
#ifndef  _APP_H
#define  _APP_H

//------------------------------
#define MAX_FL                    0//12 //最大费率数
#define MAX_FLPrice               0 //最大费率电价数
#define DEFAULT_FL                    1//   默认费率数

#define MAX_POTTABLE                  0     //最大时段表数

#define MAX_POT                     0    //最大时段数
#define MAX_TIMEZONE                  0     //最大时区数
#define MAX_HOLIDAY                 0   //最大公共假日数

#define MAX_CYCDISP                 99    //最大轮显项数
#define MAX_KEYDISP                 99    //最大键显项数

#define MAX_EVSTAT                15    //最大事件统计
#define MAX_EVRECORD                  10    //最大事件记录

#define MAX_POWDN_EVRECORD          100      //最大掉电事件记录
#define MAX_PRG_EVRECORD            10      //最大编程事件记录
#define MAX_CLR_EVRECORD            10      //最大清零事件记录
#define MAX_NEEDCLR_EVRECORD          10      //最大需量清零事件记录
#define MAX_EVENTCLR_EVRECORD       10      //最大事件清零事件记录
#define MAX_SETCLOK_EVRECORD        10      //最大校时事件记录
#define MAX_PRGPOTTABLE_EVRECORD    10      //最大时段编程事件记录
#define MAX_PRGTIMEZONE_EVRECORD    10      //最大时区编程事件记录
#define MAX_PRGWEEKEND_EVRECORD     10      //最大周休日编程事件记录
#define MAX_PRGHOLIDAY_EVRECORD     10       //最大公共假日编程事件记录
#define MAX_PRGP_EVRECORD           10      //最大有功组合特征字编程事件记录
#define MAX_QRGP_EVRECORD         10      //最大无功组合1特征字编程事件记录
#define MAX_PRGRMDAY_EVRECORD       10      //最大结算日编程事件记录
#define MAX_OPENCOVER_EVRECORD      10      //最大开盖事件记录
#define MAX_OPENTAIL_EVRECORD       10      //最大开端钮盖事件记录
#define MAX_GATEOFF_EVRECORD        10      //最大跳闸事件记录
#define MAX_GATEON_EVRECORD         10      //最大合闸事件记录
#define MAX_BUYEG_EVRECORD          10      //最大购电量事件记录
#define MAX_BUYMONEY_EVRECORD       10      //最大购金额事件记录
#define MAX_PrgRatePrice_EVRECORD     10      //最大费率编程事件记录
#define MAX_PrgLadderPrice_EVRECORD 10    //最大阶梯电价编程事件记录
#define MAX_PrgSetPsw_EVRECORD    2   //最大密钥更新事件记录
#define MAX_InsertCardErr_EVRECORD  10    //最大异常插卡事件记录
#define MAX_ReturnMoney_EVRECORD    10    //最大退费事件记录
#define MAX_MagnetDisturb_EVRECORD  10    //恒定磁场干扰事件记录
#define MAX_RelayStatErr_EVRECORD     10      //最大负荷开关误动作事件记录
#define MAX_PowerErr_EVRECORD         10      //最大电源异常事件记录
#define     MAX_BrdTime_EVRECORD    100 //广播校时

#define MAX_EVENTTYPE       4   //定义最大事件类型(实时判断状态触发型)

#define MAX_LADDER                6       //最大阶梯数

#define DL645_MAX_RMDAY                   12    //最大结算日

#define MAX_CipherKey                 32    // 最大密钥条数
#define MAX_SafePara                  64    // 最大安全模式设置参数

//--------技术要求-存储周期--------
#define MAX_FRZWINK_RECORD                3 //最大瞬时冻结
#define MAX_FRZMIN_RECORD1                525600    //曲线1 存储深度
#define MAX_FRZMIN_RECORD2                35040       //曲线2 存储深度
#define MAX_FRZHOUR_RECORD                254   //最大整点冻结
#define MAX_FRZDAY_RECORD                 365   //最大日冻结
#define MAX_FRZRMDAY_RECORD                12   //最大结算日
#define MAX_FRZMONTH_RECORD                24   //月冻结
#define MAX_FRZLADDER_RECORD                   4    //最大年结算日
#define MAX_FRZTZONESW_RECORD                  2    //最大时区表切换冻结
#define MAX_FRZPOTSW_RECORD                2    //最大时段表切换冻结
#define MAX_FRZRATEPRICESW_RECORD            2  //最大费率电价表切换冻结
#define MAX_FRZLADDERSW_RECORD               2  //最大阶梯电价表切换冻结

//--------预留最大存储空间次数1.3倍--------
#define MAX_FRZWINK_STAT                  4 //最大瞬时冻结
#define MAX_FRZMIN_STAT                 525600
#define MAX_FRZHOUR_STAT                  330   //最大整点冻结
#define MAX_FRZDAY_STAT                 475 //最大日冻结
#define MAX_FRZRMDAY_STAT                  16   //最大结算日
#define MAX_FRZMONTH_STAT                  32   //月冻结
#define MAX_FRZLADDER_STAT                 6    //最大年结算日
#define MAX_FRZTZONESW_STAT                3    //最大时区表切换冻结
#define MAX_FRZPOTSW_STAT                  3    //最大时段表切换冻结
#define MAX_FRZRATEPRICESW_STAT          3  //最大费率电价表切换冻结
#define MAX_FRZLADDERSW_STAT                 3  //最大阶梯电价表切换冻结

#define MAX_FRZMIN_LINE                  8  //最大分钟冻结曲线条数

#define MAX_MACERR                  200  //MAC验证错误最大次数

#define FlashAdMax  0x80000

#define First_DataInit    1
#define Comm_DataInit    1

#include <BSP.h>

#include <Memory.h>
#include <Types.h>
#include <File.h>

#include <Power_Up_Down.h>
#include <Measure.h>
#include <Bkgrd.h>
#include <Energy.h>
#include <Harmonic.h>
#include <Event.h>

#include <Secret.h>
#include <Output.h>
#include <Freeze.h>
#include <Dl645_ICEsam.h>

#include <Scom.h>
#include <Dl645B_Com.h>

#include <Globals.h>

#include "Dl698_Type.h"
#include "Dl698_Scom.h"
#include "Dl698_Globals.h"
#include "Dl698_DL.h"
#include <Dl698_EsamOp.h>
#include "Dl698_Memory.h"
#include "Dl698_UserData_Oad2DI.h"
#include "Dl698_UserData.h"

// dyf 新增南瑞中天头文件
#include "app_rn7306.h"

#include <SysConst.h>

#endif  //_APP_H
