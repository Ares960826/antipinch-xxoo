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
		__IO uint32_t        DMASRCADDRC;                       /*!< �ŵ�Դ��ַ�Ĵ��� */
		__IO uint32_t        DMADSTADDRC;                       /*!< ͨ��Ŀ�ĵ�ַ�Ĵ��� */
		__IO uint32_t        DMACTRLC;                      		/*!< ͨ�����ƼĴ��� */
		__IO uint32_t        DMASTATUSC;                      	/*!< ͨ��״̬�Ĵ��� */
	}DMACHANREG[4];
	__IO uint32_t		DMAEN;                                    /*!< DMA ʹ�ܼĴ��� */
	__IO uint32_t		DMASRST;                                  /*!< DMA ��λ�Ĵ��� */
	__IO uint32_t		DMAINTSTATUS;                             /*!< �ж�״̬/�ж�����Ĵ��� */
	__IO uint32_t		DMAINTMASK;                               /*!< �ж����μĴ��� */
	__I uint32_t		DMAPERREQ;                                /*!< ��������״̬�Ĵ��� */
	
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
  * @brief DMA��ʼ���ṹ�嶨��
  */
typedef struct
{
	uint8_t chan;                               /*!< �ŵ� */
	uint8_t TargetBurst;                        /*!< ����һ�����ߣ��յ������� */
	uint8_t SourceBurst;                        /*!< ����һ�����ߣ����͵����� */
	uint8_t TargetWidth;                        /*!< Ŀ��һ�����ݵ�bit */
	uint8_t SourceWidth;                        /*!< Դһ�����ݵ�bit */
	uint16_t TransferSize;                      /*!< �������ݵĴ�С */
	uint8_t FlowControl;                        /*!< Ŀ���豸ID */
	uint8_t TargetPerID;                        /*!< Ŀ���豸ID */
	uint8_t SourcePerID;                        /*!< Դ�豸ID */
	uint8_t TargetAddrInc;                      /*!< Ŀ�ĵ�ַ����ʹ��λ */
	uint8_t SourceAddrInc;                      /*!< Դ��ַ����ʹ��λ */
}DMA_InitTypeDef;
extern DMA_Type *DMA;

/* Exported constants --------------------------------------------------------*/
/** @defgroup DMA_Exported_Constants DMAģ��ʹ�ò�������
  * @{
  */ 	

/** @defgroup DMA_Channel_Num DMAͨ��
  * @{
  */
typedef enum
{
	DMA_Channel_0 = 0,       /*!< DMAͨ��0 */
	DMA_Channel_1 ,          /*!< DMAͨ��1 */
	DMA_Channel_2 ,          /*!< DMAͨ��2 */
	DMA_Channel_3 ,          /*!< DMAͨ��3 */
}DMA_Channel_Num;
/**
  * @}
  */

/** @defgroup DMA_TargetData_Burst DMAĿ�Ĳ�������Burstѡ��
  * @{
  */
typedef enum
{
	DMA_TargetBurst1 = 0,          /*!< Ŀ�Ĳ�������BurstΪ1 */
	DMA_TargetBurst2,              /*!< Ŀ�Ĳ�������BurstΪ2 */
	DMA_TargetBurst4,              /*!< Ŀ�Ĳ�������BurstΪ4 */
	DMA_TargetBurst8,              /*!< Ŀ�Ĳ�������BurstΪ8 */
	DMA_TargetBurst16,             /*!< Ŀ�Ĳ�������BurstΪ16 */
	DMA_TargetBurst32              /*!< Ŀ�Ĳ�������BurstΪ32 */
}DMA_TargetBurstDef;
/**
  * @}
  */


/** @defgroup DMA_SourceData_Burst DMAԴ��������Burstѡ��
  * @{
  */
typedef enum
{
	DMA_SourceBurst1 = 0,         /*!< Դ��������BurstΪ1 */
	DMA_SourceBurst2,             /*!< Դ��������BurstΪ2 */
	DMA_SourceBurst4,             /*!< Դ��������BurstΪ4 */
	DMA_SourceBurst8,             /*!< Դ��������BurstΪ8 */
	DMA_SourceBurst16,            /*!< Դ��������BurstΪ16 */
	DMA_SourceBurst32             /*!< Դ��������BurstΪ32 */
}DMA_SourceBurstDef;
/**
  * @}
  */

