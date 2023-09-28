/**
  ******************************************************************************
  * @file     xl_ftm.c
  * @author   Kirk ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about FTM firmware program 
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
#include "xl_ftm.h"

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup FTM FTM Module 
  * @brief FTM Driver Modules Library
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup FTM_Private_Functions
  * @brief 
  * @{
  */ 	

/**
  * @brief  写保护功能使能.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @retval None
  */
void FTM_WriteProtectEnable(FTM_Type* FTMx)
{
	FTMx->FMS |= FTM_FMS_WPEN_MASK;	
}

/**
  * @brief  写保护功能禁用.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @retval None
  */
void FTM_WriteProtectDisable(FTM_Type* FTMx)
{
	FTMx->MODE |= FTM_MODE_WPDIS_MASK;
}

/**
  * @brief  配置FTMx外设寄存器为默认值
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @retval None.
  */
void FTM_DeInit(FTM_Type* FTMx)
{
	/* disable channel  */
	FTMx->CONTROLS[0].CnSC = 0;
	FTMx->CONTROLS[0].CnV = 0;
	FTMx->CONTROLS[1].CnSC = 0;
	FTMx->CONTROLS[1].CnV = 0;
	FTMx->CONTROLS[2].CnSC = 0;
	FTMx->CONTROLS[2].CnV = 0;
	FTMx->CONTROLS[3].CnSC = 0;
	FTMx->CONTROLS[3].CnV = 0;
	
	if(FTMx == FTM2)
	{
		FTMx->CONTROLS[4].CnSC = 0;
		FTMx->CONTROLS[4].CnV = 0;
		FTMx->CONTROLS[5].CnSC = 0;
		FTMx->CONTROLS[5].CnV = 0;
		FTMx->CONTROLS[6].CnSC = 0;
		FTMx->CONTROLS[6].CnV = 0;
		FTMx->CONTROLS[7].CnSC = 0;
		FTMx->CONTROLS[7].CnV = 0;
	}
	
  /* disable the colck  */	
	FTMx->SC = 0;
	FTMx->CNT=0;
	FTMx->MOD = 0;
	FTMx->CNTIN=0;
	FTMx->MODE = 0x4; 
	FTMx->COMBINE = 0;      
	FTMx->CNTIN = 0;      
	FTMx->SYNC = 0;      
	FTMx->OUTINIT = 0;      
	FTMx->OUTMASK = 0;      
	FTMx->DEADTIME = 0;      
	FTMx->EXTTRIG = 0;      
	FTMx->POL = 0;      
	FTMx->FMS = 0;      
	FTMx->FILTER = 0;      
	FTMx->FLTCTRL = 0;  
	FTMx->FLTPOL = 0;      
	FTMx->CONF = 0;      
	FTMx->SYNCONF = 0;      
	FTMx->SWOCTRL = 0;      
	FTMx->PWMLOAD = 0;    
}

/**
  * @brief  FTMx外设寄存器初始化.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_InitStruct: 指定FTM_InitTypeDef配置.
  * @retval None.
  */
void FTM_Init(FTM_Type* FTMx, const FTM_InitTypeDef* FTM_InitStruct)
{
	/*---------------------------- FTMx SC Configuration -----------------*/
	/* write SC to enable clock */
	FTMx->SC &= ~(FTM_SC_CLKS_MASK | FTM_SC_PS_MASK);
	
	FTMx->SC |= ((FTM_InitStruct->FTM_ClkSource << FTM_SC_CLKS_SHIFT)| (FTM_InitStruct->FTM_Prescaler));
	/* At this step, return the status of initialization */
}


/**
  * @brief  FTMx指定通道边缘对齐PWM配置.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @param  PWMEdgeSelect: 边沿选择
  *		这个参数可以为以下值:
  *			@arg FTM_PWM_HIGHTRUEPULSE: 匹配时清零输出
  *			@arg FTM_PWM_LOWTRUEPULSE: 匹配时置位输出
  * @retval None
  */
void FTM_EdgeAlignedPWMInit(FTM_Type* FTMx, uint8_t FTM_Channel, uint8_t PWMEdgeSelect)
{ 
	/* disable counter */  
	FTMx->SC  = 0x0;                                    
	FTMx->MOD = FTM_MOD_INIT; 
	
	if(FTM_PWM_HIGHTRUEPULSE == PWMEdgeSelect)
	{
		/* Configure timers PWM High True Pulses */
		FTMx->CONTROLS[FTM_Channel].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;  
		FTMx->CONTROLS[FTM_Channel].CnV  = FTM_C0V_INIT + (FTM_Channel*(uint32_t)100); 
	}
	else
	{
		/* Configure timers for PWM Low True Pulses */
		FTMx->CONTROLS[FTM_Channel].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSA_MASK; 
		FTMx->CONTROLS[FTM_Channel].CnV  = FTM_C0V_INIT + (FTM_Channel*(uint32_t)100) ;
	}
}


/**
  * @brief  FTMx指定通道中心对齐PWM配置.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @param  PWMEdgeSelect: 边沿选择
  *		这个参数可以取下面的值:
  *			@arg FTM_PWM_HIGHTRUEPULSE: 匹配时清零输出
  *			@arg FTM_PWM_LOWTRUEPULSE: 匹配时置位输出
  * @retval None
  */
void FTM_CenterAlignedPWMInit(FTM_Type* FTMx, uint8_t FTM_Channel, uint8_t PWMEdgeSelect)
{ 
	/* disable counter */ 
	FTMx->SC  = 0x0;                                     
	FTMx->MOD = FTM_MOD_INIT; 
	
	FTMx->SC |= FTM_SC_CPWMS_MASK; 
	
	if(FTM_PWM_HIGHTRUEPULSE == PWMEdgeSelect)
	{
		/* Configure timers PWM High True Pulses */
		FTMx->CONTROLS[FTM_Channel].CnSC =  FTM_CnSC_ELSB_MASK; 
		FTMx->CONTROLS[FTM_Channel].CnV  = FTM_C0V_INIT + (FTM_Channel * (uint32_t)100); 
	}
	else
	{
		/* Configure timers for PWM Low True Pulses */
		FTMx->CONTROLS[FTM_Channel].CnSC =  FTM_CnSC_ELSA_MASK; 
		FTMx->CONTROLS[FTM_Channel].CnV  = FTM_C0V_INIT + (FTM_Channel * (uint32_t)100);
	}  
}

/**
  * @brief  FTMx组合模式PWM配置.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_CombinePWMStruct: 指向FTM_CombinePWMTypeDef配置.
  * @retval None
  */
