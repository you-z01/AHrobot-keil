/**
 * @Author: z
 * @Date: 2024-11-14
 * @LastEditTime: 2024-11-14
 * @Description: 舵机控制接口
 * @FilePath: \AHrobot\App\steeringEngine.c
 */
#include "steeringEngine.h"

/****************************************************************************************
 * @description: 舵机控制
 * @param {u8} num 舵机编号 (1-6)
 * @param {float} Angle 转动角度 (0-180度 0-270度)
 * @param {ServoType} type 舵机类型，180度舵机或者270度舵机
 * @return {*}
 ****************************************************************************************/
void Sengine_setAngle(u8 num, float Angle, ServoType type)
{
	u16 pulseWidth; // 计算的脉冲宽度

	if (type == SERVO_180 && (Angle >= 0 && Angle <= 180))
	{
		pulseWidth = Angle / 180 * 2000 + 500;
	}
	else if (type == SERVO_270 && (Angle >= 0 || Angle <= 270))
	{
		pulseWidth = Angle / 270 * 2000 + 500;
	}
	else
		return;

	switch (num)
	{
	case 1:
		TIM_SetCompare1(TIM4, pulseWidth);
		break;
	case 2:
		TIM_SetCompare2(TIM4, pulseWidth);
		break;
	case 3:
		TIM_SetCompare3(TIM4, pulseWidth);
		break;
	case 4:
		TIM_SetCompare4(TIM4, pulseWidth);
		break;

	case 5:
		TIM_SetCompare1(TIM5, pulseWidth);
		break;
	case 6:
		TIM_SetCompare2(TIM5, pulseWidth);
		break;
	default:
		break;
	}
}

/****************************************************************************************
 * @description: 舵机PWM驱动初始化
 * @return {*}
 ****************************************************************************************/
void Sengine_Init(void)
{
	Sengine_PWM_TIM4_Init(20000 - 1, 84 - 1); // 频率=84M/((20000)*(84))=50HZ
	Sengine_PWM_TIM5_Init(20000 - 1, 84 - 1); // 频率=84M/((20000)*(84))=50HZ
}
