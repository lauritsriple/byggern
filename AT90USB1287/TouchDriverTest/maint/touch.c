#include "touch.h"
#include "touch_api.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

volatile uint16_t time_ms = 0;
extern qt_touch_lib_config_data_t qt_config_data;

extern y_line_info_t y_line_info[NUM_Y_LINES];
extern x_line_info_t x_line_info[NUM_X_LINES];

x_line_info_t x_line_info[NUM_X_LINES]= {
   FILL_OUT_X_LINE_INFO(  1,7u ),
   FILL_OUT_X_LINE_INFO(  1,3u ),
   FILL_OUT_X_LINE_INFO(  1,5u ),
   FILL_OUT_X_LINE_INFO(  1,4u ),
   FILL_OUT_X_LINE_INFO(  2,2u ),
   FILL_OUT_X_LINE_INFO(  2,3u ),
   FILL_OUT_X_LINE_INFO(  2,4u ),
   FILL_OUT_X_LINE_INFO(  2,5u ),
};

y_line_info_t y_line_info[NUM_Y_LINES]= {
   FILL_OUT_Y_LINE_INFO(  6u ),
   FILL_OUT_Y_LINE_INFO(  7u ),
};

void touch_init(uint8_t ls_threshold, uint8_t rs_threshold, uint8_t lb_threshold, uint8_t rb_threshold)
{
	//	Run at 16MHz
	asm("ldi r16,0x80");
	asm("sts 0x61,r16");
	asm("ldi r16,0x00");
	asm("sts 0x61,r16");

	// Disable the JTAG Pins
	asm("ldi r16,0x80");
	asm("sts 0x55,r16");
	asm("ldi r16,0x80");
	asm("sts 0x55,r16");

	asm("nop");
	asm("nop");

	// Disable pull-up
	MCUCR |= (1u << PUD);
	
	// Set burst length
	qt_burst_lengths[0] = 32u;
	qt_burst_lengths[1] = 32u;
	qt_burst_lengths[2] = 32u;
	qt_burst_lengths[3] = 32u;
	qt_burst_lengths[4] = 32u;
	qt_burst_lengths[5] = 32u;
	qt_burst_lengths[6] = 32u;
	qt_burst_lengths[7] = 32u;
	qt_burst_lengths[8] = 96u;
	qt_burst_lengths[9] = 96u;
	qt_burst_lengths[10] = 96u;
	qt_burst_lengths[11] = 96u;
	qt_burst_lengths[12] = 32u;
	qt_burst_lengths[13] = 32u;
	qt_burst_lengths[14] = 32u;
	qt_burst_lengths[15] = 32u;

	qt_enable_key( CHANNEL_12, NO_AKS_GROUP, ls_threshold, HYST_12_5 );
	qt_enable_key( CHANNEL_0, NO_AKS_GROUP, rs_threshold, HYST_12_5 );
	qt_enable_slider( CHANNEL_8, CHANNEL_11, NO_AKS_GROUP, lb_threshold, HYST_12_5, RES_8_BIT, 0u  );
	qt_enable_slider( CHANNEL_4, CHANNEL_7, NO_AKS_GROUP, rb_threshold, HYST_12_5, RES_8_BIT, 0u  );

	qt_init_sensing();
	
	// Set configuration
	qt_config_data.qt_di              = DEF_QT_DI;
	qt_config_data.qt_neg_drift_rate  = DEF_QT_NEG_DRIFT_RATE;
	qt_config_data.qt_pos_drift_rate  = DEF_QT_POS_DRIFT_RATE;
	qt_config_data.qt_max_on_duration = DEF_QT_MAX_ON_DURATION;
	qt_config_data.qt_drift_hold_time = DEF_QT_DRIFT_HOLD_TIME;
	qt_config_data.qt_recal_threshold = RECAL_100;  //DEF_QT_RECAL_THRESHOLD;
	qt_config_data.qt_pos_recal_delay = 10u;        //DEF_QT_POS_RECAL_DELAY;
	
    qt_filter_callback = 0;
	
    sei();
}

void touch_measure(unsigned char* left_slider, unsigned char* right_slider, unsigned char* left_button, unsigned char* right_button)
{
	uint8_t burst_flag = 0;
	do {
		burst_flag = qt_measure_sensors(time_ms) & QTLIB_BURST_AGAIN;
	} while(burst_flag);
	time_ms += 10;
	
	*left_slider = qt_measure_data.qt_touch_status.rotor_slider_values[0];
	*right_slider = qt_measure_data.qt_touch_status.rotor_slider_values[1];
	*left_button = ((qt_measure_data.qt_touch_status.sensor_states[0]&(1<<0))>>0);
	*right_button = ((qt_measure_data.qt_touch_status.sensor_states[0]&(1<<1))>>1);
}
