 /**
  ******************************************************************************
  * @file     xl_uart.c
  * @author   Kirk
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about SIM firmware program
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
#include "xl_sim.h"

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup SIM SIM Module
  * @brief SIM Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @defgroup SIM_Private_Functions
  * @{
 */


/**
  * @brief  重新设置SIM寄存器状态.
  * @param  None
  * @retval None
  */
void SIM_DeInit(void)
{
	/* Deinitializes to default reset values */
	SIM->SOPT0 = 0x0000000C;
	SIM->SOPT1 = 0x00000000;
	SIM->PINSEL0 = 0x00000000;
	SIM->PINSEL1 = 0x00000000;
	SIM->SCGC = 0x00000800;
	SIM->CLKDIV = 0x00000000;
}


/**
  * @brief  读取器件PINID
  * @param  None
  * @retval PINID 返回Pin的ID
  *		这个参数可以取下面的值:
  * 		@arg PINID_8_PIN: 8引脚器件
  * 		@arg PINID_16_PIN: 16引脚器件
  * 		@arg PINID_20_PIN: 20引脚器件
  * 		@arg PINID_24_PIN: 24引脚器件
  * 		@arg PINID_32_PIN: 32引脚器件
  * 		@arg PINID_44_PIN: 44引脚器件
  * 		@arg PINID_48_PIN: 48引脚器件
  * 		@arg PINID_64_PIN: 64引脚器件
  * 		@arg PINID_80_PIN: 80引脚器件
  * 		@arg PINID_100_PIN: 100引脚器件
  * 		@arg PINID_RESERVE_PIN: 保留
  */
uint32_t SIM_ReadFPINID(void)
{
	return (SIM->SRSID & SIM_SRSID_PINID_MASK) >> SIM_SRSID_PINID_SHIFT;
}

/**
  * @brief  获取复位原因
  * @param  SIM: 复位的原因
  *		这个参数可以取下面的值:
  *			@arg SIM_ECCERR_RESET: ECC校验出错复位
  *			@arg SIM_LVD_RESET: 低电压跳变或上电复位
  *			@arg SIM_WDOG_RESET: 看门狗复位
  *			@arg SIM_PIN_RESET: 外部引脚复位
  *			@arg SIM_POR_RESET: 上电复位
  *			@arg SIM_SW_RESET: 软件复位
  * @retval 复位状态(TRUE or FALSE)
  */
FlagStatus SIM_GetRstCauses(uint32_t ResetCause)
{
	FlagStatus ret;
	
	if( ((SIM->SRSID >> ResetCause)&(uint32_t)0x01) != 0u)
	{
		ret = SET;
	}
	else
	{
		ret = RESET;
	}
	
	return ret;
}

/**
  * @brief  清除复位原因标志
  * @param  SIM: 清楚复位的原因
  *		这个参数可以取下面的值:
  *			@arg SIM_ECCERR_RESET: ECC校验出错复位
  * 		@arg SIM_LVD_RESET: 低电压跳变或上电复位
  * 		@arg SIM_WDOG_RESET: 看门狗复位
  *			@arg SIM_PIN_RESET: 外部引脚复位
  * 		@arg SIM_POR_RESET: 上电复位
  *			@arg SIM_SW_RESET: 软件复位
  * @retval None
  */
void SIM_ClrRstCauses(uint8_t ResetCause)
{
	SIM->SRSID |= ((uint32_t)0x01 << ResetCause);
}	

/**
  * @brief  NMI引脚使能
  * @param  State: NMI引脚使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: NMI引脚使能
  *			@arg DISABLE: NMI引脚失能
  * @retval None
  */
void SIM_SOPT0_NMIECmd(FunctionalState State)
{
	if(State == ENABLE)
	{
		SIM->SOPT0 |= SIM_SOPT0_NMIE_MASK;
	}
	else
	{
		SIM->SOPT0 &= ~SIM_SOPT0_NMIE_MASK;
	}
}

/**
  * @brief  RESET引脚使能
  * @param  State: RESET引脚使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: RESET引脚使能
  *			@arg DISABLE: RESET引脚失能
  * @retval None
  */
void SIM_SOPT0_RSTPECmd(FunctionalState State)
{
	if(State == ENABLE)
	{
		SIM->SOPT0 |= SIM_SOPT0_RSTPE_MASK;
	}
	else
	{
		SIM->SOPT0 &= ~SIM_SOPT0_RSTPE_MASK;
	}	
}

/**
  * @brief  SWD引脚使能
  * @param  State: SWD引脚使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: SWD引脚使能
  *			@arg DISABLE: SWD引脚失能
  * @retval None
  */
void SIM_SOPT0_SWDECmd(FunctionalState State)
{
	if(State == ENABLE)
	{
		SIM->SOPT0 |= SIM_SOPT0_SWDE_MASK;
	}
	else
	{
		SIM->SOPT0 &= ~SIM_SOPT0_SWDE_MASK;
	}		
}	

/**
  * @brief  ACMP触发FTM2触发源选择
  * @param  TriggerType: 触发源选择
  *		这个参数可以取下面的值:
  *			@arg ACMP0_OUTPUT_TRIGGER_FTM2: ACMP0输出触发FTM2
  *			@arg ACMP1_OUTPUT_TRIGGER_FTM2: ACMP1输出触发FTM2
  * @retval None
  */
void SIM_SOPT0_ACMPT_FTM2Config(uint8_t TriggerType)
{
	if(TriggerType == ACMP1_OUTPUT_TRIGGER_FTM2)
	{
		SIM->SOPT0 |= SIM_SOPT0_ACTRG_MASK;
	}
	else
	{
		SIM->SOPT0 &= ~SIM_SOPT0_ACTRG_MASK;
	}
}	

