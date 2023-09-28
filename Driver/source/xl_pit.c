/**
  ******************************************************************************
  * @file     xl_pit.c
  * @author   Kirk ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about PIT firmware program 
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
#include "xl_pit.h"

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup PIT PIT Module 
  * @brief PIT Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
	#define PIT_CLEAR_MASK     ((uint8_t)0x02)	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @defgroup PIT_Private_Functions
  * @{
  */ 
	
/**
  * @brief  PITĬ�ϳ�ʼ��
  * @param  None
  * @retval None
  */
void PIT_DeInit(void)
{
	/* Deinitializes to default reset values */
	PIT->CHANNEL[0].CTR = 0x00;
	PIT->CHANNEL[1].CTR = 0x00;
	PIT->CHAIN=0x00;	
}

/**
  * @brief PTT��ʼ��
  * @param  Channel: PITͨ����
  *		�����������ȡ�����ֵ:
  *        @arg PIT_Channel0: PITͨ��0
  *        @arg PIT_Channel1: PITͨ��1
  * @param  PIT_Mode: ģʽѡ��
  *		�����������ȡ�����ֵ:
  *        @arg PIT_Run_Mode: ��������ģʽ
  *        @arg PIT_Count_Mode: �û��������ģʽ
  * @param  CLK_DIV: ʱ�ӷ�Ƶ(0~65535)
  * @retval None
  */
void PIT_Init(uint8_t Channel,uint8_t PIT_Mode,uint16_t CLK_DIV)
{
	uint32_t tmpreg;

	/*---------------------------- PIT CTR Configuration ------------------------*/	
	/* Get the PIT CTR value. */
	tmpreg = PIT->CHANNEL[Channel].CTR ;

	/* Clear MODE bit Value in CTR register.*/
	tmpreg &= ~PIT_CLEAR_MASK;

	/* Set the bit MODE in CTR Register. */
	tmpreg |= (PIT_Mode);

	//Aaron He add clock divider
	PIT->PIT_DIV[Channel] = CLK_DIV;

	/* Write to PIT CTR Register. */
	PIT->CHANNEL[Channel].CTR = tmpreg ;
}

/**
  * @brief PITʹ��
  * @param  Channel: PITͨ����
  *		�����������ȡ�����ֵ:
  *        @arg PIT_Channel0: PITͨ��0
  *        @arg PIT_Channel1: PITͨ��1
  * @param  NewState: ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: PITʹ��
  *			@arg DISABLE: PITʧ��
  * @retval None.
  */
void PIT_EnableCmd(uint8_t Channel,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Enable PIT bits for PIT. */
		PIT->CHANNEL[Channel].CTR |= PIT_CTR_EN_MASK;
	}
	else 
	{
		/* Disable PIT bits for PIT. */
		PIT->CHANNEL[Channel].CTR &= ~PIT_CTR_EN_MASK;
	}
}

/**
  * @brief PIT�ж�ʹ��
  * @param  Channel: PITͨ����
  *		�����������ȡ�����ֵ:
  *        @arg PIT_Channel0: PITͨ��0
  *        @arg PIT_Channel1: PITͨ��1
  * @param  NewState: ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: PITʹ��
  *			@arg DISABLE: PITʧ��
  * @retval None.
  */
void PIT_InterruptEn(uint8_t Channel,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* ENABLE PIT interrupt for PIT. */
		PIT->CHANNEL[Channel].CTR &= ~PIT_CTR_IM_MASK;			
	}
	else
	{
		/* DISABLE PIT interrupt for PIT. */
		PIT->CHANNEL[Channel].CTR |= PIT_CTR_IM_MASK;
	}
}

/**
  * @brief ΪPIT�����ŵ�ģֵ.
  * @param  Channel: PITͨ����
  *		�����������ȡ�����ֵ:
  *        @arg PIT_Channel0: PITͨ��0
  *        @arg PIT_Channel1: PITͨ��1
  * @param  loadVal: �����ص�PIT�е�ֵ.
  * @retval None.
  */
void PIT_SetLoadCount(uint8_t Channel,uint32_t loadVal)
{
	/* Value to be load into PIT. */
	PIT->CHANNEL[Channel].LC = loadVal ;
}

/**
  * @brief �õ�PIT��ͨ������ֵ.
  * @param  Channel: PITͨ����
  *		�����������ȡ�����ֵ:
  *        @arg PIT_Channel0: PITͨ��0
  *        @arg PIT_Channel1: PITͨ��1
  * @retval current Value.���ص���ֵ.
  */
uint32_t PIT_GetCurrentVal(uint8_t Channel)
{
	uint32_t currentVal;
	
	/* get the current Value. */
	currentVal = PIT->CHANNEL[Channel].CV ;

	/* return the value. */
	return currentVal ;
}

/**
  * @brief ���PIT�ж�.
  * @param  Channel: PITͨ����
  *		�����������ȡ�����ֵ:
  *        @arg PIT_Channel0: PITͨ��0
  *        @arg PIT_Channel1: PITͨ��1
  * @retval None.
  */
void PIT_ClrInterrupt(uint8_t Channel)
{
	/* clear the interrupt from PIT.*/
	PIT->CHANNEL[Channel].EOI;
}

/**
  * @brief ����PIT���ж�״̬.
  * @param  Channel: PITͨ����
  *		�����������ȡ�����ֵ:
  *        @arg PIT_Channel0: PITͨ��0
  *        @arg PIT_Channel1: PITͨ��1
  * @retval interrupt status.�����ж�״̬.
  */
ITStatus PIT_GetIntStatus(uint8_t Channel)
{
	/* return interrupt status. */
	return ((PIT->CHANNEL[Channel].IS & PIT_IS_IS_MASK) == PIT_IS_IS_MASK);
}

/**
  * @brief ��ȡPIT���ж�״̬.
  * @retval �ж�״̬
  */
uint8_t PIT_GetAllIntStatus(void)
{
	/* return all interrupt status. */
	return (uint8_t)(PIT->AIS & PIT_AIS_AIS_MASK);
}

/**
  * @brief ������л�е��ж�.
  * @param  None
  * @retval None.
  */
void PIT_ClrAllInterrupt(void)
{
	/* Dummy reading the register and clear all active interrupts. */
	(void)(PIT->AEOI);
}

/**
  * @brief ��ȡ�������ж�״̬.
  * @param  None
  * @retval �����������ж�״̬
  */
uint8_t PIT_GetRawIntStatus(void)
{
	/* return unmasked interrupt status. */
	return (uint8_t)(PIT->RAWIS & PIT_RAWIS_RAWIS_MASK);
}


/**
  * @brief PIT ����ģʽ���û����.
  * @param  NewState: ʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ����ģʽʹ��
  *			@arg DISABLE: ����ģʽʧ��
  * @retval None.
  */
void PIT_FreezeCmd(FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* Timers are stopped in debug mode . */
		PIT->CHAIN |= PIT_DEBUG_FRZ_MASK;			
	}
	else
	{
		/* Timers continue to run in debug mode . */
		PIT->CHAIN &= ~PIT_DEBUG_FRZ_MASK;
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

