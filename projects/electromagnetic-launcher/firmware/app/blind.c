#include "blind.h"
#include "tim.h"     
#include "usart.h" 
#include "motor.h"
#include "encode.h"
#include "gyro.h"
#include "gray.h"
#include "gray_control.h"
#include "turning.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "do_scream.h"
#include "one_tow.h"
#include "three_four.h"
#include "five.h"

uint8_t flag_blind = 0;

void blind_1() {
    
    static int initialEncoderValue;  // 初始
    static int currentEncoderValue;  // 当前
    static int state = 0;            // 状态控制

    switch (state)
    {
        case 0:
            initialEncoderValue = encoderValueA;
            state = 1; // 进入下一个状态
            break;

        case 1:
            GreyCameraControl();
            if (encoderValueA - initialEncoderValue >= 2800) {  
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                HAL_Delay(100);
                turn_left(); 
                currentEncoderValue = encoderValueA;
                state = 2;  // 进入下一个状态
            }
            break;

        case 2: 
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 1300) { 
                Set_Speed(0, 0); 
                Set_Speed(1, 0);
                state = 3;  // 完成所有步骤
            }
            break;

        case 3:  // 完成状态
            flag0_1 = 2;
            break;

        default:
            break;
    }
}

void blind_2() {
    static int initialEncoderValue;  // 初始
    static int currentEncoderValue;  // 当前
    static int state = 0;            // 状态控制

    switch (state)
    {
        case 0:
            initialEncoderValue = encoderValueA;
            state = 1;  // 进入下一个状态
            break;

        case 1:
            GreyCameraControl();
            if (encoderValueA - initialEncoderValue >= 2800) {  
                Set_Speed(0, 0);
                Set_Speed(1, 0); 
                HAL_Delay(100);
                turn_right();  // 右转
                currentEncoderValue = encoderValueA;
                state = 2;  // 进入下一个状态
            }
            break;

        case 2:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 1300) { 
                Set_Speed(0, 0); 
                Set_Speed(1, 0);
                state = 3;  // 完成所有步骤
            }
            break;

        case 3:  // 完成状态
            flag0_1 = 2;
            break;

        default:
            break;
    }
}

void blind_3() {
    static int initialEncoderValue;
    static int currentEncoderValue;
    static int state = 0;

    switch (state) {
        case 0:
            initialEncoderValue = encoderValueA;
            state = 1; 
            break;
        case 1:
            if (encoderValueA - initialEncoderValue < 6000) {
                GreyCameraControl();  
            } else {
                GreyCameraControlSlow();  
            }
            if (encoderValueA - initialEncoderValue >= 7700) {
                turn_left();
                currentEncoderValue = encoderValueA;
                state = 2; 
            }
            break;
        case 2:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 1300) {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state = 3; 
            }
            break;
        case 3:
            flag_blind = 0;
            break;
        default:
            break;
    }
}

void blind_4() {
    static int initialEncoderValue;
    static int currentEncoderValue;
    static int state = 0;

    switch (state) {
        case 0:
            initialEncoderValue = encoderValueA;
            state = 1; 
            break;
        case 1:
            if (encoderValueA - initialEncoderValue < 6000) {
                GreyCameraControl();  
            } else {
                GreyCameraControlSlow();  
            }
            if (encoderValueA - initialEncoderValue >= 7700) {
                turn_right();
                currentEncoderValue = encoderValueA;
                state = 2; 
            }
            break;
        case 2:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 1300) {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state = 3; 
            }
            break;
        case 3:
            flag_blind = 0;
            break;
        default:
            break;
    }
}

