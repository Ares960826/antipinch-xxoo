/**
  ******************************************************************************
  * @file     xl_i2c.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the I2C 
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
#ifndef __XL_I2C_H__
#define __XL_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif
/* Define to prevent recursive inclusion -------------------------------------*/
#include "XL6600.h"
/* Register define ------------------------------------------------------------*/
/* I2C_CR Bit Fields */
#define I2C_CR_ME_MASK                             0x1u
#define I2C_CR_ME_SHIFT                            0
#define I2C_CR_SPEED_MASK                          0x6u
#define I2C_CR_SPEED_SHIFT                         2
#define I2C_CR_SAD_MASK                            0x8u
#define I2C_CR_SAD_SHIFT                           3
#define I2C_CR_MAD_MASK                            0x10u
#define I2C_CR_MAD_SHIFT                           4
#define I2C_CR_RE_MASK                             0x20u
#define I2C_CR_RE_SHIFT                            5
#define I2C_CR_SD_MASK                             0x40u
#define I2C_CR_SD_SHIFT                            6

/* I2C_TAR Bit Fields */
#define I2C_TAR_TAD_MASK                           0x3FFu
#define I2C_TAR_TAD_SHIFT                          0
#define I2C_TAR_GOS_MASK                           0x400u
#define I2C_TAR_GOS_SHIFT                          10
#define I2C_TAR_SPECIAL_MASK                       0x800u
#define I2C_TAR_SPECIAL_SHIFT                      11

/* I2C_SAR Bit Fields */
#define I2C_SAR_SAD_MASK                           0x3FFu
#define I2C_SAR_SAD_SHIFT                          0

/* I2C_HSMA Bit Fields */ 
#define I2C_HSMA_HSMC_MASK                         0x7u
#define I2C_HSMA_HSMC_SHIFT                        0

/* I2C_DBC Bit Fields */
#define I2C_DBC_DAT_MASK                           0xFFu
#define I2C_DBC_DAT_SHIFT                          0

#define I2C_DBC_CMD_MASK                           0x100u
#define I2C_DBC_CMD_SHIFT                          8

#define I2C_DBC_STOP_MASK                          0x200u
#define I2C_DBC_STOP_SHIFT                         9

#define I2C_DBC_RESTART_MASK                       0x400u
#define I2C_DBC_RESTART_SHIFT                      10

/* I2C_SSCH Bit Fields */
#define I2C_SSCH_HCNT_MASK                         0xFFFFu
#define I2C_SSCH_HCNT_SHIFT                        0

/* I2C_SSCL Bit Fields */
#define I2C_SSCL_LCNT_MASK                         0xFFFFu
#define I2C_SSCL_LCNT_SHIFT                        0

/* I2C_FSCH Bit Fields */
#define I2C_FSCH_HCNT_MASK                         0xFFFFu
#define I2C_FSCH_HCNT_SHIFT                        0

/* I2C_FSCL Bit Fields */
#define I2C_FSCL_LCNT_MASK                         0xFFFFu
#define I2C_FSCL_LCNT_SHIFT                        0

/* I2C_HSCH Bit Fields */
#define I2C_HSCH_HCNT_MASK                         0xFFFFu
#define I2C_HSCH_HCNT_SHIFT                        0

/* I2C_HSCL Bit Fields */
#define I2C_HSCL_LCNT_MASK                         0xFFFFu
#define I2C_HSCL_LCNT_SHIFT                        0

/* I2C_IS Bit Fields */
#define I2C_IS_RU_MASK                             0x1u
#define I2C_IS_RU_SHIFT                            0
#define I2C_IS_RO_MASK                             0x2u
#define I2C_IS_RO_SHIFT                            1
#define I2C_IS_RF_MASK                             0x4u
#define I2C_IS_RF_SHIFT                            2
#define I2C_IS_TO_MASK                             0x8u
#define I2C_IS_TO_SHIFT                            3
#define I2C_IS_TEMP_MASK                           0x10u
#define I2C_IS_TEMP_SHIFT                          4
#define I2C_IS_RDREQ_MASK                          0x20u
#define I2C_IS_RDREQ_SHIFT                         5
#define I2C_IS_TABT_MASK                           0x40u
#define I2C_IS_TABT_SHIFT                          6
#define I2C_IS_RD_MASK                             0x80u
#define I2C_IS_RD_SHIFT                            7
#define I2C_IS_ACT_MASK                            0x100u
#define I2C_IS_ACT_SHIFT                           8
#define I2C_IS_STPD_MASK                           0x200u
#define I2C_IS_STPD_SHIFT                          9
#define I2C_IS_STATD_MASK                          0x400u
#define I2C_IS_STATD_SHIFT                         10
#define I2C_IS_GC_MASK                             0x800u
#define I2C_IS_GC_SHIFT                            11

 /* I2C_INTRM Bit Fields */
