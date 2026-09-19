#include "gyro.h"
#include "ti_msp_dl_config.h"
#include "GrayPID.h"
#include "motor.h"
#include "yc_datou_m0.h"
#include "xc_systick.h"
#include "track.h"
#include "gray.h"
#include "eyes1.h"

//串口屏传输数据

#define ZC_X4 133
#define ZC_Y4 83

///////////////

uint8_t flag_qu4=0;
uint8_t state_qu4=0;//WARNING 记得改为0
uint8_t start=1;
uint8_t state_cao=0;
uint8_t state_ta4=7;
uint8_t state_rou=0;
uint8_t Get_turn=0;
uint8_t queues=0;
uint8_t turns=0;
uint8_t the_second=0;


float Turn_out4;
float Gan_out4;
float track1_out4,track2_out4;
float Turn_fixed=0.0f;

float X_1,Y_1;
float X_rea,Y_rea;
float X_rou,Y_rou;
uint8_t rou_flag=0;
int xxx=0;

void Round_start()
{
    switch (start)
    {   case 1:
        track1_out4=Track1PID(ZC_Y4);
        track2_out4=Track2PID(ZC_X4);
        if(track2_out4>0)
        {
            Emm_V5_Pos_Control(2, 1, 2, 1, 1, 0, 1);
            xc_delay(10);
        }
        else if(track2_out4<0)
        {
            Emm_V5_Pos_Control(2, 0, 2, 1, 1, 0, 1);
            xc_delay(10);
        }
        else
        {
            Emm_V5_Pos_Control(2, 0, 2, 1, 0, 0, 1);
        }
        if(track1_out4>0)
        {
            Emm_V5_Pos_Control(1, 1, 2, 1, 1, 0, 1);
            xc_delay(10);
        }
        else if(track1_out4<0)
        {
            Emm_V5_Pos_Control(1, 0, 2, 1, 1, 0, 1);
            xc_delay(10);
        }
        else
        {
            Emm_V5_Pos_Control(1, 0, 2, 1, 0, 0, 1);
        }
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        if((eye_x[0]-ZC_X4<1 && eye_x[0]-ZC_X4>-1) && (eye_y[0]-ZC_Y4<1 && eye_y[0]-ZC_Y4>-1))
        {
            DL_GPIO_setPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);  //亮灯，蜂鸣器程序
            start=2;
        }
        break;
        case 2:
        Emm_V5_Pos_Control(1, 1, 2, 1, 0, 0, 1);
        xc_delay(10);
        Emm_V5_Pos_Control(1, 0, 2, 1, 0, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        stop_test2=0;
        Emm_V5_Reset_CurPos_To_Zero(1);
        xc_delay(10);
        Emm_V5_Reset_CurPos_To_Zero(2);
        xc_delay(10);
       state_rou=1;
       start=0;
        break;
    }
}
void Round()
{       
		X_rou=50.0*cos((float)the_time/10.0);
		Y_rou=50.0*sin((float)the_time/10.0);
		switch(state_rou)
		{
			case 1:
				if(X_rou>=0)
				{
					Emm_V5_Pos_Control(2, 1, 1, 1, X_rou, 1, 1); // 多机同步标志位置1
				}
				else
				{
					Emm_V5_Pos_Control(2, 0, 1, 1, -X_rou, 1, 1); // 多机同步标志位置1
				}
				stop_test2=0;
				state_rou=2;
			break;
			case 2:
				if(stop_test2>10)
				{
					stop_test2=0;
					state_rou=3;
				}
				break;
			case 3:
				if(Y_rou>=0)
				{
					Emm_V5_Pos_Control(1, 0, 1, 1, Y_rou, 1, 1); // 多机同步标志位置1
				}
				else
				{
					Emm_V5_Pos_Control(1, 1, 1, 1, -Y_rou, 1, 1); // 多机同步标志位置1
				}
				stop_test2=0;
				state_rou=4;
				break;
			case 4:
				if(stop_test2>10)
				{
					stop_test2=0;
					state_rou=5;
				}
				break;
			case 5:
				Emm_V5_Synchronous_motion(0); 						 // 广播地址0触发
				state_rou=6;
                stop_test2=0;
				break;
			case 6:
				if(stop_test2>10)
				{
					stop_test2=0;
					state_rou=1;
				}
				break;
		}
		
		
}


