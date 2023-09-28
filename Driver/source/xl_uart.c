/**
  ******************************************************************************
  * @file     xl_uart.c
  * @author   Kirk 
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about UART firmware program 
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
#endif
/* Includes ---------------------------------------------------------------*/
#include "xl_uart.h"

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup UART UART Module
  * @brief UART Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup UART_Private_Functions
  * @brief 
  * @{
  */ 

/**
  * @brief  ����UARTx����Ĵ���ΪĬ��ֵ
  * @param  UARTx: ѡ��UART����
	*		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @retval None
  */
void UART_DeInit(UART_Type* UARTx)
{
	/* Deinitializes to default reset values */
	UARTx->LCR = 0x00;
	UARTx->DLH = 0x00;
	UARTx->DLL = 0x00;
	UARTx->SGW = 0x00;
}

/**
  * @brief  ����UARTxͨѶ�����ʣ���̬����
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param  SourceClk: ����ʱ��Ƶ��
  * @param  BaudRate: ͨѶ������
  * @retval None
  */
static void UART_SetBaudRate(UART_Type *UARTx, uint32_t SourceClk, uint32_t BaudRate)
{
    uint32_t DivisorLatch;
	uint32_t Fractional;
	  
	/* the serial clock frequency divided by sixteen times the value of the baud rate divisor */
	DivisorLatch=(SourceClk>>4u)/BaudRate;
	Fractional =(((SourceClk>>4u) - (BaudRate*DivisorLatch))<<4u)/BaudRate;
	
	/* Divisor Latch Low */
	UARTx->DLL=DivisorLatch;
	
	/* Divisor Latch High */
	UARTx->DLH=DivisorLatch>>8u;
	
	UARTx->DLF = Fractional;
}

/**
  * @brief  ����UART_InitStruct��ָ���Ĳ�����ʼ��UARTx����
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param  UART_InitStruct: UART��ʼ�����ýṹ��
  * @retval None
  */
void UART_Init(UART_Type* UARTx, const UART_InitTypeDef* UART_InitStruct)
{
	uint32_t temp;
	uint32_t temp1;
	/* set the DLAB bit (LCR[7]) */
	UARTx->LCR |= UART_LCR_DLAB_MASK;
	
	/* Set the baudrate */
	UART_SetBaudRate(UARTx,UART_InitStruct->UART_SourceClk,UART_InitStruct->UART_BaudRate);

	
	temp1 = UARTx->LCR;
	
	temp1 &= ~UART_LCR_DLAB_MASK;
	
	temp1 |= ((uint32_t)UART_InitStruct->UART_DataLength | (uint32_t)UART_InitStruct->UART_StopBits | (uint32_t)UART_InitStruct->UART_Parity);
	
	UARTx->LCR = temp1;
	
	temp = UARTx->FCR;
	
	/* first clear the TET and RT bit */
	temp &= ~(UART_FCR_RT_MASK | UART_FCR_TET_MASK);

	/* select the empty threshold level at which the THRE Interrupts */
	temp |= UART_InitStruct->UART_TET;

	/* select the trigger level in the receiver FIFO at which the Received Data */
	temp |= UART_InitStruct->UART_RT;			
	
	UARTx->FCR = temp;
}

/**
  * @brief  ����UART_FIFOInitStruct��ָ���Ĳ�����ʼ��UARTx����
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param  UART_FIFOInitStruct: UART��ʼ�����ýṹ��
  * @retval None
  */
void UART_FIFOInit(UART_Type* UARTx, const UART_FIFOInitTypeDef* UART_FIFOInitStruct)
{
	uint32_t temp;
	
	temp = (uint32_t)UART_FIFOInitStruct->UART_RT | (uint32_t)UART_FIFOInitStruct->UART_TET | \
					(uint32_t)UART_FIFOInitStruct->UART_FIFO_Enable;
	
	UARTx->FCR = temp;
}

/**
  * @brief  ��ȡUART��FTFO����ʹ��״̬
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @retval (ENABLE or DISABLE)
  */
FunctionalState UART_GetFIFOEnableStatus(const UART_Type* UARTx)
{
	FunctionalState ret;
	
	if((UARTx->IIR & UART_IIR_FIFOSE_MASK) == UART_IIR_FIFOSE_MASK)
	{
		ret = ENABLE;
	}
	else
	{
		ret = DISABLE;
	}
	
	return ret;
}


/**
  * @brief  ʹ��UARTx����
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  * 		@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param  State: UARTxʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: UARTxʹ��
  *			@arg DISABLE: UARTxʧ��
  * @retval None
  */
void UART_EnableCmd(UART_Type* UARTx, FunctionalState State)
{
	if(State == ENABLE)
	{
		UARTx->SGW |= UART_SGW_EN_MASK;
	}
	else
	{
		UARTx->SGW &= ~UART_SGW_EN_MASK;
	}
}


/**
  * @brief  ����LINͬ�������
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @retval None
  */
void UART_SendLinBreak(UART_Type* UARTx)
{
	UARTx->PATTERN |= UART_PATTERN_BC_MASK;
}

/**
  * @brief  ����UARTxͬ������γ���
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param  UART_BreakLength: ָ��ͬ������γ���
  *		�����������ȡ�����ֵ:
  *			@arg UART_LINBreakLength_10b: ��������10bitͬ������γ���
  *			@arg UART_LINBreakLength_13b: ��������13bitͬ������γ���
  * @retval None
  */
void UART_LINBreakLengthConfig(UART_Type* UARTx, uint8_t UART_BreakLength)
{
	UARTx->LCR &= ~UART_LCR_BRK13_MASK;
	UARTx->LCR |= UART_BreakLength;
}

/**
  * @brief  ͨ��UARTx����һ������
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param  Data: ����������
  * @retval None
  */
void UART_SendData(UART_Type *UARTx,uint8_t Data)
{
	UARTx->THR = Data;
}

/**
  * @brief  ͨ��UARTx����һ������
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @retval ��������
  */
uint8_t UART_ReceiveData(const UART_Type *UARTx)
{
	return (uint8_t)UARTx->RBR;
}

/**
  * @brief  ʹ��UARTx����ָ���ж�
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param UART_Interrupt���ж�����
  *		�����������ȡ�����ֵ:
  *			@arg UART_RDataAvailableIntEN: ���������ж�
  *			@arg UART_THoldingEmptyIntEN�����ͼĴ������ж�
  *			@arg UART_RLineStatusIntEN�� ��·״̬�ж�
  *			@arg UART_ModenStatusIntEN�� �����ж�
  *			@arg UART_THREIntEN��THRE�ж�
  * @param  State: UARTx �ж�ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: UARTx ָ���ж�ʹ��
  *			@arg DISABLE: UARTx ָ���ж�ʧ��
  * @retval None 
  */
void UART_EnableInterruptCmd(UART_Type *UARTx, uint8_t UART_Interrupt, FunctionalState State)
{
	if(State == ENABLE)
	{
		UARTx->IER |= UART_Interrupt;
	}
	else
	{
		UARTx->IER &= ~UART_Interrupt;
	}
}

/**
  * @brief  ��ȡUARTx����ָ���ж�ʹ��״̬
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param UART_Interrupt���ж�����
  *		�����������ȡ�����ֵ:
  *			@arg UART_RDataAvailableIntEN: ���������ж�
  *			@arg UART_THoldingEmptyIntEN�����ͼĴ������ж�
  *			@arg UART_RLineStatusIntEN�� ��·״̬�ж�
  *			@arg UART_ModenStatusIntEN�� �����ж�
  *			@arg UART_THREIntEN��THRE�ж�
  * @retval ��ǰ״̬(SET or RESET) 
  */
FlagStatus UART_GetInterruptCmd(const UART_Type *UARTx, uint8_t UART_Interrupt)
{
	FlagStatus ret = RESET;
	if(0u != (UARTx->IER & UART_Interrupt))
	{
		ret = SET;
	}
	
	return ret;
}

/**
  * @brief  ��ȡUARTx�����ж�״̬
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @retval  IID: �ж�ID��ָʾ�����жϵ�����
  *			@arg UART_IID_NONE: ���жϵȴ�
  *			@arg UART_IID_TxHoldingEmpty: THRΪ��
  *			@arg UART_IID_RxDataAvailable: ���յ����ݿ���
  *			@arg UART_IID_RxLineStatus: ������·״̬
  *			@arg UART_IID_Busy: æ�ж�
  *			@arg UART_IID_Overtime: �ַ���ʱ
  */
uint8_t UART_GetInterruptStatus (const UART_Type *UARTx)
{
	uint8_t IntIdentityTemp;
	IntIdentityTemp =(uint8_t)UARTx->IIR ;
	
	return IntIdentityTemp;
	
}

/**
  * @brief  ʹ��UARTx������ͣ����
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param  State: UARTx ��ͣ����ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: UARTx ��ͣ����ʹ��
  *			@arg DISABLE: UARTx ��ͣ����ʧ��
  * @retval None 
  */
void UART_EnableHaltTransmitCmd(UART_Type *UARTx, FunctionalState State)
{
	if(State == ENABLE)
	{
		UARTx->HTX |= UART_HTX_HTX_MASK;
	}
	else
	{
		UARTx->HTX &= ~UART_HTX_HTX_MASK;
	}
}

/**
  * @brief  ��ȡUARTx���跢��FIFO���ݸ���
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @retval TxFIFO���ݸ���  
  */
uint8_t UART_GetTxFIFOLevel(const UART_Type *UARTx)
{
	return (uint8_t)UARTx->TFL&UART_TFL_TFIFOL_MASK;
}

/**
  * @brief  ��ȡUARTx�������FIFO���ݸ���
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @retval RxFIFO���ݸ��� 
  */
uint8_t UART_GetRxFIFOLevel(const UART_Type *UARTx)
{
	return (uint8_t)UARTx->RFL&UART_RFL_RFIFOL_MASK;
}
	
/**
  * @brief  ��ȡUARTx����ָ��״̬
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param  UART_StatusType: ״̬����
  *		�����������ȡ�����ֵ:
  *			@arg UART_Busy: UARTæ
  *			@arg UART_TransmitFIFONotFull: ����FIFOδ��
  *			@arg UART_TransmitFIFOEmpty: ����FIFOΪ��
  *			@arg UART_ReceiveFIFONotEmpty: ����FIFO��Ϊ��
  *			@arg UART_ReceiveFIFOFull: ����FIFO��
  *			@arg UART_BusIdle: UART���ߴ���IDLE״̬
  * @retval ��ǰ״̬(SET or RESET) 
  */
FlagStatus UART_GetStatus(const UART_Type *UARTx, uint8_t UART_StatusType)
{
	FlagStatus ret;
	
	if( ( (UARTx->USR >> UART_StatusType)&(uint32_t)0x01) != 0u)
	{
		ret = SET;
	}
	else
	{
		ret = RESET;
	}
	
	return ret;
}

/**
  * @brief  ��ȡUARTx����ִ����·״̬
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param  UART_LineStatusType: ��·״̬����
  *		�����������ȡ�����ֵ:
  *			@arg UART_LSRDataReady: ����׼����
  *			@arg UART_LSROverrunErr: �������
  *			@arg UART_LSRParityErr: ��żУ�����
  *			@arg UART_LSRFrameErr: ֡����
  *			@arg UART_LSRBreakIntr: ���������ж�
  *			@arg UART_LSRTHREmpty: ���ͱ��ּĴ���Ϊ��λ
  *			@arg UART_LSRTransmitterEmpty: ��������
  *			@arg UART_LSRReceiverFIFOErr: ������FIFO����
  * @retval ��ǰ״̬(TRUE or FALSE) 
  */
FlagStatus UART_GetLineStatus(const UART_Type *UARTx,uint8_t UART_LineStatusType)
{
	FlagStatus ret;
	
	if( ( (UARTx->LSR >> UART_LineStatusType)&(uint32_t)0x01) != 0u)
	{
		ret = SET;
	}
	else
	{
		ret = RESET;
	}
	
	return ret;
}

/**
  * @brief  ����ģʽ������UARTx����TxD���ŷ���
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  * 		@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param  UART_SingleLineDirection: ָ��TxD���ŷ���
  *		�����������ȡ�����ֵ:
  *			@arg UART_SingleLineDirection_Input: TxD�����ڵ���ģʽ������Ϊ����
  *			@arg UART_SingleLineDirection_Output: TxD�����ڵ���ģʽ������Ϊ���
  * @retval None
  */
void UART_SingleLineDirectionConfig(UART_Type *UARTx, bool_t UART_SingleLineDirection)
{
	if(UART_SingleLineDirection)
	{
		UARTx->SGW |= UART_SGW_TXDIR_MASK;
	}
	else
	{
		UARTx->SGW &= ~UART_SGW_TXDIR_MASK;
	}
}

/**
  * @brief  ����UARTx����ģʽ
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param  UART_ModeType: ָ��UARTx����ģʽ
  *		�����������ȡ�����ֵ:
  *			@arg UART_Mode_Normal: ����ģʽ
  *			@arg UART_Mode_SingleLine: ����ģʽ
  *			@arg UART_Mode_Loop: ����ģʽ
  * @retval None
  */
void UART_SetMode(UART_Type *UARTx , uint8_t UART_ModeType)
{
	if(UART_ModeType == UART_Mode_Normal)
	{
		UARTx->SGW &= ~UART_SGW_LOOPS_MASK;
	}
	else if(UART_ModeType == UART_Mode_SingleLine)
	{
		UARTx->SGW |= UART_SGW_LOOPS_MASK;
		UARTx->SGW |= UART_SGW_RSRC_MASK;
	}
	else
	{
		UARTx->SGW |= UART_SGW_LOOPS_MASK;
		UARTx->SGW &= ~UART_SGW_RSRC_MASK;
	}
}

/**
  * @brief  ʹ��DMAģʽ���ȷ��
  * @param  UARTx: ѡ��UART����
  *		�����������ȡ�����ֵ:
  *			@arg UART0: UART0����
  *			@arg UART1: UART1����
  *			@arg UART2: UART2����
  * @param  State: UARTx ���Ӧ��ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: UARTx ���Ӧ��ʹ��
  *			@arg DISABLE: UARTx ���Ӧ��ʧ��
  * @retval None
  */
void UART_DMASoftwareAckEnableCmd(UART_Type *UARTx, FunctionalState State)
{
	if(State == ENABLE)
	{
		UARTx->DMASA |= UART_DMASA_DMASA_MASK;
	}
	else
	{
		UARTx->DMASA &= ~UART_DMASA_DMASA_MASK;
	}
	
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

