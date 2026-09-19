#include "luna.h"
#include "gyro.h"
#include <stdbool.h>

// 全局变量定义
volatile uint16_t Luna_Distance = 0;     // 距离值 (cm)
volatile bool Luna_DataValid = false;    // 数据是否有效标志
volatile uint16_t Luna_Amplitude = 0;    // 信号强度值

// 模块内部状态变量
static LunaState sLunaState = LUNA_WAIT_HEADER1;
static uint8_t sDataCnt = 0;             // 数据接收计数器
static uint8_t sDataBuf[7];              // 数据缓冲区 (Dist_L, Dist_H, Amp_L, Amp_H, Temp_L, Temp_H, Check_sum)

// 初始化函数
void Luna_Init(void) {
    sLunaState = LUNA_WAIT_HEADER1;
    sDataCnt = 0;
    Luna_Distance = 0;
    Luna_DataValid = false;
    Luna_Amplitude = 0;
}

// 数据处理函数
void Luna_ProcessData(uint8_t res) {
    switch (sLunaState) {
        case LUNA_WAIT_HEADER1:
            if (res == 0x59) {
                sLunaState = LUNA_WAIT_HEADER2;
            }
            break;
            
        case LUNA_WAIT_HEADER2:
            if (res == 0x59) {
                sLunaState = LUNA_RECEIVING_DATA;
                sDataCnt = 0;
            } else {
                // 如果不是第二个0x59，重置状态机
                sLunaState = LUNA_WAIT_HEADER1;
            }
            break;
            
        case LUNA_RECEIVING_DATA:
            // 存储数据到缓冲区
            sDataBuf[sDataCnt++] = res;
            
            // 检查是否接收完所有数据字节
            if (sDataCnt >= 7) {
                // 计算校验和
                uint8_t checksum = 0;
                checksum += 0x59;  // 第一个头字节
                checksum += 0x59;  // 第二个头字节
                
                // 计算数据部分校验和
                for (int i = 0; i < 6; i++) {
                    checksum += sDataBuf[i];
                }
                
                // 验证校验和
                if (checksum == sDataBuf[6]) {
                    // 解析距离
                    Luna_Distance = (sDataBuf[1] << 8) | sDataBuf[0];
                    
                    // 解析信号强度
                    Luna_Amplitude = (sDataBuf[3] << 8) | sDataBuf[2];
                    
                    // 检查信号强度是否有效
                    // 条件：信号强度 >= 100 且不是过曝值 (65535)
                    if (Luna_Amplitude >= 100 && Luna_Amplitude != 65535) {
                        Luna_DataValid = true;
                    } else {
                        Luna_DataValid = false;
                    }
                } else {
                    // 校验和失败，数据无效
                    Luna_DataValid = false;
                }
                
                // 重置状态机
                sLunaState = LUNA_WAIT_HEADER1;
            }
            break;
    }
}