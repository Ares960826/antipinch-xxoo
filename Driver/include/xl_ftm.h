/**
  ******************************************************************************
  * @file     xl_ftm.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the FTM 
  *           firmware library.
  ******************************************************************************
  * @attention
	*
  * 2019 by Chipways Communications,Inc. All Rights Reserved.
  * This software is supplied under the terms of a license
  * agreement or non-disclosure agreement with Chipways.
  * Passing on and copying of this document,and communication
  * of its contents is not permitted without prior written
  * authorization.
  *
  * <h2><center>&copy; COPYRIGHT 2019 Chipways</center></h2>
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/	  
#ifndef XL_FTM_H__
#define XL_FTM_H__

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ---------------------------------------------------------------*/
#include <XL6600.h>
/* Register define ------------------------------------------------------------*/
/* SC Bit Fields */
#define FTM_SC_PS_MASK                           0x7u
#define FTM_SC_PS_SHIFT                          0
#define FTM_SC_CLKS_MASK                         0x18u
#define FTM_SC_CLKS_SHIFT                        3
#define FTM_SC_CPWMS_MASK                        0x20u
#define FTM_SC_CPWMS_SHIFT                       5
#define FTM_SC_TOIE_MASK                         0x40u
#define FTM_SC_TOIE_SHIFT                        6
#define FTM_SC_TOF_MASK                          0x80u
#define FTM_SC_TOF_SHIFT                         7
	
/* CNT Bit Fields */
#define FTM_CNT_COUNT_MASK                       0xFFFFu
#define FTM_CNT_COUNT_SHIFT                      0
	
/* MOD Bit Fields */
#define FTM_MOD_MOD_MASK                         0xFFFFu
#define FTM_MOD_MOD_SHIFT                        0

/* CnSC Bit Fields */
#define FTM_CnSC_ELSA_MASK                       0x4u
#define FTM_CnSC_ELSA_SHIFT                      2
#define FTM_CnSC_ELSB_MASK                       0x8u
#define FTM_CnSC_ELSB_SHIFT                      3
#define FTM_CnSC_MSA_MASK                        0x10u
#define FTM_CnSC_MSA_SHIFT                       4
#define FTM_CnSC_MSB_MASK                        0x20u
#define FTM_CnSC_MSB_SHIFT                       5
#define FTM_CnSC_CHIE_MASK                       0x40u
#define FTM_CnSC_CHIE_SHIFT                      6
#define FTM_CnSC_CHF_MASK                        0x80u
#define FTM_CnSC_CHF_SHIFT                       7

/* CnV Bit Fields */
#define FTM_CnV_VAL_MASK                         0xFFFFu
#define FTM_CnV_VAL_SHIFT                        0

/* CNTIN Bit Fields */
#define FTM_CNTIN_INIT_MASK                      0xFFFFu
#define FTM_CNTIN_INIT_SHIFT                     0

/* STATUS Bit Fields */
#define FTM_STATUS_CH0F_MASK                     0x1u
#define FTM_STATUS_CH0F_SHIFT                    0
#define FTM_STATUS_CH1F_MASK                     0x2u
#define FTM_STATUS_CH1F_SHIFT                    1
#define FTM_STATUS_CH2F_MASK                     0x4u
#define FTM_STATUS_CH2F_SHIFT                    2
#define FTM_STATUS_CH3F_MASK                     0x8u
#define FTM_STATUS_CH3F_SHIFT                    3
#define FTM_STATUS_CH4F_MASK                     0x10u
#define FTM_STATUS_CH4F_SHIFT                    4
#define FTM_STATUS_CH5F_MASK                     0x20u
#define FTM_STATUS_CH5F_SHIFT                    5
#define FTM_STATUS_CH6F_MASK                     0x40u
#define FTM_STATUS_CH6F_SHIFT                    6
#define FTM_STATUS_CH7F_MASK                     0x80u
#define FTM_STATUS_CH7F_SHIFT                    7

/* MODE Bit Fields */
#define FTM_MODE_SYNCLOADEN_MASK                 0x1u
#define FTM_MODE_SYNCLOADEN_SHIFT                0
#define FTM_MODE_INIT_MASK                       0x2u
#define FTM_MODE_INIT_SHIFT                      1
#define FTM_MODE_WPDIS_MASK                      0x4u
#define FTM_MODE_WPDIS_SHIFT                     2
#define FTM_MODE_PWMSYNC_MASK                    0x8u
#define FTM_MODE_PWMSYNC_SHIFT                   3
#define FTM_MODE_CAPTEST_MASK                    0x10u
#define FTM_MODE_CAPTEST_SHIFT                   4
#define FTM_MODE_FAULTM_MASK                     0x60u
#define FTM_MODE_FAULTM_SHIFT                    5
#define FTM_MODE_FAULTIE_MASK                    0x80u
#define FTM_MODE_FAULTIE_SHIFT                   7

/* SYNC Bit Fields */
#define FTM_SYNC_CNTMIN_MASK                     0x1u
#define FTM_SYNC_CNTMIN_SHIFT                    0
#define FTM_SYNC_CNTMAX_MASK                     0x2u
#define FTM_SYNC_CNTMAX_SHIFT                    1
#define FTM_SYNC_REINIT_MASK                     0x4u
#define FTM_SYNC_REINIT_SHIFT                    2
#define FTM_SYNC_SYNCHOM_MASK                    0x8u
#define FTM_SYNC_SYNCHOM_SHIFT                   3
#define FTM_SYNC_TRIG0_MASK                      0x10u
#define FTM_SYNC_TRIG0_SHIFT                     4
#define FTM_SYNC_TRIG1_MASK                      0x20u
#define FTM_SYNC_TRIG1_SHIFT                     5
#define FTM_SYNC_TRIG2_MASK                      0x40u
#define FTM_SYNC_TRIG2_SHIFT                     6
#define FTM_SYNC_SWSYNC_MASK                     0x80u
#define FTM_SYNC_SWSYNC_SHIFT                    7

/* OUTINIT Bit Fields */
#define FTM_OUTINIT_CH0OI_MASK                   0x1u
#define FTM_OUTINIT_CH0OI_SHIFT                  0
#define FTM_OUTINIT_CH1OI_MASK                   0x2u
#define FTM_OUTINIT_CH1OI_SHIFT                  1
#define FTM_OUTINIT_CH2OI_MASK                   0x4u
#define FTM_OUTINIT_CH2OI_SHIFT                  2
#define FTM_OUTINIT_CH3OI_MASK                   0x8u
#define FTM_OUTINIT_CH3OI_SHIFT                  3
#define FTM_OUTINIT_CH4OI_MASK                   0x10u
#define FTM_OUTINIT_CH4OI_SHIFT                  4
#define FTM_OUTINIT_CH5OI_MASK                   0x20u
#define FTM_OUTINIT_CH5OI_SHIFT                  5
#define FTM_OUTINIT_CH6OI_MASK                   0x40u
#define FTM_OUTINIT_CH6OI_SHIFT                  6
#define FTM_OUTINIT_CH7OI_MASK                   0x80u
#define FTM_OUTINIT_CH7OI_SHIFT                  7

