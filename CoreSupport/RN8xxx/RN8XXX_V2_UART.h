/*!
    \file    RN8XXX_V2_UART.h
    \brief   definitions for the UART

    \version 2023,03,07, V1.0.0, firmware for rn8xxx_v2
*/
#ifndef RN8XXX_V2_UART_H
#define RN8XXX_V2_UART_H

#include "RN8XXX_V2.h"

/* UART_CTRL */
#define UART_CTRL_EN                 BIT(0)        /*!< UART module enable bit */
#define UART_CTRL_TXIE               BIT(1)        /*!< transmit interrupt enable bit */
#define UART_CTRL_RXIE               BIT(2)        /*!< receive interrupt enable bit */
#define UART_CTRL_ERRIE              BIT(3)        /*!< error interrupt enable bit */
#define UART_CTRL_STOPS              BIT(4)        /*!< stop bits width selection */
#define UART_CTRL_DATLEN             BITS(5,6)     /*!< data length of frame format */
#define UART_CTRL_PARS               BITS(7,9)     /*!< parity type selection */
#define UART_CTRL_IRE                BIT(10)       /*!< infra-red modulation enable */
#define UART_CTRL_ILBE               BIT(11)       /*!< inner loopback enable */
#define UART_CTRL_IRSEL              BIT(12)       /*!< infra-red modulation polarity selection */
#define UART_CTRL_LMSB               BIT(13)       /*!< LSB/MSB transfer mode selection */
#define UART_CTRL_NEG                BIT(14)       /*!< UART transfer bit polarity selection */

/* UART_BAUD  */
#define UART_BAUD_CLKDIV             BITS(0,12)        /*!< baud rate configuration bits */

/* UART_STA */
#define UART_STA_RX                  BIT(0)        /*!< receive finish flag */
#define UART_STA_TX                  BIT(1)        /*!< transmit finish flag */
#define UART_STA_PE                  BIT(2)        /*!< parity error flag */
#define UART_STA_OE                  BIT(3)        /*!< overflow error flag */
#define UART_STA_FE                  BIT(4)        /*!< frame error flag */
#define UART_STA_DE                  BIT(5)        /*!< data error flag */
#define UART_STA_RB                  BIT(6)        /*!< receive busy flag */
#define UART_STA_TB                  BIT(7)        /*!< transmit busy  flag */
#define UART_STA_tx_fifo_empty       BIT(8)        /*!< transmit fifo empty flag */
#define UART_STA_tx_fifo_full        BIT(9)        /*!< transmit fifo full flag */

/* UART_TXD */
#define UART_TXD_TXDATA              BITS(0,7)     /*!< transmit data value */
#define UART_TXD_UP                  BIT(8)        /*!< user-defined parity bit(valid when user-defined parity selected) */

/* UART_RXD */
#define UART_RXD_RXDATA              BITS(0,7)     /*!< read data value */
#define UART_RXD_UP                  BIT(8)        /*!< user-defined parity bit(valid when user-defined parity selected) */

/* UART_FDIV */
#define UART_FDIV                    BITS(0,13)    /*!< baud rate fractional part */

/* UART_DMA_CTL */
#define UART_DMA_CTL_TX_DMA_EN      BIT(0)     /*!< UART TX DMA enable */
#define UART_DMA_CTL_RX_DMA_EN      BIT(1)     /*!< UART RX DMA enable */
#define UART_DMA_CTL_TX_CYC_MODE    BIT(2)     /*!< UART TX loop mode enable */
#define UART_DMA_CTL_RX_CYC_MODE    BIT(3)     /*!< UART RX loop mode enable */
#define UART_DMA_CTL_DMA_PARS       BIT(4)     /*!< UART DMA parity */

/* UART_DMA_TBADR */
#define UART_DMA_TBADR        BITS(0,16)  /*!< UART DMA TX base address */

/* UART_DMA_RBADR */
#define UART_DMA_RBADR        BITS(0,16)  /*!< UART DMA RX base address */

/* UART_DMA_TLEN */
#define UART_DMA_TLEN         BITS(0,16)  /*!< UART DMA TX length */

/* UART_DMA_RLEN */
#define UART_DMA_RLEN         BITS(0,16)  /*!< UART DMA RX length */

/* UART_DMA_TADRV */
#define UART_DMA_TADR         BITS(0,16)  /*!< UART DMA TX current address */

/* UART_DMA_RADR */
#define UART_DMA_RADR         BITS(0,16)  /*!< UART DMA RX current address */

