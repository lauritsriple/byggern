/*
 * uart.h
 *
 * Created: 28.08.2015 12:14:58
 *  Author: laurittr
 */ 


#ifndef UART_H_
#define UART_H_

#define BAUD 9600

void uart_init(void);
void uart_putChar(unsigned char c);
unsigned char uart_getChar(void);

#endif /* UART_H_ */