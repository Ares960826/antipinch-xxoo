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
  __IO uint32_t CANMOD;                            /*!< MCAN模式寄存器, offset: 0x0 */
  __O  uint32_t CANCMR;                            /*!< MCAN命令寄存器, offset: 0x4 */
  __I  uint32_t CANSR;                             /*!< MCAN状态寄存器, offset: 0x8 */	
  __I  uint32_t CANIR;                             /*!< MCAN中断寄存器, offset: 0xc */	
  __IO uint32_t CANIER;                            /*!< MCAN中断使能寄存器, offset: 0x10 */	
  __IO uint32_t CANTDCS;                           /*!< MCAN延时补偿时间设置寄存器, offset: 0x14 */	
  __IO uint32_t CANBTR0;                           /*!< MCAN总线定时寄存器0, offset: 0x18 */
  __IO uint32_t CANBTR1;                           /*!< MCAN总线定时寄存器1, offset: 0x1c */
	__IO uint32_t CANFDBTR0;                         /*!< MCAN FD总线定时寄存器0, offset: 0x20 */
  __IO uint32_t CANFDBTR1;                         /*!< MCAN FD总线定时寄存器1, offset: 0x24 */
	     uint32_t RESERVED_0[1];
  __IO uint32_t CANHFC;                            /*!< FD接收帧变频补偿寄存器, offset: 0x2C */	
	     uint32_t RESERVED_1[1];		
  __I  uint32_t CANALC;                            /*!< MCAN仲裁丢失寄存器, offset: 0x34 */ 
  __I  uint32_t CANECC;                            /*!< MCAN错误码捕获寄存器, offset: 0x38 */
  __IO uint32_t CANEWLR;                           /*!< MCAN错误警告限制寄存器, offset: 0x3C */
  __IO uint32_t CANRXERR;                          /*!< MCAN 接收错误计数器, offset: 0x40 */
  __IO uint32_t CANTXERR;                          /*!< MCAN发送错误计数器, offset: 0x44 */
  union 
	{		
		__O uint32_t CANTB[69];                        /*!< MCAN发送缓冲器0, array offset: 0x48, array step: 0x4  */
		__I uint32_t CANRB[69];                        /*!< MCAN接收缓冲器0, array offset: 0x48, array step: 0x4  */
    struct
		{
			__IO uint32_t CANACR[4];                     /*!< MCAN验收码寄存器0, array offset: 0x48, array step: 0x4  */
			__IO uint32_t CANAMR[4];                     /*!< MCAN屏蔽码寄存器0, array offset: 0x58, array step: 0x4  */
			uint32_t RESERVED_2[61];	
		}CANAR; 
	};
			 uint32_t RESERVED_3[60];		
  __I  uint32_t CANRMC;                            /*!< MCAN接收报文计数器, offset: 0x24C*/
	     uint32_t RESERVED_4[258];	
  __I  uint32_t CANTB2R[69];                       /*!< MCAN发送缓冲器读取, offset: 0x658, array step: 0x4 */	

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
 * @brief MCAN 错误类型初始化结构体
 */
typedef struct
{
	uint8_t MCAN_ErrorWarningLimit ;     			/*!< 错误警告限制 */
	uint8_t MCAN_ReceiveErrorCount ;    			/*!< 接收错误计数器 */
	uint8_t MCAN_TranmitErrorCount ;     			/*!< 发送错误计数器 */	
}MCAN_ErrorSettingDef;

/**
 * @brief MCAN 初始化结构体
 */
typedef struct
{
	uint32_t MCAN_SJW;     		            			/*!< 同步跳转位宽 */
	uint32_t MCAN_BRP;					              	/*!< 波特率预分频器 */
	uint32_t MCAN_SAMP;				             			/*!< 采样 */
	uint32_t MCAN_TSEG2;				            		/*!< 时间段2 */
	uint32_t MCAN_TSEG1;					            	/*!< 时间段1 */
	uint32_t MCAN_FDSJW;     		            		/*!< CAN FD 同步跳转位宽 */
	uint32_t MCAN_FDBRP;					              /*!< CAN FD 波特率预分频器 */
	uint32_t MCAN_FDSAMP;				             		/*!< CAN FD 采样 */
	uint32_t MCAN_FDTSEG2;				            	/*!< CAN FD 时间段2 */
	uint32_t MCAN_FDTSEG1;					            /*!< CAN FD 时间段1 */
}MCAN_InitTypeDef;
   
/**
 * @brief MCAN 滤波初始化结构体
 */
