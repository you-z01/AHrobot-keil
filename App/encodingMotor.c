/**
 * @Author: z
 * @Date: 2024-11-13
 * @LastEditTime: 2024-11-14
 * @Description: ���������ƽӿ�
 * @FilePath: \AHrobot\App\encodingMotor.c
 */
#include "encodingMotor.h"

/****************************************************************************************
 * @description: ������������ʼ��
 * @return {*}
 ****************************************************************************************/
void Emotor_Init(void)
{
	Emotor_GPIO_Init();
	Emotor_PWM_TIM8_Init(8400 - 1, 0); // Ƶ��=168M/((8400+1)*(1))=20KHZ
}

/****************************************************************************************
 * @description: �������
 * @param {u8} num ������(1-4)
 * @param {int} pwm ���ת��(+- ��ʾ����)
 * @return {*}
 ****************************************************************************************/
void Emotor_control(u8 num, int pwm)
{
	switch (num)
	{
	case 1:
		if (pwm > 0)
			E1_IN1 = 0, E1_IN2 = 1; // ��ת
		else if (pwm < 0)
			E1_IN1 = 1, E1_IN2 = 0; // ��ת
		else if (pwm == 0)
			E1_IN1 = 0, E1_IN2 = 0;		 // ֹͣ
		TIM_SetCompare1(TIM8, abs(pwm)); // ���ת�ٿ���
		break;
	case 2:
		if (pwm > 0)
			E2_IN1 = 1, E2_IN2 = 0; // ��ת
		else if (pwm < 0)
			E2_IN1 = 0, E2_IN2 = 1; // ��ת
		else if (pwm == 0)
			E2_IN1 = 0, E2_IN2 = 0; // ֹͣ
		TIM_SetCompare2(TIM8, abs(pwm));
		break;
	case 3:
		if (pwm > 0)
			E3_IN1 = 1, E3_IN2 = 0; // ��ת
		else if (pwm < 0)
			E3_IN1 = 0, E3_IN2 = 1; // ��ת
		else if (pwm == 0)
			E3_IN1 = 0, E3_IN2 = 0; // ֹͣ
		TIM_SetCompare3(TIM8, abs(pwm));
		break;
	case 4:
		if (pwm > 0)
			E4_IN1 = 0, E4_IN2 = 1; // ��ת
		else if (pwm < 0)
			E4_IN1 = 1, E4_IN2 = 0; // ��ת
		else if (pwm == 0)
			E4_IN1 = 0, E4_IN2 = 0; // ֹͣ
		TIM_SetCompare4(TIM8, abs(pwm));
		break;
	default:
		break;
	}
}

/****************************************************************************************
 * @description: ��ȡ����������
 * @param {u8} TIMX ��ȡ��һ����ʱ���ı���ֵ
 * @return {int} Encoder_TIM ���ر�������ֵ
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
