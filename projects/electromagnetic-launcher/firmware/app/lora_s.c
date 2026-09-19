#include "lora_s.h"

// 数据缓冲区
uint8_t Lora_DataBuf[4];  // 用于存储接收到的Lora数据
uint8_t flag_do_1 = 0;
uint8_t flag_do_2 = 0;
uint8_t flag_do_3 = 0;

void processLoraData(uint8_t res)
{
    static uint8_t loraState = 0;
    static uint8_t dataCnt = 0;
    uint8_t errFlag = 0;

    switch (loraState)
    {
        case 0:
            if (res == 0x55)  // 帧头检查
            {
                loraState = 1;  // 进入数据接收状态
                dataCnt = 0;   // 重置数据计数
            }
            else
            {
                errFlag = 1;
            }
            break;

        case 1:
            // 接收并存储数据
            Lora_DataBuf[dataCnt++] = res;  // 按顺序存储接收到的数据
            if (dataCnt >= 3)  // 两个数据字节接收完毕，进入帧尾检查状态
            {
                loraState = 2;
            }
            break;

        case 2:
            if (res == 0xFF)  // 帧尾检查
            {
                loraState = 0;  // 重置状态机
                flag_do_1 = Lora_DataBuf[0];
                flag_do_2 = Lora_DataBuf[1];
                flag_do_3 = Lora_DataBuf[2];
            }
            else
            {
                errFlag = 1;
            }
            break;

        default:
            errFlag = 1;
            break;
    }

    if (errFlag)
    {
        // 如果发生错误，重置状态机
        loraState = 0;
    }
}
