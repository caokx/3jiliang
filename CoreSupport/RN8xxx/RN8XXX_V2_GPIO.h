/*!
    \file    RN8XXX_V2_GPIO.h
    \brief   definitions for the GPIO

    \version 2023,03,07, V1.0.0, firmware for rn8xxx_v2
*/
#ifndef RN8XXX_V2_GPIO_H
#define RN8XXX_V2_GPIO_H

#include "RN8XXX_V2.h"

/* bits definitions */
/* PMA */
#define GPIO_PMA_PM00      BIT(0)        /*!< P00 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM01      BIT(1)        /*!< P01 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM02      BIT(2)        /*!< P02 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM03      BIT(3)        /*!< P03 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM04      BIT(4)        /*!< P04 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM05      BIT(5)        /*!< P05 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM10      BIT(8)        /*!< P10 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM11      BIT(9)        /*!< P11 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM12      BIT(10)       /*!< P12 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM13      BIT(11)       /*!< P13 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM14      BIT(12)       /*!< P14 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM15      BIT(13)       /*!< P15 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM16      BIT(14)       /*!< P16 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM17      BIT(15)       /*!< P17 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM20      BIT(16)       /*!< P20 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM21      BIT(17)       /*!< P21 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM22      BIT(18)       /*!< P22 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM23      BIT(19)       /*!< P23 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM24      BIT(20)       /*!< P24 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM25      BIT(21)       /*!< P25 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM26      BIT(22)       /*!< P26 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM27      BIT(23)       /*!< P27 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM30      BIT(24)       /*!< P30 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM31      BIT(25)       /*!< P31 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM32      BIT(26)       /*!< P32 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM33      BIT(27)       /*!< P33 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM34      BIT(28)       /*!< P34 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM35      BIT(29)       /*!< P35 input(1)/output(0) mode selection bit */
#define GPIO_PMA_PM36      BIT(30)       /*!< P36 input(1)/output(0) mode state bit, only use as input port */
#define GPIO_PMA_PM37      BIT(31)       /*!< P37 input(1)/output(0) mode state bit, only use as input port */

/* PAPIN PA */
#define GPIO_PAPIN_P00     BIT(0)       /*!< port A P00 data */
#define GPIO_PAPIN_P01     BIT(1)       /*!< port A P01 data */
#define GPIO_PAPIN_P02     BIT(2)       /*!< port A P02 data */
#define GPIO_PAPIN_P03     BIT(3)       /*!< port A P03 data */
#define GPIO_PAPIN_P04     BIT(4)       /*!< port A P04 data */
#define GPIO_PAPIN_P05     BIT(5)       /*!< port A P05 data */
#define GPIO_PAPIN_P10     BIT(8)       /*!< port A P10 data */
#define GPIO_PAPIN_P11     BIT(9)       /*!< port A P11 data */
#define GPIO_PAPIN_P12     BIT(10)      /*!< port A P12 data */
#define GPIO_PAPIN_P13     BIT(11)      /*!< port A P13 data */
#define GPIO_PAPIN_P14     BIT(12)      /*!< port A P14 data */
#define GPIO_PAPIN_P15     BIT(13)      /*!< port A P15 data */
#define GPIO_PAPIN_P16     BIT(14)      /*!< port A P16 data */
#define GPIO_PAPIN_P17     BIT(15)      /*!< port A P17 data */
#define GPIO_PAPIN_P20     BIT(16)      /*!< port A P20 data */
#define GPIO_PAPIN_P21     BIT(17)      /*!< port A P21 data */
#define GPIO_PAPIN_P22     BIT(18)      /*!< port A P22 data */
#define GPIO_PAPIN_P23     BIT(19)      /*!< port A P23 data */
#define GPIO_PAPIN_P24     BIT(20)      /*!< port A P24 data */
#define GPIO_PAPIN_P25     BIT(21)      /*!< port A P25 data */
#define GPIO_PAPIN_P26     BIT(22)      /*!< port A P26 data */
#define GPIO_PAPIN_P27     BIT(23)      /*!< port A P27 data */
#define GPIO_PAPIN_P30     BIT(24)      /*!< port A P30 data */
#define GPIO_PAPIN_P31     BIT(25)      /*!< port A P31 data */
#define GPIO_PAPIN_P32     BIT(26)      /*!< port A P32 data */
#define GPIO_PAPIN_P33     BIT(27)      /*!< port A P33 data */
#define GPIO_PAPIN_P34     BIT(28)      /*!< port A P34 data */
#define GPIO_PAPIN_P35     BIT(29)      /*!< port A P35 data */
#define GPIO_PAPIN_P36     BIT(30)      /*!< port A P36 data */
#define GPIO_PAPIN_P37     BIT(31)      /*!< port A P37 data */

/* PCA0 */
#define GPIO_PCA0_PC00       BITS(0,1)    /*!< P00 mode cfg bit */
#define GPIO_PCA0_PC01       BITS(2,3)    /*!< P01 mode cfg bit */
#define GPIO_PCA0_PC02       BIT(4)       /*!< P02 mode cfg bit */
#define GPIO_PCA0_PC03       BIT(5)       /*!< P03 mode cfg bit */
#define GPIO_PCA0_PC04       BIT(6)       /*!< P04 mode cfg bit */
#define GPIO_PCA0_PC05       BIT(7)       /*!< P05 mode cfg bit */
#define GPIO_PCA0_KEY4_SEL   BIT(8)       /*!< key4 mode selection bit*/
#define GPIO_PCA0_PC10       BITS(9,10)   /*!< P10 mode cfg bit  */
#define GPIO_PCA0_PC11       BITS(11,12)  /*!< P11 mode cfg bit  */
#define GPIO_PCA0_PC12       BITS(13,14)  /*!< P12 mode cfg bit  */
#define GPIO_PCA0_PC13       BITS(15,16)  /*!< P13 mode cfg bit  */
#define GPIO_PCA0_PC14       BITS(17,18)  /*!< P14 mode cfg bit  */
#define GPIO_PCA0_PC15       BITS(19,20)  /*!< P15 mode cfg bit  */
#define GPIO_PCA0_PC16       BITS(21,22)  /*!< P16 mode cfg bit  */
#define GPIO_PCA0_PC17       BITS(23,24)  /*!< P17 mode cfg bit  */
#define GPIO_PCA0_PC201      BIT(25)      /*!< P20 and P21 mode cfg bit  */
#define GPIO_PCA0_PC223      BIT(26)      /*!< P22 and P23 mode cfg bit  */
#define GPIO_PCA0_PC245      BIT(27)      /*!< P24 and P25 mode cfg bit  */
#define GPIO_PCA0_PC267      BIT(28)      /*!< P26 and P27 mode cfg bit  */
#define GPIO_PCA0_SWD_SEL    BIT(29)      /*!< SWD selection */
#define GPIO_PCA0_UART2_SEL  BITS(30,31)  /*!< UART2 selection */

/* PCA1 */
#define GPIO_PCA1_PC30       BITS(0,1)      /*!< P30 mode cfg bit */
#define GPIO_PCA1_PC31       BITS(2,3)      /*!< P31 mode cfg bit */
#define GPIO_PCA1_PC32       BITS(4,5)      /*!< P32 mode cfg bit */
#define GPIO_PCA1_PC33       BITS(6,7)      /*!< P33 mode cfg bit */
#define GPIO_PCA1_PC34       BITS(8,9)      /*!< P34 mode cfg bit */
#define GPIO_PCA1_PC35       BITS(10,11)    /*!< P35 mode cfg bit */
#define GPIO_PCA1_PC36       BITS(12,13)    /*!< P36 mode cfg bit */
#define GPIO_PCA1_PC37       BITS(14,15)    /*!< P37 mode cfg bit */
#define GPIO_PCA1_PC223_2    BIT(16)        /*!< P22 and P23 second mode cfg bit */
#define GPIO_PCA1_PC267_2    BIT(17)        /*!< P26 and P27 second mode cfg bit */

/* PUA */
#define GPIO_PUA_PU00       BIT(0)          /*!< P00 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU01       BIT(1)          /*!< P01 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU02       BIT(2)          /*!< P02 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU03       BIT(3)          /*!< P03 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU04       BIT(4)          /*!< P04 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU05       BIT(5)          /*!< P05 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU10       BIT(8)          /*!< P10 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU11       BIT(9)          /*!< P11 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU12       BIT(10)         /*!< P12 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU13       BIT(11)         /*!< P13 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU14       BIT(12)         /*!< P14 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU15       BIT(13)         /*!< P15 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU16       BIT(14)         /*!< P16 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU17       BIT(15)         /*!< P17 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU20       BIT(16)         /*!< P20 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU21       BIT(17)         /*!< P21 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU22       BIT(18)         /*!< P22 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU23       BIT(19)         /*!< P23 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU24       BIT(20)         /*!< P24 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU25       BIT(21)         /*!< P25 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU26       BIT(22)         /*!< P26 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU27       BIT(23)         /*!< P27 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU30       BIT(24)         /*!< P30 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU31       BIT(25)         /*!< P31 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU32       BIT(26)         /*!< P32 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU33       BIT(27)         /*!< P33 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU34       BIT(28)         /*!< P34 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU35       BIT(29)         /*!< P35 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU36       BIT(30)         /*!< P36 pull up cfg bit (=0 do not pull up, =1 pull up) */
#define GPIO_PUA_PU37       BIT(31)         /*!< P37 pull up cfg bit (=0 do not pull up, =1 pull up) */

/* PIMA */
#define GPIO_PIMA_PID10     BIT(0)      /*!< P10 output mode cfg bit */
#define GPIO_PIMA_PID11     BIT(1)      /*!< P11 output mode cfg bit */
#define GPIO_PIMA_PID12     BIT(2)      /*!< P12 output mode cfg bit */
#define GPIO_PIMA_PID13     BIT(3)      /*!< P13 output mode cfg bit */
#define GPIO_PIMA_PID14     BIT(4)      /*!< P14 output mode cfg bit */
#define GPIO_PIMA_PID15     BIT(5)      /*!< P15 output mode cfg bit */
#define GPIO_PIMA_PID16     BIT(6)      /*!< P16 output mode cfg bit */
#define GPIO_PIMA_PID17     BIT(7)      /*!< P17 output mode cfg bit */
#define GPIO_PIMA_PID20     BIT(8)      /*!< P20 output mode cfg bit */
#define GPIO_PIMA_PID21     BIT(9)      /*!< P21 output mode cfg bit */
#define GPIO_PIMA_PID22     BIT(10)     /*!< P22 output mode cfg bit */
#define GPIO_PIMA_PID23     BIT(11)     /*!< P23 output mode cfg bit */
#define GPIO_PIMA_PID24     BIT(12)     /*!< P24 output mode cfg bit */
#define GPIO_PIMA_PID25     BIT(13)     /*!< P25 output mode cfg bit */
#define GPIO_PIMA_PID26     BIT(14)     /*!< P26 output mode cfg bit */
#define GPIO_PIMA_PID27     BIT(15)     /*!< P27 output mode cfg bit */
#define GPIO_PIMA_PIL10     BIT(16)     /*!< P10 input cfg bit */
#define GPIO_PIMA_PIL11     BIT(17)     /*!< P11 input cfg bit */
#define GPIO_PIMA_PIL12     BIT(18)     /*!< P12 input cfg bit */
#define GPIO_PIMA_PIL13     BIT(19)     /*!< P13 input cfg bit */
#define GPIO_PIMA_PIL14     BIT(20)     /*!< P14 input cfg bit */
#define GPIO_PIMA_PIL15     BIT(21)     /*!< P15 input cfg bit */
#define GPIO_PIMA_PIL16     BIT(22)     /*!< P16 input cfg bit */
#define GPIO_PIMA_PIL17     BIT(23)     /*!< P17 input cfg bit */
#define GPIO_PIMA_PIL20     BIT(24)     /*!< P20 input cfg bit */
#define GPIO_PIMA_PIL21     BIT(25)     /*!< P21 input cfg bit */
#define GPIO_PIMA_PIL22     BIT(26)     /*!< P22 input cfg bit */
#define GPIO_PIMA_PIL23     BIT(27)     /*!< P23 input cfg bit */
#define GPIO_PIMA_PIL24     BIT(28)     /*!< P24 input cfg bit */
#define GPIO_PIMA_PIL25     BIT(29)     /*!< P25 input cfg bit */
#define GPIO_PIMA_PIL26     BIT(30)     /*!< P26 input cfg bit */
#define GPIO_PIMA_PIL27     BIT(31)     /*!< P27 input cfg bit */

/* PIEA */
#define GPIO_PIEA_PIE00    BIT(0)       /*!< P00 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE01    BIT(1)       /*!< P01 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE02    BIT(2)       /*!< P02 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE03    BIT(3)       /*!< P03 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE04    BIT(4)       /*!< P04 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE05    BIT(5)       /*!< P05 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE10    BIT(8)       /*!< P10 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE11    BIT(9)       /*!< P11 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE12    BIT(10)      /*!< P12 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE13    BIT(11)      /*!< P13 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE14    BIT(12)      /*!< P14 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE15    BIT(13)      /*!< P15 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE16    BIT(14)      /*!< P16 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE17    BIT(15)      /*!< P17 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE20    BIT(16)      /*!< P20 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE21    BIT(17)      /*!< P21 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE22    BIT(18)      /*!< P22 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE23    BIT(19)      /*!< P23 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE24    BIT(20)      /*!< P24 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE25    BIT(21)      /*!< P25 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE26    BIT(22)      /*!< P26 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE27    BIT(23)      /*!< P27 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE30    BIT(24)      /*!< P30 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE31    BIT(25)      /*!< P31 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE32    BIT(26)      /*!< P32 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE33    BIT(27)      /*!< P33 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE34    BIT(28)      /*!< P34 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE35    BIT(29)      /*!< P35 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE36    BIT(30)      /*!< P36 input disbale bit (=1 disable input, =0 enable input) */
#define GPIO_PIEA_PIE37    BIT(31)      /*!< P37 input disbale bit (=1 disable input, =0 enable input) */

/* PMB */
#define GPIO_PMB_PM40      BIT(0)       /*!< P40 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM41      BIT(1)       /*!< P41 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM42      BIT(2)       /*!< P42 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM43      BIT(3)       /*!< P43 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM44      BIT(4)       /*!< P44 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM45      BIT(5)       /*!< P45 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM46      BIT(6)       /*!< P46 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM47      BIT(7)       /*!< P47 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM50      BIT(8)       /*!< P50 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM51      BIT(9)       /*!< P51 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM52      BIT(10)      /*!< P52 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM53      BIT(11)      /*!< P53 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM54      BIT(12)      /*!< P54 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM55      BIT(13)      /*!< P55 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM56      BIT(14)      /*!< P56 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM57      BIT(15)      /*!< P57 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM60      BIT(16)      /*!< P60 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM61      BIT(17)      /*!< P61 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM62      BIT(18)      /*!< P62 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM63      BIT(19)      /*!< P63 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM64      BIT(20)      /*!< P64 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM65      BIT(21)      /*!< P65 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM66      BIT(22)      /*!< P66 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM67      BIT(23)      /*!< P67 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM70      BIT(24)      /*!< P70 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM71      BIT(25)      /*!< P71 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM72      BIT(26)      /*!< P72 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM73      BIT(27)      /*!< P73 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM74      BIT(28)      /*!< P74 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM75      BIT(29)      /*!< P75 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM76      BIT(30)      /*!< P76 input/output cfg bit (=0 output mode, =1 input mode) */
#define GPIO_PMB_PM77      BIT(31)      /*!< P77 input/output cfg bit (=0 output mode, =1 input mode) */

