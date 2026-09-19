#ifndef __MOTOR_H__
#define __MOTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "tim.h"
#include "gpio.h"
#include "main.h"

#define MOTOR_LEFT  0
#define MOTOR_RIGHT 1

#define MAX_DUTY_CYCLE 100
#define MIN_DUTY_CYCLE 0

void Motor_On(void);

void Motor_Off(void);

int Set_Speed(uint8_t side, int8_t duty);

#ifdef __cplusplus
}
#endif

#endif /* __MOTOR_H__ */
