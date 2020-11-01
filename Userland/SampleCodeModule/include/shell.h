/**
 * shell.c: Contrato para interprete de comandos del usuario.
*/
#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdlib.h>
/**
 * Decidimos usar defines para la resolución de la pantalla ya que una syscall es más costosa.
 */
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16
#define WIDTH 1024 / CHAR_WIDTH
#define HEIGHT 768 / CHAR_HEIGHT

typedef struct{
    void(*command)(int args, char *arg[]);
    char *name;
    char *description;
}t_command;
/**
 * Inicializa la estructura que ejecuta los programas del usuario.
*/
void intializeShell();
/**
 * 
*/
void loadCommands();
void readInput(char * inputBuffer, int maxSize);
int processInput(char *inputBuffer);
void help();
void inforeg(uint64_t *reg);
void printCurrentTime();
extern void _setCursor(int x, int y);

#endif