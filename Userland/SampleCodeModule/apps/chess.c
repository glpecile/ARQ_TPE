/**
 * chess.c: Juego de ajedrez.
*/
#include <chess.h>
#define MAX_INPUT 5
#define MAX_ARGUMENTS 3
#define FALSE 0
#define TRUE 1
#define FIRST_ROW 0
#define FINAL_ROW 7

static t_tile board[8][8];
char input[MAX_INPUT];

static t_piece initializePiece(int posX, int posY, typePieces name, int color, int player);
static void initializeBoard();
static void fetchMovement(t_piece piece, int toX, int toY);

static void deleteFigure(t_piece toPiece);
static t_tile getTile(int x, int y);
static void move(t_piece piece, int toX, int toY);
static void isEmpty(t_piece fromPiece, t_piece toPiece);
//static void enroque(t_piece tower1, t_piece tower2, t_piece queen, int long);

void startGame(int mode)
{
    _clearScreen();
    _setCursor(0,0);
    print("Player 1:  \t");
    print("Player 1:  \t");
    print("    TIME: ");
    drawBoard(300, 0);
    _setCursor(0, HEIGHT);
    if (mode == NEW_GAME)
    {
        int quit = 1;
        initializeBoard();
        //int sizeInfo[2] = {PIECE_HE// IGHT, PIECE_WIDTH};
        //_drawFigure(piecesBitmap(PAWN), 0, 0, 90, WHITE, BEIGE, sizeInfo);
        while (quit) //c = getChar()) != 'q'
        {
            quit = readInput(input, MAX_INPUT, 'q');
            processGame(input);
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
    }
    movePieces(position);
    return 1;
}
static void initializeBoard()
{
    for (int j = 0; j < 8; j++)
    {
        //Se ponen los peones primero con sus respectivos colores y posiciones.
        board[1][j].empty = FALSE;
        board[6][j].empty = FALSE;
        board[1][j].piece = initializePiece(1, j, PAWN, WHITE, PLAYER1);
        board[6][j].piece = initializePiece(6, j, PAWN, BLACK, PLAYER2);
    }
    //Se ponen las torres
    board[0][0].empty = FALSE;
    board[7][0].empty = FALSE;
    board[0][0].piece = initializePiece(0, 0, TOWER, WHITE, PLAYER1);
    board[7][0].piece = initializePiece(7, 0, TOWER, BLACK, PLAYER2);
    board[0][7].empty = FALSE;
    board[7][7].empty = FALSE;
    board[0][7].piece = initializePiece(0, 7, TOWER, WHITE, PLAYER1);
    board[7][7].piece = initializePiece(7, 7, TOWER, BLACK, PLAYER2);

    //Se ponen los caballos
    board[0][1].empty = FALSE;
    board[7][1].empty = FALSE;
    board[0][1].piece = initializePiece(0, 1, HORSE, WHITE, PLAYER1);
    board[7][1].piece = initializePiece(7, 1, HORSE, BLACK, PLAYER2);
    board[0][6].empty = FALSE;
    board[7][6].empty = FALSE;
    board[0][6].piece = initializePiece(0, 6, HORSE, WHITE, PLAYER1);
    board[7][6].piece = initializePiece(7, 6, HORSE, BLACK, PLAYER2);

    //Se ponen los alfiles
    board[0][2].empty = FALSE;
    board[7][2].empty = FALSE;
    board[0][2].piece = initializePiece(0, 2, BISHOP, WHITE, PLAYER1);
    board[7][2].piece = initializePiece(7, 2, BISHOP, BLACK, PLAYER2);
    board[0][5].empty = FALSE;
    board[7][5].empty = FALSE;
    board[0][5].piece = initializePiece(0, 5, BISHOP, WHITE, PLAYER1);
    board[7][5].piece = initializePiece(7, 5, BISHOP, BLACK, PLAYER2);

    //Se pone a la reina
    board[0][3].empty = FALSE;
    board[7][3].empty = FALSE;
    board[0][3].piece = initializePiece(0, 3, QUEEN, WHITE, PLAYER1);
    board[7][3].piece = initializePiece(7, 3, QUEEN, BLACK, PLAYER2);

    //Se pone al rey
    board[0][4].empty = FALSE;
    board[7][4].empty = FALSE;
    board[0][4].piece = initializePiece(0, 4, KING, WHITE, PLAYER1);
    board[7][4].piece = initializePiece(7, 4, KING, BLACK, PLAYER2);

    //Se inicializan los espacios vacios de la matriz logica
    for (int i = 2; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j].empty = TRUE;
            board[7 - i][j].empty = TRUE;
        }
    }
}

