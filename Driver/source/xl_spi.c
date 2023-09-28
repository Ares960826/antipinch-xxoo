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
 * @brief SPI外设恢复初始状态
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
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
 * @brief 设置SPI的模式
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  SPI_MODEType: 选择SPI工作模式
 *		这个参数可以取下面的值:
 *			@arg SPI_MODE_MASTER(0x00) ：主机模式
 *			@arg SPI_MODE_SLAVE (0x01) ：从机模式
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
 * @brief 设置SPI发送数据包的模式
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  SPI_PACKType: 数据包的模式，选择是长包发送还是短包发送
 *		这个参数可以取下面的值:
 *			@arg SPI_PACK_CS_LOW(0x00) :片选为低
 *			@arg SPI_PACK_CS_HIGHT (0x01):片选为高
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
 * @brief SPI为主机时初始化
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  SPI_MasterInitStruct: 需要初始化的参数结构体
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
 * @brief SPI为从机时的初始化
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  SPI_SlaveInitTypeDef: 需要初始化的参数结构体
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
 * @brief SPI使能
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  NewState: 使能和失能选择
 *		这个参数可以取下面的值:
 *			@arg ENABLE ：使能
 *			@arg DISENABLE ：失能
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
 * @brief  SPI作为从机时使能命令
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  NewState: 使能和失能选择
 *		这个参数可以取下面的值:
 *			@arg ENABLE ：使能
 *			@arg DISENABLE ：失能
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
 * @brief  SPI发送数据
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  Data: 发送的数据
 * @retval None
 */
void SPI_SendData(SPI_Type *SPIx,uint16_t Data)
{
	/* Write in the DR register the data to be sent */
	SPIx->DR[0] = Data;
}

/**
 * @brief  SPI接收数据
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @retval Data：SPI接收的数据
 */
uint16_t SPI_ReceiveData(const SPI_Type *SPIx)
{
	uint16_t Data;		
	Data =(uint16_t)SPIx->DR[0];		
	/* Return the data in the DR register */	
	return Data;
}

