/**
  ******************************************************************************
  * @file     xl_uart.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the USART 
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
#ifndef __XL_UART_H
#define __XL_UART_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ---------------------------------------------------------------*/
#include "xl6600.h"
#pragma anon_unions /* added by neo, to support union function */
	
/* Register define ------------------------------------------------------------*/

/* RBR Bit Fields */                                
#define UART_RBR_RDB_MASK                       0xFFu
#define UART_RBR_RDB_SHIFT                      0

/* THR Bit Fields */                                     
#define UART_THR_TDH_MASK                       0xFFu
#define UART_THR_TDH_SHIFT                      0

/* DLH Bit Fields */                                                    
#define UART_DLH_BRD_MASK                       0xFFu
#define UART_DLH_BRD_SHIFT                      0

/* DLL Bit Fields */                                                    
#define UART_DLL_BRD_MASK                       0xFFu
#define UART_DLL_BRD_SHIFT                      0

/* IER Bit Fields */
#define UART_IER_ERBFI_MASK                     0x1u
#define UART_IER_ERBFI_SHIFT                    0

#define UART_IER_ETBEI_MASK                     0x2u
#define UART_IER_ETBEI_SHIFT                    1

#define UART_IER_ELSI_MASK                      0x4u
#define UART_IER_ELSI_SHIFT                     1

#define UART_IER_EDSSI_MASK                      0x8u
#define UART_IER_EDSSI_SHIFT                     1

#define UART_IER_PTIME_MASK                     0x80u
#define UART_IER_PTIME_SHIFT                    7

/* IIR Bit Fields */                                                    
#define UART_IIR_IID_MASK                       0xFu
#define UART_IIR_IID_SHIFT                      0

#define UART_IIR_FIFOSE_MASK                    0xC0u
#define UART_IIR_FIFOSE_SHIFT                   6

/* FCR Bit Fields */
#define UART_FCR_FIFOE_MASK                     0x1u
#define UART_FCR_FIFOE_SHIFT                    0

#define UART_FCR_TET_MASK                       0x30u
#define UART_FCR_TET_SHIFT                      4

#define UART_FCR_RT_MASK                        0xC0u
#define UART_FCR_RT_SHIFT                       6

/* LCR Bit Fields */                
#define UART_LCR_DLS_MASK                       0x3u
#define UART_LCR_DLS_SHIFT                      0

#define UART_LCR_STOP_MASK                      0x4u
#define UART_LCR_STOP_SHIFT                     2

#define UART_LCR_PEN_MASK                       0x8u
#define UART_LCR_PEN_SHIFT                      3

#define UART_LCR_EPS_MASK                       0x10u
#define UART_LCR_EPS_SHIFT                      4

#define UART_LCR_SP_MASK                        0x20u
#define UART_LCR_SP_SHIFT                       5

#define UART_LCR_BRK13_MASK                        0x40u
#define UART_LCR_BRK13_SHIFT                       6

#define UART_LCR_DLAB_MASK                      0x80u
#define UART_LCR_DLAB_SHIFT                     7

/* LSR Bit Fields */                
#define UART_LSR_DR_MASK                        0x1u
#define UART_LSR_DR_SHIFT                       0

#define UART_LSR_OE_MASK                        0x2u
#define UART_LSR_OE_SHIFT                       1

#define UART_LSR_PE_MASK                        0x4u
#define UART_LSR_PE_SHIFT                       2

#define UART_LSR_FE_MASK                        0x8u
#define UART_LSR_FE_SHIFT                       3

#define UART_LSR_BI_MASK                        0x10u
#define UART_LSR_BI_SHIFT                       4

#define UART_LSR_THRE_MASK                      0x20u
#define UART_LSR_THRE_SHIFT                     5

#define UART_LSR_TEMT_MASK                      0x40u
#define UART_LSR_TEMT_SHIFT                     6

#define UART_LSR_RFE_MASK                       0x80u
#define UART_LSR_RFE_SHIFT                      7

/* PATTERN Bit Fields */      
#define UART_PATTERN_BC_MASK                 0x80u
#define UART_PATTERN_BC_SHIFT                7

/* USR Bit Fields */        
#define UART_USR_BUSY_MASK                      0x1u
#define UART_USR_BUSY_SHIFT                     0

#define UART_USR_TFNF_MASK                      0x2u
#define UART_USR_TFNF_SHIFT                     1

#define UART_USR_TFE_MASK                       0x4u
#define UART_USR_TFE_SHIFT                      2

#define UART_USR_RFNE_MASK                      0x8u
#define UART_USR_RFNE_SHIFT                     3

#define UART_USR_RFF_MASK                       0x10u
#define UART_USR_RFF_SHIFT                      4