static t_piece initializePiece(int posX, int posY, typePieces name, int color, int player){
    t_piece piece;
    piece.player = player;
    piece.name = name;
    piece.color = color;
    piece.state = 0;
    piece.posX = posX;
    piece.posY = posY;
    piece.moved = FALSE;
    return piece;
}

void movePieces(int position[4])
{
    int fromX = position[0];
    int fromY = position[1];
    int toX = position[2];
    int toY = position[3];
    t_tile space = board[fromX][fromY];
    if (space.empty)
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
    fetchMovement(space.piece, toX, toY);
}

static void fetchMovement(t_piece piece, int toX, int toY){
    switch (piece.name)
    {
    case PAWN:
        pawn(piece, toX, toY);
        break;
    case TOWER:
        tower(piece, toX, toY);
        break;
    case BISHOP:
        bishop(piece, toX, toY);
        break;
    case KING:
        king(piece, toX, toY);
        break;
    case HORSE:
        horse(piece, toX, toY);
        break;

    default:
        break;
    }
    t_tile toTile = getTile(toX, toY);
    isEmpty(piece, toTile.piece);
}

void drawBoard(int x, int y)
{
    //char num[1];
    for (int i = 0; i < 8; i++) //WIDTH_T / PIECE_WIDTH
    {
        for (int j = 0; j < 8; j++) //HEIGHT_T / PIECE_HEIGHT
        {
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) //ambos pares o ambos impares
                _drawSquare(x + i * TILE, y + j * TILE, TILE, BEIGE);
            else
                _drawSquare(x + i * TILE, y + j * TILE, TILE, BROWN);
        }
        // numToStr(i,num,1);
        // print(num);
    }
    // print("a\t");
    // print("b\t");
    // print("c\t");
    // print("d\t");
    // print("e\t");
    // print("f\t");
    // print("g\t");
    // print("h\n");
}

//************* MOVIMIENTOS ***********//
void attack(t_piece fromPiece, t_piece toPiece)
{
    if (fromPiece.player != toPiece.player)
    {
        deleteFigure(toPiece);
        //move(fromPiece, toPiece.posX, toPiece.posY);
    }
    else
    {
        print("Invalid move.");
        return;
    }
}

static void deleteFigure(t_piece toPiece){
    //_drawFigure(piecesBitmap(toPiece.name), 0, 0, 90, toPiece.color, toPiece.color, sizeInfo);
}

static t_tile getTile(int row, int col)
{
    return board[row][col];
}

static void move(t_piece piece, int toX, int toY)
{
    board[piece.posX][piece.posY].empty = TRUE;
    piece.posX = toX;
    piece.posY = toY;
    board[toX][toY].piece = piece;
    board[toX][toY].empty = FALSE;
    
}
static void isEmpty(t_piece fromPiece, t_piece toPiece){
    int fromX =fromPiece.posX, fromY = fromPiece.posY;
    int toX =toPiece.posX, toY = toPiece.posY;

    for(int i = fromX; i <= toX; i++){
        for (int j = fromY; j <= toY; j++)
        {
            if(board[i][j].empty != TRUE)
                return;
        } 
    }

    move(fromPiece, toX, toY);
}

// static void enroque(t_piece tower1, t_piece tower2, t_piece queen, int long){
//     //solo si las torres y la reina estan en posiciones iniciales
//     if(tower1.moved != FALSE && tower2.moved != FALSE && queen.moved != FALSE && (long != 2 || long != 3)){
//         print("No se puede hacer enroque");
//     }
//     //vemos de izquierda a derecha, torre 1 es en A1 y torre 2 es en H1
//     int fromT1X = tower1.posX, fromT1Y = tower1.posY;
//     int fromT2X = tower2.posX, fromT2Y = tower2.posY;
//     int fromQX = queen.posX, fromQY = queen.posY;

