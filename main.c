
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

#include "switch.h"
#include "led.h"

void main()
{
	EnableSwitch(SW_ALL);
	EnableLED(LED_ALL);

	while (1) // Main loop
	{
		if (IsPressed(SW_Left))        { TurnOn(LED_3);         _delay_ms(300); }
		else if (IsPressed(SW_Down))   { TurnOn(LED_2);         _delay_ms(300); }
		else if (IsPressed(SW_Right))  { TurnOn(LED_2 | LED_3); _delay_ms(300); }
		else if (IsPressed(SW_Up))     { TurnOn(LED_1);         _delay_ms(300); }
		else if (IsPressed(SW_Center)) { TurnOn(LED_1 | LED_3); _delay_ms(300); }
		else TurnOff(LED_ALL);
	}
}
