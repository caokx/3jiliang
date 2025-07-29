#ifndef  __SPL_H
#define  __SPL_H

/* reg default value */
#define ANAADC_REG_DEF         0x40
#define ANACLK1_REG_DEF        0x420
#define ANACLK2_REG_DEF        0x14
#define ANALDO_REG_DEF         0x58
#define ANABGR_REG_DEF         0x6158
#define ANAPSW_REG_DEF         0x10
#define TPSCTRL_REG_DEF        0x193b//0x7bb
#define ADCTEST_REG_DEF        0x28
#define CACHECTRL_REG_DEF      0x1

#define RTCMODE_REG_DEF        0x1
#define RTCDOTA0_REG_DEF       0x0
#define RTCALPHAL_REG_DEF      0x3ee//0x404
#define RTCALPHAH_REG_DEF      0x4cf//0x4c9
#define RTCXT0_REG_DEF         0x64
#define RTCBETA_REG_DEF        0xff
#define WDTCTRL_REG_DEF        0x6e
#define WDTHALT_REG_DEF        0x7e5a
#define WDTSTBY_REG_DEF        0xa538
#define EMAP_REG_DEF           0x0
#define RTCTADJ_REG_DEF        0x680//0x66a
#define RTCZT_REG_DEF          0x116

//====================================
// From QC eeSpl.h svn r9327
//====================================

#define WAFER_NUM  0xFA69
//===========================================
//  EEPROM SPECIAL LINE 1
//===========================================
#define F1             0x0
#define F2             0x0
#define F3             0x0
#define F4             0x0

//A?
#define ANAADC         0x40
#define ANACLK1        0x420
#define ANACLK2        0x14
#define ANALDO         0x58
#define ANABGR         0x615a//0x6158
#define ANAPSW         0x10
#define FTTIMES        0x1
#define FTRES          0x5678
#define TPSCTRL        0x193b
#define ADCTEST        0x28
#define CACHECTRL      0x1

//B?
#define ANAADC_B       0x40
#define ANACLK1_B      0x420
#define ANACLK2_B      0x4E14      //2015/10/13,?LCD/SAR????LOSC
#define ANALDO_B       0x0850
#define ANABGR_B       0x615A      //2015/10/13,?BGR TRIM???0x615a
#define ANAPSW_B       0x0010      //2015/8/24,BOR18 on,LCD???LBGR
#define FTTIMES_B      0x1
#define FTRES_B        0x5678
#define TPSCTRL_B      0x193b
#define ADCTEST_B      0x28
#define CACHECTRL_B    0x1
#define SOFT_CHIPID_B  0x000B      //2015/10/13??????B

//C?
#define ANAADC_C          0x3440
#define ANACLK1_C         0x60
#define ANACLK2_C         0x914
#define ANALDO_C          0x145f
#define ANABGR_C          0x612a//0x593a
#define ANAPSW_C          0x0
#define FTTIMES_C         0x1
#define FTRES_C           0x5678
#define TPSCTRL_C         0x193b
#define ADCTEST_C         0x28
#define CACHECTRL_C       0x1
#define ANAPWR_C          0x7000
#define ANACLK3_C         0x3ca4
#define ANASYS_C          0x6c22
#define DIEVER_C          0xc0
#define EETMSPE_C         0x2FF
#define EETEPE_C          0x2
#define EETMSCE_C         0x2FF
#define EETECE_C          0x2
#define EETMSPP_C         0x2B2
#define EETPPP_C          0x1
#define FLTMSPE_C         0x325
#define FLTEPE_C          0x3
#define FLTMSCE_C         0x36B
#define FLTECE_C          0x3
#define FLTMSPP_C         0x2B2
#define FLTPPP_C          0x1
#define EETMSPE32K_C      0x1A
#define EETMSCE32K_C      0x1A
#define EETMSPP32K_C      0x18
#define FLTMSPE32K_C      0x1C
#define FLTMSCE32K_C      0x1E
#define FLTMSPP32K_C      0x18

