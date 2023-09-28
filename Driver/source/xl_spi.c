/**
  ******************************************************************************
  * @file     xl_spi.c
  * @author   xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about spi firmware program 
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
#include "xl_spi.h"
	/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup SPI  SPI Module
  * @brief SPI Driver Modules Library
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
	
/** @defgroup SPI_Private_Functions
  * @{
  */ 

/**
 * @brief SPI����ָ���ʼ״̬
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @retval None
 */
void SPI_DeInit(SPI_Type *SPIx)
{
	/* Deinitializes to default reset values */
	SPIx->CTRLR0 = 0x0007u;
	SPIx->CTRLR1 = 0x0000u;
	SPIx->BAUDR  = 0x0000u; 
	SPIx->TXFTLR = 0x0000u;
	SPIx->RXFTLR = 0x0000u;
}

/**
 * @brief ����SPI��ģʽ
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  SPI_MODEType: ѡ��SPI����ģʽ
 *		�����������ȡ�����ֵ:
 *			@arg SPI_MODE_MASTER(0x00) ������ģʽ
 *			@arg SPI_MODE_SLAVE (0x01) ���ӻ�ģʽ
 * @retval None
 */
void SPI_SetMode(SPI_Type *SPIx,SPI_MODETypeDef SPI_MODEType)
{
	if(SPI_MODEType != SPI_MODE_MASTER )
	{
		/* SLAVE SPI */
		SPIx->MODE |= SPI_MODE_MSTR_MASK;
	}
	else 
	{
		/* MASTER SPI */
		SPIx->MODE &= ~SPI_MODE_MSTR_MASK;
	}
}

/**
 * @brief ����SPI�������ݰ���ģʽ
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  SPI_PACKType: ���ݰ���ģʽ��ѡ���ǳ������ͻ��Ƕ̰�����
 *		�����������ȡ�����ֵ:
 *			@arg SPI_PACK_CS_LOW(0x00) :ƬѡΪ��
 *			@arg SPI_PACK_CS_HIGHT (0x01):ƬѡΪ��
 * @retval None
 */
void SPI_SetPackCS(SPI_Type *SPIx,SPI_PACKCSTypeDef SPI_PACKCSType)
{
	if(SPI_PACKCSType != SPI_PACK_CS_HIGHT )
	{
		/* SLAVE SPI */
		SPIx->MODE |= SPI_MODE_PACK_MASK;
	}
	else 
	{
		/* MASTER SPI */
		SPIx->MODE &= ~SPI_MODE_PACK_MASK;
	}
}



/**
 * @brief SPIΪ����ʱ��ʼ��
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  SPI_MasterInitStruct: ��Ҫ��ʼ���Ĳ����ṹ��
 * @retval None
 */
void SPI_MasterInit(SPI_Type* SPIx, const SPI_MsterInitTypeDef *SPI_MasterInitStruct)
{
	uint16_t slckdiv;
	  		
	 /* Set the CTRLR0 */				
	 /* Set the bit in CTRLR0 Register */
	 SPIx->CTRLR0 = (SPI_MasterInitStruct->SPI_SRL | SPI_MasterInitStruct->SPI_TMOD | \
	                  SPI_MasterInitStruct->SPI_SCPOL | SPI_MasterInitStruct->SPI_SCPH | \
	                  SPI_MasterInitStruct->SPI_DFS);	  
		
	 /* Set the CTRLR1 Register bit*/				
	  SPIx->CTRLR1 = SPI_MasterInitStruct->SPI_NDF;
		
	 /* Set the BAUDR */
    slckdiv= (uint16_t)(SPI_MasterInitStruct->SPI_SourceClk/SPI_MasterInitStruct->SPI_BAUDR);
		
	  SPIx->BAUDR = slckdiv;	
		
	 /* Set the TXFTLR */				
	  SPIx->TXFTLR = SPI_MasterInitStruct->SPI_TFT;			

	 /* Set the RXFTLR */				
	  SPIx->RXFTLR = SPI_MasterInitStruct->SPI_RFT;		
}	

/**
 * @brief SPIΪ�ӻ�ʱ�ĳ�ʼ��
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  SPI_SlaveInitTypeDef: ��Ҫ��ʼ���Ĳ����ṹ��
 * @retval None
 */
