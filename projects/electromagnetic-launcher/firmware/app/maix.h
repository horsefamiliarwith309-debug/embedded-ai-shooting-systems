#ifndef __MAIX_H__
#define __MAIX_H__

#include <stdint.h>

// 坐标数据
extern uint16_t xxx;  // X坐标值
extern uint16_t yyy;  // Y坐标值

/**
 * 处理接收到的Maix模块数据
 * @param res 接收到的单个字节数据
 */
void processMaixData(uint8_t res);

#endif // __MAIX_H__    