void blind_5() {
    static int initialEncoderValue;
    static int currentEncoderValue;
    static int state = 0;

    switch (state)
    {
        case 0:
            initialEncoderValue = encoderValueA;
            GreyCameraControl();
            state = 1;  // 进入下一个状态
            break;

        case 1:
            if (encoderValueA - initialEncoderValue < 10000) {
                GreyCameraControl();  // 使用巡线控制
            } else {
                GreyCameraControlSlow();  // 超过10000后为慢速度
            }
            if (encoderValueA - initialEncoderValue >= 11000) {
                turn_left_3();
                currentEncoderValue = encoderValueA;
                state = 2;  // 进入下一个状态
            }
            break;

        case 2:
            GreyCameraControlSlow();
            if (encoderValueA - currentEncoderValue >= 3000) {
                turn_left_new();
                currentEncoderValue = encoderValueA;
                state = 3;  // 进入下一个状态
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 1500) {
                Set_Speed(0, 0);  // 最终停止
                Set_Speed(1, 0);
                state = 4;  // 完成状态
            }
            break;

        case 4:  // 完成状态
            flag_blind = 0;  // 其他标志或逻辑操作
            break;

        default:
            break;
    }
}

void blind_7() {
    static int initialEncoderValue;
    static int currentEncoderValue;
    static int state = 0;

    switch (state)
    {
        case 0:
            initialEncoderValue = encoderValueA;
            GreyCameraControl();
            state = 1;  // 进入下一个状态
            break;

        case 1:
            if (encoderValueA - initialEncoderValue < 10000) {
                GreyCameraControl();  // 使用巡线控制
            } else {
                GreyCameraControlSlow();  // 超过10000后为慢速度
            }
            if (encoderValueA - initialEncoderValue >= 11000) {
                turn_left_3();
                currentEncoderValue = encoderValueA;
                state = 2;  // 进入下一个状态
            }
            break;

        case 2:
            GreyCameraControlSlow();
            if (encoderValueA - currentEncoderValue >= 3000) {
                turn_right();
                currentEncoderValue = encoderValueA;
                state = 3;  // 进入下一个状态
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 1500) {
                Set_Speed(0, 0);  // 最终停止
                Set_Speed(1, 0);
                state = 4;  // 完成状态
            }
            break;

        case 4:  // 完成状态
            flag_blind = 0;  // 其他标志或逻辑操作
            break;

        default:
            break;
    }
}

void blind_6() {
    static int initialEncoderValue;
    static int currentEncoderValue;
    static int state = 0;

    switch (state)
    {
        case 0:
            initialEncoderValue = encoderValueA;
            GreyCameraControl();
            state = 1;  // 进入下一个状态
            break;

        case 1:
            if (encoderValueA - initialEncoderValue < 10000) {
                GreyCameraControl();  // 使用巡线控制
            } else {
                GreyCameraControlSlow();  // 超过10000后为慢速度
            }
            if (encoderValueA - initialEncoderValue >= 11000) {
                turn_right_3();
                currentEncoderValue = encoderValueA;
                state = 2;  // 进入下一个状态
            }
            break;

        case 2:
            GreyCameraControlSlow();
            if (encoderValueA - currentEncoderValue >= 3000) {
                turn_left();
                currentEncoderValue = encoderValueA;
                state = 3;  // 进入下一个状态
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 1500) {
                Set_Speed(0, 0);  // 最终停止
                Set_Speed(1, 0);
                state = 4;  // 完成状态
            }
            break;

        case 4:  // 完成状态
            flag_blind = 0;  // 其他标志或逻辑操作
            break;

        default:
            break;
    }
}

void blind_8() {
static int initialEncoderValue;
    static int currentEncoderValue;
    static int state = 0;

    switch (state)
    {
        case 0:
            initialEncoderValue = encoderValueA;
            GreyCameraControl();
            state = 1;  // 进入下一个状态
            break;

        case 1:
            if (encoderValueA - initialEncoderValue < 10000) {
                GreyCameraControl();  // 使用巡线控制
            } else {
                GreyCameraControlSlow();  // 超过10000后为慢速度
            }
            if (encoderValueA - initialEncoderValue >= 11000) {
                turn_right_3();
                currentEncoderValue = encoderValueA;
                state = 2;  // 进入下一个状态
            }
            break;

        case 2:
            GreyCameraControlSlow();
            if (encoderValueA - currentEncoderValue >= 3000) {
                turn_right_new();
                currentEncoderValue = encoderValueA;
                state = 3;  // 进入下一个状态
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 1500) {
                Set_Speed(0, 0);  // 最终停止
                Set_Speed(1, 0);
                state = 4;  // 完成状态
            }
            break;

        case 4:  // 完成状态
            flag_blind = 0;  // 其他标志或逻辑操作
            break;

        default:
            break;
    }
}

