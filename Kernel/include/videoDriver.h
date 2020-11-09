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
void drawCursor(int x, int y, int blink, int color);
/**
 *  Dibuja un caracter de tamaño, color y posición determinada en pantalla.
 */
void drawChar(int x, int y, char character, int fontSize, int fontColor, int bgColor);
/**
 * Dibuja una figura genérica pasada como vector de chars en las coordenadas deseadas.
 */
void drawFigure(char *toDraw, int color, int size, int x, int y);
/**
 * Dibuja un rectangulo en una posición determinada.
 */
void drawRectangle(unsigned int x, unsigned int y, int base, int height, int color);
/**
 * Misma funcionalidad que drawRectangle, composicion con la misma.
 */
void drawSquare(unsigned int x, unsigned int y, int area, int color);
/**
 * Limpia la pantalla en su toalidad.
 */
void clearScreen();
/**
 * Limpia una linea en la pantalla.
 */ 
void clearLine();
/**
 * Retorna la cantidad de pixeles horizontales de la pantalla.
 */ 
int getPixelWidth();
/**
 * Retorna la cantidad de pixeles Verticales de la pantalla.
 */ 
int getPixelHeight();
#endif