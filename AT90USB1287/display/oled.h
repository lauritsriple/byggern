/*
 * oled.h
 *
 * Created: 18.09.2015 11:31:21
 *  Author: laurittr
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <stdint.h>
#define SCREEN_ROWS 128
#define SCREEN_COLS 64

void oled_reset(void);
void oled_init(void);
void oled_home(void);
void oled_clear_page(uint8_t line);
void oled_clear_all(void);
void oled_pos(uint8_t page, uint8_t column);
void oled_put_char(char c);
void oled_printf(char* fmt, ...);
void oled_fill_page(uint8_t page);
void oled_clear_all();
void clear(void);
void update_oled(void);

/*OLED Command address defines*/
#define COMMAND_SET_LOWER_COLUMN_START_BASEADR_PAGEADRMODE	0x00	//See table 8-1, and section 9.1.3, goes from 0x00 to 0x0F

#define COMMAND_SET_HIGHER_COLUMN_START_BASEADR_PAGEADRMODE	0x10	//See table 8-1, and section 9.1.3, goes from 0x10 to 0x1F

#define COMMAND_SET_MEMORY_ADRESSING_MODE					0x20
#define PAGE_ADDRESSING_MODE								0x02
#define HORIZONTAL_ADDRESSING_MODE							0x00
#define VERTICAL_ADDRESSING_MODE							0x01
#define COMMAND_SET_COLUMN_ADDRESS							0x21
#define COMMAND_SET_PAGE_ADDRESS							0x22
#define COMMAND_SET_DISPLAY_START_LINE_BASEADR				0x40	//See table 9-1, goes from 0x40 to 0x7F
#define COMMAND_SET_CONTRAST_CONTROL						0x81	// Double byte command to select 1 out of 256 contrast steps. Contrast increases as the value increases.(RESET = 7Fh )
#define SET_CONTRAST_CONTROL_RESET_VALUE					0x7F
#define COMMAND_SET_SEGMENT_RE_MAP_0						0xA0
#define COMMAND_SET_SEGMENT_RE_MAP_1						0xA1
#define COMMAND_ENTIRE_DISPLAY_ON							0xA4
#define COMMAND_ENTIRE_DISPLAY_ON_FORCE						0xA5
#define COMMAND_SET_INVERSE_MODE_DISPLAY_NORMAL				0xA6
#define COMMAND_SET_INVERSE_MODE_DISPLAY_INVERSE			0xA7
#define COMMAND_SET_MULTIPLEX_RATIO							0xA8
#define COMMAND_SELECT_EXT_OR_INTERNAL_IREF					0xAD
#define COMMAND_SET_DISPLAY_ON								0xAF
#define COMMAND_SET_DISPLAY_OFF								0xAE
#define COMMAND_SET_PAGE_ADDRESS_0							0xB0	//See Table 8-1 and section 9.1.3
#define COMMAND_SET_PAGE_ADDRESS_1							0xB1
#define COMMAND_SET_PAGE_ADDRESS_2							0xB2
#define COMMAND_SET_PAGE_ADDRESS_3							0xB3
#define COMMAND_SET_PAGE_ADDRESS_4							0xB4
#define COMMAND_SET_PAGE_ADDRESS_5							0xB5
#define COMMAND_SET_PAGE_ADDRESS_6							0xB6
#define COMMAND_SET_PAGE_ADDRESS_7							0xB7
#define COMMAND_SET_COM_OUTPUT_SCAN_DIRECTION_0				0xC0	//See table 9-3
#define COMMAND_SET_COM_OUTPUT_SCAN_DIRECTION_1				0xC8
#define COMMAND_SET_DISPLAY_OFFSET							0xD3
#define COMMAND_SET_DISPLAY_CLOCKDIVIDE_RATIO				0xD5
#define COMMAND_SET_PRECHARGE_PERIOD						0xD9
#define COMMAND_SET_COM_PINS_HARDWARE_CONFIGURATION			0xDA
#define COMMAND_SET_VCOMH_DESELECT_LEVEL					0xDB
#define COMMAND_NOP											0xE3
//#define GA_COMMAND_HORIZONTAL_SCROLL_RIGHT
//#define GA_COMMAND_CONTINUOUS_VERT_AND_HORZ_SCROLL_SETUP	0x29
#define GA_COMMAND_DEACTIVATE_SCROLL						0x2E
#define GA_COMMAND_ACTIVATE_SCROLL							0x2F
#define GA_COMMAND_SET_VERTICAL_SCROLL_AREA					0xA3


#endif /* OLED_H_ */