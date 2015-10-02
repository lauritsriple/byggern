/*
 * spi.h
 *
 * Created: 02.10.2015 10:11:32
 *  Author: shahrukk
 */ 


#ifndef SPI_H_
#define SPI_H_

void spi_init(void);
void spi_write(char data);
char spi_read(void);


#endif /* SPI_H_ */