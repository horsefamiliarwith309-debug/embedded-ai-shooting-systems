#include "ti_msp_dl_config.h"
#include "track.h"
#include "eyes1.h"

float Kp_1=0.23f,Ki_1=0.0f;
float Err_1=0,Err_1_sum=0;

float Kp_2=0.23f,Ki_2=0.0f;
float Err_2=0,Err_2_sum=0;

float Kp_3=0.30f,Ki_3=0.0f,Kd_3=0.00f;
float Err_3,Err_3_sum=0.0f,Err_3_D;

float Kp_4=0.5*0.6,Ki_4=0.3/250,Kd_4=-1.0;//0.5
float Err_4=0,Err_4_sum=0.0f,Err_4_D;

float Kp_fro=0.3,Ki_fro=0.3/250,Kd_fro=-1.5;//0.5
float Err_fro,Err_fro_sum=0.0f,Err_fro_D;

float Kp_side=0.3,Ki_side=0.3/250,Kd_side=-1.5;//0.5
float Err_side,Err_side_sum=0.0f,Err_side_D;

float Kp_back=0.3,Ki_back=0.3/250,Kd_back=-1.0;//0.5
float Err_back,Err_back_sum=0.0f,Err_back_D;

float eye_x_last,eye_y_last;



#define ERR_1_MAX 300
#define ERR_2_MAX 300
#define MAXAA 1700
//摄像头跟踪绿点
float Track1PID(int16_t PosY)
{
	float temp;
    if(eye_y[0]>=0 && eye_y[0]<=180)
    {
        Err_1=PosY-eye_y[0];
	    Err_1_sum+=Err_1;
    }
    else
    {
        Err_1_sum=0;
        Err_1=0;
    }
	Err_1_sum=Err_1_sum>ERR_1_MAX?ERR_1_MAX:(Err_1_sum<(-ERR_1_MAX)?(-ERR_1_MAX):Err_1_sum);//积分限幅(-100~100)
	temp=Kp_1*Err_1+Ki_1*Err_1_sum;
    temp=temp>15?15:(temp<(-15)?(-15):temp);//速度限幅
	return temp;
}
float Track2PID(int16_t PosX)
{
	float temp;
    if(eye_x[0]>=0 && eye_x[0]<=240)
    {
        Err_2=PosX-eye_x[0];
	    Err_2_sum+=Err_2;
    }
    else
    {
        Err_2_sum=0;
        Err_2=0;
    }
	Err_2_sum=Err_2_sum>ERR_2_MAX?ERR_2_MAX:(Err_2_sum<(-ERR_2_MAX)?(-ERR_2_MAX):Err_2_sum);//积分限幅(-100~100)
	temp=Kp_2*Err_2+Ki_2*Err_2_sum;
    temp=temp>15?15:(temp<(-15)?(-15):temp);//速度限幅
	return temp;
}


float Track1PID_move(int16_t PosY)
{
	float temp;

    if(eye_y[0]>=0 && eye_y[0]<=180)
    {
        Err_3=PosY-eye_y[0];
	    Err_3_sum+=Err_3;
        Err_3_D=eye_y[0]-eye_y_last;
    }
    else
    {
        Err_3_sum=0;
        Err_3=0;
        Err_3_D=0;
    }
    eye_y_last=eye_y[0];

	Err_3_sum=Err_3_sum>ERR_1_MAX?ERR_1_MAX:(Err_3_sum<(-ERR_1_MAX)?(-ERR_1_MAX):Err_3_sum);//积分限幅(-100~100)
	temp=Kp_3*Err_3+Ki_3*Err_3_sum+Kd_3*Err_3_D;
    temp=temp>40?40:(temp<(-40)?(-40):temp);//速度限幅
	return temp;
}


float Track2PID_front(int16_t PosX)
{
	float temp;
    if(eye_x[0]>=0 && eye_x[0]<=240)
    {
        Err_fro=PosX-eye_x[0];
	    Err_fro_sum+=Err_fro;
        Err_fro_D=eye_x[0]-eye_x_last;
    }
    else
    {
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
    }
    eye_x_last=eye_x[0];
	Err_fro_sum=Err_fro_sum>MAXAA?MAXAA:(Err_fro_sum<(-MAXAA)?(-MAXAA):Err_fro_sum);//积分限幅(-100~100)
	temp=Kp_fro*Err_fro+Ki_fro*Err_fro_sum+Kd_fro*Err_fro_D;
    temp=temp>35?35:(temp<(-35)?(-35):temp);//速度限幅
	return temp;
}



float Track2PID_side(int16_t PosX)//走两边的PID
{
	float temp;
    if(eye_x[0]>=0 && eye_x[0]<=240)
    {
        Err_fro=PosX-eye_x[0];
	    Err_fro_sum+=Err_fro;
        Err_fro_D=eye_x[0]-eye_x_last;
    }
    else
    {
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
    }
    eye_x_last=eye_x[0];
	Err_fro_sum=Err_fro_sum>MAXAA?MAXAA:(Err_fro_sum<(-MAXAA)?(-MAXAA):Err_fro_sum);//积分限幅(-100~100)
	temp=Kp_side*Err_fro+Ki_side*Err_fro_sum+Kd_side*Err_fro_D;
    temp=temp>10?10:(temp<(-10)?(-10):temp);//速度限幅
	return temp;
}

float Track2PID_back(int16_t PosX)
{
	float temp;
    if(eye_x[0]>=0 && eye_x[0]<=240)
    {
        Err_fro=PosX-eye_x[0];
	    Err_fro_sum+=Err_fro;
        Err_fro_D=eye_x[0]-eye_x_last;
    }
    else
    {
        Err_fro_sum=0;
        Err_fro=0;
        Err_fro_D=0;
    }
    eye_x_last=eye_x[0];
	Err_fro_sum=Err_fro_sum>MAXAA?MAXAA:(Err_fro_sum<(-MAXAA)?(-MAXAA):Err_fro_sum);//积分限幅(-100~100)
	temp=Kp_back*Err_fro+Ki_back*Err_fro_sum+Kd_back*Err_fro_D;
    temp=temp>15?15:(temp<(-15)?(-15):temp);//速度限幅
	return temp;
}