#include "oled.h"

void write_oled_line(float* data_to_show,char* text_to_show, oled_lines line)
{
	uint8_t text_size = 0;
	
	while(text_to_show[text_size] != NULL)
	{
		text_size++;
	}
	
	if( text_size < OLED_SCREEN_WIDTH)
	{
	
	char string_to_show[OLED_SCREEN_WIDTH];	
	sprintf(string_to_show,text_to_show,(*data_to_show));
	ssd1306_display_string(2, line, (uint8_t *)string_to_show , 14, 1);
	}

}


void oled_show_params(float* data){
	char kartSpeed[20];
	char kartBattery[20];
	char wheelsAngle[20];
	char rcBattery[20];
	
	/*
		sprintf( char array, "sample text i %f %d", value to replace %f, walu to replace %d)
	*/
	sprintf(kartSpeed, "v kart: %.1f km/h",data[0]);
	sprintf(kartBattery, "bat.kart: %.1f %%", data[1]);
	sprintf(wheelsAngle, "skret kol: %.1f *",data[2]);
	sprintf(rcBattery, "bat.RC: %.1f %%",data[3]);
/*
	ssd1306_display_string(Xpos,Ypos, (uint8_t)pointer on char wtih data to show, Font?, dont't know what does this argument but wit "0" not working);
*/		
	ssd1306_display_string(2, 0, (uint8_t *)kartSpeed , 14, 1);
	ssd1306_display_string(2, 16,(uint8_t *)kartBattery , 14, 1);
	ssd1306_display_string(2, 32,(uint8_t *)wheelsAngle  , 14, 1);
	ssd1306_display_string(2, 48,(uint8_t *)rcBattery , 14, 1);
	ssd1306_refresh_gram();
	

}	
void oled_demo(void)
{
	oled_show_params((float[]){10,40,55.3,81.9});
	hardware_functions.delay_ms(500);
	
	oled_show_params((float[]){0,10,44.4,44});
	hardware_functions.delay_ms(500);
	
	oled_show_params((float[]){55.3,60,15.6,70});
	hardware_functions.delay_ms(500);
}
