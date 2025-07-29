/****************************************************************************
  * File name:      cosem_hd.h
  * Version :       0.1
  * Author:         ylzhu@renergy-me.cn
  * Description:    HDLC layer data type definitions
****************************************************************************/
#ifndef _DL698AL_DEF_H_
#define _DL698AL_DEF_H_

//#include ".\cosem_ic_def.h"
#include "Dl698_DL.h"

//#define DL698_THENGET_WITH_DELAY //SETTHEGET/ACTTHENGET 延迟功能支持时
//#define DL698_GETBLOCK // GETBLOCK支持时

//时间单位
#define  DL698_UNITDEF_YEAR         1    //年
#define  DL698_UNITDEF_MONTH        2    //月
#define  DL698_UNITDEF_WEEK         3    //周
#define  DL698_UNITDEF_DAY          4    //日
#define  DL698_UNITDEF_HOUR         5    //时
#define  DL698_UNITDEF_MIN          6    //分
#define  DL698_UNITDEF_SEC          7    //秒

#define  DL698_UNITDEF_RAD          8    //弧度
#define  DL698_UNITDEF_TEMPER       9    //温度，摄氏度
#define  DL698_UNITDEF_MONEY        10   //货币
#define  DL698_UNITDEF_M            11   //长度，米
#define  DL698_UNITDEF_MPS          12   //速度，米/秒
#define  DL698_UNITDEF_MMM          13   //体积，立方米
#define  DL698_UNITDEF_DIFMMM       14   //修正体积，立方米
#define  DL698_UNITDEF_MMMPS        15   //流量，mmm/h
#define  DL698_UNITDEF_DIFMMMPS     16   //修正的流量，mmm/h
#define  DL698_UNITDEF_MMMPD        17   //流量，mmm/d
#define  DL698_UNITDEF_DIFMMMPD     18   //修正的流量，mmm/d
#define  DL698_UNITDEF_L            19   //容积，升
#define  DL698_UNITDEF_KG           20   //质量，kg
#define  DL698_UNITDEF_N            21   //力，N牛顿
#define  DL698_UNITDEF_NM           22   //力量，牛顿米，Nm
#define  DL698_UNITDEF_P            23   //压力，牛顿每平方米
#define  DL698_UNITDEF_BAR          24   //压力，00001牛顿每平方米
#define  DL698_UNITDEF_J            25   //能量，焦耳
#define  DL698_UNITDEF_JPH          26   //热功，焦耳每小时
#define  DL698_UNITDEF_W            27   //有功功率，W
#define  DL698_UNITDEF_KW           28   //有功功率，KW
#define  DL698_UNITDEF_VA           29   //视在功率，伏安
#define  DL698_UNITDEF_KVA          30   //视在功率，千伏安
#define  DL698_UNITDEF_VAR          31   //无功功率，乏
#define  DL698_UNITDEF_KVAR         32   //无功功率，千乏
#define  DL698_UNITDEF_KWH          33   //有功能量，千瓦时
#define  DL698_UNITDEF_KVAH         34   //视在能量，千伏-安-小时
#define  DL698_UNITDEF_KVARH        35   //无功能量，千乏-时
#define  DL698_UNITDEF_A            36   //电流，安培
#define  DL698_UNITDEF_C            37   //电量, 库仑
#define  DL698_UNITDEF_V            38   //电压, 伏特
#define  DL698_UNITDEF_VPM          39   //电场强度, 伏每米
#define  DL698_UNITDEF_F            40   //电容, 法拉
#define  DL698_UNITDEF_OM           41   //电阻，欧姆
#define  DL698_UNITDEF_OMM          42   //电阻系数，欧姆米
#define  DL698_UNITDEF_WB           43   //磁通量，韦伯
#define  DL698_UNITDEF_T            44   //磁通密度，泰斯拉
#define  DL698_UNITDEF_APM          45   //磁场强度，安培每米
#define  DL698_UNITDEF_H            46   //电感，亨利
#define  DL698_UNITDEF_HZ           47   //频率，赫兹
#define  DL698_UNITDEF_1PWH         48   //有功能量表常数或脉冲
#define  DL698_UNITDEF_1PVARH       49   //无功能量表常数或脉冲
#define  DL698_UNITDEF_1VAH         50   //视在能量表常数或脉冲
#define  DL698_UNITDEF_PERCENT      51   //百分比
#define  DL698_UNITDEF_BYTE         52   //字节
#define  DL698_UNITDEF_DBM          53   //分贝毫瓦
#define  DL698_UNITDEF_YPKWH        54   //电价，元每度
#define  DL698_UNITDEF_AH           55   //安时
#define  DL698_UNITDEF_MS           56   //毫秒

