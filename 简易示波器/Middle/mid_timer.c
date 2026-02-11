#include "mid_timer.h"
#include "hw_key.h"
#include "hw_ec11.h"

static __IO uint16_t key_timer_value;			//按键定时器
static __IO uint16_t tft_timer_value;			//屏幕定时器
static uint8_t key_timer_bit = RUN_MS_TIMER;		//ms定时器标志位
static uint8_t tft_timer_bit = RUN_MS_TIMER;		//ms定时器标志位

//开启输入捕获
void ic_tim3_start(void)
{
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
}

//停止输入捕获
void ic_tim3_stop(void)
{
    HAL_TIM_IC_Stop_IT(&htim3, TIM_CHANNEL_1);
}

//开启定时器4
void tim4_start(void)
{
    HAL_TIM_Base_Start_IT(&htim4);
}

//停止定时器4
void tim4_stop(void)
{
    HAL_TIM_Base_Stop_IT(&htim4);
}

/**
  * @brief 定时器更新中断回调函数(每1ms调用一次)
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM4)
    {
        if(key_timer_bit == RUN_MS_TIMER)
        {
            key_timer_value++;
            if(key_timer_value >= 10000){
                key_timer_value = 0;		//防止数据越界
            }
        }

        if(tft_timer_bit == RUN_MS_TIMER)
        {
            tft_timer_value++;
            if(tft_timer_value >= 10000){
                tft_timer_value = 0;		//防止数据越界
            }
        }
    }


}

/*
 * 函数内容：得到按键定时器值
 * 函数参数：无
 * 返回值：uint16_t -- 定时器值
 */
uint16_t get_key_timer_value(void)
{
	return key_timer_value;
}

/*
 * 函数内容：设置按键定时器值
 * 函数参数：无
 * 返回值：uint16_t -- 定时器值
 */
void set_key_timer_value(uint16_t value)
{
	key_timer_value =  value;
}

/*
 * 函数内容：设置按键定时器标志位值
 * 函数参数：uint8_t value
 * 返回值：无
 */
void set_key_bit_value(uint8_t value)
{
	key_timer_bit = value;
}

/*
 * 函数内容：得到屏幕定时器值
 * 函数参数：无
 * 返回值：uint16_t -- 定时器值
 */
uint16_t get_tft_timer_value(void)
{
	return tft_timer_value;
}

/*
 * 函数内容：设置屏幕定时器值
 * 函数参数：无
 * 返回值：uint16_t -- 定时器值
 */
void set_tft_timer_value(uint16_t value)
{
	tft_timer_value =  value;
}

/*
 * 函数内容：设置屏幕定时器标志位值
 * 函数参数：uint8_t value
 * 返回值：无
 */
void set_tft_bit_value(uint8_t value)
{
	tft_timer_bit = value;
}

//ec11外部中断回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == EC11_A_Pin)
    {
        ec11_exti_callback(&ec11_handle);
    }
}

static __IO uint16_t ccnumber = 0;						//捕获次数
static __IO uint32_t freq = 0;							//频率值
static __IO uint16_t readvalue1 = 0, readvalue2 = 0;	//两次捕获值
static __IO uint32_t count = 0;							//周期间隔时长

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
        if(ccnumber == 0)  // 第一次捕获
        {
            // 读取第一次捕获值
            readvalue1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            ccnumber = 1;
        }
        else if(ccnumber == 1)  // 第二次捕获
        {
            // 读取第二次捕获值
            readvalue2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            
            // 计算两次捕获的时间差
            if(readvalue2 > readvalue1)
            {
                count = (readvalue2 - readvalue1);
            }
            else  // 处理溢出情况
            {
                count = ((0xFFFFU - readvalue1) + readvalue2);
            }
            
            // 计算频率
            // 定时器频率: 1MHz, 频率 = 1000000 / count
            freq = 1000000U / count;			
			readvalue1 = 0;readvalue2 = 0;
			ccnumber = 0;
			count=0;
        }
    }
}

/*
 * 函数内容：得到频率值
 * 函数参数：无
 * 返回值：uint32_t -- 频率值
 */
uint32_t get_freq_value(void)
{
	return freq;
}

