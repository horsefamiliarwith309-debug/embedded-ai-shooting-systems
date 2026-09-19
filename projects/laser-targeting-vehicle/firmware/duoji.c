#include "duoji.h"

// 设置 舵机PWM 占空比的函数
void Set_Duty(float duty)
{
    uint32_t CompareValue = 32000 - 32000 * duty; // 计算比较值

    DL_Timer_setCaptureCompareValue(PWM_SERVO_INST, CompareValue, GPIO_PWM_SERVO_C0_IDX); // 设置通道 0 的 PWM 占空比

}