// void Rou_Start()
// {
//     switch (start)
//     {   case 1:
//         if(!rou_flag && eye_x[1]!=0 && eye_y[1]!=0)
//         {
//             X_rou=148.5+60.0;
//             Y_rou=105;
//             X_1=(float)((eye_x[2]-eye_x[1])+(eye_x[2]-eye_x[1]))/2;
//             Y_1=(float)((eye_y[2]-eye_y[1])+(eye_y[2]-eye_y[1]))/2;
//             X_rea=X_rou/297*X_1;
//             Y_rea=Y_rou/210*Y_1;
//             rou_flag=1;
//         }
//         track1_out4=Track1PID(ZC_Y4+Y_rea);
//         track2_out4=Track2PID(ZC_X4+X_rea);
//         if(track2_out4>0)
//         {
//             Emm_V5_Pos_Control(2, 1, 2, 1, 1, 0, 1);
//             xc_delay(10);
//         }
//         else if(track2_out4<0)
//         {
//             Emm_V5_Pos_Control(2, 0, 2, 1, 1, 0, 1);
//             xc_delay(10);
//         }
//         else
//         {
//             Emm_V5_Pos_Control(2, 0, 2, 1, 0, 0, 1);
//         }
//         if(track1_out4>=0)
//         {
//             Emm_V5_Pos_Control(1, 1, 2, 1, 1, 0, 1);
//             xc_delay(10);
//         }
//         else if(track1_out4<0)
//         {
//             Emm_V5_Pos_Control(1, 0, 2, 1, 1, 0, 1);
//             xc_delay(10);
//         }
//         else
//         {
//             Emm_V5_Pos_Control(1, 0, 2, 1, 0, 0, 1);
//         }
//         Emm_V5_Synchronous_motion(0);
//         xc_delay(10);
//         if((eye_x[0]-(ZC_X4+X_rea)<1 && eye_x[0]-(ZC_X4+X_rea)>-1) && (eye_y[0]-(ZC_Y4+Y_rea)<1 && eye_y[0]-(ZC_Y4+Y_rea)>-1))
//         {
//             DL_GPIO_setPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);  //亮灯，蜂鸣器程序
//             start=2;
//         }
//         break;
//         case 2:
//         Emm_V5_Pos_Control(1, 1, 2, 1, 0, 0, 1);
//         xc_delay(10);
//         Emm_V5_Pos_Control(1, 0, 2, 1, 0, 0, 1);
//         xc_delay(10);
//         Emm_V5_Synchronous_motion(0);
//         xc_delay(10);
//         state_qu4=14;
//         start=0;
//         state_cao=1;
//         xc_delay(1800);
//         stop_test2=0;
//         break;
//     }
// }

// void yuncao_rou()
// {
//     switch(state_cao)
//     {
//         case 1://发送数据修正X
//         //先判断调用何种PID
//         X_rou=148.5+60.0*cos((float)the_time/3100.0);
// 		Y_rou=105+60.0*sin((float)the_time/3100.0);
//         X_1=(float)((eye_x[2]-eye_x[1])+(eye_x[2]-eye_x[1]))/2;
//         Y_1=(float)((eye_y[4]-eye_y[1])+(eye_y[3]-eye_y[2]))/2;
//         X_rea=X_rou/297*X_1;
//         Y_rea=Y_rou/210*Y_1;
//         track1_out4=Track1PID_move(ZC_Y4+Y_rea);
//         if(queues==1)
//             track2_out4=Track2PID_front(ZC_X4+X_rea);
//         else if(queues==2 || queues==4)
//             track2_out4=Track2PID_side(ZC_X4+X_rea);
//         else if(queues==3)
//             track2_out4=Track2PID_back(ZC_X4+X_rea);
        
//         //再判断调用哪条线路
//         if(queues==1)
//         {
//             if(track2_out4>0)
//             {
//                 Emm_V5_Pos_Control(2, 1, 1, 1, 1, 0, 1);
//             }
//             else if(track2_out4<0)
//             {
//                 Emm_V5_Pos_Control(2, 0, 1, 1, 1, 0, 1);
//             }
//             else {
//                 Emm_V5_Pos_Control(2, 0, 1, 1, 0, 0, 1);
//             }
//         }
//         else if(queues==2 || queues ==4)
//         {
//             if(track2_out4>0)
//             {
//                 Emm_V5_Pos_Control(2, 1, 1, 1, 1, 0, 1);
//             }
//             else if(track2_out4<0)
//             {
//                 Emm_V5_Pos_Control(2, 0, 1, 1, 1, 0, 1);
//             }
//             else {
//                 Emm_V5_Pos_Control(2, 0, 1, 1, 0, 0, 1);
//             }
//         }
//         else if (queues==3) 
//         {
//             if(track2_out4>0)
//             {
//                 Emm_V5_Pos_Control(2, 1, 1, 1, 1, 0, 1);
//             }
//             else if(track2_out4<0)
//             {
//                 Emm_V5_Pos_Control(2, 0, 1, 1, 1, 0, 1);
//             }
//             else {
//                 Emm_V5_Pos_Control(2, 0, 1, 1, 0, 0, 1);
//             }
//         }
//         state_cao=2;
//         stop_ta=0;
//         break;
//         case 2://中断延时10ms
//         if(stop_ta>10)
//             state_cao=3;
//         break;
//         case 3://发送数据修正Y
//         if(track1_out4>0)
//         {
//             Emm_V5_Pos_Control(1, 1, 1, 1, 1, 0, 1);
//         }
//         else if(track1_out4<0)
//         {
//             Emm_V5_Pos_Control(1, 0, 1, 1, 1, 0, 1);
//         }
//         else
//         {
//             Emm_V5_Pos_Control(1, 0, 1, 1, 0, 0, 1);
//         }
//         state_cao=4;
//         stop_ta=0;
//         break;
//         case 4://中断延时10ms
//         if(stop_ta>=10)
//             state_cao=5;
//         break;
//         case 5://双张大头开始运动
//         Emm_V5_Synchronous_motion(0);
//         state_cao=6;
//         stop_ta=0;
//         break;
//         case 6://中断延时10ms，回到开始
//         if(stop_ta>=10)
//         {
//             state_cao=1;
//         }  
//         break;
//     }
// }

