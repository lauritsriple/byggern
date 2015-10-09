/*
 * mcp2515.h
 *
 * Created: 02.10.2015 10:12:13
 *  Author: shahrukk
 */ 


#ifndef MCP2515_H_
#define MCP2515_H_

#include <avr/io.h>

#define MCP2515_CS 4 //ss on PB4

uint8_t mcp2515_init(void);
uint8_t mcp2515_read(uint8_t address);
void mcp2515_write(uint8_t address,uint8_t data);
void mcp2515_requestToSend(uint8_t bufferSelect);
void mcp2515_bitModify(uint8_t address, uint8_t mask, uint8_t data);
void mcp2515_reset(void);
uint8_t mcp2515_readStatus(void);


#endif /* MCP2515_H_ */