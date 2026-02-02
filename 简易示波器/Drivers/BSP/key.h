#ifndef __KEY_H__
#define __KEY_H__

#include "gpio.h"

enum{
    KEY1 = 1,
    KEY2,
    KEY3,
};

uint8_t Read_Key(void);
void Key_Handler(void);

#endif
