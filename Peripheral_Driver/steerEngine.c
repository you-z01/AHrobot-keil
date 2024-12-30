/** 
 * @Author: z
 * @Date: 2024-11-15 
 * @LastEditTime: 2024-11-19 
 * @Description: 舵机驱动程序
 * @FilePath: \AHrobot\Peripheral_Driver\steerEngine.c
 */
#include "steerEngine.h"

/****************************************************************************************
 * @description: TIM9输出pwm初始化，用于驱动舵机，A2 A3两路
 * @param {u16} arr 时钟频率的最大值
 * @param {u16} psc 预分频值
 * @return {*}
 ****************************************************************************************/
void Sengine_PWM_TIM9_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM9);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM9);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; // GPIO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;           // 复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;     // 速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         // 推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;           // 上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 // 初始化PC口

    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = 1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 输出极性:TIM输出比较极性高
    TIM_OC1Init(TIM9, &TIM_OCInitStructure);
    TIM_OC2Init(TIM9, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);

    // 使能TIMx在ARR上的预装载寄存器
    TIM_ARRPreloadConfig(TIM9, ENABLE);

    TIM9->CCR1 = 0;
    TIM9->CCR2 = 0;

    // 使能TIM9
    TIM_Cmd(TIM9, ENABLE);
}



/****************************************************************************************
 * @description: TIM10输出pwm初始化，用于驱动舵机，F6一路
 * @param {u16} arr 时钟频率的最大值
 * @param {u16} psc 预分频值
 * @return {*}
 ****************************************************************************************/
void Sengine_PWM_TIM10_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    GPIO_PinAFConfig(GPIOF, GPIO_PinSource6, GPIO_AF_TIM10);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;              // GPIO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;           // 复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;     // 速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         // 推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;           // 上拉
    GPIO_Init(GPIOF, &GPIO_InitStructure);                 // 初始化PC口

    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = 1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 输出极性:TIM输出比较极性高
    TIM_OC1Init(TIM10, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);

    // 使能TIMx在ARR上的预装载寄存器
    TIM_ARRPreloadConfig(TIM10, ENABLE);

    TIM9->CCR1 = 0;

    // 使能TIM10
    TIM_Cmd(TIM10, ENABLE);
}



/****************************************************************************************
 * @description: TIM11输出pwm初始化，用于驱动舵机，F7一路
 * @param {u16} arr 时钟频率的最大值
 * @param {u16} psc 预分频值
 * @return {*}
 ****************************************************************************************/
void Sengine_PWM_TIM11_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    GPIO_PinAFConfig(GPIOF, GPIO_PinSource7, GPIO_AF_TIM11);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;          // GPIO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       // 复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // 推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       // 上拉
    GPIO_Init(GPIOF, &GPIO_InitStructure);             // 初始化PC口

    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = 1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM11, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 输出极性:TIM输出比较极性高
    TIM_OC1Init(TIM11, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM11, TIM_OCPreload_Enable);

    // 使能TIMx在ARR上的预装载寄存器
    TIM_ARRPreloadConfig(TIM11, ENABLE);

    TIM1->CCR1 = 0;

    // 使能TIM11
    TIM_Cmd(TIM11, ENABLE);
}



/****************************************************************************************
 * @description: TIM12输出pwm初始化，用于驱动舵机，B14 B15两路
 * @param {u16} arr 时钟频率的最大值
 * @param {u16} psc 预分频值
 * @return {*}
 ****************************************************************************************/
void Sengine_PWM_TIM12_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_TIM12);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_TIM12);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15; // GPIO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;           // 复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;     // 速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         // 推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;           // 上拉
    GPIO_Init(GPIOB, &GPIO_InitStructure);                 // 初始化PC口

    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = 1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 输出极性:TIM输出比较极性高
    TIM_OC1Init(TIM12, &TIM_OCInitStructure);
    TIM_OC2Init(TIM12, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM12, TIM_OCPreload_Enable);

    // 使能TIMx在ARR上的预装载寄存器
    TIM_ARRPreloadConfig(TIM12, ENABLE);

    TIM12->CCR1 = 0;
    TIM12->CCR2 = 0;

    // 使能TIM12
    TIM_Cmd(TIM12, ENABLE);
}

