/**
  ******************************************************************************
  * @file     xl_adc.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the ADC 
  *           firmware library.
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
#ifndef XL_ADC_H__
#define XL_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif
	
/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
	
	
/* Register define ------------------------------------------------------------*/
/* CR Bit Fields */
#define ADC_CR_MODE_MASK                        0x3u
#define ADC_CR_MODE_SHIFT                       0

#define ADC_CR_FSE_MASK                         0x4u
#define ADC_CR_FSE_SHIFT                        2

#define ADC_CR_FDEP_MASK                        0x38u
#define ADC_CR_FDEP_SHIFT                       3

#define ADC_CR_CCE_MASK                         0x40u
#define ADC_CR_CCE_SHIFT                        6

#define ADC_CR_AIE_MASK                         0x80u
#define ADC_CR_AIE_SHIFT                        7

#define ADC_CR_TRGSEL_MASK                      0x100u
#define ADC_CR_TRGSEL_SHIFT                     8

#define ADC_CR_COSBEN_MASK                      0x200u
#define ADC_CR_COSBEN_SHIFT                     9

#define ADC_CR_LPE_MASK                         0x400u
#define ADC_CR_LPE_SHIFT                        10

#define ADC_CR_LSTE_MASK                        0x800u
#define ADC_CR_LSTE_SHIFT                       11

#define ADC_CR_REFSEL_MASK                      0x3000u
#define ADC_CR_REFSEL_SHIFT                     12

#define ADC_CR_CLKSEL_MASK                      0xC000u
#define ADC_CR_CLKSEL_SHIFT                     14

#define ADC_CR_CFE_MASK                         0x10000u
#define ADC_CR_CFE_SHIFT                        16

#define ADC_CR_CFRE_MASK                        0x20000u
#define ADC_CR_CFRE_SHIFT                       17

#define ADC_CR_CFGRE_MASK                       0x40000u
#define ADC_CR_CFGRE_SHIFT                      18

#define ADC_CR_CFSEL_MASK                       0x80000u
#define ADC_CR_CFSEL_SHIFT                      19

#define ADC_CR_ADACKS_MASK                      0x100000u
#define ADC_CR_ADACKS_SHIFT                     20

#define ADC_CR_ECOBD_MASK                      0x200000u
#define ADC_CR_ECOBD_SHIFT                     21

#define ADC_CR_DMATXEN_MASK                     0x400000u
#define ADC_CR_DMATXEN_SHIFT                    22

#define ADC_CR_DMARXEN_MASK                     0x800000u
#define ADC_CR_DMARXEN_SHIFT                    23

#define ADC_CR_ADIV_MASK                        0x3000000u
#define ADC_CR_ADIV_SHIFT                       24

/* SR Bit Fields */
#define ADC_SR_RFCNT_MASK                       0xFu
#define ADC_SR_RFCNT_SHIFT                      0

#define ADC_SR_RFF_MASK                         0x10u
#define ADC_SR_RFF_SHIFT                        4

#define ADC_SR_REF_MASK                         0x20u
#define ADC_SR_REF_SHIFT                        5

#define ADC_SR_CCF_MASK                         0x80u
#define ADC_SR_CCF_SHIFT                        7

#define ADC_SR_CB_MASK                          0x100u
#define ADC_SR_CB_SHIFT                         8

#define ADC_SR_CFF_MASK                         0x200u
#define ADC_SR_CFF_SHIFT                        9

#define ADC_SR_CEF_MASK                         0x400u
#define ADC_SR_CEF_SHIFT                        10

/* CSR Bit Fields */
#define ADC_CSR_ADCH_MASK                       0x1Fu
#define ADC_CSR_ADCH_SHIFT                      0
/* RDR Bit Fields */
#define ADC_RDR_DATA_MASK                       0xFFFu
#define ADC_RDR_DATA_SHIFT                      0
/* CVR Bit Fields */
#define ADC_CVR_CVL_MASK                        0xFFFu
#define ADC_CVR_CVL_SHIFT                       0

#define ADC_CVR_CVH_MASK                        0xFFF0000u
#define ADC_CVR_CVH_SHIFT                       16
/* EHTMR Bit Fields */
#define ADC_EHTMR_EN_MASK                       0x1u
#define ADC_EHTMR_EN_SHIFT                      0

