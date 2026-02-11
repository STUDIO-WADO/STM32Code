#ifndef _HW_KEY_H__
#define _HW_KEY_H__

#include "gpio.h"

// 时间参数
#define DOUBLE_TIME 40      // 400ms内按下两次算双击

// 按键状态
#define KEY_NoPress 0xFF    // 无按键按下
#define KEY_ERROR   0x00    // 错误状态
#define KEY_OK      0x01    // 有效按键

// 单个按键状态
#define KeyPress       0x10  // 单击
#define KeyDoublePress 0x20  // 双击
#define KeyLongPress   0x30  // 长按

// 高4位表示按键类型 1=单击, 2=双击, 3=长按
// 低4位表示按键编号 0~F
#define Key1Press 0x10
#define Key2Press 0x11
#define Key3Press 0x12

#define Key1DoublePress 0x20
#define Key2DoublePress 0x21
#define Key3DoublePress 0x22

#define Key1LongPress  0x30
#define Key2LongPress  0x31
#define Key3LongPress  0x32

#define GET_KEY1_IN        HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)  // 获取KEY1输入状态
#define GET_KEY2_IN        HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)  // 获取KEY2输入状态
#define GET_KEY3_IN        HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)  // 获取KEY3输入状态

struct key_class
{
    GPIO_TypeDef *key_port;     // 按键GPIO端口
    uint16_t key_pin;           // 按键引脚
    uint8_t key_state;          // 按键状态
    uint8_t key_press_level;    // 按下时的电平 RESET或SET

     // ===== 状态机相关变量 =====
    uint8_t keyCnt;             // 消抖计数   
    uint8_t keyFcnt;            // 用于判断按键多久间隔算双击
    uint8_t keyCount;           // 按键按下的次数
    uint8_t keyLongFlag;        // 长按标志位
};

//enum KEYNum
//{
//    KEY1 = 0,
//    KEY2,
//    KEY3,
//    KEY_NUM
//};

enum key_instance
{
    key1 = 0,
    key2,
    key3,
    keyd,
    key_num
};

extern struct key_class key_handle[key_num];

void key_scanf(struct key_class *key_handle);
uint8_t key_scanf_all(void);
struct key_class key_init(GPIO_TypeDef *key_port, uint32_t key_pin, uint8_t key_press_level);
void hw_key_init(void);
void hw_key_scan_all(void);

#endif