void FTM_CombinePWMPWMInit(FTM_Type* FTMx, const FTM_CombinePWMTypeDef *FTM_CombinePWMStruct)
{ 
	/* disable counter */  
	FTMx->SC  = 0x0;                                    
	FTMx->MOD = FTM_MOD_INIT; 
			
	FTMx->SC &= ~FTM_SC_CPWMS_MASK; 
	
	if(FTM_CombinePWMStruct->FTM_ChannelPair == FTM_CHANNELPAIR0)
	{
		FTMx->COMBINE &= ~(FTM_COMBINE_COMBINE0_MASK | FTM_COMBINE_COMP0_MASK | FTM_COMBINE_DTEN0_MASK | \
							FTM_COMBINE_SYNCEN0_MASK | FTM_COMBINE_FAULTEN0_MASK);
		
		FTMx->COMBINE |= ((FTM_CombinePWMStruct->FTM_CombineEn) | \
							(FTM_CombinePWMStruct->FTM_CompEn << FTM_COMBINE_COMP0_SHIFT)| \
							(FTM_CombinePWMStruct->FTM_DeadtimeEn << FTM_COMBINE_DTEN0_SHIFT) | 
							(FTM_CombinePWMStruct->FTM_SynchronizationEn << FTM_COMBINE_SYNCEN0_SHIFT)| \
							(FTM_CombinePWMStruct->FTM_FaultControlEn << FTM_COMBINE_FAULTEN0_SHIFT));
	}
	else if(FTM_CombinePWMStruct->FTM_ChannelPair==FTM_CHANNELPAIR1)
	{
		FTMx->COMBINE &= ~(FTM_COMBINE_COMBINE1_MASK | FTM_COMBINE_COMP1_MASK | FTM_COMBINE_DTEN1_MASK | \
							FTM_COMBINE_SYNCEN1_MASK | FTM_COMBINE_FAULTEN1_MASK);
		
		FTMx->COMBINE |= ((FTM_CombinePWMStruct->FTM_CombineEn << FTM_COMBINE_COMBINE1_SHIFT) | \
							(FTM_CombinePWMStruct->FTM_CompEn << FTM_COMBINE_COMP1_SHIFT)| \
							(FTM_CombinePWMStruct->FTM_DeadtimeEn << FTM_COMBINE_DTEN1_SHIFT) | 
							(FTM_CombinePWMStruct->FTM_SynchronizationEn << FTM_COMBINE_SYNCEN1_SHIFT)| \
							(FTM_CombinePWMStruct->FTM_FaultControlEn << FTM_COMBINE_FAULTEN1_SHIFT));
	}	
	else if(FTM_CombinePWMStruct->FTM_ChannelPair==FTM_CHANNELPAIR2)
	{
		FTMx->COMBINE &= ~(FTM_COMBINE_COMBINE2_MASK | FTM_COMBINE_COMP2_MASK | FTM_COMBINE_DTEN2_MASK | \
							FTM_COMBINE_SYNCEN2_MASK | FTM_COMBINE_FAULTEN2_MASK);
		
		FTMx->COMBINE |= ((FTM_CombinePWMStruct->FTM_CombineEn << FTM_COMBINE_COMBINE2_SHIFT) | \
							(FTM_CombinePWMStruct->FTM_CompEn << FTM_COMBINE_COMP2_SHIFT)| \
							(FTM_CombinePWMStruct->FTM_DeadtimeEn << FTM_COMBINE_DTEN2_SHIFT) | 
							(FTM_CombinePWMStruct->FTM_SynchronizationEn << FTM_COMBINE_SYNCEN2_SHIFT)| \
							(FTM_CombinePWMStruct->FTM_FaultControlEn << FTM_COMBINE_FAULTEN2_SHIFT));
	}
	else
	{
		FTMx->COMBINE &= ~(FTM_COMBINE_COMBINE3_MASK | FTM_COMBINE_COMP3_MASK | FTM_COMBINE_DTEN3_MASK | \
							FTM_COMBINE_SYNCEN3_MASK | FTM_COMBINE_FAULTEN3_MASK);
		
		FTMx->COMBINE |= ((FTM_CombinePWMStruct->FTM_CombineEn << FTM_COMBINE_COMBINE3_SHIFT) | \
							(FTM_CombinePWMStruct->FTM_CompEn << FTM_COMBINE_COMP3_SHIFT)| \
							(FTM_CombinePWMStruct->FTM_DeadtimeEn << FTM_COMBINE_DTEN3_SHIFT) | 
							(FTM_CombinePWMStruct->FTM_SynchronizationEn << FTM_COMBINE_SYNCEN3_SHIFT)| \
							(FTM_CombinePWMStruct->FTM_FaultControlEn << FTM_COMBINE_FAULTEN3_SHIFT));
	}

	if(FTM_PWM_HIGHTRUEPULSE == FTM_CombinePWMStruct->PWMEdgeSelect)
	{
		/* Configure timers PWM High True Pulses */
		FTMx->CONTROLS[FTM_CombinePWMStruct->FTM_ChannelPair].CnSC = FTM_CnSC_ELSB_MASK;  
		FTMx->CONTROLS[FTM_CombinePWMStruct->FTM_ChannelPair].CnV  = FTM_C0V_INIT + (FTM_CombinePWMStruct->FTM_ChannelPair*(uint32_t)100); 
		
		FTMx->CONTROLS[FTM_CombinePWMStruct->FTM_ChannelPair + (uint32_t)1].CnSC = FTM_CnSC_ELSB_MASK;  
		FTMx->CONTROLS[FTM_CombinePWMStruct->FTM_ChannelPair + (uint32_t)1].CnV  = FTM_C0V_INIT + ((FTM_CombinePWMStruct->FTM_ChannelPair+(uint32_t)1)*(uint32_t)100); 
	}
	else
	{
		/* Configure timers for PWM Low True Pulses */
		FTMx->CONTROLS[FTM_CombinePWMStruct->FTM_ChannelPair].CnSC = FTM_CnSC_ELSA_MASK; 
		FTMx->CONTROLS[FTM_CombinePWMStruct->FTM_ChannelPair].CnV  = FTM_C0V_INIT + (FTM_CombinePWMStruct->FTM_ChannelPair* (uint32_t)100);
		
		FTMx->CONTROLS[FTM_CombinePWMStruct->FTM_ChannelPair + (uint32_t)1].CnSC = FTM_CnSC_ELSA_MASK; 
		FTMx->CONTROLS[FTM_CombinePWMStruct->FTM_ChannelPair + (uint32_t)1].CnV  = FTM_C0V_INIT + ((FTM_CombinePWMStruct->FTM_ChannelPair+ (uint32_t)1)* (uint32_t)100) ; 		
	}  
}


/**
  * @brief  FTMxPWM初始化
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  PWMModeSelect: 选择pwm模式.
  *		这个参数可以取下面的值:
  *			@arg FTM_PWMMODE_EDGEALLIGNED: 边沿对齐模式
  *			@arg FTM_PWMMODE_CENTERALLIGNED: 中心模式对齐
  *			@arg FTM_PWMMODE_COMBINE: 组合模式
  * @param  PWMEdgeSelect: 边沿选择
  *		这个参数可以取下面的值:
  *			@arg FTM_PWM_HIGHTRUEPULSE: 匹配时清零输出
  *			@arg FTM_PWM_LOWTRUEPULSE: 匹配时置位输出
  * @retval None
  */
void FTM_PWMInit(FTM_Type* FTMx, uint8_t PWMModeSelect, uint8_t PWMEdgeSelect)
{
	uint8_t channels, i;

	/* channels num */
	if (FTM0 == FTMx)
	{
		channels = 2;
	}
	else if(FTM1 == FTMx)
	{
		channels = 2;
	}        
	else
	{
		channels = 6;
	}
	/* disable counter */ 
	FTMx->SC  = 0x0;                                     
	FTMx->MOD = FTM_MOD_INIT; 
	 
	/* enable CPWM */
	if(FTM_PWMMODE_CENTERALLIGNED == PWMModeSelect)  
	{
		FTMx->SC |= FTM_SC_CPWMS_MASK; 
	}
	/* enable combine pwm mode */
	else if(FTM_PWMMODE_COMBINE == PWMModeSelect)
	{
		FTMx->MODE    |= FTM_MODE_WPDIS_MASK | FTM_MODE_SYNCLOADEN_MASK;
		FTMx->COMBINE = FTM_COMBINE_COMBINE0_MASK | FTM_COMBINE_COMP0_MASK | FTM_COMBINE_SYNCEN0_MASK | FTM_COMBINE_DTEN0_MASK |
										FTM_COMBINE_COMBINE1_MASK | FTM_COMBINE_COMP1_MASK | FTM_COMBINE_SYNCEN1_MASK | FTM_COMBINE_DTEN1_MASK |
										FTM_COMBINE_COMBINE2_MASK | FTM_COMBINE_COMP2_MASK | FTM_COMBINE_SYNCEN2_MASK | FTM_COMBINE_DTEN2_MASK ;     
		FTMx->SC &= ~FTM_SC_CPWMS_MASK; 
	}
	else
	{
		FTMx->SC &= ~FTM_SC_CPWMS_MASK;
	}
	
	if(FTM_PWM_HIGHTRUEPULSE == PWMEdgeSelect)
	{
		/* Configure timers PWM High True Pulses */
		for(i=0; i<channels; i++)
		{
				FTMx->CONTROLS[i].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;  
				FTMx->CONTROLS[i].CnV  = FTM_C0V_INIT + (i*(uint32_t)100); 
		}
	}
	else
	{
		/* Configure timers for PWM Low True Pulses */
		for(i=0; i<channels; i++) 
		{
				FTMx->CONTROLS[i].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSA_MASK; 
				FTMx->CONTROLS[i].CnV  = FTM_C0V_INIT + (i*(uint32_t)100); 
		}
	}  
}

/**
  * @brief  FTMx输入捕获初始化
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @param  CaptureMode: 选择捕获边沿.
  *		这个参数可以取下面的值:
  *			@arg FTM_INPUTCAPTURE_RISINGEDGE: 上升沿捕获
  *			@arg FTM_INPUTCAPTURE_FALLINGEDGE: 下降沿捕获
  *			@arg FTM_INPUTCAPTURE_BOTHEDGE: 双边沿捕获
  * @retval None
  * VIP QUESTION
  */
