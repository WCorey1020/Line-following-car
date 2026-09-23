#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"
#define MOTOR_PWM_MAX 999

void MotorSpeed(int16_t pwm_val);
float limit(float input,float MAX);

#endif