/*
 * oled.c
 *
 * Created: 18.09.2015 11:32:46
 *  Author: laurittr
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "oled.h"
#include "font.h"
#include <util/delay.h>
#include <stdio.h>
#include "../board.h"

#define OLED_DATA_BASE_ADDRESS				0x2600
#define OLED_COMMAND_BASE_ADDRESS			0x2400
//PRIVATE

//static FILE oled_stdout = FDEV_SETUP_STREAM(oled_put_char, NULL, _FDEV_SETUP_WRITE);

static inline void oled_write_cmd(char cmd){
	//NEEDED BECAUSE CHIP DOES NOT HAVE GAL IC
	//OLED_PORT &=~(1<<OLED_CS); //select chip PA
	//OLED_PORT &=~(1<<OLED_CD); //set D/C low -> Command mode
	//volatile char * ext_oled_cmd = (char *) 0x2100; // 0x1000 not needed, GAL
	//*ext_oled_cmd = cmd;
	//external memory starts at 0x2100
	volatile char * ext_oled_cmd = (char *) 0;
	ext_oled_cmd[0x2400] = cmd; //2400
	//OLED_PORT |= (1<<OLED_CS);
}

static inline void oled_write_data(char data){
	//OLED_PORT &=~(1<<OLED_CS); //select chip
	//OLED_PORT |= (1 <<OLED_CD); //set D/C high -> Datamode
	//volatile char * ext_oled_data = (char *) 0x2300; //0x1200 not needed, GAL
	//*ext_oled_data = data;
	volatile char * ext_oled_data = (char *) 0;
	ext_oled_data[0x2600] = data; //2600
	//OLED_PORT |= (1<<OLED_CS);
}

static inline void oled_goto_page(uint8_t page){
	oled_write_cmd(0xb0+page);
}

static inline void oled_goto_column(uint8_t column){
	oled_write_cmd(column & 0x0f);
	oled_write_cmd(((column & 0xf0) >> 4) | (0x10));
}

//PUBLIC
void oled_init(void){
	
	XMCRA |= (1<< SRE); //Enables external memory interface
	XMCRB |= (1<<XMM2) | (1<<XMM1);
	XMCRB |= (1<<XMBK);
	
/*
	volatile char *ext_ram = (char *) 0;
	
	ext_ram[OLED_COMMAND_BASE_ADDRESS] = COMMAND_SET_DISPLAY_ON;						//Turn display on
	ext_ram[OLED_COMMAND_BASE_ADDRESS] = COMMAND_SET_CONTRAST_CONTROL;					//Set contrast next command
	ext_ram[OLED_COMMAND_BASE_ADDRESS] = 250;											//Contrast value
	ext_ram[OLED_COMMAND_BASE_ADDRESS] = COMMAND_SET_COM_OUTPUT_SCAN_DIRECTION_1;		//Flip scan direction vertically
	ext_ram[OLED_COMMAND_BASE_ADDRESS] = COMMAND_SET_SEGMENT_RE_MAP_1;					//Flip scan direction horizontally
	ext_ram[OLED_COMMAND_BASE_ADDRESS] = COMMAND_SET_MEMORY_ADRESSING_MODE;
	ext_ram[OLED_COMMAND_BASE_ADDRESS] = HORIZONTAL_ADDRESSING_MODE;
	ext_ram[OLED_COMMAND_BASE_ADDRESS] = COMMAND_SET_COLUMN_ADDRESS;
	ext_ram[OLED_COMMAND_BASE_ADDRESS] = 0;
	ext_ram[OLED_COMMAND_BASE_ADDRESS] = 127;
	ext_ram[OLED_COMMAND_BASE_ADDRESS] = COMMAND_SET_PAGE_ADDRESS;
	ext_ram[OLED_COMMAND_BASE_ADDRESS] = 0;
	ext_ram[OLED_COMMAND_BASE_ADDRESS] = 7;
	//_delay_ms(4000);
	//ext_ram[OLED_COMMAND_BASE_ADDRESS] = COMMAND_ENTIRE_DISPLAY_ON_FORCE;
	//_delay_ms(4000);

	while(1){
		for (uint16_t i=0; i < 128*8; i++){
			if ( (i % 2) - 0 ){
				ext_ram[OLED_DATA_BASE_ADDRESS] = 0xFF;
			}
			else{
				ext_ram[OLED_DATA_BASE_ADDRESS] = 0x00;
			}
		}

		for (uint8_t i=0; i<=255; i++){
			ext_ram[0] = COMMAND_SET_CONTRAST_CONTROL;
			ext_ram[0] = i;
			_delay_ms(2);
		}
	}
	clear();*/
	uint8_t delay=1000;
	oled_write_cmd(0xae);    // display off
	_delay_ms(delay);
	oled_write_cmd(0xa1);    //segment remap
	_delay_ms(delay);
	oled_write_cmd(0xda);    //common pads hardware: alternative
	_delay_ms(delay);
	oled_write_cmd(0x12);
	_delay_ms(delay);
	oled_write_cmd(0xc8);    //common output scan direction:com63~com0
	_delay_ms(delay);
	oled_write_cmd(0xa8);    //multiplex ration mode:63
	_delay_ms(delay);
	oled_write_cmd(0x3f);
	_delay_ms(delay);
	oled_write_cmd(0xd5);    //display divide ratio/osc. freq. mode
	_delay_ms(delay);
	oled_write_cmd(0x80);
	_delay_ms(delay);
	oled_write_cmd(0x81);    //contrast control
	_delay_ms(delay);
	oled_write_cmd(0xf0);
	_delay_ms(delay);
	oled_write_cmd(0xd9);    //set pre-charge period
	_delay_ms(delay);
	oled_write_cmd(0x21);
	_delay_ms(delay);
	oled_write_cmd(0x20);    //Set Memory Addressing Mode
	_delay_ms(delay);
	oled_write_cmd(0x02);	//Set page adressing mode
	_delay_ms(delay);
	oled_write_cmd(0xdb);    //VCOM deselect level mode
	_delay_ms(delay);
	oled_write_cmd(0x30);
	_delay_ms(delay);
	oled_write_cmd(0xad);    //master configuration
	_delay_ms(delay);
	oled_write_cmd(0x00);
	_delay_ms(delay);
	oled_write_cmd(0xa4);    //out follows RAM content
	_delay_ms(delay);
	oled_write_cmd(0xa6);    //set normal display
	_delay_ms(delay);
	oled_write_cmd(0xaf);    // display on
	_delay_ms(delay);

	
	//oled_reset();
	//_delay_ms(1000);//fuck
	//oled_write_cmd(0xa5); //to fill screen command

}


