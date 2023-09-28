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
  * @brief  配置UARTx外设寄存器为默认值
  * @param  UARTx: 选择UART外设
	*		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
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
  * @brief  配置UARTx通讯波特率，静态函数
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param  SourceClk: 外设时钟频率
  * @param  BaudRate: 通讯波特率
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
  * @brief  根据UART_InitStruct中指定的参数初始化UARTx外设
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param  UART_InitStruct: UART初始化配置结构体
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
  * @brief  根据UART_FIFOInitStruct中指定的参数初始化UARTx外设
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param  UART_FIFOInitStruct: UART初始化配置结构体
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
  * @brief  获取UART的FTFO功能使能状态
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
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
  * @brief  使能UARTx外设
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  * 		@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param  State: UARTx使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: UARTx使能
  *			@arg DISABLE: UARTx失能
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
  * @brief  发送LIN同步间隔段
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @retval None
  */
void UART_SendLinBreak(UART_Type* UARTx)
{
	UARTx->PATTERN |= UART_PATTERN_BC_MASK;
}

/**
  * @brief  设置UARTx同步间隔段长度
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param  UART_BreakLength: 指定同步间隔段长度
  *		这个参数可以取下面的值:
  *			@arg UART_LINBreakLength_10b: 至少生成10bit同步间隔段长度
  *			@arg UART_LINBreakLength_13b: 至少生成13bit同步间隔段长度
  * @retval None
  */
void UART_LINBreakLengthConfig(UART_Type* UARTx, uint8_t UART_BreakLength)
{
	UARTx->LCR &= ~UART_LCR_BRK13_MASK;
	UARTx->LCR |= UART_BreakLength;
}

/**
  * @brief  通过UARTx发送一个数据
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param  Data: 待发送数据
  * @retval None
  */
void UART_SendData(UART_Type *UARTx,uint8_t Data)
{
	UARTx->THR = Data;
}

/**
  * @brief  通过UARTx接收一个数据
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @retval 返回数据
  */
uint8_t UART_ReceiveData(const UART_Type *UARTx)
{
	return (uint8_t)UARTx->RBR;
}

/**
  * @brief  使能UARTx外设指定中断
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param UART_Interrupt：中断类型
  *		这个参数可以取下面的值:
  *			@arg UART_RDataAvailableIntEN: 接收数据中断
  *			@arg UART_THoldingEmptyIntEN：发送寄存器空中断
  *			@arg UART_RLineStatusIntEN： 线路状态中断
  *			@arg UART_ModenStatusIntEN： 调制中断
  *			@arg UART_THREIntEN：THRE中断
  * @param  State: UARTx 中断使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: UARTx 指定中断使能
  *			@arg DISABLE: UARTx 指定中断失能
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
  * @brief  获取UARTx外设指定中断使能状态
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param UART_Interrupt：中断类型
  *		这个参数可以取下面的值:
  *			@arg UART_RDataAvailableIntEN: 接收数据中断
  *			@arg UART_THoldingEmptyIntEN：发送寄存器空中断
  *			@arg UART_RLineStatusIntEN： 线路状态中断
  *			@arg UART_ModenStatusIntEN： 调制中断
  *			@arg UART_THREIntEN：THRE中断
  * @retval 当前状态(SET or RESET) 
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
  * @brief  获取UARTx外设中断状态
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @retval  IID: 中断ID，指示产生中断的类型
  *			@arg UART_IID_NONE: 无中断等待
  *			@arg UART_IID_TxHoldingEmpty: THR为空
  *			@arg UART_IID_RxDataAvailable: 接收的数据可用
  *			@arg UART_IID_RxLineStatus: 接收线路状态
  *			@arg UART_IID_Busy: 忙中断
  *			@arg UART_IID_Overtime: 字符超时
  */
uint8_t UART_GetInterruptStatus (const UART_Type *UARTx)
{
	uint8_t IntIdentityTemp;
	IntIdentityTemp =(uint8_t)UARTx->IIR ;
	
	return IntIdentityTemp;
	
}

/**
  * @brief  使能UARTx外设暂停传输
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param  State: UARTx 暂停传输使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: UARTx 暂停传输使能
  *			@arg DISABLE: UARTx 暂停传输失能
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
  * @brief  获取UARTx外设发送FIFO数据个数
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @retval TxFIFO数据个数  
  */
uint8_t UART_GetTxFIFOLevel(const UART_Type *UARTx)
{
	return (uint8_t)UARTx->TFL&UART_TFL_TFIFOL_MASK;
}

/**
  * @brief  获取UARTx外设接收FIFO数据个数
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @retval RxFIFO数据个数 
  */
uint8_t UART_GetRxFIFOLevel(const UART_Type *UARTx)
{
	return (uint8_t)UARTx->RFL&UART_RFL_RFIFOL_MASK;
}
	
/**
  * @brief  获取UARTx外设指定状态
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param  UART_StatusType: 状态类型
  *		这个参数可以取下面的值:
  *			@arg UART_Busy: UART忙
  *			@arg UART_TransmitFIFONotFull: 发送FIFO未满
  *			@arg UART_TransmitFIFOEmpty: 发送FIFO为空
  *			@arg UART_ReceiveFIFONotEmpty: 接收FIFO不为空
  *			@arg UART_ReceiveFIFOFull: 接收FIFO满
  *			@arg UART_BusIdle: UART总线处于IDLE状态
  * @retval 当前状态(SET or RESET) 
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
  * @brief  获取UARTx外设执行线路状态
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param  UART_LineStatusType: 线路状态类型
  *		这个参数可以取下面的值:
  *			@arg UART_LSRDataReady: 数据准备好
  *			@arg UART_LSROverrunErr: 溢出错误
  *			@arg UART_LSRParityErr: 奇偶校验错误
  *			@arg UART_LSRFrameErr: 帧错误
  *			@arg UART_LSRBreakIntr: 间隔符检测中断
  *			@arg UART_LSRTHREmpty: 发送保持寄存器为空位
  *			@arg UART_LSRTransmitterEmpty: 发送器空
  *			@arg UART_LSRReceiverFIFOErr: 接收器FIFO错误
  * @retval 当前状态(TRUE or FALSE) 
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
  * @brief  单线模式下设置UARTx外设TxD引脚方向
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  * 		@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param  UART_SingleLineDirection: 指定TxD引脚方向
  *		这个参数可以取下面的值:
  *			@arg UART_SingleLineDirection_Input: TxD引脚在单线模式下设置为输入
  *			@arg UART_SingleLineDirection_Output: TxD引脚在单线模式下设置为输出
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
  * @brief  设置UARTx外设模式
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param  UART_ModeType: 指定UARTx外设模式
  *		这个参数可以取下面的值:
  *			@arg UART_Mode_Normal: 正常模式
  *			@arg UART_Mode_SingleLine: 单线模式
  *			@arg UART_Mode_Loop: 环回模式
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
  * @brief  使能DMA模式软件确认
  * @param  UARTx: 选择UART外设
  *		这个参数可以取下面的值:
  *			@arg UART0: UART0外设
  *			@arg UART1: UART1外设
  *			@arg UART2: UART2外设
  * @param  State: UARTx 软件应答使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: UARTx 软件应答使能
  *			@arg DISABLE: UARTx 软件应答失能
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

