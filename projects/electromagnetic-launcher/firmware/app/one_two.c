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


void one()
{
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


void two()
{
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

void one_back()
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

void two_back()
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

