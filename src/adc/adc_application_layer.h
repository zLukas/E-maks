#ifndef _ADC_APPLICATION_LAYER_H_
#define _ADC_APPLICATION_LAYER_H_


/* adjust your include */
# include "adc.h"



typedef struct{
	void (*adc_init)(void);
	float (*adc_conversion)(uint16_t);
}adc_layer_functions;



static adc_layer_functions adc_functions = {
	.adc_init = adcInit,
	.adc_conversion = ConverToVolts
};
	
#endif
