#include "ltdc.h"

static  GPIO_TypeDef * const GPIOInitTable[] = {
    GPIOC, GPIOB, GPIOA, GPIOA, GPIOB, GPIOG,
    GPIOA, GPIOG, GPIOB, GPIOB, GPIOC, GPIOD,
    GPIOD, GPIOG, GPIOG, GPIOA, GPIOB, GPIOB,
    GPIOA, GPIOC, GPIOF, GPIOG,
    0};

static uint8_t const PINInitTable[] = {
    10, 0, 11, 12, 1, 6,
    6, 10, 10, 11, 7, 3,
    6, 11, 12, 3, 8, 9,
    4, 6, 10, 7,
    0};

static uint8_t const  AFInitTable[] = {
    14, 9, 14, 14, 9, 14,
    14, 9, 14, 14, 14, 14,
    14, 14, 9, 14, 14, 14,
    14, 14, 14, 14,
    0};

void TFTLCD_Init(void)
{
  uint8_t i = 0;
  /* GPIO pin configuration */
  while(GPIOInitTable[i] != 0){
  gpio_conf(GPIOInitTable[i], PINInitTable[i], MODE_AF, TYPE_PUSHPULL, SPEED_100MHz, PULLUP_NONE, AFInitTable[i]);
    i++;
  }
  /* PLL  */
  RCC->PLLSAICFGR = (192 << 6) | (4 << 24) | (4 << 28) ;
  RCC->DCKCFGR = (RCC->DCKCFGR & ~RCC_DCKCFGR_PLLSAIDIVR) | (2 << 16);
  /* Enable SAI PLL */
  RCC->CR |= RCC_CR_PLLSAION;
  /* wait for SAI PLL ready */
  while((RCC->CR & RCC_CR_PLLSAIRDY) == 0);
  /* enable clock for LTDC */
  RCC->APB2ENR     |= RCC_APB2ENR_LTDCEN;
  /* Synchronization Size Configuration */
  LTDC->SSCR      = ((HSYNC - 1) << 16)   | (VSYNC - 1);
  /* Back Porch Configuration */
  LTDC->BPCR      = ((HBP - 1) << 16)   | (VBP - 1);
  /* Active Width Configuration */
  LTDC->AWCR      = (ACTIVE_W << 16)    | (ACTIVE_H);
  /* Total Width Configuration */
  LTDC->TWCR      = (TOTAL_WIDTH << 16)   | (TOTAL_HEIGHT);
  /* Window Horizontal Position Configuration */
  LTDC_Layer1->WHPCR  = HBP | ((HBP + LCD_WIDTH - 1) << 16);
  /* Window Vertical Position Configuration */
  LTDC_Layer1->WVPCR  = VBP | ((VBP + LCD_HEIGHT - 1) << 16);
  /* Pixel Format Configuration */
  LTDC_Layer1->PFCR   = 2;
  /* Color Frame Buffer Address */
  LTDC_Layer1->CFBAR  = SDRAM_BASE;
  /* Color Frame Buffer Length */
  LTDC_Layer1->CFBLR  = ((LCD_WIDTH * PIXELWIDHT) << 16) | ((LCD_WIDTH * PIXELWIDHT) + 3);
  /* Enable Layer */
  LTDC_Layer1->CR   = LTDC_LxCR_LEN;
  /* Immediate Reload */
  LTDC->SRCR      = LTDC_SRCR_IMR;
  /* Enable LTDC */
  LTDC->GCR       = LTDC_GCR_LTDCEN;
}

void PutPixel(uint16_t x, uint16_t y, uint16_t color)
{
  *((uint16_t *) (SDRAM_BASE + (x * PIXELWIDHT) + (y * (LCD_WIDTH * PIXELWIDHT)))) = color;
}