void SPI_SlaveInit(SPI_Type* SPIx, const SPI_SlaveInitTypeDef *SPI_SlaveInitStruct)
{
	
		/* Set the CTRLR0 */				
		/* Set the bit in CTRLR0 Register */	
		SPIx->CTRLR0 = (SPI_SlaveInitStruct->SPI_SRL | SPI_SlaveInitStruct->SPI_TMOD | \
										SPI_SlaveInitStruct->SPI_SCPOL | SPI_SlaveInitStruct->SPI_SCPH | \
										SPI_SlaveInitStruct->SPI_DFS);
		
				/* check the slave output Enable */	
		if(SPI_SlaveInitStruct->SPI_SLVOE != DISABLE)
		{
			SPIx->CTRLR0 &= ~SPI_CTRLR0_SLVOE_MASK;
		}
		else
		{
			SPIx->CTRLR0 |= SPI_CTRLR0_SLVOE_MASK;
		}
			
		/* Set the TXFTLR */				
		SPIx->TXFTLR = SPI_SlaveInitStruct->SPI_TFT;			

		/* Set the RXFTLR */				
		SPIx->RXFTLR = SPI_SlaveInitStruct->SPI_RFT;		
}	

/**
 * @brief SPIʹ��
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  NewState: ʹ�ܺ�ʧ��ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISENABLE ��ʧ��
 * @retval None
 */
void SPI_EnableCmd(SPI_Type *SPIx,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enable the SPI */
		SPIx->SPIENR |= SPI_SPIENR_SPIE_MASK;
	}
	else 
	{
		/* Disable the SPI */
		SPIx->SPIENR &= ~SPI_SPIENR_SPIE_MASK;
	}
}

/**
 * @brief  SPI��Ϊ�ӻ�ʱʹ������
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  NewState: ʹ�ܺ�ʧ��ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISENABLE ��ʧ��
 * @retval None
 */
void SPI_SlaveEnableCmd(SPI_Type *SPIx,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enable the SPI Slave Select Output */
		SPIx->SER |= SPI_SER_SSEF_MASK;
	}
	else 
	{
		/* Disable the SPI Slave Select Output */
		SPIx->SER &= ~SPI_SER_SSEF_MASK;
	}
}

/**
 * @brief  SPI��������
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  Data: ���͵�����
 * @retval None
 */
void SPI_SendData(SPI_Type *SPIx,uint16_t Data)
{
	/* Write in the DR register the data to be sent */
	SPIx->DR[0] = Data;
}

/**
 * @brief  SPI��������
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @retval Data��SPI���յ�����
 */
uint16_t SPI_ReceiveData(const SPI_Type *SPIx)
{
	uint16_t Data;		
	Data =(uint16_t)SPIx->DR[0];		
	/* Return the data in the DR register */	
	return Data;
}

/**
 * @brief  �õ�SPI��FIFO��Ч���ݵĸ���
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param FIFOLevelDef: FIFO���ͣ�����FIFO�����FIFO
 *		�����������ȡ�����ֵ:
 *			@arg SPI_TransmitFIFOLevel (0x00), ����FIFO
 *			@arg SPI_ReceiveFIFOLevel  (0x01)  ����FIFO
 * @retval fifolevel��SPI��FIFO�е���Ч���ݸ���
 */
uint8_t SPI_GetFIFOLevel(const SPI_Type *SPIx,SPI_TXRXFIFOLevelDef FIFOLevelDef)
{
	uint8_t fifolevel;
	 
	/* Get the Transmit FIFO Level */
	if(FIFOLevelDef==SPI_TransmitFIFOLevel)
	{
		fifolevel=(uint8_t)(SPIx->TXFLR &SPI_TXFLR_TFL_MASK);
	}
	/* Get the Receive FIFO Level */
	else
	{
		fifolevel=(uint8_t)(SPIx->RXFLR &SPI_RXFLR_RFL_MASK);		
	}
	
	/* return the fifolevel Value */
	return fifolevel;	  
}

/**
 * @brief  �õ�SPI״̬
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  SPI_StatusTypeDef ��Ҫ��ȡ��״̬����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI_SPIBusyFlagStatus ��           SPI��æ��־λ
 *			@arg SPI_TransmitFIFONotFullStatus��    ����FIFOδ��
 *			@arg SPI_TransmitFIFOEmptyStatus��      ����FIFOΪ��
 *			@arg SPI_ReceiveFIFONotEmptyStatus��    ����FIFO��Ϊ��
 *			@arg SPI_ReceiveFIFOFullStatus��        ����FIFO����
 *			@arg SPI_TransmissionErrorStatus��      ���ݷ��ʹ���ֻ��SPIΪ�ӻ�ʱ����ʹ�ô˹���
 *			@arg SPI_DataCollisionErrorStatus��     ���ݳ�ͻ����ֻ��SPIΪ����ʱ���д˹���
 * @retval SPI_Status��SPI״̬������
 *			@arg 0:��Ӧ״̬δ����
 *			@arg 1:��Ӧ״̬����
 */
