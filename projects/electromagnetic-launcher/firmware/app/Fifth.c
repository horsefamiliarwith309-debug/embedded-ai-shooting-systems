#include "stm32f4xx_hal.h"
#include "motor.h"
#include <math.h>
#include "stm.h"
#include "electric.h"
#include "Second.h"
#include "Third.h"
#include "luna.h"
#include "stm_receive.h"
#include "maix.h"

uint8_t state_fif=1;
uint8_t sum2=1;
uint8_t FIR2=1;//抬升角度
uint8_t Flag=1;
uint8_t Flag_1=1;
uint8_t V1=0;
uint8_t V2=0;
uint8_t sum_fif=1;

uint8_t Torque2=0;
//void Fifth()
//{
//    switch(state_fif)
//    {
//        case 1:
//            if(Flag_1)
//        {
//            Flag_1=0;
//            KP1=20;
//            KD1=1;
//            Position1=3+50;
//            KD2=0;
//            KP2=0;
//            Position2=0+50;
//            Torque2=10+10;
//            Stm_SendFrame();
//            HAL_Delay(100);
//            Torque2=5+10;
//            Stm_SendFrame();
//        }
//        
//            if(actual_position<=-30 && Flag)
//        {
//            KD2=0;
//            KP2=0;
//            Position2=0+50;
//            Torque2=5+10;
//            Stm_SendFrame();
//        }
//            if(actual_position>=30 && Flag)
//        {
//            KD2=0;
//            KP2=0;
//            Position2=0+50;
//            Torque2=-5+10;
//            Stm_SendFrame();
//        }
//        
//            if(xxx>230 && xxx<250 && Flag && Receive==0)
//        {
//            
//            Flag=0;
//            Electric_On;
//            HAL_Delay(1000);//延时
//            Electric_Off;//关闭蜂鸣器
//            Electric1_Off;
//            HAL_Delay(1000);//延时
//            state_fif=2;

//        }
//            break;
//        
//        case 2:
//            KP1=20;
//            KD1=1;
//            Position1=0+50;
//            Torque2=0+10;
//            state_fif=0;
//            Stm_SendFrame();
//            HAL_Delay(1000);//延时
//            break;
//    }
//    

//}


void Fifth()
{
    switch(state_fif)
    {
        case 1:
            KP1=10;
            KD1=1;
            Position1=20+50;
            KP2=10;
            KD2=1;
            Position2=0+50;
            state_fif=2;
            Stm_SendFrame();
            HAL_Delay(500);
        break;
        case 2://0~30
            if(sum_fif<=30)
            {
                Position2=sum_fif+50+5;
                sum_fif++;
                Stm_SendFrame();
                HAL_Delay(100);
            }
            else
            {
                sum_fif=1;
                state_fif=3;
            }
            if(xxx>235 && xxx<245)
                state_fif=5;
        break;
        case 3://30~-30
            if(sum_fif<=60)
            {
                Position2=-sum_fif+30+50+5;
                sum_fif++;
                Stm_SendFrame();
                HAL_Delay(100);
            }
            else
            {
                sum_fif=1;
                state_fif=4;
            }
            if(xxx>235 && xxx<245)
                state_fif=5;
            break;
        case 4://-30~0
            if(sum_fif<=30)
            {
                Position2=sum_fif-30+50+5;
                sum_fif++;
                Stm_SendFrame();
                HAL_Delay(100);
            }
            else
            {
                sum_fif=1;
                state_fif=2;
            }
            if(xxx>235 && xxx<245)
                state_fif=5;
            break;
            
        case 5:
            if(Receive==0)
        {
            Electric_On;//开炮
            HAL_Delay(1000);//延时
            Electric_Off;//关闭
            Electric1_Off;//断掉充电
            HAL_Delay(1000);//延时
            state_fif=6;
        }
            break;
        case 6:
            Position2=0+50;
            Position1=0+50;
            Stm_SendFrame();
            state_fif=0;
            break;
        
    }
    

}


