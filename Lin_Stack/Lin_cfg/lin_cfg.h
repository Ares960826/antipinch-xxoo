/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2020-2021 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      lin_cfg.h 
* 
* @author    FPT Software
*  
* @version   1.0 
*  
* @date      Mon Sep 06 17:32:54 CST 2021
*  
* @brief     Hardware configuration file
* 
******************************************************************************/
#ifndef    _LIN_CFG_H_  
#define    _LIN_CFG_H_  
#include "lin_hw_cfg.h" 
/* Define operating mode */
#define _MASTER_MODE_     0 
#define _SLAVE_MODE_      1 
#define LIN_MODE   _SLAVE_MODE_
/* Define protocol version */
#define PROTOCOL_21       0  
#define PROTOCOL_J2602    1  
#define PROTOCOL_20       2 
#define LIN_PROTOCOL    PROTOCOL_21

#define UART_ADDR        UART0_ADDR    /* For slave */ 


#define LIN_BAUD_RATE    19200    	 /*For slave*/ 
/**********************************************************************/
/***************          Diagnostic class selection  *****************/
/**********************************************************************/
#define _DIAG_CLASS_I_          0
#define _DIAG_CLASS_II_         1
#define _DIAG_CLASS_III_        2

#define _DIAG_CLASS_SUPPORT_    _DIAG_CLASS_III_
/**************** FRAME SUPPORT DEFINITION ******************/
#define _TL_SINGLE_FRAME_       0
#define _TL_MULTI_FRAME_        1

#define _TL_FRAME_SUPPORT_      _TL_MULTI_FRAME_
/*************** DIAGNOSTIC SERVICES INDEX  ************/
#define DIAGSRV_READ_DATA_BY_IDENTIFIER_ORDER       0   /**< Diagnostic service: read data by identifier */
#define DIAGSRV_WRITE_DATA_BY_IDENTIFIER_ORDER      1   /**< Diagnostic service: write data by identifier */
#define DIAGSRV_SESSION_CONTROL_ORDER               2   /**< Diagnostic service: session control */
#define DIAGSRV_IO_CONTROL_BY_IDENTIFIER_ORDER      3   /**< Diagnostic service: I/O control by identifier */
#define DIAGSRV_FAULT_MEMORY_READ_ORDER             4   /**< Diagnostic service: read and clear DTC (fault memory) */
#define DIAGSRV_FAULT_MEMORY_CLEAR_ORDER            5   /**< Diagnostic service: fault memory clear */
#define DIAGSRV_ECU_RESET_ORDER                     6   /**< Diagnostic service: EcuReset */
#define DIAGSRV_TESTER_PRESENT_ORDER                7   /**< Diagnostic service: Tester Present */
#define DIAGSRV_ROUTINE_CONTROL_ORDER               8   /**< Diagnostic service: Routine Control */
/*Diagnostic class III */
#define _DIAG_NUMBER_OF_SERVICES_     9           /**< Number of diagnostic services class II and class III */
/* frame buffer size */
#define LIN_FRAME_BUF_SIZE			16
#define LIN_FLAG_BUF_SIZE			6

/**********************************************************************/
/***************               Interfaces           *******************/
/**********************************************************************/
typedef enum { 
   LI0
}l_ifc_handle; 

/**********************************************************************/
/***************               Signals              *******************/
/**********************************************************************/
/* Number of signals */
#define LIN_NUM_OF_SIGS  14
/* List of signals */   
typedef enum {

   /* Interface_name = LI0 */

   LI0_BCMSysPwrMd_lL1

   , LI0_DrvrPWLHiEftCndA_l
  
   , LI0_DrvrPWLNotNormd_l
  
   , LI0_DrvrPWLOpEnb_l
  
   , LI0_DrvrPWLRelayFltDetc_l
  
   , LI0_DrvrPWLRevsng_l
  
   , LI0_DrvrPWLSnsngSysFltDetc_l
  
   , LI0_DrvrPWLThrmlProtnA_l
  
   , LI0_DrvrWndDclnSpc_l
  
   , LI0_DrvrWndLclSwDsbld_l
  
   , LI0_DrvrWndLclSwSts_l
  
   , LI0_DrvrWndOpReq_l
  
   , LI0_DrvrWndShrtMvReq_l
  
   , LI0_PWL1RespEr_l
  
  
} l_signal_handle; 
/**********************************************************************/
/*****************               Frame             ********************/
/**********************************************************************/
/* Number of frames */
#define LIN_NUM_OF_FRMS  4 
/* List of frames */
typedef enum {
/* All frames for master node */

   /* Interface_name = LI0 */

   LI0_BCM_LIN1_FrP00

   , LI0_PWL1_LIN1_FrP00
  
   , LI0_MasterReq
  
   , LI0_SlaveResp
  
  
} l_frame_handle; 
 
