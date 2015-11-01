/*
 * adc.h
 *
 * Created: 23.10.2015 14:20:24
 *  Author: shahrukk
 */ 

#include <stdint.h>

#ifndef ADC_H_
#define ADC_H_

void adc_init(void);
uint16_t adc_read(uint8_t ch);

#endif /* ADC_H_ */