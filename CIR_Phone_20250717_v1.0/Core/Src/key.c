#include "key.h"
#include "main.h"
#include "rs485.h"
#include <stdbool.h>

#define PRESS_KEY(fn)  do { fn(0); HAL_Delay(DELAY_TIME); fn(1); HAL_Delay(DELAY_TIME); } while(0)  // 封装按键处理宏
#define DELAY_TIME  500    //延时继电器开关 ms
#define DIALING_MAP_SIZE sizeof(dialing_map)/sizeof(dialing_map[0]) //按键映射表数量

extern HOLDREG Reg[];
#define Reg_Len modbus.rcbuf[2] - 1
typedef void (*KeyFunc)(uint8_t);

uint8_t MT_Flag;

// 映射表结构
typedef struct {
    uint16_t code;
    KeyFunc  key_func;
} DialingMap;

// 映射表
DialingMap dialing_map[] = {
    {0x60, KEY_0},			
    {0x61, KEY_1},
    {0x62, KEY_2},
    {0x63, KEY_3},
    {0x64, KEY_4},
    {0x65, KEY_5},
    {0x66, KEY_6},
    {0x67, KEY_7},
    {0x68, KEY_8},
    {0x69, KEY_9},
    {0x6A, KEY_STAR},
    {0x6E, KEY_POUND},
    {0xDC, KEY_MT},
    {0x6B, KEY_GD}     //挂断
};

#if 0
void Cir_Dialing(void)
{
    if(Reg[0].HoldRegData == 0) return;
    
    for(int i = 0;i < Reg_Len; i++)
    {
        int matched = 0;
        for(int j = 0;j < DIALING_MAP_SIZE; j++)
        {
            if(Reg[i].HoldRegData == dialing_map[j].code)
            {
                PRESS_KEY(dialing_map[j].key_func);
                matched = 1;
                break;
            }
        }
        Reg[i].HoldRegData = 0;
        if (!matched)
        {
            Reg[0].HoldRegData = 0;  // 立即中止处理
            return;
        }
    }
}
#else
void Cir_Dialing_Text(void)
{  
    if(Reg[Reg_Len].HoldRegData == 0x6B && (Led_Mt_flag())) //通话状态才执行挂断
    {
        PRESS_KEY(KEY_GD);
    }
    
    if(Reg[Reg_Len].HoldRegData == 0xDC && (!Led_Mt_flag()))//挂断未通话状态才执行通话
    {
        PRESS_KEY(KEY_MT);  // 拨号前按下 MT 键
    
        HAL_Delay(500);
        for (int i = 0; i < Reg_Len; i++)
        {
            int matched = 0;
            for (int j = 0; j < DIALING_MAP_SIZE; j++)
            {
                if (Reg[i].HoldRegData == dialing_map[j].code)
                {
                    PRESS_KEY(dialing_map[j].key_func);
                    matched = 1;
                    break;
                }
            }
            Reg[i].HoldRegData = 0;
            if (!matched)
            {
                Reg[Reg_Len].HoldRegData = 0;  // 立即中止处理
                return;
            }    
        }
    }
    Reg[Reg_Len].HoldRegData = 0;  // 拨号结束清零
}
#endif

uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;
    uint8_t keyval = 0;
    
    if(mode) key_up = 1;
    
    if(key_up && (KEYI == 1 || KEYII == 1 || KEYPTT == 1))
    {
        HAL_Delay(10);
        key_up = 0;
        
        if(KEYI == 1)   keyval = KEYI_PRES;
        if(KEYII == 1)  keyval = KEYII_PRES;
        if(KEYPTT == 1) keyval = KEYPTT_PRES;
    }
    else if(KEYI == 0 && KEYII == 0 && KEYPTT == 0)
    {
        key_up = 1;
    }
    return keyval;
}

uint8_t Led_Mt_flag(void)
{
    return MT_Flag = LED_MT;
}

/* -------------------------------------KEY端口定义-------------------------------------------------- */
void KEY_0(uint8_t x) {
    HAL_GPIO_WritePin(Key_0_GPIO_Port, Key_0_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void KEY_1(uint8_t x) {
    HAL_GPIO_WritePin(Key_1_GPIO_Port, Key_1_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void KEY_2(uint8_t x) {
    HAL_GPIO_WritePin(Key_2_GPIO_Port, Key_2_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void KEY_3(uint8_t x) {
    HAL_GPIO_WritePin(Key_3_GPIO_Port, Key_3_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void KEY_4(uint8_t x) {
    HAL_GPIO_WritePin(Key_4_GPIO_Port, Key_4_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void KEY_5(uint8_t x) {
    HAL_GPIO_WritePin(Key_5_GPIO_Port, Key_5_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void KEY_6(uint8_t x) {
    HAL_GPIO_WritePin(Key_6_GPIO_Port, Key_6_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void KEY_7(uint8_t x) {
    HAL_GPIO_WritePin(Key_7_GPIO_Port, Key_7_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void KEY_8(uint8_t x) {
    HAL_GPIO_WritePin(Key_8_GPIO_Port, Key_8_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void KEY_9(uint8_t x) {
    HAL_GPIO_WritePin(Key_9_GPIO_Port, Key_9_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void KEY_STAR(uint8_t x) {
    HAL_GPIO_WritePin(Key_STAR_GPIO_Port, Key_STAR_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}   // *

void KEY_POUND(uint8_t x) {
    HAL_GPIO_WritePin(Key_POUND_GPIO_Port, Key_POUND_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}   // #

void KEY_MT(uint8_t x) {
    HAL_GPIO_WritePin(Key_MT_GPIO_Port, Key_MT_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}   // 免提

void KEY_GD(uint8_t x) {
    HAL_GPIO_WritePin(Key_MT_GPIO_Port, Key_MT_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET);
}   // 免提