/**********************************************************************/
/***************             Configuration          *******************/
/**********************************************************************/
/* Size of configuration in ROM and RAM used for interface: LI1 */
#define LIN_SIZE_OF_CFG  6 
#define LIN_CFG_FRAME_NUM  2 
/*********************************************************************
 * global macros
 *********************************************************************/
#define l_bool_rd(SIGNAL) l_bool_rd_##SIGNAL()
#define l_bool_wr(SIGNAL, A) l_bool_wr_##SIGNAL(A)
#define l_u8_rd(SIGNAL) l_u8_rd_##SIGNAL()
#define l_u8_wr(SIGNAL, A) l_u8_wr_##SIGNAL(A)
#define l_u16_rd(SIGNAL) l_u16_rd_##SIGNAL()
#define l_u16_wr(SIGNAL, A) l_u16_wr_##SIGNAL(A)
#define l_bytes_rd(SIGNAL, start, count, data)  l_bytes_rd_##SIGNAL(start, count, data)
#define l_bytes_wr(SIGNAL, start, count, data) l_bytes_wr_##SIGNAL(start, count, data)
#define l_flg_tst(FLAG) l_flg_tst_##FLAG()
#define l_flg_clr(FLAG) l_flg_clr_##FLAG()
#define LIN_TEST_BIT(A,B) ((l_bool)((((A) & (1U << (B))) != 0U) ? 1U : 0U))
#define LIN_SET_BIT(A,B)                      ((A) |= (l_u8) (1U << (B)))
#define LIN_CLEAR_BIT(A,B)               ((A) &= ((l_u8) (~(1U << (B)))))
#define LIN_BYTE_MASK  ((l_u16)(((l_u16)((l_u16)1 << CHAR_BIT)) - (l_u16)1))
#define LIN_FRAME_LEN_MAX                                             10U

/* Returns the low byte of the 32-bit value    */
#define BYTE_0(n)                              ((l_u8)((n) & (l_u8)0xFF))
/* Returns the second byte of the 32-bit value */
#define BYTE_1(n)                        ((l_u8)(BYTE_0((n) >> (l_u8)8)))
/* Returns the third byte of the 32-bit value  */
#define BYTE_2(n)                       ((l_u8)(BYTE_0((n) >> (l_u8)16)))
/* Returns high byte of the 32-bit value       */
#define BYTE_3(n)                       ((l_u8)(BYTE_0((n) >> (l_u8)24)))

/*
 * defines for signal access
 */


#define LIN_BYTE_OFFSET_LI0_BCMSysPwrMd_lL1    7
#define LIN_BIT_OFFSET_LI0_BCMSysPwrMd_lL1    5
#define LIN_SIGNAL_SIZE_LI0_BCMSysPwrMd_lL1    2
#define LIN_FLAG_BYTE_OFFSET_LI0_BCMSysPwrMd_lL1    3
#define LIN_FLAG_BIT_OFFSET_LI0_BCMSysPwrMd_lL1    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCMSysPwrMd_lL1    0

#define LIN_BYTE_OFFSET_LI0_DrvrPWLHiEftCndA_l    14
#define LIN_BIT_OFFSET_LI0_DrvrPWLHiEftCndA_l    0
#define LIN_SIGNAL_SIZE_LI0_DrvrPWLHiEftCndA_l    1
#define LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLHiEftCndA_l    4
#define LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLHiEftCndA_l    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLHiEftCndA_l    1

#define LIN_BYTE_OFFSET_LI0_DrvrPWLNotNormd_l    13
#define LIN_BIT_OFFSET_LI0_DrvrPWLNotNormd_l    7
#define LIN_SIGNAL_SIZE_LI0_DrvrPWLNotNormd_l    1
#define LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLNotNormd_l    4
#define LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLNotNormd_l    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLNotNormd_l    1

#define LIN_BYTE_OFFSET_LI0_DrvrPWLOpEnb_l    6
#define LIN_BIT_OFFSET_LI0_DrvrPWLOpEnb_l    0
#define LIN_SIGNAL_SIZE_LI0_DrvrPWLOpEnb_l    1
#define LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLOpEnb_l    2
#define LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLOpEnb_l    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLOpEnb_l    0

