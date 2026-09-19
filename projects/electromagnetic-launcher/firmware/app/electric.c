#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"



volatile uint32_t Receive = 1;


void Shoot_read(void)
{
    
    Receive = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6);
    
}