/* OUTMASK Bit Fields */
#define FTM_OUTMASK_CH0OM_MASK                   0x1u
#define FTM_OUTMASK_CH0OM_SHIFT                  0
#define FTM_OUTMASK_CH1OM_MASK                   0x2u
#define FTM_OUTMASK_CH1OM_SHIFT                  1
#define FTM_OUTMASK_CH2OM_MASK                   0x4u
#define FTM_OUTMASK_CH2OM_SHIFT                  2
#define FTM_OUTMASK_CH3OM_MASK                   0x8u
#define FTM_OUTMASK_CH3OM_SHIFT                  3
#define FTM_OUTMASK_CH4OM_MASK                   0x10u
#define FTM_OUTMASK_CH4OM_SHIFT                  4
#define FTM_OUTMASK_CH5OM_MASK                   0x20u
#define FTM_OUTMASK_CH5OM_SHIFT                  5
#define FTM_OUTMASK_CH6OM_MASK                   0x40u
#define FTM_OUTMASK_CH6OM_SHIFT                  6
#define FTM_OUTMASK_CH7OM_MASK                   0x80u
#define FTM_OUTMASK_CH7OM_SHIFT                  7

/* COMBINE Bit Fields */
#define FTM_COMBINE_COMBINE0_MASK                0x1u
#define FTM_COMBINE_COMBINE0_SHIFT               0
#define FTM_COMBINE_COMP0_MASK                   0x2u
#define FTM_COMBINE_COMP0_SHIFT                  1
#define FTM_COMBINE_DECAPEN0_MASK                0x4u
#define FTM_COMBINE_DECAPEN0_SHIFT               2
#define FTM_COMBINE_DECAP0_MASK                  0x8u
#define FTM_COMBINE_DECAP0_SHIFT                 3
#define FTM_COMBINE_DTEN0_MASK                   0x10u
#define FTM_COMBINE_DTEN0_SHIFT                  4
#define FTM_COMBINE_SYNCEN0_MASK                 0x20u
#define FTM_COMBINE_SYNCEN0_SHIFT                5
#define FTM_COMBINE_FAULTEN0_MASK                0x40u
#define FTM_COMBINE_FAULTEN0_SHIFT               6
#define FTM_COMBINE_COMBINE1_MASK                0x100u
#define FTM_COMBINE_COMBINE1_SHIFT               8
#define FTM_COMBINE_COMP1_MASK                   0x200u
#define FTM_COMBINE_COMP1_SHIFT                  9
#define FTM_COMBINE_DECAPEN1_MASK                0x400u
#define FTM_COMBINE_DECAPEN1_SHIFT               10
#define FTM_COMBINE_DECAP1_MASK                  0x800u
#define FTM_COMBINE_DECAP1_SHIFT                 11
#define FTM_COMBINE_DTEN1_MASK                   0x1000u
#define FTM_COMBINE_DTEN1_SHIFT                  12
#define FTM_COMBINE_SYNCEN1_MASK                 0x2000u
#define FTM_COMBINE_SYNCEN1_SHIFT                13
#define FTM_COMBINE_FAULTEN1_MASK                0x4000u
#define FTM_COMBINE_FAULTEN1_SHIFT               14
#define FTM_COMBINE_COMBINE2_MASK                0x10000u
#define FTM_COMBINE_COMBINE2_SHIFT               16
#define FTM_COMBINE_COMP2_MASK                   0x20000u
#define FTM_COMBINE_COMP2_SHIFT                  17
#define FTM_COMBINE_DECAPEN2_MASK                0x40000u
#define FTM_COMBINE_DECAPEN2_SHIFT               18
#define FTM_COMBINE_DECAP2_MASK                  0x80000u
#define FTM_COMBINE_DECAP2_SHIFT                 19
#define FTM_COMBINE_DTEN2_MASK                   0x100000u
#define FTM_COMBINE_DTEN2_SHIFT                  20
#define FTM_COMBINE_SYNCEN2_MASK                 0x200000u
#define FTM_COMBINE_SYNCEN2_SHIFT                21
#define FTM_COMBINE_FAULTEN2_MASK                0x400000u
#define FTM_COMBINE_FAULTEN2_SHIFT               22
#define FTM_COMBINE_COMBINE3_MASK                0x1000000u
#define FTM_COMBINE_COMBINE3_SHIFT               24
#define FTM_COMBINE_COMP3_MASK                   0x2000000u
#define FTM_COMBINE_COMP3_SHIFT                  25
#define FTM_COMBINE_DECAPEN3_MASK                0x4000000u
#define FTM_COMBINE_DECAPEN3_SHIFT               26
#define FTM_COMBINE_DECAP3_MASK                  0x8000000u
#define FTM_COMBINE_DECAP3_SHIFT                 27
#define FTM_COMBINE_DTEN3_MASK                   0x10000000u
#define FTM_COMBINE_DTEN3_SHIFT                  28
#define FTM_COMBINE_SYNCEN3_MASK                 0x20000000u
#define FTM_COMBINE_SYNCEN3_SHIFT                29
#define FTM_COMBINE_FAULTEN3_MASK                0x40000000u
#define FTM_COMBINE_FAULTEN3_SHIFT               30

/* DEADTIME Bit Fields */
#define FTM_DEADTIME_DTVAL_MASK                  0x3Fu
#define FTM_DEADTIME_DTVAL_SHIFT                 0
#define FTM_DEADTIME_DTPS_MASK                   0xC0u
#define FTM_DEADTIME_DTPS_SHIFT                  6

/* EXTTRIG Bit Fields */
#define FTM_EXTTRIG_CH2TRIG_MASK                 0x1u
#define FTM_EXTTRIG_CH2TRIG_SHIFT                0
#define FTM_EXTTRIG_CH3TRIG_MASK                 0x2u
#define FTM_EXTTRIG_CH3TRIG_SHIFT                1
#define FTM_EXTTRIG_CH4TRIG_MASK                 0x4u
#define FTM_EXTTRIG_CH4TRIG_SHIFT                2
#define FTM_EXTTRIG_CH5TRIG_MASK                 0x8u
#define FTM_EXTTRIG_CH5TRIG_SHIFT                3
#define FTM_EXTTRIG_CH0TRIG_MASK                 0x10u
#define FTM_EXTTRIG_CH0TRIG_SHIFT                4
#define FTM_EXTTRIG_CH1TRIG_MASK                 0x20u
#define FTM_EXTTRIG_CH1TRIG_SHIFT                5
#define FTM_EXTTRIG_INITTRIGEN_MASK              0x40u
#define FTM_EXTTRIG_INITTRIGEN_SHIFT             6
#define FTM_EXTTRIG_TRIGF_MASK                   0x80u
#define FTM_EXTTRIG_TRIGF_SHIFT                  7

/* POL Bit Fields */
#define FTM_POL_POL0_MASK                        0x1u
#define FTM_POL_POL0_SHIFT                       0
#define FTM_POL_POL1_MASK                        0x2u
#define FTM_POL_POL1_SHIFT                       1
#define FTM_POL_POL2_MASK                        0x4u
#define FTM_POL_POL2_SHIFT                       2
#define FTM_POL_POL3_MASK                        0x8u
#define FTM_POL_POL3_SHIFT                       3
#define FTM_POL_POL4_MASK                        0x10u
#define FTM_POL_POL4_SHIFT                       4
#define FTM_POL_POL5_MASK                        0x20u
#define FTM_POL_POL5_SHIFT                       5
#define FTM_POL_POL6_MASK                        0x40u
#define FTM_POL_POL6_SHIFT                       6
#define FTM_POL_POL7_MASK                        0x80u
#define FTM_POL_POL7_SHIFT                       7

