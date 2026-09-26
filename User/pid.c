#include "pid.h"
#include "motor.h"

void setPIDParam(Pid* pid,float kp,float ki,float kd,float integral_max)
{
    pid->kp=kp;
    pid->ki=ki;
    pid->kd=kd;
    pid->actual=0;
    pid->target=0;
    pid->error_now=0;
    pid->error_last=0;
    pid->error_integral=0;
    pid->ERROR_INTEGRAL_MAX=integral_max;
}
void updatePID(Pid* pid,float actual)
{
    pid->actual=actual;
    pid->error_now=pid->target-pid->actual;
    pid->error_integral+=pid->error_now;
    pid->error_integral=limit(pid->error_integral,pid->ERROR_INTEGRAL_MAX);
    pid->output=pid->kp*pid->error_now+pid->ki*pid->error_integral+pid->kd*(pid->error_now-pid->error_last);
    pid->error_last=pid->error_now;
}
void setPIDtarget(Pid* pid,float target)
{
    pid->target=target;
}
