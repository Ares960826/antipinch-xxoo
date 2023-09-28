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
  * @brief  д��������ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @retval None
  */
void FTM_WriteProtectEnable(FTM_Type* FTMx)
{
	FTMx->FMS |= FTM_FMS_WPEN_MASK;	
}

/**
  * @brief  д�������ܽ���.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @retval None
  */
void FTM_WriteProtectDisable(FTM_Type* FTMx)
{
	FTMx->MODE |= FTM_MODE_WPDIS_MASK;
}

/**
  * @brief  ����FTMx����Ĵ���ΪĬ��ֵ
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
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
  * @brief  FTMx����Ĵ�����ʼ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_InitStruct: ָ��FTM_InitTypeDef����.
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
  * @brief  FTMxָ��ͨ����Ե����PWM����.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @param  PWMEdgeSelect: ����ѡ��
  *		�����������Ϊ����ֵ:
  *			@arg FTM_PWM_HIGHTRUEPULSE: ƥ��ʱ�������
  *			@arg FTM_PWM_LOWTRUEPULSE: ƥ��ʱ��λ���
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
  * @brief  FTMxָ��ͨ�����Ķ���PWM����.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @param  PWMEdgeSelect: ����ѡ��
  *		�����������ȡ�����ֵ:
  *			@arg FTM_PWM_HIGHTRUEPULSE: ƥ��ʱ�������
  *			@arg FTM_PWM_LOWTRUEPULSE: ƥ��ʱ��λ���
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
  * @brief  FTMx���ģʽPWM����.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_CombinePWMStruct: ָ��FTM_CombinePWMTypeDef����.
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
  * @brief  FTMxPWM��ʼ��
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  PWMModeSelect: ѡ��pwmģʽ.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_PWMMODE_EDGEALLIGNED: ���ض���ģʽ
  *			@arg FTM_PWMMODE_CENTERALLIGNED: ����ģʽ����
  *			@arg FTM_PWMMODE_COMBINE: ���ģʽ
  * @param  PWMEdgeSelect: ����ѡ��
  *		�����������ȡ�����ֵ:
  *			@arg FTM_PWM_HIGHTRUEPULSE: ƥ��ʱ�������
  *			@arg FTM_PWM_LOWTRUEPULSE: ƥ��ʱ��λ���
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
  * @brief  FTMx���벶���ʼ��
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @param  CaptureMode: ѡ�񲶻����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_INPUTCAPTURE_RISINGEDGE: �����ز���
  *			@arg FTM_INPUTCAPTURE_FALLINGEDGE: �½��ز���
  *			@arg FTM_INPUTCAPTURE_BOTHEDGE: ˫���ز���
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
  * @brief  FTMx˫�ز����ʼ��
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_DualEdgeStruct: ָ��FTM_DualEdgeCaptureTypeDef����.
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
  * @brief  FTMx����Ƚϳ�ʼ��
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @param  CompareMode: ѡ��Ƚϱ���
  *		�����������ȡ�����ֵ:
  *			@arg FTM_OUTPUT_TOGGLE: ƥ��ʱ�л����
  *			@arg FTM_OUTPUT_CLEAR: ƥ��ʱ�������
  *			@arg FTM_OUTPUT_SET: ƥ��ʱ��λ���
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
  * @brief  ʹ��FTM����ж�.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  NewState:FTMx����ж��Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��FTMx����ж�
  *			@arg DISABLE: ʧ��FTMx����ж�
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
  * @brief ��ȡ�����־״̬.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @retval ��ǰ״̬(TRUE or FALSE) 
  */
FlagStatus FTM_GetOverFlowFlag(const FTM_Type* FTMx)
{
  return ((FTMx->SC & FTM_SC_TOF_MASK) == FTM_SC_TOF_MASK);
}


