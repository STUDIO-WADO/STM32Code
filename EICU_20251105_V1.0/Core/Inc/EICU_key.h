#ifndef __EICU_KEY_H
#define __EICU_KEY_H

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#define LED_MT      HAL_GPIO_ReadPin(LED_MT_GPIO_Port, LED_MT_Pin)

#define OUT_1       HAL_GPIO_ReadPin(OUT_1_GPIO_Port,OUT_1_Pin)
#define OUT_2       HAL_GPIO_ReadPin(OUT_2_GPIO_Port,OUT_2_Pin)
#define OUT_3       HAL_GPIO_ReadPin(OUT_3_GPIO_Port,OUT_3_Pin)
#define OUT_4       HAL_GPIO_ReadPin(OUT_4_GPIO_Port,OUT_4_Pin)
#define LED_MT      HAL_GPIO_ReadPin(LED_MT_GPIO_Port, LED_MT_Pin)

void KEY_0(uint8_t x);
void KEY_1(uint8_t x);
void KEY_2(uint8_t x);
void KEY_3(uint8_t x);
void KEY_4(uint8_t x);
void KEY_5(uint8_t x);
void KEY_6(uint8_t x);
void KEY_7(uint8_t x);
void KEY_8(uint8_t x);
void KEY_9(uint8_t x);
void KEY_STAR(uint8_t x);
void KEY_POUND(uint8_t x);
void KEY_MT(uint8_t x);

void LED_1(uint8_t x);
void LED_2(uint8_t x);
void LED_3(uint8_t x);
void LED_4(uint8_t x);

void EICU_Test_Call_State(void);
void EICU_Start_Num(uint8_t *num_buff);
void EICU_Start_MT(void);
void EICU_out(void);

void EICU_Main_Loop(void);
void task_led_blink_5s(void *pvParameters);

#endif
