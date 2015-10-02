/*
 * spi.c
 *
 * Created: 02.10.2015 10:11:20
 *  Author: shahrukk
 */ 

#include "spi.h"
#include <avr/io.h>


void spi_init(void){
	//SCK UT, MISO IN, MOSI UT, SS UT
	DDRB |= (1 << PB5) | (1<<PB7)| (1<<PB4);
	DDRB &= ~(1 << PB6);
	// NOT intterupt driven
	// mcp2515, max frequency is 10mhz
	// with external clock, F_CPU is defined to 4,9mhz. we divide by 4, so our sck is 1,2mhz
	SPCR= (1 << SPE) | (1 << MSTR) | (1 << CPHA);
}



void spi_write(char data){
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
}

char spi_read(void){
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}


