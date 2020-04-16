#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include "gpio_conf.h"
#include "sdram.h"
#include "ltdc.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(PC2, PD13, PF9, PF7, -1, PF8);

void SPI_Init(void)
{
__GPIOC_CLK_ENABLE();
__GPIOD_CLK_ENABLE();
__GPIOF_CLK_ENABLE();
GPIO_InitTypeDef GPIO_InitStruct;
GPIO_InitStruct.Pin = GPIO_PIN_2;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
GPIO_InitStruct.Pin = GPIO_PIN_13;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
GPIO_InitStruct.Alternate = GPIO_AF5_SPI5;
HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}

void setup() {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN |
          RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN |
          RCC_AHB1ENR_GPIOGEN;
  SDRAM_Init();
  SPI_Init();
  Serial.begin(9600);
  Serial.println("Touch Paint!");
  tft.begin_ltdc();
  TFTLCD_Init();
}

void loop() {
   for (int i = 0; i <= 240; i++){
      for (int j = 0; j <= 320; j++){
        PutPixel(i, j, ILI9341_BLACK);
  }
  }
   delay(1000);
   for (int i = 0; i <= 240; i++){
      for (int j = 0; j <= 320; j++){
        PutPixel(i, j, ILI9341_BLUE);
  }
  }
    delay(1000);
   for (int i = 0; i <= 240; i++){
      for (int j = 0; j <= 320; j++){
        PutPixel(i, j, ILI9341_RED);
  }
  }
  delay(1000);
}
