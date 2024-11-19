/**
 * @Author: z
 * @Date: 2024-11-15 
 * @LastEditTime: 2024-11-19 
 * @Description: 编码电机驱动 PWM初始化 引脚初始化 编码值初始化
 * @FilePath: \AHrobot\Peripheral_Driver\encodeMotor.c
 */
#include "encodeMotor.h"

/****************************************************************************************
 * @description: 编码电机方向引脚初始化
 * @return {*}
 ****************************************************************************************/
void Emotor_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // 普通输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; // 下拉, 初始化为低电平
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}



/****************************************************************************************
 * @description: 编码电机PWM引脚初始化 TIM8
 * @param {u16} arr 自动重装值
 * @param {u16} psc 时钟预分频数
 * @return {*}
 ****************************************************************************************/
void Emotor_PWM_TIM8_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);  // TIM8时钟使能
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); // 使能PORTC时钟

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM8);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; // GPIO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                                     // 复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                               // 速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                                   // 推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                                     // 上拉
    GPIO_Init(GPIOC, &GPIO_InitStructure);                                           // 初始化PC口

    // 设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Period = arr;
    // 设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    // 设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_ClockDivision = 1;
    // 向上计数模式
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    // 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

    // 选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    // 比较输出使能
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    // 输出极性:TIM输出比较极性高
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    // 根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    TIM_OC1Init(TIM8, &TIM_OCInitStructure);
    TIM_OC2Init(TIM8, &TIM_OCInitStructure);
    TIM_OC3Init(TIM8, &TIM_OCInitStructure);
    TIM_OC4Init(TIM8, &TIM_OCInitStructure);

    // 高级定时器输出必须使能这句
    TIM_CtrlPWMOutputs(TIM8, ENABLE);

    // CH1预装载使能
    TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);

    // 使能TIMx在ARR上的预装载寄存器
    TIM_ARRPreloadConfig(TIM8, ENABLE);

    TIM8->CCR1 = 0;
    TIM8->CCR2 = 0;
    TIM8->CCR3 = 0;
    TIM8->CCR4 = 0;

    // 使能TIM8
    TIM_Cmd(TIM8, ENABLE);
}



/****************************************************************************************
 * @description: 把TIM2初始化为编码器接口模式
 * @return {*}
 ****************************************************************************************/
void Encoder_Init_TIM2(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                         // 使能定时器
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE); // 使用A B口

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; // PA15
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; // PB3
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2); // 复用为TIM2 编码器接口
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);  // 复用为TIM2 编码器接口

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                  // No prescaling     //不分频
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;      // 设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 选择时钟分频：不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             // 初始化定时器

    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // 使用编码器模式3
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update); // 清除TIM的更新标志位
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_SetCounter(TIM2, 0);
    TIM_Cmd(TIM2, ENABLE);
}



/****************************************************************************************
 * @description: 把TIM3初始化为编码器接口模式
 * @return {*}
 ****************************************************************************************/
void Encoder_Init_TIM3(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // 使能定时器
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // 使用A口

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // PA6 PA7
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3); // 复用为TIM2 编码器接口
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3); // 复用为TIM2 编码器接口

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                  // No prescaling     //不分频
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;      // 设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 选择时钟分频：不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             // 初始化定时器

    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // 使用编码器模式3
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_ClearFlag(TIM3, TIM_FLAG_Update); // 清除TIM的更新标志位
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_SetCounter(TIM3, 0);
    TIM_Cmd(TIM3, ENABLE);
}



/****************************************************************************************
 * @description: 把TIM4初始化为编码器接口模式
 * @return {*}
 ****************************************************************************************/
void Encoder_Init_TIM4(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   // 使能定时器4的时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  // 使能PB端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // 端口配置
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure); // 根据设定参数初始化GPIOB

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4); // 复用为TIM4 编码器接口
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4); // 复用为TIM4 编码器接口

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                  // No prescaling
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;      // 设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 选择时钟分频：不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // 使用编码器模式3
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);

    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_SetCounter(TIM4, 0);
    TIM_Cmd(TIM4, ENABLE);
}



/****************************************************************************************
 * @description: 把TIM5初始化为编码器接口模式
 * @return {*}
 ****************************************************************************************/
void Encoder_Init_TIM5(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);   // 使能定时器4的时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  // 使能PB端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // 端口配置
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 根据设定参数初始化GPIOB

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5); // 复用为TIM5 编码器接口
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5); // 复用为TIM5 编码器接口

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                  // No prescaling
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;      // 设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 选择时钟分频：不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM向上计数
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // 使用编码器模式3
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);

    TIM_ClearFlag(TIM5, TIM_FLAG_Update);
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
    TIM_SetCounter(TIM5, 0);
    TIM_Cmd(TIM5, ENABLE);
}



/****************************************************************************************
 * @description: TIM2中断服务函数
 * @return {*}
 ****************************************************************************************/
void TIM2_IRQHandler(void)
{
    if (TIM2->SR & 0X0001) // Overflow interrupt //溢出中断
    {
    }
    TIM2->SR &= ~(1 << 0); // Clear the interrupt flag bit //清除中断标志位
}



/****************************************************************************************
 * @description: TIM3中断服务函数
 * @return {*}
 ****************************************************************************************/
void TIM3_IRQHandler(void)
{
    if (TIM3->SR & 0X0001) // Overflow interrupt //溢出中断
    {
    }
    TIM3->SR &= ~(1 << 0); // Clear the interrupt flag bit //清除中断标志位
}



/****************************************************************************************
 * @description: TIM4中断服务函数
 * @return {*}
 ****************************************************************************************/
void TIM4_IRQHandler(void)
{
    if (TIM4->SR & 0X0001) // Overflow interrupt //溢出中断
    {
    }
    TIM4->SR &= ~(1 << 0); // Clear the interrupt flag bit //清除中断标志位
}



/****************************************************************************************
 * @description: TIM5中断服务函数
 * @return {*}
 ****************************************************************************************/
void TIM5_IRQHandler(void)
{
    if (TIM5->SR & 0X0001) // Overflow interrupt //溢出中断
    {
    }
    TIM5->SR &= ~(1 << 0); // Clear the interrupt flag bit //清除中断标志位
}
