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
#define TILE 85

#define NEW_GAME 0
#define CONTINUE_GAME 1
#define PLAYER1 1
#define PLAYER2 2

/**
 *  -1: No ocupado, 0: Peon, 1: Torre, 2: Caballo, 3: Alfil, 4: Reina, 5: Rey.
*/

typedef struct
{
    int player;
    typePieces name;
    int color;
    int state; //si esta vivo es 0, sino 1
    int posX;
    int posY;
    int moved; //si aun no se movio, esta en 0
    //int (*fn)(int fromX, int fromY, int toX, int toY);
} t_piece;

typedef struct
{
    t_piece piece;
    int empty; //si esta vacio es 0
} t_tile;


void startGame(int mode);
int processGame(char *inputBuffer);
void movePieces(int position[4]);
void drawBoard(int x, int y);

void attack(t_piece fromPiece, t_piece toPiece);

//Pecas
void pawn(t_piece fromPiece, int toX, int toY);
void tower(t_piece fromPiece, int toX, int toY);
void bishop(t_piece fromPiece, int toX, int toY);
void king(t_piece fromPiece, int toX, int toY);
void horse(t_piece fromPiece, int toX, int toY);

#endif