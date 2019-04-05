#include "main.h"


int main(void)
{
	
	hardware_functions.hardware_init();
	
	while(1)
	{
		
		oled_demo();		
		
	}
}
