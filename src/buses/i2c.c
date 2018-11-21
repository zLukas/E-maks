#include "i2c.h"
#include "LIB_Config.h"

/*
	additional universal i2c functions just in case
*/
extern void* i2cData;


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
	
	I2C_DMACmd(I2C1,ENABLE);
} 

/*
	i2cSetAddress
	-connect to device and send memeory address to send data
*/
void i2cSetAddress(uint32_t memoryAddress)
{
	I2C_GenerateSTART(I2C1,ENABLE);
	 while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
 I2C_Send7bitAddress(I2C1, OLED_DEVICE_ADDRESS, I2C_Direction_Transmitter);
 while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
 
 I2C_SendData(I2C1, memoryAddress);
 while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
}

void i2cWrite(uint32_t memoryAddress, int dataSize)
{
	int i;
	const uint8_t* buffer = (uint8_t*)i2cData;
	i2cSetAddress(memoryAddress);
	for (i = 0; i < dataSize; i++) 
	{
		I2C_SendData(I2C1, buffer[i]);
		while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
  }
	
	I2C_GenerateSTOP(I2C1, ENABLE);
}


void i2cRead(uint32_t memoryAddress, int dataSize)
{
	int i;
	uint8_t* buffer = (uint8_t*)i2cData;
	i2cSetAddress(memoryAddress);
	 while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
 
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	I2C_Send7bitAddress(I2C1, OLED_DEVICE_ADDRESS, I2C_Direction_Receiver);
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);
 
	for (i = 0; i < dataSize - 1; i++) 
	{
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
     buffer[i] = I2C_ReceiveData(I2C1);
  }
 I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);
    while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
    buffer[i] = I2C_ReceiveData(I2C1);
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
