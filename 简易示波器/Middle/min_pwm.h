#ifndef _MIN_PWM_H__
#define _MIN_PWM_H__

#include "gpio.h"
#include "tim.h"

#define PWM_ON 	0x01		//PWM输出打开
#define PWM_OFF 0x02		//PWM输出关闭
#define TIMER_FREQ 1000000	//PWM输出定时器频率

void set_pwm_duty(uint16_t duty);
uint16_t get_pwm_duty(void);
void set_pwm_period(uint16_t period);
uint16_t get_pwm_period(void);
void set_pwm_state(uint8_t state);
uint8_t get_pwm_state(void);
uint16_t get_pwm_out_freq(void);

#endif
