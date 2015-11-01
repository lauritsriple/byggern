/*
 * board.c
 *
 * Created: 01.11.2015 16.06.07
 *  Author: laura
 */ 

void static init_led(){
	LED_DDR |= (1 << LED1);
}

void static init_pwm(){
	PWM_DDR |= (1 << PWM1);
}

void board_init(){
	init_led();
	init_pwm();
}