void oled_reset(void){
	for (uint8_t i = 0; i<8;i++){
		oled_clear_page(i);
	}
	oled_goto_page(0);
	oled_goto_column(0);
}

void oled_pos(uint8_t page,uint8_t column){
	oled_goto_page(page);
	oled_goto_column(column);
}

void oled_home(void){
	oled_pos(0,0);
}

void oled_clear_page(uint8_t page){
	oled_goto_page(page);
	oled_goto_column(0);
	for (uint16_t i = 0 ; i<SCREEN_COLS; i++){
		oled_write_data(0);
	}
}

void oled_clear_all(void){
	for (uint8_t i=0;i<8;i++){
		oled_clear_page(i);
	}
}

void oled_fill_page(uint8_t page){
	oled_pos(page,0);
	for (uint16_t i = 0 ; i< 128; i++){
		oled_write_data(0xff);
	}
}

/*void oled_writeMatrix(uint8_t* matrix){
	oled_home();
	uint8_t tmp=0;
	for (uint8_t page = 0; page < 8; page ++){
		for(uint8_t i = 0; i < 128; i++){
			for(uint8_t j = 0; j < 8; j++){
				tmp[i]=*matrix[i][j];
			}
			oled_write_data(tmp);
		}
}*/

void oled_put_char(char c){
	for (uint8_t i = 0; i<FONT_WIDTH; i++){
		oled_write_data(pgm_read_byte(&font[c - FONT_OFFSET][i]));
		//oled_write_data(0xA5);
	}
}

void oled_put(uint8_t c){
	oled_write_data(c);
}

/*
void oled_printf(char* fmt, ...){
	va_list v;
	va_start(v, fmt);
	vfprintf(&oled_stdout, fmt, v);
	va_end(v);
}*/
