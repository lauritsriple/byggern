/*
 * timer.h
 *
 * Created: 19.11.2015 20:35:56
 *  Author: laurittr
 */ 


#ifndef TIMER_H_
#define TIMER_H_


void timer_start(void);
void timer_stop(void);
uint16_t timer_get();
void timer_reset(void);


#endif /* TIMER_H_ */