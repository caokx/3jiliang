
#define  _DRIVE_AT45DB_GLOBALS

#include <BSP.h>
//mx25l32 ��������
/*****************************************************************************
** Function name:fnMX25LXX_Dly
**
** Description:��ʱ���� ��λΪ1US
**
** Parameters:tDly US
**
** Returned value:none
**
******************************************************************************/
void fnMX25LXX_Dly(u32  tDly)
{
    for (; tDly != 0 ; tDly--)
    {
        __NOP();
        __NOP();
    }
}

//void ENABLE_FLASH_MX25LXX(void)
//{
//  PinWrite_MX25LCs(0);
//  //fnMX25LXX_Dly(4);
//}
//
//void DISABLE_FLASH_MX25LXX(void)
//{
//  PinWrite_MX25LCs(1);
//  //fnMX25LXX_Dly(4);
//}
/*****************************************************************************
** Function name:fnMX25LXX_Init
**
** Description:MX25LXX ��ʼ������
**
** Parameters:NONE
**
** Returned value:NONE
**
******************************************************************************/
void  fnMX25LXX_Init(void)
{
    BSP_FlashSpi_Init();
    Std_Memset(&MX25LData.Buf[0], 0, MX25L_SECTOR_SIZE);
    fnMX25LXX_SetWritable(1);
    ENABLE_FLASH_MX25LXX();
    BSP_FlashSpi_WriteByte(CMD_RDP);
    DISABLE_FLASH_MX25LXX();
}

/*****************************************************************************
** Function name:fnMX25LXX_WaitRdy
**
** Description: ���mx25l�Ƿ�æ��־
**
** Parameters:  TimeOut �����ʱʱ��
**
** Returned value:SUCCESS OR ERROR
**
******************************************************************************/
ErrorStatus fnMX25LXX_WaitRdy(u8 TimeOut)
{
    u8 RxBuf[2];
    for (; TimeOut != 0 ; TimeOut--)
    {
        ENABLE_FLASH_MX25LXX();
        BSP_FlashSpi_WriteByte(CMD_READ_STATUS);
        RxBuf[0] = BSP_FlashSpi_ReadByte();
        DISABLE_FLASH_MX25LXX();
        if (!(RxBuf[0] & STATUS_WIP))
        {
            return (SUCCESS);
        }
        fnMX25LXX_Dly(1000);
    }
    return (ERROR);
}

/*****************************************************************************
** Function name:fnMX25LXX_SetWritable
**
** Description: MX25LXX д�����򿪻�ر�
**
** Parameters:writable  1�� ��д����  0���ر�д����
**
** Returned value: NONE
**
******************************************************************************/
ErrorStatus fnMX25LXX_SetWritable(u8 writable)
{
    u8  i;
    if (writable)
    {
        ENABLE_FLASH_MX25LXX();
        BSP_FlashSpi_WriteByte(CMD_WRITE_ENABLE);
        DISABLE_FLASH_MX25LXX();
        for (i = 0; i < 200; i++)
        {
            ENABLE_FLASH_MX25LXX();
            BSP_FlashSpi_WriteByte(CMD_READ_STATUS);
            if (BSP_FlashSpi_ReadByte() & 0x02)
            {
                DISABLE_FLASH_MX25LXX();
                return (SUCCESS);
            }
            DISABLE_FLASH_MX25LXX();
            ENABLE_FLASH_MX25LXX();
            BSP_FlashSpi_WriteByte(CMD_RDP);
            DISABLE_FLASH_MX25LXX();
            fnMX25LXX_Dly(100);
        }
        return (ERROR);
    }
    else
    {
        ENABLE_FLASH_MX25LXX();
        BSP_FlashSpi_WriteByte(CMD_WRITE_DISABLE);
        DISABLE_FLASH_MX25LXX();
        return (SUCCESS);
    }
}

/*****************************************************************************
** Function name:
**
** Description:
**
** Parameters:
**
** Returned value:
**
******************************************************************************/
ErrorStatus fnMX25LXX_eraseChip(void)
{
    if (fnMX25LXX_WaitRdy(MX25LXX_TIMEOUT) != SUCCESS)
    {
        return (ERROR);
    }
    fnMX25LXX_SetWritable(1);
    ENABLE_FLASH_MX25LXX();
    BSP_FlashSpi_WriteByte(CMD_BULK_ERASE);
    DISABLE_FLASH_MX25LXX();
    return (SUCCESS);
}

/*****************************************************************************
** Function name:fnMX25LXX_eraseSector
**
** Description:4K���ֽ����ݲ���
**
** Parameters:SectorAd �����
**
** Returned value:NONE
**
******************************************************************************/
void fnMX25LXX_eraseSector(u32 SectorAd)
{
    ENABLE_FLASH_MX25LXX();
    BSP_FlashSpi_WriteByte(CMD_BLOCK_4K_ERASE);
    BSP_FlashSpi_WriteByte((SectorAd >> 16) & 0xff);
    BSP_FlashSpi_WriteByte((SectorAd >> 8) & 0xff);
    BSP_FlashSpi_WriteByte(SectorAd & 0xff);
    DISABLE_FLASH_MX25LXX();
}

