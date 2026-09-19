#include "stm32f4xx_hal.h"
#include "gyro.h"
#include "motor.h"
#include "turning.h"
#include "encode.h"
#include <math.h>

void turn_left()
{
    float initial_yaw = RelativeYaw;
    float target_yaw = initial_yaw - 70.0f;  // 左转 90 度

    Set_Speed(0, 20);
    Set_Speed(1, -20); 

    while (RelativeYaw > target_yaw)
    {   
        read_gyro();
        read_encode ();
    }

    Set_Speed(0, 0);
    Set_Speed(1, 0);
}

void turn_right()
{
    float initial_yaw = RelativeYaw;
    float target_yaw = initial_yaw + 70.0f;  // 右转 90 度

    Set_Speed(0, -20);
    Set_Speed(1, 20);

    while (RelativeYaw < target_yaw)
    {
        read_gyro(); 
        read_encode ();
    }

    Set_Speed(0, 0);
    Set_Speed(1, 0);
}

void turn_around_l()
{
    float initial_yaw = RelativeYaw;  // 记录初始角度
    float target_yaw_difference = 160.0f;  // 定义需要旋转的角度差

    Set_Speed(0, 20);
    Set_Speed(1, -20);

    while (fabs(RelativeYaw - initial_yaw) < target_yaw_difference)
    {
        read_gyro();
        read_encode();
    }

    // 停止电机
    Set_Speed(0, 0);
    Set_Speed(1, 0);
}

void turn_around_r()
{
    float initial_yaw = RelativeYaw;  // 记录初始角度
    float target_yaw_difference = 160.0f;  // 定义需要旋转的角度差

    Set_Speed(0, -20);
    Set_Speed(1, 20);

    while (fabs(RelativeYaw - initial_yaw) < target_yaw_difference)
    {
        read_gyro();
        read_encode();
    }

    // 停止电机
    Set_Speed(0, 0);
    Set_Speed(1, 0);
}

void turn_left_new()
{

    Set_Speed(0, 20);
    Set_Speed(1, -20);

    while (RelativeYaw>= -150 && RelativeYaw<= 150)
    {
        read_gyro(); 
        read_encode ();
    }

    Set_Speed(0, 0);
    Set_Speed(1, 0);
}

void turn_left_news()
{

    Set_Speed(0, 20);
    Set_Speed(1, -20);

    while (RelativeYaw < 70 || RelativeYaw > 110)
    {
        read_gyro(); 
        read_encode ();
    }

    Set_Speed(0, 0);
    Set_Speed(1, 0);
}

void turn_left_3()
{
    float initial_yaw = RelativeYaw;
    float target_yaw = initial_yaw - 50.0f;  // 左转 90 度

    Set_Speed(0, 20);
    Set_Speed(1, -20); 

    while (RelativeYaw > target_yaw)
    {   
        read_gyro();
        read_encode ();
    }

    Set_Speed(0, 0);
    Set_Speed(1, 0);
}

void turn_right_3()
{
    float initial_yaw = RelativeYaw;
    float target_yaw = initial_yaw + 50.0f;  // 右转 90 度

    Set_Speed(0, -20);
    Set_Speed(1, 20);

    while (RelativeYaw < target_yaw)
    {
        read_gyro(); 
        read_encode ();
    }

    Set_Speed(0, 0);
    Set_Speed(1, 0);
}

void turn_right_new()
{

    Set_Speed(0, -20);
    Set_Speed(1, 20);

    while (RelativeYaw>= -160 && RelativeYaw<= 160)
    {
        read_gyro(); 
        read_encode ();
    }

    Set_Speed(0, 0);
    Set_Speed(1, 0);
}

void turn_right_news()
{

    Set_Speed(0, -20);
    Set_Speed(1, 20);

    while (RelativeYaw < -110 || RelativeYaw > -70)
    {
        read_gyro(); 
        read_encode ();
    }

    Set_Speed(0, 0);
    Set_Speed(1, 0);
}

void turn_around_f()
{
    Set_Speed(0, -20);
    Set_Speed(1, 20);

    while (RelativeYaw < -20 || RelativeYaw > 20)
    {
        read_gyro(); 
        read_encode ();
    }

    Set_Speed(0, 0);
    Set_Speed(1, 0);
}

void turn_around_b()
{
    Set_Speed(0, -20);
    Set_Speed(1, 20);

    while (RelativeYaw>= -160 && RelativeYaw<= 160)
    {
        read_gyro(); 
        read_encode ();
    }

    Set_Speed(0, 0);
    Set_Speed(1, 0);
}