/**
  ******************************************************************************
  * @file     xl_dma.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the DMA 
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
#ifndef XL_DMA_H_
#define XL_DMA_H_

#ifdef __cplusplus
extern "C" {
#endif
	
/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"

/* Register define ------------------------------------------------------------*/
#define DMA_DMACTRLC_DBURSTC_MASK                       0xE0000000u
#define DMA_DMACTRLC_DBURSTC_SHIFT                      29u

#define DMA_DMACTRLC_SBURSTC_MASK                       0x1C000000u
#define DMA_DMACTRLC_SBURSTC_SHIFT                      26u

#define DMA_DMACTRLC_DWIDTHC_MASK                       0x03000000u
#define DMA_DMACTRLC_DWIDTHC_SHIFT                      24u

#define DMA_DMACTRLC_SWIDTHC_MASK                       0x00C00000u
#define DMA_DMACTRLC_SWIDTHC_SHIFT                      22u

#define DMA_DMACTRLC_TRANSIZEC_MASK                     0x003FE000u
#define DMA_DMACTRLC_TRANSIZEC_SHIFT                    13u

#define DMA_DMACTRLC_FLOWCTRLC_MASK                     0x00001800u
#define DMA_DMACTRLC_FLOWCTRLC_SHIFT                    11u

#define DMA_DMACTRLC_DSTPERC_MASK                       0x00000780u
#define DMA_DMACTRLC_DSTPERC_SHIFT                      7u

#define DMA_DMACTRLC_SRCPERC_MASK                       0x00000078u
#define DMA_DMACTRLC_SRCPERC_SHIFT                      3u

#define DMA_DMACTRLC_DSTINCC_MASK                       0x00000004u
#define DMA_DMACTRLC_DSTINCC_SHIFT                      2u

#define DMA_DMACTRLC_SRCINCC_MASK                       0x00000002u
#define DMA_DMACTRLC_SRCINCC_SHIFT                      1u

#define DMA_DMACTRLC_CHENC_MASK                       	0x00000001u
#define DMA_DMACTRLC_CHENC_SHIFT                      	0u

#define DMA_DMASTATUSC_TRANSLENGTH_MASK                 0x0000007FEu
#define DMA_DMASTATUSC_TRANSLENGTH_SHIFT                1u

#define DMA_DMASTATUSC_BUSY_MASK                        0x00000001u
#define DMA_DMASTATUSC_BUSY_SHIFT                       0u

#define DMA_DMAEN_DMAEN_MASK                       		0x00000001u
#define DMA_DMAEN_DMAEN_SHIFT                      		0u

#define DMA_DMASRST_DMASRST_MASK                       	0x00000001u
#define DMA_DMASRST_DMASRST_SHIFT                      	0u

#define DMA_DMAINTSTATUS_INTCC3_MASK                    0x00000080u
#define DMA_DMAINTSTATUS_INTCC3_SHIFT                   7u

#define DMA_DMAINTSTATUS_INTCC2_MASK                    0x00000040u
#define DMA_DMAINTSTATUS_INTCC2_SHIFT                   6u

#define DMA_DMAINTSTATUS_INTCC1_MASK                    0x00000020u
#define DMA_DMAINTSTATUS_INTCC1_SHIFT                   5u

#define DMA_DMAINTSTATUS_INTCC0_MASK                    0x00000010u
#define DMA_DMAINTSTATUS_INTCC0_SHIFT                   4u

#define DMA_DMAINTSTATUS_INTERRC3_MASK                  0x00000008u
#define DMA_DMAINTSTATUS_INTERRC3_SHIFT                 3u

#define DMA_DMAINTSTATUS_INTERRC2_MASK                  0x00000004u
#define DMA_DMAINTSTATUS_INTERRC2_SHIFT                 2u

#define DMA_DMAINTSTATUS_INTERRC1_MASK                  0x00000002u
#define DMA_DMAINTSTATUS_INTERRC1_SHIFT                 1u

#define DMA_DMAINTSTATUS_INTERRC0_MASK                  0x00000001u
#define DMA_DMAINTSTATUS_INTERRC0_SHIFT                 0u

#define DMA_DMAINTMASK_MASKTCC3_MASK                    0x00000080u
#define DMA_DMAINTMASK_MASKTCC3_SHIFT                   7u

#define DMA_DMAINTMASK_MASKTCC2_MASK                    0x00000040u
#define DMA_DMAINTMASK_MASKTCC2_SHIFT                   6u

#define DMA_DMAINTMASK_MASKTCC1_MASK                    0x00000020u
#define DMA_DMAINTMASK_MASKTCC1_SHIFT                   5u

