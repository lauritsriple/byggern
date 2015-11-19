/*
 * pi.h
 *
 * Created: 19.11.2015 20:35:11
 *  Author: laurittr
 */ 
#include <stdint.h>


#ifndef PI_H_
#define PI_H_

typedef struct pi_controller_t pi_controller_t;
struct pi_controller_t {
	float reference;
	
	float Kp;
	float Ki;
	
	float prev_error;
	float integral;
};

pi_controller_t* pi_init(float Kp, float Ki);
void pi_update(pi_controller_t* c, float y);
float pi_calculate(pi_controller_t* c, float y);

#endif /* PI_H_ */