/** @defgroup DMA_TargetData_Width DMAĿ�Ĳ�������λ��ѡ��
  * @{
  */
typedef enum
{
	DMA_TargetWidth8 = 0,             /*!< Ŀ���������λ��8λ */
	DMA_TargetWidth16,                /*!< Ŀ���������λ��16λ */
	DMA_TargetWidth32,                /*!< Ŀ���������λ��32λ */
	DMA_TargetWidth32_1,              /*!< Ŀ���������λ��32λ */
}DMA_TargetWidthDef;
/**
  * @}
  */
	
/** @defgroup DMA_SourceData_Width DMAԴ��������λ��ѡ��
  * @{
  */
typedef enum
{
	DMA_SourceWidth8 = 0,           /*!< Դ��������λ��8λ */
	DMA_SourceWidth16,              /*!< Դ��������λ��16λ */
	DMA_SourceWidth32,              /*!< Դ��������λ��32λ */
	DMA_SourceWidth32_1,            /*!< Դ��������λ��32λ */
}DMA_SourceWidthDef;
/**
  * @}
  */

/** @defgroup DMA_Flow_Control DMA���䷽ʽѡ��
  * @{
  */
typedef enum
{ 
	DMA_MemoryToMemory = 0,                /*!< �洢�����洢�� */
	DMA_MemoryToPeripheral ,               /*!< �洢�������� */
	DMA_PeripheralToMemory ,               /*!< ���赽�洢�� */
	DMA_PeripheralToPeripheral ,           /*!< ���赽���� */
}DMA_FlowControlDef;
/**
  * @}
  */


/** @defgroup DMA_Peripheral_ID DMAĿ������IDѡ��
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

/** @defgroup DMA_Address_Add DMA��ַ����
  * @{
  */
typedef enum
{
	DMA_AddressNoAdd = 0,                  /*!< ��ַ���ֲ��� */         
	DMA_AddressAdd ,                       /*!< ��ַ���� */ 
}DMA_AddrIncDef;

/**
  * @}
  */

/** @defgroup DMA_Interrupt_Status DMA�ж�״̬�����
  * @{
  */
typedef enum
{
	DMA_Channel0_Err = 0,                 /*!< DMAͨ��0�����ж� */        
	DMA_Channel1_Err,                     /*!< DMAͨ��0�����ж� */ 
	DMA_Channel2_Err,                     /*!< DMAͨ��0�����ж� */ 
	DMA_Channel3_Err,                     /*!< DMAͨ��0�����ж� */ 
	DMA_Channel0_TransferFinish,          /*!< DMAͨ��0��������ж� */            
	DMA_Channel1_TransferFinish,          /*!< DMAͨ��0��������ж� */         
	DMA_Channel2_TransferFinish,          /*!< DMAͨ��0��������ж� */
	DMA_Channel3_TransferFinish,          /*!< DMAͨ��0��������ж� */
	DMA_ClearALL_Status = 0xFF            /*!< �������DMA�ж�״̬ */
}DMA_InterruptStatusDef;
/**
  * @}
  */

/** @defgroup DMA_Interrupt_Mask DMA�ж�����
  * @{
  */
typedef enum
{
	DMA_Channel0_Err_Mask = 0,                 /*!< DMAͨ��0�����ж����� */ 
	DMA_Channel1_Err_Mask,                     /*!< DMAͨ��1�����ж����� */
	DMA_Channel2_Err_Mask,                     /*!< DMAͨ��2�����ж����� */
	DMA_Channel3_Err_Mask,                     /*!< DMAͨ��3�����ж����� */
	DMA_Channel0_TransferFinish_Mask,          /*!< DMAͨ��0��������ж����� */
	DMA_Channel1_TransferFinish_Mask,          /*!< DMAͨ��1��������ж����� */
	DMA_Channel2_TransferFinish_Mask,          /*!< DMAͨ��2��������ж����� */
	DMA_Channel3_TransferFinish_Mask,          /*!< DMAͨ��3��������ж����� */
}DMA_InterruptMaskDef;
/**
  * @}
  */


/** @defgroup DMA_Peripheral_ResquestDef DMA��������״̬
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

/** @defgroup DMA_Chan_Status DMAͨ��״̬
  * @{
  */
typedef enum
{
	DMA_Chan_Idle = 0,               /*!< DMAͨ������ */ 
	DMA_Chan_Busy                    /*!< DMAͨ��æ */ 
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

