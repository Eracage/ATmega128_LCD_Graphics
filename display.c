#include "display.h"

// TODO: remove lcd.h
#include "lcd.h"

#ifndef F_CPU
#define F_CPU 8000000UL // 8Mhz
#endif
#include <util/delay.h>

byte m_display[HEIGHT/GROUPSIZE][WIDTH][2];

// TODO: remove m_inverse when inverse has been correctly implemented
byte m_inverse;

// TODO: Make own function with lcd_send functionality preferably with optimization

void Display_Init()
{
	// TODO: Copy from lcd.cpp and optimize
	lcd_init();						//Initiate the LCD
	
	// Make sure display starts cleared
	byte x, y;
	for(y = 0;y < (HEIGHT/GROUPSIZE); ++y)
	{
		lcd_send(0xB0|y, LCD_CMD);	// page 0
		lcd_send(0x10, LCD_CMD);	// X MSB 0
		lcd_send(0x04, LCD_CMD);	// X LSB 4 Because apparently first pixel is in index 4


		for(x = 0; x < 128; ++x)
		{
			lcd_send(0x00, LCD_DATA);  // Set Data in Page to 0, automatically moves 1 to the right
			m_display[y][x][0] = m_display[y][x][1] = 0; // initialize display buffers
		}
	}

	m_inverse = 0;
}

void Display_Update()
{
	// Probably working version of buffer update, more optimized

	byte x, y, prevX, prevY;
	prevX = prevY = -1;

	// Update from up to down
	for (y = 0; y < (HEIGHT/GROUPSIZE); ++y)
	{
		// Update from left to right
		for (x = 0; x < WIDTH; ++x)
		{
			// If the contents of the page (8 pixels) has changed, update the page on LCD display
			if (m_display[y][x][0] != m_display[y][x][1])
			{
				if (prevY != y) // If page has changed
				{
					lcd_send(0xB0|y, LCD_CMD); // change page on LCD display
					prevY = y;
				}
				if (prevX != x-1) // If x has changed more than the 1 it moves automatically
				{
					if (((prevX + 4) & 0xF0) == ((x + 4) & 0xF0))
						lcd_send(0x10 | (((x + 4) & 0xF0) >> 4), LCD_CMD); // Change x MSB on LCD display
					lcd_send(0x00 | ((x + 4) & 0x0F), LCD_CMD); // Change x LSB on LCD display
				}
				prevX = x;

				lcd_send(m_display[y][x][0] = m_display[y][x][1], LCD_DATA); // Change Data in Page, automatically moves 1 to the right
			}
		}
	}



	// More working version of buffer update, less optimized

	//byte x, y, prevX;

	//for (y = 0; y < (HEIGHT/GROUPSIZE); ++y)
	//{
	//	lcd_send(0xB0|y, LCD_CMD);	// page 0

	//	for (x = 0; x < WIDTH; ++x)
	//	{
	//		if (m_display[y][x][0] != m_display[y][x][1])
	//		{
	//			if (prevX != x-1)
	//			{
	//				lcd_send(0x10 | (((x + 4) & 0xF0) >> 4), LCD_CMD);
	//				lcd_send(0x00 | ((x + 4) & 0x0F), LCD_CMD);
	//			}
	//			prevX = x;
	//			lcd_send(m_display[y][x][0] = m_display[y][x][1], LCD_DATA); // Set Data in Page to 0, move 1
	//		}
	//	}
	//}
}

void Display_Pixel(byte x, byte y, byte on)
{
	// TODO: remove m_inverse when inverse has been correctly implemented
	on = m_inverse ? !on : on;

	if (on)
		m_display[y / GROUPSIZE][x][1] |=   1 << y % GROUPSIZE; 
	else
		m_display[y / GROUPSIZE][x][1] &= ~(1 << y % GROUPSIZE);
}

void Dixplay_InverseColors(byte on)
{
	// TODO: Redo this function, by using the LCD's own inverse functionality.
	if (m_inverse != on)
	{
		m_inverse = on;

		byte x, y;

		for (y = 0; y < (HEIGHT / GROUPSIZE); ++y)
			for (x = 0; x < WIDTH; ++x)
				m_display[y][x][1] = ~m_display[y][x][1];
	}

	//Possibly working implementation
	//byte data = 0xA6 + (on != 1);
	//lcd_send(data, LCD_CMD);
}

void Display_Clear()
{
	byte x, y;
	
	for (y = 0; y < (HEIGHT/GROUPSIZE); ++y)
		for (x = 0; x < WIDTH; ++x)
			m_display[y][x][1] = m_inverse; // Sets every byte in buffer to 0 (1 if inversed)
}
