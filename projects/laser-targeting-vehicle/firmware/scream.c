#include "scream.h"

// 协议状态定义
typedef enum {
    STATE_WAIT_START,      // 等待起始字节55
    STATE_RECV_DATA,       // 接收两个数据字节
    STATE_WAIT_END,        // 等待结束字节FF
    STATE_COMPLETE         // 数据包接收完成
} ProtocolState;

// 内部全局变量
volatile uint8_t SCREAM_DataBuf[SCREAM_DATA_BUF_SIZE];    // 数据接收缓冲区
volatile uint8_t SCREAM_DataCnt = 0;                      // 数据计数
volatile ProtocolState SCREAM_STA = STATE_WAIT_START;     // 状态机状态

// 外部可访问变量
volatile bool SCREAM_DataReceived = false;  // 接收完成标志
uint8_t command_1 = 0;                        // 数据1
uint8_t command_2 = 0;                      // 数据2

// =====================================================================
// 串口接收处理函数
// 数据格式：55 数据1 数据2 FF
// =====================================================================
void processSCREAMData(uint8_t res) {
    switch (SCREAM_STA) {
        // 等待起始字节 55
        case STATE_WAIT_START:
            if (res == 0x55) {
                SCREAM_DataCnt = 0;
                SCREAM_STA = STATE_RECV_DATA;
            }
            break;

        // 接收数据字节（2个）
        case STATE_RECV_DATA:
            if (SCREAM_DataCnt < SCREAM_DATA_BUF_SIZE) {
                SCREAM_DataBuf[SCREAM_DataCnt++] = res;
                if (SCREAM_DataCnt >= SCREAM_DATA_BUF_SIZE) {
                    SCREAM_STA = STATE_WAIT_END;
                }
            } else {
                // 超出预期数据字节，重置
                SCREAM_STA = STATE_WAIT_START;
            }
            break;

        // 等待结束字节 FF
        case STATE_WAIT_END:
            if (res == 0xFF) {
                SCREAM_STA = STATE_COMPLETE;
            } else {
                // 错误的结束字节，重置
                SCREAM_STA = STATE_WAIT_START;
            }
            break;

        default:
            break;
    }

    // 接收完成处理
    if (SCREAM_STA == STATE_COMPLETE) {
        command_1   = SCREAM_DataBuf[0];
        command_2 = SCREAM_DataBuf[1];

        SCREAM_DataReceived = true;

        // 重置状态机
        SCREAM_STA = STATE_WAIT_START;
        SCREAM_DataCnt = 0;
    }
}