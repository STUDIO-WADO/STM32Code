#include "key.h"

uint8_t Read_Key(void)
{
    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET)
    {
        HAL_Delay(10);
        if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET)
        {
            while(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET);
            return KEY1;
        }
    }

    if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET)
    {
        HAL_Delay(10);
        if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET)
        {
            while(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET);
            return KEY2;
        }
    }

    if(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET)
    {
        HAL_Delay(10);
        if(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET)
        {
            while(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET);
            return KEY3;
        }
    }
    return 0;
}

void Key_Handler(void)
{
    uint8_t key = Read_Key();
    switch(key)
    {
        case KEY1:
            // 打开LED2
            LED2_Open();
            break;
        case KEY2:
            // 打开LED3
            LED3_Open();
            break;
        case KEY3:
            // 关闭LED2和LED3
            LED2_Close();
            LED3_Close();
            break;
        default:
            break;
    }
}