/**
  * @brief  UART0输入信号滤波器选择
  * @param  FilterType: 滤波器选择
  *		这个参数可以取下面的值:
  *			@arg UART0_RXD0_FILTER_NONE: 无滤波器
  *			@arg UART0_RXD0_FILTER_ACMP0: 滤波器ACMP0
  *			@arg UART0_RXD0_FILTER_ACMP1: 滤波器ACMP1
  * @retval None
  */
void SIM_SOPT0_UART0FilterConfig(uint32_t FilterType)
{
	SIM->SOPT0 &= ~SIM_SOPT0_RXDFE_MASK;
	SIM->SOPT0 |= (FilterType << SIM_SOPT0_RXDFE_SHIFT);
}

/**
  * @brief  FTM1通道1捕捉RTC溢出使能
  * @param  State: FTM1通道1捕捉RTC溢出使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能FTM1通道1捕捉RTC溢出
  *			@arg DISABLE: 失能FTM1通道1捕捉RTC溢出
  * @retval None
  */
void SIM_SOPT0_FTM1CH1C_RTCOutputCmd(FunctionalState State)
{
	if(State == ENABLE)
	{
		SIM->SOPT0 |= SIM_SOPT0_RTCC_MASK;
	}
	else
	{
		SIM->SOPT0 &= ~SIM_SOPT0_RTCC_MASK;
	}		
}	

/**
  * @brief  FTM1通道0捕捉ACMP0输出使能
  * @param  State: FTM1通道0捕捉ACMP0输出使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能FTM1通道0捕捉ACMP0输出
  *			@arg DISABLE: 失能FTM1通道0捕捉ACMP0输出
  * @retval None
  */
void SIM_SOPT0_FTM1CH0C_ACMP0OCmd(FunctionalState State)
{
	if(State == ENABLE)
	{
		SIM->SOPT0 |= SIM_SOPT0_ACIC_MASK;
	}
	else
	{
		SIM->SOPT0 &= ~SIM_SOPT0_ACIC_MASK;
	}		
}	

/**
  * @brief  FTM0通道1捕捉UART0输入使能
  * @param  State: FTM0通道1捕捉UART0输入使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能FTM0通道1捕捉UART0输入
  *			@arg DISABLE: 失能FTM0通道1捕捉UART0输入
  * @retval None
  */
void SIM_SOPT0_FTM0CH1C_UART0ICmd(FunctionalState State)
{
	if(State == ENABLE)
	{
		SIM->SOPT0 |= SIM_SOPT0_RXDCE_MASK;
	}
	else
	{
		SIM->SOPT0 &= ~SIM_SOPT0_RXDCE_MASK;
	}			
}

/**
  * @brief  生成FTM2模块的PWM同步触发使能
  * @param  State: 生成FTM2模块的PWM同步触发使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能生成FTM2模块的PWM同步触发
  *			@arg DISABLE: 失能生成FTM2模块的PWM同步触发
  * @retval None
  */
void SIM_SOPT0_FTM2S_PWMCmd(FunctionalState State)
{
	if(State == ENABLE)
	{
		SIM->SOPT0 |= SIM_SOPT0_FTMSYNC_MASK;
	}
	else
	{
		SIM->SOPT0 &= ~SIM_SOPT0_FTMSYNC_MASK;
	}		
}

/**
  * @brief  FTM0通道0调制UART0输出使能
  * @param  State: FTM0通道0调制UART0输出使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能FTM0通道0调制UART0输出
  *			@arg DISABLE: 失能FTM0通道0调制UART0输出
  * @retval None
  */
void SIM_SOPT0_FTM0M_UART0OutputCmd(FunctionalState State)
{
	if(State == ENABLE)
	{
		SIM->SOPT0 |= SIM_SOPT0_TXDME_MASK;
	}
	else
	{
		SIM->SOPT0 &= ~SIM_SOPT0_TXDME_MASK;
	}			
}

/**
  * @brief  总线时钟输出配置
  * @param  Divide: 总线时钟输出分频
  *		这个参数可以取下面的值:
  *			@arg BUSCLOCK_OUTPUT_DIVIDE_1: 总线时钟输出1分频
  *			@arg BUSCLOCK_OUTPUT_DIVIDE_2: 总线时钟输出2分频
  *			@arg BUSCLOCK_OUTPUT_DIVIDE_4: 总线时钟输出4分频
  *			@arg BUSCLOCK_OUTPUT_DIVIDE_8: 总线时钟输出8分频
  *			@arg BUSCLOCK_OUTPUT_DIVIDE_16: 总线时钟输出16分频
  *			@arg BUSCLOCK_OUTPUT_DIVIDE_32: 总线时钟输出32分频
  *			@arg BUSCLOCK_OUTPUT_DIVIDE_64: 总线时钟输出64分频
  *			@arg BUSCLOCK_OUTPUT_DIVIDE_128: 总线时钟输出128分频
  *  @retval None
  */
void SIM_SOPT0_BusClockDivide(uint8_t Divide)
{
	SIM->SOPT0 &= ~SIM_SOPT0_BUSREF_MASK;
	SIM->SOPT0 |= ((uint32_t)Divide << SIM_SOPT0_BUSREF_SHIFT);	
}

/**
  * @brief  总线时钟输出使能
  * @param  State: 总线时钟输出使能状态
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能总线时钟输出
  *			@arg DISABLE: 失能总线时钟输出
  * @retval None
  */
void SIM_SOPT0_BusClockOutputCmd(FunctionalState State)
{
	if(State == ENABLE)
	{
		SIM->SOPT0 |= SIM_SOPT0_CLKOE_MASK;
	}
	else
	{
		SIM->SOPT0 &= ~SIM_SOPT0_CLKOE_MASK;
	}		
}

/**
  * @brief  获取FTM2触发延迟状态
  * @param  None
  * @retval FTM2触发延迟状态(TRUE or FALSE)
  */
FlagStatus SIM_SOPT0_FTM2DelayTStatus(void)
{
	FlagStatus ret;
	
	if( ((SIM->SOPT0 & SIM_SOPT0_DLYACT_MASK) >> SIM_SOPT0_DLYACT_SHIFT) != 0u)
	{
		ret = SET;
	}
	else
	{
		ret = RESET;
	}
	
	return ret;
}

