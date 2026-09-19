/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define bijiao_Pin GPIO_PIN_6
#define bijiao_GPIO_Port GPIOE
#define Motor_R_1_Pin GPIO_PIN_0
#define Motor_R_1_GPIO_Port GPIOA
#define Motor_L_2_Pin GPIO_PIN_1
#define Motor_L_2_GPIO_Port GPIOA
#define Motor_R_2_Pin GPIO_PIN_4
#define Motor_R_2_GPIO_Port GPIOA
#define Motor_L_1_Pin GPIO_PIN_5
#define Motor_L_1_GPIO_Port GPIOA
#define EncodeA1_Pin GPIO_PIN_6
#define EncodeA1_GPIO_Port GPIOA
#define EncodeA2_Pin GPIO_PIN_7
#define EncodeA2_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOB
#define gray1_Pin GPIO_PIN_10
#define gray1_GPIO_Port GPIOE
#define gray2_Pin GPIO_PIN_12
#define gray2_GPIO_Port GPIOE
#define gray3_Pin GPIO_PIN_12
#define gray3_GPIO_Port GPIOB
#define gray4_Pin GPIO_PIN_13
#define gray4_GPIO_Port GPIOB
#define gray5_Pin GPIO_PIN_14
#define gray5_GPIO_Port GPIOB
#define gray6_Pin GPIO_PIN_8
#define gray6_GPIO_Port GPIOD
#define gray7_Pin GPIO_PIN_10
#define gray7_GPIO_Port GPIOD
#define EncodeB1_Pin GPIO_PIN_12
#define EncodeB1_GPIO_Port GPIOD
#define EncodeB2_Pin GPIO_PIN_13
#define EncodeB2_GPIO_Port GPIOD
#define gray8_Pin GPIO_PIN_14
#define gray8_GPIO_Port GPIOD
#define electric_Pin GPIO_PIN_8
#define electric_GPIO_Port GPIOC
#define electric_1_Pin GPIO_PIN_15
#define electric_1_GPIO_Port GPIOA
#define electric_1D3_Pin GPIO_PIN_3
#define electric_1D3_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
