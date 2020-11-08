/**
 * chess.h: Contrato juego de ajedrez.
*/
#ifndef _CHESS_H_
#define _CHESS_H_
#include <stdlib.h>
#include <shell.h>
#include <colors.h>
#include <chessPieces.h>
#include <chessConsole.h>

#define TILE 85
#define TIMER_TICKS_PER_SEC 18

#define NEW_GAME 0
#define CONTINUE_GAME 1
#define PLAYER1 1
#define PLAYER2 2
#define KING_KILLED 3

/**
 *  typePiece: 0: Peon, 1: Torre, 2: Caballo, 3: Alfil, 4: Reina, 5: Rey.
*/

typedef struct
{
    int player;
    typePieces name;
    int color;
    int posX;
    int posY;
    int moved; //si aun no se movio, esta en 0
} t_piece;

typedef struct
{
    t_piece piece;
    int empty; //si no esta vacio es 0
} t_tile;


void startGame(int mode);
int processGame(char *inputBuffer);
int validMovePieces(int position[4]);
void drawBoard(int x, int y);

int attack(t_piece fromPiece, t_piece toPiece);
void enroque(int lon);
void coronation(t_piece fromPiece, typePieces toName, int toX, int toY);

// Pecas.
int pawn(t_piece fromPiece, int toX, int toY);
int rook(t_piece fromPiece, int toX, int toY);
int bishop(t_piece fromPiece, int toX, int toY);
int king(t_piece fromPiece, int toX, int toY);
int queen(t_piece fromPiece, int toX, int toY);
int knight(t_piece fromPiece, int toX, int toY);

#endif