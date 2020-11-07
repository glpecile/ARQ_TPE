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
 *  typePiece: 0: Peon, 1: Torre, 2: Caballo, 3: Alfil, 4: Reina, 5: Rey.
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
    int empty; //si no esta vacio es 0
} t_tile;


void startGame(int mode);
void printPlayer(int number);
int processGame(char *inputBuffer);
void validMovePieces(int position[4]);
void drawBoard(int x, int y);

int attack(t_piece fromPiece, t_piece toPiece);
void enroque(int lon);
void coronation(t_piece fromPiece, typePieces toName, int toX, int toY);

// Pecas.
int pawn(t_piece fromPiece, int toX, int toY);
int tower(t_piece fromPiece, int toX, int toY);
int bishop(t_piece fromPiece, int toX, int toY);
int king(t_piece fromPiece, int toX, int toY);
int queen(t_piece fromPiece, int toX, int toY);
int horse(t_piece fromPiece, int toX, int toY);

#endif