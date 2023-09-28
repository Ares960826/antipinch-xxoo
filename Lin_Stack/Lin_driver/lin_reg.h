/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2008-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
******************************************************************************/
/**************************************************************************//**
* @addtogroup UART_group
* @{
******************************************************************************/
/**************************************************************************//**
*
* @file      bsp/UART/lin_reg.h
*
* @author    FPT Software
*
* @brief     UART register definition on S08, S12, S12X
*
******************************************************************************/

/******************************************************************************
 *
 * History:
 *
 * 20101027		v1.0	First version
 *
 *****************************************************************************/

#ifndef LIN_REG_H         /* Prevent duplicated includes */
#define LIN_REG_H

#include "lin_hw_cfg.h"

/*************************************/
/******   Common Register struct *****/
/*************************************/

/**
* @var typedef unsigned char tU08
* unsigned 8 bits definition
*/
typedef unsigned char   tU08;   /**< unsigned 8 bit definition */

/**
* @var typedef unsigned char tU16
* unsigned 16 bits definition
*/
typedef unsigned short    tU16;   /**< unsigned 16 bit definition */

/**
* @var typedef unsigned long tU32
* unsigned 32 bits definition
*/
typedef unsigned long   tU32;   /**< unsigned 32 bit definition */

/**
* @var typedef unsigned char tS08
* signed 32 bits definition
*/
typedef signed char     tS08;   /**< signed 8 bit definition */

/**
* @var typedef signed int      tS16
* signed 16 bits definition
*/
typedef signed short      tS16;   /**< signed 16 bit definition */

/**
* @var typedef signed long      tS32
* signed 32 bits definition
*/
typedef signed long     tS32;   /**< signed 32 bit definition */

/**
* @union uUARTDRH
* UART Data Register hight
*/
typedef union uUARTLCR
{
  tU32   dword;				/**< access register as byte */
  struct
  {
    tU32 dls       	:2;      	/**< data len select */
    tU32 stopl    	:1;      	/**< stop bit num */
    tU32 pen    	:1;      	/**<    */
    tU32 eps    	:1;
    tU32 			:1;			/**< bit reserved area */
    tU32 brk13		:1;
    tU32 dlab		:1;
    tU32 			:24;
  }bit;						/**< access register as bits */
}tUARTLCR;


/**
* @struct tUART
* UART data structure
*/
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

typedef struct 				 /**< UART data structure  */
{
	union {
	 __I  tU32       RBR;                     /**<Receive Buffer Register, offset:0x00*/
	 __O  tU32       THR;                     /**<Transmit Holding Register , offset:0x00*/
	 __IO tU32       DLL;                     /**<Divisor Latch (Low), offset:0x00*/
	};
	union {
	 __IO tU32       DLH;                     /**<Divisor Latch (High), offset:0x04*/
	 __IO tU32       IER;                     /**<Interrupt Enable Register , offset:0x04*/
	};
	union {
	 __I  tU32       IIR;                     /**<Interrupt Identification Register, offset:0x08*/
	 __O  tU32       FCR;                     /**<FIFO Control Register, offset:0x08*/
	};
	__IO tUARTLCR        LCR;                      /**<Line Control Register, offset:0x0C*/
	tU32 RESERVED_0[1];
	__I  tU32        LSR;                      /**<Line Status Register, offset:0x14*/
	tU32 RESERVED_1[10];
	__IO tU32        PATTERN;
	tU32 RESERVED_2[14];
	__I  tU32        USR;                      /**<UART Status Register, offset:0x7C*/
	__I  tU32        TFL;                      /**<Transmit FIFO Level, offset:0x80*/
	__I  tU32        RFL;                      /**<Receive FIFO Level, offset:0x84*/
	tU32 RESERVED_3[7];
	__IO tU32        HTX;                      /**<Halt TX, offset:0xA4*/
	__O  tU32        DMASA;                    /**<DMA Software Acknowledge, offset:0xA8*/
	tU32 RESERVED_4[5];
	__O tU32 DLF;
	tU32 RESERVED_5[15];
	__IO tU32        SGW;                      /**<Single Wire and Loop Mode control, offset:0x100*/

}tUART;


/*--------------------------------------------------------------------------------*/
/*CongTH*/
typedef struct UART_MemMap1 {

} volatile UART_Ptr;


/* IER Bit Fields */
#define UART_IER_ERBFI_MASK                     0x1u
#define UART_IER_ERBFI_SHIFT                    0

#define UART_IER_ETBEI_MASK                     0x2u
#define UART_IER_ETBEI_SHIFT                    1

#define UART_IER_ELSI_MASK                      0x4u
#define UART_IER_ELSI_SHIFT                     1

#define UART_IER_EDSSI_MASK                      0x8u
#define UART_IER_EDSSI_SHIFT                     1
/* LCR Bit Fields */
#define UART_LCR_BRK13_MASK                        0x40u
#define UART_LCR_BRK13_SHIFT                       6

#define UART_LCR_DLS_MASK                       0x3u
#define UART_LCR_DLS_SHIFT                      0

#define UART_LCR_STOP_MASK                      0x4u
#define UART_LCR_STOP_SHIFT                     2

#define UART_LCR_DLAB_MASK                      0x80u
#define UART_LCR_DLAB_SHIFT                     7

/* PATTERN Bit Fields */
#define UART_PATTERN_BC_MASK                 0x80u
#define UART_PATTERN_BC_SHIFT                7

/* SGW Bit Fields */
#define UART_SGW_TXDIR_MASK                     0x1u
#define UART_SGW_TXDIR_SHIFT                    0

#define UART_SGW_EN_MASK						0x02u
#define UART_SGW_EN_SHIFT                       1

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
/**
	* @defgroup LIN_BreakLenght_Select LIN同步间隔段长度选择
	* @{
	*/
#define UART_LINBreakLength_10b              ((uint8_t)0x00)   /* 至少生成10bit同步间隔段长度 */
#define UART_LINBreakLength_13b              ((uint8_t)0x40)   /* 至少生成13bit同步间隔段长度 */

/* UARTD - UART Data Register */
#define UARTTHR_WAKE_SIGNAL        128

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



#endif /* Lin register */

/**
* @}
*/
