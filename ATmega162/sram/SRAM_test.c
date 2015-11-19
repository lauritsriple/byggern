/*
 * SRAM_test.c
 *
 * Created: 11.09.2015 12:02:24
 *  Author: shahrukk
 */ 
#include <stdlib.h> 
#include <avr/io.h>
#include <stdio.h>
#include "SRAM_test.h"

uint8_t * SRAM_test(void)
{
	uint8_t * errors;
	errors=(uint8_t*) malloc(2*sizeof(uint8_t));
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size       = 0x800;
	uint16_t write_errors       = 0;
	uint16_t retrieval_errors   = 0;

	//printf("Starting SRAM test...\n");

	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();

	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			//printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}

	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);    // reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			//printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	//printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
	errors[0]=write_errors;
	errors[1]=retrieval_errors;
	return errors; 
}



/*
void SRAM_testADC(void){
	volatile char *ext_ram = (char *) 0x1400; // Start address for the adc
	uint8_t retreived_valuex = ext_ram[0x0];
	uint8_t retreived_valuey = ext_ram[0x1];
	printf("x-value: %4d , y-value: %4d\n",retreived_valuex, retreived_valuey);	
}*/