#define LIN_BYTE_OFFSET_LI0_DrvrPWLRelayFltDetc_l    14
#define LIN_BIT_OFFSET_LI0_DrvrPWLRelayFltDetc_l    4
#define LIN_SIGNAL_SIZE_LI0_DrvrPWLRelayFltDetc_l    1
#define LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLRelayFltDetc_l    4
#define LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLRelayFltDetc_l    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLRelayFltDetc_l    1

#define LIN_BYTE_OFFSET_LI0_DrvrPWLRevsng_l    14
#define LIN_BIT_OFFSET_LI0_DrvrPWLRevsng_l    1
#define LIN_SIGNAL_SIZE_LI0_DrvrPWLRevsng_l    1
#define LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLRevsng_l    4
#define LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLRevsng_l    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLRevsng_l    1

#define LIN_BYTE_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l    14
#define LIN_BIT_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l    2
#define LIN_SIGNAL_SIZE_LI0_DrvrPWLSnsngSysFltDetc_l    1
#define LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l    4
#define LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l    1

#define LIN_BYTE_OFFSET_LI0_DrvrPWLThrmlProtnA_l    14
#define LIN_BIT_OFFSET_LI0_DrvrPWLThrmlProtnA_l    3
#define LIN_SIGNAL_SIZE_LI0_DrvrPWLThrmlProtnA_l    1
#define LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLThrmlProtnA_l    4
#define LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLThrmlProtnA_l    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLThrmlProtnA_l    1

#define LIN_BYTE_OFFSET_LI0_DrvrWndDclnSpc_l    15
#define LIN_BIT_OFFSET_LI0_DrvrWndDclnSpc_l    0
#define LIN_SIGNAL_SIZE_LI0_DrvrWndDclnSpc_l    8
#define LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndDclnSpc_l    5
#define LIN_FLAG_BIT_OFFSET_LI0_DrvrWndDclnSpc_l    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrWndDclnSpc_l    1

#define LIN_BYTE_OFFSET_LI0_DrvrWndLclSwDsbld_l    5
#define LIN_BIT_OFFSET_LI0_DrvrWndLclSwDsbld_l    4
#define LIN_SIGNAL_SIZE_LI0_DrvrWndLclSwDsbld_l    1
#define LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndLclSwDsbld_l    2
#define LIN_FLAG_BIT_OFFSET_LI0_DrvrWndLclSwDsbld_l    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrWndLclSwDsbld_l    0

#define LIN_BYTE_OFFSET_LI0_DrvrWndLclSwSts_l    14
#define LIN_BIT_OFFSET_LI0_DrvrWndLclSwSts_l    5
#define LIN_SIGNAL_SIZE_LI0_DrvrWndLclSwSts_l    3
#define LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndLclSwSts_l    5
#define LIN_FLAG_BIT_OFFSET_LI0_DrvrWndLclSwSts_l    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrWndLclSwSts_l    1

#define LIN_BYTE_OFFSET_LI0_DrvrWndOpReq_l    6
#define LIN_BIT_OFFSET_LI0_DrvrWndOpReq_l    1
#define LIN_SIGNAL_SIZE_LI0_DrvrWndOpReq_l    3
#define LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndOpReq_l    3
#define LIN_FLAG_BIT_OFFSET_LI0_DrvrWndOpReq_l    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrWndOpReq_l    0

#define LIN_BYTE_OFFSET_LI0_DrvrWndShrtMvReq_l    0
#define LIN_BIT_OFFSET_LI0_DrvrWndShrtMvReq_l    3
#define LIN_SIGNAL_SIZE_LI0_DrvrWndShrtMvReq_l    2
#define LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndShrtMvReq_l    0
#define LIN_FLAG_BIT_OFFSET_LI0_DrvrWndShrtMvReq_l    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrWndShrtMvReq_l    0

#define LIN_BYTE_OFFSET_LI0_PWL1RespEr_l    13
#define LIN_BIT_OFFSET_LI0_PWL1RespEr_l    6
#define LIN_SIGNAL_SIZE_LI0_PWL1RespEr_l    1
#define LIN_FLAG_BYTE_OFFSET_LI0_PWL1RespEr_l    4
#define LIN_FLAG_BIT_OFFSET_LI0_PWL1RespEr_l    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_PWL1RespEr_l    1

