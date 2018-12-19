/**
 *  Defines for your entire project at one place
 * 
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@version 	v1.0
 *	@ide		Keil uVision 5
 *	@license	GNU GPL v3
 *	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#ifndef TM_DEFINES_H
#define TM_DEFINES_H

/*Put your global defines for all libraries here used in your project */


#endif

/**
void TM_SPI_SendMulti(SPI_TypeDef* SPIx, uint8_t* dataOut, uint8_t* dataIn, uint32_t count) {
	uint32_t i;
	
	 Check if SPI is enabled 
	SPI_CHECK_ENABLED(SPIx);
	
	Wait for previous transmissions to complete if DMA TX enabled for SPI 
	SPI_WAIT(SPIx);
	
	for (i = 0; i < count; i++) {
		 Fill output buffer with data 
		SPIx->DR = dataOut[i];
		
		 Wait for SPI to end everything 
		SPI_WAIT(SPIx);
		
		 Read data register 
		dataIn[i] = SPIx->DR;
	}
}

void TM_SPI_WriteMulti(SPI_TypeDef* SPIx, uint8_t* dataOut, uint32_t count) {
	uint32_t i;	
	
	 Check if SPI is enabled 
	SPI_CHECK_ENABLED(SPIx);
	
	 Wait for previous transmissions to complete if DMA TX enabled for SPI 
	SPI_WAIT(SPIx);
	
	for (i = 0; i < count; i++) {
		 Fill output buffer with data 
		SPIx->DR = dataOut[i];
		
		 Wait for SPI to end everything 
		SPI_WAIT(SPIx);
		
		 Read data register 
		(void)SPIx->DR;
	}
}

void TM_SPI_ReadMulti(SPI_TypeDef* SPIx, uint8_t* dataIn, uint8_t dummy, uint32_t count) {
	uint32_t i;
	
	 Check if SPI is enabled 
	SPI_CHECK_ENABLED(SPIx);
	
	 Wait for previous transmissions to complete if DMA TX enabled for SPI 
	SPI_WAIT(SPIx);
	
	for (i = 0; i < count; i++) {
		 Fill output buffer with data 
		SPIx->DR = dummy;
		
		 Wait for SPI to end everything 
		SPI_WAIT(SPIx);
		
		 Save data to buffer 
		dataIn[i] = SPIx->DR;
	}
}

void TM_SPI_SendMulti16(SPI_TypeDef* SPIx, uint16_t* dataOut, uint16_t* dataIn, uint32_t count) {
	uint32_t i;	
	
	 Check if SPI is enabled 
	SPI_CHECK_ENABLED(SPIx);
	
	 Wait for previous transmissions to complete if DMA TX enabled for SPI 
	SPI_WAIT(SPIx);
	
	for (i = 0; i < count; i++) {
		 Fill output buffer with data 
		SPIx->DR = dataOut[i];
		
		 Wait for SPI to end everything 
		SPI_WAIT(SPIx);
		
		 Read data register 
		dataIn[i] = SPIx->DR;
	}
}

void TM_SPI_WriteMulti16(SPI_TypeDef* SPIx, uint16_t* dataOut, uint32_t count) {
	uint32_t i;
	
	 Check if SPI is enabled 
	SPI_CHECK_ENABLED(SPIx);
	
	 Wait for previous transmissions to complete if DMA TX enabled for SPI 
	SPI_WAIT(SPIx);
	
	for (i = 0; i < count; i++) {
		 Fill output buffer with data 
		SPIx->DR = dataOut[i];
		
		 Wait for SPI to end everything 
		SPI_WAIT(SPIx);
		
		 Read data register 
		(void)SPIx->DR;
	}
}

void TM_SPI_ReadMulti16(SPI_TypeDef* SPIx, uint16_t* dataIn, uint16_t dummy, uint32_t count) {
	uint32_t i;
	
	 Check if SPI is enabled 
	SPI_CHECK_ENABLED(SPIx);
	
	 Wait for previous transmissions to complete if DMA TX enabled for SPI 
	SPI_WAIT(SPIx);
	
	for (i = 0; i < count; i++) {
		 Fill output buffer with data 
		SPIx->DR = dummy;
		
		 Wait for SPI to end everything 
		SPI_WAIT(SPIx);
		
		 Save data to buffer 
		dataIn[i] = SPIx->DR;
	}
}
*/
