#ifndef GRAPHICS_H
#define GRAPHICS_H

// Display size is 128*64
// Display first x is 4

#define HEIGHT 64 // Height of the LCD display
#define WIDTH 128 // Width of the LCD display
#define GROUPSIZE 8 // Page contains 8 pixels

typedef unsigned char byte;

// Initiates LCD display
void Display_Init();

// Swaps buffers. Updates LCD display only where there are changes in the pixel buffer
void Display_Update();

// Sets the state of a single pixel in the frame buffer
void Display_Pixel(byte x, byte y, byte on);

// Sets the inverse colors functionality on or off
void Dixplay_InverseColors(byte on);

// Sets all pixels in buffer to empty
void Display_Clear();

#endif
