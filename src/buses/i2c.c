#include "i2c.h"
#include "LIB_Config.h"

/*
	additional universal i2c functions just in case
*/



I2C_InitTypeDef i2c;

/* i2cInit
	-i2C bus Initialization 
	additional universal i2c functions just in case
*/
void i2cInit(void)
{	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	
	I2C_StructInit(&i2c);
	i2c.I2C_Mode = I2C_Mode_I2C;
	i2c.I2C_ClockSpeed = 100000;
	I2C_Init(I2C1, &i2c);
	I2C_Cmd(I2C1, ENABLE);
} 





/*
	oledWriteLine.
	based on Waveshare oled Library, function used are in file 'SSD1306.c
*/

void oledWriteLine(uint8_t *textToWrite,uint8_t line )
{
		
		if(line == 1)
		{
			ssd1306_display_string(2, 0, textToWrite, 14, 1);
		}
		else if(line == 2)
		{
			ssd1306_display_string(2, 16, textToWrite, 14, 1);
		}
		else if (line == 3)
		{
			ssd1306_display_string(2, 32, textToWrite, 14, 1);
		}		
		else if (line == 4)
		{
			ssd1306_display_string(2, 48, textToWrite, 14, 1);
		}
		ssd1306_refresh_gram();
}

void oledShowParameters(uint16_t *kartBattery, uint16_t *kartSpeed, uint816_t *wheels, uint16_t *rcBattery)
{
	char ks = "v kart: " && kartSpeed;
	char kb = "bat.kart: "&& kartBattery;
	char wh = "kola: "&& wheels;
	char rb	= "bar. RC: "&& rcBattery;
	
	
	
	ssd1306_clear_screen(0xFF);
	delay_ms(100);
	ssd1306_clear_screen(0x00);
	/*
	ssd1306_display_string(Xpos, Ypos, string , definiuje czcionke 12 mala 16 duza, nie wiem co robi )
	*/
	ssd1306_display_string(2, 0, ks, 14, 1);
	ssd1306_display_string(2, 16, wh, 14, 1);
	ssd1306_display_string(2, 32, kb, 14, 1);
	ssd1306_display_string(2, 32, rb, 14, 1);
	ssd1306_refresh_gram();
	

}