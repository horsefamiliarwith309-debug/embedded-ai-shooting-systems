#ifndef DO_SCREAM_H
#define DO_SCREAM_H

#include "stm32f4xx_hal.h"

// SCREAM 数据缓冲区
extern uint8_t SCREAM_DataBuf[10];   // SCREAM 数据缓冲区
extern uint16_t Length_0;
extern float Angle_0;

extern uint8_t flag0_1;
extern uint8_t flag_shoot;
// 函数声明
void processSCREAMData(uint8_t res);  // 处理 SCREAM 数据的函数
void controlLight(uint8_t state);     // 控制灯的亮灭函数
void Blind_Walk(uint8_t command);

#endif // DO_SCREAM_H
