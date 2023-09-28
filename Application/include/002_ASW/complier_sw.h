
/*******************************************************************************
|  File Name:    main.c
|  Description:  app main function source file
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       -----------------------------------------
| 20190123	   0.01       	HaiH          	Init
|******************************************************************************/

#ifndef COMPILER_SW_H
#define COMPILER_SW_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                             **
*******************************************************************************/
#define EE_FILE_EXIST    0x0000
#define CS_EnableUBattery  					//鏈夌數婧愮鐞�

#if defined(__GNUC__)
#undef _Init_Static_Rom
#define _Init_Static_Rom __attribute__((__section__(".static_data")))
#else
#undef _Init_Static_Rom
#define _Init_Static_Rom
#endif


#if defined(__GNUC__)
#undef _Init_factory_Rom
#define _Init_factory_Rom __attribute__((__section__(".factory_data")))
#else
#undef _Init_factory_Rom
#define _Init_factory_Rom
#endif

#if defined(__GNUC__)
#undef _Init_SAVE_RAM
#define _Init_SAVE_RAM __attribute__((__section__(".save_ram")))
#else
#undef _Init_SAVE_RAM
#define _Init_SAVE_RAM
#endif

//#define HARDWARE_TEST
//#define KEY_DEBUG
//#define 	ROUGH_ROAD_TEST
#define DOOR_FL
//#define DOOR_FR
//#define DOOR_RL
//#define DOOR_RR

/*******************************************************************************
**    Define  software id for special customer 								                **
*******************************************************************************/
#define SW_CustomerID 0x24
#define SW_ID	 0x34             //鎺у埗鐗堟湰鍙蜂粠瀛楃'0'寮�濮�

/*******************************************************************************
**    Define  complier switch for calibrate sw 								                **
*******************************************************************************/
#define AP_OFF_AP_10SECONDS  
//#define AP_SIM_DEBUG


#endif
