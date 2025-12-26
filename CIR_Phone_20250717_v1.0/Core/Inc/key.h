#ifndef __KEY_H
#define __KEY_H

#include "main.h"

/* -------------------------------------送受话器----KEY端口定义-------------------------------------------------- */
#define KEYI        HAL_GPIO_ReadPin(KEY_I_GPIO_Port,  KEY_I_Pin)          /* 读取 I 引脚 */
#define KEYII       HAL_GPIO_ReadPin(KEY_II_GPIO_Port, KEY_II_Pin)         /* 读取 II 引脚 */
#define KEYPTT      HAL_GPIO_ReadPin(PTT_GPIO_Port,    PTT_Pin)           /* 读取 PTT 引脚 */

#define KEYI_PRES       1       /* KEYI按下 */
#define KEYII_PRES      2       /* KEYII按下 */
#define KEYPTT_PRES     3       /* KEYPTT按下 */

#define LED_MT      HAL_GPIO_ReadPin(LED_MT_GPIO_Port, LED_MT_Pin);

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
void KEY_GD(uint8_t x);

void Cir_Dialing_Text(void);
void Cir_Dialing(void);
uint8_t key_scan(uint8_t mode);     /* 按键扫描函数 */
uint8_t Led_Mt_flag(void);
    
#endif
