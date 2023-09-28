/**
  ******************************************************************************
  * @file     xl_ics.c
  * @author   xu.wang
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
#include "xl_ics.h"

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @defgroup ICS ISC Module 
  * @brief ICS Driver Modules Library
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

	
/** @defgroup ICS_Private_Functions
  * @{
 */ 	

/**
 * @brief  将ICS外设寄存器恢复默认值
 * @param  ICSx: 指向ICS外设
 * @retval None
 */
void ICS_DeInit(void)
{
	/* Deinitializes to default reset values */
	ICS->C1 = 0x04;
	ICS->C2 = 0x02;
	ICS->C3 = 0x00;
	ICS->C4 = 0x00;
}

/**
 * @brief 时钟源选择
 * @param  Clksel: 时钟源选择
 *		这个参数可以取下面的值:
 *			@arg ICS_CLOCKS_FLL：时钟源为FLL输出         
 *			@arg ICS_CLOCKS_IRC：时钟源为内部时钟(IRC)    
 *			@arg ICS_CLOCKS_OSC：时钟源为外部时钟(OSC)   
 *			@arg ICS_CLOCKS_RESERVED：保留
 * @retval None
 */
void ICS_ClocksSelect(uint8_t Clksel)
{
	uint8_t temp;
	
	temp = ICS->C1;
	
	temp &= ~ICS_C1_CLKS_MASK;
	
	temp |= (uint8_t)(Clksel<<ICS_C1_CLKS_SHIFT);
	
	ICS->C1 = temp;
}

/**
 * @brief 时钟基准分频
 * @param  BDiv: 分频系数
 *		这个参数可以取下面的值:
 *			@arg ICS_RDIV_1or32   ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为1  ；频率范围为4-24MHz低频范围：分频系数为32；
 *			@arg ICS_RDIV_2or64   ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为2  ；频率范围为4-24MHz低频范围：分频系数为64；
 *			@arg ICS_RDIV_4or128  ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为4  ；频率范围为4-24MHz低频范围：分频系数为128；
 *			@arg ICS_RDIV_8or256  ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为8  ；频率范围为4-24MHz低频范围：分频系数为256；
 *			@arg ICS_RDIV_16or512 ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为16 ；频率范围为4-24MHz低频范围：分频系数为512；       
 *			@arg ICS_RDIV_32or1024：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为32 ；频率范围为4-24MHz低频范围：分频系数为1024；
 *			@arg ICS_RDIV_64      ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为64 ；频率范围为4-24MHz低频范围：分频系数为保留；
 *			@arg ICS_RDIV_128     ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为128；频率范围为4-24MHz低频范围：分频系数为保留；
 * @retval None
 */
void ICS_BaseDivider(uint8_t RDiv)
{
	uint8_t temp;
	
	temp = ICS->C1;
	
	temp &= ~ICS_C1_RDIV_MASK;
	
	temp |= (uint8_t)(RDiv<<ICS_C1_RDIV_SHIFT);
	
	ICS->C1 = temp;
}

/**
 * @brief 时钟基准分频2
 * @param  BDiv: 分频系数
 *		这个参数可以取下面的值:
 *			@arg ICS_RDIV2_1  ：1分频
 *			@arg ICS_RDIV2_2  ：2分频
 *			@arg ICS_RDIV2_3  ：3分频
 *			@arg ICS_RDIV2_4  ：4分频
 *			@arg ICS_RDIV2_5  ：5分频  
 *			@arg ICS_RDIV2_6  ：6分频
 *			@arg ICS_RDIV2_7  ：7分频
 *			@arg ICS_RDIV2_8  ：8分频
 * @retval None
 */
void ICS_BaseDivider2(uint8_t RDiv2)
{
	uint8_t temp;
	
	temp = ICS->C4;
	
	temp &= ~ICS_C4_RDIV2_MASK;
	
	temp |= (uint8_t)(RDiv2<<ICS_C4_RDIV2_SHIFT);
	
	ICS->C4 = temp;
}

