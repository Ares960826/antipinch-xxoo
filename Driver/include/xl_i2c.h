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
  __IO uint32_t CR;                               /**<I2C���ƼĴ���, offset: 0x00*/
  __IO uint32_t TAR;                              /**<I2CĿ���ַ�Ĵ���, offset: 0x04*/
  __IO uint32_t SAR;                              /**<I2C�ӵ�ַ�Ĵ���, offset: 0x08*/
	   uint32_t RESERVED1;                         
  __IO uint32_t DBC;                              /**<I2C���ݺ�����Ĵ���, offset: 0x10*/
  __IO uint32_t SSCH;                             /**<��׼�ٶ�IICʱ��SCL�߼����Ĵ���, offset: 0x14*/
  __IO uint32_t SSCL;                             /**<��׼�ٶ�I2Cʱ��SCL�ͼ����Ĵ���, offset: 0x18*/
  __IO uint32_t FSCH;                             /**<����I2Cʱ��SCL�߼����Ĵ���, offset: 0x1C*/
  __IO uint32_t FSCL;                             /**<����I2Cʱ��SCL�ͼ����Ĵ���, offset: 0x20*/
	   uint32_t RESERVED2[2];                      
  __I  uint32_t IS;                               /**<I2C�ж�״̬�Ĵ���, offset: 0x2C*/
  __IO uint32_t INTRM;                            /**<I2C�ж����μĴ���, offset: 0x30*/
  __I  uint32_t RIS;                              /**<I2Cԭʼ�ж�״̬�Ĵ���, offset: 0x34*/
  __IO uint32_t RXTL;                             /**<I2C����FIFO��ֵ�Ĵ���, offset: 0x38*/
  __IO uint32_t TXTL;                             /**<I2C����FIFO��ֵ�Ĵ���, offset: 0x3C*/
  __I  uint32_t CCI;                              /**<���������жϼĴ���, offset: 0x40*/
  __I  uint32_t CRU;                              /**<������������жϼĴ���, offset: 0x44*/
  __I  uint32_t CRO;                              /**<�����������жϼĴ���, offset: 0x48*/
  __I  uint32_t CTO;                              /**<���㷢������жϼĴ���, offset: 0x4C*/
  __I  uint32_t CRR;                              /**<����������жϼĴ���, offset: 0x50*/
  __I  uint32_t CTXA;                             /**<���㷢����ֹ�жϼĴ���, offset: 0x54*/
  __I  uint32_t CRD;                              /**<�����������жϼĴ���, offset: 0x58*/
  __I  uint32_t CACT;                             /**<�����жϼĴ���, offset: 0x5c*/
  __I  uint32_t CSTOP;                            /**<������ֹλ����жϼĴ���, offset: 0x60*/
  __I  uint32_t CSTART;                           /**<������ʼλ����жϼĴ���, offset: 0x64*/
  __I  uint32_t CGC;                              /**<����ͨ�õ����жϼĴ���, offset: 0x68*/
  __IO uint32_t ENABLE;                           /**<I2Cʹ�ܼĴ���, offset: 0x6C*/
  __I  uint32_t STATUS;                           /**<I2C״̬�Ĵ���, offset: 0x70*/
  __I  uint32_t TXFLR;                            /**<I2C����FIFOˮƽ�Ĵ���, offset: 0x74*/
  __I  uint32_t RXFLR;                            /**<I2C����FIFOˮƽ�Ĵ���, offset: 0x78*/
	__IO uint32_t SDAHOLD;	                        /**<I2C SDA ����ʱ�䳤�ȼĴ���, offset: 0x7C*/
	__IO uint32_t TXAS;                             /**<I2C ������ֹԴ�Ĵ���, offset: 0x80*/
	     uint32_t RESERVED_2[4];	
  __IO uint32_t SDAS;                             /**<I2C SDA ���üĴ���, offset: 0x94*/
  __IO uint32_t AGC;                              /**<I2C ACK ͨ�õ��üĴ���, offset: 0x98*/
  __I  uint32_t ES;                               /**<I2C ʹ��״̬�Ĵ���, offset: 0x9C*/

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
  * @brief I2C��ʼ���ṹ�嶨��
  */ 
