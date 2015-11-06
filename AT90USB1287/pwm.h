/*
 * pwm.h
 *
 * Created: 06.11.2015 11:59:37
 *  Author: laurittr
 */ 



#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>
//pwm on timer0, using both PB6 and PB7 as outputs.
void pwm_init(void);
void pwm_set(uint8_t ch, uint8_t val);


#endif /* PWM_H_ */