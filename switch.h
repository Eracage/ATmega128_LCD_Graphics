
#ifndef SWITCH_H
#define SWITCH_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

// Define switches 1..5 (0 = pressed)
#define SW_1      (1 << PD0)
#define SW_Left   SW_1
#define SW_2      (1 << PD1)
#define SW_Down   SW_2
#define SW_3      (1 << PD2)
#define SW_Right  SW_3
#define SW_4      (1 << PD3)
#define SW_Up     SW_4
#define SW_5      (1 << PD4)
#define SW_Center SW_5
#define SW_ALL    (SW_1 | SW_2 | SW_3 | SW_4 | SW_5)
#define SW_PORT   PIND

#define IsPressed(x)     (~SW_PORT & x)
#define EnableSwitch(x)  (DDRD &= ~(x))
#define DisableSwitch(x) (DDRD |= x)

#endif
