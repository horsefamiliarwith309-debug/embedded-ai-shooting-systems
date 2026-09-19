#include "gray.h"

// 声明灰度传感器读取值的变量
volatile uint32_t val_1 = 0;
volatile uint32_t val_2 = 0;
volatile uint32_t val_3 = 0;
volatile uint32_t val_4 = 0;
volatile uint32_t val_5 = 0;

// 灰度传感器处理函数实现
void GreyCamera(void)
{
    val_1 = DL_GPIO_readPins(GPIO_Light_PORT, GPIO_Light_PIN_Light_1_PIN);  // 读取灰度1，1为黑线
    val_2 = DL_GPIO_readPins(GPIO_Light_PORT, GPIO_Light_PIN_Light_2_PIN);  // 读取灰度2，1为黑线
    val_3 = DL_GPIO_readPins(GPIO_Light_PORT, GPIO_Light_PIN_Light_3_PIN);  // 读取灰度3，1为黑线
    val_4 = DL_GPIO_readPins(GPIO_Light_PORT, GPIO_Light_PIN_Light_4_PIN);  // 读取灰度4，1为黑线
    val_5 = DL_GPIO_readPins(GPIO_Light_PORT, GPIO_Light_PIN_Light_5_PIN);  // 读取灰度5，1为黑线
}