#ifndef __STM_RECEIVE_H
#define __STM_RECEIVE_H

#include "stdint.h"

// 声明接收到的位置变量
extern uint16_t received_position;  // 接收到的原始位置值(1000-7000)
extern float actual_position;       // 转换后的实际位置值(-30.0到30.0)

// 接收处理函数声明
void Stm_Receive_Process(uint8_t res);

#endif /* __STM_RECEIVE_H */