#include "Periph_config.h"

void RCC_config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
}

void GPIO_config()
{
	GPIO_InitTypeDef gpio;
	GPIO_StructInit(&gpio);

	gpio.GPIO_Pin = GPIO_Pin_2;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_3;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15; // SCK, MOSI
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_14; // MISO
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_7; // CS
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &gpio);

	GPIO_SetBits(GPIOC, GPIO_Pin_7);

	gpio.GPIO_Pin = GPIO_Pin_8; //IRQ
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_9; // CE
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &gpio);

	////////////////////////////////////////////

	gpio.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_7; // SCK, MOSI
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_6; // MISO
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_4; // CS
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &gpio);

	GPIO_SetBits(GPIOC, GPIO_Pin_4);

	gpio.GPIO_Pin = GPIO_Pin_5; //IRQ
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_0; // CE
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &gpio);
}

void SPI_config()
{
	SPI_InitTypeDef spi;
	SPI_StructInit(&spi);

	spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi.SPI_Mode = SPI_Mode_Master;
	spi.SPI_DataSize = SPI_DataSize_8b;
	spi.SPI_CPOL = SPI_CPOL_Low;
	spi.SPI_CPHA = SPI_CPHA_1Edge;
	spi.SPI_NSS = SPI_NSS_Soft;
	spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	spi.SPI_FirstBit = SPI_FirstBit_MSB;
	spi.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &spi);

	SPI_Cmd(SPI2, ENABLE);

	//////////////////////////////////////

	spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi.SPI_Mode = SPI_Mode_Master;
	spi.SPI_DataSize = SPI_DataSize_8b;
	spi.SPI_CPOL = SPI_CPOL_Low;
	spi.SPI_CPHA = SPI_CPHA_1Edge;
	spi.SPI_NSS = SPI_NSS_Soft;
	spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	spi.SPI_FirstBit = SPI_FirstBit_MSB;
	spi.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &spi);

	SPI_Cmd(SPI1, ENABLE);
}

void USART_config()
{
	USART_InitTypeDef uart;
	USART_StructInit(&uart);

	uart.USART_BaudRate = 115200;
	USART_Init(USART2, &uart);
	USART_Cmd(USART2, ENABLE);
}

void SysTick_config()
{
	//Ustawienie czêstotliwoœci taktowania
	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	//Ustawienie wartoœci pocz¹tkowej zliczania
	SysTick_Config(SystemCoreClock /100000);
}

void NVIC_config()
{
	//Utworzenie struktury inicjuj¹cej
	NVIC_InitTypeDef nvic;

	//Wybór grupy przerwañ
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

void EXTI_config()
{
	//Utworzenie struktury inicjuj¹cej
	EXTI_InitTypeDef exti;
	EXTI_StructInit(&exti);

	//Poinformowanie uC o Ÿródle przerwania
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource8);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);

	//Przerwanie na zboczu narastaj¹cym linii EXTI_Linex
	exti.EXTI_Line = EXTI_Line8;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);

	//////////////////////////////////////

	exti.EXTI_Line = EXTI_Line5;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
}

void DMA_config()
{
	DMA_StructInit(&dmarx);
	DMA_DeInit(DMA1_Channel4);

	dmarx.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
	dmarx.DMA_DIR = DMA_DIR_PeripheralSRC;
	dmarx.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dmarx.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dmarx.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dmarx.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dmarx.DMA_Mode = DMA_Mode_Normal;
	dmarx.DMA_Priority = DMA_Priority_High;
	dmarx.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel4, &dmarx);

	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);

	DMA_DeInit(DMA1_Channel5);

	dmatx.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
	dmatx.DMA_DIR = DMA_DIR_PeripheralDST;
	dmatx.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dmatx.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dmatx.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dmatx.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dmatx.DMA_Mode = DMA_Mode_Normal;
	dmatx.DMA_Priority = DMA_Priority_VeryHigh;
	dmatx.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5, &dmatx);

	DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
}

void TIM_config()
{
	TIM_TimeBaseInitTypeDef tim;
	TIM_TimeBaseStructInit(&tim);

	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Prescaler =  6 - 1;
	tim.TIM_Period = 60 - 1;
	tim.TIM_ClockDivision = TIM_CKD_DIV2;

	TIM_TimeBaseInit(TIM2, &tim);
}