#define LIN_BYTE_OFFSET_LI0_FrtPsngPWLOpEnb_l    0
#define LIN_BIT_OFFSET_LI0_FrtPsngPWLOpEnb_l    5
#define LIN_SIGNAL_SIZE_LI0_FrtPsngPWLOpEnb_l    1
#define LIN_FLAG_BYTE_OFFSET_LI0_FrtPsngPWLOpEnb_l    0
#define LIN_FLAG_BIT_OFFSET_LI0_FrtPsngPWLOpEnb_l    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrtPsngPWLOpEnb_l    0

#define LIN_BYTE_OFFSET_LI0_FrtPsngWndLclSwDsbld_l    5
#define LIN_BIT_OFFSET_LI0_FrtPsngWndLclSwDsbld_l    3
#define LIN_SIGNAL_SIZE_LI0_FrtPsngWndLclSwDsbld_l    1
#define LIN_FLAG_BYTE_OFFSET_LI0_FrtPsngWndLclSwDsbld_l    2
#define LIN_FLAG_BIT_OFFSET_LI0_FrtPsngWndLclSwDsbld_l    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrtPsngWndLclSwDsbld_l    0

#define LIN_BYTE_OFFSET_LI0_FrtPsngWndOpReq_l    5
#define LIN_BIT_OFFSET_LI0_FrtPsngWndOpReq_l    0
#define LIN_SIGNAL_SIZE_LI0_FrtPsngWndOpReq_l    3
#define LIN_FLAG_BYTE_OFFSET_LI0_FrtPsngWndOpReq_l    2
#define LIN_FLAG_BIT_OFFSET_LI0_FrtPsngWndOpReq_l    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrtPsngWndOpReq_l    0

#define LIN_BYTE_OFFSET_LI0_FrtPsngWndShrtMvReq_l    5
#define LIN_BIT_OFFSET_LI0_FrtPsngWndShrtMvReq_l    6
#define LIN_SIGNAL_SIZE_LI0_FrtPsngWndShrtMvReq_l    2
#define LIN_FLAG_BYTE_OFFSET_LI0_FrtPsngWndShrtMvReq_l    2
#define LIN_FLAG_BIT_OFFSET_LI0_FrtPsngWndShrtMvReq_l    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrtPsngWndShrtMvReq_l    0


#define LIN_FLAG_BYTE_OFFSET_LI0_BCM_LIN1_FrP00             0
#define LIN_FLAG_BIT_OFFSET_LI0_BCM_LIN1_FrP00              0

#define LIN_FLAG_BYTE_OFFSET_LI0_PWL1_LIN1_FrP00             4
#define LIN_FLAG_BIT_OFFSET_LI0_PWL1_LIN1_FrP00              0


/**********************************************************************/
/***************        Static API Functions        *******************/
/**********************************************************************/
/*
 * the static signal access macros
 */


/* static access macros for signal LI0_BCMSysPwrMd_lL1 */
#define l_u8_rd_LI0_BCMSysPwrMd_lL1() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCMSysPwrMd_lL1] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_BCMSysPwrMd_lL1) - 1) \
    << LIN_BIT_OFFSET_LI0_BCMSysPwrMd_lL1 )) >> LIN_BIT_OFFSET_LI0_BCMSysPwrMd_lL1))
#define l_u8_wr_LI0_BCMSysPwrMd_lL1(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCMSysPwrMd_lL1] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_BCMSysPwrMd_lL1] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_BCMSysPwrMd_lL1) - 1) << LIN_BIT_OFFSET_LI0_BCMSysPwrMd_lL1)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_BCMSysPwrMd_lL1) - 1) & (A)) << LIN_BIT_OFFSET_LI0_BCMSysPwrMd_lL1))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_BCMSysPwrMd_lL1] = 1;}

/* static access macros for signal LI0_DrvrPWLHiEftCndA_l */
#define l_bool_rd_LI0_DrvrPWLHiEftCndA_l() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLHiEftCndA_l], \
   	LIN_BIT_OFFSET_LI0_DrvrPWLHiEftCndA_l))
#define l_bool_wr_LI0_DrvrPWLHiEftCndA_l(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLHiEftCndA_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLHiEftCndA_l)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLHiEftCndA_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLHiEftCndA_l));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLHiEftCndA_l] = 1;}

/* static access macros for signal LI0_DrvrPWLNotNormd_l */
#define l_bool_rd_LI0_DrvrPWLNotNormd_l() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLNotNormd_l], \
   	LIN_BIT_OFFSET_LI0_DrvrPWLNotNormd_l))
