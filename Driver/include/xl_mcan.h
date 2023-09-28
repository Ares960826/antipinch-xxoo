/**
  ******************************************************************************
  * @file     xl_mcan.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the MCAN 
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
#ifndef XL_MCAN_H
#define XL_MCAN_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
/* Register define ------------------------------------------------------------*/
#pragma anon_unions /* added by neo, to support union function */

/* CANMOD Bit Fields */
#define MCAN_CANMOD_RM_MASK                     0x1u
#define MCAN_CANMOD_RM_SHIFT                    0
#define MCAN_CANMOD_LOM_MASK                    0x2u
#define MCAN_CANMOD_LOM_SHIFT                   1
#define MCAN_CANMOD_STM_MASK                    0x4u
#define MCAN_CANMOD_STM_SHIFT                   2
#define MCAN_CANMOD_AFM_MASK                    0x8u
#define MCAN_CANMOD_AFM_SHIFT                   3
#define MCAN_CANMOD_SM_MASK                     0x10u
#define MCAN_CANMOD_SM_SHIFT                    4
#define MCAN_CANMOD_FDM_MASK                    0x20u
#define MCAN_CANMOD_FDM_SHIFT                   5
#define MCAN_CANMOD_FDTREN_MASK                 0x40u
#define MCAN_CANMOD_FDTREN_SHIFT                6
#define MCAN_CANMOD_FDTDCEN_MASK                0x80u
#define MCAN_CANMOD_FDTDCEN_SHIFT               7

/* CANCMR Bit Fields */
#define MCAN_CANCMR_TR_MASK                     0x1u
#define MCAN_CANCMR_TR_SHIFT                    0
#define MCAN_CANCMR_AT_MASK                     0x2u
#define MCAN_CANCMR_AT_SHIFT                    1
#define MCAN_CANCMR_RRB_MASK                    0x4u
#define MCAN_CANCMR_RRB_SHIFT                   2
#define MCAN_CANCMR_CDO_MASK                    0x8u
#define MCAN_CANCMR_CDO_SHIFT                   3
#define MCAN_CANCMR_SRR_MASK                    0x10u
#define MCAN_CANCMR_SRR_SHIFT                   4
#define MCAN_CANCMR_EN_MASK                    	0x20u
#define MCAN_CANCMR_EN_SHIFT                   	5

/* CANSR Bit Fields */
#define MCAN_CANSR_RBS_MASK                     0x1u
#define MCAN_CANSR_RBS_SHIFT                    0
#define MCAN_CANSR_DOS_MASK                     0x2u
#define MCAN_CANSR_DOS_SHIFT                    1
#define MCAN_CANSR_TBS_MASK                     0x4u
#define MCAN_CANSR_TBS_SHIFT                    2
#define MCAN_CANSR_TCS_MASK                     0x8u
#define MCAN_CANSR_TCS_SHIFT                    3
#define MCAN_CANSR_RS_MASK                      0x10u
#define MCAN_CANSR_RS_SHIFT                     4
#define MCAN_CANSR_TS_MASK                      0x20u
#define MCAN_CANSR_TS_SHIFT                     5
#define MCAN_CANSR_ES_MASK                      0x40u
#define MCAN_CANSR_ES_SHIFT                     6
#define MCAN_CANSR_BS_MASK                      0x80u
#define MCAN_CANSR_BS_SHIFT                     7

/* CANIR Bit Fields */
#define MCAN_CANIR_RI_MASK                      0x1u
#define MCAN_CANIR_RI_SHIFT                     0
#define MCAN_CANIR_TI_MASK                      0x2u
#define MCAN_CANIR_TI_SHIFT                     1
#define MCAN_CANIR_EI_MASK                      0x4u
#define MCAN_CANIR_EI_SHIFT                     2
#define MCAN_CANIR_DOI_MASK                     0x8u
#define MCAN_CANIR_DOI_SHIFT                    3
#define MCAN_CANIR_WUI_MASK                     0x10u
#define MCAN_CANIR_WUI_SHIFT                    4
#define MCAN_CANIR_EPI_MASK                     0x20u
#define MCAN_CANIR_EPI_SHIFT                    5
#define MCAN_CANIR_ALI_MASK                     0x40u
#define MCAN_CANIR_ALI_SHIFT                    6
#define MCAN_CANIR_BEI_MASK                     0x80u
#define MCAN_CANIR_BEI_SHIFT                    7

