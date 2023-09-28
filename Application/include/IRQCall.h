/*
 * IRQCall.h
 *
 *  Created on: Mar 27, 2021
 *      Author: wyanw003
 */

#ifndef APPLICATION_INCLUDE_IRQCALL_H_
#define APPLICATION_INCLUDE_IRQCALL_H_

extern bool_t	g_bl_NewHPWFlg;
extern uint16_t getBothEdgeCounter();

extern uint16_t getVehicleEnableAD();
extern uint16_t getKeyAD();
extern uint16_t getBattAD();
extern uint16_t getRelayDownAD();
extern uint16_t getRelayUpAD();
extern uint16_t getThermalAD();


#endif /* APPLICATION_INCLUDE_IRQCALL_H_ */
