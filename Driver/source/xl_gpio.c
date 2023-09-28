/**
  ******************************************************************************
  * @file     xl_gpio.c
  * @author   kirk  ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about GPIO firmware program 
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
#include "xl_gpio.h"

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO GPIO Module 
  * @brief GPIO Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
	
/** @defgroup GPIO_Private_Functions
  * @{
  */ 

/**
 * @brief  GPIO����ָ�Ĭ��ֵ.
 * @param  GPIOx: GPIO_Type����ָ�룬������GPIO���мĴ���.
 * @retval None
 */
void GPIO_DeInit(GPIO_Type *GPIOx)
{
	GPIOx->PDOR = 0x00000000u;
	GPIOx->PSOR = 0x00000000u;
	GPIOx->PCOR = 0x00000000u;
	GPIOx->PTOR = 0x00000000u;
	GPIOx->PDDR = 0x00000000u;
	GPIOx->PIDR = 0xFFFFFFFFu;
}


/**
 * @brief  ����GPIO�ķ���
 * @param  gpioPin: GPIO Pin Name(GPIO_PTA0~GPIO_PTI6)
 * @param  GPIO_Mode: �˿����ݷ���.
 *		�����������ȡ�����ֵ:
 *			@arg GPIO_Direction_Input������     
 *			@arg GPIO_Direction_Output�����    
 * @retval None
 */
void GPIO_SetPinDir(uint8_t gpioPin, GPIO_Direction_Mode GPIO_Mode)
{
	/* when gpioPin less than GPIO_PortD7 use GPIOA
	 * (1-629)�� 30 �� ͨ������/�����GPIO��
	 * (1-632)30.3.1 GPIO �Ĵ���λ����
	 * (1-637)30.3.6 �˿���������Ĵ���(PDIR)*/
	if(gpioPin < (uint8_t)GPIO_PTE0)
	{
		switch (GPIO_Mode)
		{
			case GPIO_Direction_Output:
				GPIOA->PDDR |= ((uint32_t)1	<< (uint8_t)gpioPin) ;
				GPIOA->PIDR |= ((uint32_t)1	<< (uint8_t)gpioPin) ;
				break ;
			case GPIO_Direction_Input:
				GPIOA->PDDR &= ~((uint32_t)1	<< (uint8_t)gpioPin);
				GPIOA->PIDR &= ~((uint32_t)1	<< (uint8_t)gpioPin) ;
				break ;
			case GPIO_Direction_High_Z:
			default:
				GPIOA->PDDR &= ~((uint32_t)1	<< (uint8_t)gpioPin) ;
				GPIOA->PIDR |= ((uint32_t)1	<< (uint8_t)gpioPin) ;
				break;
		}
	}
	/* when gpioPin less than GPIO_PortH7 use GPIOB */
	else if(gpioPin < (uint8_t)GPIO_PTI0)
	{
		switch (GPIO_Mode )
		{
			case GPIO_Direction_Output:
				GPIOB->PDDR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)32));
				GPIOB->PIDR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)32));
				break ;
			case GPIO_Direction_Input:
				GPIOB->PDDR &=  ~((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)32));
				GPIOB->PIDR &=  ~((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)32));
				break ;
			case GPIO_Direction_High_Z:
			default:
				GPIOB->PDDR &= ~((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)32));
				GPIOB->PIDR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)32));
				break;			
		}
	}
	/* then use GPIOC */
	else 
	{
		switch (GPIO_Mode )
		{
			case GPIO_Direction_Output:
				GPIOC->PDDR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)64));
				GPIOC->PIDR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)64));
				break ;
			case GPIO_Direction_Input:
				GPIOC->PDDR &=  ~((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)64));
				GPIOC->PIDR &=  ~((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)64));
				break ;
			case GPIO_Direction_High_Z:
			default:
				GPIOC->PDDR &= ~((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)64));
				GPIOC->PIDR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)64));
				break;
		}
	}
}

/**
 * @brief  ����GPIO�ĵ�ƽ
 * @param  gpioPin: GPIO Pin Name(GPIO_PTA0~GPIO_PTI6)
 * @param  Output: ����ĵ�ƽ
 *		�����������ȡ�����ֵ:
 *			@arg GPIO_Output_Low���͵�ƽ    
 *			@arg GPIO_Output_High���ߵ�ƽ    
 * @retval None
 */