/**
  * @brief  ʹ��FTMͨ������CV �Ĵ���ͬ��.
  * @param  FTMx: ѡ��FTM����.
  *           �����������ȡ�����ֵ:
  *                  @arg FTM0: FTM0����
  *                  @arg FTM1: FTM1����
  *                  @arg FTM2: FTM2����
  * @param  FTM_ ChannelPair: ѡ��FTMͨ����.
  *           �����������ȡ�����ֵ:
  *                  @arg FTM_CHANNELPAIR0: FTMxͨ����0
  *                  @arg FTM_CHANNELPAIR1: FTMxͨ����1
  *                  @arg FTM_CHANNELPAIR2: FTMxͨ����2
  *                  @arg FTM_CHANNELPAIR3: FTMxͨ����3
  * @param  NewState:�Ƿ�ʹ��ͨ������CV�Ĵ���ͬ��.
  *           �����������ȡ�����ֵ:
  *                  @arg ENABLE: ʹ��CV�Ĵ���ͬ��
  *                  @arg DISABLE: ʧ��CV�Ĵ���ͬ��
 
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
  * @brief  ���FTMx�����־.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
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
  * @brief  ��ȡCNTֵ.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @retval ����CNT��ֵ.
  */
uint16_t FTM_GetCountValue(const FTM_Type* FTMx)
{
	return (uint16_t)FTMx->CNT;
}

/**
  * @brief  ����MODֵ.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  ModValue: �趨MODֵ.
  * @retval None
  */
void FTM_SetModValue(FTM_Type* FTMx, uint16_t ModValue)
{
	FTMx->CNT = 0;
	FTMx->MOD = ModValue;
}

/**
  * @brief  ����CNTINֵ.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @retval None
  */
void FTM_SetCountInitValue(FTM_Type* FTMx, uint16_t InitialValue)
{
	FTMx->CNTIN = InitialValue;
}

/**
  * @brief  FTMxͨ���ж�ʹ��
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @param  NewState: FTMx��Ӧͨ���ж��Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��FTMxͨ���ж�
  *			@arg DISABLE: ʧ��FTMxͨ���ж�
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
  * @brief  FTM��ȡͨ����־
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @retval ����ͨ����־.
  */
FlagStatus FTM_GetChannelFlag(const FTM_Type* FTMx, uint8_t FTM_Channel)
{
  return ((FTMx->CONTROLS[FTM_Channel].CnSC & FTM_CnSC_CHF_MASK) == FTM_CnSC_CHF_MASK);
}

/**
  * @brief  FTM���ͨ����־
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @retval None
  */
void FTM_ClrChannelFlag(FTM_Type* FTMx, uint8_t FTM_Channel)
{
	//Dummy read while CHF is set
	(void) FTMx->CONTROLS[FTM_Channel].CnSC; 
	FTMx->CONTROLS[FTM_Channel].CnSC &= ~FTM_CnSC_CHF_MASK;
}

/**
  * @brief  FTM����ͨ��ֵ
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @param  ChannelValue: �趨ͨ��ֵ.
  * @retval None
  */
void FTM_SetChannelValue(FTM_Type* FTMx, uint8_t FTM_Channel, uint16_t ChannelValue)
{
	FTMx->CONTROLS[FTM_Channel].CnV = ChannelValue;
}
/**
  * @brief  FTM��ȡͨ��ֵ
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @retval ͨ��ֵ
  */
uint16_t FTM_GetChannelValue(const FTM_Type* FTMx, uint8_t FTM_Channel )
{
	return (uint16_t)FTMx->CONTROLS[FTM_Channel].CnV;
}
/**
  * @brief ��ȡ����ͨ�������־.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @retval ��������ͨ����־.
  */
uint32_t FTM_GetStatusRegFlag(const FTM_Type* FTMx)
{
  return (FTMx->STATUS & 0xFFu);
}

