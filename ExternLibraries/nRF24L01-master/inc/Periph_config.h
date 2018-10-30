/*
 * Periph_config.h
 *
 *  Created on: 28 lut 2018
 *      Author: uzytkownik
 */

#ifndef PERIPH_CONFIG_H_
#define PERIPH_CONFIG_H_

#include "Library_includes.h"

DMA_InitTypeDef dmarx;
DMA_InitTypeDef dmatx;

void RCC_config();
void GPIO_config();
void SPI_config();
void USART_config();
void SysTick_config();
void NVIC_config();
void EXTI_config();
void DMA_config();
void TIM_config();

#endif /* PERIPH_CONFIG_H_ */
