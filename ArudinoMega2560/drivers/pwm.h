/*
 * pwm.h
 *
 * Created: 23.10.2015 08:57:44
 *  Author: shahrukk
 */ 

#include <avr/io.h>

#ifndef PWM_H_
#define PWM_H_

//Servo has min and max values for dutycycle
#define PWM_MIN 21
#define PWM_MAX 39
#define PWM_MID ((PWM_MAX+PWM_MIN)/2)

void pwm_init(void);
void pwm_setValue(uint8_t val);
void pwm_setServo(int16_t val);
void pwm_setServoSlider(uint8_t val);

#endif /* PWM_H_ */