/**
  * @brief �������ͨ�������־.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
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
  * @brief �õ�ָ��ͨ�������־.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @retval ��������ͨ����־.
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
  * @brief  ���ָ��ͨ�������־.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
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
  * @brief ʹ�ܴ����ж�.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  NewState: �����ж��Ƿ�ʹ��
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��FTMx�����ж�
  *			@arg DISABLE: ʧ��FTMx�����ж�
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
  * @brief ����FTM�������ģʽ.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_FaultControlModeDef: ѡ��������ģʽ.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_ALLDISABLE: ����ͨ�����ù���
  *			@arg FTM_EVENENABLE_MANUALCLEAR: ż��ͨ��ʹ�ܹ��Ͽ��ƣ��ֶ���������.
  *			@arg FTM_ALLENABLE_MANUALCLEAR: ����ͨ��ʹ�ܹ��Ͽ��ƣ��ֶ���������.
  *			@arg FTM_ALLENABLE_AUTOCLEAR: ����ͨ��ʹ�ܹ��Ͽ��ƣ��Զ���������.
  * @retval None
  */
void FTM_SetFaultControlMode(FTM_Type* FTMx, FTM_FaultControlModeDef FTM_FaultControlMode)
{	
	FTMx->MODE &= ~FTM_MODE_FAULTM_MASK;
	
	FTMx->MODE |= ((uint32_t)FTM_FaultControlMode << FTM_MODE_FAULTM_SHIFT);
}

