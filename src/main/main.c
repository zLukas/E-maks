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
	
	oledSample();
	while(1)
	{
		testLed();
	}
}
