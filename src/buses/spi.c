/*
	spi.c
	SPI configuration files.
*/

#include "spi.h"

/*
	spi init structure
*/
SPI_InitTypeDef spi;

/* spiInit
	-spi bus configuraion
*/
void spiInit(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi.SPI_Mode = SPI_Mode_Master;
	spi.SPI_DataSize = SPI_DataSize_8b;
	spi.SPI_CPOL = SPI_CPOL_Low;
	spi.SPI_CPHA = SPI_CPHA_1Edge;
	spi.SPI_NSS = SPI_NSS_Soft;
	spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	spi.SPI_FirstBit = SPI_FirstBit_MSB;
	spi.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2,&spi);
 
	SPI_Cmd(SPI2, ENABLE);
	SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Rx,ENABLE);
	SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Tx,ENABLE);
}

/* spisendReceive
	-sending and receiving function. 
*/

/*
void spi2Wait(void)
{
	while((SPI2->SR & SPI_I2S_FLAG_TXE) == (uint16_t)SET || (SPI2->SR & SPI_I2S_FLAG_RXNE) == (uint16_t)SET);
}
*/
uint8_t spiSendReceive(uint8_t byte)
{	
/*
	wait for free buffer
 while(SPI2->SR & SPI_I2S_FLAG_TXE == (uint16_t)SET || SPI2->SR & SPI_I2S_FLAG_RXNE == (uint16_t)SET);
	
	
*/
	
 while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	
 SPI_I2S_SendData(SPI2, byte);
 
 while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
 return SPI_I2S_ReceiveData(SPI2);
}




// todo: move it to another module
/* nrf24_ce_digitalWrite.
	 externall library function 
	 set chip enable state 
	 -state: 0 or 1 value
*/
void spi_write_nrf24_ce(uint8_t state)
{
    if(state)
    {
        GPIO_SetBits(NRF_PORT, NRF_CE);
    }
    else
    {
        GPIO_ResetBits(NRF_PORT, NRF_CE);
    }
}
/* nrf24_csn_digitalWrite
	 externall library function 
	 set chip enable state
	 -state: 0 or 1 value
*/
void spi_write_nrf24_csn(uint8_t state)
{
    if(state)
    {
        GPIO_SetBits(NRF_PORT, NRF_CS);
    }
    else
    {
        GPIO_ResetBits(NRF_PORT, NRF_CS);
    }
}
