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

#include "lcd.h"

#include "graphics.h"
#include "joystick.h"


int x, y;

//M‰‰ritell‰‰n kytkimet 1-5
#define Switch PIND
#define SW1 PD0		// Painettaessa 0-tilassa
#define SW2 PD1
#define SW3 PD2
#define SW4 PD3
#define SW5 PD4

int joystick;
int debug;



//typedef char bool;

/********************************
	main 

	*******************************/
	int main(void)
{
	int i;


	//Kytkimet sis‰‰ntuloja
	DDRD &= ~((1<<SW1) | (1<<SW2) | (1<<SW3) | (1<<SW4) | (1<<SW5));
	debug = 1;
	joystick = 1;


	ADCSRA |= 1<<ADPS2; 			//Esijakaja 64 -> Taajuus sopivaksi AD-muuntimelle
	ADCSRA |= 1<<ADPS1;
	ADMUX |=1<<ADLAR;				// ADC result left adjusted
	ADMUX &=~(1<<REFS0);
	ADMUX &= ~(1<<REFS1);			//Avcc(+5v) muuntimen referenssij‰nnitteeksi
	ADCSRA |= 1<<ADIE;				//ADC Interrupt Enable
	ADCSRA |= 1<<ADEN;				//K‰ynnistet‰‰n AD-muunnin

	sei();							//Sallitaan keskeytykset

	lcd_init();						//N‰ytˆn alustus

	lcd_clear();					//N‰ytˆn tyhjennys

	x=1;							//Osoittimen aloituspiste
	y=0;

	lcd_goto_xy(x,y);
	lcd_chr(132);

	while(1)
	{
		if ((~Switch & (1<<SW5)) != 0)
		{
			debug = 1-debug;
			_delay_ms(30);
		}
		if (debug == 1)
			showDebug();

		if ((~Switch & (1<<SW3)) != 0)
		{
			joystick = 1-joystick;
			_delay_ms(30);
		}

		if (joystick)
		{
			readJoystick();
			moveCursor();
		}
	}



}

void showDebug()
{
	char buf[15];

	if (joystick)
	{
		sprintf(buf, "X=%.2f V", voltage);

		lcd_goto_xy(7,1);
		lcd_str(buf);

		sprintf(buf, "Y=%.2f V", voltage1);

		lcd_goto_xy(7,2);
		lcd_str(buf);
	}
}

void readJoystick()
{
	ADMUX &= ~(1<<MUX0);			//Valitaan AD-muuntimen MUXin ensimm‰inen tulo
	ADMUX &= ~(1<<MUX1);
	ADCSRA |= 1<<ADSC;
	_delay_ms(1);
	voltage= ((intermed *5)/1024);	//J‰nnitteen laskukaava	

	ADMUX |=1<<MUX0;
	ADMUX &= ~(1<<MUX1);				//Valitaan AD-muuntimen MUXin toinen tulo
	ADCSRA |= 1<<ADSC;
	_delay_ms(1);
	voltage1= ((intermed *5)/1024);	//J‰nnitteen laskukaava
}

void moveCursor()
{
	if (joystick)
	{
		if((voltage<2.4) & (x>1))	
		{

			x--;
			lcd_goto_xy(x,y);				//Siirret‰‰n osoitinta x-akselilla vasemmalle
			lcd_chr(132);
			lcd_goto_xy(x+1,y);				//Tyhjennet‰‰n osoittimen edellinen paikka
			lcd_str(" ");		
		}

		if((voltage>2.9) & (x<=20))
		{
			x++;
			lcd_goto_xy(x,y);				//Siirret‰‰n osoitinta x-akselilla oikealle
			lcd_chr(132);
			lcd_goto_xy(x-1,y);
			lcd_str(" ");
		}

		if((voltage1<2.4) & (y>0))
		{
			y--;
			lcd_goto_xy(x,y);				//Siirret‰‰n osoitinta y-akselilla alasp‰in
			lcd_chr(132);
			lcd_goto_xy(x,y+1);
			lcd_str(" ");
		}
		if((voltage1>2.9) & (y<7))
		{
			y++;
			lcd_goto_xy(x,y);				//Siirret‰‰n osoitinta y-akselilla ylˆsp‰in
			lcd_chr(132);
			lcd_goto_xy(x,y-1);
			lcd_str(" ");
		}
	}
}

ISR(ADC_vect)
{
	cli();						//Estet‰‰n keskeytykset

	uint8_t theLowADC = (ADCL>>6);	// Luetaan AD-muuntimelta tuleva LSB ja bittien siirto
	uint8_t theHighADC = ADCH;		// Luetaan AD-muuntimelta tuleva MSB

	ADCresult = theLowADC | (theHighADC<<2);	//Yhdistet‰‰n AD-muuntimen LSB ja MSB ja bittien siirto
	ADCresult = ADCresult & 0x03FF;				//Tuloksen maskaus
	intermed = ADCresult;						

	sei();										//Sallitaan keskeytykset
	ADCSRA |= 1<<ADSC;							//Aloitetaan uusi muunnos			
}