uint8_t SPI_GetStatus(const SPI_Type *SPIx,SPI_StatusTypeDef SPI_StatusType)
{
	uint8_t StatusTemp;

	/* Get all the status */
	StatusTemp = (uint8_t)(SPIx->SR);

	/* get the selected status */
	return (StatusTemp &	(uint8_t)(1u<<(uint8_t)SPI_StatusType));
}

/**
 * @brief  SPI�ж�ʹ��
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  SPI_InterruptTypeDef ʹ���ж����ͣ���ֵ���£�
 *		�����������ȡ�����ֵ:
 *			@arg SPI_TransmitFIFOEmptyIT��           ����FIFO�ѿյ��ж�����
 *			@arg SPI_TransmitFIFOOverflowIT��        ����FIFO������ж�����
 *			@arg SPI_ReceiveFIFOUnderflowIT��        ����FIFO������ж�����
 *			@arg SPI_ReceiveFIFOOverflowIT��         ����FIFO������ж�����
 *			@arg SPI_ReceiveFIFOFullIT ��            ����FIFO�������ж�����
 *			@arg SPI_ALLIT ��                        ���е�����
 * @param  NewState: ״̬ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISENABLE ��ʧ��
 * @retval None
 */
void SPI_InterruptEn(SPI_Type *SPIx, SPI_InterruptTypeDef SPI_Interrupt, FunctionalState NewState)
{
  uint8_t itmask;
	if(SPI_Interrupt == SPI_ALLIT)
	{
		if (NewState != DISABLE)
		{
			/* Enable the selected SPI interrupts */
			SPIx->IMR = 0xFFFFFFFFu;
		}
		else
		{
			/* Disable the selected SPI interrupts */
			SPIx->IMR = 0u;
		}
	}
	else
	{
		/* Get the interrupt enable index */
		itmask = (uint8_t)(1u<<(uint8_t)SPI_Interrupt);

		if (NewState != DISABLE)
		{
			/* Enable the selected SPI interrupts */
			SPIx->IMR |= itmask;
		}
		else
		{
			/* Disable the selected SPI interrupts */
			SPIx->IMR &= ~itmask;
		}
	}
}

/**
 * @brief  SPI����ж�
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  SPI_InterruptClearDef ����жϵ����ͣ���ֵ���£�
 *		�����������ȡ�����ֵ:
 *			@arg SPI_TransmitFIFOOverflowITClear��      ��շ���FIFO����жϼĴ���
 *			@arg SPI_ReceiveFIFOOverflowITClear��       ��ս���FIFO����жϼĴ���
 *			@arg SPI_ReceiveFIFOUnderflowITClear��      ��ս���FIFO�����жϼĴ���
 *			@arg SPI_ALLITClear��                       �������״̬
 * @retval �ж�����
 */
uint8_t SPI_ClearInterrupt(const SPI_Type *SPIx, SPI_InterruptClearDef SPI_Interrupt2Clear)
{
	uint8_t interrupt2clear;
	 
	/* Clear Transmit FIFO Overflow Interrupt */
	if(SPI_Interrupt2Clear==SPI_TransmitFIFOOverflowITClear)
	{
		interrupt2clear=(uint8_t)(SPIx->TXOICR);
	}
	/* Clear Receive FIFO Overflow Interrupt */
	else if(SPI_Interrupt2Clear==SPI_ReceiveFIFOOverflowITClear)
	{
		interrupt2clear=(uint8_t)(SPIx->RXOICR);		
	}
	/* Clear Receive FIFO Underflow Interrupt */
	else if(SPI_Interrupt2Clear==SPI_ReceiveFIFOUnderflowITClear)
	{
		interrupt2clear=(uint8_t)(SPIx->RXUICR);	
	}
	/* Clear Interrupt */
	else
	{
		interrupt2clear=(uint8_t)(SPIx->ICR);			
	}
	
	/* return the interrupt type */
	return interrupt2clear;	  
}