void FTM_InputCaptureInit(FTM_Type* FTMx, uint8_t FTM_Channel, uint8_t CaptureMode)
{
	FTMx->SC  = 0x0;     /* disable counter */ 
	FTMx->MOD = 0xFFFF;  /* free running */
	
	/* enable interrupt, Capture on rising edge */
	if(FTM_INPUTCAPTURE_RISINGEDGE == CaptureMode)        
	{
		FTMx->CONTROLS[FTM_Channel].CnSC = FTM_CnSC_CHIE_MASK | FTM_CnSC_ELSA_MASK;
	}
	
	/* Capture on falling edge */
	else if(FTM_INPUTCAPTURE_FALLINGEDGE == CaptureMode)  
	{
		FTMx->CONTROLS[FTM_Channel].CnSC = FTM_CnSC_CHIE_MASK | FTM_CnSC_ELSB_MASK;
	}
	
	/* Capture on rising or falling edge */
	else
	{
		FTMx->CONTROLS[FTM_Channel].CnSC = FTM_CnSC_CHIE_MASK | FTM_CnSC_ELSA_MASK | FTM_CnSC_ELSB_MASK;       
	}
}


/**
  * @brief  FTMx双沿捕获初始化
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_DualEdgeStruct: 指向FTM_DualEdgeCaptureTypeDef配置.
  * @retval None
  */
void FTM_DualEdgeCaptureInit(FTM_Type* FTMx, const FTM_DualEdgeCaptureTypeDef* FTM_DualEdgeStruct)
{ 
	/* diable counter */ 	
	FTMx->SC    = 0x0;                  
	FTMx->MOD   = 0xFFFF;

	/* DECAPEN = 1,  ChannelPair/2 * 8 */
	FTMx->COMBINE |=  ((uint32_t)(FTM_COMBINE_DECAPEN0_MASK) << (FTM_DualEdgeStruct->FTM_ChannelPair * 4u)); 

	/* CH(n)F and CH(n+1)F bits must be cleared first */
	FTMx->CONTROLS[FTM_DualEdgeStruct->FTM_ChannelPair].CnSC &= ~FTM_CnSC_CHF_MASK;       
	FTMx->CONTROLS[FTM_DualEdgeStruct->FTM_ChannelPair + (uint8_t)1].CnSC &= ~FTM_CnSC_CHF_MASK;

	/* oneshot mode */
	if(FTM_INPUTCAPTURE_DUALEDGE_ONESHOT == FTM_DualEdgeStruct->FTM_CaptureMode)          
	{
		FTMx->CONTROLS[FTM_DualEdgeStruct->FTM_ChannelPair].CnSC &= ~FTM_CnSC_MSA_MASK;
		FTMx->CONTROLS[FTM_DualEdgeStruct->FTM_ChannelPair + (uint8_t)1].CnSC &= ~FTM_CnSC_MSA_MASK;
	}
	/* continuouse mode */
	else
	{
		FTMx->CONTROLS[FTM_DualEdgeStruct->FTM_ChannelPair].CnSC |= FTM_CnSC_MSA_MASK;
		FTMx->CONTROLS[FTM_DualEdgeStruct->FTM_ChannelPair + (uint8_t)1u].CnSC |= FTM_CnSC_MSA_MASK;
	}

	/* select detec edge */
	FTMx->CONTROLS[FTM_DualEdgeStruct->FTM_ChannelPair].CnSC |= (FTM_DualEdgeStruct->FTM_Channel_N_Edge << (uint8_t)2);   
	FTMx->CONTROLS[FTM_DualEdgeStruct->FTM_ChannelPair + (uint8_t)1].CnSC |= (FTM_DualEdgeStruct->FTM_Channel_Np1_Edge << (uint8_t)2);   

	FTMx->COMBINE |= ((uint32_t)FTM_COMBINE_DECAP0_MASK << (FTM_DualEdgeStruct->FTM_ChannelPair * 4u)); 
}

/**
  * @brief  FTMx输出比较初始化
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @param  CompareMode: 选择比较边沿
  *		这个参数可以取下面的值:
  *			@arg FTM_OUTPUT_TOGGLE: 匹配时切换输出
  *			@arg FTM_OUTPUT_CLEAR: 匹配时清零输出
  *			@arg FTM_OUTPUT_SET: 匹配时置位输出
  * @retval None
  */
void FTM_OutputCompareInit(FTM_Type* FTMx, uint8_t FTM_Channel, uint32_t CompareMode)
{
	FTM_WriteProtectDisable(FTMx );
	
	/* diable counter */
	FTMx->SC  = 0x0;                                                                    
	FTMx->MOD = FTM_MOD_INIT; 
	
	/* select detec edge */
	FTMx->CONTROLS[FTM_Channel].CnSC = (FTM_CnSC_MSA_MASK | (CompareMode << (uint8_t)2u));    
	FTMx->CONTROLS[FTM_Channel].CnV  = FTM_C0V_INIT;
}

/**
  * @brief  使能FTM溢出中断.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  NewState:FTMx溢出中断是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能FTMx溢出中断
  *			@arg DISABLE: 失能FTMx溢出中断
  * @retval None
  */
void FTM_OverflowITCmd(FTM_Type* FTMx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* first clear the Timer Overflow flag */
		if((FTMx->SC & FTM_SC_TOF_MASK) == FTM_SC_TOF_MASK)
		{
			FTMx->SC &= ~FTM_SC_TOF_MASK;
		} 
			/* Enable the Timer Overflow interrupt function */
		FTMx->SC |= FTM_SC_TOIE_MASK;
	}
	else
	{
		/* Disable the Timer Overflow interrupt function */
		FTMx->SC &= ~FTM_SC_TOIE_MASK;
	}
}

/**
  * @brief 获取溢出标志状态.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @retval 当前状态(TRUE or FALSE) 
  */
FlagStatus FTM_GetOverFlowFlag(const FTM_Type* FTMx)
{
  return ((FTMx->SC & FTM_SC_TOF_MASK) == FTM_SC_TOF_MASK);
}


/**
  * @brief  使能FTM通道对中CV 寄存器同步.
  * @param  FTMx: 选择FTM外设.
  *           这个参数可以取下面的值:
  *                  @arg FTM0: FTM0外设
  *                  @arg FTM1: FTM1外设
  *                  @arg FTM2: FTM2外设
  * @param  FTM_ ChannelPair: 选择FTM通道对.
  *           这个参数可以取下面的值:
  *                  @arg FTM_CHANNELPAIR0: FTMx通道对0
  *                  @arg FTM_CHANNELPAIR1: FTMx通道对1
  *                  @arg FTM_CHANNELPAIR2: FTMx通道对2
  *                  @arg FTM_CHANNELPAIR3: FTMx通道对3
  * @param  NewState:是否使能通道对中CV寄存器同步.
  *           这个参数可以取下面的值:
  *                  @arg ENABLE: 使能CV寄存器同步
  *                  @arg DISABLE: 失能CV寄存器同步
 
  * @retval None
  */
void FTM_CVSyncEnable(FTM_Type* FTMx,uint8_t FTM_ChannelPair,FunctionalState State)
{
	if(State == ENABLE)
	{
		if(FTM_ChannelPair == FTM_CHANNELPAIR0)
		{
			FTMx->COMBINE |= FTM_COMBINE_SYNCEN0_MASK;
		}
		else if(FTM_ChannelPair == FTM_CHANNELPAIR1)
		{
			FTMx->COMBINE |= FTM_COMBINE_SYNCEN1_MASK;
		}
		else if(FTM_ChannelPair == FTM_CHANNELPAIR2)
		{
			FTMx->COMBINE |= FTM_COMBINE_SYNCEN2_MASK;
		}
		else
		{
			FTMx->COMBINE |= FTM_COMBINE_SYNCEN3_MASK;
		}
	}
	else
	{
		if(FTM_ChannelPair == FTM_CHANNELPAIR0)
		{
			FTMx->COMBINE &= ~FTM_COMBINE_SYNCEN0_MASK;
		}
		else if(FTM_ChannelPair == FTM_CHANNELPAIR1)
		{
			FTMx->COMBINE &= ~FTM_COMBINE_SYNCEN1_MASK;
		}
		else if(FTM_ChannelPair == FTM_CHANNELPAIR2)
		{
			FTMx->COMBINE &= ~FTM_COMBINE_SYNCEN2_MASK;
		}
		else
		{
			FTMx->COMBINE &= ~FTM_COMBINE_SYNCEN3_MASK;
		}
	}
}

/**
  * @brief  清除FTMx溢出标志.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @retval None
  */
void FTM_ClrOverFlowFlag(FTM_Type* FTMx)
{
	if((FTMx->SC & FTM_SC_TOF_MASK) == FTM_SC_TOF_MASK)
	{
		FTMx->SC &= ~FTM_SC_TOF_MASK;
	}
}

/**
  * @brief  获取CNT值.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @retval 返回CNT的值.
  */
uint16_t FTM_GetCountValue(const FTM_Type* FTMx)
{
	return (uint16_t)FTMx->CNT;
}

/**
  * @brief  设置MOD值.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  ModValue: 设定MOD值.
  * @retval None
  */
