/**
  ******************************************************************************
  * @file     system_XL6600.c
  * @author   xu.wang
  * @version  V3.0.0
  * @date     4-Jun-2019
  * @brief    This file provide function about system XL6600 firmware program 
	* 					Provides a system configuration function and a global variable that contains
	*           the system frequency. It configures the device and initializes the oscillator
	*           (PLL) that is part of the microcontroller device.
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

/* Includes ---------------------------------------------------------------*/

#include "system_xl6600.h"
#include "xl6600.h"
#include "xl_sim.h"
#include "xl_wdog.h"
#include "xl_ics.h"
#include "xl_osc.h"
#include "xl_flash.h"

static uint32_t OSC_ClockSource;


/**
 * @brief  SystemInit函数
 */
void SystemInit(void) 
{
	FMC->FCPC0 |= FMC_FCPC0_CEN_MASK;
	
	SIM_SCGC_Cmd(SIM_SCGC_WDG,ENABLE);
	WDOG_EnableCmd(WDOG,ENABLE);
	WDOG_ClrInt(WDOG);
	WDOG_CountRestart(WDOG);
	WDOG_DeInit(WDOG);
	WDOG_EnableCmd(WDOG,DISABLE);
	
	SIM_SCGC_Cmd(SIM_SCGC_WDG,DISABLE);

}

/**
 * @brief 设置内部时钟
 * @param  ICS_IRCSel: IRC频率选择	# IRC（Internal Reference Clock）频率是内部参考时钟的频率，用于作为系统时钟的参考
 *			@arg ICS_IRC_50K ：50K
 *			@arg ICS_IRC_37o5K ：37.5K
 * @param  FactorValue: 倍频系数			# FLL（Frequency-Locked Loop）
 *			@arg ICS_FLLFACTOR_1280 ：1280倍频
 *			@arg ICS_FLLFACTOR_1920 ：1920倍频
 * @retval None
 * FLL 上电阶段从FLASH配置区加载
 */
