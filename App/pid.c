/**
 * @Author: z
 * @Date: 2024-11-13
 * @LastEditTime: 2024-11-14
 * @Description: PID�㷨
 * @FilePath: \AHrobot\App\pid.c
 */

#include "pid.h"

E_Motor_parameter EMOTOR_1, EMOTOR_2, EMOTOR_3, EMOTOR_4;

/****************************************************************************************
 * @description:��������ʽ��ɢPID��ʽ:pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
				e(k)������ƫ��
				e(k-1)������һ�ε�ƫ��  �Դ�����
				pwm�����������
 * @param {float} Actual_val ����������ֵ���˴�û��ʹ��M��ת��Ϊʵ�ʵ��ٶ�
 * @return {*}
 ****************************************************************************************/
int Incremental_PI_1(float Actual_val)
{
	/*����Ŀ��ֵ��ʵ��ֵ�����*/
	EMOTOR_1.err = EMOTOR_1.Target_Val - Actual_val;

	/*������*/
	EMOTOR_1.integral += EMOTOR_1.err;

	/*PID�㷨ʵ��*/
	EMOTOR_1.output_val = EMOTOR_1.Kp * EMOTOR_1.err +
						  EMOTOR_1.Ki * EMOTOR_1.integral +
						  EMOTOR_1.Kd * (EMOTOR_1.err - EMOTOR_1.err_last);

	/*����*/
	EMOTOR_1.err_last = EMOTOR_1.err;

	/*���ص�ǰʵ��ֵ*/
	return EMOTOR_1.output_val;
}
int Incremental_PI_2(float Actual_val)
{
	/*����Ŀ��ֵ��ʵ��ֵ�����*/
	EMOTOR_2.err = EMOTOR_2.Target_Val - Actual_val;

	/*������*/
	EMOTOR_2.integral += EMOTOR_2.err;

	/*PID�㷨ʵ��*/
	EMOTOR_2.output_val = EMOTOR_2.Kp * EMOTOR_2.err +
						  EMOTOR_2.Ki * EMOTOR_2.integral +
						  EMOTOR_2.Kd * (EMOTOR_2.err - EMOTOR_2.err_last);

	/*����*/
	EMOTOR_2.err_last = EMOTOR_2.err;

	/*���ص�ǰʵ��ֵ*/
	return EMOTOR_2.output_val;
}
int Incremental_PI_3(float Actual_val)
{
	/*����Ŀ��ֵ��ʵ��ֵ�����*/
	EMOTOR_3.err = EMOTOR_3.Target_Val - Actual_val;

	/*������*/
	EMOTOR_3.integral += EMOTOR_3.err;

	/*PID�㷨ʵ��*/
	EMOTOR_3.output_val = EMOTOR_3.Kp * EMOTOR_3.err +
						  EMOTOR_3.Ki * EMOTOR_3.integral +
						  EMOTOR_3.Kd * (EMOTOR_3.err - EMOTOR_3.err_last);

	/*����*/
	EMOTOR_3.err_last = EMOTOR_3.err;

	/*���ص�ǰʵ��ֵ*/
	return EMOTOR_3.output_val;
}
int Incremental_PI_4(float Actual_val)
{
	/*����Ŀ��ֵ��ʵ��ֵ�����*/
	EMOTOR_4.err = EMOTOR_4.Target_Val - Actual_val;

	/*������*/
	EMOTOR_4.integral += EMOTOR_4.err;

	/*PID�㷨ʵ��*/
	EMOTOR_4.output_val = EMOTOR_4.Kp * EMOTOR_4.err +
						  EMOTOR_4.Ki * EMOTOR_4.integral +
						  EMOTOR_4.Kd * (EMOTOR_4.err - EMOTOR_4.err_last);

	/*����*/
	EMOTOR_4.err_last = EMOTOR_4.err;

	/*���ص�ǰʵ��ֵ*/
	return EMOTOR_4.output_val;
}

/****************************************************************************************
 * @description: ����PWMֵ
 * @param {int} pwm_input PID������ֵ
 * @param {float} high ���ֵ
 * @param {float} low ���ֵ
 * @return {int}  �޷�������ֵ
 ****************************************************************************************/
