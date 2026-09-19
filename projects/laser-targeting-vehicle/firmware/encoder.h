#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>

// 外部可访问的变量声明
extern volatile int32_t Left_Count;    // 左轮编码器计数
extern volatile int32_t Right_Count;   // 右轮编码器计数

// 函数声明
void ENCODER_Init(void);
void GROUP1_IRQHandler(void);

#endif // ENCODER_H