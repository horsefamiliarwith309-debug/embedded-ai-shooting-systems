#ifndef __STM_H
#define __STM_H

#include "stdint.h"

// 声明函数
void Stm_SendFrame(void);      // 发送 LoRa 帧函数
void Stm_SetFlagCar(uint8_t flag);
void Stm_SendFrame1(void);

#endif // __STM_H