void yuncao()
{
    switch(state_cao)
    {
        case 1://发送数据修正X
        //先判断调用何种PID
        track1_out4=Track1PID_move(ZC_Y4);
        if(queues==1)
            track2_out4=Track2PID_front(ZC_X4);
        else if(queues==2 || queues==4)
            track2_out4=Track2PID_side(ZC_X4);
        else if(queues==3)
            track2_out4=Track2PID_back(ZC_X4);
        //  track2_out4=Track2PID(ZC_X4);
        
        //再判断调用哪条线路
        if(queues==1)
        {
            if(track2_out4>0)
            {
                Emm_V5_Vel_Control(2, 1, track2_out4, 120, 1);
            }
            else if(track2_out4<0)
            {
                Emm_V5_Vel_Control(2, 0, -track2_out4, 120, 1);
            }
            else {
                Emm_V5_Vel_Control(2, 0, 0, 120, 1);
            }
        }
        else if(queues==2 || queues ==4)
        {
            if(track2_out4>0)
            {
                Emm_V5_Vel_Control(2, 1, track2_out4, 80, 1);
            }
            else if(track2_out4<0)
            {
                Emm_V5_Vel_Control(2, 0, -track2_out4, 80, 1);
            }
            else {
                Emm_V5_Vel_Control(2, 0, 0, 80, 1);
            }
        }
        else if (queues==3) 
        {
            if(track2_out4>0)
            {
                Emm_V5_Vel_Control(2, 1, track2_out4, 120, 1);
            }
            else if(track2_out4<0)
            {
                Emm_V5_Vel_Control(2, 0, -track2_out4, 120, 1);
            }
            else {
                Emm_V5_Vel_Control(2, 0, 0, 120, 1);
            }
        }
        state_cao=2;
        stop_ta=0;
        break;
        case 2://中断延时10ms
        if(stop_ta>10)
            state_cao=3;
        break;
        case 3://发送数据修正Y
        if(track1_out4>0)
        {
            Emm_V5_Pos_Control(1, 1, 1, 1, 1, 0, 1);
        }
        else if(track1_out4<0)
        {
            Emm_V5_Pos_Control(1, 0, 1, 1, 1, 0, 1);
        }
        else
        {
            Emm_V5_Pos_Control(1, 0, 1, 1, 0, 0, 1);
        }
        state_cao=4;
        stop_ta=0;
        break;
        case 4://中断延时10ms
        if(stop_ta>=10)
            state_cao=5;
        break;
        case 5://双张大头开始运动
        Emm_V5_Synchronous_motion(0);
        state_cao=6;
        stop_ta=0;
        break;
        case 6://中断延时10ms，回到开始
        if(stop_ta>=10)
        {
            state_cao=1;
        }  
        break;
    }
        
}

