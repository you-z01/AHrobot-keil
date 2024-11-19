/**
 * @Author: z
 * @Date: 2024-11-15 
 * @LastEditTime: 2024-11-19 
 * @Description: 步进电机驱动程序
 * @FilePath: \AHrobot\Peripheral_Driver\stepMotor.c
 */
#include "stepMotor.h"


/****************************************************************************************
 * @description: 步进电机方向引脚初始化
 * @return {*}
 ****************************************************************************************/
void Smotor_GPIO_Init(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_StructInit(&GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN; // 下拉, 初始化为低电平
  GPIO_Init(GPIOG, &GPIO_InitStruct);
  // GPIO_ResetBits(GPIOG, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
}

/****************************************************************************************
 * @description: 步进电机PWM引脚初始化 TIM1
 * @param {u16} arr 自动重装值
 * @param {u16} psc 时钟预分频数
 * @return {*}
 ****************************************************************************************/
void Smotor_PWM_TIM1_Init(u16 arr, u16 psc)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);  // TIM1时钟使能
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); // GPIO端口时钟使能

  // 配置PE9、PE11、PE13和PE14引脚为复用功能
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  // 将GPIO引脚与TIM1的对应通道连接起来
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);

  // 配置TIM1为PWM模式
  TIM_TimeBaseStructure.TIM_Period = arr;                     // 设置在下一个更新事件装入活动的自动重装载寄存器周期的值
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  // 设置用来作为TIMx时钟频率除数的预分频值
  TIM_TimeBaseStructure.TIM_ClockDivision = 1;                // 不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            // 禁用重复计数功能
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  // 配置TIM1通道1、通道2和通道3为PWM输出
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;             // 选择定时器模式:TIM脉冲宽度调制模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 比较输出使能
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     // 输出极性:TIM输出比较极性高
  // TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);

  // TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE); // 使能TIM1的CC1中断
  //  在NVIC中使能TIM1更新中断对应的中断向量
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;  // 选择定时器TIM1的更新中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; // 设置抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // 设置子优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // 使能中断通道
  NVIC_Init(&NVIC_InitStructure);
  TIM_UpdateRequestConfig(TIM1, TIM_UpdateSource_Regular);     // 配置更新请求来源：计数器溢出/ 下一个更新事件
  TIM_SetAutoreload(TIM1, arr);                                // 配置自动重装载寄存器
  TIM_PrescalerConfig(TIM1, psc, TIM_PSCReloadMode_Immediate); // 配置预分频器

  TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE); // 先不使能更新中断
                                              // TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); // 使能更新中断

  // 高级定时器输出必须使能这句
  TIM_CtrlPWMOutputs(TIM1, ENABLE); // 开启TIM1主输出

  // CH1预装载使能
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

  // 使能TIMx在ARR上的预装载寄存器
  TIM_ARRPreloadConfig(TIM1, ENABLE);

  TIM1->CCR1 = 0; // 初始设置占空比为0，即关闭PWM输出
  TIM1->CCR2 = 0;
  TIM1->CCR3 = 0;
  TIM1->CCR4 = 0;

  TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
  TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
  TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
  TIM_CCxCmd(TIM1, TIM_Channel_4, TIM_CCx_Disable);

  TIM_Cmd(TIM1, ENABLE); // 使能TIM1
}

/****************************************************************************************
 * @description: TIM1更新中断处理函数
 * @return {*}
 ****************************************************************************************/
void TIM1_UP_TIM10_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
  {
    // 步进电机角度控制 每个中断周期会产生一定数量的脉冲（根据占空比和定时器设置），
    // 通过累加脉冲计数器 ci，步进电机脉冲数到ci时，关闭PWM，就能控制转动指定的角度
    Smotor_Angle_control();
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
  }
}

/****************************************************************************************
 * @description: 控制指定通道的PWM输出使能与失能
 * @param {int} channel 要控制的通道
 * @param {FunctionalState} state 使能或失能
 * @return {*}
 ****************************************************************************************/
void TIM1_PWM_Output(int channel, FunctionalState state)
{
  switch (channel)
  {
  case 1:
    if (state == ENABLE)
      TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
    else
      TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
    break;
  case 2:
    if (state == ENABLE)
      TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
    else
      TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
    break;
  case 3:
    if (state == ENABLE)
      TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
    else
      TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
    break;
  case 4:
    if (state == ENABLE)
      TIM_CCxCmd(TIM1, TIM_Channel_4, TIM_CCx_Enable);
    else
      TIM_CCxCmd(TIM1, TIM_Channel_4, TIM_CCx_Disable);
  default:
    break;
  }

  // 在使能情况下，如果 TIM1 的有任意通道使能了，则开启中断
  if (state == ENABLE && TIM1->CCER != 0)
  {
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
  }
  // 在失能情况下，如果 TIM1 所有通道都关闭了，则关闭中断
  else if (TIM1->CCER == 0) // 如果所有通道都使能了，CCER寄存器的值应为0
  {
    TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
  }
}