/**
 * @brief  得到SPI中FIFO有效数据的个数
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param FIFOLevelDef: FIFO类型，发送FIFO或接收FIFO
 *		这个参数可以取下面的值:
 *			@arg SPI_TransmitFIFOLevel (0x00), 发送FIFO
 *			@arg SPI_ReceiveFIFOLevel  (0x01)  接收FIFO
 * @retval fifolevel：SPI的FIFO中得有效数据个数
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
 * @brief  得到SPI状态
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  SPI_StatusTypeDef 将要获取的状态类型选择
 *		这个参数可以取下面的值:
 *			@arg SPI_SPIBusyFlagStatus ：           SPI繁忙标志位
 *			@arg SPI_TransmitFIFONotFullStatus：    发送FIFO未满
 *			@arg SPI_TransmitFIFOEmptyStatus：      发送FIFO为空
 *			@arg SPI_ReceiveFIFONotEmptyStatus：    接收FIFO不为空
 *			@arg SPI_ReceiveFIFOFullStatus：        接收FIFO已满
 *			@arg SPI_TransmissionErrorStatus：      数据发送错误，只有SPI为从机时才能使用此功能
 *			@arg SPI_DataCollisionErrorStatus：     数据冲突错误，只有SPI为主机时才有此功能
 * @retval SPI_Status：SPI状态的类型
 *			@arg 0:对应状态未产生
 *			@arg 1:对应状态产生
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
 * @brief  SPI中断使能
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  SPI_InterruptTypeDef 使能中断类型，其值如下：
 *		这个参数可以取下面的值:
 *			@arg SPI_TransmitFIFOEmptyIT：           发送FIFO已空的中断掩码
 *			@arg SPI_TransmitFIFOOverflowIT：        发送FIFO溢出的中断掩码
 *			@arg SPI_ReceiveFIFOUnderflowIT：        接收FIFO下溢的中断掩码
 *			@arg SPI_ReceiveFIFOOverflowIT：         接收FIFO溢出的中断掩码
 *			@arg SPI_ReceiveFIFOFullIT ：            接收FIFO已满的中断掩码
 *			@arg SPI_ALLIT ：                        所有的掩码
 * @param  NewState: 状态选择
 *		这个参数可以取下面的值:
 *			@arg ENABLE ：使能
 *			@arg DISENABLE ：失能
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
 * @brief  SPI清除中断
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  SPI_InterruptClearDef 清除中断的类型，其值如下：
 *		这个参数可以取下面的值:
 *			@arg SPI_TransmitFIFOOverflowITClear：      清空发送FIFO溢出中断寄存器
 *			@arg SPI_ReceiveFIFOOverflowITClear：       清空接收FIFO溢出中断寄存器
 *			@arg SPI_ReceiveFIFOUnderflowITClear：      清空接收FIFO下溢中断寄存器
 *			@arg SPI_ALLITClear：                       清空所有状态
 * @retval 中断类型
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
 * @brief  得到SPI中断状态，中断屏蔽后的状态
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  SPI_ITStatusMaskedDef 获取的中断类型
 *		这个参数可以取下面的值:
 *			@arg SPI_TransmitFIFOEmptyITStatus ：       发送FIFO空中断状态
 *			@arg SPI_TransmitFIFOOverflowITStatus：     发送FIFO溢出中断状态
 *			@arg SPI_ReceiveFIFOUnderflowITStatus：     接收FIFO下溢中断状态
 *			@arg SPI_ReceiveFIFOOverflowITStatus：      接收FIFO溢出中断状态
 *			@arg SPI_ReceiveFIFOFullITStatus：          接收FIFO已满中断状态
 * @retval 中断状态
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
 * @brief  获得SPI中断前状态，在屏蔽之前SPI中断的状态
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  SPI_RawITStatusTypeDef 获取的中断类型
 *		这个参数可以取下面的值:
 *			@arg SPI_TransmitFIFOEmptyRawITStatus：        发送FIFO原始中断为空状态
 *			@arg SPI_TransmitFIFOOverflowRawITStatus：     发送FIFO原始中断溢出状态
 *			@arg SPI_ReceiveFIFOUnderflowRawITStatus：     接收FIFO原始中断下溢状态
 *			@arg SPI_ReceiveFIFOOverflowRawITStatus：      接收FIFO原始中断溢出状态
 *			@arg SPI_ReceiveFIFOFullRawITStatus：          接收FIFO原始中断已满状态
 * @retval 原始中断状态
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
 * @brief  SPI设置DMA发送数据的长度
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  lenght ：数据长度
 * @retval None
 */
void SPI_SetDMATxDataLenght(SPI_Type *SPIx,uint8_t lenght)
{
	SPIx->DMATDLR = lenght;
}
/**
 * @brief  SPI设置DMA接收数据长度
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  lenght ：数据长度
 * @retval None
 */
void SPI_SetDMARxDataLenght(SPI_Type *SPIx,uint8_t lenght)
{
	SPIx->DMARDLR = lenght;
}
/**
 * @brief  SPI设置DMA发送使能
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  NewState: 状态选择
 *		这个参数可以取下面的值:
 *			@arg ENABLE ：使能
 *			@arg DISENABLE ：失能
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
 * @brief  SPI设置DMA接收使能
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  NewState: 状态选择
 *		这个参数可以取下面的值:
 *			@arg ENABLE ：使能
 *			@arg DISENABLE ：失能
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
 * @brief  SPI设置延时采样时间
 * @param  SPIx: SPI外设的选择
 *		这个参数可以取下面的值:
 *			@arg SPI0 ：SPI0外设
 *			@arg SPI1 ：SPI1外设
 * @param  nclock ：延时的时间,取值(0-255)
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


