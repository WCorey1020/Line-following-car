#include "tim.h"
#include "uart.h"
#include "motor.h"
#include "usart.h"
#include "pid.h"

extern uint8_t dma_rx_buf[128];
uint8_t A[128],B[128];
uint8_t* rx_write_buf=A;
uint8_t* rx_read_buf=B;
uint16_t len;
uint16_t flag=0;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(huart==&huart1)
    {
        memcpy(rx_write_buf,dma_rx_buf,Size);
        uint8_t*temp=rx_write_buf;
        rx_write_buf=rx_read_buf;
        rx_read_buf=temp;
        flag=1;
        len=Size;
        HAL_UARTEx_ReceiveToIdle_DMA(&huart1,dma_rx_buf,128);
        __HAL_DMA_DISABLE_IT(huart1.hdmarx, DMA_IT_HT);
    }
}
/*//定速
int16_t counter=0;
float speed_w=0;

float kd=2;
float ki=5;
float kp=20;
float target=-200;
float error_now=0;
float error_last=0;
float error_integral=0;
float output=0;
const float ERROR_INTEGRAL_MAX=2000;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==&htim1)
    {
        counter=(int16_t)__HAL_TIM_GetCounter(&htim2);
        __HAL_TIM_SET_COUNTER(&htim2,0);
        speed_w=(float)counter/(4*13*28)/10*1000*60;
        error_now=target-speed_w;
        error_integral+=error_now;
        limit(error_integral,ERROR_INTEGRAL_MAX);
        output=kp*error_now+ki*error_integral+kd*(error_now-error_last);
        error_last=error_now;
        UART_Sending("%.2f,%.2f,%.2f\n",target,speed_w,output);
        
        MotorSpeed(output);         
    }
}

 //定位
int32_t counter=0;

float kd=0;
float ki=0.01;
float kp=1;
int target=1000;
float error_now=0;
float error_last=0;
float error_integral=0;
float output=0;
const float ERROR_INTEGRAL_MAX=2000;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==&htim1)
    {
        counter=(int16_t)__HAL_TIM_GetCounter(&htim2);
        error_now=target-counter;
        error_integral+=error_now;
        limit(error_integral,ERROR_INTEGRAL_MAX);
        output=kp*error_now+ki*error_integral+kd*(error_now-error_last);
        error_last=error_now;
        UART_Sending("%d,%d,%.2f\n",target,counter,output);
        
        MotorSpeed(output);
    }
}*/

float kd_s=2;
float ki_s=5;
float kp_s=20;
extern float target_s;
float error_now_s=0;
float error_last_s=0;
float error_integral_s=0;
float output_s=0;

float kd_p=0;
float ki_p=0.01;
float kp_p=1;
extern int target_p;
float error_now_p=0;
float error_last_p=0;
float error_integral_p=0;
float output_p=0;

const float ERROR_INTEGRAL_MAX=2000;

int32_t counter=0;
float speed_w=0;
extern uint8_t mode;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==&htim1)
    {
        if(mode==1)
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
            MotorSpeed(output_s);
        }
        else if(mode==2)
        {
            //位置定位模式
            counter=(int16_t)__HAL_TIM_GetCounter(&htim2);
            error_now_p=target_p-counter;
            error_integral_p+=error_now_p;
            limit(error_integral_p,ERROR_INTEGRAL_MAX);
            output_p=kp_p*error_now_p+ki_p*error_integral_p+kd_p*(error_now_p-error_last_p);
            error_last_p=error_now_p;

            UART_Sending("%d,%d,%.2f\n",target_p,counter,output_p);
            MotorSpeed(output_p);
        }
    }
}


