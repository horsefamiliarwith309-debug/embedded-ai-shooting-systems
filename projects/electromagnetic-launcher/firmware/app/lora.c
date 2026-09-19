#include "usart.h"
#include "lora.h"
#include "lora_s.h"
#include "three_four.h"
#include "five.h"
#include "three_four.h"

extern UART_HandleTypeDef huart6;

void LoRa_SendByte(uint8_t byte)
{
    HAL_UART_Transmit(&huart6, &byte, 1, HAL_MAX_DELAY);  // 发送单字节
}

// 帧头 55、n个变量 flag_car、帧尾 FF
void LoRa_SendFrame(void)
{
    uint8_t startFrame = 0x55;
    uint8_t endFrame = 0xFF;

    // 发送帧头、flag_car、帧尾
    LoRa_SendByte(startFrame);
    LoRa_SendByte(flag_car);
    LoRa_SendByte(flag_car_1);
    LoRa_SendByte(flag_car_2);
    LoRa_SendByte(endFrame);
}

