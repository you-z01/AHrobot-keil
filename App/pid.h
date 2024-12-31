
#ifndef __PID_H
#define __PID_H

#include "stm32f4xx.h"

#define PID_ASSISTANT_EN (0) // 1:使用PID调试助手显示波形，0：使用串口直接打印数据

// 编码电机控制相关参数结构体
typedef struct
{
    float Encoder_num; // 编码器读取到的数值
    float Target_Val;  // 目标值
    int PID_PWM;       // 计算后的PWM

    float err;        // 偏差值
    float err_last;   // 上一个偏差值
    float Kp, Ki, Kd; // 比例、积分、微分系数
    float integral;   // 积分值
    float output_val; // 输出值
} E_Motor_parameter;

int Incremental_PI_1(float Actual_val);
int Incremental_PI_2(float Actual_val);
int Incremental_PI_3(float Actual_val);
int Incremental_PI_4(float Actual_val);

int Limit_Pwm(int pwm_input, float high, float low);
void set_pid_target(int number, float temp_val);
void set_p_i_d(int number, float p, float i, float d);
u32 myabs(long int a);
float float_abs(float insert);
void PID_param_init(int number);

#endif
