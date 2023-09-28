/**
  ******************************************************************************
  * @file     xl_i2c.c
  * @author   kirk  ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about I2C firmware program 
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
#include "xl_i2c.h"
	
	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup I2C   I2C Module 
  * @brief I2C Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup I2C_Private_Functions 
  * @{
  */ 

/**
 * @brief  I2C�ָ���ʼ״̬
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @retval None
 */
void I2C_Deinit(I2C_Type *I2Cx)
{
   I2Cx->ENABLE =  0x0000u;		
   I2Cx->CR     =  0x007Fu;  	
   I2Cx->TAR    =  0x0055u;	
   I2Cx->SAR    =  0x0055u;	
   I2Cx->SSCH   =  0x0190u;	
   I2Cx->SSCL   =  0x01d6u;	
   I2Cx->FSCH   =  0x003cu;	
   I2Cx->FSCL   =  0x0082u;	
   I2Cx->RXTL   =  0x0000u;	
   I2Cx->TXTL   =  0x0000u;	

}
/**
 * @brief ����ͨѶ�ٶ�
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  I2C_SourceClk: I2Cʱ��Դѡ��ϵͳʱ��
 * @param  I2C_SpeedMode: ͨѶ�ٶ�ģʽ
 *		�����������ȡ�����ֵ:
 *			@arg I2C_StandardMode �� ��׼ģʽ 100k
 *			@arg I2C_FastMode ��     ����ģʽ 400k
 *			@arg I2C_HighspeedMode ������ģʽ 3.4M
 * @retval None
 */
static void I2C_SetSpeed(I2C_Type *I2Cx, uint16_t I2C_SourceClk,uint16_t I2C_SpeedMode)
{
	 uint16_t IC_HCNT;
	 uint16_t IC_LCNT;
	/* set I2C speed in standaed mode */	
	if(I2C_SpeedMode == I2C_StandardMode)
	{
		IC_HCNT=(uint16_t)(4000u*(I2C_SourceClk)/1000u);
		I2Cx->SSCH = (uint32_t)IC_HCNT;
		IC_LCNT=(uint16_t)(4700u*(I2C_SourceClk)/1000u);
		I2Cx->SSCL = (uint32_t)IC_LCNT;		
	}
	/* set I2C speed in fast mode */	
	else
	{
		IC_HCNT=(uint16_t)(600u*(I2C_SourceClk)/1000u);
		I2Cx->FSCH = (uint32_t)IC_HCNT;
		IC_LCNT=(uint16_t)(1300u*(I2C_SourceClk)/1000u);
		I2Cx->FSCL = (uint32_t)IC_LCNT;				
	}
}	

/**
 * @brief ��ʼ��I2Cģ��
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param I2C_InitStruct I2C ��ʼ���Ĳ����ṹ��
 * @retval None
 */
void I2C_Init(I2C_Type *I2Cx, const I2C_InitTypeDef * I2C_InitStruct)
{
	uint32_t temp1;
	
	/* Set the I2Cx  control register */
	I2Cx->CR = (I2C_InitStruct->I2C_MasterModeEn | I2C_InitStruct->I2C_SlaveModeDis |\
							I2C_InitStruct->I2C_SendRestart | I2C_InitStruct->I2C_SpeedMode |\
							I2C_InitStruct->I2C_SADmode | I2C_InitStruct->I2C_MADmode);
	
	/* set I2C speed  */		
	I2C_SetSpeed(I2Cx,I2C_InitStruct->I2C_SourceClk,I2C_InitStruct->I2C_SpeedMode);

	/*  IC_RXTL : I2C Receive FIFO Threshold Register */
	I2Cx->RXTL = I2C_InitStruct->I2C_RXTL;
	
	/*  IC_TXTL : I2C Transmit FIFO Threshold Register */
	I2Cx->TXTL = I2C_InitStruct->I2C_TXTL;
	
	/*************************only used in master mode ***************************/				
	/* Set the I2Cx  TAR register,only used in master mode */		
	temp1 = I2Cx->TAR;
	
	temp1 &= ~I2C_TAR_TAD_MASK;	
	
	temp1 |= I2C_InitStruct->I2C_TargetAddress;		
	
	I2Cx->TAR = temp1;	

	/*************************only used in slave mode ***************************/				
	/* IC_SAR : I2C slave address register */	
	I2Cx->SAR = I2C_InitStruct->I2C_SlaveAddress;
}
	

