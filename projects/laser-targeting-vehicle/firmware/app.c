#include "ti_msp_dl_config.h"
#include "scream.h"
#include "gyro.h"
#include "ti/driverlib/dl_timerg.h"  // 包含定时器库文件
#include "motor.h"
#include "xc_systick.h"
#include "encoder.h"
#include "luna.h"
#include "yc_datou_m0.h"
#include "DT_Position.h"
#include "duoji.h"
#include "GrayPID.h"
#include "eyes.h"
#include "eyes1.h"
#include "eyes_uart.h"
#include "question1.h"
#include "question0.h"
#include "question2.h"
#include "question3.h"
#include "question4.h"
#include "gray.h"

// 定义实时位置全局变量
float Motor_Cur_Pos = 0.0f;
float Gray_out=0.0f;
float Duty_out=0.0f;
uint8_t flags=0;
uint8_t flags2=0;
uint8_t state=1;
uint8_t wycfw=0;

int main(void)
{

    SYSCFG_DL_init();  // 初始化系统配置
    SYSCFG_DL_UART_0_init();  // 初始化 UART0
    SYSCFG_DL_UART_1_init();  // 初始化 UART1
    SYSCFG_DL_UART_2_init(); // 初始化 UART2
    SYSCFG_DL_UART_3_init(); // 初始化 UART3
    SYSCFG_DL_GPIO_init();  // 初始化 GPIO
    SYSCFG_DL_PWM_MOTOR_init(); // 初始化 PWM

    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);  // 启用 UART0 中断
    NVIC_EnableIRQ(UART_1_INST_INT_IRQN);  // 启用 UART1 中断
    NVIC_EnableIRQ(UART_2_INST_INT_IRQN);  // 启用 UART2 中断
    NVIC_EnableIRQ(UART_3_INST_INT_IRQN);  // 启用 UART3 中断

    // 启用GPIOA和GPIOB中断
    NVIC_EnableIRQ(GPIO_MULTIPLE_GPIOA_INT_IRQN);
    NVIC_EnableIRQ(GPIO_Encoder_GPIOB_INT_IRQN);

    DL_TimerG_startCounter(PWM_MOTOR_INST); // 启动 PWM电机 计数器
    DL_TimerG_startCounter(PWM_SERVO_INST); // 启动 PWM舵机 计数`器


    // 初始化定时器
    SYSCFG_DL_TIMER_0_init();
    
    // Emm_V5_Pos_Control(1, 0, 200, 0, 400, 1, 1); // 多机同步标志位置1
    // xc_delay(10);
    // Emm_V5_Pos_Control(2, 0, 100, 0, 300, 1, 1); // 多机同步标志位置1
    // xc_delay(10);
    // Emm_V5_Synchronous_motion(0); 								 // 广播地址0触发
    // xc_delay(10);

    // DT_Position_Request(1);
    // xc_delay(10);
    // if (DT_Position_Available()) {
    //     Motor_Cur_Pos = DT_Position_GetAngle();  // 获取电机角度
    //  }

    Emm_V5_Vel_Control(1, 1, 0, 1, 1);
    xc_delay(10);
    Emm_V5_Vel_Control(2, 1, 0, 1, 1);
    xc_delay(10);
    Emm_V5_Synchronous_motion(0);
    xc_delay(10);
    DL_GPIO_clearPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);  //关灯，蜂鸣器程序

    while (1) //0是左轮，1是右轮
    {
        // DL_GPIO_setPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);  //亮灯，蜂鸣器程序
        // xc_delay(5000);
        // DL_GPIO_clearPins(GPIO_Jidianqi_PORT, GPIO_Jidianqi_GPIO_Ji_PIN);  //关灯，蜂鸣器程序
        // xc_delay(1000);
        GreyCamera();
        if(command_1==1)
        {
            if(command_2!=0)
            {
                if(!wycfw)
                {
                    stop_test2=0;
                    wycfw=1;
                }
                Quest0();
                
            }
                
        }
        else if(command_1==2)
        {
            if(command_2==1)
                Quest2();
            else if(command_2==2)
                Quest2_1();
        }
        else if(command_1==3)
        {
            if(command_2==1)//左转
                Quest3_1();
            else if(command_2==2)//右转
                Quest3_2();
            else if(command_2==3)//左转大阈值
                Quest3_1b();
            else if(command_2==4)//右转大阈值
                Quest3_2b();       
            
        }
        else if(command_1==4)
        {
            if(command_2==1)
            {
                Yun_Start();
                Quest4();
            }
            else if(command_2==2)
            {
                Yun_Start();
                Quest4_1();
            }
            else if(command_2==3)
            {
                Yun_Start();
                Quest4_3();
            }
            else if(command_2==4)
            {
                Yun_Start();
                Quest4_4();
            }
                
        }
        else if(command_1==5)
        {
            if(command_2==1)
            {
                Yun_Start();
                Quest5_2();
            }
            if(command_2==2)
            {
                Yun_Start();
                Quest5_1();
            }    
            
        }
        else if(command_1==6)
        {
            Round_start();
            Round();
            // Rou_Start();
            // Quest6_2();
        }
        else if(command_1 == 7)
        {
            Emm_V5_Pos_Control(1, 1, 100, 0, 150, 1, 1); // 多机同步标志位置1
            xc_delay(10);
            Emm_V5_Synchronous_motion(1);
            xc_delay(10);
            if(command_2==3)//左转大阈值
                Quest3_1b();
            else if(command_2==4)//右转大阈值
                Quest3_2b();
        }
        else if(command_1 == 8)
        {
            Emm_V5_Pos_Control(1, 0, 100, 0, 150, 1, 1); // 多机同步标志位置1
            xc_delay(10);
            Emm_V5_Synchronous_motion(1);
            xc_delay(10);
            if(command_2==3)//左转大阈值
                Quest3_1b();
            else if(command_2==4)//右转大阈值
                Quest3_2b();
        }



        // Set_Speed(0,20);

        // Set_Speed(0, 40);
        // Set_Speed(1, 40);
        // read_Gray();
        // if(!flags)
        // {
        //     xc_delay(30000);
        //     flags=1;
        //     commanddd=0;
        // }
        // test3();
        // if(gray_1 || gray_2|| gray_3|| gray_4|| gray_5|| gray_6|| gray_7|| gray_8|| gray_9|| gray_10|| gray_11|| gray_12|| gray_13|| gray_14|| gray_15|| gray_16)
        // {
        //     flags=1;
        // }
        // if(flags)
        // {
        //     Gray_out=GrayPID();
        //     Set_Speed(0,20-Gray_out);
        //     Set_Speed(1,20+Gray_out);
        // }
        // else {
        //     Set_Speed(0,0);
        //     Set_Speed(1,0);
        // }
        
    }
}