#define I2C_INTRM_RU_MASK                          0x1u
#define I2C_INTRM_RU_SHIFT                         0
#define I2C_INTRM_RO_MASK                          0x2u
#define I2C_INTRM_RO_SHIFT                         1
#define I2C_INTRM_RF_MASK                          0x4u
#define I2C_INTRM_RF_SHIFT                         2
#define I2C_INTRM_TO_MASK                          0x8u
#define I2C_INTRM_TO_SHIFT                         3
#define I2C_INTRM_TEMP_MASK                        0x10u
#define I2C_INTRM_TEMP_SHIFT                       4
#define I2C_INTRM_RDREQ_MASK                       0x20u
#define I2C_INTRM_RDREQ_SHIFT                      5
#define I2C_INTRM_TABT_MASK                        0x40u
#define I2C_INTRM_TABT_SHIFT                       6
#define I2C_INTRM_RD_MASK                          0x80u
#define I2C_INTRM_RD_SHIFT                         7
#define I2C_INTRM_ACT_MASK                         0x100u
#define I2C_INTRM_ACT_SHIFT                        8
#define I2C_INTRM_STPD_MASK                        0x200u
#define I2C_INTRM_STPD_SHIFT                       9
#define I2C_INTRM_STATD_MASK                       0x400u
#define I2C_INTRM_STATD_SHIFT                      10
#define I2C_INTRM_GC_MASK                          0x800u
#define I2C_INTRM_GC_SHIFT                         11

 /* I2C_RIS Bit Fields */
#define I2C_RIS_RU_MASK                            0x1u
#define I2C_RIS_RU_SHIFT                           0
#define I2C_RIS_RO_MASK                            0x2u
#define I2C_RIS_RO_SHIFT                           1
#define I2C_RIS_RF_MASK                            0x4u
#define I2C_RIS_RF_SHIFT                           2
#define I2C_RIS_TO_MASK                            0x8u
#define I2C_RIS_TO_SHIFT                           3
#define I2C_RIS_TEMP_MASK                          0x10u
#define I2C_RIS_TEMP_SHIFT                         4
#define I2C_RIS_RDREQ_MASK                         0x20u
#define I2C_RIS_RDREQ_SHIFT                        5
#define I2C_RIS_TABT_MASK                          0x40u
#define I2C_RIS_TABT_SHIFT                         6
#define I2C_RIS_RD_MASK                            0x80u
#define I2C_RIS_RD_SHIFT                           7
#define I2C_RIS_ACT_MASK                           0x100u
#define I2C_RIS_ACT_SHIFT                          8
#define I2C_RIS_STPD_MASK                          0x200u
#define I2C_RIS_STPD_SHIFT                         9
#define I2C_RIS_STATD_MASK                         0x400u
#define I2C_RIS_STATD_SHIFT                        10
#define I2C_RIS_GC_MASK                            0x800u
#define I2C_RIS_GC_SHIFT                           11

 /* I2C_RXTL Bit Fields */
#define I2C_RXTL_RFTL_MASK                         0xFFu
#define I2C_RXTL_RFTL_SHIFT                        0

 /* I2C_TXTL Bit Fields */
#define I2C_TXTL_TFTL_MASK                         0xFFu
#define I2C_TXTL_TFTL_SHIFT                        0

 /* I2C_CCI Bit Fields */
#define I2C_CCI_CI_MASK                            0x1u
#define I2C_CCI_CI_SHIFT                           0

 /* I2C_CRU Bit Fields */
#define I2C_CRU_CRUI_MASK                          0x1u
#define I2C_CRU_CRUI_SHIFT                         0

 /* I2C_CRO Bit Fields */
#define I2C_CRO_CROI_MASK                          0x1u
#define I2C_CRO_CROI_SHIFT                         0

 /* I2C_CTO Bit Fields */
#define I2C_CTO_CTOI_MASK                          0x1u
#define I2C_CTO_CTOI_SHIFT                         0

 /* I2C_CRR Bit Fields */
#define I2C_CRR_CRRI_MASK                          0x1u
#define I2C_CRR_CRRI_SHIFT                         0

 /* I2C_CTXA Bit Fields */
