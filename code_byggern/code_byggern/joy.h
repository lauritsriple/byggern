/*
 * joy.h
 *
 * Created: 11.09.2015 15:41:10
 *  Author: shahrukk
 */ 


#ifndef JOY_H_
#define JOY_H_

#include <avr/io.h>

typedef struct joy_pos_t joy_pos_t;
struct joy_pos_t {
	int16_t x;
	int16_t y;
};

void joy_init(void);
joy_pos_t joy_getPos(void);

#endif /* JOY_H_ */ 