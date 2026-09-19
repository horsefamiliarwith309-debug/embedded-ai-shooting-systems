#include "tim.h"
#include "gpio.h"


void Set_Speed(uint8_t side, int8_t duty)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);  // Start PWM on channel 1
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);  // Start PWM on channel 4 
    
    uint32_t compareValue = 0;
    
    if(side == 0) // 左电机控制
    {
        if(duty > 0) // 前进
        {
            compareValue = 16800 * (duty / 100.0);  // 正向占空比
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, compareValue);  // 设置PWM比较值
            
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);  // 设置IN1高电平，前进
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); // 设置IN2低电平
        }
        else if(duty < 0) // 后退
        {
            compareValue = 16800 * (-duty / 100.0); // 反向占空比
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, compareValue);  // 设置PWM比较值

            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);  // 设置IN1低电平，后退
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);  // 设置IN2高电平
        }
        else // 停止
        {
            // 停止时，将两个控制引脚都置为低电平
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); 
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); 
        }
    }
    else // 右电机控制
    {
        if(duty > 0) // 前进
        {
            compareValue = 16800 * (duty / 100.0);  // 正向占空比
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, compareValue);  // 设置PWM比较值
            
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);  // 设置IN1高电平，前进
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // 设置IN2低电平
        }
        else if(duty < 0) // 后退
        {
            compareValue = 16800 * (-duty / 100.0);  // 反向占空比
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, compareValue);  // 设置PWM比较值

            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);  // 设置IN1低电平，后退
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);  // 设置IN2高电平
        }
        else // 停止
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET); 
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 
        }
    }
}




//void Set_Speed(uint8_t side, int8_t duty)
//{
//    
//    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);  // Start PWM on channel 1
//    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);  // Start PWM on channel 4 
//    
//    uint32_t compareValue = 0;
//    
//    if(side == 0) // 左电机控制
//    {
//        if(duty > 0) //前进
//        {
//            compareValue = 16800 - 16800 * (duty / 100.0); 
//            
//            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, compareValue);  // 通道 1 的 PWM 比较值 
//            

//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);  
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); 
//        }
//        else if(duty < 0) // 后退
//        {
//            
//            compareValue = 16800 - 16800 * (-duty / 100.0); 

//            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, compareValue);  // 通道 1 的 PWM 比较值 

//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); 
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);  
//        }
//        else // 停止
//        {
//            // 将两个控制引脚都置为低电平
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // 清除 IN1 引脚
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); // 清除 IN2 引脚
//        }
//    }
//    else // 右电机控制
//    {
//        if(duty > 0) // 前进方向
//        {
//            // 计算 PWM 比较值
//            compareValue = 16800 - 16800 * (duty / 100.0); 
//            
//            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, compareValue); 
//            
//            // 设置控制引脚，IN1 置为高电平（前进），IN2 置为低电平（停止）
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);  
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); 
//        }
//        else if(duty < 0) // 后退方向
//        {
//            // 计算 PWM 比较值
//            compareValue = 16800 - 16800 * (-duty / 100.0); 
//            
//            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, compareValue); 

//            // 设置控制引脚，IN1 置为低电平（停止），IN2 置为高电平（后退）
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET); 
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);  
//        }
//        else // 停止
//        {
//            // 将两个控制引脚都置为低电平
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET); // 清除 IN1 引脚
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // 清除 IN2 引脚
//        }
//    }
//}
