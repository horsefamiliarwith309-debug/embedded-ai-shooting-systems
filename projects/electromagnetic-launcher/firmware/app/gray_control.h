#ifndef GRAY_CONTROL_H
#define GRAY_CONTROL_H

#include <stdint.h>

// 定义 PID 控制的常量
#define P 2.8  // 比例常数
#define I 0.01  // 积分常数

// 函数声明
void GreyCameraControl(void);
void GreyCameraControlSlow(void);
    
#endif // GRAY_CONTROL_H