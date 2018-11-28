/*
	i2c.c
	I2C configuration files. Not used in this project oled has it's own i2c protocol.
	Sample i2c functions. Written just in case.
*/

#include "i2c.h"

/*
	oled chars (strings) to schow on oled
*/

char kartSpeed[20];
char kartBattery[20];
char wheelsAngle[20];
char rcBattery[20];

/*
	 i2c init structure
*/
I2C_InitTypeDef i2c;

/* i2cInit
	-i2C bus Initialization 
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
	- make connection with other device
	- deviceAddress: addres of the device to connect
	- memoryAddress: address of device memeory we want co use 
*/
void i2cSetAddress(uint8_t deviceAddress, uint32_t memoryAddress )
{
	I2C_GenerateSTART(I2C1,ENABLE);
	 while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
 I2C_Send7bitAddress(I2C1, deviceAddress, I2C_Direction_Transmitter);
 while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
 
 I2C_SendData(I2C1, memoryAddress);
 while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
}

/*
	i2cWrite
	- function to send data via i2c
	- deviceAddress: addres of the device to connect
	- memoryAddress: address of device memeory we want co use  
	- dataSize: size of data to send 
*/
void i2cWrite(uint8_t deviceAddress,uint32_t memoryAddress, int dataSize)
{
	int i;
	const uint8_t* buffer ;
	i2cSetAddress(deviceAddress, memoryAddress);
	for (i = 0; i < dataSize; i++) 
	{
		I2C_SendData(I2C1, buffer[i]);
		while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
  }
	
	I2C_GenerateSTOP(I2C1, ENABLE);
}

/*
	i2cRead
	- function to receive data via i2c
	- deviceAddress: addres of the device to connect
	- memoryAddress: address of device memeory we want co use  
	- dataSize: size of received data 
*/
void i2cRead(uint8_t deviceAddress ,uint32_t memoryAddress, int dataSize)
{
	int i;
	uint8_t* buffer ;
	i2cSetAddress(deviceAddress,memoryAddress);
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
	oledShowParameters
	- show some data on oled screen. in this case electric cart parameters.
	- kartBatt: battery percent value.
	- kartspd: kart speed value.
	- wheels : angle of wheels turn.
	- rcBatt: Remote controller battery vlaue.
*/
void oledShowParameters(float kartBatt, float kartSpd, float wheels, float rcBatt)
{
/*
		sprintf( char array, "sample text i %f %d", value to replace %f, walu to replace %d)
*/
	sprintf(kartSpeed, "v kart: %.1f km/h",kartSpd);
	sprintf(kartBattery, "bat.kart: %.1f %%", kartBatt);
	sprintf(wheelsAngle, "skret kol: %.1f *",wheels);
	sprintf(rcBattery, "bat.RC: %.1f %%",rcBatt);
/*
	ssd1306_display_string(Xpos,Ypos, (uint8_t)pointer on char wtih data to show, Font?, dont't know what does this argument but wit "0" not working);
*/		
	ssd1306_display_string(2, 0, (uint8_t *)kartSpeed , 14, 1);
	ssd1306_display_string(2, 16,(uint8_t *)kartBattery , 14, 1);
	ssd1306_display_string(2, 32,(uint8_t *)wheelsAngle  , 14, 1);
	ssd1306_display_string(2, 48,(uint8_t *)rcBattery , 14, 1);
	ssd1306_refresh_gram();
}
/*
	oledTest
	oled test function. Show random parameters on oled  screen.
*/
void oledTest(void)
{				
		oledShowParameters(50,60,10,67);		
		oledShowParameters(40,55,20,65);
		oledShowParameters(30,67,15,60);
		oledShowParameters(20,59,20,48);
}
