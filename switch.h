
#ifndef SWITCH_H
#define SWITCH_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

// Define switches 1..5 (0 = pressed)
#define SW_Left   (1 << PD0)		
#define SW_Down   (1 << PD1)
#define SW_Right  (1 << PD2)
#define SW_Up     (1 << PD3)
#define SW_Center (1 << PD4)
#define SW_ALL    (SW_Left | SW_Right | SW_Up | SW_Down | SW_Center)
#define SW_PORT   PIND

#define IsPressed(x)     (~SW_PORT & x)
#define EnableSwitch(x)  (DDRD &= ~(x))
#define DisableSwitch(x) (DDRD |= x)

#endif
