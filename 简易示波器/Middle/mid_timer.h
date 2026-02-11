#ifndef _MID_TIMER_H__
#define _MID_TIMER_H__

#include "tim.h"

#define PAUSE_MS_TIMER 0x01
#define RUN_MS_TIMER   0x02

void ic_tim3_start(void);
void ic_tim3_stop(void);
void tim4_start(void);
void tim4_stop(void);


#endif
