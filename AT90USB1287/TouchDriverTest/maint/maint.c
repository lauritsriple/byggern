#include <avr/io.h>
#include <util/delay.h>
#include "touch.h"

int main(void)
{
	touch_init(30, 30, 30, 30);

	uint8_t ls, rs, lb, rb;
	DDRB |= (1<<0)|(1<<1)|(1<<2)|(1<<3);

	while(1)
	{
		touch_measure(&ls, &rs, &lb, &rb);

		if (lb)
			PORTB &= ~(1<<0);
		else
			PORTB |= (1<<0);
		if (rb)
			PORTB &= ~(1<<1);
		else
			PORTB |= (1<<1);

		_delay_ms(10);
	}
}
