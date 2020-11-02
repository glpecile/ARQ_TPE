/**
 * exception.c: Contrato para manejo de excepciones.
*/
#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_
#include <stdio.h>
#include <naiveConsole.h>
#define REG_SIZE 17
/**
 * Obtiene el SP.
 */
extern uint64_t getSP();
/**
 * Toma los valores iniciales del IP y SP para poder reinicar la shell si es necesario,
 * en caso de realizar una excepción.
 */ 
void initialStateSnapshot(uint64_t IP, uint64_t SP);
#endif