/**
  * @brief ʹ�ܲ������ģʽ.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  NewState: ��������Ƿ�ʹ��
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��FTMx�������
  *			@arg DISABLE: ʧ��FTMx�������
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
  * @brief ѡ��PWMͬ���������.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  NewState: PWMͬ����������Ƿ�ʹ��
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��FTMx��PWMͬ���������
  *			@arg DISABLE: ʧ��FTMx��PWMͬ���������
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
  * @brief ѡ��PWMͬ��Ӳ������.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  TriggerN: ͬ�������ź�ѡ��
  *		�����������ȡ�����ֵ:
  *			@arg FTM_SYNC_TRIGGER_TRIGGER0: Tigger0 synchronization
  *			@arg FTM_SYNC_TRIGGER_TRIGGER1: Tigger1 synchronization
  *			@arg FTM_SYNC_TRIGGER_TRIGGER2: Tigger2 synchronization
  * @param  NewState: PWMͬ��Ӳ�������Ƿ�ʹ��
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��FTMx��PWMͬ��Ӳ������
  *			@arg DISABLE: ʧ��FTMx��PWMͬ��Ӳ������
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
  * @brief ѡ��SWOCTRL/INVCTRL/OUTMASK/MOD, CNTIN��CV/CNTͬ��.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  TriggerType: ����ģʽѡ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_SYNCONF_SWTRIGGER: �������ģʽ
  *			@arg FTM_SYNCONF_HWTRIGGER: Ӳ������ģʽ
  * @param  RegType: �Ĵ���ͬ������.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_SYNCONF_CNTREG: CNT�Ĵ���ͬ��
  *			@arg FTM_SYNCONF_MODCNTINCVREG: MOD��CNTIN��CV�Ĵ���ͬ��
  *			@arg FTM_SYNCONF_OUTMASKREG: OUTMASK �Ĵ���ͬ��
  *			@arg FTM_SYNCONF_INVCTRLREG: INVCTRL�Ĵ���ͬ��
  *			@arg FTM_SYNCONF_SWOCTRLREG: SWOCTRL�Ĵ���ͬ��
  * @param  NewState: ͬ���Ƿ�ʹ��.
  *			@arg ENABLE: ʹ��FTMx��PWMͬ��Ӳ������
  *			@arg DISABLE: ʧ��FTMx��PWMͬ��Ӳ������
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
  * @brief  OUTMASK�Ĵ���ͬ��
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  update:ͬ��ģʽѡ��
  *		�����������ȡ�����ֵ:
  *			@arg FTM_UPDATE_RISINGCLK: �Ĵ���������ϵͳ�������ؽ���ͬ������
  *			@arg FTM_UPDATE_PWMSYNC: �Ĵ�����ͨ��PWMͬ������
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
  * @brief CNTIN�Ĵ���ͬ��
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  update:ͬ������ģʽѡ��
  *		�����������ȡ�����ֵ:
  *			@arg FTM_UPDATE_RISINGCLK: �Ĵ���������ϵͳ�������ؽ���ͬ������
  *			@arg FTM_UPDATE_PWMSYNC: �Ĵ�����ͨ��PWMͬ������
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
  * @brief INVCTRL�Ĵ���ͬ��.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  update:ͬ������ģʽѡ��
  *		�����������ȡ�����ֵ:
  *			@arg FTM_UPDATE_RISINGCLK: �Ĵ���������ϵͳ�������ؽ���ͬ������
  *			@arg FTM_UPDATE_PWMSYNC: �Ĵ�����ͨ��PWMͬ������
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
  * @brief SWOCTRL�Ĵ���ͬ��.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  update:ͬ������ģʽѡ��
  *		�����������ȡ�����ֵ:
  *			@arg FTM_UPDATE_RISINGCLK: �Ĵ���������ϵͳ�������ؽ���ͬ������
  *			@arg FTM_UPDATE_PWMSYNC: �Ĵ�����ͨ��PWMͬ������
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
  * @brief ѡ��PWMͬ��ģʽ.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  mode:ģʽѡ��
  *		�����������ȡ�����ֵ:
  *			@arg FTM_SYNCMODE_LEGACY: ѡ��ͳPWMͬ��
  *			@arg FTM_SYNCMODE_ENHANCED: ѡ����ǿPWMͬ��
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
  * @brief FTM���ͬ����������
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  type:ģʽѡ��
  *		�����������ȡ�����ֵ:
	*			@arg FTM_SOFTWARE_SYN_CNT: �����������FTM������ͬ��
	*			@arg FTM_SOFTWARE_SYN_MOD_CNTIN_CV: �����������MOD��CNTIN��CV�Ĵ���ͬ��
	*			@arg FTM_SOFTWARE_SYN_OUTMASK: ������������������ͬ��
	*			@arg FTM_SOFTWARE_SYN_INVCTRL: ���������������ͬ��
	*			@arg FTM_SOFTWARE_SYN_OUTCTRL: ������������������ͬ��
  * @param  NewState: ���ͬ������ģʽ�Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��
  *			@arg DISABLE: ʧ��
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
  * @brief FTMӲ��ͬ����������
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  type:ģʽѡ��
  *		�����������ȡ�����ֵ:
	*			@arg FTM_HARDWARE_SYN_CNT: Ӳ����������FTM������ͬ��
	*			@arg FTM_HARDWARE_SYN_MOD_CNTIN_CV: Ӳ����������MOD��CNTIN��CV�Ĵ���ͬ��
	*			@arg FTM_HARDWARE_SYN_OUTMASK: Ӳ�����������������ͬ��
	*			@arg FTM_HARDWARE_SYN_INVCTRL: Ӳ��������������ͬ��
	*			@arg FTM_HARDWARE_SYN_OUTCTRL: Ӳ�����������������ͬ��
  * @param  NewState: Ӳ��ͬ������ģʽ�Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: �����ص�ʹ��
  *			@arg DISABLE: �����ص�ʧ��
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
  * @brief ѡ��PWMͬ��ģʽ.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  mode:ģʽѡ��
  *		�����������ȡ�����ֵ:
  *			@arg FTM_PWMSYNC_NORESTRICT: ������MOD,CnV,OUTMASK��FTM������ͬ���������Ӳ������
  *			@arg FTM_PWMSYNC_SWANDHW: �������ֻ������MOD��CnVͬ����Ӳ������ֻ������OUTMASK��FTM������ͬ��
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
  * @brief ѡ��Ӳ������ģʽ.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  mode:ģʽѡ��
  *		�����������ȡ�����ֵ:
  *			@arg FTM_HWTRIGMODE_CLEAR: ��鵽Ӳ������ʱ��FTM����TRIGλ
  *			@arg FTM_HWTRIGMODE_UNCLEAR: ��鵽Ӳ������ʱ��FTM������TRIGλ
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
  * @brief ѡ��PWMͬ���������.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  NewState: �����ص��Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: �����ص�ʹ��
  *			@arg DISABLE: �����ص�ʧ��
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
  * @brief ѡ��PWMͬ����С����.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  NewState: ��С���ص��Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ��С���ص�ʹ��
  *			@arg DISABLE: ��С���ص�ʧ��
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
  * @brief FTM������ͬ������Ԥ��.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  mode: ���³�ʼ������
  *		�����������ȡ�����ֵ:
  *			@arg FTM_REINIT_NORMALLY: ��������
  *			@arg FTM_REINIT_UPDATED: ����⵽�ض��Ĵ���ʱ��FTM�����������ʼֵ����
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
  * @brief ѡ���ʼ������ʱͨ�����ֵ.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  initialvalue:��ʼ��ͨ�����
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
  * @brief ָ��ͨ��ѡ���ʼ������ʱͨ�����ֵ.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @param  initialvalue:ָ��ͨ����ʼ�����
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
  * @brief ����ͨ������Ƿ�ɼ���.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  outmask: ����outmask�Ĵ�����ֵ.
  * @retval None
  */
