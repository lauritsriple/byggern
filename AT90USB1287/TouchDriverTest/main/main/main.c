/*
 * main.c
 *
 * Created: 25.09.2011 14:51:20
 *  Author: Tablet
 */ 

#include <avr/io.h>
#include "touch.h"

int main(void)
{
	touch_init(30, 30, 30, 30);
    
	DDRB |= (1<<0);
	
	uint8_t ls, rs, lb, rb;
	while(1)
    {
		touch_measure(&ls, &rs, &lb, &rb);
		
		if(lb)
			PORTB &= ~(1<<0);
		else
			PORTB |= (1<<0);
        //TODO:: Please write your application code 
    }
}