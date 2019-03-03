#include "main.h"


uint8_t dataArray[4];
uint8_t txdataArray[4];
uint8_t tx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
uint8_t rx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};
uint8_t counter;
extern uint8_t sendingStatus;


extern float adcConvertedValues[];
extern  uint8_t myAddress[];
extern	uint8_t txAddress[];
extern 	char dataOut[]; /* data to send */
extern 	char	dataIn[];	/*received data */
uint8_t sendstatus;
int main(void)
{

	
	/*fill data to send Array */
	snprintf(dataOut,sizeof("it works !"),"it works !");
	
	sendstatus = nrf24SendData((uint8_t *)&dataOut);

	ssd1306_clear_screen(0xFF);
	ssd1306_clear_screen(0x00);
	
	while(1)
	{
		
		delayMs(50);		
		oledTest();
		/*adcTest();*/		
	}
}
