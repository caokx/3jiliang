
#ifndef  _FM24CXX_H
#define  _FM24CXX_H

//---------------------------------------------------
//---------------------------------------------------
#define  IICFun_HardwareMode    0
#define  IICFun_FirmwareMode    1
#define  IICFun_Mode            IICFun_FirmwareMode//IICFun_HardwareMode

#define EEPROM_CLK  F16M_100K

//???????,?????
#define EEPROM_MAXSize      EEPROM24C512MAXSIZE
#define EEPROM2_MAXSIZE     EEPROM24C256MAXSize
//---------------------
#define EEPROM_PageSize     EEPROM24C512PageSize//EEPROM24C256PageSize
#define Read_EEPROM              ((u8  *) EEPROM_MEMORY_BASE    )
#define Read_Flash               ((u8  *) FLASH_MEMORY_BASE    )

#define EEPROM1_DeviceNo   0x0
#define EEPROM2_DeviceNo   0x30000

//---------------------------------------------------
extern ErrorStatus fnFM24CXX_Read(u8 *Dst, u32 Src, u32 DatLen, u8 Repeat);
extern ErrorStatus fnFM24CXX_Write(u32 Dst, u8 *Src, u32 DatLen, u8 Repeat);
extern void fnFm24c256_Init(void);
extern void EEprom_Stop(void);

#endif  //_FM24CXX_H

//---------------------------------------------------
