#ifndef _I2C_H_
#define _I2C_H_

#include <stdio.h>
#include <hardware.h>
#include <stm32f10x_i2c.h>

#define DEVICE_ADDRESS 				  0x00 // ustawic poprawny addres urzadzenia
#define DEVICE_MEMORY_ADDRESS	0x00//ustwic poprawny dla urzadzenia

void i2cInit(void);
uint8_t findAddress(uint32_t deviceAddress);
void setDeviceMemoryAddress(uint32_t DeviceMemoryAddress);
void i2cSend(uint32_t deviceMemoryAddress , const void* data, int size);
int i2cReveive( uint32_t deviceMemoryAddress , const void* data, int size);
#endif
