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

//#define DL698_THENGET_WITH_DELAY //SETTHEGET/ACTTHENGET �ӳٹ���֧��ʱ
//#define DL698_GETBLOCK // GETBLOCK֧��ʱ

//ʱ�䵥λ
#define  DL698_UNITDEF_YEAR         1    //��
#define  DL698_UNITDEF_MONTH        2    //��
#define  DL698_UNITDEF_WEEK         3    //��
#define  DL698_UNITDEF_DAY          4    //��
#define  DL698_UNITDEF_HOUR         5    //ʱ
#define  DL698_UNITDEF_MIN          6    //��
#define  DL698_UNITDEF_SEC          7    //��

#define  DL698_UNITDEF_RAD          8    //����
#define  DL698_UNITDEF_TEMPER       9    //�¶ȣ����϶�
#define  DL698_UNITDEF_MONEY        10   //����
#define  DL698_UNITDEF_M            11   //���ȣ���
#define  DL698_UNITDEF_MPS          12   //�ٶȣ���/��
#define  DL698_UNITDEF_MMM          13   //�����������
#define  DL698_UNITDEF_DIFMMM       14   //���������������
#define  DL698_UNITDEF_MMMPS        15   //������mmm/h
#define  DL698_UNITDEF_DIFMMMPS     16   //������������mmm/h
#define  DL698_UNITDEF_MMMPD        17   //������mmm/d
#define  DL698_UNITDEF_DIFMMMPD     18   //������������mmm/d
#define  DL698_UNITDEF_L            19   //�ݻ�����
#define  DL698_UNITDEF_KG           20   //������kg
#define  DL698_UNITDEF_N            21   //����Nţ��
#define  DL698_UNITDEF_NM           22   //������ţ���ף�Nm
#define  DL698_UNITDEF_P            23   //ѹ����ţ��ÿƽ����
#define  DL698_UNITDEF_BAR          24   //ѹ����00001ţ��ÿƽ����
#define  DL698_UNITDEF_J            25   //����������
#define  DL698_UNITDEF_JPH          26   //�ȹ�������ÿСʱ
#define  DL698_UNITDEF_W            27   //�й����ʣ�W
#define  DL698_UNITDEF_KW           28   //�й����ʣ�KW
#define  DL698_UNITDEF_VA           29   //���ڹ��ʣ�����
#define  DL698_UNITDEF_KVA          30   //���ڹ��ʣ�ǧ����
#define  DL698_UNITDEF_VAR          31   //�޹����ʣ���
#define  DL698_UNITDEF_KVAR         32   //�޹����ʣ�ǧ��
#define  DL698_UNITDEF_KWH          33   //�й�������ǧ��ʱ
#define  DL698_UNITDEF_KVAH         34   //����������ǧ��-��-Сʱ
#define  DL698_UNITDEF_KVARH        35   //�޹�������ǧ��-ʱ
#define  DL698_UNITDEF_A            36   //����������
#define  DL698_UNITDEF_C            37   //����, ����
#define  DL698_UNITDEF_V            38   //��ѹ, ����
#define  DL698_UNITDEF_VPM          39   //�糡ǿ��, ��ÿ��
#define  DL698_UNITDEF_F            40   //����, ����
#define  DL698_UNITDEF_OM           41   //���裬ŷķ
#define  DL698_UNITDEF_OMM          42   //����ϵ����ŷķ��
#define  DL698_UNITDEF_WB           43   //��ͨ����Τ��
#define  DL698_UNITDEF_T            44   //��ͨ�ܶȣ�̩˹��
#define  DL698_UNITDEF_APM          45   //�ų�ǿ�ȣ�����ÿ��
#define  DL698_UNITDEF_H            46   //��У�����
#define  DL698_UNITDEF_HZ           47   //Ƶ�ʣ�����
#define  DL698_UNITDEF_1PWH         48   //�й���������������
#define  DL698_UNITDEF_1PVARH       49   //�޹���������������
#define  DL698_UNITDEF_1VAH         50   //������������������
#define  DL698_UNITDEF_PERCENT      51   //�ٷֱ�
#define  DL698_UNITDEF_BYTE         52   //�ֽ�
#define  DL698_UNITDEF_DBM          53   //�ֱ�����
#define  DL698_UNITDEF_YPKWH        54   //��ۣ�Ԫÿ��
#define  DL698_UNITDEF_AH           55   //��ʱ
#define  DL698_UNITDEF_MS           56   //����

//���ⵥλ
#define  DL698_UNITDEF_OTHER        254   //������λ
#define  DL698_UNITDEF_NOUNIT       255   //�޵�λ��ȱ��λ������

#define DL698AL_RESV_SEC_HDR          3   //SEC ͷ���ֶγ���
#define DL698AL_RESV_SEC_MAC          7   //MAC�ֶεĳ���
#define DL698AL_RESV_BLOCK            5   //BLOCK�ֶ���󳤶�
#define DL698AL_RESV_TIMETAG(chan)    gDl698AL_Server.pAlChan[chan].time_info.time_tag.len //timetag�ֶγ���
#define DL698AL_RESV_REPORT           1   //�����ϱ��ֶγ��ȣ�Ԥ��ʱĬ�ϳ���Ϊ 1

#define DL698AL_STATE_MASK_ASSO      0xC0   //2bit��ʾ���ӵ�״̬��������0��NO ;1 ASSOCIATED; 2 PENDING
#define DL698AL_STATE_MASK_REQ_TYPE  0x30   //2bit��ʾ��ǰ�������������ͣ�������: 0 GET;1 SET;2 ACTION;3 ����
#define DL698AL_STATE_MASK_REQ_SPEC  0x0F   //4bit���������;�������Ҫ�������ַ��ͺͽ��յķ����Ƿ�Ҫ�ֿ飬����ֿ�Ļ��Ƿ��һ�顢���һ��ȡ�

#define DL698AL_STATE_NO_ASSO        0x00  //δ����
#define DL698AL_STATE_IDLE           0x01  //�����ӣ�������
#define DL698AL_STATE_GET            0x10  //�����ӣ�GET��������
#define DL698AL_STATE_GET_FIRST_BLK  0x11  //�����ӣ�GET�������У���Ҫ��block����һ��block������
#define DL698AL_STATE_GET_BLK        0x12  //�����ӣ�GET�������У���Ҫ��block���ǵ�һ��block�����У�����������block֮��ת��IDLE״̬
#define DL698AL_STATE_GET_LAST_BLK   0x13  //�����ӣ�GET�������У���Ҫ��block�����һ��block�����У�����������block֮��ת��IDLE״̬
#define DL698AL_STATE_SET            0x21  //�����ӣ�SET��������
#define DL698AL_STATE_SET_FIRST_BLK  0x22  //�����ӣ�SET��������
#define DL698AL_STATE_SET_BLK        0x23  //�����ӣ�SET��������
#define DL698AL_STATE_SET_LAST_BLK   0x24  //�����ӣ�SET��������
#define DL698AL_STATE_ACT            0x31  //�����ӣ�ACT��������
#define DL698AL_STATE_ACT_FIRST_BLK  0x32  //�����ӣ�ACT��������
#define DL698AL_STATE_ACT_BLK        0x33  //�����ӣ�ACT��������
#define DL698AL_STATE_ACT_LAST_BLK   0x34  //�����ӣ�ACT��������
#define DL698AL_STATE_ACT_RES_FBLK   0x35  //�����ӣ�ACT��������
#define DL698AL_STATE_ACT_RES_BLK    0x36  //�����ӣ�ACT��������
#define DL698AL_STATE_ACT_RES_LBLK   0x37  //�����ӣ�ACT��������
#define DL698AL_STATE_HLS_FORMLY     0x40  //mechnism_nameΪHLSʱAARQ�������״̬����״̬��ֻ�ܵ���IC 15/12��reply_to_HLS_authentication ����

//�궨��APDU�ܽ��ա����͵���С�ߴ�
#define DL698AL_APDU_MAXSIZE(chan)        gDl698AL_Server.pAlChan[chan].nego.apdu_size_deal //2048
#ifdef DL698_GETBLOCK
#define DL698AL_GET_APDU_MAXSIZE(chan)    gDl698AL_Server.pAlChan[chan].nego.apdu_size_tx_nego//512
#else
#define DL698AL_GET_APDU_MAXSIZE(chan)    gDl698AL_Server.pAlChan[chan].nego.apdu_size_deal //2048
#endif
#define DL698AL_LAST_ATT_MASK_GET0  0x01
#define DL698AL_LAST_ATT_MASK_VALID 0x80
#define DL698AL_LAST_ARR_MASK_VALID 0x40

//�̶���Э��һ����
#define DL698AL_PROTCFM_HI8B       0xFFFFFFFF    //�̶���Э��һ���Ը�4bytes
#define DL698AL_PROTCFM_LO4B       0xC0000000    //�̶���Э��һ���Ե�4bytes

//�̶��Ĺ���һ����
#define DL698AL_FUNCCFM_HI16B      0xFFFEC400    //�̶��Ĺ���һ���Ը�4bytes
#define DL698AL_FUNCCFM_HI12B      0x00000000    //�̶��Ĺ���һ������4bytes
#define DL698AL_FUNCCFM_HI8B       0x00000000    //�̶��Ĺ���һ������4bytes
#define DL698AL_FUNCCFM_LO4B       0x00000000    //�̶��Ĺ���һ���Ե�4bytes

//����Ӧ�ò�Э��汾��protocol
#define DL698AL_PROTOCOL_VERSION       0x0018   // dyf �����ͼ��ĵ���Э��汾����18H��֮ǰΪ17H

//�����������Ӧ�����ӳ�ʱʱ�䣬7200s
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

#define MASTER    0xA0  //��վ
#define TERMINAL  0  //�ն�

//���ص�RN��Sign����
#define RN_LEN      64
#define SING_LEN    4

//BLOCK flag
#define DL698AL_NO_BLOCKING           0  //������
#define DL698AL_GET_BLOCKING          1  //GET BLOCK��Ƭ��
#define DL698AL_SETTHENGET_BLOCKING   2  //SET THEN GET ������
#define DL698AL_ACTTHENGET_BLOCKING   3  //ACT THEN GET ������

#define DL698AL_SERVER_DELAY_TIME     0  //��λ���룬��ʾ���÷�����Ĭ�ϵ���ʱʱ�䡣Ĭ��Ϊ0

//��������
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

//------�������ͳ���---------------
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
    u8   temp_seq_num;   //δ�������seq��
    u8   get_next_wait;  //�ȴ�Getnext��Ӧ��־,�����ͳ�ȥһ����Ƭ֡����ϵȴ�get_next_wait��־
    u8   block_flag;     //��block���,Ϊ1ʱ��ʾĿǰ����GET BLOCK��Ƭ�У�Ϊ2ʱ��ʾ��ǰ����SETTHENGET�����У�Ϊ3ʱ��ʾ��ǰ����ACTTHENGET������
    u16  block_num;      //�ѷ��͵�block���
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
    u16   left;   //����ߵ���Ч������������data[left..right-1]����Ч���ݣ����left>=right��û����Ч����
    u16   right;  //���ұߵ���Ч������������1
    u8   *data;
} sDl698AL_DatBuf_TypeDef;

//Э��һ����Э�����ݶ���
typedef struct
{
    u32  protocolconformance_lo4 ;   //Э��һ���Ե�4bytes
    u32  protocolconformance_hi8;   //Э��һ���Ը�4bytes
} sDl698AL_ProtocolConformance_TypeDef;