/**
  * @brief  配置FTM2触发ADC采样延迟时间
  * @param  Delay: FTM2触发ADC采样延迟时间(0~255)
  * @retval None
  */
void SIM_SOPT0_FTM2DelayTConfig(uint8_t Delay)
{
	SIM->SOPT0 &= ~SIM_SOPT0_DELAY_MASK;
	SIM->SOPT0 |= ((uint32_t)Delay << SIM_SOPT0_DELAY_SHIFT);	
}


/**
 * @brief  PWTIN2输入信号选择
 * @param  InputType: PWTIN2输入信号
 *		这个参数可以取下面的值:
 *			@arg PWTIN2_INPUT_ACMP1OUT: ACMP1的输出为PWTIN2的输入
 *			@arg PWTIN2_INPUT_ACMP0OUT: ACMP0的输出为PWTIN2的输入
 * @retval None
 */
void SIM_SOPT1_PWTIN2InputConfig(uint8_t InputType)
{
	if(InputType == PWTIN2_INPUT_ACMP0OUT)
	{
		SIM->SOPT1 |= SIM_SOPT1_ACPWTS_MASK;
	}
	else
	{
		SIM->SOPT1 &= ~SIM_SOPT1_ACPWTS_MASK;
	}
}

/**
 * @brief  PWTIN3输入信号选择
 * @param  None
 * @param  InputType: PWTIN3输入信号
 *		这个参数可以取下面的值:
 *			@arg PWTIN3_INPUT_UART0RX: UART0的输入为PWTIN3的输入
 *			@arg PWTIN3_INPUT_UART1RX: UART1的输入为PWTIN3的输入
 *			@arg PWTIN3_INPUT_UART2RX: UART2的输入为PWTIN3的输入
 * @retval None
 */
void SIM_SOPT1_PWTIN3InputConfig(uint8_t InputType)
{
	SIM->SOPT1 &= ~SIM_SOPT1_UARTPWTS_MASK;
	SIM->SOPT1 |= ((uint32_t)InputType << SIM_SOPT1_UARTPWTS_SHIFT);		
}

/**
 * @brief  ADC硬件触发源选择
 * @param  TriggerType: ADC硬件触发源
 *		这个参数可以取下面的值:
 *			@arg ADC_HT_RTCOVERFLOW: RTC溢出触发
 *			@arg ADC_HT_FTM0: FTM0触发
 *			@arg ADC_HT_FTM2UPDATE: FTM2初始触发
 *			@arg ADC_HT_FTM2CAPTURE: FTM2匹配触发
 *			@arg ADC_HT_PITCH0OVERFLOW: PIT通道0溢出触发
 *			@arg ADC_HT_PITCH1OVERFLOW: PIT通道1溢出触发
 *			@arg ADC_HT_ACMP0OUTPUT: ACMP0输出触发
 *			@arg ADC_HT_ACMP1OUTPUT: ACMP1输出触发
 *			@arg ADC_HT_FTM2CH1MAP:	 FTM2通道1匹配触发		  
 *			@arg ADC_HT_FTM2CH2MAP:	 FTM2通道2匹配触发		  
 *			@arg ADC_HT_FTM2CH3MAP:	 FTM2通道3匹配触发		  
 *			@arg ADC_HT_FTM2CH4MAP:	 FTM2通道4匹配触发		  
 *			@arg ADC_HT_FTM2CH5MAP:	 FTM2通道5匹配触发		  
 *			@arg ADC_HT_FTM1CH0MAP:	 FTM1通道0匹配触发		  
 *			@arg ADC_HT_FTM1CH1MAP:	 FTM1通道1匹配触发		  
 *			@arg ADC_HT_FTM0CH1MAP:	 FTM0通道1匹配触发		  
 * @retval None
 */
void SIM_SOPT1_ADCHardwareTConfig(uint8_t TriggerType)
{
	SIM->SOPT1 &= ~SIM_SOPT1_ADHWT_MASK;
	SIM->SOPT1 |= ((uint32_t)TriggerType << SIM_SOPT1_ADHWT_SHIFT);		
}

/**
 * @brief  UART0端口引脚选择 20190729XU
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg UART0_PS_PTB0_PTB1: UART0_RX和UART0_TX分别映射到PTB0和PTB1上
 *			@arg UART0_PS_PTA2_PTA3: UART0_RX和UART0_TX分别映射到PTA2和PTA3上
 *			@arg UART0_PS_PTC2_PTC3: UART0_RX和UART0_TX分别映射到PTC2和PTC3上
 * @retval None
 */
void SIM_PINSEL_UART0(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_UART0PS_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_UART0PS_SHIFT);			
}

/**
 * @brief  FTM0通道0端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM0CH0_PS_PTA0: FTM0_CH0通道映射到PTA0上
 *			@arg FTM0CH0_PS_PTB2: FTM0_CH0通道映射到PTB2上
 *			@arg FTM0CH0_PS_PTE5: FTM0_CH0通道映射到PTE5上
 *			@arg FTM0CH0_PS_PTF4: FTM0_CH0通道映射到PTF4上
 * @retval None
 */
void SIM_PINSEL_FTM0CH0(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_FTM0PS0_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_FTM0PS0_SHIFT);			
}

/**
 * @brief  FTM0通道1端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM0CH1_PS_PTA1: FTM0_CH1通道映射到PTA1上
 *			@arg FTM0CH1_PS_PTB3: FTM0_CH1通道映射到PTB3上
 *			@arg FTM0CH1_PS_PTE6: FTM0_CH1通道映射到PTE6上
 *			@arg FTM0CH1_PS_PTF5: FTM0_CH1通道映射到PTF5上
 * @retval None
 */
void SIM_PINSEL_FTM0CH1(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_FTM0PS1_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_FTM0PS1_SHIFT);			
}

