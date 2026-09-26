#include "motor.h"
#include "main.h"
#include "tim.h"

float limit(float input,float MAX)
{
    input=input>MAX?MAX:input;
    input=input<-MAX?-MAX:input;
    return input;
}

float limit_output(float output)
{
    output=output>MOTOR_PWM_MAX?MOTOR_PWM_MAX:output;
    output=output<-MOTOR_PWM_MAX?-MOTOR_PWM_MAX:output;
    return output;
}

void MotorSpeed(MotorChoice right_or_left, int16_t pwm_val)
{
    if(right_or_left==right)
    {
        if(pwm_val>0)
    {
        HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,limit_output(pwm_val));
    }
    else if(pwm_val<0)
    {
        HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,-limit_output(pwm_val));
    }
    else if(pwm_val==0)
    { 
        HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);
    }
    }
    else if(right_or_left==left)
    {
         if(pwm_val>0)
    {
        HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,limit_output(pwm_val));
    }
    else if(pwm_val<0)
    {
        HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,-limit_output(pwm_val));
    }
    else if(pwm_val==0)
    {
        HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
    }
    }
}
