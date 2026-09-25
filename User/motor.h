#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f1xx_hal.h"
#define MOTOR_PWM_MAX 999

typedef enum{
    right,
    left
}MotorChoice;

void MotorSpeed(MotorChoice right_or_left, int16_t pwm_val);
float limit(float input,float MAX);

#endif