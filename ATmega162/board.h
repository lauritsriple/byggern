/*
 * board.h
 *
 * Created: 01.11.2015 15.15.30
 *  Author: laura
 */ 


#ifndef BOARD_H_
#define BOARD_H_

//PORTB
#define LED_PORT PORTB
#define SW1_PORT PORTB
#define LED1 0
#define SW1 1

//ADC
#define ADC_PORT PORTE
#define ADC_INT 0

//TOUCH
#define TOUCH_PORT PORTB
#define TOUCH_SW_R 2
#define TOUCH_SW_L 3
//L_SLIDER on ADC
//R_SlIDER on ADC

//SPI
#define SPI_PORT		PORTB
#define SPI_SCK			7
#define SPI_MOSI		5
#define SPI_MISO		6
#define SPI_CS_MCP2515	4

//CAN
#define CAN_INT_PORT	PORTD
#define CAN_INT_PIN		PIND
#define CAN_INT			2

//void init_buttons(void);
//void init_leds(void);
//void init_sram(void);
void board_init(void);



#endif /* BOARD_H_ */