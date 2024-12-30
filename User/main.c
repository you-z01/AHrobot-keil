/**
 * @Author: z
 * @Date: 2024-11-13
 * @LastEditTime: 2024-11-14
 * @Description: 程序主函数
 * @FilePath: \AHrobot\User\main.c
 */
#include "system.h"

#define mode (0) // 0: 裸机  1：FreeRTOS

#define START_TASK_PRIO 1       // 任务优先级
#define START_STK_SIZE 256      // 任务堆栈大小
TaskHandle_t StartTask_Handler; // 任务句柄

void start_task(void *pvParameters); // 任务函数

int main()
{
    SysTick_Init(168);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置系统中断优先级分组2(抢占0-3, 响应0-3)

    //USART1_Init(9600);
    LED_Init();

    Emotor_Init();  // f=20k
    Smotor_Init();  // f=1KHZ
    Sengine_Init(); // f=50HZ

#if !mode
    Start_motion(1, 0, 1, 500);
    Start_motion(2, 0, 1, 500);
    Start_motion(3, 0, 1, 500);
    Start_motion(4, 1, 1, 500);
    while (1)
    {
        Sengine_setAngle(1, 90, SERVO_180);
        delay_ms(1000);
        Sengine_setAngle(2, 200, SERVO_270);
        delay_ms(1000);
        Emotor_control(1, -3000);
        Emotor_control(2, 3000);
        Emotor_control(3, 3000);
        Emotor_control(4, 3000);
    }
#endif

#if mode

    // 创建开始任务
    xTaskCreate((TaskFunction_t)start_task,          // 任务函数
                (const char *)"start_task",          // 任务名称
                (uint16_t)START_STK_SIZE,            // 任务堆栈大小
                (void *)NULL,                        // 传递给任务函数的参数
                (UBaseType_t)START_TASK_PRIO,        // 任务优先级
                (TaskHandle_t *)&StartTask_Handler); // 任务句柄
    vTaskStartScheduler();                           // 开启任务调度
#endif
}

// 开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();

    xTaskCreate(Bluetooth_control_task, "Bluetooth_control_task", Bluetooth_control_STK_SIZE, NULL, Bluetooth_control_TASK_PRIO, NULL);

    // xTaskCreate(encoder_motorControl_task,	"encoder_motorControl_task",	E_MOTORCONTROL_STK_SIZE,	NULL, 	E_MOTORCONTROL_TASK_PRIO,	NULL);
    // xTaskCreate(step_motorControl_task,		"step_motorControl_task",		S_MOTORCONTROL_STK_SIZE,	NULL, 	S_MOTORCONTROL_TASK_PRIO, 	NULL);
    // xTaskCreate(data_task,    				"data_task",     				DATA_STK_SIZE,     			NULL, 	DATA_TASK_PRIO,     NULL);
    // xTaskCreate(line_patrol_task,    		"line_patrol_task",     		LIN_PATROL_STK_SIZE,     	NULL, 	LIN_PATROL_TASK_PRIO,    	NULL);

    vTaskDelete(StartTask_Handler);
    taskEXIT_CRITICAL();
}
