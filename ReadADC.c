#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"

short ReadADC(unsigned char ch)
{

	ADMUX=0x40;

   //Select ADC Channel ch must be 0-7
   ch=ch&0b00000111;
   ADMUX|=ch;

   //Start Single conversion
   ADCSRA|=(1<<ADSC);

   //Wait for conversion to complete
   while(!(ADCSRA & (1<<ADIF)));

   //Clear ADIF by writing one to it
   ADCSRA|=(1<<ADIF);

   return(ADC);
}