/* PBPIN */
#define GPIO_PBPIN_P40    BIT(0)       /*!< port B P40 data */
#define GPIO_PBPIN_P41    BIT(1)       /*!< port B P41 data */
#define GPIO_PBPIN_P42    BIT(2)       /*!< port B P42 data */
#define GPIO_PBPIN_P43    BIT(3)       /*!< port B P43 data */
#define GPIO_PBPIN_P44    BIT(4)       /*!< port B P44 data */
#define GPIO_PBPIN_P45    BIT(5)       /*!< port B P45 data */
#define GPIO_PBPIN_P46    BIT(6)       /*!< port B P46 data */
#define GPIO_PBPIN_P47    BIT(7)       /*!< port B P47 data */
#define GPIO_PBPIN_P50    BIT(8)       /*!< port B P50 data */
#define GPIO_PBPIN_P51    BIT(9)       /*!< port B P51 data */
#define GPIO_PBPIN_P52    BIT(10)      /*!< port B P52 data */
#define GPIO_PBPIN_P53    BIT(11)      /*!< port B P53 data */
#define GPIO_PBPIN_P54    BIT(12)      /*!< port B P54 data */
#define GPIO_PBPIN_P55    BIT(13)      /*!< port B P55 data */
#define GPIO_PBPIN_P56    BIT(14)      /*!< port B P56 data */
#define GPIO_PBPIN_P57    BIT(15)      /*!< port B P57 data */
#define GPIO_PBPIN_P60    BIT(16)      /*!< port B P60 data */
#define GPIO_PBPIN_P61    BIT(17)      /*!< port B P61 data */
#define GPIO_PBPIN_P62    BIT(18)      /*!< port B P62 data */
#define GPIO_PBPIN_P63    BIT(19)      /*!< port B P63 data */
#define GPIO_PBPIN_P64    BIT(20)      /*!< port B P64 data */
#define GPIO_PBPIN_P65    BIT(21)      /*!< port B P65 data */
#define GPIO_PBPIN_P66    BIT(22)      /*!< port B P66 data */
#define GPIO_PBPIN_P67    BIT(23)      /*!< port B P67 data */
#define GPIO_PBPIN_P70    BIT(24)      /*!< port B P70 data */
#define GPIO_PBPIN_P71    BIT(25)      /*!< port B P71 data */
#define GPIO_PBPIN_P72    BIT(26)      /*!< port B P72 data */
#define GPIO_PBPIN_P73    BIT(27)      /*!< port B P73 data */
#define GPIO_PBPIN_P74    BIT(28)      /*!< port B P74 data */
#define GPIO_PBPIN_P75    BIT(29)      /*!< port B P75 data */
#define GPIO_PBPIN_P76    BIT(30)      /*!< port B P76 data */
#define GPIO_PBPIN_P77    BIT(31)      /*!< port B P77 data */

/* PCB */
#define GPIO_PCB_PC40     BIT(0)       /*!< P40 mode cfg bit */
#define GPIO_PCB_PC41     BIT(1)       /*!< P41 mode cfg bit */
#define GPIO_PCB_PC42     BIT(2)       /*!< P42 mode cfg bit */
#define GPIO_PCB_PC43     BIT(3)       /*!< P43 mode cfg bit */
#define GPIO_PCB_PC44     BIT(4)       /*!< P44 mode cfg bit */
#define GPIO_PCB_PC45     BIT(5)       /*!< P45 mode cfg bit */
#define GPIO_PCB_PC46     BIT(6)       /*!< P46 mode cfg bit */
#define GPIO_PCB_PC47     BIT(7)       /*!< P47 mode cfg bit */
#define GPIO_PCB_PC50     BIT(8)       /*!< P50 mode cfg bit */
#define GPIO_PCB_PC51     BIT(9)       /*!< P51 mode cfg bit */
#define GPIO_PCB_PC52     BIT(10)      /*!< P52 mode cfg bit */
#define GPIO_PCB_PC53     BIT(11)      /*!< P53 mode cfg bit */
#define GPIO_PCB_PC54     BIT(12)      /*!< P54 mode cfg bit */
#define GPIO_PCB_PC55     BIT(13)      /*!< P55 mode cfg bit */
#define GPIO_PCB_PC56     BIT(14)      /*!< P56 mode cfg bit */
#define GPIO_PCB_PC57     BIT(15)      /*!< P57 mode cfg bit */
#define GPIO_PCB_PC60     BIT(16)      /*!< P60 mode cfg bit */
#define GPIO_PCB_PC61     BIT(17)      /*!< P61 mode cfg bit */
#define GPIO_PCB_PC62     BIT(18)      /*!< P62 mode cfg bit */
#define GPIO_PCB_PC63     BIT(19)      /*!< P63 mode cfg bit */
#define GPIO_PCB_PC64     BIT(20)      /*!< P64 mode cfg bit */
#define GPIO_PCB_PC65     BIT(21)      /*!< P65 mode cfg bit */
#define GPIO_PCB_PC66     BIT(22)      /*!< P66 mode cfg bit */
#define GPIO_PCB_PC67     BIT(23)      /*!< P67 mode cfg bit */
#define GPIO_PCB_PC70     BIT(24)      /*!< P70 mode cfg bit */
#define GPIO_PCB_PC71     BIT(25)      /*!< P71 mode cfg bit */
#define GPIO_PCB_PC72     BIT(26)      /*!< P72 mode cfg bit */
#define GPIO_PCB_PC73     BIT(27)      /*!< P73 mode cfg bit */
#define GPIO_PCB_PC74     BIT(28)      /*!< P74 mode cfg bit */
#define GPIO_PCB_PC75     BIT(29)      /*!< P75 mode cfg bit */
#define GPIO_PCB_PC76     BIT(30)      /*!< P76 mode cfg bit */
#define GPIO_PCB_PC77     BIT(31)      /*!< P77 mode cfg bit */

/* PCB2 */
#define GPIO_PCB2_PC40_2   BITS(0,1)     /*!< P40 second mode cfg bits */
#define GPIO_PCB2_PC41_2   BITS(2,3)     /*!< P41 second mode cfg bits */
#define GPIO_PCB2_PC42_2   BITS(4,5)     /*!< P42 second mode cfg bits */
#define GPIO_PCB2_PC43_2   BITS(6,7)     /*!< P43 second mode cfg bits */
#define GPIO_PCB2_PC44_2   BITS(8,9)     /*!< P44 second mode cfg bits */
#define GPIO_PCB2_PC45_2   BITS(10,11)   /*!< P45 second mode cfg bits */
#define GPIO_PCB2_PC46_2   BITS(12,13)   /*!< P46 second mode cfg bits */
#define GPIO_PCB2_PC47_2   BITS(14,15)   /*!< P47 second mode cfg bits */
#define GPIO_PCB2_PC50_2   BITS(16,17)   /*!< P50 second mode cfg bits */
#define GPIO_PCB2_PC51_2   BITS(18,19)   /*!< P51 second mode cfg bits */
#define GPIO_PCB2_PC52_2   BITS(20,21)   /*!< P52 second mode cfg bits */
#define GPIO_PCB2_PC53_2   BITS(22,23)   /*!< P53 second mode cfg bits */
#define GPIO_PCB2_PC54_2   BITS(24,25)   /*!< P54 second mode cfg bits */
#define GPIO_PCB2_PC55_2   BITS(26,27)   /*!< P55 second mode cfg bits */
#define GPIO_PCB2_PC56_2   BITS(28,29)   /*!< P56 second mode cfg bits */
#define GPIO_PCB2_PC57_2   BITS(30,31)   /*!< P57 second mode cfg bits */

/* PUB */
#define GPIO_PUB_PU40      BIT(0)       /*!< P40 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU41      BIT(1)       /*!< P41 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU42      BIT(2)       /*!< P42 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU43      BIT(3)       /*!< P43 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU44      BIT(4)       /*!< P44 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU45      BIT(5)       /*!< P45 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU46      BIT(6)       /*!< P46 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU47      BIT(7)       /*!< P47 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU50      BIT(8)       /*!< P50 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU51      BIT(9)       /*!< P51 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU52      BIT(10)      /*!< P52 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU53      BIT(11)      /*!< P53 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU54      BIT(12)      /*!< P54 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU55      BIT(13)      /*!< P55 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU56      BIT(14)      /*!< P56 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU57      BIT(15)      /*!< P57 pull-up enable bit (=1 enable pull-up, =0 do not enable pull up) */
#define GPIO_PUB_PU60      BIT(16)      /*!< P60 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU61      BIT(17)      /*!< P61 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU62      BIT(18)      /*!< P62 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU63      BIT(19)      /*!< P63 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU64      BIT(20)      /*!< P64 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU65      BIT(21)      /*!< P65 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU66      BIT(22)      /*!< P66 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU67      BIT(23)      /*!< P67 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU70      BIT(24)      /*!< P70 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU71      BIT(25)      /*!< P71 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU72      BIT(26)      /*!< P72 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU73      BIT(27)      /*!< P73 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU74      BIT(28)      /*!< P74 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU75      BIT(29)      /*!< P75 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU76      BIT(30)      /*!< P76 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */
#define GPIO_PUB_PU77      BIT(31)      /*!< P77 pull-down enable bit (=1 enable pull-down, =0 do not enable pul down) */

/* PIMB */
#define GPIO_PIMB_PID40     BIT(0)        /*!< P40 output mode cfg bit */
#define GPIO_PIMB_PID41     BIT(1)        /*!< P41 output mode cfg bit */
#define GPIO_PIMB_PID42     BIT(2)        /*!< P42 output mode cfg bit */
#define GPIO_PIMB_PID43     BIT(3)        /*!< P43 output mode cfg bit */
#define GPIO_PIMB_PID44     BIT(4)        /*!< P44 output mode cfg bit */
#define GPIO_PIMB_PID45     BIT(5)        /*!< P45 output mode cfg bit */
#define GPIO_PIMB_PID46     BIT(6)        /*!< P46 output mode cfg bit */
#define GPIO_PIMB_PID47     BIT(7)        /*!< P47 output mode cfg bit */
#define GPIO_PIMB_PID50     BIT(8)        /*!< P50 output mode cfg bit */
#define GPIO_PIMB_PID51     BIT(9)        /*!< P51 output mode cfg bit */
#define GPIO_PIMB_PID52     BIT(10)       /*!< P52 output mode cfg bit */
#define GPIO_PIMB_PID53     BIT(11)       /*!< P53 output mode cfg bit */
#define GPIO_PIMB_PID54     BIT(12)       /*!< P54 output mode cfg bit */
#define GPIO_PIMB_PID55     BIT(13)       /*!< P55 output mode cfg bit */
#define GPIO_PIMB_PID56     BIT(14)       /*!< P56 output mode cfg bit */
#define GPIO_PIMB_PID57     BIT(15)       /*!< P57 output mode cfg bit */
#define GPIO_PIMB_PIL40     BIT(16)       /*!< P40 input mode cfg bit */
#define GPIO_PIMB_PIL41     BIT(17)       /*!< P41 input mode cfg bit */
#define GPIO_PIMB_PIL42     BIT(18)       /*!< P42 input mode cfg bit */
#define GPIO_PIMB_PIL43     BIT(19)       /*!< P43 input mode cfg bit */
#define GPIO_PIMB_PIL44     BIT(20)       /*!< P44 input mode cfg bit */
#define GPIO_PIMB_PIL45     BIT(21)       /*!< P45 input mode cfg bit */
#define GPIO_PIMB_PIL46     BIT(22)       /*!< P46 input mode cfg bit */
#define GPIO_PIMB_PIL47     BIT(23)       /*!< P47 input mode cfg bit */
#define GPIO_PIMB_PIL50     BIT(24)       /*!< P50 input mode cfg bit */
#define GPIO_PIMB_PIL51     BIT(25)       /*!< P51 input mode cfg bit */
#define GPIO_PIMB_PIL52     BIT(26)       /*!< P52 input mode cfg bit */
#define GPIO_PIMB_PIL53     BIT(27)       /*!< P53 input mode cfg bit */
#define GPIO_PIMB_PIL54     BIT(28)       /*!< P54 input mode cfg bit */
#define GPIO_PIMB_PIL55     BIT(29)       /*!< P55 input mode cfg bit */
#define GPIO_PIMB_PIL56     BIT(30)       /*!< P56 input mode cfg bit */
#define GPIO_PIMB_PIL57     BIT(31)       /*!< P57 input mode cfg bit */

/* PIEB */
#define GPIO_PIEB_PIE40     BIT(0)      /*!< P40 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE41     BIT(1)      /*!< P41 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE42     BIT(2)      /*!< P42 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE43     BIT(3)      /*!< P43 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE44     BIT(4)      /*!< P44 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE45     BIT(5)      /*!< P45 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE46     BIT(6)      /*!< P46 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE47     BIT(7)      /*!< P47 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE50     BIT(8)      /*!< P50 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE51     BIT(9)      /*!< P51 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE52     BIT(10)     /*!< P52 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE53     BIT(11)     /*!< P53 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE54     BIT(12)     /*!< P54 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE55     BIT(13)     /*!< P55 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE56     BIT(14)     /*!< P56 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE57     BIT(15)     /*!< P57 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE60     BIT(16)     /*!< P60 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE61     BIT(17)     /*!< P61 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE62     BIT(18)     /*!< P62 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE63     BIT(19)     /*!< P63 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE64     BIT(20)     /*!< P64 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE65     BIT(21)     /*!< P65 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE66     BIT(22)     /*!< P66 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE67     BIT(23)     /*!< P67 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE70     BIT(24)     /*!< P70 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE71     BIT(25)     /*!< P71 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE72     BIT(26)     /*!< P72 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE73     BIT(27)     /*!< P73 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE74     BIT(28)     /*!< P74 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE75     BIT(29)     /*!< P75 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE76     BIT(30)     /*!< P76 input disable bit (=1 disable input, =0 enable input) */
#define GPIO_PIEB_PIE77     BIT(31)     /*!< P77 input disable bit (=1 disable input, =0 enable input) */

/* PMC */
#define GPIO_PMC_PM80      BIT(0)       /*!< P80  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM81      BIT(1)       /*!< P81  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM82      BIT(2)       /*!< P82  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM83      BIT(3)       /*!< P83  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM84      BIT(4)       /*!< P84  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM85      BIT(5)       /*!< P85  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM86      BIT(6)       /*!< P86  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM87      BIT(7)       /*!< P87  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM90      BIT(8)       /*!< P90  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM91      BIT(9)       /*!< P91  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM92      BIT(10)      /*!< P92  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM93      BIT(11)      /*!< P93  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM94      BIT(12)      /*!< P94  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM95      BIT(13)      /*!< P95  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM96      BIT(14)      /*!< P96  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM97      BIT(15)      /*!< P97  input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM100     BIT(16)      /*!< P100 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM101     BIT(17)      /*!< P101 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM102     BIT(18)      /*!< P102 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM103     BIT(19)      /*!< P103 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM104     BIT(20)      /*!< P104 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM105     BIT(21)      /*!< P105 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM106     BIT(22)      /*!< P106 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM107     BIT(23)      /*!< P107 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM110     BIT(24)      /*!< P110 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM111     BIT(25)      /*!< P111 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM112     BIT(26)      /*!< P112 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM113     BIT(27)      /*!< P113 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM114     BIT(28)      /*!< P114 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM115     BIT(29)      /*!< P115 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM116     BIT(30)      /*!< P116 input/output cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMC_PM117     BIT(31)      /*!< P117 input/output cfg bit (=0 output mode, =1 input mode)  */