/**
 * @brief I2C ʹ��
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  NewState: ״̬ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISENABLE ��ʧ��
 * @retval None
 */
void I2C_EnableCmd(I2C_Type *I2Cx, FunctionalState NewState)
{
	/* enable the I2C moudle */
	if(NewState != DISABLE )
	{
		/* Enable the selected I2C peripheral */
		I2Cx->ENABLE |=  I2C_ENABLE_EN_MASK ;
	}
	else 
	{
		/* Disable the selected I2C peripheral */
		I2Cx->ENABLE &= ~I2C_ENABLE_EN_MASK;
	}
}

/**
 * @brief I2C ����һ��CALL����
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @retval None
 */
void I2C_GeneralCall( I2C_Type* I2Cx)
{
	/* set special mode */	
	I2Cx->TAR |=I2C_TAR_SPECIAL_MASK;
	
	/* set General Call */		
	I2Cx->TAR &= ~I2C_TAR_GOS_MASK;
}


/**
 * @brief I2Cͨ�õ���Ӧ��ʹ��
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  NewState: ״̬ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISENABLE ��ʧ��
 * @retval None
 */
void I2C_GeneralCallAckEnableCmd(I2C_Type* I2Cx, FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		I2Cx->ENABLE |=  I2C_AGC_ACKGC_MASK ;
	}
	else 
	{
		I2Cx->ENABLE &= ~I2C_AGC_ACKGC_MASK;
	}
}


/**
 * @brief I2C ����һ��StartByte����
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  TargetAddress: Ŀ���ַ
 * @retval None
 */
void I2C_StartByte(I2C_Type* I2Cx, uint32_t TargetAddress)
{	
	uint32_t temp;
	
	temp = I2Cx->TAR;
	
	temp &= ~I2C_TAR_TAD_MASK;
	
	temp |= (I2C_TAR_SPECIAL_MASK | I2C_TAR_GOS_MASK | TargetAddress);
	
	I2Cx->TAR = temp;
}


/**
 * @brief I2C �ж�ʹ�ܺ���
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  I2C_Interrupt: �ж�Դ
 *		�����������ȡ�����ֵ:
 *			@arg    I2C_RXUNDERInterrupt     RX UNDER Interrupt 
 *			@arg 	I2C_RXOVERInterrupt      RX OVER Interrupt
 *			@arg 	I2C_RXFULLInterrupt      RX FULL Interrupt
 *			@arg 	I2C_TXOVERInterrupt      TX OVER Interrupt 
 *			@arg 	I2C_TXEMPTYInterrupt     TX EMPTY Interrupt
 *			@arg 	I2C_RDREQInterrupt       RD REQ Interrupt 
 *			@arg 	I2C_TXABRTInterrupt      TX ABRT Interrupt
 *			@arg 	I2C_RXDONEInterrupt      RX DONE Interrupt 
 *			@arg 	I2C_ACTIVITYInterrupt    ACTIVITY Interrupt
 *			@arg 	I2C_STOPDETInterrupt     STOP DET Interrupt
 *			@arg 	I2C_STARTDETInterrupt    START DET Interrupt 
 *			@arg 	I2C_GENCALLInterrupt     GEN CALL Interrupt
 * @param  NewState: ״̬ѡ��
 *		�����������ȡ�����ֵ:
 *			@arg ENABLE ��ʹ��
 *			@arg DISENABLE ��ʧ��
 * @retval None
 */
