#include "main.h"


void delayMs(volatile int time)
{
	TIM4->CNT = time;
	while(TIM1->CNT);
}
void testLed(void)
{
	
	GPIO_SetBits( TEST_LED_PORT, TEST_LED);
	delayMs(100);
	GPIO_ResetBits( TEST_LED_PORT, TEST_LED);
	delayMs(500);

}


int main()
{
	void gpioInit(void);s
	void dmaInit(void);
	void tim4Init(void);
	void nvicInit (void);
	
	system_init();
	
	ssd1306_clear_screen(0xFF);
	ssd1306_clear_screen(0x00);
	
	
	while(1)
	{
		oledShowParameters(50,60,10,67);		
		oledShowParameters(40,55,20,65);
		oledShowParameters(30,67,15,60);
		oledShowParameters(20,59,20,48);
		
	}
}