/* FMS Bit Fields */
#define FTM_FMS_FAULTF0_MASK                     0x1u
#define FTM_FMS_FAULTF0_SHIFT                    0
#define FTM_FMS_FAULTF1_MASK                     0x2u
#define FTM_FMS_FAULTF1_SHIFT                    1
#define FTM_FMS_FAULTF2_MASK                     0x4u
#define FTM_FMS_FAULTF2_SHIFT                    2
#define FTM_FMS_FAULTF3_MASK                     0x8u
#define FTM_FMS_FAULTF3_SHIFT                    3
#define FTM_FMS_FAULTIN_MASK                     0x20u
#define FTM_FMS_FAULTIN_SHIFT                    5
#define FTM_FMS_WPEN_MASK                        0x40u
#define FTM_FMS_WPEN_SHIFT                       6
#define FTM_FMS_FAULTF_MASK                      0x80u
#define FTM_FMS_FAULTF_SHIFT                     7

/* FILTER Bit Fields */
#define FTM_FILTER_CH0FVAL_MASK                  0xFu
#define FTM_FILTER_CH0FVAL_SHIFT                 0
#define FTM_FILTER_CH1FVAL_MASK                  0xF0u
#define FTM_FILTER_CH1FVAL_SHIFT                 4
#define FTM_FILTER_CH2FVAL_MASK                  0xF00u
#define FTM_FILTER_CH2FVAL_SHIFT                 8
#define FTM_FILTER_CH3FVAL_MASK                  0xF000u
#define FTM_FILTER_CH3FVAL_SHIFT                 12

/* FLTCTRL Bit Fields */
#define FTM_FLTCTRL_FAULT0EN_MASK                0x1u
#define FTM_FLTCTRL_FAULT0EN_SHIFT               0
#define FTM_FLTCTRL_FAULT1EN_MASK                0x2u
#define FTM_FLTCTRL_FAULT1EN_SHIFT               1
#define FTM_FLTCTRL_FAULT2EN_MASK                0x4u
#define FTM_FLTCTRL_FAULT2EN_SHIFT               2
#define FTM_FLTCTRL_FAULT3EN_MASK                0x8u
#define FTM_FLTCTRL_FAULT3EN_SHIFT               3
#define FTM_FLTCTRL_FFLTR0EN_MASK                0x10u
#define FTM_FLTCTRL_FFLTR0EN_SHIFT               4
#define FTM_FLTCTRL_FFLTR1EN_MASK                0x20u
#define FTM_FLTCTRL_FFLTR1EN_SHIFT               5
#define FTM_FLTCTRL_FFLTR2EN_MASK                0x40u
#define FTM_FLTCTRL_FFLTR2EN_SHIFT               6
#define FTM_FLTCTRL_FFLTR3EN_MASK                0x80u
#define FTM_FLTCTRL_FFLTR3EN_SHIFT               7
#define FTM_FLTCTRL_FFVAL_MASK                   0xF00u
#define FTM_FLTCTRL_FFVAL_SHIFT                  8

/* CONF Bit Fields */
#define FTM_CONF_NUMTOF_MASK                     0x1Fu
#define FTM_CONF_NUMTOF_SHIFT                    0
#define FTM_CONF_BDMMODE_MASK                    0xC0u
#define FTM_CONF_BDMMODE_SHIFT                   6
#define FTM_CONF_GTBEEN_MASK                     0x200u
#define FTM_CONF_GTBEEN_SHIFT                    9
#define FTM_CONF_GTBEOUT_MASK                    0x400u
#define FTM_CONF_GTBEOUT_SHIFT                   10

/* FLTPOL Bit Fields */
#define FTM_FLTPOL_FLT0POL_MASK                  0x1u
#define FTM_FLTPOL_FLT0POL_SHIFT                 0
#define FTM_FLTPOL_FLT1POL_MASK                  0x2u
#define FTM_FLTPOL_FLT1POL_SHIFT                 1
#define FTM_FLTPOL_FLT2POL_MASK                  0x4u
#define FTM_FLTPOL_FLT2POL_SHIFT                 2
#define FTM_FLTPOL_FLT3POL_MASK                  0x8u
#define FTM_FLTPOL_FLT3POL_SHIFT                 3

/* SYNCONF Bit Fields */
#define FTM_SYNCONF_HWTRIGMODE_MASK              0x1u
#define FTM_SYNCONF_HWTRIGMODE_SHIFT             0
#define FTM_SYNCONF_CNTINC_MASK                  0x4u
#define FTM_SYNCONF_CNTINC_SHIFT                 2
#define FTM_SYNCONF_INVC_MASK                    0x10u
#define FTM_SYNCONF_INVC_SHIFT                   4
#define FTM_SYNCONF_SWOC_MASK                    0x20u
#define FTM_SYNCONF_SWOC_SHIFT                   5
#define FTM_SYNCONF_SYNCMODE_MASK                0x80u
#define FTM_SYNCONF_SYNCMODE_SHIFT               7
#define FTM_SYNCONF_SWRSTCNT_MASK                0x100u
#define FTM_SYNCONF_SWRSTCNT_SHIFT               8
#define FTM_SYNCONF_SWWRBUF_MASK                 0x200u
#define FTM_SYNCONF_SWWRBUF_SHIFT                9
#define FTM_SYNCONF_SWOM_MASK                    0x400u
#define FTM_SYNCONF_SWOM_SHIFT                   10
#define FTM_SYNCONF_SWINVC_MASK                  0x800u
#define FTM_SYNCONF_SWINVC_SHIFT                 11
#define FTM_SYNCONF_SWSOC_MASK                   0x1000u
#define FTM_SYNCONF_SWSOC_SHIFT                  12
#define FTM_SYNCONF_HWRSTCNT_MASK                0x10000u
#define FTM_SYNCONF_HWRSTCNT_SHIFT               16
#define FTM_SYNCONF_HWWRBUF_MASK                 0x20000u
#define FTM_SYNCONF_HWWRBUF_SHIFT                17
#define FTM_SYNCONF_HWOM_MASK                    0x40000u
#define FTM_SYNCONF_HWOM_SHIFT                   18
#define FTM_SYNCONF_HWINVC_MASK                  0x80000u
#define FTM_SYNCONF_HWINVC_SHIFT                 19
#define FTM_SYNCONF_HWSOC_MASK                   0x100000u
#define FTM_SYNCONF_HWSOC_SHIFT                  20

/* INVCTRL Bit Fields */
#define FTM_INVCTRL_INV0EN_MASK                  0x1u
#define FTM_INVCTRL_INV0EN_SHIFT                 0
#define FTM_INVCTRL_INV1EN_MASK                  0x2u
#define FTM_INVCTRL_INV1EN_SHIFT                 1
#define FTM_INVCTRL_INV2EN_MASK                  0x4u
#define FTM_INVCTRL_INV2EN_SHIFT                 2
#define FTM_INVCTRL_INV3EN_MASK                  0x8u
#define FTM_INVCTRL_INV3EN_SHIFT                 3