void I2C_InterruptEn(I2C_Type *I2Cx, const I2C_InterruptTypeDef I2C_Interrupt, FunctionalState NewState)
{
  uint16_t itmask;

  /* Get the interrupt enable index */
  itmask = (uint16_t)((uint32_t)1u << (uint8_t)I2C_Interrupt);
	
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    I2Cx->INTRM |= (uint32_t)itmask;
  }
  else
  {
    /* Disable the selected I2C interrupts */
    I2Cx->INTRM &= ~(uint32_t)itmask;
  }
}
/**
 * @brief I2C �õ��ж�״̬����
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  I2C_IntStatusType: �ж�Դ
 *		�����������ȡ�����ֵ:
 *			@arg	I2C_RXUNDERInterruptStatus      RX UNDER Interrupt Masked Status.
 *			@arg	I2C_RXOVERInterruptStatus       RX OVER Interrupt Masked Status.
 *			@arg	I2C_RXFULLInterruptStatus       RX FULL Interrupt Masked Status. 
 *			@arg	I2C_TXOVERInterruptStatus       TX OVER Interrupt Masked Status. 
 *			@arg	I2C_TXEMPTYInterruptStatus      TX EMPTY Interrupt Masked Status.
 *			@arg	I2C_RDREQInterruptStatus        RD REQ Interrupt Masked Status. 
 *			@arg	I2C_TXABRTInterruptStatus       TX ABRT Interrupt Masked Status. 
 *			@arg	I2C_RXDONEInterruptStatus       RX DONE Interrupt Masked Status. 
 *			@arg    I2C_ACTIVITYInterruptStatus     ACTIVITY Interrupt Masked Status. 
 *			@arg    I2C_STOPDETInterruptStatus      STOP DET Interrupt Masked Status. 
 *			@arg	I2C_STARTDETInterruptStatus     START DET Interrupt Masked Status. 
 *			@arg	I2C_GENCALLInterruptStatus      GEN CALL Interrupt Masked Status. 
 * @retval �����ж�״̬
 */
uint16_t I2C_GetMaskedIntStatus(const I2C_Type *I2Cx, I2C_ITStatusMaskedDef I2C_IntStatusType)
{
	uint16_t IntStatusTemp;
	/* Get all the interrupt status */
	IntStatusTemp =(uint16_t)(I2Cx->IS);
	
	/* get the selected interrupt status */
	return (uint16_t)((uint32_t)IntStatusTemp & ((uint32_t)1 << (uint8_t)I2C_IntStatusType));
}


/**
 * @brief I2C �õ�I2Cԭʼ�ж�״̬
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  I2C_RawIntStatusType: �ж�Դ
 *		�����������ȡ�����ֵ:
 *			@arg    I2C_RXUNDERInterruptRawStatus   RX UNDER Interrupt Raw Status. 
 *			@arg	I2C_RXOVERInterruptRawStatus    RX OVER InterruptRawStatus. 
 *			@arg	I2C_RXFULLInterruptRawStatus    RX FULL InterruptRawStatus.  
 *			@arg	I2C_TXOVERInterruptRawStatus    TX OVER InterruptRawStatus. 
 *			@arg	I2C_TXEMPTYInterruptRawStatus   TX EMPTY InterruptRawStatus. 
 *			@arg	I2C_RDREQInterruptRawStatus     RD REQ Interrupt Raw Status.  
 *			@arg	I2C_TXABRTInterruptRawStatus    TX ABRT Interrupt Raw Status. 
 *			@arg	I2C_RXDONEInterruptRawStatus    RX DONE Interrupt Raw Status. 
 *			@arg	I2C_ACTIVITYInterruptRawStatus  ACTIVITY Interrupt Raw Status. 
 *			@arg	I2C_STOPDETInterruptRawStatus   STOP DET Interrupt Raw Status.  
 *			@arg	I2C_STARTDETInterruptRawStatus  START DET Interrupt Raw Status. 
 *			@arg	I2C_GENCALLInterruptRawStatus   GEN CALL Interrupt Raw Status. 
 * @retval �����ж�״̬
 */