//特殊单位
#define  DL698_UNITDEF_OTHER        254   //其他单位
#define  DL698_UNITDEF_NOUNIT       255   //无单位、缺单位、计数

#define DL698AL_RESV_SEC_HDR          3   //SEC 头部字段长度
#define DL698AL_RESV_SEC_MAC          7   //MAC字段的长度
#define DL698AL_RESV_BLOCK            5   //BLOCK字段最大长度
#define DL698AL_RESV_TIMETAG(chan)    gDl698AL_Server.pAlChan[chan].time_info.time_tag.len //timetag字段长度
#define DL698AL_RESV_REPORT           1   //跟随上报字段长度，预留时默认长度为 1

#define DL698AL_STATE_MASK_ASSO      0xC0   //2bit表示连接的状态，有三种0：NO ;1 ASSOCIATED; 2 PENDING
#define DL698AL_STATE_MASK_REQ_TYPE  0x30   //2bit表示当前处理的请求的类型，有三种: 0 GET;1 SET;2 ACTION;3 保留
#define DL698AL_STATE_MASK_REQ_SPEC  0x0F   //4bit由请求类型决定，主要用来区分发送和接收的方向，是否要分块，如果分块的话是否第一块、最后一块等。

#define DL698AL_STATE_NO_ASSO        0x00  //未连接
#define DL698AL_STATE_IDLE           0x01  //已连接，空闲中
#define DL698AL_STATE_GET            0x10  //已连接，GET请求处理中
#define DL698AL_STATE_GET_FIRST_BLK  0x11  //已连接，GET请求处理中，需要分block，第一个block处理中
#define DL698AL_STATE_GET_BLK        0x12  //已连接，GET请求处理中，需要分block，非第一个block处理中，处理完所有block之后转到IDLE状态
#define DL698AL_STATE_GET_LAST_BLK   0x13  //已连接，GET请求处理中，需要分block，最后一个block处理中，处理完所有block之后转到IDLE状态
#define DL698AL_STATE_SET            0x21  //已连接，SET请求处理中
#define DL698AL_STATE_SET_FIRST_BLK  0x22  //已连接，SET请求处理中
#define DL698AL_STATE_SET_BLK        0x23  //已连接，SET请求处理中
#define DL698AL_STATE_SET_LAST_BLK   0x24  //已连接，SET请求处理中
#define DL698AL_STATE_ACT            0x31  //已连接，ACT请求处理中
#define DL698AL_STATE_ACT_FIRST_BLK  0x32  //已连接，ACT请求处理中
#define DL698AL_STATE_ACT_BLK        0x33  //已连接，ACT请求处理中
#define DL698AL_STATE_ACT_LAST_BLK   0x34  //已连接，ACT请求处理中
#define DL698AL_STATE_ACT_RES_FBLK   0x35  //已连接，ACT请求处理中
#define DL698AL_STATE_ACT_RES_BLK    0x36  //已连接，ACT请求处理中
#define DL698AL_STATE_ACT_RES_LBLK   0x37  //已连接，ACT请求处理中
#define DL698AL_STATE_HLS_FORMLY     0x40  //mechnism_name为HLS时AARQ交互后的状态，该状态下只能调用IC 15/12的reply_to_HLS_authentication 方法

//宏定义APDU能接收、发送的最小尺寸
#define DL698AL_APDU_MAXSIZE(chan)        gDl698AL_Server.pAlChan[chan].nego.apdu_size_deal //2048
#ifdef DL698_GETBLOCK
#define DL698AL_GET_APDU_MAXSIZE(chan)    gDl698AL_Server.pAlChan[chan].nego.apdu_size_tx_nego//512
#else
#define DL698AL_GET_APDU_MAXSIZE(chan)    gDl698AL_Server.pAlChan[chan].nego.apdu_size_deal //2048
#endif
#define DL698AL_LAST_ATT_MASK_GET0  0x01
#define DL698AL_LAST_ATT_MASK_VALID 0x80
#define DL698AL_LAST_ARR_MASK_VALID 0x40

