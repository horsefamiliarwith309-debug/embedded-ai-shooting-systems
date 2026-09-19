#include "stm32f4xx_hal.h"
#include "gyro.h"
#include "motor.h"
#include "turning.h"
#include "encode.h"
#include <math.h>
#include "second.h"
#include "stm.h"
#include "electric.h"
#include "Third.h"

uint8_t first_flag=0;
uint8_t tempp=0;
    
void First()
{
    if(!tempp)
    {
        KP1=20;
        KD1=1;
        KP2=KP1;
        KD2=KD1;
        Position1=0+50;
        Position2=0+50;
        tempp=1;
        //发送数据，等待转动
        Stm_SendFrame();
        HAL_Delay(500);
    }
    if(Receive==0 && first_flag==0)
    {
        Electric_On;
        HAL_Delay(1000);//延时
        Electric_Off;//关闭蜂鸣器
        Electric1_Off;
        HAL_Delay(1000);//延时
        first_flag=1;
    }
        
}


//void First()
//{
//    if(!tempp)
//    {
//        KP1=20;
//        KD1=1;
//        KP2=KP1;
//        KD2=KD1;
//        Position1=0+50;
//        Position2=0+50;
//        tempp=1;
//        //发送数据，等待转动
//        Stm_SendFrame();
//        HAL_Delay(500);
//    }
//    if(first_flag==1)
//    {
//        KP1=5;
//        KD1=1;
//        KP2=KP1;
//        KD2=KD1;
//        Position2=30+50;
//        //发送数据，等待转动
//        Stm_SendFrame();
//        HAL_Delay(2000);
//        first_flag=0;
//    }
//    else if(first_flag==0)
//    {
//        KP1=5;
//        KD1=1;
//        KP2=KP1;
//        KD2=KD1;
//        Position2=-30+50;
//        //发送数据，等待转动
//        Stm_SendFrame();
//        HAL_Delay(2000);
//        first_flag=1;
//    }
//    
//        
//}