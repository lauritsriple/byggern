/*
 * can.c
 *
 * Created: 02.10.2015 12:00:05
 *  Author: shahrukk
 */ 

#include "can.h"
#include "mcp2515.h"
#include "mcp2515defines.h"
#include "uart.h"
#include <stdlib.h>
#include <string.h> //needed?

#if defined(__AVR_ATMega162__)
#include "../ATmega162/board.h"
#elif defined(__AVR_ATMega2560__)
#include "../ArduinoMega2560/board.h"
#elif defined(__AVR_AT90usb1287__)
#include "../AT90USB1287/board.h"
#endif


void can_init(uint8_t operationMode){
	mcp2515_init();
	mcp2515_bitModify(MCP_RXB0CTRL, MCP_FILTER_MASK, 0xff); //turn off filter
	mcp2515_bitModify(MCP_RXB1CTRL, MCP_FILTER_MASK, 0xff); //turn off filter
	mcp2515_bitModify(MCP_CANCTRL, MODE_MASK, operationMode);
	CAN_INT_PORT &= ~(1<<CAN_INT); //for can_pollInt()
}

//TODO: Should find a empty buffer by itself. No need for bufferselect. Should rather have priorities
void can_messageSend(can_message_t* msg,uint8_t bufferSelect){
	//transelate bufferSelect to bufferControl
	uint8_t bufferControl;
	if (bufferSelect==MCP_TXB0CTRL){
		bufferControl=MCP_RTS_TX0;
	}
	else if (bufferSelect==MCP_TXB1CTRL){
		bufferControl=MCP_RTS_TX1;
	}
	else if (bufferSelect==MCP_TXB2CTRL){
		bufferControl=MCP_RTS_TX2;
	}
	else{
		return; //if invalid bufferselect
	}

	//MCP_TXBnCTRL - Control Registers
	//wait for the previous message to complete sending, TXREQ - Message transmit request bit. high if buffer is already waiting to send
	while(mcp2515_read(bufferSelect) & (1 << MCP_TXREQ)){}
	
	//MCP_TXBnSIDH & MCP_TXBnSIDL- ID registers
	//sending the id of the message, using standard mode, so no need to write extended ids
	mcp2515_write(bufferSelect+1, ((msg->id>>3) & MCP_IDH_MASK)); //16 to 10bit, 8 msb
	mcp2515_write(bufferSelect+2, ((msg->id<<5) & MCP_IDL_MASK)); //16 to 10bit, 3 lsb 
	
	//TXBnDLC - Data length code registers
	//sending the msg
	mcp2515_write(bufferSelect+5, (msg->length) & MCP_DLC_MASK); //8 to 4bit, lsb
	//TXBnDm - Data registers
	for (uint8_t i = 0; i < msg->length; i++){
		mcp2515_write(bufferSelect+6+i, msg->data[i]);
	}
	mcp2515_requestToSend(bufferControl);
}

//TODO: can use real interrupts to read from buffers when message is received
can_message_t can_dataReceive(void){
	//creating msg stuct. Also sets all elem to zero
	can_message_t m;
	memset(&m, 0, sizeof(can_message_t));

	//which buffer to read?
	uint8_t bufferSelect=can_pollInt();

	//get id and length
	//id is 16bit, and needs some shifting of two registers which are then or'ed together
	m.id=(uint16_t)((mcp2515_read(bufferSelect+2) >> 5) | (mcp2515_read(bufferSelect+1) << 3));
	//length is 8bit, bit actual data only on 4 lsb. Therefore the bitmask
	m.length = mcp2515_read(bufferSelect+5) & 0x0f;

	//iterate all the data bytes 
	for (uint8_t i = 0; i < m.length; i++){
		m.data[i] = mcp2515_read(bufferSelect + 6 + i);
	}
	
	if(bufferSelect == MCP_RXB0CTRL){
		mcp2515_bitModify(MCP_CANINTF, MCP_RX0IF, 0x00); //unset flag
	}
	else if(bufferSelect == MCP_RXB1CTRL){
		mcp2515_bitModify(MCP_CANINTF, MCP_RX1IF, 0x00); //unset flag
	}
	
	return m;
}

uint8_t can_pollInt(){
	//PD2 is set as input in can_init()
	while(!(CAN_INT_PIN & (1<<CAN_INT))){} //w8 for interrupt, hopefully not forever!
	//find out which buffer is full
	//if both is full, will only read the first one. Might be problematic if we send lot of data on the can-bus
	if (mcp2515_read(MCP_CANINTF) & MCP_RX0IF){
		return MCP_RXB0CTRL;
	}
	
	else if (mcp2515_read(MCP_CANINTF) & MCP_RX1IF){
		return MCP_RXB1CTRL;
	}
	abort();
}

void can_print(can_message_t m){ //for debugging
	printf("can_message_t(id:%d, len:%d, data:{", m.id, m.length);
	if(m.length){
		printf("%d", m.data[0]);
	}
	for(uint8_t i = 1; i < m.length; i++){
		printf(", %d", m.data[i]);
	}
	printf("})\n");
}
