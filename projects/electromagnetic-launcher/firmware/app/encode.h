#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>

// 全局变量声明
extern int32_t encoderValueA;      // 编码器A当前值
extern int32_t encoderValueB;      // 编码器B当前值
extern int32_t encoderChangeA;     // 编码器A变化值
extern int32_t encoderChangeB;     // 编码器B变化值
extern int32_t lastValueA;         // 编码器A上一个值
extern int32_t lastValueB;         // 编码器B上一个值

// 函数声明
int16_t EncoderA_Get(void);           // 获取编码器A的值
int16_t EncoderB_Get(void);           // 获取编码器B的值
void send_to_tjc_screen(int32_t value, int index);  // 发送数据到淘晶驰屏
void send_to_tjc_screen_float(float value, int index);  // 发送浮点数到淘晶驰屏
void read_encode(void);                // 读取编码器值并发送数据

#endif // ENCODER_H
