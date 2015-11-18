/*
 * adc.h
 *
 * Created: 06.11.2015 13:59:34
 *  Author: laurittr
 */ 

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adc_init(void);
uint16_t adc_read10(uint8_t adc_ch);
uint8_t adc_read8(uint8_t adc_ch);
void adc_reset(void);

#endif /* ADC_H_ */