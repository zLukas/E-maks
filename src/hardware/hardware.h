#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_adc.h>
#include <stm32f10x_exti.h>
#include <stm32f10x_dma.h> 
#include <stm32f10x_usart.h>
#include <stm32f10x_can.h>
#include <stm32f10x_i2c.h>




#define DIO0						GPIO_Pin_0
#define DIO0_PORT				GPIO

#define	DC							GPIO_Pin_12
#define	DC_PORT				GPIO_A

#define RFM_RES					GPIO_Pin_1
#define	RFM_RES_PORT		GPIOA

#define	RFM_CS					GPIO_Pin_6
#define RFM_CS_PORT			GPIOC

#define	SCREEN RES			GPIO_Pin_11
#define SCREEN_RES_PORT	GPIOA

#define	UART2_TX				GPIO_Pin_2
#define	UART2_RX				GPIO_Pin_3
#define	UART2_PORT			GPIOA

#define JOY1_X					GPIO_Pin_4			
#define	JOY1_Y					GPIO_Pin_5
#define	JOY2_X					GPIO_Pin_6
#define	JOY2_Y					GPIO_Pin_7
#define	JOYX_PORT				GPIOA

#define	UART1_TX				GPIO_Pin_9
#define	UART1_RX				GPIO_Pin_10
#define UART1_PORT			GPIO_A

#define	OSC_IN					GPIO_Pin_0
#define	OSC_OUT					GPIO_Pin1
#define OSC_PORT				GPIOD

#define	BUTTON1					GPIO_Pin_5
#define BUTTON1_PORT		GPIOC

#define	BUTTON2					GPIO_Pin_0
#define BUTTON3					GPIO_Pin_1
#define BUTTON4					GPIO_Pin_2
#define BUTTON5					GPIO_Pin_10
#define BUTTON6					GPIO_Pin_11
#define BUTTON2_6_PORT	GPIOB

#define DIO5						GPIO_Pin_5
#define DIO5_PORT				GPIOB

#define	DIO1						GPIO_Pin_3
#define DIO2						GPIO_Pin_2
#define DIO3						GPIO_Pin_1
#define DIO4						GPIO_Pin_0
#define DIO1_4_PORT			GPIOC

#define I2C_SCL					GPIO_Pin_6
#define	I2C_SDA					GPIO_Pin_7
#define I2C_PORT				GPIO_B

#define	BLK							GPIO_Pin_12
#define	BLK_PORT				GPIOB

#define	SPI2_SCK				GPIO_Pin_13	
#define	SPI2_MISO				GPIO_Pin_14
#define	SPI2_MOSI				GPIO_Pin_15
#define SPI2_PORT				GPIOB

#define VBAT						GPIO_Pin_4
#define	VBAT_PORT				GPIOC

#define	NRF_CS					GPIO_Pin_7
#define NRF_IRQ					GPIO_Pin_8
#define NRF_CE					GPIO_Pin_9
#define NRF_PORT				GPIOC


void rccInit(void);
void gpioInit(void);

#endif
