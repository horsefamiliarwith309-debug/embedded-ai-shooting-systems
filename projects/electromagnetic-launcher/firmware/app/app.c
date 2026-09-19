#include "tim.h"
#include "usart.h"
#include "motor.h"
#include "encode.h"
#include "gyro.h"
#include "gray.h"
#include "gray_control.h"
#include "do_scream.h"
#include "eyes.h"
#include "blind.h"
#include "luna.h"
#include "electric.h"
#include <stdio.h>
#include <string.h>
#include "First.h"
#include "Second.h"
#include "Third.h"
#include "Fourth.h"
#include "Fifth.h"
#include "stm.h"
#include "maix.h"

extern volatile uint8_t gRxPacket1[UART_PACKET_SIZE];
extern volatile uint8_t gRxPacket2[UART_PACKET_SIZE];
extern volatile uint8_t gRxPacket3[UART_PACKET_SIZE];
extern volatile uint8_t gRxPacket4[UART_PACKET_SIZE];
extern volatile uint8_t gRxPacket5[UART_PACKET_SIZE];

int8_t start=0;

void app(void)
{
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL); // 启动编码器计数
    HAL_UART_Receive_IT(&huart4,  (uint8_t *)gRxPacket1, UART_PACKET_SIZE); // 启动UART4非阻塞接收
    HAL_UART_Receive_IT(&huart2,  (uint8_t *)gRxPacket2, UART_PACKET_SIZE); // 启动UART2非阻塞接收
    HAL_UART_Receive_IT(&huart3,  (uint8_t *)gRxPacket3, UART_PACKET_SIZE); // 启动UART3非阻塞接收
    HAL_UART_Receive_IT(&huart6,  (uint8_t *)gRxPacket4, UART_PACKET_SIZE); // 启动UART6非阻塞接收
    HAL_UART_Receive_IT(&huart1,  (uint8_t *)gRxPacket5, UART_PACKET_SIZE); // 启动UART1非阻塞接收
    
    start = 1;
    Eye_Value1 = 0;
    Eye_Value2 = 0;
    flag0_1 = 0;
    
    
    
//    KP1=20;
//    KD1=1;
//    Position1=30;

    
    //发送数据，等待转动
    
    
    while(1)
    {
        
        Shoot_read();
//        Stm_SendFrame();
//        HAL_Delay(2000);//延时
        if(flag_shoot==6)
        {
            Electric1_On;
            flag_shoot=0;
        }

        
        if(flag0_1==1)
        {
            First();

        }
        
        if(flag0_1==2)
        {
            Second();
            
        }
        
        if(flag0_1==3)
        {
            Third();
            
        }
        
        if(flag0_1==4)
        {
            Fourth();
        }
        
        if(flag0_1==5)
        {
            Fifth();
        }
        

    }
}















//void Easy_LED(void)
//{
//    uint8_t receivedData;
//    while (1)
//    {
//        HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
//        if (receivedData == '1') {
//        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);  // 点亮LED
//        }
//         else if (receivedData == '0'){
//        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET); // 熄灭LED
//        }
//    }
//}



/*
extern void app(void);
app();
*/