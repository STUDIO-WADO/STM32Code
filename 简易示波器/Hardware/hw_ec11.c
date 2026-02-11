#include "hw_ec11.h"

struct ec11_class ec11_init(GPIO_TypeDef *ec11_Aport, uint16_t ec11_Apin, GPIO_TypeDef *ec11_Bport, uint16_t ec11_Bpin)
{
    struct ec11_class handle;

    handle.ec11_Aport = ec11_Aport;
    handle.ec11_Apin = ec11_Apin;
    handle.ec11_Bport = ec11_Bport;
    handle.ec11_Bpin = ec11_Bpin;
    handle.ec11_direction = ec11_static;  // 初始状态为静止
    handle.ec11_count = 0;  // 计数器清零

    return handle;
}

struct ec11_class ec11_handle;

void hw_ec11_init(void)
{
    ec11_handle = ec11_init(EC11_A_GPIO_Port, EC11_A_Pin, EC11_B_GPIO_Port, EC11_B_Pin);
}


void ec11_exti_callback(struct ec11_class *handle)
{
    static uint8_t cnt = 0;
    static uint8_t b_value = 0;

    if((HAL_GPIO_ReadPin(handle->ec11_Aport, handle->ec11_Apin) == GPIO_PIN_RESET) && (cnt == 0))
    {
        cnt++;
        b_value = 0;

        if(HAL_GPIO_ReadPin(handle->ec11_Bport, handle->ec11_Bpin) == GPIO_PIN_SET)
        {
            b_value = 1;
        }
    }
    // ===== A相上升沿(第二次触发) =====
    else if((HAL_GPIO_ReadPin(handle->ec11_Aport, handle->ec11_Apin) == GPIO_PIN_SET) && (cnt == 1))
    {
        cnt = 0;

        // 判断B相变化趋势
        // 情况1: B相从高变低 → 反转
        if((HAL_GPIO_ReadPin(handle->ec11_Bport, handle->ec11_Bpin) == GPIO_PIN_RESET) && (b_value == 1))
        {
            handle->ec11_direction = ec11_reversal;
            handle->ec11_count--;
        }
        // 情况2: B相从低变高 → 正转
        else if((HAL_GPIO_ReadPin(handle->ec11_Bport, handle->ec11_Bpin) == GPIO_PIN_SET) && (b_value == 0))
        {
            handle->ec11_direction = ec11_forward;
            handle->ec11_count++;
        }
    }
}
