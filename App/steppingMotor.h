
#ifndef __STEPPINGMOTOR_H
#define __STEPPINGMOTOR_H

#include "system.h"

/*--------------步进电机1-------------*/
#define S_PWM_PORT_1 GPIOE
#define S_PWM_PIN_1 GPIO_Pin_9
#define S_PWM_1 TIM1->CCR1

#define DIR_PORT_1 GPIOG
#define DIR_PIN_1 GPIO_Pin_2
#define DIR_1 PGout(2)
/*------------------------------------*/

/*--------------步进电机2-------------*/
#define S_PWM_PORT_2 GPIOE
#define S_PWM_PIN_2 GPIO_Pin_11
#define S_PWM_2 TIM1->CCR2

#define DIR_PORT_2 GPIOG
#define DIR_PIN_2 GPIO_Pin_3
#define DIR_2 PGout(3)
/*------------------------------------*/

/*--------------步进电机3-------------*/
#define S_PWM_PORT_3 GPIOE
#define S_PWM_PIN_3 GPIO_Pin_13
#define S_PWM_3 TIM1->CCR3

#define DIR_PORT_3 GPIOG
#define DIR_PIN_3 GPIO_Pin_4
#define DIR_3 PGout(4)
/*------------------------------------*/

/*--------------步进电机4-------------*/
#define S_PWM_PORT_4 GPIOE
#define S_PWM_PIN_4 GPIO_Pin_14
#define S_PWM_4 TIM1->CCR4

#define DIR_PORT_4 GPIOG
#define DIR_PIN_4 GPIO_Pin_5
#define DIR_4 PGout(5)
/*------------------------------------*/

// 步进电机控制相关参数
typedef struct
{
    u32 count_value;  // 计数值
    u16 target_value; // 目标值
} S_Motor_parameter;

void Smotor_Init(void);
void Start_motion(uint8_t num, uint8_t dir, uint16_t targe, uint16_t pwm);
void Smotor_Angle_control(void);

#endif
