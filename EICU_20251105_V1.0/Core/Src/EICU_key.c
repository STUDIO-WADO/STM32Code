#include "EICU_key.h"

#define DELAY_TIME  500
#define PRESS_KEY(fn)  do { fn(0); HAL_Delay(DELAY_TIME); fn(1); HAL_Delay(DELAY_TIME); } while(0)
#define DIALING_MAP_SIZE sizeof(dialing_map)/sizeof(dialing_map[0])
#define KEY_NUM_SIZE 5
#define DEBOUNCE_MS 50

uint8_t Key_Num_Flag;
uint8_t Key_Num_Buff[KEY_NUM_SIZE];
/*------------------测试----------------------*/
uint8_t out_num1;
uint8_t out_num2;
uint8_t out_num3;
uint8_t out_num4;
/*--------------------------------------------*/

typedef enum {
    CH_IDLE = 0,        // 空闲
    CH_DEBOUNCE_PRESS,  // 按下去抖
    CH_DIALING,         // 拨号动作
    CH_IN_CALL,         // 通话中
    CH_DEBOUNCE_RELEASE,// 松开去抖
} EICU_ChannelState_t;

typedef void (*LED_Func_t)(uint8_t on);

typedef struct {
    LED_Func_t led_ctrl;
    uint8_t dial_code;
    GPIO_TypeDef *port;
    uint16_t pin;

    EICU_ChannelState_t state;
    uint32_t debounce_ts;

    uint8_t blinking;        // 是否处于闪烁期
} EICU_Channel_t;

static EICU_Channel_t EICU_Channels[] =
{
    {LED_1, 0x61, OUT_1_GPIO_Port, OUT_1_Pin, CH_IDLE, 0},
    {LED_2, 0x61, OUT_2_GPIO_Port, OUT_2_Pin, CH_IDLE, 0},
    {LED_3, 0x61, OUT_3_GPIO_Port, OUT_3_Pin, CH_IDLE, 0},
    {LED_4, 0x61, OUT_4_GPIO_Port, OUT_4_Pin, CH_IDLE, 0},
};

static inline uint8_t CH_Read(const EICU_Channel_t *ch)
{
    return HAL_GPIO_ReadPin(ch->port, ch->pin) == GPIO_PIN_SET;
}

static inline uint8_t EICU_IsDialMode(void)
{
    return (LED_MT == GPIO_PIN_SET);
}

static void EICU_Channel_FSM(EICU_Channel_t *ch)
{
    switch(ch->state)
    {
    case CH_IDLE:
        if(CH_Read(ch))
        {
            ch->debounce_ts = HAL_GetTick();
            ch->state = CH_DEBOUNCE_PRESS;
        }
        break;

    case CH_DEBOUNCE_PRESS:
    if(CH_Read(ch) && (HAL_GetTick() - ch->debounce_ts >= DEBOUNCE_MS))
    {
        // 启动LED闪烁任务，只执行一次
        if(ch->blinking == 0)
        {
            ch->blinking = 1;
            xTaskCreate(task_led_blink_5s,
                        "ledBlink5s",
                        128,               
                        (void*)ch,         
                        2,                 
                        NULL);
        }
        ch->state = CH_DIALING;
    }
    else if(!CH_Read(ch))
    {
        ch->state = CH_IDLE;
    }
    break;

    case CH_DIALING:
        if(EICU_IsDialMode()) // 已经拨号 / 通话状态
        {
            ch->state = CH_IN_CALL;
            break;
        }

        // 拨号
        Key_Num_Buff[0]=0xDC; Key_Num_Buff[1]=0x68;
        Key_Num_Buff[2]=0x60; Key_Num_Buff[3]=0x60;
        Key_Num_Buff[4]=ch->dial_code;
        
        Key_Num_Flag = 1;
        EICU_Start_Num(Key_Num_Buff);
        ch->state = CH_IN_CALL;
        break;

    case CH_IN_CALL:
        if(!CH_Read(ch))
        {
            ch->debounce_ts = HAL_GetTick();
            ch->state = CH_DEBOUNCE_RELEASE;
        }
        break;

    case CH_DEBOUNCE_RELEASE:
        if(!CH_Read(ch) && (HAL_GetTick() - ch->debounce_ts >= DEBOUNCE_MS))
        {
            ch->led_ctrl(0); // LED OFF

            if(EICU_IsDialMode())
                PRESS_KEY(KEY_MT); // 挂断

            ch->state = CH_IDLE;
        }
        else if(CH_Read(ch))
        {
            ch->state = CH_IN_CALL;
        }
        break;
    }
}

void EICU_Main_Loop(void)
{
    for(int i = 0; i < (sizeof(EICU_Channels)/sizeof(EICU_Channels[0])); i++)
    {
        EICU_Channel_FSM(&EICU_Channels[i]);
    }
}

void task_led_blink_5s(void *pvParameters)
{
    EICU_Channel_t *ch = (EICU_Channel_t *)pvParameters;
    TickType_t start = xTaskGetTickCount();

    while((xTaskGetTickCount() - start) < pdMS_TO_TICKS(5000))
    {
        ch->led_ctrl(1);
        vTaskDelay(pdMS_TO_TICKS(500));
        ch->led_ctrl(0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    ch->led_ctrl(1);

    ch->blinking = 0; // 清标志位
    
    vTaskDelete(NULL); // 自杀，释放任务栈
}


//test
uint8_t test_call_state;

/*------------------拨号驱动----------------------*/
typedef void (*KeyFunc)(uint8_t);

typedef struct {
    uint8_t code;
    KeyFunc  key_func;
} DialingMap;

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
};

void EICU_Start_Num(uint8_t *num_buff)
{
    if(Key_Num_Flag)
    {
        if(num_buff[0] == 0) return;
        
        for(uint8_t i = 0;i < KEY_NUM_SIZE;i++)
        {
            int matched = 0;
            for(uint8_t j = 0;j < DIALING_MAP_SIZE;j++)
            {
                if(num_buff[i] == dialing_map[j].code)
                {
                    PRESS_KEY(dialing_map[j].key_func);
                    matched = 1;
                    break;
                }
            }
            num_buff[i] = 0;
            if (!matched)
            {
                num_buff[0] = 0;  // 清空拨号缓冲区
                return;
            }
        }

        Key_Num_Flag = 0;
    }
}
/*-----------------------------------------------------------*/


//电话通话状态测试
void EICU_Test_Call_State(void)
{
    if(LED_MT == GPIO_PIN_SET)
    {
        // 通话中
        test_call_state = 1;
    }
    else
    {
        // 挂机状态
        test_call_state = 0;
    }
}


/* -------------------------------------KEY-------------------------------------------------- */
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
}   // MT

/* -------------------------------------LED-------------------------------------------------- */

void LED_1(uint8_t x) {
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, x ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void LED_2(uint8_t x) {
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, x ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void LED_3(uint8_t x) {
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, x ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void LED_4(uint8_t x) {
    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, x ? GPIO_PIN_RESET : GPIO_PIN_SET);
}






