#define I2C_CTXA_CTABTI_MASK                       0x1u
#define I2C_CTXA_CTABTI_SHIFT                      0

 /* I2C_CRD Bit Fields */
#define I2C_CRD_CRDI_MASK                          0x1u
#define I2C_CRD_CRDI_SHIFT                         0

 /* I2C__CACT Bit Fields */
#define I2C_CACT_CACT_MASK                         0x1u
#define I2C_CACT_CACT_SHIFT                        0

 /* I2C_CSTOP Bit Fields */
#define I2C_CSTOP_CSTPD_MASK                       0x1u
#define I2C_CSTOP_CSTPD_SHIFT                      0

 /* I2C_CSTART Bit Fields */
#define I2C_CSTART_CSTATD_MASK                     0x1u
#define I2C_CSTART_CSTATD_SHIFT                    0

 /* I2C_CGC Bit Fields */
#define I2C_CGC_CGC_MASK                           0x1u
#define I2C_CGC_CGC_SHIFT                          0

 /* I2C_ENABLE Bit Fields */
#define I2C_ENABLE_EN_MASK                         0x1u
#define I2C_ENABLE_EN_SHIFT                        0

 /* I2C_STATUS Bit Fields */   
#define I2C_STATUS_ACT_MASK                        0x1u
#define I2C_STATUS_ACT_SHIFT                       0

#define I2C_STATUS_TFNF_MASK                       0x2u
#define I2C_STATUS_TFNF_SHIFT                      1

#define I2C_STATUS_TFE_MASK                        0x4u
#define I2C_STATUS_TFE_SHIFT                       2

#define I2C_STATUS_RFNE_MASK                       0x8u
#define I2C_STATUS_RFNE_SHIFT                      3

#define I2C_STATUS_RFF_MASK                        0x10u
#define I2C_STATUS_RFF_SHIFT                       4

#define I2C_STATUS_MACT_MASK                       0x20u
#define I2C_STATUS_MACT_SHIFT                      5

#define I2C_STATUS_SACT_MASK                       0x40u
#define I2C_STATUS_SACT_SHIFT                      6

 /* I2C_TXFLR Bit Fields */        
#define I2C_TXFLR_TXFL_MASK                        0xFu
#define I2C_TXFLR_TXFL_SHIFT                       0

 /* I2C_RXFLR Bit Fields */
#define I2C_RXFLR_RXFL_MASK                        0xFu
#define I2C_RXFLR_RXFL_SHIFT                       0

 /* I2C_TXAS Bit Fields */
#define I2C_TXAS_A7ADN_MASK                        0x1u
#define I2C_TXAS_A7ADN_SHIFT                       0

#define I2C_TXAS_A10AD1N_MASK                      0x2u
#define I2C_TXAS_A10AD1N_SHIFT                     1

#define I2C_TXAS_A10AD2N_MASK                      0x4u
#define I2C_TXAS_A10AD2N_SHIFT                     2

#define I2C_TXAS_ATXDN_MASK                        0x8u
#define I2C_TXAS_ATXDN_SHIFT                       3

#define I2C_TXAS_AGCN_MASK                         0x10u
#define I2C_TXAS_AGCN_SHIFT                        4

#define I2C_TXAS_AGCR_MASK                         0x20u
#define I2C_TXAS_AGCR_SHIFT                        5

#define I2C_TXAS_AHSA_MASK                         0x40u
#define I2C_TXAS_AHSA_SHIFT                        6

#define I2C_TXAS_ASBA_MASK                         0x80u
#define I2C_TXAS_ASBA_SHIFT                        7

#define I2C_TXAS_AHSNS_MASK                        0x100u
#define I2C_TXAS_AHSNS_SHIFT                       8

#define I2C_TXAS_ASBNS_MASK                        0x200u
#define I2C_TXAS_ASBNS_SHIFT                       9

#define I2C_TXAS_A10BNS_MASK                       0x400u
#define I2C_TXAS_A10BNS_SHIFT                      10

#define I2C_TXAS_AMD_MASK                          0x800u
#define I2C_TXAS_AMD_SHIFT                         11

#define I2C_TXAS_AL_MASK                           0x1000u
#define I2C_TXAS_AL_SHIFT                          12

#define I2C_TXAS_AST_MASK                          0x2000u
#define I2C_TXAS_AST_SHIFT                         13

#define I2C_TXAS_ASA_MASK                          0x4000u
#define I2C_TXAS_ASA_SHIFT                         14

