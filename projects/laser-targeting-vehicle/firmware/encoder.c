#include "encoder.h"
#include "ti/driverlib/dl_flashctl.h"
#include "ti_msp_dl_config.h"  // 包含系统配置库文件
#include "ti/driverlib/dl_timerg.h"  // 包含定时器库文件

// 编码器计数变量
volatile int32_t Left_Count = 0;     // 左轮编码器计数
volatile int32_t Right_Count = 0;    // 右轮编码器计数

// =====================================================================
// 函数名称：GROUP1_IRQHandler
// 功能描述：编码器中断处理函数
// 输入参数：无
// 输出结果：无
// =====================================================================
// 中断处理函数
void GROUP1_IRQHandler(void)
{
    // 获取GPIOA中断状态
    uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA, 
                        GPIO_Encoder_PIN_Left_A_PIN);
    
    // 获取GPIOB中断状态
    uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(GPIOB, 
                        GPIO_Encoder_PIN_Right_A_PIN);

    // 处理左前编码器A相中断
    if (gpioA & GPIO_Encoder_PIN_Left_A_PIN) 
    {
        // 读取左前编码器B相信号，判断计数增减
        if (DL_GPIO_readPins(GPIO_Encoder_PIN_Left_B_PORT, GPIO_Encoder_PIN_Left_B_PIN))
            Left_Count++;  // B相高电平，计数减1
        else 
            Left_Count--;  // B相低电平，计数加1
        
        // 清除左前编码器A相中断状态
        DL_GPIO_clearInterruptStatus(GPIO_Encoder_PIN_Left_A_PORT, GPIO_Encoder_PIN_Left_A_PIN);
    }

    // 处理右前编码器A相中断
    if (gpioB & GPIO_Encoder_PIN_Right_A_PIN) 
    {
        // 读取右前编码器B相信号，判断计数增减
        if (DL_GPIO_readPins(GPIO_Encoder_PIN_Right_B_PORT, GPIO_Encoder_PIN_Right_B_PIN))
            Right_Count--;  // B相高电平，计数减1(电机是反着装的)
        else
            Right_Count++;  // B相低电平，计数加1(电机是反着装的)
        
        // 清除右前编码器A相中断状态
        DL_GPIO_clearInterruptStatus(GPIO_Encoder_PIN_Right_A_PORT, GPIO_Encoder_PIN_Right_A_PIN);
    }

    // 处理左前编码器B相中断
    if (gpioB & GPIO_Encoder_PIN_Left_B_PIN) 
    {
        // 读取左前编码器A相信号，判断计数增减
        if (DL_GPIO_readPins(GPIO_Encoder_PIN_Left_A_PORT, GPIO_Encoder_PIN_Left_A_PIN))
            Left_Count--;  // A相高电平，计数加1
        else
            Left_Count++;  // A相低电平，计数减1
        
        // 清除左前编码器B相中断状态
        DL_GPIO_clearInterruptStatus(GPIO_Encoder_PIN_Left_B_PORT, GPIO_Encoder_PIN_Left_B_PIN);
    }

    // 处理右前编码器B相中断
    if (gpioB & GPIO_Encoder_PIN_Right_B_PIN) 
    {
        // 读取右前编码器A相信号，判断计数增减
        if (DL_GPIO_readPins(GPIO_Encoder_PIN_Right_A_PORT, GPIO_Encoder_PIN_Right_A_PIN))
            Right_Count--;  // A相高电平，计数加1
        else
            Right_Count++;  // A相低电平，计数减1
        
        // 清除右前编码器B相中断状态
        DL_GPIO_clearInterruptStatus(GPIO_Encoder_PIN_Right_B_PORT, GPIO_Encoder_PIN_Right_B_PIN);
    }
}