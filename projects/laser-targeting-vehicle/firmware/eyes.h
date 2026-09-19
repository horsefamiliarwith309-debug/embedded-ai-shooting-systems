#include <stdint.h>
#include <stdbool.h>
#include "ti_msp_dl_config.h"

// 常量定义
#define EYES_DATA_BUF_SIZE 3  // 数据缓冲区大小 (0x55 + 2字节数据 + 0xFF)
#define NUM_COLUMNS 16        // 列的数量

// 模块状态枚举
typedef enum {
    EYES_STATE_WAIT_HEADER,
    EYES_STATE_RECV_LOW_BYTE,
    EYES_STATE_RECV_HIGH_BYTE,
    EYES_STATE_WAIT_FOOTER
} EyesState;

// 模块内部使用的全局变量
extern volatile EyesState eyes_state;          // 数据接收状态机状态
extern volatile uint8_t eyes_data_buf[2];      // 数据接收缓冲区 (低字节 + 高字节)
extern volatile uint8_t eyes_data_cnt;         // 数据接收计数器
extern volatile bool eyes_data_received;       // 数据接收完成标志

// 外部可访问的全局变量
extern volatile uint16_t eyes_status_value;    // 解析后的16位状态值
extern volatile uint8_t eyes_column_status[NUM_COLUMNS]; // 每个列的状态 (0或1)

void eyes_init(void);
void eyes_process_data(uint8_t byte);
void eyes_update_column_status(void);