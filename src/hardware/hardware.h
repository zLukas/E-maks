/*
	hardware.h 
	hardware configuration file. Contains pinout defines and functions references.
*/

#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_adc.h>
#include <stm32f10x_exti.h>
#include <stm32f10x_dma.h> 
#include <stm32f10x_usart.h>
#include <stm32f10x_can.h>
#include <stm32f10x_i2c.h>
#include <stm32f10x_tim.h>
#include <misc.h>

#include	"adc.h"
#include "spi.h"


#define DIO0						GPIO_Pin_0		
#define DIO0_PORT				GPIOA					

#define TEST_LED				GPIO_Pin_12	
#define TEST_LED_PORT		GPIOC

#define	DIO1						GPIO_Pin_3	
#define DIO2						GPIO_Pin_2	
#define DIO3						GPIO_Pin_1	
#define DIO4						GPIO_Pin_0	
#define DIO14_PORT			GPIOC

#define DIO5						GPIO_Pin_5	 
#define DIO5_PORT				GPIOB

#define	RFM_CS					GPIO_Pin_6		
#define RFM_CS_PORT			GPIOC

#define	NRF_CS					GPIO_Pin_7		
#define NRF_IRQ					GPIO_Pin_8
#define NRF_IRQ_SRC			GPIO_PinSource8
#define NRF_CE					GPIO_Pin_9		
#define NRF_PORT				GPIOC	
#define NRF_PORT_SRC 		GPIO_PortSourceGPIOC
#define NRF_EXTI_LINE		EXTI_Line8


#define	SCREEN_RES			GPIO_Pin_11			//out		reset  high pullup 
#define SCREEN_RES_PORT	GPIOA

#define	UART1_TX				GPIO_Pin_9			//pad , kontroler STM32
//#define	UART1_TX				GPIO_Pin_2			//nucleo RB
#define	UART1_RX				GPIO_Pin_10			//pad, kontroler STM32
//#define	UART1_RX				GPIO_Pin_3			//nucleo RB
#define UART1_PORT			GPIOA

#define	UART2_TX				GPIO_Pin_2			
#define	UART2_RX				GPIO_Pin_3			
#define	UART2_PORT			GPIOA

#define JOY1_X					GPIO_Pin_4			
#define	JOY1_Y					GPIO_Pin_5			
#define	JOY2_X					GPIO_Pin_6			
#define	JOY2_Y					GPIO_Pin_7			
#define	JOYS_PORT				GPIOA

#define VBAT						GPIO_Pin_4			
#define	VBAT_PORT				GPIOC

#define	BUTTON1					GPIO_Pin_5			
#define BUTTON1_PORT		GPIOC

#define	BUTTON2					GPIO_Pin_0		
#define BUTTON3					GPIO_Pin_1		
#define BUTTON4					GPIO_Pin_2		
#define BUTTON5					GPIO_Pin_10		
#define BUTTON6					GPIO_Pin_11		
#define BUTTON2_6_PORT	GPIOB

#define	BLK							GPIO_Pin_12  // gpio out HIGH
#define	BLK_PORT				GPIOB

/* cale I2C ( piny, funkcje) zainicjowane w bibliotece wyswietlacza OLED w plikach:
- LIB_Config.h
- IIC.c

w pliku LIB_COnfig podmieniono tylko piny
*/
#define I2C1_SCL					GPIO_Pin_6	//AF_OD;
#define	I2C1_SDA					GPIO_Pin_7	//AF_OD;
#define I2C1_PORT					GPIOB

#define	OLED_DC							GPIO_Pin_12		//in commands/data oled
#define	OLED_DC_PORT				GPIOA
#define	OLED_RES						GPIO_Pin_11			//out	reset  high pullup 
#define OLED_RES_PORT				GPIOA


#define RFM_RES					GPIO_Pin_1		//out (pwm) light saturation oled 
#define	RFM_RES_PORT		GPIOA

#define	SPI2_SCK				GPIO_Pin_13	 
#define	SPI2_MISO				GPIO_Pin_14	 
#define	SPI2_MOSI				GPIO_Pin_15	 
#define SPI2_PORT				GPIOB




void delayMs(volatile int time);
void hardwareInit(void);

#endif
