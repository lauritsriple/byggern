/*
 * pi.c
 *
 * Created: 19.11.2015 20:35:19
 *  Author: laurittr
 */ 

#include "pi.h"
#include "timer.h"

//dt = (float)TIMER5_OCRB / (float)F_CPU)*1024;
//Should be calculated every time pi() is called

pi_controller_t* pi_init(float Kp, float Ki){
	pi_controller_t* c = malloc(sizeof(pi_controller_t));
	memset(c, 0, sizeof(pi_controller_t));
	c->Kp = Kp;
	c->Ki = Ki;
	timer_start();
	return c;
}

void pi_update(pi_controller_t* c, float ref){
	c->reference = ref;
}

float pi_calculate(pi_controller_t* c, float y){
	uint16_t dt=timer_get();
	
	float error = c->reference - y;
	
	c->integral += error *dt;
	c->prev_error = error;

	timer_reset();

	return	c->Kp * error + c->Ki * c->integral;
}
