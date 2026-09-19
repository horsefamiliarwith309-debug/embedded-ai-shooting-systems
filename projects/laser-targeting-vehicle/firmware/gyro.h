#ifndef __GYRO_H
#define __GYRO_H

#include <stdint.h>
#include "ti_msp_dl_config.h"

// ================== 宏定义 ==================
#define GYRO_STATE_WAIT_HEADER   0
#define GYRO_STATE_READ_DATA     1
#define GYRO_STATE_WAIT_TAIL     2

#define GYRO_HEADER              0x55
#define GYRO_FRAME_RATE          0x52
#define GYRO_FRAME_ANGLE         0x53

#define P_FACTOR                 1.0f   // 偏航误差比例因子

// ================== 全局变量声明 ==================

// 角速度 (°/s)
extern volatile float gyro_wx;
extern volatile float gyro_wy;
extern volatile float gyro_wz;

// 角度 (°)
extern volatile float gyro_roll;
extern volatile float gyro_pitch;
extern volatile float Gyro_Yaw;

// 相对偏航角 (°)
extern volatile float gyro_relative_yaw;
extern volatile float RelativeYaw;
extern volatile float InitialYaw;

// 数据接收完成标志
extern volatile uint8_t gyro_data_received;

// ================== 接口函数 ==================
void gyro_process_data(uint8_t data);
float yaw_error(float target, float now);

#endif
