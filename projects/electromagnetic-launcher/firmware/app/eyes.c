#include "eyes.h"

// 数据缓冲区
uint8_t Eye_DataBuf[4];  // 用于存储接收到的眼睛数据
uint8_t Eye_Value1 = 0;  // 第一个数字
uint8_t Eye_Value2 = 0;  // 第二个数字

void processEyesData(uint8_t res)
{
    static uint8_t eyeState = 0;
    static uint8_t dataCnt = 0;
    uint8_t errFlag = 0;  // 错误标志

    switch (eyeState)
    {
        case 0:
            if (res == 0x2C)  // 帧头检查
            {
                eyeState = 1;  // 进入数据接收状态
                dataCnt = 0;   // 重置数据计数
            }
            else
            {
                errFlag = 1;  // 帧头不匹配，标记错误
            }
            break;

        case 1:
            // 接收并存储数据
            if (dataCnt < 2)  // 我们只期待接收两个数据字节
            {
                Eye_DataBuf[dataCnt++] = res;  // 按顺序存储接收到的数据
            }

            if (dataCnt >= 2)  // 两个数据字节接收完毕，进入帧尾检查状态
            {
                eyeState = 2;
            }
            break;

        case 2:
            if (res == 0x5B)  // 帧尾检查
            {
                // 成功接收到完整的帧数据
                eyeState = 0;  // 重置状态机
                // 在这里可以处理 `Eye_DataBuf`
                Eye_Value1 = Eye_DataBuf[0];
                Eye_Value2 = Eye_DataBuf[1];
                
            }
            else
            {
                errFlag = 1;  // 帧尾不匹配，标记错误
            }
            break;

        default:
            errFlag = 1;  // 如果状态无效，标记错误
            break;
    }

    if (errFlag)
    {
        // 如果发生错误，重置状态机
        eyeState = 0;
        dataCnt = 0;
    }
}