/*****************************************************************************
** Function name:fnMX25LXX_MMPage_To_Buf
**
** Description:�������ݶ���Buf��
**
** Parameters:  PA ��ȡ���ַ
**
** Returned value: SUCCESS OR ERROR
**
******************************************************************************/
ErrorStatus fnMX25LXX_MMPage_To_Buf(u32 PA)
{
    u32 Len;
    if (PA > MX25L_MAX_AD)
    {
        return (ERROR);
    }
    if (fnMX25LXX_WaitRdy(MX25LXX_TIMEOUT) != SUCCESS)
    {
        return (ERROR);
    }
    ENABLE_FLASH_MX25LXX();
    BSP_FlashSpi_WriteByte(CMD_READ);
    BSP_FlashSpi_WriteByte((PA >> 16) & 0xff);
    BSP_FlashSpi_WriteByte((PA >> 8) & 0xff);
    BSP_FlashSpi_WriteByte(PA & 0xff);
    for (Len = 0; Len < MX25L_SECTOR_SIZE; Len++)
    {
        MX25LData.Buf[Len] = BSP_FlashSpi_ReadByte();
    }
    DISABLE_FLASH_MX25LXX();
    return (SUCCESS);
}

/*****************************************************************************
** Function name:fnMX25LXX_Buf_Read
**
** Description:��ȡMX25LXX�е�����
**
** Parameters:  Dst ��ȡ���ݴ��BUF  Src ��ȡ���ݵ�ַ   Len ��ȡ���ݳ���
**
** Returned value:SUCCESS OR ERROR
**
******************************************************************************/
ErrorStatus fnMX25LXX_Buf_Read(u8 *Dst, u32 Src, u32 Len)
{
    if (Src > MX25L_MAX_AD)
    {
        return (ERROR);
    }
    if (Len > MX25L_MAX_AD - Src)
    {
        Len = MX25L_MAX_AD - Src;
    }

    if (fnMX25LXX_WaitRdy(MX25LXX_TIMEOUT) != SUCCESS)
    {
        return (ERROR);
    }

    ENABLE_FLASH_MX25LXX();
    BSP_FlashSpi_WriteByte(CMD_READ);
    BSP_FlashSpi_WriteByte((Src >> 16) & 0xff);
    BSP_FlashSpi_WriteByte((Src >> 8) & 0xff);
    BSP_FlashSpi_WriteByte(Src & 0xff);

    for (; Len != 0 ; Len--)
    {
        *Dst++ = BSP_FlashSpi_ReadByte();
    }
    DISABLE_FLASH_MX25LXX();
    return (SUCCESS);
}

/*****************************************************************************
** Function name:fnMX25LXX_MMPage_Prog_Through_Buf
**
** Description:������д��MX25LXX��
**
** Parameters:Dst д��Ŀ���ַ Src д�����ݴ��ָ�� Len ���ݳ���
**
** Returned value:SUCCESS OR ERROR
**
******************************************************************************/
ErrorStatus fnMX25LXX_MMPage_Prog_Through_Buf(u32 Dst, u8 *Src, u32 Len)
{
    if (Dst > MX25L_MAX_AD)
    {
        return (ERROR);
    }
    if (Len > MX25L_MAX_AD - Dst)
    {
        Len = MX25L_MAX_AD - Dst;
    }
    if (fnMX25LXX_WaitRdy(MX25LXX_TIMEOUT) != SUCCESS)
    {
        return (ERROR);
    }
    fnMX25LXX_SetWritable(1);
    PinMode_MX25LSCK(GPIO_MODE_OUT);
    PinMode_MX25LMOSI(GPIO_MODE_OUT);
    PinMode_MX25LMISO(GPIO_MODE_IN);
    ENABLE_FLASH_MX25LXX();
    BSP_FlashSpi_WriteByte(CMD_PAGE_PROGRAM);
    BSP_FlashSpi_WriteByte((Dst >> 16) & 0xff);
    BSP_FlashSpi_WriteByte((Dst >> 8) & 0xff);
    BSP_FlashSpi_WriteByte(Dst & 0xff);

    for (; Len != 0 ; Len--)
    {
        BSP_FlashSpi_WriteByte(*Src++);
    }

    DISABLE_FLASH_MX25LXX();
    return (SUCCESS);
}

