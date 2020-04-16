#ifndef __SDRAM_H__
#define __SDRAM_H__

#include "gpio_conf.h"
#include "stm32f4xx.h"

// SDRAM base address for Bank 2
#define SDRAM_BASE 0xD0000000
// SDRAM size is 8MB
#define SDRAM_SIZE 0x00800000

#define SDRAM_START_ADR             (uint32_t)0xD0000000

#define TMRD(x) (x << 0)  /* Load Mode Register to Active */
#define TXSR(x) (x << 4)  /* Exit Self-refresh delay */
#define TRAS(x) (x << 8)  /* Self refresh time */
#define TRC(x)  (x << 12) /* Row cycle delay */
#define TWR(x)  (x << 16) /* Recovery delay */
#define TRP(x)  (x << 20) /* Row precharge delay */
#define TRCD(x) (x << 24) /* Row to column delay */


#define SDRAM_Write8(address, value)    (*(__IO uint8_t *) (SDRAM_START_ADR + (address)) = (value))

#define SDRAM_Read8(address)       (*(__IO uint8_t *) (SDRAM_START_ADR + (address)))

#define SDRAM_Write16(address, value)    (*(__IO uint16_t *) (SDRAM_START_ADR + (address)) = (value))

#define SDRAM_Read16(address)       (*(__IO uint16_t *) (SDRAM_START_ADR + (address)))

#define SDRAM_Write32(address, value)    (*(__IO uint32_t *) (SDRAM_START_ADR + (address)) = (value))

#define SDRAM_Read32(address)       (*(__IO uint32_t *) (SDRAM_START_ADR + (address)))


void SDRAM_Init(void);

 

#endif
