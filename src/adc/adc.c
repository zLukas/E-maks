/*
	adc.c 
	ADC module initialization file.
*/

#include "adc.h"
#include "LIB_Config.h"


/*
	variables:
	- adcValue holds raw ADC data
	-	adcConvertedValues holds calulated voltage data
*/
uint16_t adcValues[ADC_CHANNELS];
float adcConvertedValues[ADC_CHANNELS];
ADC_InitTypeDef adc;
/* 
	adcInit
	-ADC and 4  ADC channels configuration 
*/
void adcInit(void)
{
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	 RCC_ADCCLKConfig(RCC_PCLK2_Div6);
 
	ADC_StructInit(&adc);
	adc.ADC_ScanConvMode = ENABLE;
	adc.ADC_ContinuousConvMode = ENABLE;
	adc.ADC_NbrOfChannel = ADC_CHANNELS;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_Init(ADC1, &adc);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_71Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_71Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_71Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_71Cycles5);
	
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1));

	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));

  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}


/*
	convertToVolts
	-function for converting raw adc int value to float voltage value
*/
void ConverToVolts(void)
{
	for (int i = 0 ; i<= ADC_CHANNELS-1;i++)
	{
		adcConvertedValues[i]= (float)adcValues[i] *3.3/4096.0f;
	}
}

/*
	adcTest
	- function created for testing adc functionality
	- function shows adc values on oled screen

*/
void adcTest(void)
{
	char adc1[20];
	char adc2[20];
	char adc3[20];
	char adc4[20];
/*
		sprintf( char array, "sample text i %f %d", value to replace %f, walu to replace %d)
*/
	ConverToVolts();
	sprintf(adc1, "adc1 j1x: %.1f ",adcConvertedValues[ADC_JOY1_X]);
	sprintf(adc2, "adc2 j1y: %.1f ", adcConvertedValues[ADC_JOY1_Y]);
	sprintf(adc3, "adc3 j2x: %.1f ",adcConvertedValues[ADC_JOY2_X]);
	sprintf(adc4, "adc4 j2y: %.1f ",adcConvertedValues[ADC_JOY2_Y]);
/*
	ssd1306_display_string(Xpos,Ypos, (uint8_t)pointer on char wtih data to show, Font?, dont't know what does this argument but wit "0" not working);
*/	
	ssd1306_display_string(2, 0, (uint8_t *)adc1 , 14, 1);
	ssd1306_display_string(2, 16,(uint8_t *)adc2 , 14, 1);
	ssd1306_display_string(2, 32,(uint8_t *)adc3  , 14, 1);
	ssd1306_display_string(2, 48,(uint8_t *)adc4, 14, 1);
	ssd1306_refresh_gram();
}
