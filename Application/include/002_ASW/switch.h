/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*Name     :  switch.h                                                           *
;*Project  :  AntiPinch                                                    *
;*Device   :  S12VR64					                                       *
;*AUTHOR   :  AP project team						                                       *
;*DATE     :  2010/05/20					                                   *
;*SW VER   :  0.1					                                           *
;*HW VER   :    					                                           *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;* COPYRIGHT STEC(C) Shanghai SIIC Transportation Electric CO.,ltd             *
;*                                                                             *
;* ALL RIGHTS RESERVED                                                         *
;*                                                                             *
;* The reproduction, transmission, or use of this document or its content is   *
;* not permitted without express written authority. Offenders will be liable   *
;* for damages.                                                                *
;* All rights, including rights created by patent grant or registration of a   *
;* utility model or design, are reserved.                                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
#ifndef _SWITCH_H

#define _SWITCH_H 
#include "keyport.h"

#define WIDLE    0x00	//idle 状态
#define WSTOP    0x01	//stop
#define SMU      0x02	//manual up 
#define SMD      0x03	//down
#define SMU2     0x04	//manual up  

#define SAU      0x05	//auto up
#define SMD2     0x06 //manual down
#define SAD      0x07  

#define LMU      0x08	//lin manual up
#define LMD      0x09
#define LAU0     0x0A	//lin auto up 
#define LAU	     0x0B	//auto up without signal
#define LAD0     0x0C //lin auto down
#define LAD 	   0x0D
#define BMU      0x0E	//both local & lin up
#define BMD      0x0F	//both down 
#define ERR		   0x10	//开始时双有效，释放一个按键，车窗不应动作 for factory test	


extern uint8_t  SW_ub_KeyAct;
extern uint8_t  SW_ub_Win_Status;
extern uint8_t  SW_ub_KeyErr;
extern uint8_t  SW_ub_Lin_Func    ;

extern volatile T_FLAG8 SW_T8_Flag ;

#define  SW_bi_Change_Direction   SW_T8_Flag.Bits.Bit0 //换向
//#define          SW_T8_Flag.bi.bit1 //
//#define          SW_T8_Flag.bi.bit2 //


extern void key(void);
extern void key_init(void);
extern void key_checkstop(void);
extern void key_init_st();
#endif