#define ADC_EHTMR_HTRGM_MASK                    0x2u
#define ADC_EHTMR_HTRGM_SHIFT                   1
/* APCTL Bit Fields */
#define ADC_PINSEL_ADPC_MASK                    0xFFFFFFu
#define ADC_PINSEL_ADPC_SHIFT                   0


/** ADC - Register Layout Typedef
 * (1-269)20.3 ADC 存储器映像和寄存器定义*/
typedef struct {
  __IO uint32_t CR;                               /*!< (1-270)20.3.1 ADC 控制寄存器 (CR), offset: 0x0 */
  __I  uint32_t SR;                               /*!< (1-273)20.3.2 ADC 状态寄存器 (SR), offset: 0x4 */
  __IO uint32_t CSR;                              /*!< (1-275)20.3.3 数据通道选择寄存器 (CSR), offset: 0x8 */
  __I  uint32_t RDR;                              /*!< (1-176)20.3.4 转换结果输出寄存器 (RDR), offset: 0xC */
  __IO uint32_t CVR;                              /*!< (1-277)20.3.5 转换结果比较标准值寄存器(CVR), offset: 0x10 */
  __IO uint32_t EHTMR;                            /*!< ADC使能与触发控制寄存器, offset: 0x14 */   
  __IO uint32_t APCTL;                            /*!< ADC使能与触发控制寄存器, offset: 0x18 */
  __IO uint32_t CFR;                              /*!< ADC比较功能状态寄存器, offset: 0x1C */
} ADC_Type, *ADC_MemMapPtr;
extern ADC_Type* ADC0;



