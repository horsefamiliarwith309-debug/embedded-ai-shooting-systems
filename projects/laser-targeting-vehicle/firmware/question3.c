#include "ti_msp_dl_config.h"
#include "gyro.h"
#include "yc_datou_m0.h"
#include "eyes1.h"
#include "track.h"
#include "xc_systick.h"
#include "scream.h"

#define ZC_X3 133
#define ZC_Y3 83


//串口屏传输数据
uint8_t kaishirenwu1=0;
///////////////
//打开灯
uint8_t light_3=0;
////////////////
uint8_t state_qu3=1;

float Pos_Now_3;
float Pulse_3;

float track1_out_3,track2_out_3;

void Quest3_1()
{
    switch(state_qu3)
    {
        case 1:
        state_qu3=2;
        break;
        case 2:
        if(command_1==3)
        {
            Emm_V5_Vel_Control(2, 0, 12, 5, 1);
            xc_delay(10);
        }
        Emm_V5_Vel_Control(1, 1, 0, 1, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        state_qu3=3;
        break;
        case 3:
        if(eye_x[0]<ZC_X3+20 && eye_x[0]>ZC_X3-20)
        {
            state_qu3=4;
        }
        break;
        case 4:
        track1_out_3=Track1PID(ZC_Y3);
        track2_out_3=Track2PID(ZC_X3);
        if(track2_out_3>=0)
        {
            Emm_V5_Pos_Control(2, 1, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(2, 1, track2_out_3, 1, 1);
            xc_delay(10);
        }
        else if(track2_out_3<0)
        {
            Emm_V5_Pos_Control(2, 0, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(2, 0, -track2_out_3, 1, 1);
            xc_delay(10);
        }
        if(track1_out_3>=0)
        {
            Emm_V5_Pos_Control(1, 1, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 1, track1_out_3, 1, 1);
            xc_delay(10);
        }
        else if(track1_out_3<0)
        {
            Emm_V5_Pos_Control(1, 0, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 0, -track1_out_3, 1, 1);
            xc_delay(10);
        }
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        if((eye_x[0]-ZC_X3<1 && eye_x[0]-ZC_X3>-1) && (eye_y[0]-ZC_Y3<1 && eye_y[0]-ZC_Y3>-1))
        {
            DL_GPIO_setPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);
            light_3=1;
            state_qu3=5;
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

void Quest3_1b()
{
    switch(state_qu3)
    {
        case 1:
        state_qu3=2;
        break;
        case 2:
        if(command_1==3)
        {
            Emm_V5_Vel_Control(2, 0, 12, 5, 1);
            xc_delay(10);
        }
        Emm_V5_Vel_Control(1, 1, 0, 1, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        state_qu3=3;
        break;
        case 3:
        if(eye_x[0]<ZC_X3+20 && eye_x[0]>ZC_X3-20)
        {
            state_qu3=4;
        }
        break;
        case 4:
        track1_out_3=Track1PID(ZC_Y3);
        track2_out_3=Track2PID(ZC_X3);
        if(track2_out_3>=0)
        {
            Emm_V5_Pos_Control(2, 1, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(2, 1, track2_out_3, 1, 1);
            xc_delay(10);
        }
        else if(track2_out_3<0)
        {
            Emm_V5_Pos_Control(2, 0, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(2, 0, -track2_out_3, 1, 1);
            xc_delay(10);
        }
        if(track1_out_3>=0)
        {
            Emm_V5_Pos_Control(1, 1, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 1, track1_out_3, 1, 1);
            xc_delay(10);
        }
        else if(track1_out_3<0)
        {
            Emm_V5_Pos_Control(1, 0, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 0, -track1_out_3, 1, 1);
            xc_delay(10);
        }
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        if((eye_x[0]-ZC_X3<5 && eye_x[0]-ZC_X3>-5) && (eye_y[0]-ZC_Y3<5 && eye_y[0]-ZC_Y3>-5))
        {
            DL_GPIO_setPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);
            light_3=1;
            state_qu3=5;
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

void Quest3_2()
{
    switch(state_qu3)
    {
        case 1:
        state_qu3=2;
        break;
        case 2:
        Emm_V5_Vel_Control(2, 1, 12, 5, 1);
        xc_delay(10);
        Emm_V5_Vel_Control(1, 1, 0, 1, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        state_qu3=3;
        break;
        case 3:
        if(eye_x[0]<ZC_X3+20 && eye_x[0]>ZC_X3-20)
        {
            state_qu3=4;
        }
        break;
        case 4:
        track1_out_3=Track1PID(ZC_Y3);
        track2_out_3=Track2PID(ZC_X3);
        if(track2_out_3>=0)
        {
            Emm_V5_Pos_Control(2, 1, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(2, 1, track2_out_3, 1, 1);
            xc_delay(10);
        }
        else if(track2_out_3<0)
        {
            Emm_V5_Pos_Control(2, 0, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(2, 0, -track2_out_3, 1, 1);
            xc_delay(10);
        }
        if(track1_out_3>=0)
        {
            Emm_V5_Pos_Control(1, 1, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 1, track1_out_3, 1, 1);
            xc_delay(10);
        }
        else if(track1_out_3<0)
        {
            Emm_V5_Pos_Control(1, 0, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 0, -track1_out_3, 1, 1);
            xc_delay(10);
        }
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        if((eye_x[0]-ZC_X3<1 && eye_x[0]-ZC_X3>-1) && (eye_y[0]-ZC_Y3<1 && eye_y[0]-ZC_Y3>-1))
        {
            DL_GPIO_setPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);
            light_3=1;
            state_qu3=5;
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

void Quest3_2b()
{
    switch(state_qu3)
    {
        case 1:
        state_qu3=2;
        break;
        case 2:
        Emm_V5_Vel_Control(2, 1, 12, 5, 1);
        xc_delay(10);
        Emm_V5_Vel_Control(1, 1, 0, 1, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        state_qu3=3;
        break;
        case 3:
        if(eye_x[0]<ZC_X3+20 && eye_x[0]>ZC_X3-20)
        {
            state_qu3=4;
        }
        break;
        case 4:
        track1_out_3=Track1PID(ZC_Y3);
        track2_out_3=Track2PID(ZC_X3);
        if(track2_out_3>=0)
        {
            Emm_V5_Pos_Control(2, 1, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(2, 1, track2_out_3, 1, 1);
            xc_delay(10);
        }
        else if(track2_out_3<0)
        {
            Emm_V5_Pos_Control(2, 0, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(2, 0, -track2_out_3, 1, 1);
            xc_delay(10);
        }
        if(track1_out_3>=0)
        {
            Emm_V5_Pos_Control(1, 1, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 1, track1_out_3, 1, 1);
            xc_delay(10);
        }
        else if(track1_out_3<0)
        {
            Emm_V5_Pos_Control(1, 0, 2, 2, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 0, -track1_out_3, 1, 1);
            xc_delay(10);
        }
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        if((eye_x[0]-ZC_X3<5 && eye_x[0]-ZC_X3>-5) && (eye_y[0]-ZC_Y3<5 && eye_y[0]-ZC_Y3>-5))
        {
            DL_GPIO_setPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);
            light_3=1;
            state_qu3=5;
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