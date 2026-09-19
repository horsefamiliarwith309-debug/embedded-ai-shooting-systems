#ifndef EYES_H
#define EYES_H

#include "stm32f4xx_hal.h"

// 全局变量定义
extern uint8_t Eye_DataBuf[4];    // 用于存储接收到的眼睛数据
extern uint8_t Eye_Value1;         // 第一个数字
extern uint8_t Eye_Value2;         // 第二个数字

extern uint8_t flag0_1;


// 函数声明
void processEyesData(uint8_t res); // 处理眼睛数据的函数

#endif // EYES_H
