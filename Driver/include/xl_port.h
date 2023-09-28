/**
  ******************************************************************************
  * @file     xl_port.h
  * @author   software group
  * @brief    This file contains all the functions prototypes for the PORT 
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
	
/* Define to prevent recursive inclusion -------------------------------------*/	  
#ifndef XL_PORT_H
#define XL_PORT_H

#ifdef __cplusplus
extern "C"{
#endif
/* Includes ---------------------------------------------------------------*/
#include "XL6600.h"
	
/* Register define ------------------------------------------------------------*/

/* IOFLT0 Bit Fields */
#define PORT_IOFLT0_FLTA_MASK                    0x3u
#define PORT_IOFLT0_FLTA_SHIFT                   0
#define PORT_IOFLT0_FLTB_MASK                    0xCu
#define PORT_IOFLT0_FLTB_SHIFT                   2
#define PORT_IOFLT0_FLTC_MASK                    0x30u
#define PORT_IOFLT0_FLTC_SHIFT                   4
#define PORT_IOFLT0_FLTD_MASK                    0xC0u
#define PORT_IOFLT0_FLTD_SHIFT                   6
#define PORT_IOFLT0_FLTE_MASK                    0x300u
#define PORT_IOFLT0_FLTE_SHIFT                   8
#define PORT_IOFLT0_FLTF_MASK                    0xC00u
#define PORT_IOFLT0_FLTF_SHIFT                   10
#define PORT_IOFLT0_FLTG_MASK                    0x3000u
#define PORT_IOFLT0_FLTG_SHIFT                   12
#define PORT_IOFLT0_FLTH_MASK                    0xC000u
#define PORT_IOFLT0_FLTH_SHIFT                   14
#define PORT_IOFLT0_FLTRST_MASK                  0x30000u
#define PORT_IOFLT0_FLTRST_SHIFT                 16
#define PORT_IOFLT0_FLTKBI0_MASK                 0xC0000u
#define PORT_IOFLT0_FLTKBI0_SHIFT                18
#define PORT_IOFLT0_FLTKBI1_MASK                 0x300000u
#define PORT_IOFLT0_FLTKBI1_SHIFT                20
#define PORT_IOFLT0_FLTNMI_MASK                  0xC00000u
#define PORT_IOFLT0_FLTNMI_SHIFT                 22
#define PORT_IOFLT0_FLTDIV1_MASK                 0x3000000u
#define PORT_IOFLT0_FLTDIV1_SHIFT                24
#define PORT_IOFLT0_FLTDIV2_MASK                 0x1C000000u
#define PORT_IOFLT0_FLTDIV2_SHIFT                26
#define PORT_IOFLT0_FLTDIV3_MASK                 0xE0000000u
#define PORT_IOFLT0_FLTDIV3_SHIFT                29
/* IOFLT1 Bit Fields */
#define PORT_IOFLT1_FLTI_MASK                    0x3u
#define PORT_IOFLT1_FLTI_SHIFT                   0
#define PORT_IOFLT1_FLTIRQ_MASK                  0x30u
#define PORT_IOFLT1_FLTIRQ_SHIFT                 4
#define PORT_IOFLT1_FLTFTM0_MASK                 0xC0u
#define PORT_IOFLT1_FLTFTM0_SHIFT                6
#define PORT_IOFLT1_FLTFTM1_MASK                 0x300u
#define PORT_IOFLT1_FLTFTM1_SHIFT                8
#define PORT_IOFLT1_FLTPWT_MASK                  0xC00u
#define PORT_IOFLT1_FLTPWT_SHIFT                 10
#define PORT_IOFLT1_FLTI2C0_MASK                 0x3000u
#define PORT_IOFLT1_FLTI2C0_SHIFT                12
#define PORT_IOFLT1_FLTI2C1_MASK                 0xC000u
#define PORT_IOFLT1_FLTI2C1_SHIFT                14
#define PORT_IOFLT1_FLTEWM_MASK                  0x30000u
#define PORT_IOFLT1_FLTEWM_SHIFT                 16
/* PUE0 Bit Fields */
#define PORT_PUE0_PTAPE0_MASK                    0x1u
#define PORT_PUE0_PTAPE0_SHIFT                   0
#define PORT_PUE0_PTAPE1_MASK                    0x2u
#define PORT_PUE0_PTAPE1_SHIFT                   1
#define PORT_PUE0_PTAPE2_MASK                    0x4u
#define PORT_PUE0_PTAPE2_SHIFT                   2
#define PORT_PUE0_PTAPE3_MASK                    0x8u
#define PORT_PUE0_PTAPE3_SHIFT                   3
#define PORT_PUE0_PTAPE4_MASK                    0x10u
#define PORT_PUE0_PTAPE4_SHIFT                   4
#define PORT_PUE0_PTAPE5_MASK                    0x20u
#define PORT_PUE0_PTAPE5_SHIFT                   5
#define PORT_PUE0_PTAPE6_MASK                    0x40u
#define PORT_PUE0_PTAPE6_SHIFT                   6
#define PORT_PUE0_PTAPE7_MASK                    0x80u
#define PORT_PUE0_PTAPE7_SHIFT                   7

#define PORT_PUE0_PTBPE0_MASK                    0x100u
#define PORT_PUE0_PTBPE0_SHIFT                   8
#define PORT_PUE0_PTBPE1_MASK                    0x200u
#define PORT_PUE0_PTBPE1_SHIFT                   9
#define PORT_PUE0_PTBPE2_MASK                    0x400u
#define PORT_PUE0_PTBPE2_SHIFT                   10
#define PORT_PUE0_PTBPE3_MASK                    0x800u
#define PORT_PUE0_PTBPE3_SHIFT                   11
#define PORT_PUE0_PTBPE4_MASK                    0x1000u
#define PORT_PUE0_PTBPE4_SHIFT                   12
#define PORT_PUE0_PTBPE5_MASK                    0x2000u
#define PORT_PUE0_PTBPE5_SHIFT                   13
#define PORT_PUE0_PTBPE6_MASK                    0x4000u
#define PORT_PUE0_PTBPE6_SHIFT                   14
#define PORT_PUE0_PTBPE7_MASK                    0x8000u
#define PORT_PUE0_PTBPE7_SHIFT                   15

#define PORT_PUE0_PTCPE0_MASK                    0x10000u
#define PORT_PUE0_PTCPE0_SHIFT                   16
#define PORT_PUE0_PTCPE1_MASK                    0x20000u
#define PORT_PUE0_PTCPE1_SHIFT                   17
#define PORT_PUE0_PTCPE2_MASK                    0x40000u
#define PORT_PUE0_PTCPE2_SHIFT                   18
#define PORT_PUE0_PTCPE3_MASK                    0x80000u
#define PORT_PUE0_PTCPE3_SHIFT                   19
#define PORT_PUE0_PTCPE4_MASK                    0x100000u
#define PORT_PUE0_PTCPE4_SHIFT                   20
#define PORT_PUE0_PTCPE5_MASK                    0x200000u
#define PORT_PUE0_PTCPE5_SHIFT                   21
#define PORT_PUE0_PTCPE6_MASK                    0x400000u
#define PORT_PUE0_PTCPE6_SHIFT                   22
#define PORT_PUE0_PTCPE7_MASK                    0x800000u
#define PORT_PUE0_PTCPE7_SHIFT                   23
#define PORT_PUE0_PTDPE0_MASK                    0x1000000u
#define PORT_PUE0_PTDPE0_SHIFT                   24
#define PORT_PUE0_PTDPE1_MASK                    0x2000000u
#define PORT_PUE0_PTDPE1_SHIFT                   25
#define PORT_PUE0_PTDPE2_MASK                    0x4000000u
#define PORT_PUE0_PTDPE2_SHIFT                   26
#define PORT_PUE0_PTDPE3_MASK                    0x8000000u
#define PORT_PUE0_PTDPE3_SHIFT                   27
#define PORT_PUE0_PTDPE4_MASK                    0x10000000u
#define PORT_PUE0_PTDPE4_SHIFT                   28
#define PORT_PUE0_PTDPE5_MASK                    0x20000000u
#define PORT_PUE0_PTDPE5_SHIFT                   29
#define PORT_PUE0_PTDPE6_MASK                    0x40000000u
#define PORT_PUE0_PTDPE6_SHIFT                   30
#define PORT_PUE0_PTDPE7_MASK                    0x80000000u
#define PORT_PUE0_PTDPE7_SHIFT                   31
/* PUE1 Bit Fields */
#define PORT_PUE1_PTEPE0_MASK                    0x1u
#define PORT_PUE1_PTEPE0_SHIFT                   0
#define PORT_PUE1_PTEPE1_MASK                    0x2u
#define PORT_PUE1_PTEPE1_SHIFT                   1
#define PORT_PUE1_PTEPE2_MASK                    0x4u
#define PORT_PUE1_PTEPE2_SHIFT                   2
#define PORT_PUE1_PTEPE3_MASK                    0x8u
#define PORT_PUE1_PTEPE3_SHIFT                   3
#define PORT_PUE1_PTEPE4_MASK                    0x10u
#define PORT_PUE1_PTEPE4_SHIFT                   4
#define PORT_PUE1_PTEPE5_MASK                    0x20u
#define PORT_PUE1_PTEPE5_SHIFT                   5
#define PORT_PUE1_PTEPE6_MASK                    0x40u
#define PORT_PUE1_PTEPE6_SHIFT                   6
#define PORT_PUE1_PTEPE7_MASK                    0x80u
#define PORT_PUE1_PTEPE7_SHIFT                   7
#define PORT_PUE1_PTFPE0_MASK                    0x100u
#define PORT_PUE1_PTFPE0_SHIFT                   8
#define PORT_PUE1_PTFPE1_MASK                    0x200u
#define PORT_PUE1_PTFPE1_SHIFT                   9
#define PORT_PUE1_PTFPE2_MASK                    0x400u
#define PORT_PUE1_PTFPE2_SHIFT                   10
#define PORT_PUE1_PTFPE3_MASK                    0x800u
#define PORT_PUE1_PTFPE3_SHIFT                   11
#define PORT_PUE1_PTFPE4_MASK                    0x1000u
#define PORT_PUE1_PTFPE4_SHIFT                   12
#define PORT_PUE1_PTFPE5_MASK                    0x2000u
#define PORT_PUE1_PTFPE5_SHIFT                   13
#define PORT_PUE1_PTFPE6_MASK                    0x4000u
#define PORT_PUE1_PTFPE6_SHIFT                   14
#define PORT_PUE1_PTFPE7_MASK                    0x8000u
#define PORT_PUE1_PTFPE7_SHIFT                   15

#define PORT_PUE1_PTGPE0_MASK                    0x10000u
#define PORT_PUE1_PTGPE0_SHIFT                   16
#define PORT_PUE1_PTGPE1_MASK                    0x20000u
#define PORT_PUE1_PTGPE1_SHIFT                   17
#define PORT_PUE1_PTGPE2_MASK                    0x40000u
#define PORT_PUE1_PTGPE2_SHIFT                   18
#define PORT_PUE1_PTGPE3_MASK                    0x80000u
#define PORT_PUE1_PTGPE3_SHIFT                   19
#define PORT_PUE1_PTGPE4_MASK                    0x100000u
#define PORT_PUE1_PTGPE4_SHIFT                   20
#define PORT_PUE1_PTGPE5_MASK                    0x200000u
#define PORT_PUE1_PTGPE5_SHIFT                   21
#define PORT_PUE1_PTGPE6_MASK                    0x400000u
#define PORT_PUE1_PTGPE6_SHIFT                   22
#define PORT_PUE1_PTGPE7_MASK                    0x800000u
#define PORT_PUE1_PTGPE7_SHIFT                   23

#define PORT_PUE1_PTHPE0_MASK                    0x1000000u
#define PORT_PUE1_PTHPE0_SHIFT                   24
#define PORT_PUE1_PTHPE1_MASK                    0x2000000u
#define PORT_PUE1_PTHPE1_SHIFT                   25
#define PORT_PUE1_PTHPE2_MASK                    0x4000000u
#define PORT_PUE1_PTHPE2_SHIFT                   26
#define PORT_PUE1_PTHPE3_MASK                    0x8000000u
#define PORT_PUE1_PTHPE3_SHIFT                   27
#define PORT_PUE1_PTHPE4_MASK                    0x10000000u
#define PORT_PUE1_PTHPE4_SHIFT                   28
#define PORT_PUE1_PTHPE5_MASK                    0x20000000u
#define PORT_PUE1_PTHPE5_SHIFT                   29
#define PORT_PUE1_PTHPE6_MASK                    0x40000000u
#define PORT_PUE1_PTHPE6_SHIFT                   30
#define PORT_PUE1_PTHPE7_MASK                    0x80000000u
#define PORT_PUE1_PTHPE7_SHIFT                   31 
/* PUE2 Bit Fields */
#define PORT_PUE2_PTIPE0_MASK                    0x1u
#define PORT_PUE2_PTIPE0_SHIFT                   0
#define PORT_PUE2_PTIPE1_MASK                    0x2u
#define PORT_PUE2_PTIPE1_SHIFT                   1
#define PORT_PUE2_PTIPE2_MASK                    0x4u
#define PORT_PUE2_PTIPE2_SHIFT                   2
#define PORT_PUE2_PTIPE3_MASK                    0x8u
#define PORT_PUE2_PTIPE3_SHIFT                   3
#define PORT_PUE2_PTIPE4_MASK                    0x10u
#define PORT_PUE2_PTIPE4_SHIFT                   4
#define PORT_PUE2_PTIPE5_MASK                    0x20u
#define PORT_PUE2_PTIPE5_SHIFT                   5
#define PORT_PUE2_PTIPE6_MASK                    0x40u
#define PORT_PUE2_PTIPE6_SHIFT                   6
/* HDRVE Bit Fields */
#define PORT_HDRVE_PTB4_MASK                     0x1u
#define PORT_HDRVE_PTB4_SHIFT                    0
#define PORT_HDRVE_PTB5_MASK                     0x2u
#define PORT_HDRVE_PTB5_SHIFT                    1
#define PORT_HDRVE_PTD0_MASK                     0x4u
#define PORT_HDRVE_PTD0_SHIFT                    2
#define PORT_HDRVE_PTD1_MASK                     0x8u
#define PORT_HDRVE_PTD1_SHIFT                    3
#define PORT_HDRVE_PTE0_MASK                     0x10u
#define PORT_HDRVE_PTE0_SHIFT                    4
#define PORT_HDRVE_PTE1_MASK                     0x20u
#define PORT_HDRVE_PTE1_SHIFT                    5
#define PORT_HDRVE_PTH0_MASK                     0x40u
#define PORT_HDRVE_PTH0_SHIFT                    6
#define PORT_HDRVE_PTH1_MASK                     0x80u
#define PORT_HDRVE_PTH1_SHIFT                    7

/** PORT - Register Layout Typedef */
typedef struct {
  __IO uint32_t IOFLT0;                            /*!< (1-130)11.7.1 端口滤波寄存器 0 (IOFLT0), offset: 0x0 */
  __IO uint32_t IOFLT1;                            /*!< (1-133)11.7.2 端口滤波寄存器 1 (IOFLT1), offset: 0x4 */
  __IO uint32_t PUE0;                              /*!< (1-135)11.7.3 端口上拉使能寄存器 0 (PUE0), offset: 0x8 */
  __IO uint32_t PUE1;                              /*!< 端口上拉使能寄存器1, offset: 0xC */
  __IO uint32_t PUE2;                              /*!< 端口上拉使能寄存器2, offset: 0x10 */
  __IO uint32_t HDRVE;                             /*!< (1-148)11.7.6 端口大电流驱动使能寄存器(HDRVE), offset: 0x14 */
} PORT_Type, *PORT_MemMapPtr;

extern PORT_Type*		PORT;

/** @addtogroup XL6600_StdPeriph_Driver
  * @{
  */

/** @addtogroup PORT 
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/** 
  * @brief PORT端口滤波器0结构体定义
  */
typedef struct 
{
		uint32_t      iofltdiv3;     /*!< 端口滤波器分组 3 */
		uint32_t      iofltdiv2;     /*!< 端口滤波器分组 2 */
		uint32_t      iofltdiv1;     /*!< 端口滤波器分组 1 */
		uint32_t      iofltnmi;      /*!< 针对 NMI 输入的滤波器选择           */
		uint32_t      iofltkbi1;     /*!< 针对 KBI1 输入的滤波器选择           */
		uint32_t      iofltkbi0;     /*!< 针对 KBI0 输入的滤波器选择           */
		uint32_t      iofltrst;      /*!< 针对 RESET 输入的滤波器选择 */
		uint32_t      iofltpth;      /*!< 针对 PTH 输入的滤波器选择 */
		uint32_t      iofltptg;      /*!< 针对 PTG 输入的滤波器选择 */
		uint32_t      iofltptf;      /*!< 针对 PTF 输入的滤波器选择 */
		uint32_t      iofltpte;      /*!< 针对 PTE 输入的滤波器选择 */
		uint32_t      iofltptd;      /*!< 针对 PTD 输入的滤波器选择 */
		uint32_t      iofltptc;      /*!< 针对 PTC 输入的滤波器选择 */
		uint32_t      iofltptb;      /*!< 针对 PTB 输入的滤波器选择 */
		uint32_t      iofltpta;      /*!< 针对 PTA 输入的滤波器选择 */

}port_ioflt0_config;

/** 
  * @brief PORT端口滤波器1结构体定义
  */
typedef struct
{
		uint16_t     ioflti2c1;     /*!< 针对 SCL1/SDA1 输入的滤波器选择  (1-123)10.3.6 通信接口=>表 10-15. I2C1 信号说明*/
		uint16_t     ioflti2c0;     /*!< 针对 SCL0/SDA0 输入的滤波器选择  (1-123)10.3.6 通信接口=>表 10-14. I2C1 信号说明*/
		uint16_t     iofltpwt;      /*!< 针对   PWT_IN1/PWT_IN0  (1-123)输入的滤波器选择 10.3.5 定时器模块=> 表 10-11. PWT 信号说明*/
		uint16_t     iofltftm1;     /*!< 针对 FTM1CH0/FTM1CH1  (1-122)输入的滤波器选择 表 10-8. FTM1 信号说明*/
		uint16_t     iofltftm0;     /*!< 针对 FTM0CH0/FTM0CH1 输入的滤波器选择 */
		uint16_t     iofltirq;      /*!< 针对   IRQ 输入的滤波器选择 (1-133)11.7.2 端口滤波寄存器 1 (IOFLT1)->FLTIRQ*/
		uint16_t     iofltpti;      /*!< 针对   PTI 输入的滤波器选择*/
}port_ioflt1_config;


/* Exported constants --------------------------------------------------------*/
/** @defgroup PORT_Exported_Constants PORT模块使用参数定义
  * @{
  */
/** @defgroup PORT_Filter_Division_3 PORT滤波器分组3设置定义
  * @{
  */
#define   	Port_FLTDIV3SetLPOCLK 			    	((uint32_t)0x00000000u)		/*!< LPOCLK */
#define		Port_FLTDIV3SetLPOCLKDiv2 		    	((uint32_t)0x20000000u)		/*!< LPOCLK/2 */
#define		Port_FLTDIV3SetLPOCLKDiv4 		    	((uint32_t)0x40000000u)		/*!< LPOCLK/4 */
#define		Port_FLTDIV3SetLPOCLKDiv8 		    	((uint32_t)0x60000000u)		/*!< LPOCLK/8 */
#define		Port_FLTDIV3SetLPOCLKDiv16 		    	((uint32_t)0x80000000u)		/*!< LPOCLK/16 */
#define		Port_FLTDIV3SetLPOCLKDiv32 		    	((uint32_t)0xA0000000u)		/*!< LPOCLK/32 */
#define		Port_FLTDIV3SetLPOCLKDiv64 	      		((uint32_t)0xC0000000u)		/*!< LPOCLK/64 */
#define		Port_FLTDIV3SetLPOCLKDiv128 		  	((uint32_t)0xE0000000u)		/*!< LPOCLK/128 */
/**
	* @}
	*/
	
/** @defgroup PORT_Filter_Division_2 PORT滤波器分组2设置定义

  * @{
  */
#define   	Port_FLTDIV2SetBUSCLKDiv32 			  	((uint32_t)0x00000000u)		/*!< BUSCLK/32 */
#define		Port_FLTDIV2SetBUSCLKDiv64 		    	((uint32_t)0x04000000u)		/*!< BUSCLK/64 */
#define		Port_FLTDIV2SetBUSCLKDiv128 		  	((uint32_t)0x08000000u)		/*!< BUSCLK/128 */
#define		Port_FLTDIV2SetBUSCLKDiv256 		  	((uint32_t)0x0C000000u)		/*!< BUSCLK/256 */
#define		Port_FLTDIV2SetBUSCLKDiv512 		  	((uint32_t)0x10000000u)		/*!< BUSCLK/512 */
#define		Port_FLTDIV2SetBUSCLKDiv1024 		  	((uint32_t)0x14000000u)		/*!< BUSCLK/1024 */
#define		Port_FLTDIV2SetBUSCLKDiv2048 		  	((uint32_t)0x18000000u)		/*!< BUSCLK/2048 */
#define		Port_FLTDIV2SetBUSCLKDiv4096 		  	((uint32_t)0x1C000000u)		/*!< BUSCLK/4096 */
/**
	* @}
	*/
	
/** @defgroup PORT_Filter_Division_1 PORT滤波器分组1设置定义
  * @{
  */
#define		Port_FLTDIV1SetBUSCLKDiv2 			((uint32_t)0x00000000)		/*!< BUSCLK/2 */
#define		Port_FLTDIV1SetBUSCLKDiv4	  		((uint32_t)0x01000000)		/*!< BUSCLK/4 */
#define		Port_FLTDIV1SetBUSCLKDiv8   		((uint32_t)0x02000000)		/*!< BUSCLK/8 */
#define		Port_FLTDIV1SetBUSCLKDiv16   		((uint32_t)0x03000000)		/*!< BUSCLK/16 */
/**
	* @}
	*/

/** @defgroup PORT_NMI_Filter_Division_Seclect PORT针对NMI输入滤波选择定义
  * @{
  */
#define		Port_FLTNMINoFilter  						((uint32_t)0x00000000)		    /*!< 无滤波器 */
#define		Port_FLTNMIFLTDIV1 	  					((uint32_t)0x00400000)		    /*!< Selects FLTDIV1, Stop 模式下自动切换到FLTDIV3 */
#define		Port_FLTNMIFLTDIV2 		 				((uint32_t)0x00800000) 		      /*!< Selects FLTDIV2, Stop 模式下自动切换到FLTDIV3 */
#define		Port_FLTNMIFLTDIV3    		  				((uint32_t)0x00C00000) 		/*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_KBI1_Filter_Division_Seclect PORT针对KBI1输入滤波选择定义
  * @{
  */
#define		Port_FLTKBI1NoFilter     					((uint32_t)0x00000000)		  /*!< 无滤波器 */
#define		Port_FLTKBI1FLTDIV1      				((uint32_t)0x00100000)		    /*!< Selects FLTDIV1, Stop 模式下自动切换到FLTDIV3 */
#define		Port_FLTKBI1FLTDIV2      				((uint32_t)0x00200000)		    /*!< Selects FLTDIV2, Stop 模式下自动切换到FLTDIV3 */
#define		Port_FLTKBI1FLTDIV3    		   				((uint32_t)0x00300000)		/*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_KBI0_Filter_Division_Seclect PORT针对KBI0输入滤波选择定义
  * @{
  */
#define		Port_FLTKBI0NoFilter     					((uint32_t)0x00000000)		/*!< 无滤波器 */
#define		Port_FLTKBI0FLTDIV1 		  				((uint32_t)0x00040000)		/*!< Selects FLTDIV1, Stop 模式下自动切换到FLTDIV3 */
#define		Port_FLTKBI0FLTDIV2	    				((uint32_t)0x00080000)		  /*!< Selects FLTDIV2, Stop 模式下自动切换到FLTDIV3 */
#define		Port_FLTKBI0FLTDIV3      		 			((uint32_t)0x000C0000)		/*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_RESET/IRQ_Filter_Division_Seclect PORT针对RESET/IRQ输入滤波选择定义
  * @{
  */
#define		Port_FLTRSTNoFilter     					((uint32_t)0x00000000)		  /*!< 无滤波器 */
#define		Port_FLTRSTFLTDIV1 	   					((uint32_t)0x00010000)		    /*!< Selects FLTDIV1, Stop 模式下自动切换到FLTDIV3 */
#define		Port_FLTRSTFLTDIV2	     				((uint32_t)0x00020000)		    /*!< Selects FLTDIV2, Stop 模式下自动切换到FLTDIV3 */
#define		Port_FLTRSTFLTDIV3          				((uint32_t)0x00030000)		/*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_PTH_Filter_Division_Seclect PORT针对PTH输入滤波选择定义
  * @{
  */
#define   	Port_FLTHBUSCLK      						((uint32_t)0x00000000)		/*!< BUSCLK */
#define		Port_FLTHFLTDIV1   		  					((uint32_t)0x00004000)		/*!< BUSCLK1 */
#define		Port_FLTHFLTDIV2   	 						((uint32_t)0x00008000)		  /*!< BUSCLK2 */
#define		Port_FLTHFLTDIV3      						((uint32_t)0x0000C000)		/*!< BUSCLK3 */
/**
	* @}
	*/

/** @defgroup PORT_PTG_Filter_Division_Seclect PORT针对PTG输入滤波选择定义
  * @{
  */
#define		Port_FLTGBUSCLK      						((uint32_t)0x00000000)		  /*!< BUSCLK */
#define		Port_FLTGFLTDIV1   		  					((uint32_t)0x00001000)		/*!< FLTDIV1 */
#define		Port_FLTGFLTDIV2  		  					((uint32_t)0x00002000)		/*!< FLTDIV2 */
#define		Port_FLTGFLTDIV3     		 				((uint32_t)0x00003000)		  /*!< FLTDIV3 */																			
/**
	* @}
	*/

/** @defgroup PORT_PTF_Filter_Division_Seclect PORT针对PTF输入滤波选择定义
  * @{
  */
#define		Port_FLTFBUSCLK      						((uint32_t)0x00000000)		/*!< BUSCLK */
#define		Port_FLTFFLTDIV1   							((uint32_t)0x00000400)		/*!< FLTDIV1 */
#define		Port_FLTFFLTDIV2  	 						((uint32_t)0x00000800)		/*!< FLTDIV2 */
#define		Port_FLTFFLTDIV3   	     					((uint32_t)0x00000C00)	/*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_PTE_Filter_Division_Seclect PORT针对PTE输入滤波选择定义
  * @{
  */
#define		Port_FLTEBUSCLK  							((uint32_t)0x00000000)		    /*!< BUSCLK */
#define		Port_FLTEFLTDIV1     						((uint32_t)0x00000100)	    /*!< FLTDIV1 */
#define		Port_FLTEFLTDIV2     						((uint32_t)0x00000200)		  /*!< FLTDIV2 */
#define		Port_FLTEFLTDIV3   	     					((uint32_t)0x00000300)		/*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_PTD_Filter_Division_Seclect PORT针对PTD输入滤波选择定义
  * @{
  */
#define		Port_FLTDBUSCLK     						((uint32_t)0x00000000)		/*!< BUSCLK */
#define		Port_FLTDFLTDIV1     						((uint32_t)0x00000040)		/*!< FLTDIV1 */
#define		Port_FLTDFLTDIV2   	 						((uint32_t)0x00000080)		/*!< FLTDIV2 */
#define		Port_FLTDFLTDIV3   		   					((uint32_t)0x000000C0)	/*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_PTC_Filter_Division_Seclect PORT针对PTC输入滤波选择定义
  * @{
  */
#define		Port_FLTCBUSCLK   							((uint32_t)0x00000000)  	/*!< BUSCLK */
#define		Port_FLTCFLTDIV1   							((uint32_t)0x00000010)		/*!< FLTDIV1 */
#define		Port_FLTCFLTDIV2     						((uint32_t)0x00000020)		/*!< FLTDIV2 */
#define		Port_FLTCFLTDIV3        					((uint32_t)0x00000030)	/*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_PTB_Filter_Division_Seclect 	PORT针对PTB输入滤波选择定义
  * @{
  */
#define		Port_FLTBBUSCLK     						((uint32_t)0x00000000)		  /*!< BUSCLK */
#define		Port_FLTBFLTDIV1   	   						((uint32_t)0x00000004)		/*!< FLTDIV1 */
#define		Port_FLTBFLTDIV2       						((uint32_t)0x00000008)		/*!< FLTDIV2 */
#define		Port_FLTBFLTDIV3        					((uint32_t)0x0000000C)		/*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_PTA_Filter_Division_Seclect 	PORT针对PTA输入滤波选择定义
  * @{
  */
#define		Port_FLTABUSCLK     						((uint32_t)0x00000000)		  /*!< BUSCLK */
#define		Port_FLTAFLTDIV1   	   						((uint32_t)0x00000001)		/*!< FLTDIV1 */
#define		Port_FLTAFLTDIV2       						((uint32_t)0x00000002)		/*!< FLTDIV2 */
#define		Port_FLTAFLTDIV3        					((uint32_t)0x00000003)		/*!< FLTDIV3 */
/**
	* @}
	*/
	
	
/** @defgroup PORT_EWM_Filter_Division_Seclect PORT针对EWM输入滤波选择定义
  * @{
  */
#define		Port_FLTEWMNoFilter       					((uint16_t)0x00000)		/*!< 无滤波器 */
#define		Port_FLTEWMFLTDIV1   	 					((uint16_t)0x10000)		    /*!< FLTDIV1 */
#define		Port_FLTEWMFLTDIV2   	  					((uint16_t)0x20000)		  /*!< FLTDIV2 */
#define		Port_FLTIEWMBUSCLK       	 				((uint16_t)0x30000)		  /*!< FLTDIV3 */		
/**
	* @}
	*/

/** @defgroup PORT_I2C1_Filter_Division_Seclect PORT针对I2C1输入滤波选择定义
  * @{
  */
#define		Port_FLTI2C1NoFilter       					((uint16_t)0x0000)		/*!< 无滤波器 */
#define		Port_FLTI2C1FLTDIV1   	 					((uint16_t)0x4000)		  /*!< FLTDIV1 */
#define		Port_FLTI2C1FLTDIV2   	  					((uint16_t)0x8000)		/*!< FLTDIV2 */
#define		Port_FLTI2C1BUSCLK       	 				((uint16_t)0xC000)		  /*!< FLTDIV3 */																			 
/**
	* @}
	*/

/** @defgroup PORT_I2C0_Filter_Division_Seclect PORT针对I2C0输入滤波选择定义
  * @{
  */
#define		Port_FLTI2C0NoFilter     					((uint16_t)0x0000)          /*!< 无滤波器 */
#define   	Port_FLTI2C0FLTDIV1   		      			((uint16_t)0x1000)	  /*!< FLTDIV1 */
#define		Port_FLTI2C0FLTDIV2   		      			((uint16_t)0x2000)      /*!< FLTDIV2 */
#define		Port_FLTI2C0BUSCLK      		 			((uint16_t)0x3000)		      /*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_PWT_Filter_Division_Seclect PORT针对PWT输入滤波选择定义
  * @{
  */
#define		Port_FLTPWTNoFilter     					((uint16_t)0x0000)   /*!< 无滤波器 */
#define		Port_FLTPWTFLTDIV1   						((uint16_t)0x0400)     /*!< FLTDIV1 */
#define		Port_FLTPWTFLTDIV2  		 				((uint16_t)0x0800)     /*!< FLTDIV2 */
#define		Port_FLTPWTFLTDIV3      					((uint16_t)0x0C00)   /*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_FTM1_Filter_Division_Seclect PORT针对FTM1输入滤波选择定义
  * @{
  */
#define	Port_FLTFTM1NoFilter     						((uint16_t)0x0000)   /*!< No filter */
#define	Port_FLTFTM1FLTDIV1   							((uint16_t)0x0100)   /*!< FLTDIV1 */
#define	Port_FLTFTM1FLTDIV2   							((uint16_t)0x0200)   /*!< FLTDIV2 */
#define	Port_FLTFTM1FLTDIV3     		 				((uint16_t)0x0300)	 /*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_FTM0_Filter_Division_Seclect PORT针对FTM0输入滤波选择定义
  * @{
  */
#define		Port_FLTFTM0NoFilter    					((uint16_t)0x0000)   /*!< 无滤波器 */
#define		Port_FLTFTM0FLTDIV1   						((uint16_t)0x0040) 	 /*!< FLTDIV1 */
#define		Port_FLTFTM0FLTDIV2  	  					((uint16_t)0x0080)   /*!< FLTDIV2 */
#define		Port_FLTFTM0FLTDIV3      	 				((uint16_t)0x00C0)	 /*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_IRQ_Filter_Division_Seclect PORT针对IRQ输入滤波选择定义
  * @{
  */
#define		Port_FLTIRQNoFilter   						((uint16_t)0x0000)   /*!< 无滤波器 */
#define		Port_FLTIRQFLTDIV1 	 						((uint16_t)0x0010)     /*!< Selects FLTDIV1, Stop 模式下自动切换到FLTDIV3 */
#define		Port_FLTIRQFLTDIV2 	 						((uint16_t)0x0020)     /*!< Selects FLTDIV2, Stop 模式下自动切换到FLTDIV3 */
#define		Port_FLTIRQFLTDIV3      	 				((uint16_t)0x0030)   /*!< FLTDIV3 */
																			 
/**
	* @}
	*/

/** @defgroup PORT_PTI_Filter_Division_Seclect PORT针对PTI输入滤波选择定义
  * @{
  */
#define		Port_FLTPTIBUSCLK    						((uint16_t)0x0000)   /*!< BUSCLK */
#define		Port_FLTPTIFLTDIV1   						((uint16_t)0x0001)   /*!< FLTDIV1 */
#define		Port_FLTPTIFLTDIV2   						((uint16_t)0x0002)   /*!< FLTDIV2 */
#define		Port_FLTPTIFLTDIV3   		    			((uint16_t)0x0003)   /*!< FLTDIV3 */
/**
	* @}
	*/

/** @defgroup PORT_PullPin_Seclect PORT引脚上拉选择
  * @{
  */
#define    PORT_PTA0 			0             /*!< GPIO引脚PTA0 */
#define    PORT_PTA1			1             /*!< GPIO引脚PTA1 */
#define    PORT_PTA2			2             /*!< GPIO引脚PTA2 */
#define    PORT_PTA3           	3       /*!< GPIO引脚PTA3 */
#define    PORT_PTA4           	4       /*!< GPIO引脚PTA4 */
#define    PORT_PTA5            5       /*!< GPIO引脚PTA5 */
#define    PORT_PTA6            6       /*!< GPIO引脚PTA6 */
#define    PORT_PTA7            7       /*!< GPIO引脚PTA7 */
#define    PORT_PTB0            8       /*!< GPIO引脚PTB0 */
#define    PORT_PTB1            9       /*!< GPIO引脚PTB1 */
#define    PORT_PTB2            10      /*!< GPIO引脚PTB2 */
#define    PORT_PTB3            11      /*!< GPIO引脚PTB3 */
#define    PORT_PTB4            12      /*!< GPIO引脚PTB4 */
#define    PORT_PTB5            13      /*!< GPIO引脚PTB5 */
#define    PORT_PTB6            14      /*!< GPIO引脚PTB6 */
#define    PORT_PTB7            15      /*!< GPIO引脚PTB7 */
#define    PORT_PTC0            16      /*!< GPIO引脚PTC0 */
#define    PORT_PTC1            17      /*!< GPIO引脚PTC1 */
#define    PORT_PTC2            18      /*!< GPIO引脚PTC2 */
#define    PORT_PTC3            19      /*!< GPIO引脚PTC3 */
#define    PORT_PTC4            20      /*!< GPIO引脚PTC4 */
#define    PORT_PTC5            21      /*!< GPIO引脚PTC5 */
#define    PORT_PTC6            22      /*!< GPIO引脚PTC6 */
#define    PORT_PTC7            23      /*!< GPIO引脚PTC7 */
#define    PORT_PTD0            24      /*!< GPIO引脚PTD0 */
#define    PORT_PTD1            25      /*!< GPIO引脚PTD1 */
#define    PORT_PTD2            26      /*!< GPIO引脚PTD2 */
#define    PORT_PTD3            27      /*!< GPIO引脚PTD3 */
#define    PORT_PTD4            28      /*!< GPIO引脚PTD4 */
#define    PORT_PTD5            29      /*!< GPIO引脚PTD5 */
#define    PORT_PTD6            30      /*!< GPIO引脚PTD6 */
#define    PORT_PTD7            31      /*!< GPIO引脚PTD7 */
    /* in GPIOB register */
#define    PORT_PTE0            32       /*!< GPIO引脚PTE0 */
#define    PORT_PTE1            33       /*!< GPIO引脚PTE1 */
#define    PORT_PTE2            34       /*!< GPIO引脚PTE2 */
#define    PORT_PTE3            35       /*!< GPIO引脚PTE3 */
#define    PORT_PTE4            36       /*!< GPIO引脚PTE4 */
#define    PORT_PTE5            37       /*!< GPIO引脚PTE5 */
#define    PORT_PTE6            38       /*!< GPIO引脚PTE6 */
#define    PORT_PTE7            39       /*!< GPIO引脚PTE7 */
#define    PORT_PTF0            40       /*!< GPIO引脚PTF0 */
#define    PORT_PTF1            41       /*!< GPIO引脚PTF1 */
#define    PORT_PTF2            42      /*!< GPIO引脚PTF2 */
#define    PORT_PTF3            43      /*!< GPIO引脚PTF3 */
#define    PORT_PTF4            44      /*!< GPIO引脚PTF4 */
#define    PORT_PTF5            45      /*!< GPIO引脚PTF5 */
#define    PORT_PTF6            46      /*!< GPIO引脚PTF6 */
#define    PORT_PTF7            47      /*!< GPIO引脚PTF7 */
#define    PORT_PTG0            48      /*!< GPIO引脚PTG0 */
#define    PORT_PTG1            49      /*!< GPIO引脚PTG1 */
#define    PORT_PTG2            50      /*!< GPIO引脚PTG2 */
#define    PORT_PTG3            51      /*!< GPIO引脚PTG3 */
#define    PORT_PTG4            52      /*!< GPIO引脚PTG4 */
#define    PORT_PTG5            53      /*!< GPIO引脚PTG5 */
#define    PORT_PTG6            54      /*!< GPIO引脚PTG6 */
#define    PORT_PTG7            55      /*!< GPIO引脚PTG7 */
#define    PORT_PTH0            56      /*!< GPIO引脚PTH0 */
#define    PORT_PTH1            57      /*!< GPIO引脚PTH1 */
#define    PORT_PTH2            58      /*!< GPIO引脚PTH2 */
#define    PORT_PTH3            59      /*!< GPIO引脚PTH3 */
#define    PORT_PTH4            60      /*!< GPIO引脚PTH4 */
#define    PORT_PTH5            61      /*!< GPIO引脚PTH5 */
#define    PORT_PTH6            62      /*!< GPIO引脚PTH6 */
#define    PORT_PTH7            63      /*!< GPIO引脚PTH7 */
    /* in GPIOC register */
#define    PORT_PTI0            64       /*!< GPIO引脚PTI0 */
#define    PORT_PTI1            65       /*!< GPIO引脚PTI1 */
#define    PORT_PTI2            66       /*!< GPIO引脚PTI2 */
#define    PORT_PTI3            67       /*!< GPIO引脚PTI3 */
#define    PORT_PTI4            68       /*!< GPIO引脚PTI4 */
#define    PORT_PTI5            69       /*!< GPIO引脚PTI5 */
#define    PORT_PTI6            70       /*!< GPIO引脚PTI6 */
/**
	* @}
	*/
													
/** @defgroup PORT_HighDrive_Seclect PORT大电流驱动引脚定义
  * @{
  */
#define		PORT_PullPTB4 	 	0		/*!< 引脚PTB4 */
#define		PORT_PullPTB5		1		/*!< 引脚PTB5 */
#define		PORT_PullPTD0		2		/*!< 引脚PTD0 */
#define		PORT_PullPTD1		3		/*!< 引脚PTD1 */
#define		PORT_PullPTE0		4		/*!< 引脚PTE0 */
#define		PORT_PullPTE1		5		/*!< 引脚PTE1 */
#define		PORT_PullPTH0		6		/*!< 引脚PTH0 */
#define		PORT_PullPTH1		7		/*!< 引脚PTH1 */
/**
	* @}
	*/



/**
	* @}
	*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
void PORT_DeInit(void);
void PORT_IOFLT0Config(const port_ioflt0_config *IOflt0ConfigPtr);
void PORT_IOFLT1Config(const port_ioflt1_config *IOflt1ConfigPtr);
void PORT_FLTDIV3ConSet(uint32_t clk);
void PORT_FLTDIV2Set(uint32_t clk);
void PORT_FLTDIV1Set(uint32_t clk);
void PORT_FLTNMISET(uint32_t NMIFilter);
void PORT_FLTKBI1SET(uint32_t KBI1Filter);
void PORT_FLTKBI0SET(uint32_t KBI0Filter);
void PORT_FLTRSTSET(uint32_t RSTFilter);
void PORT_FLTISET(uint32_t FLTIFilter);
void PORT_FLTHSET(uint32_t FLTHFilter);
void PORT_FLTGSET(uint32_t FLTGFilter);
void PORT_FLTFSET(uint32_t FLTFFilter);
void PORT_FLTESET(uint32_t FLTEFilter);
void PORT_FLTDSET(uint32_t FLTDFilter);
void PORT_FLTCSET(uint32_t FLTCFilter);
void PORT_FLTBSET(uint32_t FLTBFilter);
void PORT_FLTASET(uint32_t FLTAFilter);
void PORT_FLTEWMSET(uint32_t FLTEWMFilter);
void PORT_FLTI2C1SET(uint32_t FLTI2C1Filter);
void PORT_FLTI2C0SET(uint32_t FLTI2C0Filter);
void PORT_FLTPWTSET(uint32_t FLTPWTFilter);
void PORT_FLTFTM1SET(uint32_t FLTFTM1Filter);
void PORT_FLTFTM0SET(uint32_t FLTFTM0Filter);
void PORT_FLTIRQSET(uint32_t FLTIRQFilter);
void PORT_PullPinCmd(uint8_t PortPin,FunctionalState NewState);
void PORT_HDRVEPinCmd(uint8_t hdrvePin,FunctionalState NewState);
	

#ifdef __cplusplus
}
#endif	
	
#endif /* __XL_PORT_H */
/**
  * @}
  */

/**
  * @}
  */
