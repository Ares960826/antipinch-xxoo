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
	 __I  uint32_t       RBR;                      /*!< ���ջ���Ĵ���, offset:0x00*/
	 __O  uint32_t       THR;                      /*!< ���ͱ��ּĴ���, offset:0x00*/
	 __IO uint32_t       DLL;                      /*!< �����ʼĴ�����λ, offset:0x00*/
	};
	union {
	 __IO uint32_t       DLH;                      /*!< �����ʼĴ�����λ, offset:0x04*/
	 __IO uint32_t       IER;                      /*!< �ж�ʹ�ܼĴ���, offset:0x04*/
	};
	union {
	 __I  uint32_t       IIR;                      /*!< �жϱ�ʶ�Ĵ���, offset:0x08*/
	 __O  uint32_t       FCR;                      /*!< FIFO���ƼĴ���, offset:0x08*/
	};
	__IO uint32_t        LCR;                      /*!< ��·���ƼĴ���, offset:0x0C*/
       uint32_t RESERVED_0[1];
	__I  uint32_t        LSR;                      /*!< ��·״̬�Ĵ���, offset:0x14*/
       uint32_t RESERVED_1[10];
	__IO uint32_t        PATTERN;			             /*!< UART/LINģʽѡ��Ĵ���, offset:0x40*/
			 uint32_t RESERVED_2[14];
	__I  uint32_t        USR;                      /*!< UART״̬�Ĵ���, offset:0x7C*/
	__I  uint32_t        TFL;                      /*!< ����FIFO�����Ĵ���, offset:0x80*/
	__I  uint32_t        RFL;                      /*!< ����FIFO�����Ĵ���, offset:0x84*/
       uint32_t RESERVED_3[7];		
	__IO uint32_t        HTX;                      /*!< ��ͣTX, offset:0xA4*/
	__O  uint32_t        DMASA;                    /*!< DMA���ȷ�ϼĴ���, offset:0xA8*/
	uint32_t RESERVED_4[5];	
	__O uint32_t DLF;                              /*!< С�������ʼĴ���, offset:0xA8*/
    uint32_t RESERVED_5[15];	
	__IO uint32_t        SGW;                      /*!< ����ģʽ�ͻ���ģʽ, offset:0x100*/
	
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
  * @brief UART��ʼ���ṹ�嶨��
  */
typedef struct
{
	uint32_t UART_SourceClk;          /*!< uartʱ��Ƶ�� */
	uint32_t UART_BaudRate;           /*!<  ͨѶ������ */
	uint8_t  UART_DataLength;         /*!< uart���ݳ��� */  
	uint8_t  UART_StopBits;           /*!< uartֹͣλ    */
	uint8_t  UART_Parity;             /*!< uartУ��λ */
	uint8_t  UART_TET;	              /*!< TX�մ�����������ѡ�����THRE�жϵĿ���ֵ��ƽ */
	uint8_t  UART_RT;                 /*!< RCVR����������ѡ�����ɽ�������׼�����жϵĽ���FIFO����ˮƽ */
} UART_InitTypeDef;

/** 
  * @brief UART FIFO��ʼ���ṹ�嶨��
  */
typedef struct
{
	uint8_t  UART_TET;	              /*!< select the empty threshold level at which the THRE Interrupts aregenerated when the mode is active */
	uint8_t  UART_RT;                 /*!< select the trigger level in the receiver FIFO at which the Received Data Available Interrupt is generated. In */
	uint8_t  UART_FIFO_Enable;
}UART_FIFOInitTypeDef;
/* Exported constants --------------------------------------------------------*/
/** @defgroup UART_Exported_Constants UARTģ��ʹ�ò�������
  * @{
  */

/**
	* @defgroup Data_Length_Select UART����λ����
	* @{
	*/
#define UART_DataLength_5b           					((uint8_t)0x00)   /*!< 5λ */
#define UART_DataLength_6b           					((uint8_t)0x01)   /*!< 6λ */
#define UART_DataLength_7b           					((uint8_t)0x02)   /*!< 7λ */
#define UART_DataLength_8b           					((uint8_t)0x03)   /*!< 8λ */
/**
  * @}
  */ 
  
/**
	* @defgroup Stop_Bits_Select UARTֹͣλ����
	* @{
	*/
#define UART_StopBits_1              					((uint8_t)0x00)   /*!< 1��ֹͣλ */
#define UART_StopBits_2              					((uint8_t)0x04)   /*!< ��DLS��LCR [1��0]��Ϊ0ʱΪ1�D1.5��ֹͣλ������Ϊ2��ֹͣλ */
/**
  * @}
  */	

	
/**
	* @defgroup Parity_Bits_Select UARTУ��λ����
	* @{
	*/	
#define UART_Parity_No               					((uint8_t)0x00)   /*!< У��λʧ�� */
#define UART_Parity_Odd              					((uint8_t)0x08)   /*!< ��У�� */
#define UART_Parity_Even             					((uint8_t)0x18)   /*!< żУ�� */
#define UART_StickParity_Odd         					((uint8_t)0x28)   /*!< ���ͻ����������� */
#define UART_StickParity_Even        					((uint8_t)0x38)   /*!< ���ͻ���ż������  */
/**
  * @}
  */

/**
	* @defgroup RX_FIFO_LEV UART����FIFO��ȶ���
	* @{
	*/	
