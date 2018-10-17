#ifndef _spi_H_
#define _spi_H_

#include <stdio.h>
#include <hardware.h>
#include <stm32f10x_spi.h>


void spiInit(void);
uint8_t spiSendReceive(uint8_t byte);
 
#endif