//商定的协议一致性
#define DL698AL_PROTCFM_HI8B       0xFFFFFFFF    //商定的协议一致性高4bytes
#define DL698AL_PROTCFM_LO4B       0xC0000000    //商定的协议一致性低4bytes

//商定的功能一致性
#define DL698AL_FUNCCFM_HI16B      0xFFFEC400    //商定的功能一致性高4bytes
#define DL698AL_FUNCCFM_HI12B      0x00000000    //商定的功能一致性中4bytes
#define DL698AL_FUNCCFM_HI8B       0x00000000    //商定的功能一致性中4bytes
#define DL698AL_FUNCCFM_LO4B       0x00000000    //商定的功能一致性低4bytes

//定义应用层协议版本号protocol
#define DL698AL_PROTOCOL_VERSION       0x0018   // dyf 最新送检文档中协议版本号是18H，之前为17H

//服务器定义的应用连接超时时间，7200s
#define DL698AL_CONNECT_TIMEOUT    0x1C20

#define DL698AL_APTU_MAXSIZE_485A   2000
#define DL698AL_APTU_MAXSIZE_SPI    2000
#define DL698AL_APTU_MAXSIZE_PLC    2000
#define DL698AL_APTU_MAXSIZE_485B   2000

#define DL698AL_DL_SIZE_TX_485A     512
#define DL698AL_DL_SIZE_TX_SPI      2048//200
#define DL698AL_DL_SIZE_TX_PLC      255
#define DL698AL_DL_SIZE_TX_485B     512

#define DL698AL_DL_SIZE_RX_485A     512
#define DL698AL_DL_SIZE_RX_SPI      2048//200
#define DL698AL_DL_SIZE_RX_PLC      255
#define DL698AL_DL_SIZE_RX_485B     512

#define MASTER    0xA0  //主站
#define TERMINAL  0  //终端

//返回的RN及Sign长度
#define RN_LEN      64
#define SING_LEN    4

//BLOCK flag
#define DL698AL_NO_BLOCKING           0  //空闲中
#define DL698AL_GET_BLOCKING          1  //GET BLOCK分片中
#define DL698AL_SETTHENGET_BLOCKING   2  //SET THEN GET 处理中
#define DL698AL_ACTTHENGET_BLOCKING   3  //ACT THEN GET 处理中

#define DL698AL_SERVER_DELAY_TIME     0  //单位：秒，表示采用服务器默认的延时时间。默认为0

//数据类型
/*no data type is set,is it means no data?*/
#define DTYPE_NONE        0
/**Array*/
#define DTYPE_ARRAY       1
/*Structure*/
#define DTYPE_STRUCTURE   2
/*Boolean*/
#define DTYPE_BOOLEAN     3
/*Bit string*/
#define DTYPE_BITSTRING   4
/*Int32*/
#define DTYPE_INT32       5
/*UInt32*/
#define DTYPE_UINT32      6
/*Data type is Octet string*/
#define DTYPE_OCT_STR     9
/*visible-string ASCII*/
#define DTYPE_STRING      10
/*UTF8-string*/
#define DTYPE_UTF         12
/*Binary coded decimal*/
#define DTYPE_BCD         13
/*Int8*/
#define DTYPE_INT8        15
/*Int16*/
#define DTYPE_INT16       16
/*UInt8*/
#define DTYPE_UINT8       17
/*UInt16*/
#define DTYPE_UINT16      18
/*Compact array*/
#define DTYPE_COMPACT     19  //not supported now
/*Int64*/
#define DTYPE_INT64       20
/*UInt64*/
#define DTYPE_UINT64      21
/*Enum*/
#define DTYPE_ENUM        22
/*Float32,octet string ,size 4*/
#define DTYPE_FLOAT32     23
/*Float64,octet string ,size 8*/
#define DTYPE_FLOAT64     24
/*DateTime,octet string ,size 12*/
#define DTYPE_DATETIME    25
/*Date,octet string ,size 5*/
#define DTYPE_DATE        26
/*Time,octet string ,size 4*/
#define DTYPE_TIME        27
/*date_time_s, size 7*/
#define DTYPE_DATETIME_S  28
/*OI,size 2*/
#define DTYPE_OI          80
/*OAD ,size 4*/
#define DTYPE_OAD         81
/*ROAD ,size 4*N */
#define DTYPE_ROAD        82
/*OMD, size 4*/
#define DTYPE_OMD         83
/*TI,  size 3*/
#define DTYPE_TI          84
/*TSA, octet-string, size 2...17*/
#define DTYPE_TSA         85
/*MAC, octet string */
#define DTYPE_MAC         86
/*RN,  octet-string */
#define DTYPE_RN          87
/*Region */
#define DTYPE_REGION      88
/*Scaler_Unit,  size 2*/
#define DTYPE_SCAUNIT     89
/*RSD*/
#define DTYPE_RSD         90
/*CSD */
#define DTYPE_CSD         91
/*MS,  size 3*/
#define DTYPE_MS          92
/*SID, size 4 + octet-string */
#define DTYPE_SID         93
/*SID_MAC */
#define DTYPE_SID_MAC     94
/*COMDCB,  size 5*/
#define DTYPE_COMDCB      95
/*RCSD */
#define DTYPE_RCSD        96

