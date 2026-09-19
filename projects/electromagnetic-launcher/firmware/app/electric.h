#ifndef __ELECTRIC_H
#define __ELECTRIC_H

#include <stdbool.h>
#include <stdint.h>

#define Electric_On     HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,1);
#define Electric_Off    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,0);
#define Electric_Toggle HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_8);

#define Electric1_On     HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,1);
#define Electric1_Off    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,0);
#define Electric1_Toggle HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_3);

extern volatile uint32_t Receive;

void Shoot_read(void);

#endif // __ELECTRIC_H