#include "ti_msp_dl_config.h"
#include "xc_systick.h"

#define SYSTEM_CLOCK_FREQ 32000000

// 中断次数，49天溢出 一定要加volatile关键字
volatile unsigned int jiffies = 0;
// 前台任务标志位
unsigned int time=0;
volatile unsigned int stop_test2=0;
volatile unsigned int the_time=0;
volatile unsigned int stop_ta=0;
// 滴答定时器中断服务函数 1ms一次
void SysTick_Handler(void)
{
    jiffies++; // 每次滴答定时器中断，jiffies加一
    time++;
    stop_test2++;
    stop_ta++;
    // 每200ms触发一次的标志位
    if (jiffies % 200 == 0) {
        the_time++; // LED1_FLAG递增，用于指示500ms间隔的事件
    }

    // 每1000ms触发一次的标志位
    // if (jiffies % 1000 == 0) {
    //     UART0_JIFFIES_FLAG++; // UART0_JIFFIES_FLAG递增，用于指示1000ms间隔的事件
    // }
}

// 延时函数，以毫秒为单位
void xc_delay(unsigned int ms)
{
    unsigned int waitfor;
    waitfor = jiffies + ms; // 计算延时结束的时间点

    // 等待jiffies达到waitfor
    while (waitfor > jiffies);
}

// 微秒级延时函数
void yc_delay(uint32_t us)
{
    // 计算1us对应的SysTick周期数
    uint32_t ticks_per_us = SYSTEM_CLOCK_FREQ / 1000000;
    
    // 计算需要延时的总周期数
    uint32_t total_ticks = us * ticks_per_us;
    
    // 禁用中断以确保精确计时
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    
    // 重置SysTick计数器
    SysTick->VAL = 0;
    
    // 启动SysTick（使用处理器时钟，不产生中断）
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    
    // 精确等待
    while(total_ticks > SysTick->VAL)
    {
        // 空循环等待
    }
    // 停止SysTick
    SysTick->CTRL = 0;
    // 恢复中断状态
    __set_PRIMASK(primask);
}