//     t_tile toTTile, toQTile;
        
//     if(long == 2){//enroque corto
//         toTTile= getTile(fromT2X +2, fromT2Y);
//         if(toTTile.empty != FALSE)
//             move(tower2, fromT2X +2, fromT2Y);
//     }
//     if(long == 3){//enroque largo
//         toTTile = getTile(fromT1X +3, fromT1Y);
//         if(toTTile.empty != FALSE)
//             move(tower1, fromT2X +3, fromT1Y);
//     }
    
//     toQTile = getTile(fromQX -2, fromQY);
//     if(toQTile.empty != FALSE)
//         move(queen, fromQX -2, fromQY);
// }

//************* PIEZAS ***********//

void pawn(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    if (fromY >= toY)
    {
        print("Invalid move.");
        return;
    }
    t_tile toTile;
    if (fromX != toX)
    {
        if (toX != fromX + 1 || toX != fromX - 1)
        {
            print("Invalid move. You can only move once in diagonal.");
            return;
        }
        else
        {
            if (toX == fromX + 1)
            {
                toTile = getTile(toX + 1, toY);
                if (toTile.empty != FALSE)
                {
                    attack(fromPiece, toTile.piece);
                }
                //vereficamos si podemos hacer captura al paso
                else
                {
                    toTile = getTile(toX + 1, toY - 1);
                    if (toTile.empty != FALSE)
                        attack(fromPiece, toTile.piece);
                }
            }
            if (toX == fromX - 1)
            {
                toTile = getTile(toX - 11, toY);
                if (toTile.empty != FALSE)
                {
                    attack(fromPiece, toTile.piece);
                }
                //vereficamos si podemos hacer captura al paso
                else
                {
                    toTile = getTile(toX - 1, toY - 1);
                    if (toTile.empty != FALSE)
                        attack(fromPiece, toTile.piece);
                }
            }
        }
    }
    else
    {
        if ((toY != fromY + 1) || (toY != fromY + 2))
        {
            print("Invalid move.");
            return;
        }
        else{
            if(toY == fromY +2 && fromPiece.moved != FALSE){
                print("Invalid move.");
                return;
            }
        }
    }
    if (toY == FINAL_ROW || toY == FIRST_ROW)
    {
        //llegar al final del tablero, puedo "cambiar" de  pieza

    }
}

void tower(t_piece fromPiece, int toX, int toY)
{
    int fromX =fromPiece.posX;
    int fromY = fromPiece.posY;
    if (fromX!= toX || fromY != toY)
    {
        print("Invalid move.");
        return;
    }    
    t_tile toTile = getTile(toX, toY);
    if(toTile.empty != FALSE)
        attack(fromPiece, toTile.piece);
}


void bishop(t_piece fromPiece, int toX, int toY){
    int fromX =fromPiece.posX;
    int fromY = fromPiece.posY;
    if((toX - fromX != toY - fromY) || (fromX - toX != fromY - toY)){
        print("Invalid move.");
        return;
    }
    t_tile toTile = getTile(toX, toY);
    if(toTile.empty != FALSE)
        attack(fromPiece, toTile.piece);
}

void king(t_piece fromPiece, int toX, int toY){
    int fromX =fromPiece.posX;
    int fromY = fromPiece.posY;
    if(((toX != fromX +1) || (toX != fromX -1)) && ((toY != fromY +1) || (toY != fromY -1))) {
        print("Invalid move.");
        return;
    }
    t_tile toTile = getTile(toX, toY);
    if(toTile.empty != FALSE)
        attack(fromPiece, toTile.piece);
}

void horse(t_piece fromPiece, int toX, int toY){
    int fromX =fromPiece.posX;
    int fromY = fromPiece.posY;
    if( (((toX != fromX +2) || (toX != fromX -2)) && ((toY != fromY +1) || (toY != fromY -1))) ||
        (((toX != fromX +1) || (toX != fromX -1)) && ((toY != fromY +2) || (toY != fromY -2))) ){
            print("Invalid move.");
            return;
        }
    t_tile toTile = getTile(toX, toY);
    if(toTile.empty != FALSE)
        attack(fromPiece, toTile.piece);
}