#define DMA_DMAINTMASK_MASKTCC0_MASK                    0x00000010u
#define DMA_DMAINTMASK_MASKTCC0_SHIFT                   4u

#define DMA_DMAINTMASK_MASKERRC3_MASK                   0x00000008u
#define DMA_DMAINTMASK_MASKERRC3_SHIFT                  3u

#define DMA_DMAINTMASK_MASKERRC2_MASK                   0x00000004u
#define DMA_DMAINTMASK_MASKERRC2_SHIFT                  2u

#define DMA_DMAINTMASK_MASKERRC1_MASK                   0x00000002u
#define DMA_DMAINTMASK_MASKERRC1_SHIFT                  1u

#define DMA_DMAINTMASK_MASKERRC0_MASK                   0x00000001u
#define DMA_DMAINTMASK_MASKERRC0_SHIFT                  0u


#define DMA_DMAPERREQ_ADCRXREQ_MASK                     0x00000800u
#define DMA_DMAPERREQ_ADCRXREQ_SHIFT                    11u

#define DMA_DMAPERREQ_ADCTXREQ_MASK                     0x00000400u
#define DMA_DMAPERREQ_ADCTXREQ_SHIFT                    10u

#define DMA_DMAPERREQ_UART2RXREQ_MASK                   0x00000200u
#define DMA_DMAPERREQ_UART2RXREQ_SHIFT                  9u

#define DMA_DMAPERREQ_UART2TXREQ_MASK                   0x00000100u
#define DMA_DMAPERREQ_UART2TXREQ_SHIFT                  8u

#define DMA_DMAPERREQ_UART1RXREQ_MASK                   0x00000080u
#define DMA_DMAPERREQ_UART1RXREQ_SHIFT                  7u

#define DMA_DMAPERREQ_UART1TXREQ_MASK                   0x00000040u
#define DMA_DMAPERREQ_UART1TXREQ_SHIFT                  6u

#define DMA_DMAPERREQ_UART0RXREQ_MASK                   0x00000020u
#define DMA_DMAPERREQ_UART0RXREQ_SHIFT                  5u

#define DMA_DMAPERREQ_UART0TXREQ_MASK                   0x00000010u
#define DMA_DMAPERREQ_UART0TXREQ_SHIFT                  4u

#define DMA_DMAPERREQ_SPI0RXREQ_MASK                    0x00000008u
#define DMA_DMAPERREQ_SPI0RXREQ_SHIFT                   3u

#define DMA_DMAPERREQ_SPI0TXREQ_MASK                    0x00000004u
#define DMA_DMAPERREQ_SPI0TXREQ_SHIFT                   2u

#define DMA_DMAPERREQ_SPI1RXREQ_MASK                    0x00000002u
#define DMA_DMAPERREQ_SPI1RXREQ_SHIFT                   1u

#define DMA_DMAPERREQ_SPI1TXREQ_MASK                    0x00000001u
#define DMA_DMAPERREQ_SPI1TXREQ_SHIFT                   0u
	
/** DMA - Register Layout Typedef */
typedef struct{
	struct {
		__IO uint32_t        DMASRCADDRC;                       /*!< 信道源地址寄存器 */
		__IO uint32_t        DMADSTADDRC;                       /*!< 通道目的地址寄存器 */
		__IO uint32_t        DMACTRLC;                      		/*!< 通道控制寄存器 */
		__IO uint32_t        DMASTATUSC;                      	/*!< 通道状态寄存器 */
	}DMACHANREG[4];
	__IO uint32_t		DMAEN;                                    /*!< DMA 使能寄存器 */
	__IO uint32_t		DMASRST;                                  /*!< DMA 软复位寄存器 */
	__IO uint32_t		DMAINTSTATUS;                             /*!< 中断状态/中断清除寄存器 */
	__IO uint32_t		DMAINTMASK;                               /*!< 中断屏蔽寄存器 */
	__I uint32_t		DMAPERREQ;                                /*!< 外设请求状态寄存器 */
	
} DMA_Type;
extern DMA_Type *DMA;

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup DMA 
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 
/** 
  * @brief DMA初始化结构体定义
  */
