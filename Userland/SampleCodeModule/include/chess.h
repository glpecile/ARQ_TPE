/**
 * chess.h: Contrato juego de ajedrez.
*/
#ifndef _CHESS_H_
#define _CHESS_H_
#include <stdlib.h>
#include <shell.h>
#include <colors.h>
#include <chessPieces.h>

#define WIDTH_T 1024
#define HEIGHT_T 768

/**
 *  -1: No ocupado,
 *  0: Peon,
 *  1: Torre,
 *  2: Caballo,
 *  3: Alfil,
 *  4: Reina,
 *  5: Rey.
*/
typedef struct
{
    int player;
    int name;
    int color;
    int state;
    int posX;
    int posY;
    //int (*fn)(int fromX, int fromY, int toX, int toY);
} t_piece;

#define NEW_GAME 0
#define CONTINUE_GAME 1
#define TILE 90

void startGame(int mode);
int processGame(char *inputBuffer);
void movePieces(int position[4]);
void drawBoard(int x, int y);
#endif