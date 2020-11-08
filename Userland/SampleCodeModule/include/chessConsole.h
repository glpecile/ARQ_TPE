/**
 * chessConsole.h: Contrato consola del juego de ajedrez.
*/
#ifndef _CHESSCONSOLE_H_
#define _CHESSCONSOLE_H_
#include <chess.h>
#include <shell.h>
#include <stdlib.h>

#define MAX_WIDTH 300
#define PLAYER_LENGTH 7 * CHAR_WIDTH
#define THRESHOLD (MAX_WIDTH - PLAYER_LENGTH) / CHAR_WIDTH
#define LAST_LINE 48-1 // Trae errores de compilacion de scope si se modifica llamando por syscall al tamaño actual. 

void initializeCursor();
void printIn(char *string, int x, int y, int color);
void printCommand(char *string);
void printPlayer(int number, int line);
void printLogLine(char *move, int player);
void clearLine(int y);
void addMoveToLog(char *move, int player);
void moveUpLog();
void updateTimerConsole(int time);
char *getNextMove(int i);
int getVerticalPixelPosition(int value);
int getHorizontalPixelPosition(int value);
void displayChar(char c);
void printEntireLog();
void resetCursor();
void initializeLog();
#endif