#ifndef _OLED_H_
#define _OLED_H_

#include "SSD1306.h" 
#include "application_layer.h"

#define OLED_SCREEN_WIDTH  20

typedef enum {
	oled_first_line 	= 0,
	oled_second_line	= 16,
	oled_third_line	  = 32,
	oled_fourth_line  = 48,
}oled_lines;

void write_oled_line(float* data_to_show,char* text_to_show, oled_lines line);
void oled_show_params(float* data);
void oled_demo(void);

#endif