/**
 * @brief  FTM1通道0端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM1CH0_PS_PTC4: FTM1_CH0通道映射到PTC4上
 *			@arg FTM1CH0_PS_PTH2: FTM1_CH0通道映射到PTH2上
 *			@arg FTM1CH0_PS_PTE5: FTM1_CH0通道映射到PTE5上
 * @retval None
 */
void SIM_PINSEL_FTM1CH0(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_FTM1PS0_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_FTM1PS0_SHIFT);			
}

/**
 * @brief  FTM1通道1端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM1CH1_PS_PTC5: FTM1_CH1通道映射到PTC5上
 *			@arg FTM1CH1_PS_PTE7: FTM1_CH1通道映射到PTE7上
 *			@arg FTM1CH1_PS_PTE6: FTM1_CH1通道映射到PTE6上
 * @retval None
 */
void SIM_PINSEL_FTM1CH1(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_FTM1PS1_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_FTM1PS1_SHIFT);			
}

/**
 * @brief  FTM_FLT2引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM_FLT2_PS_PTA7: FTM_FLT2通道映射到PTA7
 *			@arg FTM_FLT2_PS_PTI1: FTM_FLT2通道映射到PTI1
 *			@arg FTM_FLT2_PS_PTF7: FTM_FLT2通道映射到PTF7
 *			@arg FTM_FLT2_PS_PTF6: FTM_FLT2通道映射到PTF6
 * @retval None
 */
void SIM_PINSEL_FTMFLT2(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_FTMFLT2PS_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_FTMFLT2PS_SHIFT);			
}

/**
 * @brief  FTM_FLT1引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM_FLT1_PS_PTA6: FTM_FLT1通道映射到PTA7
 *			@arg FTM_FLT2_PS_PTI1: FTM_FLT1通道映射到PTI1
 *			@arg FTM_FLT2_PS_PTF7: FTM_FLT1通道映射到PTF7
 *			@arg FTM_FLT2_PS_PTF6: FTM_FLT1通道映射到PTF6
 * @retval None
 */
void SIM_PINSEL_FTMFLT1(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_FTMFLT1PS_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_FTMFLT1PS_SHIFT);			
}

/**
 * @brief  BUSOUT输出引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg BUSOUT_PS_PTH2: BUSOUT通道映射到PTH2
 *			@arg BUSOUT_PS_PTH6: BUSOUT通道映射到PTH6
 *			@arg BUSOUT_PS_PTB5: BUSOUT通道映射到PTB5
 * @retval None
 */
void SIM_PINSEL_BUSOUT(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_BUSOUTPS_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_BUSOUTPS_SHIFT);			
}

/**
 * @brief  TCLK2引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg TCLK2_PS_PTE7: TCLK2选择引脚PTE7
 *			@arg TCLK2_PS_PTH7: TCLK2选择引脚PTH7
 *			@arg TCLK2_PS_PTD5: TCLK2选择引脚PTD5
 * @retval None
 */
void SIM_PINSEL_TCLK2(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_TCLK2PS_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_TCLK2PS_SHIFT);			
}

/**
 * @brief  TCLK1引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg TCLK1_PS_PTE0: TCLK1选择引脚PTE0
 *			@arg TCLK1_PS_PTH7: TCLK1选择引脚PTH7
 *			@arg TCLK1_PS_PTD5: TCLK1选择引脚PTD5
 * @retval None
 */
void SIM_PINSEL_TCLK1(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_TCLK1PS_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_TCLK1PS_SHIFT);			
}

/**
 * @brief  TCLK0引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg TCLK0_PS_PTA5: TCLK0选择引脚PTA5
 *			@arg TCLK0_PS_PTH7: TCLK0选择引脚PTH7
 *			@arg TCLK0_PS_PTD5: TCLK0选择引脚PTD5
 * @retval None
 */
void SIM_PINSEL_TCLK0(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_TCLK0PS_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_TCLK0PS_SHIFT);			
}

/**
 * @brief  FTM0TCLK引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM0CLK_PS_TCLK0: 选择TCLK0用于FTM0模块
 *			@arg FTM0CLK_PS_TCLK1: 选择TCLK1用于FTM0模块
 *			@arg FTM0CLK_PS_TCLK2: 选择TCLK2用于FTM0模块
 * @retval None
 */
void SIM_PINSEL_FTM0TCLK(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_FTM0CLKPS_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_FTM0CLKPS_SHIFT);			
}

/**
 * @brief  FTM1TCLK引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM1CLK_PS_TCLK0: 选择TCLK0用于FTM1模块
 *			@arg FTM1CLK_PS_TCLK1: 选择TCLK1用于FTM1模块
 *			@arg FTM1CLK_PS_TCLK2: 选择TCLK2用于FTM1模块
 * @retval None
 */
void SIM_PINSEL_FTM1TCLK(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_FTM1CLKPS_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_FTM1CLKPS_SHIFT);	
}

/**
 * @brief  FTM2TCLK引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM2CLK_PS_TCLK0: 选择TCLK0用于FTM2模块
 *			@arg FTM2CLK_PS_TCLK1: 选择TCLK1用于FTM2模块
 *			@arg FTM2CLK_PS_TCLK2: 选择TCLK2用于FTM2模块
 * @retval None
 */
void SIM_PINSEL_FTM2TCLK(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_FTM2CLKPS_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_FTM2CLKPS_SHIFT);	
}

/**
 * @brief  PWTCLK引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg PWTCLK_PS_TCLK0: 选择TCLK0用于PWT模块
 *			@arg PWTCLK_PS_TCLK1: 选择TCLK1用于PWT模块
 *			@arg PWTCLK_PS_TCLK2: 选择TCLK2用于PWT模块
 * @retval None
 */
