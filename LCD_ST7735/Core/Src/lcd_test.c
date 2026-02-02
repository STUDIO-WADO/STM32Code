#include "lcd_test.h"
#include "spi.h"

// 使用你提供的颜色宏
uint16_t test_colors[] = {
    WHITE, BLACK, BLUE, BRED, GRED, GBLUE, RED, MAGENTA,
    GREEN, CYAN, YELLOW, BROWN, BRRED, GRAY, DARKBLUE, LIGHTBLUE,
    GRAYBLUE, LIGHTGREEN, LGRAY, LGRAYBLUE, LBBLUE
};
uint8_t color_count = sizeof(test_colors) / sizeof(test_colors[0]);

void LCD_Fill_Test(void)
{
    for(uint8_t i = 0; i < color_count; i++)
    {
        // 等待 SPI 空闲，确保 DMA 可用
        while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

        // 全屏填充
        LCD_Fill(0, 0, LCD_W, LCD_H, test_colors[i]);

        HAL_Delay(500); // 每个颜色停 0.5 秒，可根据需要调整
    }

    // 可选：测试局部矩形填充
    while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
    LCD_Fill(LCD_W/4, LCD_H/4, LCD_W*3/4, LCD_H*3/4, RED);
    HAL_Delay(500);

    while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
    LCD_Fill(LCD_W/4, LCD_H/4, LCD_W/2, LCD_H/2, GREEN);
    HAL_Delay(500);
}


void LCD_DrawPoint_Test(void)
{

    // 1. 测试屏幕四角 + 中心点
    LCD_DrawPoint(0, 0, RED);                 // 左上角
    LCD_DrawPoint(LCD_W-1, 0, RED);          // 右上角
    LCD_DrawPoint(0, LCD_H-1, RED);           // 左下角
    LCD_DrawPoint(LCD_W-1, LCD_H-1, BRED);     // 右下角
    LCD_DrawPoint(LCD_W/2, LCD_H/2, RED);     // 屏幕中心

    HAL_Delay(200); // 适当延时观察

    // 2. 横向线条测试
    for(uint16_t x = 0; x < 128; x += 4)
    {
        LCD_DrawPoint(x, 40, RED);
        LCD_DrawPoint(x, 50, RED);
        LCD_DrawPoint(x, 60, RED);
        LCD_DrawPoint(x, 70, RED);
    }

    HAL_Delay(200);

    // 3. 纵向线条测试
    for(uint16_t y = 0; y < 160; y += 4)
    {
        LCD_DrawPoint(30, y, YELLOW);
        LCD_DrawPoint(40, y, BROWN);
        LCD_DrawPoint(50, y, BRRED);
        LCD_DrawPoint(60, y, GRAY);
    }

    HAL_Delay(200);

    // 4. 斜线测试
    for(uint16_t i = 0; i < 128 && i < 160; i += 4)
    {
        LCD_DrawPoint(i, i, DARKBLUE);
        LCD_DrawPoint(i, 159 - i, LIGHTBLUE);
    }

    HAL_Delay(200);

    // 5. 中间区域小方块测试
    for(uint16_t x = 50; x < 80; x++)
    {
        for(uint16_t y = 60; y < 90; y++)
        {
            LCD_DrawPoint(x, y, LGRAYBLUE);
        }
    }

    HAL_Delay(200);
}

