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
	nrf24Init();
	
	uint8_t sendStatus;
	/*fill data to send Array */
	snprintf(dataOut,sizeof("it works !"),"it works !");
	
	while(1)
	{
		
		hardware_functions.delay_ms(50);		
		hardware_functions.show_on_display((float[]){20.4, 44.2, 10.9, 30.1});
		
		if(sendStatus != 0xFF)
		{
			sendStatus = nrf24Transmit((uint8_t*)&dataOut);
			
		}
		nrf24Receive((uint8_t*)dataIn);		
	}
}
