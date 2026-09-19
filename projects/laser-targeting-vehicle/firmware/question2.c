#include "ti_msp_dl_config.h"
#include "gyro.h"
#include "yc_datou_m0.h"
#include "eyes1.h"
#include "track.h"
#include "xc_systick.h"

#define ZC_X 133
#define ZC_Y 83

//串口屏传输数据
uint8_t kaishirenwu=0;
///////////////
//打开灯
uint8_t light=0;
///////////////
uint8_t state_qu2=1;

float Pos_Now_2;

float Pulse_2;

float track1_out,track2_out;

void Quest2()
{
    switch(state_qu2)
    {
        case 1:
        if(eye_x[0]!=0 && eye_y[0]!=0)
        {
            state_qu2=4;
        }
        break;
        case 4:
        track1_out=Track1PID(ZC_Y);
        track2_out=Track2PID(ZC_X);
        if(track2_out>=0)
        {
            Emm_V5_Pos_Control(2, 1, 2, 1, 1, 0, 1);
            // Emm_V5_Vel_Control(2, 1, track2_out, 1, 1);
            xc_delay(10);
        }
        else if(track2_out<0)
        {
            Emm_V5_Pos_Control(2, 0, 2, 1, 1, 0, 1);
            // Emm_V5_Vel_Control(2, 0, -track2_out, 1, 1);
            xc_delay(10);
        }
        if(track1_out>=0)
        {
            Emm_V5_Pos_Control(1, 1, 2, 1, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 1, track1_out, 1, 1);
            xc_delay(10);
        }
        else if(track1_out<0)
        {
            Emm_V5_Pos_Control(1, 0, 2, 1, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 0, -track1_out, 1, 1);
            xc_delay(10);
        }
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        
        if((eye_x[0]-ZC_X<1 && eye_x[0]-ZC_X>-1) && (eye_y[0]-ZC_Y<1 && eye_y[0]-ZC_Y>-1))
        {
            DL_GPIO_setPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);  //亮灯，蜂鸣器程序
            state_qu2=5;
        }
        else 
        {
            DL_GPIO_clearPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);  //关灯，蜂鸣器程序
        }
        break;
        case 5:
        Emm_V5_Vel_Control(2, 0, 0, 1, 1);
        xc_delay(10);
        Emm_V5_Vel_Control(1, 0, 0, 1, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        break;
    }
}

void Quest2_1()
{
    switch(state_qu2)
    {
        case 1:
        if(eye_x[0]!=0 && eye_y[0]!=0)
        {
            state_qu2=4;
        }
        break;
        case 4:
        track1_out=Track1PID(ZC_Y);
        track2_out=Track2PID(ZC_X);
        if(track2_out>=0)
        {
            Emm_V5_Pos_Control(2, 1, 2, 1, 1, 0, 1);
            // Emm_V5_Vel_Control(2, 1, track2_out, 1, 1);
            xc_delay(10);
        }
        else if(track2_out<0)
        {
            Emm_V5_Pos_Control(2, 0, 2, 1, 1, 0, 1);
            // Emm_V5_Vel_Control(2, 0, -track2_out, 1, 1);
            xc_delay(10);
        }
        if(track1_out>=0)
        {
            Emm_V5_Pos_Control(1, 1, 2, 1, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 1, track1_out, 1, 1);
            xc_delay(10);
        }
        else if(track1_out<0)
        {
            Emm_V5_Pos_Control(1, 0, 2, 1, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 0, -track1_out, 1, 1);
            xc_delay(10);
        }
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        
        if((eye_x[0]-ZC_X<5 && eye_x[0]-ZC_X>-5) && (eye_y[0]-ZC_Y<5 && eye_y[0]-ZC_Y>-5))
        {
            DL_GPIO_setPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);  //亮灯，蜂鸣器程序
            state_qu2=5;
        }
        else 
        {
            DL_GPIO_clearPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);  //关灯，蜂鸣器程序
        }
        break;
        case 5:
        Emm_V5_Vel_Control(2, 0, 0, 1, 1);
        xc_delay(10);
        Emm_V5_Vel_Control(1, 0, 0, 1, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        break;
    }
}