#include "nrf24.h"


/* My address */
uint8_t myAddress[] = {
    0xE7,
    0xE7,
    0xE7,
    0xE7,
    0xE7
};
/* Receiver address */
uint8_t txAddress[] = {
    0x7E,
    0x7E,
    0x7E,
    0x7E,
    0x7E
};


char dataOut[PAYLOAD_SIZE], dataIn[PAYLOAD_SIZE];

/*
	configure nrf24
*/
void nrf24Set(void)
{
		TM_NRF24L01_Init(CHANNEL,PAYLOAD_SIZE);
		TM_NRF24L01_SetRF(DATA_RATE, OUTPUT_POWER);
		TM_NRF24L01_SetMyAddress(myAddress);
		TM_NRF24L01_SetTxAddress(txAddress);
}


/*
	send some data via nrf24
*/

uint8_t nrf24SendData(uint8_t* dataToSend)
{
	uint8_t sendingStatus = 0;
	
	TM_NRF24L01_PowerUpTx();
	
	TM_NRF24L01_Transmit_Status_t transmissionStatus;
	TM_NRF24L01_Transmit(dataToSend);
	
	TIM4->CNT = 0;
	transmissionStatus = TM_NRF24L01_GetTransmissionStatus();
	while(transmissionStatus == 0)
	{
		if(TIM4->CNT == 999)
		{
			sendingStatus = MESSAGE_NOT_SENT;
			return sendingStatus;
		}
		transmissionStatus = TM_NRF24L01_GetTransmissionStatus();
	}
		
	TM_NRF24L01_PowerUpRx();
	sendingStatus =MESSAGE_SENT;
	return sendingStatus;
}

/*
	read received nrf24 data
*/
void nrf24ReceiveData(uint8_t* data)
{
	TM_NRF24L01_PowerUpRx();
	if(TM_NRF24L01_DataReady() == 1)
	{
		TM_NRF24L01_GetData(data);
	}

}
	
