#include "eyes_uart.h"
#include "ti_msp_dl_config.h"  // 包含您的UART驱动头文件

void send_eyes1_buf(uint8_t mode)
{
    // 根据模式选择要发送的数据
    uint8_t data[3];
    
    data[0] = 0x55;  // 起始字节
    
    if(mode == 1) {
        data[1] = 0x01;  // 绿点识别模式
    } else if(mode == 2) {
        data[1] = 0x02;  // 矩形识别模式
    } else {
        // 无效模式，不发送
        return;
    }
    
    data[2] = 0xFF;  // 结束字节
    
    // 发送数据
    for(uint8_t i = 0; i < 3; i++) {
        while(DL_UART_isBusy(UART_1_INST));  // 等待UART空闲
        DL_UART_Main_transmitData(UART_1_INST, data[i]);
    }
}