//------数据类型长度---------------
#define DTYPE_INT8_Len      1
#define DTYPE_UINT8_Len     1

#define DTYPE_INT16_Len     2
#define DTYPE_UINT16_Len    2

#define DTYPE_INT32_Len     4
#define DTYPE_UINT32_Len    4

#define DTYPE_INT64_Len     8
#define DTYPE_UINT64_Len    8

#define DTYPE_ENUM_Len  1

typedef struct
{
    u8   temp_seq_num;   //未处理完的seq数
    u8   get_next_wait;  //等待Getnext响应标志,当发送出去一个分片帧后打上等待get_next_wait标志
    u8   block_flag;     //分block标记,为1时表示目前处于GET BLOCK分片中，为2时表示当前处于SETTHENGET操作中，为3时表示当前处于ACTTHENGET操作中
    u16  block_num;      //已发送的block序号
} sDl698AL_BlockInfo_TypeDef;

typedef struct
{
    u8   piid;
    u8   tag;
    u8   attevt_id;
    u16  oi;
    u16  class_id;
    u16  oi_list_index;
    u32  oad_omd;
} sDl698AL_ObjInfo_TypeDef;

typedef struct
{
    u16   left;   //最左边的有效的数据索引，data[left..right-1]是有效数据，如果left>=right则没有有效数据
    u16   right;  //最右边的有效的数据索引加1
    u8   *data;
} sDl698AL_DatBuf_TypeDef;

//协议一致性协商内容定义
typedef struct
{
    u32  protocolconformance_lo4 ;   //协议一致性低4bytes
    u32  protocolconformance_hi8;   //协议一致性高4bytes
} sDl698AL_ProtocolConformance_TypeDef;

//功能一致性协商内容定义
typedef struct
{
    u32  functionconformance_lo4 ;   //功能一致性低4bytes
    u32  functionconformance_lo8;    //功能一致性第5bytes-8bytes
    u32  functionconformance_hi12;   //功能一致性第9bytes-12bytes
    u32  functionconformance_hi16;   //功能一致性第13bytes-16bytes
} sDl698AL_FunctionConformance_TypeDef;

//认证请求对象
typedef enum
{
    NullSecurity      = 0,           //公共连接
    PasswordSecurity  = 1,           //一般密码
    SymmetrySecurity  = 2,           //对称加密
    SignatureSecurity = 3          //数字签名
} eDl698ConnMechInfo_TypeDef;

//认证请求对象
typedef enum
{
    second  = 0,           //秒
    minute  = 1,           //分
    hour    = 2,           //时
    day     = 3,           //天
    month   = 4,           //月
    year    = 5           //年
} eDl698TimeUnit_TypeDef;

//时间间隔TI结构体
typedef struct
{
    eDl698TimeUnit_TypeDef  time_unit;
    u16                     time_interval;
} sDl698TI_TypeDef;

//时间标签结构体
typedef struct
{
    u8                          len;    //时间标签长度，有标签为10，无标签为1
    u8                          check_timetag_result;
    sDate_time_s_TypeDef   date_time_s;
    sDl698TI_TypeDef            ti;
} sDl698TimeTag_TypeDef;

//时间相关的结构体
typedef struct
{
    u8                         delay_time;      //延时时间(s),用于存储SetthenGet,ActThenGet延时
    u32                        start_stamp;     //计时开始时间
    u32                        current_cout;    //RTC当前计数
    u32                        lastdata_cout;   //最后一次数据交互时的RTC计数
    sDl698date_time_s_TypeDef  conn_time;       //连接建立的时间
    sDl698TimeTag_TypeDef      time_tag;
} sDl698TimeInfo_TypeDef;