typedef struct
{
	uint8_t chan;                               /*!< 信道 */
	uint8_t TargetBurst;                        /*!< 申请一次总线，收到的数据 */
	uint8_t SourceBurst;                        /*!< 申请一次总线，发送的数据 */
	uint8_t TargetWidth;                        /*!< 目标一个数据的bit */
	uint8_t SourceWidth;                        /*!< 源一个数据的bit */
	uint16_t TransferSize;                      /*!< 传输数据的大小 */
	uint8_t FlowControl;                        /*!< 目标设备ID */
	uint8_t TargetPerID;                        /*!< 目标设备ID */
	uint8_t SourcePerID;                        /*!< 源设备ID */
	uint8_t TargetAddrInc;                      /*!< 目的地址递增使能位 */
	uint8_t SourceAddrInc;                      /*!< 源地址递增使能位 */
}DMA_InitTypeDef;
extern DMA_Type *DMA;

/* Exported constants --------------------------------------------------------*/
/** @defgroup DMA_Exported_Constants DMA模块使用参数定义
  * @{
  */ 	

/** @defgroup DMA_Channel_Num DMA通道
  * @{
  */
typedef enum
{
	DMA_Channel_0 = 0,       /*!< DMA通道0 */
	DMA_Channel_1 ,          /*!< DMA通道1 */
	DMA_Channel_2 ,          /*!< DMA通道2 */
	DMA_Channel_3 ,          /*!< DMA通道3 */
}DMA_Channel_Num;
/**
  * @}
  */

/** @defgroup DMA_TargetData_Burst DMA目的操作数据Burst选择
  * @{
  */
typedef enum
{
	DMA_TargetBurst1 = 0,          /*!< 目的操作数据Burst为1 */
	DMA_TargetBurst2,              /*!< 目的操作数据Burst为2 */
	DMA_TargetBurst4,              /*!< 目的操作数据Burst为4 */
	DMA_TargetBurst8,              /*!< 目的操作数据Burst为8 */
	DMA_TargetBurst16,             /*!< 目的操作数据Burst为16 */
	DMA_TargetBurst32              /*!< 目的操作数据Burst为32 */
}DMA_TargetBurstDef;
/**
  * @}
  */


/** @defgroup DMA_SourceData_Burst DMA源操作数据Burst选择
  * @{
  */
typedef enum
{
	DMA_SourceBurst1 = 0,         /*!< 源操作数据Burst为1 */
	DMA_SourceBurst2,             /*!< 源操作数据Burst为2 */
	DMA_SourceBurst4,             /*!< 源操作数据Burst为4 */
	DMA_SourceBurst8,             /*!< 源操作数据Burst为8 */
	DMA_SourceBurst16,            /*!< 源操作数据Burst为16 */
	DMA_SourceBurst32             /*!< 源操作数据Burst为32 */
}DMA_SourceBurstDef;
/**
  * @}
  */

/** @defgroup DMA_TargetData_Width DMA目的操作数据位宽选择
  * @{
  */
typedef enum
{
	DMA_TargetWidth8 = 0,             /*!< 目标操作数据位宽8位 */
	DMA_TargetWidth16,                /*!< 目标操作数据位宽16位 */
	DMA_TargetWidth32,                /*!< 目标操作数据位宽32位 */
	DMA_TargetWidth32_1,              /*!< 目标操作数据位宽32位 */
}DMA_TargetWidthDef;
/**
  * @}
  */
	
/** @defgroup DMA_SourceData_Width DMA源操作数据位宽选择
  * @{
  */
typedef enum
{
	DMA_SourceWidth8 = 0,           /*!< 源操作数据位宽8位 */
	DMA_SourceWidth16,              /*!< 源操作数据位宽16位 */
	DMA_SourceWidth32,              /*!< 源操作数据位宽32位 */
	DMA_SourceWidth32_1,            /*!< 源操作数据位宽32位 */
}DMA_SourceWidthDef;
/**
  * @}
  */

/** @defgroup DMA_Flow_Control DMA传输方式选择
  * @{
  */
typedef enum
{ 
	DMA_MemoryToMemory = 0,                /*!< 存储器到存储器 */
	DMA_MemoryToPeripheral ,               /*!< 存储器到外设 */
	DMA_PeripheralToMemory ,               /*!< 外设到存储器 */
	DMA_PeripheralToPeripheral ,           /*!< 外设到外设 */
}DMA_FlowControlDef;
/**
  * @}
  */


/** @defgroup DMA_Peripheral_ID DMA目的外设ID选择
  * @{
  */
typedef enum
{
	DMA_SPI1_Tx = 0,
	DMA_SPI1_Rx,
	DMA_SPI0_Tx,
	DMA_SPI0_Rx,
	DMA_UART0_Tx,
	DMA_UART0_Rx,
	DMA_UART1_Tx,
	DMA_UART1_Rx,
	DMA_UART2_Tx,
	DMA_UART2_Rx,
	DMA_ADC_Tx,
	DMA_ADC_Rx,
	DMA_Reserver0,
	DMA_Reserver1,
	DMA_Reserver2,
	DMA_Reserver3,
}DMA_Peripheral_IDDef;
/**
  * @}
  */

