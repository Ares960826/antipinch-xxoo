/**
  ******************************************************************************
  * @file     xl_spi.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the SPI 
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
#ifndef XL_SPI_H_
#define XL_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
/* Register define ------------------------------------------------------------*/
/* CTRLR0 Bit Fields */
#define SPI_CTRLR0_DFS_MASK                    0xFu
#define SPI_CTRLR0_DFS_SHIFT                   0
#define SPI_CTRLR0_SCPH_MASK                   0x40u
#define SPI_CTRLR0_SCPH_SHIFT                  6
#define SPI_CTRLR0_SCPOL_MASK                  0x80u
#define SPI_CTRLR0_SCPOL_SHIFT                 7
#define SPI_CTRLR0_TMOD_MASK                   0x300u
#define SPI_CTRLR0_TMOD_SHIFT                  8
#define SPI_CTRLR0_SLVOE_MASK                  0x400u
#define SPI_CTRLR0_SLVOE_SHIFT                 10
#define SPI_CTRLR0_SRL_MASK                    0x800u
#define SPI_CTRLR0_SRL_SHIFT                   11
	
/* CTRLR1 Bit Fields */
#define SPI_CTRLR1_NDF_MASK                    0xFFFFu
#define SPI_CTRLR1_NDF_SHIFT                   0

/* SPIENR Bit Fields */      
#define SPI_SPIENR_SPIE_MASK                   0x1u
#define SPI_SPIENR_SPIE_SHIFT                  0

/* SER Bit Fields */
#define SPI_SER_SSEF_MASK                      0x1u
#define SPI_SER_SSEF_SHIFT                     0

/* BAUDR Bit Fields */
#define SPI_BAUDR_SCKDV_MASK                   0xFFFFu
#define SPI_BAUDR_SCKDV_SHIFT                  0

/* TXFTLR Bit Fields */
#define SPI_TXFTLR_TFTL_MASK                   0xFu
#define SPI_TXFTLR_TFTL_SHIFT                  0

/* RXFTLR Bit Fields */
#define SPI_RXFTLR_RFTL_MASK                   0xFu
#define SPI_RXFTLR_RFTL_SHIFT                  0

/* TXFLR Bit Fields */
#define SPI_TXFLR_TFL_MASK                     0x1Fu
#define SPI_TXFLR_TFL_SHIFT                    0

/* RXFLR Bit Fields */
#define SPI_RXFLR_RFL_MASK                     0x1Fu
#define SPI_RXFLR_RFL_SHIFT                    0

 /* SR Bit Fields */
#define SPI_SR_BUSY_MASK                       0x1u
#define SPI_SR_BUSY_SHIFT                      0
#define SPI_SR_TFNF_MASK                       0x2u
#define SPI_SR_TFNF_SHIFT                      1
#define SPI_SR_TFE_MASK                        0x4u
#define SPI_SR_TFE_SHIFT                       2
#define SPI_SR_RFNE_MASK                       0x8u
#define SPI_SR_RFNE_SHIFT                      3
#define SPI_SR_RFF_MASK                        0x10u
#define SPI_SR_RFF_SHIFT                       4
#define SPI_SR_TXE_MASK                        0x20u
#define SPI_SR_TXE_SHIFT                       5
#define SPI_SR_DCOL_MASK                       0x40u
#define SPI_SR_DCOL_SHIFT                      6

 /* IMR Bit Fields */
#define SPI_IMR_TXEIM_MASK                     0x1u
#define SPI_IMR_TXEIM_SHIFT                    0
#define SPI_IMR_TXOIM_MASK                     0x2u
#define SPI_IMR_TXOIM_SHIFT                    1
#define SPI_IMR_RXUIM_MASK                     0x4u
#define SPI_IMR_RXUIM_SHIFT                    2
#define SPI_IMR_RXOIM_MASK                     0x8u
#define SPI_IMR_RXOIM_SHIFT                    3
#define SPI_IMR_RXFIM_MASK                     0x10u
#define SPI_IMR_RXFIM_SHIFT                    4

 /* ISR Bit Fields */
