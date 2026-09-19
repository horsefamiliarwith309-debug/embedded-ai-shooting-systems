#ifndef __GRAY_H__
#define __GRAY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"  // Include the appropriate HAL library
#include "gpio.h"           // Include the GPIO configuration

/**
 * @brief External variables to store gray sensor values.
 */
extern volatile uint32_t gray_1;
extern volatile uint32_t gray_2;
extern volatile uint32_t gray_3;
extern volatile uint32_t gray_4;
extern volatile uint32_t gray_5;
extern volatile uint32_t gray_6;
extern volatile uint32_t gray_7;
extern volatile uint32_t gray_8;

/**
 * @brief Reads the values from gray sensors and stores them in global variables.
 */
void Gray_read(void);


#ifdef __cplusplus
}
#endif

#endif /* __GRAY_H__ */
