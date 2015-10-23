/*
 * pwm.h
 *
 * Created: 23.10.2015 08:57:44
 *  Author: shahrukk
 */ 

#include <avr/io.h>

#ifndef PWM_H_
#define PWM_H_

void pwm_init(void);
void pwm_setValue(uint8_t val);
void pwm_setServo(int16_t val);



#endif /* PWM_H_ */