#define SPI_ISR_TXEIS_MASK                     0x1u
#define SPI_ISR_TXEIS_SHIFT                    0
#define SPI_ISR_TXOIS_MASK                     0x2u
#define SPI_ISR_TXOIS_SHIFT                    1
#define SPI_ISR_RXUIS_MASK                     0x4u
#define SPI_ISR_RXUIS_SHIFT                    2
#define SPI_ISR_RXOIS_MASK                     0x8u
#define SPI_ISR_RXOIS_SHIFT                    3
#define SPI_ISR_RXFIS_MASK                     0x10u
#define SPI_ISR_RXFIS_SHIFT                    4

 /* RISR Bit Fields */
#define SPI_RISR_TXEIR_MASK                    0x1u
#define SPI_RISR_TXEIR_SHIFT                   0
#define SPI_RISR_TXOIR_MASK                    0x2u
#define SPI_RISR_TXOIR_SHIFT                   1
#define SPI_RISR_RXUIR_MASK                    0x4u
#define SPI_RISR_RXUIR_SHIFT                   2
#define SPI_RISR_RXOIR_MASK                    0x8u
#define SPI_RISR_RXOIR_SHIFT                   3
#define SPI_RISR_RXFIR_MASK                    0x10u
#define SPI_RISR_RXFIR_SHIFT                   4

 /* TXOICR Bit Fields */
#define SPI_TXOICR_CTXOI_MASK                  0x1u
#define SPI_TXOICR_CTXOI_SHIFT                 0

 /* RXOICR Bit Fields */
#define SPI_RXOICR_CRXOI_MASK                  0x1u
#define SPI_RXOICR_CRXOI_SHIFT                 0

 /* RXUICR Bit Fields */
#define SPI_RXUICR_CRXUI_MASK                  0x1u
#define SPI_RXUICR_CRXUI_SHIFT                 0

 /* ICR Bit Fields */
#define SPI_ICR_CI_MASK                        0x1u
#define SPI_ICR_CI_SHIFT                       0

 /* DMACR Bit Fields */
#define SPI_DMACR_RDMAE_MASK                   0x1u
#define SPI_DMACR_RDMAE_SHIFT                  0
#define SPI_DMACR_TDMAE_MASK                   0x2u
#define SPI_DMACR_TDMAE_SHIFT                  1

 /* DMATDLR Bit Fields */
#define SPI_DMATDLR_DMATDL_MASK                0xFu
#define SPI_DMATDLR_DMATDL_SHIFT               0
#define SPI_DMATDLR_DMATDL_WIDTH               4

 /* DMARDLR Bit Fields */
#define SPI_DMARDLR_DMARDL_MASK                0xFu
#define SPI_DMARDLR_DMARDL_SHIFT               0

 /* DR Bit Fields */
#define SPI_DR_DR_MASK                         0xFFFFu
#define SPI_DR_DR_SHIFT                        0

 /* MODE Bit Fields */
#define SPI_MODE_MSTR_MASK                     0x1u
#define SPI_MODE_MSTR_SHIFT                    0

 /* MODE Bit Fields */
#define SPI_MODE_PACK_MASK                     0x2u
#define SPI_MODE_PACK_SHIFT                    1