void GPIO_SetPinOutput(uint8_t gpioPin, GPIO_Output_Level Output)
{	
	/* when gpioPin less than GPIO_PortD7 use GPIOA */
	if(gpioPin < (uint8_t)GPIO_PTE0)
	{
		if(Output != GPIO_Output_Low)
		{
			/* output high 1 */
			GPIOA->PDOR |= ((uint32_t)1	<< (uint8_t)gpioPin) ;
		}
		else 
		{
			/* output low 0 */
			GPIOA->PDOR &= ~((uint32_t)1	<< (uint8_t)gpioPin);
		}
	}	
	/* when gpioPin less than GPIO_PortH7 use GPIOB */
	else if(gpioPin < (uint8_t)GPIO_PTI0)
	{
		if(Output != GPIO_Output_Low)
		{
			/* output high 1 */
			GPIOB->PDOR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)32));
		}
		else 
		{
			/* output high 0 */
			GPIOB->PDOR &= ~((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)32));
		}
	}
	/* else use GPIOC */
	else 
	{
		if(Output != GPIO_Output_Low)
		{
			/* output high 1 */
			GPIOC->PDOR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)64));
		}
		else 
		{
			/* output high 0 */
			GPIOC->PDOR &= ~((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)64));
		}
	}
}

/**
 * @brief GPIO����ߵ�ƽ MARK-�����ƽ
 * @param  gpioPin: GPIO Pin Name(GPIO_PTA0~GPIO_PTI6)
 * @retval None
 */
void GPIO_SetPin(uint8_t gpioPin)
{
	/* when gpioPin less than GPIO_PortD7 use GPIOA */
	if(gpioPin < (uint8_t)GPIO_PTE0)
	{
		GPIOA->PSOR |= ((uint32_t)1	<<	(uint8_t)gpioPin) ;
	}
	/* when gpioPin less than GPIO_PortH7 use GPIOB */
	else if(gpioPin < (uint8_t)GPIO_PTI0)
	{
		GPIOB->PSOR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)32));
	}
	/* else use GPIOC */
	else 
	{
		GPIOC->PSOR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)64));
	}	
}

/**
 * @brief GPIO����͵�ƽ	MARK-�����ƽ
 * @param  gpioPin: GPIO Pin Name(GPIO_PTA0~GPIO_PTI6)
 * @retval None
 */
void GPIO_ClrPin(uint8_t gpioPin)
{
	/* when gpioPin less than GPIO_PortD7 use GPIOA */
	if(gpioPin < (uint8_t)GPIO_PTE0)
	{
		GPIOA->PCOR |= ((uint32_t)1	<<	(uint8_t)gpioPin);
	}
	/* when gpioPin less than GPIO_PortH7 use GPIOB */
	else if(gpioPin < (uint8_t)GPIO_PTI0)
	{
		GPIOB->PCOR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)32));
	}
	/* else use GPIOC */
	else
	{
		GPIOC->PCOR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)64));
	}	
}

/**
 * @brief GPIO�����ƽ��ת
 * @param  gpioPin: GPIO Pin Name(GPIO_PTA0~GPIO_PTI6)
 * @retval None
 */
void GPIO_TogglePin(uint8_t gpioPin)
{
	/* when gpioPin less than GPIO_PortD7 use GPIOA */
	if(gpioPin < (uint8_t)GPIO_PTE0)
	{
		GPIOA->PTOR |= ((uint32_t)1	<<	(uint8_t)gpioPin) ;
	}
	/* when gpioPin less than GPIO_PortH7 use GPIOB */
	else if(gpioPin < (uint8_t)GPIO_PTI0)
	{
		GPIOB->PTOR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)32));
	}
	/* else use GPIOC */
	else 
	{
		GPIOC->PTOR |= ((uint32_t)1	<<	((uint8_t)gpioPin - (uint8_t)64));
	}
}

/**
 * @brief GPIO���˿ڼĴ���ֵ
 * @param  gpioPin: GPIO Pin Name(GPIO_PTA0~GPIO_PTI6)
 * @retval PDIR�Ĵ�����ֵ.
 */