// void Quest6_2()
// {
//     switch(state_qu4)
//     {
//         case 14:
//         Set_Speed(0,21);
//         Set_Speed(1,21);
//         queues=1;
//         yuncao_rou();
//         stop_test2=0;
//         state_qu4=15;
//         break;
//         case 15:
//         if(stop_test2>400)
//         {
//             state_qu4=1;
//             Set_Speed(0,0);
//             Set_Speed(1,0);
//             stop_test2=0;
//         } 
//         break;
//         case 1://直接启动转弯A
//         Set_Speed(0,-5);
//         Set_Speed(1,30);
//         Emm_V5_Pos_Control(2, 1, 19, 200, 800, 0, 1);
//         xc_delay(10);
//         Emm_V5_Synchronous_motion(2);
//         xc_delay(10);
//         state_qu4=2;
//         stop_test2=0;
//         Err_fro_sum=0;
//         Err_fro=0;
//         Err_fro_D=0;
//         break;
//         case 2://A转弯判断
//         if(stop_test2>450)
//         {
//             state_qu4=3;
//             state_cao=1;
//             Set_Speed(0,0);
//             Set_Speed(1,0);
//             stop_test2=0;
//         }   
//         break;
//         case 3://直走AC
//         GreyCamera();
//         Gan_out4=GanPID();
//         queues=2;
//         Set_Speed(0,25-Gan_out4);
//         Set_Speed(1,25+Gan_out4);
//         yuncao_rou();
//         if(val_5>0 && stop_test2>2000)
//             {
//                 Set_Speed(0, 0);
//                 Set_Speed(1, 0);
//                 state_qu4=4;
//             }
//         break;
//         case 4://直接启动转弯C
//         Set_Speed(0,-5);
//         Set_Speed(1,30);
//         Emm_V5_Pos_Control(2, 1, 16, 180, 800, 0, 1);
//         xc_delay(10);
//         Emm_V5_Synchronous_motion(2);
//         xc_delay(10);
//         state_qu4=5;
//         stop_test2=0;
//         Err_fro_sum=0;
//         Err_fro=0;
//         Err_fro_D=0;
//         break;
//         case 5://C转弯判断
//         if(stop_test2>450)
//         {
//             state_qu4=6;
//             state_cao=1;
//             Set_Speed(0,0);
//             Set_Speed(1,0);
//             stop_test2=0;
//         }   
//         break;
//         case 6://直走CD
//         GreyCamera();
//         Gan_out4=GanPID();
//         queues=3;
//         Set_Speed(0,21-Gan_out4);
//         Set_Speed(1,21+Gan_out4);
//         yuncao_rou();
//         if(val_5>0 && stop_test2>2000)
//             {
//                 Set_Speed(0, 0);
//                 Set_Speed(1, 0);
//                 state_qu4=7;
//             }
//         break;
//         case 7://直接启动转弯D
//         Set_Speed(0,-5);
//         Set_Speed(1,30);
//         Emm_V5_Pos_Control(2, 1, 16, 200, 800, 0, 1);
//         xc_delay(10);
//         Emm_V5_Synchronous_motion(2);
//         xc_delay(10);
//         state_qu4=8;
//         stop_test2=0;
//         Err_fro_sum=0;
//         Err_fro=0;
//         Err_fro_D=0;
//         break;
//         case 8://D转弯判断
//         if(stop_test2>450)
//         {
//             state_qu4=9;
//             state_cao=1;
//             Set_Speed(0,0);
//             Set_Speed(1,0);
//             stop_test2=0;
//         } 
//         break;
//         case 9://直走DB
//         GreyCamera();
//         Gan_out4=GanPID();
//         queues=4;
//         Set_Speed(0,25-Gan_out4);
//         Set_Speed(1,25+Gan_out4);
//         yuncao_rou();
//         if(val_5>0 && stop_test2>2000)
//             {
//                 InitialYaw=Gyro_Yaw;
//                 Set_Speed(0, 0);
//                 Set_Speed(1, 0);
//                 state_qu4=10;
//             }
//         break;
//         case 10://直接启动转弯B
//         Set_Speed(0,-5);
//         Set_Speed(1,30);
//         Emm_V5_Pos_Control(2, 1, 17, 100, 800, 0, 1);
//         xc_delay(10);
//         Emm_V5_Synchronous_motion(2);
//         xc_delay(10);
//         state_qu4=11;
//         stop_test2=0;
//         Err_fro_sum=0;
//         Err_fro=0;
//         Err_fro_D=0;
//         break;
//         case 11://B转弯判断
//         if(stop_test2>550)
//             {
//                 state_qu4=12;
//                 state_cao=1;
//                 Set_Speed(0, 0);
//                 Set_Speed(1, 0);
//                 stop_test2=0;
//             }
//         break;
//         case 12://直走BA
//         GreyCamera();
//         Gan_out4=GanPID();
//         queues=4;
//         Set_Speed(0,21-Gan_out4);
//         Set_Speed(1,21+Gan_out4);
//         yuncao_rou();
//         if(val_5>0 && stop_test2>2000)
//             {
//                 InitialYaw=Gyro_Yaw;
//                 Set_Speed(0, 0);
//                 Set_Speed(1, 0);
//                 state_qu4=13;
//             }
//         break;
//         case 13:
//             Set_Speed(0,0);
//             Set_Speed(1,0);
//             yuncao_rou();
//             // Emm_V5_Vel_Control(2, 1, 0, 120, 1);
//             // xc_delay(10);
//             // Emm_V5_Vel_Control(1, 1, 0, 120, 1);
//             // xc_delay(10);
//             // Emm_V5_Synchronous_motion(0);
//             // xc_delay(10);
//         break;
//     }
// }

void Quest4()
{
    switch(state_qu4)
    {
        case 14:
        Set_Speed(0,21);
        Set_Speed(1,21);
        queues=1;
        yuncao();
        stop_test2=0;
        state_qu4=15;
        break;
        case 15:
        if(stop_test2>200)
        {
            state_qu4=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        } 
        break;
        case 1://直接启动转弯A
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 19, 200, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 19, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=2;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 2://A转弯判断
        if(stop_test2>450)
        {
            state_qu4=3;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        }   
        break;
        case 3://直走AC
        GreyCamera();
        Gan_out4=GanPID();
        queues=2;
        Set_Speed(0,25-Gan_out4);
        Set_Speed(1,25+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=4;
            }
        break;
        case 4://直接启动转弯C
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 15, 180, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 16, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=5;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 5://C转弯判断
        if(stop_test2>450)
        {
            state_qu4=6;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        }   
        break;
        case 6://直走CD
        GreyCamera();
        Gan_out4=GanPID();
        queues=3;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=7;
            }
        break;
        case 7://直接启动转弯D
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 15, 200, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 13, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=8;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 8://D转弯判断
        if(stop_test2>450)
        {
            state_qu4=9;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        } 
        break;
        case 9://直走DB
        GreyCamera();
        Gan_out4=GanPID();
        queues=4;
        Set_Speed(0,25-Gan_out4);
        Set_Speed(1,25+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=10;
            }
        break;
        case 10://直接启动转弯B
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 17, 100, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 17, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=11;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 11://B转弯判断
        if(stop_test2>550)
            {
                state_qu4=12;
                state_cao=1;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                stop_test2=0;
            }
        break;
        case 12://直走BA
        GreyCamera();
        Gan_out4=GanPID();
        queues=4;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=13;
            }
        break;
        case 13:
            Set_Speed(0,0);
            Set_Speed(1,0);
            yuncao();
            // Emm_V5_Vel_Control(2, 1, 0, 120, 1);
            // xc_delay(10);
            // Emm_V5_Vel_Control(1, 1, 0, 120, 1);
            // xc_delay(10);
            // Emm_V5_Synchronous_motion(0);
            // xc_delay(10);
        break;
    }
}

