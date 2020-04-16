#include "sdram.h"

static  GPIO_TypeDef * const GPIOInitTable[] = {
    GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOG, GPIOG,
    GPIOD, GPIOD, GPIOD, GPIOD, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE,
    GPIOD, GPIOD, GPIOD,
    GPIOB, GPIOB, GPIOC, GPIOE, GPIOE, GPIOF, GPIOG, GPIOG, GPIOG, GPIOG,
    0
};
static uint8_t const PINInitTable[] = {
    0, 1, 2, 3, 4, 5, 12, 13, 14, 15, 0, 1,
    14, 15, 0, 1, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    8, 9, 10,
    5, 6, 0, 0, 1, 11, 4, 5, 8, 15,
    0
};

void SDRAM_Init(void)
{
  uint32_t tmp;

   uint32_t i = 0;



  while(GPIOInitTable[i] != 0){
    gpio_conf(GPIOInitTable[i], PINInitTable[i],  MODE_AF, TYPE_PUSHPULL, SPEED_100MHz, PULLUP_NONE, 12);
    i++;
  }
  // Enable clock for FMC
  RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;
  // Initialization step 1
  FMC_Bank5_6->SDCR[0] = FMC_SDCR1_SDCLK_1 | FMC_SDCR1_RBURST | FMC_SDCR1_RPIPE_1;
  FMC_Bank5_6->SDCR[1] = FMC_SDCR1_NR_0 | FMC_SDCR1_MWID_0 | FMC_SDCR1_NB | FMC_SDCR1_CAS;
  // Initialization step 2
  FMC_Bank5_6->SDTR[0] = TRC(7) | TRP(2);
  FMC_Bank5_6->SDTR[1] = TMRD(2) | TXSR(7) | TRAS(4) | TWR(2) | TRCD(2);
  // Initialization step 3
  while(FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);
  FMC_Bank5_6->SDCMR = 1 | FMC_SDCMR_CTB2 | (1 << 5);
  // Initialization step 4
  for(tmp = 0; tmp < 1000000; tmp++);
  // Initialization step 5
  while(FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);
  FMC_Bank5_6->SDCMR = 2 | FMC_SDCMR_CTB2 | (1 << 5);
  // Initialization step 6
  while(FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);
  FMC_Bank5_6->SDCMR = 3 | FMC_SDCMR_CTB2 | (4 << 5);
  // Initialization step 7
  while(FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);
  FMC_Bank5_6->SDCMR = 4 | FMC_SDCMR_CTB2 | (1 << 5) | (0x231 << 9);
  // Initialization step 8
  while(FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);
  FMC_Bank5_6->SDRTR |= (683 << 1);
  while(FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);
  // Clear SDRAM or fill with some pattern/color
  for(tmp = SDRAM_BASE; tmp < (SDRAM_BASE + SDRAM_SIZE); tmp += 4)
    *((uint32_t *)tmp) = 0x00000000;
}