#define UART_USR_IDLE_MASK                       0x80u
#define UART_USR_IDLE_SHIFT                      7

/* TFL Bit Fields */                                                    
#define UART_TFL_TFIFOL_MASK                    0x7Fu
#define UART_TFL_TFIFOL_SHIFT                   0

/* RFL Bit Fields */                                                    
#define UART_RFL_RFIFOL_MASK                    0x7Fu
#define UART_RFL_RFIFOL_SHIFT                   0

/* HTX Bit Fields */                                                    
#define UART_HTX_HTX_MASK                       0x1u
#define UART_HTX_HTX_SHIFT                      0

/* DMASA Bit Fields */                                                    
#define UART_DMASA_DMASA_MASK                   0x1u
#define UART_DMASA_DMASA_SHIFT                  0

/* SGW Bit Fields */
#define UART_SGW_TXDIR_MASK                     0x1u
#define UART_SGW_TXDIR_SHIFT                    0

#define UART_SGW_EN_MASK												0x02u
#define UART_SGW_EN_SHIFT                       1

#define UART_SGW_RSRC_MASK                      0x4u
#define UART_SGW_RSRC_SHIFT                     2

#define UART_SGW_LOOPS_MASK                     0x8u
#define UART_SGW_LOOPS_SHIFT                    3

/** UART - Register Layout Typedef */
typedef struct {
	union {
	 __I  uint32_t       RBR;                      /*!< 接收缓存寄存器, offset:0x00*/
	 __O  uint32_t       THR;                      /*!< 发送保持寄存器, offset:0x00*/
	 __IO uint32_t       DLL;                      /*!< 波特率寄存器低位, offset:0x00*/
	};
	union {
	 __IO uint32_t       DLH;                      /*!< 波特率寄存器高位, offset:0x04*/
	 __IO uint32_t       IER;                      /*!< 中断使能寄存器, offset:0x04*/
	};
	union {
	 __I  uint32_t       IIR;                      /*!< 中断标识寄存器, offset:0x08*/
	 __O  uint32_t       FCR;                      /*!< FIFO控制寄存器, offset:0x08*/
	};
	__IO uint32_t        LCR;                      /*!< 线路控制寄存器, offset:0x0C*/
       uint32_t RESERVED_0[1];
	__I  uint32_t        LSR;                      /*!< 线路状态寄存器, offset:0x14*/
       uint32_t RESERVED_1[10];
	__IO uint32_t        PATTERN;			             /*!< UART/LIN模式选择寄存器, offset:0x40*/
			 uint32_t RESERVED_2[14];
	__I  uint32_t        USR;                      /*!< UART状态寄存器, offset:0x7C*/
	__I  uint32_t        TFL;                      /*!< 发送FIFO计数寄存器, offset:0x80*/
	__I  uint32_t        RFL;                      /*!< 接收FIFO计数寄存器, offset:0x84*/
       uint32_t RESERVED_3[7];		
	__IO uint32_t        HTX;                      /*!< 暂停TX, offset:0xA4*/
	__O  uint32_t        DMASA;                    /*!< DMA软件确认寄存器, offset:0xA8*/
	uint32_t RESERVED_4[5];	
	__O uint32_t DLF;                              /*!< 小数波特率寄存器, offset:0xA8*/
    uint32_t RESERVED_5[15];	
	__IO uint32_t        SGW;                      /*!< 单线模式和环回模式, offset:0x100*/
	
}UART_Type;

extern UART_Type*  		UART0;
extern UART_Type*  		UART1;
extern UART_Type*  		UART2;	


/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup UART 
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 
/** 
  * @brief UART初始化结构体定义
  */
typedef struct
{
	uint32_t UART_SourceClk;          /*!< uart时钟频率 */
	uint32_t UART_BaudRate;           /*!<  通讯波特率 */
	uint8_t  UART_DataLength;         /*!< uart数据长度 */  
	uint8_t  UART_StopBits;           /*!< uart停止位    */
	uint8_t  UART_Parity;             /*!< uart校验位 */
	uint8_t  UART_TET;	              /*!< TX空触发。这用于选择产生THRE中断的空阈值电平 */
	uint8_t  UART_RT;                 /*!< RCVR触发。用于选择生成接收数据准备好中断的接收FIFO触发水平 */
} UART_InitTypeDef;

/** 
  * @brief UART FIFO初始化结构体定义
  */
typedef struct
{
	uint8_t  UART_TET;	              /*!< select the empty threshold level at which the THRE Interrupts aregenerated when the mode is active */
	uint8_t  UART_RT;                 /*!< select the trigger level in the receiver FIFO at which the Received Data Available Interrupt is generated. In */
	uint8_t  UART_FIFO_Enable;
}UART_FIFOInitTypeDef;
/* Exported constants --------------------------------------------------------*/
/** @defgroup UART_Exported_Constants UART模块使用参数定义
  * @{
  */