int Limit_Pwm(int pwm_input, float high, float low)
{
	int pwm_output = 0;
	if (pwm_input > high)
	{
		pwm_output = high;
	}
	else if (pwm_input < low)
	{
		pwm_output = low;
	}
	else if ((pwm_input > -100) && (pwm_input < 100)) // ռ�ձ�̫С�����յ����̫С�����
	{
		pwm_output = 0;
	}
	else
	{
		pwm_output = pwm_input;
	}
	return pwm_output;
}

/****************************************************************************************
 * @description: ����Ŀ��ֵ
 * @param {int} number ������
 * @param {float} temp_val Ŀ��ֵ
 * @return {*}
 ****************************************************************************************/
void set_pid_target(int number, float temp_val)
{
	if (number == 1)
	{
		EMOTOR_1.Target_Val = temp_val; // ���õ�ǰ��Ŀ��ֵ
	}
	else if (number == 2)
	{
		EMOTOR_2.Target_Val = temp_val;
	}
	else if (number == 3)
	{
		EMOTOR_3.Target_Val = temp_val;
	}
	else if (number == 4)
	{
		EMOTOR_4.Target_Val = temp_val;
	}
}

/****************************************************************************************
 * @description: ���ñ��������֡�΢��ϵ��
 * @param {int} number ������
 * @param {float} p ����
 * @param {float} i ����
 * @param {float} d ΢��
 * @return {*}
 ****************************************************************************************/
void set_p_i_d(int number, float p, float i, float d)
{
	if (number == 1)
	{
		EMOTOR_1.Kp = p;
		EMOTOR_1.Ki = i;
		EMOTOR_1.Kd = d;
	}
	else if (number == 2)
	{
		EMOTOR_2.Kp = p;
		EMOTOR_2.Ki = i;
		EMOTOR_2.Kd = d;
	}
	else if (number == 3)
	{
		EMOTOR_3.Kp = p;
		EMOTOR_3.Ki = i;
		EMOTOR_3.Kd = d;
	}
	else if (number == 4)
	{
		EMOTOR_4.Kp = p;
		EMOTOR_4.Ki = i;
		EMOTOR_4.Kd = d;
	}
}

/****************************************************************************************
 * @description: �����ֵ
 * @param {long int} ������
 * @return {u32} �޷���������
 ****************************************************************************************/
u32 myabs(long int a)
{
	u32 temp;
	if (a < 0)
		temp = -a;
	else
		temp = a;
	return temp;
}

/****************************************************************************************
 * @description: ���������ݼ������ֵ
 * @param {float} insert ������
 * @return {float} �������ľ���ֵ
 ****************************************************************************************/
float float_abs(float insert)
{
	if (insert >= 0)
		return insert;
	else
		return -insert;
}

/****************************************************************************************
 * @description: PID������ʼ��
 * @param {int} number ������
 * @return {*}
 ****************************************************************************************/
void PID_param_init(int number)
{
#if (PID_ASSISTANT_EN)
	int32_t target_speed = 0;
	float pid_temp[3];
	if (number == 1)
	{
		pid_temp[0] = MOTOR_A.Kp;
		pid_temp[1] = MOTOR_A.Ki;
		pid_temp[2] = MOTOR_A.Kd;
		target_speed = (int32_t)MOTOR_A.Target_Val;
	}
	else if (number == 2)
	{
		pid_temp[0] = MOTOR_B.Kp;
		pid_temp[1] = MOTOR_B.Ki;
		pid_temp[2] = MOTOR_B.Kd;
		target_speed = (int32_t)MOTOR_B.Target_Val;
	}
	else if (number == 3)
	{
		pid_temp[0] = MOTOR_C.Kp;
		pid_temp[1] = MOTOR_C.Ki;
		pid_temp[2] = MOTOR_C.Kd;
		target_speed = (int32_t)MOTOR_C.Target_Val;
	}
	else if (number == 4)
	{
		pid_temp[0] = MOTOR_D.Kp;
		pid_temp[1] = MOTOR_D.Ki;
		pid_temp[2] = MOTOR_D.Kd;
		target_speed = (int32_t)MOTOR_D.Target_Val;
	}

	// ϵͳ��ʼʱ����λ�����ͳ�ʼֵ

	set_computer_value(SEND_P_I_D_CMD, CURVES_CH1, pid_temp, 3); // ��ͨ��1����PIDֵ

	set_computer_value(SEND_STOP_CMD, CURVES_CH1, NULL, 0);
	set_computer_value(SEND_TARGET_CMD, CURVES_CH1, &target_speed, 1); // ��ͨ��1����Ŀ��ֵ
#endif
}
