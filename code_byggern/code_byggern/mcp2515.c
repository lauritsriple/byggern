/*
 * mcp2515.c
 *
 * Created: 02.10.2015 10:12:26
 *  Author: shahrukk
 */ 

#include "mcp2515.h"
#include "mcp2515defines.h"
#include <avr/io.h>

uint8_t mcp2515_read(uint8_t address){
	uint8_t result;
	PORTB &= ~(1 << MCP2515_CS); //select
	spi_write(MCP_READ);
	spi_write(address);
	result=spi_read();
	PORTB |= (1 << MCP2515_CS); //deselect
}

void mcp2515_write(uint8_t adress,uint8_t data){
	PORTB &= ~(1 << MCP2515_CS); //select
	spi_write(MCP_WRITE);
	spi_write(address);
	spi_write(data);
	PORTB |= (1 << MCP2515_CS); //deselect
}

void mcp2515_requestToSend(uint8_t bufferSelect){
	PORTB &= ~(1 << MCP2515_CS); //select
	spi_write(bufferSelect);
	PORTB |= (1 << MCP2515_CS); //deselect
}

void mcp2515_bitModify(uint8_t address, uint8_t mask, uint8_t data){
	PORTB &= ~(1 << MCP2515_CS); //select
	spi_write(MCP_BITMOD);
	spi_write(address);
	spi_write(mask);
	spi_write(data);
	PORTB |= (1 << MCP2515_CS); //deselect
}
void mcp2515_reset(void){
	PORTB &= ~(1 << MCP2515_CS); //select
	spi_write(MCP_RESET);
	PORTB |= (1 << MCP2515_CS); //deselect
}

uint8_t mcp2515_readStatus(void){
	uint8_t result;
	PORTB &= ~(1 << MCP2515_CS); //select
	spi_write(MCP_READ_STATUS);
	result = spi_read();
	PORTB |= (1 << MCP2515_CS); //deselect
	return result;
}