/*
 * pi.c
 *
 * Created: 19.11.2015 20:35:19
 *  Author: laurittr
 */ 

struct PID_controller {
	float reference;
	
	float Kp;
	float Ki;
	
	float prev_error;
	float integral;
};

//dt = (float)TIMER5_OCRB / (float)F_CPU)*1024;
//Should be calculated every time pi() is called

PI_controller* init_pi(float Kp, float Ki){
	PID_controller* c = malloc(sizeof(PID_controller));
	memset(c, 0, sizeof(PID_controller));
	
	c->Kp = Kp;
	c->Ki = Ki;
	timer_start();
	return c;
}

void pi_update(PI_Controller* c, float ref){
	c->reference = ref;
}

float pi(PI_controller* c, float y){

	dt=timer_get();

	float position = y;
	float error = c->reference - y;
	
	c->integral += error *dt;
	c->prev_error = error;

	timer_reset();

	return	c->Kp * error +
	c->Ki * c->integral;
}
