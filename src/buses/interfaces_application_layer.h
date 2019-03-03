#ifndef _INTERFACES_APPLICATION_LAYER_H_
#define _INTERFACES_APPLICATION_LAYER_H_

/* adjust yours includes */
#include "spi.h"
#include "uart.h"

typedef  struct{
	void (*spi_init)(void);
	uint8_t (*spi_send_receive)(uint8_t);
	void (*uart_init)(void);
	void (*uart_send)(char);
	char (*uart_receive)(void);
	void (*can_init)(void);
	void (*can_send)(uint8_t*);
}interfaces_layer_functions;

static interfaces_layer_functions interfaces_functions = {
	.spi_init				  = 	spiInit,
	.spi_send_receive = 	spiSendReceive,
	.uart_init 				= 	uartInit,
	.uart_send  			= 	sendString,
	.uart_receive 		= 	uartReceive
};





#endif