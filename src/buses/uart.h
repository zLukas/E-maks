#ifndef _UART1_H_
#define _UART1_H_

#include <stdio.h>
#include <hardware.h>
#include <stm32f10x_usart.h>
 
void uart1init(USART_TypeDef *usartx );
void sendChar(char c, USART_TypeDef *usartx);
void sendString(const char* s, USART_TypeDef *usartx);
char uartReceive(USART_TypeDef *usartx);

#endif
