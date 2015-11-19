/*
 * board.h
 *
 * Created: 01.11.2015 15.15.30
 *  Author: laura
 */ 


#ifndef BOARD_H_
#define BOARD_H_

#include <avr/io.h>

//OLED
//#define OLED_PORT	PORTC
//#define OLED_CS		0
//#define OLED_CD		1

//PORTB
#define LED_PORT	PORTB
#define LED_DDR		DDRB
#define LED1		5
#define JOY			4
#define JOY_DDR		DDRB
#define JOY_PORT	PORTB
#define JOY_PIN		PINB


//ADC
#define ADC_PORT	PORTF
#define ADC_DDR		DDRF
#define ADC_JOY_X	0 //ADC0 - PF0
#define ADC_JOY_Y	1 //ADC1 - PF1

//PWM
#define PWM_PORT	PORTB
#define PWM1		7
#define PWM2		6

//TOUCH
//Predefined in touchdriver, touch.h and touch.c

//SPI
#define SPI_PORT		PORTB
#define SPI_DDR			DDRB
#define SPI_PIN			PINB
#define SPI_SCK			1
#define SPI_MOSI		2
#define SPI_MISO		3
#define SPI_CS_MCP2515	0

//CAN
#define CAN_INT_PORT	PORTD
#define CAN_INT_PIN		PIND
#define CAN_INT			1

#define SW_PORT		PORTD
#define SW			4
#define SW2			6
#define SW_DDR		DDRD
#define SW_PIN		PIND

void board_init(void);

#endif /* BOARD_H_ */