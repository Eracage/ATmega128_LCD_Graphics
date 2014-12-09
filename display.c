#include "display.h"

#include "lcd.h"

#define F_CPU 8000000UL // 8Mhz
#include <util/delay.h>

byte m_display[HEIGHT/GROUPSIZE][WIDTH][2];

char PreviousX;

void Display_Init()
{
	lcd_init();						//Näytön alustus
	
	byte x, y;
	for(y = 0;y < (HEIGHT/GROUPSIZE); ++y)
	{
		lcd_send(0xB0|y, LCD_CMD);	// page 0
		lcd_send(0x10, LCD_CMD);	// X MSB 0
		lcd_send(0x04, LCD_CMD);	// X LSB 4 Because apparently starts from 4


		for(x = 0; x < 128; ++x)
		{
			lcd_send(0x00, LCD_DATA); // Set Data in Page to 0, move 1
			m_display[y][x][0] = m_display[y][x][1] = 0;
		}
	}
}
// updates lcd display only where there are changes in the pixel buffer
void Display_Update()
{
	byte x, y, prevX, prevY;
	prevX = prevY = -1;

	for (y = 0; y < (HEIGHT/GROUPSIZE); ++y)
	{
		for (x = 0; x < WIDTH; ++x)
		{
			if (m_display[y][x][0] != m_display[y][x][1])
			{
				if (prevY != y)
				{
					lcd_send(0xB0|y, LCD_CMD);
					prevY = y;
				}
				if (prevX != x-1)
				{
					lcd_send(0x10 | (((x + 4) & 0xF0) >> 4), LCD_CMD);
					lcd_send(0x00 | ((x + 4) & 0x0F), LCD_CMD);
					prevX = x;
				}

				lcd_send(m_display[y][x][0] = m_display[y][x][1], LCD_DATA); // Set Data in Page to 0, move 1
			}
		}	
	}

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

	//PreviousX = 0;
	//PreviousX2= 0;
	//PreviousY = 0;
	//
	//lcd_send(0xB0, LCD_CMD);
	//lcd_send(0x10, LCD_CMD);
	//lcd_send(0x04, LCD_CMD);

	//// updates from left to right, 
	//for (byte y = 0; y < (HEIGHT/GROUPSIZE); ++y)
	//{
	//	for (byte x = 4; x < WIDTH-4; ++x)
	//	{
	//		// if the contents of the page (8 pixels) has changed, update the page on lcd display
	//		if (m_display[y][x][0] != m_display[y][x][1])
	//		{
	//			/*if (PreviousY != y)
	//			{*/
	//				lcd_send(0xB0 | y, LCD_CMD);
	//			/*}
	//			if (PreviousX2 != (x/64))
	//			{*/
	//				lcd_send(0x10 | (x/64), LCD_CMD);
	//			/*}
	//			if (PreviousX != (x%64))
	//			{*/
	//				lcd_send(0x04 | (x%64), LCD_CMD);
	//			//}
	//			
	//			lcd_send(m_display[y][x][0] = m_display[y][x][1], LCD_DATA);

	//			PreviousX = (x+1);
	//			PreviousX2 = (x/64);
	//			PreviousY = y;
	//		}
	//	}
	//}
}

void Display_Pixel(byte x, byte y, byte on)
{
	if (on)
		m_display[y / GROUPSIZE][x][1] |=   1 << y % GROUPSIZE; 
	else
		m_display[y / GROUPSIZE][x][1] &= ~(1 << y % GROUPSIZE);
}

void Dixplay_InverseColors(byte on)
{
	// TODO: Redo this function, by using the LCD's own inverse functionality.

	byte x, y;
	
	for (y = 0; y < (HEIGHT/GROUPSIZE); ++y)
		for (x = 0; x < WIDTH; ++x)
			m_display[y][x][1] = ~m_display[y][x][1];
}

void Display_Clear()
{
	byte x, y;
	
	for (y = 0; y < (HEIGHT/GROUPSIZE); ++y)
		for (x = 0; x < WIDTH; ++x)
			m_display[y][x][1] = 0;
}
