#ifndef _I2C_H_
#define _I2C_H_

#include <stdio.h>
#include <hardware.h>
#include <stm32f10x_i2c.h>

#define OLED_DEVICE_ADDRESS 	0x00 // ustawic poprawny addres urzadzenia
#define OLED_MEMORY_ADDRESS		0x00//ustwic poprawny dla urzadzenia
 
void i2cInit(void);
void oledShowParameters(float kartBatt,float  kartSpd,float  wheels,float  rcBatt);
void oledTest(void);

#endif