//换算及单位结构体
typedef struct
{
    u8 unit;
    s8 scala;
} sDl698_UnitScaler_Typedef;

//作为跟HDLC层发送方向的接口
typedef struct apdu_buffer_send
{
    u8  flag;//bit[0] 发送标志，表示buffer中有处理完毕待发送的APDU数据
    u16 left;
    u16 right;
    u16 size; //buf总size
    u8 *data;
} sDl698AL_ApduSBuf_TypeDef;

typedef struct apdu_buffer_recv
{
    u8                        flag;     //接收标志，当HDLC接收到一个APDU时置1，APP模块处理完成之后清除
    u16                       left;   //最左边的有效的数据索引，data[left..right-1]是有效数据，如果left>=right则没有有效数据
    u16                       right;  //最右边的有效的数据索引加1
    sDl698AL_ObjInfo_TypeDef  obj;
    u8                       *data;
} sDl698AL_ApduRBuf_TypeDef;

typedef struct
{
    u8                       RN[RN_LEN];         //随机数
    u8                       Sign[SING_LEN];       //签名信息
    u8                       RnLen;       //随机数长度
    u8                       SignLen;     //签名信息长度
    u8                       SecType;      //接收到SECURITY-Request所使用的安全等级
    //bit[0]表示明文或密文,
    //    0 明文,
    //    1 密文;
    //bit[2:1]表示MAC类型，
    //    数据验证码      [0]  SID_MAC，
    //    随机数          [1]  RN，
    //    随机数+数据MAC  [2]  RN_MAC，
    //    安全标识        [3]  SID
    u8                       SecTagLen;
    u8                       *pSecTag;
} sDl698AL_SecData_TypeDef;       //安全数据结构体

//    cosem_nego结构体存储COSEM应用层连接建立时协商的结果，
//    auth_mech_name的取值范围包括mechanism_id(0)和mechanism_id(1)，即lowest ls和lls。
//    app_contex只支持context_id(1)即使用LN引用方式不加密。context_id(2)为SN引用方式，目前暂不支持
//    conformance_block的默认取值为0x00001F，即支持get、set、selective-access、envent-notification和action。 见绿皮书P252中conformance block的举例
//
typedef struct
{
    sDl698AL_ProtocolConformance_TypeDef   protocol_conformance;
    sDl698AL_FunctionConformance_TypeDef   function_conformance;
    u32                                    timeout_nego;          //期望的应用连接超时时间32bit
    u16                                    pro_version;         //应用层协议版本号0x0016
    u16                                    apdu_size_tx_nego;     //发送APDU最大长度 ，协商的值
    u16                                    apdu_size_rx_nego;     //接收APDU最大长度 ，AARQ中协商的值
    u16                                    apdu_size_deal;        //客户机最大可处理APDU尺寸
    u8                                     apdu_window_size_rx;   //客户机接收帧最大窗口尺寸
    eDl698ConnMechInfo_TypeDef             auth_object;            //认证请求对象
} sDl698AL_Nego_TypeDef;

typedef struct
{
    u8                     apdu_window_size_rx;
    u16                    apdu_size;
    u16                    dl_size_tx;
    u16                    dl_size_rx;
    sServerAddr_TypeDef    *pSa;
} sDl698AL_UserCfg_TypeDef;

//一个AL通道对应一个DL通道
typedef struct
{
    u8                        state;
    u8                        funcode;            //功能码，区分是链路连接管理（登录，心跳，退出登录）还是应用连接
    u8                        dirprm;             //当前apdu帧的DIRPRM
    sDl698AL_Nego_TypeDef     nego;               //连接建立时的协商结果
    sDl698AL_BlockInfo_TypeDef blockInfo;         //BLOCK 信息
    sDl698AL_ApduRBuf_TypeDef apdu_rx_buf;        //APDU buf
    #ifdef DL698_GETBLOCK
    sDl698AL_ApduRBuf_TypeDef apdu_rx_buf_pend;   //APDU buf
    #endif
    sDl698AL_ApduSBuf_TypeDef apdu_tx_buf;        //用户数据接口数据缓存
    sDl698TimeInfo_TypeDef    time_info;          //时间信息
    sDl698AL_SecData_TypeDef  sec_data;           //安全数据
} sDl698AL_ChnInfo_TypeDef;

