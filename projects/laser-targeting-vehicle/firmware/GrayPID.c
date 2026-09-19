#include "gyro.h"
#include "ti_msp_dl_config.h"
#include "eyes.h"
#include "gray.h"
volatile uint32_t gray_1 = 0;
volatile uint32_t gray_2 = 0;
volatile uint32_t gray_3 = 0;
volatile uint32_t gray_4 = 0;
volatile uint32_t gray_5 = 0;
volatile uint32_t gray_6 = 0;
volatile uint32_t gray_7 = 0;
volatile uint32_t gray_8 = 0;
volatile uint32_t gray_9 = 0;
volatile uint32_t gray_10 = 0;
volatile uint32_t gray_11 = 0;
volatile uint32_t gray_12 = 0;
volatile uint32_t gray_13 = 0;
volatile uint32_t gray_14 = 0;
volatile uint32_t gray_15 = 0;
volatile uint32_t gray_16 = 0;


float Kp_gra=0.9f,Ki_gra=0.02f;
float Err_gra=0,Err_gra_sum=0;

float Kp_wei=0.9f,Ki_wei=0.02f;
float Err_wei=0,Err_wei_sum=0;

float Kp_gan=0.9f,Ki_gan=0.03f;
float Err_gan=0,Err_gan_sum=0;

float Kp_du=0.004f,Ki_du=0.0006f;
float Err_du=0,Err_du_sum=0;

float Kp_tu=3;

int i;
int ganweidehuidu[8];

#define GAN_SUM_MAX 50
#define GRA_SUM_MAX 55
#define DU_SUM_MAX 20



float TurnPID(float Point)
{
	float temp;
    temp=Kp_tu*(RelativeYaw-Point);
    temp=temp>10?10:(temp<(-10)?(-10):temp);//速度限幅
	return temp;
}

float GanPID()
{
    float temp;
	
    if(val_1>0)
	{
		Err_wei=5;
	}
    else if(val_4>0)
	{
		Err_wei=-5;
	}
    else if(val_2>0)
	{
		Err_wei=2;
	}
    else if(val_3>0)
	{
		Err_wei=-2;
	}
    
    if(!val_1 && !val_2 && !val_3 && !val_4)
    {
        Err_wei=0;
    }

	Err_wei_sum+=Err_wei;
	Err_wei_sum=Err_wei_sum>GRA_SUM_MAX?GRA_SUM_MAX:(Err_wei_sum<(-GRA_SUM_MAX)?(-GRA_SUM_MAX):Err_wei_sum);//积分限幅(-100~100)
	temp=Kp_wei*Err_wei+Ki_wei*Err_wei_sum;
    temp=temp>20?20:(temp<(-20)?(-20):temp);//速度限幅

	return temp;
}

float GanPID2()
{
    float temp;
	
    if(val_5>0)
    {
        Err_wei=41;
    }
    else if(val_1>0)
	{
		Err_wei=5;
	}
    else if(val_3>0)
	{
		Err_wei=-5;
	}
    else if(val_2>0)
	{
		Err_wei=1;
	}
    else if(val_4>0)
	{
		Err_wei=-1;
	}
    
    // if(!val_1 && !val_2 && !val_3 && !val_4)
    // {
    //     Err_wei=0;
    // }

	Err_wei_sum+=Err_wei;
	Err_wei_sum=Err_wei_sum>GRA_SUM_MAX?GRA_SUM_MAX:(Err_wei_sum<(-GRA_SUM_MAX)?(-GRA_SUM_MAX):Err_wei_sum);//积分限幅(-100~100)
	temp=Kp_wei*Err_wei+Ki_wei*Err_wei_sum;
    temp=temp>35?35:(temp<(-35)?(-35):temp);//速度限幅

	return temp;
}

float GanPID3()
{
    float temp;
	
    if(val_5>0)
    {
        Err_gan=41;
    }
    else if(val_1>0)
	{
		Err_gan=5;
	}
    else if(val_3>0)
	{
		Err_gan=-5;
	}
    else if(val_2>0)
	{
		Err_gan=1;
	}
    else if(val_4>0)
	{
		Err_gan=-1;
	}
    
    // if(!val_1 && !val_2 && !val_3 && !val_4)
    // {
    //     Err_gan=0;
    // }

	Err_gan_sum+=Err_gan;
	Err_gan_sum=Err_gan_sum>GAN_SUM_MAX?GAN_SUM_MAX:(Err_gan_sum<(-GAN_SUM_MAX)?(-GAN_SUM_MAX):Err_gan_sum);//积分限幅(-100~100)
	temp=Kp_gan*Err_gan+Ki_gan*Err_gan_sum;
    temp=temp>31?31:(temp<(-31)?(-31):temp);//速度限幅

	return temp;
}