/* SWOCTRL Bit Fields */
#define FTM_SWOCTRL_CH0OC_MASK                   0x1u
#define FTM_SWOCTRL_CH0OC_SHIFT                  0
#define FTM_SWOCTRL_CH1OC_MASK                   0x2u
#define FTM_SWOCTRL_CH1OC_SHIFT                  1
#define FTM_SWOCTRL_CH2OC_MASK                   0x4u
#define FTM_SWOCTRL_CH2OC_SHIFT                  2
#define FTM_SWOCTRL_CH3OC_MASK                   0x8u
#define FTM_SWOCTRL_CH3OC_SHIFT                  3
#define FTM_SWOCTRL_CH4OC_MASK                   0x10u
#define FTM_SWOCTRL_CH4OC_SHIFT                  4
#define FTM_SWOCTRL_CH5OC_MASK                   0x20u
#define FTM_SWOCTRL_CH5OC_SHIFT                  5
#define FTM_SWOCTRL_CH6OC_MASK                   0x40u
#define FTM_SWOCTRL_CH6OC_SHIFT                  6
#define FTM_SWOCTRL_CH7OC_MASK                   0x80u
#define FTM_SWOCTRL_CH7OC_SHIFT                  7
#define FTM_SWOCTRL_CH0OCV_MASK                  0x100u
#define FTM_SWOCTRL_CH0OCV_SHIFT                 8
#define FTM_SWOCTRL_CH1OCV_MASK                  0x200u
#define FTM_SWOCTRL_CH1OCV_SHIFT                 9
#define FTM_SWOCTRL_CH2OCV_MASK                  0x400u
#define FTM_SWOCTRL_CH2OCV_SHIFT                 10
#define FTM_SWOCTRL_CH3OCV_MASK                  0x800u
#define FTM_SWOCTRL_CH3OCV_SHIFT                 11
#define FTM_SWOCTRL_CH4OCV_MASK                  0x1000u
#define FTM_SWOCTRL_CH4OCV_SHIFT                 12
#define FTM_SWOCTRL_CH5OCV_MASK                  0x2000u
#define FTM_SWOCTRL_CH5OCV_SHIFT                 13
#define FTM_SWOCTRL_CH6OCV_MASK                  0x4000u
#define FTM_SWOCTRL_CH6OCV_SHIFT                 14
#define FTM_SWOCTRL_CH7OCV_MASK                  0x8000u
#define FTM_SWOCTRL_CH7OCV_SHIFT                 15

/* PWMLOAD Bit Fields */
#define FTM_PWMLOAD_CH0SEL_MASK                  0x1u
#define FTM_PWMLOAD_CH0SEL_SHIFT                 0
#define FTM_PWMLOAD_CH1SEL_MASK                  0x2u
#define FTM_PWMLOAD_CH1SEL_SHIFT                 1
#define FTM_PWMLOAD_CH2SEL_MASK                  0x4u
#define FTM_PWMLOAD_CH2SEL_SHIFT                 2
#define FTM_PWMLOAD_CH3SEL_MASK                  0x8u
#define FTM_PWMLOAD_CH3SEL_SHIFT                 3
#define FTM_PWMLOAD_CH4SEL_MASK                  0x10u
#define FTM_PWMLOAD_CH4SEL_SHIFT                 4
#define FTM_PWMLOAD_CH5SEL_MASK                  0x20u
#define FTM_PWMLOAD_CH5SEL_SHIFT                 5
#define FTM_PWMLOAD_CH6SEL_MASK                  0x40u
#define FTM_PWMLOAD_CH6SEL_SHIFT                 6
#define FTM_PWMLOAD_CH7SEL_MASK                  0x80u
#define FTM_PWMLOAD_CH7SEL_SHIFT                 7
#define FTM_PWMLOAD_LDOK_MASK                    0x200u
#define FTM_PWMLOAD_LDOK_SHIFT                   9

/** FTM - Register Layout Typedef */
typedef struct {
  __IO uint32_t SC;                                /*!< (1-306)22.3.1 状态和控制寄存器(SC), offset: 0x0 */
  __IO uint32_t CNT;                               /*!< (1-308)22.3.2 计数器寄存器(CNT), offset: 0x4 */
  __IO uint32_t MOD;                               /*!< (1-308)22.3.3 模数寄存器(FTMx_MOD), offset: 0x8 */
  struct {                                       
    __IO uint32_t CnSC;                            /*!< 通道状态和控制寄存器, array offset: 0xC, array step: 0x8 */
    __IO uint32_t CnV;                             /*!< 通道值寄存器, array offset: 0x10, array step: 0x8 */
  } CONTROLS[8];
  __IO uint32_t CNTIN;                             /*!< (1-313)22.3.6 计数器初始值寄存器(CNTIN), offset: 0x4C */
  __IO uint32_t STATUS;                            /*!< 捕捉和比较状态寄存器, offset: 0x50 */
  __IO uint32_t MODE;                              /*!< (1-316)22.3.8 特性模式选择寄存器(MODE), offset: 0x54 */
  __IO uint32_t SYNC;                              /*!< 同步寄存器, offset: 0x58 */
  __IO uint32_t OUTINIT;                           /*!< 通道输出的初始状态寄存器, offset: 0x5C */
  __IO uint32_t OUTMASK;                           /*!< 输出屏蔽寄存器, offset: 0x60 */
  __IO uint32_t COMBINE;                           /*!< 已连接信道功能寄存器, offset: 0x64 */
  __IO uint32_t DEADTIME;                          /*!< 死区时间插入控制, offset: 0x68 */
  __IO uint32_t EXTTRIG;                           /*!< FTM外部触发寄存器, offset: 0x6C */
  __IO uint32_t POL;                               /*!< 通道极性寄存器, offset: 0x70 */
  __IO uint32_t FMS;                               /*!< 故障模式状态寄存器, offset: 0x74 */
  __IO uint32_t FILTER;                            /*!< 输入捕捉滤波器控制寄存器, offset: 0x78 */
  __IO uint32_t FLTCTRL;                           /*!< 故障控制寄存器, offset: 0x7C */
       uint8_t RESERVED_1[4];
  __IO uint32_t CONF;                              /*!< 配置寄存器, offset: 0x84 */
  __IO uint32_t FLTPOL;                            /*!< FTM 故障输入极性寄存器, offset: 0x88 */
  __IO uint32_t SYNCONF;                           /*!< FTM 软件输出控制寄存器, offset: 0x8C */
  __IO uint32_t INVCTRL;                           /*!< FTM 软件输出控制寄存器, offset: 0x90 */
  __IO uint32_t SWOCTRL;                           /*!< FTM 软件输出控制寄存器, offset: 0x94 */
  __IO uint32_t PWMLOAD;                           /*!< FTM PWM 加载寄存器, offset: 0x98 */
} FTM_Type, *FTM_MemMapPtr;	
extern FTM_Type*		FTM0;
extern FTM_Type*		FTM1;
extern FTM_Type*		FTM2;


/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup FTM
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/**
  * @brief FTM 时钟初始化结构体
  */
