/**
 * stdlib.h: contrato de librería estandar del usuario.
 */
#ifndef _stdlib_H_
#define _stdlib_H_
#include <stdint.h>

// asm.
extern int swrite(char *buffer, int size);
extern int sread(unsigned int fd, const char *buffer, int size);

int getChar();

void putChar(char c);

void print(char *s);

int strlen(char *s);

int scan(char *buffer, int size);
#endif