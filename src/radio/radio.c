#include "radio.h"

/* My address */
uint8_t MyAddress[] = {
    0xE7,
    0xE7,
    0xE7,
    0xE7,
    0xE7
};
/* Receiver address */
uint8_t TxAddress[] = {
    0x7E,
    0x7E,
    0x7E,
    0x7E,
    0x7E
};
void send_multiple_radio_data(uint16_t* data){
	
}

void nrf24Init(void)
{
	TM_NRF24L01_Init(CHANNEL, PAYLOAD_SIZE);
	TM_NRF24L01_SetRF(TM_NRF24L01_DataRate_2M,TM_NRF24L01_OutputPower_M18dBm);
    TM_NRF24L01_SetMyAddress(MyAddress);
    TM_NRF24L01_SetTxAddress(TxAddress);
	
}


uint8_t nrf24Transmit(uint8_t* data)
{
	TM_NRF24L01_Transmit(data);
	
	hardware_functions.delay_ms(600);
	TM_NRF24L01_PowerUpRx();
	
	/* Wait received data, wait max 100ms, if time is larger, then data were probably lost */ 	
		uint8_t	attempt = 100;
		while (!TM_NRF24L01_DataReady() && attempt != 0)
		{
			attempt--;
		}
			
		/* Check transmit status */
			if (TM_NRF24L01_GetTransmissionStatus() == TM_NRF24L01_Transmit_Status_Ok) 
			{
				/* Transmit went OK */
				return 0x01;
			}
			else if (TM_NRF24L01_GetTransmissionStatus() == TM_NRF24L01_Transmit_Status_Lost) 
			{
				/* Message was LOST */
				return 0x00;
			} 
			else 
			{
				return 0xFF;
			}
}

void nrf24Receive(uint8_t* data)
{
	while(TM_NRF24L01_DataReady() == 0);
	TM_NRF24L01_GetData(data);
}
