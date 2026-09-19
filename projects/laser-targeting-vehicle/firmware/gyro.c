#include "gyro.h"

// ================== 内部状态变量 ==================

// 状态机
static volatile uint8_t gyro_rate_state = GYRO_STATE_WAIT_HEADER;
static volatile uint8_t gyro_angle_state = GYRO_STATE_WAIT_HEADER;

// 缓冲区
static volatile uint8_t gyro_rate_buf[6] = {0};
static volatile uint8_t gyro_angle_buf[6] = {0};

// 计数
static volatile uint8_t gyro_rate_cnt = 0;
static volatile uint8_t gyro_angle_cnt = 0;

// 初始角度
volatile float InitialYaw = 0.0f;

volatile float RelativeYaw = 0.0f;

// ================== 外部变量定义 ==================

volatile float gyro_wx = 0.0f;
volatile float gyro_wy = 0.0f;
volatile float gyro_wz = 0.0f;

volatile float gyro_roll = 0.0f;
volatile float gyro_pitch = 0.0f;
volatile float Gyro_Yaw = 0.0f;

volatile float gyro_relative_yaw = 0.0f;

volatile uint8_t gyro_data_received = 0;

// ================== 工具函数 ==================

static inline float float_abs(float value)
{
    return value < 0 ? -value : value;
}

/**
 * @brief 计算偏航误差 (目标角度与当前角度差)
 */
float yaw_error(float target, float now)
{
    float error;
    float temp = target;
    target = now;
    now = temp;

    if (target > 0)
    {
        if (now <= 0)
        {
            if (float_abs(now) < (180 - target))
                error = float_abs(now) + target;
            else
                error = -(180 - target) - (180 - float_abs(now));
        }
        else
        {
            error = target - now;
        }
    }
    else if (target < 0)
    {
        if (now > 0)
        {
            if (now > target + 180)
                error = (180 - now) + (180 - float_abs(target));
            else
                error = -(float_abs(target) + now);
        }
        else
        {
            error = -(float_abs(target) - float_abs(now));
        }
    }
    else
    {
        error = 0;
    }

    return error;
}

// ================== 数据解析函数 ==================

/**
 * @brief 解析角速度数据帧
 */
static void parse_rate_data(void)
{
    int16_t Wx = (int16_t)((gyro_rate_buf[1] << 8) | gyro_rate_buf[0]);
    int16_t Wy = (int16_t)((gyro_rate_buf[3] << 8) | gyro_rate_buf[2]);
    int16_t Wz = (int16_t)((gyro_rate_buf[5] << 8) | gyro_rate_buf[4]);

    gyro_wx = Wx / 32768.0f * 2000.0f;
    gyro_wy = Wy / 32768.0f * 2000.0f;
    gyro_wz = Wz / 32768.0f * 2000.0f;
}

/**
 * @brief 解析角度数据帧
 */
static void parse_angle_data(void)
{
    int16_t Roll  = (int16_t)((gyro_angle_buf[1] << 8) | gyro_angle_buf[0]);
    int16_t Pitch = (int16_t)((gyro_angle_buf[3] << 8) | gyro_angle_buf[2]);
    int16_t Yaw   = (int16_t)((gyro_angle_buf[5] << 8) | gyro_angle_buf[4]);

    gyro_roll  = Roll / 32768.0f * 180.0f;
    gyro_pitch = Pitch / 32768.0f * 180.0f;
    Gyro_Yaw   = Yaw / 32768.0f * 180.0f;

    // 初始化开机角度
    if (InitialYaw == 0.0f)
        InitialYaw = Gyro_Yaw;

}

// ================== 接口函数实现 ==================
/**
 * @brief 处理接收到的一个字节数据
 */
void gyro_process_data(uint8_t data)
{
    // ---- 角速度帧解析 ----
    switch (gyro_rate_state)
    {
        case GYRO_STATE_WAIT_HEADER:
            if (data == GYRO_HEADER)
                gyro_rate_state = GYRO_STATE_READ_DATA;
            break;

        case GYRO_STATE_READ_DATA:
            if (data == GYRO_FRAME_RATE)
            {
                gyro_rate_state = GYRO_STATE_WAIT_TAIL;
                gyro_rate_cnt = 0;
            }
            else
                gyro_rate_state = GYRO_STATE_WAIT_HEADER;
            break;

        case GYRO_STATE_WAIT_TAIL:
            gyro_rate_buf[gyro_rate_cnt++] = data;
            if (gyro_rate_cnt >= 6)
            {
                parse_rate_data();
                gyro_rate_state = GYRO_STATE_WAIT_HEADER;
            }
            break;
    }

    // ---- 角度帧解析 ----
    switch (gyro_angle_state)
    {
        case GYRO_STATE_WAIT_HEADER:
            if (data == GYRO_HEADER)
                gyro_angle_state = GYRO_STATE_READ_DATA;
            break;

        case GYRO_STATE_READ_DATA:
            if (data == GYRO_FRAME_ANGLE)
            {
                gyro_angle_state = GYRO_STATE_WAIT_TAIL;
                gyro_angle_cnt = 0;
            }
            else
                gyro_angle_state = GYRO_STATE_WAIT_HEADER;
            break;

        case GYRO_STATE_WAIT_TAIL:
            gyro_angle_buf[gyro_angle_cnt++] = data;
            if (gyro_angle_cnt >= 6)
            {
                parse_angle_data();
                gyro_angle_state = GYRO_STATE_WAIT_HEADER;
                gyro_data_received = 1; // 标记有新角度数据
            }
            break;
    }
}