void Quest4_1()
{
    switch(state_qu4)
    {
        case 14:
        Set_Speed(0,21);
        Set_Speed(1,21);
        queues=1;
        yuncao();
        stop_test2=0;
        state_qu4=15;
        break;
        case 15:
        if(stop_test2>200)
        {
            state_qu4=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        } 
        break;
        case 1://直接启动转弯A
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 19, 200, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 19, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=2;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 2://A转弯判断
        if(stop_test2>500)
        {
            state_qu4=3;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        }   
        break;
        case 3://直走AC
        GreyCamera();
        Gan_out4=GanPID();
        queues=2;
        Set_Speed(0,25-Gan_out4);
        Set_Speed(1,25+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=4;
            }
        break;
        case 4://直接启动转弯C
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 15, 180, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 16, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=5;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 5://C转弯判断
        if(stop_test2>500)
        {
            state_qu4=6;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        }   
        break;
        case 6://直走CD
        GreyCamera();
        Gan_out4=GanPID();
        queues=3;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=7;
            }
        break;
        case 7://直接启动转弯D
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 15, 200, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 13, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=8;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 8://D转弯判断
        if(stop_test2>500)
        {
            state_qu4=9;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        } 
        break;
        case 9://直走DB
        GreyCamera();
        Gan_out4=GanPID();
        queues=4;
        Set_Speed(0,25-Gan_out4);
        Set_Speed(1,25+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=10;
            }
        break;
        case 10://直接启动转弯B
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 17, 100, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 17, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=11;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 11://B转弯判断
        if(stop_test2>600)
            {
                state_qu4=12;
                state_cao=1;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                stop_test2=0;
            }
        break;
        case 12://直走BA
        GreyCamera();
        Gan_out4=GanPID();
        queues=4;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=13;
            }
        break;
        case 13:
            Set_Speed(0,0);
            Set_Speed(1,0);
            yuncao();
            // Emm_V5_Vel_Control(2, 1, 0, 120, 1);
            // xc_delay(10);
            // Emm_V5_Vel_Control(1, 1, 0, 120, 1);
            // xc_delay(10);
            // Emm_V5_Synchronous_motion(0);
            // xc_delay(10);
        break;
    }
}

void Quest4_4()
{
    switch(state_qu4)
    {
        case 14:
        Set_Speed(0,21);
        Set_Speed(1,21);
        queues=1;
        yuncao();
        stop_test2=0;
        state_qu4=15;
        break;
        case 15:
        if(stop_test2>300)
        {
            state_qu4=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        } 
        break;
        case 1://直接启动转弯A
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 19, 200, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 19, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=2;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 2://A转弯判断
        if(stop_test2>500)
        {
            state_qu4=3;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        }   
        break;
        case 3://直走AC
        GreyCamera();
        Gan_out4=GanPID();
        queues=2;
        Set_Speed(0,25-Gan_out4);
        Set_Speed(1,25+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=4;
            }
        break;
        case 4://直接启动转弯C
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 15, 180, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 16, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=5;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 5://C转弯判断
        if(stop_test2>500)
        {
            state_qu4=6;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        }   
        break;
        case 6://直走CD
        GreyCamera();
        Gan_out4=GanPID();
        queues=3;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=7;
            }
        break;
        case 7://直接启动转弯D
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 15, 200, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 13, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=8;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 8://D转弯判断
        if(stop_test2>500)
        {
            state_qu4=9;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        } 
        break;
        case 9://直走DB
        GreyCamera();
        Gan_out4=GanPID();
        queues=4;
        Set_Speed(0,25-Gan_out4);
        Set_Speed(1,25+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=10;
            }
        break;
        case 10://直接启动转弯B
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 17, 100, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 17, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=11;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 11://B转弯判断
        if(stop_test2>600)
            {
                state_qu4=12;
                state_cao=1;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                stop_test2=0;
            }
        break;
        case 12://直走BA
        GreyCamera();
        Gan_out4=GanPID();
        queues=4;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=13;
            }
        break;
        case 13:
            Set_Speed(0,0);
            Set_Speed(1,0);
            yuncao();
            // Emm_V5_Vel_Control(2, 1, 0, 120, 1);
            // xc_delay(10);
            // Emm_V5_Vel_Control(1, 1, 0, 120, 1);
            // xc_delay(10);
            // Emm_V5_Synchronous_motion(0);
            // xc_delay(10);
        break;
    }
}


