#include "DT_Position.h"
#include "yc_datou_m0.h"

#define CMD_BUF_LEN 16
#define TARGET_LEN 8

static uint8_t rxCmd[CMD_BUF_LEN];
static uint8_t rxIndex = 0;
static uint8_t rxFrameFlag = 0;
static float current_position_deg = 0.0f;
static uint8_t new_data_ready = 0;
static uint8_t expected_id = 0;

// 发送读取电机位置命令
void DT_Position_Request(uint8_t id)
{
    expected_id = id;
    rxFrameFlag = 0;
    new_data_ready = 0;
    Emm_V5_Read_Sys_Params(id, S_CPOS); // 读取当前位置
}

// 每收到一个字节，在串口中断中调用此函数
void DT_Position_UART_RX_Callback(uint8_t byte)
{
    static uint8_t foundHeader = 0;

    if (!foundHeader) {
        // 等待帧头：地址 + 0x36
        if (rxIndex == 0 && byte == expected_id) {
            rxCmd[rxIndex++] = byte;
        } else if (rxIndex == 1 && byte == 0x36) {
            rxCmd[rxIndex++] = byte;
            foundHeader = 1; // 找到帧头，开始记录剩下的内容
        } else {
            rxIndex = 0; // 无效，重置
        }
    } else {
        // 收集后续数据
        if (rxIndex < CMD_BUF_LEN) {
            rxCmd[rxIndex++] = byte;

            if (rxIndex >= TARGET_LEN) {
                rxFrameFlag = 1;
                foundHeader = 0;  // 完成一帧，重置状态
            }
        } else {
            // 溢出保护
            rxIndex = 0;
            foundHeader = 0;
        }
    }
}

// 主循环中轮询判断是否接收到新数据帧
uint8_t DT_Position_Available(void)
{
    if (rxFrameFlag) {
        rxFrameFlag = 0;
        
        // 检查帧合法性
        if (rxCmd[0] == expected_id && rxCmd[1] == 0x36 && rxIndex == TARGET_LEN) {
            uint32_t pos = ((uint32_t)rxCmd[3] << 24) |
                           ((uint32_t)rxCmd[4] << 16) |
                           ((uint32_t)rxCmd[5] << 8)  |
                           ((uint32_t)rxCmd[6]);

            current_position_deg = (float)pos * 360.0f / 65536.0f;

            if (rxCmd[2]) current_position_deg = -current_position_deg;

            new_data_ready = 1;
        }

        rxIndex = 0; // 重置索引
    }

    return new_data_ready;
}

float DT_Position_GetAngle(void)
{
    new_data_ready = 0;
    return current_position_deg;
}