typedef struct
{
	  uint16_t I2C_SourceClk;                             /*!< ʱ��Դ (Mhz) */
	
    /*	IC_CR :I2C Control Register */
    uint32_t I2C_MasterModeEn;                          /*!< ����ģʽ�Ƿ�ʹ�� */
    uint32_t I2C_SlaveModeDis;                          /*!< ����I2C�ӻ��Ƿ�ʹ�� */
    uint32_t I2C_SendRestart;                           /*!< ����ģʽ,  �Ƿ����� */
	  uint16_t I2C_SpeedMode;    		                      /*!< I2C�����ٶ� */
	  uint32_t I2C_SADmode;                               /*!< �ӻ�ģʽ����λ����I2C��Ӧ7λ��10λ��ַ */																		                     
	  uint32_t I2C_MADmode;     			                    /*!< ����ģʽ,��λ����I2C����7λ����10λ��ַģʽ��ʼ���� */	
																                 
	  uint32_t I2C_TargetAddress;                         /*!< I2C Ŀ���ַ */      
    
																												
	  uint32_t I2C_SlaveAddress;                          /*!< I2C �ӻ���ַ */
	
																												
	  uint16_t I2C_HSMasterModeCode;                      /*!< I2C��������ģʽ���� */
	
	  uint32_t I2C_RXTL;                                  /*!< I2C ����FIFO ��ֵ */
	  uint32_t I2C_TXTL;                                  /*!< I2C ����FIFO ��ֵ */	

}I2C_InitTypeDef,*I2C_InitConfigPtr; 



/** @defgroup I2C_Function_Constants
  * @{
  */ 

 /** @defgroup I2C_Master_Enable I2C����ģʽʹ��
  * @{
   */
#define   I2C_MasterModeEnabled      					((uint16_t)0x0001) /*!< 1: ����ģʽʹ�� */
#define   I2C_MasterModeDisabled     					((uint16_t)0x0000) /*!< 0: ����ģʽʧ�� */
/**
* @}
*/

/** @defgroup  I2C_Speed_Mode I2C����
  * @{
 */
#define  I2C_StandardMode            					((uint16_t)0x0002) /*!< 1: ��׼ģʽ (100 kbit/s) */
#define  I2C_FastMode                					((uint16_t)0x0004) /*!< 2: ����ģʽ (400 kbit/s) */
/**
* @}
*/

/** @defgroup I2C_Slave_Address_Bit I2C�ӻ���ַλ
  * @{
 */
#define  I2C_10BitAddrSlave         				((uint16_t)0x0008)  /*!< 1: 10λ��ַ���� */
#define  I2C_7BitAddrSlave          				((uint16_t)0x0000)  /*!< 0: 7λ��ַ���� */
/**
* @}
*/

/** @defgroup  I2C_Master_Address_Bit I2C ������ַλ
  * @{
 */
#define  I2C_10BitAddrMaster        				((uint16_t)0x0010)  /*!< 1: 10λ��ַ���� */
#define  I2C_7BitAddrMaster         				((uint16_t)0x0000)  /*!< 0: 7λ��ַ���� */
/**
* @}
*/

/** @defgroup  I2C_Slave_Mode_Enable I2C�ӻ�ʹ��
  * @{
 */
#define  I2C_SlaveModeEnabled       			((uint16_t)0x0000) /*!< 0: �ӻ�ʹ�� */
#define  I2C_SlaveModeDisabled      			((uint16_t)0x0040) /*!< 1: �ӻ�ʧ�� */
/**
* @}
*/	

/** @defgroup  I2C_Send_Restsrt_Enable I2C�ط�����
  * @{
 */
