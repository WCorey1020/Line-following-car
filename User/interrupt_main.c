#include "tim.h"

int32_t r_counter=0,l_counter=0;
uint8_t speed_flag=0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==&htim1)
    {
        r_counter=(int16_t)__HAL_TIM_GetCounter(&htim4);
        __HAL_TIM_SET_COUNTER(&htim4,0);
        l_counter=(int16_t)__HAL_TIM_GetCounter(&htim2);
        __HAL_TIM_SET_COUNTER(&htim2,0);
       speed_flag=1;
        /*if(mode==2)
        {
            //速度模式
            counter=(int16_t)__HAL_TIM_GetCounter(&htim2);
            __HAL_TIM_SET_COUNTER(&htim2,0);
            speed_w=(float)counter/(4*13*28)/10*1000*60;

            error_now_s=target_s-speed_w;
            error_integral_s+=error_now_s;
            limit(error_integral_s,ERROR_INTEGRAL_MAX);
            output_s=kp_s*error_now_s+ki_s*error_integral_s+kd_s*(error_now_s-error_last_s);
            error_last_s=error_now_s;

            UART_Sending("%.2f,%.2f,%.2f\n",target_s,speed_w,output_s);
            MotorSpeed(left,output_s);
        }
        else if(mode==1)
        {
            //速度模式
            counter=(int16_t)__HAL_TIM_GetCounter(&htim4);
            __HAL_TIM_SET_COUNTER(&htim4,0);
            speed_w=(float)counter/(4*13*28)/10*1000*60;

            error_now_s=target_s-speed_w;
            error_integral_s+=error_now_s;
            limit(error_integral_s,ERROR_INTEGRAL_MAX);
            output_s=kp_s*error_now_s+ki_s*error_integral_s+kd_s*(error_now_s-error_last_s);
            error_last_s=error_now_s;

            UART_Sending("%.2f,%.2f,%.2f\n",target_s,speed_w,output_s);
            MotorSpeed(right,output_s);
        }*/ 
    }
}