void FTM_SetOutMask(FTM_Type* FTMx, uint8_t outmask)
{
	/* Enable the Output Mask function */	
	FTMx->OUTMASK = outmask;
}

/**
  * @brief ����ָ��ͨ������Ƿ�ɼ���.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @param  NewState: ͨ����������Ƿ�ʹ��
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ͨ���������
  *			@arg DISABLE: ͨ�����δ����
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
  * @brief ѡ������Ԥ�����������ֵ.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  PrescalerValue: ����ʱ��Ԥ��Ƶֵ
  *		�����������ȡ�����ֵ:
  *			@arg FTM_DEADTIME_DTPS_DIV1: FTMxʱ��1��Ƶ
  *			@arg FTM_DEADTIME_DTPS_DIV4: FTMxʱ��4��Ƶ
  *			@arg FTM_DEADTIME_DTPS_DIV16: FTMxʱ��16��Ƶ
  * @param  DeadtimeValue: ����ʱ��(0x00~0x3F)
  * @retval None
  */
void FTM_PWMDeadtimeSet(FTM_Type* FTMx, uint32_t PrescalerValue, uint32_t DeadtimeValue)
{
	FTM0->DEADTIME = 0;
	/* set the deadtime */
	FTMx->DEADTIME = ((DeadtimeValue & (uint32_t)0x3F) | ((PrescalerValue & (uint32_t)0x3) << FTM_DEADTIME_DTPS_SHIFT));      
}

/**
  * @brief  ��ȡͨ��������־.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @return ����ͨ��������־.
  */
FlagStatus FTM_GetExternalTriggerFlag(const FTM_Type* FTMx)
{
	return ((FTMx->EXTTRIG & FTM_EXTTRIG_TRIGF_MASK) == FTM_EXTTRIG_TRIGF_MASK);
}

/**
  * @brief ���ͨ��������־.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
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
  * @brief �Ƿ�ʹ��ͨ��N����.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  * @param  NewState: ͨ��N�����Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��ͨ��N����
  *			@arg DISABLE: ʹ��ͨ��N����
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
  * @brief ��FTM������CNTIN�Ĵ���ֵ��ͬʱ����ʹ��.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  NewState: ��ʼ�������Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ�ܳ�ʼ����������
  *			@arg DISABLE: ʧ�ܳ�ʼ����������
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
  * @brief ����ͨ���������.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  PolarityValue: ����POL�Ĵ�����ֵ.
  * @retval None
  */
