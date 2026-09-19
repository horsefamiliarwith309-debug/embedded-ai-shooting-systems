#ifndef __DT_POSITION_H
#define __DT_POSITION_H

#include <stdint.h>

// 主流程调用的接口
void DT_Position_Request(uint8_t id);           // 请求读取位置
uint8_t DT_Position_Available(void);            // 是否有新数据（非阻塞）
float DT_Position_GetAngle(void);               // 获取角度值（单位度）

// 串口接收中断中调用
void DT_Position_UART_RX_Callback(uint8_t byte); // 每收到一个字节调用

#endif
