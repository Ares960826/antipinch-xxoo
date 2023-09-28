/**
  ******************************************************************************
  * @file     xl_port.c
  * @author   Kirk ,xu.wang
  * @version  4.5.2
  * @date     Fri Mar 26 17:29:12 2021
  * @brief    This file provide function about PORT firmware program 
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
#include "xl_port.h"
	
/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup PORT PORT Module
  * @brief PORT Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PORT_Private_Functions
  * @{
  */ 

/**
  * @brief PORT默认初始化
  * @param  None.
  * @retval None.
  */ 
void PORT_DeInit(void)
{
	/* Deinitializes to default reset values */
	PORT->IOFLT0 = 0x00C00000;
	PORT->IOFLT1 = 0x00000000;
	PORT->PUE0 = 	 0x00100000;
	PORT->PUE1 = 	 0x00000000;
	PORT->PUE2 =	 0x00000000;
	PORT->HDRVE =  0x00000000;
}

/**
  * @brief 设置输入引脚的滤波器
  * @param IOflt0ConfigPtr: port_ioflt0_config 类型的指针，包含了PORT IOFLT0 外设的配置信息
  * @retval None.
  */ 
void PORT_IOFLT0Config(const port_ioflt0_config *IOflt0ConfigPtr)
{										 
	PORT->IOFLT0 = (uint32_t)(IOflt0ConfigPtr->iofltdiv3 | IOflt0ConfigPtr->iofltdiv2 | \
							  IOflt0ConfigPtr->iofltdiv1 | IOflt0ConfigPtr->iofltnmi | \
							  IOflt0ConfigPtr->iofltkbi1 | IOflt0ConfigPtr->iofltkbi0 | \
							  IOflt0ConfigPtr->iofltrst | IOflt0ConfigPtr->iofltpth | \
							  IOflt0ConfigPtr->iofltptg | IOflt0ConfigPtr->iofltptf | \
							  IOflt0ConfigPtr->iofltpte | IOflt0ConfigPtr->iofltptd | \
							  IOflt0ConfigPtr->iofltptc | IOflt0ConfigPtr->iofltptb | \
							  IOflt0ConfigPtr->iofltpta);
}
	
/**
  * @brief 设置输入引脚的滤波器
  * @param IOflt1ConfigPtr: port_ioflt1_config 类型的指针，包含PORT IOFLT1 外设的设置信息
  * @retval None.
  */ 
void PORT_IOFLT1Config(const port_ioflt1_config *IOflt1ConfigPtr)
{
	uint16_t tmpreg;

	/*---------------------------- PORT IOFLT1 Configuration ------------------------*/	
	/* get the present value in IOFLT1 Register. */
	tmpreg = (uint16_t)PORT->IOFLT1 ;
	/* Clear the bits in IOFLT1. */
	tmpreg &= ~(uint16_t)(PORT_IOFLT1_FLTI_MASK | PORT_IOFLT1_FLTIRQ_MASK| PORT_IOFLT1_FLTFTM0_MASK | \
					  	  PORT_IOFLT1_FLTFTM1_MASK | PORT_IOFLT1_FLTPWT_MASK | \
						  PORT_IOFLT1_FLTI2C0_MASK | PORT_IOFLT1_FLTI2C1_MASK);
	/* Configure the bits. */
	tmpreg |= (IOflt1ConfigPtr->ioflti2c1 | IOflt1ConfigPtr->ioflti2c0 | \
			   IOflt1ConfigPtr->iofltpwt  | IOflt1ConfigPtr->iofltftm1 | \
			   IOflt1ConfigPtr->iofltftm0 | IOflt1ConfigPtr->iofltirq | \
			   IOflt1ConfigPtr->iofltpti);
	/* data write to IOFLT1 register. */
	PORT->IOFLT1 = tmpreg ;
}


/**
  * @brief 	PORT滤波器分组3时钟选择
  * @param clk: 时钟选择参数
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTDIV3SetLPOCLK: LPO时钟不分频
  *			@arg Port_FLTDIV3SetLPOCLKDiv2: LPO时钟2分频
  *			@arg Port_FLTDIV3SetLPOCLKDiv4: LPO时钟4分频
  *			@arg Port_FLTDIV3SetLPOCLKDiv8: LPO时钟8分频
  *			@arg Port_FLTDIV3SetLPOCLKDiv16: LPO时钟16分频
  *			@arg Port_FLTDIV3SetLPOCLKDiv32: LPO时钟32分频
  *			@arg Port_FLTDIV3SetLPOCLKDiv64: LPO时钟64分频
  *			@arg Port_FLTDIV3SetLPOCLKDiv128: LPO时钟128分频
  * @retval None.
  */ 
