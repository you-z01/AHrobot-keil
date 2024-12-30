/****************************************************************************************
 * @Author: z
 * @Date: 2024-11-14
 * @LastEditTime: 2024-11-14
 * @Description:
 * @FilePath: \AHrobot\App\steeringEngine.h
 ****************************************************************************************/
#ifndef __STEERINGENGINE_H
#define __STEERINGENGINE_H

#include "system.h"
typedef enum
{
    SERVO_180,
    SERVO_270
} ServoType;

void Sengine_setAngle(u8 num, float Angle, ServoType type);
void Sengine_Init(void);

#endif
