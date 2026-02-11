#ifndef _HW_EC11_H__
#define _HW_EC11_H__

#include "gpio.h"

struct ec11_class
{
	GPIO_TypeDef *ec11_Aport;		//EC11的A端口
    uint16_t ec11_Apin;					//EC11的A引脚
	GPIO_TypeDef *ec11_Bport;		//EC11的B端口
	uint16_t ec11_Bpin;					//EC11的B引脚
	uint8_t ec11_direction;			//EC11的方向

    int16_t ec11_count;
};

#define ec11_forward 	0x01		//正转
#define ec11_reversal   0x02		//反转
#define ec11_static		0x03		//禁止

extern struct ec11_class ec11_handle;

struct ec11_class ec11_init(GPIO_TypeDef *ec11_Aport, uint16_t ec11_Apin, GPIO_TypeDef *ec11_Bport, uint16_t ec11_Bpin);
void hw_ec11_init(void);
void ec11_exti_callback(struct ec11_class *handle);

#endif
