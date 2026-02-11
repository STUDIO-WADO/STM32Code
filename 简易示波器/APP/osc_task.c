#include "osc_task.h"
#include "st7735.h"

void TFT_StaticUI(void)
{
    uint16_t i = 0;

    char showData[32]={0};

    LCD_ShowChinese(10,0,(uint8_t *)"简易示波器",BLACK,GREEN,16,0);

    LCD_ShowString(110,0,(uint8_t *)showData,BLACK,YELLOW,16,0);

    LCD_ShowChinese(110,20,(uint8_t *)"输出状态",WHITE,PURPLE,12,0);

    LCD_ShowString(110,36,(uint8_t *)showData,BLACK,YELLOW,16,0);

    LCD_ShowChinese(110,56,(uint8_t *)"输出频率",WHITE,PURPLE,12,0);

    LCD_ShowString(110,72,(uint8_t *)showData,BLACK,YELLOW,16,0);

    LCD_ShowString(110,92,(uint8_t *)showData,WHITE,PURPLE,12,0);

    LCD_ShowChinese(118,92,(uint8_t *)"占空比",WHITE,PURPLE,12,0);

    LCD_ShowString(110,106,(uint8_t *)showData,BLACK,YELLOW,16,0);

    LCD_ShowChinese(5,92,(uint8_t *)"输入峰值",WHITE,PURPLE,12,0);

    LCD_ShowChinese(55,92,(uint8_t *)"输入频率",WHITE,PURPLE,12,0);

    for(i=0;i<=128;i=i+2)
    {
        LCD_DrawPoint(106,i,YELLOW);
    }
    
    for(i=0;i<100;i++)
    {
        LCD_DrawPoint(i,81,GREEN);
    }
    for(i=30;i<=80;i++)
    {
        LCD_DrawPoint(0,i,GREEN);
    }
    for(i=0;i<10;i++)
    {
        LCD_DrawPoint((i*10)+2,82,GREEN); 
        LCD_DrawPoint((i*10)+3,82,GREEN); 
    }
    for(i=0;i<10;i++)
    {
        LCD_DrawPoint((i*10)+2,83,GREEN); 
        LCD_DrawPoint((i*10)+3,83,GREEN);
    }
}




