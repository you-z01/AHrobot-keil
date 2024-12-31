#ifndef __STEERENGINE_H
#define __STEERENGINE_H

#include "stm32f4xx.h"

void Sengine_PWM_TIM9_Init(u16 arr, u16 psc);
void Sengine_PWM_TIM10_Init(u16 arr, u16 psc);
void Sengine_PWM_TIM11_Init(u16 arr, u16 psc);
void Sengine_PWM_TIM12_Init(u16 arr, u16 psc);

#endif
