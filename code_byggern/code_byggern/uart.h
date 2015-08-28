/*
 * uart.h
 *
 * Created: 28.08.2015 12:14:58
 *  Author: laurittr
 */ 


#ifndef UART_H_
#define UART_H_

void uart_init(void);
void uart_putChar(char c);
char uart_getChar(void);

//function to redirect printf



#endif /* UART_H_ */