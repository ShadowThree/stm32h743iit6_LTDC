#ifndef _SDRAM__H_
#define _SDRAM__H_

#include "stm32h7xx_hal.h"

#define SDRAM_MODEREG_BURST_LENGTH_1							(uint16_t)0x0000
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL				(uint16_t)0x0000
#define SDRAM_MODEREG_CAS_LATENCY_2								(uint16_t)0x0020
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD			(uint16_t)0x0000
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE			(uint16_t)0x0200

#define EXT_SDRAM_ADDR		(0xC0000000)
#define EXT_SDRAM_SIZE		(32*1024*1024)		// 32MBytes

void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram);
uint32_t FMC_SDRAM_test(void);
#endif
