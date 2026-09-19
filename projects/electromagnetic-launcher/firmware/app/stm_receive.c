#include "stm_receive.h"

// 接收状态机状态定义
typedef enum {
    WAIT_HEADER,        // 等待帧头0x55
    RECEIVE_HIGH_BYTE,   // 接收高字节
    RECEIVE_LOW_BYTE,    // 接收低字节
    WAIT_TAIL           // 等待帧尾0xFF
} ReceiveState;

// 定义接收状态变量
static ReceiveState receiveState = WAIT_HEADER;

// 定义接收缓冲区
static uint8_t highByte = 0;
static uint8_t lowByte = 0;

// 全局变量定义
uint16_t received_position = 0;  // 接收到的原始位置值
float actual_position = 0.0f;     // 转换后的实际位置值

// 接收数据处理函数
void Stm_Receive_Process(uint8_t res)
{
    switch (receiveState)
    {
        case WAIT_HEADER:  // 状态0: 等待帧头
            if (res == 0x55) {
                receiveState = RECEIVE_HIGH_BYTE;  // 收到帧头，进入高字节接收状态
            }
            break;
            
        case RECEIVE_HIGH_BYTE:  // 状态1: 接收高字节
            highByte = res;       // 保存高字节
            receiveState = RECEIVE_LOW_BYTE;  // 进入低字节接收状态
            break;
            
        case RECEIVE_LOW_BYTE:   // 状态2: 接收低字节
            lowByte = res;        // 保存低字节
            receiveState = WAIT_TAIL;  // 进入等待帧尾状态
            break;
            
        case WAIT_TAIL:          // 状态3: 等待帧尾
            if (res == 0xFF) {
                // 帧尾正确，合并高低字节
                received_position = (uint16_t)((highByte << 8) | lowByte);
                
                // 转换为实际位置值：
                // 1. 除以100得到10.0-70.0之间的值
                // 2. 减去40得到-30.0到30.0之间的原始值
                actual_position = (received_position / 100.0f) - 40.0f;
            }
            // 无论帧尾是否正确，都回到初始状态等待下一帧
            receiveState = WAIT_HEADER;
            break;
            
        default:
            // 异常状态，重置状态机
            receiveState = WAIT_HEADER;
            break;
    }
}