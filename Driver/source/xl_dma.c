/**
  ******************************************************************************
  * @file     xl_dma.c
  * @author   xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about DMA firmware program 
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

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
/* Includes ---------------------------------------------------------------*/
#include "xl_dma.h"

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup DMA   DMA Module
  * @brief DMA Driver Modules Library
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
	
/** @defgroup DMA_Private_Functions 
* @{
*/ 

/**
 * @brief  ����DMA ͨ���ĳ�ʼ��
 * @param  DMAx: DMA����
 * @param  DMA_InitStruct: DMA��ʼ�������ṹ��
 * @retval None
 */
void DMA_ChannelInit(const DMA_InitTypeDef *DMA_InitStruct)
{
	uint32_t temp;
	
	temp =	(uint32_t)(((uint32_t)DMA_InitStruct->TargetBurst<<DMA_DMACTRLC_DBURSTC_SHIFT)    | ((uint32_t)DMA_InitStruct->SourceBurst<<DMA_DMACTRLC_SBURSTC_SHIFT) | \
					((uint32_t)DMA_InitStruct->TargetWidth<<DMA_DMACTRLC_DWIDTHC_SHIFT)    | ((uint32_t)DMA_InitStruct->SourceWidth<<DMA_DMACTRLC_SWIDTHC_SHIFT) |  \
					((uint32_t)DMA_InitStruct->TransferSize<<DMA_DMACTRLC_TRANSIZEC_SHIFT) | ((uint32_t)DMA_InitStruct->FlowControl<<DMA_DMACTRLC_FLOWCTRLC_SHIFT) |  \
					((uint32_t)DMA_InitStruct->TargetPerID<<DMA_DMACTRLC_DSTPERC_SHIFT)    | ((uint32_t)DMA_InitStruct->SourcePerID<<DMA_DMACTRLC_SRCPERC_SHIFT) |  \
					((uint32_t)DMA_InitStruct->TargetAddrInc<<DMA_DMACTRLC_DSTINCC_SHIFT)  | ((uint32_t)DMA_InitStruct->SourceAddrInc<<DMA_DMACTRLC_SRCINCC_SHIFT));
	
	DMA->DMACHANREG[DMA_InitStruct->chan].DMACTRLC = temp;
}
/**
 * @brief  DMAʹ��
 * @param  DMAx: DMA����
 * @param  NewState: ״̬ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISENABLE ��ʧ��
 * @retval None
 */
void DMA_Enable(FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
			DMA->DMAEN = 0x444D4145;
	}
	else 
	{
			DMA->DMASRST = 0x53525354;
	}
}
/**
 * @brief  DMAͨ��ʹ��
 * @param  DMAx: DMA����
 * @param  Channel: DMAͨ��
 *		�����������ȡ�����ֵ:
 *			@arg DMA_Channel_0 ��DMAͨ��0
 *			@arg DMA_Channel_1 ��DMAͨ��1
 *			@arg DMA_Channel_2 ��DMAͨ��2
 *			@arg DMA_Channel_3 ��DMAͨ��3
 * @param  NewState: ״̬ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISENABLE ��ʧ��
 * @retval None
 */

void DMA_ChannelEnableCmd(uint8_t Channel,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
			DMA->DMACHANREG[Channel].DMACTRLC |= DMA_DMAEN_DMAEN_MASK;
	}
	else 
	{
			DMA->DMACHANREG[Channel].DMACTRLC &= ~DMA_DMAEN_DMAEN_MASK;
	}
}
/**
 * @brief  DMA����Դ��ַ
 * @param  DMAx: DMA����
 * @param  Channel: DMAͨ��
 *		�����������ȡ�����ֵ:
 *			@arg DMA_Channel_0 ��DMAͨ��0
 *			@arg DMA_Channel_1 ��DMAͨ��1
 *			@arg DMA_Channel_2 ��DMAͨ��2
 *			@arg DMA_Channel_3 ��DMAͨ��3
 * @param  address: DMAԴ��ַ
 * @retval None
 */
void DMA_SetSourceAddress(uint8_t Channel,uint32_t address)
{
	DMA->DMACHANREG[Channel].DMASRCADDRC = address;
}
/**
 * @brief  DMA����Ŀ���ַ
 * @param  DMAx: DMA����
 * @param  Channel: DMAͨ��
 *		�����������ȡ�����ֵ:
 *			@arg DMA_Channel_0 ��DMAͨ��0
 *			@arg DMA_Channel_1 ��DMAͨ��1
 *			@arg DMA_Channel_2 ��DMAͨ��2
 *			@arg DMA_Channel_3 ��DMAͨ��3
 * @param  address: DMAĿ���ַ
 * @retval None
 */
