/**
 * @Author: z
 * @Date: 2024-11-13
 * @LastEditTime: 2024-11-14
 * @Description: 编码电机控制接口
 * @FilePath: \AHrobot\App\encodingMotor.c
 */
#include "encodingMotor.h"

/****************************************************************************************
 * @description: 编码电机驱动初始化
 * @return {*}
 ****************************************************************************************/
void Emotor_Init(void)
{
	Emotor_GPIO_Init();
	Emotor_PWM_TIM8_Init(8400 - 1, 0); // 频率=168M/((8400+1)*(1))=20KHZ
}

/****************************************************************************************
 * @description: 电机控制
 * @param {u8} num 电机编号(1-4)
 * @param {int} pwm 电机转速(+- 表示正反)
 * @return {*}
 ****************************************************************************************/
void Emotor_control(u8 num, int pwm)
{
	switch (num)
	{
	case 1:
		if (pwm > 0)
			E1_IN1 = 0, E1_IN2 = 1; // 正转
		else if (pwm < 0)
			E1_IN1 = 1, E1_IN2 = 0; // 反转
		else if (pwm == 0)
			E1_IN1 = 0, E1_IN2 = 0;		 // 停止
		TIM_SetCompare1(TIM8, abs(pwm)); // 电机转速控制
		break;
	case 2:
		if (pwm > 0)
			E2_IN1 = 1, E2_IN2 = 0; // 正转
		else if (pwm < 0)
			E2_IN1 = 0, E2_IN2 = 1; // 反转
		else if (pwm == 0)
			E2_IN1 = 0, E2_IN2 = 0; // 停止
		TIM_SetCompare2(TIM8, abs(pwm));
		break;
	case 3:
		if (pwm > 0)
			E3_IN1 = 1, E3_IN2 = 0; // 正转
		else if (pwm < 0)
			E3_IN1 = 0, E3_IN2 = 1; // 反转
		else if (pwm == 0)
			E3_IN1 = 0, E3_IN2 = 0; // 停止
		TIM_SetCompare3(TIM8, abs(pwm));
		break;
	case 4:
		if (pwm > 0)
			E4_IN1 = 0, E4_IN2 = 1; // 正转
		else if (pwm < 0)
			E4_IN1 = 1, E4_IN2 = 0; // 反转
		else if (pwm == 0)
			E4_IN1 = 0, E4_IN2 = 0; // 停止
		TIM_SetCompare4(TIM8, abs(pwm));
		break;
	default:
		break;
	}
}

/****************************************************************************************
 * @description: 读取编码器计数
 * @param {u8} TIMX 读取哪一个定时器的编码值
 * @return {int} Encoder_TIM 返回编码器数值
 ****************************************************************************************/
int Read_Encoder(u8 TIMX)
{
	int Encoder_TIM;
	switch (TIMX)
	{
	case 2:
		Encoder_TIM = (short)TIM2->CNT;
		TIM2->CNT = 0;
		break;
	case 3:
		Encoder_TIM = (short)TIM3->CNT;
		TIM3->CNT = 0;
		break;
	case 4:
		Encoder_TIM = (short)TIM4->CNT;
		TIM4->CNT = 0;
		break;
	case 5:
		Encoder_TIM = (short)TIM5->CNT;
		TIM5->CNT = 0;
		break;
	default:
		Encoder_TIM = 0;
	}
	return Encoder_TIM;
}
