/*
	uart.c
	USART configuration files.
*/

#include "uart.h"

/*
	uart unit structure.
*/
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
	 one char sending.
	- charToSend : char to send
*/
void sendChar(char charToSend, USART_TypeDef *usartx)
{
 while (USART_GetFlagStatus(usartx, USART_FLAG_TXE) == RESET);
 USART_SendData(usartx, charToSend);
}
 /* sendString
		-send several chars(string) function 
		- dataToSend: sting to send
*/
void sendString(const char* dataToSend, USART_TypeDef *usartx)
{
 while (*dataToSend)
 sendChar(*dataToSend++, usartx);
}
/* uartReceive
	function to read from RX line.
	- usartx: usart number UASRT2 or USART1.
*/
char uartReceive(USART_TypeDef *usartx)
{
	char received;
	if (USART_GetFlagStatus(usartx, USART_FLAG_RXNE)) 
		{
			received = USART_ReceiveData(usartx);
		}
	else
		{
		received = ' ';
		}
 return received;
}
/*
	__io_putchar
	default c function to prevent writing everything in one line in terminal.
*/
int __io_putchar(int received)
{
	if (received=='\n')
		sendChar('\r',USART1);
	sendChar(received,USART1);
	return received;
}
