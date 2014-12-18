#ifndef JOYSTICK_H
#define JOYSTICK_H

#define ADC_MAX 1024

// Struct for short type point data
typedef struct
{
	short x, y;
} Pointi;

// Struct for float type point data
typedef struct
{
	float x, y;
} Pointf;

// Initiates the ADC
void Analog_Init();

// Returns value between 0 and ADC_MAX
short Analog_ReadX();
// Returns value between 0 and ADC_MAX
short Analog_ReadY();

// Returns Pointi with values between 0 and ADC_MAX
Pointi Analog_GetPositioni();

// Returns Pointf with values between 0 and 1
Pointf Analog_GetPositionf();


#endif
