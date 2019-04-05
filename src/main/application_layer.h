#ifndef _APPLICATION_LAYER_H_
#define _APPLICATION_LAYER_H_

/* change it to ONBOARD_CONTROLER if necessary*/
#define RADIO_CONTROLER

#include <stdint.h>
#include "nrf24.h"
#include "stm32f1xx_hal.h"
#include "hal_init.h"



/* 
* RADIO_CONTROLER for pad 
* ON_BOARD controler for vechicle board
*/
#if defined(RADIO_CONTROLER)

#endif

typedef struct{
	void (*hardware_init)(void);
	void (*delay_ms)(volatile uint16_t);
	uint8_t (*spi_send_receive)(uint8_t);
	void (*spi_set_ce_pin)(uint8_t);
	void (*spi_set_csn_pin)(uint8_t);		
	uint16_t* adc_values;			
	void (*i2c_send)(uint16_t, uint16_t, uint8_t*); /*for pad radio controler */
}application_layer;

static application_layer hardware_functions = {
	.hardware_init = hal_init,
	.adc_values = hal_adc_values,
	.spi_set_ce_pin = set_nrf_ce_pin,
	.spi_set_csn_pin = set_nrf_cs_pin,
	.spi_send_receive = spi_transmit_receive,
	.delay_ms = hal_delay_ms,
	.i2c_send =hal_i2c_send
};
#endif
