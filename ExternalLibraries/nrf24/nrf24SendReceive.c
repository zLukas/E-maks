#include "nrf24SendReceive.h"
/*
  Keil project for NRF24L01+ transceiver
 *
 *    Transmitter code
 *
 *    Before you start, select your target, on the right of the "Load" button
 *
 *    @author        Tilen Majerle
 *    @email        tilen@majerle.eu
 *    @website    http://stm32f4-discovery.net
 *    @ide        Keil uVision 5
 *    @packs        STM32F4xx Keil packs version 2.2.0 or greater required
 *    @stdperiph    STM32F4xx Standard peripheral drivers version 1.4.0 or greater required
 *
*/
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
 
uint8_t dataOut[32], dataIn[32];

typedef struct 
{
	uint8_t myAddress[5];
	uint8_t receiverAddress[5];
	uint8_t channel;
	uint8_t payload;
	TM_NRF24L01_OutputPower_t outPutPower;
	TM_NRF24L01_DataRate_t transmitionspeed;
	
}nrf24params;

struct nrf24message
{
	uint8_t data[32];
	uint8_t messageStatus;
	uint8_t ack;
};


void nrf24SetParameters(nrf24params params)
{	
		TM_NRF24L01_Init(params.channel, params.payload);
		TM_NRF24L01_SetMyAddress(params.myAddress);
		TM_NRF24L01_SetTxAddress(params.receiverAddress);
		TM_NRF24L01_SetRF(params.transmitionspeed, params.outPutPower);
}


void nrf24Transmit(void) 
{
	
    TM_NRF24L01_Transmit_Status_t transmissionStatus;
		uint8_t sendingStatus = 0;
    
    
    TM_NRF24L01_Init(15, 32);
    
    /* Set 2MBps data rate and -18dBm output power */
    TM_NRF24L01_SetRF(TM_NRF24L01_DataRate_2M, TM_NRF24L01_OutputPower_M18dBm);
    
    /* Set my address, 5 bytes */
    TM_NRF24L01_SetMyAddress(MyAddress);
    /* Set TX address, 5 bytes */
    TM_NRF24L01_SetTxAddress(TxAddress);
    
		delayMs(500);

    /* Fill data with something */
    sprintf((char *)dataOut, "abcdefghijklmnoszxABCDEFCBDA");
		
    /* send data */       
    TM_NRF24L01_Transmit(dataOut);
       
		/*wait o send */
    do 
		{
      transmissionStatus = TM_NRF24L01_GetTransmissionStatus();
    } 
		while (transmissionStatus == TM_NRF24L01_Transmit_Status_Sending);

    /* switch to RX mode */        
    TM_NRF24L01_PowerUpRx();
            
		/* Check transmit status */
    if (transmissionStatus == TM_NRF24L01_Transmit_Status_Ok) 
		{
				sendingStatus = 1;
		} 
		else if (transmissionStatus == TM_NRF24L01_Transmit_Status_Lost) 
		{
      /* Message was LOST */
			sendingStatus = 0;
    }
		else
		{
      /* This should never happen */
      sendingStatus = 2;
		}

}
        

void Receive(void)
{
uint8_t dataIn[32];



    
    /* Initialize NRF24L01+ on channel 15 and 32bytes of payload */
    /* By default 2Mbps data rate and 0dBm output power */
    /* NRF24L01 goes to RX mode by default */
    TM_NRF24L01_Init(15, 32);
    
    /* Set RF settings, Data rate to 2Mbps, Output power to -18dBm */
    TM_NRF24L01_SetRF(TM_NRF24L01_DataRate_2M, TM_NRF24L01_OutputPower_M18dBm);
    
    /* Set my address, 5 bytes */
    TM_NRF24L01_SetMyAddress(MyAddress);
    /* Set TX address, 5 bytes */
    TM_NRF24L01_SetTxAddress(TxAddress);
 
 
        /* If data is ready on NRF24L01+ */
				TIM4->CNT = 0;
        while (!TM_NRF24L01_DataReady() && TIM4->CNT < 999);
					
					if (TM_NRF24L01_DataReady())
					{
            /* Get data from NRF24L01+ */       
           TM_NRF24L01_GetData(dataIn);
					}
					else
					{
						dataIn[1] = 0xFF;
						dataIn[2] = 0x00;
						dataIn[3] = 0xFF;
						dataIn[4] = 0x00;
						dataIn[5] = 0xFF;
						dataIn[6] = 0x00;
					}
                 
}
 

