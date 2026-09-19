# 视觉辅助曲射电磁发射系统（STM32F407）

基于 STM32F407VET6 的多传感器、多 MCU 协同原型。系统接收 Maix 端侧视觉坐标与 TF-Luna 测距数据，完成目标搜索、锁定、角度/位置计算、双轴执行和互锁触发。

<p align="center"><img src="../../docs/images/electromagnetic-launcher.jpg" alt="曲射电磁发射系统原型" width="820" /></p>

## 实现内容

- STM32F407 运行于 168 MHz，使用 HAL 组织 GPIO、定时器、编码器和 5 路 UART。
- 在统一 UART 接收回调中分发 Maix、TF-Luna、串口屏和板间反馈，接收完成后立即恢复非阻塞接收。
- 用独立状态机解析视觉坐标帧和测距帧，包含帧头、帧尾、校验和与信号强度判断。
- 将搜索、居中、测距、角度解算、瞄准、触发、回零拆为明确状态，降低复杂动作的耦合。
- 通过自定义帧将位置、KP/KD、力矩等参数下发到执行 MCU，形成“感知控制板 + 实时执行板”的分层结构。

## 代码导航

| 文件 | 职责 |
| --- | --- |
| [`firmware/app/app.c`](firmware/app/app.c) | 外设启动、模式选择与顶层任务循环 |
| [`firmware/app/gyro.c`](firmware/app/gyro.c) | 5 路 UART 中断接收与协议分发 |
| [`firmware/app/maix.c`](firmware/app/maix.c) | Maix 二维坐标帧解析 |
| [`firmware/app/luna.c`](firmware/app/luna.c) | TF-Luna 双帧头、校验和、距离/强度解析 |
| [`firmware/app/stm.c`](firmware/app/stm.c) | 双 MCU 控制参数帧发送 |
| [`firmware/app/stm_receive.c`](firmware/app/stm_receive.c) | 执行 MCU 位置反馈解析 |
| [`firmware/app/Fourth.c`](firmware/app/Fourth.c) | 扫描—锁定—距离解算—互锁触发—回零流程 |
| [`firmware/app/Fifth.c`](firmware/app/Fifth.c) | 往复扫描、视觉窗口判定与执行流程 |
| [`firmware/app/electric.c`](firmware/app/electric.c) | 执行机构状态读取与控制接口 |

## 主要协议

Maix 坐标帧：

```text
0x55 | X_L | X_H | Y_L | Y_H | 0xFF
```

执行 MCU 参数帧：

```text
0x55 | Position2 | KP2 | KD2 | Position1 | KP1 | KD1 | Torque2 | 0xFF
```

TF-Luna 使用 `0x59 0x59` 双帧头，固件计算校验和并结合幅值判断数据有效性。

## 开发环境

- STM32CubeMX / STM32CubeF4 1.28.1
- Keil MDK-ARM
- MCU：STM32F407VET6，168 MHz

建议先打开 [`firmware/NEW ENcode.ioc`](firmware/NEW%20ENcode.ioc) 重新生成基础工程，再加入 [`firmware/app`](firmware/app/) 应用层源码。公开快照保留了构建所需的 HAL/CMSIS 依赖，并移除了 `.axf/.hex/.o/.map/.lst` 等编译产物及 IDE 用户配置。

> 安全提示：该工程与实物电源、机构和执行器强相关。任何复现或调试必须先断开高能执行端，确认机械限位、急停和互锁逻辑后再分级上电。

