/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define LED2_Pin GPIO_PIN_14
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_15
#define LED3_GPIO_Port GPIOC
#define KEY1_Pin GPIO_PIN_13
#define KEY1_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_14
#define KEY2_GPIO_Port GPIOB
#define KEY3_Pin GPIO_PIN_15
#define KEY3_GPIO_Port GPIOB
#define EC11_B_Pin GPIO_PIN_3
#define EC11_B_GPIO_Port GPIOB
#define EC11_A_Pin GPIO_PIN_4
#define EC11_A_GPIO_Port GPIOB
#define EC11_A_EXTI_IRQn EXTI4_IRQn
#define ST7735_RES_Pin GPIO_PIN_5
#define ST7735_RES_GPIO_Port GPIOB
#define ST7735_DC_Pin GPIO_PIN_6
#define ST7735_DC_GPIO_Port GPIOB
#define ST7735_CS_Pin GPIO_PIN_7
#define ST7735_CS_GPIO_Port GPIOB
#define ST7735_BL_Pin GPIO_PIN_8
#define ST7735_BL_GPIO_Port GPIOB
#define EC11_D_Pin GPIO_PIN_9
#define EC11_D_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
