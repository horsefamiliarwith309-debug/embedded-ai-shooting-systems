#include "do_scream.h"
#include "tim.h"
#include "eyes.h"
#include "five.h"
#include "blind.h"

// SCREAM 数据缓冲区
uint8_t SCREAM_DataBuf[10];  // 适当放大缓冲区避免越界
uint8_t Length_1 = 0;
uint8_t Length_2 = 0;
uint8_t Length_3 = 0;
uint8_t Angle_1 = 0;
uint8_t Angle_2 = 0;
uint8_t Angle_3 = 0;

uint16_t Length_0 = 0;
float Angle_0 = 0.00f;

uint8_t flag0_1 = 0;//任务选择
uint8_t flag_shoot = 0;//开关电磁炮充电

uint8_t temp=0;//临时存储

void processSCREAMData(uint8_t res)
{
    static uint8_t screamState = 0;
    static uint8_t dataCnt = 0;
    static uint8_t frameType = 0;
    static uint8_t expectedDataLen = 0;
    uint8_t errFlag = 0;

    switch (screamState)
    {
        case 0:  // 帧头判断
            if (res == 0x55)
            {
                screamState = 1;
                dataCnt = 0;
                frameType = 0x55;
                expectedDataLen = 0;  // 先置零，等收到第 4 个字节再确定长度
            }
            else if (res == 0x66)
            {
                screamState = 3;
                dataCnt = 0;
                frameType = 0x66;
            }
            else
            {
                errFlag = 1;
            }
            break;

        case 1:  // 55 帧数据接收
            SCREAM_DataBuf[dataCnt++] = res;

            if (dataCnt == 4)
            {
                // 判断第 4 个字节（索引3）
                if (SCREAM_DataBuf[3] == 0x2D)
                {
                    expectedDataLen = 8;  // 负数，总共接收 8 个数据字节
                }
                else
                {
                    expectedDataLen = 7;  // 正数，总共接收 7 个数据字节
                }
            }

            if ((expectedDataLen != 0) && (dataCnt >= expectedDataLen))
            {
                screamState = 2;  // 数据接收完成，等待帧尾
            }
            break;

        case 2:  // 55 帧尾
            if (res == 0xFF)
            {
                // 先处理距离
                Length_1 = SCREAM_DataBuf[0];
                Length_2 = SCREAM_DataBuf[1];
                Length_3 = SCREAM_DataBuf[2];
                Length_0 = (Length_1 - '0') * 100 + (Length_2 - '0') * 10 + (Length_3 - '0');

                if (expectedDataLen == 8)  // 负角度
                {
                    Angle_1 = SCREAM_DataBuf[4];
                    Angle_2 = SCREAM_DataBuf[5];
                    Angle_3 = SCREAM_DataBuf[7];  // 注意是7索引
                    int int_part = (Angle_1 - '0') * 10 + (Angle_2 - '0');
                    int decimal_part = (Angle_3 - '0');
                    Angle_0 = -(int_part + decimal_part / 10.0f);
                }
                else  // 正角度
                {
                    Angle_1 = SCREAM_DataBuf[3];
                    Angle_2 = SCREAM_DataBuf[4];
                    Angle_3 = SCREAM_DataBuf[6];
                    int int_part = (Angle_1 - '0') * 10 + (Angle_2 - '0');
                    int decimal_part = (Angle_3 - '0');
                    Angle_0 = int_part + decimal_part / 10.0f;
                }
            }
            else
            {
                errFlag = 1;
            }
            screamState = 0;
            break;

        case 3:  // 66 帧数据接收
            SCREAM_DataBuf[dataCnt++] = res;
            if (dataCnt >= 1)
            {
                screamState = 4;
            }
            break;

        case 4:  // 66 帧尾
            if (res == 0xFF)
            {
                temp = SCREAM_DataBuf[0];
                if(temp<=5)
                    flag0_1=temp;
                else if(temp>=6)
                    flag_shoot=temp;
                    
            }
            else
            {
                errFlag = 1;
            }
            screamState = 0;
            break;

        default:
            errFlag = 1;
            screamState = 0;
            break;
    }

    if (errFlag)
    {
        screamState = 0;
        dataCnt = 0;
    }
}