void PORT_FLTDIV3ConSet(uint32_t clk)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTDIV3_MASK;
	PORT->IOFLT0 |= clk;
}

/**
  * @brief 	PORT滤波器分组2时钟选择
  * @param clk: 时钟选择参数
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTDIV2SetBUSCLKDiv32: 总线时钟32分频
  * 		@arg Port_FLTDIV2SetBUSCLKDiv64: 总线时钟64分频
  * 		@arg Port_FLTDIV2SetBUSCLKDiv128: 总线时钟128分频
  * 		@arg Port_FLTDIV2SetBUSCLKDiv256: 总线时钟256分频
  * 		@arg Port_FLTDIV2SetBUSCLKDiv512: 总线时钟512分频
  * 		@arg Port_FLTDIV2SetBUSCLKDiv1024: 总线时钟1024分频
  * 		@arg Port_FLTDIV2SetBUSCLKDiv2048: 总线时钟2048分频
  * 		@arg Port_FLTDIV2SetBUSCLKDiv4096: 总线时钟4096分频
  * @retval None.
  */ 
void PORT_FLTDIV2Set(uint32_t clk)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTDIV2_MASK;
	PORT->IOFLT0 |= clk;
}

/**
  * @brief 	PORT滤波器分组1时钟选择
  * @param clk: 时钟选择参数
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTDIV1SetBUSCLKDiv2: 总线时钟2分频
  * 		@arg Port_FLTDIV1SetBUSCLKDiv4: 总线时钟4分频
  * 		@arg Port_FLTDIV1SetBUSCLKDiv8: 总线时钟8分频
  * 		@arg Port_FLTDIV1SetBUSCLKDiv16: 总线时钟16分频
  * @retval None.
  */ 
void PORT_FLTDIV1Set(uint32_t clk)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTDIV1_MASK;
	PORT->IOFLT0 |= clk;
}	

/**
  * @brief 	NMI输入滤波器选择
  * @param NMIFilter: NMI滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTNMINoFilter: 无滤波器
  * 		@arg Port_FLTNMIFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTNMIFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTNMIFLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTNMISET(uint32_t NMIFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTNMI_MASK;
	PORT->IOFLT0 |= NMIFilter;
}

/**
  * @brief 	KBI1输入滤波器选择
  * @param KBI1Filter: KBI1滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTKBI1NoFilter: 无滤波器
  * 		@arg Port_FLTKBI1FLTDIV1: 滤波器分组1
  * 		@arg Port_FLTKBI1FLTDIV2: 滤波器分组2
  * 		@arg Port_FLTKBI1FLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTKBI1SET(uint32_t KBI1Filter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTKBI1_MASK;
	PORT->IOFLT0 |= KBI1Filter;
}

/**
  * @brief 	KBI0输入滤波器选择
  * @param KBI0Filter: KBI0滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTKBI0NoFilter: 无滤波器
  * 		@arg Port_FLTKBI0FLTDIV1: 滤波器分组1
  * 		@arg Port_FLTKBI0FLTDIV2: 滤波器分组2
  * 		@arg Port_FLTKBI0FLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTKBI0SET(uint32_t KBI0Filter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTKBI0_MASK;
	PORT->IOFLT0 |= KBI0Filter;
}

/**
  * @brief 	Reset输入滤波器选择
  * @param RSTFilter: RESET滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTRSTNoFilter: 无滤波器
  * 		@arg Port_FLTRSTFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTRSTFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTRSTFLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTRSTSET(uint32_t RSTFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTRST_MASK;
	PORT->IOFLT0 |= RSTFilter;
}

/**
  * @brief 	FLTH输入滤波器选择
  * @param FLTHFilter: FLTH滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTHBUSCLK: 总线时钟
  * 		@arg Port_FLTHFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTHFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTHFLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTHSET(uint32_t FLTHFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTH_MASK;
	PORT->IOFLT0 |= FLTHFilter;
}

/**
  * @brief 	FLTG输入滤波器选择
  * @param FLTGFilter: FLTG滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTGBUSCLK: 总线时钟
  * 		@arg Port_FLTGFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTGFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTGFLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTGSET(uint32_t FLTGFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTG_MASK;
	PORT->IOFLT0 |= FLTGFilter;
}

/**
  * @brief 	FLTF输入滤波器选择
  * @param FLTFFilter: FLTF滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTFBUSCLK: 总线时钟
  * 		@arg Port_FLTFFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTFFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTFFLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTFSET(uint32_t FLTFFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTF_MASK;
	PORT->IOFLT0 |= FLTFFilter;
}

/**
  * @brief 	FLTE输入滤波器选择
  * @param FLTEFilter: FLTE滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTEBUSCLK: 总线时钟
  * 		@arg Port_FLTEFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTEFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTEFLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTESET(uint32_t FLTEFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTE_MASK;
	PORT->IOFLT0 |= FLTEFilter;
}

/**
  * @brief 	FLTD输入滤波器选择
  * @param FLTDFilter: FLTD滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTDBUSCLK: 总线时钟
  * 		@arg Port_FLTDFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTDFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTDFLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTDSET(uint32_t FLTDFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTD_MASK;
	PORT->IOFLT0 |= FLTDFilter;
}

/**
  * @brief 	FLTC输入滤波器选择
  * @param FLTCFilter: FLTC滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTCBUSCLK: 总线时钟
  * 		@arg Port_FLTCFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTCFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTCFLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTCSET(uint32_t FLTCFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTC_MASK;
	PORT->IOFLT0 |= FLTCFilter;
}

/**
  * @brief 	FLTB输入滤波器选择
  * @param FLTBFilter: FLTB滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTBBUSCLK: 总线时钟
  * 		@arg Port_FLTBFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTBFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTBFLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTBSET(uint32_t FLTBFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTB_MASK;
	PORT->IOFLT0 |= FLTBFilter;
}

/**
  * @brief 	FLTA输入滤波器选择
  * @param FLTAFilter: FLTA滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTABUSCLK: 总线时钟
  * 		@arg Port_FLTAFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTAFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTAFLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTASET(uint32_t FLTAFilter)
{
	PORT->IOFLT0 &= ~PORT_IOFLT0_FLTA_MASK;
	PORT->IOFLT0 |= FLTAFilter;
}

/**
  * @brief 	FLTEWM输入滤波器选择
  * @param FLTEWMFilter: FLTEWM滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTEWMNoFilter: 无滤波器
  * 		@arg Port_FLTEWMFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTEWMFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTIEWMBUSCLK: 总线时钟
  * @retval None.
  */ 
