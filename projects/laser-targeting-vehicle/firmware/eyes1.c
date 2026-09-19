#include "eyes1.h"

// ------------------ 状态机状态定义 ------------------
#define EYES_STATE_WAIT_HEADER   0
#define EYES_STATE_READ_P1_X     1
#define EYES_STATE_READ_P1_Y     2
#define EYES_STATE_READ_P2_X     3
#define EYES_STATE_READ_P2_Y     4
#define EYES_STATE_READ_P3_X     5
#define EYES_STATE_READ_P3_Y     6
#define EYES_STATE_READ_P4_X     7
#define EYES_STATE_READ_P4_Y     8
#define EYES_STATE_READ_P5_X     9
#define EYES_STATE_READ_P5_Y     10
#define EYES_STATE_WAIT_TAIL     11

// ------------------ 全局变量 ------------------
volatile uint8_t eye_x[5] = {254,0,0,0,0};
volatile uint8_t eye_y[5] = {254,0,0,0,0};
volatile uint8_t eyes1_data_received = 0;

// ------------------ 内部状态变量 ------------------
static volatile uint8_t eyes_state = EYES_STATE_WAIT_HEADER;

// =====================================================================
// 函数名称：eyes1_process_data
// 功能描述：处理串口接收到的字节，解析55开头的多点数据帧
// 新数据帧格式：55 x1 y1 x2 y2 x3 y3 x4 y4 x5 y5 FF
// =====================================================================
void eyes1_process_data(uint8_t data)
{
    switch (eyes_state)
    {
        case EYES_STATE_WAIT_HEADER:
            if (data == 0x55) {
                eyes_state = EYES_STATE_READ_P1_X;
            }
            break;

        case EYES_STATE_READ_P1_X:
            eye_x[0] = data;
            eyes_state = EYES_STATE_READ_P1_Y;
            break;

        case EYES_STATE_READ_P1_Y:
            eye_y[0] = data;
            eyes_state = EYES_STATE_READ_P2_X;
            break;

        case EYES_STATE_READ_P2_X:
            eye_x[1] = data;
            eyes_state = EYES_STATE_READ_P2_Y;
            break;

        case EYES_STATE_READ_P2_Y:
            eye_y[1] = data;
            eyes_state = EYES_STATE_READ_P3_X;
            break;

        case EYES_STATE_READ_P3_X:
            eye_x[2] = data;
            eyes_state = EYES_STATE_READ_P3_Y;
            break;

        case EYES_STATE_READ_P3_Y:
            eye_y[2] = data;
            eyes_state = EYES_STATE_READ_P4_X;
            break;

        case EYES_STATE_READ_P4_X:
            eye_x[3] = data;
            eyes_state = EYES_STATE_READ_P4_Y;
            break;

        case EYES_STATE_READ_P4_Y:
            eye_y[3] = data;
            eyes_state = EYES_STATE_READ_P5_X;
            break;

        case EYES_STATE_READ_P5_X:
            eye_x[4] = data;
            eyes_state = EYES_STATE_READ_P5_Y;
            break;

        case EYES_STATE_READ_P5_Y:
            eye_y[4] = data;
            eyes_state = EYES_STATE_WAIT_TAIL;
            break;

        case EYES_STATE_WAIT_TAIL:
            if (data == 0xFF) {
                eyes1_data_received = 1;
            }
            // 无论帧尾是否正确都回到初始状态
            eyes_state = EYES_STATE_WAIT_HEADER;
            break;

        default:
            eyes_state = EYES_STATE_WAIT_HEADER;
            break;
    }
}