/* PCPIN PC */
#define GPIO_PCPIN_P80     BIT(0)       /*!< port C P80  data */
#define GPIO_PCPIN_P81     BIT(1)       /*!< port C P81  data */
#define GPIO_PCPIN_P82     BIT(2)       /*!< port C P82  data */
#define GPIO_PCPIN_P83     BIT(3)       /*!< port C P83  data */
#define GPIO_PCPIN_P84     BIT(4)       /*!< port C P84  data */
#define GPIO_PCPIN_P85     BIT(5)       /*!< port C P85  data */
#define GPIO_PCPIN_P86     BIT(6)       /*!< port C P86  data */
#define GPIO_PCPIN_P87     BIT(7)       /*!< port C P87  data */
#define GPIO_PCPIN_P90     BIT(8)       /*!< port C P90  data */
#define GPIO_PCPIN_P91     BIT(9)       /*!< port C P91  data */
#define GPIO_PCPIN_P92     BIT(10)      /*!< port C P92  data */
#define GPIO_PCPIN_P93     BIT(11)      /*!< port C P93  data */
#define GPIO_PCPIN_P94     BIT(12)      /*!< port C P94  data */
#define GPIO_PCPIN_P95     BIT(13)      /*!< port C P95  data */
#define GPIO_PCPIN_P96     BIT(14)      /*!< port C P96  data */
#define GPIO_PCPIN_P97     BIT(15)      /*!< port C P97  data */
#define GPIO_PCPIN_P100    BIT(16)      /*!< port C P100 data */
#define GPIO_PCPIN_P101    BIT(17)      /*!< port C P101 data */
#define GPIO_PCPIN_P102    BIT(18)      /*!< port C P102 data */
#define GPIO_PCPIN_P103    BIT(19)      /*!< port C P103 data */
#define GPIO_PCPIN_P104    BIT(20)      /*!< port C P104 data */
#define GPIO_PCPIN_P105    BIT(21)      /*!< port C P105 data */
#define GPIO_PCPIN_P106    BIT(22)      /*!< port C P106 data */
#define GPIO_PCPIN_P107    BIT(23)      /*!< port C P107 data */
#define GPIO_PCPIN_P110    BIT(24)      /*!< port C P110 data */
#define GPIO_PCPIN_P111    BIT(25)      /*!< port C P111 data */
#define GPIO_PCPIN_P112    BIT(26)      /*!< port C P112 data */
#define GPIO_PCPIN_P113    BIT(27)      /*!< port C P113 data */
#define GPIO_PCPIN_P114    BIT(28)      /*!< port C P114 data */
#define GPIO_PCPIN_P115    BIT(29)      /*!< port C P115 data */
#define GPIO_PCPIN_P116    BIT(30)      /*!< port C P116 data */
#define GPIO_PCPIN_P117    BIT(31)      /*!< port C P117 data */

/* PCC */
#define GPIO_PCC_PC80       BIT(0)      /*!< PC80  mode cfg bit */
#define GPIO_PCC_PC81       BIT(1)      /*!< PC81  mode cfg bit */
#define GPIO_PCC_PC82       BIT(2)      /*!< PC82  mode cfg bit */
#define GPIO_PCC_PC83       BIT(3)      /*!< PC83  mode cfg bit */
#define GPIO_PCC_PC84       BIT(4)      /*!< PC84  mode cfg bit */
#define GPIO_PCC_PC85       BIT(5)      /*!< PC85  mode cfg bit */
#define GPIO_PCC_PC86       BIT(6)      /*!< PC86  mode cfg bit */
#define GPIO_PCC_PC87       BIT(7)      /*!< PC87  mode cfg bit */
#define GPIO_PCC_PC90       BIT(8)      /*!< PC90  mode cfg bit */
#define GPIO_PCC_PC91       BIT(9)      /*!< PC91  mode cfg bit */
#define GPIO_PCC_PC92       BIT(10)     /*!< PC92  mode cfg bit */
#define GPIO_PCC_PC93       BIT(11)     /*!< PC93  mode cfg bit */
#define GPIO_PCC_PC94       BIT(12)     /*!< PC94  mode cfg bit */
#define GPIO_PCC_PC95       BIT(13)     /*!< PC95  mode cfg bit */
#define GPIO_PCC_PC96       BIT(14)     /*!< PC96  mode cfg bit */
#define GPIO_PCC_PC97       BIT(15)     /*!< PC97  mode cfg bit */
#define GPIO_PCC_PC100      BIT(16)     /*!< PC100 mode cfg bit */
#define GPIO_PCC_PC101      BIT(17)     /*!< PC101 mode cfg bit */
#define GPIO_PCC_PC102      BIT(18)     /*!< PC102 mode cfg bit */
#define GPIO_PCC_PC103      BIT(19)     /*!< PC103 mode cfg bit */
#define GPIO_PCC_PC104      BIT(20)     /*!< PC104 mode cfg bit */
#define GPIO_PCC_PC105      BIT(21)     /*!< PC105 mode cfg bit */
#define GPIO_PCC_PC106      BIT(22)     /*!< PC106 mode cfg bit */
#define GPIO_PCC_PC107      BIT(23)     /*!< PC107 mode cfg bit */
#define GPIO_PCC_PC110      BIT(24)     /*!< PC110 mode cfg bit */
#define GPIO_PCC_PC111      BIT(25)     /*!< PC111 mode cfg bit */
#define GPIO_PCC_PC112      BIT(26)     /*!< PC112 mode cfg bit */
#define GPIO_PCC_PC113      BIT(27)     /*!< PC113 mode cfg bit */
#define GPIO_PCC_SPI_MUX    BIT(28)     /*!< SPI0 pin defination bit */

/* PUC */
#define GPIO_PUC_PU80       BIT(0)      /*!< P80  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU81       BIT(1)      /*!< P81  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU82       BIT(2)      /*!< P82  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU83       BIT(3)      /*!< P83  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU84       BIT(4)      /*!< P84  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU85       BIT(5)      /*!< P85  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU86       BIT(6)      /*!< P86  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU87       BIT(7)      /*!< P87  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU90       BIT(8)      /*!< P90  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU91       BIT(9)      /*!< P91  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU92       BIT(10)     /*!< P92  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU93       BIT(11)     /*!< P93  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU94       BIT(12)     /*!< P94  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU95       BIT(13)     /*!< P95  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU96       BIT(14)     /*!< P96  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU97       BIT(15)     /*!< P97  pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU100      BIT(16)     /*!< P100 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU101      BIT(17)     /*!< P101 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU102      BIT(18)     /*!< P102 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU103      BIT(19)     /*!< P103 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down)  */
#define GPIO_PUC_PU104      BIT(20)     /*!< P104 pull up enable bit(=1 enable pull-up ,=0 do not enable pull-up)  */
#define GPIO_PUC_PU105      BIT(21)     /*!< P105 pull up enable bit(=1 enable pull-up ,=0 do not enable pull-up)  */
#define GPIO_PUC_PU106      BIT(22)     /*!< P106 pull up enable bit(=1 enable pull-up ,=0 do not enable pull-up)  */
#define GPIO_PUC_PU107      BIT(23)     /*!< P107 pull up enable bit(=1 enable pull-up ,=0 do not enable pull-up)  */
#define GPIO_PUC_PU110      BIT(24)     /*!< P110 pull up enable bit(=1 enable pull-up ,=0 do not enable pull-up)  */
#define GPIO_PUC_PU111      BIT(25)     /*!< P111 pull up enable bit(=1 enable pull-up ,=0 do not enable pull-up)  */
#define GPIO_PUC_PU112      BIT(26)     /*!< P112 pull up enable bit(=1 enable pull-up ,=0 do not enable pull-up)  */
#define GPIO_PUC_PU113      BIT(27)     /*!< P113 pull up enable bit(=1 enable pull-up ,=0 do not enable pull-up)  */
#define GPIO_PUC_PU114      BIT(28)     /*!< P114 pull up enable bit(=1 enable pull-up ,=0 do not enable pull-up)  */
#define GPIO_PUC_PU115      BIT(29)     /*!< P115 pull up enable bit(=1 enable pull-up ,=0 do not enable pull-up)  */
#define GPIO_PUC_PU116      BIT(30)     /*!< P116 pull up enable bit(=1 enable pull-up ,=0 do not enable pull-up)  */
#define GPIO_PUC_PU117      BIT(31)     /*!< P117 pull up enable bit(=1 enable pull-up ,=0 do not enable pull-up)  */

/* PIEC */
#define GPIO_PIEC_PIE80     BIT(0)      /*!< P80  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE81     BIT(1)      /*!< P81  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE82     BIT(2)      /*!< P82  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE83     BIT(3)      /*!< P83  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE84     BIT(4)      /*!< P84  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE85     BIT(5)      /*!< P85  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE86     BIT(6)      /*!< P86  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE87     BIT(7)      /*!< P87  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE90     BIT(8)      /*!< P90  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE91     BIT(9)      /*!< P91  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE92     BIT(10)     /*!< P92  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE93     BIT(11)     /*!< P93  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE94     BIT(12)     /*!< P94  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE95     BIT(13)     /*!< P95  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE96     BIT(14)     /*!< P96  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE97     BIT(15)     /*!< P97  input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE100    BIT(16)     /*!< P100 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE101    BIT(17)     /*!< P101 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE102    BIT(18)     /*!< P102 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE103    BIT(19)     /*!< P103 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE104    BIT(20)     /*!< P104 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE105    BIT(21)     /*!< P105 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE106    BIT(22)     /*!< P106 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE107    BIT(23)     /*!< P107 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE110    BIT(24)     /*!< P110 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE111    BIT(25)     /*!< P111 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE112    BIT(26)     /*!< P112 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE113    BIT(27)     /*!< P113 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE114    BIT(28)     /*!< P114 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE115    BIT(29)     /*!< P115 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE116    BIT(30)     /*!< P116 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIEC_PIE117    BIT(31)     /*!< P117 input disable bit(=1 disable input, =0 enable input) */

/* PIMC */
#define GPIO_PIMC_PID110    BIT(0)      /*!< P110 output mode cfg bit */
#define GPIO_PIMC_PID111    BIT(1)      /*!< P111 output mode cfg bit */
#define GPIO_PIMC_PID112    BIT(2)      /*!< P112 output mode cfg bit */
#define GPIO_PIMC_PID113    BIT(3)      /*!< P113 output mode cfg bit */
#define GPIO_PIMC_PIL110    BIT(4)      /*!< P110 input mode cfg bit */
#define GPIO_PIMC_PIL111    BIT(5)      /*!< P111 input mode cfg bit */
#define GPIO_PIMC_PIL112    BIT(6)      /*!< P112 input mode cfg bit */
#define GPIO_PIMC_PIL113    BIT(7)      /*!< P113 input mode cfg bit */
#define GPIO_PIMC_PID114    BIT(8)      /*!< P114 output mode cfg bit */
#define GPIO_PIMC_PID115    BIT(9)      /*!< P115 output mode cfg bit */
#define GPIO_PIMC_PID116    BIT(10)     /*!< P116 output mode cfg bit */
#define GPIO_PIMC_PID117    BIT(11)     /*!< P117 output mode cfg bit */
#define GPIO_PIMC_PIL114    BIT(12)     /*!< P114 input mode cfg bit */
#define GPIO_PIMC_PIL115    BIT(13)     /*!< P115 input mode cfg bit */
#define GPIO_PIMC_PIL116    BIT(14)     /*!< P116 input mode cfg bit */
#define GPIO_PIMC_PIL117    BIT(15)     /*!< P117 input mode cfg bit */

/* PMD */
#define GPIO_PMD_PMD120     BIT(0)      /*!< P120 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD121     BIT(1)      /*!< P121 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD122     BIT(2)      /*!< P122 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD123     BIT(3)      /*!< P123 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD124     BIT(4)      /*!< P124 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD125     BIT(5)      /*!< P125 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD126     BIT(6)      /*!< P126 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD127     BIT(7)      /*!< P127 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD130     BIT(8)      /*!< P130 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD131     BIT(9)      /*!< P131 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD132     BIT(10)     /*!< P132 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD133     BIT(11)     /*!< P133 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD134     BIT(12)     /*!< P134 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD135     BIT(13)     /*!< P135 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD136     BIT(14)     /*!< P136 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD137     BIT(15)     /*!< P137 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD140     BIT(16)     /*!< P140 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD141     BIT(17)     /*!< P141 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD142     BIT(18)     /*!< P142 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD143     BIT(19)     /*!< P143 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD144     BIT(20)     /*!< P144 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD145     BIT(21)     /*!< P145 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD146     BIT(22)     /*!< P146 input/output mode cfg bit (=0 output mode, =1 input mode)  */
#define GPIO_PMD_PMD147     BIT(23)     /*!< P147 input/output mode cfg bit (=0 output mode, =1 input mode)  */

/* PDPIN */
#define GPIO_PDPIN_P120     BIT(0)            /*!< port D P120 data */
#define GPIO_PDPIN_P121     BIT(1)            /*!< port D P121 data */
#define GPIO_PDPIN_P122     BIT(2)            /*!< port D P122 data */
#define GPIO_PDPIN_P123     BIT(3)            /*!< port D P123 data */
#define GPIO_PDPIN_P124     BIT(4)            /*!< port D P124 data */
#define GPIO_PDPIN_P125     BIT(5)            /*!< port D P125 data */
#define GPIO_PDPIN_P126     BIT(6)            /*!< port D P126 data */
#define GPIO_PDPIN_P127     BIT(7)            /*!< port D P127 data */
#define GPIO_PDPIN_P130     BIT(8)            /*!< port D P130 data */
#define GPIO_PDPIN_P131     BIT(9)            /*!< port D P131 data */
#define GPIO_PDPIN_P132     BIT(10)           /*!< port D P132 data */
#define GPIO_PDPIN_P133     BIT(11)           /*!< port D P133 data */
#define GPIO_PDPIN_P134     BIT(12)           /*!< port D P134 data */
#define GPIO_PDPIN_P135     BIT(13)           /*!< port D P135 data */
#define GPIO_PDPIN_P136     BIT(14)           /*!< port D P136 data */
#define GPIO_PDPIN_P137     BIT(15)           /*!< port D P137 data */
#define GPIO_PDPIN_P140     BIT(16)           /*!< port D P140 data */
#define GPIO_PDPIN_P141     BIT(17)           /*!< port D P141 data */
#define GPIO_PDPIN_P142     BIT(18)           /*!< port D P142 data */
#define GPIO_PDPIN_P143     BIT(19)           /*!< port D P143 data */
#define GPIO_PDPIN_P144     BIT(20)           /*!< port D P144 data */
#define GPIO_PDPIN_P145     BIT(21)           /*!< port D P145 data */
#define GPIO_PDPIN_P146     BIT(22)           /*!< port D P146 data */
#define GPIO_PDPIN_P147     BIT(23)           /*!< port D P147 data */
/* PCD*/
#define GPIO_PCD_PC120      BIT(0)            /*!< P120 mode cfg bit */
#define GPIO_PCD_PC121      BIT(1)            /*!< P121 mode cfg bit */
#define GPIO_PCD_PC122      BIT(2)            /*!< P122 mode cfg bit */
#define GPIO_PCD_PC123      BIT(3)            /*!< P123 mode cfg bit */
#define GPIO_PCD_PC124      BIT(4)            /*!< P124 mode cfg bit */
#define GPIO_PCD_PC125      BIT(5)            /*!< P125 mode cfg bit */
#define GPIO_PCD_PC126      BIT(6)            /*!< P126 mode cfg bit */
#define GPIO_PCD_PC127      BIT(7)            /*!< P127 mode cfg bit */
#define GPIO_PCD_PC130      BIT(8)            /*!< P130 mode cfg bit */
#define GPIO_PCD_PC131      BIT(9)            /*!< P131 mode cfg bit */
#define GPIO_PCD_PC132      BIT(10)           /*!< P132 mode cfg bit */
#define GPIO_PCD_PC133      BIT(11)           /*!< P133 mode cfg bit (=0 select as IO, =1 reserved)*/
#define GPIO_PCD_PC134      BIT(12)           /*!< P134 mode cfg bit */
#define GPIO_PCD_PC135      BIT(13)           /*!< P135 mode cfg bit */
#define GPIO_PCD_PC136      BIT(14)           /*!< P136 mode cfg bit */
#define GPIO_PCD_PC137      BIT(15)           /*!< P137 mode cfg bit (=0 select as IO, =1 reserved)*/
#define GPIO_PCD_PC140      BITS(16,17)       /*!< P140 mode cfg bits (=0 select as IO, =other num reserved)*/
#define GPIO_PCD_PC141      BITS(18,19)       /*!< P141 mode cfg bits (=0 select as IO, =other num reserved)*/
#define GPIO_PCD_PC142      BITS(20,21)       /*!< P142 mode cfg bits (=0 select as IO, =other num reserved)*/
/* PUD */
#define GPIO_PUD_PU120     BIT(0)     /*!< P120 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU121     BIT(1)     /*!< P121 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU122     BIT(2)     /*!< P122 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU123     BIT(3)     /*!< P123 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU124     BIT(4)     /*!< P124 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU125     BIT(5)     /*!< P125 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU126     BIT(6)     /*!< P126 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU127     BIT(7)     /*!< P127 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU130     BIT(8)     /*!< P130 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU131     BIT(9)     /*!< P131 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU132     BIT(10)    /*!< P132 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU133     BIT(11)    /*!< P133 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU134     BIT(12)    /*!< P134 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU135     BIT(13)    /*!< P135 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU136     BIT(14)    /*!< P136 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU137     BIT(15)    /*!< P137 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU140     BIT(16)    /*!< P140 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU141     BIT(17)    /*!< P141 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU142     BIT(18)    /*!< P142 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU143     BIT(19)    /*!< P143 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU144     BIT(20)    /*!< P144 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU145     BIT(21)    /*!< P145 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU146     BIT(22)    /*!< P146 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */
#define GPIO_PUD_PU147     BIT(23)    /*!< P147 pull down enable bit(=1 enable pull-down ,=0 do not enable pull-down) */