#define I2C_TXAS_ASI_MASK                          0x8000u
#define I2C_TXAS_ASI_SHIFT                         15

 /* I2C_SDAS Bit Fields */
#define I2C_SDAS_SDAS_MASK                         0xFFu
#define I2C_SDAS_SDAS_SHIFT                        0

 /* I2C_AGC Bit Fields */
#define I2C_AGC_ACKGC_MASK                         0x1u
#define I2C_AGC_ACKGC_SHIFT                        0

 /* I2C_ES Bit Fields */
#define I2C_ES_ENS_MASK                            0x1u
#define I2C_ES_ENS_SHIFT                           0

#define I2C_ES_SROA_MASK                           0x2u
#define I2C_ES_SROA_SHIFT                          1

#define I2C_ES_SFFF_MASK                           0x4u
#define I2C_ES_SFFF_SHIFT                          2



/** I2C - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR;                               /**<I2C控制寄存器, offset: 0x00*/
  __IO uint32_t TAR;                              /**<I2C目标地址寄存器, offset: 0x04*/
  __IO uint32_t SAR;                              /**<I2C从地址寄存器, offset: 0x08*/
	   uint32_t RESERVED1;                         
  __IO uint32_t DBC;                              /**<I2C数据和命令寄存器, offset: 0x10*/
  __IO uint32_t SSCH;                             /**<标准速度IIC时钟SCL高计数寄存器, offset: 0x14*/
  __IO uint32_t SSCL;                             /**<标准速度I2C时钟SCL低计数寄存器, offset: 0x18*/
  __IO uint32_t FSCH;                             /**<快速I2C时钟SCL高计数寄存器, offset: 0x1C*/
  __IO uint32_t FSCL;                             /**<快速I2C时钟SCL低计数寄存器, offset: 0x20*/
	   uint32_t RESERVED2[2];                      
  __I  uint32_t IS;                               /**<I2C中断状态寄存器, offset: 0x2C*/
  __IO uint32_t INTRM;                            /**<I2C中断屏蔽寄存器, offset: 0x30*/
  __I  uint32_t RIS;                              /**<I2C原始中断状态寄存器, offset: 0x34*/
  __IO uint32_t RXTL;                             /**<I2C接收FIFO阈值寄存器, offset: 0x38*/
  __IO uint32_t TXTL;                             /**<I2C发送FIFO阈值寄存器, offset: 0x3C*/
  __I  uint32_t CCI;                              /**<清零所有中断寄存器, offset: 0x40*/
  __I  uint32_t CRU;                              /**<清零接收下溢中断寄存器, offset: 0x44*/
  __I  uint32_t CRO;                              /**<清零接收溢出中断寄存器, offset: 0x48*/
  __I  uint32_t CTO;                              /**<清零发送溢出中断寄存器, offset: 0x4C*/
  __I  uint32_t CRR;                              /**<清零读请求中断寄存器, offset: 0x50*/
  __I  uint32_t CTXA;                             /**<清零发送中止中断寄存器, offset: 0x54*/
  __I  uint32_t CRD;                              /**<清零接收完成中断寄存器, offset: 0x58*/
  __I  uint32_t CACT;                             /**<清零活动中断寄存器, offset: 0x5c*/
  __I  uint32_t CSTOP;                            /**<清零终止位检测中断寄存器, offset: 0x60*/
  __I  uint32_t CSTART;                           /**<清零起始位检测中断寄存器, offset: 0x64*/
  __I  uint32_t CGC;                              /**<清零通用调用中断寄存器, offset: 0x68*/
  __IO uint32_t ENABLE;                           /**<I2C使能寄存器, offset: 0x6C*/
  __I  uint32_t STATUS;                           /**<I2C状态寄存器, offset: 0x70*/
  __I  uint32_t TXFLR;                            /**<I2C发送FIFO水平寄存器, offset: 0x74*/
  __I  uint32_t RXFLR;                            /**<I2C接收FIFO水平寄存器, offset: 0x78*/
	__IO uint32_t SDAHOLD;	                        /**<I2C SDA 保持时间长度寄存器, offset: 0x7C*/
	__IO uint32_t TXAS;                             /**<I2C 发送中止源寄存器, offset: 0x80*/
	     uint32_t RESERVED_2[4];	
  __IO uint32_t SDAS;                             /**<I2C SDA 设置寄存器, offset: 0x94*/
  __IO uint32_t AGC;                              /**<I2C ACK 通用调用寄存器, offset: 0x98*/
  __I  uint32_t ES;                               /**<I2C 使能状态寄存器, offset: 0x9C*/

} I2C_Type, *I2C_MemMapPtr;