#define l_bool_wr_LI0_DrvrPWLNotNormd_l(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLNotNormd_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLNotNormd_l)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLNotNormd_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLNotNormd_l));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLNotNormd_l] = 1;}

/* static access macros for signal LI0_DrvrPWLOpEnb_l */
#define l_bool_rd_LI0_DrvrPWLOpEnb_l() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLOpEnb_l], \
   	LIN_BIT_OFFSET_LI0_DrvrPWLOpEnb_l))
#define l_bool_wr_LI0_DrvrPWLOpEnb_l(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLOpEnb_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLOpEnb_l)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLOpEnb_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLOpEnb_l));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLOpEnb_l] = 1;}

/* static access macros for signal LI0_DrvrPWLRelayFltDetc_l */
#define l_bool_rd_LI0_DrvrPWLRelayFltDetc_l() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLRelayFltDetc_l], \
   	LIN_BIT_OFFSET_LI0_DrvrPWLRelayFltDetc_l))
#define l_bool_wr_LI0_DrvrPWLRelayFltDetc_l(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLRelayFltDetc_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLRelayFltDetc_l)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLRelayFltDetc_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLRelayFltDetc_l));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLRelayFltDetc_l] = 1;}

/* static access macros for signal LI0_DrvrPWLRevsng_l */
#define l_bool_rd_LI0_DrvrPWLRevsng_l() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLRevsng_l], \
   	LIN_BIT_OFFSET_LI0_DrvrPWLRevsng_l))
#define l_bool_wr_LI0_DrvrPWLRevsng_l(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLRevsng_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLRevsng_l)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLRevsng_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLRevsng_l));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLRevsng_l] = 1;}

/* static access macros for signal LI0_DrvrPWLSnsngSysFltDetc_l */
#define l_bool_rd_LI0_DrvrPWLSnsngSysFltDetc_l() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l], \
   	LIN_BIT_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l))
#define l_bool_wr_LI0_DrvrPWLSnsngSysFltDetc_l(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l] = 1;}

/* static access macros for signal LI0_DrvrPWLThrmlProtnA_l */
#define l_bool_rd_LI0_DrvrPWLThrmlProtnA_l() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLThrmlProtnA_l], \
   	LIN_BIT_OFFSET_LI0_DrvrPWLThrmlProtnA_l))
#define l_bool_wr_LI0_DrvrPWLThrmlProtnA_l(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLThrmlProtnA_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLThrmlProtnA_l)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrPWLThrmlProtnA_l], \
  	LIN_BIT_OFFSET_LI0_DrvrPWLThrmlProtnA_l));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrPWLThrmlProtnA_l] = 1;}

/* static access macros for signal LI0_DrvrWndDclnSpc_l */
#define l_u8_rd_LI0_DrvrWndDclnSpc_l() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndDclnSpc_l] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_DrvrWndDclnSpc_l) - 1) \
    << LIN_BIT_OFFSET_LI0_DrvrWndDclnSpc_l )) >> LIN_BIT_OFFSET_LI0_DrvrWndDclnSpc_l))
#define l_u8_wr_LI0_DrvrWndDclnSpc_l(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndDclnSpc_l] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndDclnSpc_l] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_DrvrWndDclnSpc_l) - 1) << LIN_BIT_OFFSET_LI0_DrvrWndDclnSpc_l)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_DrvrWndDclnSpc_l) - 1) & (A)) << LIN_BIT_OFFSET_LI0_DrvrWndDclnSpc_l))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrWndDclnSpc_l] = 1;}

/* static access macros for signal LI0_DrvrWndLclSwDsbld_l */
#define l_bool_rd_LI0_DrvrWndLclSwDsbld_l() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndLclSwDsbld_l], \
   	LIN_BIT_OFFSET_LI0_DrvrWndLclSwDsbld_l))
#define l_bool_wr_LI0_DrvrWndLclSwDsbld_l(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndLclSwDsbld_l], \
  	LIN_BIT_OFFSET_LI0_DrvrWndLclSwDsbld_l)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndLclSwDsbld_l], \
  	LIN_BIT_OFFSET_LI0_DrvrWndLclSwDsbld_l));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrWndLclSwDsbld_l] = 1;}

/* static access macros for signal LI0_DrvrWndLclSwSts_l */
#define l_u8_rd_LI0_DrvrWndLclSwSts_l() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndLclSwSts_l] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_DrvrWndLclSwSts_l) - 1) \
    << LIN_BIT_OFFSET_LI0_DrvrWndLclSwSts_l )) >> LIN_BIT_OFFSET_LI0_DrvrWndLclSwSts_l))
