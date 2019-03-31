#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include "application_layer.h"

typedef struct {
	uint8_t command;
	uint8_t* data;
	uint8_t	id;
} radio_frame;

#endif 
