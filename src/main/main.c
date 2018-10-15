#include "main.h"

void delayMs(volatile int time)
{
	TIM4->CNT = time;
	while(TIM1->CNT);
}
int main()
{
	while(1);
}
