#include "gyro.h"
#include "ti_msp_dl_config.h"
#include "GrayPID.h"
#include "motor.h"
#include "gray.h"
#include "scream.h"
//串口屏传输数据

///////////////

uint8_t flag_qu1=0;
uint8_t state_qu1=1;

float Turn_out;
float Gan_out;

void Quest1()
{
    switch(state_qu1)
    {
        case 1://判断圈数
        if(flag_qu1>=command_2)
        {
            state_qu1=0;
        }
        else
        {
            state_qu1=2;
        }
        break;
        case 2://沿0度直走AC
        Turn_out=TurnPID(0);
        GreyCamera();
        Gan_out=GanPID();
        Set_Speed(0,20-Gan_out);
        Set_Speed(1,20+Gan_out);
        if(val_5>0)
        {
            Set_Speed(0, 0);
            Set_Speed(1, 0);
            state_qu1=3;
        }
        break;
        case 3://转到90度C
        if((RelativeYaw-90)<=2 && (RelativeYaw-90)>=-2)
            {
                state_qu1=4;
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
            }   
            else
            {
                Turn_out=TurnPID(90);
                Set_Speed(0,Turn_out);
                Set_Speed(1,-Turn_out);
            }
        break;
        case 4://沿90度直走CD
        Turn_out=TurnPID(0);
        GreyCamera();
        Gan_out=GanPID();
        Set_Speed(0,20-Gan_out);
        Set_Speed(1,20+Gan_out);
        if(val_5>0)
        {
            Set_Speed(0, 0);
            Set_Speed(1, 0);
            state_qu1=5;
        }
        break;
        case 5://转到180度D
        if((RelativeYaw-90)<=2 && (RelativeYaw-90)>=-2)
            {
                state_qu1=6;
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
            }   
            else
            {
                Turn_out=TurnPID(90);
                Set_Speed(0,Turn_out);
                Set_Speed(1,-Turn_out);
            }
        break;
        case 6://沿180度直走DB
        Turn_out=TurnPID(0);
        GreyCamera();
        Gan_out=GanPID();
        Set_Speed(0,20-Gan_out);
        Set_Speed(1,20+Gan_out);
        if(val_5>0)
        {
            Set_Speed(0, 0);
            Set_Speed(1, 0);
            state_qu1=7;
        }
        break;
        case 7://转到270度B
        if((RelativeYaw-90)<=2 && (RelativeYaw-90)>=-2)
            {
                state_qu1=8;
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
            }   
            else
            {
                Turn_out=TurnPID(90);
                Set_Speed(0,Turn_out);
                Set_Speed(1,-Turn_out);
            }
        break;
        case 8://沿270度直走BA
        Turn_out=TurnPID(0);
        GreyCamera();
        Gan_out=GanPID();
        Set_Speed(0,20-Gan_out);
        Set_Speed(1,20+Gan_out);
        if(val_5>0)
        {
            Set_Speed(0, 0);
            Set_Speed(1, 0);
            state_qu1=9;
        }
        break;
        case 9://转到360度A
        if((RelativeYaw-90)<=2 && (RelativeYaw-90)>=-2)
            {
                flag_qu1++;
                state_qu1=1;
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
            }   
            else
            {
                Turn_out=TurnPID(90);
                Set_Speed(0,Turn_out);
                Set_Speed(1,-Turn_out);
            }
        break;

    }
}
