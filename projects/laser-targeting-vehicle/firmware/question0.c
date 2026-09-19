#include "gyro.h"
#include "ti_msp_dl_config.h"
#include "GrayPID.h"
#include "motor.h"
#include "gray.h"
#include "scream.h"
#include "xc_systick.h"
#include "yc_datou_m0.h"
//串口屏传输数据

///////////////

uint8_t flag_qu0=0;
uint8_t state_qu0=1;

float Turn_out0;
float Gan_out0;

//////////////////////////
uint8_t zhanwu=1;


void Quest0()
{
    switch(state_qu0)
    {
        case 1://判断圈数
        if(flag_qu0>=command_2*4)
        {
            state_qu0=0;
            Set_Speed(0,0);
            Set_Speed(1,0);
        }
        else
        {
            state_qu0=2;
            stop_test2=0;
        }
        break;
        case 2://沿0度直走AC
        GreyCamera();
        Gan_out0=GanPID2();
        Set_Speed(0,25-Gan_out0);
        Set_Speed(1,25+Gan_out0);
        if(stop_test2>2000 && val_5>0)
        {
            flag_qu0++;
            stop_test2=0;
            state_qu0=1;
        }
        break;
    }
}


void testggg()
{
    switch (zhanwu) {
        case 1:
        DL_GPIO_setPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);  //亮灯，蜂鸣器程序
        zhanwu=2;
        Set_Speed(0,-6);
        Set_Speed(1,56);
        Emm_V5_Vel_Control(2, 1, 40, 120, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        stop_test2=0;
        break;
        case 2:
        if(stop_test2>1500)
        {
            Set_Speed(0,0);
            Set_Speed(1,0);
            Emm_V5_Vel_Control(2, 1, 0, 120, 1);
            xc_delay(10);
            Emm_V5_Synchronous_motion(2);
            xc_delay(10);
            zhanwu=3;
            DL_GPIO_clearPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);  //亮灯，蜂鸣器程序
        }
        break;
        case 3:

        break;
    }

   

}