#define UART_RxFIFO_1Char              				((uint8_t)0x00)   /*!< ����FIFO���Ϊ1�ֽ� */
#define UART_RxFIFO_4Char             			 	((uint8_t)0x40)   /*!< ����FIFO���Ϊ4�ֽ� */
#define UART_RxFIFO_8Char              				((uint8_t)0x80)   /*!< ����FIFO���Ϊ8�ֽ� */
#define UART_RxFIFO_14Char              			((uint8_t)0xC0)   /*!< ����FIFO���Ϊ14�ֽ� */
/**
  * @}
  */ 
	
/**
	* @defgroup TX_FIFO_LEV UART����FIFO��ȶ���
	* @{
	*/	
#define UART_TxFIFO_0Char              				((uint8_t)0x00)   /*!< ����FIFO���Ϊ0�ֽ� */
#define UART_TxFIFO_2Char              				((uint8_t)0x10)   /*!< ����FIFO���Ϊ2�ֽ� */
#define UART_TxFIFO_4Char              				((uint8_t)0x20)   /*!< ����FIFO���Ϊ4�ֽ� */
#define UART_TxFIFO_8Char              				((uint8_t)0x30)   /*!< ����FIFO���Ϊ8�ֽ� */
/**
  * @}
  */ 
    	
/**
	* @defgroup LIN_BreakLenght_Select LINͬ������γ���ѡ��
	* @{
	*/	
#define UART_LINBreakLength_10b              ((uint8_t)0x00)   /* ��������10bitͬ������γ��� */
#define UART_LINBreakLength_13b              ((uint8_t)0x40)   /* ��������13bitͬ������γ��� */
/**
 .. * @}
  */ 


/**
	* @defgroup UART_Interrupt_Select UARTʹ���ж����Ͷ���
	* @{
	*/
#define UART_RDataAvailableIntEN							((uint8_t)0x01)   /* �������ݿ����ж� */
#define UART_THoldingEmptyIntEN								((uint8_t)0x02)   /* ���ͱ��ּĴ������ж� */
#define UART_RLineStatusIntEN								((uint8_t)0x04)     /* ������·״̬�ж� */
#define UART_ModenStatusIntEN								((uint8_t)0x08)     /* ���ƽ����״̬�ж� */
#define UART_THREIntEN										((uint8_t)0x80)       /* THRE�ж� */
/**
  * @}
  */ 
  	
/**
	* @defgroup UART_Interrupt_ID UARTײ�����Ͷ���
	* @{
	*/
#define UART_IID_NONE													((uint8_t)0x01)   /* ���жϵȴ� */
#define UART_IID_TxHoldingEmpty								((uint8_t)0x02)   /* THRΪ�� */
#define UART_IID_RxDataAvailable							((uint8_t)0x04)   /* ���յ����ݿ��� */
#define UART_IID_RxLineStatus									((uint8_t)0x06)   /* ������·״̬ */
#define UART_IID_Busy													((uint8_t)0x07)   /* æ�ж� */
#define UART_IID_Overtime											((uint8_t)0x0C)   /* �ַ���ʱ */
/**
  * @}
  */  
	
/**
	* @defgroup UART_Status_Select UART״̬���Ͷ���
	* @{
	*/
#define UART_Busy															((uint8_t)0x00)   /* UARTæ */
#define UART_TransmitFIFONotFull							((uint8_t)0x01)   /* ����FIFOδ�� */
#define UART_TransmitFIFOEmpty								((uint8_t)0x02)   /* ����FIFOΪ�� */
#define UART_ReceiveFIFONotEmpty							((uint8_t)0x03)   /* ����FIFO��Ϊ�� */
#define UART_ReceiveFIFOFull									((uint8_t)0x04)   /* ����FIFO�� */
#define UART_BusIdle													((uint8_t)0x07)   /* UART���ߴ���IDLE״̬ */
/**
  * @}
  */ 
 
/**
	* @defgroup UART_LineStatus_Select  UART��·״̬���Ͷ���
	* @{
	*/	
#define UART_LSRDataReady											((uint8_t)0x00)   /* ����׼���� */
#define UART_LSROverrunErr										((uint8_t)0x01)   /* ������� */
#define UART_LSRParityErr											((uint8_t)0x02)   /* ��żУ����� */
#define UART_LSRFrameErr											((uint8_t)0x03)   /* ֡���� */
#define UART_LSRBreakIntr											((uint8_t)0x04)   /* ���������ж� */
#define UART_LSRTHREmpty											((uint8_t)0x05)   /* ���ͱ��ּĴ���Ϊ��λ */
#define UART_LSRTransmitterEmpty							((uint8_t)0x06)   /* �������� */
#define UART_LSRReceiverFIFOErr								((uint8_t)0x07)   /* ������FIFO���� */
/**
  * @}
  */ 
  
/**
	* @defgroup UART_SingleLineDir_Seclect UART����ģʽ������UARTx����TxD���ŷ���  
  * @{
	*/		
#define UART_SingleLineDirection_Input				((uint8_t)0x00)   /* ����׼���� */
#define UART_SingleLineDirection_Output				((uint8_t)0x01)   /* ������� */
/**
  * @}
  */ 

/**
	* @defgroup UART_Mode_Seclect ����UARTx����ģʽ 
	* @{
	*/	
#define UART_Mode_Normal											((uint8_t)0x00)   /* ����׼���� */
#define UART_Mode_SingleLine									((uint8_t)0x01)   /* ������� */
#define UART_Mode_Loop												((uint8_t)0x02)   /* ������� */
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
