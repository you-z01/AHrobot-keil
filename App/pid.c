/**
 * @Author: z
 * @Date: 2024-11-13
 * @LastEditTime: 2024-11-14
 * @Description: PID算法
 * @FilePath: \AHrobot\App\pid.c
 */

#include "pid.h"

E_Motor_parameter EMOTOR_1, EMOTOR_2, EMOTOR_3, EMOTOR_4;

/****************************************************************************************
 * @description:根据增量式离散PID公式:pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
				e(k)代表本次偏差
				e(k-1)代表上一次的偏差  以此类推
				pwm代表增量输出
 * @param {float} Actual_val 编码器测量值。此处没有使用M法转换为实际的速度
 * @return {*}
 ****************************************************************************************/
int Incremental_PI_1(float Actual_val)
{
	/*计算目标值与实际值的误差*/
	EMOTOR_1.err = EMOTOR_1.Target_Val - Actual_val;

	/*积分项*/
	EMOTOR_1.integral += EMOTOR_1.err;

	/*PID算法实现*/
	EMOTOR_1.output_val = EMOTOR_1.Kp * EMOTOR_1.err +
						  EMOTOR_1.Ki * EMOTOR_1.integral +
						  EMOTOR_1.Kd * (EMOTOR_1.err - EMOTOR_1.err_last);

	/*误差传递*/
	EMOTOR_1.err_last = EMOTOR_1.err;

	/*返回当前实际值*/
	return EMOTOR_1.output_val;
}
int Incremental_PI_2(float Actual_val)
{
	/*计算目标值与实际值的误差*/
	EMOTOR_2.err = EMOTOR_2.Target_Val - Actual_val;

	/*积分项*/
	EMOTOR_2.integral += EMOTOR_2.err;

	/*PID算法实现*/
	EMOTOR_2.output_val = EMOTOR_2.Kp * EMOTOR_2.err +
						  EMOTOR_2.Ki * EMOTOR_2.integral +
						  EMOTOR_2.Kd * (EMOTOR_2.err - EMOTOR_2.err_last);

	/*误差传递*/
	EMOTOR_2.err_last = EMOTOR_2.err;

	/*返回当前实际值*/
	return EMOTOR_2.output_val;
}
int Incremental_PI_3(float Actual_val)
{
	/*计算目标值与实际值的误差*/
	EMOTOR_3.err = EMOTOR_3.Target_Val - Actual_val;

	/*积分项*/
	EMOTOR_3.integral += EMOTOR_3.err;

	/*PID算法实现*/
	EMOTOR_3.output_val = EMOTOR_3.Kp * EMOTOR_3.err +
						  EMOTOR_3.Ki * EMOTOR_3.integral +
						  EMOTOR_3.Kd * (EMOTOR_3.err - EMOTOR_3.err_last);

	/*误差传递*/
	EMOTOR_3.err_last = EMOTOR_3.err;

	/*返回当前实际值*/
	return EMOTOR_3.output_val;
}
int Incremental_PI_4(float Actual_val)
{
	/*计算目标值与实际值的误差*/
	EMOTOR_4.err = EMOTOR_4.Target_Val - Actual_val;

	/*积分项*/
	EMOTOR_4.integral += EMOTOR_4.err;

	/*PID算法实现*/
	EMOTOR_4.output_val = EMOTOR_4.Kp * EMOTOR_4.err +
						  EMOTOR_4.Ki * EMOTOR_4.integral +
						  EMOTOR_4.Kd * (EMOTOR_4.err - EMOTOR_4.err_last);

	/*误差传递*/
	EMOTOR_4.err_last = EMOTOR_4.err;

	/*返回当前实际值*/
	return EMOTOR_4.output_val;
}

/****************************************************************************************
 * @description: 限制PWM值
 * @param {int} pwm_input PID计算后的值
 * @param {float} high 最高值
 * @param {float} low 最低值
 * @return {int}  限幅处理后的值
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
	else if ((pwm_input > -100) && (pwm_input < 100)) // 占空比太小可能烧电机，太小则不输出
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
 * @description: 设置目标值
 * @param {int} number 电机编号
 * @param {float} temp_val 目标值
 * @return {*}
 ****************************************************************************************/
void set_pid_target(int number, float temp_val)
{
	if (number == 1)
	{
		EMOTOR_1.Target_Val = temp_val; // 设置当前的目标值
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
 * @description: 设置比例、积分、微分系数
 * @param {int} number 电机编号
 * @param {float} p 比例
 * @param {float} i 积分
 * @param {float} d 微分
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
 * @description: 求绝对值
 * @param {long int} 整型数
 * @return {u32} 无符号整型数
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
 * @description: 浮点型数据计算绝对值
 * @param {float} insert 浮点数
 * @return {float} 输入数的绝对值
 ****************************************************************************************/
float float_abs(float insert)
{
	if (insert >= 0)
		return insert;
	else
		return -insert;
}

/****************************************************************************************
 * @description: PID参数初始化
 * @param {int} number 电机编号
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

	// 系统开始时向上位机发送初始值

	set_computer_value(SEND_P_I_D_CMD, CURVES_CH1, pid_temp, 3); // 给通道1发送PID值

	set_computer_value(SEND_STOP_CMD, CURVES_CH1, NULL, 0);
	set_computer_value(SEND_TARGET_CMD, CURVES_CH1, &target_speed, 1); // 给通道1发送目标值
#endif
}