//server 包含了所有的cosem通道和hdlc通道
typedef struct
{
    //密码的判定在回调函数server_passwd中由用户决定，这里不再存密码
    u8                            channel_number;//通道个数
    sDl698AL_UserCfg_TypeDef      *user_para;
    sDl698DL_ChannelInfo_TypeDef  pDlChan[SCOM_PORT_MAX];
    sDl698AL_ChnInfo_TypeDef      pAlChan[SCOM_PORT_MAX];
} sDl698AL_Server_TypeDef;

//HDLC与COSEM模块接口，包括三类
//    1. 读、写标志；
//    2. HDLC帧地址，包括client地址和逻辑器件地址；
//    3. 数据，包括接收APDU和发送APDU数据。
//
//
#define DL698AL_GET_RECV_FLAG(chan)  (gDl698AL_Server.pAlChan[chan].apdu_rx_buf.flag & 0x01)
#define DL698AL_SET_RECV_FLAG(chan)  (gDl698AL_Server.pAlChan[chan].apdu_rx_buf.flag |=0x01)
#define DL698AL_CLR_RECV_FLAG(chan)   gDl698AL_Server.pAlChan[chan].apdu_rx_buf.flag &=0xFE; \
    gDl698AL_Server.pAlChan[chan].apdu_rx_buf.left=0; \
    gDl698AL_Server.pAlChan[chan].apdu_rx_buf.right=0;\
    fnDl698_Buffer_Free(gDl698AL_Server.pAlChan[chan].apdu_rx_buf.data);\
    fnDl698_memset(&gDl698AL_Server.pAlChan[chan].apdu_rx_buf.obj, 0, sizeof(sDl698AL_ObjInfo_TypeDef)); \
    gDl698AL_Server.pAlChan[chan].apdu_rx_buf.data = NULL

#define DL698AL_GET_SEND_FLAG(chan)  (gDl698AL_Server.pAlChan[chan].apdu_tx_buf.flag & 0x02)
#define DL698AL_SET_SEND_FLAG(chan)  (gDl698AL_Server.pAlChan[chan].apdu_tx_buf.flag |=0x02)
#define DL698AL_CLR_SEND_FLAG(chan)   gDl698AL_Server.pAlChan[chan].apdu_tx_buf.flag &=0xFD; \
    gDl698AL_Server.pAlChan[chan].apdu_tx_buf.left = 0; \
    gDl698AL_Server.pAlChan[chan].apdu_tx_buf.right = 0; \
    fnDl698_Buffer_Free(gDl698AL_Server.pAlChan[chan].apdu_tx_buf.data);\
    gDl698AL_Server.pAlChan[chan].apdu_tx_buf.data = NULL;\
    gDl698AL_Server.pAlChan[chan].apdu_tx_buf.size = 0

#define DL698AL_CLR_PEND_BUFFER(chan)   fnDl698_Buffer_Free(gDl698AL_Server.pAlChan[chan].apdu_rx_buf_pend.data);\
    fnDl698_memset(&gDl698AL_Server.pAlChan[chan].apdu_rx_buf_pend, 0, sizeof(sDl698AL_ApduRBuf_TypeDef))

#define DL698AL_CLR_BLOCKINFO(chan)     fnDl698_memset(&gDl698AL_Server.pAlChan[chan].blockInfo, 0, sizeof(sDl698AL_BlockInfo_TypeDef))

#define DL698AL_BOOL_GETTIMEOUT(start,current,timeout)  ((current > start) ? (((current - start ) >= timeout) ? (true) : (false)) : (((( 0xFFFFFFFF - start + current) >= (timeout)) ? (true) : (false))))

//读写数据使用函数实现
//read函数里面的length的作用有两个：
//    1. 作为输入参数，当*length=0时，不做实际的读取，将*length更新为实际的数据长度，此时pdata可以为NULL
//        当*length!=0时，将其看做接收数据的最大长度，此时的pdata不能为NULL；
//    2. 作为返回参数，函数返回后，*length会更新为实际的数据长度或拷贝到pdata的字节数
//
//  write函数里面的length的作用也有两个：
//    1. 作为输入参数，表示要写的数据字节长度；
//    2. 作为返回参数，表示实际写入的数据字节长度。
//    注：因为HDLC帧不会跨APDU，因此write每次写的长度必须能够处理完成，因此write函数里面的length不会改变
//
//  read函数是将通道APDU缓存数据读到pdata指向的地址中；
//  write函数是将pdata指向的地址的数据写入到通道APDU缓存中。
//
//  返回值是错误编码，0表示没有错误，非零分别表示相应错误

