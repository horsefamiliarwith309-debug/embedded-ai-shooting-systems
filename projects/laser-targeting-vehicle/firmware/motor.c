#include "motor.h"

void Set_Speed(uint8_t side, float duty)
{
    uint32_t compareValue = 0;
    if(side == 0)
    {
        if(duty > 0)
        {
            compareValue = 31999 - 31999 * (duty/100.0);
            DL_Timer_setCaptureCompareValue(PWM_MOTOR_INST, compareValue, DL_TIMER_CC_0_INDEX);
            DL_GPIO_setPins(GPIO_MOTOR_PIN_FL1_PORT, GPIO_MOTOR_PIN_FL1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PIN_FL2_PORT, GPIO_MOTOR_PIN_FL2_PIN);
        }
        else if(duty < 0)
        {
            compareValue = 31999 - 31999 * (-duty/100.0);
            DL_Timer_setCaptureCompareValue(PWM_MOTOR_INST, compareValue, DL_TIMER_CC_0_INDEX);
            DL_GPIO_clearPins(GPIO_MOTOR_PIN_FL1_PORT, GPIO_MOTOR_PIN_FL1_PIN);
            DL_GPIO_setPins(GPIO_MOTOR_PIN_FL2_PORT, GPIO_MOTOR_PIN_FL2_PIN);
        }
        else 
        {
            DL_GPIO_clearPins(GPIO_MOTOR_PIN_FL1_PORT, GPIO_MOTOR_PIN_FL1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PIN_FL2_PORT, GPIO_MOTOR_PIN_FL2_PIN);
        }
    }
    else
    {
        if(duty < 0)
        {
            compareValue = 31999 - 31999 * (-duty/100.0);
            DL_Timer_setCaptureCompareValue(PWM_MOTOR_INST, compareValue, DL_TIMER_CC_1_INDEX);
            DL_GPIO_setPins(GPIO_MOTOR_PIN_FR1_PORT, GPIO_MOTOR_PIN_FR1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PIN_FR2_PORT, GPIO_MOTOR_PIN_FR2_PIN);
        }
        else if(duty > 0)
        {
            compareValue = 31999 - 31999 * (duty/100.0);
            DL_Timer_setCaptureCompareValue(PWM_MOTOR_INST, compareValue, DL_TIMER_CC_1_INDEX);
            DL_GPIO_clearPins(GPIO_MOTOR_PIN_FR1_PORT, GPIO_MOTOR_PIN_FR1_PIN);
            DL_GPIO_setPins(GPIO_MOTOR_PIN_FR2_PORT, GPIO_MOTOR_PIN_FR2_PIN);
        }
        else 
        {
            DL_GPIO_clearPins(GPIO_MOTOR_PIN_FR1_PORT, GPIO_MOTOR_PIN_FR1_PIN);
            DL_GPIO_clearPins(GPIO_MOTOR_PIN_FR2_PORT, GPIO_MOTOR_PIN_FR2_PIN);
        }
    }
}