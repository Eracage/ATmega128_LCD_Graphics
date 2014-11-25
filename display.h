#ifndef GRAPHICS_H
#define GRAPHICS_H

// 128*64
// first x = 4

#define HEIGHT 128
#define WIDTH 64
#define GROUPSIZE 8

typedef unsigned char byte;

// Inits lcd display
void Display_Init();

// Swaps buffers
void Display_Update();

// Sets the state of a single pixel in the frame buffer
void Display_Pixel(byte x, byte y, byte on);

#endif