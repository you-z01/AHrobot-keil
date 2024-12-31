/**
 * @Author: z
 * @Date: 2024-11-13
 * @LastEditTime: 2024-11-14
 * @Description: 步进电机控制接口
 * @FilePath: \AHrobot\App\steppingMotor.c
 */
#include "steppingMotor.h"
#include "system.h"

// 步进电机的参数结构体
S_Motor_parameter SMOTOR_1, SMOTOR_2, SMOTOR_3, SMOTOR_4;

/****************************************************************************************
 * @description: 步进电机驱动初始化
 * @return {*}
 ****************************************************************************************/
void Smotor_Init(void)
{
    Smotor_GPIO_Init();
    Smotor_PWM_TIM1_Init(1000 - 1, 168 - 1); // 频率=168M/((999+1)*(167+1))=1KHZ
}

/****************************************************************************************
 * @description: 步进电机启动函数
 * @param {uint8_t} num 电机编号(1-4)
 * @param {uint8_t} dir 旋转方向(0 1)
 * @param {uint16_t} targe 旋转的圈数 （400细分）
 * @param {uint16_t} pwm 占空比
 * @return {*}
 ****************************************************************************************/
void Start_motion(uint8_t num, uint8_t dir, uint16_t targe, uint16_t pwm)
{
    switch (num)
    {
    case 1:
        DIR_1 = dir;                         // 方向设置
        SMOTOR_1.target_value = targe * 400; // 圈速设置
        TIM_SetCompare1(TIM1, pwm);          // 占空比设置
        break;
    case 2:
        DIR_2 = dir;
        SMOTOR_2.target_value = targe * 400;
        TIM_SetCompare2(TIM1, pwm);
        break;
    case 3:
        DIR_3 = dir;
        SMOTOR_3.target_value = targe * 400;
        TIM_SetCompare3(TIM1, pwm);
        break;
    case 4:
        DIR_4 = dir;
        SMOTOR_4.target_value = targe * 400;
        TIM_SetCompare4(TIM1, pwm);
        break;
    default:
        break;
    }
    TIM1_PWM_Output(num, ENABLE); // 使能对应通道的PWM输出
}

/****************************************************************************************
 * @description: TIM1中断调用函数，用于控制步进电机转动指定角度
 * @return {*}
 ****************************************************************************************/
void Smotor_Angle_control(void)
{
    // 检查TIM1的CCER寄存器，CC1E位是否为1，为1则表示改通道PWM使能了
    if (TIM1->CCER & TIM_CCER_CC1E) // CC1E 是通道1的使能位
    {
        if (SMOTOR_1.count_value < SMOTOR_1.target_value)
        {
            SMOTOR_1.count_value++;
        }
        else
        {
            TIM1_PWM_Output(1, DISABLE); // 关闭通道1的PWM输出
            SMOTOR_1.count_value = 0;
        }
    }
    if (TIM1->CCER & TIM_CCER_CC2E)
    {
        if (SMOTOR_2.count_value < SMOTOR_2.target_value)
        {
            SMOTOR_2.count_value++;
        }
        else
        {
            TIM1_PWM_Output(2, DISABLE); // 关闭通道2的PWM输出
            SMOTOR_2.count_value = 0;
        }
    }
    if (TIM1->CCER & TIM_CCER_CC3E)
    {
        if (SMOTOR_3.count_value < SMOTOR_3.target_value)
        {
            SMOTOR_3.count_value++;
        }
        else
        {
            TIM1_PWM_Output(3, DISABLE); // 关闭通道3的PWM输出
            SMOTOR_3.count_value = 0;
        }
    }
    if (TIM1->CCER & TIM_CCER_CC4E)
    {
        if (SMOTOR_4.count_value < SMOTOR_4.target_value)
        {
            SMOTOR_4.count_value++;
        }
        else
        {
            TIM1_PWM_Output(4, DISABLE); // 关闭通道4的PWM输出
            SMOTOR_4.count_value = 0;
        }
    }
}
