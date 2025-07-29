/********************************************************************
Filename:       Dl698_AL.h
Revised:        $Date: 2017-05-18 $
Revision:       $Revision: V0.1 $
Author:

Description:
**********************************************************************/
#ifndef _DL698_AL_H_
#define _DL698_AL_H_

/*********************************************************************
* INCLUDES
*/
#include "Dl698_Type.h"
#include "Dl698AL_def.h"
#ifdef __cplusplus
extern "C"
{
#endif

//protocolconformance∷=bit-string（SIZE（64）） bit offset
typedef enum
{
    DL698AL_CPRO_ASSNEGO                = 0,
    DL698AL_CPRO_GET                    = 1,
    DL698AL_CPRO_GETLIST                = 2,
    DL698AL_CPRO_GETREC                 = 3,
    DL698AL_CPRO_GETPROXY               = 4,
    DL698AL_CPRO_GETPROXYREC            = 5,
    DL698AL_CPRO_GETNEXT                = 6,
    DL698AL_CPRO_SET                    = 7,
    DL698AL_CPRO_SETLIST                = 8,
    DL698AL_CPRO_SETWITHGET             = 9,
    DL698AL_CPRO_SETPROXY               = 10,
    DL698AL_CPRO_SETPROXYWITHGET        = 11,
    DL698AL_CPRO_ACT                    = 12,
    DL698AL_CPRO_ACTLIST                = 13,
    DL698AL_CPRO_ACTWITHGET             = 14,
    DL698AL_CPRO_ACTPROXY               = 15,
    DL698AL_CPRO_ACTPROXYWITHGET        = 16,
    DL698AL_CPRO_RPT                    = 17,
    DL698AL_CPRO_FLLORPT                = 18,
    DL698AL_CPRO_ACDRPT                 = 19,
    DL698AL_CPRO_SLICE                  = 20,
    DL698AL_CPRO_GETREQSLI              = 21,
    DL698AL_CPRO_GETRSPSLI              = 22,
    DL698AL_CPRO_SETREQSLI              = 23,
    DL698AL_CPRO_SETRSPSLI              = 24,
    DL698AL_CPRO_ACTREQSLI              = 25,
    DL698AL_CPRO_ACTRSPSLI              = 26,
    DL698AL_CPRO_PRXREQSLI              = 27,
    DL698AL_CPRO_PRXRSPSLI              = 28,
    DL698AL_CPRO_RPTSLI                 = 29,
    DL698AL_CPRO_DLT645                 = 30,
    DL698AL_CPRO_SEC                    = 31,
    DL698AL_CPRO_GET0                   = 32,
    DL698AL_CPRO_SET0                   = 33,
} eDl698AL_CPro_TypeDef;

//FunctionConformance∷=bit-string（SIZE（128））
typedef enum
{
    DL698AL_FPRO_ENERGY = 0,
    DL698AL_FPRO_TACT   = 1,
    DL698AL_FPRO_IENERGY = 2,
} eDl698AL_CFun_TypeDef;

//安全模式参数掩码定义
#define DL698AL_SECMASK_PRXACT      0x0001
#define DL698AL_SECMASK_PRXSET      0x0002
#define DL698AL_SECMASK_PRXGET      0x0004
#define DL698AL_SECMASK_RSV         0x0008
#define DL698AL_SECMASK_ACT_CYPMAC  0x0010
#define DL698AL_SECMASK_ACT_CYP     0x0020
#define DL698AL_SECMASK_ACT_PLAMAC  0x0040
#define DL698AL_SECMASK_ACT_PLA     0x0080
#define DL698AL_SECMASK_SET_CYPMAC  0x0100
#define DL698AL_SECMASK_SET_CYP     0x0200
#define DL698AL_SECMASK_SET_PLAMAC  0x0400
#define DL698AL_SECMASK_SET_PLA     0x0800
#define DL698AL_SECMASK_GET_CYPMAC  0x1000
#define DL698AL_SECMASK_GET_CYP     0x2000
#define DL698AL_SECMASK_GET_PLAMAC  0x4000
#define DL698AL_SECMASK_GET_PLA     0x8000

/*LINK-APDU TAG*/
#define DL698AL_APDU_TAG_LNKREQ     0x01  //2
#define DL698AL_APDU_TAG_LNKRSP     0x81  //129
/*Client-APDU TAG*/
#define DL698AL_APDU_TAG_CONREQ     0x02  //2
#define DL698AL_APDU_TAG_RLSREQ     0x03  //3
#define DL698AL_APDU_TAG_GETREQ     0x05  //5
#define DL698AL_APDU_TAG_SETREQ     0x06  //6
#define DL698AL_APDU_TAG_ACTREQ     0x07  //7
#define DL698AL_APDU_TAG_RPTRSP     0x08  //8
#define DL698AL_APDU_TAG_PRXREQ     0x09  //9
/*Server-APDU TAG*/
#define DL698AL_APDU_TAG_CONRSP     0x82  //130
#define DL698AL_APDU_TAG_RLSRSP     0x83  //131
#define DL698AL_APDU_TAG_RLSRPT     0x84  //132
#define DL698AL_APDU_TAG_GETRSP     0x85  //133
#define DL698AL_APDU_TAG_SETRSP     0x86  //134
#define DL698AL_APDU_TAG_ACTRSP     0x87  //135
#define DL698AL_APDU_TAG_RPTNOTI    0x88  //136
#define DL698AL_APDU_TAG_PRXRSP     0x89  //137
#define DL698AL_APDU_TAG_ERRORRSP     0xEE  //238
/*SECURITY-APDU TAG*/
#define DL698AL_APDU_TAG_SECREQ     0x10  //16
#define DL698AL_APDU_TAG_SECRSP     0x90  //144
#define DL698AL_APDU_TAG_SECREQ_PT  0x00
#define DL698AL_APDU_TAG_SECREQ_CT  0x01
#define DL698AL_APDU_TAG_SECREQ_DAR 0x02
#define DL698AL_APDU_TAG_SECRSP_PT  0x00
#define DL698AL_APDU_TAG_SECRSP_CT  0x01
#define DL698AL_APDU_TAG_SECRSP_DAR 0x02
#define DL698AL_APDU_TAG_SECRSP_MAC 0x00

//length define for temp buf
#define TEMP_MAXSIZE    2048
#define TEMP_GETREC_MAXSIZE    3072   //读取记录型数据时需扩到3k
//length define for SEC
#define DL698AL_ESAMBUF_MAXSIZE 2048
#define DL698AL_SIDCHR_LEN      4
#define DL698AL_MAC_LEN         4
/*创建连接失败原因？？*/

//-------------异常应答数据类型定义--------------
#define DATA_ERRORRSP_APDUERR           1   //APDU无法解析
#define DATA_ERRORRSP_NOTSEVR           2   //服务不支持
#define DATA_ERRORRSP_OTH               255 //其他错

//数据访问结果DAR（Data Access Result） 宏定义
#define DATA_ACCESS_RESULT_SUC          0   //成功
#define DATA_ACCESS_RESULT_HD           1   //硬件失效
#define DATA_ACCESS_RESULT_TEMP         2   //暂时失效
#define DATA_ACCESS_RESULT_DENY         3   //拒绝读写
#define DATA_ACCESS_RESULT_UNDEF        4   //对象未定义
#define DATA_ACCESS_RESULT_CLAS         5   //对象接口类不符合
#define DATA_ACCESS_RESULT_UNAVA        6   //对象不存在
#define DATA_ACCESS_RESULT_TYPE         7   //类型不匹配
#define DATA_ACCESS_RESULT_ACC          8   //越界
#define DATA_ACCESS_RESULT_BLKUNV       9   //数据块不可用
#define DATA_ACCESS_RESULT_LGET         10  //分帧传输已取消
#define DATA_ACCESS_RESULT_NLGET        11  //不处于分帧传输状态
#define DATA_ACCESS_RESULT_LSET         12  //块写取消
#define DATA_ACCESS_RESULT_NLSET        13  //不存在块写状态
#define DATA_ACCESS_RESULT_BLKNUM       14  //数据块序号无效
#define DATA_ACCESS_RESULT_SECERR       15  //密码错/未授权
#define DATA_ACCESS_RESULT_SPDCONST     16  //通信速率不能更改
#define DATA_ACCESS_RESULT_YOVER        17  //年时区数超
#define DATA_ACCESS_RESULT_DOVER        18  //日时段数超
#define DATA_ACCESS_RESULT_ROVER        19  //费率数超
#define DATA_ACCESS_RESULT_SECNMATH     20  //安全认证不匹配
#define DATA_ACCESS_RESULT_DUPCHG       21  //重复充值
#define DATA_ACCESS_RESULT_ESAMFAIL     22  //ESAM验证失败
#define DATA_ACCESS_RESULT_SECFAIL      23  //安全认证失败
#define DATA_ACCESS_RESULT_CLTNMATH     24  //客户编号不匹配
#define DATA_ACCESS_RESULT_CHGCNTERR    25  //充值次数错误
#define DATA_ACCESS_RESULT_PUROVER      26  //购电超囤积
#define DATA_ACCESS_RESULT_ADDERR       27  //地址异常
#define DATA_ACCESS_RESULT_SYMENC       28  //对称解密错误
#define DATA_ACCESS_RESULT_ASYMENC      29  //非对称解密错误
#define DATA_ACCESS_RESULT_MACERR       30  //签名错误
#define DATA_ACCESS_RESULT_SUSPD        31  //电能表挂起
#define DATA_ACCESS_RESULT_TIMLAGERR    32  //时间标签无效
#define DATA_ACCESS_RESULT_TIMOUT       33  //请求超时
#define DATA_ACCESS_RESULT_ESAMP1P2     34  //ESAM的P1P2不正确
#define DATA_ACCESS_RESULT_ESAMLC       35  //ESAM的LC错误
//-协议自定义错误类型 linxm
#define DATA_ACCESS_RESULT_OVERFLOAT_ERR 200 //溢出错误left >right
#define DATA_ACCESS_AL_ASSO_ERROR        201 //已经建立了连接，又重复连接，将重复连接的请求丢弃就可以了！
#define DATA_ACCESS_AL_MEMALLOC_ERR      202
#define DATA_ACCESS_RESULT_LGET_ING      203 //分片帧传输过程中，接收到非分片帧时拒绝
#define DATA_ACCESS_LENTH_ERROR          210//长度与数据类型不匹配
#define DATA_CTL_GATA_ERROR              211//继电器控制错误
//-end
#define DATA_ACCESS_RESULT_OTH          255 //其它

//event_type:   0x0101 链路层建立连接
//              0x0102 链路层断开连接
//              0x0103 链路层连接失败
//              0x0104 链路层重复连接
//              0x0105 链路层连接失败
//              0x0106 inter-octet timeout
//              0x0107 inactive timeout

//              0x0201 应用层建立连接
//              0x0202 应用层断开连接，通过断开HDLC层连接来断开应用层连接
//              0x0203 应用层连接失败
//              0x0204 应用层断开连接失败
//              0x0205 应用层连接已经存在的连接，应用层不做处理，丢弃请求
//              0x0206 应用层断开连接，通过RLRQ断开应用层连接
//              0x0207 应用层断开不存在的连接

#define DL698DL_EVENT_CONNECT      0x0101
#define DL698DL_EVENT_BREAK        0x0102
#define DL698DL_EVENT_FAIL         0x0103
#define DL698DL_EVENT_RECONNECT    0x0104
#define DL698DL_EVENT_DUMMYBREAK   0x0105
#define DL698DL_EVENT_OCTTIMEOUT   0x0106
#define DL698DL_EVENT_INACTTIMEOUT 0x0107

#define DL698AL_EVENT_CONNECT             0x0201
#define DL698AL_EVENT_BREAK             0x0202
#define DL698AL_EVENT_CONNECTFAIL       0x0203
#define DL698AL_EVENT_RELEASEFAIL       0x0204
#define DL698AL_EVENT_RECONNECT       0x0205
#define DL698AL_EVENT_RELEASE             0x0206
#define DL698AL_EVENT_DUMMYDIS            0x0207

//功能码
#define DL698AL_FUNCODE_LINKMANAG     1    //链路连接管理
#define DL698AL_FUNCODE_DATAINTER     3    //数据交互

//当前帧方向
#define DL698AL_DIRPRM_SERVREPORT     2    //服务器发起的上报
#define DL698AL_DIRPRM_SERVRSP        3    //服务器对客户端请求的响应

//时间标签
#define DL698AL_TIMETAG_SUCCESS       1    //时间标签格式、解析均正确
#define DL698AL_TIMETAG_ERROR         2    //时间标签解析错误
#define DL698AL_NO_TIMETAG            3    //无时间标签

#define  RPTEVT_POWNDOWN   1  //掉电上报，纯明文,上报3011具体事件记录内容
#define  RPTEVT_POWNUP     2  //掉电上报，明文+MAC,上报3011具体事件记录内容
#define  RPTEVT_OTHER      3  //其他事件记录上报，明文+MAC，上报3320及2015内容

void fnDl698AL_GetCurrTime(sDl698date_time_s_TypeDef * ptime); //通过RTC获取当前时间
u8 fnDl698AL_Decode_TimeTag(u8 chan, u8* recvdata);      //解析时间标签
u16 fnDl698AL_TimeTagPkg(u8 chan, u8 *send_buf);
u8 fnDl698AL_TimeTag_Handle(u8 chan);
void fnDl698AL_FlwRptPkg(u8 chan, u16 retMaxLen, u8 *pRetBuf, u16 *retLen);
u8 fnDl698AL_DelayHandle(u8 chan, u8 block_flag, u8 temp_oad_num);

u16 fnDl698AL_Gen_SecRsp(u8 chan);
u16 fnDl698AL_SecReq_Handle(u8 chan);
u8 fnDl698AL_TimeTag_Valid(u8 chan);
u16 fnDl698AL_Resport_SecRsp(u8 chan);

extern  ErrorStatus fnSetCurrTime(sDate_time_s_TypeDef * ptime);
extern u8 fnDl698AL_Check_Auth(u8 chan, u8 tag_flag, u32 OAD_OMD);

#ifdef __cplusplus
}
#endif

#endif
