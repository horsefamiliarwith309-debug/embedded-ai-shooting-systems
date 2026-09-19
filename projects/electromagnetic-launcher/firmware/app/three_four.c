#include "tim.h"     
#include "usart.h" 
#include "motor.h"
#include "encode.h"
#include "gyro.h"
#include "gray.h"
#include "gray_control.h"
#include "eyes.h"
#include "turning.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

uint8_t flag1_1 = 0; 
uint8_t flag_car = 0;       //作为判断去的是3还是4的旗子
uint8_t flag_car_1 = 0;     //作为判断1车到达的旗子
uint8_t flag_car_2 = 0;     //作为判断1车回程时候到达路口的旗子

void threeORfour(uint8_t EyeValue)
{
    static int initialEncoderValue;  // 初始编码器值
    static int currentEncoderValue;  // 当前编码器值
    static int state = 0;            // 状态控制

    switch (state)
    {
        case 0:
            initialEncoderValue = encoderValueA;
            GreyCameraControl();
            state = 1;  // 进入下一个状态
            break;

        case 1:
            if (encoderValueA - initialEncoderValue < 6000) {
                GreyCameraControl();  // 使用巡线控制
            } else {
                GreyCameraControlSlow();  // 超过3000后为慢速度
            }
            if (encoderValueA - initialEncoderValue >= 7700) {
                if (EyeValue == 1) {
                    flag1_1 = 1;
                    turn_left(); // Eye_Value2 == 1 左转
                    flag_car = 1;
                }
                else if (EyeValue == 2) {
                    flag1_1 = 2;
                    turn_right(); // Eye_Value2 == 2 右转
                    flag_car = 2;
                }
                else {
                    GreyCameraControlSlow();
                }
                currentEncoderValue = encoderValueA;
                state = 2;  // 进入下一个状态
            }
            break;

        case 2:
            GreyCameraControl();
            if (encoderValueA - currentEncoderValue >= 1300) { 
                Set_Speed(0, 0); // 停止运动
                Set_Speed(1, 0);
                flag_car_1 = 1;
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


void three_backORfour_back()
{
    static int initialEncoderValue;  // 初始编码器值
    static int currentEncoderValue;  // 当前编码器值
    static int state = 0;            // 状态控制

    switch (state)
    {
        case 0:
            if(flag1_1 == 1) turn_around_r();  // 掉头
            else if(flag1_1 == 2) turn_around_l();  // 掉头
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
                if (flag1_1 == 1) {
                    turn_right_new();  // 去时左转，回来时右转
                    flag_car_2 = 1;
                }
                else if (flag1_1 == 2) {
                    turn_left_new();   // 去时右转，回来时左转
                    flag_car_2 = 1;
                }

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
            flag0_1 = 2;
            break;

        default:
            break;
    }
}