uint32_t GPIO_ReadReg(const GPIO_Type *GPIOx)
{
	uint32_t inputData;

	inputData = GPIOx->PDIR ;

	return inputData ;
}
	
/**
 * @brief GPIO���˿ڵ�ƽ
 * @param  gpioPin: GPIO Pin Name(GPIO_PTA0~GPIO_PTI6)
 * @retval GPIO_Pin vlaue�������ĵ�ƽ
 *		�����������ȡ�����ֵ:
 *      @arg GPIO_Input_Low :����͵�ƽ
 *      @arg GPIO_Input_High :����ߵ�ƽ
 */
GPIO_Input_Def GPIO_ReadPin(uint8_t gpioPin)
{
	GPIO_Input_Def ret;
	
	/* when gpioPin less than GPIO_PortD7 use GPIOA */
	if(gpioPin < (uint8_t)GPIO_PTE0)
	{
		if(  ((GPIOA->PDIR>>((uint8_t)gpioPin))& (uint32_t)1) != 0u)
		{
			ret = GPIO_Input_High;
		}
		else
		{
			ret = GPIO_Input_Low;
		}
	}
	/* when gpioPin less than GPIO_PortH7 use GPIOB */
	else if(gpioPin < (uint8_t)GPIO_PTI0)
	{
		if(((GPIOB->PDIR>>((uint8_t)gpioPin - (uint8_t)32)) & (uint32_t)1) != 0u)
		{
			ret = GPIO_Input_High;
		}
		else
		{
			ret = GPIO_Input_Low;
		}
	}
	/* else use GPIOC */
	else 
	{
		if(((GPIOC->PDIR>>((uint8_t)gpioPin - (uint8_t)64)) & (uint32_t)1) != 0u)
		{
			ret = GPIO_Input_High;
		}
		else
		{
			ret = GPIO_Input_Low;
		}
	}

	return ret;
}


/**
 * @brief GPIO���˿ڷ���
 * @param  gpioPin: GPIO Pin Name(GPIO_PTA0~GPIO_PTI6)
 * @retval GPIO_Direction_Seclect����������
 *		�����������ȡ�����ֵ:
 *      @arg GPIO_Direction_Input :����͵�ƽ
 *      @arg GPIO_Direction_Output :����ߵ�ƽ
 */
GPIO_Direction_Mode GPIO_ReadPinDir(uint8_t gpioPin)
{
	GPIO_Direction_Mode ret;
	
	/* when gpioPin less than GPIO_PortD7 use GPIOA */
	if(gpioPin < (uint8_t)GPIO_PTE0)
	{
		if(  ((GPIOA->PDDR>>((uint8_t)gpioPin))& (uint32_t)1) != 0u)
		{
			ret = GPIO_Direction_Output;
		}
		else
		{
			if(  ((GPIOA->PIDR>>((uint8_t)gpioPin))& (uint32_t)1) != 0u)
			{
				ret = GPIO_Direction_High_Z;
			}
			else
			{
				ret = GPIO_Direction_Input; 
			}
		}
	}
	/* when gpioPin less than GPIO_PortH7 use GPIOB */
	else if(gpioPin < (uint8_t)GPIO_PTI0)
	{
		if(((GPIOB->PDDR>>((uint8_t)gpioPin - (uint8_t)32)) & (uint32_t)1) != 0u)
		{
			ret = GPIO_Direction_Output;
		}
		else
		{
			if(((GPIOB->PIDR>>((uint8_t)gpioPin - (uint8_t)32)) & (uint32_t)1) != 0u)
			{
				ret = GPIO_Direction_High_Z;
			}
			else
			{
				ret = GPIO_Direction_Input;
			}
		}
	}
	/* else use GPIOC */
	else 
	{
		if(((GPIOC->PDDR>>((uint8_t)gpioPin - (uint8_t)64)) & (uint32_t)1) != 0u)
		{
			ret = GPIO_Direction_Output;
		}
		else
		{
			if(((GPIOC->PIDR>>((uint8_t)gpioPin - (uint8_t)64)) & (uint32_t)1) != 0u)
			{
				ret = GPIO_Direction_High_Z;
			}
			else
			{
				ret = GPIO_Direction_Input;
			}
		}
	}

	return ret;
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