void Quest4_3()
{
    switch(state_qu4)
    {
        case 14:
        Set_Speed(0,21);
        Set_Speed(1,21);
        queues=1;
        yuncao();
        stop_test2=0;
        state_qu4=15;
        break;
        case 15:
        if(stop_test2>300)
        {
            state_qu4=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        } 
        break;
        case 1://直接启动转弯A
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 19, 200, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 19, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=2;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 2://A转弯判断
        if(stop_test2>500)
        {
            state_qu4=3;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        }   
        break;
        case 3://直走AC
        GreyCamera();
        Gan_out4=GanPID();
        queues=2;
        Set_Speed(0,25-Gan_out4);
        Set_Speed(1,25+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=4;
            }
        break;
        case 4://直接启动转弯C
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 15, 180, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 16, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=5;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 5://C转弯判断
        if(stop_test2>500)
        {
            state_qu4=6;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        }   
        break;
        case 6://直走CD
        GreyCamera();
        Gan_out4=GanPID();
        queues=3;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=7;
            }
        break;
        case 7://直接启动转弯D
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 15, 200, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 13, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=8;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 8://D转弯判断
        if(stop_test2>500)
        {
            state_qu4=9;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        } 
        break;
        case 9://直走DB
        GreyCamera();
        Gan_out4=GanPID();
        queues=4;
        Set_Speed(0,25-Gan_out4);
        Set_Speed(1,25+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=10;
            }
        break;
        case 10://直接启动转弯B
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 17, 100, 800, 0, 1);
        // Emm_V5_Vel_Control(2, 1, 17, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=11;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 11://B转弯判断
        if(stop_test2>600)
            {
                state_qu4=12;
                state_cao=1;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                stop_test2=0;
            }
        break;
        case 12://直走BA
        GreyCamera();
        Gan_out4=GanPID();
        queues=4;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=13;
            }
        break;
        case 13:
            Set_Speed(0,0);
            Set_Speed(1,0);
            yuncao();
            // Emm_V5_Vel_Control(2, 1, 0, 120, 1);
            // xc_delay(10);
            // Emm_V5_Vel_Control(1, 1, 0, 120, 1);
            // xc_delay(10);
            // Emm_V5_Synchronous_motion(0);
            // xc_delay(10);
        break;
    }
}




void Yun_Start()
{
    switch (start)
    {   case 1:
        track1_out4=Track1PID(ZC_Y4);
        track2_out4=Track2PID(ZC_X4);
        if(track2_out4>0)
        {
            Emm_V5_Pos_Control(2, 1, 2, 1, 1, 0, 1);
            xc_delay(10);
        }
        else if(track2_out4<0)
        {
            Emm_V5_Pos_Control(2, 0, 2, 1, 1, 0, 1);
            xc_delay(10);
        }
        else
        {
            Emm_V5_Pos_Control(2, 0, 2, 1, 0, 0, 1);
        }
        if(track1_out4>0)
        {
            Emm_V5_Pos_Control(1, 1, 2, 1, 1, 0, 1);
            xc_delay(10);
        }
        else if(track1_out4<0)
        {
            Emm_V5_Pos_Control(1, 0, 2, 1, 1, 0, 1);
            xc_delay(10);
        }
        else
        {
            Emm_V5_Pos_Control(1, 0, 2, 1, 0, 0, 1);
        }
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        if((eye_x[0]-ZC_X4<1 && eye_x[0]-ZC_X4>-1) && (eye_y[0]-ZC_Y4<1 && eye_y[0]-ZC_Y4>-1))
        {
            DL_GPIO_setPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);  //亮灯，蜂鸣器程序
            start=2;
        }
        break;
        case 2:
        Emm_V5_Pos_Control(1, 1, 2, 1, 0, 0, 1);
        xc_delay(10);
        Emm_V5_Pos_Control(1, 0, 2, 1, 0, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        state_qu4=14;
        start=0;
        state_cao=1;
        xc_delay(1800);
        stop_test2=0;
        break;
    }
}