/* CANIER Bit Fields */
#define MCAN_CANIER_RIE_MASK                    0x1u
#define MCAN_CANIER_RIE_SHIFT                   0
#define MCAN_CANIER_TIE_MASK                    0x2u
#define MCAN_CANIER_TIE_SHIFT                   1
#define MCAN_CANIER_EIE_MASK                    0x4u
#define MCAN_CANIER_EIE_SHIFT                   2
#define MCAN_CANIER_DOIE_MASK                   0x8u
#define MCAN_CANIER_DOIE_SHIFT                  3
#define MCAN_CANIER_WUIE_MASK                   0x10u
#define MCAN_CANIER_WUIE_SHIFT                  4
#define MCAN_CANIER_EPIE_MASK                   0x20u
#define MCAN_CANIER_EPIE_SHIFT                  5
#define MCAN_CANIER_ALIE_MASK                   0x40u
#define MCAN_CANIER_ALIE_SHIFT                  6
#define MCAN_CANIER_BEIE_MASK                   0x80u
#define MCAN_CANIER_BEIE_SHIFT                  7

/* CANTDCS Bit Fields */
#define MCAN_CANTDCS_TDCT_MASK                  0x1Fu
#define MCAN_CANTDCS_TDCT_SHIFT                 0

/* CANBTR0 Bit Fields */
#define MCAN_CANBTR0_BRP_MASK                   0x3Fu
#define MCAN_CANBTR0_BRP_SHIFT                  0
#define MCAN_CANBTR0_SJW_MASK                   0xC0u
#define MCAN_CANBTR0_SJW_SHIFT                  6

/* CANBTR1 Bit Fields */
#define MCAN_CANBTR1_TSEG1_MASK                 0xFu
#define MCAN_CANBTR1_TSEG1_SHIFT                0
#define MCAN_CANBTR1_TSEG2_MASK                 0x70u
#define MCAN_CANBTR1_TSEG2_SHIFT                4
#define MCAN_CANBTR1_SAMP_MASK                  0x80u
#define MCAN_CANBTR1_SAMP_SHIFT                 7

/* CANFDBTR0 Bit Fields */
#define MCAN_CANFDBTR0_FDBRP_MASK               0x3Fu
#define MCAN_CANFDBTR0_FDBRP_SHIFT              0
#define MCAN_CANFDBTR0_FDSJW_MASK               0xC0u
#define MCAN_CANFDBTR0_FDSJW_SHIFT              6

/* CANFDBTR1 Bit Fields */
#define MCAN_CANFDBTR1_FDTSEG1_MASK             0xFu
#define MCAN_CANFDBTR1_FDTSEG1_SHIFT            0
#define MCAN_CANFDBTR1_FDTSEG2_MASK             0x70u
#define MCAN_CANFDBTR1_FDTSEG2_SHIFT            4
#define MCAN_CANFDBTR1_FDSAMP_MASK              0x80u
#define MCAN_CANFDBTR1_FDSAMP_SHIFT             7

/* CANHFC Bit Fields */
#define MCAN_CANHFC_HFCT_MASK                   0x7Fu
#define MCAN_CANHFC_HFCT_SHIFT                  0

/* CANALC Bit Fields */
#define MCAN_CANALC_ALC_MASK                    0x1Fu
#define MCAN_CANALC_ALC_SHIFT                   0

