/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED2_Pin|LED3_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7735_RES_Pin|ST7735_DC_Pin|ST7735_CS_Pin|ST7735_BL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED2_Pin LED3_Pin */
  GPIO_InitStruct.Pin = LED2_Pin|LED3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : KEY1_Pin KEY2_Pin KEY3_Pin EC11_B_Pin
                           EC11_D_Pin */
  GPIO_InitStruct.Pin = KEY1_Pin|KEY2_Pin|KEY3_Pin|EC11_B_Pin
                          |EC11_D_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : EC11_A_Pin */
  GPIO_InitStruct.Pin = EC11_A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(EC11_A_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7735_RES_Pin ST7735_DC_Pin ST7735_CS_Pin ST7735_BL_Pin */
  GPIO_InitStruct.Pin = ST7735_RES_Pin|ST7735_DC_Pin|ST7735_CS_Pin|ST7735_BL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

/* USER CODE BEGIN 2 */
// 全局变量
volatile uint8_t A_cnt = 0;
volatile uint8_t B_value = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == EC11_A_Pin)
  {
    if((HAL_GPIO_ReadPin(EC11_A_GPIO_Port, EC11_A_Pin) == GPIO_PIN_RESET) && (A_cnt == 0))
    {
      A_cnt++;
      B_value = 0;
      if(HAL_GPIO_ReadPin(EC11_B_GPIO_Port, EC11_B_Pin) == GPIO_PIN_SET)
      {
        B_value = 1;
      }
    }
    else if((HAL_GPIO_ReadPin(EC11_A_GPIO_Port, EC11_A_Pin) == GPIO_PIN_SET) && (A_cnt == 1))
    {
      A_cnt = 0;
      if((B_value == 1) && (HAL_GPIO_ReadPin(EC11_B_GPIO_Port, EC11_B_Pin) == GPIO_PIN_RESET))
      {
        // 顺时针
        LED2_Open();
        LED3_Close();
      }
      if((B_value == 0) && (HAL_GPIO_ReadPin(EC11_B_GPIO_Port, EC11_B_Pin) == GPIO_PIN_SET))
      {
        // 逆时针
        LED2_Close();
        LED3_Open();
      }
    }

  }
}
/* USER CODE END 2 */