void SIM_PINSEL_PWTTCLK(uint8_t PinSelect)
{
	SIM->PINSEL0 &= ~SIM_PINSEL0_PWTCLKPS_MASK;
	SIM->PINSEL0 |= ((uint32_t)PinSelect << SIM_PINSEL0_PWTCLKPS_SHIFT);	
}

/**
 * @brief  FTM2通道0端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM2CH0_PS_PTC0: FTM2_CH0通道映射到PTC0上
 *			@arg FTM2CH0_PS_PTH0: FTM2_CH0通道映射到PTH0上
 *			@arg FTM2CH0_PS_PTF0: FTM2_CH0通道映射到PTF0上
 * @retval None
 */
void SIM_PINSEL_FTM2CH0(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS0_MASK;
	SIM->PINSEL1 |= (uint32_t)PinSelect;	
}

/**
 * @brief  FTM2通道1端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM2CH1_PS_PTC1: FTM2_CH1通道映射到PTC1上
 *			@arg FTM2CH1_PS_PTH1: FTM2_CH1通道映射到PTH1上
 *			@arg FTM2CH1_PS_PTF1: FTM2_CH1通道映射到PTF1上
 * @retval None
 */
void SIM_PINSEL_FTM2CH1(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS1_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_FTM2PS1_SHIFT);	
}

/**
 * @brief  FTM2通道2端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM2CH2_PS_PTC2: FTM2_CH2通道映射到PTC2上
 *			@arg FTM2CH2_PS_PTD0: FTM2_CH2通道映射到PTD0上
 *			@arg FTM2CH2_PS_PTG4: FTM2_CH2通道映射到PTG4上
 * @retval None
 */
void SIM_PINSEL_FTM2CH2(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS2_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_FTM2PS2_SHIFT);	
}

/**
 * @brief  FTM2通道3端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM2CH3_PS_PTC3: FTM2_CH3通道映射到PTC3上
 *			@arg FTM2CH3_PS_PTD1: FTM2_CH3通道映射到PTD1上
 *			@arg FTM2CH3_PS_PTG5: FTM2_CH3通道映射到PTG5上
 * @retval None
 */
void SIM_PINSEL_FTM2CH3(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS3_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_FTM2PS3_SHIFT);	
}

/**
 * @brief  FTM2通道4端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM2CH4_PS_PTB4: FTM2_CH4通道映射到PTB4上
 *			@arg FTM2CH4_PS_PTG6: FTM2_CH4通道映射到PTG6上
 * @retval None
 */
void SIM_PINSEL_FTM2CH4(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS4_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_FTM2PS4_SHIFT);	
}

/**
 * @brief  FTM2通道5端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM2CH5_PS_PTB5: FTM2_CH5通道映射到PTB5上
 *			@arg FTM2CH5_PS_PTG7: FTM2_CH5通道映射到PTG7上
 * @retval None
 */
void SIM_PINSEL_FTM2CH5(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS5_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_FTM2PS5_SHIFT);	
}

/**
 * @brief  I2C1端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg I2C1_PS_PTE1_PTE0: I2C1_SCL和I2C1_SDA分别映射到PTE1和PTE0上
 *			@arg I2C1_PS_PTH4_PTH3: I2C1_SCL和I2C1_SDA分别映射到PTH4和PTH3上
 * @retval None
 */
void SIM_PINSEL_I2C1(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_I2C1PS_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_I2C1PS_SHIFT);		
}

/**
 * @brief  SPI1端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg SPI1_PS_PTD0_PTD1_PTD2_PTD3: SPI0_SCK,SPI0_MOSI,SPI0_MISO和SPI0_CS分别映射到PTD0,PTD1,PTD2和PTD3上
 *			@arg SPI1_PS_PTG4_PTG5_PTG6_PTG7: SPI0_SCK,SPI0_MOSI,SPI0_MISO和SPI0_CS分别映射到PTG4,PTG5,PTG6和PTG7上
 * @retval None
 */
void SIM_PINSEL_SPI1(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_SPI1PS_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_SPI1PS_SHIFT);		
}

/**
 * @brief  UART1端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg UART1_PS_PTC7_PTC6: UART0_RX和UART0_TX分别映射到PTC7和PTC6上
 *			@arg UART1_PS_PTF3_PTF2: UART0_RX和UART0_TX分别映射到PTF3和PTF2上
 * @retval None
 */
void SIM_PINSEL_UART1(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_UART1PS_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_UART1PS_SHIFT);		
}

/**
 * @brief  UART2端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg UART2_PS_PTD7_PTD6: UART0_RX和UART0_TX分别映射到PTD7和PTD6上
 *			@arg UART2_PS_PTI1_PTI0: UART0_RX和UART0_TX分别映射到PTI1和PTI0上
 * @retval None
 */
void SIM_PINSEL_UART2(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_UART2PS_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_UART2PS_SHIFT);		
}

/**
 * @brief  PWTIN0端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg PWTIN0_PS_PTD5: PWTIN0引脚映射到PTD5上
 *			@arg PWTIN0_PS_PTE2: PWTIN0引脚映射到PTE2上
 * @retval None
 */
void SIM_PINSEL_PWTIN0(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_PWTIN0PS_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_PWTIN0PS_SHIFT);		
}

/**
 * @brief  PWTIN1端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg PWTIN1_PS_PTB0: PWTIN0引脚映射到PTB0上
 *			@arg PWTIN1_PS_PTH7: PWTIN0引脚映射到PTH7上
 * @retval None
 */
void SIM_PINSEL_PWTIN1(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_PWTIN1PS_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_PWTIN1PS_SHIFT);		
}

/**
 * @brief  SPI0端口引脚选择 20190729XU
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg SPI0_PS_PTB2_PTB3_PTB4_PTB5: SPI0_SCK,SPI0_MOSI,SPI0_MISO和SPI0_CS分别映射到PTB2,PTB3,PTB4和PTB5上
 *			@arg SPI0_PS_PTE0_PTE1_PTE2_PTE3: SPI0_SCK,SPI0_MOSI,SPI0_MISO和SPI0_CS分别映射到PTE0,PTE1,PTE2和PTE3上
 * @retval None
 */
