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


#define DIO0						GPIO_Pin_0		//IO not connected
#define DIO0_PORT				GPIOA					//IO not connected

#define TEST_LED				GPIO_Pin_12	
#define TEST_LED_PORT		GPIOC

#define	DIO1						GPIO_Pin_3	//out	not connected
#define DIO2						GPIO_Pin_2	//out not connected
#define DIO3						GPIO_Pin_1	//out not connected
#define DIO4						GPIO_Pin_0	//out not connected
#define DIO14_PORT			GPIOC

#define DIO5						GPIO_Pin_5	//in out not connected 
#define DIO5_PORT				GPIOB

#define	RFM_CS					GPIO_Pin_6		// spi CS
#define RFM_CS_PORT			GPIOC

#define	NRF_CS					GPIO_Pin_7		//  spi CS  NRF42L01
#define NRF_IRQ					GPIO_Pin_8		//	interrupt line "in"
#define NRF_CE					GPIO_Pin_9		//	spi Chip enable 
#define NRF_PORT				GPIOC					//	not connected


#define	SCREEN_RES			GPIO_Pin_11			//out		reset  high pullup 
#define SCREEN_RES_PORT	GPIOA

#define	UART1_TX				GPIO_Pin_9			//af_PP
#define	UART1_RX				GPIO_Pin_10			//floating
#define UART1_PORT			GPIOA

#define	UART2_TX				GPIO_Pin_2			//af_pp
#define	UART2_RX				GPIO_Pin_3			//floating
#define	UART2_PORT			GPIOA

#define JOY1_X					GPIO_Pin_4			//adc
#define	JOY1_Y					GPIO_Pin_5			//adc
#define	JOY2_X					GPIO_Pin_6			//adc
#define	JOY2_Y					GPIO_Pin_7			//adc
#define	JOYS_PORT				GPIOA

#define VBAT						GPIO_Pin_4			//adc
#define	VBAT_PORT				GPIOC

#define	BUTTON1					GPIO_Pin_5			// in 
#define BUTTON1_PORT		GPIOC

#define	BUTTON2					GPIO_Pin_0		//in
#define BUTTON3					GPIO_Pin_1		//in
#define BUTTON4					GPIO_Pin_2		//in
#define BUTTON5					GPIO_Pin_10		//in
#define BUTTON6					GPIO_Pin_11		//in
#define BUTTON2_6_PORT	GPIOB

#define	BLK							GPIO_Pin_12  // gpio out HiGH
#define	BLK_PORT				GPIOB

/* cale I2C ( piny, funkcje) zainicjowane w bibliotece wyswietlacza OLED w plikach:
- LIB_Config.h
- IIC.c

w pliku LIB_COnfig podmieniono tylko piny
*/
#define I2C1_SCL					GPIO_Pin_6	//AF_OD;
#define	I2C1_SDA					GPIO_Pin_7	//AF_OD;
#define I2C1_PORT					GPIOB

#define	OLED_DC							GPIO_Pin_12		//in komendy/data wyslwietlacza
#define	OLED_DC_PORT				GPIOA
#define	OLED_RES						GPIO_Pin_11			//out		reset  high pullup 
#define OLED_RES_PORT				GPIOA


#define RFM_RES					GPIO_Pin_1		//out pwm? podswietlenie
#define	RFM_RES_PORT		GPIOA

#define	SPI2_SCK				GPIO_Pin_13	 //AF-PP
#define	SPI2_MISO				GPIO_Pin_14	 //floating
#define	SPI2_MOSI				GPIO_Pin_15	 //AF_pp
#define SPI2_PORT				GPIOB


void gpioInit(void);
void dmaInit(void);
void tim4Init(void);
void nvicInit (void);
void delayMs(volatile int time);

#endif
