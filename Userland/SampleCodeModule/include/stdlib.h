/**
 * stdlib.h: contrato de librería estandar del usuario.
 */
#ifndef _stdlib_H_
#define _stdlib_H_
#include <stdint.h>
/**
 * Funciones a syscall asm.
 */
extern uint64_t _swrite(char *buffer, int size);
// extern int _sread(unsigned int fd, const char *buffer, int size);

/**
 * Obtiene un caracter desde entrada estandar.
 */ 
int getChar();

void putChar(char c);

void print(char *s);

int strlen(char *s);

int scan(char *buffer, int size);
#endif