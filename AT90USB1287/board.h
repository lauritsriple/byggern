/*
 * board.h
 *
 * Created: 01.11.2015 15.15.30
 *  Author: laura
 */ 


#ifndef BOARD_H_
#define BOARD_H_

//PORTB
#define LED_PORT	PORTB
#define LED_DDR		DDRB
#define SW1_PORT	PORTB
#define SW_DDR		DDRB
#define LED1 0
#define SW1 1

//ADC
#define ADC_PORT PORTF
#define ADC_JOY_X 0	//ADC0 - PF0
#define ADC_JOY_Y 1 //ADC1 - PP1


//TOUCH
//Predefined in touchdriver, touch.h and touch.c

//SPI
#define SPI_PORT		PORTB
#define SPI_SCK			1
#define SPI_MOSI		2
#define SPI_MISO		3
#define SPI_CS_MCP2515	0

//CAN
#define CAN_INT_PORT	PORTB
#define CAN_INT_PIN		PINB
#define CAN_INT			4

//void init_buttons(void);
//void init_leds(void);
//void init_sram(void);
void board_init(void);

#endif /* BOARD_H_ */