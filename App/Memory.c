#define  _DL645_MEMORY_GLOBALS
#include <App.h>

//存储器读取函数
ErrorStatus fnMemory_Read(u8 *Dst, u32 Src, u32 DatLen)
{
    ErrorStatus err;

    if ((FM24C_START_ADDR <= Src) &&
        ((Src + DatLen) < (FM24C_START_ADDR + FM24C_SIZE)))
    {
        #if  !DL645SOFT_DEBUG
        err = fnFM24CXX_Read(Dst, Src - FM24C_START_ADDR, DatLen, 3);
        //err = fnFM24CXX_Read(Dst , (Src - FM24C_START_ADDR)|0x00030000 , DatLen , 3);
        if (err == ERROR)
        {
            Bkgrd.PubData.EventErr[5] = BKGRD_EVENTERR_INTERMEMORY;
        }
        else
        {
            Bkgrd.PubData.EventErr[5] = BKGRD_EVENTERR_OK;
        }
        #endif
    }
    else if ((AT45DB_START_ADDR <= Src) &&
             ((Src + DatLen) < (AT45DB_START_ADDR + AT45DB_SIZE)))
    {
        #if  !DL645SOFT_DEBUG
        err = fnMX25LXX_Read(Dst, Src - AT45DB_START_ADDR, DatLen, 3);

        if (err == ERROR)
        {
            Bkgrd.PubData.EventErr[6] = BKGRD_EVENTERR_INTERMEMORY;
        }
        else
        {
            Bkgrd.PubData.EventErr[6] = BKGRD_EVENTERR_OK;
        }
        #endif
    }
    else if ((SocEE_START_ADDR <= Src) &&
             ((Src + DatLen) < (SocEE_START_ADDR + SocEE_SIZE)))
    {
        #if  !DL645SOFT_DEBUG
        err = fnSocEE_Read(Dst, Src - SocEE_START_ADDR, DatLen, 3);
        if (err == ERROR)
        {
            Bkgrd.PubData.EventErr[5] = BKGRD_EVENTERR_INTERMEMORY;
        }
        else
        {
            Bkgrd.PubData.EventErr[5] = BKGRD_EVENTERR_OK;
        }
        #endif
    }
    else if ((AT1024_START_ADDR <= Src) &&
             ((Src + DatLen) < (AT1024_START_ADDR + AT1024_SIZE)))
    {
        #if  !DL645SOFT_DEBUG
        err = fnFM24CXX_Read(Dst, (Src - AT1024_START_ADDR) | EEPROM2_DeviceNo, DatLen, 3);
        //err = fnFM24CXX_Read(Dst , (Src - AT1024_START_ADDR) , DatLen , 3);
        if (err == ERROR)
        {
            Bkgrd.PubData.EventErr[5] = BKGRD_EVENTERR_INTERMEMORY;
        }
        else
        {
            Bkgrd.PubData.EventErr[5] = BKGRD_EVENTERR_OK;
        }
        #endif
    }
    else
    {
        err = ERROR;
    }

    if (err == ERROR)
    {
        Bkgrd.PubData.MtSysSta.SysStaBit.MemoryErr = 1;
    }
    else
    {
        // dyf EE 和外部Flash读写都正常才清除状态位
        if ((Bkgrd.PubData.MtSysSta.SysStaBit.MemoryErr == 1) && (Bkgrd.PubData.EventErr[5] == BKGRD_EVENTERR_OK)
            && (Bkgrd.PubData.EventErr[6] == BKGRD_EVENTERR_OK))
        {
            Bkgrd.PubData.MtSysSta.SysStaBit.MemoryErr  = 0;
        }
    }

    return (err);
}

//存储器写入函数
ErrorStatus fnMemory_Write(u32 Dst, u8 *Src, u32 DatLen)
{
    ErrorStatus err;

    if ((FM24C_START_ADDR <= Dst) &&
        ((Dst + DatLen) < (FM24C_START_ADDR + FM24C_SIZE)))
    {
        #if  !DL645SOFT_DEBUG
        err = fnFM24CXX_Write(Dst - FM24C_START_ADDR, Src, DatLen, 3);
        //err = fnFM24CXX_Write((Dst- FM24C_START_ADDR)|0x00030000 , Src  , DatLen , 3);

        if (err == ERROR)
        {
            Bkgrd.PubData.EventErr[5] = BKGRD_EVENTERR_INTERMEMORY;
        }
        else
        {
            Bkgrd.PubData.EventErr[5] = BKGRD_EVENTERR_OK;
        }
        #endif
    }
    else if ((AT45DB_START_ADDR <= Dst) &&
             ((Dst + DatLen) < (AT45DB_START_ADDR + AT45DB_SIZE)))
    {
        #if  !DL645SOFT_DEBUG

        err = fnMX25LXX_Write(Dst - AT45DB_START_ADDR, Src, DatLen, 3);

        if (err == ERROR)
        {
            Bkgrd.PubData.EventErr[6] = BKGRD_EVENTERR_INTERMEMORY;
        }
        else
        {
            Bkgrd.PubData.EventErr[6] = BKGRD_EVENTERR_OK;
        }
        #endif
    }
    else if ((SocEE_START_ADDR <= Dst) &&
             ((Dst + DatLen) < (SocEE_START_ADDR + SocEE_SIZE)))
    {
        #if  !DL645SOFT_DEBUG
        err = fnSocEE_Write(Dst - SocEE_START_ADDR, Src, DatLen, 3);
        if (err == ERROR)
        {
            Bkgrd.PubData.EventErr[5] = BKGRD_EVENTERR_INTERMEMORY;
        }
        else
        {
            Bkgrd.PubData.EventErr[5] = BKGRD_EVENTERR_OK;
        }
        #endif
    }
    else if ((AT1024_START_ADDR <= Dst) &&
             ((Dst + DatLen) < (AT1024_START_ADDR + AT1024_SIZE)))
    {
        #if  !DL645SOFT_DEBUG
        err = fnFM24CXX_Write((Dst - AT1024_START_ADDR) | EEPROM2_DeviceNo, Src, DatLen, 3);
        //err = fnFM24CXX_Write((Dst- AT1024_START_ADDR) , Src  , DatLen , 3);
        if (err == ERROR)
        {
            Bkgrd.PubData.EventErr[5] = BKGRD_EVENTERR_INTERMEMORY;
        }
        else
        {
            Bkgrd.PubData.EventErr[5] = BKGRD_EVENTERR_OK;
        }
        #endif
    }
    else
    {
        err = ERROR;
        Bkgrd.PubData.EventErr[5] = BKGRD_EVENTERR_INTERMEMORY;
    }

    if (err == ERROR)
    {
        Bkgrd.PubData.MtSysSta.SysStaBit.MemoryErr = 1;
    }
    else
    {
        // dyf EE 和外部Flash读写都正常才清除状态位
        if ((Bkgrd.PubData.MtSysSta.SysStaBit.MemoryErr == 1) && (Bkgrd.PubData.EventErr[5] == BKGRD_EVENTERR_OK)
            && (Bkgrd.PubData.EventErr[6] == BKGRD_EVENTERR_OK))
        {
            Bkgrd.PubData.MtSysSta.SysStaBit.MemoryErr  = 0;
        }
    }

    return (err);
}
