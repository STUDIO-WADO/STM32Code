#ifndef __HW_LED_H__
#define __HW_LED_H__

#include "gpio.h"

struct led_class
{
    uint8_t led_state;
    uint8_t led_on_level;
    uint16_t led_pin;
    GPIO_TypeDef *led_port;
};

enum led_instance
{
    led1 = 0,
    led2,
    led_num
};

#define LED_ON 0x01
#define LED_OFF 0x02

void led_turn_on(struct led_class *led);
void led_turn_off(struct led_class *led);
void led_toggle(struct led_class *led);
struct led_class led_init(GPIO_TypeDef *led_port, uint32_t led_pin, uint8_t led_on_level);

//不做封装，直接根据引脚来
void led_turn_on_all(void);
void led_turn_off_all(void);
void led_toggle_all(void);

extern struct led_class led_handle[led_num];
void hw_led_init(void);

#endif
