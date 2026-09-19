#include "usart.h"
#include "stm.h"
#include "Second.h"
#include "Third.h"
#include "Fifth.h"

extern UART_HandleTypeDef huart6;

void Stm_SendByte(uint8_t byte)
{
    HAL_UART_Transmit(&huart6, &byte, 1, HAL_MAX_DELAY);  // 发送单字节
}

// 帧头 55、n个变量 flag_car、帧尾 FF
void Stm_SendFrame(void)
{
    uint8_t startFrame = 0x55;
    uint8_t endFrame = 0xFF;

    // 发送帧头、flag_car、帧尾
    Stm_SendByte(startFrame);
    Stm_SendByte(Position2);
    Stm_SendByte(KP2);
    Stm_SendByte(KD2);
    Stm_SendByte(Position1);
    Stm_SendByte(KP1);
    Stm_SendByte(KD1);
    Stm_SendByte(Torque2);
    Stm_SendByte(endFrame);
}


// 帧头 55、n个变量 flag_car、帧尾 FF
void Stm_SendFrame1(void)
{
    uint8_t startFrame = 0x99;
    uint8_t endFrame = 0xFF;

    // 发送帧头、flag_car、帧尾
    Stm_SendByte(startFrame);
    Stm_SendByte(V1);
    Stm_SendByte(V2);
    Stm_SendByte(endFrame);
}

