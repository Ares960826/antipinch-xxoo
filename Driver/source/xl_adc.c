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
  * @brief  ADCx外设寄存器恢复默认值
  * @param  ADCx:设置ADC外设.
  * @retval None
  */
void ADC_DeInit(ADC_Type* ADCx)
{
	/* Deinitializes to default reset values */	
	ADCx->CR = 0x00000000;

	ADC_SetChannel(ADCx,ADC_CHANNEL_DISABLE);
}

/**
  * @brief  ADC初始化
  * @param  ADCx:设置ADC外设
  * @param  ADC_InitStruct:ADC初始化配置结构体
  * @retval None
  */
void ADC_Init(ADC_Type* ADCx, const ADC_InitTypeDef* ADC_InitStruct)
{
	/*---------------------------- ADCx CR Configuration -----------------*/

	/* Clear MODE、REFSEL、CLKSEL、DIV 、LPE and LSTE bits */
	ADCx->CR &= ~(ADC_CR_MODE_MASK | ADC_CR_REFSEL_MASK | ADC_CR_CLKSEL_MASK | \
							ADC_CR_ADIV_MASK | ADC_CR_LSTE_MASK | ADC_CR_LPE_MASK);
	/* Configures MODE、REFSEL、CLKSEL、DIV 、LPE and LSTE bits */	
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
  * @brief  ADC FIFO配置寄存器
  * @param  ADCx:设置ADC外设.
  * @param  ADC_FIFOStruct:ADC FIFO配置参数结构体
  * @retval None
  */
void ADC_FIFOConfig(ADC_Type* ADCx, const ADC_FIFOTypeDef* ADC_FIFOStruct)
{
	/*---------------------------- ADCx CR Configuration -----------------*/

	/* Clear FSE、FDEP bits */
	ADCx->CR &= ~(ADC_CR_FDEP_MASK | ADC_CR_FSE_MASK);
	/* Configures FSE、FDEP bits */	
	ADCx->CR |= ((ADC_FIFOStruct->ADC_FIFOLevel << ADC_CR_FDEP_SHIFT) & ADC_CR_FDEP_MASK);
	
	if(ADC_FIFOStruct->ADC_ChannelScan == ENABLE)
	{
		ADCx->CR |= ADC_CR_FSE_MASK;
	}
}

/**
  * @brief  ADC Compare功能配置函数
  * @param  ADCx:设置ADC外设.
  * @param  ADC_CompareStruct:ADC Compare配置参数结构体
  * @retval None
  */
void ADC_CompareConfig(ADC_Type* ADCx, const ADC_CompareTypeDef* ADC_CompareStruct)
{
	/*---------------------------- ADCx CR Configuration -----------------*/

	/* Clear CFE、CFRE、CFGRE and CFSEL bits */
	ADCx->CR &= ~(ADC_CR_CFRE_MASK | ADC_CR_CFGRE_MASK | ADC_CR_CFE_MASK | ADC_CR_CFSEL_MASK | ADC_CR_COSBEN_MASK);
	/* Configures CFE、CFRE、CFGRE and CFSEL bits */	
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
  * @brief  ADC使能函数
  * @param  ADCx:设置ADC外设.
  * @param  State: ADCx使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: ADCx使能
  *			@arg DISABLE: ADCx失能
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
  * @brief  ADC硬件触发使能函数
  * @param  ADCx:设置ADC外设.
  * @param  State: ADCx使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: ADCx使能
  *			@arg DISABLE: ADCx失能
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
  * @brief  ADC触发模式选择
  * @param  ADCx:设置ADC外设.
  * @param  ADC_Triggermode: 软件或硬件触发.
  *		这个参数可以取下面的值:
  *			@arg ADC_SOFTWARE_TRIGGER: 软件触发
  *			@arg ADC_HARDWARE_TRIGGER: 硬件触发
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
  * @brief  ADC异步时钟选择位
  * @param  ADCx:设置ADC外设.
  * @param  ADC_ADACKmode: 正常ADACK值或者1.5倍正常ADACK值.
  *		这个参数可以取下面的值:
  *			@arg ADC_ADACK_NORMAL: 正常ADACK
  *			@arg ADC_ADACK_TIMES1P5: 1.5倍的ADACK
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
  * @brief  ADC转换模式选择，单次转换还是异步转换
  * @param  ADCx:设置ADC外设.
  * @param  ADC_ConventionMode: 一次或者连续.
  *		这个参数可以取下面的值:
  *			@arg ADC_CONVENTION_ONCE:       单次转换
  *			@arg ADC_CONVENTION_CONTINUOUS: 连续转换
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
  * @brief  ADC通道设置
  * @param  ADCx:设置ADC外设.
  * @param  Channel:指向约定通道.
  *		这个参数可以取下面的值:
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
  * @brief  是否启用ADC外设中断.
  * @param  ADCx:设置ADC外设.
  * @param  State: ADCx使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: ADCx使能
  *			@arg DISABLE: ADCx失能
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
  * @brief  是否启用ADC外设DMA发射状态.
  * @param  ADCx:设置ADC外设.
  * @param  State: ADCx使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: ADCx使能
  *			@arg DISABLE: ADCx失能
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
  * @brief  是否启用ADC外设DMA接收状态.
  * @param  ADCx:设置ADC外设.
  * @param  State: ADCx使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: ADCx使能
  *			@arg DISABLE: ADCx失能
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
  * @brief  返回最后的ADCx结果数据.
  * @param  ADCx:设置ADC外设.
  * @param  NewState:选择是否状态.
  * @retval 返回数据结果.
  */
uint16_t ADC_GetConversionValue(const ADC_Type* ADCx)
{
  /* Return the selected ADC conversion value */
  return (uint16_t)(ADCx->RDR & ADC_RDR_DATA_MASK);
}

/**
  * @brief  返回最后的ADCx结果数据.
  * @param  ADCx:设置ADC外设.
  * @param  NewState:选择是否状态.
  * @retval 返回FIFO中的数据值.
  */
uint16_t ADC_GetFIFOValueCounter(const ADC_Type* ADCx)
{
	/* Return FIFO conversion value number*/
	return (uint16_t) (ADCx->SR & ADC_SR_RFCNT_MASK);
}

/**
  * @brief  检测ADC标志是否设置.
  * @param  ADCx:设置ADC外设.
  * @param  ADC_FLAG: 检测特定标志.
  *		这个参数可以取下面的值:
  *     @arg ADC_FLAG_DATAFIFO_FULL: FIFO数据满标志.
  *     @arg ADC_FLAG_DATAFIFO_EMPTY:FIFO数据空标志.
  *     @arg ADC_FLAG_CONV_FINISH: 结束标志.
  *     @arg ADC_FLAG_CONV_BUSY: 繁忙标志.
  *     @arg ADC_FLAG_ChannelFIFO_FULL: Channel FIFO数据满标志.
  *     @arg ADC_FLAG_ChannelFIFO_EMPTY: Channel FIFO数据空标志.
  * @retval 返回ADC_FLAG 0重启 1置数.
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
  * @brief  检测ADC标志是否设置.
  * @param  ADCx:设置ADC外设.
  * @param  ADC_COMPARE_FLAG: 比较功能状态.
  *		这个参数可以取下面的值:
  *     @arg ADC_CHANNEL0_COMPARE_EXCEPTION: 通道0比较结果异常标志.
  *     @arg ADC_CHANNEL1_COMPARE_EXCEPTION: 通道1比较结果异常标志.
  *     @arg ADC_CHANNEL2_COMPARE_EXCEPTION: 通道2比较结果异常标志.
  *     @arg ADC_CHANNEL3_COMPARE_EXCEPTION: 通道3比较结果异常标志.
  *     @arg ADC_CHANNEL4_COMPARE_EXCEPTION: 通道4比较结果异常标志.
  *     @arg ADC_CHANNEL5_COMPARE_EXCEPTION: 通道5比较结果异常标志.
  *     @arg ADC_CHANNEL6_COMPARE_EXCEPTION: 通道6比较结果异常标志.
  *     @arg ADC_CHANNEL7_COMPARE_EXCEPTION: 通道7比较结果异常标志.
  *     @arg ADC_CHANNELALL_COMPARE_EXCEPTION: 所有通道比较结果异常标志.
  *     @arg ADC_COMPARE_CFSEL_FLAG: 输出结果选择方式标志.
  *     @arg ADC_COMPARE_CFGRE_FLAG: 大于选择标志.
  *     @arg ADC_COMPARE_CFRE_FLAG: 比较方式选择标志.
  *     @arg ADC_COMPARE_CFE_FLAG: 自动比较功能使能标志.
  * @retval 返回ADC_COMPARE_FLAG 0清零 1置位.
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
  * @brief  是否关断对应通道引脚数字功能.
  * @param  ADCx:设置ADC外设.
  * @param  Channel:指向约定通道.
  *		这个参数可以取下面的值:
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
  * @param  NewState: ADCx使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: ADCx使能
  *			@arg DISABLE: ADCx失能
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


