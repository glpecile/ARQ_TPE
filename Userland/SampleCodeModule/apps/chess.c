/**
 * chess.c: Juego de ajedrez.
*/
#include <chess.h>
#define MAX_INPUT 8
#define MAX_ARGUMENTS 4
#define ESC 27
#define FALSE 0
#define TRUE 1
#define FIRST_ROW 0
#define FINAL_ROW 7
#define abs(x)  (x<0)?-x:x

t_tile board[8][8];
char input[MAX_INPUT];
char *piecesCoronation[4]= { "queen", "tower", "bishop", "horse"};
static typePieces toCoronation = 6;

//void intializeTestingBoard();

static t_piece initializePiece(int posX, int posY, typePieces name, int color, int player);
static void initializeBoard();
static void drawPieces(int x, int y);
static int fetchMovement(t_piece piece, int toX, int toY);

static void deleteFigure(t_piece toPiece);
static t_tile getTile(int x, int y);
static void move(t_piece piece, int toX, int toY);
static int isEmptyP(t_piece fromPiece, int toX, int toY ,int iX, int iY);
static int isEmptyN(t_piece fromPiece, int toX, int toY, int iX, int iY);
static int isEmptyP2(t_piece fromPiece, int toX, int toY, int iX, int iY);
static int isEmptyN2(t_piece fromPiece, int toX, int toY, int iX, int iY);

