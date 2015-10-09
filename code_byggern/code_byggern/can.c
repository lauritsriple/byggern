/*
 * can.c
 *
 * Created: 02.10.2015 12:00:05
 *  Author: shahrukk
 */ 

//SKAL KUNNE UTVIDES

#include "can.h"
#include "mcp2515.h"
#include "mcp2515defines.h"
#include <stdlib.h>
#include <string.h>


void can_init(uint8_t operationMode){
	mcp2515_init();


printf("CANSTAT: 0x%02x (should be 0x80)\n", mcp2515_read(MCP_CANSTAT));
printf("CANCTRL: 0x%02x (should be 0x87)\n", mcp2515_read(MCP_CANCTRL));

	mcp2515_bitModify(MCP_RXB0CTRL, 0b01100000, 0xff);
	mcp2515_bitModify(MCP_RXB1CTRL, 0b01100000, 0xff);
	mcp2515_bitModify(MCP_CANCTRL, MODE_MASK, operationMode);


printf("CANSTAT: 0x%02x (should be 0x40)\n", mcp2515_read(MCP_CANSTAT));
printf("CANCTRL: 0x%02x (should be 0x47)\n", mcp2515_read(MCP_CANCTRL));
}

void can_messageSend(can_message_t* msg,uint8_t bufferSelect){
	//transelate bufferselct to buffercontrol
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
		return;
	}

	//wait for the previous message to complete sending
	while(mcp2515_read(bufferSelect) & (1 << 3)){}
	
	//sending the id of the message
	mcp2515_write(bufferSelect+1, ((msg->id>>3) & 0xff)); //16 to 10bit, 8 msb
	mcp2515_write(bufferSelect+2, ((msg->id<<5) & 0xe0)); //16 to 10bit, 3 lsb 
	//using standard mode, so no need to write extended ids
	
	//sending the msg
	mcp2515_write(bufferSelect+5, (msg->length) & 0x0f); //8 to 4bit, lsb
	for (uint8_t i = 0; i < msg->length; i++){
		mcp2515_write(bufferSelect+6+i, msg->data[i]);
	}
	mcp2515_requestToSend(bufferControl);
}


can_message_t can_dataReceive(void){
	can_message_t m;
	memset(&m, 0, sizeof(can_message_t));
	
	uint8_t bufferSelect = 0;
	uint8_t interrupt = can_interruptHandler();
	
	if(interrupt == 0){
		bufferSelect = MCP_RXB0CTRL;
	}
	if (interrupt == 1){
		bufferSelect = MCP_RXB1CTRL;
	}
	
	bufferSelect = MCP_RXB0CTRL;
		

	if (bufferSelect != 0  &&  (mcp2515_read(MCP_CANINTF) & (1<<0))){
		
		uint16_t IDhigh = mcp2515_read(bufferSelect+1);
		uint16_t IDlow  = mcp2515_read(bufferSelect+2);

		
		m.id = IDlow >> 5  |  IDhigh << 3;
		/*
		recieve->id = (
			(uint16_t)(mcp2515_read((bufferSelect+1) >> 3)) << 8 | 
			(uint16_t)(mcp2515_read((bufferSelect+2) << 5) & 0xe0)
		);
		*/
		m.length = mcp2515_read(bufferSelect+5) & 0x0f;
		
		for (uint8_t i = 0; i < m.length; i++){
			m.data[i] = mcp2515_read(bufferSelect + 6 + i);
		}
	}
	
	return m;
}


uint8_t can_interruptHandler(){
	/*DDRD &= ~(1<<PD2);
	if(!(PIND & (1<<PIND2))){
		if (mcp2515_read(MCP_CANINTF) & 0x01){
			mcp2515_bitModify(MCP_CANINTF, 0x01, 0);
			return 0;
		}
		
		if (mcp2515_read(MCP_CANINTF) & 0x02){
			mcp2515_bitModify(MCP_CANINTF, 0x02, 0);
			return 1;
		}
	}*/	
	return -1;	
}