// UART0中断处理程序
void UART_0_INST_IRQHandler(void)
{
    uint32_t intStatus = DL_UART_Main_getPendingInterrupt(UART_0_INST); // 获取 UART 中断状态

    // 检查是否接收到数据
    if (intStatus & DL_UART_MAIN_IIDX_RX)
    {
        uint8_t res = DL_UART_Main_receiveData(UART_0_INST); // 接收 UART 数据
        processSCREAMData(res); // 处理接收到的数据
    }
}


// UART1中断处理程序
void UART_1_INST_IRQHandler(void)
{
    uint32_t intStatus = DL_UART_Main_getPendingInterrupt(UART_1_INST); // 获取 UART 中断状态

    // 检查是否接收到数据
    if (intStatus & DL_UART_MAIN_IIDX_RX)
    {
        uint8_t res = DL_UART_Main_receiveData(UART_1_INST); // 接收 UART 数据
        eyes1_process_data(res);
        // Luna_ProcessData(res); // 处理接收到的数据
    }
}


// UART2 中断处理函数
void UART_2_INST_IRQHandler(void)
{
    uint32_t intStatus = DL_UART_Main_getPendingInterrupt(UART_2_INST); // 获取 UART 中断状态

    // 检查是否接收到数据
    if (intStatus & DL_UART_MAIN_IIDX_RX)
    {
        uint8_t res = DL_UART_Main_receiveData(UART_2_INST); // 接收 UART 数据
        // DT_Position_UART_RX_Callback(res);  // 回调处理
        gyro_process_data(res); // 处理接收到的数据
        if (gyro_data_received)
        {
            gyro_data_received = 0;
            RelativeYaw = yaw_error(InitialYaw, Gyro_Yaw);  // 使用偏航角
        }
    }
}


// UART3 中断处理函数
void UART_3_INST_IRQHandler(void)
{
    uint32_t intStatus = DL_UART_Main_getPendingInterrupt(UART_3_INST); // 获取 UART 中断状态

    // 检查是否接收到数据
    if (intStatus & DL_UART_MAIN_IIDX_RX)
    {
        uint8_t res = DL_UART_Main_receiveData(UART_3_INST); // 接收 UART 数据
        // eyes_process_data(res); // 处理接收到的数据
        DT_Position_UART_RX_Callback(res);  // 回调处理
    }
}