//E?
#define ANAADC_E          0x3400
#define ANACLK1_E         0x60
#define ANACLK2_E         0x900
#define ANALDO_E          0x29ff
//#define ANABGR_E          0x6150
#define ANAPSW_E          0x0
#define FTTIMES_E         0x1
#define FTRES_E           0x5678
#define TPSCTRL_E         0x083b
#define ADCTEST_E         0x3e8
#define CACHECTRL_E       0x1
//#define ANAPWR_E          0x7000
//#define ANACLK3_E         0x3ca4
#define ANASYS_E          0xac22
#define DIEVER_E          0xe0
#define EETMSPE_E         0x2FF
#define EETEPE_E          0x2
#define EETMSCE_E         0x2FF
#define EETECE_E          0x2
#define EETMSPP_E         0x2B2
#define EETPPP_E          0x1
#define FLTMSPE_E         0x325
#define FLTEPE_E          0x3
#define FLTMSCE_E         0x36B
#define FLTECE_E          0x3
#define FLTMSPP_E         0x2B2
#define FLTPPP_E          0x1
#define EETMSPE32K_E      0x1A
#define EETMSCE32K_E      0x1A
#define EETMSPP32K_E      0x18
#define FLTMSPE32K_E      0x1C
#define FLTMSCE32K_E      0x1E
#define FLTMSPP32K_E      0x18

#define LOSC_CFG2_E       0x6424
#define MADC_ANA_BGR_E    0x6150
#define MADC_ANA_LDO_E    0x4
#define MADC_ANA_RCH_E    0x300
#define MADC_SAR_CTL2_E   0x3   //0->3,20161129,hqn

//F?
#define ANAADC_F          0x3400
#define ANACLK1_F         0x60
#define ANACLK2_F         0x900
#define ANALDO_F          0x29ff
//#define ANABGR_E          0x6150
#define ANAPSW_F          0x0
#define FTTIMES_F         0x1
#define FTRES_F           0x5678
#define TPSCTRL_F         0x083b
#define ADCTEST_F         0x3e8
#define CACHECTRL_F       0x1
//#define ANAPWR_E          0x7000
//#define ANACLK3_E         0x3ca4
#define ANASYS_F          0xac22
#define DIEVER_F          0xf0
#define EETMSPE_F         0x0
#define EETEPE_F          0x0
#define EETMSCE_F         0x0
#define EETECE_F          0x0
#define EETMSPP_F         0x0
#define EETPPP_F          0x0
#define FLTMSPE_F         0x325
#define FLTEPE_F          0x38
#define FLTMSCE_F         0x36B
#define FLTECE_F          0x3e
#define FLTMSPP_F         0x2B2
#define FLTPPP_F          0x18
#define EETMSPE32K_F      0x0
#define EETMSCE32K_F      0x0
#define EETMSPP32K_F      0x0
#define FLTMSPE32K_F      0x1C
#define FLTMSCE32K_F      0x1E
#define FLTMSPP32K_F      0x18

#define LOSC_CFG2_F       0x6424
#define MADC_ANA_BGR_F    0x6150
#define MADC_ANA_LDO_F    0x4
#define MADC_ANA_RCH_F    0x300
#define MADC_SAR_CTL2_F   0x3
#define FL_CFG_F          0x1
#define FL_TW32K_F        0x0
#define FL_TW1M_F         0x0
#define FL_TW3M_F         0x1
#define FL_TW7M_F         0x2
#define FL_TW14M_F        0x3
#define FL_TW29M_F        0x7

/* from hqn @2023.2.20 */
#define TPSCTRL_71        0x083b
#define ADCTEST_71        0x5b58
#define LOSC_CFG2_71      0x6428
#define MADC_ANA_BGR_71   0x8200
#define MADC_ANA_LDO_71   0x4
#define MADC_ANA_RCH_71   0x180
#define MADC_SAR_CTL2_71  0x2904
#define RTCMODE_71        0x1
#define RTCTADJ_71        0x670
#define RTCZT_71          0xd11
//===========================================
//  EEPROM SPECIAL LINE 1
//===========================================
#define CP0_H         0x0
#define CP0_L         0x0
#define PASS_H        0x0
#define PASS_L        0x0

#define RTCMODE     0x1
#define RTCDOTA0    0x0
#define RTCALPHAL   0x3ee
#define RTCALPHAH   0x4cf
#define RTCXT0      0x64
#define RTCBETA     0xff

#define WDTCTRL     0x68
#define EMAP        0x0
#define WDTHALT     0x7e5a
#define WDTSTBY     0xa538

#define RTCTADJ     0x680
#define RTCZT       0x116

#endif

// -*- r32775 -*-
