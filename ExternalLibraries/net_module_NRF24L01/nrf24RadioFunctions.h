#ifndef _NRF24RADIOFUNCTIONS_H_
#define _NRF24RADIOFUNCTIONS_H_

#include "nrf24.h"

uint8_t sendRadioMessage(uint8_t* data, uint8_t* txAddress, uint8_t* rxAddress, uint8_t channel, uint8_t payload);
uint8_t * receiveRadioMessage(uint8_t* txAddress, uint8_t* rxAddress, uint8_t channel, uint8_t payload);


#endif