uint16_t I2C_GetRawIntgStatus(const I2C_Type *I2Cx,I2C_RawITStatusTypeDef I2C_RawIntStatusType)
{
	uint16_t RawIntStatusTemp;

	/* Get all the Raw interrupt status */
	RawIntStatusTemp =(uint16_t)(I2Cx->RIS) ;
	
	/* get the selected Raw interrupt status */
	return (uint16_t)((uint32_t)RawIntStatusTemp & ((uint32_t)1u << (uint8_t)I2C_RawIntStatusType));
}

/**
 * @brief I2C ����жϱ�־
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  I2C_Interrupt2Clear: �ж�Դ
 *		�����������ȡ�����ֵ:
 *			@arg    I2C_AllInterruptClear          Combined and Individual Clear.
 *			@arg	I2C_RXUNDERInterruptClear      Clear RX UNDER Interrupt  
 *			@arg	I2C_RXOVERInterruptClear       Clear RX OVER Interrupt
 *			@arg	I2C_TXOVERInterruptClear       Clear TX OVER Interrupt 
 *			@arg	I2C_RDREQInterruptClear        Clear RD REQ Interrupt 
 *			@arg	I2C_TXABRTInterruptClear       Clear TX ABRT Interrupt 
 *			@arg	I2C_RXDONEInterruptClear       Clear RX DONE Interrupt 
 *			@arg	I2C_ACTIVITYInterruptClear     Clear ACTIVITY Interrupt 
 *			@arg	I2C_STOPDETInterruptClear      Clear STOP DET Interrupt 
 *			@arg	I2C_STARTDETInterruptClear     Clear START DET Interrupt 
 *			@arg	I2C_GENCALLInterruptClear      Clear GEN CALL Interrupt 
 * @retval �����ж�״̬
 */
uint16_t I2C_ClearInterrupt(const I2C_Type *I2Cx, I2C_InterruptClearDef I2C_Interrupt2Clear)
{
	uint16_t interrupt2clear;
	 
	/*!< Clear GEN_CALL Interrupt Register */
	if(I2C_Interrupt2Clear == I2C_GENCALLInterruptClear)
	{
		interrupt2clear=(uint16_t)(I2Cx->CGC);
	}
	/*!< Clear START_DET Interrupt Register */
	else if(I2C_Interrupt2Clear == I2C_STARTDETInterruptClear)
	{
		interrupt2clear=(uint16_t)(I2Cx->CSTART);
	}
	/*!< Clear STOP_DET Interrupt Register */
	else if(I2C_Interrupt2Clear == I2C_STOPDETInterruptClear)
	{
		interrupt2clear=(uint16_t)(I2Cx->CSTOP);
	}	
	/*!< Clear ACTIVITY Interrupt Register */
	else if(I2C_Interrupt2Clear == I2C_ACTIVITYInterruptClear)
	{
		interrupt2clear=(uint16_t)(I2Cx->CACT);
	}
	/*!< Clear RX_DONE Interrupt Register */
	else if(I2C_Interrupt2Clear==I2C_RXDONEInterruptClear)
	{
		interrupt2clear=(uint16_t)(I2Cx->CRD);		
	}
	/*!< Clear TX_ABRT Interrupt Register */
	else if(I2C_Interrupt2Clear==I2C_TXABRTInterruptClear)
	{
		interrupt2clear=(uint16_t)(I2Cx->CTXA);		
	}
	/*!< Clear RD_REQ Interrupt Register */
	else if(I2C_Interrupt2Clear==I2C_RDREQInterruptClear)
	{
		interrupt2clear=(uint16_t)(I2Cx->CRR);		
	}
	/*!< Clear TX_OVER Interrupt Register */
	else if(I2C_Interrupt2Clear==I2C_TXOVERInterruptClear)
	{
		interrupt2clear=(uint16_t)(I2Cx->CTO);		
	}
	/*!< Clear RX_OVER Interrupt Register */
	else if(I2C_Interrupt2Clear==I2C_RXOVERInterruptClear)
	{
		interrupt2clear=(uint16_t)(I2Cx->CRO);		
	}
	/*!< Clear RX_UNDER Interrupt Register */
	else if(I2C_Interrupt2Clear == I2C_RXUNDERInterruptClear)
	{
		interrupt2clear=(uint16_t)(I2Cx->CRU);	
	}
	/* Clear all Interrupt */
	else
	{
		interrupt2clear=(uint16_t)(I2Cx->CCI);			
	}
	
	return interrupt2clear;
}