void FTM_SetModValue(FTM_Type* FTMx, uint16_t ModValue)
{
	FTMx->CNT = 0;
	FTMx->MOD = ModValue;
}

/**
  * @brief  设置CNTIN值.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @retval None
  */
void FTM_SetCountInitValue(FTM_Type* FTMx, uint16_t InitialValue)
{
	FTMx->CNTIN = InitialValue;
}

/**
  * @brief  FTMx通道中断使能
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @param  NewState: FTMx相应通道中断是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能FTMx通道中断
  *			@arg DISABLE: 失能FTMx通道中断
  * @retval None
  */
void FTM_ChannelIntCmd(FTM_Type* FTMx, uint8_t FTM_Channel, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
		/* Enable the channel interrupt function */
		FTMx->CONTROLS[FTM_Channel].CnSC |= FTM_CnSC_CHIE_MASK;
  }
  else
  {
    /* Disable the channel interrupt function */
    FTMx->CONTROLS[FTM_Channel].CnSC &= ~FTM_CnSC_CHIE_MASK;
  }
	
}

/**
  * @brief  FTM获取通道标志
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @retval 返回通道标志.
  */
FlagStatus FTM_GetChannelFlag(const FTM_Type* FTMx, uint8_t FTM_Channel)
{
  return ((FTMx->CONTROLS[FTM_Channel].CnSC & FTM_CnSC_CHF_MASK) == FTM_CnSC_CHF_MASK);
}

/**
  * @brief  FTM清除通道标志
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @retval None
  */
void FTM_ClrChannelFlag(FTM_Type* FTMx, uint8_t FTM_Channel)
{
	//Dummy read while CHF is set
	(void) FTMx->CONTROLS[FTM_Channel].CnSC; 
	FTMx->CONTROLS[FTM_Channel].CnSC &= ~FTM_CnSC_CHF_MASK;
}

/**
  * @brief  FTM设置通道值
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @param  ChannelValue: 设定通道值.
  * @retval None
  */
void FTM_SetChannelValue(FTM_Type* FTMx, uint8_t FTM_Channel, uint16_t ChannelValue)
{
	FTMx->CONTROLS[FTM_Channel].CnV = ChannelValue;
}
/**
  * @brief  FTM获取通道值
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @retval 通道值
  */
uint16_t FTM_GetChannelValue(const FTM_Type* FTMx, uint8_t FTM_Channel )
{
	return (uint16_t)FTMx->CONTROLS[FTM_Channel].CnV;
}
/**
  * @brief 获取所有通道溢出标志.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @retval 返回所有通道标志.
  */
uint32_t FTM_GetStatusRegFlag(const FTM_Type* FTMx)
{
  return (FTMx->STATUS & 0xFFu);
}

/**
  * @brief 清除所有通道溢出标志.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @retval None
  */
void FTM_ClrStatusRegFlag(FTM_Type* FTMx)
{
	if((FTMx->STATUS & 0xFFu) != 0u)
	{
		FTMx->STATUS = 0x00;
	}
}

/**
  * @brief 得到指定通道溢出标志.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @retval 返回所有通道标志.
  */
FlagStatus FTM_GetStatusChannelFlag(const FTM_Type* FTMx, uint8_t ChannelFlag)
{
	uint32_t flag;
	
	/* Get all the channel flags */
	flag = FTMx->STATUS ;
	
	/* get the selected channel flag */
	return ((flag &((uint32_t)1<<ChannelFlag))  == ((uint32_t)1<<ChannelFlag));
}

/**
  * @brief  清除指定通道溢出标志.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @retval None
  */
void FTM_ClrStatusChannelFlag(FTM_Type* FTMx, uint8_t ChannelFlag)
{
	if((FTMx->STATUS & ((uint32_t)1<<ChannelFlag)) != 0u)
	{
		FTMx->STATUS &= ~((uint32_t)1<<ChannelFlag);
	}
}

/**
  * @brief 使能错误中断.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  NewState: 错误中断是否使能
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能FTMx错误中断
  *			@arg DISABLE: 失能FTMx错误中断
  * @retval None
  */
void FTM_FaultITCmd(FTM_Type* FTMx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the fault interrupt  */
		FTMx->MODE |= FTM_MODE_FAULTIE_MASK;
	}
	else
	{
		/* Disable the fault interrupt  */
		FTMx->MODE &= ~FTM_MODE_FAULTIE_MASK;
	}
}

/**
  * @brief 定义FTM错误控制模式.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_FaultControlModeDef: 选择错误控制模式.
  *		这个参数可以取下面的值:
  *			@arg FTM_ALLDISABLE: 所有通道禁用故障
  *			@arg FTM_EVENENABLE_MANUALCLEAR: 偶数通道使能故障控制，手动故障清零.
  *			@arg FTM_ALLENABLE_MANUALCLEAR: 所有通道使能故障控制，手动故障清零.
  *			@arg FTM_ALLENABLE_AUTOCLEAR: 所有通道使能故障控制，自动故障清零.
  * @retval None
  */
void FTM_SetFaultControlMode(FTM_Type* FTMx, FTM_FaultControlModeDef FTM_FaultControlMode)
{	
	FTMx->MODE &= ~FTM_MODE_FAULTM_MASK;
	
	FTMx->MODE |= ((uint32_t)FTM_FaultControlMode << FTM_MODE_FAULTM_SHIFT);
}

/**
  * @brief 使能捕获测试模式.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  NewState: 捕获测试是否使能
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能FTMx捕获测试
  *			@arg DISABLE: 失能FTMx捕获测试
  * @retval None
  */
void FTM_CaptureTestCmd(FTM_Type* FTMx, FunctionalState NewState)
{	
	if (NewState != DISABLE)
	{
		/* Enable the CAPTEST function */
		FTMx->MODE |= FTM_MODE_CAPTEST_MASK;
	}
	else
	{
		/* Disable the CAPTEST function */
		FTMx->MODE &= ~FTM_MODE_CAPTEST_MASK;
	}	
}

/**
  * @brief 选择PWM同步软件触发.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  NewState: PWM同步软件触发是否使能
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能FTMx的PWM同步软件触发
  *			@arg DISABLE: 失能FTMx的PWM同步软件触发
  * @retval None
  */
void FTM_SoftwareSync(FTM_Type* FTMx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the SWSYNC function */
		FTMx->SYNC |= FTM_SYNC_SWSYNC_MASK;
	}
	else
	{
		/* Disable the SWSYNC function */
		FTMx->SYNC &= ~FTM_SYNC_SWSYNC_MASK;
	}		
}

/**
  * @brief 选择PWM同步硬件触发.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  TriggerN: 同步触发信号选择
  *		这个参数可以取下面的值:
  *			@arg FTM_SYNC_TRIGGER_TRIGGER0: Tigger0 synchronization
  *			@arg FTM_SYNC_TRIGGER_TRIGGER1: Tigger1 synchronization
  *			@arg FTM_SYNC_TRIGGER_TRIGGER2: Tigger2 synchronization
  * @param  NewState: PWM同步硬件触发是否使能
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能FTMx的PWM同步硬件触发
  *			@arg DISABLE: 失能FTMx的PWM同步硬件触发
  * @retval None
  */
void FTM_HardwareSync(FTM_Type* FTMx, uint8_t TriggerN, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the selected Trigger */
		FTMx->SYNC |= ((uint32_t)TriggerN);
	}
	else
	{
		/* Disable the selected Trigger */
		FTMx->SYNC &= ~((uint32_t)TriggerN);
	}
}

/**
  * @brief 选择SWOCTRL/INVCTRL/OUTMASK/MOD, CNTIN和CV/CNT同步.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  TriggerType: 触发模式选择.
  *		这个参数可以取下面的值:
  *			@arg FTM_SYNCONF_SWTRIGGER: 软件触发模式
  *			@arg FTM_SYNCONF_HWTRIGGER: 硬件触发模式
  * @param  RegType: 寄存器同步控制.
  *		这个参数可以取下面的值:
  *			@arg FTM_SYNCONF_CNTREG: CNT寄存器同步
  *			@arg FTM_SYNCONF_MODCNTINCVREG: MOD、CNTIN和CV寄存器同步
  *			@arg FTM_SYNCONF_OUTMASKREG: OUTMASK 寄存器同步
  *			@arg FTM_SYNCONF_INVCTRLREG: INVCTRL寄存器同步
  *			@arg FTM_SYNCONF_SWOCTRLREG: SWOCTRL寄存器同步
  * @param  NewState: 同步是否使能.
  *			@arg ENABLE: 使能FTMx的PWM同步硬件触发
  *			@arg DISABLE: 失能FTMx的PWM同步硬件触发
  * @retval None
  */
