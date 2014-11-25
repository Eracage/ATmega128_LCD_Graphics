#include "analog.h"

#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

short ADCresult;

ISR(ADC_vect)
{
	cli();
	ADCresult = (0xFF & (ADCL>>6)) | ((0xFF & ADCH)<<2);
	sei();//Sallitaan keskeytykset
	ADCSRA |= 1<<ADSC;//Aloitetaan uusi muunnos			
}


void Analog_Init()
{
	ADCSRA |= 1<<ADPS2; 			//Esijakaja 64 -> Taajuus sopivaksi AD-muuntimelle
	ADCSRA |= 1<<ADPS1;
	ADMUX |=1<<ADLAR;				// ADC result left adjusted
	ADMUX &=~(1<<REFS0);
	ADMUX &= ~(1<<REFS1);			//Avcc(+5v) muuntimen referenssij�nnitteeksi
	ADCSRA |= 1<<ADIE;				//ADC Interrupt Enable
	ADCSRA |= 1<<ADEN;				//K�ynnistet��n AD-muunnin

	sei();	
}


short Analog_ReadX()
{
	ADMUX &= ~(1<<MUX0);			//Valitaan AD-muuntimen MUXin ensimm�inen tulo
	ADMUX &= ~(1<<MUX1);
	ADCSRA |= 1<<ADSC;
	_delay_ms(1);
	return ADCresult;

}
short Analog_ReadY()
{
	ADMUX |=1<<MUX0;
	ADMUX &= ~(1<<MUX1);				//Valitaan AD-muuntimen MUXin toinen tulo
	ADCSRA |= 1<<ADSC;
	_delay_ms(1);
	return ADCresult;
}