
#ifndef  _MISC_H
#define  _MISC_H

#ifdef   _MISC_GLOBALS
#define  MISC_EXT
#else
#define  MISC_EXT  extern
#endif

extern u16 fnStamp_Through(u16 Ago);
extern u8 fnStampThroughSecond(u8 Ago);

#endif  //_MISC_H