void PORT_FLTEWMSET(uint32_t FLTEWMFilter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTEWM_MASK;
	PORT->IOFLT1 |= FLTEWMFilter;
}

/**
  * @brief 	FLTI2C1输入滤波器选择
  * @param FLTI2C1Filter: FLTI2C1滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTI2C1NoFilter: 无滤波器
  * 		@arg Port_FLTI2C1FLTDIV1: 滤波器分组1
  * 		@arg Port_FLTI2C1FLTDIV2: 滤波器分组2
  * 		@arg Port_FLTI2C1BUSCLK: 总线时钟
  * @retval None.
  */ 
void PORT_FLTI2C1SET(uint32_t FLTI2C1Filter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTI2C1_MASK;
	PORT->IOFLT1 |= FLTI2C1Filter;
}

/**
  * @brief 	FLTI2C0输入滤波器选择
  * @param FLTI2C0Filter: FLTI2C0滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTI2C0NoFilter: 无滤波器
  * 		@arg Port_FLTI2C0FLTDIV1: 滤波器分组1
  * 		@arg Port_FLTI2C0FLTDIV2: 滤波器分组2
  * 		@arg Port_FLTI2C0BUSCLK: 总线时钟
  * @retval None.
  */ 
void PORT_FLTI2C0SET(uint32_t FLTI2C0Filter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTI2C0_MASK;
	PORT->IOFLT1 |= FLTI2C0Filter;
}

