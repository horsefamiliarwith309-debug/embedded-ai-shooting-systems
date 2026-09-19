#ifndef GYRO_H
#define GYRO_H

#include "stm32f4xx_hal.h"

// UART 数据包大小
#define UART_PACKET_SIZE (1) 

// 陀螺仪相关变量和常量
extern uint8_t Gyro_STA;           // 陀螺仪数据状态
extern uint8_t Gyro_DataCnt;       // 陀螺仪数据计数
extern uint8_t Gyro_DataBuf[10];   // 陀螺仪数据缓冲区
extern float Gyro_DataYaw;         // 陀螺仪偏航角度数据
extern float InitialYaw;           // 开机时的角度
extern float RelativeYaw;          // 相对角度
extern float CalculatedYaw;        // 计算出的角度

// 角度阈值和调节系数
#define ANGLE_THRESHOLD 5.0f       // 角度阈值
#define P_FACTOR 1.0f              // 调节系数 p

// 函数声明
void read_gyro(void);
void processGyroData(uint8_t res);  // 处理陀螺仪数据
float Yaw_error(float Target, float Now);  // 计算角度误差
float float_abs(float value);  // 绝对值函数
void UART_ReceiveGyroData_IT(UART_HandleTypeDef *huart);  // 中断接收函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);  // UART 回调函数

#endif // GYRO_H
