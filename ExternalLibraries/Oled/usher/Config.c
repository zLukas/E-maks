/**
  ******************************************************************************
  * @file    xxx.c 
  * @author  Waveshare Team
  * @version 
  * @date    xx-xx-2014
  * @brief   xxxxx.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "LIB_Config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void port_init(void);

#ifdef INTERFACE_4WIRE_SPI
static void spi2_init(void);
#endif
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  System initialization.
  * @param  None
  * @retval  None
  */
void system_init(void)
{
	RCC_ClocksTypeDef tRCC;
	
	RCC_GetClocksFreq(&tRCC); 
	delay_init(tRCC.HCLK_Frequency);
	
		port_init();
    iic_init();
    ssd1306_init();
	
}

static void port_init(void) 
{
	GPIO_InitTypeDef tGPIO;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE); 

	
	//SSD1306 OLED
	tGPIO.GPIO_Pin = SSD1306_CS_PIN;     // CS				 
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	tGPIO.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(BLK_PORT, &tGPIO);
	
	tGPIO.GPIO_Pin = SSD1306_RES_PIN | SSD1306_DC_PIN;     // RES D/C 				 
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	tGPIO.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(OLED_RES_PORT, &tGPIO);
	
	
	/*----------------------------------------------------------------------------------*/
	//I2C
#ifdef INTERFACE_IIC
	tGPIO.GPIO_Pin = IIC_SCL_PIN | IIC_SDA_PIN;
	tGPIO.GPIO_Mode = GPIO_Mode_Out_PP; //GPIO_Mode_Out_PP
	tGPIO.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(I2C1_PORT, &tGPIO);
#endif
	/*----------------------------------------------------------------------------------*/
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	;
}

/*-------------------------------END OF FILE-------------------------------*/