/* PIED */
#define GPIO_PIED_PIE120     BIT(0)      /*!< P120 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE121     BIT(1)      /*!< P121 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE122     BIT(2)      /*!< P122 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE123     BIT(3)      /*!< P123 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE124     BIT(4)      /*!< P124 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE125     BIT(5)      /*!< P125 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE126     BIT(6)      /*!< P126 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE127     BIT(7)      /*!< P127 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE130     BIT(8)      /*!< P130 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE131     BIT(9)      /*!< P131 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE132     BIT(10)     /*!< P132 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE133     BIT(11)     /*!< P133 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE134     BIT(12)     /*!< P134 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE135     BIT(13)     /*!< P135 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE136     BIT(14)     /*!< P136 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE137     BIT(15)     /*!< P137 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE140     BIT(16)     /*!< P140 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE141     BIT(17)     /*!< P141 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE142     BIT(18)     /*!< P142 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE143     BIT(19)     /*!< P143 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE144     BIT(20)     /*!< P144 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE145     BIT(21)     /*!< P145 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE146     BIT(22)     /*!< P146 input disable bit(=1 disable input, =0 enable input) */
#define GPIO_PIED_PIE147     BIT(23)     /*!< P147 input disable bit(=1 disable input, =0 enable input) */

/* PIMD */
#define GPIO_PIMD_PID140    BIT(0)      /*!< P140 output mode cfg bit */
#define GPIO_PIMD_PID141    BIT(1)      /*!< P141 output mode cfg bit */
#define GPIO_PIMD_PID142    BIT(2)      /*!< P142 output mode cfg bit */
#define GPIO_PIMD_PID143    BIT(3)      /*!< P143 output mode cfg bit */
#define GPIO_PIMD_PIL140    BIT(4)      /*!< P140 input mode cfg bit */
#define GPIO_PIMD_PIL141    BIT(5)      /*!< P141 input mode cfg bit */
#define GPIO_PIMD_PIL142    BIT(6)      /*!< P142 input mode cfg bit */
#define GPIO_PIMD_PIL143    BIT(7)      /*!< P143 input mode cfg bit */
#define GPIO_PIMD_PID144    BIT(8)      /*!< P144 output mode cfg bit */
#define GPIO_PIMD_PID145    BIT(9)      /*!< P145 output mode cfg bit */
#define GPIO_PIMD_PID146    BIT(10)     /*!< P146 output mode cfg bit */
#define GPIO_PIMD_PID147    BIT(11)     /*!< P147 output mode cfg bit */
#define GPIO_PIMD_PIL144    BIT(12)     /*!< P144 input mode cfg bit */
#define GPIO_PIMD_PIL145    BIT(13)     /*!< P145 input mode cfg bit */
#define GPIO_PIMD_PIL146    BIT(14)     /*!< P146 input mode cfg bit */
#define GPIO_PIMD_PIL147    BIT(15)     /*!< P147 input mode cfg bit */

/* PCE */
#define GPIO_PCE_SEG0_COM4  BIT(0)     /*!< COM4 mode selection bit (=1 select as SEG, =0 select as COM)*/
#define GPIO_PCE_SEG1_COM5  BIT(1)     /*!< COM5 mode selection bit (=1 select as SEG, =0 select as COM)*/
#define GPIO_PCE_SEG2_COM6  BIT(2)     /*!< COM6 mode selection bit (=1 select as SEG, =0 select as COM)*/
#define GPIO_PCE_SEG3_COM7  BIT(3)     /*!< COM7 mode selection bit (=1 select as SEG, =0 select as COM)*/

/* PASET */
#define GPIO_PASET_P00      BIT(0)     /*!< PA P00 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P01      BIT(1)     /*!< PA P01 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P02      BIT(2)     /*!< PA P02 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P03      BIT(3)     /*!< PA P03 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P04      BIT(4)     /*!< PA P04 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P10      BIT(8)     /*!< PA P10 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P11      BIT(9)     /*!< PA P11 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P12      BIT(10)    /*!< PA P12 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P13      BIT(11)    /*!< PA P13 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P14      BIT(12)    /*!< PA P14 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P15      BIT(13)    /*!< PA P15 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P16      BIT(14)    /*!< PA P16 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P17      BIT(15)    /*!< PA P17 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P20      BIT(16)    /*!< PA P20 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P21      BIT(17)    /*!< PA P21 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P22      BIT(18)    /*!< PA P22 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P23      BIT(19)    /*!< PA P23 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P24      BIT(20)    /*!< PA P24 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P25      BIT(21)    /*!< PA P25 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P26      BIT(22)    /*!< PA P26 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P27      BIT(23)    /*!< PA P27 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P30      BIT(24)    /*!< PA P30 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P31      BIT(25)    /*!< PA P31 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P32      BIT(26)    /*!< PA P32 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P33      BIT(27)    /*!< PA P33 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P34      BIT(28)    /*!< PA P34 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PASET_P35      BIT(29)    /*!< PA P35 state set bit(=1 set as high level, =0 no effection) */

/* PACLR */
#define GPIO_PACLR_P00      BIT(0)     /*!< PA P00 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P01      BIT(1)     /*!< PA P01 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P02      BIT(2)     /*!< PA P02 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P03      BIT(3)     /*!< PA P03 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P04      BIT(4)     /*!< PA P04 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P10      BIT(8)     /*!< PA P10 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P11      BIT(9)     /*!< PA P11 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P12      BIT(10)    /*!< PA P12 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P13      BIT(11)    /*!< PA P13 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P14      BIT(12)    /*!< PA P14 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P15      BIT(13)    /*!< PA P15 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P16      BIT(14)    /*!< PA P16 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P17      BIT(15)    /*!< PA P17 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P20      BIT(16)    /*!< PA P20 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P21      BIT(17)    /*!< PA P21 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P22      BIT(18)    /*!< PA P22 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P23      BIT(19)    /*!< PA P23 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P24      BIT(20)    /*!< PA P24 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P25      BIT(21)    /*!< PA P25 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P26      BIT(22)    /*!< PA P26 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P27      BIT(23)    /*!< PA P27 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P30      BIT(24)    /*!< PA P30 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P31      BIT(25)    /*!< PA P31 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P32      BIT(26)    /*!< PA P32 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P33      BIT(27)    /*!< PA P33 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P34      BIT(28)    /*!< PA P34 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P35      BIT(29)    /*!< PA P35 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P36      BIT(30)    /*!< PA P36 state clean bit (=1 clean pin state low level output, =0 no effection) */
#define GPIO_PACLR_P37      BIT(31)    /*!< PA P37 state clean bit (=1 clean pin state low level output, =0 no effection) */

/* PBSET */
#define GPIO_PBSET_P40      BIT(0)      /*!< PB P40 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P41      BIT(1)      /*!< PB P41 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P42      BIT(2)      /*!< PB P42 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P43      BIT(3)      /*!< PB P43 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P44      BIT(4)      /*!< PB P44 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P45      BIT(5)      /*!< PB P45 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P46      BIT(6)      /*!< PB P46 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P47      BIT(7)      /*!< PB P47 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P50      BIT(8)      /*!< PB P50 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P51      BIT(9)      /*!< PB P51 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P52      BIT(10)     /*!< PB P52 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P53      BIT(11)     /*!< PB P53 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P54      BIT(12)     /*!< PB P54 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P55      BIT(13)     /*!< PB P55 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P56      BIT(14)     /*!< PB P56 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P57      BIT(15)     /*!< PB P57 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P60      BIT(16)     /*!< PB P60 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P61      BIT(17)     /*!< PB P61 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P62      BIT(18)     /*!< PB P62 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P63      BIT(19)     /*!< PB P63 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P64      BIT(20)     /*!< PB P64 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P65      BIT(21)     /*!< PB P65 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P66      BIT(22)     /*!< PB P66 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P67      BIT(23)     /*!< PB P67 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P70      BIT(24)     /*!< PB P70 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P71      BIT(25)     /*!< PB P71 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P72      BIT(26)     /*!< PB P72 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P73      BIT(27)     /*!< PB P73 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P74      BIT(28)     /*!< PB P74 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P75      BIT(29)     /*!< PB P75 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P76      BIT(30)     /*!< PB P76 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PBSET_P77      BIT(31)     /*!< PB P77 state set bit(=1 set as high level, =0 no effection) */

/* PBCLR */
#define GPIO_PBCLR_P40      BIT(0)      /*!< PB P40 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P41      BIT(1)      /*!< PB P41 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P42      BIT(2)      /*!< PB P42 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P43      BIT(3)      /*!< PB P43 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P44      BIT(4)      /*!< PB P44 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P45      BIT(5)      /*!< PB P45 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P46      BIT(6)      /*!< PB P46 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P47      BIT(7)      /*!< PB P47 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P50      BIT(8)      /*!< PB P50 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P51      BIT(9)      /*!< PB P51 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P52      BIT(10)     /*!< PB P52 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P53      BIT(11)     /*!< PB P53 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P54      BIT(12)     /*!< PB P54 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P55      BIT(13)     /*!< PB P55 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P56      BIT(14)     /*!< PB P56 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P57      BIT(15)     /*!< PB P57 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P60      BIT(16)     /*!< PB P60 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P61      BIT(17)     /*!< PB P61 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P62      BIT(18)     /*!< PB P62 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P63      BIT(19)     /*!< PB P63 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P64      BIT(20)     /*!< PB P64 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P65      BIT(21)     /*!< PB P65 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P66      BIT(22)     /*!< PB P66 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P67      BIT(23)     /*!< PB P67 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P70      BIT(24)     /*!< PB P70 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P71      BIT(25)     /*!< PB P71 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P72      BIT(26)     /*!< PB P72 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P73      BIT(27)     /*!< PB P73 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P74      BIT(28)     /*!< PB P74 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P75      BIT(29)     /*!< PB P75 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P76      BIT(30)     /*!< PB P76 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PBCLR_P77      BIT(31)     /*!< PB P77 state clean bit (=1 clean pin state low level output, =0 no effection)  */

/* PCSET */
#define GPIO_PCSET_P80      BIT(0)      /*!< PC P80  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P81      BIT(1)      /*!< PC P81  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P82      BIT(2)      /*!< PC P82  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P83      BIT(3)      /*!< PC P83  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P84      BIT(4)      /*!< PC P84  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P85      BIT(5)      /*!< PC P85  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P86      BIT(6)      /*!< PC P86  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P87      BIT(7)      /*!< PC P87  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P90      BIT(8)      /*!< PC P90  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P91      BIT(9)      /*!< PC P91  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P92      BIT(10)     /*!< PC P92  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P93      BIT(11)     /*!< PC P93  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P94      BIT(12)     /*!< PC P94  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P95      BIT(13)     /*!< PC P95  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P96      BIT(14)     /*!< PC P96  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P97      BIT(15)     /*!< PC P97  state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P100     BIT(16)     /*!< PC P100 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P101     BIT(17)     /*!< PC P101 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P102     BIT(18)     /*!< PC P102 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P103     BIT(19)     /*!< PC P103 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P104     BIT(20)     /*!< PC P104 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P105     BIT(21)     /*!< PC P105 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P106     BIT(22)     /*!< PC P106 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P107     BIT(23)     /*!< PC P107 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P110     BIT(24)     /*!< PC P110 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P111     BIT(25)     /*!< PC P111 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P112     BIT(26)     /*!< PC P112 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P113     BIT(27)     /*!< PC P113 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P114     BIT(28)     /*!< PC P114 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P115     BIT(29)     /*!< PC P115 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P116     BIT(30)     /*!< PC P116 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PCSET_P117     BIT(31)     /*!< PC P117 state set bit(=1 set as high level, =0 no effection) */

/* PCCLR */
#define GPIO_PCCLR_P80      BIT(0)      /*!< PC P80  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P81      BIT(1)      /*!< PC P81  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P82      BIT(2)      /*!< PC P82  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P83      BIT(3)      /*!< PC P83  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P84      BIT(4)      /*!< PC P84  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P85      BIT(5)      /*!< PC P85  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P86      BIT(6)      /*!< PC P86  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P87      BIT(7)      /*!< PC P87  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P90      BIT(8)      /*!< PC P90  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P91      BIT(9)      /*!< PC P91  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P92      BIT(10)     /*!< PC P92  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P93      BIT(11)     /*!< PC P93  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P94      BIT(12)     /*!< PC P94  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P95      BIT(13)     /*!< PC P95  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P96      BIT(14)     /*!< PC P96  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P97      BIT(15)     /*!< PC P97  state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P100     BIT(16)     /*!< PC P100 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P101     BIT(17)     /*!< PC P101 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P102     BIT(18)     /*!< PC P102 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P103     BIT(19)     /*!< PC P103 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P104     BIT(20)     /*!< PC P104 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P105     BIT(21)     /*!< PC P105 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P106     BIT(22)     /*!< PC P106 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P107     BIT(23)     /*!< PC P107 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P110     BIT(24)     /*!< PC P110 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P111     BIT(25)     /*!< PC P111 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P112     BIT(26)     /*!< PC P112 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P113     BIT(27)     /*!< PC P113 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P114     BIT(28)     /*!< PC P114 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P115     BIT(29)     /*!< PC P115 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P116     BIT(30)     /*!< PC P116 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PCCLR_P117     BIT(31)     /*!< PC P117 state clean bit (=1 clean pin state low level output, =0 no effection)  */

/* PDSET */
#define GPIO_PDSET_P120     BIT(0)            /*!< PD P120 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P121     BIT(1)            /*!< PD P121 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P122     BIT(2)            /*!< PD P122 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P123     BIT(3)            /*!< PD P123 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P124     BIT(4)            /*!< PD P124 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P125     BIT(5)            /*!< PD P125 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P126     BIT(6)            /*!< PD P126 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P127     BIT(7)            /*!< PD P127 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P130     BIT(8)            /*!< PD P130 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P131     BIT(9)            /*!< PD P131 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P132     BIT(10)           /*!< PD P132 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P133     BIT(11)           /*!< PD P133 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P134     BIT(12)           /*!< PD P134 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P135     BIT(13)           /*!< PD P135 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P136     BIT(14)           /*!< PD P136 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P137     BIT(15)           /*!< PD P137 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P140     BIT(16)           /*!< PD P140 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P141     BIT(17)           /*!< PD P141 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P142     BIT(18)           /*!< PD P142 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P143     BIT(19)           /*!< PD P143 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P144     BIT(20)           /*!< PD P144 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P145     BIT(21)           /*!< PD P145 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P146     BIT(22)           /*!< PD P146 state set bit(=1 set as high level, =0 no effection) */
#define GPIO_PDSET_P147     BIT(23)           /*!< PD P147 state set bit(=1 set as high level, =0 no effection) */