/* CANECC Bit Fields */
#define MCAN_CANECC_SEGMENT_MASK                0x1Fu
#define MCAN_CANECC_SEGMENT_SHIFT               0
#define MCAN_CANECC_DIR_MASK                    0x20u
#define MCAN_CANECC_DIR_SHIFT                   5
#define MCAN_CANECC_ERROR_MASK                  0xC0u
#define MCAN_CANECC_ERROR_SHIFT                 6

/* CANEWLR Bit Fields */
#define MCAN_CANEWLR_EWL_MASK                   0xFFu
#define MCAN_CANEWLR_EWL_SHIFT                  0

/* CANRXERR Bit Fields */
#define MCAN_CANRXERR_RXERR_MASK                0xFFu
#define MCAN_CANRXERR_RXERR_SHIFT               0

/* CANTXERR Bit Fields */
#define MCAN_CANTXERR_TXERR_MASK                0xFFu
#define MCAN_CANTXERR_TXERR_SHIFT               0

/* CANTB Bit Fields */
#define MCAN_CANTB_TX_MASK                      0xFFu
#define MCAN_CANTB_TX_SHIFT                     0

/* CANRB Bit Fields */
#define MCAN_CANRB_RX_MASK                      0xFFu
#define MCAN_CANRB_RX_SHIFT                     0

/* CANACR Bit Fields */
#define MCAN_CANACR_AC_MASK                     0xFFu
#define MCAN_CANACR_AC_SHIFT                    0

/* CANAMR Bit Fields */
#define MCAN_CANAMR_AM_MASK                     0xFFu
#define MCAN_CANAMR_AM_SHIFT                    0

/* CANRMC Bit Fields */
#define MCAN_CANRMC_RMC_MASK                    0x1Fu
#define MCAN_CANRMC_RMC_SHIFT                   0

/* CANTB2R Bit Fields */
#define MCAN_CANTB2R_TB2RX_MASK                 0xFFu
#define MCAN_CANTB2R_TB2RX_SHIFT                0

/** MCAN - Register Layout Typedef */
typedef struct {
  __IO uint32_t CANMOD;                            /*!< MCANģʽ�Ĵ���, offset: 0x0 */
  __O  uint32_t CANCMR;                            /*!< MCAN����Ĵ���, offset: 0x4 */
  __I  uint32_t CANSR;                             /*!< MCAN״̬�Ĵ���, offset: 0x8 */	
  __I  uint32_t CANIR;                             /*!< MCAN�жϼĴ���, offset: 0xc */	
  __IO uint32_t CANIER;                            /*!< MCAN�ж�ʹ�ܼĴ���, offset: 0x10 */	
  __IO uint32_t CANTDCS;                           /*!< MCAN��ʱ����ʱ�����üĴ���, offset: 0x14 */	
  __IO uint32_t CANBTR0;                           /*!< MCAN���߶�ʱ�Ĵ���0, offset: 0x18 */
  __IO uint32_t CANBTR1;                           /*!< MCAN���߶�ʱ�Ĵ���1, offset: 0x1c */
	__IO uint32_t CANFDBTR0;                         /*!< MCAN FD���߶�ʱ�Ĵ���0, offset: 0x20 */
  __IO uint32_t CANFDBTR1;                         /*!< MCAN FD���߶�ʱ�Ĵ���1, offset: 0x24 */
	     uint32_t RESERVED_0[1];
  __IO uint32_t CANHFC;                            /*!< FD����֡��Ƶ�����Ĵ���, offset: 0x2C */	
	     uint32_t RESERVED_1[1];		
  __I  uint32_t CANALC;                            /*!< MCAN�ٲö�ʧ�Ĵ���, offset: 0x34 */ 
  __I  uint32_t CANECC;                            /*!< MCAN�����벶��Ĵ���, offset: 0x38 */
  __IO uint32_t CANEWLR;                           /*!< MCAN���󾯸����ƼĴ���, offset: 0x3C */
  __IO uint32_t CANRXERR;                          /*!< MCAN ���մ��������, offset: 0x40 */
  __IO uint32_t CANTXERR;                          /*!< MCAN���ʹ��������, offset: 0x44 */
  union 
	{		
		__O uint32_t CANTB[69];                        /*!< MCAN���ͻ�����0, array offset: 0x48, array step: 0x4  */
		__I uint32_t CANRB[69];                        /*!< MCAN���ջ�����0, array offset: 0x48, array step: 0x4  */
    struct
		{
			__IO uint32_t CANACR[4];                     /*!< MCAN������Ĵ���0, array offset: 0x48, array step: 0x4  */
			__IO uint32_t CANAMR[4];                     /*!< MCAN������Ĵ���0, array offset: 0x58, array step: 0x4  */
			uint32_t RESERVED_2[61];	
		}CANAR; 
	};
			 uint32_t RESERVED_3[60];		
  __I  uint32_t CANRMC;                            /*!< MCAN���ձ��ļ�����, offset: 0x24C*/
	     uint32_t RESERVED_4[258];	
  __I  uint32_t CANTB2R[69];                       /*!< MCAN���ͻ�������ȡ, offset: 0x658, array step: 0x4 */	

} MCAN_Type;

