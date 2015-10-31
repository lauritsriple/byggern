This driver can be used to add touch support to the USB Multifunction Node (P1000 from Nimron). To add the driver to your project, please follow the steps below:

* Add the following files to your project: 
	touch.c
	touch.h
	touch_api.h
	touch_qm_config.h
	qm_asm_tiny_mega.S

* Copy the library (libavr51g2_16qm_8x_2y_krs_2rs.a) to your project folder.

* Add your project folder to the library search path.
	- AVR Studio 4: Project->Configuration options.., Libraries, Library search path +.
	- AVR Studio 5: Project->Properties, Toolchain, Library search path +.

* Add the library to your project. 
	- AVR Studio 4: Project->Configuration options.., Libraries, Available Link Objects, Select "libavr51g2_16qm_8x_2y_krs_2rs.a", Click Add Library.
	- AVR Studio 5: Project->Properties, Toolchain, Libraries, + "libavr51g2_16qm_8x_2y_krs_2rs.a".

* In the project settings, add the following define values:
	_QMATRIX_
	_ROTOR_SLIDER_
	QT_DELAY_CYCLES=1
	QT_NUM_CHANNELS=16
	QT_MAX_NUM_ROTORS_SLIDERS=2
	NUM_X_LINES=8 
	NUM_Y_LINES=2
	NUM_X_PORTS=2
	PORT_NUM_1=1
	PORT_NUM_2=2
	PORT_X_1=E
	PORT_X_2=C
	PORT_YA=C
	PORT_YB=F
	PORT_SMP=F
	SMP_PIN=5
		- AVR Studio 4: Project->Configuration options.., Custom Options, For each define type "-D" followed by the define (-DPORT_YA=C), click Add.
		- AVR Studio 5: Project->Properties, Toolchain, Symbols +.

* For AVR Studio 5, add the following to Assembler Flags: "-D_QMATRIX_ -D_ROTOR_SLIDER_ -DQT_DELAY_CYCLES=1 -DQT_NUM_CHANNELS=16 -DQT_MAX_NUM_ROTORS_SLIDERS=2 -DNUM_X_LINES=8  -DNUM_Y_LINES=2 -DNUM_X_PORTS=2 -DPORT_NUM_1=1 -DPORT_NUM_2=2 -DPORT_X_1=E -DPORT_X_2=C -DPORT_YA=C -DPORT_YB=F -DPORT_SMP=F -DSMP_PIN=5"

* Include "touch.h" to one of your project files.

* Be sure to call the function "touch_init(unsigned char ls_threshold, unsigned char rs_threshold, unsigned char lb_threshold, unsigned char rb_threshold)" in the start of your application. The typical value for all thresholds are 30. A lower threshold increases the sensitivity.
	- "ls_threshold" is the detect threshold for the left slider
	- "rs_threshold" is the detect threshold for the right slider
	- "lb_threshold" is the detect threshold for the left button
	- "rb_threshold" is the detect threshold for the right button

* Use "touch_measure(unsigned char* left_slider, unsigned char* right_slider, unsigned char* left_button, unsigned char* right_button)" to measure the values of the touch sensors. The parameters are pointers to variables where the measured values will be stored by the function. The slider values are stored as integers between 0 and 255, and the button values are stored as 0 or 1. 