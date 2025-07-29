
#define  _DRIVE_M2M_GLOBALS
#include <CoreSupport.h>
#include <Rn8xxx_Common.h>
#include <Rn8xxx_M2M.h>

/*********************************************************************************************************
** Function name:          Rn8xxx_M2M_Move
** Descriptions:             M2M 数据搬运
** input parameters:      M2M_ModePara:搬运模式配置
**                  SAddr:源数据地址
**                  DAddr:目标数据地址
**                  ILen:源数据长度
** output parameters:   NONE
** Returned value:      SUCCESEE  or ERROR
*********************************************************************************************************/
ErrorStatus Rn8xxx_M2M_Move(uM2M_ModePara_TypeDef M2M_ModePara, u32 SAddr, u32 DAddr, u16 ILen)
{
    M2M->CTL = 0;       //停止上一次搬运;
    M2M->MODE = M2M_ModePara.gMode;
    //M2M->DUMMY    = M2M_ModePara.Mode_DUMMY;
    M2M->SADDR = (SAddr & 0x0001FFFF);  //数据源地址
    M2M->DADDR = (DAddr & 0x0001FFFF); //目标地址

    M2M->ILEN = ILen;  //len
    M2M->CTL = 1;   //启动搬运

    if (fnRegState_Detect((u32)(&M2M->IF), 0, 1, M2M_TimeOut) == ERROR)
    {
        return (ERROR);    //等待转换完成
    }

    M2M->IF = 0x01;  //clear If

    return SUCCESS;
}

//------------------------------------------------------------------------------
