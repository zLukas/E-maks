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
	void gpioInit(void);
	void dmaInit(void);
	void tim4Init(void);
	void nvicInit (void);
	
	system_init();
	
	ssd1306_clear_screen(0xFF);
	delay_ms(1000);
	ssd1306_clear_screen(0x00);
	ssd1306_display_string(18, 0, "1.3inch OLED", 16, 1);
	ssd1306_display_string(0, 16, "starting screen", 16, 1);
	ssd1306_refresh_gram();
	delay_ms(1000);
	
	oledShowParameters(50,32,15,67);
	
	
	
	while(1)
	{
		testLed();
	}
}
