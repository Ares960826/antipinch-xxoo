/**
  ******************************************************************************
  * @file     xl_adc.c
  * @author   kirk  ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about ICS firmware program 
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
#include "xl_adc.h"

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup ADC ADC Module 
  * @brief ADC Driver Modules Library
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
	
/** @defgroup ADC_Private_Functions
  * @{
  */ 	
	
/**
  * @brief  ADCx����Ĵ����ָ�Ĭ��ֵ
  * @param  ADCx:����ADC����.
  * @retval None
  */
void ADC_DeInit(ADC_Type* ADCx)
{
	/* Deinitializes to default reset values */	
	ADCx->CR = 0x00000000;

	ADC_SetChannel(ADCx,ADC_CHANNEL_DISABLE);
}

/**
  * @brief  ADC��ʼ��
  * @param  ADCx:����ADC����
  * @param  ADC_InitStruct:ADC��ʼ�����ýṹ��
  * @retval None
  */
void ADC_Init(ADC_Type* ADCx, const ADC_InitTypeDef* ADC_InitStruct)
{
	/*---------------------------- ADCx CR Configuration -----------------*/

	/* Clear MODE��REFSEL��CLKSEL��DIV ��LPE and LSTE bits */
	ADCx->CR &= ~(ADC_CR_MODE_MASK | ADC_CR_REFSEL_MASK | ADC_CR_CLKSEL_MASK | \
							ADC_CR_ADIV_MASK | ADC_CR_LSTE_MASK | ADC_CR_LPE_MASK);
	/* Configures MODE��REFSEL��CLKSEL��DIV ��LPE and LSTE bits */	
	ADCx->CR |= ((ADC_InitStruct->ADC_Mode & ADC_CR_MODE_MASK) | \
				((ADC_InitStruct->ADC_ReferVoltage << ADC_CR_REFSEL_SHIFT) & ADC_CR_REFSEL_MASK)| \
				((ADC_InitStruct->ADC_ClockSource << ADC_CR_CLKSEL_SHIFT) & ADC_CR_CLKSEL_MASK)| \
				(ADC_CR_ECOBD_MASK)|\
				((ADC_InitStruct->ADC_ClkDivide << ADC_CR_ADIV_SHIFT) & ADC_CR_ADIV_MASK));
	
	if(ADC_InitStruct->ADC_LongTimeConvert == ENABLE)
	{
		ADCx->CR |= ADC_CR_LSTE_MASK;
	}
	if(ADC_InitStruct->ADC_LowPowerConvert == ENABLE)
	{
		ADCx->CR |= ADC_CR_LPE_MASK;
	}
}

/**
  * @brief  ADC FIFO���üĴ���
  * @param  ADCx:����ADC����.
  * @param  ADC_FIFOStruct:ADC FIFO���ò����ṹ��
  * @retval None
  */
void ADC_FIFOConfig(ADC_Type* ADCx, const ADC_FIFOTypeDef* ADC_FIFOStruct)
{
	/*---------------------------- ADCx CR Configuration -----------------*/

	/* Clear FSE��FDEP bits */
	ADCx->CR &= ~(ADC_CR_FDEP_MASK | ADC_CR_FSE_MASK);
	/* Configures FSE��FDEP bits */	
	ADCx->CR |= ((ADC_FIFOStruct->ADC_FIFOLevel << ADC_CR_FDEP_SHIFT) & ADC_CR_FDEP_MASK);
	
	if(ADC_FIFOStruct->ADC_ChannelScan == ENABLE)
	{
		ADCx->CR |= ADC_CR_FSE_MASK;
	}
}

/**
  * @brief  ADC Compare�������ú���
  * @param  ADCx:����ADC����.
  * @param  ADC_CompareStruct:ADC Compare���ò����ṹ��
  * @retval None
  */
