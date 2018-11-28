#include "main.h"

uint8_t dataArray[4];
uint8_t txdataArray[4];
uint8_t tx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
uint8_t rx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};
uint8_t counter;
uint8_t sendingStatus;

extern float adcConvertedValues[];


int main()
{
	 gpioInit();
	 dmaInit();
	 tim4Init();
	 nvicInit ();
	 adcInit();
	 spiInit();
	 uartInit(USART1);
	
	system_init();
	
	ssd1306_clear_screen(0xFF);
	ssd1306_clear_screen(0x00);
	
	setRegisers(4,2,tx_address,rx_address);
	
	
	while(1)
	{
		delayMs(1);
		
		oledTest();
		/*
		if(nrf24_dataReady())
		{
			nrf24_getData(dataArray);
		}
		
		sendString( "przeslane dane:  ", USART1);
		sendString( "\n", USART1);
		
		for (int i = 0; i<=3 ;i++)
		{
			sendChar(dataArray[i],USART1);
		
		}
		
		*/
		
		
		if (counter == 127)
		{
			counter =0;
		}
		
		for(int  i = 0 ; i<= 3;  i++)
		{
			txdataArray[i] =  counter;
			counter++;			
		}
		
		/* reset przerwania */
		GPIO_SetBits(NRF_PORT, NRF_IRQ);
		
		sendingStatus = sendRadioMessage(txdataArray);
		delayMs(500);
		
		
	/*	adcTest();*/
		
			
	}
}