void LCD_DrawLine_Test(void)
{
    uint8_t i;

    // 1 画横线
    for(i = 0; i < color_count && i < LCD_H; i++)
    {
        LCD_DrawLine(0, i*2, LCD_W-1, i*2, test_colors[i]);
        HAL_Delay(50); // 观察颜色变化
    }

    HAL_Delay(200);

    // 2 画竖线
    for(i = 0; i < color_count && i < LCD_W; i++)
    {
        LCD_DrawLine(i*2, 0, i*2, LCD_H-1, test_colors[i]);
        HAL_Delay(50);
    }

    HAL_Delay(200);

    // 3 画四条屏幕对角线
    LCD_DrawLine(0, 0, LCD_W-1, LCD_H-1, RED);        // 左上到右下
    LCD_DrawLine(0, LCD_H-1, LCD_W-1, 0, GREEN);      // 左下到右上
    LCD_DrawLine(LCD_W/2, 0, LCD_W/2, LCD_H-1, BLUE); // 屏幕中心竖线
    LCD_DrawLine(0, LCD_H/2, LCD_W-1, LCD_H/2, CYAN); // 屏幕中心横线

    HAL_Delay(500);

    // 4 画放射状多彩线（中心向四周）
    uint16_t cx = LCD_W / 2;
    uint16_t cy = LCD_H / 2;
    for(i = 0; i < color_count; i++)
    {
        LCD_DrawLine(cx, cy, i*5 < LCD_W ? i*5 : LCD_W-1, 0, test_colors[i]);
        LCD_DrawLine(cx, cy, 0, i*5 < LCD_H ? i*5 : LCD_H-1, test_colors[i]);
        LCD_DrawLine(cx, cy, i*5 < LCD_W ? i*5 : LCD_W-1, LCD_H-1, test_colors[i]);
        LCD_DrawLine(cx, cy, LCD_W-1, i*5 < LCD_H ? i*5 : LCD_H-1, test_colors[i]);
    }
}

void LCD_DrawRectangle_Test(void)
{
    uint8_t i;
    uint16_t step_w = LCD_W / 6;  // 每个矩形宽度步长
    uint16_t step_h = LCD_H / 6;  // 每个矩形高度步长

    // 1 从大到小画嵌套矩形
    for(i = 0; i < 5; i++)
    {
        uint16_t x1 = i * step_w / 2;
        uint16_t y1 = i * step_h / 2;
        uint16_t x2 = LCD_W - 1 - i * step_w / 2;
        uint16_t y2 = LCD_H - 1 - i * step_h / 2;

        LCD_DrawRectangle(x1, y1, x2, y2, test_colors[i]);
        HAL_Delay(200);  // 每个矩形停留 0.2 秒
    }

    HAL_Delay(300);

    // 2 在屏幕中心画多彩矩形
    uint16_t cx = LCD_W / 2;
    uint16_t cy = LCD_H / 2;
    for(i = 0; i < color_count; i++)
    {
        uint16_t x1 = (cx - 20 + i) < LCD_W ? cx - 20 + i : 0;
        uint16_t y1 = (cy - 20 + i) < LCD_H ? cy - 20 + i : 0;
        uint16_t x2 = (cx + 20 - i) < LCD_W ? cx + 20 - i : LCD_W-1;
        uint16_t y2 = (cy + 20 - i) < LCD_H ? cy + 20 - i : LCD_H-1;

        LCD_DrawRectangle(x1, y1, x2, y2, test_colors[i]);
        HAL_Delay(50);
    }
}

void Draw_Circle_Test(void)
{
    uint8_t i;
    
    // 清屏为黑色，便于观察
    LCD_Fill(0, 0, LCD_W, LCD_H, BLACK);
    HAL_Delay(200);

    // 在屏幕中心画不同半径的彩色圆
    uint16_t cx = LCD_W / 2;
    uint16_t cy = LCD_H / 2;
    uint8_t max_radius = (LCD_W < LCD_H ? LCD_W : LCD_H) / 2 - 5; // 最大半径适应屏幕

    for(i = 0; i < color_count; i++)
    {
        uint8_t radius = 5 + (i * max_radius / color_count); // 半径从小到大
        Draw_Circle(cx, cy, radius, test_colors[i]);
        HAL_Delay(150); // 停留观察
    }

    HAL_Delay(300);

    // 在屏幕四角画小圆
    Draw_Circle(10, 10, 5, RED);
    Draw_Circle(LCD_W-10, 10, 5, GREEN);
    Draw_Circle(10, LCD_H-10, 5, BLUE);
    Draw_Circle(LCD_W-10, LCD_H-10, 5, YELLOW);
}
