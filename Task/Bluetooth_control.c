/**
 * @Author: z
 * @Date: 2024-11-14
 * @LastEditTime: 2024-11-14
 * @Description: ������������
 * @FilePath: \AHrobot\Task\Bluetooth_control.c
 */
#include "Bluetooth_control.h"
#include "system.h"
// #define Bluetooth_control_TASK_PRIO 4  // �������ȼ�
// #define Bluetooth_control_STK_SIZE 256 // �����ջ��С

extern u8 Recvl_Data[3]; // ���ڽ�������

/****************************************************************************************
 * @description: ������������
 * @param {void} *pvParameters ������������ʱ��Ҫ�ĳ�ʼ�����������������Ϣ
 * @return {*}
 ****************************************************************************************/
void Bluetooth_control_task(void *pvParameters)
{
	u32 lastWakeTime = getSysTickCnt();
	while (1)
	{
		vTaskDelayUntil(&lastWakeTime, F2T(100)); // ��������100Hz��Ƶ�����У�10ms����һ�Σ�

		switch (Recvl_Data[2])
		{
		case '1':
			Emotor_control(1, 500);
			Recvl_Data[2] = '0';
			break;
		case '2':
			Start_motion(1, 0, 1, 500);
			Recvl_Data[2] = '0';
			break;
		case '3':
			Sengine_setAngle(1, 90, SERVO_180);
			Recvl_Data[2] = '0';
			break;

		default:
			break;
		}
	}
}
