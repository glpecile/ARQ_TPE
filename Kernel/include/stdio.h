/**
 * stdio.h: contrato de libreria de kernel para el manejo del io en pantalla. 
 */ 
#ifndef __stdio_H_
#define __stdio_H_
#include <videoDriver.h>
#define FONT_SIZE 1
/**
 * Dibuja un caracter en la pantalla en base a la posición del cursor.
*/
void putchar(char c);
/**
 * Imprime un string en pantalla.
*/
void printString(char *string);
/**
 * Imprime un string en una linea en pantalla.
 */
void printStringln(char *string);
#endif