void DMA_SetTargetAddress(uint8_t Channel,uint32_t address)
{
	DMA->DMACHANREG[Channel].DMADSTADDRC = address;
}

/**
 * @brief  DMA����Ŀ���ַ
 * @param  DMAx: DMA����
 * @param  channel: DMAͨ��
 *		�����������ȡ�����ֵ:
 *			@arg DMA_Channel_0 ��DMAͨ��0
 *			@arg DMA_Channel_1 ��DMAͨ��1
 *			@arg DMA_Channel_2 ��DMAͨ��2
 *			@arg DMA_Channel_3 ��DMAͨ��3
 * @param  address: DMAĿ���ַ
 * @retval None
 */
void DMA_SetTransferSize(uint8_t channel,uint16_t len)
{
	DMA->DMACHANREG[channel].DMACTRLC |= (uint32_t)((uint32_t)len<<DMA_DMACTRLC_TRANSIZEC_SHIFT);
}

/**
 * @brief  DMA�õ�ͨ��״̬
 * @param  DMAx: DMA����
 * @param  Channel: DMAͨ��
 *		�����������ȡ�����ֵ:
 *			@arg DMA_Channel_0 ��DMAͨ��0
 *			@arg DMA_Channel_1 ��DMAͨ��1
 *			@arg DMA_Channel_2 ��DMAͨ��2
 *			@arg DMA_Channel_3 ��DMAͨ��3
 * @retval None
 */
uint8_t DMA_GetChannelStatus(uint8_t Channel)
{
	uint8_t temp;
	temp = (uint8_t)(DMA->DMACHANREG[Channel].DMASTATUSC & 0x00000001u);
	return temp; 
}
/**
 * @brief  DMA�õ��������ݵĳ���
 * @param  DMAx: DMA����
 * @param  Channel: DMAͨ��
 *		�����������ȡ�����ֵ:
 *			@arg DMA_Channel_0 ��DMAͨ��0
 *			@arg DMA_Channel_1 ��DMAͨ��1
 *			@arg DMA_Channel_2 ��DMAͨ��2
 *			@arg DMA_Channel_3 ��DMAͨ��3
 * @retval None
 */
uint16_t DMA_GetChanTransferDataLen(uint8_t Channel)
{
	uint16_t temp;
	temp = (uint16_t)(DMA->DMACHANREG[Channel].DMASTATUSC & 0x000007FEu);
	return temp>>1u; 
}
/**
 * @brief  DMA�õ��ж�״̬
 * @param  DMAx: DMA����
 * @param  DMA_InterruptStatusType: DMA�ж�Դ
 *		�����������ȡ�����ֵ:
 *			@arg DMA_Channel0_Err ��DMAͨ��0�����ж�
 *			@arg DMA_Channel1_Err ��DMAͨ��1�����ж�
 *			@arg DMA_Channel2_Err ��DMAͨ��2�����ж�
 *			@arg DMA_Channel3_Err ��DMAͨ��3�����ж�
 *			@arg DMA_Channel0_TransferFinish ��DMAͨ��0��������ж�
 *			@arg DMA_Channel1_TransferFinish ��DMAͨ��1��������ж�
 *			@arg DMA_Channel2_TransferFinish ��DMAͨ��2��������ж�
 *			@arg DMA_Channel3_TransferFinish ��DMAͨ��3��������ж�
 *			@arg DMA_ClearALL_Status ��DMA�����ж�
 * @retval None
 */

uint8_t DMA_GetInterruptStatus(uint8_t DMA_InterruptStatusType)
{
	uint8_t DMAStatusTemp;

	/* Get all the Line Control status */
	DMAStatusTemp =(uint8_t) DMA->DMAINTSTATUS;

	/* get the selected Line Control status */
	return (DMAStatusTemp & (uint8_t)((uint32_t)1u<<DMA_InterruptStatusType));
}