void ADC_CompareConfig(ADC_Type* ADCx, const ADC_CompareTypeDef* ADC_CompareStruct)
{
	/*---------------------------- ADCx CR Configuration -----------------*/

	/* Clear CFE��CFRE��CFGRE and CFSEL bits */
	ADCx->CR &= ~(ADC_CR_CFRE_MASK | ADC_CR_CFGRE_MASK | ADC_CR_CFE_MASK | ADC_CR_CFSEL_MASK | ADC_CR_COSBEN_MASK);
	/* Configures CFE��CFRE��CFGRE and CFSEL bits */	
	ADCx->CR |= (((ADC_CompareStruct->ADC_CompareMode << ADC_CR_CFRE_SHIFT) & ADC_CR_CFRE_MASK) | \
							((ADC_CompareStruct->ADC_CompareOut << ADC_CR_CFGRE_SHIFT) & ADC_CR_CFGRE_MASK)|  \
							((ADC_CompareStruct->ADC_FIFOCompareOut << ADC_CR_CFSEL_SHIFT) & ADC_CR_CFSEL_MASK));
	
	 if(ADC_CompareStruct->ADC_AutoCompare == ENABLE)
	 {
		 ADCx->CR |= ADC_CR_CFE_MASK;
	 }
	 
	 if(ADC_CompareStruct->ADC_CompareResultSwitch == ENABLE)
	 {
		 ADCx->CR |= ADC_CR_COSBEN_MASK;
	 }

	/* Set the compare value */
	ADCx->CVR &=	~ADC_CVR_CVH_MASK;
	ADCx->CVR |= ((ADC_CompareStruct->ADC_CompareValueHigh<<ADC_CVR_CVH_SHIFT)&ADC_CVR_CVH_MASK);
	
	ADCx->CVR &= ~ADC_CVR_CVL_MASK;
	ADCx->CVR |= (ADC_CompareStruct->ADC_CompareValueLow & ADC_CVR_CVL_MASK);	
}

/**
  * @brief  ADCʹ�ܺ���
  * @param  ADCx:����ADC����.
  * @param  State: ADCxʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ADCxʹ��
  *			@arg DISABLE: ADCxʧ��
  */
void ADC_EnableCmd(ADC_Type* ADCx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the selected ADC peripheral */
		ADCx->EHTMR |= ADC_EHTMR_EN_MASK;
	}
	else
	{
		/* Disable the selected ADC peripheral */
		ADCx->EHTMR &= ~ADC_EHTMR_EN_MASK;
	}
}

/**
  * @brief  ADCӲ������ʹ�ܺ���
  * @param  ADCx:����ADC����.
  * @param  State: ADCxʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ADCxʹ��
  *			@arg DISABLE: ADCxʧ��
  */
void ADC_HardwareTriggrMaskCmd(ADC_Type* ADCx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the hardware trigger mask function */
		ADCx->EHTMR |= ADC_EHTMR_HTRGM_MASK;
	}
	else
	{
		/* Disable the hardware trigger mask function */
		ADCx->EHTMR &= ~ADC_EHTMR_HTRGM_MASK;
	}
}

/**
  * @brief  ADC����ģʽѡ��
  * @param  ADCx:����ADC����.
  * @param  ADC_Triggermode: �����Ӳ������.
  *		�����������ȡ�����ֵ:
  *			@arg ADC_SOFTWARE_TRIGGER: �������
  *			@arg ADC_HARDWARE_TRIGGER: Ӳ������
  */
void ADC_SetTriggerMode(ADC_Type* ADCx, uint8_t ADC_Triggermode)
{
	/* software trigger mode */
	if(ADC_Triggermode==ADC_SOFTWARE_TRIGGER)
	{
		 ADCx->CR &=~ADC_CR_TRGSEL_MASK;
	}
	else
	{
		/* hardware trigger mode */
		 ADCx->CR |= ADC_CR_TRGSEL_MASK;
	}
}

/**
  * @brief  ADC�첽ʱ��ѡ��λ
  * @param  ADCx:����ADC����.
  * @param  ADC_ADACKmode: ����ADACKֵ����1.5������ADACKֵ.
  *		�����������ȡ�����ֵ:
  *			@arg ADC_ADACK_NORMAL: ����ADACK
  *			@arg ADC_ADACK_TIMES1P5: 1.5����ADACK
  */
