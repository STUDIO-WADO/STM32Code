#include "hw_led.h"

//点亮LED
void led_turn_on(struct led_class *led)
{
    if(led->led_on_level == RESET)
    {
        HAL_GPIO_WritePin(led->led_port, led->led_pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(led->led_port, led->led_pin, GPIO_PIN_SET);
    }
    led->led_state = LED_ON;
}

//熄灭LED
void led_turn_off(struct led_class *led)
{
    if(led->led_on_level == RESET)
    {
        HAL_GPIO_WritePin(led->led_port, led->led_pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(led->led_port, led->led_pin, GPIO_PIN_RESET);
    }
    led->led_state = LED_OFF;
}

//切换LED状态
void led_toggle(struct led_class *led)
{
    if(led->led_state == LED_ON)
    {
        led_turn_off(led);
    }
    else
    {
        led_turn_on(led);
    }
}

//注册led
struct led_class led_init(GPIO_TypeDef *led_port, uint32_t led_pin, uint8_t led_on_level)
{
    struct led_class led_handle;

    led_handle.led_port = led_port;
    led_handle.led_pin = led_pin;
    led_handle.led_on_level = led_on_level;
    led_handle.led_state = RESET;

    return led_handle;
}

//打开所有LED，直接操纵硬件
void led_turn_on_all(void)
{
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
}

//关闭所有LED，直接操纵硬件
void led_turn_off_all(void)
{
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
}

void led_toggle_all(void)
{
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
}

struct led_class led_handle[led_num];

void hw_led_init(void)
{
    led_handle[led1] = led_init(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);   //注册LED
    led_handle[led2] = led_init(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);   //注册LED
}



