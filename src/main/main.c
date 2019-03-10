#include "main.h"

extern float adcConvertedValues[];
extern  uint8_t myAddress[];
extern	uint8_t txAddress[];
extern 	char dataOut[]; /* data to send */
extern 	char	dataIn[];	/*received data */
uint8_t sendstatus;
int main(void)
{
	
	hardware_functions.hardware_init();
	hardware_functions.spi_init();
	nrf24Init();
	
	uint8_t sendStatus;
	/*fill data to send Array */
	snprintf(dataOut,sizeof("it works !"),"it works !");

	ssd1306_clear_screen(0xFF);
	ssd1306_clear_screen(0x00);
	
	while(1)
	{
		
		hardware_functions.delay_ms(50);		
		oledTest();		

		if(sendStatus != 0xFF)
		{
			sendStatus = nrf24Transmit((uint8_t*)&dataOut);
		}
	}
}
