/**
 * chess.c: Juego de ajedrez.
*/
#include <chess.h>
#define MAX_INPUT 5
#define MAX_ARGUMENTS 3

static t_tile board[8][8];

static t_piece getPiece(int x, int y);

static void initializePiece(t_piece piece, int player, typePieces name, int color, int posX, int posY);
static void initializeTile(t_tile tile, int posX, int posY, t_piece piece);

void startGame(int mode)
{
    drawBoard(300, 0);
    if (mode == NEW_GAME)
    {
        _clearScreen();
        char input[MAX_INPUT];
        int quit = 1;
        //int sizeInfo[2] = {PIECE_HE// IGHT, PIECE_WIDTH};
        //_drawFigure(piecesBitmap(PAWN), 0, 0, 90, WHITE, BEIGE, sizeInfo);
        while (quit) //c = getChar()) != 'q'
        {
            quit = readInput(input, MAX_INPUT, 'q');
            proccessGame(input);
        }
        _clearScreen();
    }
    if (mode == CONTINUE_GAME)
        print("continue");
    putChar('\n');
}

void printPlayer(int number)
{

    printWithColor("Player", GREEN);
}

int processGame(char *inputBuffer)
{
    char *args[MAX_ARGUMENTS];
    int argSize = strtok(inputBuffer, ' ', args, MAX_ARGUMENTS);
    // Solo se permiten hasta 2 arg, el origen y el destino
    if (argSize <= 0 || argSize > 2)
    {
        print("Invalid amount of arguments, try again.\n");
        return 0;
    }
    int position[4] = {-1, -1, -1, -1};
    for (int i = 0; i < argSize; i++)
    {
        //A1 A2
        int letter = args[i][0];
        int num = args[i][1];
        int flag = letter >= 'A' && letter <= 'H' && num >= '0' && num <= '7';
        if (!flag)
        {
            print("Invalid input, please use the correct notation.");
            return 0;
        }
        position[i] = letter;
        position[i + 1] = num;

        //if(board.fn - fn[i].fromX(args[0][0]-'A' == 0)
    }
    movePieces(position);
    return 1;
}

static void initializePiece(t_piece piece, int player, typePieces name, int color, int pose){int posY
    pipiece.player = player;
    piece.name = name;
    piece.color = color;
    ece.state = 0;
 
    piece.posX = posX;
    piece.posY = posY;  
    piece.moved  =0;

static void initializeTile(t_tile tile, int posX, int posY, t_piece piece){
    tile.posX = posX;
    tile.posY = posY;
    tile.piece = piece;
    tile.empty = 0;
}

vePiecovesi(int position[4])
{
    int fromX = position[0];
    int fromY = position[1];
    int toX = position[2];
    int toY = position[3];
    t_tile space = board[fromX][fromY];
    if (space.empty == 0)
    {
        print("No piece to access. Please move an actual piece");
        return;
    }
    if (fromX == toX && fromY == toY)
    {
        print("Invalid move");
        return;
    }
    //move.fn(fromX, fromY, toX, toY);
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
    //print("a\tb\tc\td\te\tf\tg\th\n");
}

//************* MOVIMIENTOS ***********//
void comer(t_piece fromPiece, t_piece toPiece)
{
    if (toPiece != null && fromPiece.player != toPiece.player)
    {
        //deleteFigure(toPiece);
        move(fromPiece, toPiece.posX, toPiece.toY);
    }
    else
    {
        print("Invalid move.");
        return;
    }
}

static t_piece getPiece(int x, int y)
{
    t_piece *toReturn = board[x][y];
    return *toReturn;
}

void move(struct t_piece piece, int toX, int toY)
{
    piece->posX = toX;
    piece->posY = toY;
    board[toX][toY] = &piece;
    board[piece->posX][piece->posY] = null;
}

//************* PIEZAS ***********//


// void pawn(t_piece fromPiece, int toX, int toY)
// {
//     int fromY = fromPiece.posY;
//     int fromX = fromPiece.posX;
//     if (fromY >= toY)
//     {
//         print("Invalid move.");
//         return;
//     }
//     if (fromX != toX)
//     {
//         if (toX != fromX + 1 || toX != fromX - 1)
//         {
//             print("Invalid move. You can only move once in diagonal.");
//             return;
//         }
//         else
//         {
//             if (toX == fromX + 1)
//             {
//                 t_piece toPiece = getPiece(toX + 1, toY);
//                 if (toPiece != null)
//                 {
//                     comer(fromPiece, toPiece);
//                 }
//                 //vereficamos si podemos hacer captura al paso
//                 else
//                 {
//                     t_piece toPiece = getPiece(toX + 1, toY - 1);
//                     if (toPiece != null)
//                         comer(fromPiece, toPiece);
//                 }
//             }
//             if (toX == fromX - 1)
//             {
//                 t_piece toPiece = getPiece(toX - 11, toY);
//                 if (toPiece != null)
//                 {
//                     comer(fromPiece, toPiece);
//                 }
//                 //vereficamos si podemos hacer captura al paso
//                 else
//                 {
//                     t_piece toPiece = getPiece(toX - 1, toY - 1);
//                     if (toPiece != null)
//                         comer(fromPiece, toPiece);
//                 }
//             }
//         }
//     }
//     else
//     {
//         if ((toY != fromY + 1) || (toY != fromY + 2))
//         {
//             print("Invalid move.");
//             return;
//         }
//         //chequeo que no haya una pieza por delante, si no la hay me muevo.
//         t_piece toPiece = getPiece(toX, toY);
//         if (toPiece == null)
//         {
//             move(fromPiece, toX, toY);
//         }
//     }
//     if (toY == HEIGHT_T - 1)
//     {
//         //llegar al final del tablero, puedo "cambiar" de  pieza
//     }
// }

void tower(t_piece piece, int toX, int toY)
{
    if (piece.posX != toX || piece.posY != toY)
    {
        print("Invalid move.");
        return;
    }    
}


// void bishop(t_piece fromPiece, int toX, int toY){
//     int fromX =fromPiece.posX;
//     int fromY = fromPiece.posY;
//     if((toX - fromX != toY - fromY) || (fromX - toX != fromY - toY)){
//         print("Invalid move.");
//         return;
//     }
// }

// void king(t_piece fromPiece, int toX, int toY){
//     int fromX =fromPiece.posX;
//     int fromY = fromPiece.posY;
//     if(((toX != fromX +1) || (toX != fromX -1)) && ((toY != fromY +1) || (toY != fromY -1))) {
//         print("Invalid move.");
//         return;
//     }
// }

// void horse(t_piece fromPiece, int toX, int toY){
//     int fromX =fromPiece.posX;
//     int fromY = fromPiece.posY;
//     if(((toX != fromX +2) || (toX != fromX -2)) && ((toY != from +1) || (toY != from -1)) 
//         ((toX != fromX +1) || (toX != fromX -1)) && ((toY != from +2) || (toY != from -2))){
//             print("Invalid move.");
//             return;
//         }
// }
