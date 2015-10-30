/*
 * max520.h
 *
 * Created: 30.10.2015 19:09:43
 *  Author: laurittr
 */ 

#include <stdint.h>

#ifndef MAX520_H_
#define MAX520_H_

void max520_init(void);
//only sends to one address, and only one pwm output is selected
void max520_send(uint8_t val);

#endif /* MAX520_H_ */