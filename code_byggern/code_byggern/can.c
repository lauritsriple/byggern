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
	if (bufferSelect==MCP_TXB0CTRL){
		bufferControl=MCP_RTS_TX0;
	}
	else if (bufferSelect==MCP_TXB1CTRL){
		bufferControl=MCP_RTS_TX1;
	}
	else if (bufferSelect==MCP_TXB2CTRL){
		bufferControl=MCP_RTS_TX2;
	}
	
	//sending the id of the message
	mcp2515_write(bufferSelect+1,((msg->id>>3)& 0xff)); //16 to 10bit, 8 msb
	mcp2515_write(bufferSelect+2,((msg->id<<5)& 0xe0)); //16 to 10bit, 3 lsb 
	//using standard mode, so no need to write extended ids
	
	//sending the msg
	mcp2515_write(bufferSelect+5,(msg->length)); //8 to 4bit, lsb
	for (uint8_t i = 1; i <msg->length; i++){
		mcp2515_write(bufferSelect+5+i,msg->data[i]);
	}
	mcp2515_requestToSend(bufferControl);
}


can_message_t can_dataReceive(uint8_t bufferSelect){
	
	can_message_t msg;
	if bufferSelect == MCP_RXB0CTRL{
		if(!(mcp2515_read(MCP_CANINTF) & 0x01)){
			return NULL;
		}
	}
	if bufferSelect == MCP_RXB1CTRL{
		if (!(mcp2515_read(MCP_CANINTF) & 0x02)){
			return NULL;
		}
	}
		msg->id = (mcp2515_read((bufferSelect+1) >> 3) & 0xff) | (mcp2515_read((bufferSelect+2) << 5)& 0xe0);
		msg->length = mcp2515_read((bufferSelect+5)& 0x07);
		
		for (uint8_t i = 1; i <msg.length; i++){
			msg.data[i] = mcp2515_read(bufferSelect + 5 + i);
		}
		
		for (uint8_t i = msg.length; i < 8; i++){
			msg.data[i] = 0;		
		}
		mcp2515_bitModify(MCP_CANINTF, 0x01, 0);
		mcp2515_bitModify(MCP_CANINTF, 0x02, 0);
	}
	return msg;
}




