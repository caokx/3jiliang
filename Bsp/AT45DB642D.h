
#ifndef _AT45DB642D_H
#define _AT45DB642D_H

#ifdef   _DRIVE_AT45DB_GLOBALS
#define  AT45DB_EXT
#else
#define  AT45DB_EXT  extern
#endif

#if(nPhs==ThreePhs)
#define MX25L_MAX_AD        0x04000000
#else
#define MX25L_MAX_AD        0x02000000
#endif
#define CMD_WRITE_ENABLE    0x06
#define CMD_WRITE_DISABLE   0x04
#define CMD_READ_IDENT      0x9F
#define CMD_READ_STATUS     0x05
#define CMD_WRITE_STATUS    0x01
#define CMD_READ            0x03
#define CMD_FAST_READ       0x0B
#define CMD_PAGE_PROGRAM    0x02
#define CMD_SECTOR_ERASE    0xD8
#define CMD_BULK_ERASE      0xC7
#define CMD_BLOCK_4K_ERASE  0x20
#define CMD_BLOCK_32K_ERASE 0x52
#define CMD_RDP             0xab

#define MX25LXX_TIMEOUT     60

/*
 * Status register flags
 */
#define STATUS_SRWD (1 << 7)
#define STATUS_BP2  (1 << 4)
#define STATUS_BP1  (1 << 3)
#define STATUS_BP0  (1 << 2)
#define STATUS_WEL  (1 << 1)
#define STATUS_WIP  (1 << 0)

#define MX25L_PAGE_SIZE 256
#define MX25L_SECTOR_SIZE 4096

typedef struct
{
    u8          Buf[MX25L_SECTOR_SIZE];
} sMX25L_TypeDef;
AT45DB_EXT sMX25L_TypeDef   MX25LData;

extern  ErrorStatus fnMX25LXX_Read(u8 *Dst, u32 Src, u32 DatLen, u8 Repeat);
extern  ErrorStatus fnMX25LXX_Write(u32 Dst, u8 *Src, u32 DatLen, u8 Repeat);
extern  void  fnMX25LXX_Init(void);
extern  ErrorStatus fnMX25LXX_SetWritable(u8 writable);
//---------------------------------

#endif
