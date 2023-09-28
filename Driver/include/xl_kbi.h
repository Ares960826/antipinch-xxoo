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
  __IO uint32_t PE;                                /*!< KBI ����ʹ�ܼĴ���, offset: 0x0 */
  __IO uint32_t ES;                                /*!< KBI ����ѡ��Ĵ���, offset: 0x4 */
  __IO uint32_t SC;                                /*!< KBI ״̬�Ϳ��ƼĴ���, offset: 0x8 */
  __I  uint32_t SP;                                /*!< KBI Դ���żĴ���, offset: 0xC */
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
 * @brief KBI ��ʼ���ṹ�嶨��
 */
typedef struct
{	
	uint32_t  KBI_SPRegValue;          /*!< KBIԴ���� */
	uint32_t  KBI_DetectMode;          /*!< KBI���ģʽ */
	
}KBI_InitTypeDef; 

/* Exported constants --------------------------------------------------------*/
/** @defgroup KBI_Exported_Constants KBIģ��ʹ�ò�������
  * @{
  */

/** @defgroup KBI_SourcePin_Enable KBIԴ����ʹ��
  * @{
  */
#define KBI_SP_RealValue              				(uint8_t)0x00          /*!< ��ȡ�ļ���Դ���ŵ�ʵʱֵ */
#define KBI_SP_LatchedValue           				(uint8_t)0x10          /*!< ���жϱ�־����ʱҪ��ȡ��KBxSP�Ĵ����е�����ֵ */
/**
	* @}
	*/

/** @defgroup KBI_Detection_Mode KBI����ģʽѡ��
  * @{
  */
#define KBI_Detect_Edge               				(uint8_t)0x0           /*!< KBI�������ش��� */
#define KBI_Detect_EdgeANDLevel       				(uint8_t)0x1           /*!< KBI�����غ͵�ƽ���� */
/**
	* @}
	*/
	
/** @defgroup KBI_EdgeLevel_Seclect KBI�������غ͵�ƽ����
  * @{
  */	
#define KBI_FallEdge_LowLevel             		0                 /*!< ���̼���½��غ͵͵�ƽ */
#define KBI_RiseEdge_HighLevel           		 	1                 /*!< ���̼�������غ͸ߵ�ƽ */
/**
	* @}
	*/

/** @defgroup KBI_Pin_Seclect KBIͨ������ѡ��
  * @{
  */	
#define  KBI_P0                  						0                    /*!< ����0. */
#define  KBI_P1 	             						1                      /*!< ����1. */	
#define  KBI_P2 	             						2                      /*!< ����2. */	
#define  KBI_P3 	             						3                      /*!< ����3. */	
#define  KBI_P4	                 						4                    /*!< ����4. */	
#define  KBI_P5	                 						5                    /*!< ����5. */	
#define  KBI_P6	                 						6                    /*!< ����6. */	
#define  KBI_P7	                 						7                    /*!< ����7. */	
#define  KBI_P8	                 						8                    /*!< ����8. */	
#define  KBI_P9	                 						9                    /*!< ����9. */	
#define  KBI_P10	             						10                     /*!< ����10. */	
#define  KBI_P11	             						11                     /*!< ����11. */	
#define  KBI_P12	             						12                     /*!< ����12. */	
#define  KBI_P13	             						13                     /*!< ����13. */	
#define  KBI_P14	             						14                     /*!< ����14. */	
#define  KBI_P15	             						15                     /*!< ����15. */	
#define  KBI_P16	             						16                     /*!< ����16. */	
#define  KBI_P17	             						17                     /*!< ����17. */	
#define  KBI_P18	             						18                     /*!< ����18. */	
#define  KBI_P19	             						19                     /*!< ����19. */	
#define  KBI_P20	            						20                     /*!< ����20. */	
#define  KBI_P21	             						21                     /*!< ����21. */	
#define  KBI_P22	             						22                     /*!< ����22. */	
#define  KBI_P23	             						23                     /*!< ����23. */	
#define  KBI_P24	             						24                     /*!< ����24. */	
#define  KBI_P25	             						25                     /*!< ����25. */	
#define  KBI_P26	             						26                     /*!< ����26. */	
#define  KBI_P27	             						27                     /*!< ����27. */	
#define  KBI_P28	             						28                     /*!< ����28. */	
#define  KBI_P29	             						29                     /*!< ����29. */	
#define  KBI_P30	             						30                     /*!< ����30. */	
#define  KBI_P31	             						31                     /*!< ����31. */	
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

