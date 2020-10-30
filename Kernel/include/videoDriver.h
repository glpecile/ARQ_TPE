/**
 * videoDriver.h: contrato para drivers relaiconado al manejo del video.
 */ 
#ifndef __videoDriver_H_
#define __videoDriver_H_
#define PIXEL 3
#include <lib.h>
#include <stdint.h>
#include <font.h>
#include <colors.h>
void scrollUpScreen();
void drawPixel(int x, int y, int color);
void drawCursor(int x, int y);
void drawChar(int x, int y, char character, int fontSize, int fontColor, int bgColor);
void drawRectangle(unsigned int x, unsigned int y, int b, int h, int color);
void drawSquare(unsigned int x, unsigned int y, int l, int color);
void clearScreen();
void deleteChar(int x, int y);
int getWidth();
int getHeight();
#endif