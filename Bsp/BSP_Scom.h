#ifndef _BSP_SCOM_H
#define _BSP_SCOM_H

typedef enum
{
    SCOM_PORT_RS485A = 0,
    SCOM_PORT_SPI = 1,
    SCOM_PORT_ZBCOM = 2,
    SCOM_PORT_IR    = 3, //红外通信口
    SCOM_PORT_RS485B = 4,
    SCOM_PORT_MAX   = 2,
} eScomPort_TypeDef;

#endif