/**
 * @brief I2C ��ȡI2C״̬
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  I2C_StatusType: ״̬����
 *			@arg    I2C_ActivityStatus                    I2C Activity Status. 
 *			@arg	  I2C_TransmitFIFONotFullStatus         Transmit FIFO Not Full.
 *			@arg    I2C_TransmitFIFOEmptyStatus           Transmit FIFO Completely Empty
 *			@arg    I2C_ReceiveFIFONotEmptyStatus         Receive FIFO not Empty.
 *			@arg    I2C_ReceiveFIFOFullStatus             Receive FIFO Completely Full. 
 *			@arg    I2C_MasterFSMActStatus                Master FSM Activity Status. 
 *			@arg    I2C_SlaveFSMActStatus                 Slave FSM Activity Status. 
 * @retval �����ж�״̬
 */
uint8_t I2C_GetStatus(const I2C_Type *I2Cx, I2C_StatusTypeDef I2C_StatusType)
{
	uint8_t StatusTemp;
	/* Get all the status */
	StatusTemp =(uint8_t)(I2Cx->STATUS);

	/* get the selected status */
	return (StatusTemp &(uint8_t)(1u << (uint8_t)I2C_StatusType));
}


/**
 * @brief I2C ��ȡI2C��ֹԴ
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  I2C_ABRTSourceType: ��ֹԴ
 * @retval �����ж�״̬
 */
uint16_t I2C_GetAbortSource(const I2C_Type *I2Cx, I2C_ABRTSourceTypeDef I2C_ABRTSourceType)
{
	uint16_t StatusTemp;
	/* Get all the status */
	StatusTemp = (uint16_t)(I2Cx->TXAS);

	/* get the selected status */
	return (uint16_t)((uint32_t)StatusTemp & ((uint32_t)1u << (uint8_t)I2C_ABRTSourceType));
}

/**
 * @brief I2C ��ȡI2Cʹ��״̬
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  I2C_EnableStatusType: ʹ�ܵ�״̬
 *		�����������ȡ�����ֵ:
 *			@arg	I2C_ENStatusI2CENStatus                  I2C_en Status.
 *			@arg	I2C_ENStatusSlaveRXOperationAborted      Slave-Receiver Operation Aborted.  
 *			@arg  I2C_ENStatusSlaveFIFOFilledAndFlushed   Slave FIFO Filled and Flushed.  
 * @retval �����ж�״̬
 */
uint8_t I2C_GetEnableStatus(const I2C_Type *I2Cx, I2C_EnableStatusTypeDef I2C_EnableStatusType)
{
	uint8_t StatusTemp;
	/* Get all the status */
	StatusTemp =(uint8_t)(I2Cx->ES);

	/* get the selected status */
	return (StatusTemp &(uint8_t)(1u << (uint8_t)I2C_EnableStatusType));
}
 
/**
 * @brief I2C ��ȡI2C FIFO��״̬
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  FIFOLevelDef: FIFO��״̬Դ
 *		�����������ȡ�����ֵ:
 *			@arg I2C_TransmitFIFOLevel               Transmit FIFO Level
 *			@arg  I2C_ReceiveFIFOLevel               Receive FIFO Level 
 * @retval �����ж�״̬
 */
uint8_t I2C_GetFIFOLev(const I2C_Type *I2Cx, I2C_TXRXFIFOLevelDef FIFOLevelDef)
{
	uint8_t fifolevel;
	 
	/* Check the FIFO Level is transmit or receive*/
	if(FIFOLevelDef==I2C_TransmitFIFOLevel)
	{
		fifolevel=(uint8_t)(I2Cx->TXFLR &I2C_TXFLR_TXFL_MASK);
	}
	else
	{
		fifolevel=(uint8_t)(I2Cx->RXFLR &I2C_RXFLR_RXFL_MASK);		
	}
  /* return the fifolevel Value */
	return fifolevel;	  
}
 
