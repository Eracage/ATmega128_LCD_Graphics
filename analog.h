#ifndef JOYSTICK_H
#define JOYSTICK_H

#define ADC_MAX 1024

typedef struct
{
	short x, y;
} Pointi;

typedef struct
{
	float x, y;
} Pointf;

void Analog_Init();

// Returns value between 0 and ADC_MAX
short Analog_ReadX();
// Returns value between 0 and ADC_MAX
short Analog_ReadY();

Pointi Analog_GetPositioni();

Pointf Analog_GetPositionf();


#endif
