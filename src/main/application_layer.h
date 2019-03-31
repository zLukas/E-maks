#ifndef _APPLICATION_LAYER_H_
#define _APPLICATION_LAYER_H_

/*write your own includes*/

#include <stdint.h>
#include "nrf24.h"
#include "stm32f1xx_hal.h"
#include "hal_init.h"

typedef struct{
	void (*hardware_init)(void);
	void (*delay_ms)(int);
	uint8_t (*spi_send_receive)(uint8_t);
	void (*spi_set_ce_pin)(uint8_t);
	void (*spi_set_csn_pin)(uint8_t);
	uint16_t* adc_values;
	void (*show_on_display)(float*);
	
}application_layer;

static application_layer hardware_functions = {
	.hardware_init = hal_init
};
#endif
