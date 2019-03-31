#ifndef _APPLICATION_LAYER_H_
#define _APPLICATION_LAYER_H_

/*write your own includes*/

#include <stdint.h>
#include "nrf24.h"
#include "stm32f1xx_hal.h"

typedef struct{
	void (*hardware_init)(void);
	void (*spi_init) (void);
	void (*delay_ms)(int);
	uint8_t (*spi_send_receive)(uint8_t);
	void (*spi_set_ce_pin)(uint8_t);
	void (*spi_set_csn_pin)(uint8_t);
	uint16_t* adc_values;
	void (*show_on_display)(float*);
	
}application_layer;

static application_layer hardware_functions /*= {
	.hardware_init = hardwareInit,
	.spi_init = spiInit,
	.delay_ms = delayMs,
	.spi_send_receive = spiSendReceive,
	.spi_set_ce_pin = spi_write_nrf24_ce,
	.spi_set_csn_pin = spi_write_nrf24_csn,
	.show_on_display = write_oled_lines
}*/;

#endif