void SIM_PINSEL_SPI0(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_SPI0PS_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_SPI0PS_SHIFT);		
}

/**
 * @brief  EWM端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg EWM_PS_PTA3_PTA2: EWM_IN和EWM_RESET分别映射到PTA3和PTA2上
 *			@arg EWM_PS_PTC4_PTA4: EWM_IN和EWM_RESET分别映射到PTC4和PTA4上
 *			@arg EWM_PS_PTE7_PTH2: EWM_IN和EWM_RESET分别映射到PTE7和PTH2上
 * @retval None
 */
void SIM_PINSEL_EWM(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_EWMPS_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_EWMPS_SHIFT);		
}

/**
 * @brief  IRQ端口引脚选择 20190729XU
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg IRQ_PS_GROUP1: IRQ映射到第一组PIN脚上
 *			@arg IRQ_PS_GROUP2: IRQ映射到第二组PIN脚上
 *			@arg IRQ_PS_GROUP3: IRQ映射到第三组PIN脚上
 *			@arg IRQ_PS_GROUP4: IRQ映射到第四组PIN脚上
 *			@arg IRQ_PS_GROUP5: IRQ映射到第五组PIN脚上
 * @retval None
 */
void SIM_PINSEL_IRQ(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_IRQPS_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_IRQPS_SHIFT);		
}

/**
 * @brief  ACMP1输出PS端口引脚选择 20190729XU
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg ACMP1_PS_PTB5: ACMP1输出映射到PTB5上
 *			@arg ACMP1_PS_PTI1: ACMP1输出映射到PTI1上
 * @retval None
 */
void SIM_PINSEL_ACMP(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_ACMP1PS_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_ACMP1PS_SHIFT);		
}

/**
 * @brief  RTC输出PS端口引脚选择 20190729XU
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg RTCO_PS_PTC4: RTC输出映射到PTC4上
 *			@arg RTCO_PS_PTC5: RTC输出映射到PTC5上
 * @retval None
 */
void SIM_PINSEL_RTC(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_RTCPS_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_RTCPS_SHIFT);		
}

/**
 * @brief  I2C0端口引脚选择 20190729XU
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg I2C0_PS_PTA3_PTA2: I2C0_SCL和I2C0_SDA分别映射到PTA3和PTA2上
 *			@arg I2C0_PS_PTB7_PTB6: I2C0_SCL和I2C0_SDA分别映射到PTB7和PTB6上
 * @retval None
 */
void SIM_PINSEL_I2C0(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_I2C0PS_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_I2C0PS_SHIFT);		
}

/**
 * @brief  FTM0通道2端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM0CH2_PS_PTH7: FTM0_CH2通道映射到PTH7上
 *			@arg FTM0CH2_PS_PTD5: FTM0_CH2通道映射到PTD5上
 * @retval None
 */
void SIM_PINSEL_FTM0CH2(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_FTM0PS2_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_FTM0PS2_SHIFT);		
}

/**
 * @brief  FTM0通道3端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM0CH3_PS_PTE4: FTM0_CH3通道映射到PTE4上
 *			@arg FTM0CH3_PS_PTD4: FTM0_CH3通道映射到PTD4上
 * @retval None
 */
void SIM_PINSEL_FTM0CH3(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_FTM0PS3_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_FTM0PS3_SHIFT);		
}

/**
 * @brief  FTM1通道2端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM1CH2_PS_PTH1: FTM1_CH2通道映射到PTH1上
 *			@arg FTM1CH2_PS_PTB4: FTM1_CH2通道映射到PTB4上
 * @retval None
 */
void SIM_PINSEL_FTM1CH2(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_FTM1PS2_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_FTM1PS2_SHIFT);		
}

/**
 * @brief  FTM1通道3端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM1CH3_PS_PTH0: FTM1_CH3通道映射到PTE4上
 *			@arg FTM1CH3_PS_PTE3: FTM1_CH3通道映射到PTD4上
 * @retval None
 */
void SIM_PINSEL_FTM1CH3(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_FTM1PS3_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_FTM1PS3_SHIFT);		
}

/**
 * @brief  FTM2通道6端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM2CH6_PS_PTF3: FTM2_CH6通道映射到PTF3上
 *			@arg FTM2CH6_PS_PTD3: FTM2_CH6通道映射到PTD3上
 * @retval None
 */
void SIM_PINSEL_FTM2CH6(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS6_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_FTM2PS6_SHIFT);		
}

/**
 * @brief  FTM2通道7端口引脚选择
 * @param  PinSelect: 引脚选择
 *		这个参数可以取下面的值:
 *			@arg FTM2CH7_PS_PTF2: FTM2_CH7通道映射到PTF2上
 *			@arg FTM2CH7_PS_PTD2: FTM2_CH7通道映射到PTD2上
 * @retval None
 */
void SIM_PINSEL_FTM2CH7(uint8_t PinSelect)
{
	SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS7_MASK;
	SIM->PINSEL1 |= ((uint32_t)PinSelect << SIM_PINSEL1_FTM2PS7_SHIFT);		
}

