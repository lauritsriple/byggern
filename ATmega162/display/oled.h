/*
 * oled.h
 *
 * Created: 18.09.2015 11:31:21
 *  Author: laurittr
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <stdint.h>
#define SCREEN_ROWS 128;
#define SCREEN_COLS 64;

void oled_init(void);
void oled_home(void);
void oled_clear_page(uint8_t line);
void oled_clear_all(void);
void oled_pos(uint8_t page, uint8_t column);
void oled_put_char(char c);
void oled_printf(char* fmt, ...);
void oled_fill_page(uint8_t page);
void oled_clear_all();

#endif /* OLED_H_ */