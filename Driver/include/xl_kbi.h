/**
  ******************************************************************************
  * @file     xl_kbi.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the KBI 
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
#ifndef __XL_KBI_H__
#define __XL_KBI_H__

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
/* Register define ------------------------------------------------------------*/
/* PE Bit Fields */
#define KBI_PE_KBIPE_MASK                        0xFFFFFFFFu
#define KBI_PE_KBIPE_SHIFT                       0
/* ES Bit Fields */
#define KBI_ES_KBEDG_MASK                        0xFFFFFFFFu
#define KBI_ES_KBEDG_SHIFT                       0
/* SC Bit Fields */
#define KBI_SC_KBMOD_MASK                        0x1u
#define KBI_SC_KBMOD_SHIFT                       0
#define KBI_SC_KBIE_MASK                         0x2u
#define KBI_SC_KBIE_SHIFT                        1
#define KBI_SC_KBACK_MASK                        0x4u
#define KBI_SC_KBACK_SHIFT                       2
#define KBI_SC_KBF_MASK                          0x8u
#define KBI_SC_KBF_SHIFT                         3
#define KBI_SC_KBSPEN_MASK                       0x10u
#define KBI_SC_KBSPEN_SHIFT                      4
#define KBI_SC_RSTKBSP_MASK                      0x20u
#define KBI_SC_RSTKBSP_SHIFT                     5
/* SP Bit Fields */
#define KBI_SP_SP_MASK                           0xFFFFFFFFu
#define KBI_SP_SP_SHIFT                          0

/** KBI - Register Layout Typedef */
typedef struct {
  __IO uint32_t PE;                                /*!< KBI 引脚使能寄存器, offset: 0x0 */
  __IO uint32_t ES;                                /*!< KBI 边沿选择寄存器, offset: 0x4 */
  __IO uint32_t SC;                                /*!< KBI 状态和控制寄存器, offset: 0x8 */
  __I  uint32_t SP;                                /*!< KBI 源引脚寄存器, offset: 0xC */
} KBI_Type, *KBI_MemMapPtr;
extern KBI_Type * KBI0;
extern KBI_Type * KBI1;

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup KBI 
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/**
 * @brief KBI 初始化结构体定义
 */
typedef struct
{	
	uint32_t  KBI_SPRegValue;          /*!< KBI源引脚 */
	uint32_t  KBI_DetectMode;          /*!< KBI检测模式 */
	
}KBI_InitTypeDef; 

/* Exported constants --------------------------------------------------------*/
/** @defgroup KBI_Exported_Constants KBI模块使用参数定义
  * @{
  */

/** @defgroup KBI_SourcePin_Enable KBI源引脚使能
  * @{
  */
#define KBI_SP_RealValue              				(uint8_t)0x00          /*!< 读取的键盘源引脚的实时值 */
#define KBI_SP_LatchedValue           				(uint8_t)0x10          /*!< 当中断标志出现时要读取的KBxSP寄存器中的锁存值 */
/**
	* @}
	*/

/** @defgroup KBI_Detection_Mode KBI触发模式选择
  * @{
  */
#define KBI_Detect_Edge               				(uint8_t)0x0           /*!< KBI仅检测边沿触发 */
#define KBI_Detect_EdgeANDLevel       				(uint8_t)0x1           /*!< KBI检测边沿和电平触发 */
/**
	* @}
	*/
	
/** @defgroup KBI_EdgeLevel_Seclect KBI触发边沿和电平定义
  * @{
  */	
#define KBI_FallEdge_LowLevel             		0                 /*!< 键盘检测下降沿和低电平 */
#define KBI_RiseEdge_HighLevel           		 	1                 /*!< 键盘检测上升沿和高电平 */
/**
	* @}
	*/

/** @defgroup KBI_Pin_Seclect KBI通道引脚选择
  * @{
  */	
#define  KBI_P0                  						0                    /*!< 引脚0. */
#define  KBI_P1 	             						1                      /*!< 引脚1. */	
#define  KBI_P2 	             						2                      /*!< 引脚2. */	
#define  KBI_P3 	             						3                      /*!< 引脚3. */	
#define  KBI_P4	                 						4                    /*!< 引脚4. */	
#define  KBI_P5	                 						5                    /*!< 引脚5. */	
#define  KBI_P6	                 						6                    /*!< 引脚6. */	
#define  KBI_P7	                 						7                    /*!< 引脚7. */	
#define  KBI_P8	                 						8                    /*!< 引脚8. */	
#define  KBI_P9	                 						9                    /*!< 引脚9. */	
#define  KBI_P10	             						10                     /*!< 引脚10. */	
#define  KBI_P11	             						11                     /*!< 引脚11. */	
#define  KBI_P12	             						12                     /*!< 引脚12. */	
#define  KBI_P13	             						13                     /*!< 引脚13. */	
#define  KBI_P14	             						14                     /*!< 引脚14. */	
#define  KBI_P15	             						15                     /*!< 引脚15. */	
#define  KBI_P16	             						16                     /*!< 引脚16. */	
#define  KBI_P17	             						17                     /*!< 引脚17. */	
#define  KBI_P18	             						18                     /*!< 引脚18. */	
#define  KBI_P19	             						19                     /*!< 引脚19. */	
#define  KBI_P20	            						20                     /*!< 引脚20. */	
#define  KBI_P21	             						21                     /*!< 引脚21. */	
#define  KBI_P22	             						22                     /*!< 引脚22. */	
#define  KBI_P23	             						23                     /*!< 引脚23. */	
#define  KBI_P24	             						24                     /*!< 引脚24. */	
#define  KBI_P25	             						25                     /*!< 引脚25. */	
#define  KBI_P26	             						26                     /*!< 引脚26. */	
#define  KBI_P27	             						27                     /*!< 引脚27. */	
#define  KBI_P28	             						28                     /*!< 引脚28. */	
#define  KBI_P29	             						29                     /*!< 引脚29. */	
#define  KBI_P30	             						30                     /*!< 引脚30. */	
#define  KBI_P31	             						31                     /*!< 引脚31. */	
/**
	* @}
	*/
	


/**
	* @}
	*/



/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void KBI_Deinit(KBI_Type *KBIx);
void KBI_Init(KBI_Type *KBIx, const KBI_InitTypeDef *KBI_InitStruct);
void KBI_PinConfig(KBI_Type *KBIx, uint8_t KBI_Pin,uint8_t EdgeSelect);
void KBI_BatchPinConfig(KBI_Type *KBIx, uint32_t KBI_Pin,uint32_t EdgeRegSelect);
void KBI_InterruptEn(KBI_Type *KBIx,FunctionalState NewState);
FlagStatus KBI_GetInterruptFlag(const KBI_Type *KBIx);
void KBI_ClrInterruptFlag(KBI_Type *KBIx);
void KBI_RstSP(KBI_Type *KBIx);
uint32_t KBI_GetSP(const KBI_Type *KBIx);

	
#ifdef __cplusplus
}
#endif

#endif /*__XL_KBI_H__ */	

/**
  * @}
  */

/**
  * @}
  */