void FTM_SetChannelsPolarity(FTM_Type* FTMx, uint8_t PolarityValue)
{
	/* Enable the channels polarity */	
	FTMx->POL = PolarityValue;
}

/**
  * @brief ���嵥ͨ���������.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @param  FTM_Polarity: �������
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNELPOLARITY_HIGH: ͨ������Ϊ�ߵ�ƽ��Ч
  *			@arg FTM_CHANNELPOLARITY_LOW: ͨ������Ϊ�͵�ƽ��Ч
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
  * @brief ����FAULTF�е�j = 3, 2, 1, 0ʱ���߼�OR,��д0ʱ���,��д1ʱû������.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @retval ����FAULTF�е�j = 3, 2, 1, 0ʱ���߼�OR.
  */
FlagStatus FTM_GetFaultDetectLogicORFlag(const FTM_Type* FTMx)
{
	return ((FTMx->FMS & FTM_FMS_FAULTF_MASK) == FTM_FMS_FAULTF_MASK);
}

/**
  * @brief ͨ��Ӳ�����ô����ź�ʹ��.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FaultDetectFlag: ���ϼ���־.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_FAULTDETECTION_FLAG0: ���ϼ���־0
  *			@arg FTM_FAULTDETECTION_FLAG1: ���ϼ���־1
  *			@arg FTM_FAULTDETECTION_FLAG2: ���ϼ���־2
  *			@arg FTM_FAULTDETECTION_FLAG3: ���ϼ���־3
  * @retval None
  */
FlagStatus FTM_GetFaultDetectFlag(const FTM_Type* FTMx, uint8_t FaultDetectFlag)
{
	return ((FTMx->FMS & ((uint32_t)1 << FaultDetectFlag))  == ((uint32_t)1 << FaultDetectFlag));
}

/**
  * @brief ���������ʹ�����ô�������ʹ��OR�߼�.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @retval None
  */
uint32_t FTM_GetFaultInLogicORValue(const FTM_Type* FTMx)
{
	return (FTMx->FMS & FTM_FMS_FAULTIN_MASK);
}

/**
  * @brief ���FaultDetectLogicOR��־.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
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
  * @brief ����������־.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FaultDetectFlag: ���ϼ���־.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_FAULTDETECTION_FLAG0: ���ϼ���־0
  *			@arg FTM_FAULTDETECTION_FLAG1: ���ϼ���־1
  *			@arg FTM_FAULTDETECTION_FLAG2: ���ϼ���־2
  *			@arg FTM_FAULTDETECTION_FLAG3: ���ϼ���־3
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
  * @brief  ѡ��ͨ��������ֵ,��ֵΪ0ʱ��ֵ��Ч.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_FilterChannel: FTM�����˲�ͨ��
  *		�����������ȡ�����ֵ:
  *			@arg FTM_INPUTFILTER_CHANNEL0: ͨ��0�����˲���
  *			@arg FTM_INPUTFILTER_CHANNEL1: ͨ��1�����˲���
  *			@arg FTM_INPUTFILTER_CHANNEL2: ͨ��2�����˲���
  *			@arg FTM_INPUTFILTER_CHANNEL3: ͨ��3�����˲���
  * @param  FilterValue: ������ֵ0x0~0xF.
  * @retval None
  */
void FTM_SetChannelInFilter(FTM_Type* FTMx, uint8_t FTM_FilterChannel, uint32_t FilterValue)
{
	FTMx->FILTER &= ~((uint32_t)0xF << (FTM_FilterChannel << 2)); 
	/* Selects the filter value for the channel input. */
	FTMx->FILTER |= (FilterValue << (FTM_FilterChannel << 2)); 
}