typedef struct
{
	uint32_t MCAN_IDMode;		            				/*!< 标识符格式 */
	uint32_t MCAN_FiltMode;	                		/*!< 滤波模式，单滤波器或者双滤波器 */
	uint32_t MCAN_IDAR;		    	            		/*!< MCAN标识符 + 一位远程传输请求 */
	uint32_t MCAN_IDMR;		    	           			/*!< MCAN验收屏蔽 + 一位远程传输请求 */
	uint32_t MCAN_DIDAR;
	uint32_t MCAN_DIDMR;		 
}MCAN_FilterDef, *MCAN_FilterConfigPtr;

/** 
  * @brief  MCAN 发送接收信息初始化结构体
  */
typedef struct
{
  uint32_t MCAN_ID;                        		/*!< 标识符，11位标准帧或者29位拓展帧 */
  uint32_t MCAN_FDBRS;                      	/*!< 可变速率使能位, 仅操作于FD模式  */
  uint32_t MCAN_FDESI;                      	/*!< 错误状态位, 仅操作于FD模式    */	
  uint32_t MCAN_FF;                         	/*!< 帧格式  */
  uint32_t MCAN_RTR;                       		/*!< 远程传输请求    ，远程帧或者数据帧            */
  uint32_t MCAN_DLC;                        	/*!< 数据长度 */
  uint8_t MCAN_Data[64];                   		/*!< 包含的接收数据，范围是 0 到 63 */
                                             
} MCAN_MsgTypeDef, *MCAN_MsgConfigPtr;

/* Exported constants --------------------------------------------------------*/
/** @defgroup MCAN_Exported_Constants MCAN模块使用参数定义
  * @{
  */


/**  
	* @defgroup MCAN_Mode_List MCAN模式定义
  * @{
  */	
#define MCAN_NORMALMODE                   		0			/*!< 正常模式 */
#define MCAN_RESETMODE                    		1			/*!< 重置模式 */	
#define MCAN_LISTENONLYMODE               		2			/*!< 只听模式 */
#define MCAN_SELFTESTMODE                 		3			/*!< 自测模式 */
#define MCAN_SLEEPMODE                    		4			/*!< 睡眠模式 */
/** 
  * @} 
  */
	
/** 
	* @defgroup MCAN_synchronisation_jump_width MCAN同步跳转宽度定义
  * @{
  */	
#define MCAN_SJW_1tq                 					((uint8_t)0x00)  /*!< 1个Tq时钟周期 */
#define MCAN_SJW_2tq                 					((uint8_t)0x01)  /*!< 2个Tq时钟周期 */
#define MCAN_SJW_3tq                 					((uint8_t)0x02)  /*!< 3个Tq时钟周期 */
#define MCAN_SJW_4tq                 					((uint8_t)0x03)  /*!< 4个Tq时钟周期 */
/** 
  * @} 
  */
	
/** 
	* @defgroup MCAN_Sample_Times  MCAN采样时间定义
  * @{
  */	
#define MCAN_SAMPLE_1                					((uint8_t)0x00) /*!< 每位一个采样 */
#define MCAN_SAMPLE_3                					((uint8_t)0x01) /*!< 每位三个采样 */
/** 
  * @} 
  */

/** 
	* @defgroup MCAN_TSEG1_Select MCAN时间段2定义
  * @{
  */
#define MCAN_TSEG1_1tq                 				((uint8_t)0x00)  /*!< 1个Tq时钟周期 */	
#define MCAN_TSEG1_2tq                 				((uint8_t)0x01)  /*!< 2个Tq时钟周期 */	
#define MCAN_TSEG1_3tq                			 	((uint8_t)0x02)  /*!< 3个Tq时钟周期 */		
#define MCAN_TSEG1_4tq                 				((uint8_t)0x03)  /*!< 4个Tq时钟周期 */
#define MCAN_TSEG1_5tq                 				((uint8_t)0x04)  /*!< 5个Tq时钟周期 */
#define MCAN_TSEG1_6tq                 				((uint8_t)0x05)  /*!< 6个Tq时钟周期 */
#define MCAN_TSEG1_7tq                 				((uint8_t)0x06)  /*!< 7个Tq时钟周期 */
#define MCAN_TSEG1_8tq                 				((uint8_t)0x07)  /*!< 8个Tq时钟周期 */
#define MCAN_TSEG1_9tq                 				((uint8_t)0x08)  /*!< 9个Tq时钟周期 */
#define MCAN_TSEG1_10tq                				((uint8_t)0x09)  /*!< 10个Tq时钟周期 */
#define MCAN_TSEG1_11tq                				((uint8_t)0x0A)  /*!< 11个Tq时钟周期 */
#define MCAN_TSEG1_12tq                				((uint8_t)0x0B)  /*!< 12个Tq时钟周期 */
#define MCAN_TSEG1_13tq                				((uint8_t)0x0C)  /*!< 13个Tq时钟周期 */
#define MCAN_TSEG1_14tq                				((uint8_t)0x0D)  /*!< 14个Tq时钟周期 */
#define MCAN_TSEG1_15tq                				((uint8_t)0x0E)  /*!< 15个Tq时钟周期 */
#define MCAN_TSEG1_16tq                				((uint8_t)0x0F)  /*!< 16个Tq时钟周期 */
/** 
  * @} 
  */
	
	
