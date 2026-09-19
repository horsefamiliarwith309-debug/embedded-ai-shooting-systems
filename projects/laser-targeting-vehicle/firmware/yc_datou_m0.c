#include "yc_datou_m0.h"
#include "ti_msp_dl_config.h"

/**********************************************************
***	Emm_V5.0步进闭环控制例程
***	编写作者：WYCCC
**********************************************************/

static uint8_t cmd_buf[32];


void send_command_buf(uint8_t *buf, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++) {
        while (DL_UART_isBusy(UART_3_INST));
        DL_UART_Main_transmitData(UART_3_INST, buf[i]);
    }
}

/**
  * @brief    将当前位置清零
  * @param    addr  ：电机地址
  * @retval   地址 + 功能码 + 命令状态 + 校验字节
  */
void Emm_V5_Reset_CurPos_To_Zero(uint8_t addr)
{
    cmd_buf[0] = addr;
    cmd_buf[1] = 0x0A;
    cmd_buf[2] = 0x6D;
    cmd_buf[3] = 0x6B;
    send_command_buf(cmd_buf, 4);
}

/**
  * @brief    解除堵转保护
  * @param    addr  ：电机地址
  * @retval   地址 + 功能码 + 命令状态 + 校验字节
  */
void Emm_V5_Reset_Clog_Pro(uint8_t addr)
{
    cmd_buf[0] = addr;
    cmd_buf[1] = 0x0E;
    cmd_buf[2] = 0x52;
    cmd_buf[3] = 0x6B;
    send_command_buf(cmd_buf, 4);
}


/**
  * @brief    读取系统参数
  * @param    addr  ：电机地址
  * @param    s     ：系统参数类型
  * @retval   地址 + 功能码 + 命令状态 + 校验字节

    DT_Position_Request(2);  // 请求读取ID为2的电机位置
    HAL_Delay(10);
    if (DT_Position_Available()      
    {
        Motor_Cur_Pos = DT_Position_GetAngle();  // 获取电机角度
    }
  */
void Emm_V5_Read_Sys_Params(uint8_t addr, SysParams_t s)
{
    uint8_t i = 0;
    cmd_buf[i++] = addr;
    switch(s) {
        case S_VER:  cmd_buf[i++] = 0x1F; break;
        case S_RL:   cmd_buf[i++] = 0x20; break;
        case S_PID:  cmd_buf[i++] = 0x21; break;
        case S_VBUS: cmd_buf[i++] = 0x24; break;
        case S_CPHA: cmd_buf[i++] = 0x27; break;
        case S_ENCL: cmd_buf[i++] = 0x31; break;
        case S_TPOS: cmd_buf[i++] = 0x33; break;
        case S_VEL:  cmd_buf[i++] = 0x35; break;
        case S_CPOS: cmd_buf[i++] = 0x36; break;
        case S_PERR: cmd_buf[i++] = 0x37; break;
        case S_FLAG: cmd_buf[i++] = 0x3A; break;
        case S_ORG:  cmd_buf[i++] = 0x3B; break;
        case S_Conf: cmd_buf[i++] = 0x42; cmd_buf[i++] = 0x6C; break;
        case S_State:cmd_buf[i++] = 0x43; cmd_buf[i++] = 0x7A; break;
        default: return;
    }
    cmd_buf[i++] = 0x6B;
    send_command_buf(cmd_buf, i);
}

/**
  * @brief    修改开环/闭环控制模式
  * @param    addr     ：电机地址
  * @param    svF      ：是否存储标志，false为不存储，true为存储
  * @param    ctrl_mode：控制模式（对应屏幕上的P_Pul菜单），0是关闭脉冲输入引脚，1是开环模式，2是闭环模式，3是让En端口复用为多圈限位开关输入引脚，Dir端口复用为到位输出高电平功能
  * @retval   地址 + 功能码 + 命令状态 + 校验字节
  */
void Emm_V5_Modify_Ctrl_Mode(uint8_t addr, bool svF, uint8_t ctrl_mode)
{
    cmd_buf[0] = addr;
    cmd_buf[1] = 0x46;
    cmd_buf[2] = 0x69;
    cmd_buf[3] = svF;
    cmd_buf[4] = ctrl_mode;
    cmd_buf[5] = 0x6B;
    send_command_buf(cmd_buf, 6);
}

