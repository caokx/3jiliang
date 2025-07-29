/****************************************************************************
* @file     BSP_Relay.c
* @author   Renergy Application Team
* @version  V1.0.1
* @date     2021.10.14
* @brief    板级层继电器
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include <BSP.h>
/* Private define ------------------------------------------------------------*/

/* Private enum -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
    BSP_RelayID_TypeDef     RelayID;
    BSP_RelayType_TypeDef   RelayType;
    uint8_t                 RelayON_PinId;
    uint8_t                 RelayOFF_PinId;/*"电保持继电器次配置为_PIN_nMAX"*/
    uint16_t                RelayCloseTime;/*"合闸驱动时间  ;电保持继电器次配置为0"*/
    uint16_t                RelayOpenTime;/*"拉闸驱动时间  ;电保持继电器次配置为0"*/
    uint16_t                RelayRestTime;/*"操作完继电器后至少休息时间;电保持继电器次配置为0"*/
} sBSP_RelayCfg_TypeDef;

/* Private data ---------------------------------------------------------*/
sBSP_RelayOperParm_TypeDef  RelayOperParm[Relay_NUM];/*"继电器运行参数"*/

/*"继电器配置表格，根据实际硬件配置*/
const sBSP_RelayCfg_TypeDef RelayCfgTable[Relay_NUM] =
{
    {Relay_Load_ID,     Relay_MagneticLatch,    PinLoadRelayON,     PinLoadRelayOFF,    150,    150,    150     },
    {Relay_Warn_ID,     Relay_ElectricLatch,    PinWarn,            _PIN_nMAX,          0,      0,      0       },
};
/* Exported data  ----------------------------------------------------------*/

/* Private functions ------------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/
/*****************************************************************************
** Function name:BSP_RelayCtrl
** Description:　继电器初始化
** Parameters:
** Returned value:NONE
******************************************************************************/
void BSP_RelayInit(void)
{
    uint8_t u8i;

    Std_Memset(&RelayOperParm, 0x00, sizeof(RelayOperParm));

    for (u8i = 0; u8i < Relay_NUM; u8i++)
    {
        Rn8xxx_GPIO_CfgFun(RelayCfgTable[u8i].RelayON_PinId, _NORMALIO);
        Rn8xxx_GPIO_CfgIOMode(RelayCfgTable[u8i].RelayON_PinId, GPIO_MODE_OUT, NORMAL_OUT);

        if (RelayCfgTable[u8i].RelayType == Relay_MagneticLatch) /*"磁保持继电器有两根驱动线"*/
        {
            Rn8xxx_GPIO_CfgFun(RelayCfgTable[u8i].RelayOFF_PinId, _NORMALIO);
            Rn8xxx_GPIO_CfgIOMode(RelayCfgTable[u8i].RelayOFF_PinId, GPIO_MODE_OUT, NORMAL_OUT);
        }
    }
}

/*****************************************************************************
** Function name:BSP_RelayCtrl
** Description:　多功能端子输出信号类型选择
** Parameters:
** Returned value:NONE
******************************************************************************/
void BSP_RelayCtrl(BSP_RelayID_TypeDef RelayID, eRelayCmd_TypeDef RelayCmd)
{
    if (RelayID == RelayCfgTable[RelayID].RelayID)
    {
        if (RelayCfgTable[RelayID].RelayType == Relay_ElectricLatch)
        {
            if (RelayCmd == RelayCmdOpen)
            {
                Rn8xxx_GPIO_SetPin(RelayCfgTable[RelayID].RelayON_PinId, 1);
            }
            else
            {
                Rn8xxx_GPIO_SetPin(RelayCfgTable[RelayID].RelayON_PinId, 0);
            }
        }
        else if ((RelayCfgTable[RelayID].RelayType == Relay_MagneticLatch)
                 && (RelayOperParm[RelayID].RelayActionStamp == 0)
                 && (RelayOperParm[RelayID].RelayRestStamp == 0))
        {
            if (RelayCmd == RelayCmdOpen)
            {
                Rn8xxx_GPIO_SetPin(RelayCfgTable[RelayID].RelayOFF_PinId, 0);
                Rn8xxx_GPIO_SetPin(RelayCfgTable[RelayID].RelayON_PinId, 1);
                RelayOperParm[RelayID].RelayActionStamp = RelayCfgTable[RelayID].RelayOpenTime;
            }
            else
            {
                Rn8xxx_GPIO_SetPin(RelayCfgTable[RelayID].RelayON_PinId, 0);
                Rn8xxx_GPIO_SetPin(RelayCfgTable[RelayID].RelayOFF_PinId, 1);
                RelayOperParm[RelayID].RelayActionStamp = RelayCfgTable[RelayID].RelayCloseTime;
            }
        }
    }
}

/*****************************************************************************
** Function name:BSP_RelayCtrl
** Description:　多功能端子输出信号类型选择
** Parameters:
** Returned value:NONE
******************************************************************************/
void BSP_Relay_TimeScan(void)
{
    uint8_t u8i;

    for (u8i = 0; u8i < Relay_NUM; u8i++)
    {
        if (RelayOperParm[u8i].RelayActionStamp != 0)
        {
            RelayOperParm[u8i].RelayActionStamp--;

            if (RelayOperParm[u8i].RelayActionStamp == 0)
            {
                Rn8xxx_GPIO_SetPin(RelayCfgTable[u8i].RelayON_PinId, 0);
                Rn8xxx_GPIO_SetPin(RelayCfgTable[u8i].RelayOFF_PinId, 0);
            }
            RelayOperParm[u8i].RelayRestStamp = RelayCfgTable[u8i].RelayRestTime;
        }
        if (RelayOperParm[u8i].RelayRestStamp != 0)
        {
            RelayOperParm[u8i].RelayRestStamp--;
        }
    }
}

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