/** @defgroup DMA_Address_Add DMA地址自增
  * @{
  */
typedef enum
{
	DMA_AddressNoAdd = 0,                  /*!< 地址保持不变 */         
	DMA_AddressAdd ,                       /*!< 地址递增 */ 
}DMA_AddrIncDef;

/**
  * @}
  */

/** @defgroup DMA_Interrupt_Status DMA中断状态及清除
  * @{
  */
typedef enum
{
	DMA_Channel0_Err = 0,                 /*!< DMA通道0错误中断 */        
	DMA_Channel1_Err,                     /*!< DMA通道0错误中断 */ 
	DMA_Channel2_Err,                     /*!< DMA通道0错误中断 */ 
	DMA_Channel3_Err,                     /*!< DMA通道0错误中断 */ 
	DMA_Channel0_TransferFinish,          /*!< DMA通道0传输完成中断 */            
	DMA_Channel1_TransferFinish,          /*!< DMA通道0传输完成中断 */         
	DMA_Channel2_TransferFinish,          /*!< DMA通道0传输完成中断 */
	DMA_Channel3_TransferFinish,          /*!< DMA通道0传输完成中断 */
	DMA_ClearALL_Status = 0xFF            /*!< 清除所有DMA中断状态 */
}DMA_InterruptStatusDef;
/**
  * @}
  */

/** @defgroup DMA_Interrupt_Mask DMA中断屏蔽
  * @{
  */
typedef enum
{
	DMA_Channel0_Err_Mask = 0,                 /*!< DMA通道0错误中断屏蔽 */ 
	DMA_Channel1_Err_Mask,                     /*!< DMA通道1错误中断屏蔽 */
	DMA_Channel2_Err_Mask,                     /*!< DMA通道2错误中断屏蔽 */
	DMA_Channel3_Err_Mask,                     /*!< DMA通道3错误中断屏蔽 */
	DMA_Channel0_TransferFinish_Mask,          /*!< DMA通道0传输完成中断屏蔽 */
	DMA_Channel1_TransferFinish_Mask,          /*!< DMA通道1传输完成中断屏蔽 */
	DMA_Channel2_TransferFinish_Mask,          /*!< DMA通道2传输完成中断屏蔽 */
	DMA_Channel3_TransferFinish_Mask,          /*!< DMA通道3传输完成中断屏蔽 */
}DMA_InterruptMaskDef;
/**
  * @}
  */


/** @defgroup DMA_Peripheral_ResquestDef DMA外设请求状态
  * @{
  */
typedef enum
{
	DMA_SPI1_Tx_Req = 0,
	DMA_SPI1_Rx_Req,
	DMA_SPI0_Tx_Req,
	DMA_SPI0_Rx_Req,
	DMA_UART0_Tx_Req,
	DMA_UART0_Rx_Req,
	DMA_UART1_Tx_Req,
	DMA_UART1_Rx_Req,
	DMA_UART2_Tx_Req,
	DMA_UART2_Rx_Req,
	DMA_ADC_Tx_Req,
	DMA_ADC_Rx_Req,
}DMA_Peripheral_ResquestDef;
/**
  * @}
  */

/** @defgroup DMA_Chan_Status DMA通道状态
  * @{
  */
typedef enum
{
	DMA_Chan_Idle = 0,               /*!< DMA通道空闲 */ 
	DMA_Chan_Busy                    /*!< DMA通道忙 */ 
}DMA_Chan_Status;
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void DMA_ChannelInit(const DMA_InitTypeDef *DMA_InitStruct);
void DMA_Enable(FunctionalState NewState);
void DMA_ChannelEnableCmd(uint8_t Channel,FunctionalState NewState);
void DMA_SetSourceAddress(uint8_t Channel,uint32_t address);
void DMA_SetTargetAddress(uint8_t Channel,uint32_t address);
void DMA_SetTransferSize(uint8_t channel,uint16_t len);
uint8_t DMA_GetChannelStatus(uint8_t Channel);
uint16_t DMA_GetChanTransferDataLen(uint8_t Channel);
uint8_t DMA_GetInterruptStatus(uint8_t DMA_InterruptStatusType);
void DMA_ClearInterruptStatus(const uint8_t DMA_InterruptStatusType);
void DMA_InterruptEnable(uint8_t DMA_InterruptMaskType,FunctionalState NewState);
uint32_t DMA_GetPeripheralResquestStatus(const uint8_t DMA_Peripheral_ResquestType);
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