s8  fnDl698AL_Wr_RecvData(u8 chan, u16* length, u8* pdata, u8 seg, u8 scramble);
s8  fnDl698AL_Rd_SendData(u8 chan, u16* length, u8* pdata, u8 scramble);

//当链路层接收到帧时，将帧头中的逻辑器件地址传给应用层，让应用层来判断该地址是否合理，如果合理则接收帧，
//不合理则丢弃。
//参数client_address为1个字节的client地址
//参数 logic_address 为地址；1字节的情况，将地址放在address的低7bit，高9bit全0；两个字节的情况，将第一个字节放在address的bit[13:7]，第二个字节放在bit[6:0]。
//返回0为判断通过，返回非零为判断不通过。
//u8 fnDl698AL_LogAdd_test(u8 chan,u8 client_address,u16 logic_address);

s8  fnDl698AL_Brk_Asso(u8 chan);

//初始化服务器，所有通道共有的信息，通道的最大数量由宏定义指定，见re_port.h
//配置timer和密码

s8 fnDl698_Serv_Init(u8 channel_number, sDl698AL_UserCfg_TypeDef *pUsrCfg);

//COSEM层初始化，每个通道需要调用一次，chan_num是通道的编号
VOID fnDl698AL_Init(u8 channel_id);

//COSEM层处理，每个通道需要分别调用，chan_num是通道的编号
VOID fnDl698AL_Process(u8 chan);

//请求服务处理入口函数
s16  fnDl698AL_Handle(u8 chan);

//一些公共函数，多种类型服务中都会用到
//使用二分法从OBIS_LIST中查找指定的OBIS，如果没找到返回NULL

//u16  fnDl698AL_FindOI(RE_OBISCODE* name);

//该函数由用户实现，作用是通知用户某些事件发生了
//chan:为通道编号
//event_type:
#define DL698AL_SECMASK_PT    3
#define DL698AL_SECMASK_PTMAC 2
#define DL698AL_SECMASK_CT    1
#define DL698AL_SECMASK_CTMAC 0
//#define fnDl698AL_Cmp_OISec(sec1,sec2) ((sec1)>(sec2) ? 1 : (sec1)==(sec2) ? 0 : (-1))

u16 fnDl698AL_Get_OISec(u16 oi);
u8 fnDl698AL_Get_OIOpSec(u16 oi, u8 op, u8 transfer_sec);
u8 fnDl698AL_Check_ApduSec(u8 chan, u8 tag, u8 tag2, u32 OMD);
VOID fnDl698AL_EvtNotify(u8 chan, u16 event_value);
u16 fnDl698AL_Check_OIList(sDl698AL_ObjInfo_TypeDef *pObj);
//u8 fnDl698AL_Check_OISec(u8 chan);
#ifdef _WIN32
u8 fnDl698_GetValueTest(u16 *parLen, u8  *pRetBuf, u16 *retLen, u8 *blockRsp);
u8 fnDl698_SetValueTest(u32 OAD, u16 classId, u8 *pParBuf, u16 *parLen);
u8 fnDl698_ActMethTest(
    u32  OMD,        //OMD
    u16  classId,    //class id
    u8  *pParBuf,    //parameter buffer
    u16 *parLen,     //parameter length ，已处理的参数数据长度
    u16  retMaxLen,  //return result buffer max length
    u8  *pRetBuf,    //return result buffer
    u16 *retLen      //return result buffer length
);
u8 fnDl698_Chk_Symm(u8 *SeqEncry, u8 *SeqSign, u8 *ResRn, u8 *ResSign);
u8 fnDl698_Chk_passwd(u8 Chan, u8* pPwd, u8 PwdLen);
u8 fnDl698_SafetyCertiHandle(
    u8   req_type,   //请求类型
    u32  OMD,        //OMD
    u8  *pParBuf,    //parameter buffer
    u8  *pRetBuf,    //return result buffer
    u16 *retLen      //return result buffer length
);
#endif
#endif//_DL698AL_DEF_H_
