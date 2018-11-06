#include "stm32f10x.h"
#include "Library_includes.h"

volatile uint16_t timer_ms = 11;

void send_char(char c)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2, c);
}

int __io_putchar(int c)
{
	if (c=='\n')
		send_char('\r');
	send_char(c);
	return c;
}

void delay(uint16_t _time_delay)
{
	timer_ms = _time_delay;
	while(timer_ms);
}

void SysTick_Handler(void)
{
    if (timer_ms) {
        timer_ms--;
    }
}

void EXTI9_5_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line8)!= RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line8);
		nRF_Read_REGISTER(STATUS);
		flag_to_analize = 1;
	}

	if(EXTI_GetITStatus(EXTI_Line5)!= RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line5);

		if(Get_status_flag_2(RX_DR_FLAG) == 1)
		{
			Clear_status_flag_2(RX_DR_FLAG);
			SPI_receive(2);
			printf("Odebrane -> 0x%x%x\n", Receive_buffer[0], Receive_buffer[1]);
		}
		if(Get_status_flag_2(TX_DS_FLAG) == 1)
		{
			Clear_status_flag_2(TX_DS_FLAG);
		}
		if(Get_status_flag_2(MAX_RT_FLAG) == 1)
		{
			Clear_status_flag_2(MAX_RT_FLAG);
		}
	}
}

void DMA1_Channel4_IRQHandler()
{
	if (DMA_GetFlagStatus(DMA1_FLAG_TC4) == SET)
	{
		DMA_ClearFlag(DMA1_FLAG_TC4);
		SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Rx, DISABLE);
		DMA_Cmd(DMA1_Channel4, DISABLE);
		nRF_SPI_stop_transfer();

		if(preparing_to_send == 1)
		{
			preparing_to_send = 0;
			GPIO_SetBits(GPIOC, GPIO_Pin_9);
			TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
			TIM_Cmd(TIM2, ENABLE);
		}
		else if(flag_to_analize == 1)
			nRF_Analyze_flags();
		else if(initialization_in_process == 1)
		{
			initialize_counter++;
			nRF_Init();
		}

		if (count_lost_packets_request == 1)
		{
			count_lost_packets_request++;
			nRF_Read_REGISTER(OBSERVE_TX);
		}
		else if (count_lost_packets_request == 2)
			nRF_Analyze_lost();

		if (count_retry_request == 1)
		{
			count_retry_request++;
			nRF_Read_REGISTER(OBSERVE_TX);
		}
		else if (count_retry_request == 2)
			nRF_Analyze_retransmited();

		if (check_fifo_request == 1)
		{
			nRF_Analyze_FIFO();
		}
	}
}

void DMA1_Channel5_IRQHandler()
{
	if (DMA_GetFlagStatus(DMA1_FLAG_TC5) == SET)
	{
		DMA_ClearFlag(DMA1_FLAG_TC5);
		SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Tx, DISABLE);
		DMA_Cmd(DMA1_Channel5, DISABLE);
	}
}

void TIM2_IRQHandler()
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
		TIM_Cmd(TIM2, DISABLE);
		GPIO_ResetBits(GPIOC, GPIO_Pin_9);
	}
}

int main(void)
{
	RCC_config();
	GPIO_config();
	SPI_config();
	USART_config();
	SysTick_config();
	TIM_config();
	DMA_config();
	NVIC_config();
	EXTI_config();

	delay(1030);

	initialization_in_process = 1;

	nRF_Init();

	while(1)
	{

	}
}