/**
 * @brief 时钟基准分频
 * @param  None
 * @retval 分频值
 *		这个参数可以取下面的值:
 *			@arg ICS_RDIV_1or32   ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为1  ；频率范围为4-24MHz低频范围：分频系数为32；
 *			@arg ICS_RDIV_2or64   ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为2  ；频率范围为4-24MHz低频范围：分频系数为64；
 *			@arg ICS_RDIV_4or128  ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为4  ；频率范围为4-24MHz低频范围：分频系数为128；
 *			@arg ICS_RDIV_8or256  ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为8  ；频率范围为4-24MHz低频范围：分频系数为256；
 *			@arg ICS_RDIV_16or512 ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为16 ；频率范围为4-24MHz低频范围：分频系数为512；       
 *			@arg ICS_RDIV_32or1024：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为32 ；频率范围为4-24MHz低频范围：分频系数为1024；
 *			@arg ICS_RDIV_64      ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为64 ；频率范围为4-24MHz低频范围：分频系数为保留；
 *			@arg ICS_RDIV_128     ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为128；频率范围为4-24MHz低频范围：分频系数为保留；
 */
uint8_t ICS_GetBaseDivider(void)
{
	uint8_t temp;
	
	temp = ICS->C1;
	
	temp &= ICS_C1_RDIV_MASK;
	
	temp >>= ICS_C1_RDIV_SHIFT;
	
	return temp;
}

/**
 * @brief 获取OSC的基准分频器2的分频值
 * @param  None
 * @retval 分频值
 *		这个参数可以取下面的值:
 *			@arg ICS_RDIV_1or32   ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为1  ；频率范围为4-24MHz低频范围：分频系数为32；
 *			@arg ICS_RDIV_2or64   ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为2  ；频率范围为4-24MHz低频范围：分频系数为64；
 *			@arg ICS_RDIV_4or128  ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为4  ；频率范围为4-24MHz低频范围：分频系数为128；
 *			@arg ICS_RDIV_8or256  ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为8  ；频率范围为4-24MHz低频范围：分频系数为256；
 *			@arg ICS_RDIV_16or512 ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为16 ；频率范围为4-24MHz低频范围：分频系数为512；       
 *			@arg ICS_RDIV_32or1024：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为32 ；频率范围为4-24MHz低频范围：分频系数为1024；
 *			@arg ICS_RDIV_64      ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为64 ；频率范围为4-24MHz低频范围：分频系数为保留；
 *			@arg ICS_RDIV_128     ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为128；频率范围为4-24MHz低频范围：分频系数为保留；
 */
uint8_t ICS_GetBaseDivider2(void)
{
	uint8_t temp;
	temp = ICS->C4;
	
	temp &= ICS_C4_RDIV2_MASK;
	
	temp >>= ICS_C4_RDIV2_SHIFT;
	
	return temp + 1u;
}

/**
 * @brief FLL时钟基准选择
 * @param  FllSel: FLL选择的基准时钟源
 *	 这个参数可以取下面的值:
 *			@arg ICS_IREFS_OSC ：外部OSC时钟源
 *			@arg ICS_IREFS_IRC ：内部IRC时钟源
 * @retval None
 * 	NOTE:
 * 		(1-60)3.6 时钟模块->3.6.1 ICS 配置
 */
void ICS_IREFSSelect(uint8_t FllSel)
{
	uint8_t temp;
	
	temp = ICS->C1;
	
	temp &= ~ICS_C1_IREFS_MASK;
	
	temp |= (uint8_t)(FllSel<<ICS_C1_IREFS_SHIFT);
	
	ICS->C1 = temp;
}

/**
 * @brief 内部基准时钟(IRC)使能
 * @param  State: 使能状态
 *	 这个参数可以取下面的值:
 *			@arg ENABLE ：内部基准时钟(IRC)有效
 *			@arg DISABLE ：内部基准时钟(IRC)无效
 * @retval None
 */
void ICS_IRCEnableCmd(FunctionalState State)
{
	if(State !=DISABLE)
	{
		/*  */
		ICS->C1 |= ICS_C1_IRCLKEN_MASK;
	}
	else 
	{
		/*  */
		ICS->C1 &= ~ICS_C1_IRCLKEN_MASK;
	}
}

/**
 * @brief  内部基准时钟停止使能，控制内部时钟在ICS进入Stop模式时是否保持使能
 * @param  ICSx: 指向ICS外设
 * @param  State: 使能状态
 *	 这个参数可以取下面的值:
 *			@arg ENABLE ：内部基准时钟在stop模式下禁用
 *			@arg DISABLE ：内部基准时钟在stop模式下不禁用
 * @retval None
 */
void ICS_IREFStopEnableCmd(FunctionalState State)
{
	if(State !=DISABLE)
	{
		/*  */
		ICS->C1 &= ~ICS_C1_IREFSTEN_MASK;
	}
	else 
	{
		/*  */
		ICS->C1 |= ICS_C1_IREFSTEN_MASK;
	}
}
/**
 * @brief  总线时钟分频
 * @param  BDiv: 分频系数(1-128)
 * @retval None
 */