typedef struct
{
  uint32_t   FTM_ClkSource;        /*!< 时钟源 */
  uint32_t   FTM_Prescaler;        /*!< 时钟预分频系数 */
	
}FTM_InitTypeDef, *FTM_InitConfigPtr;

/**
  * @brief FTM 组合模式初始化结构体定义
  */
typedef struct
{
	uint32_t		FTM_ChannelPair;                /*!< 通道对 */
	uint32_t		PWMEdgeSelect;                  /*!< PWM边沿选择 */                            
	uint32_t		FTM_CombineEn;                  /*!< 组合通道使能 */	
	uint32_t		FTM_CompEn;                     /*!< 通道互补使能 */	
	uint32_t		FTM_DeadtimeEn;                 /*!< 死区时间使能 */
	uint32_t		FTM_SynchronizationEn;          /*!< 使能寄存器C(n)V 和C(n+1)V的PWM同步 */
	uint32_t		FTM_FaultControlEn;             /*!< 故障控制使能 */
	
}FTM_CombinePWMTypeDef, *FTM_CombinePWMConfigPtr;
  
/**
  * @brief FTM 比较功能初始化结构体
  */
typedef struct
{
	uint32_t FTM_ChannelPair;                /*!< 通道对 */                                               
	uint32_t FTM_CaptureMode;                /*!< 捕获模式: 单次捕获和连续 */	
	uint32_t FTM_Channel_N_Edge;             /*!< 通道N边沿检测 */	
	uint32_t FTM_Channel_Np1_Edge;           /*!< 通道N+1边沿检测 */
	
}FTM_DualEdgeCaptureTypeDef, *FTM_DualEdgeCaptureConfigPtr;



/* Exported constants --------------------------------------------------------*/
/** @defgroup FTM_Exported_Constants FTM模块使用参数定义
  * @{
  */	

/** @defgroup FTM_Deinit_Value FTM寄存器默认值
  * @{
  */
#define FTM_MOD_INIT	                ((uint32_t)20000-(uint32_t)1)              /*!< MOD inite value */
#define FTM_C0V_INIT	                (uint32_t)1000                  /*!< C0V inite value */
#define FTM_C1V_INIT	                (uint32_t)1000                  /*!< C1V inite value */
#define FTM_C2V_INIT	                (uint32_t)1000                  /*!< C2V inite value */    
#define FTM_C3V_INIT	                (uint32_t)1000                  /*!< C3V inite value */
#define FTM_C4V_INIT	                (uint32_t)1000                  /*!< C4V inite value */
#define FTM_C5V_INIT	                (uint32_t)1000                  /*!< C5V inite value */
#define FTM_C6V_INIT	                (uint32_t)1000                  /*!< C6V inite value */
#define FTM_C7V_INIT	                (uint32_t)1000                  /*!< C7V inite value */
/**
  * @}
  */	
	
/** @defgroup FTM_Clocksource_Seclect FTM时钟源选择定义
  * @{
  */	
#define FTM_CLOCK_NOCLOCK                		0              /*!< 未选定时钟，该设置生效后可禁用FTM计数器 */
#define FTM_CLOCK_SYSTEMCLOCK            		1              /*!< System clock */
#define FTM_CLOCK_FIXEDFREQCLOCK        		2              /*!< Fixed Freq Clock */
#define FTM_CLOCK_EXTERNALCLOCK          		3              /*!< External Clock */
/**
  * @}
  */
	
/** @defgroup FTM_Clockprescale_Seclect FTM时钟分频选择定义
  * @{
  */	
#define FTM_CLOCK_PS_DIV1                		0              /*!< 1分频 */
#define FTM_CLOCK_PS_DIV2                		1              /*!< 2分频 */
#define FTM_CLOCK_PS_DIV4                		2              /*!< 4分频 */
#define FTM_CLOCK_PS_DIV8                		3              /*!< 8分频 */
#define FTM_CLOCK_PS_DIV16               		4              /*!< 16分频 */
#define FTM_CLOCK_PS_DIV32               		5              /*!< 32分频 */
#define FTM_CLOCK_PS_DIV64               		6              /*!< 64分频 */
#define FTM_CLOCK_PS_DIV128              		7              /*!< 128分频 */
/**
  * @}
  */
   
/** @defgroup FTM_Deadtime_Clockprescale_Seclect FTM死区时间时钟分频选择定义
  * @{
  */	
#define FTM_DEADTIME_DTPS_DIV1           		0               /*!< 1分频 */
#define FTM_DEADTIME_DTPS_DIV4           		2               /*!< 4分频 */
#define FTM_DEADTIME_DTPS_DIV16          		3               /*!< 16分频 */
/**
  * @}
  */
	
/** @defgroup FTM_Channels_Modes_Definition FTM通道模式定义
  * @{
  */
#define FTM_PWMMODE_EDGEALLIGNED						(uint8_t)1            /*!< 边沿对齐PWM */
#define FTM_PWMMODE_CENTERALLIGNED						(uint8_t)2          /*!< 中心对齐PWM */
#define FTM_PWMMODE_COMBINE								(uint8_t)3		          /*!< 组合PWM */
/**
  * @}
  */
	
/** @defgroup FTM_PWM_High/Low_TruePulse FTM_PWM高/低真实脉冲

  * @{
  */	
#define FTM_PWM_HIGHTRUEPULSE            		2u           /*!< 高真脉冲（通道(n)匹配时置位，通道(n+1)匹配时清零） */
#define FTM_PWM_LOWTRUEPULSE             		1u           /*!< 低真脉冲（通道(n)匹配时清零，通道(n+1)匹配时置位 */
/**
  * @}
  */

/** @defgroup FTM_InputcaptureEdge_Seclect FTM输入捕获边沿类型选择
  * @{
  */
#define FTM_INPUTCAPTURE_RISINGEDGE          1u     /*!< 上升沿 */
#define FTM_INPUTCAPTURE_FALLINGEDGE         2u     /*!< 下降沿 */
#define FTM_INPUTCAPTURE_BOTHEDGE            3u     /*!< 双边沿 */
/**
  * @}
  */

/** @defgroup FTM_InputcaptureDualEdge_Seclect  FTM输入捕获双边沿类型选择
  * @{
  */																
#define FTM_INPUTCAPTURE_DUALEDGE_NOEDGE      0u     /*!< 无边沿 */
#define FTM_INPUTCAPTURE_DUALEDGE_RISING      1u     /*!< 上升沿 */
#define FTM_INPUTCAPTURE_DUALEDGE_FALLING     2u     /*!< 下降沿 */
#define FTM_INPUTCAPTURE_DUALEDGE_BOTHEDGE    3u     /*!< 双边沿 */
/**
  * @}
  */
	
/** @defgroup FTM_DualCapture_Mode FTM双比较模式
  * @{
  */	
#define FTM_INPUTCAPTURE_DUALEDGE_ONESHOT     2u     /*!< 单次捕获模式 */ 
#define FTM_INPUTCAPTURE_DUALEDGE_CONTINUOUS  1u     /*!< 连续捕获模式 */
/**
  * @}
  */
	
/** @defgroup FTM_OutCompare_Mode FTM输出比较模式
  * @{
  */		
