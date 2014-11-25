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
			m_display[y][x][0] = 0;
			m_display[y][x][1] = 0;
		}
	}
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

void Graphics_InverseColors(byte on)
{

}