void FTM_RegSyncCmd(FTM_Type* FTMx, uint8_t TriggerType, uint8_t RegType, FunctionalState NewState)
{
	uint32_t tempvalue;
	
	if(TriggerType == FTM_SYNCONF_SWTRIGGER)
	{
		tempvalue= ((uint32_t)0x100 << RegType);
		
		if (NewState != DISABLE)
		{
			/* Enable the software trigger activate synchronization. */
			FTMx->SYNCONF |= tempvalue;
		}
		else
		{
			/* Disable the software trigger activate synchronization. */
			FTMx->SYNCONF &= ~tempvalue;
		}
	}
	else
	{
		tempvalue= ((uint32_t)0x10000 << RegType);
		
		if (NewState != DISABLE)
		{
			/* Enable the hardware trigger activate synchronization. */
			FTMx->SYNCONF |= tempvalue;
		}
		else
		{
			/* Disable the hardware trigger activate synchronization. */
			FTMx->SYNCONF &= ~tempvalue;
		}
	}
}

/**
  * @brief  OUTMASK寄存器同步
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  update:同步模式选择
  *		这个参数可以取下面的值:
  *			@arg FTM_UPDATE_RISINGCLK: 寄存器在所有系统的上升沿进行同步更新
  *			@arg FTM_UPDATE_PWMSYNC: 寄存器仅通过PWM同步更新
  * @retval None
  */
void FTM_OutMaskSync(FTM_Type* FTMx,  uint8_t update)
{
	if(FTM_UPDATE_PWMSYNC==update)
	{
		/* updated with the value of its buffer only by the PWM synchronization. */
		FTMx->SYNC |= FTM_SYNC_SYNCHOM_MASK;
	}
	else
	{
		/* updated with the value of its buffer in all rising edges of the system clock. */		
		FTMx->SYNC &= ~FTM_SYNC_SYNCHOM_MASK;
	}
}

/**
  * @brief CNTIN寄存器同步
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  update:同步更新模式选择
  *		这个参数可以取下面的值:
  *			@arg FTM_UPDATE_RISINGCLK: 寄存器在所有系统的上升沿进行同步更新
  *			@arg FTM_UPDATE_PWMSYNC: 寄存器仅通过PWM同步更新
  * @retval None
  */
void FTM_CNTINCSync(FTM_Type* FTMx,  uint8_t update)
{
	if(FTM_UPDATE_PWMSYNC==update)
	{
		/* updated with the value of its buffer only by the PWM synchronization. */		
		FTMx->SYNCONF |= FTM_SYNCONF_CNTINC_MASK;
	}
	else
	{
		/* updated with the value of its buffer in all rising edges of the system clock. */				
		FTMx->SYNCONF &= ~FTM_SYNCONF_CNTINC_MASK;
	}
}

/**
  * @brief INVCTRL寄存器同步.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  update:同步更新模式选择
  *		这个参数可以取下面的值:
  *			@arg FTM_UPDATE_RISINGCLK: 寄存器在所有系统的上升沿进行同步更新
  *			@arg FTM_UPDATE_PWMSYNC: 寄存器仅通过PWM同步更新
  * @retval None
  */
void FTM_INVCSync(FTM_Type* FTMx,  uint8_t update)
{
	if(FTM_UPDATE_PWMSYNC==update)
	{
		/* updated with the value of its buffer only by the PWM synchronization. */			
		FTMx->SYNCONF |= FTM_SYNCONF_INVC_MASK;
	}
	else
	{
		/* updated with the value of its buffer in all rising edges of the system clock. */				
		FTMx->SYNCONF &= ~FTM_SYNCONF_INVC_MASK;
	}
}

/**
  * @brief SWOCTRL寄存器同步.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  update:同步更新模式选择
  *		这个参数可以取下面的值:
  *			@arg FTM_UPDATE_RISINGCLK: 寄存器在所有系统的上升沿进行同步更新
  *			@arg FTM_UPDATE_PWMSYNC: 寄存器仅通过PWM同步更新
  * @retval None
  */
void FTM_SWOCSync(FTM_Type* FTMx,  uint8_t update)
{
	if(FTM_UPDATE_PWMSYNC==update)
	{
		/* updated with the value of its buffer only by the PWM synchronization. */			
		FTMx->SYNCONF |= FTM_SYNCONF_SWOC_MASK;
	}
	else
	{
		/* updated with the value of its buffer in all rising edges of the system clock. */		
		FTMx->SYNCONF &= ~FTM_SYNCONF_SWOC_MASK;
	}
}

/**
  * @brief 选择PWM同步模式.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  mode:模式选择
  *		这个参数可以取下面的值:
  *			@arg FTM_SYNCMODE_LEGACY: 选择传统PWM同步
  *			@arg FTM_SYNCMODE_ENHANCED: 选择增强PWM同步
  * @retval None
  */
void FTM_SetSyncMode(FTM_Type* FTMx,  uint8_t mode)
{
	if(FTM_SYNCMODE_ENHANCED == mode)
	{
		/* selecte Enhanced PWM synchronization */
		FTMx->SYNCONF |= FTM_SYNCONF_SYNCMODE_MASK;
	}
	else
	{
		/* selecte Legacy PWM synchronization . */
		FTMx->SYNCONF &= ~FTM_SYNCONF_SYNCMODE_MASK;
	}
}

/**
  * @brief FTM软件同步触发类型
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  type:模式选择
  *		这个参数可以取下面的值:
	*			@arg FTM_SOFTWARE_SYN_CNT: 软件触发激活FTM计数器同步
	*			@arg FTM_SOFTWARE_SYN_MOD_CNTIN_CV: 软件触发激活MOD、CNTIN、CV寄存器同步
	*			@arg FTM_SOFTWARE_SYN_OUTMASK: 软件触发激活输出屏蔽同步
	*			@arg FTM_SOFTWARE_SYN_INVCTRL: 软件触发激活反相控制同步
	*			@arg FTM_SOFTWARE_SYN_OUTCTRL: 软件触发激活输出控制同步
  * @param  NewState: 软件同步激活模式是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能
  *			@arg DISABLE: 失能
  * @retval None
  */
void FTM_SoftSyncActivateTypeEnable(FTM_Type* FTMx,  uint32_t type, FunctionalState NewState)
{
	if(NewState != DISABLE)
	{
		FTMx->SYNCONF |= type;
	}
	else
	{
		FTMx->SYNCONF &= ~type;
	}
}

/**
  * @brief FTM硬件同步触发类型
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  type:模式选择
  *		这个参数可以取下面的值:
	*			@arg FTM_HARDWARE_SYN_CNT: 硬件触发激活FTM计数器同步
	*			@arg FTM_HARDWARE_SYN_MOD_CNTIN_CV: 硬件触发激活MOD、CNTIN、CV寄存器同步
	*			@arg FTM_HARDWARE_SYN_OUTMASK: 硬件触发激活输出屏蔽同步
	*			@arg FTM_HARDWARE_SYN_INVCTRL: 硬件触发激活反相控制同步
	*			@arg FTM_HARDWARE_SYN_OUTCTRL: 硬件触发激活输出控制同步
  * @param  NewState: 硬件同步激活模式是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 最大加载点使能
  *			@arg DISABLE: 最大加载点失能
  * @retval None
  */
void FTM_HardSyncActivateTypeEnable(FTM_Type* FTMx,  uint32_t type, FunctionalState NewState)
{
	if(NewState != DISABLE)
	{
		FTMx->SYNCONF |= type;
	}
	else
	{
		FTMx->SYNCONF &= ~type;
	}
}
	


/**
  * @brief 选择PWM同步模式.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  mode:模式选择
  *		这个参数可以取下面的值:
  *			@arg FTM_PWMSYNC_NORESTRICT: 可用于MOD,CnV,OUTMASK和FTM计数器同步的软件和硬件触发
  *			@arg FTM_PWMSYNC_SWANDHW: 软件触发只能用于MOD和CnV同步，硬件触发只能用于OUTMASK和FTM计数器同步
  * @retval None
  */
void FTM_SetPWMSyncMode(FTM_Type* FTMx,  uint8_t mode)
{
	if(FTM_PWMSYNC_SWANDHW == mode)
	{
		/* Software trigger can only be used by MOD and CnV synchronization, and hardware 
		triggers can only be used by OUTMASK and FTM counter synchronization */
		FTMx->MODE |= FTM_MODE_PWMSYNC_MASK;
	}
	else
	{
		/* Software and hardware triggers can be used by MOD, CnV, OUTMASK, and FTM
       counter synchronization. */
		FTMx->MODE &= ~FTM_MODE_PWMSYNC_MASK;
	}
}

