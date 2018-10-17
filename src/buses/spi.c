#include "spi.h"

SPI_InitTypeDef spi;

/* spiInit
	-spi bus initialization
*/
void spiInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	SPI_StructInit(&spi);
	spi.SPI_Mode = SPI_Mode_Master;
	spi.SPI_NSS = SPI_NSS_Soft;
	spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_Init(SPI2, &spi);
 
	SPI_Cmd(SPI1, ENABLE);
}

/* spisendReceive
	-sending then receiving function
*/
uint8_t spiSendReceive(uint8_t byte)
{
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
 SPI_I2S_SendData(SPI2, byte);
 
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
 return SPI_I2S_ReceiveData(SPI1);
}
