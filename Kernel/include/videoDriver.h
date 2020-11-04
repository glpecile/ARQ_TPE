/**
 * videoDriver.h: contrato para drivers relaiconado al manejo del video.
 */ 
#ifndef __videoDriver_H_
#define __videoDriver_H_
#define PIXEL 3
#define WIDTH 1024
#define HEIGHT 768
#include <lib.h>
#include <stdint.h>
#include <font.h>
#include <colors.h>
/**
 * Mueve la pantalla una posición hacia arriba desde la posición actual.
 */
void scrollUpScreen();
/**
 * Dibuja un pixel en la pantalla.
 */
void drawPixel(int x, int y, int color);
/**
 * Dibuja el cursor una posición determinada en en la pantalla.
 */
void drawCursor(int x, int y, int blink);
/**
 *  Dibuja un caracter de tamaño, color y posición determinada en pantalla.
 */
void drawChar(int x, int y, char character, int fontSize, int fontColor, int bgColor);
/**
 * Dibuja una figura genérica pasada como vector de chars en las coordenadas deseadas.
 */
void drawFigure(char *toDraw, int color, int size, int x, int y);

void drawRectangle(unsigned int x, unsigned int y, int b, int h, int color);
/**
 * Dibuja un cuadrado en una posición determinada a través de una syscall.
 */ 
void drawSquare(unsigned int x, unsigned int y, int l, int color);
/**
 *  Limpia la pantalla en su toalidad.
 */
void clearScreen();
void clearLine();
#endif