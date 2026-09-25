#include "pid.h"
#include "interrupt_main.h"
#include "motor.h"

float l_speed=0,r_speed=0;
void Speed_Calculate(void)
{
    l_speed=(float)l_counter/(4*13*28)/10*1000*60;
    r_speed=(float)r_counter/(4*13*28)/10*1000*60;
}


//PID
void Pid_Init(Pid* pid,float kp,float ki,float kd,float integral_max)
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

int16_t Pid_Calculate(Pid* pid)
{
    pid->error_now=pid->target-pid->actual;
    pid->error_integral+=pid->error_now;
    pid->error_integral=limit(pid->error_integral,pid->ERROR_INTEGRAL_MAX);
    pid->output=pid->kp*pid->error_now+pid->ki*pid->error_integral+pid->kd*(pid->error_now-pid->error_last);
    pid->error_last=pid->error_now;
    return  pid->output;
}