/** 
	* @defgroup MCAN_TSEG2_Select MCAN时间段1定义
  * @{
  */
#define MCAN_TSEG2_1tq                 				((uint8_t)0x00)  /*!< 1个Tq时钟周期 */  //Nemo cmt
#define MCAN_TSEG2_2tq                 				((uint8_t)0x01)  /*!< 2个Tq时钟周期 */
#define MCAN_TSEG2_3tq                 				((uint8_t)0x02)  /*!< 3个Tq时钟周期 */
#define MCAN_TSEG2_4tq                 				((uint8_t)0x03)  /*!< 4个Tq时钟周期 */
#define MCAN_TSEG2_5tq                 				((uint8_t)0x04)  /*!< 5个Tq时钟周期 */
#define MCAN_TSEG2_6tq                 				((uint8_t)0x05)  /*!< 6个Tq时钟周期 */
#define MCAN_TSEG2_7tq                 				((uint8_t)0x06)  /*!< 7个Tq时钟周期 */
#define MCAN_TSEG2_8tq                 				((uint8_t)0x07)  /*!< 8个Tq时钟周期 */
/** 
  * @} 
  */
	
/** 
	* @defgroup MCAN_Filter_Scale  MCAN滤波选择定义
  * @{
  */
#define MCAN_Dual_Filter              			((uint8_t)0x00) /*!< 两个单独16位滤波器 */
#define MCAN_Single_Filter            			((uint8_t)0x01) /*!< 单个32位滤波器 */
/** 
  * @} 
  */
	
/** 
	* @defgroup MCAN_FDM_FRAME  MCANFD帧定义
  * @{
  */	
#define MCAN_FDM_NOMFrame             			((uint8_t)0x00) /*!< 发送帧为普通CAN数据帧          */
#define MCAN_FDM_FDFrame              			((uint8_t)0x01) /*!< 发送帧为CAN FD帧      */
/** 
  * @} 
  */     
	
/** 
	* @defgroup MCAN_BRS_Enable MCAN比特率转换
  * @{
  */	
#define MCAN_BRS_DISABLE              			((uint8_t)0x00) /*!< 相同未速率发送 */
#define MCAN_BRS_ENABLE               			((uint8_t)0x01) /*!< ESI 字段、DLC 字段、DATA 字段、CRC 字段使用高频速率发送 */
/** 
  * @} 
  */
	
	
/** 
	* @defgroup MCAN_ESI_Define MCAN错误检测
  * @{
  */		
#define MCAN_ESI_ACTIVE               			((uint8_t)0x00) /*!< 活动错误标志 */
#define MCAN_ESI_PASSIVE             			 	((uint8_t)0x01) /*!< 被动错误标志 */
/** 
  * @} 
  */

/** 
	* @defgroup MCAN_FRAME_FORMAT MCAN帧结构定义
  * @{
  */	
#define MCAN_Standard_Frame           			((uint8_t)0x00) /*!< 标准帧 */
#define MCAN_Extended_Frame           			((uint8_t)0x01) /*!< 拓展帧 */
#define MCAN_Custom_Frame						((uint8_t)0x02) /*!< 特定帧 */
/** 
  * @} 
  */
	
/** 
	* @defgroup MCAN_REMOTE_TYPE MCAN帧结构定义
  * @{
  */	
#define MCAN_RTR_Data                 			((uint8_t)0x00)  /*!< 数据帧 */
#define MCAN_RTR_Remote               			((uint8_t)0x01)  /*!< 远程帧 */
/** 
  * @} 
  */
	
	
/** 
	* @defgroup MCAN_DATA_LENGTH MCAN数据长度
  * @{
  */
