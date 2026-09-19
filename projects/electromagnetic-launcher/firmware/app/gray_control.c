#include "gray_control.h"
#include "tim.h"       // 包含自定义定时器配置
#include "global_time.h"
#include "gray.h"      
#include "gpio.h"
#include "motor.h"
#include "encode.h"

// 全局变量用于 PID 控制
volatile float error = 0;
volatile float errs = 0;
volatile float ALLthemods = 0;


void GreyCameraControl(void)  // 灰度巡线控制
{
    Gray_read();  // 调用 gray_read 函数读取传感器数据

    // 根据传感器数据计算 error
    if (gray_1 == 0)
    {
        error = -4;  // -2
    }
    else if (gray_2 == 0)
    {
        error = -2;  // -1.5
    }
    else if (gray_3 == 0)
    {
        error = -1.5;  // -1
    }
    else if (gray_4 == 0)
    {
        error = 0.5;  // -0.5
    }
    else if (gray_8 == 0)
    {
        error = 4;
    }
    else if (gray_7 == 0)
    {
        error = 2;
    }
    else if (gray_6 == 0)
    {
        error = 1.5;
    }
    else if (gray_5 == 0)
    {
        error = 0.5;
    }
    else
    {
        error = 0;  // 如果没有传感器触发，误差设为0
    }

    // PID 积分项累积
    errs += error;
    if (errs > 50) errs = 50;
    if (errs < -50) errs = -50;

    // 计算输出修正值
    ALLthemods = error * P + errs * I;

    // 调整左右电机速度
    Set_Speed(0, 40 - ALLthemods / 2);  // 左轮
    Set_Speed(1, 40 + ALLthemods / 2);  // 右轮
}

void GreyCameraControlSlow(void)  // 灰度巡线控制（慢速）
{
    Gray_read();  // 调用 gray_read 函数读取传感器数据

    // 根据传感器数据计算 error
    if (gray_1 == 0)
    {
        error = -5;
    }
    else if (gray_2 == 0)
    {
        error = -3;
    }
    else if (gray_3 == 0)
    {
        error = -2;
    }
    else if (gray_4 == 0)
    {
        error = 0.5;
    }
    else if (gray_8 == 0)
    {
        error = 5;
    }
    else if (gray_7 == 0)
    {
        error = 3;
    }
    else if (gray_6 == 0)
    {
        error = 2;
    }
    else if (gray_5 == 0)
    {
        error = 0.5;
    }
    else
    {
        error = 0;  // 如果没有传感器触发，误差设为0
    }

    // PID 积分项累积
    errs += error;
    if (errs > 50) errs = 50;
    if (errs < -50) errs = -50;

    // 计算输出修正值
    ALLthemods = error * P + errs * I;

    // 调整左右电机速度（慢速）
    Set_Speed(0, 26 - ALLthemods / 2);  // 左轮，速度减慢
    Set_Speed(1, 26 + ALLthemods / 2);  // 右轮，速度减慢
}