/** SPI - Register Layout Typedef */
typedef struct {
 __IO uint32_t  CTRLR0;                          /*!< SPI控制寄存器0, offset:0x0*/
 __IO uint32_t  CTRLR1;                          /*!< SPI控制寄存器1, offset:0x04*/
 __IO uint32_t  SPIENR;                          /*!< SPI使能寄存器, offset:0x08*/
      uint32_t  RESERVED_0[1];                  
 __IO uint32_t  SER;                             /*!< SPI从机使能寄存器, offset:0x10*/
 __IO uint32_t  BAUDR;                           /*!< SPI波特率选择寄存器, offset:0x14*/
 __IO uint32_t  TXFTLR;                          /*!< SPI发送FIFO阈值设置寄存器, offset:0x18*/
 __IO uint32_t  RXFTLR;                          /*!< SPI接收FIFO阈值设置寄存器, offset:0x1C*/
 __I  uint32_t  TXFLR;                           /*!< SPI发送FIFO阈值寄存器, offset:0x20*/
 __I  uint32_t  RXFLR;                           /*!< SPI接收FIFO阈值寄存器, offset:0x24*/
 __I  uint32_t  SR;                              /*!< SPI状态寄存器, offset:0x28*/
 __IO uint32_t  IMR;                             /*!< SPI中断屏蔽寄存器, offset:0x2C*/
 __I  uint32_t  ISR;                             /*!< SPI中断状态寄存器, offset:0x30*/
 __I  uint32_t  RISR;                            /*!< SPI原始中断状态寄存器, offset:0x34*/
 __I  uint32_t  TXOICR;                          /*!< SPI发送FIFO溢出中断清零寄存器, offset:0x38*/
 __I  uint32_t  RXOICR;                          /*!< SPI接收FIFO溢出中断清零寄存器, offset:0x3C*/
 __I  uint32_t  RXUICR;                          /*!< SPI接收FIFO下溢中断清零寄存器, offset:0x40*/
      uint32_t  RESERVED_1[1];                 
 __I  uint32_t  ICR;                             /*!< SPI中断清零寄存器, offset:0x48*/
 __IO uint32_t  DMACR;                           /*!< SPI DMA控制寄存器, offset:0x4C*/
 __IO uint32_t  DMATDLR;                         /*!< SPI DMA发送数据水平寄存器, offset:0x50*/
 __IO uint32_t  DMARDLR;                         /*!< SPI DMA接收数据水平寄存器, offset:0x54*/
      uint32_t  RESERVED_2[1];                   
      uint32_t  RESERVED_3[1];                   
 __IO uint32_t  DR[36];                          /*!< SPI数据寄存器, array offset: 0x60, array step: 0x4*/\
 __IO uint32_t  DLY;                             /*!< SPI数据延迟采样寄存器, offset:0xF0*/
      uint32_t  RESERVED_4[1];									 			
			uint32_t  RESERVED_5[1];                  
      uint32_t  RESERVED_6[1];									
 __IO uint32_t  MODE;                            /*!< SPI模式选择寄存器, array offset: 0x100 */
} SPI_Type;	 
//} SPI_Type, *SPI_MemMapPtr;	
extern SPI_Type* SPI0;
extern SPI_Type* SPI1;	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup SPI 
  * @{
  */
	
/* Exported types ------------------------------------------------------------*/ 

/** 
	* @brief SPI主机初始化结构体
*/
typedef struct 
{	
		uint32_t      SPI_SourceClk;    					/*!< 时钟源 */
		uint32_t      SPI_BAUDR;       					 	/*!< 波特率选择      */
	  uint32_t      SPI_SRL;          					/*!< 移位寄存器循环 */
	  uint32_t      SPI_TMOD;         					/*!< 传输模式 */
	  uint32_t      SPI_SCPOL;        					/*!< 串行时钟极性 */
	  uint32_t      SPI_SCPH;         					/*!< 串行时钟相位 */
	  uint32_t      SPI_DFS;          					/*!< 数据帧大小 */
	  uint32_t      SPI_NDF;	        					/*!< 数据帧数量 */
	  uint32_t      SPI_TFT;          					/*!< 发送FIFO阈值 */
	  uint32_t      SPI_RFT;          					/*!< 接收FIFO阈值 */
}SPI_MsterInitTypeDef, *SPI_MsterInitConfigPtr;

/** 
	* @brief SPI从机初始化结构体
*/
typedef struct 
{	
	  FunctionalState   SPI_SLVOE;    					/*!< 从机输出使能 */
	  uint32_t          SPI_SRL;      					/*!< 移位寄存器循环 */
	  uint32_t          SPI_TMOD;     					/*!< 传输模式 */
	  uint32_t          SPI_SCPOL;    					/*!< 串行时钟极性 */
	  uint32_t          SPI_SCPH;     					/*!< 串行时钟相位 */
	  uint32_t          SPI_DFS;      					/*!< 数据帧大小 */
	  uint32_t          SPI_TFT;      					/*!< 发送FIFO阈值 */
	  uint32_t          SPI_RFT;      					/*!< 接收FIFO阈值 */
}SPI_SlaveInitTypeDef, *SPI_SlaveInitConfigPtr;	

/* Exported constants --------------------------------------------------------*/


/** @defgroup SPI_Exported_Constants SPI模块使用参数定义
  * @{
  */

/**
	* @defgroup SPI_Work_Mode SPI工作模式
	*	@brief 时钟源选择
	* @{
  */
#define SPI_SRL_NORMAL                    		((uint16_t)0x0000) /*!< 正常模式工作 */
#define SPI_SRL_TEST                      		((uint16_t)0x0800) /*!< 测试模式工作 */
/**
  * @}
*/

/**
	* @defgroup SPI_Transfer_Mode SPI传输模式
  * @{
  */
#define SPI_TransmitAndReceive            		((uint16_t)0x0000) /*!< 发送和接收 */
#define SPI_TransmitOnly                  		((uint16_t)0x0100) /*!< 仅发送 */
#define SPI_ReceiveOnly                   		((uint16_t)0x0200) /*!< 仅接收 */
#define SPI_EEPROMRead                    		((uint16_t)0x0300) /*!< EEPROM读取 */
/**
  * @}
*/

/**
	* @defgroup SPI_Serial_Clock_Polarity SPI时钟极性
  * @{
  */
#define SPI_SCPOL_Low                    		((uint16_t)0x0000) /*!< SPI时钟极性为低 */
#define SPI_SCPOL_High                   		((uint16_t)0x0080) /*!< SPI时钟极性位高 */
/**
  * @}
*/

/**
	* @defgroup SPI Serial Clock Phase
	*	@brief 时钟源选择
  * @{
  */
#define SPI_SCPH_Middle                 		((uint16_t)0x0000) /*!< 串行时钟在第一个数据位的中间切换 */
#define SPI_SCPH_Start                  		((uint16_t)0x0040) /*!< 串行时钟在第一个数据位开始时切换 */
/**
  * @}
*/

/**
	* @defgroup SPI_Data_Lenght SPI数据长度
  * @{
  */
#define SPI_DataSize_4b               		((uint16_t)0x0003) /*!< 4―位串行数据传输 */
#define SPI_DataSize_5b               		((uint16_t)0x0004) /*!< 5―位串行数据传输 */
#define SPI_DataSize_6b               		((uint16_t)0x0005) /*!< 6―位串行数据传输 */
#define SPI_DataSize_7b               		((uint16_t)0x0006) /*!< 7―位串行数据传输 */
#define SPI_DataSize_8b               		((uint16_t)0x0007) /*!< 8―位串行数据传输 */
#define SPI_DataSize_9b               		((uint16_t)0x0008) /*!< 9―位串行数据传输 */
#define SPI_DataSize_10b              		((uint16_t)0x0009) /*!< 10―位串行数据传输 */
#define SPI_DataSize_11b              		((uint16_t)0x000A) /*!< 11―位串行数据传输 */
#define SPI_DataSize_12b              		((uint16_t)0x000B) /*!< 12―位串行数据传输 */
#define SPI_DataSize_13b              		((uint16_t)0x000C) /*!< 13―位串行数据传输 */
#define SPI_DataSize_14b              		((uint16_t)0x000D) /*!< 14―位串行数据传输 */
#define SPI_DataSize_15b              		((uint16_t)0x000E) /*!< 15―位串行数据传输 */
#define SPI_DataSize_16b              		((uint16_t)0x000F) /*!< 16―位串行数据传输 */
/**
  * @}
*/

/**
	* @brief SPI_Mode SPI模式
  * @{
	*/
typedef enum
{
  SPI_MODE_MASTER = 0x00,        /*!< 主机模式 */
  SPI_MODE_SLAVE  = 0x01         /*!< 从机模式 */
	
}SPI_MODETypeDef;
/**
  * @}
*/

/**
	* @brief SPI_Data_Pack SPI传输包类型
	* @{
	*/
typedef enum
{
  SPI_PACK_CS_LOW  = 0x00,           /*!< 片选为低 */
  SPI_PACK_CS_HIGHT   = 0x01         /*!< 片选为高 */
	
}SPI_PACKCSTypeDef;
/**
  * @}
  */

/**
	* @brief SPI TxRx_FIFO_Level SPI发送/接收FIFO深度
  * @{
	*/
typedef enum
{
  SPI_TransmitFIFOLevel = 0x00,        /*!< 发送FIFO有效数据个数 */
  SPI_ReceiveFIFOLevel  = 0x01         /*!< 接收FIFO有效数据个数 */
	
}SPI_TXRXFIFOLevelDef;
/**
  * @}
	*/

/**
	* @brief SPI_Status SPI状态
  * @{
	*/
typedef enum 
{
		SPI_SPIBusyFlagStatus = 0,                  /*!< SPI繁忙标志位 */
		SPI_TransmitFIFONotFullStatus,              /*!< 发送FIFO未满 */
		SPI_TransmitFIFOEmptyStatus,                /*!< 发送FIFO为空 */
		SPI_ReceiveFIFONotEmptyStatus,              /*!< 接收FIFO不为空 */
		SPI_ReceiveFIFOFullStatus,                  /*!< 接收FIFO已满 */
		SPI_TransmissionErrorStatus,                /*!< 数据发送错误，只有SPI为从机时才能使用此功能 */	
		SPI_DataCollisionErrorStatus                /*!< 数据冲突错误，只有SPI为主机时才有此功能*/

}SPI_StatusTypeDef;
/**
  * @}
	*/

/**
	* @brief SPI_Interrupt_Status SPI中断状态
  * @{
	*/
typedef enum 
{
          SPI_TransmitFIFOEmptyIT = 0,         /*!< 发送FIFO已空的中断掩码 */
          SPI_TransmitFIFOOverflowIT,          /*!< 发送FIFO溢出的中断掩码 */
          SPI_ReceiveFIFOUnderflowIT,          /*!< 接收FIFO下溢的中断掩码 */
          SPI_ReceiveFIFOOverflowIT,           /*!< 接收FIFO溢出的中断掩码 */
          SPI_ReceiveFIFOFullIT    ,           /*!< 接收FIFO已满的中断掩码 */
					SPI_ALLIT   = 0xFu                   /*!< 所有掩码 */
}SPI_InterruptTypeDef;
/**
  * @}
	*/

/**
	* @brief SPI_Interrupt_Mask SPI中断屏蔽
  * @{
	*/
typedef enum 
{
	  SPI_TransmitFIFOEmptyITStatus = 0,          /*!< 发送FIFO已空的中断状态 */
	  SPI_TransmitFIFOOverflowITStatus,           /*!< 发送FIFO溢出的中断状态 */
	  SPI_ReceiveFIFOUnderflowITStatus,           /*!< 接收FIFO下溢的中断状态 */
	  SPI_ReceiveFIFOOverflowITStatus,            /*!< 接收FIFO溢出的中断状态 */
	  SPI_ReceiveFIFOFullITStatus                 /*!< 接收FIFO已满的中断状态 */
	 
}SPI_ITStatusMaskedDef;
/**
  * @}
	*/

/**
	* @brief SPI_Raw_Interrupt_Status SPI中断前状态
  * @{
	*/
typedef enum 
{
	  SPI_TransmitFIFOEmptyRawITStatus = 0,          /*!< 发送FIFO原始中断为空状态 */
	  SPI_TransmitFIFOOverflowRawITStatus,           /*!< 发送FIFO原始状态溢出状态 */
	  SPI_ReceiveFIFOUnderflowRawITStatus,           /*!< 接收FIFO原始中断下溢状态 */
	  SPI_ReceiveFIFOOverflowRawITStatus,            /*!< 接收FIFO原始中断溢出状态 */
	  SPI_ReceiveFIFOFullRawITStatus                 /*!< 接收FIFO原始中断已满状态 */
	 
}SPI_RawITStatusTypeDef;
/**
  * @}
	*/

/**
	* @brief SPI_Clear_Interrupt SPI清除中断标志
  * @{
	*/
typedef enum 
{
	  SPI_TransmitFIFOOverflowITClear  = 0,           /*!< 清空发送FIFO溢出中断寄存器 */
	  SPI_ReceiveFIFOOverflowITClear,                 /*!< 清空接收FIFO溢出中断寄存器 */
    SPI_ReceiveFIFOUnderflowITClear,                /*!< 清空接收FIFO下溢中断寄存器 */
	  SPI_ALLITClear                                  /*!< 清空所有中断状态 */

}SPI_InterruptClearDef;
/**
  * @}
	*/


/**
  * @}
*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void SPI_DeInit(SPI_Type *SPIx);
void SPI_SetMode(SPI_Type *SPIx,SPI_MODETypeDef SPI_MODEType);
void SPI_SetPackCS(SPI_Type *SPIx,SPI_PACKCSTypeDef SPI_PACKCSType);
void SPI_MasterInit(SPI_Type* SPIx, const SPI_MsterInitTypeDef *SPI_MasterInitStruct);
void SPI_SlaveInit(SPI_Type* SPIx,const SPI_SlaveInitTypeDef *SPI_SlaveInitStruct);
void SPI_EnableCmd(SPI_Type *SPIx,FunctionalState NewState);
void SPI_SlaveEnableCmd(SPI_Type *SPIx,FunctionalState NewState);
void SPI_SendData(SPI_Type *SPIx,uint16_t Data);
uint16_t SPI_ReceiveData(const SPI_Type *SPIx);
uint8_t SPI_GetFIFOLevel(const SPI_Type *SPIx,SPI_TXRXFIFOLevelDef FIFOLevelDef);
uint8_t SPI_GetStatus(const SPI_Type *SPIx,SPI_StatusTypeDef SPI_StatusType);
void SPI_InterruptEn(SPI_Type *SPIx, SPI_InterruptTypeDef SPI_Interrupt, FunctionalState NewState);
uint8_t SPI_ClearInterrupt(const SPI_Type *SPIx, SPI_InterruptClearDef SPI_Interrupt2Clear);
uint8_t SPI_GetIntMaskedStatus(const SPI_Type *SPIx,SPI_ITStatusMaskedDef SPI_IntStatusType);
uint8_t SPI_GetRawIntStatus(const SPI_Type *SPIx,SPI_RawITStatusTypeDef SPI_RawIntStatusType);
void SPI_SetDMATxDataLenght(SPI_Type *SPIx,uint8_t lenght);
void SPI_SetDMARxDataLenght(SPI_Type *SPIx,uint8_t lenght);
void SPI_DMATxEnableCmd(SPI_Type *SPIx,FunctionalState NewState);
void SPI_DMARxEnableCmd(SPI_Type *SPIx,FunctionalState NewState);
void SPI_DelaySampling(SPI_Type *SPIx,uint32_t nclock);
#ifdef __cplusplus
}
#endif

#endif /*__XL_SPI_H */
/**
  * @}
*/

/**
  * @}
*/
