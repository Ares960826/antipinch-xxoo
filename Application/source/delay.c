#include "delay.h"
#include "xl_ics.h"
#include "xl_osc.h"
#include "xl_nvic.h"	
#include "system_xl6600.h"

static uint8_t  fac_us=0;							//us延时倍乘数	

/**
	* @param SysTick 使能定义
*/
#define SysTick_CTRL_ENABLE_Pos             0U                                            /*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Msk            (1UL /*<< SysTick_CTRL_ENABLE_Pos*/)           /*!< SysTick CTRL: ENABLE Mask */

/**
	* @param SysTick 中断使能定义
*/
#define SysTick_CTRL_TICKINT_Pos            1U                                            /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */

/**
 * @brief  Core系统时钟的初始化
 * @param  None
 * @return None
 */ 
void Systick_Init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); 
	fac_us=Get_SystemCoreClock()/1000000;	
}

#if 0
/**
 * @brief  SysTick中断函数
 * @param  None
 * @return None
 */
void SysTick_Handler(void)
{	

}
#endif

/**
 * @brief  微秒级延时
 * @param  nus  延时的时间
 * @return None
 */ 
void Delay_us(uint32_t nus)
{
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; 				//时间加载	  		 
	SysTick->VAL=0x00;        				//清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ; //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL&=~ SysTick_CTRL_ENABLE_Msk; //关闭计数器
	SysTick->VAL =0X00;       				//清空计数器 
}


/**
 * @brief  毫秒级延时
 * @param  nms  延时的时间
 * @return None
 */ 
void Delay_ms(uint32_t nms)
{
	uint32_t i;
	for(i=0;i<nms;i++) Delay_us(1000);
}



