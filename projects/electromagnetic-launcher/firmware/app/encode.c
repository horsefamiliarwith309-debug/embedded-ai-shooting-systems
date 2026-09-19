#include "tim.h"                // 包含自定义定时器配置
#include "usart.h" 
#include "global_time.h"
#include <stdio.h>
#include <string.h>
#include "gyro.h"
#include "eyes.h"
#include "five.h"
#include "do_scream.h"

int32_t encoderValueA = 0;
int32_t encoderValueB = 0;
int32_t encoderChangeA = 0;
int32_t encoderChangeB = 0;
int32_t lastValueA = 0;
int32_t lastValueB = 0;

int16_t EncoderA_Get(void)
{
	int16_t Temp;
    // 直接访问 TIM3 的 CNT 寄存器
    Temp = (int16_t)(TIM3->CNT);  // 获取计数器值
	return Temp;
}


int16_t EncoderB_Get(void)
{
	int16_t Temp;
    // 直接访问 TIM4 的 CNT 寄存器
    Temp = (int16_t)(TIM4->CNT);  // 获取计数器值
	return Temp;
}


// 发送数据到淘晶驰屏的函数
void send_to_tjc_screen(int32_t value, int index)
{
    char buffer[100];  // 用于存储发送的数据
    uint8_t end_cmd[3] = {0xFF, 0xFF, 0xFF};  // 结束符

    // 格式化成淘晶驰屏的指令
    sprintf(buffer, "t%d.txt=\"%d\"", index, value);
    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart2, end_cmd, 3, HAL_MAX_DELAY);  // 发送结束符
}


// 重载函数用于发送浮点数速度
void send_to_tjc_screen_float(float value, int index)
{
    char buffer[100];  // 用于存储发送的数据
    uint8_t end_cmd[3] = {0xFF, 0xFF, 0xFF};  // 结束符

    // 格式化成淘晶驰屏的指令
    sprintf(buffer, "t%d.txt=\"%.2f\"", index, value);
    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart2, end_cmd, 3, HAL_MAX_DELAY);  // 发送结束符
}

void read_encode(void)
{
    
    float speedA ,speedB;

	encoderValueA = EncoderA_Get();
    encoderValueB = EncoderB_Get();
	// 将编码器值转换为字符串，并通过串口发送
	encoderChangeA = encoderValueA - lastValueA;
	// 计算速度：单位是圈/秒，encoderChange为计数增量，11是每圈脉冲数，2是双通道模式
	speedA = (float)encoderChangeA / 0.1 / 11 / 2;

	// 发送编码器值、变化和速度到淘晶驰屏
    send_to_tjc_screen(Eye_Value1, 0);  // 发

	lastValueA = encoderValueA;
	
}