/**
 * shell.c: Contrato para interprete de comandos del usuario.
*/
#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdlib.h>
#include <chess.h>

/**
 * Decidimos usar defines para el tamaño de los chars ya que una syscall seria innecesaria.
 */
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

#define HEIGHT getScreenHeight()
#define WIDTH getScreenWidth()

#define SECONDS 0
#define MINUTES 2
#define HOURS 4
#define DAY_OF_THE_WEEK 6
#define DAY_OF_THE_MONTH 7
#define MONTH 8
#define YEAR 9

typedef struct
{
    void (*command)(int argSize, char *args[]);
    char *name;
    char *description;
} t_command;

extern void _setCursor(int x, int y, int color);

extern void _clearScreen();

extern void _drawFigure(char *toDraw, int color, int size, int x, int y);

extern void getRegs(int argcount, char *args[]);

/**
 * Obtiene la cantidad de renglones en pantalla.
 */ 
int getScreenHeight();
/**
 * Obtiene la cantidad de posiciones de caracteres disponibles en pantalla.
 */ 
int getScreenWidth();
/**
 * Inicializa la estructura que ejecuta los programas del usuario.
*/
void intializeShell();
/**
 * Carga los camandos posibles para el usuario a traves de .
*/
void loadCommands();
/**
 * Actua de 
*/
void loadCommand(void (*fn)(), char *name, char *desc);

int readInput(char *inputBuffer, int maxSize, char token);
int processInput(char *inputBuffer);

/****************** COMANDOS ******************/
void printUser();
void help();
void inforeg(uint64_t *reg);
void printCurrentTime();
void printmem();
void invalidOpCodeException();
void invalidZeroDivisionException();
void chess(int argSize, char *args[]);

#endif