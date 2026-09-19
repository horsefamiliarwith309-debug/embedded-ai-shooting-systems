#ifndef __EYES1_H
#define __EYES1_H

#include <stdint.h>

// 全局变量声明
extern volatile uint8_t eye_x[5];       // 5个点的X坐标 (0-255)
extern volatile uint8_t eye_y[5];       // 5个点的Y坐标 (0-255)
extern volatile uint8_t eyes1_data_received;

/**
 * @brief 处理接收到的眼睛坐标数据
 * @param data 接收到的字节数据
 */
void eyes1_process_data(uint8_t data);

#endif /* __EYES1_H */