/* PDCLR */
#define GPIO_PDCLR_P120     BIT(0)            /*!< PD P120 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P121     BIT(1)            /*!< PD P121 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P122     BIT(2)            /*!< PD P122 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P123     BIT(3)            /*!< PD P123 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P124     BIT(4)            /*!< PD P124 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P125     BIT(5)            /*!< PD P125 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P126     BIT(6)            /*!< PD P126 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P127     BIT(7)            /*!< PD P127 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P130     BIT(8)            /*!< PD P130 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P131     BIT(9)            /*!< PD P131 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P132     BIT(10)           /*!< PD P132 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P133     BIT(11)           /*!< PD P133 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P134     BIT(12)           /*!< PD P134 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P135     BIT(13)           /*!< PD P135 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P136     BIT(14)           /*!< PD P136 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P137     BIT(15)           /*!< PD P137 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P140     BIT(16)           /*!< PD P140 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P141     BIT(17)           /*!< PD P141 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P142     BIT(18)           /*!< PD P142 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P143     BIT(19)           /*!< PD P143 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P144     BIT(20)           /*!< PD P144 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P145     BIT(21)           /*!< PD P145 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P146     BIT(22)           /*!< PD P146 state clean bit (=1 clean pin state low level output, =0 no effection)  */
#define GPIO_PDCLR_P147     BIT(23)           /*!< PD P147 state clean bit (=1 clean pin state low level output, =0 no effection)  */

/* P34_CFG */
#define GPIO_P34_CFG_P34CNT BITS(0,19)         /*!< P34 (INT4) pulse input counter, clear after read */
#define GPIO_P34_CFG_P34CFG BITS(20,30)        /*!< P34 pulse input div cfg bit,div=P34CFG+1, range:0~2048 */
#define GPIO_P34_CFG_P34INT BITS(31,31)        /*!< after divider, P34 level invert cfg (=1 invert level, =0 do not invert level)  */

/* P50_CFG */
#define GPIO_P50_CFG_P50CNT BITS(0,19)         /*!< P50 (INT2/6) pulse input counter, clear after read */
#define GPIO_P50_CFG_P50CFG BITS(20,30)        /*!< P50 pulse input div cfg bit,div=P34CFG+1, range:0~2048 */
#define GPIO_P50_CFG_P50INT BITS(31,31)        /*!< after divider, P50 level invert cfg (=1 invert level, =0 do not invert level)  */

/* P51_CFG */
#define GPIO_P51_CFG_P51CNT BITS(0,19)         /*!< P51 (INT5/7) pulse input counter, clear after read */
#define GPIO_P51_CFG_P51CFG BITS(20,30)        /*!< P51 pulse input div cfg bit,div=P34CFG+1, range:0~2048 */
#define GPIO_P51_CFG_P51INT BITS(31,31)        /*!< after divider, P51 level invert cfg (=1 invert level, =0 do not invert level)  */

/* IOCNT_CTL */
#define GPIO_IOCNT_CTL_P34CNT_EN      BIT(0)    /*!< P34 IOCNT enable bit */
#define GPIO_IOCNT_CTL_P50CNT_EN      BIT(1)    /*!< P50 IOCNT enable bit  */
#define GPIO_IOCNT_CTL_P51CNT_EN      BIT(2)    /*!< P51 IOCNT enable bit  */
#define GPIO_IOCNT_CTL_P34_MODE_EN    BIT(8)    /*!< P34 trigger edge selection bit (=1 rising edge, =0 falling edge) */
#define GPIO_IOCNT_CTL_P50_MODE_EN    BIT(9)    /*!< P50 trigger edge selection bit (=1 rising edge, =0 falling edge) */
#define GPIO_IOCNT_CTL_P51_MODE_EN    BIT(10)   /*!< P51 trigger edge selection bit (=1 rising edge, =0 falling edge) */
#define GPIO_IOCNT_CTL_CNTREG_CLR     BIT(16)   /*!< IOCNT clear mode cfg bit (=1 sum mode not clear, =0 clean after read)  */

/*constants definitions*/
/* PCA0_PC00 P00 mode cfg */
#define PCA0_PC00(regval) (GPIO_PCA0_PC00 & ((uint32_t)(regval) << 0))
#define GPIO_PCA0_PC00_IO              PCA0_PC00(0)       /*!< use as general IO */
#define GPIO_PCA0_PC00_ANAIN           PCA0_PC00(1)       /*!< use as analog input */
#define GPIO_PCA0_PC00_KEY2            PCA0_PC00(2)       /*!< use as key2 (lower priority than PC12) */
#define GPIO_PCA0_PC00_RX2             PCA0_PC00(3)       /*!< use as uart rx2 */

/* PCA0_PC01 P01 mode cfg */
#define PCA0_PC01(regval) (GPIO_PCA0_PC01 & ((uint32_t)(regval) << 2))
#define GPIO_PCA0_PC01_IO              PCA0_PC01(0)       /*!< use as general IO */
#define GPIO_PCA0_PC01_ANAIN           PCA0_PC01(1)       /*!< use as analog input */
#define GPIO_PCA0_PC01_KEY3            PCA0_PC01(2)       /*!< use as key3 (lower priority than PC13) */
#define GPIO_PCA0_PC01_TX2             PCA0_PC01(3)       /*!< use as uart tx2 */

/* PCA0_PC02 P02 mode cfg bit */
#define GPIO_PCA0_PC02_IO       ((uint32_t)0x00000000U)     /*!< use as general IO */
#define GPIO_PCA0_PC02_ANAIN    GPIO_PCA0_PC02              /*!< use as analog input */

/* PCA0_PC03 P03 mode cfg bit */
#define GPIO_PCA0_PC03_IO       ((uint32_t)0x00000000U)     /*!< use as general IO */
#define GPIO_PCA0_PC03_ANAIN    GPIO_PCA0_PC03              /*!< use as analog input */

/* PCA0_PC04 P04 mode cfg bit */
#define GPIO_PCA0_PC04_IO       ((uint32_t)0x00000000U)     /*!< use as general IO */
#define GPIO_PCA0_PC04_ANAIN    GPIO_PCA0_PC04              /*!< use as analog input */

/* PCA0_PC05 P05 mode cfg bit */
#define GPIO_PCA0_PC05_IO       ((uint32_t)0x00000000U)     /*!< use as general IO */
#define GPIO_PCA0_PC05_ANAIN    GPIO_PCA0_PC05              /*!< use as analog input */

/* GPIO_PCA0_KEY4_SEL */
#define GPIO_PCA0_KEY4_SEL_OTH  ((uint32_t)0x00000000U)     /*!< P04 function decided by PC04 */
#define GPIO_PCA0_KEY4_SEL_P04  GPIO_PCA0_KEY4_SEL          /*!< P04 select as KEY4 (lower priority than PC14 select as KEY4) */

/* PCA0_PC10 P10 mode cfg  */
#define PCA0_PC10(regval) (GPIO_PCA0_PC10 & ((uint32_t)(regval) << 9))
#define GPIO_PCA0_PC10_IO              PCA0_PC010(0)   /*!< use as general IO  */
#define GPIO_PCA0_PC10_KEY0            PCA0_PC010(1)   /*!< use as key0 */
#define GPIO_PCA0_PC10_TCIN            PCA0_PC010(2)   /*!< use as TC0_N[0] output */
#define GPIO_PCA0_PC10_TCOUT           PCA0_PC010(3)   /*!< use as TC0_N[0] input  */

/* PCA0_PC11 P11 mode cfg */
#define PCA0_PC11(regval) (GPIO_PCA0_PC11 & ((uint32_t)(regval) << 11))
#define GPIO_PCA0_PC11_IO              PCA0_PC011(0)   /*!< use as general IO  */
#define GPIO_PCA0_PC11_KEY1            PCA0_PC011(1)   /*!< use as key1 */
#define GPIO_PCA0_PC11_TCIN            PCA0_PC011(2)   /*!< use as TC0_P[0] output */
#define GPIO_PCA0_PC11_TCOUT           PCA0_PC011(3)   /*!< use as TC0_P[0] input  */

/* PCA0_PC12 P12 mode cfg  */
#define PCA0_PC12(regval) (GPIO_PCA0_PC12 & ((uint32_t)(regval) << 13))
#define GPIO_PCA0_PC12_IO              PCA0_PC012(0)   /*!< use as general IO  */
#define GPIO_PCA0_PC12_KEY2            PCA0_PC012(1)   /*!< use as key2 */
#define GPIO_PCA0_PC12_TCIN            PCA0_PC012(2)   /*!< use as TC0_N[1] output */
#define GPIO_PCA0_PC12_TCOUT           PCA0_PC012(3)   /*!< use as TC0_N[1] input  */

/* PCA0_PC13 P13 mode cfg */
#define PCA0_PC13(regval) (GPIO_PCA0_PC13 & ((uint32_t)(regval) << 15))
#define GPIO_PCA0_PC13_IO              PCA0_PC013(0)   /*!< use as general IO  */
#define GPIO_PCA0_PC13_KEY3            PCA0_PC013(1)   /*!< use as key3 */
#define GPIO_PCA0_PC13_TCIN            PCA0_PC013(2)   /*!< use as TC0_P[1] output */
#define GPIO_PCA0_PC13_TCOUT           PCA0_PC013(3)   /*!< use as TC0_P[1] input  */

/* PCA0_PC14 P14 mode cfg */
#define PCA0_PC14(regval) (GPIO_PCA0_PC14 & ((uint32_t)(regval) << 17))
#define GPIO_PCA0_PC14_IO              PCA0_PC014(0)   /*!< use as general IO  */
#define GPIO_PCA0_PC14_KEY4            PCA0_PC014(1)   /*!< use as key4 */
#define GPIO_PCA0_PC14_TCIN            PCA0_PC014(2)   /*!< use as TC1_N[0] output */
#define GPIO_PCA0_PC14_TCOUT           PCA0_PC014(3)   /*!< use as TC1_N[0] input  */

/* PCA0_PC15 P15 mode cfg */
#define PCA0_PC15(regval) (GPIO_PCA0_PC15 & ((uint32_t)(regval) << 19))
#define GPIO_PCA0_PC15_IO              PCA0_PC015(0)   /*!< use as general IO  */
#define GPIO_PCA0_PC15_KEY5            PCA0_PC015(1)   /*!< use as key5 */
#define GPIO_PCA0_PC15_TCIN            PCA0_PC015(2)   /*!< use as TC1_P[0] output */
#define GPIO_PCA0_PC15_TCOUT           PCA0_PC015(3)   /*!< use as TC1_P[0] input  */

/* PCA0_PC16 P16 mode cfg */
#define PCA0_PC16(regval) (GPIO_PCA0_PC16 & ((uint32_t)(regval) << 21))
#define GPIO_PCA0_PC16_IO              PCA0_PC016(0)   /*!< use as general IO  */
#define GPIO_PCA0_PC16_KEY6            PCA0_PC016(1)   /*!< use as key6 */
#define GPIO_PCA0_PC16_TCIN            PCA0_PC016(2)   /*!< use as TC1_N[1] output */
#define GPIO_PCA0_PC16_TCOUT           PCA0_PC016(3)   /*!< use as TC1_N[1] input  */

/* PCA0_PC17 P17 mode cfg bit */
#define PCA0_PC17(regval) (GPIO_PCA0_PC17 & ((uint32_t)(regval) << 23))
#define GPIO_PCA0_PC17_IO              PCA0_PC017(0)   /*!< use as general IO  */
#define GPIO_PCA0_PC17_KEY7            PCA0_PC017(1)   /*!< use as key7 */
#define GPIO_PCA0_PC17_TCIN            PCA0_PC017(2)   /*!< use as TC1_P[1] output */
#define GPIO_PCA0_PC17_TCOUT           PCA0_PC017(3)   /*!< use as TC1_P[1] input  */

/* PCA0_PC201 P20 and P21 mode cfg bit */
#define GPIO_PCA0_PC201_IO      ((uint32_t)0x00000000U)   /*!< P20 and P21 use as general IO  */
#define GPIO_PCA0_PC201_UART0   GPIO_PCA0_PC201           /*!< P20(RX0) and P21(TX0) use as UART0 */

/* PCA0_PC223 P22 and P23 mode cfg bit */
#define GPIO_PCA0_PC223_IO      ((uint32_t)0x00000000U)   /*!< P22 and P23 use as general IO  */
#define GPIO_PCA0_PC223_UART1   GPIO_PCA0_PC223           /*!< P22(RX1) and P23(TX1) use as UART1 */

/* PCA0_PC245 P24 and P25 mode cfg bit */
#define GPIO_PCA0_PC245_IO      ((uint32_t)0x00000000U)   /*!< P24 and P25 use as general IO  */
#define GPIO_PCA0_PC245_UART2   GPIO_PCA0_PC245           /*!< P24(RX2) and P25(TX2) use as UART2 */

/* PCA0_PC267 P26 and P27 mode cfg bit */
#define GPIO_PCA0_PC267_IO      ((uint32_t)0x00000000U)   /*!< P26 and P27 use as general IO  */
#define GPIO_PCA0_PC267_UART3   GPIO_PCA0_PC267           /*!< P26(RX3) and P27(TX3) use as UART3 */

/* PCA0_SWD_SEL SWD selection */
#define GPIO_PCA0_SWD_SEL_OTH       ((uint32_t)0x00000000U)   /*!< do not use P24 P25 as swd, P24 P25 function define by PCA0.PCA0_PC245*/
#define GPIO_PCA0_SWD_SEL_P245      GPIO_PCA0_SWD_SEL         /*!< use P24 as SWDCLK and P25 as SWDIO */

/* PCA0_UART2_SEL UART2 PAD selection */
#define PCA0_UART2_SEL(regval)  (GPIO_PCA0_UART2_SEL & ((uint32_t)(regval) << 30))
#define GPIO_PCA0_UART2_SEL_PC245         PCA0_UART2_SEL(0)   /*!< when PCA0.PC245 =1, select P24/P25 as UART2 */
#define GPIO_PCA0_UART2_SEL_PC0_1         PCA0_UART2_SEL(1)   /*!< when PCA0.PC00 =3 PCA0.PC01 =3, select P00/P01 as UART2 (P00-RX2£¬P01-TX2) */
#define GPIO_PCA0_UART2_SEL_PC223         PCA0_UART2_SEL(2)   /*!< when PCA1.PC223_2 =1, select P24/P25 as UART2  */
#define GPIO_PCA0_UART2_SEL_PC267         PCA0_UART2_SEL(3)   /*!< when PCA1.PC267_2 =1, select P24/P25 as UART2  */

/* PCA1_PC30 P30 mode cfg */
#define PCA1_PC30(regval)  (GPIO_PCA1_PC30 & ((uint32_t)(regval) << 0))
#define GPIO_PCA1_PC30_IO         PCA1_PC30(0)    /*!< use as general IO */
#define GPIO_PCA1_PC30_INTC0      PCA1_PC30(1)    /*!< use as external interupt request No.0 */
#define GPIO_PCA1_PC30_TCIN       PCA1_PC30(2)    /*!< use as TC input */
#define GPIO_PCA1_PC30_TX4        PCA1_PC30(3)    /*!< use as TX4 */

/* PCA1_PC31 PC31 mode cfg */
#define PCA1_PC31(regval)  (GPIO_PCA1_PC31 & ((uint32_t)(regval) << 2))
#define GPIO_PCA1_PC31_IO       PCA1_PC31(0)    /*!< use as general IO */
#define GPIO_PCA1_PC31_INTC1    PCA1_PC31(1)    /*!< use as external interupt request No.1 */
#define GPIO_PCA1_PC31_TCIN     PCA1_PC31(2)    /*!< use as TC input */
#define GPIO_PCA1_PC31_RX4      PCA1_PC31(3)    /*!< use as RX4  */

