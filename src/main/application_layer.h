#ifndef _APPLICATION_LAYER_H_
#define _APPLICATION_LAYER_H_


#include <stdio.h>
#include <string.h>
#include "hardware.h"
#include "oledMain.h"
#include "i2c.h"
#include "adc.h"
#include "uart.h"
#include "nrf24.h"

#include "spi.h"



typedef struct{
	void (*hardware_init)(void);
	void (*spi_init) (void);
	void (*delay_ms)(int);
	uint8_t (*spi_send_receive)(uint8_t);
	void (*spi_set_ce_pin)(uint8_t);
	void (*spi_set_csn_pin)(uint8_t);
	uint16_t* adc_values;
	
}application_layer;


static application_layer hardware_functions = {
	.hardware_init = hardwareInit,
	.spi_init = spiInit,
	.delay_ms = delayMs,
	.spi_send_receive = spiSendReceive,
	.spi_set_ce_pin = spi_write_nrf24_ce,
	.spi_set_csn_pin = spi_write_nrf24_csn
};

#endif
