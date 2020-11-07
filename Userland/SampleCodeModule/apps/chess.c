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


int timer_player1 = 0, timer_player2 = 0, currentPlayer = PLAYER1;

static t_piece initializePiece(int posX, int posY, typePieces name, int color, int player);
static void initializeBoard();
static void drawPieces(int x, int y);
static int fetchMovement(t_piece piece, int toX, int toY);

static void deleteFigure(t_piece toPiece);
static t_tile getTile(int x, int y);
static void move(t_piece piece, int toX, int toY);
static int isEmptyP(int fromX, int fromY, int toX, int toY);
static int isEmptyN(int fromX, int fromY, int toX, int toY);

void game();
int readPlayerInput(char *inputBuffer, int maxSize, char token);
void startTimer(int player);
void endTimer();
void activeTimer();

void startGame(int mode)
{
    _clearScreen();
    drawBoard(300, 0);

    if (mode == NEW_GAME)
    {   
        initializeCursor();
        initializeBoard();
        drawPieces(300, 0);
        currentPlayer = PLAYER1;
        startTimer(currentPlayer);
        // Cambiar.
        printPlayer(currentPlayer, LAST_LINE);
        game();
    }
    if (mode == CONTINUE_GAME)
        print("continue");
    putChar('\n');
}
void game() {
    int quit = 0;
    while (quit == 0) //c = getChar()) != 'q'
        {
            quit = readPlayerInput(input, MAX_INPUT, 'q');
            // 1 si se movio la pieza 0 si no. -1 cuando se termino el tiempo del jugador o murio el rey del otro jugador.
            // if (processGame(input))
            // {
            //     (currentPlayer==PLAYER1)?(currentPlayer=PLAYER2):currentPlayer;
            //     startTimer(currentPlayer);
            // }
            
        }
        _clearScreen();
        if (quit == -1)
        {
            (currentPlayer == PLAYER1) ? print("Game Over. Player 2 has won!") : print("Game Over. Player 1 has won!");
        }
        if(quit == 3){
            //Se mato al rey enemigo.
            (currentPlayer == PLAYER2) ? print("Game Over. Player 2 has won!") : print("Game Over. Player 1 has won!");
        }

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
            if(letter == 'e' && (num == '2' || num == '3')){//verificamos si entro un e y long, para hacer enroque
                num = num - '0' - 1;
                enroque(num);
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
            return 0;//"Invalid input, please use the correct notation."
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
        return;//"No piece to access. Please move an actual piece.";
    if (fromX == toX && fromY == toY)
        return;//"Invalid move. Same position.";
        
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

void startTimer(int player)
{
    (player == PLAYER1) ? (timer_player1 = 0) : (timer_player2 = 0);
    // syscall.
    _timerFunc(&activeTimer, TRUE);
}

void endTimer()
{
    timer_player1 = 0;
    timer_player2 = 0;
    _timerFunc(&activeTimer, FALSE);
}

// Funcion pasada por parametro encargada de actualizar los contadores de tiempo.
void activeTimer()
{
    if (currentPlayer == PLAYER1)
    {
        timer_player1++;
    }
    else if (currentPlayer == PLAYER2)
    {
        timer_player2++;
    }
}
// Funcion nueva que lee input del teclado.
int readPlayerInput(char *inputBuffer, int maxSize, char token)
{
    int size = 0;
    uint64_t c;
    while (size < (maxSize - 1) && (c = getChar()) != '\n' && c != token)
    {

        if (c && c != '\t') // Verificamos que se presiona una letra. No permitimos tabs en esta consola porque romperia con las dimensiones predeterminadas.
        {
            if (c != '\b')
            {
                displayChar(c);
                inputBuffer[size++] = c;
            }
            else if (size > 0)
            {
                displayChar('\b');
                size--;
            }
        } else
        { // Se hace un update en el timer visual para que el jugador vea el tiempo que lleva.
        int time = (currentPlayer == PLAYER1 ? timer_player1 : timer_player2);
        if(time%TIMER_TICKS_PER_SEC==0)
        {
            // printInt(time/TIMER_TICKS_PER_SEC);
            updateTimerConsole(time/TIMER_TICKS_PER_SEC);
        }

        if ((timer_player1 / TIMER_TICKS_PER_SEC) >= 60 || (timer_player2 / TIMER_TICKS_PER_SEC) >= 60)
        {
            return -1;
        }}
    }
    // Ponemos la marca de final al string.
    inputBuffer[size++] = 0;
    if(c == '\n'){
        char aux[size];
        memcpy(aux, inputBuffer, size);
        if (processGame(inputBuffer)){
                printLogLine(aux, currentPlayer);
                endTimer(currentPlayer);
                (currentPlayer==PLAYER1)?(currentPlayer=PLAYER2):currentPlayer;
                startTimer(currentPlayer);
                printPlayer(currentPlayer, LAST_LINE);
                printEntireLog();
            }else{
                clearLine(LAST_LINE);
                printPlayer(currentPlayer, LAST_LINE);
                resetCursor();
            }
    }
    
    return c == token;
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
    piece.posX = posX;
    piece.posY = posY;
    piece.moved = FALSE;
    return piece;
}

void drawBoard(int x, int y)
{
    char *c[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    char numToPrint[2];
    for (int i = 0; i < 8; i++) //WIDTH_T / PIECE_WIDTH
    {
        for (int j = 0; j < 8; j++) //HEIGHT_T / PIECE_HEIGHT
        {
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) // ambos pares o ambos impares
                drawSquare(x + i * TILE, y + j * TILE, TILE, BEIGE);
            else
                drawSquare(x + i * TILE, y + j * TILE, TILE, BROWN);
        }
        uintToBase(i+1, numToPrint, 10);
        // Numeros
        printIn(c[i], (MAX_WIDTH / CHAR_WIDTH) + 7 + i * (TILE / CHAR_WIDTH), LAST_LINE - 4, BROWN);
        // Letras.
        printIn(numToPrint, (MAX_WIDTH / CHAR_WIDTH) - 2, i * (TILE / CHAR_HEIGHT) + 3, BEIGE);
    }
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
    board[piece.posX][piece.posY].empty = TRUE;
    deleteFigure(piece);
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
    int fromX ,fromY;

    if((board[0][0].empty == FALSE ||  board[7][0].empty == FALSE) && board[4][0].empty == FALSE){
            if(tower1P1.moved == FALSE  && kingP1.moved == FALSE ){    
                //vemos de izquierda a derecha, torre 1 es en A1 y torre 2 es en H1
                if(lon == 2){//enroque corto
                    fromX = tower2P1.posX; fromY = tower2P1.posY;
                    empty = tower(tower2P1, fromX + lon, fromY);                       
                    if(empty == FALSE){
                        move(tower2P1, 7 - lon, 0);
                        move(kingP1, 4 + 2, 0);
                    }
                }
                if(lon == 3){//enroque largo
                    empty = tower(tower1P1, 7- lon, 0);
                    
                    if(empty == FALSE){
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
                        empty = tower(tower2P2, 7- lon, 7);
                        
                        if(empty == FALSE){
                            move(tower2P2, 7 - lon, 7);
                            move(kingP2, 4 + 2, 7);
                        }
                    }
                    if(lon == 3){//enroque largo
                        empty = tower(tower1P2, 0 + lon, 7);
                        
                        if(empty == FALSE){
                            move(tower1P2, 0 + lon, 7);
                            move(kingP2, 4 -2, 7);
                        }
                    }
                }
            }
    }
}

//vemos si estan vacios los casilleros entre medio hacia adelante y atras, dependiendo el movimiento
//1 es que no pude moverme, 0 que si
static int isEmptyP(int fromX, int fromY, int toX, int toY)
{
    for (int j = 1; fromY + j <= toY; j++)
    {
            if (board[fromX][fromY +j].empty == FALSE){
                return 1;
            }
    }    
    return 0;
}

static int isEmptyN(int fromX, int fromY, int toX, int toY)
{
    for (int j = 1; fromY - j >= toY; j++)
    {
            if (board[fromX][fromY - j].empty == FALSE ){//&& board[i][j].piece.posX != toX &&  board[i][j].piece.posY != toY
                return 1; 
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
                empty = isEmptyP(fromX, fromY, toX, toY);
            }
            else{
                if (toY == FINAL_ROW && toCoronation != 6)
                {
                    coronation(fromPiece, toCoronation, toX, toY);
                    return -1;
                }
                if(toY == fromY + 1){
                    empty = isEmptyP(fromX, fromY, toX, toY);
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
                    empty = isEmptyN(fromX, fromY, toX, toY);
                }
                else{
                    if( toY == FIRST_ROW && toCoronation != 6){ 
                        coronation(fromPiece, toCoronation, toX, toY);
                        return -1;
                    }
                    if(toY == fromY - 1){
                        empty = isEmptyN(fromX, fromY, toX, toY);
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
    int empty = -1, i;

    if (fromX == toX)
    {   
        if(fromY < toY){//abajo
            for(i = 1; fromY + i < toY; i++){
                if(board[fromX][fromY +i].empty == FALSE){
                    return 1;
                }
            }
            empty = 0; 
        }
        else{//arriba
            for(i = 1; fromY - i > toY; i++){
                if(board[fromX][fromY -i].empty == FALSE){
                    return 1;
                }
            }
            empty = 0; 
        }
    }
    else{
        if( fromY == toY){
            if(fromX < toX){//derecha
                for(i = 1; fromX + i < toX; i++){
                    if(board[fromX + i][fromY].empty == FALSE){
                        return 1;
                    }
                }
                empty = 0; 
            }
            else{//izquierda
                for(i = 1; fromX - i > toX; i++){
                    if(board[fromX - i][fromY].empty == FALSE){
                        return 1;
                    }
                }
                empty = 0;
            }
        }
    }

   if (toTile.empty == TRUE && empty == FALSE){//pude recorrer y si tambien esta vacio el ultimo, movete
            return 0;
    }
    else
    {
       if(toTile.empty == FALSE && empty == FALSE){ //pudo recorrer y mira el ultimo a ver si puede comer
        empty = attack(fromPiece, toTile.piece);
        }    
    } 
    
    return empty;
}

int bishop(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    t_tile toTile = getTile(toX, toY);

    int empty = -1, i;
    if (toX - fromX == toY - fromY){ // ambos pos o neg
        if(toX > fromX){//  hacia la derecha y abajo 
            for (i = 1; fromX + i < toX && fromY + i < toY; i++)
            {
                if(board[fromX + i][fromY + i].empty != TRUE){
                    return 1;                   
                }
            }
            empty = 0;
        }
        else{// hacia izquierda arriba
            for (i = 1; fromX - i > toX && fromY - i > toY; i++)
            {
                if(board[fromX - i][fromY - i].empty != TRUE){
                    return 1;
                }
            }
            empty = 0;
        }
    }
    else{
        if (-(toX - fromX) == toY - fromY){
            if(toX > fromX){// hacia la derecha y arriba 
                for (i = 1; fromX + i < toX && fromY - i > toY; i++)
                {
                    if(board[fromX + i][fromY - i].empty != TRUE){
                        return 1;                    
                    }
                }
                empty = 0;
            }
            else{// hacia la izquierda abajo
                for (i = 1; fromX - i > toX && fromY + i < toY; i++)
                {
                    if(board[fromX - i][fromY + i].empty != TRUE){
                        return 1;
                    }
                }
                empty = 0;
            }
        }
    }
    if (toTile.empty == FALSE && empty == FALSE){
        empty = attack(fromPiece, toTile.piece);
    }
    else
    {
        if(toTile.empty == TRUE && empty == FALSE){
            return 0;
        }
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

    if(toX == fromX || fromY == toY){
            empty = tower(fromPiece, toX, toY);
    }
    else{
        if (abs(toX - fromX) == abs(toY - fromY)){
            empty = bishop(fromPiece, toX, toY);
        }
    }

    return empty;
}

int horse(t_piece fromPiece, int toX, int toY)
{
    int fromX = fromPiece.posX;
    int fromY = fromPiece.posY;
    int empty = -1;

    int potentialMoves[8][2] = {
        {fromX + 1, fromY - 2},
        {fromX + 2, fromY - 1},
        {fromX - 1, fromY - 2},
        {fromX - 2, fromY - 1},
        {fromX + 1, fromY + 2},
        {fromX + 2, fromY + 1},
        {fromX - 1, fromY + 2},
        {fromX - 2, fromY + 1},
    };
    t_tile tile = board[toX][toY];

    for (int j = 0; j < 8; j++)
    {
        if (toX == potentialMoves[j][0] && toY == potentialMoves[j][1] )
        {;
            if (tile.empty != FALSE){
                return 0;    
            }
            else{
                empty = attack(fromPiece, tile.piece);
                return empty; 
            }                    
        }
    }       
    return empty;
}
  