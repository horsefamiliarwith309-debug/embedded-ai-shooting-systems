#include "five.h"
#include "motor.h"
#include "encode.h"
#include "gyro.h"
#include "gray.h"
#include "gray_control.h"
#include "tim.h"
#include "usart.h"
#include "turning.h"
#include "do_scream.h"
#include "three_four.h"

uint8_t flag2_1 = 0;

void fiveORsixORsevenOREight(uint8_t EyeValue)
{
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
            if (encoderValueA - initialEncoderValue < 8300) {
                GreyCameraControl();  // 使用巡线控制
            } else {
                GreyCameraControlSlow();  // 超过10000后为慢速度
            }
            //encoderValueA - initialEncoderValue >= 10800
            if (encoderValueA - initialEncoderValue >= 10800) {
                GreyCameraControlSlow();
                HAL_Delay(10);
                if (EyeValue == 1) {
                    flag2_1 = 1;
                    turn_left_3();
                }
                else if (EyeValue == 2) {
                    flag2_1 = 2;
                    turn_right_3();
                }
                else {
                    GreyCameraControlSlow();
                }
                currentEncoderValue = encoderValueA;
                state = 2;  // 进入下一个状态
            }
            break;

        case 2:
            GreyCameraControlSlow();
            if (encoderValueA - currentEncoderValue >= 3200) {
                if (EyeValue == 1) {
                    if (flag2_1 == 1) {
                        turn_left_new();
                        flag2_1 = 3;  // 左转 左转时
                        flag_car = 3;
                    }
                    else if (flag2_1 == 2) {
                        turn_left();
                        flag2_1 = 5;  // 右转 左转时
                        flag_car = 5;
                    }
                    else {
                    GreyCameraControlSlow();
                    }
                }
                else if (EyeValue == 2) {
                    if (flag2_1 == 1) {
                        turn_right();
                        flag2_1 = 4;  // 左转 右转时
                        flag_car = 4;
                    }
                    else if (flag2_1 == 2) {
                        turn_right_new();
                        flag2_1 = 6;  // 右转 右转时
                        flag_car = 6;
                    }
                    else {
                    GreyCameraControlSlow();
                    }
                }
                currentEncoderValue = encoderValueA;
                state = 3;  // 进入下一个状态
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 1400) {
                Set_Speed(0, 0);  // 最终停止
                Set_Speed(1, 0);
                state = 4;  // 完成状态
            }
            break;

        case 4:  // 完成状态
            flag0_1 = 2;  // 其他标志或逻辑操作
            break;

        default:
            break;
    }
}

void five_backORsix_backORseven_backOREight_back()
{
    static int initialEncoderValue;
    static int currentEncoderValue;
    static int state = 0;

    switch (state)
    {
        case 0:
            if(flag2_1 == 3)       turn_around_f();  // 掉头
            else if(flag2_1 == 4)  turn_around_b();  // 掉头
            else if(flag2_1 == 5)  turn_around_b();  // 掉头
            else if(flag2_1 == 6)  turn_around_f();  // 掉头
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
                if (flag2_1 == 3)  turn_right();
                else if (flag2_1 == 5)  turn_right_news();
                else if (flag2_1 == 4)  turn_left_news();
                else if (flag2_1 == 6)  turn_left();
                currentEncoderValue = encoderValueA;
                state = 3;
            }
            break;

        case 3:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 3300) {
                GreyCameraControl();
                HAL_Delay(10);
                // 根据 flag2_1 决定第二个转弯方向
                if (flag2_1 == 3 || flag2_1 == 4) {
                    turn_right_new();  // 第二次左转去，回来时右转
                }
                else if (flag2_1 == 5 || flag2_1 == 6) {
                    turn_left_new();   // 第二次右转去，回来时左转
                }

                currentEncoderValue = encoderValueA;
                state = 4;
            }
            break;

        case 4:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 10800) {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state = 5;
            }
            break;

        case 5:
            flag0_1 = 2;  // 标志位或其他逻辑操作
            break;

        default:
            break;
    }
}

