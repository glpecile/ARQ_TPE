#ifndef __videoDriver_H_
#define __videoDriver_H_
void drawPixel(int x, int y, int color);
void drawChar(int x, int y, char character, int fontSize, int fontColor, int bgColor);
void drawRectangle(unsigned int x, unsigned int y, int b, int h, int color);
void drawSquare(unsigned int x, unsigned int y, int l, int color);
#endif