#define l_u8_wr_LI0_DrvrWndLclSwSts_l(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndLclSwSts_l] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndLclSwSts_l] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_DrvrWndLclSwSts_l) - 1) << LIN_BIT_OFFSET_LI0_DrvrWndLclSwSts_l)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_DrvrWndLclSwSts_l) - 1) & (A)) << LIN_BIT_OFFSET_LI0_DrvrWndLclSwSts_l))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrWndLclSwSts_l] = 1;}

/* static access macros for signal LI0_DrvrWndOpReq_l */
#define l_u8_rd_LI0_DrvrWndOpReq_l() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndOpReq_l] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_DrvrWndOpReq_l) - 1) \
    << LIN_BIT_OFFSET_LI0_DrvrWndOpReq_l )) >> LIN_BIT_OFFSET_LI0_DrvrWndOpReq_l))
#define l_u8_wr_LI0_DrvrWndOpReq_l(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndOpReq_l] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndOpReq_l] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_DrvrWndOpReq_l) - 1) << LIN_BIT_OFFSET_LI0_DrvrWndOpReq_l)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_DrvrWndOpReq_l) - 1) & (A)) << LIN_BIT_OFFSET_LI0_DrvrWndOpReq_l))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrWndOpReq_l] = 1;}

/* static access macros for signal LI0_DrvrWndShrtMvReq_l */
#define l_u8_rd_LI0_DrvrWndShrtMvReq_l() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndShrtMvReq_l] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_DrvrWndShrtMvReq_l) - 1) \
    << LIN_BIT_OFFSET_LI0_DrvrWndShrtMvReq_l )) >> LIN_BIT_OFFSET_LI0_DrvrWndShrtMvReq_l))
#define l_u8_wr_LI0_DrvrWndShrtMvReq_l(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndShrtMvReq_l] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_DrvrWndShrtMvReq_l] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_DrvrWndShrtMvReq_l) - 1) << LIN_BIT_OFFSET_LI0_DrvrWndShrtMvReq_l)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_DrvrWndShrtMvReq_l) - 1) & (A)) << LIN_BIT_OFFSET_LI0_DrvrWndShrtMvReq_l))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_DrvrWndShrtMvReq_l] = 1;}

/* static access macros for signal LI0_PWL1RespEr_l */
#define l_bool_rd_LI0_PWL1RespEr_l() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_PWL1RespEr_l], \
   	LIN_BIT_OFFSET_LI0_PWL1RespEr_l))
#define l_bool_wr_LI0_PWL1RespEr_l(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_PWL1RespEr_l], \
  	LIN_BIT_OFFSET_LI0_PWL1RespEr_l)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_PWL1RespEr_l], \
  	LIN_BIT_OFFSET_LI0_PWL1RespEr_l));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_PWL1RespEr_l] = 1;}

/* static access macros for signal LI0_FrtPsngPWLOpEnb_l */
#define l_bool_rd_LI0_FrtPsngPWLOpEnb_l() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrtPsngPWLOpEnb_l], \
   	LIN_BIT_OFFSET_LI0_FrtPsngPWLOpEnb_l))
#define l_bool_wr_LI0_FrtPsngPWLOpEnb_l(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrtPsngPWLOpEnb_l], \
  	LIN_BIT_OFFSET_LI0_FrtPsngPWLOpEnb_l)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrtPsngPWLOpEnb_l], \
  	LIN_BIT_OFFSET_LI0_FrtPsngPWLOpEnb_l));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrtPsngPWLOpEnb_l] = 1;}

/* static access macros for signal LI0_FrtPsngWndLclSwDsbld_l */
#define l_bool_rd_LI0_FrtPsngWndLclSwDsbld_l() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrtPsngWndLclSwDsbld_l], \
   	LIN_BIT_OFFSET_LI0_FrtPsngWndLclSwDsbld_l))
#define l_bool_wr_LI0_FrtPsngWndLclSwDsbld_l(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrtPsngWndLclSwDsbld_l], \
  	LIN_BIT_OFFSET_LI0_FrtPsngWndLclSwDsbld_l)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrtPsngWndLclSwDsbld_l], \
  	LIN_BIT_OFFSET_LI0_FrtPsngWndLclSwDsbld_l));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrtPsngWndLclSwDsbld_l] = 1;}