/**
  * @brief    使能信号控制
  * @param    addr  ：电机地址
  * @param    state ：使能状态     ，true为使能电机，false为关闭电机
  * @param    snF   ：多机同步标志 ，false为不启用，true为启用
  * @retval   地址 + 功能码 + 命令状态 + 校验字节
  */
void Emm_V5_En_Control(uint8_t addr, bool state, bool snF)
{
    cmd_buf[0] = addr;
    cmd_buf[1] = 0xF3;
    cmd_buf[2] = 0xAB;
    cmd_buf[3] = state;
    cmd_buf[4] = snF;
    cmd_buf[5] = 0x6B;
    send_command_buf(cmd_buf, 6);
}

/**
  * @brief    速度模式
  * @param    addr：电机地址
  * @param    dir ：方向       ，为0CW，其余值为CCW
  * @param    vel ：速度       ，范围0 - 5000RPM
  * @param    acc ：加速度     ，范围0 - 255，注意：0是直接启动
  * @param    snF ：多机同步标志，false为不启用，true为启用
  * @retval   地址 + 功能码 + 命令状态 + 校验字节
  */
void Emm_V5_Vel_Control(uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, bool snF)
{
    cmd_buf[0] = addr;
    cmd_buf[1] = 0xF6;
    cmd_buf[2] = dir;
    cmd_buf[3] = vel >> 8;
    cmd_buf[4] = vel;
    cmd_buf[5] = acc;
    cmd_buf[6] = snF;
    cmd_buf[7] = 0x6B;
    send_command_buf(cmd_buf, 8);
}

/**
  * @brief    位置模式
  * @param    addr：电机地址
  * @param    dir ：方向        ，0为CW，其余值为CCW
  * @param    vel ：速度(RPM)   ，范围0 - 5000RPM
  * @param    acc ：加速度      ，范围0 - 255，注意：0是直接启动
  * @param    clk ：脉冲数      ，范围0- (2^32 - 1)个
  * @param    raF ：相位/绝对标志，false为相对运动，true为绝对值运动
  * @param    snF ：多机同步标志 ，false为不启用，true为启用
  * @retval   地址 + 功能码 + 命令状态 + 校验字节

    Emm_V5_Pos_Control(1, 1, 200, 0, 3200, 0, 1); // 多机同步标志位置1
    HAL_Delay(10);
    Emm_V5_Pos_Control(2, 0, 100, 0, 3200, 0, 1); // 多机同步标志位置1
    HAL_Delay(10);

  */
void Emm_V5_Pos_Control(uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF)
{
    cmd_buf[0] = addr;
    cmd_buf[1] = 0xFD;
    cmd_buf[2] = dir;
    cmd_buf[3] = vel >> 8;
    cmd_buf[4] = vel;
    cmd_buf[5] = acc;
    cmd_buf[6] = clk >> 24;
    cmd_buf[7] = clk >> 16;
    cmd_buf[8] = clk >> 8;
    cmd_buf[9] = clk;
    cmd_buf[10] = raF;
    cmd_buf[11] = snF;
    cmd_buf[12] = 0x6B;
    send_command_buf(cmd_buf, 13);
}

/**
  * @brief    立即停止（所有控制模式都通用）
  * @param    addr  ：电机地址
  * @param    snF   ：多机同步标志，false为不启用，true为启用
  * @retval   地址 + 功能码 + 命令状态 + 校验字节
  */
void Emm_V5_Stop_Now(uint8_t addr, bool snF)
{
    cmd_buf[0] = addr;
    cmd_buf[1] = 0xFE;
    cmd_buf[2] = 0x98;
    cmd_buf[3] = snF;
    cmd_buf[4] = 0x6B;
    send_command_buf(cmd_buf, 5);
}

/**
  * @brief    多机同步运动
  * @param    addr  ：电机地址
  * @retval   地址 + 功能码 + 命令状态 + 校验字节
  */
void Emm_V5_Synchronous_motion(uint8_t addr)
{
    cmd_buf[0] = addr;
    cmd_buf[1] = 0xFF;
    cmd_buf[2] = 0x66;
    cmd_buf[3] = 0x6B;
    send_command_buf(cmd_buf, 4);
}