#define  I2C_SendRestartDisabled    			((uint16_t)0x0000) /*!< 0:  I2C�ط�����ʧ�� */
#define  I2C_SendRestartEnabled     			((uint16_t)0x0020) /*!< 1:  I2C�ط�����ʹ�� */
/**
* @}
*/


/** @defgroup High Speed Master I2C ��������ģʽCode
  * @{
  */
#define I2C_HSMasterCode_0 								((uint16_t)0x0000) /*!< ������������ 0*/
#define I2C_HSMasterCode_1 								((uint16_t)0x0001) /*!< ������������ 1*/
#define I2C_HSMasterCode_2 								((uint16_t)0x0002) /*!< ������������ 2*/
#define I2C_HSMasterCode_3 								((uint16_t)0x0003) /*!< ������������ 3*/
#define I2C_HSMasterCode_4 								((uint16_t)0x0004) /*!< ������������ 4*/
#define I2C_HSMasterCode_5 								((uint16_t)0x0005) /*!< ������������ 5*/
#define I2C_HSMasterCode_6 								((uint16_t)0x0006) /*!< ������������ 6*/
#define I2C_HSMasterCode_7 								((uint16_t)0x0007) /*!< ������������ 7*/
/**
* @}
*/

/** @defgroup I2C_Interrupt_TypeDefine I2C�ж�����
	* @{
	*/
typedef enum 
{
	I2C_RXUNDERInterrupt                     =0u,        /*!< ���������ж� */  
	I2C_RXOVERInterrupt                        ,        /*!< ��������ж� */
	I2C_RXFULLInterrupt                        ,        /*!< �������ж� */
	I2C_TXOVERInterrupt                        ,        /*!< ��������ж� */ 
	I2C_TXEMPTYInterrupt                       ,        /*!< ���Ϳ��ж� */ 
	I2C_RDREQInterrupt                         ,        /*!< �������ж� */ 
	I2C_TXABRTInterrupt                        ,        /*!< ������ֹ�ж� */
	I2C_RXDONEInterrupt                        ,        /*!< ��������ж� */
	I2C_ACTIVITYInterrupt                      ,        /*!< ��ж� */
	I2C_STOPDETInterrupt                       ,        /*!< ֹͣλ����ж� */
	I2C_STARTDETInterrupt                      ,        /*!< ��ʼλ����ж� */ 
	I2C_GENCALLInterrupt                                /*!< ͨ�õ����ж� */
}I2C_InterruptTypeDef;
/**
* @}
*/

/** @defgroup I2C_Interrupt_Status I2C�ж�״̬����
	* @{
  */
typedef enum  {
	I2C_RXUNDERInterruptStatus               =0,        /*!< ���������ж�״̬ */
	I2C_RXOVERInterruptStatus                  ,        /*!< ��������ж�״̬ */
	I2C_RXFULLInterruptStatus                  ,        /*!< �������ж�״̬ */
	I2C_TXOVERInterruptStatus                  ,        /*!< ��������ж�״̬ */
	I2C_TXEMPTYInterruptStatus                 ,        /*!< ���Ϳ��ж�״̬ */
	I2C_RDREQInterruptStatus                   ,        /*!< �������ж�״̬ */
	I2C_TXABRTInterruptStatus                  ,        /*!< ������ֹ�ж�״̬ */
	I2C_RXDONEInterruptStatus                  ,        /*!< ��������ж�״̬ */
	I2C_ACTIVITYInterruptStatus                ,        /*!< ��ж�״̬ */
	I2C_STOPDETInterruptStatus                 ,        /*!< ֹͣλ����ж�״̬ */
	I2C_STARTDETInterruptStatus                ,        /*!< ��ʼλ����ж�״̬ */
	I2C_GENCALLInterruptStatus                          /*!< ͨ�õ����ж�״̬ */
} I2C_ITStatusMaskedDef;
/**
* @}
*/

/** @defgroup I2C_Interrupt_RawStatus I2Cԭʼ�ж�״̬
	* @{
	*/
