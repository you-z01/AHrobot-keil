#ifndef _SysTick_H
#define _SysTick_H

#include "stm32f4xx.h"

void SysTick_Init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

u32 getSysTickCnt(void);

#endif
