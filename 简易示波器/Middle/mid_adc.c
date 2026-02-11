#include "mid_adc.h"
#include "adc.h"

static uint8_t adc_convert_bit = ADC_CONVERT_UN_FINSIH;

/*
 * 函数内容；得到ADC通道的平均值值
 * 函数参数：无
 * 返回值：无
 */
uint16_t Get_ADC_Average(uint16_t num)
{
    uint16_t i = 0,val = 0;
    uint32_t sum_val = 0;
    uint16_t max_value = 0,min_value = 9999;
    for(i =0;i<num;i++)
    {
        val = Get_ADC_Val();
        if(min_value > val){
            min_value = val;
        }
        if(max_value < val){
            max_value = val;
        }
        sum_val = sum_val + val;
    }
    sum_val = sum_val - max_value - min_value;
    sum_val = sum_val / (num - 2);
    return sum_val;
}
