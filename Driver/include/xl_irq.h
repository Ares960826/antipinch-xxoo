/**
  ******************************************************************************
  * @file     xl_irq.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the IRQ
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
#ifndef XL_IRQ_H__
#define XL_IRQ_H__

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
/* Register define ------------------------------------------------------------*/	

/* SC Bit Fields */
#define IRQ_SC_IRQMOD_MASK                       0x1u
#define IRQ_SC_IRQMOD_SHIFT                      0
#define IRQ_SC_IRQIE_MASK                        0x2u
#define IRQ_SC_IRQIE_SHIFT                       1
#define IRQ_SC_IRQACK_MASK                       0x4u
#define IRQ_SC_IRQACK_SHIFT                      2
#define IRQ_SC_IRQF_MASK                         0x8u
#define IRQ_SC_IRQF_SHIFT                        3
#define IRQ_SC_IRQPE_MASK                        0x10u
#define IRQ_SC_IRQPE_SHIFT                       4
#define IRQ_SC_IRQEDG_MASK                       0x20u
#define IRQ_SC_IRQEDG_SHIFT                      5
#define IRQ_SC_IRQPDD_MASK                       0x40u
#define IRQ_SC_IRQPDD_SHIFT                      6

/** IRQ - Register Layout Typedef */
typedef struct {
  __IO uint32_t SC[16];                          /*!< 外部中断引脚请求状态和控制寄存器=>(1-306)22.3.1 状态和控制寄存器(SC), array offset: 0x00, array step: 0x4  */
} IRQ_Type, *IRQ_MemMapPtr;
extern IRQ_Type * IRQ;


/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup IRQ
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 
	
/**
 * @brief IRQ初始化结构体的定义
 *
 */
typedef struct
{	
	uint32_t  IRQ_EdgeSelect;                                     /*!< 中断请求边沿选择 */
	uint32_t  IRQ_ModeSelect;                                     /*!< 中断检测模式选择 */
	
}IRQ_InitTypeDef, *IRQ_InitConfigPtr;



/* Exported constants --------------------------------------------------------*/
/** @defgroup IRQ_Exported_Constants IRQ模块使用参数定义
  * @{
  */

/**
	* @defgroup IRQ_RequestEdge_Select IRQ触发边沿或电平选择
	* @{
	*/ 
#define	IRQ_Falledge_Lowlevel                		(uint8_t)0x00           /*!< 下降沿和低电平触发 */
#define	IRQ_Riseedge_Highlevel               		(uint8_t)0x20           /*!< 上升沿和高电平触发 */
/**
	* @}
	*/
	
/**
	* @defgroup IRQ_DetectionMode_Select IRQ触发模式定义
	* @{
	*/ 	
#define	IRQ_Detect_Edge                      		(uint8_t)0x0           /*!< 仅边沿触发 */
#define	IRQ_Detect_EdgeANDLevel              		(uint8_t)0x1           /*!< 边沿触发和电平触发 */
/**
	* @}
	*/
	

/**
	* @defgroup IRQ_ChannelList_Select IRQ通道选择
	* @{
	*/ 
#define  EXTI0                 0                     /*!< 外部中断通道0. */
#define  EXTI1 	               1                     /*!< 外部中断通道1. */	
#define  EXTI2 	               2                     /*!< 外部中断通道2. */	
#define  EXTI3 	               3                     /*!< 外部中断通道3. */	
#define  EXTI4	               4                     /*!< 外部中断通道4. */	
#define  EXTI5	               5                     /*!< 外部中断通道5. */	
#define  EXTI6	               6                     /*!< 外部中断通道6. */	
#define  EXTI7	               7                     /*!< 外部中断通道7. */	
#define  EXTI8	               8                     /*!< 外部中断通道8. */	
#define  EXTI9	               9                     /*!< 外部中断通道9. */	
#define  EXTI10	               10                    /*!< 外部中断通道10. */	
#define  EXTI11	               11                    /*!< 外部中断通道11. */	
#define  EXTI12	               12                    /*!< 外部中断通道12. */	
#define  EXTI13	               13                    /*!< 外部中断通道13. */	
#define  EXTI14	               14                    /*!< 外部中断通道14. */	
#define  EXTI15	               15                    /*!< 外部中断通道15. */	
/**
	* @}
	*/
	
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void IRQ_DeInit(IRQ_Type *IRQx,uint8_t IRQ_Channel);
void IRQ_Init(IRQ_Type *IRQx, uint8_t IRQ_Channel, const IRQ_InitTypeDef *IRQ_InitStuct);
void IRQ_PullDevDisableCmd(IRQ_Type *IRQx,uint8_t IRQ_Channel, FunctionalState NewState);
void IRQ_PinEnableCmd(IRQ_Type *IRQx,uint8_t IRQ_Channel,FunctionalState NewState);
void IRQ_InterruptEn(IRQ_Type *IRQx,uint8_t IRQ_Channel,FunctionalState NewState);
FlagStatus IRQ_GetFlag(const IRQ_Type *IRQx,uint8_t IRQ_Channel);
void IRQ_ClrFlag(IRQ_Type *IRQx,uint8_t IRQ_Channel);


#ifdef __cplusplus
}
#endif

#endif /*__XL_IRQ_H__ */	

/**
  * @}
  */

/**
  * @}
  */
