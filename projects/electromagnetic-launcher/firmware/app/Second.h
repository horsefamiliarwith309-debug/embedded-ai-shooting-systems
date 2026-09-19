#ifndef SECOND_H
#define SECOND_H

#include <stdint.h>

extern uint8_t Position1;           // 开机时的角度
extern uint8_t KP1;
extern uint8_t KD1;
extern uint8_t Distence;//距离的位置
extern uint8_t FIR;//调整角度的系数
extern uint8_t Afa;//角度的位置
void Second();

#endif
