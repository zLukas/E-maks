/*
	spi.h
	spi.c header file.
*/

#ifndef _spi_H_
#define _spi_H_

#include <stdio.h>
#include <hardware.h>
#include <stm32f10x_spi.h>


void spiInit(void);
uint8_t spiSendReceive(uint8_t byte);
void nrf24_ce_digitalWrite(uint8_t state);
void nrf24_csn_digitalWrite(uint8_t state);
 
#endif