/**
  * @brief    设置单圈回零的零点位置
  * @param    addr  ：电机地址
  * @param    svF   ：是否存储标志，false为不存储，true为存储
  * @retval   地址 + 功能码 + 命令状态 + 校验字节
  */
void Emm_V5_Origin_Set_O(uint8_t addr, bool svF)
{
    cmd_buf[0] = addr;
    cmd_buf[1] = 0x93;
    cmd_buf[2] = 0x88;
    cmd_buf[3] = svF;
    cmd_buf[4] = 0x6B;
    send_command_buf(cmd_buf, 5);
}

/**
  * @brief    修改回零参数
  * @param    addr  ：电机地址
  * @param    svF   ：是否存储标志，false为不存储，true为存储
  * @param    o_mode ：回零模式，0为单圈就近回零，1为单圈方向回零，2为多圈无限位碰撞回零，3为多圈有限位开关回零
  * @param    o_dir  ：回零方向，0为CW，其余值为CCW
  * @param    o_vel  ：回零速度，单位：RPM（转/分钟）
  * @param    o_tm   ：回零超时时间，单位：毫秒
  * @param    sl_vel ：无限位碰撞回零检测转速，单位：RPM（转/分钟）
  * @param    sl_ma  ：无限位碰撞回零检测电流，单位：Ma（毫安）
  * @param    sl_ms  ：无限位碰撞回零检测时间，单位：Ms（毫秒）
  * @param    potF   ：上电自动触发回零，false为不使能，true为使能
  * @retval   地址 + 功能码 + 命令状态 + 校验字节
  */
void Emm_V5_Origin_Modify_Params(uint8_t addr, bool svF, uint8_t o_mode, uint8_t o_dir, uint16_t o_vel, uint32_t o_tm, uint16_t sl_vel, uint16_t sl_ma, uint16_t sl_ms, bool potF)
{
    cmd_buf[0] = addr;
    cmd_buf[1] = 0x4C;
    cmd_buf[2] = 0xAE;
    cmd_buf[3] = svF;
    cmd_buf[4] = o_mode;
    cmd_buf[5] = o_dir;
    cmd_buf[6] = o_vel >> 8;
    cmd_buf[7] = o_vel;
    cmd_buf[8] = o_tm >> 24;
    cmd_buf[9] = o_tm >> 16;
    cmd_buf[10] = o_tm >> 8;
    cmd_buf[11] = o_tm;
    cmd_buf[12] = sl_vel >> 8;
    cmd_buf[13] = sl_vel;
    cmd_buf[14] = sl_ma >> 8;
    cmd_buf[15] = sl_ma;
    cmd_buf[16] = sl_ms >> 8;
    cmd_buf[17] = sl_ms;
    cmd_buf[18] = potF;
    cmd_buf[19] = 0x6B;
    send_command_buf(cmd_buf, 20);
}

/**
  * @brief    触发回零
  * @param    addr   ：电机地址
  * @param    o_mode ：回零模式，0为单圈就近回零，1为单圈方向回零，2为多圈无限位碰撞回零，3为多圈有限位开关回零
  * @param    snF   ：多机同步标志，false为不启用，true为启用
  * @retval   地址 + 功能码 + 命令状态 + 校验字节
  */
void Emm_V5_Origin_Trigger_Return(uint8_t addr, uint8_t o_mode, bool snF)
{
    cmd_buf[0] = addr;
    cmd_buf[1] = 0x9A;
    cmd_buf[2] = o_mode;
    cmd_buf[3] = snF;
    cmd_buf[4] = 0x6B;
    send_command_buf(cmd_buf, 5);
}

/**
  * @brief    强制中断并退出回零
  * @param    addr  ：电机地址
  * @retval   地址 + 功能码 + 命令状态 + 校验字节
  */
void Emm_V5_Origin_Interrupt(uint8_t addr)
{
    cmd_buf[0] = addr;
    cmd_buf[1] = 0x9C;
    cmd_buf[2] = 0x48;
    cmd_buf[3] = 0x6B;
    send_command_buf(cmd_buf, 4);
}
