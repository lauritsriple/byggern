/*
 * spi.c
 *
 * Created: 02.10.2015 10:11:20
 *  Author: shahrukk
 */ 

#include "spi.h"
#include <avr/io.h>

#if defined(__AVR_ATmega162__)
	#include "../ATmega162/board.h"
#elif defined(__AVR_ATmega2560__)
	#include "../ATmega2560/board.h"
#elif defined(__AVR_AT90USB1287__)
	#include "../AT90USB1287/board.h"
#endif



void spi_init(void){
	//SCK UT, MISO IN, MOSI UT, SS UT
	SPI_PORT |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_CS_MCP2515);
	SPI_PORT &= ~(1 << SPI_MISO);
	// NOT interrupt driven
	// mcp2515, max frequency is 10mhz
	// with external clock, F_CPU is defined to 4,9mhz. we divide by 4, so our sck is 1,2mhz
	SPCR= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

uint8_t spi_transmit(char data){
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}