#define MCAN_DLC_DATASIZE0            			((uint8_t)0x00)  /*!< 0字节数据长度 */
#define MCAN_DLC_DATASIZE1            			((uint8_t)0x01)  /*!< 1字节数据长度 */
#define MCAN_DLC_DATASIZE2            			((uint8_t)0x02)  /*!< 2字节数据长度 */
#define MCAN_DLC_DATASIZE3            			((uint8_t)0x03)  /*!< 3字节数据长度 */
#define MCAN_DLC_DATASIZE4            			((uint8_t)0x04)  /*!< 4字节数据长度 */
#define MCAN_DLC_DATASIZE5            			((uint8_t)0x05)  /*!< 5字节数据长度 */
#define MCAN_DLC_DATASIZE6            			((uint8_t)0x06)  /*!< 6字节数据长度 */
#define MCAN_DLC_DATASIZE7            			((uint8_t)0x07)  /*!< 7字节数据长度 */
#define MCAN_DLC_DATASIZE8            			((uint8_t)0x08)  /*!< 8字节数据长度 */
#define MCAN_DLC_DATASIZE12           			((uint8_t)0x09)  /*!< 12字节数据长度 */
#define MCAN_DLC_DATASIZE16           			((uint8_t)0x0A)  /*!< 16字节数据长度 */
#define MCAN_DLC_DATASIZE20           			((uint8_t)0x0B)  /*!< 20字节数据长度 */
#define MCAN_DLC_DATASIZE24           			((uint8_t)0x0C)  /*!< 24字节数据长度 */
#define MCAN_DLC_DATASIZE32           			((uint8_t)0x0D)  /*!< 32字节数据长度 */
#define MCAN_DLC_DATASIZE48           			((uint8_t)0x0E)  /*!< 48字节数据长度 */
#define MCAN_DLC_DATASIZE64           			((uint8_t)0x0F)  /*!< 64字节数据长度 */
/** 
  * @} 
  */

/** 
	* @defgroup MCAN_Bus_Error MCAN错误类型
  * @{
  */
typedef enum
{
  MCAN_BusErrorType = 0x00,             /*!< 位错误 */
  MCAN_BusErrorDirection  = 0x01,       /*!< 表单错误 */
  MCAN_BusErrorPosition = 0x02          /*!< 填充错误 */
}MCAN_BusErrorCaptureDef;
/** 
  * @} 
  */

/** 
	* @defgroup MCAN Command_Set MCAN 命令类型
  * @{
  */
#define MCAN_TransmissionRequest	 					0x01   	      		/*!< 发送请求 */
#define	MCAN_AbortTransmission							0x02             	/*!< 传输中止 */                   
#define	MCAN_ReleaseReceiveBuffer						0x04	          	/*!< 释放接收缓冲 */
#define	MCAN_ClearDataOverrun							0x08             	/*!< 清零数据溢出 */
#define	MCAN_SelfReceptionRequest						0x10             	/*!< 自接收请求 */
/** 
  * @} 
  */	

/** 
	* @defgroup MCAN_Status_SR  MCAN状态类型
  * @{
  */
typedef enum {
	MCAN_ReceiveBufferStatus= 0,          /*!< 接收缓冲区状态 */
	MCAN_DataOverrunStatus,               /*!< 数据溢出状态 */
	MCAN_TransBufferStatus,               /*!< 发送缓冲区状态 */
	MCAN_TransCompleteStatus,             /*!< 传输完成状态 */
	MCAN_ReceiveStatus,                   /*!< 接收状态 */
	MCAN_TransmitStatus,                  /*!< 发送状态 */
	MCAN_ErrorStatus,                     /*!< 错误状态 */
	MCAN_BusStatus	                      /*!< 总线状态 */
} MCAN_StatusTypeDef;
/** 
  * @} 
  */

/** 
	* @defgroup MCAN_Interrupt_ID MCAN中断ID
  * @{
  */
typedef enum {
	MCAN_ReceiveInterrupt= 0,             /*!< 接收中断 */
	MCAN_TransmitInterrupt,               /*!< 发送中断 */
	MCAN_ErrorWarningInterrupt,           /*!< 错误警告中断 */
	MCAN_DataOverrunInterrupt,            /*!< 数据溢出中断 */
	MCAN_WakeUpInterrupt,                 /*!< 唤醒中断 */
	MCAN_ErrorPassiveInterrupt,           /*!< 错误被动中断 */
	MCAN_ArbitrationLostInterrupt,        /*!< 仲裁丢失中断 */
	MCAN_BusErrorInterrupt                /*!< 总线错误中断 */
} MCAN_InterruptFlgDef;
/** 
  * @} 
  */

/** 
	* @defgroup MCAN_Interrupt_Enable MCAN中断使能
  * @{
  */
typedef enum {
	MCAN_ReceiveInterruptEn= 0,            /*!< 接收中断使能 */
	MCAN_TransmitInterruptEn,              /*!< 发送中断使能 */
	MCAN_ErrorWarningInterruptEn,          /*!< 错误警告中断使能 */
	MCAN_DataOverrunInterruptEn,           /*!< 数据溢出中断使能 */
	MCAN_WakeUpInterruptEn,                /*!< 唤醒中断使能 */
	MCAN_ErrorPassiveInterruptEn,          /*!< 错误被动中断使能 */
	MCAN_ArbitrationLostInterruptEn,       /*!< 仲裁丢失中断使能 */
	MCAN_BusErrorInterruptEn               /*!< 总线错误中断使能 */	
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