#define FTM_OUTPUT_TOGGLE                		1u           /*!< 匹配时切换输出 */
#define FTM_OUTPUT_CLEAR                		2u           /*!< 匹配时清零输出 */
#define FTM_OUTPUT_SET                   		3u           /*!< 匹配时置位输出 */
/**
  * @}
  */
	
	
/** @defgroup FTM_SYNC_TRIGGER_List FTM同步触发功能列表
  * @{
  */	
#define FTM_SYNC_TRIGGER_TRIGGER0         	0x10         /*!< 同步硬件触发0 */
#define FTM_SYNC_TRIGGER_TRIGGER1         	0x20         /*!< 同步硬件触发1 */
#define FTM_SYNC_TRIGGER_TRIGGER2         	0x40         /*!< 同步硬件触发2 */
/**
  * @}
  */
	
/** @defgroup FTM_Update_SYNC_TRIGGER_List FTM更新同步触发功能列表
  * @{
  */	
#define FTM_UPDATE_RISINGCLK              	0u         /*!< 寄存器将在所有SYSCLK的上升沿以其缓冲区的数值进行更新 */
#define FTM_UPDATE_PWMSYNC                	1u         /*!< 寄存器仅通过PWM 同步以其缓冲区值进行更新 */
/**
  * @}
  */
	
/** @defgroup FTM_Synchronization_Mode_list FTM同步模式
  * @{
  */	
#define FTM_SYNCMODE_LEGACY               	0u         /*!< 选择传统PWM同步 */
#define FTM_SYNCMODE_ENHANCED             	1u         /*!< 选择增强PWM同步 */
/**
  * @}
  */ 


/** @defgroup FTM_PWM_Synchronization_Mode_list FTM_PWM软硬件触发模式选择
  * @{
  */	
#define FTM_PWMSYNC_NORESTRICT            	0u         /*!< 无限制，选择可用于MOD、CnV、OUTMASK 和FTM 计数器同步的软件和硬件触发 */
#define FTM_PWMSYNC_SWANDHW               	1u         /*!< 软件触发只能用于MOD 和CnV 同步，硬件触发只能用于FTM计数器同步 */
/**
  * @}
  */ 
	
/** @defgroup FTM_Hardware_Trigger_Mode_list FTM硬件触发模式屏蔽
  * @{
  */	
#define FTM_HWTRIGMODE_CLEAR              	0u         /*!< 检测到硬件触发j时（j=0、1、2），FTM清零TRIGj位 */
#define FTM_HWTRIGMODE_UNCLEAR            	1u         /*!< 检测到硬件触发j时（j=0、1、2），FTM不清零TRIGj位 */
/**
  * @}
  */

/** @defgroup FTM_Synconf_Reg_List FTM同步
  * @{
  */	
#define FTM_SYNCONF_CNTREG                	0u         /*!< FTM同步计数器 */
#define FTM_SYNCONF_MODCNTINCVREG        	1u           /*!< MOD, CNTIN,和CV同步寄存器 */
#define FTM_SYNCONF_OUTMASKREG            	2u         /*!< 同步输出屏蔽 */
#define FTM_SYNCONF_INVCTRLREG            	3u         /*!< INVCTRL寄存器同步 */
#define FTM_SYNCONF_SWOCTRLREG            	4u         /*!< SWOCTRL寄存器同步 */
/**
  * @}
  */

/** @defgroup FTM_Synchronization_Mode_Seclect FTM同步模式触发选择
  * @{
  */	
#define FTM_SYNCONF_SWTRIGGER             	0u         /*!< 同步软件触发 */
#define FTM_SYNCONF_HWTRIGGER             	1u         /*!< 同步硬件触发 */
/**
  * @}
  */
	
/** @defgroup FTM_Reinitialization_List FTM更新输出值
  * @{
  */
#define FTM_REINIT_NORMALLY              		0u         /*!< FTM计数器继续正常计数 */
#define FTM_REINIT_UPDATED               		1u         /*!< FTM计数器以其初始值更新 */
/**
  * @}
  */
	
/** @defgroup FTM_Channel_List FTM通道列表
  * @{
  */
#define FTM_CHANNEL0                     0u           /*!< FTMx通道0 */
#define FTM_CHANNEL1                     1u           /*!< FTMx通道1 */
#define FTM_CHANNEL2                     2u           /*!< FTMx通道2 */
#define FTM_CHANNEL3                     3u           /*!< FTMx通道3 */
#define FTM_CHANNEL4                     4u           /*!< FTMx通道4 */
#define FTM_CHANNEL5                     5u           /*!< FTMx通道5 */
#define FTM_CHANNEL6                     6u           /*!< FTMx通道6 */
#define FTM_CHANNEL7                     7u           /*!< FTMx通道7 */
/**
  * @}
  */

/** @defgroup FTM_ChannelPair_List FTM组合模式通道列表
  * @{
  */	
#define FTM_CHANNELPAIR0                 0u           /*!< 通道对0:ch0 & ch1 */
#define FTM_CHANNELPAIR1                 2u           /*!< 通道对1:ch2 & ch3 */
#define FTM_CHANNELPAIR2                 4u           /*!< 通道对2:ch4 & ch5 */
#define FTM_CHANNELPAIR3                 6u           /*!< 通道对3:ch6 & ch7 */
/**
  * @}
  */

/** @defgroup FTM_ChannelFlag_List FTM通道标志列表
  * @{
  */
#define FTM_CHANNEL0_FLAG                0u           /*!< FTM通道标志0 */
#define FTM_CHANNEL1_FLAG                1u           /*!< FTM通道标志1 */
#define FTM_CHANNEL2_FLAG                2u           /*!< FTM通道标志2 */
#define FTM_CHANNEL3_FLAG                3u           /*!< FTM通道标志3 */
#define FTM_CHANNEL4_FLAG                4u           /*!< FTM通道标志4 */
#define FTM_CHANNEL5_FLAG                5u           /*!< FTM通道标志5 */
#define FTM_CHANNEL6_FLAG                6u           /*!< FTM通道标志6 */
#define FTM_CHANNEL7_FLAG                7u           /*!< FTM通道标志7 */
/**
  * @}
  */

/** @defgroup FTM_IntialValue_list FTM初始值列表
  * @{
  */
#define FTM_INITIALVALUE0                		0u          /*!< FTM初始值0 */
#define FTM_INITIALVALUE1                		1u          /*!< FTM初始值1 */
/**
  * @}
  */
	
/** @defgroup FTM_ChannelPolarity_List FTM通道极性列表
  * @{
  */
#define FTM_CHANNELPOLARITY_HIGH         		0u          /*!< FTM通道极性为高电平 */
#define FTM_CHANNELPOLARITY_LOW          		1u          /*!< FTM通道极性为低电平 */
/**
  * @}
  */
	
/** @defgroup FTM_FaultDetectionFlag_List FTM通道错误标志列表
  * @{
  */
#define FTM_FAULTDETECTION_FLAG0         		0u          /*!< 故障检测标志0 */
#define FTM_FAULTDETECTION_FLAG1         		1u          /*!< 故障检测标志1 */
#define FTM_FAULTDETECTION_FLAG2				2u          /*!< 故障检测标志2 */
#define FTM_FAULTDETECTION_FLAG3         		3u          /*!< 故障检测标志3 */
/**
  * @}
  */
	

