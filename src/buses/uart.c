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
	-USART2 configuration 
*/
void uartInit(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_StructInit(&uart);
	uart.USART_BaudRate = 115200;
	USART_Init(USART2, &uart);
	USART_Cmd(USART2, ENABLE);
}

/* sendChar
	 one char sending.
	- charToSend : char to send
*/
void sendChar(char charToSend)
{
 while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
 USART_SendData(USART2, charToSend);
}
 /* sendString
		-send several chars(string) function 
		- dataToSend: sting to send
*/
void sendString(const char* dataToSend)
{
 while (*dataToSend)
 sendChar(*dataToSend++);
}
/* uartReceive
	function to read from RX line.
	- USART2: usart number UASRT2 or USART1.
*/
//todo: creplace it with interruption
char uartReceive(void)
{
	char received;
	if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE)) 
		{
			received = USART_ReceiveData(USART2);
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
		sendChar('\r');
	sendChar(received);
	return received;
}