void ADC_ADACKSelect(ADC_Type* ADCx, uint8_t ADC_ADACKmode)
{
	/* select the normal ADACK */
	if(ADC_ADACKmode==ADC_ADACK_NORMAL)
	{
		 ADCx->CR &=~ADC_CR_ADACKS_MASK;
	}
	else
	{
		/* select 1.5 times normal ADACK */
		 ADCx->CR |= ADC_CR_ADACKS_MASK;
	}
}

/**
  * @brief  ADCת��ģʽѡ�񣬵���ת�������첽ת��
  * @param  ADCx:����ADC����.
  * @param  ADC_ConventionMode: һ�λ�������.
  *		�����������ȡ�����ֵ:
  *			@arg ADC_CONVENTION_ONCE:       ����ת��
  *			@arg ADC_CONVENTION_CONTINUOUS: ����ת��
  */
void ADC_SetConventionMode(ADC_Type* ADCx, uint8_t ADC_ConventionMode)
{
	/*!< convert once */
	if(ADC_ConventionMode==ADC_CONVENTION_ONCE)
	{
		 ADCx->CR &=~ADC_CR_CCE_MASK;
	}
	else
	{
		/*!< convert continuous */
		 ADCx->CR |= ADC_CR_CCE_MASK;
	}
}

/**
  * @brief  ADCͨ������
  * @param  ADCx:����ADC����.
  * @param  Channel:ָ��Լ��ͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg ADC_CHANNEL_AD0:       
  *			@arg ADC_CHANNEL_AD1: 
  *			@arg ADC_CHANNEL_AD2:       
  *			@arg ADC_CHANNEL_AD3: 
  *			@arg ADC_CHANNEL_AD4:       
  *			@arg ADC_CHANNEL_AD5:
  *			@arg ADC_CHANNEL_AD6:       
  *			@arg ADC_CHANNEL_AD7: 
  *			@arg ADC_CHANNEL_AD8:       
  *			@arg ADC_CHANNEL_AD9: 
  *			@arg ADC_CHANNEL_AD10:      
  *			@arg ADC_CHANNEL_AD11:  
  *			@arg ADC_CHANNEL_AD12:        
  *			@arg ADC_CHANNEL_AD13:  
  *			@arg ADC_CHANNEL_AD14:       
  *			@arg ADC_CHANNEL_AD15:  
  *			@arg ADC_CHANNEL_AD16:        
  *			@arg ADC_CHANNEL_AD17: 
  *			@arg ADC_CHANNEL_AD18:       
  *			@arg ADC_CHANNEL_AD19: 
  *			@arg ADC_CHANNEL_AD20:       
  *			@arg ADC_CHANNEL_AD21: 
  *			@arg ADC_CHANNEL_TEMPSENSOR:       
  *			@arg ADC_CHANNEL_BANDGAP:
  *			@arg ADC_CHANNEL_AD22:       
  *			@arg ADC_CHANNEL_AD23: 
  *			@arg ADC_CHANNEL_VSS:       
  *			@arg ADC_CHANNEL_VREFH: 
  *			@arg ADC_CHANNEL_VREFL:      
  *			@arg ADC_CHANNEL_DISABLE:   	
  */
void ADC_SetChannel(ADC_Type* ADCx, uint8_t channelno)
{
	/* set channel */
	ADCx->CSR =((uint32_t)channelno & ADC_CSR_ADCH_MASK);
}

/**
  * @brief  �Ƿ�����ADC�����ж�.
  * @param  ADCx:����ADC����.
  * @param  State: ADCxʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ADCxʹ��
  *			@arg DISABLE: ADCxʧ��
  */
void ADC_InterruptEn(ADC_Type* ADCx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the interrupt function */
		ADCx->CR |= ADC_CR_AIE_MASK;
	}
	else
	{
		/* Disable the interrupt function */
		ADCx->CR &= ~ADC_CR_AIE_MASK;
	}
}

