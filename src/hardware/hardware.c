#include "hardware.h"


GPIO_InitTypeDef gpio;
ADC_InitTypeDef adc; 

/* RCC initialization
	- peripethial clocks setups
*/

void rccInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
 
	SysTick_Config(SystemCoreClock / 1000);
}

/* gpioInit
	- pinout configuration
*/
void gpioInit(void)
{
	GPIO_StructInit(&gpio);	
	
	gpio.GPIO_Pin = DIO0;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DIO0_PORT,&gpio); 
	
	gpio.GPIO_Pin = DIO1|DIO2|DIO3|DIO4;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DIO14_PORT,&gpio); 
	
	gpio.GPIO_Pin = DIO5;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DIO5_PORT,&gpio);
/*	
	gpio.GPIO_Pin = DC;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DC_PORT,&gpio);
*/
	gpio.GPIO_Pin = RFM_CS;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(RFM_CS_PORT,&gpio);
/*	
	gpio.GPIO_Pin = NRF_CS;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = NRF_IRQ;
	//gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = NRF_CE;
	//gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(NRF_PORT,&gpio);
*/	
	gpio.GPIO_Pin = SCREEN_RES; 
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SCREEN_RES_PORT,&gpio);
	
	
	gpio.GPIO_Pin = UART1_TX; 
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(UART1_PORT,&gpio);
	
	gpio.GPIO_Pin = UART1_RX; 
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(UART1_PORT,&gpio);
	
	gpio.GPIO_Pin = UART2_TX; 
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(UART2_PORT,&gpio);
	
	gpio.GPIO_Pin = UART2_RX; 
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(UART2_PORT,&gpio);
	
	gpio.GPIO_Pin = JOY1_X | JOY1_Y | JOY2_X | JOY2_Y;
	gpio.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(JOYS_PORT,&gpio); 
	
	gpio.GPIO_Pin = VBAT;
	gpio.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(VBAT_PORT,&gpio); 
	
	gpio.GPIO_Pin = BUTTON1;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(VBAT_PORT,&gpio);
	
	gpio.GPIO_Pin = BUTTON2 | BUTTON3 | BUTTON4 | BUTTON5 | BUTTON6;
	gpio.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(BUTTON2_6_PORT,&gpio);
	
/*
	gpio.GPIO_Pin = BLK;
	gpio.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(BLK_PORT,&gpio);
*/
	gpio.GPIO_Pin = I2C1_SCL | I2C1_SDA;
	gpio.GPIO_Mode = GPIO_Mode_AF_OD;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(I2C1_PORT,&gpio);
		
	gpio.GPIO_Pin = SPI2_SCK | SPI2_MOSI;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI2_PORT,&gpio);	
	gpio.GPIO_Pin = SPI2_MISO;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SPI2_PORT,&gpio);
		
}
void dmaInit(void)
{}
	
void tim4Init(void)
{}
	
void nvicInit (void)
{}
