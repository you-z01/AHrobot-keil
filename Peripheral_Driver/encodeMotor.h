#ifndef __ENCODEMOTOR_H
#define __ENCODEMOTOR_H

#include "system.h"

void Emotor_GPIO_Init(void);                 // 编码电机方向脚初始化
void Emotor_PWM_TIM8_Init(u16 arr, u16 psc); // 编码器电机PWM初始化

#define ENCODER_TIM_PERIOD (u16)(65535) // 设定计数器自动重装值

void Encoder_Init_TIM2(void);
void Encoder_Init_TIM3(void);
void Encoder_Init_TIM4(void);
void Encoder_Init_TIM5(void);

void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);

#endif
