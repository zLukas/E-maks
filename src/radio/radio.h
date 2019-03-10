#ifndef _RADIO_H_
#define _RADIO_H_

#include "tm_stm32f4_nrf24l01.h"

#define PAYLOAD_SIZE	32
#define CHANNEL				15

static char dataOut[PAYLOAD_SIZE]; /* data to send */
static char	dataIn[PAYLOAD_SIZE];	/*received data */

void nrf24Init(void);
uint8_t nrf24Transmit(uint8_t* data);

#endif