SYS_CLK_STATUS SystemSetFEI(uint8_t ICS_IRCSel, uint8_t ICS_FLLFSel)
{
	uint32_t coreclk;
	uint32_t busclk;
	uint32_t timeout = 0xFFFFFu;
	
	SYS_CLK_STATUS ClkState = SYS_CLK_OK;	// SYS_CLK_OK=0
	
	//FLASH_SetReadWait(FLASH_READWAIT_4CYCLE);
	
	// 如果外部晶振使能,先禁用它
	if((OSC->CR & OSC_CR_OSCEN_MASK) == OSC_CR_OSCEN_MASK)	/*
	* OSC->CR=111 0000 0000; OSC_CR_OSCEN_MASK=1000 0000; OSC_CR_OSCEN_MASK=0x80u=1000 0000
	* */
	{
		// 选择内部时钟
		ICS_ClocksSelect(ICS_CLOCKS_IRC); /*
		* ICS_CLOCKS_IRC=(uint8_t)0x01*/
		
		// 禁用外部晶振
		OSC->CR &= ~OSC_CR_OSCEN_MASK; /*
		* ~OSC_CR_OSCEN_MASK=~(0x80u)=0111 1111=0x7Fu*/
		OSC->CR |= 0x16u; /*
		* OSC->CR=(0x7Fu || 0x16u)=(0111 1111||0001 0110)=0111 1111=0x7Fu*/
		OSC->CR |= OSC_CR_OSCEN_MASK;/*
		* OSC->CR=(0x7Fu || 0x80u)=(0111 1111||1000 0000)=1111 1111=0xFF*/
		// 等待外部晶振禁用
		while((OSC->CR & OSC_CR_OSCINIT_MASK) != OSC_CR_OSCINIT_MASK)/*
		* (0xFFu&0x01u)=0x01u != 0x01u*/
		{
			timeout--;	//1048575
			if((timeout<50u)||(timeout>0xFFFFFu))
			{	// 禁用失败则退出 QUESTION
				OSC->CR &= ~OSC_CR_OSCEN_MASK;/*
				* OSC->CR=0xFFu; ~(OSC_CR_OSCEN_MASK)=~(0x80u)=0x7Fu
				* -> OSC->CR=0xFFu&0x7Fu=1111 1111 & 0111 1111=0x7Fu*/
				break;
			}
		}
		// 禁用外部晶振
		OSC->CR &= ~OSC_CR_OSCEN_MASK;
	}
	// 选择内部时钟
	ICS_ClocksSelect(ICS_CLOCKS_IRC);	/*
	* ICS_CLOCKS_IRC：时钟源为内部时钟(IRC)*/
	FLASH_SetReadWait(FLASH_READWAIT_2CYCLE);	// Flash设置 等待(2CYCLE-2)周期
	if(ICS_IRCSel == ICS_IRC_50K)//50k	// IRC 频率选择
	{
		ICS_IRCSelect(ICS_IRC_50K);
		if(ICS_FLLFSel == ICS_FLLFACTOR_1920) // 倍频系数选择
		{
			ICS_FllFactorSelect(ICS_FLLFACTOR_1920);
			coreclk = 96000000;
		}
		else//1280
		{
			ICS_FllFactorSelect(ICS_FLLFACTOR_1280);
			coreclk = 64000000;
		}
	}
	else//37.5k
	{
		ICS_IRCSelect(ICS_IRC_37o5K);
		if(ICS_FLLFSel == ICS_FLLFACTOR_1920)//72
		{
			ICS_FllFactorSelect(ICS_FLLFACTOR_1920);
			coreclk = 72000000;
		}
		else//1280
		{
			ICS_FllFactorSelect(ICS_FLLFACTOR_1280);
			coreclk = 48000000;
		}
	}
	// 选择内部参考时钟
	ICS_IREFSSelect(ICS_IREFS_IRC);
	ICS_IRCEnableCmd(ENABLE);	// 控制内部基准时钟(IRC) - 使能 IRC
	ICS_FllLPModeStopEnableCmd(DISABLE);	// FLL在低功耗是状态选择 - 停止低功耗模式
	// 等待锁定
	timeout = 0xFFFFFu;
	while(0u == ICS_GetStatus(ICS_STATUS_LOCK))
	{
		timeout--;
		if((timeout<50u)||(timeout>0xFFFFFu))
		{
			ClkState = ICS_STATUS_UNLOCK;
			break;
			//return feeState;
		}
	}
	if(ClkState == SYS_CLK_OK)
	{	// 根据核心频率设置总线频率
		//coreclk = Get_SystemCoreClock();
		if(coreclk > 50000000u)
		{
			 //SIM_CLKDIV_OUTDIV2(2u);
			busclk = coreclk>>1u;	// 分频到一半
		}
		// 初始化Flash
		timeout = 0xFFFFFu;
		while(FLASH_ERR_SUCCESS != FLASH_Init((uint8_t)(busclk/1000000u)))
		{
			timeout--;
			if((timeout<50u)||(timeout>0xFFFFFu))
			{
				ClkState = FLASH_INIT_ERROR;
				break;
				//return feeState;
			}
		}
		if(ClkState == SYS_CLK_OK)
		{	// 根据总线频率设置Flash等待周期
			if(busclk > 90000000u)	
			{
				FLASH_SetReadWait(FLASH_READWAIT_5CYCLE);
			}
			else if(busclk > 60000000u)
			{
				FLASH_SetReadWait(FLASH_READWAIT_4CYCLE);
			}
			else if(busclk > 30000000u)
			{
				FLASH_SetReadWait(FLASH_READWAIT_3CYCLE);
			}
			else
			{
				FLASH_SetReadWait(FLASH_READWAIT_2CYCLE);
			}
		}
		else
		{
			FLASH_SetReadWait(FLASH_READWAIT_5CYCLE);
		}
		// 根据核心频率设置总线时钟分频
		if(coreclk > 50000000u)
		{
			 SIM_CLKDIV_OUTDIV2(2u);
		}
		else//20210807 AFT
		{
			SIM_CLKDIV_OUTDIV2(1u);//20210807 AFT
		}
		// 选择 FLL 作为系统时钟
		ICS_ClocksSelect(ICS_CLOCKS_FLL);
	}

	return ClkState;
}
/**
 * @brief 使用外部时钟
 * @param  osc_clkfre: 外部晶振频率
 * @param  ICS_FLLFSel: 倍频系数
 *			@arg ICS_FLLFACTOR_1280 ：1280倍频
 *			@arg ICS_FLLFACTOR_1920 ：1920倍频
 * @param  osc_bdiv: OSC第一分频器
 *		这个参数可以取下面的值:
 *			@arg ICS_RDIV_1or32   ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为1  ；频率范围为4-24MHz低频范围：分频系数为32；
 *			@arg ICS_RDIV_2or64   ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为2  ；频率范围为4-24MHz低频范围：分频系数为64；
 *			@arg ICS_RDIV_4or128  ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为4  ；频率范围为4-24MHz低频范围：分频系数为128；
 *			@arg ICS_RDIV_8or256  ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为8  ；频率范围为4-24MHz低频范围：分频系数为256；
 *			@arg ICS_RDIV_16or512 ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为16 ；频率范围为4-24MHz低频范围：分频系数为512；       
 *			@arg ICS_RDIV_32or1024：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为32 ；频率范围为4-24MHz低频范围：分频系数为1024；
 *			@arg ICS_RDIV_64      ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为64 ；频率范围为4-24MHz低频范围：分频系数为保留；
 *			@arg ICS_RDIV_128     ：(OSC_CR[RANGE]=0)频率范围为32kHz低频范围：分频系数为128；频率范围为4-24MHz低频范围：分频系数为保留；
 * @param  osc_bdiv2: OSC第二分频器
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
SYS_CLK_STATUS SystemSetFEE(uint32_t osc_clkfre, uint8_t ICS_FLLFSel, uint8_t osc_bdiv,uint8_t osc_bdiv2)
{
	OSC_InitTypeDef sOSC_InitTypeDef;
	
	uint32_t temp;
	uint32_t temp1;
	//uint8_t stat_flag;
  uint32_t coreclk;
	uint32_t busclk;
	uint32_t timeout = 0xFFFFu;

	SYS_CLK_STATUS ClkState = SYS_CLK_OK;
	
	
	OSC_EnableCmd(DISABLE);
	sOSC_InitTypeDef.OSC_ModeSelect = OSC_HG_MODE;//OSC_HG_MODE  OSC_LP_MODE
	sOSC_InitTypeDef.OSC_OutputSelect = OSC_OSCCILLATOR_COLOR;
	sOSC_InitTypeDef.OSC_RangeSelect = OSC_RANGE_HIGH;//OSC_RANGE_LOW  OSC_RANGE_HIGH
	OSC_Init(&sOSC_InitTypeDef);
	OSC_EnableCmd(ENABLE);
	while(0u==OSC_GetInitStatus())
	{
		timeout--;
		if((timeout<50u)||(timeout>0xFFFFu))
		{
			ClkState = OSC_INIT_ERROR;
			break;
			//return feeState;
		}
	}
	
	if(ClkState == SYS_CLK_OK)
	{
		//FLASH_SetReadWait(FLASH_READWAIT_4CYCLE);
	
		if(OSC_RANGE_HIGH == OSC_GetRange())
		{
			temp = (uint32_t)((uint32_t)1u<<(osc_bdiv+5u));
			temp *= ((uint32_t)osc_bdiv2+1u);
		}
		else
		{
			temp = (uint32_t)((uint32_t)1u<<(osc_bdiv));
			temp *= ((uint32_t)osc_bdiv2+1u);
		}
			
		temp1 = osc_clkfre/temp;
		
		if((temp1<30000u) || (temp1>65000u))
		{
			//stat_flag=0;
			ClkState = OSC_DIV_ERROR;
			
			OSC_EnableCmd(DISABLE);
			sOSC_InitTypeDef.OSC_ModeSelect = OSC_HG_MODE;//OSC_HG_MODE  OSC_LP_MODE
			sOSC_InitTypeDef.OSC_OutputSelect = OSC_OSCCILLATOR_COLOR;
			sOSC_InitTypeDef.OSC_RangeSelect = OSC_RANGE_HIGH;//OSC_RANGE_LOW  OSC_RANGE_HIGH
			OSC_Init(&sOSC_InitTypeDef);
			OSC_EnableCmd(DISABLE);
		}
		else
		{
			
			ICS_BaseDivider(osc_bdiv);//设置外部时钟分频值
			
			ICS_BaseDivider2(osc_bdiv2);
			
			ICS_ClocksSelect(ICS_CLOCKS_IRC);
			FLASH_SetReadWait(FLASH_READWAIT_2CYCLE);
			if(ICS_FLLFSel == ICS_FLLFACTOR_1920)
			{
				ICS_FllFactorSelect(ICS_FLLFACTOR_1920);
				coreclk = temp1 * 1920;
			}
			else//1280
			{
				ICS_FllFactorSelect(ICS_FLLFACTOR_1280);
				coreclk = temp1 * 1280;
			}
			/*FLL is not must close in stop mode*/
			//ICS_FllStopModeCloseEnableCmd(ICS,DISABLE);
			
			//SystemSetFBI();//内部旁路时钟		
			//ICS_ClocksSelect(ICS_CLOCKS_IRC);
			
			ICS_IREFSSelect(ICS_IREFS_OSC); 
			
			/*FLL 在旁路模式下不禁用*/
			ICS_FllLPModeStopEnableCmd(DISABLE);
			
			timeout = 0xFFFFu;
			
			while(0u==ICS_GetStatus(ICS_STATUS_LOCK))
			{
				timeout--;
				if((timeout<50u)||(timeout>0xFFFFu))
				{
					ClkState = ICS_STATUS_UNLOCK;
					break;
					//return feeState;
				}
			}
			if(ClkState == SYS_CLK_OK)
			{
				OSC_ClockSource = osc_clkfre;
				/*选择IREFS(FLL)时钟源为外部时钟*/
				//ICS_IREFSSelect(ICS_IREFS_OSC); 
					
				//coreclk = Get_SystemCoreClock();
				
				if(coreclk > 50000000u)
				{
					//SIM_CLKDIV_OUTDIV2(2);
					busclk = coreclk>>1u;
				}
					
				timeout = 0xFFFFFu;
				while(FLASH_ERR_SUCCESS != FLASH_Init((uint8_t)(busclk/1000000u)))
				{
					timeout--;
					if((timeout<50u)||(timeout>0xFFFFu))
					{
						ClkState = FLASH_INIT_ERROR;
						break;
					}
				}
				if(ClkState == SYS_CLK_OK)
				{
					if(busclk > 90000000u)	
					{
						FLASH_SetReadWait(FLASH_READWAIT_5CYCLE);
					}
					else if(busclk > 60000000u)
					{
						FLASH_SetReadWait(FLASH_READWAIT_4CYCLE);
					}
					else if(busclk > 30000000u)
					{
						FLASH_SetReadWait(FLASH_READWAIT_3CYCLE);
					}
					else
					{
						FLASH_SetReadWait(FLASH_READWAIT_2CYCLE);
					}
					
					if(coreclk > 50000000u)
					{
						SIM_CLKDIV_OUTDIV2(2);
					}
					ICS_ClocksSelect(ICS_CLOCKS_FLL);
				}
				else
				{
					FLASH_SetReadWait(FLASH_READWAIT_5CYCLE);
				}
			}
			else
			{
				ICS_IREFSSelect(ICS_IREFS_IRC); 
				
				OSC_EnableCmd(DISABLE);
				sOSC_InitTypeDef.OSC_ModeSelect = OSC_HG_MODE;//OSC_HG_MODE  OSC_LP_MODE
				sOSC_InitTypeDef.OSC_OutputSelect = OSC_OSCCILLATOR_COLOR;
				sOSC_InitTypeDef.OSC_RangeSelect = OSC_RANGE_HIGH;//OSC_RANGE_LOW  OSC_RANGE_HIGH
				OSC_Init(&sOSC_InitTypeDef);
				OSC_EnableCmd(DISABLE);
			}
		}
	}
	else
	{
		OSC_EnableCmd(DISABLE);
		sOSC_InitTypeDef.OSC_ModeSelect = OSC_HG_MODE;//OSC_HG_MODE  OSC_LP_MODE
		sOSC_InitTypeDef.OSC_OutputSelect = OSC_OSCCILLATOR_COLOR;
		sOSC_InitTypeDef.OSC_RangeSelect = OSC_RANGE_HIGH;//OSC_RANGE_LOW  OSC_RANGE_HIGH
		OSC_Init(&sOSC_InitTypeDef);
		OSC_EnableCmd(DISABLE);
	}
	
	
	return ClkState;
}

