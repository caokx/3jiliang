/****************************************************************************
  * File name:      DL698AL_asn1.h
  * Version :       0.1
  * Author:         ylzhu@renergy-me.cn
  * Description:    common data type define head file
****************************************************************************/

#ifndef _DL698AL_ASN1_H_
#define _DL698AL_ASN1_H_

/**
Common DataType macro usable types of data
*/
#ifdef __cplusplus
extern "C"
{
#endif

#define DL698AL_TIMETAG_CONREQ_NOSECU    40  //公共连接
#define DL698AL_TIMETAG_CONREQ_PWDSECU   41  //一般密码+密码长度
#define DL698AL_TIMETAG_CONREQ_SYMMSECU  78  //对称加密

#define DL698AL_TIMETAG_CONRLS        2
#define DL698AL_TIMETAG_GETNORM       7
#define DL698AL_TIMETAG_GETNXT        7
#define DL698AL_TIMETAG_GETRECORDDI   11

//internal used function
extern u8 fnDL698AL_asn1_set_ObjCnt(u16 data_len, u8* buffer);
extern u16 fnDL698AL_asn1_get_ObjCnt(u16* data_len, u8* buffer);
extern u16 fnDl698AL_Check_TimeTag(u8 chan);
extern u16 fnDl698AL_GetData_Len(u8 dattyp_exist, u8 datatype, u8* pBuf);
extern u8 fnDl698_GetDataType(u16 classId, u16 oi_list_index, u8 att_id);

extern u16 fnDl698_asn1_build_Type(u8 *pDst, u16 *Dstlen, u8 *pSrc, u16 *srclen, u8 type);
extern u16 fnForm_build_Type(u8 *pDst, u16 *Dstlen, u8 *pSrc, u16 *srclen, u8 *pType);
#ifdef __cplusplus
}
#endif

#endif
