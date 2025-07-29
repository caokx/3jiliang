/********************************************************************
Filename:       Dl698Def_Type.h
Revised:        $Date: 2017-05-22 $
Revision:       $Revision: V0.1 $
Author:         lin.xiaoman

Description:   DL698 data type define file.
**********************************************************************/
#ifndef _DL698_TYPE_H_
#define _DL698_TYPE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
//#include "dat_Types.h"
#include <Dat_Types.h>

#else
//#include <Drive_Lib.h>
#include <BSP.h>
#endif
//#include "../../Dl698_Test/include/Dl698_Test.h"

#ifdef DL698_DEBUG
#define fnDl698_debug(...)  printf(__VA_ARGS__)
#else
#define fnDl698_debug(...)
#endif
#define fnDl698_dl_debug(...) { fnDl698_debug("[DL698_DL_DEBUG] ");fnDl698_debug(__VA_ARGS__);}
#define fnDl698_al_debug(...) { fnDl698_debug("[DL698_AL_DEBUG] ");fnDl698_debug(__VA_ARGS__);}

/* Calculate the number of elements of an array */
#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

#define UINT32_TO_STREAM(p, data_u32) {*(p)++ = (u8)((data_u32) >> 24);*(p)++ = (u8)((data_u32) >> 16);*(p)++ = (u8)((data_u32) >> 8);*(p)++ = (u8)(data_u32);}
#define UINT24_TO_STREAM(p, data_u24) {*(p)++ = (u8)((data_u24) >> 16);*(p)++ = (u8)((data_u24) >> 8);*(p)++ = (u8)(data_u24);}
#define UINT16_TO_STREAM(p, data_u16) {*(p)++ = (u8)((data_u16) >> 8);*(p)++ = (u8)(data_u16);}
#define UINT8_TO_STREAM(p, data_u8)   {*(p)++ = (u8)(data_u8);}
#define INT8_TO_STREAM(p, data_u8)    {*(p)++ = (s8)(data_u8);}
#define Copy_TO_STREAM(p, a, len) {register int ijk; for (ijk = 0; ijk < len; ijk++) *(p)++ = *(a)++;}

#define STREAM_TO_UINT8(data_u8, p)   {data_u8 = (u8)(*(p)); (p) += 1;}
#define STREAM_TO_UINT16(data_u16, p) {data_u16 = ((u16)(*(p)<< 8) + ((u16)(*((p) + 1)))); (p) += 2;}
#define STREAM_TO_UINT32(data_u32, p) {data_u32 = (((u32)(*(p))<< 24) + ((((u32)(*((p) + 1)))) << 16) + ((((u32)(*((p) + 2)))) << 8) + ((u32)(*((p) + 3)))); (p) += 4;}
#define STREAM_TO_ARRAY(a, p, len) {register int ijk; for (ijk = 0; ijk < len; ijk++) ((u8 *) a)[ijk] = *p++;}

#define BUILD_U16(loByte, hiByte)  ((u16)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))
#define HI_U16(a) (((a) >> 8) & 0xFF)
#define LO_U16(a) ((a) & 0xFF)

#define BUILD_U8(hiByte, loByte) ((u8)(((loByte) & 0x0F) + (((hiByte) & 0x0F) << 4)))
#define HI_U8(a) (((a) >> 4) & 0x0F)
#define LO_U8(a) ((a) & 0x0F)
#endif//_DL698_TYPE_H_
