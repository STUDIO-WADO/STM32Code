#include "hw_key.h"

struct key_class key_init(GPIO_TypeDef *key_port, uint32_t key_pin, uint8_t key_press_level)
{
    struct key_class key_handle;
    
    // 保存硬件配置
    key_handle.key_port = key_port;
    key_handle.key_pin = key_pin;
    key_handle.key_press_level = key_press_level;  // 按下时是高还是低电平
    
    // 初始化状态机变量
    key_handle.key_state = KEY_NoPress;  // 初始无按键
    key_handle.keyCnt = 0;               // 按下时长清零
    key_handle.keyCount = 0;             // 按下次数清零
    key_handle.keyFcnt = 0;              // 双击计时清零
    key_handle.keyLongFlag = 0;          // 长按标志清零
    
    return key_handle;
}

void key_scanf(struct key_class *key_handle)
{
    // 默认无按键事件
    //key_handle->key_state = KEY_NoPress;
    
    // ========== 第一部分:按键按下检测 ==========
    if(HAL_GPIO_ReadPin(key_handle->key_port, key_handle->key_pin) == key_handle->key_press_level)
    {
        // 按键处于按下状态
        key_handle->keyCnt++;  // 按下时长++
        
        if(key_handle->keyCnt >= 120)  // 1.2秒封顶
        {
            key_handle->keyCnt = 120;  // 防止溢出
        }
    }
    else
    {
        // ========== 第二部分:按键释放处理 ==========
        
        // 情况1:长按判断(按下>1s 且 之前没有短按)
        if((key_handle->keyCnt >= 100) && (key_handle->keyLongFlag == 0))
        {
            key_handle->key_state = KeyLongPress;  // 触发长按事件
        }
        // 情况2:有效短按(按下>20ms 消抖)
        else if(key_handle->keyCnt >= 2)
        {
            key_handle->keyCount++;              // 按下次数+1
            key_handle->keyFcnt = DOUBLE_TIME;   // 启动双击计时器(400ms)
            key_handle->keyLongFlag = 1;         // 标记已有短按
        }
        
        key_handle->keyCnt = 0;  // 清除按下时长
        
        // ========== 第三部分:双击/单击判断 ==========
        if(key_handle->keyFcnt)  // 双击计时器运行中
        {
            key_handle->keyFcnt--;  // 倒计时-1
            
            if(key_handle->keyFcnt <= 0)  // 计时器到期
            {
                // 根据按下次数判断事件类型
                if(key_handle->keyCount == 1)
                {
                    key_handle->key_state = KeyPress;  // 单击
                }
                else if(key_handle->keyCount == 2)
                {
                    key_handle->key_state = KeyDoublePress;  // 双击
                }
                
                // 重置状态机
                key_handle->keyFcnt = 0;
                key_handle->keyCount = 0;
                key_handle->keyLongFlag = 0;
            }
        }
    }
}

uint8_t key_scanf_all(void)
{
    uint8_t ret = KEY_ERROR;
    static uint8_t keyCnt[key_num] = {0};
    static uint8_t keyFcnt[key_num] = {0};
    static uint8_t keyCount[key_num] = {0};
    static uint8_t keyLongFlag[key_num] = {0};
    
    // 定义按键配置表
    struct {
        GPIO_TypeDef *gpio_port;
        uint16_t gpio_pin;
    } key_config[] = {
        {KEY1_GPIO_Port, KEY1_Pin},  // KEY1
        {KEY2_GPIO_Port, KEY2_Pin},  // KEY2
        {KEY3_GPIO_Port, KEY3_Pin}   // KEY3
    };
    
    for(uint8_t i = 0; i < key_num; i++)
    {
        // 直接读取GPIO状态
        uint8_t key_state = HAL_GPIO_ReadPin(
            key_config[i].gpio_port, 
            key_config[i].gpio_pin
        );
        
        if(key_state == RESET)  // 按下
        {
            keyCnt[i]++;
            if(keyCnt[i] >= 120) keyCnt[i] = 120;
        }
        else  // 释放
        {
            if((keyCnt[i] >= 100) && (keyLongFlag[i] == 0))
            {
                ret = KeyLongPress + i;  // 0x30, 0x31, 0x32
            }
            else if(keyCnt[i] >= 2)
            {
                keyCount[i]++;
                keyFcnt[i] = DOUBLE_TIME;
                keyLongFlag[i] = 1;
            }
            
            keyCnt[i] = 0;
            
            if(keyFcnt[i])
            {
                keyFcnt[i]--;
                if(keyFcnt[i] <= 0)
                {
                    if(keyCount[i] == 1) 
                        ret = KeyPress + i;
                    else if(keyCount[i] == 2) 
                        ret = KeyDoublePress + i;
                    
                    keyFcnt[i] = 0;
                    keyCount[i] = 0;
                    keyLongFlag[i] = 0;
                }
            }
        }
    }
    
    return ret;
}

struct key_class key_handle[key_num];

void hw_key_init(void)
{
    key_handle[key1] = key_init(KEY1_GPIO_Port, KEY1_Pin, GPIO_PIN_RESET);
    key_handle[key2] = key_init(KEY2_GPIO_Port, KEY2_Pin, GPIO_PIN_RESET);
    key_handle[key3] = key_init(KEY3_GPIO_Port, KEY3_Pin, GPIO_PIN_RESET);
    key_handle[keyd] = key_init(EC11_D_GPIO_Port, EC11_D_Pin, GPIO_PIN_RESET);
}

// 扫描所有按键
void hw_key_scan_all(void)
{
    for(uint8_t i = 0; i < key_num; i++)
    {
        key_scanf(&key_handle[i]);
    }
}