/* UART_DMA_IE */
#define UART_DMA_IE_TX_HIE          BIT(0)     /*!< DMA TX half-full interrupt enable bit */
#define UART_DMA_IE_TX_FIE          BIT(1)     /*!< DMA TX empty interrupt enable bit */
#define UART_DMA_IE_RX_HIE          BIT(2)     /*!< DMA RX half-full interrupt enable bit */
#define UART_DMA_IE_RX_FIE          BIT(3)     /*!< DMA RX full interrupt enable bit */
#define UART_DMA_IE_TX_ERR_IE       BIT(4)     /*!< DMA TX error interrupt enable bit */
#define UART_DMA_IE_RX_ERR_IE       BIT(5)     /*!< DMA RX error interrupt enable bit */

/* UART_DMA_IF */
#define UART_DMA_IF_TX_HIF          BIT(0)     /*!< DMA TX half-full interrupt flag */
#define UART_DMA_IF_TX_FIF          BIT(1)     /*!< DMA TX empty interrupt flag */
#define UART_DMA_IF_RX_HIF          BIT(2)     /*!< DMA RX half-full interrupt flag */
#define UART_DMA_IF_RX_FIF          BIT(3)     /*!< DMA RX full interrupt flag */
#define UART_DMA_IF_RX_ERR_IF       BIT(5)     /*!< DMA RX error interrupt flag */
#define UART_DMA_IF_RX_DONE_IF      BIT(6)     /*!< DMA RX done interrupt flag */

/* UART_DMA_TO */
#define UART_DMA_TIMEOUT_CNT        BITS(0,3)  /*!< DMA time out counter */

/* constants definitions */
/* UART_CTRL_STOPS stop bits width selection definition*/
#define UART_CTRL_STOPS_2BIT        UART_CTRL_STOPS          /*!< stop bit_width select 2 bit */
#define UART_CTRL_STOPS_1BIT        ((uint32_t)0x00000000U)   /*!< stop bit_width select 1 bit */

/* UART_CTRL_DATLEN data length of frame format selection */
#define U_DATLEN(regval) (UART_CTRL_DATLEN & ((uint32_t)(regval) << 5))
#define UART_CTRL_DATLEN5           U_DATLEN(0)               /* select 5 bits of data field */
#define UART_CTRL_DATLEN6           U_DATLEN(1)               /* select 6 bits of data field */
#define UART_CTRL_DATLEN7           U_DATLEN(2)               /* select 7 bits of data field */
#define UART_CTRL_DATLEN8           U_DATLEN(3)               /* select 8 bits of data field */

/* UART_CTRL_PARS parity type selection */
#define U_CTRL_PARS(regval) (UART_CTRL_PARS & ((uint32_t)(regval) << 7))
#define UART_CTRL_PARS_NUL          U_CTRL_PARS(0)    /*!< parity type select no parity */
#define UART_CTRL_PARS_ODD          U_CTRL_PARS(1)    /*!< parity type select odd parity */
#define UART_CTRL_PARS_EVEN         U_CTRL_PARS(2)    /*!< parity type select even parity */
#define UART_CTRL_PARS_0            U_CTRL_PARS(3)    /*!< parity type select stick_zero parity */
#define UART_CTRL_PARS_1            U_CTRL_PARS(4)    /*!< parity type select stick one parity */
#define UART_CTRL_PARS_USER         U_CTRL_PARS(5)    /*!< parity type select user_defined parity */

/* UART_CTRL_IRSEL infra-red modulation polarity selection */
#define UART_CTRL_IRSEL_P           ((uint32_t)0x00000000U)    /*!< positive polarity. default driving voltage is high */
#define UART_CTRL_IRSEL_N           UART_CTRL_IRSEL            /*!< negative polarity. default driving voltage is low */

/* UART_CTRL_LMSB LSB/MSB transfer mode selection */
#define UART_CTRL_LMSB_L            ((uint32_t)0x00000000U)    /*!< LSB first transfer mode */
#define UART_CTRL_LMSB_M            UART_CTRL_LMSB             /*!< MSB first transfer mode */

/* UART_CTRL_NEG UART transfer bit polarity selection */
#define UART_CTRL_NEG_P             ((uint32_t)0x00000000U)    /*!< positive polarity. default driving voltage is high */
#define UART_CTRL_NEG_N             UART_CTRL_NEG              /*!< negative polarity. default driving voltage is low */

#endif /* RN8XXX_V2_UART_H */

// -*- r32775 -*-