typedef enum  {
	I2C_RXUNDERInterruptRawStatus            =0,        /*!< ��������ԭʼ�ж�״̬ */  
	I2C_RXOVERInterruptRawStatus               ,        /*!< �������ԭʼ�ж�״̬ */  
	I2C_RXFULLInterruptRawStatus               ,        /*!< ������ԭʼ�ж�״̬ */ 
	I2C_TXOVERInterruptRawStatus               ,        /*!< �������ԭʼ�ж�״̬ */  
	I2C_TXEMPTYInterruptRawStatus              ,        /*!< ���Ϳ�ԭʼ�ж�״̬ */  
	I2C_RDREQInterruptRawStatus                ,        /*!< ������ԭʼ�ж�״̬ */  
	I2C_TXABRTInterruptRawStatus               ,        /*!< ������ֹԭʼ�ж�״̬ */  
	I2C_RXDONEInterruptRawStatus               ,        /*!< �������ԭʼ�ж�״̬ */  
	I2C_ACTIVITYInterruptRawStatus             ,        /*!< �ԭʼ�ж�״̬ */  
	I2C_STOPDETInterruptRawStatus              ,        /*!< ֹͣλ���ԭʼ�ж�״̬ */  
	I2C_STARTDETInterruptRawStatus             ,        /*!< ��ʼλ���ԭʼ�ж�״̬ */  
	I2C_GENCALLInterruptRawStatus                       /*!< ͨ�õ���ԭʼ�ж�״̬ */
} I2C_RawITStatusTypeDef;
/**
* @}
*/	

/** @defgroup I2C_Interrupt_ClearDef I2C ����жϱ�־
	* @{
	*/
typedef enum  {  
  I2C_AllInterruptClear                  = 0,          /*!< ��������жϱ�־ */
	I2C_RXUNDERInterruptClear                 ,        /*!< ������������жϱ�־ */  
	I2C_RXOVERInterruptClear                  ,          /*!< �����������жϱ�־ */
	I2C_TXOVERInterruptClear                  ,          /*!< �����������жϱ�־ */ 
	I2C_RDREQInterruptClear                   ,          /*!< ����������жϱ�־ */ 
	I2C_TXABRTInterruptClear                  ,          /*!< ���������ֹ�жϱ�־ */
	I2C_RXDONEInterruptClear                  ,          /*!< �����������жϱ�־ */
	I2C_ACTIVITYInterruptClear                ,          /*!< �����жϱ�־ */
	I2C_STOPDETInterruptClear                 ,          /*!< ���ֹͣλ����жϱ�־ */
	I2C_STARTDETInterruptClear                ,          /*!< �����ʼλ����жϱ�־ */ 
	I2C_GENCALLInterruptClear                            /*!< ���ͨ�õ����жϱ�־ */	

} I2C_InterruptClearDef;
/**
* @}
*/

/** @defgroup I2C_Status_Register I2C״̬
	* @{
	*/
typedef enum  {
    I2C_ActivityStatus                     = 0,         /*!< I2C��Ч״̬λ */ 
	  I2C_TransmitFIFONotFullStatus             ,		      /*!< ����FIFO���� */
    I2C_TransmitFIFOEmptyStatus               ,         /*!< ����FIFO��ȫ���*/
    I2C_ReceiveFIFONotEmptyStatus           	,          /*!< ����FIFO���� */
    I2C_ReceiveFIFOFullStatus                 ,         /*!< ����FIFO���� */
    I2C_MasterFSMActStatus                    ,   	    /*!< ����FSM��Ч״̬ */
    I2C_SlaveFSMActStatus                               /*!< �ӻ�FSM��Ч״̬ */ 
} I2C_StatusTypeDef;
/**
* @}
*/


/** @defgroup I2C_TxRx_FIFO_Level I2C ���ͽ���FIFO���
	* @{
	*/
