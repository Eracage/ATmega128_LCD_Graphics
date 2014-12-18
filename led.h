
#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

// Define LEDs 1..3 (0 = on)
#define LED_1    (1 << PD5)
#define LED_2    (1 << PD6)
#define LED_3    (1 << PD7)
#define LED_ALL  (LED_1 | LED_2 | LED_3)
#define LED_PORT PORTD

#define TurnOn(x)     (LED_PORT &= ~(x))
#define TurnOff(x)    (LED_PORT |= x)
#define EnableLED(x)  (DDRD |= x)
#define DisableLED(x) (DDRD &= ~(x))

#endif