/**
  * @brief 	FLTPWT输入滤波器选择
  * @param FLTPWTFilter: FLTPWT滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTPWTNoFilter: 无滤波器
  * 		@arg Port_FLTPWTFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTPWTFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTPWTFLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTPWTSET(uint32_t FLTPWTFilter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTPWT_MASK;
	PORT->IOFLT1 |= FLTPWTFilter;
}

/**
  * @brief 	FLTFTM1输入滤波器选择
  * @param FLTFTM1Filter: FLTFTM1滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTFTM1NoFilter: 无滤波器
  * 		@arg Port_FLTFTM1FLTDIV1: 滤波器分组1
  * 		@arg Port_FLTFTM1FLTDIV2: 滤波器分组2
  * 		@arg Port_FLTFTM1FLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTFTM1SET(uint32_t FLTFTM1Filter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTFTM1_MASK;
	PORT->IOFLT1 |= FLTFTM1Filter;
}

/**
  * @brief 	FLTFTM0输入滤波器选择
  * @param FLTFTM0Filter: FLTFTM0滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTFTM0NoFilter: 无滤波器
  * 		@arg Port_FLTFTM0FLTDIV1: 滤波器分组1
  * 		@arg Port_FLTFTM0FLTDIV2: 滤波器分组2
  * 		@arg Port_FLTFTM0FLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTFTM0SET(uint32_t FLTFTM0Filter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTFTM0_MASK;
	PORT->IOFLT1 |= FLTFTM0Filter;
}

/**
  * @brief 	FLTIRQ输入滤波器选择
  * @param FLTIRQFilter: FLTIRQ滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTIRQNoFilter: 无滤波器
  * 		@arg Port_FLTIRQFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTIRQFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTIRQFLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTIRQSET(uint32_t FLTIRQFilter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTIRQ_MASK;
	PORT->IOFLT1 |= FLTIRQFilter;
}

/**
  * @brief 	FLTI输入滤波器选择
  * @param FLTAFilter: FLTI滤波器参数选择
  *		这个参数可以取下面的值:
  * 		@arg Port_FLTIBUSCLK: 总线时钟
  * 		@arg Port_FLTIFLTDIV1: 滤波器分组1
  * 		@arg Port_FLTIFLTDIV2: 滤波器分组2
  * 		@arg Port_FLTIFLTDIV3: 滤波器分组3
  * @retval None.
  */ 
void PORT_FLTISET(uint32_t FLTIFilter)
{
	PORT->IOFLT1 &= ~PORT_IOFLT1_FLTI_MASK;
	PORT->IOFLT1 |= FLTIFilter;
}

/**
  * @brief 设置端口引脚上拉
  * @param PortPin: 需要进行上拉的端口引脚(PORT_PTA0~PORT_PTI6)
  * @param NewState: 引脚上拉状态
  *		这个参数可以取下面的值:
  * 		@arg ENABLE: 使能引脚上拉
  *			@arg DISABLE: 失能引脚上拉
  * @retval None.
  */ 
void PORT_PullPinCmd(uint8_t PortPin,FunctionalState NewState)
{
	/* while PortPin less than PORT_PTD7 choose PUE0 Regsiter */
	if(PortPin <= (uint8_t)PORT_PTD7)
	{
		if(NewState != DISABLE )
		{
			/* enable pinA-D pull up */
			PORT->PUE0 |= ((uint32_t)1<<PortPin);
		}
		else 
		{	
			/* disable pinA-D pull up */
			PORT->PUE0 &= ~((uint32_t)1<<PortPin);
		}
	}
	else if(PortPin <= (uint8_t)PORT_PTH7)
	{
		if(NewState != DISABLE )
		{
			/* enable pinE-H pull up */
			PORT->PUE1 |= ((uint32_t)1<<(PortPin - 32u));
		}
		else 
		{	
			/* disable pinE-H pull up */
			PORT->PUE1 &= ~((uint32_t)1<<(PortPin - 32u));
		}
	}
	else
	{
		if(NewState != DISABLE )
		{
			/* enable pinI pull up */
			PORT->PUE2 |= ((uint32_t)1<<(PortPin - 64u));
		}
		else 
		{	
			/* disable pinI pull up */
			PORT->PUE2 &= ~((uint32_t)1<<(PortPin - 64u));
		}
	}
}

/**
  * @brief 设置端口引脚的大电流驱动
  * @param hdrvePin: 表示需要进行设置的端口
  *		这个参数可以取下面的值:
  * 		@arg PORT_PullPTB4: PTB4大电流驱动能力
  *			@arg PORT_PullPTB5: PTB5大电流驱动能力
  * 		@arg PORT_PullPTD0: PTD0大电流驱动能力
  *			@arg PORT_PullPTD1: PTD1大电流驱动能力
  * 		@arg PORT_PullPTE0: PTE0大电流驱动能力
  *			@arg PORT_PullPTE1: PTE1大电流驱动能力
  * 		@arg PORT_PullPTH0: PTH0大电流驱动能力
  *			@arg PORT_PullPTH1: PTH1大电流驱动能力
  * @param NewState: 大电流驱动使能状态
  *		这个参数可以取下面的值:
  * 		@arg ENABLE: 大电流驱动使能
  *			@arg DISABLE: 大电流驱动失能
  * @retval None.
  */ 
void PORT_HDRVEPinCmd(uint8_t hdrvePin,FunctionalState NewState)
{
	if(NewState != DISABLE )
	{
		/* enable pin high drive */
		PORT->HDRVE |= ((uint32_t)1<<hdrvePin) ;
	}
	else 
	{
		/* disable pin high drive */
		PORT->HDRVE &= ~((uint32_t)1<< hdrvePin );
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
