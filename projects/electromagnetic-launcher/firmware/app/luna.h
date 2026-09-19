#ifndef __LUNA_H
#define __LUNA_H

#include <stdbool.h>
#include <stdint.h>

// 测距模块状态定义
typedef enum {
    LUNA_WAIT_HEADER1,
    LUNA_WAIT_HEADER2,
    LUNA_RECEIVING_DATA
} LunaState;

// 全局变量声明
extern volatile uint16_t Luna_Distance;    // 距离值 (cm)
extern volatile bool Luna_DataValid;       // 数据是否有效标志
extern volatile uint16_t Luna_Amplitude;   // 信号强度值

// 函数声明
void Luna_ProcessData(uint8_t res);
void Luna_Init(void);

#endif // __LUNA_H