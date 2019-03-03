/*
	adc.h
	adc.c header file. Defines and constant values defines
*/

#ifndef _ADC_H_
#define _ADC_H_

#include "hardware.h"
#include <stm32f10x_adc.h>

#define ADC_CHANNELS  4

#define ADC_JOY1_X			0
#define ADC_JOY1_Y			1
#define ADC_JOY2_X			3
#define ADC_JOY2_Y			2

#define ADC_MAX 				3.3
#define ADC_MIN					0.5

#define ADC_MAX_2				2.8
#define ADC_MIN_2				0.0

static uint16_t adcValues[ADC_CHANNELS];


void adcInit(void);
float ConverToVolts(uint16_t inputData);
void adcTest(void);

#endif