/**
 * @brief  系统时钟选通
 * @param  SCGC_Type: 指定外设时钟使能状态
 *		这个参数可以为以下值:
 *			@arg SIM_SCGC_RTC: RTC时钟选通
 *			@arg SIM_SCGC_PIT: PIT时钟选通
 *			@arg SIM_SCGC_EWM: EWM时钟选通
 *			@arg SIM_SCGC_PWT: PWT时钟选通
 *			@arg SIM_SCGC_FTM0: FTM0时钟选通
 *			@arg SIM_SCGC_FTM1: FTM1时钟选通
 *			@arg SIM_SCGC_FTM2: FTM2时钟选通
 *			@arg SIM_SCGC_CLMA: FTM2时钟选通
 *			@arg SIM_SCGC_CLMB: FTM2时钟选通
 *			@arg SIM_SCGC_CRC: CRC时钟选通
 *			@arg SIM_SCGC_WDG: WDG时钟选通
 *			@arg SIM_SCGC_MCAN: MCAN时钟选通
 *			@arg SIM_SCGC_I2C0: I2C0时钟选通
 *			@arg SIM_SCGC_I2C1: I2C1时钟选通
 *			@arg SIM_SCGC_SPI0: SPI0时钟选通
 *			@arg SIM_SCGC_SPI1: SPI1时钟选通
 *			@arg SIM_SCGC_UART0: UART0时钟选通
 *			@arg SIM_SCGC_UART1: UART1时钟选通
 *			@arg SIM_SCGC_UART2: UART2时钟选通
 *			@arg SIM_SCGC_KBI0: KBI0时钟选通
 *			@arg SIM_SCGC_KBI1: KBI1时钟选通
 *			@arg SIM_SCGC_IRQ: IRQ时钟选通
 *			@arg SIM_SCGC_DMA: DMA时钟选通
 *			@arg SIM_SCGC_ADC: ADC时钟选通
 *			@arg SIM_SCGC_ACMP0: ACMP0时钟选通
 *			@arg SIM_SCGC_ACMP1: ACMP1时钟选通
 * @param  State: 选定指定的外设
 *		这个参数可以取下面的值:
 *			@arg ENABLE: 使能相应模块
 *			@arg DISABLE: 关闭相应模块
 * @retval None
 */
void SIM_SCGC_Cmd(uint32_t SCGC_Type, FunctionalState State)
{
	if(State == ENABLE)
	{
		SIM->SCGC |= SCGC_Type;	/*
		* (1-166)12.2.6 系统时钟选通控制寄存器(SCGC)
		* SIM->SCGC=13056=0x00003300u; SCGC_Type=0x00000800u=2048
		* SIM->SCGC=0x00003B00u=0011 1011 0000 0000*/
	}
	else
	{
		SIM->SCGC &= ~SCGC_Type;	/*
		* SIM->SCGC=13056=0x00003300u; SCGC_Type=0x00000800u=2048
		* ~(0x0000 0800u)=FFFF F7FF
		* SIM->SCGC=0x00003300u=0011 0011 0000 0000*/
	}		
}

/**
 * @brief  系统时钟选通1
 * @param  SCGC_Type: 指定外设时钟使能状态
 *		这个参数可以为以下值:
 *			@arg SIM_SCGC1_FTM0F: 	FTM0选用ICSFFCLK时钟使能                  
 *			@arg SIM_SCGC1_FTM1F: 	FTM1选用ICSFFCLK时钟使能                                 
 *			@arg SIM_SCGC1_FTM2F: 	FTM2选用ICSFFCLK时钟使能                                    
 *			@arg SIM_SCGC1_RTCEC: 	RTC选用OSCERCLK时钟使能                                	
 *			@arg SIM_SCGC1_ADCALTC: ADC选用ALTCLK时钟使能                          
 *			@arg SIM_SCGC1_FTM0T:  	FTM0选用TIMERCLK时钟使能                    
 *			@arg SIM_SCGC1_FTM1T:  	FTM1选用TIMERCLK时钟使能                       
 *			@arg SIM_SCGC1_FTM2T:  	FTM2选用TIMERCLK时钟使能     
 *			@arg SIM_SCGC1_RTCLPOC: RTC选用LPOCLK时钟使能         
 * @param  State: 选定指定的外设
 *		这个参数可以取下面的值:
 *			@arg ENABLE: 使能相应模块
 *			@arg DISABLE: 关闭相应模块
 * @retval None
 */
void SIM_SCGC1_Cmd(uint32_t SCGC1_Type, FunctionalState State)
{
	if(State == ENABLE)
	{
		SIM->SCGC1 |= SCGC1_Type;
	}
	else
	{
		SIM->SCGC1 &= ~SCGC1_Type;
	}		
}

/**
 * @brief  获取通用唯一标识符低位
 * @param  None
 * @retval 通用唯一标识符低位
 */
uint32_t SIM_GetUUIDL(void)
{
	return SIM->UUIDL;
}

/**
 * @brief  获取通用唯一标识符中低位
 * @param  None
 * @retval 通用唯一标识符低位
 */
uint32_t SIM_GetUUIDML(void)
{
	return SIM->UUIDML;
}

/**
 * @brief  获取通用唯一标识符中高位
 * @param  None
 * @retval 通用唯一标识符低位
 */
uint32_t SIM_GetUUIDMH(void)
{
	return SIM->UUIDMH;
}

/**
 * @brief  获取芯片SRAM容量大小
 * @param  None
 * @retval SRAM容量大小(SRAM_SIZE_16KB or SRAM_SIZE_24KB)
 */
uint8_t SIM_GetSRAMSize(void)
{
	return (uint8_t)(SIM->UUIDMH & SIM_UUIDMH_SS_MASK);
}

/**
 * @brief  获取芯片FLASH容量大小
 * @param  None
 * @retval FLASH容量大小(FLASH_SIZE_256KB or FLASH_SIZE_128KB)
 */
uint8_t SIM_GetFLASHSize(void)
{
	return (uint8_t)((SIM->UUIDMH & SIM_UUIDMH_FS_MASK) >> SIM_UUIDMH_FS_SHIFT);
}

/**
 * @brief  获取芯片版本
 * @param  None
 * @retval 芯片版本
 */
uint8_t SIM_GetVer(void)
{
	return (uint8_t)((SIM->UUIDMH & SIM_UUIDMH_VER_MASK) >> SIM_UUIDMH_VER_SHIFT);
}

/**
 * @brief  获取芯片型号
 * @param  None
 * @retval 芯片型号
 */
uint8_t SIM_GetDevID(void)
{
	return (uint8_t)((SIM->UUIDMH & SIM_UUIDMH_DEVID_MASK) >> SIM_UUIDMH_DEVID_SHIFT);
}

