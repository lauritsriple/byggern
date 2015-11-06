/*
 * ADC.h
 *
 * Created: 11.09.2015 13:16:53
 *  Author: shahrukk
 */ 


#ifndef ADC_H_
#define ADC_H_

typedef enum adc_ch adc_ch;
enum adc_ch{
	sli_l = 4,
	sli_r = 5,
	joy_x = 6,
	joy_y = 7,
};

uint8_t adc_read8(adc_ch ch);
volatile uint8_t adc_conversion;
void adc_init(void);

#endif /* ADC_H_ */