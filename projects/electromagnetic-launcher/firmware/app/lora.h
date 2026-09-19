#ifndef __LORA_H
#define __LORA_H

#include "stdint.h"

// 声明函数
void LoRa_SendFrame(void);      // 发送 LoRa 帧函数
void LoRa_SetFlagCar(uint8_t flag);  // 设置 flag_car 值的函数

#endif