/**
  * @brief  ѡ��ͨ��������ֵ.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  filter: ����FILTER�Ĵ�����ֵ.
  * @retval None
  */
void FTM_SetInCapFilter(FTM_Type* FTMx, uint16_t filter)
{
	/* set the filter value */	
	FTMx->FILTER = filter;
}

/**
  * @brief  �Ƿ�ʹ�ܹ�������.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FaultInput: ָ��FTM_fault_input_list����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_FAULT_INPUT0: ��������0
  *			@arg FTM_FAULT_INPUT1: ��������1
  *			@arg FTM_FAULT_INPUT2: ��������2
  *         @arg FTM_FAULT_INPUT3: ��������3
  * @param  NewState: ���������Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ�ܹ�������
  *			@arg DISABLE: ʧ�ܹ�������
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
  * @brief  �Ƿ�ʹ����ֵ��������.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����   
  *			@arg FTM2: FTM2����
  * @param  FaultFilter: ָ��FTM_fault_input_filter_list����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_FAULTINPUT_FILTER0: ��������0�˲���
  *			@arg FTM_FAULTINPUT_FILTER1: ��������1�˲���
  *			@arg FTM_FAULTINPUT_FILTER2: ��������2�˲���
  *         @arg FTM_FAULTINPUT_FILTER3: ��������3�˲���
  * @param  NewState: ���������˲��Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ�ܹ��������˲���
  *			@arg DISABLE: ʧ�ܹ��������˲���
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
  * @brief  ѡ����ֵ��������.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FilterValue:������ֵ 0x0~0xF.
  * @retval None
  */
void FTM_SetFaultInFilter(FTM_Type* FTMx, uint32_t FilterValue)
{
	FTMx->FLTCTRL &= ~FTM_FLTCTRL_FFVAL_MASK;
	
	/* Selects the filter value */        
	FTMx->FLTCTRL |= (FilterValue << FTM_FLTCTRL_FFVAL_SHIFT);
}


/**
  * @brief  ����FTMȫ��ʱ��.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  NewState: �ⲿȫ��ʱ���Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ���ⲿȫ��ʱ��
  *			@arg DISABLE: ʧ���ⲿȫ��ʱ��
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
  * @brief  ��������FTMsʹ��ȫ��ʱ��.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  NewState: ȫ��ʱ���ź������Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ʹ��ȫ��ʱ���ź�����
  *			@arg DISABLE: ʧ��ȫ��ʱ���ź�����
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
  * @brief  ����Debugģʽ.
  * @param  FTMx: ѡ��FTM����.
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  DebugMode��DebugModeֵ 0~0x03.
  * @retval None
  */
void FTM_SetDebugModeBehavior(FTM_Type* FTMx, uint32_t DebugMode)
{
	FTMx->CONF &= ~FTM_CONF_BDMMODE_MASK;

	/* Set the Debug Mode */
	FTMx->CONF |= (DebugMode << FTM_CONF_BDMMODE_SHIFT);
}

