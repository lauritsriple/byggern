/*
 * mcp2515.c
 *
 * Created: 02.10.2015 10:12:26
 *  Author: shahrukk
 */ 

#include "mcp2515.h"
#include "mcp2515defines.h"
#include <avr/io.h>
#include "uart.h"
#include "spi.h"
#include <stdlib.h>
#include <stdio.h>

void mcp2515_init(void){
	uint8_t value=0;
	spi_init();
	mcp2515_reset();
	//selftest, will reset chip until it is in configuration mode
	while(!value){
		value=mcp2515_read(MCP_CANSTAT);
		if ((value & MODE_MASK) != MODE_CONFIG) {
			puts("ERROR! ERROR! MCP2515 is NOT in configuration mode after reset!\r");
			value= 1; //error code
		}
	}
}

uint8_t mcp2515_read(uint8_t address){
	uint8_t result;
	PORTB &= ~(1 << MCP2515_CS); //select
	spi_transmit(MCP_READ);
	spi_transmit(address);
	result=spi_transmit(0x00);
	PORTB |= (1 << MCP2515_CS); //deselect
	return result;
}

void mcp2515_write(uint8_t address, uint8_t data){
	PORTB &= ~(1 << MCP2515_CS); //select
	spi_transmit(MCP_WRITE);
	spi_transmit(address);
	spi_transmit(data);
	PORTB |= (1 << MCP2515_CS); //deselect
}

void mcp2515_requestToSend(uint8_t bufferSelect){
	PORTB &= ~(1 << MCP2515_CS); //select
	spi_transmit(bufferSelect);
	PORTB |= (1 << MCP2515_CS); //deselect
}

void mcp2515_bitModify(uint8_t address, uint8_t mask, uint8_t data){
	PORTB &= ~(1 << MCP2515_CS); //select
	spi_transmit(MCP_BITMOD);
	spi_transmit(address);
	spi_transmit(mask);
	spi_transmit(data);
	PORTB |= (1 << MCP2515_CS); //deselect
}
void mcp2515_reset(void){
	PORTB &= ~(1 << MCP2515_CS); //select
	spi_transmit(MCP_RESET);
	PORTB |= (1 << MCP2515_CS); //deselect
}

uint8_t mcp2515_readStatus(void){
	uint8_t result;
	PORTB &= ~(1 << MCP2515_CS); //select
	spi_transmit(MCP_READ_STATUS);
	result = spi_transmit(0x00);
	PORTB |= (1 << MCP2515_CS); //deselect
	return result;
}