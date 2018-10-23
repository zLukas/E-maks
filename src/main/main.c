#include "main.h"

void delayMs(volatile int time)
{
	TIM4->CNT = time;
	while(TIM1->CNT);
}
void testLed(void)
{
	
	GPIO_SetBits( TEST_LED_PORT, TEST_LED);
	delayMs(500);
	GPIO_ResetBits( TEST_LED_PORT, TEST_LED);
	delayMs(500);

}


int main()
{
	oledSample();
	while(1)
	{
		testLed();
	}
}