extern MCAN_Type*		MCAN;


/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup MCAN 
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/**
 * @brief MCAN �������ͳ�ʼ���ṹ��
 */
typedef struct
{
	uint8_t MCAN_ErrorWarningLimit ;     			/*!< ���󾯸����� */
	uint8_t MCAN_ReceiveErrorCount ;    			/*!< ���մ�������� */
	uint8_t MCAN_TranmitErrorCount ;     			/*!< ���ʹ�������� */	
}MCAN_ErrorSettingDef;

/**
 * @brief MCAN ��ʼ���ṹ��
 */
typedef struct
{
	uint32_t MCAN_SJW;     		            			/*!< ͬ����תλ�� */
	uint32_t MCAN_BRP;					              	/*!< ������Ԥ��Ƶ�� */
	uint32_t MCAN_SAMP;				             			/*!< ���� */
	uint32_t MCAN_TSEG2;				            		/*!< ʱ���2 */
	uint32_t MCAN_TSEG1;					            	/*!< ʱ���1 */
	uint32_t MCAN_FDSJW;     		            		/*!< CAN FD ͬ����תλ�� */
	uint32_t MCAN_FDBRP;					              /*!< CAN FD ������Ԥ��Ƶ�� */
	uint32_t MCAN_FDSAMP;				             		/*!< CAN FD ���� */
	uint32_t MCAN_FDTSEG2;				            	/*!< CAN FD ʱ���2 */
	uint32_t MCAN_FDTSEG1;					            /*!< CAN FD ʱ���1 */
}MCAN_InitTypeDef;
   
/**
 * @brief MCAN �˲���ʼ���ṹ��
 */
typedef struct
{
	uint32_t MCAN_IDMode;		            				/*!< ��ʶ����ʽ */
	uint32_t MCAN_FiltMode;	                		/*!< �˲�ģʽ�����˲�������˫�˲��� */
	uint32_t MCAN_IDAR;		    	            		/*!< MCAN��ʶ�� + һλԶ�̴������� */
	uint32_t MCAN_IDMR;		    	           			/*!< MCAN�������� + һλԶ�̴������� */
	uint32_t MCAN_DIDAR;
	uint32_t MCAN_DIDMR;		 
}MCAN_FilterDef, *MCAN_FilterConfigPtr;

/** 
  * @brief  MCAN ���ͽ�����Ϣ��ʼ���ṹ��
  */