/** @defgroup FaultControlChanne_List FTM故障控制通道列表
  * @{
  */
#define FaultControlChanne0         		0x00000040u          /*!< 故障控制通道0 */
#define FaultControlChanne1         		0x00004000u          /*!< 故障控制通道1 */
#define FaultControlChanne2					0x00400000u          /*!< 故障控制通道2 */
#define FaultControlChanne3         		0x40000000u          /*!< 故障控制通道3 */
/**
  * @}
  */
	


	
/** @defgroup FTM_InputFilterChannel_List FTM输入滤波通道列表
  * @{
  */
#define FTM_INPUTFILTER_CHANNEL0         		0u          /*!< 通道0输入滤波 */
#define FTM_INPUTFILTER_CHANNEL1         		1u          /*!< 通道1输入滤波 */
#define FTM_INPUTFILTER_CHANNEL2         		2u          /*!< 通道2输入滤波 */
#define FTM_INPUTFILTER_CHANNEL3         		3u          /*!< 通道3输入滤波 */
/**
  * @}
  */
	
/** @defgroup FTM_FaultInput_List FTM故障输入列表
  * @{
  */
#define FTM_FAULT_INPUT0                 		0u          /*!< 故障输入0  */
#define FTM_FAULT_INPUT1                 		1u          /*!< 故障输入1  */
#define FTM_FAULT_INPUT2                 		2u          /*!< 故障输入2  */
#define FTM_FAULT_INPUT3                 		3u          /*!< 故障输入3  */
/**
  * @}
  */
	
/** @defgroup FTM_FaultInputFilter_List FTM故障滤波输入列表
  * @{
  */
#define FTM_FAULTINPUT_FILTER0           		0u          /*!< 故障滤波输入0       */   
#define FTM_FAULTINPUT_FILTER1           		1u          /*!< 故障滤波输入1       */ 
#define FTM_FAULTINPUT_FILTER2           		2u          /*!< 故障滤波输入2       */ 
#define FTM_FAULTINPUT_FILTER3           		3u          /*!< 故障滤波输入3       */ 
/**
  * @}
  */
	
/** @defgroup FTM_FaultPolarityFilter_List FTM故障滤波输入列表
  * @{
  */
#define FTM_FAULTINPOLARITY_HIGH         		0u          /*!< 故障输入极性为高         */
#define FTM_FAULTINPOLARITY_LOW          		1u          /*!< 故障输入极性为低         */
/**
  * @}
  */
	
/** @defgroup FTM_invert_pair_channel_list FTM通道反转
  * @{
  */
#define FTM_INVERT_PAIRCHANNEL0          		0u          /*!< 通道对0反转使能        */
#define FTM_INVERT_PAIRCHANNEL1         		1u          /*!< 通道对1反转使能        */
#define FTM_INVERT_PAIRCHANNEL2          		2u          /*!< 通道对2反转使能        */
#define FTM_INVERT_PAIRCHANNEL3          		3u          /*!< 通道对3反转使能        */
/**
  * @}
  */

/** @defgroup FTM_Software_Control_Outvalue_list FTM软件控制输出值列表
  * @{
  */
#define FTM_SWCONTROL_OUT0               		0u          /*!< FTM软件控制输出值强制为0 */
#define FTM_SWCONTROL_OUT1               		1u          /*!< FTM软件控制输出值强制为1 */
/**
  * @}
  */
	
/** @defgroup FTM_ChannelMatch_list FTM通道匹配控制列表
  * @{
  */
#define FTM_CHANNELMATCH_NOTINCLUDE       	0u          /*!< 匹配过程中不包括通道 */
#define FTM_CHANNELMATCH_INCLUDE          	1u          /*!< 匹配过程中包括通道 */
/**
  * @}
  */
	
/** @defgroup FTM_Software_Sync_Activate FTM软件同步触发功能
  * @{
  */	
#define FTM_SOFTWARE_SYN_CNT 							FTM_SYNCONF_SWRSTCNT_MASK
#define FTM_SOFTWARE_SYN_MOD_CNTIN_CV					FTM_SYNCONF_SWWRBUF_MASK 
#define FTM_SOFTWARE_SYN_OUTMASK						FTM_SYNCONF_SWOM_MASK
#define FTM_SOFTWARE_SYN_INVCTRL						FTM_SYNCONF_SWINVC_MASK
#define FTM_SOFTWARE_SYN_OUTCTRL						FTM_SYNCONF_SWSOC_MASK
/**
  * @}
  */
	
/** @defgroup FTM_Shardware_Sync_Activate FTM硬件同步触发功能
  * @{
  */
#define FTM_HARDWARE_SYN_CNT							FTM_SYNCONF_HWRSTCNT_MASK
#define FTM_HARDWARE_SYN_MOD_CNTIN_CV					FTM_SYNCONF_HWWRBUF_MASK
#define FTM_HARDWARE_SYN_OUTMASK						FTM_SYNCONF_HWOM_MASK
#define FTM_HARDWARE_SYN_INVCTRL						FTM_SYNCONF_HWINVC_MASK
#define FTM_HARDWARE_SYN_OUTCTRL						FTM_SYNCONF_HWSOC_MASK 
/**
  * @}
  */


/** @defgroup FTM Interrupt Enable FTM中断使能
  * @{
  */
typedef enum {
	FTM_ALLDISABLE= 0,                      /*!< 所有通道禁用故障控制 */
	FTM_EVENENABLE_MANUALCLEAR,             /*!< 仅针对偶数信道（信道0、2、4 和6）使能故障控制，所选模式为手动故障清零 */
	FTM_ALLENABLE_MANUALCLEAR,              /*!< 所有通道使能故障控制，所选模式为手动故障清零 */
	FTM_ALLENABLE_AUTOCLEAR                 /*!< 所有通道使能故障控制，所选模式为自动故障清零 */

} FTM_FaultControlModeDef;
/**
  * @}
  */

/**
	* @}
	*/


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void FTM_WriteProtectEnable(FTM_Type* FTMx);
void FTM_WriteProtectDisable(FTM_Type* FTMx);
void FTM_DeInit(FTM_Type* FTMx);
void FTM_Init(FTM_Type* FTMx, const FTM_InitTypeDef* FTM_InitStruct);

void FTM_EdgeAlignedPWMInit(FTM_Type* FTMx, uint8_t FTM_Channel, uint8_t PWMEdgeSelect);
void FTM_CenterAlignedPWMInit(FTM_Type* FTMx, uint8_t FTM_Channel, uint8_t PWMEdgeSelect);
void FTM_CombinePWMPWMInit(FTM_Type* FTMx, const FTM_CombinePWMTypeDef *FTM_CombinePWMStruct);
void FTM_PWMInit(FTM_Type* FTMx, uint8_t PWMModeSelect, uint8_t PWMEdgeSelect);

void FTM_InputCaptureInit(FTM_Type* FTMx, uint8_t FTM_Channel, uint8_t CaptureMode);
void FTM_DualEdgeCaptureInit(FTM_Type* FTMx, const FTM_DualEdgeCaptureTypeDef* FTM_DualEdgeStruct);
void FTM_OutputCompareInit(FTM_Type* FTMx, uint8_t FTM_Channel, uint32_t CompareMode);

