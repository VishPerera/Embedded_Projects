/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Vishwa Perera
 * @brief          : Executes Blinky LED
 ******************************************************************************
 * This program uses the concepts of Bit Fielding along with Structures
 * to blink Green LED at PB0 of STM Neulceo F413 development board.
 ******************************************************************************
 */

#include <stdint.h>
#include "memory_mapped.h"

int main(void)
{
	// --- Defining Register Addresses ---
	RCC_AHB1EN_R_t volatile *const pClkCtrl_Reg     = RCC_AHB1EN_REG;
	GPIOx_MODE_R_t volatile *const pPortB_Mode_Reg  = GPIOx_MODE_REG;
	GPIOx_OD_R_t   volatile *const pPortB_Out_Reg   = GPIOx_OD_REG;

	//1. enable the clock for GPOIB peripheral in the AHB1ENR (SET bit 1 position)
	pClkCtrl_Reg -> gpiob_en = CLOCK_ENABLE;

	//2. configure the mode of the IO pin as output
	pPortB_Mode_Reg -> pin_0 = PIN_MODE_OUTPUT;

	while(1)
	{
		// 3. Set bit 0 to high to turn on PB0 Green LED
		pPortB_Out_Reg -> pin_0  = PIN_STATE_HIGH;

		// Add a small software delay. Loop for 300k times
		for(uint32_t i=0 ; i < DELAY_COUNT ; i++ );

		// 4. Clear bit 0 to high to turn off PB0 Green LED
		pPortB_Out_Reg -> pin_0  = PIN_STATE_LOW;

		for(uint32_t i=0 ; i < DELAY_COUNT ; i++ );
	}

	for(;;); // Hangs the program
}
