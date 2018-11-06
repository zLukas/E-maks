#ifndef _ADC_H_
#define _ADC_H_

#include "hardware.h"
#include <stm32f10x_adc.h>
#include "i2c.h"

#define ADC_CHANNELS  4

/*
	adc na dole plytki na pólkolach, poziome X,
	adc przy malych wcieciach pionowe Y
*/
#define ADC_JOY1_X			0
#define ADC_JOY1_Y			1
#define ADC_JOY2_X			3
#define ADC_JOY2_Y			2


/*
	przedzialy napiec w zaleznosci od wpiecia +  i - ptencjometru 
	przesuniecie o 0,5V  
	
	zakres 1
	0.5V -3.3V
	
	zakres 2
	0.0V -2.8V
	
*/

#define ADC_MAX 				3.3
#define ADC_MIN					0.5

#define ADC_MAX_2				2.8
#define ADC_MIN_2				0.0

void adcInit(void);
void ConverToVolts(void);
void adcTest(void);

#endif
