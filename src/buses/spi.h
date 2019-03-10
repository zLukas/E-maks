/*
	spi.h
	spi.c header file.
*/

#ifndef _spi_H_
#define _spi_H_

#include <stdio.h>
#include "hardware.h"
#include <stm32f10x_spi.h>


#define PIN_HIGH 1
#define PIN_LOW  0


void spiInit(void);
uint8_t spiSendReceive(uint8_t byte);
void spi_write_nrf24_ce(uint8_t state);
void spi_write_nrf24_csn(uint8_t state);
 
#endif
