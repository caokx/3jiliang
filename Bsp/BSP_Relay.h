/****************************************************************************
* @file     BSP_Relay.h
* @author   Renergy Application Team
* @version  V1.0.1
* @date     2021.10.14
* @brief    板级层继电器
******************************************************************************
* @attention
*
*
****************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BSP_RELAY_H_
#define _BSP_RELAY_H_

/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/

#define LOADRELAYPULSTIMEDEF   200/*""*/

#define BSP_RELAY_TimeScan()      {if(LoadRelayPulseStamp !=0 )\
        {\
            LoadRelayPulseStamp--;\
            if(LoadRelayPulseStamp ==0 )\
            {GPIO_WRITE_PIN10_5(0);GPIO_WRITE_PIN10_6(0);}\
        }\
    }

/* Exported enum ------------------------------------------------------------*/
typedef enum
{
    Relay_Load_ID = 0,      /*"负荷开关继电器"*/
    Relay_Warn_ID,          /*"报警继电器"*/

    Relay_NUM,
} BSP_RelayID_TypeDef;       /*"继电器ID定义"*/

typedef enum
{
    RelayCmdClose = 0,   /*"继电器合闸"*/
    RelayCmdOpen = 1,    /*"继电器拉闸"*/
} eRelayCmd_TypeDef; /*"继电器控制命令"*/

typedef enum
{
    Relay_MagneticLatch = 0,    /*"磁保持继电器"*/
    Relay_ElectricLatch,        /*"电保持继电器"*/
} BSP_RelayType_TypeDef;     /*"继电器类型定义"*/

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint16_t RelayActionStamp;
    uint16_t RelayRestStamp;
} sBSP_RelayOperParm_TypeDef;

/* Exported data  ----------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void BSP_RelayInit(void);
extern void BSP_RelayCtrl(BSP_RelayID_TypeDef RelayID, eRelayCmd_TypeDef RelayCmd);
extern void BSP_Relay_TimeScan(void);

#endif

/****************************   (C) COPYRIGHT Renergy   ****************************/
/****************************       END OF FILE     ********************************/