/**
 * @brief I2C ��������
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  u8DataBuff: ���͵�����
 * @param  isstop: �Ƿ���ֹͣλ
 *		�����������ȡ�����ֵ:
 *			@arg I2C_No_Stop ��������STOP
 *			@arg I2C_Stop ������STOP
 * @retval None
 */
void I2C_WriteData(I2C_Type *I2Cx, uint8_t u8DataBuff,I2C_IsStopDef isstop)
{
	if(isstop == I2C_Stop)
	{
		/* write to the DAT */
		I2Cx->DBC = (uint32_t)u8DataBuff | I2C_DBC_STOP_MASK;
	}
	else
	{
		/* write to the DAT */
		I2Cx->DBC = (uint32_t)u8DataBuff;
	}
}

/**
 * @brief I2C ������������
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  isstop: �Ƿ���ֹͣλ
 *		�����������ȡ�����ֵ:
 *			@arg I2C_No_Stop ��������STOP
 *			@arg I2C_Stop ������STOP
 * @retval ���յ�����
 */
void I2C_ReadDataCmd(I2C_Type *I2Cx ,I2C_IsStopDef isstop)
{
	if(isstop == I2C_Stop)
	{
		I2Cx->DBC = (I2C_DBC_CMD_MASK|I2C_DBC_STOP_MASK);
	}
	else
	{
		I2Cx->DBC = I2C_DBC_CMD_MASK;
	}
}

/**
 * @brief I2C �������ݺ���
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @retval ���յ�����
 */
uint8_t I2C_ReadData(const I2C_Type *I2Cx)
{
	uint8_t dtemp;
	
	dtemp = (uint8_t)I2Cx->DBC;
	
  return dtemp ;
}


/**
 * @brief I2C ���·��Ϳ�ʼ�����Ƕ�����
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @retval None
 */
void I2C_ResStartRead(I2C_Type *I2Cx)
{
	I2Cx->DBC = I2C_DBC_RESTART_MASK|I2C_DBC_CMD_MASK;
}

/**
 * @brief I2C ���¿�ʼ��������
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @retval None
 */
void I2C_ResStartWrite(I2C_Type *I2Cx,uint8_t u8DataBuff,I2C_IsStopDef isstop)
{
	if(isstop == I2C_Stop)
	{
		I2Cx->DBC = (uint32_t)u8DataBuff |I2C_DBC_RESTART_MASK| I2C_DBC_STOP_MASK;
	}
	else
	{
		I2Cx->DBC = (uint32_t)u8DataBuff | I2C_DBC_RESTART_MASK ;
	}
}

/**
 * @brief I2C SDA��ʱ
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  I2Cclkfreq: ʱ��Ƶ��
 * @param  DelayReq: ��ʱ����
 * @retval None
 */
void I2C_SetSDADelay(I2C_Type *I2Cx, const uint8_t I2Cclkfreq, const uint8_t DelayReq)
{
	 uint8_t temp;

	 /* calculate the time delay,I2Cclkfreq in Mhz,DelayReq in ns*/
	 temp = (uint8_t)(((uint16_t)I2Cclkfreq * (uint16_t)DelayReq /1000u) + 1u);

	 /*  set the amount of time delay */
	 I2Cx->SDAS = (uint32_t)temp;
}

/**
 * @brief I2C SDA����ʱ������
 * @param  I2Cx: I2C����
 *		�����������ȡ�����ֵ:
 *			@arg I2C0 ��I2C0����
 *			@arg I2C1 ��I2C1����
 * @param  holdtime: ���ֵ�ʱ��
 * @retval None
 */
void I2C_SetSDAHoldTime(I2C_Type *I2Cx, uint16_t holdtime)
{
	 I2Cx->SDAHOLD = (uint32_t)holdtime;
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


/*******************************************************************************
 * EOF
 ******************************************************************************/