/* PCA1_PC32 PC32 mode cfg */
#define PCA1_PC32(regval) (GPIO_PCA1_PC32 & ((uint32_t)(regval) << 4))
#define GPIO_PCA1_PC32_IO       PCA1_PC32(0)    /*!< use as general IO */
#define GPIO_PCA1_PC32_INTC2    PCA1_PC32(1)    /*!< use as external interupt request No.2 */
#define GPIO_PCA1_PC32_RTCO     PCA1_PC32(2)    /*!< use as RTC output */
#define GPIO_PCA1_PC32_KEY5     PCA1_PC32(3)    /*!< use as key5 */

/* PCA1_PC33 PC33 mode cfg */
#define PCA1_PC33(regval) (GPIO_PCA1_PC33 & ((uint32_t)(regval) << 6))
#define GPIO_PCA1_PC33_IO       PCA1_PC33(0)    /*!< use as general IO */
#define GPIO_PCA1_PC33_INTC3    PCA1_PC33(1)    /*!< use as external interupt request No.3 */
#define GPIO_PCA1_PC33_RTCI     PCA1_PC33(2)    /*!< use as TC input  */
#define GPIO_PCA1_PC33_CF0      PCA1_PC33(3)    /*!< use as D2F CF0 */

/* PCA1_PC34 PC34 mode cfg */
#define PCA1_PC34(regval) (GPIO_PCA1_PC34 & ((uint32_t)(regval) << 8))
#define GPIO_PCA1_PC34_IO       PCA1_PC34(0)    /*!< use as general IO */
#define GPIO_PCA1_PC34_INTC4    PCA1_PC34(1)    /*!< use as external interupt request No.4 */
#define GPIO_PCA1_PC34_SFO      PCA1_PC34(2)    /*!< use as SF_OUT */
#define GPIO_PCA1_PC34_CF1      PCA1_PC34(3)    /*!< use as D2F CF1 */

/* PCA1_PC35 PC35 mode cfg */
#define PCA1_PC35(regval) (GPIO_PCA1_PC35 & ((uint32_t)(regval) << 10))
#define GPIO_PCA1_PC35_IO       PCA1_PC35(0)    /*!< use as general IO */
#define GPIO_PCA1_PC35_INTC5    PCA1_PC35(1)    /*!< use as external interupt request No.5 */
#define GPIO_PCA1_PC35_TCIN     PCA1_PC35(2)    /*!< use as TC input */
#define GPIO_PCA1_PC35_CF2      PCA1_PC35(3)    /*!< use as D2F CF2 */

/* PCA1_PC36 PC36 mode cfg */
#define PCA1_PC36(regval) (GPIO_PCA1_PC36 & ((uint32_t)(regval) << 12))
#define GPIO_PCA1_PC36_IO       PCA1_PC36(0)    /*!< use as general IO */
#define GPIO_PCA1_PC36_INTC6    PCA1_PC36(1)    /*!< use as external interupt request No.6 */
#define GPIO_PCA1_PC36_POSCO    PCA1_PC36(2)    /*!< use as POSC output pin */

/* PCA1_PC37 PC37 mode cfg */
#define PCA1_PC37(regval) (GPIO_PCA1_PC37 & ((uint32_t)(regval) << 14))
#define GPIO_PCA1_PC37_IO       PCA1_PC37(0)    /*!< use as general IO */
#define GPIO_PCA1_PC37_INTC7    PCA1_PC37(1)    /*!< use as external interupt request No.7 */
#define GPIO_PCA1_PC37_POSCI    PCA1_PC37(2)    /*!< use as POSC input pin */

/* PCA1_PC223_2 P22 and P23 second mode cfg */
#define GPIO_PCA1_PC223_2_NUL     ((uint32_t)0x00000000U)     /*!< P22 and P23 function decided by PCA0.PC223 */
#define GPIO_PCA1_PC223_UART2     GPIO_PCA1_PC223_2           /*!< select P22/P23 as UART2 */

/* PCA1_PC267_2 P26 and P27 second mode cfg */
#define GPIO_PCA1_PC267_2_NUL     ((uint32_t)0x00000000U)     /*!< P26 and P27 function decided by PCA0.PC267 */
#define GPIO_PCA1_PC267_UART2     GPIO_PCA1_PC267_2           /*!< select P26/P27 as UART2 */

/* PIMA_PID10 P10 output mode cfg */
#define GPIO_PIMA_PID10_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID10_NCH      GPIO_PIMA_PID10            /*!< select as N channel open drain output */

/* PIMA_PID11 P11 output mode cfg */
#define GPIO_PIMA_PID11_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID11_NCH      GPIO_PIMA_PID11            /*!< select as N channel open drain output */

/* PIMA_PID12 P12 output mode cfg */
#define GPIO_PIMA_PID12_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID12_NCH      GPIO_PIMA_PID12            /*!< select as N channel open drain output */

/* PIMA_PID13 P13 output mode cfg */
#define GPIO_PIMA_PID13_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID13_NCH      GPIO_PIMA_PID13            /*!< select as N channel open drain output */

/* PIMA_PID14 P14 output mode cfg */
#define GPIO_PIMA_PID14_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID14_NCH      GPIO_PIMA_PID14            /*!< select as N channel open drain output */

/* PIMA_PID15 P15 output mode cfg */
#define GPIO_PIMA_PID15_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID15_NCH      GPIO_PIMA_PID15            /*!< select as N channel open drain output */

/* PIMA_PID16 P16 output mode cfg */
#define GPIO_PIMA_PID16_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID16_NCH      GPIO_PIMA_PID16            /*!< select as N channel open drain output */

/* PIMA_PID17 P17 output mode cfg */
#define GPIO_PIMA_PID17_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID17_NCH      GPIO_PIMA_PID17            /*!< select as N channel open drain output */

/* PIMA_PID20 P20 output mode cfg */
#define GPIO_PIMA_PID20_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID20_NCH      GPIO_PIMA_PID20            /*!< select as N channel open drain output */

/* PIMA_PID21 P21 output mode cfg */
#define GPIO_PIMA_PID21_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID21_NCH      GPIO_PIMA_PID21            /*!< select as N channel open drain output */

/* PIMA_PID22 P22 output mode cfg */
#define GPIO_PIMA_PID22_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID22_NCH      GPIO_PIMA_PID22            /*!< select as N channel open drain output */

/* PIMA_PID23 P23 output mode cfg */
#define GPIO_PIMA_PID23_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID23_NCH      GPIO_PIMA_PID23            /*!< select as N channel open drain output */

/* PIMA_PID24 P24 output mode cfg */
#define GPIO_PIMA_PID24_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID24_NCH      GPIO_PIMA_PID24            /*!< select as N channel open drain output */

/* PIMA_PID25 P25 output mode cfg */
#define GPIO_PIMA_PID25_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID25_NCH      GPIO_PIMA_PID25            /*!< select as N channel open drain output */

/* PIMA_PID26 P26 output mode cfg */
#define GPIO_PIMA_PID26_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID26_NCH      GPIO_PIMA_PID26            /*!< select as N channel open drain output */

/* PIMA_PID27 P27 output mode cfg */
#define GPIO_PIMA_PID27_NORM     ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMA_PID27_NCH      GPIO_PIMA_PID27            /*!< select as N channel open drain output */

/* PIMA_PIL10 P10 input cfg bit */
#define GPIO_PIMA_PIL10_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL10_TTL     GPIO_PIMA_PIL10            /*!< select as TTL input mode */

/* PIMA_PIL11 P11 input cfg bit */
#define GPIO_PIMA_PIL11_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL11_TTL     GPIO_PIMA_PIL11            /*!< select as TTL input mode */

/* PIMA_PIL12 P12 input cfg bit */
#define GPIO_PIMA_PIL12_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL12_TTL     GPIO_PIMA_PIL12            /*!< select as TTL input mode */

/* PIMA_PIL13 P13 input cfg bit */
#define GPIO_PIMA_PIL13_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL13_TTL     GPIO_PIMA_PIL13            /*!< select as TTL input mode */

/* PIMA_PIL14 P14 input cfg bit */
#define GPIO_PIMA_PIL14_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL14_TTL     GPIO_PIMA_PIL14            /*!< select as TTL input mode */

/* PIMA_PIL15 P15 input cfg bit */
#define GPIO_PIMA_PIL15_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL15_TTL     GPIO_PIMA_PIL15            /*!< select as TTL input mode */

/* PIMA_PIL16 P16 input cfg bit */
#define GPIO_PIMA_PIL16_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL16_TTL     GPIO_PIMA_PIL16            /*!< select as TTL input mode */

/* PIMA_PIL17 P17 input cfg bit */
#define GPIO_PIMA_PIL17_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL17_TTL     GPIO_PIMA_PIL17            /*!< select as TTL input mode */

/* PIMA_PIL20 P20 input cfg bit */
#define GPIO_PIMA_PIL20_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL20_TTL     GPIO_PIMA_PIL20            /*!< select as TTL input mode */

/* PIMA_PIL21 P21 input cfg bit */
#define GPIO_PIMA_PIL21_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL21_TTL     GPIO_PIMA_PIL21            /*!< select as TTL input mode */

/* PIMA_PIL22 P22 input cfg bit */
#define GPIO_PIMA_PIL22_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL22_TTL     GPIO_PIMA_PIL22            /*!< select as TTL input mode */

/* PIMA_PIL23 P23 input cfg bit */
#define GPIO_PIMA_PIL23_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL23_TTL     GPIO_PIMA_PIL23            /*!< select as TTL input mode */

/* PIMA_PIL24 P24 input cfg bit */
#define GPIO_PIMA_PIL24_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL24_TTL     GPIO_PIMA_PIL24            /*!< select as TTL input mode */

/* PIMA_PIL25 P25 input cfg bit */
#define GPIO_PIMA_PIL25_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL25_TTL     GPIO_PIMA_PIL25            /*!< select as TTL input mode */

/* PIMA_PIL26 P26 input cfg bit */
#define GPIO_PIMA_PIL26_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL26_TTL     GPIO_PIMA_PIL26            /*!< select as TTL input mode */

/* PIMA_PIL27 P27 input cfg bit */
#define GPIO_PIMA_PIL27_COMS    ((uint32_t)0x00000000U)    /*!< select as CMOS input mode */
#define GPIO_PIMA_PIL27_TTL     GPIO_PIMA_PIL27            /*!< select as TTL input mode */

/* PCB_PC40 P40 mode cfg */
#define GPIO_PCB_PC40_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC40_7816_CLK      GPIO_PCB_PC40             /*!< use as 7816_CLK */

/* PCB_PC41 P41 mode cfg */
#define GPIO_PCB_PC41_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC41_78160_IO      GPIO_PCB_PC41             /*!< use as 78160_IO */

/* PCB_PC42 P42 mode cfg */
#define GPIO_PCB_PC42_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC42_78161_IO      GPIO_PCB_PC42             /*!< use as 78161_IO */

/* PCB_PC43 P43 mode cfg */
#define GPIO_PCB_PC43_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC43_78161_I       GPIO_PCB_PC43             /*!< use as 78161_I  */

/* PCB_PC44 P44 mode cfg */
#define GPIO_PCB_PC44_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC44_SPI0_SCSN     GPIO_PCB_PC44             /*!< use as SPI0_SCSN */

/* PCB_PC45 P45 mode cfg */
#define GPIO_PCB_PC45_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC45_SPI0_SCLK     GPIO_PCB_PC45             /*!< use as SPI0_SCLK */

/* PCB_PC46 P46 mode cfg */
#define GPIO_PCB_PC46_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC46_SPI0_MISO     GPIO_PCB_PC46             /*!< use as SPI0_MISO */

/* PCB_PC47 P47 mode cfg */
#define GPIO_PCB_PC47_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC47_SPI0_MOSI     GPIO_PCB_PC47             /*!< use as SPI0_MOSI */

/* PCB_PC50 P50 mode cfg */
#define GPIO_PCB_PC50_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC50_INT2O         GPIO_PCB_PC50             /*!< use as INT2 pin output */
/* PCB_PC51 P51 mode cfg */
#define GPIO_PCB_PC51_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC51_INT0O         GPIO_PCB_PC51             /*!< use as INT0 pin output */

/* PCB_PC52 P52 mode cfg */
#define GPIO_PCB_PC52_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC52_SCL           GPIO_PCB_PC52             /*!< use as I2C SCL */

/* PCB_PC53 P53 mode cfg */
#define GPIO_PCB_PC53_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC53_SDA           GPIO_PCB_PC53             /*!< use as I2C SDA */

/* PCB_PC54 P54 mode cfg */
#define GPIO_PCB_PC54_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC54_RX5           GPIO_PCB_PC54             /*!< use as uart5 RX5 */

/* PCB_PC55 P55 mode cfg */
#define GPIO_PCB_PC55_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC55_TX5           GPIO_PCB_PC55             /*!< use as uart5 TX5 */

/* PCB_PC56 P56 mode cfg */
#define GPIO_PCB_PC56_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */

/* PCB_PC57 P57 mode cfg */
#define GPIO_PCB_PC57_IO            ((uint32_t)0x00000000U)   /*!< use as general IO  */

/* PCB_PC60 P60 mode cfg */
#define GPIO_PCB_PC60_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC60_LCD      GPIO_PCB_PC60           /*!< use as LCD */

/* PCB_PC61 P61 mode cfg */
#define GPIO_PCB_PC61_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC61_LCD      GPIO_PCB_PC61           /*!< use as LCD */

/* PCB_PC62 P62 mode cfg */
#define GPIO_PCB_PC62_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC62_LCD      GPIO_PCB_PC62           /*!< use as LCD */

/* PCB_PC63 P63 mode cfg */
#define GPIO_PCB_PC63_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC63_LCD      GPIO_PCB_PC63           /*!< use as LCD */

/* PCB_PC64 P64 mode cfg */
#define GPIO_PCB_PC64_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC64_LCD      GPIO_PCB_PC64           /*!< use as LCD */

/* PCB_PC65 P65 mode cfg */
#define GPIO_PCB_PC65_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC65_LCD      GPIO_PCB_PC65           /*!< use as LCD */

/* PCB_PC66 P66 mode cfg */
#define GPIO_PCB_PC66_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC66_LCD      GPIO_PCB_PC66           /*!< use as LCD */

/* PCB_PC67 P67 mode cfg */
#define GPIO_PCB_PC67_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC67_LCD      GPIO_PCB_PC67           /*!< use as LCD */

/* PCB_PC70 P70 mode cfg */
#define GPIO_PCB_PC70_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC70_LCD      GPIO_PCB_PC70           /*!< use as LCD */

/* PCB_PC71 P71 mode cfg */
#define GPIO_PCB_PC71_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC71_LCD      GPIO_PCB_PC71           /*!< use as LCD */

/* PCB_PC72 P72 mode cfg */
#define GPIO_PCB_PC72_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC72_LCD      GPIO_PCB_PC72           /*!< use as LCD */

/* PCB_PC73 P73 mode cfg */
#define GPIO_PCB_PC73_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC73_LCD      GPIO_PCB_PC73           /*!< use as LCD */

/* PCB_PC74 P74 mode cfg */
#define GPIO_PCB_PC74_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC74_LCD    GPIO_PCB_PC74             /*!< use as LCD */

/* PCB_PC75 P75 mode cfg */
#define GPIO_PCB_PC75_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC75_LCD    GPIO_PCB_PC75             /*!< use as LCD */

/* PCB_PC76 P76 mode cfg */
#define GPIO_PCB_PC76_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC76_LCD    GPIO_PCB_PC76             /*!< use as LCD */

/* PCB_PC77 P77 mode cfg */
#define GPIO_PCB_PC77_IO     ((uint32_t)0x00000000U)   /*!< use as general IO  */
#define GPIO_PCB_PC77_LCD    GPIO_PCB_PC77             /*!< use as LCD */

/* PCB2_PC40_2 P40 second mode cfg */
#define PCB2_PC40_2(regval)  (GPIO_PCB2_PC40_2  & ((uint32_t)(regval) << 0 ))
#define GPIO_PCB2_PC40_NUL          PCB2_PC40_2(0)      /*!< P40 function decided by PCB.PC40 */
#define GPIO_PCB2_PC40_INT1         PCB2_PC40_2(1)      /*!< P40 use as INT1 (lower priority than PC31) */
#define GPIO_PCB2_PC40_SPI1_SCSN    PCB2_PC40_2(2)      /*!< P40 use as SPI1_SCSN */
#define GPIO_PCB2_PC40_SPI2_SCSN    PCB2_PC40_2(3)      /*!< P40 use as SPI2_SCSN */

