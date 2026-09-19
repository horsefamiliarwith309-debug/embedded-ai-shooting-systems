#include "stm32f4xx_hal.h"
#include "motor.h"
#include <math.h>
#include "stm.h"
#include "electric.h"
#include "Second.h"
#include "Third.h"
#include "luna.h"
#include "maix.h"


uint8_t state=1;
int Isee1=0;
uint8_t sum1=1;
uint16_t Distence_max=0;
float FIR1=1;//抬升角度系数
float wycsb2=0;

void Fourth()
{
    switch(state)
    {
        case 1://先进行缓慢转动
            
            KP2=10;
            KD2=3;
            KP1=20;
            KD1=1;
            Position1=50;
            Position2=-30+sum1+50;
            Stm_SendFrame();
            HAL_Delay(100);//延时
            state=2;
            if(Position2>=30+50)
            {
                state=0;
                Position1=0+50;
                Position2=0+50;
                Stm_SendFrame();
                HAL_Delay(1000);//延时
            }
            break;
        
        case 2://看到红色标靶
            if(xxx<=242 && xxx>=238)
            {
               Stm_SendFrame();
               state=3;
            }
            else
            {
                sum1++;
                state=1;
            }
            
            break;
            
        case 3://获取红色标靶中心点位置，水平旋转到该角度
            wycsb2=atan((xxx-240)/Luna_Distance)*180/3.14;
            Position2=-30+sum1+wycsb2+50;
            Stm_SendFrame();
            HAL_Delay(1000);//延时
            state=4;
            break;
        
        case 4://竖直方向炮口抬升
            KP1=20;
            KD1=1;
        
            //限幅///
            if(Luna_Distance>300)
                Distence_max=300;
            else if(Luna_Distance<200)
                Distence_max=200;
            else
                Distence_max=Luna_Distance;
            ////////////
            
            wycsb2=FIR1*(float)(Distence_max-200)/300*90;
            Position1=(uint8_t)wycsb2+50;
            Stm_SendFrame();
            HAL_Delay(1000);//延时
            state=5;
            break;
        
        case 5://开火
            if(Receive==0)
            {
                Electric_On;
                HAL_Delay(1000);//延时
                Electric_Off;//关闭蜂鸣器
                Electric1_Off;
                HAL_Delay(1000);//延时
                state=6;
            }
            break;
            
        case 6:
            Position1=0+50;
            Position2=0+50;
            Stm_SendFrame();
            state=0;
            HAL_Delay(1000);//延时
            break;
    }
}