/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup ADC 
  * @{
  */


/* Exported types ------------------------------------------------------------*/ 

/**
 * @brief ADC 初始化结构体定义
 */
typedef struct
{
  uint32_t ADC_Mode;                       /*!< 配置ADC转换数据宽度 */
                                                
  uint32_t ADC_ReferVoltage;               /*!< 转换参考电压源 */
	
  uint32_t ADC_ClockSource;                /*!< ADC转换时钟源 */
	
  uint32_t ADC_ClkDivide;                  /*!< ADC转换时钟分频系数 */

  FunctionalState ADC_LowPowerConvert;     /*!< ADC低功耗转换使能,设置成ENABLE或者DISABLE */
                                               

  FunctionalState ADC_LongTimeConvert;     /*!< ADC长采样时间使能, 设置成ENABLE或者DISABLE */
                                              

}ADC_InitTypeDef;


/**
  * @brief ADC_FIFO初始化结构体定义
  * NOTE: 20.4.7 FIFO 操作
  */
typedef struct
{
  uint32_t ADC_FIFOLevel;                   /*!< FIFO 深度 */                                              
	
  FunctionalState ADC_ChannelScan;          /*!< ADC信道扫描功能使能, 设置成ENABLE或者DISABLE */
                                              
}ADC_FIFOTypeDef;


/**
  * @brief ADC比较器初始化结构体定义
  */
typedef struct
{
	uint32_t ADC_CompareMode;                 /*!< ADC比较方式 ，大小或范围比较 */
											   
	uint32_t ADC_CompareOut;                  /*!< ADC比较输出模式 */

	uint32_t ADC_FIFOCompareOut;              /*!< ADC FIFO 比较输出模式 */

	uint32_t ADC_CompareValueHigh;            /*!< 比较值为高 */

	uint32_t ADC_CompareValueLow;             /*!< 比较值为低 */

	FunctionalState ADC_AutoCompare;          /*!< 自动比较功能使能,设置成ENABLE或者DISABLE */
	
	FunctionalState ADC_CompareResultSwitch;  /*!< 比较结果转换,设置成ENABLE或者DISABLE */

}ADC_CompareTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup ADC_Exported_Constants ADC模块使用参数定义
  * @{
  */

/**
	* @defgroup ADC_Mode_list ADC模式定义
	* @{
	*/
#define ADC_MODE_8BIT									  		0x0		/*!< 8位输出模式 */
#define ADC_MODE_10BIT											0x1		/*!< 10位输出模式 */
#define ADC_MODE_12BIT											0x2		/*!< 12位输出模式 */
/**
	* @}
	*/

/**
	* @defgroup ADC_FIFO_list ADCFIFO深度定义
	* @{
	*/	
#define ADC_FIFO_DISABLE                		0     /*!< FIFO功能关闭 */
#define ADC_FIFO_LEVEL2                 		1     /*!< FIFO深度为2 */
#define ADC_FIFO_LEVEL3                 		2     /*!< FIFO深度为3 */
#define ADC_FIFO_LEVEL4                 		3     /*!< FIFO深度为4 */
#define ADC_FIFO_LEVEL5                 		4     /*!< FIFO深度为5 */
#define ADC_FIFO_LEVEL6                 		5     /*!< FIFO深度为6 */
#define ADC_FIFO_LEVEL7                 		6     /*!< FIFO深度为7 */
#define ADC_FIFO_LEVEL8                 		7	    /*!< FIFO深度为8 */
/**
	* @}
	*/
	
/**
	* @defgroup ADC_CONTINUOUS_list ADC转换模式定义
	* @{
	*/
#define ADC_CONVENTION_ONCE              		0x00u   /*!< 单次转换 */
#define ADC_CONVENTION_CONTINUOUS        		0x01u   /*!< 连续转换 */
/**
	* @}
	*/
	
/**
	* @defgroup ADC_Trigger_List ADC触发模式选择
	* @{
	*/
#define ADC_SOFTWARE_TRIGGER             		0x00u   /*!< 软件触发 */
#define ADC_HARDWARE_TRIGGER             		0x01u   /*!< 硬件触发 */
/**
	* @}
	*/

/**
	* @defgroup ADC_VRFF_List ADC参考电压定义
	* @{
	*/
#define ADC_VREF_VREFH                   		0x00		/*!< 参考电压是VREFH */
#define ADC_VREF_VDDA                    		0x01		/*!< 参考电压是VDDA */
/**
	* @}
	*/
	

	
/**
	* @defgroup ADC_ClockSource_list ADC时钟源定义
	* @{
	*/
#define ADC_CLOCK_BUS_CLOCK							 		0x00	              /*!< ADC时钟源是总线时钟 */
#define ADC_CLOCK_BUS_CLOCK_DIVIDE_2	   		            0x01	  /*!< ADC时钟源是总线时钟2分频 */
#define ADC_CLOCK_ALTCLK							   		0x02	              /*!< ADC时钟源是备用时钟(ALTCLK) */
#define ADC_CLOCK_ADACK								   		0x03	              /*!< ADC时钟源是异步时钟(ADACK) */
/**
	* @}
	*/
	
/**
	* @defgroup ADC_CPMPARE_List ADC比较模式定义
	* @{
	*/	
#define ADC_COMPAREMODE_SIZE              	0x00   /*!< ADC大小比较 */
#define ADC_COMPAREMODE_RANGE             	0x01   /*!< ADC范围比较 */
/**
	* @}
	*/

/**
	* @defgroup ADC_CPMPARE_out_list ADC比较输出模式定义
	* @{
	*/	
#define ADC_COMPAREOUT_LESS              		0x00   /*!< 小于等于或者在范围内输出转换结果 */
#define ADC_COMPAREOUT_MORE              		0x01   /*!<  大于或者在范围外输出转换结果 */
/**
	* @}
	*/

/** 
	* @defgroup ADC_OutputSelect_List ADC比较输出数据模式定义
	* @{
	*/	
#define ADC_COMPAREFIFO_ALL              		0x00   /*!< 当所有通道都满足比较结果时，输出本次扫描结果 */
#define ADC_COMPAREFIFO_ONE              		0x01   /*!< 只要某一个通道满足比较结果时，输出本次扫描结果 */
/**
	* @}
	*/
	
/**
	* @defgroup ADC_AsynchronousClk_Select_List ADC异步时钟选择定义
	* @{
	*/	
#define ADC_ADACK_NORMAL                   0x00u   /*!< ADC异步时钟使用标准频率 */
#define ADC_ADACK_TIMES1P5                 0x01u   /*!< ADC异步时钟使用1.5倍标准频率 */
/**
	* @}
	*/
	
/**
	* @defgroup ADC_Deivied_List ADC时钟分频选择
	* @{
	*/		
#define ADC_ADIV_DIVIDE_1							   		0x00		/*!< 时钟1分频 */
#define ADC_ADIV_DIVIDE_2								 		0x01		/*!< 时钟2分频 */
#define ADC_ADIV_DIVIDE_4								 		0x02		/*!< 时钟4分频 */
#define ADC_ADIV_DIVIDE_8								 		0x03		/*!< 时钟8分频 */
/**
	* @}
	*/
	
/**
	* @defgroup ADC_Flags_Definition ADC比较功能状态标志定义
	* @{
	*/
#define ADC_FLAG_DATAFIFO_FULL           		0x10     /*!< FIFO数据满标志 */
#define ADC_FLAG_DATAFIFO_EMPTY          		0x20     /*!< FIFO数据空标志 */
#define ADC_FLAG_CONV_FINISH             		0x80     /*!< ADC转换结束标志 */
#define ADC_FLAG_CONV_BUSY               		0x100    /*!< ADC转换繁忙标志 */
#define ADC_FLAG_ChannelFIFO_FULL        		0x200    /*!< Channel FIFO数据满标志 */
#define ADC_FLAG_ChannelFIFO_EMPTY       		0x400    /*!< Channel FIFO数据空标志 */
/**
	* @}
	*/

/**
	* @defgroup ADC_COMPARE_FLAGs_Definition ADC标志定义
	* @{
	*/
#define ADC_CHANNEL0_COMPARE_EXCEPTION			0x000001			/*!< 通道0比较结果异常标志 */
#define ADC_CHANNEL1_COMPARE_EXCEPTION			0x000002			/*!< 通道1比较结果异常标志 */
#define ADC_CHANNEL2_COMPARE_EXCEPTION			0x000004			/*!< 通道2比较结果异常标志 */
#define ADC_CHANNEL3_COMPARE_EXCEPTION			0x000008			/*!< 通道3比较结果异常标志 */
#define ADC_CHANNEL4_COMPARE_EXCEPTION			0x000010			/*!< 通道4比较结果异常标志 */
#define ADC_CHANNEL5_COMPARE_EXCEPTION			0x000020			/*!< 通道5比较结果异常标志 */
#define ADC_CHANNEL6_COMPARE_EXCEPTION			0x000040			/*!< 通道6比较结果异常标志 */
#define ADC_CHANNEL7_COMPARE_EXCEPTION			0x000080			/*!< 通道7比较结果异常标志 */
#define ADC_CHANNELALL_COMPARE_EXCEPTION		0x000100			/*!< 所有通道比较结果异常标志 */
#define ADC_COMPARE_CFSEL_FLAG					0x010000			    /*!< 输出结果选择方式标志 */
#define ADC_COMPARE_CFGRE_FLAG					0x020000			    /*!< 大于选择标志 */
#define ADC_COMPARE_CFRE_FLAG					0x040000			      /*!< 比较方式选择标志 */
#define ADC_COMPARE_CFE_FLAG					0x080000			      /*!< 自动比较功能使能标志 */
/**
	* @}
	*/


/**
	* @defgroup ADC_Channel_list ADC通道选择定义
	* @{
	*/
#define ADC_CHANNEL_AD0                  		0x0     /*!< ADC输入通道0 */
#define ADC_CHANNEL_AD1                  		0x1     /*!< ADC输入通道1 */
#define ADC_CHANNEL_AD2                  		0x2     /*!< ADC输入通道2 */
#define ADC_CHANNEL_AD3                  		0x3     /*!< ADC输入通道3 */
#define ADC_CHANNEL_AD4                  		0x4     /*!< ADC输入通道4 */
#define ADC_CHANNEL_AD5                  		0x5     /*!< ADC输入通道5 */
#define ADC_CHANNEL_AD6                  		0x6     /*!< ADC输入通道6 */
#define ADC_CHANNEL_AD7                  		0x7     /*!< ADC输入通道7 */
#define ADC_CHANNEL_AD8                  		0x8     /*!< ADC输入通道8 */
#define ADC_CHANNEL_AD9                  		0x9     /*!< ADC输入通道9 */
#define ADC_CHANNEL_AD10                 		0xa     /*!< ADC输入通道10 */
#define ADC_CHANNEL_AD11                 		0xb     /*!< ADC输入通道11 */
#define ADC_CHANNEL_AD12                 		0xc     /*!< ADC输入通道12 */
#define ADC_CHANNEL_AD13                 		0xd     /*!< ADC输入通道13 */
#define ADC_CHANNEL_AD14                 		0xe     /*!< ADC输入通道14 */
#define ADC_CHANNEL_AD15                 		0xf     /*!< ADC输入通道15 */
#define ADC_CHANNEL_AD16                 		0x10    /*!< ADC输入通道16 */
#define ADC_CHANNEL_AD17                 		0x11    /*!< ADC输入通道17 */
#define ADC_CHANNEL_AD18                 		0x12    /*!< ADC输入通道18 */
#define ADC_CHANNEL_AD19                 		0x13    /*!< ADC输入通道19 */
#define ADC_CHANNEL_AD20                 		0x14    /*!< ADC输入通道20 */ 
#define ADC_CHANNEL_AD21                 		0x15    /*!< ADC输入通道21 */ 
#define ADC_CHANNEL_TEMPSENSOR           		0x16    /*!< ADC输入通道内部温度传感器 */
#define ADC_CHANNEL_BANDGAP              		0x17    /*!< ADC采样基准电压 */ 
#define ADC_CHANNEL_AD22                 		0x18    /*!< ADC输入通道22 */ 
#define ADC_CHANNEL_AD23                 		0x19    /*!< ADC输入通道23 */ 
#define ADC_CHANNEL_VSS                  		0x1A    /*!< ADC输入通道VSS */ 
#define ADC_CHANNEL_VREFH                		0x1D    /*!< ADC输入通道Vrefh */ 
#define ADC_CHANNEL_VREFL                		0x1E    /*!< ADC输入通道Vrefl */ 
#define ADC_CHANNEL_DISABLE              		0x1F    /*!< ADC失能 */
/**
	* @}
	*/

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void ADC_DeInit(ADC_Type* ADCx);
void ADC_Init(ADC_Type* ADCx, const ADC_InitTypeDef* ADC_InitStruct);
void ADC_FIFOConfig(ADC_Type* ADCx, const ADC_FIFOTypeDef* ADC_FIFOStruct);
void ADC_CompareConfig(ADC_Type* ADCx, const ADC_CompareTypeDef* ADC_CompareStruct);
void ADC_EnableCmd(ADC_Type* ADCx, FunctionalState NewState);
void ADC_HardwareTriggrMaskCmd(ADC_Type* ADCx, FunctionalState NewState);
void ADC_SetTriggerMode(ADC_Type* ADCx, uint8_t ADC_Triggermode);
void ADC_ADACKSelect(ADC_Type* ADCx, uint8_t ADC_ADACKmode);
void ADC_SetConventionMode(ADC_Type* ADCx, uint8_t ADC_ConventionMode);
void ADC_SetChannel(ADC_Type* ADCx, uint8_t channelno);
void ADC_InterruptEn(ADC_Type* ADCx, FunctionalState NewState);
void ADC_DMATxEn(ADC_Type* ADCx, FunctionalState NewState);
void ADC_DMARxEn(ADC_Type* ADCx, FunctionalState NewState);
uint16_t ADC_GetConversionValue(const ADC_Type* ADCx);
uint16_t ADC_GetFIFOValueCounter(const ADC_Type* ADCx);
FlagStatus ADC_GetFlagStatus(const ADC_Type* ADCx, uint16_t ADC_FLAG);
FlagStatus ADC_GetCompareFlagStatus(const ADC_Type* ADCx, uint16_t ADC_COMPARE_FLAG);
void ADC_DisableChannelDigFuc(ADC_Type* ADCx, uint8_t channelno, FunctionalState NewState);


#ifdef __cplusplus
}
#endif

#endif    /*__XL_ADC_H__ */
/**
  * @}
  */

/**
  * @}
  */