typedef struct
{
  uint32_t MCAN_ID;                        		/*!< ��ʶ����11λ��׼֡����29λ��չ֡ */
  uint32_t MCAN_FDBRS;                      	/*!< �ɱ�����ʹ��λ, ��������FDģʽ  */
  uint32_t MCAN_FDESI;                      	/*!< ����״̬λ, ��������FDģʽ    */	
  uint32_t MCAN_FF;                         	/*!< ֡��ʽ  */
  uint32_t MCAN_RTR;                       		/*!< Զ�̴�������    ��Զ��֡��������֡            */
  uint32_t MCAN_DLC;                        	/*!< ���ݳ��� */
  uint8_t MCAN_Data[64];                   		/*!< �����Ľ������ݣ���Χ�� 0 �� 63 */
                                             
} MCAN_MsgTypeDef, *MCAN_MsgConfigPtr;

/* Exported constants --------------------------------------------------------*/
/** @defgroup MCAN_Exported_Constants MCANģ��ʹ�ò�������
  * @{
  */


/**  
	* @defgroup MCAN_Mode_List MCANģʽ����
  * @{
  */	
#define MCAN_NORMALMODE                   		0			/*!< ����ģʽ */
#define MCAN_RESETMODE                    		1			/*!< ����ģʽ */	
#define MCAN_LISTENONLYMODE               		2			/*!< ֻ��ģʽ */
#define MCAN_SELFTESTMODE                 		3			/*!< �Բ�ģʽ */
#define MCAN_SLEEPMODE                    		4			/*!< ˯��ģʽ */
/** 
  * @} 
  */
	
/** 
	* @defgroup MCAN_synchronisation_jump_width MCANͬ����ת��ȶ���
  * @{
  */	
#define MCAN_SJW_1tq                 					((uint8_t)0x00)  /*!< 1��Tqʱ������ */
#define MCAN_SJW_2tq                 					((uint8_t)0x01)  /*!< 2��Tqʱ������ */
#define MCAN_SJW_3tq                 					((uint8_t)0x02)  /*!< 3��Tqʱ������ */
#define MCAN_SJW_4tq                 					((uint8_t)0x03)  /*!< 4��Tqʱ������ */
/** 
  * @} 
  */
	
/** 
	* @defgroup MCAN_Sample_Times  MCAN����ʱ�䶨��
  * @{
  */	
#define MCAN_SAMPLE_1                					((uint8_t)0x00) /*!< ÿλһ������ */
#define MCAN_SAMPLE_3                					((uint8_t)0x01) /*!< ÿλ�������� */
/** 
  * @} 
  */

/** 
	* @defgroup MCAN_TSEG1_Select MCANʱ���2����
  * @{
  */
#define MCAN_TSEG1_1tq                 				((uint8_t)0x00)  /*!< 1��Tqʱ������ */	
#define MCAN_TSEG1_2tq                 				((uint8_t)0x01)  /*!< 2��Tqʱ������ */	
#define MCAN_TSEG1_3tq                			 	((uint8_t)0x02)  /*!< 3��Tqʱ������ */		
#define MCAN_TSEG1_4tq                 				((uint8_t)0x03)  /*!< 4��Tqʱ������ */
#define MCAN_TSEG1_5tq                 				((uint8_t)0x04)  /*!< 5��Tqʱ������ */
#define MCAN_TSEG1_6tq                 				((uint8_t)0x05)  /*!< 6��Tqʱ������ */
#define MCAN_TSEG1_7tq                 				((uint8_t)0x06)  /*!< 7��Tqʱ������ */
#define MCAN_TSEG1_8tq                 				((uint8_t)0x07)  /*!< 8��Tqʱ������ */
#define MCAN_TSEG1_9tq                 				((uint8_t)0x08)  /*!< 9��Tqʱ������ */
#define MCAN_TSEG1_10tq                				((uint8_t)0x09)  /*!< 10��Tqʱ������ */
#define MCAN_TSEG1_11tq                				((uint8_t)0x0A)  /*!< 11��Tqʱ������ */
#define MCAN_TSEG1_12tq                				((uint8_t)0x0B)  /*!< 12��Tqʱ������ */
#define MCAN_TSEG1_13tq                				((uint8_t)0x0C)  /*!< 13��Tqʱ������ */
#define MCAN_TSEG1_14tq                				((uint8_t)0x0D)  /*!< 14��Tqʱ������ */
#define MCAN_TSEG1_15tq                				((uint8_t)0x0E)  /*!< 15��Tqʱ������ */
#define MCAN_TSEG1_16tq                				((uint8_t)0x0F)  /*!< 16��Tqʱ������ */
/** 
  * @} 
  */
	
	