/**
 * @brief  设置内核时钟的分频值
 * @param  divide: 内核时钟分频值(1-256)(ICSOUTCLK除以divide)
 * @retval None
 */
void SIM_CLKDIV_OUTDIV1(uint32_t divide)
{
	SIM->CLKDIV &= ~SIM_CLKDIV_OUTDIV1_MASK;
	SIM->CLKDIV |= divide - (uint32_t)1;		
}

/**
 * @brief  设置AHB总线和FLASH时钟的分频值
 * @param  divide: AHB总线和FLASH时钟的分频值(OUTDIV1除以divide)  (1-256)
 * @retval None
 * NOTE:
 * 	高性能总线(Advanced High-performance Bus, AHB)
 */
void SIM_CLKDIV_OUTDIV2(uint32_t divide)
{
	SIM->CLKDIV &= ~SIM_CLKDIV_OUTDIV2_MASK;
	SIM->CLKDIV |= (divide - (uint32_t)1) << SIM_CLKDIV_OUTDIV2_SHIFT;		
}

/**
 * @brief  设置APB总线时钟的分频值
 * @param  divide: APB总线时钟的分频值(OUTDIV2除以divide)
 * @retval None
 */
void SIM_CLKDIV_OUTDIV3(uint32_t divide)
{
	SIM->CLKDIV &= ~SIM_CLKDIV_OUTDIV3_MASK;
	SIM->CLKDIV |= (divide - (uint32_t)1) << SIM_CLKDIV_OUTDIV3_SHIFT;		
}

/**
 * @brief  设置定时器(FTM0,FTM1,FTM2,PWT)的分频值
 * @param  divide: APB总线时钟的分频值(ICSOUTCLK除以divide)
 * @retval None
 */
void SIM_CLKDIV_OUTDIV4(uint32_t divide)
{
	SIM->CLKDIV &= ~SIM_CLKDIV_OUTDIV4_MASK;
	SIM->CLKDIV |= (divide - (uint32_t)1) << SIM_CLKDIV_OUTDIV4_SHIFT;		
}

/**
 * @brief  得到OUTDIV1的分频值
 * @param  None
 * @retval 分频值
 */
uint8_t SIM_GetOUTDIV1(void)
{
	return (uint8_t)(SIM->CLKDIV); 
}

/**
 * @brief  得到OUTDIV2的分频值
 * @param  None
 * @retval 分频值
 */
uint8_t SIM_GetOUTDIV2(void)
{
	return (uint8_t)(SIM->CLKDIV >> 8); 
}

/**
 * @brief  得到OUTDIV3的分频值
 * @param  None
 * @retval 分频值
 */
uint8_t SIM_GetOUTDIV3(void)
{
	return (uint8_t)(SIM->CLKDIV >> 16); 
}

/**
 * @brief  得到OUTDIV4的分频值
 * @param  None
 * @retval 分频值
 */
uint8_t SIM_GetOUTDIV4(void)
{
	return (uint8_t)(SIM->CLKDIV >> 24); 
}

/**
 * @brief  系统功耗控制
 * @param  LP_Type: 选择关断电源的模块
 *		这个参数可以取下面的值:
 *			@arg SIM_LP_USER_FLASH: 	用户模式是关断FLASH电源         
 *			@arg SIM_LP_USER_FLASH:   STOP模式是关断FLASH电源             
 *			@arg SIM_LP_USER_RAM1: 	  用户模式是关断RAM1电源                          
 *			@arg SIM_LP_USER_RAM2: 	  用户模式是关断RAM2电源                                	
 *			@arg SIM_LP_USER_RAM3:    用户模式是关断RAM3电源                          
 *			@arg SIM_LP_STOP_RAM1:  	STOP模式是关断RAM1电源           
 *			@arg SIM_LP_STOP_RAM2:  	STOP模式是关断RAM2电源                         
 *			@arg SIM_LP_STOP_RAM3:  	STOP模式是关断RAM3电源                  	
 * @retval None
 */
void SIM_LP_SetLowpowerCmd(uint32_t LP_Type)
{
	SIM->LP = (0x55AA0000u | LP_Type);
}

/**
 * @brief  获取FLASH上电标志
 * @param  None
 * @retval FLASH上电标志
 */
FlagStatus SIM_LP_FLASHPowerONStatus(void)
{
	FlagStatus ret;
	
	if( ((SIM->LP & SIM_LP_FLASHPON_MASK)>>SIM_LP_FLASHPON_SHIFT) != 0u)
	{
		ret= SET;
	}
	else
	{
		ret = RESET;
	}
	
	return ret;
}

/**
 * @brief  获取SRAM上电标志
 * @param  None
 * @retval SRAM上电标志
 */
FlagStatus SIM_LP_SRAMPowerONStatus(void)
{
	FlagStatus ret;
	
	if( ((SIM->LP >> SIM_LP_SRAMPON_SHIFT)&(uint32_t)0x01) != 0u)
	{
		ret= SET;
	}
	else
	{
		ret = RESET;
	}
	
	return ret;
}

/**
 * @brief  设置系统稳定等待时间
 * @param  Clkwait: ICSOUTCLK的稳定计数周期
 * @retval None
 */
void SIM_WAIT_CLKWAITConfig(uint16_t Clkwait)
{
	SIM->WAIT &= ~SIM_WAIT_CLKWAIT_MASK;
	SIM->WAIT |= (uint32_t)Clkwait;		
}

/**
 * @brief  系统时钟的1us分频系数
 * @param  Div1us: 系统时钟的1us分频系数
 * @retval None
 */
void SIM_WAIT_DIV1USConfig(uint16_t Div1us)
{
	SIM->WAIT &= ~SIM_WAIT_DIV1US_MASK;
	SIM->WAIT |= ((uint32_t)Div1us << SIM_WAIT_DIV1US_SHIFT);		
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
#endif