/**
  * @brief  ����������뼫��.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FaultInput: ָ��FTM_fault_polarity_filter_list����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_FAULTINPUT_FILTER0: ��������0
  *			@arg FTM_FAULTINPUT_FILTER1: ��������1
  *			@arg FTM_FAULTINPUT_FILTER2: ��������2
  *			@arg FTM_FAULTINPUT_FILTER3: ��������3
  * @param  polarity: �������뼫��
  *		�����������ȡ�����ֵ:
  *			@arg FTM_FAULTINPOLARITY_HIGH: �������뼫��Ϊ�ߵ�ƽ��Ч
  *			@arg FTM_FAULTINPOLARITY_LOW: �������뼫��Ϊ�͵�ƽ��Ч
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
  * @brief  �������ͨ����ת.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_INVERT_PAIRCHANNEL0: ͨ����0
  *			@arg FTM_INVERT_PAIRCHANNEL1: ͨ����1
  *			@arg FTM_INVERT_PAIRCHANNEL2: ͨ����2
  *			@arg FTM_INVERT_PAIRCHANNEL3: ͨ����3
  * @param  NewState:���ͨ����ת�Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ���ͨ����תʹ��
*			@arg DISABLE: ���ͨ����ת��ʹ��
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
  * @brief  ����������ͨ��N�Ƿ�ʹ��.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @param  NewState:ͨ��N�����������Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ͨ��N����������ʹ��
  *			@arg DISABLE: ͨ��N����������ʧ��
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
  * @brief  ��������������ͨ��N��ֵ.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
  * @param  outvalue: ���ÿ���ͨ��N��ֵ.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_SWCONTROL_OUT0: ����������ǿ��0����ͨ�����
  *			@arg FTM_SWCONTROL_OUT1: ����������ǿ��1����ͨ�����

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
  * @brief  �Ƿ����ͨ���ȽϽ���.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  Matchchannel: ����PWMLOAD�Ĵ��� ��8λ��ֵ. 
  * @retval None
  */
void FTM_SetLoadMatchChannels(FTM_Type* FTMx, uint32_t Matchchannel)
{
	FTMx->PWMLOAD &= ~(uint32_t)0xFF ;
	FTMx->PWMLOAD |= Matchchannel;
}

/**
  * @brief  �Ƿ������ͨ���ȽϽ���.
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FTM_Channel: ѡ��FTMͨ��.
  *		�����������ȡ�����ֵ:
  *			@arg FTM_CHANNEL0: FTMxͨ��0
  *			@arg FTM_CHANNEL1: FTMxͨ��1
  *			@arg FTM_CHANNEL2: FTMxͨ��2
  *			@arg FTM_CHANNEL3: FTMxͨ��3
  *			@arg FTM_CHANNEL4: FTMxͨ��4
  *			@arg FTM_CHANNEL5: FTMxͨ��5
  *			@arg FTM_CHANNEL6: FTMxͨ��6
  *			@arg FTM_CHANNEL7: FTMxͨ��7
* @param  include:�Ƿ������ͨ���ȽϽ���
  *		�����������ȡ�����ֵ:
*			@arg FTM_CHANNELMATCH_NOTINCLUDE:��������ͨ���ȽϽ���
  *			@arg FTM_CHANNELMATCH_INCLUDE��������ͨ���ȽϽ���
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
  *	@brief  ʹ�ܼ���MOD, CNTIN,CV�Ĵ�����ֵ. 
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  NewState:FTMx�����Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ����ʹ��
  *			@arg DISABLE: ����ʧ��
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
  *	@brief  ʹ��PWMͬ�����м����
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  NewState:PWMͬ�����м�����Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ͬ�����м����ʹ��
  *			@arg DISABLE: ͬ�����м����ʧ��
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
  *	@brief  ���Ͽ���ʹ��
  * @param  FTMx: ѡ��FTM����.
  *		�����������ȡ�����ֵ:
  *			@arg FTM0: FTM0����
  *			@arg FTM1: FTM1����
  *			@arg FTM2: FTM2����
  * @param  FaultControlChannel:���Ͽ���ͨ��ѡ��
  *		�����������ȡ�����ֵ:
  *			@arg FaultControlChanne0: ͨ��(0)��(1)�еĹ��Ͽ���
  *			@arg FaultControlChannel: ͨ��(2)��(3)�еĹ��Ͽ���
  *			@arg FaultControlChanne2: ͨ��(4)��(5)�еĹ��Ͽ���
  *			@arg FaultControlChanne3: ͨ��(6)��(7)�еĹ��Ͽ���
  * @param  NewState:���Ͽ����Ƿ�ʹ��.
  *		�����������ȡ�����ֵ:
  *			@arg ENABLE: ���Ͽ���ʹ��
  *			@arg DISABLE: ���Ͽ���ʧ��
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