/** 
	* @defgroup MCAN_TSEG2_Select MCANʱ���1����
  * @{
  */
#define MCAN_TSEG2_1tq                 				((uint8_t)0x00)  /*!< 1��Tqʱ������ */  //Nemo cmt
#define MCAN_TSEG2_2tq                 				((uint8_t)0x01)  /*!< 2��Tqʱ������ */
#define MCAN_TSEG2_3tq                 				((uint8_t)0x02)  /*!< 3��Tqʱ������ */
#define MCAN_TSEG2_4tq                 				((uint8_t)0x03)  /*!< 4��Tqʱ������ */
#define MCAN_TSEG2_5tq                 				((uint8_t)0x04)  /*!< 5��Tqʱ������ */
#define MCAN_TSEG2_6tq                 				((uint8_t)0x05)  /*!< 6��Tqʱ������ */
#define MCAN_TSEG2_7tq                 				((uint8_t)0x06)  /*!< 7��Tqʱ������ */
#define MCAN_TSEG2_8tq                 				((uint8_t)0x07)  /*!< 8��Tqʱ������ */
/** 
  * @} 
  */
	
/** 
	* @defgroup MCAN_Filter_Scale  MCAN�˲�ѡ����
  * @{
  */
#define MCAN_Dual_Filter              			((uint8_t)0x00) /*!< ��������16λ�˲��� */
#define MCAN_Single_Filter            			((uint8_t)0x01) /*!< ����32λ�˲��� */
/** 
  * @} 
  */
	
/** 
	* @defgroup MCAN_FDM_FRAME  MCANFD֡����
  * @{
  */	
#define MCAN_FDM_NOMFrame             			((uint8_t)0x00) /*!< ����֡Ϊ��ͨCAN����֡          */
#define MCAN_FDM_FDFrame              			((uint8_t)0x01) /*!< ����֡ΪCAN FD֡      */
/** 
  * @} 
  */     
	
/** 
	* @defgroup MCAN_BRS_Enable MCAN������ת��
  * @{
  */	
#define MCAN_BRS_DISABLE              			((uint8_t)0x00) /*!< ��ͬδ���ʷ��� */
#define MCAN_BRS_ENABLE               			((uint8_t)0x01) /*!< ESI �ֶΡ�DLC �ֶΡ�DATA �ֶΡ�CRC �ֶ�ʹ�ø�Ƶ���ʷ��� */
/** 
  * @} 
  */
	
	
/** 
	* @defgroup MCAN_ESI_Define MCAN������
  * @{
  */		
#define MCAN_ESI_ACTIVE               			((uint8_t)0x00) /*!< ������־ */
#define MCAN_ESI_PASSIVE             			 	((uint8_t)0x01) /*!< ���������־ */
/** 
  * @} 
  */

/** 
	* @defgroup MCAN_FRAME_FORMAT MCAN֡�ṹ����
  * @{
  */	
#define MCAN_Standard_Frame           			((uint8_t)0x00) /*!< ��׼֡ */
#define MCAN_Extended_Frame           			((uint8_t)0x01) /*!< ��չ֡ */
#define MCAN_Custom_Frame						((uint8_t)0x02) /*!< �ض�֡ */
/** 
  * @} 
  */
	
/** 
	* @defgroup MCAN_REMOTE_TYPE MCAN֡�ṹ����
  * @{
  */	
#define MCAN_RTR_Data                 			((uint8_t)0x00)  /*!< ����֡ */
#define MCAN_RTR_Remote               			((uint8_t)0x01)  /*!< Զ��֡ */
/** 
  * @} 
  */
	
	