//����һ����Э�����ݶ���
typedef struct
{
    u32  functionconformance_lo4 ;   //����һ���Ե�4bytes
    u32  functionconformance_lo8;    //����һ���Ե�5bytes-8bytes
    u32  functionconformance_hi12;   //����һ���Ե�9bytes-12bytes
    u32  functionconformance_hi16;   //����һ���Ե�13bytes-16bytes
} sDl698AL_FunctionConformance_TypeDef;

//��֤�������
typedef enum
{
    NullSecurity      = 0,           //��������
    PasswordSecurity  = 1,           //һ������
    SymmetrySecurity  = 2,           //�ԳƼ���
    SignatureSecurity = 3          //����ǩ��
} eDl698ConnMechInfo_TypeDef;

//��֤�������
typedef enum
{
    second  = 0,           //��
    minute  = 1,           //��
    hour    = 2,           //ʱ
    day     = 3,           //��
    month   = 4,           //��
    year    = 5           //��
} eDl698TimeUnit_TypeDef;

//ʱ����TI�ṹ��
typedef struct
{
    eDl698TimeUnit_TypeDef  time_unit;
    u16                     time_interval;
} sDl698TI_TypeDef;

//ʱ���ǩ�ṹ��
typedef struct
{
    u8                          len;    //ʱ���ǩ���ȣ��б�ǩΪ10���ޱ�ǩΪ1
    u8                          check_timetag_result;
    sDate_time_s_TypeDef   date_time_s;
    sDl698TI_TypeDef            ti;
} sDl698TimeTag_TypeDef;

//ʱ����صĽṹ��
typedef struct
{
    u8                         delay_time;      //��ʱʱ��(s),���ڴ洢SetthenGet,ActThenGet��ʱ
    u32                        start_stamp;     //��ʱ��ʼʱ��
    u32                        current_cout;    //RTC��ǰ����
    u32                        lastdata_cout;   //���һ�����ݽ���ʱ��RTC����
    sDl698date_time_s_TypeDef  conn_time;       //���ӽ�����ʱ��
    sDl698TimeTag_TypeDef      time_tag;
} sDl698TimeInfo_TypeDef;

//���㼰��λ�ṹ��
typedef struct
{
    u8 unit;
    s8 scala;
} sDl698_UnitScaler_Typedef;

//��Ϊ��HDLC�㷢�ͷ���Ľӿ�
typedef struct apdu_buffer_send
{
    u8  flag;//bit[0] ���ͱ�־����ʾbuffer���д�����ϴ����͵�APDU����
    u16 left;
    u16 right;
    u16 size; //buf��size
    u8 *data;
} sDl698AL_ApduSBuf_TypeDef;

typedef struct apdu_buffer_recv
{
    u8                        flag;     //���ձ�־����HDLC���յ�һ��APDUʱ��1��APPģ�鴦�����֮�����
    u16                       left;   //����ߵ���Ч������������data[left..right-1]����Ч���ݣ����left>=right��û����Ч����
    u16                       right;  //���ұߵ���Ч������������1
    sDl698AL_ObjInfo_TypeDef  obj;
    u8                       *data;
} sDl698AL_ApduRBuf_TypeDef;

typedef struct
{
    u8                       RN[RN_LEN];         //�����
    u8                       Sign[SING_LEN];       //ǩ����Ϣ
    u8                       RnLen;       //���������
    u8                       SignLen;     //ǩ����Ϣ����
    u8                       SecType;      //���յ�SECURITY-Request��ʹ�õİ�ȫ�ȼ�
    //bit[0]��ʾ���Ļ�����,
    //    0 ����,
    //    1 ����;
    //bit[2:1]��ʾMAC���ͣ�
    //    ������֤��      [0]  SID_MAC��
    //    �����          [1]  RN��
    //    �����+����MAC  [2]  RN_MAC��
    //    ��ȫ��ʶ        [3]  SID
    u8                       SecTagLen;
    u8                       *pSecTag;
} sDl698AL_SecData_TypeDef;       //��ȫ���ݽṹ��

//    cosem_nego�ṹ��洢COSEMӦ�ò����ӽ���ʱЭ�̵Ľ����
//    auth_mech_name��ȡֵ��Χ����mechanism_id(0)��mechanism_id(1)����lowest ls��lls��
//    app_contexֻ֧��context_id(1)��ʹ��LN���÷�ʽ�����ܡ�context_id(2)ΪSN���÷�ʽ��Ŀǰ�ݲ�֧��
//    conformance_block��Ĭ��ȡֵΪ0x00001F����֧��get��set��selective-access��envent-notification��action�� ����Ƥ��P252��conformance block�ľ���
//
typedef struct
{
    sDl698AL_ProtocolConformance_TypeDef   protocol_conformance;
    sDl698AL_FunctionConformance_TypeDef   function_conformance;
    u32                                    timeout_nego;          //������Ӧ�����ӳ�ʱʱ��32bit
    u16                                    pro_version;         //Ӧ�ò�Э��汾��0x0016
    u16                                    apdu_size_tx_nego;     //����APDU��󳤶� ��Э�̵�ֵ
    u16                                    apdu_size_rx_nego;     //����APDU��󳤶� ��AARQ��Э�̵�ֵ
    u16                                    apdu_size_deal;        //�ͻ������ɴ���APDU�ߴ�
    u8                                     apdu_window_size_rx;   //�ͻ�������֡��󴰿ڳߴ�
    eDl698ConnMechInfo_TypeDef             auth_object;            //��֤�������
} sDl698AL_Nego_TypeDef;

typedef struct
{
    u8                     apdu_window_size_rx;
    u16                    apdu_size;
    u16                    dl_size_tx;
    u16                    dl_size_rx;
    sServerAddr_TypeDef    *pSa;
} sDl698AL_UserCfg_TypeDef;

//һ��ALͨ����Ӧһ��DLͨ��
typedef struct
{
    u8                        state;
    u8                        funcode;            //�����룬��������·���ӹ�����¼���������˳���¼������Ӧ������
    u8                        dirprm;             //��ǰapdu֡��DIRPRM
    sDl698AL_Nego_TypeDef     nego;               //���ӽ���ʱ��Э�̽��
    sDl698AL_BlockInfo_TypeDef blockInfo;         //BLOCK ��Ϣ
    sDl698AL_ApduRBuf_TypeDef apdu_rx_buf;        //APDU buf
    #ifdef DL698_GETBLOCK
    sDl698AL_ApduRBuf_TypeDef apdu_rx_buf_pend;   //APDU buf
    #endif
    sDl698AL_ApduSBuf_TypeDef apdu_tx_buf;        //�û����ݽӿ����ݻ���
    sDl698TimeInfo_TypeDef    time_info;          //ʱ����Ϣ
    sDl698AL_SecData_TypeDef  sec_data;           //��ȫ����
} sDl698AL_ChnInfo_TypeDef;

//server ���������е�cosemͨ����hdlcͨ��
typedef struct
{
    //������ж��ڻص�����server_passwd�����û����������ﲻ�ٴ�����
    u8                            channel_number;//ͨ������
    sDl698AL_UserCfg_TypeDef      *user_para;
    sDl698DL_ChannelInfo_TypeDef  pDlChan[SCOM_PORT_MAX];
    sDl698AL_ChnInfo_TypeDef      pAlChan[SCOM_PORT_MAX];
} sDl698AL_Server_TypeDef;

//HDLC��COSEMģ��ӿڣ���������
//    1. ����д��־��
//    2. HDLC֡��ַ������client��ַ���߼�������ַ��
//    3. ���ݣ���������APDU�ͷ���APDU���ݡ�
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

