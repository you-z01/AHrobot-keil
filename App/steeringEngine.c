/**
 * @Author: z
 * @Date: 2024-11-14
 * @LastEditTime: 2024-11-14
 * @Description: ������ƽӿ�
 * @FilePath: \AHrobot\App\steeringEngine.c
 */
#include "steeringEngine.h"

/****************************************************************************************
 * @description: �������
 * @param {u8} num ������ (1-6)
 * @param {float} Angle ת���Ƕ� (0-180�� 0-270��)
 * @param {ServoType} type ������ͣ�180�ȶ������270�ȶ��
 * @return {*}
 ****************************************************************************************/
void Sengine_setAngle(u8 num, float Angle, ServoType type)
{
	u16 pulseWidth; // �����������

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
		TIM_SetCompare1(TIM9, pulseWidth);
		break;
	case 2:
		TIM_SetCompare2(TIM9, pulseWidth);
		break;
	case 3:
		TIM_SetCompare1(TIM10, pulseWidth);
		break;
	case 4:
		TIM_SetCompare1(TIM11, pulseWidth);
		break;

	case 5:
		TIM_SetCompare1(TIM12, pulseWidth);
		break;
	case 6:
		TIM_SetCompare2(TIM12, pulseWidth);
		break;
	default:
		break;
	}
}

/****************************************************************************************
 * @description: ���PWM������ʼ��
 * @return {*}
 ****************************************************************************************/
void Sengine_Init(void)
{
	Sengine_PWM_TIM9_Init(20000 - 1, 84 - 1); // Ƶ��=84M/((20000)*(84))=50HZ
	Sengine_PWM_TIM10_Init(20000 - 1, 84 - 1);
	Sengine_PWM_TIM11_Init(20000 - 1, 84 - 1);
	Sengine_PWM_TIM12_Init(20000 - 1, 84 - 1);
}
