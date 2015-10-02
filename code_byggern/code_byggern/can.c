/*
 * can.c
 *
 * Created: 02.10.2015 12:00:05
 *  Author: shahrukk
 */ 

#include "can.h"
#include "mcp2515.h"

void can_init(uint8_t operationMode){
	mcp2515_init();
	mcp2515_bitModify(MCP_CANCTRL,0b11100000,operationMode)
}

void can_messageSend(can_message_t* msg){
	mcp2515_write()
	
	//skriv til buffer
}