void FTM_OverflowITCmd(FTM_Type* FTMx, FunctionalState NewState);
FlagStatus FTM_GetOverFlowFlag(const FTM_Type* FTMx);
void FTM_ClrOverFlowFlag(FTM_Type* FTMx);

uint16_t FTM_GetCountValue(const FTM_Type* FTMx);
void FTM_SetModValue(FTM_Type* FTMx, uint16_t ModValue);
void FTM_SetCountInitValue(FTM_Type* FTMx, uint16_t InitialValue);

void FTM_ChannelIntCmd(FTM_Type* FTMx, uint8_t FTM_Channel, FunctionalState NewState);
FlagStatus FTM_GetChannelFlag(const FTM_Type* FTMx, uint8_t FTM_Channel);
void FTM_ClrChannelFlag(FTM_Type* FTMx, uint8_t FTM_Channel);
void FTM_SetChannelValue(FTM_Type* FTMx, uint8_t FTM_Channel, uint16_t ChannelValue);
uint16_t FTM_GetChannelValue(const FTM_Type* FTMx, uint8_t FTM_Channel );

uint32_t FTM_GetStatusRegFlag(const FTM_Type* FTMx);
void FTM_ClrStatusRegFlag(FTM_Type* FTMx);
FlagStatus FTM_GetStatusChannelFlag(const FTM_Type* FTMx, uint8_t ChannelFlag);
void FTM_ClrStatusChannelFlag(FTM_Type* FTMx, uint8_t ChannelFlag);

void FTM_FaultITCmd(FTM_Type* FTMx, FunctionalState NewState);
void FTM_SetFaultControlMode(FTM_Type* FTMx, FTM_FaultControlModeDef FTM_FaultControlMode);
void FTM_CaptureTestCmd(FTM_Type* FTMx, FunctionalState NewState);

void FTM_SoftwareSync(FTM_Type* FTMx, FunctionalState NewState);
void FTM_HardwareSync(FTM_Type* FTMx, uint8_t TriggerN, FunctionalState NewState);
void FTM_RegSyncCmd(FTM_Type* FTMx, uint8_t TriggerType, uint8_t RegType, FunctionalState NewState);
void FTM_OutMaskSync(FTM_Type* FTMx,  uint8_t update);
void FTM_CNTINCSync(FTM_Type* FTMx,  uint8_t update);
void FTM_INVCSync(FTM_Type* FTMx,  uint8_t update);
void FTM_SWOCSync(FTM_Type* FTMx,  uint8_t update);
void FTM_SetSyncMode(FTM_Type* FTMx,  uint8_t mode);
void FTM_SetPWMSyncMode(FTM_Type* FTMx,  uint8_t mode);
void FTM_SetHardwareTriggerMode(FTM_Type* FTMx,  uint8_t mode);

void FTM_CNTMAXCmd(FTM_Type* FTMx, FunctionalState NewState);
void FTM_CNTMINCmd(FTM_Type* FTMx, FunctionalState NewState);
void FTM_Reinitialization(FTM_Type* FTMx,  uint8_t mode);

void FTM_SetInitOut(FTM_Type* FTMx, uint8_t initialvalue);
void FTM_SetChannelOutInitValue(FTM_Type* FTMx,uint8_t FTM_Channel, uint8_t initialvalue);

void FTM_SetOutMask(FTM_Type* FTMx, uint8_t outmask);
void FTM_SetChannelOutMaskCmd(FTM_Type* FTMx, uint8_t FTM_Channel, FunctionalState NewState);

void FTM_PWMDeadtimeSet(FTM_Type* FTMx, uint32_t PrescalerValue, uint32_t DeadtimeValue);

FlagStatus FTM_GetExternalTriggerFlag(const FTM_Type* FTMx);
void FTM_ClrExternalTriggerFlag(FTM_Type* FTMx);
void FTM_SetChnTriggerCmd(FTM_Type* FTMx, uint8_t FTM_Channel, FunctionalState NewState);
void FTM_SetInitTriggerCmd(FTM_Type* FTMx, FunctionalState NewState);

void FTM_SetChannelsPolarity(FTM_Type* FTMx, uint8_t PolarityValue);
void FTM_SetSingleChannelPolarity(FTM_Type* FTMx, uint8_t FTM_Channel, uint8_t FTM_Polarity);

FlagStatus FTM_GetFaultDetectLogicORFlag(const FTM_Type* FTMx);
FlagStatus FTM_GetFaultDetectFlag(const FTM_Type* FTMx, uint8_t FaultDetectFlag);
uint32_t FTM_GetFaultInLogicORValue(const FTM_Type* FTMx);
void FTM_ClrFaultDetectLogicORFlag(FTM_Type* FTMx);
void FTM_ClrFaultDetectFlag(FTM_Type* FTMx, uint8_t FaultDetectFlag);

void FTM_SetChannelInFilter(FTM_Type* FTMx, uint8_t FTM_FilterChannel, uint32_t FilterValue);
void FTM_SetInCapFilter(FTM_Type* FTMx, uint16_t filter);

void FTM_FaultPinCmd(FTM_Type* FTMx, uint8_t FaultInput, FunctionalState NewState);
void FTM_FaultPinFilterCmd(FTM_Type* FTMx, uint8_t FaultFilter, FunctionalState NewState);
void FTM_SetFaultInFilter(FTM_Type* FTMx, uint32_t FilterValue);

void FTM_GTBEENCmd(FTM_Type* FTMx, FunctionalState NewState);
void FTM_GTBEOUTCmd(FTM_Type* FTMx, FunctionalState NewState);
void FTM_SetDebugModeBehavior(FTM_Type* FTMx, uint32_t DebugMode);

void FTM_SetFaultInPolarity(FTM_Type* FTMx, uint8_t FaultInput, uint8_t polarity);

void FTM_PairChannelsInvertCmd(FTM_Type* FTMx, uint8_t channelpair, FunctionalState NewState);

void FTM_SWOutControlCmd(FTM_Type* FTMx, uint8_t FTM_Channel, FunctionalState NewState);
void FTM_SetSWOutControlValue(FTM_Type* FTMx, uint8_t FTM_Channel, uint8_t outvalue);

void FTM_SetLoadMatchChannels(FTM_Type* FTMx, uint32_t Matchchannel);
void FTM_SetLoadMatchChannel(FTM_Type* FTMx, uint8_t FTM_Channel, uint8_t include);
void FTM_SetLoadCmd(FTM_Type* FTMx, FunctionalState NewState);


void FTM_CVSyncEnable(FTM_Type* FTMx,uint8_t FTM_Channel,FunctionalState State);

void FTM_SoftSyncActivateTypeEnable(FTM_Type* FTMx,  uint32_t type, FunctionalState NewState);
void FTM_HardSyncActivateTypeEnable(FTM_Type* FTMx,  uint32_t type, FunctionalState NewState);

void FTM_SyncLoadEnable(FTM_Type* FTMx, FunctionalState NewState);
void FTM_FaultControlEnable(FTM_Type* FTMx, uint32_t FaultControlChannel,FunctionalState NewState);
#ifdef __cplusplus
}
#endif

#endif    /*__XL_FTM_H__ */
/**
  * @}
  */

/**
  * @}
  */

