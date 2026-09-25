#include "tim.h"

volatile int32_t r_counter=0,l_counter=0;
volatile uint8_t speed_flag=0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==&htim1)
    {
        r_counter=(int16_t)__HAL_TIM_GetCounter(&htim4);
        __HAL_TIM_SET_COUNTER(&htim4,0);
        l_counter=(int16_t)__HAL_TIM_GetCounter(&htim2);
        __HAL_TIM_SET_COUNTER(&htim2,0);
       speed_flag=1;
    }
}


