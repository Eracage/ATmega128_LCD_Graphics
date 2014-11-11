#ifndef GRAPHICS_H
#define GRAPHICS_H

// 128*64
// first x = 4

#define HEIGHT 128
#define WIDTH 64
#define GROUPSIZE 8

typedef unsigned char byte;

byte m_display[HEIGHT/GROUPSIZE][WIDTH][2];

void Graphics_init();

void Graphics_draw();

void Graphics_pixel(char x, char y, char on);

#endif
