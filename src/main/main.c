#include "main.h"



extern float adcConvertedValues[];


int main()
{
	 gpioInit();
	 dmaInit();
	 tim4Init();
	 nvicInit ();
	 adcInit();
	
	system_init();
	
	ssd1306_clear_screen(0xFF);
	ssd1306_clear_screen(0x00);
	
	
	while(1)
	{
		delayMs(1);
		
		oledTest();
		/*
		adcTest();
		*/
		
		

		
	}
}