/** 
	* @defgroup MCAN_DATA_LENGTH MCAN���ݳ���
  * @{
  */
#define MCAN_DLC_DATASIZE0            			((uint8_t)0x00)  /*!< 0�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE1            			((uint8_t)0x01)  /*!< 1�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE2            			((uint8_t)0x02)  /*!< 2�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE3            			((uint8_t)0x03)  /*!< 3�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE4            			((uint8_t)0x04)  /*!< 4�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE5            			((uint8_t)0x05)  /*!< 5�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE6            			((uint8_t)0x06)  /*!< 6�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE7            			((uint8_t)0x07)  /*!< 7�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE8            			((uint8_t)0x08)  /*!< 8�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE12           			((uint8_t)0x09)  /*!< 12�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE16           			((uint8_t)0x0A)  /*!< 16�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE20           			((uint8_t)0x0B)  /*!< 20�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE24           			((uint8_t)0x0C)  /*!< 24�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE32           			((uint8_t)0x0D)  /*!< 32�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE48           			((uint8_t)0x0E)  /*!< 48�ֽ����ݳ��� */
#define MCAN_DLC_DATASIZE64           			((uint8_t)0x0F)  /*!< 64�ֽ����ݳ��� */
/** 
  * @} 
  */

/** 
	* @defgroup MCAN_Bus_Error MCAN��������
  * @{
  */
typedef enum
{
  MCAN_BusErrorType = 0x00,             /*!< λ���� */
  MCAN_BusErrorDirection  = 0x01,       /*!< ������ */
  MCAN_BusErrorPosition = 0x02          /*!< ������ */
}MCAN_BusErrorCaptureDef;
/** 
  * @} 
  */

/** 
	* @defgroup MCAN Command_Set MCAN ��������
  * @{
  */
#define MCAN_TransmissionRequest	 					0x01   	      		/*!< �������� */
#define	MCAN_AbortTransmission							0x02             	/*!< ������ֹ */                   
#define	MCAN_ReleaseReceiveBuffer						0x04	          	/*!< �ͷŽ��ջ��� */
#define	MCAN_ClearDataOverrun							0x08             	/*!< ����������� */
#define	MCAN_SelfReceptionRequest						0x10             	/*!< �Խ������� */
/** 
  * @} 
  */	

/** 
	* @defgroup MCAN_Status_SR  MCAN״̬����
  * @{
  */
typedef enum {
	MCAN_ReceiveBufferStatus= 0,          /*!< ���ջ�����״̬ */
	MCAN_DataOverrunStatus,               /*!< �������״̬ */
	MCAN_TransBufferStatus,               /*!< ���ͻ�����״̬ */
	MCAN_TransCompleteStatus,             /*!< �������״̬ */
	MCAN_ReceiveStatus,                   /*!< ����״̬ */
	MCAN_TransmitStatus,                  /*!< ����״̬ */
	MCAN_ErrorStatus,                     /*!< ����״̬ */
	MCAN_BusStatus	                      /*!< ����״̬ */
} MCAN_StatusTypeDef;
/** 
  * @} 
  */

/** 
	* @defgroup MCAN_Interrupt_ID MCAN�ж�ID
  * @{
  */
typedef enum {
	MCAN_ReceiveInterrupt= 0,             /*!< �����ж� */
	MCAN_TransmitInterrupt,               /*!< �����ж� */
	MCAN_ErrorWarningInterrupt,           /*!< ���󾯸��ж� */
	MCAN_DataOverrunInterrupt,            /*!< ��������ж� */
	MCAN_WakeUpInterrupt,                 /*!< �����ж� */
	MCAN_ErrorPassiveInterrupt,           /*!< ���󱻶��ж� */
	MCAN_ArbitrationLostInterrupt,        /*!< �ٲö�ʧ�ж� */
	MCAN_BusErrorInterrupt                /*!< ���ߴ����ж� */
} MCAN_InterruptFlgDef;
/** 
  * @} 
  */

