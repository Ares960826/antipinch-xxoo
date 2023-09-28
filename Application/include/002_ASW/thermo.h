/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*Name     :  thermo.h                                                           *
;*Project  :  AntiPinch   ¤ù¡G                                                 *
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

#ifndef _Thermo_h
#define _Thermo_h
#include "Typedef.h"
extern void thermo_block_calc(uint16_t );
extern uint16_t    TP_ui_Motor_Temperature ;
extern uint8_t  TP_uc_Motor_times;
extern void thermo_init(void);
extern void thermo_calc(void);
extern void thermo_50msjob(void);
bool_t TP_TstThermalPFlg(void);
void thermo_reset(void);

#endif