/**
 * @brief 内部旁路
 * @param  None
 * @retval 内部旁路时钟的频率
 */
uint32_t SystemSetFBI(void)
{
	uint32_t temp;
        uint32_t coreclk;
	/* ICS Clocks is IRC*/
	ICS_ClocksSelect(ICS_CLOCKS_IRC);
	/*FLL 在旁路模式下不禁用*/
	ICS_FllLPModeStopEnableCmd(DISABLE);
	
	if(ICS_GetIRCFre() == ICS_IRC_37o5K)
	{
		temp = 150000u;
	}
	else
	{
		temp = 100000u;
	}
	
        coreclk = Get_SystemCoreClock();
        if(coreclk > 50000000u)
         {
             SIM_CLKDIV_OUTDIV2(2);
         }
        
	if(Get_BusClock() > 90000000u)	
	{
		FLASH_SetReadWait(FLASH_READWAIT_5CYCLE);
	}
	else if(Get_BusClock() > 60000000u)
	{
		FLASH_SetReadWait(FLASH_READWAIT_4CYCLE);
	}
	else if(Get_BusClock() > 30000000u)
	{
		FLASH_SetReadWait(FLASH_READWAIT_3CYCLE);
	}
	else
	{
		FLASH_SetReadWait(FLASH_READWAIT_2CYCLE);
	}
	
	return temp;
}
/**
 * @brief 内部旁路低功耗
 * @param  None
 * @retval None
 */
