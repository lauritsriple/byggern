/*
 * motor.h
 *
 * Created: 30.10.2015 18:39:19
 *  Author: laurittr
 */ 

#include <stdint.h>

#ifndef MOTOR_H_
#define MOTOR_H_

typedef enum motorDirection motorDirection;
enum motorDirection {right,left};

void motor_init(void);
void motor_twiAddr(uint8_t addr);
void motor_speed(uint8_t speed);
void motor_direction(motorDirection dir);
int16_t motor_encoderRead(void);
void motor_encoderCounterReset(void);



#endif /* MOTOR_H_ */