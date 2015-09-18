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
#include <stdio.h>

//PRIVATE

static FILE oled_stdout = FDEV_SETUP_STREAM(oled_put_char, NULL, _FDEV_SETUP_WRITE);

static inline void oled_write_cmd(char cmd){
	volatile char * ext_oled_cmd = (char *) 0x1000;
	*ext_oled_cmd = cmd;
}

static inline void oled_write_data(char data){
	volatile char * ext_oled_data = (char *) 0x1200;
	*ext_oled_data = data;
}

static inline void oled_goto_page(uint8_t page){
	oled_write_cmd(page | (0xb0));
}

static inline void oled_goto_column(uint8_t column){
	oled_write_cmd(column & 0x0f);
	oled_write_cmd(((column & 0xf0) >> 4) | (0x10));
}

//PUBLIC
void oled_init(void){
		oled_write_cmd(0xae);    // display off
		oled_write_cmd(0xa1);    //segment remap
		oled_write_cmd(0xda);    //common pads hardware: alternative
		oled_write_cmd(0x12);
		oled_write_cmd(0xc8);    //common output scan direction:com63~com0
		oled_write_cmd(0xa8);    //multiplex ration mode:63
		oled_write_cmd(0x3f);
		oled_write_cmd(0xd5);    //display divide ratio/osc. freq. mode
		oled_write_cmd(0x80);
		oled_write_cmd(0x81);    //contrast control
		oled_write_cmd(0x50);
		oled_write_cmd(0xd9);    //set pre-charge period
		oled_write_cmd(0x21);
		oled_write_cmd(0x20);    //Set Memory Addressing Mode
		oled_write_cmd(0x02);
		oled_write_cmd(0xdb);    //VCOM deselect level mode
		oled_write_cmd(0x30);
		oled_write_cmd(0xad);    //master configuration
		oled_write_cmd(0x00);
		oled_write_cmd(0xa4);    //out follows RAM content
		oled_write_cmd(0xa6);    //set normal display
		oled_write_cmd(0xaf);    // display on
}

void oled_pos(uint8_t page,uint8_t column){
	oled_goto_page(page);
	oled_goto_column(column);
}

void oled_home(void){
	oled_pos(0,0);
	
}

void oled_clear_page(uint8_t page){
	oled_pos(page,0);
	for (uint16_t i = 0 ; i< 128; i++){
		oled_write_data(0x0);
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

void oled_put_char(char c){
	for (uint8_t i = 0; i<FONT_WIDTH; i++){
		oled_write_data(pgm_read_byte(&font[c - FONT_OFFSET][i]));
	}
}

void oled_printf(char* fmt, ...){
	va_list v;
	va_start(v, fmt);
	vfprintf(&oled_stdout, fmt, v);
	va_end(v);
}