/**
	* @defgroup Data_Length_Select UART数据位定义
	* @{
	*/
#define UART_DataLength_5b           					((uint8_t)0x00)   /*!< 5位 */
#define UART_DataLength_6b           					((uint8_t)0x01)   /*!< 6位 */
#define UART_DataLength_7b           					((uint8_t)0x02)   /*!< 7位 */
#define UART_DataLength_8b           					((uint8_t)0x03)   /*!< 8位 */
/**
  * @}
  */ 
  
/**
	* @defgroup Stop_Bits_Select UART停止位定义
	* @{
	*/
#define UART_StopBits_1              					((uint8_t)0x00)   /*!< 1个停止位 */
#define UART_StopBits_2              					((uint8_t)0x04)   /*!< 当DLS（LCR [1：0]）为0时为1―1.5个停止位，否则为2个停止位 */
/**
  * @}
  */	

	
/**
	* @defgroup Parity_Bits_Select UART校验位定义
	* @{
	*/	
#define UART_Parity_No               					((uint8_t)0x00)   /*!< 校验位失能 */
#define UART_Parity_Odd              					((uint8_t)0x08)   /*!< 奇校验 */
#define UART_Parity_Even             					((uint8_t)0x18)   /*!< 偶校验 */
#define UART_StickParity_Odd         					((uint8_t)0x28)   /*!< 发送或检查奇数个数 */
#define UART_StickParity_Even        					((uint8_t)0x38)   /*!< 发送或检查偶数个数  */
/**
  * @}
  */

/**
	* @defgroup RX_FIFO_LEV UART接收FIFO深度定义
	* @{
	*/	
#define UART_RxFIFO_1Char              				((uint8_t)0x00)   /*!< 接收FIFO深度为1字节 */
#define UART_RxFIFO_4Char             			 	((uint8_t)0x40)   /*!< 接收FIFO深度为4字节 */
#define UART_RxFIFO_8Char              				((uint8_t)0x80)   /*!< 接收FIFO深度为8字节 */
#define UART_RxFIFO_14Char              			((uint8_t)0xC0)   /*!< 接收FIFO深度为14字节 */
/**
  * @}
  */ 
	
/**
	* @defgroup TX_FIFO_LEV UART发送FIFO深度定义
	* @{
	*/	
#define UART_TxFIFO_0Char              				((uint8_t)0x00)   /*!< 发送FIFO深度为0字节 */
#define UART_TxFIFO_2Char              				((uint8_t)0x10)   /*!< 发送FIFO深度为2字节 */
#define UART_TxFIFO_4Char              				((uint8_t)0x20)   /*!< 发送FIFO深度为4字节 */
#define UART_TxFIFO_8Char              				((uint8_t)0x30)   /*!< 发送FIFO深度为8字节 */
/**
  * @}
  */ 
    	
/**
	* @defgroup LIN_BreakLenght_Select LIN同步间隔段长度选择
	* @{
	*/	
#define UART_LINBreakLength_10b              ((uint8_t)0x00)   /* 至少生成10bit同步间隔段长度 */
#define UART_LINBreakLength_13b              ((uint8_t)0x40)   /* 至少生成13bit同步间隔段长度 */
/**
 .. * @}
  */ 


/**
	* @defgroup UART_Interrupt_Select UART使能中断类型定义
	* @{
	*/
#define UART_RDataAvailableIntEN							((uint8_t)0x01)   /* 接收数据可用中断 */
#define UART_THoldingEmptyIntEN								((uint8_t)0x02)   /* 发送保持寄存器空中断 */
#define UART_RLineStatusIntEN								((uint8_t)0x04)     /* 接收线路状态中断 */
#define UART_ModenStatusIntEN								((uint8_t)0x08)     /* 调制解调器状态中断 */
#define UART_THREIntEN										((uint8_t)0x80)       /* THRE中断 */
/**
  * @}
  */ 
  	
/**
	* @defgroup UART_Interrupt_ID UART撞断类型定义
	* @{
	*/
#define UART_IID_NONE													((uint8_t)0x01)   /* 无中断等待 */
#define UART_IID_TxHoldingEmpty								((uint8_t)0x02)   /* THR为空 */
#define UART_IID_RxDataAvailable							((uint8_t)0x04)   /* 接收的数据可用 */
#define UART_IID_RxLineStatus									((uint8_t)0x06)   /* 接收线路状态 */
#define UART_IID_Busy													((uint8_t)0x07)   /* 忙中断 */
#define UART_IID_Overtime											((uint8_t)0x0C)   /* 字符超时 */
/**
  * @}
  */  
	