typedef enum
{
  I2C_TransmitFIFOLevel	= 0x00,      /*!< ����FIFO��� */
  I2C_ReceiveFIFOLevel	= 0x01       /*!< ����FIFO��� */	
}I2C_TXRXFIFOLevelDef;
/**
* @}
*/

/** @defgroup I2C_Send_Stop_Def I2C ����stopλ����
	* @{
	*/
typedef enum
{
  I2C_No_Stop	 = 0x00,      /*!< I2C���Ͳ�ֹͣ */
  I2C_Stop	= 0x01       /*!< I2C������ֹ */	
}I2C_IsStopDef;
/**
* @}
*/

/** @defgroup I2C_Send_Abort_Codes I2C ������ֹ��ԭ����
	* @{
	*/
typedef enum   {
  I2C_ABRT_7B_ADDR_NOACK                   = 0,         /*!< ��������7λѰַģʽ�����͵ĵ�ַδ���κδӻ�ȷ�� */
  I2C_ABRT_10ADDR1_NOACK                      ,         /*!< ��������10λ��ַģʽ����һ��10λ��ַ�ֽ�δ���κδӻ�ȷ�� */
  I2C_ABRT_10ADDR2_NOACK                      ,         /*!< ��������10λ��ַģʽ��10λ��ַ�ĵڶ�����ַ�ֽ�δ���κδӻ�ȷ�� */
  I2C_ABRT_TXDATA_NOACK                       ,         /*!< I2C ������Ӧ�� */
  I2C_ABRT_GCALL_NOACK                        ,         /*!< ������û�дӻ�ȷ��General Call */
  I2C_ABRT_GCALL_READ                         ,		      /*!< �û���ͨ�õ��ú���ֽڱ��Ϊ�����߶�ȡ */
  I2C_ABRT_HS_ACKDET                          ,         /*!< �������ڸ���ģʽ�����Ҹ��������뱻ȷ�� */ 
  I2C_ABRT_SBYTE_ACKDET                       ,         /*!< ����������һ��START�ֽڣ���ȷ����START�ֽ� */   
  I2C_ABRT_HS_NORSTRT                         ,         /*!< ��ֹ����������REλ��I2C_CR [5]��= 0�����û�����ʹ�������ڸ���ģʽ�´������� */  
  I2C_ABRT_SBYTE_NORSTRT                      ,         /*!< ������λ9֮ǰASBNS��Դ���̶� */  
  I2C_ABRT_10B_RD_NORSTRT                     ,         /*!< ����������REλ��I2C_CR [5]��= 0����������10λѰַģʽ�·��Ͷ����� */  
  I2C_ABRT_MASTER_DIS                         ,         /*!< �û������ڽ�������ģʽ������������������� */  
  I2C_ARBT_LOST                               ,         /*!< ��ʧ�ٲ� */  
  I2C_ABRT_SLVFLUSH_TXFIFO                    ,         /*!< �ӻ��ѽ��յ����������TX FIFO�д���һЩ���ݣ���˴ӻ�����TX_ABRT�ж�������TX FIFO�еľ����ݡ� */  
  I2C_ABRT_SLV_ARBLOST                        ,         /*!< �ӻ�����Զ��������������ʱ��ʧ���� */  
  I2C_ABRT_SLVRD_INTX                                   /*!< I2C��Ϊ�ӷ��ͣ���������Ӧ�ӻ�ģʽ����Ҫ���͵�Զ������������ʱ���û���I2C_DBC�Ĵ�����CMD��λ8����д��1. */ 
} I2C_ABRTSourceTypeDef;
/**
* @}
*/
 
/** @defgroup I2C_Enable_Status I2Cʹ��״̬
	* @{
	*/
typedef enum   {
	I2C_ENStatusI2CENStatus                  = 0,         /*!< I2Cʹ��״̬ */  
	I2C_ENStatusSlaveRXOperationAborted         ,         /*!< �ӻ����ղ�����ֹ */  
  I2C_ENStatusSlaveFIFOFilledAndFlushed                 /*!< �ӻ�FIFO������ˢ��        */
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