/** 
	* @defgroup MCAN_Interrupt_Enable MCAN�ж�ʹ��
  * @{
  */
typedef enum {
	MCAN_ReceiveInterruptEn= 0,            /*!< �����ж�ʹ�� */
	MCAN_TransmitInterruptEn,              /*!< �����ж�ʹ�� */
	MCAN_ErrorWarningInterruptEn,          /*!< ���󾯸��ж�ʹ�� */
	MCAN_DataOverrunInterruptEn,           /*!< ��������ж�ʹ�� */
	MCAN_WakeUpInterruptEn,                /*!< �����ж�ʹ�� */
	MCAN_ErrorPassiveInterruptEn,          /*!< ���󱻶��ж�ʹ�� */
	MCAN_ArbitrationLostInterruptEn,       /*!< �ٲö�ʧ�ж�ʹ�� */
	MCAN_BusErrorInterruptEn               /*!< ���ߴ����ж�ʹ�� */	
} MCAN_InterruptEnDef;
/** 
  * @} 
  */

/**
	* @}
	*/


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void MCAN_DeInit(MCAN_Type* MCANx);
void MCAN_Init(MCAN_Type* MCANx, const MCAN_InitTypeDef* MCAN_InitStruct);
void MCAN_FDCmd(MCAN_Type* MCANx, FunctionalState NewState);
void MCAN_FDSendFormatSel(MCAN_Type* MCANx, uint8_t FdFormat);
void MCAN_FDTDCSet(MCAN_Type* MCANx, uint32_t CompensateTime);
void MCAN_FDTDCENCmd(MCAN_Type* MCANx, FunctionalState NewState);
void MCAN_FDHFCSet(MCAN_Type* MCANx, uint32_t CompensateTime);
void MCAN_FilterConfig(MCAN_Type* MCANx, const MCAN_FilterDef* MCAN_FilterStruct);
void MCAN_LoadTransmitData(MCAN_Type *MCANx, const MCAN_MsgTypeDef* TxMessage);
void MCAN_ReceiveData(MCAN_Type *MCANx, MCAN_MsgTypeDef* RxMessage);
void MCAN_SetMode(MCAN_Type *MCANx, uint8_t MCAN_ModeType);
void MCAN_WakeUp(MCAN_Type *MCANx);
void MCAN_SetCmd(MCAN_Type *MCANx, uint8_t MCAN_CommandType);
void MCAN_ClearReceiveInterrupt(MCAN_Type *MCANx);
FlagStatus MCAN_GetStatus(const MCAN_Type *MCANx, MCAN_StatusTypeDef MCAN_StatusType);
ITStatus MCAN_GetInterruptFlg(const MCAN_Type *MCANx, MCAN_InterruptFlgDef MCAN_InterruptFlg);
void MCAN_InterruptEn(MCAN_Type *MCANx, MCAN_InterruptEnDef MCAN_Interrupt, FunctionalState NewState);
uint8_t MCAN_ArbitrationLostCap(const MCAN_Type *MCANx);
uint8_t MCAN_GetBusErrorType(const MCAN_Type *MCANx, MCAN_BusErrorCaptureDef MCAN_BusErrorCapture);
uint8_t MCAN_GetReceiveErrorCounter(const MCAN_Type *MCANx);
uint8_t MCAN_GetTransmitErrorCounter(const MCAN_Type *MCANx);
uint8_t MCAN_GetReceiveMessageCounter(const MCAN_Type *MCANx);
void MCAN_ErrorSettingModify(MCAN_Type *MCANx, const MCAN_ErrorSettingDef *MCAN_ErrorSetting);
void MCAN_Enable(MCAN_Type* MCANx, FunctionalState NewState);
#ifdef __cplusplus
}
#endif

#endif   /*__XL_MCAN_H__ */

/**
  * @}
  */

/**
  * @}
  */
