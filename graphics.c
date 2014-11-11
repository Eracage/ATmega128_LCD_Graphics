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

void Graphics_draw()
{
	for (char x = 0; x < WIDTH/GROUPSIZE; ++x)
	{
		for (char y = 0; y < HEIGHT; ++y)
		{
			const unsigned int p0 = m_display[y][x][0];
			const unsigned int p1 = m_display[y][x][1];
			const unsigned int p2 = p0^p1;
			if (p2)
			{


				for (char p = 0; p < GROUPSIZE; ++p)
				{
					if ((1<<p) & p2)
					{
						lcd_pixel(
							x*GROUPSIZE + p,
							y,
							m_display[y][x][1] & (1<<p));
					}
				}

				m_display[y][x][0] = m_display[y][x][1];
			}
		}
	}
}

void Graphics_pixel(char x, char y, char on)
{
	if (on)
		m_display[y / GROUPSIZE][x][1] |=   1 << y % GROUPSIZE; 
	else
		m_display[y / GROUPSIZE][x][1] &= ~(1 << y % GROUPSIZE);
}

void Graphics_drawGroup()
{}