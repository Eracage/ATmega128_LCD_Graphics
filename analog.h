#ifndef JOYSTICK_H
#define JOYSTICK_H

#define ADC_MAX 1024

typedef struct Point
{
	short x, y;
} Point;

void Analog_Init();

// Returns value between 0 and ADC_MAX
short Analog_ReadX();
// Returns value between 0 and ADC_MAX
short Analog_ReadY();


#endif
