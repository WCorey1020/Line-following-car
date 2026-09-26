#include "tim.h"
#include "pid.h"
#include "motor.h"
#include "uart.h"

int32_t l_counter=0,r_counter=0;
float l_speed=0,r_speed=0;
Pid l_pid,r_pid;
Pid pos_pid;//chuanganqi 

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==&htim1)
    {
        l_counter=(int16_t)__HAL_TIM_GetCounter(&htim4);
        l_speed=(float)l_counter/(4*13*28)/10*1000*60;
        __HAL_TIM_SET_COUNTER(&htim4,0);
        r_counter=(int16_t)__HAL_TIM_GetCounter(&htim2);
        r_speed=(float)r_counter/(4*13*28)/10*1000*60;
        __HAL_TIM_SET_COUNTER(&htim2,0);

        //左轮匀速
        updatePID(&l_pid,l_speed);
        MotorSpeed(left,l_pid.output);
        //UART_Sending("%.2f,%.2f,%.2f\n",l_pid.target,l_pid.actual,l_pid.output);

        //右轮变速 串级pid
        // updatePID(&pos_pid,pos_pid.actual);
        // setPIDtarget(&r_pid,pos_pid.output);
        updatePID(&r_pid,r_speed);
        MotorSpeed(right,r_pid.output);
        UART_Sending("%.2f,%.2f,%.2f\n",r_pid.target,r_pid.actual,r_pid.output);
    }
}


