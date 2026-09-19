#include "maix.h"

// 数据缓冲区和坐标变量
uint8_t Maix_DataBuf[4];  // 存储接收到的坐标数据
uint16_t xxx = 0;         // X坐标值
uint16_t yyy = 0;         // Y坐标值

/**
 * 处理Maix模块数据的状态机
 * 格式: | 0x55 | X_LSB | X_MSB | Y_LSB | Y_MSB | 0xFF |
 */
 
void processMaixData(uint8_t res)
{
    static uint8_t state = 0;     // 状态机状态
    static uint8_t dataCnt = 0;   // 数据计数器
    uint8_t errFlag = 0;          // 错误标志

    switch (state)
    {
        case 0:  // 等待起始标志0x55
            if (res == 0x55) {
                state = 1;        // 进入数据接收状态
                dataCnt = 0;      // 重置数据计数器
            } else {
                errFlag = 1;      // 帧头不匹配
            }
            break;

        case 1:  // 接收X和Y坐标数据
            if (dataCnt < 4) {    // 接收4个数据字节 (X_LSB, X_MSB, Y_LSB, Y_MSB)
                Maix_DataBuf[dataCnt++] = res;
            }

            if (dataCnt >= 4) {   // 数据接收完毕，等待结束标志
                state = 2;
            }
            break;

        case 2:  // 等待结束标志0xFF
            if (res == 0xFF) {
                // 成功接收到完整帧，解析坐标
                state = 0;
                
                // 组合X坐标 (MSB在前，LSB在后)
                xxx = (Maix_DataBuf[1] << 8) | Maix_DataBuf[0];
                
                // 组合Y坐标
                yyy = (Maix_DataBuf[3] << 8) | Maix_DataBuf[2];
            } 
            else {
                errFlag = 1;      // 帧尾不匹配
            }
            break;

        default:
            errFlag = 1;          // 无效状态
            break;
    }

    if (errFlag) {
        // 发生错误，重置状态机
        state = 0;
        dataCnt = 0;
    }
}    