#ifndef _NRF24_H_
#define _NRF24_H_

#include "tm_stm32f4_nrf24l01.h"

#define PAYLOAD_SIZE  32  /* max 32 */
#define CHANNEL				15
#define DATA_RATE			TM_NRF24L01_DataRate_2M /* enum: tm_stm32f4_nrf24l01.h*/
#define OUTPUT_POWER	TM_NRF24L01_OutputPower_M18dBm /* enum: tm_stm32f4_nrf24l01.h*/

#define MESSAGE_LOST 			0
#define	MESSAGE_NOT_SENT 	1
#define MESSAGE_SENT 			2

void nrf24Set(void);
uint8_t nrf24SendData(uint8_t* dataToSend);
void nrf24ReceiveData(uint8_t* data);

#endif

