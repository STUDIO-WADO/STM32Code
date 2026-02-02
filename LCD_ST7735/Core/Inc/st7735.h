#ifndef __ST7735_H__
#define __ST7735_H__

#include "gpio.h"

#define USE_HORIZONTAL 2  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif

#if 0
/* RES */
#define LCD_RES_Clr()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET)
#define LCD_RES_Set()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET)

/* DC */
#define LCD_DC_Clr()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET)
#define LCD_DC_Set()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET)

/* CS */
#define LCD_CS_Clr()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET)
#define LCD_CS_Set()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET)

/* BLK(背光) */
#define LCD_BLK_Clr()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define LCD_BLK_Set()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

#else

/* RES */
#define LCD_RES_Clr()  HAL_GPIO_WritePin(ST7735_RES_GPIO_Port, ST7735_RES_Pin, GPIO_PIN_RESET)
#define LCD_RES_Set()  HAL_GPIO_WritePin(ST7735_RES_GPIO_Port, ST7735_RES_Pin, GPIO_PIN_SET)

/* DC */
#define LCD_DC_Clr()   HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_RESET)
#define LCD_DC_Set()   HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_SET)

/* CS */
#define LCD_CS_Clr()   HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET)
#define LCD_CS_Set()   HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_SET)

/* BLK(背光) */
#define LCD_BLK_Clr()  HAL_GPIO_WritePin(ST7735_BL_GPIO_Port, ST7735_BL_Pin, GPIO_PIN_RESET)
#define LCD_BLK_Set()  HAL_GPIO_WritePin(ST7735_BL_GPIO_Port, ST7735_BL_Pin, GPIO_PIN_SET)

#endif
void LCD_RESET(void);
void LCD_Writ_Bus(uint8_t dat);
void LCD_WR_DATA8(uint8_t dat);
void LCD_WR_DATA(uint16_t dat);
void LCD_WR_REG(uint8_t dat);
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void LCD_Init(void);

void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);
void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
uint32_t mypow(uint8_t m,uint8_t n);
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);
void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[]);


//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

#endif