/* static access macros for signal LI0_FrtPsngWndOpReq_l */
#define l_u8_rd_LI0_FrtPsngWndOpReq_l() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrtPsngWndOpReq_l] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_FrtPsngWndOpReq_l) - 1) \
    << LIN_BIT_OFFSET_LI0_FrtPsngWndOpReq_l )) >> LIN_BIT_OFFSET_LI0_FrtPsngWndOpReq_l))
#define l_u8_wr_LI0_FrtPsngWndOpReq_l(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrtPsngWndOpReq_l] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrtPsngWndOpReq_l] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_FrtPsngWndOpReq_l) - 1) << LIN_BIT_OFFSET_LI0_FrtPsngWndOpReq_l)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_FrtPsngWndOpReq_l) - 1) & (A)) << LIN_BIT_OFFSET_LI0_FrtPsngWndOpReq_l))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrtPsngWndOpReq_l] = 1;}

/* static access macros for signal LI0_FrtPsngWndShrtMvReq_l */
#define l_u8_rd_LI0_FrtPsngWndShrtMvReq_l() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrtPsngWndShrtMvReq_l] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_FrtPsngWndShrtMvReq_l) - 1) \
    << LIN_BIT_OFFSET_LI0_FrtPsngWndShrtMvReq_l )) >> LIN_BIT_OFFSET_LI0_FrtPsngWndShrtMvReq_l))
#define l_u8_wr_LI0_FrtPsngWndShrtMvReq_l(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrtPsngWndShrtMvReq_l] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_FrtPsngWndShrtMvReq_l] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_FrtPsngWndShrtMvReq_l) - 1) << LIN_BIT_OFFSET_LI0_FrtPsngWndShrtMvReq_l)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_FrtPsngWndShrtMvReq_l) - 1) & (A)) << LIN_BIT_OFFSET_LI0_FrtPsngWndShrtMvReq_l))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_FrtPsngWndShrtMvReq_l] = 1;}
	

/* Signal flag APIs */


#define l_flg_tst_LI0_BCMSysPwrMd_lL1() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCMSysPwrMd_lL1],\
         LIN_FLAG_BIT_OFFSET_LI0_BCMSysPwrMd_lL1)
#define l_flg_clr_LI0_BCMSysPwrMd_lL1() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCMSysPwrMd_lL1],\
         LIN_FLAG_BIT_OFFSET_LI0_BCMSysPwrMd_lL1)

#define l_flg_tst_LI0_DrvrPWLHiEftCndA_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLHiEftCndA_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLHiEftCndA_l)
#define l_flg_clr_LI0_DrvrPWLHiEftCndA_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLHiEftCndA_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLHiEftCndA_l)

#define l_flg_tst_LI0_DrvrPWLNotNormd_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLNotNormd_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLNotNormd_l)
#define l_flg_clr_LI0_DrvrPWLNotNormd_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLNotNormd_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLNotNormd_l)

#define l_flg_tst_LI0_DrvrPWLOpEnb_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLOpEnb_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLOpEnb_l)
#define l_flg_clr_LI0_DrvrPWLOpEnb_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLOpEnb_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLOpEnb_l)

#define l_flg_tst_LI0_DrvrPWLRelayFltDetc_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLRelayFltDetc_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLRelayFltDetc_l)
#define l_flg_clr_LI0_DrvrPWLRelayFltDetc_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLRelayFltDetc_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLRelayFltDetc_l)

#define l_flg_tst_LI0_DrvrPWLRevsng_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLRevsng_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLRevsng_l)
#define l_flg_clr_LI0_DrvrPWLRevsng_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLRevsng_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLRevsng_l)

#define l_flg_tst_LI0_DrvrPWLSnsngSysFltDetc_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l)
#define l_flg_clr_LI0_DrvrPWLSnsngSysFltDetc_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLSnsngSysFltDetc_l)

#define l_flg_tst_LI0_DrvrPWLThrmlProtnA_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLThrmlProtnA_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLThrmlProtnA_l)
#define l_flg_clr_LI0_DrvrPWLThrmlProtnA_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrPWLThrmlProtnA_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrPWLThrmlProtnA_l)

#define l_flg_tst_LI0_DrvrWndDclnSpc_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndDclnSpc_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrWndDclnSpc_l)
#define l_flg_clr_LI0_DrvrWndDclnSpc_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndDclnSpc_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrWndDclnSpc_l)

#define l_flg_tst_LI0_DrvrWndLclSwDsbld_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndLclSwDsbld_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrWndLclSwDsbld_l)
#define l_flg_clr_LI0_DrvrWndLclSwDsbld_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndLclSwDsbld_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrWndLclSwDsbld_l)