/**
  * @brief  �Ƿ�����ADC����DMA����״̬.
  * @param  ADCx:����ADC����.
  * @param  State: ADCxʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ADCxʹ��
  *			@arg DISABLE: ADCxʧ��
  */
void ADC_DMATxEn(ADC_Type* ADCx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the DMA transmit function */
		ADCx->CR |= ADC_CR_DMATXEN_MASK;
	}
	else
	{
		/* Disable the DMA transmit function */
		ADCx->CR &= ~ADC_CR_DMATXEN_MASK;
	}
}

/**
  * @brief  �Ƿ�����ADC����DMA����״̬.
  * @param  ADCx:����ADC����.
  * @param  State: ADCxʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ADCxʹ��
  *			@arg DISABLE: ADCxʧ��
  */
void ADC_DMARxEn(ADC_Type* ADCx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the DMA receive function */
		ADCx->CR |= ADC_CR_DMARXEN_MASK;
	}
	else
	{
		/* Disable the DMA receive function */
		ADCx->CR &= ~ADC_CR_DMARXEN_MASK;
	}
}

/**
  * @brief  ��������ADCx�������.
  * @param  ADCx:����ADC����.
  * @param  NewState:ѡ���Ƿ�״̬.
  * @retval �������ݽ��.
  */
uint16_t ADC_GetConversionValue(const ADC_Type* ADCx)
{
  /* Return the selected ADC conversion value */
  return (uint16_t)(ADCx->RDR & ADC_RDR_DATA_MASK);
}

/**
  * @brief  ��������ADCx�������.
  * @param  ADCx:����ADC����.
  * @param  NewState:ѡ���Ƿ�״̬.
  * @retval ����FIFO�е�����ֵ.
  */
uint16_t ADC_GetFIFOValueCounter(const ADC_Type* ADCx)
{
	/* Return FIFO conversion value number*/
	return (uint16_t) (ADCx->SR & ADC_SR_RFCNT_MASK);
}

/**
  * @brief  ���ADC��־�Ƿ�����.
  * @param  ADCx:����ADC����.
  * @param  ADC_FLAG: ����ض���־.
  *		�����������ȡ�����ֵ:
  *     @arg ADC_FLAG_DATAFIFO_FULL: FIFO��������־.
  *     @arg ADC_FLAG_DATAFIFO_EMPTY:FIFO���ݿձ�־.
  *     @arg ADC_FLAG_CONV_FINISH: ������־.
  *     @arg ADC_FLAG_CONV_BUSY: ��æ��־.
  *     @arg ADC_FLAG_ChannelFIFO_FULL: Channel FIFO��������־.
  *     @arg ADC_FLAG_ChannelFIFO_EMPTY: Channel FIFO���ݿձ�־.
  * @retval ����ADC_FLAG 0���� 1����.
  */
