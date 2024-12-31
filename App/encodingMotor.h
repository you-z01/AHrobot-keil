#ifndef __ENCODINGMOTOR_H
#define __ENCODINGMOTOR_H

#include "stm32f4xx.h"

/*--------------编码电机1-------------*/
#define E_PWM_PORT_1 GPIOC // 电机1 PWM
#define E_PWM_PIN_1 GPIO_Pin_6
#define E_PWM_1 TIM8->CCR1

#define IN1_PORT_1 GPIOA // 电机1 IN1
#define IN1_PIN_1 GPIO_Pin_5
#define E1_IN1 PEout(0)

#define IN2_PORT_1 GPIOA // 电机1 IN2
#define IN2_PIN_1 GPIO_Pin_4
#define E1_IN2 PEout(1)
/*------------------------------------*/
/*--------------编码电机2-------------*/
#define E_PWM_PORT_2 GPIOC // PWM
#define E_PWM_PIN_2 GPIO_Pin_7
#define E_PWM_2 TIM8->CCR2

#define IN1_PORT_2 GPIOD // IN1
#define IN1_PIN_2 GPIO_Pin_10
#define E2_IN1 PEout(2)

#define IN2_PORT_2 GPIOD // IN2
#define IN2_PIN_2 GPIO_Pin_12
#define E2_IN2 PEout(3)
/*------------------------------------*/
/*--------------编码电机3-------------*/
#define E_PWM_PORT_3 GPIOC // PWM
#define E_PWM_PIN_3 GPIO_Pin_8
#define E_PWM_3 TIM8->CCR3

#define IN1_PORT_3 GPIOC // IN1
#define IN1_PIN_3 GPIO_Pin_0
#define E3_IN1 PEout(4)

#define IN2_PORT_3 GPIOB // IN2
#define IN2_PIN_3 GPIO_Pin_14
#define E3_IN2 PEout(5)
/*------------------------------------*/
/*--------------编码电机4-------------*/
#define E_PWM_PORT_4 GPIOC // PWM
#define E_PWM_PIN_4 GPIO_Pin_9
#define E_PWM_4 TIM8->CCR4

#define IN1_PORT_4 GPIOB // IN1
#define IN1_PIN_4 GPIO_Pin_13
#define E4_IN1 PEout(6)

#define IN2_PORT_4 GPIOB // IN2
#define IN2_PIN_4 GPIO_Pin_12
#define E4_IN2 PEout(7)
/*------------------------------------*/

void Emotor_Init(void);
void Emotor_control(u8 num, int pwm);
int Read_Encoder(u8 TIMX);

#endif