void startGame(int mode)
{
    _clearScreen();
    //_setCursor(0,10);
    // print("Player 1: \t");
    // print("Player 2: \t");
    // print("TIME: ");
    // putChar('\n');
    drawBoard(300, 0);
    //_setCursor(0, HEIGHT);

    if (mode == NEW_GAME)
    {
        int quit = 1;
        initializeBoard();
        //intializeTestingBoard();
        drawPieces(300, 0);
        while (quit) //c = getChar()) != 'q'
        {
            printPlayer(1);
            quit = readInput(input, MAX_INPUT, ESC);
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
        return 0;
    
    int position[4] = {-1, -1, -1, -1};
    int dimPosition = 0;
    
    for (int i = 0; i < argSize; i++)
    {
        //A1 A2
        int letter = args[i][0];
        int num = args[i][1];
        int flag = letter >= 'A' && letter <= 'H' && num >= '1' && num <= '8';
        if (!flag)
        {
            if(letter == 'E'){//verificamos si entro un e y long, para hacer enroque
                num = args[i+1][0];                
                enroque(2);
                return 1;
            }
            for (int j = 0; j < 4; j++)
            {
                if (strcmp(args[0], piecesCoronation[j]) )
                {
                    toCoronation = j; //paso el tipo de pieza
                    return 1;           
                }
            }
            //print("Invalid input, please use the correct notation.");
            return 0;
        }
        position[dimPosition++] = letter -'A';
        position[dimPosition++] = num - '0' - 1;
    }
    
    validMovePieces(position);
    return 1;
}

void validMovePieces(int position[4])
{
    int fromX = position[0]; // A - H COLUMNA
    int fromY = position[1]; // 0 - 7 FILA
    int toX = position[2]; //A-H COLUMNA
    int toY = position[3];//0 -7 FILA
    // X son columnas e Y son las filas.
    t_tile space = board[fromX][fromY];
    int empty = -1;
    
    if (space.empty)
    {
        //print("No piece to access. Please move an actual piece.");
        return;
    }
    if (fromX == toX && fromY == toY)
    {
        //print("Invalid move. Same position.");
        return;
    }
    empty = fetchMovement(space.piece, toX, toY); // Liberamos la pos de from
    space.empty = empty;
}

static int fetchMovement(t_piece piece, int toX, int toY)
{
    int mov = -1;
    switch (piece.name)
    {
    case PAWN:
        mov = pawn(piece, toX, toY);
        break;
    case TOWER:
        mov = tower(piece, toX, toY);
        break;
    case BISHOP:
        mov = bishop(piece, toX, toY);
        break;
    case QUEEN:
        mov = queen(piece, toX, toY);
        break;
    case KING:
        mov = king(piece, toX, toY);
        break;
    case HORSE:
        mov = horse(piece, toX, toY);
        break;

    default:
        break;
    }
    int flag = mov == 0;//si es cero, es que puede moverse
    if(flag){
        move(piece, toX, toY);
    }
    return !flag;   
}

/****Inicializamos piezas y tablero *****/

static void initializeBoard()
{
    for (int j = 0; j < 8; j++)
    {
        //Se ponen los peones primero con sus respectivos colores y posiciones.
        board[j][1].empty = FALSE;
        board[j][6].empty = FALSE;
        board[j][1].piece = initializePiece(j, 1, PAWN, WHITE, PLAYER1);
        board[j][6].piece = initializePiece(j, 6, PAWN, BLACK, PLAYER2);
    }
    //Se ponen las torres
    board[0][0].empty = FALSE;
    board[0][7].empty = FALSE;
    board[0][0].piece = initializePiece(0, 0, TOWER, WHITE, PLAYER1);
    board[0][7].piece = initializePiece(0, 7, TOWER, BLACK, PLAYER2);
    board[7][0].empty = FALSE;
    board[7][7].empty = FALSE;
    board[7][0].piece = initializePiece(7, 0, TOWER, WHITE, PLAYER1);
    board[7][7].piece = initializePiece(7, 7, TOWER, BLACK, PLAYER2);

    //Se ponen los caballos
    board[1][0].empty = FALSE;
    board[1][7].empty = FALSE;
    board[1][0].piece = initializePiece(1, 0, HORSE, WHITE, PLAYER1);
    board[1][7].piece = initializePiece(1, 7, HORSE, BLACK, PLAYER2);
    board[6][0].empty = FALSE;
    board[6][7].empty = FALSE;
    board[6][0].piece = initializePiece(6, 0, HORSE, WHITE, PLAYER1);
    board[6][7].piece = initializePiece(6, 7, HORSE, BLACK, PLAYER2);

    //Se ponen los alfiles
    board[2][0].empty = FALSE;
    board[2][7].empty = FALSE;
    board[2][0].piece = initializePiece(2, 0, BISHOP, WHITE, PLAYER1);
    board[2][7].piece = initializePiece(2, 7, BISHOP, BLACK, PLAYER2);
    board[5][0].empty = FALSE;
    board[5][7].empty = FALSE;
    board[5][0].piece = initializePiece(5, 0, BISHOP, WHITE, PLAYER1);
    board[5][7].piece = initializePiece(5, 7, BISHOP, BLACK, PLAYER2);

    //Se pone a la reina
    board[3][0].empty = FALSE;
    board[3][7].empty = FALSE;
    board[3][0].piece = initializePiece(3, 0, QUEEN, WHITE, PLAYER1);
    board[3][7].piece = initializePiece(3, 7, QUEEN, BLACK, PLAYER2);

    //Se pone al rey
    board[4][0].empty = FALSE;
    board[4][7].empty = FALSE;
    board[4][0].piece = initializePiece(4, 0, KING, WHITE, PLAYER1);
    board[4][7].piece = initializePiece(4, 7, KING, BLACK, PLAYER2);
    
    //Se inicializan los espacios vacios de la matriz logica
    for (int i = 2; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[j][i].empty = TRUE;
            board[j][7-i].empty = TRUE;
        }
    }
}

//inializamos una pieza con los datos pasados
static t_piece initializePiece(int posX, int posY, typePieces name, int color, int player)
{
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

void drawBoard(int x, int y)
{
    //char num[1];
    for (int i = 0; i < 8; i++) //WIDTH_T / PIECE_WIDTH
    {
        for (int j = 0; j < 8; j++) //HEIGHT_T / PIECE_HEIGHT
        {
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) //ambos pares o ambos impares
                drawSquare(x + i * TILE, y + j * TILE, TILE, BEIGE);
            else
                drawSquare(x + i * TILE, y + j * TILE, TILE, BROWN);
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

static void drawPieces(int x, int y)
{
    //extern void _drawFigure(char *toDraw, int color, int size, int x, int y);
    int piece, color;
    for (int i = 0; i < 8; i++) //WIDTH_T / PIECE_WIDTH
    {
        for (int j = 0; j < 8; j++) //HEIGHT_T / PIECE_HEIGHT
        {
            if (board[i][j].empty == FALSE)
            {
                piece = board[i][j].piece.name;
                color = board[i][j].piece.color;
                _drawFigure(piecesBitmap(piece), color, 5, x + i * TILE, y + j * TILE);
            }
        }
    }
}

//************* MOVIMIENTOS ***********//
int attack(t_piece fromPiece, t_piece toPiece)
{
    t_tile toTile = getTile(toPiece.posX, toPiece.posY);
    if (fromPiece.player != toPiece.player)
    {
        deleteFigure(toTile.piece);
        toTile.empty = TRUE; //dejo libre el casillero al que voy asi puedo moverme
        return 0;
    }
    else
        return 1;
}

static void deleteFigure(t_piece piece)
{
    if((piece.posX % 2== 0 && piece.posY %2 ==0) || (piece.posX % 2== 1 && piece.posY %2 ==1)){
        _drawFigure(piecesBitmap(EMPTY), BEIGE, 5, 300 + piece.posX *TILE, piece.posY *TILE);
    }
    else{
        _drawFigure(piecesBitmap(EMPTY), BROWN, 5, 300 + piece.posX * TILE, piece.posY * TILE);
    }   
}

static void move(t_piece piece, int toX, int toY)
{
    deleteFigure(piece);
    board[piece.posX][piece.posY].empty = TRUE;
    piece.posX = toX;
    piece.posY = toY;
    piece.moved = TRUE;
    board[toX][toY].piece = piece;
    board[toX][toY].empty = FALSE;
    _drawFigure(piecesBitmap(piece.name), piece.color, 5, 300+ toX * TILE, toY * TILE);
}

//utilizamos para traer un casillero 
static t_tile getTile(int x, int y)
{
    t_tile toReturn = board[x][y];
    // printInt(toReturn.piece.posX);
    // printInt(toReturn.piece.posY);
    return toReturn;
}

void coronation(t_piece fromPiece, typePieces toName, int toX, int toY){
    deleteFigure(fromPiece);
    board[fromPiece.posX][fromPiece.posY].empty = TRUE;
    fromPiece.posX = toX;
    fromPiece.posY = toY;
    fromPiece.moved = TRUE;
    board[toX][toY].piece = fromPiece;
    board[toX][toY].empty = FALSE;
    _drawFigure(piecesBitmap(toName), fromPiece.color, 5, 300+ toX * TILE, toY * TILE);
}

void enroque(int lon){
    //solo si las torres y la reina estan en posiciones iniciales
    //lon sirve por si aun no se movieron las 2 torres y el user elije que enroque hacer
    t_piece tower1P1 = board[0][0].piece, tower2P1 = board[7][0].piece, kingP1 = board[4][0].piece; //piezas del jug 1
    t_piece tower1P2 = board[0][7].piece, tower2P2 = board[7][7].piece, kingP2 = board[4][7].piece; //piezas del jug 2
    int empty = -1;

    t_tile toTower;

    if (lon == 2 || lon == 3){
        if((board[0][0].empty == FALSE ||  board[7][0].empty == FALSE) && board[4][0].empty == FALSE){
            if(tower1P1.moved == FALSE  && kingP1.moved == FALSE ){    
                //vemos de izquierda a derecha, torre 1 es en A1 y torre 2 es en H1
                if(lon == 2){//enroque corto
                    toTower = getTile(7 - lon, 0);
                    empty = isEmptyP(tower2P1, 7-lon, 0, -1, 0);
                       
                    if(empty == FALSE && toTower.empty != FALSE){
                        move(tower2P1, 7 - lon, 0);
                        move(kingP1, 4 + 2, 0);
                    }
                }
                if(lon == 3){//enroque largo
                    toTower = getTile(7 - lon, 0);
                    empty = isEmptyP(tower1P1, 7- lon, 0, 1, 0);
                    
                    if(empty != TRUE && toTower.empty != FALSE){
                        move(tower1P1, 0 + lon, 0);
                        move(kingP1, 4 -2, 0);
                    }
                }
            }
        }
        //para el jugador 2
        else{
            if((board[0][7].empty == FALSE || board[7][7].empty == FALSE) && board[4][7].empty == FALSE){
                if(tower1P2.moved == FALSE  && kingP2.moved == FALSE ){    
                    //vemos de izquierda a derecha, torre 1 es en A8 y torre 2 es en H8
                    if(lon == 2){//enroque corto
                        toTower = getTile(7 - lon, 7);
                        empty = isEmptyP(tower2P2, 7- lon, 7, -1, 0);
                        
                        if(empty != TRUE && toTower.empty != FALSE){
                            move(tower2P2, 7 - lon, 7);
                            move(kingP2, 4 + 2, 7);
                        }
                    }
                    if(lon == 3){//enroque largo
                        toTower = getTile(0 + lon, 7);
                        empty = isEmptyP(tower1P2, 0 + lon, 7, 1, 0);
                        
                        if(empty != FALSE && toTower.empty != FALSE){
                            move(tower1P2, 0 + lon, 7);
                            move(kingP2, 4 -2, 7);
                        }
                    }
                }
            }
        }
    }
}

//vemos si estan vacios los casilleros entre medio hacia adelante y atras, dependiendo el movimiento
//1 es que no pude moverme, 0 que si
static int isEmptyP(t_piece fromPiece, int toX, int toY, int iX, int iY)
{
    int fromX = fromPiece.posX, fromY = fromPiece.posY;

        for (int i = fromX + iX; i <= toX; i++)
        {
            for (int j = fromY + iY; j <= toY; j++)
            {
                if (board[i][j].empty == FALSE){
                    return 1;
                }
            }
        } 

    return 0;
}

static int isEmptyP2(t_piece fromPiece, int toX, int toY, int iX, int iY)
{
    int fromX = fromPiece.posX, fromY = fromPiece.posY;
    print("emp");

    for (int i = fromX - iX; i >= fromX; i--)
    {
        print("aq");
        for (int j = fromY + iY; j <= fromY; j++)
            {
                print("emp");
                if (board[i][j].empty == FALSE){
                    return 1;
                }
            }
    }
    return 0;
}

static int isEmptyN2(t_piece fromPiece, int toX, int toY, int iX, int iY)
{
    int fromX = fromPiece.posX, fromY = fromPiece.posY;

    for (int i = fromX + iX; i <= toX; i++)
    {
        for (int j = fromY - iY; j >= toY; j--)
            {
                if (board[i][j].empty == FALSE){
                    return 1;
                }
            }
    }
    return 0;
}

static int isEmptyN(t_piece fromPiece, int toX, int toY, int iX, int iY)
{
    int fromX = fromPiece.posX, fromY = fromPiece.posY;

    for (int i = fromX - iX; i >= toX; i--)
    {
        for (int j = fromY - iY; j >= toY; j--)
        {
            if (board[i][j].empty == FALSE){
                return 1;
            }
        }
    }
    return 0;
}

//************* PIEZAS ***********//

int pawn(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    int empty = -1;
    t_tile toTile;
    
    if(fromPiece.player == PLAYER1){
        if (fromY > toY){
            return empty; 
        }   
        //si el movimiento es en diagonal solo si hay una pieza a comer o al paso, sino es ilegal
        if (fromX != toX)
        {
            if (toX == fromX + 1 && toY == fromY +1)
            {
                toTile = getTile(toX, toY);
                if (toTile.empty == FALSE)
                {
                    empty = attack(fromPiece, toTile.piece);
                    return empty;
                }                   
                //vereficamos si podemos hacer captura al paso, porque en diagonal esta libre
                else
                {
                    toTile = getTile(toX, toY - 1);
                    if (toTile.empty == FALSE){
                        empty = attack(fromPiece, toTile.piece);
                        return empty;
                    }
                }                
            }
            if (toX == fromX - 1 && toY == fromY +1)
            {
                toTile = getTile(toX, toY);
                if (toTile.empty == FALSE)
                {
                    empty = attack(fromPiece, toTile.piece);
                    return empty;
                }
                //vereficamos si podemos hacer captura al paso
                else
                {
                   toTile = getTile(toX, toY - 1);
                    if (toTile.empty == FALSE){
                        empty = attack(fromPiece, toTile.piece);
                        return empty;
                    }
                }
            }
        }
        //si el movimiento es recto
        else
        {
            if (toY == fromY + 2 && fromPiece.moved == FALSE)
            {
                //miro si los 2 de adelante estan libres
                empty = isEmptyP(fromPiece, toX, toY,0, 1);
            }
            else{
                if (toY == FINAL_ROW && toCoronation != 6)
                {
                    coronation(fromPiece, toCoronation, toX, toY);
                    return -1;
                }
                if(toY == fromY + 1){
                    empty = isEmptyP(fromPiece, toX, toY,0, 1);
                }
                     
            }       
        }
    }
    //analizo el juegador 2
    else{
        if (fromY < toY)
            return empty;
        //si el movimiento es en diagonal
        if (fromX != toX)
        {
                if (toX == fromX + 1 && toY == fromY - 1)
                {
                    //come en diagonal si esta ocupado
                    toTile = getTile(toX, toY);
                    if (toTile.empty == FALSE)
                    {
                        empty = attack(fromPiece, toTile.piece);
                        return empty;
                    }
                    //vereficamos si podemos hacer captura al paso, porque en diagonal esta libre
                    else
                    {
                        toTile = getTile(toX , toY +1);
                        if (toTile.empty == FALSE){
                            empty = attack(fromPiece, toTile.piece);
                            return empty;
                        }
                    }
                }
                if (toX == fromX - 1 && toY == fromY - 1)
                {
                    toTile = getTile(toX, toY);
                    if (toTile.empty == FALSE)
                    {
                        empty = attack(fromPiece, toTile.piece);
                        return empty;
                    }
                    //vereficamos si podemos hacer captura al paso
                    else
                    {
                        toTile = getTile(toX, toY + 1);
                        if (toTile.empty == FALSE){
                            empty = attack(fromPiece, toTile.piece);
                            return empty;
                        }
                    }
                }
         }
        //si el movimiento es recto
        else
        {
                if (toY == fromY - 2 && fromPiece.moved == FALSE)
                {
                    //miro si los 2 tile de las filas adelante estan vacias
                    empty = isEmptyN(fromPiece, toX, toY ,0, 1);
                }
                else{
                    if( toY == FIRST_ROW && toCoronation != 6){ 
                        coronation(fromPiece, toCoronation, toX, toY);
                        return -1;
                    }
                    if(toY == fromY - 1){
                        empty = isEmptyN(fromPiece, toX, toY,0, 1);
                    }                    
                }        
        }
    }    
    return empty;
}

int tower(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    t_tile toTile= getTile(toX, toY);
    int empty = -1;
    int near = abs(toY - fromY) + abs(toX - fromX);

    if (fromX == toX)
    {   
        if(fromY < toY)
            empty = isEmptyP(fromPiece, toX, toY, 0, 1);
        else
            empty = isEmptyN(fromPiece, toX, toY, 0, 1);
    }
    else{
        if( fromY == toY){
            if(fromX < toX)
                empty = isEmptyP(fromPiece, toX, toY, 1, 0);
            else
                empty = isEmptyN(fromPiece, toX, toY, 1, 0);
        }
    }

    if (toTile.empty != FALSE && (empty == FALSE ))
        empty = attack(fromPiece, toTile.piece);
    
    return empty;
}

int bishop(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    t_tile toTile = getTile(toX, toY);
    int near = abs(toY - fromY) + abs(toX - fromX);

    int empty = -1;
    if (toX - fromX == toY - fromY){ // ambos pos o neg
        if(toX > fromX)
            empty = isEmptyP(fromPiece, toX, toY, 1, 1);
        else 
            empty = isEmptyN(fromPiece, toX, toY, 1, 1);
    }
    else{
        if (-(toX - fromX) == toY - fromY){
            if(toX > fromX){
                empty = isEmptyN2(fromPiece, toX, toY, 1, 1);
            }
            else {
                print("p2");
                empty = isEmptyP2(fromPiece, toX, toY, 1, 1);
            }
        }
    }

    if (toTile.empty != FALSE && (empty == FALSE || near == 2)){
        empty = attack(fromPiece, toTile.piece);
    }
    
    return empty;
}

int king(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    int empty = -1;
    
    if( (toY == fromY && (toX == fromX + 1 || toX == fromX - 1)) || (toX == fromX && (toY == fromY + 1 || toY == fromY - 1)) ) {
        empty = tower(fromPiece, toX, toY);
    }
    else{
        if(((toX == fromX + 1) || (toX == fromX - 1)) && ((toY == fromY + 1) || (toY == fromY - 1)) )
            empty = bishop(fromPiece, toX, toY);
    }
    
    return empty;
}

int queen(t_piece fromPiece, int toX, int toY){
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    int empty = -1;
    print("reina");

    if (abs(toX - fromX) == abs(toY - fromY)){
        print("reiR");
        empty = bishop(fromPiece, toX, toY);
    }
    else{
        if(toX == fromX || fromY == toY){
            empty = tower(fromPiece, toX, toY);
            print("reiD");
        }
    }
    return empty;
}

int horse(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    int empty = -1;
    if ((((toX != fromX + 2) || (toX != fromX - 2)) && ((toY != fromY + 1) || (toY != fromY - 1))) ||
        (((toX != fromX + 1) || (toX != fromX - 1)) && ((toY != fromY + 2) || (toY != fromY - 2))))
    {
        //print("Invalid move.");
        return 1;
    }
    t_tile toTile1 , toTile2;
    if(toX == fromX + 2 && toY == fromY + 1) {
        toTile1 = getTile(toX, fromY), toTile2 = getTile(fromX, toY); 
        empty = isEmptyP(fromPiece, toX, toY, 1, 0) && isEmptyP(toTile1.piece, toX, toY, 0, -1);
    }
    if (toTile2.empty != FALSE)
        empty = attack(fromPiece, toTile2.piece);

    return empty;
}

// void intializeTestingBoard(){
//     for (int i = 0; i < 8; i++)
//     {
//         for (int j = 0; j < 8; j++)
//         {
//             board[j][i].empty = TRUE;
//         }
//     }
//     board[1][1].empty = FALSE;
//     board[1][1].piece = initializePiece(1,1,PAWN,WHITE,PLAYER1);
//     board[0][7].empty = FALSE;
//     board[0][7].piece = initializePiece(0,7,TOWER,WHITE,PLAYER1);
//     board[7][7].empty = FALSE;
//     board[7][7].piece = initializePiece(7,7,TOWER,WHITE,PLAYER1);
//     board[4][7].empty = FALSE;
//     board[4][7].piece = initializePiece(4,7,KING,WHITE,PLAYER1);
// }
  