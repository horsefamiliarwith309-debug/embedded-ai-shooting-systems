#ifndef EYES_UART_H
#define EYES_UART_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 发送眼睛控制指令
 * 
 * @param mode 控制模式：
 *             1 - 切换到绿点识别模式 (发送55 01 FF)
 *             2 - 切换到矩形识别模式 (发送55 02 FF)
 */
void send_eyes1_buf(uint8_t mode);

#ifdef __cplusplus
}
#endif

#endif // EYES1_UART_H