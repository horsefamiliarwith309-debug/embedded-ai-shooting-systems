#ifndef __LORA_S_H
#define __LORA_S_H

#include "stdint.h"

// 全局变量声明
extern uint8_t flag_do_1;  // 存储接收到的数据
extern uint8_t flag_do_2;  // 存储接收到的数据
extern uint8_t flag_do_3;  // 存储接收到的数据

extern uint8_t Lora_DataBuf[4];

// 函数声明
void processLoraData(uint8_t res);  // 处理 LoRa 数据帧的函数

#endif