/**
 * @brief  �õ�SPI�ж�״̬���ж����κ��״̬
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  SPI_ITStatusMaskedDef ��ȡ���ж�����
 *		�����������ȡ�����ֵ:
 *			@arg SPI_TransmitFIFOEmptyITStatus ��       ����FIFO���ж�״̬
 *			@arg SPI_TransmitFIFOOverflowITStatus��     ����FIFO����ж�״̬
 *			@arg SPI_ReceiveFIFOUnderflowITStatus��     ����FIFO�����ж�״̬
 *			@arg SPI_ReceiveFIFOOverflowITStatus��      ����FIFO����ж�״̬
 *			@arg SPI_ReceiveFIFOFullITStatus��          ����FIFO�����ж�״̬
 * @retval �ж�״̬
 */
uint8_t SPI_GetIntMaskedStatus(const SPI_Type *SPIx,SPI_ITStatusMaskedDef SPI_IntStatusType)
{
	uint8_t IntStatusTemp;

	/* Get all the interrupt status */
	IntStatusTemp = (uint8_t)(SPIx->ISR);
	
	/* get the selected interrupt status */
	return (IntStatusTemp &(uint8_t)(1u<<(uint8_t)SPI_IntStatusType));
}

/**
 * @brief  ���SPI�ж�ǰ״̬��������֮ǰSPI�жϵ�״̬
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  SPI_RawITStatusTypeDef ��ȡ���ж�����
 *		�����������ȡ�����ֵ:
 *			@arg SPI_TransmitFIFOEmptyRawITStatus��        ����FIFOԭʼ�ж�Ϊ��״̬
 *			@arg SPI_TransmitFIFOOverflowRawITStatus��     ����FIFOԭʼ�ж����״̬
 *			@arg SPI_ReceiveFIFOUnderflowRawITStatus��     ����FIFOԭʼ�ж�����״̬
 *			@arg SPI_ReceiveFIFOOverflowRawITStatus��      ����FIFOԭʼ�ж����״̬
 *			@arg SPI_ReceiveFIFOFullRawITStatus��          ����FIFOԭʼ�ж�����״̬
 * @retval ԭʼ�ж�״̬
 */
uint8_t SPI_GetRawIntStatus(const SPI_Type *SPIx,SPI_RawITStatusTypeDef SPI_RawIntStatusType)
{
	uint8_t RawIntStatusTemp;
	/* Get all the Raw interrupt status */
	RawIntStatusTemp =(uint8_t)(SPIx->RISR);
	
	/* get the selected Raw interrupt status */
	return (RawIntStatusTemp &(uint8_t)(1u<<(uint8_t)SPI_RawIntStatusType));
}

/**
 * @brief  SPI����DMA�������ݵĳ���
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  lenght �����ݳ���
 * @retval None
 */
void SPI_SetDMATxDataLenght(SPI_Type *SPIx,uint8_t lenght)
{
	SPIx->DMATDLR = lenght;
}
/**
 * @brief  SPI����DMA�������ݳ���
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  lenght �����ݳ���
 * @retval None
 */
void SPI_SetDMARxDataLenght(SPI_Type *SPIx,uint8_t lenght)
{
	SPIx->DMARDLR = lenght;
}
/**
 * @brief  SPI����DMA����ʹ��
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  NewState: ״̬ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISENABLE ��ʧ��
 * @retval None
 */
void SPI_DMATxEnableCmd(SPI_Type *SPIx,FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the selected SPI interrupts */
		SPIx->DMACR |= SPI_DMACR_TDMAE_MASK;
	}
	else
	{
		/* Disable the selected SPI interrupts */
		SPIx->DMACR &= ~SPI_DMACR_TDMAE_MASK;
	}
}
/**
 * @brief  SPI����DMA����ʹ��
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  NewState: ״̬ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISENABLE ��ʧ��
 * @retval None
 */
void SPI_DMARxEnableCmd(SPI_Type *SPIx,FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the selected SPI interrupts */
		SPIx->DMACR |= SPI_DMACR_RDMAE_MASK;
	}
	else
	{
		/* Disable the selected SPI interrupts */
		SPIx->DMACR &= ~SPI_DMACR_RDMAE_MASK;
	}
}
/**
 * @brief  SPI������ʱ����ʱ��
 * @param  SPIx: SPI�����ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg SPI0 ��SPI0����
 *			@arg SPI1 ��SPI1����
 * @param  nclock ����ʱ��ʱ��,ȡֵ(0-255)
 * @retval None
 */
void SPI_DelaySampling(SPI_Type *SPIx,uint32_t nclock)
{
	SPIx->DLY  = nclock;
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


