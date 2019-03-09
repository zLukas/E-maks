#ifndef _HARDWARE_APPLICATION_LAYER_H_
#define _HARDWARE_APPLICATION_LAYER_H_

/* adjust includes */
#include "hardware.h"


typedef struct{
	void (*hardware_init)(void);
	void (*timer_delay)(volatile int);
	uint16_t* timer_counter;
}hardware_layer_functions;

/* add custom hardware library functions */
static hardware_layer_functions hardware_functions ={
	.hardware_init = hardwareInit,
	.timer_delay = delayMs,
	.timer_counter = &(TIM2->CNT)
};


#endif
