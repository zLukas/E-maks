#include "uart.h"

USART_InitTypeDef uart;


void uart1init(USART_TypeDef *usartx )
{
	USART_StructInit(&uart);
	uart.USART_BaudRate = 115200;
	USART_Init(usartx, &uart);
	USART_Cmd(usartx, ENABLE);
}

void sendChar(char c, USART_TypeDef *usartx)
{
 while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
 USART_SendData(usartx, c);
}
 
void sendString(const char* s, USART_TypeDef *usartx)
{
 while (*s)
 sendChar(*s++, usartx);
}

char uartReceive(USART_TypeDef *usartx)
{
	char c;
	if (USART_GetFlagStatus(usartx, USART_FLAG_RXNE)) 
		{
			c = USART_ReceiveData(usartx);
		}
	else
		{
		c = ' ';
		}
 return c;
}