/**
	* @defgroup UART_Status_Select UART状态类型定义
	* @{
	*/
#define UART_Busy															((uint8_t)0x00)   /* UART忙 */
#define UART_TransmitFIFONotFull							((uint8_t)0x01)   /* 发送FIFO未满 */
#define UART_TransmitFIFOEmpty								((uint8_t)0x02)   /* 发送FIFO为空 */
#define UART_ReceiveFIFONotEmpty							((uint8_t)0x03)   /* 接收FIFO不为空 */
#define UART_ReceiveFIFOFull									((uint8_t)0x04)   /* 接收FIFO满 */
#define UART_BusIdle													((uint8_t)0x07)   /* UART总线处于IDLE状态 */
/**
  * @}
  */ 
 
/**
	* @defgroup UART_LineStatus_Select  UART线路状态类型定义
	* @{
	*/	
#define UART_LSRDataReady											((uint8_t)0x00)   /* 数据准备好 */
#define UART_LSROverrunErr										((uint8_t)0x01)   /* 溢出错误 */
#define UART_LSRParityErr											((uint8_t)0x02)   /* 奇偶校验错误 */
#define UART_LSRFrameErr											((uint8_t)0x03)   /* 帧错误 */
#define UART_LSRBreakIntr											((uint8_t)0x04)   /* 间隔符检测中断 */
#define UART_LSRTHREmpty											((uint8_t)0x05)   /* 发送保持寄存器为空位 */
#define UART_LSRTransmitterEmpty							((uint8_t)0x06)   /* 发送器空 */
#define UART_LSRReceiverFIFOErr								((uint8_t)0x07)   /* 接收器FIFO错误 */
/**
  * @}
  */ 
  
/**
	* @defgroup UART_SingleLineDir_Seclect UART单线模式下设置UARTx外设TxD引脚方向  
  * @{
	*/		
#define UART_SingleLineDirection_Input				((uint8_t)0x00)   /* 数据准备好 */
#define UART_SingleLineDirection_Output				((uint8_t)0x01)   /* 溢出错误 */
/**
  * @}
  */ 

/**
	* @defgroup UART_Mode_Seclect 设置UARTx外设模式 
	* @{
	*/	
#define UART_Mode_Normal											((uint8_t)0x00)   /* 数据准备好 */
#define UART_Mode_SingleLine									((uint8_t)0x01)   /* 溢出错误 */
#define UART_Mode_Loop												((uint8_t)0x02)   /* 溢出错误 */
/**
  * @}
  */ 

/**
  * @}
  */
	

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void UART_DeInit(UART_Type* UARTx);
void UART_Init(UART_Type* UARTx, const UART_InitTypeDef* UART_InitStruct);
void UART_FIFOInit(UART_Type* UARTx, const UART_FIFOInitTypeDef* UART_FIFOInitStruct);
FunctionalState UART_GetFIFOEnableStatus(const UART_Type* UARTx);
void UART_EnableCmd(UART_Type* UARTx, FunctionalState State);
void UART_SendLinBreak(UART_Type* UARTx);
void UART_LINBreakLengthConfig(UART_Type *UARTx, uint8_t UART_BreakLength);
void UART_SendData(UART_Type *UARTx,uint8_t Data);
uint8_t UART_ReceiveData(const UART_Type *UARTx);
void UART_EnableInterruptCmd(UART_Type *UARTx, uint8_t UART_Interrupt, FunctionalState State);
FlagStatus UART_GetInterruptCmd(const UART_Type *UARTx, uint8_t UART_Interrupt);
uint8_t UART_GetInterruptStatus (const UART_Type *UARTx);
void UART_EnableHaltTransmitCmd(UART_Type *UARTx, FunctionalState State);
uint8_t UART_GetTxFIFOLevel(const UART_Type *UARTx);
uint8_t UART_GetRxFIFOLevel(const UART_Type *UARTx);
FlagStatus UART_GetStatus(const UART_Type *UARTx, uint8_t UART_StatusType);
FlagStatus UART_GetLineStatus(const UART_Type *UARTx,uint8_t UART_LineStatusType);
void UART_SingleLineDirectionConfig(UART_Type *UARTx, bool_t UART_SingleLineDirection);
void UART_SetMode(UART_Type *UARTx , uint8_t UART_ModeType);
void UART_DMASoftwareAckEnableCmd(UART_Type *UARTx, FunctionalState State);
#ifdef __cplusplus
}
#endif
	
#endif /*__XL_UART_H */
/**
  * @}
  */

/**
  * @}
  */

 


/************************ (C) COPYRIGHT Chipways *****END OF FILE****/
