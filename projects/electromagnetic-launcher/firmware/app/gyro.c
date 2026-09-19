#include "tim.h"                // 包含定时器配置
#include "usart.h"              // 包含UART配置
#include "do_scream.h"
#include "eyes.h"
#include "luna.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "maix.h"
#include "stm_receive.h"

/* UART 数据包大小 */
#define UART_PACKET_SIZE (1) // 定义 UART 数据包大小为 1 字节

/* 从 UART 接收到的数据 */
volatile uint8_t gRxPacket1[UART_PACKET_SIZE]; // 用于存储接收到的 UART 数据包
volatile uint8_t gRxPacket2[UART_PACKET_SIZE]; // 用于存储接收到的 UART 数据包
volatile uint8_t gRxPacket3[UART_PACKET_SIZE]; // 用于存储接收到的 UART 数据包
volatile uint8_t gRxPacket4[UART_PACKET_SIZE]; // 用于存储接收到的 UART 数据包
volatile uint8_t gRxPacket5[UART_PACKET_SIZE]; // 用于存储接收到的 UART 数据包
volatile bool gCheckUART; // UART 接收数据标志

/* 陀螺仪数据缓冲区 */
uint8_t Gyro_STA = 0; // 陀螺仪数据状态
uint8_t Gyro_DataCnt = 0; // 陀螺仪数据计数
uint8_t Gyro_DataBuf[10]; // 陀螺仪数据缓冲区
float Gyro_DataYaw = 0.0f; // 陀螺仪偏航角度数据
float InitialYaw = 0.0f; // 开机时的角度
float RelativeYaw = 0.0f; // 相对角度
float CalculatedYaw = 0.0f; // 计算出的角度

/* 设置角度阈值 */
#define ANGLE_THRESHOLD 5.0f // 定义角度阈值为 5.0 度
#define P_FACTOR 1.0f // 调节系数 p

void processGyroData(uint8_t res); // 声明处理陀螺仪数据的函数
float Yaw_error(float Target, float Now); // 声明计算角度误差的函数
float float_abs(float value); // 声明自定义的绝对值函数


void read_gyro(void)
{
    // 将陀螺仪数据处理移到 UART 回调函数中，无需在这里处理
    RelativeYaw = Yaw_error(InitialYaw, Gyro_DataYaw) * P_FACTOR;
    CalculatedYaw = RelativeYaw;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == UART4)
    {
        processMaixData(gRxPacket1[0]); // 在接收完成回调函数中处理数据
        HAL_UART_Receive_IT(&huart4, (uint8_t *)gRxPacket1, UART_PACKET_SIZE); // 再次启动UART非阻塞接收
    }
    
    else if (huart->Instance == USART2) // 监听 UART2 接口
    {
        processSCREAMData(gRxPacket2[0]); // 处理接收到的数据
        HAL_UART_Receive_IT(&huart2, (uint8_t *)gRxPacket2, UART_PACKET_SIZE); // 启动非阻塞接收
    }
    
    else if (huart->Instance == USART3) // 监听 UART3 接口
    {
        Luna_ProcessData(gRxPacket3[0]); // 处理接收到的数据
        HAL_UART_Receive_IT(&huart3, (uint8_t *)gRxPacket3, UART_PACKET_SIZE); // 启动非阻塞接收
    }
    
    else if (huart->Instance == USART6) // 监听 UART6 接口
    {
        Stm_Receive_Process(gRxPacket4[0]);
        HAL_UART_Receive_IT(&huart6, (uint8_t *)gRxPacket4, UART_PACKET_SIZE); // 启动非阻塞接收
    }
    
    else if (huart->Instance == USART1) // 监听 UART1 接口
    {
        Luna_ProcessData(gRxPacket5[0]); // 处理接收到的数据
        HAL_UART_Receive_IT(&huart1, (uint8_t *)gRxPacket5, UART_PACKET_SIZE); // 启动非阻塞接收   
    }
}

void processGyroData(uint8_t res)
{
    uint8_t errFlag = 0; // 错误标志

    switch (Gyro_STA)
    {
        case 0:
            if (res == 0x55)
            {
                Gyro_STA = 1; // 状态 1
            } 
            else
            {
                errFlag = 1; // 错误标志
            }
            break;

        case 1:
            if (res == 0x53)
            {
                Gyro_STA = 2; // 状态 2
            } 
            else
            {
                errFlag = 1; // 错误标志
            }
            break;

        case 2:
            Gyro_DataBuf[Gyro_DataCnt++] = res; // 存储数据
            if (Gyro_DataCnt >= 8) // 判断
            {
                Gyro_STA = 3; // 进入状态 3
            }
            break;

        case 3:
            Gyro_STA = 0xFF; // 完成状态
            break;

        default:
            break;
    }

    if (errFlag) // 检查是否存在错误
    {
        Gyro_STA = 0; // 重置状态
        Gyro_DataCnt = 0; // 重置数据计数
    }

    if (Gyro_STA == 0xFF) // 检查是否完成数据接收
    {
        Gyro_DataYaw = (float)((int16_t)((Gyro_DataBuf[5] << 8) | Gyro_DataBuf[4]) / 32768.0f * 180.0f); // 计算角度
        Gyro_STA = 0; // 重置状态
        Gyro_DataCnt = 0; // 重置数据计数

        if (InitialYaw == 0.0f) // 初始化时设置开机角度
        {
            InitialYaw = Gyro_DataYaw; // 设置开机时的角度
        }
    }
}

float Yaw_error(float Target, float Now) 
{
    static float error;
    if (Target > 0) 
    {
        if (Now <= 0) 
        {
            if (float_abs(Now) < (180 - Target)) 
            {
                error = float_abs(Now) + Target;
            } 
            else 
            {
                error = -(180 - Target) - (180 - float_abs(Now));
            }
        } 
        else 
        {
            error = Target - Now;
        }
    } 
    else if (Target < 0)
    {
        if (Now > 0) 
        {
            if (Now > Target + 180)
            {
                error = (180 - Now) + (180 - float_abs(Target));
            }
            else 
            {
                error = -(float_abs(Target) + Now);
            }
        } 
        else 
        {
            error = -(float_abs(Target) - float_abs(Now));
        }
    }
    
    return error;
}

float float_abs(float value) {
    return value < 0 ? -value : value;
}