void Yuntai4()
{
    switch (state_ta4)
    {   case 7:
        track1_out4=Track1PID(ZC_Y4);
        track2_out4=Track2PID(ZC_X4);
        if(track2_out4>0)
        {
            Emm_V5_Pos_Control(2, 1, 2, 1, 1, 0, 1);
            xc_delay(10);
        }
        else if(track2_out4<0)
        {
            Emm_V5_Pos_Control(2, 0, 2, 1, 1, 0, 1);
            xc_delay(10);
        }
        else
        {
            Emm_V5_Pos_Control(2, 0, 2, 1, 0, 0, 1);
        }
        if(track1_out4>=0)
        {
            Emm_V5_Pos_Control(1, 1, 2, 1, 1, 0, 1);
            xc_delay(10);
        }
        else if(track1_out4<0)
        {
            Emm_V5_Pos_Control(1, 0, 2, 1, 1, 0, 1);
            xc_delay(10);
        }
        else
        {
            Emm_V5_Pos_Control(1, 0, 2, 1, 0, 0, 1);
        }
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        if((eye_x[0]-ZC_X4<1 && eye_x[0]-ZC_X4>-1) && (eye_y[0]-ZC_Y4<1 && eye_y[0]-ZC_Y4>-1))
        {
            DL_GPIO_setPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);  //亮灯，蜂鸣器程序
            state_ta4=8;
        }
        break;
        case 8:
        Emm_V5_Pos_Control(1, 1, 2, 1, 0, 0, 1);
        xc_delay(10);
        Emm_V5_Pos_Control(1, 0, 2, 1, 0, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(0);
        xc_delay(10);
        state_ta4=1;
        state_qu4=1;
        xc_delay(1800);
        stop_test2=0;
        break;


        //跑起来之后开始瞄准
        case 1://发送数据修正X
        track1_out4=Track1PID_move(ZC_Y4);
        if(queues==1)
            track2_out4=Track2PID_front(ZC_X4);
        else if(queues==2 || queues==4)
            track2_out4=Track2PID_side(ZC_X4);
        else if(queues==3)
            track2_out4=Track2PID_back(ZC_X4);

        if(queues==1)
        {
            if(track2_out4>0)
            {
                Emm_V5_Vel_Control(2, 1, track2_out4+Turn_fixed, 120, 1);
            }
            else if(track2_out4<0)
            {
                Emm_V5_Vel_Control(2, 0, -track2_out4+Turn_fixed, 120, 1);
            }
            else {
                Emm_V5_Vel_Control(2, 0, 0, 120, 1);
            }
        }
        else if(queues==2 || queues ==4)
        {
            if(track2_out4>0)
            {
                Emm_V5_Vel_Control(2, 1, track2_out4+Turn_fixed, 80, 1);
            }
            else if(track2_out4<0)
            {
                Emm_V5_Vel_Control(2, 0, -track2_out4+Turn_fixed, 80, 1);
            }
            else {
                Emm_V5_Vel_Control(2, 0, 0, 80, 1);
            }
        }
        else if (queues==3) 
        {
            if(track2_out4>0)
            {
                Emm_V5_Vel_Control(2, 1, track2_out4+Turn_fixed, 120, 1);
            }
            else if(track2_out4<0)
            {
                Emm_V5_Vel_Control(2, 0, -track2_out4+Turn_fixed, 120, 1);
            }
            else {
                Emm_V5_Vel_Control(2, 0, 0, 120, 1);
            }
        }
        state_ta4=2;
        stop_ta=0;
        break;
        case 2://中断延时10ms
        if(stop_ta>10)
            state_ta4=3;
        break;
        case 3://发送数据修正Y
        if(track1_out4>0)
        {
            Emm_V5_Pos_Control(1, 1, 1, 1, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 1, track1_out4, 1, 1);
        }
        else if(track1_out4<0)
        {
            Emm_V5_Pos_Control(1, 0, 1, 1, 1, 0, 1);
            // Emm_V5_Vel_Control(1, 0, track1_out4, 1, 1);
        }
        else
        {
            Emm_V5_Pos_Control(1, 0, 1, 1, 0, 0, 1);
        }
        state_ta4=4;
        stop_ta=0;
        break;
        case 4://中断延时10ms
        if(stop_ta>=10)
            state_ta4=5;
        break;
        case 5://双张大头开始运动
        Emm_V5_Synchronous_motion(0);
        state_ta4=6;
        stop_ta=0;
        break;
        case 6://中断延时10ms，回到开始
        if(stop_ta>=10)
        {
            state_ta4=1;
        }
            
        break;
    }
}

void Quest4_2()
{   
    GreyCamera();
    Gan_out4=GanPID3();
    switch(state_qu4)
    {
        case 1://开局直走加转弯
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        if(val_5 > 0)
        {
            Get_turn=1;
            state_qu4=2;
            stop_test2=0;
        }
        break;
        case 2://走AC
        queues=2;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        if(stop_test2>2500 && val_5>0)
        {
            InitialYaw=Gyro_Yaw;
            Get_turn=1;
            stop_test2=0;
            state_qu4=3;
        }
        break;
        case 3://走CD
        queues=3;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        if(stop_test2>2500 && val_5>0)
        {
            InitialYaw=Gyro_Yaw;
            Get_turn=1;
            stop_test2=0;
            state_qu4=4;
        }
        break;
        case 4://走DB
        queues=4;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        if(stop_test2>2500 && val_5>0)
        {
            InitialYaw=Gyro_Yaw;
            Get_turn=1;
            stop_test2=0;
            state_qu4=5;
        }
        break;
        case 5:
        queues=1;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        if(stop_test2>2500 && val_5>0)
        {
            stop_test2=0;
            state_qu4=0;
            Set_Speed(0,0);
            Set_Speed(1,0);
        }
        break;
        

    }
}

