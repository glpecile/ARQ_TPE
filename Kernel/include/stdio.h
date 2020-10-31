/**
 * stdio.h: contrato de libreria de kernel para el manejo del io en pantalla. 
 */ 
#ifndef __stdio_H_
#define __stdio_H_
#include <videoDriver.h>
#define FONT_SIZE 1
/**
 * Define una nueva posicón valida para el cursor y lo vuelve a dibujar.
*/
void setCursor(unsigned int new_x, unsigned int new_y);
/**
 * Dibuja un caracter en la pantalla en base a la posición del cursor.
*/
void putchar(char c);
/**
 * Syscall para escribir en pantalla.
 */ 
uint64_t sWrite(char *buffer, int size);
#endif