/**
 * @brief  DMA����жϱ�־
 * @param  DMAx: DMA����
 * @param  DMA_InterruptStatusType: DMA�ж�Դ
 *		�����������ȡ�����ֵ:
 *			@arg DMA_Channel0_Err ��DMAͨ��0�����ж�
 *			@arg DMA_Channel1_Err ��DMAͨ��1�����ж�
 *			@arg DMA_Channel2_Err ��DMAͨ��2�����ж�
 *			@arg DMA_Channel3_Err ��DMAͨ��3�����ж�
 *			@arg DMA_Channel0_TransferFinish ��DMAͨ��0��������ж�
 *			@arg DMA_Channel1_TransferFinish ��DMAͨ��1��������ж�
 *			@arg DMA_Channel2_TransferFinish ��DMAͨ��2��������ж�
 *			@arg DMA_Channel3_TransferFinish ��DMAͨ��3��������ж�
 *			@arg DMA_ClearALL_Status ��DMA�����ж�
 * @retval None
 */

void DMA_ClearInterruptStatus(const uint8_t DMA_InterruptStatusType)
{
	if(DMA_InterruptStatusType == (uint8_t)DMA_ClearALL_Status)
	{
		DMA->DMAINTSTATUS = 0x000000FFu;
	}
	else
	{
		DMA->DMAINTSTATUS |= (uint32_t)1u << DMA_InterruptStatusType;
	}
}
/**
 * @brief  DMAʹ���ж�
 * @param  DMAx: DMA����
 * @param  DMA_InterruptStatusType: DMA�ж�Դ
 *		�����������ȡ�����ֵ:
 *			@arg DMA_Channel0_Err_Mask ��DMAͨ��0�����ж�����
 *			@arg DMA_Channel1_Err_Mask ��DMAͨ��1�����ж�����
 *			@arg DMA_Channel2_Err_Mask ��DMAͨ��2�����ж�����
 *			@arg DMA_Channel3_Err_Mask ��DMAͨ��3�����ж�����
 *			@arg DMA_Channel0_TransferFinish_Mask ��DMAͨ��0��������ж�����
 *			@arg DMA_Channel1_TransferFinish_Mask ��DMAͨ��1��������ж�����
 *			@arg DMA_Channel2_TransferFinish_Mask ��DMAͨ��2��������ж�����
 *			@arg DMA_Channel3_TransferFinish_Mask ��DMAͨ��3��������ж�����
 * @param  NewState: ״̬ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISENABLE ��ʧ��
 * @retval None
 */

void DMA_InterruptEnable(uint8_t DMA_InterruptMaskType,FunctionalState NewState)
{
	uint32_t itenable;

	/* Get the interrupt enable index */
	itenable = ((uint32_t)1u << DMA_InterruptMaskType);
	if(NewState != DISABLE )
	{
		/* Enable the selected UART interrupts */
		DMA->DMAINTMASK |= itenable ;
	}
	else 
	{
		DMA->DMAINTMASK &= ~itenable;
	}
}

/**
 * @brief  DMA��������״̬
 * @param  DMAx: DMA����
 * @param  DMA_Peripheral_ResquestType: ��������״̬
 *		�����������ȡ�����ֵ:
 *			@arg DMA_SPI1_Tx_Req ��SPI1������������״̬
 *			@arg DMA_SPI1_Rx_Req ��SPI1������������״̬
 *			@arg DMA_SPI0_Tx_Req ��SPI0������������״̬
 *			@arg DMA_SPI0_Rx_Req ��SPI0������������״̬
 *			@arg DMA_UART0_Tx_Req ��UART0������������״̬
 *			@arg DMA_UART0_Rx_Req ��UART0������������״̬
 *			@arg DMA_UART1_Tx_Req ��UART1������������״̬
 *			@arg DMA_UART1_Rx_Req ��UART1������������״̬
 *			@arg DMA_UART2_Tx_Req ��UART2������������״̬
 *			@arg DMA_UART2_Rx_Req ��UART2������������״̬
 *			@arg DMA_ADC_Tx_Req ��ADC���ݻ���״̬
 *			@arg DMA_ADC_Rx_Req ��ADCת�����ݾ���״̬
 * @retval None
 */

uint32_t DMA_GetPeripheralResquestStatus(const uint8_t DMA_Peripheral_ResquestType)
{
	uint32_t DMAPeripheral_Resquest;
	
	/* Get all the Line Control status */
	DMAPeripheral_Resquest = DMA->DMAPERREQ;

	/* get the selected Line Control status */
	return (uint32_t)(DMAPeripheral_Resquest & ((uint32_t)1u<<DMA_Peripheral_ResquestType));
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif /* __cplusplus */


