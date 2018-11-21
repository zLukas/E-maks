#include "nrf24RadioFunctions.h"


uint8_t sendRadioMessage(uint8_t* data, uint8_t* txAddress, uint8_t* rxAddress, uint8_t channel, uint8_t payload)
{
	nrf24_config(channel, payload);
	
	nrf24_tx_address(txAddress);
	nrf24_rx_address(rxAddress);
	
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

uint8_t * receiveRadioMessage(uint8_t* txAddress, uint8_t* rxAddress, uint8_t channel, uint8_t payload)
{
	static uint8_t dataArray[5];
	nrf24_config(channel, payload);
	
	nrf24_tx_address(txAddress);
	nrf24_rx_address(rxAddress);
	
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

