#ifndef DELAY_H_
#define DELAY_H_

#include "XL6600.h"



void Systick_Init(void);
void Delay_us(uint32_t nus);
void Delay_ms(uint32_t nms);

#endif