/* PCB2_PC41_2 P41 second mode cfg */
#define PCB2_PC41_2(regval)  (GPIO_PCB2_PC41_2  & ((uint32_t)(regval) << 2 ))
#define GPIO_PCB2_PC41_NUL          PCB2_PC41_2(0)      /*!< P41 function decided by PCB.PC41 */
#define GPIO_PCB2_PC41_INT3         PCB2_PC41_2(1)      /*!< P41 use as INT3 (lower priority than PC33) */
#define GPIO_PCB2_PC41_SPI1_SCLK    PCB2_PC41_2(2)      /*!< P41 use as SPI1_SCLK */
#define GPIO_PCB2_PC41_SPI2_SCLK    PCB2_PC41_2(3)      /*!< P41 use as SPI2_SCLK */

/* PCB2_PC42_2 P42 second mode cfg */
#define PCB2_PC42_2(regval)  (GPIO_PCB2_PC42_2  & ((uint32_t)(regval) << 4 ))
#define GPIO_PCB2_PC42_NUL          PCB2_PC42_2(0)     /*!< P42 function decided by PCB.PC42 */
#define GPIO_PCB2_PC42_INT4         PCB2_PC42_2(1)      /*!< P42 use as INT4 (lower priority than PC34) */
#define GPIO_PCB2_PC42_SPI1_MISO    PCB2_PC42_2(2)      /*!< P42 use as SPI1_MISO */
#define GPIO_PCB2_PC42_SPI2_MISO    PCB2_PC42_2(3)      /*!< P42 use as SPI2_MISO */

/* PCB2_PC43_2 P43 second mode cfg */
#define PCB2_PC43_2(regval)  (GPIO_PCB2_PC43_2  & ((uint32_t)(regval) << 6 ))
#define GPIO_PCB2_PC43_NUL          PCB2_PC43_2(0)     /*!< P43 function decided by PCB.PC43 */
#define GPIO_PCB2_PC43_INT5         PCB2_PC43_2(1)      /*!< P43 use as INT5 (lower priority than PC35) */
#define GPIO_PCB2_PC43_SPI1_MOSI    PCB2_PC43_2(2)      /*!< P43 use as SPI1_MOSI */
#define GPIO_PCB2_PC43_SPI2_MOSI    PCB2_PC43_2(3)      /*!< P43 use as SPI2_MOSI */

/* PCB2_PC44_2 P44 second mode cfg */
#define PCB2_PC44_2(regval)  (GPIO_PCB2_PC44_2  & ((uint32_t)(regval) << 8 ))
#define GPIO_PCB2_PC44_NUL          PCB2_PC44_2(0)     /*!< P44 function decided by PCB.PC44 */
#define GPIO_PCB2_PC44_KEY6         PCB2_PC44_2(1)      /*!< P44 use as KEY6 (lower priority than PC16) */

/* PCB2_PC45_2 P45 second mode cfg */
#define PCB2_PC45_2(regval)  (GPIO_PCB2_PC45_2 & ((uint32_t)(regval) << 10))
#define GPIO_PCB2_PC45_NUL          PCB2_PC45_2(0)      /*!< P45 function decided by PCB.PC45 */
#define GPIO_PCB2_PC45_KEY7         PCB2_PC45_2(1)      /*!< P45 use as KEY7 (lower priority than PC17) */

/* PCB2_PC46_2 P46 second mode cfg */
#define PCB2_PC46_2(regval)  (GPIO_PCB2_PC46_2 & ((uint32_t)(regval) << 12))
#define GPIO_PCB2_PC46_NUL          PCB2_PC46_2(0)      /*!< P46 function decided by PCB.PC46 */
#define GPIO_PCB2_PC46_RX4          PCB2_PC46_2(1)      /*!< P46 use as RX4 */
#define GPIO_PCB2_PC46_CF1          PCB2_PC46_2(2)      /*!< P46 use as D2F CF1 */
#define GPIO_PCB2_PC46_CF2          PCB2_PC46_2(3)      /*!< P46 use as D2F CF2 */

/* PCB2_PC47_2 P47 second mode cfg */
#define PCB2_PC47_2(regval)  (GPIO_PCB2_PC47_2 & ((uint32_t)(regval) << 14))
#define GPIO_PCB2_PC47_NUL          PCB2_PC47_2(0)       /*!< P47 function decided by PCB.PC47 */
#define GPIO_PCB2_PC47_TX4          PCB2_PC47_2(1)      /*!< P47 use as TX4 */
#define GPIO_PCB2_PC47_CF0          PCB2_PC47_2(2)      /*!< P47 use as D2F CF0 */
#define GPIO_PCB2_PC47_CF1          PCB2_PC47_2(3)      /*!< P47 use as D2F CF1 */

/* PCB2_PC50_2 P50 second mode cfg */
#define PCB2_PC50_2(regval)  (GPIO_PCB2_PC50_2 & ((uint32_t)(regval) << 16))
#define GPIO_PCB2_PC50_NUL          PCB2_PC50_2(0)      /*!< P50 function decided by PCB.PC50 */
#define GPIO_PCB2_PC50_RTCO         PCB2_PC50_2(1)      /*!< P50 use as RTC_OUT */
#define GPIO_PCB2_PC50_SPI0_SCSN    PCB2_PC50_2(2)      /*!< P50 use as SPI0_SCSN */
#define GPIO_PCB2_PC50_SF1          PCB2_PC50_2(3)      /*!< P50 use as SF1£¨INT6 OUT) */

/* PCB2_PC51_2 P51 second mode cfg */
#define PCB2_PC51_2(regval)  (GPIO_PCB2_PC51_2 & ((uint32_t)(regval) << 18))
#define GPIO_PCB2_PC51_NUL          PCB2_PC51_2(0)      /*!< P51 function decided by PCB.PC51 */
#define GPIO_PCB2_PC51_RTCO         PCB2_PC51_2(1)      /*!< P51 use as RTC_OUT */
#define GPIO_PCB2_PC51_SPI0_SCLK    PCB2_PC51_2(2)      /*!< P51 use as SPI0_SCLK */
#define GPIO_PCB2_PC51_SF2          PCB2_PC51_2(3)      /*!< P51 use as SF2£¨INT7 OUT) */

/* PCB2_PC52_2 P52 second mode cfg */
#define PCB2_PC52_2(regval)  (GPIO_PCB2_PC52_2 & ((uint32_t)(regval) << 20))
#define GPIO_PCB2_PC52_NUL          PCB2_PC52_2(0)      /*!< P52 function decided by PCB.PC52 */
#define GPIO_PCB2_PC52_TCIN         PCB2_PC52_2(1)      /*!< P52 use as TCIN */
#define GPIO_PCB2_PC52_TC0_N1       PCB2_PC52_2(2)      /*!< P52 use as TC0_N[1] */
#define GPIO_PCB2_PC52_SPI1_SCSN    PCB2_PC52_2(3)      /*!< P52 use as SPI1_SCSN */

/* PCB2_PC53_2 P53 second mode cfg */
#define PCB2_PC53_2(regval)  (GPIO_PCB2_PC53_2 & ((uint32_t)(regval) << 22))
#define GPIO_PCB2_PC53_NUL          PCB2_PC53_2(0)      /*!< P53 function decided by PCB.PC53 */
#define GPIO_PCB2_PC53_TCIN         PCB2_PC53_2(1)      /*!< P53 use as TCIN */
#define GPIO_PCB2_PC53_TC0_P1       PCB2_PC53_2(2)      /*!< P53 use as TC0_P[1] */
#define GPIO_PCB2_PC53_SPI1_SCLK    PCB2_PC53_2(3)      /*!< P53 use as SPI1_SCLK */

/* PCB2_PC54_2 P54 second mode cfg */
#define PCB2_PC54_2(regval)  (GPIO_PCB2_PC54_2 & ((uint32_t)(regval) << 24))
#define GPIO_PCB2_PC54_NUL          PCB2_PC54_2(0)      /*!< P54 function decided by PCB.PC54 */
#define GPIO_PCB2_PC54_TCIN         PCB2_PC54_2(1)      /*!< P54 use as TCIN */
#define GPIO_PCB2_PC54_TC1_N0       PCB2_PC54_2(2)      /*!< P54 use as TC1_N[0] */
#define GPIO_PCB2_PC54_SPI1_MISO    PCB2_PC54_2(3)      /*!< P54 use as SPI1_MISO */

/* PCB2_PC55_2 P55 second mode cfg */
#define PCB2_PC55_2(regval)  (BGPIO_PCB2_PC55_2 & ((uint32_t)(regval) << 26))
#define GPIO_PCB2_PC55_NUL          PCB2_PC55_2(0)      /*!< P55 function decided by PCB.PC55 */
#define GPIO_PCB2_PC55_TCIN         PCB2_PC55_2(1)      /*!< P55 use as TCIN */
#define GPIO_PCB2_PC55_TC1_P0       PCB2_PC55_2(2)      /*!< P55 use as TC1_P[0]*/
#define GPIO_PCB2_PC55_SPI1_MOSI    PCB2_PC55_2(3)      /*!< P55 use as SPI1_MOSI */

/* PCB2_PC56_2 P56 second mode cfg */
#define PCB2_PC56_2(regval)  (GPIO_PCB2_PC56_2 & ((uint32_t)(regval) << 28))
#define GPIO_PCB2_PC56_NUL          PCB2_PC56_2(0)      /*!< P56 function decided by PCB.PC56 */
#define GPIO_PCB2_PC56_TCIN         PCB2_PC56_2(1)      /*!< P56 use as TCIN */
#define GPIO_PCB2_PC56_TC1_N1       PCB2_PC56_2(2)      /*!< P56 use as TC1_N[1]*/

/* PCB2_PC57_2 P57 second mode cfg */
#define PCB2_PC57_2(regval)  (GPIO_PCB2_PC57_2 & ((uint32_t)(regval) << 30))
#define GPIO_PCB2_PC57_NUL          PCB2_PC57_2(0)      /*!< P57 function decided by PCB.PC57 */
#define GPIO_PCB2_PC57_TCIN         PCB2_PC57_2(1)      /*!< P57 use as TCIN */
#define GPIO_PCB2_PC57_TC1_P1       PCB2_PC57_2(2)      /*!< P57 use as TC1_P[1]*/

/* PIMB_PID40 P40 output mode cfg */
#define GPIO_PIMB_PID40_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID40_NCH     GPIO_PIMB_PID40            /*!< select as N channel open drain output */

/* PIMB_PID41 P41 output mode cfg */
#define GPIO_PIMB_PID41_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID41_NCH     GPIO_PIMB_PID41            /*!< select as N channel open drain output */

/* PIMB_PID42 P42 output mode cfg */
#define GPIO_PIMB_PID42_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID42_NCH     GPIO_PIMB_PID42            /*!< select as N channel open drain output */

/* PIMB_PID43 P43 output mode cfg */
#define GPIO_PIMB_PID43_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID43_NCH     GPIO_PIMB_PID43            /*!< select as N channel open drain output */

/* PIMB_PID44 P44 output mode cfg */
#define GPIO_PIMB_PID44_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID44_NCH     GPIO_PIMB_PID44            /*!< select as N channel open drain output */

/* PIMB_PID45 P45 output mode cfg */
#define GPIO_PIMB_PID45_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID45_NCH     GPIO_PIMB_PID45            /*!< select as N channel open drain output */

/* PIMB_PID46 P46 output mode cfg */
#define GPIO_PIMB_PID46_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID46_NCH     GPIO_PIMB_PID46            /*!< select as N channel open drain output */

/* PIMB_PID47 P47 output mode cfg */
#define GPIO_PIMB_PID47_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID47_NCH     GPIO_PIMB_PID47            /*!< select as N channel open drain output */

/* PIMB_PID50 P50 output mode cfg */
#define GPIO_PIMB_PID50_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID50_NCH     GPIO_PIMB_PID50            /*!< select as N channel open drain output */

/* PIMB_PID51 P51 output mode cfg */
#define GPIO_PIMB_PID51_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID51_NCH     GPIO_PIMB_PID51            /*!< select as N channel open drain output */

/* PIMB_PID52 P52 output mode cfg */
#define GPIO_PIMB_PID52_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID52_NCH     GPIO_PIMB_PID52            /*!< select as N channel open drain output */

/* PIMB_PID53 P53 output mode cfg */
#define GPIO_PIMB_PID53_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID53_NCH     GPIO_PIMB_PID53            /*!< select as N channel open drain output */

/* PIMB_PID54 P54 output mode cfg */
#define GPIO_PIMB_PID54_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID54_NCH     GPIO_PIMB_PID54            /*!< select as N channel open drain output */

/* PIMB_PID55 P55 output mode cfg */
#define GPIO_PIMB_PID55_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID55_NCH     GPIO_PIMB_PID55            /*!< select as N channel open drain output */

/* PIMB_PID56 P56 output mode cfg */
#define GPIO_PIMB_PID56_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID56_NCH     GPIO_PIMB_PID56            /*!< select as N channel open drain output */

/* PIMB_PID57 P57 output mode cfg */
#define GPIO_PIMB_PID57_NORM    ((uint32_t)0x00000000U)    /*!< select as normal output mode */
#define GPIO_PIMB_PID57_NCH     GPIO_PIMB_PID57            /*!< select as N channel open drain output */

/* PIMB_PIL40 P40 input mode cfg  */
#define GPIO_PIMB_PIL40_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL40_TTL     GPIO_PIMB_PIL40             /*!< select as TTL input mode */

/* PIMB_PIL41 P41 input mode cfg  */
#define GPIO_PIMB_PIL41_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL41_TTL     GPIO_PIMB_PIL41             /*!< select as TTL input mode */

/* PIMB_PIL42 P42 input mode cfg  */
#define GPIO_PIMB_PIL42_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL42_TTL     GPIO_PIMB_PIL42             /*!< select as TTL input mode */

/* PIMB_PIL43 P43 input mode cfg  */
#define GPIO_PIMB_PIL43_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL43_TTL     GPIO_PIMB_PIL43             /*!< select as TTL input mode */

/* PIMB_PIL44 P44 input mode cfg  */
#define GPIO_PIMB_PIL44_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL44_TTL     GPIO_PIMB_PIL44             /*!< select as TTL input mode */

/* PIMB_PIL45 P45 input mode cfg  */
#define GPIO_PIMB_PIL45_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL45_TTL     GPIO_PIMB_PIL45             /*!< select as TTL input mode */

/* PIMB_PIL46 P46 input mode cfg  */
#define GPIO_PIMB_PIL46_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL46_TTL     GPIO_PIMB_PIL46             /*!< select as TTL input mode */

/* PIMB_PIL47 P47 input mode cfg  */
#define GPIO_PIMB_PIL47_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL47_TTL     GPIO_PIMB_PIL47             /*!< select as TTL input mode */

/* PIMB_PIL50 P50 input mode cfg  */
#define GPIO_PIMB_PIL50_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL50_TTL     GPIO_PIMB_PIL50             /*!< select as TTL input mode */

/* PIMB_PIL51 P51 input mode cfg  */
#define GPIO_PIMB_PIL51_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL51_TTL     GPIO_PIMB_PIL51             /*!< select as TTL input mode */

/* PIMB_PIL52 P52 input mode cfg  */
#define GPIO_PIMB_PIL52_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL52_TTL     GPIO_PIMB_PIL52             /*!< select as TTL input mode */

/* PIMB_PIL53 P53 input mode cfg  */
#define GPIO_PIMB_PIL53_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL53_TTL     GPIO_PIMB_PIL53             /*!< select as TTL input mode */

/* PIMB_PIL54 P54 input mode cfg  */
#define GPIO_PIMB_PIL54_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL54_TTL     GPIO_PIMB_PIL54             /*!< select as TTL input mode */

