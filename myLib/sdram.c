#include "sdram.h"

extern SDRAM_HandleTypeDef hsdram1;
uint32_t volatile SDRAMBuf[EXT_SDRAM_SIZE] __attribute__((at(EXT_SDRAM_ADDR))) = {0};

HAL_StatusTypeDef SDRAM_Send_Cmd(uint8_t bank, uint8_t cmd, uint8_t refresh, uint16_t regval)
{
	uint32_t target_bank = 0;
	FMC_SDRAM_CommandTypeDef Command;
	
	if(bank == 0) {
		target_bank = FMC_SDRAM_CMD_TARGET_BANK1;
	} else if(bank == 1) {
		target_bank = FMC_SDRAM_CMD_TARGET_BANK2;
	}
	
	Command.CommandMode = cmd;
	Command.CommandTarget = target_bank;
	Command.AutoRefreshNumber = refresh;
	Command.ModeRegisterDefinition = regval;
	
	return HAL_SDRAM_SendCommand(&hsdram1, &Command, 0xFFFF);
}

void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram)
{
	uint32_t temp = 0;

	SDRAM_Send_Cmd(0,FMC_SDRAM_CMD_CLK_ENABLE,1,0);
	HAL_Delay(1);
	
	SDRAM_Send_Cmd(0,FMC_SDRAM_CMD_PALL,1,0);
	SDRAM_Send_Cmd(0,FMC_SDRAM_CMD_AUTOREFRESH_MODE,8,0);

	temp = (uint32_t)	SDRAM_MODEREG_BURST_LENGTH_1 					|
										SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL 	|
										SDRAM_MODEREG_CAS_LATENCY_2						|
										SDRAM_MODEREG_OPERATING_MODE_STANDARD |
										SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	SDRAM_Send_Cmd(0,FMC_SDRAM_CMD_LOAD_MODE,1,temp);
}

uint32_t FMC_SDRAM_test(void)
{
	for(uint32_t i = 0; i < EXT_SDRAM_SIZE/sizeof(uint32_t); i += 16*1024) {
		SDRAMBuf[i] = i;
	}
	
	for(uint32_t i = 0; i < EXT_SDRAM_SIZE/sizeof(uint32_t); i += 16*1024) {
		if(SDRAMBuf[i] != i) {
			return i+1;
		}
	}
	return 0;
}