void ICS_BusDivder(uint8_t BDiv)
{
	uint8_t temp;
	
	temp = ICS->C2;
	
	temp &= ~ICS_C2_BDIV_MASK;
	
	temp |= (uint8_t)((BDiv-1u) << ICS_C2_BDIV_SHIFT);
	
	ICS->C2 = temp;
}

/**
 * @brief  得到ICS_OUTCLK的分频值
 * @param  None
 * @retval 分频值
 */
uint8_t ICS_GetBusDivder(void)
{	
	return (uint8_t)(ICS->C2 >> 1);
}

/**
 * @brief  FLL在低功耗是禁用选择
 * @param  State: 使能状态
 *	 这个参数可以取下面的值:
 *			@arg ENABLE ：低功耗模式下禁用
 *			@arg DISABLE ：低功耗模式下不禁用
 * @retval None
 */
void ICS_FllLPModeStopEnableCmd(FunctionalState State)
{
	if(State !=DISABLE)
	{
		/*  */
		ICS->C2 |= ICS_C2_LP_MASK;
	}
	else 
	{
		/*  */
		ICS->C2 &= ~ICS_C2_LP_MASK;
	}
}

/**
 * @brief  失锁中断使能，该功能在FLL已失锁有效
 * @param  State: 使能状态
 *	 这个参数可以取下面的值:
 *			@arg ENABLE ：使能失锁中断
 *			@arg DISABLE ：不使能失锁中断
 * @retval None
 */
void ICS_LosingLockIntEnableCmd(FunctionalState State)
{
	if(State !=DISABLE)
	{
		/*  */
		ICS->C4 |= ICS_C4_LOLIE_MASK;
	}
	else 
	{
		/*  */
		ICS->C4 &= ~ICS_C4_LOLIE_MASK;
	}
}
/**
 * @brief  失锁中断使能，该功能在FLL已失锁有效
 * @param  State: 使能状态
 *	 这个参数可以取下面的值:
 *			@arg ENABLE ：FLL在stop模式下强制关断，即LP为0
 *			@arg DISABLE ：FLL在stop模式下根据LP标志选择关断
 * @retval None
 */
void ICS_FllStopModeCloseEnableCmd(FunctionalState State)
{
	if(State !=DISABLE)
	{
		/*  */
		ICS->C4 &= ~ICS_C4_FLLSTEN_MASK;
	}
	else 
	{
		/*  */
		ICS->C4 |= ICS_C4_FLLSTEN_MASK;
	}
}
/**
 * @brief 时钟监控使能
 * @param  State: 使能状态
 *	 这个参数可以取下面的值:
 *			@arg ENABLE ：丢失外部时钟时产生一个复位请求
 *			@arg DISABLE ：禁用时钟监控
 * @retval None
 */
void ICS_ClockMonitorEnableCmd(FunctionalState State)
{
	if(State !=DISABLE)
	{
		/*  */
		ICS->C4 |= ICS_C4_CME_MASK;
	}
	else 
	{
		/*  */
		ICS->C4 &= ~ICS_C4_CME_MASK;
	}
}

/**
 * @brief  IRC时钟选择
 * @param  IRCValue: IRC时钟
 *	 这个参数可以取下面的值:
 *			@arg ICS_IRC_50K ：IRC为54kHz
 *			@arg ICS_IRC_37o5K ：IRC为37.5kHz
 * @retval None
 */
void ICS_IRCSelect(uint8_t IRCValue)
{
	uint32_t temp;
	
	temp = ICS->CFG;
	
	temp &= ~ICS_CFG_IRCSEL_MASK;
	
	temp |= (uint32_t)(0x55690000u | (uint32_t)((uint32_t)IRCValue << (uint32_t)ICS_CFG_IRCSEL_SHIFT));
	
	ICS->CFG = temp;
}

/**
 * @brief FLL倍频选择
 * @param  FactorValue: 倍频系数
 *	 这个参数可以取下面的值:
 *			@arg ICS_FLLFACTOR_1280 ：1280倍频
 *			@arg ICS_FLLFACTOR_1920 ：1920倍频
 * @retval None
 * NOTE:
 * 	(1-237)16.4.7.1 FLL(锁频环)时钟锁定 确定频率
 */