//��д����ʹ�ú���ʵ��
//read���������length��������������
//    1. ��Ϊ�����������*length=0ʱ������ʵ�ʵĶ�ȡ����*length����Ϊʵ�ʵ����ݳ��ȣ���ʱpdata����ΪNULL
//        ��*length!=0ʱ�����俴���������ݵ���󳤶ȣ���ʱ��pdata����ΪNULL��
//    2. ��Ϊ���ز������������غ�*length�����Ϊʵ�ʵ����ݳ��Ȼ򿽱���pdata���ֽ���
//
//  write���������length������Ҳ��������
//    1. ��Ϊ�����������ʾҪд�������ֽڳ��ȣ�
//    2. ��Ϊ���ز�������ʾʵ��д��������ֽڳ��ȡ�
//    ע����ΪHDLC֡�����APDU�����writeÿ��д�ĳ��ȱ����ܹ�������ɣ����write���������length����ı�
//
//  read�����ǽ�ͨ��APDU�������ݶ���pdataָ��ĵ�ַ�У�
//  write�����ǽ�pdataָ��ĵ�ַ������д�뵽ͨ��APDU�����С�
//
//  ����ֵ�Ǵ�����룬0��ʾû�д��󣬷���ֱ��ʾ��Ӧ����

s8  fnDl698AL_Wr_RecvData(u8 chan, u16* length, u8* pdata, u8 seg, u8 scramble);
s8  fnDl698AL_Rd_SendData(u8 chan, u16* length, u8* pdata, u8 scramble);

//����·����յ�֡ʱ����֡ͷ�е��߼�������ַ����Ӧ�ò㣬��Ӧ�ò����жϸõ�ַ�Ƿ����������������֡��
//������������
//����client_addressΪ1���ֽڵ�client��ַ
//���� logic_address Ϊ��ַ��1�ֽڵ����������ַ����address�ĵ�7bit����9bitȫ0�������ֽڵ����������һ���ֽڷ���address��bit[13:7]���ڶ����ֽڷ���bit[6:0]��
//����0Ϊ�ж�ͨ�������ط���Ϊ�жϲ�ͨ����
//u8 fnDl698AL_LogAdd_test(u8 chan,u8 client_address,u16 logic_address);

s8  fnDl698AL_Brk_Asso(u8 chan);

//��ʼ��������������ͨ�����е���Ϣ��ͨ������������ɺ궨��ָ������re_port.h
//����timer������

s8 fnDl698_Serv_Init(u8 channel_number, sDl698AL_UserCfg_TypeDef *pUsrCfg);

//COSEM���ʼ����ÿ��ͨ����Ҫ����һ�Σ�chan_num��ͨ���ı��
VOID fnDl698AL_Init(u8 channel_id);

//COSEM�㴦��ÿ��ͨ����Ҫ�ֱ���ã�chan_num��ͨ���ı��
VOID fnDl698AL_Process(u8 chan);

//�����������ں���
s16  fnDl698AL_Handle(u8 chan);

//һЩ�����������������ͷ����ж����õ�
//ʹ�ö��ַ���OBIS_LIST�в���ָ����OBIS�����û�ҵ�����NULL

//u16  fnDl698AL_FindOI(RE_OBISCODE* name);

//�ú������û�ʵ�֣�������֪ͨ�û�ĳЩ�¼�������
//chan:Ϊͨ�����
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
    u16 *parLen,     //parameter length ���Ѵ���Ĳ������ݳ���
    u16  retMaxLen,  //return result buffer max length
    u8  *pRetBuf,    //return result buffer
    u16 *retLen      //return result buffer length
);
u8 fnDl698_Chk_Symm(u8 *SeqEncry, u8 *SeqSign, u8 *ResRn, u8 *ResSign);
u8 fnDl698_Chk_passwd(u8 Chan, u8* pPwd, u8 PwdLen);
u8 fnDl698_SafetyCertiHandle(
    u8   req_type,   //��������
    u32  OMD,        //OMD
    u8  *pParBuf,    //parameter buffer
    u8  *pRetBuf,    //return result buffer
    u16 *retLen      //return result buffer length
);
#endif
#endif//_DL698AL_DEF_H_
