/*
	uart.h
	USART header file.
*/

#ifndef _UART1_H_
#define _UART1_H_

#include <stdio.h>
#include <hardware.h>
#include <stm32f10x_usart.h>
 
void uartInit(void);
void sendChar(char c);
void sendString(const char* s);
char uartReceive(void);

#endif
