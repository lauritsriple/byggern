/*
 * spi.h
 *
 * Created: 02.10.2015 10:11:32
 *  Author: shahrukk
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

void spi_init(void);
uint8_t spi_transmit(char data);

#endif /* SPI_H_ */