/**
 * chess.c: Juego de ajedrez.
*/
#include <chess.h>

t_tile board[8][8];

void startGame(int mode)
{
    int c;
    if (mode == NEW_GAME)
    {
        _clearScreen();
        board(0, 0);
        // int sizeInfo[2] = {PIECE_HEIGHT, PIECE_WIDTH};
        // _drawFigure(piecesBitmap(PAWN), 0, 0, 50, WHITE, BLACK, sizeInfo);
        while ((c = getChar()) != 'q')
        {
        }
        _clearScreen();
    }
    if (mode == CONTINUE_GAME)
        print("continue");
    putChar('\n');
}

void drawBoard(int x, int y)
{
    // char num[1];
    for (int i = 0; i < 8; i++) //WIDTH_T / PIECE_WIDTH
    {
        for (int j = 0; j < 8; j++) //HEIGHT_T / PIECE_HEIGHT
        {
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) //ambos pares, o ambos impares
                _drawSquare(x + i * TILE, y + j * TILE, TILE, BEIGE);
            else
                _drawSquare(x + i * TILE, y + j * TILE, TILE, BROWN);
        }
        // numToStr(i,num,1);
        // print(num);
    }
    // print("a\tb\tc\td\te\tf\tg\th\n");
}

void pawn(int x, int y){
    // if(board[x][y+1] == free){

    // }
}
