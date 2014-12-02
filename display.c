#include "display.h"

#include "lcd.h"

byte m_display[HEIGHT/GROUPSIZE][WIDTH][2];

void Display_Init()
{
	lcd_init();						//Näytön alustus

	lcd_clear();

	for (byte y = 0; y < HEIGHT/GROUPSIZE; ++y)
	{
		for (byte x = 0; x < WIDTH; ++x)
		{
			m_display[y][x][0] = 1;
		}
	}

	Display_Clear();
}
// updates lcd display only where there are changes in the pixel buffer
void Display_Update()
{
	// updates from left to right, 
	for (byte x = 0; x < WIDTH; ++x)
	{
		for (byte y = 0; y < HEIGHT/GROUPSIZE; ++y)
		{
			// if the contents of the page (8 pixels) has changed, update the page on lcd display
			if (m_display[x][y][0] != m_display[x][y][1])
			{
				Display_DrawGroup(m_display[x][y][1]);

				m_display[x][y][0] = m_display[x][y][1];
			}
		}
	}
}

void Display_Pixel(byte x, byte y, byte on)
{
	if (on)
		m_display[x][y / GROUPSIZE][1] |=   1 << y % GROUPSIZE; 
	else
		m_display[x][y / GROUPSIZE][1] &= ~(1 << y % GROUPSIZE);
}

void Display_DrawGroup(byte data)
{
	lcd_send(data, LCD_DATA);
}

void Dixplay_InverseColors(byte on)
{

}

void Display_Clear()
{
	int x,y;

	for(y=0;y<8;y++){
		lcd_send(0xB0|y, LCD_CMD);	// page j
		lcd_send(0x10, LCD_CMD);
		lcd_send(0x00, LCD_CMD);	// column 0


		for(x=0;x<128;x++){
			lcd_send(0x00, LCD_DATA);
			m_display[y][x][1] = 0;
		}
	}

	lcd_send(0xB0, LCD_CMD);	// page 0
	lcd_send(0x10, LCD_CMD);
	lcd_send(0x00, LCD_CMD);	// column 0
}