/*****************************************************************************
** Function name:fnMX25LXX_CheckDat
**
** Description:���BUF��������MX25LXX��
**
** Parameters:Dst ���ݴ�ŵ�ַ  Src ��ȡĿ���ַ Len ��ȡ����
**
** Returned value: SUCCESS OR ERROR
**
******************************************************************************/
ErrorStatus fnMX25LXX_CheckDat(u8 *Dst, u32 Src, u32 Len)
{
    u32 i;
    u8  temp;
    if (Src > MX25L_MAX_AD)
    {
        return (ERROR);
    }
    if (fnMX25LXX_WaitRdy(MX25LXX_TIMEOUT) != SUCCESS)
    {
        return (ERROR);
    }
    ENABLE_FLASH_MX25LXX();
    BSP_FlashSpi_WriteByte(CMD_READ);
    BSP_FlashSpi_WriteByte((Src >> 16) & 0xff);
    BSP_FlashSpi_WriteByte((Src >> 8) & 0xff);
    BSP_FlashSpi_WriteByte(Src & 0xff);
    for (i = 0; i < Len; i++)
    {
        temp = BSP_FlashSpi_ReadByte();
        if (Dst[i] != temp)
        {
            DISABLE_FLASH_MX25LXX();
            return (ERROR);
        }
    }
    DISABLE_FLASH_MX25LXX();
    return (SUCCESS);
}

/*****************************************************************************
** Function name:   fnMX25LXX_Read
**
** Description:     MX25LXX������
**
** Parameters:      Dst �����ݴ�ŵ�ַ  Src ƫ�Ƶ�ַ  DatLen ���ݳ��� Repeat�ظ�����
**
** Returned value:  SUCCESS OR  ERROR
**
******************************************************************************/
ErrorStatus fnMX25LXX_Read(u8 *Dst, u32 Src, u32 DatLen, u8 Repeat)
{
    #if !DL645SOFT_DEBUG
    u8  i;
    PinMode_MX25LSCK(GPIO_MODE_OUT);
    PinMode_MX25LMOSI(GPIO_MODE_OUT);
    PinMode_MX25LMISO(GPIO_MODE_IN);

    for (i = 0 ; i < Repeat ; i++)
    {
        fnMX25LXX_Buf_Read(Dst, Src, DatLen);
        if (fnMX25LXX_CheckDat(Dst, Src, DatLen) != SUCCESS)
        {
            continue;
        }
        break;
    }
    if (i >= Repeat)
    {
        return (ERROR);
    }
    return (SUCCESS);
    #else
    return (SUCCESS);
    #endif
}

/*****************************************************************************
** Function name:fnMX25LXX_Write
**
** Description: MX25LXXд����
**
** Parameters:Dst д�����ݵ�ַ  Src д������BUF DatLen ���ݳ���  Repeat �����ظ�����
**
** Returned value:SUCCESS OR ERROR
**
******************************************************************************/
ErrorStatus fnMX25LXX_Write(u32 Dst, u8 *Src, u32 DatLen, u8 Repeat)
{
    #if !DL645SOFT_DEBUG

    u32 Page;
    u32 OnceDatLen;
    u32 PageDatLen;
    u8  i;

    while (DatLen > 0)
    {
        if (fnMX25LXX_SetWritable(1) != SUCCESS)
        {
            return (ERROR);    // ��дʹ�ܣ���ҳдʱ��ÿ�ζ���ʼ��
        }

        (DatLen > MX25L_SECTOR_SIZE - Dst % MX25L_SECTOR_SIZE) ?
        (OnceDatLen = MX25L_SECTOR_SIZE - Dst % MX25L_SECTOR_SIZE) : (OnceDatLen = DatLen);

        fnWDT_Restart();
        Page = (Dst / MX25L_SECTOR_SIZE) * MX25L_SECTOR_SIZE;
        if (fnMX25LXX_MMPage_To_Buf(Page) != SUCCESS)
        {
            fnMX25LXX_SetWritable(0);
            return (ERROR);
        }
        Std_Memcpy(&MX25LData.Buf[Dst % MX25L_SECTOR_SIZE], Src, OnceDatLen);

        fnMX25LXX_eraseSector(Page);
        PageDatLen = 0;
        while (PageDatLen < MX25L_SECTOR_SIZE)
        {
            fnWDT_Restart();
            for (i = 0 ; i < Repeat ; i++)
            {
                if (fnMX25LXX_MMPage_Prog_Through_Buf(Page, &MX25LData.Buf[PageDatLen], MX25L_PAGE_SIZE) != SUCCESS)
                {
                    continue;
                }
                if (fnMX25LXX_CheckDat(&MX25LData.Buf[PageDatLen], Page, MX25L_PAGE_SIZE) != SUCCESS)
                {
                    continue;
                }
                break;
            }
            if (i >= Repeat)
            {
                fnMX25LXX_SetWritable(0);
                return (ERROR);
            }
            PageDatLen += MX25L_PAGE_SIZE;
            Page += MX25L_PAGE_SIZE;
        }
        fnWDT_Restart();
        Dst += OnceDatLen;
        Src += OnceDatLen;
        DatLen -= OnceDatLen;
        fnWDT_Restart();
    }
    fnMX25LXX_SetWritable(0);
    return (SUCCESS);
    #else
    return (SUCCESS);
    #endif
}
