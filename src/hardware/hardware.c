#include "hardware.h"


GPIO_InitTypeDef gpio;
ADC_InitTypeDef adc; 

/* RCC initialization
	- peripethial clocks setups
*/

void rccInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
 
	SysTick_Config(SystemCoreClock / 1000);
}

/* RCC initialization
	- peripethial clocks setups
*/
void gpioInit(void)
{
	GPIO_StructInit(&gpio);	
	
}