void blind_1_back()
{
    static int initialEncoderValue;  // 初始
    static int currentEncoderValue;  // 当前
    static int state = 0;            // 状态控制

    switch (state)
    {
        case 0:
            turn_around_r();  // 掉头
            state = 1;
            break;

        case 1:
            initialEncoderValue = encoderValueA;
            GreyCameraControl();
            state = 2;
            break;

        case 2:
            GreyCameraControl();
            if (encoderValueA - initialEncoderValue >= 1300) {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                HAL_Delay(100);
                turn_right_new();  // 右转
                currentEncoderValue = encoderValueA;
                state = 3;
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 2800) {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                HAL_Delay(100);
                state = 4;  // 完成状态
            }
            break;

        case 4:  // 完成状态
            flag0_1 = 2;
            break;
        default:
            break;
    }
}

void blind_2_back()
{
    static int initialEncoderValue;  // 初始
    static int currentEncoderValue;  // 当前
    static int state = 0;            // 状态控制

    switch (state)
    {
        case 0:
            turn_around_l();  // 掉头
            state = 1;
            break;

        case 1:
            initialEncoderValue = encoderValueA;
            GreyCameraControl();
            state = 2;
            break;

        case 2:
            GreyCameraControl();
            if (encoderValueA - initialEncoderValue >= 1300) {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                HAL_Delay(100);
                turn_left();  // 左转
                currentEncoderValue = encoderValueA;
                state = 3;
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 2800) {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state = 4;  // 完成状态
            }
            break;

        case 4:  // 完成状态
            flag0_1 = 2;
            break;

        default:
            break;
    }
}

void blind_3_back()
{
    static int initialEncoderValue;  // 初始编码器值
    static int currentEncoderValue;  // 当前编码器值
    static int state = 0;            // 状态控制

    switch (state)
    {
        case 0:
            turn_around_r();  // 掉头
            state = 1;
            break;

        case 1:
            initialEncoderValue = encoderValueA;
            GreyCameraControl();
            state = 2;
            break;

        case 2:
            GreyCameraControl();
            if (encoderValueA - initialEncoderValue >= 1300) {
                Set_Speed(0, 0);  // 停止运动
                Set_Speed(1, 0);
                HAL_Delay(500);
                turn_right_new();  // 去时左转，回来时右转
                currentEncoderValue = encoderValueA;
                state = 3;
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 7700) {
                Set_Speed(0, 0); // 停止运动
                Set_Speed(1, 0);
                state = 4;  // 完成状态
            }
            break;

        case 4:  // 完成状态
            flag_blind = 0;
            break;

        default:
            break;
    }
}

void blind_4_back()
{
    static int initialEncoderValue;  // 初始编码器值
    static int currentEncoderValue;  // 当前编码器值
    static int state = 0;            // 状态控制

    switch (state)
    {
        case 0:
            turn_around_l();  // 掉头
            state = 1;
            break;

        case 1:
            initialEncoderValue = encoderValueA;
            GreyCameraControl();
            state = 2;
            break;

        case 2:
            GreyCameraControl();
            if (encoderValueA - initialEncoderValue >= 1300) {
                Set_Speed(0, 0);  // 停止运动
                Set_Speed(1, 0);
                HAL_Delay(500);
                turn_left_new();  // 去时右转，回来时左转
                currentEncoderValue = encoderValueA;
                state = 3;
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 7700) {
                Set_Speed(0, 0); // 停止运动
                Set_Speed(1, 0);
                state = 4;  // 完成状态
            }
            break;

        case 4:  // 完成状态
            flag_blind = 0;
            break;

        default:
            break;
    }
}

