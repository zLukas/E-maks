/*
	nrf24RadioFunction.c
	nrf24 sending and receiving functions.
*/

#include "nrf24RadioFunctions.h"


/*
	setRegister
	function to configure nrf24 parameters.
	- payload: set payload value.
	- channel: set used channel
	- txAdrr: set TX line address
	- rxAdrr: set RX line address
*/
void setRegisers(uint8_t payload, uint8_t channel, uint8_t* txAdrr, uint8_t* rxAdrr)
{
		nrf24_config(channel,payload);
	
		nrf24_tx_address(txAdrr);
		nrf24_rx_address(rxAdrr);
}

/*
	sendRadioMessage
	function to send message via nrf24.
	- data: data to send.
*/
uint8_t sendRadioMessage(uint8_t* data)
{

	uint8_t temp;
	uint8_t transmissionStatus = 0;

	nrf24_send(data);

	while( nrf24_isSending());
	
	temp = nrf24_lastMessageStatus();
	
	if (temp == NRF24_TRANSMISSON_OK)
	{
		 transmissionStatus = 1;
	}
	else if (temp == NRF24_MESSAGE_LOST)
	{
		transmissionStatus = 0;
	}
	
	
	nrf24_powerUpRx();
	
	delayMs(5);
	
	return transmissionStatus;
}

/*
	receiveRadioMessage
	function to receive message via nrf24.
	- data: data to send.
*/
uint8_t * receiveRadioMessage( uint8_t channel, uint8_t payload)
{
	static uint8_t dataArray[4];
	nrf24_config(channel, payload);
	
	
	if (nrf24_dataReady())
	{
		nrf24_getData(dataArray);
		return dataArray;
	}
	else 
	{
		return dataArray;
	}
}

