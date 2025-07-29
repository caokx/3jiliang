/********************************************************************
Filename:       Dl698_UserData.h
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
#ifndef _DL698_USERDATA_H_
#define _DL698_USERDATA_H_

/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"

#ifdef __cplusplus
extern "C"
{
#endif
/*********************************************************************
* MACROS
*/
//接口类id宏定义
#define CLASSID_ENERGY        1   //电能量接口类
#define CLASSID_NEED          2   //最大需量接口类
#define CLASSID_SP_VAR        3   //分相变量接口类
#define CLASSID_POWER         4   //功率接口类
#define CLASSID_HM_VAR        5   //谐波变量接口类
#define CLASSID_DATA_VAR      6   //数据变量接口类
#define CLASSID_EVENT         7   //事件对象接口类
#define CLASSID_PARA_VAR      8   //参数变量接口类
#define CLASSID_FREEZE        9   //冻结数据接口类
#define CLASSID_COLL_MONIT    10  //采集监控接口类
#define CLASSID_COLLECT       11  //集合接口类
#define CLASSID_PULSE_MEAS    12  //脉冲计量接口类
#define CLASSID_LOAD_CTL      13  //负荷控制接口类
#define CLASSID_REGIONR       14  //区间统计接口类
#define CLASSID_ADD           15  //累加平均接口类
#define CLASSID_EXTREME       16  //极值工具接口类
#define CLASSID_SHOW          17  //显示接口类
#define CLASSID_FILE_TRANS    18  //文件传输接口类
#define CLASSID_EQUIP_MNG     19  //设备管理接口类
#define CLASSID_APP_CONN      20  //应用连接接口类
#define CLASSID_ESAM          21  //ESAM接口类
#define CLASSID_INPUT_OUTPUT  22  //输入输出设备接口类
#define CLASSID_TOTAL_GRP     23  //总加组接口类
#define CLASSID_DISCIP_EVT    24  //分项事件对象接口类
#define CLASSID_GPRS          25  //无线公网通信接口类
#define CLASSID_ETHERNET      26  //以太网通信接口类

//OIA2
#define OIA2_ENERGY_ALL 0x0
#define OIA2_ENERGY_FUNDWAVE   0x1
#define OIA2_ENERGY_HARMONICWAVE   0x2
#define OIA2_ENERGY_IRONLOSS 0x3
#define OIA2_ENERGY_COPPERLOSS 0x4
#define OIA2_ENERGY_RELATE 0x5

#define OIA2_NEED_NOW 0x0
#define OIA2_NEED_FRERZE 0x1

#define OIA2_VAR_EMU 0X0    //计量
#define OIA2_VAR_STATISTIC 0x01 //统计

#define OIB2_PHASE_ALL  0X0
#define OIB2_PHASE_A    0X1
#define OIB2_PHASE_B    0X2
#define OIB2_PHASE_C    0X3

//OIA1
#define SELECTOR_0 0x0
#define SELECTOR_1 0x1
#define SELECTOR_2 0x2
#define SELECTOR_3 0x3
#define SELECTOR_9 0x9

//用户数据接口函数
u8 fnDl698_GetValue(
    u32  OAD,           //OAD
    u16  classId,       //class id
    u16  oiindex,       //oi list index
    u8  *pParBuf,       //paramter buffer ,非记录型的pParBuf为NULL，记录型的pParBuf指向后面的RCD等信息
    u16 *parLen,        //paramter buffer length ,已处理的数据长度
    u16  retMaxLen,     //return result buffer max length，表返回的数据长度必须<= retMaxLen
    u8  *pRetBuf,       //return result buffer
    u16 *retLen,        //return result buffer length
    u8   blockReq,      //req is get-next，协议栈收到的是GET-NEXT请求
    u8  *blockRsp       //rsp is blocking，当表返回的数据长度data length>max length时，将BlockRsp置1，说明还有更多数据需要下次读取
);

u8 fnDl698_SetValue(
    u32  OAD,          //oad
    u16  classId,      //class id
    u8  *pParBuf,      //parameter buffer
    u16 *parLen        //parameter length 已处理的数据长度
);

u8 fnDl698_ActMeth(
    u32  OMD,        //OMD
    u16  classId,    //class id
    u8  *pParBuf,    //parameter buffer
    u16 *parLen,     //parameter length ，已处理的参数数据长度
    u16  retMaxLen,  //return result buffer max length
    u8  *pRetBuf,    //return result buffer
    u16 *retLen      //return result buffer length
);

u8 fnDl698_SafetyCertiHandle(
    u8   req_type,   //请求类型
    u32  OMD,        //OMD
    u8  *pParBuf,    //parameter buffer
    u8  *pRetBuf,    //return result buffer
    u16 *retLen      //return result buffer length
);

//获取尾随上报信息标志，若有尾随上报信息则返回1，否则返回0
u8 fnDl698_GetFlwRptFlag(u8 chan);       //channel number

//成功返回0,失败返回非0
void fnDl698_FlwRptValue(
    u16  retMaxLen,     //return result buffer max length，表返回的数据长度必须<= retMaxLen
    u8  *pRetBuf,       //return result buffer
    u16 *retLen         //return follow info length
);

//-用户数据接口

