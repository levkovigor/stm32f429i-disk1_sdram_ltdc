#ifndef __LTDC_H__
#define __LTDC_H__

#include "gpio_conf.h"
#include "sdram.h"
#include "stm32f4xx.h"

#define LCD_WIDTH     240    //Vadr
#define LCD_HEIGHT    320   //Hadr

#define HFP   10
#define HSYNC  10
#define HBP   20

#define VFP   4
#define VSYNC   2
#define VBP   2

#define ACTIVE_W (HSYNC + LCD_WIDTH + HBP - 1)
#define ACTIVE_H (VSYNC + LCD_HEIGHT + VBP - 1)

#define TOTAL_WIDTH  (HSYNC + HBP + LCD_WIDTH + HFP-1)   //horizontal period
#define TOTAL_HEIGHT (VSYNC + VBP + LCD_HEIGHT + VFP-1)  //vertical period

#define PIXELWIDHT 2


void TFTLCD_Init(void);

void PutPixel(uint16_t x, uint16_t y, uint16_t color);

 

#endif
