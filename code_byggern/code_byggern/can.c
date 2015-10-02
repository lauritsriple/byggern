/*
 * can.c
 *
 * Created: 02.10.2015 12:00:05
 *  Author: shahrukk
 */ 

//SKAL KUNNE UTVIDES

#include "can.h"
#include "mcp2515.h"

void can_init(uint8_t operationMode){
	mcp2515_init();
	mcp2515_bitModify(MCP_CANCTRL,0b11100000,operationMode)
}

void can_messageSend(can_message_t* msg,uint8_t bufferSelect){
	//transelate bufferselct to buffercontrol
	uint8_t bufferControl;
	if (bufferSelect==MCP_RTS_TX0){
		bufferControl=MCP_TXB0CTRL;
	}
	else if (bufferSelect==MCP_RTS_TX1){
		bufferControl=MCP_TXB1CTRL;
	}
	else if (bufferSelect==MCP_RTS_TX2){
		bufferControl=MCP_TXB2CTRL;
	}
	
	mcp2515_write(bufferControl+1,((msg->id>>3)& 0xff)); //16 to 10bit, 8 msb
	mcp2515_write(bufferControl+2,((msg->id<<5)& 0xe0)); //16 to 10bit, 3 lsb 
	//using standard mode, so no need to write extended ids
	mcp2515_write(bufferControl+5,(msg->length)); //8 to 4bit, lsb
	for (uint8_t i = 0; i <msg->length; i++){
		mcp2515_write(bufferControl+5+i,msg->data[i]);
	}
	mcp2515_requestToSend(bufferSelect);
}


uint8_t can_dataReceive(){}