extern I2C_Type* I2C1;
extern I2C_Type* I2C0;	 
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup I2C 
  * @{
  */
	
/* Exported types ------------------------------------------------------------*/ 

/** 
  * @brief I2C初始化结构体定义
  */ 
typedef struct
{
	  uint16_t I2C_SourceClk;                             /*!< 时钟源 (Mhz) */
	
    /*	IC_CR :I2C Control Register */
    uint32_t I2C_MasterModeEn;                          /*!< 主机模式是否使能 */
    uint32_t I2C_SlaveModeDis;                          /*!< 控制I2C从机是否使能 */
    uint32_t I2C_SendRestart;                           /*!< 主机模式,  是否重启 */
	  uint16_t I2C_SpeedMode;    		                      /*!< I2C操作速度 */
	  uint32_t I2C_SADmode;                               /*!< 从机模式，该位控制I2C响应7位或10位地址 */																		                     
	  uint32_t I2C_MADmode;     			                    /*!< 主机模式,此位控制I2C是以7位还是10位地址模式开始传输 */	
																                 
	  uint32_t I2C_TargetAddress;                         /*!< I2C 目标地址 */      
    
																												
	  uint32_t I2C_SlaveAddress;                          /*!< I2C 从机地址 */
	
																												
	  uint16_t I2C_HSMasterModeCode;                      /*!< I2C高速主机模式代码 */
	
	  uint32_t I2C_RXTL;                                  /*!< I2C 接收FIFO 阈值 */
	  uint32_t I2C_TXTL;                                  /*!< I2C 发送FIFO 阈值 */	

}I2C_InitTypeDef,*I2C_InitConfigPtr; 



/** @defgroup I2C_Function_Constants
  * @{
  */ 

 /** @defgroup I2C_Master_Enable I2C主机模式使能
  * @{
   */
#define   I2C_MasterModeEnabled      					((uint16_t)0x0001) /*!< 1: 主机模式使能 */
#define   I2C_MasterModeDisabled     					((uint16_t)0x0000) /*!< 0: 主机模式失能 */
/**
* @}
*/

/** @defgroup  I2C_Speed_Mode I2C速率
  * @{
 */
#define  I2C_StandardMode            					((uint16_t)0x0002) /*!< 1: 标准模式 (100 kbit/s) */
#define  I2C_FastMode                					((uint16_t)0x0004) /*!< 2: 快速模式 (400 kbit/s) */
/**
* @}
*/

/** @defgroup I2C_Slave_Address_Bit I2C从机地址位
  * @{
 */
#define  I2C_10BitAddrSlave         				((uint16_t)0x0008)  /*!< 1: 10位地址传输 */
#define  I2C_7BitAddrSlave          				((uint16_t)0x0000)  /*!< 0: 7位地址传输 */
/**
* @}
*/

/** @defgroup  I2C_Master_Address_Bit I2C 主机地址位
  * @{
 */
#define  I2C_10BitAddrMaster        				((uint16_t)0x0010)  /*!< 1: 10位地址传输 */
#define  I2C_7BitAddrMaster         				((uint16_t)0x0000)  /*!< 0: 7位地址传输 */
/**
* @}
*/

/** @defgroup  I2C_Slave_Mode_Enable I2C从机使能
  * @{
 */
#define  I2C_SlaveModeEnabled       			((uint16_t)0x0000) /*!< 0: 从机使能 */
#define  I2C_SlaveModeDisabled      			((uint16_t)0x0040) /*!< 1: 从机失能 */
/**
* @}
*/	

/** @defgroup  I2C_Send_Restsrt_Enable I2C重发命令
  * @{
 */
#define  I2C_SendRestartDisabled    			((uint16_t)0x0000) /*!< 0:  I2C重发命令失能 */
#define  I2C_SendRestartEnabled     			((uint16_t)0x0020) /*!< 1:  I2C重发命令使能 */
/**
* @}
*/


/** @defgroup High Speed Master I2C 高速主机模式Code
  * @{
  */
#define I2C_HSMasterCode_0 								((uint16_t)0x0000) /*!< 高速主机代码 0*/
#define I2C_HSMasterCode_1 								((uint16_t)0x0001) /*!< 高速主机代码 1*/
#define I2C_HSMasterCode_2 								((uint16_t)0x0002) /*!< 高速主机代码 2*/
#define I2C_HSMasterCode_3 								((uint16_t)0x0003) /*!< 高速主机代码 3*/
#define I2C_HSMasterCode_4 								((uint16_t)0x0004) /*!< 高速主机代码 4*/
#define I2C_HSMasterCode_5 								((uint16_t)0x0005) /*!< 高速主机代码 5*/
#define I2C_HSMasterCode_6 								((uint16_t)0x0006) /*!< 高速主机代码 6*/
#define I2C_HSMasterCode_7 								((uint16_t)0x0007) /*!< 高速主机代码 7*/
/**
* @}
*/

/** @defgroup I2C_Interrupt_TypeDefine I2C中断类型
	* @{
	*/
typedef enum 
{
	I2C_RXUNDERInterrupt                     =0u,        /*!< 接收下溢中断 */  
	I2C_RXOVERInterrupt                        ,        /*!< 接收溢出中断 */
	I2C_RXFULLInterrupt                        ,        /*!< 接收满中断 */
	I2C_TXOVERInterrupt                        ,        /*!< 发送溢出中断 */ 
	I2C_TXEMPTYInterrupt                       ,        /*!< 发送空中断 */ 
	I2C_RDREQInterrupt                         ,        /*!< 读请求中断 */ 
	I2C_TXABRTInterrupt                        ,        /*!< 发送中止中断 */
	I2C_RXDONEInterrupt                        ,        /*!< 接收完成中断 */
	I2C_ACTIVITYInterrupt                      ,        /*!< 活动中断 */
	I2C_STOPDETInterrupt                       ,        /*!< 停止位检测中断 */
	I2C_STARTDETInterrupt                      ,        /*!< 起始位检测中断 */ 
	I2C_GENCALLInterrupt                                /*!< 通用调用中断 */
}I2C_InterruptTypeDef;
/**
* @}
*/

/** @defgroup I2C_Interrupt_Status I2C中断状态类型
	* @{
  */
typedef enum  {
	I2C_RXUNDERInterruptStatus               =0,        /*!< 接收下溢中断状态 */
	I2C_RXOVERInterruptStatus                  ,        /*!< 接收溢出中断状态 */
	I2C_RXFULLInterruptStatus                  ,        /*!< 接收满中断状态 */
	I2C_TXOVERInterruptStatus                  ,        /*!< 发送溢出中断状态 */
	I2C_TXEMPTYInterruptStatus                 ,        /*!< 发送空中断状态 */
	I2C_RDREQInterruptStatus                   ,        /*!< 读请求中断状态 */
	I2C_TXABRTInterruptStatus                  ,        /*!< 发送中止中断状态 */
	I2C_RXDONEInterruptStatus                  ,        /*!< 接收完成中断状态 */
	I2C_ACTIVITYInterruptStatus                ,        /*!< 活动中断状态 */
	I2C_STOPDETInterruptStatus                 ,        /*!< 停止位检测中断状态 */
	I2C_STARTDETInterruptStatus                ,        /*!< 起始位检测中断状态 */
	I2C_GENCALLInterruptStatus                          /*!< 通用调用中断状态 */
} I2C_ITStatusMaskedDef;
/**
* @}
*/

/** @defgroup I2C_Interrupt_RawStatus I2C原始中断状态
	* @{
	*/
typedef enum  {
	I2C_RXUNDERInterruptRawStatus            =0,        /*!< 接收下溢原始中断状态 */  
	I2C_RXOVERInterruptRawStatus               ,        /*!< 接收溢出原始中断状态 */  
	I2C_RXFULLInterruptRawStatus               ,        /*!< 接收满原始中断状态 */ 
	I2C_TXOVERInterruptRawStatus               ,        /*!< 发送溢出原始中断状态 */  
	I2C_TXEMPTYInterruptRawStatus              ,        /*!< 发送空原始中断状态 */  
	I2C_RDREQInterruptRawStatus                ,        /*!< 读请求原始中断状态 */  
	I2C_TXABRTInterruptRawStatus               ,        /*!< 发送中止原始中断状态 */  
	I2C_RXDONEInterruptRawStatus               ,        /*!< 接收完成原始中断状态 */  
	I2C_ACTIVITYInterruptRawStatus             ,        /*!< 活动原始中断状态 */  
	I2C_STOPDETInterruptRawStatus              ,        /*!< 停止位检测原始中断状态 */  
	I2C_STARTDETInterruptRawStatus             ,        /*!< 起始位检测原始中断状态 */  
	I2C_GENCALLInterruptRawStatus                       /*!< 通用调用原始中断状态 */
} I2C_RawITStatusTypeDef;
/**
* @}
*/	

/** @defgroup I2C_Interrupt_ClearDef I2C 清除中断标志
	* @{
	*/
typedef enum  {  
  I2C_AllInterruptClear                  = 0,          /*!< 清除所有中断标志 */
	I2C_RXUNDERInterruptClear                 ,        /*!< 清除接收下溢中断标志 */  
	I2C_RXOVERInterruptClear                  ,          /*!< 清除接收溢出中断标志 */
	I2C_TXOVERInterruptClear                  ,          /*!< 清除发送溢出中断标志 */ 
	I2C_RDREQInterruptClear                   ,          /*!< 清除读请求中断标志 */ 
	I2C_TXABRTInterruptClear                  ,          /*!< 清除发送中止中断标志 */
	I2C_RXDONEInterruptClear                  ,          /*!< 清除接收完成中断标志 */
	I2C_ACTIVITYInterruptClear                ,          /*!< 清除活动中断标志 */
	I2C_STOPDETInterruptClear                 ,          /*!< 清除停止位检测中断标志 */
	I2C_STARTDETInterruptClear                ,          /*!< 清除起始位检测中断标志 */ 
	I2C_GENCALLInterruptClear                            /*!< 清除通用调用中断标志 */	

} I2C_InterruptClearDef;
/**
* @}
*/

/** @defgroup I2C_Status_Register I2C状态
	* @{
	*/
typedef enum  {
    I2C_ActivityStatus                     = 0,         /*!< I2C有效状态位 */ 
	  I2C_TransmitFIFONotFullStatus             ,		      /*!< 接收FIFO不空 */
    I2C_TransmitFIFOEmptyStatus               ,         /*!< 发送FIFO完全清空*/
    I2C_ReceiveFIFONotEmptyStatus           	,          /*!< 接收FIFO不空 */
    I2C_ReceiveFIFOFullStatus                 ,         /*!< 接收FIFO已满 */
    I2C_MasterFSMActStatus                    ,   	    /*!< 主机FSM有效状态 */
    I2C_SlaveFSMActStatus                               /*!< 从机FSM有效状态 */ 
} I2C_StatusTypeDef;
/**
* @}
*/


/** @defgroup I2C_TxRx_FIFO_Level I2C 发送接收FIFO深度
	* @{
	*/
typedef enum
{
  I2C_TransmitFIFOLevel	= 0x00,      /*!< 发送FIFO深度 */
  I2C_ReceiveFIFOLevel	= 0x01       /*!< 接收FIFO深度 */	
}I2C_TXRXFIFOLevelDef;
/**
* @}
*/

/** @defgroup I2C_Send_Stop_Def I2C 发送stop位定义
	* @{
	*/
typedef enum
{
  I2C_No_Stop	 = 0x00,      /*!< I2C发送不停止 */
  I2C_Stop	= 0x01       /*!< I2C发送中止 */	
}I2C_IsStopDef;
/**
* @}
*/

/** @defgroup I2C_Send_Abort_Codes I2C 发送终止的原因定义
	* @{
	*/
typedef enum   {
  I2C_ABRT_7B_ADDR_NOACK                   = 0,         /*!< 主机处于7位寻址模式，发送的地址未被任何从机确认 */
  I2C_ABRT_10ADDR1_NOACK                      ,         /*!< 主机处于10位地址模式，第一个10位地址字节未被任何从机确认 */
  I2C_ABRT_10ADDR2_NOACK                      ,         /*!< 主机处于10位地址模式，10位地址的第二个地址字节未被任何从机确认 */
  I2C_ABRT_TXDATA_NOACK                       ,         /*!< I2C 发送无应答 */
  I2C_ABRT_GCALL_NOACK                        ,         /*!< 总线上没有从机确认General Call */
  I2C_ABRT_GCALL_READ                         ,		      /*!< 用户将通用调用后的字节编程为从总线读取 */
  I2C_ABRT_HS_ACKDET                          ,         /*!< 主机处于高速模式，并且高速主代码被确认 */ 
  I2C_ABRT_SBYTE_ACKDET                       ,         /*!< 主机发送了一个START字节，并确认了START字节 */   
  I2C_ABRT_HS_NORSTRT                         ,         /*!< 禁止重新启动（RE位（I2C_CR [5]）= 0），用户尝试使用主机在高速模式下传输数据 */  
  I2C_ABRT_SBYTE_NORSTRT                      ,         /*!< 试清零位9之前ASBNS的源不固定 */  
  I2C_ABRT_10B_RD_NORSTRT                     ,         /*!< 禁用重启（RE位（I2C_CR [5]）= 0），主机在10位寻址模式下发送读命令 */  
  I2C_ABRT_MASTER_DIS                         ,         /*!< 用户尝试在禁用主机模式的情况下启动主机操作 */  
  I2C_ARBT_LOST                               ,         /*!< 丢失仲裁 */  
  I2C_ABRT_SLVFLUSH_TXFIFO                    ,         /*!< 从机已接收到读命令，并且TX FIFO中存在一些数据，因此从机发出TX_ABRT中断以清零TX FIFO中的旧数据。 */  
  I2C_ABRT_SLV_ARBLOST                        ,         /*!< 从机在向远程主机发送数据时丢失总线 */  
  I2C_ABRT_SLVRD_INTX                                   /*!< I2C作为从发送，处理器响应从机模式请求要发送到远程主机的数据时，用户在I2C_DBC寄存器的CMD（位8）中写入1. */ 
} I2C_ABRTSourceTypeDef;
/**
* @}
*/
 
/** @defgroup I2C_Enable_Status I2C使能状态
	* @{
	*/
typedef enum   {
	I2C_ENStatusI2CENStatus                  = 0,         /*!< I2C使能状态 */  
	I2C_ENStatusSlaveRXOperationAborted         ,         /*!< 从机接收操作中止 */  
  I2C_ENStatusSlaveFIFOFilledAndFlushed                 /*!< 从机FIFO已满被刷新        */
} I2C_EnableStatusTypeDef;
/**
* @}
*/

/**
* @}
*/

/* ICS exported function --------------------------------------------------------*/

void I2C_Deinit(I2C_Type *I2Cx);
void I2C_Init(I2C_Type *I2Cx, const I2C_InitTypeDef * I2C_InitStruct);
void I2C_EnableCmd(I2C_Type *I2Cx, FunctionalState NewState);
void I2C_GeneralCall( I2C_Type* I2Cx);
void I2C_GeneralCallAckEnableCmd(I2C_Type* I2Cx, FunctionalState NewState);
void I2C_StartByte(I2C_Type* I2Cx, uint32_t TargetAddress);
void I2C_InterruptEn(I2C_Type *I2Cx, const I2C_InterruptTypeDef I2C_Interrupt, FunctionalState NewState);
uint16_t I2C_GetMaskedIntStatus(const I2C_Type *I2Cx, I2C_ITStatusMaskedDef I2C_IntStatusType);
uint16_t I2C_GetRawIntgStatus(const I2C_Type *I2Cx,I2C_RawITStatusTypeDef I2C_RawIntStatusType);
uint16_t I2C_ClearInterrupt(const I2C_Type *I2Cx, I2C_InterruptClearDef I2C_Interrupt2Clear);
uint8_t I2C_GetStatus(const I2C_Type *I2Cx, I2C_StatusTypeDef I2C_StatusType);
uint16_t I2C_GetAbortSource(const I2C_Type *I2Cx, I2C_ABRTSourceTypeDef I2C_ABRTSourceType);
uint8_t I2C_GetEnableStatus(const I2C_Type *I2Cx, I2C_EnableStatusTypeDef I2C_EnableStatusType);
uint8_t I2C_GetFIFOLev(const I2C_Type *I2Cx, I2C_TXRXFIFOLevelDef FIFOLevelDef);
void I2C_WriteData(I2C_Type *I2Cx, uint8_t u8DataBuff,I2C_IsStopDef isstop);
void I2C_ReadDataCmd(I2C_Type *I2Cx ,I2C_IsStopDef isstop);
uint8_t I2C_ReadData(const I2C_Type *I2Cx);
void I2C_ResStartWrite(I2C_Type *I2Cx, uint8_t u8DataBuff,I2C_IsStopDef isstop);
void I2C_ResStartRead(I2C_Type *I2Cx);
void I2C_SetSDADelay(I2C_Type *I2Cx, const uint8_t I2Cclkfreq, const uint8_t DelayReq);
void I2C_SetSDAHoldTime(I2C_Type *I2Cx, uint16_t holdtime);
#ifdef __cplusplus
}
#endif

#endif 

/**
* @}
*/

/**
* @}
*/

