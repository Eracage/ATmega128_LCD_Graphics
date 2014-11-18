#include "graphics.h"
#include "lcd.h"

void Graphics_init()
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
void Graphics_draw()
{
	// updates from left to right, 
	for (char x = 0; x < WIDTH; ++x)
	{
		for (char y = 0; y < HEIGHT/GROUPSIZE; ++y)
		{
			// if the contents of the page (8 pixels) has changed, update the page on lcd display
			if (m_display[x][y][0] != m_display[x][y][1])
			{
				Graphics_drawGroup(m_display[x][y][1]);

				m_display[x][y][0] = m_display[x][y][1];
			}
		}
	}
}

void Graphics_pixel(char x, char y, char on)
{
	if (on)
		m_display[x][y / GROUPSIZE][1] |=   1 << y % GROUPSIZE; 
	else
		m_display[x][y / GROUPSIZE][1] &= ~(1 << y % GROUPSIZE);
}

void Graphics_drawGroup(byte data)
{
	lcd_send(data, LCD_DATA);
}

void Graphics_inverseColors(char on_off)
{

}

