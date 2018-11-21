#include "uart.h"

USART_InitTypeDef uart;

/* uartInit
	-USARTx configuration 
*/
void uartInit(USART_TypeDef *usartx )
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_StructInit(&uart);
	uart.USART_BaudRate = 115200;
	USART_Init(usartx, &uart);
	USART_Cmd(usartx, ENABLE);
}

/* sendChar
	- basic data sending function
*/
void sendChar(char c, USART_TypeDef *usartx)
{
 while (USART_GetFlagStatus(usartx, USART_FLAG_TXE) == RESET);
 USART_SendData(usartx, c);
}
 /* sendString
	-complex data sending function 
*/
void sendString(const char* s, USART_TypeDef *usartx)
{
 while (*s)
 sendChar(*s++, usartx);
}
/* sendString
	-complex data sending function 
*/
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
int __io_putchar(int c)
{
	if (c=='\n')
		sendChar('\r',USART1);
	sendChar(c,USART1);
	return c;
}

