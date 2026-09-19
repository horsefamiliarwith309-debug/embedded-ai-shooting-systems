#ifndef GRAY_H
#define GRAY_H

#include "ti/driverlib/dl_gpio.h"
#include "ti_msp_dl_config.h"

// 声明灰度传感器读取值的变量
extern volatile uint32_t val_1;
extern volatile uint32_t val_2;
extern volatile uint32_t val_3;
extern volatile uint32_t val_4;
extern volatile uint32_t val_5;

// 声明灰度传感器处理函数
void GreyCamera(void);

#endif // GRAY_H