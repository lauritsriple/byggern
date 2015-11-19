/*
 * pi.h
 *
 * Created: 19.11.2015 20:35:11
 *  Author: laurittr
 */ 


#ifndef PI_H_
#define PI_H_

PI_controller* init_pi(float Kp, float Ki);
void pi_update(PI_Controller* c, float y);
float pi(PI_controller* c, float y);



#endif /* PI_H_ */