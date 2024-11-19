#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H

#include "system.h"

void Smotor_GPIO_Init(void);                              // 步进电机方向脚初始化
void Smotor_PWM_TIM1_Init(u16 arr, u16 psc);              // 步进电机PWM初始化
void TIM1_UP_TIM10_IRQHandler(void);                      // 步进电机中断函数
void TIM1_PWM_Output(int channel, FunctionalState state); // TIM1 PWM输出控制

#endif
