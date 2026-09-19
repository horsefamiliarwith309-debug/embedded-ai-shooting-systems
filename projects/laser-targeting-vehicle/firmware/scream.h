#ifndef __SCREAM_H
#define __SCREAM_H

#include <stdint.h>
#include <stdbool.h>

// ================= 配置宏 =================
#define SCREAM_DATA_BUF_SIZE   2   // 55 + 数据1 + 数据2 + FF

// ================= 外部变量声明 =================
extern volatile bool SCREAM_DataReceived;   // 接收完成标志
extern uint8_t command_1;                     // 任务
extern uint8_t command_2;                   // 圈数

// ================= 函数声明 =================
void processSCREAMData(uint8_t res);

#endif