/*
	 hardware.c 
	 peripethial configuration. 
*/

#include "hardware.h"

/*
	peiphethial init structures
*/
GPIO_InitTypeDef gpio;
DMA_InitTypeDef dmaAdc;
DMA_InitTypeDef dmaRx;
DMA_InitTypeDef dmaTx;
TIM_TimeBaseInitTypeDef tim;
TIM_OCInitTypeDef channel;
NVIC_InitTypeDef nvic;
EXTI_InitTypeDef exti;
/*
	ADC variables defined in adc.c file needed for DMA configuration
*/
extern ADC_InitTypeDef adc;
extern int adcValues[];
extern uint8_t Receive_buffer[];


/* gpioInit
	- Pinout configuration
*/
void gpioInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	SysTick_Config(SystemCoreClock / 1000);
	
	GPIO_StructInit(&gpio);	
	/*
		DIO ports
	*/
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

	/* 
		RFM Pinout
	*/
	gpio.GPIO_Pin = RFM_CS;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(RFM_CS_PORT,&gpio);
		
	/*
		Oled reset
	*/
	gpio.GPIO_Pin = SCREEN_RES; 
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SCREEN_RES_PORT,&gpio);
	
	/*
		Uart pinout
	*/
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
	
	/*
		ADC Pinout
	*/
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

	/*
		SPI2 pinout
	*/
	gpio.GPIO_Pin = SPI2_SCK | SPI2_MOSI;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI2_PORT,&gpio);	
	
	gpio.GPIO_Pin = SPI2_MISO;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SPI2_PORT,&gpio);
	
	gpio.GPIO_Pin = SPI2_MISO;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SPI2_PORT,&gpio);
	
	gpio.GPIO_Pin = SPI2_MISO;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SPI2_PORT,&gpio);
	
	gpio.GPIO_Pin = NRF_CS;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(NRF_PORT,&gpio);
	
	gpio.GPIO_Pin = NRF_IRQ;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(NRF_PORT,&gpio);
	
	gpio.GPIO_Pin = NRF_CE;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(NRF_PORT,&gpio);
	
	gpio.GPIO_Pin = TEST_LED;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(TEST_LED_PORT, &gpio);
	
		
}
/* dmaInit
	- DMA  configuration
``-	ADC  channel 1
	-	SPI2 MOSI channel 4
	-	SPI2 MISO channel 5

*/
void dmaInit(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	/*
		ADC channel
	*/
	DMA_StructInit(&dmaAdc);
	dmaAdc.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	dmaAdc.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dmaAdc.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dmaAdc.DMA_MemoryBaseAddr = (uint32_t)adcValues;
	dmaAdc.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dmaAdc.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dmaAdc.DMA_DIR = DMA_DIR_PeripheralSRC;
	dmaAdc.DMA_BufferSize = ADC_CHANNELS;
	dmaAdc.DMA_Mode = DMA_Mode_Circular;
	DMA_Init(DMA1_Channel1, &dmaAdc);
	DMA_Cmd(DMA1_Channel1, ENABLE);

	
	/*
		SPI2 MISO channel
	*/	
	DMA_DeInit(DMA1_Channel4);
	DMA_StructInit(&dmaRx);
	dmaRx.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
	dmaRx.DMA_DIR = DMA_DIR_PeripheralSRC;
	dmaRx.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dmaRx.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dmaRx.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dmaRx.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dmaRx.DMA_Mode = DMA_Mode_Normal;
	dmaRx.DMA_Priority = DMA_Priority_High;
	dmaRx.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel4, &dmaRx);
	
	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
	
	
	/*
		SPI2 MOSI channel
	*/
	DMA_DeInit(DMA1_Channel5);
	DMA_StructInit(&dmaTx);
	dmaTx.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
	dmaTx.DMA_DIR = DMA_DIR_PeripheralDST;
	dmaTx.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dmaTx.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dmaTx.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dmaTx.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dmaTx.DMA_Mode = DMA_Mode_Normal;
	dmaTx.DMA_Priority = DMA_Priority_VeryHigh;
	dmaTx.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5, &dmaTx);
		
	DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
	
}
	
/* tim4Init
	- Timer4 configuration
*/
void tim4Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Prescaler =64-1;   //1 MHZ 1us
	tim.TIM_Period = 1;		//			1MHZ 1 us
	TIM_TimeBaseInit(TIM4, &tim);

	TIM_OCStructInit(&channel);
	channel.TIM_OCMode = TIM_OCMode_PWM1;
	channel.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM4, &channel);
	TIM_OC2Init(TIM4, &channel);
	TIM_Cmd(TIM4, ENABLE);
}
/*
	tim2Init
	supply timer for 	nrf24L01+ 
	- prescalled on 1Mhz
*/
void Tim2Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseStructInit(&tim);

	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Prescaler =  6 - 1;
	tim.TIM_Period = 60 - 1;
	tim.TIM_ClockDivision = TIM_CKD_DIV2;

	TIM_TimeBaseInit(TIM2, &tim);
	
	
}
/*
	nvicInit
	interruption channels (IRQn) configuration
*/
void extiInit(void)
{
		//Utworzenie struktury inicjuj¹cej
	EXTI_InitTypeDef exti;
	EXTI_StructInit(&exti);

	//Poinformowanie uC o Ÿródle przerwania
	GPIO_EXTILineConfig(NRF_PORT_SRC, NRF_IRQ_SRC);

	//Przerwanie na zboczu narastaj¹cym linii EXTI_Linex
	exti.EXTI_Line = NRF_EXTI_LINE;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);

}




void nvicInit (void)
{		
	nvic.NVIC_IRQChannel = TIM4_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 4;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	
	nvic.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	nvic.NVIC_IRQChannel = DMA1_Channel5_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 2;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);


	nvic.NVIC_IRQChannel = TIM2_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 3;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
}

/* delayMs
	-Timer based delay in miliseconds
*/
void delayMs(volatile int time)
{
	TIM4->CNT = 1000*time;
	while(TIM1->CNT);
}
/* delayUs
	-Timer based delay in microseconds
*/
void delayUs(volatile int time)
{
	TIM4->CNT = time;
	while(TIM1->CNT);
}


/*
	EXTI9_5_IRQHandler,
	@breif responsible for receiving data from nrf
*/



