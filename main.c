/********************************************************

Kajaani Amk
Esko Haila
Aleksi Jokihaara
Mika Muhonen

Muokattu:
28.10.2014

N‰yttˆ:
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

#define F_CPU 1000000UL

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "display.h"
#include "analog.h"


int x, y;

//M‰‰ritell‰‰n kytkimet 1-5
#define Switch PIND
#define SW1 PD0		// Painettaessa 0-tilassa
#define SW2 PD1
#define SW3 PD2
#define SW4 PD3
#define SW5 PD4

int debug;



//typedef char bool;

/********************************
main 

*******************************/
int main(void)
{

	//Kytkimet sis‰‰ntuloja
	DDRD &= ~((1<<SW1) | (1<<SW2) | (1<<SW3) | (1<<SW4) | (1<<SW5));
	debug = 1;

	Analog_Init();
	Display_Init();

//Osoittimen aloituspiste
	x=1;							
	y=0;

	while(1)
	{
		if ((~Switch & (1<<SW5)) != 0)
		{
			debug = 1-debug;
			_delay_ms(30);
		}


	}



}



