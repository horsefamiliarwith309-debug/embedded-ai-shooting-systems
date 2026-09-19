#include "stm32f4xx_hal.h"
#include "motor.h"
#include <math.h>
#include "stm.h"
#include "electric.h"
#include "Second.h"
#include "do_scream.h"

uint8_t Position2 = 0;
uint8_t KP2=0;
uint8_t KD2=0;
uint8_t state_thd=1;

float wycsb1=0;



void Third()
{
    switch(state_thd)
    {
        case 1:
            //赋初值

            FIR=1;

            
            //上方电机转动到合适位置
            KP1=20;
            KD1=1;
            wycsb1=FIR*(float)(Length_0-200)/300*90;
            Position1=(uint8_t)wycsb1+50;
            KP2=KP1;
            KD2=KD1;
            Position2=(uint8_t)(Angle_0+50);
            
            //发送数据，等待转动
            Stm_SendFrame();
            HAL_Delay(2000);//延时
            state_thd=2;
            break;
        case 2:
            if(Receive==0)
            {
                Electric_On;
                HAL_Delay(1000);//延时
                Electric_Off;//关闭蜂鸣器
                Electric1_Off;
                HAL_Delay(1000);//延时
                state_thd=3;
            }
            break;
        case 3:
            Position1=0+50;
            Position2=0+50;
            Stm_SendFrame();
            state_thd=0;
            break;
        
    }

    //开炮
    
}