void Quest5_1()
{
    switch(state_qu4)
    {
        case 14:
        Set_Speed(0,21);
        Set_Speed(1,21);
        queues=1;
        yuncao();
        stop_test2=0;
        state_qu4=15;
        break;
        case 15:
        if(stop_test2>200)
        {
            state_qu4=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        } 
        break;
        case 1://直接启动转弯A
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 19, 200, 800, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=2;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 2://A转弯判断
        if(stop_test2>500)
        {
            state_qu4=3;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        }   
        break;
        case 3://直走AC
        GreyCamera();
        Gan_out4=GanPID();
        queues=2;
        Set_Speed(0,25-Gan_out4);
        Set_Speed(1,25+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=4;
            }
        break;
        case 4://直接启动转弯C
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 16, 180, 800, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=5;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 5://C转弯判断
        if(stop_test2>500)
        {
            state_qu4=6;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        }   
        break;
        case 6://直走CD
        GreyCamera();
        Gan_out4=GanPID();
        queues=3;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=7;
            }
        break;
        case 7://直接启动转弯D
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 16, 200, 800, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=8;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 8://D转弯判断
        if(stop_test2>500)
        {
            state_qu4=9;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        } 
        break;
        case 9://直走DB
        GreyCamera();
        Gan_out4=GanPID();
        queues=4;
        Set_Speed(0,25-Gan_out4);
        Set_Speed(1,25+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=10;
            }
        break;
        case 10://直接启动转弯B
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 17, 100, 800, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=11;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 11://B转弯判断
        if(stop_test2>600)
            {
                state_qu4=12;
                state_cao=1;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                stop_test2=0;
            }
        break;
        case 12://直走BA
        GreyCamera();
        Gan_out4=GanPID();
        queues=4;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        yuncao();
        
        if(val_5>0 && stop_test2>2000)
            {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=1;
                the_second++;
                state_cao=1;

            }
        if(the_second==2)
            state_qu4=16;
        break;
        case 16:
        Set_Speed(0,0);
        Set_Speed(1,0);
        yuncao();
        break;
    }
}

void Quest5_2()
{
    switch(state_qu4)
    {
        case 14:
        Set_Speed(0,21);
        Set_Speed(1,21);
        queues=1;
        yuncao();
        stop_test2=0;
        state_qu4=15;
        break;
        case 15:
        if(stop_test2>200)
        {
            state_qu4=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        } 
        break;
        case 1://直接启动转弯A
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 19, 200, 800, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=2;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 2://A转弯判断
        if(stop_test2>450)
        {
            state_qu4=3;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        }   
        break;
        case 3://直走AC
        GreyCamera();
        Gan_out4=GanPID();
        queues=2;
        Set_Speed(0,25-Gan_out4);
        Set_Speed(1,25+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                InitialYaw=Gyro_Yaw;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=4;
            }
        break;
        case 4://直接启动转弯C
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 16, 180, 800, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=5;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 5://C转弯判断
        if(stop_test2>450)
        {
            state_qu4=6;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        }   
        break;
        case 6://直走CD
        GreyCamera();
        Gan_out4=GanPID();
        queues=3;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=7;
            }
        break;
        case 7://直接启动转弯D
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 16, 200, 800, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=8;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 8://D转弯判断
        if(stop_test2>450)
        {
            state_qu4=9;
            state_cao=1;
            Set_Speed(0,0);
            Set_Speed(1,0);
            stop_test2=0;
        } 
        break;
        case 9://直走DB
        GreyCamera();
        Gan_out4=GanPID();
        queues=4;
        Set_Speed(0,25-Gan_out4);
        Set_Speed(1,25+Gan_out4);
        yuncao();
        if(val_5>0 && stop_test2>2000)
            {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=10;
            }
        break;
        case 10://直接启动转弯B
        Set_Speed(0,-5);
        Set_Speed(1,30);
        Emm_V5_Pos_Control(2, 1, 17, 100, 800, 0, 1);
        xc_delay(10);
        Emm_V5_Synchronous_motion(2);
        xc_delay(10);
        state_qu4=11;
        stop_test2=0;
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
        break;
        case 11://B转弯判断
        if(stop_test2>550)
            {
                state_qu4=12;
                state_cao=1;
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                stop_test2=0;
            }
        break;
        case 12://直走BA
        GreyCamera();
        Gan_out4=GanPID();
        queues=4;
        Set_Speed(0,21-Gan_out4);
        Set_Speed(1,21+Gan_out4);
        yuncao();
        
        if(val_5>0 && stop_test2>2000)
            {
                Set_Speed(0, 0);
                Set_Speed(1, 0);
                state_qu4=1;
                the_second++;
                state_cao=1;

            }
        if(the_second==2)
            state_qu4=16;
        break;
        case 16:
        Set_Speed(0,0);
        Set_Speed(1,0);
        yuncao();
        break;
    }
}