/**
  * @brief 选择硬件触发模式.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  mode:模式选择
  *		这个参数可以取下面的值:
  *			@arg FTM_HWTRIGMODE_CLEAR: 检查到硬件触发时，FTM清零TRIG位
  *			@arg FTM_HWTRIGMODE_UNCLEAR: 检查到硬件触发时，FTM不清零TRIG位
  * @retval None
  */
void FTM_SetHardwareTriggerMode(FTM_Type* FTMx,  uint8_t mode)
{
	if(FTM_HWTRIGMODE_UNCLEAR == mode)
	{
		/* FTM does not clear the TRIGj bit when the hardware trigger j is detected, where j = 0, 1,2. */	
		FTMx->SYNCONF |= FTM_SYNCONF_HWTRIGMODE_MASK;
	}
	else
	{
		/* FTM clears the TRIGj bit when the hardware trigger j is detected, where j = 0, 1,2. */
		FTMx->SYNCONF &= ~FTM_SYNCONF_HWTRIGMODE_MASK;
	}
}

/**
  * @brief 选择PWM同步最大载入.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  NewState: 最大加载点是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 最大加载点使能
  *			@arg DISABLE: 最大加载点失能
  * @retval None
  */
void FTM_CNTMAXCmd(FTM_Type* FTMx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the CNTMAX function */
		FTMx->SYNC |= FTM_SYNC_CNTMAX_MASK;
	}
	else
	{
		/* Disable the CNTMAX function */
		FTMx->SYNC &= ~FTM_SYNC_CNTMAX_MASK;
	}	
}


/**
  * @brief 选择PWM同步最小载入.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  NewState: 最小加载点是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 最小加载点使能
  *			@arg DISABLE: 最小加载点失能
  * @retval None
  */
void FTM_CNTMINCmd(FTM_Type* FTMx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the CNTMIN function */
		FTMx->SYNC |= FTM_SYNC_CNTMIN_MASK;
	}
	else
	{
		/* Disable the CNTMIN function */
		FTMx->SYNC &= ~FTM_SYNC_CNTMIN_MASK;
	}	
}

/**
  * @brief FTM计数器同步重新预置.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  mode: 重新初始化配置
  *		这个参数可以取下面的值:
  *			@arg FTM_REINIT_NORMALLY: 正常计数
  *			@arg FTM_REINIT_UPDATED: 当检测到特定的触发时，FTM计数器以其初始值更新
  * @retval None
  */
void FTM_Reinitialization(FTM_Type* FTMx,  uint8_t mode)
{	
	if(FTM_REINIT_UPDATED == mode)
	{
		/* FTM counter is updated with its initial value when the selected trigger is detected. */
		FTMx->SYNC |= FTM_SYNC_REINIT_MASK;
	}
	else
	{
		/* FTM counter continues to count normally. */
		FTMx->SYNC &= ~FTM_SYNC_REINIT_MASK;
	}
}

/**
  * @brief 选择初始化发生时通道输出值.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  initialvalue:初始化通道输出
  * @retval None
  */
void FTM_SetInitOut(FTM_Type* FTMx, uint8_t initialvalue)
{
	FTMx->OUTINIT = initialvalue;
	
	/* When a 1 is written to INIT bit the channels output is initialized according to 
	the state of their corresponding bit in the OUTINIT register.*/
	FTMx->MODE |= FTM_MODE_INIT_MASK;
}

/**
  * @brief 指定通道选择初始化发生时通道输出值.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @param  initialvalue:指定通道初始化输出
  * @retval None
  */
void FTM_SetChannelOutInitValue(FTM_Type* FTMx,uint8_t FTM_Channel, uint8_t initialvalue)
{
	uint32_t tempvalue;

	tempvalue = ((uint32_t)1<<FTM_Channel);
	
	if(initialvalue != (uint32_t)0)
	{
		/* The initialization value is 1. */
		FTMx->OUTINIT |= tempvalue;
	}
	else
	{
		/* The initialization value is 0. */
		FTMx->OUTINIT &= ~tempvalue;
	}
	
	/* When a 1 is written to INIT bit the channels output is initialized according to 
	the state of their corresponding bit in the OUTINIT register.*/
	FTMx->MODE |= FTM_MODE_INIT_MASK;
}

/**
  * @brief 定义通道输出是否可见的.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  outmask: 设置outmask寄存器的值.
  * @retval None
  */
void FTM_SetOutMask(FTM_Type* FTMx, uint8_t outmask)
{
	/* Enable the Output Mask function */	
	FTMx->OUTMASK = outmask;
}

/**
  * @brief 定义指定通道输出是否可见的.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @param  NewState: 通道输出屏蔽是否使能
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 通道输出屏蔽
  *			@arg DISABLE: 通道输出未屏蔽
  * @retval None
  */
void FTM_SetChannelOutMaskCmd(FTM_Type* FTMx, uint8_t FTM_Channel, FunctionalState NewState)
{
	uint32_t maskvalue;
	
	maskvalue = ((uint32_t)1<<FTM_Channel);
	
	if (NewState != DISABLE)
	{
			/* Enable Output Mask */
			FTMx->OUTMASK |= maskvalue;
	}
	else
	{
			/* Disable Output Mask */
			FTMx->OUTMASK &= ~maskvalue;
	}
}

/**
  * @brief 选择死区预定区域和死区值.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  PrescalerValue: 死区时间预分频值
  *		这个参数可以取下面的值:
  *			@arg FTM_DEADTIME_DTPS_DIV1: FTMx时钟1分频
  *			@arg FTM_DEADTIME_DTPS_DIV4: FTMx时钟4分频
  *			@arg FTM_DEADTIME_DTPS_DIV16: FTMx时钟16分频
  * @param  DeadtimeValue: 死区时间(0x00~0x3F)
  * @retval None
  */
void FTM_PWMDeadtimeSet(FTM_Type* FTMx, uint32_t PrescalerValue, uint32_t DeadtimeValue)
{
	FTM0->DEADTIME = 0;
	/* set the deadtime */
	FTMx->DEADTIME = ((DeadtimeValue & (uint32_t)0x3F) | ((PrescalerValue & (uint32_t)0x3) << FTM_DEADTIME_DTPS_SHIFT));      
}

/**
  * @brief  获取通道触发标志.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @return 返回通道触发标志.
  */
FlagStatus FTM_GetExternalTriggerFlag(const FTM_Type* FTMx)
{
	return ((FTMx->EXTTRIG & FTM_EXTTRIG_TRIGF_MASK) == FTM_EXTTRIG_TRIGF_MASK);
}

/**
  * @brief 清除通道触发标志.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @retval None
  */
void FTM_ClrExternalTriggerFlag(FTM_Type* FTMx)
{
	/* first read the reg, then write 0 to clear */
	if((FTMx->EXTTRIG & FTM_EXTTRIG_TRIGF_MASK) == FTM_EXTTRIG_TRIGF_MASK)
	{
		FTMx->EXTTRIG &= ~FTM_EXTTRIG_TRIGF_MASK;
	}
}

/**
  * @brief 是否使能通道N触发.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  * @param  NewState: 通道N触发是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能通道N触发
  *			@arg DISABLE: 使能通道N触发
  * @retval None
  */
void FTM_SetChnTriggerCmd(FTM_Type* FTMx, uint8_t FTM_Channel, FunctionalState NewState)
{
	uint32_t value;
	
	/* Enable the hardware trigger mask function */	
	value = (FTM_Channel > 1U) ? ((uint32_t)1 << (FTM_Channel - 2U)) : ((uint32_t)1 << (FTM_Channel + 4U));

	if (NewState != DISABLE)
	{
			/* Enable The generation of the channel trigger */
			FTMx->EXTTRIG |= value;
	}
	else
	{
			/* Disable The generation of the channel trigger */
			FTMx->EXTTRIG &= ~value;
	}
}

/**
  * @brief 当FTM计数与CNTIN寄存器值相同时触发使能.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  NewState: 初始化触发是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能初始化触发生成
  *			@arg DISABLE: 失能初始化触发生成
  * @retval None
  */
void FTM_SetInitTriggerCmd(FTM_Type* FTMx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the generation of the channel trigger */
		FTMx->EXTTRIG |= FTM_EXTTRIG_INITTRIGEN_MASK;
	}
	else
	{
		/* Disable the generation of the channel trigger */		
		FTMx->EXTTRIG &= ~FTM_EXTTRIG_INITTRIGEN_MASK;
	}
}

/**
  * @brief 定义通道输出极性.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  PolarityValue: 设置POL寄存器的值.
  * @retval None
  */
void FTM_SetChannelsPolarity(FTM_Type* FTMx, uint8_t PolarityValue)
{
	/* Enable the channels polarity */	
	FTMx->POL = PolarityValue;
}