void SystemSetFBILP(void)
{
	/* ICS Clocks is IRC*/
	ICS_ClocksSelect(ICS_CLOCKS_IRC);
	//ICS_IRCSelect(ICS_IRC_37o5K);
	//ICS_IREFStopEnableCmd(ENABLE);
	/*FLL Factor is 1280*/
	ICS_FllFactorSelect(ICS_FLLFACTOR_1280);
	/*FLL is must close in stop mode*/
	ICS_FllStopModeCloseEnableCmd(ENABLE);
	
	//ICS_FllLPModeStopEnableCmd(ENABLE);
}
/**
 * @brief 外部旁路
 * @param  None
 * @retval None
 */
void SystemSetFBE(uint32_t osc_clkfre)
{
	OSC_InitTypeDef sOSC_InitTypeDef;
        uint32_t coreclk;
	
	OSC_EnableCmd(DISABLE);
	
	sOSC_InitTypeDef.OSC_ModeSelect = OSC_HG_MODE;
	sOSC_InitTypeDef.OSC_OutputSelect = OSC_OSCCILLATOR_COLOR;
	sOSC_InitTypeDef.OSC_RangeSelect = OSC_RANGE_HIGH;
	OSC_Init(&sOSC_InitTypeDef);
	OSC_EnableCmd(ENABLE);
	while(0u==OSC_GetInitStatus()){};
	
	/*选择ICS为外部基准时钟*/		
	ICS_ClocksSelect(ICS_CLOCKS_OSC);		
	
	/*选择IREFS(FLL)时钟源为外部时钟*/
	ICS_IREFSSelect(ICS_IREFS_OSC);
	
	/*选择IREFS在stop模式下不停止使能*/
	ICS_IREFStopEnableCmd(DISABLE);
	
	/*FLL Factor is 1280*/
	ICS_FllFactorSelect(ICS_FLLFACTOR_1280);
	/*FLL is not must close in stop mode*/
	ICS_FllStopModeCloseEnableCmd(DISABLE);
	/*FLL 在旁路模式下不禁用*/
	ICS_FllLPModeStopEnableCmd(ENABLE);
	
	//ICS_IRCEnableCmd(ICS,DISABLE);
	OSC_ClockSource = osc_clkfre;
        
        coreclk = Get_SystemCoreClock();
        if(coreclk > 50000000u)
         {
             SIM_CLKDIV_OUTDIV2(2);
         }
	
	if(Get_BusClock() > 90000000u)	
	{
		FLASH_SetReadWait(FLASH_READWAIT_5CYCLE);
	}
	else if(Get_BusClock() > 60000000u)
	{
		FLASH_SetReadWait(FLASH_READWAIT_4CYCLE);
	}
	else if(Get_BusClock() > 30000000u)
	{
		FLASH_SetReadWait(FLASH_READWAIT_3CYCLE);
	}
	else
	{
		FLASH_SetReadWait(FLASH_READWAIT_2CYCLE);
	}
		
}
/**
 * @brief 外部旁路低功耗
 * @param  ICSx: 指向ICS外设
 * @param  FactorValue: 倍频系数
 *			@arg ICS_FLLFactorSelect1280 ：1280倍频
 *			@arg ICS_FLLFactorSelect1920 ：1920倍频
 * @retval None
 */
