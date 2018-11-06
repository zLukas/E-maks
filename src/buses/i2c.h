#ifndef _I2C_H_
#define _I2C_H_

#include <stdio.h>
#include <hardware.h>
#include <stm32f10x_i2c.h>

#define DEVICE_ADDRESS 				  0x00 // ustawic poprawny addres urzadzenia
#define DEVICE_MEMORY_ADDRESS	0x00//ustwic poprawny dla urzadzenia

#define OLED_BASED_I2C_FUNTION
//#define FORBOT_BASED_I2C_FUNCTIONS 

void i2cInit(void);
void oledShowParameters(float kartBatt,float  kartSpd,float  wheels,float  rcBatt);
void oledTest(void);

#endif
