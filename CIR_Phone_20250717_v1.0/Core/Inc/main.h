/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define Key_3_Pin GPIO_PIN_2
#define Key_3_GPIO_Port GPIOE
#define Key_4_Pin GPIO_PIN_3
#define Key_4_GPIO_Port GPIOE
#define Key_5_Pin GPIO_PIN_4
#define Key_5_GPIO_Port GPIOE
#define Key_6_Pin GPIO_PIN_5
#define Key_6_GPIO_Port GPIOE
#define Key_7_Pin GPIO_PIN_6
#define Key_7_GPIO_Port GPIOE
#define LED_RUN_Pin GPIO_PIN_3
#define LED_RUN_GPIO_Port GPIOA
#define LED_MT_Pin GPIO_PIN_0
#define LED_MT_GPIO_Port GPIOB
#define KEY_I_Pin GPIO_PIN_7
#define KEY_I_GPIO_Port GPIOE
#define KEY_II_Pin GPIO_PIN_8
#define KEY_II_GPIO_Port GPIOE
#define PTT_Pin GPIO_PIN_9
#define PTT_GPIO_Port GPIOE
#define Key_POUND_Pin GPIO_PIN_11
#define Key_POUND_GPIO_Port GPIOE
#define Key_MT_Pin GPIO_PIN_12
#define Key_MT_GPIO_Port GPIOE
#define Key_0_Pin GPIO_PIN_10
#define Key_0_GPIO_Port GPIOB
#define Key_8_Pin GPIO_PIN_7
#define Key_8_GPIO_Port GPIOC
#define RS485_EN_Pin GPIO_PIN_8
#define RS485_EN_GPIO_Port GPIOC
#define US1_T_Pin GPIO_PIN_9
#define US1_T_GPIO_Port GPIOA
#define US1_R_Pin GPIO_PIN_10
#define US1_R_GPIO_Port GPIOA
#define Key_9_Pin GPIO_PIN_8
#define Key_9_GPIO_Port GPIOB
#define Key_STAR_Pin GPIO_PIN_9
#define Key_STAR_GPIO_Port GPIOB
#define Key_1_Pin GPIO_PIN_0
#define Key_1_GPIO_Port GPIOE
#define Key_2_Pin GPIO_PIN_1
#define Key_2_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
