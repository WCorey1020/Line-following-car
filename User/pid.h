#ifndef __PID_H
#define __PID_H
#include "interrupt_main.h"
#include "stdint.h"

typedef struct
{
    float kp;
    float ki;
    float kd;
    float target;
    float actual;
    float error_now;
    float error_last;
    float error_integral;
    float output;
    float ERROR_INTEGRAL_MAX;
}Pid;

extern float l_speed,r_speed;

void Speed_Calculate(void);

void Pid_Init(Pid* pid,float kp,float ki,float kd,float integral_max);
int16_t Pid_Calculate(Pid* pid);

#endif
