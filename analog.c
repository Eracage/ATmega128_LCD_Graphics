#include "analog.h"

#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

short ADCresult;

ISR(ADC_vect)
{
	cli();							//Switch interrupts off
	ADCresult = (0xFF & (ADCL>>6)) | ((0xFF & ADCH)<<2);
	sei();							//Switch interrupts on
	ADCSRA |= 1<<ADSC;				//Start a new conversion
}


void Analog_Init()
{
	ADCSRA |= 1<<ADPS2; 			//Prescaler 64 -> Correct frequency for AD converter
	ADCSRA |= 1<<ADPS1; 			//Prescaler 64 -> Correct frequency for AD converter

	ADMUX |=1<<ADLAR;				// ADC result left adjusted

	ADMUX &=~(1<<REFS0);			//Avcc(+5v) as voltage reference
	ADMUX &= ~(1<<REFS1);			//Avcc(+5v) as voltage reference

	ADCSRA |= 1<<ADIE;				//ADC Interrupt Enable

	ADCSRA |= 1<<ADEN;				//Start up AD converter

	sei();							//Switch interrupts on
}


short Analog_ReadX()
{
	ADMUX &= ~(1 << MUX0);			//Choose the first gain of MUX (last bit off)
	ADMUX &= ~(1 << MUX1);			//Choose the first gain of MUX (second last bit off)

	ADCSRA |= 1<<ADSC;				//Start a new conversion
	_delay_ms(1);					//Wait for the conversion to finish
	return ADCresult;

}
short Analog_ReadY()
{
	ADMUX |=1<<MUX0;				//Choose the second gain of MUX (last bit on)
	ADMUX &= ~(1<<MUX1);			//Choose the second gain of MUX (second last bit off)

	ADCSRA |= 1<<ADSC;				//Start a new conversion
	_delay_ms(1);					//Wait for the conversion to finish
	return ADCresult;
}

Pointi Analog_GetPositioni()
{
	Pointi retVal;
	retVal.x = Analog_ReadX();
	retVal.y = Analog_ReadY();
	return retVal;
}

Pointf Analog_GetPositionf()
{
	Pointf retVal;
	retVal.x = (float)Analog_ReadX() / ADC_MAX;
	retVal.y = (float)Analog_ReadY() / ADC_MAX;
	return retVal;
}