void SystemSetFBELP(void)
{
	OSC_InitTypeDef sOSC_InitTypeDef;
	
	OSC_EnableCmd(DISABLE);
	
	sOSC_InitTypeDef.OSC_ModeSelect = OSC_HG_MODE;
	sOSC_InitTypeDef.OSC_OutputSelect = OSC_OSCCILLATOR_COLOR;
	sOSC_InitTypeDef.OSC_RangeSelect = OSC_RANGE_HIGH;
	OSC_Init(&sOSC_InitTypeDef);
	OSC_EnableCmd(ENABLE);
	while(0u != OSC_GetInitStatus()){};
	
	/*选择ICS为外部基准时钟*/
	ICS_ClocksSelect(ICS_CLOCKS_OSC);
	
	/*选择IREFS在stop模式下不停止使能*/
	ICS_IREFStopEnableCmd(ENABLE);
	
	/*FLL is must close in stop mode*/
	ICS_FllStopModeCloseEnableCmd(ENABLE);
}


/**
 * @brief 获取FLLOutCLK输出的时钟频率
 * @param  None
 * @retval FLL输出的时钟频率
 */
static uint32_t Get_FllOutClock(void)
{
	uint32_t FLL_OutClock;
	uint32_t rdiv_flag;
	uint32_t rdiv2_flag;
	uint32_t rdiv_value;
	if(ICS_IREFS_IRC == ICS_GetIREFSSelect())//内部时钟源
	{
		if(ICS_IRC_37o5K == ICS_GetIRCFre())
		{
			if(ICS_FLLFACTOR_1920 == ICS_GetFLLMultiple())
			{
				FLL_OutClock = 37500 * 1920;
			}
			else
			{
				FLL_OutClock = 37500 * 1280;
			}
		}
		else
		{
			if(ICS_FLLFACTOR_1920 == ICS_GetFLLMultiple())
			{
				FLL_OutClock = 50000 * 1920;
			}
			else
			{
				FLL_OutClock = 50000 * 1280;
			}
		}
	}
	else//外部时钟
	{
		rdiv_flag = ICS_GetBaseDivider();
		rdiv2_flag = ICS_GetBaseDivider2();
		if(OSC_RANGE_HIGH == OSC_GetRange())
		{
			rdiv_value = (uint32_t)((uint32_t)1u<<(rdiv_flag+5u));
		}
		else
		{
			rdiv_value = (uint32_t)((uint32_t)1u<<(rdiv_flag));
		}
		rdiv_value = rdiv_value*rdiv2_flag;
		if(ICS_FLLFACTOR_1920 == ICS_GetFLLMultiple())
		{
			FLL_OutClock = (OSC_ClockSource/rdiv_value) * 1920u;
		}
		else
		{
			FLL_OutClock = (OSC_ClockSource/rdiv_value) * 1280u;
		}
	}
	return FLL_OutClock;
}

