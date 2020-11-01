/**
 * stdlib.h: contrato de librería estandar del usuario.
 */
#ifndef _stdlib_H_
#define _stdlib_H_
#include <stdint.h>
#include <colors.h>
/**
 * Funciones a syscall asm.
 */
extern uint64_t _swrite(char *buffer, int size);
/**
 * Obtiene un caracter desde entrada estandar.
 */
extern uint64_t _sGetChar();
// extern int _sread(unsigned int fd, const char *buffer, int size);

uint64_t getChar();

void putChar(char c);

void print(char *s);

int strlen(char *s);

int scan(char *buffer, int size);

int strtok(char *s, char delim, char *array[], int arraySize);

int strcmp(char *s1, char *s2);

// uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base);

// void printHex(uint64_t value);

// void printBase(uint64_t value, uint32_t base);

#endif