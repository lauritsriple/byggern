/*
 * timer.c
 *
 * Created: 19.11.2015 20:35:46
 *  Author: laurittr
 */ 


uint16_t volatile static timer=0; //Vet ikke om man kan ha static og volatile, men den skal være private

void timer_start(void){
	TCCR5B |=  (1 << CS50) | (1<<CS52);  //Prescaler set to 1024
	TIMSK5 |= (1 << TOIE5);              // Overflow interrupt enable
}

void timer_stop(void){
	TCCR5B &= ~(1 << CS50);
	TCCR5B &= ~(1 << CS52);
	TIMSK5 &= ~(1 << TOIE5);
}

uint16_t timer_get(){
	return timer;
}

void timer_reset(void){
	timer=0;
}

ISR(TIMER5_OVF_vect){
	timer++;
}