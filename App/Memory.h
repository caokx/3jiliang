
#ifndef _DL645_MEMORY_H
#define _DL645_MEMORY_H

#define MALLOC_SIZE                 512
#define MALLOC_256SIZE                  256

#define FM24C_START_ADDR        0x90000000          // fm24c512
#define FM24C_SIZE              EEPROM_MAXSize

#define AT1024_START_ADDR       0x91000000          // fm24c512
#define AT1024_SIZE             EEPROM2_MAXSIZE

#define AT45DB_START_ADDR       0x92000000          //
#if(nPhs==ThreePhs)
#define AT45DB_SIZE             0x04000000  //0x04000000 64M byte
#else
#define AT45DB_SIZE             0x02000000  //0x02000000 32M byte
#endif
#define SocEE_START_ADDR        0x94000000
#define SocEE_SIZE              0x00008000            //256
extern ErrorStatus fnMemory_Read(u8 *Dst, u32 Src, u32 DatLen);
extern ErrorStatus fnMemory_Write(u32 Dst, u8 *Src, u32 DatLen);

#endif
