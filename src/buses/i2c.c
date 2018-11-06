#include "i2c.h"
#include "LIB_Config.h"

/*
	additional universal i2c functions just in case
*/



/*
	oled variables
*/

char kartSpeed[20];
char kartBattery[20];
char wheelsAngle[20];
char rcBattery[20];

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
	funkcja wyswietlajaca bazujaca na bibliotece OLED
	na bazie funcji oledSample z oledMain.c
	
*/
void oledShowParameters(float kartBatt, float kartSpd, float wheels, float rcBatt)
{
	/*
		sprintf(tablica char, "jakis statyczny text i %f %d", watorsc do wstawienia pod %f, wartosc do wstawienia pod d)
	*/
	sprintf(kartSpeed, "v kart: %.1f km/h",kartSpd);
	sprintf(kartBattery, "bat.kart: %.1f %%", kartBatt);
	sprintf(wheelsAngle, "skret kol: %.1f *",wheels);
	sprintf(rcBattery, "bat.RC: %.1f %%",rcBatt);
	/*
	ssd1306_display_string(Xpos,Ypos, wskaznik(uint8_t) na tablice char do wyswietlenia, Font?, nie wiem co to robi ale jak wstawi sie 0 to nie dziala);
	*/	
	ssd1306_display_string(2, 0, (uint8_t *)kartSpeed , 14, 1);
	ssd1306_display_string(2, 16,(uint8_t *)kartBattery , 14, 1);
	ssd1306_display_string(2, 32,(uint8_t *)wheelsAngle  , 14, 1);
	ssd1306_display_string(2, 48,(uint8_t *)rcBattery , 14, 1);
	ssd1306_refresh_gram();
}

void oledTest(void)
{				
		oledShowParameters(50,60,10,67);		
		oledShowParameters(40,55,20,65);
		oledShowParameters(30,67,15,60);
		oledShowParameters(20,59,20,48);
}
