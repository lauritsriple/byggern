#ifndef TOUCH_H_

void touch_init(unsigned char ls_threshold, unsigned char rs_threshold, unsigned char lb_threshold, unsigned char rb_threshold);
void touch_measure(unsigned char* left_slider, unsigned char* right_slider, unsigned char* left_button, unsigned char* right_button);

#endif
