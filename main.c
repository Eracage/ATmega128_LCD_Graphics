
/********************************************************

Kajaani Amk
Esko Haila
Aleksi Jokihaara
Mika Muhonen

Muokattu:
28.10.2014

Näyttö:
Batron

Joystick:
PC0: Reset
PC1: Sce
PC2: D / C
PC3: SDin (Data)
PC4: SCLK (Kello)

Alusta:
Opetukortti ATMEGA 128:: AVR-GCC
Fuse Bits:0xFF, 0xB9, 0xE4

**********************************************************/

// Kellotaajuuden määritelmä delay.h kirjastolle.
// Määriteltävä ennen delay.h kirjaston lisäystä
#define F_CPU 8000000UL // 8Mhz

#include <util/delay.h>
#include <avr/io.h>

#include "analog.h"
#include "switch.h"
#include "led.h"
#include "display.h"

void main()
{
	EnableSwitch(SW_ALL);
	EnableLED(LED_ALL);

	Analog_Init();
	Display_Init();

	for (int i = 0; i < 64; ++i)
		Display_Pixel(i,i,1);
	for (int i = 0; i < 20; ++i)
		for (int j = 0; j < 20; ++j)
			Display_Pixel(20+i,20+j,1);

	float x, y, speed = 1.4f;
	x = y = 0;

	while (1) // Main loop
	{
		if (IsPressed(SW_Left))        
		{ 
			TurnOn(LED_3);
		}
		else if (IsPressed(SW_Down))   
		{ 
			TurnOn(LED_2);
		}
		else if (IsPressed(SW_Right))  
		{ 
			TurnOn(LED_2 | LED_3);
		}
		else if (IsPressed(SW_Up))     
		{ 
			TurnOn(LED_1);
			Dixplay_InverseColors(0);
		}
		else if (IsPressed(SW_Center)) 
		{ 
			TurnOn(LED_1 | LED_3);
			Display_Clear();
		}
		else TurnOff(LED_ALL);

		Pointf anaali = Analog_GetPositionf();

		// CLEAR
		{
			for(int u = y - 2; u <= y + 2; u++)
				for(int v = x - 2; v <= x + 2; v++)
					Display_Pixel(v, u, 0);
		}
		
		// CLEAR

		if(anaali.x - 0.5f >= 0.15)
			TurnOn(LED_ALL);

		x += (anaali.x - 0.5) * speed;
		y += (anaali.y - 0.5) * speed;

		if      (x > 127 - 3) x = 127 - 3;
		else if (x <   0 + 3) x =   0 + 3;

		if      (y > 63 - 3) y = 63 - 3;
		else if (y <  0 + 3) y =  0 + 3;

		// RE-DRAW
		{
			for(int u = y - 2; u <= y + 2; u++)
				for(int v = x - 2; v <= x + 2; v++)
					Display_Pixel(v, u, 1);
		}
		// RE-DRAW

		//Display_Pixel(x,y,1);
		Display_Update();
	}
}
