/********************************************************************
Filename:       Dl698_Globals.h
Revised:        $Date: 2017-05-22 $
Revision:       $Revision: V0.1 $
Author:         lin.xiaoman

Description:   DL698 globals data define file.
**********************************************************************/
#ifndef _DL698_GLOBALS_H_
#define _DL698_GLOBALS_H_

#include "Dl698AL_def.h"
#include "Dl698_AL.h"
#include "Dl698_DL.h"
//#include "../../Dl698_Test/include/Dl698_Test.h"

extern sDl698DL_ChannelInfo_TypeDef *pDl698DL_Channel;
extern sDl698AL_Server_TypeDef gDl698AL_Server;
#ifdef _WIN32
extern u8 rxbuf[1024];
extern u8 txbuf[1024];
extern u8 sendflag;
extern u8 recvflag;

#endif

#endif//_DL698_GLOBALS_H_
