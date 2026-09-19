#include "stm32f4xx_hal.h"
#include "motor.h"
#include <math.h>
#include "stm.h"
#include "electric.h"
#include "Third.h"
#include "do_scream.h"
uint8_t Position1 = 0;
uint8_t KP1=0;
uint8_t KD1=0;


uint8_t Distence=250;//距离的位置
float FIR=1.0f;//调整角度的系数
uint8_t Afa=0;//角度的位置
float wycsb=0;

uint8_t state_sec=1;

void Second()
{
    //上方电机转动到合适位置
    switch (state_sec)
    {
        case 1:
            KP1=20;
            KD1=1;
            KP2=KP1;
            KD2=KD1;
            wycsb=FIR*(float)(Length_0-200)/300*90;
            Position1=(uint8_t)wycsb+50;
            Position2=0+50;
            //发送数据，等待转动
            Stm_SendFrame();
            HAL_Delay(2000);//延时
            state_sec=2;
            break;
        case 2:
            if(Receive==0)
            {
                Electric_On;
                HAL_Delay(1000);//延时
                Electric_Off;//关闭蜂鸣器
                Electric1_Off;
                HAL_Delay(1000);//延时
                state_sec=3;
            }    
            break;
        case 3:
                Position1=0+50;
                Stm_SendFrame();
                state_sec=0;
            break;
    }
    
    
    
    //开炮
    
    
    
    
}