/**
  * @brief 定义单通道输出极性.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @param  FTM_Polarity: 输出极性
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNELPOLARITY_HIGH: 通道极性为高电平有效
  *			@arg FTM_CHANNELPOLARITY_LOW: 通道极性为低电平有效
  * @retval None
  */
void FTM_SetSingleChannelPolarity(FTM_Type* FTMx, uint8_t FTM_Channel, uint8_t FTM_Polarity)
{
	uint32_t polvalue;

	polvalue = ((uint32_t)1<<FTM_Channel);
	
	if (FTM_Polarity != FTM_CHANNELPOLARITY_HIGH)
	{
		/* The channel polarity is active low */
		FTMx->POL |= polvalue;
	}
	else
	{
		/* The channel polarity is active high */
		FTMx->POL &= ~polvalue;
	}
}	

/**
  * @brief 表征FAULTF中当j = 3, 2, 1, 0时的逻辑OR,当写0时清除,当写1时没有作用.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @retval 返回FAULTF中当j = 3, 2, 1, 0时的逻辑OR.
  */
FlagStatus FTM_GetFaultDetectLogicORFlag(const FTM_Type* FTMx)
{
	return ((FTMx->FMS & FTM_FMS_FAULTF_MASK) == FTM_FMS_FAULTF_MASK);
}

/**
  * @brief 通过硬件设置错误信号使能.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FaultDetectFlag: 故障检测标志.
  *		这个参数可以取下面的值:
  *			@arg FTM_FAULTDETECTION_FLAG0: 故障检测标志0
  *			@arg FTM_FAULTDETECTION_FLAG1: 故障检测标志1
  *			@arg FTM_FAULTDETECTION_FLAG2: 故障检测标志2
  *			@arg FTM_FAULTDETECTION_FLAG3: 故障检测标志3
  * @retval None
  */
FlagStatus FTM_GetFaultDetectFlag(const FTM_Type* FTMx, uint8_t FaultDetectFlag)
{
	return ((FTMx->FMS & ((uint32_t)1 << FaultDetectFlag))  == ((uint32_t)1 << FaultDetectFlag));
}

/**
  * @brief 当错误控制使能重置错误输入使能OR逻辑.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @retval None
  */
uint32_t FTM_GetFaultInLogicORValue(const FTM_Type* FTMx)
{
	return (FTMx->FMS & FTM_FMS_FAULTIN_MASK);
}

/**
  * @brief 清除FaultDetectLogicOR标志.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @retval None
  */
void FTM_ClrFaultDetectLogicORFlag(FTM_Type* FTMx)
{
	/* first read the reg, then write 0 to clear */
	if((FTMx->FMS & FTM_FMS_FAULTF_MASK) == FTM_FMS_FAULTF_MASK)
	{
		FTMx->FMS &= ~FTM_FMS_FAULTF_MASK;
	}
}

/**
  * @brief 清除错误检测标志.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FaultDetectFlag: 故障检测标志.
  *		这个参数可以取下面的值:
  *			@arg FTM_FAULTDETECTION_FLAG0: 故障检测标志0
  *			@arg FTM_FAULTDETECTION_FLAG1: 故障检测标志1
  *			@arg FTM_FAULTDETECTION_FLAG2: 故障检测标志2
  *			@arg FTM_FAULTDETECTION_FLAG3: 故障检测标志3
  * @retval None
  */
void FTM_ClrFaultDetectFlag(FTM_Type* FTMx, uint8_t FaultDetectFlag)
{
	/* first read the reg, then write 0 to clear */
	if((FTMx->FMS & ((uint32_t)1<<FaultDetectFlag)) != (uint32_t)0)
	{
		FTMx->FMS &= ~(((uint32_t)1 << FaultDetectFlag));
	}
}


/**
  * @brief  选择单通道输入滤值,当值为0时滤值无效.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_FilterChannel: FTM输入滤波通道
  *		这个参数可以取下面的值:
  *			@arg FTM_INPUTFILTER_CHANNEL0: 通道0输入滤波器
  *			@arg FTM_INPUTFILTER_CHANNEL1: 通道1输入滤波器
  *			@arg FTM_INPUTFILTER_CHANNEL2: 通道2输入滤波器
  *			@arg FTM_INPUTFILTER_CHANNEL3: 通道3输入滤波器
  * @param  FilterValue: 设置滤值0x0~0xF.
  * @retval None
  */
void FTM_SetChannelInFilter(FTM_Type* FTMx, uint8_t FTM_FilterChannel, uint32_t FilterValue)
{
	FTMx->FILTER &= ~((uint32_t)0xF << (FTM_FilterChannel << 2)); 
	/* Selects the filter value for the channel input. */
	FTMx->FILTER |= (FilterValue << (FTM_FilterChannel << 2)); 
}


/**
  * @brief  选择通道输入滤值.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  filter: 设置FILTER寄存器的值.
  * @retval None
  */
void FTM_SetInCapFilter(FTM_Type* FTMx, uint16_t filter)
{
	/* set the filter value */	
	FTMx->FILTER = filter;
}

/**
  * @brief  是否使能故障输入.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FaultInput: 指向FTM_fault_input_list数据.
  *		这个参数可以取下面的值:
  *			@arg FTM_FAULT_INPUT0: 故障输入0
  *			@arg FTM_FAULT_INPUT1: 故障输入1
  *			@arg FTM_FAULT_INPUT2: 故障输入2
  *         @arg FTM_FAULT_INPUT3: 故障输入3
  * @param  NewState: 故障输入是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能故障输入
  *			@arg DISABLE: 失能故障输入
  * @retval None
  */
void FTM_FaultPinCmd(FTM_Type* FTMx, uint8_t FaultInput, FunctionalState NewState)
{
	uint32_t tempvalue;
	
	tempvalue= ((uint32_t)1 << FaultInput);
	
	if (NewState != DISABLE)
	{
		/* Enable Fault input */
		FTMx->FLTCTRL |= tempvalue;
	}
	else
	{
		/* Disable Fault input */
		FTMx->FLTCTRL &= ~tempvalue;
	}
}


/**
  * @brief  是否使能滤值故障输入.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设   
  *			@arg FTM2: FTM2外设
  * @param  FaultFilter: 指向FTM_fault_input_filter_list数据.
  *		这个参数可以取下面的值:
  *			@arg FTM_FAULTINPUT_FILTER0: 故障输入0滤波器
  *			@arg FTM_FAULTINPUT_FILTER1: 故障输入1滤波器
  *			@arg FTM_FAULTINPUT_FILTER2: 故障输入2滤波器
  *         @arg FTM_FAULTINPUT_FILTER3: 故障输入3滤波器
  * @param  NewState: 故障输入滤波是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能故障输入滤波器
  *			@arg DISABLE: 失能故障输入滤波器
  * @retval None
  */
void FTM_FaultPinFilterCmd(FTM_Type* FTMx, uint8_t FaultFilter, FunctionalState NewState)
{
	uint32_t tempvalue;
	
	tempvalue= ((uint32_t)0x10 << FaultFilter);
	
	if (NewState != DISABLE)
	{
		/* Enable Fault input filter */
		FTMx->FLTCTRL |= tempvalue;
	}
	else
	{
		/* Disable Fault input filter */
		FTMx->FLTCTRL &= ~tempvalue;
	}
}


/**
  * @brief  选择滤值错误输入.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FilterValue:设置滤值 0x0~0xF.
  * @retval None
  */
void FTM_SetFaultInFilter(FTM_Type* FTMx, uint32_t FilterValue)
{
	FTMx->FLTCTRL &= ~FTM_FLTCTRL_FFVAL_MASK;
	
	/* Selects the filter value */        
	FTMx->FLTCTRL |= (FilterValue << FTM_FLTCTRL_FFVAL_SHIFT);
}


/**
  * @brief  配置FTM全局时钟.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  NewState: 外部全局时基是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能外部全局时基
  *			@arg DISABLE: 失能外部全局时基
  * @retval None
  */
void FTM_GTBEENCmd(FTM_Type* FTMx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable Use of an external global time base */
		FTMx->CONF |= FTM_CONF_GTBEEN_MASK;
	}
	else
	{
		/* Disable Use of an external global time base */
		FTMx->CONF &= ~FTM_CONF_GTBEEN_MASK;
	}	
}


/**
  * @brief  基于其它FTMs使能全局时钟.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  NewState: 全局时基信号生成是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 使能全局时基信号生成
  *			@arg DISABLE: 失能全局时基信号生成
  * @retval None
  */
void FTM_GTBEOUTCmd(FTM_Type* FTMx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable A global time base signal generation */
		FTMx->CONF |= FTM_CONF_GTBEOUT_MASK;
	}
	else
	{
		/* Disable A global time base signal generation */
		FTMx->CONF &= ~FTM_CONF_GTBEOUT_MASK;
	}	
}


