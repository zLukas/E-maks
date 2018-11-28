/*
	i2c.h
	i2c.c header file. i2c defines and constants
*/
#ifndef _I2C_H_
#define _I2C_H_

#include <stdio.h>
#include <hardware.h>
#include <stm32f10x_i2c.h>
#include "LIB_Config.h"

#define OLED_DEVICE_ADDRESS 	0x00 // set correct address
#define OLED_MEMORY_ADDRESS		0x00//set correct address
 
void i2cInit(void);
void oledShowParameters(float kartBatt,float  kartSpd,float  wheels,float  rcBatt);
void oledTest(void);

#endif