#define l_flg_tst_LI0_DrvrWndLclSwSts_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndLclSwSts_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrWndLclSwSts_l)
#define l_flg_clr_LI0_DrvrWndLclSwSts_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndLclSwSts_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrWndLclSwSts_l)

#define l_flg_tst_LI0_DrvrWndOpReq_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndOpReq_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrWndOpReq_l)
#define l_flg_clr_LI0_DrvrWndOpReq_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndOpReq_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrWndOpReq_l)

#define l_flg_tst_LI0_DrvrWndShrtMvReq_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndShrtMvReq_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrWndShrtMvReq_l)
#define l_flg_clr_LI0_DrvrWndShrtMvReq_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_DrvrWndShrtMvReq_l],\
         LIN_FLAG_BIT_OFFSET_LI0_DrvrWndShrtMvReq_l)

#define l_flg_tst_LI0_PWL1RespEr_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_PWL1RespEr_l],\
         LIN_FLAG_BIT_OFFSET_LI0_PWL1RespEr_l)
#define l_flg_clr_LI0_PWL1RespEr_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_PWL1RespEr_l],\
         LIN_FLAG_BIT_OFFSET_LI0_PWL1RespEr_l)


#define l_flg_tst_LI0_FrtPsngPWLOpEnb_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrtPsngPWLOpEnb_l],\
         LIN_FLAG_BIT_OFFSET_LI0_FrtPsngPWLOpEnb_l)
#define l_flg_clr_LI0_FrtPsngPWLOpEnb_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrtPsngPWLOpEnb_l],\
         LIN_FLAG_BIT_OFFSET_LI0_FrtPsngPWLOpEnb_l)

#define l_flg_tst_LI0_FrtPsngWndLclSwDsbld_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrtPsngWndLclSwDsbld_l],\
         LIN_FLAG_BIT_OFFSET_LI0_FrtPsngWndLclSwDsbld_l)
#define l_flg_clr_LI0_FrtPsngWndLclSwDsbld_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrtPsngWndLclSwDsbld_l],\
         LIN_FLAG_BIT_OFFSET_LI0_FrtPsngWndLclSwDsbld_l)

#define l_flg_tst_LI0_FrtPsngWndOpReq_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrtPsngWndOpReq_l],\
         LIN_FLAG_BIT_OFFSET_LI0_FrtPsngWndOpReq_l)
#define l_flg_clr_LI0_FrtPsngWndOpReq_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrtPsngWndOpReq_l],\
         LIN_FLAG_BIT_OFFSET_LI0_FrtPsngWndOpReq_l)

#define l_flg_tst_LI0_FrtPsngWndShrtMvReq_l() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrtPsngWndShrtMvReq_l],\
         LIN_FLAG_BIT_OFFSET_LI0_FrtPsngWndShrtMvReq_l)
#define l_flg_clr_LI0_FrtPsngWndShrtMvReq_l() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_FrtPsngWndShrtMvReq_l],\
         LIN_FLAG_BIT_OFFSET_LI0_FrtPsngWndShrtMvReq_l)
		 
/* Frame flag APIs */

#define l_flg_tst_LI0_BCM_LIN1_FrP00() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_LIN1_FrP00],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_LIN1_FrP00)
#define l_flg_clr_LI0_BCM_LIN1_FrP00() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_BCM_LIN1_FrP00],\
         LIN_FLAG_BIT_OFFSET_LI0_BCM_LIN1_FrP00)

#define l_flg_tst_LI0_PWL1_LIN1_FrP00() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_PWL1_LIN1_FrP00],\
         LIN_FLAG_BIT_OFFSET_LI0_PWL1_LIN1_FrP00)
#define l_flg_clr_LI0_PWL1_LIN1_FrP00() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_PWL1_LIN1_FrP00],\
         LIN_FLAG_BIT_OFFSET_LI0_PWL1_LIN1_FrP00)



/* INTERFACE MANAGEMENT */

#define l_ifc_init_LI0() l_ifc_init(LI0)



#define l_ifc_wake_up_LI0() l_ifc_wake_up(LI0)



#define l_ifc_rx_LI0() l_ifc_rx(LI0)



#define l_ifc_tx_LI0() l_ifc_tx(LI0)



#define l_ifc_aux_LI0() l_ifc_aux(LI0)



#define l_ifc_read_status_LI0() l_ifc_read_status(LI0)


#endif    /* _LIN_CFG_H_ */