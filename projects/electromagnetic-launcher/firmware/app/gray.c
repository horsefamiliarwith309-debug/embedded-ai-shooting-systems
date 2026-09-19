#include "tim.h"                // 包含自定义定时器配置
#include "global_time.h"
#include <stdio.h>
#include <string.h>


volatile uint32_t gray_1 = 0;
volatile uint32_t gray_2 = 0;
volatile uint32_t gray_3 = 0;
volatile uint32_t gray_4 = 0;
volatile uint32_t gray_5 = 0;
volatile uint32_t gray_6 = 0;
volatile uint32_t gray_7 = 0;
volatile uint32_t gray_8 = 0;


void Gray_read(void)
{
    gray_1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_10);
    gray_2 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
    gray_3 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
    gray_4 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
    gray_5 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
    gray_6 = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8);
    gray_7 = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_10);
    gray_8 = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14);
}