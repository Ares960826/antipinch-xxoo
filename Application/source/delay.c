#include "delay.h"
#include "xl_ics.h"
#include "xl_osc.h"
#include "xl_nvic.h"	
#include "system_xl6600.h"

static uint8_t  fac_us=0;							//us��ʱ������	

/**
	* @param SysTick ʹ�ܶ���
*/
#define SysTick_CTRL_ENABLE_Pos             0U                                            /*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Msk            (1UL /*<< SysTick_CTRL_ENABLE_Pos*/)           /*!< SysTick CTRL: ENABLE Mask */

/**
	* @param SysTick �ж�ʹ�ܶ���
*/
#define SysTick_CTRL_TICKINT_Pos            1U                                            /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */

/**
 * @brief  Coreϵͳʱ�ӵĳ�ʼ��
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
 * @brief  SysTick�жϺ���
 * @param  None
 * @return None
 */
void SysTick_Handler(void)
{	

}
#endif

/**
 * @brief  ΢�뼶��ʱ
 * @param  nus  ��ʱ��ʱ��
 * @return None
 */ 
void Delay_us(uint32_t nus)
{
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; 				//ʱ�����	  		 
	SysTick->VAL=0x00;        				//��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ; //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~ SysTick_CTRL_ENABLE_Msk; //�رռ�����
	SysTick->VAL =0X00;       				//��ռ����� 
}


/**
 * @brief  ���뼶��ʱ
 * @param  nms  ��ʱ��ʱ��
 * @return None
 */ 
void Delay_ms(uint32_t nms)
{
	uint32_t i;
	for(i=0;i<nms;i++) Delay_us(1000);
}