void ICS_FllFactorSelect(uint8_t FactorValue)
{
	uint32_t temp;
	
	temp = ICS->CFG;
	
	temp &= ~ICS_CFG_FLLFSEL_MASK;
	
	temp |= (uint32_t)(0x55690000u | (uint32_t)FactorValue);
	
	ICS->CFG = temp;
}

/**
 * @brief 获取ICS状态
 * @param  Status: 将要获取的状态标志
 *	 这个参数可以取下面的值:
 *			@arg ICS_STATUS_LOSINGLOCK ：失锁状态，指定FLL锁定状态
 *			@arg ICS_STATUS_LOCK ：锁定状态，指示FLL是否已经获取锁定
 *			@arg ICS_STATUS_IREF ：内部基准状态，为0：基准时钟来源于外部时钟，为1：基准时钟来源于内部时钟
 * @retval 返回对应ICS状态的标志
 *	 这个参数可以取下面的值:
 *			@arg 1 ：状态置1
 *			@arg 0 ：状态置0
 */
uint8_t ICS_GetStatus(uint8_t ICSStatus)
{
	uint8_t sta;
	if(ICSStatus == (ICSStatus & ICS->S))
	{
		sta = 1;
	}
	else
	{
		sta = 0;
	}
	return sta;
}

/**
 * @brief 获取时钟模式
 * @param  Status: 将要获取的状态标志
 * @retval 返回对应ICS状态的标志
 *	 这个参数可以取下面的值:
 *			@arg ICS_MODE_FLL ：时钟模式为FLL输出
 *			@arg ICS_MODE_IRC ：时钟模式为内部基准时钟(IRC)
 *			@arg ICS_MODE_OSC ：时钟模式为外部基准时钟(OSC)
 *			@arg ICS_MODE_RESERVED ：保留
 */
uint8_t ICS_GetClockMode(void)
{
	uint8_t temp;
	
	uint8_t clkmode;
	
	temp = ICS->S & ICS_S_CLKST_MASK;
	
	temp >>= ICS_S_CLKST_SHIFT;
	
	if(temp == ICS_MODE_FLL)
	{
		clkmode = ICS_MODE_FLL;
	}
	else if(temp == ICS_MODE_IRC)
	{
		clkmode =  ICS_MODE_IRC;
	}
	else if(temp == ICS_MODE_OSC)
	{
		clkmode =  ICS_MODE_OSC;
	}
	else
	{
		clkmode =  ICS_MODE_RESERVED;
	}
	return clkmode;
}

/**
 * @brief 获取IREF时钟源
 * @param  None
 * @retval IREF的时钟源标志
 *	 这个参数可以取下面的值:
 *			@arg ICS_IREFS_OSC ：外部OSC时钟源
 *			@arg ICS_IREFS_IRC ：内部IRC时钟源
 */
uint8_t ICS_GetIREFSSelect(void)
{
	uint8_t temp;
	
	if((ICS->C1 & (uint8_t)0x04) == (uint8_t)0x04)
	{
		temp = ICS_IREFS_IRC;
	}
	else
	{
		temp = ICS_IREFS_OSC;
	}
	return temp;
}

/**
 * @brief 获取当前IRC时钟频率
 * @retval 返回对应ICS状态的标志
 *	 这个参数可以取下面的值:
 *			@arg ICS_IRC_50K ：IRC频率为100k
 *			@arg ICS_IRC_37o5K ：IRC频率为150k
 */
uint8_t ICS_GetIRCFre(void)
{
	uint8_t temp;
	if((ICS->CFG & (uint32_t)0x2) == (uint32_t)0x2)
	{
		temp = ICS_IRC_37o5K;
	}
	else
	{
		temp = ICS_IRC_50K;
	}
	return temp;
}

/**
 * @brief 获取当前FLL倍频器的倍数
 * @retval 返回对应FLL倍频器系数的标志
 *	 这个参数可以取下面的值:
 *			@arg ICS_FLLFACTOR_1280 ：FLL倍频系数是1280倍
 *			@arg ICS_FLLFACTOR_1920 ：FLL倍频系数是1920倍
 */
uint8_t ICS_GetFLLMultiple(void)
{
	uint8_t temp;
	if((ICS->CFG & (uint32_t)0x1) == (uint32_t)0x1)
	{
		temp = ICS_FLLFACTOR_1920;
	}
	else
	{
		temp = ICS_FLLFACTOR_1280;
	}
	return temp;
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