/* PIMB_PIL55 P55 input mode cfg  */
#define GPIO_PIMB_PIL55_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL55_TTL     GPIO_PIMB_PIL55             /*!< select as TTL input mode */

/* PIMB_PIL56 P56 input mode cfg  */
#define GPIO_PIMB_PIL56_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL56_TTL     GPIO_PIMB_PIL56             /*!< select as TTL input mode */

/* PIMB_PIL57 P57 input mode cfg  */
#define GPIO_PIMB_PIL57_CMOS    ((uint32_t)0x00000000U)     /*!< select as CMOS input mode */
#define GPIO_PIMB_PIL57_TTL     GPIO_PIMB_PIL57             /*!< select as TTL input mode */

/* PCC_PC80 PC80  mode cfg */
#define GPIO_PCC_PC80_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC80_LCD   GPIO_PCC_PC80               /*!< select as LCD */

/* PCC_PC81 PC81  mode cfg */
#define GPIO_PCC_PC81_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC81_LCD   GPIO_PCC_PC81               /*!< select as LCD */

/* PCC_PC82 PC82  mode cfg */
#define GPIO_PCC_PC82_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC82_LCD   GPIO_PCC_PC82               /*!< select as LCD */

/* PCC_PC83 PC83  mode cfg */
#define GPIO_PCC_PC83_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC83_LCD   GPIO_PCC_PC83               /*!< select as LCD */

/* PCC_PC84 PC84  mode cfg */
#define GPIO_PCC_PC84_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC84_LCD   GPIO_PCC_PC84               /*!< select as LCD */

/* PCC_PC85 PC85  mode cfg */
#define GPIO_PCC_PC85_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC85_LCD   GPIO_PCC_PC85               /*!< select as LCD */

/* PCC_PC86 PC86  mode cfg */
#define GPIO_PCC_PC86_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC86_LCD   GPIO_PCC_PC86               /*!< select as LCD */

/* PCC_PC87 PC87  mode cfg */
#define GPIO_PCC_PC87_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC87_LCD   GPIO_PCC_PC87               /*!< select as LCD */

/* PCC_PC90 PC90  mode cfg */
#define GPIO_PCC_PC90_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC90_LCD   GPIO_PCC_PC90               /*!< select as LCD */

/* PCC_PC91 PC91  mode cfg */
#define GPIO_PCC_PC91_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC91_LCD   GPIO_PCC_PC91               /*!< select as LCD */

/* PCC_PC92 PC92  mode cfg */
#define GPIO_PCC_PC92_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC92_LCD   GPIO_PCC_PC92               /*!< select as LCD */

/* PCC_PC93 PC93  mode cfg */
#define GPIO_PCC_PC93_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC93_LCD   GPIO_PCC_PC93               /*!< select as LCD */

/* PCC_PC94 PC94  mode cfg */
#define GPIO_PCC_PC94_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC94_LCD   GPIO_PCC_PC94               /*!< select as LCD */

/* PCC_PC95 PC95  mode cfg */
#define GPIO_PCC_PC95_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC95_LCD   GPIO_PCC_PC95               /*!< select as LCD */

/* PCC_PC96 PC96  mode cfg */
#define GPIO_PCC_PC96_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC96_LCD   GPIO_PCC_PC96               /*!< select as LCD */

/* PCC_PC97 PC97  mode cfg */
#define GPIO_PCC_PC97_IO    ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC97_LCD   GPIO_PCC_PC97               /*!< select as LCD */

/* PCC_PC100   PC100 mode cfg */
#define GPIO_PCC_PC100_IO           ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC100_LCD          GPIO_PCC_PC100              /*!< select as LCD */

/* PCC_PC101   PC101 mode cfg */
#define GPIO_PCC_PC101_IO           ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC101_LCD          GPIO_PCC_PC101              /*!< select as LCD */

/* PCC_PC102   PC102 mode cfg */
#define GPIO_PCC_PC102_IO           ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC102_LCD          GPIO_PCC_PC102              /*!< select as LCD */

/* PCC_PC103   PC103 mode cfg */
#define GPIO_PCC_PC103_IO           ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC103_LCD          GPIO_PCC_PC103              /*!< select as LCD */

/* PCC_PC104   PC104 mode cfg */
#define GPIO_PCC_PC104_IO           ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC104_SPI3_SCSN    GPIO_PCC_PC104              /*!< select as SPI3_SCSN */

/* PCC_PC105   PC105 mode cfg */
#define GPIO_PCC_PC105_IO           ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC105_SPI3_SCLK    GPIO_PCC_PC105              /*!< select as SPI3_SCLK */

/* PCC_PC106   PC106 mode cfg */
#define GPIO_PCC_PC106_IO           ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC106_SPI3_MISO    GPIO_PCC_PC106              /*!< select as SPI3_MISO */

/* PCC_PC107   PC107 mode cfg */
#define GPIO_PCC_PC107_IO           ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC107_SPI3_MOSI    GPIO_PCC_PC107              /*!< select as SPI3_MOSI */

/* PCC_PC110   PC110 mode cfg */
#define GPIO_PCC_PC110_IO           ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC110_SPI0_SCSN    GPIO_PCC_PC110              /*!< select as SPI0_SCSN */

/* PCC_PC111   PC111 mode cfg */
#define GPIO_PCC_PC111_IO           ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC111_SPI0_SCLK    GPIO_PCC_PC111              /*!< select as SPI0_SCLK */

/* PCC_PC112   PC112 mode cfg */
#define GPIO_PCC_PC112_IO           ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC112_SPI0_MISO    GPIO_PCC_PC112              /*!< select as SPI0_MISO */

/* PCC_PC113   PC113 mode cfg */
#define GPIO_PCC_PC113_IO           ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCC_PC113_SPI0_MOSI    GPIO_PCC_PC113              /*!< select as SPI0_MOSI */

/* PCC_SPI_MUX SPI0 pin defination bit */
#define GPIO_PCC_SPI_MUX_P4         ((uint32_t)0x00000000U)      /*!< select P50/P51/P46/P47 as SPI0 */
#define GPIO_PCC_SPI_MUX_P11        GPIO_PCC_SPI_MUX             /*!< select P110/P111/P112/P113 as SPI0 */

/* PIMC_PID110 P110 output mode cfg */
#define GPIO_PIMC_PID110_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMC_PID110_NCH       GPIO_PIMC_PID110             /*!< select as N channel open drain output */

/* PIMC_PID111 P111 output mode cfg */
#define GPIO_PIMC_PID111_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMC_PID111_NCH       GPIO_PIMC_PID111             /*!< select as N channel open drain output */

/* PIMC_PID112 P112 output mode cfg */
#define GPIO_PIMC_PID112_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMC_PID112_NCH       GPIO_PIMC_PID112             /*!< select as N channel open drain output */

/* PIMC_PID113 P113 output mode cfg */
#define GPIO_PIMC_PID113_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMC_PID113_NCH       GPIO_PIMC_PID113             /*!< select as N channel open drain output */

/* PIMC_PIL110 P110 input mode cfg */
#define GPIO_PIMC_PIL110_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output */
#define GPIO_PIMC_PIL110_TTL       GPIO_PIMC_PIL110             /*!< select as TTL input mode */

/* PIMC_PIL111 P111 input mode cfg */
#define GPIO_PIMC_PIL111_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output */
#define GPIO_PIMC_PIL111_TTL       GPIO_PIMC_PIL111             /*!< select as TTL input mode */

/* PIMC_PIL112 P112 input mode cfg */
#define GPIO_PIMC_PIL112_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output */
#define GPIO_PIMC_PIL112_TTL       GPIO_PIMC_PIL112             /*!< select as TTL input mode */

/* PIMC_PIL113 P113 input mode cfg */
#define GPIO_PIMC_PIL113_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output */
#define GPIO_PIMC_PIL113_TTL       GPIO_PIMC_PIL113             /*!< select as TTL input mode */

/* PIMC_PID114 P114 output mode cfg */
#define GPIO_PIMC_PID114_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMC_PID114_NCH       GPIO_PIMC_PID114             /*!< select as N channel open drain output */

/* PIMC_PID115 P115 output mode cfg */
#define GPIO_PIMC_PID115_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMC_PID115_NCH       GPIO_PIMC_PID115             /*!< select as N channel open drain output */

/* PIMC_PID116 P116 output mode cfg */
#define GPIO_PIMC_PID116_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMC_PID116_NCH       GPIO_PIMC_PID116             /*!< select as N channel open drain output */

/* PIMC_PID117 P117 output mode cfg */
#define GPIO_PIMC_PID117_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMC_PID117_NCH       GPIO_PIMC_PID117             /*!< select as N channel open drain output */

/* PIMC_PIL114 P114 input mode cfg */
#define GPIO_PIMC_PIL114_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output*/
#define GPIO_PIMC_PIL114_TTL       GPIO_PIMC_PIL114             /*!< select as TTL input mode */

/* PIMC_PIL115 P115 input mode cfg */
#define GPIO_PIMC_PIL115_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output*/
#define GPIO_PIMC_PIL115_TTL       GPIO_PIMC_PIL115             /*!< select as TTL input mode */

/* PIMC_PIL116 P116 input mode cfg */
#define GPIO_PIMC_PIL116_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output*/
#define GPIO_PIMC_PIL116_TTL       GPIO_PIMC_PIL116             /*!< select as TTL input mode */

/* PIMC_PIL117 P117 input mode cfg */
#define GPIO_PIMC_PIL117_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output*/
#define GPIO_PIMC_PIL117_TTL       GPIO_PIMC_PIL117             /*!< select as TTL input mode */

/* GPIO_PCD_PC120 P120 mode cfg */
#define GPIO_PCD_PC120_IO         ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCD_PC120_LCD        GPIO_PCD_PC120              /*!< select as LCD    */

/* GPIO_PCD_PC121 P121 mode cfg */
#define GPIO_PCD_PC121_IO         ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCD_PC121_LCD        GPIO_PCD_PC121              /*!< select as LCD    */

/* GPIO_PCD_PC122 P122 mode cfg */
#define GPIO_PCD_PC122_IO         ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCD_PC122_LCD        GPIO_PCD_PC122              /*!< select as LCD    */

/* GPIO_PCD_PC123 P123 mode cfg */
#define GPIO_PCD_PC123_IO         ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCD_PC123_LCD        GPIO_PCD_PC123              /*!< select as LCD    */

/* GPIO_PCD_PC124 P124 mode cfg */
#define GPIO_PCD_PC124_IO         ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCD_PC124_LCD        GPIO_PCD_PC124              /*!< select as LCD    */

/* GPIO_PCD_PC125 P125 mode cfg */
#define GPIO_PCD_PC125_IO         ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCD_PC125_LCD        GPIO_PCD_PC125              /*!< select as LCD    */

/* GPIO_PCD_PC126 P126 mode cfg */
#define GPIO_PCD_PC126_IO         ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCD_PC126_LCD        GPIO_PCD_PC126              /*!< select as LCD    */

/* GPIO_PCD_PC127 P127 mode cfg */
#define GPIO_PCD_PC127_IO         ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCD_PC127_LCD        GPIO_PCD_PC127              /*!< select as LCD    */

/* GPIO_PCD_PC130 P130 mode cfg */
#define GPIO_PCD_PC130_IO         ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCD_PC130_LCDVA      GPIO_PCD_PC130              /*!< select as LCDVA  */

/* GPIO_PCD_PC131 P131 mode cfg */
#define GPIO_PCD_PC131_IO         ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCD_PC131_LCDVB      GPIO_PCD_PC131              /*!< select as LCDVB  */

/* GPIO_PCD_PC132 P132 mode cfg */
#define GPIO_PCD_PC132_IO         ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCD_PC132_LCDVC      GPIO_PCD_PC132              /*!< select as LCDVC  */

/* GPIO_PCD_PC134 P134 mode cfg */
#define GPIO_PCD_PC134_IO         ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCD_PC134_LCDVP1     GPIO_PCD_PC134              /*!< select as LCDVP1 */

/* GPIO_PCD_PC135 P135 mode cfg */
#define GPIO_PCD_PC135_IO         ((uint32_t)0x00000000U)     /*!< select as general IO */
#define GPIO_PCD_PC135_LCDVP2     GPIO_PCD_PC135              /*!< select as LCDVP2 */

/* PIMD_PID140 P140 output mode cfg bit */
#define GPIO_PIMD_PID140_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMD_PID140_NCH       GPIO_PIMD_PID140             /*!< select as N channel open drain output */

/* PIMD_PID141 P141 output mode cfg bit */
#define GPIO_PIMD_PID141_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMD_PID141_NCH       GPIO_PIMD_PID141             /*!< select as N channel open drain output */

/* PIMD_PID142 P142 output mode cfg bit */
#define GPIO_PIMD_PID142_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMD_PID142_NCH       GPIO_PIMD_PID142             /*!< select as N channel open drain output */

/* PIMD_PID143 P143 output mode cfg bit */
#define GPIO_PIMD_PID143_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMD_PID143_NCH       GPIO_PIMD_PID143             /*!< select as N channel open drain output */

/* PIMD_PIL140 P140 input mode cfg bit  */
#define GPIO_PIMD_PIL140_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output */
#define GPIO_PIMD_PIL140_TTL       GPIO_PIMD_PIL140             /*!< select as TTL input mode */

/* PIMD_PIL141 P141 input mode cfg bit  */
#define GPIO_PIMD_PIL141_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output */
#define GPIO_PIMD_PIL141_TTL       GPIO_PIMD_PIL141             /*!< select as TTL input mode */

/* PIMD_PIL142 P142 input mode cfg bit  */
#define GPIO_PIMD_PIL142_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output */
#define GPIO_PIMD_PIL142_TTL       GPIO_PIMD_PIL142             /*!< select as TTL input mode */

/* PIMD_PIL143 P143 input mode cfg bit  */
#define GPIO_PIMD_PIL143_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output */
#define GPIO_PIMD_PIL143_TTL       GPIO_PIMD_PIL143             /*!< select as TTL input mode */

/* PIMD_PID144 P144 output mode cfg bit */
#define GPIO_PIMD_PID144_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMD_PID144_NCH        GPIO_PIMD_PID144            /*!< select as N channel open drain output */

/* PIMD_PID145 P145 output mode cfg bit */
#define GPIO_PIMD_PID145_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMD_PID145_NCH        GPIO_PIMD_PID145            /*!< select as N channel open drain output */

/* PIMD_PID146 P146 output mode cfg bit */
#define GPIO_PIMD_PID146_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMD_PID146_NCH        GPIO_PIMD_PID146            /*!< select as N channel open drain output */

/* PIMD_PID147 P147 output mode cfg bit */
#define GPIO_PIMD_PID147_NORM      ((uint32_t)0x00000000U)      /*!< select as normal output mode */
#define GPIO_PIMD_PID147_NCH        GPIO_PIMD_PID147            /*!< select as N channel open drain output */

/* PIMD_PIL144 P144 input mode cfg bit  */
#define GPIO_PIMD_PIL144_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output */
#define GPIO_PIMD_PIL144_TTL       GPIO_PIMD_PIL144             /*!< select as TTL input mode */

/* PIMD_PIL145 P145 input mode cfg bit  */
#define GPIO_PIMD_PIL145_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output */
#define GPIO_PIMD_PIL145_TTL       GPIO_PIMD_PIL145             /*!< select as TTL input mode */

/* PIMD_PIL146 P146 input mode cfg bit  */
#define GPIO_PIMD_PIL146_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output */
#define GPIO_PIMD_PIL146_TTL       GPIO_PIMD_PIL146             /*!< select as TTL input mode */

/* PIMD_PIL147 P147 input mode cfg bit  */
#define GPIO_PIMD_PIL147_COMS      ((uint32_t)0x00000000U)      /*!< select as N channel open drain output */
#define GPIO_PIMD_PIL147_TTL       GPIO_PIMD_PIL147             /*!< select as TTL input mode */

#endif /* RN8XXX_V2_GPIO_H */

// -*- r32775 -*-
