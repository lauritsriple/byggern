/*
 * board.h
 *
 * Created: 01.11.2015 16.08.00
 *  Author: laura
 */ 


#ifndef BOARD_H_
#define BOARD_H_

//DEBUG LED
#define LED_DDR		DDRH
#define LED_PORT	PORTH
#define LED1		3

//PWM
#define PWM_PORT	PORTE
#define PWM_DDR		DDRE
#define PWM1		3

//ADC
#define IR_CHANNEL 0

//MOTOR
#define MOTOR_PORT			PORTF
#define MOTOR_DDR			DDRF
#define MOTOR_EN			4
#define MOTOR_DIR			3
#define MOTOR_ENCODER_EN	7
#define MOTOR_ENCODER_RESET	6
#define MOTOR_ENCODER_SEL	5
#define ENCODER_PORT		PORTK
#define ENCODER_PIN			PINK

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

//void static init_led();



#endif /* BOARD_H_ */