FlagStatus ADC_GetFlagStatus(const ADC_Type* ADCx, uint16_t ADC_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the status of the specified ADC flag */
	if ((ADCx->SR & ADC_FLAG) == ADC_FLAG)
	{
		/* ADC_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* ADC_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the ADC_FLAG status */
	return  bitstatus;
}

/**
  * @brief  ���ADC��־�Ƿ�����.
  * @param  ADCx:����ADC����.
  * @param  ADC_COMPARE_FLAG: �ȽϹ���״̬.
  *		�����������ȡ�����ֵ:
  *     @arg ADC_CHANNEL0_COMPARE_EXCEPTION: ͨ��0�ȽϽ���쳣��־.
  *     @arg ADC_CHANNEL1_COMPARE_EXCEPTION: ͨ��1�ȽϽ���쳣��־.
  *     @arg ADC_CHANNEL2_COMPARE_EXCEPTION: ͨ��2�ȽϽ���쳣��־.
  *     @arg ADC_CHANNEL3_COMPARE_EXCEPTION: ͨ��3�ȽϽ���쳣��־.
  *     @arg ADC_CHANNEL4_COMPARE_EXCEPTION: ͨ��4�ȽϽ���쳣��־.
  *     @arg ADC_CHANNEL5_COMPARE_EXCEPTION: ͨ��5�ȽϽ���쳣��־.
  *     @arg ADC_CHANNEL6_COMPARE_EXCEPTION: ͨ��6�ȽϽ���쳣��־.
  *     @arg ADC_CHANNEL7_COMPARE_EXCEPTION: ͨ��7�ȽϽ���쳣��־.
  *     @arg ADC_CHANNELALL_COMPARE_EXCEPTION: ����ͨ���ȽϽ���쳣��־.
  *     @arg ADC_COMPARE_CFSEL_FLAG: ������ѡ��ʽ��־.
  *     @arg ADC_COMPARE_CFGRE_FLAG: ����ѡ���־.
  *     @arg ADC_COMPARE_CFRE_FLAG: �ȽϷ�ʽѡ���־.
  *     @arg ADC_COMPARE_CFE_FLAG: �Զ��ȽϹ���ʹ�ܱ�־.
  * @retval ����ADC_COMPARE_FLAG 0���� 1��λ.
  */
FlagStatus ADC_GetCompareFlagStatus(const ADC_Type* ADCx, uint16_t ADC_COMPARE_FLAG)
{
	FlagStatus bitstatus = RESET;

	/* Check the status of the specified ADC flag */
	if ((ADCx->CFR & ADC_COMPARE_FLAG) == ADC_COMPARE_FLAG)
	{
		/* ADC_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* ADC_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the ADC_FLAG status */
	return  bitstatus;
}

/**
  * @brief  �Ƿ�ض϶�Ӧͨ���������ֹ���.
  * @param  ADCx:����ADC����.
  * @param  Channel:ָ��Լ��ͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg ADC_CHANNEL_AD0:       
  *			@arg ADC_CHANNEL_AD1: 
  *			@arg ADC_CHANNEL_AD2:       
  *			@arg ADC_CHANNEL_AD3: 
  *			@arg ADC_CHANNEL_AD4:       
  *			@arg ADC_CHANNEL_AD5:
  *			@arg ADC_CHANNEL_AD6:       
  *			@arg ADC_CHANNEL_AD7: 
  *			@arg ADC_CHANNEL_AD8:       
  *			@arg ADC_CHANNEL_AD9: 
  *			@arg ADC_CHANNEL_AD10:      
  *			@arg ADC_CHANNEL_AD11:  
  *			@arg ADC_CHANNEL_AD12:        
  *			@arg ADC_CHANNEL_AD13:  
  *			@arg ADC_CHANNEL_AD14:       
  *			@arg ADC_CHANNEL_AD15:  
  *			@arg ADC_CHANNEL_AD16:        
  *			@arg ADC_CHANNEL_AD17: 
  *			@arg ADC_CHANNEL_AD18:       
  *			@arg ADC_CHANNEL_AD19: 
  *			@arg ADC_CHANNEL_AD20:       
  *			@arg ADC_CHANNEL_AD21: 
  *			@arg ADC_CHANNEL_TEMPSENSOR:       
  *			@arg ADC_CHANNEL_BANDGAP:
  *			@arg ADC_CHANNEL_AD22:       
  *			@arg ADC_CHANNEL_AD23: 
  *			@arg ADC_CHANNEL_VSS:       
  *			@arg ADC_CHANNEL_VREFH: 
  *			@arg ADC_CHANNEL_VREFL:      
  *			@arg ADC_CHANNEL_DISABLE:   	
  * @param  NewState: ADCxʹ��״̬
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ADCxʹ��
  *			@arg DISABLE: ADCxʧ��
  */
void ADC_DisableChannelDigFuc(ADC_Type* ADCx, uint8_t channelno, FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		ADCx->APCTL |= ((uint32_t)1u << channelno);
	}
	else
	{
		ADCx->APCTL &= ~((uint32_t)1u << channelno);
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