/*********************************************************************
* @fn      fnDl698_RptRspValue
* @brief   将ReportRsp的回复信息发给电表,表用完buffer后，调用698的空间释放函数释放掉buffer
* @param   chan      通道编号
*          Result    上报事件处理结果，0上报成功，非零上报失败，失败原因说明见XXX；上报成功时pBuffer才可用，失败时pBuffer为NULL
*          pBuffer   待发送信息的buf
*          BufferLen 待发送信息的长度
* @return  无
*/
VOID fnDl698_RptRspValue(
    u8  chan,         //channel number
    u8* pBuffer,     //待发送信息的buf
    u8  *pOADNum);   //待发送信息的长度

extern void fnDl698_ReportValue(
    u8  *pParBuf,      //parameter buffer
    u8  *pOADNum        //
);

//IC数据声明
//gDl698_OIList_ICXX 和 gDl698_SecList_ICXX是一一对应的
extern CONST u16 *gDl698_OIList[];
extern CONST u8 gDl698_OIList_NUMBER;
//extern u16 gDl698_SecList_IC01[];//默认值为默认安全模式参数，用户可以修改，修改后为显示安全模式参数

extern CONST u16 gDl698_NumIC[];

//-IC数据声明

//Report.c定义的与表接口的几个函数
//表端上报的处理顺序：
//1. fnDl698AL_RptNotiHandle 表端调用，获取当前是否允许上报，BUFFER指针和最大长度
//2. fnDl698AL_RptNotiToAl   表端调用，将上报数据放到BUFFER中，并告知有效数据长度，
//3. fnDl698_RptRspValue 协议栈调用，告知表端上报操作是否成功
//
/*********************************************************************
* @fn      fnDl698AL_RptReqHandle
* @brief   当有上报信息时，表端调用此函数进行ReportNotification，本函数是AL层的
* @param   chan         通道编号
*          rpt_type     上报类型，是ReportNotificationList还是ReportNotificationRecordList
*          repeat_flag  是否是重传帧，是为1,不是为0
*          pBufferAddr  协议栈为此次上报事件分配的BUFFER起始地址
*          BufLen       BUFFER最大长度，若表端检测到需要上报的数据大于BufLen, 则不上报，
*                       表端需要将之前申请的txbuf释放掉
* @return  处理结果，若ReportNotificaionHandle结果没问题，则返回0，否则返回错误
*/
//s8 fnDl698AL_RptNotiHandle(u8 chan, u8 rpt_type, u8 retrans_flag, u8** pBufferAddr, u16 *BufLen);
//u8 fnDl698AL_RptNotiHandle(u8 chan, u8 rpt_type, u8 retrans_flag);

/*********************************************************************
* @fn      fnDl698AL_RptNotiToAl
* @brief   表端将要上报的数据传给AL层，此函数为AL层调用表端的函数
* @param   chan     通道编号
*          DataLen  电表端上报的数据长度
*
* @return  处理结果，0 表示成功；非零表示失败；如果失败，再次上报则需要重新调用fnDl698AL_RptReqHandle再次分配BUFFER
*/
u8 fnDl698AL_RptNotiToAl(u8 chan, u16 DataLen);

/*********************************************************************
* @fn      fnRaed_DefaultSecPar
*
* @brief   获取OI的默认安全模式参数
*
* @param   oi
*
* @return  返回OI的默认安全模式参数，失败返回0xFFFF，原因为默认安全模式参数列表中未找到该oi
*/
extern u16 fnRaed_DefaultSecPar(u16 oi);
extern u16 fnRead_FormulationSecPar(u16 oi);
extern u8 fnReadMeter_Esam(u8*  uBuf) ;
extern u8 fnUpdateMeterNo(void);
extern u8 fnReadAuthOn_Esam(u8*  uBuf);
extern u8 fnUpdateAuthOn(void);
extern u8 fnRead_SecMode(void);
extern u8 fnReadPswVer_Esam(u8*  uBuf);
extern u8 fnUpdatePswSta(void);
extern void fnWrite_Broatcast_SafetyType(u8  Type);
extern u8 fnRead_Broatcast_SafetyType(void);
extern void fnGetCurrTime(sDate_time_s_TypeDef * ptime);
extern u8 fnReadDlyTime_Esam(u32*  DlyTime, u8 CA, u8 Type);
extern u8 fnConnDataDefault(u8 chan, u8 CA);
extern u8 fnConnSizeDefault(u8 chan, u8 CA);
extern void fnConnDataInit(u8 Chan, u8 CA);
extern u8 fnReadConnSize(sCommSize_TypeDef *Size, u8 chan, u8 CA);
extern u8 fnWriteConnSize(sCommSize_TypeDef *LinkSize, u8 chan, u8 CA);
extern void  fnCommStatus(u8 id);
extern u8 CheckTPeriodValid(u8 *Buf, u8 tpnum);
extern u8 fnReport_EvtData(u8 *pRetBuf, u16 *pRetLen, u8 item,  u8  *blockRsp);
extern u8 fnCheck_ReportCnt(void);
extern u8 fnCheck_RptType(void);
extern u8 fnCheck_nMacErr(void);

extern u8 fnRead_SecurtyStatus(void);
extern u8 fnRead_tIRDly(void);
extern u8 fnChk_TermBinCoreAuthStatus(u8 chan);
extern u8 fnChk_AuthOnStatus(void);
extern u8 fnReadStatus_PrgEnable(void);
extern u8 fnChkStatus_tLinkDly(void);
extern void  fnGet_ConnServer(u8 *Data);

#endif