/**
  * @brief  进入Debug模式.
  * @param  FTMx: 选择FTM外设.
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  DebugMode：DebugMode值 0~0x03.
  * @retval None
  */
void FTM_SetDebugModeBehavior(FTM_Type* FTMx, uint32_t DebugMode)
{
	FTMx->CONF &= ~FTM_CONF_BDMMODE_MASK;

	/* Set the Debug Mode */
	FTMx->CONF |= (DebugMode << FTM_CONF_BDMMODE_SHIFT);
}

/**
  * @brief  定义错误输入极性.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FaultInput: 指向FTM_fault_polarity_filter_list数据.
  *		这个参数可以取下面的值:
  *			@arg FTM_FAULTINPUT_FILTER0: 故障输入0
  *			@arg FTM_FAULTINPUT_FILTER1: 故障输入1
  *			@arg FTM_FAULTINPUT_FILTER2: 故障输入2
  *			@arg FTM_FAULTINPUT_FILTER3: 故障输入3
  * @param  polarity: 故障输入极性
  *		这个参数可以取下面的值:
  *			@arg FTM_FAULTINPOLARITY_HIGH: 故障输入极性为高电平有效
  *			@arg FTM_FAULTINPOLARITY_LOW: 故障输入极性为低电平有效
  * @retval None
  */
void FTM_SetFaultInPolarity(FTM_Type* FTMx, uint8_t FaultInput, uint8_t polarity)
{
	uint32_t polvalue;

	polvalue = ((uint32_t)1<<FaultInput);
	
	if (polarity != FTM_FAULTINPOLARITY_HIGH)
	{
		/* The fault input polarity is active low */
		FTMx->FLTPOL |= polvalue;
	}
	else
	{
		/* The fault input polarity is active high */
		FTMx->FLTPOL &= ~polvalue;
	}
}


/**
  * @brief  控制组合通道翻转.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_INVERT_PAIRCHANNEL0: 通道组0
  *			@arg FTM_INVERT_PAIRCHANNEL1: 通道组1
  *			@arg FTM_INVERT_PAIRCHANNEL2: 通道组2
  *			@arg FTM_INVERT_PAIRCHANNEL3: 通道组3
  * @param  NewState:组合通道翻转是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 组合通道翻转使能
*			@arg DISABLE: 组合通道翻转不使能
  * @retval None
  */
void FTM_PairChannelsInvertCmd(FTM_Type* FTMx, uint8_t channelpair, FunctionalState NewState)
{
	uint32_t tempvalue;

	tempvalue= ((uint32_t)1<<channelpair);
	
	if (NewState != DISABLE)
	{
		/* Enable Inverting */
		FTMx->INVCTRL |= tempvalue;
	}
	else
	{
		/* Disable Inverting */
		FTMx->INVCTRL &= ~tempvalue;
	}
}


/**
  * @brief  软件输出控制通道N是否使能.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @param  NewState:通道N软件输出控制是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 通道N软件输出控制使能
  *			@arg DISABLE: 通道N软件输出控制失能
  * @retval None
  */
void FTM_SWOutControlCmd(FTM_Type* FTMx, uint8_t FTM_Channel, FunctionalState NewState)
{
	uint32_t tempvalue;
	tempvalue= ((uint32_t)1<<FTM_Channel);
	
	if (NewState != DISABLE)
	{
		/* The channel output is affected */
		FTMx->SWOCTRL |= tempvalue;
	}
	else
	{
		/* The channel output is not affected */
		FTMx->SWOCTRL &= ~tempvalue;
	}
}

/**
  * @brief  设置软件输出控制通道N的值.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
  * @param  outvalue: 设置控制通道N的值.
  *		这个参数可以取下面的值:
  *			@arg FTM_SWCONTROL_OUT0: 软件输出控制强制0进入通道输出
  *			@arg FTM_SWCONTROL_OUT1: 软件输出控制强制1进入通道输出

  * @retval None
  */
void FTM_SetSWOutControlValue(FTM_Type* FTMx, uint8_t FTM_Channel, uint8_t outvalue)
{
	uint32_t tempvalue;

	tempvalue= ((uint32_t)0x100<<FTM_Channel);
	
	if (outvalue != FTM_SWCONTROL_OUT0)
	{
		/* The software output control forces 1 to the channel output */
		FTMx->SWOCTRL |= tempvalue;
	}
	else
	{
		/* The software output control forces 0 to the channel output */
		FTMx->SWOCTRL &= ~tempvalue;
	}
}


/**
  * @brief  是否包含通道比较进程.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  Matchchannel: 设置PWMLOAD寄存器 低8位的值. 
  * @retval None
  */
void FTM_SetLoadMatchChannels(FTM_Type* FTMx, uint32_t Matchchannel)
{
	FTMx->PWMLOAD &= ~(uint32_t)0xFF ;
	FTMx->PWMLOAD |= Matchchannel;
}

/**
  * @brief  是否包含单通道比较进程.
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FTM_Channel: 选择FTM通道.
  *		这个参数可以取下面的值:
  *			@arg FTM_CHANNEL0: FTMx通道0
  *			@arg FTM_CHANNEL1: FTMx通道1
  *			@arg FTM_CHANNEL2: FTMx通道2
  *			@arg FTM_CHANNEL3: FTMx通道3
  *			@arg FTM_CHANNEL4: FTMx通道4
  *			@arg FTM_CHANNEL5: FTMx通道5
  *			@arg FTM_CHANNEL6: FTMx通道6
  *			@arg FTM_CHANNEL7: FTMx通道7
* @param  include:是否包含单通道比较进程
  *		这个参数可以取下面的值:
*			@arg FTM_CHANNELMATCH_NOTINCLUDE:不包含单通道比较进程
  *			@arg FTM_CHANNELMATCH_INCLUDE：包含单通道比较进程
  * @retval None
  */
void FTM_SetLoadMatchChannel(FTM_Type* FTMx, uint8_t FTM_Channel, uint8_t include)
{
	uint32_t tempvalue;
	
	tempvalue= ((uint32_t)1<<FTM_Channel);
	
	if (include != FTM_CHANNELMATCH_NOTINCLUDE)
	{
		/* Include the channel in the matching process */
		FTMx->PWMLOAD |= tempvalue;
	}
	else
	{
		/* Do not include the channel in the matching process. */
		FTMx->PWMLOAD &= ~tempvalue;
	}
}

/**
  *	@brief  使能加载MOD, CNTIN,CV寄存器的值. 
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  NewState:FTMx加载是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 加载使能
  *			@arg DISABLE: 加载失能
  * @retval None
  */
void FTM_SetLoadCmd(FTM_Type* FTMx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable Loading updated */		
		FTMx->PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
	}
	else
	{
		/* Disable Loading updated */
		FTMx->PWMLOAD &= ~FTM_PWMLOAD_LDOK_MASK;
	}
}

/**
  *	@brief  使能PWM同步和中间加载
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  NewState:PWM同步和中间加载是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 同步和中间加载使能
  *			@arg DISABLE: 同步和中间加载失能
  * @retval None
  */
void FTM_SyncLoadEnable(FTM_Type* FTMx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{		
		FTMx->MODE |= FTM_MODE_SYNCLOADEN_MASK;
	}
	else
	{
		FTMx->MODE &= ~FTM_MODE_SYNCLOADEN_MASK;
	}
}


/**
  *	@brief  故障控制使能
  * @param  FTMx: 选择FTM外设.
  *		这个参数可以取下面的值:
  *			@arg FTM0: FTM0外设
  *			@arg FTM1: FTM1外设
  *			@arg FTM2: FTM2外设
  * @param  FaultControlChannel:故障控制通道选择
  *		这个参数可以取下面的值:
  *			@arg FaultControlChanne0: 通道(0)和(1)中的故障控制
  *			@arg FaultControlChannel: 通道(2)和(3)中的故障控制
  *			@arg FaultControlChanne2: 通道(4)和(5)中的故障控制
  *			@arg FaultControlChanne3: 通道(6)和(7)中的故障控制
  * @param  NewState:故障控制是否使能.
  *		这个参数可以取下面的值:
  *			@arg ENABLE: 故障控制使能
  *			@arg DISABLE: 故障控制失能
  * @retval None
  */
void FTM_FaultControlEnable(FTM_Type* FTMx, uint32_t FaultControlChannel,FunctionalState NewState)
{
	if (NewState != DISABLE)
	{		
		FTMx->COMBINE |= FaultControlChannel;
	}
	else
	{
		FTMx->COMBINE &= ~FaultControlChannel;
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
