/*
 * AT90USB1287.c
 *
 * Created: 31.10.2015 15:29:18
 *  Author: medlem
 */ 


#include <avr/io.h>
#include <util/delay.h>
//#include "touch.h"

#define F_CPU 8000000

int main(void)
{
	//examplecode
	touch_init(30, 30, 30, 30);
	uint8_t ls, rs, lb, rb;
	//DDRB |= (1<<0)|(1<<1)|(1<<2)|(1<<3);
	DDRD |= (1 << 0);
	DDRD |= (1 << 2);

	while(1)
	{
		touch_measure(&ls, &rs, &lb, &rb);
		if (lb)
		PORTD &= ~(1<<0);
		else
		PORTD |= (1<<0);
		if (rb)
		PORTD &= ~(1<<1);
		else
		PORTD |= (1<<1);

	}
}