void blind_5_back()
{
    static int initialEncoderValue;
    static int currentEncoderValue;
    static int state = 0;

    switch (state)
    {
        case 0:
            turn_around_f();  // 掉头
            state = 1;
            break;

        case 1:
            initialEncoderValue = encoderValueA;
            GreyCameraControl();
            state = 2;
            break;

        case 2:
            GreyCameraControl();
            if (encoderValueA - initialEncoderValue >= 1500) {
                Set_Speed(0, 0);  // 停止运动
                Set_Speed(1, 0);  // 停止运动
                turn_right();
                currentEncoderValue = encoderValueA;
                state = 3;
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 3000) {
                turn_right_new(); 
                currentEncoderValue = encoderValueA;
                state = 4;
            }
            break;

        case 4:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 11000) {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state = 5;
            }
            break;

        case 5:
            flag_blind = 0;  // 标志位或其他逻辑操作
            break;

        default:
            break;
    }
}

void blind_7_back()
{
    static int initialEncoderValue;
    static int currentEncoderValue;
    static int state = 0;

    switch (state)
    {
        case 0:
            turn_around_b();  // 掉头
            state = 1;
            break;

        case 1:
            initialEncoderValue = encoderValueA;
            GreyCameraControl();
            state = 2;
            break;

        case 2:
            GreyCameraControl();
            if (encoderValueA - initialEncoderValue >= 1500) {
                Set_Speed(0, 0);  // 停止运动
                Set_Speed(1, 0);  // 停止运动

                // 根据 flag2_1 决定第一个转弯方向
                turn_left_news();
                currentEncoderValue = encoderValueA;
                state = 3;
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 3000) {
                turn_right_new();  // 第二次左转去，回来时右转
                currentEncoderValue = encoderValueA;
                state = 4;
            }
            break;

        case 4:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 11000) {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state = 5;
            }
            break;

        case 5:
            flag_blind = 0;  // 标志位或其他逻辑操作
            break;

        default:
            break;
    }
}

void blind_6_back()
{
    static int initialEncoderValue;
    static int currentEncoderValue;
    static int state = 0;

    switch (state)
    {
        case 0:
            turn_around_b();  // 掉头
            state = 1;
            break;

        case 1:
            initialEncoderValue = encoderValueA;
            GreyCameraControl();
            state = 2;
            break;

        case 2:
            GreyCameraControl();
            if (encoderValueA - initialEncoderValue >= 1500) {
                Set_Speed(0, 0);  // 停止运动
                Set_Speed(1, 0);  // 停止运动

                // 根据 flag2_1 决定第一个转弯方向
                turn_right_news();
                currentEncoderValue = encoderValueA;
                state = 3;
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 3000) {
                turn_left_new();   // 第二次右转去，回来时左转
                currentEncoderValue = encoderValueA;
                state = 4;
            }
            break;

        case 4:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 11000) {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state = 5;
            }
            break;

        case 5:
            flag_blind = 0;  // 标志位或其他逻辑操作
            break;

        default:
            break;
    }
}

void blind_8_back()
{
    static int initialEncoderValue;
    static int currentEncoderValue;
    static int state = 0;

    switch (state)
    {
        case 0:
            turn_around_f();  // 掉头
            state = 1;
            break;

        case 1:
            initialEncoderValue = encoderValueA;
            GreyCameraControl();
            state = 2;
            break;

        case 2:
            GreyCameraControl();
            if (encoderValueA - initialEncoderValue >= 1500) {
                Set_Speed(0, 0);  // 停止运动
                Set_Speed(1, 0);  // 停止运动

                // 根据 flag2_1 决定第一个转弯方向
                turn_left();
                currentEncoderValue = encoderValueA;
                state = 3;
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 3000) {
                turn_left_new();   // 第二次右转去，回来时左转
                currentEncoderValue = encoderValueA;
                state = 4;
            }
            break;

        case 4:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 11000) {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state = 5;
            }
            break;

        case 5:
            flag_blind = 0;  // 标志位或其他逻辑操作
            break;

        default:
            break;
    }
}