/**
 * @brief 获取IcsOutCLK输出的时钟频率
 * @param  None
 * @retval FLL输出的时钟频率
 */
uint32_t Get_ICSOUTClock(void)
{
	uint8_t bdiv_value;
	uint32_t fll_outfre;
	fll_outfre = Get_FllOutClock();
	bdiv_value = ICS_GetBusDivder();
	
	return (fll_outfre/((uint32_t)bdiv_value+1u));
}

/**
 * @brief 获取输入到Core的时钟频率
 * @param  None
 * @retval 输入到Core的时钟频率
 */
uint32_t Get_SystemCoreClock(void)
{
	uint32_t ics_outclk;
	uint8_t outdiv1_value;
	
	ics_outclk = Get_ICSOUTClock();
	
	outdiv1_value = SIM_GetOUTDIV1();
	
	return (ics_outclk/((uint32_t)outdiv1_value+1u));
}

/**
 * @brief 获取输入到FTM和PWT的时钟频率
 * @param  None
 * @retval 输入到FTM和PWT的时钟频率
 */
uint32_t Get_FTM_PWT_Clock(void)
{
	uint32_t ics_outclk;
	uint8_t outdiv4_value;
	
	ics_outclk = Get_ICSOUTClock();
	
	outdiv4_value = SIM_GetOUTDIV4();
	
	return (ics_outclk/((uint32_t)outdiv4_value+1u));
}
/**
 * @brief 获取输入到BUS和Flash的时钟频率
 * @param  None
 * @retval 输入到BUS和Flash的时钟频率
 */
uint32_t Get_BusClock(void)
{
	uint32_t core_clk;
	uint8_t outdiv2_value;
	
	core_clk = Get_SystemCoreClock();
	
//	if(core_clk > 50000000)
//	{
//		 SIM_CLKDIV_OUTDIV2(2);
//	}
	
	outdiv2_value = SIM_GetOUTDIV2();
	
	return (core_clk/((uint32_t)outdiv2_value+1u));
}
/**
 * @brief 获取输入到外设的时钟频率
 * @param  None
 * @retval 输入到外设的时钟频率
 */
uint32_t Get_PeripheralClock(void)
{
	uint32_t bus_clk;
	uint8_t outdiv3_value;
	
	bus_clk = Get_BusClock();

	
	
	outdiv3_value = SIM_GetOUTDIV3();
	
	return (bus_clk/((uint32_t)outdiv3_value+1u));
}


