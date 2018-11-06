#include "hardware.h"


GPIO_InitTypeDef gpio;
DMA_InitTypeDef dma;
TIM_TimeBaseInitTypeDef tim;
TIM_OCInitTypeDef channel;
NVIC_InitTypeDef nvic;
extern ADC_InitTypeDef adc;
extern int adcValues[];

/* gpioInit
	- Pinout configuration
*/
void gpioInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	SysTick_Config(SystemCoreClock / 1000);
	
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
	

	gpio.GPIO_Pin = BLK;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(BLK_PORT,&gpio);

		
	gpio.GPIO_Pin = SPI2_SCK | SPI2_MOSI;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI2_PORT,&gpio);	
	gpio.GPIO_Pin = SPI2_MISO;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SPI2_PORT,&gpio);
	
	gpio.GPIO_Pin = TEST_LED;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(TEST_LED_PORT, &gpio);
		
}
/* dmaInit
	- DMA  configuration
*/
void dmaInit(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_StructInit(&dma);
	dma.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dma.DMA_MemoryBaseAddr = (uint32_t)adcValues;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dma.DMA_DIR = DMA_DIR_PeripheralSRC;
	dma.DMA_BufferSize = ADC_CHANNELS;
	dma.DMA_Mode = DMA_Mode_Circular;
	DMA_Init(DMA1_Channel1, &dma);
	DMA_Cmd(DMA1_Channel1, ENABLE);
}
	
/* dmaInit
	- Timer configuration
*/
void tim4Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Prescaler =64-1;   //1 MHZ
	tim.TIM_Period = 1000-1;		//1kHz 
	TIM_TimeBaseInit(TIM4, &tim);

	TIM_OCStructInit(&channel);
	channel.TIM_OCMode = TIM_OCMode_PWM1;
	channel.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM4, &channel);
	TIM_OC2Init(TIM4, &channel);
	TIM_Cmd(TIM4, ENABLE);
}
/* delayMs
	-Timer base delay in microseconds
*/
void delayMs(volatile int time)
{
	TIM4->CNT = time;
	while(TIM1->CNT);
}


/* dmaInit
	-Timer event configuration
*/
void nvicInit (void)
{
	
	
	nvic.NVIC_IRQChannel = TIM4_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
}
