#include "eyes.h"

// 模块内部使用的全局变量
volatile EyesState eyes_state = EYES_STATE_WAIT_HEADER;  // 初始状态为等待帧头
volatile uint8_t eyes_data_buf[2] = {0};                 // 数据接收缓冲区
volatile uint8_t eyes_data_cnt = 0;                      // 数据接收计数器
volatile bool eyes_data_received = false;                // 数据接收完成标志

// 外部可访问的全局变量
volatile uint16_t eyes_status_value = 0;                 // 解析后的16位状态值
volatile uint8_t eyes_column_status[NUM_COLUMNS] = {0};  // 每个列的状态 (初始为0)

// =====================================================================
// 函数名称：eyes_init
// 功能描述：初始化EYES模块
// =====================================================================
void eyes_init(void) {
    eyes_state = EYES_STATE_WAIT_HEADER;
    eyes_data_cnt = 0;
    eyes_data_received = false;
    eyes_status_value = 0;
    
    // 初始化所有列状态为0
    for (int i = 0; i < NUM_COLUMNS; i++) {
        eyes_column_status[i] = 0;
    }
}

// =====================================================================
// 函数名称：eyes_process_data
// 功能描述：处理接收到的EYES数据（状态机实现）
// =====================================================================
void eyes_process_data(uint8_t byte) {
    switch (eyes_state) {
        case EYES_STATE_WAIT_HEADER:
            // 等待帧头0x55
            if (byte == 0x55) {
                eyes_state = EYES_STATE_RECV_LOW_BYTE;
                eyes_data_cnt = 0;
            }
            break;
            
        case EYES_STATE_RECV_LOW_BYTE:
            // 接收低字节数据
            eyes_data_buf[0] = byte;
            eyes_state = EYES_STATE_RECV_HIGH_BYTE;
            break;
            
        case EYES_STATE_RECV_HIGH_BYTE:
            // 接收高字节数据
            eyes_data_buf[1] = byte;
            eyes_state = EYES_STATE_WAIT_FOOTER;
            break;
            
        case EYES_STATE_WAIT_FOOTER:
            // 等待帧尾0xFF
            if (byte == 0xFF) {
                // 组合16位状态值 (小端序: 低字节在前，高字节在后)
                eyes_status_value = (eyes_data_buf[1] << 8) | eyes_data_buf[0];
                
                // 更新所有列的状态变量
                eyes_update_column_status();
                
                eyes_data_received = true;
            }
            // 无论是否收到正确帧尾，都回到初始状态
            eyes_state = EYES_STATE_WAIT_HEADER;
            break;
            
        default:
            // 未知状态，重置状态机
            eyes_state = EYES_STATE_WAIT_HEADER;
            break;
    }
}

// =====================================================================
// 函数名称：eyes_update_column_status
// 功能描述：更新所有列的状态变量
// =====================================================================
void eyes_update_column_status(void) {
    // 将16位状态值解析为16个独立的状态变量
    for (int i = 0; i < NUM_COLUMNS; i++) {
        // 从状态值中提取第i位的值 (0或1)
        eyes_column_status[i] = (eyes_status_value >> i) & 0x01;
    }
}