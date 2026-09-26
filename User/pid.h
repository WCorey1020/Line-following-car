#ifndef __PID_H
#define __PID_H
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

void setPIDParam(Pid* pid,float kp,float ki,float kd,float integral_max);
void updatePID(Pid* pid,float actual);
void setPIDtarget(Pid* pid,float target);

#endif
